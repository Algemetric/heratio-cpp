#pragma once

#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "rational.h"

using namespace std;
using namespace NTL;

class Heratio
{
public:
  long d;
  long t;
  long alpha;
  long beta;
  long mu;
  long lambda;
  long eta;
  long gamma;
  long sigma;

  ZZ q0;
  ZZ p;
  ZZ p_to_alpha;
  ZZ q0_to_beta;
  ZZ p_star;
  ZZ x0;

  void KeyGen(const long d_, const long t_, const long alpha_, const long beta_, const long lambda_)
  {
    this->d = d_;
    this->t = t_;
    this->alpha = alpha_;
    this->beta = beta_;
    this->lambda = lambda_;

    this->gamma = ComputeGamma();
    this->eta = ComputeEta();
    this->mu = ComputeMu();
    this->sigma = ComputeSigma();

    this->q0 = GenerateQ();
    this->p = GenerateP();
    this->p_to_alpha = ComputePToAlpha();
    this->q0_to_beta = ComputeQToBeta();
    this->x0 = ComputeX0();
    this->p_star = GeneratePStar();
  }

  ZZ Encrypt(ZZ m)
  {
    ZZ r = RandomLen_ZZ(this->sigma);
    ZZ two_to_lambda = power2_ZZ(this->lambda);
    ZZ delta = RandomBnd(two_to_lambda / this->p_to_alpha);
    ZZ c = delta * this->p_to_alpha + m + r * this->q0_to_beta;

    return c;
  }

  ZZ Decrypt(ZZ c)
  {
    ZZ m = c % this->p_to_alpha % this->q0_to_beta;
    return m;
  }

  ZZ Add(const ZZ c1, const ZZ c2)
  {
    return AddMod(c1, c2, this->x0);
  }

  ZZ Mul(const ZZ c1, const ZZ c2)
  {
    return MulMod(c1, c2, this->x0);
  }

  Vec<ZZ> EncryptVector(Vec<ZZ> v)
  {
    Vec<ZZ> c;
    c.SetLength(v.length());

    for (long i = 0; i < v.length(); i++)
    {
      c[i] = Encrypt(v[i]);
    }

    return c;
  }

  Vec<ZZ> DecryptVector(Vec<ZZ> c)
  {
    Vec<ZZ> v;
    v.SetLength(c.length());

    for (long i = 0; i < c.length(); i++)
    {
      v[i] = Decrypt(c[i]);
    }

    return v;
  }

  ZZ DotProduct(Vec<ZZ> v1, Vec<ZZ> v2, ZZ prime)
  {
    ZZ result = ZZ(0);

    for (long i = 0; i < v1.length(); i++)
    {
      result += MulMod(v1[i], v2[i], prime);
    }

    return result % prime;
  }

private:
  long ComputeGamma()
  {
    return power_long(this->lambda, 4) / 500;
  }

  long ComputeEta()
  {
    return power_long(this->lambda, 2);
  }

  long ComputeMu()
  {
    return long((this->gamma - this->alpha * this->eta) / this->beta);
  }

  long ComputeSigma()
  {
    return ((this->alpha * this->eta - long(log2(this->t)) - this->d * this->beta * this->mu - this->d) / this->d) - 1;
  }

  ZZ GenerateQ()
  {
    return GenPrime_ZZ(this->mu, 80);
  }

  ZZ GenerateP()
  {
    ZZ p_ = this->q0;
    while (GCD(this->q0, p_) != 1)
    {
      p_ = GenPrime_ZZ(this->eta, 80);
    }
    return p_;
  }

  ZZ GeneratePStar()
  {
    long expression1 = (this->beta * this->mu - long(log(this->t))) / this->d;
    long expression2 = (this->beta * this->mu - 4) / 2;
    long p_star_bits = long(min(expression1, expression2));
    ZZ p_star = GenPrime_ZZ(this->mu, 80);

    return p_star;
  }

  ZZ ComputePToAlpha()
  {
    return power(this->p, this->alpha);
  }

  ZZ ComputeQToBeta()
  {
    return power(this->q0, this->beta);
  }

  ZZ ComputeX0()
  {
    return this->p_to_alpha * this->q0_to_beta;
  }
};