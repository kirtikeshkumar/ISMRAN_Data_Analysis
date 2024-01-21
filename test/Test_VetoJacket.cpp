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
int main(int argc, char *argv[]){
	//std::cout<<"0th argv"<<std::string(argv[0])<<std::endl;
	std::string dataFileName    = std::string(argv[1]);
	std::string calibFileName	= std::string(argv[2]);
	unsigned int numOfEvts	= 0;
	unsigned int numEvts	= 0;					// number of events not vetoed
	unsigned int numVeto	= 0;					// number of vetoed events
	const int dT			= 20000;				// dead time in picoseconds
	ULong64_t fdTStamp		= 0;					// =time of jacket hit + dead time 
	//ushort barVIndx			= 10000;				// index of bar being vetoed by jacket
	ULong64_t StartTStamp	= 0;					// Start of File TStamp
	ULong64_t StopTStamp	= 0;					// End of File TStamp
	int QMean				= 0;					// QMean for single event
	Double_t E				= 0.0;					// Energy corresponding to a single event
	ushort numVetoLayers	= 4;					// Number of Layers to use for Veto
	ushort barindex;
	
	//std::string barName     = "PS45_S1AA6525";		// bar to veto 
	//std::string barName     = "PS15_S2AB1011";
	//std::string barName     = "PS62_S3AA1781";
	//std::string barName     = "PS49_S1AA6642";
	//std::string barName     = "PS25_S2AB0717";
	//std::string barName     = "PS66_S1AA6639";
	//std::string barName     = "PS48_S1AA6708";
	//barVIndx = ismran::GetIndexFromBarName(ismran::vecOfPsBars,barName);
	//std::cout << "the index for bar "<<barName<<" is "<<barVIndx<<std::endl;
	
	std::vector<ismran::ScintillatorBar_F *> vecNoVetos;
	std::vector<ismran::ScintillatorBar_F *> vecOfSignal;
	TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	c1->cd(1);
	
	
	ismran::Analyzer_F an(dataFileName, numOfEvts);											//read the events in file
	std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators(); 	//adds all events into a vector
	std::sort(vecOfScint.begin(), vecOfScint.end(), ismran::CompareTimestampScintillator);	//sort all events according to fTStamp
	
	
	//Generate a calibration object and extract the calibration for the required bar
	ismran::Calibration Calib(calibFileName);																				
	ismran::CalibrationData *CalibDat;// = Calib.GetCalibrationDataOf(barVIndx);
	TF1 ECalib;// = *CalibDat->GetEnergyCalibFormula();
	
	TH1* HFull = new TH1D("HFull", "", 1000, 0.0, 100.0);				//Histogram for All events in the required bar
	HFull->SetLineColor(kGreen);
	TH1* HSig  = new TH1D("HSig", "", 1000, 0.0, 100.0);				//Histrogram of events after veto
	HSig->SetLineColor(kRed);
	
	std::vector<int> VetoBarsIndx = ismran::GetJacketBarIndx(numVetoLayers);
	
	for(int i=0;i < vecOfScint.size();i++){
		barindex = vecOfScint[i]->GetBarIndex();
		if(ismran::IsJacket(barindex, VetoBarsIndx)){					//is the event in jacket?
			/*if(barindex==barVIndx){
				std::cout << "Hi" << std::endl;
			}*/
			fdTStamp = vecOfScint[i]->GetTStampSmall()+dT;
			//numVeto += 1;
		}else{// if(barindex==barVIndx){
			CalibDat = Calib.GetCalibrationDataOf(barindex);
			ECalib = CalibDat->GetEnergyCalibFormula();
			//std::cout << "Hi" << std::endl;
			vecNoVetos.push_back(vecOfScint[i]);
			QMean = vecOfScint[i]->GetQMean();
			HFull->Fill(ECalib(QMean));
			if(vecOfScint[i]->GetTStampSmall() < fdTStamp){				//has the deadtime passed?
				numVeto += 1;
				//vecOfVetos.push_back(vecOfScint[i]);
			}else{
				numEvts += 1;
				vecOfSignal.push_back(vecOfScint[i]);
				HSig->Fill(ECalib(QMean));
			}
		}
	}
	//std::cout << "First event TStamp: "<<vecOfScint[0]->GetTStampSmall()<<std::endl;
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
    TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
    leg->SetBorderSize(0);
    leg->AddEntry(HFull,"All Events","l");
    leg->AddEntry(HSig,"After Veto","l");
    leg->Draw();
	//ECalib->Draw();
	std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	//c1->SaveAs(("./Spectra_2Jacket_"+barName+"_"+fname+".pdf").c_str());
	c1->SaveAs(("./Spectra_"+barName+"_"+fname+".pdf").c_str());
	
}
