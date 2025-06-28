//! @file Ag/Geometry/Test_DCEL_Tools.hpp
//! @brief The declaration of tools shared between various DCEL unit tests.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2024
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_TEST_DCEL_TOOLS_HPP__
#define __AG_GEOMETRY_TEST_DCEL_TOOLS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry/DCEL.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Geom {
namespace DCEL {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Describes the indices of a rectangle added to a Doubly-Connected
//! Edge List.
struct RectIndices
{
    ID TL;
    ID TR;
    ID BL;
    ID BR;

    RectIndices();

    IDCollection toCollection() const;
};

using IndexRange = std::pair<uint32_t, uint32_t>;
using PrimVertex = std::pair<double, double>;

struct GlyphInfo
{
    Rect2D Range;
    size_t VertexCount;
    size_t EdgeCount;

    GlyphInfo();
    GlyphInfo(const IndexRange *figures, size_t figureCount,
              const PrimVertex *vertices);

    GlyphInfo &operator+=(const GlyphInfo &rhs);
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
RectIndices addRect(NodeTable &table, double x, double y,
                    double width, double height);
RectIndices addRect(EdgeTable &edges, NodeTable &nodes, double x, double y,
                    double width, double height);

IDCollection addPolygon(EdgeTable &edges, NodeTable &nodes,
                        const std::initializer_list<Point2D> &points);

void addGlyph(NodeTable &nodes, EdgeTable &edges,
              const IndexRange *figures, size_t figureCount,
              const PrimVertex *vertices);

::testing::AssertionResult indicesUnique(const IDCollection &indices);

::testing::AssertionResult ringDefinition(const IDCollection &ringVertices,
                                          std::initializer_list<ID> &expectedIDs);

::testing::AssertionResult verifyRing(const EdgeTable &edges, const Ring &ring);

void dumpNodes(const NodeTable &nodes);
void dumpEdges(const EdgeTable &edges);
void dumpRingNodes(const Ring &ring);
void dumpRingGeometry(const Ring &ring);
void dumpFigures(const NodeTable &nodes, const PrimVertex *vertices,
                 const IndexRange *figures, size_t figureCount);

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}}} // namespace Ag::Geom::DCEL

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
