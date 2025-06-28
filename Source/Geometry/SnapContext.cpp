//! @file Geometry/SnapContext.cpp
//! @brief The definition an object used to snap real points to a grid with
//! arbitrary granularity.
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

#include <algorithm>
#include <limits>

#include "Ag/Core/Utils.hpp"
#include "Ag/Geometry/NumericDomain.hpp"
#include "Ag/Geometry/Rect2D.hpp"
#include "Ag/Geometry/SnapContext.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// SnapContext Members Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which can snap real points to a uniform grid.
//! @param[in] domain The expected range of spatial points to snap.
SnapContext::SnapContext(const Rect2D &domain) :
    _domainOrigin(domain.getOrigin()),
    _domain(std::min(domain.getMinimumX(), domain.getMinimumY()),
            std::max(domain.getMaximumX(), domain.getMaximumY()))
{
    using SnapType = std::numeric_limits<int64_t>;
    using RealType = std::numeric_limits<double>;

    // Calculate the maximum size of the snapping grid with some additional
    // resolution.
    const double maxValue = pow(10.0, RealType::digits10 - 2);
    Point2D maxSnapExtents(maxValue, maxValue);

    const Point2D extents(domain.getExtents());

    // Calculate the scale from real points to the snapping grid.
    _domainScale = maxSnapExtents / extents;
}

//! @brief Gets the object used to aid comparisons of positions within the
//! snap context.
const NumericDomain &SnapContext::getDomain() const
{
    return _domain;
}

//! @brief Creates a point snapped to the uniform grid from a real point.
//! @param[in] position The real position to snap.
//! @returns A point on the integer grid.
SnapPoint SnapContext::snapPoint(const Point2D &position) const
{
    Point2D domainPoint = (position - _domainOrigin) * _domainScale;

    return SnapPoint(Ag::roundNearest<int64_t>(domainPoint.getX()),
                     Ag::roundNearest<int64_t>(domainPoint.getY()));
}

//! @brief Converts a point on the snapping grid back to its real interpretation.
//! @param[in] snapped The grid point to convert.
//! @returns A real position in the pre-defined domain, though with accuracy
//! truncated to that of the grid.
Point2D SnapContext::unsnap(const SnapPoint &snapped) const
{
    Point2D source(static_cast<double>(snapped.getX()),
                   static_cast<double>(snapped.getY()));

    return (source / _domainScale) + _domainOrigin;
}

}} // namespace Ag::Geom
////////////////////////////////////////////////////////////////////////////////

