/*
**	Filename : Analyzer_F.cpp
**	2021-10-06
**	username : rsehgal
*/
#include "Analyzer_F.h"
#include "Helpers.h"
#include "Helpers_Dqm.h"
#include "PairFinder.h"
#include "ScintillatorBar_F.h"
#include "SingleAnimal.h"
#include "SingleBasket.h"
#include "SingleMuonTrack.h"
#include "TreeEntry.h"
#include "colors.h"
#include <iostream>

using namespace std;
namespace ismran {

unsigned int Analyzer_F::numOfShots = 1;
unsigned int Analyzer_F::shotNo = 1;

Analyzer_F::Analyzer_F() {}
Analyzer_F::Analyzer_F(std::string datafilename, unsigned int numOfEvents,
                       double EThreshold) {
  fDatafileName = datafilename;
  BarEThreshold = EThreshold;
  LoadData(numOfEvents, BarEThreshold);
}
Analyzer_F::~Analyzer_F() {}

unsigned int Analyzer_F::GetFileTime() const { return fFileTime; }
#ifndef FOLDED_DATA
void Analyzer_F::LoadData(unsigned int numOfEvents, double EThreshold) {
  // THRESHOLD IS NOT IMPLEMENTED YET HERE

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
  if (numOfEvents > 0)
    nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo = shotNo * numOfEventsInOneShot;

  bool newPair = true;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {

  TreeEntry *near = new TreeEntry;
  TreeEntry *far = new TreeEntry;
  bool pairFound = true;
  for (Long64_t iev = startEvNo; iev < endEvNo;) {
    if (!(iev % 1000000))
      std::cout << "Processed : " << iev << " events........." << std::endl;
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
      // fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(new
      // ScintillatorBar_F(
      fVecOfScint_F.push_back(new ScintillatorBar_F(
          near->brch, near->qlong, far->qlong, near->tstamp, near->time,
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
    if (!(iev % 1000000)) std::cout << "Processed : " << iev << "
events........." << std::endl;
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
      bool pairCond      = (!(smallBrCh % 2)) && (std::fabs(fTstamp_prev -
fTstamp) < 25000); if (pairCond) {
        //std::cout << "PAIR condition found............." << std::endl;
        if ((fBrCh - fBrCh_prev) == 1) {
          fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong_prev, fQlong, fTstamp, fTime,
fDelt))); } else { fVecOfScint_F.push_back(std::shared_ptr<ScintillatorBar_F>(
              new ScintillatorBar_F(fBrCh, fQlong, fQlong_prev, fTstamp, fTime,
fDelt)));
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
void Analyzer_F::LoadData(unsigned int numOfEvents, double EThreshold) {
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
  if (numOfEvents > 0)
    nEntries = numOfEvents;
  std::cout << "Total number of Entries : " << nEntries << std::endl;
  Long64_t nb = 0;

  /* Injecting shots mechanism */
  unsigned long int numOfEventsInOneShot = nEntries / numOfShots;
  Long64_t startEvNo = (shotNo - 1) * numOfEventsInOneShot;
  Long64_t endEvNo = shotNo * numOfEventsInOneShot;

  // bool properev = true;
  UInt_t badcounter = 0;
  // for (Long64_t iev = 0; iev < nEntries; iev++) {
  for (Long64_t iev = startEvNo; iev < endEvNo; iev++) {
    // std::cout << "inside event loop......." << std::endl;
    // properev = true;
    nb += tr->GetEntry(iev);
    if (iev == 0) {
      fFileTime = fTime;
      std::cout << "FileTime : " << fFileTime << " : " << __FILE__ << std::endl;
    }

    unsigned short int maxU_16bits = USHRT_MAX;
    UInt_t maskingVal = maxU_16bits;
    if ((fQlong & maskingVal) == 0 or
        (fQlong >> 16) ==
            0) { // events where QFar or QNear is 0 must be neglected
      // properev=false;
      badcounter += 1;
    }

    if (0)
      std::cout << fBrCh << " , " << fQlong << " , " << fTstamp << " , "
                << fTime << " , " << fDelt << std::endl;
    // if(properev){
    ScintillatorBar_F *sbar =
        new ScintillatorBar_F(iev, fBrCh, fQlong, fTstamp, fTime, fDelt);
    double energ = sbar->GetQMeanCorrected();
    if (energ >= EThreshold) {
      fVecOfScint_F.push_back(
          new ScintillatorBar_F(iev, fBrCh, fQlong, fTstamp, fTime, fDelt));
    }
    delete sbar;
    //}
    // fVecOfScint_F.push_back(new ScintillatorBar_F(fBrCh, fQlong, fTstamp,
    // fTime, fDelt));

    // std::shared_ptr<ScintillatorBar_F>(new ScintillatorBar_F(fBrCh, fQlong,
    // fTstamp, fTime, fDelt)));

    if (iev % 1000000 == 0) {
      // times->Set(time, kTRUE, offset, kFALSE);
      std::cout << " Processing event : " << iev << "\t" << times->GetTimeSpec()
                << std::endl;
    }

  } //! event loop
  std::cout << "badcounter " << badcounter << std::endl;
  fp->Close();
}
#endif

std::vector<SingleBasket *> Analyzer_F::ReadBasket(std::string datafilename) {
  if (fDatafileName.empty()) {
    fDatafileName = datafilename;
  }
  TFile *fp = new TFile(fDatafileName.c_str(), "r");
  std::vector<SingleBasket *> sbVec;
  if (!fp || fp->IsZombie()) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return sbVec;
  }

  // read the tree
  TTree *ftree = dynamic_cast<TTree *>(fp->Get("basketTree"));
  if (!ftree) {
    std::cerr << "Error: Unable to retrieve tree from file." << std::endl;
    fp->Close();
    return sbVec;
  }

  std::cout << "Loaded basketTree" << std::endl;

  // Set the branch address to read the object from the tree
  ismran::SingleBasket *basket = new ismran::SingleBasket();
  ftree->SetBranchAddress("Baskets", &basket);

  // Initialising the vecotr to read into

  // initialising variables before reading
  Long64_t nentries = ftree->GetEntries();
  Long64_t nbytes = 0;
  double Ethresh = 999999999.0;

  for (Long64_t i = 0; i < nentries; i++) {
    if (i % 1000000 == 0) {
      std::cout << "Reading Basket " << i << " of " << nentries << std::endl;
    }
    nbytes += ftree->GetEntry(i);
    if (basket->GetBasketEnergy() < Ethresh) {
      Ethresh = basket->GetBasketEnergy();
    }
    sbVec.push_back(new SingleBasket(*basket));
  }
  fp->Close();
  BarEThreshold = Ethresh;
  return sbVec;
}

// std::vector<std::shared_ptr<SingleMuonTrack>>
// Analyzer_F::ReconstructMuonTrack()
std::vector<SingleMuonTrack *> Analyzer_F::ReconstructMuonTrack() {
  // std::vector<unsigned int> vecOfPeakPos = GetPeakPosVec();
  std::cout << "Going to Create Muon Tracks.................." << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(),
            CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleMuonTrack *singleMuonTrack = new SingleMuonTrack();
  // std::shared_ptr<SingleMuonTrack> singleMuonTrack =
  // std::shared_ptr<SingleMuonTrack>(new SingleMuonTrack());
  std::vector<SingleMuonTrack *> smtVec;
  // std::vector<std::shared_ptr<SingleMuonTrack>> smtVec;

  // std::string
  // outfileName="/home/rsehgal/myAmbar/MuonTracks/Muon_Tracks_"+ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName))+".root";
  std::string outfileName = //"/home/rsehgal/MuonTracks/Muon_Tracks_" +
      "MuonTracks_" +
      ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  // TFile *tracksFile = new TFile("MuonTracks.root", "RECREATE");
  TFile *tracksFile = new TFile(outfileName.c_str(), "RECREATE");
  tracksFile->cd();
  TTree *tracksTree = new TTree("TracksTree", "TracksTree");
  // tracksTree->SetDirectory(0);
  tracksTree->Branch("MuonTracks", "ismran::SingleMuonTrack", &singleMuonTrack);

  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  for (unsigned int i = 1; i < scintVecSize; i++) {
    // if
    // (fVecOfScint_F[i]->GetQMeanCorrected(vecOfPeakPos[fVecOfScint_F[i]->GetBarIndex()])
    // > qmeanCorrThreshold) {
    // if (fVecOfScint_F[i]->GetQMeanCorrected() > qmeanCorrThreshold) {
    if (std::fabs(fVecOfScint_F[i]->GetTStampSmall() - tStart) < 20000) {
      // Within 20ns window
      singleMuonTrack->push_back(fVecOfScint_F[i]);
      // singleMuonTrack->push_back(fVecOfScint_F[i].get());
      if (fVecOfScint_F[i]->GetTStampSmall() < tStart)
        tStart = fVecOfScint_F[i]->GetTStampSmall();
    } else {
      // Previous muon event over

      // Do we REALLY need SORTING
      singleMuonTrack->Sort();
      // singleMuonTrack->Print();
      // smtVec.push_back(std::shared_ptr<SingleMuonTrack>(new
      // SingleMuonTrack(*singleMuonTrack)));
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

std::vector<SingleBasket *> Analyzer_F::ReconstructBasket() {
  std::cout << "Going to Create Baskets based on delT between events"
            << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(),
            CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  // std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
  std::vector<SingleBasket *> sbVec;
  std::string outfileName =
      "Baskets_EventDelT_" +
      ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);
  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  double_t delt = 0;
  singleBasket->push_back(fVecOfScint_F[0]);
  // std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
  bool properev = true;
  UInt_t badcounter = 0;
  unsigned short int maxU_16bits = USHRT_MAX;
  UInt_t maskingVal = maxU_16bits;
  for (unsigned int i = 1; i < scintVecSize; i++) {
    if (fVecOfScint_F[i]->GetTStampSmall() - singleBasket->GetBasketEndTime() <
        50000) {
      // 2 consecutive events within 50ns window
      singleBasket->push_back(fVecOfScint_F[i]);
      if (fVecOfScint_F[i]->GetQFar() == 0 or
          fVecOfScint_F[i]->GetQNear() == 0) {
        // events where QFar or QNear is 0 must be neglected properev=false;
        badcounter += 1;
      }
      // std::cout<<singleBasket->GetBasketEnergy()<<std::endl;
    } else {
      if (properev) {
        sbVec.push_back(new SingleBasket(*singleBasket));
        basketTree->Fill();
      }
      // singleBasket->SetBasketParameters();
      // std::cout<<" Basket Energy Is
      // "<<singleBasket->GetBasketEnergy()<<std::endl; singleBasket->clear();
      properev = true;
      // std::cout<<"________________________________________________________"<<std::endl;
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

std::vector<SingleBasket *> Analyzer_F::ReconstructBasket(uint basketdT) {
  std::cout << "Going to Create Baskets with Max Timespan " << basketdT
            << std::endl;
  std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(),
            CompareTimestampScintillator);
  unsigned int scintVecSize = fVecOfScint_F.size();
  std::cout << "ScintVectSize : " << scintVecSize << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  std::vector<SingleBasket *> sbVec;

  std::string outfileName =
      "../../Data_Analysis_Outputs/Baskets/Raw/Baskets_of_TSpan_" +
      std::to_string(basketdT / 1000) + "ns_" +
      ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);

  ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
  double_t delt = 0;
  bool properev = true;
  UInt_t badcounter = 0;
  ULong64_t prevbasketendtime = 0;
  for (unsigned int i = 0; i < scintVecSize; i++) {
    if (i % 1000000 == 0) {
      std::cout << " Processing event : " << i << std::endl;
    }
    // std::cout<<tStart<<"	"<<fVecOfScint_F[i]->GetTStampAverage()<<"
    // "<<fVecOfScint_F[i]->GetTStampAverage() - tStart<<std::endl;
    if (fVecOfScint_F[i]->GetTStampSmall() - tStart < basketdT) {
      // Within basketdT window
      singleBasket->push_back(fVecOfScint_F[i]);
      if (fVecOfScint_F[i]->GetQFar() == 0 or
          fVecOfScint_F[i]->GetQNear() ==
              0) { // events where QFar or QNear is 0 must be neglected
        properev = false;
        badcounter += 1;
      }
    } else {
      // if(sbVec.size()==9){singleBasket->Print();}
      if (properev) { // && singleBasket->GetBasketEnergy()>=2){// &&
                      // singleBasket->GetBasketEnergy()>=0.40){// and
                      // (singleBasket->GetBasketStartTime()-prevbasketendtime)
                      // >= basketdT){ //this allows to neglect baskets very
                      // close in time
        // singleBasket->Print();
        sbVec.push_back(new SingleBasket(*singleBasket));
        basketTree->Fill();
      }
      singleBasket->clear();
      if (fVecOfScint_F[i]->GetQFar() == 0 or
          fVecOfScint_F[i]->GetQNear() ==
              0) { // events where QFar or QNear is 0 must be neglected
        properev = false;
        badcounter += 1;
      } else {
        properev = true;
      }
      singleBasket->push_back(fVecOfScint_F[i]);
      tStart = fVecOfScint_F[i]->GetTStampSmall();
    }
    //   }
  }
  std::cout << "SBVec size : " << sbVec.size() << std::endl;
  std::cout << "badcounter : " << badcounter << std::endl;
  basketTree->Write();
  basketFile->Close();
  // sbVec[0]->Print();
  return sbVec;
}

// std::vector<SingleBasket *> Analyzer_F::ReconstructBasket() {
//   uint basketdt = 50000;
//   std::cout << "Going to Create Baskets with Rolling Lookup" << std::endl;
//   std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(),
//             CompareTimestampScintillator);
//   unsigned int scintVecSize = fVecOfScint_F.size();
//   std::cout << "ScintVectSize : " << scintVecSize << std::endl;
//   SingleBasket *singleBasket = new SingleBasket();
//   SingleBasket *finalBasket = new SingleBasket();
//   std::vector<SingleBasket *> sbVec;
//   std::string outfileName =
//       "../../Data_Analysis_Outputs/Baskets/Raw/Baskets_Rolling_" +
//       ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) +
//       ".root";
//   TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
//   basketFile->cd();
//   TTree *basketTree = new TTree("basketTree", "basketTree");
//   basketTree->Branch("Baskets", "ismran::SingleBasket", &finalBasket);
//   ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
//   double_t delt = 0;
//   bool properev = true;
//   UInt_t badcounter = 0;
//   uint compval;
//   uint uniT;
//   uint sigt;
//   std::cout << "now starting" << std::endl;
//   for (unsigned int i = 0; i < scintVecSize; i++) {
//     if (i % 1000000 == 0) {
//       std::cout << " Processing event : " << i << std::endl;
//     }
//     if (fVecOfScint_F[i]->GetTStampSmall() - tStart < basketdt) {
//       // Within basketdT window
//       singleBasket->push_back(new ScintillatorBar_F(*fVecOfScint_F[i]));
//       /*if(fVecOfScint_F[i]->GetQFar()==0 or
//       fVecOfScint_F[i]->GetQNear()==0){
//          //events where QFar or QNear is 0 must be neglected properev=false;
//                       badcounter+=1;
//               }*/
//     } else {
//       if (singleBasket->size() == 1) {
//         finalBasket = new SingleBasket(*singleBasket);
//         sbVec.push_back(new SingleBasket(*finalBasket));
//         basketTree->Fill();
//       } else {
//         // singleBasket->SetBasketMeanTime();
//         // singleBasket->SetBasketStdDevT();
//         uniT = singleBasket->GetBasketDuration() /
//                singleBasket->size(); // separation between poisson/uniform
//                                      // distributed events
//         // sigt = singleBasket->GetBasketStdDevT();
//         compval = std::max(uniT, 4 * sigt / singleBasket->size());
//         finalBasket->push_back(
//             new ScintillatorBar_F(*singleBasket->GetEvent(0)));
//         if (singleBasket->GetEvent(0)->GetQFar() == 0 or
//             singleBasket->GetEvent(0)->GetQNear() == 0) {
//           properev = false;
//         }
//         for (uint j = 1; j < singleBasket->size(); j++) {
//           if ((singleBasket->GetBasketEventTime(j) -
//                finalBasket->GetBasketEndTime()) <=
//               compval) { //+int(TMath::Sqrt(compval))){		//this
//               can allow
//                          //for more stringent cuts
//             if (singleBasket->GetEvent(j)->GetQFar() == 0 or
//                 singleBasket->GetEvent(j)->GetQNear() == 0) {
//               properev = false;
//             }
//             // std::cout<<"Adding event "<<j+1<<" of basket
//             // "<<sbVec.size()+1<<std::endl;
//             finalBasket->push_back(
//                 new ScintillatorBar_F(*singleBasket->GetEvent(j)));
//             // std::cout<<"Added event "<<j+1<<" of basket
//             // "<<sbVec.size()+1<<std::endl;
//           } else {
//             if (properev) {
//               // std::cout<<"Adding basket"<<sbVec.size() + 1<<std::endl;
//               sbVec.push_back(new SingleBasket(*finalBasket));
//               basketTree->Fill();
//               // std::cout<<"Added basket"<<sbVec.size()<<std::endl;
//             }
//             i = i + j - singleBasket->size();
//             if (fVecOfScint_F[i]->GetTStampSmall() ==
//                 finalBasket->GetBasketEndTime()) {
//               std::cout << "error overlapping baskets" << std::endl;
//             }
//             break;
//           }
//           if (j == singleBasket->size() - 1 and properev) {
//             // std::cout<<"Adding basket end"<<sbVec.size() + 1<<std::endl;
//             sbVec.push_back(new SingleBasket(*finalBasket));
//             basketTree->Fill();
//             // std::cout<<"Added basket end"<<sbVec.size()<<std::endl;
//           }
//           // std::cout<<"Going for event "<<j+1<<" of
//           basket"<<sbVec.size()<<"
//           // of size "<<singleBasket->size()<<std::endl;
//         }
//       }
//       singleBasket->clear();
//       if (finalBasket) {
//         finalBasket->clear();
//       }
//       properev = true;
//       singleBasket->push_back(new ScintillatorBar_F(*fVecOfScint_F[i]));
//       tStart = fVecOfScint_F[i]->GetTStampSmall();
//     }
//   }
//   std::cout << "SBVec size : " << sbVec.size() << std::endl;
//   std::cout << "badcounter : " << badcounter << std::endl;
//   basketTree->Write();
//   basketFile->Close();
//   sbVec[0]->Print();

//   return sbVec;
// }

// std::vector<SingleBasket *> Analyzer_F::ReconstructRollingEventBasket() {
//   std::cout << "Going to Create Baskets with Rolling Event Lookup" <<
//   std::endl; std::sort(fVecOfScint_F.begin(), fVecOfScint_F.end(),
//             CompareTimestampScintillator);
//   unsigned int scintVecSize = fVecOfScint_F.size();
//   std::cout << "ScintVectSize : " << scintVecSize << std::endl;
//   SingleBasket *finalBasket = new SingleBasket();
//   std::vector<SingleBasket *> sbVec;
//   std::vector<SingleBasket *> vecOfOpenBaskets;
//   std::string outfileName =
//       "../../Data_Analysis_Outputs/Baskets/Raw/Baskets_RollingEvent_" +
//       ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) +
//       ".root";
//   TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
//   basketFile->cd();
//   TTree *basketTree = new TTree("basketTree", "basketTree");
//   basketTree->Branch("Baskets", "ismran::SingleBasket", &finalBasket);
//   ULong64_t tStart = fVecOfScint_F[0]->GetTStampSmall();
//   double_t delt = 0;
//   bool properev = true;
//   UInt_t badcounter = 0;
//   uint compval;
//   uint uniT;
//   uint sigt;
//   std::cout << "now starting" << std::endl;
//   for (unsigned int i = 0; i < scintVecSize; i++) {
//     if (i % 1000000 == 0) {
//       std::cout << " Processing event : " << i << std::endl;
//       // fVecOfScint_F[i]->Print();
//     }
//     SingleBasket *singleBasket = new SingleBasket();
//     if (vecOfOpenBaskets.size() == 0) {
//       singleBasket->push_back(new ScintillatorBar_F(*fVecOfScint_F[i]));
//       // vecOfOpenBaskets.push_back()
//     }
//   }
//   return sbVec;
// }

std::vector<SingleBasket *>
Analyzer_F::ReconstructVetoedBasket(uint numVetoLayers,
                                    std::vector<SingleBasket *> baskets) {
  std::cout << "Going to Create Baskets with " << numVetoLayers
            << " veto layers" << std::endl;
  SingleBasket *singleBasket = new SingleBasket();
  std::vector<SingleBasket *> vsbVec;

  std::string outfileName =
      "../../Data_Analysis_Outputs/Baskets/Veto/VetoBaskets_with_" +
      std::to_string(numVetoLayers) + "_VetoLayers_" +
      ismran::GetFileNameWithoutExtension(GetBaseName(fDatafileName)) + ".root";
  TFile *basketFile = new TFile(outfileName.c_str(), "RECREATE");
  basketFile->cd();
  TTree *basketTree = new TTree("basketTree", "basketTree");
  basketTree->Branch("Baskets", "ismran::SingleBasket", &singleBasket);

  ULong64_t tStart = baskets[0]->GetBasketStartTime();
  unsigned int basketVecSize = baskets.size();

  std::vector<int> VetoBarsIndx = GetJacketBarIndx(numVetoLayers);
  ushort barindex;
  bool veto = false;

  for (uint i = 0; i < basketVecSize; i++) {
    if (i % 1000000 == 0) {
      std::cout << "Analyzing Basket: " << i << std::endl;
    }
    // std::cout<<"Basket Energy "<<baskets[i]->GetBasketEnergy()<<std::endl;
    singleBasket = new SingleBasket(*baskets[i]);
    // std::cout<<"singleBasket Energy "<<singleBasket->GetBasketEnergy()<<"
    // size "<< singleBasket->size() <<std::endl;
    singleBasket->SetBasketEnergy();
    // std::cout<<"singleBasket Energy now
    // "<<singleBasket->GetBasketEnergy()<<std::endl;
    for (unsigned int j = 0; j < singleBasket->size(); j++) {
      barindex = (singleBasket->GetBasket())[j]->GetBarIndex();
      veto = ismran::IsJacket(barindex, VetoBarsIndx);
      if (veto) {
        break;
      }
    }
    if (!veto) {
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

std::vector<unsigned int>
Analyzer_F::GetPeakPosVec(std::string peakPosFileLoc) {
  return ismran::GetPeakPosVec(peakPosFileLoc,
                               ismran::GetBaseName(fDatafileName));
}
std::vector<unsigned int>
Analyzer_F::GetPeakPosVec_Direct(std::string peakPosFile) {
#ifdef VERBOSE
  std::cout << RED << "PEAK pos file : " << peakPosFile << RESET << std::endl;
#endif
  return ismran::GetPeakPosVec_Direct(".", peakPosFile);
}

// std::vector<std::shared_ptr<ScintillatorBar_F>>
// Analyzer_F::GetVectorOfScintillators()
std::vector<ScintillatorBar_F *> Analyzer_F::GetVectorOfScintillators() {
  return fVecOfScint_F;
}

std::pair<std::vector<SingleBasket *>, std::vector<SingleBasket *>>
Analyzer_F::CleanBasket(std::vector<SingleBasket *> baskets,
                        std::string fname) {
  std::string fileappend = fname.substr(fname.find("_Basket"),
                                        fname.length() - fname.find("_Basket"));
  std::string filepath = fname.substr(0, fname.find("_Pre"));
  std::string postFile = filepath + "_PostEvent" + fileappend;
  // std::cout<<postFile<<std::endl;

  SingleBasket *singleBasketA = new SingleBasket();
  SingleBasket *singleBasketB = new SingleBasket();
  std::vector<SingleBasket *> preVec;
  std::vector<SingleBasket *> postVec;

  ULong64_t tStart = baskets[0]->GetBasketStartTime();
  unsigned int basketVecSize = baskets.size();

  bool AETC;   // Basket "A" "E"nergy "T"hreshold "C"ut
  bool BETC;   // Basket "B" "E"nergy "T"hreshold "C"ut
  bool AMuC;   // Basket "A" "Mu"on "C"ut
  bool BMuC;   // Basket "B" "Mu"on "C"ut
  bool AMultC; // Basket "A" "Mult"iplicity "C"ut
  bool BMultC; // Basket "B" "Mult"iplicity "C"ut

  for (uint i = 0; i < basketVecSize - 1; i++) {
    if (i % 1000000 == 0) {
      std::cout << "Analyzing Basket: " << i << std::endl;
    }
    singleBasketA = new SingleBasket(*baskets[i]);
    singleBasketB = new SingleBasket(*baskets[i + 1]);

    /*if(i==1){
            singleBasketA->Print();
            singleBasketB->Print();
    }*/

    AETC = (singleBasketA->GetBasketEnergy() > 0.7) and
           (singleBasketA->GetBasketEnergy() < 1.3);
    BETC = (singleBasketB->GetBasketEnergy() > 6.0) and
           (singleBasketB->GetBasketEnergy() < 10.0);
    AMuC = singleBasketA->isMuonBasket();
    BMuC = singleBasketB->isMuonBasket();
    AMultC = singleBasketA->size() < 3;
    BMultC = singleBasketB->size() > 2;

    if (AETC and BETC and !AMuC and !BMuC and AMultC and BMultC) {
      preVec.push_back(new ismran::SingleBasket(*singleBasketA));
      postVec.push_back(new ismran::SingleBasket(*singleBasketB));
    }
    singleBasketA->clear();
    singleBasketB->clear();
  }
  /*
  std::cout<<"_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+"<<std::endl;
  preVec[0]->Print();
  std::cout<<"_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+"<<std::endl;
  postVec[0]->Print();
  std::cout<<"_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+"<<std::endl;
  */
  std::cout << "CleanedSBVec size : " << preVec.size() << std::endl;
  return std::make_pair(preVec, postVec);
}

std::vector<uint>
Analyzer_F::CleanBasketIndex(std::vector<SingleBasket *> baskets,
                             std::string fname) {
  std::string fileappend = fname.substr(fname.find("_Basket"),
                                        fname.length() - fname.find("_Basket"));
  std::string filepath = fname.substr(0, fname.find("_Pre"));
  std::string postFile = filepath + "_PostEvent" + fileappend;
  // std::cout<<postFile<<std::endl;

  SingleBasket *singleBasketA = new SingleBasket();
  SingleBasket *singleBasketB = new SingleBasket();
  std::vector<uint> preVec;

  ULong64_t tStart = baskets[0]->GetBasketStartTime();
  unsigned int basketVecSize = baskets.size();

  bool AETC;   // Basket "A" "E"nergy "T"hreshold "C"ut
  bool BETC;   // Basket "B" "E"nergy "T"hreshold "C"ut
  bool AMuC;   // Basket "A" "Mu"on "C"ut
  bool BMuC;   // Basket "B" "Mu"on "C"ut
  bool AMultC; // Basket "A" "Mult"iplicity "C"ut
  bool BMultC; // Basket "B" "Mult"iplicity "C"ut

  // uint j = 0;
  uint i = 0;

  for (i = 0; i < basketVecSize - 1; i++) {
    if (i % 1000000 == 0) {
      std::cout << "Analyzing Basket: " << i << std::endl;
    }
    singleBasketA = new SingleBasket(*baskets[i]);
    singleBasketB = new SingleBasket(*baskets[i + 1]);

    /*if(i==1){
            singleBasketA->Print();
            singleBasketB->Print();
    }*/

    AETC = (singleBasketA->GetBasketEnergy() > 0.7);
    BETC = (singleBasketB->GetBasketEnergy() > 6.0) and
           (singleBasketB->GetBasketEnergy() < 10.0);
    AMuC = singleBasketA->isMuonBasket();
    BMuC = singleBasketB->isMuonBasket();
    AMultC = singleBasketA->size() < 3;
    BMultC = singleBasketB->size() > 2;

    if (AETC and BETC and !AMuC and !BMuC and AMultC and BMultC) {
      preVec.push_back(i);
    }
    singleBasketA->clear();
    singleBasketB->clear();
  }

  std::cout << "_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_"
               "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+"
            << std::endl;
  std::cout << preVec[0] << std::endl;
  std::cout << "_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_"
               "+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+"
            << std::endl;

  std::cout << "CleanedSBVec size : " << preVec.size() << std::endl;
  delete singleBasketA;
  delete singleBasketB;
  return preVec;
}

std::vector<SingleBasket *>
Analyzer_F::MuonBasket(std::vector<SingleBasket *> baskets, std::string fname) {
  SingleBasket *singleBasket = new SingleBasket();
  std::vector<SingleBasket *> msbVec;

  TFile *MuonBasketFile = new TFile(fname.c_str(), "RECREATE");
  MuonBasketFile->cd();
  TTree *muonBasketTree = new TTree("muonBasketTree", "muonBasketTree");
  muonBasketTree->Branch("Muon Baskets", "ismran::SingleBasket", &singleBasket);

  ULong64_t tStart = baskets[0]->GetBasketStartTime();
  unsigned int basketVecSize = baskets.size();

  for (uint i = 0; i < basketVecSize; i++) {
    if (i % 1000000 == 0) {
      std::cout << "Analyzing Basket: " << i << std::endl;
    }
    singleBasket = new SingleBasket(*baskets[i]);

    // double BE = singleBasket->GetBasketEnergy();
    // singleBasket->SetBasketEnergy();
    // if(BE != singleBasket->GetBasketEnergy()){std::cout<<"Setting Energy is
    // Required:
    // "<<(BE-singleBasket->GetBasketEnergy())/singleBasket->GetBasketEnergy()*100.0<<std::endl;}
    // else{std::cout<<"Remove the energy check from MuonBasket()"<<std::endl;}

    if (singleBasket->isMuonBasket()) {
      msbVec.push_back(new ismran::SingleBasket(*baskets[i]));
      muonBasketTree->Fill();
    }
    singleBasket->clear();
  }
  std::cout << "MuonSBVec size : " << msbVec.size() << std::endl;
  muonBasketTree->Write();
  MuonBasketFile->Close();
  return msbVec;
}

/*std::vector<SingleAnimal *>
Analyzer_F::ReconstructAnimal(std::vector<SingleBasket *> baskets){ std::cout <<
"Going to Create Animals " << std::endl; SingleBasket *singleBasket = new
SingleBasket(); SingleAnimal *singleAnimal = new SingleAnimal();
        std::vector<SingleAnimal *> saVec;


}*/

} // namespace ismran
