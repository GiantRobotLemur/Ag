//! @file Geometry/Line2D.cpp
//! @brief The definition of an infinite 2-dimensional parametric line.
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

#include "Ag/Geometry/Exceptions.hpp"
#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Line2D Class Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an infinite line defaulting to horizontal.
Line2D::Line2D() :
    _delta(1, 0)
{
}

//! @brief Constructs an infinite line from a position and a vector.
//! @param[in] originX The horizontal offset of a point on the line.
//! @param[in] originY The vertical offset of a point on the line.
//! @param[in] deltaX The horizontal component of the line's direction.
//! @param[in] deltaY The vertical component of the line's direction.
//! @throw ZeroLengthVectorException If deltaX/Y has a near-zero length.
Line2D::Line2D(double originX, double originY, double deltaX, double deltaY) :
    _origin(originX, originY),
    _delta(deltaX, deltaY)
{
    _delta.normalise();
}

//! @brief Constructs an infinite line from a position and a vector.
//! @param[in] origin The a on the line.
//! @param[in] delta A vector giving the direction of the line.
//! @throw ZeroLengthVectorException If delta has a near-zero length.
Line2D::Line2D(const Point2D &origin, const Point2D &delta) :
    _origin(origin),
    _delta(delta.normalised())
{
}

//! @brief Constructs an infinite line from a line segment.
//! @param[in] lineSeg The line segment providing an origin and direction.
//! @throw ZeroLengthVectorException If lineSeg has a near-zero length.
Line2D::Line2D(const LineSeg2D &lineSeg) :
    _origin(lineSeg.getStart()),
    _delta(lineSeg.getDelta().normalised())
{
}

//! @brief Constructs an infinite parametric line from two points.
//! @param[in] originPt The point which will be the origin of the constructed line.
//! @param[in] otherPt A second point defining the direction of the line.
//! @return A newly constructed infinite parametric line.
Line2D Line2D::fromTwoPoints(const Point2D &originPt, const Point2D &otherPt)
{
    return Line2D(originPt, otherPt - originPt);
}

//! @brief Gets the position of a point on the line.
const Point2D &Line2D::getOrigin() const { return _origin; }

//! @brief Sets the point which defines the position of the line relative
//! to the origin.
//! @param[in] origin The new origin point.
void Line2D::setOrigin(const Point2D &origin) { _origin = origin; }

//! @brief Gets the unit vector defining the direction of the line.
const Point2D &Line2D::getDelta() const { return _delta; }

//! @brief Sets the vector defining the direction of the line.
//! @param[in] delta The new direction vector, which does not have to be a
//! unit vector.
//! @throw DivisionByZeroException If delta has a near-zero length.
void Line2D::setDelta(const Point2D &delta)
{
    _delta = delta.normalised();
}

//! @brief Gets the origin and delta vectors as an array of 4 doubles which is
//! guaranteed to be aligned on a 16-byte boundary.
const double *Line2D::asVector() const
{
    return reinterpret_cast<const double *>(this);
}

//! @brief Gets a point on the line based on its signed distance from the
//! origin point.
//! @param[in] parameter The distance from the line origin of the point to
//! calculate.
//! @returns A point on the line.
Point2D Line2D::getPoint(double parameter) const
{
    return _origin + (_delta * parameter);
}

//! @brief Calculates the parameter with respect to the line of the nearest
//! point on the line to a specified position.
//! @param[in] position The position to calculate the parameter of.
//! @return A linear value specifying the nearest point on the line to
//! position, which can be obtained by passing the result to getPoint().
double Line2D::getParameter(const Point2D &position) const
{
    double param = 0;
    getDistanceToPoint(position, param);

    return param;
}

//! @brief Determines if the line is near-enough horizontal.
//! @retval true The line is near-enough horizontal.
//! @retval false The line has a significant enough vertical component.
bool Line2D::isHorizontal() const
{
    return NumericDomain::SignedScalar.isNearZero(_delta.getY());
}

//! @brief Determines if the line is near-enough vertical.
//! @retval true The line is near-enough vertical.
//! @retval false The line has a significant enough horizontal component.
bool Line2D::isVertical() const
{
    return NumericDomain::SignedScalar.isNearZero(_delta.getX());
}

//! @brief Determines if a line is parallel to the current one.
//! @param[in] rhs The line to test.
//! @retval true The current line and rhs are near-enough parallel.
//! @retval false The current line is not parallel to rhs.
bool Line2D::isParallel(const Line2D &rhs) const
{
    double det = _delta.determinant(rhs._delta);

    return NumericDomain::SignedScalar.isNearZero(det);
}

//! @brief Determines if a line is perpendicular to the current one.
//! @param[in] rhs The line to test.
//! @retval true The current line and rhs are near-enough perpendicular.
//! @retval false The current line is not perpendicular to rhs.
bool Line2D::isPerpendicular(const Line2D &rhs) const
{
    double det = _delta.determinant(rhs._delta);

    return NumericDomain::SignedScalar.isNearEqual(std::abs(det), 1.0);
}

//! @brief Determines if a line is parallel and overlapping with the current one.
//! @param[in] domain The domain used to provide a distance tolerance.
//! @param[in] rhs The line to check for co-linearity.
//! @retval true The lines are parallel and close enough in position and
//! direction to be co-linear.
//! @retval false Either the lines aren't parallel or they are but don't
//! overlap.
bool Line2D::isColinear(const NumericDomain &domain, const Line2D &rhs) const
{
    bool isColinear = false;

    // First determine if the lines are parallel.
    double det = _delta.determinant(rhs._delta);

    if (NumericDomain::SignedScalar.isNearZero(det))
    {
        // Now determine if the lines overlay each other by calculating the
        // distance from a point on one line to the other.
        double param = 0.0;
        double distance = getDistanceToPoint(rhs.getOrigin(), param);

        isColinear = domain.isNearZero(distance);
    }

    return isColinear;
}

//! @brief Calculates the determinant of a point relative to the line segment.
//! @param[in] rhs The point to measure with respect to the line.
//! @retval &gt;0 The point is logically 'above' the line.
//! @retval 0.0 The point is on the line.
//! @retval &lt;0 The point is logically 'below' the line.
double Line2D::getDeterminant(const Point2D &rhs) const
{
    Point2D externalDelta = rhs - _origin;

    return _delta.determinant(externalDelta);
}

//! @brief Calculates the perpendicular distance from the nearest point on the
//! line to a specified position.
//! @param[in] pt The point to measure to.
//! @return The distance to the line, the sign indicates the side of the line
//! the point is on.
double Line2D::getDistanceToPoint(const Point2D &pt) const
{
    double param = 0;

    return getDistanceToPoint(pt, param);
}

//! @brief Calculates the perpendicular distance from the nearest point on the
//! line to a specified position.
//! @param[in] pt The point to measure to.
//! @param[out] param Receives the parameter of the point on the line from
//! which the perpendicular extends
//! @return The distance to the line, the sign indicates the side of the line
//! the point is on.
double Line2D::getDistanceToPoint(const Point2D &pt, double &param) const
{
    Point2D deltaSq = _delta * _delta;

    double fgSq = deltaSq.getX() + deltaSq.getY();
    double distance = 0.0;

    Point2D originDelta = pt - _origin;

    if (NumericDomain::SignedScalar.isNearZero(fgSq))
    {
        // The line has no length, simply measure from the line's
        // origin point to pt.
        distance = originDelta.magnitudeSquared();

        if (NumericDomain::UnsignedScalar.isNearZero(distance))
        {
            distance = 0;
        }
        else
        {
            distance = std::sqrt(distance);
        }

        param = 0.0;
    }
    else
    {
        double fg = _delta.getX() * _delta.getY();

        Point2D lineDelta((deltaSq.getY() * originDelta.getX()) - (fg * originDelta.getY()),
                          (deltaSq.getX() * originDelta.getY()) - (fg * originDelta.getX()));

        distance = lineDelta.magnitudeSquared() / fgSq;

        // Parameter of point given by:
        param = originDelta.dotProduct(_delta) / fgSq;
    }

    return distance;
}

//! @brief Attempts to calculate the intersection between this and another line.
//! @param[in] rhs The line to calculate intersection with.
//! @param[out] intersection Receives the point of intersection, if any.
//! @retval true The lines intersect, intersection receives where.
//! @retval false The lines are near-enough parallel as to not intersect.
bool Line2D::tryCalculateIntersection(const Line2D &rhs, Point2D &intersection) const
{
    double intersectionParam;
    bool hasIntersection = true;

    if (tryCalculateIntersectionParam(rhs, intersectionParam))
    {
        intersection = _delta.fma(intersectionParam, _origin);
    }
    else
    {
        intersection.set(0.0, 0.0);
        hasIntersection = false;
    }

    return hasIntersection;
}

//! @brief Attempts to calculate the linear parameter of the point of
//! intersection between this and another line.
//! @param[in] rhs The line to calculate intersection with.
//! @param[out] lhsParam Receives the point of intersection, expressed as a linear
//! distance parameter from the origin point of the current line.
//! @retval true The lines intersect, intersection receives where.
//! @retval false The lines are near-enough parallel as to not intersect.
bool Line2D::tryCalculateIntersectionParam(const Line2D &rhs, double &lhsParam) const
{
    double rhsParam = 0;

    return tryCalculateIntersectionParam(rhs, lhsParam, rhsParam);
}

//! @brief Attempts to calculate the linear parameter of the point of
//! intersection between this and another line.
//! @param[in] rhs The line to calculate intersection with.
//! @param[out] lhsParam Receives the point of intersection, expressed as a linear
//! distance parameter, from the origin point of the current line.
//! @param[out] rhsParam Receives the point of intersection, expressed as a linear
//! distance parameter, from the origin point of rhs.
//! @retval true The lines intersect, intersection receives where.
//! @retval false The lines are near-enough parallel as to not intersect.
bool Line2D::tryCalculateIntersectionParam(const Line2D &rhs, double &lhsParam,
                                           double &rhsParam) const
{
    double det = rhs._delta.determinant(_delta);
    bool hasIntersection = true;

    if (NumericDomain::SignedScalar.isNearZero(det))
    {
        hasIntersection = false;
        lhsParam = 0.0;
        rhsParam = 0.0;
    }
    else
    {
        Point2D originDelta = rhs._origin - _origin;
        lhsParam = rhs._delta.determinant(originDelta) / det;
        rhsParam = _delta.determinant(originDelta) / det;
    }

    return hasIntersection;
}

//! @brief Overwrites the line with a new one derived from a line segment.
//! @param[in] rhs The line segment providing the origin and direction of
//! the new line.
//! @throw ZeroLengthVectorException If rhs has a near-zero length.
Line2D &Line2D::operator=(const LineSeg2D &rhs)
{
    double magSq = rhs.getDelta().magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magSq))
    {
        throw ZeroLengthVectorException("Defining an infinite line from a line segment.");
    }

    _origin = rhs.getStart();
    _delta = rhs.getDelta().normalised();

    return *this;
}

//! @brief Defines the line using a point on it and a direction vector.
//! @param[in] originX The horizontal offset of a point on the line.
//! @param[in] originY The vertical offset of a point on the line.
//! @param[in] deltaX The horizontal component of the line's direction.
//! @param[in] deltaY The vertical component of the line's direction.
//! @throw ZeroLengthVectorException If deltaX/Y has a near-zero length.
void Line2D::setPointDelta(double originX, double originY,
                           double deltaX, double deltaY)
{
    double magnitudeSq = (deltaX * deltaX) + (deltaY * deltaY);

    if (NumericDomain::SignedScalar.isNearZero(magnitudeSq))
    {
        throw ZeroLengthVectorException("Defining an infinite line.");
    }

    double magnitude = std::sqrt(magnitudeSq);

    _origin.set(originX, originY);
    _delta.set(deltaX, deltaY);
    _delta /= magnitude;
}

//! @brief Defines the line using a point on it and a direction vector.
//! @param[in] origin The a on the line.
//! @param[in] delta A vector giving the direction of the line.
//! @throw ZeroLengthVectorException If delta has a near-zero length.
void Line2D::setPointDelta(const Point2D &origin, const Point2D &delta)
{
    double magSq = delta.magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magSq))
    {
        throw ZeroLengthVectorException("Defining an infinite line.");
    }

    _origin = origin;
    _delta = delta / std::sqrt(magSq);
}

//! @brief Defines the line using two points on it.
//! @param[in] x1 The horizontal component of the first point on the line.
//! @param[in] y1 The vertical component of the first point on the line.
//! @param[in] x2 The horizontal component of the second point on the line.
//! @param[in] y2 The vertical component of the second point on the line.
//! @throw ZeroLengthVectorException If the distance between the two points
//! is near-enough zero.
void Line2D::setPointPoint(double x1, double y1, double x2, double y2)
{
    Point2D delta(x2 - x1, y2 - y1);

    double magSq = delta.magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magSq))
    {
        throw ZeroLengthVectorException("Defining an infinite line.");
    }

    _origin.set(x1, y1);
    _delta = delta / std::sqrt(magSq);
}

//! @brief Defines the line using two points on it.
//! @param[in] origin A point on the line which will become its origin.
//! @param[in] waypoint Another point on the line used to calculate the
//! unit direction vector.
//! @throw ZeroLengthVectorException If the distance between the two points
//! is near-enough zero.
void Line2D::setPointPoint(const Point2D &origin, const Point2D &waypoint)
{
    Point2D delta = waypoint - origin;
    double magSq = delta.magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magSq))
    {
        throw ZeroLengthVectorException("Defining an infinite line.");
    }

    _origin = origin;
    _delta = delta / std::sqrt(magSq);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

