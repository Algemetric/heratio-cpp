#pragma once

struct Rational
{
  NTL::ZZ numerator;
  NTL::ZZ denominator;

  Rational(NTL::ZZ numerator, NTL::ZZ denominator);

  Rational(long num, long den);

  std::string ToString();

  Rational operator+(Rational ohter);

  Rational operator-(Rational ohter);

  Rational operator*(Rational other);

  Rational operator/(Rational other);

  bool operator==(Rational other);
};