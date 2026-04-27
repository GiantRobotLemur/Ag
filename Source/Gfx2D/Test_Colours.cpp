//! @file Gfx2D/Test_Colours.cpp
//! @brief The definition of unit tests for functions in the Colours namespace.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>
#include "Ag/GTest_Core.hpp"

#include "Ag/Gfx2D/Colours.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Colours, GetCount)
{
    EXPECT_GT(Colours::getNamedColourCount(), 10);
}

GTEST_TEST(Colours, GetDisplayName)
{
    Colours::Index count = Colours::getNamedColourCount();

    for (Colours::Index i = 0; i < count; ++i)
    {
        string_cref_t colourName = Colours::getDisplayName(i);

        EXPECT_FALSE(colourName.isEmpty());
    }

    EXPECT_THROW(Colours::getDisplayName(count), IndexOutOfRangeException);
}

GTEST_TEST(Colours, GetValue)
{
    Colours::Index count = Colours::getNamedColourCount();

    for (Colours::Index i = 0; i < count; ++i)
    {
        EXPECT_NO_THROW(Colours::getValue(i));
    }

    EXPECT_THROW(Colours::getDisplayName(count), IndexOutOfRangeException);
}

GTEST_TEST(Colours, GetColourByName)
{
    Colours::Index count = Colours::getNamedColourCount();
    Colours::Index colourID;

    for (Colours::Index i = 0; i < count; ++i)
    {
        string_cref_t colourName = Colours::getDisplayName(i);
        String lowerName = colourName.toLower();

        EXPECT_TRUE(Colours::tryGetColourByName(lowerName, colourID));
        EXPECT_EQ(colourID, i);
    }

    EXPECT_FALSE(Colours::tryGetColourByName("MistyBuff", colourID));
    EXPECT_FALSE(Colours::tryGetColourByName("VomitGreen", colourID));
    EXPECT_FALSE(Colours::tryGetColourByName("DysenteryBrown", colourID));
    EXPECT_FALSE(Colours::tryGetColourByName("HearingAidBeige", colourID));
}

GTEST_TEST(Colours, GetColourByValue)
{
    Colours::Index colourID;

    ASSERT_TRUE(Colours::tryGetColourByValue(colourID, 0xFF, 0, 0));
    EXPECT_STRINGEQC(Colours::getDisplayName(colourID), "Red");
    EXPECT_EQ(Colours::getValue(colourID), Colours::Red);

    ASSERT_TRUE(Colours::tryGetColourByValue(colourID, 0, 0xFF, 0));
    EXPECT_STRINGEQC(Colours::getDisplayName(colourID), "Lime");
    EXPECT_EQ(Colours::getValue(colourID), Colours::Lime);

    ASSERT_TRUE(Colours::tryGetColourByValue(colourID, 0, 0, 0xFF));
    EXPECT_STRINGEQC(Colours::getDisplayName(colourID), "Blue");
    EXPECT_EQ(Colours::getValue(colourID), Colours::Blue);

    ASSERT_TRUE(Colours::tryGetColourByValue(colourID, 0, 0, 0));
    EXPECT_STRINGEQC(Colours::getDisplayName(colourID), "Black");
    EXPECT_EQ(Colours::getValue(colourID), Colours::Black);

    ASSERT_TRUE(Colours::tryGetColourByValue(colourID, 0xFF, 0xFF, 0xFF));
    EXPECT_STRINGEQC(Colours::getDisplayName(colourID), "White");
    EXPECT_EQ(Colours::getValue(colourID), Colours::White);
}

} // Anonymous namespace

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

