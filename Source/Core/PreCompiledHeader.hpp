//! @file Ag/Core/PreCompiledHeader.hpp
//! @brief The root private pre-compiled header for the Core project.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_PCH_HPP__
#define __AG_CORE_PCH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// C/CRT Headers
#ifdef _MSC_VER
#include <intrin.h>
#include <stdlib.h>
#endif

#include <cctype>
#include <cmath>
#include <climits>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cuchar>
#include <cwchar>
#include <cwctype>

// C++/STL Headers
#include <algorithm>
#include <atomic>
#include <exception>
#include <deque>
#include <functional>
#include <initializer_list>
#include <ios>
#include <iomanip>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <set>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// System Headers (required by the public Core API).
#include "Ag/Core/Platform.hpp"

// Include libbz2 for internal compression services.
#include <bzlib.h>

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
