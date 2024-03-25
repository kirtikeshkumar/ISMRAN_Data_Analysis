/*
 * Kirtikesh Kumar
 * 2024-03-22
 * Code to read baskets and find all muon events 
 * 
 * 		  argv[1] is the Calibration file path
 * 		  argv[2] is the filename to be checked
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
	std::string dataFileName    = std::string(argv[2]);
	
	std::cout<<"Reading "<<dataFileName<<std::endl;
	
	//Generating Calibration Instance
	fs::path calibFilePath		= std::string(argv[1]);
	ismran::Calibration Calib;
	Calib.instance(calibFilePath.string());
	
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
    
    std::cout<<"Loaded basketTree"<<std::endl;
    
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
	
	std::cout<<"There are "<<nentries<<" entries"<<std::endl;
	
	//for plotting 
	TCanvas *c1 = new TCanvas("c1","",10,10,720,800);
	c1->cd(1);
	gStyle->SetPalette(kRainBow);
	//2d basket hits
	/*TH2* H2D = new TH2F("H2D", "2D Hits", 9,0,9, 10,0,10); 
	std::vector<ismran::ScintillatorBar_F *> basketscint;
	H2D->SetStats(0);
	ushort indxb;
	Double_t levels[501];
	for(int i=0;i<sizeof(levels)/sizeof(levels[0]);i++){
		levels[i]=i*0.1;
	}*/
	
	//Time difference
	TH1* hTime = new TH1D("hTime", "", 601, 0.0, 12);
	hTime->SetStats(0);
	hTime->SetLineColor(kGreen);
	ULong64_t prevBasketEndTime = 0;
	
	for (Long64_t i=0; i<nentries;i++) {
		if(i%1000000 == 0){std::cout<<"Analysing Basket "<<i<<" of "<<nentries<<std::endl;}
		nbytes += ftree->GetEntry(i);
		avBasketEnergy = (basket->GetBasketEnergy())/basket->size();
		if(basket->size() >= 5 and (avBasketEnergy >= 15.0 and avBasketEnergy <= 25.0)){
			muBasketTree->Fill();
			
			//For plotting Inter Basket Time
			if(muBasketTree->GetEntries()!=0){
				//std::cout<<muBasketTree->GetEntries()<<std::endl;
				hTime->Fill(log10(basket->GetBasketStartTime()-prevBasketEndTime));
				//std::cout<<prevBasketEndTime<<" "<<log10(basket->GetBasketStartTime()-prevBasketEndTime)<<std::endl;
				prevBasketEndTime = basket->GetBasketEndTime();
			}else{
				prevBasketEndTime = basket->GetBasketEndTime();
			}
			
			//For plotting Hits
			/*basketscint = basket->GetBasket();
			//std::cout<<"there are "<<basketscint.size()<<" bars in this basket"<<std::endl;
			for(int j=0;j<basketscint.size();j++){
				indxb = basketscint[j]->GetBarIndex();
				//std::cout<<indxb<<std::endl;
				H2D->Fill(indxb/10+0.5,indxb%10+0.5,basket->GetBasketBarEnergy(j));
			}
			H2D->GetXaxis()->SetTitle("X");
			H2D->GetYaxis()->SetTitle("Y");
			H2D->SetContour(sizeof(levels)/sizeof(levels[0]),levels);
			H2D->Draw("colz");
			c1->SaveAs(("../Plots/Basket"+std::to_string(i)+".jpg").c_str());*/
		}
		//clear to plot the next Hits
		//c1->Clear();
		//H2D->Reset();
	}
	
	gPad->SetLogy();
	hTime->GetXaxis()->SetTitle("log10(delT)");
    hTime->GetYaxis()->SetTitle("Counts");
    hTime->Draw("C");
    std::string fname = dataFileName.substr(dataFileName.find("Baskets"),dataFileName.length()-dataFileName.find("Baskets")-5);
    TFile myfile(("../../Data_Analysis_Results/InterBasketTimeSpectra_"+fname+".root").c_str(),"RECREATE");
	hTime->Write();
	myfile.Close();
	
	//write to file
	mubasketFile->cd();
    muBasketTree->Write();
    mubasketFile->Close();
	
	
	fApp->Run();
}
