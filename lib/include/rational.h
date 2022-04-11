#pragma once

struct Rational
{
  NTL::ZZ numerator;
  NTL::ZZ denominator;

  Rational(NTL::ZZ numerator, NTL::ZZ denominator);

  std::string ToString();

  Rational operator+(Rational ohter);

  Rational operator*(Rational other);
};