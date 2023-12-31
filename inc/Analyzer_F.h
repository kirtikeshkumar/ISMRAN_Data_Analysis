/*
**	Filename : Analyzer_F.h
**	2021-10-06
**	username : rsehgal
*/
#ifndef Analyzer_F_h
#define Analyzer_F_h

#include <vector>
#include <string>

namespace ismran {

class ScintillatorBar_F;

class Analyzer_F {

private:
  std::string fDatafileName;
  std::vector<ScintillatorBar_F *> fVecOfScint_F;

public:
  Analyzer_F();
  Analyzer_F(std::string datafilename);
  ~Analyzer_F();
  void LoadData();
  std::vector<ScintillatorBar_F *> GetVectorOfScintillators();
};
} // namespace ismran

#endif
