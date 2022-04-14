#pragma once
#include "IPerceptronConfig.hpp"
#include <stdlib.h>

class ITPMConfig
{
protected:
  int _K;
  int _N;
  int _L;

public:
  ITPMConfig()
    : _K(3)
    , _N(16)
    , _L(3){};
  ITPMConfig(int k, int n, int l)
    : _K(k)
    , _N(n)
    , _L(l){};
  ITPMConfig(ITPMConfig const& rhs)
  {
    this->_L = rhs._L;
    this->_N = rhs._N;
    this->_K = rhs._K;
  };
  IPerceptronConfig ConvertToPConfig()
  {
    return IPerceptronConfig(this->_N, this->_L);
  }

  int N() { return this->_N; };
  int K() { return this->_K; };
  int L() { return this->_L; };
};