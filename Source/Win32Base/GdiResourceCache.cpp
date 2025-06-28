//! @file Win32Base/GdiResourceCache.cpp
//! @brief The definition of an object which can create GDI resource on demand
//! and cache them for later use.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "Ag/Core/VariantTypes.hpp"
#include "Ag/Win32Base/DeviceContext.hpp"
#include "Ag/Win32Base/GdiResourceCache.hpp"
#include "Ag/Win32Base/GdiResourceFactory.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// GdiResourceCache Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a cache of GDI resources for use in a specific drawing context.
//! @param[in] dc The device the resources will be used to draw to.
//! @param[in] factory An object which knows how to create GDI resources on demand.
GdiResourceCache::GdiResourceCache(DeviceContext &dc, const GdiResourceFactory &factory) :
    _factory(factory),
    _device(dc.getHandle()),
    _originalBrush(::GetCurrentObject(_device, OBJ_BRUSH)),
    _originalPen(::GetCurrentObject(_device, OBJ_PEN)),
    _originalFont(::GetCurrentObject(_device, OBJ_FONT))
{
}

//! @brief Ensures the state of the device context is restored before the cached
//! resources are deleted.
GdiResourceCache::~GdiResourceCache()
{
    restore();
}

//! @brief Gets the raw handle to the device resources are being rendered to.
HDC GdiResourceCache::getDevice() const
{
    return _device;
}

//! @brief Disposes of all cached resources, restoring the device state first.
void GdiResourceCache::flush()
{
    restore();
    _resources.clear();
    _fonts.clear();
}

//! @brief Restores the resources in the device which were selected when the
//! cache was constructed.
void GdiResourceCache::restore()
{
    if (_device)
    {
        ::SelectObject(_device, _originalBrush);
        ::SelectObject(_device, _originalPen);
        ::SelectObject(_device, _originalFont);
    }
}

//! @brief Gets a handle to a cached font resource.
//! @param[in] id The identifier of the resource to obtain.
//! @param[in] angleInDegrees The angle of the font text, in degrees.
//! @return The handle to the cached font, newly created if necessary.
HFONT GdiResourceCache::getFont(uint32_t id, double angleInDegrees)
{
    return reinterpret_cast<HFONT>(getResource(id, angleInDegrees));
}

//! @brief Selects a resource for use on the bound device, creating it if
//! necessary.
//! @param[in] id The identifier of the resource to select.
//! @return The handle to the previously selected object of the same type.
HGDIOBJ GdiResourceCache::selectResource(uint32_t id)
{
    HGDIOBJ resourceHandle = getResource(id, 0.0);

    return ::SelectObject(_device, resourceHandle);
}

//! @brief Selects an arbitrary resource for use on the bound device.
//! @param[in] handle The handle of the resource to select.
//! @return The handle to the previously selected object of the same type.
HGDIOBJ GdiResourceCache::selectResource(HGDIOBJ handle)
{
    return ::SelectObject(_device, handle);
}

//! @brief Selects a stock resource for use on the bound device.
//! @param[in] stockId The identifier of the stock resource, e.g. BLACK_BRUSH.
//! @return The handle to the previously selected object of the same type.
HGDIOBJ GdiResourceCache::selectStockResource(uint32_t stockId)
{
    HGDIOBJ resourceHandle = ::GetStockObject(stockId);

    return ::SelectObject(_device, resourceHandle);
}

//! @brief Selects a font resource for use on the bound device, creating it if
//! necessary.
//! @param[in] id The identifier of the font resource to select.
//! @param[in] angleInDegrees The angle of the font text, in degrees.
//! @return The handle to the previously selected font.
HGDIOBJ GdiResourceCache::selectFont(uint32_t id, double angleInDegrees)
{
    HGDIOBJ resourceHandle = getResource(id, angleInDegrees);

    return ::SelectObject(_device, resourceHandle);
}

//! @brief Constructs an object used to identify a cached font.
//! @param[in] id The identifier of the definition used to create the font.
//! @param[in] angleInDegrees The angle of the font text in degrees.
GdiResourceCache::FontResourceId::FontResourceId(uint32_t id, double angleInDegrees) :
    ID(id),
    Escarpment(static_cast<int32_t>(std::rint(angleInDegrees)) % 3600)
{
    if (Escarpment < 0)
    {
        Escarpment += 3600;
    }
}

//! @brief Performs a less-than comparison between font resource identifiers.
//! @param[in] rhs The font resource identifier to compare against.
//! @retval true If the current object has a lower value than rhs.
//! @retval false The current object has an equal or higher value than rhs.
bool GdiResourceCache::FontResourceId::operator<(const FontResourceId &rhs) const
{
    bool isLess = false;

    if (ID == rhs.ID)
    {
        isLess = Escarpment < rhs.Escarpment;
    }
    else
    {
        isLess = ID < rhs.ID;
    }

    return isLess;
}

//! @brief Gets a handle for a GDI resource, creating the resource if necessary.
//! @param[in] id The identifier of the resource to create.
//! @param[in] escarpment The angle of the text in any font created.
//! @return A handle to the resource, possibly lazily created.
HGDIOBJ GdiResourceCache::getResource(uint32_t id, double escarpment)
{
    HGDIOBJ handle = nullptr;
    auto mapping = (escarpment == 0) ? _resources.find(id) : _resources.end();

    // Look for a cached non-font resource.
    if (mapping == _resources.end())
    {
        // Not cached, try the font cache.
        FontResourceId key(id, escarpment);

        auto fontMapping = _fonts.find(key);

        if (fontMapping == _fonts.end())
        {
            // Not cached at all.
            DeviceContext tempContext(_device);
            GdiResource resource;

            // Attempt to create the resource.
            if (_factory.tryCreateFont(tempContext, id,
                                       key.Escarpment, resource))
            {
                // The resource was successfully created, cache it.
                handle = resource.getHandle();

                if (resource.getType() == GdiResourceType::Font)
                {
                    // Store the font in cache.
                    _fonts[key] = std::move(resource);
                }
                else
                {
                    // Store the brush or pen in cache.
                    _resources[id] = std::move(resource);
                }
            }
            else
            {
                // The factory didn't contain a definition matching the
                // specified ID.
                String detail = String::format("GDI resource ID #{0} not defined.",
                                               { id });
                throw OperationException(detail);
            }
        }
        else
        {
            // The font resource was already cached.
            handle = fontMapping->second.getHandle();
        }
    }
    else
    {
        // The brush/pen resource was already cached.
        handle = mapping->second.getHandle();
    }

    return handle;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
