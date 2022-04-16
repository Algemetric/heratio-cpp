#include "include_helper.h"

int main() {
  std::string config = "default";
  long d;
  long t;
  long alpha;
  long beta;
  long lambda;

  Heratio heratio;
  HenselCode hensel_code = HenselCode(NTL::ZZ(1), 1);

  SelectParameters(config, d, t, alpha, beta, lambda, heratio, hensel_code);

  MainMenu(d, t, alpha, beta, lambda, heratio, hensel_code);

  return 0;
}