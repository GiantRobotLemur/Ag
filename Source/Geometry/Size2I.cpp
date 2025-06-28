//! @file Geometry/Size2I.cpp
//! @brief The definition of a value representing a 2-dimensional size using
//! discrete integer components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include <Ag/Core.hpp>

#include "Ag/Geometry/Exceptions.hpp"
#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Size2I.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Size2I Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a 2-dimensional size value using specific component values.
//! @param[in] width The value of the initial width.
//! @param[in] height The value of the initial height.
//! @throw NegativeSizeException If either width or height are negative.
Size2I::Size2I(int32_t width, int32_t height) :
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
Size2I::Size2I(const Size2I &rhs)
{
    asScalar() = rhs.asScalar();
}

//! @brief Constructs a 2-dimensional size value from a 2D vector.
//! @param[in] rhs The vector to convert.
//! @throws NegativeSizeException If either component of rhs is negative.
Size2I::Size2I(const Point2I &rhs) :
    _width(0),
    _height(0)
{
    if ((rhs.getX() < 0) || (rhs.getY() < 0))
    {
        throw NegativeSizeException(rhs.getX() < 0);
    }

    asScalar() = *reinterpret_cast<const uint64_t *>(&rhs);
}

//! @brief Constructs a 2-dimensional size value by moving from another.
//! @param[in] rhs The size value to move.
Size2I::Size2I(Size2I &&rhs) noexcept
{
    asScalar() = rhs.asScalar();
}

//! @brief Determines if the size is in an empty state.
//! @retval true All components are zero.
//! @retval false At least one component is greater than zero.
bool Size2I::isEmpty() const { return asScalar() == 0; }

////! @brief Gets the width component of the size.
//int32_t Size2I::getWidth() const { return _width; }

//! @brief Sets the width component of the size.
//! @param[in] width The new width value.
//! @throw NegativeSizeException If width is less than zero.
void Size2I::setWidth(int32_t width)
{
    if (width < 0)
    {
        throw NegativeSizeException(true);
    }

    _width = width;
}

////! @brief Gets the height component of the size.
//int32_t Size2I::getHeight() const { return _height; }

//! @brief Sets the height component of the size.
//! @param[in] height The new height value.
//! @throw NegativeSizeException If height is less than zero.
void Size2I::setHeight(int32_t height)
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
void Size2I::set(int32_t width, int32_t height)
{
    if ((width < 0) || (height < 0))
    {
        throw NegativeSizeException(_width < 0);
    }

    _width = width;
    _height = height;
}

//! @brief Resets all components to zero.
void Size2I::clear() { *reinterpret_cast<uint64_t *>(this) = 0; }

//! @brief Overwrites the value of the object from another.
//! @param[in] rhs The value to copy.
//! @returns A reference to the current object.
Size2I &Size2I::operator=(const Size2I &rhs)
{
    asScalar() = rhs.asScalar();

    return *this;
}

//! @brief Moves the value of another object to this one.
//! @param[in] rhs The object to move the value from.
//! @returns A reference to the current object.
Size2I &Size2I::operator=(Size2I &&rhs) noexcept
{
    asScalar() = rhs.asScalar();

    return *this;
}

//! @brief Uses the components of a point to overwrite the size components of
//! the current object.
//! @param[in] rhs The point containing the components to transpose.
//! @returns A reference to the current object.
//! @throws NegativeSizeException If any of the copied components are negative.
Size2I &Size2I::operator=(const Point2I &rhs)
{
    if ((rhs.getX() < 0) || (rhs.getY() < 0))
    {
        throw NegativeSizeException(rhs.getX() < 0);
    }

    asScalar() = *reinterpret_cast<const uint64_t *>(&rhs);

    return *this;
}

//! @brief Determines if the current object has the same value as another.
//! @param[in] rhs The size value to compare with.
//! @retval true All corresponding components are equal.
//! @retval false At least one pair of corresponding components differs.
bool Size2I::operator==(const Size2I &rhs) const
{
    return asScalar() == rhs.asScalar();
}

//! @brief Determines if the current object has a different value from another.
//! @param[in] rhs The size value to compare with.
//! @retval true At least one pair of corresponding components differs.
//! @retval false All corresponding components are equal.
bool Size2I::operator!=(const Size2I &rhs) const
{
    return asScalar() != rhs.asScalar();
}

//! @brief Gets a reference to the object value as a single 64-bit scalar.
uint64_t &Size2I::asScalar() noexcept
{
    static_assert(sizeof(Size2I) == (sizeof(int32_t) * 2),
                  "A Size2I should be an alias for a vector of 2 32-bit integers.");

    return *reinterpret_cast<uint64_t *>(this);
}

//! @brief Gets a read-only reference to the object value as a single 64-bit scalar.
const uint64_t &Size2I::asScalar() const noexcept
{
    return *reinterpret_cast<const uint64_t *>(this);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

