//! @file Geometry/Test_Matrix3x3.cpp
//! @brief The definition of unit tests for the Matrix3x3 class.
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

#include "Ag/Geometry/Matrix3x3.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Matrix3x3, DefaultConstruct)
{
    Matrix3x3 specimen;

    EXPECT_TRUE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0], 1.0);
    EXPECT_EQ(specimen.M[1], 0.0);
    EXPECT_EQ(specimen.M[2], 0.0);
    EXPECT_EQ(specimen.M[3], 0.0);
    EXPECT_EQ(specimen.M[4], 1.0);
    EXPECT_EQ(specimen.M[5], 0.0);
    EXPECT_EQ(specimen.M[6], 0.0);
    EXPECT_EQ(specimen.M[7], 0.0);
    EXPECT_EQ(specimen.M[8], 1.0);
}

GTEST_TEST(Matrix3x3, InitaliseConstruct)
{
    double input[] = { 2.0, 1.1, -3.0, 5.0, 12, 69, 42, 0, 91 };
    Matrix3x3 specimen(input);

    EXPECT_FALSE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0], 2.0);
    EXPECT_EQ(specimen.M[1], 1.1);
    EXPECT_EQ(specimen.M[2], -3.0);
    EXPECT_EQ(specimen.M[3], 5.0);
    EXPECT_EQ(specimen.M[4], 12.0);
    EXPECT_EQ(specimen.M[5], 69);
    EXPECT_EQ(specimen.M[6], 42);
    EXPECT_EQ(specimen.M[7], 0);
    EXPECT_EQ(specimen.M[8], 91);

    // Test overwriting the matrix with identity values.
    specimen.makeIdentity();
    EXPECT_TRUE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0], 1.0);
    EXPECT_EQ(specimen.M[1], 0.0);
    EXPECT_EQ(specimen.M[2], 0.0);
    EXPECT_EQ(specimen.M[3], 0.0);
    EXPECT_EQ(specimen.M[4], 1.0);
    EXPECT_EQ(specimen.M[5], 0.0);
    EXPECT_EQ(specimen.M[6], 0.0);
    EXPECT_EQ(specimen.M[7], 0.0);
    EXPECT_EQ(specimen.M[8], 1.0);
}

GTEST_TEST(Matrix3x3, MultiplyPoint2D)
{
    Matrix3x3 specimen;
    specimen.makeRotationXY(Angle::Pi_2);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Rotated = specimen * p1;
    Point2D p2Rotated = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Rotated.getX(), -1.0);
    EXPECT_DOUBLE_EQ(p1Rotated.getY(), 2.0);

    EXPECT_DOUBLE_EQ(p2Rotated.getX(), -4.0);
    EXPECT_DOUBLE_EQ(p2Rotated.getY(), -1.0);

    Matrix3x3 inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Rotated;
    Point2D p2Original = inverse * p2Rotated;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(Matrix3x3, MakeScale)
{
    Matrix3x3 specimen;
    specimen.makeScaleXY(2.0, -1.0);

    EXPECT_EQ(specimen.M[0], 2.0);
    EXPECT_EQ(specimen.M[1], 0.0);
    EXPECT_EQ(specimen.M[2], 0.0);
    EXPECT_EQ(specimen.M[3], 0.0);
    EXPECT_EQ(specimen.M[4], -1.0);
    EXPECT_EQ(specimen.M[5], 0.0);
    EXPECT_EQ(specimen.M[6], 0.0);
    EXPECT_EQ(specimen.M[7], 0.0);
    EXPECT_EQ(specimen.M[8], 1.0);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Scaled = specimen * p1;
    Point2D p2Scaled = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Scaled.getX(), 4.0);
    EXPECT_DOUBLE_EQ(p1Scaled.getY(), -1);

    EXPECT_DOUBLE_EQ(p2Scaled.getX(), -2.0);
    EXPECT_DOUBLE_EQ(p2Scaled.getY(), -4.0);

    Matrix3x3 inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Scaled;
    Point2D p2Original = inverse * p2Scaled;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(Matrix3x3, RotateAboutPoint)
{
    const Point2D centre(3, 2);
    const Point2D pt1(7, 8);

    // Create two transforms to rotate about a specified centre.

    // One all-in-one.
    Matrix3x3 combined = Matrix3x3::rotationXY(Angle::Pi_2, centre);

    // One by construction/multiplication.
    Matrix3x3 toOrigin = Matrix3x3::translationXY(-centre);
    Matrix3x3 rotation = Matrix3x3::rotationXY(Angle::Pi_2);
    Matrix3x3 awayFromOrigin = Matrix3x3::translationXY(centre);
    Matrix3x3 specimen = awayFromOrigin * rotation * toOrigin;

    // Verify the matrices are the same.
    for (int i = 0; i < 9; ++i)
    {
        EXPECT_DOUBLE_EQ(combined.M[i], specimen.M[i]);
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
    Matrix3x3 reverse = combined.inverse();

    // Undo the transform.
    Point2D p1Original = reverse * pt1CombineTransformed;

    // Verify the results are back to the original.
    EXPECT_DOUBLE_EQ(p1Original.getX(), pt1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), pt1.getY());
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

