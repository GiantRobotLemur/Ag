//! @file Gfx2D/PartitionedPolygon.cpp
//! @brief The definition of a polygon which has been partitioned into a set
//! of triangles ready for rendering by a driver.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// PartitionedPolygon Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which is a set of triangles ready to be rendered
//! which represent the decomposition of a graphic path.
//! @param[in] decomposition An object containing the vertices and edges of the
//! polygons already partitioned and ready to be triangulated.
//! @param[in] triangleIndices The set of indices of points defining the
//! triangles required to fill the shape.
//! @param[in] outlineIndices The set of indices defining the outline of the
//! shape and any holes.
//! @param[in] originalBounds The bounds of the original Path geometry, before
//! any clipping took place.
PartitionedPolygon::PartitionedPolygon(const Geom::Point2DCollection &vertices,
                                       const Geom::DCEL::IDDeque &triangleIndices,
                                       const Geom::DCEL::IDDeque &outlineIndices,
                                       const Geom::Rect2D &originalBounds) :
    _originalBounds(originalBounds)
{
    InlineAllocator allocator;
    auto pointsField = allocator.allocateArray<Geom::Point2D>(vertices.size());
    auto trianglesField = allocator.allocateArray<Geom::DCEL::ID>(triangleIndices.size());
    auto outlinesField = allocator.allocateArray<Geom::DCEL::ID>(outlineIndices.size());

    _data.resize(allocator.getSize());
    InlineInitialiser initialiser(_data.data(), _data.size());

    _points =
        initialiser.initialiseArray<Geom::Point2D>(pointsField, vertices);

    _triangleIndices =
        initialiser.initialiseArray<Geom::DCEL::ID>(trianglesField, triangleIndices);

    _outlineIndices =
        initialiser.initialiseArray<Geom::DCEL::ID>(outlinesField, outlineIndices);
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

