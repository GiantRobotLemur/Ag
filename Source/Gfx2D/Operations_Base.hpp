//! @file Gfx2D/Operations_Base.hpp
//! @brief The definition of various low-level operations which could be
//! accelerated with SIMD.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_OPERATIONS_BASE_HPP__
#define __GFX_2D_OPERATIONS_BASE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

#include <algorithm>
#include <utility>

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
struct OperationsBase_Vec4F
{
    static void copy(const float *lhs, float *rhs) noexcept
    {
        std::copy_n(lhs, 4, rhs);
    }

    static void add(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = lhs[0] + rhs[0];
        result[1] = lhs[1] + rhs[1];
        result[2] = lhs[2] + rhs[2];
        result[3] = lhs[3] + rhs[3];
    }

    static void addAssign(float *lhs, const float *rhs) noexcept
    {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
        lhs[2] += rhs[2];
        lhs[3] += rhs[3];
    }

    static void sub(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = lhs[0] - rhs[0];
        result[1] = lhs[1] - rhs[1];
        result[2] = lhs[2] - rhs[2];
        result[3] = lhs[3] - rhs[3];
    }

    static void subAssign(float *lhs, const float *rhs) noexcept
    {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
        lhs[2] -= rhs[2];
        lhs[3] -= rhs[3];
    }

    static void mul(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = lhs[0] * rhs[0];
        result[1] = lhs[1] * rhs[1];
        result[2] = lhs[2] * rhs[2];
        result[3] = lhs[3] * rhs[3];
    }

    static void mulAssign(float *lhs, const float *rhs) noexcept
    {
        lhs[0] *= rhs[0];
        lhs[1] *= rhs[1];
        lhs[2] *= rhs[2];
        lhs[3] *= rhs[3];
    }

    static void mul(const float *lhs, float rhs, float *result) noexcept
    {
        result[0] = lhs[0] * rhs;
        result[1] = lhs[1] * rhs;
        result[2] = lhs[2] * rhs;
        result[3] = lhs[3] * rhs;
    }

    static void mulAssign(float *lhs, float rhs) noexcept
    {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
        lhs[2] *= rhs;
        lhs[3] *= rhs;
    }

    static bool anyZero(const float *rhs) noexcept
    {
        return (rhs[0] * rhs[1] * rhs[2] * rhs[3]) == 0;
    }

    static void div(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = lhs[0] / rhs[0];
        result[1] = lhs[1] / rhs[1];
        result[2] = lhs[2] / rhs[2];
        result[3] = lhs[3] / rhs[3];
    }

    static void divAssign(float *lhs, const float *rhs) noexcept
    {
        lhs[0] /= rhs[0];
        lhs[1] /= rhs[1];
        lhs[2] /= rhs[2];
        lhs[3] /= rhs[3];
    }

    static void div(const float *lhs, float rhs, float *result) noexcept
    {
        result[0] = lhs[0] / rhs;
        result[1] = lhs[1] / rhs;
        result[2] = lhs[2] / rhs;
        result[3] = lhs[3] / rhs;
    }

    static void divAssign(float *lhs, float rhs) noexcept
    {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
        lhs[2] /= rhs;
        lhs[3] /= rhs;
    }

    static void min(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = std::min(lhs[0], rhs[0]);
        result[1] = std::min(lhs[1], rhs[1]);
        result[2] = std::min(lhs[2], rhs[2]);
        result[3] = std::min(lhs[3], rhs[3]);
    }

    static void max(const float *lhs, const float *rhs, float *result) noexcept
    {
        result[0] = std::max(lhs[0], rhs[0]);
        result[1] = std::max(lhs[1], rhs[1]);
        result[2] = std::max(lhs[2], rhs[2]);
        result[3] = std::max(lhs[3], rhs[3]);
    }

    static void minmax(const float *lhs, const float *rhs, float *result) noexcept
    {
        for (uint8_t i = 0; i < 4; ++i)
        {
            auto resultPair = std::minmax(lhs[i], rhs[i]);

            result[i] = resultPair.first;
            result[i + 4] = resultPair.second;
        }
    }

    static void clamp(const float *lhs, const float *minRhs,
                      const float *maxRhs, float *result) noexcept
    {
        result[0] = std::clamp(lhs[0], minRhs[0], maxRhs[0]);
        result[1] = std::clamp(lhs[1], minRhs[1], maxRhs[1]);
        result[2] = std::clamp(lhs[2], minRhs[2], maxRhs[2]);
        result[3] = std::clamp(lhs[3], minRhs[3], maxRhs[3]);
    }

    static void lerp(const float *lhs, const float *rhs, float scale, float *result) noexcept
    {
        float inverseScale = 1.0f - scale;

        result[0] = (lhs[0] * inverseScale) + (rhs[0] * scale);
        result[1] = (lhs[1] * inverseScale) + (rhs[1] * scale);
        result[2] = (lhs[2] * inverseScale) + (rhs[2] * scale);
        result[3] = (lhs[3] * inverseScale) + (rhs[3] * scale);
    }

    static void fma(const float *lhs, const float *rhsScale,
                    const float *rhsOffset, float *result) noexcept
    {
        result[0] = std::fma(lhs[0], rhsScale[0], rhsOffset[0]);
        result[1] = std::fma(lhs[1], rhsScale[1], rhsOffset[1]);
        result[2] = std::fma(lhs[2], rhsScale[2], rhsOffset[2]);
        result[3] = std::fma(lhs[3], rhsScale[3], rhsOffset[3]);
    }

    static void sourceBlend(const float *lhs, const float *rhs,
                            float *result) noexcept
    {
        float alpha = lhs[3];
        float inverseAlpha = 1.0f - alpha;

        result[0] = (lhs[0] * alpha) + (rhs[0] * inverseAlpha);
        result[1] = (lhs[1] * alpha) + (rhs[1] * inverseAlpha);
        result[2] = (lhs[2] * alpha) + (rhs[2] * inverseAlpha);
        result[3] = 1;
    }

    static void constantBlend(const float *lhs, const float *rhs,
                              float alpha, float *result) noexcept
    {
        float inverseAlpha = 1.0f - alpha;

        result[0] = (lhs[0] * alpha) + (rhs[0] * inverseAlpha);
        result[1] = (lhs[1] * alpha) + (rhs[1] * inverseAlpha);
        result[2] = (lhs[2] * alpha) + (rhs[2] * inverseAlpha);
        result[3] = 1;
    }
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
