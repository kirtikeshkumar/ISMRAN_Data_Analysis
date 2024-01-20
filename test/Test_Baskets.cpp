/*
 * Kirtikesh Kumar
 * 2023-10-11
 * Code to plot number of baskets in a fixed time.
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
int main(int argc, char *argv[]){
	std::cout<<"argc "<<argc<<std::endl;
	TApplication *fApp       = new TApplication("TEST", NULL, NULL);
	std::string dataFileName    = std::string(argv[1]);
	
	unsigned int numOfEvts	= 0;	
	ULong64_t fTStep 		= 1;											//step size to check number of baskets in ms
	ULong64_t fTStart		= 0;											//start time of first basket
	ULong64_t fTBStart		= 0;											//start time of basket
	unsigned int counter	= 0;											//counter for number of baskets in given time
	unsigned int flagvar	= 0;
	unsigned int prevflagvar= 0;
	
	if(argv[2]){std::sscanf(argv[2], "%lld", &fTStep); }
	std::cout<<"Time window: "<<fTStep<<"ms"<<std::endl;
	
	ismran::Analyzer_F an(dataFileName, numOfEvts);											//read the events in file
	std::vector<ismran::SingleBasket *> vecOfBaskets = an.ReconstructBasket(); 				//adds all Baskets into a vector
	unsigned int basketVecSize = vecOfBaskets.size();
	std::cout<<"basketVecSize "<<basketVecSize<<std::endl;
	fTStart		= vecOfBaskets[0]->GetBasketStartTime();
	
	//std::cout<<fTStart<<"	"<<vecOfBaskets[0]->GetBasketStartTime()<<"	"<<vecOfBaskets[0]->GetBasketEndTime()<<std::endl;
	//std::cout<<vecOfBaskets[1]->GetBasketStartTime()-fTStart<<"	"<<vecOfBaskets[1]->GetBasketStartTime()<<"	"<<vecOfBaskets[1]->GetBasketEndTime()<<std::endl;
	
	TCanvas *c1 = new TCanvas("c1","",20,10,800,600);
	c1->cd(1);
	TH1* HNumBasket  = new TH1I("HNumBasket", "", 301, 0, 300);				//Histrogram of number of baskets in fTStep
	HNumBasket->SetLineColor(kRed);
		
	for (unsigned int i = 0; i < basketVecSize; i++){
		fTBStart = vecOfBaskets[i]->GetBasketStartTime();
		flagvar = int64_t(ceil(fTBStart-fTStart))/int64_t(fTStep*1E9);		//division of ints only gives the quotient
		//std::cout<<fTBStart-fTStart<<"	"<<flagvar<<"	"<<prevflagvar<<std::endl;
		if(flagvar==prevflagvar){counter++;}								//if within the same fTStep window, increase counter
		else{																//10ms window changed
			//std::cout<< "numofbaskets = "<<counter<<std::endl;
			if(flagvar-prevflagvar==1){HNumBasket->Fill(counter);}			//fill the histogram with number of baskets
			else{HNumBasket->Fill(0.1,(flagvar-prevflagvar-1));}			//some 10ms windows were empty, fill histogram with 0's
			prevflagvar=flagvar;												
			counter=1;														//since the new basket has been read, reset the counter to 1
		}
	}
	
	//if(counter!=0){HNumBasket->Fill(counter);}
	gPad->SetLogy();
    //gPad->SetLogx();
    HNumBasket->GetXaxis()->SetTitle("Num Of Baskets");
    HNumBasket->GetYaxis()->SetTitle("Counts");
    //HNumBasket->GetYaxis()->SetRangeUser(1,1E9);
    //HNumBasket->GetXaxis()->SetLimits(0,10.0);
    HNumBasket->Draw("C");
    //TLegend *leg = new TLegend(0.5,0.6,0.8,0.8);
    //leg->SetBorderSize(0);
    //leg->AddEntry(HNumBasket,"NumBasket","l");
    //leg->Draw();
	std::string fname = dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
	c1->SaveAs(("./NumBasket_"+std::to_string(fTStep)+"ms_"+fname+".root").c_str());
	c1->SaveAs(("./NumBasket_"+std::to_string(fTStep)+"ms_"+fname+".pdf").c_str());
	//fApp->Run();
	
}
