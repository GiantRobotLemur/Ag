//! @file CodePoint.hpp
//! @brief The declaration of functions which manipulate and test Unicode
//! code point values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_CORE_CODE_POINT_HPP_
#define HEADER_AG_CORE_CODE_POINT_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cuchar>

#include "Memory.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An alias for a view of contiguous writeable memory containing
//! Unicode code points.
using CodePointView = View<char32_t>;

//! An alias for a read-only view of contiguous memory containing Unicode
//! code points.
using CodePointConstView = ConstView<char32_t>;

//! @brief An alias for a buffer of Unicode code points.
using CodePointCollection = std::vector<char32_t>;

namespace CodePoint {

////////////////////////////////////////////////////////////////////////////////
// Data Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Defines the minimum value of any valid Unicode code point.
constexpr char32_t MinValue = U'\x000000';

//! @brief Defines the maximum value of any valid Unicode code point.
constexpr char32_t MaxValue = U'\x10FFFF';

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
// TODO: Create a non-locale-specific implementation of these functions based
// on the ISO 30112 standard rather than the C runtime library.
char32_t toUpper(char32_t codePoint);
char32_t toLower(char32_t codePoint);
bool isWhiteSpace(char32_t codePoint);
bool isBlank(char32_t codePoint);
bool isAlphaNumeric(char32_t codePoint);
bool isNumeric(char32_t codePoint);
bool isHexDigit(char32_t codePoint);
bool isLetter(char32_t codePoint);
bool isPrintable(char32_t codePoint);
bool isValid(char32_t codePoint);

}} // namespace Ag::CodePoint

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
