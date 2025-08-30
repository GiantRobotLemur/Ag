//! @file Geometry/DCEL_Sweep.cpp
//! @brief The definition of structures required to implement a sweep through
//! edges held in a Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <iterator>

#include "Ag/Core/Exception.hpp"
#include "Ag/Geometry/Line2D.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief A functor to add edge start and end sweep events to a collection.
struct AccumulateEdgeEvents
{
private:
    const SweepContext &_context;
    SweepEventCollection &_edgeEvents;

public:
    AccumulateEdgeEvents(const SweepContext &context, SweepEventCollection &edgeEvents) :
        _context(context),
        _edgeEvents(edgeEvents)
    {
    }

    void operator()(EdgePtr edge)
    {
        NodePtr startNode = edge->getFirstNode();
        NodePtr endNode = edge->getSecondNode();

        if (_context.comparePositions(endNode->getGridPosition(), startNode->getGridPosition()))
        {
            // startNode appears after endNode in the sweep.
            std::swap(startNode, endNode);
        }

        if (startNode->getGridPosition().getY() == endNode->getGridPosition().getY())
        {
            // The edge is horizontal.
            _edgeEvents.emplace_back(startNode, edge, IntersectionEventType::HorizontalEdgeStarting);
            _edgeEvents.emplace_back(endNode, edge, IntersectionEventType::HorizontalEdgeEnding);
        }
        else
        {
            _edgeEvents.emplace_back(startNode, edge, IntersectionEventType::DiagonalEdgeStarting);
            _edgeEvents.emplace_back(endNode, edge, IntersectionEventType::DiagonalEdgeEnding);
        }
    }
};

//! @brief A comparer used to insert edges into an intersection plane sweep.
struct InsertionSweepDiagonalComparer
{
private:
    const SweepContext &_context;
public:
    InsertionSweepDiagonalComparer(const SweepContext &context) :
        _context(context)
    {
    }

    bool operator()(const SweepEdge &lhs, const SweepEdge &rhs) const
    {
        int64_t lhsX = lhs.getSweepIntersection(_context).getX();
        int64_t rhsX = rhs.getSweepIntersection(_context).getX();

        // Allow for subtle rounding errors.
        if (std::abs(lhsX - rhsX) <= 2)
        {
            // Adjust line angles to be CCW relative to the LH negative Y axis,
            // i.e. a range of -Pi/2 going left, 0 going down and +Pi/2 going right.
            static const Angle downAngle = Angle::fromDegrees(270);
            double lhsAngle = Angle::radiansToDegrees(downAngle.getOffsetTo(lhs.getEdge()->getAngle()));
            double rhsAngle = Angle::radiansToDegrees(downAngle.getOffsetTo(rhs.getEdge()->getAngle()));

            return lhsAngle < rhsAngle;
        }

        return (lhsX < rhsX);
    }
};

//! @brief Orders horizontal sweep edges by the X position of their
//! right-most (sweep-latest) node.
struct HorzSweepEdgeInsertionComparer
{
    bool operator()(const SweepEdge &lhs, const SweepEdge &rhs) const
    {
        return lhs.getLatestNode()->getGridPosition().lessThanSweep(rhs.getLatestNode()->getGridPosition());
    }
};

using IDToIDMapping = std::pair<ID, ID>;
using IDToIDMappingCollection = std::vector<IDToIDMapping>;

//! @brief A functor used to sort mappings from Edge ID to Node IDs, ordering nodes
//! by their position on a plane sweep.
struct IndexEdgeIDToNodeIDMappings
{
private:
    const NodeTable &_nodes;
public:
    IndexEdgeIDToNodeIDMappings(const NodeTable &nodes) :
        _nodes(nodes)
    {
    }

    bool operator()(const IDToIDMapping &lhs, const IDToIDMapping &rhs) const
    {
        bool isLessThan = false;

        if (lhs.first == rhs.first)
        {
            // Then compare by sweep position.
            const SnapPoint &lhsPos = _nodes[lhs.second].getGridPosition();
            const SnapPoint &rhsPos = _nodes[rhs.second].getGridPosition();

            isLessThan = lhsPos.lessThanSweep(rhsPos);
        }
        else
        {
            // First - sort by edge ID.
            isLessThan = lhs.first < rhs.first;
        }

        return isLessThan;
    }
};

using IndexIDMapping = LessThanKeyComparer<ID, ID>;
using EqualIDMapping = EqualToPairComparer<ID, ID>;

using ParametricNode = std::pair<double, NodePtr>;
using ParametricNodeIndexer = LessThanKeyComparer<double, NodePtr>;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Checks to see if two edges intersect later in the sweep and adds
//! an intersection event if one doesn't already exist.
//! @param[in] nodes The table of nodes used to find or create an intersection node.
//! @param[in] lhs The first edge to check for intersection.
//! @param[in] rhs The second edge to check for intersection.
//! @param[in] sweepPos The current position of the sweep.
//! @param[in] sweepEvents The event queue to add an intersection event to.
//! @retval true If a sweep event was added.
//! @retval false The edges didn't intersect or the intersection was before
//! the current sweep location.
bool checkForIntersection(NodeTable &nodes,
                          const SweepEdge &lhs, const SweepEdge &rhs,
                          NodeCPtr sweepPos, SweepEventQueue &sweepEvents)
{
    LineSeg2D lhsSeg = lhs.getEdge()->getSegment();
    LineSeg2D rhsSeg = rhs.getEdge()->getSegment();
    Point2D intersection;
    bool intersectionAdded = false;

    if (lhs.getEdgeLine().isColinear(nodes.getGrid().getDomain(), rhs.getEdgeLine()))
    {
        // The lines overlap - their intersection points are the start/end of
        // their overlapping portion.
        Line2D parametricLine;
        lhs.getEdgeLine().toParametricForm(parametricLine);

        // We know there will be at most 4 unique nodes in two overlapping lines.
        ParametricNode colinearNodes[4];
        size_t colinearNodeCount = 0;

        // Gather the nodes along with their positions along the shared line.
        for (DirectionIndex i = 0; i < 2; ++i)
        {
            EdgePtr edge = ((i == 0) ? lhs.getEdge() : rhs.getEdge())->getParent();

            for (DirectionIndex j = 0; j < 2; ++j)
            {
                NodePtr node = edge->getNode(j);
                const Point2D &nodePos = node->getRealPosition();

                colinearNodes[colinearNodeCount++] = { parametricLine.getParameter(nodePos), node };
            }
        }

        // Sort the nodes by their relative position on the shared line.
        std::sort(colinearNodes, colinearNodes + colinearNodeCount, ParametricNodeIndexer());

        // Remove any duplicates.
        const NumericDomain &domain = nodes.getGrid().getDomain();

        auto colinearEnd = std::unique(colinearNodes, colinearNodes + colinearNodeCount,
                                       [&domain](const ParametricNode &lhs, const ParametricNode &rhs) {
                                           return domain.isNearEqual(lhs.first, rhs.first);
                                       });
        size_t uniqueCount = (colinearEnd - colinearNodes) - 1;

        // The non-outlier nodes are the ones where intersection takes place.
        for (size_t i = 1; i < uniqueCount; ++i)
        {
            // Determine if an intersection event at that node already
            // exists, and if it doesn't, create one.
            SweepEvent intersectionEvent(colinearNodes[i].second, IntersectionEventType::Intersection);

            intersectionAdded |= sweepEvents.tryAddUniqueEvent(intersectionEvent);
        }
    }
    else if (lhsSeg.tryCalculateIntersection(nodes.getGrid().getDomain(), rhsSeg, intersection))
    {
        SnapPoint gridIntersection = nodes.getGrid().snapPoint(intersection);

        if (sweepPos->getGridPosition().lessThanSweep(gridIntersection))
        {
            // The intersection point is further down the sweep - create a node
            NodePtr intersectionNode = &nodes.addNode(intersection);

            // Ensure the intersection isn't where the two edges meet.
            if ((lhs.getEdge()->hasNode(intersectionNode) == false) ||
                (rhs.getEdge()->hasNode(intersectionNode) == false))
            {
                // Determine if an intersection event at that node already
                // exists, and if it doesn't, create one.
                SweepEvent intersectionEvent(intersectionNode, IntersectionEventType::Intersection);

                intersectionAdded = sweepEvents.tryAddUniqueEvent(intersectionEvent);
            }
        }
    }

    return intersectionAdded;
}

//! @brief Checks to see of a diagonal edge on the sweep line will likely
//! intersect a horizontal edge on the sweep line.
//! @param[in] nodes The table of nodes used to find or create an intersection node.
//! @param[in] horzLimitNode The right-most node on any horizontal edge
//! currently on the sweep line.
//! @param[in] diagonal A diagonal edge on the sweep line.
//! @param[in] sweepEvents The event queue to add an intersection event to.
//! @retval true If a sweep event was added.
//! @retval false The edges didn't inter
bool checkForHorizontalIntersection(const SweepContext &context, NodeTable &nodes,
                                    NodeCPtr horzLimitNode,
                                    const SweepEdge &diagonal,
                                    SweepEventQueue &sweepEvents)
{
    // If there are no horizontal lines on the sweep, there can be no intersections.
    if (horzLimitNode == nullptr)
        return false;

    // Ensure the horizontal line doesn't end before hitting the
    // diagonal as it crosses the sweep line.
    if (diagonal.getSweepIntersection(context).getX() >= horzLimitNode->getGridPosition().getX())
        return false;

    Point2D intersection;

    if (context.getSweepLine().tryCalculateIntersection(diagonal.getEdgeLine(), intersection))
    {
        SnapPoint gridIntersection = nodes.getGrid().snapPoint(intersection);

        if (context.getSweepNode()->getGridPosition().lessThanSweep(gridIntersection))
        {
            // The intersection is after the current sweep position - add it.
            NodePtr intersectionNode = &nodes.addNode(intersection);

            // Determine if an intersection event at that node already
            // exists, and if it doesn't, create one.
            SweepEvent intersectionEvent(intersectionNode, IntersectionEventType::Intersection);

            return sweepEvents.tryAddUniqueEvent(intersectionEvent);
        }
    }

    return false;
}

//! @brief Splits batched edges by nodes, clearing the batch.
//! @param[in] nodes The table defining all nodes in the mesh.
//! @param[in] edges The table defining all edges in the mesh.
//! @param[in] intersections A collection non-unique mappings from Edge ID to
//! the IDs of nodes which split that edge.
//! @retval true At lest one edge was split.
//! @retval false No edges were split.
bool splitEdgesAtIntersections(NodeTable &nodes, EdgeTable &edges,
                               IDToIDMappingCollection &intersections)
{
    // Sort mappings by edge ID and then by the relative position of the
    // identified node on the sweep, earliest first.
    std::sort(intersections.begin(), intersections.end(),
              IndexEdgeIDToNodeIDMappings(nodes));

    // Remove duplicates.
    auto last = std::unique(intersections.begin(), intersections.end(), EqualIDMapping());
    intersections.erase(last, intersections.end());

    IteratorRange<IDToIDMappingCollection::iterator> group;
    IndexIDMapping indexer;
    bool edgesSplit = false;

    if (getFirstGroup(intersections.begin(), intersections.end(), group, indexer))
    {
        do
        {
            // Go through the sweep ordered nodes, including the original first and
            // last nodes, to create a set of edges which replace the original.
            ID edgeID = group.front().first;
            EdgePtr originalEdge = edges[edgeID];

            auto firstNode = originalEdge->getFirstNode();
            auto secondNode = originalEdge->getSecondNode();

            // Ensure firstNode is earliest in sweep order.
            if (secondNode->getGridPosition().lessThanSweep(firstNode->getGridPosition()))
                std::swap(firstNode, secondNode);

            // Create new segments between original and intersection nodes.
            NodePtr prevNode = firstNode;

            for (const auto &mappingPos : group)
            {
                NodePtr nextNode = &nodes[mappingPos.second];

                if (originalEdge == nullptr)
                {
                    edges.addEdge(nodes, prevNode->getID(), nextNode->getID());
                }
                else if (edges.replaceEdge(nodes, edgeID, prevNode->getID(),
                                           nextNode->getID()))
                {
                    // The original edge was replaced.
                    originalEdge = nullptr;
                }

                prevNode = nextNode;
            }

            // Create the final edge.
            if (originalEdge == nullptr)
            {
                edges.addEdge(nodes, prevNode->getID(), secondNode->getID());
            }
            else if (edges.replaceEdge(nodes, edgeID, prevNode->getID(),
                                       secondNode->getID()))
            {
                originalEdge = nullptr;
            }

            if (originalEdge != nullptr)
            {
                // Delete originalEdge if it hasn't been replaced yet.
                edges.removeEdge(edgeID);
            }

            edgesSplit = true;
        } while (getNextGroup(intersections.end(), group, indexer));
    }

    intersections.clear();

    return edgesSplit;
}

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
        // Create an equation of a line passing through the new sweep position.
        _sweepLine = LineEq2D::createHorizontal(_sweepPosition->getRealPosition().getY());
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
SweepEdge::SweepEdge(NodeCPtr node) :
    _edge(nullptr),
    _edgeLine(),
    _lastSweepOffset(0),
    _cachedSweepIntersection(0),
    _isColinear(false)
{
    // Create a line parallel to the sweep direction passing through the node.
    _edgeLine = LineEq2D::createVertical(node->getRealPosition().getX());
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

//! @brief Gets the node on the sweep edge which appears earliest in the sweep.
//! @return A valid node or nullptr if the edge was created from the current
//! sweep position node.
NodePtr SweepEdge::getEarliestNode() const
{
    // The edge direction was set to be in the direction of the sweep in the constructor.
    return (_edge == nullptr) ? nullptr : _edge->getStartNode();
}

//! @brief Gets the node on the sweep edge which appears latest in the sweep.
//! @return A valid node or nullptr if the edge was created from the current
//! sweep position node.
NodePtr SweepEdge::getLatestNode() const
{
    // The edge direction was set to be in the direction of the sweep in the constructor.
    return (_edge == nullptr) ? nullptr : _edge->getEndNode();
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
    _sortedEdges.reserve(32);
    _horizontalEdges.reserve(16);
}

//! @brief Gets the position of the edge on the left-most side of the sweep line.
SweepEdgeIter SweepStatus::begin() { return _sortedEdges.begin(); }

//! @brief Gets the position of the edge just after the right-most side of
//! the sweep line.
SweepEdgeIter SweepStatus::end() { return _sortedEdges.end(); }

//! @brief Determines of the there are currently no edges in the sweep.
//! @retval true The sweep is currently empty.
//! @retval false The sweep contains at least one edge.
bool SweepStatus::isEmpty() const noexcept
{
    return _sortedEdges.empty() && _horizontalEdges.empty();
}

//! @brief Determines whether there are any non-horizontal edges in the
//! current sweep state.
//! @retval true At least one non-horizontal edge intersects the sweep line.
//! @retval false No non-horizontal edges intersect the horizontal sweep line.
bool SweepStatus::hasDiagonalEdges() const noexcept
{
    return _sortedEdges.empty() == false;
}

//! @brief Determines whether there are any horizontal edges in the current
//! sweep state.
//! @retval true There is at least one horizontal edge on the sweep.
//! @retval false There are no horizontal edges in the sweep.
bool SweepStatus::hasHorizontalEdges() const noexcept
{
    return _horizontalEdges.empty() == false;
}

//! @brief Gets the right-most node of any horizontal edge in the sweep.
//! @return Either the right-most edge, or nullptr if there are no horizontal
//! edges at the sweep.
NodePtr SweepStatus::getRightMostHorizontal() const
{
    return _horizontalEdges.empty() ? nullptr : _horizontalEdges.back().getLatestNode();
}

//! @brief Searches for the first non-horizontal edge in the sweep which
//! intersects the sweep line after a specific node.
//! @param[in] position The node position to search for.
//! @param[out] nextEdge Receives the edge at the next greatest X position from
//! the node at @p position.
//! @retval true An edge was found with an intersections with the horizontal
//! sweep line that has an X value greater than that of @p node.
//! @retval false There are no non-horizontal edges after @p node on the
//! sweep line.
bool SweepStatus::tryFindDiagonalEdgeAfterNode(NodePtr position, SweepEdgeIter &nextEdge)
{
    SweepEdge key(position);

    nextEdge = std::upper_bound(_sortedEdges.begin(), _sortedEdges.end(),
                                key, CompareSweepElements(_context));

    return nextEdge != _sortedEdges.end();
}

//! @brief Searches for the range of edges at the current sweep position.
//! @return A range of sweep edge iterators.
SweepRange SweepStatus::findEdgesAtSweep()
{
    NodeCPtr sweepNode = _context.getSweepNode();
    SweepEdge key(sweepNode);
    auto keyOffset = sweepNode->getGridPosition().getX();
    auto minKeyOffset = keyOffset - 1;
    auto maxKeyOffset = keyOffset + 1;

    auto resultRange = std::equal_range(_sortedEdges.begin(), _sortedEdges.end(), key,
                                        CompareSweepElements(_context));

    // Extend the range to allow for grid inaccuracy.
    while (resultRange.first != _sortedEdges.begin())
    {
        auto pos = resultRange.first;
        --pos;

        auto edgeOffset = pos->getSweepIntersection(_context).getX();

        if (edgeOffset < minKeyOffset)
            break;

        resultRange.first = pos;
    }

    while (resultRange.second != _sortedEdges.end())
    {
        auto edgeOffset = resultRange.second->getSweepIntersection(_context).getX();

        if (edgeOffset > maxKeyOffset)
            break;

        ++resultRange.second;
    }

    return resultRange;
}

//! @brief Adds a non-horizontal edge to the set intersecting the sweep line.
//! @param[in] edge The edge to add.
//! @return The position of the edge in the sweep.
//! @throws ArgumentException If @p edge is horizontal.
SweepEdgeIter SweepStatus::addDiagonalEdge(EdgePtr edge)
{
    SweepEdge edgeToAdd(_context, edge);

    if (edgeToAdd.isColinear())
    {
        throw ArgumentException("The edge is horizontal.", "edge");
    }

    // The edge is diagonal, insert it at the correct location.
    auto insertionPos = std::upper_bound(_sortedEdges.begin(), _sortedEdges.end(),
                                         edgeToAdd, InsertionSweepDiagonalComparer(_context));

    return _sortedEdges.insert(insertionPos, edgeToAdd);
}

//! @brief Adds a horizontal edge to the sweep.
//! @param[in] edge The horizontal edge to add.
//! @return The position of the newly inserted edge.
//! @throws ArgumentException If @p edge is not horizontal.
SweepEdgeIter SweepStatus::addHorizontalEdge(EdgePtr edge)
{
    SweepEdge edgeToAdd(_context, edge);

    if (edgeToAdd.isColinear() == false)
    {
        throw ArgumentException("The edges is not horizontal.", "edge");
    }

    // Insert the edge at a position defined by the end which is furthest along
    // the sweep (right-most).
    auto insertionPos = std::upper_bound(_horizontalEdges.begin(),
                                         _horizontalEdges.end(),
                                         edgeToAdd, HorzSweepEdgeInsertionComparer());

    return _horizontalEdges.insert(insertionPos, edgeToAdd);
}

//! @brief Removes a diagonal edge from the sweep.
//! @param[in] edgePos The position of the edge to remove.
//! @return The position of the diagonal edge after the one removed.
SweepEdgeIter SweepStatus::removeEdge(SweepEdgeIter edgePos)
{
    return _sortedEdges.erase(edgePos);
}

//! @brief Removes a horizontal edge from the sweep.
//! @param[in] edge The edge to remove.
void SweepStatus::removeHorizontalEdge(EdgePtr edge)
{
    _horizontalEdges.front().getEdge()->getParent();

    auto last = std::remove_if(_horizontalEdges.begin(), _horizontalEdges.end(),
                               [edge](const SweepEdge &sweepEdge) {
                                    return sweepEdge.getEdge()->getParent() == edge;
                               });

    _horizontalEdges.erase(last, _horizontalEdges.end());
}

//! @brief Removes an edge from the sweep.
//! @param[in] edgeToRemove The edge to remove, possibly parallel to the sweep.
//! @return The iterator after the diagonal edge removed or the end of the
//! diagonal edge collection is the edge was parallel to the sweep.
SweepEdgeIter SweepStatus::removeEdge(HalfEdgeCPtr edgeToRemove)
{
    auto rangePair = findEdgesAtSweep();
    EdgePtr targetEdge = edgeToRemove->getParent();

    for (auto pos = rangePair.Begin; pos != rangePair.End; ++pos)
    {
        if (pos->getEdge()->getParent() == targetEdge)
        {
            return _sortedEdges.erase(pos);
        }
    }

    return _sortedEdges.end();
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
    _context(context),
    _comparer(context)
{
}

//! @brief Creates an event queue with an initial set of events.
//! @param[in] context An object defining the sweep environment.
//! @param[in] initialEvents An unsorted array of events to copy.
//! @param[in] eventCount The count of elements in @p initialEvents.
SweepEventQueue::SweepEventQueue(const SweepContext &context,
                                 const SweepEvent *initialEvents,
                                 size_t eventCount) :
    _context(context),
    _comparer(context)
{
    if (eventCount > 0)
    {
        // Copy the events en-mass.
        std::copy_n(initialEvents, eventCount,
                    std::back_inserter(_sortedEvents));

        // Sort the events all at once.
        std::sort(_sortedEvents.begin(), _sortedEvents.end(), _comparer);
    }
}

//! @brief Determines if there are no events in the queue.
bool SweepEventQueue::isEmpty() const noexcept
{
    return _sortedEvents.empty();
}

//! @brief Attempts to add an event to the queue which is unique in the node it
//! refers to and the type of event described.
//! @param[in] eventToAdd The event to try to add.
//! @retval true The event was added to the queue.
//! @retval false The event was already present in the queue so no change was made.
bool SweepEventQueue::tryAddUniqueEvent(const SweepEvent &eventToAdd)
{
    // Find the position of the event after any matching one.
    auto pos = std::upper_bound(_sortedEvents.begin(), _sortedEvents.end(),
                                eventToAdd, _comparer);
    bool wasUnique = false;

    if (pos == _sortedEvents.begin())
    {
        // There cannot be a matching event.
        _sortedEvents.insert(pos, eventToAdd);
        wasUnique = true;
    }
    else
    {
        // The matching event, if there is one, proceeds pos.
        auto previous = std::prev(pos);

        if ((previous->getEventNode() != eventToAdd.getEventNode()) ||
            (previous->getEventType() != eventToAdd.getEventType()))
        {
            // The proceeding event didn't match, so insert the new one.
            _sortedEvents.insert(pos, eventToAdd);
            wasUnique = true;
        }
    }

    return wasUnique;
}

//! @brief Inserts an event into the correct position in the queue.
//! @param[in] eventToInsert The event to insert.
void SweepEventQueue::insertEvent(const SweepEvent &eventToInsert)
{
    auto insertionPos = std::upper_bound(_sortedEvents.begin(),
                                         _sortedEvents.end(), eventToInsert,
                                         _comparer);

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

//! @brief Processes all edges in an edge table to find intersections, splitting
//! edges and adding nodes to represent them.
//! @param[in] nodes The table of nodes to add to.
//! @param[in] edges The table of edges to scan and add to.
//! @retval true At least one intersection was found which split edges, the
//! intersection in question may have been an existing node.
//! @retval false No edges were split due to intersection.
bool findAllIntersections(NodeTable &nodes, EdgeTable &edges)
{
    SweepContext context(nodes);

    // Stoke an event queue with a start and end event for every edge.
    SweepEventCollection initialEvents;
    initialEvents.reserve(edges.getCount() * 2);

    AccumulateEdgeEvents accumulator(context, initialEvents);
    edges.forEachEdge(accumulator);

    SweepEventQueue eventQueue(context, initialEvents.data(), initialEvents.size());
    initialEvents.clear();

    // Process the events, adding and processing intersections as we go.
    IDToIDMappingCollection splitNodesByEdgeID;
    splitNodesByEdgeID.reserve(32);

    SweepStatus state(context);
    SweepEvent currentEvent;
    bool intersectionsFound = false;

    while (eventQueue.tryPopEvent(currentEvent))
    {
        // Move the sweep to the position of the next event.
        NodePtr eventNode = currentEvent.getEventNode();
        auto eventType = static_cast<IntersectionEventType>(currentEvent.getEventType());

        // Move to the next sweep location.
        context.setSweepNode(eventNode);

        // Process any batched intersections, if we can.
        if (state.isEmpty() && (splitNodesByEdgeID.empty() == false))
            intersectionsFound |= splitEdgesAtIntersections(nodes, edges, splitNodesByEdgeID);

        // Process the event by type.
        if (eventType == IntersectionEventType::DiagonalEdgeStarting)
        {
            // Add the edge to the sweep state.
            auto pos = state.addDiagonalEdge(currentEvent.getEdge());

            // Check pos with pos - 1 for intersection.
            if ((pos != state.end()) && (pos != state.begin()))
            {
                checkForIntersection(nodes, *std::prev(pos), *pos,
                                     eventNode, eventQueue);
            }

            // Check pos with pos + 1 for intersection.
            auto next = std::next(pos);

            if (next != state.end())
            {
                checkForIntersection(nodes, *pos, *next, eventNode, eventQueue);
            }

            // Check for intersections with horizontal edges.
            if (state.hasHorizontalEdges())
            {
                // All horizontal edges still on the sweep pass through the
                // current node. If this isn't the start or end point for at
                // least one of those horizontal edges, this should be an
                // intersection for something.
                SweepEvent intersectionEvent(eventNode, IntersectionEventType::Intersection);

                // Processing the intersection event should filter out any
                // intersections with horizontal start/end points.
                eventQueue.tryAddUniqueEvent(intersectionEvent);
            }
        }
        else if (eventType == IntersectionEventType::HorizontalEdgeStarting)
        {
            if (state.hasHorizontalEdges())
            {
                // Check for intersections with all other horizontal edges.
                SweepEdge newEdge(context, currentEvent.getEdge());

                for (const SweepEdge &horzEdge : state.getHorizontalEdgesInSweep())
                {
                    checkForIntersection(nodes, horzEdge, newEdge, eventNode, eventQueue);
                }
            }

            // Add the new horizontal edge.
            SweepEdge &horzEdge = *state.addHorizontalEdge(currentEvent.getEdge());
            SweepEdgeIter nextEdge;

            if (state.tryFindDiagonalEdgeAfterNode(eventNode, nextEdge))
            {
                // Check the node immediately right of the point where the
                // horizontal edge starts and see if there is an intersecting
                // edge there.
                checkForIntersection(nodes, horzEdge, *nextEdge, eventNode, eventQueue);
            }
        }
        else if (eventType == IntersectionEventType::DiagonalEdgeEnding)
        {
            auto pos = state.removeEdge(currentEvent.getDirectedEdge());

            // Check the new neighbours for intersection.
            if (pos != state.end())
            {
                // There is an edge after the one removed.
                if (pos != state.begin())
                {
                    checkForIntersection(nodes, *std::prev(pos), *pos,
                                         eventNode, eventQueue);
                }

                // Check to see if horizontal edges intersect with
                // the new neighbour on the right.
                checkForHorizontalIntersection(context, nodes,
                                               state.getRightMostHorizontal(),
                                               *pos, eventQueue);
            }
        }
        else if (eventType == IntersectionEventType::HorizontalEdgeEnding)
        {
            state.removeHorizontalEdge(currentEvent.getEdge());
        }
        else // if (eventType == IntersectionEventType::Intersection)
        {
            auto edgesAtSweep = state.findEdgesAtSweep();

            // Note all of these edges as intersecting at the current node if
            // it does not represent one of their end points.
            ID nodeID = eventNode->getID();

            if (edgesAtSweep.isEmpty() == false)
            {
                // Process diagonal edges at the node.
                size_t intersectionCount = splitNodesByEdgeID.size();

                for (const SweepEdge &edgeAtNode : edgesAtSweep)
                {
                    auto edge = edgeAtNode.getEdge()->getParent();

                    // Ignore edges which already start or end at this node.
                    if (edge->hasNode(eventNode))
                        continue;

                    splitNodesByEdgeID.emplace_back(edge->getID(), nodeID);
                }

                if ((edgesAtSweep.getCount() > 1) &&
                    (splitNodesByEdgeID.size() > intersectionCount))
                {
                    // All the diagonal edges at the current node will swap their order
                    // on the sweep line after this node.
                    std::reverse(edgesAtSweep.Begin, edgesAtSweep.End);

                    // Compare the new outlier edges with their neighbours for
                    // intersection.
                    if (edgesAtSweep.End != state.end())
                    {
                        checkForIntersection(nodes, *std::prev(edgesAtSweep.End),
                                             *edgesAtSweep.End, eventNode, eventQueue);
                    }

                    if (edgesAtSweep.Begin != state.begin())
                    {
                        checkForIntersection(nodes, *std::prev(edgesAtSweep.Begin),
                                             *edgesAtSweep.Begin, eventNode, eventQueue);
                    }
                }
            }

            if (state.hasHorizontalEdges())
            {
                // Process horizontal edges at the node.
                size_t intersectionCount = splitNodesByEdgeID.size();

                for (const SweepEdge &edgeAtNode : state.getHorizontalEdgesInSweep())
                {
                    auto edge = edgeAtNode.getEdge()->getParent();

                    // Ignore edges which already start or end at this node.
                    if (edge->hasNode(eventNode))
                        continue;

                    splitNodesByEdgeID.emplace_back(edge->getID(), nodeID);
                }

                if (splitNodesByEdgeID.size() > intersectionCount)
                {
                    // We added at least one horizontal intersection. Check for further
                    // horizontal intersections with right neighbours.
                    if (edgesAtSweep.End != state.end())
                    {
                        checkForHorizontalIntersection(context, nodes,
                                                       state.getRightMostHorizontal(),
                                                       *edgesAtSweep.End, eventQueue);
                    }
                }
            }
        }
    }

    // Process final batch of edges to be split.
     intersectionsFound |= splitEdgesAtIntersections(nodes, edges, splitNodesByEdgeID);

    return intersectionsFound;
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

