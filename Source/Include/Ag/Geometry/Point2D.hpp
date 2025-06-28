//! @file Ag/Geometry/Point2D.hpp
//! @brief The declaration of a 2-dimensional vector value used as an interface
//! to all geometry primitives.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_POINT2D_HPP__
#define __AG_GEOMETRY_POINT2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <utility>
#include <vector>

#include "Ag/Core/Memory.hpp"
#include "Ag/Geometry/Point2I.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Size2D;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A 2-dimensional vector value used as an interface to all geometry
//! primitives.
class Point2D
{
public:
    // Public Types
    using Component = double;
    using ComponentRef = Component &;
    using ComponentCRef = const Component &;
    using ComponentPtr = Component *;
    using ComponentCPtr = const Component *;
    using Pair = std::pair<Point2D, Point2D>;

    // Construction/Destruction
//! @brief Constructs a point primitive with components set to 0.0.
    constexpr Point2D()  noexcept : _x(0.0), _y(0.0) { }

    //! @brief Constructs a point primitive with components initialised
    //! individually from parameter.
    //! @param[in] x The horizontal component.
    //! @param[in] y The vertical component.
    constexpr Point2D(Point2D::Component x, Point2D::Component y)  noexcept :
        _x(x), _y(y) { }

    //! @brief Constructs a point primitive from an integer equivalent.
    constexpr Point2D(const Point2I &point) noexcept :
        _x(point.getX()), _y(point.getY()) { }

    Point2D(const Size2D &size) noexcept;
    ~Point2D() = default;

    static const Point2D Origin;

    // Accessors
    constexpr Component getX() const noexcept { return _x; }
    constexpr Component getY() const noexcept { return _y; }
    ComponentRef getXRef() noexcept;
    ComponentRef getYRef() noexcept;
    ComponentCRef getXRef() const noexcept { return _x; }
    ComponentCRef getYRef() const noexcept { return _y; }
    void setX(Component x) noexcept;
    void setY(Component y) noexcept;
    void set(Component x, Component y) noexcept;
    ComponentPtr asComponents() noexcept;

    // Operations
    //! @brief Gets the point as an array of component values.
    constexpr ComponentCPtr asComponents() const noexcept { return &_x; }

    //! @brief Determines of the current point has identical component values
    //! to another.
    //! @param[in] rhs The point to compare against.
    //! @retval true The current point has identical components of rhs.
    //! @retval false The current point has at least one component which
    //! differs from rhs.
    constexpr bool operator==(const Point2D &rhs) const noexcept {
        return (_x == rhs._x) && (_y == rhs._y); }

    //! @brief Determines of the current point has a least one differing
    //! component value to another.
    //! @param[in] rhs The point to compare against.
    //! @retval true The current point has at least one component which
    //! differs from rhs.
    //! @retval false The current point has identical components of rhs.
    constexpr bool operator!=(const Point2D &rhs) const noexcept {
        return (_x != rhs._x) || (_y != rhs._y); }

    //! @brief Calculates the sum of the current point and another.
    //! @param[in] rhs The point to add.
    //! @return The sum of the two points.
    constexpr Point2D operator+(const Point2D &rhs) const noexcept {
        return { _x + rhs._x, _y + rhs._y }; }

    //! @brief Calculates the difference between the current point and another.
    //! @param[in] rhs The point to subtract.
    //! @return The difference the two points.
    constexpr Point2D operator-(const Point2D &rhs) const noexcept {
        return { _x - rhs._x, _y - rhs._y }; }

    //! @brief Calculates the negative of the current point.
    constexpr Point2D operator-() const noexcept { return { -_x, -_y }; }

    //! @brief Calculates the product of the current point and another.
    //! @param[in] rhs The point to multiply by.
    //! @return The component-wise product of the two points.
    constexpr Point2D operator*(const Point2D &rhs) const noexcept {
        return { _x * rhs._x, _y * rhs._y }; }

    //! @brief Calculates the product of the current point and a scalar.
    //! @param[in] rhs The scalar to multiply by.
    //! @return The component-wise product of the point and scalar.
    constexpr Point2D operator*(Point2D::Component rhs) const noexcept {
        return { _x * rhs, _y * rhs }; }

    Point2D operator/(const Point2D &rhs) const;
    Point2D operator/(Component rhs) const;
    Point2D &operator+=(const Point2D &rhs);
    Point2D &operator-=(const Point2D &rhs);
    Point2D &operator*=(const Point2D &rhs);
    Point2D &operator*=(Component rhs);
    Point2D &operator/=(const Point2D &rhs);
    Point2D &operator/=(Component rhs);

    //! @brief Calculates the minimum component values between the current and
    //! another point.
    //! @param[in] rhs The point to calculate the minimum with.
    //! @return A point containing minimum component values between the current point
    //! and rhs.
    constexpr Point2D min(const Point2D &rhs) const noexcept {
        return { std::min(_x, rhs._x), std::min(_y, rhs._y) }; }

    //! @brief Calculates the maximum component values between the current and
    //! another point.
    //! @param[in] rhs The point to calculate the maximum with.
    //! @return A point containing maximum component values between the current point
    //! and rhs.
    constexpr Point2D max(const Point2D &rhs) const noexcept {
        return { std::max(_x, rhs._x), std::max(_y, rhs._y) }; }

    //! @brief Calculates the minimum and maximum component values between the
    //! current and another point.
    //! @param[in] rhs The point to calculate the minimum and maximum with.
    //! @return A pair of points containing minimum and maximum component values
    //! respectively.
    constexpr Pair minmax(const Point2D &rhs) const noexcept {
        std::pair<Component, Component> xRange = std::minmax(_x, rhs._x);
        std::pair<Component, Component> yRange = std::minmax(_y, rhs._y);

        return std::make_pair<Point2D, Point2D>({ xRange.first, yRange.first },
                                                { xRange.second, yRange.second });
    }

    Point2D clamp(const Point2D &minimum, const Point2D &maximum) const;
    Component magnitude() const;

    //! @brief Calculates the squared length of the vector.
    constexpr Component magnitudeSquared() const noexcept
    {
        return (_x * _x) + (_y * _y);
    }

    //! @brief Calculates the dot product of the current vector with another.
    //! @param[in] rhs The second vector to create a dot product with.
    //! @return The dot product value.
    constexpr Component dotProduct(const Point2D &rhs) const noexcept
    {
        return (_x * rhs._x) + (_y * rhs._y);
    }

    //! @brief Calculates the signed area of a triangle formed by the current
    //! and another vector.
    //! @param[in] rhs The vector to calculate the determinant with.
    //! @return The signed area of the triangle, the sign indicating the relative
    //! orientation of the two vectors.
    constexpr Component determinant(const Point2D &rhs) const noexcept
    {
        return (_x * rhs._y) - (rhs._x * _y);
    }

    double distance(const Point2D &rhs) const;
    double angleTo(const Point2D &rhs) const;
    Point2D fma(Component scale, const Point2D &translation) const;
    Point2D fma(const Point2D &scale, const Point2D &translation) const;
    Point2D normalised() const;
    void normalise();

    //! @brief Rounds the components to the nearest whole number.
    //! @return An integer point representing the rounded value.
    constexpr Point2I round() const noexcept
    {
        return Point2I(static_cast<Point2I::Component>(std::rint(_x)),
                       static_cast<Point2I::Component>(std::rint(_y)));
    }

    //! @brief Rounds the components to the highest whole number.
    //! @return An integer point representing the rounded value.
    constexpr Point2I ceil() const noexcept
    {
        return Point2I(static_cast<Point2I::Component>(std::ceil(_x)),
                       static_cast<Point2I::Component>(std::ceil(_y)));
    }

    //! @brief Rounds the components to the lowest whole number.
    //! @return An integer point representing the rounded value.
    constexpr Point2I floor() const noexcept
    {
        return Point2I(static_cast<Point2I::Component>(std::floor(_x)),
                       static_cast<Point2I::Component>(std::floor(_y)));
    }

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Point2D &value) {
        return os << '(' << value._x << ", " << value._y << ')';
    }
#endif

    Point2D rotateCW(double angle) const;
    Point2D rotateCCW(double angle) const;

private:
    // Internal Fields
    Component _x;
    Component _y;
};

//! @brief An alias for a std::pair of Point2D values.
using Point2DPair = Point2D::Pair;

//! @brief An alias for a vector of Point2D values which will allow them to
//! be processed by AVX instruction.
using Point2DCollection = std::vector<Point2D, Ag::AlignedAllocator<Point2D, 32>>;

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
