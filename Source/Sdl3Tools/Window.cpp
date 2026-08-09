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

//! @brief Gets the numeric identifier of the window, or 0 if unbound.
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

//! @brief Gets the flags of the window, or 0 if unbound.
SDL_WindowFlags Window::getFlags() const
{
    return (_window == nullptr) ? 0u : SDL_GetWindowFlags(_window);
}

//! @brief Gets the SDL property set associated with the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to return a property set.
PropertySet Window::getProperties() const
{
    auto window = verifyAccess("Get properties");
    SDL_PropertiesID id = SDL_GetWindowProperties(window);

    if (id == 0)
        throw ApiException("SDL_GetWindowProperties()");

    return PropertySet(id);
}

//! @brief Gets the pixel density of the window, or 0 if unbound.
float Window::getPixelDensity() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowPixelDensity(_window);
}

//! @brief Gets the display scale of the window, or 0 if unbound.
float Window::getDisplayScale() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowDisplayScale(_window);
}

//! @brief Gets the pixel format of the window, or SDL_PIXELFORMAT_UNKNOWN when
//! unbound.
SDL_PixelFormat Window::getPixelFormat() const
{
    return (_window == nullptr) ? SDL_PIXELFORMAT_UNKNOWN
                                : SDL_GetWindowPixelFormat(_window);
}

//! @brief Determines whether the mouse is grabbed by the window.
bool Window::getMouseGrab() const
{
    return (_window != nullptr) && SDL_GetWindowMouseGrab(_window);
}

//! @brief Determines whether the keyboard is grabbed by the window.
bool Window::getKeyboardGrab() const
{
    return (_window != nullptr) && SDL_GetWindowKeyboardGrab(_window);
}

//! @brief Determines whether relative mouse mode is active for the window.
bool Window::getRelativeMouseMode() const
{
    return (_window != nullptr) && SDL_GetWindowRelativeMouseMode(_window);
}

//! @brief Gets the opacity of the window, or 0 if unbound.
float Window::getOpacity() const
{
    return (_window == nullptr) ? 0.0f : SDL_GetWindowOpacity(_window);
}

//! @brief Gets the vsync interval for the window surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to return the vsync value.
int Window::getSurfaceVSync() const
{
    auto window = verifyAccess("Get surface vsync");
    int value = 0;

    if (SDL_GetWindowSurfaceVSync(window, &value) == false)
        throw ApiException("SDL_GetWindowSurfaceVSync()");

    return value;
}

//! @brief Determines whether the window currently has an associated surface.
bool Window::hasSurface() const
{
    return (_window != nullptr) && SDL_WindowHasSurface(_window);
}

//! @brief Gets a non-owning wrapper for the window's parent, if any.
Window Window::getParent() const
{
    auto window = verifyAccess("Get parent");
    SDL_Window *parent = SDL_GetWindowParent(window);

    return Window(parent, false);
}

//! @brief Gets the current title of the window, or an empty string if unbound.
utf8_cptr_t Window::getTitle() const
{
    return (_window == nullptr) ? "" : SDL_GetWindowTitle(_window);
}

//! @brief Sets the title of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowTitle() fails.
void Window::setTitle(utf8_cptr_t title)
{
    auto window = verifyAccess("Set title");

    if (SDL_SetWindowTitle(window, title) == false)
        throw ApiException("SDL_SetWindowTitle()");
}

//! @brief Sets the icon of the window from a surface.
//! @throws ObjectNotBoundException If either the window or icon surface is
//! unbound.
//! @throws ApiException If SDL_SetWindowIcon() fails.
void Window::setIcon(const Surface &icon)
{
    auto window = verifyAccess("Set icon");
    auto iconSurface = icon.verifyAccess("Provide window icon");

    if (SDL_SetWindowIcon(window, iconSurface) == false)
        throw ApiException("SDL_SetWindowIcon()");
}

//! @brief Gets the current position of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowPosition() fails.
void Window::getPosition(int &x, int &y) const
{
    auto window = verifyAccess("Get position");

    if (SDL_GetWindowPosition(window, &x, &y) == false)
        throw ApiException("SDL_GetWindowPosition()");
}

//! @brief Sets the position of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowPosition() fails.
void Window::setPosition(int x, int y)
{
    auto window = verifyAccess("Set position");

    if (SDL_SetWindowPosition(window, x, y) == false)
        throw ApiException("SDL_SetWindowPosition()");
}

//! @brief Gets the size of the window in logical units.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSize() fails.
void Window::getSize(int &w, int &h) const
{
    auto window = verifyAccess("Get size");

    if (SDL_GetWindowSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowSize()");
}

//! @brief Sets the size of the window in logical units.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowSize() fails.
void Window::setSize(int w, int h)
{
    auto window = verifyAccess("Set size");

    if (SDL_SetWindowSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowSize()");
}

//! @brief Gets the size of the window in raw pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSizeInPixels() fails.
void Window::getSizeInPixels(int &w, int &h) const
{
    auto window = verifyAccess("Get size in pixels");

    if (SDL_GetWindowSizeInPixels(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowSizeInPixels()");
}

//! @brief Gets the minimum size of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMinimumSize() fails.
void Window::getMinimumSize(int &w, int &h) const
{
    auto window = verifyAccess("Get minimum size");

    if (SDL_GetWindowMinimumSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowMinimumSize()");
}

//! @brief Sets the minimum size of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMinimumSize() fails.
void Window::setMinimumSize(int w, int h)
{
    auto window = verifyAccess("Set minimum size");

    if (SDL_SetWindowMinimumSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowMinimumSize()");
}

//! @brief Gets the maximum size of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowMaximumSize() fails.
void Window::getMaximumSize(int &w, int &h) const
{
    auto window = verifyAccess("Get maximum size");

    if (SDL_GetWindowMaximumSize(window, &w, &h) == false)
        throw ApiException("SDL_GetWindowMaximumSize()");
}

//! @brief Sets the maximum size of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMaximumSize() fails.
void Window::setMaximumSize(int w, int h)
{
    auto window = verifyAccess("Set maximum size");

    if (SDL_SetWindowMaximumSize(window, w, h) == false)
        throw ApiException("SDL_SetWindowMaximumSize()");
}

//! @brief Gets the size of the platform-drawn window borders.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowBordersSize() fails.
void Window::getBordersSize(int &top, int &left, int &bottom, int &right) const
{
    auto window = verifyAccess("Get borders size");

    if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) == false)
        throw ApiException("SDL_GetWindowBordersSize()");
}

//! @brief Gets the aspect ratio bounds for the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowAspectRatio() fails.
void Window::getAspectRatio(float &minRatio, float &maxRatio) const
{
    auto window = verifyAccess("Get aspect ratio");

    if (SDL_GetWindowAspectRatio(window, &minRatio, &maxRatio) == false)
        throw ApiException("SDL_GetWindowAspectRatio()");
}

//! @brief Sets the aspect ratio bounds for the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowAspectRatio() fails.
void Window::setAspectRatio(float minRatio, float maxRatio)
{
    auto window = verifyAccess("Set aspect ratio");

    if (SDL_SetWindowAspectRatio(window, minRatio, maxRatio) == false)
        throw ApiException("SDL_SetWindowAspectRatio()");
}

//! @brief Gets the safe-area rectangle within the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSafeArea() fails.
void Window::getSafeArea(SDL_Rect &area) const
{
    auto window = verifyAccess("Get safe area");

    if (SDL_GetWindowSafeArea(window, &area) == false)
        throw ApiException("SDL_GetWindowSafeArea()");
}

//! @brief Gets the current fullscreen display mode, or nullptr if none.
const SDL_DisplayMode *Window::getFullscreenMode() const
{
    return (_window == nullptr) ? nullptr : SDL_GetWindowFullscreenMode(_window);
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
//! @param[in] flags Options defining style and usage of the new window.
void Window::create(utf8_cptr_t title, int width, int height, SDL_WindowFlags flags)
{
    release();

    _window = SDL_CreateWindow(title, width, height, flags);
    _owned = true;

    if (_window == nullptr)
        throw ApiException("SDL_CreateWindow()");
}

//! @brief Creates a new window which covers an entire screen, perhaps changing
//! the display mode.
//! @param[in] title The title of the window which maybe displayed elsewhere in the system.
//! @param[in] display The display for the window to acquire.
//! @param[in] mode The display mode to set that display to.
//! @param[in] flags Option flags determining behaviour of the window.
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

//! @brief Creates a new window from a fully specified property set.
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
void Window::show()
{
    auto window = verifyAccess("Show");

    if (SDL_ShowWindow(window) == false)
        throw ApiException("SDL_ShowWindow()");
}

//! @brief Hides the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_HideWindow() fails.
void Window::hide()
{
    auto window = verifyAccess("Hide");

    if (SDL_HideWindow(window) == false)
        throw ApiException("SDL_HideWindow()");
}

//! @brief Raises the window above other windows.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RaiseWindow() fails.
void Window::raise()
{
    auto window = verifyAccess("Raise");

    if (SDL_RaiseWindow(window) == false)
        throw ApiException("SDL_RaiseWindow()");
}

//! @brief Minimizes the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_MinimizeWindow() fails.
void Window::minimize()
{
    auto window = verifyAccess("Minimize");

    if (SDL_MinimizeWindow(window) == false)
        throw ApiException("SDL_MinimizeWindow()");
}

//! @brief Maximizes the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_MaximizeWindow() fails.
void Window::maximize()
{
    auto window = verifyAccess("Maximize");

    if (SDL_MaximizeWindow(window) == false)
        throw ApiException("SDL_MaximizeWindow()");
}

//! @brief Restores a minimized or maximized window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RestoreWindow() fails.
void Window::restore()
{
    auto window = verifyAccess("Restore");

    if (SDL_RestoreWindow(window) == false)
        throw ApiException("SDL_RestoreWindow()");
}

//! @brief Blocks until pending window state changes have been applied.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SyncWindow() fails.
void Window::sync()
{
    auto window = verifyAccess("Sync");

    if (SDL_SyncWindow(window) == false)
        throw ApiException("SDL_SyncWindow()");
}

//! @brief Requests the window flash to indicate a need for attention.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FlashWindow() fails.
void Window::flash(SDL_FlashOperation operation)
{
    auto window = verifyAccess("Flash");

    if (SDL_FlashWindow(window, operation) == false)
        throw ApiException("SDL_FlashWindow()");
}

//! @brief Enables or disables the window border.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowBordered() fails.
void Window::setBordered(bool bordered)
{
    auto window = verifyAccess("Set bordered");

    if (SDL_SetWindowBordered(window, bordered) == false)
        throw ApiException("SDL_SetWindowBordered()");
}

//! @brief Enables or disables window resizing.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowResizable() fails.
void Window::setResizable(bool resizable)
{
    auto window = verifyAccess("Set resizable");

    if (SDL_SetWindowResizable(window, resizable) == false)
        throw ApiException("SDL_SetWindowResizable()");
}

//! @brief Sets whether the window should stay above other windows.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowAlwaysOnTop() fails.
void Window::setAlwaysOnTop(bool onTop)
{
    auto window = verifyAccess("Set always on top");

    if (SDL_SetWindowAlwaysOnTop(window, onTop) == false)
        throw ApiException("SDL_SetWindowAlwaysOnTop()");
}

//! @brief Toggles fullscreen mode on the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFullscreen() fails.
void Window::setFullscreen(bool fullscreen)
{
    auto window = verifyAccess("Set fullscreen");

    if (SDL_SetWindowFullscreen(window, fullscreen) == false)
        throw ApiException("SDL_SetWindowFullscreen()");
}

//! @brief Sets the display mode used in fullscreen.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFullscreenMode() fails.
void Window::setFullscreenMode(const SDL_DisplayMode *mode)
{
    auto window = verifyAccess("Set fullscreen mode");

    if (SDL_SetWindowFullscreenMode(window, mode) == false)
        throw ApiException("SDL_SetWindowFullscreenMode()");
}

//! @brief Sets the opacity of the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowOpacity() fails.
void Window::setOpacity(float opacity)
{
    auto window = verifyAccess("Set opacity");

    if (SDL_SetWindowOpacity(window, opacity) == false)
        throw ApiException("SDL_SetWindowOpacity()");
}

//! @brief Enables or disables keyboard grab.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowKeyboardGrab() fails.
void Window::setKeyboardGrab(bool grabbed)
{
    auto window = verifyAccess("Set keyboard grab");

    if (SDL_SetWindowKeyboardGrab(window, grabbed) == false)
        throw ApiException("SDL_SetWindowKeyboardGrab()");
}

//! @brief Enables or disables mouse grab.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMouseGrab() fails.
void Window::setMouseGrab(bool grabbed)
{
    auto window = verifyAccess("Set mouse grab");

    if (SDL_SetWindowMouseGrab(window, grabbed) == false)
        throw ApiException("SDL_SetWindowMouseGrab()");
}

//! @brief Confines the mouse to a rectangle within the window, or clears the
//! confinement when @p rect is nullptr.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowMouseRect() fails.
void Window::setMouseRect(const SDL_Rect *rect)
{
    auto window = verifyAccess("Set mouse rect");

    if (SDL_SetWindowMouseRect(window, rect) == false)
        throw ApiException("SDL_SetWindowMouseRect()");
}

//! @brief Sets whether the window can receive focus.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowFocusable() fails.
void Window::setFocusable(bool focusable)
{
    auto window = verifyAccess("Set focusable");

    if (SDL_SetWindowFocusable(window, focusable) == false)
        throw ApiException("SDL_SetWindowFocusable()");
}

//! @brief Sets the transparent shape of the window from a surface.
//! @throws ObjectNotBoundException If either the window or shape surface is
//! unbound.
//! @throws ApiException If SDL_SetWindowShape() fails.
void Window::setShape(const Surface &shape)
{
    auto window = verifyAccess("Set shape");
    auto shapeSurface = shape.verifyAccess("Provide shape surface");

    if (SDL_SetWindowShape(window, shapeSurface) == false)
        throw ApiException("SDL_SetWindowShape()");
}

//! @brief Sets the vsync interval for the window's surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowSurfaceVSync() fails.
void Window::setSurfaceVSync(int vsync)
{
    auto window = verifyAccess("Set surface vsync");

    if (SDL_SetWindowSurfaceVSync(window, vsync) == false)
        throw ApiException("SDL_SetWindowSurfaceVSync()");
}

//! @brief Marks the window as modal (or not) with respect to its parent.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowModal() fails.
void Window::setModal(bool modal)
{
    auto window = verifyAccess("Set modal");

    if (SDL_SetWindowModal(window, modal) == false)
        throw ApiException("SDL_SetWindowModal()");
}

//! @brief Sets the parent of the window.
//! @throws ObjectNotBoundException If either window is unbound.
//! @throws ApiException If SDL_SetWindowParent() fails.
void Window::setParent(const Window &parent)
{
    auto window = verifyAccess("Set parent");
    auto parentWindow = parent.verifyAccess("Provide parent");

    if (SDL_SetWindowParent(window, parentWindow) == false)
        throw ApiException("SDL_SetWindowParent()");
}

//! @brief Warps the mouse cursor to a location within the window.
//! @throws ObjectNotBoundException If the object is unbound.
void Window::warpMouseInWindow(float x, float y)
{
    auto window = verifyAccess("Warp mouse");
    SDL_WarpMouseInWindow(window, x, y);
}

//! @brief Registers a hit test callback for the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetWindowHitTest() fails.
void Window::setHitTest(SDL_HitTest callback, void *callbackData)
{
    auto window = verifyAccess("Set hit test");

    if (SDL_SetWindowHitTest(window, callback, callbackData) == false)
        throw ApiException("SDL_SetWindowHitTest()");
}

//! @brief Obtains the surface associated with the window, creating it if
//! necessary.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetWindowSurface() fails.
Surface Window::getSurface() const
{
    return Surface(verifyAccess("Get surface"));
}

//! @brief Presents any changes made to the window surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_UpdateWindowSurface() fails.
void Window::updateSurface()
{
    auto window = verifyAccess("Update surface");

    if (SDL_UpdateWindowSurface(window) == false)
        throw ApiException("SDL_UpdateWindowSurface()");
}

//! @brief Presents specific rectangular regions of the window surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_UpdateWindowSurfaceRects() fails.
void Window::updateSurfaceRects(const SDL_Rect *rects, int count)
{
    auto window = verifyAccess("Update surface rects");

    if (SDL_UpdateWindowSurfaceRects(window, rects, count) == false)
        throw ApiException("SDL_UpdateWindowSurfaceRects()");
}

//! @brief Destroys the surface currently associated with the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_DestroyWindowSurface() fails.
void Window::destroySurface()
{
    auto window = verifyAccess("Destroy surface");

    if (SDL_DestroyWindowSurface(window) == false)
        throw ApiException("SDL_DestroyWindowSurface()");
}

//! @brief Gets a non-owning wrapper for the renderer associated with the
//! window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderer() fails.
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
//! SDL choose.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateRenderer() fails.
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
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateRendererWithProperties() fails.
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
    _owned = rhs._owned;
    rhs._owned = true;

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
