#include "TPM.hpp"
#include <cstring>

TPM::TPM()
{
  this->config = ITPMConfig();
  int K = this->config.K();

  this->Perceptrons = new Perceptron[K];
  IPerceptronConfig pConfig = config.ConvertToPConfig();
  for (size_t i = 0; i < K; i++) {
    this->Perceptrons[i] = Perceptron(pConfig);
  }
}

TPM::TPM(ITPMConfig config)
{
  this->config = config;
  int K = this->config.K();

  this->Perceptrons = new Perceptron[K];
  IPerceptronConfig pConfig = config.ConvertToPConfig();
  for (size_t i = 0; i < K; i++) {
    this->Perceptrons[i] = Perceptron(pConfig);
  }
}

TPM::TPM(TPM const& rhs)
{
  this->config = rhs.config;
  this->Output = rhs.Output;
  this->Perceptrons = new Perceptron[this->config.K()];
  memcpy(
    this->Perceptrons, rhs.Perceptrons, this->config.K() * sizeof(Perceptron));
}

TPM::~TPM()
{
  delete[] this->Perceptrons;
}

TPM&
TPM::operator=(TPM const& rhs)
{
  this->config = rhs.config;
  this->Output = rhs.Output;
  this->Perceptrons = new Perceptron[this->config.K()];
  memcpy(
    this->Perceptrons, rhs.Perceptrons, this->config.K() * sizeof(Perceptron));
  return *this;
}

int
TPM::GetOutput(int** AInputs, size_t x, size_t y)
{
  if (x != this->config.K() || y != this->config.N()) {
    return -1;
  }

  this->Output = 1;
  for (size_t i = 0; i < this->config.K(); i++) {
    this->Output *= this->Perceptrons[i].GetOutput(AInputs[i]);
  }
  return this->Output;
}

void
TPM::Synchronize(int OutputTPM)
{
  if (this->Output == OutputTPM) {
    for (size_t i = 0; i < this->config.K(); i++) {
      this->Perceptrons[i].AktualizeWieghts(this->Output);
    }
  }
}

int
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

int**
TPM::GetWeightMatrix()
{
  int** matrix = new int*[this->config.K()];
  for (size_t i = 0; i < this->config.K(); i++) {
    matrix[i] = this->Perceptrons[i].GetWeights();
  }
  return matrix;
}