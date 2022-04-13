#include "TPM.hpp"

TPM::TPM()
{
  this->config = ITPMConfig();
  u_int32_t K = this->config.K();

  this->Perceptrons = new Perceptron[K];
  IPerceptronConfig pConfig = config.ConvertToPConfig();
  for (size_t i = 0; i < K; i++) {
    this->Perceptrons[i] = Perceptron(pConfig);
  }
}

TPM::TPM(ITPMConfig config)
{
  this->config = config;
  u_int32_t K = this->config.K();

  this->Perceptrons = new Perceptron[K];
  IPerceptronConfig pConfig = config.ConvertToPConfig();
  for (size_t i = 0; i < K; i++) {
    this->Perceptrons[i] = Perceptron(pConfig);
  }
}

TPM::~TPM()
{
  delete[] this->Perceptrons;
}

int32_t
TPM::GetOutput(int** AInputs, size_t x, size_t y)
{
  if (x != this->config.K() || y != this->config.N()) {
    return -1;
  }

  this->Output = 0;
  for (size_t i = 0; i < this->config.K(); i++) {
    this->Output *= this->Perceptrons[i].GetOutput(AInputs[i]);
  }
  return this->Output;
}

void
TPM::Synchronize()
{
  for (size_t i = 0; i < this->config.K(); i++) {
    this->Perceptrons[i].AktualizeWieghts(this->Output);
  }
}

int32_t
TPM::Distance(const TPM& ATPM)
{
  int Result = 0;
  for (size_t i = 0; i < this->config.K(); i++) {
    Result += this->Perceptrons[i].Distance(ATPM.Perceptrons[i]);
  }
  return Result;
}

ITPMConfig
TPM::GetConfig()
{
  return this->config;
}

int32_t**
TPM::GetWeightMatrix()
{
  int32_t** matrix = new int32_t*[this->config.K()];
  for (size_t i = 0; i < this->config.K(); i++) {
    matrix[i] = this->Perceptrons[i].GetWeights();
  }
  return matrix;
}