#include <NTL/ZZ.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "lib/include/rational.h"

Rational::Rational(NTL::ZZ numerator, NTL::ZZ denominator)
{
  NTL::ZZ g = NTL::GCD(numerator, denominator);
  this->numerator = numerator / g;
  this->denominator = denominator / g;
}

std::string Rational::ToString()
{
  std::stringstream buffer;
  buffer << this->numerator << "/" << this->denominator;
  return buffer.str();
}

Rational Rational::operator+(Rational other)
{
  return Rational(this->numerator * other.denominator + this->denominator * other.numerator, this->denominator * other.denominator);
}

Rational Rational::operator*(Rational other)
{
  return Rational(this->numerator * other.numerator, this->denominator * other.denominator);
}