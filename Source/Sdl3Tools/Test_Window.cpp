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

TEST_F(WindowVideoTest, SizeAsPointMatchesScalarForm)
{
    Window window = makeHiddenWindow(96, 72);
    int w = 0, h = 0;

    ASSERT_NO_THROW(window.getSize(w, h));

    SDL_Point size = window.getSize();

    EXPECT_EQ(size.x, w);
    EXPECT_EQ(size.y, h);
}

TEST_F(WindowVideoTest, CreateWithPointSizeMatchesScalarForm)
{
    Window window;

    ASSERT_NO_THROW(window.create("Hidden", Point(96, 72), SDL_WINDOW_HIDDEN));
    EXPECT_TRUE(window.isBound());

    SDL_Point size = window.getSize();
    EXPECT_EQ(size.x, 96);
    EXPECT_EQ(size.y, 72);
}

TEST_F(WindowVideoTest, SizeRoundTripsThroughPointOverload)
{
    Window window = makeHiddenWindow(64, 48);

    ASSERT_NO_THROW(window.setSize(Point(128, 96)));

    SDL_Point size = window.getSize();
    EXPECT_EQ(size.x, 128);
    EXPECT_EQ(size.y, 96);
}

TEST_F(WindowVideoTest, PositionRoundTripsThroughPointOverload)
{
    Window window = makeHiddenWindow();

    ASSERT_NO_THROW(window.setPosition(Point(120, 90)));

    int x = 0, y = 0;
    ASSERT_NO_THROW(window.getPosition(x, y));

    SDL_Point position = window.getPosition();
    EXPECT_EQ(position.x, x);
    EXPECT_EQ(position.y, y);
}

TEST_F(WindowVideoTest, MinimumSizeRoundTripsThroughPointOverload)
{
    Window window = makeHiddenWindow();

    ASSERT_NO_THROW(window.setMinimumSize(Point(32, 24)));

    SDL_Point size = window.getMinimumSize();
    EXPECT_EQ(size.x, 32);
    EXPECT_EQ(size.y, 24);
}

TEST_F(WindowVideoTest, MouseRectSetAndClear)
{
    Window window = makeHiddenWindow();
    SDL_Rect rect;

    ASSERT_NO_THROW(window.setMouseRect(Rect(4, 4, 16, 16)));
    ASSERT_TRUE(window.tryGetMouseRect(rect));
    EXPECT_EQ(rect.x, 4);
    EXPECT_EQ(rect.w, 16);

    ASSERT_NO_THROW(window.clearMouseRect());
    EXPECT_FALSE(window.tryGetMouseRect(rect));
}

TEST_F(WindowVideoTest, FullscreenModeResetsToDesktop)
{
    Window window = makeHiddenWindow();
    SDL_DisplayMode mode;

    // A hidden windowed window has no explicit fullscreen mode to begin with.
    EXPECT_FALSE(window.tryGetFullscreenMode(mode));

    ASSERT_NO_THROW(window.resetFullscreenMode());
    EXPECT_FALSE(window.tryGetFullscreenMode(mode));
    EXPECT_EQ(window.getFullscreenMode(), nullptr);
}

// Note: there is no bound-window test for clearHitTest(). The dummy video
// driver used for headless runs does not implement hit testing at all, so
// SDL_SetWindowHitTest() fails whatever it is passed.

GTEST_TEST(Window, NullSemanticsOperationsThrowWhenUnbound)
{
    Window window;

    EXPECT_THROW(window.clearMouseRect(), ObjectNotBoundException);
    EXPECT_THROW(window.resetFullscreenMode(), ObjectNotBoundException);
    EXPECT_THROW(window.clearHitTest(), ObjectNotBoundException);
    EXPECT_THROW(window.getSize(), ObjectNotBoundException);

    SDL_DisplayMode mode;
    EXPECT_FALSE(window.tryGetFullscreenMode(mode));
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
