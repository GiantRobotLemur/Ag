//! @file Ag/Sdl3Tools/Window.hpp
//! @brief The declaration of a class which wraps an SDL_Window resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_WINDOW_HPP__
#define __AG_SDL3_TOOLS_WINDOW_HPP__

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class which wraps an SDL_Window resource.
class Window
{
public:
    // Construction/Destruction
    Window();
    Window(SDL_Window *window);
    Window(const Window &) = delete;
    Window(Window &&rhs) noexcept;
    ~Window();

    // Accessors
    bool isBound() const;
    SDL_DisplayID getDisplayID() const;

    // Operations
    void create(utf8_cptr_t title, int width, int height, SDL_WindowFlags flags);
    void release();
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&rhs) noexcept;
    SDL_Window *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Window *_window;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
