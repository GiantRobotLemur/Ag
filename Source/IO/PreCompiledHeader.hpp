//! @file Ag/IO/PreCompiledHeader.hpp
//! @brief Includes all system or library header files required internally by
//! the library so that they can be pre-compiled once.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_IO_PCH_HPP_
#define HEADER_AG_IO_PCH_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Header Files
#include <cstdint>
#include <cmath>

// C++/STL Header Files
#include <algorithm>
#include <deque>
#include <limits>
#include <list>
#include <random>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <utility>

// 3rd Party Library Files
#ifndef _WIN32
// POSIX Headers required.
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#endif

// Upstream Library Files
#include <Ag/Core.hpp>

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
