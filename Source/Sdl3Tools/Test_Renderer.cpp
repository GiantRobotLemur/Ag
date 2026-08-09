//! @file Sdl3Tools/Test_Renderer.cpp
//! @brief Unit tests for the Ag::SDL3::Renderer wrapper.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstring>

#include <gtest/gtest.h>

#include "Ag/Core.hpp"
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/Renderer.hpp"
#include "Ag/Sdl3Tools/Surface.hpp"
#include "Ag/Sdl3Tools/Texture.hpp"
#include "Ag/Sdl3Tools/Window.hpp"
#include "SdlVideoFixture.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Renderer, DefaultConstructUnbound)
{
    Renderer renderer;

    EXPECT_FALSE(renderer.isBound());
    EXPECT_EQ(renderer.get(), nullptr);
    EXPECT_STREQ(renderer.getName(), "");
    EXPECT_THROW(renderer.clear(), ObjectNotBoundException);
}

class RendererTest : public SdlVideoFixture {};

TEST_F(RendererTest, SoftwareRendererFromSurface)
{
    Surface surface;
    surface.create(32, 32, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    ASSERT_NO_THROW(renderer.createSoftware(surface));

    EXPECT_TRUE(renderer.isBound());
    EXPECT_STREQ(renderer.getName(), "software");
}

TEST_F(RendererTest, DrawColorRoundTrip)
{
    Surface surface;
    surface.create(16, 16, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    renderer.createSoftware(surface);

    ASSERT_NO_THROW(renderer.setDrawColor(32, 64, 128, 200));

    uint8_t r = 0, g = 0, b = 0, a = 0;
    renderer.getDrawColor(r, g, b, a);
    EXPECT_EQ(r, 32u);
    EXPECT_EQ(g, 64u);
    EXPECT_EQ(b, 128u);
    EXPECT_EQ(a, 200u);
}

TEST_F(RendererTest, ClearPresentReadBack)
{
    Surface surface;
    surface.create(8, 8, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    renderer.createSoftware(surface);

    renderer.setDrawColor(255, 0, 0, 255);
    ASSERT_NO_THROW(renderer.clear());
    ASSERT_NO_THROW(renderer.present());

    uint8_t r = 0, g = 0, b = 0, a = 0;
    surface.readPixel(4, 4, r, g, b, a);
    EXPECT_EQ(r, 255u);
    EXPECT_EQ(g, 0u);
    EXPECT_EQ(b, 0u);
}

TEST_F(RendererTest, FillRectDrawsIntoTargetSurface)
{
    Surface surface;
    surface.create(16, 16, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    renderer.createSoftware(surface);

    renderer.setDrawColor(0, 0, 0, 255);
    renderer.clear();

    SDL_FRect rect{4.0f, 4.0f, 4.0f, 4.0f};
    renderer.setDrawColor(0, 255, 0, 255);
    ASSERT_NO_THROW(renderer.fillRect(&rect));
    renderer.present();

    uint8_t r = 0, g = 0, b = 0, a = 0;
    surface.readPixel(5, 5, r, g, b, a);
    EXPECT_EQ(g, 255u);

    surface.readPixel(0, 0, r, g, b, a);
    EXPECT_EQ(g, 0u);
}

TEST_F(RendererTest, ViewportRoundTrip)
{
    Surface surface;
    surface.create(32, 32, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    renderer.createSoftware(surface);

    SDL_Rect viewport{2, 2, 20, 20};
    ASSERT_NO_THROW(renderer.setViewport(&viewport));

    SDL_Rect readBack{};
    renderer.getViewport(readBack);
    EXPECT_EQ(readBack.x, 2);
    EXPECT_EQ(readBack.y, 2);
    EXPECT_EQ(readBack.w, 20);
    EXPECT_EQ(readBack.h, 20);
}

TEST_F(RendererTest, ScaleRoundTrip)
{
    Surface surface;
    surface.create(16, 16, SDL_PIXELFORMAT_RGBA32);

    Renderer renderer;
    renderer.createSoftware(surface);

    ASSERT_NO_THROW(renderer.setScale(2.0f, 3.0f));

    float x = 0.0f, y = 0.0f;
    renderer.getScale(x, y);
    EXPECT_FLOAT_EQ(x, 2.0f);
    EXPECT_FLOAT_EQ(y, 3.0f);
}

TEST_F(RendererTest, MoveConstructTransfersOwnership)
{
    Surface surface;
    surface.create(8, 8, SDL_PIXELFORMAT_RGBA32);

    Renderer a;
    a.createSoftware(surface);
    SDL_Renderer *raw = a.get();

    Renderer b(std::move(a));

    EXPECT_FALSE(a.isBound());
    EXPECT_EQ(b.get(), raw);
}

TEST_F(RendererTest, WindowRendererBinding)
{
    Window window = makeHiddenWindow();

    Renderer renderer;
    try
    {
        renderer = window.createRenderer();
    }
    catch (const ApiException &)
    {
        GTEST_SKIP() << "Driver could not create a renderer for hidden window.";
    }

    EXPECT_TRUE(renderer.isBound());
    Window bound = renderer.getWindow();
    EXPECT_TRUE(bound.isBound());
    EXPECT_FALSE(bound.isOwned());
    EXPECT_EQ(bound.getID(), window.getID());
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
