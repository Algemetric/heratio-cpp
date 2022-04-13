#include <NTL/ZZ.h>
#include <vector>
#include <string>
#include "lib/include/rational.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "gtest/gtest.h"

TEST(InspectTools, InspectRationalVector)
{
  std::vector<Rational> v = {Rational(2, 3), Rational(4, 5), Rational(6, 7)};
  std::string expected_result = "<Vector 2/3, 4/5, 6/7>";

  EXPECT_EQ(expected_result, Inspect(v));
}

TEST(InspectTools, InspectZZVector)
{
  NTL::Vec<NTL::ZZ> v;
  v.SetLength(3);
  v[0] = NTL::ZZ(11);
  v[1] = NTL::ZZ(13);
  v[2] = NTL::ZZ(14);
  std::string expected_result = "<Vector 11, 13, 14>";

  EXPECT_EQ(expected_result, Inspect(v));
}