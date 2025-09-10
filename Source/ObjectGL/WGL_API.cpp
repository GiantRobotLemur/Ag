//! @file ObjectGL/WGL_API.cpp
//! @brief The definition of Microsoft Windows-specific OpenGL entry points,
//! also known as WGL.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Required Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <utility>
#include "Ag/ObjectGL/WGL_API.hpp"

namespace wgl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const gl::EntryOffset __WGLEntryPoints[] = {
    { offsetof(WGL, ChoosePixelFormat), "ChoosePixelFormat" },
    { offsetof(WGL, DescribePixelFormat), "DescribePixelFormat" },
    { offsetof(WGL, GetEnhMetaFilePixelFormat), "GetEnhMetaFilePixelFormat" },
    { offsetof(WGL, GetPixelFormat), "GetPixelFormat" },
    { offsetof(WGL, SetPixelFormat), "SetPixelFormat" },
    { offsetof(WGL, SwapBuffers), "SwapBuffers" },
    { offsetof(WGL, wglCopyContext), "wglCopyContext" },
    { offsetof(WGL, wglCreateContext), "wglCreateContext" },
    { offsetof(WGL, wglCreateLayerContext), "wglCreateLayerContext" },
    { offsetof(WGL, wglDeleteContext), "wglDeleteContext" },
    { offsetof(WGL, wglDescribeLayerPlane), "wglDescribeLayerPlane" },
    { offsetof(WGL, wglGetCurrentContext), "wglGetCurrentContext" },
    { offsetof(WGL, wglGetCurrentDC), "wglGetCurrentDC" },
    { offsetof(WGL, wglGetLayerPaletteEntries), "wglGetLayerPaletteEntries" },
    { offsetof(WGL, wglGetProcAddress), "wglGetProcAddress" },
    { offsetof(WGL, wglMakeCurrent), "wglMakeCurrent" },
    { offsetof(WGL, wglRealizeLayerPalette), "wglRealizeLayerPalette" },
    { offsetof(WGL, wglSetLayerPaletteEntries), "wglSetLayerPaletteEntries" },
    { offsetof(WGL, wglShareLists), "wglShareLists" },
    { offsetof(WGL, wglSwapLayerBuffers), "wglSwapLayerBuffers" },
    { offsetof(WGL, wglUseFontBitmaps), "wglUseFontBitmaps" },
    { offsetof(WGL, wglUseFontBitmapsA), "wglUseFontBitmapsA" },
    { offsetof(WGL, wglUseFontBitmapsW), "wglUseFontBitmapsW" },
    { offsetof(WGL, wglUseFontOutlines), "wglUseFontOutlines" },
    { offsetof(WGL, wglUseFontOutlinesA), "wglUseFontOutlinesA" },
    { offsetof(WGL, wglUseFontOutlinesW), "wglUseFontOutlinesW" },
};

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// WGL Member Definitions
////////////////////////////////////////////////////////////////////////////////
WGL::WGL()
{
    std::for_each_n(__WGLEntryPoints,
                    std::size(__WGLEntryPoints),
                    gl::ClearEntryPoint(this));
}

void WGL::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__WGLEntryPoints,
                    std::size(__WGLEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
