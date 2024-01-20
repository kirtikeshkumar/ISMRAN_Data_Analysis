{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Fri Sep 29 11:42:23 2023 by ROOT version6.28/00)
//   from TTree ftree/V1730-digiTES4.10.5
//   found on file: ISMRAN_digiROOT_RON_01hrs00mins00secs_18Aug2023_Run210.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
   gROOT->Reset();
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ISMRAN_digiROOT_RON_01hrs00mins00secs_18Aug2023_Run210.root");
   if (!f) {
      f = new TFile("ISMRAN_digiROOT_RON_01hrs00mins00secs_18Aug2023_Run210.root");
   }
    f->GetObject("ftree",tree);

//Declaration of leaves types
   UShort_t        fBrCh;
   ULong64_t       fTstamp;
   UInt_t          fTime;
   UInt_t          fQlong;
   Int_t           fDelt;

   // Set branch addresses.
   ftree->SetBranchAddress("fBrCh",&fBrCh);
   ftree->SetBranchAddress("fTstamp",&fTstamp);
   ftree->SetBranchAddress("fTime",&fTime);
   ftree->SetBranchAddress("fQlong",&fQlong);
   ftree->SetBranchAddress("fDelt",&fDelt);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// ftree->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = ftree->GetEntries();

   Long64_t nbytes = 0;
//   for (Long64_t i=0; i<nentries;i++) {
//      nbytes += ftree->GetEntry(i);
//   }
}
