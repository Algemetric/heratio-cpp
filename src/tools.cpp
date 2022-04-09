#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../include/rational.h"
#include "../include/heratio.h"
#include "../include/inspect.h"
#include "../include/hensel_code.h"
#include "../include/tools.h"

NTL::ZZ GenerateNonZeroRandomInteger(const NTL::ZZ upperbound)
{
  NTL::ZZ number;
  while (true)
  {
    number = NTL::RandomBnd(upperbound);
    if (number != 0)
    {
      break;
    }
  }
  return number;
}

std::vector<Rational> GenerateRandomVector(const int size, const NTL::ZZ upperbound)
{
  NTL::ZZ numerator;
  NTL::ZZ denominator;
  std::vector<Rational> v;

  for (int i = 0; i < size; i++)
  {
    numerator = GenerateNonZeroRandomInteger(upperbound);
    denominator = GenerateNonZeroRandomInteger(upperbound);
    v.push_back(Rational(numerator, denominator));
  }

  return v;
}

NTL::Vec<NTL::ZZ> CreateVectorFromUniqueValue(long size, NTL::ZZ value)
{
  NTL::Vec<NTL::ZZ> v;
  v.SetLength(size);

  for (long i = 0; i < size; i++)
  {
    v[i] = value;
  }

  return v;
}

Rational DotProduct(std::vector<Rational> v1, std::vector<Rational> v2)
{
  Rational result = Rational(NTL::ZZ(0), NTL::ZZ(1));

  for (long i = 0; i < v1.size(); i++)
  {
    result = result + v1[i] * v2[i];
  }

  return result;
}

NTL::ZZ DotProduct(NTL::Vec<NTL::ZZ> v1, NTL::Vec<NTL::ZZ> v2)
{
  NTL::ZZ result = NTL::ZZ(0);

  for (long i = 0; i < v1.length(); i++)
  {
    result += v1[i], v2[i];
  }

  return result;
}