//! @file Ag/Win32Base/Brush.hpp
//! @brief The declaration of an object wrapping a GDI brush resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_BRUSH_HPP__
#define __AG_WIN32_BASE_GDI_BRUSH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "GdiResource.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping a GDI brush resource.
class Brush : public GdiResource
{
public:
    // Construction/Destruction
    Brush();
    Brush(Brush &&rhs) noexcept;
    Brush(const Brush &) = delete;
    Brush &operator=(const Brush &) = delete;
    Brush(int sysColourId);
    Brush(HBRUSH handle, bool needsDisposal = false);
    Brush(uint8_t red, uint8_t green, uint8_t blue);

    // Accessors
    bool getDefinition(LOGBRUSH &info) const;

    // Operations
    Brush &operator=(Brush &&rhs) noexcept;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
