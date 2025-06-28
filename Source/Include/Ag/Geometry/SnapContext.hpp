//! @file SnapContext.hpp
//! @brief The declaration of an object used to snap real points to a grid with
//! arbitrary granularity.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_SNAP_CONTEXT_HPP__
#define __AG_GEOMETRY_SNAP_CONTEXT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Point2D.hpp"

#include "SnapPoint.hpp"

namespace Ag {
namespace Geom {
////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class Rect2D;

//! @brief An object used to snap real points to a grid with arbitrary granularity.
class SnapContext
{
public:
    // Construction/Destruction
    SnapContext(const Rect2D &domain);
    ~SnapContext() = default;

    // Operations
    const NumericDomain &getDomain() const;
    SnapPoint snapPoint(const Point2D &position) const;
    Point2D unsnap(const SnapPoint &snapped) const;
private:
    // Internal Fields
    Point2D _domainOrigin;
    Point2D _domainScale;
    NumericDomain _domain;
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
