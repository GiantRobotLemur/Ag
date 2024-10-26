//! @file Core/CoreInternal.hpp
//! @brief The declaration of a set of definitions which are internal to the
//! Core module and should not be exposed in its public interface.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2023
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_INTERNAL_HPP__
#define __AG_CORE_INTERNAL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <map>
#include <string>
#include <utility>
#include <vector>

// Include system headers private to Ag Core here.
#ifdef _WIN32
#include "Win32API.hpp"
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <execinfo.h>
#include <time.h>
#include "PosixAPI.hpp"
#endif

#include "Ag/Core/Utils.hpp"
#include "Ag/Core/VariantType.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
// Needed to implement the Win32 file system schema, even under Linux.
#ifndef _MAX_PATH
#define _MAX_PATH 260
#endif

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
struct StackTracePrivate;
struct ActivationRecord;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
typedef std::pair<size_t, size_t> StringRange;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
// Implemented in StackTrace.cpp.
#ifdef _WIN32
size_t captureActivationRecords(const CONTEXT *context,
                                ActivationRecord *records,
                                size_t maxCount,
                                size_t skip);
#endif

size_t getStackTraceSize(const StackTracePrivate *info);
StackTracePrivate *cloneStackTrace(const StackTracePrivate *info);
void destroyStackTrace(StackTracePrivate *&info);

// Implemented in StringPrivate.cpp.
void appendPrintf(std::string &target, const char *format, ...);
bool tryReadLine(StdFilePtr &input, std::string &line);
void tokeniseLine(const std::string &line, std::vector<StringRange> &tokenRanges);
std::string_view getLineToken(const std::string &line, const StringRange &range);

// Implemented in VariantType.cpp.

//! @brief An object which represents a pair of variant types used to identify
//! a valid conversion.
struct VariantTypePair
{
    const VariantType *Source;
    const VariantType *Target;

    VariantTypePair(const VariantType *source, const VariantType *target);

    bool operator<(const VariantTypePair &rhs) const;
};

typedef std::map<VariantTypePair, VariantConversionFn> VariantConversionMap;

// Implemented in VariantTypes.cpp
VariantConversionMap &getConversionMap();

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
