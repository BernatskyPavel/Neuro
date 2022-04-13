#include "TPM.hpp"
#include <iostream>
#include <random>
#include <wchar.h>

int
main(int argc, char const* argv[])
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution dist(-1, 1);

  TPM tpm = TPM(), tpm2 = TPM();
  ITPMConfig config = tpm.GetConfig();
  int32_t O = 0, O2 = 0;
  do {
    int32_t** inputs = new int32_t*[config.K()];
    for (size_t i = 0; i < config.K(); i++) {
      inputs[i] = new int32_t[config.N()];
      for (size_t j = 0; j < config.N(); j++) {
        int temp = dist(rng);
        while (temp == 0) {
          temp = dist(rng);
        }
        inputs[i][j] = temp;
      }
    }

    O = tpm.GetOutput(inputs, config.K(), config.N());
    O2 = tpm2.GetOutput(inputs, config.K(), config.N());
    if (O == O2) {
      break;
    }
    tpm.ModifyOutput(O2);
    tpm2.ModifyOutput(O);
    tpm.Synchronize();
    tpm2.Synchronize();
  } while (O != O2);

  int32_t** m1 = tpm.GetWeightMatrix();
  int32_t** m2 = tpm2.GetWeightMatrix();

  for (size_t i = 0; i < config.K(); i++) {
    for (size_t j = 0; j < config.N(); j++) {
      std::wcout << m1[i][j] << L' ';
    }
    std::wcout << L'\n';
  }

  for (size_t i = 0; i < config.K(); i++) {
    for (size_t j = 0; j < config.N(); j++) {
      std::wcout << m2[i][j] << L' ';
    }
    std::wcout << L'\n';
  }

  delete[] m1;
  delete[] m2;

  return 0;
}
