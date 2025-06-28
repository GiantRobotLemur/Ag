//! @file Sdl3Tools/Primitives.cpp
//! @brief The definition of various C++ classes wrapping SDL-specific
//! structures in order to provide useful services.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Sdl3Tools/Primitives.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Point Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a point with components initialised to 0.
Point::Point()
{
    x = 0;
    y = 0;
}

//! @brief Creates a points with components initialised to a uniform value.
//! @param[in] initX The horizontal component.
//! @param[in] initY The vertical component.
Point::Point(int scalar)
{
    x = y = scalar;
}

//! @brief Creates a points with initialised components.
//! @param[in] initX The horizontal component.
//! @param[in] initY The vertical component.
Point::Point(int initX, int initY)
{
    x = initX;
    y = initY;
}

//! @brief Creates a point from a base structure instance.
//! @param[in] rhs The structure to copy.
Point::Point(const SDL_Point &rhs)
{
    x = rhs.x;
    y = rhs.y;
}

//! @brief Overwrites the components to a uniform value.
//! @param[in] scalar The value to set all components to.
//! @return A reference to the current object.
Point &Point::set(int scalar)
{
    x = y = scalar;

    return *this;
}

//! @brief Overwrites the components with individual values.
//! @param[in] newX The new horizontal offset value.
//! @param[in] newY The new vertical offset value.
//! @return A reference to the current object.
Point &Point::set(int newX, int newY)
{
    x = newX;
    y = newY;

    return *this;
}

//! @brief Gets the object as an array of two integers.
int *Point::toArray()
{
    return &x;
}

//! @brief Gets the object as a read-only array of two integers.
const int *Point::toArray() const
{
    return &x;
}

//! @brief Formats the object as a string.
String Point::toString() const
{
    return String::format(FormatInfo::getNeutral(),
                          "({0}, {1})",
                          { x, y });
}

//! @brief Resets all components to 0.
void Point::clear()
{
    x = y = 0;
}

//! @brief Determines if a point has the same value as this one.
//! @param[in] rhs The point to test against.
//! @retval true @p rhs has the same component values has the current object.
//! @retval false At least one component differs.
bool Point::operator==(const SDL_Point &rhs)
{
    return (x == rhs.x) && (y == rhs.y);
}

//! @brief Determines if a point has a different value as this one.
//! @param[in] rhs The point to test against.
//! @retval true At least one component differs.
//! @retval false @p rhs has the same component values has the current object.
bool Point::operator!=(const SDL_Point &rhs)
{
    return (x != rhs.x) || (y != rhs.y);
}

//! @brief Overwrites the current point with another.
//! @param[in] rhs The value to copy over the current one.
//! @return A reference to the current object.
Point &Point::operator=(const SDL_Point &rhs)
{
    x = rhs.x;
    y = rhs.y;

    return *this;
}

//! @brief Adds the components of another point to this one.
//! @param[in] rhs The point with the components to add.
//! @return A reference to the current point.
Point &Point::operator+=(const SDL_Point &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

//! @brief Subtracts the components of another point from this one.
//! @param[in] rhs The point with the components to subtract.
//! @return A reference to the current point.
Point &Point::operator-=(const SDL_Point &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

//! @brief Multiplies the components of another point with this one.
//! @param[in] rhs The point with the components to multiply.
//! @return A reference to the current point.
Point &Point::operator*=(const SDL_Point &rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

//! @brief Multiplies the components of this point by a scalar.
//! @param[in] scalar The scalar to multiply components by.
//! @return A reference to the current point.
Point &Point::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

//! @brief Divides the components of the current point by those of another.
//! @param[in] rhs The point with the components to divide by.
//! @return A reference to the current point.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
Point &Point::operator/=(const SDL_Point &rhs)
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point vector division by zero.");
    }

    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

//! @brief Divides the components of the current point by a scalar value.
//! @param[in] scalar The scalar to divide by.
//! @return A reference to the current point.
//! @throws DivisionByZeroException If @p scalar is 0.
Point &Point::operator/=(int scalar)
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point scalar division by zero.");
    }

    x /= scalar;
    y /= scalar;

    return *this;
}

//! @brief Takes the modulo of the components of the current point divided by another one.
//! @param[in] rhs The point with the components to multiply.
//! @return A reference to the current point.
Point &Point::operator%=(const SDL_Point &rhs)
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point vector division by zero.");
    }

    x %= rhs.x;
    y %= rhs.y;

    return *this;
}

//! @brief Takes the modulo of the components of this point when divided by a scalar.
//! @param[in] scalar The scalar to divide components by.
//! @return A reference to the current point.
Point &Point::operator%=(int scalar)
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point scalar division by zero.");
    }

    x %= scalar;
    y %= scalar;

    return *this;
}

//! @brief Calculates the negative of the point.
//! @return A point representing the current one negated.
Point Point::operator-() const
{
    return Point(-x, -y);
}

//! @brief Calculates the sum of this and another point.
//! @param[in] rhs The point to add to the current one.
//! @return The sum of the two points.
Point Point::operator+(const SDL_Point &rhs) const
{
    return Point(x + rhs.x, y + rhs.y);
}

//! @brief Calculates the difference between this and another point.
//! @param[in] rhs The point to subtract from the current one.
//! @return The result of the subtraction.
Point Point::operator-(const SDL_Point &rhs) const
{
    return Point(x - rhs.x, y - rhs.y);
}

//! @brief Calculates the product of this and another point.
//! @param[in] rhs The point to multiply by the current one.
//! @return The result of the multiplication.
Point Point::operator*(const SDL_Point &rhs) const
{
    return Point(x * rhs.x, y * rhs.y);
}

//! @brief Calculates the product of the current point and a scalar.
//! @param[in] scalar The scalar value to multiply by.
//! @return The result of the multiplication.
Point Point::operator*(int scalar) const
{
    return Point(x * scalar, y * scalar);
}

//! @brief Calculates the quotient of this and another point.
//! @param[in] rhs The point to divide the current one by.
//! @return The result of the division.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
Point Point::operator/(const SDL_Point &rhs) const
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point vector division by zero.");
    }

    return Point(x / rhs.x, y / rhs.y);
}

//! @brief Calculates the result of the current object divided a scalar.
//! @param[in] scalar The value to divide the components of the current point by.
//! @return The result of the division.
//! @throws DivisionByZeroException If @p scalar is 0.
Point Point::operator/(int scalar) const
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point scalar division by zero.");
    }

    return Point(x / scalar, y / scalar);
}

//! @brief Calculates the quotient of this and another point.
//! @param[in] rhs The point to divide the current one by.
//! @return The remainder of the division.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
Point Point::operator%(const SDL_Point &rhs) const
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point vector division by zero.");
    }

    return Point(x % rhs.x, y % rhs.y);
}

//! @brief Calculates the remainder of the current object divided a scalar.
//! @param[in] scalar The value to divide the components of the current point by.
//! @return The remainder of the division.
//! @throws DivisionByZeroException If @p scalar is 0.
Point Point::operator%(int scalar) const
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_Point scalar division by zero.");
    }

    return Point(x % scalar, y % scalar);
}

////////////////////////////////////////////////////////////////////////////////
// Rect Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a rectangle initialised to an empty state.
Rect::Rect()
{
    x = y = w = h = 0;
}

//! @brief Creates a copy of an SDL rectangle.
//! @param[in] rhs The rectangle to copy.
Rect::Rect(const SDL_Rect &rhs)
{
    x = rhs.x;
    y = rhs.y;
    w = rhs.w;
    h = rhs.h;
}

//! @brief Constructs a rectangle from components.
//! @param initX The horizontal origin offset.
//! @param initY The vertical origin offset.
//! @param initW The horizontal size.
//! @param initH The vertical size.
Rect::Rect(int initX, int initY, int initW, int initH)
{
    x = initX;
    y = initY;
    w = initW;
    h = initH;
}

//! @brief Constructs a rectangle to encompass a set of points.
//! @param[in] points An array of points to encompass.
//! @param[in] count The number of elements in @p points.
Rect::Rect(const SDL_Point *points, int count)
{
    if (SDL_GetRectEnclosingPoints(points, count, nullptr, this) == false)
    {
        x = y = w = h = 0;
    }
}

//! @brief Constructs a rectangle to encompass a clipped set of points.
//! @param[in] points An array of points to encompass.
//! @param[in] count The number of elements in @p points.
//! @param[in] clipBounds A rectangle used to filter the points considered.
Rect::Rect(const SDL_Point *points, int count, const SDL_Rect &clipBounds)
{
    if (SDL_GetRectEnclosingPoints(points, count, &clipBounds, this) == false)
    {
        x = y = w = h = 0;
    }
}

//! @brief Determines of the rectangle has a size which is zero or negative.
//! @retval true The rectangle is in an empty state.
//! @retval false The rectangle is in a non-empty state.
bool Rect::isEmpty() const
{
    return SDL_RectEmpty(this);
}

//! @brief Determines if the rectangle contains a specified point.
//! @param[in] pos The point to test.
//! @retval true The point is inside the rectangle.
//! @retval false The point is outside the rectangle.
bool Rect::contains(const SDL_Point &pos) const
{
    return SDL_PointInRect(&pos, this);
}

//! @brief Calculates the rectangle encompassing the current one and another.
//! @param[in] rhs The rectangle to encompass.
//! @return A rectangle covering the area of the current one and @p rhs.
Rect Rect::makeUnion(const SDL_Rect &rhs) const
{
    Rect shared;

    return SDL_GetRectUnion(this, &rhs, &shared) ? shared : Rect();
}

//! @brief Determines if the current rectangle overlaps with another.
//! @param[in] rhs The rectangle to test for intersection.
//! @retval true The rectangles overlap.
//! @retval false The rectangles are distinct.
bool Rect::hasIntersection(const SDL_Rect &rhs) const
{
    return SDL_HasRectIntersection(this, &rhs);
}

//! @brief Attempts to calculate the rectangular area covered by the current
//! and another rectangle.
//! @param[in] rhs The rectangle to test for intersection.
//! @param[out] common Receives a rectangle defining the common are, if any.
//! @retval true The rectangles overlap, @p common was updated.
//! @retval false The rectangles are distinct.
bool Rect::tryGetOverlap(const SDL_Rect &rhs, SDL_Rect &common) const
{
    return SDL_GetRectIntersection(this, &rhs, &common);
}

//! @brief Attempts to clip a line segment to the bounds of the rectangle.
//! @param[in,out] start The start point of the line segment, updated with the
//! clipped position.
//! @param[in,out] end The end point of the line segment, updated with the
//! clipped position.
//! @retval true The line segment overlapped with the rectangle, @p start and
//! @p end have been updated.
//! @retval false The line segment was wholly outside the rectangle.
bool Rect::clipLineSegment(SDL_Point &start, SDL_Point &end) const
{
    return SDL_GetRectAndLineIntersection(this, &start.x, &start.y, &end.x, &end.y);
}

//! @brief Overwrites this rectangle with another.
//! @param[in] rhs The rectangle to copy over this one.
//! @return A reference to the current object.
Rect &Rect::operator=(const SDL_Rect &rhs)
{
    x = rhs.x;
    y = rhs.y;
    w = rhs.w;
    h = rhs.h;

    return *this;
}

//! @brief Determines if two rectangles are equal, either in values or both
//! are in an empty state.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The rectangles have the same value or are both in an empty state.
//! @retval false One rectangle is in an empty state or their parameters differ.
bool Rect::operator==(const SDL_Rect &rhs) const
{
    return SDL_RectsEqual(this, &rhs);
}

//! @brief Determines if two rectangles are not equal, either in values or both
//! are in an empty state.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true One rectangle is in an empty state or their parameters differ.
//! @retval false The rectangles have the same value or are both in an empty state.
bool Rect::operator!=(const SDL_Rect &rhs) const
{
    return SDL_RectsEqual(this, &rhs) == false;
}

////////////////////////////////////////////////////////////////////////////////
// Colour Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a colour value initialised to opaque black.
Colour::Colour()
{
    r = 0;
    g = 0;
    b = 0;
    a = 255;
}

//! @brief Constructs a colour initialised with individual component values.
//! @param[in] red The red component of the colour.
//! @param[in] green The green component of the colour.
//! @param[in] blue The blue component of the colour.
//! @param[in] alpha The alpha transparency component of the colour.
Colour::Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha /*= 255*/)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

//! @brief Constructs a colour value from an SDL colour value.
//! @param[in] rhs The primitive colour value to convert.
Colour::Colour(const SDL_Color &rhs)
{
    *toPackedArray() = *reinterpret_cast<const uint32_t *>(&rhs);
}

//! @brief Returns the colour value as a packed 32-bit value.
uint32_t Colour::pack()
{
    return *reinterpret_cast<const uint32_t *>(this);
}

//! @brief Returns the colour value as an array of 4 x 8-bit components.
uint8_t *Colour::toArray()
{
    return reinterpret_cast<uint8_t *>(this);
}

//! @brief Returns the colour value as a read-only array of 4 x 8-bit components.
const uint8_t *Colour::toArray() const
{
    return reinterpret_cast<const uint8_t *>(this);
}

//! @brief Returns the colour as a pointer to a packed 32-bit value.
uint32_t *Colour::toPackedArray()
{
    return reinterpret_cast<uint32_t *>(this);
}

//! @brief Returns the colour as a read-only pointer to a packed 32-bit value.
const uint32_t *Colour::toPackedArray() const
{
    return reinterpret_cast<const uint32_t *>(this);
}

//! @brief Formats the value as an HTML hex-style string value.
String Colour::toString() const
{
    utf8_cptr_t format = (a == 255) ? "#{2:X2}{1:X2}{0:X2}" :
                                      "#{3:X2}{2:X2}{1:X2}{0:X2}";

    return String::format(FormatInfo::getNeutral(),
                          format, { r, g, b, a });
}

//! @brief Overwrites the colour with a raw SDL colour value.
//! @param[in] rhs The colour value to overwrite with.
//! @return A reference to the current object.
Colour &Colour::operator=(const SDL_Color &rhs)
{
    *toPackedArray() = *reinterpret_cast<const uint32_t *>(&rhs);

    return *this;
}

//! @brief Determines if a colour has the same value as the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true The components of the two colours are the same.
//! @retval false At least one colour component differs.
bool Colour::operator==(const SDL_Color &rhs)
{
    return *toPackedArray() == *reinterpret_cast<const uint32_t *>(&rhs);
}

//! @brief Determines if a colour has a different value from the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true At least one colour component differs.
//! @retval false The components of the two colours are the same.
bool Colour::operator!=(const SDL_Color &rhs)
{
    return *toPackedArray() != *reinterpret_cast<const uint32_t *>(&rhs);
}

////////////////////////////////////////////////////////////////////////////////
// FPoint Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a point with components initialised to 0.
FPoint::FPoint()
{
    x = 0;
    y = 0;
}

//! @brief Creates a points with components initialised to a uniform value.
//! @param[in] initX The horizontal component.
//! @param[in] initY The vertical component.
FPoint::FPoint(float scalar)
{
    x = y = scalar;
}

//! @brief Creates a points with initialised components.
//! @param[in] initX The horizontal component.
//! @param[in] initY The vertical component.
FPoint::FPoint(float initX, float initY)
{
    x = initX;
    y = initY;
}

//! @brief Creates a point from a base structure instance.
//! @param[in] rhs The structure to copy.
FPoint::FPoint(const SDL_FPoint &rhs)
{
    x = rhs.x;
    y = rhs.y;
}

//! @brief Overwrites the components to a uniform value.
//! @param[in] scalar The value to set all components to.
//! @return A reference to the current object.
FPoint &FPoint::set(float scalar)
{
    x = y = scalar;

    return *this;
}

//! @brief Overwrites the components with individual values.
//! @param[in] newX The new horizontal offset value.
//! @param[in] newY The new vertical offset value.
//! @return A reference to the current object.
FPoint &FPoint::set(float newX, float newY)
{
    x = newX;
    y = newY;

    return *this;
}

//! @brief Gets the object as an array of two integers.
float *FPoint::toArray()
{
    return &x;
}

//! @brief Gets the object as a read-only array of two integers.
const float *FPoint::toArray() const
{
    return &x;
}

//! @brief Formats the object as a string.
String FPoint::toString() const
{
    return String::format(FormatInfo::getNeutral(),
                          "({0}, {1})",
                          { x, y });
}

//! @brief Calculates the length of the vector represented by the
//! point components.
//! @return A scalar representing the vector length.
float FPoint::magnitude() const
{
    if ((x * y) == 0)
        return 0;

    return std::sqrt((x * x) + (y * y));
}

//! @brief Calculates the square of the length of the vector represented
//! by the point components.
//! @return A scalar representing the squared vector length.
float FPoint::magnitudeSquared() const
{
    return (x * x) + (y * y);
}

//! @brief Resets all components to 0.
void FPoint::clear()
{
    x = y = 0;
}

//! @brief Determines if a point has the same value as this one.
//! @param[in] rhs The point to test against.
//! @retval true @p rhs has the same component values has the current object.
//! @retval false At least one component differs.
bool FPoint::operator==(const SDL_FPoint &rhs)
{
    return (x == rhs.x) && (y == rhs.y);
}

//! @brief Determines if a point has a different value as this one.
//! @param[in] rhs The point to test against.
//! @retval true At least one component differs.
//! @retval false @p rhs has the same component values has the current object.
bool FPoint::operator!=(const SDL_FPoint &rhs)
{
    return (x != rhs.x) || (y != rhs.y);
}

//! @brief Overwrites the current point with another.
//! @param[in] rhs The value to copy over the current one.
//! @return A reference to the current object.
FPoint &FPoint::operator=(const SDL_FPoint &rhs)
{
    x = rhs.x;
    y = rhs.y;

    return *this;
}

//! @brief Adds the components of another point to this one.
//! @param[in] rhs The point with the components to add.
//! @return A reference to the current point.
FPoint &FPoint::operator+=(const SDL_FPoint &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

//! @brief Subtracts the components of another point from this one.
//! @param[in] rhs The point with the components to subtract.
//! @return A reference to the current point.
FPoint &FPoint::operator-=(const SDL_FPoint &rhs)
{
    x -= rhs.x;
    y -= rhs.y;

    return *this;
}

//! @brief Multiplies the components of another point with this one.
//! @param[in] rhs The point with the components to multiply.
//! @return A reference to the current point.
FPoint &FPoint::operator*=(const SDL_FPoint &rhs)
{
    x *= rhs.x;
    y *= rhs.y;

    return *this;
}

//! @brief Multiplies the components of this point by a scalar.
//! @param[in] scalar The scalar to multiply components by.
//! @return A reference to the current point.
FPoint &FPoint::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

//! @brief Divides the components of the current point by those of another.
//! @param[in] rhs The point with the components to divide by.
//! @return A reference to the current point.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
FPoint &FPoint::operator/=(const SDL_FPoint &rhs)
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_FPoint vector division by zero.");
    }

    x /= rhs.x;
    y /= rhs.y;

    return *this;
}

//! @brief Divides the components of the current point by a scalar value.
//! @param[in] scalar The scalar to divide by.
//! @return A reference to the current point.
//! @throws DivisionByZeroException If @p scalar is 0.
FPoint &FPoint::operator/=(float scalar)
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_FPoint scalar division by zero.");
    }

    x /= scalar;
    y /= scalar;

    return *this;
}

//! @brief Calculates the negative of the point.
//! @return A point representing the current one negated.
FPoint FPoint::operator-() const
{
    return FPoint(-x, -y);
}

//! @brief Calculates the sum of this and another point.
//! @param[in] rhs The point to add to the current one.
//! @return The sum of the two points.
FPoint FPoint::operator+(const SDL_FPoint &rhs) const
{
    return FPoint(x + rhs.x, y + rhs.y);
}

//! @brief Calculates the difference between this and another point.
//! @param[in] rhs The point to subtract from the current one.
//! @return The result of the subtraction.
FPoint FPoint::operator-(const SDL_FPoint &rhs) const
{
    return FPoint(x - rhs.x, y - rhs.y);
}

//! @brief Calculates the product of this and another point.
//! @param[in] rhs The point to multiply by the current one.
//! @return The result of the multiplication.
FPoint FPoint::operator*(const SDL_FPoint &rhs) const
{
    return FPoint(x * rhs.x, y * rhs.y);
}

//! @brief Calculates the product of the current point and a scalar.
//! @param[in] scalar The scalar value to multiply by.
//! @return The result of the multiplication.
FPoint FPoint::operator*(float scalar) const
{
    return FPoint(x * scalar, y * scalar);
}

//! @brief Calculates the quotient of this and another point.
//! @param[in] rhs The point to divide the current one by.
//! @return The result of the division.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
FPoint FPoint::operator/(const SDL_FPoint &rhs) const
{
    if ((rhs.x * rhs.y) == 0)
    {
        throw Ag::DivisionByZeroException("SDL_FPoint vector division by zero.");
    }

    return FPoint(x / rhs.x, y / rhs.y);
}

//! @brief Calculates the result of the current object divided a scalar.
//! @param[in] scalar The value to divide the components of the current point by.
//! @return The result of the division.
//! @throws DivisionByZeroException If @p scalar is 0.
FPoint FPoint::operator/(float scalar) const
{
    if (scalar == 0)
    {
        throw Ag::DivisionByZeroException("SDL_FPoint scalar division by zero.");
    }

    return FPoint(x / scalar, y / scalar);
}

////////////////////////////////////////////////////////////////////////////////
// FRect Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a rectangle initialised to an empty state.
FRect::FRect()
{
    x = y = w = h = 0;
}

//! @brief Creates a copy of an SDL rectangle.
//! @param[in] rhs The rectangle to copy.
FRect::FRect(const SDL_FRect &rhs)
{
    x = rhs.x;
    y = rhs.y;
    w = rhs.w;
    h = rhs.h;
}

//! @brief Constructs a rectangle from components.
//! @param initX The horizontal origin offset.
//! @param initY The vertical origin offset.
//! @param initW The horizontal size.
//! @param initH The vertical size.
FRect::FRect(float initX, float initY, float initW, float initH)
{
    x = initX;
    y = initY;
    w = initW;
    h = initH;
}

//! @brief Constructs a rectangle to encompass a set of points.
//! @param[in] points An array of points to encompass.
//! @param[in] count The number of elements in @p points.
FRect::FRect(const SDL_FPoint *points, int count)
{
    if (SDL_GetRectEnclosingPointsFloat(points, count, nullptr, this) == false)
    {
        x = y = w = h = 0;
    }
}

//! @brief Constructs a rectangle to encompass a clipped set of points.
//! @param[in] points An array of points to encompass.
//! @param[in] count The number of elements in @p points.
//! @param[in] clipBounds A rectangle used to filter the points considered.
FRect::FRect(const SDL_FPoint *points, int count, const SDL_FRect &clipBounds)
{
    if (SDL_GetRectEnclosingPointsFloat(points, count, &clipBounds, this) == false)
    {
        x = y = w = h = 0;
    }
}

//! @brief Determines of the rectangle has a size which is zero or negative.
//! @retval true The rectangle is in an empty state.
//! @retval false The rectangle is in a non-empty state.
bool FRect::isEmpty() const
{
    return SDL_RectEmptyFloat(this);
}

//! @brief Determines if the rectangle contains a specified point.
//! @param[in] pos The point to test.
//! @retval true The point is inside the rectangle.
//! @retval false The point is outside the rectangle.
bool FRect::contains(const SDL_FPoint &pos) const
{
    return SDL_PointInRectFloat(&pos, this);
}

//! @brief Calculates the rectangle encompassing the current one and another.
//! @param[in] rhs The rectangle to encompass.
//! @return A rectangle covering the area of the current one and @p rhs.
FRect FRect::makeUnion(const SDL_FRect &rhs) const
{
    FRect shared;

    return SDL_GetRectUnionFloat(this, &rhs, &shared) ? shared : FRect();
}

//! @brief Determines if the current rectangle overlaps with another.
//! @param[in] rhs The rectangle to test for intersection.
//! @retval true The rectangles overlap.
//! @retval false The rectangles are distinct.
bool FRect::hasIntersection(const SDL_FRect &rhs) const
{
    return SDL_HasRectIntersectionFloat(this, &rhs);
}

//! @brief Attempts to calculate the rectangular area covered by the current
//! and another rectangle.
//! @param[in] rhs The rectangle to test for intersection.
//! @param[out] common Receives a rectangle defining the common are, if any.
//! @retval true The rectangles overlap, @p common was updated.
//! @retval false The rectangles are distinct.
bool FRect::tryGetOverlap(const SDL_FRect &rhs, SDL_FRect &common) const
{
    return SDL_GetRectIntersectionFloat(this, &rhs, &common);
}

//! @brief Attempts to clip a line segment to the bounds of the rectangle.
//! @param[in,out] start The start point of the line segment, updated with the
//! clipped position.
//! @param[in,out] end The end point of the line segment, updated with the
//! clipped position.
//! @retval true The line segment overlapped with the rectangle, @p start and
//! @p end have been updated.
//! @retval false The line segment was wholly outside the rectangle.
bool FRect::clipLineSegment(SDL_FPoint &start, SDL_FPoint &end) const
{
    return SDL_GetRectAndLineIntersectionFloat(this, &start.x, &start.y, &end.x, &end.y);
}

//! @brief Overwrites this rectangle with another.
//! @param[in] rhs The rectangle to copy over this one.
//! @return A reference to the current object.
FRect &FRect::operator=(const SDL_FRect &rhs)
{
    x = rhs.x;
    y = rhs.y;
    w = rhs.w;
    h = rhs.h;

    return *this;
}

//! @brief Determines if two rectangles are equal, either in values or both
//! are in an empty state.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true The rectangles have the same value or are both in an empty state.
//! @retval false One rectangle is in an empty state or their parameters differ.
bool FRect::operator==(const SDL_FRect &rhs) const
{
    return SDL_RectsEqualFloat(this, &rhs);
}

//! @brief Determines if two rectangles are not equal, either in values or both
//! are in an empty state.
//! @param[in] rhs The rectangle to compare with the current one.
//! @retval true One rectangle is in an empty state or their parameters differ.
//! @retval false The rectangles have the same value or are both in an empty state.
bool FRect::operator!=(const SDL_FRect &rhs) const
{
    return SDL_RectsEqualFloat(this, &rhs) == false;
}

////////////////////////////////////////////////////////////////////////////////
// FColour Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a colour value initialised to opaque black.
FColour::FColour()
{
    r = 0;
    g = 0;
    b = 0;
    a = 1.0f;
}

//! @brief Constructs a colour initialised with individual component values.
//! @param[in] red The red component of the colour.
//! @param[in] green The green component of the colour.
//! @param[in] blue The blue component of the colour.
//! @param[in] alpha The alpha transparency component of the colour.
FColour::FColour(float red, float green, float blue, float alpha /*= 1.0f */)
{
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

//! @brief Constructs a colour value from an SDL colour value.
//! @param[in] rhs The primitive colour value to convert.
FColour::FColour(const SDL_FColor &rhs)
{
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;
}

//! @brief Returns the colour value as an array of 4 components.
float *FColour::toArray()
{
    return reinterpret_cast<float *>(this);
}

//! @brief Returns the colour value as a read-only array of 4 x 8-bit components.
const float *FColour::toArray() const
{
    return reinterpret_cast<const float *>(this);
}

//! @brief Formats the value as a string.
String FColour::toString() const
{
    utf8_cptr_t format = (a == 1.0f) ? "[r={0:F5},g={1:F5},b={2:F5}]" :
                                       "[r={0:F5},g={1:F5},b={2:F5},a={3:F5}]";

    return String::format(FormatInfo::getNeutral(),
                          format, { r, g, b, a });
}

//! @brief Calculates a colour with the minimum component values between the
//! current object and another.
//! @param[in] rhs The second colour.
//! @return A colour with minimum component values.
FColour FColour::min(const SDL_FColor &rhs) const
{
    return FColour(std::min(r, rhs.r),
                   std::min(g, rhs.g),
                   std::min(b, rhs.b),
                   std::min(a, rhs.a));
}

//! @brief Calculates a colour with the maximum component values between the
//! current object and another.
//! @param[in] rhs The second colour.
//! @return A colour with maximum component values.
FColour FColour::max(const SDL_FColor &rhs) const
{
    return FColour(std::max(r, rhs.r),
                   std::max(g, rhs.g),
                   std::max(b, rhs.b),
                   std::max(a, rhs.a));
}

//! @brief Calculates a colour with component values clamped between a specific range.
//! @param[in] minimum The minimum value of any component.
//! @param[in] maximum The maximum value of any component.
//! @return A colour with component values within the specified range.
FColour FColour::clamp(float minimum, float maximum) const
{
    return FColour(std::clamp(minimum, maximum, r),
                   std::clamp(minimum, maximum, g),
                   std::clamp(minimum, maximum, b),
                   std::clamp(minimum, maximum, a));
}

//! @brief Calculates a colour with component values clamped between a specific range.
//! @param[in] minimum The minimum component values.
//! @param[in] maximum The maximum component values.
//! @return A colour with component values within the specified range.
FColour FColour::clamp(const SDL_FColor &minimum, const SDL_FColor &maximum) const
{
    return FColour(std::clamp(minimum.r, maximum.r, r),
                   std::clamp(minimum.g, maximum.g, g),
                   std::clamp(minimum.b, maximum.b, b),
                   std::clamp(minimum.a, maximum.a, a));
}

//! @brief Linearly interpolates a colour value between the current one and another.
//! @param[in] towards The colour value to interpolate towards.
//! @param[in] param The interpolation factor, ideally between 0.0 and 1.0.
//! @return The interpolated colour value.
FColour FColour::lerp(const SDL_FColor &towards, float param) const
{
    float deltaR = towards.r - r;
    float deltaG = towards.g - g;
    float deltaB = towards.b - b;
    float deltaA = towards.a - a;

    return FColour(std::fma(deltaR, param, r),
                   std::fma(deltaG, param, g),
                   std::fma(deltaB, param, b),
                   std::fma(deltaA, param, a));
}

//! @brief Performs a fused multiply/add on the colour value.
//! @param[in] scale The vector components to multiply by.
//! @param[in] translation The fixed scalar value to add.
//! @return The result of the fused multiply add operation.
FColour FColour::fma(const SDL_FColor &scale, float translation) const
{
    return FColour(std::fma(r, scale.r, translation),
                   std::fma(g, scale.g, translation),
                   std::fma(b, scale.b, translation),
                   std::fma(a, scale.a, translation));
}

//! @brief Performs a fused multiply/add on the colour value.
//! @param[in] scale The vector components to multiply by.
//! @param[in] translation The vector components to add.
//! @return The result of the fused multiply add operation
FColour FColour::fma(const SDL_FColor &scale, const SDL_FColor &translation) const
{
    return FColour(std::fma(r, scale.r, translation.r),
                   std::fma(g, scale.g, translation.g),
                   std::fma(b, scale.b, translation.b),
                   std::fma(a, scale.a, translation.a));
}

//! @brief Overwrites the colour with a raw SDL colour value.
//! @param[in] rhs The colour value to overwrite with.
//! @return A reference to the current object.
FColour &FColour::operator=(const SDL_FColor &rhs)
{
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
    a = rhs.a;

    return *this;
}

//! @brief Determines if a colour has the same value as the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true The components of the two colours are the same.
//! @retval false At least one colour component differs.
bool FColour::operator==(const SDL_FColor &rhs)
{
    return (r == rhs.r) && (g == rhs.g) && (b == rhs.b) && (a == rhs.a);
}

//! @brief Determines if a colour has a different value from the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true At least one colour component differs.
//! @retval false The components of the two colours are the same.
bool FColour::operator!=(const SDL_FColor &rhs)
{
    return (r != rhs.r) || (g != rhs.g) || (b != rhs.b) || (a != rhs.a);
}

//! @brief Adds the components of another colour to this one.
//! @param[in] rhs The colour with the components to add.
//! @return A reference to the current colour.
FColour &FColour::operator+=(const SDL_FColor &rhs)
{
    r += rhs.r;
    g += rhs.g;
    b += rhs.b;
    a += rhs.a;

    return *this;
}

//! @brief Subtracts the components of another colour from this one.
//! @param[in] rhs The colour with the components to subtract.
//! @return A reference to the current colour.
FColour &FColour::operator-=(const SDL_FColor &rhs)
{
    r -= rhs.r;
    g -= rhs.g;
    b -= rhs.b;
    a -= rhs.a;

    return *this;
}

//! @brief Multiplies the components of another colour with this one.
//! @param[in] rhs The colour with the components to multiply.
//! @return A reference to the current colour.
FColour &FColour::operator*=(const SDL_FColor &rhs)
{
    r *= rhs.r;
    g *= rhs.g;
    b *= rhs.b;
    a *= rhs.a;

    return *this;
}

//! @brief Multiplies the components of this colour by a scalar.
//! @param[in] scalar The scalar to multiply components by.
//! @return A reference to the current colour.
FColour &FColour::operator*=(float scalar)
{
    r *= scalar;
    g *= scalar;
    b *= scalar;
    a *= scalar;

    return *this;
}

//! @brief Divides the components of the current colour by those of another.
//! @param[in] rhs The colour with the components to divide by.
//! @return A reference to the current colour.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
FColour &FColour::operator/=(const SDL_FColor &rhs)
{
    float product = rhs.r * rhs.g * rhs.b * rhs.a;

    if (product == 0.0f)
    {
        throw DivisionByZeroException("SDL_FColor vector division by zero.");
    }

    r /= rhs.r;
    g /= rhs.g;
    b /= rhs.b;
    a /= rhs.a;

    return *this;
}

//! @brief Divides the components of the current colour by a scalar value.
//! @param[in] scalar The scalar to divide by.
//! @return A reference to the current colour.
//! @throws DivisionByZeroException If @p scalar is 0.
FColour &FColour::operator/=(float scalar)
{
    if (scalar == 0.0f)
    {
        throw DivisionByZeroException("SDL_FColor scalar division by zero.");
    }

    r /= scalar;
    g /= scalar;
    b /= scalar;
    a /= scalar;

    return *this;
}

//! @brief Calculates the negative of the colour.
//! @return A colour representing the current one negated.
FColour FColour::operator-() const
{
    return FColour(-r, -g, -b, -a);
}

//! @brief Calculates the sum of this and another colour.
//! @param[in] rhs The colour to add to the current one.
//! @return The sum of the two points.
FColour FColour::operator+(const SDL_FColor &rhs) const
{
    return FColour(r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a);
}

//! @brief Calculates the difference between this and another colour.
//! @param[in] rhs The colour to subtract from the current one.
//! @return The result of the subtraction.
FColour FColour::operator-(const SDL_FColor &rhs) const
{
    return FColour(r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a);
}

//! @brief Calculates the product of this and another colour.
//! @param[in] rhs The colour to multiply by the current one.
//! @return The result of the multiplication.
FColour FColour::operator*(const SDL_FColor &rhs) const
{
    return FColour(r * rhs.r, g * rhs.g, b * rhs.b, a * rhs.a);
}

//! @brief Calculates the product of the current colour and a scalar.
//! @param[in] scalar The scalar value to multiply by.
//! @return The result of the multiplication.
FColour FColour::operator*(float scalar) const
{
    return FColour(r * scalar, g * scalar, b * scalar, a * scalar);
}

//! @brief Calculates the quotient of this and another colour.
//! @param[in] rhs The colour to divide the current one by.
//! @return The result of the division.
//! @throws DivisionByZeroException If either component of @p rhs is 0.
FColour FColour::operator/(const SDL_FColor &rhs) const
{
    float product = rhs.r * rhs.g * rhs.b * rhs.a;

    if (product == 0.0f)
    {
        throw DivisionByZeroException("SDL_FColor vector division by zero.");
    }

    return FColour(r / rhs.r, g / rhs.g, b / rhs.b, a / rhs.a);
}

//! @brief Calculates the result of the current object divided a scalar.
//! @param[in] scalar The value to divide the components of the current colour by.
//! @return The result of the division.
//! @throws DivisionByZeroException If @p scalar is 0.
FColour FColour::operator/(float scalar) const
{
    if (scalar == 0.0f)
    {
        throw DivisionByZeroException("SDL_FColor scalar division by zero.");
    }

    return FColour(r / scalar, g / scalar, b / scalar, a / scalar);
}

////////////////////////////////////////////////////////////////////////////////
// Vertex Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a vertex with a position.
//! @param[in] pos The position to embed within the vertex.
Vertex::Vertex(const SDL_FPoint &pos) :
    position(pos)
{
}

//! @brief Constructs a vertex with a position and colour.
//! @param[in] pos The position to embed within the vertex.
//! @param[in] colour The colour to embed within the vertex.
Vertex::Vertex(const SDL_FPoint &pos, const SDL_FColor &colour) :
    position(pos),
    color(colour)
{
}

//! @brief Constructs a vertex with a position, colour and texture coordinate.
//! @param[in] pos The position to embed within the vertex.
//! @param[in] colour The colour to embed within the vertex.
//! @param[in] texturePos The texture coordinate to embed within the vertex.
Vertex::Vertex(const SDL_FPoint &pos, const SDL_FColor &colour, const SDL_FPoint &texturePos) :
    position(pos),
    color(colour),
    tex_coord(texturePos)
{
}

//! @brief Constructs a vertex with a position and texture coordinate.
//! @param[in] pos The position to embed within the vertex.
//! @param[in] texturePos The texture coordinate to embed within the vertex.
Vertex::Vertex(const SDL_FPoint &pos, const SDL_FPoint &texturePos) :
    position(pos),
    tex_coord(texturePos)
{
}

//! @brief Constructs a vertex with a position.
//! @param[in] x The horizontal position offset.
//! @param[in] y The vertical position offset.
Vertex::Vertex(float x, float y) :
    position(x, y)
{
}

//! @brief Constructs a vertex with a position and colour.
//! @param[in] x The horizontal position offset.
//! @param[in] y The vertical position offset.
//! @param[in] r The red component of the colour.
//! @param[in] g The green component of the colour.
//! @param[in] b The blue component of the colour.
//! @param[in] a The alpha transparency component of the colour.
Vertex::Vertex(float x, float y, float r, float g, float b, float a /*= 1.0f*/) :
    position(x, y),
    color(r, g, b, a)
{
}

//! @brief Gets a pointer to the vertex as an SDL-compatible SDL_Vertex pointer.
SDL_Vertex *Vertex::toBase()
{
    return reinterpret_cast<SDL_Vertex *>(this);
}

//! @brief Gets a read-only pointer to the vertex as an SDL-compatible
//! SDL_Vertex pointer.
const SDL_Vertex *Vertex::toBase() const
{
    return reinterpret_cast<const SDL_Vertex *>(this);
}

}} // namespace Ag::SDL3
////////////////////////////////////////////////////////////////////////////////

