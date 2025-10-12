//! @file Ag/Geometry/Matrix3x3.hpp
//! @brief The declaration of an object representing a 3x3 matrix with double
//! precision values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_MATRIX_3X3_HPP__
#define __AG_GEOMETRY_MATRIX_3X3_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a 3x3 matrix with double precision values.
class STRUCT_ALIGN_16 Matrix3x3
{
public:
    // Public Fields
    double M[9];

    // Construction/Destruction
    Matrix3x3();
    Matrix3x3(const double *m);
    ~Matrix3x3() = default;
    static Matrix3x3 scale(double uniformScale);
    static Matrix3x3 scaleXY(const Point2D &scale);
    static Matrix3x3 scaleXY(double scaleX, double scaleY);
    static Matrix3x3 rotationXY(double angleInRadians);
    static Matrix3x3 rotationXY(double angleInRadians, const Point2D &rotationCentre);
    static Matrix3x3 translationXY(double dX, double dY);
    static Matrix3x3 translationXY(const Point2D &delta);

    // Accessors
    bool isIdentity() const noexcept;
    Matrix3x3 inverse() const;

    // Operations
    void makeIdentity();
    void makeScale(double scaleFactor);
    void makeScaleXY(const Point2D &scaleFactor);
    void makeScaleXY(double scaleFactorX, double scaleFactorY);
    void makeRotationXY(double angleInRadians);
    void makeRotationXY(double angleInRadians, const Point2D &rotationCentre);
    void makeTranslationXY(double dX, double dY);
    void makeTranslationXY(const Point2D &delta);
    Point2D operator*(const Point2D &rhs) const;
    Matrix3x3 operator*(const Matrix3x3 &rhs) const;
    Matrix3x3 &operator*=(const Matrix3x3 &rhs);
private:
    // Internal Fields
    // Pad the structure to a 16-byte boundary.
    double _padding;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
