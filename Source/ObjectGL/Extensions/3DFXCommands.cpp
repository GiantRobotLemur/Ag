//! @file ObjectGL/Extensions/3DFXCommands.cpp
//! @brief The definition of 3DFX-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/3DFXCommands.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// _3DFXTbufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_3DFX_tbuffer extension.
_3DFXTbufferAPI::_3DFXTbufferAPI() :
    BaseExtension("GL_3DFX_tbuffer")
{
}

// Grant read-only access to the underlying function pointers.
const _3DFXTbuffer &_3DFXTbufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_3DFX_tbuffer entry points.
void _3DFXTbufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTbufferMask3DFX().
void _3DFXTbufferAPI::tbufferMask(GLuint mask) const
{
    static const char *fnName = "glTbufferMask3DFX";

    beforeCommand(fnName, _api.glTbufferMask);
    _api.glTbufferMask(mask);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

