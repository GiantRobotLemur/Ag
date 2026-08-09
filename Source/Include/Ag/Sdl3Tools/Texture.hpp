//! @file Ag/Sdl3Tools/Texture.hpp
//! @brief The declaration of a wrapper for the SDL3 2D SDL_Texture resource.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code (Opus 5).
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_SDL3_TOOLS_TEXTURE_HPP_
#define HEADER_AG_SDL3_TOOLS_TEXTURE_HPP_

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
//! @brief A wrapper for a locked streaming SDL_Texture that provides random
//! access to its pixel data.
class LockedTexture
{
public:
    // Construction/Destruction
    LockedTexture();
    LockedTexture(SDL_Texture *texture, void *pixels, int pitch,
                  int width, int height, SDL_PixelFormat format);
    LockedTexture(const LockedTexture &) = delete;
    LockedTexture(LockedTexture &&rhs) noexcept;
    ~LockedTexture();

    // Accessors
    bool isLocked() const;
    void *getBits() const;
    void *getRow(int row) const;
    void *getPixel(int column, int row) const;
    void *getPixel(const SDL_Point &at) const;
    int getPitch() const;
    int getWidth() const;
    int getHeight() const;
    SDL_PixelFormat getFormat() const;

    // Operations
    void unlock() noexcept;
    LockedTexture &operator=(const LockedTexture &) = delete;
    LockedTexture &operator=(LockedTexture &&rhs) noexcept;
private:
    // Internal Functions
    SDL_Texture *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_Texture *_texture;
    void *_pixels;
    int _pitch;
    int _width;
    int _height;
    SDL_PixelFormat _format;
};

//! @brief A wrapper for the 2D SDL_Texture resource used with the SDL_Renderer
//! interface. The GPU pipeline's texture is @c Ag::SDL3::GPU::Texture.
class Texture
{
public:
    // Construction/Destruction
    Texture();
    Texture(SDL_Renderer *parentRenderer, SDL_Texture *texture,
            bool owned = true);
    Texture(const Texture &) = delete;
    Texture(Texture &&rhs) noexcept;
    ~Texture();

    // Accessors
    bool isBound() const;
    bool isOwned() const;
    SDL_Texture *get() const;
    SDL_PixelFormat getFormat() const;
    SDL_TextureAccess getAccess() const;
    int getWidth() const;
    int getHeight() const;
    void getSize(float &w, float &h) const;
    SDL_FPoint getSize() const;
    PropertySet getProperties() const;
    Renderer getRenderer() const;

    void getColourMod(uint8_t &r, uint8_t &g, uint8_t &b) const;
    SDL_Color getColourMod() const;
    void setColourMod(uint8_t r, uint8_t g, uint8_t b);
    void setColourMod(const SDL_Color &colour);
    void getColourModFloat(float &r, float &g, float &b) const;
    SDL_FColor getColourModFloat() const;
    void setColourModFloat(float r, float g, float b);
    void setColourModFloat(const SDL_FColor &colour);
    uint8_t getAlphaMod() const;
    void setAlphaMod(uint8_t alpha);
    float getAlphaModFloat() const;
    void setAlphaModFloat(float alpha);
    SDL_BlendMode getBlendMode() const;
    void setBlendMode(SDL_BlendMode mode);
    SDL_ScaleMode getScaleMode() const;
    void setScaleMode(SDL_ScaleMode mode);

    // Operations
    void create(const Renderer &renderer, SDL_PixelFormat format,
                SDL_TextureAccess access, int width, int height);
    void create(const Renderer &renderer, SDL_PixelFormat format,
                SDL_TextureAccess access, const SDL_Point &size);
    void createFromSurface(const Renderer &renderer, const Surface &surface);
    void createWithProperties(const Renderer &renderer, const PropertySet &props);

    void update(const SDL_Rect &area, const void *pixels, int pitch);
    void update(const void *pixels, int pitch);
    void updateYUV(const SDL_Rect &area,
                   const uint8_t *yPlane, int yPitch,
                   const uint8_t *uPlane, int uPitch,
                   const uint8_t *vPlane, int vPitch);
    void updateYUV(const uint8_t *yPlane, int yPitch,
                   const uint8_t *uPlane, int uPitch,
                   const uint8_t *vPlane, int vPitch);
    void updateNV(const SDL_Rect &area,
                  const uint8_t *yPlane, int yPitch,
                  const uint8_t *uvPlane, int uvPitch);
    void updateNV(const uint8_t *yPlane, int yPitch,
                  const uint8_t *uvPlane, int uvPitch);

    LockedTexture lock(const SDL_Rect &area) const;
    LockedTexture lock() const;

    void release() noexcept;
    Texture &operator=(const Texture &) = delete;
    Texture &operator=(Texture &&rhs) noexcept;
    SDL_Texture *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Renderer *_parentRenderer;
    SDL_Texture *_texture;
    bool _owned;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
