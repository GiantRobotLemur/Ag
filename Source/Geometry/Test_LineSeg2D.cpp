//! @file Test_LineSeg2D.cpp
//! @brief The definition of unit tests for the LineSeg2D class.
//! @author Nick Arkell
//! @copyright (c) 2021-2024 Nick Arkell : Software Engineer
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include <cmath>

#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(LineSeg2D, Length)
{
    LineSeg2D specimen(0, 0, 1, 1);

    EXPECT_NEAR(specimen.getLength(), std::sqrt(2.0), 1e-8);
}

GTEST_TEST(LineSeg2D, Start)
{
    LineSeg2D specimen(5, 2, -1, 42);

    EXPECT_EQ(specimen.getStart(), Point2D(5, 2));
}

GTEST_TEST(LineSeg2D, GetDeterminant)
{
    constexpr double Tol = 1e-8;
    LineSeg2D horizontal(2, 5, 9, 5);

    // Test points above the horizontal line.
    EXPECT_GT(horizontal.getDeterminant({ 1, 6 }), 0.0);
    EXPECT_GT(horizontal.getDeterminant({ 2, 7 }), 0.0);
    EXPECT_GT(horizontal.getDeterminant({ 4, 8 }), 0.0);
    EXPECT_GT(horizontal.getDeterminant({ 9, 6.5 }), 0.0);
    EXPECT_GT(horizontal.getDeterminant({ 25, 97 }), 0.0);

    // Test points below the horizontal line.
    EXPECT_LT(horizontal.getDeterminant({ 1, -6 }), 0.0);
    EXPECT_LT(horizontal.getDeterminant({ 2, -7 }), 0.0);
    EXPECT_LT(horizontal.getDeterminant({ 4, -8 }), 0.0);
    EXPECT_LT(horizontal.getDeterminant({ 9, -6.5 }), 0.0);
    EXPECT_LT(horizontal.getDeterminant({ 25, -97 }), 0.0);

    // Test points on the horizontal line.
    EXPECT_NEAR(horizontal.getDeterminant({ 1, 5 }), 0.0, Tol);
    EXPECT_NEAR(horizontal.getDeterminant({ 2, 5 }), 0.0, Tol);
    EXPECT_NEAR(horizontal.getDeterminant({ 4, 5 }), 0.0, Tol);
    EXPECT_NEAR(horizontal.getDeterminant({ 9, 5 }), 0.0, Tol);
    EXPECT_NEAR(horizontal.getDeterminant({ 25, 5 }), 0.0, Tol);

    LineSeg2D reverseHorizontal(9, 5, 2, 5);

    // Test points above the reversed horizontal line.
    EXPECT_LT(reverseHorizontal.getDeterminant({ 1, 6 }), 0.0);
    EXPECT_LT(reverseHorizontal.getDeterminant({ 2, 7 }), 0.0);
    EXPECT_LT(reverseHorizontal.getDeterminant({ 4, 8 }), 0.0);
    EXPECT_LT(reverseHorizontal.getDeterminant({ 9, 6.5 }), 0.0);
    EXPECT_LT(reverseHorizontal.getDeterminant({ 25, 97 }), 0.0);

    // Test points below the reversed reverse horizontal line.
    EXPECT_GT(reverseHorizontal.getDeterminant({ 1, -6 }), 0.0);
    EXPECT_GT(reverseHorizontal.getDeterminant({ 2, -7 }), 0.0);
    EXPECT_GT(reverseHorizontal.getDeterminant({ 4, -8 }), 0.0);
    EXPECT_GT(reverseHorizontal.getDeterminant({ 9, -6.5 }), 0.0);
    EXPECT_GT(reverseHorizontal.getDeterminant({ 25, -97 }), 0.0);

    // Test points on the reversed horizontal line.
    EXPECT_NEAR(reverseHorizontal.getDeterminant({ 1, 5 }), 0.0, Tol);
    EXPECT_NEAR(reverseHorizontal.getDeterminant({ 2, 5 }), 0.0, Tol);
    EXPECT_NEAR(reverseHorizontal.getDeterminant({ 4, 5 }), 0.0, Tol);
    EXPECT_NEAR(reverseHorizontal.getDeterminant({ 9, 5 }), 0.0, Tol);
    EXPECT_NEAR(reverseHorizontal.getDeterminant({ 25, 5 }), 0.0, Tol);

    LineSeg2D vertical(-11, 4, -11, 25);

    // Test points 'logically above' (left of) the vertical line.
    EXPECT_GT(vertical.getDeterminant({ -12, 2 }), 0.0);
    EXPECT_GT(vertical.getDeterminant({ -15, 4 }), 0.0);
    EXPECT_GT(vertical.getDeterminant({ -19, 19 }), 0.0);
    EXPECT_GT(vertical.getDeterminant({ -16, 25 }), 0.0);
    EXPECT_GT(vertical.getDeterminant({ -11.5, 29 }), 0.0);

    // Test points 'logically below' (right of) the vertical line.
    EXPECT_LT(vertical.getDeterminant({ 12, 2 }), 0.0);
    EXPECT_LT(vertical.getDeterminant({ 15, 4 }), 0.0);
    EXPECT_LT(vertical.getDeterminant({ 19, 19 }), 0.0);
    EXPECT_LT(vertical.getDeterminant({ 16, 25 }), 0.0);
    EXPECT_LT(vertical.getDeterminant({ 11.5, 29 }), 0.0);

    // Test points on the vertical line.
    EXPECT_NEAR(vertical.getDeterminant({ -11, 2 }), 0.0, Tol);
    EXPECT_NEAR(vertical.getDeterminant({ -11, 4 }), 0.0, Tol);
    EXPECT_NEAR(vertical.getDeterminant({ -11, 15 }), 0.0, Tol);
    EXPECT_NEAR(vertical.getDeterminant({ -11, 25 }), 0.0, Tol);
    EXPECT_NEAR(vertical.getDeterminant({ -11, 33 }), 0.0, Tol);

    LineSeg2D reversedVertical(-11, 25, -11, 4);

    // Test points 'logically above' (right of) the reversed vertical line.
    EXPECT_GT(reversedVertical.getDeterminant({ 12, 2 }), 0.0);
    EXPECT_GT(reversedVertical.getDeterminant({ 15, 4 }), 0.0);
    EXPECT_GT(reversedVertical.getDeterminant({ 19, 19 }), 0.0);
    EXPECT_GT(reversedVertical.getDeterminant({ 16, 25 }), 0.0);
    EXPECT_GT(reversedVertical.getDeterminant({ 11.5, 29 }), 0.0);

    // Test points 'logically below' (left of) the reversed vertical line.
    EXPECT_LT(reversedVertical.getDeterminant({ -12, 2 }), 0.0);
    EXPECT_LT(reversedVertical.getDeterminant({ -15, 4 }), 0.0);
    EXPECT_LT(reversedVertical.getDeterminant({ -19, 19 }), 0.0);
    EXPECT_LT(reversedVertical.getDeterminant({ -16, 25 }), 0.0);
    EXPECT_LT(reversedVertical.getDeterminant({ -11.5, 29 }), 0.0);

    // Test points on the reversed vertical line.
    EXPECT_NEAR(reversedVertical.getDeterminant({ -11, 2 }), 0.0, Tol);
    EXPECT_NEAR(reversedVertical.getDeterminant({ -11, 4 }), 0.0, Tol);
    EXPECT_NEAR(reversedVertical.getDeterminant({ -11, 15 }), 0.0, Tol);
    EXPECT_NEAR(reversedVertical.getDeterminant({ -11, 25 }), 0.0, Tol);
    EXPECT_NEAR(reversedVertical.getDeterminant({ -11, 33 }), 0.0, Tol);

    LineSeg2D diagonal(0, 0, 9, 9);

    // Test points above the diagonal line.
    EXPECT_GT(diagonal.getDeterminant({ -2, -1 }), 0.0);
    EXPECT_GT(diagonal.getDeterminant({ -1, 1 }), 0.0);
    EXPECT_GT(diagonal.getDeterminant({ 4, 8 }), 0.0);
    EXPECT_GT(diagonal.getDeterminant({ 8, 10 }), 0.0);
    EXPECT_GT(diagonal.getDeterminant({ 25, 97 }), 0.0);

    // Test points below the diagonal line.
    EXPECT_LT(diagonal.getDeterminant({ -3, -5 }), 0.0);
    EXPECT_LT(diagonal.getDeterminant({ 1, -1 }), 0.0);
    EXPECT_LT(diagonal.getDeterminant({ 4, 2 }), 0.0);
    EXPECT_LT(diagonal.getDeterminant({ 10, 8 }), 0.0);
    EXPECT_LT(diagonal.getDeterminant({ 25, -97 }), 0.0);

    // Test points on the diagonal line.
    EXPECT_NEAR(diagonal.getDeterminant({ -11, -11 }), 0.0, Tol);
    EXPECT_NEAR(diagonal.getDeterminant({ 0, 0 }), 0.0, Tol);
    EXPECT_NEAR(diagonal.getDeterminant({ 4, 4 }), 0.0, Tol);
    EXPECT_NEAR(diagonal.getDeterminant({ 9, 9 }), 0.0, Tol);
    EXPECT_NEAR(diagonal.getDeterminant({ 25, 25 }), 0.0, Tol);
}


GTEST_TEST(LineSeg2D, TryCalculateIntersectionParam)
{
    Point2D vertices[] = {
        { 2, 1 },
        { 57, 56 },
        { 25, 2 },
        { -38, 65 }
    };

    LineSeg2D firstSecond(vertices[0], vertices[1]);
    LineSeg2D thirdFourth(vertices[2], vertices[3]);

    NumericDomain domain(-38, 65);
    double firstSecondParam = 0, thirdFourthParam = 0;

    ASSERT_TRUE(firstSecond.tryCalculateIntersectionParam(domain, thirdFourth,
                                                          firstSecondParam,
                                                          thirdFourthParam));

    EXPECT_GT(firstSecondParam, 0.0);
    EXPECT_LT(firstSecondParam, 1.0);
    EXPECT_GT(thirdFourthParam, 0.0);
    EXPECT_LT(thirdFourthParam, 1.0);

    Point2D firstIntersection = firstSecond.getPoint(firstSecondParam);
    Point2D secondIntersection = thirdFourth.getPoint(thirdFourthParam);
    Point2D crossAt(14, 13);

    EXPECT_DOUBLE_EQ(crossAt.getX(), firstIntersection.getX());
    EXPECT_DOUBLE_EQ(crossAt.getY(), firstIntersection.getY());

    EXPECT_DOUBLE_EQ(crossAt.getX(), secondIntersection.getX());
    EXPECT_DOUBLE_EQ(crossAt.getY(), secondIntersection.getY());
}

GTEST_TEST(LineSeg2D, TryCalculateIntersection)
{
    Point2D vertices[] = {
        { 2, 1 },
        { 57, 56 },
        { 25, 2 },
        { -38, 65 }
    };

    Point2D crossAt(14, 13);

    LineSeg2D firstSecond(vertices[0], vertices[1]);
    LineSeg2D thirdFourth(vertices[2], vertices[3]);

    NumericDomain domain(-38, 65);
    Point2D intersectionPt;

    EXPECT_TRUE(firstSecond.tryCalculateIntersection(domain, thirdFourth, intersectionPt));

    EXPECT_DOUBLE_EQ(intersectionPt.getX(), crossAt.getX());
    EXPECT_DOUBLE_EQ(intersectionPt.getY(), crossAt.getY());
}

} // Anonymous namespace.

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

