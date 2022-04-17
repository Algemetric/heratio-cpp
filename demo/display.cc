#include "include_helper.h"

void DisplayDemoTitle(const int &option) {
  std::string title;
  if (option == -1) {
    title = "HERatio Demo";
  } else if (option == 1) {
    title = "HERatio: Hensel Code Demo";
  } else if (option == 2) {
    title = "HERatio: Encryption/Decryption Demo";
  } else if (option == 3) {
    title = "HERatio: Basic Homomorphic Operations Demo";
  } else if (option == 4) {
    title = "HERatio: Composite Homomorphic Operations Demo";
  } else if (option == 5) {
    title = "HERatio: Show Config";
  } else if (option == 6) {
    title = "HERatio: Performance";
  } else {
    title = "HERatio: Unknown Selection";
  }

  std::cout << "\n\n==============================================="
            << std::endl;
  std::cout << title << std::endl;
  std::cout << "===============================================" << endln(2);
}

void MainMenu(int64_t &d, int64_t &t, int64_t &alpha, int64_t &beta,
              int64_t &lambda, Heratio heratio, HenselCode hensel_code) {
  int option = -1;
  std::string params = "default";

  while (option != 9) {
    DisplayDemoTitle(-1);
    DisplayMainMenu(params);
    std::cin >> option;

    if (option == 0) {
      Clear();
      std::cout << "Choose a set of parameters:\n\n";
      std::cout << "toy, small, medium, large, or larger" << std::endl;
      std::cin >> params;
      SelectParameters(params, d, t, alpha, beta, lambda, heratio, hensel_code);
      Clear();
    } else if (option == 1) {
      Clear();
      HenselCodeDemo(heratio, hensel_code);
    } else if (option == 2) {
      Clear();
      EncryptionDemo(heratio, hensel_code);
    } else if (option == 3) {
      Clear();
      BasicHomomorphicOperationsDemo(heratio, hensel_code);
    } else if (option == 4) {
      Clear();
      CompositeHomomorphicOperationsDemo(heratio, hensel_code);
    } else if (option == 5) {
      Clear();
      ShowConfig(heratio);
    } else if (option == 6) {
      Clear();
      PerformanceDemo(heratio, hensel_code);
    } else if (option == 7) {
      Clear();
    } else if (option == 9) {
      std::cout << "End of demo" << std::endl;
    } else {
      Clear();
      std::cout << "Unknown option. Please try again." << std::endl;
    }
  }
}

void DisplayMainMenu(std::string params) {
  std::cout << "Choose an option:\n\n";
  std::cout << "0 - Select parameters (using " << params << " config)"
            << std::endl;
  std::cout << "1 - Hensel Code" << std::endl;
  std::cout << "2 - Encryption/Decryption" << std::endl;
  std::cout << "3 - Basic Homomorphic operations" << std::endl;
  std::cout << "4 - Composite Homomorphic operations" << std::endl;
  std::cout << "5 - Show Config" << std::endl;
  std::cout << "6 - Performance" << std::endl;
  std::cout << "7 - Clear" << std::endl;
  std::cout << "9 - Quit\n\n";
}

void DisplayEncodingDecodingResults(Rational rational,
                                    Rational rational_decoded, NTL::ZZ h) {
  Clear();
  DisplayDemoTitle(1);
  std::cout << "Encoding/decoding results:" << std::endl;
  std::cout << "Hensel code: " << h << std::endl;
  std::cout << "Rational: " << rational.ToString() << std::endl;
  std::cout << "Decoded rational: " << rational_decoded.ToString() << "\n\n";
}

void DisplayEncryptionDecryptionResults(Rational &rational,
                                        Rational &rational_decoded, NTL::ZZ &h,
                                        NTL::ZZ &c, NTL::ZZ &h_decrypted) {
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
                                    Rational &decoded_sum_result,
                                    Rational &decoded_mul_result, NTL::ZZ &h1,
                                    NTL::ZZ &h2, NTL::ZZ &c1, NTL::ZZ &c2,
                                    NTL::ZZ &c1_plus_c2, NTL::ZZ &c1_times_c2,
                                    NTL::ZZ &decrypted_sum_result,
                                    NTL::ZZ &decrypted_mul_result) {
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
  std::cout << "decoded_sum_result: " << decoded_sum_result.ToString()
            << "\n\n";
  std::cout << "decoded_mul_result: " << decoded_mul_result.ToString()
            << "\n\n";
}

void ShowConfig(Heratio &heratio) {
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
  std::cout << "sigma = " << heratio.sigma << endln(2);

  std::cout << "Computed values:" << std::endl;
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "p = " << heratio.p << std::endl;
  std::cout << "q0 = " << heratio.q0 << std::endl;
  std::cout << "p_to_alpha = " << heratio.p_to_alpha << std::endl;
  std::cout << "q0_to_beta = " << heratio.q0_to_beta << std::endl;
  std::cout << "x0 = " << heratio.x0 << std::endl;
  std::cout << "q_star = " << heratio.q_star << endln(2);
}