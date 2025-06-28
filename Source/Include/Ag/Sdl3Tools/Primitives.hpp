//! @file Ag/Sdl3Tools/Primitives.hpp
//! @brief The declaration of various C++ classes wrapping SDL-specific
//! structures in order to provide useful services.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SDL3_TOOLS_PRIMITIVES_HPP__
#define __AG_SDL3_TOOLS_PRIMITIVES_HPP__

namespace Ag {
namespace SDL3 {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A C++ wrapper for the SDL_Point structure.
struct Point : public SDL_Point
{
public:
    // Construction/Destruction
    Point();
    Point(int scalar);
    Point(int initX, int initY);
    Point(const SDL_Point &rhs);

    // Accessors
    Point &set(int scalar);
    Point &set(int newX, int newY);
    int *toArray();
    const int *toArray() const;
    String toString() const;

    // Operations
    void clear();
    bool operator==(const SDL_Point &rhs);
    bool operator!=(const SDL_Point &rhs);
    Point &operator=(const SDL_Point &rhs);
    Point &operator+=(const SDL_Point &rhs);
    Point &operator-=(const SDL_Point &rhs);
    Point &operator*=(const SDL_Point &rhs);
    Point &operator*=(int scalar);
    Point &operator/=(const SDL_Point &rhs);
    Point &operator/=(int scalar);
    Point &operator%=(const SDL_Point &rhs);
    Point &operator%=(int scalar);
    Point operator-() const;
    Point operator+(const SDL_Point &rhs) const;
    Point operator-(const SDL_Point &rhs) const;
    Point operator*(const SDL_Point &rhs) const;
    Point operator*(int scalar) const;
    Point operator/(const SDL_Point &rhs) const;
    Point operator/(int scalar) const;
    Point operator%(const SDL_Point &rhs) const;
    Point operator%(int scalar) const;
};

//! @brief A C++ wrapper for SDL_Rect which provides useful utilities.
struct Rect : public SDL_Rect
{
public:
    // Construction
    Rect();
    Rect(const SDL_Rect &rhs);
    Rect(int initX, int initY, int initW, int initH);
    Rect(const SDL_Point *points, int count);
    Rect(const SDL_Point *points, int count, const SDL_Rect &clipBounds);

    // Accessors
    bool isEmpty() const;
    bool contains(const SDL_Point &pos) const;
    Rect makeUnion(const SDL_Rect &rhs) const;
    bool hasIntersection(const SDL_Rect &rhs) const;
    bool tryGetOverlap(const SDL_Rect &rhs, SDL_Rect &common) const;
    bool clipLineSegment(SDL_Point &start, SDL_Point &end) const;

    // Operations
    Rect &operator=(const SDL_Rect &rhs);
    bool operator==(const SDL_Rect &rhs) const;
    bool operator!=(const SDL_Rect &rhs) const;
};

//! @brief A C++ wrapper for SDL_Color which provides useful utilities.
struct Colour : public SDL_Color
{
public:
    // Construction/Destruction
    Colour();
    Colour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255);
    Colour(const SDL_Color &rhs);

    // Accessors
    uint32_t pack();
    uint8_t *toArray();
    const uint8_t *toArray() const;
    uint32_t *toPackedArray();
    const uint32_t *toPackedArray() const;
    String toString() const;

    // Operations
    Colour &operator=(const SDL_Color &rhs);
    bool operator==(const SDL_Color &rhs);
    bool operator!=(const SDL_Color &rhs);
};

//! @brief A C++ wrapper for the SDL_FPoint structure.
struct FPoint : public SDL_FPoint
{
public:
    // Construction/Destruction
    FPoint();
    FPoint(float scalar);
    FPoint(float initX, float initY);
    FPoint(const SDL_FPoint &rhs);

    // Accessors
    FPoint &set(float scalar);
    FPoint &set(float newX, float newY);
    float *toArray();
    const float *toArray() const;
    String toString() const;
    float magnitude() const;
    float magnitudeSquared() const;

    // Operations
    void clear();
    bool operator==(const SDL_FPoint &rhs);
    bool operator!=(const SDL_FPoint &rhs);
    FPoint &operator=(const SDL_FPoint &rhs);
    FPoint &operator+=(const SDL_FPoint &rhs);
    FPoint &operator-=(const SDL_FPoint &rhs);
    FPoint &operator*=(const SDL_FPoint &rhs);
    FPoint &operator*=(float scalar);
    FPoint &operator/=(const SDL_FPoint &rhs);
    FPoint &operator/=(float scalar);
    FPoint operator-() const;
    FPoint operator+(const SDL_FPoint &rhs) const;
    FPoint operator-(const SDL_FPoint &rhs) const;
    FPoint operator*(const SDL_FPoint &rhs) const;
    FPoint operator*(float scalar) const;
    FPoint operator/(const SDL_FPoint &rhs) const;
    FPoint operator/(float scalar) const;
};

//! @brief A C++ wrapper for SDL_FRect which provides useful utilities.
struct FRect : public SDL_FRect
{
public:
    // Construction
    FRect();
    FRect(const SDL_FRect &rhs);
    FRect(float initX, float initY, float initW, float initH);
    FRect(const SDL_FPoint *points, int count);
    FRect(const SDL_FPoint *points, int count, const SDL_FRect &clipBounds);

    // Accessors
    bool isEmpty() const;
    bool contains(const SDL_FPoint &pos) const;
    FRect makeUnion(const SDL_FRect &rhs) const;
    bool hasIntersection(const SDL_FRect &rhs) const;
    bool tryGetOverlap(const SDL_FRect &rhs, SDL_FRect &common) const;
    bool clipLineSegment(SDL_FPoint &start, SDL_FPoint &end) const;

    // Operations
    FRect &operator=(const SDL_FRect &rhs);
    bool operator==(const SDL_FRect &rhs) const;
    bool operator!=(const SDL_FRect &rhs) const;
};

//! @brief A C++ wrapper for SDL_FColor which provides useful utilities.
struct FColour : public SDL_FColor
{
public:
    // Construction/Destruction
    FColour();
    FColour(float red, float green, float blue, float alpha = 1.0f);
    FColour(const SDL_FColor &rhs);

    // Accessors
    float *toArray();
    const float *toArray() const;
    String toString() const;
    FColour min(const SDL_FColor &rhs) const;
    FColour max(const SDL_FColor &rhs) const;
    FColour clamp(float minimum, float maximum) const;
    FColour clamp(const SDL_FColor &minimum, const SDL_FColor &maximum) const;
    FColour lerp(const SDL_FColor &towards, float param) const;
    FColour fma(const SDL_FColor &scale, float translation) const;
    FColour fma(const SDL_FColor &scale, const SDL_FColor &translation) const;

    // Operations
    FColour &operator=(const SDL_FColor &rhs);
    bool operator==(const SDL_FColor &rhs);
    bool operator!=(const SDL_FColor &rhs);
    FColour &operator+=(const SDL_FColor &rhs);
    FColour &operator-=(const SDL_FColor &rhs);
    FColour &operator*=(const SDL_FColor &rhs);
    FColour &operator*=(float scalar);
    FColour &operator/=(const SDL_FColor &rhs);
    FColour &operator/=(float scalar);
    FColour operator-() const;
    FColour operator+(const SDL_FColor &rhs) const;
    FColour operator-(const SDL_FColor &rhs) const;
    FColour operator*(const SDL_FColor &rhs) const;
    FColour operator*(float scalar) const;
    FColour operator/(const SDL_FColor &rhs) const;
    FColour operator/(float scalar) const;
};

//! @brief A structure which aliases SDL_Vertex using the C++ wrappers for
//! its component parts.
struct Vertex
{
public:
    // Public Fields
    FPoint position;
    FColour color;
    FPoint tex_coord;

    // Construction/Destruction
    Vertex() = default;
    Vertex(const SDL_FPoint &pos);
    Vertex(const SDL_FPoint &pos, const SDL_FColor &colour);
    Vertex(const SDL_FPoint &pos, const SDL_FColor &colour, const SDL_FPoint &texturePos);
    Vertex(const SDL_FPoint &pos, const SDL_FPoint &texturePos);
    Vertex(float x, float y);
    Vertex(float x, float y, float r, float g, float b, float a = 1.0f);

    // Accessors
    SDL_Vertex *toBase();
    const SDL_Vertex *toBase() const;
};

}} // namespace Ag::SDL3

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
