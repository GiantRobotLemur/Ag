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
//! @brief A 2-dimensional parametric line segment object represented using
//! real values.
class STRUCT_ALIGN_16 LineSeg2D
{
public:
    // Construction/Destruction
    LineSeg2D() = default;
    LineSeg2D(double x1, double y1, double x2, double y2);
    LineSeg2D(const Point2D &start, const Point2D &end);
    LineSeg2D(const Line2D &line, double length);
    ~LineSeg2D() = default;

    // Accessors
    const Point2D &getStart() const;
    void setStart(const Point2D &start);
    const Point2D &getDelta() const;
    void setDelta(const Point2D &delta);
    Point2D getEnd() const;
    void setEnd(const Point2D &end);
    const double *asVector() const;
    double getLength() const;
    Point2D getPoint(double parameter) const;
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
private:
    // Internal Fields
    Point2D _origin;
    Point2D _delta;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
