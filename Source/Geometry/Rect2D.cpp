//! @file Geometry/Rect2D.cpp
//! @brief The definition of a value representing a 2-dimensional rectangle
//! using real continuous components.
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
#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/LineEq2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"
#include "Ag/Geometry/Rect2D.hpp"
#include "Ag/Geometry/Size2D.hpp"

namespace Ag {
namespace Geom {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
enum BoundFlags : uint8_t
{
    Bounds_Inside   = 0x00,
    Bounds_Left     = 0x01,
    Bounds_Right    = 0x02,
    Bounds_HorzMask = 0x03,
    Bounds_Bottom   = 0x04,
    Bounds_Top      = 0x08,
    Bounds_VertMask = 0x0C,
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Classifies a point in relation to a rectangle it is being clipped
//! against.
//! @param[in] point The point to classify.
//! @param[in] origin The minimum X and Y components of the area being clipped
//! against.
//! @param[in] extreme The maximum X and Y components of the area being clipped
//! against.
//! @returns A bit field made up of BoundFlags values.
uint8_t classifyPoint(const Point2D &point, const Point2D &origin, const Point2D &extreme)
{
    uint8_t flags = Bounds_Inside;

    if (point.getX() < origin.getX())
    {
        flags |= Bounds_Left;
    }
    else if (point.getX() > extreme.getX())
    {
        flags |= Bounds_Right;
    }

    if (point.getY() < origin.getY())
    {
        flags |= Bounds_Bottom;
    }
    else if (point.getY() > extreme.getY())
    {
        flags |= Bounds_Top;
    }

    return flags;
}

//! @brief Calculates the X value at which a line segment intersects with a
//! horizontal line.
//! @param[in] segment The line segment to calculate intersection with, this
//! must not be horizontal.
//! @param[in] horzY The Y offset through which the horizontal line passes.
//! @return The X coordinate at which segment intersect with the line Y = horzY.
double intersectWithHorizontal(const LineSeg2D &segment, double horzY)
{
    const Point2D &delta = segment.getDelta();
    double deltaY = horzY - segment.getStart().getY();

    return ((delta.getX() * deltaY) / delta.getY()) + segment.getStart().getX();
}

//! @brief Calculates the Y value at which a line segment intersects with a
//! vertical line.
//! @param[in] segment The line segment to calculate intersection with, this
//! must not be vertical.
//! @param[in] vertX The X offset through which the vertical line passes.
//! @return The Y coordinate at which segment intersect with the line X = vertX.
double intersectWithVertical(const LineSeg2D &segment, double vertX)
{
    const Point2D &delta = segment.getDelta();
    double deltaX = vertX - segment.getStart().getX();

    return ((delta.getY() * deltaX) / delta.getX()) + segment.getStart().getY();
}

} // Anonymous namespace.

////////////////////////////////////////////////////////////////////////////////
// Rect2D Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a rectangle in an empty state.
Rect2D::Rect2D() :
    _origin(0.0, 0.0),
    _extents(0.0, 0.0)
{
}

//! @brief Constructs a rectangle with a position but zero size.
//! @param[in] origin The initial origin of the rectangle.
Rect2D::Rect2D(const Point2D &origin) :
    _origin(origin),
    _extents(0.0, 0.0)
{
}

//! @brief Constructs a rectangle at the origin with a specified size.
//! @param[in] extents The initial size of the rectangle.
Rect2D::Rect2D(const Size2D &extents) :
    _origin(0.0, 0.0),
    _extents(extents.getWidth(), extents.getHeight())
{
}

//! @brief Constructs a rectangle with an origin and size.
//! @param[in] origin The initial origin of the rectangle.
//! @param[in] extents The initial size of the rectangle.
Rect2D::Rect2D(const Point2D &origin, const Size2D &extents) :
    _origin(origin),
    _extents(extents.getWidth(), extents.getHeight())
{
}

//! @brief Constructs a rectangle from two opposite corners.
//! @param[in] corner1 The first corner defining the rectangle.
//! @param[in] corner2 The second corner defining the rectangle.
Rect2D::Rect2D(const Point2D &corner1, const Point2D &corner2)
{
    auto range = corner1.minmax(corner2);

    _origin = range.first;
    _extents = range.second - _origin;
}

//! @brief Construct a rectangle from X and Y corner coordinates.
//! @param[in] x1 The horizontal component of the first corner.
//! @param[in] y1 The vertical component of the first corner.
//! @param[in] x2 The horizontal component of the second corner.
//! @param[in] y2 The vertical component of the second corner.
Rect2D::Rect2D(double x1, double y1, double x2, double y2)
{
    auto minAndMaxX = std::minmax(x1, x2);
    auto minAndMaxY = std::minmax(y1, y2);

    _origin.set(minAndMaxX.first, minAndMaxY.first);
    _extents.set(minAndMaxX.second - minAndMaxX.first,
                 minAndMaxY.second - minAndMaxY.first);
}

//! @brief Constructs a copy of a rectangle.
//! @param[in] rhs The rectangle to copy.
Rect2D::Rect2D(const Rect2D &rhs) :
    _origin(rhs._origin),
    _extents(rhs._extents)
{
}

//! @brief Constructs a rectangle value moved from another.
//! @param[in] rhs The rectangle to move data from.
Rect2D::Rect2D(Rect2D &&rhs) noexcept :
    _origin(rhs._origin),
    _extents(rhs._extents)
{
}

//! @brief Determines if the rectangle is in an empty state.
//! @retval true The rectangle is at the origin and has zero size.
//! @retval false The rectangle is not at the origin or has a non-zero size.
bool Rect2D::isEmpty() const
{
    return (_origin.getX() == 0.0) && (_origin.getY() == 0.0) &&
           (_extents.getX() == 0.0) && (_extents.getY() == 0.0);
}

//! @brief Gets the minimum X and Y coordinates of the area enclosed
//! by the rectangle.
const Point2D &Rect2D::getOrigin() const { return _origin; }

//! @brief Gets the dimensions of the rectangle along the X and Y axes.
const Point2D &Rect2D::getExtents() const { return _extents; }

//! @brief Gets the minimum horizontal position of points enclosed by the rectangle.
double Rect2D::getMinimumX() const { return _origin.getX(); }

//! @brief Sets the minimum horizontal position of points enclosed by the rectangle.
//! @param[in] x The new horizontal minimum.
void Rect2D::setMinimumX(double x) { _origin.setX(x); }

//! @brief Gets the minimum vertical position of points enclosed by the rectangle.
double Rect2D::getMinimumY() const { return _origin.getY(); }

//! @brief Sets the minimum vertical position of points enclosed by the rectangle.
//! @param[in] y The new vertical minimum.
void Rect2D::setMinimumY(double y) { _origin.setY(y); }

//! @brief Gets the smallest horizontal position greater than the set of points
//! enclosed by the rectangle.
double Rect2D::getMaximumX() const
{
    return _origin.getX() + _extents.getX();
}

//! @brief Gets the smallest vertical position greater than the set of points
//! enclosed by the rectangle.
double Rect2D::getMaximumY() const
{
    return _origin.getY() + _extents.getY();
}

//! @brief Gets the current width of the rectangle.
double Rect2D::getWidth() const
{
    return _extents.getX();
}

//! @brief Sets the current width of the rectangle.
//! @param[in] width The new rectangle width.
//! @throw NegativeSizeException If width is less then zero.
void Rect2D::setWidth(double width)
{
    if (width < 0)
    {
        throw NegativeSizeException(true);
    }
    else
    {
        _extents.setX(width);
    }
}

//! @brief Gets the current height of the rectangle.
double Rect2D::getHeight() const
{
    return _extents.getY();
}

//! @brief Sets the current height of the rectangle.
//! @param[in] height The new rectangle height.
//! @throw NegativeSizeException If height is less then zero.
void Rect2D::setHeight(double height)
{
    if (height < 0)
    {
        throw NegativeSizeException(false);
    }
    else
    {
        _extents.setY(height);
    }
}

//! @brief Gets a point representing the smallest components greater than the
//! set of points enclosed by the rectangle.
Point2D Rect2D::getExtreme() const
{
    return _origin + Point2D(_extents);
}

//! @brief Gets a point made up of the minimum horizontal and maximum
//! vertical components of the rectangle.
Point2D Rect2D::getOriginXExtremeY() const
{
    return Point2D(_origin.getX(), _origin.getY() + _extents.getY());
}

//! @brief Gets a point made up of the maximum horizontal and minimum
//! vertical components of the rectangle.
Point2D Rect2D::getExtremeXOriginY() const
{
    return Point2D(_origin.getX() + _extents.getX(), _origin.getY());
}

//! @brief Gets the rectangle as a pointer to an array of 4 scalars, the
//! origin X and Y coordinates and the width and height values.
const double *Rect2D::asVector() const noexcept
{
    static_assert(sizeof(Rect2D) == (sizeof(double) * 4),
                  "A Rect2D should be an alias for a vector of 4 doubles.");

    return reinterpret_cast<const double *>(this);
}

//! @brief Creates the smallest rectangle which encloses the current one and
//! a specified point.
//! @param[in] rhs The point to encompass.
//! @returns The minimum rectangle enclosing rhs and the current rectangle.
Rect2D Rect2D::combine(const Point2D &rhs) const
{
    Point2D origin = _origin.min(rhs);
    Point2D extreme = rhs.max(_origin + _extents);

    Size2D extents(extreme - origin);

    return Rect2D(origin, extents);
}

//! @brief Creates the smallest rectangle which encloses the current one and
//! another.
//! @param[in] rhs The second rectangle to enclose.
//! @returns The minimum rectangle enclosing rhs and the current rectangle.
Rect2D Rect2D::combine(const Rect2D &rhs) const
{
    Point2D origin = _origin.min(rhs._origin);
    Point2D extreme = (_origin + _extents).max(rhs._origin + rhs._extents);

    Size2D extents(extreme - origin);

    return Rect2D(origin, extents);
}

//! @brief Determines if a point is within the bounds of the rectangle.
//! @param[in] rhs The point to test for containment.
//! @retval true The point is within the bounds of the rectangle.
//! @retval false The point is outside the rectangle.
bool Rect2D::contains(const Point2D &rhs) const
{
    Point2D lhsExtreme = _origin + _extents;

    return !((rhs.getX() <= _origin.getX()) ||
             (lhsExtreme.getX() <= rhs.getX()) ||
             (rhs.getY() <= _origin.getY()) ||
             (lhsExtreme.getY() <= rhs.getY()));
}

//! @brief Determines if a rectangle encloses space within the current one.
//! @retval true The current rectangle shares some or all of its area with rhs.
//! @retval false The current rectangle does not overlap rhs at all.
bool Rect2D::intersects(const Rect2D &rhs) const
{
    Point2D lhsExtreme = _origin + _extents;
    Point2D rhsExtreme = rhs._origin + rhs._extents;

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
bool Rect2D::tryIntersect(const Rect2D &rhs, Rect2D &intersection) const
{
    Point2D lhsExtreme = _origin + _extents;
    Point2D rhsExtreme = rhs._origin + rhs._extents;
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
        intersection._origin =_origin.max(rhs._origin);
        intersection._extents = lhsExtreme.min(rhsExtreme);
    }

    return hasIntersection;
}

//! @brief Attempts to clip a line segment to the bounds of the rectangle.
//! @param[in] segment The line segment to clip.
//! @param[out] result The clipped segment, if any of the line was within
//! the bounds of the rectangle.
//! @retval true Some part of the line segment was within the bounds of the
//! rectangle, result describes which.
//! @retval false No part of the line segment was inside the rectangle.
bool Rect2D::clip(const LineSeg2D &segment, LineSeg2D &result) const
{
    // Use Cohen-Sutherland line clipping algorithm.
    Point2D extreme = _origin + _extents;
    Point2D start = segment.getStart();
    Point2D end = segment.getEnd();

    NumericDomain domain = combine(Rect2D(start, end)).createDomain();

    uint8_t startOutCode = classifyPoint(start, _origin, extreme);
    uint8_t endOutCode = classifyPoint(end, _origin, extreme);
    bool isInside = false;
    bool isDone = false;

    // Loop while at least one of the points is outside and both
    // points aren't outside on the same side.
    while (!isDone)
    {
        if ((startOutCode | endOutCode) == 0)
        {
            // Both points are inside the line.
            result = LineSeg2D(start, end);
            isInside = true;
            isDone = true;
        }
        else if (startOutCode & endOutCode)
        {
            isDone = true;
        }
        else
        {
            Point2D intersection;
            uint8_t outCode = std::max(startOutCode, endOutCode);

            if (outCode & Bounds_Top)
            {
                intersection.set(intersectWithHorizontal(segment, extreme.getY()),
                                 extreme.getY());
            }
            else if (outCode & Bounds_Bottom)
            {
                intersection.set(intersectWithHorizontal(segment, _origin.getY()),
                                 _origin.getY());
            }
            else if (outCode & Bounds_Right)
            {
                intersection.set(extreme.getX(),
                                 intersectWithVertical(segment, extreme.getX()));
            }
            else // if (outCode & Bounds_Left)
            {
                intersection.set(_origin.getX(),
                                 intersectWithVertical(segment, _origin.getY()));
            }

            if (outCode == startOutCode)
            {
                start = intersection;
                startOutCode = classifyPoint(start, _origin, extreme);
            }
            else // if (outCode == endOutCode)
            {
                end = intersection;
                endOutCode = classifyPoint(end, _origin, extreme);
            }
        }
    }

    return isInside;
}

//! @brief Attempts to clip an infinite parametric line to the bounds of the rectangle.
//! @param[in] line The parametric line to clip.
//! @param[out] result The clipped segment, if any of the line was within
//! the bounds of the rectangle.
//! @retval true Some part of the line was within the bounds of the
//! rectangle, result describes which.
//! @retval false No part of the line was inside the rectangle.
bool Rect2D::clip(const Line2D &line, LineSeg2D &result) const
{
    Point2D extreme = _origin + _extents;
    const Point2D &linePoint = line.getOrigin();
    uint8_t boundsFlags = classifyPoint(linePoint, _origin, extreme);

    bool isInside = false;

    if (line.isVertical())
    {
        if ((boundsFlags & Bounds_HorzMask) == 0)
        {
            // The line is inside the bounds.
            isInside = true;
            result = LineSeg2D(linePoint.getX(), _origin.getY(), linePoint.getX(), extreme.getY());
        }
    }
    else if (line.isHorizontal())
    {
        if ((boundsFlags & Bounds_VertMask) == 0)
        {
            // The line is inside the bounds.
            isInside = true;
            result = LineSeg2D(_origin.getX(), linePoint.getY(), extreme.getX(), linePoint.getY());
        }
    }
    else
    {
        // The line is diagonal.
        // Calculate parameters of the intersections with the bounds of
        // the rectangle. The bounds of the line inside the rectangle will
        // be the middle two points.
        double intersections[4];

        if (line.tryCalculateIntersectionParam(Line2D(_origin, Point2D(1, 0)), intersections[0]) &&
            line.tryCalculateIntersectionParam(Line2D(_origin, Point2D(0, 1)), intersections[1]) &&
            line.tryCalculateIntersectionParam(Line2D(extreme, Point2D(1, 0)), intersections[2]) &&
            line.tryCalculateIntersectionParam(Line2D(extreme, Point2D(0, 1)), intersections[3]))
        {
            std::sort(intersections, intersections + 4);

            // Ensure the mid-point of the middle segment is inside the
            // rectangle.
            double midParam = (intersections[1] + intersections[2]) * 0.5;
            Point2D midPoint = line.getPoint(midParam);

            if (classifyPoint(midPoint, _origin, extreme) == 0)
            {
                Point2D start = line.getPoint(intersections[1]);
                Point2D end = line.getPoint(intersections[2]);

                isInside = true;
                result = LineSeg2D(start, end);
            }
        }
    }

    return isInside;
}

//! @brief Attempts to clip an infinite line to the bounds of the rectangle.
//! @param[in] line The general form equation of the line to clip.
//! @param[out] result The clipped segment, if any of the line was within
//! the bounds of the rectangle.
//! @retval true Some part of the line was within the bounds of the
//! rectangle, result describes which.
//! @retval false No part of the line was inside the rectangle.
bool Rect2D::clip(const LineEq2D &line, LineSeg2D &result) const
{
    // Convert the line equation to parametric form.
    Line2D parametricForm;
    line.toParametricForm(parametricForm);

    return clip(parametricForm, result);
}

//! @brief Resets the rectangle to an empty state.
void Rect2D::clear()
{
    _origin.set(0.0, 0.0);
    _extents.set(0.0, 0.0);
}

//! @brief Overwrites the current rectangle with the value of another.
//! @param[in] rhs The rectangle to copy.
//! @returns A reference to the current rectangle.
Rect2D &Rect2D::operator=(const Rect2D &rhs)
{
    _origin = rhs._origin;
    _extents = rhs._extents;

    return *this;
}

//! @brief Overwrites the current rectangle by moving the value of another.
//! @param[in] rhs The rectangle to move.
//! @returns A reference to the current rectangle.
Rect2D &Rect2D::operator=(Rect2D &&rhs) noexcept
{
    _origin = rhs._origin;
    _extents = rhs._extents;

    return *this;
}

//! @brief Determines if the current rectangle has a value matching another.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The current rectangle has the same value as rhs.
//! @retval false The current rectangle has a different value from rhs.
bool Rect2D::operator==(const Rect2D &rhs) const
{
    return (_origin == rhs._origin) && (_extents == rhs._extents);
}

//! @brief Determines if the current rectangle has a value matching another.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The current rectangle has a different value from rhs.
//! @retval false The current rectangle has the same value as rhs.
bool Rect2D::operator!=(const Rect2D &rhs) const
{
    return (_origin != rhs._origin) || (_extents != rhs._extents);
}

//! @brief Updates the current rectangle to encompass a specified point.
//! @param[in] rhs The point to encompass.
void Rect2D::combineTo(const Point2D &rhs)
{
    Point2D extreme = rhs.max(_origin + _extents);
    _origin = _origin.min(rhs);

    _extents = extreme - _origin;
}

//! @brief Updates the rectangle to encompass another rectangle.
//! @param[in] rhs The rectangle to encompass.
void Rect2D::combineTo(const Rect2D &rhs)
{
    Point2D extreme = (rhs._origin + rhs._extents).max(_origin + _extents);
    _origin = _origin.min(rhs._origin);

    _extents = extreme - _origin;
}

//! @brief Calculates the range of values represented by a rectangle to produce
//! a numeric domain.
//! @return A numeric domain derived from the range of position values encompassed
//! by the rectangle.
NumericDomain Rect2D::createDomain() const
{
    const Point2D extreme = _origin + _extents;

    auto xRange = std::minmax(_origin.getXRef(), extreme.getXRef());
    auto yRange = std::minmax(_origin.getYRef(), extreme.getYRef());

    return NumericDomain(std::min(xRange.first, yRange.first),
                         std::max(xRange.second, yRange.second));
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

