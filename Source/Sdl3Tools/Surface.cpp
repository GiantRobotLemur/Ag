//! @file Sdl3Tools/Surface.cpp
//! @brief The definition of a wrapper for an SDL3 system memory image resource,
//! a 'surface'.
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
#include "Ag/Sdl3Tools/Surface.hpp"

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// LockedSurface Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty object to wrap a locked surface.
LockedSurface::LockedSurface() :
    _surface(nullptr)
{
}

//! @brief Constructs an object to wrap a locked surface.
//! @param[in] surface The surface which has been locked.
LockedSurface::LockedSurface(SDL_Surface *surface) :
    _surface(surface)
{
}

//! @brief Acquires a locked surface from another wrapper.
//! @param[in] rhs The wrapper to obtain the wrapped surface from.
LockedSurface::LockedSurface(LockedSurface &&rhs) noexcept :
    _surface(std::exchange(rhs._surface, nullptr))
{
}

//! @brief Ensures the surface is properly unlocked at destruction.
LockedSurface::~LockedSurface()
{
    unlock();
}

//! @brief Determines if the object wraps a valid locked surface.
//! @retval true The object wraps a valid locked surface.
//! @retval false The object is in an unbound state.
bool LockedSurface::isLocked() const
{
    return _surface != nullptr;
}

//! @brief Gets a pointer to the first byte of the pixel data.
//! @throws ObjectNotBoundException If the object does not wrap a valid
//! locked surface.
void *LockedSurface::getBits() const
{
    return verifyAccess("Access pixels")->pixels;
}

//! @brief Gets a pointer to the first byte of a row of pixel data.
//! @param[in] row The 0-based index of the row to obtain a pointer to.
//! @return A pointer to the first byte of the row.
//! @throws ObjectNotBoundException If the object does not wrap a valid
//! locked surface.
//! @throws ArgumentException If @p row is out of range.
//! @details This member function only works if the surface is a matrix
//! of pixels with one or more bytes per pixel. If the surface contains
//! multiple planes or is defined with less than one byte per pixel, the
//! results are undefined.
void *LockedSurface::getRow(int row) const
{
    auto lockedSurface = verifyAccess("Access row");

    if ((row < 0) || (row >= lockedSurface->h))
        throw ArgumentException("row");

    uint8_t *bits = reinterpret_cast<uint8_t *>(lockedSurface->pixels);

    return bits + (lockedSurface->pitch * row);
}

//! @brief Gets a pointer to the first byte of a pixel.
//! @param[in] column The 0-based index of the column containing the pixel.
//! @param[in] row The 0-based index of the row containing the pixel.
//! @return A pointer to the first byte of the pixel.
//! @throws ObjectNotBoundException If the object does not wrap a valid
//! locked surface.
//! @throws ArgumentException If @p column or @p row is out of range.
//! @details This member function only works if the surface is a matrix
//! of pixels with one or more bytes per pixel. If the surface contains
//! multiple planes or is defined with less than one byte per pixel, the
//! results are undefined.
void *LockedSurface::getPixel(int column, int row) const
{
    auto lockedSurface = verifyAccess("Access pixel");

    if ((row < 0) || (row >= lockedSurface->h))
        throw ArgumentException("row");

    if ((column < 0) || (column >= lockedSurface->w))
        throw ArgumentException("column");

    auto format = SDL_GetPixelFormatDetails(lockedSurface->format);
    uint8_t *bits = reinterpret_cast<uint8_t *>(lockedSurface->pixels);

    return bits + (lockedSurface->pitch * row) + (column * format->bytes_per_pixel);
}

//! @brief Gets the width of the surface, in pixels, or -1 if the object is in
//! an unbound state.
int LockedSurface::getWidth() const
{
    return (_surface == nullptr) ? -1 : _surface->w;
}

//! @brief Gets the height of the surface, in pixels, or -1 if the object is in
//! an unbound state.
int LockedSurface::getHeight() const
{
    return (_surface == nullptr) ? -1 : _surface->h;
}

//! @brief Gets the count of bytes for each row of the surface, or -1 if the
//! object is in an unbound state.
int LockedSurface::getPitch() const
{
    return (_surface == nullptr) ? -1 : _surface->pitch;
}

//! @brief Gets the pixel format of the surface, or SDL_PIXELFORMAT_UNKNOWN if
//! the object is in an unbound state.
SDL_PixelFormat LockedSurface::getFormat() const
{
    return (_surface == nullptr) ? SDL_PIXELFORMAT_UNKNOWN :
                                   _surface->format;
}

//! @brief Gets the flags associated with the surface, or 0 if
//! the object is in an unbound state.
SDL_SurfaceFlags LockedSurface::getFlags() const
{
    return (_surface == nullptr) ? 0u : _surface->flags;
}

//! @brief Gets pointer to a description of the pixel format used by the
//! surface, or nullptr if the object is in an unbound state.
const SDL_PixelFormatDetails *LockedSurface::getFormatDetails() const
{
    return (_surface == nullptr) ? nullptr :
                                   SDL_GetPixelFormatDetails(_surface->format);
}

//! @brief Unlocks the surface if one is bound and leaves the object in an
//! unbound state.
void LockedSurface::unlock() noexcept
{
    auto lockedSurface = std::exchange(_surface, nullptr);

    if (lockedSurface != nullptr)
    {
        SDL_UnlockSurface(lockedSurface);
    }
}

//! @brief Acquires a locked surface resource from another wrapper, unlocking
//! any previously bound resource.
//! @param[in] rhs The wrapper to acquire the locked surface from.
//! @return A reference to the current object.
LockedSurface &LockedSurface::operator=(LockedSurface &&rhs) noexcept
{
    if (_surface == rhs._surface)
        return *this;

    unlock();
    _surface = std::exchange(rhs._surface, nullptr);

    return *this;
}

//! @brief Verifies that the object is in a bound state before an operation.
//! @param[in] operation A description of the operation to be performed.
//! @return A valid pointer to a locked surface.
//! @throws ObjectNotBoundException If the object is in an unbound state.
SDL_Surface *LockedSurface::verifyAccess(utf8_cptr_t operation) const
{
    if (_surface == nullptr)
        throw ObjectNotBoundException("Locked surface", operation);

    return _surface;
}

////////////////////////////////////////////////////////////////////////////////
// Surface Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty wrapper for an SDL surface.
Surface::Surface() :
    _surface(nullptr),
    _associatedWindow(nullptr),
    _isOwned(false)
{
}

//! @brief Acquires a surface resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the resource from.
Surface::Surface(Surface &&rhs) noexcept :
    _surface(std::exchange(rhs._surface, nullptr)),
    _associatedWindow(std::exchange(rhs._associatedWindow, nullptr)),
    _isOwned(std::exchange(rhs._isOwned, false))
{
}

//! @brief Constructs a wrapper for a surface resource.
//! @param[in] surface The surface resource to wrap, possibly nullptr.
//! @param[in] isOwned True if the @p surface is now tied to the
//! lifetime of this object, false to access it passively.
Surface::Surface(SDL_Surface *surface, bool isOwned /*= true*/) :
    _surface(surface),
    _associatedWindow(nullptr),
    _isOwned(isOwned)
{
}

//! @brief Creates a wrapper for the surface associated with a window.
//! @param[in] window A pointer to the SDL window to obtain a surface for.
//! @throws ApiException If SDL_GetWindowSurface() returns nullptr for a
//! non-null window.
Surface::Surface(SDL_Window *window) :
    _surface(nullptr),
    _associatedWindow(window),
    _isOwned(false)
{
    if (window != nullptr)
    {
        _surface = SDL_GetWindowSurface(window);

        if (_surface == nullptr)
            throw ApiException("SDL_GetWindowSurface()");

        _isOwned = true;
    }
}

//! @brief Ensures that any wrapped surface resource is properly released.
Surface::~Surface()
{
    release();
}

//! @brief Determines if the object wraps a valid surface resource.
//! @retval true The object wraps a valid surface resource.
//! @retval false The object is in an unbound state.
bool Surface::isBound() const
{
    return _surface != nullptr;
}

//! @brief Determines if the surface needs to be locked to access its pixels.
//! @retval true The surface must be locked to access its pixels.
//! @retval false The surface does not need to be locked to access its pixels.
bool Surface::needsLock() const
{
    return (_surface != nullptr) && SDL_MUSTLOCK(_surface);
}

//! @brief Gets a pointer to the underlying SDL surface, or nullptr if the
//! object is unbound.
SDL_Surface *Surface::get() const
{
    return _surface;
}

//! @brief Gets the size of the surface, in pixels, or -1 x -1 if the
//! object is unbound.
SDL_Point Surface::getSize() const
{
    return (_surface == nullptr) ? Point(-1, -1) : Point(_surface->w, _surface->h);
}

//! @brief Gets the width of the surface, in pixels, or -1 if the object is
//! unbound.
int Surface::getWidth() const
{
    return (_surface == nullptr) ? -1 : _surface->w;
}

//! @brief Gets the height of the surface, in pixels, or -1 if the object is
//! unbound.
int Surface::getHeight() const
{
    return (_surface == nullptr) ? -1 : _surface->h;
}

//! @brief Gets the count of bytes for each row of the surface, or -1 if the
//! object is unbound.
int Surface::getPitch() const
{
    return (_surface == nullptr) ? -1 : _surface->pitch;
}

//! @brief Gets the pixel format of the surface, or SDL_PIXELFORMAT_UNKNOWN if
//! the object is unbound.
SDL_PixelFormat Surface::getFormat() const
{
    return (_surface == nullptr) ? SDL_PIXELFORMAT_UNKNOWN :
                                   _surface->format;
}

//! @brief Gets the flags associated with the surface, or 0 if the object is
//! unbound.
SDL_SurfaceFlags Surface::getFlags() const
{
    return (_surface == nullptr) ? 0u : _surface->flags;
}

//! @brief Gets a wrapper for the SDL property set associated with the surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to return a property set.
PropertySet Surface::getProperties() const
{
    auto surface = verifyAccess("Get properties");

    SDL_PropertiesID id = SDL_GetSurfaceProperties(surface);

    if (id == 0)
        throw ApiException("SDL_GetSurfaceProperties()");

    return PropertySet(id);
}

//! @brief Gets the current colour space of the surface.
//! @throws ObjectNotBoundException If the object is unbound.
SDL_Colorspace Surface::getColourspace() const
{
    return SDL_GetSurfaceColorspace(verifyAccess("Get colour space"));
}

//! @brief Sets the colour space of the surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to set the colour space.
void Surface::setColourspace(SDL_Colorspace colorspace)
{
    auto surface = verifyAccess("Set colour space");

    if (SDL_SetSurfaceColorspace(surface, colorspace) == false)
        throw ApiException("SDL_SetSurfaceColorspace()");
}

//! @brief Determines whether the surface has additional images beyond its
//! primary one.
bool Surface::hasAlternateImages() const
{
    return (_surface != nullptr) && SDL_SurfaceHasAlternateImages(_surface);
}

//! @brief Gets all images associated with the surface, including the primary.
//! @return The images belonging to the surface, or an empty vector when the
//! surface is unbound.
Surface::Collection Surface::getImages() const
{
    Collection result;

    if (_surface != nullptr)
    {
        int count = 0;
        SDL_Surface **images = SDL_GetSurfaceImages(_surface, &count);

        if (images == nullptr)
            throw ApiException("SDL_GetSurfaceImages()");

        // Ensure we dispose of the returned array, no matter what happens.
        AtScopeExit1 freeImages(SDL_free, images);

        result.reserve(toSize(count));

        for (int i = 0; i < count; ++i)
            result.emplace_back(images[i], false);
    }

    return result;
}

//! @brief Adds an alternate image to the surface.
//! @param[in] image The surface to add as an additional image.
//! @throws ObjectNotBoundException If either the current or @p image surface
//! is unbound.
//! @throws ApiException If SDL_AddSurfaceAlternateImage() fails.
void Surface::addAlternateImage(const Surface &image)
{
    auto surface = verifyAccess("Add alternate image");
    auto other = image.verifyAccess("Provide alternate image");

    if (SDL_AddSurfaceAlternateImage(surface, other) == false)
        throw ApiException("SDL_AddSurfaceAlternateImage()");

    // NOTE: Both the new and old reference to image remain valid,
    // so there is no need to remove the underlying SDL_Surface
    // from inside image on success.
}

//! @brief Removes any alternate images from the surface.
void Surface::removeAlternateImages()
{
    if (_surface != nullptr)
        SDL_RemoveSurfaceAlternateImages(_surface);
}

//! @brief Determines whether the surface has an associated palette.
bool Surface::hasPalette() const
{
    return (_surface != nullptr) && (SDL_GetSurfacePalette(_surface) != nullptr);
}

//! @brief Gets the palette associated with the surface, or nullptr if none is
//! set or the object is unbound.
SDL_Palette *Surface::getPalette() const
{
    return (_surface == nullptr) ? nullptr : SDL_GetSurfacePalette(_surface);
}

//! @brief Associates a palette with the surface.
//! @param[in] palette The palette to associate, or nullptr to remove the
//! current palette.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfacePalette() fails.
void Surface::setPalette(SDL_Palette *palette)
{
    auto surface = verifyAccess("Set palette");

    if (SDL_SetSurfacePalette(surface, palette) == false)
        throw ApiException("SDL_SetSurfacePalette()");
}

//! @brief Creates a palette suitable for the surface and assigns it.
//! @return A pointer to the newly created palette, owned by the surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateSurfacePalette() fails.
SDL_Palette *Surface::createAndSetPalette()
{
    auto surface = verifyAccess("Create palette");

    SDL_Palette *palette = SDL_CreateSurfacePalette(surface);

    if (palette == nullptr)
        throw ApiException("SDL_CreateSurfacePalette()");

    return palette;
}

//! @brief Determines whether RLE acceleration is enabled for the surface.
bool Surface::hasRLE() const
{
    return (_surface != nullptr) && SDL_SurfaceHasRLE(_surface);
}

//! @brief Enables or disables RLE acceleration for the surface.
//! @param[in] enable True to enable RLE, false to disable.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceRLE() fails.
void Surface::setRLE(bool enable)
{
    auto surface = verifyAccess("Set RLE");

    if (SDL_SetSurfaceRLE(surface, enable) == false)
        throw ApiException("SDL_SetSurfaceRLE()");
}

//! @brief Determines whether the surface has a colour key enabled.
bool Surface::hasColourKey() const
{
    return (_surface != nullptr) && SDL_SurfaceHasColorKey(_surface);
}

//! @brief Attempts to obtain the current colour key value.
//! @param[out] key Receives the colour key pixel value on success.
//! @retval true A colour key is set and has been returned.
//! @retval false The object is unbound or no colour key is set.
bool Surface::tryGetColourKey(uint32_t &key) const
{
    return (_surface != nullptr) &&
        SDL_GetSurfaceColorKey(_surface, &key);
}

//! @brief Sets or clears the colour key for the surface.
//! @param[in] enable True to enable the colour key, false to disable.
//! @param[in] key The pixel value to treat as transparent (ignored when
//! disabling).
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceColorKey() fails.
void Surface::setColourKey(bool enable, uint32_t key)
{
    auto surface = verifyAccess("Set colour key");

    if (SDL_SetSurfaceColorKey(surface, enable, key) == false)
        throw ApiException("SDL_SetSurfaceColorKey()");
}

//! @brief Gets the additional colour modulation values applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetSurfaceColorMod() fails.
void Surface::getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    auto surface = verifyAccess("Get colour mod");

    if (SDL_GetSurfaceColorMod(surface, &r, &g, &b) == false)
        throw ApiException("SDL_GetSurfaceColorMod()");
}

//! @brief Sets the additional colour modulation values applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceColorMod() fails.
void Surface::setColourMod(uint8_t r, uint8_t g, uint8_t b)
{
    auto surface = verifyAccess("Set colour mod");

    if (SDL_SetSurfaceColorMod(surface, r, g, b) == false)
        throw ApiException("SDL_SetSurfaceColorMod()");
}

//! @brief Gets the alpha modulation value applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetSurfaceAlphaMod() fails.
uint8_t Surface::getAlphaMod() const
{
    auto surface = verifyAccess("Get alpha mod");
    uint8_t alpha = 0;

    if (SDL_GetSurfaceAlphaMod(surface, &alpha) == false)
        throw ApiException("SDL_GetSurfaceAlphaMod()");

    return alpha;
}

//! @brief Sets the alpha modulation value applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceAlphaMod() fails.
void Surface::setAlphaMod(uint8_t alpha)
{
    auto surface = verifyAccess("Set alpha mod");

    if (SDL_SetSurfaceAlphaMod(surface, alpha) == false)
        throw ApiException("SDL_SetSurfaceAlphaMod()");
}

//! @brief Gets the blend mode applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetSurfaceBlendMode() fails.
SDL_BlendMode Surface::getBlendMode() const
{
    auto surface = verifyAccess("Get blend mode");
    SDL_BlendMode mode = SDL_BLENDMODE_NONE;

    if (SDL_GetSurfaceBlendMode(surface, &mode) == false)
        throw ApiException("SDL_GetSurfaceBlendMode()");

    return mode;
}

//! @brief Sets the blend mode applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceBlendMode() fails.
void Surface::setBlendMode(SDL_BlendMode mode)
{
    auto surface = verifyAccess("Set blend mode");

    if (SDL_SetSurfaceBlendMode(surface, mode) == false)
        throw ApiException("SDL_SetSurfaceBlendMode()");
}

//! @brief Attempts to obtain the current clip rectangle.
//! @param[out] clip Receives the clip rectangle on success.
//! @retval true A clip rectangle was returned.
//! @retval false The object is unbound or no clip rectangle is set.
bool Surface::tryGetClipRect(SDL_Rect &clip) const
{
    return (_surface != nullptr) &&
        SDL_GetSurfaceClipRect(_surface, &clip);
}

//! @brief Sets the clip rectangle used when blitting into the
//! surface.
//! @param[in] clip The new clip rectangle, or nullptr to disable clipping.
//! @throws ObjectNotBoundException If the object is unbound.
bool Surface::setClipRect(const SDL_Rect &clip)
{
    auto surface = verifyAccess("Set clip rect");

    return SDL_SetSurfaceClipRect(surface, &clip);
}

//! @brief Disables clipping for subsequent blits into the surface.
//! @throws ObjectNotBoundException If the object is unbound.
void Surface::resetClipRect()
{
    auto surface = verifyAccess("Reset clip rect");

    SDL_SetSurfaceClipRect(surface, nullptr);
}

//! @brief Creates a new blank surface of the given dimensions.
//! @param[in] width The width, in pixels.
//! @param[in] height The height, in pixels.
//! @param[in] format The pixel format of the new surface.
//! @throws ApiException If SDL_CreateSurface() fails.
void Surface::create(int width, int height, SDL_PixelFormat format)
{
    release();

    _surface = SDL_CreateSurface(width, height, format);

    if (_surface == nullptr)
        throw ApiException("SDL_CreateSurface()");
}

//! @brief Creates a surface referencing an existing block of pixel data.
//! @param[in] width The width, in pixels.
//! @param[in] height The height, in pixels.
//! @param[in] format The pixel format of the pixel data.
//! @param[in] pixels A pointer to the pixel data, whose lifetime must exceed
//! the lifetime of the surface.
//! @param[in] pitch The count of bytes between adjacent rows.
//! @throws ApiException If SDL_CreateSurfaceFrom() fails.
void Surface::createFrom(int width, int height, SDL_PixelFormat format,
                         void *pixels, int pitch)
{
    release();

    _surface = SDL_CreateSurfaceFrom(width, height, format, pixels, pitch);

    if (_surface == nullptr)
        throw ApiException("SDL_CreateSurfaceFrom()");
}

//! @brief Loads a BMP file from disk into a new surface.
//! @param[in] file The UTF-8 path to the BMP file.
//! @return A new Surface wrapping the loaded image.
//! @throws ApiException If SDL_LoadBMP() fails.
Surface Surface::loadBMP(utf8_cptr_t file)
{
    SDL_Surface *loaded = SDL_LoadBMP(file);

    if (loaded == nullptr)
        throw ApiException("SDL_LoadBMP()");

    return Surface(loaded);
}

//! @brief Saves the surface to a BMP file.
//! @param[in] file The UTF-8 path to write to.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SaveBMP() fails.
void Surface::saveBMP(utf8_cptr_t file) const
{
    auto surface = verifyAccess("Save BMP");

    if (SDL_SaveBMP(surface, file) == false)
        throw ApiException("SDL_SaveBMP()");
}

//! @brief Creates an independent copy of the surface.
//! @return A new Surface which is a duplicate of the current one.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_DuplicateSurface() fails.
Surface Surface::duplicate() const
{
    auto surface = verifyAccess("Duplicate");
    SDL_Surface *copy = SDL_DuplicateSurface(surface);

    if (copy == nullptr)
        throw ApiException("SDL_DuplicateSurface()");

    return Surface(copy);
}

//! @brief Creates a scaled copy of the surface.
//! @param[in] width The width of the resulting surface, in pixels.
//! @param[in] height The height of the resulting surface, in pixels.
//! @param[in] mode The scaling filter to apply.
//! @return A new surface containing the scaled result.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ScaleSurface() fails.
Surface Surface::scaled(int width, int height, SDL_ScaleMode mode) const
{
    auto surface = verifyAccess("Scale");
    SDL_Surface *result = SDL_ScaleSurface(surface, width, height, mode);

    if (result == nullptr)
        throw ApiException("SDL_ScaleSurface()");

    return Surface(result);
}

//! @brief Creates a copy of the surface converted to a different pixel format.
//! @param[in] format The target pixel format.
//! @return A new surface in the requested format.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ConvertSurface() fails.
Surface Surface::converted(SDL_PixelFormat format) const
{
    auto surface = verifyAccess("Convert");
    SDL_Surface *result = SDL_ConvertSurface(surface, format);

    if (result == nullptr)
        throw ApiException("SDL_ConvertSurface()");

    return Surface(result);
}

//! @brief Creates a copy of the surface converted to a different pixel format
//! and colour space.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ConvertSurfaceAndColorspace() fails.
Surface Surface::convertedWithColourspace(SDL_PixelFormat format,
                                         SDL_Palette *palette,
                                         SDL_Colorspace colourspace,
                                         SDL_PropertiesID props) const
{
    auto surface = verifyAccess("Convert with colour space");
    SDL_Surface *result = SDL_ConvertSurfaceAndColorspace(surface, format, palette,
                                                          colourspace, props);

    if (result == nullptr)
        throw ApiException("SDL_ConvertSurfaceAndColorspace()");

    return Surface(result);
}

//! @brief Flips the surface horizontally, vertically or both.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FlipSurface() fails.
void Surface::flip(SDL_FlipMode flip)
{
    auto surface = verifyAccess("Flip");

    if (SDL_FlipSurface(surface, flip) == false)
        throw ApiException("SDL_FlipSurface()");
}

//! @brief Fills the surface with a fixed colour value.
//! @param[in] value The colour value used to set all pixels.
//! @throws ObjectNotBoundException If the object is not currently bound to
//! a valid surface resource.
//! @throws ApiException If the clear operation failed.
void Surface::clear(const SDL_FColor &value) const
{
    auto surface = verifyAccess("Clear");

    if (SDL_ClearSurface(surface, value.r, value.g, value.b, value.a) == false)
        throw ApiException("SDL_ClearSurface()");
}

//! @brief Fills a rectangular region of the surface with a pixel value.
//! @param[in] rect The rectangle to fill, or nullptr to fill the whole surface.
//! @param[in] pixelValue The packed pixel value to write, matching the
//! surface's pixel format.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FillSurfaceRect() fails.
void Surface::fillRect(const SDL_Rect *rect, uint32_t pixelValue)
{
    auto surface = verifyAccess("Fill rectangle");

    if (SDL_FillSurfaceRect(surface, rect, pixelValue) == false)
        throw ApiException("SDL_FillSurfaceRect()");
}

//! @brief Fills a collection of rectangles with a single pixel value.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FillSurfaceRects() fails.
void Surface::fillRects(const SDL_Rect *rects, int count, uint32_t pixelValue)
{
    auto surface = verifyAccess("Fill rectangles");

    if (SDL_FillSurfaceRects(surface, rects, count, pixelValue) == false)
        throw ApiException("SDL_FillSurfaceRects()");
}

//! @brief Blits from this surface into another.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurface() fails.
void Surface::blit(const SDL_Rect *srcRect, const Surface &dst,
                   const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit");
    auto target = dst.verifyAccess("Receive blit");

    if (SDL_BlitSurface(surface, srcRect, target, dstRect) == false)
        throw ApiException("SDL_BlitSurface()");
}

//! @brief Blits from this surface into another with scaling.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceScaled() fails.
void Surface::blitScaled(const SDL_Rect *srcRect, const Surface &dst,
                         const SDL_Rect *dstRect, SDL_ScaleMode mode) const
{
    auto surface = verifyAccess("Blit scaled");
    auto target = dst.verifyAccess("Receive scaled blit");

    if (SDL_BlitSurfaceScaled(surface, srcRect, target, dstRect, mode) == false)
        throw ApiException("SDL_BlitSurfaceScaled()");
}

//! @brief Blits with no bounds checking, matching the pixel formats of the
//! two surfaces.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceUnchecked() fails.
void Surface::blitUnchecked(const SDL_Rect &srcRect, const Surface &dst,
                            const SDL_Rect &dstRect) const
{
    auto surface = verifyAccess("Blit unchecked");
    auto target = dst.verifyAccess("Receive unchecked blit");

    if (SDL_BlitSurfaceUnchecked(surface, &srcRect, target, &dstRect) == false)
        throw ApiException("SDL_BlitSurfaceUnchecked()");
}

//! @brief Tiles this surface across a region of another.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceTiled() fails.
void Surface::blitTiled(const SDL_Rect *srcRect, const Surface &dst,
                        const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit tiled");
    auto target = dst.verifyAccess("Receive tiled blit");

    if (SDL_BlitSurfaceTiled(surface, srcRect, target, dstRect) == false)
        throw ApiException("SDL_BlitSurfaceTiled()");
}

//! @brief Tiles this surface across a region of another with scaling.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceTiledWithScale() fails.
void Surface::blitTiledWithScale(const SDL_Rect *srcRect, float scale,
                                 SDL_ScaleMode mode, const Surface &dst,
                                 const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit tiled with scale");
    auto target = dst.verifyAccess("Receive scaled tiled blit");

    if (SDL_BlitSurfaceTiledWithScale(surface, srcRect, scale, mode, target,
                                      dstRect) == false)
        throw ApiException("SDL_BlitSurfaceTiledWithScale()");
}

//! @brief Blits this surface into another using nine-slice scaling.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurface9Grid() fails.
void Surface::blit9Grid(const SDL_Rect *srcRect,
                        int leftWidth, int rightWidth,
                        int topHeight, int bottomHeight,
                        float scale, SDL_ScaleMode mode, const Surface &dst,
                        const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit 9-grid");
    auto target = dst.verifyAccess("Receive 9-grid blit");

    if (SDL_BlitSurface9Grid(surface, srcRect, leftWidth, rightWidth, topHeight,
                             bottomHeight, scale, mode, target, dstRect) == false)
        throw ApiException("SDL_BlitSurface9Grid()");
}

//! @brief Stretches this surface into a destination rectangle.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_StretchSurface() fails.
void Surface::stretch(const SDL_Rect *srcRect, const Surface &dst,
                      const SDL_Rect *dstRect, SDL_ScaleMode mode) const
{
    auto surface = verifyAccess("Stretch");
    auto target = dst.verifyAccess("Receive stretch");

    if (SDL_StretchSurface(surface, srcRect, target, dstRect, mode) == false)
        throw ApiException("SDL_StretchSurface()");
}

//! @brief Pre-multiplies the alpha component into the RGB channels of the
//! surface.
//! @param[in] linear True to pre-multiply in linear space, false for sRGB.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_PremultiplySurfaceAlpha() fails.
void Surface::premultiplyAlpha(bool linear)
{
    auto surface = verifyAccess("Pre-multiply alpha");

    if (SDL_PremultiplySurfaceAlpha(surface, linear) == false)
        throw ApiException("SDL_PremultiplySurfaceAlpha()");
}

//! @brief Reads a single pixel as 8-bit RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixel() fails.
void Surface::readPixel(const SDL_Point &at, SDL_Color &colour) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixel(surface, at.x, at.y, &colour.r,
                            &colour.g, &colour.b, &colour.a) == false)
        throw ApiException("SDL_ReadSurfacePixel()");
}

//! @brief Reads a single pixel as 8-bit RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixel() fails.
void Surface::readPixel(int x, int y, uint8_t &r, uint8_t &g,
                        uint8_t &b, uint8_t &a) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a) == false)
        throw ApiException("SDL_ReadSurfacePixel()");
}

//! @brief Reads a single pixel as normalised float RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixelFloat() fails.
void Surface::readPixelFloat(const SDL_Point &at, SDL_FColor &colour) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixelFloat(surface, at.x, at.y, &colour.r,
                                  &colour.g, &colour.b, &colour.a) == false)
        throw ApiException("SDL_ReadSurfacePixelFloat()");
}

//! @brief Reads a single pixel as normalised float RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixelFloat() fails.
void Surface::readPixelFloat(int x, int y, float &r, float &g,
                             float &b, float &a) const
{
    auto surface = verifyAccess("Read pixel (float)");

    if (SDL_ReadSurfacePixelFloat(surface, x, y, &r, &g, &b, &a) == false)
        throw ApiException("SDL_ReadSurfacePixelFloat()");
}

//! @brief Writes a single pixel using 8-bit RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixel() fails.
void Surface::writePixel(const SDL_Point &at, const SDL_Color &colour)
{
    auto surface = verifyAccess("Write pixel");

    if (SDL_WriteSurfacePixel(surface, at.x, at.y,
                              colour.r, colour.g,
                              colour.b, colour.a) == false)
        throw ApiException("SDL_WriteSurfacePixel()");
}

//! @brief Writes a single pixel using 8-bit RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixel() fails.
void Surface::writePixel(int x, int y, uint8_t r, uint8_t g,
                         uint8_t b, uint8_t a)
{
    auto surface = verifyAccess("Write pixel");

    if (SDL_WriteSurfacePixel(surface, x, y, r, g, b, a) == false)
        throw ApiException("SDL_WriteSurfacePixel()");
}

//! @brief Writes a single pixel using normalised float RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixelFloat() fails.
void Surface::writePixelFloat(const SDL_Point &at, const SDL_FColor &colour)
{
    auto surface = verifyAccess("Write pixel (float)");

    if (SDL_WriteSurfacePixelFloat(surface, at.x, at.y,
                                   colour.r, colour.g,
                                   colour.b, colour.a) == false)
        throw ApiException("SDL_WriteSurfacePixelFloat()");
}

//! @brief Writes a single pixel using normalised float RGBA values.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixelFloat() fails.
void Surface::writePixelFloat(int x, int y, float r, float g, float b, float a)
{
    auto surface = verifyAccess("Write pixel (float)");

    if (SDL_WriteSurfacePixelFloat(surface, x, y, r, g, b, a) == false)
        throw ApiException("SDL_WriteSurfacePixelFloat()");
}

//! @brief Releases any wrapped surface resource. Safe to call on an unbound
//! wrapper. Errors from SDL are swallowed to preserve the destructor's
//! noexcept guarantee.
void Surface::release() noexcept
{
    auto surface = std::exchange(_surface, nullptr);
    auto window = std::exchange(_associatedWindow, nullptr);

    if (_isOwned && (surface != nullptr))
    {
        if (window == nullptr)
        {
            SDL_DestroySurface(surface);
        }
        else
        {
            SDL_DestroyWindowSurface(window);
        }
    }

    _isOwned = false;
}

//! @brief Locks the surface so that pixels can be randomly accessed.
//! @return An object wrapping the locked surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws OperationException If the surface is already locked.
//! @throws ApiException If SDL_LockSurface() fails.
LockedSurface Surface::lock() const
{
    auto surface = verifyAccess("Lock surface");

    if (SDL_MUSTLOCK(surface) && ((surface->flags & SDL_SURFACE_LOCKED) != 0))
        throw OperationException("Surface already locked.");

    if (SDL_LockSurface(surface) == false)
        throw ApiException("SDL_LockSurface()");

    return LockedSurface(surface);
}

//! @brief Releases any wrapped surface resource and acquires another from
//! another wrapper.
//! @param[in] rhs The wrapper to acquire the resource from.
//! @return A reference to the current object.
Surface &Surface::operator=(Surface &&rhs) noexcept
{
    if ((_surface == rhs._surface) &&
        (_associatedWindow == rhs._associatedWindow))
        return *this;

    release();

    _surface = std::exchange(rhs._surface, nullptr);
    _associatedWindow = std::exchange(rhs._associatedWindow, nullptr);
    _isOwned = std::exchange(rhs._isOwned, false);

    return *this;
}

//! @brief Ensures the object wraps a valid surface resource before using it
//! for an operation.
//! @param[in] operation A description of the operation to be performed.
//! @return A valid pointer to the underlying surface resource.
//! @throws ObjectNotBoundException If the object is not currently bound to
//! a valid surface resource.
SDL_Surface *Surface::verifyAccess(utf8_cptr_t operation) const
{
    if (_surface == nullptr)
        throw ObjectNotBoundException("SDL Surface", operation);

    return _surface;
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
