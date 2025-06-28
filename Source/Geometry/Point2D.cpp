//! @file Geometry/Point2D.cpp
//! @brief The definition of a 2-dimensional vector value used as an interface
//! to all geometry primitives.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <algorithm>

#include "Ag/Core/Exception.hpp"

#include "Ag/Geometry/Exceptions.hpp"
#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Point2D.hpp"
#include "Ag/Geometry/Size2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Point2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a point primitive with components initialised to those of
//! an integer size object.
//! @param[in] size The size containing the horizontal and vertical components to
//! initialise the point with.
Point2D::Point2D(const Size2D &size)  noexcept :
    _x(size.getWidth()),
    _y(size.getHeight())
{
}

//! @brief A fixed values where the components are all zero.
const Point2D Point2D::Origin;

//! @brief Gets a reference to the horizontal component.
Point2D::ComponentRef Point2D::getXRef() noexcept
{
    return _x;
}

//! @brief Gets a reference to the vertical component.
Point2D::ComponentRef Point2D::getYRef() noexcept
{
    return _y;
}

//! @brief Sets the horizontal component of the point.
//! @param[in] x The new horizontal component value.
void  Point2D::setX(Point2D::Component x) noexcept
{
    _x = x;
}

//! @brief Sets the vertical component of the point.
//! @param[in] y The new vertical component value.
void  Point2D::setY(Point2D::Component y) noexcept
{
    _y = y;
}

//! @brief Sets the component values of the point.
//! @param[in] x The new horizontal component value.
//! @param[in] y The new vertical component value.
void Point2D::set(Point2D::Component x, Point2D::Component y) noexcept
{
    _x = x;
    _y = y;
}

//! @brief Gets the point as an array of component values.
Point2D::ComponentPtr Point2D::asComponents() noexcept
{
    return &_x;
}

//! @brief Calculates the quotient of the current point divided by another.
//! @param[in] rhs The point to divide by.
//! @return The quotient of the two points.
//! @throws Ag::DivisionByZeroException If either component of rhs is 0.
Point2D Point2D::operator/(const Point2D &rhs) const
{
    if ((rhs._x * rhs._y) == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    return { _x / rhs._x, _y / rhs._y };
}

//! @brief Calculates the quotient of the current point divided by a scalar.
//! @param[in] rhs The scalar to divide by.
//! @return The quotient of the point divided by the scalar.
//! @throws Ag::DivisionByZeroException If rhs is 0.0.
Point2D Point2D::operator/(Point2D::Component rhs) const
{
    if (rhs == 0.0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    return { _x / rhs, _y / rhs };
}

//! @brief Calculates the sum of the current point and another in-place.
//! @param[in] rhs The point to add to the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator+=(const Point2D &rhs)
{
    _x += rhs._x;
    _y += rhs._y;

    return *this;
}

//! @brief Calculates the difference between current point and another in-place.
//! @param[in] rhs The point to subtract from the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator-=(const Point2D &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;

    return *this;
}

//! @brief Calculates the product of the current point and another in-place.
//! @param[in] rhs The point to multiply by the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator*=(const Point2D &rhs)
{
    _x *= rhs._x;
    _y *= rhs._y;

    return *this;
}

//! @brief Calculates the product of the current point and a scalar in-place.
//! @param[in] rhs The scalar to multiply the current components by.
//! @return A reference to the current object.
Point2D &Point2D::operator*=(Point2D::Component rhs)
{
    _x *= rhs;
    _y *= rhs;

    return *this;
}

//! @brief Calculates the quotient of the current point divided by another in-place.
//! @param[in] rhs The point to divide the current components by.
//! @return A reference to the current object.
//! @throws Ag::DivisionByZeroException If either component of rhs was 0.
Point2D &Point2D::operator/=(const Point2D &rhs)
{
    if ((rhs._x * rhs._y) == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    _x /= rhs._x;
    _y /= rhs._y;

    return *this;
}

//! @brief Calculates the quotient of the current point divided by a scalar in-place.
//! @param[in] rhs The scalar to divide the current point components by.
//! @return A reference to the current object.
//! @throws Ag::DivisionByZeroException If rhs was 0.
Point2D &Point2D::operator/=(Point2D::Component rhs)
{
    if (rhs == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    _x /= rhs;
    _y /= rhs;

    return *this;
}

//! @brief Clamps the component values of the point to a specified range.
//! @param[in] minimum Represents minimum allowed component values.
//! @param[in] maximum Represents maximum allowed component values.
//! @return A point with component values forced into the specified range.
Point2D Point2D::clamp(const Point2D &minimum,
                       const Point2D &maximum) const
{
    return { std::clamp(_x, minimum._x, maximum._x),
             std::clamp(_y, minimum._y, maximum._y) };
}

//! @brief Calculates the length of the vector.
Point2D::Component Point2D::magnitude() const
{
    double magnitudeSq = magnitudeSquared();

    return std::sqrt(magnitudeSq);
}

//! @brief Performs a (possibly optimised) fused-multiply-add operation on the
//! vector components.
//! @param[in] scale The scalar to multiply by the current vector components.
//! @param[in] translation The vector components to add to the product.
//! @return The resultant vector.
Point2D Point2D::fma(Point2D::Component scale, const Point2D &translation) const
{
    return { std::fma(_x, scale, translation._x),
             std::fma(_y, scale, translation._y) };
}

//! @brief Calculates the non-negative distance separating the current point
//! from another.
//! @param[in] rhs The point to measure to.
//! @return The non-negative distance between the points.
double Point2D::distance(const Point2D &rhs) const
{
    Point2D delta = *this - rhs;

    return delta.magnitude();
}

//! @brief Calculates the angle of a line connecting the current point to another.
//! @param[in] rhs The point to measure the angle to.
//! @return The angle in radians relative to the X axis, counter-clockwise in
//! a LH coordinate system.
double Point2D::angleTo(const Point2D &rhs) const
{
    Point2D delta = rhs - *this;

    return std::atan2(delta.getY(), delta.getX());
}

//! @brief Performs a (possibly optimised) fused-multiply-add operation on the
//! vector components.
//! @param[in] scale The vector components to multiply by the current components.
//! @param[in] translation The vector components to add to the product.
//! @return The resultant vector.
Point2D Point2D::fma(const Point2D &scale, const Point2D &translation) const
{
    return { std::fma(_x, scale._x, translation._x),
             std::fma(_y, scale._y, translation._y) };
}

//! @brief Creates a version of the vector with unit length, i.e. with
//! a magnitude of 1.0.
//! @return A copy of the vector scaled to have a length of 1.0.
//! @throws ZeroLengthVectorException If the magnitude is zero.
Point2D Point2D::normalised() const
{
    double magSq = magnitudeSquared();

    if (magSq == 0.0)
    {
        throw ZeroLengthVectorException("Attempting to scale a "
                                        "zero-length vector to unit length.");
    }

    double magnitude = std::sqrt(magSq);

    return { _x / magnitude, _y / magnitude };
}

//! @brief Scales the vector to have a magnitude of unit length, i.e. 1.0.
//! @throws ZeroLengthVectorException If the magnitude is zero.
void Point2D::normalise()
{
    double magSq = magnitudeSquared();

    if (magSq == 0.0)
    {
        throw ZeroLengthVectorException("Attempting to scale a "
                                        "zero-length vector to unit length.");
    }

    double magnitude = std::sqrt(magSq);

    _x /= magnitude;
    _y /= magnitude;
}

//! @brief Rotates the point about the origin LH clockwise relative to the origin.
//! @param[in] angle The angle to rotate by, in radians.
//! @return The rotated position.
Point2D Point2D::rotateCW(double angle) const
{
    double cosAngle = std::cos(angle);
    double sinAngle = std::sin(angle);

    return Point2D((_x * cosAngle) - (_y * sinAngle),
                   (_x * sinAngle) + (_y * cosAngle));
}

//! @brief Rotates the point about the origin LH counter-clockwise relative
//! to the origin.
//! @param[in] angle The angle to rotate by, in radians.
//! @return The rotated position.
Point2D Point2D::rotateCCW(double angle) const
{
    double cosAngle = std::cos(angle);
    double sinAngle = std::sin(angle);

    return Point2D((_x * cosAngle) + (_y * sinAngle),
                   (_y * cosAngle) - (_x * sinAngle));
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

