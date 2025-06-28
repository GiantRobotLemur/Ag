//! @file Ag/Win32Base/Tools.hpp
//! @brief The declaration of various utility functions and templates specific
//! to basic Win32 integration.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_WIN32_BASE_TOOLS_HPP__
#define __AG_WIN32_BASE_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <initializer_list>

#include "Ag/Core/Variant.hpp"
#include "Ag/Win32Base/Win32API.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define TRACE Ag::Win32::trace
#else
#define TRACE
#endif

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
namespace Ag {
class Exception;

//! @brief A namespace containing Win32-specific source code elements.
namespace Win32 {
class BaseWindow;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class SizeI;

//! @brief A class derived from the legacy C structure POINT to give it
//! additional functionality.
class PointI : public ::POINT
{
public:
    // Construction/Destruction
    PointI();
    PointI(const POINT &rhs);
    PointI(const POINTS &rhs);
    PointI(int initialX, int initialY);

    // Accessors
    PointI min(const POINT& rhs) const;
    PointI max(const POINT& rhs) const;
    std::pair<PointI, PointI> minmax(const POINT& rhs) const;

    // Operations
    PointI& translateX(int deltaX);
    PointI& translateY(int deltaY);
    PointI& translate(int deltaX, int deltaY);
    PointI operator+(const POINT& rhs) const;
    PointI operator+(const SizeI& rhs) const;
    PointI& operator+=(const POINT& rhs);
    PointI operator-(const POINT& rhs) const;
    PointI& operator-=(const POINT& rhs);
};

//! @brief A class derived from the legacy C structure SIZE to give it
//! additional functionality.
class LegacySize : public ::SIZE
{
public:
    // Construction/Destruction
    LegacySize();
    LegacySize(const SIZE &rhs);
    LegacySize(const POINT &rhs);
    LegacySize(int width, int height);
};

//! @brief A class equivalent to SIZE, but which enforces no minimum component
//! values.
class SizeI
{
public:
    // Construction/Destruction
    SizeI();
    SizeI(const SIZE &rhs);
    SizeI(const POINT &rhs);
    SizeI(int width, int height);

    // Accessors
    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);
    void set(int width, int height);

    double maximizeWidth(int width);
    double maximizeHeight(int height);

    // Operations
    operator SIZE () const;
    SizeI &operator=(const SIZE &rhs);
    SizeI operator+(const SizeI &rhs) const;
private:
    // Internal Fields
    int _width;
    int _height;
};

//! @brief A class derived from RECT to give it additional functionality.
//! @note The orientation of the values in this structure is not defined, i.e.
//! top and bottom could be maxY and minY or vice-versa.
class LegacyRect : public ::RECT
{
public:
    // Construction/Destruction
    LegacyRect();
    LegacyRect(const RECT &original);
    LegacyRect(const POINT &origin, const SIZE &extents, bool isRh = true);
    LegacyRect(int initialLeft, int initialTop,
               int initialRight, int initialBottom);

    // Accessors
    int getWidth() const;
    int getHeight() const;
    POINT getOrigin() const;
    POINT getExtreme() const;
    SIZE getSize() const;

    // Operations
    LegacyRect centre(const SIZE &space) const;
};

//! @brief A class equivalent to RECT, but which is defined in terms of origin
//! and extents with no specific direction.
class RectI
{
public:
    // Construction/Destruction
    RectI() = default;
    RectI(const RECT &rhs);
    RectI(const POINT &origin, const SizeI &extents);
    RectI(const POINT& corner1, const POINT& corner2);
    RectI(int originX, int originY, int width, int height);

    // Accessors
    const PointI &getOrigin() const;
    void setOrigin(int x, int y);
    void setOrigin(const POINT &origin);
    int getOriginX() const;
    void setOriginX(int originX);
    int getOriginY() const;
    void setOriginY(int originY);
    int getExtremeX() const;
    int getExtremeY() const;
    PointI getExtreme() const;

    int getWidth() const;
    void setWidth(int width);
    int getHeight() const;
    void setHeight(int height);

    const SizeI &getSize() const;
    void setSize(const SizeI &extents);
    void setSize(int width, int height);

    void set(const PointI& corner1, const PointI& corner2);

    // Operations
    void translate(const PointI& delta);
    void translate(int deltaX, int deltaY);
    LegacyRect toLegacy(bool isRh = true) const;

    RectI unionRect(const RectI& rhs) const;
    bool overlaps(const RectI& rhs) const;
    bool intersectionRect(const RectI& rhs, RectI& intersection) const;
private:
    // Internal Fields
    PointI _origin;
    SizeI _extents;
};

//! @brief Defines a colour in terms of 8-bit integer channels.
class ColourI
{
public:
    // Construction/Destruction
    ColourI();
    ColourI(COLORREF colourRef);
    ColourI(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);
    ~ColourI() = default;

    // Accessors
    COLORREF toColourRef() const;
    uint8_t getRed() const;
    void setRed(uint8_t red);
    uint8_t getGreen() const;
    void setGreen(uint8_t green);
    uint8_t getBlue() const;
    void setBlue(uint8_t blue);
    uint8_t getAlpha() const;
    void setAlpha(uint8_t alpha);
    void set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF);

    // Operations
private:
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;
    uint8_t _alpha;
};

class SizeD;
class MarginD;

//! @brief A position primitive used by the layout engine.
//! @todo Move this to the geometry module when it exists.
class PointD
{
public:
    // Construction/Destruction
    PointD();
    PointD(double x, double y);
    PointD(const SizeD &size);
    static PointD fromPixels(int x, int y, const PointD &dpiScale);
    static PointD fromPixels(const POINT &pixelPosition, const PointD &dpiScale);

    // Accessors
    double getX() const;
    void setX(double x);
    double deltaX(double delta);
    double getY() const;
    void setY(double y);
    double deltaY(double delta);
    void set(double x, double y);
    PointD &delta(double x, double y);
    PointD min(const PointD &rhs) const;
    PointD max(const PointD &rhs) const;
    std::pair<PointD, PointD> minmax(const PointD &rhs) const;
    POINT toPixelsRound(const PointD &dpiScale) const;
    POINT toPixelsFloor(const PointD &dpiScale) const;
    POINT toPixelsCeil(const PointD &dpiScale) const;
    SIZE toPixelSize(const PointD &dpiScale) const;
    RECT toPixelRect(const PointD &extreme, const PointD &dpiScale) const;

    // Operations
    PointD operator-() const;
    PointD operator+(const PointD &rhs) const;
    PointD &operator+=(const PointD &rhs);
    PointD operator-(const PointD &rhs) const;
    PointD &operator-=(const PointD &rhs);
    PointD operator*(const PointD &rhs) const;
    PointD &operator*=(const PointD &rhs);
    PointD operator/(const PointD &rhs) const;
    PointD &operator/=(const PointD &rhs);
    PointD operator*(double rhs) const;
    PointD &operator*=(double rhs);
    PointD operator/(double rhs) const;
    PointD &operator/=(double rhs);
private:
    // Internal Fields
    double _x;
    double _y;
};

//! @brief Defines the size of a rectangular area using non-negative components.
//! @todo Move this to the geometry module when it exists.
class SizeD
{
public:
    // Construction/Destruction
    SizeD();
    SizeD(double width, double height);
    SizeD(const PointD &delta);

    // Accessors
    double getWidth() const;
    void setWidth(double width);
    double minimiseWidth(double width);
    double maximiseWidth(double width);
    double getHeight() const;
    void setHeight(double height);
    double minimiseHeight(double height);
    double maximiseHeight(double height);
    void set(double width, double height);
    SIZE toPixels(const PointD &dpiScale) const;

    // Operations
    SizeD min(const SizeD &rhs) const;
    SizeD max(const SizeD &rhs) const;
    SizeD operator+(const SizeD &rhs) const;
    SizeD &operator+=(const SizeD &rhs);
    SizeD operator-(const SizeD &rhs) const;
    SizeD expand(const MarginD &margins) const;
    SizeD contract(const MarginD &margins) const;
private:
    // Internal Fields
    double _width;
    double _height;
};

class MarginD;

//! @brief Defines a rectangular area with non-negative size.
//! @todo Move this to the geometry module when it exists.
class RectD
{
public:
    // Construction/Destruction
    RectD() = default;
    RectD(const PointD &origin, const SizeD &extents);
    RectD(const PointD &corner1, const PointD &corner2);
    RectD(double originX, double originY, double width, double height);
    static RectD fromPixels(const RECT &pixelRect, const PointD &dpiScale);

    // Accessors
    const PointD &getOrigin() const;
    PointD getExtreme() const;
    void setOrigin(const PointD &origin);
    double getOriginX() const;
    void setOriginX(double x);
    double getExtremeX() const;
    void setExtremeX(double x);
    double getOriginY() const;
    void setOriginY(double y);
    double getExtremeY() const;
    void setExtremeY(double y);
    double getWidth() const;
    void setWidth(double width);
    double getHeight() const;
    void setHeight(double height);
    const SizeD &getExtents() const;
    void setExtents(const SizeD &extents);

    void set(const PointD &corner1, const PointD &corner2);
    void set(double originX, double originY, double width, double height);
    void setByExtent(double left, double top, double right, double bottom);
    void translateX(double deltaX);
    void translateY(double deltaY);
    void translate(const PointD &delta);

    // Operations
    RECT toPixels(const PointD &dpiScale) const;
    RectD expand(const MarginD &margin) const;
    RectD contract(const MarginD &margin) const;
    RectD unionRect(const RectD &rhs) const;
    bool overlaps(const RectD& rhs) const;
    bool intersectionRect(const RectD &rhs, RectD &intersection) const;
private:
    // Internal Fields
    PointD _origin;
    SizeD _extents;
};

//! @brief Defines a borders along the four edges.
//! @todo Move this to the geometry module when it exists.
class MarginD
{
public:
    // Construction/Destruction
    MarginD();
    MarginD(double all);
    MarginD(double horzontal, double vertical);
    MarginD(double left, double top, double right, double bottom);

    // Accessors
    double getLeft() const;
    void setLeft(double left);
    double getTop() const;
    void setTop(double top);
    double getRight() const;
    void setRight(double right);
    double getBottom() const;
    void setBottom(double bottom);
    double getWidthDelta() const;
    double getHeightDelta() const;
    PointD getTopLeftDelta() const;
    PointD getBottomRightDelta() const;
    PointD getBottomRightOffset() const;
    SizeD getSize() const;
    void set(double globalValue);
    void set(double horizontalPaddding, double verticalPadding);
    void set(double left, double top, double right, double bottom);

    // Operations
    MarginD operator+(const MarginD &rhs) const;
    MarginD &operator+=(const MarginD &rhs);
private:
    // Internal Fields
    double _left;
    double _top;
    double _right;
    double _bottom;
};

//! @brief A class which provides tolls for converting between device units
//! and resolution independent display units (96th of an inch).
class PixelScaler
{
public:
    // Public Constants
    static const PointD UnitsPerInch;

    // Construction/Destruction
    PixelScaler(HWND handle);
    PixelScaler(const BaseWindow &window);
    PixelScaler(double dotsPerInch);
    PixelScaler(double horizontalDotsPerInch, double verticalDotsPerInch);
    PixelScaler(const PointD &scale);
    ~PixelScaler() = default;

    // Accessors
    double fromHorizontalPixels(int pixels) const;
    double fromVerticalPixels(int pixels) const;
    PointD fromPixels(const POINT &position) const;
    SizeD fromPixels(const SIZE &dimensions) const;
    SizeD fromPixels(const SizeI &dimensions) const;
    RectD fromPixels(const RECT &rect) const;
    RectD fromPixels(const RectI &rect) const;
    MarginD fromPixels(const RECT &outer, const RECT &inner) const;

    int toHorizontalPixels(double horizontalSize) const;
    int toVerticalPixels(double verticalSize) const;
    POINT toPixels(const PointD &position) const;
    SIZE toPixels(const SizeD &size) const;
    RECT toPixels(const RectD &rect) const;
    RECT toPixels(const RECT &outer, const MarginD &margin) const;
private:
    // Internal Fields
    PointD _scale;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
bool isValidAddress(const void *addr);
bool isValidAddress(uintptr_t addr);
LPWSTR makeResourceText(uint32_t resourceId);
void reportError(const Ag::Exception &error, const BaseWindow *parent = nullptr);
void trace(const char *text);
void trace(const char *formatSpec, const std::initializer_list<Ag::Variant> &values);

}} // namespace Ag::Win32

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
