//! @file Ag/Geometry/Angle.hpp
//! @brief The declaration of a class which represents an angle in radians in a
//! normalised range.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_ANGLES_HPP__
#define __AG_GEOMETRY_ANGLES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include "NumericDomain.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An enumeration which expresses the relative orientation of coordinate
//! axes for the purposes of angle manipulation.
enum class CoordSystem : uint8_t
{
    //! @brief With a positive Z-axis which proceeds into the screen, positive X
    //! proceeds right and positive Y, up.
    LeftHanded,

    //! @brief With a positive Z-axis which proceeds into the screen, positive X
    //! proceeds right and positive Y, down.
    RightHanded,
};

//! @brief An enumeration which expresses the orientation of positive angles.
enum class Orientation : uint8_t
{
    //! @brief Positive angles proceed in a clockwise direction.
    Clockwise,

    //! @brief Positive angles proceed in a counter-clockwise direction.
    CounterClockwise
};

//! @brief An enumeration which expresses the base line which angles are
//! measured relative to.
enum class AngleAnchor : uint8_t
{
    //! @brief Angles are relative to the line Y=0.
    PositiveXAxis,

    //! @brief Angles are relative to the line X=0.
    PositiveYAxis,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class which represents an angle in radians in a normalised range of
//! +/- Pi radians.
class Angle
{
public:
    // Public Constants

    // NOTE: Constants are to the maximum precision of a double data type.

    //! @brief A value of Pi accurate to the range of a double.
    static constexpr double Pi      = 3.1415926535897932384;

    //! @brief A value of 2 * Pi accurate to the range of a double.
    static constexpr double Pi2     = 6.2831853071795864769;

    //! @brief A value of 0.5 * Pi accurate to the range of a double.
    static constexpr double Pi_2    = 1.5707963267948966192;

    //! @brief A value of 0.25 * Pi accurate to the range of a double.
    static constexpr double Pi_4    = 0.7853981633974483096;

    //! @brief An object representing the domain of normalised angle values.
    static const NumericDomain Domain;

    // Construction/Destruction
    Angle();
    explicit Angle(double angleInRadians);
    static Angle fromDegrees(double angleInDegrees);
    ~Angle() = default;

    // Accessors
    double toRadians() const;
    double toDegrees() const;
    double getOffsetTo(const Angle &nextAngle) const;

    //! @brief Converts an angle from degrees to radians without normalisation.
    //! @param[in] angleInDegrees The angle in degrees to convert.
    //! @return The equivalent angle in degrees.
    static constexpr double Angle::degreesToRadians(double angleInDegrees) noexcept
    {
        return (angleInDegrees * Pi) / 180.0;
    }

    //! @brief Converts an angle from radians to degrees without normalisation.
    //! @param[in] angleInRadians The angle in radians to convert.
    //! @return The equivalent angle in radians.
    static constexpr double Angle::radiansToDegrees(double angleInRadians) noexcept
    {
        return (angleInRadians * 180.0) / Pi;
    }

    // Operations
    Angle reverse() const;
    int compare(const Angle &rhs) const;
    int compareWithWrapping(const Angle &rhs) const;
    Angle &operator=(double value);
    bool operator==(const Angle &rhs) const;
    bool operator!=(const Angle &rhs) const;
    bool operator<(const Angle &rhs) const;
    bool operator<=(const Angle &rhs) const;
    bool operator>(const Angle &rhs) const;
    bool operator>=(const Angle &rhs) const;
    Angle operator+(const Angle &rhs) const;
    Angle operator-(const Angle &rhs) const;
    Angle operator-() const;

#ifdef GOOGLETEST_INCLUDE_GTEST_GTEST_H_
    // Google Test output integration.
    friend std::ostream &operator<<(std::ostream &os, const Angle &value) {
        return os << value.toDegrees() << " degrees"; // The 'degrees' sign
    }
#endif
private:
    // Internal Fields
    double _value;
};

//! @brief A structure which defines the orientation of a relative angle based
//! in the LH coordinate system.
struct AngleOrientation
{
    // Public Members

    //! @brief Defines the direction of a positive angle.
    Orientation Direction;

    //! @brief Defines the fixed direction of an angle of 0.0.
    AngleAnchor Anchor;

    // Construction/Destruction
    AngleOrientation() noexcept;
    AngleOrientation(Orientation direction, AngleAnchor anchor) noexcept;
    ~AngleOrientation() = default;

    // Accessors
    //! @brief Makes a numeric key based on the property values.
    constexpr uint8_t makeKey() const noexcept
    {
        return static_cast<uint8_t>(Direction) |
            (static_cast<uint8_t>(Anchor) << 1);
    }

    // Operations
    //! @brief Determines if two orientations are equal.
    //! @param[in] rhs The orientation to compare against.
    //! @retval true The orientations are equal.
    //! @retval false At least one property differs between orientations.
    constexpr bool operator==(const AngleOrientation &rhs) const noexcept
    {
        return makeKey() == rhs.makeKey();
    }

    //! @brief Determines if two orientations are not equal.
    //! @param[in] rhs The orientation to compare against.
    //! @retval true At least one property differs between orientations.
    //! @retval false The orientations are equal.
    constexpr bool operator!=(const AngleOrientation &rhs) const noexcept
    {
        return makeKey() != rhs.makeKey();
    }
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
Angle convertOrientation(AngleOrientation sourceOrientation,
                         AngleOrientation targetOrientation,
                         Angle source);

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
