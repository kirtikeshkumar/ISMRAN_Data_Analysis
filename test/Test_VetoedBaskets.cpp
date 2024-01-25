/*
 * Kirtikesh Kumar
 * 2024-01-25
 * Code to generate baskets and remove baskets with events in veto layers.
 * 
 * 		argv[1] is the filename to be checked
 * 		argv[2] is the path to claibration files
 * 		argv[3] is the max duration of single basket in ps
 * 		argv[4] is number of veto layers
 */
#include <iostream>
#include "ScintillatorBar_F.h"
#include "Analyzer_F.h"
#include "SingleBasket.h"
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
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char *argv[]){
	std::cout<<"argc "<<argc<<std::endl;
	TApplication *fApp       = new TApplication("TEST", NULL, NULL);
	
	//Defining all variables from input arguments
	std::string dataFileName    = std::string(argv[1]);
	fs::path calibFilePath		= std::string(argv[2]);
	ushort numVetoLayers 		= 0;									//number of veto layers
	uint basketdT 				= 0;									// max duration of each basket. 
																		//if basketdT = 0, baskets are made based on time difference between events
	if(argv[3]){std::sscanf(argv[3], "%d", &basketdT); }
	if(argv[4]){std::sscanf(argv[4], "%hd", &numVetoLayers); }
	
	//Generating Calibration Instance
	ismran::Calibration Calib;
	Calib.instance(calibFilePath.string());
	
	//Reading and sorting events from file
	unsigned int numOfEvts	= 0;
	ismran::Analyzer_F an(dataFileName, numOfEvts);						//read the events in file
	std::vector<ismran::SingleBasket *> vecOfBaskets; 				
	if(argv[3]){														//construct baskets
		vecOfBaskets = an.ReconstructBasket(basketdT);
	}else{vecOfBaskets = an.ReconstructBasket();}
	unsigned int basketVecSize = vecOfBaskets.size();
	std::cout<<"basketVecSize "<<basketVecSize<<std::endl;
	
	//Generating plots
	/*TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	c1->cd(1);
	TH1* HdTEvtinBasket = new TH1D("HdTEvtinBasket", "", 1000, 1.0, 12);//Histogram for dT between events in basket
	HdTEvtinBasket->SetLineColor(kGreen);
	for(int i=1; i<basketVecSize; i++){
		//for(int j=1; j<vecOfBaskets[i]->size(); j++){
		//	ULong64_t delTime = vecOfBaskets[i]->GetBasketEventTime(j)-vecOfBaskets[i]->GetBasketEventTime(j-1);
		//	HdTEvtinBasket->Fill(delTime/1000.0);
		//}
		ULong64_t delTime = vecOfBaskets[i]->GetBasketStartTime()-vecOfBaskets[i-1]->GetBasketStartTime();
		HdTEvtinBasket->Fill(log10(delTime/1000.0));
		//if(vecOfBaskets[i]->size()==1){HdTEvtinBasket->Fill(0.0);}
	}
	
	gPad->SetLogy();
	gPad->SetLogx();
	HdTEvtinBasket->GetXaxis()->SetTitle("DelT Evt (ms)");
    HdTEvtinBasket->GetYaxis()->SetTitle("Counts");
    HdTEvtinBasket->Draw("C");
    std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	c1->SaveAs(("./delTEvt_"+fname+".root").c_str());
	fApp->Run();
	*/
}
