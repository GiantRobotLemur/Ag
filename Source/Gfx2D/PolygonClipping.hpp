//! @file Gfx2D/PolygonClipping.hpp
//! @brief Internal helpers for clipping triangle lists against convex
//! polygons (Sutherland-Hodgman).
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_POLYGON_CLIPPING_HPP__
#define __GFX_2D_POLYGON_CLIPPING_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry.hpp"

#include "Ag/Gfx2D/PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief Clips a triangulated polygon against a convex CCW clip polygon
//! and returns the resulting triangulation.
//!
//! Implements the Sutherland-Hodgman algorithm per triangle: each input
//! triangle is reduced against the four (or N) half-planes that bound the
//! clip polygon, and the resulting convex sub-polygon (0..N+3 vertices) is
//! fan-triangulated back into the output. Triangles fully inside the clip
//! are passed through unchanged; triangles fully outside are dropped.
//!
//! The clip polygon must be convex and given in counter-clockwise order in
//! the same coordinate space as the source polygon's vertices. Both inputs
//! and outputs use the same coordinate space.
//!
//! @param[in] source The polygon to clip. Only its vertex and triangle-index
//! data are used; outline indices are not preserved in the output.
//! @param[in] clipVertices The vertices of the convex clip polygon, in
//! counter-clockwise order, with at least 3 entries.
//! @return A new partitioned polygon containing the clipped triangles. The
//! result has empty outline indices (clipping invalidates the original
//! outline correspondence). The original bounds are preserved unchanged.
PartitionedPolygon clipPolygonAgainstConvex(const PartitionedPolygon &source,
                                            const Geom::Point2DCollectionView &clipVertices);

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
