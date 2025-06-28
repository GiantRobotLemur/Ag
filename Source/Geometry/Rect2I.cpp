//! @file Geometry/Rect2I.cpp
//! @brief The definition of a value representing a 2-dimensional axis-aligned
//! rectangle using discrete integer components.
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

#include "Ag/Core.hpp"

#include "Ag/Geometry/Exceptions.hpp"
#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Rect2I.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Rect2I Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a rectangle in an empty state.
Rect2I::Rect2I()
{
    uint64_t *scalars = asScalars();

    scalars[0] = scalars[1] = 0;
}

//! @brief Constructs a rectangle with a position but zero size.
//! @param[in] origin The initial origin of the rectangle.
Rect2I::Rect2I(const Point2I &origin) :
    _origin(origin),
    _extents(0, 0)
{
}

//! @brief Constructs a rectangle at the origin with a specified size.
//! @param[in] extents The initial size of the rectangle.
Rect2I::Rect2I(const Size2I &extents) :
    _origin(0, 0),
    _extents(extents.getWidth(), extents.getHeight())
{
}

//! @brief Constructs a rectangle with an origin and size.
//! @param[in] origin The initial origin of the rectangle.
//! @param[in] extents The initial size of the rectangle.
Rect2I::Rect2I(const Point2I &origin, const Size2I &extents) :
    _origin(origin),
    _extents(extents.getWidth(), extents.getHeight())
{
}

//! @brief Constructs a rectangle from two opposite corners.
//! @param[in] corner1 The first corner defining the rectangle.
//! @param[in] corner2 The second corner defining the rectangle.
Rect2I::Rect2I(const Point2I &corner1, const Point2I &corner2)
{
    Point2IPair range = corner1.minmax(corner2);

    _origin = range.first;
    _extents = range.second - _origin;
}

//! @brief Construct a rectangle from X and Y corner coordinates.
//! @param[in] x1 The horizontal component of the first corner.
//! @param[in] y1 The vertical component of the first corner.
//! @param[in] x2 The horizontal component of the second corner.
//! @param[in] y2 The vertical component of the second corner.
Rect2I::Rect2I(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
    auto minAndMaxX = std::minmax(x1, x2);
    auto minAndMaxY = std::minmax(y1, y2);

    _origin.getXRef() = minAndMaxX.first;
    _origin.getYRef() = minAndMaxY.first;
    _extents.getXRef() = minAndMaxX.second - minAndMaxX.first;
    _extents.getYRef() = minAndMaxY.second - minAndMaxY.first;
}

//! @brief Constructs a copy of a rectangle.
//! @param[in] rhs The rectangle to copy.
Rect2I::Rect2I(const Rect2I &rhs)
{
    uint64_t *lhsScalars = asScalars();
    const uint64_t *rhsScalars = rhs.asScalars();

    lhsScalars[0] = rhsScalars[0];
    lhsScalars[1] = rhsScalars[1];
}

//! @brief Constructs a rectangle value moved from another.
//! @param[in] rhs The rectangle to move data from.
Rect2I::Rect2I(Rect2I &&rhs) noexcept
{
    uint64_t *lhsScalars = asScalars();
    uint64_t *rhsScalars = rhs.asScalars();

    lhsScalars[0] = rhsScalars[0];
    lhsScalars[1] = rhsScalars[1];
}

//! @brief Determines if the rectangle is in an empty state.
//! @retval true The rectangle is at the origin and has zero size.
//! @retval false The rectangle is not at the origin or has a non-zero size.
bool Rect2I::isEmpty() const
{
    const uint64_t *scalars = asScalars();

    return (scalars[0] == 0) && (scalars[1] == 0);
}

//! @brief Gets the minimum X and Y coordinates of the area enclosed
//! by the rectangle.
const Point2I &Rect2I::getOrigin() const { return _origin; }

//! @brief Sets the position of the minimum X/Y values from which the
//! rectangle extends.
//! @param[in] origin The new origin.
void Rect2I::setOrigin(const Point2I &origin)
{
    _origin = origin;
}

//! @brief Gets the dimensions of the rectangle along the X and Y axes.
const Point2I &Rect2I::getExtents() const { return _extents; }

//! @brief Sets the size of the rectangle.
//! @param[in] extents The new horizontal and vertical dimensions relative to
//! the origin. Negative values will be set to 0.
void Rect2I::setExtents(const Point2I &extents)
{
    _extents = extents.max(Point2I(0, 0));
}

//! @brief Gets the dimensions of the rectangle along the X and Y axes.
Size2I Rect2I::getSize() const
{
    return Size2I(_extents);
}

//! @brief Gets the minimum horizontal position of points enclosed by the rectangle.
int32_t Rect2I::getMinimumX() const { return _origin.getX(); }

//! @brief Sets the minimum horizontal position of points enclosed by the rectangle.
//! @param[in] x The new horizontal minimum.
void Rect2I::setMinimumX(int32_t x) { _origin.setX(x); }

//! @brief Gets the minimum vertical position of points enclosed by the rectangle.
int32_t Rect2I::getMinimumY() const { return _origin.getY(); }

//! @brief Sets the minimum vertical position of points enclosed by the rectangle.
//! @param[in] y The new vertical minimum.
void Rect2I::setMinimumY(int32_t y) { _origin.setY(y); }

//! @brief Gets the smallest horizontal position greater than the set of points
//! enclosed by the rectangle.
int32_t Rect2I::getMaximumX() const
{
    return _origin.getX() + _extents.getX();
}

//! @brief Gets the smallest vertical position greater than the set of points
//! enclosed by the rectangle.
int32_t Rect2I::getMaximumY() const
{
    return _origin.getY() + _extents.getY();
}

//! @brief Gets the current width of the rectangle.
int32_t Rect2I::getWidth() const
{
    return _extents.getX();
}

//! @brief Sets the current width of the rectangle.
//! @param[in] width The new rectangle width.
//! @throw NegativeSizeException If width is less then zero.
void Rect2I::setWidth(int32_t width)
{
    if (width >= 0)
    {
        _extents.setX(width);
    }
    else
    {
        throw NegativeSizeException(true);
    }
}

//! @brief Gets the current height of the rectangle.
int32_t Rect2I::getHeight() const
{
    return _extents.getY();
}

//! @brief Sets the current height of the rectangle.
//! @param[in] height The new rectangle height.
//! @throw NegativeSizeException If height is less then zero.
void Rect2I::setHeight(int32_t height)
{
    if (height >= 0)
    {
        _extents.setY(height);
    }
    else
    {
        throw NegativeSizeException(false);
    }
}

//! @brief Gets a point representing the smallest components greater than the
//! set of points enclosed by the rectangle.
Point2I Rect2I::getExtreme() const
{
    return _origin + _extents;
}

//! @brief Gets a point made up of the minimum horizontal and maximum
//! vertical components of the rectangle.
Point2I Rect2I::getOriginXExtremeY() const
{
    return Point2I(_origin.getX(), _origin.getY() + _extents.getY());
}

//! @brief Gets a point made up of the maximum horizontal and minimum
//! vertical components of the rectangle.
Point2I Rect2I::getExtremeXOriginY() const
{
    return Point2I(_origin.getX() + _extents.getX(), _origin.getY());
}

//! @brief Creates the smallest rectangle which encloses the current one and
//! a specified point.
//! @param[in] rhs The point to encompass.
//! @returns The minimum rectangle enclosing rhs and the current rectangle.
Rect2I Rect2I::combine(const Point2I &rhs) const
{
    Point2I origin = _origin.min(rhs);
    Point2I extreme = rhs.max(_origin + _extents);

    Size2I extents(extreme - origin);

    return Rect2I(origin, extents);
}

//! @brief Creates the smallest rectangle which encloses the current one and
//! another.
//! @param[in] rhs The second rectangle to enclose.
//! @returns The minimum rectangle enclosing rhs and the current rectangle.
Rect2I Rect2I::combine(const Rect2I &rhs) const
{
    Point2I origin = _origin.min(rhs._origin);
    Point2I extreme = rhs.getExtreme().max(_origin + _extents);

    Size2I extents(extreme - origin);

    return Rect2I(origin, extents);
}

//! @brief Determines if a point is within the bounds of the rectangle.
//! @param[in] rhs The point to test for containment.
//! @retval true The point is within the bounds of the rectangle.
//! @retval false The point is outside the rectangle.
bool Rect2I::contains(const Point2I &rhs) const
{
    Point2I lhsExtreme = _origin + _extents;

    return !((rhs.getX() <= _origin.getX()) ||
             (lhsExtreme.getX() <= rhs.getX()) ||
             (rhs.getY() <= _origin.getY()) ||
             (lhsExtreme.getY() <= rhs.getY()));
}

//! @brief Determines if a rectangle encloses space within the current one.
//! @retval true The current rectangle shares some or all of its area with rhs.
//! @retval false The current rectangle does not overlap rhs at all.
bool Rect2I::intersects(const Rect2I &rhs) const
{
    Point2I lhsExtreme = _origin + _extents;
    Point2I rhsExtreme = rhs._origin + rhs._extents;

    return !((rhsExtreme.getX() <= _origin.getX()) ||
             (lhsExtreme.getX() <= rhs._origin.getX()) ||
             (rhsExtreme.getY() <= _origin.getY()) ||
             (lhsExtreme.getY() <= rhs._origin.getY()));
}

//! @brief Attempts to calculate the area shared by this rectangle and another.
//! @param[in] rhs The rectangle to calculate shared area with.
//! @param[out] intersection Receives the rectangle enclosing any shared area.
//! @retval true The two rectangles overlap, intersection is updated to define
//! the area they share.
//! @retval false The two rectangles do not overlap.
bool Rect2I::tryIntersect(const Rect2I &rhs, Rect2I &intersection) const
{
    Point2I lhsExtreme = _origin + _extents;
    Point2I rhsExtreme = rhs._origin + rhs._extents;
    bool hasIntersection = true;

    if ((rhsExtreme.getX() <= _origin.getX()) ||
        (lhsExtreme.getX() <= rhs._origin.getX()) ||
        (rhsExtreme.getY() <= _origin.getY()) ||
        (lhsExtreme.getY() <= rhs._origin.getY()))
    {
        hasIntersection = false;
    }
    else
    {
        intersection._origin = _origin.max(rhs._origin);
        intersection._extents = lhsExtreme.min(rhsExtreme);
    }

    return hasIntersection;
}

//! @brief Resets the rectangle to an empty state.
void Rect2I::clear()
{
    uint64_t *scalars = asScalars();
    scalars[0] = 0;
    scalars[1] = 0;
}

//! @brief Overwrites the current rectangle with the value of another.
//! @param[in] rhs The rectangle to copy.
//! @returns A reference to the current rectangle.
Rect2I &Rect2I::operator=(const Rect2I &rhs)
{
    uint64_t *lhsScalars = asScalars();
    const uint64_t *rhsScalars = rhs.asScalars();
    lhsScalars[0] = rhsScalars[0];
    lhsScalars[1] = rhsScalars[1];

    return *this;
}

//! @brief Overwrites the current rectangle by moving the value of another.
//! @param[in] rhs The rectangle to move.
//! @returns A reference to the current rectangle.
Rect2I &Rect2I::operator=(Rect2I &&rhs) noexcept
{
    uint64_t *lhsScalars = asScalars();
    const uint64_t *rhsScalars = rhs.asScalars();
    lhsScalars[0] = rhsScalars[0];
    lhsScalars[1] = rhsScalars[1];

    return *this;
}

//! @brief Determines if the current rectangle has a value matching another.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The current rectangle has the same value as rhs.
//! @retval false The current rectangle has a different value from rhs.
bool Rect2I::operator==(const Rect2I &rhs) const
{
    const uint64_t *lhsScalars = asScalars();
    const uint64_t *rhsScalars = rhs.asScalars();

    return (lhsScalars[0] == rhsScalars[0]) &&
        (lhsScalars[1] == rhsScalars[1]);
}

//! @brief Determines if the current rectangle has a value matching another.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The current rectangle has a different value from rhs.
//! @retval false The current rectangle has the same value as rhs.
bool Rect2I::operator!=(const Rect2I &rhs) const
{
    const uint64_t *lhsScalars = asScalars();
    const uint64_t *rhsScalars = rhs.asScalars();

    return (lhsScalars[0] != rhsScalars[0]) ||
        (lhsScalars[1] != rhsScalars[1]);
}

//! @brief Updates the current rectangle to encompass a specified point.
//! @param[in] rhs The point to encompass.
void Rect2I::combineTo(const Point2I &rhs)
{
    Point2I extreme = rhs.max(_origin + _extents);
    _origin = _origin.min(rhs);

    _extents = extreme - _origin;
}

//! @brief Updates the rectangle to encompass another rectangle.
//! @param[in] rhs The rectangle to encompass.
void Rect2I::combineTo(const Rect2I &rhs)
{
    Point2I extreme = (rhs._origin + rhs._extents).max(_origin + _extents);
    _origin = _origin.min(rhs._origin);
    _extents = extreme - _origin;
}

//! @brief Gets the value of the rectangle as an array of 2 x 64-bit scalars.
uint64_t *Rect2I::asScalars() noexcept
{
    static_assert(sizeof(Rect2I) == (sizeof(int32_t) * 4),
                  "A Rect2I should be an alias for a vector of 2 32-bit integers.");

    return reinterpret_cast<uint64_t *>(this);
}

//! @brief Gets the value of the rectangle as a read-only array of
//! 2 x 64-bit scalars.
const uint64_t *Rect2I::asScalars() const noexcept
{
    return reinterpret_cast<const uint64_t *>(this);
}

//! @brief Gets the value of the rectangle as an array of 4 x 32-bit integers.
int32_t *Rect2I::asComponents() noexcept
{
    return reinterpret_cast<int32_t *>(this);
}

//! @brief Gets the value of the rectangle as a read-only array of
//! 4 x 32-bit integers.
const int32_t *Rect2I::asComponents() const noexcept
{
    return reinterpret_cast<const int32_t *>(this);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

