//! @file Geometry/Point2I.cpp
//! @brief The definition of a 32-bit integer-based 2-dimensional vector value
//! used as an interface to all integer geometry primitives.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include "Ag/Core/Exception.hpp"

#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Size2I.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Point2I Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a point primitive with components initialised to those of
//! an integer size object.
//! @param[in] size The size containing the horizontal and vertical components to
//! initialise the point with.
Point2I::Point2I(const Size2I &size) noexcept :
    _x(size.getWidth()),
    _y(size.getHeight())
{
}

//! @brief A fixed point with components set to zero.
const Point2I Point2I::Origin;

//! @brief Gets a reference to the horizontal component.
Point2I::ComponentRef Point2I::getXRef() noexcept
{
    return _x;
}

//! @brief Gets a reference to the vertical component.
Point2I::ComponentRef Point2I::getYRef() noexcept
{
    return _y;
}

//! @brief Sets the horizontal component of the point.
//! @param[in] x The new horizontal component value.
void  Point2I::setX(Point2I::Component x) noexcept
{
    _x = x;
}

//! @brief Sets the vertical component of the point.
//! @param[in] y The new vertical component value.
void  Point2I::setY(Point2I::Component y) noexcept
{
    _y = y;
}

//! @brief Sets the component values of the point.
//! @param[in] x The new horizontal component value.
//! @param[in] y The new vertical component value.
void Point2I::set(Point2I::Component x, Point2I::Component y) noexcept
{
    _x = x;
    _y = y;
}

//! @brief Gets the point as an array of component values.
Point2I::ComponentPtr Point2I::asComponents() noexcept
{
    return &_x;
}

//! @brief Calculates the quotient of the current point divided by another.
//! @param[in] rhs The point to divide by.
//! @return The quotient of the two points.
//! @throws Ag::DivisionByZeroException If either component of rhs is 0.
Point2I Point2I::operator/(const Point2I &rhs) const
{
    if ((rhs._x * rhs._y) == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling an integer "
                                          "2-dimensional point.");
    }

    return { _x / rhs._x, _y / rhs._y };
}

//! @brief Calculates the quotient of the current point divided by another.
//! @param[in] rhs The point to divide by.
//! @return The quotient of the two points.
//! @throws Ag::DivisionByZeroException If either component of rhs is 0.
Point2I Point2I::operator/(Point2I::Component rhs) const
{
    if (rhs == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling an integer "
                                          "2-dimensional point.");
    }

    return { _x / rhs, _y / rhs };
}

//! @brief Calculates the sum of the current point and another in-place.
//! @param[in] rhs The point to add to the current components.
//! @return A reference to the current object.
Point2I &Point2I::operator+=(const Point2I &rhs)
{
    _x += rhs._x;
    _y += rhs._y;

    return *this;
}

//! @brief Calculates the difference between current point and another in-place.
//! @param[in] rhs The point to subtract from the current components.
//! @return A reference to the current object.
Point2I &Point2I::operator-=(const Point2I &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;

    return *this;
}

//! @brief Calculates the product of the current point and another in-place.
//! @param[in] rhs The point to multiply by the current components.
//! @return A reference to the current object.
Point2I &Point2I::operator*=(const Point2I &rhs)
{
    _x *= rhs._x;
    _y *= rhs._y;

    return *this;
}

//! @brief Calculates the product of the current point and a scalar in-place.
//! @param[in] rhs The scalar to multiply by the current components.
//! @return A reference to the current object.
Point2I &Point2I::operator*=(Point2I::Component rhs)
{
    _x *= rhs;
    _y *= rhs;

    return *this;
}

//! @brief Calculates the quotient of the current point divided by another in-place.
//! @param[in] rhs The point to divide the current components by.
//! @return A reference to the current object.
//! @throws Ag::DivisionByZeroException If either component of rhs was 0.
Point2I &Point2I::operator/=(const Point2I &rhs)
{
    if ((rhs._x * rhs._y) == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling an integer "
                                          "2-dimensional point.");
    }

    _x /= rhs._x;
    _y /= rhs._y;

    return *this;
}

//! @brief Calculates the quotient of the current point divided by a scalar in-place.
//! @param[in] rhs The scalar to divide the current components by.
//! @return A reference to the current object.
//! @throws Ag::DivisionByZeroException If rhs was 0.
Point2I &Point2I::operator/=(Point2I::Component rhs)
{
    if (rhs * rhs == 0)
    {
        throw Ag::DivisionByZeroException("The program attempted to perform a "
                                          "division by 0 in scaling an integer "
                                          "2-dimensional point.");
    }

    _x /= rhs;
    _y /= rhs;

    return *this;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

