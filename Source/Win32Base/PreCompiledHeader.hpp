//! @file Ag/Win32Base/PreCompiledHeader.hpp
//! @brief Includes all system or library header files required internally by
//! the library so that they can be pre-compiled once.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
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
#include <cstdint>

// C++/STL Header Files


// 3rd Party Library Files
#define NOMINMAX
#define UNICODE
#include <Windows.h>
#include <objbase.h>

// Upstream Library Files
#include <Ag/Core.hpp>

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
