//! @file Ag/ObjectGL/WGLDriver.hpp
//! @brief The declaration of an object which uses direct calls to the WGL API
//! to create an OpenGL context.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_WGL_DRIVER_HPP__
#define __AG_OBJECT_GL_WGL_DRIVER_HPP__

#ifdef _WIN32

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Driver.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which uses direct calls to the WGL API to create an
//! OpenGL context.
//! @note The 'drawable' referred to by render contexts from this driver is an
//! handle to a Win32 window (HWND).
class WGLDriver : public IDriver
{
public:
    // Construction/Destruction
    WGLDriver() = default;
    virtual ~WGLDriver() = default;

    // Operations
    virtual DisplayContext createDisplayDevice(const DisplayFormat &format) const override;
};

} // namespace gl

#endif // ifdef _WIN32
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
