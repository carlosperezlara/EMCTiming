//====C++
#include <iostream>
#include <fstream>
#include <vector>
//===ROOT
#include "TLorentzVector.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TF1.h"
#include "TList.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TMath.h"
#include "TRandom3.h"
//===OTHERS
#include "PbScIndexer.h"
#include "PbScIndexer.C"
#include "PbGlIndexer.h"
#include "PbGlIndexer.C"
#include "EmcIndexer.h"
#include "EmcIndexer.C"

using namespace std;

const double kSpeedOfLightinNS = 29.979245829979; //[cm/ns]
const int kNTWRS = 24768;
unsigned int kBBCnc = 0x00000008;
unsigned int kBBCn  = 0x00000010;

TTree *fTree;

typedef struct MyTreeRegister2 {
  Float_t vtxZ;
  Float_t cent;
  Float_t bbct;
  Float_t bbctmin;
  Float_t bbctmax;
  Float_t frac;
  UInt_t  trig;
} MyTreeRegister2_t;
MyTreeRegister2_t fGLB;

std::vector<Int_t> *pEMCtwrid;
std::vector<Int_t> *pEMCtdc;
std::vector<Int_t> *pEMCadc;
std::vector<Float_t> *pEMClen;
std::vector<Float_t> *pEMCene;
