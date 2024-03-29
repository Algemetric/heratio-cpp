#include "include_helper.h"

void PerformanceDemo(Heratio &heratio, HenselCode &hensel_code) {
  DisplayDemoTitle(6);
  KeyGenPerformance(heratio);
  HenselCodePerformance(hensel_code);
  EncryptionPerformance(heratio, hensel_code);
  BasicHomomorphismPerformance(heratio, hensel_code);
  CompositeHomomorphismPerformance(heratio, hensel_code);
  ComputeDepth(heratio, hensel_code);
}

void KeyGenPerformance(Heratio &heratio) {
  double milliseconds;

  std::cout << "Key Generation: ";
  auto start = std::chrono::high_resolution_clock::now();
  heratio.KeyGen(heratio.config);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);
}

void HenselCodePerformance(HenselCode &hensel_code) {
  double milliseconds;
  Rational rational = Rational(15, 19);

  std::cout << "Hensel Encoding: ";
  auto start = std::chrono::high_resolution_clock::now();
  NTL::ZZ h = hensel_code.Encode(rational);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);

  std::cout << "Hensel Decoding: ";
  start = std::chrono::high_resolution_clock::now();
  hensel_code.Decode(h);
  stop = std::chrono::high_resolution_clock::now();
  duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);
}

void EncryptionPerformance(Heratio &heratio, HenselCode &hensel_code) {
  double milliseconds;
  Rational rational = Rational(15, 19);
  NTL::ZZ h = hensel_code.Encode(rational);

  std::cout << "Encryption: ";
  auto start = std::chrono::high_resolution_clock::now();
  NTL::ZZ c = heratio.Encrypt(h);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);

  std::cout << "Decryption: ";
  start = std::chrono::high_resolution_clock::now();
  heratio.Decrypt(c);
  stop = std::chrono::high_resolution_clock::now();
  duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);
}

void BasicHomomorphismPerformance(Heratio &heratio, HenselCode &hensel_code) {
  double milliseconds;
  Rational rational1 = Rational(15, 19);
  Rational rational2 = Rational(13, 17);
  NTL::ZZ h1 = hensel_code.Encode(rational1);
  NTL::ZZ h2 = hensel_code.Encode(rational2);
  NTL::ZZ c1 = heratio.Encrypt(h1);
  NTL::ZZ c2 = heratio.Encrypt(h2);

  std::cout << "Homomorphic addition: ";
  auto start = std::chrono::high_resolution_clock::now();
  NTL::ZZ c1_plus_c2 = heratio.Add(c1, c2);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);

  std::cout << "Homomorphic multiplication: ";
  start = std::chrono::high_resolution_clock::now();
  NTL::ZZ c1_times_c2 = heratio.Mul(c1, c2);
  stop = std::chrono::high_resolution_clock::now();
  duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);
}

void CompositeHomomorphismPerformance(Heratio &heratio,
                                      HenselCode &hensel_code) {
  double milliseconds;
  std::vector<Rational> v1 = GenerateRandomVector(4, NTL::ZZ(50));
  std::vector<Rational> v2 = GenerateRandomVector(4, NTL::ZZ(50));
  NTL::Vec<NTL::ZZ> vh1 = hensel_code.EncodeVector(v1);
  NTL::Vec<NTL::ZZ> vh2 = hensel_code.EncodeVector(v2);
  NTL::Vec<NTL::ZZ> cvh1 = heratio.EncryptVector(vh1);
  NTL::Vec<NTL::ZZ> cvh2 = heratio.EncryptVector(vh2);

  std::cout << "Homomorphic dot product: ";
  auto start = std::chrono::high_resolution_clock::now();
  NTL::ZZ encrypted_dot_product = heratio.DotProduct(cvh1, cvh1, heratio.x0);
  auto stop = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = stop - start;
  milliseconds = duration.count();
  PrintDuration(milliseconds);
}

void ComputeDepth(Heratio &heratio, HenselCode &hensel_code) {
  std::vector<Rational> plaintexts;
  NTL::ZZ bound = NTL::ZZ(heratio.big_m);
  long depth = heratio.d;

  hensel_code.prime = heratio.q0_to_beta;

  std::cout << "Depth: " << heratio.d << std::endl;
  std::cout << "heratio.q0_to_beta: " << heratio.q0_to_beta << std::endl;
  std::cout << "hensel_code.prime: " << hensel_code.prime << std::endl;

  for (int i = 0; i < depth; i++) {
    plaintexts.push_back(GenerateRandomRational(bound));
  }

  NTL::Vec<NTL::ZZ> encodings = hensel_code.EncodeVector(plaintexts);
  NTL::Vec<NTL::ZZ> ciphertexts = heratio.EncryptVector(encodings);

  Rational rational_product = Product(plaintexts);
  NTL::ZZ encrypted_product = Product(ciphertexts, heratio.x0);
  NTL::ZZ encoded_product = heratio.Decrypt(encrypted_product);
  Rational decoded_product = hensel_code.Decode(encoded_product);

  std::cout << "Computing depth:" << std::endl;
  std::cout << "Decoded product: " << decoded_product.ToString() << std::endl;
  std::cout << "Rational product: " << rational_product.ToString() << std::endl;
  std::cout << "Equal? " << (decoded_product == rational_product) << std::endl;
}

void Average(NTL::Vec<NTL::ZZ> v, NTL::ZZ prime) {
  NTL::ZZ sum;
  NTL::ZZ avg;

  for (int i = 0; i < v.length(); i++) {
    sum += v[i];
  }
}

void PrintDuration(double milliseconds) {
  std::cout << milliseconds << " milliseconds" << endln(2);
}