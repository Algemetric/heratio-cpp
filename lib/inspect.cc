#include <NTL/ZZ.h>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>
#include "lib/include/rational.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"

std::string StringFromZZ(const NTL::ZZ &x)
{
  std::stringstream ss;
  ss << x;
  return ss.str();
}

std::string Inspect(Heratio heratio)
{
  std::string buffer;
  buffer += "Heratio instance:\n\n";
  buffer += "d = " + std::to_string(heratio.d) + "\n";
  buffer += "t = " + std::to_string(heratio.t) + "\n";
  buffer += "alpha = " + std::to_string(heratio.alpha) + "\n";
  buffer += "beta = " + std::to_string(heratio.beta) + "\n";
  buffer += "lambda = " + std::to_string(heratio.lambda) + "\n\n";
  buffer += "eta = " + std::to_string(heratio.eta) + "\n";
  buffer += "mu = " + std::to_string(heratio.mu) + "\n";
  buffer += "sigma = " + std::to_string(heratio.sigma) + "\n";
  buffer += "gamma = " + std::to_string(heratio.gamma) + "\n\n";
  buffer += "q0_bits = " + std::to_string(NTL::NumBits(heratio.q0)) + "\n";
  buffer += "p_bits = " + std::to_string(NTL::NumBits(heratio.p)) + "\n";
  buffer += "q_star_bits = " + std::to_string(NTL::NumBits(heratio.q_star)) + "\n\n";

  return buffer;
}

std::string Inspect(std::vector<Rational> v)
{
  std::string buffer = "<Vector ";

  for (long i = 0; i < v.size(); i++)
  {
    buffer += v[i].ToString();
    if (i < v.size() - 1)
    {
      buffer += ", ";
    }
  }
  buffer += ">";
  return buffer;
}

std::string Inspect(NTL::Vec<NTL::ZZ> v)
{
  std::string buffer = "<Vector ";

  for (long i = 0; i < v.length(); i++)
  {
    buffer += StringFromZZ(v[i]);
    if (i < v.length() - 1)
    {
      buffer += ", ";
    }
  }
  buffer += ">";
  // std::cout + buffer.str() + "\n";
  return buffer;
}