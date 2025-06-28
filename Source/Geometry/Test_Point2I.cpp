//! @file Geometry/Test_Point2I.cpp
//! @brief The definition of unit tests for the Point2I class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include <gtest/gtest.h>

#include "Ag/Core/Exception.hpp"

#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Size2I.hpp"

namespace Ag {
namespace Geom {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Point2I, DefaultConstruct)
{
    Point2I specimen;

    EXPECT_EQ(specimen.getX(), 0);
    EXPECT_EQ(specimen.getY(), 0);
    EXPECT_EQ(specimen.getXRef(), 0);
    EXPECT_EQ(specimen.getYRef(), 0);

    const Point2I &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), 0);
    EXPECT_EQ(specRef.getYRef(), 0);
}

GTEST_TEST(Point2I, ComponentConstruct)
{
    Point2I specimen(12, -42);

    EXPECT_EQ(specimen.getX(), 12);
    EXPECT_EQ(specimen.getY(), -42);
    EXPECT_EQ(specimen.getXRef(), 12);
    EXPECT_EQ(specimen.getYRef(), -42);

    const Point2I &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), 12);
    EXPECT_EQ(specRef.getYRef(), -42);
}

GTEST_TEST(Point2I, SizeConstruct)
{
    const Size2I inputSize(32, 9);
    Point2I specimen(inputSize);

    EXPECT_EQ(specimen.getX(), inputSize.getWidth());
    EXPECT_EQ(specimen.getY(), inputSize.getHeight());
    EXPECT_EQ(specimen.getXRef(), inputSize.getWidth());
    EXPECT_EQ(specimen.getYRef(), inputSize.getHeight());

    const Point2I &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), inputSize.getWidth());
    EXPECT_EQ(specRef.getYRef(), inputSize.getHeight());
}

GTEST_TEST(Point2I, Addition)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs + rhs;

    EXPECT_EQ(result.getX(), lhs.getX() + rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() + rhs.getY());
}

GTEST_TEST(Point2I, Subtraction)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs - rhs;

    EXPECT_EQ(result.getX(), lhs.getX() - rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() - rhs.getY());
}

GTEST_TEST(Point2I, Negation)
{
    const Point2I specimen(12, -42);

    Point2I result = -specimen;

    EXPECT_EQ(result.getX(), -specimen.getX());
    EXPECT_EQ(result.getY(), -specimen.getY());
}

GTEST_TEST(Point2I, Multiplication)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs * rhs;

    EXPECT_EQ(result.getX(), lhs.getX() * rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() * rhs.getY());
}

GTEST_TEST(Point2I, Division)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs / rhs;

    EXPECT_EQ(result.getX(), lhs.getX() / rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() / rhs.getY());
}

GTEST_TEST(Point2I, DivisionByZero)
{
    const Point2I lhs(12, -42);
    const Point2I rhsXZero(0, 9);
    const Point2I rhsYZero(11, 0);
    const Point2I rhsBothZero(0, 0);

    EXPECT_THROW({ Point2I result = lhs / rhsXZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2I result = lhs / rhsYZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2I result = lhs / rhsBothZero; }, Ag::DivisionByZeroException);
}

GTEST_TEST(Point2I, AdditionInPlace)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);
    Point2I specimen = lhs;

    specimen += rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() + rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() + rhs.getY());
}

GTEST_TEST(Point2I, SubtractionInPlace)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);
    Point2I specimen = lhs;

    specimen -= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() - rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() - rhs.getY());
}

GTEST_TEST(Point2I, MultiplicationInPlace)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);
    Point2I specimen = lhs;

    specimen *= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() * rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() * rhs.getY());
}

GTEST_TEST(Point2I, DivisionInPlace)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);
    Point2I specimen = lhs;

    specimen /= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() / rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() / rhs.getY());
}

GTEST_TEST(Point2I, DivisionByZeroInPlace)
{
    const Point2I lhs(12, -42);
    const Point2I rhsXZero(0, 9);
    const Point2I rhsYZero(11, 0);
    const Point2I rhsBothZero(0, 0);

    EXPECT_THROW({ Point2I specimen = lhs; specimen /= rhsXZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2I specimen = lhs; specimen /= rhsYZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2I specimen = lhs; specimen /= rhsBothZero; }, Ag::DivisionByZeroException);
}

GTEST_TEST(Point2I, Minimum)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs.min(rhs);

    EXPECT_EQ(result.getX(), std::min(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.getY(), std::min(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2I, Maximum)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    Point2I result = lhs.max(rhs);

    EXPECT_EQ(result.getX(), std::max(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.getY(), std::max(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2I, MinimumAndMaximum)
{
    const Point2I lhs(12, -42);
    const Point2I rhs(32, 9);

    auto result = lhs.minmax(rhs);

    EXPECT_EQ(result.first.getX(), std::min(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.first.getY(), std::min(lhs.getY(), rhs.getY()));
    EXPECT_EQ(result.second.getX(), std::max(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.second.getY(), std::max(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2I, Clamp)
{
    const Point2I lower(12, -42);
    const Point2I upper(32, 9);

    const Point2I noChange(24, 0);
    const Point2I floorX(11, 5);
    const Point2I floorY(20, -44);
    const Point2I floorBoth(11, -44);
    const Point2I ceilX(34, 7);
    const Point2I ceilY(16, 12);
    const Point2I ceilBoth(34, 12);

    Point2I result = noChange.clamp(lower, upper);

    EXPECT_EQ(result.getX(), std::clamp(noChange.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(noChange.getY(), lower.getY(), upper.getY()));

    result = floorX.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(floorX.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(floorX.getY(), lower.getY(), upper.getY()));

    result = floorY.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(floorY.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(floorY.getY(), lower.getY(), upper.getY()));

    result = floorBoth.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(floorBoth.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(floorBoth.getY(), lower.getY(), upper.getY()));

    result = ceilX.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(ceilX.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(ceilX.getY(), lower.getY(), upper.getY()));

    result = ceilY.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(ceilY.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(ceilY.getY(), lower.getY(), upper.getY()));

    result = ceilBoth.clamp(lower, upper);
    EXPECT_EQ(result.getX(), std::clamp(ceilBoth.getX(), lower.getX(), upper.getX()));
    EXPECT_EQ(result.getY(), std::clamp(ceilBoth.getY(), lower.getY(), upper.getY()));
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

