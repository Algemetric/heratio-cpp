#pragma once

#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include "heratio.h"
#include "inspect.h"
#include "hensel_code.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace NTL;

ZZ GenerateNonZeroRandomInteger(const ZZ upperbound)
{
  ZZ number;
  while (true)
  {
    number = RandomBnd(upperbound);
    if (number != 0)
    {
      break;
    }
  }
  return number;
}

vector<Rational> GenerateRandomVector(const int size, const ZZ upperbound)
{
  ZZ numerator;
  ZZ denominator;
  vector<Rational> v;

  for (int i = 0; i < size; i++)
  {
    numerator = GenerateNonZeroRandomInteger(upperbound);
    denominator = GenerateNonZeroRandomInteger(upperbound);
    v.push_back(Rational(numerator, denominator));
  }

  return v;
}