//! @file Ag/ObjectGL/SDL3Driver.hpp
//! @brief The declaration of an implementation of an OpenGL driver which uses
//! libSDL3.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_SDL3_DRIVER_HPP__
#define __AG_OBJECT_GL_SDL3_DRIVER_HPP__

#ifdef AG_OBJECT_GL_SDL3_DRIVER

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Driver.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of an OpenGL driver which uses libSDL3.
//! @note The 'drawable' referred to by render contexts from this driver is an
//! SDL_Window pointer.
class SDL3Driver : public IDriver
{
public:
    // Construction/Destruction
    SDL3Driver() = default;
    virtual ~SDL3Driver() = default;

    // Overrides
    virtual DisplayContext createDisplayDevice(const DisplayFormat &format) const override;
};

} // namespace gl

#endif // ifdef AG_OBJECT_GL_SDL3_DRIVER
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
