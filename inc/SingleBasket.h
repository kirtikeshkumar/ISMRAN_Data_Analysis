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
  Double_t BasketEnergy;
  ushort COMIndex;
  ULong64_t meanT;
  Double_t sigX;
  Double_t sigY;
  uint sigT;
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
  void push_back(std::vector<ScintillatorBar_F *> vecOfScint);
  void clear();
  unsigned long int size();

  /*
   * Required Getters
   */
  std::vector<ScintillatorBar_F*> GetBasket() const;
  ULong64_t GetBasketEventTime(int EvtIndx);
  ULong64_t GetBasketStartTime();
  ULong64_t GetBasketEndTime();
  ULong64_t GetBasketDuration();
  ULong64_t GetBasketMeanTime();
  uint GetBasketStdDevT();
  Double_t GetBasketStdDevX();
  Double_t GetBasketStdDevY();
  ushort GetBasketCOMBar();
  Double_t GetBasketEnergy();
  Double_t GetBasketBarEnergy(int evtIndx);
  bool isBarInBasket(ushort barIndx);
  /*
   * Print functions
   */
  void Print();
  /*
   * Setters
   */
   void SetBasketEnergy();
   void SetBasketEnergy(Double_t E);
   void SetBasketParameters();
   void Initialiser();

  ~SingleBasket();

  ClassDef(SingleBasket, 1)
};

} // namespace ismran

#endif
