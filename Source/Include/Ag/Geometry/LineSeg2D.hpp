//! @file Ag/Geometry/LineSeg2D.hpp
//! @brief The declaration of a 2-dimensional parametric line segment object
//! represented using real values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to-
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_LINE_SEG_2D_HPP__
#define __AG_GEOMETRY_LINE_SEG_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/Configuration.hpp"

#include "Ag/Geometry/Point2D.hpp"
#include "Ag/Geometry/LineHelpers.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Point2D;
class Line2D;
class NumericDomain;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Parametric line concept:
//
// class AbstractParametricLineSegment
// {
//      const double *toArray() const noexcept;
//      const Point2D &getStart() const noexcept;
//      void setStart(const Point2D &newStart) noexcept;
//      Point2D getEnd() const noexcept;
//      void setEnd(const Point2D &end) noexcept;
//
//      Point2D getPoint(double parameter) const;
//      double getParameter(const Point2D &position) const;
//      double getDistanceToPoint(const Point2D &pt, double &param) const;
//      Point2DCollection toPolyline(double tolerance, double startParam = 0.0, double endParam = 1.0) const
// }

//! @brief A 2-dimensional parametric line segment object represented using
//! real values.
class STRUCT_ALIGN_16 LineSeg2D
{
private:
    // Internal Fields
    Point2D _start;
    Point2D _end;
public:
    // Construction/Destruction
    LineSeg2D() = default;
    LineSeg2D(double x1, double y1, double x2, double y2);
    LineSeg2D(const Point2D &start, const Point2D &end);
    LineSeg2D(const Line2D &line, double length);
    ~LineSeg2D() = default;

    // Concept
    //! @brief Gets the line segment as a vector of four doubles representing
    //! the start point and direction vector.
    //! @note The pointer is guaranteed to be aligned on a 16-byte boundary.
    constexpr const double *toArray() const noexcept { return _start.toArray(); }

    //! @brief Gets the point at the start of the line segment.
    constexpr const Point2D &getStart() const noexcept { return _start; }
    void setStart(const Point2D &start) noexcept;

    //! @brief Gets the end point of the line segment.
    constexpr const Point2D &getEnd() const noexcept { return _end; }
    void setEnd(const Point2D &end) noexcept;
    Point2D getPoint(double parameter) const;

    double getParameter(const Point2D &position) const;
    double getDistanceToPoint(const Point2D &pt, double &param) const;
    double getPerpDistanceToPoint(const Point2D &pt, double &param) const;

    // Accessors
    Point2D getDelta() const noexcept;
    void setDelta(const Point2D &delta) noexcept;
    double getLength() const;

    double getDeterminant(const Point2D &rhs) const;
    bool tryCalculateIntersection(const NumericDomain &domain, const Line2D &rhs,
                                  Point2D &intersection) const;
    bool tryCalculateIntersection(const NumericDomain &domain, const LineSeg2D &rhs,
                                  Point2D &intersection) const;
    bool tryCalculateIntersectionParam(const NumericDomain &domain,
                                       const LineSeg2D &rhs, double &thisParam,
                                       double &rhsParam) const;

    // Operations
    void reverse();
    void setLine(const Line2D &line, double length);
    void setPointDelta(double originX, double originY, double deltaX, double deltaY);
    void setPointDelta(const Point2D & origin, const Point2D & delta);
    void setPointPoint(double x1, double y1, double x2, double y2);
    void setPointPoint(const Point2D &start, const Point2D &end);
};

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
namespace Line {

template<> double findNearestPointParam<LineSeg2D>(const LineSeg2D &line,
                                                   const Point2D &point,
                                                   double startParam,
                                                   double endParam);

} // namespace Line

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
