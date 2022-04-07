#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include "heratio.h"
#include "inspect.h"
#include "hensel_code.h"
#include "tools.h"

using namespace std;
using namespace NTL;

int main()
{
  const int d = 2;
  const int t = 8;
  const int alpha = 2;
  const int beta = 2;
  const int lambda = 72;

  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);

  Inspect(heratio);

  Rational m_prime = Rational(ZZ(2), ZZ(3));
  HenselCode hensel_code = HenselCode(heratio.p_star, 1);
  ZZ h = hensel_code.Encode(m_prime);
  Rational m_prime_r = hensel_code.Decode(h);

  cout << "m_prime = " << m_prime.ToString() << endl;
  cout << "h_bits = " << NumBits(h) << endl;
  cout << "m_prime_r = " << m_prime_r.ToString() << "\n\n";

  ZZ c = heratio.Encrypt(h);
  ZZ h_r = heratio.Decrypt(c);
  Rational m_prime_decoded = hensel_code.Decode(h_r);

  cout << "c_bits = " << NumBits(c) << endl;
  cout << "h_r_bits = " << NumBits(h_r) << endl;
  cout << "m_prime_decoded = " << m_prime_decoded.ToString() << "\n\n";

  Rational m_prime1 = Rational(ZZ(3), ZZ(5));
  Rational m_prime2 = Rational(ZZ(7), ZZ(4));

  ZZ h1 = hensel_code.Encode(m_prime1);
  ZZ h2 = hensel_code.Encode(m_prime2);

  ZZ c1 = heratio.Encrypt(h1);
  ZZ c2 = heratio.Encrypt(h2);

  ZZ c1_plus_c2 = heratio.Add(c1, c2);
  ZZ c1_times_c2 = heratio.Mul(c1, c2);

  ZZ h1_plus_h2_r = heratio.Decrypt(c1_plus_c2);
  ZZ h1_times_h2_r = heratio.Decrypt(c1_times_c2);

  Rational m_prime1_plus_m_prime2 = hensel_code.Decode(h1_plus_h2_r);
  Rational m_prime1_times_m_prime2 = hensel_code.Decode(h1_times_h2_r);

  cout << "m_prime1 = " << m_prime1.ToString() << endl;
  cout << "m_prime2 = " << m_prime2.ToString() << endl;
  cout << "m_prime1_plus_m_prime2 = " << m_prime1_plus_m_prime2.ToString() << endl;
  cout << "m_prime1_times_m_prime2 = " << m_prime1_times_m_prime2.ToString() << "\n\n";

  cout << "Generate two random vectors:" << endl;
  vector<Rational> v1 = GenerateRandomVector(4, ZZ(30));
  Inspect(v1);
  vector<Rational> v2 = GenerateRandomVector(4, ZZ(30));
  Inspect(v2);

  cout << "\n\nEncode vectors:" << endl;
  Vec<ZZ> vh1 = hensel_code.EncodeVector(v1);
  Vec<ZZ> vh2 = hensel_code.EncodeVector(v2);
  // Uncomment the lines below to see the vectors. It will be very large.
  // Inspect(vh1);
  // Inspect(vh2);

  cout << "\n\nEncrypt vectors:" << endl;
  Vec<ZZ> cvh1 = heratio.EncryptVector(vh1);
  Vec<ZZ> cvh2 = heratio.EncryptVector(vh2);
  // Uncomment the lines below to see the vectors. This will be even larger, might not fit the buffer of the terminal.
  // Inspect(cvh1);
  // Inspect(cvh2);

  cout << "\n\nDecrypt vectors:" << endl;
  Vec<ZZ> vh1_r = heratio.DecryptVector(cvh1);
  Vec<ZZ> vh2_r = heratio.DecryptVector(cvh2);
  // Uncomment the lines below to see the vectors. It will be very large.
  // Inspect(vh1_r);
  // Inspect(vh2_r);

  cout << "\n\nDecode vectors:" << endl;
  vector<Rational> v1_r = hensel_code.DecodeVector(vh1_r);
  vector<Rational> v2_r = hensel_code.DecodeVector(vh2_r);
  Inspect(v1_r);
  Inspect(v2_r);

  cout << "\n\nCompute encrypted dot product:" << endl;
  ZZ encrypted_dot_product = heratio.DotProduct(cvh1, cvh2, heratio.p_star);
  ZZ decrypted_dot_product = heratio.Decrypt(encrypted_dot_product);

  cout << "decrypted_dot_product = " << decrypted_dot_product << endl;

  return 0;
}