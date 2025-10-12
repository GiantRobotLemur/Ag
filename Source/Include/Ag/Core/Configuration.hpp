//! @file Ag/Core/Configuration.hpp
//! @brief The declaration of various data types and macros used throughout the
//! core library component and beyond.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_CONFIGURATION_HPP__
#define __AG_CORE_CONFIGURATION_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <climits>
#include <cwchar>

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#define FUNC_DISPLAY_NAME __FUNCSIG__
#ifdef __INTELLISENSE__
// This messes with intelli-sense, so disable it when not building.
#define STRUCT_ALIGN(x)
#else
#define STRUCT_ALIGN(x) __declspec(align(x))
#endif
#else
#define FUNC_DISPLAY_NAME __PRETTY_FUNCTION__
#define STRUCT_ALIGN(x) __attribute__ ( (aligned(x)) )
#endif

// Function-style macros in class declarations don't mix well with Doxygen
// and intelli-sense, so define some concrete alignments here.
#define STRUCT_ALIGN_8 STRUCT_ALIGN(8)
#define STRUCT_ALIGN_16 STRUCT_ALIGN(16)
#define STRUCT_ALIGN_32 STRUCT_ALIGN(32)
#define STRUCT_ALIGN_64 STRUCT_ALIGN(64)

#if WCHAR_MAX > 0xFFFF
#define WCHAR_IS_32BIT
#endif

#if SIZE_MAX > 0xFFFFFFFF
#define IS_64_BIT
#else
#define IS_32_BIT
#endif

#ifdef _MSC_VER
#define DISABLE_WARNING_PUSH __pragma(warning(push))
#define DISABLE_WARNING_POP __pragma(warning(pop))
#define DISABLE_WARNING_UNREF_PARAM
#define DISABLE_WARNING_UNREF_FUNCITON
#define DISABLE_WARNING_ALIGN_PADDING __pragma(warning(disable : 4324))

#elif defined(__GNUC__) || defined (__clang__)
#define DO_PRAGMA(X) _Pragma(#X)
#define DISABLE_WARNING_PUSH DO_PRAGMA(GCC diagnostic push)
#define DISABLE_WARNING_POP DO_PRAGMA(GCC diagnostic pop)
#define DISABLE_WARNING(warningName)   DO_PRAGMA(GCC diagnostic ignored #warningName)
#define DISABLE_WARNING_UNREF_PARAM   DISABLE_WARNING(-Wunused-parameter)
#define DISABLE_WARNING_UNREF_FUNCITON DISABLE_WARNING(-Wunused-function)
#define DISABLE_WARNING_ALIGN_PADDING
#else
#define DISABLE_WARNING_PUSH
#define DISABLE_WARNING_POP
#define DISABLE_WARNING_UNREF_PARAM
#define DISABLE_WARNING_UNREF_FUNCITON
#define DISABLE_WARNING_ALIGN_PADDING
#endif

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @addtogroup AgFundamentals
//! @{

//! @brief An alias for a pointer to an array of bytes.
typedef uint8_t *uint8_ptr_t;

//! @brief An alias for a const pointer to an array of bytes.
typedef const uint8_t *uint8_cptr_t;

//! @brief An alias for a pointer to an array of UTF-8 encoded characters.
typedef char *utf8_ptr_t;

//! @brief An alias for a const pointer to an array of UTF-8 encoded characters.
typedef const char *utf8_cptr_t;

//! @brief An alias for a pointer to an array of UTF-16 encoded characters.
typedef char16_t *utf16_ptr_t;
typedef const char16_t *utf16_cptr_t;

//! @brief An alias for a pointer to an array of UTF-32 encoded characters, or
//! raw Unicode code points.
typedef char32_t *utf32_ptr_t;

//! @brief An alias for a const pointer to an array of UTF-32 encoded
//! characters, or raw Unicode code points.
typedef const char32_t *utf32_cptr_t;

//! @brief An alias for a pointer to an array of wide characters which represent
//! UTF-16 words on Windows platforms and Unicode code points on POSIX platforms.
typedef wchar_t *wchar_ptr_t;

//! @brief An alias for a const pointer to an array of wide characters which
//! represent UTF-16 words on Windows platforms and Unicode code points on POSIX
//! platforms.
typedef const wchar_t *wchar_cptr_t;

//! @}

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
