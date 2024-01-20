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

  SingleBasket::SingleBasket() {}

  SingleBasket::~SingleBasket() {}

  
  SingleBasket::SingleBasket(std::vector<ScintillatorBar_F *> vecOfScintBars)
  {
    fVecOfScintillators = vecOfScintBars;
  }

  SingleBasket::SingleBasket(const SingleBasket &sb)
  {
    for (unsigned int i = 0; i < sb.GetBasket().size(); i++) {
      fVecOfScintillators.push_back(new ScintillatorBar_F(*(sb.GetBasket()[i])));
    }
  }
  
  std::vector<ScintillatorBar_F *> SingleBasket::GetBasket() const { return fVecOfScintillators; }

  void SingleBasket::clear()
  {

    for (unsigned int i = 0; i < size(); i++) {
      delete fVecOfScintillators[i];
    }
    fVecOfScintillators.clear();
  }

  unsigned long int SingleBasket::size() { return fVecOfScintillators.size(); }

  void SingleBasket::push_back(ScintillatorBar_F * scint) { fVecOfScintillators.push_back(scint); }

  void SingleBasket::Print()
  {
    std::cout << RED << "******************** Size : " << size() << "***************************************" << RESET
              << std::endl;
    // std::vector<std::shared_ptr<ScintillatorBar_F>> scintBarVec = GetBasket();
    std::vector<ScintillatorBar_F *> scintBarVec = GetBasket();
    for (unsigned int i = 0; i < scintBarVec.size(); i++) {
      scintBarVec[i]->Print();
    }
    std::cout << std::endl;
  }
  
  ULong64_t SingleBasket::GetBasketEventTime(int EvtIndx)
  {
	  return fVecOfScintillators[EvtIndx]->GetTStampAverage();
  }
  ULong64_t SingleBasket::GetBasketStartTime(){return GetBasketEventTime(0);}
  ULong64_t SingleBasket::GetBasketEndTime(){return GetBasketEventTime(size()-1);}

} // namespace ismran
