//! @file Sdl3Tools/Test_DisplayModeSpec.cpp
//! @brief The definition of unit tests for the DisplayModeSpec class.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/GTest_Core.hpp"
#include "Ag/Sdl3Tools/DisplayModeSpec.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DisplayModeSpec, DefaultContruct)
{
    DisplayModeSpec specimen;

    EXPECT_TRUE(specimen.isEmpty());
    EXPECT_FALSE(specimen.hasBpp());
    EXPECT_FALSE(specimen.hasRefreshRate());
    EXPECT_TRUE(specimen.toString().isEmpty());
}

GTEST_TEST(DisplayModeSpec, InitialiseConstructSizeOnly)
{
    DisplayModeSpec specimen(640, 480);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_FALSE(specimen.hasBpp());
    EXPECT_FALSE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 640);
    EXPECT_EQ(specimen.getHeight(), 480);
    EXPECT_LT(specimen.getBpp(), 0);
    EXPECT_LT(specimen.getRefreshRate(), 0);
    EXPECT_STRINGEQC(specimen.toString(), "640x480");
}

GTEST_TEST(DisplayModeSpec, InitialiseConstructSizeAndBpp)
{
    DisplayModeSpec specimen(640, 480, 24);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_TRUE(specimen.hasBpp());
    EXPECT_FALSE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 640);
    EXPECT_EQ(specimen.getHeight(), 480);
    EXPECT_EQ(specimen.getBpp(), 24);
    EXPECT_LT(specimen.getRefreshRate(), 0);
    EXPECT_STRINGEQC(specimen.toString(), "640x480@24");
}

GTEST_TEST(DisplayModeSpec, InitialiseConstructSizeAndRefeshRate)
{
    DisplayModeSpec specimen(1920, 1080, -1, 75);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_FALSE(specimen.hasBpp());
    EXPECT_TRUE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 1920);
    EXPECT_EQ(specimen.getHeight(), 1080);
    EXPECT_LT(specimen.getBpp(), 0);
    EXPECT_EQ(specimen.getRefreshRate(), 75);
    EXPECT_STRINGEQC(specimen.toString(), "1920x1080:75");
}

GTEST_TEST(DisplayModeSpec, InitialiseConstructAll)
{
    DisplayModeSpec specimen(1920, 1080, 32, 75);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_TRUE(specimen.hasBpp());
    EXPECT_TRUE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 1920);
    EXPECT_EQ(specimen.getHeight(), 1080);
    EXPECT_EQ(specimen.getBpp(), 32);
    EXPECT_EQ(specimen.getRefreshRate(), 75);
    EXPECT_STRINGEQC(specimen.toString(), "1920x1080@32:75");
}

GTEST_TEST(DisplayModeSpec, TryParseSizeOnly)
{
    DisplayModeSpec specimen;

    ASSERT_TRUE(specimen.tryParse("1920x1080"));

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_FALSE(specimen.hasBpp());
    EXPECT_FALSE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 1920);
    EXPECT_EQ(specimen.getHeight(), 1080);
    EXPECT_LT(specimen.getBpp(), 0);
    EXPECT_LT(specimen.getRefreshRate(), 0);
    EXPECT_STRINGEQC(specimen.toString(), "1920x1080");
}

GTEST_TEST(DisplayModeSpec, TryParseSizeAndBpp)
{
    DisplayModeSpec specimen;

    ASSERT_TRUE(specimen.tryParse("   1024X768@8   "));

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_TRUE(specimen.hasBpp());
    EXPECT_FALSE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 1024);
    EXPECT_EQ(specimen.getHeight(), 768);
    EXPECT_EQ(specimen.getBpp(), 8);
    EXPECT_LT(specimen.getRefreshRate(), 0);
    EXPECT_STRINGEQC(specimen.toString(), "1024x768@8");
}

GTEST_TEST(DisplayModeSpec, TryParseSizeAndRefeshRate)
{
    DisplayModeSpec specimen;

    ASSERT_TRUE(specimen.tryParse("\t800x600:144   "));

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_FALSE(specimen.hasBpp());
    EXPECT_TRUE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 800);
    EXPECT_EQ(specimen.getHeight(), 600);
    EXPECT_LT(specimen.getBpp(), 0);
    EXPECT_EQ(specimen.getRefreshRate(), 144);
    EXPECT_STRINGEQC(specimen.toString(), "800x600:144");
}

GTEST_TEST(DisplayModeSpec, TryParseAll)
{
    DisplayModeSpec specimen;

    ASSERT_TRUE(specimen.tryParse("320X240@16:120"));

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_TRUE(specimen.hasBpp());
    EXPECT_TRUE(specimen.hasRefreshRate());

    EXPECT_EQ(specimen.getWidth(), 320);
    EXPECT_EQ(specimen.getHeight(), 240);
    EXPECT_EQ(specimen.getBpp(), 16);
    EXPECT_EQ(specimen.getRefreshRate(), 120);
    EXPECT_STRINGEQC(specimen.toString(), "320x240@16:120");
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

