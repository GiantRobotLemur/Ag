//! @file ObjectGL/Extensions/3DFX.cpp
//! @brief The definition of 3DFX-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/3DFX.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset _3DFXTbufferEntryPoints[] = {
    { offsetof(_3DFXTbuffer, glTbufferMask), "glTbufferMask3DFX" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// _3DFXTbuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
_3DFXTbuffer::_3DFXTbuffer()
{
    std::for_each_n(_3DFXTbufferEntryPoints,
                    std::size(_3DFXTbufferEntryPoints),
                    ClearEntryPoint(this));
}

bool _3DFXTbuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_3DFX_tbuffer");
}

void _3DFXTbuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(_3DFXTbufferEntryPoints,
                    std::size(_3DFXTbufferEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

