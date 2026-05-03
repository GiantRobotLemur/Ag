//! @file Geometry/AffineTransform2D.cpp
//! @brief The definition of an object representing a 2-dimensional affine
//! transformation.
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

#include "Operations.hpp"
#include "Ag/Geometry/AffineTransform2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// AffineTransform2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an identity transform.
AffineTransform2D::AffineTransform2D()
{
    Operations_AffineTrans2D::makeIdentity(_m);
    Operations_Vec2D::setOne(_m + 6);
}

//! @brief Constructs an affine transform from a 2x2 matrix.
//! @param[in] scale A 2x2 matrix defining a transformation which does not
//! involve translation.
AffineTransform2D::AffineTransform2D(const Matrix2x2 &scale)
{
    Operations_Mat2x2D::copy(scale.M, _m);
    Operations_Vec2D::setZero(_m + 4);
    Operations_Vec2D::setOne(_m + 6);
}

//! @brief Constructs an affine translation transformation.
//! @param[in] translation The translation offsets to encode.
AffineTransform2D::AffineTransform2D(const Point2D &translation)
{
    Operations_AffineTrans2D::makeTranslation(translation.toArray(), _m);
    Operations_Vec2D::setOne(_m + 6);
}

//! @brief Constructs an affine transformation which is a scale transform
//! based on a 2x2 matrix followed by a translation.
//! @param[in] scale The scale transform to encode.
//! @param[in] translation The additional translation to encode.
AffineTransform2D::AffineTransform2D(const Matrix2x2 &scale, const Point2D &translation)
{
    Operations_Mat2x2D::copy(scale.M, _m);
    Operations_Vec2D::copy(translation.toArray(), _m + 4);
    Operations_Vec2D::setOne(_m + 6);
}

//! @brief Constructs an affine transformation from a set of 6 values.
//! @param[in] values The raw homogeneous 2D transform values, the first four
//! are a 2x2 matrix the and the last two are translation values.
AffineTransform2D::AffineTransform2D(const double *values)
{
    Operations_AffineTrans2D::copy(values, _m);
    Operations_Vec2D::setOne(_m + 6);
}

//! @brief Gets a pointer to the 6 raw values defining the transformation.
//! @return A read-only pointer to the 2x2 matrix followed by the
//! translation offsets.
const double *AffineTransform2D::toArray() const noexcept
{
    return _m;
}

//! @brief Determines if the object represents the identity transform.
//! @retval true The object represents the identity transform.
//! @retval false The object differs by at least one component from the
//! identity transform.
bool AffineTransform2D::isIdentity() const noexcept
{
    return Operations_AffineTrans2D::isIdentity(_m);
}

//! @brief Constructs an affine transformation representing the inverse
//! of the current transformation.
//! @return The inverse transform.
//! @throw DivisionByZeroException Thrown if the scale transform is singular.
AffineTransform2D AffineTransform2D::inverse() const
{
    double m[6];

    if (Operations_AffineTrans2D::tryCalculateInverse(_m, m))
        return { m };

    throw DivisionByZeroException("Creating an inverse 2D affine transformation.");
}

//! @brief Attempts to calculate the affine transformation representing the inverse
//! of the current transformation.
//! @param[out] inv Receives the inverse transformation, if on e is possible.
//! @retval true An inverse transform was calculated and returned in @p inv.
//! @retval false The transform did not have an inverse.
bool AffineTransform2D::tryCalculateInverse(AffineTransform2D &inv) const
{
    return Operations_AffineTrans2D::tryCalculateInverse(_m, inv._m);
}

//! @brief Overwrites the object with the identity transform.
AffineTransform2D &AffineTransform2D::makeIdentity()
{
    Operations_AffineTrans2D::makeIdentity(_m);

    return *this;
}

//! @brief Overwrites the object with a uniform scale transform.
//! @param[in] scaleFactor The scale factor to apply uniformly in the X and Y
//! directions.
AffineTransform2D &AffineTransform2D::makeScale(double scaleFactor)
{
    Operations_AffineTrans2D::makeUniformScale(scaleFactor, _m);

    return *this;
}

//! @brief Overwrites the object with a scale transform.
//! @param[in] scaleFactor A vector object specifying individual scale factors
//! in the X and Y direction.
AffineTransform2D &AffineTransform2D::makeScale(const Point2D &scaleFactor)
{
    Operations_AffineTrans2D::makeScale(scaleFactor.toArray(), _m);

    return *this;
}

//! @brief Overwrites the object with a scale transform.
//! @param[in] scaleFactorX The scale factor to apply to the X axis.
//! @param[in] scaleFactorY The scale factor to apply to the Y axis.
AffineTransform2D &AffineTransform2D::makeScale(double scaleFactorX,
                                                double scaleFactorY)
{
    double scale[] = { scaleFactorX, scaleFactorY };

    Operations_AffineTrans2D::makeScale(scale, _m);

    return *this;
}

//! @brief Overwrites the object with a scale about an arbitrary point.
//! @param[in] scaleFactor A vector object specifying individual scale factors
//! in the X and Y direction.
//! @param[in] centre The point about which the scale will be applied.
AffineTransform2D &AffineTransform2D::makeScale(const Point2D &scaleFactor,
                                                const Point2D &centre)
{
    double scaleTransform[6];
    double negativeOffset[2];
    Operations_Vec2D::neg(centre.toArray(), negativeOffset);

    // Make the translation back to the origin.
    Operations_AffineTrans2D::makeTranslation(negativeOffset, _m);

    // Make the scale transform and append it.
    Operations_AffineTrans2D::makeScale(scaleFactor.toArray(), scaleTransform);
    Operations_AffineTrans2D::appendTransformInPlace(_m, scaleTransform);

    // Translate back from the origin.
    Operations_Vec2D::addAssign(_m + 4, centre.toArray());

    return *this;
}

AffineTransform2D &AffineTransform2D::makeTranslation(double dX, double dY)
{
    Point2D offset(dX, dY);

    Operations_AffineTrans2D::makeTranslation(offset.toArray(), _m);

    return *this;
}

AffineTransform2D &AffineTransform2D::makeTranslation(const Point2D &rhs)
{
    Operations_AffineTrans2D::makeTranslation(rhs.toArray(), _m);

    return *this;
}

//! @brief Overwrites the object with a rotation about the origin.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
AffineTransform2D &AffineTransform2D::makeRotation(double angleInRadians)
{
    Operations_AffineTrans2D::makeRotation(angleInRadians, _m);

    return *this;
}

//! @brief Overwrites the object with a rotation about a specified point.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @param[in] centre The point about which rotation takes place.
AffineTransform2D &AffineTransform2D::makeRotation(double angleInRadians, const Point2D &centre)
{
    double n[6];
    double negativeOffset[2];

    // Translate the rotation centre to the origin.
    Operations_Vec2D::neg(centre.toArray(), negativeOffset);
    Operations_AffineTrans2D::makeTranslation(negativeOffset, _m);

    // Create a rotation transform.
    Operations_AffineTrans2D::makeRotation(angleInRadians, n);

    // Append it.
    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    // Translate back from the origin.
    Operations_Vec2D::addAssign(_m + 4, centre.toArray());

    return *this;
}

//! @brief Appends a uniform scale transform to the current transform.
//! @param scaleFactor 
//! @param[in] scaleFactor A vector object specifying individual scale factors
//! in the X and Y direction.
AffineTransform2D &AffineTransform2D::appendScale(double scaleFactor)
{
    double n[6];
    Operations_AffineTrans2D::makeUniformScale(scaleFactor, n);

    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    return *this;
}

//! @brief Appends a scale transform to the current transform.
//! @param[in] scaleFactor A vector object specifying individual scale factors
//! in the X and Y direction.
AffineTransform2D &AffineTransform2D::appendScale(const Point2D &scaleFactor)
{
    double n[6];
    Operations_AffineTrans2D::makeScale(scaleFactor.toArray(), n);

    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    return *this;
}

//! @brief Appends a scale transform to the current transform.
//! @param[in] scaleFactorX The scale factor to apply to the X axis.
//! @param[in] scaleFactorY The scale factor to apply to the Y axis.
AffineTransform2D &AffineTransform2D::appendScale(double scaleX, double scaleY)
{
    double n[8];

    // Put the scale factors at the end of the array to guarantee alignment.
    n[6] = scaleX;
    n[7] = scaleY;

    Operations_AffineTrans2D::makeScale(n + 6, n);

    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    return *this;
}

//! @brief Appends a scale about an arbitrary point transform to the
//! current transform.
//! @param[in] scaleFactor A vector object specifying individual scale factors
//! in the X and Y direction.
//! @param[in] centre The centre about which scaling is calculated.
AffineTransform2D &AffineTransform2D::appendScale(const Point2D &scaleFactor, const Point2D &centre)
{
    double n[6];

    // Translate the scaling centre to the origin.
    Operations_Vec2D::subAssign(_m + 4, centre.toArray());

    // Create a scaling transform.
    Operations_AffineTrans2D::makeScale(scaleFactor.toArray(), n);

    // Append it.
    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    // Translate back from the origin.
    Operations_Vec2D::addAssign(_m + 4, centre.toArray());

    return *this;
}

//! @brief Appends a rotation about the origin to the current transform.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
AffineTransform2D &AffineTransform2D::appendRotation(double angleInRadians)
{
    double n[6];
    Operations_AffineTrans2D::makeRotation(angleInRadians, n);

    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    return *this;
}

//! @brief Appends a rotation about a fixed point to the current transform.
//! @param[in] angleInRadians The rotation angle counter-clockwise in a
//! left-handed system.
//! @param[in] centre The point about which the rotation should take place.
AffineTransform2D &AffineTransform2D::appendRotation(double angleInRadians, const Point2D &centre)
{
    double n[6];

    // Translate the scaling centre to the origin.
    Operations_Vec2D::subAssign(_m + 4, centre.toArray());

    // Create a rotation transform.
    Operations_AffineTrans2D::makeRotation(angleInRadians, n);

    // Append it.
    Operations_AffineTrans2D::appendTransformInPlace(_m, n);

    // Translate back from the origin.
    Operations_Vec2D::addAssign(_m + 4, centre.toArray());

    return *this;
}

//! @brief Appends a translation to the current transform.
//! @param[in] dX The horizontal offset to add.
//! @param[in] dY The vertical offset to add.
AffineTransform2D &AffineTransform2D::appendTranslation(double dX, double dY)
{
    // [  1  0     [ A B     [    A        B
    //    0  1   *   C D   =      C        D
    //   -----       ---       -----------------
    //   dX dY ]     E F ]     (E + dX) (F + dY) ]

    // Get a properly aligned array.
    double n[] = { dX, dY };

    Operations_Vec2D::addAssign(_m + 4, n);

    return *this;
}

//! @brief Appends a translation to the current transform.
//! @param[in] offset A vector providing the horizontal and vertical components
//! to translate by.
AffineTransform2D &AffineTransform2D::appendTranslation(const Point2D &offset)
{
    Operations_Vec2D::addAssign(_m + 4, offset.toArray());

    return *this;
}

//! @brief Transforms a point using the current transform.
//! @param[in] rhs The point to transform.
//! @return The transformed point.
Point2D AffineTransform2D::operator*(const Point2D &rhs) const
{
    double result[2];
    Operations_AffineTrans2D::multiplyPoint2D(_m, rhs.toArray(), result);

    return { result };
}

//! @brief Combines the current transform with an other, creating a transform
//! which has the effect of the other followed by the current one.
//! @param[in] rhs The transform to multiply by.
//! @return The transform resulting from the multiplication.
AffineTransform2D AffineTransform2D::operator*(const AffineTransform2D &rhs) const
{
    double result[6];

    Operations_AffineTrans2D::multiply(_m, rhs._m, result);

    return { result };
}

//! @brief Combines the current transform with another, updating the transform
//! to essentially be the other transform followed by the current one.
//! @param[in] rhs The transform to multiply.
//! @return A reference to the current (updated) transform.
AffineTransform2D &AffineTransform2D::operator*=(const AffineTransform2D &rhs)
{
    Operations_AffineTrans2D::multiplyInPlace(_m, rhs._m);

    return *this;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

