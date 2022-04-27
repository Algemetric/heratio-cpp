#include "lib/include/inspect.h"
#include "lib/include/heratio.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

std::string StringFromZZ(const NTL::ZZ &zz_) {
  std::stringstream ss_;
  ss_ << zz_;
  return ss_.str();
}

std::string Inspect(const Heratio &heratio) {
  std::string buffer;
  buffer += "Heratio instance:\n\n";
  buffer += "d = " + std::to_string(heratio.d) + "\n";
  buffer += "t = " + std::to_string(heratio.t) + "\n";
  buffer += "alpha = " + std::to_string(heratio.alpha) + "\n";
  buffer += "beta = " + std::to_string(heratio.beta) + "\n";
  buffer += "lambda = " + std::to_string(heratio.lambda) + "\n\n";
  buffer += "gamma = " + std::to_string(heratio.gamma) + "\n";
  buffer += "eta = " + std::to_string(heratio.eta) + "\n";
  buffer += "mu = " + std::to_string(heratio.mu) + "\n";
  buffer += "tau = " + std::to_string(heratio.tau) + "\n";
  buffer += "pi = " + std::to_string(heratio.pi) + "\n\n";
  buffer += "q0_bits = " + std::to_string(NTL::NumBits(heratio.q0)) + "\n";
  buffer += "p_bits = " + std::to_string(NTL::NumBits(heratio.p)) + "\n\n";
  buffer +=
      "q_star_bits = " + std::to_string(NTL::NumBits(heratio.q_star)) + "\n\n";

  return buffer;
}

std::string Inspect(std::vector<Rational> vector) {
  std::string buffer = "<Vector ";

  for (long i = 0; i < vector.size(); i++) {
    buffer += vector[i].ToString();
    if (i < vector.size() - 1) {
      buffer += ", ";
    }
  }
  buffer += ">";
  return buffer;
}

std::string Inspect(NTL::Vec<NTL::ZZ> vector) {
  std::string buffer = "<Vector ";

  for (long i = 0; i < vector.length(); i++) {
    buffer += StringFromZZ(vector[i]);
    if (i < vector.length() - 1) {
      buffer += ", ";
    }
  }
  buffer += ">";
  return buffer;
}