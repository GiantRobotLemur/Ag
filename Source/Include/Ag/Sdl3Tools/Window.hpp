//! @file Ag/Sdl3Tools/Window.hpp
//! @brief The declaration of a class which wraps an SDL_Window resource.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SDL3_TOOLS_WINDOW_HPP_
#define HEADER_AG_SDL3_TOOLS_WINDOW_HPP_

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class PropertySet;
class Renderer;
class Surface;

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
    Window(SDL_Window *window, bool owned);
    Window(const Window &) = delete;
    Window(Window &&rhs) noexcept;
    ~Window();

    // Accessors
    bool isBound() const;
    bool isOwned() const;
    SDL_Window *get() const;
    SDL_WindowID getID() const;
    SDL_DisplayID getDisplayID() const;
    SDL_WindowFlags getFlags() const;
    PropertySet getProperties() const;
    float getPixelDensity() const;
    float getDisplayScale() const;
    SDL_PixelFormat getPixelFormat() const;
    bool getMouseGrab() const;
    bool getKeyboardGrab() const;
    bool getRelativeMouseMode() const;
    float getOpacity() const;
    int getSurfaceVSync() const;
    bool hasSurface() const;
    Window getParent() const;

    utf8_cptr_t getTitle() const;
    void setTitle(utf8_cptr_t title);
    void setIcon(const Surface &icon);

    void getPosition(int &x, int &y) const;
    SDL_Point getPosition() const;
    void setPosition(int x, int y);
    void setPosition(const SDL_Point &pos);
    void getSize(int &w, int &h) const;
    SDL_Point getSize() const;
    void setSize(int w, int h);
    void setSize(const SDL_Point &size);
    void getSizeInPixels(int &w, int &h) const;
    SDL_Point getSizeInPixels() const;
    void getMinimumSize(int &w, int &h) const;
    SDL_Point getMinimumSize() const;
    void setMinimumSize(int w, int h);
    void setMinimumSize(const SDL_Point &size);
    void getMaximumSize(int &w, int &h) const;
    SDL_Point getMaximumSize() const;
    void setMaximumSize(int w, int h);
    void setMaximumSize(const SDL_Point &size);
    void getBordersSize(int &top, int &left, int &bottom, int &right) const;
    void getAspectRatio(float &minRatio, float &maxRatio) const;
    void setAspectRatio(float minRatio, float maxRatio);
    void getSafeArea(SDL_Rect &area) const;
    SDL_Rect getSafeArea() const;

    const SDL_DisplayMode *getFullscreenMode() const;
    bool tryGetFullscreenMode(SDL_DisplayMode &mode) const;
    bool tryGetMouseRect(SDL_Rect &rect) const;

    // Operations
    void create(utf8_cptr_t title, int width, int height, SDL_WindowFlags flags);
    void create(utf8_cptr_t title, const SDL_Point &size, SDL_WindowFlags flags);
    void createFullScreen(utf8_cptr_t title, SDL_DisplayID display,
                          const SDL_DisplayMode &mode, SDL_WindowFlags flags);
    void createPopup(const Window &parent, int x, int y, int w, int h,
                     SDL_WindowFlags flags);
    void createPopup(const Window &parent, const SDL_Rect &area,
                     SDL_WindowFlags flags);
    void createWithProperties(const PropertySet &props);

    void show();
    void hide();
    void raise();
    void minimize();
    void maximize();
    void restore();
    void sync();
    void flash(SDL_FlashOperation operation);
    void setBordered(bool bordered);
    void setResizable(bool resizable);
    void setAlwaysOnTop(bool onTop);
    void setFullscreen(bool fullscreen);
    void setFullscreenMode(const SDL_DisplayMode &mode);
    void resetFullscreenMode();
    void setOpacity(float opacity);
    void setKeyboardGrab(bool grabbed);
    void setMouseGrab(bool grabbed);
    void setMouseRect(const SDL_Rect &rect);
    void clearMouseRect();
    void setFocusable(bool focusable);
    void setShape(const Surface &shape);
    void setSurfaceVSync(int vsync);
    void setModal(bool modal);
    void setParent(const Window &parent);
    void warpMouseInWindow(float x, float y);
    void warpMouseInWindow(const SDL_FPoint &at);
    void setHitTest(SDL_HitTest callback, void *callbackData);
    void clearHitTest();

    Surface getSurface() const;
    void updateSurface();
    void updateSurfaceRects(const SDL_Rect *rects, int count);
    void destroySurface();

    Renderer getRenderer() const;
    Renderer createRenderer(utf8_cptr_t driverName = nullptr) const;
    Renderer createRendererWithProperties(const PropertySet &props) const;

    void release() noexcept;
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&rhs) noexcept;
    SDL_Window *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Window *_window;
    bool _owned;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
