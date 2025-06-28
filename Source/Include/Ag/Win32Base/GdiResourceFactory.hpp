//! @file Ag/Win32Base/GdiResourceFactory.hpp
//! @brief The declaration of an object which can instantiate pre-defined GDI
//! resources on demand.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_GDI_RESOURCE_FACTORY_HPP__
#define __AG_WIN32_BASE_GDI_RESOURCE_FACTORY_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <map>

#include "GdiResource.hpp"
#include "Tools.hpp"
#include "DeviceContext.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class GdiResourceDefinition
{
public:
    // Construction/Destruction
    GdiResourceDefinition(GdiResourceType resourceType);
    virtual ~GdiResourceDefinition() = default;

    // Accessors
    GdiResourceType getType() const;

    // Operations
    virtual GdiResource create(DeviceContext &dc, int escarpment = 0) const =0;
private:
    // Internal Fields
    GdiResourceType _type;
};

using GdiResourceDefinitionUPtr = std::unique_ptr<GdiResourceDefinition>;

//! @brief An object which can instantiate pre-defined GDI resources on demand.
class GdiResourceFactory
{
public:
    // Construction/Destruction
    GdiResourceFactory() = default;
    ~GdiResourceFactory() = default;

    // Accessors
    bool isEmpty() const;

    // Operations
    void clear();
    bool tryCreateResource(DeviceContext &dc, uint32_t id,
                           GdiResource &resource) const;
    bool tryCreateFont(DeviceContext &dc, uint32_t id, int escarpment,
                       GdiResource &resource) const;
    void defineSolidBrush(uint32_t id, const ColourI &fillColour);
    void defineSimplePen(uint32_t id, const ColourI &colour,
                         uint32_t thickness = 0, uint32_t style = PS_SOLID);
    void defineFont(uint32_t id, Ag::string_cref_t name, double pointSize,
                    int weight = FW_NORMAL, bool isUnderlined = false,
                    bool isItalic = false, bool isStrikeOut = false);
    void defineFont(uint32_t id, const LOGFONTW &fontDefinition, double pointSize = -1.0);
    void defineCustom(uint32_t id, GdiResourceDefinitionUPtr &&definition);
private:
    // Internal Types
    using GdiResourceDefinitionMap = std::map<uint32_t, GdiResourceDefinitionUPtr>;

    // Internal Functions
    bool tryGetDefinition(uint32_t id, GdiResourceDefinition *&def) const;

    // Internal Fields
    GdiResourceDefinitionMap _definitionsById;
};

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
