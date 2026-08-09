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
    ASSERT_NO_THROW(texture.update(nullptr, pixels, 4 * 4));

    renderer.setDrawColor(0, 0, 0, 255);
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
