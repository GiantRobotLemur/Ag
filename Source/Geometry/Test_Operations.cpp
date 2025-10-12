//! @file Geometry/Test_Operations.cpp
//! @brief The definition of unit tests for the Operations_* structures which
//! implement the same operations with different SIMD technology.
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

#include "Operations.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Vec2D : public ::testing::Test
{
public:
    using OpType = T;
};

template<typename T>
class Mat2x2D : public ::testing::Test
{
public:
    static constexpr double Epsilon = 1e-8;
    using OpType = T;
};

template<typename T>
class AffineTrans2D : public ::testing::Test
{
public:
    static constexpr double Epsilon = 1e-8;
    using OpType = T;
};

#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2)
using Vec2D_Types = ::testing::Types<OperationsBase_Vec2D, OperationsX64v1_Vec2D, OperationsX64v2_Vec2D>;
using Mat2x2D_Types = ::testing::Types<OperationsBase_Mat2x2D, OperationsX64v1_Mat2x2D, OperationsX64v2_Mat2x2D>;
using Trans2D_Types = ::testing::Types<OperationsBase_AffineTrans2D, OperationsX64v1_AffineTrans2D>;
#elif defined(AG_ENABLE_X64_V1)
using Vec2D_Types = ::testing::Types<OperationsBase_Vec2D, OperationsX64v1_Vec2D>;
using Mat2x2D_Types = ::testing::Types<OperationsBase_Mat2x2D, OperationsX64v1_Mat2x2D>;
using Trans2D_Types = ::testing::Types<OperationsBase_AffineTrans2D, OperationsX64v1_AffineTrans2D>;
#else
using Vec2D_Types = ::testing::Types<OperationsBase_Vec2D>;
using Mat2x2D_Types = ::testing::Types<OperationsBase_Mat2x2D>;
using Trans2D_Types = ::testing::Types<OperationsBase_AffineTrans2D>;
#endif

#pragma region Vec2D Tests
TYPED_TEST_SUITE(Vec2D, Vec2D_Types);

TYPED_TEST(Vec2D, Copy)
{
    const double lhs[]{ 1, 2 };
    double result[]{ 10, 20 };

    TypeParam::copy(lhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
}

TYPED_TEST(Vec2D, Neg)
{
    const double lhs[]{ 3, 4 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::neg(lhs, result);

    EXPECT_EQ(result[0], -3);
    EXPECT_EQ(result[1], -4);
}

TYPED_TEST(Vec2D, IsEqual)
{
    const double lhs1[]{ 3, 4 };
    const double rhs1[]{ 30, 40 };
    const double lhs2[]{ 4, 3 };

    EXPECT_FALSE(TypeParam::isNotEqual(lhs1, lhs1));
    EXPECT_FALSE(TypeParam::isNotEqual(rhs1, rhs1));
    EXPECT_FALSE(TypeParam::isNotEqual(lhs2, lhs2));

    EXPECT_FALSE(TypeParam::isEqual(lhs1, lhs2));
    EXPECT_FALSE(TypeParam::isEqual(lhs1, rhs1));
    EXPECT_FALSE(TypeParam::isEqual(lhs2, rhs1));
}

TYPED_TEST(Vec2D, IsNotEqual)
{
    const double lhs1[]{ 3, 4 };
    const double rhs1[]{ 30, 40 };
    const double lhs2[]{ 4, 3 };

    EXPECT_FALSE(TypeParam::isNotEqual(lhs1, lhs1));
    EXPECT_FALSE(TypeParam::isNotEqual(rhs1, rhs1));
    EXPECT_FALSE(TypeParam::isNotEqual(lhs2, lhs2));

    EXPECT_TRUE(TypeParam::isNotEqual(lhs1, lhs2));
    EXPECT_TRUE(TypeParam::isNotEqual(lhs1, rhs1));
    EXPECT_TRUE(TypeParam::isNotEqual(lhs2, rhs1));
}

TYPED_TEST(Vec2D, Add)
{
    const double lhs[]{ 3, 4 };
    const double rhs[]{ 30, 40 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::add(lhs, rhs, result);

    EXPECT_EQ(result[0], 33);
    EXPECT_EQ(result[1], 44);
}

TYPED_TEST(Vec2D, AddAssign)
{
    double lhs[]{ 2, 3 };
    const double rhs[]{ 20, 30 };

    TypeParam::addAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 22);
    EXPECT_EQ(lhs[1], 33);
}

TYPED_TEST(Vec2D, Sub)
{
    const double lhs[]{ 10, 20 };
    const double rhs[]{ 1, 2 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::sub(lhs, rhs, result);

    EXPECT_EQ(result[0], 9);
    EXPECT_EQ(result[1], 18);
}

TYPED_TEST(Vec2D, SubAssign)
{
    double lhs[]{ 30, 40 };
    const double rhs[]{ 3, 4 };

    TypeParam::subAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 27);
    EXPECT_EQ(lhs[1], 36);
}

TYPED_TEST(Vec2D, Mul)
{
    const double lhs[]{ 1, 2 };
    const double rhs[]{ 10, 20 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::mul(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 40);
}

TYPED_TEST(Vec2D, MulAssign)
{
    double lhs[]{ 1, 2 };
    const double rhs[]{ 10, 20 };

    TypeParam::mulAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 10);
    EXPECT_EQ(lhs[1], 40);
}

TYPED_TEST(Vec2D, MulScalar)
{
    const double lhs[]{ 1, 2 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::scalarMul(lhs, 2, result);

    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
}

TYPED_TEST(Vec2D, MulScalarAssign)
{
    double lhs[]{ 1, 2 };

    TypeParam::scalarMulAssign(lhs, 2);

    EXPECT_EQ(lhs[0], 2);
    EXPECT_EQ(lhs[1], 4);
}

TYPED_TEST(Vec2D, AnyZero)
{
    const double noZeros[]{ 1, 2 };
    const double oneZero[]{ 1, 0 };
    const double allZeros[]{ 0, 0 };

    EXPECT_FALSE(TypeParam::anyZero(noZeros));
    EXPECT_TRUE(TypeParam::anyZero(oneZero));
    EXPECT_TRUE(TypeParam::anyZero(allZeros));
}

TYPED_TEST(Vec2D, AllZero)
{
    const double noZeros[]{ 1, 2 };
    const double oneZero[]{ 1, 0 };
    const double allZeros[]{ 0, 0 };

    EXPECT_FALSE(TypeParam::allZero(noZeros));
    EXPECT_FALSE(TypeParam::allZero(oneZero));
    EXPECT_TRUE(TypeParam::allZero(allZeros));
}

TYPED_TEST(Vec2D, Div)
{
    const double lhs[]{ 10, 20 };
    const double rhs[]{ 1, 2 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::div(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 10);
}

TYPED_TEST(Vec2D, DivAssign)
{
    double lhs[]{ 10, 20 };
    const double rhs[]{ 1, 2 };

    TypeParam::divAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 10);
    EXPECT_EQ(lhs[1], 10);
}

TYPED_TEST(Vec2D, DivScalar)
{
    const double lhs[]{ 10, 20 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::scalarDiv(lhs, 2, result);

    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 10);
}

TYPED_TEST(Vec2D, DivScalarAssign)
{
    double lhs[]{ 10, 20 };

    TypeParam::scalarDivAssign(lhs, 2);

    EXPECT_EQ(lhs[0], 5);
    EXPECT_EQ(lhs[1], 10);
}

TYPED_TEST(Vec2D, Min)
{
    const double lhs[]{ 10, 2 };
    const double rhs[]{ 1, 20 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::min(lhs, rhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
}

TYPED_TEST(Vec2D, Max)
{
    const double lhs[]{ 10, 2 };
    const double rhs[]{ 1, 20 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::max(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
}

TYPED_TEST(Vec2D, MinMax)
{
    const double lhs[]{ 10, 2 };
    const double rhs[]{ 1, 20 };
    double result[OperationsBase_Vec2D::ElementCount * 2];

    TypeParam::minmax(lhs, rhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);

    EXPECT_EQ(result[2], 10);
    EXPECT_EQ(result[3], 20);
}

TYPED_TEST(Vec2D, Clamp)
{
    const double minimums[]{ 1, 2, 3, 4 };
    const double maximums[]{ 10, 20, 30, 40 };
    const double speciman[]{ 0, 5, 90, 40 };
    double result[OperationsBase_Vec2D::ElementCount * 2];

    TypeParam::clamp(speciman, minimums, maximums, result);
    TypeParam::clamp(speciman + 2, minimums + 2, maximums + 2, result + 2);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 5);

    EXPECT_EQ(result[2], 30);
    EXPECT_EQ(result[3], 40);
}

TYPED_TEST(Vec2D, Lerp)
{
    const double start[]{ 4, 8 };
    const double end[]{ 44, 88 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::lerp(start, end, 0.25f, result);

    EXPECT_EQ(result[0], 14);
    EXPECT_EQ(result[1], 28);
}

TYPED_TEST(Vec2D, Fma)
{
    const double specimen[]{ 0, 5 };
    const double scales[]{ 1, 2 };
    const double offsets[]{ 10, 20 };
    double result[OperationsBase_Vec2D::ElementCount];

    TypeParam::fma(specimen, scales, offsets, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 30);
}

TYPED_TEST(Vec2D, MagnitudeSq)
{
    const double specimen1[]{ 0, 5 };
    const double specimen2[]{ -1, -2 };

    EXPECT_EQ(TypeParam::magnitudeSq(specimen1), 25);
    EXPECT_EQ(TypeParam::magnitudeSq(specimen2), 5);
}

TYPED_TEST(Vec2D, DotProduct)
{
    const double lhs[]{ 2, 5 };
    const double rhs[]{ -1, -2 };

    EXPECT_EQ(TypeParam::dot(lhs, rhs), -12);
}

TYPED_TEST(Vec2D, Determinant)
{
    const double lhs[]{ 2, 5 };
    const double rhs[]{ -1, -2 };

    EXPECT_EQ(TypeParam::det(lhs, rhs), 1);
}

TYPED_TEST(Vec2D, Distance)
{
    const double lhs[]{ 10, 20 };
    const double rhs[]{ 13, 24 };

    EXPECT_DOUBLE_EQ(TypeParam::distance(lhs, rhs), 5.0);
}

TYPED_TEST(Vec2D, TryNormalise)
{
    const double specimen1[]{ 3, 4 };
    const double specimen2[]{ -1, 0 };
    const double specimen3[]{ 0, 0 };
    double result[2];

    EXPECT_TRUE(TypeParam::tryNormalise(specimen1, result));
    EXPECT_DOUBLE_EQ(result[0], 3.0 / 5.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0 / 5.0);

    EXPECT_TRUE(TypeParam::tryNormalise(specimen2, result));
    EXPECT_DOUBLE_EQ(result[0], -1);
    EXPECT_DOUBLE_EQ(result[1], 0);

    EXPECT_FALSE(TypeParam::tryNormalise(specimen3, result));
}
#pragma endregion

#pragma region Mat2x2D Tests
TYPED_TEST_SUITE(Mat2x2D, Mat2x2D_Types);

TYPED_TEST(Mat2x2D, Copy)
{
    const double lhs[]{ 1, 2, 3, 4 };
    double result[]{ 10, 20, 30, 40 };

    TypeParam::copy(lhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
}

TYPED_TEST(Mat2x2D, Identity)
{
    double specimen[]{ -1, 12, 36, 42 };

    EXPECT_FALSE(TypeParam::isIdentity(specimen));

    TypeParam::makeIdentity(specimen);

    EXPECT_EQ(specimen[0], 1);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], 1);

    EXPECT_TRUE(TypeParam::isIdentity(specimen));
}

TYPED_TEST(Mat2x2D, MakeUniformScale)
{
    double specimen[]{ -1, 12, 36, 42 };
    double scale = 10;
    TypeParam::makeUniformScale(scale, specimen);

    EXPECT_EQ(specimen[0], 10);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], 10);
}

TYPED_TEST(Mat2x2D, MakeScale)
{
    double specimen[]{ -1, 12, 36, 42 };
    const double scale[] = { 10, -4 };
    TypeParam::makeScale(scale, specimen);

    EXPECT_EQ(specimen[0], 10);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], -4);
}

TYPED_TEST(Mat2x2D, MakeRotation)
{
    double specimen[]{ -1, 12, 36, 42 };
    TypeParam::makeRotation(-Angle::Pi_2, specimen);

    EXPECT_NEAR(specimen[0], 0, Epsilon);
    EXPECT_NEAR(specimen[1], 1, Epsilon);
    EXPECT_NEAR(specimen[2], -1, Epsilon);
    EXPECT_NEAR(specimen[3], 0, Epsilon);
}

TYPED_TEST(Mat2x2D, Inverse)
{
    double specimen[]{ -1, 12, 36, 42 };
    TypeParam::makeRotation(-Angle::Pi_2, specimen);

    EXPECT_NEAR(specimen[0], 0, Epsilon);
    EXPECT_NEAR(specimen[1], 1, Epsilon);
    EXPECT_NEAR(specimen[2], -1, Epsilon);
    EXPECT_NEAR(specimen[3], 0, Epsilon);

    double expectedInverse[4];
    TypeParam::makeRotation(Angle::Pi_2, expectedInverse);

    double inverse[4];
    ASSERT_TRUE(TypeParam::tryCalculateInverse(specimen, inverse));

    EXPECT_DOUBLE_EQ(expectedInverse[0], inverse[0]);
    EXPECT_DOUBLE_EQ(expectedInverse[1], inverse[1]);
    EXPECT_DOUBLE_EQ(expectedInverse[2], inverse[2]);
    EXPECT_DOUBLE_EQ(expectedInverse[3], inverse[3]);
}

TYPED_TEST(Mat2x2D, InverseSingular)
{
    double specimen[]{ 0, 1, 0, -1 };
    double inverse[4];

    EXPECT_FALSE(TypeParam::tryCalculateInverse(specimen, inverse));
}

TYPED_TEST(Mat2x2D, MultiplyByPoint)
{
    double specimen[4];
    TypeParam::makeRotation(Angle::Pi_2, specimen);

    const double p1[] = { 2.0, 1.0 };
    const double p2[] = { -1.0, 4.0 };

    double p1Rotated[2];
    double p2Rotated[2];

    TypeParam::multiplyPoint2D(specimen, p1, p1Rotated);
    TypeParam::multiplyPoint2D(specimen, p2, p2Rotated);

    EXPECT_DOUBLE_EQ(p1Rotated[0], -1.0);
    EXPECT_DOUBLE_EQ(p1Rotated[1], 2.0);

    EXPECT_DOUBLE_EQ(p2Rotated[0], -4.0);
    EXPECT_DOUBLE_EQ(p2Rotated[1], -1.0);

    double inverse[4];
    ASSERT_TRUE(TypeParam::tryCalculateInverse(specimen, inverse));

    double p1Original[2];
    double p2Original[2];

    TypeParam::multiplyPoint2D(inverse, p1Rotated, p1Original);
    TypeParam::multiplyPoint2D(inverse, p2Rotated, p2Original);

    EXPECT_DOUBLE_EQ(p1Original[0], p1[0]);
    EXPECT_DOUBLE_EQ(p1Original[1], p1[1]);

    EXPECT_DOUBLE_EQ(p2Original[0], p2[0]);
    EXPECT_DOUBLE_EQ(p2Original[1], p2[1]);
}

TYPED_TEST(Mat2x2D, Multiply)
{
    const double matrix1[] = { 1, 2,
                               3, 4 };
    const double matrix2[] = { 40, 30,
                               20, 10 };
    double result[4];

    TypeParam::multiply(matrix1, matrix2, result);

    EXPECT_DOUBLE_EQ(result[0], 80);
    EXPECT_DOUBLE_EQ(result[1], 50);
    EXPECT_DOUBLE_EQ(result[2], 200);
    EXPECT_DOUBLE_EQ(result[3], 130);
}

TYPED_TEST(Mat2x2D, MultiplyInPlace)
{
    double matrix1[] = { 1, 2,
                         3, 4 };
    const double matrix2[] = { 40, 30,
                               20, 10 };

    TypeParam::multiplyInPlace(matrix1, matrix2);

    EXPECT_DOUBLE_EQ(matrix1[0], 80);
    EXPECT_DOUBLE_EQ(matrix1[1], 50);
    EXPECT_DOUBLE_EQ(matrix1[2], 200);
    EXPECT_DOUBLE_EQ(matrix1[3], 130);
}

#pragma endregion

#pragma region AffineTrans2D Tests
TYPED_TEST_SUITE(AffineTrans2D, Trans2D_Types);

TYPED_TEST(AffineTrans2D, Copy)
{
    const double lhs[]{ 1, 2, 3, 4, 5, 6 };
    double result[]{ 10, 20, 30, 40, 50, 60, 70, 80 };

    TypeParam::copy(lhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
    EXPECT_EQ(result[4], 5);
    EXPECT_EQ(result[5], 6);
    EXPECT_EQ(result[6], 70);
    EXPECT_EQ(result[7], 80);
}

TYPED_TEST(AffineTrans2D, Identity)
{
    double specimen[]{ -1, 12, 36, 42, 0, 31 };

    EXPECT_FALSE(TypeParam::isIdentity(specimen));

    TypeParam::makeIdentity(specimen);

    EXPECT_EQ(specimen[0], 1);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], 1);
    EXPECT_EQ(specimen[4], 0);
    EXPECT_EQ(specimen[5], 0);

    EXPECT_TRUE(TypeParam::isIdentity(specimen));
}

TYPED_TEST(AffineTrans2D, MakeUniformScale)
{
    double specimen[]{ -1, 12, 36, 42, 9, -31 };
    double scale = 10;
    TypeParam::makeUniformScale(scale, specimen);

    EXPECT_EQ(specimen[0], 10);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], 10);
    EXPECT_EQ(specimen[4], 0);
    EXPECT_EQ(specimen[5], 0);
}

TYPED_TEST(AffineTrans2D, MakeScale)
{
    double specimen[]{ -1, 12, 36, 42, 9, -31 };
    const double scale[] = { 10, -4 };
    TypeParam::makeScale(scale, specimen);

    EXPECT_EQ(specimen[0], 10);
    EXPECT_EQ(specimen[1], 0);
    EXPECT_EQ(specimen[2], 0);
    EXPECT_EQ(specimen[3], -4);
    EXPECT_EQ(specimen[4], 0);
    EXPECT_EQ(specimen[5], 0);
}

TYPED_TEST(AffineTrans2D, MakeRotation)
{
    double specimen[]{ -1, 12, 36, 42, 9, -31 };
    TypeParam::makeRotation(-Angle::Pi_2, specimen);

    EXPECT_NEAR(specimen[0], 0, Epsilon);
    EXPECT_NEAR(specimen[1], 1, Epsilon);
    EXPECT_NEAR(specimen[2], -1, Epsilon);
    EXPECT_NEAR(specimen[3], 0, Epsilon);
    EXPECT_EQ(specimen[4], 0);
    EXPECT_EQ(specimen[5], 0);
}

TYPED_TEST(AffineTrans2D, Inverse)
{
    double specimen[]{ -1, 12, 36, 42, 9, -31 };
    TypeParam::makeRotation(-Angle::Pi_2, specimen);

    EXPECT_NEAR(specimen[0], 0, Epsilon);
    EXPECT_NEAR(specimen[1], 1, Epsilon);
    EXPECT_NEAR(specimen[2], -1, Epsilon);
    EXPECT_NEAR(specimen[3], 0, Epsilon);
    EXPECT_EQ(specimen[4], 0);
    EXPECT_EQ(specimen[5], 0);

    double expectedInverse[6];
    TypeParam::makeRotation(Angle::Pi_2, expectedInverse);

    double inverse[6];
    ASSERT_TRUE(TypeParam::tryCalculateInverse(specimen, inverse));

    EXPECT_DOUBLE_EQ(expectedInverse[0], inverse[0]);
    EXPECT_DOUBLE_EQ(expectedInverse[1], inverse[1]);
    EXPECT_DOUBLE_EQ(expectedInverse[2], inverse[2]);
    EXPECT_DOUBLE_EQ(expectedInverse[3], inverse[3]);
    EXPECT_EQ(inverse[4], 0);
    EXPECT_EQ(inverse[5], 0);
}

TYPED_TEST(AffineTrans2D, InverseSingular)
{
    double specimen[]{ 0, 1, 0, -1, 12, 19 };
    double inverse[6];

    EXPECT_FALSE(TypeParam::tryCalculateInverse(specimen, inverse));
}

TYPED_TEST(AffineTrans2D, MultiplyByPoint)
{
    double specimen[6];
    TypeParam::makeRotation(Angle::Pi_2, specimen);

    const double p1[] = { 2.0, 1.0 };
    const double p2[] = { -1.0, 4.0 };

    double p1Rotated[2];
    double p2Rotated[2];

    TypeParam::multiplyPoint2D(specimen, p1, p1Rotated);
    TypeParam::multiplyPoint2D(specimen, p2, p2Rotated);

    EXPECT_DOUBLE_EQ(p1Rotated[0], -1.0);
    EXPECT_DOUBLE_EQ(p1Rotated[1], 2.0);

    EXPECT_DOUBLE_EQ(p2Rotated[0], -4.0);
    EXPECT_DOUBLE_EQ(p2Rotated[1], -1.0);

    double inverse[6];
    ASSERT_TRUE(TypeParam::tryCalculateInverse(specimen, inverse));

    double p1Original[2];
    double p2Original[2];

    TypeParam::multiplyPoint2D(inverse, p1Rotated, p1Original);
    TypeParam::multiplyPoint2D(inverse, p2Rotated, p2Original);

    EXPECT_DOUBLE_EQ(p1Original[0], p1[0]);
    EXPECT_DOUBLE_EQ(p1Original[1], p1[1]);

    EXPECT_DOUBLE_EQ(p2Original[0], p2[0]);
    EXPECT_DOUBLE_EQ(p2Original[1], p2[1]);
}

TYPED_TEST(AffineTrans2D, Multiply)
{
    const double matrix1[] = { 1, 2,
                               3, 4,
                               5, 6 };
    const double matrix2[] = { 40, 30,
                               20, 10,
                               15, 25 };
    double result[6];

    TypeParam::multiply(matrix1, matrix2, result);

    EXPECT_DOUBLE_EQ(result[0], 80);
    EXPECT_DOUBLE_EQ(result[1], 50);
    EXPECT_DOUBLE_EQ(result[2], 200);
    EXPECT_DOUBLE_EQ(result[3], 130);
    EXPECT_DOUBLE_EQ(result[4], 70);
    EXPECT_DOUBLE_EQ(result[5], 151);
}

TYPED_TEST(AffineTrans2D, MultiplyInPlace)
{
    double matrix1[] = { 1, 2,
                         3, 4,
                         5, 6 };
    const double matrix2[] = { 40, 30,
                               20, 10,
                               15, 25 };

    TypeParam::multiplyInPlace(matrix1, matrix2);

    EXPECT_DOUBLE_EQ(matrix1[0], 80);
    EXPECT_DOUBLE_EQ(matrix1[1], 50);
    EXPECT_DOUBLE_EQ(matrix1[2], 200);
    EXPECT_DOUBLE_EQ(matrix1[3], 130);
    EXPECT_DOUBLE_EQ(matrix1[4], 70);
    EXPECT_DOUBLE_EQ(matrix1[5], 151);
}

#pragma endregion


} // Anonymous namespace

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

