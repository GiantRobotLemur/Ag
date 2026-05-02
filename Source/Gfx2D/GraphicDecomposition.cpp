//! @file Gfx2D/GraphicDecomposition.cpp
//! @brief The definition of an object representing a graphic which has been
//! de-composed ready for rendering by a graphic driver, probably GPU-based.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/GraphicDecomposition.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// DecomposedShape Member Definitions
////////////////////////////////////////////////////////////////////////////////
DecomposedShape::DecomposedShape(PartitionedPolygon geometry,
                                 const Geom::AffineTransform2D &worldTransform,
                                 BrushSPtr brush,
                                 double effectiveOpacity,
                                 size_t clipStackId) :
    _geometry(std::move(geometry)),
    _worldTransform(worldTransform),
    _brush(std::move(brush)),
    _effectiveOpacity(effectiveOpacity),
    _clipStackId(clipStackId)
{
}

////////////////////////////////////////////////////////////////////////////////
// ClipRegion Member Definitions
////////////////////////////////////////////////////////////////////////////////
ClipRegion::ClipRegion(PartitionedPolygon geometry,
                       const Geom::AffineTransform2D &worldTransform,
                       size_t parentClipId) :
    _geometry(std::move(geometry)),
    _worldTransform(worldTransform),
    _parentClipId(parentClipId)
{
}

////////////////////////////////////////////////////////////////////////////////
// GraphicDecomposition Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Appends a draw item to the decomposition and merges its world
//! bounds into the cumulative bounds.
void GraphicDecomposition::appendShape(DecomposedShape &&shape)
{
    // The shape's geometry is in local space; project its bounds through the
    // shape transform to compute its world-space contribution to bounds.
    const Geom::Rect2D &local = shape.getGeometry().getOriginalBounds();

    if (!local.isEmpty())
    {
        const Geom::AffineTransform2D &t = shape.getWorldTransform();

        Geom::Point2D corners[4] = {
            t * Geom::Point2D(local.getMinimumX(), local.getMinimumY()),
            t * Geom::Point2D(local.getMaximumX(), local.getMinimumY()),
            t * Geom::Point2D(local.getMaximumX(), local.getMaximumY()),
            t * Geom::Point2D(local.getMinimumX(), local.getMaximumY()),
        };
        Geom::Rect2D worldRect(corners, 4);
        mergeBounds(worldRect);
    }

    _shapes.push_back(std::move(shape));
}

//! @brief Appends a clip region and returns its id, suitable for passing as
//! @c parentClipId to descendant shapes or nested clips.
size_t GraphicDecomposition::appendClip(ClipRegion clip)
{
    size_t id = _clips.size();
    _clips.push_back(std::move(clip));
    return id;
}

//! @brief Merges the supplied rectangle into the cumulative world bounds.
void GraphicDecomposition::mergeBounds(const Geom::Rect2D &bounds)
{
    if (bounds.isEmpty())
    {
        return;
    }

    if (_hasBounds)
    {
        _worldBounds = _worldBounds.combine(bounds);
    }
    else
    {
        _worldBounds = bounds;
        _hasBounds = true;
    }
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
