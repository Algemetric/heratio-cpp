#pragma once

#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <vector>
#include <math.h>
#include "rational.h"

using namespace std;
using namespace NTL;

class HenselCode
{
public:
  ZZ prime;
  int r;

  HenselCode(ZZ prime_, int r_)
  {
    this->prime = prime_;
    this->r = r_;
  }

  ZZ Encode(Rational m)
  {
    ZZ den_inv = InvMod(m.denominator, power(this->prime, this->r));
    ZZ h = MulMod(m.numerator, den_inv, power(this->prime, this->r));

    return h;
  }

  Rational Decode(ZZ h)
  {
    int i = 0;
    ZZ big_n = SqrRoot((prime - 1) / 2);
    Vec<ZZ> x;
    x.SetLength(2);
    x[i] = power(this->prime, this->r);
    x[i + 1] = h;

    Vec<ZZ> y;
    y.SetLength(2);
    y[i] = ZZ(0);
    y[i + 1] = ZZ(1);

    Vec<ZZ> z;
    z.SetLength(2);
    z[i] = ZZ(1);
    z[i + 1] = ZZ(0);
    ZZ q;
    i = 1;

    while (x[i] > big_n)
    {
      x.SetLength(x.length() + 2);
      y.SetLength(y.length() + 2);
      z.SetLength(z.length() + 2);
      q = x[i - 1] / x[i];
      x[i + 1] = x[i - 1] - q * x[i];
      y[i + 1] = y[i - 1] - q * y[i];
      z[i + 1] = z[i - 1] - q * z[i];
      i++;
    }

    ZZ c = power(ZZ(-1), (i + 1)) * x[i];
    ZZ d = power(ZZ(-1), (i + 1)) * y[i];

    Rational m = Rational(c, d);

    return m;
  }

  Vec<ZZ> EncodeVector(vector<Rational> v)
  {
    Vec<ZZ> vh;
    vh.SetLength(v.size());

    for (long i = 0; i < vh.length(); i++)
    {
      vh[i] = Encode(v[i]);
    }

    return vh;
  }

  vector<Rational> DecodeVector(Vec<ZZ> vh)
  {
    vector<Rational> v;

    for (long i = 0; i < vh.length(); i++)
    {
      v.push_back(Decode(vh[i]));
    }

    return v;
  }
};