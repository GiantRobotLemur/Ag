//! @file Geometry/Rect2I.hpp
//! @brief The declaration of a value representing a 2-dimensional axis-aligned
//! rectangle using discrete integer components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_RECT_2I_HPP__
#define __AG_GEOMETRY_RECT_2I_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/Configuration.hpp"

#include "Ag/Geometry/Point2I.hpp"
#include "Ag/Geometry/Size2I.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A value representing a 2-dimensional axis-aligned rectangle using
//! discrete integer components.
class STRUCT_ALIGN_16 Rect2I
{
public:
    // Construction/Destruction
    Rect2I();
    Rect2I(const Point2I &origin);
    Rect2I(const Size2I &extents);
    Rect2I(const Point2I &origin, const Size2I &extents);
    Rect2I(const Point2I &corner1, const Point2I &corner2);
    Rect2I(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
    Rect2I(const Rect2I &rhs);
    Rect2I(Rect2I &&rhs) noexcept;
    ~Rect2I() = default;

    // Accessors
    bool isEmpty() const;
    const Point2I &getOrigin() const;
    void setOrigin(const Point2I &origin);
    const Point2I &getExtents() const;
    void setExtents(const Point2I &extents);
    Size2I getSize() const;
    int32_t getMinimumX() const;
    void setMinimumX(int32_t x);
    int32_t getMinimumY() const;
    void setMinimumY(int32_t y);
    int32_t getMaximumX() const;
    int32_t getMaximumY() const;
    int32_t getWidth() const;
    void setWidth(int32_t width);
    int32_t getHeight() const;
    void setHeight(int32_t height);
    Point2I getExtreme() const;
    Point2I getOriginXExtremeY() const;
    Point2I getExtremeXOriginY() const;
    Rect2I combine(const Point2I &rhs) const;
    Rect2I combine(const Rect2I &rhs) const;
    bool contains(const Point2I &rhs) const;
    bool intersects(const Rect2I &rhs) const;
    bool tryIntersect(const Rect2I &rhs, Rect2I &intersection) const;

    // Operations
    void clear();
    Rect2I &operator=(const Rect2I &rhs);
    Rect2I &operator=(Rect2I &&rhs) noexcept;
    bool operator==(const Rect2I &rhs) const;
    bool operator!=(const Rect2I &rhs) const;
    void combineTo(const Point2I &rhs);
    void combineTo(const Rect2I &rhs);

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Rect2I &value) {
        return os << value._origin << " + " << value._extents;
    }
#endif

private:
    // Internal Functions
    uint64_t *asScalars() noexcept;
    const uint64_t *asScalars() const noexcept;
    int32_t *asComponents() noexcept;
    const int32_t *asComponents() const noexcept;

    // Internal Fields
    Point2I _origin;
    Point2I _extents;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
