#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include "lib/include/rational.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "lib/include/hensel_code.h"
#include "lib/include/tools.h"

int main()
{
  const long d = 2;
  const long t = 3;
  const long alpha = 3;
  const long beta = 1;
  const long lambda = 32;
  const int dimension = 23;

  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);

  std::cout << Inspect(heratio) << std::endl;

  Rational m_prime = Rational(NTL::ZZ(2), NTL::ZZ(3));
  HenselCode hensel_code = HenselCode(heratio.q_star, 1);
  NTL::ZZ h = hensel_code.Encode(m_prime);
  Rational m_prime_r = hensel_code.Decode(h);

  std::cout << "m_prime = " << m_prime.ToString() << std::endl;
  std::cout << "h_bits = " << NumBits(h) << std::endl;
  std::cout << "m_prime_r = " << m_prime_r.ToString() << "\n\n";

  NTL::ZZ c = heratio.Encrypt(h);
  NTL::ZZ h_r = heratio.Decrypt(c);
  Rational m_prime_decoded = hensel_code.Decode(h_r);

  std::cout << "c_bits = " << NumBits(c) << std::endl;
  std::cout << "h_r_bits = " << NumBits(h_r) << std::endl;
  std::cout << "m_prime_decoded = " << m_prime_decoded.ToString() << "\n\n";

  Rational m_prime1 = Rational(NTL::ZZ(3), NTL::ZZ(5));
  Rational m_prime2 = Rational(NTL::ZZ(7), NTL::ZZ(4));

  std::cout << "m_prime1 = " << m_prime1.ToString() << std::endl;
  std::cout << "m_prime2 = " << m_prime2.ToString() << std::endl;

  NTL::ZZ h1 = hensel_code.Encode(m_prime1);
  NTL::ZZ h2 = hensel_code.Encode(m_prime2);

  std::cout << "Encoded m_prime1 and m_prime2 (h1 and h2) " << std::endl;

  NTL::ZZ c1 = heratio.Encrypt(h1);
  NTL::ZZ c2 = heratio.Encrypt(h2);

  std::cout << "Encrypted h1 and h2 (c1 and c2) " << std::endl;

  NTL::ZZ c1_plus_c2 = heratio.Add(c1, c2);

  std::cout << "Computed c1_plus_c2 " << std::endl;

  NTL::ZZ c1_times_c2 = heratio.Mul(c1, c2);

  std::cout << "Computed c1_times_c2 " << std::endl;

  NTL::ZZ h1_plus_h2_r = heratio.Decrypt(c1_plus_c2);
  NTL::ZZ h1_times_h2_r = heratio.Decrypt(c1_times_c2);

  Rational m_prime1_plus_m_prime2 = hensel_code.Decode(h1_plus_h2_r);
  Rational m_prime1_times_m_prime2 = hensel_code.Decode(h1_times_h2_r);

  std::cout << "m_prime1_plus_m_prime2 = " << m_prime1_plus_m_prime2.ToString() << std::endl;
  std::cout << "m_prime1_times_m_prime2 = " << m_prime1_times_m_prime2.ToString() << "\n\n";

  std::cout << "Generate two random vectors:" << std::endl;
  std::vector<Rational> v1 = GenerateRandomVector(dimension, NTL::ZZ(30));
  std::cout << Inspect(v1) << std::endl;
  std::vector<Rational> v2 = GenerateRandomVector(dimension, NTL::ZZ(30));
  std::cout << Inspect(v2) << std::endl;

  std::cout << "\n\nEncode vectors:" << std::endl;
  NTL::Vec<NTL::ZZ> vh1 = hensel_code.EncodeVector(v1);
  NTL::Vec<NTL::ZZ> vh2 = hensel_code.EncodeVector(v2);
  // Uncomment the lines below to see the vectors. It will be very large.
  // Inspect(vh1);
  // Inspect(vh2);

  std::cout << "\n\nEncrypt vectors:" << std::endl;
  NTL::Vec<NTL::ZZ> cvh1 = heratio.EncryptVector(vh1);
  NTL::Vec<NTL::ZZ> cvh2 = heratio.EncryptVector(vh2);
  // Uncomment the lines below to see the vectors. This will be even larger, might not fit the buffer of the terminal.
  // Inspect(cvh1);
  // Inspect(cvh2);

  std::cout << "\n\nDecrypt vectors:" << std::endl;
  NTL::Vec<NTL::ZZ> vh1_r = heratio.DecryptVector(cvh1);
  NTL::Vec<NTL::ZZ> vh2_r = heratio.DecryptVector(cvh2);
  // Uncomment the lines below to see the vectors. It will be very large.
  // Inspect(vh1_r);
  // Inspect(vh2_r);

  std::cout << "\n\nDecode vectors:" << std::endl;
  std::vector<Rational> v1_r = hensel_code.DecodeVector(vh1_r);
  std::vector<Rational> v2_r = hensel_code.DecodeVector(vh2_r);
  std::cout << Inspect(v1_r) << std::endl;
  std::cout << Inspect(v2_r) << std::endl;

  std::cout << "\n\nCompute encrypted dot product:" << std::endl;
  NTL::ZZ encrypted_dot_product = heratio.DotProduct(cvh1, cvh2, heratio.x0);
  NTL::ZZ decrypted_dot_product = heratio.Decrypt(encrypted_dot_product);

  // Uncomment the line below to see the value. It will be large.
  // std::cout << "decrypted_dot_product = " << decrypted_dot_product << endl;

  Rational decoded_dot_product = hensel_code.Decode(decrypted_dot_product);
  Rational plain_dot_product = DotProduct(v1, v2);

  std::cout << "decoded_dot_product = " << decoded_dot_product.ToString() << std::endl;
  std::cout << "plain_dot_product = " << plain_dot_product.ToString() << std::endl;

  std::cout << "\n\nTesting the correctness bound:" << std::endl;

  NTL::Vec<NTL::ZZ> vt1 = CreateVectorFromUniqueValue(dimension, heratio.q_star - 1);
  NTL::Vec<NTL::ZZ> vt2 = CreateVectorFromUniqueValue(dimension, heratio.q_star - 1);
  NTL::ZZ test_dot_product = DotProduct(vt1, vt2);

  NTL::Vec<NTL::ZZ> cvt1 = heratio.EncryptVector(vt1);
  NTL::Vec<NTL::ZZ> cvt2 = heratio.EncryptVector(vt2);
  NTL::ZZ encrypted_test_dot_product = heratio.DotProduct(cvt1, cvt2, heratio.x0);
  NTL::ZZ decrypted_test_dot_product = heratio.Decrypt(encrypted_test_dot_product);

  std::cout << "Is test_dot_product == decrypted_test_dot_product? " << (test_dot_product == decrypted_test_dot_product) << std::endl;

  return 0;
}