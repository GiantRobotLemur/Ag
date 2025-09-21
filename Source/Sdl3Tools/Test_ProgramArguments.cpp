//! @file Sdl3Tools/Test_ProgramArguments.cpp
//! @brief The definition of unit tests for the Sdl3ProgramArguments class.
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
#include "Ag/Core.hpp"
#include "Ag/Sdl3Tools/ProgramArguments.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
std::wstring createCommandLine()
{
    std::wstring commandLine;
    commandLine.reserve(256);
    commandLine.push_back(L'\"');
    commandLine.append(Fs::Path::getProgramFile().toWideString());
    commandLine.push_back(L'\"');

    return commandLine;
}

void appendQuotedArgument(std::wstring &commandLine, const std::string_view &arg)
{
    if (arg.empty())
        return;

    commandLine.push_back(L' ');
    commandLine.push_back(L'\"');
    Utf::appendToWide(commandLine, arg.data(), arg.length());
    commandLine.push_back(L'\"');
}

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(ProgramArguments, DefaultContruct)
{
    ProgramArguments specimen;

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_TRUE(specimen.getDisplayName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayDriverName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayMode().isEmpty());
}

GTEST_TEST(ProgramArguments, EmptyArguments)
{
    std::wstring commandLine = createCommandLine();
    String error;
    ProgramArguments specimen;

    ASSERT_TRUE(specimen.tryParse(commandLine.c_str(), error));
    ASSERT_TRUE(error.isEmpty());

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_TRUE(specimen.getDisplayName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayDriverName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayMode().isEmpty());
}

GTEST_TEST(ProgramArguments, DisplayModeArgument)
{
    std::wstring commandLine = createCommandLine();
    appendQuotedArgument(commandLine, "--sdl_display_mode");
    appendQuotedArgument(commandLine, "640x480@32");
    String error;
    ProgramArguments specimen;

    ASSERT_TRUE(specimen.tryParse(commandLine.c_str(), error));
    ASSERT_TRUE(error.isEmpty());

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_TRUE(specimen.getDisplayName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayDriverName().isEmpty());
    EXPECT_FALSE(specimen.getDisplayMode().isEmpty());
    EXPECT_EQ(specimen.getDisplayMode().getWidth(), 640);
    EXPECT_EQ(specimen.getDisplayMode().getHeight(), 480);
    EXPECT_EQ(specimen.getDisplayMode().getBpp(), 32);
    EXPECT_FALSE(specimen.getDisplayMode().hasRefreshRate());
}

GTEST_TEST(ProgramArguments, DisplayDriverArgument)
{
    std::wstring commandLine = createCommandLine();
    appendQuotedArgument(commandLine, "--sdl_display_driver");
    appendQuotedArgument(commandLine, "Direct2D");
    String error;
    ProgramArguments specimen;

    ASSERT_TRUE(specimen.tryParse(commandLine.c_str(), error));
    ASSERT_TRUE(error.isEmpty());

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_TRUE(specimen.getDisplayName().isEmpty());
    EXPECT_STRINGEQC(specimen.getDisplayDriverName(), "Direct2D");
    EXPECT_TRUE(specimen.getDisplayMode().isEmpty());
}

GTEST_TEST(ProgramArguments, DisplayNameArgument)
{
    std::wstring commandLine = createCommandLine();
    appendQuotedArgument(commandLine, "--sdl_display_name");
    appendQuotedArgument(commandLine, "AOC Super-Wide");
    String error;
    ProgramArguments specimen;

    ASSERT_TRUE(specimen.tryParse(commandLine.c_str(), error));
    ASSERT_TRUE(error.isEmpty());

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_STRINGEQC(specimen.getDisplayName(), "AOC Super-Wide");
    EXPECT_TRUE(specimen.getDisplayDriverName().isEmpty());
    EXPECT_TRUE(specimen.getDisplayMode().isEmpty());
}

GTEST_TEST(ProgramArguments, AllArguments)
{
    std::wstring commandLine = createCommandLine();
    appendQuotedArgument(commandLine, "--sdl_display_name");
    appendQuotedArgument(commandLine, "Legacy SVGA");
    appendQuotedArgument(commandLine, "--sdl_display_mode");
    appendQuotedArgument(commandLine, "1024x768@24:75");
    appendQuotedArgument(commandLine, "--sdl_display_driver");
    appendQuotedArgument(commandLine, "DirectDraw");

    String error;
    ProgramArguments specimen;

    ASSERT_TRUE(specimen.tryParse(commandLine.c_str(), error));
    ASSERT_TRUE(error.isEmpty());

    EXPECT_FALSE(specimen.hasCommand());
    EXPECT_EQ(specimen.getCommand(), Cli::StandardCommands::NoCommand);
    EXPECT_EQ(specimen.getSDLListObjectType(), SdlObjectType::None);
    EXPECT_STRINGEQC(specimen.getDisplayName(), "Legacy SVGA");
    EXPECT_STRINGEQC(specimen.getDisplayDriverName(), "DirectDraw");
    EXPECT_FALSE(specimen.getDisplayMode().isEmpty());
    EXPECT_EQ(specimen.getDisplayMode().getWidth(), 1024);
    EXPECT_EQ(specimen.getDisplayMode().getHeight(), 768);
    EXPECT_EQ(specimen.getDisplayMode().getBpp(), 24);
    EXPECT_EQ(specimen.getDisplayMode().getRefreshRate(), 75);
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

