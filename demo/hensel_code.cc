#include "include_helper.h"

void HenselCodeDemo(Heratio heratio, HenselCode hensel_code) {

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

void EncodeDecodeRational(HenselCode &hensel_code, Rational &rational,
                          NTL::ZZ &h, Rational &rational_decoded) {
  h = hensel_code.Encode(rational);
  rational_decoded = hensel_code.Decode(h);
}