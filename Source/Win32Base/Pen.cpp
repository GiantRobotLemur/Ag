//! @file Win32Base/Pen.cpp
//! @brief The definition of an object wrapping a GDI pen resource.
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

#include "Ag/Win32Base/Pen.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Pen Member Functions Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to take ownership of a GDI pen resource from
//! another object.
Pen::Pen(Pen &&rhs) noexcept :
    GdiResource(std::move(rhs))
{
}

//! @brief Constructs an object to wrap an existing GDI pen resource with
//! optional disposal semantics.
//! @param[in] handle The handle to the existing pen resource.
//! @param[in] needsDisposal True to ensure the resource is disposed of when
//! the object is destroyed.
Pen::Pen(HPEN handle, bool needsDisposal /* = false */) :
    GdiResource(handle,
                (needsDisposal && (handle != nullptr)) ? ::DeleteObject : nullptr)
{
}

//! @brief Creates a new logical pen.
//! @param[in] style The line style such as PS_SOLID, PS_DOT, PS_DASH, etc.
//! @param[in] width The width of the line, 0 for a single pixel thick line.
//! @param[in] colour The colour used to fill pixels overwritten by the line.
Pen::Pen(UINT style, UINT width, COLORREF colour) :
    GdiResource(::CreatePen(style, width, colour), ::DeleteObject)
{
}

//! @brief Attempts to get the definition of a simple pen resource.
//! @param[out] info A structure to receive the pen definition.
//! @retval true The pen definition was successfully retrieved.
//! @retval false Either the object was not bound to a pen resource
//! or the query failed.
bool Pen::getDefinition(LOGPEN &info) const
{
    return getTypedDefinition(info);
}

//! @brief Attempts to get the definition of an extended pen resource.
//! @param[out] info A structure to receive the pen definition.
//! @retval true The pen definition was successfully retrieved.
//! @retval false Either the object was not bound to an extended pen resource
//! or the query failed.
bool Pen::getDefinition(EXTLOGPEN &info) const
{
    return getTypedDefinition(info);
}

//! @brief Disposes of any currently bound resource and takes ownership of
//! another.
//! @param[in] rhs The object to transfer the new pen resource from.
//! @return A reference to the current object.
Pen &Pen::operator=(Pen &&rhs) noexcept
{
    GdiResource::operator=(std::move(rhs));

    return *this;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
