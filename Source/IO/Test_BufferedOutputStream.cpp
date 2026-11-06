//! @file IO/Test_BufferedOutputStream.cpp
//! @brief The definition of unit tests for the BufferedOutputStream class.
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

#include "TestTools.hpp"

#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/BufferedOutputStream.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(BufferedOutputStream, CreateEmpty)
{
    MemoryStream innerStream;
    BufferedOutputStream specimen(&innerStream);

    EXPECT_GT(specimen.getBufferSize(), 0u);
    EXPECT_EQ(specimen.getBufferUsed(), 0u);
}

GTEST_TEST(BufferedOutputStream, BufferedWriteNoFlush)
{
    RandomByteGenerator entropySource(42);
    MemoryStream innerStream;
    BufferedOutputStream specimen(&innerStream);

    size_t maxBufferedWrite = specimen.getBufferSize() - 1;

    // Verify that nearly filling the buffer, doesn't force a flush.
    EXPECT_EQ(writeRandomBytes(entropySource, &specimen, maxBufferedWrite), maxBufferedWrite);
    EXPECT_EQ(specimen.getBufferUsed(), maxBufferedWrite);
    EXPECT_EQ(innerStream.getPosition(), 0);

    // Now ensure the buffer is overfilled to force a flush.
    EXPECT_EQ(writeRandomBytes(entropySource, &specimen, 2), 2u);
    EXPECT_EQ(innerStream.getPosition(), static_cast<StreamPosition>(specimen.getBufferSize()));
    EXPECT_EQ(specimen.getBufferUsed(), 1u);
}

GTEST_TEST(BufferedOutputStream, WriteThrough)
{
    RandomByteGenerator entropySource(69);
    MemoryStream innerStream;
    BufferedOutputStream specimen(&innerStream);

    ByteBlock randomData;
    std::generate_n(std::back_inserter(randomData),
                    specimen.getBufferSize() + 12,
                    entropySource);

    // Verify that writing a block larger than the buffer just passes through.
    EXPECT_EQ(specimen.write(randomData.data(), randomData.size()), randomData.size());
    EXPECT_EQ(specimen.getBufferUsed(), 0u);
    EXPECT_EQ(innerStream.getPosition(), static_cast<StreamPosition>(randomData.size()));
}

GTEST_TEST(BufferedOutputStream, PartialWriteThrough)
{
    RandomByteGenerator entropySource(34);
    MemoryStream innerStream;
    BufferedOutputStream specimen(&innerStream);

    // Configure so that the data left after the first flush is smaller than the buffer.
    constexpr size_t InitialData = 12;
    constexpr size_t ExtraData = 32;

    ByteBlock randomData;
    std::generate_n(std::back_inserter(randomData),
                    specimen.getBufferSize() + ExtraData,
                    entropySource);

    // Verify writing to a part-filled buffer with a block larger
    // than the buffer flushes with maximum capacity and buffers what is left.
    EXPECT_EQ(writeRandomBytes(entropySource, &specimen, InitialData), InitialData);
    EXPECT_EQ(specimen.getBufferUsed(), InitialData);
    EXPECT_EQ(innerStream.getPosition(), 0);

    // Now write the larger buffer.
    size_t totalData = randomData.size() + InitialData;
    EXPECT_EQ(specimen.write(randomData.data(), randomData.size()), randomData.size());

    // Verify the resultant state.
    EXPECT_EQ(specimen.getBufferUsed(), totalData - specimen.getBufferSize());
    EXPECT_EQ(innerStream.getPosition(), static_cast<StreamPosition>(specimen.getBufferSize()));
}

GTEST_TEST(BufferedOutputStream, PartialWriteThroughEmptyBuffer)
{
    RandomByteGenerator entropySource(12);
    MemoryStream innerStream;
    BufferedOutputStream specimen(&innerStream);

    // Configure so that the data left after the initial flush is larger
    // than the buffer.
    constexpr size_t InitialData = 24;
    size_t ExtraData = (specimen.getBufferSize() * 2) + 32;

    ByteBlock randomData;
    std::generate_n(std::back_inserter(randomData),
                    specimen.getBufferSize() + ExtraData,
                    entropySource);

    // Verify writing to a part-filled buffer with a block larger
    // than the buffer flushes with maximum capacity and buffers what is left.
    EXPECT_EQ(writeRandomBytes(entropySource, &specimen, InitialData), InitialData);
    EXPECT_EQ(specimen.getBufferUsed(), InitialData);
    EXPECT_EQ(innerStream.getPosition(), 0);

    // Now write the larger buffer.
    size_t totalData = randomData.size() + InitialData;
    EXPECT_EQ(specimen.write(randomData.data(), randomData.size()), randomData.size());

    // Verify the buffer is empty and all data has been written to the
    // underlying stream.
    EXPECT_EQ(specimen.getBufferUsed(), 0u);
    EXPECT_EQ(innerStream.getPosition(), static_cast<StreamPosition>(totalData));
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

