//! @file Ag/Geometry/Line2D.hpp
//! @brief The declaration of an infinite 2-dimensional parametric line.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to-
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_LINE_2D_HPP__
#define __AG_GEOMETRY_LINE_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Configuration.hpp"

#include "Point2D.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Point2D;
class LineSeg2D;
class NumericDomain;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An infinite 2-dimensional parametric line.
class STRUCT_ALIGN_16 Line2D
{
public:
    // Construction/Destruction
    Line2D();
    Line2D(double originX, double originY, double deltaX, double deltaY);
    Line2D(const Point2D &origin, const Point2D &delta);
    Line2D(const LineSeg2D &lineSeg);
    static Line2D fromTwoPoints(const Point2D &originPt, const Point2D &otherPt);
    ~Line2D() = default;

    // Accessors
    const Point2D &getOrigin() const;
    void setOrigin(const Point2D &origin);
    const Point2D &getDelta() const;
    void setDelta(const Point2D &delta);
    const double *asVector() const;
    Point2D getPoint(double parameter) const;
    double getParameter(const Point2D &position) const;
    bool isHorizontal() const;
    bool isVertical() const;
    bool isParallel(const Line2D &rhs) const;
    bool isPerpendicular(const Line2D &rhs) const;
    bool isColinear(const NumericDomain &domain, const Line2D &rhs) const;
    double getDeterminant(const Point2D &rhs) const;
    double getDistanceToPoint(const Point2D &pt) const;
    double getDistanceToPoint(const Point2D &pt, double &param) const;
    bool tryCalculateIntersection(const Line2D &rhs, Point2D &intersection) const;
    bool tryCalculateIntersectionParam(const Line2D &rhs, double &lhsParam) const;
    bool tryCalculateIntersectionParam(const Line2D &rhs, double &lhsPparam, double &rhsParam) const;

    // Operations
    Line2D &operator=(const LineSeg2D &rhs);
    void setPointDelta(double originX, double originY, double deltaX, double deltaY);
    void setPointDelta(const Point2D &origin, const Point2D &delta);
    void setPointPoint(double x1, double y1, double x2, double y2);
    void setPointPoint(const Point2D &origin, const Point2D &waypoint);
private:
    // Internal Fields
    Point2D _origin;
    Point2D _delta;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
