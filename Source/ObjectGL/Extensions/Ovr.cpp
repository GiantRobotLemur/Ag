//! @file ObjectGL/Extensions/Ovr.cpp
//! @brief The definition of Ovr-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Ovr.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __OvrMultiviewEntryPoints[] = {
    { offsetof(OvrMultiview, glFramebufferTextureMultiviewOVR), "glFramebufferTextureMultiviewOVR" },
    { offsetof(OvrMultiview, glNamedFramebufferTextureMultiviewOVR), "glNamedFramebufferTextureMultiviewOVR" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// OvrMultiview Member Definitions
////////////////////////////////////////////////////////////////////////////////
OvrMultiview::OvrMultiview()
{
    std::for_each_n(__OvrMultiviewEntryPoints,
                    std::size(__OvrMultiviewEntryPoints),
                    ClearEntryPoint(this));
}

bool OvrMultiview::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_OVR_multiview");
}

void OvrMultiview::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OvrMultiviewEntryPoints,
                    std::size(__OvrMultiviewEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

