//! @file Sdl3Tools/SdlVideoFixture.hpp
//! @brief A shared gtest fixture for tests that require the SDL video
//! subsystem, gated by SDL_Init success.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SDL3_TOOLS_SDL_VIDEO_FIXTURE_HPP_
#define HEADER_AG_SDL3_TOOLS_SDL_VIDEO_FIXTURE_HPP_

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <string>

#include <gtest/gtest.h>

#include <SDL3/SDL.h>

#include "Ag/Sdl3Tools/Renderer.hpp"
#include "Ag/Sdl3Tools/Surface.hpp"
#include "Ag/Sdl3Tools/Texture.hpp"
#include "Ag/Sdl3Tools/Window.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A gtest fixture that initialises the SDL video subsystem once per
//! test suite. Tests are skipped if initialisation fails, so headless CI
//! runners produce no failures.
class SdlVideoFixture : public ::testing::Test
{
public:
    inline static bool _videoAvailable = false;
    inline static std::string _initError;

    static void SetUpTestSuite()
    {
        _videoAvailable = SDL_InitSubSystem(SDL_INIT_VIDEO);

        if (_videoAvailable == false)
            _initError.assign(SDL_GetError());
    }

    static void TearDownTestSuite()
    {
        if (_videoAvailable)
        {
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            _videoAvailable = false;
        }
    }

    void SetUp() override
    {
        if (_videoAvailable == false)
            GTEST_SKIP() << "SDL video subsystem unavailable: " << _initError;
    }

    //! @brief Creates a hidden window suitable for renderer/surface tests.
    static Window makeHiddenWindow(int w = 64, int h = 48)
    {
        Window window;
        window.create("Sdl3Tools Test", w, h, SDL_WINDOW_HIDDEN);

        return window;
    }
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
