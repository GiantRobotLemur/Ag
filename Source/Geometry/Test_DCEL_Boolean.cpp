//! @file Geometry/Test_DCEL_Boolean.cpp
//! @brief The definition of unit tests for boolean operations performed on a
//! Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Test_DCEL_Tools.hpp"
#include "Ag/Geometry/DCEL_Boolean.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Builds an ExplicitRing for an axis-aligned rectangle from its
//! RectIndices. addRect adds edges in the order TL→TR→BR→BL→TL which is
//! clockwise in Y-up math coordinates, so we mark IsCCW=false and store
//! the same node order. Y-up rectangles are fill rings (not holes).
ExplicitRing makeRectRing(ID ringID, const RectIndices &rect,
                          Ring::FlagsType operandFlag)
{
    return ExplicitRing(ringID,
                        operandFlag | Ring::IsConvex,
                        rect.toCollection());
}

//! @brief Convenience: builds two operand rings from two rectangles and
//! propagates flags to the underlying nodes/edges. Suitable for tests where
//! the operands are simple rectangles built via addRect.
ExplicitRingCollection prepareOperands(NodeTable &nodes, EdgeTable &edges,
                                       const RectIndices &lhs,
                                       const RectIndices &rhs)
{
    ExplicitRingCollection rings;
    rings.reserve(2);
    rings.push_back(makeRectRing(0, lhs, Ring::IsLhs));
    rings.push_back(makeRectRing(1, rhs, Ring::IsRhs));

    markBooleanOperands(nodes, edges, rings);
    return rings;
}

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Boolean, Disjoint)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 20, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = clip(nodes, edges, rings);

    EXPECT_EQ(result.size(), 0u);
}

GTEST_TEST(DCEL_Boolean, RhsContainedInLhs)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 20, 20);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 5, 5);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = clip(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);

    Ring::FlagsType resultFlags = result[0].getFlags();
    EXPECT_EQ(resultFlags & (Ring::IsLhs | Ring::IsRhs), 0u);
}

GTEST_TEST(DCEL_Boolean, LhsContainedInRhs)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 5, 5, 5, 5);
    RectIndices rhs = addRect(edges, nodes, 0, 0, 20, 20);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = clip(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);
}

GTEST_TEST(DCEL_Boolean, OverlappingCorner)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = clip(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);

    Ring::FlagsType resultFlags = result[0].getFlags();
    EXPECT_EQ(resultFlags & (Ring::IsLhs | Ring::IsRhs), 0u);
}

GTEST_TEST(DCEL_Boolean, Identical)
{
    // Two identical input rectangles collapse to a single shared ring once
    // node positions snap. This case exercises the "ring is both Lhs and Rhs"
    // path — the result of intersecting a region with itself is the region.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices rect = addRect(edges, nodes, 0, 0, 10, 10);

    ExplicitRingCollection rings;
    rings.push_back(makeRectRing(0, rect, Ring::IsLhs | Ring::IsRhs));
    markBooleanOperands(nodes, edges, rings);

    auto result = clip(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);
}

GTEST_TEST(DCEL_Boolean, SharedEdge)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 10, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = clip(nodes, edges, rings);

    EXPECT_EQ(result.size(), 0u);
}

////////////////////////////////////////////////////////////////////////////////
// Unite (boolean OR) tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Boolean, UniteDisjoint)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 20, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = unite(nodes, edges, rings);

    EXPECT_EQ(result.size(), 2u);
}

GTEST_TEST(DCEL_Boolean, UniteRhsContainedInLhs)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 20, 20);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 5, 5);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = unite(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);
}

GTEST_TEST(DCEL_Boolean, UniteOverlappingCorner)
{
    // Lhs (0,0,10,10) and Rhs (5,5,10,10) overlap. Their union forms an
    // L-shape with eight vertices: the four exterior Lhs/Rhs corners not
    // shared with the overlap, plus the two intersection points.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = unite(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 8u);
}

GTEST_TEST(DCEL_Boolean, UniteIdentical)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices rect = addRect(edges, nodes, 0, 0, 10, 10);

    ExplicitRingCollection rings;
    rings.push_back(makeRectRing(0, rect, Ring::IsLhs | Ring::IsRhs));
    markBooleanOperands(nodes, edges, rings);

    auto result = unite(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 4u);
}

GTEST_TEST(DCEL_Boolean, UniteSharedEdge)
{
    // Two rectangles abutting along a shared edge merge into a single
    // wider rectangle - the shared edge is interior to the union.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 10, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = unite(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    // 6 vertices: 4 outer corners + 2 endpoints of the (now collinear)
    // shared boundary that remain because they are also corners of the
    // combined outline.
    EXPECT_EQ(result[0].getNodes().size(), 6u);
}

////////////////////////////////////////////////////////////////////////////////
// SymmetricDifference (boolean XOR) tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Boolean, XorDisjoint)
{
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 20, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = symmetricDifference(nodes, edges, rings);

    EXPECT_EQ(result.size(), 2u);
}

GTEST_TEST(DCEL_Boolean, XorIdentical)
{
    // The symmetric difference of a region with itself is empty.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices rect = addRect(edges, nodes, 0, 0, 10, 10);

    ExplicitRingCollection rings;
    rings.push_back(makeRectRing(0, rect, Ring::IsLhs | Ring::IsRhs));
    markBooleanOperands(nodes, edges, rings);

    auto result = symmetricDifference(nodes, edges, rings);

    EXPECT_EQ(result.size(), 0u);
}

GTEST_TEST(DCEL_Boolean, XorSharedEdge)
{
    // Two rectangles abutting along a shared edge: the symmetric difference
    // is the union (no overlap, so XOR == OR), a single wider rectangle.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 10, 0, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = symmetricDifference(nodes, edges, rings);

    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0].getNodes().size(), 6u);
}

GTEST_TEST(DCEL_Boolean, XorRhsContainedInLhs)
{
    // When Rhs is fully inside Lhs, XOR is the donut: outer Lhs boundary
    // (filled ring) plus inner Rhs boundary (hole).
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 20, 20);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 5, 5);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = symmetricDifference(nodes, edges, rings);

    ASSERT_EQ(result.size(), 2u);

    size_t fills = 0;
    size_t holes = 0;
    for (const auto &r : result)
    {
        if (r.getFlags() & Ring::IsHole)
            ++holes;
        else
            ++fills;
    }
    EXPECT_EQ(fills, 1u);
    EXPECT_EQ(holes, 1u);
}

GTEST_TEST(DCEL_Boolean, XorOverlappingCorner)
{
    // Two overlapping rectangles produce two L-shaped components in the
    // symmetric difference (Lhs - Rhs and Rhs - Lhs), meeting only at the
    // two intersection vertices.
    NodeTable nodes(Rect2D(-50, -50, 100, 100));
    EdgeTable edges;

    RectIndices lhs = addRect(edges, nodes, 0, 0, 10, 10);
    RectIndices rhs = addRect(edges, nodes, 5, 5, 10, 10);

    auto rings = prepareOperands(nodes, edges, lhs, rhs);

    auto result = symmetricDifference(nodes, edges, rings);

    EXPECT_EQ(result.size(), 2u);
    for (const auto &r : result)
    {
        EXPECT_EQ(r.getNodes().size(), 6u);
    }
}

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////
