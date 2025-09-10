//! @file ObjectGL/Extensions/OML.cpp
//! @brief The definition of OML-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/OML.hpp"

#ifdef _WIN32
namespace wgl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const gl::EntryOffset __OMLSyncControlEntryPoints[] = {
    { offsetof(OMLSyncControl, wglGetMscRate), "wglGetMscRateOML" },
    { offsetof(OMLSyncControl, wglGetSyncValues), "wglGetSyncValuesOML" },
    { offsetof(OMLSyncControl, wglSwapBuffersMsc), "wglSwapBuffersMscOML" },
    { offsetof(OMLSyncControl, wglSwapLayerBuffersMsc), "wglSwapLayerBuffersMscOML" },
    { offsetof(OMLSyncControl, wglWaitForMsc), "wglWaitForMscOML" },
    { offsetof(OMLSyncControl, wglWaitForSbc), "wglWaitForSbcOML" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// OMLSyncControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
OMLSyncControl::OMLSyncControl()
{
    std::for_each_n(__OMLSyncControlEntryPoints,
                    std::size(__OMLSyncControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool OMLSyncControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_OML_sync_control");
}

void OMLSyncControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OMLSyncControlEntryPoints,
                    std::size(__OMLSyncControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
#endif // ifdef _WIN32


#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __OMLSyncControlEntryPoints[] = {
    { offsetof(OMLSyncControl, glXGetMscRate), "glXGetMscRateOML" },
    { offsetof(OMLSyncControl, glXGetSyncValues), "glXGetSyncValuesOML" },
    { offsetof(OMLSyncControl, glXSwapBuffersMsc), "glXSwapBuffersMscOML" },
    { offsetof(OMLSyncControl, glXWaitForMsc), "glXWaitForMscOML" },
    { offsetof(OMLSyncControl, glXWaitForSbc), "glXWaitForSbcOML" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// OMLSyncControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
OMLSyncControl::OMLSyncControl()
{
    std::for_each_n(__OMLSyncControlEntryPoints,
                    std::size(__OMLSyncControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool OMLSyncControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_OML_sync_control");
}

void OMLSyncControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OMLSyncControlEntryPoints,
                    std::size(__OMLSyncControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

