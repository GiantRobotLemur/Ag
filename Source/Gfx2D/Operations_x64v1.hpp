//! @file Gfx2D/Operations_x64v1.hpp
//! @brief The definition of various low-level operations accelerated by being
//! implemented using SSE2 SIMD technology available to the v1 x86-64 processor
//! architecture.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_OPERATIONS_X64_V1_HPP__
#define __GFX_2D_OPERATIONS_X64_V1_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <xmmintrin.h>

#include "Operations_Base.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
struct OperationsX64v1_Vec4F : public OperationsBase_Vec4F
{
    using vec4f = __m128;
    using vec4f_ptr_t = __m128 *;

    static void copy(const float *lhs, float *rhs) noexcept
    {
        _mm_store_ps(rhs, _mm_load_ps(lhs));
    }

    static void add(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_add_ps(lhsVec, rhsVec));
    }

    static void addAssign(float *lhs, const float *rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);
        _mm_store_ps(lhs, _mm_add_ps(lhsVec, rhsVec));
    }

    static void sub(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_sub_ps(lhsVec, rhsVec));
    }

    static void subAssign(float *lhs, const float *rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);
        _mm_store_ps(lhs, _mm_sub_ps(lhsVec, rhsVec));
    }

    static void mul(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_mul_ps(lhsVec, rhsVec));
    }

    static void mulAssign(float *lhs, const float *rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);
        _mm_store_ps(lhs, _mm_mul_ps(lhsVec, rhsVec));
    }

    static void mul(const float *lhs, float rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps1(&rhs);

        _mm_store_ps(result, _mm_mul_ps(lhsVec, rhsVec));
    }

    static void mulAssign(float *lhs, float rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps1(&rhs);

        _mm_store_ps(lhs, _mm_mul_ps(lhsVec, rhsVec));
    }

    static bool anyZero(const float *rhs) noexcept
    {
        vec4f rhsVec = _mm_load_ps(rhs);
        vec4f zero = _mm_setzero_ps();

        vec4f compResult = _mm_cmpeq_ps(rhsVec, zero);
        int resultMask = _mm_movemask_ps(compResult);

        return (resultMask != 0);
    }

    static void div(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_div_ps(lhsVec, rhsVec));
    }

    static void divAssign(float *lhs, const float *rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);
        _mm_store_ps(lhs, _mm_div_ps(lhsVec, rhsVec));
    }

    static void div(const float *lhs, float rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps1(&rhs);

        _mm_store_ps(result, _mm_div_ps(lhsVec, rhsVec));
    }

    static void divAssign(float *lhs, float rhs) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps1(&rhs);

        _mm_store_ps(lhs, _mm_div_ps(lhsVec, rhsVec));
    }

    static void min(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_min_ps(lhsVec, rhsVec));
    }

    static void max(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_max_ps(lhsVec, rhsVec));
    }

    static void minmax(const float *lhs, const float *rhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);

        _mm_store_ps(result, _mm_min_ps(lhsVec, rhsVec));
        _mm_store_ps(result + 4, _mm_max_ps(lhsVec, rhsVec));
    }

    static void clamp(const float *lhs, const float *minRhs,
                      const float *maxRhs, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f minVec = _mm_load_ps(minRhs);
        vec4f maxVec = _mm_load_ps(maxRhs);

        _mm_store_ps(result, _mm_max_ps(_mm_min_ps(lhsVec, maxVec), minVec));
    }

    static void lerp(const float *lhs, const float *rhs, float scale, float *result) noexcept
    {
        vec4f scaleVec = _mm_load_ps1(&scale);
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsVec = _mm_load_ps(rhs);
        vec4f inverseVec = _mm_sub_ps(_mm_set1_ps(1), scaleVec);

        vec4f resultVec = _mm_add_ps(_mm_mul_ps(lhsVec, inverseVec),
                                     _mm_mul_ps(rhsVec, scaleVec));

        _mm_store_ps(result, resultVec);
    }

    static void fma(const float *lhs, const float *rhsScale,
                    const float *rhsOffset, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs);
        vec4f rhsScaleVec = _mm_load_ps(rhsScale);
        vec4f rhsOffsetVec = _mm_load_ps(rhsOffset);

        vec4f resultVec = _mm_add_ps(_mm_mul_ps(lhsVec, rhsScaleVec), rhsOffsetVec);

        _mm_store_ps(result, resultVec);
    }

    static constexpr int makeShuffleMask(uint8_t first, uint8_t second,
                                         uint8_t third, uint8_t fourth) noexcept
    {
        return (first & 0x03) | ((second & 0x03) << 2) |
            ((third & 0x03) << 4) | ((fourth & 0x03) << 6);
    }

    static void sourceBlend(const float *lhs, const float *rhs,
                            float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs); // { r g b a }
        vec4f rhsVec = _mm_load_ps(rhs);
        vec4f alphaVec = _mm_unpackhi_ps(lhsVec, lhsVec); // { b b a a }
        alphaVec = _mm_unpackhi_ps(alphaVec, alphaVec); // { a a a a }

        // This code is to blend in an alpha of 1.0 in the result
        // is it really needed?
        vec4f zeroVec = _mm_setzero_ps();
        vec4f oneVec = _mm_set1_ps(1.0f);
        vec4f maskVec = _mm_unpackhi_ps(zeroVec, oneVec); // { 0 1 0 1 }
        vec4f scaleVec = _mm_shuffle_ps(maskVec, maskVec,
                                        makeShuffleMask(1, 1, 1, 0)); // { 1 1 1 0 }
        maskVec = _mm_shuffle_ps(maskVec, maskVec,
                                 makeShuffleMask(0, 0, 0, 1)); // { 0 0 0 1 }

        vec4f inverseVec = _mm_sub_ps(oneVec, alphaVec);

        vec4f resultVec = _mm_add_ps(_mm_mul_ps(lhsVec, alphaVec),
                                     _mm_mul_ps(rhsVec, inverseVec));

        // Set the alpha component to 1.
        resultVec = _mm_add_ps(_mm_mul_ps(resultVec, scaleVec), maskVec);

        _mm_store_ps(result, resultVec);
    }

    static void constantBlend(const float *lhs, const float *rhs,
                              float alpha, float *result) noexcept
    {
        vec4f lhsVec = _mm_load_ps(lhs); // { r g b a }
        vec4f rhsVec = _mm_load_ps(rhs);
        vec4f alphaVec = _mm_load_ps1(&alpha); // { a a a a }

        // This code is to blend in an alpha of 1.0 in the result
        // is it really needed?
        vec4f zeroVec = _mm_setzero_ps();
        vec4f oneVec = _mm_set1_ps(1.0f);
        vec4f maskVec = _mm_unpackhi_ps(zeroVec, oneVec); // { 0 1 0 1 }
        vec4f scaleVec = _mm_shuffle_ps(maskVec, maskVec,
                                        makeShuffleMask(1, 1, 1, 0)); // { 1 1 1 0 }
        maskVec = _mm_shuffle_ps(maskVec, maskVec,
                                 makeShuffleMask(0, 0, 0, 1)); // { 0 0 0 1 }

        vec4f inverseVec = _mm_sub_ps(oneVec, alphaVec);

        vec4f resultVec = _mm_add_ps(_mm_mul_ps(lhsVec, alphaVec),
                                     _mm_mul_ps(rhsVec, inverseVec));

        // Set the alpha component to 1.
        resultVec = _mm_add_ps(_mm_mul_ps(resultVec, scaleVec), maskVec);

        _mm_store_ps(result, resultVec);
    }
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
