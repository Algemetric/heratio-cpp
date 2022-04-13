#include <NTL/ZZ.h>
#include <string>
#include "lib/include/rational.h"
#include "gtest/gtest.h"

TEST(RationalTest, RationalConstructor)
{
  Rational rational = Rational(NTL::ZZ(8), NTL::ZZ(9));

  EXPECT_EQ(8, rational.numerator);
  EXPECT_EQ(9, rational.denominator);
}

TEST(RationalTest, IrreducibleFraction)
{
  Rational rat1 = Rational(NTL::ZZ(8), NTL::ZZ(4));
  Rational rat2 = Rational(NTL::ZZ(9), NTL::ZZ(6));

  EXPECT_EQ(2, rat1.numerator);
  EXPECT_EQ(1, rat1.denominator);
  EXPECT_EQ(3, rat2.numerator);
  EXPECT_EQ(2, rat2.denominator);
}

TEST(RationalTest, ToString)
{
  Rational rat1 = Rational(NTL::ZZ(5), NTL::ZZ(3));
  Rational rat2 = Rational(NTL::ZZ(7), NTL::ZZ(4));

  EXPECT_EQ("5/3", rat1.ToString());
  EXPECT_EQ("7/4", rat2.ToString());
}

TEST(RationalTest, Addition)
{
  Rational rat1 = Rational(NTL::ZZ(2), NTL::ZZ(3));
  Rational rat2 = Rational(NTL::ZZ(3), NTL::ZZ(5));
  Rational rat3 = rat1 + rat2;

  EXPECT_EQ("19/15", rat3.ToString());
}

TEST(RationalTest, Subtraction)
{
  Rational rat1 = Rational(NTL::ZZ(2), NTL::ZZ(3));
  Rational rat2 = Rational(NTL::ZZ(3), NTL::ZZ(5));
  Rational rat3 = rat1 - rat2;

  EXPECT_EQ("1/15", rat3.ToString());
}

TEST(RationalTest, Multiplication)
{
  Rational rat1 = Rational(NTL::ZZ(2), NTL::ZZ(3));
  Rational rat2 = Rational(NTL::ZZ(3), NTL::ZZ(5));
  Rational rat3 = rat1 * rat2;

  EXPECT_EQ("2/5", rat3.ToString());
}

TEST(RationalTest, Division)
{
  Rational rat1 = Rational(NTL::ZZ(2), NTL::ZZ(3));
  Rational rat2 = Rational(NTL::ZZ(3), NTL::ZZ(5));
  Rational rat3 = rat1 / rat2;

  EXPECT_EQ("10/9", rat3.ToString());
}

TEST(RationalTest, RationalEquality)
{
  Rational rat1 = Rational(2, 3);
  Rational rat2 = Rational(2, 3);
  Rational rat3 = Rational(4, 3);

  EXPECT_TRUE(rat1 == rat2);
  EXPECT_FALSE(rat1 == rat3);
  EXPECT_FALSE(rat2 == rat3);
}