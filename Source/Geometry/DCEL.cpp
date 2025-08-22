//! @file Geometry/DCEL.cpp
//! @brief The definition of a doubly-Connected Edge List and child data
//! structures used in geometry algorithms.
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

#include "Ag/Geometry/DCEL.hpp"
#include "Ag/Geometry/DCEL_Algorithms.hpp"
#include "DCEL_RingTracer.hpp"
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

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

} // Anonymous namespace


////////////////////////////////////////////////////////////////////////////////
// InvalidNodeIDException Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an exception describing the use of an invalid
//! node identifier.
//! @param[in] id The invalid node identifier.
InvalidNodeIDException::InvalidNodeIDException(ID id)
{
    std::string detail;
    Ag::appendFormat("DCEL node identifier #{0} is invalid.", detail, { id });

    initialise("InvalidNodeIDException",
               "An attempt was made to access a node in a doubly-connected "
               "edge list using an invalid identifier.",
               detail, id);
}

////////////////////////////////////////////////////////////////////////////////
// InvalidEdgeIDException Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an exception describing the use of an invalid
//! edge identifier.
//! @param[in] id The invalid edge identifier.
InvalidEdgeIDException::InvalidEdgeIDException(ID id)
{
    std::string detail;
    Ag::appendFormat("DCEL edge identifier #{0} is invalid.", detail, { id });

    initialise("InvalidEdgeIDException",
               "An attempt was made to access an edge in a doubly-connected "
               "edge list using an invalid identifier.",
               detail, id);
}

////////////////////////////////////////////////////////////////////////////////
// InvalidHalfEdgeIDException Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an exception describing the use of an invalid
//! half-edge identifier.
//! @param[in] id The invalid half-edge identifier.
InvalidHalfEdgeIDException::InvalidHalfEdgeIDException(const HalfEdgeID &id)
{
    std::string detail;
    Ag::appendFormat("DCEL half-edge identifier #{0}/{1} is invalid.", detail,
                     { id.getEdgeID(), id.getDirectionIndex() });

    initialise("InvalidHalfEdgeIDException",
               "An attempt was made to access a half-edge in a doubly-connected "
               "edge list using an invalid identifier.",
               detail);
}

////////////////////////////////////////////////////////////////////////////////
// Node Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a new node.
//! @param[in] id The unique identifier of the node.
//! @param[in] position The actual position of the node in space.
//! @param[in] gridPosition A rounded representation of position used for indexing.
Node::Node(ID id, const Point2D &position, const SnapPoint &gridPosition) :
    _id(id),
    _mappedIndex(0),
    _realPosition(position),
    _gridPosition(gridPosition),
    _buddyEdge(nullptr),
    _flags(0)
{
}

//! @brief Sets the edge to associate with the node.
//! @param[in] buddyEdge A pointer to the associated edge.
void Node::setBuddyEdge(Edge *buddyEdge) noexcept { _buddyEdge = buddyEdge; }

//! @brief Sets the index used to refer to the vertex when outputting vertices.
//! @param[in] index The vertex index to map to this node.
void Node::setMappedIndex(ID index) noexcept { _mappedIndex = index; }

//! @brief Gets the physical position of this node in 2D space.
const Point2D &Node::getRealPosition() const noexcept { return _realPosition; }

//! @brief Gets the position of this node in the snapping grid.
const SnapPoint &Node::getGridPosition() const noexcept { return _gridPosition; }

////////////////////////////////////////////////////////////////////////////////
// NodeTable Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty node table with estimated extents between
//! (0.0, 0.0) and (1.0, 1.0).
NodeTable::NodeTable() :
    _grid(Rect2D(0, 0, 1, 1)),
    _idSeed(0)
{
}

//! @brief Constructs an indexed table of nodes.
//! @param[in] estimatedBounds The estimated physical bounds of the points which
//! the table will contain.
//! @param[in] nodeCountHint An optional count of the number of nodes which the
//! table might contain.
NodeTable::NodeTable(const Rect2D &estimatedBounds, size_t nodeCountHint /*= 0*/) :
    _grid(estimatedBounds),
    _idSeed(0)
{
    reset(estimatedBounds, nodeCountHint);
}

//! @brief Determines if the table contains zero nodes.
//! @retval true The table contains no nodes.
//! @retval false The table contains at least one node.
bool NodeTable::isEmpty() const noexcept
{
    return _allNodes.empty();
}

//! @brief Gets the count of active nodes in the table.
//! @return The count of not-deleted nodes in the table.
uint32_t NodeTable::getCount() const noexcept
{
    return static_cast<uint32_t>(_allNodes.size());
}

//! @brief Gets the grid used to snap points.
const SnapContext &NodeTable::getGrid() const noexcept
{
    return _grid;
}

//! @brief Calculates a rectangle encompassing all nodes in the table.
Rect2D NodeTable::calculateExtents() const
{
    if (_allNodes.empty())
        return { };

    Rect2D extents(_allNodes.front()->getRealPosition());

    for (const auto &node : _allNodes)
    {
        extents.combineTo(node->getRealPosition());
    }

    return extents;
}

//! @brief Resets the object to an empty state.
void NodeTable::clear()
{
    _nodesByID.clear();
    _nodesByPosition.clear();;
    _allNodes.clear();
    _idSeed = 0;
}

//! @brief Sets the object to an empty state and resets it ready to receive
//! new geometry.
//! @param[in] estimatedBounds The estimated physical bounds of the points which
//! the table will contain.
//! @param[in] nodeCountHint An optional count of the number of nodes which the
//! table might contain.
void NodeTable::reset(const Rect2D &estimatedBounds, size_t /*nodeCountHint = 0*/)
{
    clear();
    _grid = SnapContext(estimatedBounds);
}

//! @brief Gets a node based on its unique identifier.
//! @param[in] nodeID The identifier of the node to get.
//! @return A reference to the node.
//! @throw InvalidNodeIDException If nodeID is invalid.
Node &NodeTable::operator[](ID nodeID)
{
    NodePtr node;

    if (tryFindNodeByID(nodeID, node))
    {
        return *node;
    }

    throw InvalidNodeIDException(nodeID);
}

//! @brief Gets a node based on its unique identifier.
//! @param[in] nodeID The identifier of the node to get.
//! @return A reference to the node.
//! @throw InvalidNodeIDException If nodeID is invalid.
const Node &NodeTable::operator[](ID nodeID) const
{
    NodeCPtr node;

    if (tryFindNodeByID(nodeID, node))
    {
        return *node;
    }

    throw InvalidNodeIDException(nodeID);
}

//! @brief Attempts to find a node based on its unique identifier.
//! @param[in] nodeID The identifier of the node to find.
//! @param[out] node Receives a pointer to the node, if it was found.
//! @retval true The node was found and its pointer returned.
//! @retval false A node with the specified identifier was not found.
bool NodeTable::tryFindNodeByID(ID nodeID, NodePtr &node)
{
    auto pos = _nodesByID.find(nodeID);

    node = (pos == _nodesByID.end()) ? nullptr : pos->second;

    return node != nullptr;
}

//! @brief Attempts to find a node based on its unique identifier.
//! @param[in] nodeID The identifier of the node to find.
//! @param[out] node Receives a pointer to the node, if it was found.
//! @retval true The node was found and its pointer returned.
//! @retval false A node with the specified identifier was not found.
bool NodeTable::tryFindNodeByID(ID nodeID, NodeCPtr &node) const
{
    auto pos = _nodesByID.find(nodeID);

    node = (pos == _nodesByID.end()) ? nullptr : pos->second;

    return node != nullptr;
}

//! @brief Attempts to find a node based on its position.
//! @param[in] realPosition The position of the node to find.
//! @param[out] node Receives a pointer to the node, if it was found.
//! @retval true The node was found and its pointer returned.
//! @retval false A node at or near-enough to the specified position
//! was not found.
bool NodeTable::tryFindNodeByPosition(const Point2D &realPosition,
                                      NodePtr &node)
{
    // Snap the point to find to the grid.
    SnapPoint gridPosition = _grid.snapPoint(realPosition);

    // Search based on the snapped position.
    auto pos = _nodesByPosition.find(gridPosition);

    node = (pos == _nodesByPosition.end()) ? nullptr : pos->second;

    return node != nullptr;
}

//! @brief Attempts to find a node based on its position.
//! @param[in] realPosition The position of the node to find.
//! @param[out] node Receives a pointer to the node, if it was found.
//! @retval true The node was found and its pointer returned.
//! @retval false A node at or near-enough to the specified position
//! was not found.
bool NodeTable::tryFindNodeByPosition(const Point2D &realPosition,
                                      NodeCPtr &node) const
{
    // Snap the point to find to the grid.
    SnapPoint gridPosition = _grid.snapPoint(realPosition);

    // Search based on the snapped position.
    auto pos = _nodesByPosition.find(gridPosition);

    node = (pos == _nodesByPosition.end()) ? nullptr : pos->second;

    return node != nullptr;
}

//! @brief Gets an iterator pointing to the first node in Y-major position ordering.
NodeTable::NodeGridCIter NodeTable::beginByPosition() const
{
    return _nodesByPosition.begin();
}

//! @brief Gets an iterator pointing to after the last node in Y-major
//! position ordering.
NodeTable::NodeGridCIter NodeTable::endByPosition() const
{
    return _nodesByPosition.end();
}

//! @brief Gets an iterator pointing to the first mapping of ID to
//! node pointer.
NodeTable::NodeIDCIter NodeTable::beginByID() const
{
    return _nodesByID.begin();
}

//! @brief Gets an iterator pointing to after the last mapping of ID to
//! node pointer.
NodeTable::NodeIDCIter NodeTable::endByID() const
{
    return _nodesByID.end();
}

//! @brief Adds or gets a node.
//! @param[in] realPosition The position of the node to add.
//! @return A reference to the node, possibly newly created.
Node &NodeTable::addNode(const Point2D &realPosition)
{
    SnapPoint gridPosition = _grid.snapPoint(realPosition);

    auto pos = _nodesByPosition.find(gridPosition);

    if (pos == _nodesByPosition.end())
    {
        // No node exists at that position, insert one.
        _allNodes.emplace_back(std::make_unique<Node>(_idSeed++, realPosition, gridPosition));

        // Update indexes.
        NodePtr newNode = _allNodes.back().get();
        _nodesByID[newNode->getID()] = newNode;
        _nodesByPosition[gridPosition] = newNode;

        return *newNode;
    }
    else
    {
        // A node at that position already exists, return it.
        return *pos->second;
    }
}

//! @brief Removes the node with the specified identifier.
//! @param[in] nodeID The identifier of the node to remove.
void NodeTable::removeNode(ID nodeID)
{
    // TODO: Linear search, not optimal.
    auto matches = [nodeID](const NodeUPtr &rhs) {
        return rhs && rhs->getID() == nodeID;
        };

    auto pos = std::find_if(_allNodes.begin(), _allNodes.end(),
                            [nodeID](const NodeUPtr &rhs) {
                                return rhs && rhs->getID() == nodeID; });

    if (pos != _allNodes.end())
    {
        _nodesByID.erase(nodeID);
        _nodesByPosition.erase(pos->get()->getGridPosition());
        _allNodes.erase(pos);
    }
}


////////////////////////////////////////////////////////////////////////////////
// HalfEdge Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a half-edge identifier with a null value.
HalfEdgeID::HalfEdgeID() :
    _id(NullID)
{
}

//! @brief Constructs a half-edge identifier initialised with raw IDs.
//! @param[in] edgeID The identifier of the parent edge.
//! @param[in] directionIndex The direction of traversal along the edge.
HalfEdgeID::HalfEdgeID(ID edgeID, DirectionIndex directionIndex) :
    _id((edgeID & EdgeIDMask) | (static_cast<ID>(directionIndex) << DirectionShift))
{
}

//! @brief Constructs a half-edge identifier from a half-edge object.
//! @param[in] halfEdge The half-edge to identify.
HalfEdgeID::HalfEdgeID(const HalfEdge &halfEdge) :
    _id((halfEdge.getEdgeID() & EdgeIDMask) |
        (static_cast<ID>(halfEdge.getDirectionIndex()) << DirectionShift))
{
}

//! @brief Gets the identifier of the directed edge co-linear with the referenced
//! one, but travelling in the opposite direction.
HalfEdgeID HalfEdgeID::getReverseID() const noexcept
{
    // Create a copy of the current ID.
    HalfEdgeID reversed(*this);

    // Flip the direction bit.
    reversed._id ^= (1u << DirectionShift);

    return reversed;
}

////////////////////////////////////////////////////////////////////////////////
// HalfEdge Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty directed edge. The setParent() member function
//! must be called for the object to be in a valid state.
HalfEdge::HalfEdge() :
    _parent(nullptr),
    _index(0),
    _ring(NullID)
{
}

//! @brief Gets the unique identifier of this directed edge.
HalfEdgeID HalfEdge::getID() const noexcept { return HalfEdgeID(*this); }

//! @brief Gets the identifier of the edge which owns this half-edge.
ID HalfEdge::getEdgeID() const noexcept { return _parent->_id; }

//! @brief Gets the identifier of the node at the beginning of the edge.
ID HalfEdge::getStartNodeID() const noexcept
{
    return _parent->_nodes[_index]->getID();
}

//! @brief Gets the identifier of the node at the end of the edge.
ID HalfEdge::getEndNodeID() const noexcept
{
    return _parent->_nodes[_index ^ 1]->getID();
}

//! @brief Gets a pointer to the node defining the start point of the edge.
NodePtr HalfEdge::getStartNode() const noexcept
{
    return _parent->_nodes[_index];
}

//! @brief Gets a pointer to the node defining the end point of the edge.
NodePtr HalfEdge::getEndNode() const noexcept
{
    return _parent->_nodes[_index ^ 1];
}

//! @brief Sets the identifier of the ring for which the edge forms a part of
//! the perimeter.
//! @param[in] ring The identifier of the ring or NullID
void HalfEdge::setRingID(ID ring) noexcept { _ring = ring; }

//! @brief Sets the previous edge on the ring this edge belongs to.
HalfEdge *HalfEdge::getPreviousEdge() const noexcept { return _prevEdge; }

//! @brief Sets the previous edge on the ring this edge belongs to.
//! @param[in] prevEdge The new predecessor edge.
void HalfEdge::setPreviousEdge(HalfEdge *prevEdge) noexcept { _prevEdge = prevEdge; }

//! @brief Sets the next edge on the ring this edge belongs to.
HalfEdge *HalfEdge::getNextEdge() const noexcept { return _nextEdge; }

//! @brief Sets the next edge on the ring this edge belongs to.
//! @param[in] nextEdge A pointer to the successor edge.
void HalfEdge::setNextEdge(HalfEdge *nextEdge) noexcept { _nextEdge = nextEdge; }

//! @brief Gets the identifier of the directed edge which proceeds the current
//! one in a chain, possibly as part of a ring perimeter.
HalfEdgeID HalfEdge::getPreviousEdgeID() const noexcept
{
    return (_prevEdge == nullptr) ? HalfEdgeID() : _prevEdge->getID();
}

//! @brief Gets the identifier of the directed edge which succeeds the current
//! one in a chain, possibly as part of a ring perimeter.
HalfEdgeID HalfEdge::getNextEdgeID() const noexcept
{
    return (_nextEdge == nullptr) ? HalfEdgeID() : _nextEdge->getID();
}

//! @brief Gets the directed edge connecting the same nodes, but travelling in
//! the opposite direction.
HalfEdgePtr HalfEdge::getReverse() noexcept
{
    return _parent->_directions + (_index ^ 1);
}

//! @brief Gets the directed edge connecting the same nodes, but travelling in
//! the opposite direction.
HalfEdgeCPtr HalfEdge::getReverse() const noexcept
{
    return _parent->_directions + (_index ^ 1);
}

//! @brief Gets the angle of the edge from its start to its end.
//! @return The angle in radians, LH CCW relative to the X axis.
Angle HalfEdge::getAngle() const
{
    return Angle(_parent->_angle + (Angle::Pi * _index));
}

//! @brief Resets the previous/next edge IDs and ring ID to null values.
void HalfEdge::resetConnections()
{
    _prevEdge = _nextEdge = nullptr;
    _ring = NullID;
}

//! @brief Connects a directed edge to this one as successor or predecessor.
//! @param[in] linkedEdge The edge to link which must share a node with the
//! current edge.
void HalfEdge::linkEdges(HalfEdge *linkedEdge)
{
    if (linkedEdge == nullptr)
    {
        throw Ag::ArgumentException("linkedEdge");
    }
    else if ((linkedEdge == this) || (linkedEdge == getReverse()))
    {
        // Error: Cannot link co-linear edges.
        throw Ag::OperationException("A directed edge cannot be linked to a co-linear edge.");
    }
    else if (linkedEdge->getStartNodeID() == getEndNodeID())
    {
        // The linked edge is the successor.
        _nextEdge = linkedEdge;
        linkedEdge->_prevEdge = this;
    }
    else if (linkedEdge->getEndNodeID() == getStartNodeID())
    {
        // The linked edge is the predecessor.
        linkedEdge->_nextEdge = this;
        _prevEdge = linkedEdge;
    }
    else
    {
        // Error: The edges aren't connected.
        throw Ag::OperationException("A directed edge cannot be liked to "
                                     "an edge which doesn't share a node.");
    }
}

//! @brief Assigns a parent edge and direction to this half-edge.
//! @param[in] parent A pointer to the parent edge.
//! @param[in] index Either 0 or 1 to indicate the direction of travel of the
//! current edge along its parent.
void HalfEdge::setParent(Edge *parent, DirectionIndex index)
{
    if (index > 1)
    {
        throw Ag::IndexOutOfRangeException(static_cast<uintptr_t>(index),
                                           static_cast<uintptr_t>(1));
    }

    _parent = parent;
    _index = index;
}

////////////////////////////////////////////////////////////////////////////////
// Edge Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a copy of an undirected edge.
//! @param[in] rhs The edge to copy.
Edge::Edge(const Edge &rhs) :
    _id(rhs._id),
    _angle(0.0)
{
    copyEdge(rhs);
}

//! @brief Moves an undirected edge to a new object.
//! @param[in] rhs The edge to copy.
Edge::Edge(Edge &&rhs) noexcept :
    _id(rhs._id),
    _angle(0.0)
{
    moveEdge(std::move(rhs));
}

//! @brief Constructs a connection between nodes.
//! @param[in] edgeID The unique identifier of the connection.
//! @param[in] firstNode A pointer to the first node being connected.
//! @param[in] secondNode A pointer to the second node being connected.
//! @throws Ag::ArgumentException If firstNode == secondNode.
Edge::Edge(ID edgeID, NodePtr firstNode, NodePtr secondNode) :
    _id(edgeID),
    _angle(0.0),
    _associatedNode(nullptr)
{
    if (firstNode == secondNode)
    {
        throw Ag::ArgumentException("An edge must be defined as connecting two different nodes.",
                                    "firstNode");
    }
    else if (firstNode == nullptr)
    {
        throw Ag::ArgumentNullException("firstNode");
    }
    else if (secondNode == nullptr)
    {
        throw Ag::ArgumentNullException("secondNode");
    }

    _nodes[0] = firstNode;
    _nodes[1] = secondNode;

    // Initialise directed edges based on this edge as their parent.
    _directions[0].setParent(this, 0);
    _directions[1].setParent(this, 1);

    // Calculate the angle of the edge once, here.
    _angle = firstNode->getRealPosition().angleTo(secondNode->getRealPosition());
}

//! @brief Gets the half-edge which traverses this edge in a specified direction.
//! @param[in] index The direction index (either 0 or 1).
//! @return The child directed edge.
HalfEdge *Edge::getHalfEdge(DirectionIndex index) noexcept
{
    return _directions + index;
}

//! @brief Gets the half-edge which traverses this edge in a specified direction.
//! @param[in] index The direction index (either 0 or 1).
//! @return The child directed edge.
const HalfEdge *Edge::getHalfEdge(DirectionIndex index) const noexcept
{
    return _directions + index;
}

//! @brief Gets the directed edge proceeding from the specified node.
//! @param[in] node The identifier of a node defining the edge.
//! @return The directed edge with node at its start.
//! @note If node does not identify a node on the current edge,
//! an edge will still be returned and no error raised.
HalfEdge *Edge::getHalfEdgeFrom(ID node) noexcept
{
    return (_nodes[0]->getID() == node) ? _directions : (_directions + 1);
}

//! @brief Gets the directed edge proceeding from the specified node.
//! @param[in] node The identifier of a node defining the edge.
//! @return The directed edge with node at its start.
//! @note If node does not identify a node on the current edge,
//! an edge will still be returned and no error raised.
const HalfEdge *Edge::getHalfEdgeFrom(ID node) const noexcept
{
    return (_nodes[0]->getID() == node) ? _directions : (_directions + 1);
}

//! @brief Gets the directed edge incident to the specified node.
//! @param[in] node The identifier of a node defining the edge.
//! @return The directed edge with node at its end.
//! @note If node does not identify a node on the current edge,
//! an edge will still be returned and no error raised.
HalfEdge *Edge::getHalfEdgeTo(ID node) noexcept
{
    return (_nodes[1]->getID() == node) ? (_directions + 1) : _directions;
}

//! @brief Gets the directed edge incident to the specified node.
//! @param[in] node The identifier of a node defining the edge.
//! @return The directed edge with node at its end.
//! @note If node does not identify a node on the current edge,
//! an edge will still be returned and no error raised.
const HalfEdge *Edge::getHalfEdgeTo(ID node) const noexcept
{
    return (_nodes[1]->getID() == node) ? (_directions + 1) : _directions;
}

//! @brief Annotates the edge with an arbitrary node.
//! @param[in] node The node to associate with the edge.
void Edge::setAssociatedNode(NodePtr node)
{
    _associatedNode = node;
}

//! @brief Copy assigns an edge to overwrite the current edge.
//! @param[in] rhs The edge to copy.
//! @return A reference to the current edge.
Edge &Edge::operator=(const Edge &rhs) noexcept
{
    copyEdge(rhs);

    return *this;
}

//! @brief Moves an edge to overwrite the current edge.
//! @param[in] rhs The edge to copy.
//! @return A reference to the current edge.
Edge &Edge::operator=(Edge &&rhs) noexcept
{
    moveEdge(std::move(rhs));

    return *this;
}

//! @brief Resets the previous/next edge IDs and ring ID to null values of
//! child half-edges.
void Edge::resetConnections()
{
    _associatedNode = nullptr;
    _directions[0].resetConnections();
    _directions[1].resetConnections();
}

//! @brief Updates the edge after splitting it about a new node somewhere along
//! its interior.
//! @param[in] splitNode The identifier of the node split about.
//! @param[in] secondEdge The new edge which connects splitNode to the original
//! second node in the current edge.
//! @note The angle of the current edge is not updated as it is expected to be
//! the same.
void Edge::updateAfterSplit(NodePtr splitNode, Edge *secondEdge)
{
    _nodes[1] = splitNode;

    if (secondEdge != nullptr)
    {
        // Connect the directed edges together about the split.
        secondEdge->_directions[0]._nextEdge = _directions[0]._nextEdge;
        secondEdge->_directions[0]._prevEdge = _directions;
        _directions[0]._nextEdge = secondEdge->_directions;
        secondEdge->_directions[1]._prevEdge = _directions[1]._prevEdge;
        secondEdge->_directions[1]._nextEdge = _directions + 1;
        _directions[1]._prevEdge = secondEdge->_directions + 1;

        // Allow secondEdge to inherit the properties from the current edge.
        secondEdge->_directions[0]._ring = _directions[0]._ring;
        secondEdge->_directions[1]._ring = _directions[1]._ring;
    }
}

//! @brief Copy assigns an edge to overwrite the current edge.
//! @param[in] rhs The edge to copy.
void Edge::copyEdge(const Edge &rhs) noexcept
{
    if (&rhs != this)
    {
        _angle = rhs._angle;
        _id = rhs._id;

        std::copy_n(rhs._nodes, 2, _nodes);
        _associatedNode = rhs._associatedNode;

        _directions[0].setParent(this, 0);
        _directions[1].setParent(this, 1);
    }
}

//! @brief Moves an edge to overwrite the current edge.
//! @param[in] rhs The edge to copy.
void Edge::moveEdge(Edge &&rhs) noexcept
{
    if (&rhs != this)
    {
        _angle = rhs._angle;
        _id = rhs._id;

        std::copy_n(rhs._nodes, 2, _nodes);
        _associatedNode = rhs._associatedNode;

        _directions[0].setParent(this, 0);
        _directions[1].setParent(this, 1);
    }
}

////////////////////////////////////////////////////////////////////////////////
// SplitEdgeResult Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! Constructs an empty split edge result value.
SplitEdgeResult::SplitEdgeResult() :
    FirstEdge(nullptr),
    SecondEdge(nullptr),
    SplitNode(nullptr)
{
}

//! @brief Constructs an initialised split edge result value.
//! @param[in] first The original edge truncated to the split joint.
//! @param[in] second A new edge proceeding from the split joint.
//! @param[in] node The joint about which the split was performed.
SplitEdgeResult::SplitEdgeResult(EdgePtr first, EdgePtr second, NodePtr node) :
    FirstEdge(first),
    SecondEdge(second),
    SplitNode(node)
{
}

////////////////////////////////////////////////////////////////////////////////
// EdgeTable Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a table of edges.
//! @param[in] edgeCountHint A hint at how many edges the table might contain.
EdgeTable::EdgeTable(size_t /*edgeCountHint = 0*/) :
    _idSeed(0)
{
    //if (edgeCountHint > 32)
    //{
    //    _allEdges.reserve(edgeCountHint);
    //}
}

//! @brief Determines whether the table is empty.
//! @retval true The table has no edges.
//! @retval false The table contains at least one edge.
bool EdgeTable::isEmpty() const noexcept
{
    return _allEdges.empty();
}

//! @brief Gets the count of edges in the table.
uint32_t EdgeTable::getCount() const noexcept
{
    return static_cast<uint32_t>(_allEdges.size());
}

//! @brief Attempts to find an edge corresponding to an identifier.
//! @param[in] edgeId The identifier of the edge to find.
//! @param[out] edge Receives a pointer to the edge found or nullptr.
//! @retval true An edge with the specified identifier was found and
//! a pointer to it returned.
//! @retval false No edge matched the specified identifier.
bool EdgeTable::tryFindEdgeByID(ID edgeId, EdgePtr &edge)
{
    auto pos = _edgesByID.find(edgeId);

    edge = (pos == _edgesByID.end()) ? nullptr : pos->second;

    return edge != nullptr;
}

//! @brief Attempts to find an edge corresponding to an identifier.
//! @param[in] edgeId The identifier of the edge to find.
//! @param[out] edge Receives a pointer to the edge found or nullptr.
//! @retval true An edge with the specified identifier was found and
//! a pointer to it returned.
//! @retval false No edge matched the specified identifier.
bool EdgeTable::tryFindEdgeByID(ID edgeId, EdgeCPtr &edge) const
{
    auto pos = _edgesByID.find(edgeId);

    edge = (pos == _edgesByID.end()) ? nullptr : pos->second;

    return edge != nullptr;
}

//! @brief Attempts to find a directed edge corresponding to an identifier.
//! @param[in] id The identifier of the directed edge to find.
//! @param[out] edge Receives a pointer to a directed edge or nullptr.
//! @retval true A directed edge with the specified identifier was found and
//! a pointer to it returned.
//! @retval false No directed edge matched the specified identifier.
bool EdgeTable::tryFindHalfEdgeByID(const HalfEdgeID &id, HalfEdgePtr &edge)
{
    EdgePtr parentEdge;

    if (tryFindEdgeByID(id.getEdgeID(), parentEdge))
    {
        edge = parentEdge->getHalfEdge(id.getDirectionIndex());
    }
    else
    {
        edge = nullptr;
    }

    return edge != nullptr;
}

//! @brief Attempts to find a directed edge corresponding to an identifier.
//! @param[in] id The identifier of the directed edge to find.
//! @param[out] edge Receives a pointer to a directed edge or nullptr.
//! @retval true A directed edge with the specified identifier was found and
//! a pointer to it returned.
//! @retval false No directed edge matched the specified identifier.
bool EdgeTable::tryFindHalfEdgeByID(const HalfEdgeID &id, HalfEdgeCPtr &edge) const
{
    EdgeCPtr parentEdge;

    if (tryFindEdgeByID(id.getEdgeID(), parentEdge))
    {
        edge = parentEdge->getHalfEdge(id.getDirectionIndex());
    }
    else
    {
        edge = nullptr;
    }

    return edge != nullptr;
}

//! @brief Attempts to find an edge by the nodes it connects.
//! @param[in] firstNode The identifier of one connected node.
//! @param[in] secondNode The identifier of the other connected node.
//! @param[out] edge Receives a pointer to the edge which connects the
//! specified nodes, or nullptr.
//! @retval true An edge connecting the specified nodes was found and returned.
//! @retval false No edge connected the specified nodes, edge is set to nullptr.
bool EdgeTable::tryFindEdgeByNodes(ID firstNode, ID secondNode, EdgePtr &edge)
{
    EdgeKey key = makeEdgeKey(firstNode, secondNode);

    auto pos = _edgesByConnection.find(key);

    edge = (pos == _edgesByConnection.end()) ? nullptr : pos->second;

    return edge != nullptr;
}

//! @brief Attempts to find an edge by the nodes it connects.
//! @param[in] firstNode The identifier of one connected node.
//! @param[in] secondNode The identifier of the other connected node.
//! @param[out] edge Receives a pointer to the edge which connects the
//! specified nodes, or nullptr.
//! @retval true An edge connecting the specified nodes was found and returned.
//! @retval false No edge connected the specified nodes, edge is set to nullptr.
bool EdgeTable::tryFindEdgeByNodes(ID firstNode, ID secondNode, EdgeCPtr &edge) const
{
    EdgeKey key = makeEdgeKey(firstNode, secondNode);

    auto pos = _edgesByConnection.find(key);

    edge = (pos == _edgesByConnection.end()) ? nullptr : pos->second;

    return edge != nullptr;
}

//! @brief Attempts to find a directed edge by the nodes it connects.
//! @param[in] startNode The identifier of the node at the start of the edge.
//! @param[in] endNode The identifier of the node at the end of the edge.
//! @param[out] edge Receives a pointer to the directed edge which connects the
//! specified nodes in the specified order, or nullptr.
//! @retval true An edge connecting the specified nodes was found and returned.
//! @retval false No edge connected the specified nodes, edge is set to nullptr.
bool EdgeTable::tryFindHalfEdgeByNodes(ID startNode, ID endNode, HalfEdgePtr &edge)
{
    EdgePtr parentEdge;

    if (tryFindEdgeByNodes(startNode, endNode, parentEdge))
    {
        edge = parentEdge->getHalfEdgeFrom(startNode);
    }
    else
    {
        edge = nullptr;
    }

    return edge != nullptr;
}

//! @brief Attempts to find a directed edge by the nodes it connects.
//! @param[in] startNode The identifier of the node at the start of the edge.
//! @param[in] endNode The identifier of the node at the end of the edge.
//! @param[out] edge Receives a pointer to the directed edge which connects the
//! specified nodes in the specified order, or nullptr.
//! @retval true An edge connecting the specified nodes was found and returned.
//! @retval false No edge connected the specified nodes, edge is set to nullptr.
bool EdgeTable::tryFindHalfEdgeByNodes(ID startNode, ID endNode, HalfEdgeCPtr &edge) const
{
    EdgeCPtr parentEdge;

    if (tryFindEdgeByNodes(startNode, endNode, parentEdge))
    {
        edge = parentEdge->getHalfEdgeFrom(startNode);
    }
    else
    {
        edge = nullptr;
    }

    return edge != nullptr;
}

//! @brief Gets all of the edges which connect to a specific joint.
//! @param[in] node The node to find edges associated with.
//! @return A collection of pointers to edges which connect node to another node.
EdgePtrCollection EdgeTable::edgesAtNode(ID node)
{
    std::vector<EdgePtr> edges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        edges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            edges.push_back(i->second);
        }
    }

    return edges;
}

//! @brief Gets all of the edges which connect to a specific joint.
//! @param[in] node The node to find edges associated with.
//! @return A collection of pointers to edges which connect node to another node.
EdgeCPtrCollection EdgeTable::edgesAtNode(ID node) const
{
    std::vector<EdgeCPtr> edges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        edges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            edges.push_back(i->second);
        }
    }

    return edges;
}

//! @brief Gets all half edges which start at a specified node.
//! @param[in] node The identifier of the node to find edges related to.
//! @return A collection of half edges all starting at node.
HalfEdgePtrCollection EdgeTable::halfEdgesFromNode(ID node)
{
    HalfEdgePtrCollection halfEdges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        halfEdges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            EdgePtr edge = i->second;

            halfEdges.push_back(edge->getHalfEdgeFrom(node));
        }
    }

    return halfEdges;
}

//! @brief Gets all half edges which start at a specified node.
//! @param[in] node The identifier of the node to find edges related to.
//! @return A collection of half edges all starting at node.
HalfEdgeCPtrCollection EdgeTable::halfEdgesFromNode(ID node) const
{
    HalfEdgeCPtrCollection halfEdges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        halfEdges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            EdgePtr edge = i->second;

            halfEdges.push_back(edge->getHalfEdgeFrom(node));
        }
    }

    return halfEdges;
}

//! @brief Gets all half edges which end at a specified node.
//! @param[in] node The identifier of the node to find edges related to.
//! @return A collection of half edges all ending at node.
HalfEdgePtrCollection EdgeTable::halfEdgesToNode(ID node)
{
    HalfEdgePtrCollection halfEdges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        halfEdges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            EdgePtr edge = i->second;

            halfEdges.push_back(edge->getHalfEdgeTo(node));
        }
    }

    return halfEdges;
}

//! @brief Gets all half edges which end at a specified node.
//! @param[in] node The identifier of the node to find edges related to.
//! @return A collection of half edges all ending at node.
HalfEdgeCPtrCollection EdgeTable::halfEdgesToNode(ID node) const
{
    HalfEdgeCPtrCollection halfEdges;

    auto resultPair = _edgesByNode.equal_range(node);
    size_t count = std::distance(resultPair.first, resultPair.second);

    if (count > 0)
    {
        halfEdges.reserve(count);

        for (auto i = resultPair.first; i != resultPair.second; ++i)
        {
            EdgePtr edge = i->second;

            halfEdges.push_back(edge->getHalfEdgeTo(node));
        }
    }

    return halfEdges;
}

//! @brief Gets a range of iterators representing mappings of node ID to
//! EdgePtr for a specific node.
//! @param[in] node The identifier of the node to find all mappings for.
//! @return A pair of iterators to node ID->EdgePtr mappings.
EdgeTable::EdgesAtNodeCIterRange EdgeTable::rangeOfEdgesAtNode(ID node) const
{
    return _edgesByNode.equal_range(node);
}

bool EdgeTable::tryFindSuccessor(HalfEdgePtr edge, bool ccw,
                                 HalfEdgePtr &successor) const
{
    successor = nullptr;

    if (edge == nullptr)
        throw Ag::ArgumentException("edge");

    Angle rootAngle = edge->getAngle();
    ID sourceNode = edge->getEndNodeID();
    double bestOffset = 0;

    // Search the index for all edges connected to the end of the source edge.
    auto resultPair = _edgesByNode.equal_range(sourceNode);

    for (auto pos = resultPair.first; pos != resultPair.second; ++pos)
    {
        // Discard co-linear edges.
        if (pos->second == edge->getParent())
            continue;

        // Get the directed edge proceeding from the source node.
        HalfEdgePtr nextEdge = pos->second->getHalfEdgeFrom(sourceNode);

        // Calculate the angle of the new edge relative to the old.
        double angularOffset = rootAngle.getOffsetTo(nextEdge->getAngle());
        bool isBest = false;

        if (successor == nullptr)
        {
            isBest = true;
        }
        else if (ccw)
        {
            isBest = (angularOffset > bestOffset);
        }
        else
        {
            isBest = (angularOffset < bestOffset);
        }

        if (isBest)
        {
            successor = nextEdge;
            bestOffset = angularOffset;
        }
    }

    return successor != nullptr;
}

//! @brief Resets the edge table to an empty state.
void EdgeTable::clear()
{
    _edgesByID.clear();
    _edgesByConnection.clear();
    _edgesByNode.clear();
    _allEdges.clear();
    _idSeed = 0;
}

//! @brief Adds an edge connecting existing nodes or finds an existing connection.
//! @param[in] nodes The table of node definitions.
//! @param[in] firstNode The ID of the first node to connect.
//! @param[in] secondNode The ID of the second node to connect.
//! @return A reference to the edge connecting the nodes, possibly new. The
//! returned edge isn't guaranteed to connect the nodes in the order specified
//! in the parameters.
Edge *EdgeTable::addEdge(NodeTable &nodes, ID firstNodeID, ID secondNodeID)
{
    if (firstNodeID == secondNodeID)
    {
        Ag::OperationException("The program attempted to add an edge to a "
                               "doubly connected edge list which connected "
                               "a node to itself.");
    }

    EdgeKey key = makeEdgeKey(firstNodeID, secondNodeID);

    auto edgeIDPos = _edgesByConnection.find(key);

    if (edgeIDPos == _edgesByConnection.end())
    {
        NodePtr firstNode = nullptr, secondNode = nullptr;

        if (nodes.tryFindNodeByID(firstNodeID, firstNode) &&
            nodes.tryFindNodeByID(secondNodeID, secondNode))
        {
            // The edge doesn't exist yet, create it.
            Edge newEdge(_idSeed++, firstNode, secondNode);

            // Add the edge to the table.
            _allEdges.push_back(std::make_unique<Edge>(newEdge));

            // Add the edge to the indexes.
            EdgePtr edgePtr = _allEdges.back().get();
            _edgesByID[edgePtr->getID()] = edgePtr;
            _edgesByConnection[edgePtr->getKey()] = edgePtr;

            for (DirectionIndex i = 0; i < 2; ++i)
            {
                _edgesByNode.emplace(edgePtr->getNodeID(i), edgePtr);
            }

            return edgePtr;
        }
        else
        {
            throw InvalidNodeIDException((firstNode == nullptr) ? firstNodeID : secondNodeID);
        }
    }
    else
    {
        // The edge already exists.
        return edgeIDPos->second;
    }

}

//! @brief Removes the specified edge from the collection.
//! @param[in] edgeID The identifier of the edge to remove.
void EdgeTable::removeEdge(ID edgeID)
{
    auto edgeIDPos = _edgesByID.find(edgeID);

    if (edgeIDPos != _edgesByID.end())
    {
        // Remove the edge from indexes.
        EdgePtr edgeToRemove = edgeIDPos->second;

        for (DirectionIndex i = 0; i < 2; ++i)
        {
            // Remove mappings for both ends of the edge.
            auto mappingRange = _edgesByNode.equal_range(edgeToRemove->getNodeID(i));

            for (auto j = mappingRange.first; j != mappingRange.second; )
            {
                if (j->second == edgeToRemove)
                {
                    j = _edgesByNode.erase(j);

                    // Highlander pattern: There should only be one.
                    break;
                }
                else
                {
                    ++j;
                }
            }
        }

        _edgesByConnection.erase(edgeToRemove->getKey());
        _edgesByID.erase(edgeIDPos);

        // Find the actual edge storage.
        // TODO: This uses slow linear search: Optimise.
        auto edgePos = std::find_if(_allEdges.begin(), _allEdges.end(),
                     [edgeID](const EdgeUPtr &edge) {
                         return edge->getID() == edgeID; });

        if (edgePos != _allEdges.end())
        {
            _allEdges.erase(edgePos);
        }
    }
}

//! @brief Removes all sibling connections and ring associations from all
//! edges in the table.
void EdgeTable::resetConnections()
{
    std::for_each(std::execution::parallel_unsequenced_policy(),
                  _allEdges.begin(), _allEdges.end(),
                  [](EdgeUPtr &edgeUPtr) { edgeUPtr->resetConnections(); });
}

//! @brief Splits a specified edge about a specified joint, which is expected
//! to be somewhere within its interior.
//! @param[in] nodes The table the node defining the edge and to split by.
//! @param[in] edgeID The identifier of the edge to split.
//! @param[in] nodeToSplitAboutID The identifier of the node at the split point.
//! @return A structure defining the two edges which result and the node which
//! they have in common.
SplitEdgeResult EdgeTable::splitEdge(NodeTable &nodes, ID edgeID, ID nodeToSplitAboutID)
{
    auto edgeIDPos = _edgesByID.find(edgeID);

    if (edgeIDPos == _edgesByID.end())
    {
        throw InvalidEdgeIDException(edgeID);
    }

    EdgePtr originalEdge = edgeIDPos->second;

    if ((originalEdge->getFirstNode()->getID() == nodeToSplitAboutID) ||
        (originalEdge->getSecondNode()->getID() == nodeToSplitAboutID))
    {
        throw Ag::OperationException("Splitting an edge about one of its ends.");
    }

    NodePtr nodeToSplitAbout = &nodes[nodeToSplitAboutID];
    ID endNodeID = originalEdge->getSecondNodeID();

    auto newEdgePos = _edgesByConnection.find(makeEdgeKey(nodeToSplitAboutID, endNodeID));
    EdgePtr secondEdgePtr = nullptr;

    if (newEdgePos == _edgesByConnection.end())
    {
        // We need to create the new edge.
        Edge secondEdge(_idSeed++, nodeToSplitAbout, originalEdge->getSecondNode());

        // If we get this far, all nodes are valid.
        _allEdges.emplace_back(std::make_unique<Edge>(secondEdge));
        secondEdgePtr = _allEdges.back().get();

        // Update indexes to include the new edge.
        _edgesByID.insert({ secondEdgePtr->getID(), secondEdgePtr });
        _edgesByNode.insert({ nodeToSplitAboutID, secondEdgePtr });
        _edgesByNode.insert({ endNodeID, secondEdgePtr });
        _edgesByConnection.insert({ secondEdgePtr->getKey(), secondEdgePtr });
    }
    else
    {
        // The second edge already exists.
        secondEdgePtr = newEdgePos->second;
    }

    // Partially remove the original edge from node-based indexes.
    _edgesByConnection.erase(originalEdge->getKey());

    auto edgeNodePair = _edgesByNode.equal_range(endNodeID);

    for (auto i = edgeNodePair.first; i != edgeNodePair.second; ++i)
    {
        if (i->second == originalEdge)
        {
            // Replace the original edge with the new one in this index.
            i->second = secondEdgePtr;
            break;
        }
    }

    // Truncate the original edge and connect to the new edge created after
    // the split.
    originalEdge->updateAfterSplit(nodeToSplitAbout, secondEdgePtr);

    return SplitEdgeResult(originalEdge, secondEdgePtr, nodeToSplitAbout);
}

//! @brief Gets the edge with a specified identifier.
//! @param[in] edgeID The unique identifier of the edge to get.
//! @return A reference to the edge.
Edge *EdgeTable::operator[](ID edgeID)
{
    EdgePtr edge;

    if (tryFindEdgeByID(edgeID, edge))
    {
        return edge;
    }

    throw InvalidEdgeIDException(edgeID);
}

//! @brief Gets the edge with a specified identifier.
//! @param[in] edgeID The unique identifier of the edge to get.
//! @return A reference to the edge.
const Edge *EdgeTable::operator[](ID edgeID) const
{
    EdgeCPtr edge;

    if (tryFindEdgeByID(edgeID, edge))
    {
        return edge;
    }

    throw InvalidEdgeIDException(edgeID);
}

//! @brief Gets a directed edge based on a specified identifier.
//! @param[in] edgeID The half-edge identifier to look up.
//! @return A reference to the directed edge found.
//! @throws InvalidHalfEdgeIDException If edgeID did not identify a valid
//! directed edge.
HalfEdge *EdgeTable::operator[](const HalfEdgeID &edgeID)
{
    HalfEdgePtr halfEdge;

    if (tryFindHalfEdgeByID(edgeID, halfEdge))
    {
        return halfEdge;
    }

    throw InvalidHalfEdgeIDException(edgeID);
}

//! @brief Gets a directed edge based on a specified identifier.
//! @param[in] edgeID The half-edge identifier to look up.
//! @return A reference to the directed edge found.
//! @throws InvalidHalfEdgeIDException If edgeID did not identify a valid
//! directed edge.
const HalfEdge *EdgeTable::operator[](const HalfEdgeID &edgeID) const
{
    HalfEdgeCPtr halfEdge;

    if (tryFindHalfEdgeByID(edgeID, halfEdge))
    {
        return halfEdge;
    }

    throw InvalidHalfEdgeIDException(edgeID);
}

////////////////////////////////////////////////////////////////////////////////
// Ring Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a ring which can be traced from a specific directed edge.
//! @param[in] ringID The unique identifier of the ring being created.
//! @param[in] firstHalfEdge The a pointer to a directed edge which forms
//! part of the perimeter of the ring.
//! @param[in] nodeCount The optional count of vertices defining the ring.
//! @param[in] flags Optional attributes of the ring, such as IsCCW.
Ring::Ring(ID ringID, HalfEdgePtr firstHalfEdge,
           uint32_t nodeCount /*= 0*/, uint32_t flags /*= 0*/) :
    _id(ringID),
    _parentRingID(NullID),
    _firstHalfEdge(firstHalfEdge),
    _nodeCount(nodeCount),
    _flags(flags)
{
    if (_firstHalfEdge == nullptr)
    {
        throw Ag::ArgumentNullException("firstHalfEdge");
    }
}

//! @brief Sets the parentage of the current ring and whether it represents a
//! void within its parent.
//! @param[in] parentID The identifier of the ring which surrounds this one.
void Ring::setParentRingID(ID parentID)
{
    _parentRingID = parentID;
}

//! @brief Gets the identifiers of nodes which define the ring.
//! @return A collection of numeric node identifiers.
IDCollection Ring::getNodeIDs() const
{
    IDCollection nodeIDs;

    appendNodeIDs(nodeIDs);

    return nodeIDs;
}

//! @brief Appends the identifiers of nodes which define the ring to a collection.
//! @param[in] nodeIDs A reference to the collection to append node IDs to.
void Ring::appendNodeIDs(IDCollection &nodeIDs) const
{
    ensureExtraCapacity(nodeIDs, _nodeCount);

    HalfEdgePtr currentEdge = _firstHalfEdge;

    do
    {
        nodeIDs.push_back(currentEdge->getEndNodeID());

        currentEdge = currentEdge->getNextEdge();
    } while ((currentEdge != nullptr) && (currentEdge != _firstHalfEdge));
}

//! @brief Gets a collection of points defining the ring.
//! @return A collection of points defining the ring.
Point2DCollection Ring::getVertices() const
{
    Point2DCollection points;

    if (_nodeCount > 0)
    {
        points.reserve(_nodeCount);
    }

    // Traverse the edges to extract positions.
    HalfEdgePtr currentEdge = _firstHalfEdge;

    do
    {
        points.push_back(currentEdge->getEndNode()->getRealPosition());

        currentEdge = currentEdge->getNextEdge();
    }
    while ((currentEdge != nullptr) && (currentEdge != _firstHalfEdge));

    return points;
}

//! @brief Gets a collection of nodes defining the collection.
//! @param[in] nodes The table of all nodes in the mesh.
//! @param[in] edges The table of all edges in the mesh.
//! @return A collection of pointers to the nodes which define the ring.
NodeCPtrCollection Ring::getNodes() const
{
    NodeCPtrCollection ringNodes;

    if (_nodeCount > 0)
    {
        ringNodes.reserve(_nodeCount);
    }

    // Traverse the edges to extract positions.
    HalfEdgePtr currentEdge = _firstHalfEdge;

    do
    {
        ringNodes.push_back(currentEdge->getEndNode());

        currentEdge = currentEdge->getNextEdge();
    }
    while ((currentEdge != nullptr) && (currentEdge != _firstHalfEdge));

    return ringNodes;
}

//! @brief Extracts the directed edges and corresponding nodes of the ring.
//! @param[out] nodes Receives the start node of each corresponding edge.
//! @param[out] edges Receives the directed edges defining the ring.
void Ring::getNodesAndEdges(NodePtrCollection &nodes, HalfEdgePtrCollection &edges) const
{
    nodes.clear();
    edges.clear();

    if (_nodeCount > 0)
    {
        nodes.reserve(_nodeCount);
        edges.reserve(_nodeCount);
    }

    // Traverse the edges to extract positions.
    HalfEdgePtr currentEdge = _firstHalfEdge;

    do
    {
        nodes.push_back(currentEdge->getEndNode());
        edges.push_back(currentEdge);

        currentEdge = currentEdge->getNextEdge();
    }
    while ((currentEdge != nullptr) && (currentEdge != _firstHalfEdge));
}

//! @brief Decomposes a convex, X or Y monotone ring into a list of triangles.
//! @return A list of node indices, every three defining a triangle.
//! @throws OperationException If the ring is not convex or X/Y monotone.
IDCollection Ring::triangulate() const
{
    return triangulateRing(*this);
}

////////////////////////////////////////////////////////////////////////////////
// RingSystem Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines whether the system contains no rings or holes.
bool RingSystem::isEmpty() const
{
    return _allRings.empty();
}

//! @brief Gets the count of all rings, filled and holes alike, in the system.
size_t RingSystem::getRingCount() const
{
    return _allRings.size();
}

//! @brief Gets the count of rings in the system which represent filled areas.
size_t RingSystem::getFilledCount() const
{
    return _allRings.size() - _holesByParentID.getCount();
}

//! @brief Gets the count of rings in the system which represent holes.
size_t RingSystem::getHoleCount() const
{
    return _holesByParentID.getCount();
}

//! @brief Gets a reference to the ring with the specified identifier.
//! @param[in] ringID The identifier of the ring or hole to obtain.
//! @throws IndexOutOfRangeException If @p ringID is invalid.
Ring &RingSystem::getRing(ID ringID)
{
    if (ringID >= _allRings.size())
        throw IndexOutOfRangeException(static_cast<size_t>(ringID),
                                       _allRings.size());

    return _allRings[ringID];
}

//! @brief Gets a reference to the ring with the specified identifier.
//! @param[in] ringID The identifier of the ring or hole to obtain.
//! @throws IndexOutOfRangeException If @p ringID is invalid.
const Ring &RingSystem::getRing(ID ringID) const
{
    if (ringID >= _allRings.size())
        throw IndexOutOfRangeException(static_cast<size_t>(ringID),
                                       _allRings.size());

    return _allRings[ringID];
}

//! @brief Gets a read-only reference to the collection of all rings (filled
//! and holes alike) in the system.
const RingCollection &RingSystem::getRings() const
{
    return _allRings;
}

//! @brief Gets a range of mappings of filled parent ring ID to child hole ID.
//! @param[in] parentRingID The identifier of the parent ring used to
//! query for holes.
//! @return A rang of ID pairs specifying filled and hole ring IDs.
SortedIDToIDMap::MatchingCRange RingSystem::getHoleMappings(ID parentRingID) const
{
    return _holesByParentID.findRange(parentRingID);
}

//! @brief Resets the object to an empty state.
void RingSystem::clear()
{
    _holesByParentID.clear();
    _allRings.clear();
}

//! @brief Initialises the system with all rings defined by a doubly-connected
//! edge list, annotating nodes and edges with the newly created rings.
//! @param[in] nodes The table of nodes to annotate with edges to their left.
//! @param[in] edges The table of edges to annotate with ring IDs.
//! @param[in] hasBuddyEdges Indicates whether the nodes of the mesh have already
//! been annotated with the edges immediately to their left, perhaps by an
//! intersection sweep or Y-monotone sweep.
//! @details
//! Any previous ring assignments for edges in the DCEL are overwritten. An index
//! of filled-hole parentage is created.
void RingSystem::build(NodeTable &nodes, EdgeTable &edges,
                       bool hasBuddyEdges /*= false*/)
{
    _allRings.clear();
    _holesByParentID.clear();

    _allRings = traceRings(nodes, edges, hasBuddyEdges);
    _holesByParentID.reserve(_allRings.size());

    for (size_t ringId = 0; ringId < _allRings.size(); ++ringId)
    {
        const Ring &ring = _allRings[ringId];

        if (ring.isHole() && (ring.getParentRingID() < _allRings.size()))
        {
            _holesByParentID.push_back(ring.getParentRingID(),
                                       static_cast<ID>(ringId));
        }
    }

    // Ensure the index is ready to be searched.
    _holesByParentID.reindex();
}

//! @brief Rebuilds the ring system after rings have been partitioned to remove holes.
//! @param[in] nodes The table of nodes to annotate with edges to their left.
//! @param[in] edges The table of edges to annotate with ring IDs.
void RingSystem::buildFromPartitioned(NodeTable &nodes, EdgeTable &edges)
{
    // Re-scan the edges to form a new set of CCW-only polygons.
    _holesByParentID = findPartitionedRings(nodes, edges, _allRings);
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an index key used to look up an edge.
constexpr EdgeKey makeEdgeKey(ID firstNode, ID secondNode) noexcept
{
    if (firstNode < secondNode)
    {
        return static_cast<EdgeKey>(firstNode) |
               (static_cast<EdgeKey>(secondNode) << 32);
    }
    else
    {
        return static_cast<EdgeKey>(secondNode) |
               (static_cast<EdgeKey>(firstNode) << 32);
    }
}

}}} // namespace Ag::Geom:DCEL
////////////////////////////////////////////////////////////////////////////////

