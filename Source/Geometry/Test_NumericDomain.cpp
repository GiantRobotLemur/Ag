//! @file Test_NumericDomain.cpp
//! @brief The definition of unit tests for the NumericDomain class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Geometry/NumericDomain.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(NumericDomain, UnsignedIsNearZero)
{
    const double epsilon = NumericDomain::UnsignedScalar.getTolerance();

    EXPECT_LT(epsilon, 0.00001);
    EXPECT_GT(epsilon, 0.0);
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearZero(0.0));
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearZero(epsilon * 0.1));
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearZero(epsilon * -0.1));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearZero(epsilon * 1.1));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearZero(epsilon * -1.1));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearZero(1.0));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearZero(-0.1));
}

GTEST_TEST(NumericDomain, UnsignedIsNearEqual)
{
    const double epsilon = NumericDomain::UnsignedScalar.getTolerance();

    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearEqual(0.0, 0.0));
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearEqual(3.0, 3.0));
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearEqual(1.0, 1.0 + (epsilon * 0.1)));
    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearEqual(-1.0, -1.0 + (epsilon * -0.1)));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearEqual(1.0, 1.1));
    EXPECT_FALSE(NumericDomain::UnsignedScalar.isNearEqual(1.0, 1.0 + epsilon));
}

GTEST_TEST(NumericDomain, UnsignedCompare)
{
    const double epsilon = NumericDomain::UnsignedScalar.getTolerance();

    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(0.0, 0.0), 0);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(1.0, 1.0), 0);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(-12.0, 9.0), -1);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(12.0, 9.0), 1);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(1.0, 1.0 + epsilon), -1);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(1.0, 1.0 + (epsilon * 0.1)), 0);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(1.0 + epsilon, 1.0), 1);
    EXPECT_EQ(NumericDomain::UnsignedScalar.compare(1.0 + (epsilon * 0.1), 1.0), 0);
}


GTEST_TEST(NumericDomain, SignedIsNearZero)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();

    EXPECT_LT(epsilon, 0.00001);
    EXPECT_GT(epsilon, 0.0);
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearZero(0.0));
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearZero(epsilon * 0.1));
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearZero(epsilon * -0.1));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearZero(epsilon * 1.1));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearZero(epsilon * -1.1));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearZero(1.0));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearZero(-0.1));
}

GTEST_TEST(NumericDomain, SignedIsNearEqual)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();

    EXPECT_TRUE(NumericDomain::SignedScalar.isNearEqual(0.0, 0.0));
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearEqual(3.0, 3.0));
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearEqual(1.0, 1.0 + (epsilon * 0.1)));
    EXPECT_TRUE(NumericDomain::SignedScalar.isNearEqual(-1.0, -1.0 + (epsilon * -0.1)));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearEqual(1.0, 1.1));
    EXPECT_FALSE(NumericDomain::SignedScalar.isNearEqual(1.0, 1.0 + (epsilon * 1.1)));
}

GTEST_TEST(NumericDomain, SignedCompare)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();

    EXPECT_EQ(NumericDomain::SignedScalar.compare(0.0, 0.0), 0);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(1.0, 1.0), 0);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(-12.0, 9.0), -1);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(12.0, 9.0), 1);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(1.0, 1.0 + (epsilon * 1.1)), -1);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(1.0, 1.0 + (epsilon * 0.1)), 0);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(1.0 + (epsilon * 1.1), 1.0), 1);
    EXPECT_EQ(NumericDomain::SignedScalar.compare(1.0 + (epsilon * 0.1), 1.0), 0);
}

GTEST_TEST(NumericDomain, IsLessThan)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();
    const NumericDomain &specimen = NumericDomain::SignedScalar;

    // Ensure we get true when the first value is less than by more than
    // the tolerance.
    EXPECT_TRUE(specimen.isLessThan(1.0, 1.0 + (epsilon * 1.1)));
    EXPECT_TRUE(specimen.isLessThan(-1.0 - (epsilon * 1.1), -1.0));

    // Ensure we get false when the first value is less than by less than
    // the tolerance.
    EXPECT_FALSE(specimen.isLessThan(1.0, 1.0 + (epsilon * 0.9)));
    EXPECT_FALSE(specimen.isLessThan(-1.0 - (epsilon * 0.9), -1.0));

    // Ensure we get false when the first value is greater than the
    // other by more than the tolerance.
    EXPECT_FALSE(specimen.isLessThan(1.0 + (epsilon * 1.1), 1.0));
    EXPECT_FALSE(specimen.isLessThan(-1.0, -1.0 - (epsilon * 1.1)));

    // Ensure we get false when the first value is greater than the
    // other by less than the tolerance.
    EXPECT_FALSE(specimen.isLessThan(1.0 + (epsilon * 0.9), 1.0));
    EXPECT_FALSE(specimen.isLessThan(-1.0, -1.0 - (epsilon * 0.9)));
}

GTEST_TEST(NumericDomain, IsLessThanOrEqual)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();
    const NumericDomain &specimen = NumericDomain::SignedScalar;

    // Ensure we get true when the first value is less than by more than
    // the tolerance.
    EXPECT_TRUE(specimen.isLessThanOrEqual(1.0, 1.0 + (epsilon * 1.1)));
    EXPECT_TRUE(specimen.isLessThanOrEqual(-1.0 - (epsilon * 1.1), -1.0));

    // Ensure we get true when the first value is less than by less than
    // the tolerance.
    EXPECT_TRUE(specimen.isLessThanOrEqual(1.0, 1.0 + (epsilon * 0.9)));
    EXPECT_TRUE(specimen.isLessThanOrEqual(-1.0 - (epsilon * 0.9), -1.0));

    // Ensure we get false when the first value is greater than the
    // other by more than the tolerance.
    EXPECT_FALSE(specimen.isLessThanOrEqual(1.0 + (epsilon * 1.1), 1.0));
    EXPECT_FALSE(specimen.isLessThanOrEqual(-1.0, -1.0 - (epsilon * 1.1)));

    // Ensure we get false when the first value is greater than the
    // other by less than the tolerance.
    EXPECT_TRUE(specimen.isLessThanOrEqual(1.0 + (epsilon * 0.9), 1.0));
    EXPECT_TRUE(specimen.isLessThanOrEqual(-1.0, -1.0 - (epsilon * 0.9)));
}

GTEST_TEST(NumericDomain, IsGreaterThan)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();
    const NumericDomain &specimen = NumericDomain::SignedScalar;

    // Ensure we get false when the second value is greater than by more than
    // the tolerance.
    EXPECT_FALSE(specimen.isGreaterThan(1.0, 1.0 + (epsilon * 1.1)));
    EXPECT_FALSE(specimen.isGreaterThan(-1.0 - (epsilon * 1.1), -1.0));

    // Ensure we get false when the first value is greater than by less than
    // the tolerance.
    EXPECT_FALSE(specimen.isGreaterThan(1.0, 1.0 + (epsilon * 0.9)));
    EXPECT_FALSE(specimen.isGreaterThan(-1.0 - (epsilon * 0.9), -1.0));

    // Ensure we get true when the first value is greater than the
    // other by more than the tolerance.
    EXPECT_TRUE(specimen.isGreaterThan(1.0 + (epsilon * 1.1), 1.0));
    EXPECT_TRUE(specimen.isGreaterThan(-1.0, -1.0 - (epsilon * 1.1)));

    // Ensure we get false when the first value is greater than the
    // other by less than the tolerance.
    EXPECT_FALSE(specimen.isGreaterThan(1.0 + (epsilon * 0.9), 1.0));
    EXPECT_FALSE(specimen.isGreaterThan(-1.0, -1.0 - (epsilon * 0.9)));
}

GTEST_TEST(NumericDomain, IsGreaterThanOrEqual)
{
    const double epsilon = NumericDomain::SignedScalar.getTolerance();
    const NumericDomain &specimen = NumericDomain::SignedScalar;

    // Ensure we get false when the second value is greater than by more than
    // the tolerance.
    EXPECT_FALSE(specimen.isGreaterThanOrEqual(1.0, 1.0 + (epsilon * 1.1)));
    EXPECT_FALSE(specimen.isGreaterThanOrEqual(-1.0 - (epsilon * 1.1), -1.0));

    // Ensure we get true when the first value is greater than by less than
    // the tolerance.
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(1.0, 1.0 + (epsilon * 0.9)));
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(-1.0 - (epsilon * 0.9), -1.0));

    // Ensure we get true when the first value is greater than the
    // other by more than the tolerance.
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(1.0 + (epsilon * 1.1), 1.0));
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(-1.0, -1.0 - (epsilon * 1.1)));

    // Ensure we get false when the first value is greater than the
    // other by less than the tolerance.
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(1.0 + (epsilon * 0.9), 1.0));
    EXPECT_TRUE(specimen.isGreaterThanOrEqual(-1.0, -1.0 - (epsilon * 0.9)));
}

} // Anonymous namespace.

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

