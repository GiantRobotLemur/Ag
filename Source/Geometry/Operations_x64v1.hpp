//! @file Geometry/Operations_x64v1.hpp
//! @brief The declaration of basic implementations of operations 
//! accelerated by SSE 2 SIMD technology available to the v1 x86-64 processor
//! architecture.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_OPERATIONS_X64_V1_HPP__
#define __AG_GEOMETRY_OPERATIONS_X64_V1_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <emmintrin.h>

#include "Operations_Base.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Implementations of operations on pairs of double values accelerated
//! by SSE 2 operations.
struct OperationsX64v1_Vec2D : public OperationsBase_Vec2D
{
    using Vec2D = __m128d;

    static void setZero(double *rhs) noexcept
    {
        _mm_store_pd(rhs, _mm_setzero_pd());
    }

    static void setOne(double *rhs) noexcept
    {
        _mm_store_pd(rhs, _mm_set1_pd(1.0));
    }

    static void copy(const double *lhs, double *rhs) noexcept
    {
        _mm_store_pd(rhs, _mm_load_pd(lhs));
    }

    static bool isEqual(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultMask = _mm_cmpeq_pd(lhsVec, rhsVec);

        return _mm_movemask_pd(resultMask) == 3;
    }

    static bool isNotEqual(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultMask = _mm_cmpneq_pd(lhsVec, rhsVec);

        return _mm_movemask_pd(resultMask) == 3;
    }

    static void neg(const double *lhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D zero = _mm_setzero_pd();
        Vec2D resultVec = _mm_sub_pd(zero, lhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void add(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_add_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void addAssign(double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_add_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static void sub(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_sub_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void subAssign(double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_sub_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static void mul(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_mul_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void mulAssign(double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_mul_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static void scalarMul(const double *lhs, double rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load1_pd(&rhs);
        Vec2D resultVec = _mm_mul_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void scalarMulAssign(double *lhs, double rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load1_pd(&rhs);
        Vec2D resultVec = _mm_mul_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static bool anyZero(const double *rhs) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultMask = _mm_cmpeq_pd(rhsVec, zero);

        return _mm_movemask_pd(resultMask) != 0;
    }

    static bool allZero(const double *rhs) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultMask = _mm_cmpeq_pd(rhsVec, zero);

        return _mm_movemask_pd(resultMask) == 3;
    }

    static void div(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_div_pd(lhsVec, rhsVec);
        _mm_store_pd(result, resultVec);
    }

    static void divAssign(double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_div_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static void scalarDiv(const double *lhs, double rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load1_pd(&rhs);
        Vec2D resultVec = _mm_div_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void scalarDivAssign(double *lhs, double rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load1_pd(&rhs);
        Vec2D resultVec = _mm_div_pd(lhsVec, rhsVec);

        _mm_store_pd(lhs, resultVec);
    }

    static void min(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_min_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void max(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D resultVec = _mm_max_pd(lhsVec, rhsVec);

        _mm_store_pd(result, resultVec);
    }

    static void minmax(const double *lhs, const double *rhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D minResultVec = _mm_min_pd(lhsVec, rhsVec);
        Vec2D maxResultVec = _mm_max_pd(lhsVec, rhsVec);

        _mm_store_pd(result, minResultVec);
        _mm_store_pd(result + ElementCount, maxResultVec);
    }

    static void clamp(const double *lhs, const double *minRhs,
                      const double *maxRhs, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D minVec = _mm_load_pd(minRhs);
        Vec2D maxVec = _mm_load_pd(maxRhs);
        Vec2D resultVec = _mm_max_pd(_mm_min_pd(lhsVec, maxVec), minVec);

        _mm_store_pd(result, resultVec);
    }

    static void lerp(const double *lhs, const double *rhs, double scale, double *result) noexcept
    {
        Vec2D one = _mm_set1_pd(1.0);
        Vec2D scaleVec = _mm_load1_pd(&scale);             // [ scale, scale ]
        Vec2D inverseScaleVec = _mm_sub_pd(one, scaleVec); // [ 1 - scale, 1 - scale ]
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);

        // [ (lhsX * invScale) + (rhsX * scale), (lhsY * invScale) + (rhsY * scale) ]
        Vec2D resultVec = _mm_add_pd(_mm_mul_pd(inverseScaleVec, lhsVec),
                                     _mm_mul_pd(scaleVec, rhsVec));

        _mm_store_pd(result, resultVec);
    }

    static void scalarFma(const double *lhs, double rhsScale,
                          const double *rhsOffset, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsScaleVec = _mm_load1_pd(&rhsScale);
        Vec2D rhsOffsetVec = _mm_load_pd(rhsOffset);

        Vec2D resultVec = _mm_add_pd(_mm_mul_pd(lhsVec, rhsScaleVec), rhsOffsetVec);

        _mm_store_pd(result, resultVec);
    }

    static void fma(const double *lhs, const double *rhsScale,
                    const double *rhsOffset, double *result) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsScaleVec = _mm_load_pd(rhsScale);
        Vec2D rhsOffsetVec = _mm_load_pd(rhsOffset);

        Vec2D resultVec = _mm_add_pd(_mm_mul_pd(lhsVec, rhsScaleVec), rhsOffsetVec);

        _mm_store_pd(result, resultVec);
    }

    static double magnitudeSq(const double *rhs) noexcept
    {
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D rhsSq = _mm_mul_pd(rhsVec, rhsVec);
        Vec2D rhsHi = _mm_unpackhi_pd(rhsSq, rhsSq);

        return _mm_add_sd(rhsSq, rhsHi).m128d_f64[0];
    }

    static double dot(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D factors = _mm_mul_pd(lhsVec, rhsVec);
        Vec2D factorHi = _mm_unpackhi_pd(factors, factors);

        return _mm_add_sd(factors, factorHi).m128d_f64[0];
    }

    static double det(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);    // [ Lx Ly ]
        Vec2D rhsVec = _mm_loadr_pd(rhs);   // [ Ry Rx ]

        Vec2D factors = _mm_mul_pd(lhsVec, rhsVec); // [ (Lx * Ry) (Ly * Rx) ]
        Vec2D factorHi = _mm_unpackhi_pd(factors, factors); // [ (Ly * Rx) (Ly * Rx) ]

        return _mm_sub_sd(factors, factorHi).m128d_f64[0];
    }

    static double distance(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D delta = _mm_sub_pd(rhsVec, lhsVec);
        Vec2D magSq = _mm_mul_pd(delta, delta);

        Vec2D magSqHi = _mm_unpackhi_pd(magSq, magSq);
        Vec2D sum = _mm_add_sd(magSq, magSqHi);
        Vec2D mag = _mm_sqrt_sd(_mm_setzero_pd(), sum);

        return mag.m128d_f64[0];
    }

    static bool tryNormalise(const double *rhs, double *result) noexcept
    {
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D rhsSqs = _mm_mul_pd(rhsVec, rhsVec); // [ (rhsX * rhsX) (rhsY * rhsY) ]
        Vec2D rhsY = _mm_unpackhi_pd(rhsSqs, rhsSqs); // [ (rhsY * rhsY) (rhsY * rhsY) ]
        Vec2D magSq = _mm_add_sd(rhsSqs, rhsY); // [ ((rhsX * rhsX) + (rhsY * rhsY)) (rhsY * rhsY) ]
        Vec2D zero = _mm_setzero_pd(); // [ 0 0 ]
        Vec2D isZero = _mm_cmpeq_sd(zero, magSq); 
        int cmpResult = _mm_movemask_pd(isZero);

        if (cmpResult)
        {
            return false;
        }
        else
        {
            Vec2D magnitude = _mm_sqrt_sd(zero, magSq); // [ sqrt(magSq) 0 ]
            Vec2D denominatorVec = _mm_unpacklo_pd(magnitude, magnitude); // [ sqrt(magSq) sqrt(magSq) ]
            Vec2D unitVec = _mm_div_pd(rhsVec, denominatorVec); // [ (rhsX / sqrt(magSq)) (rhsY / sqrt(magSq)) ]
            _mm_store_pd(result, unitVec);

            return true;
        }
    }

    // Note: for matrix multiply SSE2: https://stackoverflow.com/questions/18499971/efficient-4x4-matrix-multiplication-c-vs-assembly
};

//! @brief Implementations of operations on matrices of two by two double
//! values accelerated by SSE 2 operations.
struct OperationsX64v1_Mat2x2D : public OperationsBase_Mat2x2D
{
    using Vec2D = __m128d;

    static void copy(const double *src, double *dest) noexcept
    {
        Vec2D row1 = _mm_load_pd(src);
        Vec2D row2 = _mm_load_pd(src + 2);
        _mm_store_pd(dest, row1);
        _mm_store_pd(dest + 2, row2);
    }

    static void makeIdentity(double *result) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D one = _mm_set1_pd(1);

        _mm_store_pd(result, _mm_unpacklo_pd(one, zero));
        _mm_store_pd(result + 2, _mm_unpacklo_pd(zero, one));
    }

    static bool isIdentity(const double *m) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D one = _mm_set1_pd(1);

        Vec2D row1 = _mm_load_pd(m);
        Vec2D row2 = _mm_load_pd(m + 2);

        Vec2D row1Result = _mm_cmpeq_pd(_mm_unpacklo_pd(one, zero), row1);
        Vec2D row2Result = _mm_cmpeq_pd(_mm_unpacklo_pd(zero, one), row2);

        int result = _mm_movemask_pd(row1Result) |
            (_mm_movemask_pd(row2Result) << 2);

        return result == 15;
    }

    static void makeUniformScale(double scale, double *m) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D scaleVec = _mm_load1_pd(&scale);
        Vec2D row1 = _mm_unpacklo_pd(scaleVec, zero);
        Vec2D row2 = _mm_unpacklo_pd(zero, scaleVec);

        _mm_store_pd(m, row1);
        _mm_store_pd(m + 2, row2);
    }

    static void makeScale(const double *scale, double *m) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D scaleVec = _mm_load_pd(scale);
        Vec2D row1 = _mm_unpacklo_pd(scaleVec, zero);
        Vec2D row2 = _mm_unpackhi_pd(zero, scaleVec);

        _mm_store_pd(m, row1);
        _mm_store_pd(m + 2, row2);
    }

    static void makeRotation(double angleInRadians, double *m) noexcept
    {
        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };
        double cosSin[] = { std::cos(angleInRadians), std::sin(angleInRadians) };

        Vec2D cosSinVec = _mm_load_pd(cosSin);                  // [ cos sin ]
        Vec2D row1Factors = _mm_load_pd(oneMinusOne);           // [  1  -1  ]
        Vec2D row1 = _mm_mul_pd(cosSinVec, row1Factors);        // [ cos -sin ]
        Vec2D row2 = _mm_shuffle_pd(cosSinVec, cosSinVec, 1);   // [ sin  cos ]

        _mm_store_pd(m, row1);
        _mm_store_pd(m + 2, row2);
    }

    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        // Calculate the determinant.
        Vec2D row1 = _mm_load_pd(m);            // [ A B ]
        Vec2D row2Rev = _mm_loadr_pd(m + 2);    // [ D C ]

        Vec2D factors = _mm_mul_pd(row1, row2Rev);          // [ AD BC ]
        Vec2D factorLo = _mm_unpacklo_pd(factors, factors); // [ AD AD ]
        Vec2D factorHi = _mm_unpackhi_pd(factors, factors); // [ BC BC ]

        Vec2D det = _mm_sub_pd(factorLo, factorHi); // [ (AD - BC) (AD - BC) ]

        int isZero = _mm_movemask_pd(_mm_cmpeq_pd(det, _mm_setzero_pd()));

        if (isZero)
            return false;

        // Divide all matrix components by the calculated determinant in the
        // following order: [ ( D / determinant) (-B / determinant) ]
        //                  [ (-C / determinant) ( A / determinant) ]

        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };

        Vec2D oneMinusOneVec = _mm_load_pd(oneMinusOne);
        Vec2D row1Mod = _mm_div_pd(_mm_mul_pd(row1, oneMinusOneVec), det); // 1/det [ A -B ]
        Vec2D row2RevMod = _mm_div_pd(_mm_mul_pd(row2Rev, oneMinusOneVec), det); // 1/det [ D -C ]

        Vec2D invRow1 = _mm_shuffle_pd(row2RevMod, row1Mod, 2); // 1/det [  D -B ]
        Vec2D invRow2 = _mm_shuffle_pd(row2RevMod, row1Mod, 1); // 1/det [ -C  A ]

        _mm_store_pd(inverse, invRow1);
        _mm_store_pd(inverse + 2, invRow2);

        return true;
    }

    static void multiplyPoint2D(const double *m, const double *pt, double *result) noexcept
    {
        // [ A B   * [ x y ] = [ (Ax + By) (Cx + Dy) ]
        //   C D ]

        Vec2D row1 = _mm_load_pd(m);        // [ A B ]
        Vec2D row2 = _mm_load_pd(m + 2);    // [ C D ]
        Vec2D ptVec = _mm_load_pd(pt);      // [ x y ]

        Vec2D xResult = _mm_mul_pd(row1, ptVec);    // [ Ax By ]
        Vec2D yResult = _mm_mul_pd(row2, ptVec);    // [ Cx Dy ]

        Vec2D col1 = _mm_unpacklo_pd(xResult, yResult); // [ Ax Cx ]
        Vec2D col2 = _mm_unpackhi_pd(xResult, yResult); // [ By Dy ]

        Vec2D transformed = _mm_add_pd(col1, col2); // [ (Ax + By) (Cx + Dy) ]

        _mm_store_pd(result, transformed);
    }

    static void multiply(const double *m, const double *n, double *result) noexcept
    {
        // [ A B   * [ a b   =  [ (Aa + Bc) (Ab + Bd)
        //   C D ]     c d ]      (Ca + Dc) (Cb + Dd) ]

        Vec2D mRow1 = _mm_load_pd(m);
        Vec2D mRow2 = _mm_load_pd(m + 2);

        Vec2D A = _mm_unpacklo_pd(mRow1, mRow1);  // [ A A ]
        Vec2D B = _mm_unpackhi_pd(mRow1, mRow1);  // [ B B ]
        Vec2D C = _mm_unpacklo_pd(mRow2, mRow2);  // [ C C ]
        Vec2D D = _mm_unpackhi_pd(mRow2, mRow2);  // [ D D ]

        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]

        Vec2D rRow1First = _mm_mul_pd(A, nRow1);    // [ Aa Ab ]
        Vec2D rRow1Second = _mm_mul_pd(B, nRow2);   // [ Bc Bd ]

        Vec2D rRow2First = _mm_mul_pd(C, nRow1);    // [ Ca Cb ]
        Vec2D rRow2Second = _mm_mul_pd(D, nRow2);   // [ Dc Dd ]

        Vec2D rRow1 = _mm_add_pd(rRow1First, rRow1Second);  // [ (Aa + Bc) (Ab + Bd) ]
        Vec2D rRow2 = _mm_add_pd(rRow2First, rRow2Second);  // [ (Ca + Dc) (Cb + Dd) ]

        _mm_store_pd(result, rRow1);
        _mm_store_pd(result + 2, rRow2);
    }

    static void multiplyInPlace(double *lhs, const double *n) noexcept
    {
        // [ A B   * [ a b   =  [ (Aa + Bc) (Ab + Bd)
        //   C D ]     c d ]      (Ca + Dc) (Cb + Dd) ]

        Vec2D mRow1 = _mm_load_pd(lhs);
        Vec2D mRow2 = _mm_load_pd(lhs + 2);

        Vec2D A = _mm_unpacklo_pd(mRow1, mRow1);  // [ A A ]
        Vec2D B = _mm_unpackhi_pd(mRow1, mRow1);  // [ B B ]
        Vec2D C = _mm_unpacklo_pd(mRow2, mRow2);  // [ C C ]
        Vec2D D = _mm_unpackhi_pd(mRow2, mRow2);  // [ D D ]

        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]

        Vec2D rRow1First = _mm_mul_pd(A, nRow1);    // [ Aa Ab ]
        Vec2D rRow1Second = _mm_mul_pd(B, nRow2);   // [ Bc Bd ]

        Vec2D rRow2First = _mm_mul_pd(C, nRow1);    // [ Ca Cb ]
        Vec2D rRow2Second = _mm_mul_pd(D, nRow2);   // [ Dc Dd ]

        Vec2D rRow1 = _mm_add_pd(rRow1First, rRow1Second);  // [ (Aa + Bc) (Ab + Bd) ]
        Vec2D rRow2 = _mm_add_pd(rRow2First, rRow2Second);  // [ (Ca + Dc) (Cb + Dd) ]

        _mm_store_pd(lhs, rRow1);
        _mm_store_pd(lhs + 2, rRow2);
    }
};

//! @brief Implementations of operations on a 2D affine transforms
//! represented by 6 double values accelerated by SSE 2.
struct OperationsX64v1_AffineTrans2D : public OperationsBase_AffineTrans2D
{
    using Vec2D = __m128d;

    static void copy(const double *src, double *dest) noexcept
    {
        Vec2D row1 = _mm_load_pd(src);
        Vec2D row2 = _mm_load_pd(src + 2);
        Vec2D row3 = _mm_load_pd(src + 4);

        _mm_store_pd(dest, row1);
        _mm_store_pd(dest + 2, row2);
        _mm_store_pd(dest + 4, row3);
    }

    static void makeIdentity(double *dest) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D one = _mm_set1_pd(1);

        _mm_store_pd(dest, _mm_unpacklo_pd(one, zero));
        _mm_store_pd(dest + 2, _mm_unpacklo_pd(zero, one));
        _mm_store_pd(dest + 4, zero);
    }

    static bool isIdentity(const double *lhs) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D one = _mm_set1_pd(1);

        Vec2D row1 = _mm_load_pd(lhs);
        Vec2D row2 = _mm_load_pd(lhs + 2);
        Vec2D row3 = _mm_load_pd(lhs + 4);

        Vec2D row1Result = _mm_cmpeq_pd(_mm_unpacklo_pd(one, zero), row1);
        Vec2D row2Result = _mm_cmpeq_pd(_mm_unpacklo_pd(zero, one), row2);
        Vec2D row3Result = _mm_cmpeq_pd(zero, row3);

        int result = _mm_movemask_pd(row1Result) |
            (_mm_movemask_pd(row2Result) << 2) |
            (_mm_movemask_pd(row3Result) << 4);

        return result == 0x3F;
    }

    static void makeUniformScale(double scale, double *dest) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D scaleVec = _mm_load1_pd(&scale);
        Vec2D row1 = _mm_unpacklo_pd(scaleVec, zero);
        Vec2D row2 = _mm_unpacklo_pd(zero, scaleVec);

        _mm_store_pd(dest, row1);
        _mm_store_pd(dest + 2, row2);
        _mm_store_pd(dest + 4, zero);
    }

    static void makeScale(const double *scale, double *dest) noexcept
    {
        Vec2D zero = _mm_setzero_pd();
        Vec2D scaleVec = _mm_load_pd(scale);
        Vec2D row1 = _mm_unpacklo_pd(scaleVec, zero);
        Vec2D row2 = _mm_unpackhi_pd(zero, scaleVec);

        _mm_store_pd(dest, row1);
        _mm_store_pd(dest + 2, row2);
        _mm_store_pd(dest + 4, zero);
    }

    static void makeTranslation(const double *offsets, double *dest) noexcept
    {
        dest[0] = 1;
        dest[1] = dest[2] = 0;
        dest[3] = 1;
        dest[4] = offsets[0];
        dest[5] = offsets[1];

        Vec2D zero = _mm_setzero_pd();
        Vec2D one = _mm_set1_pd(1);
        Vec2D offsetsVec = _mm_load_pd(offsets);

        _mm_store_pd(dest, _mm_unpacklo_pd(one, zero));
        _mm_store_pd(dest + 2, _mm_unpacklo_pd(zero, one));
        _mm_store_pd(dest + 4, offsetsVec);
    }

    static void makeRotation(double angleInRadians, double *dest) noexcept
    {
        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };
        double cosSin[] = { std::cos(angleInRadians), std::sin(angleInRadians) };

        Vec2D cosSinVec = _mm_load_pd(cosSin);                  // [ cos sin ]
        Vec2D row1Factors = _mm_load_pd(oneMinusOne);           // [  1  -1  ]
        Vec2D row1 = _mm_mul_pd(cosSinVec, row1Factors);        // [ cos -sin ]
        Vec2D row2 = _mm_shuffle_pd(cosSinVec, cosSinVec, 1);   // [ sin  cos ]

        _mm_store_pd(dest, row1);
        _mm_store_pd(dest + 2, row2);
        _mm_store_pd(dest + 4, _mm_setzero_pd());
    }

    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        // [ A B   -1 =   [     D        -B
        //   C D        1      -C         A
        //   ---        /   -------------------
        //   E F ]     det  (BF - DE) (CE - AF) ]
        //
        // det = (AD - BC)

        // Calculate the determinant.
        Vec2D row1 = _mm_load_pd(m);            // [ A B ]
        Vec2D row2Rev = _mm_loadr_pd(m + 2);    // [ D C ]
        Vec2D row3 = _mm_load_pd(m + 4);        // [ E F ]

        Vec2D factors = _mm_mul_pd(row1, row2Rev);          // [ AD BC ]
        Vec2D factorLo = _mm_unpacklo_pd(factors, factors); // [ AD AD ]
        Vec2D factorHi = _mm_unpackhi_pd(factors, factors); // [ BC BC ]

        Vec2D det = _mm_sub_pd(factorLo, factorHi); // [ (AD - BC) (AD - BC) ]

        int isZero = _mm_movemask_pd(_mm_cmpeq_pd(det, _mm_setzero_pd()));

        if (isZero)
            return false;

        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };

        Vec2D oneMinusOneVec = _mm_load_pd(oneMinusOne);
        Vec2D row1Mod = _mm_div_pd(_mm_mul_pd(row1, oneMinusOneVec), det); // 1/det [ A -B ]
        Vec2D row2RevMod = _mm_div_pd(_mm_mul_pd(row2Rev, oneMinusOneVec), det); // 1/det [ D -C ]

        Vec2D invRow1 = _mm_shuffle_pd(row2RevMod, row1Mod, 2); // 1/det [  D -B ]
        Vec2D invRow2 = _mm_shuffle_pd(row2RevMod, row1Mod, 1); // 1/det [ -C  A ]

        _mm_store_pd(inverse, invRow1);
        _mm_store_pd(inverse + 2, invRow2);

        Vec2D col1 = _mm_unpacklo_pd(row2Rev, row1);    // [ D A ]
        Vec2D temp1 = _mm_mul_pd(col1, row3);           // [ DE AF ]

        Vec2D row3Rev = _mm_shuffle_pd(row3, row3, 1); // [ F E ]
        Vec2D col2 = _mm_unpackhi_pd(row1, row2Rev); // [ B C ]

        Vec2D temp2 = _mm_mul_pd(row3Rev, col2);    // [ BF CE ]

        Vec2D offsetVec = _mm_sub_pd(temp2, temp1); // [ (BF - DE) (CE - AF) ]
        _mm_store_pd(inverse + 4, _mm_div_pd(offsetVec, det));

        return true;
    }

    static void multiplyPoint2D(const double *m, const double *pt, double *result)
    {
        // [ A B   * [ x   = [ Ax + By + E
        //   C D       y       Cx + Dy + F
        //   ---       -       -----------
        //   E F ]     1 ]           1     ]

        Vec2D row1 = _mm_load_pd(m);        // [ A B ]
        Vec2D row2 = _mm_load_pd(m + 2);    // [ C D ]
        Vec2D row3 = _mm_load_pd(m + 4);    // [ E F ]
        Vec2D ptVec = _mm_load_pd(pt);      // [ x y ]

        Vec2D xResult = _mm_mul_pd(row1, ptVec);    // [ Ax By ]
        Vec2D yResult = _mm_mul_pd(row2, ptVec);    // [ Cx Dy ]

        Vec2D col1 = _mm_unpacklo_pd(xResult, yResult); // [ Ax Cx ]
        Vec2D col2 = _mm_unpackhi_pd(xResult, yResult); // [ By Dy ]

        Vec2D scaled = _mm_add_pd(col1, col2); // [ (Ax + By) (Cx + Dy) ]
        Vec2D transformed = _mm_add_pd(scaled, row3);

        _mm_store_pd(result, transformed);
    }

    static void multiply(const double *m, const double *n,
                         double *result) noexcept
    {
        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        Vec2D mRow1 = _mm_load_pd(m);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(m + 2);   // [ C D ]

        Vec2D nRow3 = _mm_load_pd(n + 4);   // [ e f ]

        // Calculate the translation terms (row 3 of the result).
        Vec2D colX = _mm_mul_pd(mRow1, nRow3);   // [ Ae Bf ]
        Vec2D colY = _mm_mul_pd(mRow2, nRow3);   // [ Ce Df ]

        Vec2D rowX = _mm_unpacklo_pd(colX, colY);   // [ Ae Ce ]
        Vec2D rowY = _mm_unpackhi_pd(colX, colY);   // [ Bf Df ]
        Vec2D rowXY = _mm_add_pd(rowX, rowY);   // [ (Ae + Bf) (Ce + Df) ]

        Vec2D mRow3 = _mm_load_pd(m + 4);   // [ E F ]
        Vec2D translation = _mm_add_pd(mRow3, rowXY); // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(result + 4, translation);

        // Now start working on rows 1 and 2 of the result.
        Vec2D A = _mm_unpacklo_pd(mRow1, mRow1);  // [ A A ]
        Vec2D B = _mm_unpackhi_pd(mRow1, mRow1);  // [ B B ]
        Vec2D C = _mm_unpacklo_pd(mRow2, mRow2);  // [ C C ]
        Vec2D D = _mm_unpackhi_pd(mRow2, mRow2);  // [ D D ]

        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]

        Vec2D rRow1First = _mm_mul_pd(A, nRow1);    // [ Aa Ab ]
        Vec2D rRow1Second = _mm_mul_pd(B, nRow2);   // [ Bc Bd ]

        Vec2D rRow2First = _mm_mul_pd(C, nRow1);    // [ Ca Cb ]
        Vec2D rRow2Second = _mm_mul_pd(D, nRow2);   // [ Dc Dd ]

        Vec2D rRow1 = _mm_add_pd(rRow1First, rRow1Second);  // [ (Aa + Bc) (Ab + Bd) ]
        Vec2D rRow2 = _mm_add_pd(rRow2First, rRow2Second);  // [ (Ca + Dc) (Cb + Dd) ]

        _mm_store_pd(result, rRow1);
        _mm_store_pd(result + 2, rRow2);
    }

    static void multiplyInPlace(double *result, const double *n) noexcept
    {
        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        Vec2D mRow1 = _mm_load_pd(result);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(result + 2);   // [ C D ]

        Vec2D nRow3 = _mm_load_pd(n + 4);   // [ e f ]

        // Calculate the translation terms (row 3 of the result).
        Vec2D colX = _mm_mul_pd(mRow1, nRow3);   // [ Ae Bf ]
        Vec2D colY = _mm_mul_pd(mRow2, nRow3);   // [ Ce Df ]

        Vec2D rowX = _mm_unpacklo_pd(colX, colY);   // [ Ae Ce ]
        Vec2D rowY = _mm_unpackhi_pd(colX, colY);   // [ Bf Df ]
        Vec2D rowXY = _mm_add_pd(rowX, rowY);   // [ (Ae + Bf) (Ce + Df) ]

        Vec2D mRow3 = _mm_load_pd(result + 4);   // [ E F ]
        Vec2D translation = _mm_add_pd(mRow3, rowXY); // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(result + 4, translation);

        // Now start working on rows 1 and 2 of the result.
        Vec2D A = _mm_unpacklo_pd(mRow1, mRow1);  // [ A A ]
        Vec2D B = _mm_unpackhi_pd(mRow1, mRow1);  // [ B B ]
        Vec2D C = _mm_unpacklo_pd(mRow2, mRow2);  // [ C C ]
        Vec2D D = _mm_unpackhi_pd(mRow2, mRow2);  // [ D D ]

        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]

        Vec2D rRow1First = _mm_mul_pd(A, nRow1);    // [ Aa Ab ]
        Vec2D rRow1Second = _mm_mul_pd(B, nRow2);   // [ Bc Bd ]

        Vec2D rRow2First = _mm_mul_pd(C, nRow1);    // [ Ca Cb ]
        Vec2D rRow2Second = _mm_mul_pd(D, nRow2);   // [ Dc Dd ]

        Vec2D rRow1 = _mm_add_pd(rRow1First, rRow1Second);  // [ (Aa + Bc) (Ab + Bd) ]
        Vec2D rRow2 = _mm_add_pd(rRow2First, rRow2Second);  // [ (Ca + Dc) (Cb + Dd) ]

        _mm_store_pd(result, rRow1);
        _mm_store_pd(result + 2, rRow2);
    }

    static void appendTransformInPlace(double *lhs, const double *m) noexcept
    {
        // To append transform n to m we must perform m = n * m
        // Note the reversal of operands to apply the transform n
        // to m.

        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        Vec2D mRow1 = _mm_load_pd(m);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(m + 2);   // [ C D ]

        Vec2D nRow3 = _mm_load_pd(lhs + 4);   // [ e f ]

        // Calculate the translation terms (row 3 of the result).
        Vec2D colX = _mm_mul_pd(mRow1, nRow3);   // [ Ae Bf ]
        Vec2D colY = _mm_mul_pd(mRow2, nRow3);   // [ Ce Df ]

        Vec2D rowX = _mm_unpacklo_pd(colX, colY);   // [ Ae Ce ]
        Vec2D rowY = _mm_unpackhi_pd(colX, colY);   // [ Bf Df ]
        Vec2D rowXY = _mm_add_pd(rowX, rowY);   // [ (Ae + Bf) (Ce + Df) ]

        Vec2D mRow3 = _mm_load_pd(m + 4);   // [ E F ]
        Vec2D translation = _mm_add_pd(mRow3, rowXY); // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(lhs + 4, translation);

        // Now start working on rows 1 and 2 of the result.
        Vec2D A = _mm_unpacklo_pd(mRow1, mRow1);  // [ A A ]
        Vec2D B = _mm_unpackhi_pd(mRow1, mRow1);  // [ B B ]
        Vec2D C = _mm_unpacklo_pd(mRow2, mRow2);  // [ C C ]
        Vec2D D = _mm_unpackhi_pd(mRow2, mRow2);  // [ D D ]

        Vec2D nRow1 = _mm_load_pd(lhs);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(lhs + 2);   // [ c d ]

        Vec2D rRow1First = _mm_mul_pd(A, nRow1);    // [ Aa Ab ]
        Vec2D rRow1Second = _mm_mul_pd(B, nRow2);   // [ Bc Bd ]

        Vec2D rRow2First = _mm_mul_pd(C, nRow1);    // [ Ca Cb ]
        Vec2D rRow2Second = _mm_mul_pd(D, nRow2);   // [ Dc Dd ]

        Vec2D rRow1 = _mm_add_pd(rRow1First, rRow1Second);  // [ (Aa + Bc) (Ab + Bd) ]
        Vec2D rRow2 = _mm_add_pd(rRow2First, rRow2Second);  // [ (Ca + Dc) (Cb + Dd) ]

        _mm_store_pd(lhs, rRow1);
        _mm_store_pd(lhs + 2, rRow2);
    }
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
