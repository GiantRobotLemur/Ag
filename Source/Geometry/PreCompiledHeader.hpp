//! @file Ag/Geometry/PreCompiledHeader.hpp
//! @brief Includes all system or library header files required internally by
//! the library so that they can be pre-compiled once.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_PCH_HPP__
#define __AG_GEOMETRY_PCH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Header Files
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
#ifdef _MSC_VER
// On MSVC, disable warning C4201: non-standard extension used: nameless
// struct/union for GLM headers.
#pragma warning ( push )
#pragma warning ( disable : 4201 )
#endif

#ifdef _MSC_VER
#pragma warning ( pop )
#endif // defined _MSC_VER

// Upstream Library Files
#include <Ag/Core.hpp>

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
