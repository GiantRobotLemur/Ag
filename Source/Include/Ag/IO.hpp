//! @file Ag/IO.hpp
//! @brief The root public header file of the IO library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_IO_HPP_
#define HEADER_AG_IO_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
// Included roughly in dependency order:
#include <Ag/Core.hpp>

#include "IO/Exceptions.hpp"
#include "IO/ISeekableStream.hpp"
#include "IO/MemoryStream.hpp"
#include "IO/SeekableFileStream.hpp"
#include "IO/BufferedInputStream.hpp"
#include "IO/BufferedOutputStream.hpp"

#include "IO/HierarchySerialization.hpp"

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
