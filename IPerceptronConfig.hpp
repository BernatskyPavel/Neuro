#ifndef PERCEPTRON_CONFIG
#define PERCEPTRON_CONFIG
#include <stdlib.h>

class IPerceptronConfig
{
private:
  int _N;
  int _L;

public:
  IPerceptronConfig()
    : _N(16)
    , _L(3){};
  IPerceptronConfig(int n, int l)
    : _N(n)
    , _L(l){};
  IPerceptronConfig(IPerceptronConfig const& rhs)
  {
    this->_L = rhs._L;
    this->_N = rhs._N;
  };
  int N() { return this->_N; };
  int L() { return this->_L; };
};
#endif