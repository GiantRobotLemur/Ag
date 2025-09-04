//! @file Geometry/Arc2D.cpp
//! @brief The definition of a parametric line segment representing a portion
//! of an elliptical arc.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

#include "Ag/Geometry/Angle.hpp"
#include "Ag/Geometry/Arc2D.hpp"
#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/LineHelpers.hpp"
#include "Ag/Geometry/NumericDomain.hpp"

namespace Ag {
namespace Geom {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
// TODO: Replace this with a proper SIMD-capable matrix transform.
struct LinearTransform
{
    // Public Fields
    double M[4];

    LinearTransform()
    {
        M[0] = 1;
        M[1] = 0;
        M[2] = 0;
        M[3] = 1;
    }

    LinearTransform(const std::initializer_list<double> &matrixValues)
    {
        if (matrixValues.size() != std::size(M))
            throw ArgumentException("Invalid number of matrix parameters.", "matrixValues");

        std::copy_n(matrixValues.begin(), std::size(M), M);
    }

    LinearTransform(const double *matrixValues)
    {
        std::copy_n(matrixValues, std::size(M), M);
    }

    //! @brief Overwrites the matrix with a rotation in the Z axis.
    //! @param[in] angleInRadians The rotation angle counter-clockwise in a left handed system.
    void LinearTransform::makeRotationXY(double angleInRadians)
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        M[0] = cosAngle;
        M[1] = -sinAngle;
        M[2] = sinAngle;
        M[3] = cosAngle;
    }

    //! @brief Multiplies the transform by a rotation in the Z axis.
    //! @param[in] angleInRadians The rotation angle counter-clockwise in a left handed system.
    void LinearTransform::appendRotationXY(double angleInRadians)
    {
        double cosAngle = std::cos(angleInRadians);
        double sinAngle = std::sin(angleInRadians);

        LinearTransform rotation({ cosAngle, -sinAngle,
                                   sinAngle,  cosAngle });

        *this *= rotation;
    }

    //! @brief Multiplies the current matrix by a scale transform along the X
    //! and Y axes.
    //! @param[in] scaleXY The scales along the X and Y axis to combine.
    void LinearTransform::appendScaleXY(const Point2D &scaleXY)
    {
        LinearTransform scale({ scaleXY.getX(),             0,
                                             0, scaleXY.getY() } );

        *this *= scale;
    }

    LinearTransform inverse() const
    {
        double determinant = (M[0] * M[3]) - (M[1] * M[2]);

        // Divide all matrix components by the calculated determinant in the
        // following order: [ ( D / determinant) (-B / determinant) ]
        //                  [ (-C / determinant) ( A / determinant) ]
        return LinearTransform({  M[3] / determinant, -M[1] / determinant,
                                 -M[2] / determinant,  M[0] / determinant });
    }

    LinearTransform &operator*=(const LinearTransform &rhs)
    {
        double lhs[4];
        std::copy_n(M, std::size(M), lhs);

        M[0] = (lhs[0] * rhs.M[0]) + (lhs[1] * rhs.M[2]);
        M[1] = (lhs[0] * rhs.M[1]) + (lhs[1] * rhs.M[3]);
        M[2] = (lhs[2] * rhs.M[0]) + (lhs[3] * rhs.M[2]);
        M[3] = (lhs[2] * rhs.M[1]) + (lhs[3] * rhs.M[3]);

        return *this;
    }

    Point2D operator*(const Point2D &rhs) const
    {
        return Point2D((rhs.getX() * M[0]) + (rhs.getY() * M[2]),
                       (rhs.getX() * M[1]) + (rhs.getY() * M[3]));
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Arc2D::Parameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty set of Arc2D parameters.
Arc2D::Parameters::Parameters() :
    //LinearTransform ToEllipse;
    _circleRadius(0),
    _startAngle(0),
    _angleDelta(0)
{
    _toEllipse[0] = 1;
    _toEllipse[1] = 0;
    _toEllipse[2] = 0;
    _toEllipse[3] = 1;
}

//! @brief Constructs a set of pre-calculated Arc2D interpolation parameters.
//! @param[in] arc The definition of the elliptical arc to interpolate.
Arc2D::Parameters::Parameters(const Arc2D &arc)
{
    // The following code is inspired by  Grandfather of Windows Programming
    // Charles Petzold:
    // http://www.charlespetzold.com/blog/2008/01/mathematics-of-arcsegment.html
    // Check out the WaybackMachine as this article was deleted on 2024.

    // Calculate a factors to scale the ellipse into a circle.
    _circleRadius = arc._ellipseAxes.getY();
    Point2D scale(_circleRadius / arc._ellipseAxes.getX(), 1.0);

    // Create a transform to allow us to work with a uniform circle rather
    // than an ellipse.
    LinearTransform toCircle;

    toCircle.makeRotationXY(-arc._ellipseAngle);
    toCircle.appendScaleXY(scale);

    Point2D circleArcStart = toCircle * arc._start;
    Point2D circleArcEnd = toCircle * arc._end;
    LineSeg2D circleArcChord(circleArcStart, circleArcEnd);

    // Calculate the centre of the circle.

    // Get the point half way between start and end point.
    Point2D circleArcMid = circleArcChord.getPoint(0.5);
    Point2D chordVector = circleArcChord.getDelta();
    Point2D vectorToCentre;

    // Note: Deliberate boolean/boolean comparison.
    if (arc._isLargeSweep == arc._isClockwiseSweep)
    {
        vectorToCentre.set(-chordVector.getY(),
                            chordVector.getX());
    }
    else
    {
        vectorToCentre.set( chordVector.getY(),
                           -chordVector.getX());
    }

    // Create an infinite line from the chord mid-point which will pass through
    // the centre of the circle.
    Line2D lineToCentre(circleArcMid, vectorToCentre);

    double halfChordLength = circleArcChord.getLength() / 2.0;
    double distanceToCentre = std::sqrt((_circleRadius * _circleRadius) -
                                        (halfChordLength * halfChordLength));

    _circleCentre = lineToCentre.getPoint(distanceToCentre);

    // Calculate the angle of the start and end points in the circular domain.
    double startAngle = (circleArcChord.getStart() - _circleCentre).angleFromOrigin();
    double endAngle = (circleArcChord.getEnd() - _circleCentre).angleFromOrigin();

    // Note: Another deliberate comparison of boolean values.
    if (arc._isLargeSweep == (std::abs(endAngle - startAngle) < Angle::Pi))
    {
        if (startAngle < endAngle)
        {
            startAngle += Angle::Pi2;
        }
        else
        {
            endAngle += Angle::Pi2;
        }
    }

    _startAngle = startAngle;
    _angleDelta = endAngle - startAngle;

    // Create a transform which will allow us to transform points from the
    // circular coordinate system back to the ellipse.
    LinearTransform toEllipse = toCircle.inverse();

    std::copy_n(toEllipse.M, 4, _toEllipse);
}

//! @brief Calculates the position of a point on the arc.
//! @param[in] parameter The parameter value, preferably between 0.0 and 1.0.
//! @return The position of the point corresponding to the value of @p parameter
//! on the arc.
Point2D Arc2D::Parameters::getPoint(double parameter) const
{
    // Calculate an angle from the line parameter.
    double pointAngle = _startAngle + (parameter * _angleDelta);

    // Calculate a point on the circle from the angle.
    Point2D scale(std::cos(pointAngle), std::sin(pointAngle));

    Point2D circlePoint = _circleCentre + (Point2D(_circleRadius, _circleRadius) * scale);

    // Transform the point from the circular coordinate system to the
    // elliptical system.
    LinearTransform toEllipse(_toEllipse);
    Point2D ellipsePoint = toEllipse * circlePoint;

    return ellipsePoint;
}

//! @brief Gets the parameter of the point on the arc closest to a specified position.
//! @param[in] position The position to measure to.
//! @return The parameter of the closest point on the arc.
double Arc2D::Parameters::getParameter(const Point2D &position) const
{
    LinearTransform toEllipse(_toEllipse);
    LinearTransform toCircle = toEllipse.inverse();
    NumericDomain domain(0, _circleRadius);

    // Calculate the position in circular space.
    Point2D circularPosition = toCircle * position;

    // Ensure the point is not at the centre.
    Point2D delta = circularPosition - _circleCentre;
    double circularDistanceSq = delta.magnitudeSquared();

    if (domain.isNearZero(circularDistanceSq))
        return 0;

    Angle pointAngle(delta.angleFromOrigin());
    Angle angleOffset = pointAngle - Angle(_startAngle);
    double offset = angleOffset.toRadians();
    double nearestAngle = std::clamp(offset, 0.0, _angleDelta);

    return nearestAngle / _angleDelta;
}

//! @brief Gets the shortest distance to the arc from a point.
//! @param[in] position The point to measure to.
//! @param[out] param Receives the parameter of the point on the arc to measure to.
//! @return The distance from @p pt to the closest point on the arc defined
//! by the parameter returned in @p param.
double Arc2D::Parameters::getDistanceToPoint(const Point2D &position, double &param) const
{
    LinearTransform toEllipse(_toEllipse);
    LinearTransform toCircle = toEllipse.inverse();
    NumericDomain domain(0, _circleRadius);

    // Calculate the position in circular space.
    Point2D circularPosition = toCircle * position;

    // Ensure the point is not at the centre.
    Point2D delta = circularPosition - _circleCentre;
    double circularDistanceSq = delta.magnitudeSquared();

    if (domain.isNearZero(circularDistanceSq))
        return 0;

    Angle angleOffset = Angle(delta.angleFromOrigin()) - Angle(_startAngle);
    double offset = angleOffset.toRadians();
    double nearestAngle = std::clamp(offset, 0.0, _angleDelta);

    param = nearestAngle / _angleDelta;

    // Calculate an angle from the line parameter.
    double pointAngle = _startAngle + (param * _angleDelta);

    // Calculate a point on the circle from the angle.
    Point2D scale(std::cos(pointAngle), std::sin(pointAngle));
    Point2D circlePoint = _circleCentre + (Point2D(_circleRadius, _circleRadius) * scale);

    // Transform the point from the circular coordinate system to the
    // elliptical system.
    Point2D ellipsePoint = toEllipse * circlePoint;

    return ellipsePoint.distance(position);
}

//! @brief Gets the centre of the projected ellipse.
Point2D Arc2D::Parameters::getCentre() const
{
    LinearTransform toEllipse(_toEllipse);

    return toEllipse * _circleCentre;
}

//! @brief Gets a point on the semimajor axis of the ellipse
//! @param[in] yScale The scale, 1.0 or -1.0 to get points on the ellipse,
//! or 0.0 for the centre.
//! @return A point on the semimajor axis of the projected ellipse.
Point2D Arc2D::Parameters::getMajorAxisPoint(double yScale /*= 1.0*/) const
{
    LinearTransform toEllipse(_toEllipse);
    Point2D axisDelta(0, _circleRadius * yScale);

    return toEllipse * (_circleCentre + axisDelta);
}

//! @brief Gets a point on the semiminor axis of the projected ellipse.
//! @param[in] xScale The scale, 1.0 or -1.0 to get points on the ellipse,
//! or 0.0 for the centre.
//! @return A point on the semiminor axis of the projected ellipse.
Point2D Arc2D::Parameters::getMinorAxisPoint(double xScale /*= 1.0*/) const
{
    LinearTransform toEllipse(_toEllipse);
    Point2D axisDelta(_circleRadius * xScale, 0);

    return toEllipse * (_circleCentre + axisDelta);
}

////////////////////////////////////////////////////////////////////////////////
// Arc2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty elliptical arc segment.
Arc2D::Arc2D() :
    _ellipseAngle(0),
    _isLargeSweep(true),
    _isClockwiseSweep(false)
{
}

//! @brief Constructs an object representing a line traced around the perimeter
//! of an ellipse.
//! @param[in] start The point at the beginning of the line on the perimeter
//! of the ellipse.
//! @param[in] end The point at the end of the line tracing the perimeter of
//! the ellipse.
//! @param[in] axes The radii of the ellipse relative to the X and Y
//! axes in its local coordinate system.
//! @param[in] angle The angle of the ellipse coordinate system rotated
//! clockwise from the X axis.
//! @param[in] isLargeSweep Use the longest sweep given the possible outline
//! traces between the start and end points.
//! @param[in] isClockwise Use the clockwise sweep given the possible outline
//! trace directions between the start and end points.
Arc2D::Arc2D(const Point2D &start, const Point2D &end, const Point2D &axes,
             double angle, bool isLargeSweep, bool isClockwise) :
    _start(start),
    _end(end),
    _ellipseAxes(axes),
    _ellipseAngle(angle),
    _isLargeSweep(isLargeSweep),
    _isClockwiseSweep(isClockwise)
{
    double arcDistanceSq = (_end - _start).magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(arcDistanceSq))
    {
        throw ArgumentException("Arc end points are coincident.", "start/end");
    }

    double arcDistance = std::sqrt(arcDistanceSq);

    // TODO: Produce a more certain test for segment greater than diameter. The
    // test below will not always catch when the arc distance is too long, but never
    // be wrong when it does throw.
    double maxDiameter = std::max(axes.getX(), axes.getY()) * 2.0;

    if (arcDistance > maxDiameter)
    {
        throw ArgumentException("Arc length is larger than the diameter.", "axes");
    }
}

//! @brief Constructs an arc segment from a transformable set of parameters.
//! @param[in] start The start point of the segment.
//! @param[in] end The end point of the segment.
//! @param[in] ellipseCentre The centre of the ellipse.
//! @param[in] ellipseXRadius The point level with the centre at the extreme
//! of the rotated ellipse's X axis.
//! @param[in] ellipseYRadius The point level with the centre at the extreme
//! of the rotated ellipse's Y axis.
//! @param[in] isLargeSweep Use the longest sweep given the possible outline
//! traces between the start and end points.
//! @param[in] isClockwise Use the clockwise sweep given the possible outline
//! trace directions between the start and end points.
Arc2D::Arc2D(const Point2D &start, const Point2D &end,
             const Point2D &ellipseCentre,
             const Point2D &ellipseXRadius,
             const Point2D &ellipseYRadius,
             bool isLargeSweep, bool isClockwise) :
    _start(start),
    _end(end),
    _ellipseAngle(0),
    _isLargeSweep(isLargeSweep),
    _isClockwiseSweep(isClockwise)
{
    Point2D delta = _end - _start;
    double arcLengthSq = delta.magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(arcLengthSq))
    {
        throw ArgumentException("Arc end points are coincident.", "start/end");
    }

    Point2D deltaToX = ellipseXRadius - ellipseCentre;
    Point2D deltaToY = ellipseYRadius - ellipseCentre;

    _ellipseAngle = deltaToX.angleFromOrigin();
    _ellipseAxes.set(deltaToX.magnitude(), deltaToY.magnitude());

    if (deltaToY.determinant(deltaToX) > 0)
    {
        // The coordinate system has swapped over since the arc was encoded.
        _isClockwiseSweep = !_isClockwiseSweep;
    }
}

//! @brief Sets the point at the start of the arc.
//! @param[in] newStart The new start position.
void Arc2D::setStart(const Point2D &newStart) noexcept
{
    _start = newStart;
}

//! @brief Sets the point at the end of the arc.
//! @param[in] end The new end position.
void Arc2D::setEnd(const Point2D &end) noexcept
{
    _end = end;
}

//! @brief Calculates the position of a point on the arc.
//! @param[in] parameter The parameter value, preferably between 0.0 and 1.0.
//! @return The position of the point corresponding to the value of @p parameter
//! on the arc.
Point2D Arc2D::getPoint(double parameter) const
{
    Parameters arcParameters(*this);

    return arcParameters.getPoint(parameter);
}

//! @brief Gets the parameter of the point on the arc closest to a specified position.
//! @param[in] position The position to measure to.
//! @return The parameter of the closest point on the arc.
double Arc2D::getParameter(const Point2D &position) const
{
    Parameters arcParameters(*this);

    return arcParameters.getParameter(position);
}

//! @brief Gets the shortest distance to the arc from a point.
//! @param[in] position The point to measure to.
//! @param[out] param Receives the parameter of the point on the arc to measure to.
//! @return The distance from @p pt to the closest point on the arc defined
//! by the parameter returned in @p param.
double Arc2D::getDistanceToPoint(const Point2D &pt, double &param) const
{
    Parameters arcParameters(*this);

    return arcParameters.getDistanceToPoint(pt, param);
}

//! @brief Approximates the arc into a run of connected line segments.
//! @param[in] tolerance The maximum distance allowed between the approximation
//! and the actual arc.
//! @param[in] startParam The parameter of the first point on the arc to include.
//! @param[in] endParam The parameter of the last point on the arc to include.
//! @return A collection of points defining a polyline approximating the arc.
Point2DCollection Arc2D::toPolyline(double tolerance,
                                    double startParam /*= 0.0*/,
                                    double endParam /*= 1.0*/) const
{
    Parameters arcParameters(*this);

    return Line::simplifyLinePoints<Parameters>(arcParameters, tolerance,
                                                startParam, endParam);
}

//! @brief Sets the radius of the ellipse along the Y axis before rotation.
//! @param[in] yRadius The new distance from the centre to the arc on the
//! Y axis before the rotation is applied.
void Arc2D::setMajorRadius(double yRadius) noexcept
{
    _ellipseAxes.setY(yRadius);
}

//! @brief Sets the radius of the ellipse along the X axis before rotation.
//! @param[in] xRadius The new distance from the centre to the arc on the
//! X axis before the rotation is applied.
void Arc2D::setMinorRadius(double xRadius) noexcept
{
    _ellipseAxes.setX(xRadius);
}

//! @brief Sets whether to use the clockwise sweep given the two
//! possible outline traces directions between the start and end points.
//! @param[in] isCW Set to true if the segment will trace clockwise
//! about the ellipse from the start to the end point, false for clockwise.
void Arc2D::setClockwiseSweep(bool isCW)
{
    _isClockwiseSweep = isCW;
}

//! @brief Sets whether to use the longest sweep given the two possible outline
//! traces between the start and end points.
//! @param[in] isLargeSweep Set to true to trace the larger segment, false for
//! the shorter segment.
void Arc2D::setLargeSweep(bool isLargeSweep)
{
    _isLargeSweep = isLargeSweep;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

