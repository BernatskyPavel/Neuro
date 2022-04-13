#ifndef UTPMH
#define UTPMH
#include "UPerceptron.hpp"

const int K = 3;
const int L = 3;
const int N = 16;

class TPM
{
  Perceptron Perceptrons[K];
  int Output;

public:
  int GetOutput(int AInputs[K][N]);
  void Synchronize();
  int Distance(const TPM& ATPM);
  void ModifyOutput(int AOutput) { Output = AOutput; }
};

#endif