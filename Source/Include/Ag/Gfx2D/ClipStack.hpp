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
#include <vector>

#include "Ag/Geometry.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief One ancestor clip captured during scene graph traversal.
//!
//! @c bounds is the clip rectangle in the local space of the @c GraphicGroup
//! that owns it. @c localToWorld takes points from that local space to world
//! space; the receiving shape composes its own world-to-local with this
//! transform to bring the four clip corners into shape-local space, where
//! triangle clipping is then applied.
//!
//! @note In v1 the clip is captured as the axis-aligned bounding rectangle
//! of the owning group's clip @c Path. This is exact for rectangular clips
//! and overly permissive for other clip shapes — a follow-up will replace
//! @c bounds with a flattened polyline so non-rectangular clips are handled
//! exactly. The plumbing in this header does not need to change for that
//! upgrade; only the field type and the consumer in the partitioner do.
struct ActiveClip
{
    Geom::Rect2D            bounds;
    Geom::AffineTransform2D localToWorld;
};

//! @brief A stack of active clips inherited from ancestor @c GraphicGroup
//! nodes during decomposition.
using ClipStack = std::vector<ActiveClip>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
