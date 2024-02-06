/*
**	Filename : SingleAnimal.cpp
**	2024-02-06
**	username : Kirtikesh Kumar
**  Store all events in one animal as a vector
*/

#ifndef SingleAnimal_h
#define SingleAnimal_h

#include <memory>
#include <vector>
#pragma once
#include <TROOT.h>
#include "ScintillatorBar_F.h"
#include <iterator>
#include "PsBar.h"
#include "HardwareNomenclature.h"
#include "Plotter.h"
#include <algorithm>
#include "colors.h"

namespace ismran {

class ScintillatorBar_F;

class SingleAnimal {
private:
  std::vector<ScintillatorBar_F*> fVecOfScintillators;
  Double_t AnimalEnergy;
public:
  /*
   * Various constructors
   */
  SingleAnimal();
  SingleAnimal(std::vector<ScintillatorBar_F*> vecOfScintBars);
  SingleAnimal(const SingleAnimal &smt);

  /*
   * Function similar to std::vector
   */
  void push_back(ScintillatorBar_F *hittedBar);
  void push_back(std::vector<ScintillatorBar_F *> vecOfScint);
  void clear();
  unsigned long int size();

  /*
   * Required Getters
   */
  std::vector<ScintillatorBar_F*> GetAnimal() const;
  ULong64_t GetAnimalEventTime(int EvtIndx);
  ULong64_t GetAnimalStartTime();
  ULong64_t GetAnimalEndTime();
  ULong64_t GetAnimalDuration();
  Double_t GetAnimalEnergy();
  void SetAnimalEnergy();
  bool isBarInAnimal(ushort barIndx);
  /*
   * Print functions
   */
  void Print();

  ~SingleAnimal();

  ClassDef(SingleAnimal, 1)
};

} // namespace ismran

#endif
