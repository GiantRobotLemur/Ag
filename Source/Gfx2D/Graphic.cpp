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
#include "Ag/Gfx2D/Path.hpp"

#include <array>

#include "DecompositionContext.hpp"
#include "PolygonClipping.hpp"

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

//! @brief Builds the four corners of an axis-aligned clip rectangle in
//! shape-local space, in counter-clockwise order suitable for
//! Sutherland-Hodgman clipping against shape-local triangles.
//!
//! @c clipLocalBounds lives in the clip-owner @c GraphicGroup's local space
//! and reaches world space via @c clipLocalToWorld; the receiving shape
//! reaches world space via @c shapeLocalToWorld. The composite
//! @c shapeLocalToWorld⁻¹ * clipLocalToWorld brings the four corners into
//! shape-local space.
//!
//! @return @c true if the corners are valid and were written; @c false if
//! the clip rectangle is empty or @c shapeLocalToWorld is singular.
bool buildClipQuadInShapeLocal(const Geom::Rect2D &clipLocalBounds,
                               const Geom::AffineTransform2D &clipLocalToWorld,
                               const Geom::AffineTransform2D &shapeLocalToWorld,
                               std::array<Geom::Point2D, 4> &outCorners)
{
    if (clipLocalBounds.isEmpty())
        return false;

    Geom::AffineTransform2D worldToShapeLocal;
    try
    {
        // TODO: Expose tryCalculateInverse() so that exceptions aren't part of
        // the non-exceptional control flow.

        worldToShapeLocal = shapeLocalToWorld.inverse();
    }
    catch (const DivisionByZeroException &)
    {
        return false;
    }

    const Geom::AffineTransform2D clipLocalToShapeLocal =
        worldToShapeLocal * clipLocalToWorld;

    // CCW corner order in clip-local space (positive Y is "down" in screen
    // conventions, but our signed-distance treats CCW with the +X-right /
    // +Y-down convention consistently — the shape-local triangulation
    // produced by the partitioner uses the same orientation, so they
    // agree).
    const Geom::Point2D corners[4] = {
        Geom::Point2D(clipLocalBounds.getMinimumX(), clipLocalBounds.getMinimumY()),
        Geom::Point2D(clipLocalBounds.getMaximumX(), clipLocalBounds.getMinimumY()),
        Geom::Point2D(clipLocalBounds.getMaximumX(), clipLocalBounds.getMaximumY()),
        Geom::Point2D(clipLocalBounds.getMinimumX(), clipLocalBounds.getMaximumY()),
    };

    for (int i = 0; i < 4; ++i)
        outCorners[i] = clipLocalToShapeLocal * corners[i];

    return true;
}

//! @brief Applies every clip in @a activeClips to @a poly (in shape-local
//! space). Returns the clipped polygon — possibly empty if all geometry was
//! clipped away.
PartitionedPolygon applyActiveClips(PartitionedPolygon poly,
                                    const ClipStack &activeClips,
                                    const Geom::AffineTransform2D &shapeLocalToWorld)
{
    for (const ActiveClip &clip : activeClips)
    {
        if (poly.getTriangleIndices().getCount() == 0)
            break;

        std::array<Geom::Point2D, 4> corners;

        if (!buildClipQuadInShapeLocal(clip.bounds, clip.localToWorld,
                                       shapeLocalToWorld, corners))
            continue;

        // The corner order above is CCW only when the composite transform's
        // determinant is positive; if it's negative (mirrored), we need to
        // reverse to keep "left of edge" == "inside".
        Geom::Point2DCollectionView clipView(corners.data(), corners.size());

        // Detect orientation by signed area; reverse if needed.
        std::array<Geom::Point2D, 4> reversed;
        const double signedArea =
            (corners[1].getX() - corners[0].getX()) *
                (corners[2].getY() - corners[0].getY()) -
            (corners[1].getY() - corners[0].getY()) *
                (corners[2].getX() - corners[0].getX());

        if (signedArea < 0.0)
        {
            for (int i = 0; i < 4; ++i)
                reversed[i] = corners[3 - i];
            clipView = Geom::Point2DCollectionView(reversed.data(), reversed.size());
        }

        poly = clipPolygonAgainstConvex(poly, clipView);
    }

    return poly;
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
    ClipStack activeClips;
    decomposeInto(out, Geom::AffineTransform2D(), 1.0,
                  GraphicDecomposition::NoClip, activeClips, ctx);
    return out;
}

//! @brief Backwards-compatible overload — calls the virtual with an empty
//! clip stack.
void Graphic::decomposeInto(GraphicDecomposition &out,
                            const Geom::AffineTransform2D &parentTransform,
                            double parentOpacity,
                            size_t parentClipId,
                            DecompositionContext &ctx) const
{
    ClipStack activeClips;
    decomposeInto(out, parentTransform, parentOpacity, parentClipId,
                  activeClips, ctx);
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
    makeFrozen(_fill);
    makeFrozen(_stroke);

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
                                  const ClipStack &activeClips,
                                  DecompositionContext &ctx) const
{
    Geom::Rect2D localBounds = calculateLocalBounds();

    if (localBounds.isEmpty())
    {
        return;
    }

    const bool wantsFill = _fill && (_fill->getType() != FillType::Empty);
    const bool wantsStroke = _stroke && (_stroke->getThickness() > 0.0) &&
                             _stroke->getFill() &&
                             (_stroke->getFill()->getType() != FillType::Empty);

    if (!wantsFill && !wantsStroke)
        return;

    Path path = lowerToPath();

    if (path.isBound() == false)
        return;

    DecompositionParams params(DefaultDecompositionTolerance);

    // Fill: triangulate the closed regions of the path.
    if (wantsFill)
    {
        DecompositionStatistics stats = path.simulateDecomposition(params);

        if (stats.isEmpty() == false)
        {
            ctx.reset(stats);
            path.addFillToDecomposition(ctx, params, /* isClip = */ false);

            PartitionedPolygon poly = ctx.partition();

            poly = applyActiveClips(std::move(poly), activeClips, parentTransform);

            if (poly.getTriangleIndices().getCount() > 0)
            {
                BrushSPtr frozenBrush = std::static_pointer_cast<Brush>(
                    _fill->createFrozenClone());

                out.appendShape(DecomposedShape(std::move(poly),
                                                parentTransform,
                                                std::move(frozenBrush),
                                                parentOpacity,
                                                parentClipId));
            }
        }
    }

    // Stroke: expand the outline by the pen and triangulate the result.
    if (wantsStroke)
    {
        DecompositionStatistics stats = path.simulateDecomposition(params);

        if (stats.isEmpty() == false)
        {
            ctx.reset(stats);
            path.addOutlineToDecomposition(ctx, params, _stroke);

            PartitionedPolygon poly = ctx.partition();

            poly = applyActiveClips(std::move(poly), activeClips, parentTransform);

            if (poly.getTriangleIndices().getCount() > 0)
            {
                BrushSPtr frozenBrush = std::static_pointer_cast<Brush>(
                    _stroke->getFill()->createFrozenClone());

                out.appendShape(DecomposedShape(std::move(poly),
                                                parentTransform,
                                                std::move(frozenBrush),
                                                parentOpacity,
                                                parentClipId));
            }
        }
    }
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
