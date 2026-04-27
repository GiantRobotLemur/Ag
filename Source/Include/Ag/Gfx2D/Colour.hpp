//! @file Ag/Gfx2D/Colour.hpp
//! @brief The declaration of a representation of a colour value using RGBA values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_COLOUR_HPP__
#define __GFX_2D_COLOUR_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <utility>

#include "Ag/Core/Configuration.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A representation of a colour value using RGBA values.
class STRUCT_ALIGN_16 Colour
{
private:
    // Internal Types

    // Internal Fields
    float _red;
    float _green;
    float _blue;
    float _alpha;

    // Internal Functions

public:
    // Public Constants
    static const Colour Zero;
    static const Colour One;
    static const Colour MinusOne;

    // Construction/Destruction
    Colour() noexcept;
    Colour(Colour &&rhs) noexcept;
    Colour(const Colour &rhs) noexcept;
    Colour(const float *vector) noexcept;
    Colour(float red, float green, float blue, float alpha = 1.0f) noexcept;
    ~Colour() = default;

    // Accessors
    constexpr float *toArray() noexcept { return &_red; }
    constexpr const float *toArray() const noexcept { return &_red; }
    constexpr float getRed() const noexcept { return _red; }
    constexpr const float &getRedRef() const noexcept { return _red; }
    constexpr void setRed(float red) noexcept { _red = red; }
    constexpr float getGreen() const noexcept { return _green; }
    constexpr const float &getGreenRef() const noexcept { return _green; }
    constexpr void setGreen(float green) noexcept { _green = green; }
    constexpr float getBlue() const noexcept { return _blue; }
    constexpr const float &getBlueRef() const noexcept { return _blue; }
    constexpr void setBlue(float blue) noexcept { _blue = blue; }
    constexpr float getAlpha() const noexcept { return _alpha; }
    constexpr const float &getAlphaRef() const noexcept { return _alpha; }
    constexpr void setAlpha(float alpha) noexcept { _alpha = alpha; }

    // Operations
    bool operator==(const Colour &rhs) const noexcept;
    bool operator!=(const Colour &rhs) const noexcept;
    Colour &operator=(const Colour &rhs) noexcept;
    Colour &operator=(Colour &&rhs) noexcept;
    Colour operator+(const Colour &rhs) const;
    Colour operator-(const Colour &rhs) const;
    Colour operator*(const Colour &rhs) const;
    Colour operator*(float rhs) const;
    Colour operator/(const Colour &rhs) const;
    Colour operator/(float rhs) const;
    Colour &operator+=(const Colour &rhs);
    Colour &operator-=(const Colour &rhs);
    Colour &operator*=(const Colour &rhs);
    Colour &operator*=(float rhs);
    Colour &operator/=(const Colour &rhs);
    Colour &operator/=(float rhs);
    Colour min(const Colour &rhs) const;
    Colour max(const Colour &rhs) const;
    std::pair<Colour, Colour> minmax(const Colour &rhs) const;
    Colour clamp(const Colour &min, const Colour &max) const;
    Colour lerp(const Colour &toward, float scalar) const;
    Colour fma(const Colour &scale, const Colour &offset) const;
    Colour alphaBlend(Colour &rhs) const;
    Colour alphaBlend(Colour &rhs, float alpha) const;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
