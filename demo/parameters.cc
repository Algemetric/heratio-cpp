#include "include_helper.h"

void SelectParameters(std::string &id, long &d, long &t, long &alpha,
                      long &beta, long &lambda, Heratio &heratio,
                      HenselCode &hensel_code) {
  if (id == "toy" || id == "default") {
    d = 2;
    t = 3;
    alpha = 3;
    beta = 1;
    lambda = 18;
  } else if (id == "small") {
    d = 2;
    t = 3;
    alpha = 6;
    beta = 2;
    lambda = 25;
  } else if (id == "medium") {
    d = 2;
    t = 3;
    alpha = 8;
    beta = 2;
    lambda = 32;
  } else if (id == "large") {
    d = 2;
    t = 3;
    alpha = 20;
    beta = 10;
    lambda = 50;
  } else if (id == "larger") {
    d = 2;
    t = 3;
    alpha = 40;
    beta = 30;
    lambda = 72;
  } else {
    std::cout << "Unknown selection. Continuing with default parameters."
              << endln(2);
  }

  heratio.KeyGen(d, t, alpha, beta, lambda);
  hensel_code.prime = heratio.q_star;
  hensel_code.r = 1;
}