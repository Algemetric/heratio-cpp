#include "lib/include/heratio.h"
#include "lib/include/rational.h"
#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

void Heratio::KeyGen(const u_int64_t config_) {
  this->config = config_;

  SelectParameters();

  this->rho = this->beta * this->mu + this->lambda;

  this->q0 = GenerateQ();
  this->p = GenerateP();
  this->p_to_alpha = ComputePToAlpha();
  this->q0_to_beta = ComputeQToBeta();
  this->x0 = ComputeX0();
  this->q_star = GenerateQStar();
  this->big_m = ComputeM();
}

NTL::ZZ Heratio::Encrypt(const NTL::ZZ &message) const {
  NTL::ZZ two_to_beta_mu = NTL::power2_ZZ(this->beta * this->mu);
  NTL::ZZ two_to_rho_minus_beta_mu =
      NTL::power2_ZZ(this->rho - this->beta * this->mu);
  NTL::ZZ r_noise = NTL::RandomBnd(two_to_rho_minus_beta_mu);

  NTL::ZZ delta = NTL::RandomBnd(two_to_beta_mu);
  NTL::ZZ ciphertext =
      (delta * this->p_to_alpha + message + r_noise * this->q0_to_beta) %
      this->x0;

  return ciphertext;
}

NTL::ZZ Heratio::Decrypt(NTL::ZZ &ciphertext) const {
  NTL::ZZ message = ciphertext % this->p_to_alpha % this->q0_to_beta;
  return message;
}

NTL::ZZ Heratio::Add(const NTL::ZZ &ciphertext1,
                     const NTL::ZZ &ciphertext2) const {
  return NTL::AddMod(ciphertext1, ciphertext2, this->x0);
}

NTL::ZZ Heratio::Sub(const NTL::ZZ &ciphertext1,
                     const NTL::ZZ &ciphertext2) const {
  return NTL::SubMod(ciphertext1, ciphertext2, this->x0);
}

NTL::ZZ Heratio::Mul(const NTL::ZZ &ciphertext1,
                     const NTL::ZZ &ciphertext2) const {
  return NTL::MulMod(ciphertext1, ciphertext2, this->x0);
}

NTL::ZZ Heratio::Div(const NTL::ZZ &ciphertext1,
                     const NTL::ZZ &ciphertext2) const {
  NTL::ZZ c2_inv = NTL::InvMod(ciphertext2, this->x0);
  return NTL::MulMod(ciphertext1, c2_inv, this->x0);
}

NTL::Vec<NTL::ZZ>
Heratio::EncryptVector(NTL::Vec<NTL::ZZ> plaintext_vector) const {
  NTL::Vec<NTL::ZZ> ciphertext_vector;
  ciphertext_vector.SetLength(plaintext_vector.length());

  for (long i = 0; i < plaintext_vector.length(); i++) {
    ciphertext_vector[i] = Encrypt(plaintext_vector[i]);
  }

  return ciphertext_vector;
}

NTL::Vec<NTL::ZZ>
Heratio::DecryptVector(NTL::Vec<NTL::ZZ> ciphertext_vector) const {
  NTL::Vec<NTL::ZZ> plaintext_vector;
  plaintext_vector.SetLength(ciphertext_vector.length());

  for (long i = 0; i < ciphertext_vector.length(); i++) {
    plaintext_vector[i] = Decrypt(ciphertext_vector[i]);
  }

  return plaintext_vector;
}

NTL::ZZ Heratio::DotProduct(NTL::Vec<NTL::ZZ> vector1,
                            NTL::Vec<NTL::ZZ> vector2, const NTL::ZZ &prime) {
  NTL::ZZ result = NTL::ZZ(0);

  for (long i = 0; i < vector1.length(); i++) {
    result += NTL::MulMod(vector1[i], vector2[i], prime);
  }

  return result % prime;
}

NTL::ZZ Heratio::GenerateQ() const { return NTL::GenPrime_ZZ(this->mu, 80); }

NTL::ZZ Heratio::GenerateP() const {
  NTL::ZZ prime_p = this->q0;
  while ((NTL::GCD(this->q0, prime_p) != 1) != 0) {
    prime_p = NTL::GenPrime_ZZ(this->eta, 80);
  }
  return prime_p;
}

NTL::ZZ Heratio::GenerateQStar() const {
  NTL::ZZ q_star = NTL::GenPrime_ZZ(this->tau, 80);

  return q_star;
}

NTL::ZZ Heratio::ComputePToAlpha() const {
  return NTL::power(this->p, this->alpha);
}

NTL::ZZ Heratio::ComputeQToBeta() const {
  return NTL::power(this->q0, this->beta);
}

NTL::ZZ Heratio::ComputeX0() const {
  return this->p_to_alpha * this->q0_to_beta;
}

NTL::ZZ Heratio::ComputeM() const {
  return NTL::SqrRoot((this->q_star - 1) / 2);
}

void Heratio::SelectParameters() {
  switch (this->config) {
  case 0:
    Toy1Config();
    break;
  case 1:
    Toy2Config();
    break;
  case 2:
    SmallConfig();
    break;
  case 3:
    MediumConfig();
    break;
  }
}

void Heratio::Toy1Config() {
  this->d = 5;
  this->t = 1;
  this->alpha = 3;
  this->beta = 1;
  this->lambda = 18;
  this->gamma = 2111;
  this->eta = 678;
  this->mu = 77;
  this->tau = 16;
  this->pi = 8;
}

void Heratio::Toy2Config() {
  this->d = 10;
  this->t = 3;
  this->alpha = 6;
  this->beta = 2;
  this->lambda = 24;
  this->gamma = 9948;
  this->eta = 1632;
  this->mu = 78;
  this->tau = 24;
  this->pi = 12;
}

void Heratio::SmallConfig() {
  this->d = 15;
  this->t = 3;
  this->alpha = 7;
  this->beta = 2;
  this->lambda = 52;
  this->gamma = 76040;
  this->eta = 12182;
  this->mu = 768;
  this->tau = 64;
  this->pi = 32;
}

void Heratio::MediumConfig() {
  this->d = 20;
  this->t = 5;
  this->alpha = 6;
  this->beta = 2;
  this->lambda = 64;
  this->gamma = 89478;
  this->eta = 15639;
  this->mu = 1280;
  this->tau = 128;
  this->pi = 64;
}