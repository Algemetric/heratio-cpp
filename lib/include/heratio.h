#pragma once

#include <stddef.h>

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

  NTL::ZZ q0;
  NTL::ZZ p;
  NTL::ZZ p_to_alpha;
  NTL::ZZ q0_to_beta;
  NTL::ZZ q_star;
  NTL::ZZ x0;

  void KeyGen(const long d_, const long t_, const long alpha_, const long beta_, const long lambda_);

  NTL::ZZ Encrypt(NTL::ZZ m);

  NTL::ZZ Decrypt(NTL::ZZ c);

  NTL::ZZ Add(const NTL::ZZ c1, const NTL::ZZ c2);

  NTL::ZZ Mul(const NTL::ZZ c1, const NTL::ZZ c2);

  NTL::Vec<NTL::ZZ> EncryptVector(NTL::Vec<NTL::ZZ> v);

  NTL::Vec<NTL::ZZ> DecryptVector(NTL::Vec<NTL::ZZ> c);

  NTL::ZZ DotProduct(NTL::Vec<NTL::ZZ> v1, NTL::Vec<NTL::ZZ> v2, NTL::ZZ prime);

private:
  long ComputeGamma();

  long ComputeEta();

  long ComputeMu();

  long ComputeSigma();

  NTL::ZZ GenerateQ();

  NTL::ZZ GenerateP();

  NTL::ZZ GenerateQStar();

  NTL::ZZ ComputePToAlpha();

  NTL::ZZ ComputeQToBeta();

  NTL::ZZ ComputeX0();
};