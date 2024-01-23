/*
 * Calibration.cpp
 *
 *  Created on: 21-Aug-2020
 *      Author: rsehgal
 */

#include "Calibration.h"
#include "TFile.h"
#include "PsBar.h"
#include "includes.hh"
#include "HardwareNomenclature.h"
#include <TH1D.h>
#include "colors.h"
#include <TString.h>
namespace ismran {

Calibration *Calibration::s_instance = 0;

Calibration::Calibration()
{
  // TODO Auto-generated constructor stub
}

Calibration::~Calibration()
{
  // TODO Auto-generated destructor stub
}

Calibration *Calibration::instance(std::string filename)
{
  if (!s_instance) s_instance = new Calibration(filename);
  return s_instance;
}

Calibration *Calibration::instance()
{
  if (s_instance)
    return s_instance;
  else {
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@ Instance of Calibration class does not exist in Memory, please create it first....@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
  }
  return s_instance;
}

Calibration::Calibration(std::string fileName)
{
  fFileName = fileName;
  std::string BarName;
  std::string calibFileName;
  unsigned int numOfBars = vecOfPsBars.size(); // vecOfBarsName.size();
  /* For the case of combined calibration file
  for (unsigned int barIndex = 0; barIndex < numOfBars; barIndex++) {

    TF1 *delTShift_F = (TF1 *)fp->Get(Form("fdelt_shift_Cs137_%s_0cm", vecOfPsBars[barIndex].c_str()));
    TF1 *paramertization_F = (TF1 *)fp->Get(Form("fzparam_%s", vecOfPsBars[barIndex].c_str()));
    TF1 *enerCalibFormula = (TF1 *)fp->Get(Form("%s_Energy_F", vecOfPsBars[barIndex].c_str()));

    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "Processing Bar : " << vecOfPsBars[barIndex] << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

    fVecOfCalibrationData.push_back(new CalibrationData(delTShift_F, paramertization_F, enerCalibFormula)); 
  }*/
  
  //for the case of individual bar calibration files
  for (unsigned int barIndex = 0; barIndex < numOfBars; barIndex++){
	  BarName = ismran::vecOfPsBars[barIndex];
	  calibFileName = Form("calibration_%s.root", BarName.c_str());
	  TFile *fp = new TFile((fileName+calibFileName).c_str(), "r");
	  std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
      std::cout << "Processing Bar : " << BarName << std::endl;
      std::cout << "calib file: "<<fileName+calibFileName<<std::endl;
      std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
	  TF1 *delTShift_F;													//to complete
	  TF1 *paramertization_F;											//to complete
	  TF1 *enerCalibFormula = (TF1 *)fp->Get(Form("%s_ECalib", BarName.c_str()));
	  fVecOfCalibrationData.push_back(new CalibrationData(delTShift_F, paramertization_F, enerCalibFormula)); 
	  fp->Close();
  }
}

CalibrationData *Calibration::GetCalibrationDataOf(int barNo)
{
  // std::cout <<" @@@@@@2 BAR NO : " << barNo << std::endl;
  return fVecOfCalibrationData[barNo];
}

} // namespace ismran
