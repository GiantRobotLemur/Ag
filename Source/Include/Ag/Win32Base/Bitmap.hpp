//! @file Ag/Win32Base/Bitmap.hpp
//! @brief The declaration of an object wrapping a GDI bitmap resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_BITMAP_HPP__
#define __AG_WIN32_BASE_GDI_BITMAP_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "GdiResource.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping a GDI bitmap resource.
class Bitmap : public GdiResource
{
public:
    // Construction/Destruction
    //! @brief Creates an unbound wrapper for a bitmap resource.
    Bitmap() = default;
    Bitmap(Bitmap &&rhs) noexcept;
    Bitmap(const Bitmap &) = delete;
    Bitmap &operator=(const Bitmap &) = delete;
    Bitmap(HBITMAP handle, bool needsDisposal = false);

    // Accessors
    bool getDefinition(BITMAP &info) const;
    bool getDefinition(DIBSECTION &info) const;

    // Operations
    Bitmap &operator=(Bitmap &&rhs) noexcept;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
