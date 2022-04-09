#include <NTL/ZZ.h>
#include <vector>
#include <sstream>
#include "../include/rational.h"
#include "../include/heratio.h"

void Inspect(Heratio heratio)
{
  std::cout << "Heratio instance:\n\n";
  std::cout << "d = " << heratio.d << std::endl;
  std::cout << "t = " << heratio.t << std::endl;
  std::cout << "alpha = " << heratio.alpha << std::endl;
  std::cout << "beta = " << heratio.beta << std::endl;
  std::cout << "lambda = " << heratio.lambda << "\n\n";
  std::cout << "eta = " << heratio.eta << std::endl;
  std::cout << "mu = " << heratio.mu << std::endl;
  std::cout << "sigma = " << heratio.sigma << std::endl;
  std::cout << "gamma = " << heratio.gamma << "\n\n";
  std::cout << "q0_bits = " << NTL::NumBits(heratio.q0) << std::endl;
  std::cout << "p_bits = " << NTL::NumBits(heratio.p) << std::endl;
  std::cout << "q0_to_beta_bits = " << NTL::NumBits(heratio.q0_to_beta) << std::endl;
  std::cout << "p_to_alpha_bits = " << NTL::NumBits(heratio.p_to_alpha) << std::endl;
  std::cout << "p_star_bits = " << NTL::NumBits(heratio.p_star) << std::endl;
  std::cout << "x0_bits = " << NTL::NumBits(heratio.x0) << "\n\n";
}

void Inspect(std::vector<Rational> v)
{
  std::stringstream buffer;
  buffer << "<Vector ";
  for (long i = 0; i < v.size(); i++)
  {
    buffer << v[i].ToString();
    if (i < v.size() - 1)
    {
      buffer << ", ";
    }
  }
  buffer << ">";
  std::cout << buffer.str() << std::endl;
}

void Inspect(NTL::Vec<NTL::ZZ> v)
{
  std::stringstream buffer;
  buffer << "<Vector ";
  for (long i = 0; i < v.length(); i++)
  {
    buffer << v[i];
    if (i < v.length() - 1)
    {
      buffer << ", ";
    }
  }
  buffer << ">";
  std::cout << buffer.str() << std::endl;
}