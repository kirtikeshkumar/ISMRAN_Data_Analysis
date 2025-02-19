/*
 * Kirtikesh Kumar
 * 2024-01-25
 * Code to generate baskets and remove baskets with events in veto layers.
 *
 * 		argv[1] is the path to claibration files
 * 		argv[2] is the filename to be checked
 * 		argv[3] is the max duration of single basket in ps
 * 		argv[4] is the Threshold in keV
 * 		argv[5] is number of veto layers
 */
#include "Analyzer_F.h"
#include "Database.h"
#include "HardwareNomenclature.h"
#include "Helpers.h"
#include "Plotter.h"
#include "ScintillatorBar_F.h"
#include "SingleBasket.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include <TApplication.h>
#include <TFile.h>
#include <TString.h>
#include <TStyle.h>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
  std::cout << "argc " << argc << std::endl;
  TApplication *fApp = new TApplication("TEST", NULL, NULL);

  // Defining all variables from input arguments
  std::string dataFileName = std::string(argv[2]);
  fs::path calibFilePath = std::string(argv[1]);
  ushort numVetoLayers = 0; // number of veto layers
  uint basketdT = 0;        // max duration of each basket.
                            // if basketdT = 0, baskets are made based on time
                            // difference between events
  double EThres = 100.0;    // threshold energy for baskets in keV

  if (argv[3]) {
    std::sscanf(argv[3], "%d", &basketdT);
  }
  if (argv[4]) {
    std::sscanf(argv[4], "%lf", &EThres);
  }
  if (argv[5]) {
    std::sscanf(argv[5], "%hd", &numVetoLayers);
  }

  // Generating Calibration Instance
  ismran::Calibration Calib;
  Calib.instance(calibFilePath.string());

  // Reading and sorting events from file
  unsigned int numOfEvts = 0; // 10000000;
  ismran::Analyzer_F an(dataFileName, numOfEvts,
                        EThres); // read the events in file
  std::vector<ismran::SingleBasket *> vecOfBaskets;
  std::vector<ismran::SingleBasket *> vecOfBasketsPostVeto;
  if (argv[3] and basketdT != 0) { // construct baskets
    vecOfBaskets = an.ReconstructBasket(basketdT);
  } else {
    vecOfBaskets = an.ReconstructBasket();
  }
  unsigned int basketVecSize = vecOfBaskets.size();
  std::cout << "basketVecSize " << basketVecSize << std::endl;

  if (argc == 6 and numVetoLayers != 0) {
    vecOfBasketsPostVeto =
        an.ReconstructVetoedBasket(numVetoLayers, vecOfBaskets);
  }
  unsigned int vetoedbasketVecSize = vecOfBasketsPostVeto.size();
  std::cout << "VetoedBasketVecSize " << vetoedbasketVecSize << std::endl;

  ////Generating plots
  TCanvas *c1 = new TCanvas("c1", "", 10, 5, 1900, 950);
  c1->Draw();
  c1->cd();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(73);
  c1->cd();

  //// For 2d hits with Pre and Post Event
  /*TH2 *H2DPre = new TH2F("H2DPre", "2D Hits", 9, 0, 9, 10, 0, 10);
  TH2 *H2DPost = new TH2F("H2DPost", "2D Hits", 9, 0, 9, 10, 0, 10);
  std::vector<ismran::ScintillatorBar_F *> basketscint;
  ushort indxb;
  Double_t levels[701];
  // std::cout << sizeof(levels) << " " << sizeof(levels[0]) << sizeof(levels) /
  // sizeof(levels[0]) << std::endl;
  for (int i = 0; i < sizeof(levels) / sizeof(levels[0]); i++) {
    levels[i] = i * 0.1;
  }
  float basketEnergy;
  int numBars;
  c1->cd();
  float logDelT;
  for (int i = 100000; i < basketVecSize - 1; i++) {
    logDelT = log10(vecOfBaskets[i + 1]->GetBasketStartTime() -
                    vecOfBaskets[i]->GetBasketEndTime());
    // if (logDelT > 5.3 and logDelT < 5.6 and
    // vecOfBaskets[i]->GetBasketEnergy() > 125) {
    if (fabs(log10(vecOfBaskets[i]->GetBasketEnergy()) - (-0.372)) < 0.012) {
      TPad *c1_1 = new TPad("c1_1", "PreEvt", 0.01, 0.01, 0.49, 0.99);
      TPad *c1_2 = new TPad("c1_2", "PostEvt", 0.51, 0.01, 0.99, 0.99);
      c1_1->Draw();
      c1_2->Draw();
      c1->Update();

      basketscint = vecOfBaskets[i]->GetBasket();

      c1_1->cd();

      for (int j = 0; j < basketscint.size(); j++) {
        indxb = basketscint[j]->GetBarIndex();
        H2DPre->Fill(indxb / 10 + 0.5, indxb % 10 + 0.5,
                     vecOfBaskets[i]->GetBasketBarEnergy(j));
      }

      basketEnergy = vecOfBaskets[i]->GetBasketEnergy();
      numBars = basketscint.size();
      H2DPre->SetTitle(Form("%d E: %.2f B: %d", i, basketEnergy, numBars));
      H2DPre->SetContour(sizeof(levels) / sizeof(levels[0]), levels);
      H2DPre->Draw("colz");

      basketscint = vecOfBaskets[i + 1]->GetBasket();

      c1_2->cd();

      for (int j = 0; j < basketscint.size(); j++) {
        indxb = basketscint[j]->GetBarIndex();
        H2DPost->Fill(indxb / 10 + 0.5, indxb % 10 + 0.5,
                      vecOfBaskets[i + 1]->GetBasketBarEnergy(j));
      }

      basketEnergy = vecOfBaskets[i + 1]->GetBasketEnergy();
      numBars = basketscint.size();
      H2DPost->SetTitle(Form("%d E: %.2f B: %d", i + 1, basketEnergy, numBars));
      H2DPost->SetContour(sizeof(levels) / sizeof(levels[0]), levels);
      H2DPost->Draw("colz");

      c1->Update();

      if (i > 500000) {
        break;
      }
      c1->SaveAs(("../Plots/CorrelatedEvents_420keV/Basket_PrePost_" +
                  std::to_string(i) + ".jpg")
                     .c_str());

      c1->Clear();
    }
    H2DPre->Reset();
    H2DPost->Reset();
  }
  fApp->Run();*/

  //// For 2d hits
  /*TH2 *H2D = new TH2F("H2D", "2D Hits", 9, 0, 9, 10, 0, 10);
  std::vector<ismran::ScintillatorBar_F *> basketscint;
  H2D->SetStats(0);
  // char* histsavename="../Plots/Basket"

  ushort indxb;
  Double_t levels[501];
  for (int i = 0; i < sizeof(levels) / sizeof(levels[0]); i++) {
    levels[i] = i * 0.1;
  }
  for (int i = 0; i < vecOfBaskets.size(); i++) {
    if (vecOfBaskets[i]->size() >= 2) {
      basketscint = vecOfBaskets[i]->GetBasket();
      for (int j = 0; j < basketscint.size(); j++) {
        indxb = basketscint[j]->GetBarIndex();
        H2D->Fill(indxb / 10 + 0.5, indxb % 10 + 0.5,
                  vecOfBaskets[i]->GetBasketBarEnergy(j));
      }
      // break;
      H2D->GetXaxis()->SetTitle("X");
      H2D->GetYaxis()->SetTitle("Y");
      H2D->SetContour(sizeof(levels) / sizeof(levels[0]), levels);
      // H2D->Draw("ARR");
      H2D->Draw("colz");
      // H2D->Draw("TEXT");
      c1->SaveAs(("../Plots/Basket" + std::to_string(i) + ".jpg").c_str());
    }
    c1->Clear();
    H2D->Reset();
  }*/

  //// For 3D Hits Density
  /*TH1 *hMult = new TH1I("hMult", "Multiplicity of 420 keV", 91, 0, 90);
  TH3 *H3Ddensity =
      new TH3I("H3Ddensity", "3D Hits", 9, 0, 9, 10, 0, 10, 101, -1, 1);
  std::vector<ismran::ScintillatorBar_F *> basketscint;
  H3Ddensity->SetStats(0);
  // char* histsavename="../Plots/Basket"

  ushort indxb;
  ushort count = 0;
  float QRatio;
  for (int i = 0; i < vecOfBaskets.size(); i++) {
    // if (vecOfBaskets[i]->size() >= 2) {
    basketscint = vecOfBaskets[i]->GetBasket();
    if (fabs(log10(vecOfBaskets[i]->GetBasketEnergy()) - (-1)) < 0.025) {
      // count += 1;
      hMult->Fill(basketscint.size());
      // std::cout << "muon" << std::endl;
      for (int j = 0; j < basketscint.size(); j++) {
        indxb = basketscint[j]->GetBarIndex();
        QRatio = (basketscint[j]->GetQMean() * 1.0) / basketscint[j]->GetQFar();
        // std::cout << QRatio << std::endl;
        // if (count == 3) { // if particular event to be plotted only
        H3Ddensity->Fill(indxb / 10 + 0.5, indxb % 10 + 0.5, log10(QRatio));
        // }
      }
      // if (count == 3) {
      //   break;
      // }
    }
  }
  H3Ddensity->GetXaxis()->SetTitle("X");
  H3Ddensity->GetYaxis()->SetTitle("Y");
  // H2D->Draw("ARR");
  H3Ddensity->Draw("colz");
  // H2D->Draw("TEXT");
  std::string fname = dataFileName.substr(
      dataFileName.find("ISMRAN_digi"),
      dataFileName.length() - dataFileName.find("ISMRAN_digi") - 5);
  TFile f(("../../Data_Analysis_Outputs/"
           "hMult_100keV_BasketSz_" +
           std::to_string(basketdT / 1000) + "ns_Threshold_" +
           std::to_string(static_cast<int>(EThres)) + "keV_" + fname + ".root")
              .c_str(),
          "RECREATE");
  hMult->Write();
  f.Close();
  // c1->SaveAs(("../../Data_Analysis_Outputs/"
  //             "Basket_Density_muon_3D_Canvas_" +
  //             std::to_string(basketdT / 1000) + "ns_Threshold_" +
  //             std::to_string(static_cast<int>(EThres)) + "keV_LogE_" + fname
  //             + "1.root")
  //                .c_str()); // VLE2_Linear
  TFile myfile(("../../Data_Analysis_Outputs/"
                "Basket_Density_100keV_3D_" +
                std::to_string(basketdT / 1000) + "ns_Threshold_" +
                std::to_string(static_cast<int>(EThres)) + "keV_LogE_" + fname +
                "1.root")
                   .c_str(),
               "RECREATE");
  H3Ddensity->Write();
  myfile.Close();
  // }
  c1->Clear();
  H3Ddensity->Reset();
  */

  //// For energy Spectra
  ///*TH1* HEUnVeto = new TH1D("HEUnVeto", "", 501, 0, 500);
  // HEUnVeto->SetLineColor(kGreen);
  // TH1* HEVeto = new TH1D("HEVeto", "", 501, 0, 500);
  // HEVeto->SetLineColor(kRed);
  // unsigned int vetobasketcounter=0;
  // ULong64_t delTBaskets;
  // for(int i=0; i<basketVecSize-1; i++){
  ////delTBaskets =
  /// vecOfBaskets[i+1]->GetBasketStartTime()-vecOfBaskets[i]->GetBasketEndTime();
  ////if(log10(delTBaskets)>=5.2 and log10(delTBaskets)<=6.6){
  // HEUnVeto->Fill(vecOfBaskets[i]->GetBasketEnergy());
  ////}
  ////if(log10(delTBaskets)>=2.5 and log10(delTBaskets)<=5.0){
  ////	HEVeto->Fill(vecOfBaskets[i+1]->GetBasketEnergy());
  ////}
  //}

  ////for(int i=0; i<vetoedbasketVecSize-1; i++){
  ////	delTBaskets =
  /// vecOfBasketsPostVeto[i+1]->GetBasketStartTime()-vecOfBasketsPostVeto[i]->GetBasketEndTime();
  ////	if(log10(delTBaskets)>=2.5 and log10(delTBaskets)<=5.0){
  //// HEVeto->Fill(vecOfBasketsPostVeto[i]->GetBasketEnergy()); /	}
  ////HEVeto->Fill(vecOfBasketsPostVeto[i]->GetBasketEnergy());
  ////}

  // gPad->SetLogy();
  ////gPad->SetLogx();

  // HEUnVeto->GetXaxis()->SetTitle("Energy(MeV)");
  // HEUnVeto->GetYaxis()->SetTitle("Counts");
  // HEUnVeto->Draw("C");
  // HEVeto->Draw("LSAME");
  // TLegend *leg = new TLegend(0.6,0.7,0.75,0.85);
  // leg->SetBorderSize(0);
  // leg->AddEntry(HEUnVeto,"Total Energy Spectra","l");
  // leg->AddEntry(HEVeto,"Vetoed Energy Spectra","l");
  // leg->Draw();
  // std::string fname =
  // dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
  // c1->SaveAs(("../../Data_Analysis_Outputs/Canvas_EnergySpectra_"+std::to_string(numVetoLayers)+"_VetoLayers_"+std::to_string(basketdT/1000)+"ns_Basket_Threshold_"+std::to_string(static_cast<int>(EThres))+"keV_"+fname+"1.root").c_str());
  // TFile
  // myfile(("../../Data_Analysis_Outputs/EnergySpectra_"+std::to_string(numVetoLayers)+"_VetoLayers_"+std::to_string(basketdT/1000)+"ns_Basket_Threshold_"+std::to_string(static_cast<int>(EThres))+"keV_"+fname+"1.root").c_str(),"RECREATE");
  // HEUnVeto->Write();
  ////HEVeto->Write();
  // myfile.Close();
  ////c1->SaveAs(("../../Data_Analysis_Outputs/EnergySpectra_"+std::to_string(numVetoLayers)+"_VetoLayers"+fname+".root").c_str());
  // fApp->Run();*/

  ////For Time Difference
  c1->cd();
  TH1 *hTime = new TH1D("hTime", "", 601, 0.0, 12);
  hTime->SetStats(0);
  hTime->SetLineColor(kGreen);

  TH1 *hTimeVeto = new TH1D("hTimeVeto", "", 601, 0.0, 12);
  hTimeVeto->SetStats(0);
  hTimeVeto->SetLineColor(kRed);

  TH2 *hTimeEnergy = new TH2D("hTimeEnergy", "", 2501, -1, 2.5, 601, 0.0, 12);
  // TH2* hEnergyMult = new TH2D("hEnergyMult", "", 2501, 0, 2.5, 101, 0.0,
  // 100);

  std::cout << "histograms created" << std::endl;
  std::cout << vecOfBaskets.size() << std::endl;

  double preEvtTime = 0;
  double postEvtTime = 0;

  for (int i = 0; i < basketVecSize - 2; i++) {
    // if(vecOfBaskets[i+1]->GetBasketEnergy()<10.0 and
    // vecOfBaskets[i]->GetBasketEnergy()<10.0){
    //
    // hTime->Fill(log10(vecOfBaskets[i + 1]->GetBasketStartTime() -
    // vecOfBaskets[i]->GetBasketEndTime()));
    if (fabs(log10(vecOfBaskets[i]->GetBasketEnergy()) - (-0.372)) < 0.012) {
      // fill hTime for particular energy range events i.e both pre and post
      // events in same energy range
      preEvtTime = postEvtTime;
      postEvtTime = vecOfBaskets[i]->GetBasketStartTime();
      hTime->Fill(log10(postEvtTime - preEvtTime));
    }
    if (argc < 6 or numVetoLayers == 0) {
      hTimeEnergy->Fill(log10(vecOfBaskets[i + 2]->GetBasketEnergy()),
                        log10(vecOfBaskets[i + 2]->GetBasketStartTime() -
                              vecOfBaskets[i]->GetBasketEndTime()));
      //   //if (fabs(log10(vecOfBaskets[i]->GetBasketEnergy()) - (-0.372)) <
      //   0.12)
      //   //{
      //   //  hEnergyMult->Fill((vecOfBaskets[i]->GetBasketEnergy()),
      //   //                    (vecOfBaskets[i]->size()));
      //   //}
    }
    //}
  }

  std::cout << "histogram hTime Filled" << std::endl;
  if (argc == 6 and numVetoLayers != 0) {
    for (int i = 0; i < vetoedbasketVecSize - 1; i++) {
      //
      hTimeVeto->Fill(log10(vecOfBasketsPostVeto[i + 1]->GetBasketStartTime() -
                            vecOfBasketsPostVeto[i]->GetBasketEndTime()));
      hTimeEnergy->Fill(
          log10(vecOfBasketsPostVeto[i + 1]->GetBasketEnergy()),
          log10(vecOfBasketsPostVeto[i + 1]->GetBasketStartTime() -
                vecOfBasketsPostVeto[i]->GetBasketEndTime()));
    }
    std::cout << "histogram hTimeVeto Filled" << std::endl;
  }
  //
  // gPad->SetLogy();
  // hTime->GetXaxis()->SetTitle("log10(delT)");
  // hTime->GetYaxis()->SetTitle("Counts");
  // hTime->Draw("C");
  // hTimeVeto->Draw("SAME");
  // TLegend *leg = new TLegend(0.6,0.7,0.75,0.85);
  // leg->SetBorderSize(0);
  // leg->AddEntry(hTime,"Total TimeDiff Spectra","l");
  // leg->AddEntry(hTimeVeto,"Vetoed TimeDiff Spectra","l");
  // leg->Draw();
  // std::string fname = dataFileName.substr(
  //     dataFileName.find("ISMRAN_digi"),
  //     dataFileName.length() - dataFileName.find("ISMRAN_digi") - 5);
  // //
  // c1->SaveAs(("../../Data_Analysis_Outputs/Canvas_InterBasketTimeSpectra_" +
  //             std::to_string(basketdT / 1000) + "ns_Threshold_" +
  //             std::to_string(static_cast<int>(EThres)) + "keV_" + fname +
  //             "1.root")
  //                .c_str());
  // TFile myfile(("../../Data_Analysis_Outputs/InterBasketTimeSpectra_" +
  //               std::to_string(basketdT / 1000) + "ns_Threshold_" +
  //               std::to_string(static_cast<int>(EThres)) + "keV_" + fname +
  //               "1.root")
  //                  .c_str(),
  //              "RECREATE");
  // hTime->Write();
  // myfile.Close();

  // hTimeEnergy->Smooth();
  hTimeEnergy->DrawCopy("colz");
  std::string fname = dataFileName.substr(
      dataFileName.find("ISMRAN_digi"),
      dataFileName.length() - dataFileName.find("ISMRAN_digi") - 5);
  TFile f(("../../Data_Analysis_Outputs/"
           "hTime_BasketSz_" +
           std::to_string(basketdT / 1000) + "ns_Threshold_" +
           std::to_string(static_cast<int>(EThres)) + "keV_" + fname + ".root")
              .c_str(),
          "RECREATE");
  hTime->Write();
  f.Close();
  if (argc < 6 or numVetoLayers == 0) {
    // c1->SaveAs(("../../Data_Analysis_Outputs/"
    //             "PreEvent_InterBasketTimeEnergySpectra_Canvas_" +
    //             std::to_string(basketdT / 1000) + "ns_Threshold_" +
    //             std::to_string(static_cast<int>(EThres)) + "keV_LogE_" +
    //             fname + "1.root")
    //                .c_str()); // VLE2_Linear TFile
    TFile myfile(("../../Data_Analysis_Outputs/"
                  "PostEvent_nextNearestInterBasketTimeEnergySpectra_" +
                  std::to_string(basketdT / 1000) + "ns_Threshold_" +
                  std::to_string(static_cast<int>(EThres)) + "keV_LogE_" +
                  fname + "1.root")
                     .c_str(),
                 "RECREATE");
    hTimeEnergy->Write();
    myfile.Close();
  }
  // else if (argc == 6 and numVetoLayers != 0) {
  //   c1->SaveAs(("../../Data_Analysis_Outputs/"
  //               "InterBasketTimeEnergySpectra_VetoLayers_Canvas_" +
  //               std::to_string(basketdT / 1000) + "ns_Threshold_" +
  //               std::to_string(static_cast<int>(EThres)) + "keV_" +
  //               std::to_string(numVetoLayers) + "_VetoLayers_VLE2_Linear_" +
  //               fname + "1.root")
  //                  .c_str());
  //   TFile myfile(("../../Data_Analysis_Outputs/"
  //                 "InterBasketTimeEnergySpectra_VetoLayers_" +
  //                 std::to_string(basketdT / 1000) + "ns_Threshold_" +
  //                 std::to_string(static_cast<int>(EThres)) + "keV_" +
  //                 std::to_string(numVetoLayers) + "_VetoLayers_VLE2_Linear_"
  //                 + fname + "1.root")
  //                    .c_str(),
  //                "RECREATE");
  //   hTimeEnergy->Write();
  //   myfile.Close();
  // }

  ///*hEnergyMult->DrawCopy("colz");
  // std::string fname =
  // dataFileName.substr(dataFileName.find("ISMRAN_digi"),dataFileName.length()-dataFileName.find("ISMRAN_digi")-5);
  // c1->SaveAs(("../../Data_Analysis_Outputs/InterBasketEnergyMultSpectra_Canvas_"+std::to_string(basketdT/1000)+"ns_Threshold_"+std::to_string(static_cast<int>(EThres))+"keV_VLE3_Linear_"+fname+"1.root").c_str());
  // TFile
  // myfile(("../../Data_Analysis_Outputs/InterBasketEnergyMultSpectra_"+std::to_string(basketdT/1000)+"ns_Threshold_"+std::to_string(static_cast<int>(EThres))+"keV_VLE3_Linear_"+fname+"1.root").c_str(),"RECREATE");
  // hEnergyMult->Write();
  // myfile.Close();*/
  // fApp->Run();

  ////For Basket Duration
  ///*TH1* BDelt = new TH1D("BDelt", "", 51, 0, 50);
  // BDelt->SetLineColor(kGreen);
  // for(int i=0; i<basketVecSize-1; i++){
  // BDelt->Fill(vecOfBaskets[i]->GetBasketDuration()/1000);//vecOfBaskets[i]->size());
  //}
  // BDelt->GetXaxis()->SetTitle("Basket Duration (ns)");
  // BDelt->GetYaxis()->SetTitle("Counts");
  // BDelt->Draw("C");
  fApp->Run();
}
