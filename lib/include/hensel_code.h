#pragma once

#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <vector>

class HenselCode {
public:
  NTL::ZZ prime;
  int r;

  HenselCode(const NTL::ZZ &prime_, const long &r_exponent);

  NTL::ZZ Encode(Rational &m_prime) const;

  Rational Decode(NTL::ZZ &hencoded) const;

  NTL::Vec<NTL::ZZ> EncodeVector(std::vector<Rational> vector) const;

  std::vector<Rational> DecodeVector(NTL::Vec<NTL::ZZ> &vencoded);
};