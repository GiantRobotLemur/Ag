//! @file Ag/Geometry/DCEL_Algorithms.hpp
//! @brief The declaration of various algorithms which operate on a Doubly
//! Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_DCEL_ALGORITHMS_HPP__
#define __AG_GEOMETRY_DCEL_ALGORITHMS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "DCEL.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A functor which compares directed edges by their direction.
struct CompareHalfEdgeByAngle
{
    bool operator()(HalfEdgePtr lhs, HalfEdgePtr rhs) const;
    bool operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const;
};

//! @brief A functor which compares directed edges by their direction.
struct CompareHalfEdgeByRelativeAngle
{
private:
    Angle _baseAngle;
    bool _reverse;
public:
    CompareHalfEdgeByRelativeAngle(const Angle &baseAngle, bool reverse);

    bool operator()(HalfEdgePtr lhs, HalfEdgePtr rhs) const;
    bool operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const;
};

//! @brief A functor which compares the grid position of nodes by X and then Y
//! components.
struct CompareNodeByHorizontalPosition
{
public:
    static constexpr bool IsFirstCCWEdgeHigh = false;
    bool isParallel(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const;
    bool operator()(const SnapPoint &lhs, const SnapPoint &rhs) const;
};

//! @brief A functor which compares the grid position of nodes by Y and then X
//! components.
struct CompareNodeByVerticalPosition
{
public:
    static constexpr bool IsFirstCCWEdgeHigh = true;
    bool isParallel(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const;
    bool operator()(const SnapPoint &lhs, const SnapPoint &rhs) const;
};

//! @brief A functor which compares the grid position of nodes by Y and then X
//! components.
struct CompareNodeYMonotoneSweepOrder
{
public:
    static constexpr bool IsFirstCCWEdgeHigh = true;
    bool isParallel(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(NodeCPtr lhs, NodeCPtr rhs) const;
    bool operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const;
    bool operator()(const SnapPoint &lhs, const SnapPoint &rhs) const;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
uint32_t classifyXMonotonePoint(uint32_t ringFlags,
                                NodeCPtr prevNode, NodeCPtr currentNode,
                                NodeCPtr nextNode);
uint32_t classifyYMonotonePoint(uint32_t ringFlags,
                                NodeCPtr prevNode, NodeCPtr currentNode,
                                NodeCPtr nextNode);
void assignEdgesLeftOfNodes(NodeTable &nodes, EdgeTable &edges);

bool makeYMonotone(NodeTable &nodes, EdgeTable &edges, RingSystem &rings);

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
