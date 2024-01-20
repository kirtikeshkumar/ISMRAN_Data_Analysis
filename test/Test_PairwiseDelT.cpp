/*
 * Kirtikesh Kumar
 * 2023-10-11
 * Code to find time between two consecutive events.
 * 		argv[1] is the filename to be checked
 * 		argv[2] is optional bar index ------------------- To be added
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
#include <TApplication.h>
int main(int argc, char *argv[]){
	TApplication *fApp       = new TApplication("TEST", NULL, NULL);
	//std::cout<<"0th argv"<<std::string(argv[0])<<std::endl;
	std::string dataFileName    = std::string(argv[1]);
	
	
	unsigned int numOfEvts	= 0;
	ULong64_t fdTStamp		= 0;					// =time of jacket hit + dead time
	const int dT			= 20000;				// dead time in picoseconds
	
	
	TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	c1->cd(1);
	
	
	ismran::Analyzer_F an(dataFileName, numOfEvts);											//read the events in file
	std::vector<ismran::ScintillatorBar_F *> vecOfScint = an.GetVectorOfScintillators(); 	//adds all events into a vector
	std::sort(vecOfScint.begin(), vecOfScint.end(), ismran::CompareTimestampScintillator);	//sort all events according to fTStamp
	
	TH1* HDelT  = new TH1D("HDelT", "", 100, 0, 12);										//Histrogram of time difference between consecutive events
	HDelT->SetLineColor(kRed);
	
	double_t delt=0;
	for(int i=0;i < vecOfScint.size()-1;i++){
		delt=vecOfScint[i+1]->GetTStampAverage()-vecOfScint[i]->GetTStampAverage();
		//HDelT->Fill(delt/1000.0);
		HDelT->Fill(TMath::Log10(delt));
		/*if(ismran::IsJacket(vecOfScint[i]->GetBarIndex()))
		{
			fdTStamp=vecOfScint[i]->GetTStampAverage()+dT;
		}*/
		/*if(vecOfScint[i]->GetTStampAverage() > fdTStamp)
		{
			HDelT->Fill(TMath::Log10(delt));
		}*/
	}
	
	gPad->SetLogy();
    //gPad->SetLogx();
    HDelT->GetXaxis()->SetTitle("DelT");
    HDelT->GetYaxis()->SetTitle("Counts");
    //HDelT->GetYaxis()->SetRangeUser(1,1E9);
    //HDelT->GetXaxis()->SetLimits(0,10.0);
    HDelT->Draw("C");
    //TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
    //leg->SetBorderSize(0);
    //leg->AddEntry(HDelT,"DelT","l");
    //leg->Draw();
	//ECalib->Draw();
	std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	c1->SaveAs(("./Spectra_DelT_Linear_"+fname+".pdf").c_str());
	fApp->Run();
}
