//! @file Test_LineEq2D.cpp
//! @brief The definition of unit tests for the LineEq2D class.
//! @author Nick Arkell
//! @copyright (c) 2021-2024 Nick Arkell : Software Engineer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/GTest_Core.hpp"

#include "Ag/Geometry/Angle.hpp"
#include "Ag/Geometry/LineEq2D.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(LineEq2D, DefaultConstruct)
{
    LineEq2D specimen;

    EXPECT_NEAR(0.0, specimen.getDistanceToPoint(Point2D(0, 0)), 1e-8);
}

GTEST_TEST(LineEq2D, IsParallel)
{
    LineEq2D specimen(Point2D(-1, 11), Point2D(-3, 13));

    EXPECT_TRUE(specimen.isParallel(LineEq2D(Point2D(10, -2), Point2D(6, 2))));

    // Check it's still parallel when travelling in the opposite direction.
    EXPECT_TRUE(specimen.isParallel(LineEq2D(Point2D(11, 6), Point2D(15, 2))));

    // Check it's not parallel when travelling in a different direction.
    EXPECT_FALSE(specimen.isParallel(LineEq2D(Point2D(-42, 69), Point2D(-46, 72))));
}

GTEST_TEST(LineEq2D, IsPerpendicular)
{
    LineEq2D specimen(Point2D(-1, 11), Point2D(-3, 13));

    // Ensure it's not perpendicular when parallel.
    EXPECT_FALSE(specimen.isPerpendicular(LineEq2D(Point2D(10, -2), Point2D(6, 2))));

    // Check both perpendicular forms are accepted.
    EXPECT_TRUE(specimen.isPerpendicular(LineEq2D(Point2D(10, -2), Point2D(14, 2))));
    EXPECT_TRUE(specimen.isPerpendicular(LineEq2D(Point2D(10, -2), Point2D(6, -6))));

    // Check it's not perpendicular when travelling in a different direction.
    EXPECT_FALSE(specimen.isPerpendicular(LineEq2D(Point2D(-42, 69), Point2D(-46, 72))));
}

GTEST_TEST(LineEq2D, GetDistanceToPoint)
{
    const double recipRoot2 = 1.0 / std::sqrt(2.0);
    LineEq2D specimen(Point2D(0, 0), Point2D(2, 2));

    EXPECT_NEAR(specimen.getDistanceToPoint(Point2D(0, 1)), recipRoot2, 1e-8);

    EXPECT_NEAR(specimen.getDistanceToPoint(Point2D(1, 0)), -recipRoot2, 1e-8);
}

GTEST_TEST(LineEq2D, IsHorizontal)
{
    EXPECT_TRUE(LineEq2D(Point2D(0, 0), Point2D(1, 0)).isHorizontal());
    EXPECT_TRUE(LineEq2D(Point2D(0, 0), Point2D(-1, 0)).isHorizontal());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(0, 1)).isHorizontal());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(0, -1)).isHorizontal());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(1, 1)).isHorizontal());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(-1, -1)).isHorizontal());

    EXPECT_TRUE(LineEq2D(Point2D(10, 10), Point2D(20, 10)).isHorizontal());
    EXPECT_TRUE(LineEq2D(Point2D(10, 10), Point2D(-10, 10)).isHorizontal());
    EXPECT_TRUE(LineEq2D(Point2D(10, -10), Point2D(20, -10)).isHorizontal());
    EXPECT_TRUE(LineEq2D(Point2D(10, -10), Point2D(-10, -10)).isHorizontal());

    EXPECT_FALSE(LineEq2D(Point2D(-10, 20), Point2D(-11, -20)).isHorizontal());
}


GTEST_TEST(LineEq2D, IsVertical)
{
    EXPECT_TRUE(LineEq2D(Point2D(0, 0), Point2D(0, 1)).isVertical());
    EXPECT_TRUE(LineEq2D(Point2D(0, 0), Point2D(0, -1)).isVertical());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(1, 0)).isVertical());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(-1, 0)).isVertical());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(1, 1)).isVertical());
    EXPECT_FALSE(LineEq2D(Point2D(0, 0), Point2D(-1, -1)).isVertical());

    EXPECT_TRUE(LineEq2D(Point2D(10, 10), Point2D(10, 20)).isVertical());
    EXPECT_TRUE(LineEq2D(Point2D(10, 10), Point2D(10, -20)).isVertical());
    EXPECT_TRUE(LineEq2D(Point2D(-10, 10), Point2D(-10, 20)).isVertical());
    EXPECT_TRUE(LineEq2D(Point2D(-10, 10), Point2D(-10, -20)).isVertical());

    EXPECT_FALSE(LineEq2D(Point2D(10, 10), Point2D(20, -20)).isVertical());
}


GTEST_TEST(LineEq2D, AngleTo)
{
    // Create a 45-degree line.
    LineEq2D specimen(Point2D(0, 0), Point2D(1, 1));

    LineEq2D vertical(Point2D(0, 0), Point2D(0, 1));
    LineEq2D horizontal(Point2D(0, 0), Point2D(1, 0));

    const double tol = Angle::Domain.getTolerance();

    double angle = vertical.getAngleTo(specimen);
    EXPECT_NEAR(angle, Angle::Pi_4, tol);

    angle = horizontal.getAngleTo(specimen);
    EXPECT_NEAR(angle, -Angle::Pi_4, tol);

    // Try a line offset from the origin.
    specimen = LineEq2D(Point2D(1, -1), Point2D(2, -2));

    angle = vertical.getAngleTo(specimen);
    EXPECT_NEAR(angle, -Angle::Pi_4, tol);

    angle = horizontal.getAngleTo(specimen);
    EXPECT_NEAR(angle, Angle::Pi_4, tol);
}


GTEST_TEST(LineEq2D, TryCalculateIntersection)
{
    Point2D vertices[] = {
        { 2, 1 },
        { 57, 56 },
        { 25, 2 },
        { -38, 65 }
    };

    Point2D crossAt(14, 13);

    LineEq2D firstSecond(vertices[0], vertices[1]);
    LineEq2D thirdFourth(vertices[2], vertices[3]);

    Point2D intersectionPt;

    EXPECT_TRUE(firstSecond.tryCalculateIntersection(thirdFourth, intersectionPt));

    EXPECT_DOUBLE_EQ(intersectionPt.getX(), crossAt.getX());
    EXPECT_DOUBLE_EQ(intersectionPt.getY(), crossAt.getY());
}

} // Anonymous namespace.

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

