//! @file Geometry/Test_DCEL.cpp
//! @brief The definition of unit tests for the structure which form part of
//! the Doubly-Connected Edge List namespace.
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

#include "Ag/Geometry/DCEL.hpp"

#include "GtestHelpers.hpp"
#include "Test_DCEL_Tools.hpp"

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

////////////////////////////////////////////////////////////////////////////////
// Unit Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(DCEL_Nodes, ConstructNode)
{
    constexpr ID id = 42;
    const Point2D position(1, 10);
    const SnapPoint gridPosition(100, 1000);

    Node specimen(id, position, gridPosition);

    EXPECT_EQ(specimen.getID(), id);
    EXPECT_EQ(specimen.getRealPosition(), position);
    EXPECT_EQ(specimen.getGridPosition(), gridPosition);
}

GTEST_TEST(DCEL_Nodes, ConstructTable)
{
    NodeTable specimen(Rect2D(-10, -10, 20, 20));

    EXPECT_TRUE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 0u);
}

GTEST_TEST(DCEL_Nodes, AddNodes)
{
    NodeTable specimen(Rect2D(-100, -100, 200, 200));

    RectIndices firstIndices = addRect(specimen, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);
    EXPECT_TRUE(indicesUnique(firstIndices.toCollection()));

    // Add a second rectangle which shares nodes with the previous one.
    RectIndices secondIndices = addRect(specimen, 10, -15, 10, 30);

    // Ensure the coincident points are represented by a single node.
    EXPECT_EQ(specimen.getCount(), 6u);
    EXPECT_TRUE(indicesUnique(secondIndices.toCollection()));

    EXPECT_EQ(firstIndices.TR, secondIndices.TL);
    EXPECT_EQ(firstIndices.BR, secondIndices.BL);
}

GTEST_TEST(DCEL_Nodes, FindNodeByID)
{
    NodeTable specimen(Rect2D(-100, -100, 200, 200));

    RectIndices indices = addRect(specimen, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    NodePtr node;

    ASSERT_TRUE(specimen.tryFindNodeByID(indices.BL, node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.BL);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(-10, -15)));

    ASSERT_TRUE(specimen.tryFindNodeByID(indices.BR, node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.BR);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(10, -15)));

    ASSERT_TRUE(specimen.tryFindNodeByID(indices.TL, node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.TL);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(-10, 15)));

    ASSERT_TRUE(specimen.tryFindNodeByID(indices.TR, node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.TR);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(10, 15)));

    // Test the negative case.
    ASSERT_FALSE(specimen.tryFindNodeByID(specimen.getCount() + 5, node));
    EXPECT_EQ(node, nullptr);
}

GTEST_TEST(DCEL_Nodes, FindNodeByPosition)
{
    NodeTable specimen(Rect2D(-100, -100, 200, 200));

    RectIndices indices = addRect(specimen, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    NodePtr node;

    ASSERT_TRUE(specimen.tryFindNodeByPosition(Point2D(-10, -15), node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.BL);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(-10, -15)));

    ASSERT_TRUE(specimen.tryFindNodeByPosition(Point2D(10, -15), node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.BR);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(10, -15)));

    ASSERT_TRUE(specimen.tryFindNodeByPosition(Point2D(-10, 15), node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.TL);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(-10, 15)));

    ASSERT_TRUE(specimen.tryFindNodeByPosition(Point2D(10, 15), node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.TR);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(10, 15)));

    // Test the negative case.
    ASSERT_FALSE(specimen.tryFindNodeByPosition(Point2D(), node));
    EXPECT_EQ(node, nullptr);
}

GTEST_TEST(DCEL_Nodes, RemoveNode)
{
    NodeTable specimen(Rect2D(-100, -100, 100, 100));

    RectIndices indices = addRect(specimen, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    NodePtr node;

    // Ensure the Bottom Left node exists.
    ASSERT_TRUE(specimen.tryFindNodeByID(indices.BL, node));
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->getID(), indices.BL);
    EXPECT_TRUE(isNear(specimen.getGrid(), node->getRealPosition(), Point2D(-10, -15)));

    // Remove the node.
    specimen.removeNode(indices.BL);

    // Ensure it no longer exists.
    EXPECT_FALSE(specimen.tryFindNodeByID(indices.BL, node));
    EXPECT_EQ(node, nullptr);
}

GTEST_TEST(DCEL_Edges, DefaultConstruct)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);
    EdgePtr edge = nullptr;

    EXPECT_TRUE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 0u);
    EXPECT_FALSE(specimen.tryFindEdgeByID(0, edge));
}

GTEST_TEST(DCEL_Edges, AddEdge)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices firstIndices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    // Add a second rectangle which shares nodes and an edge with the previous one.
    RectIndices secondIndices = addRect(specimen, nodes, 10, -15, 10, 30);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(specimen.getCount(), 7u);

    EXPECT_EQ(firstIndices.TR, secondIndices.TL);
    EXPECT_EQ(firstIndices.BR, secondIndices.BL);

    // Ensure the shared edge defines a single table entry.
    EdgePtr firstSharedEdge;
    EdgePtr secondSharedEdge;

    ASSERT_TRUE(specimen.tryFindEdgeByNodes(firstIndices.TR, firstIndices.BR, firstSharedEdge));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(secondIndices.TL, secondIndices.BL, secondSharedEdge));

    EXPECT_EQ(firstSharedEdge, secondSharedEdge);
}

GTEST_TEST(DCEL_Edges, RemoveEdge)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices firstIndices = addRect(specimen, nodes, -10, -15, 20, 30);
    RectIndices secondIndices = addRect(specimen, nodes, 10, -15, 10, 30);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(specimen.getCount(), 7u);

    // Ensure the shared edge defines a single table entry.
    EdgePtr sharedEdge;

    ASSERT_TRUE(specimen.tryFindEdgeByNodes(firstIndices.TR, firstIndices.BR, sharedEdge));

    // Verify the nodes at either end of the shared edge have three connections.
    auto edgesAtNode = specimen.edgesAtNode(firstIndices.TR);
    ASSERT_EQ(edgesAtNode.size(), 3u);

    edgesAtNode = specimen.edgesAtNode(firstIndices.BR);
    ASSERT_EQ(edgesAtNode.size(), 3u);

    // Remove the shared edge.
    specimen.removeEdge(sharedEdge->getID());

    EXPECT_EQ(specimen.getCount(), 6u);
    EXPECT_FALSE(specimen.tryFindEdgeByNodes(firstIndices.TR, firstIndices.BR, sharedEdge));

    // Verify the nodes at either end of the former shared edge now have two connections.
    edgesAtNode = specimen.edgesAtNode(firstIndices.TR);
    ASSERT_EQ(edgesAtNode.size(), 2u);

    edgesAtNode = specimen.edgesAtNode(firstIndices.BR);
    ASSERT_EQ(edgesAtNode.size(), 2u);
}

GTEST_TEST(DCEL_Edges, FindEdgeByNodes)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    EdgePtr tlToTr, trToBr, brToBl, blToTl;
    EdgePtr trToTl, brToTr, blToBr, tlToBl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Ensure the same edges connect corners in the opposite direction.
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TR, indices.TL, trToTl));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BR, indices.TR, brToTr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BL, indices.BR, blToBr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TL, indices.BL, tlToBl));

    EXPECT_EQ(tlToTr, trToTl);
    EXPECT_EQ(trToBr, brToTr);
    EXPECT_EQ(brToBl, blToBr);
    EXPECT_EQ(blToTl, tlToBl);

    // Ensure opposite corners aren't connected.
    EdgePtr invalidEdge;

    EXPECT_FALSE(specimen.tryFindEdgeByNodes(indices.TL, indices.BR, invalidEdge));
    EXPECT_FALSE(specimen.tryFindEdgeByNodes(indices.BL, indices.TR, invalidEdge));

    // Ensure invalid node IDs don't connect.
    EXPECT_FALSE(specimen.tryFindEdgeByNodes(nodes.getCount() + 3,
                                             nodes.getCount() + 4,
                                             invalidEdge));
}

GTEST_TEST(DCEL_Edges, FindEdgeByID)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    EdgePtr tlToTr, trToBr, brToBl, blToTl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Ensure the edges found by ID match those found by node.
    EdgePtr idEdge;

    EXPECT_TRUE(specimen.tryFindEdgeByID(tlToTr->getID(), idEdge));
    EXPECT_EQ(idEdge, tlToTr);

    EXPECT_TRUE(specimen.tryFindEdgeByID(trToBr->getID(), idEdge));
    EXPECT_EQ(idEdge, trToBr);

    EXPECT_TRUE(specimen.tryFindEdgeByID(brToBl->getID(), idEdge));
    EXPECT_EQ(idEdge, brToBl);

    EXPECT_TRUE(specimen.tryFindEdgeByID(blToTl->getID(), idEdge));
    EXPECT_EQ(idEdge, blToTl);

    // Test negative case.
    EXPECT_FALSE(specimen.tryFindEdgeByID(specimen.getCount() + 5, idEdge));
    EXPECT_EQ(idEdge, nullptr);
}

GTEST_TEST(DCEL_Edges, FindHalfEdgeByNodes)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    HalfEdgePtr tlToTr, trToBr, brToBl, blToTl;
    HalfEdgePtr trToTl, brToTr, blToBr, tlToBl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Ensure the same edges connect corners in the opposite direction.
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TR, indices.TL, trToTl));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BR, indices.TR, brToTr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BL, indices.BR, blToBr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TL, indices.BL, tlToBl));

    // Ensure the reverse of directed edges is correct in both directions.
    EXPECT_NE(tlToTr, trToTl);
    EXPECT_EQ(tlToTr->getReverse(), trToTl);
    EXPECT_EQ(trToTl->getReverse(), tlToTr);

    EXPECT_EQ(trToTl->getAngle(), Angle::fromDegrees(180.0));
    EXPECT_EQ(tlToTr->getAngle(), Angle::fromDegrees(0.0));

    EXPECT_NE(trToBr, brToTr);
    EXPECT_EQ(trToBr->getReverse(), brToTr);
    EXPECT_EQ(brToTr->getReverse(), trToBr);

    EXPECT_EQ(trToBr->getAngle(), Angle::fromDegrees(-90.0));
    EXPECT_EQ(brToTr->getAngle(), Angle::fromDegrees(90.0));

    EXPECT_NE(brToBl, blToBr);
    EXPECT_EQ(brToBl->getReverse(), blToBr);
    EXPECT_EQ(blToBr->getReverse(), brToBl);

    EXPECT_EQ(brToBl->getAngle(), Angle::fromDegrees(180.0));
    EXPECT_EQ(blToBr->getAngle(), Angle::fromDegrees(0.0));

    EXPECT_NE(blToTl, tlToBl);
    EXPECT_EQ(blToTl->getReverse(), tlToBl);
    EXPECT_EQ(tlToBl->getReverse(), blToTl);

    EXPECT_EQ(blToTl->getAngle(), Angle::fromDegrees(90.0));
    EXPECT_EQ(tlToBl->getAngle(), Angle::fromDegrees(-90.0));

    // Ensure opposite corners aren't connected.
    HalfEdgePtr invalidEdge;

    EXPECT_FALSE(specimen.tryFindHalfEdgeByNodes(indices.TL, indices.BR, invalidEdge));
    EXPECT_FALSE(specimen.tryFindHalfEdgeByNodes(indices.BL, indices.TR, invalidEdge));

    // Ensure invalid node IDs don't connect.
    EXPECT_FALSE(specimen.tryFindHalfEdgeByNodes(nodes.getCount() + 3,
                                                 nodes.getCount() + 4,
                                                 invalidEdge));
}

GTEST_TEST(DCEL_Edges, FindHalfEdgeByID)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    HalfEdgePtr tlToTr, trToBr, brToBl, blToTl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Ensure the edges found by ID match those found by node.
    HalfEdgePtr idEdge;

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(tlToTr->getID(), idEdge));
    EXPECT_EQ(idEdge, tlToTr);

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(trToBr->getID(), idEdge));
    EXPECT_EQ(idEdge, trToBr);

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(brToBl->getID(), idEdge));
    EXPECT_EQ(idEdge, brToBl);

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(blToTl->getID(), idEdge));
    EXPECT_EQ(idEdge, blToTl);

    // Test negative case.
    EXPECT_FALSE(specimen.tryFindHalfEdgeByID(HalfEdgeID(specimen.getCount() + 5, 0), idEdge));
    EXPECT_EQ(idEdge, nullptr);

    // Ensure reverse edges are found from reverse IDs.
    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(tlToTr->getID().getReverseID(), idEdge));
    EXPECT_EQ(idEdge, tlToTr->getReverse());

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(trToBr->getID().getReverseID(), idEdge));
    EXPECT_EQ(idEdge, trToBr->getReverse());

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(brToBl->getID().getReverseID(), idEdge));
    EXPECT_EQ(idEdge, brToBl->getReverse());

    ASSERT_TRUE(specimen.tryFindHalfEdgeByID(blToTl->getID().getReverseID(), idEdge));
    EXPECT_EQ(idEdge, blToTl->getReverse());
}

GTEST_TEST(DCEL_Edges, EdgesAtNode)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    EdgePtr tlToTr, trToBr, brToBl, blToTl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Get edges at Top Left.
    auto edgeCollection = specimen.edgesAtNode(indices.TL);

    ASSERT_FALSE(edgeCollection.empty());
    ASSERT_EQ(edgeCollection.size(), 2u);

    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), tlToTr), edgeCollection.end());
    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), blToTl), edgeCollection.end());

    // Get edges at Top Right.
    edgeCollection = specimen.edgesAtNode(indices.TR);

    ASSERT_FALSE(edgeCollection.empty());
    ASSERT_EQ(edgeCollection.size(), 2u);

    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), tlToTr), edgeCollection.end());
    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), trToBr), edgeCollection.end());

    // Get edges at Bottom Left.
    edgeCollection = specimen.edgesAtNode(indices.BL);

    ASSERT_FALSE(edgeCollection.empty());
    ASSERT_EQ(edgeCollection.size(), 2u);

    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), brToBl), edgeCollection.end());
    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), blToTl), edgeCollection.end());

    // Get edges at Bottom Right.
    edgeCollection = specimen.edgesAtNode(indices.BR);

    ASSERT_FALSE(edgeCollection.empty());
    ASSERT_EQ(edgeCollection.size(), 2u);

    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), brToBl), edgeCollection.end());
    EXPECT_NE(std::find(edgeCollection.begin(), edgeCollection.end(), trToBr), edgeCollection.end());
}

GTEST_TEST(DCEL_Edges, SplitEdge)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices indices = addRect(specimen, nodes, -10, -15, 20, 30);

    EXPECT_FALSE(specimen.isEmpty());
    EXPECT_EQ(specimen.getCount(), 4u);

    EdgePtr tlToTr, trToBr, brToBl, blToTl;

    // Ensure all corners are connected.
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TL, indices.TR, tlToTr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.TR, indices.BR, trToBr));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BR, indices.BL, brToBl));
    ASSERT_TRUE(specimen.tryFindEdgeByNodes(indices.BL, indices.TL, blToTl));

    // Create a node to split about.
    auto splitNode = nodes.addNode(Point2D(5.0, 20.0));

    auto splitResult = specimen.splitEdge(nodes, tlToTr->getID(), splitNode.getID());

    EXPECT_TRUE(splitResult.FirstEdge->isDefinedByNode(indices.TL));
    EXPECT_TRUE(splitResult.FirstEdge->isDefinedByNode(splitNode.getID()));

    EXPECT_TRUE(splitResult.SecondEdge->isDefinedByNode(indices.TR));
    EXPECT_TRUE(splitResult.SecondEdge->isDefinedByNode(splitNode.getID()));

    EXPECT_EQ(splitResult.SplitNode->getID(), splitNode.getID());
}

GTEST_TEST(DCEL_Edges, FindSuccessorEdge)
{
    NodeTable nodes(Rect2D(-100, -100, 100, 100));
    EdgeTable specimen(8);

    RectIndices firstIndices = addRect(specimen, nodes, -10, -15, 20, 30);
    RectIndices secondIndices = addRect(specimen, nodes, 10, -15, 10, 30);

    // Ensure the coincident points are represented by a single edge.
    EXPECT_EQ(specimen.getCount(), 7u);

    HalfEdgePtr sourceEdge;

    ASSERT_TRUE(specimen.tryFindHalfEdgeByNodes(firstIndices.BL, firstIndices.BR,
                                                sourceEdge));

    HalfEdgePtr successorEdge;
    ASSERT_TRUE(specimen.tryFindSuccessor(sourceEdge, true, successorEdge));
    EXPECT_EQ(successorEdge->getStartNodeID(), firstIndices.BR);
    EXPECT_EQ(successorEdge->getEndNodeID(), firstIndices.TR);
}

} // Anonymous namespace

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

