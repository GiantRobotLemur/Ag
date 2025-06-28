//! @file Geometry/Triangle2D.cpp
//! @brief The definition of an object representing a triangle in 2-dimensional
//! space defined using double-precision geometry.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/Triangle2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Triangle2D Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Initialises the triangle from an array of three points.
//! @param[in] triplet The array of points used to form the triangle.
Triangle2D::Triangle2D(const Point2D *triplet)
{
    std::uninitialized_copy_n(triplet, 3, _vertices);
}

//! @brief Initialises the triangle from three individual points.
//! @param[in] first The first point in the sequence defining the triangle.
//! @param[in] second The second point in the sequence defining the triangle.
//! @param[in] third The third point in the sequence defining the triangle.
Triangle2D::Triangle2D(const Point2D &first, const Point2D &second,
                       const Point2D &third)
{
    _vertices[0] = first;
    _vertices[1] = second;
    _vertices[2] = third;
}

//! @brief Determines of the triangle is formed from three different points.
//! @retval true The triangle is formed from three unique points.
//! @retval false The triangle has no area.
bool Triangle2D::isValid() const
{
    return getDeterminant() != 0.0;
}

//! @brief Determines of the triangle is wound clockwise in the LH system.
//! @retval true The triangle is wound in a clockwise direction given the
//! order in which its points were specified.
//! @retval false The triangle is wound counter clockwise or invalid.
bool Triangle2D::isWoundCW() const
{
    return getDeterminant() < 0.0;
}

//! @brief Determines of the triangle is wound counter-clockwise in the LH system.
//! @retval true The triangle is wound in a counter-clockwise direction given
//! the order in which its points were specified.
//! @retval false The triangle is wound clockwise or invalid.
bool Triangle2D::isWoundCCW() const
{
    return getDeterminant() > 0.0;
}

//! @brief Calculates the non-negative area of the triangle.
double Triangle2D::getArea() const
{
    return std::abs(getDeterminant() * 0.5);
}

//! @brief Calculates the determinant of the two vectors the first point makes
//! with the second and third points, in that order.
//! @return The scalar determinant. In a LH system, positive values indicate a
//! CCW winding, negative, a CW winding and zero, a line segment.
double Triangle2D::getDeterminant() const
{
    Point2D deltaSecond = _vertices[1] - _vertices[0];
    Point2D deltaThird = _vertices[2] - _vertices[0];

    return deltaSecond.determinant(deltaThird);
}

//! @brief Reverses the current winding of the polygon.
void Triangle2D::reverseWinding()
{
    Point2D temp = _vertices[1];
    _vertices[1] = _vertices[2];
    _vertices[2] = temp;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

