//! @file Gfx2D/Colour.cpp
//! @brief The definition of a representation of a colour value using RGBA values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Colour.hpp"
#include "Operations.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Colour Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a default colour value which is opaque black.
Colour::Colour() noexcept :
    _red(0),
    _green(0),
    _blue(0),
    _alpha(1)
{
}

//! @brief Copy constructs a colour value from another.
//! @param[in] rhs The colour value used to create this one.
Colour::Colour(Colour &&rhs) noexcept
{
    Operations_Vec4F::copy(&rhs._red, &_red);
}

Colour::Colour(const Colour &rhs) noexcept
{
    Operations_Vec4F::copy(&rhs._red, &_red);
}


//! @brief Constructs a colour from an array of RGBA values.
//! @param[in] vector An array containing at least four elements.
Colour::Colour(const float *vector) noexcept :
    _red(vector[0]),
    _green(vector[1]),
    _blue(vector[2]),
    _alpha(vector[3])
{
}

//! @brief Constructs an initialised colour value.
//! @param[in] red The initial red component, nominally between 0.0 and 1.0.
//! @param[in] green The initial green component, nominally between 0.0 and 1.0.
//! @param[in] blue The initial blue component, nominally between 0.0 and 1.0.
//! @param[in] alpha The initial alpha transparency component, nominally between
//! 0.0 and 1.0.
Colour::Colour(float red, float green, float blue, float alpha /*= 1.0f*/) noexcept :
    _red(red),
    _green(green),
    _blue(blue),
    _alpha(alpha)
{
}

//! @brief Determines if a colour object has an equal value to the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true The @p rhs colour has the same value for all components.
//! @retval false At least one component of @p rhs differs from the current object.
bool Colour::operator==(const Colour &rhs) const noexcept
{
    return (_red == rhs._red) &&
        (_green == rhs._green) &&
        (_blue == rhs._blue) &&
        (_alpha == rhs._alpha);
}

//! @brief Determines if a colour object has a differing value from the current object.
//! @param[in] rhs The colour value to compare against.
//! @retval true At least one component of @p rhs differs from the current object.
//! @retval false The @p rhs colour has the same value for all components.
bool Colour::operator!=(const Colour &rhs) const noexcept
{
    return (_red != rhs._red) ||
        (_green != rhs._green) ||
        (_blue != rhs._blue) ||
        (_alpha != rhs._alpha);
}

//! @brief Overwrites the colour value with another.
//! @param[in] rhs The colour value to copy over this one.
//! @return A reference to the current object.
Colour &Colour::operator=(const Colour &rhs) noexcept
{
    Operations_Vec4F::copy(&rhs._red, &_red);

    return *this;
}

//! @brief Overwrites the colour value with another.
//! @param[in] rhs The colour value to copy over this one.
//! @return A reference to the current object.
Colour &Colour::operator=(Colour &&rhs) noexcept
{
    Operations_Vec4F::copy(&rhs._red, &_red);

    return *this;
}

//! @brief Creates a colour which is the sum of the current and another object.
//! @param[in] rhs The colour with components to add.
//! @return A new colour value with summed components.
Colour Colour::operator+(const Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::add(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Creates a colour which is the difference between the current value
//! and another object.
//! @param[in] rhs The colour value to take away from the current one.
//! @return The difference between this and @p rhs.
Colour Colour::operator-(const Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::sub(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Creates a colour which is the product of this and another colour.
//! @param[in] rhs The colour value to multiple.
//! @return The component-wise product of this and @p rhs.
Colour Colour::operator*(const Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::mul(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Creates a colour which is the product of this and a scalar.
//! @param[in] rhs The scalar to multiply all components by.
//! @return A colour with all components multiplied by @p rhs.
Colour Colour::operator*(float rhs) const
{
    float result[4];
    Operations_Vec4F::mul(&_red, rhs, result);

    return Colour(result);
}

//! @brief Creates a colour which is the component-wise quotient of this
//! divided by another colour.
//! @param[in] rhs The colour value which forms the denominator.
//! @return A quotient colour value.
Colour Colour::operator/(const Colour &rhs) const
{
    if (Operations_Vec4F::anyZero(&rhs._red))
        throw DivisionByZeroException("The colour denominator had a zero component.");

    float result[4];
    Operations_Vec4F::div(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Creates a colour which is the component-wise quotient of this
//! object divided by a scalar.
//! @param[in] rhs The scalar denominator.
//! @return The quotient colour value.
Colour Colour::operator/(float rhs) const
{
    if (rhs == 0)
        throw DivisionByZeroException("The colour denominator was zero.");

    float result[4];
    Operations_Vec4F::div(&_red, rhs, result);

    return Colour(result);
}

//! @brief Performs component-wise addition on the current object.
//! @param[in] rhs The colour components to add to the current ones.
//! @return A reference to the current object.
Colour &Colour::operator+=(const Colour &rhs)
{
    Operations_Vec4F::addAssign(&_red, &rhs._red);

    return *this;
}

//! @brief Performs component-wise subtraction on the current object.
//! @param[in] rhs The colour components to subtract from the current ones.
//! @return A reference to the current object.
Colour &Colour::operator-=(const Colour &rhs)
{
    Operations_Vec4F::subAssign(&_red, &rhs._red);

    return *this;
}

//! @brief Performs component-wise multiplication on the current object.
//! @param[in] rhs The colour components to multiply the current object by.
//! @return A reference to the current object.
Colour &Colour::operator*=(const Colour &rhs)
{
    Operations_Vec4F::mulAssign(&_red, &rhs._red);

    return *this;
}

//! @brief Performs component-wise multiplication of the current object by a scalar.
//! @param[in] rhs The scalar to multiply the current object by.
//! @return A reference to the current object.
Colour &Colour::operator*=(float rhs)
{
    Operations_Vec4F::mulAssign(&_red, rhs);

    return *this;
}

//! @brief Performs component-wise division on the current object.
//! @param[in] rhs The colour components to divide the current object by.
//! @return A reference to the current object.
Colour &Colour::operator/=(const Colour &rhs)
{
    if (Operations_Vec4F::anyZero(&rhs._red))
        throw DivisionByZeroException("The colour denominator had a zero component.");

    Operations_Vec4F::divAssign(&_red, &rhs._red);

    return *this;
}

//! @brief Performs component-wise division on the current object.
//! @param[in] rhs The scalar denominator to divide the current object by.
//! @return A reference to the current object.
Colour &Colour::operator/=(float rhs)
{
    if (rhs == 0)
        throw DivisionByZeroException("The colour denominator had a zero component.");

    Operations_Vec4F::mulAssign(&_red, rhs);

    return *this;
}

//! @brief Calculates the minimum of all component values.
//! @param[in] rhs The colour value to compare against.
//! @return A colour value with minimum component values.
Colour Colour::min(const Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::min(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Calculates the maximum of all component values.
//! @param[in] rhs The colour value to compare against.
//! @return A colour value with maximum component values.
Colour Colour::max(const Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::max(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Calculates the minimum and maximum of all component values.
//! @param[in] rhs The colour value to compare against.
//! @return A colour value pair with minimum and maximum component values.
std::pair<Colour, Colour> Colour::minmax(const Colour &rhs) const
{
    float result[8];
    Operations_Vec4F::minmax(&_red, &rhs._red, result);

    return { Colour(result), Colour(result + 4) };
}

//! @brief Calculates a colour value with clamped components.
//! @param[in] min The minimum component value.
//! @param[in] max The maximum component value.
//! @return The current colour with its component values clamped.
Colour Colour::clamp(const Colour &min, const Colour &max) const
{
    float result[4];
    Operations_Vec4F::clamp(&_red, &min._red, &max._red, result);

    return Colour(result);
}

//! @brief Calculates a linear interpolation between the current colour and
//! another.
//! @param[in] toward The colour value to interpolate towards.
//! @param[in] scalar The value indicating the amount of each colour to mix,
//! 0.0 for all the current value, 1.0 for all @p towards, 0.5 for half way
//! in between.
//! @return A blended colour value.
Colour Colour::lerp(const Colour &toward, float scalar) const
{
    float result[4];
    Operations_Vec4F::lerp(&_red, &toward._red, scalar, result);

    return Colour(result);
}

//! @brief Performs a component-wise fused-multiply-add on this colour value.
//! @param[in] scale The colour value containing the values to multiply by.
//! @param[in] offset The colour value containing the values to add.
//! @return The resultant colour.
Colour Colour::fma(const Colour &scale, const Colour &offset) const
{
    float result[4];
    Operations_Vec4F::fma(&_red, &scale._red, &offset._red, result);

    return Colour(result);
}

//! @brief Blends the current colour onto another using the alpha channel.
//! @param[in] rhs The colour to blend onto using the current alpha value.
//! @return A blended colour value with an alpha channel of 1.0.
Colour Colour::alphaBlend(Colour &rhs) const
{
    float result[4];
    Operations_Vec4F::sourceBlend(&_red, &rhs._red, result);

    return Colour(result);
}

//! @brief Blends the current colour onto another using a fixed transparency value.
//! @param[in] rhs The colour to blend onto using the current alpha value.
//! @param[in] alpha The transparency value used to blend colours.
//! @return A blended colour value with an alpha channel of 1.0.
Colour Colour::alphaBlend(Colour &rhs, float alpha) const
{
    float result[4];
    Operations_Vec4F::constantBlend(&_red, &rhs._red, alpha, result);

    return Colour(result);
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

