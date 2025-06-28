//! @file Geometry/Test_Point2D.cpp
//! @brief The definition of unit tests for the Point2D class.
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

#include "Ag/Geometry/Point2D.hpp"
#include "Ag/Geometry/Size2D.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Point2D, DefaultConstruct)
{
    Point2D specimen;

    EXPECT_EQ(specimen.getX(), 0.0);
    EXPECT_EQ(specimen.getY(), 0.0);
    EXPECT_EQ(specimen.getXRef(), 0.0);
    EXPECT_EQ(specimen.getYRef(), 0.0);

    const Point2D &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), 0.0);
    EXPECT_EQ(specRef.getYRef(), 0.0);
}

GTEST_TEST(Point2D, ComponentConstruct)
{
    constexpr double SampleX = 12.345;
    constexpr double SampleY = -42.25;
    Point2D specimen(SampleX, SampleY);

    EXPECT_EQ(specimen.getX(), SampleX);
    EXPECT_EQ(specimen.getY(), SampleY);
    EXPECT_EQ(specimen.getXRef(), SampleX);
    EXPECT_EQ(specimen.getYRef(), SampleY);

    const Point2D &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), SampleX);
    EXPECT_EQ(specRef.getYRef(), SampleY);
}

GTEST_TEST(Point2D, SizeConstruct)
{
    const Size2D inputSize(32.422, 9.11);
    Point2D specimen(inputSize);

    EXPECT_EQ(specimen.getX(), inputSize.getWidth());
    EXPECT_EQ(specimen.getY(), inputSize.getHeight());
    EXPECT_EQ(specimen.getXRef(), inputSize.getWidth());
    EXPECT_EQ(specimen.getYRef(), inputSize.getHeight());

    const Point2D &specRef = specimen;

    EXPECT_EQ(specRef.getXRef(), inputSize.getWidth());
    EXPECT_EQ(specRef.getYRef(), inputSize.getHeight());
}

GTEST_TEST(Point2D, Addition)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs + rhs;

    EXPECT_EQ(result.getX(), lhs.getX() + rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() + rhs.getY());
}

GTEST_TEST(Point2D, Subtraction)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs - rhs;

    EXPECT_EQ(result.getX(), lhs.getX() - rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() - rhs.getY());
}

GTEST_TEST(Point2D, Negation)
{
    const Point2D specimen(12.345, -42.25);

    Point2D result = -specimen;

    EXPECT_EQ(result.getX(), -specimen.getX());
    EXPECT_EQ(result.getY(), -specimen.getY());
}

GTEST_TEST(Point2D, Multiplication)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs * rhs;

    EXPECT_EQ(result.getX(), lhs.getX() * rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() * rhs.getY());
}

GTEST_TEST(Point2D, Division)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs / rhs;

    EXPECT_EQ(result.getX(), lhs.getX() / rhs.getX());
    EXPECT_EQ(result.getY(), lhs.getY() / rhs.getY());
}

GTEST_TEST(Point2D, DivisionByZero)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhsXZero(0.0, 9.6);
    const Point2D rhsYZero(4.3, 0.0);
    const Point2D rhsBothZero(0.0, 0.0);

    EXPECT_THROW({ Point2D result = lhs / rhsXZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2D result = lhs / rhsYZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2D result = lhs / rhsBothZero; }, Ag::DivisionByZeroException);
}

GTEST_TEST(Point2D, AdditionInPlace)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);
    Point2D specimen = lhs;

    specimen += rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() + rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() + rhs.getY());
}

GTEST_TEST(Point2D, SubtractionInPlace)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);
    Point2D specimen = lhs;

    specimen -= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() - rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() - rhs.getY());
}

GTEST_TEST(Point2D, MultiplicationInPlace)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);
    Point2D specimen = lhs;

    specimen *= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() * rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() * rhs.getY());
}

GTEST_TEST(Point2D, DivisionInPlace)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);
    Point2D specimen = lhs;

    specimen /= rhs;

    EXPECT_EQ(specimen.getX(), lhs.getX() / rhs.getX());
    EXPECT_EQ(specimen.getY(), lhs.getY() / rhs.getY());
}

GTEST_TEST(Point2D, DivisionByZeroInPlace)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhsXZero(0.0, 9.8);
    const Point2D rhsYZero(3.14159, 0.0);
    const Point2D rhsBothZero(0.0, 0.0);

    EXPECT_THROW({ Point2D specimen = lhs; specimen /= rhsXZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2D specimen = lhs; specimen /= rhsYZero; }, Ag::DivisionByZeroException);
    EXPECT_THROW({ Point2D specimen = lhs; specimen /= rhsBothZero; }, Ag::DivisionByZeroException);
}

GTEST_TEST(Point2D, Minimum)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs.min(rhs);

    EXPECT_EQ(result.getX(), std::min(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.getY(), std::min(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2D, Maximum)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    Point2D result = lhs.max(rhs);

    EXPECT_EQ(result.getX(), std::max(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.getY(), std::max(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2D, MinimumAndMaximum)
{
    const Point2D lhs(12.345, -42.25);
    const Point2D rhs(32.369, 9.125);

    auto result = lhs.minmax(rhs);

    EXPECT_EQ(result.first.getX(), std::min(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.first.getY(), std::min(lhs.getY(), rhs.getY()));
    EXPECT_EQ(result.second.getX(), std::max(lhs.getX(), rhs.getX()));
    EXPECT_EQ(result.second.getY(), std::max(lhs.getY(), rhs.getY()));
}

GTEST_TEST(Point2D, Clamp)
{
    const Point2D lower(12.345, -42.25);
    const Point2D upper(32.369, 9.125);

    const Point2D noChange(24.772, 0.0);
    const Point2D floorX(11.5, 5.43);
    const Point2D floorY(20.9, -44.879);
    const Point2D floorBoth(12.25, -44.56);
    const Point2D ceilX(34.9, 7.25);
    const Point2D ceilY(16.82, 12.4);
    const Point2D ceilBoth(34.117, 12.36);

    Point2D result = noChange.clamp(lower, upper);

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

GTEST_TEST(Point2D, CollectionAlignment)
{
    constexpr uintptr_t AlignmentMask = 0x1F;

    // Try allocating memory with a vector.
    Point2DCollection specimen1;
    specimen1.emplace_back(42, -69);

    // Verify the alignment of the address.
    EXPECT_EQ(reinterpret_cast<uintptr_t>(specimen1.data()) & AlignmentMask, 0u);

    // Try again, to ensure it wasn't a fluke.
    Point2DCollection specimen2;
    specimen1.emplace_back(-37, 96.5);

    // Verify the alignment of the address.
    EXPECT_EQ(reinterpret_cast<uintptr_t>(specimen2.data()) & AlignmentMask, 0u);
}

GTEST_TEST(Point2D, RotateCW)
{
    Point2D specimen(1, 2);
    const Angle quarterTurn = Angle::fromDegrees(90);
    const Angle halfTurn = Angle::fromDegrees(180);
    const Angle threeQuarterTurn = Angle::fromDegrees(270);

    // Verify identity.
    Point2D result = specimen.rotateCW(0.0);

    EXPECT_DOUBLE_EQ(specimen.getX(), result.getX());
    EXPECT_DOUBLE_EQ(specimen.getY(), result.getY());

    // Rotate by 90 degrees.
    result = specimen.rotateCW(quarterTurn.toRadians());

    EXPECT_DOUBLE_EQ(-2.0, result.getX());
    EXPECT_DOUBLE_EQ(1.0, result.getY());

    // Rotate by 180 degrees.
    result = specimen.rotateCW(halfTurn.toRadians());

    EXPECT_DOUBLE_EQ(-1.0, result.getX());
    EXPECT_DOUBLE_EQ(-2.0, result.getY());

    // Rotate by 270 degrees.
    result = specimen.rotateCW(threeQuarterTurn.toRadians());

    EXPECT_DOUBLE_EQ(2.0, result.getX());
    EXPECT_DOUBLE_EQ(-1.0, result.getY());
}

GTEST_TEST(Point2D, RotateCCW)
{
    Point2D specimen(1, 2);
    const Angle quarterTurn = Angle::fromDegrees(90);
    const Angle halfTurn = Angle::fromDegrees(180);
    const Angle threeQuarterTurn = Angle::fromDegrees(270);

    // Verify identity.
    Point2D result = specimen.rotateCW(0.0);

    EXPECT_DOUBLE_EQ(specimen.getX(), result.getX());
    EXPECT_DOUBLE_EQ(specimen.getY(), result.getY());

    // Rotate by 90 degrees.
    result = specimen.rotateCCW(quarterTurn.toRadians());

    EXPECT_DOUBLE_EQ(2.0, result.getX());
    EXPECT_DOUBLE_EQ(-1.0, result.getY());

    // Rotate by 180 degrees.
    result = specimen.rotateCCW(halfTurn.toRadians());

    EXPECT_DOUBLE_EQ(-1.0, result.getX());
    EXPECT_DOUBLE_EQ(-2.0, result.getY());

    // Rotate by 270 degrees.
    result = specimen.rotateCCW(threeQuarterTurn.toRadians());

    EXPECT_DOUBLE_EQ(-2.0, result.getX());
    EXPECT_DOUBLE_EQ(1.0, result.getY());
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

