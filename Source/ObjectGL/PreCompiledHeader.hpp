//! @file ObjectGL/PreCompiledHeader.hpp
//! @brief The root private pre-compiled header for the ObjectGL library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_PCH_HPP__
#define __AG_OBJECT_GL_PCH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#define NOMINMAX
#endif

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
#else
#include <X11/X.h>
#include <X11/Xlib.h>
#endif

#include <KHR/khrplatform.h>

// 3rd Party Libraries
#ifdef AG_OBJECT_GL_SDL3_DRIVER
#include <SDL3/SDL.h>
#endif

// Local Library headers
#include "Ag/Core.hpp"

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
