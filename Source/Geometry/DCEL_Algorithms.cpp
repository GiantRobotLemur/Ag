//! @file Geometry/DCEL_Algorithms.cpp
//! @brief The definition of various algorithms which operate on a Doubly
//! Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <optional>
#include <iterator>
#include <map>
#include <set>

#include "Ag/Core/Binary.hpp"
#include "Ag/Core/LinearSortedMap.hpp"
#include "Ag/Geometry/Triangle2D.hpp"
#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/DCEL_Algorithms.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"
#include "DCEL_RingTracer.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////
// To get trace output of the Y-monotone sweep algorithm swap the commenting
// of the two lines below.
// #define TRACE_SWEEP TRACE
#define TRACE_SWEEP

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
using IDToIDCollection = std::vector<std::pair<ID, ID>>;

//! @brief An object used to maintain the state of a plane sweep where edge
//! node connects with at most 2 relevant edges.
class MonotoneSweepState
{
private:
    SweepEdgeCollection _edges;
    const SweepContext &_context;
public:
    MonotoneSweepState(const SweepContext &context) :
        _context(context)
    {
    }

    SweepEdgeIter begin() { return _edges.begin(); }
    SweepEdgeIter end() { return _edges.end(); }

    bool isEmpty() const { return _edges.empty(); }

    void clear()
    {
        _edges.clear();
    }

    SweepEdgeIter insertEdge(EdgePtr edge, NodePtr associatedNode)
    {
        SweepEdge key(_context, edge);

        auto pos = std::upper_bound(_edges.begin(), _edges.end(), key,
                                    CompareSweepElements(_context));

        edge->setAssociatedNode(associatedNode);
        return _edges.insert(pos, key);
    }

    void replaceEdge(SweepEdgeIter at, EdgePtr edge, NodePtr associatedNode)
    {
        edge->setAssociatedNode(associatedNode);

        *at = SweepEdge(_context, edge);
    }

    SweepEdgeIter findEdgeAtNode(NodePtr node)
    {
        SweepEdge key(node);

        auto posPair = std::equal_range(_edges.begin(), _edges.end(), key,
                                        CompareSweepElements(_context));

        return posPair.first;
    }

    //! @brief Returns the position of the edge which intersects with or
    //! is left of a specified node.
    //! @param[in] node The node on the current sweep line.
    //! @param[out] isLeft Determines whether the returned edge is left
    //! of @p node.
    //! @return The edge related to @p node.
    SweepEdgeIter findEdgeAtNodeOrLeftOf(NodePtr node, bool &isLeft)
    {
        if (_edges.empty())
        {
            isLeft = false;
            return _edges.end();
        }

        SweepEdge key(node);

        auto pos = std::upper_bound(_edges.begin(), _edges.end(), key,
                                    CompareSweepElements(_context));

        if (pos == _edges.begin())
        {
            // The node is left of all edges on the sweep
            isLeft = false;

            return _edges.end();
        }

        // Move left of the edge found to either one intersecting
        // the specified node, or left of it.
        --pos;

        // Allow for slight inaccuracy in the grid.
        auto minOffset = node->getGridPosition().getX() - 1;

        isLeft = (pos->getSweepIntersection(_context).getX() < minOffset);

        return pos;
    }

    std::pair<SweepEdgeIter, SweepEdgeIter> findEdgesAtNode(NodePtr node)
    {
        SweepEdge key(node);
        auto keyOffset = node->getGridPosition().getX();
        auto minKeyOffset = keyOffset - 1;
        auto maxKeyOffset = keyOffset + 1;

        auto resultRange = std::equal_range(_edges.begin(), _edges.end(), key,
                                            CompareSweepElements(_context));

        // Extend the range to allow for grid inaccuracy.
        while (resultRange.first != _edges.begin())
        {
            auto pos = resultRange.first;
            --pos;

            auto edgeOffset = pos->getSweepIntersection(_context).getX();

            if (edgeOffset < minKeyOffset)
                break;

            resultRange.first = pos;
        }

        while (resultRange.second != _edges.end())
        {
            auto edgeOffset = resultRange.second->getSweepIntersection(_context).getX();

            if (edgeOffset > maxKeyOffset)
                break;

            ++resultRange.second;
        }

        return resultRange;
    }

    SweepEdgeIter findEdgeBefore(NodePtr node)
    {
        auto pos = _edges.end();

        if (_edges.empty() == false)
        {
            SweepEdge key(node);

            auto greaterOrEqualPos = std::lower_bound(_edges.begin(), _edges.end(), key,
                                                      CompareSweepElements(_context));

            if (greaterOrEqualPos != _edges.begin())
            {
                pos = greaterOrEqualPos - 1;
            }
        }

        return pos;
    }

    //! @brief Assigns a node in the sweep a buddy of the edge just left of it.
    //! @param[in] nodeOnSweep The node on the sweep to find and to assign to.
    void assignEdgeBefore(NodePtr nodeOnSweep)
    {
        EdgePtr edgeOnLeft = nullptr;

        if (_edges.empty() == false)
        {
            SweepEdge key(nodeOnSweep);
            SweepEdgeIter pos = std::lower_bound(_edges.begin(), _edges.end(), key,
                                                 CompareSweepElements(_context));

            if (pos != _edges.begin())
            {
                auto posLeftOf = pos;
                --posLeftOf;

                edgeOnLeft = posLeftOf->getEdge()->getParent();
            }
        }

        nodeOnSweep->setBuddyEdge(edgeOnLeft);
    }

    //! @brief Assigns a node in the sweep a buddy of the edge just left of it.
    //! @param[in] nodeOnSweep The node to assign to.
    //! @param[in] pos The position of the node in the sweep.
    void assignEdgeBefore(NodePtr nodeOnSweep, SweepEdgeIter pos)
    {
        EdgePtr edgeOnLeft = nullptr;

        if ((_edges.empty() == false) && (pos != _edges.begin()))
        {
            auto prev = pos;
            --prev;

            edgeOnLeft = prev->getEdge()->getParent();
        }

        nodeOnSweep->setBuddyEdge(edgeOnLeft);
    }

    SweepEdgeIter removeEdge(SweepEdgeIter pos)
    {
        return _edges.erase(pos);
    }

    SweepEdgeIter removeEdgeRange(SweepEdgeIter begin, SweepEdgeIter end)
    {
        return _edges.erase(begin, end);
    }

    EdgePtr succeedEdge(SweepEdgeIter pos)
    {
        if (pos == _edges.end())
            return nullptr;

        HalfEdgePtr edge = pos->getEdge();
        HalfEdgePtr nextEdge = nullptr;

        if (_context.comparePositions(edge->getStartNode()->getGridPosition(),
                                      edge->getEndNode()->getGridPosition()))
        {
            nextEdge = edge->getNextEdge();
        }
        else
        {
            nextEdge = edge->getPreviousEdge();
        }

        EdgePtr parent = nextEdge->getParent();
        *pos = SweepEdge(_context, parent);

        return parent;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if a vertex in a monotone sweep was classified as a
//! merge vertex.
//! @param[in] context The object defining the sweep ordering.
//! @param[in] events The sorted collection of all events.
//! @param[in] vertex The vertex to classify, can be nullptr.
//! @retval true @p vertex was classified as a merge vertex.
//! @retval false @p vertex was null or given a different classification.
bool isMergeVertex(/*const SweepContext &context,
                   const SweepEventCollection &events,*/
                   NodeCPtr vertex)
{
    return (vertex->getFlags() & 1) != 0;
}

//! @brief Classifies a point for use in a monotone-polygon making sweep.
//! @param[in] ringFlags The flags associated with the ring the points belong to.
//! @param[in] prevNode The node before the one to classify.
//! @param[in] currentNode The node to classify.
//! @param[in] nextNode The node after the one to classify.
//! @return The monotone sweep vertex classification, e.g. RegularVertex.
template<typename TComparer>
uint32_t classifyMonotonePoint(uint32_t ringFlags,
                               NodeCPtr prevNode, NodeCPtr currentNode,
                               NodeCPtr nextNode)
{
    TComparer compare;
    const bool isCCW = (ringFlags & Ring::IsCCW) != 0;
    const bool isHole = (ringFlags & Ring::IsHole) != 0;

    // Determine if the previous point is earlier than the current point in the sweep.
    bool isPrevLater = compare(currentNode->getGridPosition(),
                               prevNode->getGridPosition());

    // Determine if the next point is earlier than the current point in the sweep.
    bool isNextLater = compare(currentNode->getGridPosition(),
                               nextNode->getGridPosition());

    // Calculate the local winding of the three points.
    Triangle2D triangle(prevNode->getRealPosition(),
                        currentNode->getRealPosition(),
                        nextNode->getRealPosition());

    double localDet = triangle.getDeterminant();
    bool isLocalCCW = (localDet > 0.0);

    if (localDet == 0)
    {
        // The point forms a direct extension of the line.
        isLocalCCW = isCCW;
    }

    // Merge the properties of the point into a bitfield using the
    // following bit INDEXES.
    constexpr uint8_t PrevLater = 0;
    constexpr uint8_t NextLater = 1;
    constexpr uint8_t IsReflexAngle = 2;

    // Look up the classification of the point from the bitfield index.
    static const uint8_t classifications[] = {
        EndVertex,      // Both points before, interior angle < 180 degrees.
        RegularVertex,  // Previous point before, next after.
        RegularVertex,  // Next point before, previous after.
        StartVertex,    // Both points after, interior angle < 180 degrees.
        MergeVertex,    // Both points before, interior angle > 180 degrees.
        RegularVertex,  // Previous point before, next after.
        RegularVertex,  // Next point before, previous after.
        SplitVertex,    // Both points after, interior angle > 180 degrees.
    };

    uint8_t classificationBits = 0;
    Ag::Bin::updateBit(classificationBits, PrevLater, isPrevLater);
    Ag::Bin::updateBit(classificationBits, NextLater, isNextLater);
    Ag::Bin::updateBit(classificationBits, IsReflexAngle, (isCCW != isLocalCCW) ^ isHole);

    return classifications[classificationBits];
}

//! @brief Traverses the nodes of a ring to create make-monotone sweep events.
//! @param[out] sweepEvents The collection of events to add to.
//! @param[in] ring The ring to traverse.
//! @param[in] context Details of the sweep to be performed.
//! @retval true At least one split or merge vertex was added to the collection.
//! @retval false No 'turn' vertices were added to the collection.
bool addMonotoneSweepEvents(SweepEventCollection &sweepEvents,
                            const Ring &ring)
{
    HalfEdgePtr currentEdge = ring.getFirstEdge();
    bool hasTurnVertices = false;
    CompareNodeYMonotoneSweepOrder comp;

    const SnapPoint gridStart = currentEdge->getStartNode()->getGridPosition();
    HalfEdgePtr prevEdge = currentEdge->getPreviousEdge();

    do
    {
        prevEdge = currentEdge->getPreviousEdge();
        NodePtr prevNode = prevEdge->getStartNode();
        NodePtr currentNode = currentEdge->getStartNode();
        NodePtr nextNode = currentEdge->getEndNode();

        // Classify the point based on its relationship to surrounding
        // points and the ring it belongs to.
        uint32_t vertexClass =
            classifyMonotonePoint<CompareNodeYMonotoneSweepOrder>(ring.getFlags(),
                                                                  prevNode, currentNode,
                                                                  nextNode);

        switch (vertexClass)
        {
        case MergeVertex:
            hasTurnVertices = true;

            // Annotate merge vertices.
            currentNode->setFlags((vertexClass == MergeVertex) ? 1 : 0);
            break;

        case SplitVertex:
            // There is a turn vertex to eliminate, the polygon is
            // not y-monotone.
            hasTurnVertices = true;
            break;

        case RegularVertex:
            // The polygon is not strictly Y-monotone, but we can only treat
            // the affected RegularVertex nodes properly as Split/Merge
            // vertices when we get to them.
            hasTurnVertices |= comp.isParallel(prevNode, currentNode);
            break;
        }

        sweepEvents.emplace_back(currentNode, currentEdge, vertexClass);

        // Move on to the next edge.
        currentEdge = currentEdge->getNextEdge();
    } while ((currentEdge != nullptr) &&
             (currentEdge != ring.getFirstEdge()));

    if (currentEdge == nullptr)
    {
        throw Ag::OperationException("The ring to make monotone was malformed.");
    }

    return hasTurnVertices;
}

//! @brief Handles a merge vertex in a Y-monotone sweep.
//! @param[in] currentEvent Details of the vertex event.
//! @param[in] status The current status of the sweep.
//! @param[in] connections A collection to receive new connections to add
//! in order to make the ring y-monotone.
//! @return A pointer to the edge to the left of the processed vertex, if any.
EdgePtr handleMergeSweepVertex(const SweepEvent &currentEvent,
                               MonotoneSweepState &status,
                               IDToIDCollection &connections)
{
    EdgePtr buddyEdge = nullptr;
    ID sweepNodeID = currentEvent.getEventNode()->getID();

    // Remove the edge from the sweep.
    auto pos = status.findEdgeAtNode(currentEvent.getEventNode());

    TRACE_SWEEP("\nMerge Vertex #{0}",
          sweepNodeID);

    if (pos == status.end())
    {
        TRACE_SWEEP("Failed to find edge associated with node #{0} to remove!",
                    sweepNodeID);
    }
    else
    {
        HalfEdgePtr prevEdge = pos->getEdge();
        EdgePtr prevParent = prevEdge->getParent();

        TRACE_SWEEP("Found edge #{0} on sweep", prevParent->getID());

        NodePtr associatedNode = prevParent->getAssociatedNode();
        if (associatedNode != nullptr)
        {
            TRACE_SWEEP("  with buddy vertex #{0}", associatedNode->getID());
        }

        if (isMergeVertex(associatedNode))
        {
            // The node associated with the event edge is a merge vertex,
            // add a diagonal to connect it to the event location.
            TRACE_SWEEP("Connect vertices #{0} and #{1}",
                        sweepNodeID,
                        associatedNode->getID());

            connections.emplace_back(sweepNodeID,
                                     associatedNode->getID());
        }

        // Remove the last edge before the vertex.
        TRACE_SWEEP("Remove edge #{0}", prevParent->getID());

        pos = status.removeEdge(pos);

        if (pos != status.begin())
        {
            // Get the edge before the one which was deleted.
            --pos;

            buddyEdge = pos->getEdge()->getParent();
            associatedNode = buddyEdge->getAssociatedNode();
            TRACE_SWEEP("  with previous edge #{0}", buddyEdge->getID());

            if (isMergeVertex(associatedNode))
            {
                // The node associated with the event edge is a merge vertex,
                // add a diagonal to connect it to the event location.
                TRACE_SWEEP("Connect vertices #{0} and #{1}",
                            sweepNodeID,
                            associatedNode->getID());

                connections.emplace_back(sweepNodeID,
                                         associatedNode->getID());
            }

            TRACE_SWEEP("Set edge #{0} buddy vertex to #{1}",
                        buddyEdge->getID(),
                        sweepNodeID);

            buddyEdge->setAssociatedNode(currentEvent.getEventNode());
        }
    }

    return buddyEdge;
}

//! @brief Handles a split vertex in a Y-monotone sweep.
//! @param[in] currentEvent Details of the vertex event.
//! @param[in] status The current status of the sweep.
//! @param[in] connections A collection to receive new connections to add
//! in order to make the ring y-monotone.
//! @return A pointer to the edge to the left of the processed vertex, if any.
EdgePtr handleSplitSweepVertex(const SweepEvent &currentEvent,
                               MonotoneSweepState &status,
                               IDToIDCollection &connections)
{
    EdgePtr buddyEdge = nullptr;
    ID sweepNodeID = currentEvent.getEventNode()->getID();

    TRACE_SWEEP("\nSplit Vertex #{0}", sweepNodeID);

    SweepEdgeIter pos = status.findEdgeBefore(currentEvent.getEventNode());

    if (pos != status.end())
    {
        buddyEdge = pos->getEdge()->getParent();
        TRACE_SWEEP("Found previous edge #{0}", buddyEdge->getID());

        NodePtr associatedNode = buddyEdge->getAssociatedNode();
        if (associatedNode != nullptr)
        {
            TRACE_SWEEP("  with buddy vertex #{0}", associatedNode->getID());
        }

        if (associatedNode != nullptr)
        {
            // The node associated with the event edge is a merge vertex,
            // add a diagonal to connect it to the event location.
            TRACE_SWEEP("Connect vertices #{0} and #{1}",
                        sweepNodeID,
                        associatedNode->getID());

            connections.emplace_back(sweepNodeID,
                                     associatedNode->getID());
        }

        TRACE_SWEEP("Set edge #{0} buddy vertex to #{1}",
                    buddyEdge->getID(),
                    sweepNodeID);

        buddyEdge->setAssociatedNode(currentEvent.getEventNode());
    }

    // Set the buddy of  the new edge to the new node.
    currentEvent.getEdge()->setAssociatedNode(currentEvent.getEventNode());

    // Insert the new edge into the sweep.
    TRACE_SWEEP("Insert edge #{0} with buddy node  #{1}",
                currentEvent.getEdge()->getID(),
                sweepNodeID);

    status.insertEdge(currentEvent.getEdge(), currentEvent.getEventNode());

    return buddyEdge;
}

//! @brief Handles a regular vertex in a Y-monotone sweep.
//! @param[in] currentEvent Details of the vertex event.
//! @param[in] status The current status of the sweep.
//! @param[in] connections A collection to receive new connections to add
//! in order to make the ring y-monotone.
//! @return A pointer to the edge to the left of the processed vertex, if any.
EdgePtr handleRegularSweepVertex(const SweepEvent &currentEvent,
                                 MonotoneSweepState &status,
                                 IDToIDCollection &connections)
{
    EdgePtr buddyEdge = nullptr;
    ID sweepNodeID = currentEvent.getEventNode()->getID();

    bool isEdgeLeftOfNode = false;
    auto pos = status.findEdgeAtNodeOrLeftOf(currentEvent.getEventNode(),
                                             isEdgeLeftOfNode);

    if (pos == status.end())
    {
        TRACE_SWEEP("Failed to find edge associated with bounding node #{0}!",
                    sweepNodeID);
    }
    else if (isEdgeLeftOfNode)
    {
        // The interior of the polygon is left of this node and we are
        // not tracing this side in the sweep status.
        TRACE_SWEEP("\nRegular Non-Bounding Vertex #{0}",
                    sweepNodeID);

        buddyEdge = pos->getEdge()->getParent();
        TRACE_SWEEP("Previous edge #{0}", buddyEdge->getID());

        NodePtr associatedNode = buddyEdge->getAssociatedNode();
        if (associatedNode != nullptr)
        {
            TRACE_SWEEP("  with buddy vertex #{0}", associatedNode->getID());
        }

        if (isMergeVertex(associatedNode))
        {
            // The node associated with the event edge is a merge vertex,
            // add a diagonal to connect it to the event location.
            TRACE_SWEEP("Connect vertices #{0} and #{1}",
                        sweepNodeID,
                        associatedNode->getID());

            connections.emplace_back(sweepNodeID,
                                     associatedNode->getID());
        }

        // Replace the node associated with the edge to the left/below.
        TRACE_SWEEP("Set edge #{0} buddy vertex to #{1}",
                    buddyEdge->getID(),
                    sweepNodeID);

        buddyEdge->setAssociatedNode(currentEvent.getEventNode());
    }
    else // current node is on the edge at pos
    {
        // The interior of the polygon is to the right of this node
        // and we are tracking this edge.
        TRACE_SWEEP("\nRegular Bounding Vertex #{0}",
                    sweepNodeID);

        HalfEdgePtr prevEdge = pos->getEdge();

        TRACE_SWEEP("Found sweep edge #{0}",
                    prevEdge->getParent()->getID());

        NodePtr associatedNode = prevEdge->getParent()->getAssociatedNode();

        if (associatedNode != nullptr)
        {
            TRACE("  with buddy vertex #{0}",
                  associatedNode->getID());
        }

        if (isMergeVertex(associatedNode))
        {
            // The node associated with the event edge is a merge vertex,
            // add a diagonal to connect it to the event location.
            TRACE_SWEEP("Connect vertices #{0} and #{1}",
                        sweepNodeID,
                        associatedNode->getID());

            connections.emplace_back(sweepNodeID,
                                     associatedNode->getID());
        }

        // Replace the edge coming to an end with its successor.
        TRACE_SWEEP("Replace edge #{0} with #{1}",
                    pos->getEdge()->getParent()->getID(),
                    currentEvent.getEdge()->getID());

        status.replaceEdge(pos, currentEvent.getEdge(),
                           currentEvent.getEventNode());

        TRACE_SWEEP("Set buddy of edge #{0} to vertex #{1}",
                    pos->getEdge()->getParent()->getID(),
                    sweepNodeID);

        // Use the position in the sweep to assign a buddy edge.
        if (pos != status.begin())
        {
            auto prevPos = pos;
            --prevPos;

            buddyEdge = prevPos->getEdge()->getParent();
        }
    }

    return buddyEdge;
}

//! @brief Handles a start vertex in a Y-monotone sweep.
//! @param[in] currentEvent Details of the vertex event.
//! @param[in] status The current status of the sweep.
//! @return A pointer to the edge to the left of the processed vertex, if any.
EdgePtr handleStartSweepVertex(const SweepEvent &currentEvent,
                               MonotoneSweepState &status)
{
    EdgePtr buddyEdge = nullptr;
    ID sweepNodeID = currentEvent.getEventNode()->getID();

    TRACE_SWEEP("\nStart Vertex #{0}", sweepNodeID);

    TRACE_SWEEP("Insert edge #{0} with buddy node  #{1}",
                currentEvent.getEdge()->getID(),
                sweepNodeID);

    auto insertionPos = status.insertEdge(currentEvent.getEdge(),
                                          currentEvent.getEventNode());

    // Assign the edge to the left of the node, if any.
    if (insertionPos != status.begin())
    {
        auto prevPos = insertionPos;
        --prevPos;

        buddyEdge = prevPos->getEdge()->getParent();
    }

    return buddyEdge;
}

//! @brief Handles a merge vertex in a Y-monotone sweep.
//! @param[in] currentEvent Details of the vertex event.
//! @param[in] status The current status of the sweep.
//! @param[in] connections A collection to receive new connections to add
//! in order to make the ring y-monotone.
void handleEndSweepVertex(const SweepEvent &currentEvent,
                          MonotoneSweepState &status,
                          IDToIDCollection &connections)
{
    ID sweepNodeID = currentEvent.getEventNode()->getID();

    TRACE_SWEEP("\nEnd Vertex #{0}", sweepNodeID);

    // Find the bounding edge which ends here.
    auto pos = status.findEdgeAtNode(currentEvent.getEventNode());

    if (pos == status.end())
    {
        TRACE_SWEEP("\nEnd Vertex #{0} is not on an edge in the sweep!",
                    sweepNodeID);
    }
    else
    {
        HalfEdgePtr prevEdge = pos->getEdge();

        NodePtr associatedNode = prevEdge->getParent()->getAssociatedNode();
        if (associatedNode != nullptr)
        {
            TRACE_SWEEP("  with buddy vertex #{0}",
                        associatedNode->getID());
        }

        if (isMergeVertex(associatedNode))
        {
            // The node associated with the event edge is a merge vertex,
            // add a diagonal to connect it to the event location.
            TRACE_SWEEP("Connect vertices #{0} and #{1}",
                        sweepNodeID,
                        associatedNode->getID());

            connections.emplace_back(sweepNodeID,
                                     associatedNode->getID());
        }

        // Remove the edge from the sweep.
        TRACE_SWEEP("Remove edge #{0}",
                    pos->getEdge()->getParent()->getID());

        pos = status.removeEdge(pos);
    }
}

//! @brief Sorts and processes events in a y-monotone sweep.
//! @param[in] context The context in which the sweep takes place.
//! @param[in] sweepEvents The collection of events to be sorted and processed.
//! @param[in] status The data structure which tracks which edges are currently
//! intersecting the horizontal sweep line.
//! @param[in] connections A collection to receive new connections to add
//! in order to make the ring y-monotone.
void processMonotoneSweepEvents(SweepContext &context,
                                SweepEventCollection &sweepEvents,
                                MonotoneSweepState &status,
                                IDToIDCollection &connections)
{
    // Sort the events so that they can be processed in sweep order.
    sortSweepEvents(context, sweepEvents);

    TRACE("Sweep Events");

    static const std::string_view nodeTypes[] = {
        "Split",
        "Start",
        "Regular",
        "Merge",
        "End",
    };

    for (const auto &evt : sweepEvents)
    {
        if (evt.getEdge() == nullptr)
            TRACE_SWEEP("{0}: Type: {1}",
                        evt.getEventNode()->getID(),
                        nodeTypes[evt.getEventType()]);
        else
            TRACE_SWEEP("{0}: Type: {1} (Edge {2})",
                        evt.getEventNode()->getID(),
                        nodeTypes[evt.getEventType()],
                        evt.getEdge()->getID());
    }

    // Process the events in order to add diagonal lines.
    for (const SweepEvent &currentEvent : sweepEvents)
    {
        // Move the sweep line to the position of the next event.
        context.setSweepNode(currentEvent.getEventNode());
        EdgePtr buddyEdge = nullptr;

        // Process the event.
        auto sweepNodeID = currentEvent.getEventNode()->getID();

        switch (currentEvent.getEventType())
        {
        case RegularVertex:
            buddyEdge = handleRegularSweepVertex(currentEvent, status,
                                                 connections);
            break;

        case StartVertex:
            buddyEdge = handleStartSweepVertex(currentEvent, status);
            break;

        case EndVertex:
            handleEndSweepVertex(currentEvent, status, connections);
            break;

        case MergeVertex:
            buddyEdge = handleMergeSweepVertex(currentEvent, status, connections);
            break;

        case SplitVertex:
            buddyEdge = handleSplitSweepVertex(currentEvent, status, connections);
            break;

        default: // Unknown event, do nothing.
            break;
        }

        // Associate the node with the edge immediately to the left if
        // we are doing a vertical sweep so that we can calculate the
        // hierarchy of rings and holes later.
        if (buddyEdge != nullptr)
            TRACE_SWEEP("[For later] Set node #{0} buddy edge to #{1}",
                        sweepNodeID,
                        buddyEdge->getID());

        currentEvent.getEventNode()->setBuddyEdge(buddyEdge);
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// CompareHalfEdgeByAngle Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Performs a less-than comparison on two directed edges based on their
//! absolute angle.
bool CompareHalfEdgeByAngle::operator()(HalfEdgePtr lhs, HalfEdgePtr rhs) const
{
    return lhs->getAngle() < rhs->getAngle();
}

//! @brief Performs a less-than comparison on two directed edges based on their
//! absolute angle.
bool CompareHalfEdgeByAngle::operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const
{
    return lhs->getAngle() < rhs->getAngle();
}

////////////////////////////////////////////////////////////////////////////////
// CompareHalfEdgeByRelativeAngle Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a relative angle comparison based on a fixed baseline.
//! @param[in] baseAngle The angle of the edge angles will be compared against.
//! @param[in] reverse Indicates whether the comparison result should be reversed.
CompareHalfEdgeByRelativeAngle::CompareHalfEdgeByRelativeAngle(const Angle &baseAngle,
                                                               bool reverse) :
    _baseAngle(baseAngle),
    _reverse(reverse)
{
}

//! @brief Performs a less-than comparison on two directed edges based on their
//! relative angle.
bool CompareHalfEdgeByRelativeAngle::operator()(HalfEdgePtr lhs, HalfEdgePtr rhs) const
{
    Angle lhsAngle = lhs->getAngle() - _baseAngle;
    Angle rhsAngle = rhs->getAngle() - _baseAngle;

    return _reverse ? (lhsAngle < rhsAngle) : (rhsAngle < lhsAngle);
}

//! @brief Performs a less-than comparison on two directed edges based on their
//! relative angle.
bool CompareHalfEdgeByRelativeAngle::operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const
{
    Angle lhsAngle = lhs->getAngle() - _baseAngle;
    Angle rhsAngle = rhs->getAngle() - _baseAngle;

    return _reverse ? (lhsAngle < rhsAngle) : (rhsAngle < lhsAngle);
}

////////////////////////////////////////////////////////////////////////////////
// CompareNodeByHorizontalPosition Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if the edges is parallel to the sweep.
//! @retval true The points have the same horizontal offset.
//! @retval false The horizontal offsets are different.
bool CompareNodeByHorizontalPosition::isParallel(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().getX() == rhs->getGridPosition().getX();
}

//! @brief Performs a less-than comparison using the grid position of nodes.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a lower X offset to @p rhs, or
//! their X offsets are equal and @lhs has the lowest Y position.
bool CompareNodeByHorizontalPosition::operator()(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().lessThanXMajor(rhs->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid position of start nodes
//! of a pair of directed edges.
//! @param[in] lhs The edge starting with the first position to compare.
//! @param[in] rhs The edge starting with the second position to compare.
//! @retval true The grid position of @p lhs has a lower X offset to @p rhs, or
//! their X offsets are equal and @lhs has the lowest Y position.
bool CompareNodeByHorizontalPosition::operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const
{
    return lhs->getStartNode()->getGridPosition().lessThanXMajor(rhs->getStartNode()->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid positions.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a lower X offset to @p rhs, or
//! their X offsets are equal and @lhs has the lowest Y position.
bool CompareNodeByHorizontalPosition::operator()(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return lhs.lessThanXMajor(rhs);
}

////////////////////////////////////////////////////////////////////////////////
// CompareNodeByVerticalPosition Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if the edges is parallel to the sweep.
//! @retval true The points have the same vertical offset.
//! @retval false The vertical offsets are different.
bool CompareNodeByVerticalPosition::isParallel(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().getY() == rhs->getGridPosition().getY();
}

//! @brief Performs a less-than comparison using the grid position of nodes.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a lower Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeByVerticalPosition::operator()(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().lessThanYMajor(rhs->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid position of start nodes
//! of a pair of directed edges.
//! @param[in] lhs The edge starting with the first position to compare.
//! @param[in] rhs The edge starting with the second position to compare.
//! @retval true The grid position of @p lhs has a lower Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeByVerticalPosition::operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const
{
    return lhs->getStartNode()->getGridPosition().lessThanYMajor(rhs->getStartNode()->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid positions.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a lower Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeByVerticalPosition::operator()(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return lhs.lessThanYMajor(rhs);
}

////////////////////////////////////////////////////////////////////////////////
// CompareNodeYMonotoneSweepOrder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if the edges is parallel to the sweep.
//! @retval true The points have the same vertical offset.
//! @retval false The vertical offsets are different.
bool CompareNodeYMonotoneSweepOrder::isParallel(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().getY() == rhs->getGridPosition().getY();
}

//! @brief Performs a less-than comparison using the grid position of nodes.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a lower Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeYMonotoneSweepOrder::operator()(NodeCPtr lhs, NodeCPtr rhs) const
{
    return lhs->getGridPosition().lessThanSweep(rhs->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid position of start nodes
//! of a pair of directed edges.
//! @param[in] lhs The edge starting with the first position to compare.
//! @param[in] rhs The edge starting with the second position to compare.
//! @retval true The grid position of @p lhs has a lower Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeYMonotoneSweepOrder::operator()(HalfEdgeCPtr lhs, HalfEdgeCPtr rhs) const
{
    return lhs->getStartNode()->getGridPosition().lessThanSweep(rhs->getStartNode()->getGridPosition());
}

//! @brief Performs a less-than comparison using the grid positions.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval true The grid position of @p lhs has a higher Y offset to @p rhs, or
//! their Y offsets are equal and @lhs has the lowest X position.
bool CompareNodeYMonotoneSweepOrder::operator()(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return lhs.lessThanSweep(rhs);
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Classifies a point on a ring to be used in an X-monotone sweep.
//! @param[in] ringFlags The flags associated with the ring the points belong to.
//! @param[in] prevNode The node before the one to classify.
//! @param[in] currentNode The node to classify.
//! @param[in] nextNode The node after the one to classify.
//! @return The monotone sweep vertex classification, e.g. RegularVertex.
uint32_t classifyXMonotonePoint(uint32_t ringFlags,
                                NodeCPtr prevNode, NodeCPtr currentNode,
                                NodeCPtr nextNode)
{
    return classifyMonotonePoint<CompareNodeByHorizontalPosition>(ringFlags, prevNode,
                                                                  currentNode, nextNode);
}

//! @brief Classifies a point on a ring to be used in an Y-monotone sweep.
//! @param[in] ringFlags The flags associated with the ring the points belong to.
//! @param[in] prevNode The node before the one to classify.
//! @param[in] currentNode The node to classify.
//! @param[in] nextNode The node after the one to classify.
//! @return The monotone sweep vertex classification, e.g. RegularVertex.
uint32_t classifyYMonotonePoint(uint32_t ringFlags,
                                NodeCPtr prevNode, NodeCPtr currentNode,
                                NodeCPtr nextNode)
{
    // TODO: Needs to be this way to make most test pass.
    // Triangulate test fail doing a bottom-up sweep because of the
    // order of horizontal edges in the examples - they change whether
    // the polygons are strict Y-monotone and the tests fail.
    // 
    // We need to fix the contradiction that the Y-monotone plane sweep
    // can introduce horizontal edges, which make the results not strictly
    // Y-monotone.
    return classifyMonotonePoint<CompareNodeYMonotoneSweepOrder>(ringFlags, prevNode,
                                                                 currentNode, nextNode);
}

//! @brief Performs a vertical sweep through all nodes in the mesh to annotate
//! each node with the edge immediately to its left.
//! @param[in] nodes The table of all nodes in the mesh.
//! @param[in] edges The table of all meshes in the mesh.
void assignEdgesLeftOfNodes(NodeTable &nodes, EdgeTable &edges)
{
    // Perform a vertical sweep through all points.
    SweepContext context(nodes);
    auto end = nodes.endByPosition();

    MonotoneSweepState status(context);

    std::pair<SweepEdgeIter, SweepEdgeIter> edgesToSort(status.end(), status.end());

    // Iterate over the nodes assigning each the edge to its left, if any.
    for (auto nodePos = nodes.beginByPosition(); nodePos != end; ++nodePos)
    {
        NodePtr currentNode = nodePos->second;
        EdgePtr edgeLeftOfNode = nullptr;

        context.setSweepNode(currentNode);

        if (edgesToSort.first != edgesToSort.second)
        {
            // Sort the edge added in the previous pass.
            std::sort(edgesToSort.first, edgesToSort.second,
                      CompareSweepElements(context));
        }

        // Find the edges which connect to the current sweep node.
        auto sweepEdgeRange = status.findEdgesAtNode(currentNode);

        if (sweepEdgeRange.first == sweepEdgeRange.second)
        {
            // There are no edges at the current node.
            // 
            // Find the edge to the left of the current node (if any).
            auto edgePos = status.findEdgeBefore(currentNode);

            if (edgePos != status.end())
            {
                edgeLeftOfNode = edgePos->getEdge()->getParent();
            }
        }
        else
        {
            // Find the edge just before the range of edges at the current node.
            if (sweepEdgeRange.first != status.begin())
            {
                SweepEdgeIter prevEdge = sweepEdgeRange.first;
                --prevEdge;

                edgeLeftOfNode = prevEdge->getEdge()->getParent();
            }

            // Removes the edges which connect to the current node.
            status.removeEdgeRange(sweepEdgeRange.first, sweepEdgeRange.second);
        }

        // Annotate the current node with the edge immediately to its left.
        currentNode->setBuddyEdge(edgeLeftOfNode);

        // Iterate over the edges connected to the current node.
        auto edgeMappingPair = edges.rangeOfEdgesAtNode(currentNode->getID());

        size_t edgesAdded = 0;

        for (const auto &edgeMappingPos : edgeMappingPair)
        {
            EdgePtr nextEdge = edgeMappingPos.second;
            NodePtr otherEnd = nextEdge->getOppositeNode(currentNode);

            if (currentNode->getGridPosition().lessThanSweep(otherEnd->getGridPosition()))
            {
                // The edge proceeds into the sweep.
                status.insertEdge(nextEdge, nullptr);
                ++edgesAdded;
            }
        }

        if (edgesAdded > 1)
        {
            // Defer sorting the newly added edges until we have swept to
            // the next node.
            edgesToSort = status.findEdgesAtNode(currentNode);
        }
        else
        {
            // No sorting required.
            edgesToSort.first = edgesToSort.second = status.end();
        }
    }
}

//! @brief Adds diagonal lines to a set of polygons and holes to make the
//! mesh monotone in the Y direction.
//! @param[in] nodes The table of all notes in the mesh.
//! @param[in] edges The table of all edges in the mesh.
//! @param[in,out] rings The system of rings and holes to make monotone, updated
//! with a new set of rings if/when diagonals have been added.
//! @retval True if diagonal edges were added and the @p rings collection
//! has been re-calculated.
//! @retval False No diagonal lines were added, the rings collection is unaltered.
bool makeYMonotone(NodeTable &nodes, EdgeTable &edges,
                  RingSystem &rings)
{
    SweepContext context(nodes);
    const uint32_t MonotoneFlags = Ring::IsYMonotone;

    SweepEventCollection sweepEvents;
    sweepEvents.reserve((nodes.getCount() * 110) / 100);

    MonotoneSweepState status(context);
    IDToIDCollection connections;
    connections.reserve(16);

    // Iterate over filled rings.
    for (const Ring &originalRing : rings.getRings())
    {
        if (originalRing.isHole())
            continue;

        // Now find any holes in that ring and add events for them.
        auto holeIDs = rings.getHoleMappings(originalRing.getID());

        // If the hole has no rings and is already monotone on the specified
        // axis, don't bother processing it.
        if (holeIDs.isEmpty() && (originalRing.getFlags() & MonotoneFlags))
            continue;

        // Reset the state for a new sweep.
        sweepEvents.clear();
        status.clear();

        // Go through all nodes on the ring classifying them and creating sweep
        // events.
        bool hasTurnVertices = addMonotoneSweepEvents(sweepEvents, originalRing);

        for (const auto &mapping : holeIDs)
        {
            // If there is a hole the ring must be processed.
            hasTurnVertices = true;

            addMonotoneSweepEvents(sweepEvents,
                                   rings.getRing(mapping.second));
        }

        // Only process the events if we can actually make some new connections
        // which will split the ring.
        if (hasTurnVertices)
        {
            // Sort and process the events gathered for a single ring and
            // all of its holes to add to the set of connections needed
            // to make the system of rings monotone.
            processMonotoneSweepEvents(context, sweepEvents,
                                       status, connections);
        }
    }

    if (connections.empty() == false)
    {
        // Create edges for all the connections.
        puts("Monotone Connected Edges:\n");

        for (const auto &connection : connections)
        {
            printf("Connect %u -> %u\n", connection.first, connection.second);

            edges.addEdge(nodes, connection.first, connection.second);
        }

         putchar('\n');

        // Reform the ring split by diagonals into several rings.
        rings.buildFromPartitioned(nodes, edges);
    }

    return (connections.empty() == false);
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

