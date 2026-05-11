//! @file Text/CharacterSource.cpp
//! @brief The definition of an interface to an object which reads text from
//! an input source.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Text/CharacterSource.hpp"

namespace Ag {
namespace Text {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static constexpr size_t MinBufferSize = 32;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// StreamCharacterSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which produces characters by decoding a binary
//! input stream.
//! @param[in] input The stream to read from.
//! @param[in] initialBytes Initial bytes read from the stream, perhaps used to
//! identify the format, but need to be interpreted as character data. Can be
//! nullptr if @p initialCount is zero.
//! @param[in] initialCount The count of bytes in @p initialBytes. Can be zero.
//! @throws ArgumentNullException If @p input is nullptr.
StreamCharacterSource::StreamCharacterSource(Ag::IStream *input,
                                             uint8_cptr_t initialBytes /*= nullptr*/,
                                             size_t initialCount /*= 0*/) :
    _source(input),
    _commitOffset(0),
    _readOffset(0)
{
    if (input == nullptr)
        throw Ag::ArgumentNullException("input");

    _buffer.reserve(std::max(MinBufferSize, initialCount));

    if (initialCount > 0)
    {
        if (initialBytes == nullptr)
            throw Ag::ArgumentNullException("initialBytes");

        // Stoke the buffer with initial bytes.
        std::copy_n(initialBytes, initialCount, std::back_inserter(_buffer));
    }
}

//! @brief Sets the preferred size of the internal buffer.
//! @param[in] byteCount The preferred buffer size, in bytes.
void StreamCharacterSource::setBufferSize(size_t byteCount)
{
    _buffer.reserve(std::max(byteCount, MinBufferSize));
}

//! @brief Attempts to return the next byte from the buffer.
//! @param[out] next Receives the next byte, if one was available.
//! @retval true A byte was available and returned in @p next.
//! @retval false No more bytes were available in the buffer.
bool StreamCharacterSource::tryGetNextByte(uint8_t &next)
{
    if (_readOffset < _buffer.size())
    {
        next = _buffer.at(_readOffset);
        ++_readOffset;

        return true;
    }

    next = 0;
    return false;
}

//! @brief Restores bytes previously read by tryGetNextByte().
//! @param[in] offset The offset to roll back to, previously returned by
//! commit() or can be 0 after a call to tryRefillBuffer().
//! @throws ArgumentException if @p count is too small.
void StreamCharacterSource::rollback(size_t offset)
{
    if (offset < _commitOffset)
        throw ArgumentException("The rollback offset is too small.", "offset");

    _readOffset = offset;
}

//! @brief Marks all previously read bytes as consumed.
//! @return The buffer offset of the next byte to read which can be rolled back
//! to until the next call to commit().
size_t StreamCharacterSource::commit()
{
    _commitOffset = _readOffset;

    return _commitOffset;
}

//! @brief Gets the count of bytes still to be read in the buffer.
size_t StreamCharacterSource::getUnreadByteCount() const
{
    return _buffer.size() - _readOffset;
}

//! @brief Reads bytes directly from the input buffer.
//! @param[in] output The buffer to copy the bytes to.
//! @param[in] maxCount The maximum number of bytes to copy to @p output.
//! @return The actual number of bytes copied to @p output.
//! @remarks The bytes read are automatically marked as consumed (committed).
size_t StreamCharacterSource::readBytes(void *output, size_t maxCount)
{
    size_t bytesRead = 0;
    size_t maxRead = std::min(maxCount, _buffer.size() - _readOffset);
    uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(output);

    if (maxRead > 0)
    {
        // Empty the buffer.
        memcpy(target, _buffer.data() + _readOffset, maxRead);
        _readOffset += maxRead;
        bytesRead += maxRead;
    }

    if (_readOffset == _buffer.size())
    {
        // If we drained the buffer, mark it as empty.
        _buffer.clear();
        _commitOffset = _readOffset = 0;

        // Try to read more bypassing the cache.
        size_t preferredBufferSize = _buffer.capacity();

        while (bytesRead < maxCount)
        {
            // Calculate how much we have left to read.
            maxRead = maxCount - bytesRead;

            if (maxRead < preferredBufferSize)
            {
                // Its less than a buffers worth, read via the buffer.
                if (tryRefillBuffer())
                {
                    maxRead = std::min(maxRead, _buffer.size());

                    memcpy(target + bytesRead, _buffer.data(), maxRead);
                    _readOffset = maxRead;
                }

                // We've read all we can.
                break;
            }
            else
            {
                // Read directly from the input source.
                size_t sourceRead = _source->read(target + bytesRead, maxRead);
                bytesRead += sourceRead;

                if (sourceRead == 0)
                    break;
            }
        }
    }

    return bytesRead;
}

//! @brief Attempts to re-fill the buffer from the input source.
//! @retval true New bytes were read into the buffer.
//! @retval false No more bytes were read.
bool StreamCharacterSource::tryRefillBuffer()
{
    size_t preferredSize = _buffer.capacity();

    if (_commitOffset < _buffer.size())
    {
        // Ensure unconsumed bytes are preserved.
        _buffer.erase(_buffer.begin(), _buffer.begin() + _commitOffset);
        _readOffset -= _commitOffset;
        _commitOffset = 0;
    }
    else
    {
        // All bytes in the buffer had been read.
        _commitOffset = 0;
        _readOffset = 0;
        _buffer.clear();
    }

    size_t initialSize = _buffer.size();

    _buffer.resize(preferredSize);

    size_t bufferAvailable = preferredSize - initialSize;

    size_t bytesRead = _source->read(_buffer.data() + initialSize,
                                     bufferAvailable);

    if (bytesRead < bufferAvailable)
    {
        // Truncate the buffer, if necessary.
        _buffer.erase(_buffer.begin() + initialSize + bytesRead,
                      _buffer.end());
    }

    return bytesRead > 0;
}

////////////////////////////////////////////////////////////////////////////////
// Utf8StreamCharacterSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which reads bytes from a binary input stream
//! and interprets them as UTF-8 characters.
//! @param[in] input The binary input stream the object should read bytes from.
//! @param[in] initialBytes Initial bytes read from the stream, perhaps used to
//! identify the format, but need to be interpreted as character data. Can be
//! nullptr if @p initialCount is zero.
//! @param[in] initialCount The count of bytes in @p initialBytes. Can be zero.
Utf8StreamCharacterSource::Utf8StreamCharacterSource(Ag::IStream *input,
                                                     uint8_cptr_t initialBytes /*= nullptr*/,
                                                     size_t initialCount /*= 0*/) :
    StreamCharacterSource(input, initialBytes, initialCount)
{
}

// Inherited from ICharacterSource.
size_t Utf8StreamCharacterSource::readUtf8(utf8_ptr_t characters, size_t maxBytes)
{
    commit();

    // Ensure the buffer is initially stoked before attempting a translation.
    if ((getUnreadByteCount() == 0) && (tryRefillBuffer() == false))
        return 0;

    size_t written = 0;

    while (written < maxBytes)
    {
        size_t baseOffset = commit();
        size_t maxBuffered = getUnreadByteCount();
        size_t maxWrite = maxBytes - written;
        uint8_t next;

        // Read the first byte in the UTF-8 sequence.
        if (tryGetNextByte(next))
        {
            // Ensure that only whole code points are transferred.
            uint32_t sequenceLength;

            if (Utf::tryGetUTF8ByteCountFromLeadingByte(next, sequenceLength))
            {
                if (sequenceLength <= 1)
                {
                    // It's a 1-byte encoding, copy it to the buffer.
                    characters[written++] = static_cast<char>(next);
                }
                else if ((maxBuffered < sequenceLength) ||
                         (maxWrite < sequenceLength))
                {
                    // We don't have enough bytes in one buffer or the other for
                    // the entire code point encoding to be copied.
                    rollback(baseOffset);

                    // Try reading more bytes.
                    if (tryRefillBuffer() == false)
                        break;
                }
                else
                {
                    characters[written++] = static_cast<char>(next);

                    for (uint32_t i = 1; i < sequenceLength; ++i)
                    {
                        if (tryGetNextByte(next))
                        {
                            characters[written++] = static_cast<char>(next);
                        }
                        else
                        {
                            // We were told there were enough bytes, but there wasn't!
                            throw OperationException("Not enough bytes for an entire code point.");
                        }
                    }
                }
            }
        }
        else if (tryRefillBuffer() == false)
        {
            // There are no more bytes to read.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf8StreamCharacterSource::readUtf16(utf16_ptr_t characters, size_t maxWords)
{
    Utf::ToUtf16Converter outputConverter;
    size_t written = 0;

    while (written < maxWords)
    {
        // Mark the point where we might roll back to.
        size_t baseOffset = commit();
        size_t writeMax = maxWords - written;
        char32_t codePoint;

        if (tryGetBufferedCodePoint(codePoint))
        {
            uint32_t sequenceLength = outputConverter.setCodePoint(codePoint);

            if (sequenceLength > writeMax)
            {
                // Put the code point back, and return what we have.
                rollback(baseOffset);
                break;
            }
            else
            {
                while (outputConverter.tryGetNextCharacter(characters[written]))
                    ++written;
            }
        }
        else if (tryRefillBuffer() == false)
        {
            // We couldn't get a whole code point from the existing buffer, or
            // refill it, so give up.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf8StreamCharacterSource::readUtf32(utf32_ptr_t characters, size_t maxCodePoints)
{
    size_t written = 0;

    while (written < maxCodePoints)
    {
        // Mark the point where we might roll back to.
        if (tryGetBufferedCodePoint(characters[written]))
        {
            ++written;
        }
        else if (tryRefillBuffer() == false)
        {
            // We couldn't get a whole code point from the existing buffer, or
            // refill it, so give up.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf8StreamCharacterSource::readWide(wchar_ptr_t characters, size_t maxChars)
{
#ifdef WCHAR_IS_32BIT
    return readUtf32(reinterpret_cast<utf32_ptr_t>(characters), maxChars);
#else
    return readUtf16(reinterpret_cast<utf16_ptr_t>(characters), maxChars);
#endif
}

//! @brief Attempts to read the next Unicode code point from the buffer without
//! refilling it.
//! @param[out] next Receives the next code point.
//! @retval true A code point was successfully decoded from the current
//! contents of the internal buffer.
//! @retval false There were not enough bytes in the buffer to read an entire
//! Unicode code point.
//! @remarks The commit() member function is called before any bytes are read.
bool Utf8StreamCharacterSource::tryGetBufferedCodePoint(char32_t &next)
{
    next = U'\0';

    size_t baseOffset = commit();
    size_t maxRead = getUnreadByteCount();
    uint32_t sequenceLength;
    uint8_t nextByte;

    if (maxRead == 0)
        return false;

    while (tryGetNextByte(nextByte))
    {
        if (Utf::tryGetUTF8ByteCountFromLeadingByte(nextByte, sequenceLength))
        {
            if (maxRead < sequenceLength)
            {
                // There aren't enough buffered bytes to interpret the entire
                // code point.
                rollback(baseOffset);
                return false;
            }

            Utf::FromUtf8Converter converter;
            bool error = false;

            while (converter.tryConvert(nextByte, next, error) == false)
            {
                if (error)
                {
                    // Ignore the previous bytes.
                    commit();

                    // Try again.
                    break;
                }

                if (tryGetNextByte(nextByte) == false)
                {
                    // We ran out of bytes? We shouldn't have.
                    rollback(baseOffset);

                    return false;
                }
            }

            // Skip bytes which couldn't produce a valid code point.
            if (error)
                continue;

            // If we got this far, we fed enough bytes into the converter to get a
            // single Unicode code point out.
            return true;
        }
        else
        {
            // The leading byte was invalid, ignore it.
            commit();
        }
    }

    // If we can't get a leading byte, we can't produce a code point.
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// Utf16StreamCharacterSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which reads bytes from a binary input stream
//! and interprets them as UTF-16 characters.
//! @param[in] input The binary input stream the object should read bytes from.
//! @param[in] byteOrder The order in which bytes from the stream should be
//! interpreted when combined to form UTF-16 characters.
//! @param[in] initialBytes Initial bytes read from the stream, perhaps used to
//! identify the format, but need to be interpreted as character data. Can be
//! nullptr if @p initialCount is zero.
//! @param[in] initialCount The count of bytes in @p initialBytes. Can be zero.
Utf16StreamCharacterSource::Utf16StreamCharacterSource(Ag::IStream *input,
                                                       Bin::Endedness byteOrder /*= Bin::Endedness::Native*/,
                                                       uint8_cptr_t initialBytes /*= nullptr*/,
                                                       size_t initialCount /*= 0*/) :
    StreamCharacterSource(input, initialBytes, initialCount),
    _reorderBytes(Bin::ByteOrder::get(byteOrder)->requiresSwap())
{
}

// Inherited from ICharacterSource.
size_t Utf16StreamCharacterSource::readUtf8(utf8_ptr_t characters, size_t maxBytes)
{
    Utf::ToUtf8Converter converter;
    uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(characters);
    size_t written = 0;

    while (written < maxBytes)
    {
        // Mark the current buffer position.
        size_t baseOffset = commit();
        char32_t codePoint;

        // Read a whole Unicode code point from the buffer, if we can.
        if (tryGetBufferedCodePoint(codePoint))
        {
            // See if we can encode the code point into the output buffer.
            size_t maxWrite = maxBytes - written;
            uint32_t sequenceLength = converter.setCodePoint(codePoint);

            if (sequenceLength <= maxWrite)
            {
                // There is enough space in the output buffer to receive the
                // encoded code point.
                while (converter.tryGetNextByte(target[written]))
                    ++written;
            }
            else
            {
                // The output buffer isn't big enough.
                rollback(baseOffset);
            }
        }
        else if (tryRefillBuffer() == false)
        {
            // We couldn't read any more source bytes.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf16StreamCharacterSource::readUtf16(utf16_ptr_t characters, size_t maxWords)
{
    size_t written = 0;

    if (_reorderBytes)
    {
        while (written < maxWords)
        {
            if (tryReadWord(characters[written]))
            {
                ++written;
            }
            else if (tryRefillBuffer() == false)
            {
                break;
            }
        }
    }
    else
    {
        // Try to read the characters directly.
        return readBytes(characters, maxWords * 2) / 2;
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf16StreamCharacterSource::readUtf32(utf32_ptr_t characters, size_t maxCodePoints)
{
    size_t written = 0;

    while (written < maxCodePoints)
    {
        // Read a whole Unicode code point from the buffer, if we can.
        if (tryGetBufferedCodePoint(characters[written]))
        {
            ++written;
        }
        else if (tryRefillBuffer() == false)
        {
            // We couldn't read any more source bytes.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf16StreamCharacterSource::readWide(wchar_ptr_t characters, size_t maxChars)
{
#ifdef WCHAR_IS_32BIT
    return readUtf32(reinterpret_cast<utf32_ptr_t>(characters), maxChars);
#else
    return readUtf16(reinterpret_cast<utf16_ptr_t>(characters), maxChars);
#endif
}

//! @brief Attempts to read the next Unicode code point from the buffer without
//! refilling it.
//! @param[out] next Receives the next code point.
//! @retval true A code point was successfully decoded from the current
//! contents of the internal buffer.
//! @retval false There were not enough bytes in the buffer to read an entire
//! Unicode code point.
//! @remarks The commit() member function is called before any bytes are read.
bool Utf16StreamCharacterSource::tryGetBufferedCodePoint(char32_t &next)
{
    next = U'\0';

    size_t baseOffset = commit();
    size_t maxReadWords = getUnreadByteCount() / 2;
    uint32_t sequenceLength;
    char16_t nextWord;

    if (tryReadWord(nextWord) == false)
    {
        rollback(baseOffset);

        return false;
    }

    if (Utf::tryGetUTF16WordCountFromLeadingWord(nextWord, sequenceLength))
    {
        if (maxReadWords < sequenceLength)
        {
            // There aren't enough buffered bytes to interpret the entire
            // code point.
            rollback(baseOffset);

            return false;
        }

        Utf::FromUtf16Converter converter;
        bool error = false;

        while (converter.tryConvert(nextWord, next, error) == false)
        {
            if (error)
            {
                // Ignore the previous bytes.
                commit();

                return false;
            }

            if (tryReadWord(nextWord) == false)
            {
                // We ran out of bytes? We shouldn't have.
                rollback(baseOffset);

                return false;
            }
        }

        // If we got this far, we fed enough bytes into the converter to get a
        // single Unicode code point out.
        return true;
    }
    else
    {
        // The leading byte was invalid, ignore it.
        commit();

        return false;
    }
}

//! @brief Attempts to read the next UTF-16 character from the input stream
//! without re-filling the buffer.
//! @param[out] word Receives the next 16-bit character, adjusted for byte order.
//! @retval true A UTF-16 character was successfully read from the buffer and
//! returned in @p word.
//! @retval false There were not enough bytes in the buffer for a whole 16-bit
//! character.
//! @remarks The function does not commit any previously read bytes, nor does it
//! consume any if it returns false.
bool Utf16StreamCharacterSource::tryReadWord(char16_t &word)
{
    word = u'\0';

    if (getUnreadByteCount() < 2)
        return false;

    uint16_t inputWord;
    uint8_t *input = reinterpret_cast<uint8_t *>(&inputWord);

    if (tryGetNextByte(input[0]) &&
        tryGetNextByte(input[1]))
    {
        if (_reorderBytes)
        {
            word = static_cast<char16_t>(Bin::byteSwap(inputWord));
        }
        else
        {
            word = static_cast<char16_t>(inputWord);
        }

        return true;
    }

    return false;
}



////////////////////////////////////////////////////////////////////////////////
// Utf32StreamCharacterSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which reads bytes from a binary input stream
//! and interprets them as UTF-32 code points.
//! @param[in] input The binary input stream the object should read bytes from.
//! @param[in] byteOrder The order in which bytes from the stream should be
//! interpreted when combined to form UTF-32 code points.
//! @param[in] initialBytes Initial bytes read from the stream, perhaps used to
//! identify the format, but need to be interpreted as character data. Can be
//! nullptr if @p initialCount is zero.
//! @param[in] initialCount The count of bytes in @p initialBytes. Can be zero.
Utf32StreamCharacterSource::Utf32StreamCharacterSource(Ag::IStream *input,
                                                       Bin::Endedness byteOrder /*= Bin::Endedness::Native*/,
                                                       uint8_cptr_t initialBytes /*= nullptr*/,
                                                       size_t initialCount /*= 0*/) :
    StreamCharacterSource(input, initialBytes, initialCount),
    _reorderBytes(Bin::ByteOrder::get(byteOrder)->requiresSwap())
{
}

// Inherited from ICharacterSource.
size_t Utf32StreamCharacterSource::readUtf8(utf8_ptr_t characters, size_t maxBytes)
{
    Utf::ToUtf8Converter converter;
    uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(characters);
    size_t written = 0;

    while (written < maxBytes)
    {
        // Mark the current buffer position.
        size_t baseOffset = commit();
        char32_t codePoint;

        // Read a whole Unicode code point from the buffer, if we can.
        if (tryGetBufferedCodePoint(codePoint))
        {
            // See if we can encode the code point into the output buffer.
            size_t maxWrite = maxBytes - written;
            uint32_t sequenceLength = converter.setCodePoint(codePoint);

            if (sequenceLength <= maxWrite)
            {
                // There is enough space in the output buffer to receive the
                // encoded code point.
                while (converter.tryGetNextByte(target[written]))
                    ++written;
            }
            else
            {
                // The output buffer isn't big enough.
                rollback(baseOffset);
            }
        }
        else if (tryRefillBuffer() == false)
        {
            // We couldn't read any more source bytes.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf32StreamCharacterSource::readUtf16(utf16_ptr_t characters, size_t maxWords)
{
    size_t written = 0;

    Utf::ToUtf16Converter converter;

    while (written < maxWords)
    {
        size_t baseOffset = commit();
        char32_t codePoint;

        if (tryGetBufferedCodePoint(codePoint))
        {
            // Convert the code point, if the output buffer is large enough
            // to receive it.
            size_t wordsLeft = maxWords - written;
            uint32_t sequenceLength = converter.setCodePoint(codePoint);

            if (sequenceLength <= wordsLeft)
            {
                while (converter.tryGetNextCharacter(characters[written]))
                    ++written;
            }
            else
            {
                rollback(baseOffset);
                break;
            }
        }
        else if (tryRefillBuffer() == false)
        {
            // There was not more input data.
            break;
        }
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf32StreamCharacterSource::readUtf32(utf32_ptr_t characters, size_t maxCodePoints)
{
    size_t written = 0;

    if (_reorderBytes)
    {
        while (written < maxCodePoints)
        {
            // Read a whole Unicode code point from the buffer, if we can.
            if (tryGetBufferedCodePoint(characters[written]))
            {
                ++written;
            }
            else if (tryRefillBuffer() == false)
            {
                // We couldn't read any more source bytes.
                break;
            }
        }
    }
    else
    {
        // Read the code points directly.
        written = readBytes(characters, maxCodePoints * 4) / 4;
    }

    return written;
}

// Inherited from ICharacterSource.
size_t Utf32StreamCharacterSource::readWide(wchar_ptr_t characters, size_t maxChars)
{
#ifdef WCHAR_IS_32BIT
    return readUtf32(reinterpret_cast<utf32_ptr_t>(characters), maxChars);
#else
    return readUtf16(reinterpret_cast<utf16_ptr_t>(characters), maxChars);
#endif
}

//! @brief Attempts to read the next Unicode code point from the buffer without
//! refilling it.
//! @param[out] next Receives the next code point.
//! @retval true A code point was successfully decoded from the current
//! contents of the internal buffer.
//! @retval false There were not enough bytes in the buffer to read an entire
//! Unicode code point.
//! @remarks The commit() member function is called before any bytes are read.
bool Utf32StreamCharacterSource::tryGetBufferedCodePoint(char32_t &next)
{
    next = U'\0';

    if (getUnreadByteCount() < 4)
        return false;

    uint32_t rawCodePoint = 0;

    if (readBytes(&rawCodePoint, 4) != 4)
        return false;

    if (_reorderBytes)
        next = static_cast<char32_t>(Bin::byteSwap(rawCodePoint));
    else
        next = static_cast<char32_t>(rawCodePoint);

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an ICharacterSource implementation instances to read
//! characters from a binary input stream.
//! @param[in] input The input stream to read from.
//! @param[in] detectEncodingFromBOM True to try use the initial bytes of the input
//! stream to detect the character encoding. If no BOM is detected, use the
//! preferred encoding. False to use the preferred encoding.
//! @param[in] encoding The preferred character encoding.
//! @param[in] byteOrder The preferred byte order of multi-byte character encodings.
//! @return An instance of ICharacterSource which will read characters from
//! @p input.
StreamCharacterSourceUPtr createStreamCharacterSource(IStream *input,
                                                      bool detectEncodingFromBOM /*= true */,
                                                      Utf::Encoding encoding /*= Utf::Encoding::Utf8*/,
                                                      Bin::Endedness byteOrder /*= Bin::Endedness::Native*/)
{
    if (input == nullptr)
        throw Ag::ArgumentNullException("input");

    size_t initialCount = 0;
    uint8_ptr_t initialBytes = nullptr;
    uint8_t headerBuffer[4];

    if (detectEncodingFromBOM)
    {
        static const uint8_t Utf8Bom[]      = { 0xEF, 0xBB, 0xBF };
        static const uint8_t Utf16LeBom[]   = { 0xFF, 0xFE };
        static const uint8_t Utf16BeBom[]   = { 0xFE, 0xFF };
        static const uint8_t Utf32LeBom[]   = { 0xFF, 0xFE, 0x00, 0x00 };
        static const uint8_t Utf32BeBom[]   = { 0x00, 0x00, 0xFE, 0xFF };

        // Read the maximum number of bytes required to recognise a Unicode
        // character encoding.
        size_t headerSize = input->read(headerBuffer, std::size(headerBuffer));

        if ((headerSize >= std::size(Utf32LeBom)) &&
             memcmp(Utf32LeBom, headerBuffer, std::size(Utf32LeBom)) == 0)
        {
            // UTF-32 Little Endian.
            return std::make_unique<Utf32StreamCharacterSource>(input, Bin::Endedness::LittleEndian);
        }
        else if ((headerSize >= std::size(Utf32BeBom)) &&
                 memcmp(Utf32BeBom, headerBuffer, std::size(Utf32BeBom)) == 0)
        {
            // UTF-32 Big Endian.
            return std::make_unique<Utf32StreamCharacterSource>(input, Bin::Endedness::BigEndian);
        }
        else if ((headerSize >= std::size(Utf16LeBom)) &&
                 memcmp(Utf16LeBom, headerBuffer, std::size(Utf16LeBom)) == 0)
        {
            // UTF-16 Little Endian.
            return std::make_unique<Utf16StreamCharacterSource>(input, Bin::Endedness::LittleEndian,
                                                                headerBuffer + std::size(Utf16LeBom),
                                                                headerSize - std::size(Utf16LeBom));
        }
        else if ((headerSize >= std::size(Utf16BeBom)) &&
                 memcmp(Utf16BeBom, headerBuffer, std::size(Utf16BeBom)) == 0)
        {
            // UTF-16 Big Endian.
            return std::make_unique<Utf16StreamCharacterSource>(input, Bin::Endedness::BigEndian,
                                                                headerBuffer + std::size(Utf16BeBom),
                                                                headerSize - std::size(Utf16BeBom));
        }
        else if ((headerSize >= std::size(Utf8Bom)) &&
                 memcmp(Utf8Bom, headerBuffer, std::size(Utf8Bom)) == 0)
        {
            // UTF-8 Little Endian.
            return std::make_unique<Utf8StreamCharacterSource>(input,
                                                               headerBuffer + std::size(Utf8Bom),
                                                               headerSize - std::size(Utf8Bom));
        }
        else
        {
            // There is no byte order mark, use the preferred encoding and
            // consume the header bytes based on that encoding.
            initialBytes = headerBuffer;
            initialCount = headerSize;
        }
    }

    // Create a character source based on the preferred encoding, using the
    // bytes used to attempt to detect the BOM.
    switch (encoding)
    {
    default:
    case Utf::Utf8:
        return std::make_unique<Utf8StreamCharacterSource>(input, initialBytes,
                                                           initialCount);

    case Utf::Utf16:
        return std::make_unique<Utf16StreamCharacterSource>(input, byteOrder,
                                                            initialBytes,
                                                            initialCount);

    case Utf::Utf32:
        return std::make_unique<Utf32StreamCharacterSource>(input, byteOrder,
                                                            initialBytes,
                                                            initialCount);

    case Utf::Wide:
#ifdef WCHAR_IS_32BIT
        return std::make_unique<Utf32StreamCharacterSource>(input, byteOrder,
                                                            initialBytes,
                                                            initialCount);
#else
        return std::make_unique<Utf16StreamCharacterSource>(input, byteOrder,
                                                            initialBytes,
                                                            initialCount);
#endif
    }
}

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////

