//! @file Text/CharacterSink.cpp
//! @brief The definition of an interface to an object which receives text
//! characters for processing or storage.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cassert>

#include <algorithm>

#include "Ag/Core/ByteOrder.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Text/CharacterSink.hpp"

namespace Ag {
namespace Text {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static constexpr size_t MinBufferSize = 32;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// StreamCharacterSink Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can write characters to a binary output stream.
StreamCharacterSink::StreamCharacterSink(Ag::IStream *output) :
    _sink(output)
{
    if (output == nullptr)
        throw Ag::ArgumentNullException("output");

    _buffer.reserve(MinBufferSize);
}

//! @brief Ensures any buffered data is flushed to the output stream.
StreamCharacterSink::~StreamCharacterSink()
{
    flush();
}

//! @brief Sets the size of the buffer used to cache data to write to the stream.
//! @param[in] byteCount The new preferred buffer size.
void StreamCharacterSink::setBufferSize(size_t byteCount)
{
    _buffer.reserve(std::max(byteCount, MinBufferSize));
}

// Inherited from ICharacterSink.
void StreamCharacterSink::flush()
{
    // Ensure there is nothing left in cache.
    flushCache();

    // Flush the underlying stream.
    _sink->flush();
}

//! @brief Receives encoded bytes for eventual output to the underlying sink.
//! @param[in] bytes The array of bytes to write.
//! @param[in] count The count of bytes in @p bytes.
//! @throws OperationException If the sink stops accepting bytes.
void StreamCharacterSink::writeBytes(const void *bytes, size_t count)
{
    if (count < 1)
        return;

    if (bytes == nullptr)
        throw Ag::ArgumentNullException("bytes");

    uint8_cptr_t input = reinterpret_cast<uint8_cptr_t>(bytes);
    size_t bytesWritten = 0;

    if (_buffer.empty() && (count >= _buffer.capacity()))
    {
        // Write trailing bytes directly to the output stream.
        while (bytesWritten < count)
        {
            size_t written = _sink->write(input + bytesWritten,
                                          count - bytesWritten);

            bytesWritten += written;

            if (written == 0)
                throw OperationException("Failed to write any bytes to text sink.");
        }

        return;
    }

    size_t freeSpace = _buffer.capacity() - _buffer.size();

    if (freeSpace > 0)
    {
        // Fill the remainder of the buffer.
        size_t bytesToWrite = std::min(freeSpace, count);
        bytesWritten = bytesToWrite;

        std::copy_n(input, bytesToWrite, std::back_inserter(_buffer));
    }

    // Flush if we filled the buffer with the leading bytes.
    if (_buffer.size() == _buffer.capacity())
        flushCache();

    // See if there are more bytes left to write.
    size_t bytesLeft = count - bytesWritten;

    if (bytesLeft > 0)
    {
        freeSpace = _buffer.capacity() - _buffer.size();

        if (bytesLeft < freeSpace)
        {
            // Write trailing bytes to the buffer.
            std::copy_n(input + bytesWritten, bytesLeft,
                        std::back_inserter(_buffer));
        }
        else
        {
            // Write trailing bytes directly to the output stream.
            while (bytesWritten < count)
            {
                size_t written = _sink->write(input + bytesWritten,
                                              count - bytesWritten);

                bytesWritten += written;

                if (written == 0)
                    throw OperationException("Failed to write any bytes to text sink.");
            }
        }
    }
}

//! @brief Ensures any outstanding cached bytes are written to the underlying
//! sink and clears the buffer.
void StreamCharacterSink::flushCache()
{
    if (_buffer.empty())
        return;

    size_t bytesWritten = 0;

    while (bytesWritten < _buffer.size())
    {
        size_t written = _sink->write(_buffer.data() + bytesWritten,
                                      _buffer.size() - bytesWritten);

        bytesWritten += written;

        if (written == 0)
            throw OperationException("Failed to write any bytes to text sink.");
    }

    // Empty the buffer.
    _buffer.clear();
}

////////////////////////////////////////////////////////////////////////////////
// Utf8StreamCharacterSink Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which encodes text as UTF-8 bytes and writes them
//! to an output stream.
Utf8StreamCharacterSink::Utf8StreamCharacterSink(Ag::IStream *output) :
    StreamCharacterSink(output)
{
}

// Inherited from ICharacterSink.
void Utf8StreamCharacterSink::writeUtf8(utf8_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    // The bytes are already encoded - don't perform any conversion.
    writeBytes(characters, count);
}

// Inherited from ICharacterSink.
void Utf8StreamCharacterSink::writeUtf16(utf16_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::FromUtf16Converter inputConverter;
    Utf::ToUtf8Converter outputConverter;
    uint8_t encodingBuffer[Utf::MaxUTF8EncodingLength];
    char32_t codePoint = U'\0';
    bool hasError = false;

    for (size_t i = 0; i < count; ++i)
    {
        // Convert 1 or 2 words into a Unicode code point.
        if (inputConverter.tryConvert(characters[i], codePoint, hasError))
        {
            if (hasError)
                continue;

            // Now encode the code point as UTF-8 bytes.
            size_t encodedBytes;
            uint32_t sequenceLength = outputConverter.setCodePoint(codePoint);

            // The buffer should ALWAYS be big enough for any valid encoding.
            assert(sequenceLength <= std::size(encodingBuffer));

            for (encodedBytes = 0;
                 (encodedBytes < sequenceLength) &&
                 outputConverter.tryGetNextByte(encodingBuffer[encodedBytes]);
                 ++encodedBytes)
            {
                // Deliberately empty.
            }

            // Write the entire UTF-8 encoded code point.
            writeBytes(encodingBuffer, encodedBytes);
        }
    }
}

// Inherited from ICharacterSink.
void Utf8StreamCharacterSink::writeUtf32(utf32_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::ToUtf8Converter outputConverter;
    uint8_t encodingBuffer[Utf::MaxUTF8EncodingLength];

    for (size_t i = 0; i < count; ++i)
    {
        // Encode the code point as UTF-8 bytes.
        size_t encodedBytes;
        uint32_t sequenceLength = outputConverter.setCodePoint(characters[i]);

        // The encoding should NEVER be larger than the buffer.
        assert(sequenceLength <= Utf::MaxUTF8EncodingLength);

        for (encodedBytes = 0;
             (encodedBytes < sequenceLength) &&
             outputConverter.tryGetNextByte(encodingBuffer[encodedBytes]);
             ++encodedBytes)
        {
            // Deliberately empty.
        }

        // Write the entire UTF-8 encoded code point.
        writeBytes(encodingBuffer, encodedBytes);
    }
}

// Inherited from ICharacterSink.
void Utf8StreamCharacterSink::writeWide(wchar_cptr_t characters, size_t count)
{
#ifdef WCHAR_IS_32BIT
    writeUtf32(reinterpret_cast<utf32_cptr_t>(characters), count);
#else
    writeUtf16(reinterpret_cast<utf16_cptr_t>(characters), count);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// Utf16StreamCharacterSink Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to encode text as UTF-16 words in a binary
//! output stream using a specific byte order.
//! @param[in] output The output stream to write the encoded characters to.
//! @param[in] byteOrder The order in which the bytes of UTF-16 words should be
//! written to the output stream.
Utf16StreamCharacterSink::Utf16StreamCharacterSink(Ag::IStream *output,
                                                   Bin::Endedness byteOrder /*= Bin::Endedness::Native*/) :
    StreamCharacterSink(output),
    _reorderBytes(Ag::Bin::ByteOrder::get(byteOrder)->requiresSwap())
{
}

// Inherited from ICharacterSink.
void Utf16StreamCharacterSink::writeUtf8(utf8_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::FromUtf8Converter inputConverter;
    Utf::ToUtf16Converter outputConverter;
    uint8_cptr_t input = reinterpret_cast<uint8_cptr_t>(characters);
    char32_t codePoint = U'\0';
    char16_t next = u'\0';
    bool hasError = false;

    for (size_t i = 0; i < count; ++i)
    {
        // Convert the UTF-8 bytes to a Unicode code point.
        if (inputConverter.tryConvert(input[i], codePoint, hasError))
        {
            if (hasError)
                continue;

            // Convert the code point into 1 or 2 UTF-16 words.
            outputConverter.setCodePoint(codePoint);

            while (outputConverter.tryGetNextCharacter(next))
            {
                writeWord(next);
            }
        }
    }
}

// Inherited from ICharacterSink.
void Utf16StreamCharacterSink::writeUtf16(utf16_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    if (_reorderBytes)
    {
        // Re-order the bytes in each word before writing to the sink.
        auto words = reinterpret_cast<const uint16_t *>(characters);
        uint16_t swapped;

        for (size_t i = 0; i < count; ++i)
        {
            swapped = Bin::byteSwap(words[i]);

            writeBytes(&swapped, 2);
        }
    }
    else
    {
        // Send the words to the sink without conversion.
        writeBytes(characters, count * 2);
    }
}

// Inherited from ICharacterSink.
void Utf16StreamCharacterSink::writeUtf32(utf32_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::ToUtf16Converter outputConverter;
    char16_t next = u'\0';

    for (size_t i = 0; i < count; ++i)
    {
        // Convert the code point into 1 or 2 UTF-16 words.
        outputConverter.setCodePoint(characters[i]);

        while (outputConverter.tryGetNextCharacter(next))
        {
            writeWord(next);
        }
    }
}

// Inherited from ICharacterSink.
void Utf16StreamCharacterSink::writeWide(wchar_cptr_t characters, size_t count)
{
#ifdef WCHAR_IS_32BIT
    writeUtf32(reinterpret_cast<utf32_cptr_t>(characters), count);
#else
    writeUtf16(reinterpret_cast<utf16_cptr_t>(characters), count);
#endif
}

//! @brief Writes a UTF-16 word to the output stream, enforcing the preferred
//! byte order in the process.
//! @param[in] utf16Word The word to write.
void Utf16StreamCharacterSink::writeWord(char16_t utf16Word)
{
    // Enforce byte order if necessary.
    if (_reorderBytes)
    {
        uint16_t swapped = Bin::byteSwap(static_cast<uint16_t>(utf16Word));

        writeBytes(&swapped, 2);
    }
    else
    {
        writeBytes(&utf16Word, 2);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Utf16StreamCharacterSink Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to encode text as UTF-32 code points in a binary
//! output stream using a specific byte order.
//! @param[in] output The output stream to write the encoded characters to.
//! @param[in] byteOrder The order in which the bytes of UTF-32 code points
//! should be written to the output stream.
Utf32StreamCharacterSink::Utf32StreamCharacterSink(Ag::IStream *output,
                                                   Bin::Endedness byteOrder /*= Bin::Endedness::Native*/) :
    StreamCharacterSink(output),
    _reorderBytes(Ag::Bin::ByteOrder::get(byteOrder)->requiresSwap())
{
}

// Inherited from ICharacterSink.
void Utf32StreamCharacterSink::writeUtf8(utf8_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::FromUtf8Converter inputConverter;
    Utf::ToUtf16Converter outputConverter;
    uint8_cptr_t input = reinterpret_cast<uint8_cptr_t>(characters);
    char32_t codePoint = U'\0';
    bool hasError = false;

    for (size_t i = 0; i < count; ++i)
    {
        // Convert the UTF-8 bytes to a Unicode code point.
        if (inputConverter.tryConvert(input[i], codePoint, hasError))
        {
            if (hasError)
                continue;

            writeCodePoint(codePoint);
        }
    }
}

// Inherited from ICharacterSink.
void Utf32StreamCharacterSink::writeUtf16(utf16_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    Utf::FromUtf16Converter inputConverter;
    char32_t codePoint = U'\0';
    bool hasError = false;

    for (size_t i = 0; i < count; ++i)
    {
        // Convert 1 or 2 words into a Unicode code point.
        if (inputConverter.tryConvert(characters[i], codePoint, hasError))
        {
            if (hasError)
                continue;

            writeCodePoint(codePoint);
        }
    }
}

// Inherited from ICharacterSink.
void Utf32StreamCharacterSink::writeUtf32(utf32_cptr_t characters, size_t count)
{
    if ((count == 0) || (characters == nullptr))
        return;

    if (_reorderBytes)
    {
        auto codePoints = reinterpret_cast<const uint32_t *>(characters);

        for (size_t i = 0; i < count; ++i)
        {
            uint32_t swapped = Bin::byteSwap(codePoints[i]);

            writeBytes(&swapped, 4);
        }
    }
    else
    {
        writeBytes(characters, count * 4);
    }
}

// Inherited from ICharacterSink.
void Utf32StreamCharacterSink::writeWide(wchar_cptr_t characters, size_t count)
{
#ifdef WCHAR_IS_32BIT
    writeUtf32(reinterpret_cast<utf32_cptr_t>(characters), count);
#else
    writeUtf16(reinterpret_cast<utf16_cptr_t>(characters), count);
#endif
}

//! @brief Writes a Unicode code point to the output stream, enforcing the
//! preferred byte order in the process.
//! @param[in] codePoint The character to write.
void Utf32StreamCharacterSink::writeCodePoint(char32_t codePoint)
{
    if (_reorderBytes)
    {
        uint32_t swapped = Bin::byteSwap(static_cast<uint32_t>(codePoint));

        writeBytes(&swapped, 4);
    }
    else
    {
        writeBytes(&codePoint, 4);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a character sink which encodes characters in a specified
//! encoding using native byte order and writes them to an output stream.
//! @param[in] output The output stream to write encoded characters to.
//! @param[in] encoding The encoding of the characters to write.
StreamCharacterSinkUPtr createCharacterStream(IStream *output,
                                              Utf::Encoding encoding)
{
    switch (encoding)
    {
    case Ag::Utf::Utf8:
        return std::make_unique<Utf8StreamCharacterSink>(output);

    case Ag::Utf::Utf16:
        return std::make_unique<Utf16StreamCharacterSink>(output);

    case Ag::Utf::Utf32:
        return std::make_unique<Utf32StreamCharacterSink>(output);

    case Ag::Utf::Wide:
        return std::make_unique<WideStreamCharacterSink>(output);

    default:
        throw Ag::ArgumentException("Unknown character encoding.", "encoding");
    }
}

//! @brief Creates a character sink which encodes characters in a specified
//! encoding and byte order, and writes them to an output stream.
//! @param[in] output The output stream to write encoded characters to.
//! @param[in] encoding The encoding of the characters to write.
//! @param[in] byteOrder The order in which the bytes of multi-byte encodings
//! should be written to the output stream.
StreamCharacterSinkUPtr createCharacterStream(IStream *output,
                                              Utf::Encoding encoding /*= Utf::Utf8*/,
                                              Bin::Endedness byteOrder /*= Bin::Endedness::Native*/)
{
    switch (encoding)
    {
    case Ag::Utf::Utf8:
        return std::make_unique<Utf8StreamCharacterSink>(output);

    case Ag::Utf::Utf16:
        return std::make_unique<Utf16StreamCharacterSink>(output, byteOrder);

    case Ag::Utf::Utf32:
        return std::make_unique<Utf32StreamCharacterSink>(output, byteOrder);

    case Ag::Utf::Wide:
        return std::make_unique<WideStreamCharacterSink>(output, byteOrder);

    default:
        throw Ag::ArgumentException("Unknown character encoding.", "encoding");
    }
}

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////

