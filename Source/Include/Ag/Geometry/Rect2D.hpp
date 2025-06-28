//! @file Ag/Geometry/Rect2D.hpp
//! @brief The declaration of a value representing a 2-dimensional rectangle
//! using real continuous components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_RECT_2D_HPP__
#define __AG_GEOMETRY_RECT_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/Configuration.hpp"

#include "NumericDomain.hpp"
#include "Point2D.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Size2D;
class Line2D;
class LineEq2D;
class LineSeg2D;

//! @brief A value representing a 2-dimensional rectangle using real continuous
//! components.
class STRUCT_ALIGN_16 Rect2D
{
public:
    // Construction/Destruction
    Rect2D();
    Rect2D(const Point2D &origin);
    Rect2D(const Size2D &extents);
    Rect2D(const Point2D &origin, const Size2D &extents);
    Rect2D(const Point2D &corner1, const Point2D &corner2);
    Rect2D(double x1, double y1, double x2, double y2);
    Rect2D(const Rect2D &rhs);
    Rect2D(Rect2D &&rhs) noexcept;
    ~Rect2D() = default;

    // Accessors
    bool isEmpty() const;
    const Point2D &getOrigin() const;
    const Point2D &getExtents() const;
    double getMinimumX() const;
    void setMinimumX(double x);
    double getMinimumY() const;
    void setMinimumY(double y);
    double getMaximumX() const;
    double getMaximumY() const;
    double getWidth() const;
    void setWidth(double width);
    double getHeight() const;
    void setHeight(double height);
    Point2D getExtreme() const;
    Point2D getOriginXExtremeY() const;
    Point2D getExtremeXOriginY() const;
    const double *asVector() const noexcept;
    Rect2D combine(const Point2D &rhs) const;
    Rect2D combine(const Rect2D &rhs) const;
    bool contains(const Point2D &rhs) const;
    bool intersects(const Rect2D &rhs) const;
    bool tryIntersect(const Rect2D &rhs, Rect2D &intersection) const;
    bool clip(const LineSeg2D &segment, LineSeg2D &result) const;
    bool clip(const Line2D &line, LineSeg2D &result) const;
    bool clip(const LineEq2D &line, LineSeg2D &result) const;

    // Operations
    void clear();
    Rect2D &operator=(const Rect2D &rhs);
    Rect2D &operator=(Rect2D &&rhs) noexcept;
    bool operator==(const Rect2D &rhs) const;
    bool operator!=(const Rect2D &rhs) const;
    void combineTo(const Point2D &rhs);
    void combineTo(const Rect2D &rhs);
    NumericDomain createDomain() const;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Rect2D &value) {
        return os << value._origin << " + " << value._extents;
    }
#endif

private:
    // Internal Fields
    Point2D _origin;
    Point2D _extents;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
