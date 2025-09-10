//! @file ObjectGL/Extensions/OvrCommands.cpp
//! @brief The definition of Ovr-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/OvrCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// OvrMultiviewAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_OVR_multiview extension.
OvrMultiviewAPI::OvrMultiviewAPI() :
    BaseExtension("GL_OVR_multiview")
{
}

// Grant read-only access to the underlying function pointers.
const OvrMultiview &OvrMultiviewAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_OVR_multiview entry points.
void OvrMultiviewAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferTextureMultiviewOVR().
void OvrMultiviewAPI::framebufferTextureMultiviewOvr(FramebufferTarget target,
                                                     FramebufferAttachment attachment,
                                                     TextureName texture,
                                                     GLint level,
                                                     GLint baseViewIndex,
                                                     GLsizei numViews) const
{
    static const char *fnName = "glFramebufferTextureMultiviewOVR";

    beforeCommand(fnName, _api.glFramebufferTextureMultiviewOVR);
    _api.glFramebufferTextureMultiviewOVR(toScalar(target), toScalar(attachment),
                                          texture.ID, level, baseViewIndex,
                                          numViews);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

