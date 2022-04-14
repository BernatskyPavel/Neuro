#pragma once
#include "ITPMConfig.hpp"
#include "Perceptron.hpp"

class TPM
{
  ITPMConfig config;
  Perceptron* Perceptrons;
  int Output;

public:
  TPM();
  TPM(ITPMConfig config);
  TPM(TPM const& rhs);
  ~TPM();
  TPM& operator=(TPM const& rhs);
  ITPMConfig GetConfig();
  int GetOutput(int** AInputs, size_t x, size_t y);
  void Synchronize(int OutputTPM);
  int Distance(const TPM& ATPM);
  void ModifyOutput(int AOutput) { Output = AOutput; }
  int** GetWeightMatrix();
};