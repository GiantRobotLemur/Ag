//! @file Ag/Geometry/Size2I.hpp
//! @brief The declaration of a value representing a 2-dimensional size using
//! discrete integer components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_SIZE_2I_HPP__
#define __AG_GEOMETRY_SIZE_2I_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../Core/Configuration.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Point2I;

//! @brief A value representing a 2-dimensional size using discrete integer
//! components.
class STRUCT_ALIGN_8 Size2I
{
public:
    // Construction/Destruction

    //! @brief Constructs a 2-dimensional size value which has component values of 0.
    constexpr Size2I() noexcept : _width(0), _height(0) {};
    Size2I(int32_t width, int32_t height);
    Size2I(const Size2I &rhs);
    explicit Size2I(const Point2I &rhs);
    Size2I(Size2I &&rhs) noexcept;
    ~Size2I() = default;

    // Accessors
    bool isEmpty() const;

    //! @brief Gets the width component of the size.
    constexpr int32_t getWidth() const noexcept { return _width; };

    void setWidth(int32_t width);

    //! @brief Gets the height component of the size.
    constexpr int32_t getHeight() const noexcept { return _height; };

    void setHeight(int32_t height);
    void set(int32_t width, int32_t height);

    // Operations
    void clear();
    Size2I &operator=(const Size2I &rhs);
    Size2I &operator=(Size2I &&rhs) noexcept;
    Size2I &operator=(const Point2I &rhs);
    bool operator==(const Size2I &rhs) const;
    bool operator!=(const Size2I &rhs) const;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Size2I &value) {
        return os << '[' << value._width << " x " << value._height << ']';
    }
#endif

private:
    // Internal Functions
    uint64_t &asScalar() noexcept;
    const uint64_t &asScalar() const noexcept;

    // Internal Fields
    int32_t _width;
    int32_t _height;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
