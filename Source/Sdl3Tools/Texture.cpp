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
#include "Ag/Sdl3Tools/ApiException.hpp"
#include "Ag/Sdl3Tools/Primitives.hpp"
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
//! @retval true The object wraps a valid locked texture.
//! @retval false The object is in an unlocked state.
bool LockedTexture::isLocked() const
{
    return _texture != nullptr;
}

//! @brief Gets a pointer to the first byte of the locked pixel data.
//! @return A pointer to the top left pixel of the locked region. Rows are
//! separated by getPitch() bytes, which may exceed the width times the
//! bytes per pixel.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @details The memory is write-only. Reading back from a locked streaming
//! texture gives undefined results, since the buffer need not hold the
//! texture's current contents.
void *LockedTexture::getBits() const
{
    verifyAccess("Access pixels");

    return _pixels;
}

//! @brief Gets a pointer to the first byte of a row of the locked pixel data.
//! @param[in] row The 0-based row index within the locked region.
//! @return A pointer to the first byte of the row.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @throws ArgumentException If @p row is out of range.
//! @details The memory is write-only, as getBits() describes.
void *LockedTexture::getRow(int row) const
{
    verifyAccess("Access row");

    if ((row < 0) || (row >= _height))
        throw ArgumentException("row");

    return reinterpret_cast<uint8_t *>(_pixels) + (_pitch * row);
}

//! @brief Gets a pointer to a specific pixel within the locked region.
//! @param[in] column The 0-based column index within the locked region.
//! @param[in] row The 0-based row index within the locked region.
//! @return A pointer to the first byte of the pixel.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @throws ArgumentException If @p column or @p row is out of range.
//! @details Only meaningful for formats of one or more whole bytes per
//! pixel; planar and sub-byte formats give undefined results. The memory is
//! write-only, as getBits() describes.
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

//! @brief Gets a pointer to a specific pixel within the locked region.
//! @param[in] at The column and row of the pixel, relative to the top left
//! corner of the locked region.
//! @return A pointer to the first byte of the pixel.
//! @throws ObjectNotBoundException If the texture is not locked.
//! @throws ArgumentException If @p at is out of range.
//! @details Only meaningful for formats of one or more whole bytes per
//! pixel. The memory is write-only, as getBits() describes.
void *LockedTexture::getPixel(const SDL_Point &at) const
{
    verifyAccess("Access pixel");

    if ((at.y < 0) || (at.y >= _height))
        throw ArgumentException("row");

    if ((at.x < 0) || (at.x >= _width))
        throw ArgumentException("column");

    auto details = SDL_GetPixelFormatDetails(_format);
    uint8_t *bits = reinterpret_cast<uint8_t *>(_pixels);

    return bits + (_pitch * at.y) + (at.x * details->bytes_per_pixel);
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

//! @brief Gets the texture's access mode.
//! @return One of SDL_TEXTUREACCESS_STATIC, SDL_TEXTUREACCESS_STREAMING or
//! SDL_TEXTUREACCESS_TARGET, or SDL_TEXTUREACCESS_STATIC when the object is
//! unbound.
//! @details Read from the SDL_PROP_TEXTURE_ACCESS_NUMBER property. Only a
//! streaming texture can be passed to lock(), and only a target texture can
//! be given to Renderer::setTarget().
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
//! @param[out] w Receives the width.
//! @param[out] h Receives the height.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureSize() fails.
void Texture::getSize(float &w, float &h) const
{
    auto texture = verifyAccess("Get size");

    if (SDL_GetTextureSize(texture, &w, &h) == false)
        throw ApiException("SDL_GetTextureSize()");
}

//! @brief Gets the width and height of the texture as float values, matching
//! the coordinate space used by SDL_RenderTexture.
//! @return The horizontal and vertical extent of the texture.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureSize() fails.
SDL_FPoint Texture::getSize() const
{
    auto texture = verifyAccess("Get size");
    FPoint size;

    if (SDL_GetTextureSize(texture, &size.x, &size.y) == false)
        throw ApiException("SDL_GetTextureSize()");

    return size;
}

//! @brief Gets the SDL property set associated with the texture.
//! @return A PropertySet giving access to read-only texture properties such
//! as SDL_PROP_TEXTURE_FORMAT_NUMBER, SDL_PROP_TEXTURE_ACCESS_NUMBER,
//! SDL_PROP_TEXTURE_WIDTH_NUMBER and SDL_PROP_TEXTURE_HEIGHT_NUMBER, plus
//! the backend-specific native handles.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureProperties() fails.
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
//! @return A Renderer wrapper which does not own the underlying resource, so
//! destroying it will not destroy the renderer.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetRendererFromTexture() fails.
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
//! @param[out] r Receives the red modulation, where 255 leaves the channel
//! unchanged.
//! @param[out] g Receives the green modulation.
//! @param[out] b Receives the blue modulation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureColorMod() fails.
//! @details The alpha modulation is reported separately by getAlphaMod();
//! use the parameterless overload to obtain both at once.
void Texture::getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const
{
    auto texture = verifyAccess("Get colour mod");

    if (SDL_GetTextureColorMod(texture, &r, &g, &b) == false)
        throw ApiException("SDL_GetTextureColorMod()");
}

//! @brief Gets the additional colour modulation applied when drawing the
//! texture.
//! @return The colour modulation, with the alpha modulation in the alpha
//! component.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureColorMod() or
//! SDL_GetTextureAlphaMod() fails.
//! @details Unlike the scalar overload, the returned alpha component is
//! meaningful, being obtained via SDL_GetTextureAlphaMod().
SDL_Color Texture::getColourMod() const
{
    auto texture = verifyAccess("Get colour mod");
    Colour colour;

    if (SDL_GetTextureColorMod(texture, &colour.r, &colour.g,
                               &colour.b) == false)
        throw ApiException("SDL_GetTextureColorMod()");

    if (SDL_GetTextureAlphaMod(texture, &colour.a) == false)
        throw ApiException("SDL_GetTextureAlphaMod()");

    return colour;
}

//! @brief Sets the additional colour modulation applied when drawing the
//! texture.
//! @param[in] r The red modulation value, where 255 leaves the channel
//! unchanged.
//! @param[in] g The green modulation value.
//! @param[in] b The blue modulation value.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureColorMod() fails, which also
//! covers renderers without colour modulation support.
//! @details Each source channel is scaled by its modulation value divided
//! by 255 as the texture is drawn. The alpha modulation is left untouched;
//! use the SDL_Color overload to set both at once.
void Texture::setColourMod(uint8_t r, uint8_t g, uint8_t b)
{
    auto texture = verifyAccess("Set colour mod");

    if (SDL_SetTextureColorMod(texture, r, g, b) == false)
        throw ApiException("SDL_SetTextureColorMod()");
}

//! @brief Sets the additional colour modulation applied when drawing the
//! texture.
//! @param[in] colour The colour modulation to apply, the alpha component
//! defining the alpha modulation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureColorMod() or
//! SDL_SetTextureAlphaMod() fails.
//! @details Unlike the scalar overload, the alpha component of @p colour is
//! also applied, via SDL_SetTextureAlphaMod().
void Texture::setColourMod(const SDL_Color &colour)
{
    auto texture = verifyAccess("Set colour mod");

    if (SDL_SetTextureColorMod(texture, colour.r, colour.g, colour.b) == false)
        throw ApiException("SDL_SetTextureColorMod()");

    if (SDL_SetTextureAlphaMod(texture, colour.a) == false)
        throw ApiException("SDL_SetTextureAlphaMod()");
}

//! @brief Gets the additional colour modulation as normalised float values.
//! @param[out] r Receives the red modulation, where 1.0f leaves the channel
//! unchanged.
//! @param[out] g Receives the green modulation.
//! @param[out] b Receives the blue modulation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureColorModFloat() fails.
void Texture::getColourModFloat(float &r, float &g, float &b) const
{
    auto texture = verifyAccess("Get colour mod (float)");

    if (SDL_GetTextureColorModFloat(texture, &r, &g, &b) == false)
        throw ApiException("SDL_GetTextureColorModFloat()");
}

//! @brief Gets the additional colour modulation as normalised float values.
//! @return The colour modulation, with the alpha modulation in the alpha
//! component.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureColorModFloat() or
//! SDL_GetTextureAlphaModFloat() fails.
//! @details Unlike the scalar overload, the returned alpha component is
//! meaningful, being obtained via SDL_GetTextureAlphaModFloat().
SDL_FColor Texture::getColourModFloat() const
{
    auto texture = verifyAccess("Get colour mod (float)");
    FColour colour;

    if (SDL_GetTextureColorModFloat(texture, &colour.r, &colour.g,
                                    &colour.b) == false)
        throw ApiException("SDL_GetTextureColorModFloat()");

    if (SDL_GetTextureAlphaModFloat(texture, &colour.a) == false)
        throw ApiException("SDL_GetTextureAlphaModFloat()");

    return colour;
}

//! @brief Sets the additional colour modulation using normalised float values.
//! @param[in] r The red modulation, where 1.0f leaves the channel
//! unchanged.
//! @param[in] g The green modulation.
//! @param[in] b The blue modulation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureColorModFloat() fails.
//! @details The alpha modulation is left untouched; use the SDL_FColor
//! overload to set both at once.
void Texture::setColourModFloat(float r, float g, float b)
{
    auto texture = verifyAccess("Set colour mod (float)");

    if (SDL_SetTextureColorModFloat(texture, r, g, b) == false)
        throw ApiException("SDL_SetTextureColorModFloat()");
}

//! @brief Sets the additional colour modulation using normalised float values.
//! @param[in] colour The colour modulation to apply, the alpha component
//! defining the alpha modulation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureColorModFloat() or
//! SDL_SetTextureAlphaModFloat() fails.
//! @details Unlike the scalar overload, the alpha component of @p colour is
//! also applied, via SDL_SetTextureAlphaModFloat().
void Texture::setColourModFloat(const SDL_FColor &colour)
{
    auto texture = verifyAccess("Set colour mod (float)");

    if (SDL_SetTextureColorModFloat(texture, colour.r, colour.g,
                                    colour.b) == false)
        throw ApiException("SDL_SetTextureColorModFloat()");

    if (SDL_SetTextureAlphaModFloat(texture, colour.a) == false)
        throw ApiException("SDL_SetTextureAlphaModFloat()");
}

//! @brief Gets the alpha modulation applied when drawing.
//! @return The alpha modulation value, where 255 leaves the texture's own
//! alpha unchanged.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureAlphaMod() fails.
uint8_t Texture::getAlphaMod() const
{
    auto texture = verifyAccess("Get alpha mod");
    uint8_t alpha = 0;

    if (SDL_GetTextureAlphaMod(texture, &alpha) == false)
        throw ApiException("SDL_GetTextureAlphaMod()");

    return alpha;
}

//! @brief Sets the alpha modulation applied when drawing.
//! @param[in] alpha The alpha value multiplied into draw operations, where
//! 255 leaves the texture's own alpha unchanged.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureAlphaMod() fails, which also covers
//! renderers that do not support alpha modulation.
//! @details Source alpha is scaled by @p alpha divided by 255 as the
//! texture is drawn. A blend mode other than SDL_BLENDMODE_NONE must be set
//! for this to be visible.
void Texture::setAlphaMod(uint8_t alpha)
{
    auto texture = verifyAccess("Set alpha mod");

    if (SDL_SetTextureAlphaMod(texture, alpha) == false)
        throw ApiException("SDL_SetTextureAlphaMod()");
}

//! @brief Gets the alpha modulation as a normalised float value.
//! @return The alpha modulation, where 1.0f leaves the texture's own alpha
//! unchanged.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureAlphaModFloat() fails.
float Texture::getAlphaModFloat() const
{
    auto texture = verifyAccess("Get alpha mod (float)");
    float alpha = 0.0f;

    if (SDL_GetTextureAlphaModFloat(texture, &alpha) == false)
        throw ApiException("SDL_GetTextureAlphaModFloat()");

    return alpha;
}

//! @brief Sets the alpha modulation using a normalised float value.
//! @param[in] alpha The alpha value multiplied into draw operations, where
//! 1.0f leaves the texture's own alpha unchanged.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureAlphaModFloat() fails.
//! @details A blend mode other than SDL_BLENDMODE_NONE must be set for this
//! to be visible.
void Texture::setAlphaModFloat(float alpha)
{
    auto texture = verifyAccess("Set alpha mod (float)");

    if (SDL_SetTextureAlphaModFloat(texture, alpha) == false)
        throw ApiException("SDL_SetTextureAlphaModFloat()");
}

//! @brief Gets the blend mode used when drawing the texture.
//! @return The current SDL_BlendMode.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureBlendMode() fails.
SDL_BlendMode Texture::getBlendMode() const
{
    auto texture = verifyAccess("Get blend mode");
    SDL_BlendMode mode = SDL_BLENDMODE_NONE;

    if (SDL_GetTextureBlendMode(texture, &mode) == false)
        throw ApiException("SDL_GetTextureBlendMode()");

    return mode;
}

//! @brief Sets the blend mode used when drawing the texture.
//! @param[in] mode The SDL_BlendMode to blend with.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureBlendMode() fails, which is how a
//! mode the renderer cannot support is reported.
//! @details SDL_BLENDMODE_NONE ignores alpha entirely; the alpha and colour
//! modulation set on the texture only take visible effect under a blending
//! mode such as SDL_BLENDMODE_BLEND.
void Texture::setBlendMode(SDL_BlendMode mode)
{
    auto texture = verifyAccess("Set blend mode");

    if (SDL_SetTextureBlendMode(texture, mode) == false)
        throw ApiException("SDL_SetTextureBlendMode()");
}

//! @brief Gets the scale filter used when drawing the texture.
//! @return SDL_SCALEMODE_NEAREST or SDL_SCALEMODE_LINEAR.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_GetTextureScaleMode() fails.
SDL_ScaleMode Texture::getScaleMode() const
{
    auto texture = verifyAccess("Get scale mode");
    SDL_ScaleMode mode = SDL_SCALEMODE_LINEAR;

    if (SDL_GetTextureScaleMode(texture, &mode) == false)
        throw ApiException("SDL_GetTextureScaleMode()");

    return mode;
}

//! @brief Sets the scale filter used when drawing the texture.
//! @param[in] mode SDL_SCALEMODE_NEAREST for point sampling, which suits
//! pixel art, or SDL_SCALEMODE_LINEAR for smooth interpolation.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_SetTextureScaleMode() fails.
//! @details The filter is applied whenever the texture is drawn at a size
//! other than its own.
void Texture::setScaleMode(SDL_ScaleMode mode)
{
    auto texture = verifyAccess("Set scale mode");

    if (SDL_SetTextureScaleMode(texture, mode) == false)
        throw ApiException("SDL_SetTextureScaleMode()");
}

//! @brief Creates a texture on the given renderer.
//! @param[in] renderer The renderer which will own the texture.
//! @param[in] format The pixel format of the new texture.
//! @param[in] access The access pattern the texture will be used with, one
//! of SDL_TEXTUREACCESS_STATIC, SDL_TEXTUREACCESS_STREAMING or
//! SDL_TEXTUREACCESS_TARGET.
//! @param[in] width The width of the new texture, in pixels.
//! @param[in] height The height of the new texture, in pixels.
//! @throws ObjectNotBoundException If @p renderer is unbound.
//! @throws ApiException If SDL_CreateTexture() fails, such as when the
//! renderer does not support @p format or the size exceeds the maximum
//! reported by SDL_PROP_RENDERER_MAX_TEXTURE_SIZE_NUMBER.
//! @details Any texture previously bound to the object is released first.
//! The new texture is owned, so it is destroyed when the object is, and its
//! contents are undefined until written to.
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

//! @brief Creates a texture on the given renderer.
//! @param[in] renderer The renderer which will own the texture.
//! @param[in] format The pixel format of the new texture.
//! @param[in] access The access pattern the texture will be used with.
//! @param[in] size The width and height of the new texture, in pixels.
//! @throws ObjectNotBoundException If @p renderer is unbound.
//! @throws ApiException If SDL_CreateTexture() fails.
//! @details Any texture previously bound to the object is released first.
//! The new texture is owned, so it is destroyed when the object is, and its
//! contents are undefined until written to.
void Texture::create(const Renderer &renderer, SDL_PixelFormat format,
                     SDL_TextureAccess access, const SDL_Point &size)
{
    auto sdlRenderer = renderer.verifyAccess("Provide renderer for texture");

    release();

    _texture = SDL_CreateTexture(sdlRenderer, format, access, size.x, size.y);
    _parentRenderer = sdlRenderer;
    _owned = true;

    if (_texture == nullptr)
    {
        _parentRenderer = nullptr;
        throw ApiException("SDL_CreateTexture()");
    }
}

//! @brief Creates a texture initialised from an existing surface.
//! @param[in] renderer The renderer which will own the texture.
//! @param[in] surface The surface whose pixels are copied into the texture.
//! @throws ObjectNotBoundException If @p renderer or @p surface is unbound.
//! @throws ApiException If SDL_CreateTextureFromSurface() fails.
//! @details Any texture previously bound to the object is released first.
//! The pixels are copied, so @p surface may be released afterwards. The new
//! texture has SDL_TEXTUREACCESS_STATIC access and its format is chosen by
//! SDL rather than inherited from @p surface.
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
//! @param[in] renderer The renderer which will own the texture.
//! @param[in] props Properties describing the texture to create, such as
//! SDL_PROP_TEXTURE_CREATE_FORMAT_NUMBER,
//! SDL_PROP_TEXTURE_CREATE_ACCESS_NUMBER,
//! SDL_PROP_TEXTURE_CREATE_WIDTH_NUMBER and
//! SDL_PROP_TEXTURE_CREATE_HEIGHT_NUMBER.
//! @throws ObjectNotBoundException If @p renderer is unbound.
//! @throws ApiException If SDL_CreateTextureWithProperties() fails.
//! @details Any texture previously bound to the object is released first.
//! This is the only route to the backend-specific creation properties, such
//! as wrapping an existing platform texture handle.
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

//! @brief Uploads pixel data into a rectangular region of the texture.
//! @param[in] area The region of the texture to overwrite.
//! @param[in] pixels The pixel data to upload.
//! @param[in] pitch The count of bytes per row within @p pixels, including
//! any padding between rows.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateTexture() fails, which includes
//! @p area straying outside the texture.
//! @details @p pixels must already be in the texture's own format, which
//! getFormat() reports. This is a fairly slow path intended for static
//! textures which change rarely; a texture updated often is better created
//! as streaming and written through lock(). It does work on a streaming
//! texture, but for optimisation reasons the pixels may not be readable
//! back through a subsequent lock().
void Texture::update(const SDL_Rect &area, const void *pixels, int pitch)
{
    auto texture = verifyAccess("Update");

    if (SDL_UpdateTexture(texture, &area, pixels, pitch) == false)
        throw ApiException("SDL_UpdateTexture()");
}

//! @brief Uploads pixel data into the entire texture.
//! @param[in] pixels The pixel data to upload.
//! @param[in] pitch The count of bytes per row within @p pixels, including
//! any padding between rows.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateTexture() fails.
//! @details @p pixels must already be in the texture's own format, which
//! getFormat() reports, and must hold at least getHeight() rows. This is a
//! fairly slow path intended for static textures which change rarely; a
//! texture updated often is better created as streaming and written through
//! lock().
void Texture::update(const void *pixels, int pitch)
{
    auto texture = verifyAccess("Update");

    if (SDL_UpdateTexture(texture, nullptr, pixels, pitch) == false)
        throw ApiException("SDL_UpdateTexture(nullptr)");
}

//! @brief Uploads planar YUV pixel data into a rectangular region of the
//! texture.
//! @param[in] area The region of the texture to overwrite.
//! @param[in] yPlane The raw pixels of the Y (luma) plane.
//! @param[in] yPitch The count of bytes per row of the Y plane.
//! @param[in] uPlane The raw pixels of the U (Cb) plane.
//! @param[in] uPitch The count of bytes per row of the U plane.
//! @param[in] vPlane The raw pixels of the V (Cr) plane.
//! @param[in] vPitch The count of bytes per row of the V plane.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateYUVTexture() fails.
//! @details Only for textures in a planar YUV format such as
//! SDL_PIXELFORMAT_IYUV or SDL_PIXELFORMAT_YV12; use update() for packed
//! formats. The chroma planes are typically half the width and height of
//! the luma plane.
void Texture::updateYUV(const SDL_Rect &area,
                        const uint8_t *yPlane, int yPitch,
                        const uint8_t *uPlane, int uPitch,
                        const uint8_t *vPlane, int vPitch)
{
    auto texture = verifyAccess("Update YUV");

    if (SDL_UpdateYUVTexture(texture, &area, yPlane, yPitch, uPlane, uPitch,
                             vPlane, vPitch) == false)
        throw ApiException("SDL_UpdateYUVTexture()");
}

//! @brief Uploads planar YUV pixel data into the entire texture.
//! @param[in] yPlane The raw pixels of the Y (luma) plane.
//! @param[in] yPitch The count of bytes per row of the Y plane.
//! @param[in] uPlane The raw pixels of the U (Cb) plane.
//! @param[in] uPitch The count of bytes per row of the U plane.
//! @param[in] vPlane The raw pixels of the V (Cr) plane.
//! @param[in] vPitch The count of bytes per row of the V plane.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateYUVTexture() fails.
//! @details Only for textures in a planar YUV format such as
//! SDL_PIXELFORMAT_IYUV or SDL_PIXELFORMAT_YV12. The chroma planes are
//! typically half the width and height of the luma plane.
void Texture::updateYUV(const uint8_t *yPlane, int yPitch,
                        const uint8_t *uPlane, int uPitch,
                        const uint8_t *vPlane, int vPitch)
{
    auto texture = verifyAccess("Update YUV");

    if (SDL_UpdateYUVTexture(texture, nullptr, yPlane, yPitch, uPlane, uPitch,
                             vPlane, vPitch) == false)
        throw ApiException("SDL_UpdateYUVTexture(nullptr)");
}

//! @brief Uploads planar NV12 / NV21 pixel data into a rectangular region of
//! the texture.
//! @param[in] area The region of the texture to overwrite.
//! @param[in] yPlane The raw pixels of the Y (luma) plane.
//! @param[in] yPitch The count of bytes per row of the Y plane.
//! @param[in] uvPlane The raw pixels of the interleaved UV chroma plane.
//! @param[in] uvPitch The count of bytes per row of the UV plane.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateNVTexture() fails.
//! @details Only for textures in the SDL_PIXELFORMAT_NV12 or
//! SDL_PIXELFORMAT_NV21 formats, where the two chroma channels share one
//! interleaved plane rather than being separate as in updateYUV().
void Texture::updateNV(const SDL_Rect &area,
                       const uint8_t *yPlane, int yPitch,
                       const uint8_t *uvPlane, int uvPitch)
{
    auto texture = verifyAccess("Update NV");

    if (SDL_UpdateNVTexture(texture, &area, yPlane, yPitch, uvPlane,
                            uvPitch) == false)
        throw ApiException("SDL_UpdateNVTexture()");
}

//! @brief Uploads planar NV12 / NV21 pixel data into the entire texture.
//! @param[in] yPlane The raw pixels of the Y (luma) plane.
//! @param[in] yPitch The count of bytes per row of the Y plane.
//! @param[in] uvPlane The raw pixels of the interleaved UV chroma plane.
//! @param[in] uvPitch The count of bytes per row of the UV plane.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws ApiException If SDL_UpdateNVTexture() fails.
//! @details Only for textures in the SDL_PIXELFORMAT_NV12 or
//! SDL_PIXELFORMAT_NV21 formats, where the two chroma channels share one
//! interleaved plane rather than being separate as in updateYUV().
void Texture::updateNV(const uint8_t *yPlane, int yPitch,
                       const uint8_t *uvPlane, int uvPitch)
{
    auto texture = verifyAccess("Update NV");

    if (SDL_UpdateNVTexture(texture, nullptr, yPlane, yPitch, uvPlane,
                            uvPitch) == false)
        throw ApiException("SDL_UpdateNVTexture(nullptr)");
}

//! @brief Locks a rectangular region of a streaming texture for direct pixel
//! access.
//! @param[in] area The area to lock.
//! @return A LockedTexture describing the locked region.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws OperationException If the texture is not a streaming texture.
//! @throws ApiException If SDL_LockTexture() fails, which includes @p area
//! straying outside the texture.
//! @details The locked memory is write-only, so reading it back gives
//! undefined results. The returned LockedTexture unlocks on destruction,
//! which uploads the written pixels to the GPU.
LockedTexture Texture::lock(const SDL_Rect &area) const
{
    auto texture = verifyAccess("Lock");

    if (getAccess() != SDL_TEXTUREACCESS_STREAMING)
        throw OperationException("Only streaming textures can be locked.");

    void *pixels = nullptr;
    int pitch = 0;

    if (SDL_LockTexture(texture, &area, &pixels, &pitch) == false)
        throw ApiException("SDL_LockTexture()");

    return LockedTexture(texture, pixels, pitch, area.w, area.h,
                         static_cast<SDL_PixelFormat>(texture->format));
}

//! @brief Locks the whole of a streaming texture for direct pixel access.
//! @return A LockedTexture describing the locked texture.
//! @throws ObjectNotBoundException If the texture is not bound.
//! @throws OperationException If the texture is not a streaming texture.
//! @throws ApiException If SDL_LockTexture() fails.
//! @details The locked memory is write-only, so reading it back gives
//! undefined results. The returned LockedTexture unlocks on destruction,
//! which uploads the written pixels to the GPU.
LockedTexture Texture::lock() const
{
    auto texture = verifyAccess("Lock");

    if (getAccess() != SDL_TEXTUREACCESS_STREAMING)
        throw OperationException("Only streaming textures can be locked.");

    void *pixels = nullptr;
    int pitch = 0;

    if (SDL_LockTexture(texture, nullptr, &pixels, &pitch) == false)
        throw ApiException("SDL_LockTexture(nullptr)");

    return LockedTexture(texture, pixels, pitch, texture->w, texture->h,
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
