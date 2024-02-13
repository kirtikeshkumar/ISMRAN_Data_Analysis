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
  //Constructors
  SingleBasket::SingleBasket() {
	  BasketEnergy=0.0;
	  COMIndex = 0;
	  sigX = 0.0;
	  sigY = 0.0;
	  sigT = 0;
	  meanT = 0;
  }

  SingleBasket::~SingleBasket() {}

  
  SingleBasket::SingleBasket(std::vector<ScintillatorBar_F *> vecOfScintBars)
  {
    fVecOfScintillators = vecOfScintBars;
    SetBasketParameters();
  }

  SingleBasket::SingleBasket(const SingleBasket &sb)
  {
	  for (unsigned int i = 0; i < sb.GetBasket().size(); i++) {
	      fVecOfScintillators.push_back(new ScintillatorBar_F(*(sb.GetBasket()[i])));
      }
	  SetBasketParameters();
	  //Print();
  }
  
  //Vectors
  void SingleBasket::clear()
  {

    for (unsigned int i = 0; i < size(); i++) {
      delete fVecOfScintillators[i];
    }
    BasketEnergy = 0.0;
	COMIndex = 0;
	sigX = 0.0;
	sigY = 0.0;
	sigT = 0;
	meanT = 0;
    fVecOfScintillators.clear();
  }

  uint SingleBasket::size() { return fVecOfScintillators.size(); }

  void SingleBasket::push_back(ScintillatorBar_F * scint) { 
	  if(fVecOfScintillators.size()==0){Initialiser();}
	  fVecOfScintillators.push_back(scint); 
	  SetBasketEnergy(scint->GetQMeanCorrected()/1000.0);
  }
  
  void SingleBasket::push_back(std::vector<ScintillatorBar_F *> vecOfScint) { 
	  //Untested Functionality
	  if(fVecOfScintillators.size()==0){
		  fVecOfScintillators=vecOfScint;
		  SetBasketEnergy();
	  }else{
		  for(int i=0;i<vecOfScint.size();i++){
			  fVecOfScintillators.push_back(new ScintillatorBar_F(*vecOfScint[i])); 
			  SetBasketEnergy(vecOfScint[i]->GetQMeanCorrected()/1000.0);
		  }
	  }
  }
  //Print
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
    std::cout << "Start Time of Basket is: " << GetBasketStartTime() << std::endl;
    std::cout << "Mean Time of Basket is: " << GetBasketMeanTime() << std::endl;
    std::cout << "StdDev in Time of Basket is: " << GetBasketStdDevT() << std::endl;
    std::cout << "StdDev in X of Basket is: " << GetBasketStdDevX() << std::endl;
    std::cout << "StdDev in Y of Basket is: " << GetBasketStdDevY() << std::endl;
    std::cout << "COM Bar of Basket is: " << GetBasketCOMBar() << std::endl;
  }
  //Getters
  std::vector<ScintillatorBar_F *> SingleBasket::GetBasket() const { return fVecOfScintillators; }
  ULong64_t SingleBasket::GetBasketEventTime(int EvtIndx)
  {
	  return fVecOfScintillators[EvtIndx]->GetTStampSmall();
  }
  ULong64_t SingleBasket::GetBasketStartTime(){return GetBasketEventTime(0);}
  ULong64_t SingleBasket::GetBasketEndTime(){return GetBasketEventTime(size()-1);}
  ULong64_t SingleBasket::GetBasketDuration(){return GetBasketEndTime()-GetBasketStartTime();}
  ULong64_t SingleBasket::GetBasketMeanTime(){return meanT;}
  uint SingleBasket::GetBasketStdDevT(){return sigT;}
  Double_t SingleBasket::GetBasketStdDevX(){return sigX;}
  Double_t SingleBasket::GetBasketStdDevY(){return sigY;}
  ushort SingleBasket::GetBasketCOMBar(){return COMIndex;}
  Double_t SingleBasket::GetBasketEnergy(){return BasketEnergy;}
  Double_t SingleBasket::GetBasketBarEnergy(int evtIndx){
	  return fVecOfScintillators[evtIndx]->GetQMeanCorrected()/1000.0;
  }
  ScintillatorBar_F* SingleBasket::GetEvent(int EvtIndx){
	  return fVecOfScintillators[EvtIndx];
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
  //Setters
  void SingleBasket::SetBasketEnergy(){
	  BasketEnergy=0.0;
	  for(int i=0; i < fVecOfScintillators.size(); i++){
		  BasketEnergy += fVecOfScintillators[i]->GetQMeanCorrected()/1000.0;
	  }
  }
  void SingleBasket::SetBasketEnergy(Double_t E){
	  BasketEnergy += E;
  }
  void SingleBasket::SetBasketParameters(){
	  //std::cout<<"Entered for parameter setting"<<std::endl;
	  BasketEnergy = 0.0;
	  TH2* H2D  = new TH2F("H2D", "2D Hits", 9,0,9, 10,0,10);
	  //TH1* H1DT  = new TH1I("H1DT", "Time", std::max(static_cast<int>(GetBasketDuration()/1000),1),0.0,std::max(static_cast<int>(GetBasketDuration()/1000),1)); // 1ns bins
	  H2D->SetStats(0);	//not necessary, only sets stat box to not show
	  //H1DT->SetStats(0);
	  Double_t times = 0.0;
	  ushort indxb;
	  for(int j=0;j<size();j++){
		  indxb = fVecOfScintillators[j]->GetBarIndex();
		  H2D->Fill(indxb/10+0.5,indxb%10+0.5,GetBasketBarEnergy(j));
		  //H1DT->Fill(GetBasketEventTime(j)-GetBasketStartTime());
		  BasketEnergy += fVecOfScintillators[j]->GetQMeanCorrected()/1000.0;
	  }
	  //meanT = H1DT->GetMean()+GetBasketStartTime();
	  //sigT = H1DT->GetRMS();
	  SetBasketMeanTime();
	  SetBasketStdDevT();
	  COMIndex = static_cast<int>(std::floor(H2D->GetMean(1)))*10 + static_cast<int>(std::floor(H2D->GetMean(2)));
	  sigX = H2D->GetStdDev(1);
	  sigY = H2D->GetStdDev(2);
	  //Print();
	  delete H2D;
	  //delete H1DT;	  
  }
  
  void SingleBasket::SetBasketMeanTime(){
	  ULong64_t startT = GetBasketStartTime();
	  ULong64_t sum = 0;
	  for(int i=0; i < size(); i++){
		  sum += GetBasketEventTime(i) - startT;
	  }
	  meanT = sum/size() + startT;
  }
  
  /*void SingleBasket::SetBasketMeanTime(ULong64_t val){
	  meanT = val;
  }*/
  
  void SingleBasket::SetBasketStdDevT(){
	  ULong64_t startT = GetBasketStartTime();
	  ULong64_t sum = 0;
	  if(meanT==0 or meanT==GetBasketStartTime()){SetBasketMeanTime();}
	  for(int i=0; i < size(); i++){
		  if(GetBasketEventTime(i)<meanT){
			  sum += TMath::Power((meanT - GetBasketEventTime(i)),2);
		  }else{
			  sum += TMath::Power((GetBasketEventTime(i) - meanT),2);
		  }
	  }
	  //std::cout<<"sum"<<sum<<std::endl;
	  double stdDev = std::sqrt(sum/size());
	  //std::cout<<"stdev"<<stdDev<<std::endl;
	  sigT = static_cast<uint>(std::ceil(stdDev));
	  //std::cout<<"stdev"<<sigT<<std::endl;
      
  }
  
  /*void SingleBasket::SetBasketStdDevT(uint val){
	  sigT = val;
  }*/
  
  void SingleBasket::Initialiser(){
	  BasketEnergy=0.0;
	  COMIndex = 0;
	  sigX = 0.0;
	  sigY = 0.0;
	  sigT = 0;
	  meanT = 0;
  }
} // namespace ismran
