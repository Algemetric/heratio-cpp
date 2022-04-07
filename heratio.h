#pragma once

#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <vector>
#include <math.h>
#include "rational.h"

using namespace std;
using namespace NTL;

class Heratio
{
public:
  int d;
  int t;
  int alpha;
  int beta;
  int mu;
  int lambda;
  int eta_star;
  int eta;
  int rho;
  int gamma;

  ZZ q0;
  ZZ p;
  ZZ p_to_alpha;
  ZZ q0_to_beta;
  ZZ p_star;
  ZZ x0;

  void KeyGen(const int d_, const int t_, const int alpha_, const int beta_, const int lambda_)
  {
    this->d = d_;
    this->t = t_;
    this->alpha = alpha_;
    this->beta = beta_;
    this->lambda = lambda_;
    this->rho = this->lambda * int(log(this->lambda));
    int eta_star1 = power_long(this->lambda, 2) + this->rho * this->lambda;
    int eta_star2 = int(log(eta_star1));
    this->eta_star = (eta_star1 * eta_star2) / 100;
    this->gamma = (power_long(this->eta_star, 2) * int(log(this->lambda)) + 1);
    this->eta = int(9999 * ceil(this->gamma / 10000) / this->alpha);
    this->mu = int((this->gamma - this->alpha * this->eta) / this->beta);
    this->q0 = generate_q(this->mu);
    this->p = generate_p(this->q0, this->eta);
    this->p_to_alpha = power(this->p, this->alpha);
    this->q0_to_beta = power(this->q0, this->beta);
    this->x0 = this->p_to_alpha * this->q0_to_beta;
    this->p_star = generate_p_star(this->d, this->t, this->beta, this->mu);
  }

  ZZ Encrypt(ZZ m)
  {
    ZZ r_bound = power2_ZZ(500);
    ZZ r = RandomBnd(r_bound);
    ZZ two_to_lambda = power2_ZZ(lambda);
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

    return result;
  }

private:
  ZZ generate_q(int mu)
  {
    return GenPrime_ZZ(mu, 80);
  }

  ZZ generate_p(ZZ q0, int eta)
  {
    ZZ p = q0;
    while (GCD(q0, p) != 1)
    {
      p = RandomLen_ZZ(eta);
    }
    return p;
  }

  ZZ generate_p_star(int d, int t, int beta, int mu)
  {
    int expression1 = (beta * mu - int(log(t))) / d;
    int expression2 = (beta * mu - 4) / 2;
    int p_star_bits = int(min(expression1, expression2));
    ZZ p_star = GenPrime_ZZ(mu, 80);

    return p_star;
  }
};