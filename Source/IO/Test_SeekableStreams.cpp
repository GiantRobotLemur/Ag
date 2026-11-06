//! @file IO/Test_SeekableStreams.cpp
//! @brief The definition of unit tests for various ISeekableStream
//! implementations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <random>

#include <gtest/gtest.h>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/FsPath.hpp"
#include "Ag/Core/FsDirectory.hpp"
#include "Ag/Core/Utils.hpp"

#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/SeekableFileStream.hpp"

#include "TestTools.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
class SeekableFileHarness
{
private:
    // Internal Fields
    Fs::Path _tempFilePath;
public:
    SeekableFileHarness()
    {
        _tempFilePath = generateTempFileName();
    }

    ~SeekableFileHarness()
    {
        // Ensure the temporary file is deleted.
        Fs::Entry tempFile(_tempFilePath);

        if (tempFile.exists())
            tempFile.remove(/* reportError = */ false);
    }

    ISeekableStreamUPtr createNew()
    {
        auto stream = SeekableFileStream::open(_tempFilePath,
                                               FileAccess::ReadWrite |
                                               FileAccess::CreateAlways);

        return stream;
    }

    ISeekableStreamUPtr createExisting(size_t dataSize, bool isReadOnly)
    {
        RandomByteGenerator entropySource(43);

        createRandomDataFile(entropySource, _tempFilePath, dataSize);

        FileAccessBits accessBits = FileAccess::OpenExisting;
        accessBits |= isReadOnly ? FileAccess::Read : FileAccess::ReadWrite;

        return SeekableFileStream::open(_tempFilePath, accessBits);
    }
};

class SeekableBufferHarness
{
private:
    // Internal Fields
public:
    SeekableBufferHarness()
    {
    }

    ~SeekableBufferHarness()
    {
    }

    ISeekableStreamUPtr createNew()
    {
        return ISeekableStreamUPtr(new MemoryStream());
    }

    ISeekableStreamUPtr createExisting(size_t dataSize, bool isReadOnly)
    {
        if (dataSize == 0)
            return ISeekableStreamUPtr(new MemoryStream());

        RandomByteGenerator entropySource(43);
        ByteBlock randomData = fillRandomData(entropySource, dataSize);

        return ISeekableStreamUPtr(new MemoryStream(randomData.data(),
                                                    randomData.size(),
                                                    isReadOnly));
    }
};

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class SeekableStream : public testing::Test
{
public:
    T _harness;
};

using SeekableStreamTestHarnesses = ::testing::Types<SeekableFileHarness, SeekableBufferHarness>;
TYPED_TEST_SUITE(SeekableStream, SeekableStreamTestHarnesses);

TYPED_TEST(SeekableStream, CreateEmpty)
{
    ISeekableStreamUPtr stream = this->_harness.createNew();

    EXPECT_EQ(stream->getPosition(), 0);
}

TYPED_TEST(SeekableStream, WriteToEmpty)
{
    ISeekableStreamUPtr stream = this->_harness.createNew();

    constexpr uint32_t sampleData = 0xDEADBEEF;

    EXPECT_EQ(stream->getPosition(), 0);
    EXPECT_EQ(stream->write(&sampleData, sizeof(sampleData)), sizeof(sampleData));
    EXPECT_EQ(stream->getPosition(), static_cast<StreamPosition>(sizeof(sampleData)));
}

TYPED_TEST(SeekableStream, SeekAndReReadToEmpty)
{
    ISeekableStreamUPtr stream = this->_harness.createNew();

    constexpr uint32_t sampleData = 0xCAFEBABE;

    EXPECT_EQ(stream->getPosition(), 0);
    EXPECT_EQ(stream->write(&sampleData, sizeof(sampleData)), sizeof(sampleData));
    EXPECT_EQ(stream->getPosition(), static_cast<StreamPosition>(sizeof(sampleData)));

    EXPECT_EQ(stream->setPosition(StreamRelative::Beginning, 0), 0);
    EXPECT_EQ(stream->getPosition(), 0);

    uint32_t readData = 0;
    EXPECT_EQ(stream->read(&readData, sizeof(readData)), sizeof(readData));
    EXPECT_EQ(readData, sampleData);
}

TYPED_TEST(SeekableStream, ReReadExisting)
{
    // Create a stream with existing data.
    ISeekableStreamUPtr stream = this->_harness.createExisting(768, false);

    // Move into the stream.
    EXPECT_EQ(stream->setPosition(StreamRelative::Beginning, 512), 512);

    // Read some data.
    ByteBlock readBytes;
    readBytes.resize(64);

    EXPECT_EQ(stream->read(readBytes.data(), readBytes.size()), readBytes.size());

    // Reposition back to the position previously read from.
    EXPECT_EQ(stream->setPosition(StreamRelative::Current, -64), 512);

    // Read the bytes again.
    ByteBlock reReadBytes;
    reReadBytes.resize(readBytes.size());

    EXPECT_EQ(stream->read(reReadBytes.data(), reReadBytes.size()), reReadBytes.size());

    // Compare the two sets of bytes.
    EXPECT_TRUE(std::equal(readBytes.begin(), readBytes.end(), reReadBytes.begin()));
}

TYPED_TEST(SeekableStream, SeekEndRelative)
{
    // Create a stream with existing data.
    ISeekableStreamUPtr stream = this->_harness.createExisting(768, false);

    // Move into the stream.
    EXPECT_EQ(stream->setPosition(StreamRelative::End, -512), 256);

    // Read some data.
    ByteBlock readBytes;
    readBytes.resize(64);

    EXPECT_EQ(stream->read(readBytes.data(), readBytes.size()), readBytes.size());

    // Reposition back to the position previously read from.
    EXPECT_EQ(stream->setPosition(StreamRelative::Beginning, 256), 256);

    // Read the bytes again.
    ByteBlock reReadBytes;
    reReadBytes.resize(readBytes.size());

    EXPECT_EQ(stream->read(reReadBytes.data(), reReadBytes.size()), reReadBytes.size());

    // Compare the two sets of bytes.
    EXPECT_TRUE(std::equal(readBytes.begin(), readBytes.end(), reReadBytes.begin()));
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

