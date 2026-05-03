//! @file Ag/Gfx2D/ClipStack.hpp
//! @brief The declaration of the active-clip stack threaded through scene
//! graph decomposition.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_CLIP_STACK_HPP__
#define __GFX_2D_CLIP_STACK_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>
#include <vector>

#include "Ag/Geometry.hpp"

#include "PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief One ancestor clip captured during scene graph traversal.
//!
//! @c localGeometry is the clip path flattened into a triangulated polygon
//! in the local space of the @c GraphicGroup that owns it. The geometry is
//! captured once at decomposition time and shared (by @c shared_ptr) across
//! the descendants that consume it; clipping is non-mutating.
//!
//! @c localToWorld takes points from that local space to world space; the
//! receiving shape composes its own world-to-local with this transform to
//! bring each clip triangle into shape-local space, where Sutherland-Hodgman
//! clipping is then applied per source-triangle / clip-triangle pair. The
//! union of those per-pair intersections is the shape's geometry inside this
//! clip; non-convex clip outlines are handled correctly because clip
//! triangles are themselves convex by construction.
struct ActiveClip
{
    std::shared_ptr<const PartitionedPolygon> localGeometry;
    Geom::AffineTransform2D                   localToWorld;
};

//! @brief A stack of active clips inherited from ancestor @c GraphicGroup
//! nodes during decomposition.
using ClipStack = std::vector<ActiveClip>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
