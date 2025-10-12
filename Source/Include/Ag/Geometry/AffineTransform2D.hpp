//! @file Ag/Geometry/AffineTransform2D.hpp
//! @brief The declaration of an object representing a 2-dimensional affine
//! transformation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_AFFINE_TRANSFORM_2D_HPP__
#define __AG_GEOMETRY_AFFINE_TRANSFORM_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Matrix2x2.hpp"
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a 2-dimensional affine transformation.
class STRUCT_ALIGN_16 AffineTransform2D
{
public:
    // Construction/Destruction
    AffineTransform2D();
    AffineTransform2D(const Matrix2x2 &scale);
    AffineTransform2D(const Point2D &translation);
    AffineTransform2D(const Matrix2x2 &scale, const Point2D &translation);
    AffineTransform2D(const double *values);
    ~AffineTransform2D() = default;

    // Accessors
    const double *toArray() const noexcept;
    bool isIdentity() const noexcept;
    AffineTransform2D inverse() const;

    // Operations
    AffineTransform2D &makeIdentity();
    AffineTransform2D &makeScale(double scaleFactor);
    AffineTransform2D &makeScale(const Point2D &scaleFactor);
    AffineTransform2D &makeScale(double scaleFactorX, double scaleFactorY);
    AffineTransform2D &makeScale(const Point2D &scaleFactor, const Point2D &centre);
    AffineTransform2D &makeTranslation(double dX, double dY);
    AffineTransform2D &makeTranslation(const Point2D &rhs);
    AffineTransform2D &makeRotation(double angleInRadians);
    AffineTransform2D &makeRotation(double angleInRadians, const Point2D &centre);
    AffineTransform2D &appendScale(double scaleFactor);
    AffineTransform2D &appendScale(const Point2D &scaleFactor);
    AffineTransform2D &appendScale(double scaleX, double scaleY);
    AffineTransform2D &appendScale(const Point2D &scaleFactor, const Point2D &centre);
    AffineTransform2D &appendRotation(double angleInRadians);
    AffineTransform2D &appendRotation(double angleInRadians, const Point2D &centre);
    AffineTransform2D &appendTranslation(double dX, double dY);
    AffineTransform2D &appendTranslation(const Point2D &offset);
    Point2D operator*(const Point2D &rhs) const;
    AffineTransform2D operator*(const AffineTransform2D &rhs) const;
    AffineTransform2D &operator*=(const AffineTransform2D &rhs);
private:
    // Internal Fields
    double _m[8];
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
