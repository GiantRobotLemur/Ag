//! @file Geometry/DCEL_Boolean.cpp
//! @brief The definition of functions which perform boolean geometry operations
//! on Doubly-Connected Edge Lists (DCELs).
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/DCEL_Boolean.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
enum TraceState
{
    NotOnAny    = 0x00,
    OnLhs       = 0x01,
    OnRhs       = 0x02,
    OnLhsAndRhs = 0x04,
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Calculates which boolean operand ring the node is on.
//! @param[in] node The node to query.
//! @return The state of the node in relations to boolean operands.
TraceState getNodeState(NodeCPtr node) noexcept
{
    TraceState state = NotOnAny;

    auto nodeFlags = node->getFlags();

    if (nodeFlags & Node::IsLhs)
    {
        if (nodeFlags & Node::IsRhs)
        {
            state = OnLhsAndRhs;
        }
        else
        {
            state = OnLhs;
        }
    }
    else if (nodeFlags & Node::IsRhs)
    {
        state = OnRhs;
    }

    return state;
}

//! @brief Resets half-edge ownership and assigns Rhs rings to edges, ignoring
//! Lhs rings.
//! @param[in] edges The table of all edges in the mesh.
//! @param[in] rings The set of rings to assert primacy for.
void assignLhsRings(EdgeTable &edges, const ExplicitRingCollection &rings)
{
    // Unassigned all rings.
    edges.resetOwnership();

    for (const auto &ring : rings)
    {
        if ((ring.getFlags() & Ring::IsLhs) == 0)
            continue;

        const auto &nodeIDs = ring.getNodes();

        ID prevNodeID = nodeIDs.back();

        for (ID currentNodeID : nodeIDs)
        {
            EdgePtr currentEdge = nullptr;

            if (edges.tryFindEdgeByNodes(prevNodeID, currentNodeID, currentEdge))
            {
                HalfEdgePtr directedEdge = currentEdge->getHalfEdgeFrom(prevNodeID);
                directedEdge->setRingID(ring.getID());
            }

            // Move on to the next edge.
            prevNodeID = currentNodeID;
        }
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Xxx Member Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Sets flags on nodes and edges implied by the rings they appear on.
//! @param[in] nodes The table of nodes to update.
//! @param[in] edges The table of edges to update.
//! @param[in] rings The ring definitions used to update node and edge flags.
void markBooleanOperands(NodeTable &nodes, EdgeTable &edges,
                         const ExplicitRingCollection &rings)
{
    constexpr Node::FlagsType nodeFlagMask = ~(Node::IsLhs | Node::IsRhs);
    constexpr Edge::FlagsType edgeFlagMask = ~(Edge::IsLhs | Edge::IsRhs | Edge::Hole | Edge::Fill);

    for (const ExplicitRing &ring : rings)
    {
        const auto &nodeIDs = ring.getNodes();
        auto ringFlags = ring.getFlags();

        Node::FlagsType nodeFlags = 0;
        Bin::updateMask(nodeFlags, Node::IsLhs, ringFlags & Ring::IsLhs);
        Bin::updateMask(nodeFlags, Node::IsRhs, ringFlags & Ring::IsRhs);

        Edge::FlagsType edgeFlags = 0;
        Bin::updateMask(edgeFlags, Edge::IsLhs, ringFlags & Ring::IsLhs);
        Bin::updateMask(edgeFlags, Edge::IsRhs, ringFlags & Ring::IsRhs);
        Bin::updateMask(edgeFlags, Edge::Hole, ringFlags & Ring::IsHole);
        Bin::updateMask(edgeFlags, Edge::Fill, (ringFlags & Ring::IsHole) == 0);

        ID prevNodeID = nodeIDs.back();

        for (ID currentNodeID : nodeIDs)
        {
            EdgePtr edge = nullptr;
            NodePtr currentNode = nodes[currentNodeID];

            Node::FlagsType currentNodeFlags = currentNode->getFlags();
            currentNode->setFlags((currentNodeFlags & nodeFlagMask) | nodeFlags);

            if (edges.tryFindEdgeByNodes(prevNodeID, currentNodeID, edge))
            {
                Edge::FlagsType currentEdgeFlags = edge->getFlags();
                edge->setFlags((currentEdgeFlags & edgeFlagMask) | edgeFlags);
            }

            // Prepare for the next node.
            prevNodeID = currentNodeID;
        }
    }
}

//! @brief Uses rings marked as Lhs to clip rings marked as Rhs.
//! @param[in] nodes The table of nodes which define the rings to process.
//! @param[in] edges The table of edges which define the rings to process.
//! @param[in] rings All Lhs and Rhs ring definitions.
//! @returns A collection of Rhs rings clipped to Lhs geometry.
//! @remarks
//! The nodes and edges are expected to have flag values which are sympathetic
//! with the initial ring definitions, this can be performed explicitly by
//! calling markBooleanOperands().
//! 
//! The functions adds nodes at intersections and splits edges accordingly. The
//! ring definitions are updated with the intersections.
ExplicitRingCollection clip(NodeTable &nodes, EdgeTable &edges,
                            ExplicitRingCollection &rings)
{
    //auto updatedEdges = findAllIntersections(nodes, edges);

    //if (updatedEdges.isEmpty() == false)
    //{
    //    // Update the ring definitions to include the edges which were split
    //    // and the new intersection nodes.
    //    for (auto &ring : rings)
    //    {
    //        ring.addIntersections(updatedEdges);
    //    }
    //}

    //// Ensure all edges are linked to Lhs rings, we don't care about Rhs rings
    //// as we are about to break them up.
    //assignLhsRings(edges, rings);

    //// For each Rhs ring - clip.
    //ExplicitRingCollection clippedRings;

    //// Process each ring which needs clipping.
    //for (const auto &ringToClip : rings)
    //{
    //    if ((ringToClip.getFlags() & Ring::IsRhs) == 0)
    //        continue;

    //    // Determine whether the top left node of the Rhs ring is inside or
    //    // outside an Lhs ring.
    //    NodePtr startNode = nodes[ringToClip.getNodes().front()];
    //    TraceState state = getNodeState(startNode);


    //}

    return { };
}


}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

