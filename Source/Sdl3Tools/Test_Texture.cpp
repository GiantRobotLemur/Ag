//! @file Sdl3Tools/Test_Texture.cpp
//! @brief Unit tests for the Ag::SDL3::Texture and LockedTexture wrappers.
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
#include "SdlVideoFixture.hpp"

namespace Ag {
namespace SDL3 {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Helpers
////////////////////////////////////////////////////////////////////////////////
Renderer makeSoftwareRendererForSurface(Surface &surface, int w = 16, int h = 16)
{
    surface.create(w, h, SDL_PIXELFORMAT_RGBA32);
    Renderer renderer;
    renderer.createSoftware(surface);

    return renderer;
}

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(Texture, DefaultConstructUnbound)
{
    Texture texture;

    EXPECT_FALSE(texture.isBound());
    EXPECT_EQ(texture.get(), nullptr);
    EXPECT_EQ(texture.getWidth(), -1);
    EXPECT_THROW(texture.setAlphaMod(200), ObjectNotBoundException);
}

class TextureTest : public SdlVideoFixture {};

TEST_F(TextureTest, CreateStaticTexture)
{
    Surface surface;
    Renderer renderer = makeSoftwareRendererForSurface(surface);

    Texture texture;
    ASSERT_NO_THROW(texture.create(renderer, SDL_PIXELFORMAT_RGBA32,
                                   SDL_TEXTUREACCESS_STATIC, 16, 16));

    EXPECT_TRUE(texture.isBound());
    EXPECT_EQ(texture.getWidth(), 16);
    EXPECT_EQ(texture.getHeight(), 16);
    EXPECT_EQ(texture.getFormat(), SDL_PIXELFORMAT_RGBA32);
}

TEST_F(TextureTest, CreateFromSurface)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Surface source;
    source.create(8, 8, SDL_PIXELFORMAT_RGBA32);
    source.clear({0.0f, 1.0f, 0.0f, 1.0f});

    Texture texture;
    ASSERT_NO_THROW(texture.createFromSurface(renderer, source));

    EXPECT_TRUE(texture.isBound());
    EXPECT_EQ(texture.getWidth(), 8);
    EXPECT_EQ(texture.getHeight(), 8);
}

TEST_F(TextureTest, AlphaModRoundTrip)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);

    ASSERT_NO_THROW(texture.setAlphaMod(128));
    EXPECT_EQ(texture.getAlphaMod(), 128u);
}

TEST_F(TextureTest, BlendModeRoundTrip)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);

    ASSERT_NO_THROW(texture.setBlendMode(SDL_BLENDMODE_BLEND));
    EXPECT_EQ(texture.getBlendMode(), SDL_BLENDMODE_BLEND);
}

TEST_F(TextureTest, UpdateStaticAndDrawRendersPixels)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    // Fill a 4x4 red block of pixels.
    uint8_t pixels[4 * 4 * 4];
    for (int i = 0; i < 4 * 4; ++i)
    {
        pixels[i * 4 + 0] = 255;
        pixels[i * 4 + 1] = 0;
        pixels[i * 4 + 2] = 0;
        pixels[i * 4 + 3] = 255;
    }

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);
    ASSERT_NO_THROW(texture.update(pixels, 4 * 4));

    renderer.setDrawColour(0, 0, 0, 255);
    renderer.clear();
    SDL_FRect dst{2.0f, 2.0f, 4.0f, 4.0f};
    renderer.drawTexture(texture, nullptr, &dst);
    renderer.present();

    uint8_t r = 0, g = 0, b = 0, a = 0;
    backing.readPixel(3, 3, r, g, b, a);
    EXPECT_EQ(r, 255u);
    EXPECT_EQ(g, 0u);
}

TEST_F(TextureTest, LockStreamingTextureExposesPixels)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                   4, 4);

    {
        LockedTexture locked = texture.lock();
        ASSERT_TRUE(locked.isLocked());
        EXPECT_EQ(locked.getWidth(), 4);
        EXPECT_EQ(locked.getHeight(), 4);
        EXPECT_GT(locked.getPitch(), 0);

        std::memset(locked.getBits(), 0xFF, locked.getPitch() * locked.getHeight());
    }

    EXPECT_NO_THROW(texture.setAlphaMod(255));
}

TEST_F(TextureTest, CreateWithPointSizeMatchesScalarForm)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    ASSERT_NO_THROW(texture.create(renderer, SDL_PIXELFORMAT_RGBA32,
                                   SDL_TEXTUREACCESS_STATIC, Point(12, 6)));

    EXPECT_EQ(texture.getWidth(), 12);
    EXPECT_EQ(texture.getHeight(), 6);
}

TEST_F(TextureTest, SizeAsPointMatchesScalarForm)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   12, 6);

    float w = 0.0f, h = 0.0f;
    ASSERT_NO_THROW(texture.getSize(w, h));

    SDL_FPoint size = texture.getSize();

    EXPECT_FLOAT_EQ(size.x, w);
    EXPECT_FLOAT_EQ(size.y, h);
    EXPECT_FLOAT_EQ(size.x, 12.0f);
    EXPECT_FLOAT_EQ(size.y, 6.0f);
}

TEST_F(TextureTest, ColourModAsColourAppliesAlpha)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);

    ASSERT_NO_THROW(texture.setColourMod(Colour(10, 20, 30, 40)));

    SDL_Color mod = texture.getColourMod();
    EXPECT_EQ(mod.r, 10u);
    EXPECT_EQ(mod.g, 20u);
    EXPECT_EQ(mod.b, 30u);

    // The struct overload also carries the separately stored alpha modulation.
    EXPECT_EQ(mod.a, 40u);
    EXPECT_EQ(texture.getAlphaMod(), 40u);

    // The scalar overload leaves the alpha modulation alone.
    ASSERT_NO_THROW(texture.setColourMod(50, 60, 70));
    EXPECT_EQ(texture.getAlphaMod(), 40u);
}

TEST_F(TextureTest, ColourModFloatAsColourAppliesAlpha)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);

    ASSERT_NO_THROW(texture.setColourModFloat(FColour(0.25f, 0.5f, 0.75f, 0.5f)));

    SDL_FColor mod = texture.getColourModFloat();
    EXPECT_NEAR(mod.r, 0.25f, 0.01f);
    EXPECT_NEAR(mod.g, 0.5f, 0.01f);
    EXPECT_NEAR(mod.b, 0.75f, 0.01f);
    EXPECT_NEAR(mod.a, 0.5f, 0.01f);
    EXPECT_NEAR(texture.getAlphaModFloat(), 0.5f, 0.01f);
}

TEST_F(TextureTest, UpdateRegionLeavesRestOfTextureUntouched)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    // Start with an entirely blue texture, then overwrite a single red pixel.
    uint8_t blue[4 * 4 * 4];
    for (int i = 0; i < 4 * 4; ++i)
    {
        blue[i * 4 + 0] = 0;
        blue[i * 4 + 1] = 0;
        blue[i * 4 + 2] = 255;
        blue[i * 4 + 3] = 255;
    }

    uint8_t red[4] = { 255, 0, 0, 255 };

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);
    ASSERT_NO_THROW(texture.update(blue, 4 * 4));
    ASSERT_NO_THROW(texture.update(Rect(0, 0, 1, 1), red, 4));

    renderer.setDrawColour(0, 0, 0, 255);
    renderer.clear();

    // Draw at 1:1 scale so each texel maps onto exactly one target pixel.
    SDL_FRect dst{ 0.0f, 0.0f, 4.0f, 4.0f };
    renderer.drawTexture(texture, nullptr, &dst);
    renderer.present();

    uint8_t r = 0, g = 0, b = 0, a = 0;
    backing.readPixel(0, 0, r, g, b, a);
    EXPECT_EQ(r, 255u);
    EXPECT_EQ(b, 0u);

    backing.readPixel(2, 2, r, g, b, a);
    EXPECT_EQ(r, 0u);
    EXPECT_EQ(b, 255u);
}

TEST_F(TextureTest, LockRegionReportsRegionSize)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                   8, 8);

    {
        LockedTexture locked = texture.lock(Rect(2, 2, 4, 3));
        ASSERT_TRUE(locked.isLocked());
        EXPECT_EQ(locked.getWidth(), 4);
        EXPECT_EQ(locked.getHeight(), 3);
    }

    LockedTexture whole = texture.lock();
    EXPECT_EQ(whole.getWidth(), 8);
    EXPECT_EQ(whole.getHeight(), 8);
}

TEST_F(TextureTest, LockedPixelAtPointMatchesScalarForm)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING,
                   4, 4);

    LockedTexture locked = texture.lock();

    EXPECT_EQ(locked.getPixel(Point(2, 3)), locked.getPixel(2, 3));
    EXPECT_THROW(locked.getPixel(Point(4, 0)), ArgumentException);
    EXPECT_THROW(locked.getPixel(Point(0, 4)), ArgumentException);
}

TEST_F(TextureTest, LockOnStaticThrows)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture texture;
    texture.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
                   4, 4);

    EXPECT_THROW(texture.lock(), OperationException);
}

TEST_F(TextureTest, MoveAssignReleasesPrevious)
{
    Surface backing;
    Renderer renderer = makeSoftwareRendererForSurface(backing);

    Texture a;
    a.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 4, 4);
    Texture b;
    b.create(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 8, 8);

    SDL_Texture *bRaw = b.get();

    a = std::move(b);

    EXPECT_FALSE(b.isBound());
    EXPECT_EQ(a.get(), bRaw);
    EXPECT_EQ(a.getWidth(), 8);
}

} // Anonymous namespace

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
