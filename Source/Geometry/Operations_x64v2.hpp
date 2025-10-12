//! @file Geometry/Operations_x64v2.hpp
//! @brief The declaration of basic implementations of operations 
//! accelerated by SSE 4.1/4.2 SIMD instructions available to the v2 x86-64
//! processor architecture.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_OPERATIONS_SSE4_HPP__
#define __AG_GEOMETRY_OPERATIONS_SSE4_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Operations_x64v1.hpp"

namespace Ag {
namespace Geom {


////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Basic implementations of operations on pairs of double values
//! accelerated by SSE 4.1/4.2 operations.
struct OperationsX64v2_Vec2D : public OperationsX64v1_Vec2D
{
    //! @brief The constant required by the _mm_dp_pd() intrinsic to store the
    //! result in the low element of the vector.
    static constexpr int DotProdLow = 0x31;

    //! @brief The constant required by the _mm_dp_pd() intrinsic to store the
    //! result in the both elements of the vector.
    static constexpr int DotProdBoth = 0x33;

    static double magnitudeSq(const double *rhs) noexcept
    {
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D result = _mm_dp_pd(rhsVec, rhsVec, DotProdLow);

        return result.m128d_f64[0];
    }

    static double dot(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D result = _mm_dp_pd(lhsVec, rhsVec, DotProdLow);

        return result.m128d_f64[0];
    }

    static double det(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);    // [ Lx Ly ]
        Vec2D rhsVec = _mm_loadr_pd(rhs);   // [ Ry Rx ]
        Vec2D minusOne = _mm_set_pd(-1, 1); // [ 1 -1 ]
        Vec2D revRhs = _mm_mul_pd(rhsVec, minusOne);    // [ Ry (-1 * Rx) ]

        Vec2D result = _mm_dp_pd(lhsVec, revRhs, DotProdLow);   // [ (Lx * Ry) - (Ly * Rx) ]

        return result.m128d_f64[0];
    }

    static double distance(const double *lhs, const double *rhs) noexcept
    {
        Vec2D lhsVec = _mm_load_pd(lhs);
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D delta = _mm_sub_pd(rhsVec, lhsVec);
        Vec2D magSq = _mm_dp_pd(delta, delta, DotProdLow);

        Vec2D mag = _mm_sqrt_sd(_mm_setzero_pd(), magSq);

        return mag.m128d_f64[0];
    }

    static bool tryNormalise(const double *rhs, double *result) noexcept
    {
        Vec2D rhsVec = _mm_load_pd(rhs);
        Vec2D magSq = _mm_dp_pd(rhsVec, rhsVec, DotProdBoth); // [ ((rhsX * rhsX) + (rhsY * rhsY)) ((rhsX * rhsX) + (rhsY * rhsY)) ]
        Vec2D zero = _mm_setzero_pd(); // [ 0 0 ]
        Vec2D isZero = _mm_cmpeq_sd(zero, magSq);
        int cmpResult = _mm_movemask_pd(isZero);

        if (cmpResult)
        {
            return false;
        }
        else
        {
            Vec2D magnitudeVec = _mm_sqrt_pd(magSq); // [ sqrt(magSq) sqrt(magSq) ]
            Vec2D unitVec = _mm_div_pd(rhsVec, magnitudeVec); // [ (rhsX / sqrt(magSq)) (rhsY / sqrt(magSq)) ]
            _mm_store_pd(result, unitVec);

            return true;
        }
    }
};

//! @brief Basic implementations of operations on matrices of two by two double
//! values which could be accelerated by SIMD.
struct OperationsX64v2_Mat2x2D : public OperationsX64v1_Mat2x2D
{
    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        // m = [ A B
        //       C D ]
        // 
        // Calculate the determinant (AD - BC)
        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };

        Vec2D row1 = _mm_load_pd(m);            // [ A B ]
        Vec2D row2Rev = _mm_loadr_pd(m + 2);    // [ D C ]
        Vec2D oneMinusOneVec = _mm_load_pd(oneMinusOne);

        Vec2D row1Factors = _mm_mul_pd(row1, oneMinusOneVec);   // [ A -B ]
        Vec2D det = _mm_dp_pd(row1Factors, row2Rev, 0x33); // [ (AD - BC) (AD - BC) ]

        int isZero = _mm_movemask_pd(_mm_cmpeq_pd(det, _mm_setzero_pd()));

        if (isZero)
            return false;

        // Divide all matrix components by the calculated determinant in the
        // following order: [ ( D / determinant) (-B / determinant) ]
        //                  [ (-C / determinant) ( A / determinant) ]

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

        Vec2D xResult = _mm_dp_pd(row1, ptVec, 0x31); // [ (Ax + By) 0 ]
        Vec2D yResult = _mm_dp_pd(row2, ptVec, 0x31); // [ (Cx + Dy) 0 ]

        Vec2D transformed = _mm_unpacklo_pd(xResult, yResult); // [ (Ax + By) (Cx + Dy) ]

        _mm_store_pd(result, transformed);
    }

    static void multiply(const double *m, const double *n, double *result) noexcept
    {
        // [ A B   * [ a b   =  [ (Aa + Bc) (Ab + Bd)
        //   C D ]     c d ]      (Ca + Dc) (Cb + Dd) ]

        // Transpose n.
        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]
        Vec2D nCol1 = _mm_unpacklo_pd(nRow1, nRow2);    // [ a c ]
        Vec2D nCol2 = _mm_unpackhi_pd(nRow1, nRow2);    // [ b d ]

        Vec2D mRow1 = _mm_load_pd(m);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(m + 2);   // [ C D ]

        Vec2D rRow1First = _mm_dp_pd(mRow1, nCol1, 0x31);   // [ (Aa + Bc) 0 ]
        Vec2D rRow1Second = _mm_dp_pd(mRow1, nCol2, 0x31);  // [ (Ab + Bd) 0 ]
        Vec2D rRow1 = _mm_unpacklo_pd(rRow1First,
                                      rRow1Second);         // [ (Aa + Bc) (Ab + Bd) ]

        Vec2D rRow2First = _mm_dp_pd(mRow2, nCol1, 0x31);   // [ (Ca + Dc) 0 ]
        Vec2D rRow2Second = _mm_dp_pd(mRow2, nCol2, 0x31);  // [ (Cb + Dd) 0 ]
        Vec2D rRow2 = _mm_unpacklo_pd(rRow2First,
                                      rRow2Second);         // [ (Ca + Dc) (Cb +Dd) ]

        _mm_store_pd(result, rRow1);
        _mm_store_pd(result + 2, rRow2);
    }

    static void multiplyInPlace(double *lhs, const double *n) noexcept
    {
        // [ A B   * [ a b   =  [ (Aa + Bc) (Ab + Bd)
        //   C D ]     c d ]      (Ca + Dc) (Cb + Dd) ]

        // Transpose n.
        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]
        Vec2D nCol1 = _mm_unpacklo_pd(nRow1, nRow2);    // [ a c ]
        Vec2D nCol2 = _mm_unpackhi_pd(nRow1, nRow2);    // [ b d ]

        Vec2D mRow1 = _mm_load_pd(lhs);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(lhs + 2);   // [ C D ]

        Vec2D rRow1First = _mm_dp_pd(mRow1, nCol1, 0x31);   // [ (Aa + Bc) 0 ]
        Vec2D rRow1Second = _mm_dp_pd(mRow1, nCol2, 0x31);  // [ (Ab + Bd) 0 ]
        Vec2D rRow1 = _mm_unpacklo_pd(rRow1First,
                                      rRow1Second);         // [ (Aa + Bc) (Ab + Bd) ]

        Vec2D rRow2First = _mm_dp_pd(mRow2, nCol1, 0x31);   // [ (Ca + Dc) 0 ]
        Vec2D rRow2Second = _mm_dp_pd(mRow2, nCol2, 0x31);  // [ (Cb + Dd) 0 ]
        Vec2D rRow2 = _mm_unpacklo_pd(rRow2First,
                                      rRow2Second);         // [ (Ca + Dc) (Cb +Dd) ]

        _mm_store_pd(lhs, rRow1);
        _mm_store_pd(lhs + 2, rRow2);
    }
};

//! @brief Implementations of operations on a 2D affine transforms
//! represented by 6 double values accelerated by SSE 4.
struct OperationsX64v2_AffineTrans2D : public OperationsX64v1_AffineTrans2D
{
    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        // [ A B   -1 =   [     D        -B
        //   C D        1      -C         A
        //   ---        /   -------------------
        //   E F ]     det  (BF - DE) (CE - AF) ]


        static const double STRUCT_ALIGN_16 oneMinusOne[] = { 1, -1 };

        Vec2D row1 = _mm_load_pd(m);            // [ A B ]
        Vec2D row2Rev = _mm_loadr_pd(m + 2);    // [ D C ]
        Vec2D oneMinusOneVec = _mm_load_pd(oneMinusOne);

        Vec2D row1Factors = _mm_mul_pd(row1, oneMinusOneVec);   // [ A -B ]
        Vec2D det = _mm_dp_pd(row1Factors, row2Rev, 0x33); // [ (AD - BC) (AD - BC) ]

        int isZero = _mm_movemask_pd(_mm_cmpeq_pd(det, _mm_setzero_pd()));

        if (isZero)
            return false;

        Vec2D row1Mod = _mm_div_pd(_mm_mul_pd(row1, oneMinusOneVec), det); // 1/det [ A -B ]
        Vec2D row2RevMod = _mm_div_pd(_mm_mul_pd(row2Rev, oneMinusOneVec), det); // 1/det [ D -C ]

        Vec2D invRow1 = _mm_shuffle_pd(row2RevMod, row1Mod, 2); // 1/det [  D -B ]
        Vec2D invRow2 = _mm_shuffle_pd(row2RevMod, row1Mod, 1); // 1/det [ -C  A ]

        _mm_store_pd(inverse, invRow1);
        _mm_store_pd(inverse + 2, invRow2);

        Vec2D row3 = _mm_load_pd(m + 4);                // [ E F ]
        Vec2D col1 = _mm_unpacklo_pd(row2Rev, row1);    // [ D A ]
        Vec2D temp1 = _mm_mul_pd(col1, row3);           // [ DE AF ]

        Vec2D row3Rev = _mm_shuffle_pd(row3, row3, 1);  // [ F E ]
        Vec2D col2 = _mm_unpackhi_pd(row1, row2Rev);    // [ B C ]

        Vec2D temp2 = _mm_mul_pd(row3Rev, col2);        // [ BF CE ]

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

        Vec2D scaledX = _mm_dp_pd(row1, ptVec, 0x31);       // [ (Ax + By) 0 ]
        Vec2D scaledY = _mm_dp_pd(row2, ptVec, 0x31);       // [ (Cx + Dy) 0 ]
        Vec2D scaled = _mm_unpacklo_pd(scaledX, scaledY);   // [ (Ax + By) (Cx + Dy) ]
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
        Vec2D mRow3 = _mm_load_pd(m + 4);   // [ E F ]

        Vec2D nRow3 = _mm_load_pd(n + 4);   // [ e f ]

        Vec2D scaledX = _mm_dp_pd(mRow1, nRow3, 0x31);      // [ (Ae + Bf) 0 ]
        Vec2D scaledY = _mm_dp_pd(mRow2, nRow3, 0x31);      // [ (Ce + Df) 0 ]
        Vec2D scaled = _mm_unpacklo_pd(scaledX, scaledY);   // [ (Ae + Bf) (Ce + Df) ]
        Vec2D translation = _mm_add_pd(scaled, mRow3);      // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(result + 4, translation);

        // Transpose n.
        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]
        Vec2D nCol1 = _mm_unpacklo_pd(nRow1, nRow2);    // [ a c ]
        Vec2D nCol2 = _mm_unpackhi_pd(nRow1, nRow2);    // [ b d ]

        Vec2D rRow1First = _mm_dp_pd(mRow1, nCol1, 0x31);   // [ (Aa + Bc) 0 ]
        Vec2D rRow1Second = _mm_dp_pd(mRow1, nCol2, 0x31);  // [ (Ab + Bd) 0 ]
        Vec2D rRow1 = _mm_unpacklo_pd(rRow1First,
                                      rRow1Second);         // [ (Aa + Bc) (Ab + Bd) ]

        Vec2D rRow2First = _mm_dp_pd(mRow2, nCol1, 0x31);   // [ (Ca + Dc) 0 ]
        Vec2D rRow2Second = _mm_dp_pd(mRow2, nCol2, 0x31);  // [ (Cb + Dd) 0 ]
        Vec2D rRow2 = _mm_unpacklo_pd(rRow2First,
                                      rRow2Second);         // [ (Ca + Dc) (Cb +Dd) ]

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
        Vec2D mRow3 = _mm_load_pd(result + 4);   // [ E F ]

        Vec2D nRow3 = _mm_load_pd(n + 4);   // [ e f ]

        Vec2D scaledX = _mm_dp_pd(mRow1, nRow3, 0x31);      // [ (Ae + Bf) 0 ]
        Vec2D scaledY = _mm_dp_pd(mRow2, nRow3, 0x31);      // [ (Ce + Df) 0 ]
        Vec2D scaled = _mm_unpacklo_pd(scaledX, scaledY);   // [ (Ae + Bf) (Ce + Df) ]
        Vec2D translation = _mm_add_pd(scaled, mRow3);      // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(result + 4, translation);

        // Transpose n.
        Vec2D nRow1 = _mm_load_pd(n);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(n + 2);   // [ c d ]
        Vec2D nCol1 = _mm_unpacklo_pd(nRow1, nRow2);    // [ a c ]
        Vec2D nCol2 = _mm_unpackhi_pd(nRow1, nRow2);    // [ b d ]

        Vec2D rRow1First = _mm_dp_pd(mRow1, nCol1, 0x31);   // [ (Aa + Bc) 0 ]
        Vec2D rRow1Second = _mm_dp_pd(mRow1, nCol2, 0x31);  // [ (Ab + Bd) 0 ]
        Vec2D rRow1 = _mm_unpacklo_pd(rRow1First,
                                      rRow1Second);         // [ (Aa + Bc) (Ab + Bd) ]

        Vec2D rRow2First = _mm_dp_pd(mRow2, nCol1, 0x31);   // [ (Ca + Dc) 0 ]
        Vec2D rRow2Second = _mm_dp_pd(mRow2, nCol2, 0x31);  // [ (Cb + Dd) 0 ]
        Vec2D rRow2 = _mm_unpacklo_pd(rRow2First,
                                      rRow2Second);         // [ (Ca + Dc) (Cb +Dd) ]

        _mm_store_pd(result, rRow1);
        _mm_store_pd(result + 2, rRow2);
    }

    static void appendTransformInPlace(double *lhs, const double *m) noexcept
    {
        // To append transform n to m we must perform m = n * m
        // Note the reversal of operands to apply the transform n
        // to m.
        // 
        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        Vec2D mRow1 = _mm_load_pd(m);       // [ A B ]
        Vec2D mRow2 = _mm_load_pd(m + 2);   // [ C D ]
        Vec2D mRow3 = _mm_load_pd(m + 4);   // [ E F ]

        Vec2D nRow3 = _mm_load_pd(lhs + 4);   // [ e f ]

        Vec2D scaledX = _mm_dp_pd(mRow1, nRow3, 0x31);      // [ (Ae + Bf) 0 ]
        Vec2D scaledY = _mm_dp_pd(mRow2, nRow3, 0x31);      // [ (Ce + Df) 0 ]
        Vec2D scaled = _mm_unpacklo_pd(scaledX, scaledY);   // [ (Ae + Bf) (Ce + Df) ]
        Vec2D translation = _mm_add_pd(scaled, mRow3);      // [ (Ae + Bf + E) (Ce + Df + F) ]
        _mm_store_pd(lhs + 4, translation);

        // Transpose n.
        Vec2D nRow1 = _mm_load_pd(lhs);       // [ a b ]
        Vec2D nRow2 = _mm_load_pd(lhs + 2);   // [ c d ]
        Vec2D nCol1 = _mm_unpacklo_pd(nRow1, nRow2);    // [ a c ]
        Vec2D nCol2 = _mm_unpackhi_pd(nRow1, nRow2);    // [ b d ]

        Vec2D rRow1First = _mm_dp_pd(mRow1, nCol1, 0x31);   // [ (Aa + Bc) 0 ]
        Vec2D rRow1Second = _mm_dp_pd(mRow1, nCol2, 0x31);  // [ (Ab + Bd) 0 ]
        Vec2D rRow1 = _mm_unpacklo_pd(rRow1First,
                                      rRow1Second);         // [ (Aa + Bc) (Ab + Bd) ]

        Vec2D rRow2First = _mm_dp_pd(mRow2, nCol1, 0x31);   // [ (Ca + Dc) 0 ]
        Vec2D rRow2Second = _mm_dp_pd(mRow2, nCol2, 0x31);  // [ (Cb + Dd) 0 ]
        Vec2D rRow2 = _mm_unpacklo_pd(rRow2First,
                                      rRow2Second);         // [ (Ca + Dc) (Cb +Dd) ]

        _mm_store_pd(lhs, rRow1);
        _mm_store_pd(lhs + 2, rRow2);
    }
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
