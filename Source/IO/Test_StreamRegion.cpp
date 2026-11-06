//! @file IO/Test_StreamRegion.cpp
//! @brief The definition of unit tests for the StreamRegion class.
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

#include "Ag/Core/Exception.hpp"
#include "Ag/IO/ISeekableStream.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(StreamRegion, CreateEmpty)
{
    StreamRegion specimen;

    EXPECT_EQ(specimen.getOffset(), 0);
    EXPECT_EQ(specimen.getLength(), 0);
    EXPECT_EQ(specimen.getEnd(), 0);
}

GTEST_TEST(StreamRegion, ExplicitCreateEmpty)
{
    StreamRegion specimen(0, 0);

    EXPECT_EQ(specimen.getOffset(), 0);
    EXPECT_EQ(specimen.getLength(), 0);
    EXPECT_EQ(specimen.getEnd(), 0);
}

GTEST_TEST(StreamRegion, CreateInitialised)
{
    StreamRegion specimen(256, 512);

    EXPECT_EQ(specimen.getOffset(), 256);
    EXPECT_EQ(specimen.getLength(), 512);
    EXPECT_EQ(specimen.getEnd(), 768);
}

GTEST_TEST(StreamRegion, InvalidConstructionThrows)
{
    EXPECT_THROW(StreamRegion(-1, 16), Ag::ArgumentException);
    EXPECT_THROW(StreamRegion(11, -555), Ag::ArgumentException);
}

GTEST_TEST(StreamRegion, SliceOffsetOnly)
{
    StreamRegion specimen(32, 16);

    StreamRegion sliced = specimen.slice(8);
    EXPECT_EQ(sliced.getOffset(), 32 + 8);
    EXPECT_EQ(sliced.getLength(), 8);
    EXPECT_EQ(sliced.getEnd(), specimen.getEnd());

    // Try slicing off the whole region.
    sliced = specimen.slice(specimen.getLength());
    EXPECT_EQ(sliced.getOffset(), specimen.getEnd());
    EXPECT_EQ(sliced.getLength(), 0);
    EXPECT_EQ(sliced.getEnd(), specimen.getEnd());

    // Try slicing off nothing.
    sliced = specimen.slice(0);
    EXPECT_EQ(sliced.getOffset(), specimen.getOffset());
    EXPECT_EQ(sliced.getLength(), specimen.getLength());
    EXPECT_EQ(sliced.getEnd(), specimen.getEnd());

    // Ensure slicing with invalid values, throws.
    EXPECT_THROW(sliced.slice(-3), Ag::ArgumentException);
    EXPECT_THROW(sliced.slice(specimen.getLength() + 1), Ag::ArgumentException);
}

GTEST_TEST(StreamRegion, SliceOffsetAndLength)
{
    StreamRegion specimen(32, 16);

    StreamRegion sliced = specimen.slice(8, 4);
    EXPECT_EQ(sliced.getOffset(), 32 + 8);
    EXPECT_EQ(sliced.getLength(), 4);
    EXPECT_EQ(sliced.getEnd(), specimen.getOffset() + 8 + 4);

    // Try slicing off the whole region.
    sliced = specimen.slice(specimen.getLength(), 0);
    EXPECT_EQ(sliced.getOffset(), specimen.getEnd());
    EXPECT_EQ(sliced.getLength(), 0);
    EXPECT_EQ(sliced.getEnd(), specimen.getEnd());

    // Try slicing off nothing.
    sliced = specimen.slice(0, specimen.getLength());
    EXPECT_EQ(sliced.getOffset(), specimen.getOffset());
    EXPECT_EQ(sliced.getLength(), specimen.getLength());
    EXPECT_EQ(sliced.getEnd(), specimen.getEnd());

    // Ensure slicing with invalid values, throws.
    EXPECT_THROW(sliced.slice(-3, 4), Ag::ArgumentException);
    EXPECT_THROW(sliced.slice(1, -4), Ag::ArgumentException);
    EXPECT_THROW(sliced.slice(specimen.getLength() + 1, 1), Ag::ArgumentException);
    EXPECT_THROW(sliced.slice(2, specimen.getLength()), Ag::ArgumentException);
}

GTEST_TEST(StreamRegion, Combine)
{
    StreamRegion lhs(32, 16);
    StreamRegion rhs(64, 8);

    StreamRegion result = lhs.combine(rhs);
    EXPECT_EQ(result.getOffset(), 32);
    EXPECT_EQ(result.getLength(), 40);
    EXPECT_EQ(result.getEnd(), 72);

    // Try combining with reversed operands.
    result = rhs.combine(lhs);
    EXPECT_EQ(result.getOffset(), 32);
    EXPECT_EQ(result.getLength(), 40);
    EXPECT_EQ(result.getEnd(), 72);

    // Try overlap below the range.
    StreamRegion overlapLhs(16, 24); // Ends at 40
    result = overlapLhs.combine(lhs);
    EXPECT_EQ(result.getOffset(), 16);
    EXPECT_EQ(result.getLength(), 32);
    EXPECT_EQ(result.getEnd(), 48);

    // Try reversed operands to overlap above the range.
    result = lhs.combine(overlapLhs);
    EXPECT_EQ(result.getOffset(), 16);
    EXPECT_EQ(result.getLength(), 32);
    EXPECT_EQ(result.getEnd(), 48);
}

GTEST_TEST(StreamRegion, MaxLength)
{
    StreamRegion specimen(256, 512);

    // Test with the same length.
    StreamRegion result = specimen.maxLength(specimen.getLength());

    EXPECT_EQ(specimen, result);

    // Test with a shorter length.
    result = specimen.maxLength(32);

    EXPECT_EQ(specimen.getOffset(), result.getOffset());
    EXPECT_EQ(result.getLength(), 32);

    // Test with a longer length.
    result = specimen.maxLength(1024);

    EXPECT_EQ(specimen.getOffset(), result.getOffset());
    EXPECT_EQ(result.getLength(), 512);
}

} // Anonymous namespace

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

