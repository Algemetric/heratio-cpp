#pragma once

#include <NTL/ZZ.h>
#include <string>
#include <iostream>
#include <sstream>
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