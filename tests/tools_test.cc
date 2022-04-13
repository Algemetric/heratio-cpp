#include <NTL/ZZ.h>
#include <NTL/vector.h>
#include <NTL/ZZ_p.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "lib/include/rational.h"
#include "lib/include/heratio.h"
#include "lib/include/inspect.h"
#include "lib/include/hensel_code.h"
#include "lib/include/tools.h"
#include "gtest/gtest.h"

TEST(ToolsTest, RandomInteger)
{
  long bound = 30;
  NTL::ZZ number = GenerateNonZeroRandomInteger(NTL::ZZ(bound));

  EXPECT_TRUE((0 <= number) && (number < bound));
}

TEST(ToolsTest, RandomVector)
{
  long bound = 50;
  long size1 = 3;
  long size2 = 2;
  std::vector<Rational> v1 = GenerateRandomVector(size1, NTL::ZZ(bound));
  std::vector<Rational> v2 = GenerateRandomVector(size2, NTL::ZZ(bound));

  EXPECT_EQ(size1, v1.size());
  EXPECT_TRUE((0 <= v1[0].numerator) && (v1[0].numerator < bound));
  EXPECT_TRUE((0 <= v1[0].denominator) && (v1[0].denominator < bound));
  EXPECT_TRUE((0 <= v1[1].numerator) && (v1[1].numerator < bound));
  EXPECT_TRUE((0 <= v1[1].denominator) && (v1[1].denominator < bound));
  EXPECT_TRUE((0 <= v1[2].numerator) && (v1[2].numerator < bound));
  EXPECT_TRUE((0 <= v1[2].denominator) && (v1[2].denominator < bound));
  EXPECT_EQ(size2, v2.size());
  EXPECT_TRUE((0 <= v2[0].numerator) && (v2[0].numerator < bound));
  EXPECT_TRUE((0 <= v2[0].denominator) && (v2[0].denominator < bound));
  EXPECT_TRUE((0 <= v2[1].numerator) && (v2[1].numerator < bound));
  EXPECT_TRUE((0 <= v2[1].denominator) && (v2[1].denominator < bound));
}

TEST(ToolsTest, VectorFromUniqueValue)
{
  long size = 5;
  NTL::ZZ value = NTL::ZZ(36);
  NTL::Vec<NTL::ZZ> v = CreateVectorFromUniqueValue(size, value);

  EXPECT_EQ(size, v.length());
  EXPECT_EQ(value, v[0]);
  EXPECT_EQ(value, v[1]);
  EXPECT_EQ(value, v[2]);
  EXPECT_EQ(value, v[3]);
  EXPECT_EQ(value, v[4]);
}

TEST(ToolsTest, DotProduct)
{
  std::vector<Rational> v1 = {Rational(2, 3), Rational(4, 5), Rational(6, 7)};
  std::vector<Rational> v2 = {Rational(8, 9), Rational(10, 11), Rational(12, 13)};
  Rational expected_dot_product1 = Rational(57056, 27027);

  NTL::Vec<NTL::ZZ> v3;
  v3.SetLength(3);
  v3[0] = NTL::ZZ(2);
  v3[1] = NTL::ZZ(3);
  v3[2] = NTL::ZZ(4);

  NTL::Vec<NTL::ZZ> v4;
  v4.SetLength(3);
  v4[0] = NTL::ZZ(5);
  v4[1] = NTL::ZZ(6);
  v4[2] = NTL::ZZ(7);
  NTL::ZZ expected_dot_product2 = NTL::ZZ(56);

  EXPECT_TRUE(expected_dot_product1 == DotProduct(v1, v2));
  EXPECT_TRUE(expected_dot_product2 == DotProduct(v3, v4));
}