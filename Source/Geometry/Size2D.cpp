//! @file Geometry/Size2D.cpp
//! @brief The definition of a value representing a 2-dimensional size using
//! real continuous components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
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
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"
#include "Ag/Geometry/Size2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Size2D Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a 2-dimensional size value which has component values of 0.
Size2D::Size2D() :
    _width(0),
    _height(0)
{
}

//! @brief Constructs a 2-dimensional size value using specific component values.
//! @param[in] width The value of the initial width.
//! @param[in] height The value of the initial height.
//! @throw NegativeSizeException If either width or height are negative.
Size2D::Size2D(double width, double height) :
    _width(width),
    _height(height)
{
    if ((_width < 0) || (_height < 0))
    {
        bool isWidth = (_width < 0);
        _width = _height = 0;

        throw NegativeSizeException(isWidth);
    }
}

//! @brief Constructs a 2-dimensional size value by copying another.
//! @param[in] rhs The size value to copy.
Size2D::Size2D(const Size2D &rhs) :
    _width(rhs._width),
    _height(rhs._height)
{
}

//! @brief Constructs a 2-dimensional size value from a 2D vector.
//! @param[in] rhs The vector to convert.
//! @throws NegativeSizeException If either component of rhs is negative.
Size2D::Size2D(const Point2D &rhs) :
    _width(0),
    _height(0)
{
    if ((rhs.getX() < 0) || (rhs.getY() < 0))
    {
        throw NegativeSizeException(rhs.getX() < 0);
    }

    _width = rhs.getX();
    _height = rhs.getY();
}

//! @brief Constructs a 2-dimensional size value by moving from another.
//! @param[in] rhs The size value to move.
Size2D::Size2D(Size2D &&rhs) noexcept :
    _width(rhs._width),
    _height(rhs._height)
{
}

//! @brief Determines if the size is in an empty state.
//! @retval true All components are zero.
//! @retval false At least one component is greater than zero.
bool Size2D::isEmpty() const
{
    return (_width == 0) && (_height == 0);
}

//! @brief Gets the width component of the size.
double Size2D::getWidth() const { return _width; }

//! @brief Sets the width component of the size.
//! @param[in] width The new width value.
//! @throw NegativeSizeException If width is less than zero.
void Size2D::setWidth(double width)
{
    if (width < 0)
    {
        throw NegativeSizeException(true);
    }

    _width = width;
}

//! @brief Gets the height component of the size.
double Size2D::getHeight() const { return _height; }

//! @brief Sets the height component of the size.
//! @param[in] height The new height value.
//! @throw NegativeSizeException If height is less than zero.
void Size2D::setHeight(double height)
{
    if (height < 0)
    {
        throw NegativeSizeException(false);
    }

    _height = height;
}

//! @brief Sets both width and height components of the object.
//! @param[in] width The new width value.
//! @param[in] height The new height value.
//! @throw NegativeSizeException If either width or height is less than zero.
void Size2D::set(double width, double height)
{
    if ((width < 0) || (height < 0))
    {
        throw NegativeSizeException(_width < 0);
    }

    _width = width;
    _height = height;
}

//! @brief Gets the object as a 2-element array of real values.
const double *Size2D::toArray() const noexcept
{
    static_assert(sizeof(Size2D) == (sizeof(double) * 2),
                  "A Size2D should be an alias for a vector of 2 doubles.");

    return reinterpret_cast<const double *>(this);
}

//! @brief Resets all components to zero.
void Size2D::clear()
{
    _width = 0;
    _height = 0;
}

//! @brief Overwrites the value of the object from another.
//! @param[in] rhs The value to copy.
//! @returns A reference to the current object.
Size2D &Size2D::operator=(const Size2D &rhs)
{
    _width = rhs._width;
    _height = rhs._height;

    return *this;
}

//! @brief Moves the value of another object to this one.
//! @param[in] rhs The object to move the value from.
//! @returns A reference to the current object.
Size2D &Size2D::operator=(Size2D &&rhs) noexcept
{
    _width = rhs._width;
    _height = rhs._height;

    return *this;
}

//! @brief Uses the components of a point to overwrite the size components of
//! the current object.
//! @param[in] rhs The point containing the components to transpose.
//! @returns A reference to the current object.
//! @throws NegativeSizeException If any of the copied components are negative.
Size2D &Size2D::operator=(const Point2D &rhs)
{
    if ((rhs.getX() < 0) || (rhs.getY() < 0))
    {
        throw NegativeSizeException(rhs.getX() < 0);
    }

    _width = rhs.getX();
    _height = rhs.getY();

    return *this;
}

//! @brief Determines if the current object has the same value as another.
//! @param[in] rhs The size value to compare with.
//! @retval true All corresponding components are equal.
//! @retval false At least one pair of corresponding components differs.
bool Size2D::operator==(const Size2D &rhs) const
{
    return (_width == rhs._width) && (_height == rhs._height);
}

//! @brief Determines if the current object has a different value from another.
//! @param[in] rhs The size value to compare with.
//! @retval true At least one pair of corresponding components differs.
//! @retval false All corresponding components are equal.
bool Size2D::operator!=(const Size2D &rhs) const
{
    return (_width != rhs._width) || (_height != rhs._height);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

