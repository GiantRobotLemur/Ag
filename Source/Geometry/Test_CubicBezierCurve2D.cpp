//! @file Geometry/Test_CubicBezierCurve2D.cpp
//! @brief The definition of unit tests for the CubicBezierCurve2D class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Geometry/CubicBezierCurve2D.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CubicBezierCurve2D, Start)
{
    CubicBezierCurve2D specimen(Point2D(5, 2), Point2D(-1, 42), Point2D(12, 36), Point2D(-5, 7));

    EXPECT_EQ(specimen.getStart(), Point2D(5, 2));

    specimen.setStart(Point2D(9, 7));

    EXPECT_EQ(specimen.getStart(), Point2D(9, 7));
}

GTEST_TEST(CubicBezierCurve2D, End)
{
    CubicBezierCurve2D specimen(Point2D(5, 2), Point2D(-1, 42), Point2D(12, 36), Point2D(-5, 7));
    EXPECT_EQ(specimen.getEnd(), Point2D(-5, 7));

    specimen.setEnd(Point2D(9, 7));
    EXPECT_EQ(specimen.getEnd(), Point2D(9, 7));
}

GTEST_TEST(CubicBezierCurve2D, GetParameterDistance)
{
    constexpr double Epsilon = 1e-8;
    const CubicBezierCurve2D specimen(Point2D(0, 0), Point2D(2.5, 7.5), Point2D(7.5, 7.5), Point2D(10, 0));
    const Point2D upperTarget(5, 15);
    const Point2D lowerTarget(5, 0);
    const Point2D beforeStart(-5, -5);
    const Point2D afterEnd(15, -15);

    // Test a point above the line.
    double param = specimen.getParameter(upperTarget);
    EXPECT_NEAR(param, 0.5, Epsilon);

    double distance = specimen.getDistanceToPoint(upperTarget, param);
    EXPECT_GT(distance, 0.0);
    EXPECT_NEAR(param, 0.5, Epsilon);

    // Test a point before the start of the line
    param = specimen.getParameter(beforeStart);
    EXPECT_NEAR(param, 0.0, Epsilon);

    distance = specimen.getDistanceToPoint(beforeStart, param);
    EXPECT_NEAR(distance, specimen.getStart().distance(beforeStart), Epsilon);
    EXPECT_NEAR(param, 0.0, Epsilon);

    // Test a point after the end of the line.
    param = specimen.getParameter(afterEnd);
    EXPECT_NEAR(param, 1.0, Epsilon);

    distance = specimen.getDistanceToPoint(afterEnd, param);
    EXPECT_NEAR(distance, specimen.getEnd().distance(afterEnd), Epsilon);
    EXPECT_NEAR(param, 1.0, Epsilon);
}

GTEST_TEST(CubicBezierCurve2D, ToPolyline)
{
    constexpr double Tolerance = 1.0;
    const CubicBezierCurve2D specimen(Point2D(0, 0), Point2D(2.5, 7.5), Point2D(7.5, 7.5), Point2D(10, 0));

    auto points = specimen.toPolyline(Tolerance);

    ASSERT_GT(points.size(), 2u);
    EXPECT_DOUBLE_EQ(specimen.getStart().getX(), points.front().getX());
    EXPECT_DOUBLE_EQ(specimen.getStart().getY(), points.front().getY());
    EXPECT_DOUBLE_EQ(specimen.getEnd().getX(), points.back().getX());
    EXPECT_DOUBLE_EQ(specimen.getEnd().getY(), points.back().getY());

    for (const Point2D &point : points)
    {
        double param = specimen.getParameter(point);
        Point2D actualPoint = specimen.getPoint(param);

        double approxDistance = actualPoint.distance(point);

        EXPECT_LE(approxDistance, Tolerance);
    }
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

