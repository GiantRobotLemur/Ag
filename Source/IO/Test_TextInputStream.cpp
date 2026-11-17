//! @file IO/Test_TextInputStream.cpp
//! @brief The definition of unit tests for the TextInputStream class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/TextInputStream.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(TextInputStream, ConstructFromEmpty)
{
    uint8_t dummyData = 0;
    MemoryStream empty(&dummyData, 0, true);

    TextInputStream specimen(&empty);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    EXPECT_EQ(specimen.read(buffer, BufferSize), 0u);

    // Try a second time to confirm.
    EXPECT_EQ(specimen.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, RecogniseUTF8ValidBOM)
{
    // Try 2-byte encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0xEF, 0xBB, 0xBF, 0xC2, 0xA3 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF8);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    char32_t utf8Bom = 0xFEFF;

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 2u);
    EXPECT_EQ(buffer[0], utf8Bom);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, RecogniseUTF16LittleEndianValidBOM)
{
    // Try 1-word encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0xFF, 0xFE, 0xA3, 0x00 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF16_LittleEndian);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    char32_t utf8Bom = 0xFEFF;

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 2u);
    EXPECT_EQ(buffer[0], utf8Bom);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, RecogniseUTF16BigEndianValidBOM)
{
    // Try 1-word encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0xFE, 0xFF, 0x00, 0xA3 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF16_BigEndian);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    char32_t utf8Bom = 0xFEFF;

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 2u);
    EXPECT_EQ(buffer[0], utf8Bom);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, RecogniseUTF32LittleEndianValidBOM)
{
    // Try 1-word encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0xFF, 0xFE, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF32_LittleEndian);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    char32_t utf8Bom = 0xFEFF;

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 2u);
    EXPECT_EQ(buffer[0], utf8Bom);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, RecogniseUTF32BigEndianValidBOM)
{
    // Try 1-word encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0x00, 0x00, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0xA3 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF32_BigEndian);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    char32_t utf8Bom = 0xFEFF;

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 2u);
    EXPECT_EQ(buffer[0], utf8Bom);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, InvalidBOM)
{
    // Try 1-word encoding.
    char32_t poundsSterling = 0xA3;

    uint8_t sampleData[] = { 0xC2, 0xA3 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF8);
    options.setBOMExpectation(TextInputOptions::BOMMode::Mandatory);
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with a mandatory BOM ///////////////////////////////////////
    TextInputStream specimen1(&rawInput, options);

    EXPECT_THROW(specimen1.read(buffer, BufferSize), InvalidBOMException);

    // Case 2: Try with an optional BOM ///////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Optional);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    EXPECT_EQ(specimen2.read(buffer, BufferSize), 1);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try with no BOM expected //////////////////////////////////////
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    EXPECT_EQ(specimen3.read(buffer, BufferSize), 1u);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

GTEST_TEST(TextInputStream, InvalidSequence)
{
    // Try 2-byte encoding.
    constexpr char32_t poundsSterling = 0xA3;
    constexpr char32_t substitute = U'@';

    uint8_t sampleData[] = { 0xFF, 0xC2, 0xA3 };
    MemoryStream rawInput(sampleData, std::size(sampleData), true);

    TextInputOptions options;
    options.setPreferredEncoding(TextEncoding::UTF8);
    options.setBOMExpectation(TextInputOptions::BOMMode::Ignored);
    options.setErrorAction(TextInputOptions::ErrorMode::Ignore);
    options.setErrorSubstituteCharacter(substitute);

    constexpr size_t BufferSize = 4;
    char32_t buffer[BufferSize];

    // Case 1: Try with ignoring invalid characters ///////////////////////////
    TextInputStream specimen1(&rawInput, options);

    // We should read the character after the bad byte.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 1u);

    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen1.read(buffer, BufferSize), 0u);

    // Case 2: Try with a substitute character ////////////////////////////////
    options.setErrorAction(TextInputOptions::ErrorMode::Substitute);
    rawInput.setPosition(StreamRelative::Beginning, 0);

    TextInputStream specimen2(&rawInput, options);

    ASSERT_EQ(specimen2.read(buffer, BufferSize), 2);
    EXPECT_EQ(buffer[0], substitute);
    EXPECT_EQ(buffer[1], poundsSterling);

    // Try a second time to confirm.
    EXPECT_EQ(specimen2.read(buffer, BufferSize), 0u);

    // Case 3 - Try throwing an exception /////////////////////////////////////
    options.setErrorAction(TextInputOptions::ErrorMode::Throw);
    rawInput.setPosition(StreamRelative::Beginning, 0);
    TextInputStream specimen3(&rawInput, options);

    EXPECT_THROW(specimen3.read(buffer, BufferSize), InvalidEncodingSequenceException);

    // Try a second time to confirm recovery.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 1u);
    EXPECT_EQ(buffer[0], poundsSterling);

    // Try a third time to confirm.
    EXPECT_EQ(specimen3.read(buffer, BufferSize), 0u);
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

