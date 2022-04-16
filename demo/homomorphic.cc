#include "include_helper.h"

void BasicHomomorphicOperationsDemo(Heratio &heratio, HenselCode &hensel_code) {
  std::string string;
  Rational rational1;
  Rational rational2;
  Rational decoded_sum_result;
  Rational decoded_mul_result;
  NTL::ZZ h1;
  NTL::ZZ h2;
  NTL::ZZ c1;
  NTL::ZZ c2;
  NTL::ZZ c1_plus_c2;
  NTL::ZZ c1_times_c2;
  NTL::ZZ decrypted_sum_result;
  NTL::ZZ decrypted_mul_result;

  DisplayDemoTitle(3);

  std::cout << "Type one rational number:\n\n";
  std::cin >> string;
  rational1 = StringToRational(string);

  std::cout << "\nType another rational number:\n\n";
  std::cin >> string;
  rational2 = StringToRational(string);

  h1 = hensel_code.Encode(rational1);
  h2 = hensel_code.Encode(rational2);
  c1 = heratio.Encrypt(h1);
  c2 = heratio.Encrypt(h2);
  c1_plus_c2 = heratio.Add(c1, c2);
  c1_times_c2 = heratio.Mul(c1, c2);
  decrypted_sum_result = heratio.Decrypt(c1_plus_c2);
  decrypted_mul_result = heratio.Decrypt(c1_times_c2);
  decoded_sum_result = hensel_code.Decode(decrypted_sum_result);
  decoded_mul_result = hensel_code.Decode(decrypted_mul_result);

  DisplayBasicHomomorphicResults(
      rational1, rational2, decoded_sum_result, decoded_mul_result, h1, h2, c1,
      c2, c1_plus_c2, c1_times_c2, decrypted_sum_result, decrypted_mul_result);
}

void CompositeHomomorphicOperationsDemo(Heratio &heratio,
                                        HenselCode &hensel_code) {
  int size;
  std::vector<Rational> vector1;
  std::vector<Rational> vector2;

  DisplayDemoTitle(4);

  std::cout << "Type any dimension between 2 and 4:\n\n";
  std::cin >> size;

  ReadInputVector(1, size, vector1);
  ReadInputVector(2, size, vector2);

  std::cout << "\nPlaintext vectors: " << std::endl;
  std::cout << "v1: " << Inspect(vector1) << std::endl;
  std::cout << "v2: " << Inspect(vector2) << endln(2);

  NTL::Vec<NTL::ZZ> vh1 = hensel_code.EncodeVector(vector1);
  NTL::Vec<NTL::ZZ> vh2 = hensel_code.EncodeVector(vector2);

  std::cout << "Encoded vectors: " << std::endl;
  std::cout << "vh1: " << Inspect(vh1) << std::endl;
  std::cout << "vh2: " << Inspect(vh2) << endln(2);

  NTL::Vec<NTL::ZZ> vc1 = heratio.EncryptVector(vh1);
  NTL::Vec<NTL::ZZ> vc2 = heratio.EncryptVector(vh2);

  std::cout << "Encrypted vectors: " << std::endl;
  std::cout << "vc1: " << Inspect(vc1) << std::endl;
  std::cout << "vc2: " << Inspect(vc2) << endln(2);

  NTL::ZZ encrypted_dot_product = heratio.DotProduct(vc1, vc2, heratio.x0);

  std::cout << "Encrypted dot product: " << std::endl;
  std::cout << "encrypted_dot_product: " << encrypted_dot_product << endln(2);

  NTL::ZZ decrypted_dot_product = heratio.Decrypt(encrypted_dot_product);

  std::cout << "Decrypted dot product: " << std::endl;
  std::cout << "decrypted_dot_product: " << decrypted_dot_product << endln(2);

  Rational decoded_dot_product = hensel_code.Decode(decrypted_dot_product);

  std::cout << "Decoded dot product: " << std::endl;
  std::cout << "decoded_dot_product: " << decoded_dot_product.ToString()
            << endln(2);

  Rational plaintext_dot_product = DotProduct(vector1, vector2);

  std::cout << "Plaintext dot product: " << std::endl;
  std::cout << "plaintext_dot_product: " << plaintext_dot_product.ToString()
            << endln(2);
}