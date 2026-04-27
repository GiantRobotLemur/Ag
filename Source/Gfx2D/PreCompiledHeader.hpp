//! @file Gfx2D/PreCompiledHeader.hpp
//! @brief The root private pre-compiled header for the Gfx2D project.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GFX_2D_PCH_HPP__
#define __AG_GFX_2D_PCH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Headers
#include <cmath>

#if defined(_MSC_VER) && defined(_M_AMD64)
#include <xmmintrin.h>
#endif

// C++/STL Headers
#include <algorithm>
#include <memory>
#include <utility>

// System Headers (required by the public Core API).

// Local Headers
#include "Ag/Core.hpp"
#include "Ag/Geometry.hpp"

#ifdef AG_OBJECT_GL
// ObjectGL can be linked.
#include "Ag/ObjectGL.hpp"
#endif // ifdef AG_OBJECT_GL

#ifdef AG_SDL3_TOOLS
#include "Ag/Sdl3Tools.hpp"
#endif // ifdef AG_SDL3_TOOLS

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
