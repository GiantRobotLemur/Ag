//! @file Ag/Geometry/DCEL_Boolean.hpp
//! @brief The declaration of functions which perform boolean geometry operations
//! on Doubly-Connected Edge Lists.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_DCEL_BOOLEAN_HPP__
#define __AG_GEOMETRY_DCEL_BOOLEAN_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "DCEL.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {


////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void markBooleanOperands(NodeTable &nodes, EdgeTable &edges,
                         const ExplicitRingCollection &rings);

ExplicitRingCollection clip(NodeTable &nodes, EdgeTable &edges,
                            ExplicitRingCollection &rings);

ExplicitRingCollection unite(NodeTable &nodes, EdgeTable &edges,
                             ExplicitRingCollection &rings);

ExplicitRingCollection symmetricDifference(NodeTable &nodes, EdgeTable &edges,
                                           ExplicitRingCollection &rings);

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
