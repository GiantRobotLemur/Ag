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

//! @brief Constructs a line from raw equation components.
//! @param[in] a The cosine of the angle a perpendicular makes with the horizontal.
//! @param[in] b The cosine of the angle a perpendicular makes with the vertical.
//! @param[in] c The distance from the origin to the nearest point.
//! @throws ArgumentException If (a^2 + b^2) is near-enough 0, as the definition is invalid.
//! @note The equation parameters will be normalised so that (a^2 + b^2) == 1.0.
LineEq2D::LineEq2D(double a, double b, double c) :
    _a(a),
    _b(b),
    _c(c)
{
    // Ensure the line is normalised.
    double magnitude = (_a * _a) + (_b * _b);

    if (NumericDomain::SignedScalar.isNearZero(magnitude))
    {
        throw ArgumentException("The values do not represent a valid equation of a line.", "a/b");
    }
    else if (NumericDomain::SignedScalar.isNearEqual(magnitude, 1.0) == false)
    {
        double magRoot = std::sqrt(magnitude);

        _a /= magRoot;
        _b /= magRoot;
        _c /= magRoot;
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

//! @brief Creates the equation of a vertical line.
//! @param[in] throughX The X value at every point on the line.
//! @return A newly created vertical line.
LineEq2D LineEq2D::createVertical(double throughX)
{
    return LineEq2D(-1, 0, throughX);
}

//! @brief Creates the equation of a horizontal line.
//! @param[in] throughY The Y value at every point on the line.
//! @return A newly created horizontal line.
LineEq2D LineEq2D::createHorizontal(double throughY)
{
    return LineEq2D(0, 1, -throughY);
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

//! @brief Calculates the closest point on the line to the origin.
//! @return A position on the line.
Point2D LineEq2D::getOrigin() const
{
    double denominator = (_a * _a) + (_b * _b);
    double factor = -_c / denominator;

    return { _a * factor, _b * factor };
}

//! @brief Gets the gradient of the line as a unit vector.
//! @return A gradient of the line, the negative of the gradient would be an
//! equally valid representation.
Point2D LineEq2D::getDelta() const
{
    double denominator = (_a * _a) + (_b * _b);
    double rootDenominator = std::sqrt(denominator);

    return { _b / rootDenominator, -_a / rootDenominator };
}

//! @brief Determines if the line is near-enough horizontal.
//! @retval true The line is near-enough horizontal.
//! @retval false The line is not horizontal.
bool LineEq2D::isHorizontal() const
{
    return NumericDomain::SignedScalar.isNearEqual(std::abs(_b), 1.0);
}

//! @brief Determines if the line is near-enough vertical.
//! @retval true The line is near-enough vertical.
//! @retval false The line is not vertical.
bool LineEq2D::isVertical() const
{
    return NumericDomain::SignedScalar.isNearEqual(std::abs(_a), 1.0);
}

//! @brief Gets the equation of the line as an array of 3 values, a, b and c.
const double *LineEq2D::toVector() const
{
    return &_a;
}

//! @brief Determines if the lines represented by this and another line equation
//! are near-enough co-linear, even if they have different definitions.
//! @param[in] domain The numeric domain used to compare distances to the origin.
//! @param[in] rhs The equation of the line to compare against this one.
//! @retval true The lines near-enough overlap along their entire length.
//! @retval false The lines do not overlap.
bool LineEq2D::isColinear(const NumericDomain &domain, const LineEq2D &rhs) const
{
    return isParallel(rhs) &&
        domain.isNearZero(getDistanceToPoint(rhs.getOrigin()));
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

