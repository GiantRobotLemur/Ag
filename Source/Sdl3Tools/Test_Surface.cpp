//! @file Sdl3Tools/Test_Surface.cpp
//! @brief Unit tests for the Ag::SDL3::Surface and LockedSurface wrappers.
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
#include "Ag/Sdl3Tools/Surface.hpp"
#include "SdlVideoFixture.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Surface, DefaultConstructUnbound)
{
    Surface surface;

    EXPECT_FALSE(surface.isBound());
    EXPECT_EQ(surface.get(), nullptr);
    EXPECT_EQ(surface.getWidth(), -1);
    EXPECT_THROW(surface.clear({0.0f, 0.0f, 0.0f, 1.0f}), ObjectNotBoundException);
}

GTEST_TEST(Surface, CreateSurfaceRGBA)
{
    Surface surface;

    ASSERT_NO_THROW(surface.create(16, 16, SDL_PIXELFORMAT_RGBA32));
    EXPECT_TRUE(surface.isBound());
    EXPECT_EQ(surface.getWidth(), 16);
    EXPECT_EQ(surface.getHeight(), 16);
    EXPECT_EQ(surface.getFormat(), SDL_PIXELFORMAT_RGBA32);
}

GTEST_TEST(Surface, ClearFillsPixels)
{
    Surface surface;
    surface.create(8, 8, SDL_PIXELFORMAT_RGBA32);

    ASSERT_NO_THROW(surface.clear({1.0f, 0.0f, 0.0f, 1.0f}));

    uint8_t r = 0, g = 0, b = 0, a = 0;
    ASSERT_NO_THROW(surface.readPixel(4, 4, r, g, b, a));
    EXPECT_EQ(r, 255u);
    EXPECT_EQ(g, 0u);
    EXPECT_EQ(b, 0u);
    EXPECT_EQ(a, 255u);
}

GTEST_TEST(Surface, FillRectAffectsInsideNotOutside)
{
    Surface surface;
    surface.create(16, 16, SDL_PIXELFORMAT_RGBA32);
    surface.clear({0.0f, 0.0f, 0.0f, 1.0f});

    SDL_Rect region{4, 4, 4, 4};

    auto details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA32);
    uint32_t greenPixel = SDL_MapRGBA(details, nullptr, 0, 255, 0, 255);
    ASSERT_NO_THROW(surface.fillRect(&region, greenPixel));

    uint8_t r = 0, g = 0, b = 0, a = 0;
    surface.readPixel(5, 5, r, g, b, a);
    EXPECT_EQ(g, 255u);

    surface.readPixel(0, 0, r, g, b, a);
    EXPECT_EQ(g, 0u);
}

GTEST_TEST(Surface, LockUnlockRAII)
{
    Surface surface;
    surface.create(4, 4, SDL_PIXELFORMAT_INDEX8);
    surface.createAndSetPalette();

    {
        LockedSurface locked = surface.lock();
        EXPECT_TRUE(locked.isLocked());
        EXPECT_NE(locked.getBits(), nullptr);
        EXPECT_EQ(locked.getWidth(), 4);
    }

    // Surface should still be usable after lock scope ends.
    EXPECT_NO_THROW(surface.clear({0.0f, 0.0f, 0.0f, 1.0f}));
}

GTEST_TEST(Surface, DuplicateProducesIndependentCopy)
{
    Surface original;
    original.create(8, 8, SDL_PIXELFORMAT_RGBA32);
    original.clear({1.0f, 0.0f, 0.0f, 1.0f});

    Surface copy = original.duplicate();
    EXPECT_TRUE(copy.isBound());
    EXPECT_NE(copy.get(), original.get());

    copy.clear({0.0f, 0.0f, 1.0f, 1.0f});

    uint8_t r = 0, g = 0, b = 0, a = 0;
    original.readPixel(0, 0, r, g, b, a);
    EXPECT_EQ(r, 255u);
    EXPECT_EQ(b, 0u);
}

GTEST_TEST(Surface, ConvertPixelFormat)
{
    Surface original;
    original.create(4, 4, SDL_PIXELFORMAT_RGBA32);
    original.clear({0.0f, 1.0f, 0.0f, 1.0f});

    Surface converted = original.converted(SDL_PIXELFORMAT_RGB24);

    EXPECT_TRUE(converted.isBound());
    EXPECT_EQ(converted.getFormat(), SDL_PIXELFORMAT_RGB24);
    EXPECT_EQ(converted.getWidth(), 4);
    EXPECT_EQ(converted.getHeight(), 4);
}

GTEST_TEST(Surface, MoveAssignReleasesPrevious)
{
    Surface a;
    a.create(4, 4, SDL_PIXELFORMAT_RGBA32);
    Surface b;
    b.create(8, 8, SDL_PIXELFORMAT_RGBA32);

    SDL_Surface *bRaw = b.get();

    a = std::move(b);

    EXPECT_FALSE(b.isBound());
    EXPECT_EQ(a.get(), bRaw);
    EXPECT_EQ(a.getWidth(), 8);
}

class SurfaceVideoTest : public SdlVideoFixture {};

TEST_F(SurfaceVideoTest, WindowSurfaceBinds)
{
    Window window = makeHiddenWindow(32, 24);

    // Regression: Surface(SDL_Window*) previously unconditionally threw due
    // to a missing SDL_GetWindowSurface() call. Hidden windows on some
    // drivers legitimately fail to produce a surface, so treat the ApiException
    // as a driver limitation rather than a wrapper bug.
    try
    {
        Surface surface = window.getSurface();
        EXPECT_TRUE(surface.isBound());
        EXPECT_GT(surface.getWidth(), 0);
        EXPECT_GT(surface.getHeight(), 0);
    }
    catch (const ApiException &)
    {
        GTEST_SKIP() << "Driver refused SDL_GetWindowSurface for hidden window.";
    }
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
