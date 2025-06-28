//! @file Geometry/Test_DCEL_Tools.cpp
//! @brief The definition of tools shared between various DCEL unit tests.
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

#include "Test_DCEL_Tools.hpp"

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
// GlyphInfo Member Definitions
////////////////////////////////////////////////////////////////////////////////
GlyphInfo::GlyphInfo() :
    VertexCount(0),
    EdgeCount(0)
{
}

GlyphInfo::GlyphInfo(const IndexRange *figures, size_t figureCount,
                     const PrimVertex *vertices) :
    VertexCount(0),
    EdgeCount(0)
{
    uint32_t maxVertex = 0;

    for (size_t f = 0; f < figureCount; ++f)
    {
        const auto &figure = figures[f];
        maxVertex = std::max(maxVertex, figure.first + figure.second);
        EdgeCount += figure.second;
    }

    VertexCount = maxVertex;

    double minX = vertices[0].first;
    double maxX = minX;
    double minY = vertices[0].second;
    double maxY = minY;

    for (uint32_t i = 0; i < maxVertex; ++i)
    {
        const auto &vertex = vertices[i];
        minX = std::min(vertex.first, minX);
        maxX = std::max(vertex.first, maxX);
        minY = std::min(vertex.second, minY);
        maxY = std::max(vertex.second, maxY);
    }

    Range = Rect2D(minX, minY, maxX, maxY);
}

GlyphInfo &GlyphInfo::operator+=(const GlyphInfo &rhs)
{
    if (this != &rhs)
    {
        Range.combineTo(rhs.Range);
        VertexCount += rhs.VertexCount;
        EdgeCount += rhs.EdgeCount;
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// RectIndices Member Definitions
////////////////////////////////////////////////////////////////////////////////
RectIndices::RectIndices() :
    TL(NullID),
    TR(NullID),
    BL(NullID),
    BR(NullID)
{
}

IDCollection RectIndices::toCollection() const
{
    IDCollection indices;
    indices.reserve(4);

    indices.push_back(TL);
    indices.push_back(TR);
    indices.push_back(BR);
    indices.push_back(BL);

    return indices;
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Adds a rectangle to a node table, returning the indices.
//! @param[in] table The table to add nodes to.
//! @param[in] x The minimum horizontal offset of the rectangle.
//! @param[in] y The minimum vertical offset of the rectangle.
//! @param[in] width The non-negative width of the rectangle.
//! @param[in] height The non-negative height of the rectangle.
//! @returns The indices of the added nodes.
RectIndices addRect(NodeTable &table, double x, double y,
                    double width, double height)
{
    RectIndices indices;
    indices.BL = table.addNode(Point2D(x, y)).getID();
    indices.BR = table.addNode(Point2D(x + std::abs(width), y)).getID();
    indices.TL = table.addNode(Point2D(x, y + std::abs(height))).getID();
    indices.TR = table.addNode(Point2D(x + std::abs(width),
                                       y + std::abs(height))).getID();

    return indices;
}

//! @brief Adds the nodes and edges required to represent a rectangle.
//! @param[in] edges The table of edges to add to.
//! @param[in] nodes The table of nodes to add to.
//! @param[in] x The minimum horizontal offset of the rectangle.
//! @param[in] y The minimum vertical offset of the rectangle.
//! @param[in] width The non-negative width of the rectangle.
//! @param[in] height The non-negative height of the rectangle.
//! @returns The indices of the added nodes.
RectIndices addRect(EdgeTable &edges, NodeTable &nodes, double x, double y,
                    double width, double height)
{
    RectIndices indices = addRect(nodes, x, y, width, height);

    edges.addEdge(nodes, indices.TL, indices.TR);
    edges.addEdge(nodes, indices.TR, indices.BR);
    edges.addEdge(nodes, indices.BR, indices.BL);
    edges.addEdge(nodes, indices.BL, indices.TL);

    return indices;
}

//! @brief Adds a polygon to the mesh by defining nodes and edges.
//! @param[in] edges The table of all edges in the mesh.
//! @param[in] nodes The table of all nodes in the mesh.
//! @param[in] points The points defining the polygon.
//! @return A collection of node identifiers defining the polygon.
IDCollection addPolygon(EdgeTable &edges, NodeTable &nodes,
                        const std::initializer_list<Point2D> &points)
{
    IDCollection nodeIDs;
    nodeIDs.reserve(points.size());

    NodePtr firstNode = nullptr;
    NodePtr prevNode = nullptr;

    for (const Point2D &vertex : points)
    {
        NodePtr currentNode = &nodes.addNode(vertex);
        nodeIDs.push_back(currentNode->getID());

        if (firstNode == nullptr)
        {
            firstNode = currentNode;
        }
        else
        {
            // Create an edge joining the nodes.
            edges.addEdge(nodes, prevNode->getID(), currentNode->getID());
        }

        // Move on to the next node.
        prevNode = currentNode;
    }

    // Close the ring.
    edges.addEdge(nodes, prevNode->getID(), firstNode->getID());

    return nodeIDs;
}


void addGlyph(NodeTable &nodes, EdgeTable &edges,
              const IndexRange *figures, size_t figureCount,
              const PrimVertex *vertices)
{
    IDCollection nodeIDs;

    for (size_t f = 0; f < figureCount; ++f)
    {
        const auto &figure = figures[f];
        uint32_t last = figure.second - 1;

        for (uint32_t i = 0; i < figure.second; ++i)
        {
            const auto &start = vertices[figure.first + ((i == 0) ? last : i - 1)];
            const auto &end = vertices[figure.first + i];
            ID startNodeID = nodes.addNode(Point2D(start.first, start.second)).getID();
            ID endNodeID = nodes.addNode(Point2D(end.first, end.second)).getID();

            // Prevent us from trying to create an edge where the
            // nodes were snapped together.
            if (startNodeID != endNodeID)
                edges.addEdge(nodes, startNodeID, endNodeID);
        }
    }
}

//! @brief Ensure a set of numeric identifiers contains no duplicate values.
//! @param[in] indices The collection of identifiers to check.
//! @returns A google test result with description.
::testing::AssertionResult indicesUnique(const IDCollection &indices)
{
    if (indices.size() > 1)
    {
        IDCollection sorted(indices);
        IDCollection duplicates;
        duplicates.reserve(sorted.size());

        std::sort(sorted.begin(), sorted.end());
        ID prev = sorted.front();

        for (auto pos = sorted.begin() + 1; pos != sorted.end(); ++pos)
        {
            if (*pos == prev)
            {
                duplicates.push_back(*pos);
            }

            prev = *pos;
        }

        if (duplicates.empty() == false)
        {
            auto last = std::unique(duplicates.begin(), duplicates.end());
            duplicates.erase(last, duplicates.end());

            if (duplicates.size() == 1)
            {
                return ::testing::AssertionFailure() <<
                    "A duplicate was found: #" << duplicates.front();
            }
            else
            {
                ::testing::Message failureMessage("Duplicates were found: { #");

                failureMessage << duplicates.front();

                for (auto pos = duplicates.begin() + 1; pos != duplicates.end(); ++pos)
                {
                    failureMessage << ", #" << *pos;
                }

                failureMessage << " }";
                return ::testing::AssertionFailure(failureMessage);
            }

        }
    }

    return ::testing::AssertionSuccess();
}

//! @brief Determines if a set of vertices matches a fixed set.
//! @param[in] ringVertices The set of vertices defining the ring being tested.
//! @param[in] expectedIDs The set of vertices expected to define the ring.
::testing::AssertionResult ringDefinition(const IDCollection &ringVertices,
                                          std::initializer_list<ID> &expectedIDs)
{
    if (ringVertices.size() != expectedIDs.size())
    {
        return ::testing::AssertionFailure() << "The ring (defined with " <<
            ringVertices.size() << " vertices) didn't match the expectation of " <<
            expectedIDs.size() << " vertices.";
    }

    if (!ringVertices.empty())
    {
        if (ringVertices.front() == *expectedIDs.begin())
        {
            // No shuffling required.
            if (std::equal(ringVertices.begin(), ringVertices.end(),
                           expectedIDs.begin()) == false)
            {
                return ::testing::AssertionFailure() <<
                    "The sequence of vertices did not match the expected sequence.";
            }
        }
        else
        {
            // Find the first matching vertex in the ring.
            auto firstPos = std::find(ringVertices.begin(), ringVertices.end(),
                                      *expectedIDs.begin());

            if (firstPos == ringVertices.end())
            {
                return ::testing::AssertionFailure() <<
                    "The first vertex in the expected sequence was not found.";

            }

            // Create a new collection where the expected first vertex appears
            // at the beginning of the collection.
            IDCollection shuffled;
            shuffled.reserve(ringVertices.size());

            std::copy(firstPos, ringVertices.end(), std::back_inserter(shuffled));
            std::copy(ringVertices.begin(), firstPos, std::back_inserter(shuffled));

            if (std::equal(shuffled.begin(), shuffled.end(),
                           expectedIDs.begin()) == false)
            {
                return ::testing::AssertionFailure() <<
                    "The sequence of vertices did not match the expected sequence.";
            }
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult verifyRing(const EdgeTable &edges, const Ring &ring)
{
    HalfEdgeCPtr startEdge;

    if (ring.getFirstEdge() == nullptr)
    {
        return ::testing::AssertionFailure() << "Initial ring edge is invalid.";
    }
    else if (edges.tryFindHalfEdgeByID(ring.getFirstEdge()->getID(), startEdge) == false)
    {
        return ::testing::AssertionFailure() << "Unable to obtain first edge on ring.";
    }
    else if (ring.getFirstEdge() != startEdge)
    {
        return ::testing::AssertionFailure() << "First edge on ring does not match edge table entry.";
    }

    HalfEdgeCPtr currentEdge = startEdge;
    uint32_t edgeCount = 0;

    // Perform forward iteration.
    do
    {
        currentEdge = currentEdge->getNextEdge();
        ++edgeCount;
    }
    while ((currentEdge != nullptr) && (currentEdge != startEdge));

    if (currentEdge == nullptr)
    {
        return ::testing::AssertionFailure() << "Not all ring edges are connected.";
    }
    else if (edgeCount != ring.getNodeCount())
    {
        return ::testing::AssertionFailure() << "A forward traversal of a ring had " <<
            edgeCount << " edges when it reported " << ring.getNodeCount();
    }

    // Attempt a reverse iteration.
    currentEdge = startEdge;
    edgeCount = 0;

    // Perform forward iteration.
    do
    {
        currentEdge = currentEdge->getPreviousEdge();
        ++edgeCount;
    }
    while ((currentEdge != nullptr) && (currentEdge != startEdge));

    if (currentEdge == nullptr)
    {
        return ::testing::AssertionFailure() << "Not all reverse edges are connected.";
    }
    else if (edgeCount != ring.getNodeCount())
    {
        return ::testing::AssertionFailure() << "A reverse traversal of a ring had " <<
            edgeCount << " edges when it reported " << ring.getNodeCount();
    }

    return ::testing::AssertionSuccess();
}

void dumpNodes(const NodeTable &nodes)
{
    puts("Node Summary:");

    for (auto iter = nodes.beginByID(), end = nodes.endByID();
         iter != end; ++iter)
    {
        printf("%u, %g, %g\n", iter->first,
               iter->second->getRealPosition().getX(),
               iter->second->getRealPosition().getY());
    }
}

void dumpEdges(const EdgeTable &edges)
{
    ID idSeed = 0;
    uint32_t edgesVisited = 0;

    puts("Edge Summary:");

    for (; edgesVisited < edges.getCount(); ++edgesVisited)
    {
        EdgeCPtr edge;

        while (edges.tryFindEdgeByID(idSeed, edge) == false)
        {
            ++idSeed;
        }

        printf("Edge %.2u: #%.2u -> #%.2u\n", edge->getID(),
               edge->getFirstNodeID(), edge->getSecondNodeID());

        ++idSeed;
    }

    putchar('\n');
}

void dumpRingNodes(const Ring &ring)
{
    HalfEdgeCPtr currentEdge = ring.getFirstEdge();

    printf("Ring #%u nodes:\n", ring.getID());

    do
    {
        if (currentEdge == ring.getFirstEdge())
        {
            printf("[%u]", currentEdge->getStartNodeID());
        }
        else
        {
            printf("->[%u]", currentEdge->getStartNodeID());
        }

        // Move on to next edge.
        currentEdge = currentEdge->getNextEdge();
    }
    while (currentEdge != ring.getFirstEdge());

    puts("\n\n");
}

void dumpRingGeometry(const Ring &ring)
{
    HalfEdgeCPtr currentEdge = ring.getFirstEdge();

    printf("Ring #%u nodes:\n", ring.getID());

    do
    {
        auto node = currentEdge->getStartNode();

        printf("%u\t%g\t%g\n", node->getID(),
               node->getRealPosition().getX(),
               node->getRealPosition().getY());

        // Move on to next edge.
        currentEdge = currentEdge->getNextEdge();
    } while (currentEdge != ring.getFirstEdge());

    puts("\n\n");
}

void dumpFigures(const NodeTable &nodes, const PrimVertex *vertices,
                 const IndexRange *figures, size_t figureCount)
{
    for (size_t f = 0; f < figureCount; ++f)
    {
        printf("Figure #%zu\n", f);
        auto figure = figures[f];

        for (size_t i = 0; i < figure.second; ++i)
        {
            auto vertex = vertices[figure.first + i];
            NodeCPtr node = nullptr;

            if (nodes.tryFindNodeByPosition(Point2D(vertex.first, vertex.second), node))
            {
                printf("%u\t%g\t%g\n", node->getID(),
                       node->getRealPosition().getX(),
                       node->getRealPosition().getY());
            }
            else
            {
                printf("** Unknown vertex at (%g, %g)\n", vertex.first, vertex.second);
            }
        }

        putchar('\n');
    }
}

}}} // namespace Ag::Geom::DCEL
////////////////////////////////////////////////////////////////////////////////

