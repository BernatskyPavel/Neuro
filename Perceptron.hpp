#ifndef PERCEPTRON
#define PERCEPTRON
#pragma once
#include "IPerceptronConfig.hpp"
#include <stdlib.h>

class Perceptron
{
  IPerceptronConfig config;
  int* Weights;
  int* Inputs;
  int Output;
  void RandomWeights();

public:
  Perceptron();
  Perceptron(IPerceptronConfig config);
  Perceptron(Perceptron const& rhs);
  ~Perceptron();
  Perceptron& operator=(Perceptron const& rhs);
  int GetOutput(int* AInputs);
  void AktualizeWieghts(int OutputTPM);
  int Distance(const Perceptron& p);
  int* GetWeights();
};
#endif
