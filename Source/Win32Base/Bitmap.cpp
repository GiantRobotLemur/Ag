//! @file Win32Base/Bitmap.cpp
//! @brief The definition of an object wrapping a GDI bitmap resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/Bitmap.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Bitmap Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object which acquires a GDI bitmap resource from another.
//! @param[in] rhs The object to obtain the underlying bitmap resource from.
Bitmap::Bitmap(Bitmap &&rhs) noexcept :
    GdiResource(std::move(rhs))
{
}

//! @brief Creates an object to wrap a GDI bitmap resource.
//! @param[in] handle The handle of the resource to map.
//! @param[in] needsDisposal True if the resource should be linked to the
//! lifetime of the object, false to merely wrap it.
Bitmap::Bitmap(HBITMAP handle, bool needsDisposal /*= false*/) :
    GdiResource(reinterpret_cast<HGDIOBJ>(handle),
                needsDisposal ? ::DeleteObject : nullptr)
{
}

//! @brief Attempts to obtain a definition of the bitmap resource.
//! @param[out] info A structure to receive the definition.
//! @retval true The definition was successfully obtained.
//! @retval false The definition could not be obtained.
bool Bitmap::getDefinition(BITMAP &info) const
{
    return getTypedDefinition(info);
}

//! @brief Attempts to obtain a definition of the DIB section resource.
//! @param[out] info A structure to receive the definition.
//! @retval true The definition was successfully obtained.
//! @retval false The definition could not be obtained.
bool Bitmap::getDefinition(DIBSECTION &info) const
{
    return getTypedDefinition(info);
}

//! @brief Acquires the underlying bitmap resource from another object and
//! uses it to overwrite the resource previously bound to this object.
//! @param[in] rhs The object to acquire the resource from.
//! @return A reference to the current object.
Bitmap &Bitmap::operator=(Bitmap &&rhs) noexcept
{
    GdiResource::operator=(std::move(rhs));

    return *this;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
