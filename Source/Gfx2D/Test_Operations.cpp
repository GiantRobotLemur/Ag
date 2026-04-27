//! @file Gfx2D/Test_Operations.cpp
//! @brief The definition of unit tests for various implementations of
//! SIMD-accelerated operation classes.
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

#include "Operations_Base.hpp"
#include "Operations_x64v1.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

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
template<typename T>
class Vec4F : public ::testing::Test
{
public:
    using OpType = T;
};

#if defined(AG_ENABLE_X64_V4) || defined(AG_ENABLE_X64_V3) || defined(AG_ENABLE_X64_V2) || defined(AG_ENABLE_X64_V1)
using Vec4F_Types = ::testing::Types<OperationsBase_Vec4F, OperationsX64v1_Vec4F>;
#else
using Vec4F_Types = ::testing::Types<OperationsBase_Vec4F>;
#endif

TYPED_TEST_SUITE(Vec4F, Vec4F_Types);

TYPED_TEST(Vec4F, Copy)
{
    const float lhs[]{ 1, 2, 3, 4 };
    float result[]{ 10, 20, 30, 40 };

    TypeParam::copy(lhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
}

TYPED_TEST(Vec4F, Add)
{
    const float lhs[]{ 1, 2, 3, 4 };
    const float rhs[]{ 10, 20, 30, 40 };
    float result[4];

    TypeParam::add(lhs, rhs, result);

    EXPECT_EQ(result[0], 11);
    EXPECT_EQ(result[1], 22);
    EXPECT_EQ(result[2], 33);
    EXPECT_EQ(result[3], 44);
}

TYPED_TEST(Vec4F, AddAssign)
{
    float lhs[]{ 1, 2, 3, 4 };
    const float rhs[]{ 10, 20, 30, 40 };

    TypeParam::addAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 11);
    EXPECT_EQ(lhs[1], 22);
    EXPECT_EQ(lhs[2], 33);
    EXPECT_EQ(lhs[3], 44);
}

TYPED_TEST(Vec4F, Sub)
{
    const float lhs[]{ 10, 20, 30, 40 };
    const float rhs[]{ 1, 2, 3, 4 };
    float result[4];

    TypeParam::sub(lhs, rhs, result);

    EXPECT_EQ(result[0], 9);
    EXPECT_EQ(result[1], 18);
    EXPECT_EQ(result[2], 27);
    EXPECT_EQ(result[3], 36);
}

TYPED_TEST(Vec4F, SubAssign)
{
    float lhs[]{ 10, 20, 30, 40 };
    const float rhs[]{ 1, 2, 3, 4 };

    TypeParam::subAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 9);
    EXPECT_EQ(lhs[1], 18);
    EXPECT_EQ(lhs[2], 27);
    EXPECT_EQ(lhs[3], 36);
}

TYPED_TEST(Vec4F, Mul)
{
    const float lhs[]{ 1, 2, 3, 4 };
    const float rhs[]{ 10, 20, 30, 40 };
    float result[4];

    TypeParam::mul(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 40);
    EXPECT_EQ(result[2], 90);
    EXPECT_EQ(result[3], 160);
}

TYPED_TEST(Vec4F, MulAssign)
{
    float lhs[]{ 1, 2, 3, 4 };
    const float rhs[]{ 10, 20, 30, 40 };

    TypeParam::mulAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 10);
    EXPECT_EQ(lhs[1], 40);
    EXPECT_EQ(lhs[2], 90);
    EXPECT_EQ(lhs[3], 160);
}

TYPED_TEST(Vec4F, MulScalar)
{
    const float lhs[]{ 1, 2, 3, 4 };
    float result[4];

    TypeParam::mul(lhs, 2, result);

    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 6);
    EXPECT_EQ(result[3], 8);
}

TYPED_TEST(Vec4F, MulScalarAssign)
{
    float lhs[]{ 1, 2, 3, 4 };

    TypeParam::mulAssign(lhs, 2);

    EXPECT_EQ(lhs[0], 2);
    EXPECT_EQ(lhs[1], 4);
    EXPECT_EQ(lhs[2], 6);
    EXPECT_EQ(lhs[3], 8);
}

TYPED_TEST(Vec4F, AnyZero)
{
    const float noZeros[]{ 1, 2, 3, 4 };
    const float oneZero[]{ 1, 0, 3, 4 };
    const float allZeros[]{ 0, 0, 0, 0 };

    EXPECT_FALSE(TypeParam::anyZero(noZeros));
    EXPECT_TRUE(TypeParam::anyZero(oneZero));
    EXPECT_TRUE(TypeParam::anyZero(allZeros));
}

TYPED_TEST(Vec4F, Div)
{
    const float lhs[]{ 10, 20, 30, 40 };
    const float rhs[]{ 1, 2, 3, 4 };
    float result[4];

    TypeParam::div(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 10);
    EXPECT_EQ(result[3], 10);
}

TYPED_TEST(Vec4F, DivAssign)
{
    float lhs[]{ 10, 20, 30, 40 };
    const float rhs[]{ 1, 2, 3, 4 };

    TypeParam::divAssign(lhs, rhs);

    EXPECT_EQ(lhs[0], 10);
    EXPECT_EQ(lhs[1], 10);
    EXPECT_EQ(lhs[2], 10);
    EXPECT_EQ(lhs[3], 10);
}

TYPED_TEST(Vec4F, DivScalar)
{
    const float lhs[]{ 10, 20, 30, 40 };
    float result[4];

    TypeParam::div(lhs, 2, result);

    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 10);
    EXPECT_EQ(result[2], 15);
    EXPECT_EQ(result[3], 20);
}

TYPED_TEST(Vec4F, DivScalarAssign)
{
    float lhs[]{ 10, 20, 30, 40 };

    TypeParam::divAssign(lhs, 2);

    EXPECT_EQ(lhs[0], 5);
    EXPECT_EQ(lhs[1], 10);
    EXPECT_EQ(lhs[2], 15);
    EXPECT_EQ(lhs[3], 20);
}

TYPED_TEST(Vec4F, Min)
{
    const float lhs[]{ 10, 2, 30, 4 };
    const float rhs[]{ 1, 20, 3, 40 };
    float result[4];

    TypeParam::min(lhs, rhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);
}

TYPED_TEST(Vec4F, Max)
{
    const float lhs[]{ 10, 2, 30, 4 };
    const float rhs[]{ 1, 20, 3, 40 };
    float result[4];

    TypeParam::max(lhs, rhs, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
    EXPECT_EQ(result[3], 40);
}

TYPED_TEST(Vec4F, MinMax)
{
    const float lhs[]{ 10, 2, 30, 4 };
    const float rhs[]{ 1, 20, 3, 40 };
    float result[8];

    TypeParam::minmax(lhs, rhs, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
    EXPECT_EQ(result[3], 4);

    EXPECT_EQ(result[4], 10);
    EXPECT_EQ(result[5], 20);
    EXPECT_EQ(result[6], 30);
    EXPECT_EQ(result[7], 40);
}

TYPED_TEST(Vec4F, Clamp)
{
    const float minimums[]{ 1, 2, 3, 4 };
    const float maximums[]{ 10, 20, 30, 40 };
    const float speciman[]{ 0, 5, 90, 40 };
    float result[4];

    TypeParam::clamp(speciman, minimums, maximums, result);

    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 5);
    EXPECT_EQ(result[2], 30);
    EXPECT_EQ(result[3], 40);
}

TYPED_TEST(Vec4F, Lerp)
{
    const float start[]{ 4, 8, 12, 16 };
    const float end[]{ 44, 88, 132, 176 };
    float result[4];

    TypeParam::lerp(start, end, 0.25f, result);

    EXPECT_EQ(result[0], 14);
    EXPECT_EQ(result[1], 28);
    EXPECT_EQ(result[2], 42);
    EXPECT_EQ(result[3], 56);
}

TYPED_TEST(Vec4F, Fma)
{
    const float specimen[]{ 0, 5, 90, 40 };
    const float scales[]{   1, 2, 3, 4 };
    const float offsets[]{ 10, 20, 30, 40 };
    float result[4];

    TypeParam::fma(specimen, scales, offsets, result);

    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 30);
    EXPECT_EQ(result[2], 300);
    EXPECT_EQ(result[3], 200);
}

TYPED_TEST(Vec4F, SourceBlend)
{
    const float lhs[]{ 1, 0.75f, 0.5f, 0.25f };
    // 0.25, 0.1875, 0.125
    const float rhs[]{ 0.75f, 0.5f, 0.75f, 0 };
    // 0.5625, 0.375, 0.5625
    float result[4];

    TypeParam::sourceBlend(lhs, rhs, result);

    EXPECT_EQ(result[0], 0.8125f);
    EXPECT_EQ(result[1], 0.5625f);
    EXPECT_EQ(result[2], 0.6875);
    EXPECT_EQ(result[3], 1);
}

TYPED_TEST(Vec4F, ConstantBlend)
{
    const float lhs[]{ 1, 0.75f, 0.5f, 0 };
    // 0.25, 0.1875, 0.125
    const float rhs[]{ 0.75f, 0.5f, 0.75f, 0 };
    // 0.5625, 0.375, 0.5625
    float result[4];

    TypeParam::constantBlend(lhs, rhs, 0.25f, result);

    EXPECT_EQ(result[0], 0.8125f);
    EXPECT_EQ(result[1], 0.5625f);
    EXPECT_EQ(result[2], 0.6875);
    EXPECT_EQ(result[3], 1);
}

} // Anonymous namespace

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

