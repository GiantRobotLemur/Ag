//! @file Geometry/DCEL_Boolean.cpp
//! @brief The definition of functions which perform boolean geometry operations
//! on Doubly-Connected Edge Lists (DCELs).
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <unordered_map>

#include "Ag/Geometry/DCEL_Boolean.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"
#include "DCEL_RingTracer.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief Identifies which boolean operation is being performed.
enum class BooleanOpKind
{
    Intersect,
    Unite,
};

//! @brief A transient marker bit set on each half-edge that survives the
//! boolean classification step. Cleared at the start of every booleanOp() call.
constexpr HalfEdge::FlagsType OnResult = 0x01;

//! @brief For each operand-flagged edge, records the half-edge direction
//! (DirectionIndex 0 or 1) whose left-hand side faces the operand's fill
//! region. A value of 2 indicates the edge does not bound that operand.
struct OperandFillSides
{
    DirectionIndex lhs = 2;
    DirectionIndex rhs = 2;
};

using OperandFillMap = std::unordered_map<ID, OperandFillSides>;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Iterates each operand-flagged ring and records, per edge, the
//! direction in which the operand's fill region lies on the half-edge's
//! left-hand side.
//! @param[in] edges The edge table containing the post-split DCEL.
//! @param[in] rings The ring definitions, with intersection nodes already added.
//! @param[out] output The map to populate with per-edge fill-side directions.
void computeOperandFillSides(EdgeTable &edges,
                             const ExplicitRingCollection &rings,
                             OperandFillMap &output)
{
    output.clear();
    output.reserve(edges.getCount());

    for (const ExplicitRing &ring : rings)
    {
        const Ring::FlagsType ringFlags = ring.getFlags();
        const bool isLhs = (ringFlags & Ring::IsLhs) != 0;
        const bool isRhs = (ringFlags & Ring::IsRhs) != 0;

        if (!isLhs && !isRhs)
            continue;

        const bool isHole = (ringFlags & Ring::IsHole) != 0;
        const bool isCCW  = (ringFlags & Ring::IsCCW) != 0;

        const auto &nodeIDs = ring.getNodes();

        if (nodeIDs.size() < 2)
            continue;

        ID prevNodeID = nodeIDs.back();

        for (ID currentNodeID : nodeIDs)
        {
            EdgePtr edge = nullptr;

            if (edges.tryFindEdgeByNodes(prevNodeID, currentNodeID, edge))
            {
                // The half-edge starting at prevNodeID in this stored
                // traversal direction is direction 0 if prevNodeID is the
                // edge's first node, else direction 1.
                const uint8_t storedDir =
                    (edge->getFirstNodeID() == prevNodeID) ? 0u : 1u;

                // The CCW direction of the ring is the stored direction if
                // the ring is wound CCW, otherwise the opposite.
                const uint8_t ccwDir = isCCW ? storedDir
                                             : static_cast<uint8_t>(1u - storedDir);

                // For a fill ring the fill is on the left of the CCW
                // direction; for a hole the fill is on the left of the CW
                // direction.
                const uint8_t fillOnLeftDir =
                    isHole ? static_cast<uint8_t>(1u - ccwDir) : ccwDir;

                OperandFillSides &sides = output[edge->getID()];
                if (isLhs) sides.lhs = fillOnLeftDir;
                if (isRhs) sides.rhs = fillOnLeftDir;
            }

            prevNodeID = currentNodeID;
        }
    }
}

//! @brief Determines whether a point lies inside a region bounded by edges
//! flagged with @p operandEdgeFlag, by horizontal even-odd ray-casting.
//! @param[in] point The position to test.
//! @param[in] edges The edge table containing the operand boundary edges.
//! @param[in] operandEdgeFlag Either Edge::IsLhs or Edge::IsRhs.
//! @retval true The point is in the interior of the operand region.
//! @retval false The point is outside the operand region.
//! @remarks The test point should not lie on any operand-flagged edge. In the
//! clip() pipeline this is achieved by passing a half-edge midpoint, which
//! after findAllIntersections cannot coincide with another operand edge unless
//! that edge is itself coincident (handled separately as a shared boundary).
bool isPointInsideOperand(const Point2D &point, EdgeTable &edges,
                          Edge::FlagsType operandEdgeFlag)
{
    int crossings = 0;
    const double px = point.getX();
    const double py = point.getY();

    edges.forEachEdge([&](EdgePtr e) {
        if ((e->getFlags() & operandEdgeFlag) == 0)
            return;

        const Point2D &a = e->getFirstNode()->getRealPosition();
        const Point2D &b = e->getSecondNode()->getRealPosition();

        const double ay = a.getY();
        const double by = b.getY();

        // Half-open Y range avoids double-counting at shared vertices.
        if ((ay <= py) != (by <= py))
        {
            const double xIntersect = a.getX() +
                (py - ay) * (b.getX() - a.getX()) / (by - ay);

            if (xIntersect < px)
                ++crossings;
        }
    });

    return (crossings & 1) == 1;
}

//! @brief Clears the OnResult marker on every half-edge in the table.
void clearOnResultFlags(EdgeTable &edges)
{
    edges.applyToAllEdges([](EdgePtr e) {
        constexpr HalfEdge::FlagsType mask = static_cast<HalfEdge::FlagsType>(~OnResult);
        HalfEdgePtr h0 = e->getHalfEdge(0);
        HalfEdgePtr h1 = e->getHalfEdge(1);
        h0->setFlags(h0->getFlags() & mask);
        h1->setFlags(h1->getFlags() & mask);
    });
}

//! @brief The shared workhorse for boolean operations. Mutates @p nodes,
//! @p edges and @p rings in place and returns the boundary rings of the
//! result.
//! @param[in,out] nodes The node table; intersection nodes are added.
//! @param[in,out] edges The edge table; split at intersections, then pruned
//! to the result-boundary subdivision.
//! @param[in,out] rings The operand ring definitions, augmented with
//! intersection nodes during the split.
//! @param[in] op Selects the boolean operation to apply.
//! @returns The boundary rings of the result, with operand flags cleared.
ExplicitRingCollection booleanOp(NodeTable &nodes, EdgeTable &edges,
                                 ExplicitRingCollection &rings,
                                 BooleanOpKind op)
{
    // Stage A: split at intersections and propagate operand flags onto every
    // sub-edge and intersection node.
    auto substitutes = findAllIntersections(nodes, edges);

    for (auto &ring : rings)
        ring.addIntersections(substitutes);

    markBooleanOperands(nodes, edges, rings);

    // Stage B: per-edge "fill on left" direction for each operand.
    OperandFillMap fillSides;
    computeOperandFillSides(edges, rings, fillSides);

    clearOnResultFlags(edges);

    // Stage C: classify each operand-bearing edge against the result predicate.
    edges.forEachEdge([&](EdgePtr e) {
        const Edge::FlagsType eFlags = e->getFlags();
        const bool isLhsEdge = (eFlags & Edge::IsLhs) != 0;
        const bool isRhsEdge = (eFlags & Edge::IsRhs) != 0;

        if (!isLhsEdge && !isRhsEdge)
            return;

        auto sidesIt = fillSides.find(e->getID());
        if (sidesIt == fillSides.end())
            return;

        const OperandFillSides &sides = sidesIt->second;

        auto markKept = [&](uint8_t dir) {
            HalfEdgePtr he = e->getHalfEdge(static_cast<DirectionIndex>(dir));
            he->setFlags(he->getFlags() | OnResult);
        };

        if (isLhsEdge && isRhsEdge)
        {
            // Coincident operand edges. Parallel coincidence (both rings
            // traverse the edge with fills on the same side) keeps the kept
            // direction as a boundary of both Intersect and Union.
            // Anti-parallel coincidence (operands abut without overlapping)
            // contributes zero-area to either result and is dropped.
            if (sides.lhs < 2 && sides.rhs < 2 && sides.lhs == sides.rhs)
            {
                markKept(sides.lhs);
            }
            return;
        }

        // Non-coincident operand edge: the edge bounds exactly one operand.
        // Its "fill on left" half-edge has that operand's interior on its
        // left; the result includes this half-edge iff the predicate holds
        // for the left side relative to the OTHER operand.
        const uint8_t fillDir = isLhsEdge ? sides.lhs : sides.rhs;
        if (fillDir >= 2)
            return;

        const Edge::FlagsType otherFlag =
            isLhsEdge ? Edge::IsRhs : Edge::IsLhs;

        HalfEdgePtr he = e->getHalfEdge(fillDir);
        const Point2D &start = he->getStartNode()->getRealPosition();
        const Point2D &end   = he->getEndNode()->getRealPosition();
        const Point2D mid((start.getX() + end.getX()) * 0.5,
                          (start.getY() + end.getY()) * 0.5);

        const bool insideOther = isPointInsideOperand(mid, edges, otherFlag);

        const bool keep = (op == BooleanOpKind::Intersect) ? insideOther
                                                           : !insideOther;

        if (keep)
            markKept(fillDir);
    });

    // Stage D: keep edges with at least one half-edge marked OnResult; drop
    // the rest. EdgeTable::removeEdgesIf takes a "keep" predicate (despite
    // its name) - elements for which the predicate returns false are erased.
    edges.removeEdgesIf([](EdgePtr e) {
        return ((e->getHalfEdge(0)->getFlags() & OnResult) != 0) ||
               ((e->getHalfEdge(1)->getFlags() & OnResult) != 0);
    });

    // Stage E: trace the surviving subdivision into rings and lift to
    // ExplicitRings. traceRings classifies IsHole/IsCCW/IsConvex for the
    // result topology; we only strip the operand markers.
    RingCollection traced = traceRings(nodes, edges, /*hasBuddyEdges=*/false);

    ExplicitRingCollection out;
    out.reserve(traced.size());

    for (const Ring &r : traced)
    {
        ExplicitRing er(r);
        Ring::FlagsType f = er.getFlags();
        f &= ~(Ring::IsLhs | Ring::IsRhs);
        er.setFlags(f);
        out.push_back(std::move(er));
    }

    return out;
}

} // Anonymous namespace

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

//! @brief Uses rings marked as Lhs to clip rings marked as Rhs, returning the
//! intersection of the two operand regions as a collection of explicit rings.
//! @param[in] nodes The table of nodes which define the rings to process.
//! @param[in] edges The table of edges which define the rings to process.
//! @param[in] rings All Lhs and Rhs ring definitions.
//! @returns The boundary rings of Lhs ∩ Rhs.
//! @remarks
//! The nodes and edges are expected to have flag values which are sympathetic
//! with the initial ring definitions; this can be performed explicitly by
//! calling markBooleanOperands().
//!
//! The function adds nodes at intersections, splits edges accordingly, and
//! mutates @p edges to retain only the result-boundary subdivision. The ring
//! definitions are augmented with the new intersection nodes.
ExplicitRingCollection clip(NodeTable &nodes, EdgeTable &edges,
                            ExplicitRingCollection &rings)
{
    return booleanOp(nodes, edges, rings, BooleanOpKind::Intersect);
}


}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////
