//! @file IO/TextOutputStream.cpp
//! @brief The definition of an object which can encode characters as bytes
//! sent to a binary output stream.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <bit>

#include "Ag/IO/BufferedOutputStream.hpp"
#include "Ag/IO/Exceptions.hpp"
#include "Ag/IO/TextOutputStream.hpp"

namespace Ag {
namespace IO {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of ICharacterEncoder which only outputs ASCII
//! characters.
class ASCIICharacterEncoder : public ICharacterEncoder
{
private:
    // Internal Fields
    uint8_t _buffer = 0;
public:
    // Construction/Destruction
    ASCIICharacterEncoder() = default;

    // Accessors

    // Inherited from ICharacterEncoder
    virtual std::string_view getName() const override { return "ASCII"; }

    // Operations

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeBOM() override
    {
        // No Byte Order Mark for ASCII.
        return {};
    }

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeCodePoint(char32_t next, bool &error) override
    {
        error = false;

        if (next > 127)
        {
            return {};
        }

        _buffer = static_cast<uint8_t>(next);

        return ByteConstView(&_buffer, 1);
    }
};

//! @brief An implementation of ICharacterEncoder which outputs code points
//! encoded as UTF-8 byte sequences.
class UTF8CharacterEncoder : public ICharacterEncoder
{
private:
    // Internal Fields
    uint8_t _buffer[Utf::ToUtf8Converter::MaxEncodingSize];
public:
    // Construction/Destruction
    UTF8CharacterEncoder() = default;

    // Accessors

    // Inherited from ICharacterEncoder
    virtual std::string_view getName() const override { return "UTF-8"; }

    // Operations

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeBOM() override
    {
        // Encode the 3-byte BOM for UTF-8.
        _buffer[0] = 0xEF;
        _buffer[1] = 0xBB;
        _buffer[2] = 0xBF;

        return ByteConstView(_buffer, 3);
    }

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeCodePoint(char32_t next, bool &error) override
    {
        Utf::ToUtf8Converter converter;

        // Calculate if encoding is possible, and if so, how big it will be.
        uint32_t encodingLength = converter.setCodePoint(next);
        error = false;

        if (encodingLength > std::size(_buffer))
        {
            // Indicate the code point cannot be encoded.
            return {};
        }
        else if (encodingLength == 0)
        {
            // Indicate the code point is invalid.
            error = true;
            return {};
        }

        // Extract the bytes of the encoded code point.
        size_t i = 0;
        while (converter.tryGetNextByte(_buffer[i]))
        {
            ++i;
        }

        // Return the span of bytes representing the encoding.
        return ByteConstView(_buffer, i);
    }
};

//! @brief An implementation of ICharacterEncoder which outputs code points
//! encoded as UTF-16 word sequences.
//! @tparam SwapBytes Indicates whether the output encoding has the opposite
//! byte order to the host encoding.
template<bool SwapBytes>
class UTF16CharacterEncoder : public ICharacterEncoder
{
private:
    // Internal Types
    using BufferView = ConstView<uint16_t>;

    // Internal Fields
    uint16_t _buffer[Utf::ToUtf16Converter::MaxEncodingSize];
public:
    // Construction/Destruction
    UTF16CharacterEncoder()
    {
        std::fill_n(_buffer, std::size(_buffer), u'\0');
    }

    // Accessors

    // Inherited from ICharacterEncoder
    virtual std::string_view getName() const override
    {
        if constexpr (Ag::Bin::ResolvedByteOrder<SwapBytes>::value == Bin::Endedness::LittleEndian)
        {
            return "UTF16-LE";
        }
        else
        {
            return "UTF16-BE";
        }
    }

    // Operations

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeBOM() override
    {
        // Encode the 2-byte BOM for UTF-16 and swap it accordingly.
        constexpr uint16_t BOM = 0xFEFF;

        if constexpr (SwapBytes)
        {
            _buffer[0] = std::byteswap(BOM);
        }
        else
        {
            _buffer[0] = BOM;
        }

        return BufferView(_buffer, 1).toBytes();
    }

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeCodePoint(char32_t next, bool &error) override
    {
        Utf::ToUtf16Converter converter;

        // Calculate if encoding is possible, and if so, how big it will be.
        uint32_t encodingLength = converter.setCodePoint(next);

        if (encodingLength > std::size(_buffer))
        {
            // Indicate the code point cannot be encoded.
            error = false;
            return {};
        }
        else if (encodingLength == 0)
        {
            // Indicate the code point is invalid.
            error = true;
            return {};
        }

        // Extract the bytes of the encoded code point.
        size_t i = 0;
        char16_t word;
        error = false;

        while (converter.tryGetNextCharacter(word))
        {
            if constexpr (SwapBytes)
            {
                _buffer[i] = std::byteswap(static_cast<uint16_t>(word));
            }
            else
            {
                _buffer[i] = static_cast<uint16_t>(word);
            }

            ++i;
        }

        // Return the span of bytes representing the encoding.
        return BufferView(_buffer, i).toBytes();
    }
};

//! @brief An implementation of ICharacterEncoder which outputs code points
//! encoded as UTF-32 words.
//! @tparam SwapBytes Indicates whether the output encoding has the opposite
//! byte order to the host encoding.
template<bool SwapBytes>
class UTF32CharacterEncoder : public ICharacterEncoder
{
private:
    // Internal Fields
    using BufferConstView = ConstView<uint32_t>;

    // Internal Fields
    uint32_t _buffer = 0;
public:
    // Construction/Destruction
    UTF32CharacterEncoder() = default;

    // Accessors

    // Inherited from ICharacterEncoder
    virtual std::string_view getName() const override
    {
        if constexpr (Ag::Bin::ResolvedByteOrder<SwapBytes>::value == Bin::Endedness::LittleEndian)
        {
            return "UTF32-LE";
        }
        else
        {
            return "UTF32-BE";
        }
    }

    // Operations

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeBOM() override
    {
        // Encode the 4-byte BOM for UTF-32 and swap it accordingly.
        constexpr uint32_t BOM = 0xFEFF;

        if constexpr (SwapBytes)
        {
            _buffer = std::byteswap(BOM);
        }
        else
        {
            _buffer = BOM;
        }

        return BufferConstView(&_buffer, 1).toBytes();
    }

    // Inherited from ICharacterEncoder
    virtual ByteConstView encodeCodePoint(char32_t next, bool &error) override
    {
        if (Ag::CodePoint::isValid(next) == false)
        {
            error = true;

            return {};
        }

        error = false;

        if constexpr (SwapBytes)
        {
            _buffer = std::byteswap(static_cast<uint32_t>(next));
        }
        else
        {
            _buffer = static_cast<uint32_t>(next);
        }

        // Return the span of bytes representing the encoding.
        return BufferConstView(&_buffer, 1).toBytes();
    }
};

//! @brief Creates an implementation of ICharacterEncoder which support a
//! specified character encoding.
//! @param[in] encoding The encoding to create an encoder for.
//! @return A unique pointer to an instance of the character encoder.
ICharacterEncoderUPtr createEncoder(TextEncoding encoding)
{
    ICharacterEncoder *encoder = nullptr;

    switch (encoding)
    {
    case Ag::IO::TextEncoding::ASCII:
        encoder = new ASCIICharacterEncoder();
        break;

    case Ag::IO::TextEncoding::UTF8:
        encoder = new UTF8CharacterEncoder();
        break;

    case Ag::IO::TextEncoding::UTF16_LittleEndian:
        encoder = new UTF16CharacterEncoder<Bin::NeedsSwap<Bin::Endedness::LittleEndian>::value>();
        break;

    case Ag::IO::TextEncoding::UTF16_BigEndian:
        encoder = new UTF16CharacterEncoder<Bin::NeedsSwap<Bin::Endedness::BigEndian>::value>();
        break;

    case Ag::IO::TextEncoding::UTF32_LittleEndian:
        encoder = new UTF32CharacterEncoder<Bin::NeedsSwap<Bin::Endedness::LittleEndian>::value>();
        break;
    case Ag::IO::TextEncoding::UTF32_BigEndian:
        encoder = new UTF32CharacterEncoder<Bin::NeedsSwap<Bin::Endedness::BigEndian>::value>();
        break;

    default:
        throw NotSupportedException("The specified output character encoding.");
    }

    return ICharacterEncoderUPtr(encoder);
}

//! @brief Gets the sequence of Unicode code points which corresponds to a
//! specified new line encoding.
//! @param[in] encoding The encoding to express.
//! @return The sequence of code points expressing the encoding.
CodePointConstView getNewLineEncoding(TextOutputOptions::NewlineEncoding encoding)
{
    static char32_t lfEncoding[] = { U'\n' };
    static char32_t crlfEncoding[] = { U'\r', U'\n' };
    static char32_t crEncoding[] = { U'\r' };
    static char32_t lfcrEncoding[] = { U'\n', U'\r' };

    switch (encoding)
    {
    case TextOutputOptions::NewlineEncoding::LF:
        return CodePointConstView(lfEncoding);

    case TextOutputOptions::NewlineEncoding::CR_LF:
        return CodePointConstView(crlfEncoding);

    case TextOutputOptions::NewlineEncoding::CR:
        return CodePointConstView(crEncoding);

    case TextOutputOptions::NewlineEncoding::LF_CR:
        return CodePointConstView(lfcrEncoding);

    default:
        throw NotSupportedException("The specified newline encoding");
    }
}

} // Anonymous namespace

IMPLEMENT_UNIQUE_PTR(ICharacterEncoder);

////////////////////////////////////////////////////////////////////////////////
// TextOutputOptions Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the encoding used to express characters as streams of bytes.
TextEncoding TextOutputOptions::getOutputEncoding() const
{
    return _outputEncoding;
}

//! @brief Sets the encoding used to express characters as streams of bytes.
//! @param[in] textEncoding The new encoding.
void TextOutputOptions::setOutputEncoding(TextEncoding textEncoding)
{
    _outputEncoding = textEncoding;
}

//! @brief Gets the encoding used to express new lines if newline processing
//! is enabled.
//! @return The newline encoding applied.
TextOutputOptions::NewlineEncoding TextOutputOptions::getNewlineEncoding() const
{
    return _newline;
}

//! @brief Sets the encoding used to express new lines if newline processing
//! is enabled.
//! @param[in] nlEncoding The new encoding of new lines.
void TextOutputOptions::setNewlineEncoding(TextOutputOptions::NewlineEncoding nlEncoding)
{
    _newline = nlEncoding;
}

//! @brief Gets whether processing is applied to the newline character ('\n').
//! @retval true Output of the LF character ('\n') will be converted into a
//! sequence of bytes according to the current new line encoding.
//! @retval false There will be no additional processing of characters before
//! encoding as byte sequences.
bool TextOutputOptions::isNewlineProcessingEnabled() const
{
    return _processNewlines;
}

//! @brief Sets whether processing is applied to the newline character ('\n').
//! @param[in] isEnabled True to enable newline processing, false to disable it.
void TextOutputOptions::enableNewlineProcessing(bool isEnabled)
{
    _processNewlines = isEnabled;
}

//! @brief Gets whether a sequence of bytes is written at the beginning of a
//! stream to express its encoding as a Byte Order Mark.
//! @retval true A Byte Order Mark will be written before the first character
//! of the output stream is encoded.
//! @retval false There will be no preamble before the first encoded character.
bool TextOutputOptions::writeBOM() const
{
    return _writeBOM;
}

//! @brief Sets whether a sequence of bytes is written at the beginning of a
//! stream to express its encoding as a Byte Order Mark.
//! @param[in] isEnabled True to ensure a BOM is written, false to suppress it.
void TextOutputOptions::enableWriteBOM(bool isEnabled)
{
    _writeBOM = isEnabled;
}

//! @brief Gets the action to perform when an invalid sequence of bytes is encountered.
TextOutputOptions::ErrorMode TextOutputOptions::getErrorAction() const
{
    return _errorAction;
}

//! @brief Sets the action to perform when an invalid sequence of bytes is encountered.
//! @param[in] action The new invalid byte sequence action.
void TextOutputOptions::setErrorAction(TextOutputOptions::ErrorMode action)
{
    _errorAction = action;
}

//! @brief Gets the action to perform when an a code point cannot be represented
//! given the output encoding selected.
TextOutputOptions::ErrorMode TextOutputOptions::getEncodingFailureAction() const
{
    return _encodingFailureAction;
}

//! @brief Sets the action to perform when an a code point cannot be represented
//! given the output encoding selected.
//! @param[in] action The new encoding failure action.
void TextOutputOptions::setEncodingFailureAction(TextOutputOptions::ErrorMode action)
{
    _encodingFailureAction = action;
}

//! @brief Gets the character used when the error action is set to ErrorMode::Substitute.
char32_t TextOutputOptions::getErrorSubstituteCharacter() const
{
    return _substitute;
}

//! @brief Sets the character used when the error action is set to ErrorMode::Substitute.
//! @param[in] substitute The character to inject into the input stream when an
//! invalid sequence is encountered.
void TextOutputOptions::setErrorSubstituteCharacter(char32_t substitute)
{
    _substitute = substitute;
}

////////////////////////////////////////////////////////////////////////////////
// TextOutputStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_UNIQUE_PTR(TextOutputStream);

//! @brief Constructs an object to write text to a binary object stream using
//! default options.
//! @param[in] output A pointer to the output stream to encode text to.
TextOutputStream::TextOutputStream(IStream *output)
{
    if (output == nullptr)
    {
        throw ArgumentNullException("output");
    }

    initialise(output);
}

//! @brief Constructs an object to write text to a binary object stream using
//! specified options.
//! @param[in] output A pointer to the output stream to encode text to.
//! @param[in] options The settings which determine how text is encoded.
TextOutputStream::TextOutputStream(IStream *output, const TextOutputOptions &options) :
    _options(options)
{
    if (output == nullptr)
    {
        throw ArgumentNullException("output");
    }

    initialise(output);
}

//! @brief Constructs an object to write text to a binary object stream using
//! default options.
//! @param[out] output A pointer to an output stream to encode text to and take
//! ownership of.
TextOutputStream::TextOutputStream(IStreamUPtr &&output)
{
    if (output)
    {
        initialise(std::move(output));
    }
    else
    {
        throw ArgumentNullException("output");
    }
}

//! @brief Constructs an object to write text to a binary object stream using
//! default options.
//! @param[out] output A pointer to an output stream to encode text to and take
//! ownership of.
//! @param[in] options The settings which determine how text is encoded.
TextOutputStream::TextOutputStream(IStreamUPtr &&output, const TextOutputOptions &options) :
    _options(options)
{
    if (output)
    {
        initialise(std::move(output));
    }
    else
    {
        throw ArgumentNullException("output");
    }
}

//! @brief Creates a new object by acquiring the contents of another.
//! @param[in] rhs The object to acquire.
TextOutputStream::TextOutputStream(TextOutputStream &&rhs) noexcept :
    _ownedStream(std::move(rhs._ownedStream)),
    _destinationStream(std::exchange(rhs._destinationStream, nullptr)),
    _encoder(std::move(rhs._encoder)),
    _options(rhs._options),
    _newlineEncoding(rhs._newlineEncoding.retarget(rhs._encodings, _encodings)),
    _substituteEncoding(rhs._substituteEncoding.retarget(rhs._encodings, _encodings)),
    _isStarted(std::exchange(rhs._isStarted, false))
{
    // Copy cached encodings of newlines and placeholders.
    std::copy_n(rhs._encodings, EncodingBufferSize, _encodings);

    // Reset rhs fields to defaults.
    rhs._options = {};
    rhs._newlineEncoding = ByteConstView();
    rhs._substituteEncoding = ByteConstView();
    std::fill_n(rhs._encodings, EncodingBufferSize, static_cast<uint8_t>(0));
}

//! @brief Brief ensures any output is flushed before the object is disposed of.
TextOutputStream::~TextOutputStream()
{
    flush();

    // Ensure the stream is not usable post-destruction.
    _destinationStream = nullptr;
}

//! @brief Ensures that all currently buffered output is flushed to
//! the inner output stream.
void TextOutputStream::flush()
{
    if (_destinationStream != nullptr)
    {
        _destinationStream->flush();
    }
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(string_cref_t &text)
{
    write(text.getUtf8Bytes(), text.getUtf8Length());
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(const std::string_view &text)
{
    encodeInternal<Utf::FromUtf8Converter>(reinterpret_cast<uint8_cptr_t>(text.data()),
                                           text.length());
}

//! @brief Writes a sequence of wide characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(const std::wstring_view &text)
{
#ifdef WCHAR_IS_32BIT
    // Write directly as UTF-32 without conversion.
    write(reinterpret_cast<utf32_cptr_t>(text.data()), text.length());
#else
    // Convert from UTF-16 to UTF-32 before output.
    encodeInternal<Utf::FromUtf16Converter>(reinterpret_cast<utf16_cptr_t>(text.data()),
                                            text.length());
#endif
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(const std::u8string_view &text)
{
    encodeInternal<Utf::FromUtf8Converter>(reinterpret_cast<uint8_cptr_t>(text.data()),
                                           text.length());
}

//! @brief Writes a sequence of UTF-16 encoded characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(const std::u16string_view &text)
{
    encodeInternal<Utf::FromUtf16Converter>(text.data(), text.length());
}

//! @brief Writes a sequence of wide characters to the output stream.
//! @param[in] text The sequence to write.
void TextOutputStream::write(const std::u32string_view &text)
{
    write(text.data(), text.length());
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream.
//! @param[in] text The sequence to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::write(utf8_cptr_t text, size_t count)
{
    encodeInternal<Utf::FromUtf8Converter>(reinterpret_cast<uint8_cptr_t>(text), count);
}

//! @brief Writes a sequence of UTF-16 encoded characters to the output stream.
//! @param[in] text The sequence to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::write(utf16_cptr_t text, size_t count)
{
    encodeInternal<Utf::FromUtf16Converter>(text, count);
}

//! @brief Writes a sequence of wide characters to the output stream.
//! @param[in] text The sequence to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::write(wchar_cptr_t text, size_t count)
{
#ifdef WCHAR_IS_32BIT
    // Write directly as UTF-32 without conversion.
    write(reinterpret_cast<utf32_cptr_t>(text), count);
#else
    // Convert from UTF-16 to UTF-32 before output.
    encodeInternal<Utf::FromUtf16Converter>(reinterpret_cast<utf16_cptr_t>(text), count);
#endif
}

//! @brief Encodes Unicode characters as sequences of bytes and writes
//! them to the underlying stream.
//! @param[in] text A pointer to the array of code points to write.
//! @param[in] count The count of elements in @p text.
void TextOutputStream::write(utf32_cptr_t text, size_t count)
{
    // Verify parameters.
    if (text == nullptr)
        throw ArgumentNullException("text");

    if (count < 1)
        return;

    if (_isStarted == false)
    {
        // Ensure we only write the BOM once.
        _isStarted = true;

        writeInternal(_encoder->encodeBOM());
    }

    bool hasError;

    for (size_t written = 0; written < count; ++written)
    {
        char32_t next = text[written];

        if ((next == U'\n') && _options.isNewlineProcessingEnabled())
        {
            // Write out the pre-encoded sequence.
            writeInternal(_newlineEncoding);
        }
        else
        {
            // Simply encode the character as a byte sequence.
            ByteConstView encodedBytes = _encoder->encodeCodePoint(next, hasError);

            if (hasError)
            {
                // Handle encoding error.
                handleEncodingError(next);
            }
            else if (encodedBytes.isEmpty())
            {
                // Handle non-encodeable code point.
                handleNoEncoding(next);
            }
            else
            {
                writeInternal(encodedBytes);
            }
        }
    }
}

//! @brief Writes a new line to the output stream.
void TextOutputStream::writeLine()
{
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(string_cref_t &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(const std::string_view &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of wide characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(const std::wstring_view &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(const std::u8string_view &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-16 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(const std::u16string_view &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-32 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
void TextOutputStream::writeLine(const std::u32string_view &text)
{
    write(text);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-8 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::writeLine(utf8_cptr_t text, size_t count)
{
    write(text, count);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-16 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::writeLine(utf16_cptr_t text, size_t count)
{
    write(text, count);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of wide characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::writeLine(wchar_cptr_t text, size_t count)
{
    write(text, count);
    writeInternal(_newlineEncoding);
}

//! @brief Writes a sequence of UTF-32 encoded characters to the output stream
//! followed by a new line.
//! @param[in] text The sequence of characters to write.
//! @param[in] count The count of valid elements in @p text.
void TextOutputStream::writeLine(utf32_cptr_t text, size_t count)
{
    write(text, count);
    writeInternal(_newlineEncoding);
}

//! @brief Formats text and writes it to the output stream.
//! @param[in] formatExpr An expression compatible with Ag::String::format().
//! @param[in] values The set off values to be formatted into the output text.
void TextOutputStream::format(const std::string_view &formatExpr,
                              const VariantList &values)
{
    std::string buffer;
    appendFormat(formatExpr, buffer, values);
    write(buffer.c_str(), buffer.length());
}

//! @brief Formats text and writes it to the output stream.
//! @param[in] options Settings detailing how values should be formatted as text.
//! @param[in] formatExpr An expression compatible with Ag::String::format().
//! @param[in] values The set off values to be formatted into the output text.
void TextOutputStream::format(const FormatInfo &options,
                              const std::string_view &formatExpr,
                              const VariantList &values)
{
    std::string buffer;
    appendFormat(options, formatExpr, buffer, values);
    write(buffer.c_str(), buffer.length());
}

//! @brief Formats text and writes it to the output stream followed by a new line.
//! @param[in] formatExpr An expression compatible with Ag::String::format().
//! @param[in] values The set off values to be formatted into the output text.
void TextOutputStream::formatLine(const std::string_view &formatExpr,
                                  const VariantList &values)
{
    format(formatExpr, values);
    writeInternal(_newlineEncoding);
}

//! @brief Formats text and writes it to the output stream followed by a new line.
//! @param[in] options Settings detailing how values should be formatted as text.
//! @param[in] formatExpr An expression compatible with Ag::String::format().
//! @param[in] values The set off values to be formatted into the output text.
void TextOutputStream::formatLine(const FormatInfo &options,
                                  const std::string_view &formatExpr,
                                  const VariantList &values)
{
    std::string buffer;
    appendFormat(options, formatExpr, buffer, values);
    write(buffer.c_str(), buffer.length());

    writeInternal(_newlineEncoding);
}

//! @brief Overwrites the current object by acquiring the contents of another.
//! @param[in] rhs The object to acquire.
//! @return A reference to the current object.
TextOutputStream &TextOutputStream::operator=(TextOutputStream &&rhs) noexcept
{
    if (&rhs != this)
    {
        _ownedStream = std::move(rhs._ownedStream);
        _destinationStream = std::exchange(rhs._destinationStream, nullptr);
        _encoder = std::move(rhs._encoder);
        _options = rhs._options;
        _isStarted = std::exchange(rhs._isStarted, false);

        std::copy_n(rhs._encodings, EncodingBufferSize, _encodings);

        _newlineEncoding = rhs._newlineEncoding.retarget(rhs._encodings, _encodings);
        _substituteEncoding = rhs._substituteEncoding.retarget(rhs._encodings, _encodings);
        _isStarted = std::exchange(rhs._isStarted, false);

        // Reset rhs fields to defaults.
        rhs._options = {};
        rhs._newlineEncoding = ByteConstView();
        rhs._substituteEncoding = ByteConstView();
        std::fill_n(rhs._encodings, EncodingBufferSize, static_cast<uint8_t>(0));
    }

    return *this;
}

//! @brief Performs shared initialisation for the object.
//! @param[in] output A pointer to the output stream to be written to.
void TextOutputStream::initialise(IStream *output)
{
    if (output->isBuffered())
    {
        _destinationStream = output;
    }
    else
    {
        // Wrap the output stream in a buffering layer.
        _ownedStream.reset(new BufferedOutputStream(output));
        _destinationStream = _ownedStream.get();
    }

    _encoder = createEncoder(_options.getOutputEncoding());

    // Create an encoding of the placeholder.
    bool hasError;

    if (_options.isNewlineProcessingEnabled())
    {
        // Get the Unicode encoding of a new line.
        CodePointConstView newlineEncoding = getNewLineEncoding(_options.getNewlineEncoding());

        // Get length of the output encoding of a new line.
        size_t encodingLength = 0;

        for (char32_t codePoint : newlineEncoding)
        {
            ByteConstView encodedChar = _encoder->encodeCodePoint(codePoint, hasError);

            if (hasError)
            {
                throw CharacterEncodingFailureException(codePoint);
            }
            else if (encodedChar.isEmpty())
            {
                throw NoCharacterEncodingException(_encoder->getName(), codePoint);
            }
            else
            {
                // Copy the encoding of the code point to the output buffer.
                encodedChar.copyTo(_encodings + encodingLength);

                encodingLength += encodedChar.getCount();
            }
        }

        _newlineEncoding = ByteConstView(_encodings, encodingLength);
    }

    if ((_options.getEncodingFailureAction() == TextOutputOptions::ErrorMode::Substitute) ||
        (_options.getErrorAction() == TextOutputOptions::ErrorMode::Substitute))
    {
        ByteConstView placeholderEncoding = _encoder->encodeCodePoint(_options.getErrorSubstituteCharacter(), hasError);
        uint8_ptr_t placeholderBuffer = _encodings + _newlineEncoding.getCount();

        if (hasError)
        {
            throw CharacterEncodingFailureException(_options.getErrorSubstituteCharacter());
        }
        else if (placeholderEncoding.isEmpty())
        {
            throw NoCharacterEncodingException(_encoder->getName(),
                                               _options.getErrorSubstituteCharacter());
        }
        else
        {
            // Copy the encoding.
            placeholderEncoding.copyTo(placeholderBuffer);

            _substituteEncoding = ByteConstView(placeholderBuffer,
                                                 placeholderEncoding.getCount());
        }
    }

    // Mark output as already started if we aren't going to write
    // a BOM pre-amble before the first byte.
    _isStarted = (_options.writeBOM() == false);
}

//! @brief Performs shared initialisation for the object.
//! @param[in] output The output stream to be written to and to manage the
//! lifetime of.
void TextOutputStream::initialise(IStreamUPtr &&output)
{
    if (output->isBuffered())
    {
        // The stream is already buffered, no need for more buffering.
        _ownedStream = std::move(output);
    }
    else
    {
        // Wrap the output stream in a buffered stream which is capable of
        // managing the lifetime of the base stream.
        _ownedStream.reset(new BufferedOutputStream(std::move(output)));
    }

    initialise(_ownedStream.get());
}

//! @brief Writes encoded bytes to the underlying output stream.
//! @param[in] bytes A view of the bytes to write.
//! @throws IOException Thrown if not all of the bytes could be written.
void TextOutputStream::writeInternal(const ByteConstView &bytes)
{
    if (bytes.isEmpty() || (_destinationStream == nullptr))
        return;

    size_t written = _destinationStream->write(bytes.getData(), bytes.getByteCount());

    if (written != bytes.getByteCount())
    {
        // Raise an error.
        throw IOException("Failed to write ");
    }
}

//! @brief Handles a failure to encode a Unicode code point for output.
//! @param[in] character The code point which couldn't be encoded.
void TextOutputStream::handleEncodingError(char32_t character)
{
    switch (_options.getErrorAction())
    {
    case TextOutputOptions::ErrorMode::Substitute:
        writeInternal(_substituteEncoding);
        break;

    case TextOutputOptions::ErrorMode::Throw:
        throw CharacterEncodingFailureException(character);
        break;

    case TextOutputOptions::ErrorMode::Ignore:
    default:
        break;
    }
}

//! @brief Handles an attempt to write a character which has no
//! corresponding sequence in the output encoding.
//! @param[in] character The Unicode code point which could not
//! be encoded.
void TextOutputStream::handleNoEncoding(char32_t character)
{
    switch (_options.getEncodingFailureAction())
    {
    case TextOutputOptions::ErrorMode::Substitute:
        writeInternal(_substituteEncoding);
        break;

    case TextOutputOptions::ErrorMode::Throw:
        throw NoCharacterEncodingException(_encoder->getName(), character);
        break;

    case TextOutputOptions::ErrorMode::Ignore:
    default:
        break;
    }
}

template<typename TConverter, typename T>
void TextOutputStream::encodeInternal(const T *text, size_t count)
{
    TConverter converter;

    constexpr size_t OutputBufferSize = 32;
    constexpr size_t InputBufferSize = 4;
    char32_t outputBuffer[OutputBufferSize];
    T inputBuffer[InputBufferSize];

    size_t readCount = 0;

    while (readCount < count)
    {
        size_t outputBufferWritten = 0;
        size_t inputBufferWritten = 0;
        bool hasError;

        // Batch conversions to UTF-32.
        while ((readCount < count) && (outputBufferWritten < OutputBufferSize))
        {
            inputBuffer[inputBufferWritten] = text[readCount];

            if (converter.tryConvert(text[readCount++],
                                     outputBuffer[outputBufferWritten],
                                     hasError))
            {
                if (hasError)
                {
                    // Handle input error according to the stream options.
                    switch (_options.getErrorAction())
                    {
                    case TextOutputOptions::ErrorMode::Throw:
                        throw CharacterEncodingFailureException(inputBuffer, inputBufferWritten);
                        break;

                    case TextOutputOptions::ErrorMode::Substitute:
                        outputBuffer[outputBufferWritten++] = _options.getErrorSubstituteCharacter();
                        break;

                    case TextOutputOptions::ErrorMode::Ignore:
                    default: // Do nothing, no character output.
                        break;
                    }
                }
                else
                {
                    inputBufferWritten = 0;
                    ++outputBufferWritten;
                }

                converter.reset();
            }
        }

        // Output the contents of the code point buffer.
        write(outputBuffer, outputBufferWritten);
        readCount += outputBufferWritten;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

