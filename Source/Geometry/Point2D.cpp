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

#include "Operations.hpp"

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
Point2D::ComponentPtr Point2D::toArray() noexcept
{
    return &_x;
}

//! @brief Determines if both components are zero.
//! @retval true Both X and Y components are zero.
//! @retval false Either X or Y, possibly both, are non-zero.
bool Point2D::isZero() const noexcept
{
    return Operations_Vec2D::anyZero(&_x);
}

//! @brief Determines of the current point has identical component values
//! to another.
//! @param[in] rhs The point to compare against.
//! @retval true The current point has identical components of rhs.
//! @retval false The current point has at least one component which
//! differs from rhs.
bool Point2D::operator==(const Point2D &rhs) const noexcept
{
    return Operations_Vec2D::isEqual(&_x, &rhs._x);
}

//! @brief Determines of the current point has a least one differing
//! component value to another.
//! @param[in] rhs The point to compare against.
//! @retval true The current point has at least one component which
//! differs from rhs.
//! @retval false The current point has identical components of rhs.
bool Point2D::operator!=(const Point2D &rhs) const noexcept
{
    return Operations_Vec2D::isNotEqual(&_x, &rhs._x);
}

//! @brief Calculates the sum of the current point and another.
//! @param[in] rhs The point to add.
//! @return The sum of the two points.
Point2D Point2D::operator+(const Point2D &rhs) const noexcept
{
    double result[2];
    Operations_Vec2D::add(&_x, &rhs._x, result);

    return { result };
}

//! @brief Calculates the difference between the current point and another.
//! @param[in] rhs The point to subtract.
//! @return The difference the two points.
Point2D Point2D::operator-(const Point2D &rhs) const noexcept
{
    double result[2];
    Operations_Vec2D::sub(&_x, &rhs._x, result);

    return { result };
}

//! @brief Calculates the negative of the current point.
Point2D Point2D::operator-() const noexcept
{
    double result[2];
    Operations_Vec2D::neg(&_x, result);

    return { result };
}

//! @brief Calculates the product of the current point and another.
//! @param[in] rhs The point to multiply by.
//! @return The component-wise product of the two points.
Point2D Point2D::operator*(const Point2D &rhs) const noexcept
{
    double result[2];
    Operations_Vec2D::mul(&_x, &rhs._x, result);

    return { result };
}

//! @brief Calculates the product of the current point and a scalar.
//! @param[in] rhs The scalar to multiply by.
//! @return The component-wise product of the point and scalar.
Point2D Point2D::operator*(Point2D::Component rhs) const noexcept
{
    double result[2];
    Operations_Vec2D::scalarMul(&_x, rhs, result);

    return { result };
}

//! @brief Calculates the quotient of the current point divided by another.
//! @param[in] rhs The point to divide by.
//! @return The quotient of the two points.
//! @throws Ag::DivisionByZeroException If either component of rhs is 0.
Point2D Point2D::operator/(const Point2D &rhs) const
{
    if (Operations_Vec2D::anyZero(&rhs._x))
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    double result[2];
    Operations_Vec2D::div(&_x, &rhs._x, result);

    return { result };
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

    double result[2];
    Operations_Vec2D::scalarDiv(&_x, rhs, result);

    return { result };
}

//! @brief Calculates the sum of the current point and another in-place.
//! @param[in] rhs The point to add to the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator+=(const Point2D &rhs)
{
    Operations_Vec2D::addAssign(&_x, &rhs._x);

    return *this;
}

//! @brief Calculates the difference between current point and another in-place.
//! @param[in] rhs The point to subtract from the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator-=(const Point2D &rhs)
{
    Operations_Vec2D::subAssign(&_x, &rhs._x);

    return *this;
}

//! @brief Calculates the product of the current point and another in-place.
//! @param[in] rhs The point to multiply by the current components.
//! @return A reference to the current object.
Point2D &Point2D::operator*=(const Point2D &rhs)
{
    Operations_Vec2D::mulAssign(&_x, &rhs._x);

    return *this;
}

//! @brief Calculates the product of the current point and a scalar in-place.
//! @param[in] rhs The scalar to multiply the current components by.
//! @return A reference to the current object.
Point2D &Point2D::operator*=(Point2D::Component rhs)
{
    Operations_Vec2D::scalarMulAssign(&_x, rhs);

    return *this;
}

//! @brief Calculates the quotient of the current point divided by another in-place.
//! @param[in] rhs The point to divide the current components by.
//! @return A reference to the current object.
//! @throws Ag::DivisionByZeroException If either component of rhs was 0.
Point2D &Point2D::operator/=(const Point2D &rhs)
{
    if (Operations_Vec2D::anyZero(&rhs._x))
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling a real "
                                          "2-dimensional point.");
    }

    Operations_Vec2D::divAssign(&_x, &rhs._x);

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

    Operations_Vec2D::scalarDivAssign(&_x, rhs);

    return *this;
}

//! @brief Clamps the component values of the point to a specified range.
//! @param[in] minimum Represents minimum allowed component values.
//! @param[in] maximum Represents maximum allowed component values.
//! @return A point with component values forced into the specified range.
Point2D Point2D::clamp(const Point2D &minimum,
                       const Point2D &maximum) const
{
    double result[2];
    Operations_Vec2D::clamp(&_x, &minimum._x, &maximum._x, result);

    return { result };
}

//! @brief Calculates the length of the vector.
Point2D::Component Point2D::magnitude() const
{
    const double magnitudeSq = Operations_Vec2D::magnitudeSq(&_x);

    return std::sqrt(magnitudeSq);
}

//! @brief Calculates the squared length of the vector.
Point2D::Component Point2D::magnitudeSquared() const noexcept
{
    return Operations_Vec2D::magnitudeSq(&_x);
}

//! @brief Calculates the dot product of the current vector with another.
//! @param[in] rhs The second vector to create a dot product with.
//! @return The dot product value.
Point2D::Component Point2D::dotProduct(const Point2D &rhs) const noexcept
{
    return Operations_Vec2D::dot(&_x, &rhs._x);
}

//! @brief Calculates the signed area of a triangle formed by the current
//! and another vector.
//! @param[in] rhs The vector to calculate the determinant with.
//! @return The signed area of the triangle, the sign indicating the relative
//! orientation of the two vectors.
Point2D::Component Point2D::determinant(const Point2D &rhs) const noexcept
{
    return Operations_Vec2D::det(&_x, &rhs._x);
}

//! @brief Calculates the non-negative distance separating the current point
//! from another.
//! @param[in] rhs The point to measure to.
//! @return The non-negative distance between the points.
double Point2D::distance(const Point2D &rhs) const
{
    return Operations_Vec2D::distance(&_x, &rhs._x);
}

//! @brief Calculates the angle of a line connecting the current point to another.
//! @param[in] rhs The point to measure the angle to.
//! @return The angle in radians relative to the X axis, counter-clockwise in
//! a LH coordinate system between -Pi and Pi.
double Point2D::angleTo(const Point2D &rhs) const
{
    double delta[2];
    Operations_Vec2D::sub(&rhs._x, &_x, delta);

    return std::atan2(delta[1], delta[0]);
}

//! @brief Calculates the angle of a line formed from the origin to the current
//! position i.e. it's vector direction.
//! @return The angle in radians relative to the X axis, counter-clockwise in
//! a LH coordinate system between -Pi and Pi.
double Point2D::angleFromOrigin() const
{
    return std::atan2(_y, _x);
}

//! @brief Creates a version of the vector with unit length, i.e. with
//! a magnitude of 1.0.
//! @return A copy of the vector scaled to have a length of 1.0.
//! @throws ZeroLengthVectorException If the magnitude is zero.
Point2D Point2D::normalised() const
{
    double result[2];

    if (Operations_Vec2D::tryNormalise(&_x, result))
    {
        return Point2D(result);
    }
    else
    {
        throw ZeroLengthVectorException("Attempting to scale a "
                                        "zero-length vector to unit length.");
    }
}

//! @brief Performs a (possibly optimised) fused-multiply-add operation on the
//! vector components.
//! @param[in] scale The scalar to multiply by the current vector components.
//! @param[in] translation The vector components to add to the product.
//! @return The resultant vector.
Point2D Point2D::fma(Point2D::Component scale, const Point2D &translation) const
{
    double result[2];
    Operations_Vec2D::scalarFma(&_x, scale, &translation._x, result);

    return { result };
}

//! @brief Performs a (possibly optimised) fused-multiply-add operation on the
//! vector components.
//! @param[in] scale The vector components to multiply by the current components.
//! @param[in] translation The vector components to add to the product.
//! @return The resultant vector.
Point2D Point2D::fma(const Point2D &scale, const Point2D &translation) const
{
    double result[2];
    Operations_Vec2D::fma(&_x, &scale._x, &translation._x, result);

    return { result };
}

//! @brief Scales the vector to have a magnitude of unit length, i.e. 1.0.
//! @throws ZeroLengthVectorException If the magnitude is zero.
void Point2D::normalise()
{
    if (Operations_Vec2D::tryNormalise(&_x, &_x) == false)
    {
        throw ZeroLengthVectorException("Attempting to scale a "
                                        "zero-length vector to unit length.");
    }
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

