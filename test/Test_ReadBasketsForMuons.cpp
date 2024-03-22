/*
 * Kirtikesh Kumar
 * 2024-03-22
 * Code to read baskets and find all muon events 
 * 
 * 		argv[1] is the filename to be checked
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
	
	//vector to read the file into
	std::vector<ismran::SingleBasket *> vecOfBaskets;
	
	//open the file for reading
	TFile *file = TFile::Open(dataFileName.c_str(), "READ");
	if (!file || file->IsZombie()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
    
    //read the tree 
	TTree *ftree = dynamic_cast<TTree*>(file->Get("basketTree"));
    if (!ftree) {
        std::cerr << "Error: Unable to retrieve tree from file." << std::endl;
        file->Close();
        return 1;
    }
    
    // Set the branch address to read the object from the tree
	ismran::SingleBasket *basket = new ismran::SingleBasket();
    ftree->SetBranchAddress("Baskets", &basket);
    
    //opening the file to write the Muon baskets into
    std::string outfileName = "Muon.root";
	TFile *mubasketFile = new TFile(outfileName.c_str(), "RECREATE");
	if (!mubasketFile || mubasketFile->IsZombie()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }
	mubasketFile->cd();
	TTree *muBasketTree = new TTree("basketTree", "basketTree");
	muBasketTree->Branch("Baskets", "ismran::SingleBasket", &basket);
	
	//Reading entries one by one and performing analysis
	Long64_t nentries = ftree->GetEntries();
	Long64_t nbytes = 0;
	Double_t avBasketEnergy;
	
	//for plotting 2d basket hits
	/*TCanvas *c1 = new TCanvas("c1","",10,10,720,800);
	c1->cd(1);
	gStyle->SetPalette(kRainBow);
	TH2* H2D = new TH2F("H2D", "2D Hits", 9,0,9, 10,0,10); 
	std::vector<ismran::ScintillatorBar_F *> basketscint;
	H2D->SetStats(0);
	ushort indxb;
	Double_t levels[501];
	for(int i=0;i<sizeof(levels)/sizeof(levels[0]);i++){
		levels[i]=i*0.1;
	}*/
	
	for (Long64_t i=0; i<nentries;i++) {
		nbytes += ftree->GetEntry(i);
		avBasketEnergy = (basket->GetBasketEnergy())/basket->size();
		if(basket->size() >= 5 and (avBasketEnergy >= 15.0 and avBasketEnergy <= 25.0)){
			muBasketTree->Fill();
		}
	}
	
	//write to file
	mubasketFile->cd();
    muBasketTree->Write();
    mubasketFile->Close();
	
	
	//fApp->Run();
}
