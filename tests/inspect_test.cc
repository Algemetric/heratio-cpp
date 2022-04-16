#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "lib/include/rational.h"
#include "gtest/gtest.h"
#include <NTL/ZZ.h>
#include <string>
#include <vector>

TEST(InspectTools, InspectHeratio) {
  const long d = 2;
  const long t = 3;
  const long alpha = 3;
  const long beta = 1;
  const long lambda = 18;

  Heratio heratio;
  heratio.KeyGen(d, t, alpha, beta, lambda);

  std::string expected_result = "";
  expected_result += "Heratio instance:\n\n";
  expected_result += "d = 2\n";
  expected_result += "t = 3\n";
  expected_result += "alpha = 3\n";
  expected_result += "beta = 1\n";
  expected_result += "lambda = 18\n\n";
  expected_result += "eta = 324\n";
  expected_result += "mu = 77\n";
  expected_result += "sigma = 406\n";
  expected_result += "gamma = 1049\n\n";
  expected_result += "q0_bits = 77\n";
  expected_result += "p_bits = 324\n";
  expected_result += "q_star_bits = 38\n\n";

  EXPECT_EQ(expected_result, Inspect(heratio));
}

TEST(InspectTools, InspectRationalVector) {
  std::vector<Rational> v = {Rational(2, 3), Rational(4, 5), Rational(6, 7)};
  std::string expected_result = "<Vector 2/3, 4/5, 6/7>";

  EXPECT_EQ(expected_result, Inspect(v));
}

TEST(InspectTools, InspectZZVector) {
  NTL::Vec<NTL::ZZ> v;
  v.SetLength(3);
  v[0] = NTL::ZZ(11);
  v[1] = NTL::ZZ(13);
  v[2] = NTL::ZZ(14);
  std::string expected_result = "<Vector 11, 13, 14>";

  EXPECT_EQ(expected_result, Inspect(v));
}