//! @file ObjectGL/GLX_API.cpp
//! @brief The definition of X Windows-specific OpenGL entry points, also
//! known as GLX.
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
#include <algorithm>

#include "Ag/ObjectGL/GLX_API.hpp"

namespace glx {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
namespace {

static const gl::EntryOffset __GLXEntryPoints[] = {
    { offsetof(GLX, glXChooseVisual), "glXChooseVisual" },
    { offsetof(GLX, glXCopyContext), "glXCopyContext" },
    { offsetof(GLX, glXCreateContext), "glXCreateContext" },
    { offsetof(GLX, glXCreateGLXPixmap), "glXCreateGLXPixmap" },
    { offsetof(GLX, glXDestroyContext), "glXDestroyContext" },
    { offsetof(GLX, glXDestroyGLXPixmap), "glXDestroyGLXPixmap" },
    { offsetof(GLX, glXGetConfig), "glXGetConfig" },
    { offsetof(GLX, glXGetCurrentContext), "glXGetCurrentContext" },
    { offsetof(GLX, glXGetCurrentDrawable), "glXGetCurrentDrawable" },
    { offsetof(GLX, glXIsDirect), "glXIsDirect" },
    { offsetof(GLX, glXMakeCurrent), "glXMakeCurrent" },
    { offsetof(GLX, glXQueryExtension), "glXQueryExtension" },
    { offsetof(GLX, glXQueryVersion), "glXQueryVersion" },
    { offsetof(GLX, glXSwapBuffers), "glXSwapBuffers" },
    { offsetof(GLX, glXUseXFont), "glXUseXFont" },
    { offsetof(GLX, glXWaitGL), "glXWaitGL" },
    { offsetof(GLX, glXWaitX), "glXWaitX" },
    { offsetof(GLX, glXGetClientString), "glXGetClientString" },
    { offsetof(GLX, glXQueryExtensionsString), "glXQueryExtensionsString" },
    { offsetof(GLX, glXQueryServerString), "glXQueryServerString" },
    { offsetof(GLX, glXGetCurrentDisplay), "glXGetCurrentDisplay" },
    { offsetof(GLX, glXChooseFBConfig), "glXChooseFBConfig" },
    { offsetof(GLX, glXCreateNewContext), "glXCreateNewContext" },
    { offsetof(GLX, glXCreatePbuffer), "glXCreatePbuffer" },
    { offsetof(GLX, glXCreatePixmap), "glXCreatePixmap" },
    { offsetof(GLX, glXCreateWindow), "glXCreateWindow" },
    { offsetof(GLX, glXDestroyPbuffer), "glXDestroyPbuffer" },
    { offsetof(GLX, glXDestroyPixmap), "glXDestroyPixmap" },
    { offsetof(GLX, glXDestroyWindow), "glXDestroyWindow" },
    { offsetof(GLX, glXGetCurrentReadDrawable), "glXGetCurrentReadDrawable" },
    { offsetof(GLX, glXGetFBConfigAttrib), "glXGetFBConfigAttrib" },
    { offsetof(GLX, glXGetFBConfigs), "glXGetFBConfigs" },
    { offsetof(GLX, glXGetSelectedEvent), "glXGetSelectedEvent" },
    { offsetof(GLX, glXGetVisualFromFBConfig), "glXGetVisualFromFBConfig" },
    { offsetof(GLX, glXMakeContextCurrent), "glXMakeContextCurrent" },
    { offsetof(GLX, glXQueryContext), "glXQueryContext" },
    { offsetof(GLX, glXQueryDrawable), "glXQueryDrawable" },
    { offsetof(GLX, glXSelectEvent), "glXSelectEvent" },
    { offsetof(GLX, glXGetProcAddress), "glXGetProcAddress" },
};

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GLX Member Definitions
////////////////////////////////////////////////////////////////////////////////
GLX::GLX()
{
    std::for_each_n(__GLXEntryPoints,
                    std::size(__GLXEntryPoints),
                    gl::ClearEntryPoint(this));
}

void GLX::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__GLXEntryPoints,
                    std::size(__GLXEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
