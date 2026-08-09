//! @file Ag/Sdl3Tools/Surface.hpp
//! @brief The declaration of a wrapper for an SDL3 system memory image resource,
//! a 'surface'.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SDL3_TOOLS_SURFACE_HPP_
#define HEADER_AG_SDL3_TOOLS_SURFACE_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class PropertySet;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A wrapper for a locked SDL surface object in which the program can
//! randomly access the pixels.
class LockedSurface
{
public:
    // Construction/Destruction
    LockedSurface();
    LockedSurface(SDL_Surface *surface);
    LockedSurface(const LockedSurface &) = delete;
    LockedSurface(LockedSurface &&rhs) noexcept;
    ~LockedSurface();

    // Accessors
    bool isLocked() const;
    void *getBits() const;
    void *getRow(int row) const;
    void *getPixel(int column, int row) const;
    int getWidth() const;
    int getHeight() const;
    int getPitch() const;
    SDL_PixelFormat getFormat() const;
    SDL_SurfaceFlags getFlags() const;
    const SDL_PixelFormatDetails *getFormatDetails() const;

    // Operations
    void unlock() noexcept;
    LockedSurface &operator=(const LockedSurface &) = delete;
    LockedSurface &operator=(LockedSurface &&rhs) noexcept;
private:
    // Internal Functions
    SDL_Surface *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_Surface *_surface;
};

//! @brief A wrapper for an SDL3 system memory image resource, a 'surface'.
class Surface
{
public:
    // Public Types
    using Collection = std::vector<Surface>;

    // Construction/Destruction
    Surface();
    Surface(const Surface &) = delete;
    Surface(Surface &&rhs) noexcept;
    Surface(SDL_Surface *surface, bool isOwned = true);
    Surface(SDL_Window *window);
    ~Surface();

    // Accessors
    bool isBound() const;
    bool needsLock() const;
    SDL_Surface *get() const;
    SDL_Point getSize() const;
    int getWidth() const;
    int getHeight() const;
    int getPitch() const;
    SDL_PixelFormat getFormat() const;
    SDL_SurfaceFlags getFlags() const;
    PropertySet getProperties() const;
    SDL_Colorspace getColourspace() const;
    void setColourspace(SDL_Colorspace colourspace);
    bool hasAlternateImages() const;
    Collection getImages() const;
    void addAlternateImage(const Surface &image);
    void removeAlternateImages();
    bool hasPalette() const;
    SDL_Palette *getPalette() const;
    void setPalette(SDL_Palette *palette);
    SDL_Palette *createAndSetPalette();
    bool hasRLE() const;
    void setRLE(bool enable);
    bool hasColourKey() const;
    bool tryGetColourKey(uint32_t &key) const;
    void setColourKey(bool enable, uint32_t key);
    void getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const;
    void setColourMod(uint8_t r, uint8_t g, uint8_t b);
    uint8_t getAlphaMod() const;
    void setAlphaMod(uint8_t alpha);
    SDL_BlendMode getBlendMode() const;
    void setBlendMode(SDL_BlendMode mode);
    bool tryGetClipRect(SDL_Rect &clip) const;
    bool setClipRect(const SDL_Rect &clip);
    void resetClipRect();

    // Operations
    void create(int width, int height, SDL_PixelFormat format);
    void createFrom(int width, int height, SDL_PixelFormat format,
                    void *pixels, int pitch);
    static Surface loadBMP(utf8_cptr_t file);
    void saveBMP(utf8_cptr_t file) const;
    Surface duplicate() const;
    Surface scaled(int width, int height, SDL_ScaleMode mode) const;
    Surface converted(SDL_PixelFormat format) const;
    Surface convertedWithColourspace(SDL_PixelFormat format, SDL_Palette *palette,
                                     SDL_Colorspace colourspace,
                                     SDL_PropertiesID props) const;
    void flip(SDL_FlipMode flip);
    void clear(const SDL_FColor &value) const;
    void fillRect(const SDL_Rect *rect, uint32_t pixelValue);
    void fillRects(const SDL_Rect *rects, int count, uint32_t pixelValue);
    void blit(const SDL_Rect *srcRect, const Surface &dst,
              const SDL_Rect *dstRect) const;
    void blitScaled(const SDL_Rect *srcRect, const Surface &dst,
                    const SDL_Rect *dstRect, SDL_ScaleMode mode) const;
    void blitUnchecked(const SDL_Rect &srcRect, const Surface &dst,
                       const SDL_Rect &dstRect) const;
    void blitTiled(const SDL_Rect *srcRect, const Surface &dst,
                   const SDL_Rect *dstRect) const;
    void blitTiledWithScale(const SDL_Rect *srcRect, float scale,
                            SDL_ScaleMode mode, const Surface &dst,
                            const SDL_Rect *dstRect) const;
    void blit9Grid(const SDL_Rect *srcRect,
                   int leftWidth, int rightWidth, int topHeight, int bottomHeight,
                   float scale, SDL_ScaleMode mode, const Surface &dst,
                   const SDL_Rect *dstRect) const;
    void stretch(const SDL_Rect *srcRect, const Surface &dst,
                 const SDL_Rect *dstRect, SDL_ScaleMode mode) const;
    void premultiplyAlpha(bool linear);
    void readPixel(const SDL_Point &at, SDL_Color &colour) const;
    void readPixel(int x, int y, uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a) const;
    void readPixelFloat(const SDL_Point &at, SDL_FColor &colour) const;
    void readPixelFloat(int x, int y, float &r, float &g, float &b, float &a) const;
    void writePixel(const SDL_Point &at, const SDL_Color &colour);
    void writePixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void writePixelFloat(const SDL_Point &at, const SDL_FColor &colour);
    void writePixelFloat(int x, int y, float r, float g, float b, float a);
    void release() noexcept;
    LockedSurface lock() const;
    Surface &operator=(const Surface &) = delete;
    Surface &operator=(Surface &&rhs) noexcept;
    SDL_Surface *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Surface *_surface;
    SDL_Window *_associatedWindow;
    bool _isOwned;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
