/*
**	Filename : SingleAnimal.cpp
**	2024-02-06
**	username : Kirtikesh Kumar
**  Store all events in one animal as a vector
*/

#include "SingleAnimal.h"


ClassImp(ismran::SingleAnimal)

namespace ismran
{

  SingleAnimal::SingleAnimal() {AnimalEnergy=0.0;}

  SingleAnimal::~SingleAnimal() {}

  
  SingleAnimal::SingleAnimal(std::vector<ScintillatorBar_F *> vecOfScintBars)
  {
	AnimalEnergy = 0.0;
    fVecOfScintillators = vecOfScintBars;
    for(int i=0; i < fVecOfScintillators.size(); i++){
		AnimalEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
	}
  }

  SingleAnimal::SingleAnimal(const SingleAnimal &sb)
  {
	AnimalEnergy = 0.0;
    for (unsigned int i = 0; i < sb.GetAnimal().size(); i++) {
      fVecOfScintillators.push_back(new ScintillatorBar_F(*(sb.GetAnimal()[i])));
      AnimalEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
    }
  }
  
  std::vector<ScintillatorBar_F *> SingleAnimal::GetAnimal() const { return fVecOfScintillators; }

  void SingleAnimal::clear()
  {

    for (unsigned int i = 0; i < size(); i++) {
      delete fVecOfScintillators[i];
    }
    AnimalEnergy = 0.0;
    fVecOfScintillators.clear();
  }

  unsigned long int SingleAnimal::size() { return fVecOfScintillators.size(); }

  void SingleAnimal::push_back(ScintillatorBar_F * scint) { 
	  fVecOfScintillators.push_back(scint); 
	  AnimalEnergy += scint->GetQMeanCorrected()/1000.0;
  }
  
  void SingleAnimal::push_back(std::vector<ScintillatorBar_F *> vecOfScint) { 
	  //Untested Functionality
	  if(fVecOfScintillators.size()==0){
		  fVecOfScintillators=vecOfScint;
		  SetAnimalEnergy();
	  }else{
		  for(int i=0;i<vecOfScint.size();i++){
			  fVecOfScintillators.push_back(new ScintillatorBar_F(*vecOfScint[i])); 
			  AnimalEnergy += vecOfScint[i]->GetQMeanCorrected()/1000.0;
		  }
	  }
  }

  void SingleAnimal::Print()
  {
    std::cout << RED << "******************** Size : " << size() << "***************************************" << RESET
              << std::endl;
    std::vector<ScintillatorBar_F *> scintBarVec = GetAnimal();
    for (unsigned int i = 0; i < scintBarVec.size(); i++) {
      scintBarVec[i]->Print();
    }
    std::cout << "Number of bars in Animal is: " << scintBarVec.size() << std::endl;
    std::cout << "Total Energy of Animal is: " << GetAnimalEnergy() << std::endl;
  }
  
  ULong64_t SingleAnimal::GetAnimalEventTime(int EvtIndx)
  {
	  return fVecOfScintillators[EvtIndx]->GetTStampSmall();
  }
  ULong64_t SingleAnimal::GetAnimalStartTime(){return GetAnimalEventTime(0);}
  ULong64_t SingleAnimal::GetAnimalEndTime(){return GetAnimalEventTime(size()-1);}
  ULong64_t SingleAnimal::GetAnimalDuration(){return GetAnimalEndTime()-GetAnimalStartTime();}
  Double_t SingleAnimal::GetAnimalEnergy(){return AnimalEnergy;}
  void SingleAnimal::SetAnimalEnergy(){
	  AnimalEnergy=0.0;
	  for(int i=0; i < fVecOfScintillators.size(); i++){
		  AnimalEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
	  }
  }

  bool SingleAnimal::isBarInAnimal(ushort barIndx){
	  bool isbar = false;
	  std::vector<ScintillatorBar_F *> scintBarVec = GetAnimal();
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
