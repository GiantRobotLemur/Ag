//! @file Ag/Text/CharacterSource.hpp
//! @brief The declaration of an interface to an object which reads text from
//! an input source.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_CHARACTER_SOURCE_HPP__
#define _AG_TEXT_CHARACTER_SOURCE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Configuration.hpp"
#include "Ag/Core/Binary.hpp"
#include "Ag/Core/Stream.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An interface to an object which reads text from an input source.
class ICharacterSource
{
protected:
    // Construction/Destruction
    ICharacterSource() = default;
public:
    virtual ~ICharacterSource() = default;

    //! @brief Reads characters as a collection of UTF-8 encoded bytes.
    //! @param[in] characters The buffer to receive the next characters.
    //! @param[in] maxBytes The maximum number of bytes which can be stored in
    //! @p characters.
    //! @return The number of bytes actually stored in @p characters.
    virtual size_t readUtf8(utf8_ptr_t characters, size_t maxBytes) = 0;

    //! @brief Reads characters as a collection of UTF-16 encoded words.
    //! @param[in] characters The buffer to receive the next characters.
    //! @param[in] maxWords The maximum number of 16-bit words which can be
    //! stored in @p characters.
    //! @return The number of 16-bit words actually stored in @p characters.
    virtual size_t readUtf16(utf16_ptr_t characters, size_t maxWords) = 0;

    //! @brief Reads characters as a collection of 32-bit Unicode code points.
    //! @param[in] characters The buffer to receive the next characters.
    //! @param[in] maxWords The maximum number of 32-bit code points which can
    //! be stored in @p characters.
    //! @return The number of 32-bit code points actually stored in @p characters.
    virtual size_t readUtf32(utf32_ptr_t characters, size_t maxCodePoints) = 0;

    //! @brief Reads characters as a collection of implementation-defined
    //! wide characters.
    //! @param[in] characters The buffer to receive the next characters.
    //! @param[in] maxWords The maximum number of wide characters which can
    //! be stored in @p characters.
    //! @return The number of wide characters actually stored in @p characters.
    virtual size_t readWide(wchar_ptr_t characters, size_t maxChars) = 0;
};

//! @brief An alias for a unique pointer to an ICharacterSource implementation.
using ICharacterSourceUPtr = std::unique_ptr<ICharacterSource>;

//! @brief A base class for implementations of ICharacterSource which read from
//! binary input streams.
class StreamCharacterSource : public ICharacterSource
{
protected:
    // Construction/Destruction
    StreamCharacterSource(Ag::IStream *input,
                          uint8_cptr_t initialBytes = nullptr,
                          size_t initialCount = 0);
public:
    virtual ~StreamCharacterSource() = default;

    // Operations
    void setBufferSize(size_t byteCount);

protected:
    // Internal Functions
    bool tryGetNextByte(uint8_t &next);
    void rollback(size_t count);
    size_t commit();
    bool tryRefillBuffer();
    size_t getUnreadByteCount() const;
    size_t readBytes(void *output, size_t maxCount);

private:
    // Internal Fields
    Ag::IStream *_source;
    Ag::ByteBlock _buffer;
    size_t _commitOffset;
    size_t _readOffset;
};

//! @brief An implementation of ICharacterSource which interprets UTF-8 encoded
//! bytes from a binary input stream.
class Utf8StreamCharacterSource : public StreamCharacterSource
{
public:
    // Construction/Destruction
    Utf8StreamCharacterSource(Ag::IStream *input,
                              uint8_cptr_t initialBytes,
                              size_t initialCount = 0);
    virtual ~Utf8StreamCharacterSource() = default;

    // Overrides
    virtual size_t readUtf8(utf8_ptr_t characters, size_t maxBytes) override;
    virtual size_t readUtf16(utf16_ptr_t characters, size_t maxWords) override;
    virtual size_t readUtf32(utf32_ptr_t characters, size_t maxCodePoints) override;
    virtual size_t readWide(wchar_ptr_t characters, size_t maxChars) override;
private:
    // Internal Functions
    bool tryGetBufferedCodePoint(char32_t &next);
};

//! @brief An implementation of ICharacterSource which interprets UTF-16 encoded
//! words from a binary input stream.
class Utf16StreamCharacterSource : public StreamCharacterSource
{
public:
    // Construction/Destruction
    Utf16StreamCharacterSource(Ag::IStream *input,
                               Bin::Endedness byteOrder = Bin::Endedness::Native,
                               uint8_cptr_t initialBytes = nullptr, size_t initialCount = 0);
    virtual ~Utf16StreamCharacterSource() = default;

    // Overrides
    virtual size_t readUtf8(utf8_ptr_t characters, size_t maxBytes) override;
    virtual size_t readUtf16(utf16_ptr_t characters, size_t maxWords) override;
    virtual size_t readUtf32(utf32_ptr_t characters, size_t maxCodePoints) override;
    virtual size_t readWide(wchar_ptr_t characters, size_t maxChars) override;
private:
    // Internal Functions
    bool tryGetBufferedCodePoint(char32_t &next);
    bool tryReadWord(char16_t &word);

    // Internal Fields
    bool _reorderBytes;
};

//! @brief An implementation of ICharacterSource which interprets UTF-32 encoded
//! code points from a binary input stream.
class Utf32StreamCharacterSource : public StreamCharacterSource
{
public:
    // Construction/Destruction
    Utf32StreamCharacterSource(Ag::IStream *input,
                               Bin::Endedness byteOrder = Bin::Endedness::Native,
                               uint8_cptr_t initialBytes = nullptr, size_t initialCount = 0);
    virtual ~Utf32StreamCharacterSource() = default;

    // Overrides
    virtual size_t readUtf8(utf8_ptr_t characters, size_t maxBytes) override;
    virtual size_t readUtf16(utf16_ptr_t characters, size_t maxWords) override;
    virtual size_t readUtf32(utf32_ptr_t characters, size_t maxCodePoints) override;
    virtual size_t readWide(wchar_ptr_t characters, size_t maxChars) override;
private:
    // Internal Functions
    bool tryGetBufferedCodePoint(char32_t &next);

    // Internal Fields
    bool _reorderBytes;
};

//! @brief An alias for a unique pointer to a character source.
using StreamCharacterSourceUPtr = std::unique_ptr<StreamCharacterSource>;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
StreamCharacterSourceUPtr createStreamCharacterSource(IStream *input,
                                                      Utf::Encoding encoding = Utf::Encoding::Utf8,
                                                      Bin::Endedness byteOrder = Bin::Endedness::Native,
                                                      bool detectFromBOM = false);

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
