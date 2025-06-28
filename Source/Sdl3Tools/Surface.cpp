//! @file Sdl3Tools/Surface.cpp
//! @brief The definition of
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
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
int LockedSurface::getWidh() const
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

//! @brief Unlocks the surface if one is bound and leaves the object in an
//! unbound state.
void LockedSurface::unlock()
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
    _associatedWindow(nullptr)
{
}

//! @brief Acquires a surface resource from another wrapper.
//! @param[in] rhs The wrapper to acquire the resource from.
Surface::Surface(Surface &&rhs) noexcept :
    _surface(std::exchange(rhs._surface, nullptr)),
    _associatedWindow(std::exchange(rhs._associatedWindow, nullptr))
{
}

//! @brief Constructs a wrapper for a surface resource.
//! @param[in] surface The surface resource to wrap, possibly nullptr.
Surface::Surface(SDL_Surface *surface) :
    _surface(surface),
    _associatedWindow(nullptr)
{
}

//! @brief Creates a wrapper for the surface associated with a window.
//! @param[in] window A pointer to the SDL window to obtain a surface for.
Surface::Surface(SDL_Window *window) :
    _surface(nullptr),
    _associatedWindow(nullptr)
{
    if ((window != nullptr) && (_surface == nullptr))
        throw ApiException("SDL_GetWindowSurface()");
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

//! @brief Releases any wrapped surface resource.
void Surface::release()
{
    auto surface = std::exchange(_surface, nullptr);
    auto window = std::exchange(_associatedWindow, nullptr);

    if (surface != nullptr)
    {
        if (window == nullptr)
        {
            SDL_DestroySurface(surface);
        }
        else if (SDL_DestroyWindowSurface(window) == false)
        {
            ApiException("SDL_DestroyWindowSurface()");
        }
    }
}

//! @brief Locks the surface so that pixels can be randomly accessed.
//! @return An object wrapping the locked surface.
LockedSurface Surface::lock() const
{
    auto surface = verifyAccess("Lock surface");

    if (SDL_MUSTLOCK(surface) && ((surface->flags & SDL_SURFACE_LOCKED) != 0))
        throw OperationException("Surface already locked.");

    if (SDL_LockSurface(surface) == false)
        ApiException("SDL_LockSurface()");

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

