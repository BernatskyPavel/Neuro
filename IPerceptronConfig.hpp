#ifndef PERCEPTRON_CONFIG
#define PERCEPTRON_CONFIG
#include <stdlib.h>

class IPerceptronConfig
{
private:
  u_int32_t _N;
  int32_t _L;

public:
  IPerceptronConfig()
    : _N(16)
    , _L(3){};
  IPerceptronConfig(u_int32_t n, int32_t l)
    : _N(n)
    , _L(l){};
  u_int32_t N() { return this->_N; };
  int32_t L() { return this->_L; };
};
#endif