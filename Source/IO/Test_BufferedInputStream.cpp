//! @file IO/Test_BufferedInputStream.cpp
//! @brief The definition of unit tests for the BufferedInputStream class.
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

#include "TestTools.hpp"

#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/BufferedInputStream.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(BufferedInputStream, CreateEmpty)
{
    MemoryStream innerStream;
    BufferedInputStream specimen(&innerStream);

    EXPECT_GT(specimen.getBufferSize(), 0u);
    EXPECT_EQ(specimen.getBufferUsed(), 0u);

    uint8_t buffer[16];

    EXPECT_EQ(specimen.read(buffer, std::size(buffer)), 0u);
    EXPECT_THROW(specimen.write(buffer, std::size(buffer)),
                 NotSupportedException);
}

GTEST_TEST(BufferedInputStream, ReadBuffered)
{
    // Create an underlying stream with some initial data.
    RandomByteGenerator entropySource(99);
    MemoryStream innerStream;

    writeRandomBytes(entropySource, &innerStream, 64);
    innerStream.setPosition(StreamRelative::Beginning, 0);

    // Create a buffered stream on top of the pre-prepared stream.
    BufferedInputStream specimen(&innerStream);

    constexpr size_t SampleSize = 16;
    uint8_t buffer[SampleSize];

    EXPECT_EQ(specimen.read(buffer, SampleSize), SampleSize);

    // Verify some buffer is used, some remains to be read.
    EXPECT_GT(specimen.getBufferUsed(), 0u);
    EXPECT_EQ(specimen.getBufferedBytesRead(), SampleSize);

    // Ensure the bytes we read were the same as those in the inner stream.
    ByteBlock bytes = innerStream.toArray();
    EXPECT_EQ(memcmp(bytes.data(), buffer, SampleSize), 0);
}

GTEST_TEST(BufferedInputStream, RefillBuffer)
{
    RandomByteGenerator entropySource(107);
    MemoryStream innerStream;
    BufferedInputStream specimen(&innerStream);

    // Ensure the underlying stream has more bytes in it than can fit
    // in the buffer.
    constexpr size_t ExtraBytes = 15;

    ByteBlock originalBytes = fillRandomData(entropySource, specimen.getBufferSize() + ExtraBytes);
    innerStream.write(originalBytes.data(), originalBytes.size());

    // Reset the underlying stream so the buffered stream reads from the beginning.
    innerStream.setPosition(StreamRelative::Beginning, 0);

    ByteBlock readBytes;
    readBytes.resize(originalBytes.size());

    // Read a few bytes so the buffer is filled.
    EXPECT_EQ(specimen.read(readBytes.data(), 8), 8u);
    EXPECT_EQ(specimen.getBufferedBytesRead(), 8u);
    EXPECT_GT(specimen.getBufferUsed(), 0u);

    size_t bytesLeftToRead = readBytes.size() - 8;
    EXPECT_EQ(specimen.read(readBytes.data() + 8, bytesLeftToRead), bytesLeftToRead);

    // Ensure there are bytes in the buffer which we have already read.
    EXPECT_GT(specimen.getBufferedBytesRead(), 0u);

    // Ensure there are no more bytes in the buffer to read.
    EXPECT_EQ(specimen.getBufferUsed(), 0u);

    // Ensure the bytes we read were the same as those in the inner stream.
    EXPECT_EQ(memcmp(readBytes.data(), originalBytes.data(), originalBytes.size()), 0);
}

GTEST_TEST(BufferedInputStream, ReadThroughBuffer)
{
    RandomByteGenerator entropySource(107);
    MemoryStream innerStream;
    BufferedInputStream specimen(&innerStream);

    // Ensure the underlying stream has more bytes in it than can fit
    // into two buffers worth.
    size_t TotalByteCount = (specimen.getBufferSize() * 2) + 13;

    ByteBlock originalBytes = fillRandomData(entropySource, TotalByteCount);
    innerStream.write(originalBytes.data(), originalBytes.size());

    // Reset the underlying stream so the buffered stream reads from the beginning.
    innerStream.setPosition(StreamRelative::Beginning, 0);

    ByteBlock readBytes;
    readBytes.resize(originalBytes.size());

    // Read a few bytes so the buffer is filled.
    EXPECT_EQ(specimen.read(readBytes.data(), 8), 8u);
    EXPECT_EQ(specimen.getBufferedBytesRead(), 8u);
    EXPECT_GT(specimen.getBufferUsed(), 0u);

    size_t bytesLeftToRead = readBytes.size() - 8;
    EXPECT_EQ(specimen.read(readBytes.data() + 8, bytesLeftToRead), bytesLeftToRead);

    // Ensure there are no bytes in the buffer because we read the rest,
    // and bypassed the buffer for the rest of the read.
    EXPECT_EQ(specimen.getBufferedBytesRead(), 0u);

    // Ensure there are no more bytes in the buffer to read.
    EXPECT_EQ(specimen.getBufferUsed(), 0u);

    // Ensure the bytes we read were the same as those in the inner stream.
    EXPECT_EQ(memcmp(readBytes.data(), originalBytes.data(), originalBytes.size()), 0);
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

