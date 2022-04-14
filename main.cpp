#include "TPM.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <wchar.h>

int
main(int argc, char const* argv[])
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> dist(-1, 1);

  ITPMConfig conf = ITPMConfig(3, 16, 3);

  int step = 0;
  int O = 0, O2 = 0;

  std::map<int, int, std::less<int>> stats;

  for (int it = 0; it < 100; it++) {
    TPM tpm = TPM(conf), tpm2 = TPM(conf);
    ITPMConfig config = tpm.GetConfig();
    do {
      int** inputs = new int*[config.K()];
      for (size_t i = 0; i < config.K(); i++) {
        inputs[i] = new int[config.N()];
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
      tpm.Synchronize(O2);
      tpm2.Synchronize(O);
      // m1 = tpm.GetWeightMatrix();
      // m2 = tpm2.GetWeightMatrix();
      step += 1;

      //} while (!areMatrixEquals(m1, config.K(), config.N(), m2, config.K(),
      // config.N()));

    } while (tpm.Distance(tpm2) != 0);

    int key = (step / 10) * 10;
    auto element = stats.find(key);

    if (element != stats.end()) {
      element->second += 1;
    } else {
      stats.insert(std::pair<int, int>(key, 1));
    }

    // std::wcout << L"Steps: " << step << L'\n';
    step = 0;
    // for(size_t i = 0; i < config.K(); i++) {
    //   for(size_t j = 0; j < config.N(); j++) {
    //     std::wcout << m1[i][j] << L' ';
    //   }
    //   std::wcout << L'\n';
    // }
  }

  for (auto pair : stats) {
    std::wcout << std::setfill(L' ') << std::setw(5) << pair.first << L": "
               << std::setfill(L'=') << std::setw(pair.second + 1) << L'\n';
  }

  return 0;
}
