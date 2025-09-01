//! @file SnapPoint.hpp
//! @brief The declaration of a 2-dimensional integer point used to snap real
//! points to a grid of arbitrary granularity.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////
#ifndef __AG_GEOMETRY_SNAP_POINT_HPP__
#define __AG_GEOMETRY_SNAP_POINT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include "Ag/Core/Configuration.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A 2-dimensional integer point used to snap real points to a grid of
//! arbitrary granularity.
class SnapPoint
{
public:
    // Public Types
    struct CompareYMajor
    {
        bool operator()(const SnapPoint &lhs, const SnapPoint &rhs) const;
    };

    struct CompareXMajor
    {
        bool operator()(const SnapPoint &lhs, const SnapPoint &rhs) const;
    };

    // Construction/Destruction
    SnapPoint();
    SnapPoint(int64_t x, int64_t y);

    // Accessors
    int64_t getX() const;
    void setX(int64_t x);
    int64_t getY() const;
    void setY(int64_t y);
    void set(int64_t x, int64_t y);
    const int64_t *toArray() const;
    bool lessThanYMajor(const SnapPoint &rhs) const;
    bool lessThanXMajor(const SnapPoint &rhs) const;
    bool lessThanSweep(const SnapPoint &rhs) const;
    int diffYMajor(const SnapPoint &rhs) const;
    int diffXMajor(const SnapPoint &rhs) const;
    int diffSweep(const SnapPoint &rhs) const;

    // Operations
    bool operator==(const SnapPoint &rhs) const;
    bool operator!=(const SnapPoint &rhs) const;
    bool operator<(const SnapPoint &rhs) const;
    bool operator<=(const SnapPoint &rhs) const;
    SnapPoint operator+(const SnapPoint &rhs) const;
    SnapPoint operator-(const SnapPoint &rhs) const;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const SnapPoint &value) {
        return os << '(' << value._x << ", " << value._y << ')';
    }
#endif

private:
    // Internal Fields
    int64_t _x;
    int64_t _y;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
