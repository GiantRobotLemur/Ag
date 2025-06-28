//! @file WriteGlyphGeometry/Helpers.hpp
//! @brief The declaration of various stand-alone utility functions.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __WRITE_GLYPH_GEOMETRY_HELPERS_HPP__
#define __WRITE_GLYPH_GEOMETRY_HELPERS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
std::wstring toFullPath(const std::wstring &path);
std::wstring changeFileExt(const std::wstring_view &fileName,
                           const std::wstring_view &newExt);
std::wstring_view getFileName(const std::wstring_view &filePath);
std::wstring getWin32ErrorMessage(uint32_t errorCode);
bool appendOptionalErrorMessage(std::wstring &error, uint32_t errorCode);
std::wstring getCRTErrorMessage(errno_t errorCode);
void appendOptionalCRTErrorMessage(std::wstring &error, errno_t errorCode);

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
