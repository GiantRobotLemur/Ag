//! @file Ag/Geometry/DCEL.hpp
//! @brief The declaration of a Doubly-Connected Edge List and child data
//! structures used in geometry algorithms.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_DCEL_HPP__
#define __AG_GEOMETRY_DCEL_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <execution>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/LinearSortedMap.hpp"

#include "Angle.hpp"
#include "Point2D.hpp"
#include "Rect2D.hpp"
#include "SnapContext.hpp"
#include "SnapPoint.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
using ID = uint32_t;

//! @brief An identifier value used to mark an element as unassigned.
constexpr ID NullID = std::numeric_limits<ID>::max() >> 1;

//! @brief An identifier used to mark an element as processed, but not assigned.
constexpr ID VisitedID = NullID - 1;

using EdgeKey = uint64_t;
using DirectionIndex = uint8_t;

struct HalfEdgeID;
class Edge;

using IDCollection = std::vector<ID>;
using SortedIDSet = std::set<ID>;
using SortedIDToIDMap = LinearSortedMap<ID, ID>;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
constexpr EdgeKey makeEdgeKey(ID firstNode, ID secondNode) noexcept;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An exception thrown when an attempt is made to access DCEL node using
//! an invalid identifier.
class InvalidNodeIDException : public Ag::Exception
{
public:
    InvalidNodeIDException(ID id);
};

//! @brief An exception thrown when an attempt is made to access DCEL edge using
//! an invalid identifier.
class InvalidEdgeIDException : public Ag::Exception
{
public:
    InvalidEdgeIDException(ID id);
};

//! @brief An exception thrown when an attempt is made to access DCEL half-edge
//! using an invalid identifier.
class InvalidHalfEdgeIDException : public Ag::Exception
{
public:
    InvalidHalfEdgeIDException(const HalfEdgeID &id);
};

//! @brief A point within a doubly-connected edge list.
class Node
{
public:
    // Construction/Destruction
    Node(ID id, const Point2D &position, const SnapPoint &gridPosition);
    ~Node() = default;

    // Accessors
    //! @brief Gets the unique identifier of the node.
    constexpr ID getID() const noexcept { return _id; }

    //! @brief Gets the identifier of the edge associated with this node,
    //! possibly the left most or next highest edge.
    //! @return The identifier of an edge or NullID.
    constexpr Edge *getBuddyEdge() const noexcept { return _buddyEdge; }
    void setBuddyEdge(Edge *buddyEdgeID) noexcept;

    constexpr ID getMappedIndex() const noexcept { return _mappedIndex; }
    void setMappedIndex(ID index) noexcept;

    const Point2D &getRealPosition() const noexcept;
    const SnapPoint &getGridPosition() const noexcept;

    //! @brief Gets flags used during algorithmic processing.
    constexpr uint32_t getFlags() const noexcept { return _flags; }

    //! @brief Updates flags used during algorithmic processing.
    //! @param[in] flags The new value for the flags field.
    constexpr void setFlags(uint32_t flags) noexcept { _flags = flags; }
private:
    // Internal Fields
    ID _id;
    ID _mappedIndex;
    Point2D _realPosition;
    SnapPoint _gridPosition;
    Edge *_buddyEdge;
    uint32_t _flags;
};

using NodePtr = Node *;
using NodeCPtr = const Node *;
using NodeUPtr = std::unique_ptr<Node>;
using NodePtrCollection = std::vector<NodePtr>;
using NodeCPtrCollection = std::vector<NodeCPtr>;

//! @brief An indexed collection of points within a doubly-connected edge list.
class NodeTable
{
public:
    // Public Types
    using NodeCollection = std::deque<NodeUPtr>;
    using NodeGridIndex = std::map<SnapPoint, NodePtr>;
    using NodeGridCIter = NodeGridIndex::const_iterator;
    using NodeIDIndex = std::map<ID, NodePtr>;
    using NodeIDCIter = NodeIDIndex::const_iterator;

    // Construction/Destruction
    NodeTable();
    NodeTable(const Rect2D &estimatedBounds, size_t nodeCountHint = 0);
    ~NodeTable() = default;

    // Accessors
    bool isEmpty() const noexcept;
    uint32_t getCount() const noexcept;
    const SnapContext &getGrid() const noexcept;
    Rect2D calculateExtents() const;

    // Operations
    void clear();
    void reset(const Rect2D &estimatedBounds, size_t nodeCountHint = 0);
    Node &operator[](ID nodeID);
    const Node &operator[](ID nodeID) const;
    bool tryFindNodeByID(ID nodeID, NodePtr &node);
    bool tryFindNodeByID(ID nodeID, NodeCPtr &node) const;
    bool tryFindNodeByPosition(const Point2D &realPosition, NodePtr &node);
    bool tryFindNodeByPosition(const Point2D &realPosition, NodeCPtr &node) const;
    NodeGridCIter beginByPosition() const;
    NodeGridCIter endByPosition() const;
    NodeIDCIter beginByID() const;
    NodeIDCIter endByID() const;

    Node &addNode(const Point2D &realPosition);
    void removeNode(ID nodeID);
private:
    // Internal Fields
    SnapContext _grid;
    NodeCollection _allNodes;
    NodeIDIndex _nodesByID;
    NodeGridIndex _nodesByPosition;
    ID _idSeed;
};

class Edge;
class HalfEdge;

//! @brief A value representing the identity of a directed edge
struct HalfEdgeID
{
private:
    // Internal Constants
    static constexpr uint8_t DirectionShift = (sizeof(ID) * 8) - 1;
    static constexpr ID EdgeIDMask = std::numeric_limits<ID>::max() >> 1;

    // Internal Fields
    //! @brief The identifier of the parent edge.
    ID _id;

public:
    // Construction/Destruction
    HalfEdgeID();
    HalfEdgeID(ID edgeID, DirectionIndex directionIndex);
    HalfEdgeID(const HalfEdge &halfEdge);
    ~HalfEdgeID() = default;

    //! @brief Determines whether the value is initialised with a valid ID.
    //! @retval true The value is set to null.
    //! @retval false The value has a valid identifier.
    constexpr bool isNull() const noexcept { return _id == NullID; }

    //! @brief Gets the identifier of the edge which owns the identifying half-edge.
    constexpr ID getEdgeID() const noexcept { return _id & EdgeIDMask; }

    HalfEdgeID getReverseID() const noexcept;

    //! @brief Gets the index of the half-edge within the parent edge.
    //! @return A value of 0 or 1.
    constexpr DirectionIndex getDirectionIndex() const noexcept {
        return static_cast<DirectionIndex>(_id >> DirectionShift);
    }

    //! @brief Determines whether two half-edge identifiers refer to the same
    //! target object.
    //! @param[in] rhs The identifier to compare against.
    //! @retval true The two identifiers refer to the same object.
    //! @retval false The identifiers refer to different half-edges.
    constexpr bool operator==(const HalfEdgeID &rhs) const noexcept {
        return (_id == rhs._id);
    }

    //! @brief Determines whether two half-edge identifiers refer to different
    //! target objects.
    //! @param[in] rhs The identifier to compare against.
    //! @retval true The identifiers refer to different half-edges.
    //! @retval false The two identifiers refer to the same object.
    constexpr bool operator!=(const HalfEdgeID &rhs) const noexcept {
        return (_id != rhs._id);
    }

    //! @brief Performs a less-than comparison between identifiers.
    //! @param[in] rhs The identifier to compare against.
    //! @retval true The current identifier has a lower value than rhs.
    //! @retval false The current identifier has an equal or higher value than rhs.
    constexpr bool operator<(const HalfEdgeID &rhs) const noexcept {
        return _id < rhs._id;
    }
};

//! @brief A directed-connection within a doubly-connected edge list.
class HalfEdge
{
private:
    // Construction/Destruction
    HalfEdge();
public:
    ~HalfEdge() = default;
    friend class Edge;

    // Accessors
    HalfEdgeID getID() const noexcept;
    ID getEdgeID() const noexcept;
    ID getStartNodeID() const noexcept;
    ID getEndNodeID() const noexcept;
    NodePtr getStartNode() const noexcept;
    NodePtr getEndNode() const noexcept;

    //! @brief Gets the non-directed edge this half-edge belongs to.
    constexpr Edge *getParent() const noexcept { return _parent; }

    //! @brief Gets the index of the directed edge within its parent.
    constexpr DirectionIndex getDirectionIndex() const noexcept { return _index; }

    //! @brief Sets the identifier of the ring for which the edge forms
    //! part of the perimeter.
    constexpr ID getRingID() const noexcept { return _ring; }

    void setRingID(ID ring) noexcept;
    HalfEdge *getPreviousEdge() const noexcept;
    void setPreviousEdge(HalfEdge *prevEdge) noexcept;
    HalfEdge *getNextEdge() const noexcept;
    void setNextEdge(HalfEdge *nextEdge) noexcept;
    HalfEdgeID getPreviousEdgeID() const noexcept;
    HalfEdgeID getNextEdgeID() const noexcept;
    HalfEdge *getReverse() noexcept;
    const HalfEdge *getReverse() const noexcept;
    Angle getAngle() const;

    // Operations
    void resetConnections();
    void linkEdges(HalfEdge *linkedEdge);
private:
    // Internal Functions
    void setParent(Edge *parent, DirectionIndex index);

    // Internal Fields
    Edge *_parent;
    DirectionIndex _index;
    HalfEdge *_prevEdge;
    HalfEdge *_nextEdge;
    ID _ring;
};

//! @brief A connection within a doubly-connected edge list.
class Edge
{
public:
    friend class HalfEdge;

    // Construction/Destruction
    Edge() = delete;
    Edge(const Edge &rhs);
    Edge(Edge &&rhs) noexcept;
    Edge(ID edgeID, NodePtr firstNode, NodePtr secondNode);
    ~Edge() = default;

    // Accessors
    //! @brief Gets the unique identifier of the edge.
    constexpr ID getID() const noexcept { return _id; }

    //! @brief Determines if a node is used to define one end of this edge.
    //! @param[in] node The node to check for.
    //! @retval true The node appears on at least one end of the edge.
    //! @retval false The node does not define this edge.
    constexpr bool hasNode(NodeCPtr node) const noexcept { return (_nodes[0] == node) || (_nodes[1] == node); }

    //! @brief Gets a key which is a value representing the two nodes the edge connects.
    constexpr EdgeKey getKey() noexcept { return makeEdgeKey(_nodes[0]->getID(), _nodes[1]->getID()); }

    //! @brief Gets the identifier of the first node being connected by the edge.
    constexpr ID getFirstNodeID() const noexcept { return _nodes[0]->getID(); }

    //! @brief Gets a pointer to the first node being connected by the edge.
    constexpr NodePtr getFirstNode() const noexcept { return _nodes[0]; }

    //! @brief Gets the identifier of the second node being connected by the edge.
    constexpr ID getSecondNodeID() const noexcept { return _nodes[1]->getID(); }

    //! @brief Gets a pointer to the second node being connected by the edge.
    constexpr NodePtr getSecondNode() const noexcept { return _nodes[1]; }

    //! @brief Gets the identifier of one of the nodes defining the edge.
    //! @param[in] index The index of the node, either 0 or 1.
    //! @return The identifier of the node.
    constexpr ID getNodeID(DirectionIndex index) const noexcept { return _nodes[index]->getID(); }

    //! @brief Gets a pointer to one of the nodes defining the edge.
    //! @param[in] index The index of the node, either 0 or 1.
    //! @return The identifier of the node.
    constexpr NodePtr getNode(DirectionIndex index) const noexcept { return _nodes[index]; }

    //! @brief Gets a pointer to the other node which defines the edge.
    //! @param[in] node The node to find the opposite of.
    //! @return The node defining the edge which isn't @p node.
    constexpr NodePtr getOppositeNode(NodePtr node) const noexcept { return _nodes[(_nodes[0] == node) ? 1 : 0]; }

    //! @brief Determines if a node is one of the points which defines the edge.
    //! @param[in] nodeID The node to test for.
    //! @retval true The specified node defines one of the edge ends.
    //! @retval false The specified node is not used to define this edge.
    constexpr bool isDefinedByNode(ID nodeID) const noexcept { return (_nodes[0]->getID() == nodeID) || (_nodes[1]->getID() == nodeID); }

    //! @brief Gets the absolute angle of the edge.
    //! @return The angle of the edge in radians relative to the X axis,
    //! counter-clockwise in a LH coordinate system.
    constexpr double getRawAngle() const noexcept { return _angle; }

    HalfEdge *getHalfEdge(DirectionIndex index) noexcept;
    const HalfEdge *getHalfEdge(DirectionIndex index) const noexcept;
    HalfEdge *getHalfEdgeFrom(ID node) noexcept;
    const HalfEdge *getHalfEdgeFrom(ID node) const noexcept;
    HalfEdge *getHalfEdgeTo(ID node) noexcept;
    const HalfEdge *getHalfEdgeTo(ID node) const noexcept;

    //! @brief Gets a pointer to a arbitrary node which annotates the edge.
    //! @return The pointer to a node, possibly null.
    constexpr NodePtr getAssociatedNode() const noexcept { return _associatedNode; }

    void setAssociatedNode(NodePtr node);

    // Operations
    Edge &operator=(const Edge &rhs) noexcept;
    Edge &operator=(Edge &&rhs) noexcept;

    void resetConnections();
    void updateAfterSplit(NodePtr splitNode, Edge *secondEdge);
private:
    // Internal Functions
    void copyEdge(const Edge &rhs) noexcept;
    void moveEdge(Edge &&rhs) noexcept;

    // Internal Fields
    ID _id;
    double _angle;
    HalfEdge _directions[2];
    NodePtr _nodes[2];
    NodePtr _associatedNode;
};

using EdgePtr = Edge *;
using EdgeCPtr = const Edge *;
using EdgeUPtr = std::unique_ptr<Edge>;
using EdgePtrCollection = std::vector<EdgePtr>;
using EdgeCPtrCollection = std::vector<EdgeCPtr>;
using HalfEdgePtr = HalfEdge *;
using HalfEdgeCPtr = const HalfEdge *;
using HalfEdgePtrCollection = std::vector<HalfEdgePtr>;
using HalfEdgeCPtrCollection = std::vector<HalfEdgeCPtr>;

//! @brief A structure to provide the results of EdgeTable::splitEdge().
struct SplitEdgeResult
{
    EdgePtr FirstEdge;
    EdgePtr SecondEdge;
    NodePtr SplitNode;

    SplitEdgeResult();
    SplitEdgeResult(EdgePtr first, EdgePtr second, NodePtr node);
    ~SplitEdgeResult() = default;
};

//! @brief An indexed collection of connections within a doubly-connected edge list.
class EdgeTable
{
public:
    // Public Types
    using EdgeCollection = std::deque<EdgeUPtr>;
    using EdgeNodeIndex = std::multimap<ID, Edge *>;
    using EdgeAtNodeCIter = EdgeNodeIndex::const_iterator;
    using EdgesAtNodeCIterRange = IteratorRange<EdgeAtNodeCIter>;

    // Construction/Destruction
    EdgeTable(size_t edgeCountHint = 0);
    ~EdgeTable() = default;

    // Accessors
    bool isEmpty() const noexcept;
    uint32_t getCount() const noexcept;
    bool tryFindEdgeByID(ID edgeId, EdgePtr &edge);
    bool tryFindEdgeByID(ID edgeId, EdgeCPtr &edge) const;
    bool tryFindHalfEdgeByID(const HalfEdgeID &id, HalfEdgePtr &edge);
    bool tryFindHalfEdgeByID(const HalfEdgeID &id, HalfEdgeCPtr &edge) const;
    bool tryFindEdgeByNodes(ID firstNode, ID secondNode, EdgePtr &edge);
    bool tryFindEdgeByNodes(ID firstNode, ID secondNode, EdgeCPtr &edge) const;
    bool tryFindHalfEdgeByNodes(ID startNode, ID endNode, HalfEdgePtr &edge);
    bool tryFindHalfEdgeByNodes(ID startNode, ID endNode, HalfEdgeCPtr &edge) const;
    EdgePtrCollection edgesAtNode(ID node);
    EdgeCPtrCollection edgesAtNode(ID node) const;
    HalfEdgePtrCollection halfEdgesFromNode(ID node);
    HalfEdgeCPtrCollection halfEdgesFromNode(ID node) const;
    HalfEdgePtrCollection halfEdgesToNode(ID node);
    HalfEdgeCPtrCollection halfEdgesToNode(ID node) const;
    EdgesAtNodeCIterRange rangeOfEdgesAtNode(ID node) const;
    bool tryFindSuccessor(HalfEdgePtr edge, bool ccw, HalfEdgePtr &successor) const;

    // Operations
    void clear();
    Edge *addEdge(NodeTable &nodes, ID firstNode, ID secondNode);
    void removeEdge(ID edgeID);
    void resetConnections();
    SplitEdgeResult splitEdge(NodeTable &nodes, ID edgeID, ID nodeToSplitAboutID);

    //! @brief Performs an operation on every edge, possibly out of
    //! order and in parallel.
    //! @tparam TUnaryFunc The type of operation to perform.
    //! @param fn A function object which takes a reference to an edge.
    template<class TUnaryFunc>
    void applyToAllEdges(TUnaryFunc fn)
    {
        std::for_each(std::execution::parallel_unsequenced_policy(),
                      _allEdges.begin(), _allEdges.end(),
                      [&fn](EdgeUPtr &edgeUPtr) { fn(edgeUPtr.get()); });
    }

    //! @brief Performs an operation on every edge sequentially and
    //! on the calling thread.
    //! @tparam TUnaryFunc The type of operation to perform, possibly a function
    //! object which can retain state as edges are iterated over.
    //! @param fn A function object which takes a reference to an edge.
    template<class TUnaryFunc>
    void forEachEdge(TUnaryFunc &fn)
    {
        std::for_each(_allEdges.begin(), _allEdges.end(),
                      [&fn](EdgeUPtr &edgeUPtr) { fn(edgeUPtr.get()); });
    }

    Edge *operator[](ID edgeID);
    const Edge *operator[](ID edgeID) const;
    HalfEdge *operator[](const HalfEdgeID &edgeID);
    const HalfEdge *operator[](const HalfEdgeID &edgeID) const;
private:
    // Internal Types
    using EdgeIDIndex = std::map<ID, Edge *>;
    using EdgeKeyIndex = std::map<EdgeKey, Edge *>;

    // Internal Fields
    EdgeCollection _allEdges;
    EdgeIDIndex _edgesByID;
    EdgeKeyIndex _edgesByConnection;
    EdgeNodeIndex _edgesByNode;
    ID _idSeed;
};

//! @brief A ring of connected nodes within a doubly-connected edge list.
class Ring
{
public:
    // Public Constants
    static constexpr uint32_t IsConvex = 0x01;
    static constexpr uint32_t IsCCW = 0x02;
    static constexpr uint32_t IsXMonotone = 0x04;
    static constexpr uint32_t IsYMonotone = 0x08;
    static constexpr uint32_t IsMonotone = IsXMonotone | IsYMonotone;
    static constexpr uint32_t IsHole = 0x10;
    static constexpr uint32_t HasChildren = 0x20;
    static constexpr uint32_t IsSurrounding = 0x40;

    // Construction/Destruction
    Ring(ID ringID, HalfEdgePtr firstHalfEdge,
         uint32_t nodeCount = 0, uint32_t flags = 0);
    ~Ring() = default;

    // Accessors
    //! @brief Gets the unique identifier of the ring.
    constexpr ID getID() const noexcept { return _id; }

    //! @brief Gets the flags which specify attributes of the ring.
    constexpr uint32_t getFlags() const noexcept { return _flags; }

    //! @brief Sets the flags which specify attributes of the ring.
    //! @param[in] flags The new flag bits, possibly including IsConvex and/or IsCCW.
    void setFlags(uint32_t flags) noexcept { _flags = flags; }

    //! @brief Determines if attributes indicate the ring is a convex polygon.
    //! @retval true The ring is convex.
    //! @retval false The ring is concave.
    constexpr bool isConvex() const noexcept { return _flags & IsConvex; }

    //! @brief Determines if attributes indicate the ring is orientated in a
    //! counter-clockwise direction.
    //! @retval true The ring is wound in a counter-clockwise direction.
    //! @retval false The ring is wound in a clockwise direction.
    constexpr bool isCCW() const noexcept { return _flags & IsCCW; }

    //! @brief Determines if the ordered ring edges only change X direction twice.
    constexpr bool isXMonotone() const noexcept { return _flags & IsXMonotone; }

    //! @brief Determines if the ordered ring edges only change Y direction twice.
    constexpr bool isYMonotone() const noexcept { return _flags & IsYMonotone; }

    //! @brief Determines if the ring surrounds a void rather than a valid area.
    constexpr bool isHole() const noexcept { return _flags & IsHole; }

    //! @brief Determines if the ring contains at least one hole.
    constexpr bool hasHoles() const noexcept { return _flags & HasChildren; }

    //! @brief Determines if the ring surrounds a space containing rings of
    //! the same winding, like a ring of connected filled rings.
    constexpr bool isSurrounding() const noexcept { return _flags & IsSurrounding; }

    //! @brief Gets the count of vertices which define the ring.
    constexpr uint32_t getNodeCount() const noexcept { return _nodeCount; }

    //! @brief Gets a pointer to one directed edge defining the ring.
    constexpr HalfEdgePtr getFirstEdge() const noexcept { return _firstHalfEdge; }

    //! @brief Gets the identifier of the ring which encompasses this one.
    //! @returns Either a valid ring identifier or NullID if an outer ring.
    constexpr ID getParentRingID() const noexcept { return _parentRingID; }

    void setParentRingID(ID parentID);

    // Operations
    IDCollection getNodeIDs() const;
    void appendNodeIDs(IDCollection &nodeIDs) const;
    Point2DCollection getVertices() const;
    NodeCPtrCollection getNodes() const;
    void getNodesAndEdges(NodePtrCollection &nodes, HalfEdgePtrCollection &edges) const;

    IDCollection triangulate() const;
private:
    // Internal Fields
    ID _id;
    ID _parentRingID;
    HalfEdgePtr _firstHalfEdge;
    uint32_t _nodeCount;
    uint32_t _flags;
};

using RingCollection = std::vector<Ring>;

//! @brief Encapsulates a hierarchy of rings and holes within them.
class RingSystem
{
public:
    // Construction/Destruction
    RingSystem() = default;
    ~RingSystem() = default;

    // Accessors
    bool isEmpty() const;
    size_t getRingCount() const;
    size_t getFilledCount() const;
    size_t getHoleCount() const;
    Ring &getRing(ID ringID);
    const Ring &getRing(ID ringID) const;
    const RingCollection &getRings() const;
    SortedIDToIDMap::MatchingCRange getHoleMappings(ID parentRingID) const;

    // Operations
    void clear();
    void build(NodeTable &nodes, EdgeTable &edges, bool hasBuddyEdges = false);
    void buildFromPartitioned(NodeTable &nodes, EdgeTable &edges);
private:
    // Internal Fields
    RingCollection _allRings;
    SortedIDToIDMap _holesByParentID;
};

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
