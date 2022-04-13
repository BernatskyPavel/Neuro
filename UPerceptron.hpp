#ifndef UPerceptronH
#define UPerceptronH
#include <stdlib.h>

class Perceptron
{
  int* Weights;
  int* Inputs;
  int Output;
  void RandomWeights();

public:
  Perceptron();
  ~Perceptron();
  int GetOutput(int* AInputs);
  void AktualizeWieghts(int OutputTPM);
  int Distance(const Perceptron& p);
};

#endif