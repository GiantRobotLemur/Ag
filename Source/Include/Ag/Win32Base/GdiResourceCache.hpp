//! @file Ag/Win32Base/GdiResourceCache.hpp
//! @brief The declaration of an object which can create GDI resource on demand
//! and cache them for later use.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_RESOURCE_CACHE_HPP__
#define __AG_WIN32_BASE_GDI_RESOURCE_CACHE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <map>

#include "Ag/Win32Base/DeviceContext.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class GdiResourceFactory;

//! @brief An object which can create GDI resource on demand and cache them for
//! later use.
class GdiResourceCache
{
public:
    // Construction/Destruction
    GdiResourceCache(DeviceContext &dc, const GdiResourceFactory &factory);
    ~GdiResourceCache();

    // Accessors
    HDC getDevice() const;

    // Operations
    void flush();
    void restore();
    HFONT getFont(uint32_t id, double angleInDegrees);
    HGDIOBJ selectResource(uint32_t id);
    HGDIOBJ selectResource(HGDIOBJ handle);
    HGDIOBJ selectStockResource(uint32_t stockId);
    HGDIOBJ selectFont(uint32_t id, double angleInDegrees);
private:
    // Internal Types
    struct FontResourceId
    {
        uint32_t ID;
        int32_t Escarpment;

        FontResourceId(uint32_t id, double angleInDegrees);

        bool operator<(const FontResourceId &rhs) const;
    };

    using GdiResourceMap = std::map<uint32_t, GdiResource>;
    using GdiFontMap = std::map<FontResourceId, GdiResource>;

    // Internal Functions
    HGDIOBJ getResource(uint32_t id, double escarpment);

    // Internal Fields
    const GdiResourceFactory &_factory;
    GdiResourceMap _resources;
    GdiFontMap _fonts;
    HDC _device;
    HGDIOBJ _originalBrush;
    HGDIOBJ _originalPen;
    HGDIOBJ _originalFont;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
