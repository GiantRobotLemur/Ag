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

//! @brief Gets the name of the render driver, or an empty string if unbound.
utf8_cptr_t Renderer::getName() const
{
    if (_renderer == nullptr)
        return "";

    utf8_cptr_t name = SDL_GetRendererName(_renderer);
    return (name == nullptr) ? "" : name;
}

//! @brief Gets a non-owning wrapper for the window associated with the
//! renderer.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetRenderWindow() fails.
Window Renderer::getWindow() const
{
    auto renderer = verifyAccess("Get window");
    SDL_Window *window = SDL_GetRenderWindow(renderer);

    if (window == nullptr)
        throw ApiException("SDL_GetRenderWindow()");

    return Window(window, false);
}

//! @brief Gets the SDL property set associated with the renderer.
PropertySet Renderer::getProperties() const
{
    auto renderer = verifyAccess("Get properties");
    SDL_PropertiesID id = SDL_GetRendererProperties(renderer);

    if (id == 0)
        throw ApiException("SDL_GetRendererProperties()");

    return PropertySet(id);
}

//! @brief Gets the fixed output size of the renderer, in pixels.
void Renderer::getOutputSize(int &w, int &h) const
{
    auto renderer = verifyAccess("Get output size");

    if (SDL_GetRenderOutputSize(renderer, &w, &h) == false)
        throw ApiException("SDL_GetRenderOutputSize()");
}

//! @brief Gets the fixed output size of the renderer, in pixels.
void Renderer::getOutputSize(SDL_Point &size) const
{
    auto renderer = verifyAccess("Get output size");

    if (SDL_GetRenderOutputSize(renderer, &size.x, &size.y) == false)
        throw ApiException("SDL_GetRenderOutputSize()");
}

//! @brief Gets the current output size of the renderer, in pixels, accounting
//! for logical presentation.
void Renderer::getCurrentOutputSize(int &w, int &h) const
{
    auto renderer = verifyAccess("Get current output size");

    if (SDL_GetCurrentRenderOutputSize(renderer, &w, &h) == false)
        throw ApiException("SDL_GetCurrentRenderOutputSize()");
}

//! @brief Gets the current output size of the renderer, in pixels, accounting
//! for logical presentation.
void Renderer::getCurrentOutputSize(SDL_Point &size) const
{
    auto renderer = verifyAccess("Get current output size");

    if (SDL_GetCurrentRenderOutputSize(renderer, &size.x, &size.y) == false)
        throw ApiException("SDL_GetCurrentRenderOutputSize()");
}

//! @brief Gets the safe-area rectangle within the render target.
void Renderer::getSafeArea(SDL_Rect &area) const
{
    auto renderer = verifyAccess("Get safe area");

    if (SDL_GetRenderSafeArea(renderer, &area) == false)
        throw ApiException("SDL_GetRenderSafeArea()");
}

//! @brief Gets the current viewport rectangle.
void Renderer::getViewport(SDL_Rect &viewport) const
{
    auto renderer = verifyAccess("Get viewport");

    if (SDL_GetRenderViewport(renderer, &viewport) == false)
        throw ApiException("SDL_GetRenderViewport()");
}

//! @brief Sets the current viewport rectangle, or nullptr to reset.
void Renderer::setViewport(const SDL_Rect &viewport)
{
    auto renderer = verifyAccess("Set viewport");

    if (SDL_SetRenderViewport(renderer, &viewport) == false)
        throw ApiException("SDL_SetRenderViewport()");
}

//! @brief Resets the current viewport rectangle, to the entire render target.
void Renderer::resetViewport()
{
    auto renderer = verifyAccess("Reset viewport");

    if (SDL_SetRenderViewport(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderViewport(nullptr)");
}

//! @brief Determines whether an explicit viewport has been set.
bool Renderer::isViewportSet() const
{
    return (_renderer != nullptr) && SDL_RenderViewportSet(_renderer);
}

//! @brief Attempts to obtain the current clip rectangle.
//! @retval true A clip rectangle was returned.
//! @retval false The object is unbound, or no clip rectangle is set.
bool Renderer::tryGetClipRect(SDL_Rect &clip) const
{
    if ((_renderer == nullptr) || (SDL_RenderClipEnabled(_renderer) == false))
        return false;

    return SDL_GetRenderClipRect(_renderer, &clip);
}

//! @brief Sets the clip rectangle.
void Renderer::setClipRect(const SDL_Rect &clip)
{
    auto renderer = verifyAccess("Set clip rect");

    if (SDL_SetRenderClipRect(renderer, &clip) == false)
        throw ApiException("SDL_SetRenderClipRect()");
}

//! @brief Clears the clip rectangle.
void Renderer::resetClipRect()
{
    auto renderer = verifyAccess("Set clip rect");

    if (SDL_SetRenderClipRect(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderClipRect()");
}

//! @brief Determines whether clipping is enabled on the renderer.
bool Renderer::clipEnabled() const
{
    return (_renderer != nullptr) && SDL_RenderClipEnabled(_renderer);
}

//! @brief Gets the current draw scale of the renderer.
void Renderer::getScale(float &scaleX, float &scaleY) const
{
    auto renderer = verifyAccess("Get scale");

    if (SDL_GetRenderScale(renderer, &scaleX, &scaleY) == false)
        throw ApiException("SDL_GetRenderScale()");
}

//! @brief Gets the current draw scale of the renderer.
void Renderer::getScale(SDL_FPoint &scale) const
{
    auto renderer = verifyAccess("Get scale");

    if (SDL_GetRenderScale(renderer, &scale.x, &scale.y) == false)
        throw ApiException("SDL_GetRenderScale()");
}

//! @brief Sets the draw scale of the renderer.
void Renderer::setScale(float scaleX, float scaleY)
{
    auto renderer = verifyAccess("Set scale");

    if (SDL_SetRenderScale(renderer, scaleX, scaleY) == false)
        throw ApiException("SDL_SetRenderScale()");
}

//! @brief Sets the draw scale of the renderer.
void Renderer::setScale(const SDL_FPoint &scale)
{
    auto renderer = verifyAccess("Set scale");

    if (SDL_SetRenderScale(renderer, scale.x, scale.y) == false)
        throw ApiException("SDL_SetRenderScale()");
}

//! @brief Gets the current draw colour as 8-bit RGBA values.
void Renderer::getDrawColour(SDL_Color &colour) const
{
    auto renderer = verifyAccess("Get draw colour");

    if (SDL_GetRenderDrawColor(renderer, &colour.r, &colour.g,
                               &colour.b, &colour.a) == false)
        throw ApiException("SDL_GetRenderDrawColor()");
}

//! @brief Gets the current draw colour as 8-bit RGBA values.
void Renderer::getDrawColour(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const
{
    auto renderer = verifyAccess("Get draw colour");

    if (SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a) == false)
        throw ApiException("SDL_GetRenderDrawColor()");
}

//! @brief Sets the current draw colour using 8-bit RGBA values.
void Renderer::setDrawColour(const SDL_Color &colour)
{
    auto renderer = verifyAccess("Set draw colour");

    if (SDL_SetRenderDrawColor(renderer, colour.r, colour.g,
                               colour.b, colour.a) == false)
        throw ApiException("SDL_SetRenderDrawColor()");
}

//! @brief Sets the current draw colour using 8-bit RGBA values.
void Renderer::setDrawColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    auto renderer = verifyAccess("Set draw colour");

    if (SDL_SetRenderDrawColor(renderer, r, g, b, a) == false)
        throw ApiException("SDL_SetRenderDrawColor()");
}

//! @brief Gets the current draw colour as normalised float RGBA values.
void Renderer::getDrawColorFloat(SDL_FColor &colour) const
{
    auto renderer = verifyAccess("Get draw colour (float)");

    if (SDL_GetRenderDrawColorFloat(renderer, &colour.r, &colour.g,
                                    &colour.b, &colour.a) == false)
        throw ApiException("SDL_GetRenderDrawColorFloat()");
}

//! @brief Gets the current draw colour as normalised float RGBA values.
void Renderer::getDrawColorFloat(float &r, float &g, float &b, float &a) const
{
    auto renderer = verifyAccess("Get draw colour (float)");

    if (SDL_GetRenderDrawColorFloat(renderer, &r, &g, &b, &a) == false)
        throw ApiException("SDL_GetRenderDrawColorFloat()");
}

//! @brief Sets the current draw colour using normalised float RGBA values.
void Renderer::setDrawColourFloat(const SDL_FColor &colour)
{
    auto renderer = verifyAccess("Set draw colour (float)");

    if (SDL_SetRenderDrawColorFloat(renderer, colour.r, colour.g,
                                    colour.b, colour.a) == false)
        throw ApiException("SDL_SetRenderDrawColorFloat()");
}

//! @brief Sets the current draw colour using normalised float RGBA values.
void Renderer::setDrawColourFloat(float r, float g, float b, float a)
{
    auto renderer = verifyAccess("Set draw colour (float)");

    if (SDL_SetRenderDrawColorFloat(renderer, r, g, b, a) == false)
        throw ApiException("SDL_SetRenderDrawColorFloat()");
}

//! @brief Gets the current draw blend mode.
SDL_BlendMode Renderer::getDrawBlendMode() const
{
    auto renderer = verifyAccess("Get draw blend mode");
    SDL_BlendMode mode = SDL_BLENDMODE_NONE;

    if (SDL_GetRenderDrawBlendMode(renderer, &mode) == false)
        throw ApiException("SDL_GetRenderDrawBlendMode()");

    return mode;
}

//! @brief Sets the draw blend mode.
void Renderer::setDrawBlendMode(SDL_BlendMode mode)
{
    auto renderer = verifyAccess("Set draw blend mode");

    if (SDL_SetRenderDrawBlendMode(renderer, mode) == false)
        throw ApiException("SDL_SetRenderDrawBlendMode()");
}

//! @brief Gets the current colour scale multiplier applied when drawing.
float Renderer::getColourScale() const
{
    auto renderer = verifyAccess("Get colour scale");
    float scale = 1.0f;

    if (SDL_GetRenderColorScale(renderer, &scale) == false)
        throw ApiException("SDL_GetRenderColorScale()");

    return scale;
}

//! @brief Sets the colour scale multiplier applied when drawing.
void Renderer::setColourScale(float scale)
{
    auto renderer = verifyAccess("Set colour scale");

    if (SDL_SetRenderColorScale(renderer, scale) == false)
        throw ApiException("SDL_SetRenderColorScale()");
}

//! @brief Gets the vsync interval used by the renderer.
int Renderer::getVSync() const
{
    auto renderer = verifyAccess("Get vsync");
    int value = 0;

    if (SDL_GetRenderVSync(renderer, &value) == false)
        throw ApiException("SDL_GetRenderVSync()");

    return value;
}

//! @brief Sets the vsync interval used by the renderer.
void Renderer::setVSync(int vsync)
{
    auto renderer = verifyAccess("Set vsync");

    if (SDL_SetRenderVSync(renderer, vsync) == false)
        throw ApiException("SDL_SetRenderVSync()");
}

//! @brief Set a device-independent resolution and presentation mode for rendering.
//! @param[in] w The horizontal size of the logical resolution.
//! @param[in] h The vertical size of the logical resolution.
//! @param[in] mode The presentation mode used.
void Renderer::setLogicalPresentation(int w, int h,
                                      SDL_RendererLogicalPresentation mode)
{
    auto renderer = verifyAccess("Set logical presentation");

    if (SDL_SetRenderLogicalPresentation(renderer, w, h, mode) == false)
        throw ApiException("SDL_SetRenderLogicalPresentation()");
}

//! @brief Set a device-independent resolution and presentation mode for rendering.
//! @param[in] size The size of the logical resolution.
//! @param[in] mode The presentation mode used.
void Renderer::setLogicalPresentation(const SDL_Point &size,
                                      SDL_RendererLogicalPresentation mode)
{
    auto renderer = verifyAccess("Set logical presentation");

    if (SDL_SetRenderLogicalPresentation(renderer, size.x, size.y, mode) == false)
        throw ApiException("SDL_SetRenderLogicalPresentation()");
}

//! @brief Gets the current logical presentation size and mode of the renderer.
void Renderer::getLogicalPresentation(SDL_Point &size,
                                      SDL_RendererLogicalPresentation &mode) const
{
    auto renderer = verifyAccess("Get logical presentation");

    if (SDL_GetRenderLogicalPresentation(renderer, &size.x, &size.y, &mode) == false)
        throw ApiException("SDL_GetRenderLogicalPresentation()");
}

//! @brief Gets the current logical presentation size and mode of the renderer.
void Renderer::getLogicalPresentation(int &w, int &h,
                                      SDL_RendererLogicalPresentation &mode) const
{
    auto renderer = verifyAccess("Get logical presentation");

    if (SDL_GetRenderLogicalPresentation(renderer, &w, &h, &mode) == false)
        throw ApiException("SDL_GetRenderLogicalPresentation()");
}

//! @brief Gets the rectangle representing the logical presentation area.
void Renderer::getLogicalPresentationRect(SDL_FRect &rect) const
{
    auto renderer = verifyAccess("Get logical presentation rect");

    if (SDL_GetRenderLogicalPresentationRect(renderer, &rect) == false)
        throw ApiException("SDL_GetRenderLogicalPresentationRect()");
}

//! @brief Converts window coordinates to render coordinates.
void Renderer::renderCoordinatesFromWindow(float wx, float wy,
                                           float &rx, float &ry) const
{
    auto renderer = verifyAccess("Convert coordinates from window");

    if (SDL_RenderCoordinatesFromWindow(renderer, wx, wy, &rx, &ry) == false)
        throw ApiException("SDL_RenderCoordinatesFromWindow()");
}

//! @brief Converts window coordinates to render coordinates.
void Renderer::renderCoordinatesFromWindow(const SDL_FPoint &windowPos,
                                 SDL_FPoint &renderPos) const
{
    auto renderer = verifyAccess("Convert coordinates from window");

    if (SDL_RenderCoordinatesFromWindow(renderer, windowPos.x, windowPos.y,
                                        &renderPos.x, &renderPos.y) == false)
        throw ApiException("SDL_RenderCoordinatesFromWindow()");
}

//! @brief Converts render coordinates to window coordinates.
void Renderer::renderCoordinatesToWindow(float rx, float ry,
                                         float &wx, float &wy) const
{
    auto renderer = verifyAccess("Convert coordinates to window");

    if (SDL_RenderCoordinatesToWindow(renderer, rx, ry, &wx, &wy) == false)
        throw ApiException("SDL_RenderCoordinatesToWindow()");
}

//! @brief Converts render coordinates to window coordinates.
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
void Renderer::convertEventToRenderCoordinates(SDL_Event &event) const
{
    auto renderer = verifyAccess("Convert event coordinates");

    if (SDL_ConvertEventToRenderCoordinates(renderer, &event) == false)
        throw ApiException("SDL_ConvertEventToRenderCoordinates()");
}

//! @brief Creates a renderer attached to a window.
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
Renderer Renderer::getRendererForWindow(const Window &window)
{
    auto sdlWindow = window.verifyAccess("Provide window for renderer lookup");
    SDL_Renderer *renderer = SDL_GetRenderer(sdlWindow);

    if (renderer == nullptr)
        throw ApiException("SDL_GetRenderer()");

    return Renderer(renderer, false);
}

//! @brief Clears the entire render target with the current draw colour.
void Renderer::clear()
{
    auto renderer = verifyAccess("Clear");

    if (SDL_RenderClear(renderer) == false)
        throw ApiException("SDL_RenderClear()");
}

//! @brief Draws a single point.
void Renderer::drawPoint(float x, float y)
{
    auto renderer = verifyAccess("Draw point");

    if (SDL_RenderPoint(renderer, x, y) == false)
        throw ApiException("SDL_RenderPoint()");
}

//! @brief Draws a single point.
void Renderer::drawPoint(const SDL_FPoint &at)
{
    auto renderer = verifyAccess("Draw point");

    if (SDL_RenderPoint(renderer, at.x, at.y) == false)
        throw ApiException("SDL_RenderPoint()");
}

//! @brief Draws an array of points.
void Renderer::drawPoints(const SDL_FPoint *points, int count)
{
    auto renderer = verifyAccess("Draw points");

    if (SDL_RenderPoints(renderer, points, count) == false)
        throw ApiException("SDL_RenderPoints()");
}

//! @brief Draws a single line.
void Renderer::drawLine(const SDL_FPoint &pt1, const SDL_FPoint &pt2)
{
    auto renderer = verifyAccess("Draw line");

    if (SDL_RenderLine(renderer, pt1.x, pt1.y, pt2.x, pt2.y) == false)
        throw ApiException("SDL_RenderLine()");
}

//! @brief Draws a single line.
void Renderer::drawLine(float x1, float y1, float x2, float y2)
{
    auto renderer = verifyAccess("Draw line");

    if (SDL_RenderLine(renderer, x1, y1, x2, y2) == false)
        throw ApiException("SDL_RenderLine()");
}

//! @brief Draws a poly-line through the supplied points.
void Renderer::drawLines(const SDL_FPoint *points, int count)
{
    auto renderer = verifyAccess("Draw lines");

    if (SDL_RenderLines(renderer, points, count) == false)
        throw ApiException("SDL_RenderLines()");
}

//! @brief Draws the outline around the entire render target.
void Renderer::drawRect()
{
    auto renderer = verifyAccess("Draw rect");

    if (SDL_RenderRect(renderer, nullptr) == false)
        throw ApiException("SDL_RenderRect()");
}

//! @brief Draws the outline of a rectangle.
void Renderer::drawRect(const SDL_FRect &rect)
{
    auto renderer = verifyAccess("Draw rect");

    if (SDL_RenderRect(renderer, &rect) == false)
        throw ApiException("SDL_RenderRect()");
}

//! @brief Draws the outline of multiple rectangles.
void Renderer::drawRects(const SDL_FRect *rects, int count)
{
    auto renderer = verifyAccess("Draw rects");

    if (SDL_RenderRects(renderer, rects, count) == false)
        throw ApiException("SDL_RenderRects()");
}

//! @brief Fills a the entire surface with the current draw colour.
void Renderer::fill()
{
    auto renderer = verifyAccess("Fill all");

    if (SDL_RenderFillRect(renderer, nullptr) == false)
        throw ApiException("SDL_RenderFillRect(nullptr)");
}

//! @brief Fills a rectangle with the current draw colour.
void Renderer::fillRect(const SDL_FRect &rect)
{
    auto renderer = verifyAccess("Fill rect");

    if (SDL_RenderFillRect(renderer, &rect) == false)
        throw ApiException("SDL_RenderFillRect()");
}

//! @brief Fills multiple rectangles with the current draw colour.
void Renderer::fillRects(const SDL_FRect *rects, int count)
{
    auto renderer = verifyAccess("Fill rects");

    if (SDL_RenderFillRects(renderer, rects, count) == false)
        throw ApiException("SDL_RenderFillRects()");
}

//! @brief Draws a texture into a destination rectangle.
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
//! @p dst will be rotated (if NULL, rotation will be done around @ dst.w * 0.5,
//! @p dst.h * 0.5).
//! @param[in] flip An SDL_FlipMode value stating which flipping actions should
//! be performed on the texture.
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

//! @brief Tiles a texture across a destination rectangle.
void Renderer::drawTextureTiled(const Texture &texture, const SDL_FRect *src,
                                float scale, const SDL_FRect *dst)
{
    auto renderer = verifyAccess("Draw texture tiled");
    auto sdlTexture = texture.verifyAccess("Provide tiled texture");

    if (SDL_RenderTextureTiled(renderer, sdlTexture, src, scale, dst) == false)
        throw ApiException("SDL_RenderTextureTiled()");
}

//! @brief Draws a texture using nine-slice scaling.
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

//! @brief Draws indexed geometry with optional texture mapping.
void Renderer::drawGeometry(const Texture *texture, const SDL_Vertex *vertices,
                            int vertexCount, const int *indices, int indexCount)
{
    auto renderer = verifyAccess("Draw geometry");
    SDL_Texture *sdlTexture = (texture == nullptr) ? nullptr : texture->get();

    if (SDL_RenderGeometry(renderer, sdlTexture, vertices, vertexCount, indices,
                           indexCount) == false)
        throw ApiException("SDL_RenderGeometry()");
}

//! @brief Draws indexed geometry from raw component arrays.
void Renderer::drawGeometryRaw(const Texture *texture,
                               const float *xy, int xyStride,
                               const SDL_FColor *color, int colorStride,
                               const float *uv, int uvStride,
                               int numVertices,
                               const void *indices, int numIndices,
                               int sizeIndices)
{
    auto renderer = verifyAccess("Draw geometry raw");
    SDL_Texture *sdlTexture = (texture == nullptr) ? nullptr : texture->get();

    if (SDL_RenderGeometryRaw(renderer, sdlTexture, xy, xyStride, color,
                              colorStride, uv, uvStride, numVertices, indices,
                              numIndices, sizeIndices) == false)
        throw ApiException("SDL_RenderGeometryRaw()");
}

//! @brief Draws a short piece of debug text using the built-in SDL font.
void Renderer::drawDebugText(const SDL_FPoint &at, utf8_cptr_t text)
{
    auto renderer = verifyAccess("Draw debug text");

    if (SDL_RenderDebugText(renderer, at.x, at.y, text) == false)
        throw ApiException("SDL_RenderDebugText()");
}

//! @brief Draws a short piece of debug text using the built-in SDL font.
void Renderer::drawDebugText(float x, float y, utf8_cptr_t text)
{
    auto renderer = verifyAccess("Draw debug text");

    if (SDL_RenderDebugText(renderer, x, y, text) == false)
        throw ApiException("SDL_RenderDebugText()");
}

//! @brief Redirects rendering to a texture target.
void Renderer::setTarget(const Texture &target)
{
    auto renderer = verifyAccess("Set target");
    auto sdlTexture = target.verifyAccess("Provide render target");

    if (SDL_SetRenderTarget(renderer, sdlTexture) == false)
        throw ApiException("SDL_SetRenderTarget()");
}

//! @brief Restores rendering to the renderer's default target (window or
//! source surface).
void Renderer::clearTarget()
{
    auto renderer = verifyAccess("Clear target");

    if (SDL_SetRenderTarget(renderer, nullptr) == false)
        throw ApiException("SDL_SetRenderTarget()");
}

//! @brief Gets the current render target as a non-owning Texture wrapper.
//! An unbound Texture is returned when the default target is in use.
Texture Renderer::getTarget() const
{
    auto renderer = verifyAccess("Get target");
    SDL_Texture *sdlTexture = SDL_GetRenderTarget(renderer);

    return Texture(renderer, sdlTexture, false);
}

//! @brief Presents the accumulated drawing commands to the screen.
void Renderer::present()
{
    auto renderer = verifyAccess("Present");

    if (SDL_RenderPresent(renderer) == false)
        throw ApiException("SDL_RenderPresent()");
}

//! @brief Flushes any pending renderer commands.
void Renderer::flush()
{
    auto renderer = verifyAccess("Flush");

    if (SDL_FlushRenderer(renderer) == false)
        throw ApiException("SDL_FlushRenderer()");
}

//! @brief Reads the pixels of the entire view port from the current render
//! target into a new Surface.
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
Surface Renderer::readPixels(const SDL_Rect &area) const
{
    auto renderer = verifyAccess("Read pixels");
    SDL_Surface *surface = SDL_RenderReadPixels(renderer, &area);

    if (surface == nullptr)
        throw ApiException("SDL_RenderReadPixels()");

    return Surface(surface);
}

//! @brief Creates a Texture with the given format, access and dimensions.
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
