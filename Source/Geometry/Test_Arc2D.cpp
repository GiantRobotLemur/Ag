//! @file Geometry/Test_Arc2D.cpp
//! @brief The definition of unit tests for the Arc2D class.
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

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

