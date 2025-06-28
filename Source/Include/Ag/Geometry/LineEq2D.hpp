//! @file Ag/Geometry/LineEq2D.hpp
//! @brief The declaration of an object representing a line in 2-dimensions using
//! the general form line equation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to-
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_LINE_EQUATION_2D_HPP__
#define __AG_GEOMETRY_LINE_EQUATION_2D_HPP__

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Point2D;
class Line2D;
class LineSeg2D;

//! @brief An object representing a line in 2-dimensions using the general form
//! line equation.
class LineEq2D
{
public:
    // Construction/Destruction
    LineEq2D();
    ~LineEq2D() = default;
    LineEq2D(const Line2D &rhs);
    LineEq2D(const LineSeg2D &rhs);
    LineEq2D(const Point2D &first, const Point2D &second);

    // Accessors
    double getA() const;
    double getB() const;
    double getC() const;
    bool isHorizontal() const;
    bool isVertical() const;
    const double *toVector() const;
    bool isParallel(const LineEq2D &rhs) const;
    bool isPerpendicular(const LineEq2D &rhs) const;
    double getAngleTo(const LineEq2D &rhs) const;
    double getAngleCosine(const LineEq2D &rhs) const;
    double getDistanceToPoint(const Point2D &pt) const;
    bool tryCalculateIntersection(const LineEq2D &rhs, Point2D &intersection) const;
    LineEq2D calculatePerpThroughPoint(const Point2D &point) const;
    void toParametricForm(Line2D &parametricLine) const;

    // Operations
    LineEq2D &operator=(const Line2D &rhs);
    LineEq2D &operator=(const LineSeg2D &rhs);
private:
    // Internal Fields
    double _a;
    double _b;
    double _c;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
