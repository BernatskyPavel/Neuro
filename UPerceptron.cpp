#include "UPerceptron.hpp"
#include "UTPM.hpp"
#include <random>
//#pragma package(smart_init)

Perceptron::Perceptron()
{
  this->Weights = new int[N];
  RandomWeights();
}

Perceptron::~Perceptron()
{
  delete[] this->Weights;
}

int
Perceptron::GetOutput(int* AInputs)
{
  this->Inputs = AInputs;
  this->Output = 0;
  for (size_t i = 0; i < N; i++) {
    this->Output += this->Inputs[i] * this->Weights[i];
  }
  this->Output = this->Output >= 0 ? 1 : -1;
  return this->Output;
}

void
Perceptron::RandomWeights()
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution dist(0, 2 * L);

  for (size_t i = 0; i < N; i++) {
    this->Weights[i] = L - dist(rng);
  }
}

void
Perceptron::AktualizeWieghts(int OutputTPM)
{
  if (this->Output == OutputTPM) {
    for (size_t i = 0; i < N; i++) {
      this->Weights[i] += this->Output * this->Inputs[i];
      if (this->Weights[i] > L) {
        this->Weights[i] = L;
      } else if (this->Weights[i] < -L) {
        this->Weights[i] = -L;
      }
    }
  }
}

int
Perceptron::Distance(const Perceptron& P)
{
  int Result = 0;
  for (size_t i = 0; i < N; i++) {
    Result += abs(this->Weights[i] - P.Weights[i]);
  }
  return Result;
}
