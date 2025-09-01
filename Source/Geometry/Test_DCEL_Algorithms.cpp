//! @file Geometry/Test_DCEL_Algorithms.cpp
//! @brief The definition of unit tests for algorithms which operate on a
//! doubly connected edge list.
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

#include "Ag/Geometry/LineSeg2D.hpp"
#include "Ag/Geometry/DCEL_Algorithms.hpp"
#include "DCEL_RingTracer.hpp"
#include "DCEL_Triangulate.hpp"
#include "Test_DCEL_Tools.hpp"

#include "Test_GlyphData.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const IndexRange DiamondWithHole_Indices[] = { { 0, 4 }, { 4, 4} };
static const PrimVertex DiamondWithHole_Vertices[] = {
    { 5, 10 },
    { 7, 8 },
    { 5, 6 },
    { 3, 8 },
    { 5, 12 },
    { 9, 8 },
    { 5, 4 },
    { 1, 8 }
};

static const IndexRange SimpleA_Indices[] = { { 0, 8 }, { 8, 3 } };
static const PrimVertex SimpleA_Vertices[] = {
    { -3, 0 },
    { 203, 0 },
    { 364, 444 },
    { 977, 444 },
    { 1148, 0 },
    { 1369, 0 },
    { 769, 1466 },
    { 560, 1466 },

    { 420, 602 },
    { 660, 1312 },
    { 917, 602 },
};

// These are taken from the horizontal cross on the pound glyph, which is a
// rectangle, but formed from 8 points because of intermediate points on the
// top and bottom horizontal lines.
static const IndexRange ComplexRect_Indices[] = { { 0, 8 } };
static const PrimVertex ComplexRect_Vertices[] = {
    { 44.00, 661.00 },
    { 240.00, 661.00 },
    { 427.00, 661.00 },
    { 711.00, 661.00 },
    { 711.00, 809.00 },
    { 396.00, 809.00 },
    { 198.00, 809.00 },
    { 44.00, 809.00 },
};

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Trace, Rectangle)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    RectIndices firstIndices = addRect(edges, nodes, -10, -15, 20, 30);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(edges.getCount(), 4u);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 1u);

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 4u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_Trace, ButtingRectangles)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    RectIndices firstIndices = addRect(edges, nodes, -10, -15, 20, 30);
    RectIndices secondIndices = addRect(edges, nodes, 10, -15, 10, 30);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(edges.getCount(), 7u);

    // Verify the shared edge.
    EXPECT_EQ(firstIndices.TR, secondIndices.TL);
    EXPECT_EQ(firstIndices.BR, secondIndices.BL);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 2u);

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 4u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_Trace, OneSharedCorner)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    // Create a geometry with one rectangle sharing a corner with another.
    RectIndices firstIndices = addRect(edges, nodes, 5, 6, 5, 3);
    RectIndices secondIndices = addRect(edges, nodes, 10, 9, 10, 4);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(nodes.getCount(), 7u);
    EXPECT_EQ(edges.getCount(), 8u);

    // Verify the shared edge.
    EXPECT_EQ(firstIndices.TR, secondIndices.BL);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 2u);

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 4u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_Trace, CascadingRectangles)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create a geometry of three rectangles, the middle one sharing
    // opposite corners with siblings.
    RectIndices firstIndices = addRect(edges, nodes, 5, 6, 5, 3);
    RectIndices secondIndices = addRect(edges, nodes, 10, 9, 10, 4);
    RectIndices thirdIndices = addRect(edges, nodes, 20, 13, 10, 5);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(nodes.getCount(), 10u);
    EXPECT_EQ(edges.getCount(), 12u);

    // Verify the shared edge.
    EXPECT_EQ(firstIndices.TR, secondIndices.BL);
    EXPECT_EQ(secondIndices.TR, thirdIndices.BL);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 3u);

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_FALSE(ring.hasHoles());
        EXPECT_EQ(ring.getNodeCount(), 4u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_Trace, TwoSharedCorners)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create a geometry of a rectangle with two other rectangles sharing
    // different corners of the original.
    RectIndices firstIndices = addRect(edges, nodes, 5, 6, 5, 3);
    RectIndices secondIndices = addRect(edges, nodes, 10, 9, 10, 4);
    RectIndices thirdIndices = addRect(edges, nodes, 10, -3, 8, 9);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(nodes.getCount(), 10u);
    EXPECT_EQ(edges.getCount(), 12u);

    // Verify the shared edge.
    EXPECT_EQ(firstIndices.TR, secondIndices.BL);
    EXPECT_EQ(firstIndices.BR, thirdIndices.TL);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 3u);

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_FALSE(ring.isHole());
        EXPECT_FALSE(ring.hasHoles());
        EXPECT_EQ(ring.getNodeCount(), 4u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_Trace, NestedRectangles)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    // Create geometry of one rectangle inside another.
    RectIndices firstIndices = addRect(edges, nodes, 5, 6, 5, 3);
    RectIndices secondIndices = addRect(edges, nodes, 4, 5, 7, 5);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(nodes.getCount(), 8u);
    EXPECT_EQ(edges.getCount(), 8u);

    auto rings = traceRings(nodes, edges);

    EXPECT_EQ(rings.size(), 2u);

    size_t ccwCount = 0;

    for (const Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_EQ(ring.getParentRingID() == NullID, ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 4u);

        if (ring.isCCW())
            ++ccwCount;
    }

    EXPECT_EQ(ccwCount, 1u);
}

GTEST_TEST(DCEL_Trace, DiamondWithHole)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create diamond intended to be a hole.
    addPolygon(edges, nodes, {
                            { 5, 10 },
                            { 7, 8 },
                            { 5, 6 },
                            { 3, 8 } });

    // Add an outer diamond to surround the hole.
    addPolygon(edges, nodes, {
                            { 5, 12 },
                            { 9, 8 },
                            { 5, 4 },
                            { 1, 8 } });

    RingCollection rings = traceRings(nodes, edges, false);

    ASSERT_EQ(rings.size(), 2u);

    size_t holeCount = 0;

    for (const Ring &ring : rings)
    {
        if (ring.isHole())
        {
            EXPECT_FALSE(ring.isCCW());
            ++holeCount;
        }
        else
        {
            EXPECT_TRUE(ring.isCCW());
            EXPECT_NE(ring.getFlags() & Ring::HasChildren, 0u);
        }
    }

    EXPECT_EQ(holeCount, 1u);
}

GTEST_TEST(DCEL_Trace, SimpleA)
{
    NodeTable nodes(Rect2D(-3, -100, 100, 100));
    EdgeTable edges(12);

    addGlyph(nodes, edges, SimpleA_Indices,
             std::size(SimpleA_Indices), SimpleA_Vertices);

    RingSystem rings;
    rings.build(nodes, edges, false);

    EXPECT_EQ(rings.getFilledCount(), 1u);
    EXPECT_EQ(rings.getHoleCount(), 1u);

    size_t holeCount = 0;

    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
        {
            EXPECT_FALSE(ring.isCCW());
            ++holeCount;
        }
        else
        {
            EXPECT_TRUE(ring.isCCW());
            EXPECT_NE(ring.getFlags() & Ring::HasChildren, 0u);
        }
    }
}

GTEST_TEST(DCEL_Trace, PlaceOfSajdah)
{
    NodeTable nodes(Rect2D(-3, -100, 100, 100));
    EdgeTable edges(12);

    constexpr uint32_t FigureCount = static_cast<uint32_t>(std::size(PlaceOfSajdah_Indices));

    addGlyph(nodes, edges,
             PlaceOfSajdah_Indices, FigureCount,
             PlaceOfSajdah_Vertices);

    RingSystem rings;
    rings.build(nodes, edges, false);

    EXPECT_EQ(rings.getFilledCount(), FigureCount / 2);
    EXPECT_EQ(rings.getHoleCount(), FigureCount / 2);

    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
        {
            EXPECT_FALSE(ring.isCCW());
        }
        else
        {
            EXPECT_TRUE(ring.isCCW());
            EXPECT_NE(ring.getFlags() & Ring::HasChildren, 0u);
        }
    }
}

GTEST_TEST(DCEL_MonotoneCheck, TriangleIsMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    auto IDs = addPolygon(edges, nodes, {
                          { 10, 10 },
                          { 15, 15 },
                          { 20, 5 }
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 3u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, ConvexIsMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    auto IDs = addPolygon(edges, nodes, {
                          { 10, 10 },
                          { 15, 15 },
                          { 20, 7 },
                          { 17, 5 },
                          { 12, 8 }
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 5u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, WideAndShallowIsXMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    auto IDs = addPolygon(edges, nodes, {
                          { 20, 7 },
                          { 17, 5 },
                          { 12, 8 },
                          { 11, 6 },
                          { 10, 10 },
                          { 15, 15 },
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_FALSE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_FALSE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 6u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, NarrowAndDeepIsYMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    auto IDs = addPolygon(edges, nodes, {
                          { 10, 10 },
                          { 12, 15 },
                          { 13, 8 },
                          { 14, 5 },
                          { 10, 4 },
                          { 11, 6 },
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_FALSE(ring.isConvex());
        EXPECT_FALSE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 6u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, HorizontalBoxIsXMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    // A rectangle with a kink in the top edge is still X monotone.
    auto IDs = addPolygon(edges, nodes, {
                          { 15, 4 },
                          { 10, 4 },
                          { 10, 10 },
                          { 12, 10 },
                          { 13, 11 },
                          { 14, 10 },
                          { 15, 10 },
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_FALSE(ring.isConvex());
        EXPECT_TRUE(ring.isXMonotone());
        EXPECT_FALSE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 7u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, VerticalBoxIsYMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    // Create a vertical box with a kink on the side.
    auto IDs = addPolygon(edges, nodes, {
                          { 11, 6 },
                          { 10, 7 },
                          { 10, 10 },
                          { 13, 10 },
                          { 13, 2 },
                          { 10, 2 },
                          { 10, 5 }
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_FALSE(ring.isConvex());
        EXPECT_FALSE(ring.isXMonotone());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 7u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MonotoneCheck, FivePointStarNotMonotone)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(8);

    // Create 5-pointed star.
    auto IDs = addPolygon(edges, nodes, {
                            { 8, 2 },
                            { 9, 2 },
                            { 10, 3 },
                            { 11, 2 },
                            { 12, 2 },
                            { 10.5, 1 },
                            { 11.5, 0 },
                            { 10, 0.5 },
                            { 8.5, 0 },
                            { 9.5, 1 },
                          });

    RingCollection rings = traceRings(nodes, edges);

    ASSERT_EQ(rings.size(), 1u);

    // Find an edge we know to be on the CCW wound polygon and ensure it is.
    HalfEdgePtr ccwEdge;
    ASSERT_TRUE(edges.tryFindHalfEdgeByNodes(IDs[1], IDs[0], ccwEdge));

    ASSERT_NE(ccwEdge->getRingID(), NullID);
    ASSERT_LT(static_cast<size_t>(ccwEdge->getRingID()), rings.size());
    EXPECT_TRUE(rings[ccwEdge->getRingID()].isCCW());

    for (Ring &ring : rings)
    {
        verifyRing(edges, ring);

        EXPECT_TRUE(ring.isCCW());
        EXPECT_FALSE(ring.isConvex());
        EXPECT_FALSE(ring.isXMonotone());
        EXPECT_FALSE(ring.isYMonotone());
        EXPECT_EQ(ring.getNodeCount(), 10u);
        EXPECT_EQ(ring.getParentRingID(), NullID);
    }
}

GTEST_TEST(DCEL_MakeYMonotone, DiamondWithHole)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create diamond intended to be a hole.
    addPolygon(edges, nodes, {
                            { 5, 10 },
                            { 7, 8 },
                            { 5, 6 },
                            { 3, 8 } });

    // Add an outer diamond to surround the hole.
    addPolygon(edges, nodes, {
                            { 5, 12 },
                            { 9, 8 },
                            { 5, 4 },
                            { 1, 8 },
               });

    RingSystem rings;
    rings.build(nodes, edges, false);

    ASSERT_EQ(rings.getRingCount(), 2u);

    EXPECT_TRUE(makeYMonotone(nodes, edges, rings));

    for (const Ring &ring : rings.getRings())
        dumpRingGeometry(ring);

    EXPECT_EQ(rings.getRingCount(), 3u);
    EXPECT_EQ(rings.getFilledCount(), 2u);
    EXPECT_EQ(rings.getHoleCount(), 1u);
    int holeCount = 0;

    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
        {
            ++holeCount;
        }
        else
        {
            EXPECT_TRUE(ring.isYMonotone());
        }
    }

    EXPECT_EQ(1, holeCount);
}

GTEST_TEST(DCEL_MakeYMonotone, StarShape)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create 5-pointed star.
    auto IDs = addPolygon(edges, nodes, {
                            { 8, 2 },
                            { 9, 2 },
                            { 10, 3 },
                            { 11, 2 },
                            { 12, 2 },
                            { 10.5, 1 },
                            { 11.5, 0 },
                            { 10, 0.5 },
                            { 8.5, 0 },
                            { 9.5, 1 },
                          });

    RingSystem rings;
    rings.build(nodes, edges, false);

    ASSERT_EQ(rings.getRingCount(), 1u);

    EXPECT_TRUE(makeYMonotone(nodes, edges, rings));
    EXPECT_GT(rings.getRingCount(), 1u);

    for (const Ring &ring : rings.getRings())
    {
        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isYMonotone());
    }
}

struct TestPath
{
    using IndexRange = std::pair<uint32_t, uint32_t>;
    using Vertex = std::pair<double, double>;

    std::string_view Name;
    const IndexRange *Indices;
    const Vertex *Vertices;
    size_t FigureCount;
    size_t VertexCount;

    TestPath(const std::string_view &name,
             const IndexRange *indices, size_t figureCount,
             const Vertex *vertices, size_t vertexCount) :
        Name(name),
        Indices(indices),
        Vertices(vertices),
        FigureCount(figureCount),
        VertexCount(vertexCount)
    {
    }

    template<size_t TFigureCount, size_t TVertexCount>
    TestPath(const std::string_view &name,
             const IndexRange(&indices)[TFigureCount],
             const Vertex(&vertices)[TVertexCount]) :
        Name(name),
        Indices(indices),
        Vertices(vertices),
        FigureCount(TFigureCount),
        VertexCount(TVertexCount)
    {
    }
};

class DCELTests : public testing::TestWithParam<TestPath>
{
};

TEST_P(DCELTests, Triangulate)
{
    // Get the geometry to triangulate.
    auto testPath = GetParam();

    ASSERT_GT(testPath.VertexCount, 0u);
    ASSERT_GT(testPath.FigureCount, 0u);

    // Calculate the extents of all vertices.
    auto vertices = reinterpret_cast<const Point2D *>(testPath.Vertices);

    Rect2D domain(vertices[0]);

    for (size_t i = 1, j = testPath.VertexCount; i < j; ++i)
    {
        domain.combineTo(vertices[i]);
    }

    // Create structures to manage the doubly-connected edge list.
    NodeTable nodes(domain);
    EdgeTable edges(64);

    // Add the geometry for the path.
    addGlyph(nodes, edges, testPath.Indices,
             testPath.FigureCount,
             testPath.Vertices);

    dumpFigures(nodes, testPath.Vertices, testPath.Indices, testPath.FigureCount);

    //dumpNodes(nodes);
    //dumpEdges(edges);

    RingSystem rings;
    rings.build(nodes, edges, false);

    EXPECT_EQ(rings.getRingCount(), testPath.FigureCount);

    EXPECT_TRUE(makeYMonotone(nodes, edges, rings));
    size_t yMonotoneSize = rings.getRingCount();

    // There should be at least as many y-monotone polygons as figures.
    EXPECT_GE(yMonotoneSize, testPath.FigureCount);

    for (const Ring &ring : rings.getRings())
    {
        dumpRingGeometry(ring);
        //dumpRingNodes(ring);
    }

    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
            continue;

        EXPECT_TRUE(ring.isYMonotone());

        // Triangulate the monotone polygon.
        //dumpRingNodes(ring);
        IDCollection triangles = triangulateRing(ring);

        // Ensure we have enough triangles.
        ASSERT_EQ(0u, triangles.size() % 3);
        ASSERT_EQ((ring.getNodeCount() - 2) * 3, triangles.size());

        for (size_t i = 0; i < triangles.size(); i += 3)
        {
            // Ensure the triangles are all wound CCW.
            ID firstID = triangles[i];
            ID secondID = triangles[i + 1];
            ID thirdID = triangles[i + 2];

            Node &first = nodes[firstID];
            Node &second = nodes[secondID];
            Node &third = nodes[thirdID];

            LineSeg2D mainEdge(first.getRealPosition(), second.getRealPosition());

            EXPECT_GT(mainEdge.getDeterminant(third.getRealPosition()), 0.0);
        }
    }
}

static const TestPath triangulationPaths[] = {
    TestPath("DiomondWithHole", DiamondWithHole_Indices, DiamondWithHole_Vertices),
    TestPath("SimpleA", SimpleA_Indices, SimpleA_Vertices),
    TestPath("AnA", AnA_Indices, AnA_Vertices),
    TestPath("AnB", AnB_Indices, AnB_Vertices),
    TestPath("An_e", An_e_Indices, An_e_Vertices),

    // TODO: See DCEL_Triangulate.PoundGlyph for why this fails.
    TestPath("PoundGlyph", Pound_Indices, Pound_Vertices),
    TestPath("Pilcrow", Pilcrow_Indices, Pilcrow_Vertices),
    TestPath("PlaceOfSajdah", PlaceOfSajdah_Indices, PlaceOfSajdah_Vertices),
    TestPath("SmilieFace", SmilingFace_Indices, SmilingFace_Vertices),

    // TODO: This fails because after partitioning, the algorithm cannot
    // re-generate the original holes.
    TestPath("BlackFace", BlackFace_Indices, BlackFace_Vertices),
};

INSTANTIATE_TEST_SUITE_P(Triangulate,
                         DCELTests,
                         testing::ValuesIn(triangulationPaths),
                         [](const testing::TestParamInfo<DCELTests::ParamType> &info)
                         {
                             return std::string(info.param.Name);
                         });


GTEST_TEST(DCEL_Triangulate, DiamondWithHole)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create diamond intended to be a hole.
    addPolygon(edges, nodes, {
                            { 5, 10 },
                            { 7, 8 },
                            { 5, 6 },
                            { 3, 8 } });

    // Add an outer diamond to surround the hole.
    addPolygon(edges, nodes, {
                            { 5, 12 },
                            { 9, 8 },
                            { 5, 4 },
                            { 1, 8 },
               });

    RingSystem rings;
    rings.build(nodes, edges, false);

    ASSERT_EQ(rings.getRingCount(), 2u);

    EXPECT_TRUE(makeYMonotone(nodes, edges, rings));
    size_t yMonotoneSize = rings.getRingCount();
    EXPECT_EQ(yMonotoneSize, 3u);
    EXPECT_EQ(rings.getFilledCount(), 2u);
    EXPECT_EQ(rings.getHoleCount(), 1u);

    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
            continue;

        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_FALSE(ring.isHole());

        // Triangulate the monotone polygon.
        dumpRingNodes(ring);
        IDCollection triangles = triangulateRing(ring);

        // Ensure we have enough triangles.
        ASSERT_EQ(0u, triangles.size() % 3);
        EXPECT_EQ((ring.getNodeCount() - 2) * 3, triangles.size());

        for (size_t i = 0; i < triangles.size(); i += 3)
        {
            // Ensure the triangles are all wound CCW.
            ID firstID = triangles[i];
            ID secondID = triangles[i + 1];
            ID thirdID = triangles[i + 2];

            Node &first = nodes[firstID];
            Node &second = nodes[secondID];
            Node &third = nodes[thirdID];

            LineSeg2D mainEdge(first.getRealPosition(), second.getRealPosition());

            EXPECT_GT(mainEdge.getDeterminant(third.getRealPosition()), 0.0);
        }
    }
}

GTEST_TEST(DCEL_Triangulate, StarShape)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable edges(12);

    // Create 5-pointed star.
    auto IDs = addPolygon(edges, nodes, {
                            { 8, 2 },
                            { 9, 2 },
                            { 10, 3 },
                            { 11, 2 },
                            { 12, 2 },
                            { 10.5, 1 },
                            { 11.5, 0 },
                            { 10, 0.5 },
                            { 8.5, 0 },
                            { 9.5, 1 },
                          });

    RingSystem rings;
    rings.build(nodes, edges, false);

    ASSERT_EQ(rings.getRingCount(), 1u);

    EXPECT_TRUE(makeYMonotone(nodes, edges, rings));
    size_t yMonotoneSize = rings.getRingCount();
    EXPECT_EQ(yMonotoneSize, 3u);

    for (const Ring &ring : rings.getRings())
    {
        EXPECT_TRUE(ring.isCCW());
        EXPECT_TRUE(ring.isYMonotone());
        EXPECT_FALSE(ring.isHole());

        // Triangulate the monotone polygon.
        dumpRingNodes(ring);
        IDCollection triangles = triangulateRing(ring);

        // Ensure we have enough triangles.
        ASSERT_EQ(0u, triangles.size() % 3);
        ASSERT_EQ((ring.getNodeCount() - 2) * 3, triangles.size());

        for (size_t i = 0; i < triangles.size(); i += 3)
        {
            // Ensure the triangles are all wound CCW.
            ID firstID = triangles[i];
            ID secondID = triangles[i + 1];
            ID thirdID = triangles[i + 2];

            Node &first = nodes[firstID];
            Node &second = nodes[secondID];
            Node &third = nodes[thirdID];

            LineSeg2D mainEdge(first.getRealPosition(), second.getRealPosition());

            EXPECT_GT(mainEdge.getDeterminant(third.getRealPosition()), 0.0);
        }
    }
}

GTEST_TEST(DCEL_Triangulate, ComplexRect)
{
    GlyphInfo metadata(ComplexRect_Indices, std::size(ComplexRect_Indices), ComplexRect_Vertices);

    NodeTable nodes(metadata.Range, metadata.VertexCount);
    EdgeTable edges(metadata.EdgeCount);

    addGlyph(nodes, edges, ComplexRect_Indices, std::size(ComplexRect_Indices), ComplexRect_Vertices);

    RingSystem rings;
    rings.build(nodes, edges, false);

    ASSERT_GT(rings.getRingCount(), 0u);

    dumpNodes(nodes);

    // We just want to triangulate a polygon which isn't strictly Y-monotone.
    for (const Ring &ring : rings.getRings())
    {
        if (ring.isHole())
            continue;

        // Triangulate the monotone polygon.
        dumpRingGeometry(ring);
        IDCollection triangles = triangulateRing(ring);

        // Ensure we have enough triangles.
        ASSERT_EQ(0u, triangles.size() % 3);
        EXPECT_EQ((ring.getNodeCount() - 2) * 3, triangles.size());

        for (size_t i = 0; i < triangles.size(); i += 3)
        {
            // Ensure the triangles are all wound CCW.
            ID firstID = triangles[i];
            ID secondID = triangles[i + 1];
            ID thirdID = triangles[i + 2];

            Node &first = nodes[firstID];
            Node &second = nodes[secondID];
            Node &third = nodes[thirdID];

            LineSeg2D mainEdge(first.getRealPosition(), second.getRealPosition());

            EXPECT_GT(mainEdge.getDeterminant(third.getRealPosition()), 0.0);
        }
    }
}

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

