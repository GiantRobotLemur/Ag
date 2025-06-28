//! @file Geometry/LineSeg2D.cpp
//! @brief The definition of a 2-dimensional parametric line segment object
//! represented using real values.
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

#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// LineSeg2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a line segment between two points.
//! @param[in] x1 The horizontal offset of the start point from the origin.
//! @param[in] y1 The vertical offset of the start point from the origin.
//! @param[in] x2 The horizontal offset of the end point from the origin.
//! @param[in] y2 The vertical offset of the end point from the origin.
LineSeg2D::LineSeg2D(double x1, double y1, double x2, double y2) :
    _origin(x1, y1),
    _delta(x2 - x1, y2 - y1)
{
}

//! @brief Constructs a line segment between two points.
//! @param[in] start The point at the start of the line segment.
//! @param[in] end The point at the end of the line segment.
LineSeg2D::LineSeg2D(const Point2D &start, const Point2D &end) :
    _origin(start),
    _delta(end - start)
{
}

//! @brief Constructs a line segment from an infinite line.
//! @param[in] line The infinite line defining an origin and direction.
//! @param[in] length The distance the line segment should extend from its origin.
LineSeg2D::LineSeg2D(const Line2D &line, double length) :
    _origin(line.getOrigin()),
    _delta(line.getDelta() * length)
{
}

//! @brief Gets the point at the start of the line segment.
const Point2D &LineSeg2D::getStart() const { return _origin; }

//! @brief Sets the point at the start of the line segment.
//! @param[in] start The new position of the start of the line segment.
void LineSeg2D::setStart(const Point2D &start) { _origin = start; }

//! @brief Gets the vector from the start point to the end point.
const Point2D &LineSeg2D::getDelta() const { return _delta; }

//! @brief Sets the offset of the end point of the line segment relative
//! to the start point.
//! @param[in] delta The new offset of the end point.
void LineSeg2D::setDelta(const Point2D &delta) { _delta = delta; }

//! @brief Gets the end point of the line segment.
Point2D LineSeg2D::getEnd() const { return _origin + _delta; }

//! @brief Sets the end point of the line segment.
//! @param[in] end The new end point.
void LineSeg2D::setEnd(const Point2D &end) { _delta = end - _origin; }

//! @brief Gets the line segment as a vector of four doubles representing
//! the start point and direction vector.
//! @note The pointer is guaranteed to be aligned on a 16-byte boundary.
const double *LineSeg2D::asVector() const
{
    return reinterpret_cast<const double *>(this);
}

//! @brief Gets the unsigned length of the line segment.
double LineSeg2D::getLength() const
{
    double magnitudeSq = _delta.magnitudeSquared();

    if (NumericDomain::UnsignedScalar.isNearZero(magnitudeSq))
    {
        return 0.0;
    }
    else
    {
        return std::sqrt(magnitudeSq);
    }
}

//! @brief Calculates the position of a point along the line segment,
//! possibly before the start point or after the end point.
//! @param[in] parameter The scalar parameter giving the point to find,
//! 0.0 for the start point, 1.0 for the end point, 0.5 for half way, etc.
Point2D LineSeg2D::getPoint(double parameter) const
{
    return _delta.fma(parameter, _origin);
}

//! @brief Calculates the determinant of a point relative to the line segment.
//! @param[in] rhs The point to measure with respect to the line.
//! @retval &gt;0 The triangle formed by the line segment and point is wound
//! counter-clockwise in a LH system, i.e. the point is logically 'above' the
//! line segment.
//! @retval 0.0 The point is on the infinite line colinear with the segment.
//! @retval &lt;0 The triangle formed by the line segment and point is wound
//! clockwise in a LH system, i.e. the point is logically 'below' the
//! line segment.
//! @details The area of the triangle formed by the line segment and point is
//! the absolute value of 0.5 * the value returned.
double LineSeg2D::getDeterminant(const Point2D &rhs) const
{
    Point2D externalDelta = rhs - _origin;

    return _delta.determinant(externalDelta);
}

//! @brief Calculates the point of intersection between a line segment and
//! an infinite line.
//! @param[in] domain The numeric domain used to tell in the line segments
//! have a valid length.
//! @param[in] rhs The infinite line to test against the current segment
//! for intersection.
//! @param[out] intersection Receives the position of the intersection if
//! it occurs within the bounds of the current segments.
//! @retval true The segment intersects the line between its end points.
//! @retval false the segment is parallel or the intersection is outside
//! the bounds of the end points.
bool LineSeg2D::tryCalculateIntersection(const NumericDomain &domain,
                                         const Line2D &rhs,
                                         Point2D &intersection) const
{
    double det = _delta.determinant(rhs.getDelta());
    bool hasIntersection = true;

    if (domain.isNearZero(det))
    {
        hasIntersection = false;
    }
    else
    {
        Point2D originDelta = rhs.getOrigin() - _origin;
        double thisParam = rhs.getDelta().determinant(originDelta) / det;

        intersection = _delta.fma(thisParam, _origin);
    }

    return hasIntersection;
}

//! @brief Calculates the point of intersection between two line segments.
//! @param[in] domain The numeric domain used to tell in the line segments
//! have a valid length.
//! @param[in] rhs The line segment to test against the current one
//! for intersection.
//! @param[out] intersection Receives the position of the intersection if
//! it occurs within the bounds of the two segments.
//! @retval true The segments intersect between their end points.
//! @retval false the segments are parallel or the intersection is outside
//! the bounds of at least one of the segments.
bool LineSeg2D::tryCalculateIntersection(const NumericDomain &domain,
                                         const LineSeg2D &rhs,
                                         Point2D &intersection) const
{
    double thisParam, rhsParam;
    bool hasIntersection = false;

    if (tryCalculateIntersectionParam(domain, rhs, thisParam, rhsParam) &&
        NumericDomain::UnsignedScalar.trySnapRange(thisParam, 0.0, 1.0) &&
        NumericDomain::UnsignedScalar.trySnapRange(rhsParam, 0.0, 1.0))
    {
        intersection = _delta.fma(thisParam, _origin);
        hasIntersection = true;
    }
    else
    {
        intersection.set(0.0, 0.0);
    }

    return hasIntersection;
}

//! @brief Calculates the parameters of intersection between two line segments.
//! @param[in] domain The numeric domain used to tell in the line segments
//! have a valid length.
//! @param[in] rhs The line segment to test against the current one
//! for intersection.
//! @param[out] thisParam Receives the position of the intersection point on
//! the current line.
//! @param[out] rhsParam Receives the position of the intersection point on
//! the rhs line.
//! @retval true The lines aren't parallel and both thisParam and rhsParam
//! are updated.
//! @retval false The line segments near-enough are parallel.
//! @note The intersection point is always calculated for two non-parallel
//! segments, but both thisParam and rhsParam have to be in the range 0.0 to
//! 1.0 for the intersection to fall between the end points of both segments.
bool LineSeg2D::tryCalculateIntersectionParam(const NumericDomain &domain,
                                              const LineSeg2D &rhs,
                                              double &thisParam,
                                              double &rhsParam) const
{
    double det = rhs._delta.determinant(_delta);
    bool hasIntersection = true;

    if (domain.isNearZero(det))
    {
        hasIntersection = false;
        thisParam = 0.0;
        rhsParam = 0.0;
    }
    else
    {
        Point2D originDelta = rhs._origin - _origin;
        thisParam = rhs._delta.determinant(originDelta) / det;
        rhsParam = _delta.determinant(originDelta) / det;
    }

    return hasIntersection;
}

//! @brief Swaps the start and end points of the line segment.
void LineSeg2D::reverse()
{
    Point2D end = _origin + _delta;
    _origin = end;
    _delta *= -1.0;
}

//! @brief Overwrites the line segment with properties derived from an
//! infinite line.
//! @param[in] line The infinite line defining an origin and direction.
//! @param[in] length The distance the line segment should extend from its origin.
void LineSeg2D::setLine(const Line2D &line, double length)
{
    _origin = line.getOrigin();
    _delta = line.getDelta() * length;
}

//! @brief Overwrites the line segment with a definition given by a start
//! point and vector offset to the end point.
//! @param[in] originX The horizontal offset of the new start point relative
//! to the origin.
//! @param[in] originY The vertical offset of the new start point relative
//! to the origin.
//! @param[in] deltaX Gives the horizontal offset of the new end point relative
//! to originX.
//! @param[in] deltaY Gives the vertical offset of the new end point relative
//! to originY.
void LineSeg2D::setPointDelta(double originX, double originY,
                              double deltaX, double deltaY)
{
    _origin.set(originX, originY);
    _delta.set(deltaX, deltaY);
}

//! @brief Overwrites the line segment with a definition given by a start
//! point and vector offset to the end point.
//! @param[in] origin The new start point of the line segment.
//! @param[in] delta The new offset vector from origin to the new end point.
void LineSeg2D::setPointDelta(const Point2D &origin, const Point2D &delta)
{
    _origin = origin;
    _delta = delta;
}

//! @brief Overwrites the line segment with a definition given by start
//! and end points.
//! @param[in] x1 The horizontal offset of the new start point relative
//! to the origin.
//! @param[in] y1 The vertical offset of the new start point relative
//! to the origin.
//! @param[in] x2 The horizontal offset of the new end point relative
//! to the origin.
//! @param[in] y2 The vertical offset of the new end point relative
//! to the origin.
void LineSeg2D::setPointPoint(double x1, double y1, double x2, double y2)
{
    _origin.set(x1, y1);
    _delta.set(x2 - x1, y2 - y1);
}

//! @brief Overwrites the line segment with a definition given by start
//! and end points.
//! @param[in] start The new start point of the line segment.
//! @param[in] end The new end point of the line segment.
void LineSeg2D::setPointPoint(const Point2D &start, const Point2D &end)
{
    _origin = start;
    _delta = end - start;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

