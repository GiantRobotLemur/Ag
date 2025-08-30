//! @file Geometry/DCEL_RingTracer.cpp
//! @brief The definition of internal structures and functions used to trace
//! a system of rings and holes from nodes and edges.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/DCEL_Algorithms.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"
#include "DCEL_RingTracer.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure used to recognise a ring, even if its nodes have been
//! reorientated
class RingValue
{
private:
    IDCollection _nodeIDs;
    size_t _hash;
    uint32_t _flags;

public:
    RingValue() : _hash(0) {}

    RingValue(const Ring &ring) :
        _nodeIDs(ring.getNodeIDs()),
        _hash(0)
    {
        // Calculate the sorted set of nodes in the ring.
        std::sort(_nodeIDs.begin(), _nodeIDs.end());

        // Hash the nodes in sorted order.
        constexpr int HashShift = 5;

        for (ID id : _nodeIDs)
        {
            _hash = Ag::Bin::rotateLeft(_hash, HashShift) ^ id;
        }
    }

    size_t getHash() const { return _hash; }

    bool operator==(const RingValue &rhs) const
    {
        if ((_hash != rhs._hash) ||
            (_nodeIDs.size() != rhs._nodeIDs.size()))
            return false;

        return std::equal(_nodeIDs.begin(), _nodeIDs.end(), rhs._nodeIDs.begin());
    }
};

//! @brief A hash function for RingValue objects.
struct RingValueHash
{
    size_t operator()(const RingValue &rhs) const
    {
        return rhs.getHash();
    }
};

//! @brief An alias for a hash set of RingValue objects.
using RingValueSet = std::unordered_set<RingValue, RingValueHash>;


//! @brief An operator which generates rings from initial edge.
class TraceRings
{
private:
    IDCollection _ringIDsToReplace;
    size_t _replacedIDs;
    NodeTable &_nodes;
    EdgeTable &_edges;
    RingCollection &_rings;
    bool _ignoreCW;

    //! @brief Creates one or more rings from an ordered set of directed edges.
    //! @param[in] source The edges forming the ring.
    //! @note Any loops in the ring will be broken out into separate rings.
    void addRings(HalfEdgePtrCollection &source)
    {
        std::set<ID> visitedNodes;
        bool canCreateRing = false;

        // Keep trying to work around the ring until we create one without
        // any duplicate nodes.
        while (!canCreateRing)
        {
            visitedNodes.clear();

            // Assume we can create a ring with no duplicate nodes until we
            // know otherwise.
            canCreateRing = true;

            // Iterate through the edges looking for duplicate nodes - indicating a loop.
            for (auto edgePos = source.begin(); canCreateRing && (edgePos != source.end()); )
            {
                HalfEdgePtr currentEdge = *edgePos;
                ID endNodeID = currentEdge->getEndNodeID();

                if (visitedNodes.find(endNodeID) == visitedNodes.end())
                {
                    visitedNodes.insert(endNodeID);
                    ++edgePos;
                }
                else
                {
                    // We've detected a loop, make a ring from the loop edges,
                    // remove them and try again.
                    auto loopPos = edgePos;
                    auto loopEnd = edgePos;
                    ++loopEnd;

                    // Find the first edge in the loop.
                    for (--loopPos; (*loopPos)->getStartNodeID() != endNodeID; --loopPos)
                    {
                        ;
                    }

                    size_t loopSize = std::distance(loopPos, loopEnd);

                    if (loopSize > 2)
                    {
                        // Create a ring from the loop edges.
                        createRing(loopPos, loopEnd);
                    }
                    else
                    {
                        // Reset the edges so that they could appear in another ring.
                        for (auto pos = loopPos; pos != loopEnd; ++pos)
                        {
                            (*pos)->setRingID(NullID);
                        }
                    }

                    // Remove the loop edges.
                    edgePos = source.erase(loopPos, loopEnd);

                    // Start again with the main ring.
                    canCreateRing = false;
                }
            }

            // Ensure we have at least 3 unique nodes before trying
            // to create a ring.
            if (canCreateRing && (visitedNodes.size() > 2))
            {
                createRing(source.begin(), source.end());
            }
        }
    }

    //! @brief Updates ring flags based on whether a node is an intermediate on
    //! a horizontal or vertical line.
    //! @param[in,out] flags The ring flags to update.
    //! @param[in] prevNode The previous node on the ring boundary.
    //! @param[in] currentNode The current node on the ring boundary.
    //! @param[in] nextNode The next node on the ring boundary.
    static void updateNodeFlags(uint32_t &flags, NodeCPtr prevNode,
                                NodeCPtr currentNode, NodeCPtr nextNode)
    {
        const SnapPoint &currentPos = currentNode->getGridPosition();

        SnapPoint prevDelta = prevNode->getGridPosition() - currentPos;
        SnapPoint nextDelta = currentPos - nextNode->getGridPosition();

        if ((prevDelta.getX() == 0) && (nextDelta.getX() == 0))
        {
            flags |= Ring::HasIntermediateHorzNodes;
        }

        if ((prevDelta.getY() == 0) && (nextDelta.getY() == 0))
        {
            flags |= Ring::HasIntermediateVertNodes;
        }
    }

    //! @brief Creates a single ring from an ordered set of directed edges.
    //! @param beginEdge The position of the first edge in the ring.
    //! @param endEdge The position after the last edge in the ring.
    //! @details A new ring is added to the collection and winding, convexity,
    //! and monotone properties are all calculated for it.
    void createRing(HalfEdgePtrCollection::iterator beginEdge,
                    HalfEdgePtrCollection::iterator endEdge)
    {
        // Calculate the statistics of the ring from its edges.
        const Point2D &basePoint = (*beginEdge)->getStartNode()->getRealPosition();
        uint32_t edgeCount = 0;
        uint32_t nodeFlags = 0;
        double totalArea = 0.0;
        ID ringID = static_cast<ID>(_rings.size());
        int offsetSign = 0;
        bool isConvex = true;

        // Re-use an old ID if we are replacing rings.
        bool reusedID = false;

        if (_replacedIDs < _ringIDsToReplace.size())
        {
            ringID = _ringIDsToReplace[_replacedIDs++];
            reusedID = true;
        }

        // Calculate winding and convexity from ring edges.
        HalfEdgePtr lastEdge = *(endEdge - 1);
        HalfEdgePtr currentEdge = lastEdge;
        HalfEdgePtr leftMostEdge = lastEdge;
        Point2D prevPt = currentEdge->getStartNode()->getRealPosition() - basePoint;

        // Ensure the ring is closed.
        (*beginEdge)->linkEdges(lastEdge);

        // Go through the edges linking them and calculating overall
        // area and convexity.
        for (auto edgePos = beginEdge; edgePos != endEdge; ++edgePos)
        {
            HalfEdgePtr successorEdge = *edgePos;
            NodeCPtr nextNode = successorEdge->getStartNode();
            Point2D nextPoint = nextNode->getRealPosition() - basePoint;

            totalArea += (prevPt.getX() - nextPoint.getX()) * (prevPt.getY() + nextPoint.getY());
            prevPt = nextPoint;

            // Update node flags to determine if a broken horizontal or vertical edge is included.
            updateNodeFlags(nodeFlags, currentEdge->getStartNode(),
                            nextNode, successorEdge->getEndNode());

            // Find the edge starting at the minimum X nodes.
            if (nextNode->getGridPosition().lessThanXMajor(leftMostEdge->getStartNode()->getGridPosition()))
            {
                leftMostEdge = successorEdge;
            }

            // Calculate the relative angle between the two edges to determine
            // whether the ring is convex/concave.
            if (isConvex)
            {
                double offsetAngle = currentEdge->getAngle().getOffsetTo(successorEdge->getAngle());

                if (Angle::Domain.isNearZero(offsetAngle) == false)
                {
                    // The angle is great enough to be significant.
                    int successorSign = (offsetAngle < 0.0) ? -1 : 1;

                    if (offsetSign == 0)
                    {
                        // Set the expected winding direction for the polygon.
                        offsetSign = successorSign;
                    }
                    else if (offsetSign != successorSign)
                    {
                        // The initial winding direction wasn't honoured, the
                        // polygon is concave.
                        isConvex = false;
                    }
                }
            }

            currentEdge->linkEdges(successorEdge);
            successorEdge->setRingID(ringID);
            currentEdge = successorEdge;
            ++edgeCount;
        }

        // Trivially reject CW wound rings.
        if (_ignoreCW && (totalArea < 0.0))
        {
            if (reusedID)
                --_replacedIDs;

            // Un-assign the edges, but don't process them again as
            // the edge at the beginning or a ring.
            for (auto edgePos = beginEdge; edgePos != endEdge; ++edgePos)
                (*edgePos)->setRingID(VisitedID);

            return;
        }

        // Set assume the ring is X and Y monotone until proven otherwise.
        uint32_t ringFlags = Ring::IsXMonotone | Ring::IsYMonotone;

        if (isConvex == false)
        {
            // Determine if the rings is X and or Y monotone.
            currentEdge = leftMostEdge;
            NodeCPtr prevNode = currentEdge->getPreviousEdge()->getStartNode();
            uint32_t classFlags = (totalArea > 0.0) ? Ring::IsCCW : 0u;

            do
            {
                NodeCPtr currentNode = currentEdge->getStartNode();
                NodeCPtr nextNode = currentEdge->getEndNode();

                // TODO: These classifications produce Split/Merge vertices
                // when edges perpendicular to the sweep direction are
                // encountered. I guess that detects strict-monotone polygons,
                // but is that useful?

                if (ringFlags & Ring::IsXMonotone)
                {
                    // Determine if the ring is still X-monotone.
                    uint32_t vertexClass = classifyXMonotonePoint(classFlags,
                                                                  prevNode,
                                                                  currentNode,
                                                                  nextNode);

                    Bin::updateMask(ringFlags, Ring::IsXMonotone,
                                    (vertexClass != SplitVertex) && (vertexClass != MergeVertex));
                }

                if (ringFlags & Ring::IsYMonotone)
                {
                    // Determine if the ring is still Y-monotone.
                    uint32_t vertexClass = classifyYMonotonePoint(classFlags,
                                                                  prevNode,
                                                                  currentNode,
                                                                  nextNode);

                    Bin::updateMask(ringFlags, Ring::IsYMonotone,
                                    (vertexClass != SplitVertex) && (vertexClass != MergeVertex));
                }

                // Move on to the next edge.
                currentEdge = currentEdge->getNextEdge();
                prevNode = currentNode;
            } while ((ringFlags != 0) && (currentEdge != leftMostEdge));
        }

        // Merge in the node-specific flags.
        ringFlags |= nodeFlags;

        Bin::updateMask(ringFlags, Ring::IsConvex, isConvex);
        Bin::updateMask(ringFlags, Ring::IsCCW, totalArea > 0.0);

        if (ringID < _rings.size())
        {
            // Replace a ring in the collection.
            _rings[ringID] = Ring(ringID, leftMostEdge, edgeCount, ringFlags);
        }
        else
        {
            // Add a new ring to the collection.
            _rings.emplace_back(ringID, leftMostEdge, edgeCount, ringFlags);
        }
    }

    //! @brief Attempts to trace one or more rings stating from a specified edge.
    //! @param[in] startEdge The first directed edge on the potential ring.
    //! @param[in] ringEdges A collection used to hold the set of edges in
    //! the ring being enumerated.
    //! @retval true At least one set of edges was found which created a
    //! close ring.
    //! @retval false The edges enumerated from @p startEdge did not
    //! create a ring. The affected edges have been assigned to a ring VisitedID.
    bool traceRing(HalfEdgePtr startEdge, HalfEdgePtrCollection &ringEdges)
    {
        HalfEdgePtr currentEdge = startEdge;

        ringEdges.clear();
        ringEdges.push_back(startEdge);
        startEdge->setRingID(VisitedID);

        while (currentEdge != nullptr)
        {
            HalfEdgePtr successorEdge = nullptr;

            // Go through all of the edges which are incident at the joint to
            // find a suitable successor.
            Angle rootAngle = currentEdge->getAngle();
            double bestOffset = 0.0;
            ID currentNodeID = currentEdge->getEndNodeID();

            auto edgeMappingIterPair = _edges.rangeOfEdgesAtNode(currentNodeID);

            for (const auto &mappingPos : edgeMappingIterPair)
            {
                EdgePtr edge = mappingPos.second;

                HalfEdgePtr directedEdge = edge->getHalfEdgeFrom(currentNodeID);

                if (directedEdge == startEdge)
                {
                    // We have returned to the start edge, always take that
                    // over another edge.
                    successorEdge = directedEdge;
                    break;
                }

                if (directedEdge->getRingID() != NullID)
                {
                    // The edge has already been assigned to a ring, don't
                    // overwrite it.
                    continue;
                }

                double angularOffset = 0.0;

                if (edge == currentEdge->getParent())
                {
                    // Allow the return edge, but as the worst possible choice
                    // of successor.
                    angularOffset = -Angle::Pi2;
                }
                else
                {
                    angularOffset = rootAngle.getOffsetTo(directedEdge->getAngle());
                }

                // Calculate the angle of the new edge relative to the old.
                if ((successorEdge == nullptr) || (angularOffset > bestOffset))
                {
                    // We've found a first successor edge or a better one.
                    successorEdge = directedEdge;
                    bestOffset = angularOffset;
                }
            }

            if (successorEdge == nullptr)
            {
                // There is no successor edge.
                currentEdge = nullptr;
            }
            else
            {
                // Mark the edge as visited so that it isn't re-used.
                successorEdge->setRingID(VisitedID);

                // Move on to the next edge.
                currentEdge = successorEdge;

                // Stop when we've performed a full loop.
                if (currentEdge == startEdge)
                {
                    break;
                }
                else
                {
                    ringEdges.push_back(currentEdge);
                }
            }
        }

        return currentEdge == startEdge;
    }

public:
    TraceRings(NodeTable &nodes, EdgeTable &edges, RingCollection &rings, bool ignoreCW = false) :
        _replacedIDs(0),
        _nodes(nodes),
        _edges(edges),
        _rings(rings),
        _ignoreCW(ignoreCW)
    {
    }

    TraceRings(NodeTable &nodes, EdgeTable &edges, RingCollection &rings,
               const std::set<ID> &affectedRingIDs) :
        _replacedIDs(0),
        _nodes(nodes),
        _edges(edges),
        _rings(rings),
        _ignoreCW(false)
    {
        _ringIDsToReplace.reserve(affectedRingIDs.size());

        std::copy(affectedRingIDs.begin(), affectedRingIDs.end(),
                  std::back_inserter(_ringIDsToReplace));
    }

    void operator()(Edge *edge)
    {
        HalfEdgePtrCollection ringEdges;
        ringEdges.reserve(32);

        // Enumerate the two directed edges within the edge.
        for (DirectionIndex d = 0; d < 2; ++d)
        {
            HalfEdgePtr directedEdge = edge->getHalfEdge(d);

            if (directedEdge->getRingID() != NullID)
                continue;

            if (traceRing(directedEdge, ringEdges))
            {
                addRings(ringEdges);
            }
        }
    }

    void operator()(HalfEdgePtr directedEdge)
    {
        HalfEdgePtrCollection ringEdges;
        ringEdges.reserve(32);

        if (directedEdge->getRingID() != NullID)
            return;

        if (traceRing(directedEdge, ringEdges))
        {
            addRings(ringEdges);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if a directed edge travels into a vertical sweep.
//! @param[in] edge The edge to test.
//! @retval true The end of the edge is higher than the start node.
//! @retval false The end node is lower than the start.
bool isEdgeGoingDown(HalfEdgeCPtr edge)
{
    const SnapPoint &start = edge->getStartNode()->getGridPosition();
    const SnapPoint &end = edge->getEndNode()->getGridPosition();

    return start.lessThanSweep(end);
}

//! @brief Determines if an edge incident at a node is assigned to a specific
//! ring.
//! @param[in] edges The index of all edges in the system.
//! @param[in] nodeID The identifier of the node to query.
//! @param[in] ringID The identifier of the ring to detect.
//! @retval true The node defined by @p nodeID forms part of the boundary of
//! the ring identified by @p ringID.
//! @retval false The specified node is not part of the specified ring.
bool isNodeOnRing(const EdgeTable &edges, ID nodeID, ID ringID)
{
    for (const auto &mapping : edges.rangeOfEdgesAtNode(nodeID))
    {
        for (DirectionIndex i = 0; i < 2; ++i)
        {
            HalfEdgeCPtr directedEdge = mapping.second->getHalfEdge(i);

            if (directedEdge->getRingID() == ringID)
                return true;
        }
    }

    return false;
}

//! @brief Creates a mapping of parent CCW ring IDs to child CW ring IDs based
//! on a collection of rings.
//! @param[in] edges The index of all edges in the system.
//! @param[in] rings The collection of rings used to derive the mapping.
//! @return A sorted non-unique mapping of parent ring ID to child ring IDs.
SortedIDToIDMap connectRings(const EdgeTable &edges, RingCollection &rings)
{
    for (Ring &ring : rings)
    {
        ring.setParentRingID(VisitedID);
    }

    // Connect all rings
    for (Ring &ring : rings)
    {
        NodePtr leftMostNode = ring.getFirstEdge()->getStartNode();
        EdgePtr edgeLeftOfRing = leftMostNode->getBuddyEdge();

        if (edgeLeftOfRing == nullptr)
        {
            // Its the ring which bounds the outer-most region to fill.
            ring.setParentRingID(NullID);

            continue;
        }

        // Analyse the edge left of the current ring.
        bool isAssignedToParent = false;

        for (DirectionIndex direction = 0; direction < 2; ++direction)
        {
            HalfEdgePtr directedEdgeOnLeft = edgeLeftOfRing->getHalfEdge(direction);
            ID connectedRingID = directedEdgeOnLeft->getRingID();

            // Check to see if the ring has no neighbour to the left.
            if (connectedRingID >= rings.size())
                continue;

            const Ring &ringOnLeft = rings[connectedRingID];

            // See if the left-most corner is shared between siblings.
            if (isNodeOnRing(edges, leftMostNode->getID(), connectedRingID))
            {
                if (!isAssignedToParent &&
                    (ringOnLeft.isCCW() == ring.isCCW()))
                {
                    // The left most node on the current ring/hole is on the
                    // neighbouring ring/hole, therefore they are siblings.
                    ring.setParentRingID(connectedRingID);
                }

                // If the rings share the node, but are different orientations
                // they can't be related, so don't bother checking.
                continue;
            }

            uint8_t decisionBits = 0;
            Bin::updateBit(decisionBits, 0, ringOnLeft.isCCW());
            Bin::updateBit(decisionBits, 1, isEdgeGoingDown(directedEdgeOnLeft));
            Bin::updateBit(decisionBits, 2, ring.isCCW());

            static const bool decisionMatrix[] = {
                false,  // Left CW, left edge going up, right CW - nested holes?
                false,  // Left CCW, left edge going up, right CW - fill left of hole?
                true,   // Left CW, left edge going down, right CW - sibling holes
                true,   // Left CCW, left edge going down, right CW - left is parent ring

                true,   // Left CW, left edge going up, right CCW - left is parent hole
                true,   // Left CCW, left edge going up, right CCW - sibling ring
                false,  // Left CW, left edge going down, right CCW - hole left of ring?
                false,  // Left CCW, left edge going down, right CCW - nested rings?
            };

            const bool couldConnect = decisionMatrix[decisionBits];

            // A connection between hole and filled ring takes priority over a
            // sibling connection between holes.
            if (couldConnect && !isAssignedToParent)
            {
                // The edge belongs to either a sibling or a parent.
                ring.setParentRingID(connectedRingID);
                isAssignedToParent = ringOnLeft.isCCW() != ring.isCCW();
            }
        }
    }

    // Compile the sibling connections into parent connections.
    SortedIDToIDMap ringIDByParentID;
    ringIDByParentID.reserve(rings.size());

    for (Ring &ring : rings)
    {
        ID parentID = ring.getParentRingID();
        const bool isCCW = ring.isCCW() ^ ring.isSurrounding();

        // Work along the chain of siblings until we find a parent.
        while ((parentID < rings.size()) &&
               ((rings[parentID].isCCW() ^ rings[parentID].isSurrounding()) == isCCW))
        {
            parentID = rings[parentID].getParentRingID();
        }

        // Assign the parent of the current ring.
        ring.setParentRingID(parentID);

        // Add to the index.
        ringIDByParentID.push_back(parentID, ring.getID());
    }

    ringIDByParentID.reindex();

    return ringIDByParentID;
}


//! @brief Creates a mapping of filled rings and the holes they contain.
//! @param[in] edges The index of all edges in the system.
//! @param[in] rings The collection of CCW rings where  used to derive the mapping.
//! @return A sorted non-unique mapping of parent ring ID to child ring IDs.
SortedIDToIDMap connectCCWRings(const EdgeTable &edges, RingCollection &rings)
{
    for (Ring &ring : rings)
    {
        ring.setParentRingID(VisitedID);
    }

    // Connect all rings
    for (Ring &ring : rings)
    {
        NodePtr leftMostNode = ring.getFirstEdge()->getStartNode();
        EdgePtr edgeLeftOfRing = leftMostNode->getBuddyEdge();

        if (edgeLeftOfRing == nullptr)
        {
            // Its the ring which bounds the outer-most region to fill.
            ring.setParentRingID(NullID);

            continue;
        }

        // Analyse the edge left of the current ring.
        bool isAssignedToParent = false;

        for (DirectionIndex direction = 0; direction < 2; ++direction)
        {
            HalfEdgePtr directedEdgeOnLeft = edgeLeftOfRing->getHalfEdge(direction);
            ID connectedRingID = directedEdgeOnLeft->getRingID();

            // Check to see if the ring has no neighbour to the left.
            if ((connectedRingID >= rings.size()) ||
                (connectedRingID == ring.getID()))
                continue;

            const Ring &ringOnLeft = rings[connectedRingID];

            // See if the left-most corner is shared between siblings.
            if (isNodeOnRing(edges, leftMostNode->getID(), connectedRingID))
            {
                if (!isAssignedToParent &&
                    (ringOnLeft.isHole() == ring.isHole()))
                {
                    // The left most node on the current ring/hole is on the
                    // neighbouring ring/hole, therefore they are siblings.
                    ring.setParentRingID(connectedRingID);
                }

                // If the rings share the node, but are different orientations
                // they can't be related, so don't bother checking.
                continue;
            }

            const bool couldConnect = isEdgeGoingDown(directedEdgeOnLeft);

            // A connection between hole and filled ring takes priority over a
            // sibling connection between holes.
            if (couldConnect && !isAssignedToParent)
            {
                // The edge belongs to either a sibling or a parent.
                ring.setParentRingID(connectedRingID);
                isAssignedToParent = ringOnLeft.isHole() != ring.isHole();
            }
        }
    }

    // Compile the sibling connections into parent connections.
    SortedIDToIDMap ringIDByParentID;
    ringIDByParentID.reserve(rings.size());

    for (Ring &ring : rings)
    {
        ID parentID = ring.getParentRingID();
        const bool isHole = ring.isHole();

        // Work along the chain of siblings until we find a parent.
        while ((parentID < rings.size()) &&
               (rings[parentID].isHole() == isHole))
        {
            parentID = rings[parentID].getParentRingID();
        }

        // Assign the parent of the current ring.
        ring.setParentRingID(parentID);

        if (ring.isHole())
        {
            // Add the hole to the index.
            ringIDByParentID.push_back(parentID, ring.getID());
        }
    }

    ringIDByParentID.reindex();

    return ringIDByParentID;
}

//! @brief Recursively populates a collection of effective rings starting
//! with the outer-most and working inwards.
//! @param[in] originalRings The collection of all rings, CCW and CW for
//! all cycles.
//! @param[in] ringIDsByParentID The mapping of the IDs of original rings
//! indexed by the ID of their parent.
//! @param[out] effectiveRings The collection of effective rings to populate.
//! @param[in] surroundingRingID The identifier of the original ring/hole to enumerate
//! child holes/rings of.
//! @param[in] parentEffectiveRingID The identifier of the effective ring/hole
//! which corresponds to @p surroundingRingID.
//! @retval true Effective child holes/rings were added.
//! @retval false The parent ring/hole had no children.
bool enumerateEffectiveRings(const RingCollection &originalRings,
                             const SortedIDToIDMap &ringIDsByParentID,
                             SortedIDSet &visitedRingIDs,
                             RingCollection &effectiveRings,
                             ID surroundingRingID,
                             ID parentEffectiveRingID)
{
    if (surroundingRingID >= originalRings.size())
        return false;

    std::deque<ID> ringsToVisit;
    bool hasChildren = false;

    const Ring &surroundingRing = originalRings[surroundingRingID];
    bool isSearchingForCCW = surroundingRing.isCCW() == false;

    HalfEdgePtr startEdge = surroundingRing.getFirstEdge();
    HalfEdgePtr currentEdge = startEdge;

    do
    {
        ID otherRingID = currentEdge->getReverse()->getRingID();

        if ((otherRingID < originalRings.size()) &&
            (originalRings[otherRingID].isCCW() == isSearchingForCCW) &&
            (visitedRingIDs.find(otherRingID) == visitedRingIDs.end()))
        {
            // This is a ring worth enumerating.
            visitedRingIDs.insert(otherRingID);
            ringsToVisit.push_back(otherRingID);
        }

        // Move on to the next surrounding edge.
        currentEdge = currentEdge->getNextEdge();
    } while (currentEdge != startEdge);

    while (ringsToVisit.empty() == false)
    {
        const Ring &originalChildRing = originalRings[ringsToVisit.front()];
        ringsToVisit.pop_front();

        // Determine if this ring is connected to the parent at all.
        startEdge = originalChildRing.getFirstEdge();
        currentEdge = startEdge;

        bool isConnectedToOuterRing = false;
        do
        {
            isConnectedToOuterRing = (currentEdge->getReverse()->getRingID() == surroundingRingID);

            // Move on to the next edge.
            currentEdge = currentEdge->getNextEdge();
        } while ((isConnectedToOuterRing == false) &&
                 (currentEdge != nullptr) &&
                 (currentEdge != startEdge));

        if (isConnectedToOuterRing == false)
        {
            // originalChildRing is surrounded by other rings connected to
            // the parent ring, possibly a hole which was originally defined
            // but became merely surrounded by filled rings after a monotone
            // sweep.

            // Check of child rings for which we can enumerate inner children
            for (const auto &grandChildMapping : ringIDsByParentID.findRange(originalChildRing.getID()))
            {
                ID grandChildRingID = grandChildMapping.second;

                if ((grandChildMapping.second >= originalRings.size()) ||
                    (originalRings[grandChildRingID].isCCW() != isSearchingForCCW) ||
                    (visitedRingIDs.find(grandChildRingID) != visitedRingIDs.end()))
                    continue;

                // We've found a ring surrounding possible children
                visitedRingIDs.insert(grandChildRingID);

                hasChildren |= enumerateEffectiveRings(originalRings,
                                                       ringIDsByParentID,
                                                       visitedRingIDs,
                                                       effectiveRings,
                                                       grandChildRingID,
                                                       parentEffectiveRingID);
            }


            // TODO: What about odd/even filling?
        }

        // Create a new effective ring representing the ring/hole we found
        // within the parent hole/ring.
        ID effectiveRingID = static_cast<ID>(effectiveRings.size());

        effectiveRings.emplace_back(effectiveRingID,
                                    originalChildRing.getFirstEdge(),
                                    originalChildRing.getNodeCount(),
                                    originalChildRing.getFlags());

        // Note the parent ring has at least one child.
        hasChildren = true;

        bool hasGrandchildren = false;

        for (const auto &grandChildMapping : ringIDsByParentID.findRange(originalChildRing.getID()))
        {
            if ((grandChildMapping.second >= originalRings.size()) ||
                (originalRings[grandChildMapping.second].isCCW() == originalChildRing.isCCW()))
                continue;

            // Go around the grandchild ring looking at reverse edges to find
            // a ring which will surround all grandchildren.
            startEdge = originalRings[grandChildMapping.second].getFirstEdge();
            currentEdge = startEdge;

            do
            {
                ID otherRingID = currentEdge->getReverse()->getRingID();

                if ((otherRingID < originalRings.size()) &&
                    (originalRings[otherRingID].isCCW() == originalChildRing.isCCW()) &&
                    (visitedRingIDs.find(otherRingID) == visitedRingIDs.end()))
                {
                    // We've found a surrounding ring.
                    visitedRingIDs.insert(otherRingID);

                    hasGrandchildren |= enumerateEffectiveRings(originalRings,
                                                                ringIDsByParentID,
                                                                visitedRingIDs,
                                                                effectiveRings,
                                                                otherRingID,
                                                                effectiveRingID);
                }

                // Move on to the next edge.
                currentEdge = currentEdge->getNextEdge();
            } while ((currentEdge != nullptr) &&
                     (currentEdge != startEdge));
        }

        // Update information on the effective ring.
        Ring &effectiveRing = effectiveRings[effectiveRingID];

        effectiveRing.setParentRingID(parentEffectiveRingID);
        uint32_t flags = effectiveRing.getFlags();

        Bin::updateMask(flags, Ring::IsHole, originalChildRing.isCCW() == false);
        Bin::updateMask(flags, Ring::HasChildren, hasGrandchildren);

        effectiveRing.setFlags(flags);
    }

    return hasChildren;
}

//! @brief Calculates a set of rings and holes from a set of rings where the
//! same area might be outlined both CCW and CW.
//! @param[in] rings The original set of rings to resolved.
//! @param[in] ringIDsByParentID A mapping of parent ring IDs to ring IDs
//! which references the @p rings collection.
//! @return A new set of rings where no outline is duplicated.
RingCollection enumerateValidRings(const RingCollection &rings,
                                   const SortedIDToIDMap &ringIDsByParentID)
{
    // Find all rings with no parent.
    RingCollection effectiveRings;
    effectiveRings.reserve((rings.size() / 2) + 1);

    // Enumerate the top-level holes, each of which will wholly surround
    // one or more top-level filled rings.
    SortedIDSet visitedRingIDs;

    for (const auto &mapping : ringIDsByParentID.findRange(NullID))
    {
        const Ring &childRing = rings[mapping.second];

        if (childRing.isCCW() == false)
        {
            // Enumerate the top-level rings, then their holes, etc.
            enumerateEffectiveRings(rings, ringIDsByParentID, visitedRingIDs,
                                    effectiveRings, childRing.getID(), NullID);
        }
    }

    return effectiveRings;
}

//! @brief Resets the IDs of rings assigned to edges, marking some as unassigned.
//! @param[in] edges The table of all edges in the mesh.
//! @param[in] rings The set of rings to traverse in order to assign ring IDs
//! to directed edges in @p edges.
void resetRingEdgeIDs(EdgeTable &edges, RingCollection &rings)
{
    // Reset the ID of the ring associated with every directed edge.
    edges.applyToAllEdges([](Edge *edge)
                          { edge->getHalfEdge(0)->setRingID(NullID);
    edge->getHalfEdge(1)->setRingID(NullID);
                          });

    for (Ring &ring : rings)
    {
        HalfEdgePtr startEdge = ring.getFirstEdge();
        HalfEdgePtr currentEdge = startEdge;

        // Iterate over the connected edges assigning them to the
        // parent ring.
        do
        {
            currentEdge->setRingID(ring.getID());

            // Move on to the next edge.
            currentEdge = currentEdge->getNextEdge();
        } while (currentEdge != startEdge);
    }
}


} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Xxx Member Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief (Re)assigns all edges belonging to closed rings and identifier.
//! @param[in] nodes The table of nodes to annotate with edges to their left.
//! @param[in] edges The table of edges to annotate with ring IDs.
//! @param[in] hasBuddyEdges Indicates whether the nodes of the mesh have already
//! been annotated with the edges immediately to their left, perhaps by an
//! intersection sweep or Y-monotone sweep.
//! @returns A collection of rings created from the edges.
RingCollection traceRings(NodeTable &nodes, EdgeTable &edges,
                          bool hasBuddyEdges /*= false*/)
{
    // Disconnect all edges and remove associations with any rings.
    edges.resetConnections();

    RingCollection rings;
    TraceRings ringTracer(nodes, edges, rings);

    // Process all edges to ensure every possible ring is resolved,
    // i.e. traversing both CW and CCW potentially around the same area.
    edges.forEachEdge(ringTracer);

    if (hasBuddyEdges == false)
    {
        // Annotate each node with the edge immediately to its left.
        assignEdgesLeftOfNodes(nodes, edges);
    }

    for (Ring &ring : rings)
    {
        // Determine if the ring doesn't share an edge with an
        // alternately wound ring, i.e. a set of rings all
        // bordering an area making a de-facto hole.
        HalfEdgeCPtr startEdge = ring.getFirstEdge();
        HalfEdgeCPtr currentEdge = startEdge;

        bool hasOpposingRing = false;
        bool isCCW = ring.isCCW();

        do
        {
            ID opposingRingID = currentEdge->getReverse()->getRingID();

            hasOpposingRing = (opposingRingID < rings.size()) &&
                (rings[opposingRingID].isCCW() != isCCW);

            // Move on to the next edge.
            currentEdge = currentEdge->getNextEdge();
        } while (!hasOpposingRing && (currentEdge != startEdge));

        uint32_t flags = ring.getFlags();
        Bin::updateMask(flags, Ring::IsSurrounding, !hasOpposingRing);
        ring.setFlags(flags);
    }

    // Determine parentage by scanning connected rings and
    // using the edge on the left to link child systems of filled
    // rings to parent holes.
    SortedIDToIDMap ringsByParent = connectRings(edges, rings);

    // From the set of all rings, use the parentage to establish which
    // filled rings and holes are valid.
    RingCollection ringsAndHoles = enumerateValidRings(rings, ringsByParent);

    // Reset Ring IDs on half edge and re-assign.
    resetRingEdgeIDs(edges, ringsAndHoles);

    return ringsAndHoles;
}

//! @brief Creates a set of rings from nodes and edges which have been partitioned
//! so that all filled areas are y-monotone.
//! @param[in] nodes The table of nodes to annotate with edges to their left.
//! @param[in] edges The table of edges to annotate with ring IDs
//! @param[in,out] rings The original collection of rings and holes to be updated
//! with new rings, but with the holes preserved.
//! @return A mapping of filled ring IDs to the IDs of remaining holes.
//! @remarks It is assumed that nodes have been annotated with edges
//! immediately to their left.
SortedIDToIDMap findPartitionedRings(NodeTable &nodes, EdgeTable &edges,
                                     RingCollection &rings)
{
    // Gather the nodes involved in each hole so that they can be recognised,
    // albeit possibly with a different winding, once new rings have been
    // created.
    RingValueSet holeSignatures;
    uint32_t minHoleNodes = std::numeric_limits<uint32_t>::max();
    uint32_t maxHoleNodes = 0;

    for (auto &ring : rings)
    {
        if (ring.isHole() == false)
            continue;

        // Set up trivial rejection when matching holes.
        minHoleNodes = std::min(minHoleNodes, ring.getNodeCount());
        maxHoleNodes = std::max(maxHoleNodes, ring.getNodeCount());

        holeSignatures.emplace(ring);
    }

    // Disconnect all edges and remove associations with any rings.
    edges.resetConnections();
    rings.clear();

    TraceRings ringTracer(nodes, edges, rings, /* ignoreCW = */ true);

    // Process all edges to ensure every possible ring is resolved,
    // but ignoring any CW rings.
    edges.forEachEdge(ringTracer);

    if (!holeSignatures.empty())
    {
        // Rediscover any holes which persisted.
        for (auto &ring : rings)
        {
            uint32_t ringSize = ring.getNodeCount();

            if ((ringSize < minHoleNodes) || (ringSize > maxHoleNodes))
                continue;

            RingValue ringSignature(ring);

            auto pos = holeSignatures.find(ringSignature);

            if (pos != holeSignatures.end())
            {
                ring.setFlags(ring.getFlags() | Ring::IsHole);
            }
        }

        // Determine parentage by scanning connected rings and
        // using the edge on the left to link child systems of filled
        // rings to parent holes.
        return connectCCWRings(edges, rings);
    }

    return { };
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

