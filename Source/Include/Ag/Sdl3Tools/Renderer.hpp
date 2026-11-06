//! @file Ag/Sdl3Tools/Renderer.hpp
//! @brief The declaration of a wrapper for the SDL3 2D SDL_Renderer resource.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SDL3_TOOLS_RENDERER_HPP_
#define HEADER_AG_SDL3_TOOLS_RENDERER_HPP_

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class PropertySet;
class Surface;
class Texture;
class Window;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A wrapper for the SDL3 2D SDL_Renderer resource.
class Renderer
{
public:
    // Construction/Destruction
    Renderer();
    Renderer(SDL_Renderer *renderer, bool owned = true);
    Renderer(const Renderer &) = delete;
    Renderer(Renderer &&rhs) noexcept;
    ~Renderer();

    // Accessors
    bool isBound() const;
    bool isOwned() const;
    SDL_Renderer *get() const;
    utf8_cptr_t getName() const;
    Window getWindow() const;
    PropertySet getProperties() const;
    void getOutputSize(int &w, int &h) const;
    void getOutputSize(SDL_Point &size) const;
    void getCurrentOutputSize(int &w, int &h) const;
    void getCurrentOutputSize(SDL_Point &size) const;
    void getSafeArea(SDL_Rect &area) const;
    void getViewport(SDL_Rect &viewport) const;
    void setViewport(const SDL_Rect &viewport);
    void resetViewport();
    bool isViewportSet() const;
    bool tryGetClipRect(SDL_Rect &clip) const;
    void setClipRect(const SDL_Rect &clip);
    void resetClipRect();
    bool clipEnabled() const;
    void getScale(float &scaleX, float &scaleY) const;
    void getScale(SDL_FPoint &scale) const;
    void setScale(float scaleX, float scaleY);
    void setScale(const SDL_FPoint &scale);
    void getDrawColour(SDL_Color &colour) const;
    void getDrawColour(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const;
    void setDrawColour(const SDL_Color &colour);
    void setDrawColour(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    void getDrawColourFloat(SDL_FColor &colour) const;
    void getDrawColourFloat(float &r, float &g, float &b, float &a) const;
    void setDrawColourFloat(const SDL_FColor &colour);
    void setDrawColourFloat(float r, float g, float b, float a = 1.0f);
    SDL_BlendMode getDrawBlendMode() const;
    void setDrawBlendMode(SDL_BlendMode mode);
    float getColourScale() const;
    void setColourScale(float scale);
    int getVSync() const;
    void setVSync(int vsync);

    void setLogicalPresentation(int w, int h, SDL_RendererLogicalPresentation mode);
    void setLogicalPresentation(const SDL_Point &size, SDL_RendererLogicalPresentation mode);
    void getLogicalPresentation(int &w, int &h,
                                SDL_RendererLogicalPresentation &mode) const;
    void getLogicalPresentation(SDL_Point &size,
                                SDL_RendererLogicalPresentation &mode) const;
    void getLogicalPresentationRect(SDL_FRect &rect) const;

    void renderCoordinatesFromWindow(float wx, float wy,
                                     float &rx, float &ry) const;
    void renderCoordinatesFromWindow(const SDL_FPoint &windowPos,
                                     SDL_FPoint &renderPos) const;
    void renderCoordinatesToWindow(float rx, float ry,
                                   float &wx, float &wy) const;
    void renderCoordinatesToWindow(const SDL_FPoint &renderPos,
                                   SDL_FPoint &windowPos) const;
    void convertEventToRenderCoordinates(SDL_Event &event) const;

    // Operations
    void create(const Window &window, utf8_cptr_t driverName = nullptr);
    void createSoftware(const Surface &surface);
    void createWithProperties(const PropertySet &props);
    static Renderer getRendererForWindow(const Window &window);

    void clear();
    void drawPoint(float x, float y);
    void drawPoint(const SDL_FPoint &at);
    void drawPoints(const SDL_FPoint *points, int count);
    void drawLine(const SDL_FPoint &pt1, const SDL_FPoint &pt2);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawLines(const SDL_FPoint *points, int count);
    void drawRect();
    void drawRect(const SDL_FRect &rect);
    void drawRects(const SDL_FRect *rects, int count);
    void fill();
    void fillRect(const SDL_FRect &rect);
    void fillRects(const SDL_FRect *rects, int count);
    void drawTexture(const Texture &texture, const SDL_FRect *src,
                     const SDL_FRect *dst);
    void drawTextureRotated(const Texture &texture, const SDL_FRect *src,
                            const SDL_FRect *dst, double angle,
                            const SDL_FPoint *centre, SDL_FlipMode flip);
    void drawTextureAffine(const Texture &texture, const SDL_FRect *src,
                           const SDL_FPoint *origin, const SDL_FPoint *right,
                           const SDL_FPoint *down);
    void drawTextureTiled(const Texture &texture, const SDL_FRect *src,
                          float scale, const SDL_FRect *dst);
    void drawTexture9Grid(const Texture &texture, const SDL_FRect *src,
                          float leftWidth, float rightWidth,
                          float topHeight, float bottomHeight,
                          float scale, const SDL_FRect *dst);
    void drawGeometry(const Texture *texture, const SDL_Vertex *vertices,
                      int vertexCount, const int *indices = nullptr,
                      int indexCount = 0);
    void drawGeometryRaw(const Texture *texture,
                         const float *xy, int xyStride,
                         const SDL_FColor *colour, int colourStride,
                         const float *uv, int uvStride,
                         int numVertices,
                         const void *indices, int numIndices,
                         int sizeIndices);
    void drawDebugText(const SDL_FPoint &at, utf8_cptr_t text);
    void drawDebugText(float x, float y, utf8_cptr_t text);

    void setTarget(const Texture &target);
    void clearTarget();
    Texture getTarget() const;
    void present();
    void flush();
    Surface readViewportPixels() const;
    Surface readPixels(const SDL_Rect &area) const;

    Texture createTexture(SDL_PixelFormat format, SDL_TextureAccess access,
                          int width, int height) const;
    Texture createTextureFromSurface(const Surface &surface) const;
    Texture createTextureWithProperties(const PropertySet &props) const;

    void release() noexcept;
    Renderer &operator=(const Renderer &) = delete;
    Renderer &operator=(Renderer &&rhs) noexcept;
    SDL_Renderer *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Renderer *_renderer;
    bool _owned;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
