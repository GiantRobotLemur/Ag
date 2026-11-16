//! @file Ag/IO/TextInputStream.hpp
//! @brief The declaration of an object which can convert a stream of bytes
//! into a stream of Unicode characters.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_TEXT_INPUT_STREAM_HPP_
#define HEADER_IO_TEXT_INPUT_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core.hpp>

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
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

//! @brief An object which defines the options by which text should be decoded
//! from a binary input stream.
class TextInputOptions
{
public:
    // Public Types
    //! Expresses what a stream reader should do in the event of an invalid
    //! sequence of bytes.
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

    //! @brief Indicates the expectation of the presence of a Byte Order Mark
    //! at the beginning of the stream.
    enum class BOMMode : uint8_t
    {
        //! @brief No BOM is expected, initial bytes are interpreted as the
        //! bytes of a character in the preferred encoding.
        Ignored,

        //! @brief If a BOM is detected, it will be used to select the encoding.
        //! If initial bytes aren't recognised as a BOM, they will be interpreted
        //! as bytes of a character in the preferred encoding.
        Optional,

        //! @brief A BOM is mandatory and an exception will be thrown if the
        //! initial bytes of the stream aren't recognised as a valid Byte Order Mark.
        Mandatory,
    };

    // Construction/Destruction
    TextInputOptions() = default;
    ~TextInputOptions() = default;

    // Accessors
    TextEncoding getPreferredEncoding() const;
    void setPreferredEncoding(TextEncoding encoding);

    BOMMode getBOMExpectation() const;
    void setBOMExpectation(BOMMode mode);

    ErrorMode getErrorAction() const;
    void setErrorAction(ErrorMode action);

    char32_t getErrorSubstituteCharacter() const;
    void setErrorSubstituteCharacter(char32_t substitute);

private:
    // Internal Fields
    char32_t _substitute = U'?';
    ErrorMode _errorAction = ErrorMode::Ignore;
    TextEncoding _preferredEncoding = TextEncoding::UTF8;
    BOMMode _bomExpectation = BOMMode::Optional;
};

//! @brief An interface to an object which can decode a stream of raw
//! bytes into Unicode code points.
class ICharacterDecoder
{
public:
    // Construction/Destruction
    ICharacterDecoder() = default;
    virtual ~ICharacterDecoder() = default;

    // Accessors
    //! @brief Gets the display name of the encoding the object implements.
    virtual std::string_view getName() const = 0;

    // Operations

    //! @brief Attempts to decode the next byte in a sequence into a Unicode character.
    //! @param[in] next The next byte in the sequence to decode.
    //! @param[out] ch Receives the decoded character, if successful.
    //! @param[out] error Receives true if the decoded character was invalid if decoding
    //! completed.
    //! @retval true The character was decoded and @p ch and @p error were updated.
    //! @retval false The byte was not enough to decode the next character in the stream.
    virtual bool tryDecode(uint8_t next, char32_t &ch, bool &error) = 0;
};

DECLARE_UNIQUE_PTR(ICharacterDecoder);

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

//! @brief An object which can convert a stream of bytes into a stream of
//! Unicode characters. The object can optionally own the underlying
//! IStream from which it receives raw bytes as input.
class TextInputStream
{
public:
    // Construction/Destruction
    TextInputStream(IStream *input);
    TextInputStream(IStreamUPtr &&input);
    TextInputStream(IStream *input, const TextInputOptions &options);
    TextInputStream(IStreamUPtr &&input, const TextInputOptions &options);
    TextInputStream(const TextInputStream &) = delete;
    TextInputStream(TextInputStream &&rhs) noexcept;
    ~TextInputStream() = default;

    // Operations
    size_t read(utf32_ptr_t buffer, size_t maxCharacters);
    TextInputStream &operator=(TextInputStream &&rhs) noexcept;
private:
    // Internal Types

    // Internal Functions
    void initialise(IStream *input);
    void initialise(IStreamUPtr &&input);
    void handleInvalidSequence(utf32_ptr_t buffer, size_t &charactersRead,
                               size_t decodedByteCount) const;
    void moveAssign(TextInputStream &&rhs) noexcept;

    // Internal Fields
    static constexpr size_t DecoderSize = 8;

    IStreamUPtr _ownedStream;
    IStream *_sourceStream = nullptr;
    ICharacterDecoderUPtr _decoder;
    TextInputOptions _options;
    size_t _decodedByteCount = 0;
    uint8_t _decodedBytes[DecoderSize];
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
