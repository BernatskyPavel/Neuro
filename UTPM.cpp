#include "UTPM.hpp"

int
TPM::GetOutput(int AInputs[K][N])
{
  this->Output = 0;
  for (size_t i = 0; i < K; i++) {
    this->Output *= this->Perceptrons[i].GetOutput(AInputs[i]);
  }
  return this->Output;
}

void
TPM::Synchronize()
{
  for (size_t i = 0; i < K; i++) {
    this->Perceptrons[i].AktualizeWieghts(this->Output);
  }
}

int
TPM::Distance(const TPM& ATPM)
{
  int Result = 0;
  for (size_t i = 0; i < K; i++) {
    Result += this->Perceptrons[i].Distance(ATPM.Perceptrons[i]);
  }
  return Result;
}