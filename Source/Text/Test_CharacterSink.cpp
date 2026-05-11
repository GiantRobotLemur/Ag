//! @file Text/Test_CharacterSink.cpp
//! @brief The definition of unit tests for StreamCharacterSink and its
//! UTF-8/UTF-16/UTF-32 derivatives, plus the createCharacterStream factory
//! and end-to-end sink-to-source round trips.
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
#include <vector>

#include <gtest/gtest.h>

#include "Ag/Text/CharacterSink.hpp"
#include "Ag/Text/CharacterSource.hpp"
#include "Test_MemoryStream.hpp"

namespace Ag {
namespace Text {

namespace {

using Ag::Test::MemoryReadStream;
using Ag::Test::MemoryWriteStream;

////////////////////////////////////////////////////////////////////////////////
// Local Data — same sample text as Test_CharacterSource.cpp.
//   "A \u00E9 \u20AC \U0001D11E" — code points U+0041 U+0020 U+00E9 U+0020 U+20AC U+0020 U+1D11E
////////////////////////////////////////////////////////////////////////////////
constexpr char32_t kSampleUtf32[] = {
    U'A', U' ', U'\u00E9', U' ', U'\u20AC', U' ', U'\U0001D11E'
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
::testing::AssertionResult bytesEqual(const uint8_t *expected, size_t expectedCount,
                                      const std::vector<uint8_t> &actual)
{
    if (actual.size() != expectedCount)
    {
        return ::testing::AssertionFailure()
            << "byte counts differ: expected " << expectedCount
            << ", actual " << actual.size();
    }

    for (size_t i = 0; i < expectedCount; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure()
                << "byte " << i << " differs: expected 0x"
                << std::hex << uint32_t(expected[i])
                << " actual 0x" << uint32_t(actual[i]);
        }
    }

    return ::testing::AssertionSuccess();
}

////////////////////////////////////////////////////////////////////////////////
// StreamCharacterSink — base class plumbing
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(StreamCharacterSink, NullStreamThrows)
{
    EXPECT_THROW(Utf8StreamCharacterSink(nullptr), ArgumentNullException);
    EXPECT_THROW(Utf16StreamCharacterSink(nullptr), ArgumentNullException);
    EXPECT_THROW(Utf32StreamCharacterSink(nullptr), ArgumentNullException);
}

GTEST_TEST(StreamCharacterSink, DestructorFlushes)
{
    MemoryWriteStream out;

    {
        Utf8StreamCharacterSink sink(&out);
        sink.writeUtf8("hi", 2);
        // sink leaves scope — destructor must flush remaining buffered data.
    }

    ASSERT_EQ(out.Bytes.size(), 2u);
    EXPECT_EQ(out.Bytes[0], uint8_t('h'));
    EXPECT_EQ(out.Bytes[1], uint8_t('i'));
}

GTEST_TEST(StreamCharacterSink, FlushPropagatesToInnerStream)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeUtf8("x", 1);
    EXPECT_FALSE(out.FlushCalled);

    sink.flush();
    EXPECT_TRUE(out.FlushCalled);
    EXPECT_EQ(out.Bytes.size(), 1u);
}

GTEST_TEST(StreamCharacterSink, LargeWriteBypassesBuffer)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    // Write twice the default 32-byte buffer to force the direct-write branch
    // inside StreamCharacterSink::writeBytes.
    constexpr size_t kSize = 64;
    char input[kSize];
    std::memset(input, 'X', kSize);

    sink.writeUtf8(input, kSize);
    sink.flush();

    ASSERT_EQ(out.Bytes.size(), kSize);
    for (size_t i = 0; i < kSize; ++i)
        EXPECT_EQ(out.Bytes[i], uint8_t('X'));
}

////////////////////////////////////////////////////////////////////////////////
// Utf8StreamCharacterSink
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf8StreamCharacterSink, WriteUtf8PassesThroughBytes)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeUtf8(reinterpret_cast<utf8_cptr_t>(kSampleUtf8),
                   kSampleUtf8ByteCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf8, kSampleUtf8ByteCount, out.Bytes));
}

GTEST_TEST(Utf8StreamCharacterSink, WriteUtf16ToUtf8Sink)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeUtf16(kSampleUtf16, kSampleUtf16WordCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf8, kSampleUtf8ByteCount, out.Bytes));
}

GTEST_TEST(Utf8StreamCharacterSink, WriteUtf32ToUtf8Sink)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf8, kSampleUtf8ByteCount, out.Bytes));
}

GTEST_TEST(Utf8StreamCharacterSink, WriteWideToUtf8Sink)
{
#ifdef WCHAR_IS_32BIT
    std::vector<wchar_t> wide;
    wide.reserve(kSampleCodePointCount);
    for (size_t i = 0; i < kSampleCodePointCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf32[i]));
#else
    std::vector<wchar_t> wide;
    wide.reserve(kSampleUtf16WordCount);
    for (size_t i = 0; i < kSampleUtf16WordCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf16[i]));
#endif

    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeWide(wide.data(), wide.size());
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf8, kSampleUtf8ByteCount, out.Bytes));
}

GTEST_TEST(Utf8StreamCharacterSink, EmptyOrNullInputIsNoOp)
{
    MemoryWriteStream out;
    Utf8StreamCharacterSink sink(&out);

    sink.writeUtf8(nullptr, 5);
    sink.writeUtf8("ignored", 0);
    sink.writeUtf16(nullptr, 5);
    sink.writeUtf16(u"x", 0);
    sink.writeUtf32(nullptr, 5);
    sink.writeUtf32(U"x", 0);
    sink.writeWide(nullptr, 5);
    sink.writeWide(L"x", 0);
    sink.flush();

    EXPECT_TRUE(out.Bytes.empty());
}

////////////////////////////////////////////////////////////////////////////////
// Utf16StreamCharacterSink
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf16StreamCharacterSink, WriteUtf16NativeIsDirectCopy)
{
    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::Native);

    sink.writeUtf16(kSampleUtf16, kSampleUtf16WordCount);
    sink.flush();

    // Native byte order: bytes equal the raw char16_t array reinterpreted.
    auto expected = reinterpret_cast<const uint8_t *>(kSampleUtf16);
    EXPECT_TRUE(bytesEqual(expected, sizeof(kSampleUtf16), out.Bytes));
}

GTEST_TEST(Utf16StreamCharacterSink, WriteUtf16LittleEndian)
{
    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeUtf16(kSampleUtf16, kSampleUtf16WordCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Le, std::size(kSampleUtf16Le), out.Bytes));
}

GTEST_TEST(Utf16StreamCharacterSink, WriteUtf16BigEndian)
{
    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::BigEndian);

    sink.writeUtf16(kSampleUtf16, kSampleUtf16WordCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Be, std::size(kSampleUtf16Be), out.Bytes));
}

GTEST_TEST(Utf16StreamCharacterSink, WriteUtf8ToUtf16SinkLE)
{
    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeUtf8(reinterpret_cast<utf8_cptr_t>(kSampleUtf8),
                   kSampleUtf8ByteCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Le, std::size(kSampleUtf16Le), out.Bytes));
}

GTEST_TEST(Utf16StreamCharacterSink, WriteUtf32ToUtf16SinkBE)
{
    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::BigEndian);

    sink.writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Be, std::size(kSampleUtf16Be), out.Bytes));
}

GTEST_TEST(Utf16StreamCharacterSink, WriteWideToUtf16SinkLE)
{
#ifdef WCHAR_IS_32BIT
    std::vector<wchar_t> wide;
    wide.reserve(kSampleCodePointCount);
    for (size_t i = 0; i < kSampleCodePointCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf32[i]));
#else
    std::vector<wchar_t> wide;
    wide.reserve(kSampleUtf16WordCount);
    for (size_t i = 0; i < kSampleUtf16WordCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf16[i]));
#endif

    MemoryWriteStream out;
    Utf16StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeWide(wide.data(), wide.size());
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Le, std::size(kSampleUtf16Le), out.Bytes));
}

////////////////////////////////////////////////////////////////////////////////
// Utf32StreamCharacterSink
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Utf32StreamCharacterSink, WriteUtf32NativeIsDirectCopy)
{
    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::Native);

    sink.writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink.flush();

    auto expected = reinterpret_cast<const uint8_t *>(kSampleUtf32);
    EXPECT_TRUE(bytesEqual(expected, sizeof(kSampleUtf32), out.Bytes));
}

GTEST_TEST(Utf32StreamCharacterSink, WriteUtf32LittleEndian)
{
    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Le, std::size(kSampleUtf32Le), out.Bytes));
}

GTEST_TEST(Utf32StreamCharacterSink, WriteUtf32BigEndian)
{
    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::BigEndian);

    sink.writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Be, std::size(kSampleUtf32Be), out.Bytes));
}

GTEST_TEST(Utf32StreamCharacterSink, WriteUtf8ToUtf32SinkLE)
{
    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeUtf8(reinterpret_cast<utf8_cptr_t>(kSampleUtf8),
                   kSampleUtf8ByteCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Le, std::size(kSampleUtf32Le), out.Bytes));
}

GTEST_TEST(Utf32StreamCharacterSink, WriteUtf16ToUtf32SinkBE)
{
    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::BigEndian);

    sink.writeUtf16(kSampleUtf16, kSampleUtf16WordCount);
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Be, std::size(kSampleUtf32Be), out.Bytes));
}

GTEST_TEST(Utf32StreamCharacterSink, WriteWideToUtf32SinkLE)
{
#ifdef WCHAR_IS_32BIT
    std::vector<wchar_t> wide;
    wide.reserve(kSampleCodePointCount);
    for (size_t i = 0; i < kSampleCodePointCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf32[i]));
#else
    std::vector<wchar_t> wide;
    wide.reserve(kSampleUtf16WordCount);
    for (size_t i = 0; i < kSampleUtf16WordCount; ++i)
        wide.push_back(static_cast<wchar_t>(kSampleUtf16[i]));
#endif

    MemoryWriteStream out;
    Utf32StreamCharacterSink sink(&out, Bin::Endedness::LittleEndian);

    sink.writeWide(wide.data(), wide.size());
    sink.flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Le, std::size(kSampleUtf32Le), out.Bytes));
}

////////////////////////////////////////////////////////////////////////////////
// createCharacterStream — factory
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(CreateCharacterStream, FactoryReturnsUtf8Sink)
{
    MemoryWriteStream out;
    auto sink = createCharacterStream(&out, Utf::Utf8);

    sink->writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink->flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf8, kSampleUtf8ByteCount, out.Bytes));
}

GTEST_TEST(CreateCharacterStream, FactoryReturnsUtf16Sink)
{
    MemoryWriteStream out;
    auto sink = createCharacterStream(&out, Utf::Utf16, Bin::Endedness::LittleEndian);

    sink->writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink->flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf16Le, std::size(kSampleUtf16Le), out.Bytes));
}

GTEST_TEST(CreateCharacterStream, FactoryReturnsUtf32Sink)
{
    MemoryWriteStream out;
    auto sink = createCharacterStream(&out, Utf::Utf32, Bin::Endedness::BigEndian);

    sink->writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink->flush();

    EXPECT_TRUE(bytesEqual(kSampleUtf32Be, std::size(kSampleUtf32Be), out.Bytes));
}

GTEST_TEST(CreateCharacterStream, FactoryReturnsWideSink)
{
    MemoryWriteStream out;
    auto sink = createCharacterStream(&out, Utf::Wide, Bin::Endedness::LittleEndian);

    sink->writeUtf32(kSampleUtf32, kSampleCodePointCount);
    sink->flush();

    // WideStreamCharacterSink is a typedef to either Utf16 or Utf32 sink.
#ifdef WCHAR_IS_32BIT
    EXPECT_TRUE(bytesEqual(kSampleUtf32Le, std::size(kSampleUtf32Le), out.Bytes));
#else
    EXPECT_TRUE(bytesEqual(kSampleUtf16Le, std::size(kSampleUtf16Le), out.Bytes));
#endif
}

GTEST_TEST(CreateCharacterStream, UnknownEncodingThrows)
{
    MemoryWriteStream out;
    auto badEncoding = static_cast<Utf::Encoding>(99);

    EXPECT_THROW(createCharacterStream(&out, badEncoding), ArgumentException);
}

////////////////////////////////////////////////////////////////////////////////
// Round-trip — sink -> bytes -> source -> code points
////////////////////////////////////////////////////////////////////////////////
namespace {

void runRoundTrip(Utf::Encoding encoding, Bin::Endedness byteOrder)
{
    MemoryWriteStream out;
    {
        auto sink = createCharacterStream(&out, encoding, byteOrder);
        sink->writeUtf32(kSampleUtf32, kSampleCodePointCount);
        sink->flush();
    }

    ASSERT_FALSE(out.Bytes.empty());

    MemoryReadStream in(out.Bytes.data(), out.Bytes.size());
    auto src = createStreamCharacterSource(&in, false, encoding, byteOrder);

    char32_t buffer[kSampleCodePointCount * 2] = {};
    size_t got = src->readUtf32(buffer, std::size(buffer));

    ASSERT_EQ(got, kSampleCodePointCount);
    for (size_t i = 0; i < got; ++i)
        EXPECT_EQ(buffer[i], kSampleUtf32[i]) << "code point index " << i;
}

} // nested anonymous namespace

GTEST_TEST(RoundTrip, Utf8)
{
    runRoundTrip(Utf::Utf8, Bin::Endedness::Native);
}

GTEST_TEST(RoundTrip, Utf16LittleEndian)
{
    runRoundTrip(Utf::Utf16, Bin::Endedness::LittleEndian);
}

GTEST_TEST(RoundTrip, Utf16BigEndian)
{
    runRoundTrip(Utf::Utf16, Bin::Endedness::BigEndian);
}

GTEST_TEST(RoundTrip, Utf32LittleEndian)
{
    runRoundTrip(Utf::Utf32, Bin::Endedness::LittleEndian);
}

GTEST_TEST(RoundTrip, Utf32BigEndian)
{
    runRoundTrip(Utf::Utf32, Bin::Endedness::BigEndian);
}

} // Anonymous namespace

}} // namespace Ag::Text
////////////////////////////////////////////////////////////////////////////////
