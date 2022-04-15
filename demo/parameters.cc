#include "include_helper.h"

void SelectParameters(std::string &id, long &d, long &t, long &alpha,
                      long &beta, long &lambda, Heratio &heratio, HenselCode &hensel_code)
{
  if (id == "toy" || id == "default")
  {
    d = 2;
    t = 3;
    alpha = 3;
    beta = 1;
    lambda = 32;

    heratio.KeyGen(d, t, alpha, beta, lambda);
    hensel_code.prime = heratio.q_star;
    hensel_code.r = 1;
  }
  else
  {
    std::cout << "Unknown selection. Continuing with default parameters." << endln(2);
  }
}