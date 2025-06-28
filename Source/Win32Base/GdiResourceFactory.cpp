//! @file Win32Base/GdiResourceFactory.cpp
//! @brief The definition of an object which can instantiate pre-defined GDI
//! resources on demand.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Utils.hpp"
#include "Ag/Win32Base/Win32API.hpp"
#include "Ag/Win32Base/GdiResourceFactory.hpp"
#include "Ag/Win32Base/Pen.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

namespace {

//! @brief An object which can wrap a GDI resource of an unknown type.
class ConstructableResource : public GdiResource
{
public:
    ConstructableResource(HGDIOBJ handle, GdiResource::DeleterFn deleteFn = nullptr) :
        GdiResource(handle, (deleteFn == nullptr) ? ::DeleteObject : deleteFn)
    {
    }
};

//! @brief An object defining a solid colour fill.
class SolidColourBrush : public GdiResourceDefinition
{
private:
    // Internal Fields
    ColourI _fillColour;

public:
    SolidColourBrush(const ColourI &colour) :
        GdiResourceDefinition(GdiResourceType::Brush),
        _fillColour(colour)
    {
    }

    // Overrides

    // Inherited from GdiResourceDefinition.
    virtual GdiResource create(DeviceContext &/*dc*/, int /*escarpment = 0*/) const override
    {
        return ConstructableResource(::CreateSolidBrush(_fillColour.toColourRef()));
    }
};

//! @brief An object defining a cosmetic pen.
class SimpleCosmeticPen : public GdiResourceDefinition
{
private:
    LOGPEN _penDefinition;
public:
    SimpleCosmeticPen(const ColourI &colour, uint32_t thickness, uint32_t dashStyle) :
        GdiResourceDefinition(GdiResourceType::Pen)
    {
        _penDefinition.lopnStyle = dashStyle;
        _penDefinition.lopnWidth.x = static_cast<LONG>(thickness);
        _penDefinition.lopnWidth.y = 0;
        _penDefinition.lopnColor = colour.toColourRef();
    }

    virtual ~SimpleCosmeticPen() = default;

    // Overrides

    // Inherited from GdiResourceDefinition.
    virtual GdiResource create(DeviceContext &/*dc*/, int /*escarpment = 0*/) const override
    {
        return ConstructableResource(::CreatePenIndirect(&_penDefinition));
    }
};

//! @brief An object defining a font.
class FontDefinition : public GdiResourceDefinition
{
private:
    LOGFONT _definition;
    double _sizeInPts;
public:
    FontDefinition(const LOGFONT &definition, double sizeInPts) :
        GdiResourceDefinition(GdiResourceType::Font),
        _definition(definition),
        _sizeInPts(sizeInPts)
    {
    }

    virtual ~FontDefinition() = default;

    // Overrides

    // Inherited from GdiResourceDefinition.
    virtual GdiResource create(DeviceContext &dc, int escarpment) const override
    {
        LOGFONT effectiveDef = _definition;
        effectiveDef.lfEscapement = escarpment;

        if (_sizeInPts > 0.0)
        {
            // Calculate the size in device units using the specified DC.
            effectiveDef.lfHeight = static_cast<LONG>(std::rint((_sizeInPts * dc.getDpiY()) / 72.0));
        }

        return ConstructableResource(::CreateFontIndirectW(&effectiveDef));
    }
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GdiResourceDefinition Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object which can create a GDI resource on demand based on
//! an embedded definition.
GdiResourceDefinition::GdiResourceDefinition(GdiResourceType resourceType) :
    _type(resourceType)
{
}

//! @brief Gets the type of the resource.
GdiResourceType GdiResourceDefinition::getType() const { return _type; }

////////////////////////////////////////////////////////////////////////////////
// GdiResourceFactory Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if the resource factory contains no definitions.
//! @retval true The resource factory is empty.
//! @retval false The resource factory contains at least one resource definition.
bool GdiResourceFactory::isEmpty() const
{
    return _definitionsById.empty();
}

//! @brief Removes all resource from the factory.
void GdiResourceFactory::clear()
{
    _definitionsById.clear();
}

//! @brief Attempts to create a resource associated with the specified identifier.
//! @param[in] dc The rendering device on which the resource will be used.
//! @param[in] id The unique identifier of the definition to look up.
//! @param[out] resource Receives the newly created resource.
//! @retval true The resource definition was found and the resource successfully
//! instantiated.
//! @retval false The resource was not defined or creation failed.
bool GdiResourceFactory::tryCreateResource(DeviceContext &dc, uint32_t id,
                                           GdiResource &resource) const
{
    resource.dispose();
    GdiResourceDefinition *def;

    if (tryGetDefinition(id, def))
    {
        resource = def->create(dc);
    }

    return resource.isBound();
}

//! @brief Attempts to create a font resource associated with the specified
//! identifier.
//! @param[in] dc The rendering device on which the resource will be used.
//! @param[in] id The unique identifier of the definition to look up.
//! @param[in] escarpment The angle of the font in 100ths of a degree.
//! @param[out] resource Receives the newly created resource.
//! @retval true The resource definition was found and the resource successfully
//! instantiated.
//! @retval false The resource was not defined or creation failed.
bool GdiResourceFactory::tryCreateFont(DeviceContext &dc, uint32_t id,
                                       int escarpment,
                                       GdiResource &resource) const
{
    resource.dispose();
    GdiResourceDefinition *def;

    if (tryGetDefinition(id, def))
    {
        resource = def->create(dc, escarpment);
    }

    return resource.isBound();
}

//! @brief Adds a definition for a solid colour brush to the factory.
//! @param[in] id The unique identifier of the brush being defined.
//! @param[in] fillColour The colour of the brush.
void GdiResourceFactory::defineSolidBrush(uint32_t id, const ColourI &fillColour)
{
    GdiResourceDefinitionUPtr definition = std::make_unique<SolidColourBrush>(fillColour);

    defineCustom(id, std::move(definition));
}

//! @brief Adds a definition for a solid-filled cosmetic pen with a standard
//! dash pattern.
//! @param[in] id The unique identifier of the pen being defined.
//! @param[in] colour The colour of the lines drawn with the pen.
//! @param[in] thickness The thickness of the pen in pixels.
//! @param[in] style The dash style of the pen, e.g. PS_SOLID or PS_DASH.
void GdiResourceFactory::defineSimplePen(uint32_t id,
                                         const ColourI &colour,
                                         uint32_t thickness /*= 0*/,
                                         uint32_t style /*= PS_SOLID*/)
{
    GdiResourceDefinitionUPtr definition =
        std::make_unique<SimpleCosmeticPen>(colour, thickness, style);

    defineCustom(id, std::move(definition));
}

//! @brief Defines a font by specifying individual properties.
//! @param[in] id The unique identifier of the font being defined.
//! @param[in] name The name of the type face, e.g. "Arial".
//! @param[in] pointSize The size of the font in points (72ths of an inch).
//! @param[in] weight The weight of the font, e.g. FW_NORMAL or FW_BOLD.
//! @param[in] isUnderlined Indicates whether the text should be underlined.
//! @param[in] isItalic Indicates whether the text should be italic.
//! @param[in] isStrikeOut Indicates whether the text should be strike through.
void GdiResourceFactory::defineFont(uint32_t id, Ag::string_cref_t name,
                                    double pointSize,
                                    int weight /*= FW_NORMAL*/,
                                    bool isUnderlined /*= false*/,
                                    bool isItalic /*= false*/,
                                    bool isStrikeOut /*= false*/)
{
    LOGFONTW gdiDef;
    Ag::zeroFill(gdiDef);

    gdiDef.lfHeight = static_cast<LONG>(std::rint(std::abs(pointSize)));
    gdiDef.lfWeight = weight;
    gdiDef.lfUnderline = isUnderlined ? TRUE : FALSE;
    gdiDef.lfItalic = isItalic ? TRUE : FALSE;
    gdiDef.lfStrikeOut = isStrikeOut ? TRUE : FALSE;

    // Copy the Unicode type face name.
    std::wstring buffer = name.toWide();
    wcsncpy_s(gdiDef.lfFaceName, buffer.c_str(), buffer.length());

    GdiResourceDefinitionUPtr definition =
        std::make_unique<FontDefinition>(gdiDef, pointSize);

    defineCustom(id, std::move(definition));
}

//! @brief Specifies a font using a raw GDI definition.
//! @param[in] id The unique identifier of the font being defined.
//! @param[in] fontDefinition The GDI definition of the font.
//! @param[in] pointSize The size of the font in points (72ths of an inch), if
//! positive, the value will override the lfHeight field when the font is
//! instantiated.
void GdiResourceFactory::defineFont(uint32_t id, const LOGFONTW &fontDefinition,
                                    double pointSize /*= -1.0*/)
{
    GdiResourceDefinitionUPtr definition =
        std::make_unique<FontDefinition>(fontDefinition, pointSize);

    defineCustom(id, std::move(definition));
}

//! @brief Adds a resource definition to the map, overwriting any previous entry
//! mapped to the specified identifier.
//! @param[in] id The unique identifier of the brush being defined.
//! @param[in] definition A pointer to an object which describes the resource
//! can create it on demand.
void GdiResourceFactory::defineCustom(uint32_t id,
                                      GdiResourceDefinitionUPtr &&definition)
{
    if (definition)
    {
    // Determine if a mapping for the specified identifier already exists.
        auto existingMapping = _definitionsById.find(id);

        if (existingMapping == _definitionsById.end())
        {
            // Create a new mapping.
            _definitionsById[id] = std::move(definition);
        }
        else
        {
            // Update the existing mapping.
            existingMapping->second = std::move(definition);
        }
    }
}

//! @brief Attempts to find the definition of a specific resource.
//! @param[in] id The numeric identifier of the resource.
//! @param[out] def Receives the definition associated with the identifier.
//! @retval true A valid definition was found and returned.
//! @retval false No valid definition was registered against the
//! specified identifier.
bool GdiResourceFactory::tryGetDefinition(uint32_t id,
                                          GdiResourceDefinition *&def) const
{
    def = nullptr;

    auto mapping = _definitionsById.find(id);

    if (mapping != _definitionsById.end())
    {
        def = mapping->second.get();
    }

    return def != nullptr;
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////
