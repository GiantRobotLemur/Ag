//! @file Sdl3Tools/WrapperTypes.cpp
//! @brief The definition of C++ wrapper types for C-based SDL structures.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <type_traits>

#include <SDL3/SDL.h>

#include "Ag/Sdl3Tools/WrapperTypes.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#define IMPLEMENT_WRAPPER(name,sdlType,destroyFnName) \
    void name ## Deleter::operator()(sdlType *obj) const \
    { if (obj != nullptr) destroyFnName(obj); }

#define IMPLEMENT_OPAQUE_WRAPPER(name,sdlType,destroyFnName) \
    void name ## Deleter::operator()(sdlType obj) const \
    { if (obj != nullptr) destroyFnName(obj); }

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Definitions
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_WRAPPER(Renderer, SDL_Renderer, SDL_DestroyRenderer);
IMPLEMENT_WRAPPER(GLContext, std::remove_pointer_t<SDL_GLContext>, SDL_GL_DestroyContext);

}} // namespace Ag::SDL3

#undef IMPLEMENT_WRAPPER
#undef IMPLEMENT_OPAQUE_WRAPPER

////////////////////////////////////////////////////////////////////////////////

