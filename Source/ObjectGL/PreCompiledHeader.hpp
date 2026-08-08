//! @file ObjectGL/PreCompiledHeader.hpp
//! @brief The root private pre-compiled header for the ObjectGL library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_PCH_HPP_
#define HEADER_AG_OBJECT_GL_PCH_HPP_

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define NOMINMAX
#endif

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Headers
#include <cstddef>
#include <cstdint>
#include <cctype>
#include <cstring>

// C++/STL Headers
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

// System Headers
#ifdef _WIN32
#include <Windows.h>
#endif

#include <KHR/khrplatform.h>

// 3rd Party Libraries
#ifdef AG_OBJECT_GL_SDL2_DRIVER
#include <SDL.h>
#endif

#ifdef AG_OBJECT_GL_SDL3_DRIVER
#include <SDL3/SDL.h>
#endif

// Local Library headers
#include "Ag/Core.hpp"

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
