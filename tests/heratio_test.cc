#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <vector>
#include "lib/include/rational.h"
#include "lib/include/hensel_code.h"
#include "lib/include/heratio.h"
#include "lib/include/tools.h"
#include "gtest/gtest.h"

class HeratioTest : public ::testing::Test
{
protected:
  const long d = 2;
  const long t = 3;
  const long alpha = 3;
  const long beta = 1;
  const long lambda = 32;
};

TEST_F(HeratioTest, KeyGen)
{
  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);

  EXPECT_EQ(d, 2);
  EXPECT_EQ(t, heratio.t);
  EXPECT_EQ(alpha, heratio.alpha);
  EXPECT_EQ(beta, heratio.beta);
  EXPECT_EQ(lambda, heratio.lambda);

  EXPECT_EQ(1024, heratio.eta);
  EXPECT_EQ(4194, heratio.gamma);
  EXPECT_EQ(1122, heratio.mu);
  EXPECT_EQ(411, heratio.sigma);

  EXPECT_EQ(heratio.mu, NTL::NumBits(heratio.q0));
  EXPECT_EQ(heratio.eta, NTL::NumBits(heratio.p));
  EXPECT_EQ(560, NTL::NumBits(heratio.q_star));
  EXPECT_EQ(NTL::power(heratio.p, heratio.alpha), heratio.p_to_alpha);
  EXPECT_EQ(NTL::power(heratio.q0, heratio.beta), heratio.q0_to_beta);
  EXPECT_EQ(heratio.p_to_alpha * heratio.q0_to_beta, heratio.x0);
}

TEST_F(HeratioTest, EncryptDecrypt)
{
  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);
  HenselCode hensel_code = HenselCode(heratio.q_star, 1);

  Rational m_prime = Rational(2, 3);
  NTL::ZZ m = hensel_code.Encode(m_prime);
  NTL::ZZ c = heratio.Encrypt(m);
  NTL::ZZ m_decrypted = heratio.Decrypt(c);
  Rational m_prime_decoded = hensel_code.Decode(m_decrypted);

  EXPECT_EQ(m_prime.ToString(), m_prime_decoded.ToString());
}

TEST_F(HeratioTest, HomomorphicAddition)
{
  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);
  HenselCode hensel_code = HenselCode(heratio.q_star, 1);

  Rational m1_prime = Rational(2, 3);
  Rational m2_prime = Rational(7, 11);
  Rational m3_prime = m1_prime + m2_prime;
  NTL::ZZ m1 = hensel_code.Encode(m1_prime);
  NTL::ZZ m2 = hensel_code.Encode(m2_prime);
  NTL::ZZ c1 = heratio.Encrypt(m1);
  NTL::ZZ c2 = heratio.Encrypt(m2);
  NTL::ZZ c3 = heratio.Add(c1, c2);
  NTL::ZZ m3_decrypted = heratio.Decrypt(c3);
  Rational m3_prime_decoded = hensel_code.Decode(m3_decrypted);

  EXPECT_EQ(m3_prime.ToString(), m3_prime_decoded.ToString());
}

TEST_F(HeratioTest, HomomorphicMultiplication)
{
  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);
  HenselCode hensel_code = HenselCode(heratio.q_star, 1);

  Rational m1_prime = Rational(2, 3);
  Rational m2_prime = Rational(7, 11);
  Rational m3_prime = m1_prime * m2_prime;
  NTL::ZZ m1 = hensel_code.Encode(m1_prime);
  NTL::ZZ m2 = hensel_code.Encode(m2_prime);
  NTL::ZZ c1 = heratio.Encrypt(m1);
  NTL::ZZ c2 = heratio.Encrypt(m2);
  NTL::ZZ c3 = heratio.Mul(c1, c2);
  NTL::ZZ m3_decrypted = heratio.Decrypt(c3);
  Rational m3_prime_decoded = hensel_code.Decode(m3_decrypted);

  EXPECT_EQ(m3_prime.ToString(), m3_prime_decoded.ToString());
}

TEST_F(HeratioTest, EncryptDecryptVector)
{
  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);
  HenselCode hensel_code = HenselCode(heratio.q_star, 1);

  std::vector<Rational> v = GenerateRandomVector(3, NTL::ZZ(50));
  NTL::Vec<NTL::ZZ> vh = hensel_code.EncodeVector(v);
  NTL::Vec<NTL::ZZ> cvh = heratio.EncryptVector(vh);
  NTL::Vec<NTL::ZZ> vh_decrypted = heratio.DecryptVector(cvh);
  std::vector<Rational> v_decoded = hensel_code.DecodeVector(vh_decrypted);

  EXPECT_EQ(v.size(), v_decoded.size());
  EXPECT_TRUE(v[0] == v_decoded[0]);
  EXPECT_TRUE(v[1] == v_decoded[1]);
  EXPECT_TRUE(v[2] == v_decoded[2]);
  EXPECT_EQ(vh.length(), vh_decrypted.length());
  EXPECT_TRUE(vh[0] == vh_decrypted[0]);
  EXPECT_TRUE(vh[1] == vh_decrypted[1]);
  EXPECT_TRUE(vh[2] == vh_decrypted[2]);
}