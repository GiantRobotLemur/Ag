//! @file Sdl3Tools/Test_Window.cpp
//! @brief Unit tests for the Ag::SDL3::Window wrapper.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Core.hpp"
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/Window.hpp"
#include "SdlVideoFixture.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Window, DefaultConstructUnbound)
{
    Window window;

    EXPECT_FALSE(window.isBound());
    EXPECT_EQ(window.get(), nullptr);
    EXPECT_EQ(window.getID(), 0u);
    EXPECT_EQ(window.getFlags(), 0u);
    EXPECT_THROW(window.getDisplayID(), ObjectNotBoundException);
    EXPECT_THROW(window.setTitle("nope"), ObjectNotBoundException);
}

GTEST_TEST(Window, ReleaseIsIdempotentOnUnbound)
{
    Window window;

    EXPECT_NO_THROW(window.release());
    EXPECT_NO_THROW(window.release());
    EXPECT_FALSE(window.isBound());
}

class WindowVideoTest : public SdlVideoFixture {};

TEST_F(WindowVideoTest, CreateHidden)
{
    Window window;

    ASSERT_NO_THROW(window.create("Hidden", 64, 48, SDL_WINDOW_HIDDEN));
    EXPECT_TRUE(window.isBound());
    EXPECT_NE(window.getID(), 0u);
    EXPECT_TRUE(window.isOwned());
}

TEST_F(WindowVideoTest, TitleRoundTrip)
{
    Window window = makeHiddenWindow();

    ASSERT_NO_THROW(window.setTitle("New Title"));
    EXPECT_STREQ(window.getTitle(), "New Title");
}

TEST_F(WindowVideoTest, SizeGetter)
{
    Window window = makeHiddenWindow(96, 72);
    int w = 0, h = 0;

    ASSERT_NO_THROW(window.getSize(w, h));
    EXPECT_GT(w, 0);
    EXPECT_GT(h, 0);
}

TEST_F(WindowVideoTest, MoveConstructTransfersOwnership)
{
    Window a = makeHiddenWindow();
    SDL_WindowID id = a.getID();

    Window b(std::move(a));

    EXPECT_FALSE(a.isBound());
    EXPECT_TRUE(b.isBound());
    EXPECT_EQ(b.getID(), id);
}

TEST_F(WindowVideoTest, MoveAssignReleasesPrevious)
{
    Window a = makeHiddenWindow(64, 48);
    Window b = makeHiddenWindow(128, 96);

    SDL_WindowID idB = b.getID();

    a = std::move(b);

    EXPECT_FALSE(b.isBound());
    EXPECT_TRUE(a.isBound());
    EXPECT_EQ(a.getID(), idB);
}

TEST_F(WindowVideoTest, PropertySetIsReadable)
{
    Window window = makeHiddenWindow();

    EXPECT_NO_THROW((void)window.getProperties());
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
