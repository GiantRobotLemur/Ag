//! @file Geometry/Matrix3x3.cpp
//! @brief The definition of an object representing a 3x3 matrix with double
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

#include "Ag/Geometry/Matrix3x3.hpp"

#include "Operations.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Matrix3x3 Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Initialises the object to an identity matrix.
Matrix3x3::Matrix3x3() :
    _padding(1.0)
{
    Operations_Mat3x3D::makeIdentity(M);
}

//! @brief Creates an initialises a 3x3 matrix from an array of 9 scalar values.
//! @param m 
Matrix3x3::Matrix3x3(const double *m) :
    _padding(1.0)
{
    Operations_Mat3x3D::copy(m, M);
}

//! @brief Creates a 3x3 matrix which defines a scale transformation in all
//! three axes.
//! @param[in] uniformScale The scale factor to apply to X, Y and Z.
//! @return A new matrix.
Matrix3x3 Matrix3x3::scale(double uniformScale)
{
    double m[9];
    Operations_Mat3x3D::makeUniformScale(uniformScale, m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a scale transformation in the
//! X and Y directions.
//! @param[in] scale A vector containing the X and Y scale factors.
//! @return A new matrix.
Matrix3x3 Matrix3x3::scaleXY(const Point2D &scale)
{
    double m[9];
    Operations_Mat3x3D::makeScaleXY(scale.toArray(), m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a scale transformation in the
//! X and Y directions.
//! @param[in] scaleX The scale factor to apply along the X axis.
//! @param[in] scaleY The scale factor to apply along the Y axis.
//! @return A new matrix.
Matrix3x3 Matrix3x3::scaleXY(double scaleX, double scaleY)
{
    Point2D scale(scaleX, scaleY);
    double m[9];

    Operations_Mat3x3D::makeScaleXY(scale.toArray(), m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a rotation transformation in the
//! X/Y plane.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @return A new matrix.
Matrix3x3 Matrix3x3::rotationXY(double angleInRadians)
{
    double m[9];
    Operations_Mat3x3D::makeRotationXY(angleInRadians, m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a rotation transformation in the
//! X/Y plane.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @param[in] rotationCentre The point which is the rotation takes place around.
//! @return A new matrix.
Matrix3x3 Matrix3x3::rotationXY(double angleInRadians, const Point2D &rotationCentre)
{
    double m[9];
    Operations_Mat3x3D::makeRotationXY(angleInRadians,
                                       rotationCentre.toArray(), m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a translation transformation in the
//! X/Y plane.
//! @param[in] dX The offset to translate in the X direction.
//! @param[in] dY The offset to translate in the Y direction.
//! @return A new matrix.
Matrix3x3 Matrix3x3::translationXY(double dX, double dY)
{
    Point2D delta(dX, dY);
    double m[9];

    Operations_Mat3x3D::makeTranslationXY(delta.toArray(), m);

    return { m };
}

//! @brief Creates a 3x3 matrix which does a translation transformation in the
//! X/Y plane.
//! @param[in] delta The offset to translate in the X and Y directions.
//! @return A new matrix.
Matrix3x3 Matrix3x3::translationXY(const Point2D &delta)
{
    double m[9];
    Operations_Mat3x3D::makeTranslationXY(delta.toArray(), m);

    return { m };
}

//! @brief Determines if the matrix is set to the identity value.
//! @retval true The matrix is set to the identity value.
//! @retval false At least one component differs from the identity matrix.
bool Matrix3x3::isIdentity() const noexcept
{
    return Operations_Mat3x3D::isIdentity(M);
}

//! @brief Calculates the inverse of the matrix transformation.
//! @return A new matrix which represents the inverse of the current matrix.
//! @throws DivisionByZeroException If the matrix is singular, i.e. the
//! determinant is zero.
Matrix3x3 Matrix3x3::inverse() const
{
    double n[9];

    if (Operations_Mat3x3D::tryCalculateInverse(M, n))
        return { n };

    throw DivisionByZeroException("Creating an inverse 3x3 matrix");
}

//! @brief Reinitialise the object to an identity matrix.
void Matrix3x3::makeIdentity()
{
    Operations_Mat3x3D::makeIdentity(M);
}

//! @brief Overwrites the matrix with a uniform scale transformation.
//! @param[in] uniformScale The scale factor to apply to X, Y and Z.
void Matrix3x3::makeScale(double scaleFactor)
{
    Operations_Mat3x3D::makeUniformScale(scaleFactor, M);
}

//! @brief Overwrites the matrix with a scale transformation in the
//! X and Y directions.
//! @param[in] scaleFactor A vector containing the X and Y scale factors.
void Matrix3x3::makeScaleXY(const Point2D &scaleFactor)
{
    Operations_Mat3x3D::makeScaleXY(scaleFactor.toArray(), M);
}

//! @brief Overwrites the matrix with a scale transformation in the
//! X and Y directions.
//! @param[in] scaleFactorX The scale factor to apply along the X axis.
//! @param[in] scaleFactorY The scale factor to apply along the Y axis.
void Matrix3x3::makeScaleXY(double scaleFactorX, double scaleFactorY)
{
    Point2D scale(scaleFactorX, scaleFactorY);

    makeScaleXY(scale);
}

//! @brief Overwrites the matrix with a rotation transformation in the
//! X/Y plane.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
void Matrix3x3::makeRotationXY(double angleInRadians)
{
    Operations_Mat3x3D::makeRotationXY(angleInRadians, M);
}

//! @brief Overwrites the matrix with a rotation transformation in the
//! X/Y plane.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @param[in] rotationCentre The point which is the rotation takes place around.
void Matrix3x3::makeRotationXY(double angleInRadians,
                               const Point2D &rotationCentre)
{
    Operations_Mat3x3D::makeRotationXY(angleInRadians,
                                       rotationCentre.toArray(), M);
}

//! @brief Overwrites the matrix with a translation transformation in the
//! X/Y plane.
//! @param[in] dX The offset to translate in the X direction.
//! @param[in] dY The offset to translate in the Y direction.
void Matrix3x3::makeTranslationXY(double dX, double dY)
{
    Point2D delta(dX, dY);

    Operations_Mat3x3D::makeTranslationXY(delta.toArray(), M);
}

//! @brief Overwrites the matrix with a translation transformation in the
//! X/Y plane.
//! @param[in] delta The offset to translate in the X and Y directions.
void Matrix3x3::makeTranslationXY(const Point2D &delta)
{
    Operations_Mat3x3D::makeTranslationXY(delta.toArray(), M);
}

//! @brief Multiplies the matrix by a 2D point, assuming the Z component is 1.0.
//! @param[in] rhs The 2D point to transform.
//! @return The transformed point.
Point2D Matrix3x3::operator*(const Point2D &rhs) const
{
    double result[2];

    Operations_Mat3x3D::multiplyPoint2D(M, rhs.toArray(), result);

    return { result };
}

//! @brief Multiplies one 3x3 matrix by another to create a new one.
//! @param[in] rhs The matrix to multiply the current one by.
//! @return A matrix representing the combined transformations.
//! @note If combining transforms, the transform to be concatenated
//! must be lhs and the transform to concatenate to must be @p rhs.
Matrix3x3 Matrix3x3::operator*(const Matrix3x3 &rhs) const
{
    double result[9];
    Operations_Mat3x3D::multiply(M, rhs.M, result);

    return { result };
}

//! @brief Multiplies one 3x3 matrix by another in place.
//! @param[in] rhs The matrix to multiply the current one by.
//! @return A reference to the current matrix.
Matrix3x3 &Matrix3x3::operator*=(const Matrix3x3 &rhs)
{
    Operations_Mat3x3D::multiplyInPlace(M, rhs.M);

    return *this;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

