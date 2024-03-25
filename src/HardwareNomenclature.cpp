/*
**	Filename : HardWareNomenclature.cpp
**	2021-09-25
**	username : rsehgal
*/

#include "HardwareNomenclature.h"
#include "PsBar.h"

namespace ismran {
/*
 * Refernce bar names in sequence
 */
std::vector<std::string> vecOfBarsNamess = {
//std::vector<std::string> vecOfPsBars = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520",  "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS55_S1AA6646", "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS64_S3AA1787", "PS65_S3AA1782", "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890",    "PS84_SF882",
    "PS85_SF881",    "PS86_SF884",    "PS87_SF876",    "PS88_SF880",    "PS89_SF873",    "PS90_SF875",
    "PS_91","PS_92","PS_93","PS_94","PS_95","PS_96"};

std::vector<std::string> sequentialBarNames = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520",  "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS55_S1AA6646", "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS64_S3AA1787", "PS65_S3AA1782", "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890",    "PS84_SF882",
    "PS85_SF881",    "PS86_SF884",    "PS87_SF876",    "PS88_SF880",    "PS89_SF873",    "PS90_SF875",
    "PS_91","PS_92","PS_93","PS_94","PS_95","PS_96"};

std::vector<unsigned int> vecOfPeakPos;/* = {
    11900, 11400, 12250, 11000, 11600, 12300, 11700, 11900, 11600, 11900, 12500, 12500, 11700, 11400, 12000,
    11800, 12200, 12000, 11200, 11500, 11400, 11000, 11600, 11500, 12000, 10950, 11700, 11400, 12100, 11400,
    11800, 12100, 11200, 11600, 11600, 11800, 11500, 10900, 11600, 12500, 11600, 11400, 11900, 11800, 12600,
    11800, 12500, 12300, 11000, 11500, 12000, 11400, 11200, 11500, 11600, 11600, 11500, 11600, 11700, 11300,
    11800, 11700, 11800, 11500, 11300, 11500, 11400, 11200, 11300, 11400, 13500, 12600, 12700, 9700,  9700,
    7000,  10500, 10000, 9600,  7100,  9450,  9600,  10500, 9200,  9600,  10100, 9750,  5000,  9800,  11600,
    //6 dummy values
    9600,  10100, 9750,  5000,  9800,  11600};*/

//Dhurva Mapping
//Physical Map
/*  
    //DO NOT APPLY CLANG-FORMATTING
    "L--0", "L--1", "L--2", "L--3", "L--4", "L--5", "L--6", "L--7", "L--8", "L--9"
    "PS51", "PS52", "PS53", "PS54", "PS55", "PS56", "PS57", "PS58", "PS84", "PS85"
    "PS88", "PS59", "PS60", "PS61", "PS62", "PS63", "PS30", "PS29", "PS74", "PS75"
    "PS87", "PS10", "PS08", "PS64", "PS66", "PS68", "PS20", "PS18", "PS77", "PS76",
    "PS86", "PS07", "PS09", "PS65", "PS67", "PS69", "PS70", "PS19", "PS78", "PS79",
    "PS41", "PS42", "PS43", "PS44", "PS45", "PS46", "PS47", "PS48", "PS49", "PS50", 
    "PS31", "PS32", "PS33", "PS34", "PS35", "PS36", "PS37", "PS38", "PS39", "PS40", 
    "PS05", "PS06", "PS80", "PS81", "PS82", "PS83", "PS90", "PS72", "PS01", "PS02",
    "PS03", "PS04", "PS13", "PS14", "PS15", "PS16", "PS17", "PS89", "PS27", "PS28",
    "PS71", "PS73", "PS11", "PS12", "PS21", "PS22", "PS23", "PS24", "PS25", "PS26",
    "PS91","PS92","PS93","PS94","PS95","PS96"
*/

//H9
/*std::vector<std::string> vecOfPsBars = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520",  "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS55_S1AA6646", "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS64_S3AA1787", "PS65_S3AA1782", "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890",    "PS84_SF882",
    "PS85_SF881",    "PS86_SF884",    "PS87_SF876",    "PS88_SF880",    "PS89_SF873",    "PS90_SF875",
    "PS_91","PS_92","PS_93","PS_94","PS_95","PS_96"};
*/
//Dhruva
  //std::vector<std::string> vecOfBarsNamess = {
#ifdef VERTICAL_ARRANGEMENT
  std::vector<std::string> vecOfPsBars = {
    "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645", "PS55_S1AA6646", "PS56_S1AA6647",
    "PS57_S1AA6705", "PS58_S1AA6712", "PS84_SF882",    "PS85_SF881",    "PS88_SF880",    "PS59_S1AA6640",
    "PS60_S1AA6641", "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS30_S2AB0714", "PS29_S1AA6521",
    "PS74_SF891",    "PS75_SF887",    "PS87_SF876",    "PS10_S2AB1012", "PS08_S3AA1784", "PS64_S3AA1787",
    "PS66_S1AA6639", "PS68_S3AA1780", "PS20_S2AB0718", "PS18_S1AA6526", "PS77_SF892",    "PS76_SF888",
    "PS86_SF884",    "PS07_S3AA1786", "PS09_S2AB1016", "PS65_S3AA1782", "PS67_S1AA6709", "PS69_S3AA1777",
    "PS70_S3AA1785", "PS19_S2AB0715", "PS78_SF886",    "PS79_SF883",    "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708",
    "PS35_S1AA6520",  "PS36_S1AA6704", "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", // PS1
    "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516", "PS25_S2AB0717", "PS26_S2AB0712",
    "PS27_S2AB0709", "PS28_S3AA1788", "PS71_SF874",    "PS73_SF878",    "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS89_SF873",
    "PS90_SF875",    "PS72_SF889",    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007",
    "PS05_S2AB1006", "PS06_S2AB1013", "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890"};
#else
std::vector<std::string> vecOfPsBars = {
    "PS01_S2AB1017", "PS02_S2AB1005", "PS03_S3AA1783", "PS04_S2AB1007", "PS05_S2AB1006", "PS06_S2AB1013",
    "PS07_S3AA1786", "PS08_S3AA1784", "PS09_S2AB1016", "PS10_S2AB1012", "PS11_S2AB1015", "PS12_S2AB1004",
    "PS13_S2AB1010", "PS14_S2AB1014", "PS15_S2AB1011", "PS16_S2AB1009", "PS17_S1AA6527", "PS18_S1AA6526",
    "PS19_S2AB0715", "PS20_S2AB0718", "PS21_S2AB0716", "PS22_S2AB1008", "PS23_S1AA6518", "PS24_S1AA6516",
    "PS25_S2AB0717", "PS26_S2AB0712", "PS27_S2AB0709", "PS28_S3AA1788", "PS29_S1AA6521", "PS30_S2AB0714",
    "PS31_S2AB0713", "PS32_S2AB0710", "PS33_S2AB0711", "PS34_S2AB0708", "PS35_S1AA6520",  "PS36_S1AA6704",
    "PS37_S1AA6710", "PS38_S1AA6711", "PS39_S1AA6706", "PS40_S1AA6707", "PS41_S1AA6519", "PS42_S1AA6522",
    "PS43_S1AA6523", "PS44_S1AA6524", "PS45_S1AA6525", "PS46_S1AA6643", "PS47_S1AA6648", "PS48_S1AA6708",
    "PS49_S1AA6642", "PS50_S1AA6517", "PS51_S1AA6644", "PS52_S1AA6515", "PS53_S1AA6713", "PS54_S1AA6645",
    "PS55_S1AA6646", "PS56_S1AA6647", "PS57_S1AA6705", "PS58_S1AA6712", "PS59_S1AA6640", "PS60_S1AA6641",
    "PS61_S3AA1779", "PS62_S3AA1781", "PS63_S3AA1778", "PS64_S3AA1787", "PS65_S3AA1782", "PS66_S1AA6639",
    "PS67_S1AA6709", "PS68_S3AA1780", "PS69_S3AA1777", "PS70_S3AA1785", "PS71_SF874",    "PS72_SF889",
    "PS73_SF878",    "PS74_SF891",    "PS75_SF887",    "PS76_SF888",    "PS77_SF892",    "PS78_SF886",
    "PS79_SF883",    "PS80_SF877",    "PS81_SF879",    "PS82_SF885",    "PS83_SF890",    "PS84_SF882",
    "PS85_SF881",    "PS86_SF884",    "PS87_SF876",    "PS88_SF880",    "PS89_SF873",    "PS90_SF875",
    "PS_91","PS_92","PS_93","PS_94","PS_95","PS_96"};

#endif
unsigned int GetIndexFromBarName(std::string barName)
{
  auto it            = find(vecOfBarsNamess.begin(), vecOfBarsNamess.end(), barName);
  unsigned int index = 10000;
  // If element was found
  if (it != vecOfBarsNamess.end()) {
    // calculating the index of barName
    index = it - vecOfBarsNamess.begin();
    // cout << index << endl;
  }
  return index;
}

unsigned int GetIndexFromBarName(std::vector<std::string> vecofbarnames, std::string barName)
{
  auto it            = find(vecofbarnames.begin(), vecofbarnames.end(), barName);
  unsigned int index = 10000;
  // If element was found
  if (it != vecofbarnames.end()) {
    // calculating the index of barName
    index = it - vecofbarnames.begin();
    // cout << index << endl;
  }
  return index;
}


unsigned int GetPeakPos(std::string barName)
{
  std::vector<std::string>::iterator it;
  unsigned int peakPos = 0;
  it                   = std::find(sequentialBarNames.begin(), sequentialBarNames.end(), barName);
  if (it != sequentialBarNames.end()) {
    unsigned int index = it - sequentialBarNames.begin();
    peakPos            = vecOfPeakPos[index];
  }
  return peakPos;
}

std::vector<int> GetJacketBarIndx(ushort numLayers){
	std::vector<int> vecOfJacketBars;
	for(int l=0;l<numLayers;l++){
		int lvalmin=l;
		int lvalmax=8-l;
		for(int i=lvalmin;i<=lvalmax;i++){
			vecOfJacketBars.push_back(10*i+lvalmin);
			vecOfJacketBars.push_back(10*(i+1)-(lvalmin+1));
			if(i!=lvalmin){
				vecOfJacketBars.push_back(10*lvalmax+i);
				vecOfJacketBars.push_back(10*lvalmin+i);
			}
		}
	}
	std::sort(vecOfJacketBars.begin(),vecOfJacketBars.end());
	std::cout<<"veto Bars Index: ";
	for(auto x:vecOfJacketBars){std::cout<<x<<" ";}
	std::cout<<" "<<std::endl;
	return vecOfJacketBars;
}


bool IsJacket(ushort barIndx, std::vector<int> vecOfVetoBarIndx)
{
	bool isjacket = false;
	unsigned int barIndex = barIndx;
	auto it            = find(vecOfVetoBarIndx.begin(),vecOfVetoBarIndx.end(),barIndex);
	//std::cout << "IsJacket Iterator " << it - vecOfVetoBarIndx.begin() <<std::endl;
	if (it != vecOfVetoBarIndx.end()){
		isjacket = true;
		//std::cout << vecOfBarsNamess[barIndx] << " " << barIndex << " "<< barIndx << std::endl;
	}
	//std::cout << "IsJacket Iterator " << it - vecOfVetoBarIndx.begin() << " value " << isjacket <<std::endl;
	return isjacket;
}

} // namespace ismran
