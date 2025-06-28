//! @file Test_Line2D.cpp
//! @brief The definition of unit tests for the Line2D class.
//! @author Nick Arkell
//! @copyright (c) 2021-2024 Nick Arkell : Software Engineer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/GTest_Core.hpp"

#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/NumericDomain.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Line2D, DefaultConstruct)
{
    Line2D specimen;

    EXPECT_TRUE(NumericDomain::UnsignedScalar.isNearEqual(1.0,
                                                          specimen.getDelta().magnitude()));
}

GTEST_TEST(Line2D, InitConstruct)
{
    Line2D specimen(-1, 11, -2, 2);
    double value = 1.0 / std::sqrt(2.0);

    EXPECT_EQ(specimen.getOrigin().getX(), -1);
    EXPECT_EQ(specimen.getOrigin().getY(), 11);
    EXPECT_EQ(specimen.getDelta().getX(), -value);
    EXPECT_EQ(specimen.getDelta().getY(), value);
    EXPECT_EQ(specimen.asVector()[0], -1);
    EXPECT_EQ(specimen.asVector()[1], 11);
    EXPECT_EQ(specimen.asVector()[2], -value);
    EXPECT_EQ(specimen.asVector()[3], value);
}

GTEST_TEST(Line2D, GetPoint)
{
    Line2D specimen(-1, 11, -2, 2);

    EXPECT_EQ(specimen.getPoint(0.0), specimen.getOrigin());
    Point2D pos = specimen.getPoint(1.0);
    double value = 1.0 / std::sqrt(2.0);

    EXPECT_NEAR(pos.getX(), specimen.getOrigin().getX() - value, 1e-8);
    EXPECT_NEAR(pos.getY(), specimen.getOrigin().getY() + value, 1e-8);
}

GTEST_TEST(Line2D, IsParallel)
{
    Line2D specimen(-1, 11, -2, 2);

    EXPECT_TRUE(specimen.isParallel(Line2D(10, -2, -4, 4)));

    // Check it's still parallel when travelling in the opposite direction.
    EXPECT_TRUE(specimen.isParallel(Line2D(11, 6, 4, -4)));

    // Check it's not parallel when travelling in a different direction.
    EXPECT_FALSE(specimen.isParallel(Line2D(-42, 69, -4, 3)));
}

GTEST_TEST(Line2D, IsPerpendicular)
{
    Line2D specimen(-1, 11, -2, 2);

    // Ensure it's not perpendicular when parallel.
    EXPECT_FALSE(specimen.isPerpendicular(Line2D(10, -2, -4, 4)));

    // Check both perpendicular forms are accepted.
    EXPECT_TRUE(specimen.isPerpendicular(Line2D(10, -2, 4, 4)));
    EXPECT_TRUE(specimen.isPerpendicular(Line2D(10, -2, -4, -4)));

    // Check it's not perpendicular when travelling in a different direction.
    EXPECT_FALSE(specimen.isPerpendicular(Line2D(-42, 69, -4, 3)));
}

GTEST_TEST(Line2D, IsColinear)
{
    Line2D specimen(-5, -5, 10, 10);
    NumericDomain domain(-50, 50);

    // The line should be co-linear with itself.
    EXPECT_TRUE(specimen.isColinear(domain, specimen));

    // The line should be co-linear with the same line travelling in the
    // opposite direction.
    EXPECT_TRUE(specimen.isColinear(domain, Line2D(5, 5, -10, -10)));

    // A line further along the travel direction or before should be co-linear.
    EXPECT_TRUE(specimen.isColinear(domain, Line2D(15, 15, 10, 10)));
    EXPECT_TRUE(specimen.isColinear(domain, Line2D(-20, -20, 10, 10)));

    // A parallel line which doesn't overlap should not be co-linear
    EXPECT_FALSE(specimen.isColinear(domain, Line2D(-5, -10, 10, 10)));

    // A non-parallel lines should not be co-linear.
    EXPECT_FALSE(specimen.isColinear(domain, Line2D(-5, -5, 10, 0)));
}

GTEST_TEST(Line2D, GetDistanceToPoint)
{
    const double recipRoot2 = 1.0 / std::sqrt(2.0);
    Line2D specimen(0, 0, 2, 2);
    double param = 0.0;

    EXPECT_NEAR(specimen.getDistanceToPoint(Point2D(0, 1), param), 0.5, 1e-8);
    EXPECT_NEAR(param, recipRoot2, 1e-8);

    EXPECT_NEAR(specimen.getDistanceToPoint(Point2D(1, 0), param), 0.5, 1e-8);
    EXPECT_NEAR(param, recipRoot2, 1e-8);
}

GTEST_TEST(Line2D, TryCalculateIntersectionParam)
{
    Line2D diagonal(0, 0, 2, 2);
    Line2D reverse(1, 0, -12, 12);
    double t = 0;
    double u = 0;

    EXPECT_TRUE(diagonal.tryCalculateIntersectionParam(reverse, t, u));
    EXPECT_FALSE(diagonal.tryCalculateIntersectionParam(diagonal, t, u));
    EXPECT_FALSE(diagonal.tryCalculateIntersectionParam(Line2D(10, 0, 2, 2), t, u));
    EXPECT_FALSE(diagonal.tryCalculateIntersectionParam(Line2D(0, 0, -2, -2), t, u));

    EXPECT_TRUE(Line2D(0, 0, 1, 0).tryCalculateIntersectionParam(Line2D(0, 0, 0, 1), t, u));
    EXPECT_FALSE(Line2D(0, 0, 1, 0).tryCalculateIntersectionParam(Line2D(0, 0, 1, 0), t, u));
    EXPECT_NEAR(t, 0.0, 1e-8);
    EXPECT_NEAR(u, 0.0, 1e-8);
}

GTEST_TEST(Line2D, TryCalculateIntersection)
{
    Point2D vertices[] = {
        { 2, 1 },
        { 57, 56 },
        { 25, 2 },
        { -38, 65 }
    };

    Point2D crossAt(14, 13);

    Line2D firstSecond = Line2D::fromTwoPoints(vertices[0], vertices[1]);
    Line2D thirdFourth = Line2D::fromTwoPoints(vertices[2], vertices[3]);

    Point2D intersectionPt;

    EXPECT_TRUE(firstSecond.tryCalculateIntersection(thirdFourth, intersectionPt));

    EXPECT_DOUBLE_EQ(intersectionPt.getX(), crossAt.getX());
    EXPECT_DOUBLE_EQ(intersectionPt.getY(), crossAt.getY());
}

} // Anonymous namespace.

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

