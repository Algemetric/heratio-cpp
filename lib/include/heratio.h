#pragma once

#include <NTL/ZZ.h>
#include <stddef.h>

class Heratio {
public:
  long d;
  long t;
  long alpha;
  long beta;
  long mu;
  long lambda;
  long eta;
  long gamma;
  long tau;
  long pi;
  u_int64_t config;

  NTL::ZZ q0;
  NTL::ZZ p;
  NTL::ZZ p_to_alpha;
  NTL::ZZ q0_to_beta;
  NTL::ZZ q_star;
  NTL::ZZ big_m;
  NTL::ZZ x0;

  void KeyGen(u_int64_t config);

  NTL::ZZ Encrypt(const NTL::ZZ &message) const;

  NTL::ZZ Decrypt(NTL::ZZ &ciphertext) const;

  NTL::ZZ Add(const NTL::ZZ &ciphertext1, const NTL::ZZ &ciphertext2) const;

  NTL::ZZ Sub(const NTL::ZZ &ciphertext1, const NTL::ZZ &ciphertext2) const;

  NTL::ZZ Mul(const NTL::ZZ &ciphertext1, const NTL::ZZ &ciphertext2) const;

  NTL::ZZ Div(const NTL::ZZ &ciphertext1, const NTL::ZZ &ciphertext2) const;

  NTL::Vec<NTL::ZZ> EncryptVector(NTL::Vec<NTL::ZZ> plaintext_vector) const;

  NTL::Vec<NTL::ZZ> DecryptVector(NTL::Vec<NTL::ZZ> ciphertext_vector) const;

  NTL::ZZ DotProduct(NTL::Vec<NTL::ZZ> vector1, NTL::Vec<NTL::ZZ> vector2,
                     const NTL::ZZ &prime);

private:
  NTL::ZZ GenerateQ() const;

  NTL::ZZ GenerateP() const;

  NTL::ZZ GenerateQStar() const;

  NTL::ZZ ComputePToAlpha() const;

  NTL::ZZ ComputeQToBeta() const;

  NTL::ZZ ComputeX0() const;

  NTL::ZZ ComputeM() const;

  void SelectParameters();

  void Toy1Config();

  void Toy2Config();

  void SmallConfig();

  void MediumConfig();
};