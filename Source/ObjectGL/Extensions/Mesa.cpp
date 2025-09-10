//! @file ObjectGL/Extensions/Mesa.cpp
//! @brief The definition of Mesa-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Mesa.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __MESAFramebufferFlipYEntryPoints[] = {
    { offsetof(MESAFramebufferFlipY, glFramebufferParameteri), "glFramebufferParameteriMESA" },
    { offsetof(MESAFramebufferFlipY, glGetFramebufferParameteriv), "glGetFramebufferParameterivMESA" },
};

static const EntryOffset __MESAResizeBuffersEntryPoints[] = {
    { offsetof(MESAResizeBuffers, glResizeBuffers), "glResizeBuffersMESA" },
};

static const EntryOffset __MESAWindowPosEntryPoints[] = {
    { offsetof(MESAWindowPos, glWindowPos2d), "glWindowPos2dMESA" },
    { offsetof(MESAWindowPos, glWindowPos2dv), "glWindowPos2dvMESA" },
    { offsetof(MESAWindowPos, glWindowPos2f), "glWindowPos2fMESA" },
    { offsetof(MESAWindowPos, glWindowPos2fv), "glWindowPos2fvMESA" },
    { offsetof(MESAWindowPos, glWindowPos2i), "glWindowPos2iMESA" },
    { offsetof(MESAWindowPos, glWindowPos2iv), "glWindowPos2ivMESA" },
    { offsetof(MESAWindowPos, glWindowPos2s), "glWindowPos2sMESA" },
    { offsetof(MESAWindowPos, glWindowPos2sv), "glWindowPos2svMESA" },
    { offsetof(MESAWindowPos, glWindowPos3d), "glWindowPos3dMESA" },
    { offsetof(MESAWindowPos, glWindowPos3dv), "glWindowPos3dvMESA" },
    { offsetof(MESAWindowPos, glWindowPos3f), "glWindowPos3fMESA" },
    { offsetof(MESAWindowPos, glWindowPos3fv), "glWindowPos3fvMESA" },
    { offsetof(MESAWindowPos, glWindowPos3i), "glWindowPos3iMESA" },
    { offsetof(MESAWindowPos, glWindowPos3iv), "glWindowPos3ivMESA" },
    { offsetof(MESAWindowPos, glWindowPos3s), "glWindowPos3sMESA" },
    { offsetof(MESAWindowPos, glWindowPos3sv), "glWindowPos3svMESA" },
    { offsetof(MESAWindowPos, glWindowPos4d), "glWindowPos4dMESA" },
    { offsetof(MESAWindowPos, glWindowPos4dv), "glWindowPos4dvMESA" },
    { offsetof(MESAWindowPos, glWindowPos4f), "glWindowPos4fMESA" },
    { offsetof(MESAWindowPos, glWindowPos4fv), "glWindowPos4fvMESA" },
    { offsetof(MESAWindowPos, glWindowPos4i), "glWindowPos4iMESA" },
    { offsetof(MESAWindowPos, glWindowPos4iv), "glWindowPos4ivMESA" },
    { offsetof(MESAWindowPos, glWindowPos4s), "glWindowPos4sMESA" },
    { offsetof(MESAWindowPos, glWindowPos4sv), "glWindowPos4svMESA" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// MESAFramebufferFlipY Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAFramebufferFlipY::MESAFramebufferFlipY()
{
    std::for_each_n(__MESAFramebufferFlipYEntryPoints,
                    std::size(__MESAFramebufferFlipYEntryPoints),
                    ClearEntryPoint(this));
}

bool MESAFramebufferFlipY::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_MESA_framebuffer_flip_y");
}

void MESAFramebufferFlipY::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAFramebufferFlipYEntryPoints,
                    std::size(__MESAFramebufferFlipYEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESAResizeBuffers Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAResizeBuffers::MESAResizeBuffers()
{
    std::for_each_n(__MESAResizeBuffersEntryPoints,
                    std::size(__MESAResizeBuffersEntryPoints),
                    ClearEntryPoint(this));
}

bool MESAResizeBuffers::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_MESA_resize_buffers");
}

void MESAResizeBuffers::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAResizeBuffersEntryPoints,
                    std::size(__MESAResizeBuffersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESAWindowPos Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAWindowPos::MESAWindowPos()
{
    std::for_each_n(__MESAWindowPosEntryPoints,
                    std::size(__MESAWindowPosEntryPoints),
                    ClearEntryPoint(this));
}

bool MESAWindowPos::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_MESA_window_pos");
}

void MESAWindowPos::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAWindowPosEntryPoints,
                    std::size(__MESAWindowPosEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl

#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __MESAAgpOffsetEntryPoints[] = {
    { offsetof(MESAAgpOffset, glXGetAGPOffset), "glXGetAGPOffsetMESA" },
};

static const gl::EntryOffset __MESACopySubBufferEntryPoints[] = {
    { offsetof(MESACopySubBuffer, glXCopySubBuffer), "glXCopySubBufferMESA" },
};

static const gl::EntryOffset __MESAPixmapColormapEntryPoints[] = {
    { offsetof(MESAPixmapColormap, glXCreateGLXPixmap), "glXCreateGLXPixmapMESA" },
};

static const gl::EntryOffset __MESAQueryRendererEntryPoints[] = {
    { offsetof(MESAQueryRenderer, glXQueryCurrentRendererInteger), "glXQueryCurrentRendererIntegerMESA" },
    { offsetof(MESAQueryRenderer, glXQueryCurrentRendererString), "glXQueryCurrentRendererStringMESA" },
    { offsetof(MESAQueryRenderer, glXQueryRendererInteger), "glXQueryRendererIntegerMESA" },
    { offsetof(MESAQueryRenderer, glXQueryRendererString), "glXQueryRendererStringMESA" },
};

static const gl::EntryOffset __MESAReleaseBuffersEntryPoints[] = {
    { offsetof(MESAReleaseBuffers, glXReleaseBuffers), "glXReleaseBuffersMESA" },
};

static const gl::EntryOffset __MESASet3DFXModeEntryPoints[] = {
    { offsetof(MESASet3DFXMode, glXSet3DfxMode), "glXSet3DfxModeMESA" },
};

static const gl::EntryOffset __MESASwapControlEntryPoints[] = {
    { offsetof(MESASwapControl, glXGetSwapInterval), "glXGetSwapIntervalMESA" },
    { offsetof(MESASwapControl, glXSwapInterval), "glXSwapIntervalMESA" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// MESAAgpOffset Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAAgpOffset::MESAAgpOffset()
{
    std::for_each_n(__MESAAgpOffsetEntryPoints,
                    std::size(__MESAAgpOffsetEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESAAgpOffset::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_agp_offset");
}

void MESAAgpOffset::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAAgpOffsetEntryPoints,
                    std::size(__MESAAgpOffsetEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESACopySubBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESACopySubBuffer::MESACopySubBuffer()
{
    std::for_each_n(__MESACopySubBufferEntryPoints,
                    std::size(__MESACopySubBufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESACopySubBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_copy_sub_buffer");
}

void MESACopySubBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESACopySubBufferEntryPoints,
                    std::size(__MESACopySubBufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESAPixmapColormap Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAPixmapColormap::MESAPixmapColormap()
{
    std::for_each_n(__MESAPixmapColormapEntryPoints,
                    std::size(__MESAPixmapColormapEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESAPixmapColormap::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_pixmap_colormap");
}

void MESAPixmapColormap::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAPixmapColormapEntryPoints,
                    std::size(__MESAPixmapColormapEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESAQueryRenderer Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAQueryRenderer::MESAQueryRenderer()
{
    std::for_each_n(__MESAQueryRendererEntryPoints,
                    std::size(__MESAQueryRendererEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESAQueryRenderer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_query_renderer");
}

void MESAQueryRenderer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAQueryRendererEntryPoints,
                    std::size(__MESAQueryRendererEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESAReleaseBuffers Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESAReleaseBuffers::MESAReleaseBuffers()
{
    std::for_each_n(__MESAReleaseBuffersEntryPoints,
                    std::size(__MESAReleaseBuffersEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESAReleaseBuffers::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_release_buffers");
}

void MESAReleaseBuffers::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESAReleaseBuffersEntryPoints,
                    std::size(__MESAReleaseBuffersEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESASet3DFXMode Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESASet3DFXMode::MESASet3DFXMode()
{
    std::for_each_n(__MESASet3DFXModeEntryPoints,
                    std::size(__MESASet3DFXModeEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESASet3DFXMode::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_set_3dfx_mode");
}

void MESASet3DFXMode::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESASet3DFXModeEntryPoints,
                    std::size(__MESASet3DFXModeEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// MESASwapControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
MESASwapControl::MESASwapControl()
{
    std::for_each_n(__MESASwapControlEntryPoints,
                    std::size(__MESASwapControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool MESASwapControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_MESA_swap_control");
}

void MESASwapControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__MESASwapControlEntryPoints,
                    std::size(__MESASwapControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

