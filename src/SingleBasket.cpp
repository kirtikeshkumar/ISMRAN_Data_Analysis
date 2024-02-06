/*
**	Filename : SingleBasket.cpp
**	2023-10-17
**	username : Kirtikesh Kumar
**  Store all events in one basket as a vector
*/

#include "SingleBasket.h"
#include "ScintillatorBar_F.h"
#include <iterator>
#include "PsBar.h"
#include "HardwareNomenclature.h"
#include "Plotter.h"
#include <algorithm>
#include "colors.h"

ClassImp(ismran::SingleBasket)

namespace ismran
{

  SingleBasket::SingleBasket() {BasketEnergy=0.0;}

  SingleBasket::~SingleBasket() {}

  
  SingleBasket::SingleBasket(std::vector<ScintillatorBar_F *> vecOfScintBars)
  {
	BasketEnergy = 0.0;
    fVecOfScintillators = vecOfScintBars;
    for(int i=0; i < fVecOfScintillators.size(); i++){
		BasketEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
	}
  }

  SingleBasket::SingleBasket(const SingleBasket &sb)
  {
	BasketEnergy = 0.0;
    for (unsigned int i = 0; i < sb.GetBasket().size(); i++) {
      fVecOfScintillators.push_back(new ScintillatorBar_F(*(sb.GetBasket()[i])));
      BasketEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
    }
  }
  
  std::vector<ScintillatorBar_F *> SingleBasket::GetBasket() const { return fVecOfScintillators; }

  void SingleBasket::clear()
  {

    for (unsigned int i = 0; i < size(); i++) {
      delete fVecOfScintillators[i];
    }
    BasketEnergy = 0.0;
    fVecOfScintillators.clear();
  }

  unsigned long int SingleBasket::size() { return fVecOfScintillators.size(); }

  void SingleBasket::push_back(ScintillatorBar_F * scint) { 
	  fVecOfScintillators.push_back(scint); 
	  BasketEnergy += scint->GetQMeanCorrected()/1000.0;
  }
  
  void SingleBasket::push_back(std::vector<ScintillatorBar_F *> vecOfScint) { 
	  //Untested Functionality
	  if(fVecOfScintillators.size()==0){
		  fVecOfScintillators=vecOfScint;
		  SetBasketEnergy();
	  }else{
		  for(int i=0;i<vecOfScint.size();i++){
			  fVecOfScintillators.push_back(new ScintillatorBar_F(*vecOfScint[i])); 
			  BasketEnergy += vecOfScint[i]->GetQMeanCorrected()/1000.0;
		  }
	  }
  }

  void SingleBasket::Print()
  {
    std::cout << RED << "******************** Size : " << size() << "***************************************" << RESET
              << std::endl;
    // std::vector<std::shared_ptr<ScintillatorBar_F>> scintBarVec = GetBasket();
    std::vector<ScintillatorBar_F *> scintBarVec = GetBasket();
    for (unsigned int i = 0; i < scintBarVec.size(); i++) {
      scintBarVec[i]->Print();
    }
    std::cout << "Number of bars in Basket is: " << scintBarVec.size() << std::endl;
    std::cout << "Total Energy of Basket is: " << GetBasketEnergy() << std::endl;
  }
  
  ULong64_t SingleBasket::GetBasketEventTime(int EvtIndx)
  {
	  return fVecOfScintillators[EvtIndx]->GetTStampSmall();
  }
  ULong64_t SingleBasket::GetBasketStartTime(){return GetBasketEventTime(0);}
  ULong64_t SingleBasket::GetBasketEndTime(){return GetBasketEventTime(size()-1);}
  ULong64_t SingleBasket::GetBasketDuration(){return GetBasketEndTime()-GetBasketStartTime();}
  Double_t SingleBasket::GetBasketEnergy(){return BasketEnergy;}
  void SingleBasket::SetBasketEnergy(){
	  BasketEnergy=0.0;
	  for(int i=0; i < fVecOfScintillators.size(); i++){
		  BasketEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
		  /*if(fVecOfScintillators[i]->GetQMeanCorrected()<0.0){
			  std::cout<<fVecOfScintillators[i]->GetBarIndex()<<"		"<<fVecOfScintillators[i]->GetQMean()<<"		"<<fVecOfScintillators[i]->GetQMeanCorrected()<<std::endl;
		  }
		  if(fVecOfScintillators[i]->GetQMean()==0.0){
			  std::cout<<fVecOfScintillators[i]->GetBarIndex()<<"		"<<fVecOfScintillators[i]->GetQMean()<<"		"<<fVecOfScintillators[i]->GetQMeanCorrected()<<"	"<<fVecOfScintillators[i]->GetQNear()<<"	"<<fVecOfScintillators[i]->GetQFar()<<std::endl;
		  }*/
	  }
  }
  Double_t SingleBasket::GetBasketBarEnergy(int evtIndx){
	  return fVecOfScintillators[evtIndx]->GetQMeanCorrected()/1000.0;
  }

  bool SingleBasket::isBarInBasket(ushort barIndx){
	  bool isbar = false;
	  std::vector<ScintillatorBar_F *> scintBarVec = GetBasket();
	  std::vector<int> *barIndxVec;
	  for(int i=0; i<scintBarVec.size(); i++){
		  barIndxVec->push_back(scintBarVec[i]->GetBarIndex());
	  } 
	  auto it            = std::find(barIndxVec->begin(),barIndxVec->end(),barIndx);
	  if (it != barIndxVec->end()){
		  isbar = true;
	  }
	  return isbar;
  }
} // namespace ismran
