//! @file IO/TextInputStream.cpp
//! @brief The definition of an object which can convert a stream of bytes
//! into a stream of Unicode characters.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstring>

#include <algorithm>
#include <bit>
#include <initializer_list>

#include "Ag/IO/BufferedInputStream.hpp"
#include "Ag/IO/TextInputStream.hpp"

namespace Ag {
namespace IO {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of ICharacterDecoder which makes a ham-fisted job
//! of decoding ASCII-encoded bytes into Unicode code points.
class ASCIIDecoder : public ICharacterDecoder
{
public:
    // Construction/Destruction
    ASCIIDecoder() = default;

    // Overrides

    // Inherited from ICharacterDecoder.
    virtual std::string_view getName() const override
    {
        return "ASCII";
    }

    // Inherited from ICharacterDecoder.
    virtual bool tryDecode(uint8_t next, char32_t &ch, bool &error) override
    {
        // Simply pass through the character code, widened to 32-bits.
        error = false;
        ch = static_cast<char32_t>(next);

        return true;
    }
};

//! @brief An implementation of ICharacterDecoder which interprets UTF-8-encoded
//! bytes into Unicode code points.
class UTF8Decoder : public ICharacterDecoder
{
private:
    // Internal Fields
    Utf::FromUtf8Converter _converter;
public:
    // Construction/Destruction
    UTF8Decoder() = default;

    // Overrides

    // Inherited from ICharacterDecoder.
    virtual std::string_view getName() const override
    {
        return "UTF-8";
    }

    // Inherited from ICharacterDecoder.
    virtual bool tryDecode(uint8_t next, char32_t &ch, bool &error) override
    {
        bool decodeComplete = _converter.tryConvert(next, ch, error);

        if (error)
        {
            // Reset the state after an error.
            _converter.reset();
        }

        return decodeComplete || error;
    }
};

//! @brief An implementation of ICharacterDecoder which interprets UTF-16-encoded
//! words into Unicode code points.
//! @tparam ByteSwap True of 16-bit words read from the input stream are in
//! a format opposite to that of the host architecture and need to be swapped.
template<bool ByteSwap>
class UTF16Decoder : public ICharacterDecoder
{
private:
    // Internal Fields
    Utf::FromUtf16Converter _converter;
    uint8_t _lowByte = 0;
    uint8_t _offset = 0;
public:
    // Construction/Destruction
    UTF16Decoder() = default;

    // Overrides

    // Inherited from ICharacterDecoder.
    virtual std::string_view getName() const override
    {
        constexpr std::endian reverseNative = (std::endian::native == std::endian::little) ? std::endian::big :
                                                                                             std::endian::little;
        constexpr std::endian ByteOrder = ByteSwap ? std::endian::native : reverseNative;

        if constexpr (ByteOrder == std::endian::little)
        {
            return "UTF16-LE";
        }
        else
        {
            return "UTF16-BE";
        }
    }

    // Inherited from ICharacterDecoder.
    virtual bool tryDecode(uint8_t next, char32_t &ch, bool &error) override
    {
        if (_offset == 0)
        {
            // We have the low byte, not enough to decode.
            _lowByte = next;
            _offset = 1;

            return false;
        }
        else
        {
            // We have the high byte, try decoding it.
            uint16_t readWord;
            _offset = 0;

            if constexpr (ByteSwap)
            {
                readWord = (static_cast<uint16_t>(_lowByte) << 8) | next;
            }
            else
            {
                readWord = (static_cast<uint16_t>(next) << 8) | _lowByte;
            }

            bool decodeComplete =  _converter.tryConvert(static_cast<char16_t>(readWord),
                                                         ch, error);

            if (error)
            {
                // Reset the state after an error.
                _converter.reset();
            }

            return decodeComplete || error;
        }
    }
};

//! @brief An implementation of ICharacterDecoder which interprets UTF-32-encoded
//! words into Unicode code points.
//! @tparam ByteSwap True of 32-bit words read from the input stream are in
//! a format opposite to that of the host architecture and need to be swapped.
template<bool ByteSwap>
class UTF32Decoder : public ICharacterDecoder
{
private:
    // Internal Fields
    uint32_t _word = 0;
    uint8_t _offset = 0;
public:
    // Construction/Destruction
    UTF32Decoder() = default;

    // Overrides

    // Inherited from ICharacterDecoder.
    virtual std::string_view getName() const override
    {
        constexpr std::endian reverseNative = (std::endian::native == std::endian::little) ? std::endian::big :
            std::endian::little;
        constexpr std::endian ByteOrder = ByteSwap ? std::endian::native : reverseNative;

        if constexpr (ByteOrder == std::endian::little)
        {
            return "UTF32-LE";
        }
        else
        {
            return "UTF32-BE";
        }
    }

    // Inherited from ICharacterDecoder.
    virtual bool tryDecode(uint8_t next, char32_t &ch, bool &error) override
    {
        // We have a low byte, not enough to decode.
        _word |= static_cast<uint32_t>(next) << (_offset * 8);

        ++_offset;

        if (_offset == 4)
        {
            // We have all the bytes we need.
            uint32_t readWord;

            if constexpr (ByteSwap)
            {
                readWord = std::byteswap(_word);
            }
            else
            {
                readWord = _word;
            }

            // Reset for the next code point.
            _word = 0;
            _offset = 0;

            ch = static_cast<char32_t>(readWord);
            error = (readWord > CodePointMax);

            return !error;
        }
        else
        {
            // Not enough bytes yet.
            return false;
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Instantiates an object which will interpret sequences of bytes into
//! Unicode code points using a specified encoding.
//! @param[in] encoding The encoding to instantiate a decoder for.
//! @returns An object capable of interpreting the specified character encoding.
ICharacterDecoderUPtr createDecoder(TextEncoding encoding)
{
    ICharacterDecoderUPtr decoder;

    switch (encoding)
    {
    case TextEncoding::ASCII:
        decoder.reset(new ASCIIDecoder());
        break;

    case TextEncoding::UTF8:
        decoder.reset(new UTF8Decoder());
        break;

    case TextEncoding::UTF16_LittleEndian:
        decoder.reset(new UTF16Decoder<std::endian::native != std::endian::little>());
        break;

    case TextEncoding::UTF16_BigEndian:
        decoder.reset(new UTF16Decoder<std::endian::native != std::endian::big>());
        break;

    case TextEncoding::UTF32_LittleEndian:
        decoder.reset(new UTF32Decoder<std::endian::native != std::endian::little>());
        break;

    case TextEncoding::UTF32_BigEndian:
        decoder.reset(new UTF32Decoder<std::endian::native != std::endian::big>());
        break;

    default:
        throw NotSupportedException("The requested text encoding it not supported.");
    }

    return decoder;
}

//! @brief Attempts to read the next byte from an input stream.
//! @param[in] input The stream to read from.
//! @param[out] next The next byte read from the stream if successful.
//! @retval true A byte was successfully read and returned in @p next.
//! @retval false There were no bytes available in @p input.
bool tryGetNextByte(IStream *input, uint8_t &next)
{
    return input->read(&next, 1) == 1;
}

//! @brief Attempts to interpret a Byte Order Mark at the beginning of a text
//! stream.
//! @param[in] input The stream to read bytes from.
//! @param[in] decodeBuffer The buffer to receive bytes used in decoding. This
//! should be able to contain at least 4 bytes.
//! @param[in,out] decodedByteCount Is passed with the maximum count of bytes
//! @p decodeBuffer can receive, and is updated with the count of unconsumed bytes
//! left in @p decodeBuffer when the function returns.
//! @param[out] encoding Receives the detected text encoding, if successful.
//! @retval true A BOM was interpreted and @p encoding updated with the value
//! found. @p decodeBuffer and @p decodedByteCount will be updated with the
//! bytes which were not consumed by the BOM, either 0 or 1.
//! @retval false No BOM was detected at the start of the stream. @p decodeBuffer
//! receives the bytes read and @p decodedByteCount their count.
bool tryInterpretBOM(IStream *input, uint8_ptr_t decodeBuffer,
                     size_t &decodedByteCount, TextEncoding &encoding)
{
    encoding = TextEncoding::ASCII;
    bool hasEncoding = false;

    if (decodedByteCount < 4)
    {
        throw ArgumentException("The buffer needs to be at least 4 bytes long.", "bufferSize");
    }

    // We have to be very careful hear to read only what we need and
    // waste as few bytes as possible.
    decodedByteCount = 0;

    if (tryGetNextByte(input, decodeBuffer[0]))
    {
        ++decodedByteCount;

        switch (decodeBuffer[0])
        {
        case 0x00: // Could be UTF32-BE.
            if (tryGetNextByte(input, decodeBuffer[1]))
            {
                ++decodedByteCount;

                if ((decodeBuffer[1] == 0x00) && tryGetNextByte(input, decodeBuffer[2]))
                {
                    ++decodedByteCount;

                    if ((decodeBuffer[2] == 0xFE) && tryGetNextByte(input, decodeBuffer[3]))
                    {
                        ++decodedByteCount;

                        if (decodeBuffer[3] == 0x0FF)
                        {
                            encoding = TextEncoding::UTF32_BigEndian;
                            hasEncoding = true;
                            decodedByteCount = 0;
                        }
                    }
                }
            }
            break;

        case 0xEF: // Could be UTF-8.
            if (tryGetNextByte(input, decodeBuffer[1]))
            {
                ++decodedByteCount;

                if ((decodeBuffer[1] == 0xBB) && tryGetNextByte(input, decodeBuffer[2]))
                {
                    ++decodedByteCount;

                    if (decodeBuffer[2] == 0xBF)
                    {
                        encoding = TextEncoding::UTF8;
                        hasEncoding = true;
                        decodedByteCount = 0;
                    }
                }
            }
            break;

        case 0xFE: // Could be UTF-16-BE.
            if (tryGetNextByte(input, decodeBuffer[1]))
            {
                ++decodedByteCount;

                if (decodeBuffer[1] == 0xFF)
                {
                    encoding = TextEncoding::UTF16_BigEndian;
                    hasEncoding = true;
                    decodedByteCount = 0;
                }
            }
            break;

        case 0xFF: // Could be UTF16-LE or UTF32-LE.
            if (tryGetNextByte(input, decodeBuffer[1]))
            {
                ++decodedByteCount;

                if (decodeBuffer[1] == 0xFE)
                {
                    // We have a UTF-16-LE BOM. Some extra bytes could make
                    // that a UTF-32-LE BOM.
                    if (tryGetNextByte(input, decodeBuffer[2]))
                    {
                        ++decodedByteCount;

                        if (decodeBuffer[2] == 0x00)
                        {
                            if (tryGetNextByte(input, decodeBuffer[3]))
                            {
                                ++decodedByteCount;

                                if (decodeBuffer[3] == 0x00)
                                {
                                    encoding = TextEncoding::UTF32_LittleEndian;
                                    decodedByteCount = 0;
                                    hasEncoding = true;
                                }
                            }
                        }
                        else
                        {
                            // We recognised UTF-16 Little Endian with one wasted byte.
                            encoding = TextEncoding::UTF16_LittleEndian;
                            hasEncoding = true;

                            // Store the wasted byte for future processing.
                            decodeBuffer[0] = decodeBuffer[2];
                            decodedByteCount = 1;
                        }
                    }
                    else
                    {
                        // We recognise the UTF-16-LE BOM and then ran out of bytes.
                        encoding = TextEncoding::UTF16_LittleEndian;
                        decodedByteCount = 0;
                        hasEncoding = true;
                    }
                }
            }
            break;
        }
    }
    else
    {
        // We failed to read any bytes at all.
        decodedByteCount = 0;
    }

    return hasEncoding;
}

void appendByteSequence(std::string &buffer, uint8_cptr_t bytes, size_t count)
{
    Ag::ensureExtraCapacity(buffer, (count * 6) + 2);

    buffer.push_back('{');
    buffer.push_back(' ');

    FormatInfo formatInfo(Ag::LocaleInfo::getNeutral());

    formatInfo.enableUpperCase(true);
    formatInfo.setRadix(16);

    for (size_t i = 0; i < count; ++i)
    {
        if (i == 0)
        {
            buffer.append("0x");
        }
        else
        {
            buffer.append(", 0x");
        }

        Ag::appendValue(formatInfo, buffer, bytes[i]);
    }

    buffer.push_back(' ');
    buffer.push_back('}');
}

} // Anonymous namespace

IMPLEMENT_UNIQUE_PTR(ICharacterDecoder);

////////////////////////////////////////////////////////////////////////////////
// TextInputOptions Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the encoding to use if a stream does not start with a Byte
//! Order Mark.
TextEncoding TextInputOptions::getPreferredEncoding() const
{
    return _preferredEncoding;
}

//! @brief Sets the encoding to use if a stream does not start with a Byte
//! Order Mark.
//! @param[in] encoding The encoding to assume.
void TextInputOptions::setPreferredEncoding(TextEncoding encoding)
{
    _preferredEncoding = encoding;
}

//! @brief Gets a value determining if a Byte Order Mark is expected at the
//! beginning of the byte stream.
TextInputOptions::BOMMode TextInputOptions::getBOMExpectation() const
{
    return _bomExpectation;
}

//! @brief Sets a value determining if a Byte Order Mark is expected at the
//! beginning of the byte stream.
//! @param[in] mode The expectation of presence of a BOM in the initial bytes of
//! the stream.
void TextInputOptions::setBOMExpectation(TextInputOptions::BOMMode mode)
{
    _bomExpectation = mode;
}

//! @brief Gets the action to perform when an invalid sequence of bytes is encountered.
TextInputOptions::ErrorMode TextInputOptions::getErrorAction() const
{
    return _errorAction;
}

//! @brief Sets the action to perform when an invalid sequence of bytes is encountered.
//! @param[in] action The new invalid byte sequence action.
void TextInputOptions::setErrorAction(TextInputOptions::ErrorMode action)
{
    _errorAction = action;
}

//! @brief Gets the character used when the error action is set to ErrorMode::Substitute.
char32_t TextInputOptions::getErrorSubstituteCharacter() const
{
    return _substitute;
}

//! @brief Sets the character used when the error action is set to ErrorMode::Substitute.
//! @param[in] substitute The character to inject into the input stream when an
//! invalid sequence is encountered.
void TextInputOptions::setErrorSubstituteCharacter(char32_t substitute)
{
    _substitute = substitute;
}

////////////////////////////////////////////////////////////////////////////////
// InvalidEncodingSequenceException Member Definitions
////////////////////////////////////////////////////////////////////////////////
const char *InvalidEncodingSequenceException::Domain = "InvalidEncodingSequenceException";

//! @brief Constructs an exception raised when a sequence of bytes is encountered
//! which does not correspond to a valid Unicode code point.
InvalidEncodingSequenceException::InvalidEncodingSequenceException(const std::string_view &encodingName,
                                                                   uint8_cptr_t bytes, size_t count)
{
    std::string detail;
    detail.assign("In the ");
    detail.append(encodingName);
    detail.append(" character encoding, the following sequence of bytes was invalid: ");
    appendByteSequence(detail, bytes, count);
    detail.push_back('.');

    initialise(Domain, "A sequence of bytes was encountered which could not be "
                       "decoded into a valid Unicode character.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// InvalidBOMException Member Definitions
////////////////////////////////////////////////////////////////////////////////
const char *InvalidBOMException::Domain = "InvalidEncodingSequenceException";

//! @brief Constructs an exception raised when a sequence of bytes is encountered
//! at the beginning of a text stream which does not represent a valid Byte Order Mark.
InvalidBOMException::InvalidBOMException(uint8_cptr_t bytes, size_t count)
{
    std::string detail;
    detail.assign("The byte sequence ");
    appendByteSequence(detail, bytes, count);
    detail.append(" was not recognised as a valid byte order mark.");

    initialise(Domain, "When expecting a byte order mark at the beginning of a "
                       "text stream and invalid sequence of bytes was encountered.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// TextInputStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a text input stream which reads bytes from a specified
//! input stream.
//! @param[in] input The input stream to interpret characters from expecting a
//! UTF-8 encoding or a BOM prefix.
TextInputStream::TextInputStream(IStream *input)
{
    if (input == nullptr)
    {
        throw Ag::ArgumentNullException("input");
    }
    else
    {
        initialise(input);
    }
}

//! @brief Constructs a text input stream which reads bytes from a specified
//! input stream which the new object takes ownership of.
//! @param[in] input The input stream to interpret characters from expecting a
//! UTF-8 encoding or a BOM prefix.
TextInputStream::TextInputStream(IStreamUPtr &&input)
{
    if (input)
    {
        initialise(std::move(input));
    }
    else
    {
        throw Ag::ArgumentNullException("input");
    }
}

//! @brief Constructs a text input stream which reads bytes from a specified
//! input stream.
//! @param[in] input The input stream to interpret characters..
//! @param[in] options An object defining how input bytes should be interpreted.
TextInputStream::TextInputStream(IStream *input, const TextInputOptions &options) :
    _options(options)
{
    if (input == nullptr)
    {
        throw Ag::ArgumentNullException("input");
    }
    else
    {
        initialise(input);
    }
}

//! @brief Constructs a text input stream which reads bytes from a specified
//! input stream which the new object takes ownership of.
//! @param[in] input The input stream to interpret characters from.
//! @param[in] options An object defining how input bytes should be interpreted.
TextInputStream::TextInputStream(IStreamUPtr &&input, const TextInputOptions &options) :
    _options(options)
{
    if (input)
    {
        initialise(std::move(input));
    }
    else
    {
        throw Ag::ArgumentNullException("input");
    }
}

//! @brief Constructs an input stream object by acquiring the contents of another.
//! @param[in] rhs The input stream to acquire.
TextInputStream::TextInputStream(TextInputStream &&rhs) noexcept
{
    moveAssign(std::move(rhs));
}

//! @brief Attempts to read characters from the input stream.
//! @param[in] buffer A pointer to the buffer to write new characters to.
//! @param[in] maxCharacters The maximum number of characters which can be
//! written to @p buffer.
//! @return The actual count of characters written to @b buffer. If @p maxCharacters
//! is non-zero a return value of zero indicates the end of the stream.
size_t TextInputStream::read(utf32_ptr_t buffer, size_t maxCharacters)
{
    if ((_sourceStream == nullptr) || (maxCharacters < 1))
        return 0;

    if (buffer == nullptr)
        throw ArgumentNullException("buffer");

    size_t charsRead = 0;
    char32_t next;
    bool hasError;

    if (!_decoder)
    {
        // This is the first request for characters from an unbuffered stream
        // where a Byte Order Mark is either optional or mandatory.
        //
        // We need to detect any BOM and try to decode any unused bytes.
        _decodedByteCount = DecoderSize;
        TextEncoding encoding;

        if (tryInterpretBOM(_sourceStream, _decodedBytes, _decodedByteCount, encoding))
        {
            // Create a decoder based in what we discovered, but we may have unconsumed bytes.
            _decoder = createDecoder(encoding);
        }
        else if (_options.getBOMExpectation() == TextInputOptions::BOMMode::Mandatory)
        {
            // Raise an error using the decoder bytes.
            throw InvalidBOMException(_decodedBytes, _decodedByteCount);
        }
        else
        {
            // Create the default encoding, but we may have unused bytes.
            _decoder = createDecoder(_options.getPreferredEncoding());
        }

        // If we get this far, we should know the encoding.

        // Process any unconsumed bytes into characters.
        for (size_t i = 0; i < _decodedByteCount; ++i)
        {
            if (_decoder->tryDecode(_decodedBytes[i], next, hasError))
            {
                size_t decodedBytes = _decodedByteCount;
                _decodedByteCount = 0;

                if (hasError)
                {
                    handleInvalidSequence(buffer, charsRead, decodedBytes);
                }
                else
                {
                    if (charsRead == maxCharacters)
                    {
                        // We can't consume the extra bytes as character data
                        // without the input buffer overflowing.
                        throw OperationException("Potential buffer overflow, try to read with a bigger buffer.");
                    }

                    // We have successfully interpreted a character.
                    buffer[charsRead++] = next;
                }

                // Shuffle the buffer down in case we end up with a partial character.
                std::memmove(_decodedBytes, _decodedBytes + i, _decodedByteCount - i);
                _decodedByteCount -= i;
                i = 0;
            }
        }
    }

    size_t bytesRead = 1;
    char32_t nextChar;
    uint8_t nextByte;
    bool decodingError;

    while ((charsRead < maxCharacters) && (bytesRead > 0))
    {
        // Read the next byte from the input source.
        bytesRead = _sourceStream->read(&nextByte, 1);

        if (bytesRead > 0)
        {
            _decodedBytes[_decodedByteCount++] = nextByte;

            if (_decoder->tryDecode(nextByte, nextChar, decodingError))
            {
                // Reset the decode buffer, unless the sequence was invalid.
                size_t encodingSize = _decodedByteCount;
                _decodedByteCount = 0;

                if (decodingError)
                {
                    // Handle the error, possibly reporting the erroneous sequence
                    // of bytes.
                    handleInvalidSequence(buffer, charsRead, encodingSize);
                }
                else
                {
                    buffer[charsRead++] = nextChar;
                }
            }

            if (_decodedByteCount == DecoderSize)
            {
                throw OperationException("Potential buffer overflow detected.");
            }
        }
    }

    return charsRead;
}

//! @brief Overwrites the current input stream by acquiring the contents of another.
//! @param[in] rhs The input stream to acquire.
//! @return A reference to the current object.
TextInputStream &TextInputStream::operator=(TextInputStream &&rhs) noexcept
{
    if (&rhs != this)
    {
        moveAssign(std::move(rhs));
    }

    return *this;
}

//! @brief Performs shared initialisation for the stream for a non-owned input stream.
//! @param[in] input The unowned input stream to wrap.
void TextInputStream::initialise(IStream *input)
{
    if (input->isBuffered())
    {
        _sourceStream = input;
    }
    else
    {
        // To improve performance, we need buffering.
        _ownedStream.reset(new BufferedInputStream(input));
        _sourceStream = _ownedStream.get();
    }

    if (_options.getBOMExpectation() == TextInputOptions::BOMMode::Ignored)
    {
        _decoder = createDecoder(_options.getPreferredEncoding());
    }
    else
    {
        // Attempt to detect a byte order mark.
        _decodedByteCount = DecoderSize;

        BufferedInputStream *bufferedInput;
        TextEncoding encoding = _options.getPreferredEncoding();

        if (tryCast(_sourceStream, bufferedInput))
        {
            // Detect BOM now as we can roll back on unconsumed bytes,
            // otherwise, wait until the first character is requested.
            if (tryInterpretBOM(bufferedInput, _decodedBytes, _decodedByteCount, encoding))
            {
                // Roll back the bytes we didn't consume.
                bufferedInput->ungetBytes(_decodedByteCount);
            }
            else if (_options.getBOMExpectation() == TextInputOptions::BOMMode::Mandatory)
            {
                // Throw error using the decoder bytes.
                throw InvalidBOMException(_decodedBytes, _decodedByteCount);
            }
            else
            {
                // Roll back over all bytes read.
                bufferedInput->ungetBytes(_decodedByteCount);
                encoding = _options.getPreferredEncoding();
            }

            _decoder = createDecoder(encoding);
        }
    }
}

//! @brief Performs shared initialisation for the stream for an owned input stream.
//! @param[in] input The raw input stream to take ownership of.
void TextInputStream::initialise(IStreamUPtr &&input)
{
    if (input->isBuffered())
    {
        _ownedStream = std::move(input);
    }
    else
    {
        // To improve performance, we need buffering.
        _ownedStream.reset(new BufferedInputStream(std::move(input)));
    }

    initialise(_ownedStream.get());
}

//! @brief Performs the appropriate action when an invalid sequence of bytes was
//! encountered in the source stream.
//! @param[in] buffer The buffer to receive decoded characters. There should
//! be space left in the buffer for at least one more character.
//! @param[in,out] charactersRead The count of characters currently in the buffer,
//! updated if a character is added to the buffer.
//! @param[in] decodedByteCount The count of
void TextInputStream::handleInvalidSequence(utf32_ptr_t buffer,
                                            size_t &charactersRead,
                                            size_t decodedByteCount) const
{
    switch (_options.getErrorAction())
    {
    case TextInputOptions::ErrorMode::Substitute:
        buffer[charactersRead++] = _options.getErrorSubstituteCharacter();
        break;

    case TextInputOptions::ErrorMode::Throw:
        throw InvalidEncodingSequenceException(_decoder->getName(),
                                               _decodedBytes, decodedByteCount);
        break;

    case TextInputOptions::ErrorMode::Ignore:
    default:
        break;
    }
}

//! @brief Acquires the contents of the object by overwriting with members from
//! another stream.
//! @param[in] rhs The stream to acquire and overwrite with.
void TextInputStream::moveAssign(TextInputStream &&rhs) noexcept
{
    _ownedStream = std::move(rhs._ownedStream);
    _sourceStream = std::exchange(rhs._sourceStream, nullptr);
    _decoder = std::move(rhs._decoder);
    _options = std::move(rhs._options);
    _decodedByteCount = std::exchange(rhs._decodedByteCount, 0);
    std::memcpy(_decodedBytes, rhs._decodedBytes, _decodedByteCount);
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

