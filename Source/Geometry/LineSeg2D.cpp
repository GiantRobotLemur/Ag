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
    _start(x1, y1),
    _end(x2, y2)
{
}

//! @brief Constructs a line segment between two points.
//! @param[in] start The point at the start of the line segment.
//! @param[in] end The point at the end of the line segment.
LineSeg2D::LineSeg2D(const Point2D &start, const Point2D &end) :
    _start(start),
    _end(end)
{
}

//! @brief Constructs a line segment from an infinite line.
//! @param[in] line The infinite line defining an origin and direction.
//! @param[in] length The distance the line segment should extend from its origin.
LineSeg2D::LineSeg2D(const Line2D &line, double length) :
    _start(line.getOrigin()),
    _end((line.getDelta() * length) + _start)
{
}

//! @brief Sets the point at the start of the line segment.
//! @param[in] start The new position of the start of the line segment.
void LineSeg2D::setStart(const Point2D &start) noexcept { _start = start; }

//! @brief Sets the end point of the line segment.
//! @param[in] end The new end point.
void LineSeg2D::setEnd(const Point2D &end) noexcept { _end = end; }

//! @brief Calculates the position of a point along the line segment,
//! possibly before the start point or after the end point.
//! @param[in] parameter The scalar parameter giving the point to find,
//! 0.0 for the start point, 1.0 for the end point, 0.5 for half way, etc.
Point2D LineSeg2D::getPoint(double parameter) const
{
    Point2D delta = _end - _start;

    return delta.fma(parameter, _start);
}

//! @brief Gets the parameter of the point along the line closest to a
//! specified position, ignoring the end points of the line.
//! @param[in] position The position to measure to.
//! @return The parameter of the closest point on the curve, which may be less
//! than 0.0 or greater than 1.0.
double LineSeg2D::getParameter(const Point2D &position) const
{
    // From A Programmer's Geometry : Section 3.2
    // t = -[(xK - xJ)(xL - xK) + (yK - yJ)(yL - yK)] /
    //      [(xL - xK)^2 + (yL - yK)^2]

    // K = _start
    // L = end (xL - xK) = _delta.getX()
    //         (yL - yK) = _delta.getY()
    // J = position
    // K - J = posDelta (xK - xJ) = posDelta.getX()
    //                  (yK - yJ) = posDelta.getY()

    Point2D posDelta = _start - position;
    Point2D delta = _end - _start;
    double denominator = delta.dotProduct(delta);
    double t;

    if (NumericDomain::SignedScalar.isNearZero(denominator))
    {
        // The line has no length, distances should be measured in
        // terms of the start point alone.
        t = 0.0;
    }
    else
    {
        t = -posDelta.dotProduct(delta) / denominator;
    }

    return t;
}

//! @brief Gets the shortest distance to the line from a point.
//! @param[in] pt The point to measure to.
//! @param[out] param Receives the parameter of the point on the line to
//! measure to which will be clamped into the range 0.0 - 1.0.
//! @return The distance from @p pt to the closest point on the segment defined
//! by the parameter returned in @p param.
//! @note If the closest perpendicular point is not between the end points,
//! the parameter and distance will be calculated in terms of the closest
//! end point.
double LineSeg2D::getDistanceToPoint(const Point2D &pt, double &param) const
{
    // From A Programmer's Geometry : Section 3.2
    // t = -[(xK - xJ)(xL - xK) + (yK - yJ)(yL - yK)] /
    //      [(xL - xK)^2 + (yL - yK)^2]

    // r = sqrt{[(xK - xJ) + t(xL - xK)]^2 + [(yK - yJ) + t(yL - yK)]^2}

    // K = _start
    // L = end (xL - xK) = _delta.getX()
    //         (yL - yK) = _delta.getY()
    // J = pt
    // K - J = posDelta (xK - xJ) = posDelta.getX()
    //                  (yK - yJ) = posDelta.getY()

    Point2D posDelta = _start - pt;
    Point2D delta = _end - _start;
    double denominator = delta.dotProduct(delta);

    if (NumericDomain::SignedScalar.isNearZero(denominator))
    {
        // The line has no length, distances should be measured in
        // terms of the start point alone.
        param = 0.0;
    }
    else
    {
        param = -posDelta.dotProduct(delta) / denominator;

        // Clamp the point to a position between the ends of the segment.
        param = std::clamp(param, 0.0, 1.0);
    }

    Point2D deltaT = delta * param;
    Point2D term = posDelta + deltaT;

    // double r = std::sqrt{[posDelta.getX() + deltaT.getX()]^2 +
    //                      [posDelta.getY() + deltaT.getY()]^2}
    double r = std::sqrt(term.dotProduct(term));

    return r;
}

//! @brief Gets the shortest distance to the line from a point.
//! @param[in] pt The point to measure to.
//! @param[out] param Receives the parameter of the point on the line to measure
//! to, the result may not be in the range 0.0 to 1.0.
//! @return The distance from @p pt to the closest point on the line defined
//! by the parameter returned in @p param.
//! @note The closest point detected may not be between the end points of the
//! line segment.
double LineSeg2D::getPerpDistanceToPoint(const Point2D &pt, double &param) const
{
    // From A Programmer's Geometry : Section 3.2
    // t = -[(xK - xJ)(xL - xK) + (yK - yJ)(yL - yK)] /
    //      [(xL - xK)^2 + (yL - yK)^2]

    // r = sqrt{[(xK - xJ) + t(xL - xK)]^2 + [(yK - yJ) + t(yL - yK)]^2}

    // K = _start
    // L = end (xL - xK) = _delta.getX()
    //         (yL - yK) = _delta.getY()
    // J = pt
    // K - J = posDelta (xK - xJ) = posDelta.getX()
    //                  (yK - yJ) = posDelta.getY()

    Point2D posDelta = _start - pt;
    Point2D delta = _end - _start;
    double denominator = delta.dotProduct(delta);

    if (NumericDomain::SignedScalar.isNearZero(denominator))
    {
        // The line has no length, distances should be measured in
        // terms of the start point alone.
        param = 0.0;
    }
    else
    {
        param = -posDelta.dotProduct(delta) / denominator;
    }

    Point2D deltaT = delta * param;
    Point2D term = posDelta + deltaT;

    // double r = std::sqrt{[posDelta.getX() + deltaT.getX()]^2 +
    //                      [posDelta.getY() + deltaT.getY()]^2}
    double r = std::sqrt(term.dotProduct(term));

    return r;
}

//! @brief Gets the vector from the start point to the end point.
Point2D LineSeg2D::getDelta() const noexcept { return _start + _end; }

//! @brief Sets the offset of the end point of the line segment relative
//! to the start point.
//! @param[in] delta The new offset of the end point.
void LineSeg2D::setDelta(const Point2D &delta) noexcept
{
    _end = _start + delta;
}

//! @brief Gets the unsigned length of the line segment.
double LineSeg2D::getLength() const
{
    Point2D delta = _end - _start;
    double magnitudeSq = delta.magnitudeSquared();

    if (NumericDomain::UnsignedScalar.isNearZero(magnitudeSq))
    {
        return 0.0;
    }
    else
    {
        return std::sqrt(magnitudeSq);
    }
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
    Point2D externalDelta = rhs - _start;
    Point2D delta = _end - _start;

    return delta.determinant(externalDelta);
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
    Point2D delta = _end - _start;
    double det = delta.determinant(rhs.getDelta());
    bool hasIntersection = true;

    if (domain.isNearZero(det))
    {
        hasIntersection = false;
    }
    else
    {
        Point2D originDelta = rhs.getOrigin() - _start;
        double thisParam = rhs.getDelta().determinant(originDelta) / det;

        intersection = delta.fma(thisParam, _start);
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
        Point2D delta = _end - _start;
        intersection = delta.fma(thisParam, _start);
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
    Point2D delta = _end - _start;
    Point2D rhsDelta = rhs._end - rhs._start;
    double det = rhsDelta.determinant(delta);
    bool hasIntersection = true;

    if (domain.isNearZero(det))
    {
        hasIntersection = false;
        thisParam = 0.0;
        rhsParam = 0.0;
    }
    else
    {
        Point2D originDelta = rhs._start - _start;
        thisParam = rhsDelta.determinant(originDelta) / det;
        rhsParam = delta.determinant(originDelta) / det;
    }

    return hasIntersection;
}

//! @brief Swaps the start and end points of the line segment.
void LineSeg2D::reverse()
{
    std::swap(_start, _end);
}

//! @brief Overwrites the line segment with properties derived from an
//! infinite line.
//! @param[in] line The infinite line defining an origin and direction.
//! @param[in] length The distance the line segment should extend from its origin.
void LineSeg2D::setLine(const Line2D &line, double length)
{
    _start = line.getOrigin();
    _end = (line.getDelta() * length) + _start;
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
    _start.set(originX, originY);
    _end.set(originX + deltaX, originY + deltaY);
}

//! @brief Overwrites the line segment with a definition given by a start
//! point and vector offset to the end point.
//! @param[in] origin The new start point of the line segment.
//! @param[in] delta The new offset vector from origin to the new end point.
void LineSeg2D::setPointDelta(const Point2D &origin, const Point2D &delta)
{
    _start = origin;
    _end = origin + delta;
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
    _start.set(x1, y1);
    _end.set(x2, y2);
}

//! @brief Overwrites the line segment with a definition given by start
//! and end points.
//! @param[in] start The new start point of the line segment.
//! @param[in] end The new end point of the line segment.
void LineSeg2D::setPointPoint(const Point2D &start, const Point2D &end)
{
    _start = start;
    _end = end;
}

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
namespace Line {
//! @brief A specialization of findNearestPointParam() which doesn't use
//! successive approximation.
//! @param[in] line The line to find the nearest point.
//! @param[in] point The point to track in relation to @p line.
//! @param[in] startParam The parameter on @p line to start searching from.
//! @param[in] endParam The parameter on @p line to not search beyond.
//! @return The parameter value, 0.0 to 1.0 of the point on @p line which is
//! closest to @p point.
template<>
double findNearestPointParam<LineSeg2D>(const LineSeg2D &line, const Point2D &point,
                                        double startParam, double endParam)
{
    auto range = std::minmax(startParam, endParam);

    return std::clamp(line.getParameter(point), range.first, range.second);
}

} // namespace Line

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

