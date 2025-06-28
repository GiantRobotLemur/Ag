//! @file Ag/Geometry/Point2I.hpp
//! @brief The declaration of a 32-bit integer-based 2-dimensional vector value
//! used as an interface to all integer geometry primitives.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_POINT_2I_HPP__
#define __AG_GEOMETRY_POINT_2I_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <utility>

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Size2I;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A 32-bit integer-based 2-dimensional vector value used as an
//! interface to all integer geometry primitives.
class Point2I
{
public:
    // Public Types
    using Component = int32_t;
    using ComponentRef = Component &;
    using ComponentCRef = const Component &;
    using ComponentPtr = Component *;
    using ComponentCPtr = const Component *;
    using Pair = std::pair<Point2I, Point2I>;

    // Construction/Destruction
    //! @brief Constructs a point primitive with components set to 0.
    constexpr Point2I() noexcept : _x(0), _y(0) {};

    //! @brief Constructs a point primitive with components initialised
    //! individually from parameter.
    //! @param[in] x The horizontal component.
    //! @param[in] y The vertical component.
    constexpr Point2I(Component x, Component y) noexcept : _x(x), _y(y) {};

    Point2I(const Size2I &size) noexcept;
    ~Point2I() = default;

    static const Point2I Origin;

    // Accessors
    //! @brief Gets a copy of the horizontal component.
    constexpr Component getX() const noexcept { return _x; }

    //! @brief Gets a copy of the vertical component.
    constexpr Component getY() const noexcept { return _y; }

    //! @brief Gets a read-only reference to the horizontal component.
    constexpr ComponentCRef getXRef() const noexcept { return _x; }

    //! @brief Gets a read-only reference to the vertical component.
    constexpr ComponentCRef getYRef() const noexcept { return _y; }

    ComponentRef getXRef() noexcept;
    ComponentRef getYRef() noexcept;
    void setX(Component x) noexcept;
    void setY(Component y) noexcept;
    void set(Component x, Component y) noexcept;
    ComponentPtr asComponents() noexcept;

    //! @brief Gets the point as an array of component values.
    constexpr ComponentCPtr asComponents() const noexcept
    {
        return &_x;
    }

    // Operations

    //! @brief Determines of the current point has identical component values
    //! to another.
    //! @param[in] rhs The point to compare against.
    //! @retval true The current point has identical components of rhs.
    //! @retval false The current point has at least one component which
    //! differs from rhs.
    constexpr bool operator==(const Point2I &rhs) const
    {
        return (_x == rhs._x) && (_y == rhs._y);
    }

    //! @brief Determines of the current point has a least one differing
    //! component value to another.
    //! @param[in] rhs The point to compare against.
    //! @retval true The current point has at least one component which
    //! differs from rhs.
    //! @retval false The current point has identical components of rhs.
    constexpr bool operator!=(const Point2I &rhs) const
    {
        return (_x != rhs._x) || (_y != rhs._y);
    }

    //! @brief Calculates the sum of the current point and another.
    //! @param[in] rhs The point to add.
    //! @return The sum of the two points.
    constexpr Point2I operator+(const Point2I &rhs) const
    {
        return { _x + rhs._x, _y + rhs._y };
    }

    //! @brief Calculates the difference between the current point and another.
    //! @param[in] rhs The point to subtract.
    //! @return The difference the two points.
    constexpr Point2I operator-(const Point2I &rhs) const
    {
        return { _x - rhs._x, _y - rhs._y };
    }

    //! @brief Calculates the negative of the current point.
    constexpr Point2I operator-() const
    {
        return { -_x, -_y };
    }

    //! @brief Calculates the product of the current point and another.
    //! @param[in] rhs The point to multiply by.
    //! @return The component-wise product of the two points.
    constexpr Point2I operator*(const Point2I &rhs) const
    {
        return { _x * rhs._x, _y * rhs._y };
    }

    //! @brief Calculates the product of the current point and a scalar.
    //! @param[in] rhs The scalar to multiply by.
    //! @return The component-wise product of the two points.
    constexpr Point2I operator*(Component rhs) const
    {
        return { _x * rhs, _y * rhs };
    }

    Point2I operator/(const Point2I &rhs) const;
    Point2I operator/(Component rhs) const;
    Point2I &operator+=(const Point2I &rhs);
    Point2I &operator-=(const Point2I &rhs);
    Point2I &operator*=(const Point2I &rhs);
    Point2I &operator*=(Component rhs);
    Point2I &operator/=(const Point2I &rhs);
    Point2I &operator/=(Component rhs);

    //! @brief Calculates the minimum component values between the current and
    //! another point.
    //! @param[in] rhs The point to calculate the minimum with.
    //! @return A point containing minimum component values between the current point
    //! and rhs.
    constexpr Point2I min(const Point2I &rhs) const noexcept
    {
        return { std::min(_x, rhs._x), std::min(_y, rhs._y) };
    }

    //! @brief Calculates the maximum component values between the current and
    //! another point.
    //! @param[in] rhs The point to calculate the maximum with.
    //! @return A point containing maximum component values between the current point
    //! and rhs.
    constexpr Point2I max(const Point2I &rhs) const noexcept
    {
        return { std::max(_x, rhs._x), std::max(_y, rhs._y) };
    }

    //! @brief Calculates the minimum and maximum component values between the
    //! current and another point.
    //! @param[in] rhs The point to calculate the minimum and maximum with.
    //! @return A pair of points containing minimum and maximum component values
    //! respectively.
    constexpr Pair minmax(const Point2I &rhs) const noexcept
    {
        std::pair<int32_t, int32_t> xRange = std::minmax(_x, rhs._x);
        std::pair<int32_t, int32_t> yRange = std::minmax(_y, rhs._y);

        return std::make_pair<Point2I, Point2I>({ xRange.first, yRange.first },
                                                { xRange.second, yRange.second });
    }

    //! @brief Clamps the component values of the point to a specified range.
    //! @param[in] minimum Represents minimum allowed component values.
    //! @param[in] maximum Represents maximum allowed component values.
    //! @return A point with component values forced into the specified range.
    constexpr Point2I clamp(const Point2I &minimum,
                            const Point2I &maximum) const noexcept
    {
        return { std::clamp(_x, minimum._x, maximum._x),
                 std::clamp(_y, minimum._y, maximum._y) };
    }

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Point2I &value) {
        return os << '(' << value._x << ", " << value._y << ')';
    }
#endif

private:
    // Internal Fields
    Component _x;
    Component _y;
};

//! @brief An alias for a std::pair of Point2I values.
using Point2IPair = Point2I::Pair;

//! @brief An alias for a vector of integer 2D points which aligns allocations
//! on 32-byte boundaries.
using Point2ICollection = std::vector<Point2I, Ag::AlignedAllocator<Point2I, 32>>;

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
