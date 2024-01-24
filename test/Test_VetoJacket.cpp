/*
 * Kirtikesh Kumar
 * 2023-10-03
 * Code to test the reduction in single events if vetoed using events in
 * 		jacket layer on all four sides.
 * GetJacketBarIndx function defined in HardwareNomenclature gives the index of bars in 
 * 		jacket layer
 */

#include <iostream>
#include "ScintillatorBar_F.h"
#include "Analyzer_F.h"
#include "Plotter.h"
#include <TFile.h>
#include "HardwareNomenclature.h"
#include "Helpers.h"
#include <TString.h>
#include "Database.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1F.h"
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char *argv[]){
	std::string dataFileName    = std::string(argv[1]);
	fs::path calibFilePath	= std::string(argv[2]);
	
	std::string calibFileName;
	std::string BarName;
	char* output;
	
	unsigned int numOfEvts	= 0;
	unsigned int numEvts	= 0;					// number of events not vetoed
	unsigned int numVeto	= 0;					// number of vetoed events
	const int dT			= 20000;				// dead time in picoseconds
	ULong64_t JacketTStamp	= 0;					// Time of jacket hit 
	ULong64_t StartTStamp	= 0;					// Start of File TStamp
	ULong64_t StopTStamp	= 0;					// End of File TStamp
	ULong64_t EvtTStamp		= 0;					// Event TStamp
	int QMean				= 0;					// QMean for single event
	Double_t E				= 0.0;					// Energy corresponding to a single event
	ushort numVetoLayers	= std::strtol(argv[3], &output, 10);			// Number of Layers to use for Veto
	ushort barindex;
	std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	
	std::vector<ismran::ScintillatorBar_F *> vecNoVetos;
	std::vector<ismran::ScintillatorBar_F *> vecOfSignal;
	TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	
	c1->cd(1);
	std::cout<<"NUMBER OF VETO LAYERS IS "<<numVetoLayers<<std::endl;
	
	ismran::Analyzer_F an(dataFileName, numOfEvts);											//read the events in file
	std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators(); 	//adds all events into a vector
	std::sort(vecOfScint.begin(), vecOfScint.end(), ismran::CompareTimestampScintillator);	//sort all events according to fTStamp
	
	StartTStamp = vecOfScint[0]->GetTStampSmall();
	StopTStamp = vecOfScint[vecOfScint.size()-1]->GetTStampLarge();
	
	
	TH1* HFull = new TH1D("HFull", "", 1000, 0.0, 100.0);				//Histogram for All events in the required bar
	HFull->SetLineColor(kGreen);
	TH1* HSig  = new TH1D("HSig", "", 1000, 0.0, 100.0);				//Histrogram of events after veto
	HSig->SetLineColor(kRed);
	/*TH1* HdT  = new TH1D("HdT", "", 1000, 0.0, 100.0);					//Histrogram of dT between events
	HdT->SetLineColor(kBlack);*/
	
	std::vector<int> VetoBarsIndx = ismran::GetJacketBarIndx(numVetoLayers);
	
	//Generate a calibration object and extract the calibration for the required bar
	ismran::Calibration Calib;
	Calib.instance(calibFilePath.string());
	ismran::CalibrationData *CalibDat;
	TF1 ECalib;
	
	for(int i=0;i < vecOfScint.size();i++){
		barindex = vecOfScint[i]->GetBarIndex();	
		EvtTStamp = vecOfScint[i]->GetTStampSmall()-StartTStamp;
		/*if(i>=1){
			HdT->Fill(((EvtTStamp-(vecOfScint[i-1]->GetTStampSmall()-StartTStamp))));
		}*/
		if(ismran::IsJacket(barindex, VetoBarsIndx)){					//is the event in jacket?
			JacketTStamp = EvtTStamp;
			//std::cout<<" Jacket TStamp "<<JacketTStamp<<std::endl;
		}else{
			CalibDat = Calib.instance()->GetCalibrationDataOf(barindex);
			ECalib = *CalibDat->GetEnergyCalibFormula();
			vecNoVetos.push_back(vecOfScint[i]);
			QMean = vecOfScint[i]->GetQMean();
			HFull->Fill(ECalib(QMean)/1000.0);
			if( EvtTStamp - JacketTStamp <= dT ){						//has the deadtime passed?
				numVeto += 1;				
			}else{
				numEvts += 1;
				vecOfSignal.push_back(vecOfScint[i]);
				HSig->Fill(ECalib(QMean)/1000.0);
			}
		}
	}
	std::cout << "First event TStamp: "<<StartTStamp<<std::endl;
	//std::cout << "Time range: "<<vecOfScint[vecOfScint.size()-1]->GetTStampSmall()-vecOfScint[0]->GetTStampSmall()<<std::endl;
	std::cout << "Total number of events: "<<numEvts+numVeto<<" "<<vecOfScint.size()<<std::endl;
	std::cout << "Vetoed events: "<<numVeto<<std::endl;
	std::cout << "Signal events: "<<numEvts<<std::endl;
	//std::cout << vecOfScint[10]->GetQNear()<<" "<<vecOfScint[10]->GetQFar()<<" "<<vecOfScint[10]->GetQMean()<<" "<<ECalib(vecOfScint[10]->GetQMean())<<std::endl;
	
	//Plotting the spectrum of non-vetoed and vetoed events

	
	gPad->SetLogy();
    //gPad->SetLogx();
    HFull->GetXaxis()->SetTitle("E");
    HFull->GetYaxis()->SetTitle("Counts");
    HFull->GetYaxis()->SetRangeUser(1,1E5);
    //HFull->GetXaxis()->SetLimits(0,10.0);
    HFull->Draw();
    HSig->Draw("SAME");
    HdT->Draw("SAME");
    TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
    leg->SetBorderSize(0);
    leg->AddEntry(HFull,"All Events","l");
    leg->AddEntry(HSig,"After Veto","l");
    leg->AddEntry(HdT,"dT/300","l");
    leg->Draw();
	//ECalib->Draw();
	
	c1->SaveAs(("./"+fname+"_Spectra_with_"+std::to_string(numVetoLayers)+"_VetoLayers"+".pdf").c_str());
}
