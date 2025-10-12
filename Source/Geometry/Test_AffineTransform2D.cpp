//! @file Geometry/Test_AffineTransform2D.cpp
//! @brief The definition of unit tests for the AffineTransform2D class.
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

#include "Ag/Geometry/AffineTransform2D.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Geom {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(AffineTransform2D, DefaultConstruct)
{
    AffineTransform2D specimen;

    specimen.isIdentity();
}

GTEST_TEST(AffineTransform2D, InitaliseConstruct)
{
    double input[] = { 2.0, 1.1, -3.0, 5.0, 12, 69, 42, 0, 91 };
    AffineTransform2D specimen(input);

    EXPECT_FALSE(specimen.isIdentity());

    // Test overwriting the matrix with identity values.
    specimen.makeIdentity();
    EXPECT_TRUE(specimen.isIdentity());
}

GTEST_TEST(AffineTransform2D, MultiplyPoint2D)
{
    AffineTransform2D specimen;
    specimen.makeRotation(Angle::Pi_2);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Rotated = specimen * p1;
    Point2D p2Rotated = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Rotated.getX(), -1.0);
    EXPECT_DOUBLE_EQ(p1Rotated.getY(), 2.0);

    EXPECT_DOUBLE_EQ(p2Rotated.getX(), -4.0);
    EXPECT_DOUBLE_EQ(p2Rotated.getY(), -1.0);

    AffineTransform2D inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Rotated;
    Point2D p2Original = inverse * p2Rotated;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(AffineTransform2D, MakeScale)
{
    AffineTransform2D specimen;
    specimen.makeScale(2.0, -1.0);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Scaled = specimen * p1;
    Point2D p2Scaled = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Scaled.getX(), 4.0);
    EXPECT_DOUBLE_EQ(p1Scaled.getY(), -1);

    EXPECT_DOUBLE_EQ(p2Scaled.getX(), -2.0);
    EXPECT_DOUBLE_EQ(p2Scaled.getY(), -4.0);

    AffineTransform2D inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Scaled;
    Point2D p2Original = inverse * p2Scaled;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(AffineTransform2D, MakeTranslation)
{
    AffineTransform2D specimen;
    specimen.makeTranslation(2.0, -1.0);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Scaled = specimen * p1;
    Point2D p2Scaled = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Scaled.getX(), 4.0);
    EXPECT_DOUBLE_EQ(p1Scaled.getY(), 0.0);

    EXPECT_DOUBLE_EQ(p2Scaled.getX(), 1.0);
    EXPECT_DOUBLE_EQ(p2Scaled.getY(), 3.0);

    AffineTransform2D inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Scaled;
    Point2D p2Original = inverse * p2Scaled;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(AffineTransform2D, RotateAboutPoint)
{
    const Point2D centre(3, 2);
    const Point2D pt1(7, 8);

    // Create two transforms to rotate about a specified centre.

    // One all-in-one.
    AffineTransform2D combined;
    combined.makeRotation(Angle::Pi_2, centre);

    // One by construction/multiplication.
    AffineTransform2D specimen;
    specimen.makeTranslation(-centre);
    specimen.appendRotation(Angle::Pi_2);
    specimen.appendTranslation(centre);

    // Verify the matrices are the same.
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_DOUBLE_EQ(combined.toArray()[i], specimen.toArray()[i]);
    }

    // Transform the point.
    Point2D pt1CombineTransformed = combined * pt1;
    Point2D pt1SpecimenTransformed = specimen * pt1;

    // Verify the results are correct and consistent.
    EXPECT_DOUBLE_EQ(pt1CombineTransformed.getX(), -3);
    EXPECT_DOUBLE_EQ(pt1CombineTransformed.getY(), 6);
    EXPECT_DOUBLE_EQ(pt1SpecimenTransformed.getX(), -3);
    EXPECT_DOUBLE_EQ(pt1SpecimenTransformed.getY(), 6);

    // Create the inverse transform.
    AffineTransform2D reverse = combined.inverse();

    // Undo the transform.
    Point2D p1Original = reverse * pt1CombineTransformed;

    // Verify the results are back to the original.
    EXPECT_DOUBLE_EQ(p1Original.getX(), pt1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), pt1.getY());
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

