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
#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/TextInputStream.hpp"

namespace Ag {
namespace IO {

namespace {


////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
constexpr char32_t LF = U'\n'; // 0x0A
constexpr char32_t CR = U'\r'; // 0x0D

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

//! @brief Compares a sequence of bytes against a fixed sequence.
//! @tparam N The count of bytes in the fixed sequence.
//! @param[in] lhs The sequence to compare against.
//! @param[in] lhsSize The count of bytes in the @p lhs sequence.
//! @param[in] rhs The fixed-sized sequence to compare against.
//! @retval true The first N bytes of @p lhs match the corresponding
//! bytes of @p rhs.
template<std::size_t N>
bool isMatchingSequence(uint8_cptr_t lhs, size_t lhsSize, const uint8_t (&rhs)[N])
{
    constexpr size_t rhsSize = N;

    if (lhsSize < rhsSize)
    {
        return false;
    }

    return std::equal(lhs, lhs + rhsSize, rhs);
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
    if (decodedByteCount < 4)
    {
        throw ArgumentException("The buffer needs to be at least 4 bytes long.", "bufferSize");
    }

    static const uint8_t Utf8Bom[] = { 0xEF, 0xBB, 0xBF };
    static const uint8_t Utf16LeBom[] = { 0xFF, 0xFE };
    static const uint8_t Utf16BeBom[] = { 0xFE, 0xFF };
    static const uint8_t Utf32LeBom[] = { 0xFF, 0xFE, 0x00, 0x00 };
    static const uint8_t Utf32BeBom[] = { 0x00, 0x00, 0xFE, 0xFF };

    size_t bytesRead = input->read(decodeBuffer, 4);
    size_t bomSize = 0;
    encoding = TextEncoding::ASCII;
    bool hasEncoding = true;

    if (isMatchingSequence(decodeBuffer, bytesRead, Utf32LeBom))
    {
        // UTF-32 Little Endian.
        encoding = TextEncoding::UTF32_LittleEndian;
        bomSize = std::size(Utf32LeBom);
    }
    else if (isMatchingSequence(decodeBuffer, bytesRead, Utf32BeBom))
    {
        // UTF-32 Big Endian.
        encoding = TextEncoding::UTF32_BigEndian;
        bomSize = std::size(Utf32BeBom);
    }
    else if (isMatchingSequence(decodeBuffer, bytesRead, Utf16LeBom))
    {
        // UTF-16 Little Endian.
        encoding = TextEncoding::UTF16_LittleEndian;
        bomSize = std::size(Utf16LeBom);
    }
    else if (isMatchingSequence(decodeBuffer, bytesRead, Utf16BeBom))
    {
        // UTF-16 Big Endian.
        encoding = TextEncoding::UTF16_BigEndian;
        bomSize = std::size(Utf16BeBom);
    }
    else if (isMatchingSequence(decodeBuffer, bytesRead, Utf8Bom))
    {
        // UTF-8.
        encoding = TextEncoding::UTF8;
        bomSize = std::size(Utf8Bom);
    }
    else
    {
        hasEncoding = false;
    }

    // Deal with any left over bytes which are to be decoded as characters.
    if (hasEncoding)
    {
        decodedByteCount = bytesRead - bomSize;

        if (bomSize < bytesRead)
        {
            // Shuffle bytes in the decoding buffer down.
            std::memmove(decodeBuffer, decodeBuffer + bomSize, decodedByteCount);
        }
    }
    else
    {
        decodedByteCount = bytesRead;
    }

    return hasEncoding;
}

//! @brief Appends text representing a sequence of bytes to a UTF-8 string.
//! @param[in] buffer The string to append to.
//! @param[in] bytes The array of bytes to format.
//! @param[in] count The count of bytes in @p bytes to format.
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


//! @brief Creates a TextInputStream from a copy of a std::basic_string_view<> derived string.
//! @tparam T The data type of the string view to copy.
//! @tparam TEnc The encoding of the string data.
//! @param[in] stringView The string data to copy.
//! @return An object to read the string data.
template<IO::TextEncoding TEnc, typename T>
TextInputStream createTextStreamFromStringView(const T &stringView)
{
    IStreamUPtr memStream(new MemoryStream(stringView.data(), stringView.length() * sizeof(T::value_type), true));
    TextInputOptions options;
    options.setPreferredEncoding(TEnc);
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);

    return TextInputStream(std::move(memStream), options);
}

//! @brief Creates a TextInputStream from a copy of a std::basic_string_view<> derived string.
//! @tparam T The data type of the string view to copy.
//! @tparam TEnc The encoding of the string data.
//! @param[in] stringView The string data to copy.
//! @param[in] options The base set of options used to configure the stream.
//! @return An object to read the string data.
template<IO::TextEncoding TEnc, typename T>
TextInputStream createTextStreamFromStringView(const T &stringView,
                                               const TextInputOptions &options)
{
    IStreamUPtr memStream(new MemoryStream(stringView.data(), stringView.length() * sizeof(T::value_type), true));

    TextInputOptions effectiveOptions(options);
    effectiveOptions.setPreferredEncoding(TEnc);
    effectiveOptions.setBOMExpectation(TextInputOptions::BOMMode::Ignored);

    return TextInputStream(std::move(memStream), effectiveOptions);
}

//! @brief Creates a unique pointer to a TextInputStream from a copy of a
//! std::basic_string_view<> derived string.
//! @tparam T The data type of the string view to copy.
//! @tparam TEnc The encoding of the string data.
//! @param[in] stringView The string data to copy.
//! @return An object to read the string data.
template<IO::TextEncoding TEnc, typename T>
TextInputStreamUPtr createTextStreamUPtrFromStringView(const T &stringView)
{
    IStreamUPtr memStream(new MemoryStream(stringView.data(), stringView.length() * sizeof(T::value_type), true));
    TextInputOptions options;
    options.setPreferredEncoding(TEnc);
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);

    return std::make_unique<TextInputStream>(std::move(memStream), options);
}

//! @brief Creates a unique pointer to a TextInputStream from a copy of a
//! std::basic_string_view<> derived string.
//! @tparam T The data type of the string view to copy.
//! @tparam TEnc The encoding of the string data.
//! @param[in] stringView The string data to copy.
//! @param[in] options The base set of options used to configure the stream.
//! @return An object to read the string data.
template<IO::TextEncoding TEnc, typename T>
TextInputStreamUPtr createTextStreamUPtrFromStringView(const T &stringView,
                                                       const TextInputOptions &options)
{
    IStreamUPtr memStream(new MemoryStream(stringView.data(), stringView.length() * sizeof(T::value_type), true));

    TextInputOptions effectiveOptions(options);
    effectiveOptions.setPreferredEncoding(TEnc);
    effectiveOptions.setBOMExpectation(TextInputOptions::BOMMode::Ignored);

    return std::make_unique<TextInputStream>(std::move(memStream), effectiveOptions);
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

//! @brief Gets whether encodings of a new line should be rendered down to a
//! simple '\n' character.
//! @retval true '\n', '\r\n' and '\r' characters will all be reported as a
//! single '\n' character.
//! @retval false Decoded characters will not be returned without additional
//! processing.
bool TextInputOptions::hasNewLineProcessing() const
{
    return _processNewLine;
}

//! @brief Sets whether decoded characters should be processed to simplify
//! newline encodings.
//! @param[in] isEnabled True to enable new line character processing, false
//! to disable processing of decoded characters.
void TextInputOptions::enableNewLineProcessing(bool isEnabled)
{
    _processNewLine = isEnabled;
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

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromString(string_cref_t &text)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(text.toUtf8View());
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromStringView(const std::string_view &utf8Text)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(utf8Text);
}

//! @brief Creates a text input stream from a copy of a wide string.
//! @param[in] wideText A view of a wide text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p wideText.
TextInputStream TextInputStream::createFromStringView(const std::wstring_view &wideText)
{
    return createTextStreamFromStringView<Wide_Native>(wideText);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromStringView(const std::u8string_view &utf8Text)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(utf8Text);
}

//! @brief Creates a text input stream from a copy of a UTF-16 encoded string.
//! @param[in] utf16Text A view of a UTF-16 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStream TextInputStream::createFromStringView(const std::u16string_view &utf16Text)
{
    return createTextStreamFromStringView<UTF16_Native>(utf16Text);
}

//! @brief Creates a text input stream from a copy of a UTF-32 encoded string.
//! @param[in] utf32Text A view of a UTF-32 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStream TextInputStream::createFromStringView(const std::u32string_view &utf32Text)
{
    return createTextStreamFromStringView<UTF32_Native>(utf32Text);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromString(string_cref_t &text,
                                                  const TextInputOptions &options)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(text.toUtf8View(),
                                                              options);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromStringView(const std::string_view &utf8Text,
                                                      const TextInputOptions &options)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(utf8Text, options);
}

//! @brief Creates a text input stream from a copy of a wide string.
//! @param[in] wideText A view of a wide text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p wideText.
TextInputStream TextInputStream::createFromStringView(const std::wstring_view &wideText,
                                                      const TextInputOptions &options)
{
    return createTextStreamFromStringView<Wide_Native>(wideText, options);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStream TextInputStream::createFromStringView(const std::u8string_view &utf8Text,
                                                      const TextInputOptions &options)
{
    return createTextStreamFromStringView<TextEncoding::UTF8>(utf8Text, options);
}

//! @brief Creates a text input stream from a copy of a UTF-16 encoded string.
//! @param[in] utf16Text A view of a UTF-16 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStream TextInputStream::createFromStringView(const std::u16string_view &utf16Text,
                                                      const TextInputOptions &options)
{
    return createTextStreamFromStringView<UTF16_Native>(utf16Text, options);
}

//! @brief Creates a text input stream from a copy of a UTF-32 encoded string.
//! @param[in] utf32Text A view of a UTF-32 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStream TextInputStream::createFromStringView(const std::u32string_view &utf32Text,
                                                      const TextInputOptions &options)
{
    return createTextStreamFromStringView<UTF32_Native>(utf32Text, options);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromString(string_cref_t &text)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(text.toUtf8View());
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::string_view &utf8Text)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(utf8Text);
}

//! @brief Creates a text input stream from a copy of a wide string.
//! @param[in] wideText A view of a wide text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p wideText.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::wstring_view &wideText)
{
    return createTextStreamUPtrFromStringView<Wide_Native>(wideText);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u8string_view &utf8Text)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(utf8Text);
}

//! @brief Creates a text input stream from a copy of a UTF-16 encoded string.
//! @param[in] utf16Text A view of a UTF-16 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u16string_view &utf16Text)
{
    return createTextStreamUPtrFromStringView<UTF16_Native>(utf16Text);
}

//! @brief Creates a text input stream from a copy of a UTF-32 encoded string.
//! @param[in] utf32Text A view of a UTF-32 text string to be copied to create the stream.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u32string_view &utf32Text)
{
    return createTextStreamUPtrFromStringView<UTF32_Native>(utf32Text);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromString(string_cref_t &text,
                                                          const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(text.toUtf8View(), options);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::string_view &utf8Text,
                                                              const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(utf8Text, options);
}

//! @brief Creates a text input stream from a copy of a wide string.
//! @param[in] wideText A view of a wide text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p wideText.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::wstring_view &wideText,
                                                              const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<Wide_Native>(wideText, options);
}

//! @brief Creates a text input stream from a copy of a UTF-8 encoded string.
//! @param[in] utf8Text A view of a UTF-8 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf8Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u8string_view &utf8Text,
                                                              const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<TextEncoding::UTF8>(utf8Text, options);
}

//! @brief Creates a text input stream from a copy of a UTF-16 encoded string.
//! @param[in] utf16Text A view of a UTF-16 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u16string_view &utf16Text,
                                                              const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<UTF16_Native>(utf16Text, options);
}

//! @brief Creates a text input stream from a copy of a UTF-32 encoded string.
//! @param[in] utf32Text A view of a UTF-32 text string to be copied to create the stream.
//! @param[in] options The base set of options used to configure the stream. The
//! BOM expectation and encoding properties will be ignored.
//! @return A new instance of a text input stream which will read a copy of @p utf16Text.
TextInputStreamUPtr TextInputStream::createUPtrFromStringView(const std::u32string_view &utf32Text,
                                                              const TextInputOptions &options)
{
    return createTextStreamUPtrFromStringView<UTF32_Native>(utf32Text, options);
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

    CodePointSpan output(buffer, maxCharacters);

    bool mightHaveMore = true;

    if (_options.hasNewLineProcessing())
    {
        // We need to go through cycles to ensure the buffer is filled as
        // far as it can be, as combining character sequences in-place
        // can leave gaps which could be filled with more characters.
        size_t charsProcessed = 0;

        while (mightHaveMore && (charsProcessed < maxCharacters))
        {
            mightHaveMore = false;

            // Create a section of the buffer to read unprocessed characters into.
            CodePointSpan unprocessed = output.subspan(charsProcessed, output.size() - charsProcessed);

            // Read what we can from cache first.
            size_t charsRead = readFromCache(unprocessed);

            if ((charsRead > 0) &&
                ((_cachedCharsRead * 2) >= _characterCache.size()))
            {
                compressCache();
            }

            if (charsRead < unprocessed.size())
            {
                // Generate additional characters straight into the output buffer.
                CodePointSpan toGenerate = unprocessed.subspan(charsRead, unprocessed.size() - charsRead);

                size_t newCharsRead = generateCharacters(toGenerate);

                mightHaveMore = (newCharsRead == toGenerate.size());
                charsRead += newCharsRead;
            }

            // Post-process the output buffer to combine newline character
            // encodings down to individual '\n' characters.
            charsProcessed += postProcessNewlines(unprocessed.subspan(0, charsRead));
        }

        if ((charsProcessed < maxCharacters) && (mightHaveMore == false))
        {
            // We've reached the end of the input stream, flush out
            // any left over new line characters.
            charsProcessed += _nlProcessor.flushUnprocessed(
                output.subspan(charsProcessed, output.size() - charsProcessed));
        }

        return charsProcessed;
    }
    else
    {
        // What we read it what we return.
        size_t charsRead = readFromCache(output);

        if ((charsRead > 0) &&
            ((_cachedCharsRead * 2) >= _characterCache.size()))
        {
            compressCache();
        }

        if (charsRead < maxCharacters)
        {
            // Generate additional characters straight into the output buffer.
            CodePointSpan bufferLeft = output.subspan(charsRead, output.size() - charsRead);

            charsRead += generateCharacters(bufferLeft);
        }

        return charsRead;
    }
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

//! @brief Processes characters to combine sequences into single 'LF' characters.
//! @param[in] next The next code point to process.
//! @param[out] output1 Receives the first processed character if the return
//! value is greater than 0.
//! @param[out] output2 Receives the second processed character if the return
//! value is greater than 1.
//! @return The count of processed characters to return.
int TextInputStream::NewlineProcessor::tryProcessCharacter(char32_t next,
                                                           char32_t &output1,
                                                           char32_t &output2)
{
    int resultCount = 0;

    switch (_state)
    {
    case NLState::Start:
        if (next == LF)
        {
            _state = NLState::AfterLF;
            resultCount = 0;
        }
        else if (next == CR)
        {
            _state = NLState::AfterCR;
            resultCount = 0;
        }
        else
        {
            output1 = next;
            resultCount = 1;
        }
        break;

    case NLState::AfterCR:
        if (next == LF)
        {
            // CR + LF => LF
            _state = NLState::Start;
            output1 = LF;
            resultCount = 1;
        }
        else if (next == CR)
        {
            // CR + CR => CR [CR]

            // Output one line break, the other could proceed an LF,
            // so we need to retain it until we are sure.
            output1 = LF;
            resultCount = 1;
        }
        else
        {
            // We've processed CR + ? => CR + ?.
            _state = NLState::Start;
            output1 = CR;
            output2 = next;
            resultCount = 2;
        }
        break;

    case NLState::AfterLF:
        if (next == LF)
        {
            // LF + LF => LF [LF]

            // Output one line break, the other could proceed an LF,
            // so we need to retain it until we are sure.
            output1 = LF;
            resultCount = 1;
        }
        else if (next == CR)
        {
            // We've processed LF + CR => LF.
            _state = NLState::Start;
            output1 = LF;
            resultCount = 1;
        }
        else
        {
            // We've processed LF + ? => LF + ?.
            _state = NLState::Start;
            output1 = LF;
            output2 = next;
            resultCount = 2;
        }
        break;

    default:
        output1 = next;
        resultCount = 1;
        break;
    }

    return resultCount;
}

//! @brief Flushes any left over unprocessed characters from the processor.
//! @param[in] buffer The buffer to receive any unprocessed characters.
//! @returns The count of characters added to @p buffer.
size_t TextInputStream::NewlineProcessor::flushUnprocessed(CodePointSpan buffer)
{
    if (buffer.empty())
        return 0;

    // Reset the state before acting.
    NLState finalState = _state;
    _state = NLState::Start;

    char32_t leftOver = U'\0';

    switch (finalState)
    {
    case NLState::AfterCR:
        leftOver = CR;
        break;

    case NLState::AfterLF:
        leftOver = LF;
        break;

    default:
        return 0;
    }

    buffer.front() = leftOver;

    return 1;
}

//! @brief Performs shared initialisation for the stream for a non-owned input stream.
//! @param[in] input The unowned input stream to wrap.
void TextInputStream::initialise(IStream *input)
{
    // Set the capacity of the character cache.
    _characterCache.reserve(16);

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
        // Attempt to detect a byte order mark from the initial bytes of the
        // stream.
        _decodedByteCount = DecoderSize;

        TextEncoding encoding = _options.getPreferredEncoding();

        // Detect BOM from the initial bytes and cache any characters produced
        // from processing initial bytes.
        if (tryInterpretBOM(_sourceStream, _decodedBytes, _decodedByteCount, encoding))
        {
            // The BOM was detected, but bytes read from the stream might be left over.
            _decoder = createDecoder(encoding);
        }
        else if (_options.getBOMExpectation() == TextInputOptions::BOMMode::Mandatory)
        {
            // Throw error using the decoder bytes.
            throw InvalidBOMException(_decodedBytes, _decodedByteCount);
        }
        else
        {
            // No BOM was detected, but some bytes read from the stream might
            // be left over.
            _decoder = createDecoder(_options.getPreferredEncoding());
        }

        // Process any unconsumed bytes into characters which can be buffered.
        char32_t next;
        bool hasError;

        for (size_t i = 0; i < _decodedByteCount; ++i)
        {
            if (_decoder->tryDecode(_decodedBytes[i], next, hasError))
            {
                size_t decodedBytes = _decodedByteCount;
                size_t bytesProcessed = i + 1;
                _decodedByteCount -= bytesProcessed;
                i = 0;

                // Shuffle the buffer down in case we end up with a partial character.
                if (bytesProcessed < _decodedByteCount)
                {
                    std::memmove(_decodedBytes, _decodedBytes + bytesProcessed,
                                 decodedBytes - bytesProcessed);
                }

                if (hasError)
                {
                    size_t bufSize = 1;

                    handleInvalidSequence(&next, bufSize, decodedBytes);

                    if (bufSize == 1)
                    {
                        // Buffer the substitute character.
                        _characterCache.push_back(next);
                    }
                }
                else
                {
                    // We have successfully interpreted a character.
                    _characterCache.push_back(next);
                }
            }
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
    _characterCache = std::move(rhs._characterCache);
    _cachedCharsRead = std::exchange(rhs._cachedCharsRead, 0);
    _options = std::move(rhs._options);
    _decodedByteCount = std::exchange(rhs._decodedByteCount, 0);
    std::memcpy(_decodedBytes, rhs._decodedBytes, _decodedByteCount);
}

//! @brief Remove any characters from the cache which have been already read.
void TextInputStream::compressCache()
{
    if (_cachedCharsRead == 0)
        return;

    if (_cachedCharsRead < _characterCache.size())
    {
        // Remove the characters previously read and shuffle down the
        // unread characters.
        _characterCache.erase(_characterCache.begin(), _characterCache.begin() + _cachedCharsRead);
        _cachedCharsRead = 0;
    }
    else
    {
        // All characters in the cache had been read, clear the cache.
        _cachedCharsRead = 0;
        _characterCache.clear();
    }
}

//! @brief Reads as many characters from cache as possible.
//! @param[in] buffer The buffer to copy cached characters from.
//! @param[in,out] bufferSize The maximum number of characters to copy to
//! @p buffer, receives the actual number copied.
//! @retval true More cached characters are available, but cannot be copied
//! until newline processing decodes further characters.
//! @retval false The cache is empty.
size_t TextInputStream::readFromCache(CodePointSpan buffer)
{
    if (buffer.empty())
        return 0;

    size_t charsRead = 0;

    if (_cachedCharsRead < _characterCache.size())
    {
        // Calculate how many characters can be copied.
        size_t safeCount = std::min(_characterCache.size() - _cachedCharsRead,
                                    buffer.size());

        // Copy the characters.
        std::copy_n(_characterCache.data() + _cachedCharsRead,
                    safeCount, buffer.data());

        // Update the counts.
        _cachedCharsRead += safeCount;
        charsRead += safeCount;

        if (_cachedCharsRead == _characterCache.size())
        {
            // Clear the cache if it has been fully read.
            _characterCache.clear();
            _cachedCharsRead = 0;
        }
    }

    return charsRead;
}

//! @brief Decodes characters directly from the buffered input stream to an
//! output buffer.
//! @param[in] buffer The buffer to receive the decoded characters.
//! @param[in] maxCharacters The maximum count of characters to copy to @p buffer.
//! @return The actual count of characters copied to @p buffer.
size_t TextInputStream::generateCharacters(CodePointSpan buffer)
{
    size_t bytesRead = 1;
    size_t charsRead = 0;
    char32_t nextChar;
    uint8_t nextByte;
    bool decodingError;

    while ((charsRead < buffer.size()) && (bytesRead > 0))
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
                    handleInvalidSequence(buffer.data(), charsRead, encodingSize);
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

//! @brief Processes the contents of a buffer in-place, to convert sequences of
//! white space characters into single LF ('\n') characters.
//! @param[in] buffer The buffer of characters to process.
//! @param[in] maxCharacters The count of characters in @p buffer.
//! @return The count of processed characters remaining in buffer.
size_t TextInputStream::postProcessNewlines(CodePointSpan buffer)
{
    // Post-process the output buffer to combine newline character
    // encodings down to individual '\n' characters.
    char32_t first, second;

    size_t dest = 0;

    for (size_t source = 0; source < buffer.size(); ++source)
    {
        int result = _nlProcessor.tryProcessCharacter(buffer[source], first, second);

        if (result > 0)
        {
            buffer[dest++] = first;
        }

        // NOTE: NewlineProcessor will never return two characters without
        // previously withholding at least one character.
        if (result > 1)
        {
            buffer[dest++] = second;
        }
    }

    return dest;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

