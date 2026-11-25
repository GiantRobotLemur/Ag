//! @file IO/Test_TextOutputStream.cpp
//! @brief The definition of unit tests for the TextOutputStream class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/TextOutputStream.hpp"

namespace Ag {
namespace IO {

namespace {

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
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
class DebugMemoryStream : public MemoryStream
{
private:
    bool _isFlushed = false;
public:
    DebugMemoryStream() = default;

    // Accessors
    bool isFlushed() const { return _isFlushed; }

    // Overrides
    virtual void flush() override
    {
        _isFlushed = true;
        MemoryStream::flush();
    }
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

TextOutputOptions getUtf8MemoryOptions()
{
    TextOutputOptions options;
    options.setEncodingFailureAction(TextOutputOptions::ErrorMode::Throw);
    options.setErrorAction(TextOutputOptions::ErrorMode::Throw);
    options.setOutputEncoding(TextEncoding::UTF8);
    options.enableNewlineProcessing(false);
    options.enableWriteBOM(false);

    return options;
}

TextOutputOptions getUtf32MemoryOptions()
{
    TextOutputOptions options;
    options.setEncodingFailureAction(TextOutputOptions::ErrorMode::Throw);
    options.setErrorAction(TextOutputOptions::ErrorMode::Throw);
    options.setOutputEncoding(TextEncodings::UTF32_Native);
    options.enableNewlineProcessing(false);
    options.enableWriteBOM(false);

    return options;
}

////////////////////////////////////////////////////////////////////////////////
// TestOuputStream — base class plumbing
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(TestOuputStream, NullStreamThrows)
{
    IStreamUPtr uptr;

    EXPECT_THROW(TextOutputStream(nullptr), ArgumentNullException);
    EXPECT_THROW(TextOutputStream(std::move(uptr)), ArgumentNullException);
}

GTEST_TEST(TestOuputStream, DestructorFlushes)
{
    MemoryStream out;

    {
        TextOutputStream sink(&out, getUtf32MemoryOptions());
        sink.write(U"hi", 2);

        // sink leaves scope — destructor must flush remaining buffered data.
    }

    ByteBlock bytes = out.toArray();
    utf32_cptr_t characters = reinterpret_cast<utf32_cptr_t>(bytes.data());

    ASSERT_EQ(bytes.size(), sizeof(char32_t) * 2);
    EXPECT_EQ(characters[0], U'h');
    EXPECT_EQ(characters[1], U'i');
}

GTEST_TEST(TestOuputStream, FlushPropagatesToInnerStream)
{
    DebugMemoryStream out;
    TextOutputStream sink(&out, getUtf32MemoryOptions());

    sink.write(U"x", 1);
    EXPECT_FALSE(out.isFlushed());

    sink.flush();
    EXPECT_TRUE(out.isFlushed());

    ByteBlock bytes = out.toArray();
    EXPECT_EQ(bytes.size(), sizeof(char32_t) * 1);
}

GTEST_TEST(TestOuputStream, LargeWriteBypassesBuffer)
{
    MemoryStream out;
    TextOutputStream sink(&out, getUtf32MemoryOptions());

    // Write twice the default 32-byte buffer to force the direct-write branch
    // inside TestOuputStream::writeBytes.
    constexpr size_t kSize = 64;
    char32_t input[kSize];
    std::fill_n(input, kSize, U'X');

    sink.write(input, kSize);
    sink.flush();

    ByteBlock bytes = out.toArray();

    ASSERT_EQ(bytes.size(), sizeof(char32_t) * kSize);

    utf32_cptr_t characters = reinterpret_cast<utf32_cptr_t>(bytes.data());

    for (size_t i = 0; i < kSize; ++i)
    {
        EXPECT_EQ(characters[i], U'X');
    }
}

//////////////////////////////////////////////////////////////////////////////////
//// TestOuputStream - Test character set conversions.
//////////////////////////////////////////////////////////////////////////////////
class TextOutputStreamConversion : public ::testing::TestWithParam<TextEncoding>
{
public:
    static uint8_cptr_t getSampleData(TextEncoding encoding, size_t &byteCount)
    {
        uint8_cptr_t sampleData;

        switch (encoding)
        {
        case TextEncoding::UTF8:
            sampleData = kSampleUtf8;
            byteCount = std::size(kSampleUtf8);
            break;

        case TextEncoding::UTF16_LittleEndian:
            sampleData = kSampleUtf16Le;
            byteCount = std::size(kSampleUtf16Le);
            break;

        case TextEncoding::UTF16_BigEndian:
            sampleData = kSampleUtf16Be;
            byteCount = std::size(kSampleUtf16Be);
            break;

        case TextEncoding::UTF32_LittleEndian:
            sampleData = kSampleUtf32Le;
            byteCount = std::size(kSampleUtf32Le);
            break;

        case TextEncoding::UTF32_BigEndian:
            sampleData = kSampleUtf32Be;
            byteCount = std::size(kSampleUtf32Be);
            break;

        default:
            sampleData = nullptr;
            byteCount = 0;
        }

        return sampleData;
    }
};

TEST_P(TextOutputStreamConversion, ConvertFromUTF32)
{
    TextEncoding outputEncoding = GetParam();

    size_t inputSize, outputSize;
    utf32_cptr_t inputData = reinterpret_cast<utf32_cptr_t>(getSampleData(TextEncodings::UTF32_Native, inputSize));
    uint8_cptr_t outputData = getSampleData(outputEncoding, outputSize);

    TextOutputOptions options = getUtf8MemoryOptions();
    options.setOutputEncoding(outputEncoding);

    MemoryStream buffer;

    {
        TextOutputStream specimen(&buffer, options);

        specimen.write(inputData, inputSize / sizeof(char32_t));
    }

    ByteBlock bytes = buffer.toArray();

    ASSERT_EQ(bytes.size(), outputSize);
    EXPECT_TRUE(std::equal(outputData, outputData + outputSize, bytes.begin()));
}

INSTANTIATE_TEST_SUITE_P(ConvertFromUTF32,
                         TextOutputStreamConversion,
                         testing::Values(TextEncoding::UTF8,
                                         TextEncoding::UTF16_LittleEndian,
                                         TextEncoding::UTF16_BigEndian,
                                         TextEncoding::UTF32_LittleEndian,
                                         TextEncoding::UTF32_BigEndian));

TEST_P(TextOutputStreamConversion, ConvertFromUTF16)
{
    TextEncoding outputEncoding = GetParam();

    size_t inputSize, outputSize;
    utf16_cptr_t inputData = reinterpret_cast<utf16_cptr_t>(getSampleData(TextEncodings::UTF16_Native, inputSize));
    uint8_cptr_t outputData = getSampleData(outputEncoding, outputSize);

    TextOutputOptions options = getUtf8MemoryOptions();
    options.setOutputEncoding(outputEncoding);

    MemoryStream buffer;

    {
        TextOutputStream specimen(&buffer, options);

        specimen.write(inputData, inputSize / sizeof(char16_t));
    }

    ByteBlock bytes = buffer.toArray();

    ASSERT_EQ(bytes.size(), outputSize);
    EXPECT_TRUE(std::equal(outputData, outputData + outputSize, bytes.begin()));
}

INSTANTIATE_TEST_SUITE_P(ConvertFromUTF16,
                         TextOutputStreamConversion,
                         testing::Values(TextEncoding::UTF8,
                                         TextEncoding::UTF16_LittleEndian,
                                         TextEncoding::UTF16_BigEndian,
                                         TextEncoding::UTF32_LittleEndian,
                                         TextEncoding::UTF32_BigEndian));

TEST_P(TextOutputStreamConversion, ConvertFromUTF8)
{
    TextEncoding outputEncoding = GetParam();

    size_t inputSize, outputSize;
    utf8_cptr_t inputData = reinterpret_cast<utf8_cptr_t>(getSampleData(TextEncoding::UTF8, inputSize));
    uint8_cptr_t outputData = getSampleData(outputEncoding, outputSize);

    TextOutputOptions options = getUtf8MemoryOptions();
    options.setOutputEncoding(outputEncoding);

    MemoryStream buffer;

    {
        TextOutputStream specimen(&buffer, options);

        specimen.write(inputData, inputSize);
    }

    ByteBlock bytes = buffer.toArray();

    ASSERT_EQ(bytes.size(), outputSize);
    EXPECT_TRUE(std::equal(outputData, outputData + outputSize, bytes.begin()));
}

INSTANTIATE_TEST_SUITE_P(ConvertFromUTF8,
                         TextOutputStreamConversion,
                         testing::Values(TextEncoding::UTF8,
                                         TextEncoding::UTF16_LittleEndian,
                                         TextEncoding::UTF16_BigEndian,
                                         TextEncoding::UTF32_LittleEndian,
                                         TextEncoding::UTF32_BigEndian));


TEST_P(TextOutputStreamConversion, ConvertFromWide)
{
    TextEncoding outputEncoding = GetParam();

    size_t inputSize, outputSize;
    wchar_cptr_t inputData = reinterpret_cast<wchar_cptr_t>(getSampleData(TextEncodings::Wide_Native, inputSize));
    uint8_cptr_t outputData = getSampleData(outputEncoding, outputSize);

    TextOutputOptions options = getUtf8MemoryOptions();
    options.setOutputEncoding(outputEncoding);

    MemoryStream buffer;

    {
        TextOutputStream specimen(&buffer, options);

        specimen.write(inputData, inputSize / sizeof(wchar_t));
    }

    ByteBlock bytes = buffer.toArray();

    ASSERT_EQ(bytes.size(), outputSize);
    EXPECT_TRUE(std::equal(outputData, outputData + outputSize, bytes.begin()));
}

INSTANTIATE_TEST_SUITE_P(ConvertFromWide,
                         TextOutputStreamConversion,
                         testing::Values(TextEncoding::UTF8,
                                         TextEncoding::UTF16_LittleEndian,
                                         TextEncoding::UTF16_BigEndian,
                                         TextEncoding::UTF32_LittleEndian,
                                         TextEncoding::UTF32_BigEndian));

} // Anonymous namespace

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////



} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

