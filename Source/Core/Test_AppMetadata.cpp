//! @file Core/Test_AppMetadata.cpp
//! @brief The definition of unit tests for the AppMetadata structure.
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

#include "Ag/Core/App.hpp"
#include "Ag/Core/Utf.hpp"

// A specially generated AppVersion.hpp created for testing purposes.
#include "AppVersion.hpp"

namespace Ag {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
const int TestMajor = APP_MAJOR_VERSION;
const int TestMinor = APP_MINOR_VERSION;
const int TestRevision = APP_REVISION;
const int TestBuild = APP_BUILD;

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(AppMetadata, Version)
{
    // Test individually specified values.
    EXPECT_EQ(TestMajor, 1);
    EXPECT_EQ(TestMinor, 2);
    EXPECT_EQ(TestRevision, 3);
    EXPECT_EQ(TestBuild, 4);

    std::string_view versionText(APP_VERSION_TEXT);

    EXPECT_GT(versionText.length(), 0u);
}

GTEST_TEST(AppMetadata, InfoFields)
{
    std::string_view name(APP_NAME);
    std::string_view displayName(APP_DISPLAY_NAME);
    std::string_view company(APP_COMPANY);
    std::string_view author(APP_AUTHOR);
    std::string_view copyright(APP_COPYRIGHT);
    std::string_view productName(APP_PRODUCT_NAME);
    std::string_view description(APP_DESCRIPTION);

    EXPECT_GT(name.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(name.data()));

    EXPECT_GT(displayName.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(displayName.data()));

    EXPECT_GT(company.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(company.data()));

    EXPECT_GT(author.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(author.data()));

    EXPECT_GT(copyright.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(copyright.data()));

    EXPECT_GT(productName.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(productName.data()));

    EXPECT_GT(description.length(), 0u);
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(description.data()));
}

GTEST_TEST(AppMetadata, Construction)
{
    AppMetadata specimen = MAKE_APP_METADATA();

    EXPECT_EQ(specimen.AppVersion.getMajor(), 1);
    EXPECT_EQ(specimen.AppVersion.getMinor(), 2);
    EXPECT_EQ(specimen.AppVersion.getRevision(), 3);
    EXPECT_EQ(specimen.AppVersion.getPatch(), 4);

    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.AppName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.DisplayName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.CompanyName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Author.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Copyright.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.ProductName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Description.data()));
}

GTEST_TEST(AppMetadata, ConstructionWithBuildNo)
{
    constexpr int BuildNo = 69;
    AppMetadata specimen = MAKE_APP_METADATA_EX(69);

    EXPECT_EQ(specimen.AppVersion.getMajor(), 1);
    EXPECT_EQ(specimen.AppVersion.getMinor(), 2);
    EXPECT_EQ(specimen.AppVersion.getRevision(), 3);
    EXPECT_EQ(specimen.AppVersion.getPatch(), BuildNo);

    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.AppName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.DisplayName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.CompanyName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Author.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Copyright.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.ProductName.data()));
    EXPECT_FALSE(Ag::Utf::isNullOrEmpty(specimen.Description.data()));
}

} // Anonymous namespace

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

