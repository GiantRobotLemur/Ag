//! @file Ag/Geometry/Matrix2x2.hpp
//! @brief The declaration of an object representing a 2x2 matrix with double
//! precision values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_MATRIX_2X2_HPP__
#define __AG_GEOMETRY_MATRIX_2X2_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a 2x2 matrix with double precision values.
class STRUCT_ALIGN_16 Matrix2x2
{
public:
    // Public Fields
    double M[4];

    // Construction/Destruction
    Matrix2x2();
    Matrix2x2(const double *m);
    ~Matrix2x2() = default;

    static Matrix2x2 scale(double uniformScale);
    static Matrix2x2 scale(const Point2D &scale);
    static Matrix2x2 scale(double scaleX, double scaleY);
    static Matrix2x2 rotation(double angleInRadians);

    // Accessors
    bool isIdentity() const noexcept;
    Matrix2x2 inverse() const;

    // Operations
    void makeIdentity();
    void makeScale(double scaleFactor);
    void makeScale(const Point2D &scaleFactor);
    void makeScale(double scaleFactorX, double scaleFactorY);
    void makeRotation(double angleInRadians);
    Point2D operator*(const Point2D &rhs) const;
    Matrix2x2 operator*(const Matrix2x2 &rhs) const;
    Matrix2x2 &operator*=(const Matrix2x2 &rhs);
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
