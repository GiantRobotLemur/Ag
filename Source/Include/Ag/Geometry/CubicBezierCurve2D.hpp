//! @file Ag/Geometry/CubicBezierCurve2D.hpp
//! @brief The declaration of class representing a parametric cubic bezier
//! curve.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_CUBIC_BEZIER_CURVE_2D_HPP__
#define __AG_GEOMETRY_CUBIC_BEZIER_CURVE_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class representing a parametric cubic bezier curve.
class CubicBezierCurve2D
{
private:
    // Internal Types

    // Internal Fields
    Point2D _start;
    Point2D _ctrl1;
    Point2D _ctrl2;
    Point2D _end;

    // Internal Functions
    NumericDomain getDomain() const;
public:
    // Construction/Destruction
    CubicBezierCurve2D() = default;
    CubicBezierCurve2D(const Point2D &start, const Point2D &ctrl1,
                       const Point2D &ctrl2, const Point2D &end);
    ~CubicBezierCurve2D() = default;

    // Concept
    constexpr const double *toArray() const noexcept { return _start.toArray(); }
    constexpr const Point2D &getStart() const noexcept { return _start; }
    void setStart(const Point2D &newStart) noexcept;
    constexpr const Point2D &getEnd() const noexcept { return _end; }
    void setEnd(const Point2D &newEnd) noexcept;

    Point2D getPoint(double parameter) const;
    double getParameter(const Point2D &position) const;
    double getDistanceToPoint(const Point2D &pt, double &param) const;
    Point2DCollection toPolyline(double tolerance, double startParam = 0.0, double endParam = 1.0) const;

    // Accessors
    constexpr const Point2D &getControlPoint1() const noexcept { return _ctrl1; }
    void setControlPoint1(const Point2D &newCtrl) noexcept;
    constexpr const Point2D &getControlPoint2() const noexcept { return _ctrl2; }
    void setControlPoint2(const Point2D &newCtrl) noexcept;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
