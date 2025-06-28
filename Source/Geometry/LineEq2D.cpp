//! @file Geometry/LineEq2D.cpp
//! @brief The definition of an object representing a line in 2-dimensions using
//! the general form line equation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/Exceptions.hpp"
#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/LineEq2D.hpp"
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object representing a valid arbitrary line.
LineEq2D::LineEq2D() :
    _a(0),
    _b(1),
    _c(0)
{
}

//! @brief Constructs an object representing a line converted from an infinite
//! parametric line.
//! @param[in] rhs The parametric line to convert.
LineEq2D::LineEq2D(const Line2D &rhs) :
    _a(-rhs.getDelta().getY()),
    _b(rhs.getDelta().getX()),
    _c(rhs.getOrigin().determinant(rhs.getDelta()))
{
    // As a Line2D has a unit vector for a delta, the implicit form is also
    // normalised.
}

//! @brief Constructs an object representing a line converted from an parametric
//! line segment.
//! @param[in] rhs The parametric line segment to convert.
LineEq2D::LineEq2D(const LineSeg2D &rhs) :
    _a(0),
    _b(0),
    _c(0)
{
    // Ensure the line segment had length.
    double magnitudeSq = rhs.getDelta().magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magnitudeSq))
    {
        throw ZeroLengthVectorException("Attempting to define an infinite line.");
    }
    else
    {
        const Point2D &delta = rhs.getDelta();
        double magnitude = std::sqrt(magnitudeSq);

        _a = -delta.getY() / magnitude;
        _b = delta.getX() / magnitude;
        _c = rhs.getStart().determinant(delta) / magnitude;
    }
}

//! @brief Constructs an object representing an infinite line passing
//! through two points.
//! @param[in] first The first point the line should pass through.
//! @param[in] second The second point the line should pass through.
LineEq2D::LineEq2D(const Point2D &first, const Point2D &second) :
    _a(0),
    _b(0),
    _c(0)
{
    // Ensure the line segment had length.
    Point2D delta = second - first;
    double magnitudeSq = delta.magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magnitudeSq))
    {
        throw ZeroLengthVectorException("Attempting to define an infinite line.");
    }
    else
    {
        const double magnitude = std::sqrt(magnitudeSq);

        _a = -delta.getY() / magnitude;
        _b = delta.getX() / magnitude;
        _c = first.determinant(delta) / magnitude;
    }
}

//! @brief Gets the cosine of the angle the normal to the line makes
//! with the horizontal.
//! @return A value between -1. and 1.0.
double LineEq2D::getA() const { return _a; }

//! @brief Gets the cosine of the angle the normal to the line makes
//! with the vertical.
//! @return A value between -1. and 1.0.
double LineEq2D::getB() const { return _b; }

//! @brief The distance along the normal to the line from the origin to
//! it's intersection point on the line.
//! @return The signed shortest distance from the origin to the line.
double LineEq2D::getC() const { return _c; }

//! @brief Determines if the line is near-enough horizontal.
//! @retval true The line is near-enough horizontal.
//! @retval false The line is not horizontal.
bool LineEq2D::isHorizontal() const
{
    //double aHorz = 0;
    //double bHorz = 1;
    //double cHorz = 0;
    //double cosine = (_a * aHorz) + (_b * bHorz);

    //return NumericDomain::SignedScalar.isNearEqual(std::abs(cosine), 1.0);

    return NumericDomain::SignedScalar.isNearEqual(std::abs(_b), 1.0);
}

//! @brief Determines if the line is near-enough vertical.
//! @retval true The line is near-enough vertical.
//! @retval false The line is not vertical.
bool LineEq2D::isVertical() const
{
    //double aVert = -1;
    //double bVert = 0;
    //double cVert = 0;
    //double cosine = (_a * aVert) + (_b * bVert);

    //return NumericDomain::SignedScalar.isNearEqual(std::abs(cosine), 1.0);

    return NumericDomain::SignedScalar.isNearEqual(std::abs(_a), 1.0);
}

//! @brief Gets the equation of the line as an array of 3 values, a, b and c.
const double *LineEq2D::toVector() const
{
    return &_a;
}

//! @brief Determines if a line is parallel to the current one.
//! @param[in] rhs The line to test.
//! @retval true The current line and rhs are near-enough parallel.
//! @retval false The current line is not parallel to rhs.
bool LineEq2D::isParallel(const LineEq2D &rhs) const
{
    double cosine = getAngleCosine(rhs);

    return NumericDomain::SignedScalar.isNearEqual(std::abs(cosine), 1.0);
}

//! @brief Determines if a line is perpendicular to the current one.
//! @param[in] rhs The line to test.
//! @retval true The current line and rhs are near-enough perpendicular.
//! @retval false The current line is not perpendicular to rhs.
bool LineEq2D::isPerpendicular(const LineEq2D &rhs) const
{
    double cosine = getAngleCosine(rhs);

    return NumericDomain::SignedScalar.isNearZero(cosine);
}

//! @brief Gets the angle between two lines calculated using atan(angle).
//! @param[in] rhs The line to calculate the angle to.
//! @return The angle in radians in the range +/- Pi/2 LH clockwise from
//! the current line to rhs.
double LineEq2D::getAngleTo(const LineEq2D &rhs) const
{
    double numerator = (rhs._a * _b) - (_a * rhs._b);
    double denominator = (_a * rhs._a) + (_b * rhs._b);
    double tanAngle = numerator / denominator;

    return std::atan(tanAngle);
}

//! @brief Calculates the cosine of the angle between the current line
//! and another.
//! @param[in] rhs The line to calculate the angle with.
//! @returns A value between -1.0 and 1.0 giving the cosine of the angle
//! between the current line and rhs.
double LineEq2D::getAngleCosine(const LineEq2D &rhs) const
{
    return (_a * rhs._a) + (_b * rhs._b);
}

//! @brief Calculates the perpendicular distance from the nearest point on the
//! line to a specified position.
//! @param[in] pt The point to measure to.
//! @return The distance to the line, the sign indicates the side of the line
//! the point is on.
double LineEq2D::getDistanceToPoint(const Point2D &pt) const
{
    return (_a * pt.getX()) + (_b * pt.getY()) + _c;
}

//! @brief Attempts to calculate the intersection between this and another line.
//! @param[in] rhs The line to calculate intersection with.
//! @param[out] intersection Receives the point of intersection, if any.
//! @retval true The lines intersect, intersection receives where.
//! @retval false The lines are near-enough parallel as to not intersect.
bool LineEq2D::tryCalculateIntersection(const LineEq2D &rhs,
                                     Point2D &intersection) const
{
    double determinant = (_a * rhs._b) - (rhs._a * _b);
    bool hasIntersection = false;

    if (NumericDomain::SignedScalar.isNearZero(determinant) == false)
    {
        // The lines aren't parallel.
        intersection.set((_b * rhs._c) - (rhs._b * _c),
                         (rhs._a * _c) - (_a * rhs._c));

        intersection /= determinant;
        hasIntersection = true;
    }

    return hasIntersection;
}

//! @brief Calculates the equation of a line perpendicular to the current one
//! which passes through a specified point.
//! @param[in] point The point the new line should pass through.
//! @returns An object representing the perpendicular line.
LineEq2D LineEq2D::calculatePerpThroughPoint(const Point2D &point) const
{
    LineEq2D perp;
    perp._a = _b;
    perp._b = -_a;
    perp._c = (_a * point.getY()) - (_b * point.getX());

    return perp;
}

//! @brief Converts the line equation to an infinite line expressed in
//! parametric form.
//! @param[out] parametricLine Receives the current line in parametric form.
void LineEq2D::toParametricForm(Line2D &parametricLine) const
{
    double denominator = (_a * _a) + (_b * _b);
    double factor = -_c / denominator;
    double rootDenominator = std::sqrt(denominator);

    Point2D origin(_a * factor, _b * factor);
    Point2D delta(_b / rootDenominator, -_a / rootDenominator);

    parametricLine = Line2D(origin, delta);
}

//! @brief Overwrites the line with a conversion of an infinite parametric
//! line.
//! @param[in] rhs The parametric line to convert.
//! @returns A reference to the current object.
LineEq2D &LineEq2D::operator=(const Line2D &rhs)
{
    const Point2D &delta = rhs.getDelta();

    // As a Line2D has a unit vector for a delta, there is no need to
    // normalise the line parameters.
    _a = -delta.getY();
    _b = delta.getX();
    _c = rhs.getOrigin().determinant(delta);

    return *this;
}

//! @brief Overwrites the line with a conversion of a parametric
//! line segment.
//! @param[in] rhs The parametric line segment to convert.
//! @returns A reference to the current object.
LineEq2D &LineEq2D::operator=(const LineSeg2D &rhs)
{
    // Ensure the line segment had length.
    double magnitudeSq = rhs.getDelta().magnitudeSquared();

    if (NumericDomain::SignedScalar.isNearZero(magnitudeSq))
    {
        throw ZeroLengthVectorException("Attempting to define an infinite line.");
    }
    else
    {
        const Point2D &delta = rhs.getDelta();
        const double magnitude = std::sqrt(magnitudeSq);

        _a = -delta.getY() / magnitude;
        _b = delta.getX() / magnitude;
        _c = rhs.getStart().determinant(delta) / magnitude;
    }

    return *this;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

