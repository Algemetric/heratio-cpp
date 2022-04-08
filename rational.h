#pragma once

#include <NTL/ZZ.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using namespace NTL;
using namespace std;

struct Rational
{
  ZZ numerator;
  ZZ denominator;

  Rational(ZZ numerator, ZZ denominator)
  {
    ZZ g = GCD(numerator, denominator);
    this->numerator = numerator / g;
    this->denominator = denominator / g;
  }

  string ToString()
  {
    stringstream buffer;
    buffer << this->numerator << "/" << this->denominator;
    return buffer.str();
  }
};

Rational operator+(Rational rat1, Rational rat2)
{
  return Rational(rat1.numerator * rat2.denominator + rat1.denominator * rat2.numerator, rat1.denominator * rat2.denominator);
}

Rational operator*(Rational rat1, Rational rat2)
{
  return Rational(rat1.numerator * rat2.numerator, rat1.denominator * rat2.denominator);
}