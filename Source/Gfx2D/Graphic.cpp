//! @file Gfx2D/Graphic.cpp
//! @brief The definition of a set of classes representing the components of
//! a 2D scene graph.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Graphic.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"

#include "DecompositionContext.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
const std::string_view VectorGraphicName("VectorGraphic");

constexpr double DefaultDecompositionTolerance = 0.5;

DecompositionParams makeParams(const Geom::AffineTransform2D &transform)
{
    return DecompositionParams(transform, DefaultDecompositionTolerance);
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Graphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Computes world-space bounds with no parent transform.
Geom::Rect2D Graphic::calculateBounds() const
{
    return calculateBounds(Geom::AffineTransform2D());
}

//! @brief Tests a world-space point with no parent transform.
bool Graphic::hitTest(const Geom::Point2D &worldPoint) const
{
    return hitTest(worldPoint, Geom::AffineTransform2D());
}

//! @brief Decomposes this node (and any subtree) into a flat draw list.
GraphicDecomposition Graphic::decompose() const
{
    GraphicDecomposition out;
    DecompositionContext ctx;
    decomposeInto(out, Geom::AffineTransform2D(), 1.0,
                  GraphicDecomposition::NoClip, ctx);
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// VectorGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Gets the style used to fill the area encompassed by the graphic.
BrushSPtr VectorGraphic::getFill() const
{
    return _fill;
}

//! @brief Sets the style used to fill the area encompassed by the graphic.
//! @param[in] fillStyle The new fill style, nullptr for no fill.
void VectorGraphic::setFill(const BrushSPtr &fillStyle)
{
    verifyAccess(VectorGraphicName, "set fill");

    _fill = fillStyle;
}

//! @brief Gets the style used to render the outline of the graphic.
PenSPtr VectorGraphic::getStroke() const
{
    return _stroke;
}

//! @brief Sets the style used to render the outline of the graphic.
//! @param[in] lineStyle The new line style, nullptr if there is no outline.
void VectorGraphic::setStroke(const PenSPtr &lineStyle)
{
    verifyAccess(VectorGraphicName, "set stroke");

    _stroke = lineStyle;
}

//! @brief Freezes this node and any brushes/pens it owns so the resulting
//! tree is safe to traverse from a render thread.
void VectorGraphic::freeze()
{
    if (_fill)
    {
        _fill->freeze();
    }

    if (_stroke)
    {
        _stroke->freeze();
    }

    GraphicArtefact::freeze();
}

//! @brief Computes the world-space bounds of this primitive.
Geom::Rect2D VectorGraphic::calculateBounds(
    const Geom::AffineTransform2D &parentTransform) const
{
    Geom::Rect2D local = calculateLocalBounds();

    if (local.isEmpty())
    {
        return local;
    }

    // Inflate by half the stroke thickness when an outline is present so that
    // bounds-based hit testing and culling include the stroked edge.
    if (_stroke)
    {
        double half = _stroke->getThickness() * 0.5;

        if (half > 0.0)
        {
            local = Geom::Rect2D(local.getMinimumX() - half,
                                 local.getMinimumY() - half,
                                 local.getMaximumX() + half,
                                 local.getMaximumY() + half);
        }
    }

    // Project local-space bounds through the parent transform.
    Geom::Point2D corners[4] = {
        parentTransform * Geom::Point2D(local.getMinimumX(), local.getMinimumY()),
        parentTransform * Geom::Point2D(local.getMaximumX(), local.getMinimumY()),
        parentTransform * Geom::Point2D(local.getMaximumX(), local.getMaximumY()),
        parentTransform * Geom::Point2D(local.getMinimumX(), local.getMaximumY()),
    };
    return Geom::Rect2D(corners, 4);
}

//! @brief Tests whether a world-space point lies inside this primitive.
//! @details v1 implementation: bounds-prune only. Precise per-triangle
//! hit-testing against the decomposed fill polygon is a future refinement.
bool VectorGraphic::hitTest(const Geom::Point2D &worldPoint,
                            const Geom::AffineTransform2D &parentTransform) const
{
    return calculateBounds(parentTransform).contains(worldPoint);
}

//! @brief Decomposes this primitive into 0-2 materialised draw items
//! (fill + stroke) and appends them to @a out.
void VectorGraphic::decomposeInto(GraphicDecomposition &out,
                                  const Geom::AffineTransform2D &parentTransform,
                                  double parentOpacity,
                                  size_t parentClipId,
                                  DecompositionContext &ctx) const
{
    Geom::Rect2D localBounds = calculateLocalBounds();

    if (localBounds.isEmpty())
    {
        return;
    }

    // NOTE: The DCEL partition() pipeline (RingSystem::build / makeYMonotone /
    // triangulate) is incomplete in the underlying Geometry library — calling
    // it on a valid closed path triggers an assertion in DCEL_Triangulate, and
    // PreDecompositionStats has unrelated issues that prevent even
    // tryCalculateBounds() from returning correct results in some cases.
    // Until those land, decomposition emits bounds-only placeholder
    // PartitionedPolygons so the scene-graph pipeline (transforms, opacity,
    // clip ids, brush attachment, draw-list ordering) can be exercised
    // end-to-end. Replace each `bounds-only` construction below with a
    // ctx.reset/addFillToDecomposition/ctx.partition sequence once partition()
    // is reliable.

    // Fill: only emit if a brush is set and the path encloses an area.
    if (_fill && _fill->getType() != FillType::Empty)
    {
        BrushSPtr frozenBrush = std::static_pointer_cast<Brush>(
            _fill->createFrozenClone());

        out.appendShape(DecomposedShape(PartitionedPolygon(localBounds),
                                        parentTransform,
                                        std::move(frozenBrush),
                                        parentOpacity,
                                        parentClipId));
    }

    // Stroke: only emit if a pen with a non-zero thickness and a brush is set.
    if (_stroke && _stroke->getThickness() > 0.0 && _stroke->getFill() &&
        _stroke->getFill()->getType() != FillType::Empty)
    {
        double half = _stroke->getThickness() * 0.5;
        Geom::Rect2D strokeBounds(localBounds.getMinimumX() - half,
                                  localBounds.getMinimumY() - half,
                                  localBounds.getMaximumX() + half,
                                  localBounds.getMaximumY() + half);

        BrushSPtr frozenBrush = std::static_pointer_cast<Brush>(
            _stroke->getFill()->createFrozenClone());

        out.appendShape(DecomposedShape(PartitionedPolygon(strokeBounds),
                                        parentTransform,
                                        std::move(frozenBrush),
                                        parentOpacity,
                                        parentClipId));
    }

    // Suppress unused-parameter warning until partition() is wired in.
    (void)ctx;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
