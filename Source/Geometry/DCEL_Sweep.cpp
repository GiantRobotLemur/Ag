//! @file Geometry/DCEL_Sweep.cpp
//! @brief The definition of structures required to implement a sweep through
//! edges held in a Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <iterator>

#include "Ag/Core/Exception.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"

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

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// SweepContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object representing the environment of a vertical
//! plane sweep.
//! @param[in] allNodes The table of nodes being swept through.
//! @param[in] allEdges The table of edges which will appear in the sweep.
SweepContext::SweepContext(const NodeTable &allNodes) :
    _allNodes(allNodes),
    _sweepPosition(nullptr),
    _sweepLine()
{
    // Initialise a sweep line which at least is orientated correctly.
    _sweepLine = LineEq2D(Point2D(0, 0), Point2D(1, 0));
}

//! @brief Sets the new position of the sweep.
//! @param[in] sweepPosition The node representing the current sweep position.
void SweepContext::setSweepNode(NodePtr sweepPosition)
{
    _sweepPosition = sweepPosition;

    if (sweepPosition != nullptr)
    {
        // A horizontal sweep needs a vertical sweep line and vice-versa.
        const Point2D delta = Point2D(1, 0);
        const Point2D &origin = _sweepPosition->getRealPosition();

        // Create an equation of a line passing through the new sweep position.
        _sweepLine = LineEq2D(origin, origin + delta);
    }
}

//! @brief Determines if the snapped ends of an edge are co-linear with the
//! sweep line, i.e. horizontal.
//! @param[in] edge The edge to test.
//! @retval true If the edge is horizontal.
//! @retval false The edge is not horizontal.
bool SweepContext::isParallelToSweepLine(EdgeCPtr edge) const
{
    const SnapPoint &first = edge->getFirstNode()->getGridPosition();
    const SnapPoint &second = edge->getSecondNode()->getGridPosition();

    return (first.getY() == second.getY());
}

//! @brief Calculates the intersection of a line with the sweep.
//! @param[in] line The line representing an edge intersecting the sweep.
//! @return The grid point where the sweep line and @p line intersect.
//! @throws Ag::OperationException If no sweep position has been set.
SnapPoint SweepContext::getSweepIntersection(const LineEq2D &line) const
{
    Point2D intersection;

    if (_sweepPosition == nullptr)
    {
        throw Ag::OperationException("Finding the sweep intersection before "
                                     "any sweep position has been set.");
    }
    else if (line.tryCalculateIntersection(_sweepLine, intersection))
    {
        return _allNodes.getGrid().snapPoint(intersection);
    }
    else
    {
        return _sweepPosition->getGridPosition();
    }
}

//! @brief Compares snapped positions in relation to where they appear on the sweep.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @retval If @p lhs appears earlier in the sweep than @p rhs.
//! @retval If @p lhs appears at the same or a later point in the sweep than @p rhs.
bool SweepContext::comparePositions(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return lhs.lessThanSweep(rhs);
}

//! @brief Calculates the relative ordering of two grid points in a sweep.
//! @param[in] lhs The first position to compare.
//! @param[in] rhs The second position to compare.
//! @return -1, 0 or 1 depending on whether @p lhs is less than, equal to or
//! greater than @p rhs, respectively.
int SweepContext::diffPositions(const SnapPoint &lhs, const SnapPoint &rhs) const
{
    return lhs.diffSweep(rhs);
}

////////////////////////////////////////////////////////////////////////////////
// SweepEdge Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a sweep edge parallel to the sweep direction (perpendicular
//! to the sweep line) through a specified node.
//! @param[in] node A pointer to the node the edge should pass through.
SweepEdge::SweepEdge(NodePtr node) :
    _edge(nullptr),
    _edgeLine(),
    _lastSweepOffset(0),
    _cachedSweepIntersection(0),
    _isColinear(true)
{
    Point2D delta(0, 1);
    const Point2D &origin = node->getRealPosition();

    // Create a line parallel to the sweep direction passing through the node.
    _edgeLine = LineEq2D(origin, origin + delta);
}

//! @brief Constructs an object representing an edge which intersects the
//! horizontal or vertical line representing the current sweep position.
//! @param[in] context Details of the sweep the edge will participate in.
//! @param[in] edge A pointer to the edge to wrap.
SweepEdge::SweepEdge(const SweepContext &context, EdgePtr edge) :
    _edge(nullptr),
    _edgeLine(),
    _lastSweepOffset(0),
    _cachedSweepIntersection(0),
    _isColinear(context.isParallelToSweepLine(edge))
{
    if (edge == nullptr)
    {
        throw Ag::ArgumentException("edge");
    }

    NodeCPtr startNode = edge->getFirstNode();
    NodeCPtr endNode = edge->getSecondNode();

    // Order the nodes by when they are processed by the sweep.
    if (context.comparePositions(endNode->getGridPosition(), startNode->getGridPosition()))
    {
        // Swap the order of the nodes.
        std::swap(startNode, endNode);
    }

    // Get the directed edge which travels into the sweep.
    _edge = edge->getHalfEdgeFrom(startNode->getID());

    // Initialise the line equation used for intersection calculation.
    _edgeLine = LineEq2D(startNode->getRealPosition(), endNode->getRealPosition());

    // Ensure the cached sweep position is calculated, so that the default value
    // of 0 doesn't confuse things when the actual sweep position is zero.
    getSweepIntersection(context);
}

//! @brief Calculates the snapped position at which the current edge intersects
//! with the current position of the plane sweep.
//! @param[in] context The object detailing the current sweep position.
//! @return The intersection point snapped to a grid.
SnapPoint SweepEdge::getSweepIntersection(const SweepContext &context) const
{
    NodeCPtr sweepPos = context.getSweepNode();

    if (sweepPos == nullptr)
    {
        throw OperationException("Cannot calculate intersection with sweep that has no position.");
    }

    const SnapPoint &sweepGridPos = sweepPos->getGridPosition();
    SnapPoint intersection;

    if (_isColinear)
    {
        intersection = sweepGridPos;
    }
    else
    {
        if (sweepGridPos.getY() == _lastSweepOffset)
        {
            // Use the cached position.
            intersection.set(_cachedSweepIntersection, _lastSweepOffset);
        }
        else
        {
            // We need to re-calculate intersection with the sweep.
            intersection = context.getSweepIntersection(_edgeLine);
            _lastSweepOffset = intersection.getY();
            _cachedSweepIntersection = intersection.getX();
        }
    }

    return intersection;
}

//! @brief Determines if the current sweep edge represents the same edge as another.
//! @param[in] rhs The sweep edge to compare against.
//! @retval true If the current object wraps the same edge as @p rhs.
//! @retval false If the current object wraps a different edge from @p rhs.
bool SweepEdge::operator==(const SweepEdge &rhs) const
{
    return _edge->getParent() == rhs._edge->getParent();
}

////////////////////////////////////////////////////////////////////////////////
// SweepStatus Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which holds the current status if a plane sweep.
//! @param[in] context The environment in which the sweep will be performed.
SweepStatus::SweepStatus(SweepContext &context) :
    _context(context)
{
    _diagonalEdges.reserve(32);
    _colinearEdges.reserve(16);
}

//! @brief Finds the edge in the sweep below or left of a point on the sweep.
//! @param[in] position The node at the position to search next to.
//! @param[out] Receives the position of the edge left or below @p node on the sweep line.
//! @retval true An edge was found and its position returned in @p prevEdge.
//! @retval false No edge was found.
bool SweepStatus::findEdgeBeforeNode(NodePtr position, SweepEdgeIter &prevEdge)
{
    SweepEdge key(position);

    auto pos = std::lower_bound(_diagonalEdges.begin(), _diagonalEdges.end(),
                                key, CompareSweepElements(_context));

    bool hasEdge = false;

    if (pos == _diagonalEdges.begin())
    {
        prevEdge = _diagonalEdges.end();
    }
    else
    {
        --pos;
        prevEdge = pos;
        hasEdge = true;
    }

    return hasEdge;
}

//! @brief Adds an edge to the set intersecting the sweep line.
//! @param[in] edge The edge to add.
//! @return The position of the edge in the sweep, or the end of the diagonal
//! edge collection if the edge was parallel to the sweep.
SweepEdgeIter SweepStatus::addEdge(EdgePtr edge)
{
    SweepEdgeCollection::iterator pos = _diagonalEdges.end();

    SweepEdge edgeToAdd(_context, edge);

    if (edgeToAdd.isColinear())
    {
            // The edge is parallel to the sweep.
        if (edge->getFirstNode()->getGridPosition().getY() == _context.getSweepNode()->getGridPosition().getY())
        {
            // The edge is co-linear with the sweep line.
            _colinearEdges.push_back(edgeToAdd.getEdge());
        }
        else
        {
            throw OperationException("Cannot add a horizontal line when not at the sweep position.");
        }
    }
    else
    {
        // The edge is diagonal, insert it at the correct location.
        auto insertionPos = std::upper_bound(_diagonalEdges.begin(), _diagonalEdges.end(),
                                             edgeToAdd, CompareSweepElements(_context));

        pos = _diagonalEdges.insert(insertionPos, edgeToAdd);
    }

    return pos;
}

//! @brief Removes a diagonal edge from the sweep.
//! @param[in] edgePos The position of the edge to remove.
//! @return The position of the diagonal edge after the one removed.
SweepEdgeIter SweepStatus::removeEdge(SweepEdgeIter edgePos)
{
    return _diagonalEdges.erase(edgePos);
}

//! @brief Removes an edge from the sweep.
//! @param[in] edgeToRemove The edge to remove, possibly parallel to the sweep.
//! @return The iterator after the diagonal edge removed or the end of the
//! diagonal edge collection is the edge was parallel to the sweep.
SweepEdgeIter SweepStatus::removeEdge(HalfEdgeCPtr edgeToRemove)
{
    SweepEdge testEdge(_context, edgeToRemove->getParent());

    if (testEdge.isColinear())
    {
        // The edge is parallel to the sweep - remove it from the co-linear set.
        auto pos = std::remove(_colinearEdges.begin(), _colinearEdges.end(), edgeToRemove);

        _colinearEdges.erase(pos, _colinearEdges.end());
    }
    else
    {
        // The edge is diagonal, remove it from the diagonal set.
        auto rangePair = std::equal_range(_diagonalEdges.begin(), _diagonalEdges.end(),
                                          testEdge, CompareSweepElements(_context));

        if (rangePair.first != rangePair.second)
        {
            auto pos = std::find(rangePair.first, rangePair.second, testEdge);

            if (pos != rangePair.second)
            {
                return _diagonalEdges.erase(pos);
            }
        }
    }

    return _diagonalEdges.end();
}

//! @brief Removes the one edge at the current sweep node.
//! @return The iterator pointing to the node after the deleted node, or the
//! end of the diagonal edge collection.
SweepEdgeIter SweepStatus::removeEdgeAtSweep()
{
    SweepEdge key(_context.getSweepNode());

    if (_colinearEdges.empty() == false)
    {
        _colinearEdges.clear();
    }

    auto pos = std::lower_bound(_diagonalEdges.begin(), _diagonalEdges.end(),
                                key, CompareSweepElements(_context));

    if (pos == _diagonalEdges.end())
    {
        return pos;
    }
    else if (pos->getEdge()->getParent()->hasNode(_context.getSweepNode()))
    {
        return _diagonalEdges.erase(pos);
    }
    else
    {
        return _diagonalEdges.end();
    }
}

//! @brief Replaces the one edge at the sweep with its successor which proceeds
//! in the sweep-wards direction.
//! @return A pointer to the successor edge.
EdgePtr SweepStatus::succeedEdgeAtSweep()
{
    EdgePtr nextEdge = nullptr;

    if (_colinearEdges.empty())
    {
        SweepEdge key(_context.getSweepNode());

        auto posRange = std::equal_range(_diagonalEdges.begin(), _diagonalEdges.end(),
                                         key, CompareSweepElements(_context));

        if (posRange.first != posRange.second)
        {
            HalfEdgePtr currentEdge = posRange.first->getEdge();

            if (_context.comparePositions(currentEdge->getStartNode()->getGridPosition(),
                                          currentEdge->getEndNode()->getGridPosition()))
            {
                nextEdge = currentEdge->getNextEdge()->getParent();
            }
            else
            {
                nextEdge = currentEdge->getPreviousEdge()->getParent();
            }

            // Create a new edge.
            SweepEdge successor(_context, nextEdge);

            if (successor.getEdgeLine().isParallel(_context.getSweepLine()))
            {
                // The edge is co-linear with the sweep line.
                _colinearEdges.push_back(nextEdge->getHalfEdge(0));
                _diagonalEdges.erase(posRange.first);
            }
            else
            {
                // The edge is diagonal, replace the current edge.
                *posRange.first = successor;
            }
        }
    }
    else
    {
        HalfEdgePtr colinearLine = _colinearEdges.front();
        _colinearEdges.clear();

        if (_context.comparePositions(colinearLine->getStartNode()->getGridPosition(),
                                      colinearLine->getEndNode()->getGridPosition()))
        {
            nextEdge = colinearLine->getNextEdge()->getParent();
        }
        else
        {
            nextEdge = colinearLine->getPreviousEdge()->getParent();
        }

        SweepEdge successor(_context, nextEdge);

        if (successor.getEdgeLine().isParallel(_context.getSweepLine()))
        {
            // The edge is parallel to the sweep.
            _colinearEdges.push_back(nextEdge->getHalfEdge(0));
        }
        else
        {
            // The edge is diagonal, insert it at the correct location.
            auto insertionPos = std::upper_bound(_diagonalEdges.begin(), _diagonalEdges.end(),
                                                 successor, CompareSweepElements(_context));

            _diagonalEdges.insert(insertionPos, successor);
        }
    }

    return nextEdge;
}

////////////////////////////////////////////////////////////////////////////////
// SweepEvent Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty sweep event.
SweepEvent::SweepEvent() :
    _sweepPosition(nullptr),
    _edgeToProcess(nullptr),
    _eventType(0)
{
}

//! @brief Constructs a new event to be processed as part of a plane sweep.
//! @param[in] sweepPosition The position of the sweep when the event should
//! be processed.
//! @param[in] eventType A numeric identifier describing what processing should
//! occur.
SweepEvent::SweepEvent(NodePtr sweepPosition, uint32_t eventType) :
    _sweepPosition(sweepPosition),
    _edgeToProcess(nullptr),
    _eventType(eventType)
{
}

//! @brief Constructs a new event to be processed as part of a plane sweep.
//! @param[in] sweepPosition The position of the sweep when the event should
//! be processed.
//! @param[in] edge The edge which is relevant to the event type.
//! @param[in] eventType A numeric identifier describing what processing should
//! occur.
SweepEvent::SweepEvent(NodePtr sweepPosition, EdgePtr edge, uint32_t eventType) :
    _sweepPosition(sweepPosition),
    _edgeToProcess((edge == nullptr) ? nullptr : edge->getHalfEdge(0)),
    _eventType(eventType)
{
}

//! @brief Constructs a new event to be processed as part of a plane sweep.
//! @param[in] sweepPosition The position of the sweep when the event should
//! be processed.
//! @param[in] edge The edge which is relevant to the event type.
//! @param[in] eventType A numeric identifier describing what processing should
//! occur.
SweepEvent::SweepEvent(NodePtr sweepPosition, HalfEdgePtr edge, uint32_t eventType) :
    _sweepPosition(sweepPosition),
    _edgeToProcess(edge),
    _eventType(eventType)
{
}

//! @brief Gets the optional directed edge used to annotate the event.
HalfEdgePtr SweepEvent::getDirectedEdge() const
{
    return _edgeToProcess;
}

//! @brief Gets the optional edge used to annotate the event.
EdgePtr SweepEvent::getEdge() const
{
    return (_edgeToProcess == nullptr) ? nullptr : _edgeToProcess->getParent();
}

////////////////////////////////////////////////////////////////////////////////
// CompareSweepElements Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs the comparer for a specific sweep.
//! @param[in] context The context of the sweep in which comparisons should
//! be made.
CompareSweepElements::CompareSweepElements(const SweepContext &context) :
    _context(context)
{
}

//! @brief Compares sweep edges by their intersection with the sweep line.
bool CompareSweepElements::operator()(const SweepEdge &lhs, const SweepEdge &rhs) const
{
    SnapPoint lhsPoint = lhs.getSweepIntersection(_context);
    SnapPoint rhsPoint = rhs.getSweepIntersection(_context);

    return _context.comparePositions(lhsPoint, rhsPoint);
}

//! @brief Compares sweep events by when they should be processed.
bool CompareSweepElements::operator()(const SweepEvent &lhs, const SweepEvent &rhs) const
{
    int diff = _context.diffPositions(lhs.getEventNode()->getGridPosition(),
                                      rhs.getEventNode()->getGridPosition());

    if (diff == 0)
    {
        return lhs.getEventType() < rhs.getEventType();
    }
    else
    {
        return diff < 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
// SweepEventQueue Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to manage events processed as part of a plane sweep.
//! @param[in] context The context in which the sweep takes place.
SweepEventQueue::SweepEventQueue(const SweepContext &context) :
    _context(context)
{
}

//! @brief Creates an event queue with an initial set of events.
//! @param[in] context An object defining the sweep environment.
//! @param[in] initialEvents An unsorted array of events to copy.
//! @param[in] eventCount The count of elements in @p initialEvents.
SweepEventQueue::SweepEventQueue(const SweepContext &context,
                                 const SweepEvent *initialEvents,
                                 size_t eventCount) :
    _context(context)
{
    if (eventCount > 0)
    {
        // Copy the events en-mass.
        std::copy_n(initialEvents, eventCount,
                    std::back_inserter(_sortedEvents));

        // Sort the events all at once.
        std::sort(_sortedEvents.begin(), _sortedEvents.end(),
                  CompareSweepElements(_context));
    }
}

//! @brief Determines if there are no events in the queue.
bool SweepEventQueue::isEmpty() const noexcept
{
    return _sortedEvents.empty();
}

//! @brief Inserts an event into the correct position in the queue.
//! @param[in] eventToInsert The event to insert.
void SweepEventQueue::insertEvent(const SweepEvent &eventToInsert)
{
    auto insertionPos = std::upper_bound(_sortedEvents.begin(),
                                         _sortedEvents.end(), eventToInsert,
                                         CompareSweepElements(_context));

    _sortedEvents.insert(insertionPos, eventToInsert);
}

//! @brief Attempts to remove the next event for processing.
//! @param[out] nextEvent Receives the event removed from the front of the queue.
//! @retval true An event was returned for processing.
//! @retval false The queue was empty.
bool SweepEventQueue::tryPopEvent(SweepEvent &nextEvent)
{
    bool hasEvent = false;

    if (_sortedEvents.empty() == false)
    {
        nextEvent = _sortedEvents.front();
        _sortedEvents.pop_front();
        hasEvent = true;
    }

    return hasEvent;
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Sorts a linear collection of sweep events into sweep order.
//! @param[in] context The object defining sweep order.
//! @param[in] events The collection to sort.
void sortSweepEvents(const SweepContext &context, SweepEventCollection &events)
{
    std::sort(events.begin(), events.end(), CompareSweepElements(context));
}

//! @brief Determines if an event exists in a sorted linear collection of events.
//! @param[in] context The sweep context defining the sort order.
//! @param[in] events The collection of events to search.
//! @param[in] key The event to search for (defined by node and type).
//! @retval true An event with the matching node and type exist in @p events.
//! @retval false The no event matches @p key in @p events.
bool containsSweepEvent(const SweepContext &context, SweepEventCollection &events,
                        const SweepEvent &key)
{
    return std::binary_search(events.begin(), events.end(), key,
                              CompareSweepElements(context));
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

