//! @file Gfx2D/DecompositionContext.cpp
//! @brief The definition of an object which can be used to decompose graphic
//! artefacts into partitioned polygons and lines while retaining resources
//! between operations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "DecompositionContext.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// DecompositionParams Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object describing how a path should be decomposed into
//! straight line segments.
DecompositionParams::DecompositionParams() :
    _approxThreashold(1.0),
    _isIdentity(true)
{
}

//! @brief Constructs an object describing how a path should be decomposed into
//! straight line segments.
//! @param[in] threshold The maximum distance between a point on an approximated
//! curve and the actual curve - must be greater than 0.0.
DecompositionParams::DecompositionParams(double threshold) :
    _approxThreashold(std::max(threshold, 0.0)),
    _isIdentity(true)
{
    if (threshold <= 0.0)
        throw ArgumentException("The curve approximation threshold must be greater than zero.",
                                "threshold");
}

//! @brief Constructs an object describing how a path should be decomposed into
//! straight line segments.
//! @param[in] transform The transform to apply to any path geometry before
//! decomposition.
//! @param[in] threshold The maximum distance between a point on an approximated
//! curve and the actual curve - must be greater than 0.0.
DecompositionParams::DecompositionParams(const Geom::AffineTransform2D &transform,
                                         double threshold /*= 1.0*/) :
    _transform(transform),
    _approxThreashold(std::max(threshold, 0.0)),
    _isIdentity(_transform.isIdentity())
{
    if (threshold <= 0.0)
        throw ArgumentException("The curve approximation threshold must be greater than zero.",
                                "threshold");
}

//! @brief Transforms a point from a path definition into a point useful in the
//! decomposition of the path.
//! @param[in] original The definition point to transform.
//! @return The transformed point.
Geom::Point2D DecompositionParams::transform(const Geom::Point2D &original) const noexcept
{
    return _isIdentity ? original : (_transform * original);
}

////////////////////////////////////////////////////////////////////////////////
// DecompositionStatistics Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty set of decomposition statistics.
DecompositionStatistics::DecompositionStatistics() :
    _pointCount(0),
    _edgeCount(0),
    _figureCount(0)
{
}

//! @brief Constructs an initialised set of decomposition statistics.
//! @param[in] bounds A rectangle encapsulating all points in the decomposition.
//! @param[in] pointCount The total count of vertices in the decomposition.
//! @param[in] edgeCount The total count of straight edges in the decomposition.
//! @param[in] figureCount The count of figures in the decomposition.
DecompositionStatistics::DecompositionStatistics(const Geom::Rect2D &bounds,
                                                 size_t pointCount,
                                                 size_t edgeCount,
                                                 size_t figureCount) :
    _bounds(bounds),
    _pointCount(pointCount),
    _edgeCount(edgeCount),
    _figureCount(figureCount)
{
}

//! @brief Combines the current decomposition statistics with another set.
//! @param[in] rhs The set of statistics to combine with.
//! @return The combined set of statistics.
DecompositionStatistics DecompositionStatistics::operator+(const DecompositionStatistics &rhs) const
{
    return { _bounds.combine(rhs._bounds),
             _pointCount + rhs._pointCount,
             _edgeCount + rhs._edgeCount,
             _figureCount + rhs._figureCount };
}

//! @brief Combines the current decomposition statistics with another set in-place.
//! @param[in] rhs The set of statistics to combine with.
//! @return A reference to the current object.
DecompositionStatistics &DecompositionStatistics::operator+=(const DecompositionStatistics &rhs)
{
    _bounds.combineTo(rhs._bounds);
    _pointCount += rhs._pointCount;
    _edgeCount += rhs._edgeCount;
    _figureCount += rhs._figureCount;

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// DecompositionContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the bounds of all points representing filled geometry.
const Geom::Rect2D &DecompositionContext::getFilledBounds() const
{
    return _filledBounds;
}

//! @brief Gets the bounds of all points representing clip geometry.
const Geom::Rect2D &DecompositionContext::getClipBounds() const
{
    return _clipBounds;
}

//! @brief Resets the object ready to receive new geometry.
//! @param[in] stats Details of the approximate size and extent of the new
//! geometry.
void DecompositionContext::reset(const DecompositionStatistics &stats)
{
    // TODO: Allow size hint to edge table.
    _edges.clear();
    _nodes.reset(stats.getBounds(), stats.getPointCount());
}

//! @brief Defines a point within the context.
//! @param[in] position The position to define.
//! @return The numeric identifier of the position, possibly returned when other
//! points were defined, but the new point is close enough for them to be
//! considered identical.
Geom::DCEL::ID DecompositionContext::definePoint(const Geom::Point2D &position)
{
    auto node = _nodes.addNode(position);

    return node->getID();
}

//! @brief Defines an edge connecting two previously defined points.
//! @param[in] startID The identifier of the first point on the edge.
//! @param[in] endID The identifier of the second point on the edge.
//! @param[in] isClip True if the edge is part of the clip geometry.
//! @return The identifier of the edge created, possibly not a unique identifier
//! if an edge connecting the specified points was already defined.
Geom::DCEL::ID DecompositionContext::defineEdge(Geom::DCEL::ID startID,
                                                Geom::DCEL::ID endID,
                                                bool isClip)
{
    auto edge = _edges.addEdge(_nodes, startID, endID);

    auto &bounds = isClip ? _clipBounds : _filledBounds;

    bounds.combineTo(edge->getFirstNode()->getRealPosition());
    bounds.combineTo(edge->getSecondNode()->getRealPosition());

    // TODO: Annotate edge with clip/noclip attribute.

    return edge->getID();
}

//! @brief Defines a set of connected edges.
//! @param[in] points The ordered collection of connected points.
//! @param[in] isClip True if the edge is part of the clip geometry.
void DecompositionContext::defineConnectedEdges(const Geom::Point2DCollectionView &points,
                                                bool isClip)
{
    if (points.getCount() < 2)
        return;

    Geom::DCEL::ID startID = Geom::DCEL::NullID;
    auto &bounds = isClip ? _clipBounds : _filledBounds;

    for (const Geom::Point2D &endPoint : points)
    {
        Geom::DCEL::ID endID = _nodes.addNode(endPoint)->getID();
        bounds.combineTo(endPoint);

        if (startID != Geom::DCEL::NullID)
        {
            // Define an edge connecting the last two points.
            defineEdge(startID, endID, isClip);
        }

        startID = endID;
    }
}

//! @brief Adds a line which exists purely to create additional points where
//! it intersects fill geometry.
//! @param[in] line The equation of the finite line to add.
void DecompositionContext::addIntersectionLine(const Geom::LineEq2D &line)
{
    if (_filledBounds.isEmpty())
        return;

    Geom::LineSeg2D clippedLine;

    if (_filledBounds.clip(line, clippedLine))
    {
        auto startNode = _nodes.addNode(clippedLine.getStart());
        auto endNode = _nodes.addNode(clippedLine.getEnd());

        auto edge = _edges.addEdge(_nodes, startNode->getID(), endNode->getID(),
                                   Geom::DCEL::Edge::IntersectionOnly);

        // TODO: Find all intersections, then remove the intersection lines
        // before partitioning the result.

    }
}

//! @brief Create a partitioned polygon from the clipped geometry.
//! @return A shape which can be rendered by a GPU, possibly empty if all
//! geometry was clipped out.
PartitionedPolygon DecompositionContext::partition(Geom::DCEL::ExplicitRingCollection &originalRings,
                                                   bool includeIntersections)
{
    // We need to trace the outlines of the original rings and assign indices
    // to the nodes we use.
    _nodes.resetNodeMapping();

    // TODO: Accumulate indices for outline nodes and assign mapped IDs.
    //   Trace the rings to be partitioned.
    //   Partition resultant rings.
    //   Accumulate indices to partition nodes and assigned mapped IDs.
    //   Copy mapped node positions into vertex buffer.
    Geom::DCEL::IDDeque triangles, outlines;
    Geom::DCEL::ID indexSeed = 0;

    for (const auto &ring : originalRings)
    {
        // TODO: Filter out rings used in clipping?

        // Ensure every node on the outline has a mapped index.
        for (auto outlineNodeID : ring.getNodes())
        {
            Geom::DCEL::NodePtr node = _nodes[outlineNodeID];
            auto mappedId = node->getMappedIndex();

            if (mappedId == Geom::DCEL::NullID)
            {
                mappedId = indexSeed++;
                node->setMappedIndex(mappedId);
            }

            outlines.push_back(mappedId);
        }

        outlines.push_back(Geom::DCEL::EndIndex);
    }

    // If we need to add intersections for intersection lines, do so and update
    // the rings to match.
    if (includeIntersections)
    {
        auto edgeReplacements = Ag::Geom::DCEL::findAllIntersections(_nodes, _edges);

        // TODO: Outlines could be created without the added intermediate points,
        // so theoretically, there is no need to update the outline geometry.
        //for (auto &ring : originalRings)
        //{
        //    ring.addIntersections(edgeReplacements);
        //}

        if (edgeReplacements.isEmpty() == false)
        {
            // Remove the edges which were created only to create intersections,
            // perhaps for linear shading gradient stops.
            _edges.removeIntersectionEdges();
        }
    }

    // Trace the set of rings to partition into y-monotone polygons.
    Geom::DCEL::RingSystem ringsToPartition;
    ringsToPartition.build(_nodes, _edges, includeIntersections);

    if (Geom::DCEL::makeYMonotone(_nodes, _edges, ringsToPartition))
    {
        // If any partitioning was done, re-build the rings.
        ringsToPartition.buildFromPartitioned(_nodes, _edges);
    }

    // Triangulate the y-monotone and convex polygons.
    for (const auto &ring : ringsToPartition.getRings())
    {
        if (ring.isHole())
            continue;

        auto triangleIndices = ring.triangulate();

        if (triangleIndices.empty())
            continue;

        for (auto triangleIndex : triangleIndices)
        {
            Geom::DCEL::NodePtr triangleNode = _nodes[triangleIndex];
            auto mappedId = triangleNode->getMappedIndex();

            if (mappedId == Geom::DCEL::NullID)
            {
                mappedId = indexSeed++;
                triangleNode->setMappedIndex(mappedId);
            }

            triangles.push_back(mappedId);
        }

        // NOTE: No need to terminate the run of indices, as a list of
        // triangles we can just render them all, whether connected or not.
    }

    // Now gather the vertices referred to in either the outline or triangle list.
    Geom::Point2DCollection vertices;
    vertices.resize(indexSeed);

    _nodes.collectMappedNodePoints(vertices);

    return PartitionedPolygon(vertices, triangles, outlines, _filledBounds);
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

