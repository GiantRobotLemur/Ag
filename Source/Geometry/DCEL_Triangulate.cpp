//! @file Geometry/DCEL_Triangulate.cpp
//! @brief The definition of functions and structures needed to triangulate
//! convex and monotone polygons.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/Triangle2D.hpp"
#include "Ag/Geometry/DCEL.hpp"
#include "DCEL_Triangulate.hpp"

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
//! @brief Represents a node on a boundary chain of a monotone polygon being
//! decomposed into triangles.
class BoundaryEdgeNode
{
public:
    // Construction/Destruction
    BoundaryEdgeNode(NodeCPtr node, uint8_t majorIndex);
    ~BoundaryEdgeNode() = default;

    // Accessors
    constexpr bool isOnMaxSide() const noexcept { return _isOnMaxSide; }
    constexpr NodeCPtr getNode() const noexcept { return _node; }
    bool isLevelWith(const BoundaryEdgeNode &rhs) const;

    // Operations
    bool operator<(const BoundaryEdgeNode &rhs) const;
    void initialiseBoundary(uint32_t sequence, bool isOnMaxSide);
private:
    // Internal Fields
    NodeCPtr _node;
    uint32_t _sequence;
    uint8_t _majorIndex;
    bool _isOnMaxSide;
};

//! @brief An alias for a collection of boundary chain nodes.
using BoundaryEdgeCollection = std::vector<BoundaryEdgeNode>;

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// BoundaryEdgeNode members Definitions
////////////////////////////////////////////////////////////////////////////////
BoundaryEdgeNode::BoundaryEdgeNode(NodeCPtr node,
                                   uint8_t majorIndex) :
    _node(node),
    _sequence(0),
    _majorIndex(majorIndex & 1),
    _isOnMaxSide(false)
{
}

bool BoundaryEdgeNode::operator<(const BoundaryEdgeNode &rhs) const
{
    auto lhsComponents = _node->getGridPosition().toArray();
    auto rhsComponents = rhs._node->getGridPosition().toArray();

    const uint8_t minorIndex = _majorIndex ^ 1;

    if (lhsComponents[_majorIndex] == rhsComponents[_majorIndex])
    {
        // The points form a line parallel to the sweep.
        if (_isOnMaxSide == rhs._isOnMaxSide)
        {
            // They are on the same boundary chain, process them in sequence
            return _sequence < rhs._sequence;
        }
        else
        {
            return lhsComponents[minorIndex] < rhsComponents[minorIndex];
        }
    }
    else
    {
        return lhsComponents[_majorIndex] < rhsComponents[_majorIndex];
    }
}

bool BoundaryEdgeNode::isLevelWith(const BoundaryEdgeNode &rhs) const
{
    return (_node->getGridPosition().toArray()[_majorIndex] ==
            rhs._node->getGridPosition().toArray()[_majorIndex]);
}

void BoundaryEdgeNode::initialiseBoundary(uint32_t sequence, bool isOnMaxSide)
{
    _sequence = sequence;
    _isOnMaxSide = isOnMaxSide;
}


//! @brief Enumerates the nodes in a ring and which side they are on.
//! @param[in] ring The ring to enumerate.
//! @param[in] majorIndex 0 for a scan parallel to the X axis, 1 for
//! a scan parallel to the Y axis.
//! @return A collection of boundary nodes ordered ready for processing.
BoundaryEdgeCollection enumerateSideNodes(const Ring &ring, uint8_t majorIndex)
{
    BoundaryEdgeCollection orderedNodes;

    orderedNodes.reserve(ring.getNodeCount());

    HalfEdgeCPtr startEdge = ring.getFirstEdge();
    HalfEdgeCPtr currentEdge = startEdge;
    size_t minNodeIndex = 0;
    size_t maxNodeIndex = 0;
    const uint8_t safeMajorIndex = majorIndex & 1;
    const uint8_t safeMinorIndex = majorIndex ^ 1;

    do
    {
        size_t index = orderedNodes.size();
        NodePtr currentNode = currentEdge->getStartNode();

        if (!orderedNodes.empty())
        {
            // Update the minimum/maximum node indexes.
            auto currentComponents = currentNode->getGridPosition().toArray();
            auto minComponents = orderedNodes[minNodeIndex].getNode()->getGridPosition().toArray();
            auto maxComponents = orderedNodes[maxNodeIndex].getNode()->getGridPosition().toArray();

            // Properly sort nodes which are level by their minor component.
            if ((currentComponents[safeMajorIndex] < minComponents[safeMajorIndex]) ||
                ((currentComponents[safeMajorIndex] == minComponents[safeMajorIndex]) &&
                 (currentComponents[safeMinorIndex] < minComponents[safeMinorIndex])))
            {
                minNodeIndex = index;
            }

            if ((currentComponents[safeMajorIndex] > maxComponents[safeMajorIndex]) ||
                ((currentComponents[safeMajorIndex] == maxComponents[safeMajorIndex]) &&
                 (currentComponents[safeMinorIndex] > maxComponents[safeMinorIndex])))
            {
                maxNodeIndex = index;
            }
        }

        orderedNodes.emplace_back(currentEdge->getStartNode(), safeMajorIndex);

        // Move on to the next edge.
        currentEdge = currentEdge->getNextEdge();

    } while ((currentEdge != nullptr) && (currentEdge != startEdge));

    // Mark all the points on the greater X/Y chain as true.
    uint32_t sequence = 0;
    const bool isFirstCCWEdgeHigh = (majorIndex != 0);

    size_t i;
    for (i = minNodeIndex; i != maxNodeIndex; i = (i + 1) % orderedNodes.size())
    {
        orderedNodes[i].initialiseBoundary(sequence++, isFirstCCWEdgeHigh);
    }

    // Use a reverse sequence on the other chain.
    sequence = static_cast<uint32_t>(orderedNodes.size() + 1 - sequence);

    for (; i != minNodeIndex; i = (i + 1) % orderedNodes.size())
    {
        orderedNodes[i].initialiseBoundary(sequence--, !isFirstCCWEdgeHigh);
    }

    // Now sort the nodes by sweep position and, for the purposes
    // of edges parallel with the sweep, their sequence.
    std::sort(orderedNodes.begin(), orderedNodes.end());

    return orderedNodes;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Xxx Member Definitions
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a collection of CCW wound triangles from a monotone
//! or convex ring.
//! @param[in] ring The ring to triangulate.
//! @return A collection of triangle vertex indices, three for each triangle defined.
IDCollection triangulateRing(const Ring &ring)
{
    constexpr uint32_t HasIntermediateFlagNodes = Ring::HasIntermediateHorzNodes | Ring::HasIntermediateVertNodes;
    const uint32_t ringFlags = ring.getFlags();

    IDCollection indices;
    indices.reserve((ring.getNodeCount() - 2) * 3);

    if (((ringFlags & Ring::IsConvex) != 0) && ((ringFlags & HasIntermediateFlagNodes) == 0))
    {
        // Easy, pick the first point and create a triangle fan using it
        // as the point common to all.
        HalfEdgeCPtr startEdge = ring.getFirstEdge();
        HalfEdgeCPtr lastEdge = startEdge->getPreviousEdge();
        const Point2D &startPt = startEdge->getStartNode()->getRealPosition();
        ID rootPoint = startEdge->getStartNodeID();

        for (HalfEdgeCPtr currentEdge = startEdge->getNextEdge();
             currentEdge != lastEdge;
             currentEdge = currentEdge->getNextEdge())
        {
            LineSeg2D lowerEdge(startPt, currentEdge->getStartNode()->getRealPosition());
            double determinant = lowerEdge.getDeterminant(currentEdge->getEndNode()->getRealPosition());

            if (determinant < 0)
            {
                // The points are wound CW.
                indices.push_back(rootPoint);
                indices.push_back(currentEdge->getEndNodeID());
                indices.push_back(currentEdge->getStartNodeID());
            }
            else if (determinant > 0)
            {
                indices.push_back(rootPoint);
                indices.push_back(currentEdge->getStartNodeID());
                indices.push_back(currentEdge->getEndNodeID());
            }
            // else - if (determinant == 0) - It's  a line of points.
        }
    }
    else if (ringFlags & Ring::IsMonotone)
    {
        // The ring is X or Y monotone, enumerate the nodes and which sides of
        // the ring they are on True = Max X/Y, False = Min X/Y.
        BoundaryEdgeCollection orderedNodes;
        double detSign = 1.0;
        ID currentID, previousID, firstID;
        uint8_t minorComponentIndex = 0;

        if (ring.isXMonotone())
        {
            orderedNodes = enumerateSideNodes(ring, 0);
            detSign = -1.0;
            minorComponentIndex = 1;
        }
        else //if (ring.isYMonotone())
        {
            orderedNodes = enumerateSideNodes(ring, 1);
        }

        BoundaryEdgeCollection nodeStack;
        nodeStack.reserve(orderedNodes.size());

        // Stoke the initial stack.
        nodeStack.push_back(orderedNodes[0]);
        nodeStack.push_back(orderedNodes[1]);

        for (size_t i = 2; i < orderedNodes.size(); ++i)
        {
            const auto &current = orderedNodes[i];
            currentID = current.getNode()->getID();

            if (nodeStack.back().isOnMaxSide() == current.isOnMaxSide())
            {
                // The current and previous point are on the same side.
                auto previous = nodeStack.back();
                nodeStack.pop_back();
                previousID = previous.getNode()->getID();

                // Calculate a modification factor which takes into account
                // the sweep direction and edge we are working down in order
                // to determine if three points form a reflex angle or not.
                const double detMod = (current.isOnMaxSide() ? -1.0 : 1.0) * detSign;

                while (!nodeStack.empty())
                {
                    // Get the earliest point on the sweep triangle being formed
                    auto first = nodeStack.back();
                    firstID = first.getNode()->getID();

                    Triangle2D triangle(first.getNode()->getRealPosition(),
                                        previous.getNode()->getRealPosition(),
                                        current.getNode()->getRealPosition());

                    double determinant = triangle.getDeterminant();

                    if ((determinant * detMod) >= 0)
                    {
                        // We have three edges in a straight line or a
                        // reflex angle.
                        break;
                    }

                    // The angle is NOT reflexive, we can form a triangle.
                    nodeStack.pop_back();
                    indices.push_back(firstID);
                    const bool isCCW = (determinant > 0.0);

                    // Order the last two points depending on local winding
                    // to ensure the final triangle is wound CCW.
                    indices.push_back(isCCW ? previousID : currentID);
                    indices.push_back(isCCW ? currentID : previousID);

                    // Move on to the next triangle.
                    previous = first;
                    previousID = previous.getNode()->getID();
                }

                nodeStack.push_back(previous);
                nodeStack.push_back(current);
            }
            else
            {
                // The current vertex is on a different side to the last one.
                auto last = nodeStack.back();
                nodeStack.pop_back();
                auto previous = last;
                bool isWoundCCW = false;

                if (!nodeStack.empty())
                {
                    // Calculate how to wind all the triangles we are about
                    // to make.
                    Triangle2D triangle(nodeStack.back().getNode()->getRealPosition(),
                                        previous.getNode()->getRealPosition(),
                                        current.getNode()->getRealPosition());

                    isWoundCCW = triangle.isWoundCCW();
                }

                // Pop all vertices to make triangles.
                while (!nodeStack.empty())
                {
                    previousID = previous.getNode()->getID();
                    auto first = nodeStack.back();
                    nodeStack.pop_back();
                    firstID = first.getNode()->getID();

                    // Register a triangle which is wound CCW.
                    indices.push_back(firstID);
                    indices.push_back(isWoundCCW ? previousID : currentID);
                    indices.push_back(isWoundCCW ? currentID : previousID);

                    // Move on to the next triangle.
                    previous = first;
                }

                // Restore the new top edge of the unprocessed polygon.
                nodeStack.push_back(last);
                nodeStack.push_back(current);
            }
        }
    }
    else
    {
        throw OperationException("A ring cannot be triangulated if it isn't convex or strictly monotone.");
    }

    return indices;
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

