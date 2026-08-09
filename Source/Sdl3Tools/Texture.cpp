//! @file Sdl3Tools/Texture.cpp
//! @brief The definition of a wrapper for the SDL3 2D SDL_Texture resource.
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

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// LockedTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an unbound LockedTexture.
LockedTexture::LockedTexture() :
    _texture(nullptr),
    _pixels(nullptr),
    _pitch(0),
    _width(0),
    _height(0),
    _format(SDL_PIXELFORMAT_UNKNOWN)
{
}

//! @brief Wraps a texture that has just been locked by SDL_LockTexture.
LockedTexture::LockedTexture(SDL_Texture *texture, void *pixels, int pitch,
                             int width, int height, SDL_PixelFormat format) :
    _texture(texture),
    _pixels(pixels),
    _pitch(pitch),
    _width(width),
    _height(height),
    _format(format)
{
}

//! @brief Acquires a locked texture from another wrapper.
LockedTexture::LockedTexture(LockedTexture &&rhs) noexcept :
    _texture(std::exchange(rhs._texture, nullptr)),
    _pixels(std::exchange(rhs._pixels, nullptr)),
    _pitch(std::exchange(rhs._pitch, 0)),
    _width(std::exchange(rhs._width, 0)),
    _height(std::exchange(rhs._height, 0)),
    _format(std::exchange(rhs._format, SDL_PIXELFORMAT_UNKNOWN))
{
}

//! @brief Unlocks the underlying texture at destruction.
LockedTexture::~LockedTexture()
{
    unlock();
}

//! @brief Determines whether the wrapper holds a locked texture.
bool LockedTexture::isLocked() const
{
    return _texture != nullptr;
}

//! @brief Gets a pointer to the first byte of the locked pixel data.
void *LockedTexture::getBits() const
{
    verifyAccess("Access pixels");

    return _pixels;
}

//! @brief Gets a pointer to the first byte of a row of the locked pixel data.
//! @param[in] row The 0-based row index within the locked region.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @throws ArgumentException If @p row is out of range.
void *LockedTexture::getRow(int row) const
{
    verifyAccess("Access row");

    if ((row < 0) || (row >= _height))
        throw ArgumentException("row");

    return reinterpret_cast<uint8_t *>(_pixels) + (_pitch * row);
}

//! @brief Gets a pointer to a specific pixel within the locked region.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @throws ArgumentException If @p column or @p row is out of range.
void *LockedTexture::getPixel(int column, int row) const
{
    verifyAccess("Access pixel");

    if ((row < 0) || (row >= _height))
        throw ArgumentException("row");

    if ((column < 0) || (column >= _width))
        throw ArgumentException("column");

    auto details = SDL_GetPixelFormatDetails(_format);
    uint8_t *bits = reinterpret_cast<uint8_t *>(_pixels);

    return bits + (_pitch * row) + (column * details->bytes_per_pixel);
}

//! @brief Gets the count of bytes per row within the locked region.
int LockedTexture::getPitch() const
{
    return _pitch;
}

//! @brief Gets the width, in pixels, of the locked region.
int LockedTexture::getWidth() const
{
    return _width;
}

//! @brief Gets the height, in pixels, of the locked region.
int LockedTexture::getHeight() const
{
    return _height;
}

//! @brief Gets the pixel format of the underlying texture.
SDL_PixelFormat LockedTexture::getFormat() const
{
    return _format;
}

//! @brief Unlocks the texture if one is bound. Safe to call repeatedly.
void LockedTexture::unlock() noexcept
{
    auto texture = std::exchange(_texture, nullptr);
    _pixels = nullptr;

    if (texture != nullptr)
        SDL_UnlockTexture(texture);
}

//! @brief Acquires a locked texture from another wrapper.
LockedTexture &LockedTexture::operator=(LockedTexture &&rhs) noexcept
{
    if (_texture == rhs._texture)
        return *this;

    unlock();

    _texture = std::exchange(rhs._texture, nullptr);
    _pixels = std::exchange(rhs._pixels, nullptr);
    _pitch = std::exchange(rhs._pitch, 0);
    _width = std::exchange(rhs._width, 0);
    _height = std::exchange(rhs._height, 0);
    _format = std::exchange(rhs._format, SDL_PIXELFORMAT_UNKNOWN);

    return *this;
}

//! @brief Ensures the wrapper holds a locked texture.
//! @throws ObjectNotBoundException If the texture is not locked.
SDL_Texture *LockedTexture::verifyAccess(utf8_cptr_t operation) const
{
    if (_texture == nullptr)
        throw ObjectNotBoundException("Locked texture", operation);

    return _texture;
}

////////////////////////////////////////////////////////////////////////////////
// Texture Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an unbound Texture wrapper.
Texture::Texture() :
    _parentRenderer(nullptr),
    _texture(nullptr),
    _owned(true)
{
}

//! @brief Wraps an existing SDL_Texture resource.
Texture::Texture(SDL_Renderer *parentRenderer, SDL_Texture *texture, bool owned) :
    _parentRenderer((texture == nullptr) ? nullptr : parentRenderer),
    _texture(texture),
    _owned(owned)
{
}

//! @brief Acquires a texture resource from another wrapper.
Texture::Texture(Texture &&rhs) noexcept :
    _parentRenderer(std::exchange(rhs._parentRenderer, nullptr)),
    _texture(std::exchange(rhs._texture, nullptr)),
    _owned(rhs._owned)
{
    rhs._owned = true;
}

//! @brief Destroys the texture resource on wrapper destruction.
Texture::~Texture()
{
    release();
}

//! @brief Determines whether the wrapper holds an underlying texture.
bool Texture::isBound() const
{
    return _texture != nullptr;
}

//! @brief Indicates whether this wrapper owns the underlying texture.
bool Texture::isOwned() const
{
    return _owned;
}

//! @brief Gets the raw underlying SDL_Texture pointer, or nullptr if unbound.
SDL_Texture *Texture::get() const
{
    return _texture;
}

//! @brief Gets the pixel format of the texture, or SDL_PIXELFORMAT_UNKNOWN if
//! unbound.
SDL_PixelFormat Texture::getFormat() const
{
    if (_texture == nullptr)
        return SDL_PIXELFORMAT_UNKNOWN;

    return static_cast<SDL_PixelFormat>(_texture->format);
}

//! @brief Gets the texture's access mode. Meaningful only when bound.
SDL_TextureAccess Texture::getAccess() const
{
    if (_texture == nullptr)
        return SDL_TEXTUREACCESS_STATIC;

    PropertySet props(SDL_GetTextureProperties(_texture));

    return static_cast<SDL_TextureAccess>(
        props.getInt64(SDL_PROP_TEXTURE_ACCESS_NUMBER, SDL_TEXTUREACCESS_STATIC));
}

//! @brief Gets the width of the texture in pixels, or -1 if unbound.
int Texture::getWidth() const
{
    return (_texture == nullptr) ? -1 : _texture->w;
}

//! @brief Gets the height of the texture in pixels, or -1 if unbound.
int Texture::getHeight() const
{
    return (_texture == nullptr) ? -1 : _texture->h;
}

//! @brief Gets the width and height of the texture as float values, matching
//! the coordinate space used by SDL_RenderTexture.
void Texture::getSize(float &w, float &h) const
{
    auto texture = verifyAccess("Get size");

    if (SDL_GetTextureSize(texture, &w, &h) == false)
        throw ApiException("SDL_GetTextureSize()");
}

//! @brief Gets the SDL property set associated with the texture.
PropertySet Texture::getProperties() const
{
    auto texture = verifyAccess("Get properties");
    SDL_PropertiesID id = SDL_GetTextureProperties(texture);

    if (id == 0)
        throw ApiException("SDL_GetTextureProperties()");

    return PropertySet(id);
}

//! @brief Gets a non-owning wrapper for the renderer associated with the
//! texture.
Renderer Texture::getRenderer() const
{
    auto texture = verifyAccess("Get renderer");
    SDL_Renderer *renderer = SDL_GetRendererFromTexture(texture);

    if (renderer == nullptr)
        throw ApiException("SDL_GetRendererFromTexture()");

    return Renderer(renderer, false);
}

//! @brief Gets the additional colour modulation applied when drawing the
//! texture.
void Texture::getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    auto texture = verifyAccess("Get colour mod");

    if (SDL_GetTextureColorMod(texture, &r, &g, &b) == false)
        throw ApiException("SDL_GetTextureColorMod()");
}

//! @brief Sets the additional colour modulation applied when drawing the
//! texture.
void Texture::setColourMod(uint8_t r, uint8_t g, uint8_t b)
{
    auto texture = verifyAccess("Set colour mod");

    if (SDL_SetTextureColorMod(texture, r, g, b) == false)
        throw ApiException("SDL_SetTextureColorMod()");
}

//! @brief Gets the additional colour modulation as normalised float values.
void Texture::getColorModFloat(float &r, float &g, float &b) const
{
    auto texture = verifyAccess("Get colour mod (float)");

    if (SDL_GetTextureColorModFloat(texture, &r, &g, &b) == false)
        throw ApiException("SDL_GetTextureColorModFloat()");
}

//! @brief Sets the additional colour modulation using normalised float values.
void Texture::setColorModFloat(float r, float g, float b)
{
    auto texture = verifyAccess("Set colour mod (float)");

    if (SDL_SetTextureColorModFloat(texture, r, g, b) == false)
        throw ApiException("SDL_SetTextureColorModFloat()");
}

//! @brief Gets the alpha modulation applied when drawing.
uint8_t Texture::getAlphaMod() const
{
    auto texture = verifyAccess("Get alpha mod");
    uint8_t alpha = 0;

    if (SDL_GetTextureAlphaMod(texture, &alpha) == false)
        throw ApiException("SDL_GetTextureAlphaMod()");

    return alpha;
}

//! @brief Sets the alpha modulation applied when drawing.
void Texture::setAlphaMod(uint8_t alpha)
{
    auto texture = verifyAccess("Set alpha mod");

    if (SDL_SetTextureAlphaMod(texture, alpha) == false)
        throw ApiException("SDL_SetTextureAlphaMod()");
}

//! @brief Gets the alpha modulation as a normalised float value.
float Texture::getAlphaModFloat() const
{
    auto texture = verifyAccess("Get alpha mod (float)");
    float alpha = 0.0f;

    if (SDL_GetTextureAlphaModFloat(texture, &alpha) == false)
        throw ApiException("SDL_GetTextureAlphaModFloat()");

    return alpha;
}

//! @brief Sets the alpha modulation using a normalised float value.
void Texture::setAlphaModFloat(float alpha)
{
    auto texture = verifyAccess("Set alpha mod (float)");

    if (SDL_SetTextureAlphaModFloat(texture, alpha) == false)
        throw ApiException("SDL_SetTextureAlphaModFloat()");
}

//! @brief Gets the current blend mode.
SDL_BlendMode Texture::getBlendMode() const
{
    auto texture = verifyAccess("Get blend mode");
    SDL_BlendMode mode = SDL_BLENDMODE_NONE;

    if (SDL_GetTextureBlendMode(texture, &mode) == false)
        throw ApiException("SDL_GetTextureBlendMode()");

    return mode;
}

//! @brief Sets the current blend mode.
void Texture::setBlendMode(SDL_BlendMode mode)
{
    auto texture = verifyAccess("Set blend mode");

    if (SDL_SetTextureBlendMode(texture, mode) == false)
        throw ApiException("SDL_SetTextureBlendMode()");
}

//! @brief Gets the scale filter used when drawing the texture.
SDL_ScaleMode Texture::getScaleMode() const
{
    auto texture = verifyAccess("Get scale mode");
    SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR;

    if (SDL_GetTextureScaleMode(texture, &mode) == false)
        throw ApiException("SDL_GetTextureScaleMode()");

    return mode;
}

//! @brief Sets the scale filter used when drawing the texture.
void Texture::setScaleMode(SDL_ScaleMode mode)
{
    auto texture = verifyAccess("Set scale mode");

    if (SDL_SetTextureScaleMode(texture, mode) == false)
        throw ApiException("SDL_SetTextureScaleMode()");
}

//! @brief Creates a texture on the given renderer.
void Texture::create(const Renderer &renderer, SDL_PixelFormat format,
                     SDL_TextureAccess access, int width, int height)
{
    auto sdlRenderer = renderer.verifyAccess("Provide renderer for texture");

    release();

    _texture = SDL_CreateTexture(sdlRenderer, format, access, width, height);
    _parentRenderer = sdlRenderer;
    _owned = true;

    if (_texture == nullptr)
    {
        _parentRenderer = nullptr;
        throw ApiException("SDL_CreateTexture()");
    }
}

//! @brief Creates a texture initialised from an existing surface.
void Texture::createFromSurface(const Renderer &renderer, const Surface &surface)
{
    auto sdlRenderer = renderer.verifyAccess("Provide renderer for texture");
    auto sdlSurface = surface.verifyAccess("Provide surface for texture");

    release();

    _texture = SDL_CreateTextureFromSurface(sdlRenderer, sdlSurface);
    _parentRenderer = sdlRenderer;
    _owned = true;

    if (_texture == nullptr)
    {
        _parentRenderer = nullptr;
        throw ApiException("SDL_CreateTextureFromSurface()");
    }
}

//! @brief Creates a texture configured entirely from a property set.
void Texture::createWithProperties(const Renderer &renderer,
                                   const PropertySet &props)
{
    auto sdlRenderer = renderer.verifyAccess("Provide renderer for texture");

    release();

    _texture = SDL_CreateTextureWithProperties(sdlRenderer, props);
    _parentRenderer = sdlRenderer;
    _owned = true;

    if (_texture == nullptr)
    {
        _parentRenderer = nullptr;
        throw ApiException("SDL_CreateTextureWithProperties()");
    }
}

//! @brief Uploads pixel data into the texture.
void Texture::update(const SDL_Rect *area, const void *pixels, int pitch)
{
    auto texture = verifyAccess("Update");

    if (SDL_UpdateTexture(texture, area, pixels, pitch) == false)
        throw ApiException("SDL_UpdateTexture()");
}

//! @brief Uploads planar YUV pixel data into the texture.
void Texture::updateYUV(const SDL_Rect *area,
                        const uint8_t *yPlane, int yPitch,
                        const uint8_t *uPlane, int uPitch,
                        const uint8_t *vPlane, int vPitch)
{
    auto texture = verifyAccess("Update YUV");

    if (SDL_UpdateYUVTexture(texture, area, yPlane, yPitch, uPlane, uPitch,
                             vPlane, vPitch) == false)
        throw ApiException("SDL_UpdateYUVTexture()");
}

//! @brief Uploads planar NV12 / NV21 pixel data into the texture.
void Texture::updateNV(const SDL_Rect *area,
                       const uint8_t *yPlane, int yPitch,
                       const uint8_t *uvPlane, int uvPitch)
{
    auto texture = verifyAccess("Update NV");

    if (SDL_UpdateNVTexture(texture, area, yPlane, yPitch, uvPlane,
                            uvPitch) == false)
        throw ApiException("SDL_UpdateNVTexture()");
}

//! @brief Locks a streaming texture for direct pixel access.
//! @param[in] area The area to lock, or nullptr for the whole texture.
//! @return A LockedTexture describing the locked region.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws OperationException If the texture is not a streaming texture.
//! @throws ApiException If SDL_LockTexture() fails.
LockedTexture Texture::lock(const SDL_Rect *area) const
{
    auto texture = verifyAccess("Lock");

    if (getAccess() != SDL_TEXTUREACCESS_STREAMING)
        throw OperationException("Only streaming textures can be locked.");

    void *pixels = nullptr;
    int pitch = 0;

    if (SDL_LockTexture(texture, area, &pixels, &pitch) == false)
        throw ApiException("SDL_LockTexture()");

    int width = (area == nullptr) ? texture->w : area->w;
    int height = (area == nullptr) ? texture->h : area->h;

    return LockedTexture(texture, pixels, pitch, width, height,
                         static_cast<SDL_PixelFormat>(texture->format));
}

//! @brief Destroys the underlying texture if ownership is held.
void Texture::release() noexcept
{
    auto texture = std::exchange(_texture, nullptr);
    _parentRenderer = nullptr;
    bool owned = _owned;
    _owned = true;

    if ((texture != nullptr) && owned)
        SDL_DestroyTexture(texture);
}

//! @brief Acquires a texture from another wrapper, releasing any previous.
Texture &Texture::operator=(Texture &&rhs) noexcept
{
    if (_texture == rhs._texture)
        return *this;

    release();

    _parentRenderer = std::exchange(rhs._parentRenderer, nullptr);
    _texture = std::exchange(rhs._texture, nullptr);
    _owned = rhs._owned;
    rhs._owned = true;

    return *this;
}

//! @brief Ensures the object is bound to a valid texture.
SDL_Texture *Texture::verifyAccess(utf8_cptr_t operation) const
{
    if (_texture == nullptr)
        throw ObjectNotBoundException("Texture", operation);

    return _texture;
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////
