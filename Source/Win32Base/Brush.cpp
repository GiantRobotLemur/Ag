//! @file Win32Base/Brush.cpp
//! @brief The definition of an object wrapping a GDI brush resource.
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

#include "Ag/Win32Base/Brush.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Brush Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object not bound to a resource.
Brush::Brush()
{
}

//! @brief Transfers a brush resource from another object.
Brush::Brush(Brush &&rhs) noexcept :
    GdiResource(std::move(rhs))
{
}

//! @brief Creates an object encapsulating a brush for system element.
//! @param[in] sysColourId The numeric identifier of the system colour, such
//! as COLOR_WINDOW
Brush::Brush(int sysColourId) :
    GdiResource(reinterpret_cast<HGDIOBJ>(::GetSysColorBrush(sysColourId)),
                nullptr)
{
}

//! @brief Constructs an object bound to a GDI brush resource.
//! @param[in] handle The handle of the resource.
//! @param[in] needsDisposal True to ensure the object is disposed of at
//! destruction.
Brush::Brush(HBRUSH handle, bool needsDisposal /* = false */) :
    GdiResource(handle,
                ((handle != nullptr) && needsDisposal) ? ::DeleteObject : nullptr)
{
}

//! @brief Constructs an object bound to a new solid brush resource.
//! @param[in] red The red component of the solid fill colour.
//! @param[in] green The green component of the solid fill colour.
//! @param[in] blue The blue component of the solid fill colour.
Brush::Brush(uint8_t red, uint8_t green, uint8_t blue) :
    GdiResource(::CreateSolidBrush(RGB(red, green, blue)),
                ::DeleteObject)
{
}

//! @brief Attempts to obtain a definition of the brush resource.
//! @param[out] info A structure to receive the definition.
//! @retval true The definition was successfully obtained.
//! @retval false The definition could not be obtained.
bool Brush::getDefinition(LOGBRUSH &info) const
{
    return getTypedDefinition(info);
}

//! @brief Disposes of the currently bound resource and transfers another to
//! the current object.
//! @param[in] rhs The brush object to transfer the resource from.
//! @return A reference to the current object.
Brush &Brush::operator=(Brush &&rhs) noexcept
{
    GdiResource::operator=(std::move(rhs));

    return *this;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
