//! @file Ag/Sdl3Tools/OpenGL.hpp
//! @brief The declaration of tools for operating with OpenGL on top of SDL.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_OPEN_GL_HPP__
#define __AG_SDL3_TOOLS_OPEN_GL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <unordered_set>

#include <Ag/Core.hpp>

namespace Ag {
namespace SDL3 {

//! A structure which provides information about an OpenGL implementation.
struct OpenGLInfo
{
    // Public Fields
    Version MaxVersion;
    String Vendor;
    String Renderer;
    StringSet Extensions;

    // Construction/Destruction
    OpenGLInfo();
    ~OpenGLInfo() = default;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
bool tryGetOpenGLCoreProfileInfo(OpenGLInfo &info);

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
