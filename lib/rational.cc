#include <NTL/ZZ.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "lib/include/rational.h"
#include "lib/include/tools.h"

Rational::Rational()
{
  this->numerator = NTL::ZZ(0);
  this->denominator = NTL::ZZ(1);
}

Rational::Rational(NTL::ZZ numerator, NTL::ZZ denominator)
{
  NTL::ZZ g = NTL::GCD(numerator, denominator);
  this->numerator = numerator / g;
  this->denominator = denominator / g;
}

Rational::Rational(long num, long den)
{
  NTL::ZZ numerator_ = NTL::ZZ(num);
  NTL::ZZ denominator_ = NTL::ZZ(den);
  NTL::ZZ g = NTL::GCD(numerator_, denominator_);
  this->numerator = numerator_ / g;
  this->denominator = denominator_ / g;
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

Rational Rational::operator-(Rational other)
{
  return Rational(this->numerator * other.denominator - this->denominator * other.numerator, this->denominator * other.denominator);
}

Rational Rational::operator*(Rational other)
{
  return Rational(this->numerator * other.numerator, this->denominator * other.denominator);
}

Rational Rational::operator/(Rational other)
{
  return Rational(this->numerator * other.denominator, this->denominator * other.numerator);
}

bool Rational::operator==(Rational other)
{
  return (this->numerator == other.numerator) && (this->denominator == other.denominator);
}

bool IsStringInteger(std::string s)
{
  if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
    return false;

  char *p;
  strtol(s.c_str(), &p, 10);

  return (*p == 0);
}

long StringCharCount(char character, std::string string)
{
  return std::count(string.begin(), string.end(), character);
}

Rational StringToRational(std::string string)
{
  std::vector<std::string> sv;
  std::stringstream rational_ss;
  std::string s;
  NTL::ZZ numerator;
  NTL::ZZ denominator;

  rational_ss << string;

  if (IsStringInteger(string) == 1 && StringCharCount('/', string) == 0)
  {
    numerator = StringToZZ(string);
    denominator = NTL::ZZ(1);
  }
  else if (StringCharCount('/', string) == 1)
  {
    while (std::getline(rational_ss, s, '/'))
    {
      sv.push_back(s);
    }

    if (IsStringInteger(sv[0]) && IsStringInteger(sv[1]))
    {
      numerator = StringToZZ(sv[0]);
      denominator = StringToZZ(sv[1]);
    }
    else
    {
      numerator = NTL::ZZ(0);
      denominator = NTL::ZZ(1);
    }
  }
  else
  {
    numerator = NTL::ZZ(0);
    denominator = NTL::ZZ(1);
  }

  Rational rational = Rational(numerator, denominator);

  return rational;
}