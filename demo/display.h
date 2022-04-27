#pragma once

#include "lib/include/hensel_code.h"
#include "lib/include/heratio.h"
#include "lib/include/rational.h"

void DisplayDemoTitle(const int &option);

void MainMenu(Heratio heratio, HenselCode hensel_code);

void DisplayMainMenu(std::string params);

void DisplayEncodingDecodingResults(Rational rational,
                                    Rational rational_decoded, NTL::ZZ h);

void DisplayEncryptionDecryptionResults(Rational &rational,
                                        Rational &rational_decoded, NTL::ZZ &h,
                                        NTL::ZZ &c, NTL::ZZ &h_decrypted);

void DisplayBasicHomomorphicResults(Rational &rational1, Rational &rational2,
                                    Rational &decoded_sum_result,
                                    Rational &decoded_mul_result, NTL::ZZ &h1,
                                    NTL::ZZ &h2, NTL::ZZ &c1, NTL::ZZ &c2,
                                    NTL::ZZ &c1_plus_c2, NTL::ZZ &c1_times_c2,
                                    NTL::ZZ &decrypted_sum_result,
                                    NTL::ZZ &decrypted_mul_result);

void ShowConfig(Heratio &heratio);