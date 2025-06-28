//! @file Ag/Sdl3Tools/WrapperTypes.hpp
//! @brief The declaration of C++ wrapper types for C-based SDL structures.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_WRAPPER_TYPES_HPP__
#define __AG_SDL3_TOOLS_WRAPPER_TYPES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <type_traits>

#include <SDL3/SDL.h>

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#define DECLARE_WRAPPER(name,sdlType) struct name ## Deleter { \
    void operator()(sdlType *obj) const; }; \
    using name ## UPtr = std::unique_ptr<sdlType, name ## Deleter>
#define DECLARE_OPAQUE_WRAPPER(name,sdlType) struct name ## Deleter { \
    void operator()(sdlType obj) const; }; \
    using name ## UPtr = std::unique_ptr<std::remove_pointer<sdlType>::type, name ## Deleter>

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
DECLARE_WRAPPER(Renderer, SDL_Renderer);
DECLARE_WRAPPER(GLContext, std::remove_pointer_t<SDL_GLContext>);

}} // namespace Ag::SDL3

#undef DECLARE_WRAPPER
#undef DELCARE_OPAQUE_WRAPPER

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
