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
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/Primitives.hpp"
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
//! @return A pointer to the top left pixel. Rows are separated by
//! getPitch() bytes, which may exceed the width times the bytes per pixel.
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
//! surface.
//! @return A description carrying the bits and bytes per pixel and the
//! channel masks and shifts, or nullptr if the object is in an unbound
//! state.
//! @details The description is owned by SDL and remains valid for the
//! lifetime of the process, so it is safe to cache.
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
//! @return A PropertySet giving access to surface properties such as
//! SDL_PROP_SURFACE_SDR_WHITE_POINT_FLOAT and
//! SDL_PROP_SURFACE_HDR_HEADROOM_FLOAT.
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
//! @return The SDL_Colorspace describing how the surface's pixel values are
//! interpreted, or SDL_COLORSPACE_UNKNOWN on failure.
//! @throws ObjectNotBoundException If the object is unbound.
SDL_Colorspace Surface::getColourspace() const
{
    return SDL_GetSurfaceColorspace(verifyAccess("Get colour space"));
}

//! @brief Sets the colour space of the surface.
//! @param[in] colourspace An SDL_Colorspace value describing how the
//! surface's pixel values should be interpreted.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL fails to set the colour space.
//! @details This changes only the interpretation of the pixels in colour
//! operations, never the stored pixel values themselves. This function is
//! not thread safe.
void Surface::setColourspace(SDL_Colorspace colourspace)
{
    auto surface = verifyAccess("Set colour space");

    if (SDL_SetSurfaceColorspace(surface, colourspace) == false)
        throw ApiException("SDL_SetSurfaceColorspace()");
}

//! @brief Determines whether the surface has additional images beyond its
//! primary one.
//! @retval true One or more alternate representations are attached.
//! @retval false The object is unbound, or only the primary image exists.
//! @details Alternate images hold the same picture at other resolutions,
//! which lets SDL pick an appropriate one for high-DPI use, as
//! Window::setIcon() does.
bool Surface::hasAlternateImages() const
{
    return (_surface != nullptr) && SDL_SurfaceHasAlternateImages(_surface);
}

//! @brief Gets all images associated with the surface, including the primary.
//! @return The images belonging to the surface, or an empty vector when the
//! surface is unbound.
//! @throws ApiException If SDL_GetSurfaceImages() fails.
//! @details The returned wrappers are non-owning, so destroying them leaves
//! the images attached to this surface, and they become invalid once this
//! surface is released or removeAlternateImages() is called. The first
//! element is the primary image.
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
//! @details Safe to call on an unbound object, in which case it does
//! nothing. The primary image is left untouched.
void Surface::removeAlternateImages()
{
    if (_surface != nullptr)
        SDL_RemoveSurfaceAlternateImages(_surface);
}

//! @brief Determines whether the surface has an associated palette.
//! @retval true A palette is associated with the surface.
//! @retval false The object is unbound, or no palette is set.
bool Surface::hasPalette() const
{
    return (_surface != nullptr) && (SDL_GetSurfacePalette(_surface) != nullptr);
}

//! @brief Gets the palette associated with the surface.
//! @return The palette, or nullptr if none is set or the object is unbound.
//! @details The palette is owned by the surface, so it must not be freed by
//! the caller and is invalidated when the surface is released.
SDL_Palette *Surface::getPalette() const
{
    return (_surface == nullptr) ? nullptr : SDL_GetSurfacePalette(_surface);
}

//! @brief Associates a palette with the surface.
//! @param[in] palette The palette to associate, or nullptr to remove the
//! current palette.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfacePalette() fails.
//! @details The surface takes a reference to @p palette rather than
//! copying it, so the palette must outlive the surface, and changes made to
//! it afterwards affect how the surface's pixels are interpreted. This
//! function is not thread safe.
void Surface::setPalette(SDL_Palette *palette)
{
    auto surface = verifyAccess("Set palette");

    if (SDL_SetSurfacePalette(surface, palette) == false)
        throw ApiException("SDL_SetSurfacePalette()");
}

//! @brief Creates a palette suitable for the surface and assigns it.
//! @return A pointer to the newly created palette, owned by the surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_CreateSurfacePalette() fails, which includes
//! the case of a surface whose format is not indexed.
//! @details Only meaningful for surfaces with an indexed pixel format. The
//! new palette is initialised to white for 1-bit formats and to a default
//! ramp otherwise, so its entries usually need filling in afterwards. This
//! function is not thread safe.
SDL_Palette *Surface::createAndSetPalette()
{
    auto surface = verifyAccess("Create palette");

    SDL_Palette *palette = SDL_CreateSurfacePalette(surface);

    if (palette == nullptr)
        throw ApiException("SDL_CreateSurfacePalette()");

    return palette;
}

//! @brief Determines whether RLE acceleration is enabled for the surface.
//! @retval true RLE acceleration is enabled.
//! @retval false The object is unbound, or RLE is disabled.
bool Surface::hasRLE() const
{
    return (_surface != nullptr) && SDL_SurfaceHasRLE(_surface);
}

//! @brief Enables or disables RLE acceleration for the surface.
//! @param[in] enable True to enable RLE, false to disable.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceRLE() fails.
//! @details RLE makes colour-key and alpha-blended blits considerably
//! faster, but an RLE surface must be locked before its pixels can be
//! accessed directly - needsLock() reports this. This function is not
//! thread safe.
void Surface::setRLE(bool enable)
{
    auto surface = verifyAccess("Set RLE");

    if (SDL_SetSurfaceRLE(surface, enable) == false)
        throw ApiException("SDL_SetSurfaceRLE()");
}

//! @brief Determines whether the surface has a colour key enabled.
//! @retval true A transparent pixel value is set.
//! @retval false The object is unbound, or no colour key is set.
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
//! disabling), packed in the surface's own pixel format as produced by
//! SDL_MapRGB().
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceColorKey() fails.
//! @details Pixels matching @p key are skipped when the surface is blitted,
//! which is the classic way to give an image a transparent background
//! without an alpha channel. This function is not thread safe.
void Surface::setColourKey(bool enable, uint32_t key)
{
    auto surface = verifyAccess("Set colour key");

    if (SDL_SetSurfaceColorKey(surface, enable, key) == false)
        throw ApiException("SDL_SetSurfaceColorKey()");
}

//! @brief Gets the additional colour modulation values applied when blitting.
//! @param[out] r Receives the red modulation value.
//! @param[out] g Receives the green modulation value.
//! @param[out] b Receives the blue modulation value.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_GetSurfaceColorMod() fails.
void Surface::getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    auto surface = verifyAccess("Get colour mod");

    if (SDL_GetSurfaceColorMod(surface, &r, &g, &b) == false)
        throw ApiException("SDL_GetSurfaceColorMod()");
}

//! @brief Sets the additional colour modulation values applied when blitting.
//! @param[in] r The red modulation value.
//! @param[in] g The green modulation value.
//! @param[in] b The blue modulation value.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceColorMod() fails.
//! @details Each source channel is scaled by its modulation value divided
//! by 255 as the surface is blitted, so 255 leaves the channel unchanged.
//! This function is not thread safe.
void Surface::setColourMod(uint8_t r, uint8_t g, uint8_t b)
{
    auto surface = verifyAccess("Set colour mod");

    if (SDL_SetSurfaceColorMod(surface, r, g, b) == false)
        throw ApiException("SDL_SetSurfaceColorMod()");
}

//! @brief Gets the alpha modulation value applied when blitting.
//! @return The alpha modulation value, where 255 leaves source alpha
//! unchanged.
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
//! @param[in] alpha The alpha value multiplied into blit operations, where
//! 255 leaves source alpha unchanged.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceAlphaMod() fails.
//! @details Source alpha is scaled by @p alpha divided by 255 as the
//! surface is blitted. This function is not thread safe.
void Surface::setAlphaMod(uint8_t alpha)
{
    auto surface = verifyAccess("Set alpha mod");

    if (SDL_SetSurfaceAlphaMod(surface, alpha) == false)
        throw ApiException("SDL_SetSurfaceAlphaMod()");
}

//! @brief Gets the blend mode applied when blitting.
//! @throws ObjectNotBoundException If the object is unbound.
//! @return The SDL_BlendMode used when this surface is the source of a
//! blit.
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
//! @param[in] mode The SDL_BlendMode to use when this surface is the source
//! of a blit.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_SetSurfaceBlendMode() fails.
//! @details The mode belongs to the source surface, so to copy pixels
//! without blending against what is already in the destination, set
//! SDL_BLENDMODE_NONE on the surface being copied from. This function is not
//! thread safe.
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
//! @param[in] clip The new clip rectangle, in surface coordinates.
//! @retval true The clip rectangle was set and intersects the surface.
//! @retval false @p clip lies entirely outside the surface, so no drawing
//! into it can take effect.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details The rectangle is intersected with the bounds of the surface, so
//! blits can never write outside it. Use resetClipRect() to restore
//! clipping to the whole surface. This function is not thread safe.
bool Surface::setClipRect(const SDL_Rect &clip)
{
    auto surface = verifyAccess("Set clip rect");

    return SDL_SetSurfaceClipRect(surface, &clip);
}

//! @brief Restores clipping to cover the whole of the surface.
//! @throws ObjectNotBoundException If the object is unbound.
//! @details Blits are still bounded by the surface itself; only the
//! narrower rectangle set by setClipRect() is removed. Any failure reported
//! by SDL is ignored. This function is not thread safe.
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
//! @param[in] format The pixel format of the resulting surface.
//! @param[in] palette The palette the result should use, or nullptr to let
//! SDL choose one. Only meaningful for indexed formats.
//! @param[in] colourspace The colour space the result should be expressed
//! in.
//! @param[in] props Additional conversion properties, such as
//! SDL_PROP_SURFACE_TONEMAP_OPERATOR_STRING, or 0 for none.
//! @return A new surface in the requested format and colour space.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ConvertSurfaceAndColorspace() fails.
//! @details Unlike setColourspace(), which only relabels the existing
//! pixels, this converts the pixel values themselves. This function is not
//! thread safe.
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

//! @brief Flips the surface vertically or horizontally, in place.
//! @param[in] flip The direction to flip in: SDL_FLIP_HORIZONTAL,
//! SDL_FLIP_VERTICAL or SDL_FLIP_NONE to do nothing.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FlipSurface() fails.
//! @details The surface's own pixels are rearranged rather than a flipped
//! copy being produced. This function is not thread safe.
void Surface::flip(SDL_FlipMode flip)
{
    auto surface = verifyAccess("Flip");

    if (SDL_FlipSurface(surface, flip) == false)
        throw ApiException("SDL_FlipSurface()");
}

//! @brief Fills the surface with a fixed colour value.
//! @param[in] value The colour used to set all pixels, with components
//! normalised to the range 0.0 to 1.0.
//! @throws ObjectNotBoundException If the object is not currently bound to
//! a valid surface resource.
//! @throws ApiException If the clear operation failed.
//! @details The whole surface is overwritten, ignoring any clip rectangle,
//! and the colour is converted into the surface's own format and colour
//! space. This function is not thread safe.
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
//! @details The fill is clipped to the surface's clip rectangle, and writes
//! the pixel value directly without blending. Use SDL_MapRGB() or
//! SDL_MapRGBA() to produce @p pixelValue. This function is not thread safe.
void Surface::fillRect(const SDL_Rect *rect, uint32_t pixelValue)
{
    auto surface = verifyAccess("Fill rectangle");

    if (SDL_FillSurfaceRect(surface, rect, pixelValue) == false)
        throw ApiException("SDL_FillSurfaceRect()");
}

//! @brief Fills a collection of rectangles with a single pixel value.
//! @param[in] rects The array of rectangles to fill. Must hold at least
//! @p count elements and must not be nullptr.
//! @param[in] count The count of rectangles to fill.
//! @param[in] pixelValue The packed pixel value to write, matching the
//! surface's pixel format.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_FillSurfaceRects() fails.
//! @details Each fill is clipped to the surface's clip rectangle, and
//! writes the pixel value directly without blending. This function is not
//! thread safe.
void Surface::fillRects(const SDL_Rect *rects, int count, uint32_t pixelValue)
{
    auto surface = verifyAccess("Fill rectangles");

    if (SDL_FillSurfaceRects(surface, rects, count, pixelValue) == false)
        throw ApiException("SDL_FillSurfaceRects()");
}

//! @brief Performs a fast, clipped copy from this surface into another.
//! @param[in] srcRect The region of this surface to copy, or nullptr for the
//! whole of it.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The position within @p dst to copy to, or nullptr for
//! (0, 0). Only the x and y members are used; the width and height are taken
//! from @p srcRect, so this cannot scale - use blitScaled() for that.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurface() fails.
//! @details The copy is clipped to @p dst's clip rectangle. How the pixels
//! combine depends on this surface's blend mode and colour key: with
//! SDL_BLENDMODE_BLEND the source is alpha-blended using both its alpha
//! channel and its per-surface alpha, and the colour key is ignored; with
//! SDL_BLENDMODE_NONE the pixels are copied, skipping any which match the
//! colour key. Neither surface may be locked. Only one thread should be
//! using @p dst or this surface at a time.
void Surface::blit(const SDL_Rect *srcRect, const Surface &dst,
                   const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit");
    auto target = dst.verifyAccess("Receive blit");

    if (SDL_BlitSurface(surface, srcRect, target, dstRect) == false)
        throw ApiException("SDL_BlitSurface()");
}

//! @brief Performs a scaled copy from this surface into another.
//! @param[in] srcRect The region of this surface to copy, or nullptr for the
//! whole of it.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The region of @p dst to fill, or nullptr for the whole
//! of it. The source is stretched to fit.
//! @param[in] mode The scaling filter, SDL_SCALEMODE_NEAREST or
//! SDL_SCALEMODE_LINEAR.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceScaled() fails.
//! @details The copy is clipped to @p dst's clip rectangle and obeys this
//! surface's blend mode and colour key, as blit() describes. Neither
//! surface may be locked. Only one thread should be using @p dst or this
//! surface at a time.
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
//! @param[in] srcRect The region of this surface to copy. Unlike blit(),
//! this is required rather than optional.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The target region within @p dst. Also required.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceUnchecked() fails.
//! @details A low-level entry point which assumes both rectangles have
//! already been clipped, and so performs no bounds checking of its own.
//! Passing a rectangle straying outside its surface has undefined results,
//! so prefer blit() unless the clipping has demonstrably been done already.
//! Only one thread should be using @p dst or this surface at a time.
void Surface::blitUnchecked(const SDL_Rect &srcRect, const Surface &dst,
                            const SDL_Rect &dstRect) const
{
    auto surface = verifyAccess("Blit unchecked");
    auto target = dst.verifyAccess("Receive unchecked blit");

    if (SDL_BlitSurfaceUnchecked(surface, &srcRect, target, &dstRect) == false)
        throw ApiException("SDL_BlitSurfaceUnchecked()");
}

//! @brief Tiles this surface across a region of another.
//! @param[in] srcRect The region of this surface to use as the tile, or
//! nullptr for the whole of it.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The region of @p dst to cover, or nullptr for the
//! whole of it.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceTiled() fails.
//! @details The source pixels are repeated as many times as needed to fill
//! @p dstRect completely, at their original size. The destination may use a
//! different pixel format. Only one thread should be using @p dst or this
//! surface at a time.
void Surface::blitTiled(const SDL_Rect *srcRect, const Surface &dst,
                        const SDL_Rect *dstRect) const
{
    auto surface = verifyAccess("Blit tiled");
    auto target = dst.verifyAccess("Receive tiled blit");

    if (SDL_BlitSurfaceTiled(surface, srcRect, target, dstRect) == false)
        throw ApiException("SDL_BlitSurfaceTiled()");
}

//! @brief Tiles this surface across a region of another with scaling.
//! @param[in] srcRect The region of this surface to use as the tile, or
//! nullptr for the whole of it.
//! @param[in] scale The scale applied to @p srcRect to produce each tile,
//! so a 32x32 source at a scale of 2 produces 64x64 tiles.
//! @param[in] mode The scaling filter, SDL_SCALEMODE_NEAREST or
//! SDL_SCALEMODE_LINEAR.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The region of @p dst to cover, or nullptr for the
//! whole of it.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurfaceTiledWithScale() fails.
//! @details The source pixels are scaled and then repeated as many times as
//! needed to fill @p dstRect completely. The destination may use a
//! different pixel format. Only one thread should be using @p dst or this
//! surface at a time.
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
//! @param[in] srcRect The region of this surface forming the 9-grid, or
//! nullptr for the whole of it.
//! @param[in] leftWidth The width, in pixels, of the left corners of
//! @p srcRect.
//! @param[in] rightWidth The width, in pixels, of the right corners.
//! @param[in] topHeight The height, in pixels, of the top corners.
//! @param[in] bottomHeight The height, in pixels, of the bottom corners.
//! @param[in] scale The scale applied when fitting a source corner into a
//! destination corner, or 0.0f for an unscaled copy.
//! @param[in] mode The scaling filter, SDL_SCALEMODE_NEAREST or
//! SDL_SCALEMODE_LINEAR.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The region of @p dst to cover, or nullptr for the
//! whole of it.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_BlitSurface9Grid() fails.
//! @details The source is split into a 3x3 grid using the four corner
//! sizes, with the sides and centre made up of the remaining pixels. The
//! corners are scaled by @p scale and placed in the corners of @p dstRect,
//! then the sides and centre are stretched to cover what is left. This is
//! the usual way to draw a resizable panel or button without distorting its
//! borders. Only one thread should be using @p dst or this surface at a
//! time.
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
//! @param[in] srcRect The region of this surface to copy.
//! @param[in] dst The surface to copy into.
//! @param[in] dstRect The region of @p dst to fill, which the source is
//! stretched to cover.
//! @param[in] mode The scaling filter, SDL_SCALEMODE_NEAREST or
//! SDL_SCALEMODE_LINEAR.
//! @throws ObjectNotBoundException If either surface is unbound.
//! @throws ApiException If SDL_StretchSurface() fails.
//! @details A plain stretched pixel copy which, unlike blitScaled(), does
//! not apply blending or the colour key. Only one thread should be using
//! @p dst or this surface at a time.
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
//! @details The surface's own pixels are modified in place, so the
//! operation is not reversible. Pre-multiplied pixels are what
//! SDL_BLENDMODE_BLEND_PREMULTIPLIED expects. This function is not thread
//! safe.
void Surface::premultiplyAlpha(bool linear)
{
    auto surface = verifyAccess("Pre-multiply alpha");

    if (SDL_PremultiplySurfaceAlpha(surface, linear) == false)
        throw ApiException("SDL_PremultiplySurfaceAlpha()");
}

//! @brief Reads a single pixel as 8-bit RGBA values.
//! @param[in] at The column and row of the pixel to read.
//! @param[out] colour Receives the pixel's red, green, blue and alpha
//! components.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixel() fails, which includes
//! @p at lying outside the surface.
//! @details The stored pixel is converted into 8-bit RGBA regardless of the
//! surface's own format, and surfaces without an alpha channel report 255.
//! This is convenient rather than fast; use lock() and LockedSurface for
//! bulk pixel access. This function is not thread safe.
void Surface::readPixel(const SDL_Point &at, SDL_Color &colour) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixel(surface, at.x, at.y, &colour.r,
                            &colour.g, &colour.b, &colour.a) == false)
        throw ApiException("SDL_ReadSurfacePixel()");
}

//! @brief Reads a single pixel as 8-bit RGBA values.
//! @param[in] x The column of the pixel to read.
//! @param[in] y The row of the pixel to read.
//! @param[out] r Receives the red component.
//! @param[out] g Receives the green component.
//! @param[out] b Receives the blue component.
//! @param[out] a Receives the alpha component, 255 when the surface has no
//! alpha channel.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixel() fails, which includes the
//! position lying outside the surface.
//! @details This is convenient rather than fast; use lock() and
//! LockedSurface for bulk pixel access. This function is not thread safe.
void Surface::readPixel(int x, int y, uint8_t &r, uint8_t &g,
                        uint8_t &b, uint8_t &a) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a) == false)
        throw ApiException("SDL_ReadSurfacePixel()");
}

//! @brief Reads a single pixel as normalised float RGBA values.
//! @param[in] at The column and row of the pixel to read.
//! @param[out] colour Receives the components, normalised to the range 0.0
//! to 1.0.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixelFloat() fails, which
//! includes @p at lying outside the surface.
//! @details Preferable to readPixel() for high dynamic range surfaces,
//! whose values can fall outside 0.0 to 1.0 and would be clipped by the
//! 8-bit form. This function is not thread safe.
void Surface::readPixelFloat(const SDL_Point &at, SDL_FColor &colour) const
{
    auto surface = verifyAccess("Read pixel");

    if (SDL_ReadSurfacePixelFloat(surface, at.x, at.y, &colour.r,
                                  &colour.g, &colour.b, &colour.a) == false)
        throw ApiException("SDL_ReadSurfacePixelFloat()");
}

//! @brief Reads a single pixel as normalised float RGBA values.
//! @param[in] x The column of the pixel to read.
//! @param[in] y The row of the pixel to read.
//! @param[out] r Receives the red component, normalised to 0.0 to 1.0.
//! @param[out] g Receives the green component.
//! @param[out] b Receives the blue component.
//! @param[out] a Receives the alpha component, 1.0 when the surface has no
//! alpha channel.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_ReadSurfacePixelFloat() fails, which
//! includes the position lying outside the surface.
//! @details Preferable to readPixel() for high dynamic range surfaces. This
//! function is not thread safe.
void Surface::readPixelFloat(int x, int y, float &r, float &g,
                             float &b, float &a) const
{
    auto surface = verifyAccess("Read pixel (float)");

    if (SDL_ReadSurfacePixelFloat(surface, x, y, &r, &g, &b, &a) == false)
        throw ApiException("SDL_ReadSurfacePixelFloat()");
}

//! @brief Writes a single pixel using 8-bit RGBA values.
//! @param[in] at The column and row of the pixel to write.
//! @param[in] colour The red, green, blue and alpha components to store.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixel() fails, which includes
//! @p at lying outside the surface.
//! @details The colour is converted into the surface's own format, so
//! precision is lost where the format carries fewer bits, and the alpha
//! component is discarded by formats without an alpha channel. The pixel is
//! written directly rather than blended. This is convenient rather than
//! fast; use lock() and LockedSurface for bulk pixel access. This function
//! is not thread safe.
void Surface::writePixel(const SDL_Point &at, const SDL_Color &colour)
{
    auto surface = verifyAccess("Write pixel");

    if (SDL_WriteSurfacePixel(surface, at.x, at.y,
                              colour.r, colour.g,
                              colour.b, colour.a) == false)
        throw ApiException("SDL_WriteSurfacePixel()");
}

//! @brief Writes a single pixel using 8-bit RGBA values.
//! @param[in] x The column of the pixel to write.
//! @param[in] y The row of the pixel to write.
//! @param[in] r The red component.
//! @param[in] g The green component.
//! @param[in] b The blue component.
//! @param[in] a The alpha component, discarded by formats without an alpha
//! channel.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixel() fails, which includes
//! the position lying outside the surface.
//! @details The pixel is written directly rather than blended. This is
//! convenient rather than fast; use lock() and LockedSurface for bulk pixel
//! access. This function is not thread safe.
void Surface::writePixel(int x, int y, uint8_t r, uint8_t g,
                         uint8_t b, uint8_t a)
{
    auto surface = verifyAccess("Write pixel");

    if (SDL_WriteSurfacePixel(surface, x, y, r, g, b, a) == false)
        throw ApiException("SDL_WriteSurfacePixel()");
}

//! @brief Writes a single pixel using normalised float RGBA values.
//! @param[in] at The column and row of the pixel to write.
//! @param[in] colour The components to store, normalised to the range 0.0
//! to 1.0.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixelFloat() fails, which
//! includes @p at lying outside the surface.
//! @details Preferable to writePixel() for high dynamic range surfaces,
//! which can hold values outside 0.0 to 1.0. This function is not thread
//! safe.
void Surface::writePixelFloat(const SDL_Point &at, const SDL_FColor &colour)
{
    auto surface = verifyAccess("Write pixel (float)");

    if (SDL_WriteSurfacePixelFloat(surface, at.x, at.y,
                                   colour.r, colour.g,
                                   colour.b, colour.a) == false)
        throw ApiException("SDL_WriteSurfacePixelFloat()");
}

//! @brief Writes a single pixel using normalised float RGBA values.
//! @param[in] x The column of the pixel to write.
//! @param[in] y The row of the pixel to write.
//! @param[in] r The red component, normalised to the range 0.0 to 1.0.
//! @param[in] g The green component.
//! @param[in] b The blue component.
//! @param[in] a The alpha component.
//! @throws ObjectNotBoundException If the object is unbound.
//! @throws ApiException If SDL_WriteSurfacePixelFloat() fails, which
//! includes the position lying outside the surface.
//! @details Preferable to writePixel() for high dynamic range surfaces.
//! This function is not thread safe.
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
