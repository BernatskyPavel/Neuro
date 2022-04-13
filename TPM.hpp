#pragma once
#include "ITPMConfig.hpp"
#include "Perceptron.hpp"

class TPM
{
  ITPMConfig config;
  Perceptron* Perceptrons;
  int32_t Output;

public:
  TPM();
  TPM(ITPMConfig config);
  ~TPM();
  ITPMConfig GetConfig();
  int32_t GetOutput(int32_t** AInputs, size_t x, size_t y);
  void Synchronize();
  int32_t Distance(const TPM& ATPM);
  void ModifyOutput(int32_t AOutput) { Output = AOutput; }
  int32_t** GetWeightMatrix();
};