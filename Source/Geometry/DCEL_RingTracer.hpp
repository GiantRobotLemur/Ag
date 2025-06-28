//! @file Geometry/DCEL_RingTracer.hpp
//! @brief The declaration of internal structures and functions used to trace
//! a system of rings and holes from nodes and edges.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_DCEL_RING_TRACER_HPP__
#define __AG_GEOMETRY_DCEL_RING_TRACER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/DCEL.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
RingCollection traceRings(NodeTable &nodes, EdgeTable &edges,
                          bool hasBuddyEdges = false);

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
