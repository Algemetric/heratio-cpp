#pragma once

#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <vector>

class HenselCode {
public:
  NTL::ZZ prime;
  int r;

  HenselCode(NTL::ZZ prime_, int r_);

  NTL::ZZ Encode(Rational m);

  Rational Decode(NTL::ZZ h);

  NTL::Vec<NTL::ZZ> EncodeVector(std::vector<Rational> v);

  std::vector<Rational> DecodeVector(NTL::Vec<NTL::ZZ> vh);
};