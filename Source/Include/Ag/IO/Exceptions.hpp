//! @file Ag/IO/Exceptions.hpp
//! @brief The declaration of
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_EXCEPTIONS_HPP_
#define HEADER_IO_EXCEPTIONS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"
#include "ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An exception thrown when the mechanism of reading or writing data
//! from or to a stream has failed.
class IOException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static utf8_cptr_t Domain;

    // Construction
    IOException(const std::string_view &detail);
};

//! @brief An exception thrown when the data read from an IO device was not in
//! the expected format.
class DataFormatException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static utf8_cptr_t Domain;

    // Construction
    DataFormatException(const std::string_view &detail);
};

//! @brief An exception thrown when a serialized object does not contain a
//! named property.
class PropertyNotFoundException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static utf8_cptr_t Domain;

    // Construction
    PropertyNotFoundException(string_cref_t propertyName);
};

//! @brief An exception thrown when a serialized value cannot be interpreted as
//! a specific data type.
class PropertyTypeException : public Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static utf8_cptr_t Domain;

    // Construction
    PropertyTypeException(string_cref_t propertyName,
                          const std::string_view &requestedType);
    PropertyTypeException(const std::string_view &requestedType);
};

//! @brief An exception thrown when the program attempts to access a byte block
//! field which is too large to be manipulated as a linear block.
class FieldTooBigException : public Exception
{
public:
    //! @brief The domain used to annotate exceptions of this type.
    static utf8_cptr_t Domain;

    // Construction
    FieldTooBigException(StreamLength blockSize);
};

//! @brief An exception raised when a sequence of bytes is encountered which does
//! not correspond to a valid Unicode code point.
class InvalidEncodingSequenceException : public Ag::Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction
    InvalidEncodingSequenceException(const std::string_view &encodingName,
                                     uint8_cptr_t bytes, size_t count);
};

//! @brief An exception raised when a sequence of bytes is encountered at the
//! beginning of a text stream which does not represent a valid Byte Order Mark.
class InvalidBOMException : public Ag::Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction
    InvalidBOMException(uint8_cptr_t bytes, size_t count);
};

//! @brief An exception raised when an invalid Unicode code point was passed
//! for output encoding.
class CharacterEncodingFailureException : public Ag::Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction
    CharacterEncodingFailureException(uint8_cptr_t sequence, size_t count);
    CharacterEncodingFailureException(utf16_cptr_t sequence, size_t count);
    CharacterEncodingFailureException(char32_t ch);
};

//! @brief An exception raised when an Unicode code point was sent to output
//! which has no corresponding encoding in the output format.
class NoCharacterEncodingException : public Ag::Exception
{
public:
    // Public Data
    //! @brief The domain used to annotate exceptions of this type.
    static const char *Domain;

    // Construction
    NoCharacterEncodingException(const std::string_view &outputFormat, char32_t ch);
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
