//! @file Win32Base/GdiResource.cpp
//! @brief The definition of an object representing a resource used with a
//! GDI device context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Win32Base/GdiResource.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Method Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object not bound to any resource.
GdiResource::GdiResource() :
    _handle(nullptr),
    _deleterFn(nullptr)
{
}

//! @brief Transfers the underlying resource to a new object.
//! @param[in] rhs The object to transfer a resource from.
GdiResource::GdiResource(GdiResource &&rhs) noexcept :
    _handle(rhs._handle),
    _deleterFn(rhs._deleterFn)
{
    rhs._handle = nullptr;
    rhs._deleterFn = nullptr;
}

//! @brief Constructs an object bound to a resource with optional deletion
//! semantics.
//! @param[in] handle The handle to the resource to manage.
//! @param[in] deleterFn A pointer to a function to call to dispose of the
//! handle when it is no longer required, nullptr if no disposal is required.
GdiResource::GdiResource(HGDIOBJ handle, DeleterFn deleterFn /* = nullptr */) :
    _handle(handle),
    _deleterFn(handle == nullptr ? nullptr : deleterFn)
{

}

//! @brief Ensures any bound resource is disposed of if necessary.
GdiResource::~GdiResource()
{
    dispose();
}

//! @brief Determines if the object is bound to an underlying resource.
bool GdiResource::isBound() const { return _handle != nullptr; }

//! @brief Determines whether the object wraps a valid GDI pen resource.
//! @retval true The object wraps a pen or extended pen.
//! @retval false The object is unbound or wraps a different resource type.
bool GdiResource::isPen() const
{
    bool isPen = false;

    if (_handle != nullptr)
    {
        DWORD rawType = ::GetObjectType(_handle);

        isPen = (rawType == OBJ_PEN) || (rawType == OBJ_EXTPEN);
    }

    return isPen;
}

//! @brief Determines whether the object wraps a valid GDI metafile resource.
//! @retval true The object wraps a metafile or enhanced metafile.
//! @retval false The object is unbound or wraps a different resource type.
bool GdiResource::isMetafile() const
{
    bool isMetaFile = false;

    if (_handle != nullptr)
    {
        DWORD rawType = ::GetObjectType(_handle);

        isMetaFile = (rawType == OBJ_METAFILE) || (rawType == OBJ_ENHMETAFILE);
    }

    return isMetaFile;
}

//! @brief Get the handle to the underlying GDI resource, if one was bound.
HGDIOBJ GdiResource::getHandle() const { return _handle; }

//! @brief Gets the type of the underlying resource.
GdiResourceType GdiResource::getType() const
{
    GdiResourceType resourceType = GdiResourceType::Unknown;

    if (_handle != nullptr)
    {
        resourceType = static_cast<GdiResourceType>(::GetObjectType(_handle));
    }

    return resourceType;
}

//! @brief Disposes of the resource if it requires disposal.
void GdiResource::dispose()
{
    if (_handle != nullptr)
    {
        if (_deleterFn != nullptr)
        {
            _deleterFn(_handle);
        }

        _handle = nullptr;
    }

    _deleterFn = nullptr;
}

//! @brief Disposes of the current object and transfers another resource into
//! the current object.
//! @param[in] rhs The object to transfer the resource from.
//! @retval A reference to the current object.
GdiResource &GdiResource::operator=(GdiResource &&rhs) noexcept
{
    if (rhs._handle != _handle)
    {
        dispose();
        _handle = rhs._handle;
        _deleterFn = rhs._deleterFn;
        rhs._handle = nullptr;
        rhs._deleterFn = nullptr;
    }

    return *this;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
