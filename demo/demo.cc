#include "include_helper.h"

int main() {
  std::string config = "toy1";
  Heratio heratio;
  heratio.KeyGen(0);

  HenselCode hensel_code = HenselCode(heratio.q0, heratio.beta);

  SelectParameters(config, heratio, hensel_code);

  MainMenu(heratio, hensel_code);

  return 0;
}