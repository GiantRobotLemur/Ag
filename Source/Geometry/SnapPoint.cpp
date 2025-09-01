//! @file Geometry/SnapPoint.cpp
//! @brief The definition of a 2-dimensional integer point used to snap real
//! points to a grid of arbitrary granularity.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/CollectionTools.hpp"
#include "Ag/Geometry/SnapContext.hpp"
#include "Ag/Geometry/SnapPoint.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// SnapPoint Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Compares snap points by Y component, then X component.
//! @param[in] lhs The first point to compare.
//! @param[in] rhs The second point to compare.
//! @retval true The left Y values is less or the Y values are equal and the
//! left X value is less.
//! @retval false The left Y value is greater or the Y values are equal and
//! the left X value is greater.
bool SnapPoint::CompareYMajor::operator()(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return (lhs._y == rhs._y) ? (lhs._x < rhs._x) : (lhs._y < rhs._y);
}

//! @brief Compares snap points by X component, then Y component.
//! @param[in] lhs The first point to compare.
//! @param[in] rhs The second point to compare.
//! @retval true The left X values is less or the Y values are equal and the
//! left Y value is less.
//! @retval false The left X value is greater or the X values are equal and
//! the left Y value is greater.
bool SnapPoint::CompareXMajor::operator()(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return (lhs._x == rhs._x) ? (lhs._y < rhs._y) : (lhs._x < rhs._x);
}

//! @brief Constructs a snapped integer point initialised to the origin.
SnapPoint::SnapPoint() :
    _x(0),
    _y(0)
{
}

//! @brief Constructs a snapped integer point with specific component values.
//! @param[in] x The horizontal offset of the point from the snapping grid origin.
//! @param[in] y The vertical offset of the point from the snapping grid origin.
SnapPoint::SnapPoint(int64_t x, int64_t y) :
    _x(x),
    _y(y)
{
}

//! @brief Gets the integer X coordinate of the snapped point.
int64_t SnapPoint::getX() const { return _x; }

//! @brief Sets the integer X coordinate of the snapped point.
//! @param[in] x The new horizontal offset.
void SnapPoint::setX(int64_t x) { _x = x; }

//! @brief Gets the integer Y coordinate of the snapped point.
int64_t SnapPoint::getY() const { return _y; }

//! @brief Sets the integer Y coordinate of the snapped point.
//! @param[in] y the new vertical offset.
void SnapPoint::setY(int64_t y) { _y = y; }

//! @brief Resets both components of the snapped point.
//! @param[in] x The new horizontal offset.
//! @param[in] y the new vertical offset.
void SnapPoint::set(int64_t x, int64_t y)
{
    _x = x;
    _y = y;
}

//! @brief Gets the point as an array of 2 x signed 64-bit integers.
const int64_t *SnapPoint::toArray() const
{
    static_assert(sizeof(SnapPoint) == (sizeof(int64_t) * 2),
                  "A snap point should only consist of 2 x 64-bit integers.");

    return reinterpret_cast<const int64_t *>(this);
}

//! @brief Compares snap points by Y component, then X component.
//! @param[in] rhs The point to compare against.
//! @retval true The current Y values is less or the Y values are equal and the
//! current X value is less.
//! @retval false The current Y value is greater or the Y values are equal and
//! the current X value is greater.
bool SnapPoint::lessThanYMajor(const SnapPoint &rhs) const
{
    return (_y == rhs._y) ? (_x < rhs._x) : (_y < rhs._y);
}

//! @brief Compares snap points by X component, then Y component.
//! @param[in] rhs The point to compare against.
//! @retval true The current X values is less or the Y values are equal and the
//! current Y value is less.
//! @retval false The current X value is greater or the X values are equal and
//! the current Y value is greater.
bool SnapPoint::lessThanXMajor(const SnapPoint &rhs) const
{
    return (_x == rhs._x) ? (_y < rhs._y) : (_x < rhs._x);
}

//! @brief Compares snap points by Y component, then X component.
//! @param[in] rhs The point to compare against.
//! @retval true The current Y values is greater or the Y values are equal and the
//! current X value is less.
//! @retval false The current Y value is less or the Y values are equal and
//! the current X value is greater.
bool SnapPoint::lessThanSweep(const SnapPoint &rhs) const
{
    return (_y == rhs._y) ? (_x < rhs._x) : (_y > rhs._y);
}

//! @brief Calculates the difference value comparing the Y component first.
//! @param[in] rhs The point to compare against.
//! @return Either -1, 0 or 1 determining whether the current point is
//! less than, equal or greater than @p rhs respectively.
int SnapPoint::diffYMajor(const SnapPoint &rhs) const
{
    int diff = 0;

    return (diffValues(_y, rhs._y, diff) ||
            diffValues(_x, rhs._x, diff)) ? diff : 0;
}

//! @brief Calculates the difference value comparing the X component first.
//! @param[in] rhs The point to compare against.
//! @return Either -1, 0 or 1 determining whether the current point is
//! less than, equal or greater than @p rhs respectively.
int SnapPoint::diffXMajor(const SnapPoint &rhs) const
{
    int diff = 0;

    return (diffValues(_x, rhs._x, diff) ||
            diffValues(_y, rhs._y, diff)) ? diff : 0;
}

//! @brief Calculates the difference value comparing the Y component first in
//! plane sweep ordering, i.e. greater Y-values have a lower value.
//! @param[in] rhs The point to compare against.
//! @return Either -1, 0 or 1 determining whether the current point is
//! less than, equal or greater than @p rhs respectively.
int SnapPoint::diffSweep(const SnapPoint &rhs) const
{
    int diff = 0;

    return (diffValues(rhs._y, _y, diff) ||
            diffValues(_x, rhs._x, diff)) ? diff : 0;
}

//! @brief Determines if two snapped points have the same value.
//! @param[in] rhs The point to compare with the current one.
//! @retval true The corresponding components of the two points are identical.
//! @retval false At least one pair of corresponding components differs.
bool SnapPoint::operator==(const SnapPoint &rhs) const
{
    return (_x == rhs._x) && (_y == rhs._y);
}

//! @brief Determines if two snapped points have different values.
//! @param[in] rhs The point to compare with the current one.
//! @retval true At least one pair of corresponding components differs.
//! @retval false The corresponding components of the two points are identical.
bool SnapPoint::operator!=(const SnapPoint &rhs) const
{
    return (_x != rhs._x) || (_y != rhs._y);
}

//! @brief Determines if the current point has a lower value than another using
//! plane sweep ordering.
//! @param[in] rhs The point to compare with the current one.
//! @retval true The current point appears earlier in the sweep than rhs.
//! @retval false The current point appears at the same position or after rhs
//! in a plane sweep.
bool SnapPoint::operator<(const SnapPoint &rhs) const
{
    // Use sweep ordering for indexing grid points.
    if (_y == rhs._y)
    {
        return _x < rhs._x;
    }
    else
    {
        return _y > rhs._y;
    }
}


//! @brief Determines if the current point has a lower or equal value to
//! another using plane sweep ordering.
//! @param[in] rhs The point to compare with the current one.
//! @retval true The current point appears earlier or at the same point in the
//! sweep to rhs.
//! @retval false The current point appears after rhs in a plane sweep.
bool SnapPoint::operator<=(const SnapPoint &rhs) const
{
    if (_y == rhs._y)
    {
        return _x <= rhs._x;
    }
    else
    {
        return _y < rhs._y;
    }
}

//! @brief Performs vector addition between points.
//! @param[in] rhs The point to add.
//! @return The sum of the current point and @p rhs.
SnapPoint SnapPoint::operator+(const SnapPoint &rhs) const
{
    return SnapPoint(_x + rhs._x, _y + rhs._y);
}

//! @brief Performs vector subtraction between points.
//! @param[in] rhs The point to subtract.
//! @return The difference between the current point and @p rhs.
SnapPoint SnapPoint::operator-(const SnapPoint &rhs) const
{
    return SnapPoint(_x - rhs._x, _y - rhs._y);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

