//! @file NumericDomain.hpp
//! @brief The declaration of an object which defines the domain of a set of
//! scalar values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to-
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_NUMERIC_DOMAIN_HPP__
#define __AG_GEOMETRY_NUMERIC_DOMAIN_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

namespace Ag {

//! @brief Contains both 2D and 3D geometry primitives and tools.
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which defines the domain of a set of scalar values.
class NumericDomain
{
public:
    // Public Constants
    //! @brief Provides tolerances for a domain between 0.0 and 1.0.
    static const NumericDomain UnsignedScalar;

    //! @brief Provides tolerances for a domain between -1.0 and 1.0.
    static const NumericDomain SignedScalar;

    // Construction/Destruction
    NumericDomain(double tolerance);
    NumericDomain(double minValue, double maxValue);

    // Accessors
    double getTolerance() const;

    // Operations
    int sign(double value) const;
    bool isNearZero(double value) const;
    bool isNearEqual(double lhs, double rhs) const;
    bool trySnap(double &value, double target) const;
    bool trySnapRange(double &value, double targetMin, double targetMax) const;
    bool isLessThan(double lhs, double rhs) const;
    bool isLessThanOrEqual(double lhs, double rhs) const;
    bool isGreaterThan(double lhs, double rhs) const;
    bool isGreaterThanOrEqual(double lhs, double rhs) const;
    int compare(double lhs, double rhs) const;
private:
    // Internal Fields
    double _epsilon;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
