//! @file ObjectGL/Extensions/GremedyCommands.cpp
//! @brief The definition of Gremedy-specific extensions to the OpenGL Command
//! set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/GremedyCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// GremedyFrameTerminatorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_GREMEDY_frame_terminator extension.
GremedyFrameTerminatorAPI::GremedyFrameTerminatorAPI() :
    BaseExtension("GL_GREMEDY_frame_terminator")
{
}

// Grant read-only access to the underlying function pointers.
const GremedyFrameTerminator &GremedyFrameTerminatorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_GREMEDY_frame_terminator entry points.
void GremedyFrameTerminatorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFrameTerminatorGREMEDY().
void GremedyFrameTerminatorAPI::frameTerminatorGremedy() const
{
    static const char *fnName = "glFrameTerminatorGREMEDY";

    beforeCommand(fnName, _api.glFrameTerminatorGREMEDY);
    _api.glFrameTerminatorGREMEDY();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// GremedyStringMarkerAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_GREMEDY_string_marker extension.
GremedyStringMarkerAPI::GremedyStringMarkerAPI() :
    BaseExtension("GL_GREMEDY_string_marker")
{
}

// Grant read-only access to the underlying function pointers.
const GremedyStringMarker &GremedyStringMarkerAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_GREMEDY_string_marker entry points.
void GremedyStringMarkerAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glStringMarkerGREMEDY().
void GremedyStringMarkerAPI::stringMarkerGremedy(GLsizei len, const void *string) const
{
    static const char *fnName = "glStringMarkerGREMEDY";

    beforeCommand(fnName, _api.glStringMarkerGREMEDY);
    _api.glStringMarkerGREMEDY(len, string);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

