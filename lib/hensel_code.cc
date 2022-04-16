#include "lib/include/hensel_code.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <math.h>
#include <vector>

HenselCode::HenselCode(NTL::ZZ prime_, int r_) {
  this->prime = prime_;
  this->r = r_;
}

NTL::ZZ HenselCode::Encode(Rational m) {
  NTL::ZZ den_inv = InvMod(m.denominator, power(this->prime, this->r));
  NTL::ZZ h = MulMod(m.numerator, den_inv, power(this->prime, this->r));

  return h;
}

Rational HenselCode::Decode(NTL::ZZ h) {
  int i = 0;
  NTL::ZZ big_n = SqrRoot((prime - 1) / 2);
  NTL::Vec<NTL::ZZ> x;
  x.SetLength(2);
  x[i] = power(this->prime, this->r);
  x[i + 1] = h;

  NTL::Vec<NTL::ZZ> y;
  y.SetLength(2);
  y[i] = NTL::ZZ(0);
  y[i + 1] = NTL::ZZ(1);

  NTL::Vec<NTL::ZZ> z;
  z.SetLength(2);
  z[i] = NTL::ZZ(1);
  z[i + 1] = NTL::ZZ(0);
  NTL::ZZ q;
  i = 1;

  while (x[i] > big_n) {
    x.SetLength(x.length() + 2);
    y.SetLength(y.length() + 2);
    z.SetLength(z.length() + 2);
    q = x[i - 1] / x[i];
    x[i + 1] = x[i - 1] - q * x[i];
    y[i + 1] = y[i - 1] - q * y[i];
    z[i + 1] = z[i - 1] - q * z[i];
    i++;
  }

  NTL::ZZ c = NTL::power(NTL::ZZ(-1), (i + 1)) * x[i];
  NTL::ZZ d = NTL::power(NTL::ZZ(-1), (i + 1)) * y[i];

  Rational m = Rational(c, d);

  return m;
}

NTL::Vec<NTL::ZZ> HenselCode::EncodeVector(std::vector<Rational> v) {
  NTL::Vec<NTL::ZZ> vh;
  vh.SetLength(v.size());

  for (long i = 0; i < vh.length(); i++) {
    vh[i] = Encode(v[i]);
  }

  return vh;
}

std::vector<Rational> HenselCode::DecodeVector(NTL::Vec<NTL::ZZ> vh) {
  std::vector<Rational> v;

  for (long i = 0; i < vh.length(); i++) {
    v.push_back(Decode(vh[i]));
  }

  return v;
}