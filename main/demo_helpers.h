#pragma once

void SelectParameters(std::string &id, long &d, long &t, long &alpha,
                      long &beta, long &lambda, Heratio &heratio, HenselCode &hensel_code);

void DisplayDemoTitle(const int &option);

void HenselCodeDemo(Heratio heratio, HenselCode hensel_code);

void EncryptionDemo(Heratio &heratio, HenselCode &hensel_code);

void BasicHomomorphicOperationsDemo(Heratio &heratio, HenselCode &hensel_code);

void MainMenu(Heratio heratio, HenselCode hensel_code);

void DisplayMainMenu(std::string params);

void DisplayEncodingDecodingResults(Rational rational, Rational rational_decoded, NTL::ZZ h);

void EncodeDecodeRational(HenselCode &hensel_code, Rational &rational, NTL::ZZ &h, Rational &rational_decoded);

void DisplayEncryptionDecryptionResults(Rational &rational, Rational &rational_decoded,
                                        NTL::ZZ &h, NTL::ZZ &c, NTL::ZZ &h_decrypted);
void DisplayBasicHomomorphicResults(Rational &rational1, Rational &rational2,
                                    Rational &decoded_sum_result, Rational &decoded_mul_result,
                                    NTL::ZZ &h1, NTL::ZZ &h2,
                                    NTL::ZZ &c1, NTL::ZZ &c2,
                                    NTL::ZZ &c1_plus_c2, NTL::ZZ &c1_times_c2,
                                    NTL::ZZ &decrypted_sum_result, NTL::ZZ &decrypted_mul_result);

void CompositeHomomorphicOperationsDemo(Heratio &heratio, HenselCode &hensel_code);

void ReadInputVector(int index, int &size, std::vector<Rational> &vector);

void ShowConfig(Heratio &heratio);