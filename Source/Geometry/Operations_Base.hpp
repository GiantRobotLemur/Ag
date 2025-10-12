//! @file Geometry/Operations_Base.hpp
//! @brief The declaration of basic implementations of operations which could
//! be accelerated by SIMD.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_OPRERATIONS_BASE_HPP__
#define __AG_GEOMETRY_OPRERATIONS_BASE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

#include <algorithm>

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Basic implementations of operations on pairs of double values which
//! could be accelerated by SIMD.
struct OperationsBase_Vec2D
{
    static constexpr size_t ElementCount = 2;

    static void setZero(double *rhs) noexcept
    {
        rhs[0] = rhs[1] = 0;
    }

    static void setOne(double *rhs) noexcept
    {
        rhs[0] = rhs[1] = 0;
    }

    static void copy(const double *lhs, double *rhs) noexcept
    {
        std::copy_n(lhs, ElementCount, rhs);
    }

    static bool isEqual(const double *lhs, const double *rhs) noexcept
    {
        return (lhs[0] == rhs[0]) && (lhs[1] == rhs[1]);
    }

    static bool isNotEqual(const double *lhs, const double *rhs) noexcept
    {
        return (lhs[0] != rhs[0]) || (lhs[1] != rhs[1]);
    }

    static void neg(const double *lhs, double *result) noexcept
    {
        result[0] = -lhs[0];
        result[1] = -lhs[1];
    }

    static void add(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = lhs[0] + rhs[0];
        result[1] = lhs[1] + rhs[1];
    }

    static void addAssign(double *lhs, const double *rhs) noexcept
    {
        lhs[0] += rhs[0];
        lhs[1] += rhs[1];
    }

    static void sub(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = lhs[0] - rhs[0];
        result[1] = lhs[1] - rhs[1];
    }

    static void subAssign(double *lhs, const double *rhs) noexcept
    {
        lhs[0] -= rhs[0];
        lhs[1] -= rhs[1];
    }

    static void mul(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = lhs[0] * rhs[0];
        result[1] = lhs[1] * rhs[1];
    }

    static void mulAssign(double *lhs, const double *rhs) noexcept
    {
        lhs[0] *= rhs[0];
        lhs[1] *= rhs[1];
    }

    static void scalarMul(const double *lhs, double rhs, double *result) noexcept
    {
        result[0] = lhs[0] * rhs;
        result[1] = lhs[1] * rhs;
    }

    static void scalarMulAssign(double *lhs, double rhs) noexcept
    {
        lhs[0] *= rhs;
        lhs[1] *= rhs;
    }

    static bool anyZero(const double *rhs) noexcept
    {
        return (rhs[0] * rhs[1]) == 0;
    }

    static bool allZero(const double *rhs) noexcept
    {
        return (rhs[0] == 0) && (rhs[1] == 0);
    }

    static void div(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = lhs[0] / rhs[0];
        result[1] = lhs[1] / rhs[1];
    }

    static void divAssign(double *lhs, const double *rhs) noexcept
    {
        lhs[0] /= rhs[0];
        lhs[1] /= rhs[1];
    }

    static void scalarDiv(const double *lhs, double rhs, double *result) noexcept
    {
        result[0] = lhs[0] / rhs;
        result[1] = lhs[1] / rhs;
    }

    static void scalarDivAssign(double *lhs, double rhs) noexcept
    {
        lhs[0] /= rhs;
        lhs[1] /= rhs;
    }

    static void min(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = std::min(lhs[0], rhs[0]);
        result[1] = std::min(lhs[1], rhs[1]);
    }

    static void max(const double *lhs, const double *rhs, double *result) noexcept
    {
        result[0] = std::max(lhs[0], rhs[0]);
        result[1] = std::max(lhs[1], rhs[1]);
    }

    static void minmax(const double *lhs, const double *rhs, double *result) noexcept
    {
        for (uint8_t i = 0; i < ElementCount; ++i)
        {
            auto resultPair = std::minmax(lhs[i], rhs[i]);

            result[i] = resultPair.first;
            result[i + ElementCount] = resultPair.second;
        }
    }

    static void clamp(const double *lhs, const double *minRhs,
                      const double *maxRhs, double *result) noexcept
    {
        result[0] = std::clamp(lhs[0], minRhs[0], maxRhs[0]);
        result[1] = std::clamp(lhs[1], minRhs[1], maxRhs[1]);
    }

    static void lerp(const double *lhs, const double *rhs, double scale, double *result) noexcept
    {
        double inverseScale = 1.0f - scale;

        result[0] = (lhs[0] * inverseScale) + (rhs[0] * scale);
        result[1] = (lhs[1] * inverseScale) + (rhs[1] * scale);
    }

    static void scalarFma(const double *lhs, double rhsScale,
                          const double *rhsOffset, double *result) noexcept
    {
        result[0] = std::fma(lhs[0], rhsScale, rhsOffset[0]);
        result[1] = std::fma(lhs[1], rhsScale, rhsOffset[1]);
    }

    static void fma(const double *lhs, const double *rhsScale,
                    const double *rhsOffset, double *result) noexcept
    {
        result[0] = std::fma(lhs[0], rhsScale[0], rhsOffset[0]);
        result[1] = std::fma(lhs[1], rhsScale[1], rhsOffset[1]);
    }

    static double magnitudeSq(const double *rhs) noexcept
    {
        return (rhs[0] * rhs[0]) + (rhs[1] * rhs[1]);
    }

    static double dot(const double *lhs, const double *rhs) noexcept
    {
        return (lhs[0] * rhs[0]) + (lhs[1] * rhs[1]);
    }

    static double det(const double *lhs, const double *rhs) noexcept
    {
        return (lhs[0] * rhs[1]) - (lhs[1] * rhs[0]);
    }

    static double distance(const double *lhs, const double *rhs) noexcept
    {
        double dX = rhs[0] - lhs[0];
        double dY = rhs[1] - lhs[1];

        return std::sqrt((dX * dX) + (dY * dY));
    }

    static bool tryNormalise(const double *rhs, double *result) noexcept
    {
        double magSq = (rhs[0] * rhs[0]) + (rhs[1] * rhs[1]);

        if (magSq == 0)
        {
            return false;
        }
        else
        {
            double mag = std::sqrt(magSq);
            result[0] = rhs[0] / mag;
            result[1] = rhs[1] / mag;

            return true;
        }
    }
};

//! @brief Basic implementations of operations on matrices of two by two double
//! values which could be accelerated by SIMD.
struct OperationsBase_Mat2x2D
{
    static constexpr size_t ElementCount = 4;

    static void copy(const double *src, double *dest) noexcept
    {
        std::copy_n(src, ElementCount, dest);
    }

    static void makeIdentity(double *result) noexcept
    {
        result[0] = 1;
        result[1] = 0;
        result[2] = 0;
        result[3] = 1;
    }

    static bool isIdentity(const double *m) noexcept
    {
        return (m[0] == 1) && (m[1] == 0) && (m[2] == 0) && (m[3] == 1);
    }

    static void makeUniformScale(double scale, double *m) noexcept
    {
        m[0] = scale;
        m[1] = m[2] = 0;
        m[3] = scale;
    }

    static void makeScale(const double *scale, double *m) noexcept
    {
        m[0] = scale[0];
        m[1] = m[2] = 0;
        m[3] = scale[1];
    }

    static void makeRotation(double angleInRadians, double *m) noexcept
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        m[0] = cosAngle;
        m[1] = -sinAngle;
        m[2] = sinAngle;
        m[3] = cosAngle;
    }

    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        double det = (m[0] * m[3]) - (m[1] * m[2]);

        if (det == 0.0)
            return false;

        // Divide all matrix components by the calculated determinant in the
        // following order: [ ( D / determinant) (-B / determinant) ]
        //                  [ (-C / determinant) ( A / determinant) ]

        inverse[0] = m[3] / det;
        inverse[1] = -m[1] / det;
        inverse[2] = -m[2] / det;
        inverse[3] = m[0] / det;

        return true;
    }

    static void multiplyPoint2D(const double *m, const double *pt, double *result) noexcept
    {
        // [ A B   * [ x y ] = [ (Ax + By) (Cx + Dy) ]
        //   C D ]

        result[0] = (m[0] * pt[0]) + (m[1] * pt[1]);
        result[1] = (m[2] * pt[0]) + (m[3] * pt[1]);
    }

    static void multiply(const double *m, const double *n, double *result) noexcept
    {
        result[0] = (m[0] * n[0]) + (m[1] * n[2]);
        result[1] = (m[0] * n[1]) + (m[1] * n[3]);
        result[2] = (m[2] * n[0]) + (m[3] * n[2]);
        result[3] = (m[2] * n[1]) + (m[3] * n[3]);
    }

    static void multiplyInPlace(double *lhs, const double *n) noexcept
    {
        double m[ElementCount];
        std::copy_n(lhs, ElementCount, m);

        lhs[0] = (m[0] * n[0]) + (m[1] * n[2]);
        lhs[1] = (m[0] * n[1]) + (m[1] * n[3]);
        lhs[2] = (m[2] * n[0]) + (m[3] * n[2]);
        lhs[3] = (m[2] * n[1]) + (m[3] * n[3]);
    }
};

//! @brief Basic implementations of operations on matrices of three by three
//! double values which could be accelerated by SIMD.
struct OperationsBase_Mat3x3D
{
    static constexpr size_t ElementCount = 9;

    static void copy(const double *src, double *dest) noexcept
    {
        std::copy_n(src, ElementCount, dest);
    }

    static void makeIdentity(double *m) noexcept
    {
        m[0] = 1.0;
        m[1] = m[2] = m[3] = 0.0;
        m[4] = 1.0;
        m[5] = m[6] = m[7] = 0.0;
        m[8] = 1.0;
    }

    static bool isIdentity(const double *m) noexcept
    {
        return (m[0] == 1.0) &&
            (m[1] == 0.0) &&
            (m[2] == 0.0) &&
            (m[3] == 0.0) &&
            (m[4] == 1.0) &&
            (m[5] == 0.0) &&
            (m[6] == 0.0) &&
            (m[7] == 0.0) &&
            (m[8] == 1.0);
    }

    static void makeUniformScale(double scale, double *m) noexcept
    {
        m[0] = m[4] = m[8] = scale;
        m[1] = m[2] = m[3] = 0.0;
        m[5] = m[6] = m[7] = 0.0;
    }

    static void makeScaleXY(const double *scale, double *m) noexcept
    {
        m[0] = scale[0];
        m[1] = m[2] = m[3] = 0.0;
        m[4] = scale[1];
        m[5] = m[6] = m[7] = 0.0;
        m[8] = 1;
    }

    static void makeTranslationXY(const double *offsets, double *m) noexcept
    {
        m[0] = 1;
        m[1] = 0;
        m[2] = offsets[0];
        m[3] = 0.0;
        m[4] = 1;
        m[5] = offsets[1];
        m[6] = m[7] = 0.0;
        m[8] = 1;
    }

    static void makeRotationXY(double angleInRadians, double *m) noexcept
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        m[0] = cosAngle;
        m[1] = -sinAngle;
        m[2] = 0.0;
        m[3] = sinAngle;
        m[4] = cosAngle;
        m[5] = m[6] = m[7] = 0.0;
        m[8] = 1;
    }

    static void makeRotationXY(double angleInRadians, const double *centre,
                               double *m) noexcept
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        double reverseCos = 1.0 - cosAngle;
        double tX = (centre[0] * reverseCos) + (centre[1] * sinAngle);
        double tY = (centre[0] * -sinAngle) + (centre[1] * reverseCos);

        m[0] = cosAngle;
        m[1] = -sinAngle;
        m[2] = tX;
        m[3] = sinAngle;
        m[4] = cosAngle;
        m[5] = tY;
        m[6] = m[7] = 0.0;
        m[8] = 1;
    }

    static bool tryCalculateInverse(const double *m, double *inverse) noexcept
    {
        // Overall formula here: https://ardoris.wordpress.com/2008/07/18/general-formula-for-the-inverse-of-a-3x3-matrix/
        // [ a b c
        //   d e f
        //   g h i ]

        const double &a = m[0];
        const double &b = m[1];
        const double &c = m[2];
        const double &d = m[3];
        const double &e = m[4];
        const double &f = m[5];
        const double &g = m[6];
        const double &h = m[7];
        const double &i = m[8];

        // Determinant = a(ei-fh) - b(di-fg) + c(dh-eg)
        double eiMinusFh = (e * i) - (f * h);
        double dhMinusEg = (d * h) - (e * g);

        double det = (a * eiMinusFh) -
            (b * ((d * i) - (f * g))) +
            (c * dhMinusEg);

        if (det == 0.0)
            return false;

        // Inverse = 1/det * [ (ei-fh) (ch-bi) (bf-ce)
        //                     (fg-di) (ai-cg) (cd-af)
        //                     (dh-eg) (bg-ah) (ea-bd) ]

        // Row 1
        inverse[0] = eiMinusFh / det;
        inverse[1] = ((c * h) - (b * i)) / det;
        inverse[2] = ((b * f) - (c * e)) / det;

        // Row 2
        inverse[3] = ((f * g) - (d * i)) / det;
        inverse[4] = ((a * i) - (c * g)) / det;
        inverse[5] = ((c * d) - (a * f)) / det;

        // Row 3
        inverse[6] = ((d * h) - (e * g)) / det;
        inverse[7] = ((b * g) - (a * h)) / det;
        inverse[8] = ((e * a) - (b * d)) / det;

        return true;
    }

    static void multiplyPoint2D(const double *m, const double *pt, double *result) noexcept
    {
        // [ A B C    *   [ x    =  [ (Ax + By + C)
        //   D E F          y         (Dx + Ey + F)
        //   G H I ]        1 ]       (Gx + Hy + I) ]

        result[0] = (m[0] * pt[0]) + (m[1] * pt[1]) + m[2];
        result[1] = (m[3] * pt[0]) + (m[4] * pt[1]) + m[5];
    }

    static void multiply(const double *m, const double *n, double *result) noexcept
    {
        // [ A B C    *   [ a b c    =  [ (Aa + Bd + Cg) (Ab + Be + Ch) (Ac + Bf + Ci)
        //   D E F          d e f         (Da + Ed + Fg) (Db + Ee + Fh) (Dc + Ef + Fi)
        //   G H I ]        g h i ]       (Ga + Hd + Ig) (Gb + He + Ih) (Gc + Hf + Ii) ]

        // Row 1
        result[0] = (m[0] * n[0]) + (m[1] * n[3]) + (m[2] * n[6]);
        result[1] = (m[0] * n[1]) + (m[1] * n[4]) + (m[2] * n[7]);
        result[2] = (m[0] * n[2]) + (m[1] * n[5]) + (m[2] * n[8]);

        // Row 2
        result[3] = (m[3] * n[0]) + (m[4] * n[3]) + (m[5] * n[6]);
        result[4] = (m[3] * n[1]) + (m[4] * n[4]) + (m[5] * n[7]);
        result[5] = (m[3] * n[2]) + (m[4] * n[5]) + (m[5] * n[8]);

        // Row 3
        result[6] = (m[6] * n[0]) + (m[7] * n[3]) + (m[8] * n[6]);
        result[7] = (m[6] * n[1]) + (m[7] * n[4]) + (m[8] * n[7]);
        result[8] = (m[6] * n[2]) + (m[7] * n[5]) + (m[8] * n[8]);
    }

    static void multiplyInPlace(double *lhs, const double *n) noexcept
    {
        double m[ElementCount];
        std::copy_n(lhs, ElementCount, m);

        multiply(m, n, lhs);
    }
};

//! @brief Basic implementations of operations on a 2D affine transform
//! represented by double values which could be accelerated by SIMD.
struct OperationsBase_AffineTrans2D
{
    static constexpr size_t ElementCount = 6;

    struct Transform
    {
        double Matrix[4];
        double Translation[2];
    };

    static void copy(const double *src, double *dest) noexcept
    {
        std::copy_n(src, ElementCount, dest);
    }

    static void makeIdentity(double *dest) noexcept
    {
        dest[0] = 1;
        dest[1] = dest[2] = 0;
        dest[3] = 1;
        dest[4] = dest[5] = 0;
    }

    static bool isIdentity(const double *lhs) noexcept
    {
        return (lhs[0] == 1) && (lhs[1] == 0) &&
            (lhs[2] == 0) && (lhs[3] == 1) &&
            (lhs[4] == 0) && (lhs[5] == 0);
    }

    static void makeUniformScale(double scale, double *dest) noexcept
    {
        dest[0] = scale;
        dest[1] = dest[2] = 0;
        dest[3] = scale;
        dest[4] = dest[5] = 0;
    }

    static void makeScale(const double *scale, double *dest) noexcept
    {
        dest[0] = scale[0];
        dest[1] = dest[2] = 0;
        dest[3] = scale[1];
        dest[4] = dest[5] = 0;
    }

    static void makeTranslation(const double *offsets, double *dest) noexcept
    {
        dest[0] = 1;
        dest[1] = dest[2] = 0;
        dest[3] = 1;
        dest[4] = offsets[0];
        dest[5] = offsets[1];
    }

    static void makeRotation(double angleInRadians, double *dest) noexcept
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        dest[0] = cosAngle;
        dest[1] = -sinAngle;
        dest[2] = sinAngle;
        dest[3] = cosAngle;
        dest[4] = dest[5] = 0;
    }

    static bool tryCalculateInverse(const double *m, double *result) noexcept
    {
        // [ A B   -1 =   [     D        -B
        //   C D        1      -C         A
        //   ---        /   -------------------
        //   E F ]     det  (BF - ED) (EC - AF) ]

        // det = (AD - BC)

        double det = (m[0] * m[3]) - (m[1] * m[2]);

        if (det == 0)
            return false;

        double detReciprocal = 1.0 / det;

        result[0] =  m[3] * detReciprocal;
        result[1] = -m[1] * detReciprocal;
        result[2] = -m[2] * detReciprocal;
        result[3] =  m[0] * detReciprocal;
        result[4] = ((m[1] * m[5]) - (m[4] * m[3])) * detReciprocal;
        result[5] = ((m[4] * m[2]) - (m[0] * m[5])) * detReciprocal;

        return true;
    }

    static void multiplyPoint2D(const double *m, const double *pt, double *result)
    {
        // [ A B   * [ x   = [ Ax + By + E
        //   C D       y       Cx + Dy + F
        //   ---       -       -----------
        //   E F ]     1 ]           1     ]

        result[0] = (m[0] * pt[0]) + (m[1] * pt[1]) + m[4];
        result[1] = (m[2] * pt[0]) + (m[3] * pt[1]) + m[5];
    }

    static void multiply(const double *m, const double *n,
                         double *result) noexcept
    {
        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        result[0] = (m[0] * n[0]) + (m[1] * n[2]);
        result[1] = (m[0] * n[1]) + (m[1] * n[3]);
        result[2] = (m[2] * n[0]) + (m[3] * n[2]);
        result[3] = (m[2] * n[1]) + (m[3] * n[3]);
        result[4] = (m[0] * n[4]) + (m[1] * n[5]) + m[4];
        result[5] = (m[2] * n[4]) + (m[3] * n[5]) + m[5];
    }

    static void multiplyInPlace(double *result, const double *n) noexcept
    {
        double m[ElementCount];
        std::copy_n(result, ElementCount, m);

        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        result[0] = (m[0] * n[0]) + (m[1] * n[2]);
        result[1] = (m[0] * n[1]) + (m[1] * n[3]);
        result[2] = (m[2] * n[0]) + (m[3] * n[2]);
        result[3] = (m[2] * n[1]) + (m[3] * n[3]);
        result[4] = (m[0] * n[4]) + (m[1] * n[5]) + m[4];
        result[5] = (m[2] * n[4]) + (m[3] * n[5]) + m[5];
    }

    static void appendTransformInPlace(double *lhs, const double *m) noexcept
    {
        // To append transform n to m we must perform m = n * m
        // Note the reversal of operands to apply the transform n
        // to m.
        double n[ElementCount];
        std::copy_n(lhs, ElementCount, n);

        // [ A B   * [ a b   = [ (Aa + Bc)     (Ab + Bd)
        //   C D       c d       (Ca + Dc)     (Cb + Dd)
        //   ---       ---       -------------------
        //   E F ]     e f ]     (Ae + Bf + E) (Ce + Df + F) ]

        lhs[0] = (m[0] * n[0]) + (m[1] * n[2]);
        lhs[1] = (m[0] * n[1]) + (m[1] * n[3]);
        lhs[2] = (m[2] * n[0]) + (m[3] * n[2]);
        lhs[3] = (m[2] * n[1]) + (m[3] * n[3]);
        lhs[4] = (m[0] * n[4]) + (m[1] * n[5]) + m[4];
        lhs[5] = (m[2] * n[4]) + (m[3] * n[5]) + m[5];
    }
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
