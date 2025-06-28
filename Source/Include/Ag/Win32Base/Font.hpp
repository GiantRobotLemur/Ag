//! @file Ag/Win32Base/Font.hpp
//! @brief The declaration of an object wrapping a GDI font resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_FONT_HPP__
#define __AG_WIN32_BASE_GDI_FONT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/GdiResource.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping a GDI font resource.
class Font : public GdiResource
{
public:
    // Construction/Destruction
    Font() = default;
    Font(Font &&rhs) noexcept;
    Font(const Font &) = delete;
    Font &operator=(const Font &) = delete;
    Font(const LOGFONTW &definition);
    Font(HFONT handle, bool needsDisposal = false);

    // Accessors
    bool getDefinition(LOGFONTW &info) const;

    // Operations
    Font &operator=(Font &&rhs) noexcept;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
