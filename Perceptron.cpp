#include "Perceptron.hpp"
#include <cstring>
#include <random>
//#pragma package(smart_init)

Perceptron::Perceptron()
{
  this->config = IPerceptronConfig();
  this->Weights = new int[this->config.N()];
  RandomWeights();
}

Perceptron::Perceptron(IPerceptronConfig config)
{
  this->config = config;
  this->Weights = new int[this->config.N()];
  RandomWeights();
}

Perceptron::Perceptron(Perceptron const& rhs)
{
  this->config = rhs.config;
  this->Output = rhs.Output;
  this->Weights = new int[this->config.N()];
  this->Inputs = new int[this->config.N()];
  memcpy(this->Weights, rhs.Weights, this->config.N() * sizeof(int));
  memcpy(this->Inputs, rhs.Inputs, this->config.N() * sizeof(int));
}

Perceptron::~Perceptron()
{
  delete[] this->Weights;
}

Perceptron&
Perceptron::operator=(Perceptron const& rhs)
{
  this->config = rhs.config;
  this->Output = rhs.Output;
  this->Weights = new int[this->config.N()];
  this->Inputs = new int[this->config.N()];
  memcpy(this->Weights, rhs.Weights, this->config.N() * sizeof(int));
  memcpy(this->Inputs, rhs.Inputs, this->config.N() * sizeof(int));
  return *this;
}

int
Perceptron::GetOutput(int* AInputs)
{
  this->Inputs = AInputs;
  this->Output = 0;
  for (size_t i = 0; i < this->config.N(); i++) {
    this->Output += this->Inputs[i] * this->Weights[i];
  }
  this->Output = this->Output > 0 ? 1 : -1;
  return this->Output;
}

void
Perceptron::RandomWeights()
{
  std::random_device dev;
  std::mt19937 rng(dev());
  int _L = this->config.L();
  std::uniform_int_distribution<int> dist(-_L, _L);

  for (size_t i = 0; i < this->config.N(); i++) {
    this->Weights[i] = dist(rng);
  }
}

void
Perceptron::AktualizeWieghts(int OutputTPM)
{
  int _L = this->config.L();
  if (this->Output == OutputTPM) {
    for (size_t i = 0; i < this->config.N(); i++) {
      this->Weights[i] += this->Output * this->Inputs[i];
      if (this->Weights[i] > _L) {
        this->Weights[i] = _L;
      } else if (this->Weights[i] < -_L) {
        this->Weights[i] = -_L;
      }
    }
  }
}

int
Perceptron::Distance(const Perceptron& P)
{
  int Result = 0;
  for (size_t i = 0; i < this->config.N(); i++) {
    Result += abs(this->Weights[i] - P.Weights[i]);
  }
  return Result;
}

int*
Perceptron::GetWeights()
{
  return this->Weights;
}