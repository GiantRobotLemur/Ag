//! @file Win32Base/Tools.cpp
//! @brief The definition of various utility functions and templates specific
//! to basic Win32 integration.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <string_view>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Format.hpp"
#include "Ag/Core/Utf.hpp"
#include "Ag/Win32Base/BaseWindow.hpp"
#include "Ag/Win32Base/Win32API.hpp"
#include "Ag/Win32Base/Tools.hpp"

namespace Ag {
namespace Win32 {

////////////////////////////////////////////////////////////////////////////////
// PointI Members Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a point with components initialised to 0.
PointI::PointI()
{
    x = y = 0;
}

//! @brief Constructs a point initialised from a legacy POINT structure.
//! @param[in] rhs The point to initialise from.
PointI::PointI(const POINT &rhs)
{
    x = rhs.x;
    y = rhs.y;
}

//! @brief Constructs a point initialised from a legacy 16-bit POINT.
//! @param[in] rhs The point to initialise from.
PointI::PointI(const POINTS &rhs)
{
    x = rhs.x;
    y = rhs.y;
}

//! @brief Constructs a point by specifying its components.
//! @param[in] initialX The initial X component value.
//! @param[in] initialY The initial Y component value.
PointI::PointI(int initialX, int initialY)
{
    x = initialX;
    y = initialY;
}

//! @brief Creates a point with minimum components between the current
//! and another.
//! @param[in] rhs The point providing a second set of components.
//! @returns A point composed of the minimum horizontal and vertical
//! components between this and rhs.
PointI PointI::min(const POINT& rhs) const
{
    return PointI(std::min(x, rhs.x),
                  std::min(y, rhs.y));
}

//! @brief Creates a point with maximum components between the current
//! and another.
//! @param[in] rhs The point providing a second set of components.
//! @returns A point composed of the maximum horizontal and vertical
//! components between this and rhs.
PointI PointI::max(const POINT& rhs) const
{
    return PointI(std::max(x, rhs.x),
                  std::max(y, rhs.y));
}

//! @brief Creates a pair of points representing the minimum and maximum
//! components between the current point and another.
//! @param[in] rhs The point providing a second set of components.
//! @returns A pair of points, minimum and maximum.
std::pair<PointI, PointI> PointI::minmax(const POINT& rhs) const
{
    const auto horz = std::minmax(x, rhs.x);
    const auto vert = std::minmax(y, rhs.y);

    return std::pair<PointI, PointI>({ horz.first, vert.first },
                                     { horz.second, vert.second });
}


//! @brief Translates the point horizontally.
//! @param[in] deltaX The value to add to the horizontal component.
//! @returns A reference to the current object.
PointI& PointI::translateX(int deltaX) { x += deltaX; return *this; }

//! @brief Translates the point vertically.
//! @param[in] deltaY The value to add to the vertical component.
//! @returns A reference to the current object.
PointI& PointI::translateY(int deltaY) { y += deltaY; return *this; }

//! @brief Translates the point by component.
//! @param[in] deltaX The value to add to the horizontal component.
//! @param[in] deltaY The value to add to the vertical component.
//! @returns A reference to the current object.
PointI& PointI::translate(int deltaX, int deltaY)
{
    x += deltaX;
    y += deltaY;

    return *this;
}

//! @brief Adds the components of the current point to that of another.
//! @param[in] rhs The point to add.
//! @return The sum of the two points.
PointI PointI::operator+(const POINT& rhs) const
{
    return PointI(x + rhs.x, y + rhs.y);
}

//! @brief Adds the components of a size to the current point.
//! @param[in] rhs The size with horizontal and vertical components to add.
//! @returns The sum of the current point and rhs.
PointI PointI::operator+(const SizeI& rhs) const
{
    return PointI(x + rhs.getWidth(), y + rhs.getHeight());
}

//! @brief Accumulates the components of the current and another point.
//! @param[in] rhs The point containing the components to add.
//! @returns A reference to the current object.
PointI& PointI::operator+=(const POINT& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

//! @brief Subtracts the components of another point from those of the current one.
//! @param[in] rhs The point to subtract.
//! @return The difference between the two points.
PointI PointI::operator-(const POINT& rhs) const
{
    return PointI(x - rhs.x, y - rhs.y);
}

//! @brief Subtracts the components of another point from this one.
//! @param[in] rhs The point containing the components to subtract.
//! @returns A reference to the current object.
PointI& PointI::operator-=(const POINT& rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// LegacySize Members Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a size value with components initialised to zero.
LegacySize::LegacySize()
{
    cx = cy = 0;
}

//! @brief Creates a size value from a legacy SIZE structure.
//! @param[in] rhs The legacy structure to initialise from.
LegacySize::LegacySize(const SIZE &rhs)
{
    cx = rhs.cx;
    cy = rhs.cy;
}

//! @brief Creates a size value from a legacy POINT structure, ensuring the
//! resultant components are non-negative.
//! @param[in] rhs The position to create from.
LegacySize::LegacySize(const POINT &rhs)
{
    cx = std::max(rhs.x, 0l);
    cy = std::max(rhs.y, 0l);
}

//! @brief Creates a size value from individual components.
//! @param[in] width The initial width, should be non-negative.
//! @param[in] height The initial height, should be non-negative.
LegacySize::LegacySize(int width, int height)
{
    cx = width;
    cy = height;
}

////////////////////////////////////////////////////////////////////////////////
// SizeI Members Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a size value with components set to 0.
SizeI::SizeI() :
    _width(0),
    _height(0)
{
}

//! @brief Constructs a size value from a legacy size value. Components will
//! be silently truncated to be non-negative.
//! @param[in] rhs The size value providing component values.
SizeI::SizeI(const SIZE &rhs) :
    _width(std::max(rhs.cx, 0l)),
    _height(std::max(rhs.cy, 0l))
{
}

//! @brief Constructs a size value from a legacy POINT value. Components will
//! be silently truncated to be non-negative.
//! @param[in] rhs The position value providing component values.
SizeI::SizeI(const POINT &rhs) :
    _width(std::max(rhs.x, 0l)),
    _height(std::max(rhs.y, 0l))
{
}

//! @brief Constructs a size value from individual components.
//! @param[in] width The initial width.
//! @param[in] height The initial height.
//! @throws Ag::ArgumentException if either component is negative.
SizeI::SizeI(int width, int height) :
    _width(std::max(width, 0)),
    _height(std::max(height, 0))
{
    if (width < 0)
    {
        throw Ag::ArgumentException("width");
    }
    else if (height < 0)
    {
        throw Ag::ArgumentException("height");
    }
}

//! @brief Gets the current horizontal component.
int SizeI::getWidth() const { return _width; }

//! @brief Sets the new horizontal component.
//! @param[in] width The new component value.
//! @throws Ag::ArgumentException If width is negative.
void SizeI::setWidth(int width)
{
    if (width < 0)
    {
        throw ArgumentException("width");
    }

    _width = width;
}

//! @brief Gets the current vertical component.
int SizeI::getHeight() const { return _height; }

//! @brief Sets the new vertical component.
//! @param[in] width The new component value.
//! @throws Ag::ArgumentException If height is negative.
void SizeI::setHeight(int height)
{
    if (height < 0)
    {
        throw ArgumentException("height");
    }

    _height = height;
}

//! @brief Overwrites the width and height components.
//! @param[in] width The new width value.
//! @param[in] height The new height value.
//! @throws Ag::ArgumentException If either component is negative.
void SizeI::set(int width, int height)
{
    if (width < 0)
    {
        throw Ag::ArgumentException("width");
    }

    if (height < 0)
    {
        throw Ag::ArgumentException("height");
    }

    _width = width;
    _height = height;
}

//! @brief Increases the width to a required value if necessary.
//! @param[in] width The minimum required width.
//! @return The new width.
double SizeI::maximizeWidth(int width)
{
    _width = std::max(_width, std::max(width, 0));

    return _width;
}

//! @brief Increases the height to a required value if necessary.
//! @param[in] height The minimum required height.
//! @return The new height.
double SizeI::maximizeHeight(int height)
{
    _height = std::max(_height, std::max(height, 0));

    return _height;
}

//! @brief Casts the object to a legacy SIZE structure.
SizeI::operator SIZE () const
{
    return { _width, _height };
}

//! @brief Overwrites the value from a legacy SIZE structure. Components will
//! be silently truncated to be non-negative.
//! @param[in] rhs The size value providing component values.
//! @return A reference to the current object.
SizeI &SizeI::operator=(const SIZE &rhs)
{
    _width = std::max(rhs.cx, 0l);
    _height = std::max(rhs.cy, 0l);

    return *this;
}

//! @brief Accumulates the size value.
//! @param[in] rhs The size value to add.
//! @return The sum of the two size values.
SizeI SizeI::operator+(const SizeI &rhs) const
{
    return SizeI(_width + rhs._width,
                 _height + rhs._height);
}

////////////////////////////////////////////////////////////////////////////////
// LegacyRect Members Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs a legacy rectangle structure with the components set to zero.
LegacyRect::LegacyRect()
{
    left = top = right = bottom = 0;
}

//! @brief Creates a copy of a legacy rectangle.
//! @param[in] original A basic rectangle.
LegacyRect::LegacyRect(const RECT &original) :
    RECT(original)
{
}

//! @brief Creates a legacy rectangle from an origin position and a size.
//! @param[in] origin The position of the top/bottom left.
//! @param[in] extents The width and height of the rectangle.
//! @param[in] isRh Determines if the rectangle is in the right-handed coordinate
//! system, i.e. screen coordinates where top has a lower value than bottom,
//! false for bottom has a lower value from top.
LegacyRect::LegacyRect(const POINT &origin, const SIZE &extents,
                       bool isRh /*= true*/)
{
    auto horzExtents = std::minmax(origin.x, origin.x + extents.cx);
    auto vertExtents = std::minmax(origin.y, origin.y + extents.cy);

    left = horzExtents.first;
    right = horzExtents.second;

    if (isRh)
    {
        top = vertExtents.first;
        bottom = vertExtents.second;
    }
    else
    {
        bottom = vertExtents.first;
        top = vertExtents.second;
    }
}

//! @brief Constructs a legacy rectangle from individual components.
//! @param[in] initialLeft The initial value of the left component.
//! @param[in] initialTop The initial value of the top component.
//! @param[in] initialRight The initial value of the right component.
//! @param[in] initialBottom The initial value of the bottom component.
LegacyRect::LegacyRect(int initialLeft, int initialTop,
                       int initialRight, int initialBottom)
{
    left = initialLeft;
    top = initialTop;
    right = initialRight;
    bottom = initialBottom;
}

//! @brief Calculates the non-negative width of the rectangle.
int LegacyRect::getWidth() const
{
    auto range = std::minmax(left, right);

    return range.second - range.first;
}

//! @brief Calculates the non-negative height of the rectangle.
int LegacyRect::getHeight() const
{
    auto range = std::minmax(top, bottom);

    return range.second - range.first;
}

//! @brief Calculates the position of minimum X/Y.
POINT LegacyRect::getOrigin() const
{
    return { std::min(left, right), std::min(top, bottom) };
}

//! @brief Calculates the position of the maximum X/Y.
POINT LegacyRect::getExtreme() const
{
    return { std::max(left, right), std::max(top, bottom) };
}

//! @brief Calculates the non-negative size of the rectangle.
SIZE LegacyRect::getSize() const
{
    auto horzRange = std::minmax(left, right);
    auto vertRange = std::minmax(top, bottom);

    return { horzRange.second - horzRange.first,
             vertRange.second - vertRange.first };
}

//! @brief Calculates a rectangle centred on the current one with a given size.
//! @param[in] space The size of the rectangle to centre.
//! @return A rectangle centred on the current one and of the specified size.
LegacyRect LegacyRect::centre(const SIZE &space) const
{
    int centreX = (left + right) / 2;
    int centreY = (top + bottom) / 2;

    int originX = centreX - (space.cx / 2);
    int originY = centreY - (space.cy / 2);

    return LegacyRect(originX, originY,
                      originX + space.cx,
                      originY + space.cy);
}

////////////////////////////////////////////////////////////////////////////////
// RectI Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a rectangle from a legacy RECT structure.
//! @param[in] rhs The legacy structure to extract the rectangle parameters from.
RectI::RectI(const RECT &rhs)
{
    auto horz = std::minmax(rhs.left, rhs.right);
    auto vert = std::minmax(rhs.top, rhs.bottom);

    _origin.x = horz.first;
    _origin.y = vert.first;
    _extents.set(horz.second - horz.first,
                 vert.second - vert.first);
}

//! @brief Constructs a rectangle from its origin and size.
//! @param[in] origin The point within the rectangle with the lowest horizontal
//! and vertical offset.
//! @param[in] extents The width and height of the rectangle.
RectI::RectI(const POINT &origin, const SizeI &extents)
{
    _origin = origin;
    _extents = extents;
}

//! @brief Constructs the rectangle using two extreme points.
//! @param[in] corner1 One extreme corner of the new rectangle.
//! @param[in] corner2 Another extreme corner of the new rectangle.
RectI::RectI(const POINT& corner1, const POINT& corner2)
{
    set(corner1, corner2);
}

//! @brief Constructs the rectangle from individual parameters.
//! @param[in] originX The lowest horizontal position within the rectangle.
//! @param[in] originY The lowest vertical position within the rectangle.
//! @param[in] width The non-negative width of the rectangle.
//! @param[in] height The non-negative height of the rectangle.
RectI::RectI(int originX, int originY, int width, int height) :
    _origin(originX, originY),
    _extents(width, height)
{
}

//! @brief Gets the origin of the rectangle.
const PointI &RectI::getOrigin() const { return _origin; }

//! @brief Sets the origin of the rectangle by component.
//! @param[in] x The horizontal origin of the rectangle.
//! @param[in] y The vertical origin of the rectangle.
void RectI::setOrigin(int x, int y)
{
    _origin.x = x;
    _origin.y = y;
}

//! @brief Sets the origin of the rectangle.
//! @param[in] origin The position of the corner with the lowest horizontal
//! and vertical offsets.
void RectI::setOrigin(const POINT &origin) { _origin = origin; }

int RectI::getOriginX() const { return _origin.x; }
void RectI::setOriginX(int originX) { _origin.x = originX; }
int RectI::getOriginY() const { return _origin.y; }
void RectI::setOriginY(int originY) { _origin.y = originY; }
int RectI::getExtremeX() const { return _origin.x + _extents.getWidth(); }
int RectI::getExtremeY() const { return _origin.y + _extents.getHeight(); }
PointI RectI::getExtreme() const { return _origin + _extents; }

int RectI::getWidth() const { return _extents.getWidth(); }
void RectI::setWidth(int width) { _extents.setWidth(width); }
int RectI::getHeight() const { return _extents.getHeight(); }
void RectI::setHeight(int height) { _extents.setHeight(height); }

const SizeI &RectI::getSize() const { return _extents; }
void RectI::setSize(const SizeI &extents) { _extents = extents; }
void RectI::setSize(int width, int height) { _extents.set(width, height); }

//! @brief Redefines the rectangle using two extreme points.
//! @param[in] corner1 One extreme corner of the new rectangle.
//! @param[in] corner2 Another extreme corner of the new rectangle.
void RectI::set(const PointI& corner1, const PointI& corner2)
{
    const auto rangePair = corner1.minmax(corner2);

    _origin = rangePair.first;
    const PointI extents = rangePair.second - rangePair.first;

    _extents.set(extents.x, extents.y);
}

//! @brief Translates the rectangle by the components of a point.
//! @param[in] delta The translation component values.
void RectI::translate(const PointI& delta)
{
    _origin += delta;
}

//! @brief Translates the rectangle by individual components.
//! @param[in] deltaX The horizontal offset to translate by.
//! @param[in] deltaY The vertical offset to translate by.
void RectI::translate(int deltaX, int deltaY)
{
    _origin.translate(deltaX, deltaY);
}

//! @brief Converts the rectangle to a legacy rectangle bounds.
//! @param isRh True if top should have a lower value than bottom, false if
//! bottom should have a lower value than top.
LegacyRect RectI::toLegacy(bool isRh /*= true*/) const
{
    return isRh ? LegacyRect(_origin.x, _origin.y,
                             _origin.x + _extents.getWidth(),
                             _origin.y + _extents.getHeight()) :
        LegacyRect(_origin.x, _origin.y + _extents.getHeight(),
                   _origin.x + _extents.getWidth(),
                   _origin.y);
}

//! @brief Calculates the smallest rectangle which will encompass the current
//! rectangle and another.
//! @param[in] rhs The rectangle to union with.
//! @return A rectangle containing both this and rhs.
RectI RectI::unionRect(const RectI& rhs) const
{
    const PointI origin = _origin.min(rhs._origin);
    const PointI extreme = getExtreme().max(rhs.getExtreme());

    return RectI(origin, extreme - origin);
}

//! @brief Determines if the current rectangle overlaps with another.
//! @param[in] rhs The rectangle to check for intersection.
//! @retval true The rectangles overlap.
//! @retval false The rectangles don't overlap, but may butt up against
//! each other.
bool RectI::overlaps(const RectI& rhs) const
{
    const PointI lhsExtreme = getExtreme();
    const PointI rhsExtreme = rhs.getExtreme();

    if ((lhsExtreme.x < rhs._origin.x) ||
        (rhsExtreme.x < _origin.x) ||
        (lhsExtreme.y < rhs._origin.y) ||
        (rhsExtreme.y < _origin.y))
    {
        return false;
    }

    return true;
}

//! @brief Attempts to calculate the area shared between the current rectangle
//! and another.
//! @param[in] rhs The rectangle to test for intersection.
//! @param[out] intersection Receives the intersection if the rectangles overlap.
//! @retval true The rectangles overlap, intersection is updated with where.
//! @retval false The rectangles do not overlap.
bool RectI::intersectionRect(const RectI& rhs, RectI& intersection) const
{
    const PointI lhsExtreme = getExtreme();
    const PointI rhsExtreme = rhs.getExtreme();

    if ((lhsExtreme.x < rhs._origin.x) ||
        (rhsExtreme.x < _origin.x) ||
        (lhsExtreme.y < rhs._origin.y) ||
        (rhsExtreme.y < _origin.y))
    {
        return false;
    }
    else
    {
        PointI interOrigin = _origin.max(rhs._origin);
        PointI interExtreme = lhsExtreme.min(rhsExtreme);

        intersection.set(interOrigin, interExtreme);

        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////
// ColourI Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a default colour value of opaque black.
ColourI::ColourI() :
    _red(0),
    _green(0),
    _blue(0),
    _alpha(0xFF)
{
}

//! @brief Creates a colour definition from a legacy COLORREF value.
//! @param[in] colourRef The raw colour value.
ColourI::ColourI(COLORREF colourRef) :
    _red(GetRValue(colourRef)),
    _green(GetGValue(colourRef)),
    _blue(GetBValue(colourRef)),
    _alpha(0xFF)
{
}

//! @brief Creates a colour definition from channel components.
//! @param[in] red The red colour component (0-255).
//! @param[in] green The green colour component (0-255).
//! @param[in] blue The blue colour component (0-255).
//! @param[in] alpha The alpha transparency component (0-255).
ColourI::ColourI(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha /*= 0xFF*/) :
    _red(red),
    _green(green),
    _blue(blue),
    _alpha(alpha)
{
}

//! @brief Converts the colour definition to a legacy opaque COLORREF value. 
COLORREF ColourI::toColourRef() const
{
    return RGB(_red, _green, _blue);
}

uint8_t ColourI::getRed() const { return _red; }
void ColourI::setRed(uint8_t red) { _red = red; }
uint8_t ColourI::getGreen() const { return _green; }
void ColourI::setGreen(uint8_t green) { _green = green; }
uint8_t ColourI::getBlue() const { return _blue; }
void ColourI::setBlue(uint8_t blue) { _blue = blue; }
uint8_t ColourI::getAlpha() const { return _alpha; }
void ColourI::setAlpha(uint8_t alpha) { _alpha = alpha; }

//! @brief Overwrites the components of the colour object.
//! @param[in] red The red colour component (0-255).
//! @param[in] green The green colour component (0-255).
//! @param[in] blue The blue colour component (0-255).
//! @param[in] alpha The alpha transparency component (0-255).
void ColourI::set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha /*= 0xFF*/)
{
    _red = red;
    _green = green;
    _blue = blue;
    _alpha = alpha;
}

////////////////////////////////////////////////////////////////////////////////
// PointD Member Definitions
////////////////////////////////////////////////////////////////////////////////
PointD::PointD() :
    _x(0),
    _y(0)
{
}

PointD::PointD(double x, double y) :
    _x(x),
    _y(y)
{
}

PointD::PointD(const SizeD &size) :
    _x(size.getWidth()),
    _y(size.getHeight())
{
}

PointD PointD::fromPixels(int x, int y, const PointD &dpiScale)
{
    return PointD(x * 96.0 / dpiScale._x,
                  y * 96.0 / dpiScale._y);
}

PointD PointD::fromPixels(const POINT &pixelPosition, const PointD &dpiScale)
{
    return PointD(pixelPosition.x * 96.0 / dpiScale._x,
                  pixelPosition.y * 96.0 / dpiScale._y);
}

double PointD::getX() const { return _x; }
void PointD::setX(double x) { _x = x; }
double PointD::deltaX(double delta) { _x += delta; return _x; }
double PointD::getY() const { return _y; }
void PointD::setY(double y) { _y = y; }
double PointD::deltaY(double delta) { _y += delta; return _y; }

PointD &PointD::delta(double deltaX, double deltaY)
{
    _x += deltaX;
    _y += deltaY;

    return *this;
}

void PointD::set(double x, double y)
{
    _x = x;
    _y = y;
}

PointD PointD::min(const PointD &rhs) const
{
    return PointD(std::min(_x, rhs._x),
                  std::min(_y, rhs._y));
}

PointD PointD::max(const PointD &rhs) const
{
    return PointD(std::max(_x, rhs._x),
                  std::max(_y, rhs._y));
}

std::pair<PointD, PointD> PointD::minmax(const PointD &rhs) const
{
    auto horizontal = std::minmax(_x, rhs._x);
    auto vertical = std::minmax(_y, rhs._y);

    return std::make_pair<PointD, PointD>(PointD(horizontal.first, vertical.first),
                                          PointD(horizontal.second, vertical.second));
}

POINT PointD::toPixelsRound(const PointD &dpiScale) const
{
    return PointI(static_cast<int>(std::rint(_x * dpiScale._x / 96.0)),
                  static_cast<int>(std::rint(_y * dpiScale._y / 96.0)));
}

POINT PointD::toPixelsFloor(const PointD &dpiScale) const
{
    return PointI(static_cast<int>(std::floor(_x * dpiScale._x / 96.0)),
                  static_cast<int>(std::floor(_y * dpiScale._y / 96.0)));
}

POINT PointD::toPixelsCeil(const PointD &dpiScale) const
{
    return PointI(static_cast<int>(std::ceil(_x * dpiScale._x / 96.0)),
                  static_cast<int>(std::ceil(_y * dpiScale._y / 96.0)));
}

SIZE PointD::toPixelSize(const PointD &dpiScale) const
{
    return LegacySize(static_cast<int>(std::max(std::ceil(_x * dpiScale._x / 96.0), 0.0)),
                      static_cast<int>(std::max(std::ceil(_y * dpiScale._y / 96.0), 0.0)));
}

RECT PointD::toPixelRect(const PointD &extreme, const PointD &dpiScale) const
{
    auto minAndMax = minmax(extreme);

    return LegacyRect(static_cast<int>(std::floor(minAndMax.first._x * dpiScale._x / 96.0)),
                      static_cast<int>(std::floor(minAndMax.first._y * dpiScale._y / 96.0)),
                      static_cast<int>(std::ceil(minAndMax.second._x * dpiScale._x / 96.0)),
                      static_cast<int>(std::ceil(minAndMax.second._y * dpiScale._y / 96.0)));
}

PointD PointD::operator-() const
{
    return PointD(-_x, -_y);
}

PointD PointD::operator+(const PointD &rhs) const
{
    return PointD(_x + rhs._x, _y + rhs._y);
}

PointD &PointD::operator+=(const PointD &rhs)
{
    _x += rhs._x;
    _y += rhs._y;

    return *this;
}

PointD PointD::operator-(const PointD &rhs) const
{
    return PointD(_x - rhs._x, _y - rhs._y);
}

PointD &PointD::operator-=(const PointD &rhs)
{
    _x -= rhs._x;
    _y -= rhs._y;

    return *this;
}

PointD PointD::operator*(const PointD &rhs) const
{
    return PointD(_x * rhs._x, _y * rhs._y);
}

PointD &PointD::operator*=(const PointD &rhs)
{
    _x *= rhs._x;
    _y *= rhs._y;

    return *this;
}

PointD PointD::operator/(const PointD &rhs) const
{
    return PointD(_x / rhs._x, _y / rhs._y);
}

PointD &PointD::operator/=(const PointD &rhs)
{
    _x /= rhs._x;
    _y /= rhs._y;

    return *this;
}

PointD PointD::operator*(double rhs) const
{
    return PointD(_x * rhs, _y * rhs);
}

PointD &PointD::operator*=(double rhs)
{
    _x *= rhs;
    _y *= rhs;

    return *this;
}

PointD PointD::operator/(double rhs) const
{
    return PointD(_x / rhs, _y / rhs);
}

PointD &PointD::operator/=(double rhs)
{
    _x /= rhs;
    _y /= rhs;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// SizeD Member Definitions
////////////////////////////////////////////////////////////////////////////////
SizeD::SizeD() :
    _width(0),
    _height(0)
{
}

SizeD::SizeD(double width, double height) :
    _width(width),
    _height(height)
{
    if (_width < 0)
    {
        throw ArgumentException("width");
    }

    if (_height < 0)
    {
        throw ArgumentException("height");
    }
}

SizeD::SizeD(const PointD &delta) :
    _width(delta.getX()),
    _height(delta.getY())
{
    if ((_width < 0) || (_height < 0))
    {
        throw ArgumentException("delta");
    }
}
double SizeD::getWidth() const { return _width; }

void SizeD::setWidth(double width)
{
    if (width < 0)
    {
        throw ArgumentException("width");
    }

    _width = width;
}

double SizeD::minimiseWidth(double width)
{
    return _width = std::min(_width, width);
}

double SizeD::maximiseWidth(double width)
{
    return _width = std::max(_width, width);
}

double SizeD::getHeight() const { return _height; }

void SizeD::setHeight(double height)
{
    if (height < 0)
    {
        throw ArgumentException("height");
    }

    _height = height;
}

double SizeD::minimiseHeight(double height)
{
    return _height = std::min(_height, height);
}

double SizeD::maximiseHeight(double height)
{
    return _height = std::max(_height, height);
}

void SizeD::set(double width, double height)
{
    if (width < 0)
    {
        throw ArgumentException("width");
    }

    if (height < 0)
    {
        throw ArgumentException("height");
    }

    _width = width;
    _height = height;
}

SIZE SizeD::toPixels(const PointD &dpiScale) const
{
    return LegacySize(static_cast<int>(std::max(std::ceil(_width * dpiScale.getX() / 96.0), 0.0)),
                      static_cast<int>(std::max(std::ceil(_height * dpiScale.getY() / 96.0), 0.0)));
}

SizeD SizeD::min(const SizeD &rhs) const
{
    return SizeD(std::min(_width, rhs._width),
                 std::min(_height, rhs._height));
}

SizeD SizeD::max(const SizeD &rhs) const
{
    return SizeD(std::max(_width, rhs._width),
                 std::max(_height, rhs._height));
}

SizeD SizeD::operator+(const SizeD &rhs) const
{
    return SizeD(_width + rhs._width, _height + rhs._height);
}

SizeD &SizeD::operator+=(const SizeD &rhs)
{
    _width += rhs._width;
    _height += rhs._height;

    return *this;
}

//! @brief Subtracts one size from another, truncating the results if they become negative.
//! @param[in] rhs The size to subtract from the current value.
//! @return A new size value with non-negative components.
SizeD SizeD::operator-(const SizeD &rhs) const
{
    return SizeD(std::max(_width - rhs._width, 0.0),
                 std::max(_height - rhs._height, 0.0));
}

SizeD SizeD::expand(const MarginD &margins) const
{
    return SizeD(std::max(_width + margins.getWidthDelta(), 0.0),
                 std::max(_height + margins.getHeightDelta(), 0.0));
}

SizeD SizeD::contract(const MarginD &margins) const
{
    return SizeD(std::max(_width - margins.getWidthDelta(), 0.0),
                 std::max(_height - margins.getHeightDelta(), 0.0));
}

////////////////////////////////////////////////////////////////////////////////
// RectD Member Definitions
////////////////////////////////////////////////////////////////////////////////
RectD::RectD(const PointD &origin, const SizeD &extents) :
    _origin(origin),
    _extents(extents)
{
}

RectD::RectD(const PointD &corner1, const PointD &corner2) :
    _origin(corner1.min(corner2)),
    _extents(corner1.max(corner2) - _origin)
{
}

RectD::RectD(double originX, double originY, double width, double height) :
    _origin(originX, originY),
    _extents(width, height)
{
}

RectD RectD::fromPixels(const RECT &pixelRect, const PointD &dpiScale)
{
    auto horz = std::minmax(pixelRect.left, pixelRect.right);
    auto vert = std::minmax(pixelRect.top, pixelRect.bottom);

    return RectD(horz.first * 96.0 / dpiScale.getX(),
                 vert.first * 96.0 / dpiScale.getY(),
                 horz.second * 96.0 / dpiScale.getX(),
                 vert.second * 96.0 / dpiScale.getY());
}

const PointD &RectD::getOrigin() const { return _origin; }
void RectD::setOrigin(const PointD &origin) { _origin = origin; }

PointD RectD::getExtreme() const
{
    return PointD(_origin.getX() + _extents.getWidth(),
                  _origin.getY() + _extents.getHeight());
}

double RectD::getOriginX() const { return _origin.getX(); }
void RectD::setOriginX(double x) { _origin.setX(x); }

double RectD::getExtremeX() const { return _origin.getX() + _extents.getWidth(); }
void RectD::setExtremeX(double x)
{
    _origin.setX(x - _extents.getWidth());
}

double RectD::getOriginY() const { return _origin.getY(); }
void RectD::setOriginY(double y) { _origin.setY(y); }
double RectD::getExtremeY() const { return _origin.getY() + _extents.getHeight(); }
void RectD::setExtremeY(double y)
{
    _origin.setY(y - _extents.getHeight());
}

double RectD::getWidth() const { return _extents.getWidth(); }
void RectD::setWidth(double width) { _extents.setWidth(width); }
double RectD::getHeight() const { return _extents.getHeight(); }
void RectD::setHeight(double height) { _extents.setHeight(height); }

const SizeD &RectD::getExtents() const { return _extents; }
void RectD::setExtents(const SizeD &extents) { _extents = extents; }


void RectD::set(const PointD &corner1, const PointD &corner2)
{
    _origin = corner1.min(corner2);
    _extents = corner2.max(corner2) - _origin;
}

void RectD::set(double originX, double originY, double width, double height)
{
    _extents.set(width, height);
    _origin.set(originX, originY);
}

void RectD::setByExtent(double left, double top, double right, double bottom)
{
    auto horizontal = std::minmax(left, right);
    auto vertical = std::minmax(top, bottom);

    _origin.set(horizontal.first, vertical.first);
    _extents.set(horizontal.second - horizontal.first,
                 vertical.second - vertical.first);
}

void RectD::translateX(double deltaX) { _origin.deltaX(deltaX); }
void RectD::translateY(double deltaY) { _origin.deltaY(deltaY); }
void RectD::translate(const PointD &delta) { _origin += delta; }

RECT RectD::toPixels(const PointD &dpiScale) const
{
    PointD originPixels = _origin * dpiScale / 96.0;
    PointD extremePixels = getExtreme() * dpiScale / 96.0;

    return LegacyRect(static_cast<int>(std::floor(originPixels.getX())),
                      static_cast<int>(std::floor(originPixels.getY())),
                      static_cast<int>(std::ceil(extremePixels.getX())),
                      static_cast<int>(std::ceil(extremePixels.getY())));
}

RectD RectD::expand(const MarginD &margin) const
{
    return RectD(_origin.getX() - margin.getLeft(),
                 _origin.getY() - margin.getTop(),
                 _extents.getWidth() + margin.getWidthDelta(),
                 _extents.getHeight() + margin.getHeightDelta());

}

RectD RectD::contract(const MarginD &margin) const
{
    return RectD(_origin.getX() + margin.getLeft(),
                 _origin.getY() + margin.getTop(),
                 std::max(_extents.getWidth() - margin.getWidthDelta(), 0.0),
                 std::max(_extents.getHeight() - margin.getHeightDelta(), 0.0));
}

//! @brief Calculates the smallest rectangle which will encompass the current
//! rectangle and another.
//! @param[in] rhs The rectangle to union with.
//! @return A rectangle containing both this and rhs.
RectD RectD::unionRect(const RectD &rhs) const
{
    PointD origin = _origin.min(rhs._origin);
    PointD extreme = getExtreme().max(rhs.getExtreme());

    return RectD(origin, extreme - origin);
}

//! @brief Determines if the current rectangle overlaps with another.
//! @param[in] rhs The rectangle to check for intersection.
//! @retval true The rectangles overlap.
//! @retval false The rectangles don't overlap, but may butt up against
//! each other.
bool RectD::overlaps(const RectD& rhs) const
{
    const PointD lhsExtreme = getExtreme();
    const PointD rhsExtreme = rhs.getExtreme();

    if ((lhsExtreme.getX() < rhs._origin.getX()) ||
        (rhsExtreme.getX() < _origin.getX()) ||
        (lhsExtreme.getY() < rhs._origin.getY()) ||
        (rhsExtreme.getY() < _origin.getY()))
    {
        return false;
    }

    return true;
}

//! @brief Attempts to calculate the area shared between the current rectangle
//! and another.
//! @param[in] rhs The rectangle to test for intersection.
//! @param[out] intersection Receives the intersection if the rectangles overlap.
//! @retval true The rectangles overlap, intersection is updated with where.
//! @retval false The rectangles do not overlap.
bool RectD::intersectionRect(const RectD &rhs, RectD &intersection) const
{
    PointD lhsExtreme = getExtreme();
    PointD rhsExtreme = rhs.getExtreme();

    if ((lhsExtreme.getX() < rhs._origin.getX()) ||
        (rhsExtreme.getX() < _origin.getX()) ||
        (lhsExtreme.getY() < rhs._origin.getY()) ||
        (rhsExtreme.getY() < _origin.getY()))
    {
        return false;
    }
    else
    {
        PointD interOrigin = _origin.max(rhs._origin);
        PointD interExtreme = lhsExtreme.min(rhsExtreme);

        intersection.set(interOrigin, interExtreme);

        return true;
    }
}

////////////////////////////////////////////////////////////////////////////////
// MarginD Member Definitions
////////////////////////////////////////////////////////////////////////////////
MarginD::MarginD() :
    _left(0),
    _top(0),
    _right(0),
    _bottom(0)
{
}

MarginD::MarginD(double all) :
    _left(all),
    _top(all),
    _right(all),
    _bottom(all)
{
}

MarginD::MarginD(double horzontal, double vertical) :
    _left(horzontal),
    _top(vertical),
    _right(horzontal),
    _bottom(vertical)
{
}

MarginD::MarginD(double left, double top, double right, double bottom) :
    _left(left),
    _top(top),
    _right(right),
    _bottom(bottom)
{
}

double MarginD::getLeft() const { return _left; }
void MarginD::setLeft(double left) { _left = left; }
double MarginD::getTop() const { return _top; }
void MarginD::setTop(double top) { _top = top; }
double MarginD::getRight() const { return _right; }
void MarginD::setRight(double right) { _right = right; }
double MarginD::getBottom() const { return _bottom; }
void MarginD::setBottom(double bottom) { _bottom = bottom; }
double MarginD::getWidthDelta() const { return _left + _right; }
double MarginD::getHeightDelta() const { return _top + _bottom; }

PointD MarginD::getTopLeftDelta() const { return PointD(_left, _top); }
PointD MarginD::getBottomRightDelta() const { return PointD(-_right, -_bottom); }
PointD MarginD::getBottomRightOffset() const { return PointD(_right, _bottom); }
SizeD MarginD::getSize() const { return SizeD(_left + _right, _top + _bottom); }

void MarginD::set(double globalValue)
{
    _left = _top = _right = _bottom = globalValue;
}

void MarginD::set(double horizontalPaddding, double verticalPadding)
{
    _left = _right = horizontalPaddding;
    _top = _bottom = verticalPadding;
}

void MarginD::set(double left, double top, double right, double bottom)
{
    _left = left;
    _top = top;
    _right = right;
    _bottom = bottom;
}

MarginD MarginD::operator+(const MarginD &rhs) const
{
    return MarginD(_left + rhs._left,
                   _top + rhs._top,
                   _right + rhs._right,
                   _bottom + rhs._bottom);
}

MarginD &MarginD::operator+=(const MarginD &rhs)
{
    _left += rhs._left;
    _top += rhs._top;
    _right += rhs._right;
    _bottom += rhs._bottom;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// PixelScaler Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
const PointD PixelScaler::UnitsPerInch(96.0, 96.0);

//! @brief Constructs a scaler from a window.
//! @param[in] handle The handle of the window to extract the DPI scale from.
PixelScaler::PixelScaler(HWND handle) :
    _scale(96.0, 96.0)
{
    if (::IsWindow(handle))
    {
        double dpiScale = ::GetDpiForWindow(handle);
        _scale.set(dpiScale, dpiScale);
    }
}

//! @brief Constructs a scaler from a window.
//! @param[in] window The window to extract the DPI scale from.
PixelScaler::PixelScaler(const BaseWindow& window) :
    _scale(96.0, 96.0)
{
    if (window.isBound())
    {
        double dpiScale = window.getDpi();
        _scale.set(dpiScale, dpiScale);
    }
}

//! @brief Constructs a scaler from a uniform scale factor.
//! @param[in] dotsPerInch The horizontal and verical count of device units per inch.
PixelScaler::PixelScaler(double dotsPerInch) :
    _scale(std::max(dotsPerInch, 1.0), std::max(dotsPerInch, 1.0))
{
}

//! @brief Constructs a scaler from independent scale factors.
//! @param[in] horizontalDotsPerInch The horizontal count of device units per inch.
//! @param[in] verticalDotsPerInch The vertical count of device units per inch.
PixelScaler::PixelScaler(double horizontalDotsPerInch, double verticalDotsPerInch) :
    _scale(std::max(horizontalDotsPerInch, 1.0), std::max(verticalDotsPerInch, 1.0))
{
}

//! @brief Constructs a scaler from independent scale factors.
//! @param[in] scale A vector of scale factors.
PixelScaler::PixelScaler(const PointD& scale) :
    _scale(scale)
{
}

//! @brief Calculates a horizontal in display units from pixels.
//! @param[in] pixels The width in pixels.
//! @return The width in display units.
double PixelScaler::fromHorizontalPixels(int pixels) const
{
    return static_cast<double>(pixels) * UnitsPerInch.getX() / _scale.getX();
}

//! @brief Calculates a vertical in display units from pixels.
//! @param[in] pixels The height in pixels.
//! @return The height in display units.
double PixelScaler::fromVerticalPixels(int pixels) const
{
    return static_cast<double>(pixels) * UnitsPerInch.getY() / _scale.getY();
}

//! @brief Calculates a position in display units from pixels.
//! @param[in] position The position in pixels.
//! @return The position in display units.
PointD PixelScaler::fromPixels(const POINT &position) const
{
    PointD pixels(position.x, position.y);

    return pixels * UnitsPerInch / _scale;
}

//! @brief Calculates a size in display units from pixels.
//! @param[in] dimensions The size in pixels.
//! @return The size in display units.
SizeD PixelScaler::fromPixels(const SIZE &dimensions) const
{
    PointD pixels(dimensions.cx, dimensions.cy);

    return pixels * UnitsPerInch / _scale;
}

//! @brief Calculates a size in display units from pixels.
//! @param[in] dimensions The size in pixels.
//! @return The size in display units.
SizeD PixelScaler::fromPixels(const SizeI &dimensions) const
{
    PointD pixels(dimensions.getWidth(), dimensions.getHeight());

    return pixels * UnitsPerInch / _scale;
}

//! @brief Calculates a rectangle in display units from pixels.
//! @param[in] rect The rectangle in pixels.
//! @return The rectangle in display units.
RectD PixelScaler::fromPixels(const RECT &rect) const
{
    PointD topLeft(rect.left, rect.top);
    PointD bottomRight(rect.right, rect.bottom);

    return RectD(topLeft * UnitsPerInch / _scale,
                 bottomRight * UnitsPerInch / _scale);
}

//! @brief Calculates a rectangle in display units from pixels.
//! @param[in] rect The rectangle in pixels.
//! @return The rectangle in display units.
RectD PixelScaler::fromPixels(const RectI &rect) const
{
    PointD topLeft(rect.getOriginX(), rect.getOriginY());
    PointD bottomRight(rect.getExtremeX(), rect.getExtremeY());

    return RectD(topLeft * UnitsPerInch / _scale,
                 bottomRight * UnitsPerInch / _scale);
}

//! @brief Calculates the size of a display margin from two rectangles defined
//! in pixels.
//! @param[in] outer The position of the outer rectangle.
//! @param[in] inner The position of the inner rectangle.
//! @return The calculated margin expressed in display units.
MarginD PixelScaler::fromPixels(const RECT &outer, const RECT &inner) const
{
    PointD topLeft(inner.left - outer.left, inner.top - outer.top);
    PointD bottomRight(outer.right - inner.right, outer.bottom - inner.bottom);

    PointD transformedTl = topLeft * UnitsPerInch / _scale;
    PointD transformedBr = bottomRight * UnitsPerInch / _scale;

    return MarginD(topLeft.getX(), topLeft.getY(), bottomRight.getX(), bottomRight.getY());
}

//! @brief Calculates a horizontal offset in pixels from a value in display units.
//! @param[in] horizontalSize The horizontal offset to scale.
//! @return The offset as pixels.
int PixelScaler::toHorizontalPixels(double horizontalSize) const
{
    return static_cast<int>(std::rint(horizontalSize * _scale.getX() / UnitsPerInch.getX()));
}

//! @brief Calculates a vertical offset in pixels from a value in display units.
//! @param[in] verticalSize The vertical offset to scale.
//! @return The offset as pixels.
int PixelScaler::toVerticalPixels(double verticalSize) const
{
    return static_cast<int>(std::rint(verticalSize * _scale.getY() / UnitsPerInch.getY()));
}

//! @brief Calculates a position in pixels from a value in display units.
//! @param[in] position The position to scale.
//! @return The position as pixels.
POINT PixelScaler::toPixels(const PointD &position) const
{
    PointD pixels = position * _scale / UnitsPerInch;

    return { static_cast<int>(std::rint(pixels.getX())), static_cast<int>(std::rint(pixels.getY())) };
}

//! @brief Calculates a size in pixels from a value in display units.
//! @param[in] size The size to scale.
//! @return The size as pixels.
SIZE PixelScaler::toPixels(const SizeD &size) const
{
    return size.toPixels(_scale);
}

//! @brief Calculates a rectangle in pixels from a value in display units.
//! @param[in] rect The rectangle to scale.
//! @return The rectangle as pixels.
RECT PixelScaler::toPixels(const RectD &rect) const
{
    return rect.getOrigin().toPixelRect(rect.getExtreme(), _scale);
}

//! @brief Calculates a rectangle in pixels from an outer rectangle in pixels
//! and a margin specified in display units.
//! @param[in] outer The pixel rectangle to reduce by the margin.
//! @param[in] margin The margin in display units to reduce @p outer by.
//! @return The final rectangle in pixels.
RECT PixelScaler::toPixels(const RECT &outer, const MarginD &margin) const
{
    PointD topLeft = margin.getTopLeftDelta();
    PointD bottomRight = margin.getBottomRightOffset();

    POINT pixelTopLeft = topLeft.toPixelsFloor(_scale);
    POINT pixelBottomRight = bottomRight.toPixelsCeil(_scale);

    return { outer.left + pixelTopLeft.x, outer.top + pixelTopLeft.y,
             outer.right - pixelBottomRight.x, outer.bottom - pixelBottomRight.y };
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if an address if within the bounds of the address space
//! of a Win32 process.
//! @param[in] addr The address to test.
//! @retval true The address is within the valid address range, but may still
//! point to memory which isn't mapped.
//! @retval false The address is definitely invalid.
bool isValidAddress(const void *addr)
{
    return isValidAddress(reinterpret_cast<uintptr_t>(addr));
}

//! @brief Determines if an address if within the bounds of the address space
//! of a Win32 process.
//! @param[in] addr The address to test expressed as a machine word.
//! @retval true The address is within the valid address range, but may still
//! point to memory which isn't mapped.
//! @retval false The address is definitely invalid.#
bool isValidAddress(uintptr_t addr)
{
    static uintptr_t minAddr = 0;
    static uintptr_t maxAddr = 0;

    if (maxAddr == 0)
    {
        SYSTEM_INFO sysInfo;

        ::GetSystemInfo(&sysInfo);
        minAddr = reinterpret_cast<uintptr_t>(sysInfo.lpMinimumApplicationAddress);
        maxAddr = reinterpret_cast<uintptr_t>(sysInfo.lpMaximumApplicationAddress);
    }

    return (addr >= minAddr) && (addr <= maxAddr);
}

//! @brief Converts a numeric resource identifier into a wide text pointer.
//! @param[in] resourceId The numeric identifier to convert.
//! @return The value as a wide string pointer.
LPWSTR makeResourceText(uint32_t resourceId)
{
    LPWSTR resourceName = nullptr;

    if (resourceId <= 0xFFFF)
    {
        resourceName = reinterpret_cast<LPWSTR>(static_cast<uintptr_t>(resourceId));
    }
    else
    {
        // Resource identifier must be lower than 64K to be valid and
        // distinguishable from addresses.
        throw ArgumentException("resourceId");
    }

    return resourceName;
}

//! @brief Displays a message box summarising an exception.
//! @param[in] error The exception to display.
//! @param[in] parent The window which should own the message box dialog.
void reportError(const Ag::Exception &error,
                 const BaseWindow *parent /* = nullptr */)
{
    std::wstring text;
    Ag::Utf::appendToWide(text, error.getMessage().data(),
                          error.getMessage().length());
    text.append(L":\n\n");
    Ag::Utf::appendToWide(text, error.getDetail().data(),
                          error.getDetail().length());

    HWND hOwner = ::GetDesktopWindow();

    if ((parent != nullptr) && parent->isBound())
    {
        hOwner = parent->getHandle();
    }

    ::MessageBoxW(hOwner, text.c_str(), L"Error", MB_OK | MB_ICONASTERISK);
}

//! @brief Outputs verbatim text to the debugger.
//! @param[in] text The text to output in UTF-8 encoding.
void trace(const char *text)
{
    if ((text != nullptr) && (*text != '\0'))
    {
        std::wstring wideBuffer;
        Utf::appendToWide(wideBuffer, text, std::strlen(text));

        ::OutputDebugStringW(wideBuffer.c_str());
    }
}

//! @brief Outputs formatted text to the debugger.
//! @param[in] formatSpec The specification of the output text to format.
//! @param[in] values The values to render into the string.
void trace(const char *formatSpec, const std::initializer_list<Ag::Variant> &values)
{
    if ((formatSpec != nullptr) && (*formatSpec != '\0'))
    {
        std::string buffer;

        Ag::appendFormat(formatSpec, buffer, values);

        std::wstring wideBuffer;
        Utf::appendToWide(wideBuffer, buffer.c_str(), buffer.length(), buffer.length());

        ::OutputDebugStringW(wideBuffer.c_str());
    }
}

}} // namespace Ag::Win32
////////////////////////////////////////////////////////////////////////////////

