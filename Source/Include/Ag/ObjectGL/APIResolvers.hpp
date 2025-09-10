//! @file Ag/ObjectGL/APIResolvers.hpp
//! @brief The declaration of various implementations of Api
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_API_RESOLVERS_HPP__
#define __AG_OBJECT_GL_API_RESOLVERS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"
#include "EnumTypes.hpp"
#include "ExtensionSet.hpp"

#ifdef AG_OBJECT_GL_SDL3_DRIVER
#include <SDL3/SDL.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
#ifdef AG_OBJECT_GL_SDL3_DRIVER
// This code will be enabled if SDL.h has been included, specifically SDL_video.h.

//! @brief Resolves OpenGL entry points for use with the SDL2 or 3 library.
class SDLResolver : public APIResolver
{
public:
    // Construction/Destruction
    SDLResolver() = default;
    virtual ~SDLResolver() = default;

    // Overrides
    // Inherited from APIResolver.
    virtual bool isExtensionPresent(const char *extName) const
    {
        return SDL_GL_ExtensionSupported(extName);
    }

    // Inherited from APIResolver.
    virtual void *resolveEntryPoint(const char *fnName) const
    {
        return SDL_GL_GetProcAddress(fnName);
    }

    // Inherited from APIResolver.
    virtual APIResolver::GetNextErrorFn getErrorReporterProc() const
    {
        return reinterpret_cast<APIResolver::GetNextErrorFn>(SDL_GL_GetProcAddress("glGetError"));
    }
};

// The code is the same for SDL2 and SDL3, but that might change, so define a
// specific alias.
using SDL3Resolver = SDLResolver;

#endif // ifdef AG_OBJECT_GL_SDL3_DRIVER


#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
