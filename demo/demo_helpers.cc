#include <NTL/ZZ.h>
#include <string>
#include <vector>
#include <iostream>
#include "lib/include/rational.h"
#include "lib/include/hensel_code.h"
#include "lib/include/tools.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "demo/demo_helpers.h"

void SelectParameters(std::string &id, long &d, long &t, long &alpha,
                      long &beta, long &lambda, Heratio &heratio, HenselCode &hensel_code)
{
  if (id == "toy" || id == "default")
  {
    d = 2;
    t = 3;
    alpha = 3;
    beta = 1;
    lambda = 32;

    heratio.KeyGen(d, t, alpha, beta, lambda);
    hensel_code.prime = heratio.q_star;
    hensel_code.r = 1;
  }
  else
  {
    std::cout << "Unknown selection. Continuing with default parameters." << endln(2);
  }
}

void DisplayDemoTitle(const int &option)
{
  std::string title;
  if (option == -1)
  {
    title = "HERatio Demo";
  }
  else if (option == 1)
  {
    title = "HERatio: Hensel Code Demo";
  }
  else if (option == 2)
  {
    title = "HERatio: Encryption/Decryption Demo";
  }
  else if (option == 3)
  {
    title = "HERatio: Basic Homomorphic Operations Demo";
  }
  else if (option == 4)
  {
    title = "HERatio: Composite Homomorphic Operations Demo";
  }
  else if (option == 5)
  {
    title = "HERatio: Show Config";
  }

  std::cout << "\n\n===============================================" << std::endl;
  std::cout << title << std::endl;
  std::cout << "===============================================" << endln(2);
}

void HenselCodeDemo(Heratio heratio, HenselCode hensel_code)
{

  std::string string;
  DisplayDemoTitle(1);
  std::cout << "Encoding with q_star: " << heratio.q_star << std::endl;
  std::cout << "No exponent" << endln(2);
  std::cout << "Type a rational number:\n\n";
  std::cin >> string;

  Rational rational = StringToRational(string);
  Rational rational_decoded;
  NTL::ZZ h;

  EncodeDecodeRational(hensel_code, rational, h, rational_decoded);
  DisplayEncodingDecodingResults(rational, rational_decoded, h);
}

void EncryptionDemo(Heratio &heratio, HenselCode &hensel_code)
{
  std::string string;
  Rational rational;
  Rational rational_decoded;
  NTL::ZZ h;
  NTL::ZZ c;
  NTL::ZZ h_decrypted;

  DisplayDemoTitle(2);

  std::cout << "Type a rational number:\n\n";
  std::cin >> string;

  rational = StringToRational(string);
  h = hensel_code.Encode(rational);
  c = heratio.Encrypt(h);
  h_decrypted = heratio.Decrypt(c);
  rational_decoded = hensel_code.Decode(h_decrypted);

  DisplayEncryptionDecryptionResults(rational, rational_decoded,
                                     h, c, h_decrypted);
}

void BasicHomomorphicOperationsDemo(Heratio &heratio, HenselCode &hensel_code)
{
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

  DisplayBasicHomomorphicResults(rational1, rational2,
                                 decoded_sum_result, decoded_mul_result,
                                 h1, h2,
                                 c1, c2,
                                 c1_plus_c2, c1_times_c2,
                                 decrypted_sum_result, decrypted_mul_result);
}

void CompositeHomomorphicOperationsDemo(Heratio &heratio, HenselCode &hensel_code)
{
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
  std::cout << "decoded_dot_product: " << decoded_dot_product.ToString() << endln(2);

  Rational plaintext_dot_product = DotProduct(vector1, vector2);

  std::cout << "Plaintext dot product: " << std::endl;
  std::cout << "plaintext_dot_product: " << plaintext_dot_product.ToString() << endln(2);
}

void ReadInputVector(int index, int &size, std::vector<Rational> &vector)
{
  std::string string;
  Rational rational;

  std::cout << "\nDefininig vector #" << index << std::endl;
  for (int i = 0; i < size; i++)
  {
    std::cout << "Type rational number for unit basis e" << i + 1 << ": ";
    std::cin >> string;
    rational = StringToRational(string);
    vector.push_back(rational);
  }
}

void MainMenu(Heratio heratio, HenselCode hensel_code)
{
  int option = -1;
  std::string params = "Default";

  while (option != 9)
  {
    Clear();
    DisplayDemoTitle(-1);
    DisplayMainMenu(params);
    std::cin >> option;

    if (option == 0)
    {
      Clear();
      std::cout << "Choose a set of parameters:\n\n";
      std::cout << "toy - Toy Configuration for smaller values" << std::endl;
      std::cin >> params;
      Clear();
    }
    else if (option == 1)
    {
      Clear();
      HenselCodeDemo(heratio, hensel_code);
    }
    else if (option == 2)
    {
      Clear();
      EncryptionDemo(heratio, hensel_code);
    }
    else if (option == 3)
    {
      Clear();
      BasicHomomorphicOperationsDemo(heratio, hensel_code);
    }
    else if (option == 4)
    {
      Clear();
      CompositeHomomorphicOperationsDemo(heratio, hensel_code);
    }
    else if (option == 5)
    {
      Clear();
      ShowConfig(heratio);
    }
    else if (option == 6)
    {
      Clear();
    }
    else if (option == 9)
    {
      std::cout << "End of demo" << std::endl;
    }
    else
    {
      Clear();
      std::cout << "Unknown option. Please try again." << std::endl;
    }
  }
}

void DisplayMainMenu(std::string params)
{
  std::cout << "Choose an option:\n\n";
  std::cout << "0 - Select parameters (using " << params << " config)" << std::endl;
  std::cout << "1 - Hensel Code" << std::endl;
  std::cout << "2 - Encryption/Decryption" << std::endl;
  std::cout << "3 - Basic Homomorphic operations" << std::endl;
  std::cout << "4 - Composite Homomorphic operations" << std::endl;
  std::cout << "5 - Show Config" << std::endl;
  std::cout << "6 - Clear" << std::endl;
  std::cout << "9 - Quit\n\n";
}

void DisplayEncodingDecodingResults(Rational rational, Rational rational_decoded, NTL::ZZ h)
{
  Clear();
  DisplayDemoTitle(1);
  std::cout << "Encoding/decoding results:" << std::endl;
  std::cout << "Hensel code: " << h << std::endl;
  std::cout << "Rational: " << rational.ToString() << std::endl;
  std::cout << "Decoded rational: " << rational_decoded.ToString() << "\n\n";
}

void EncodeDecodeRational(HenselCode &hensel_code, Rational &rational, NTL::ZZ &h, Rational &rational_decoded)
{
  h = hensel_code.Encode(rational);
  rational_decoded = hensel_code.Decode(h);
}

void DisplayEncryptionDecryptionResults(Rational &rational, Rational &rational_decoded,
                                        NTL::ZZ &h, NTL::ZZ &c, NTL::ZZ &h_decrypted)
{
  Clear();
  DisplayDemoTitle(2);
  std::cout << "Encryption/decryption results:" << std::endl;
  std::cout << "Rational: " << rational.ToString() << std::endl;
  std::cout << "Encoded rational: " << h << std::endl;
  std::cout << "Ciphertext: " << c << std::endl;
  std::cout << "Decrypted encoded rational: " << h_decrypted << "\n\n";
  std::cout << "Decoded rational: " << rational_decoded.ToString() << "\n\n";
}

void DisplayBasicHomomorphicResults(Rational &rational1, Rational &rational2,
                                    Rational &decoded_sum_result, Rational &decoded_mul_result,
                                    NTL::ZZ &h1, NTL::ZZ &h2,
                                    NTL::ZZ &c1, NTL::ZZ &c2,
                                    NTL::ZZ &c1_plus_c2, NTL::ZZ &c1_times_c2,
                                    NTL::ZZ &decrypted_sum_result, NTL::ZZ &decrypted_mul_result)
{
  Clear();
  DisplayDemoTitle(3);
  std::cout << "Basic Homomorphic results:" << std::endl;
  std::cout << "rational1: " << rational1.ToString() << std::endl;
  std::cout << "rational2: " << rational2.ToString() << std::endl;
  std::cout << "h1: " << h1 << std::endl;
  std::cout << "h2: " << h2 << std::endl;
  std::cout << "c1: " << c1 << std::endl;
  std::cout << "c2: " << c2 << std::endl;
  std::cout << "c1_plus_c2: " << c1_plus_c2 << std::endl;
  std::cout << "c1_times_c2: " << c1_times_c2 << std::endl;
  std::cout << "decrypted_sum_result: " << decrypted_sum_result << "\n\n";
  std::cout << "decrypted_mul_result: " << decrypted_mul_result << "\n\n";
  std::cout << "decoded_sum_result: " << decoded_sum_result.ToString() << "\n\n";
  std::cout << "decoded_mul_result: " << decoded_mul_result.ToString() << "\n\n";
}

void ShowConfig(Heratio &heratio)
{
  DisplayDemoTitle(5);
  std::cout << "Arguments passed to key generation:" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "d = " << heratio.d << std::endl;
  std::cout << "t = " << heratio.t << std::endl;
  std::cout << "alpha = " << heratio.alpha << std::endl;
  std::cout << "beta = " << heratio.beta << std::endl;
  std::cout << "lambda = " << heratio.lambda << endln(2);

  std::cout << "Computed parameters:" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "gamma = " << heratio.gamma << std::endl;
  std::cout << "eta = " << heratio.eta << std::endl;
  std::cout << "mu = " << heratio.mu << std::endl;
  std::cout << "sigma = " << heratio.lambda << endln(2);

  std::cout << "Computed values:" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "p = " << heratio.p << std::endl;
  std::cout << "q0 = " << heratio.q0 << std::endl;
  std::cout << "p_to_alpha = " << heratio.p_to_alpha << std::endl;
  std::cout << "q0_to_beta = " << heratio.q0_to_beta << std::endl;
  std::cout << "x0 = " << heratio.x0 << std::endl;
  std::cout << "q_star = " << heratio.q_star << endln(2);
}