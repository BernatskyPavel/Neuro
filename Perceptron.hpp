#ifndef PERCEPTRON
#define PERCEPTRON
#pragma once
#include "IPerceptronConfig.hpp"
#include <stdlib.h>

class Perceptron
{
  IPerceptronConfig config;
  int32_t* Weights;
  int32_t* Inputs;
  int32_t Output;
  void RandomWeights();

public:
  Perceptron();
  Perceptron(IPerceptronConfig config);
  ~Perceptron();
  int32_t GetOutput(int32_t* AInputs);
  void AktualizeWieghts(int32_t OutputTPM);
  int32_t Distance(const Perceptron& p);
  int32_t* GetWeights();
};
#endif
