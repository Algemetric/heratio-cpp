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

Vec<ZZ> CreateVectorFromUniqueValue(long size, ZZ value)
{
  Vec<ZZ> v;
  v.SetLength(size);

  for (long i = 0; i < size; i++)
  {
    v[i] = value;
  }

  return v;
}

Rational DotProduct(vector<Rational> v1, vector<Rational> v2)
{
  Rational result = Rational(ZZ(0), ZZ(1));

  for (long i = 0; i < v1.size(); i++)
  {
    result = result + v1[i] * v2[i];
  }

  return result;
}

ZZ DotProduct(Vec<ZZ> v1, Vec<ZZ> v2)
{
  ZZ result = ZZ(0);

  for (long i = 0; i < v1.length(); i++)
  {
    result += v1[i], v2[i];
  }

  return result;
}