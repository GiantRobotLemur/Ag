//! @file Geometry/Angle.cpp
//! @brief The definition of a class which represents an angle in radians in a
//! normalised range
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

#include "Ag/Geometry/Angle.hpp"

namespace Ag {
namespace Geom {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Normalises an angle in radians to the range +/-Pi with angles
//! near enough to -Pi snapped to Pi.
//! @param[in] angle The angle to normalise.
//! @return An equivalent angle in the range +/-Pi.
double normaliseAngle(double angle)
{
    double normalisedAngle = angle;

    while (normalisedAngle < -Angle::Pi)
    {
        normalisedAngle += Angle::Pi2;
    }

    while (normalisedAngle > Angle::Pi)
    {
        normalisedAngle -= Angle::Pi2;
    }

    // Snap any angles approaching -Pi to +Pi to deal with wrapping.
    if (Angle::Domain.isNearEqual(normalisedAngle, -Angle::Pi))
    {
        normalisedAngle = Angle::Pi;
    }

    return normalisedAngle;
}

} // Anonymous namespace.

////////////////////////////////////////////////////////////////////////////////
// Angle Public Constant Definitions
////////////////////////////////////////////////////////////////////////////////
const NumericDomain Angle::Domain(-3.1415926535897932384, 3.1415926535897932384);

////////////////////////////////////////////////////////////////////////////////
// Angle Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object with an angular value of 0 radians.
Angle::Angle() :
    _value(0.0)
{
}

//! @brief Constructs a new angle value object by normalising the input value
//! into the range +/-Pi.
//! @param[in] angleInRadians The angle to represent, in radians.
Angle::Angle(double angleInRadians) :
    _value(normaliseAngle(angleInRadians))
{
}

//! @brief Returns an object representing an angle having specified the value
//! in degrees.
//! @param[in] angleInDegrees The angle the returned object should represent.
//! @returns A new angle object.
Angle Angle::fromDegrees(double angleInDegrees)
{
    return Angle(angleInDegrees * Pi / 180.0);
}

//! @brief Gets the value of the angle in radians in the range +/-Pi.
double Angle::toRadians() const { return _value; }

//! @brief Gets the value of the angle in degrees in the range +/- 180.
double Angle::toDegrees() const { return _value * 180.0 / Pi; }

//! @brief Gets the angular offset from the current angular bearing to another.
//! @param[in] nextAngle The angle to calculate the shortest offset to.
//! @return An normalised angular offset in radians in the range +/-Pi.
double Angle::getOffsetTo(const Angle &nextAngle) const
{
    double offset = nextAngle._value - _value;

    return normaliseAngle(offset);
}

//! @brief Creates a version of the angle which points in the opposite direction.
Angle Angle::reverse() const
{
    return Angle(_value + Pi);
}

//! @brief Compares normalised angle values using fuzzy comparison.
//! @param[in] rhs The normalised angle to compare the current value against.
//! @retval &lt;0 The current angle has a lower value than rhs.
//! @retval 0 The current angle has a near-enough value to rhs.
//! @retval &gt;0 The current angle as a higher value than rhs.
//! @note If the two angles differ by near-enough 2 Pi, the function will NOT
//! return 0.
int Angle::compare(const Angle &rhs) const
{
    return Domain.compare(_value, rhs._value);
}

//! @brief Compares normalised angle values using fuzzy comparison.
//! @param[in] rhs The normalised angle to compare the current value against.
//! @retval &lt;0 The current angle has a lower value than rhs.
//! @retval 0 The current angle has a near-enough value to rhs.
//! @retval &gt;0 The current angle as a higher value than rhs.
//! @note If the two angles differ by near-enough 2 Pi, the function will
//! return 0.
int Angle::compareWithWrapping(const Angle &rhs) const
{
    double delta = abs(_value - rhs._value);

    int diff = 0;

    // If the normalised values differ by near-enough 2 * Pi, they have
    // wrapped around to be equal.
    if (Domain.isLessThan(delta, Pi2))
    {
        diff = Domain.compare(_value, rhs._value);
    }

    return diff;
}

//! @brief Copy assigns a scalar angle value to the object.
//! @param[in] value The angle in radians to assign.
//! @return A reference to the current object holding a copy of the angle value
//! normalised into the range +/- Pi.
Angle &Angle::operator=(double value)
{
    _value = normaliseAngle(value);

    return *this;
}

//! @brief Determines if an angle is near-enough equal to the current angle.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The two angles are near-enough equal.
//! @retval false The two angles are not similar enough to be equal.
//! @note If the angles differ by near-enough 2 Pi, they will be treated
//! as equal.
bool Angle::operator==(const Angle &rhs) const
{
    double delta = abs(_value - rhs._value);
    bool isEqual = false;

    // If the normalised values differ by near-enough 2 * Pi, they have
    // wrapped around to be equal.
    if (Domain.isLessThan(delta, Pi2))
    {
        isEqual = Domain.isNearEqual(_value, rhs._value);
    }
    else
    {
        isEqual = true;
    }

    return isEqual;
}

//! @brief Determines if an angle is not near-enough equal to the current angle.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The two angles are not similar enough to be equal.
//! @retval false The two angles are near-enough equal.
//! @note If the angles differ by near-enough 2 Pi, they will be treated
//! as equal.
bool Angle::operator!=(const Angle &rhs) const
{
    double delta = abs(_value - rhs._value);
    bool isNotEqual = true;

    // If the normalised values differ by near-enough 2 * Pi, they have
    // wrapped around to be equal.
    if (Domain.isLessThan(delta, Pi2))
    {
        isNotEqual = (Domain.isNearEqual(_value, rhs._value) == false);
    }

    return isNotEqual;
}

//! @brief Determines if an angle has a lower value than the current one.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The current angle is lower than rhs.
//! @retval false The current angle is near-enough equal or greater than
//! the current angle.
bool Angle::operator<(const Angle &rhs) const
{
    return Domain.isLessThan(_value, rhs._value);
}

//! @brief Determines if an angle has a lower value or is near-enough equal to
//! the current one.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The current angle is lower or near-enough equal to rhs.
//! @retval false The current angle is greater than the current angle.
//! @note If the angles differ by near-enough 2 Pi, they will be treated
//! as equal.
bool Angle::operator<=(const Angle &rhs) const
{
    double delta = abs(_value - rhs._value);

    return Domain.isNearEqual(delta, Pi2) ||
           Domain.isLessThanOrEqual(_value, rhs._value);
}

//! @brief Determines if an angle has a greater value than the current one.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The current angle is higher than rhs.
//! @retval false The current angle is near-enough equal or less than
//! the current angle.
bool Angle::operator>(const Angle &rhs) const
{
    return Domain.isGreaterThan(_value, rhs._value);
}

//! @brief Determines if an angle has a greater value or is near-enough equal to
//! the current one.
//! @param[in] rhs The normalised angle to compare with.
//! @retval true The current angle is higher or near-enough equal to rhs.
//! @retval false The current angle is less than the current angle.
//! @note If the angles differ by near-enough 2 Pi, they will be treated
//! as equal.
bool Angle::operator>=(const Angle &rhs) const
{
    double delta = abs(_value - rhs._value);

    return Domain.isNearEqual(delta, Pi2) ||
           Domain.isGreaterThanOrEqual(_value, rhs._value);
}

//! @brief Calculates the normalised sum of the current angle and another.
//! @param[in] rhs The angle to add to the current one.
//! @return The normalised sum of the angles.
Angle Angle::operator+(const Angle &rhs) const
{
    return Angle(_value + rhs._value);
}

//! @brief Calculates the normalised difference between two angles.
//! @param[in] rhs The angle to subtract from the current one.
//! @return The normalised difference between angles.
Angle Angle::operator-(const Angle &rhs) const
{
    return Angle(_value - rhs._value);
}

//! @brief Calculates the normalised negative of the current angle.
Angle Angle::operator-() const
{
    return Angle(-_value);
}


////////////////////////////////////////////////////////////////////////////////
// AngleOrientation Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an default angular orientation based on the angles returned
//! by the std::atan2() function, LH, counter-clockwise from the X axis.
AngleOrientation::AngleOrientation() noexcept :
    Direction(Orientation::CounterClockwise),
    Anchor(AngleAnchor::PositiveXAxis)
{
}

//! @brief Creates an angular orientation by initialising the individual
//! properties.
//! @param[in] system The 'handedness' of the coordinate system.
//! @param[in] direction The direction in which positive angles turn.
//! @param[in] anchor The line representing an angle of 0.
AngleOrientation::AngleOrientation(Orientation direction,
                                   AngleAnchor anchor) noexcept :
    Direction(direction),
    Anchor(anchor)
{
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Converts and angle from one orientation to another.
//! @param[in] sourceOrientation The orientation definition of the angle to be
//! converted.
//! @param[in] targetOrientation The orientation definition of the angle to
//! convert to.
//! @param[in] source The angle to convert.
//! @returns The angle converted to the target orientation.
Angle convertOrientation(AngleOrientation sourceOrientation,
                         AngleOrientation targetOrientation,
                         Angle source)
{
    double angleInRadians = source.toRadians();

    // There are 16 possible combinations of conversions.
    // The results can be encoded as x and y such that:
    // result = (source * x) + y.
    //
    // Where:
    //  x is -1 or 1
    //  y is -Pi/2, 0 or Pi/2
    //
    // We can encode these transforms in a compressed look-up table as 3 bits.
    // We will encode as 4 bits to make a 64-bit look-up table.
    //
    // NOTE: While there is obvious symmetry allowing the LUT to be reduced
    // to 32-bits the current implementation is branchless, one which capitalised
    // on the symmetry wouldn't be.
    constexpr uint64_t transforms = 0x5142150660512415;

    // Calculate the table index.
    uint8_t key = sourceOrientation.makeKey() | (targetOrientation.makeKey() << 2);

    uint8_t tableEntry = static_cast<uint8_t>(transforms >> (key * 4)) & 0x07;

    double offset = ((tableEntry & 0x03) - 1) * Angle::Pi_2;
    double factor = (tableEntry >> 2) ? 1.0 : -1.0;

    double transformedAngle = (angleInRadians + offset) * factor;

    return Angle(transformedAngle);
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

