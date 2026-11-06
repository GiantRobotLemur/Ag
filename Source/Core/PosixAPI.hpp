//! @file Core/PosixAPI.hpp
//! @brief The declaration of some helper functions which assist the user of
//! the POSIX API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_POSIX_API_HPP_
#define HEADER_AG_CORE_POSIX_API_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/String.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
String getProgramFileName();
String getProgramDirectory();
String getWorkingDirectory();
String getTempDirectory();
String getHomeDirectory();
void getProgramArgs(std::vector<char> &buffer, std::vector<utf8_cptr_t> &args);

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
