//! @file Ag/Geometry/Triangle2D.hpp
//! @brief The declaration of an object representing a triangle in 2-dimensional
//! space defined using double-precision geometry.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_TRIANGLE_2D_HPP__
#define __AG_GEOMETRY_TRIANGLE_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a triangle in 2-dimensional
//! space defined using double-precision geometry.
class Triangle2D
{
public:
    // Construction/Destruction
    Triangle2D(const Point2D *triplet);
    Triangle2D(const Point2D &first, const Point2D &second, const Point2D &third);
    ~Triangle2D() = default;

    // Accessors
    bool isValid() const;
    bool isWoundCW() const;
    bool isWoundCCW() const;
    double getArea() const;
    double getDeterminant() const;
    constexpr const double *toArray() const noexcept { return _vertices->toArray(); }
    constexpr const Point2D *getVertices() const noexcept { return _vertices; }

    // Operations
    void reverseWinding();
private:
    // Internal Fields
    Point2D _vertices[3];
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
