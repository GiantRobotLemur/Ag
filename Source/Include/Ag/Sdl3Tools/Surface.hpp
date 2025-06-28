//! @file Ag/Sdl3Tools/Surface.hpp
//! @brief The declaration of a wrapper for an SDL3 system memory image resource,
//! a 'surface'.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_SURFACE_HPP__
#define __AG_SDL3_TOOLS_SURFACE_HPP__

namespace Ag {
namespace SDL3 {

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
    int getWidh() const;
    int getHeight() const;
    int getPitch() const;
    SDL_PixelFormat getFormat() const;
    SDL_SurfaceFlags getFlags() const;

    // Operations
    void unlock();
    LockedSurface &operator=(const LockedSurface &) = delete;
    LockedSurface &operator=(LockedSurface &&rhs) noexcept;
private:
    // Internal Types

    // Internal Functions
    SDL_Surface *verifyAccess(utf8_cptr_t operation) const;

    // Internal Fields
    SDL_Surface *_surface;
};

//! @brief A wrapper for an SDL3 system memory image resource, a 'surface'.
class Surface
{
public:
    // Construction/Destruction
    Surface();
    Surface(const Surface &) = delete;
    Surface(Surface &&rhs) noexcept;
    Surface(SDL_Surface *surface);
    Surface(SDL_Window *window);
    ~Surface();

    // Accessors
    bool isBound() const;
    bool needsLock() const;
    void clear(const SDL_FColor &value) const;

    // Operations
    void release();
    LockedSurface lock() const;
    Surface &operator=(const Surface &) = delete;
    Surface &operator=(Surface &&rhs) noexcept;
    SDL_Surface *verifyAccess(utf8_cptr_t operation) const;
private:
    // Internal Fields
    SDL_Surface *_surface;
    SDL_Window *_associatedWindow;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
