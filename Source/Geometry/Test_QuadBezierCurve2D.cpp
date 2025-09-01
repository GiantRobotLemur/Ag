//! @file Geometry/Test_QuadBezierCurve2D.cpp
//! @brief The definition of unit tests for the QuadBezierCurve2D class.
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

#include "Ag/Geometry/QuadBezierCurve2D.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(QuadBezierCurve2D, Start)
{
    QuadBezierCurve2D specimen(Point2D(5, 2), Point2D(-1, 42), Point2D(-5, 7));

    EXPECT_EQ(specimen.getStart(), Point2D(5, 2));

    specimen.setStart(Point2D(9, 7));

    EXPECT_EQ(specimen.getStart(), Point2D(9, 7));
}

GTEST_TEST(QuadBezierCurve2D, End)
{
    QuadBezierCurve2D specimen(Point2D(5, 2), Point2D(-1, 42), Point2D(-5, 7));
    EXPECT_EQ(specimen.getEnd(), Point2D(-5, 7));

    specimen.setEnd(Point2D(9, 7));
    EXPECT_EQ(specimen.getEnd(), Point2D(9, 7));
}

GTEST_TEST(QuadBezierCurve2D, GetParameterDistance)
{
    constexpr double Epsilon = 1e-8;
    const QuadBezierCurve2D specimen(Point2D(0, 0), Point2D(0, 10), Point2D(10, 10));
    const Point2D upperTarget(0, 10);
    const Point2D lowerTarget(5, 5);
    const Point2D beforeStart(-5, -5);
    const Point2D afterEnd(15, 15);

    // Test a point above the line.
    double param = specimen.getParameter(upperTarget);
    EXPECT_NEAR(param, 0.5, Epsilon);

    double distance = specimen.getDistanceToPoint(upperTarget, param);
    EXPECT_GT(distance, 0.0);
    EXPECT_NEAR(param, 0.5, Epsilon);

    // Test a point below the line.
    param = specimen.getParameter(lowerTarget);
    EXPECT_NEAR(param, 0.5, Epsilon);

    distance = specimen.getDistanceToPoint(lowerTarget, param);
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

GTEST_TEST(QuadBezierCurve2D, ToPolyline)
{
    constexpr double Tolerance = 1.5;
    const QuadBezierCurve2D specimen(Point2D(0, 0), Point2D(0, 10), Point2D(10, 10));

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

