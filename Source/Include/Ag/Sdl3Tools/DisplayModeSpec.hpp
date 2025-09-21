//! @file Ag/Sdl3Tools/DisplayModeSpec.hpp
//! @brief The declaration of an object used to specify a display mode.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_DISPLAY_MODE_SPEC_HPP__
#define __AG_SDL3_TOOLS_DISPLAY_MODE_SPEC_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/String.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object used to specify a display mode.
class DisplayModeSpec
{
private:
    // Internal Fields
    int _width;
    int _height;
    int _bpp;
    int _refreshRate;

public:
    // Construction/Destruction
    DisplayModeSpec();
    DisplayModeSpec(int width, int height, int bpp = -1, int refreshRate = -1);
    ~DisplayModeSpec() = default;

    // Accessors
    constexpr bool isEmpty() const noexcept { return (_width < 0) || (_height < 0); }

    constexpr int getWidth() const noexcept { return _width; }
    void setWidth(int widthInPixels) noexcept;

    constexpr int getHeight() const noexcept { return _height; }
    void setHeight(int heightInPixels) noexcept;

    constexpr bool hasBpp() const noexcept { return _bpp >= 0; }
    constexpr int getBpp() const noexcept { return _bpp; }
    void setBpp(int bitsPerPixel) noexcept;

    constexpr bool hasRefreshRate() const noexcept { return _refreshRate >= 0; }
    constexpr int getRefreshRate() const noexcept { return _refreshRate; }
    void setRefreshRate(int refreshRateInHz) noexcept;

    // Operations
    bool tryParse(const std::string_view &text);
    String toString() const;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
