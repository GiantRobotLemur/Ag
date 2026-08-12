//! @file Sdl3Tools/Window.cpp
//! @brief The definition of a class which wraps an SDL_Window resource.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/Primitives.hpp"
#include "Ag/Sdl3Tools/PropertySet.hpp"
#include "Ag/Sdl3Tools/Renderer.hpp"
#include "Ag/Sdl3Tools/Surface.hpp"
#include "Ag/Sdl3Tools/Window.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Window Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for an SDL window resource.
Window::Window() :
    _window(nullptr),
    _owned(true)
{
}

//! @brief Constructs a wrapper for an SDL window resource, taking ownership.
//! @param[in] window The window resource to wrap.
Window::Window(SDL_Window *window) :
    _window(window),
    _owned(true)
{
}

//! @brief Constructs a wrapper for an SDL window resource with explicit
//! ownership control.
//! @param[in] window The window resource to wrap.
//! @param[in] owned True if this wrapper should destroy the window on release;
//! false when the window is owned elsewhere (e.g. returned by
//! SDL_GetRenderWindow).
Window::Window(SDL_Window *window, bool owned) :
    _window(window),
    _owned(owned)
{
}

//! @brief Acquires a window resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the window from.
Window::Window(Window &&rhs) noexcept :
    _window(std::exchange(rhs._window, nullptr)),
    _owned(rhs._owned)
{
    rhs._owned = true;
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

//! @brief Indicates whether this wrapper owns the underlying SDL window and
//! will destroy it on release.
bool Window::isOwned() const
{
    return _owned;
}

//! @brief Gets a pointer to the underlying SDL window, or nullptr if unbound.
SDL_Window *Window::get() const
{
    return _window;
}

//! @brief Gets the numeric identifier of the window.
//! @return The SDL_WindowID, or 0 if the object is unbound.
//! @details The identifier is what event structures carry to name the
//! window an event belongs to, so it is the usual way to match an incoming
//! event back to a Window. Should only be called on the main thread.
SDL_WindowID Window::getID() const
{
    return SDL_GetWindowID(_window);
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

//! @brief Gets the flags describing the state and style of the window.
//! @return A bitwise combination of SDL_WindowFlags values, such as
//! SDL_WINDOW_FULLSCREEN, SDL_WINDOW_HIDDEN or SDL_WINDOW_RESIZABLE, or 0
//! if the object is unbound.
//! @details Should only be called on the main thread.
SDL_WindowFlags Window::getFlags() const
{
    return (_window == nullptr) ? 0u : SDL_GetWindowFlags(_window);
}

//! @brief Gets the SDL property set associated with the window.
//! @return A PropertySet giving access to window properties, including the
//! platform-specific handles such as SDL_PROP_WINDOW_WIN32_HWND_POINTER.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to return a property set.
//! @details Should only be called on the main thread.
PropertySet Window::getProperties() const
{
    auto window = verifyAccess("Get properties");
    SDL_PropertiesID id = SDL_GetWindowProperties(window);

    if (id == 0)
        throw ApiException("SDL_GetWindowProperties()");

    return PropertySet(id);
}

//! @brief Gets the pixel density of the window.
//! @return The ratio of pixel size to window size, or 0.0f if the object is
//! unbound or SDL reports a failure.
//! @details A 1920x1080 window backed by a 3840x2160 high-density buffer
//! has a pixel density of 2.0. Contrast getDisplayScale(), which also
//! folds in the user's display scale setting. Should only be called on the
//! main thread.
float Window::getPixelDensity() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowPixelDensity(_window);
}

//! @brief Gets the content display scale relative to the window's pixel
//! size.
//! @return The expected scale at which to present content, or 0.0f if the
//! object is unbound or SDL reports a failure.
//! @details This combines the window's pixel density with the display's
//! content scale, so a 3840x2160 window with a scale of 2.0 should show
//! content at the same physical size as a 1920x1080 window at 1.0. It
//! corresponds to the user's display scale setting and changes when that
//! setting changes or the window moves to a differently scaled display.
//! Should only be called on the main thread.
float Window::getDisplayScale() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowDisplayScale(_window);
}

//! @brief Gets the pixel format of the window's surface.
//! @return The SDL_PixelFormat of the window, or SDL_PIXELFORMAT_UNKNOWN
//! when the object is unbound or SDL reports a failure.
//! @details Should only be called on the main thread.
SDL_PixelFormat Window::getPixelFormat() const
{
    return (_window == nullptr) ? SDL_PIXELFORMAT_UNKNOWN
                                : SDL_GetWindowPixelFormat(_window);
}

//! @brief Determines whether the mouse is confined to the window.
//! @retval true The mouse is grabbed by the window.
//! @retval false The object is unbound, or the mouse is not grabbed.
//! @details Should only be called on the main thread.
bool Window::getMouseGrab() const
{
    return (_window != nullptr) && SDL_GetWindowMouseGrab(_window);
}

//! @brief Determines whether the keyboard is grabbed by the window.
//! @retval true The window captures system keyboard shortcuts.
//! @retval false The object is unbound, or the keyboard is not grabbed.
//! @details Should only be called on the main thread.
bool Window::getKeyboardGrab() const
{
    return (_window != nullptr) && SDL_GetWindowKeyboardGrab(_window);
}

//! @brief Determines whether relative mouse mode is active for the window.
//! @retval true Mouse events report relative motion rather than absolute
//! positions.
//! @retval false The object is unbound, or relative mode is off.
//! @details Should only be called on the main thread.
bool Window::getRelativeMouseMode() const
{
    return (_window != nullptr) && SDL_GetWindowRelativeMouseMode(_window);
}

//! @brief Gets the opacity of the window.
//! @return The opacity, from 0.0f for fully transparent to 1.0f for fully
//! opaque, or 0.0f if the object is unbound or SDL reports a failure.
//! @details A window on a platform which does not support transparency
//! reports 1.0f. Should only be called on the main thread.
float Window::getOpacity() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowOpacity(_window);
}

//! @brief Gets the vsync interval used when presenting the window surface.
//! @return A positive count of vertical refreshes to wait for,
//! SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE for late swap tearing, or
//! SDL_WINDOW_SURFACE_VSYNC_DISABLED when vsync is off.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to return the vsync value.
//! @details Applies to the surface-based presentation path only, not to a
//! renderer attached to the window. Should only be called on the main
//! thread.
int Window::getSurfaceVSync() const
{
    auto window = verifyAccess("Get surface vsync");
    int value = 0;

    if (SDL_GetWindowSurfaceVSync(window, &value) == false)
        throw ApiException("SDL_GetWindowSurfaceVSync()");

    return value;
}

//! @brief Determines whether the window currently has an associated surface.
//! @retval true A surface has been created for the window.
//! @retval false The object is unbound, or no surface exists yet.
//! @details A surface is created lazily by getSurface() and destroyed by
//! destroySurface(). Should only be called on the main thread.
bool Window::hasSurface() const
{
    return (_window != nullptr) && SDL_WindowHasSurface(_window);
}

//! @brief Gets a non-owning wrapper for the window's parent, if any.
//! @return A Window wrapper which does not own the underlying resource. It
//! is unbound when the window is top-level rather than a child or popup.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details Should only be called on the main thread.
Window Window::getParent() const
{
    auto window = verifyAccess("Get parent");
    SDL_Window *parent = SDL_GetWindowParent(window);

    return Window(parent, false);
}

//! @brief Gets the current title of the window.
//! @return The UTF-8 title text, or an empty string if the object is
//! unbound or the window has no title.
//! @details Never returns nullptr, so the result is always safe to print.
//! The pointer is owned by SDL and is invalidated by the next call to
//! setTitle(). Should only be called on the main thread.
utf8_cptr_t Window::getTitle() const
{
    return (_window == nullptr) ? "" : SDL_GetWindowTitle(_window);
}

//! @brief Sets the title of the window.
//! @param[in] title The UTF-8 text to show in the title bar. A nullptr is
//! treated as an empty title.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowTitle() fails.
//! @details The text is copied, so @p title need not outlive the call.
//! Should only be called on the main thread.
void Window::setTitle(utf8_cptr_t title)
{
    auto window = verifyAccess("Set title");

    if (SDL_SetWindowTitle(window, title) == false)
        throw ApiException("SDL_SetWindowTitle()");
}

//! @brief Sets the icon of the window from a surface.
//! @param[in] icon The surface holding the icon image.
//! @throws ObjectNotBoundException If either the window or icon surface is
//! unbound.
//! @throws ApiException If SDL_SetWindowIcon() fails.
//! @details If @p icon carries alternate representations, it is treated as
//! the image for 100% display scale and the alternates are used for high
//! DPI. On a 2x display a 32x32 original is replaced by a 64x64 alternate
//! where one exists; failing that the nearest larger image is downscaled,
//! or the nearest smaller one upscaled. Should only be called on the main
//! thread.
void Window::setIcon(const Surface &icon)
{
    auto window = verifyAccess("Set icon");
    auto iconSurface = icon.verifyAccess("Provide window icon");

    if (SDL_SetWindowIcon(window, iconSurface) == false)
        throw ApiException("SDL_SetWindowIcon()");
}

//! @brief Gets the current position of the window.
//! @param[out] x Receives the horizontal position of the top left corner.
//! @param[out] y Receives the vertical position of the top left corner.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowPosition() fails.
//! @details The position is in screen coordinates and refers to the client
//! area rather than the outer frame. Should only be called on the main
//! thread.
void Window::getPosition(int &x, int &y) const
{
    auto window = verifyAccess("Get position");

    if (SDL_GetWindowPosition(window, &x, &y) == false)
        throw ApiException("SDL_GetWindowPosition()");
}

//! @brief Gets the current position of the window.
//! @return The position of the top left corner of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowPosition() fails.
SDL_Point Window::getPosition() const
{
    auto window = verifyAccess("Get position");
    Point position;

    if (SDL_GetWindowPosition(window, &position.x, &position.y) == false)
        throw ApiException("SDL_GetWindowPosition()");

    return position;
}

//! @brief Sets the position of the window.
//! @param[in] x The horizontal position of the top left corner, or one of
//! the SDL_WINDOWPOS_CENTERED and SDL_WINDOWPOS_UNDEFINED macros.
//! @param[in] y The vertical position of the top left corner.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowPosition() fails.
//! @details This is a request which the windowing system may modify or
//! deny, and on some systems it is applied asynchronously - call sync() to
//! block until it takes effect. It has no effect on a fullscreen or
//! maximised window. Should only be called on the main thread.
void Window::setPosition(int x, int y)
{
    auto window = verifyAccess("Set position");

    if (SDL_SetWindowPosition(window, x, y) == false)
        throw ApiException("SDL_SetWindowPosition()");
}

//! @brief Sets the position of the window.
//! @param[in] pos The position of the top left corner of the window. Either
//! component may be one of the SDL_WINDOWPOS_CENTERED and
//! SDL_WINDOWPOS_UNDEFINED macros.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowPosition() fails.
//! @details This is a request which the windowing system may modify or
//! deny, and on some systems it is applied asynchronously - call sync() to
//! block until it takes effect. It has no effect on a fullscreen or
//! maximised window. Should only be called on the main thread.
void Window::setPosition(const SDL_Point &pos)
{
    auto window = verifyAccess("Set position");

    if (SDL_SetWindowPosition(window, pos.x, pos.y) == false)
        throw ApiException("SDL_SetWindowPosition()");
}

//! @brief Gets the size of the window's client area in logical units.
//! @param[out] w Receives the width.
//! @param[out] h Receives the height.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSize() fails.
//! @details On a high-DPI display this may be smaller than the size in
//! pixels reported by getSizeInPixels(). Should only be called on the main
//! thread.
void Window::getSize(int &w, int &h) const
{
    auto window = verifyAccess("Get size");

    if (SDL_GetWindowSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowSize()");
}

//! @brief Gets the size of the window in logical units.
//! @return The horizontal and vertical extent of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSize() fails.
SDL_Point Window::getSize() const
{
    auto window = verifyAccess("Get size");
    Point size;

    if (SDL_GetWindowSize(window, &size.x, &size.y) == false)
        throw ApiException("SDL_GetWindowSize()");

    return size;
}

//! @brief Sets the size of the window's client area in logical units.
//! @param[in] w The desired width, which must be greater than zero.
//! @param[in] h The desired height, which must be greater than zero.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowSize() fails.
//! @details This is a request which the windowing system may clamp to the
//! minimum and maximum sizes, or to the usable desktop bounds, and on some
//! systems it is applied asynchronously - call sync() to block until it
//! takes effect. It has no effect on a fullscreen or maximised window.
//! Should only be called on the main thread.
void Window::setSize(int w, int h)
{
    auto window = verifyAccess("Set size");

    if (SDL_SetWindowSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowSize()");
}

//! @brief Sets the size of the window's client area in logical units.
//! @param[in] size The horizontal and vertical extent of the window, both
//! of which must be greater than zero.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowSize() fails.
//! @details This is a request which the windowing system may clamp or
//! apply asynchronously - call sync() to block until it takes effect. It
//! has no effect on a fullscreen or maximised window. Should only be called
//! on the main thread.
void Window::setSize(const SDL_Point &size)
{
    auto window = verifyAccess("Set size");

    if (SDL_SetWindowSize(window, size.x, size.y) == false)
        throw ApiException("SDL_SetWindowSize()");
}

//! @brief Gets the size of the window's client area in raw pixels.
//! @param[out] w Receives the width, in pixels.
//! @param[out] h Receives the height, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSizeInPixels() fails.
//! @details This is the drawable size, which on a high-DPI display exceeds
//! the logical size reported by getSize() by the window's pixel density.
//! Should only be called on the main thread.
void Window::getSizeInPixels(int &w, int &h) const
{
    auto window = verifyAccess("Get size in pixels");

    if (SDL_GetWindowSizeInPixels(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowSizeInPixels()");
}

//! @brief Gets the size of the window in raw pixels.
//! @return The horizontal and vertical extent of the window, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSizeInPixels() fails.
SDL_Point Window::getSizeInPixels() const
{
    auto window = verifyAccess("Get size in pixels");
    Point size;

    if (SDL_GetWindowSizeInPixels(window, &size.x, &size.y) == false)
        throw ApiException("SDL_GetWindowSizeInPixels()");

    return size;
}

//! @brief Gets the minimum size of the window's client area.
//! @param[out] w Receives the minimum width, or 0 when no limit is set.
//! @param[out] h Receives the minimum height, or 0 when no limit is set.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMinimumSize() fails.
//! @details Should only be called on the main thread.
void Window::getMinimumSize(int &w, int &h) const
{
    auto window = verifyAccess("Get minimum size");

    if (SDL_GetWindowMinimumSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowMinimumSize()");
}

//! @brief Gets the minimum size of the window.
//! @return The smallest horizontal and vertical extent the window may take.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMinimumSize() fails.
SDL_Point Window::getMinimumSize() const
{
    auto window = verifyAccess("Get minimum size");
    Point size;

    if (SDL_GetWindowMinimumSize(window, &size.x, &size.y) == false)
        throw ApiException("SDL_GetWindowMinimumSize()");

    return size;
}

//! @brief Sets the minimum size of the window's client area.
//! @param[in] w The minimum width, or 0 for no limit.
//! @param[in] h The minimum height, or 0 for no limit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMinimumSize() fails.
//! @details The window is resized immediately if it is currently smaller
//! than the new minimum. Should only be called on the main thread.
void Window::setMinimumSize(int w, int h)
{
    auto window = verifyAccess("Set minimum size");

    if (SDL_SetWindowMinimumSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowMinimumSize()");
}

//! @brief Sets the minimum size of the window.
//! @param[in] size The smallest horizontal and vertical extent the window
//! may take. Either component may be 0 for no limit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMinimumSize() fails.
//! @details The window is resized immediately if it is currently smaller
//! than the new minimum. Should only be called on the main thread.
void Window::setMinimumSize(const SDL_Point &size)
{
    auto window = verifyAccess("Set minimum size");

    if (SDL_SetWindowMinimumSize(window, size.x, size.y) == false)
        throw ApiException("SDL_SetWindowMinimumSize()");
}

//! @brief Gets the maximum size of the window's client area.
//! @param[out] w Receives the maximum width, or 0 when no limit is set.
//! @param[out] h Receives the maximum height, or 0 when no limit is set.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMaximumSize() fails.
//! @details Should only be called on the main thread.
void Window::getMaximumSize(int &w, int &h) const
{
    auto window = verifyAccess("Get maximum size");

    if (SDL_GetWindowMaximumSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowMaximumSize()");
}

//! @brief Gets the maximum size of the window.
//! @return The largest horizontal and vertical extent the window may take.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMaximumSize() fails.
SDL_Point Window::getMaximumSize() const
{
    auto window = verifyAccess("Get maximum size");
    Point size;

    if (SDL_GetWindowMaximumSize(window, &size.x, &size.y) == false)
        throw ApiException("SDL_GetWindowMaximumSize()");

    return size;
}

//! @brief Sets the maximum size of the window's client area.
//! @param[in] w The maximum width, or 0 for no limit.
//! @param[in] h The maximum height, or 0 for no limit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMaximumSize() fails.
//! @details The window is resized immediately if it is currently larger
//! than the new maximum. Should only be called on the main thread.
void Window::setMaximumSize(int w, int h)
{
    auto window = verifyAccess("Set maximum size");

    if (SDL_SetWindowMaximumSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowMaximumSize()");
}

//! @brief Sets the maximum size of the window.
//! @param[in] size The largest horizontal and vertical extent the window
//! may take. Either component may be 0 for no limit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMaximumSize() fails.
//! @details The window is resized immediately if it is currently larger
//! than the new maximum. Should only be called on the main thread.
void Window::setMaximumSize(const SDL_Point &size)
{
    auto window = verifyAccess("Set maximum size");

    if (SDL_SetWindowMaximumSize(window, size.x, size.y) == false)
        throw ApiException("SDL_SetWindowMaximumSize()");
}

//! @brief Gets the size of the platform-drawn window borders around the
//! client area.
//! @param[out] top Receives the height of the top border, usually the
//! title bar.
//! @param[out] left Receives the width of the left border.
//! @param[out] bottom Receives the height of the bottom border.
//! @param[out] right Receives the width of the right border.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowBordersSize() fails, which also
//! covers platforms where the query is unsupported.
//! @details This can fail on a window the display server has not yet
//! decorated, so avoid calling it immediately after create() - wait until
//! the window has been presented and composited. On failure the outputs are
//! set to zero, as though the window were borderless. Should only be called
//! on the main thread.
void Window::getBordersSize(int &top, int &left, int &bottom, int &right) const
{
    auto window = verifyAccess("Get borders size");

    if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) == false)
        throw ApiException("SDL_GetWindowBordersSize()");
}

//! @brief Gets the aspect ratio bounds for the window's client area.
//! @param[out] minRatio Receives the minimum width divided by height, or
//! 0.0f when no limit is set.
//! @param[out] maxRatio Receives the maximum width divided by height, or
//! 0.0f when no limit is set.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowAspectRatio() fails.
//! @details Larger ratios are wider, so 2560x1600 is 1.6. Should only be
//! called on the main thread.
void Window::getAspectRatio(float &minRatio, float &maxRatio) const
{
    auto window = verifyAccess("Get aspect ratio");

    if (SDL_GetWindowAspectRatio(window, &minRatio, &maxRatio) == false)
        throw ApiException("SDL_GetWindowAspectRatio()");
}

//! @brief Requests aspect ratio bounds for the window's client area.
//! @param[in] minRatio The minimum width divided by height, or 0.0f for no
//! limit.
//! @param[in] maxRatio The maximum width divided by height, or 0.0f for no
//! limit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowAspectRatio() fails.
//! @details Larger ratios are wider, so 2560x1600 is 1.6. If the window is
//! currently fixed in size, by being maximised or fullscreen, the request
//! is deferred until it becomes resizable again. On some systems the change
//! is asynchronous - call sync() to block until it takes effect. The
//! resulting size may not match the requested ratio exactly, since the
//! windowing system can constrain it, and the request may be denied
//! outright. Should only be called on the main thread.
void Window::setAspectRatio(float minRatio, float maxRatio)
{
    auto window = verifyAccess("Set aspect ratio");

    if (SDL_SetWindowAspectRatio(window, minRatio, maxRatio) == false)
        throw ApiException("SDL_SetWindowAspectRatio()");
}

//! @brief Gets the safe-area rectangle within the window.
//! @param[out] area Receives the region which is safe to use for
//! interactive content.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSafeArea() fails.
//! @details Some devices obscure parts of the screen with on-screen
//! controls, curved edges, camera notches or TV overscan. Drawing should
//! continue into the rest of the window, but visually important or
//! interactive content should be confined to @p area. Should only be called
//! on the main thread.
void Window::getSafeArea(SDL_Rect &area) const
{
    auto window = verifyAccess("Get safe area");

    if (SDL_GetWindowSafeArea(window, &area) == false)
        throw ApiException("SDL_GetWindowSafeArea()");
}

//! @brief Gets the safe-area rectangle within the window.
//! @return The region of the window in which content will not be obscured.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSafeArea() fails.
SDL_Rect Window::getSafeArea() const
{
    auto window = verifyAccess("Get safe area");
    Rect area;

    if (SDL_GetWindowSafeArea(window, &area) == false)
        throw ApiException("SDL_GetWindowSafeArea()");

    return area;
}

//! @brief Gets the display mode the window will use in fullscreen.
//! @return A pointer to the exclusive fullscreen display mode, or nullptr
//! if the object is unbound or the window will use borderless fullscreen
//! desktop mode instead.
//! @details The returned pointer is owned by SDL and remains valid until
//! the mode is changed. Prefer tryGetFullscreenMode(), which copies the
//! mode and reports the nullptr case as a bool. Should only be called on the
//! main thread.
const SDL_DisplayMode *Window::getFullscreenMode() const
{
    return (_window == nullptr) ? nullptr : SDL_GetWindowFullscreenMode(_window);
}

//! @brief Attempts to get the display mode the window will use in fullscreen.
//! @param[out] mode Receives a copy of the display mode on success.
//! @retval true An explicit fullscreen display mode is set.
//! @retval false The object is unbound, or the window will use borderless
//! fullscreen desktop mode rather than an explicit display mode.
bool Window::tryGetFullscreenMode(SDL_DisplayMode &mode) const
{
    if (_window == nullptr)
        return false;

    const SDL_DisplayMode *result = SDL_GetWindowFullscreenMode(_window);

    if (result == nullptr)
        return false;

    mode = *result;

    return true;
}

//! @brief Attempts to get the currently confined mouse rectangle.
//! @param[out] rect Receives the rectangle on success.
//! @retval true A rectangle is currently set.
//! @retval false The object is unbound or no rectangle is set.
bool Window::tryGetMouseRect(SDL_Rect &rect) const
{
    if (_window == nullptr)
        return false;

    const SDL_Rect *result = SDL_GetWindowMouseRect(_window);

    if (result == nullptr)
        return false;

    rect = *result;
    return true;
}

//! @brief Creates a new window and binds it to the object.
//! @param[in] title The text to appear in the title bar.
//! @param[in] width The width of the window.
//! @param[in] height The height of the window.
//! @param[in] flags Options defining style and usage of the new window, a
//! bitwise combination of SDL_WindowFlags values.
//! @throws ApiException If SDL_CreateWindow() fails.
//! @details Any window previously bound to the object is released first.
//! The new window is owned, so it is destroyed when the object is. The size
//! is in logical units rather than pixels. Should only be called on the main
//! thread.
void Window::create(utf8_cptr_t title, int width, int height, SDL_WindowFlags flags)
{
    release();

    _window = SDL_CreateWindow(title, width, height, flags);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindow()");
}

//! @brief Creates a new window and binds it to the object.
//! @param[in] title The text to appear in the title bar.
//! @param[in] size The width and height of the window, in logical units.
//! @param[in] flags Options defining style and usage of the new window, a
//! bitwise combination of SDL_WindowFlags values.
//! @throws ApiException If SDL_CreateWindow() fails.
//! @details Any window previously bound to the object is released first.
//! The new window is owned, so it is destroyed when the object is. Should
//! only be called on the main thread.
void Window::create(utf8_cptr_t title, const SDL_Point &size,
                    SDL_WindowFlags flags)
{
    release();

    _window = SDL_CreateWindow(title, size.x, size.y, flags);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindow()");
}

//! @brief Creates a new window which covers an entire screen, perhaps changing
//! the display mode.
//! @param[in] title The title of the window which maybe displayed elsewhere in the system.
//! @param[in] display The display for the window to acquire.
//! @param[in] mode The display mode to set that display to.
//! @param[in] flags Option flags determining behaviour of the window. Only
//! SDL_WINDOW_OPENGL is honoured; the fullscreen state is implied.
//! @throws ApiException If SDL_CreateWindowWithProperties() or
//! SDL_SetWindowFullscreenMode() fails.
//! @details Any window previously bound to the object is released first.
//! The window is created over the usable bounds of @p display and then
//! switched to @p mode. If setting the mode fails the part-built window is
//! destroyed before the exception propagates, so the object is left
//! unbound. Should only be called on the main thread.
void Window::createFullScreen(utf8_cptr_t title, SDL_DisplayID display,
                              const SDL_DisplayMode &mode, SDL_WindowFlags flags)
{
    release();

    PropertySet windowProperties;
    Rect displayBounds;

    windowProperties.set(SDL_PROP_WINDOW_CREATE_FULLSCREEN_BOOLEAN, true);

    if (Utf::isNullOrEmpty(title) == false)
    {
        windowProperties.set(SDL_PROP_WINDOW_CREATE_TITLE_STRING, title);
    }

    SDL_GetDisplayUsableBounds(display, &displayBounds);
    windowProperties.set(SDL_PROP_WINDOW_CREATE_X_NUMBER, displayBounds.x);
    windowProperties.set(SDL_PROP_WINDOW_CREATE_Y_NUMBER, displayBounds.y);
    windowProperties.set(SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, displayBounds.w);
    windowProperties.set(SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, displayBounds.h);

    if (flags & SDL_WINDOW_OPENGL)
    {
        windowProperties.set(SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
    }

    _window = SDL_CreateWindowWithProperties(windowProperties);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindowWithProperties()");

    if (SDL_SetWindowFullscreenMode(_window, &mode) == false)
    {
        // Ensure the window is destroyed after the exception is created in
        // order to preserve the SDL error state.
        SDL_Window *windowToDestroy = std::exchange(_window, nullptr);
        AtScopeExit1 destroyWindow(SDL_DestroyWindow, windowToDestroy);

        throw ApiException("SDL_SetWindowFullscreenMode()");
    }
}

//! @brief Creates a popup window relative to another window.
//! @param[in] parent The window the popup is positioned relative to.
//! @param[in] x The horizontal offset of the popup from @p parent.
//! @param[in] y The vertical offset of the popup from @p parent.
//! @param[in] w The width of the popup.
//! @param[in] h The height of the popup.
//! @param[in] flags Options defining style and usage of the new window.
//! SDL_WINDOW_TOOLTIP or SDL_WINDOW_POPUP_MENU must be among them.
//! @throws ObjectNotBoundException If @p parent is unbound.
//! @throws ApiException If SDL_CreatePopupWindow() fails.
//! @details Any window previously bound to the object is released first.
//! The popup is destroyed automatically if @p parent is destroyed first.
//! Should only be called on the main thread.
void Window::createPopup(const Window &parent, int x, int y, int w, int h,
                         SDL_WindowFlags flags)
{
    auto parentWindow = parent.verifyAccess("Provide popup parent");

    release();

    _window = SDL_CreatePopupWindow(parentWindow, x, y, w, h, flags);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreatePopupWindow()");
}

//! @brief Creates a popup window relative to another window.
//! @param[in] parent The window the popup is positioned relative to.
//! @param[in] area The offset from @p parent and the size of the popup.
//! @param[in] flags Options defining style and usage of the new window.
//! SDL_WINDOW_TOOLTIP or SDL_WINDOW_POPUP_MENU must be among them.
//! @throws ObjectNotBoundException If @p parent is unbound.
//! @throws ApiException If SDL_CreatePopupWindow() fails.
//! @details Any window previously bound to the object is released first.
//! The popup is destroyed automatically if @p parent is destroyed first.
//! Should only be called on the main thread.
void Window::createPopup(const Window &parent, const SDL_Rect &area,
                         SDL_WindowFlags flags)
{
    auto parentWindow = parent.verifyAccess("Provide popup parent");

    release();

    _window = SDL_CreatePopupWindow(parentWindow, area.x, area.y,
                                    area.w, area.h, flags);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreatePopupWindow()");
}

//! @brief Creates a new window from a fully specified property set.
//! @param[in] props Properties describing the window to create, such as
//! SDL_PROP_WINDOW_CREATE_TITLE_STRING,
//! SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER and
//! SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER.
//! @throws ApiException If SDL_CreateWindowWithProperties() fails.
//! @details Any window previously bound to the object is released first.
//! This is the only route to creation options which have no equivalent
//! flag, such as attaching to an existing native window handle. Should only
//! be called on the main thread.
void Window::createWithProperties(const PropertySet &props)
{
    release();

    _window = SDL_CreateWindowWithProperties(props);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindowWithProperties()");
}

//! @brief Shows the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ShowWindow() fails.
//! @details A window created with SDL_WINDOW_HIDDEN stays invisible until
//! this is called. Should only be called on the main thread.
void Window::show()
{
    auto window = verifyAccess("Show");

    if (SDL_ShowWindow(window) == false)
        throw ApiException("SDL_ShowWindow()");
}

//! @brief Hides the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_HideWindow() fails.
//! @details The window still exists and may be shown again with show().
//! Should only be called on the main thread.
void Window::hide()
{
    auto window = verifyAccess("Hide");

    if (SDL_HideWindow(window) == false)
        throw ApiException("SDL_HideWindow()");
}

//! @brief Raises the window above other windows and gives it input focus.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RaiseWindow() fails.
//! @details The result is a request; windowing systems commonly restrict
//! focus stealing by applications which are not already active. Should only
//! be called on the main thread.
void Window::raise()
{
    auto window = verifyAccess("Raise");

    if (SDL_RaiseWindow(window) == false)
        throw ApiException("SDL_RaiseWindow()");
}

//! @brief Minimizes the window to an iconic state.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_MinimizeWindow() fails.
//! @details On some systems this is applied asynchronously - call sync() to
//! block until it takes effect. Should only be called on the main thread.
void Window::minimize()
{
    auto window = verifyAccess("Minimize");

    if (SDL_MinimizeWindow(window) == false)
        throw ApiException("SDL_MinimizeWindow()");
}

//! @brief Maximizes the window to fill the usable desktop area.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_MaximizeWindow() fails.
//! @details The window must be resizable for this to have any effect. On
//! some systems it is applied asynchronously - call sync() to block until it
//! takes effect. Should only be called on the main thread.
void Window::maximize()
{
    auto window = verifyAccess("Maximize");

    if (SDL_MaximizeWindow(window) == false)
        throw ApiException("SDL_MaximizeWindow()");
}

//! @brief Restores a minimized or maximized window to its previous size and
//! position.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RestoreWindow() fails.
//! @details On some systems this is applied asynchronously - call sync() to
//! block until it takes effect. Should only be called on the main thread.
void Window::restore()
{
    auto window = verifyAccess("Restore");

    if (SDL_RestoreWindow(window) == false)
        throw ApiException("SDL_RestoreWindow()");
}

//! @brief Blocks until pending window state changes have been applied.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SyncWindow() fails, which is how a timeout
//! waiting for the windowing system is reported.
//! @details Several window operations - setPosition(), setSize(),
//! setAspectRatio(), minimize(), maximize(), restore() and the fullscreen
//! calls - are requests which some windowing systems satisfy
//! asynchronously. Call this when the new state must be visible before
//! execution continues. Should only be called on the main thread.
void Window::sync()
{
    auto window = verifyAccess("Sync");

    if (SDL_SyncWindow(window) == false)
        throw ApiException("SDL_SyncWindow()");
}

//! @brief Requests the window flash to indicate a need for attention.
//! @param[in] operation How long to flash for:
//! SDL_FLASH_CANCEL to stop flashing, SDL_FLASH_BRIEFLY for a single
//! attention request, or SDL_FLASH_UNTIL_FOCUSED until the user responds.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FlashWindow() fails, which also covers
//! platforms where flashing is unsupported.
//! @details Should only be called on the main thread.
void Window::flash(SDL_FlashOperation operation)
{
    auto window = verifyAccess("Flash");

    if (SDL_FlashWindow(window, operation) == false)
        throw ApiException("SDL_FlashWindow()");
}

//! @brief Enables or disables the window border.
//! @param[in] bordered True to add the platform's decorations, false to
//! remove them.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowBordered() fails.
//! @details Has no effect on a fullscreen window. Should only be called on
//! the main thread.
void Window::setBordered(bool bordered)
{
    auto window = verifyAccess("Set bordered");

    if (SDL_SetWindowBordered(window, bordered) == false)
        throw ApiException("SDL_SetWindowBordered()");
}

//! @brief Enables or disables interactive resizing of the window.
//! @param[in] resizable True to let the user resize the window, false to
//! fix its size.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowResizable() fails.
//! @details Has no effect on a fullscreen window. Should only be called on
//! the main thread.
void Window::setResizable(bool resizable)
{
    auto window = verifyAccess("Set resizable");

    if (SDL_SetWindowResizable(window, resizable) == false)
        throw ApiException("SDL_SetWindowResizable()");
}

//! @brief Sets whether the window should stay above other windows.
//! @param[in] onTop True to keep the window above all others, false to let
//! it be covered normally.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowAlwaysOnTop() fails.
//! @details Should only be called on the main thread.
void Window::setAlwaysOnTop(bool onTop)
{
    auto window = verifyAccess("Set always on top");

    if (SDL_SetWindowAlwaysOnTop(window, onTop) == false)
        throw ApiException("SDL_SetWindowAlwaysOnTop()");
}

//! @brief Requests that the window enter or leave fullscreen.
//! @param[in] fullscreen True to go fullscreen, false to return to windowed.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFullscreen() fails.
//! @details Which kind of fullscreen is used depends on the display mode
//! previously chosen: setFullscreenMode() selects an exclusive video mode,
//! while resetFullscreenMode() - the default - gives borderless fullscreen
//! desktop. On some systems the change is asynchronous, so call sync() when
//! the new state must be in place before continuing. Should only be called
//! on the main thread.
void Window::setFullscreen(bool fullscreen)
{
    auto window = verifyAccess("Set fullscreen");

    if (SDL_SetWindowFullscreen(window, fullscreen) == false)
        throw ApiException("SDL_SetWindowFullscreen()");
}

//! @brief Sets the display mode used in fullscreen.
//! @param[in] mode The display mode the window should switch to when it
//! enters fullscreen.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFullscreenMode() fails.
//! @details Affects only the mode used while fullscreen; use setSize() to
//! change a windowed window. @p mode should be one of the modes reported by
//! SDL_GetFullscreenDisplayModes() for the target display. If the window is
//! already fullscreen the change may be applied asynchronously - call
//! sync() to block until it takes effect. Once applied, an
//! SDL_EVENT_WINDOW_RESIZED and/or SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED
//! event is emitted carrying the new dimensions. Should only be called on
//! the main thread.
void Window::setFullscreenMode(const SDL_DisplayMode &mode)
{
    auto window = verifyAccess("Set fullscreen mode");

    if (SDL_SetWindowFullscreenMode(window, &mode) == false)
        throw ApiException("SDL_SetWindowFullscreenMode()");
}

//! @brief Selects borderless fullscreen desktop mode for the window.
//! @details Rather than switching the display to a specific video mode when
//! the window enters fullscreen, the window will fill the desktop at whatever
//! mode the display is already using.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFullscreenMode() fails.
void Window::resetFullscreenMode()
{
    auto window = verifyAccess("Reset fullscreen mode");

    if (SDL_SetWindowFullscreenMode(window, nullptr) == false)
        throw ApiException("SDL_SetWindowFullscreenMode(nullptr)");
}

//! @brief Sets the opacity of the window.
//! @param[in] opacity The desired opacity, from 0.0f for fully transparent
//! to 1.0f for fully opaque. Values outside that range are clamped.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowOpacity() fails, which also covers
//! platforms where transparency is unsupported.
//! @details Should only be called on the main thread.
void Window::setOpacity(float opacity)
{
    auto window = verifyAccess("Set opacity");

    if (SDL_SetWindowOpacity(window, opacity) == false)
        throw ApiException("SDL_SetWindowOpacity()");
}

//! @brief Enables or disables keyboard grab.
//! @param[in] grabbed True to capture system keyboard shortcuts, false to
//! leave them to the system.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowKeyboardGrab() fails.
//! @details While grabbed, combinations such as Alt+Tab are delivered to
//! the window instead of being handled by the desktop, which suits
//! fullscreen games and remote-desktop clients. Some system-reserved
//! combinations cannot be captured. Should only be called on the main
//! thread.
void Window::setKeyboardGrab(bool grabbed)
{
    auto window = verifyAccess("Set keyboard grab");

    if (SDL_SetWindowKeyboardGrab(window, grabbed) == false)
        throw ApiException("SDL_SetWindowKeyboardGrab()");
}

//! @brief Enables or disables mouse grab.
//! @param[in] grabbed True to confine the mouse to the window, false to
//! release it.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMouseGrab() fails.
//! @details Confinement is to the whole window unless narrowed further by
//! setMouseRect(). Should only be called on the main thread.
void Window::setMouseGrab(bool grabbed)
{
    auto window = verifyAccess("Set mouse grab");

    if (SDL_SetWindowMouseGrab(window, grabbed) == false)
        throw ApiException("SDL_SetWindowMouseGrab()");
}

//! @brief Confines the mouse to a rectangle within the window.
//! @param[in] rect The region, in window coordinates, the mouse is confined to.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMouseRect() fails.
//! @details The confinement only takes effect while the window has mouse
//! focus, and applies whether or not setMouseGrab() has been enabled. Use
//! clearMouseRect() to remove it. Should only be called on the main thread.
void Window::setMouseRect(const SDL_Rect &rect)
{
    auto window = verifyAccess("Set mouse rect");

    if (SDL_SetWindowMouseRect(window, &rect) == false)
        throw ApiException("SDL_SetWindowMouseRect()");
}

//! @brief Removes any confinement of the mouse within the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMouseRect() fails.
//! @details Afterwards tryGetMouseRect() reports false. Any window-wide
//! grab set by setMouseGrab() remains in force. Should only be called on the
//! main thread.
void Window::clearMouseRect()
{
    auto window = verifyAccess("Clear mouse rect");

    if (SDL_SetWindowMouseRect(window, nullptr) == false)
        throw ApiException("SDL_SetWindowMouseRect(nullptr)");
}

//! @brief Sets whether the window can receive input focus.
//! @param[in] focusable True to allow the window to take focus, false to
//! prevent it.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFocusable() fails.
//! @details A non-focusable window still displays and receives mouse
//! events, which suits overlays and tool palettes. Should only be called on
//! the main thread.
void Window::setFocusable(bool focusable)
{
    auto window = verifyAccess("Set focusable");

    if (SDL_SetWindowFocusable(window, focusable) == false)
        throw ApiException("SDL_SetWindowFocusable()");
}

//! @brief Sets the transparent shape of the window from a surface.
//! @param[in] shape The surface whose alpha channel or colour key defines
//! which parts of the window are visible.
//! @throws ObjectNotBoundException If either the window or shape surface is
//! unbound.
//! @throws ApiException If SDL_SetWindowShape() fails.
//! @details The window must have been created with the
//! SDL_WINDOW_TRANSPARENT flag. Should only be called on the main thread.
void Window::setShape(const Surface &shape)
{
    auto window = verifyAccess("Set shape");
    auto shapeSurface = shape.verifyAccess("Provide shape surface");

    if (SDL_SetWindowShape(window, shapeSurface) == false)
        throw ApiException("SDL_SetWindowShape()");
}

//! @brief Sets the vsync interval used when presenting the window surface.
//! @param[in] vsync A positive count of vertical refreshes to wait for,
//! SDL_WINDOW_SURFACE_VSYNC_ADAPTIVE for late swap tearing, or
//! SDL_WINDOW_SURFACE_VSYNC_DISABLED to disable.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowSurfaceVSync() fails, which is how
//! an interval the platform does not support is reported.
//! @details Applies to the surface-based presentation path only, not to a
//! renderer attached to the window. Should only be called on the main
//! thread.
void Window::setSurfaceVSync(int vsync)
{
    auto window = verifyAccess("Set surface vsync");

    if (SDL_SetWindowSurfaceVSync(window, vsync) == false)
        throw ApiException("SDL_SetWindowSurfaceVSync()");
}

//! @brief Marks the window as modal (or not) with respect to its parent.
//! @param[in] modal True to block interaction with the parent window,
//! false to release it.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowModal() fails, which includes the
//! case of a window with no parent set.
//! @details The window must already have a parent, established either by
//! createPopup() or setParent(). Should only be called on the main thread.
void Window::setModal(bool modal)
{
    auto window = verifyAccess("Set modal");

    if (SDL_SetWindowModal(window, modal) == false)
        throw ApiException("SDL_SetWindowModal()");
}

//! @brief Sets the parent of the window.
//! @param[in] parent The window to become the parent of this one.
//! @throws ObjectNotBoundException If either window is unbound.
//! @throws ApiException If SDL_SetWindowParent() fails.
//! @details A child window is kept above its parent and is destroyed with
//! it. A window which is already modal cannot be reparented; clear the
//! modal state with setModal() first. Should only be called on the main
//! thread.
void Window::setParent(const Window &parent)
{
    auto window = verifyAccess("Set parent");
    auto parentWindow = parent.verifyAccess("Provide parent");

    if (SDL_SetWindowParent(window, parentWindow) == false)
        throw ApiException("SDL_SetWindowParent()");
}

//! @brief Warps the mouse cursor to a location within the window.
//! @param[in] x The horizontal position, in window coordinates.
//! @param[in] y The vertical position, in window coordinates.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details This generates a mouse motion event, and the underlying SDL
//! call reports no failure, so an unsupported platform passes silently.
//! Has no effect while relative mouse mode is active. Should only be called
//! on the main thread.
void Window::warpMouseInWindow(float x, float y)
{
    auto window = verifyAccess("Warp mouse");
    SDL_WarpMouseInWindow(window, x, y);
}

//! @brief Warps the mouse cursor to a location within the window.
//! @param[in] at The position, in window coordinates, to move the cursor to.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details This generates a mouse motion event, and the underlying SDL
//! call reports no failure, so an unsupported platform passes silently.
//! Has no effect while relative mouse mode is active. Should only be called
//! on the main thread.
void Window::warpMouseInWindow(const SDL_FPoint &at)
{
    auto window = verifyAccess("Warp mouse");
    SDL_WarpMouseInWindow(window, at.x, at.y);
}

//! @brief Registers a hit test callback for the window.
//! @param[in] callback The function SDL calls to classify a point within
//! the window, returning values such as SDL_HITTEST_DRAGGABLE or
//! SDL_HITTEST_RESIZE_TOPLEFT.
//! @param[in] callbackData An opaque value passed through to @p callback on
//! every invocation.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowHitTest() fails, which also covers
//! platforms where hit testing is unsupported.
//! @details This is how a borderless window is given draggable and
//! resizable regions of its own choosing. The callback runs during event
//! processing, so it should be cheap and must not block. Use clearHitTest()
//! to remove it. Should only be called on the main thread.
void Window::setHitTest(SDL_HitTest callback, void *callbackData)
{
    auto window = verifyAccess("Set hit test");

    if (SDL_SetWindowHitTest(window, callback, callbackData) == false)
        throw ApiException("SDL_SetWindowHitTest()");
}

//! @brief Removes any hit test callback previously registered for the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowHitTest() fails, which also covers
//! platforms where hit testing is unsupported - the dummy video driver
//! among them.
//! @details Should only be called on the main thread.
void Window::clearHitTest()
{
    auto window = verifyAccess("Clear hit test");

    if (SDL_SetWindowHitTest(window, nullptr, nullptr) == false)
        throw ApiException("SDL_SetWindowHitTest(nullptr)");
}

//! @brief Obtains the surface associated with the window, creating it if
//! necessary.
//! @return A non-owning Surface wrapper for the window's surface. SDL keeps
//! ownership, so it must not be freed by the caller.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSurface() fails.
//! @details The surface is invalidated whenever the window is resized, so
//! it must be re-obtained rather than cached across resize events, and it
//! must not be used on a window which has a renderer attached. Call
//! updateSurface() to present what has been drawn. Should only be called on
//! the main thread.
Surface Window::getSurface() const
{
    return Surface(verifyAccess("Get surface"));
}

//! @brief Copies the whole window surface to the screen.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_UpdateWindowSurface() fails, which includes
//! the case of a window with no surface created.
//! @details Call getSurface() at least once beforehand. Use
//! updateSurfaceRects() instead when only part of the window has changed.
//! Should only be called on the main thread.
void Window::updateSurface()
{
    auto window = verifyAccess("Update surface");

    if (SDL_UpdateWindowSurface(window) == false)
        throw ApiException("SDL_UpdateWindowSurface()");
}

//! @brief Copies specific rectangular regions of the window surface to the
//! screen.
//! @param[in] rects The array of regions to present. Must hold at least
//! @p count elements and must not be nullptr.
//! @param[in] count The count of regions to present.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_UpdateWindowSurfaceRects() fails, which
//! includes the case of a window with no surface created.
//! @details Presenting only the changed regions is cheaper than
//! updateSurface() when little of the window has altered. Call getSurface()
//! at least once beforehand. Should only be called on the main thread.
void Window::updateSurfaceRects(const SDL_Rect *rects, int count)
{
    auto window = verifyAccess("Update surface rects");

    if (SDL_UpdateWindowSurfaceRects(window, rects, count) == false)
        throw ApiException("SDL_UpdateWindowSurfaceRects()");
}

//! @brief Destroys the surface currently associated with the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_DestroyWindowSurface() fails.
//! @details Any Surface obtained from getSurface() is invalidated. This
//! must be done before attaching a renderer to a window which has been
//! using the surface path. Afterwards hasSurface() reports false. Should
//! only be called on the main thread.
void Window::destroySurface()
{
    auto window = verifyAccess("Destroy surface");

    if (SDL_DestroyWindowSurface(window) == false)
        throw ApiException("SDL_DestroyWindowSurface()");
}

//! @brief Gets a non-owning wrapper for the renderer associated with the
//! window.
//! @return A Renderer wrapper which does not own the underlying resource, so
//! destroying it will not destroy the renderer.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderer() fails, which includes the case
//! of a window with no renderer attached.
//! @details Should only be called on the main thread.
Renderer Window::getRenderer() const
{
    auto window = verifyAccess("Get renderer");
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    if (renderer == nullptr)
        throw ApiException("SDL_GetRenderer()");

    return Renderer(renderer, false);
}

//! @brief Creates and returns an owning wrapper for a new renderer bound to
//! the window.
//! @param[in] driverName The preferred render driver name, or nullptr to let
//! SDL choose the most suitable one.
//! @return A Renderer which owns the newly created resource.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateRenderer() fails, which includes
//! naming a driver that is unavailable.
//! @details A window supports only one renderer at a time. Should only be
//! called on the main thread.
Renderer Window::createRenderer(utf8_cptr_t driverName) const
{
    auto window = verifyAccess("Create renderer");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, driverName);

    if (renderer == nullptr)
        throw ApiException("SDL_CreateRenderer()");

    return Renderer(renderer, true);
}

//! @brief Creates and returns an owning wrapper for a new renderer configured
//! by a property set.
//! @param[in] props Properties describing the renderer to create. Note that
//! the target window must be named within @p props via
//! SDL_PROP_RENDERER_CREATE_WINDOW_POINTER; this object is only checked for
//! being bound.
//! @return A Renderer which owns the newly created resource.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateRendererWithProperties() fails.
//! @details Should only be called on the main thread.
Renderer Window::createRendererWithProperties(const PropertySet &props) const
{
    verifyAccess("Create renderer with properties");
    SDL_Renderer *renderer = SDL_CreateRendererWithProperties(props);

    if (renderer == nullptr)
        throw ApiException("SDL_CreateRendererWithProperties()");

    return Renderer(renderer, true);
}

//! @brief Disposes of any underlying window resource. Ownership is respected:
//! if this wrapper does not own the window, only the pointer is cleared.
void Window::release() noexcept
{
    auto window = std::exchange(_window, nullptr);
    bool owned = _owned;
    _owned = true;

    if ((window != nullptr) && owned)
        SDL_DestroyWindow(window);
}

//! @brief Disposes of any previously bound window and acquires a new window
//! resource from another wrapper.
Window &Window::operator=(Window &&rhs) noexcept
{
    if (_window == rhs._window)
        return *this;

    release();

    _window = std::exchange(rhs._window, nullptr);
    _owned = std::exchange(rhs._owned, true);

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
