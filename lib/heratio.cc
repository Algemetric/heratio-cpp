#include "lib/include/heratio.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

void Heratio::KeyGen(const long d_, const long t_, const long alpha_,
                     const long beta_, const long lambda_) {
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
  this->q_star = GenerateQStar();
}

NTL::ZZ Heratio::Encrypt(NTL::ZZ m) {
  NTL::ZZ r = NTL::RandomLen_ZZ(this->sigma);
  NTL::ZZ two_to_gamma = NTL::power2_ZZ(this->gamma);
  NTL::ZZ delta = NTL::RandomBnd(two_to_gamma / this->p_to_alpha);
  NTL::ZZ c = (delta * this->p_to_alpha + m + r * this->q0_to_beta) % this->x0;

  return c;
}

NTL::ZZ Heratio::Decrypt(NTL::ZZ c) {
  NTL::ZZ m = c % this->p_to_alpha % this->q0_to_beta;
  return m;
}

NTL::ZZ Heratio::Add(const NTL::ZZ c1, const NTL::ZZ c2) {
  return NTL::AddMod(c1, c2, this->x0);
}

NTL::ZZ Heratio::Mul(const NTL::ZZ c1, const NTL::ZZ c2) {
  return NTL::MulMod(c1, c2, this->x0);
}

NTL::Vec<NTL::ZZ> Heratio::EncryptVector(NTL::Vec<NTL::ZZ> v) {
  NTL::Vec<NTL::ZZ> c;
  c.SetLength(v.length());

  for (long i = 0; i < v.length(); i++) {
    c[i] = Encrypt(v[i]);
  }

  return c;
}

NTL::Vec<NTL::ZZ> Heratio::DecryptVector(NTL::Vec<NTL::ZZ> c) {
  NTL::Vec<NTL::ZZ> v;
  v.SetLength(c.length());

  for (long i = 0; i < c.length(); i++) {
    v[i] = Decrypt(c[i]);
  }

  return v;
}

NTL::ZZ Heratio::DotProduct(NTL::Vec<NTL::ZZ> v1, NTL::Vec<NTL::ZZ> v2,
                            NTL::ZZ prime) {
  NTL::ZZ result = NTL::ZZ(0);

  for (long i = 0; i < v1.length(); i++) {
    result += NTL::MulMod(v1[i], v2[i], prime);
  }

  return result % prime;
}

long Heratio::ComputeGamma() { return NTL::power_long(this->lambda, 4) / 100; }

long Heratio::ComputeEta() { return NTL::power_long(this->lambda, 2); }

long Heratio::ComputeMu() {
  return long((this->gamma - this->alpha * this->eta) / this->beta);
}

long Heratio::ComputeSigma() {
  return ((this->alpha * this->eta - long(log2(this->t)) -
           this->d * this->beta * this->mu - this->d) /
          this->d) -
         1;
}

NTL::ZZ Heratio::GenerateQ() { return NTL::GenPrime_ZZ(this->mu, 80); }

NTL::ZZ Heratio::GenerateP() {
  NTL::ZZ p_ = this->q0;
  while (NTL::GCD(this->q0, p_) != 1) {
    p_ = NTL::GenPrime_ZZ(this->eta, 80);
  }
  return p_;
}

NTL::ZZ Heratio::GenerateQStar() {
  // long expression1 = (this->beta * this->mu - long(log2(this->t)) - 1) /
  // this->d; long expression2 = (this->beta * this->mu - 4) / 2; long
  // q_star_bits = long(std::min(expression1, expression2)); NTL::ZZ q_star =
  // NTL::GenPrime_ZZ(q_star_bits, 80);

  long q_star_bits =
      long((this->beta * this->mu - ceil(log2(t)) + 2 * this->d) / d) - 1;
  NTL::ZZ q_star = NTL::GenPrime_ZZ(q_star_bits, 80);

  return q_star;
}

NTL::ZZ Heratio::ComputePToAlpha() { return NTL::power(this->p, this->alpha); }

NTL::ZZ Heratio::ComputeQToBeta() { return NTL::power(this->q0, this->beta); }

NTL::ZZ Heratio::ComputeX0() { return this->p_to_alpha * this->q0_to_beta; }