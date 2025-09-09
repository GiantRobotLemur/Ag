//! @file Core/Test_Bz2Straem.cpp
//! @brief The definition of unit tests for the Bz2Straem class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>

#include <iterator>
#include <random>

#include <gtest/gtest.h>

#include "Ag/Private/Bz2Stream.hpp"
#include "Ag/Core/CollectionTools.hpp"
#include "Ag/Core/FsPath.hpp"
#include "Ag/Core/Utils.hpp"

namespace Ag {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
class TestBz2Stream : public Bz2Context
{
public:
    std::vector<uint8_t> CompressedData;
    std::vector<uint8_t> DecompressedData;

    // Construction/Destruction
    TestBz2Stream() = default;
    virtual ~TestBz2Stream() = default;

    // Overrides
    virtual void onBz2Error(const char */*bz2Fn*/, int /*errorCode*/) override
    {
        FAIL();
    }

    virtual void onInvalidState(State /*preferredState*/) override
    {
        FAIL();
    }

    virtual void onBytesCompressed(const uint8_t *compressedBytes,
                                   size_t byteCount) override
    {
        std::copy_n(compressedBytes, byteCount, std::back_inserter(CompressedData));
    }
};

std::vector<uint8_t> generateRandomData(size_t byteCount, uint32_t seed)
{
    using EntropyGenerator = std::independent_bits_engine<std::ranlux24_base, 32, uint32_t>;

    EntropyGenerator generator(seed);

    std::vector<uint8_t> data;
    data.reserve(byteCount);
    size_t wordCount = byteCount / 4;
    uint32_t word = 0;
    uint8_t *bytes = reinterpret_cast<uint8_t *>(&word);

    for (size_t i = 0; i < wordCount; ++i)
    {
        word = generator();

        for (uint8_t j = 0; j < 4; ++j)
        {
            data.push_back(bytes[j]);
        }
    }

    word = generator();
    for (size_t i = (wordCount * 4); i < byteCount; ++i)
    {
        data.push_back(bytes[i]);
    }

    return data;
}

void testCompressionAndDecompression(const void *sampleData, size_t sampleSize, bool isRandom)
{
    const uint8_t *originalData = reinterpret_cast<const uint8_t *>(sampleData);
    size_t bytesConsumed = 0;

    // Compress the random data.
    TestBz2Stream specimen;
    specimen.initialiseCompression();
    constexpr size_t BlockSize = 512;

    while (bytesConsumed < sampleSize)
    {
        size_t blockSize = std::min(sampleSize - bytesConsumed, BlockSize);
        size_t bytesSent = specimen.compress(originalData + bytesConsumed, blockSize);

        ASSERT_EQ(bytesSent, blockSize);
        bytesConsumed += bytesSent;
    }

    specimen.finishCompression();

    // Verify data was compressed.
    ASSERT_FALSE(specimen.CompressedData.empty());

    // NOTE: With pseudo-random data, this assertion doesn't always hold.
    if (isRandom == false)
        EXPECT_LT(specimen.CompressedData.size(), sampleSize);

    // Decompress the previously compressed data.
    specimen.initialiseDecompression();
    bytesConsumed = 0;
    auto &decompressionBuffer = specimen.getDecompressionBuffer();

    while (bytesConsumed < specimen.CompressedData.size())
    {
        // Transfer the decompressed data from the internal buffer.
        size_t outputByteCount = 0;

        if (decompressionBuffer.canProduce())
        {
            auto bufferedData = decompressionBuffer.getConsumable(outputByteCount);

            std::copy_n(bufferedData, outputByteCount,
                        std::back_inserter(specimen.DecompressedData));
            decompressionBuffer.consume(outputByteCount);
        }

        // Try to decompress some more data.
        size_t blockSize = std::min(specimen.CompressedData.size() - bytesConsumed, BlockSize);

        size_t bytesSent = specimen.decompress(specimen.CompressedData.data() + bytesConsumed,
                                               blockSize);

        ASSERT_GT(bytesSent + outputByteCount, 0);
        bytesConsumed += bytesSent;
    }

    // Consume all outstanding bytes
    while (specimen.finishDecompression() == false)
    {
        // Transfer the decompressed data from the internal buffer.
        size_t outputByteCount = 0;

        if (decompressionBuffer.canProduce())
        {
            auto bufferedData = decompressionBuffer.getConsumable(outputByteCount);

            std::copy_n(bufferedData, outputByteCount,
                        std::back_inserter(specimen.DecompressedData));
            decompressionBuffer.consume(outputByteCount);
        }
    }

    // Verify the data made the round trip being compressed.
    ASSERT_EQ(specimen.DecompressedData.size(), sampleSize);

    ASSERT_TRUE(std::equal(originalData, originalData + sampleSize,
                           specimen.DecompressedData.begin()));
}

std::vector<uint8_t> readWholeFile(const Ag::Fs::Path &filePath)
{
    Ag::String filePathText = filePath.toString();
    Ag::String errorMessage;
    FILE *fp = nullptr;

    std::vector<uint8_t> fileData;

    if (Ag::tryOpenFile(filePathText, "rb", fp, errorMessage))
    {
        StdFilePtr fileHandle(fp);

        fseek(fp, 0, SEEK_END);
        auto length = ftell(fp);
        rewind(fp);

        fileData.resize(static_cast<size_t>(length));

        size_t actualSize = fread(fileData.data(), 1, fileData.size(), fp);

        fileData.resize(actualSize);
    }

    return fileData;
}

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Bz2Stream, CompressionAndDecompressionRandomData)
{
    constexpr size_t DataSize = 4096;
    std::vector<uint8_t> originalData = generateRandomData(DataSize, 42);
    ASSERT_EQ(originalData.size(), DataSize);

    testCompressionAndDecompression(originalData.data(), originalData.size(), true);
}

GTEST_TEST(Bz2Stream, CompressionAndDecompressionTextData)
{
    // Read the symbol data.
    Ag::Fs::Path filePath(Ag::Fs::Path::getProgramFile().changeFileExtension("txt"));

    std::vector<uint8_t> symbolData = readWholeFile(Ag::Fs::Path(filePath));

    ASSERT_FALSE(symbolData.empty());

    testCompressionAndDecompression(symbolData.data(), symbolData.size(), false);
}

GTEST_TEST(Bz2Stream, CompressionAndDecompressionBinaryData)
{
    // Read the program binary.
    std::vector<uint8_t> programData = readWholeFile(Ag::Fs::Path::getProgramFile());

    ASSERT_FALSE(programData.empty());

    testCompressionAndDecompression(programData.data(), programData.size(), false);
}

} // Anonymous namespace

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

