#include "include_helper.h"

int main() {
  std::string config = "default";
  int64_t d = 2;
  int64_t t = 3;
  int64_t alpha = 3;
  int64_t beta = 1;
  int64_t lambda = 18;

  Heratio heratio;
  HenselCode hensel_code = HenselCode(NTL::ZZ(1), 1);

  SelectParameters(config, d, t, alpha, beta, lambda, heratio, hensel_code);

  MainMenu(d, t, alpha, beta, lambda, heratio, hensel_code);

  return 0;
}