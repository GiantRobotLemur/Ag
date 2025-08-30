//! @file Geometry/Test_DCEL_Sweep.cpp
//! @brief The definition of unit tests for the a plane sweep of edges held
//! in a Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Test_DCEL_Tools.hpp"
#include "Ag/Geometry/DCEL_Sweep.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Sweep, LessThanSweep)
{
    EXPECT_TRUE(SnapPoint(2, 1).lessThanSweep(SnapPoint(5, 0)));
    EXPECT_FALSE(SnapPoint(5, 0).lessThanSweep(SnapPoint(2, 1)));
    EXPECT_TRUE(SnapPoint(2, 1).lessThanSweep(SnapPoint(5, 1)));
    EXPECT_FALSE(SnapPoint(5, 1).lessThanSweep(SnapPoint(2, 1)));
    EXPECT_FALSE(SnapPoint(5, 1).lessThanSweep(SnapPoint(5, 1)));
}

GTEST_TEST(DCEL_Sweep, DiffSweep)
{
    EXPECT_LT(SnapPoint(2, 1).diffSweep(SnapPoint(5, 0)), 0);
    EXPECT_GT(SnapPoint(5, 0).diffSweep(SnapPoint(2, 1)), 0);
    EXPECT_LT(SnapPoint(2, 1).diffSweep(SnapPoint(5, 1)), 0);
    EXPECT_GT(SnapPoint(5, 1).diffSweep(SnapPoint(2, 1)), 0);
    EXPECT_EQ(SnapPoint(5, 1).diffSweep(SnapPoint(5, 1)), 0);
}

GTEST_TEST(DCEL_SweepEdge, Intersection)
{
    NodeTable nodes(Rect2D(-100, -100, 200, 200));

    ID first = nodes.addNode(Point2D(2, 1)).getID();
    ID second = nodes.addNode(Point2D(57, 56)).getID();
    ID third = nodes.addNode(Point2D(25, 2)).getID();
    ID fourth = nodes.addNode(Point2D(-38, 65)).getID();

    EdgeTable edges(4);
    auto firstEdge = edges.addEdge(nodes, first, second);
    auto secondEdge = edges.addEdge(nodes, third, fourth);

    LineSeg2D firstSecond(nodes[first].getRealPosition(), nodes[second].getRealPosition());
    LineSeg2D thirdFourth(nodes[third].getRealPosition(), nodes[fourth].getRealPosition());
    Point2D intersectionPt;

    const auto &domain = nodes.getGrid().getDomain();

    ASSERT_TRUE(firstSecond.tryCalculateIntersection(domain, thirdFourth, intersectionPt));
    auto intersectionNode = &nodes.addNode(intersectionPt);

    SweepContext context(nodes);
    context.setSweepNode(intersectionNode);

    SweepEdge firstSweep(context, firstEdge);
    SweepEdge secondSweep(context, secondEdge);
    SweepEdge pointEdge(intersectionNode);

    EXPECT_FALSE(firstSweep.isColinear());
    EXPECT_FALSE(secondSweep.isColinear());
    EXPECT_FALSE(pointEdge.isColinear());

    SnapPoint gridIntersection = intersectionNode->getGridPosition();
    SnapPoint gridLineIntersection = firstSweep.getSweepIntersection(context);

    EXPECT_EQ(gridIntersection, gridLineIntersection);

    gridLineIntersection = secondSweep.getSweepIntersection(context);
    EXPECT_EQ(gridIntersection, gridLineIntersection);

    gridLineIntersection = pointEdge.getSweepIntersection(context);
    EXPECT_EQ(gridIntersection, gridLineIntersection);
}

GTEST_TEST(DCEL_SweepState, InsertSweepColinear)
{
    NodeTable nodes(Rect2D(-10, -10, 20, 20));

    NodePtr first = &nodes.addNode(Point2D(5, 0));
    NodePtr second = &nodes.addNode(Point2D(5, 10));
    NodePtr third = &nodes.addNode(Point2D(0, 5));
    NodePtr fourth = &nodes.addNode(Point2D(10, 5));
    NodePtr intersection = &nodes.addNode(Point2D(5, 5));

    EdgeTable edges(4);
    auto verticalEdge = edges.addEdge(nodes, first->getID(), second->getID());
    auto horizontalEdge = edges.addEdge(nodes, third->getID(), fourth->getID());

    SweepContext context(nodes);
    SweepStatus status(context);

    // Simulate a sweep from max-Y to the intersection.
    context.setSweepNode(second);
    status.addDiagonalEdge(verticalEdge);

    context.setSweepNode(fourth);
    status.addHorizontalEdge(horizontalEdge);

    context.setSweepNode(intersection);
    auto edgeRange = status.findEdgesAtSweep();

    EXPECT_EQ(edgeRange.getCount(), 1u);
    EXPECT_TRUE(status.hasHorizontalEdges());
}

GTEST_TEST(DCEL_Sweep, SimpleIntersection)
{
    NodeTable nodes(Rect2D(-10, -10, 20, 20));

    // Create a diagonal cross with two lines.
    ID first = nodes.addNode(Point2D(0, 0)).getID();
    ID second = nodes.addNode(Point2D(10, 10)).getID();
    ID third = nodes.addNode(Point2D(10, 0)).getID();
    ID fourth = nodes.addNode(Point2D(0, 10)).getID();

    EdgeTable edges(4);
    edges.addEdge(nodes, first, second);
    edges.addEdge(nodes, third, fourth);

    ASSERT_EQ(nodes.getCount(), 4u);
    ASSERT_EQ(edges.getCount(), 2u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 5u);
    EXPECT_EQ(edges.getCount(), 4u);
}

GTEST_TEST(DCEL_Sweep, ColinearIntersection)
{
    NodeTable nodes(Rect2D(-10, -10, 20, 20));

    // Create two diagonal lines which share some of their span.
    ID first = nodes.addNode(Point2D(0, 0)).getID();
    ID second = nodes.addNode(Point2D(10, 10)).getID();
    ID third = nodes.addNode(Point2D(5, 5)).getID();
    ID fourth = nodes.addNode(Point2D(15, 15)).getID();

    EdgeTable edges(4);
    edges.addEdge(nodes, first, second);
    edges.addEdge(nodes, third, fourth);

    ASSERT_EQ(nodes.getCount(), 4u);
    ASSERT_EQ(edges.getCount(), 2u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 4u);
    EXPECT_EQ(edges.getCount(), 3u);
}

GTEST_TEST(DCEL_Sweep, PartitionStar)
{
    // Calculate the tips of a 5-pointed star.
    constexpr size_t PointCount = 5;
    constexpr double Radius = 10.0;
    const Point2D centre(0, 0);
    const Point2D tip(0.0, Radius);
    Point2DCollection points;
    points.reserve(PointCount);

    for (int i = 0; i < PointCount; ++i)
    {
        Angle rotation = Angle::fromDegrees((360.0 / PointCount) * i);

        points.push_back(centre + tip.rotateCCW(rotation.toRadians()));
    }

    IndexRange starIndices(0, 5);
    GlyphInfo metadata(&starIndices, 1, reinterpret_cast<PrimVertex *>(points.data()));

    NodeTable nodes(metadata.Range);
    NodePtrCollection nodePtrs;
    nodePtrs.reserve(PointCount);

    for (size_t i = 0; i < PointCount; ++i)
    {
        nodePtrs.push_back(&nodes.addNode(points[i]));
    }

    // Create lines which cross to define a 5-pointed star.
    EdgeTable edges(15);
    edges.addEdge(nodes, nodePtrs[0]->getID(), nodePtrs[2]->getID());
    edges.addEdge(nodes, nodePtrs[2]->getID(), nodePtrs[4]->getID());
    edges.addEdge(nodes, nodePtrs[4]->getID(), nodePtrs[1]->getID());
    edges.addEdge(nodes, nodePtrs[1]->getID(), nodePtrs[3]->getID());
    edges.addEdge(nodes, nodePtrs[3]->getID(), nodePtrs[0]->getID());

    ASSERT_EQ(nodes.getCount(), 5u);
    ASSERT_EQ(edges.getCount(), 5u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 10u);
    EXPECT_EQ(edges.getCount(), 15u);
}

GTEST_TEST(DCEL_Sweep, HorzOverlappingRects)
{
    NodeTable nodes(Rect2D(0, 0, 20, 20));
    EdgeTable edges;

    // Add two horizontally overlapping rectangles.
    RectIndices firstRect = addRect(edges, nodes, 2, 2, 8, 4);
    RectIndices secondRect = addRect(edges, nodes, 6, 2, 8, 4);

    ASSERT_EQ(nodes.getCount(), 8u);
    ASSERT_EQ(edges.getCount(), 8u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 8u);
    EXPECT_EQ(edges.getCount(), 10u);
}

GTEST_TEST(DCEL_Sweep, VertOverlappingRects)
{
    NodeTable nodes(Rect2D(0, 0, 20, 20));
    EdgeTable edges;

    // Add two horizontally overlapping rectangles.
    RectIndices firstRect = addRect(edges, nodes, 2, 2, 4, 8);
    RectIndices secondRect = addRect(edges, nodes, 2, 6, 4, 8);

    ASSERT_EQ(nodes.getCount(), 8u);
    ASSERT_EQ(edges.getCount(), 8u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 8u);
    EXPECT_EQ(edges.getCount(), 10u);
}

GTEST_TEST(DCEL_Sweep, CascadingRects)
{
    NodeTable nodes(Rect2D(0, 0, 20, 20));
    EdgeTable edges;

    // Add two horizontally overlapping rectangles.
    RectIndices firstRect = addRect(edges, nodes, 2, 2, 8, 4);
    RectIndices secondRect = addRect(edges, nodes, 6, 4, 8, 4);

    ASSERT_EQ(nodes.getCount(), 8u);
    ASSERT_EQ(edges.getCount(), 8u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 10u);
    EXPECT_EQ(edges.getCount(), 12u);
}

GTEST_TEST(DCEL_Sweep, SingleVertLineRectWithHole)
{
    static const PrimVertex vertices[] = {
        { 2, 8 },
        { 5, 8 },
        { 5, 3 },
        { 8, 3 },
        { 8, 7 },
        { 5, 7 },
        { 5, 8 },
        { 10, 8 },
        { 10, 2 },
        { 2, 2 },
        { 2, 8 }
    };

    static const IndexRange indices(0, static_cast<ID>(std::size(vertices)));

    // Create a rectangle with a whole using a co-linear edge:
    //
    // +-----+---------------+
    // |     |               |
    // |     /--------+      |
    // |     |        |      |
    // |     +--------+      |
    // |                     |
    // +---------------------+
    //
    GlyphInfo metadata(&indices, 1, vertices);

    NodeTable nodes(metadata.Range);
    EdgeTable edges;

    addGlyph(nodes, edges, &indices, 1, vertices);

    ASSERT_EQ(nodes.getCount(), 9u);
    ASSERT_EQ(edges.getCount(), 10u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 9u);
    EXPECT_EQ(edges.getCount(), 10u);

    RingSystem rings;
    rings.build(nodes, edges);

    // Expect one edge to be removed.
    EXPECT_EQ(edges.removeUnassignedEdges(static_cast<ID>(rings.getRingCount())), 1u);
    EXPECT_EQ(edges.getCount(), 9u);

    EXPECT_EQ(nodes.removeDisconnectedNodes(edges), 0u);
    EXPECT_EQ(nodes.getCount(), 9u);

    EXPECT_EQ(rings.getRingCount(), 2u);
    EXPECT_EQ(rings.getFilledCount(), 1u);
    EXPECT_EQ(rings.getHoleCount(), 1u);
}

GTEST_TEST(DCEL_Sweep, SingleHorzLineRectWithHole)
{
    static const PrimVertex vertices[] = {
        { 2, 8 },
        { 10, 8 },
        { 10, 2 },
        { 2, 2 },
        { 2, 7 },
        { 8, 7 },
        { 8, 3 },
        { 5, 3 },
        { 5, 7 },
        { 2, 7 },
        { 2, 8 }
    };

    static const IndexRange indices(0, static_cast<ID>(std::size(vertices)));

    // Create a rectangle with a whole using a co-linear edge:
    //
    // +---------------------+
    // |                     |
    // +-----/--------+      |
    // |     |        |      |
    // |     +--------+      |
    // |                     |
    // +---------------------+
    //
    GlyphInfo metadata(&indices, 1, vertices);

    NodeTable nodes(metadata.Range);
    EdgeTable edges;

    addGlyph(nodes, edges, &indices, 1, vertices);

    ASSERT_EQ(nodes.getCount(), 9u);
    ASSERT_EQ(edges.getCount(), 10u);

    EXPECT_TRUE(findAllIntersections(nodes, edges));

    EXPECT_EQ(nodes.getCount(), 9u);
    EXPECT_EQ(edges.getCount(), 10u);

    RingSystem rings;
    rings.build(nodes, edges);

    // Expect one edge to be removed.
    EXPECT_EQ(edges.removeUnassignedEdges(static_cast<ID>(rings.getRingCount())), 1u);
    EXPECT_EQ(edges.getCount(), 9u);

    EXPECT_EQ(nodes.removeDisconnectedNodes(edges), 0u);
    EXPECT_EQ(nodes.getCount(), 9u);

    EXPECT_EQ(rings.getRingCount(), 2u);
    EXPECT_EQ(rings.getFilledCount(), 1u);
    EXPECT_EQ(rings.getHoleCount(), 1u);
}

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

