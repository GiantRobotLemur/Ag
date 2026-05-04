//! @file Geometry/Test_Arc2D.cpp
//! @brief The definition of unit tests for the Arc2D class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Geometry/Arc2D.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Arc2D, ConstructCircle)
{
    Point2D points[] = {
        Point2D(0, 5),
        Point2D(10, 5),
        Point2D(5, 5)
    };

    Arc2D specimen(points[0], points[1], points[2], 0, true, false);

    EXPECT_EQ(specimen.getStart(), points[0]);
    EXPECT_EQ(specimen.getEnd(), points[1]);
    EXPECT_EQ(specimen.getMajorRadius(), points[2].getY());
    EXPECT_EQ(specimen.getMinorRadius(), points[2].getX());
    EXPECT_EQ(specimen.getRotationAngle(), 0);
    EXPECT_TRUE(specimen.isLargeSweep());
    EXPECT_FALSE(specimen.isClockwiseSweep());

    Arc2D::Parameters params(specimen);

    Point2D centre = params.getCentre();
    Point2D radiusX = params.getMinorAxisPoint();
    Point2D radiusY = params.getMajorAxisPoint();

    EXPECT_DOUBLE_EQ(centre.getX(), 5);
    EXPECT_DOUBLE_EQ(centre.getY(), 5);
    EXPECT_DOUBLE_EQ(radiusX.getX(), 10);
    EXPECT_DOUBLE_EQ(radiusX.getY(), 5);
    EXPECT_DOUBLE_EQ(radiusY.getX(), 5);
    EXPECT_DOUBLE_EQ(radiusY.getY(), 10);
}

GTEST_TEST(Arc2D, Construction)
{
    Point2D points[] = {
        Point2D(0, 10),
        Point2D(10, 0),
        Point2D(10, 10)
    };

    Rect2D range(points, std::size(points));
    NumericDomain domain = range.createDomain();
    Arc2D specimen(points[0], points[1], points[2], 0, true, false);

    EXPECT_EQ(specimen.getStart(), points[0]);
    EXPECT_EQ(specimen.getEnd(), points[1]);
    EXPECT_EQ(specimen.getMajorRadius(), points[2].getY());
    EXPECT_EQ(specimen.getMinorRadius(), points[2].getX());
    EXPECT_EQ(specimen.getRotationAngle(), 0);
    EXPECT_TRUE(specimen.isLargeSweep());
    EXPECT_FALSE(specimen.isClockwiseSweep());

    Arc2D::Parameters params(specimen);

    Point2D centre = params.getCentre();
    Point2D radiusX = params.getMinorAxisPoint();
    Point2D radiusY = params.getMajorAxisPoint();

    EXPECT_NEAR(centre.getX(), 0.0, domain.getTolerance());
    EXPECT_NEAR(centre.getY(), 0.0, domain.getTolerance());
    EXPECT_NEAR(radiusX.getX(), 10.0, domain.getTolerance());
    EXPECT_NEAR(radiusX.getY(), 0.0, domain.getTolerance());
    EXPECT_NEAR(radiusY.getX(), 0.0, domain.getTolerance());
    EXPECT_NEAR(radiusY.getY(), 10.0, domain.getTolerance());
}

GTEST_TEST(Arc2D, ConstructInvalid)
{
    EXPECT_THROW({ Arc2D segment(Point2D(), Point2D(),
                                 Point2D(40, 20), 0, true, false); },
                 ArgumentException);

    EXPECT_THROW({ Arc2D segment(Point2D(), Point2D(10, 15),
                                 Point2D(1, 2), 0, true, false); },
                 ArgumentException);
}

GTEST_TEST(Arc2D, ConstructTransformable)
{
    Point2D points[] = {
        Point2D(0, 10),
        Point2D(10, 0),
        Point2D(0, 0),
        Point2D(10, 10)
    };

    Rect2D range(points, std::size(points));
    NumericDomain domain = range.createDomain();
    Arc2D guide(points[0], points[1], points[3], 0, false, true);
    Arc2D::Parameters guideParams(guide);

    // Note: X radius goes up and Y radius across to set a non-zero ellipse angle.
    Arc2D specimen(points[0], points[1], guideParams.getCentre(),
                   guideParams.getMinorAxisPoint(),
                   guideParams.getMajorAxisPoint(),
                   false, true);

    Arc2D::Parameters specimenParams(specimen);

    EXPECT_EQ(specimen.getStart(), points[0]);
    EXPECT_EQ(specimen.getEnd(), points[1]);
    EXPECT_DOUBLE_EQ(specimen.getMajorRadius(), points[3].getY());
    EXPECT_DOUBLE_EQ(specimen.getMinorRadius(), points[3].getX());
    EXPECT_DOUBLE_EQ(specimen.getRotationAngle(), 0);
    EXPECT_FALSE(specimen.isLargeSweep());
    EXPECT_TRUE(specimen.isClockwiseSweep());

    Point2D centre = specimenParams.getCentre();
    Point2D radiusX = specimenParams.getMinorAxisPoint();
    Point2D radiusY = specimenParams.getMajorAxisPoint();

    EXPECT_NEAR(centre.getX(), points[2].getX(), domain.getTolerance());
    EXPECT_NEAR(centre.getY(), points[2].getY(), domain.getTolerance());
    EXPECT_NEAR(radiusX.getX(), points[1].getX(), domain.getTolerance());
    EXPECT_NEAR(radiusX.getY(), points[1].getY(), domain.getTolerance());
    EXPECT_NEAR(radiusY.getX(), points[0].getX(), domain.getTolerance());
    EXPECT_NEAR(radiusY.getY(), points[0].getY(), domain.getTolerance());
}

GTEST_TEST(Arc2D, GetDirection)
{
    constexpr double Tolerance = 1e-7;

    // A quarter unit circle from (10, 0) to (0, 10), short sweep.
    Arc2D specimen(Point2D(10, 0), Point2D(0, 10), Point2D(10, 10),
                   0, false, false);
    Arc2D::Parameters params(specimen);
    Point2D centre = params.getCentre();

    // For a circular arc the tangent vector must be perpendicular to the
    // radius at every point along the arc, and its magnitude is constant
    // (|R * angleDelta|).
    for (double t : { 0.0, 0.25, 0.5, 0.75, 1.0 })
    {
        Point2D point = params.getPoint(t);
        Point2D radius = point - centre;
        Point2D dir = params.getDirection(t);

        // Perpendicularity: r . d == 0
        double dot = radius.dotProduct(dir);
        EXPECT_NEAR(dot, 0.0, Tolerance);

        // Constant tangent magnitude across the arc.
        EXPECT_NEAR(dir.magnitude(), specimen.getDirection(t).magnitude(),
                    Tolerance);
    }

    // Cross-check the analytical derivative against a central numerical
    // difference of getPoint().
    constexpr double H = 1e-6;
    constexpr double NumericTolerance = 1e-4;
    for (double t : { 0.1, 0.25, 0.5, 0.75, 0.9 })
    {
        Point2D numeric = (params.getPoint(t + H) -
                           params.getPoint(t - H)) * (1.0 / (2.0 * H));
        Point2D analytic = params.getDirection(t);

        EXPECT_NEAR(analytic.getX(), numeric.getX(), NumericTolerance);
        EXPECT_NEAR(analytic.getY(), numeric.getY(), NumericTolerance);

        // The Arc2D facade should delegate to Parameters and produce the
        // same result.
        Point2D viaArc = specimen.getDirection(t);
        EXPECT_NEAR(analytic.getX(), viaArc.getX(), Tolerance);
        EXPECT_NEAR(analytic.getY(), viaArc.getY(), Tolerance);
    }
}

GTEST_TEST(Arc2D, GetDirectionEllipse)
{
    constexpr double NumericTolerance = 1e-4;
    constexpr double H = 1e-6;

    // A non-circular elliptical arc (axes 10 x 5, centred at origin). The
    // closed-form derivative must match the numerical derivative of getPoint().
    Arc2D specimen(Point2D(10, 0), Point2D(0, 5), Point2D(10, 5),
                   0.0, false, false);
    Arc2D::Parameters params(specimen);

    for (double t : { 0.1, 0.3, 0.5, 0.7, 0.9 })
    {
        Point2D numeric = (params.getPoint(t + H) -
                           params.getPoint(t - H)) * (1.0 / (2.0 * H));
        Point2D analytic = params.getDirection(t);

        EXPECT_NEAR(analytic.getX(), numeric.getX(), NumericTolerance);
        EXPECT_NEAR(analytic.getY(), numeric.getY(), NumericTolerance);
    }
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

