//! @file ObjectGL/Extensions/3DLabs.cpp
//! @brief The definition of 3D Labs-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/3DLabs.hpp"

namespace wgl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const gl::EntryOffset ___3DLStereoControlEntryPoints[] = {
    { offsetof(_3DLStereoControl, wglSetStereoEmitterState3DL), "wglSetStereoEmitterState3DL" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// _3DLStereoControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
_3DLStereoControl::_3DLStereoControl()
{
    std::for_each_n(___3DLStereoControlEntryPoints,
                    std::size(___3DLStereoControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool _3DLStereoControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_3DL_stereo_control");
}

void _3DLStereoControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(___3DLStereoControlEntryPoints,
                    std::size(___3DLStereoControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
////////////////////////////////////////////////////////////////////////////////

