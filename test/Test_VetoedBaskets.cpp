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
	std::vector<ismran::SingleBasket *> vecOfBasketsPostVeto;	
	if(argv[3] and basketdT!=0){														//construct baskets
		vecOfBaskets = an.ReconstructBasket(basketdT);
	}else{vecOfBaskets = an.ReconstructBasket();}
	unsigned int basketVecSize = vecOfBaskets.size();
	std::cout<<"basketVecSize "<<basketVecSize<<std::endl;
	//if(argv[4]){vecOfBasketsPostVeto = an.ReconstructVetoedBasket(numVetoLayers,vecOfBaskets);}
	//unsigned int vetoedbasketVecSize = vecOfBasketsPostVeto.size();
	//std::cout<<"VetoedBasketVecSize "<<vetoedbasketVecSize<<std::endl;
	
	//Implementing veto functionality
	/*	if(argv[4]){
		std::vector<int> VetoBarsIndx = ismran::GetJacketBarIndx(numVetoLayers);
		ushort barindex;
		bool veto=false;
		int vetosz=0;
		std::vector<ismran::ScintillatorBar_F *> basketscint;
		for(int i=0; i<basketVecSize; i++){
			basketscint = vecOfBaskets[i]->GetBasket();
			for(int j=0; j<basketscint.size(); j++){
				barindex = basketscint[j]->GetBarIndex();
				veto=veto or ismran::IsJacket(barindex, VetoBarsIndx);
			}
			if(!veto){
				vecOfBasketsPostVeto.push_back(new ismran::SingleBasket(*vecOfBaskets[i]));
				basketscint.clear();
				vetosz+=1;
			}
		}
	}*/
	
	//Generating plots
	TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	c1->cd(1);
	gStyle->SetPalette(kRainBow);	
	
	/*
	// For 2d hits 
	TH2I* H2D = new TH2I("H2D", "2D Hits", 9,0,9, 10,0,10); 
	std::vector<ismran::ScintillatorBar_F *> basketscint;
	H2D->SetStats(0);
	//char* histsavename="../Plots/Basket"
	
	ushort indxb;
	Double_t levels[201];
	for(int i=0;i<sizeof(levels)/sizeof(levels[0]);i++){
		levels[i]=i*0.50;
	} 
	for(int i=0; i<vecOfBaskets.size(); i++){
		if(vecOfBaskets[i]->size()>=2){
			basketscint = vecOfBaskets[i]->GetBasket();
			for(int j=0;j<basketscint.size();j++){
				indxb = basketscint[j]->GetBarIndex();
				H2D->Fill(indxb/10+0.5,indxb%10+0.5,vecOfBaskets[i]->GetBasketEnergy());
			}
			//break;
			H2D->GetXaxis()->SetTitle("X");
			H2D->GetYaxis()->SetTitle("Y");
			H2D->SetContour(sizeof(levels)/sizeof(levels[0]),levels);
			//H2D->Draw("ARR");
			H2D->Draw("colz");		
			c1->SaveAs(("../Plots/Basket"+std::to_string(i)+".jpg").c_str());
		}
		c1->Clear();
		H2D->Reset();
	}
	*/
	
	// For energy Spectra
	/*TH1* HEUnVeto = new TH1D("HEUnVeto", "", 301, 0, 1000);
	HEUnVeto->SetLineColor(kGreen);
	TH1* HEVeto = new TH1D("HEVeto", "", 301, 0, 1000);
	HEVeto->SetLineColor(kRed);
	
	if(argv[4]){
		std::vector<int> VetoBarsIndx = ismran::GetJacketBarIndx(numVetoLayers);
		ushort barindex;
		bool veto=false;
		std::vector<ismran::ScintillatorBar_F *> basketscint;
		for(int i=0; i<basketVecSize; i++){
			HEUnVeto->Fill(vecOfBaskets[i]->GetBasketEnergy());
			basketscint = vecOfBaskets[i]->GetBasket();
			for(int j=0; j<basketscint.size(); j++){
				barindex = basketscint[j]->GetBarIndex();
				veto=ismran::IsJacket(barindex, VetoBarsIndx);
				if(veto){break;}
			}
			if(!veto){
				//vecOfBasketsPostVeto.push_back(new ismran::SingleBasket(*vecOfBaskets[i]));
				HEVeto->Fill(vecOfBaskets[i]->GetBasketEnergy());				
				basketscint.clear();
			}
			
		}
	}
	
	gPad->SetLogy();
	//gPad->SetLogx();   
   
    HEUnVeto->GetXaxis()->SetTitle("Energy(MeV)");
    HEUnVeto->GetYaxis()->SetTitle("Counts");
    HEUnVeto->Draw("C");
    HEVeto->Draw("SAME");
    TLegend *leg = new TLegend(0.6,0.7,0.75,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(HEUnVeto,"Total Energy Spectra","l");
    leg->AddEntry(HEVeto,"Vetoed Energy Spectra","l");
    leg->Draw();
    std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	
	c1->SaveAs(("./EnergySpectra_"+std::to_string(numVetoLayers)+"_VetoLayers"+fname+".root").c_str());
	fApp->Run();
	*/
	
	/*//For Time Difference
	TH1* hTime = new TH1D("hTime", "", 401, 4.0, 12.0);
	hTime->SetLineColor(kGreen);
	TH1* hTimeVeto = new TH1D("hTimeVeto", "", 401, 4.0, 12.0);
	hTimeVeto->SetLineColor(kRed);
	//std::cout<<"histograms created"<<std::endl;
	for(int i=0; i<basketVecSize-1; i++){
		hTime->Fill(log10(vecOfBaskets[i+1]->GetBasketStartTime()-vecOfBaskets[i]->GetBasketEndTime()));
	}
	//std::cout<<"histogram unveoed filled"<<std::endl;
	if(argv[4]){
		std::vector<int> VetoBarsIndx = ismran::GetJacketBarIndx(numVetoLayers);
		ushort barindex;
		bool veto=false;
		int vetosz=0;
		std::vector<ismran::ScintillatorBar_F *> basketscint;
		//std::cout<<"variables defined entering loops"<<std::endl;
		for(unsigned int i=0; i<basketVecSize; i++){
			//std::cout<<"retreiving basket "<<i<<std::endl;
			basketscint = vecOfBaskets[i]->GetBasket();
			//std::cout<<"retreived basket "<<i<<" with size "<<basketscint.size();
			for(unsigned int j=0; j<basketscint.size(); j++){
				barindex = basketscint[j]->GetBarIndex();
				veto = ismran::IsJacket(barindex, VetoBarsIndx);
				if(veto){break;}
			}
			//std::cout<<" and veto "<<veto<<std::endl;
			if(!veto){
				//std::cout<<"pushing into variable"<<std::endl;
				vecOfBasketsPostVeto.push_back(new ismran::SingleBasket(*vecOfBaskets[i]));
				vetosz+=1;
				basketscint.clear();
				if(vetosz>1){
					hTimeVeto->Fill(log10(vecOfBasketsPostVeto[vetosz-1]->GetBasketStartTime()-vecOfBasketsPostVeto[vetosz-2]->GetBasketEndTime()));
				}
			}
		}
		std::cout<<"Baskets after veto= "<<vetosz<<std::endl;
	}
	std::cout<<"Baskets after veto 12= "<<vecOfBasketsPostVeto.size()<<std::endl;
	gPad->SetLogy();
	hTime->GetXaxis()->SetTitle("log10(delT)");
    hTime->GetYaxis()->SetTitle("Counts");
    hTime->Draw("C");
    hTimeVeto->Draw("SAME");
    TLegend *leg = new TLegend(0.6,0.7,0.75,0.85);
    leg->SetBorderSize(0);
    leg->AddEntry(hTime,"Total TimeDiff Spectra","l");
    leg->AddEntry(hTimeVeto,"Vetoed TimeDiff Spectra","l");
    leg->Draw();
    fApp->Run();*/
}
	

