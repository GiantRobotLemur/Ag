//! @file Text/Test_CharacterSource.cpp
//! @brief The definition of unit tests for StreamCharacterSource and its
//! UTF-8/UTF-16/UTF-32 derivatives, plus the createStreamCharacterSource
//! factory.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstring>
#include <iterator>

#include <gtest/gtest.h>

#include "Ag/Text/CharacterSource.hpp"
#include "Test_MemoryStream.hpp"

namespace Ag {
namespace Text {

namespace {

using Ag::Test::MemoryReadStream;

////////////////////////////////////////////////////////////////////////////////
// Local Data — sample text "A \u00E9 \u20AC \U0001D11E" pre-encoded in every form we need.
//   Code points: U+0041 U+0020 U+00E9 U+0020 U+20AC U+0020 U+1D11E
//   Spans 1, 2, 3, and 4-byte UTF-8 sequences and a UTF-16 surrogate pair.
////////////////////////////////////////////////////////////////////////////////
constexpr char32_t kSampleUtf32[] = {
    U'A',
    U' ',
    U'\u00E9',
    U' ',
    U'\u20AC',
    U' ',
    U'\U0001D11E'
};

constexpr size_t kSampleCodePointCount = std::size(kSampleUtf32);

constexpr char16_t kSampleUtf16[] = {
    u'A', u' ', u'\u00E9', u' ', u'\u20AC', u' ',
    char16_t(0xD834), char16_t(0xDD1E)
};

constexpr size_t kSampleUtf16WordCount = std::size(kSampleUtf16);

constexpr uint8_t kSampleUtf8[] = {
    0x41, 0x20, 0xC3, 0xA9, 0x20, 0xE2, 0x82, 0xAC,
    0x20, 0xF0, 0x9D, 0x84, 0x9E
};

constexpr size_t kSampleUtf8ByteCount = std::size(kSampleUtf8);

constexpr uint8_t kSampleUtf16Le[] = {
    0x41, 0x00,  0x20, 0x00,  0xE9, 0x00,  0x20, 0x00,
    0xAC, 0x20,  0x20, 0x00,  0x34, 0xD8,  0x1E, 0xDD
};

constexpr uint8_t kSampleUtf16Be[] = {
    0x00, 0x41,  0x00, 0x20,  0x00, 0xE9,  0x00, 0x20,
    0x20, 0xAC,  0x00, 0x20,  0xD8, 0x34,  0xDD, 0x1E
};

constexpr uint8_t kSampleUtf32Le[] = {
    0x41, 0x00, 0x00, 0x00,  0x20, 0x00, 0x00, 0x00,
    0xE9, 0x00, 0x00, 0x00,  0x20, 0x00, 0x00, 0x00,
    0xAC, 0x20, 0x00, 0x00,  0x20, 0x00, 0x00, 0x00,
    0x1E, 0xD1, 0x01, 0x00
};

constexpr uint8_t kSampleUtf32Be[] = {
    0x00, 0x00, 0x00, 0x41,  0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x00, 0xE9,  0x00, 0x00, 0x00, 0x20,
    0x00, 0x00, 0x20, 0xAC,  0x00, 0x00, 0x00, 0x20,
    0x00, 0x01, 0xD1, 0x1E
};

////////////////////////////////////////////////////////////////////////////////
// Local Helpers
////////////////////////////////////////////////////////////////////////////////
template <typename Char>
::testing::AssertionResult chunksEqual(const Char *expected, size_t expectedCount,
                                       const Char *actual, size_t actualCount)
{
    if (expectedCount != actualCount)
    {
        return ::testing::AssertionFailure()
            << "lengths differ: expected " << expectedCount
            << ", actual " << actualCount;
    }

    for (size_t i = 0; i < expectedCount; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure()
                << "element " << i << " differs: expected 0x"
                << std::hex << uint64_t(expected[i])
                << " actual 0x" << uint64_t(actual[i]);
        }
    }

    return ::testing::AssertionSuccess();
}

////////////////////////////////////////////////////////////////////////////////
// StreamCharacterSource — base class plumbing
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(StreamCharacterSource, NullStreamThrows)
{
    EXPECT_THROW(Utf8StreamCharacterSource(nullptr, nullptr, 0),
                 ArgumentNullException);
    EXPECT_THROW(Utf16StreamCharacterSource(nullptr),
                 ArgumentNullException);
    EXPECT_THROW(Utf32StreamCharacterSource(nullptr),
                 ArgumentNullException);
}

GTEST_TEST(StreamCharacterSource, NullInitialBytesWithPositiveCountThrows)
{
    MemoryReadStream stream(nullptr, 0);
    EXPECT_THROW(Utf8StreamCharacterSource(&stream, nullptr, 4),
                 ArgumentNullException);
}

////////////////////////////////////////////////////////////////////////////////
// StringCharacterSource — backed by an Ag::String (UTF-8 internally)
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(StringCharacterSource, EmptyStringReadsReturnZero)
{
    String empty;
    StringCharacterSource src(empty);

    char     u8Buffer[8] = {};
    char16_t u16Buffer[8] = {};
    char32_t u32Buffer[8] = {};
    wchar_t  wBuffer[8] = {};

    EXPECT_EQ(src.readUtf8(u8Buffer, std::size(u8Buffer)), 0u);
    EXPECT_EQ(src.readUtf16(u16Buffer, std::size(u16Buffer)), 0u);
    EXPECT_EQ(src.readUtf32(u32Buffer, std::size(u32Buffer)), 0u);
    EXPECT_EQ(src.readWide(wBuffer, std::size(wBuffer)), 0u);
}

GTEST_TEST(StringCharacterSource, ReadsAsciiAsUtf8)
{
    String text("Hello");
    StringCharacterSource src(text);

    char buffer[16] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    ASSERT_EQ(got, 5u);
    EXPECT_EQ(std::memcmp(buffer, "Hello", 5), 0);
}

GTEST_TEST(StringCharacterSource, ReadsMultiByteAsUtf8)
{
    // Construct the String from UTF-32 code points so the test is independent
    // of how the source file is encoded.
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    char buffer[32] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    ASSERT_EQ(got, kSampleUtf8ByteCount);
    EXPECT_EQ(std::memcmp(buffer, kSampleUtf8, got), 0);
}

GTEST_TEST(StringCharacterSource, ReadUtf16FromMultiByteString)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    char16_t buffer[16] = {};
    size_t got = src.readUtf16(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf16, kSampleUtf16WordCount, buffer, got));
}

GTEST_TEST(StringCharacterSource, ReadUtf32FromMultiByteString)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(StringCharacterSource, ReadWideFromMultiByteString)
{
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    wchar_t buffer[16] = {};
    size_t got = src.readWide(buffer, std::size(buffer));

#ifdef WCHAR_IS_32BIT
    ASSERT_EQ(got, kSampleCodePointCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char32_t>(buffer[i]), kSampleUtf32[i]);
#else
    ASSERT_EQ(got, kSampleUtf16WordCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char16_t>(buffer[i]), kSampleUtf16[i]);
#endif
}

GTEST_TEST(StringCharacterSource, SequentialReadsContinueFromPriorPosition)
{
    // Reading the string one code point at a time should yield exactly the
    // same characters as reading it all in one shot.
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    char32_t collected[kSampleCodePointCount] = {};
    for (size_t i = 0; i < kSampleCodePointCount; ++i)
    {
        char32_t next = 0;
        size_t got = src.readUtf32(&next, 1);
        ASSERT_EQ(got, 1u) << "stalled at index " << i;
        collected[i] = next;
    }

    char32_t terminator = 0;
    EXPECT_EQ(src.readUtf32(&terminator, 1), 0u);

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount,
                            collected, kSampleCodePointCount));
}

GTEST_TEST(StringCharacterSource, ReadsAfterExhaustionReturnZero)
{
    String text("AB");
    StringCharacterSource src(text);

    char buffer[8] = {};
    EXPECT_EQ(src.readUtf8(buffer, std::size(buffer)), 2u);
    EXPECT_EQ(src.readUtf8(buffer, std::size(buffer)), 0u);
    EXPECT_EQ(src.readUtf8(buffer, std::size(buffer)), 0u);
}

GTEST_TEST(StringCharacterSource, SmallerMaxBytesReturnsPartialUtf8)
{
    // The string-backed source reads bytes directly without enforcing UTF-8
    // code-point boundaries — a caller can therefore retrieve a long string
    // in chunks even if a chunk boundary falls inside a multi-byte encoding.
    // This test documents that the bytes across two reads concatenate back
    // into the full UTF-8 sequence.
    String text(kSampleUtf32, kSampleCodePointCount);
    StringCharacterSource src(text);

    uint8_t firstHalf[6] = {};
    uint8_t secondHalf[16] = {};

    size_t got1 = src.readUtf8(reinterpret_cast<char *>(firstHalf), 6);
    size_t got2 = src.readUtf8(reinterpret_cast<char *>(secondHalf),
                               std::size(secondHalf));

    ASSERT_EQ(got1 + got2, kSampleUtf8ByteCount);

    uint8_t combined[kSampleUtf8ByteCount];
    std::memcpy(combined, firstHalf, got1);
    std::memcpy(combined + got1, secondHalf, got2);

    EXPECT_EQ(std::memcmp(combined, kSampleUtf8, kSampleUtf8ByteCount), 0);
}

////////////////////////////////////////////////////////////////////////////////
// Utf8StreamCharacterSource
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf8StreamCharacterSource, EmptyStreamReturnsZero)
{
    MemoryReadStream stream(nullptr, 0);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char     u8Buffer[8] = {};
    char16_t u16Buffer[8] = {};
    char32_t u32Buffer[8] = {};
    wchar_t  wBuffer[8] = {};

    EXPECT_EQ(src.readUtf8(u8Buffer, std::size(u8Buffer)), 0u);
    EXPECT_EQ(src.readUtf16(u16Buffer, std::size(u16Buffer)), 0u);
    EXPECT_EQ(src.readUtf32(u32Buffer, std::size(u32Buffer)), 0u);
    EXPECT_EQ(src.readWide(wBuffer, std::size(wBuffer)), 0u);
}

GTEST_TEST(Utf8StreamCharacterSource, ReadsAsciiUtf8)
{
    constexpr uint8_t input[] = { 'H', 'e', 'l', 'l', 'o' };
    MemoryReadStream stream(input, std::size(input));
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char buffer[16] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    EXPECT_EQ(got, std::size(input));
    EXPECT_EQ(std::memcmp(buffer, input, got), 0);
}

GTEST_TEST(Utf8StreamCharacterSource, ReadsMultiByteUtf8)
{
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char buffer[64] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    EXPECT_EQ(got, kSampleUtf8ByteCount);
    EXPECT_EQ(std::memcmp(buffer, kSampleUtf8, got), 0);
}

GTEST_TEST(Utf8StreamCharacterSource, ReadUtf16FromUtf8Source)
{
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char16_t buffer[16] = {};
    size_t got = src.readUtf16(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf16, kSampleUtf16WordCount, buffer, got));
}

GTEST_TEST(Utf8StreamCharacterSource, ReadUtf32FromUtf8Source)
{
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf8StreamCharacterSource, ReadWideFromUtf8Source)
{
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    wchar_t buffer[16] = {};
    size_t got = src.readWide(buffer, std::size(buffer));

#ifdef WCHAR_IS_32BIT
    ASSERT_EQ(got, kSampleCodePointCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char32_t>(buffer[i]), kSampleUtf32[i]);
#else
    ASSERT_EQ(got, kSampleUtf16WordCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char16_t>(buffer[i]), kSampleUtf16[i]);
#endif
}

GTEST_TEST(Utf8StreamCharacterSource, OutputBufferTooSmallForCodePoint)
{
    // Just the encoding of '\u20AC' (U+20AC) — 3 UTF-8 bytes.
    constexpr uint8_t input[] = { 0xE2, 0x82, 0xAC };
    MemoryReadStream stream(input, std::size(input));
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char buffer[8] = {};

    // Asking for fewer bytes than the next code point's encoding requires
    // must roll back and return 0 — never a partial sequence.
    EXPECT_EQ(src.readUtf8(buffer, 2), 0u);

    // The next read with enough room must return the complete 3-byte sequence.
    size_t got = src.readUtf8(buffer, std::size(buffer));
    ASSERT_EQ(got, 3u);
    EXPECT_EQ(std::memcmp(buffer, input, 3), 0);
}

GTEST_TEST(Utf8StreamCharacterSource, TrickleReadFromStream)
{
    // maxBytesPerRead = 1 forces tryRefillBuffer() to be called many times,
    // exercising the partial-code-point + rollback paths inside readUtf32().
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount, 1);
    Utf8StreamCharacterSource src(&stream, nullptr, 0);
    src.setBufferSize(32);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf8StreamCharacterSource, InitialBytesArePreStoked)
{
    constexpr uint8_t initial[] = { 'A', 'B' };
    MemoryReadStream emptyStream(nullptr, 0);
    Utf8StreamCharacterSource src(&emptyStream, initial, std::size(initial));

    char buffer[8] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    EXPECT_EQ(got, 2u);
    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
}

GTEST_TEST(Utf8StreamCharacterSource, InvalidLeadingByteIsSkipped)
{
    // 0xFF is not a valid UTF-8 leading byte; the source should drop it and
    // continue decoding the surrounding ASCII characters.
    constexpr uint8_t input[] = { 'A', 0xFF, 'B' };
    MemoryReadStream stream(input, std::size(input));
    Utf8StreamCharacterSource src(&stream, nullptr, 0);

    char32_t buffer[8] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    ASSERT_EQ(got, 2u);
    EXPECT_EQ(buffer[0], U'A');
    EXPECT_EQ(buffer[1], U'B');
}

////////////////////////////////////////////////////////////////////////////////
// Utf16StreamCharacterSource
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf16StreamCharacterSource, ReadsLittleEndianUtf16)
{
    MemoryReadStream stream(kSampleUtf16Le, std::size(kSampleUtf16Le));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf16StreamCharacterSource, ReadsBigEndianUtf16)
{
    MemoryReadStream stream(kSampleUtf16Be, std::size(kSampleUtf16Be));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::BigEndian);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf16StreamCharacterSource, ReadsNativeUtf16)
{
    // Reinterpret the char16_t literal as bytes — by definition that's host
    // byte order, so Bin::Endedness::Native must decode it.
    auto *bytes = reinterpret_cast<const uint8_t *>(kSampleUtf16);
    MemoryReadStream stream(bytes, sizeof(kSampleUtf16));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::Native);

    char16_t buffer[16] = {};
    size_t got = src.readUtf16(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf16, kSampleUtf16WordCount, buffer, got));
}

GTEST_TEST(Utf16StreamCharacterSource, SurrogatePairAcrossBufferBoundary)
{
    // Trickle the LE bytes 2 at a time, with the smallest allowable buffer,
    // so that the high and low surrogates of '\U0001D11E' must straddle a refill.
    MemoryReadStream stream(kSampleUtf16Le, std::size(kSampleUtf16Le), 2);
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);
    src.setBufferSize(32);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf16StreamCharacterSource, ReadUtf8FromUtf16Source)
{
    MemoryReadStream stream(kSampleUtf16Le, std::size(kSampleUtf16Le));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char buffer[64] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    ASSERT_EQ(got, kSampleUtf8ByteCount);
    EXPECT_EQ(std::memcmp(buffer, kSampleUtf8, got), 0);
}

GTEST_TEST(Utf16StreamCharacterSource, ReadWideFromUtf16Source)
{
    MemoryReadStream stream(kSampleUtf16Le, std::size(kSampleUtf16Le));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    wchar_t buffer[16] = {};
    size_t got = src.readWide(buffer, std::size(buffer));

#ifdef WCHAR_IS_32BIT
    ASSERT_EQ(got, kSampleCodePointCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char32_t>(buffer[i]), kSampleUtf32[i]);
#else
    ASSERT_EQ(got, kSampleUtf16WordCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char16_t>(buffer[i]), kSampleUtf16[i]);
#endif
}

GTEST_TEST(Utf16StreamCharacterSource, OddNumberOfBytes)
{
    // 5 bytes — two complete BMP characters (0041 0042 in LE) and one stray
    // byte that can't form a word. The source must decode the two characters
    // and then stop cleanly.
    constexpr uint8_t input[] = { 0x41, 0x00, 0x42, 0x00, 0xFF };
    MemoryReadStream stream(input, std::size(input));
    Utf16StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char32_t buffer[8] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    ASSERT_EQ(got, 2u);
    EXPECT_EQ(buffer[0], U'A');
    EXPECT_EQ(buffer[1], U'B');
}

////////////////////////////////////////////////////////////////////////////////
// Utf32StreamCharacterSource
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf32StreamCharacterSource, ReadsLittleEndianUtf32)
{
    MemoryReadStream stream(kSampleUtf32Le, std::size(kSampleUtf32Le));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf32StreamCharacterSource, ReadsBigEndianUtf32)
{
    MemoryReadStream stream(kSampleUtf32Be, std::size(kSampleUtf32Be));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::BigEndian);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf32StreamCharacterSource, ReadsNativeUtf32)
{
    auto *bytes = reinterpret_cast<const uint8_t *>(kSampleUtf32);
    MemoryReadStream stream(bytes, sizeof(kSampleUtf32));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(Utf32StreamCharacterSource, ReadUtf8FromUtf32Source)
{
    MemoryReadStream stream(kSampleUtf32Le, std::size(kSampleUtf32Le));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char buffer[64] = {};
    size_t got = src.readUtf8(buffer, std::size(buffer));

    ASSERT_EQ(got, kSampleUtf8ByteCount);
    EXPECT_EQ(std::memcmp(buffer, kSampleUtf8, got), 0);
}

GTEST_TEST(Utf32StreamCharacterSource, ReadUtf16FromUtf32Source)
{
    MemoryReadStream stream(kSampleUtf32Le, std::size(kSampleUtf32Le));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char16_t buffer[16] = {};
    size_t got = src.readUtf16(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf16, kSampleUtf16WordCount, buffer, got));
}

GTEST_TEST(Utf32StreamCharacterSource, ReadWideFromUtf32Source)
{
    MemoryReadStream stream(kSampleUtf32Le, std::size(kSampleUtf32Le));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    wchar_t buffer[16] = {};
    size_t got = src.readWide(buffer, std::size(buffer));

#ifdef WCHAR_IS_32BIT
    ASSERT_EQ(got, kSampleCodePointCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char32_t>(buffer[i]), kSampleUtf32[i]);
#else
    ASSERT_EQ(got, kSampleUtf16WordCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(static_cast<char16_t>(buffer[i]), kSampleUtf16[i]);
#endif
}

GTEST_TEST(Utf32StreamCharacterSource, IncompleteFinalCodePoint)
{
    // 5 bytes — one complete LE code point ('A' = 41 00 00 00) then a stray
    // byte that can't form a 32-bit word.
    constexpr uint8_t input[] = { 0x41, 0x00, 0x00, 0x00, 0xFF };
    MemoryReadStream stream(input, std::size(input));
    Utf32StreamCharacterSource src(&stream, Bin::Endedness::LittleEndian);

    char32_t buffer[8] = {};
    size_t got = src.readUtf32(buffer, std::size(buffer));

    ASSERT_EQ(got, 1u);
    EXPECT_EQ(buffer[0], U'A');
}

////////////////////////////////////////////////////////////////////////////////
// createStreamCharacterSource — factory
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CreateStreamCharacterSource, NullStreamThrows)
{
    EXPECT_THROW(createStreamCharacterSource(nullptr), ArgumentNullException);
}

GTEST_TEST(CreateStreamCharacterSource, FactoryReturnsUtf8ByDefault)
{
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    auto src = createStreamCharacterSource(&stream);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryHonoursEncodingArg_Utf16)
{
    MemoryReadStream stream(kSampleUtf16Le, std::size(kSampleUtf16Le));
    auto src = createStreamCharacterSource(&stream, false, Utf::Utf16,
                                           Bin::Endedness::LittleEndian);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryHonoursEncodingArg_Utf32)
{
    MemoryReadStream stream(kSampleUtf32Le, std::size(kSampleUtf32Le));
    auto src = createStreamCharacterSource(&stream, false, Utf::Utf32,
                                           Bin::Endedness::LittleEndian);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryHonoursByteOrderArg)
{
    MemoryReadStream stream(kSampleUtf16Be, std::size(kSampleUtf16Be));
    auto src = createStreamCharacterSource(&stream, false, Utf::Utf16,
                                           Bin::Endedness::BigEndian);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryDetectsUtf8Bom)
{
    std::vector<uint8_t> bytes = { 0xEF, 0xBB, 0xBF };
    bytes.insert(bytes.end(), kSampleUtf8, kSampleUtf8 + kSampleUtf8ByteCount);

    MemoryReadStream stream(bytes.data(), bytes.size());
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryDetectsUtf16LeBom)
{
    // FF FE is the spec-correct UTF-16 LE BOM. NOTE: As of writing,
    // CharacterSource.cpp declares the constant as { 0xFF, 0xEF } — this
    // test will fail until that typo is fixed.
    std::vector<uint8_t> bytes = { 0xFF, 0xFE };
    bytes.insert(bytes.end(),
                 kSampleUtf16Le, kSampleUtf16Le + std::size(kSampleUtf16Le));

    MemoryReadStream stream(bytes.data(), bytes.size());
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryDetectsUtf16BeBom)
{
    std::vector<uint8_t> bytes = { 0xFE, 0xFF };
    bytes.insert(bytes.end(),
                 kSampleUtf16Be, kSampleUtf16Be + std::size(kSampleUtf16Be));

    MemoryReadStream stream(bytes.data(), bytes.size());
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryDetectsUtf32LeBom)
{
    std::vector<uint8_t> bytes = { 0xFF, 0xFE, 0x00, 0x00 };
    bytes.insert(bytes.end(),
                 kSampleUtf32Le, kSampleUtf32Le + std::size(kSampleUtf32Le));

    MemoryReadStream stream(bytes.data(), bytes.size());
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryDetectsUtf32BeBom)
{
    std::vector<uint8_t> bytes = { 0x00, 0x00, 0xFE, 0xFF };
    bytes.insert(bytes.end(),
                 kSampleUtf32Be, kSampleUtf32Be + std::size(kSampleUtf32Be));

    MemoryReadStream stream(bytes.data(), bytes.size());
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

GTEST_TEST(CreateStreamCharacterSource, FactoryWithNoBomFallsBackToPreferredEncoding)
{
    // No BOM prefix, detectFromBOM = true, preferred = Utf8 — the up-to-4
    // header bytes already consumed during detection should be forwarded
    // back into the source as initialBytes so no characters are lost.
    MemoryReadStream stream(kSampleUtf8, kSampleUtf8ByteCount);
    auto src = createStreamCharacterSource(&stream, true, Utf::Utf8,
                                           Bin::Endedness::Native);

    char32_t buffer[16] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    EXPECT_TRUE(chunksEqual(kSampleUtf32, kSampleCodePointCount, buffer, got));
}

} // Anonymous namespace

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////
