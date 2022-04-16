#pragma once

#include <NTL/ZZ.h>
#include <string>

struct Rational {
  NTL::ZZ numerator;
  NTL::ZZ denominator;

  Rational();

  Rational(NTL::ZZ numerator, NTL::ZZ denominator);

  Rational(long num, long den);

  std::string ToString();

  Rational operator+(Rational ohter);

  Rational operator-(Rational ohter);

  Rational operator*(Rational other);

  Rational operator/(Rational other);

  bool operator==(Rational other);
};

bool IsStringInteger(std::string string);

long StringCharCount(char character, std::string string);

Rational StringToRational(std::string string);