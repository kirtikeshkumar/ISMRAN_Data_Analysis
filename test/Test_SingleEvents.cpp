/*
 * Kirtikesh Kumar
 * 2025-02-18
 * Code to generate baskets and remove baskets with events in veto layers.
 *
 * 		argv[1] is the path to claibration files
 * 		argv[2] is the filename to be checked
 * 		argv[3] is the Threshold in keV
 */
#include "Analyzer_F.h"
#include "Database.h"
#include "HardwareNomenclature.h"
#include "Helpers.h"
#include "Plotter.h"
#include "RtypesCore.h"
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
  double EThres = 100.0; // threshold energy for baskets in keV

  if (argv[3]) {
    std::sscanf(argv[3], "%lf", &EThres);
  }

  // Generating Calibration Instance
  ismran::Calibration Calib;
  Calib.instance(calibFilePath.string());

  // Reading and sorting events from file
  unsigned int numOfEvts = 0; // 10000000;
  ismran::Analyzer_F an(dataFileName, numOfEvts,
                        EThres); // read the events in file
  std::vector<ismran::ScintillatorBar_F *> fVecOfScint =
      an.GetVectorOfScintillators();
  ULong64_t scintVecSz = fVecOfScint.size();

  ////Generating plots
  TCanvas *c1 = new TCanvas("c1", "", 10, 5, 1900, 950);
  c1->Draw();
  c1->cd();
  gStyle->SetOptStat(0);
  gStyle->SetPalette(73);
  c1->cd();

  TH1 *hDelT = new TH1D("hDelT", "", 10000, 0.0, 100);
  hDelT->SetStats(0);
  hDelT->SetLineColor(kGreen);

  TH2 *hTimeEnergy = new TH2D("hTimeEnergy", "", 2501, -1, 2.5, 601, 0.0, 12);

  std::cout << "histograms created" << std::endl;
  std::cout << scintVecSz << std::endl;

  double preEvtTime = 0;
  double postEvtTime = 0;

  for (int i = 0; i < scintVecSz - 1; i++) {
    hDelT->Fill(fabs(fVecOfScint[i]->GetDelT()) / 1000);
    hTimeEnergy->Fill(log10(fVecOfScint[i]->GetQMeanCorrected() / 1000),
                      log10(fVecOfScint[i + 1]->GetTStampSmall() -
                            fVecOfScint[i]->GetTStampLarge()));
  }

  std::cout << "histogram hTime Filled" << std::endl;
  c1->Update();

  hTimeEnergy->DrawCopy("colz");
  std::string fname = dataFileName.substr(
      dataFileName.find("ISMRAN_digi"),
      dataFileName.length() - dataFileName.find("ISMRAN_digi") - 5);
  TFile f(("../../Data_Analysis_Outputs/"
           "hDelT_Scint_Threshold_" +
           std::to_string(static_cast<int>(EThres)) + "keV_" + fname + ".root")
              .c_str(),
          "RECREATE");
  hDelT->Write();
  f.Close();
  TFile myfile(("../../Data_Analysis_Outputs/"
                "PostEvent_NearestInterEventTimeEnergySpectra_Threshold_" +
                std::to_string(static_cast<int>(EThres)) + "keV_LogE_" + fname +
                ".root")
                   .c_str(),
               "RECREATE");
  hTimeEnergy->Write();
  myfile.Close();

  fApp->Run();
}