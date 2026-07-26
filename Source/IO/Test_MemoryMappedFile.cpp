//! @file IO/Test_MemoryMappedFile.cpp
//! @brief The definition of unit tests for the MemoryMappedFile class.
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
#include "Ag/IO/MemoryMappedFile.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(MemoryMappedFile, DefaultConstruct)
{
    MemoryMappedFile specimen;

    EXPECT_FALSE(specimen.isOpen());
    EXPECT_TRUE(specimen.getFileName().isEmpty());
    EXPECT_GT(MemoryMappedFile::getBlockSize(), 0u);
}

GTEST_TEST(MemoryMappedFile, OpenExisting)
{
    // Create a file populated with existing data.
    RandomByteGenerator entropySource(39);
    FileDeleter deleteOnExit(generateTempFileName());
    constexpr size_t FileSize = 32 * 1024;

    createRandomDataFile(entropySource, deleteOnExit.getPath(), FileSize);

    MemoryMappedFile specimen;

    specimen.open(deleteOnExit.getPath(), FileAccess::OpenExisting | FileAccess::Read);

    EXPECT_TRUE(specimen.isOpen());
    EXPECT_TRUE(specimen.getFileName() == deleteOnExit.getPath());

    EXPECT_NO_THROW(specimen.close());
}

GTEST_TEST(MemoryMappedFile, ReadMappedView)
{
    // Create a file populated with existing data.
    RandomByteGenerator entropySource(23);
    FileDeleter deleteOnExit(generateTempFileName());
    constexpr size_t FileSize = 32 * 1024;

    createRandomDataFile(entropySource, deleteOnExit.getPath(), FileSize);

    MemoryMappedFile specimen;

    specimen.open(deleteOnExit.getPath(), FileAccess::OpenExisting | FileAccess::Read);

    EXPECT_TRUE(specimen.isOpen());

    MemoryMappedView view = specimen.createView(0, FileSize);

    ASSERT_NE(view.getPointer(), nullptr);
    EXPECT_EQ(view.getSize(), FileSize);
    EXPECT_EQ(view.getPosition().getOffset(), 0);
    EXPECT_EQ(view.getPosition().getLength(), static_cast<StreamLength>(FileSize));

    // Verify the data.
    uint8_cptr_t source = reinterpret_cast<uint8_cptr_t>(view.getPointer());
    entropySource.reset();

    for (size_t i = 0; i < FileSize; ++i)
    {
        uint8_t next = entropySource();

        // ASSERT rather than EXPECT here as too many errors creates
        // problems for the test runner.
        ASSERT_EQ(next, source[i]) << "Mis-matching bytes at offset #" << i <<
            " (" << static_cast<int>(next) << " vs " << static_cast<int>(source[i]) << ")";
    }
}

GTEST_TEST(MemoryMappedFile, ReadOffsetView)
{
    // Create a file populated with existing data which spans multiple file blocks.
    RandomByteGenerator entropySource(23);
    FileDeleter deleteOnExit(generateTempFileName());
    size_t BlockSize = MemoryMappedFile::getBlockSize();
    size_t FileSize = BlockSize * 3;

    createRandomDataFile(entropySource, deleteOnExit.getPath(), FileSize);

    MemoryMappedFile specimen;

    specimen.open(deleteOnExit.getPath(), FileAccess::OpenExisting | FileAccess::Read);

    EXPECT_TRUE(specimen.isOpen());

    // Get a view of a block in the middle of the file.
    MemoryMappedView view = specimen.createView(1, BlockSize);

    ASSERT_NE(view.getPointer(), nullptr);
    EXPECT_EQ(view.getSize(), BlockSize);
    EXPECT_EQ(view.getPosition().getOffset(),
              static_cast<StreamPosition>(BlockSize));
    EXPECT_EQ(view.getPosition().getLength(),
              static_cast<StreamLength>(BlockSize));

    // Verify the data.
    uint8_cptr_t source = reinterpret_cast<uint8_cptr_t>(view.getPointer());
    entropySource.reset();

    // Skip the first block
    entropySource.skip(BlockSize);

    for (size_t i = 0; i < BlockSize; ++i)
    {
        uint8_t next = entropySource();
        uint8_t test = source[i];

        // ASSERT rather than EXPECT here as too many errors creates
        // problems for the test runner.
        ASSERT_EQ(next, test) << "Mis-matching bytes at offset #" << i <<
            " (" << static_cast<int>(next) << " vs " << static_cast<int>(test) << ")";
    }
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

