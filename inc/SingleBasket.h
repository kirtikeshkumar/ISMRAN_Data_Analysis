/*
**	Filename : SingleBasket.cpp
**	2023-10-17
**	username : Kirtikesh Kumar
**  Store all events in one basket as a vector
*/

#ifndef SingleBasket_h
#define SingleBasket_h

#include <memory>
#include <vector>
#pragma once
#include <TROOT.h>

namespace ismran {

class ScintillatorBar_F;

class SingleBasket {
private:
  std::vector<ScintillatorBar_F*> fVecOfScintillators;
  
public:
  /*
   * Various constructors
   */
  SingleBasket();
  SingleBasket(std::vector<ScintillatorBar_F*> vecOfScintBars);
  SingleBasket(const SingleBasket &smt);

  /*
   * Function similar to std::vector
   */
  void push_back(ScintillatorBar_F *hittedBar);
  void clear();
  unsigned long int size();

  /*
   * Required Getters
   */
  std::vector<ScintillatorBar_F*> GetBasket() const;
  ULong64_t GetBasketEventTime(int EvtIndx);
  ULong64_t GetBasketStartTime();
  ULong64_t GetBasketEndTime();

  /*
   * Print functions
   */
  void Print();

  ~SingleBasket();

  ClassDef(SingleBasket, 1)
};

} // namespace ismran

#endif
