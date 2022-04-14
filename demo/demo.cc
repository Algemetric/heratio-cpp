#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <istream>
#include "lib/include/rational.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "lib/include/hensel_code.h"
#include "lib/include/tools.h"
#include "demo/demo_helpers.h"

int main()
{
  std::string config = "default";
  long d;
  long t;
  long alpha;
  long beta;
  long lambda;

  Heratio heratio;
  HenselCode hensel_code = HenselCode(NTL::ZZ(1), 1);

  SelectParameters(config, d, t, alpha, beta, lambda, heratio, hensel_code);

  MainMenu(heratio, hensel_code);

  return 0;
}