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
#include <algorithm>
#include <set>

#include <gtest/gtest.h>

#include "Test_DCEL_Tools.hpp"
#include "Ag/Geometry/DCEL_Boolean.hpp"
#include "DCEL_RingTracer.hpp"

namespace Ag {
namespace Geom {
namespace DCEL {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Returns true if @p ring's node IDs are exactly the four corners of
//! @p rect.
bool ringContainsRect(const ExplicitRing &ring, const RectIndices &rect)
{
    const auto &n = ring.getNodes();
    if (n.size() != 4)
        return false;

    std::set<ID> ringSet(n.begin(), n.end());
    return ringSet.count(rect.TL) == 1 &&
           ringSet.count(rect.TR) == 1 &&
           ringSet.count(rect.BR) == 1 &&
           ringSet.count(rect.BL) == 1;
}

//! @brief Builds operand rings by tracing the existing edge table, then tags
//! each ring as Lhs or Rhs based on which input rectangle's corners appear
//! in its node list. Calls markBooleanOperands so the DCEL flags are ready
//! for clip().
ExplicitRingCollection prepareOperands(NodeTable &nodes, EdgeTable &edges,
                                       const RectIndices &lhs,
                                       const RectIndices &rhs)
{
    RingCollection traced = traceRings(nodes, edges);

    ExplicitRingCollection rings;
    rings.reserve(traced.size());

    for (const Ring &r : traced)
        rings.emplace_back(r);

    for (ExplicitRing &er : rings)
    {
        Ring::FlagsType flags = er.getFlags();

        if (ringContainsRect(er, lhs))
            flags |= Ring::IsLhs;
        else if (ringContainsRect(er, rhs))
            flags |= Ring::IsRhs;

        er.setFlags(flags);
    }

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

    addRect(edges, nodes, 0, 0, 10, 10);

    RingCollection traced = traceRings(nodes, edges);
    ASSERT_EQ(traced.size(), 1u);

    ExplicitRingCollection rings;
    rings.emplace_back(traced.front());
    rings[0].setFlags(rings[0].getFlags() | Ring::IsLhs | Ring::IsRhs);

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

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////
