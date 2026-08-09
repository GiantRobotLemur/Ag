//! @file Sdl3Tools/Renderer.cpp
//! @brief The definition of a wrapper for the SDL3 2D SDL_Renderer resource.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
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
#include "Ag/Sdl3Tools/Texture.hpp"
#include "Ag/Sdl3Tools/Window.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Renderer Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an unbound Renderer wrapper.
Renderer::Renderer() :
    _renderer(nullptr),
    _owned(true)
{
}

//! @brief Wraps an existing SDL_Renderer resource.
//! @param[in] renderer The renderer pointer to wrap, possibly nullptr.
//! @param[in] owned True if this wrapper should destroy the renderer on
//! release. Set false when wrapping a renderer whose lifetime is managed
//! elsewhere (e.g. returned by SDL_GetRenderer).
Renderer::Renderer(SDL_Renderer *renderer, bool owned) :
    _renderer(renderer),
    _owned(owned)
{
}

//! @brief Acquires a renderer resource from another wrapper.
Renderer::Renderer(Renderer &&rhs) noexcept :
    _renderer(std::exchange(rhs._renderer, nullptr)),
    _owned(rhs._owned)
{
    rhs._owned = true;
}

//! @brief Ensures the renderer resource is destroyed at wrapper destruction.
Renderer::~Renderer()
{
    release();
}

//! @brief Determines whether the wrapper holds an underlying renderer.
bool Renderer::isBound() const
{
    return _renderer != nullptr;
}

//! @brief Indicates whether this wrapper owns the renderer.
bool Renderer::isOwned() const
{
    return _owned;
}

//! @brief Gets the raw underlying SDL_Renderer pointer, or nullptr if unbound.
SDL_Renderer *Renderer::get() const
{
    return _renderer;
}

//! @brief Gets the name of the render driver backing the renderer.
//! @return The driver name, or an empty string if the object is unbound or
//! SDL could not supply a name.
//! @details Never returns nullptr, so the result is always safe to print.
//! It is safe to call this from any thread.
utf8_cptr_t Renderer::getName() const
{
    if (_renderer == nullptr)
        return "";

    utf8_cptr_t name = SDL_GetRendererName(_renderer);
    return (name == nullptr) ? "" : name;
}

//! @brief Gets a non-owning wrapper for the window associated with the
//! renderer.
//! @return A Window wrapper which does not own the underlying resource, so
//! destroying it will not destroy the window.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderWindow() fails, which includes the
//! case of a software renderer created over a surface rather than a window.
Window Renderer::getWindow() const
{
    auto renderer = verifyAccess("Get window");
    SDL_Window *window = SDL_GetRenderWindow(renderer);

    if (window == nullptr)
        throw ApiException("SDL_GetRenderWindow()");

    return Window(window, false);
}

//! @brief Gets the SDL property set associated with the renderer.
//! @return A PropertySet giving access to read-only renderer properties such
//! as SDL_PROP_RENDERER_NAME_STRING, SDL_PROP_RENDERER_VSYNC_NUMBER and
//! SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRendererProperties() fails.
//! @details Some properties, such as SDL_PROP_RENDERER_HDR_ENABLED_BOOLEAN,
//! can change while the renderer lives, so the set should be re-queried
//! rather than cached.
PropertySet Renderer::getProperties() const
{
    auto renderer = verifyAccess("Get properties");
    SDL_PropertiesID id = SDL_GetRendererProperties(renderer);

    if (id == 0)
        throw ApiException("SDL_GetRendererProperties()");

    return PropertySet(id);
}

//! @brief Gets the fixed output size of the renderer, in pixels.
//! @param[out] w Receives the width, in pixels.
//! @param[out] h Receives the height, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderOutputSize() fails.
//! @details This is the true output size, ignoring any render target which
//! is currently set and any logical presentation. Use
//! getCurrentOutputSize() for the size adjusted for those. Should only be
//! called on the main thread.
void Renderer::getOutputSize(int &w, int &h) const
{
    auto renderer = verifyAccess("Get output size");

    if (SDL_GetRenderOutputSize(renderer, &w, &h) == false)
        throw ApiException("SDL_GetRenderOutputSize()");
}

//! @brief Gets the fixed output size of the renderer, in pixels.
//! @param[out] size Receives the width and height, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderOutputSize() fails.
//! @details This is the true output size, ignoring any render target which
//! is currently set and any logical presentation. Use
//! getCurrentOutputSize() for the size adjusted for those. Should only be
//! called on the main thread.
void Renderer::getOutputSize(SDL_Point &size) const
{
    auto renderer = verifyAccess("Get output size");

    if (SDL_GetRenderOutputSize(renderer, &size.x, &size.y) == false)
        throw ApiException("SDL_GetRenderOutputSize()");
}

//! @brief Gets the current output size of the renderer, in pixels, accounting
//! for logical presentation.
//! @param[out] w Receives the current width, in pixels.
//! @param[out] h Receives the current height, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetCurrentRenderOutputSize() fails.
//! @details If a render target is active this reports the size of that
//! target, otherwise it reports the same size as getOutputSize(). Either
//! way the result is adjusted by the current logical presentation state.
//! Should only be called on the main thread.
void Renderer::getCurrentOutputSize(int &w, int &h) const
{
    auto renderer = verifyAccess("Get current output size");

    if (SDL_GetCurrentRenderOutputSize(renderer, &w, &h) == false)
        throw ApiException("SDL_GetCurrentRenderOutputSize()");
}

//! @brief Gets the current output size of the renderer, in pixels, accounting
//! for logical presentation.
//! @param[out] size Receives the current width and height, in pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetCurrentRenderOutputSize() fails.
//! @details If a render target is active this reports the size of that
//! target, otherwise it reports the same size as getOutputSize(). Either
//! way the result is adjusted by the current logical presentation state.
//! Should only be called on the main thread.
void Renderer::getCurrentOutputSize(SDL_Point &size) const
{
    auto renderer = verifyAccess("Get current output size");

    if (SDL_GetCurrentRenderOutputSize(renderer, &size.x, &size.y) == false)
        throw ApiException("SDL_GetCurrentRenderOutputSize()");
}

//! @brief Gets the safe-area rectangle within the current view port.
//! @param[out] area Receives the region which is safe to use for interactive
//! content.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderSafeArea() fails.
//! @details Some devices obscure parts of the screen with on-screen
//! controls, curved edges, camera notches or TV overscan. Rendering should
//! continue into the rest of the target, but visually important or
//! interactive content should be confined to @p area. Should only be called
//! on the main thread.
void Renderer::getSafeArea(SDL_Rect &area) const
{
    auto renderer = verifyAccess("Get safe area");

    if (SDL_GetRenderSafeArea(renderer, &area) == false)
        throw ApiException("SDL_GetRenderSafeArea()");
}

//! @brief Gets the current view port rectangle.
//! @param[out] viewport Receives the drawing area of the current render
//! target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderViewport() fails.
//! @details Each render target carries its own view port; this reports the
//! one belonging to the current target. Use isViewportSet() to distinguish
//! an explicitly set rectangle from the whole-target default. Should only be
//! called on the main thread.
void Renderer::getViewport(SDL_Rect &viewport) const
{
    auto renderer = verifyAccess("Get view port");

    if (SDL_GetRenderViewport(renderer, &viewport) == false)
        throw ApiException("SDL_GetRenderViewport()");
}

//! @brief Sets the drawing area within the current render target.
//! @param[in] viewport The drawing area. Its width and height must be zero
//! or greater.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderViewport() fails.
//! @details Drawing clips to this area, independently of any clip rectangle
//! set with setClipRect(), and the top left of the area becomes coordinate
//! (0, 0) for subsequent drawing. Each render target carries its own
//! view port, and the view port is reset whenever the render target changes.
//! Use resetViewport() to return to drawing over the entire target. Should
//! only be called on the main thread.
void Renderer::setViewport(const SDL_Rect &viewport)
{
    auto renderer = verifyAccess("Set view port");

    if (SDL_SetRenderViewport(renderer, &viewport) == false)
        throw ApiException("SDL_SetRenderViewport()");
}

//! @brief Resets the current view port rectangle, to the entire render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderViewport() fails.
//! @details After this call isViewportSet() reports false and drawing
//! coordinates are relative to the top left of the whole target. Should only
//! be called on the main thread.
void Renderer::resetViewport()
{
    auto renderer = verifyAccess("Reset view port");

    if (SDL_SetRenderViewport(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderViewport(nullptr)");
}

//! @brief Determines whether an explicit view port has been set.
//! @retval true The view port was set to a specific rectangle.
//! @retval false The object is unbound, or the view port covers the entire
//! render target.
//! @details Useful when saving and restoring the view port, in order to know
//! whether to restore a rectangle or call resetViewport(). Note that the
//! view port is always reset when the render target changes. Should only be
//! called on the main thread.
bool Renderer::isViewportSet() const
{
    return (_renderer != nullptr) && SDL_RenderViewportSet(_renderer);
}

//! @brief Attempts to obtain the current clip rectangle.
//! @param[out] clip Receives the clip rectangle, relative to the view port,
//! on success. Left untouched otherwise.
//! @retval true A clip rectangle was returned.
//! @retval false The object is unbound, or no clip rectangle is set.
//! @details Each render target carries its own clip rectangle; this reports
//! the one belonging to the current target. Should only be called on the
//! main thread.
bool Renderer::tryGetClipRect(SDL_Rect &clip) const
{
    if ((_renderer == nullptr) || (SDL_RenderClipEnabled(_renderer) == false))
        return false;

    return SDL_GetRenderClipRect(_renderer, &clip);
}

//! @brief Sets the clip rectangle for rendering on the current target.
//! @param[in] clip The clip area, expressed relative to the current
//! view port rather than to the render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderClipRect() fails.
//! @details Clipping applies in addition to the clipping already performed
//! by the view port. Each render target carries its own clip rectangle. Use
//! resetClipRect() to disable clipping again. Should only be called on the
//! main thread.
void Renderer::setClipRect(const SDL_Rect &clip)
{
    auto renderer = verifyAccess("Set clip rect");

    if (SDL_SetRenderClipRect(renderer, &clip) == false)
        throw ApiException("SDL_SetRenderClipRect()");
}

//! @brief Disables clipping on the current render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderClipRect() fails.
//! @details After this call clipEnabled() reports false and drawing is
//! bounded only by the view port. Should only be called on the main thread.
void Renderer::resetClipRect()
{
    auto renderer = verifyAccess("Set clip rect");

    if (SDL_SetRenderClipRect(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderClipRect()");
}

//! @brief Determines whether clipping is enabled on the current render
//! target.
//! @retval true A clip rectangle is in force.
//! @retval false The object is unbound, or clipping is disabled.
//! @details Each render target carries its own clip rectangle. Should only
//! be called on the main thread.
bool Renderer::clipEnabled() const
{
    return (_renderer != nullptr) && SDL_RenderClipEnabled(_renderer);
}

//! @brief Gets the scale applied to drawing coordinates on the current
//! render target.
//! @param[out] scaleX Receives the horizontal scaling factor.
//! @param[out] scaleY Receives the vertical scaling factor.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderScale() fails.
//! @details Each render target carries its own scale. Should only be called
//! on the main thread.
void Renderer::getScale(float &scaleX, float &scaleY) const
{
    auto renderer = verifyAccess("Get scale");

    if (SDL_GetRenderScale(renderer, &scaleX, &scaleY) == false)
        throw ApiException("SDL_GetRenderScale()");
}

//! @brief Gets the scale applied to drawing coordinates on the current
//! render target.
//! @param[out] scale Receives the horizontal scaling factor in its x
//! component and the vertical factor in its y component.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderScale() fails.
//! @details Each render target carries its own scale. Should only be called
//! on the main thread.
void Renderer::getScale(SDL_FPoint &scale) const
{
    auto renderer = verifyAccess("Get scale");

    if (SDL_GetRenderScale(renderer, &scale.x, &scale.y) == false)
        throw ApiException("SDL_GetRenderScale()");
}

//! @brief Sets the scale applied to drawing coordinates on the current
//! render target.
//! @param[in] scaleX The horizontal scaling factor.
//! @param[in] scaleY The vertical scaling factor.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderScale() fails.
//! @details Drawing coordinates are multiplied by these factors before the
//! renderer uses them, which allows resolution-independent drawing from a
//! single coordinate system. Integer factors give the best results, as
//! fractional ones leave the backend to resolve scaling or sub-pixel drawing
//! using its quality hints. Each render target carries its own scale.
//! Should only be called on the main thread.
void Renderer::setScale(float scaleX, float scaleY)
{
    auto renderer = verifyAccess("Set scale");

    if (SDL_SetRenderScale(renderer, scaleX, scaleY) == false)
        throw ApiException("SDL_SetRenderScale()");
}

//! @brief Sets the scale applied to drawing coordinates on the current
//! render target.
//! @param[in] scale The horizontal scaling factor in its x component and
//! the vertical factor in its y component.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderScale() fails.
//! @details Drawing coordinates are multiplied by these factors before the
//! renderer uses them, which allows resolution-independent drawing from a
//! single coordinate system. Integer factors give the best results, as
//! fractional ones leave the backend to resolve scaling or sub-pixel drawing
//! using its quality hints. Each render target carries its own scale.
//! Should only be called on the main thread.
void Renderer::setScale(const SDL_FPoint &scale)
{
    auto renderer = verifyAccess("Set scale");

    if (SDL_SetRenderScale(renderer, scale.x, scale.y) == false)
        throw ApiException("SDL_SetRenderScale()");
}

//! @brief Gets the current draw colour as 8-bit RGBA values.
//! @param[out] colour Receives the red, green, blue and alpha components.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderDrawColor() fails.
//! @details Should only be called on the main thread.
void Renderer::getDrawColour(SDL_Color &colour) const
{
    auto renderer = verifyAccess("Get draw colour");

    if (SDL_GetRenderDrawColor(renderer, &colour.r, &colour.g,
                               &colour.b, &colour.a) == false)
        throw ApiException("SDL_GetRenderDrawColor()");
}

//! @brief Gets the current draw colour as 8-bit RGBA values.
//! @param[out] r Receives the red component.
//! @param[out] g Receives the green component.
//! @param[out] b Receives the blue component.
//! @param[out] a Receives the alpha component.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderDrawColor() fails.
//! @details Should only be called on the main thread.
void Renderer::getDrawColour(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const
{
    auto renderer = verifyAccess("Get draw colour");

    if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) == false)
        throw ApiException("SDL_GetRenderDrawColor()");
}

//! @brief Sets the current draw colour using 8-bit RGBA values.
//! @param[in] colour The colour used to draw and fill rectangles, lines and
//! points, and to clear the target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderDrawColor() fails.
//! @details How the alpha component is applied depends on the current
//! blend mode, set via setDrawBlendMode(). Should only be called on the
//! main thread.
void Renderer::setDrawColour(const SDL_Color &colour)
{
    auto renderer = verifyAccess("Set draw colour");

    if (SDL_SetRenderDrawColor(renderer, colour.r, colour.g,
                               colour.b, colour.a) == false)
        throw ApiException("SDL_SetRenderDrawColor()");
}

//! @brief Sets the current draw colour using 8-bit RGBA values.
//! @param[in] r The red component.
//! @param[in] g The green component.
//! @param[in] b The blue component.
//! @param[in] a The alpha component, SDL_ALPHA_OPAQUE (255) by default.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderDrawColor() fails.
//! @details The colour is used to draw and fill rectangles, lines and
//! points, and to clear the target. How @p a is applied depends on the
//! current blend mode, set via setDrawBlendMode(). Should only be called on
//! the main thread.
void Renderer::setDrawColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    auto renderer = verifyAccess("Set draw colour");

    if (SDL_SetRenderDrawColor(renderer, r, g, b, a) == false)
        throw ApiException("SDL_SetRenderDrawColor()");
}

//! @brief Gets the current draw colour as normalised float RGBA values.
//! @param[out] colour Receives the red, green, blue and alpha components,
//! normalised to the range 0.0 to 1.0.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderDrawColorFloat() fails.
//! @details Should only be called on the main thread.
void Renderer::getDrawColourFloat(SDL_FColor &colour) const
{
    auto renderer = verifyAccess("Get draw colour (float)");

    if (SDL_GetRenderDrawColorFloat(renderer, &colour.r, &colour.g,
                                    &colour.b, &colour.a) == false)
        throw ApiException("SDL_GetRenderDrawColorFloat()");
}

//! @brief Gets the current draw colour as normalised float RGBA values.
//! @param[out] r Receives the red component, normalised to 0.0 to 1.0.
//! @param[out] g Receives the green component.
//! @param[out] b Receives the blue component.
//! @param[out] a Receives the alpha component.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderDrawColorFloat() fails.
//! @details Should only be called on the main thread.
void Renderer::getDrawColourFloat(float &r, float &g, float &b, float &a) const
{
    auto renderer = verifyAccess("Get draw colour (float)");

    if (SDL_GetRenderDrawColorFloat(renderer, &r, &g, &b, &a) == false)
        throw ApiException("SDL_GetRenderDrawColorFloat()");
}

//! @brief Sets the current draw colour using normalised float RGBA values.
//! @param[in] colour The colour used to draw and fill rectangles, lines and
//! points, and to clear the target, with components normalised to the range
//! 0.0 to 1.0.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderDrawColorFloat() fails.
//! @details How the alpha component is applied depends on the current blend
//! mode, set via setDrawBlendMode(). Should only be called on the main
//! thread.
void Renderer::setDrawColourFloat(const SDL_FColor &colour)
{
    auto renderer = verifyAccess("Set draw colour (float)");

    if (SDL_SetRenderDrawColorFloat(renderer, colour.r, colour.g,
                                    colour.b, colour.a) == false)
        throw ApiException("SDL_SetRenderDrawColorFloat()");
}

//! @brief Sets the current draw colour using normalised float RGBA values.
//! @param[in] r The red component, normalised to the range 0.0 to 1.0.
//! @param[in] g The green component.
//! @param[in] b The blue component.
//! @param[in] a The alpha component, fully opaque (1.0) by default.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderDrawColorFloat() fails.
//! @details The colour is used to draw and fill rectangles, lines and
//! points, and to clear the target. How @p a is applied depends on the
//! current blend mode, set via setDrawBlendMode(). Should only be called on
//! the main thread.
void Renderer::setDrawColourFloat(float r, float g, float b, float a)
{
    auto renderer = verifyAccess("Set draw colour (float)");

    if (SDL_SetRenderDrawColorFloat(renderer, r, g, b, a) == false)
        throw ApiException("SDL_SetRenderDrawColorFloat()");
}

//! @brief Gets the blend mode used when filling and drawing lines.
//! @return The current SDL_BlendMode.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderDrawBlendMode() fails.
//! @details This may differ from the mode passed to setDrawBlendMode() if
//! the backend did not support that mode exactly. Should only be called on
//! the main thread.
SDL_BlendMode Renderer::getDrawBlendMode() const
{
    auto renderer = verifyAccess("Get draw blend mode");
    SDL_BlendMode mode = SDL_BLENDMODE_NONE;

    if (SDL_GetRenderDrawBlendMode(renderer, &mode) == false)
        throw ApiException("SDL_GetRenderDrawBlendMode()");

    return mode;
}

//! @brief Sets the blend mode used when filling and drawing lines.
//! @param[in] mode The SDL_BlendMode to blend with.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderDrawBlendMode() fails.
//! @details If the backend does not support @p mode, the closest supported
//! mode is chosen instead without reporting an error, so read the mode back
//! with getDrawBlendMode() if the exact value matters. Should only be called
//! on the main thread.
void Renderer::setDrawBlendMode(SDL_BlendMode mode)
{
    auto renderer = verifyAccess("Set draw blend mode");

    if (SDL_SetRenderDrawBlendMode(renderer, mode) == false)
        throw ApiException("SDL_SetRenderDrawBlendMode()");
}

//! @brief Gets the current colour scale multiplier applied when drawing.
//! @return The colour scale value.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderColorScale() fails.
//! @details Should only be called on the main thread.
float Renderer::getColourScale() const
{
    auto renderer = verifyAccess("Get colour scale");
    float scale = 1.0f;

    if (SDL_GetRenderColorScale(renderer, &scale) == false)
        throw ApiException("SDL_GetRenderColorScale()");

    return scale;
}

//! @brief Sets the colour scale multiplier applied when drawing.
//! @param[in] scale The colour scale value.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderColorScale() fails.
//! @details The scale is multiplied into each pixel colour as it is
//! rendered, which is useful for adjusting brightness during HDR rendering,
//! or for HDR video shown on an SDR display. It affects colour brightness
//! only and leaves the alpha channel untouched. Should only be called on the
//! main thread.
void Renderer::setColourScale(float scale)
{
    auto renderer = verifyAccess("Set colour scale");

    if (SDL_SetRenderColorScale(renderer, scale) == false)
        throw ApiException("SDL_SetRenderColorScale()");
}

//! @brief Gets the vsync interval used by the renderer.
//! @return The vertical refresh sync interval: a positive count of refreshes
//! to wait for, SDL_RENDERER_VSYNC_ADAPTIVE for late swap tearing, or
//! SDL_RENDERER_VSYNC_DISABLED when vsync is off.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderVSync() fails.
//! @details Should only be called on the main thread.
int Renderer::getVSync() const
{
    auto renderer = verifyAccess("Get vsync");
    int value = 0;

    if (SDL_GetRenderVSync(renderer, &value) == false)
        throw ApiException("SDL_GetRenderVSync()");

    return value;
}

//! @brief Sets the vsync interval used by the renderer.
//! @param[in] vsync The vertical refresh sync interval: 1 to present on
//! every vertical refresh, 2 for every second refresh and so on,
//! SDL_RENDERER_VSYNC_ADAPTIVE for late swap tearing, or
//! SDL_RENDERER_VSYNC_DISABLED to disable.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderVSync() fails, which is how an
//! interval the driver does not support is reported.
//! @details A newly created renderer defaults to
//! SDL_RENDERER_VSYNC_DISABLED. Not every driver supports every value, so
//! treat the exception as a signal to fall back rather than as a fatal
//! error. Should only be called on the main thread.
void Renderer::setVSync(int vsync)
{
    auto renderer = verifyAccess("Set vsync");

    if (SDL_SetRenderVSync(renderer, vsync) == false)
        throw ApiException("SDL_SetRenderVSync()");
}

//! @brief Set a device-independent resolution and presentation mode for rendering.
//! @param[in] w The horizontal size of the logical resolution.
//! @param[in] h The vertical size of the logical resolution.
//! @param[in] mode The presentation mode used, or
//! SDL_LOGICAL_PRESENTATION_DISABLED to draw at the full pixel resolution of
//! the render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderLogicalPresentation() fails.
//! @details The renderer then behaves as though the current render target
//! were always @p w by @p h, scaling to the real resolution as needed. This
//! suits games written against a fixed size which should still fill a
//! resized window or a high-DPI display. The state belongs to the current
//! render target, and it is safe to toggle mid-frame - for example turning
//! presentation off while drawing text so glyphs stay sharp. When drawing to
//! a window, letterboxing is written into the framebuffer during present(),
//! so re-enable presentation before presenting to avoid artefacts left over
//! from earlier frames. Letterboxing is never drawn into texture targets, so
//! call clear() first if those margins matter. Should only be called on the
//! main thread.
void Renderer::setLogicalPresentation(int w, int h,
                                      SDL_RendererLogicalPresentation mode)
{
    auto renderer = verifyAccess("Set logical presentation");

    if (SDL_SetRenderLogicalPresentation(renderer, w, h, mode) == false)
        throw ApiException("SDL_SetRenderLogicalPresentation()");
}

//! @brief Set a device-independent resolution and presentation mode for rendering.
//! @param[in] size The size of the logical resolution.
//! @param[in] mode The presentation mode used, or
//! SDL_LOGICAL_PRESENTATION_DISABLED to draw at the full pixel resolution of
//! the render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderLogicalPresentation() fails.
//! @details The renderer then behaves as though the current render target
//! were always @p size, scaling to the real resolution as needed. The state
//! belongs to the current render target and may be toggled mid-frame. See
//! the scalar overload for the full set of caveats around letter-boxing.
//! Should only be called on the main thread.
void Renderer::setLogicalPresentation(const SDL_Point &size,
                                      SDL_RendererLogicalPresentation mode)
{
    auto renderer = verifyAccess("Set logical presentation");

    if (SDL_SetRenderLogicalPresentation(renderer, size.x, size.y, mode) == false)
        throw ApiException("SDL_SetRenderLogicalPresentation()");
}

//! @brief Gets the current logical presentation size and mode of the renderer.
//! @param[out] size Receives the logical resolution.
//! @param[out] mode Receives the presentation mode in force.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderLogicalPresentation() fails.
//! @details Each render target carries its own logical presentation state;
//! this reports the one belonging to the current target. Should only be
//! called on the main thread.
void Renderer::getLogicalPresentation(SDL_Point &size,
                                      SDL_RendererLogicalPresentation &mode) const
{
    auto renderer = verifyAccess("Get logical presentation");

    if (SDL_GetRenderLogicalPresentation(renderer, &size.x, &size.y, &mode) == false)
        throw ApiException("SDL_GetRenderLogicalPresentation()");
}

//! @brief Gets the current logical presentation size and mode of the renderer.
//! @param[out] w Receives the horizontal logical resolution.
//! @param[out] h Receives the vertical logical resolution.
//! @param[out] mode Receives the presentation mode in force.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderLogicalPresentation() fails.
//! @details Each render target carries its own logical presentation state;
//! this reports the one belonging to the current target. Should only be
//! called on the main thread.
void Renderer::getLogicalPresentation(int &w, int &h,
                                      SDL_RendererLogicalPresentation &mode) const
{
    auto renderer = verifyAccess("Get logical presentation");

    if (SDL_GetRenderLogicalPresentation(renderer, &w, &h, &mode) == false)
        throw ApiException("SDL_GetRenderLogicalPresentation()");
}

//! @brief Gets the rectangle representing the logical presentation area.
//! @param[out] rect Receives the final presentation rectangle, calculated
//! from the presentation mode and the output size.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderLogicalPresentationRect() fails.
//! @details When logical presentation is disabled, @p rect is filled with
//! the output size in pixels. Each render target carries its own logical
//! presentation state. Should only be called on the main thread.
void Renderer::getLogicalPresentationRect(SDL_FRect &rect) const
{
    auto renderer = verifyAccess("Get logical presentation rect");

    if (SDL_GetRenderLogicalPresentationRect(renderer, &rect) == false)
        throw ApiException("SDL_GetRenderLogicalPresentationRect()");
}

//! @brief Converts window coordinates to render coordinates.
//! @param[in] wx The horizontal position, in window coordinates.
//! @param[in] wy The vertical position, in window coordinates.
//! @param[out] rx Receives the horizontal position in render coordinates.
//! @param[out] ry Receives the vertical position in render coordinates.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderCoordinatesFromWindow() fails.
//! @details The conversion accounts for the window dimensions, the logical
//! presentation settings, the draw scale and the view port. Should only be
//! called on the main thread.
void Renderer::renderCoordinatesFromWindow(float wx, float wy,
                                           float &rx, float &ry) const
{
    auto renderer = verifyAccess("Convert coordinates from window");

    if (SDL_RenderCoordinatesFromWindow(renderer, wx, wy, &rx, &ry) == false)
        throw ApiException("SDL_RenderCoordinatesFromWindow()");
}

//! @brief Converts window coordinates to render coordinates.
//! @param[in] windowPos The position, in window coordinates.
//! @param[out] renderPos Receives the equivalent position in render
//! coordinates.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderCoordinatesFromWindow() fails.
//! @details The conversion accounts for the window dimensions, the logical
//! presentation settings, the draw scale and the view port. Should only be
//! called on the main thread.
void Renderer::renderCoordinatesFromWindow(const SDL_FPoint &windowPos,
                                 SDL_FPoint &renderPos) const
{
    auto renderer = verifyAccess("Convert coordinates from window");

    if (SDL_RenderCoordinatesFromWindow(renderer, windowPos.x, windowPos.y,
                                        &renderPos.x, &renderPos.y) == false)
        throw ApiException("SDL_RenderCoordinatesFromWindow()");
}

//! @brief Converts render coordinates to window coordinates.
//! @param[in] rx The horizontal position, in render coordinates.
//! @param[in] ry The vertical position, in render coordinates.
//! @param[out] wx Receives the horizontal position in window coordinates.
//! @param[out] wy Receives the vertical position in window coordinates.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderCoordinatesToWindow() fails.
//! @details The conversion accounts for the window dimensions, the logical
//! presentation settings, the draw scale and the view port. Should only be
//! called on the main thread.
void Renderer::renderCoordinatesToWindow(float rx, float ry,
                                         float &wx, float &wy) const
{
    auto renderer = verifyAccess("Convert coordinates to window");

    if (SDL_RenderCoordinatesToWindow(renderer, rx, ry, &wx, &wy) == false)
        throw ApiException("SDL_RenderCoordinatesToWindow()");
}

//! @brief Converts render coordinates to window coordinates.
//! @param[in] renderPos The position, in render coordinates.
//! @param[out] windowPos Receives the equivalent position in window
//! coordinates.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderCoordinatesToWindow() fails.
//! @details The conversion accounts for the window dimensions, the logical
//! presentation settings, the draw scale and the view port. Should only be
//! called on the main thread.
void Renderer::renderCoordinatesToWindow(const SDL_FPoint &renderPos,
                                         SDL_FPoint &windowPos) const
{
    auto renderer = verifyAccess("Convert coordinates to window");

    if (SDL_RenderCoordinatesToWindow(renderer, renderPos.x, renderPos.y,
                                      &windowPos.x, &windowPos.y) == false)
        throw ApiException("SDL_RenderCoordinatesToWindow()");
}

//! @brief Rewrites input event coordinates in terms of the renderer's
//! coordinate space.
//! @param[in,out] event The event to rewrite in place. Mouse, touch and pen
//! events are all handled.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ConvertEventToRenderCoordinates() fails.
//! @details The conversion accounts for the window dimensions, the logical
//! presentation settings, the draw scale and the view port. Touch
//! coordinates are converted from normalised window coordinates into
//! non-normalised render coordinates, and relative mouse motion (the xrel
//! and yrel fields) is converted too - use renderCoordinatesFromWindow() on
//! individual fields instead if that is unwanted. Converted coordinates may
//! fall outside the rendering area. Should only be called on the main
//! thread.
void Renderer::convertEventToRenderCoordinates(SDL_Event &event) const
{
    auto renderer = verifyAccess("Convert event coordinates");

    if (SDL_ConvertEventToRenderCoordinates(renderer, &event) == false)
        throw ApiException("SDL_ConvertEventToRenderCoordinates()");
}

//! @brief Creates a renderer attached to a window, binding it to the object.
//! @param[in] window The window the renderer will draw into.
//! @param[in] driverName The name of the render driver to use, or nullptr
//! to let SDL choose the most suitable one.
//! @throws ObjectNotBoundException If @p window is unbound.
//! @throws ApiException If SDL_CreateRenderer() fails.
//! @details Any renderer previously bound to the object is released first.
//! The new renderer is owned, so it is destroyed when the object is.
void Renderer::create(const Window &window, utf8_cptr_t driverName)
{
    auto sdlWindow = window.verifyAccess("Provide window for renderer");

    release();

    _renderer = SDL_CreateRenderer(sdlWindow, driverName);
    _owned = true;

    if (_renderer == nullptr)
        throw ApiException("SDL_CreateRenderer()");
}

//! @brief Creates a software renderer that draws directly into a surface.
//! @param[in] surface The surface which will receive all drawing.
//! @throws ObjectNotBoundException If @p surface is unbound.
//! @throws ApiException If SDL_CreateSoftwareRenderer() fails.
//! @details Any renderer previously bound to the object is released first.
//! @p surface must outlive the renderer. A renderer created this way has no
//! associated window, so getWindow() will throw.
void Renderer::createSoftware(const Surface &surface)
{
    auto sdlSurface = surface.verifyAccess("Provide surface for software renderer");

    release();

    _renderer = SDL_CreateSoftwareRenderer(sdlSurface);
    _owned = true;

    if (_renderer == nullptr)
        throw ApiException("SDL_CreateSoftwareRenderer()");
}

//! @brief Creates a renderer configured entirely by a property set.
//! @param[in] props Properties describing the renderer to create, such as
//! SDL_PROP_RENDERER_CREATE_WINDOW_POINTER, SDL_PROP_RENDERER_CREATE_NAME_STRING
//! and SDL_PROP_RENDERER_CREATE_PRESENT_VSYNC_NUMBER.
//! @throws ApiException If SDL_CreateRendererWithProperties() fails.
//! @details Any renderer previously bound to the object is released first.
//! The new renderer is owned, so it is destroyed when the object is.
void Renderer::createWithProperties(const PropertySet &props)
{
    release();

    _renderer = SDL_CreateRendererWithProperties(props);
    _owned = true;

    if (_renderer == nullptr)
        throw ApiException("SDL_CreateRendererWithProperties()");
}

//! @brief Retrieves the existing renderer bound to a window as a non-owning
//! wrapper.
//! @param[in] window The window to query.
//! @return A Renderer wrapper which does not own the underlying resource, so
//! destroying it will not destroy the renderer.
//! @throws ObjectNotBoundException If @p window is unbound.
//! @throws ApiException If SDL_GetRenderer() fails, which includes the case
//! of a window with no renderer attached.
Renderer Renderer::getRendererForWindow(const Window &window)
{
    auto sdlWindow = window.verifyAccess("Provide window for renderer lookup");
    SDL_Renderer *renderer = SDL_GetRenderer(sdlWindow);

    if (renderer == nullptr)
        throw ApiException("SDL_GetRenderer()");

    return Renderer(renderer, false);
}

//! @brief Clears the entire render target with the current draw colour.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderClear() fails.
//! @details Every pixel of the target is overwritten, ignoring both the
//! view port and the clip rectangle, so set the draw colour beforehand. The
//! backbuffer is invalid after each present(), so clearing at the start of
//! every frame is strongly encouraged even when every pixel will later be
//! overwritten. Should only be called on the main thread.
void Renderer::clear()
{
    auto renderer = verifyAccess("Clear");

    if (SDL_RenderClear(renderer) == false)
        throw ApiException("SDL_RenderClear()");
}

//! @brief Draws a single point at sub-pixel precision.
//! @param[in] x The horizontal position of the point.
//! @param[in] y The vertical position of the point.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderPoint() fails.
//! @details The point is drawn in the current draw colour. Should only be
//! called on the main thread.
void Renderer::drawPoint(float x, float y)
{
    auto renderer = verifyAccess("Draw point");

    if (SDL_RenderPoint(renderer, x, y) == false)
        throw ApiException("SDL_RenderPoint()");
}

//! @brief Draws a single point at sub-pixel precision.
//! @param[in] at The position of the point.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderPoint() fails.
//! @details The point is drawn in the current draw colour. Should only be
//! called on the main thread.
void Renderer::drawPoint(const SDL_FPoint &at)
{
    auto renderer = verifyAccess("Draw point");

    if (SDL_RenderPoint(renderer, at.x, at.y) == false)
        throw ApiException("SDL_RenderPoint()");
}

//! @brief Draws an array of points at sub-pixel precision.
//! @param[in] points The array of points to draw. Must hold at least
//! @p count elements.
//! @param[in] count The count of points to draw.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderPoints() fails.
//! @details The points are drawn in the current draw colour. Should only be
//! called on the main thread.
void Renderer::drawPoints(const SDL_FPoint *points, int count)
{
    auto renderer = verifyAccess("Draw points");

    if (SDL_RenderPoints(renderer, points, count) == false)
        throw ApiException("SDL_RenderPoints()");
}

//! @brief Draws a single line at sub-pixel precision.
//! @param[in] pt1 The position of the start of the line.
//! @param[in] pt2 The position of the end of the line.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderLine() fails.
//! @details The line is drawn in the current draw colour, blended according
//! to the current draw blend mode. Should only be called on the main thread.
void Renderer::drawLine(const SDL_FPoint &pt1, const SDL_FPoint &pt2)
{
    auto renderer = verifyAccess("Draw line");

    if (SDL_RenderLine(renderer, pt1.x, pt1.y, pt2.x, pt2.y) == false)
        throw ApiException("SDL_RenderLine()");
}

//! @brief Draws a single line at sub-pixel precision.
//! @param[in] x1 The horizontal position of the start of the line.
//! @param[in] y1 The vertical position of the start of the line.
//! @param[in] x2 The horizontal position of the end of the line.
//! @param[in] y2 The vertical position of the end of the line.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderLine() fails.
//! @details The line is drawn in the current draw colour, blended according
//! to the current draw blend mode. Should only be called on the main thread.
void Renderer::drawLine(float x1, float y1, float x2, float y2)
{
    auto renderer = verifyAccess("Draw line");

    if (SDL_RenderLine(renderer, x1, y1, x2, y2) == false)
        throw ApiException("SDL_RenderLine()");
}

//! @brief Draws a poly-line through the supplied points.
//! @param[in] points The array of points the lines run through. Must hold
//! at least @p count elements.
//! @param[in] count The count of points, which draws @p count - 1 connected
//! line segments.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderLines() fails.
//! @details The lines are drawn in the current draw colour. Should only be
//! called on the main thread.
void Renderer::drawLines(const SDL_FPoint *points, int count)
{
    auto renderer = verifyAccess("Draw lines");

    if (SDL_RenderLines(renderer, points, count) == false)
        throw ApiException("SDL_RenderLines()");
}

//! @brief Draws the outline around the entire render target.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderRect() fails.
//! @details Equivalent to outlining a rectangle covering the whole target.
//! The outline is drawn in the current draw colour. Should only be called on
//! the main thread.
void Renderer::drawRect()
{
    auto renderer = verifyAccess("Draw rect");

    if (SDL_RenderRect(renderer, nullptr) == false)
        throw ApiException("SDL_RenderRect()");
}

//! @brief Draws the outline of a rectangle at sub-pixel precision.
//! @param[in] rect The rectangle to outline.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderRect() fails.
//! @details The outline is drawn in the current draw colour. Use the
//! parameterless overload to outline the entire render target. Should only
//! be called on the main thread.
void Renderer::drawRect(const SDL_FRect &rect)
{
    auto renderer = verifyAccess("Draw rect");

    if (SDL_RenderRect(renderer, &rect) == false)
        throw ApiException("SDL_RenderRect()");
}

//! @brief Draws the outline of multiple rectangles.
//! @param[in] rects The array of rectangles to outline. Must hold at least
//! @p count elements.
//! @param[in] count The count of rectangles to outline.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderRects() fails.
//! @details The outlines are drawn in the current draw colour. Should only
//! be called on the main thread.
void Renderer::drawRects(const SDL_FRect *rects, int count)
{
    auto renderer = verifyAccess("Draw rects");

    if (SDL_RenderRects(renderer, rects, count) == false)
        throw ApiException("SDL_RenderRects()");
}

//! @brief Fills the entire render target with the current draw colour.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderFillRect() fails.
//! @details Unlike clear(), this is an ordinary fill, so it respects the
//! view port, the clip rectangle and the current draw blend mode. Should only
//! be called on the main thread.
void Renderer::fill()
{
    auto renderer = verifyAccess("Fill all");

    if (SDL_RenderFillRect(renderer, nullptr) == false)
        throw ApiException("SDL_RenderFillRect(nullptr)");
}

//! @brief Fills a rectangle with the current draw colour at sub-pixel
//! precision.
//! @param[in] rect The rectangle to fill.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderFillRect() fails.
//! @details The fill is blended according to the current draw blend mode.
//! Use fill() to cover the entire render target. Should only be called on
//! the main thread.
void Renderer::fillRect(const SDL_FRect &rect)
{
    auto renderer = verifyAccess("Fill rect");

    if (SDL_RenderFillRect(renderer, &rect) == false)
        throw ApiException("SDL_RenderFillRect()");
}

//! @brief Fills multiple rectangles with the current draw colour.
//! @param[in] rects The array of rectangles to fill. Must hold at least
//! @p count elements.
//! @param[in] count The count of rectangles to fill.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderFillRects() fails.
//! @details The fills are blended according to the current draw blend mode.
//! Should only be called on the main thread.
void Renderer::fillRects(const SDL_FRect *rects, int count)
{
    auto renderer = verifyAccess("Fill rects");

    if (SDL_RenderFillRects(renderer, rects, count) == false)
        throw ApiException("SDL_RenderFillRects()");
}

//! @brief Copies a portion of a texture to the current render target at
//! sub-pixel precision.
//! @param[in] texture The source texture.
//! @param[in] src The region of @p texture to copy from, or nullptr for the
//! entire texture.
//! @param[in] dst The region of the render target to copy into, or nullptr
//! for the entire target. The texture is stretched to fit.
//! @throws ObjectNotBoundException If the object or @p texture is unbound.
//! @throws ApiException If SDL_RenderTexture() fails.
//! @details Drawing is affected by the texture's colour and alpha
//! modulation and its blend mode. Should only be called on the main thread.
void Renderer::drawTexture(const Texture &texture, const SDL_FRect *src,
                           const SDL_FRect *dst)
{
    auto renderer = verifyAccess("Draw texture");
    auto sdlTexture = texture.verifyAccess("Provide texture");

    if (SDL_RenderTexture(renderer, sdlTexture, src, dst) == false)
        throw ApiException("SDL_RenderTexture()");
}

//! @brief Draws a texture with rotation and optional flipping.
//! @param[in] texture The source texture.
//! @param[in] src A pointer to the source rectangle, or nullptr for the
//! entire texture.
//! @param[in] dst A pointer to the destination rectangle, or nullptr for the
//! entire rendering target.
//! @param[in] angle An angle in degrees that indicates the rotation that will
//! be applied to @p dst, rotating it in a clockwise direction.
//! @param[in] centre A pointer to a point indicating the point around which
//! @p dst will be rotated, or nullptr to rotate about the centre of @p dst.
//! @param[in] flip An SDL_FlipMode value stating which flipping actions should
//! be performed on the texture.
//! @throws ObjectNotBoundException If the object or @p texture is unbound.
//! @throws ApiException If SDL_RenderTextureRotated() fails.
//! @details Should only be called on the main thread.
void Renderer::drawTextureRotated(const Texture &texture, const SDL_FRect *src,
                                  const SDL_FRect *dst, double angle,
                                  const SDL_FPoint *centre, SDL_FlipMode flip)
{
    auto renderer = verifyAccess("Draw texture rotated");
    auto sdlTexture = texture.verifyAccess("Provide rotated texture");

    if (SDL_RenderTextureRotated(renderer, sdlTexture, src, dst, angle, centre,
                                 flip) == false)
        throw ApiException("SDL_RenderTextureRotated()");
}

//! @brief Draws a texture transformed by an affine matrix.
//! @param[in] texture The source texture.
//! @param[in] src The region of @p texture to copy from, or nullptr for the
//! entire texture.
//! @param[in] origin The position mapped to the top left corner of @p src,
//! or nullptr for (0, 0).
//! @param[in] right The position mapped to the top right corner of @p src,
//! or nullptr for (@p src.w, 0).
//! @param[in] down The position mapped to the bottom left corner of @p src,
//! or nullptr for (0, @p src.h).
//! @throws ObjectNotBoundException If the object or @p texture is unbound.
//! @throws ApiException If SDL_RenderTextureAffine() fails.
//! @details The three corner positions define the affine transform applied
//! to the texture, allowing skew and non-uniform scaling as well as
//! rotation. Should only be called on the main thread.
void Renderer::drawTextureAffine(const Texture &texture, const SDL_FRect *src,
                                 const SDL_FPoint *origin,
                                 const SDL_FPoint *right,
                                 const SDL_FPoint *down)
{
    auto renderer = verifyAccess("Draw texture affine");
    auto sdlTexture = texture.verifyAccess("Provide affine texture");

    if (SDL_RenderTextureAffine(renderer, sdlTexture, src, origin, right,
                                down) == false)
        throw ApiException("SDL_RenderTextureAffine()");
}

//! @brief Tiles a texture across a destination rectangle at sub-pixel
//! precision.
//! @param[in] texture The source texture.
//! @param[in] src The region of @p texture to tile, or nullptr for the
//! entire texture.
//! @param[in] scale The scale applied to @p src to produce each tile, so a
//! 32x32 source at a scale of 2 produces 64x64 tiles.
//! @param[in] dst The region of the render target to cover, or nullptr for
//! the entire target.
//! @throws ObjectNotBoundException If the object or @p texture is unbound.
//! @throws ApiException If SDL_RenderTextureTiled() fails.
//! @details The source pixels are repeated as many times as needed to fill
//! @p dst completely. Should only be called on the main thread.
void Renderer::drawTextureTiled(const Texture &texture, const SDL_FRect *src,
                                float scale, const SDL_FRect *dst)
{
    auto renderer = verifyAccess("Draw texture tiled");
    auto sdlTexture = texture.verifyAccess("Provide tiled texture");

    if (SDL_RenderTextureTiled(renderer, sdlTexture, src, scale, dst) == false)
        throw ApiException("SDL_RenderTextureTiled()");
}

//! @brief Draws a texture using nine-slice scaling at sub-pixel precision.
//! @param[in] texture The source texture.
//! @param[in] src The region of @p texture forming the 9-grid, or nullptr
//! for the entire texture.
//! @param[in] leftWidth The width, in pixels, of the left corners of @p src.
//! @param[in] rightWidth The width, in pixels, of the right corners.
//! @param[in] topHeight The height, in pixels, of the top corners.
//! @param[in] bottomHeight The height, in pixels, of the bottom corners.
//! @param[in] scale The scale applied when fitting a source corner into a
//! destination corner, or 0.0f for an unscaled copy.
//! @param[in] dst The region of the render target to cover, or nullptr for
//! the entire target.
//! @throws ObjectNotBoundException If the object or @p texture is unbound.
//! @throws ApiException If SDL_RenderTexture9Grid() fails.
//! @details The source is split into a 3x3 grid using the four corner
//! sizes, with the sides and centre made up of the remaining pixels. The
//! corners are scaled by @p scale and placed in the corners of @p dst, then
//! the sides and centre are stretched to cover what is left. This is the
//! usual way to draw a resizable panel or button without distorting its
//! borders. Should only be called on the main thread.
void Renderer::drawTexture9Grid(const Texture &texture, const SDL_FRect *src,
                                float leftWidth, float rightWidth,
                                float topHeight, float bottomHeight,
                                float scale, const SDL_FRect *dst)
{
    auto renderer = verifyAccess("Draw texture 9-grid");
    auto sdlTexture = texture.verifyAccess("Provide 9-grid texture");

    if (SDL_RenderTexture9Grid(renderer, sdlTexture, src, leftWidth, rightWidth,
                               topHeight, bottomHeight, scale, dst) == false)
        throw ApiException("SDL_RenderTexture9Grid()");
}

//! @brief Renders a list of triangles, optionally textured and indexed.
//! @param[in] texture The texture to map onto the triangles, or nullptr to
//! draw untextured geometry.
//! @param[in] vertices The array of vertices, each carrying a position,
//! colour and texture coordinate. Must hold at least @p vertexCount
//! elements.
//! @param[in] vertexCount The count of vertices.
//! @param[in] indices An array of indices into @p vertices, or nullptr to
//! use every vertex in sequential order.
//! @param[in] indexCount The count of indices, ignored when @p indices is
//! nullptr.
//! @throws ObjectNotBoundException If the object is unbound, or @p texture
//! is non-null but unbound.
//! @throws ApiException If SDL_RenderGeometry() fails.
//! @details Colour and alpha modulation is applied per vertex, so the
//! texture's own colour and alpha modulation are ignored. Should only be
//! called on the main thread.
void Renderer::drawGeometry(const Texture *texture, const SDL_Vertex *vertices,
                            int vertexCount, const int *indices, int indexCount)
{
    auto renderer = verifyAccess("Draw geometry");
    SDL_Texture *sdlTexture = (texture == nullptr) ? nullptr : texture->get();

    if (SDL_RenderGeometry(renderer, sdlTexture, vertices, vertexCount, indices,
                           indexCount) == false)
        throw ApiException("SDL_RenderGeometry()");
}

//! @brief Renders a list of triangles from separate, possibly interleaved,
//! component arrays.
//! @param[in] texture The texture to map onto the triangles, or nullptr to
//! draw untextured geometry.
//! @param[in] xy The array of vertex positions.
//! @param[in] xyStride The count of bytes between consecutive positions,
//! allowing the data to be interleaved within a larger structure.
//! @param[in] colour The array of per-vertex colours.
//! @param[in] colourStride The count of bytes between consecutive colours.
//! @param[in] uv The array of normalised texture coordinates.
//! @param[in] uvStride The count of bytes between consecutive coordinates.
//! @param[in] numVertices The count of vertices.
//! @param[in] indices An array of indices into the vertex arrays, or nullptr
//! to use every vertex in sequential order.
//! @param[in] numIndices The count of indices.
//! @param[in] sizeIndices The size of each index in bytes: 1, 2 or 4.
//! @throws ObjectNotBoundException If the object is unbound, or @p texture
//! is non-null but unbound.
//! @throws ApiException If SDL_RenderGeometryRaw() fails.
//! @details Colour and alpha modulation is applied per vertex, so the
//! texture's own colour and alpha modulation are ignored. Should only be
//! called on the main thread.
void Renderer::drawGeometryRaw(const Texture *texture,
                               const float *xy, int xyStride,
                               const SDL_FColor *colour, int colourStride,
                               const float *uv, int uvStride,
                               int numVertices,
                               const void *indices, int numIndices,
                               int sizeIndices)
{
    auto renderer = verifyAccess("Draw geometry raw");
    SDL_Texture *sdlTexture = (texture == nullptr) ? nullptr : texture->get();

    if (SDL_RenderGeometryRaw(renderer, sdlTexture, xy, xyStride, colour,
                              colourStride, uv, uvStride, numVertices, indices,
                              numIndices, sizeIndices) == false)
        throw ApiException("SDL_RenderGeometryRaw()");
}

//! @brief Draws a short piece of debug text using the built-in SDL font.
//! @param[in] at The position of the top left corner of the text.
//! @param[in] text The text to draw.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderDebugText() fails.
//! @details A convenience for debugging only, not for production use. The
//! string may be UTF-8 but only ASCII characters are rendered, in a single
//! monospaced 8x8 pixel size which can only be enlarged, blurrily, via
//! logical presentation or the draw scale. The text is drawn in the current
//! draw colour. Should only be called on the main thread.
void Renderer::drawDebugText(const SDL_FPoint &at, utf8_cptr_t text)
{
    auto renderer = verifyAccess("Draw debug text");

    if (SDL_RenderDebugText(renderer, at.x, at.y, text) == false)
        throw ApiException("SDL_RenderDebugText()");
}

//! @brief Draws a short piece of debug text using the built-in SDL font.
//! @param[in] x The horizontal position of the top left corner of the text.
//! @param[in] y The vertical position of the top left corner of the text.
//! @param[in] text The text to draw.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderDebugText() fails.
//! @details A convenience for debugging only, not for production use. The
//! string may be UTF-8 but only ASCII characters are rendered, in a single
//! monospaced 8x8 pixel size. The text is drawn in the current draw colour.
//! Should only be called on the main thread.
void Renderer::drawDebugText(float x, float y, utf8_cptr_t text)
{
    auto renderer = verifyAccess("Draw debug text");

    if (SDL_RenderDebugText(renderer, x, y, text) == false)
        throw ApiException("SDL_RenderDebugText()");
}

//! @brief Redirects rendering to a texture target.
//! @param[in] target The texture to draw into, which must have been created
//! with SDL_TEXTUREACCESS_TARGET.
//! @throws ObjectNotBoundException If the object or @p target is unbound.
//! @throws ApiException If SDL_SetRenderTarget() fails, which includes
//! passing a texture not created for use as a target.
//! @details The view port, clip rectangle, scale and logical presentation
//! are each unique to a render target, and are remembered per target as the
//! current target changes. Call clearTarget() to draw into the window
//! again. There is no need to call present() while drawing into a texture.
//! Should only be called on the main thread.
void Renderer::setTarget(const Texture &target)
{
    auto renderer = verifyAccess("Set target");
    auto sdlTexture = target.verifyAccess("Provide render target");

    if (SDL_SetRenderTarget(renderer, sdlTexture) == false)
        throw ApiException("SDL_SetRenderTarget()");
}

//! @brief Restores rendering to the renderer's default target (window or
//! source surface).
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetRenderTarget() fails.
//! @details The default target is whatever the renderer was created over.
//! The view port, clip rectangle, scale and logical presentation belonging to
//! that target are restored along with it. Should only be called on the main
//! thread.
void Renderer::clearTarget()
{
    auto renderer = verifyAccess("Clear target");

    if (SDL_SetRenderTarget(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderTarget()");
}

//! @brief Gets the current render target as a non-owning Texture wrapper.
//! @return A Texture wrapper which does not own the underlying resource. It
//! is unbound when the default target (the window or source surface) is in
//! use.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details Should only be called on the main thread.
Texture Renderer::getTarget() const
{
    auto renderer = verifyAccess("Get target");
    SDL_Texture *sdlTexture = SDL_GetRenderTarget(renderer);

    return Texture(renderer, sdlTexture, false);
}

//! @brief Presents the accumulated drawing commands to the screen.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderPresent() fails.
//! @details Drawing operations act on a backbuffer rather than the screen,
//! so an entire frame is composed and then presented with a single call to
//! this function. The backbuffer must be treated as invalid afterwards -
//! nothing from the previous frame is guaranteed to survive - so begin each
//! frame with clear(). There is no need to call this while drawing into a
//! texture target; simply call clearTarget() when finished. Should only be
//! called on the main thread.
void Renderer::present()
{
    auto renderer = verifyAccess("Present");

    if (SDL_RenderPresent(renderer) == false)
        throw ApiException("SDL_RenderPresent()");
}

//! @brief Flushes any pending renderer commands and state.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FlushRenderer() fails.
//! @details Only needed when mixing SDL rendering with direct calls to the
//! underlying graphics API, so that SDL's batched work is issued before the
//! foreign calls are made. Ordinary rendering never requires it. Should only
//! be called on the main thread.
void Renderer::flush()
{
    auto renderer = verifyAccess("Flush");

    if (SDL_FlushRenderer(renderer) == false)
        throw ApiException("SDL_FlushRenderer()");
}

//! @brief Reads the pixels of the entire view port from the current render
//! target into a new Surface.
//! @return A newly created Surface owning a copy of the view port's pixels.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderReadPixels() fails.
//! @details This is a very slow operation and should not be used per frame.
//! When reading from the main render target, call it after drawing but
//! before present(). The pixels returned are those actually on screen, so
//! when logical presentation is in use consult
//! getLogicalPresentationRect() to find the area holding the content.
//! Should only be called on the main thread.
Surface Renderer::readViewportPixels() const
{
    auto renderer = verifyAccess("Read pixels");
    SDL_Surface *surface = SDL_RenderReadPixels(renderer, nullptr);

    if (surface == nullptr)
        throw ApiException("SDL_RenderReadPixels()");

    return Surface(surface);
}

//! @brief Reads a region of pixels from the current render target into
//! a new Surface.
//! @param[in] area The region to read, which is clipped to the current
//! view port.
//! @return A newly created Surface owning a copy of the pixels within
//! @p area.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_RenderReadPixels() fails.
//! @details This is a very slow operation and should not be used per frame.
//! When reading from the main render target, call it after drawing but
//! before present(). Should only be called on the main thread.
Surface Renderer::readPixels(const SDL_Rect &area) const
{
    auto renderer = verifyAccess("Read pixels");
    SDL_Surface *surface = SDL_RenderReadPixels(renderer, &area);

    if (surface == nullptr)
        throw ApiException("SDL_RenderReadPixels()");

    return Surface(surface);
}

//! @brief Creates a Texture with the given format, access and dimensions.
//! @param[in] format The pixel format of the new texture.
//! @param[in] access The access pattern the texture will be used with, one
//! of SDL_TEXTUREACCESS_STATIC, SDL_TEXTUREACCESS_STREAMING or
//! SDL_TEXTUREACCESS_TARGET.
//! @param[in] width The width of the new texture, in pixels.
//! @param[in] height The height of the new texture, in pixels.
//! @return A Texture which owns the newly created resource.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateTexture() fails, such as when the
//! renderer does not support @p format or the size exceeds the maximum
//! reported by SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER.
//! @details The contents of the new texture are undefined until written to.
//! Should only be called on the main thread.
Texture Renderer::createTexture(SDL_PixelFormat format, SDL_TextureAccess access,
                                int width, int height) const
{
    auto renderer = verifyAccess("Create texture");
    SDL_Texture *sdlTexture = SDL_CreateTexture(renderer, format, access, width,
                                                height);

    if (sdlTexture == nullptr)
        throw ApiException("SDL_CreateTexture()");

    return Texture(renderer, sdlTexture, true);
}

//! @brief Creates a Texture initialised from an existing surface's pixels.
//! @param[in] surface The surface whose pixels are copied into the texture.
//! @return A Texture which owns the newly created resource.
//! @throws ObjectNotBoundException If the object or @p surface is unbound.
//! @throws ApiException If SDL_CreateTextureFromSurface() fails.
//! @details The pixels are copied, so @p surface may be released
//! afterwards. The new texture has SDL_TEXTUREACCESS_STATIC access and its
//! format is chosen by SDL rather than inherited from @p surface. Should
//! only be called on the main thread.
Texture Renderer::createTextureFromSurface(const Surface &surface) const
{
    auto renderer = verifyAccess("Create texture from surface");
    auto sdlSurface = surface.verifyAccess("Provide surface for texture");
    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(renderer, sdlSurface);

    if (sdlTexture == nullptr)
        throw ApiException("SDL_CreateTextureFromSurface()");

    return Texture(renderer, sdlTexture, true);
}

//! @brief Creates a Texture configured entirely from a property set.
//! @param[in] props Properties describing the texture to create, such as
//! SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER,
//! SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER,
//! SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER and
//! SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER.
//! @return A Texture which owns the newly created resource.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateTextureWithProperties() fails.
//! @details This is the only way to reach the backend-specific creation
//! properties, such as wrapping an existing platform texture handle. Should
//! only be called on the main thread.
Texture Renderer::createTextureWithProperties(const PropertySet &props) const
{
    auto renderer = verifyAccess("Create texture with properties");
    SDL_Texture *sdlTexture = SDL_CreateTextureWithProperties(renderer, props);

    if (sdlTexture == nullptr)
        throw ApiException("SDL_CreateTextureWithProperties()");

    return Texture(renderer, sdlTexture, true);
}

//! @brief Destroys the underlying renderer if ownership is held.
void Renderer::release() noexcept
{
    auto renderer = std::exchange(_renderer, nullptr);
    bool owned = _owned;
    _owned = true;

    if ((renderer != nullptr) && owned)
        SDL_DestroyRenderer(renderer);
}

//! @brief Acquires a renderer from another wrapper, releasing any previous.
Renderer &Renderer::operator=(Renderer &&rhs) noexcept
{
    if (_renderer == rhs._renderer)
        return *this;

    release();

    _renderer = std::exchange(rhs._renderer, nullptr);
    _owned = rhs._owned;
    rhs._owned = true;

    return *this;
}

//! @brief Ensures the object is bound to a valid renderer.
SDL_Renderer *Renderer::verifyAccess(utf8_cptr_t operation) const
{
    if (_renderer == nullptr)
        throw ObjectNotBoundException("Renderer", operation);

    return _renderer;
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
