//! @file Ag/Geometry/Size2D.hpp
//! @brief The declaration of a value representing a 2-dimensional size using
//! real continuous components.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_SIZE_2D_HPP__
#define __AG_GEOMETRY_SIZE_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Configuration.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class Point2D;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A value representing a 2-dimensional size using real continuous
//! components.
class STRUCT_ALIGN_16 Size2D
{
public:
    // Construction/Destruction
    Size2D();
    Size2D(double width, double height);
    Size2D(const Size2D &rhs);
    explicit Size2D(const Point2D &rhs);
    Size2D(Size2D &&rhs) noexcept;
    ~Size2D() = default;

    // Accessors
    bool isEmpty() const;
    double getWidth() const;
    void setWidth(double width);
    double getHeight() const;
    void setHeight(double height);
    void set(double width, double height);
    const double *asVector() const noexcept;

    // Operations
    void clear();
    Size2D &operator=(const Size2D &rhs);
    Size2D &operator=(Size2D &&rhs) noexcept;
    Size2D &operator=(const Point2D &rhs);
    bool operator==(const Size2D &rhs) const;
    bool operator!=(const Size2D &rhs) const;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Size2D &value) {
        return os << '[' << value._width << " x " << value._height << ']';
    }
#endif

private:
    // Internal Fields
    double _width;
    double _height;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
