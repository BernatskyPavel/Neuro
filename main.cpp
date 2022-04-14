#include "TPM.hpp"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <wchar.h>

#define N_PARAM "-n:"
#define N_DEFAULT 16
#define K_PARAM "-k:"
#define K_DEFAULT 3
#define L_PARAM "-l:"
#define L_DEFAULT 3
#define ITERATIONS_PARAM "-it:"
#define ITERATIONS_DEFAULT 100

#define NOT_FOUND -2
#define BAD_ARGUMENT -1

int
parse_argument(const char* name, int argc, char const* argv[])
{
  for (int i = 1; i < argc; i++) {
    const char* ptr = strstr(argv[i], name);
    if (ptr != NULL) {
      // atoi(ptr + strlen(name));
      std::string str(ptr + strlen(name));
      try {
        return std::stoi(str);
      } catch (std::invalid_argument const& e) {
        std::cerr << e.what() << ": Invalid argument " << name << "\n";
      } catch (std::out_of_range const& e) {
        std::cerr << e.what() << ": Out of range value of argument " << name
                  << "\n";
      }
      return BAD_ARGUMENT;
    }
  }
  return NOT_FOUND;
}

int
main(int argc, char const* argv[])
{
  int n, k, l, it;
  bool is_errors = false;
  if (argc > 1) {
    n = parse_argument(N_PARAM, argc, argv);
    if (n == BAD_ARGUMENT) {
      is_errors = true;
    } else if (n == NOT_FOUND) {
      n = N_DEFAULT;
    }
    k = parse_argument(K_PARAM, argc, argv);
    if (k == BAD_ARGUMENT) {
      is_errors = true;
    } else if (k == NOT_FOUND) {
      k = K_DEFAULT;
    }
    l = parse_argument(L_PARAM, argc, argv);
    if (l == BAD_ARGUMENT) {
      is_errors = true;
    } else if (l == NOT_FOUND) {
      l = L_DEFAULT;
    }
    it = parse_argument(ITERATIONS_PARAM, argc, argv);
    if (it == BAD_ARGUMENT) {
      is_errors = true;
    } else if (it == NOT_FOUND) {
      it = ITERATIONS_DEFAULT;
    }
  }

  if (is_errors) {
    return -1;
  }

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<int> dist(-1, 1);

  ITPMConfig conf = ITPMConfig(k, n, l);

  int step = 0;
  int O = 0, O2 = 0;

  std::map<int, int, std::less<int>> stats;

  for (int t = 0; t < it; t++) {
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
