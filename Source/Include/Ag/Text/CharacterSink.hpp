//! @file Ag/Text/CharacterSink.hpp
//! @brief The declaration of an interface to an object which receives text
//! characters for processing or storage.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_CHARACTER_SINK_HPP__
#define _AG_TEXT_CHARACTER_SINK_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Stream.hpp"

namespace Ag {
namespace Text {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An interface to an object which receives text characters for
//! processing or storage.
class ICharacterSink
{
protected:
    // Construction/Destruction
    ICharacterSink() = default;
public:
    virtual ~ICharacterSink() = default;

    // Operations

    //! @brief Ensures that all characters previously passed to the write()
    //! member function have been processed by this object.
    virtual void flush() = 0;

    //! @brief Processes a collection of UTF-8-encoded Unicode bytes.
    //! @param[in] characters The array of characters to write.
    //! @param[in] count The number of characters in @p characters to process.
    //! @returns The count of characters actually processed.
    virtual void writeUtf8(utf8_cptr_t characters, size_t count) = 0;

    //! @brief Processes a collection of UTF-16-encoded Unicode words.
    //! @param[in] characters The array of characters to write.
    //! @param[in] count The number of characters in @p characters to process.
    //! @returns The count of characters actually processed.
    virtual void writeUtf16(utf16_cptr_t characters, size_t count) = 0;

    //! @brief Processes a collection of UTF-32-encoded Unicode characters.
    //! @param[in] characters The array of characters to write.
    //! @param[in] count The number of characters in @p characters to process.
    //! @returns The count of characters actually processed.
    virtual void writeUtf32(utf32_cptr_t characters, size_t count) = 0;

    //! @brief Processes a collection of wide characters.
    //! @param[in] characters The array of characters to write.
    //! @param[in] count The number of characters in @p characters to process.
    //! @returns The count of characters actually processed.
    virtual void writeWide(wchar_cptr_t characters, size_t count) = 0;
};

//! @brief An alias for a unique pointer to an implementation of ICharacterSink.
using ICharacterSinkUPtr = std::unique_ptr<ICharacterSink>;

//! @brief A base implementation of ICharacterSink which writes to a stream.
class StreamCharacterSink : public ICharacterSink
{
protected:
    // Construction/Destruction
    StreamCharacterSink(Ag::IStream *output);
public:
    virtual ~StreamCharacterSink();

    // Operations
    void setBufferSize(size_t byteCount);

    // Overrides
    virtual void flush() override;
protected:
    // Internal Functions
    void writeBytes(const void *bytes, size_t count);

private:
    void flushCache();

    // Internal Fields
    Ag::IStream *_sink;
    Ag::ByteBlock _buffer;
};

//! @brief An alias for a unique pointer to an implementation of StreamCharacterSink.
using StreamCharacterSinkUPtr = std::unique_ptr<StreamCharacterSink>;

//! @brief An implementation of StreamCharacterSink which encodes characters as
//! UTF-8 bytes.
class Utf8StreamCharacterSink : public StreamCharacterSink
{
public:
    // Construction/Destruction
    Utf8StreamCharacterSink(Ag::IStream *output);
    virtual ~Utf8StreamCharacterSink() = default;

    // Overrides
    virtual void writeUtf8(utf8_cptr_t characters, size_t count) override;
    virtual void writeUtf16(utf16_cptr_t characters, size_t count) override;
    virtual void writeUtf32(utf32_cptr_t characters, size_t count) override;
    virtual void writeWide(wchar_cptr_t characters, size_t count) override;
};

//! @brief An implementation of StreamCharacterSink which encodes characters as
//! UTF-8 bytes.
class Utf16StreamCharacterSink : public StreamCharacterSink
{
public:
    // Construction/Destruction
    Utf16StreamCharacterSink(Ag::IStream *output, Bin::Endedness byteOrder = Bin::Endedness::Native);
    virtual ~Utf16StreamCharacterSink() = default;

    // Overrides
    virtual void writeUtf8(utf8_cptr_t characters, size_t count) override;
    virtual void writeUtf16(utf16_cptr_t characters, size_t count) override;
    virtual void writeUtf32(utf32_cptr_t characters, size_t count) override;
    virtual void writeWide(wchar_cptr_t characters, size_t count) override;
private:
    // Internal Functions
    void writeWord(char16_t utf16Word);

    // Internal Fields
    bool _reorderBytes;
};

//! @brief An implementation of StreamCharacterSink which encodes characters as
//! UTF-8 bytes.
class Utf32StreamCharacterSink : public StreamCharacterSink
{
public:
    // Construction/Destruction
    Utf32StreamCharacterSink(Ag::IStream *output, Bin::Endedness byteOrder = Bin::Endedness::Native);
    virtual ~Utf32StreamCharacterSink() = default;

    // Overrides
    virtual void writeUtf8(utf8_cptr_t characters, size_t count) override;
    virtual void writeUtf16(utf16_cptr_t characters, size_t count) override;
    virtual void writeUtf32(utf32_cptr_t characters, size_t count) override;
    virtual void writeWide(wchar_cptr_t characters, size_t count) override;
private:
    // Internal Functions
    void writeCodePoint(char32_t codePoint);

    // Internal Fields
    bool _reorderBytes;
};

#ifdef WCHAR_IS_32BIT
using WideStreamCharacterSink = Utf32StreamCharacterSink;
#else
using WideStreamCharacterSink = Utf16StreamCharacterSink;
#endif

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
StreamCharacterSinkUPtr createCharacterStream(IStream *output,
                                              Utf::Encoding encoding = Utf::Utf8,
                                              Bin::Endedness byteOrder = Bin::Endedness::Native);

}} // namespace Ag::Text

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
