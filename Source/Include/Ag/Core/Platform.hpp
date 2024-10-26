//! @file Ag/Core/Platform.hpp
//! @brief The includes platform-specific headers required by the public
//! Ag Core API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_PLATFORM_HPP__
#define __AG_CORE_PLATFORM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32

#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN
#endif

#ifndef UNICODE
#define UNICODE
#endif

#ifndef NOMINMAX
#define NOMINMAX    // Macros min(a,b) and max(a,b)
#endif

#include <Windows.h>

#else // ifndef _WIN32

#include <csetjmp>
#include <csignal>
#include <execinfo.h>
#include <nl_types.h>
#include <langinfo.h>

#endif

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
