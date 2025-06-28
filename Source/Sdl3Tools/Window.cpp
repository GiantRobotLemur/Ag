//! @file Sdl3Tools/Window.cpp
//! @brief The definition of a class which wraps an SDL_Window resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/Window.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Window Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for an SDL window resource.
Window::Window() :
    _window(nullptr)
{
}

//! @brief Constructs a wrapper for an SDL window resource.
//! @param[in] window The window resource to wrap.
Window::Window(SDL_Window *window) :
    _window(window)
{
}

//! @brief Acquires a window resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the window from.
Window::Window(Window &&rhs) noexcept :
    _window(std::exchange(rhs._window, nullptr))
{
}

//! @brief Ensures that any underlying window resource is properly disposed of.
Window::~Window()
{
    release();
}

//! @brief Determines if the object is bound to an underling window resource.
//! @retval true The object is bound to an SDL window.
//! @retval false The object is in an unbound state.
bool Window::isBound() const
{
    return _window != nullptr;
}

//! @brief Gets the identifier of the display containing the centre of
//! the window.
//! @return A valid display ID.
//! @throws ObjectNotBoundException Thrown if the object is in an unbound state.
//! @throws ApiException If SDL fails to obtain a display ID.
SDL_DisplayID Window::getDisplayID() const
{
    auto window = verifyAccess("Get associated display");

    auto displayID = SDL_GetDisplayForWindow(window);

    if (displayID == 0)
        throw ApiException("SDL_GetDisplayForWindow()");

    return displayID;
}

//! @brief Creates a new window and binds it to the object.
//! @param[in] title The text to appear in the title bar.
//! @param[in] width The width of the window.
//! @param[in] height The height of the window.
//! @param[in] flags Options defining style and usage of the new window.
void Window::create(utf8_cptr_t title, int width, int height, SDL_WindowFlags flags)
{
    release();

    _window = SDL_CreateWindow(title, width, height, flags);

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindow()");
}

//! @brief Disposes of any underlying window resource.
void Window::release()
{
    auto window = std::exchange(_window, nullptr);

    if (window != nullptr)
        SDL_DestroyWindow(window);
}

//! @brief Disposes of any previously bound window and acquires a new window
//! resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the window from.
//! @returns A reference to the current object.
Window &Window::operator=(Window &&rhs) noexcept
{
    if (_window == rhs._window)
        return *this;

    release();

    _window = std::exchange(rhs._window, nullptr);

    return *this;
}

//! @brief Ensures the object is bound to an underlying SDL window.
//! @param[in] operation A description of the operation the window it to be
//! used in.
//! @return A valid pointer to the underlying SDL window.
//! @throws ObjectNotBoundException Thrown if the object is in an unbound state.
SDL_Window *Window::verifyAccess(utf8_cptr_t operation) const
{
    if (_window == nullptr)
        throw ObjectNotBoundException("Window", operation);

    return _window;
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

