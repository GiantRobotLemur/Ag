//! @file Geometry/QuadBezierCurve2D.cpp
//! @brief The definition of a class representing a parametric quadratic bezier
//! curve.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/LineHelpers.hpp"
#include "Ag/Geometry/QuadBezierCurve2D.hpp"
#include "Ag/Geometry/Rect2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// QuadBezierCurve2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
NumericDomain QuadBezierCurve2D::getDomain() const
{
    Rect2D range(&_start, 3);

    return range.createDomain();
}

//! @brief Constructs a new quadratic bezier curve.
//! @param[in] start The point at which the curve start, i.e. parameter = 0.0.
//! @param[in] ctrl The control point used to define curvature.
//! @param[in] end The point at which the curve ends, i.e. parameter = 1.0.
QuadBezierCurve2D::QuadBezierCurve2D(const Point2D &start, const Point2D &ctrl,
                                     const Point2D &end) :
    _start(start),
    _ctrl(ctrl),
    _end(end)
{
}

//! @brief Sets a new start point.
//! @param[in] newStart The new starting point of the curve.
void QuadBezierCurve2D::setStart(const Point2D &newStart) noexcept
{
    _start = newStart;
}

//! @brief Gets a point on the curve given a linear parameter.
//! @param[in] parameter The parameter, preferably between 0.0 and 1.0.
//! @return The point on the curve corresponding to @p parameter.
Point2D QuadBezierCurve2D::getPoint(double parameter) const
{
    double inverseParam = 1.0 - parameter;

    return (((_start * inverseParam) + (_ctrl * parameter)) * inverseParam) +
           (((_ctrl  * inverseParam) + (_end  * parameter)) * parameter);
}

//! @brief Gets the parameter of the point on the curve closest to a specified position.
//! @param[in] position The position to measure to.
//! @return The parameter of the closest point on the curve.
double QuadBezierCurve2D::getParameter(const Point2D &position) const
{
    return Line::findNearestPointParam(*this, position, 0.0, 1.0);
}

//! @brief Gets the shortest distance to the curve from a point.
//! @param[in] pt The point to measure to.
//! @param[out] param Receives the parameter of the point on the curve to measure to.
//! @return The distance from @p pt to the closest point on the curve defined
//! by the parameter returned in @p param.
double QuadBezierCurve2D::getDistanceToPoint(const Point2D &pt, double &param) const
{
    param = Line::findNearestPointParam(*this, pt, 0.0, 1.0);

    Point2D pointOnCurve = getPoint(param);

    return pointOnCurve.distance(pt);
}

//! @brief Sets the new end point of the curve.
//! @param[in] newEnd The new end point of the curve.
void QuadBezierCurve2D::setEnd(const Point2D &newEnd) noexcept
{
    _end = newEnd;
}

//! @brief Approximates the curve into a run of connected line segments.
//! @param[in] tolerance The maximum distance allowed between the approximation
//! and the actual curve.
//! @param[in] startParam The parameter of the first point on the curve to include.
//! @param[in] endParam The parameter of the last point on the curve to include.
//! @return A collection of points defining a polyline approximating the curve.
Point2DCollection QuadBezierCurve2D::toPolyline(double tolerance,
                                                double startParam /*= 0.0*/,
                                                double endParam /*= 1.0*/) const
{
    return Line::simplifyLinePoints(*this, tolerance, startParam, endParam);
}

//! @brief Sets the new control point defining the curvature of the line.
//! @param[in] newCtrl The new control point.
void QuadBezierCurve2D::setControlPoint(const Point2D &newCtrl) noexcept
{
    _ctrl = newCtrl;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

