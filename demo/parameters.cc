#include "include_helper.h"

void SelectParameters(std::string &id, Heratio &heratio,
                      HenselCode &hensel_code) {
  long config = 0;
  if (id == "toy1" || id == "default") {
    config = 0;
  } else if (id == "toy2") {
    config = 1;
  } else if (id == "small") {
    config = 2;
  } else if (id == "large") {
    config = 3;
  } else {
    std::cout << "Unknown selection. Continuing with default parameters."
              << endln(2);
  }

  heratio.KeyGen(config);
  hensel_code.prime = heratio.q0_to_beta;
  hensel_code.r = 1;
}