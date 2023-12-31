/*
 * PsBar.cpp
 *
 *  Created on: 14-Aug-2020
 *      Author: rsehgal
 */

#include "PsBar.h"
bool IsSimulation     = false;
const int offset      = 0;
const double kDelTBar = 32.0; //! ns
TStopwatch timer;
unsigned int numOfLayers          = 10;
unsigned int numOfBarsInEachLayer = 9;
double fwhm                       = 2.355 * 5.66353;
std::map<std::string, TH1D *> barsEnergyMap;
std::vector<TH1D *> vecOfEnergyHist;
std::vector<TH1D *> vecOfTimeDiffHist;
std::vector<unsigned int> vecOfdeltaTMin;
std::vector<unsigned int> vecOfdeltaTMax;
double qmeanCorrThreshold                  = 15.;
double qmeanCorrThresholdUpper             = 25.;
int qstart                                 = 3000;
int qend                                   = 25000;
int nbins                                  = 1000;
int timeDiffNearFar                        = 12000; // ps
unsigned long int timeBetweenTwoMuonTracks = 3e+9;
;
int muonEnergyPeak                            = 21000;
int minEnergyDepositedByMuonTrack             = 170000;
int maxEnergyDepositedByMuonTrack             = 190000;
float barWidth                                = 10.;
float barHeight                               = 10.;
float barLength                               = 100.;
std::vector<unsigned int> vecOfRequiredLayers = {0, 1, 2, 3, 7, 8, 9};
// std::vector<unsigned int> vecOfRequiredLayers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
// std::vector<unsigned int> vecOfRequiredLayers={7,8,9};
// std::vector<unsigned int> vecOfRequiredLayers = {0,1,2};
// std::vector<unsigned int> vecOfRequiredLayers={0,2,3,4,7,8,9};
std::vector<unsigned int> vecOfAntiCoincideneScint = {55, 56, 57, 58, 59, 60, 61, 50};
double xyzLimit                                    = 60.;

/*
 * Ref Y is the slab of Scatterer
 * Y of all the detector should be with respect to  Scatterer Slab.
 */
double scattererPlaneY                         = 0.;
float offsetYLowerDetectors                    = -53; //-20.;
float offsetYUpperDetectors                    = 28;  // 50.;
unsigned int numOfLowerLayers                  = 7;
unsigned int numOfUpperLayers                  = 3;
std::vector<unsigned int> incomingLayerIndices = {9, 8, 7}; //{7,6,5};
std::vector<unsigned int> outgoingLayerIndices = {4, 3, 2, 1, 0};

double errorX = 5.;
double errorY = 0.000005;

double errorX_Exact = 0.000005;
double errorY_Exact = 0.000005;
double errorZ_Exact = 0.000005;

double errorX_Smeared = 5.;
double errorY_Smeared = 0.000005;
double errorZ_Smeared = 10.;

std::vector<double> zCorrOffsetVector = {-19.24, -14.6, -9.76, -4.84, 0.145, 5.28, 10.27, 14.57, 18.7};

unsigned short exactTrack   = 1;
unsigned short smearedTrack = 2;

bool planeXY = true;
bool planeZY = false;
// std::string FileFrag[]={
/*
std::vector<std::string> vecOfBarsName={
  "PS01_S2AB1017","PS02_S2AB1005","PS03_S3AA1783","PS04_S2AB1007","PS05_S2AB1006",
  "PS06_S2AB1013","PS07_S3AA1786","PS08_S3AA1784","PS09_S2AB1016","PS10_S2AB1012",
  "PS11_S2AB1015","PS12_S2AB1004","PS13_S2AB1010","PS14_S2AB1014","PS15_S2AB1011",
  "PS16_S2AB1009","PS17_S1AA6527","PS18_S1AA6526","PS19_S2AB0715","PS20_S2AB0718",
  "PS21_S2AB0716","PS22_S2AB1008","PS23_S1AA6518","PS24_S1AA6516","PS25_S2AB0717",
  "PS26_S2AB0712","PS27_S2AB0709","PS28_S3AA1788","PS29_S1AA6521","PS30_S2AB0714",
  "PS31_S2AB0713","PS32_S2AB0710","PS33_S2AB0711","PS34_S2AB0708","PS35_S1AA6520",
  "PS36_S1AA6704","PS37_S1AA6710","PS38_S1AA6711","PS39_S1AA6706","PS40_S1AA6707",
  "PS41_S1AA6519","PS42_S1AA6522","PS43_S1AA6523","PS44_S1AA6524","PS45_S1AA6525",
  "PS46_S1AA6643","PS47_S1AA6648","PS48_S1AA6708","PS49_S1AA6642","PS50_S1AA6517",
  "PS51_S1AA6644","PS52_S1AA6515","PS53_S1AA6713","PS54_S1AA6645","PS55_S1AA6646",
  "PS56_S1AA6647","PS57_S1AA6705","PS58_S1AA6712","PS59_S1AA6640","PS60_S1AA6641",
  "PS61_S3AA1779","PS62_S3AA1781","PS63_S3AA1778","PS64_S3AA1787","PS65_S3AA1782",
  "PS66_S1AA6639","PS67_S1AA6709","PS68_S3AA1780","PS69_S3AA1777","PS70_S3AA1785",
  "PS71_SF874"   ,"PS72_SF889"   ,"PS73_SF878"   ,"PS74_SF891"   ,"PS75_SF887" ,
  "PS76_SF888"   ,"PS77_SF892"   ,"PS78_SF886"   ,"PS79_SF883"   ,"PS80_SF877" ,
  "PS81_SF879"   ,"PS82_SF885"   ,"PS83_SF890"   ,"PS84_SF882"   ,"PS85_SF881" ,
  "PS86_SF884"   ,"PS87_SF876"   ,"PS88_SF880"   ,"PS89_SF873"   ,"PS90_SF875"
};
*/

std::vector<std::string> vecOfBarsName = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520", "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS82_SF885",    "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS83_SF890",    "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS88_SF880",    "PS89_SF873",    "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879"

    //,   ,   ,"PS84_SF882"   ,"PS85_SF881" ,  "PS86_SF884"   ,"PS87_SF876"   ,   ,   ,"PS90_SF875"
    //"PS46_S1AA6643" ->  "PS82_SF885" , "PS55_S1AA6646" -> "PS83_SF890", "PS64_S3AA1787 ->
    //"PS88_SF880"","PS65_S3AA1782" -> "PS89_SF873"
};
// std::vector<ScintillatorBar*> eventsVec2={};

/*void PrintPsBarVector(){
  std::cout <<"6666666666 Printing from PrintPsBarVector 66666666" << std::endl;
  for(unsigned int i = 0 ; i < eventsVec2.size(); i++){
    eventsVec2[i]->Print();
  }
}*/

namespace Tomography {

PsBar::PsBar()
{
  // TODO Auto-generated constructor stub
}

PsBar::~PsBar()
{
  // TODO Auto-generated destructor stub
}

} /* namespace Tomography */
