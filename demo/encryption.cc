#include "include_helper.h"

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