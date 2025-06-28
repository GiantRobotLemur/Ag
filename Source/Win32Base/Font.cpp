//! @file Win32Base/Font.cpp
//! @brief The definition of an object wrapping a GDI font resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <utility>
#include "Ag/Win32Base/Font.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Font Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Transfers a font resource from another object to create a new one.
Font::Font(Font &&rhs) noexcept :
    GdiResource(std::move(rhs))
{
}

//! @brief Creates a new font from a definition.
Font::Font(const LOGFONTW &definition) :
    GdiResource(::CreateFontIndirectW(&definition), ::DeleteObject)
{
}

//! @brief Attaches to a font resource with optional disposal semantics.
Font::Font(HFONT handle, bool needsDisposal /* = false */) :
    GdiResource(handle,
                (needsDisposal && (handle != nullptr)) ? ::DeleteObject : nullptr)
{
}

//! @brief Attempts to get the definition of the bound font resource.
//! @param[out] info The structure to receive the definition.
//! @retval true A definition was retrieved.
//! @retval false The operation failed or the object was not bound.
bool Font::getDefinition(LOGFONTW &info) const
{
    return getTypedDefinition(info);
}

//! @brief Transfers a font resource from another object to this one, disposing
//! of any previously bound font resource.
//! @param[in] rhs The object to transfer from.
//! @returns A reference to the current object.
Font &Font::operator=(Font &&rhs) noexcept
{
    GdiResource::operator=(std::move(rhs));

    return *this;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
