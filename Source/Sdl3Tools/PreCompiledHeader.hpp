//! @file Ag/Sdl3Tools/PreCompiledHeader.hpp
//! @brief Includes all system or library header files required internally by
//! the library so that they can be pre-compiled once.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_PCH_HPP__
#define __AG_SDL3_TOOLS_PCH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Header Files
#include <cctype>
#include <cmath>
#include <cstdint>

// C++/STL Header Files
#include <deque>
#include <list>
#include <memory>
#include <random>
#include <type_traits>
#include <unordered_set>

// 3rd Party Library Files
#include <SDL3/SDL.h>

// Upstream Library Files
#include <Ag/Core.hpp>
#include <Ag/Sdl3Tools.hpp>

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
