//! @file Geometry/Test_DrawScene.cpp
//! @brief The definition of a class which renders a 2D scene to test geometry
//! algorithms.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Test_DrawScene.hpp"

using namespace Ag;
using namespace Ag::Geom;

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

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
// Scene Member Definitions
////////////////////////////////////////////////////////////////////////////////
void Scene::loadGeometry(const RawVertex *vertices, size_t vertexCount,
                         const IndexRange *indices, size_t indexCount)
{
    _rings.clear();
    _edges.clear();

    if (vertexCount < 1)
        return;

    // Calculate the total extents of the geometry.
    auto points = reinterpret_cast<const Point2D *>(vertices);
    _extents = Rect2D(points[0], points[0]);

    for (size_t i = 1; i < vertexCount; ++i)
    {
        _extents.combineTo(points[i]);
    }

    // Reset the nodes table now we know the extent of the contents.
    _nodes.reset(_extents, vertexCount);

    // Add all vertices.
    DCEL::IDCollection vertexIDs;
    vertexIDs.reserve(vertexCount);

    for (size_t i = 0; i < vertexCount; ++i)
    {
        DCEL::ID vertexID = _nodes.addNode(points[i]).getID();
        vertexIDs.push_back(vertexID);
    }

    // Add all edges.
    for (size_t i = 0; i < indexCount; ++i)
    {
        const auto &indexRange = indices[i];

        if (indexRange.second < 3)
            continue;

        auto lastIndex = indexRange.first + indexRange.second - 1;

        for (uint32_t j = 0; j < indexRange.second; ++j)
        {
            auto startIndex = (j == 0) ? lastIndex : (indexRange.first + j - 1);
            auto endIndex = indexRange.first + j;

            _edges.addEdge(_nodes, vertexIDs[startIndex], vertexIDs[endIndex]);
        }
    }

    // Create a system of rings and holes.
    _rings.build(_nodes, _edges, false);
}
////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

