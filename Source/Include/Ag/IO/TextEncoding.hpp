//! @file Ag/IO/TextEncoding.hpp
//! @brief The declaration of definitions required to support text-based
//! input and output.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_TEXT_ENCODING_HPP_
#define HEADER_IO_TEXT_ENCODING_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <bit>

#include <Ag/Core/Configuration.hpp>

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An enumeration expressing the binary encoding of text.
enum class TextEncoding : uint8_t
{
    //! @brief Each 8-bit quantity is a character. The lower 128 characters are
    //! defined by ASCII, the upper 128 by a code page which is region-specific.
    ASCII,

    //! @brief Unicode code points encoded as sequences of 1-4 bytes.
    UTF8,

    //! @brief Unicode code points encoded as 1 or 2 16-bit words with LSB-first
    //! byte ordering.
    UTF16_LittleEndian,

    //! @brief Unicode code points encoded as 1 or 2 16-bit words with MSB-first
    //! byte ordering.
    UTF16_BigEndian,

    //! @brief Unicode code points encoded as 32-bit words with LSB-first
    //! byte ordering.
    UTF32_LittleEndian,

    //! @brief Unicode code points encoded as 32-bit words with MSB-first
    //! byte ordering.
    UTF32_BigEndian,
};

//! @brief A namespace containing a set of pre-defined character encodings defined
//! relative to the host byte order.
namespace TextEncodings {

//! @brief A UTF-16 text encoding which uses the native byte order of the host system.
constexpr TextEncoding UTF16_Native =
    (std::endian::native == std::endian::little) ? TextEncoding::UTF16_LittleEndian :
                                                   TextEncoding::UTF16_BigEndian;

//! @brief A UTF-16 text encoding which uses the opposite of the native byte order
//! of the host system.
constexpr TextEncoding UTF16_Foreign =
    (std::endian::native == std::endian::big) ? TextEncoding::UTF16_LittleEndian :
                                                TextEncoding::UTF16_BigEndian;

//! @brief A UTF-32 text encoding which uses the native byte order of the host system.
constexpr TextEncoding UTF32_Native =
    (std::endian::native == std::endian::little) ? TextEncoding::UTF32_LittleEndian :
                                                   TextEncoding::UTF32_BigEndian;

//! @brief A UTF-32 text encoding which uses the opposite of the native byte order
//! of the host system.
constexpr TextEncoding UTF32_Foreign =
    (std::endian::native == std::endian::big) ? TextEncoding::UTF32_LittleEndian :
                                                TextEncoding::UTF32_BigEndian;

#ifdef WCHAR_IS_32BIT
//! @brief A text encoding for wide characters in the native byte order of the
//! host system (UTF-16 or 32).
constexpr TextEncoding Wide_Native = UTF32_Native;

//! @brief A text encoding for wide characters in the opposite byte order to
//! that of the host system (UTF-16 or 32).
constexpr TextEncoding Wide_Foreign = UTF32_Foreign;
#else
//! @brief A text encoding for wide characters in the native byte order of the
//! host system (UTF-16 or 32).
constexpr TextEncoding Wide_Native = UTF16_Native;

//! @brief A text encoding for wide characters in the opposite byte order to
//! that of the host system (UTF-16 or 32).
constexpr TextEncoding Wide_Foreign = UTF16_Foreign;
#endif

} // namespace TextEncodings

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
