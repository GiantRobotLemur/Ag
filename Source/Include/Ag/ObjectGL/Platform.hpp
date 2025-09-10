//! @file Ag/ObjectGL/Platform.hpp
//! @brief The declaration of platform-specific types needed by the C++
//! interpretation of the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_PLATFORM_HPP__
#define __AG_OBJECT_GL_PLATFORM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define WIN32_MEAN_AND_LEAN
#define NOMINMAX
#include <Windows.h>

#include "Ag/Core/Exception.hpp"
#endif // ifdef _WIN32

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
// Dispose of troublesome definitions amongst the WGL commands.
#undef wglUseFontOutlines
#undef wglUseFontBitmaps

#endif // ifdef _WIN32

// Define the calling convention (if needed).
#ifndef APIENTRY
#ifdef _WIN32
#define APIENTRY _stdcall
#else
#define APIENTRY
#endif // ifdef _WIN32
#endif // ifndef APIENTRY

////////////////////////////////////////////////////////////////////////////////
// Stand Alone Function Declarations
////////////////////////////////////////////////////////////////////////////////
namespace gl {

// Convenience functions to merge into generated OpenGL API implementation code.
void reportMissingFunction(const char *fnName, const char *apiName = nullptr);
void reportOpenGLError(const char *fnName, unsigned int firstErrorCode,
                       unsigned int (APIENTRY *errorReporterFn)() = nullptr,
                       const char *apiName = nullptr);

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
