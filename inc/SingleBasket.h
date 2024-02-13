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
#include <TMath.h>
#include <algorithm>  
#include <numeric>    
#include <cmath>

namespace ismran {

class ScintillatorBar_F;

class SingleBasket {
private:
  std::vector<ScintillatorBar_F*> fVecOfScintillators;
  Double_t BasketEnergy;
  ushort COMIndex;	//Index of Center Of Mass bar
  ULong64_t meanT;	//Average time of basket
  Double_t sigX;	//Stdev of basket spread in x direction
  Double_t sigY;	//Stdev of basket spread in y direction
  uint sigT;		//Stdev of basket spread in time
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
  uint size();

  /*
   * Required Getters
   */
  std::vector<ScintillatorBar_F*> GetBasket() const;
  ScintillatorBar_F* GetEvent(int EvtIndx);
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
   void SetBasketMeanTime();
   void SetBasketStdDevT();
   //void SetBasketMeanTime(ULong64_t val);
   //void SetBasketStdDevT(uint val);
   void Initialiser();

  ~SingleBasket();

  ClassDef(SingleBasket, 1)
};

} // namespace ismran

#endif
