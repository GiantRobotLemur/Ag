//! @file Ag/Win32Base/GdiResource.hpp
//! @brief The declaration of an object representing a resource used with a
//! GDI device context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_RESOURCE_HPP__
#define __AG_WIN32_BASE_GDI_RESOURCE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Win32API.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Expresses the type of a GDI resource.
enum class GdiResourceType
{
    Unknown,
    Pen = OBJ_PEN,
    Brush = OBJ_BRUSH,
    Device = OBJ_DC,
    MetaDevice = OBJ_METADC,
    Palette = OBJ_PAL,
    Font = OBJ_FONT,
    Bitmap = OBJ_BITMAP,
    Region = OBJ_REGION,
    Metafile = OBJ_METAFILE,
    MemoryDevice = OBJ_MEMDC,
    ExtendedPen = OBJ_EXTPEN,
    EnhancedMetaDevice = OBJ_ENHMETADC,
    EnhancedMetafile = OBJ_ENHMETAFILE,
    ColourSpace = OBJ_COLORSPACE,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object wrapping a resource used with a GDI device context.
class GdiResource
{
public:
    // Public Types
    typedef BOOL (WINAPI *DeleterFn)(HGDIOBJ);

    // Construction/Destruction
    GdiResource();
    GdiResource(HGDIOBJ handle, DeleterFn deleterFn = nullptr);
    GdiResource(GdiResource &&rhs) noexcept;
    GdiResource(const GdiResource &) = delete;
    GdiResource &operator=(const GdiResource &) = delete;
    virtual ~GdiResource();

    // Accessors
    bool isBound() const;
    bool isPen() const;
    bool isMetafile() const;
    HGDIOBJ getHandle() const;
    GdiResourceType getType() const;

    // Operations
    void dispose();
    GdiResource &operator=(GdiResource &&rhs) noexcept;
protected:
    //! @brief Queries information for a wrapped GDI resource.
    //! @tparam T The data type of the information structure to fill.
    //! @param[out] infoStruct Receives information about the resource,
    //! if successful.
    //! @retval true Information was successfully obtained.
    //! @retval false The object was not bound or the structure type was wrong.
    template<typename T>
    bool getTypedDefinition(T &infoStruct) const
    {
        return (_handle != nullptr) &&
            (::GetObject(_handle, sizeof(T), &infoStruct) != FALSE);
    }
private:
    // Internal Fields
    HGDIOBJ _handle;
    DeleterFn _deleterFn;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
