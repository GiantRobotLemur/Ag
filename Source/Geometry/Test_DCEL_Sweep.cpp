//! @file Geometry/Test_DCEL_Sweep.cpp
//! @brief The definition of unit tests for the a plane sweep of edges held
//! in a Doubly-Connected Edge List.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

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
    EXPECT_TRUE(pointEdge.isColinear());

    SnapPoint gridIntersection = intersectionNode->getGridPosition();
    SnapPoint gridLineIntersection = firstSweep.getSweepIntersection(context);

    EXPECT_EQ(gridIntersection, gridLineIntersection);

    gridLineIntersection = secondSweep.getSweepIntersection(context);
    EXPECT_EQ(gridIntersection, gridLineIntersection);

    gridLineIntersection = pointEdge.getSweepIntersection(context);
    EXPECT_EQ(gridIntersection, gridLineIntersection);
}

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

