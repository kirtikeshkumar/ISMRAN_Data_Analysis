/*
**	Filename : Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include <iostream>
#include "Analyzer_F.h"
#include "ScintillatorBar_F.h"
#include "Helpers.h"
#include "Helpers_Dqm.h"
#include "SingleMuonTrack.h"
#include "SingleBasket.h"
#include "SingleAnimal.h"
#include "PairFinder.h"
#include "TreeEntry.h"
#include "colors.h"
namespace ismran {

unsigned int Analyzer_F::numOfShots = 1;
unsigned int Analyzer_F::shotNo     = 1;

Analyzer_F::Analyzer_F() {}
Analyzer_F::Analyzer_F(std::string datafilename, unsigned int numOfEvents)
{
  fDatafileName = datafilename;
  LoadData(numOfEvents);
}
Analyzer_F::~Analyzer_F() {}

unsigned int Analyzer_F::GetFileTime() const
{
  return fFileTime;
}
#ifndef FOLDED_DATA
void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t fBrCh_prev;
  ULong64_t fTstamp_prev;
  UInt_t fTime_prev;
  UInt_t fQlong_prev;

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  TTree *tr = (TTree *)fp->Get("ftree");

  tr->SetBranchAddress("fBrCh", &fBrCh);
  tr->SetBranchAddress("fQlong", &fQlong);
  tr->SetBranchAddress("fTstamp", &fTstamp);
  tr->SetBranchAddress("fTime", &fTime);
  //  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  bool newPair = true;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {

  TreeEntry *near = new TreeEntry;
  TreeEntry *far  = new TreeEntry;
  bool pairFound  = true;
  for (Long64_t iev = startEvNo; iev < endEvNo;) {
    if (!(iev % 1000000)) std::cout << "Processed : " << iev << " events........." << std::endl;
    if (pairFound) {
      nb += tr->GetEntry(iev);
      near->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;

      nb += tr->GetEntry(iev);
      far->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;
    } else {
      near->Set(far->brch, far->qlong, far->tstamp, far->time);
      nb += tr->GetEntry(iev);
      far->Set(fBrCh, fQlong, fTstamp, fTime);
      iev++;
    }

    pairFound = pf.ValidatePair(near, far);
    if (pairFound) {
      // fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(new ScintillatorBar_F(
      fVecOfScint_F.push_back(new ScintillatorBar_F(near->brch, near->qlong, far->qlong, near->tstamp, near->time,
                                                    near->tstamp - far->tstamp));
    }
  }
  fp->Close();
}

/*void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  UShort_t fBrCh_prev;
  ULong64_t fTstamp_prev;
  UInt_t fTime_prev;
  UInt_t fQlong_prev;

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  TTree *tr = (TTree *)fp->Get("ftree");

  tr->SetBranchAddress("fBrCh", &fBrCh);
  tr->SetBranchAddress("fQlong", &fQlong);
  tr->SetBranchAddress("fTstamp", &fTstamp);
  tr->SetBranchAddress("fTime", &fTime);
  //  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  // Injecting shots mechanism
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  bool newPair = true;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    if (!(iev % 1000000)) std::cout << "Processed : " << iev << " events........." << std::endl;
    // std::cout << "inside event loop......." << std::endl;
    nb += tr->GetEntry(iev);
    if ((iev == startEvNo) || newPair) {
      fBrCh_prev   = fBrCh;
      fTstamp_prev = fTstamp;
      fTime_prev   = fTime;
      fQlong_prev  = fQlong;
      newPair      = false;
    } else {
      UShort_t smallBrCh = (fBrCh_prev < fBrCh) ? fBrCh_prev : fBrCh;
      bool pairCond      = (!(smallBrCh % 2)) && (std::fabs(fTstamp_prev - fTstamp) < 25000);
      if (pairCond) {
        //std::cout << "PAIR condition found............." << std::endl;
        if ((fBrCh - fBrCh_prev) == 1) {
          fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong_prev, fQlong, fTstamp, fTime, fDelt)));
        } else {
          fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong, fQlong_prev, fTstamp, fTime, fDelt)));
        }
        newPair = true;
      } else {
        fBrCh_prev   = fBrCh;
        fTstamp_prev = fTstamp;
        fTime_prev   = fTime;
        fQlong_prev  = fQlong;
      }
    }
  }
  fp->Close();
}*/

#else
/*Function to load the data and in the vector of Scintillator_F*/
void Analyzer_F::LoadData(unsigned int numOfEvents)
{
  TFile *fp = new TFile(fDatafileName.c_str(), "r");

  UShort_t fBrCh;
  ULong64_t fTstamp;
  UInt_t fTime;
  UInt_t fQlong;
  Int_t fDelt;

  TTree *tr = (TTree *)fp->Get("ftree");

  tr->SetBranchAddress("fBrCh", &fBrCh);
  tr->SetBranchAddress("fQlong", &fQlong);
  tr->SetBranchAddress("fTstamp", &fTstamp);
  tr->SetBranchAddress("fTime", &fTime);
  tr->SetBranchAddress("fDelt", &fDelt);

  TTimeStamp *times = new TTimeStamp();
  Long64_t nEntries = tr->GetEntries();
  if (numOfEvents > 0) nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo                     = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo                       = shotNo * numOfEventsInOneShot;

  bool properev = true;
  UInt_t badcounter=0;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    // std::cout << "inside event loop......." << std::endl;
    properev = true;
    nb += tr->GetEntry(iev);
    if (iev == 0) {
      fFileTime = fTime;
      std::cout << "FileTime : " << fFileTime << " : " << __FILE__ << std::endl;
    }
    
    unsigned short int maxU_16bits = USHRT_MAX;
    UInt_t maskingVal              = maxU_16bits;
    if((fQlong & maskingVal)==0 or (fQlong >> 16)==0){ //events where QFar or QNear is 0 must be neglected 
		properev=false;
		badcounter+=1;
	}
	
    if (0) std::cout << fBrCh << " , " << fQlong << " , " << fTstamp << " , " << fTime << " , " << fDelt << std::endl;
	if(properev){
		fVecOfScint_F.push_back(new ScintillatorBar_F(iev, fBrCh, fQlong, fTstamp, fTime, fDelt));
	}
    //fVecOfScint_F.push_back(new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt));


    // std::shared_ptr<ScintillatorBar_F>(new ScintillatorBar_F(fBrCh, fQlong, fTstamp, fTime, fDelt)));

    if (iev % 1000000 == 0) {
      // times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec() << std::endl;
    }

  } //! event loop
  std::cout<<"badcounter "<<badcounter<<std::endl;
  fp->Close();
}
#endif
// std::vector<std::shared_ptr<SingleMuonTrack>> Analyzer_F::ReconstructMuonTrack()
std::vector<SingleMuonTrack *> Analyzer_F::ReconstructMuonTrack()
{
  // std::vector<unsigned int> vecOfPeakPos = GetPeakPosVec();
  std::cout << "Going to Create Muon Tracks.................." << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(), CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleMuonTrack *singleMuonTrack = new SingleMuonTrack();
  // std::shared_ptr<SingleMuonTrack> singleMuonTrack = std::shared_ptr<SingleMuonTrack>(new SingleMuonTrack());
  std::vector<SingleMuonTrack *> smtVec;
  // std::vector<std::shared_ptr<SingleMuonTrack>> smtVec;

  // std::string
  // outfileName="/home/rsehgal/myAmbar/MuonTracks/Muon_Tracks_"+ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName))+".root";
  std::string outfileName = //"/home/rsehgal/MuonTracks/Muon_Tracks_" +
      "MuonTracks_" + ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  // TFile *tracksFile = new TFile("MuonTracks.root", "RECREATE");
  TFile *tracksFile = new TFile(outfileName.c_str(), "RECREATE");
  tracksFile->cd();
  TTree *tracksTree = new TTree("TracksTree", "TracksTree");
  // tracksTree->SetDirectory(0);
  tracksTree->Branch("MuonTracks", "ismran::SingleMuonTrack", &singleMuonTrack);

  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  for (unsigned int i = 1; i < scintVecSize; i++) {
    // if (fVecOfScint_F[i]->GetQMeanCorrected(vecOfPeakPos[fVecOfScint_F[i]->GetBarIndex()]) > qmeanCorrThreshold) {
    //if (fVecOfScint_F[i]->GetQMeanCorrected() > qmeanCorrThreshold) {
      if (std::fabs(fVecOfScint_F[i]->GetTStampSmall() - tStart) < 20000) {
        // Within 20ns window
        singleMuonTrack->push_back(fVecOfScint_F[i]);
        // singleMuonTrack->push_back(fVecOfScint_F[i].get());
        if (fVecOfScint_F[i]->GetTStampSmall() < tStart) tStart = fVecOfScint_F[i]->GetTStampSmall();
      } else {
        // Previous muon event over

        // Do we REALLY need SORTING
        singleMuonTrack->Sort();
        // singleMuonTrack->Print();
        // smtVec.push_back(std::shared_ptr<SingleMuonTrack>(new SingleMuonTrack(*singleMuonTrack)));
        smtVec.push_back(new SingleMuonTrack(*singleMuonTrack));
        tracksTree->Fill();
        singleMuonTrack->clear();
        singleMuonTrack->push_back(fVecOfScint_F[i]);
        // singleMuonTrack->push_back(fVecOfScint_F[i].get());
        tStart = fVecOfScint_F[i]->GetTStampSmall();
      }
    //}
  }
  std::cout << "SmtVec size : " << smtVec.size() << std::endl;
  tracksTree->Write();
  tracksFile->Close();
  return smtVec;
}

std::vector<SingleBasket *> Analyzer_F::ReconstructBasket()
{
  std::cout << "Going to Create Baskets based on delT between events" << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(), CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  //std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
  std::vector<SingleBasket *> sbVec;
  std::string outfileName = "Baskets_EventDelT_" + ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);
  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  double_t delt=0;
  singleBasket->push_back(fVecOfScint_F[0]);
  //std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
  for (unsigned int i = 1; i < scintVecSize; i++) {
      if (fVecOfScint_F[i]->GetTStampSmall() - singleBasket->GetBasketEndTime() < 50000) {
        // 2 consecutive events within 50ns window
        singleBasket->push_back(fVecOfScint_F[i]);
        //std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
      } else {
		  singleBasket->SetBasketParameters();
		  //std::cout<<"				Basket Energy Is "<<singleBasket->GetBasketEnergy()<<std::endl;
		  sbVec.push_back(new SingleBasket(*singleBasket));
		  basketTree->Fill();
		  singleBasket->clear();
		  //std::cout<<"________________________________________________________"<<std::endl;
          singleBasket->push_back(fVecOfScint_F[i]);
          tStart = fVecOfScint_F[i]->GetTStampSmall();
          
      }
 //   }
  }
  std::cout << "SBVec size : " << sbVec.size() << std::endl;
  basketTree->Write();
  basketFile->Close();
  return sbVec;
}

std::vector<SingleBasket *> Analyzer_F::ReconstructBasket(uint basketdT)
{
  std::cout << "Going to Create Baskets with Max Timespan " << basketdT << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(), CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  std::vector<SingleBasket *> sbVec;
  
  std::string outfileName = "Baskets_of_TSpan_" + std::to_string(basketdT/1000) + "ms_" + ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);

  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  double_t delt=0;
  for (unsigned int i = 0; i < scintVecSize; i++) {
	  //std::cout<<tStart<<"	"<<fVecOfScint_F[i]->GetTStampAverage()<<"	"<<fVecOfScint_F[i]->GetTStampAverage() - tStart<<std::endl;
      if (fVecOfScint_F[i]->GetTStampSmall() - tStart < basketdT) {
        // Within basketdT window
        singleBasket->push_back(fVecOfScint_F[i]);
      } else {
		  //singleBasket->SetBasketParameters();
		  if(sbVec.size()==0){singleBasket->Print();}
		  sbVec.push_back(new SingleBasket(*singleBasket));
		  if(sbVec.size()==1){sbVec[0]->Print();}
		  basketTree->Fill();
		  singleBasket->clear();
          singleBasket->push_back(fVecOfScint_F[i]);
          tStart = fVecOfScint_F[i]->GetTStampSmall();
      }
 //   }
  }
  std::cout << "SBVec size : " << sbVec.size() << std::endl;
  basketTree->Write();
  basketFile->Close();
  sbVec[0]->Print();
  return sbVec;
}

std::vector<SingleBasket *> Analyzer_F::ReconstructVetoedBasket(uint numVetoLayers, std::vector<SingleBasket *> baskets)
{
  std::cout << "Going to Create Baskets with " << numVetoLayers << " veto layers" << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  std::vector<SingleBasket *> vsbVec;
  
  std::string outfileName = "VetoedBaskets_with_" + std::to_string(numVetoLayers) + "_VetoLayers_" + ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);

  ULong64_t tStart = baskets[0]->GetBasketStartTime();
  unsigned int basketVecSize = baskets.size();
  
  std::vector<int> VetoBarsIndx = GetJacketBarIndx(numVetoLayers);
  ushort barindex;
  bool veto=false;
  
  for(uint i=0; i<basketVecSize;i++){
	  //std::cout<<"Basket Energy "<<baskets[i]->GetBasketEnergy()<<std::endl;
	  singleBasket = new SingleBasket(*baskets[i]);
	  //std::cout<<"singleBasket Energy "<<singleBasket->GetBasketEnergy()<<" size "<< singleBasket->size() <<std::endl;
	  singleBasket->SetBasketEnergy();
	  //std::cout<<"singleBasket Energy now "<<singleBasket->GetBasketEnergy()<<std::endl;
	  for(unsigned int j=0; j<singleBasket->size(); j++){
		  barindex = (singleBasket->GetBasket())[j]->GetBarIndex();
		  veto = ismran::IsJacket(barindex, VetoBarsIndx);
		  if(veto){break;}
	  }
	  if(!veto){
		  vsbVec.push_back(new ismran::SingleBasket(*baskets[i]));
		  basketTree->Fill();
	  }
	  singleBasket->clear();  
  }
  std::cout << "VetoedSBVec size : " << vsbVec.size() << std::endl;
  basketTree->Write();
  basketFile->Close();
  return vsbVec;
}

std::vector<unsigned int> Analyzer_F::GetPeakPosVec(std::string peakPosFileLoc)
{
  return ismran::GetPeakPosVec(peakPosFileLoc, ismran::GetBaseName(fDatafileName));
}
std::vector<unsigned int> Analyzer_F::GetPeakPosVec_Direct(std::string peakPosFile)
{
#ifdef VERBOSE
  std::cout << RED << "PEAK pos file : " << peakPosFile << RESET << std::endl;
#endif
  return ismran::GetPeakPosVec_Direct(".", peakPosFile);
}

// std::vector<std::shared_ptr<ScintillatorBar_F>> Analyzer_F::GetVectorOfScintillators()
std::vector<ScintillatorBar_F *> Analyzer_F::GetVectorOfScintillators()
{
  return fVecOfScint_F;
}

/*std::vector<SingleAnimal *> Analyzer_F::ReconstructAnimal(std::vector<SingleBasket *> baskets){
	std::cout << "Going to Create Animals " << std::endl;
	SingleBasket *singleBasket = new SingleBasket();
	SingleAnimal *singleAnimal = new SingleAnimal();
	std::vector<SingleAnimal *> saVec;
	
	
}*/

} // namespace ismran
