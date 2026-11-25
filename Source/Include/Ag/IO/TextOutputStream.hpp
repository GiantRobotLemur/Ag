//! @file Ag/IO/TextOutputStream.hpp
//! @brief The declaration of an object which can encode characters as bytes
//! sent to a binary output stream.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_TEXT_OUTPUT_STREAM_HPP_
#define HEADER_IO_TEXT_OUTPUT_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core.hpp>

#include "TextEncoding.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which describes how text should be encoded when output.
class TextOutputOptions
{
public:
    // Public Types

    //! @brief Expresses the encoding of line breaks in output.
    enum class NewlineEncoding : uint8_t
    {
        //! @brief Encode new lines as a single '\n' character used by POSIX-standard
        //! and RISC OS-based systems.
        LF,

        //! @brief Encode new lines as a '\r\n' character sequence used by the
        //! Microsoft Windows, OS/2 and various 16-bit systems.
        CR_LF,

        //! @brief Encode new lines as a single '\r' character used by various
        //! 8-bit micros and classic Mac OS.
        CR,

        //! @brief Encode line endings as a '\n\r' character sequence used by the
        //! RISC OS spooler.
        LF_CR,
    };

    //! Expresses what a stream writer should do in the event of an invalid
    //! character being sent for output.
    enum class ErrorMode : uint8_t
    {
        //! @brief The invalid sequence should be ignored, no characters are
        //! generated.
        Ignore,

        //! @brief The substitute character should be output in place of the
        //! bad combination.
        Substitute,

        //! @brief The stream reader should throw an exception when an invalid
        //! sequence of bytes is encountered.
        Throw,
    };

    // Public Constants
#ifdef _WIN32
    static constexpr NewlineEncoding DefaultNewline = NewlineEncoding::CR_LF;
#else
    static constexpr NewlineEncoding DefaultNewline = NewlineEncoding::LF;
#endif

    // Construction/Destruction
    TextOutputOptions() = default;

    // Accessors
    TextEncoding getOutputEncoding() const;
    void setOutputEncoding(TextEncoding textEncoding);

    NewlineEncoding getNewlineEncoding() const;
    void setNewlineEncoding(NewlineEncoding nlEncoding);

    bool isNewlineProcessingEnabled() const;
    void enableNewlineProcessing(bool isEnabled);

    bool writeBOM() const;
    void enableWriteBOM(bool isEnabled);

    ErrorMode getErrorAction() const;
    void setErrorAction(ErrorMode action);

    ErrorMode getEncodingFailureAction() const;
    void setEncodingFailureAction(ErrorMode action);

    char32_t getErrorSubstituteCharacter() const;
    void setErrorSubstituteCharacter(char32_t substitute);
private:
    // Internal Fields
    char32_t _substitute = U'?';
    TextEncoding _outputEncoding = TextEncoding::UTF8;
    NewlineEncoding _newline = DefaultNewline;
    ErrorMode _errorAction = ErrorMode::Ignore;
    ErrorMode _encodingFailureAction = ErrorMode::Substitute;
    bool _writeBOM = true;
    bool _processNewlines = true;
};

//! @brief An interface to an object which encodes Unicode code points as
//! sequences of bytes.
class ICharacterEncoder
{
protected:
    // Construction/Destruction
    ICharacterEncoder() = default;
public:
    virtual ~ICharacterEncoder() = default;

    // Accessors
    //! @brief Gets the display name of the encoding the object implements.
    virtual std::string_view getName() const = 0;

    // Operations

    //! @brief Returns an encoding of the Byte Order Mark appropriate for
    //! the supported encoding.
    //! @return A span pointing to an internal buffer which will be
    //! overwritten by subsequent calls which return a ByteSpan.
    virtual ByteConstView encodeBOM() = 0;

    //! @brief Encodes a Unicode code point into a sequence of bytes.
    //! @param[in] next The code point to encode.
    //! @param[out] error A flag set if the value of @p next is invalid.
    //! @returns A span representing an internal buffer giving the encoded
    //! form of the code point. This remains valid until the next call to
    //! the function.
    //! If the returned span is empty, the code point could not be encoded
    //! in the current coding scheme.
    virtual ByteConstView encodeCodePoint(char32_t next, bool &error) =0;
};

DECLARE_UNIQUE_PTR(ICharacterEncoder);

//! @brief An object which can encode characters as bytes sent to a binary
//! output stream.
class TextOutputStream
{
public:
    // Construction/Destruction
    TextOutputStream() = delete;
    TextOutputStream(IStream *output);
    TextOutputStream(IStream *output, const TextOutputOptions &options);
    TextOutputStream(IStreamUPtr &&output);
    TextOutputStream(IStreamUPtr &&output, const TextOutputOptions &options);
    TextOutputStream(const TextOutputStream &) = delete;
    TextOutputStream(TextOutputStream &&rhs) noexcept;
    ~TextOutputStream();

    // Operations
    void flush();
    void write(string_cref_t &text);
    void write(const std::string_view &text);
    void write(const std::wstring_view &text);
    void write(const std::u8string_view &text);
    void write(const std::u16string_view &text);
    void write(const std::u32string_view &text);
    void write(utf8_cptr_t text, size_t count);
    void write(utf16_cptr_t text, size_t count);
    void write(wchar_cptr_t text, size_t count);
    void write(utf32_cptr_t text, size_t count);

    void writeLine();
    void writeLine(string_cref_t &text);
    void writeLine(const std::string_view &text);
    void writeLine(const std::wstring_view &text);
    void writeLine(const std::u8string_view &text);
    void writeLine(const std::u16string_view &text);
    void writeLine(const std::u32string_view &text);
    void writeLine(utf8_cptr_t text, size_t count);
    void writeLine(utf16_cptr_t text, size_t count);
    void writeLine(wchar_cptr_t text, size_t count);
    void writeLine(utf32_cptr_t text, size_t count);

    void format(const std::string_view &formatExpr, const VariantList &values);
    void format(const FormatInfo &options, const std::string_view &formatExpr, const VariantList &values);
    void formatLine(const std::string_view &formatExpr, const VariantList &values);
    void formatLine(const FormatInfo &options, const std::string_view &formatExpr, const VariantList &values);

    TextOutputStream &operator=(const TextOutputStream &) = delete;
    TextOutputStream &operator=(TextOutputStream &&rhs) noexcept;
private:
    // Internal Constants

    // Calculate the maximum size of buffer required to represent a place holder
    // character and a newline sequence in any encoding.
    static constexpr size_t MaxNewLineLength = 2;
    static constexpr size_t MaxPlaceholderLength = 1;
    static constexpr size_t MaxCharEncodingSize = std::max(sizeof(char32_t), Utf::ToUtf8Converter::MaxEncodingSize);
    static constexpr size_t EncodingBufferSize = (MaxNewLineLength + MaxPlaceholderLength) * MaxCharEncodingSize;

    // Internal Functions
    void initialise(IStream *output);
    void initialise(IStreamUPtr &&output);
    void writeInternal(const ByteConstView &bytes);
    void handleEncodingError(char32_t character);
    void handleNoEncoding(char32_t character);

    template<typename TConverter, typename T>
    void encodeInternal(const T *text, size_t count);

    // Internal Fields
    IStreamUPtr _ownedStream;
    IStream *_destinationStream = nullptr;
    ICharacterEncoderUPtr _encoder;
    TextOutputOptions _options;
    uint8_t _encodings[EncodingBufferSize];
    ByteConstView _newlineEncoding;
    ByteConstView _substituteEncoding;
    bool _isStarted = false;
};

DECLARE_UNIQUE_PTR(TextOutputStream);

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
