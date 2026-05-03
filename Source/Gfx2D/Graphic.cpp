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

//! @brief Twice the signed area of a triangle. Positive when the triangle
//! is wound counter-clockwise; we use the sign to detect the orientation
//! that Sutherland-Hodgman expects ("left of edge" == "inside").
inline double signedAreaX2(const Geom::Point2D &a,
                           const Geom::Point2D &b,
                           const Geom::Point2D &c)
{
    return (b.getX() - a.getX()) * (c.getY() - a.getY()) -
           (b.getY() - a.getY()) * (c.getX() - a.getX());
}

//! @brief Appends every triangle in @a piece to the running accumulator,
//! re-basing its vertex indices into @a accVertices.
void appendClippedPiece(const PartitionedPolygon &piece,
                        Geom::Point2DCollection &accVertices,
                        Geom::DCEL::IDDeque &accTriangles)
{
    const auto &points    = piece.getPoints();
    const auto &triangles = piece.getTriangleIndices();

    if (triangles.getCount() == 0)
        return;

    const Geom::DCEL::ID base =
        static_cast<Geom::DCEL::ID>(accVertices.size());

    for (size_t i = 0; i < points.getCount(); ++i)
        accVertices.push_back(points.getAt(i));

    for (size_t i = 0; i < triangles.getCount(); ++i)
        accTriangles.push_back(base + triangles.getAt(i));
}

//! @brief Applies one clip to @a poly: clips it against every triangle in
//! the clip's triangulation and unions the results.
//!
//! Triangulating the clip outline gives a set of disjoint convex pieces;
//! the union of (input ∩ clip-triangle-i) over i equals (input ∩ clip),
//! which is correct even when the original clip outline is non-convex.
//! Each per-triangle intersection is computed by Sutherland-Hodgman.
PartitionedPolygon applyOneClip(PartitionedPolygon poly,
                                const ActiveClip &clip,
                                const Geom::AffineTransform2D &shapeLocalToWorld)
{
    if (!clip.localGeometry)
        return poly;

    const auto &clipPoints    = clip.localGeometry->getPoints();
    const auto &clipTriangles = clip.localGeometry->getTriangleIndices();

    if (clipPoints.getCount() == 0 || clipTriangles.getCount() < 3)
        return poly;

    Geom::AffineTransform2D worldToShapeLocal;

    if (shapeLocalToWorld.tryCalculateInverse(worldToShapeLocal) == false)
    {
        // Singular shape transform — leave the polygon unclipped. The
        // back-end can still cull on bounds.
        return poly;
    }

    const Geom::AffineTransform2D clipLocalToShapeLocal =
        worldToShapeLocal * clip.localToWorld;

    // Transform the clip's vertices into shape-local space once, then
    // walk each clip triangle.
    std::vector<Geom::Point2D> shapeLocalClipPoints;
    shapeLocalClipPoints.reserve(clipPoints.getCount());

    for (size_t i = 0; i < clipPoints.getCount(); ++i)
    {
        shapeLocalClipPoints.push_back(
            clipLocalToShapeLocal * clipPoints.getAt(i));
    }

    Geom::Point2DCollection accVertices;
    Geom::DCEL::IDDeque     accTriangles;
    Geom::DCEL::IDDeque     emptyOutline;

    accVertices.reserve(poly.getPoints().getCount());

    const size_t triCount = clipTriangles.getCount() / 3;

    std::array<Geom::Point2D, 3> tri;

    for (size_t t = 0; t < triCount; ++t)
    {
        tri[0] = shapeLocalClipPoints[clipTriangles.getAt(t * 3)];
        tri[1] = shapeLocalClipPoints[clipTriangles.getAt(t * 3 + 1)];
        tri[2] = shapeLocalClipPoints[clipTriangles.getAt(t * 3 + 2)];

        // Sutherland-Hodgman expects CCW; flip if the partitioner emitted
        // CW or if the composite transform mirrored orientation.
        if (signedAreaX2(tri[0], tri[1], tri[2]) < 0.0)
            std::swap(tri[1], tri[2]);

        Geom::Point2DCollectionView triView(tri.data(), tri.size());
        PartitionedPolygon piece = clipPolygonAgainstConvex(poly, triView);

        appendClippedPiece(piece, accVertices, accTriangles);
    }

    if (accTriangles.empty())
        return PartitionedPolygon(poly.getOriginalBounds());

    return PartitionedPolygon(accVertices, accTriangles, emptyOutline,
                              poly.getOriginalBounds());
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

        poly = applyOneClip(std::move(poly), clip, shapeLocalToWorld);
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
