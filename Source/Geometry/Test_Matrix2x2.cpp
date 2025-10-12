//! @file Geometry/Test_Matrix2x2.cpp
//! @brief The definition of unit tests for the Matrix2x2 class.
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

#include "Ag/Geometry/Matrix2x2.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Matrix2x2, DefaultConstruct)
{
    Matrix2x2 specimen;

    EXPECT_TRUE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0], 1.0);
    EXPECT_EQ(specimen.M[1], 0.0);
    EXPECT_EQ(specimen.M[2], 0.0);
    EXPECT_EQ(specimen.M[3], 1.0);
}

GTEST_TEST(Matrix2x2, InitaliseConstruct)
{
    double input[] = { 2.0, 1.1, -3.0, 5.0 };
    Matrix2x2 specimen(input);

    EXPECT_FALSE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0],  2.0);
    EXPECT_EQ(specimen.M[1],  1.1);
    EXPECT_EQ(specimen.M[2], -3.0);
    EXPECT_EQ(specimen.M[3],  5.0);

    // Test overwriting the matrix with identity values.
    specimen.makeIdentity();
    EXPECT_TRUE(specimen.isIdentity());

    EXPECT_EQ(specimen.M[0], 1.0);
    EXPECT_EQ(specimen.M[1], 0.0);
    EXPECT_EQ(specimen.M[2], 0.0);
    EXPECT_EQ(specimen.M[3], 1.0);
}

GTEST_TEST(Matrix2x2, MultiplyPoint2D)
{
    Matrix2x2 specimen;
    specimen.makeRotation(Angle::Pi_2);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Rotated = specimen * p1;
    Point2D p2Rotated = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Rotated.getX(), -1.0);
    EXPECT_DOUBLE_EQ(p1Rotated.getY(),  2.0);

    EXPECT_DOUBLE_EQ(p2Rotated.getX(), -4.0);
    EXPECT_DOUBLE_EQ(p2Rotated.getY(), -1.0);

    Matrix2x2 inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Rotated;
    Point2D p2Original = inverse * p2Rotated;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

GTEST_TEST(Matrix2x2, MakeScale)
{
    Matrix2x2 specimen;
    specimen.makeScale(2.0, -1.0);

    EXPECT_EQ(specimen.M[0],  2.0);
    EXPECT_EQ(specimen.M[1],  0.0);
    EXPECT_EQ(specimen.M[2],  0.0);
    EXPECT_EQ(specimen.M[3], -1.0);

    Point2D p1(2.0, 1.0);
    Point2D p2(-1.0, 4.0);
    Point2D p1Scaled = specimen * p1;
    Point2D p2Scaled = specimen * p2;

    EXPECT_DOUBLE_EQ(p1Scaled.getX(), 4.0);
    EXPECT_DOUBLE_EQ(p1Scaled.getY(), -1);

    EXPECT_DOUBLE_EQ(p2Scaled.getX(), -2.0);
    EXPECT_DOUBLE_EQ(p2Scaled.getY(), -4.0);

    Matrix2x2 inverse = specimen.inverse();
    Point2D p1Original = inverse * p1Scaled;
    Point2D p2Original = inverse * p2Scaled;

    EXPECT_DOUBLE_EQ(p1Original.getX(), p1.getX());
    EXPECT_DOUBLE_EQ(p1Original.getY(), p1.getY());

    EXPECT_DOUBLE_EQ(p2Original.getX(), p2.getX());
    EXPECT_DOUBLE_EQ(p2Original.getY(), p2.getY());
}

} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

