//! @file Geometry/Matrix2x2.cpp
//! @brief The definition of an object representing a 2x2 matrix with double
//! precision values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "Ag/Geometry/Matrix2x2.hpp"
#include "Operations.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Matrix2x2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Initialises the object to an identity matrix.
Matrix2x2::Matrix2x2()
{
    Operations_Mat2x2D::makeIdentity(M);
}

//! @brief Creates a 2x2 matrix initialised with arbitrary values.
//! @param[in] m A matrix of 4 values to initialise the matrix with.
Matrix2x2::Matrix2x2(const double *m)
{
    Operations_Mat2x2D::copy(m, M);
}

//! @brief Constructs a 2x2 matrix which defines a uniform scale transformation
//! in the X and Y axis.
//! @param[in] uniformScale The scale factor to apply to both axes.
//! @return A newly constructed matrix.
Matrix2x2 Matrix2x2::scale(double uniformScale)
{
    double m[4];

    Operations_Mat2x2D::makeUniformScale(uniformScale, m);

    return { m };
}

//! @brief Constructs a 2x2 matrix which defines a scale transformation.
//! @param[in] scale A 2D vector defining the scale factors.
//! @return A newly constructed matrix.
Matrix2x2 Matrix2x2::scale(const Point2D &scale)
{
    double m[4];

    Operations_Mat2x2D::makeScale(scale.toArray(), m);

    return { m };
}

//! @brief Constructs a 2x2 matrix which defines a scale transformation.
//! @param[in] scaleX The scale factor to apply to the X axis.
//! @param[in] scaleY The scale factor to apply to the Y axis.
//! @return A newly constructed matrix.
Matrix2x2 Matrix2x2::scale(double scaleX, double scaleY)
{
    double m[4];
    double scale[] = { scaleX, scaleY };

    Operations_Mat2x2D::makeScale(scale, m);

    return { m };
}

//! @brief Constructs a 2x2 matrix which defines a rotation transformation.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @return A newly constructed matrix.
Matrix2x2 Matrix2x2::rotation(double angleInRadians)
{
    double m[4];

    Operations_Mat2x2D::makeRotation(angleInRadians, m);

    return Matrix2x2(m);
}

//! @brief Determines if the matrix is set to the identity value.
//! @retval true The matrix is set to the identity value.
//! @retval false At least one component differs from the identity matrix.
bool Matrix2x2::isIdentity() const noexcept
{
    return Operations_Mat2x2D::isIdentity(M);
}

//! @brief Calculates the inverse of the matrix transformation.
//! @return A new matrix which represents the inverse of the current matrix.
//! @throws DivisionByZeroException If the matrix is singular, i.e. the
//! determinant is zero.
Matrix2x2 Matrix2x2::inverse() const
{
    double m[4];

    if (Operations_Mat2x2D::tryCalculateInverse(M, m))
    {
        return { m };
    }

    throw DivisionByZeroException("Creating an inverse 2x2 matrix");
}

//! @brief Reinitialises the object to an identity matrix.
void Matrix2x2::makeIdentity()
{
    Operations_Mat2x2D::makeIdentity(M);
}

//! @brief Reinitialises the object with a uniform scaling transformation.
//! @param[in] scaleFactor The scaling factor to apply to the X and Y axis.
void Matrix2x2::makeScale(double scaleFactor)
{
    Operations_Mat2x2D::makeUniformScale(scaleFactor, M);
}

//! @brief Reinitialises the object with a uniform scaling transformation.
//! @param[in] scale A 2D vector defining the scale factors.
void Matrix2x2::makeScale(const Point2D &scaleFactor)
{
    Operations_Mat2x2D::makeScale(scaleFactor.toArray(), M);
}

//! @brief Reinitialises the object with a scaling transformation.
//! @param[in] scaleFactorX The scaling factor to apply to the X axis.
//! @param[in] scaleFactorY The scaling factor to apply to the Y axis.
void Matrix2x2::makeScale(double scaleFactorX, double scaleFactorY)
{
    double scale[] = { scaleFactorX, scaleFactorY };

    Operations_Mat2x2D::makeScale(scale, M);
}

//! @brief Reinitialises the object to a rotation transformation.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
void Matrix2x2::makeRotation(double angleInRadians)
{
    Operations_Mat2x2D::makeRotation(angleInRadians, M);
}

//! @brief Multiplies the matrix by a 2D point.
//! @param[in] rhs The point to multiply.
//! @return The transformed 2D point.
Point2D Matrix2x2::operator*(const Point2D &rhs) const
{
    double transformed[2];

    Operations_Mat2x2D::multiplyPoint2D(M, rhs.toArray(), transformed);

    return { transformed };
}

//! @brief Multiples the current matrix by another.
//! @param[in] rhs The matrix to multiply by the current one.
//! @return A matrix representing the combined transformation of the current
//! matrix and @p rhs.
//! @note If concatenating transforms, the transform to concatenate must be
//! the lhs and the transform to concatenate to must be @p rhs.
Matrix2x2 Matrix2x2::operator*(const Matrix2x2 &rhs) const
{
    double result[4];

    Operations_Mat2x2D::multiply(M, rhs.M, result);

    return { result };
}

//! @brief Multiplies a matrix by the current matrix in-place.
//! @param[in] rhs The matrix to multiply by the current one.
//! @return A reference to the current matrix.
Matrix2x2 &Matrix2x2::operator*=(const Matrix2x2 &rhs)
{
    Operations_Mat2x2D::multiplyInPlace(M, rhs.M);

    return *this;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

