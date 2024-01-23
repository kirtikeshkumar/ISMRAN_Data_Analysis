/*
**	Filename : Test_GenerateCalibrationFile.cpp
**	2023-10-19
**	username : rsehgal
*/
#include <string>
#include <iostream>
#include <filesystem>
#include <regex>
#include "Helpers.h"
#include "CharacterizationFileReader.h"
#include <TApplication.h>
#include <algorithm>
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
  TApplication *fApp           = new TApplication("Tapp", NULL, NULL);
  
  /*std::vector<std::string> sequentialBarNames = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520",  "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS55_S1AA6646", "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS64_S3AA1787", "PS65_S3AA1782", "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890",    "PS84_SF882",
    "PS85_SF881",    "PS86_SF884",    "PS87_SF876",    "PS88_SF880",    "PS89_SF873",    "PS90_SF875"};
    
  for(int xsrt = 72; xsrt<90; xsrt++){*/
	  //std::string calibBarName	   = sequentialBarNames[xsrt];
	  std::string calibBarName	   = std::string(argv[2]);
	  fs::path directoryPath       = std::string(argv[1])+"/"+calibBarName;
      TFile *fout                  = new TFile(Form("calibration_%s.root", calibBarName.c_str()), "RECREATE");
  
	  std::cout<<"Path: "<<directoryPath<<std::endl;
	  std::cout<<"output: "<<Form("calibration_%s.root", calibBarName.c_str())<<std::endl;
	  int correctionFactor         = 0;
	  short counter                = 0;
	  TCanvas *can                 = new TCanvas("Calibration", "Calibraion");
	  TSpectrum *spectrum          = new TSpectrum(1);
	  std::vector<float> energyVec = {477., 1062., 4201.};
	  std::vector<float> peakPosVec;
	  std::vector<std::string> sourceVec = GetEnergyCalibrationFiles();
	  std::string barName                = directoryPath.string();
	  barName                            = barName.substr(barName.rfind('/') + 1);
	
	  std::cout << "BarName : " << barName << std::endl;
	
	  // return 0;
	
	  {
	    for (unsigned short i = 0; i < sourceVec.size(); i++) {
	      // for (unsigned short i = 0; i < 1; i++) {
	
	      std::regex b(sourceVec[i]);
	
	      // Iterate through the directory entries
	      // TFile *fw = new TFile("output.root","w");
	      for (const auto &entry : fs::directory_iterator(directoryPath)) {
	        // Convert the directory entry to a string
	        std::string entryString = entry.path().string();
	
	        if (regex_match(entryString, b)) {
	          counter++;
	          std::cout << "FOUND : " << entryString << std::endl;
	
	          // TFile *fp = new TFile(entryString.c_str(),"r");
	          CharacterizationFileReader *cf = new CharacterizationFileReader(entryString);
	          // barName = cf->GetBarName();
	          TH1F *qmeanHist = cf->GetComptonEdge();
	          if (entryString.find("Cs137") != std::string::npos) qmeanHist->SetTitle("Cs137");
	          if (entryString.find("Co60") != std::string::npos) qmeanHist->SetTitle("Co60");
	          if (entryString.find("Na22") != std::string::npos) qmeanHist->SetTitle("Na22");
	          if (entryString.find("AmBe") != std::string::npos) qmeanHist->SetTitle("AmBe");
	
	          spectrum->Search(qmeanHist, 2);
	          Double_t *xpeaks = spectrum->GetPositionX();
	          peakPosVec.push_back(xpeaks[0]);
	          // new TCanvas;
	          qmeanHist->SetLineColor(counter);
	          fout->cd();
	          qmeanHist->Write();
	
	          /*if(counter==1)
	          qmeanHist->Draw();
	          else
	          qmeanHist->Draw("same");
	
	          gPad->SetLogy();*/
	        }
	      }
	    }
	  }
	  // can->BuildLegend();
	  // fApp->Run();
	
	  for (unsigned int i = 0; i < peakPosVec.size(); i++) {
	    std::cout << peakPosVec[i] << " : ";
	  }
	
	  TGraph *grE = new TGraph(peakPosVec.size(), &peakPosVec[0], &energyVec[0]);
	  grE->SetMarkerStyle(8);
	  // std::string barName= "PS5";//""cf->GetBarName();
	  //TF1 *comptonFit = new TF1((barName + "_ECalib").c_str(), "pol1", 250, 2250);
	  TF1 *comptonFit = new TF1((barName + "_ECalib").c_str(), "pol1", 0, 22500);
	  grE->Fit(comptonFit, "q");
	  comptonFit->Write();
	  grE->Draw("ap");
	  grE->Write();
	  // fout->Close();
	  std::cout << std::endl;
	  // return 0;
	
	  {
	    std::string delTOffsetFile = GetDelTOffsetFile();
	
	    std::regex b(delTOffsetFile);
	
	    // Iterate through the directory entries
	    // TFile *fw = new TFile("output.root","w");
	    for (const auto &entry : fs::directory_iterator(directoryPath)) {
	      // Convert the directory entry to a string
	      std::string entryString = entry.path().string();
	
	      if (regex_match(entryString, b)) {
	        std::cout << "================== DELT OFFSET FILE ====================" << std::endl;
	        std::cout << "FOUND : " << entryString << std::endl;
	        CharacterizationFileReader *cf = new CharacterizationFileReader(entryString);
	        std::cout << "BarName : " << cf->GetBarName() << std::endl;
	        std::cout << "Source Pos : " << cf->GetActualPosition() << std::endl;
	        std::cout << "Total Num of Events : " << cf->GetTotalNumOfEvents() << std::endl;
	
	        TF1 *delTOffsetFormula = cf->GetDelTOffsetFormula();
	        // delTOffsetFormula->Draw();
	        // cf->GetOutputFile()->cd();
	        fout->cd();
	        delTOffsetFormula->Write();
	        correctionFactor = delTOffsetFormula->GetParameter(1);
	        delete cf;
	
	        // TFile *fp = new TFile(entryString.c_str(),"r");
	      }
	    }
	  }
	
	  std::cout << "======================== STARTING PARAMETERIZATIOn ==========================" << std::endl;
	  std::vector<float> posVec;
	  std::vector<float> meanVec;
	  {
	    std::vector<std::string> sourceVec = GetPositionCalibrationFiles();
	
	    for (unsigned short i = 0; i < sourceVec.size(); i++) {
	      // for (unsigned short i = 4; i < 5; i++) {
	
	      std::regex b(sourceVec[i]);
	
	      // Iterate through the directory entries
	      // TFile *fw = new TFile("output.root","w");
	      for (const auto &entry : fs::directory_iterator(directoryPath)) {
	        // Convert the directory entry to a string
	        std::string entryString = entry.path().string();
	
	        if (regex_match(entryString, b)) {
	          std::cout << "===============================================" << std::endl;
	          std::cout << "FOUND : " << entryString << std::endl;
	          CharacterizationFileReader *cf = new CharacterizationFileReader(entryString, correctionFactor);
	          std::cout << "Delt Offset factor : " << cf->GetDelTOffsetCorrection() << std::endl;
	          // std::cout << "BarName : " << cf->GetBarName() << std::endl;
	          // std::cout << "Source Pos : " << cf->GetActualPosition() << std::endl;
	          // std::cout << "Total Num of Events : " << cf->GetTotalNumOfEvents() << std::endl;
	          TF1 *delTOffsetFormula = cf->GetDelTOffsetFormula();
	          std::cout << "Mean after offset correction : " << delTOffsetFormula->GetParameter(1) << std::endl;
	          posVec.push_back(cf->GetActualPosition());
	          meanVec.push_back(delTOffsetFormula->GetParameter(1));
	          delete cf;
	
	          // TFile *fp = new TFile(entryString.c_str(),"r");
	        }
	      }
	    }
	  }
	
	  TGraph *gr = new TGraph(posVec.size(), &meanVec[0], &posVec[0]);
	  gr->SetTitle((barName + "_z").c_str());
	  gr->SetName((barName + "_z").c_str());
	  gr->SetMarkerStyle(8);
	  
	  auto grmin = *(std::min_element(meanVec.begin(), meanVec.end()));
	  auto grmax = *(std::max_element(meanVec.begin(), meanVec.end()));
	
	  
	  TF1 *zdelt = new TF1((barName + "_ZCalib").c_str(), "pol2", grmin,grmax);
	  gr->Fit(zdelt, "r");
	  // gr->Draw("ap");
	  fout->cd();
	  gr->Write();
	  zdelt->Write();
	
	  fout->Close();
	  // fApp->Run();
  //}
  return 0;
}
