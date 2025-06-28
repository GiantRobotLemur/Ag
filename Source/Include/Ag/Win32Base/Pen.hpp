//! @file Ag/Win32Base/Pen.hpp
//! @brief The declaration of an object wrapping a GDI pen resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_PEN_HPP__
#define __AG_WIN32_BASE_GDI_PEN_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "GdiResource.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping a GDI pen resource.
class Pen : public GdiResource
{
public:
    // Construction/Destruction
    Pen() = default;
    Pen(const Pen &) = delete;
    Pen &operator=(const Pen &) = delete;
    Pen(Pen &&rhs) noexcept;
    Pen(HPEN handle, bool needsDisposal = false);
    Pen(UINT style, UINT width, COLORREF colour);

    // Accessors
    bool getDefinition(LOGPEN &info) const;
    bool getDefinition(EXTLOGPEN &info) const;

    // Operations
    Pen &operator=(Pen &&rhs) noexcept;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
