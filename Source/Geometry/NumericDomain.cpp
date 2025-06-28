//! @file Geometry/NumericDomain.cpp
//! @brief The definition of an object which defins the domain of a set of
//! scalar values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <limits>

#include "Ag/Geometry/NumericDomain.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// NumericDomain Member Definitions
////////////////////////////////////////////////////////////////////////////////
const NumericDomain NumericDomain::UnsignedScalar(0.0, 1.0);
const NumericDomain NumericDomain::SignedScalar(-1.0, 1.0);

//! @brief Constructs an object with a specific tolerance used to determine if
//! two values in the domain are near-enough to be considered equal.
//! @param[in] tolerance The maximum delta between values which should be
//! considered equal.
NumericDomain::NumericDomain(double tolerance) :
    _epsilon(std::abs(tolerance))
{
}

//! @brief Constructs an object by calculating the tolerance required to
//! manipulate a numeric domain spanning a specific range of values.
//! @param[in] minValue The likely minimum value in the domain.
//! @param[in] maxValue The likely maximum value in the domain.
NumericDomain::NumericDomain(double minValue, double maxValue) :
    _epsilon(0.0)
{
    double range = std::abs(maxValue - minValue);
    double divisor = std::pow(10.0, std::numeric_limits<double>::max_digits10 - 2);

    _epsilon = range / divisor;
}

//! @brief Gets the maximum delta between values in the domain for them to be
//! considered equal.
double NumericDomain::getTolerance() const { return _epsilon; }

//! @brief Extracts the sign of a scalar value with leeway for what constitutes zero.
//! @param[in] value The value to analyse.
//! @retval 1 The value was greater than zero.
//! @retval 0 The value was near-enough zero.
//! @retval -1 The value was less than zero.
int NumericDomain::sign(double value) const
{
    if (value >= _epsilon)
    {
        return 1;
    }
    else if (value <= -_epsilon)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//! @brief Determines if a value is near-enough equal to zero in the domain.
//! @param[in] value The value to test.
//! @retval true The value is near enough to zero to be considered to be zero.
//! @retval false The value is not zero.
bool NumericDomain::isNearZero(double value) const
{
    return std::abs(value) < _epsilon;
}

//! @brief Determines if two values in the domain are near-enough equal.
//! @param[in] lhs The first value to compare.
//! @param[in] rhs The second value to compare.
//! @retval true The delta between lhs and rhs is small enough for them to be
//! considered to be equal.
//! @retval false The values of lhs and rhs are not equal.
bool NumericDomain::isNearEqual(double lhs, double rhs) const
{
    return std::abs(lhs - rhs) < _epsilon;
}

//! @brief Attempt to snap an input value to a target value.
//! @param[in,out] value The value to snap, possibly updated if snapped.
//! @param[in] target The value to snap to.
//! @retval true The value was close enough to target to be snapped and
//! was overwritten with target.
//! @retval false The value was not close to target.
bool NumericDomain::trySnap(double &value, double target) const
{
    bool isSnapped = false;

    if (std::abs(value - target) < _epsilon)
    {
        value = target;
        isSnapped = true;
    }

    return isSnapped;
}

//! @brief Snaps a value into a range if it is within or close enough to the
//! upper or lower bounds.
//! @param[in,out] value The value to snap, possibly overwritten with targetMin
//! or targetMax if snapped.
//! @param[in] targetMin The lower bound of the range to snap to.
//! @param[in] targetMax The upper bound of the range to snap to.
//! @retval true The value is within the range, possibly due to snapping.
//! @retval false The value is outside the required range.
bool NumericDomain::trySnapRange(double &value, double targetMin,
                                 double targetMax) const
{
    bool isInRange = true;

    if (value < targetMin)
    {
        if ((targetMin - value) < _epsilon)
        {
            value = targetMin;
        }
        else
        {
            isInRange = false;
        }
    }
    else if (value > targetMax)
    {
        if ((value - targetMax) < _epsilon)
        {
            value = targetMax;
        }
        else
        {
            isInRange = false;
        }
    }

    return isInRange;
}

//! @brief Determines if a value is less-than but not near-enough equal to another.
//! @param[in] lhs The control value to compare against.
//! @param[in] rhs The value to compare.
//! @retval true If lhs is less than rhs minus the tolerance.
//! @retval false If lhs is greater than, or within the tolerance of, rhs.
//! @note If lhs is less than rhs, but the values are within the tolerance
//! distance, they are considered equal and false is returned.
bool NumericDomain::isLessThan(double lhs, double rhs) const
{
    double delta = rhs - lhs - _epsilon;

    return (delta >= 0.0);
}

//! @brief Determines if a value is less-than or near-enough equal to another.
//! @param[in] lhs The control value to compare against.
//! @param[in] rhs The value to compare.
//! @retval true If lhs and rhs are within the tolerance distance of each other
//! or lhs is less than rhs.
//! @retval false If lhs is greater than rhs and outside the tolerance range.
//! @note If lhs is greater than rhs, but the values are within the tolerance
//! distance, they are considered equal and true is returned.
bool NumericDomain::isLessThanOrEqual(double lhs, double rhs) const
{
    double delta = rhs - lhs;

    return (delta >= 0.0) || (std::abs(delta) < _epsilon);
}


//! @brief Determines if a value is greater-than but not near-enough equal to another.
//! @param[in] lhs The control value to compare against.
//! @param[in] rhs The value to compare.
//! @retval true If lhs is greater rhs plus the tolerance.
//! @retval false If lhs is less than, or within the tolerance of, rhs.
//! @note If lhs is greater than rhs, but the values are within the tolerance
//! distance, they are considered equal and false is returned.
bool NumericDomain::isGreaterThan(double lhs, double rhs) const
{
    double delta = lhs - rhs - _epsilon;

    return (delta >= 0.0);
}

//! @brief Determines if a value is greater-than or near-enough equal to another.
//! @param[in] lhs The control value to compare against.
//! @param[in] rhs The value to compare.
//! @retval true If lhs and rhs are within the tolerance distance of each other
//! or lhs is greater than rhs.
//! @retval false If lhs is less than rhs and outside the tolerance range.
//! @note If lhs is less than rhs, but the values are within the tolerance
//! distance, they are considered equal and true is returned.
bool NumericDomain::isGreaterThanOrEqual(double lhs, double rhs) const
{
    double delta = lhs - rhs;

    return (delta >= 0.0) || (std::abs(delta) < _epsilon);
}

//! @brief Compares two values in the domain.
//! @param[in] lhs The first value to compare.
//! @param[in] rhs The second value to compare.
//! @retval <0 The value of lhs is less than the value of rhs.
//! @retval 0 The values of lhs and rhs are close enough to be considered to be
//! equal.
//! @retval >0 The values of lhs is greater than the value of rhs.
int NumericDomain::compare(double lhs, double rhs) const
{
    int diff = 0;

    if (std::abs(lhs - rhs) >= _epsilon)
    {
        diff = (lhs < rhs) ? -1 : 1;
    }

    return diff;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

