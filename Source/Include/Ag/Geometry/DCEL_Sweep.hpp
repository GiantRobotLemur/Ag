//! @file Ag/Geometry/DCEL_Sweep.hpp
//! @brief The declaration of structures required to implement a sweep through
//! edges held in a Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_DCEL_SWEEP_HPP__
#define __AG_GEOMETRY_DCEL_SWEEP_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "DCEL.hpp"
#include "LineEq2D.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Sweep event types used when creating a monotone polygon.
enum MonotoneVertexClass : uint32_t
{
    SplitVertex,
    StartVertex,
    RegularVertex,
    MergeVertex,
    EndVertex,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object represents the environment in which a plane sweep occurs.
class SweepContext
{
public:
    // Construction/Destruction
    SweepContext(const NodeTable &allNodes);
    ~SweepContext() = default;

    // Accessors
    constexpr NodePtr getSweepNode() noexcept { return _sweepPosition; }
    constexpr NodeCPtr getSweepNode() const noexcept { return _sweepPosition; }
    void setSweepNode(NodePtr sweepPosition);
    constexpr const NodeTable &getNodes() const noexcept { return _allNodes; }
    constexpr const LineEq2D &getSweepLine() const noexcept { return _sweepLine; }

    // Operations
    bool isParallelToSweepLine(EdgeCPtr edge) const;
    SnapPoint getSweepIntersection(const LineEq2D &line) const;
    bool comparePositions(const SnapPoint &lhs, const SnapPoint &rhs) const;
    int diffPositions(const SnapPoint &lhs, const SnapPoint &rhs) const;
private:
    // Internal Fields
    const NodeTable &_allNodes;
    NodePtr _sweepPosition;
    LineEq2D _sweepLine;
};

//! @brief An object represents an edge which is being processed in a plane sweep.
class SweepEdge
{
public:
    // Construction/Destruction
    SweepEdge(NodePtr node);
    SweepEdge(const SweepContext &context, EdgePtr edge);
    ~SweepEdge() = default;

    // Accessors
    constexpr bool isColinear() const noexcept { return _isColinear; }
    constexpr HalfEdgePtr getEdge() const noexcept { return _edge; }
    constexpr const LineEq2D &getEdgeLine() const noexcept { return _edgeLine; }

    SnapPoint getSweepIntersection(const SweepContext &context) const;

    // Operations
    bool operator==(const SweepEdge &rhs) const;
private:
    // Internal Fields
    HalfEdgePtr _edge;
    LineEq2D _edgeLine;
    mutable int64_t _lastSweepOffset;
    mutable int64_t _cachedSweepIntersection;
    bool _isColinear;
};

using SweepEdgeCollection = std::vector<SweepEdge>;
using SweepEdgeIter = SweepEdgeCollection::iterator;

//! @brief An object which holds the current state of a plane sweep.
class SweepStatus
{
public:
    // Construction/Destruction
    SweepStatus(SweepContext &context);
    ~SweepStatus() = default;

    // Accessors
    constexpr SweepEdgeCollection &getDiagonalEdgesInSweep() noexcept { return _diagonalEdges; }
    constexpr HalfEdgePtrCollection &getColinearEdgesInSweep() noexcept { return _colinearEdges; }
    bool findEdgeBeforeNode(NodePtr position, SweepEdgeIter &prevEdge);

    // Operations
    SweepEdgeIter addEdge(EdgePtr edge);
    SweepEdgeIter removeEdge(SweepEdgeIter edgePos);
    SweepEdgeIter removeEdge(HalfEdgeCPtr edgeToRemove);
    SweepEdgeIter removeEdgeAtSweep();
    EdgePtr succeedEdgeAtSweep();
private:
    // Internal Fields
    SweepContext &_context;
    SweepEdgeCollection _diagonalEdges;
    HalfEdgePtrCollection _colinearEdges;
};

//! @brief An object which defines an event which occurs during a plane sweep.
class SweepEvent
{
public:
    // Construction/Destruction
    SweepEvent();
    SweepEvent(NodePtr sweepPosition, uint32_t eventType);
    SweepEvent(NodePtr sweepPosition, EdgePtr edge, uint32_t eventType);
    SweepEvent(NodePtr sweepPosition, HalfEdgePtr edge, uint32_t eventType);
    ~SweepEvent() = default;

    // Accessors
    constexpr uint32_t getEventType() const noexcept { return _eventType; }
    constexpr NodePtr getEventNode() const noexcept { return _sweepPosition; }
    HalfEdgePtr getDirectedEdge() const;
    EdgePtr getEdge() const;
private:
    // Internal Fields
    NodePtr _sweepPosition;
    HalfEdgePtr _edgeToProcess;
    uint32_t _eventType;
};

//! @brief An alias for a vector of sweep event objects.
using SweepEventCollection = std::vector<SweepEvent>;


//! @brief A functor which compares sweep elements by their position on a
//! sweep of a 2D plane.
struct CompareSweepElements
{
private:
    const SweepContext &_context;
public:
    CompareSweepElements(const SweepContext &context);

    bool operator()(const SweepEdge &lhs, const SweepEdge &rhs) const;
    bool operator()(const SweepEvent &lhs, const SweepEvent &rhs) const;
};

//! @brief An object which manages events processed during a plane sweep.
class SweepEventQueue
{
public:
    // Construction/Destruction
    SweepEventQueue(const SweepContext &context);
    SweepEventQueue(const SweepContext &context, const SweepEvent *initialEvents,
                    size_t eventCount);
    ~SweepEventQueue() = default;

    // Accessors
    bool isEmpty() const noexcept;

    // Operations
    void insertEvent(const SweepEvent &eventToInsert);
    bool tryPopEvent(SweepEvent &nextEvent);
private:
    // Internal Types
    using EventQueue = std::deque<SweepEvent>;

    // Internal Fields
    const SweepContext &_context;
    EventQueue _sortedEvents;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
void sortSweepEvents(const SweepContext &context, SweepEventCollection &events);
bool containsSweepEvent(const SweepContext &context, SweepEventCollection &events, const SweepEvent &key);

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
