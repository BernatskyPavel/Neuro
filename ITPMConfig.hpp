#pragma once
#include "IPerceptronConfig.hpp"
#include <stdlib.h>

class ITPMConfig
{
protected:
  u_int32_t _N;
  u_int32_t _K;
  int32_t _L;

public:
  ITPMConfig()
    : _N(16)
    , _K(3)
    , _L(3){};
  ITPMConfig(u_int32_t n, u_int32_t k, int32_t l)
    : _N(n)
    , _K(k)
    , _L(l){};
  IPerceptronConfig ConvertToPConfig()
  {
    return IPerceptronConfig(this->_N, this->_L);
  }

  u_int32_t N() { return this->_N; };
  u_int32_t K() { return this->_K; };
  int32_t L() { return this->_L; };
};