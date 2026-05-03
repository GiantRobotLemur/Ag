//! @file Gfx2D/GpuDrawList.cpp
//! @brief The definition of the GPU-ready draw list packed from a
//! GraphicDecomposition.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/GpuDrawList.hpp"

#include <algorithm>
#include <cstring>

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"

namespace Ag {
namespace Gfx2D {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

//! @brief Evaluates a linear gradient brush at a point in the shape's local
//! space.
Colour evaluateLinearGradient(const LinearGradientBrush &brush,
                              const Geom::Point2D &localPosition)
{
    const Geom::Point2D &start = brush.getStartPosition();
    const Geom::Point2D delta = brush.getEndPosition() - start;
    const double lengthSq = delta.magnitudeSquared();

    double t = 0.0;

    if (lengthSq > 0.0)
    {
        const Geom::Point2D localDelta = localPosition - start;

        t = localDelta.dotProduct(delta) / lengthSq;
    }

    if (t <= 0.0)
        return brush.getStartColour();

    if (t >= 1.0)
        return brush.getEndColour();

    // Walk the (sorted-by-offset) interior stops, treating the start and end
    // colours as virtual stops at offsets 0.0 and 1.0.
    const auto &stops = brush.getGradientStops();

    double  loOffset = 0.0;
    Colour  loColour = brush.getStartColour();
    double  hiOffset = 1.0;
    Colour  hiColour = brush.getEndColour();

    for (const GradientStop &stop : stops)
    {
        if (stop.Offset <= t)
        {
            loOffset = stop.Offset;
            loColour = stop.Value;
        }
        else
        {
            hiOffset = stop.Offset;
            hiColour = stop.Value;
            break;
        }
    }

    const double span = hiOffset - loOffset;
    const float  alpha = (span > 0.0)
                            ? static_cast<float>((t - loOffset) / span)
                            : 0.0f;

    return loColour.lerp(hiColour, alpha);
}

//! @brief Evaluates an arbitrary brush at a point in shape-local space.
Colour evaluateBrushAt(const Brush *brush, const Geom::Point2D &localPosition)
{
    if (brush == nullptr)
        return Colour(0.0f, 0.0f, 0.0f, 0.0f);

    switch (brush->getType())
    {
    case FillType::Solid:
        return static_cast<const SolidColourBrush *>(brush)->getFill();

    case FillType::Linear:
        return evaluateLinearGradient(*static_cast<const LinearGradientBrush *>(brush),
                                      localPosition);

    case FillType::Empty:
    case FillType::Pattern:
    case FillType::Image:
    default:
        // Pattern/Image are not yet implemented; fall through to opaque
        // black so the geometry is at least visible during bring-up rather
        // than silently dropped.
        return Colour(0.0f, 0.0f, 0.0f);
    }
}

//! @brief Determines whether any vertex of a shape will require alpha
//! blending. For solid brushes the answer is the same at every vertex; for
//! linear gradients we conservatively check the start, end, and any
//! interior stop colours.
bool brushNeedsAlpha(const Brush *brush)
{
    if (brush == nullptr)
        return true;

    switch (brush->getType())
    {
    case FillType::Solid:
        return static_cast<const SolidColourBrush *>(brush)->getFill().getAlpha() < 1.0f;

    case FillType::Linear:
    {
        const auto &lg = *static_cast<const LinearGradientBrush *>(brush);

        if (lg.getStartColour().getAlpha() < 1.0f ||
            lg.getEndColour().getAlpha()   < 1.0f)
            return true;

        for (const GradientStop &stop : lg.getGradientStops())
        {
            if (stop.Value.getAlpha() < 1.0f)
                return true;
        }

        return false;
    }

    case FillType::Empty:
    case FillType::Pattern:
    case FillType::Image:
    default:
        return false;
    }
}

//! @brief Copies the first six values of an affine transform (2x2 matrix
//! plus translation) into a float array, downcasting from double.
void packTransform(const Geom::AffineTransform2D &transform, float (&out)[6])
{
    const double *src = transform.toArray();
    for (int i = 0; i < 6; ++i)
        out[i] = static_cast<float>(src[i]);
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GpuDrawList Member Definitions
////////////////////////////////////////////////////////////////////////////////

GpuDrawList GpuDrawList::buildFrom(const GraphicDecomposition &decomp)
{
    GpuDrawList result;

    const auto &shapes = decomp.getShapes();

    if (shapes.empty())
        return result;

    // Reserve up-front from aggregated vertex / index counts to avoid
    // reallocations inside the hot loop.
    size_t totalVertices = 0;
    size_t totalIndices  = 0;
    for (const DecomposedShape &shape : shapes)
    {
        totalVertices += shape.getGeometry().getPoints().getCount();
        totalIndices  += shape.getGeometry().getTriangleIndices().getCount();
    }

    result._vertices.reserve(totalVertices);
    result._indices.reserve(totalIndices);
    result._instances.reserve(shapes.size());

    for (const DecomposedShape &shape : shapes)
    {
        const PartitionedPolygon &geom = shape.getGeometry();
        const auto &points    = geom.getPoints();
        const auto &triangles = geom.getTriangleIndices();

        if (points.getCount() == 0 || triangles.getCount() == 0)
            continue;

        const Brush *brush = shape.getBrush().get();
        const double opacity = shape.getEffectiveOpacity();

        const uint32_t baseVertex = static_cast<uint32_t>(result._vertices.size());
        const uint32_t firstIndex = static_cast<uint32_t>(result._indices.size());

        // Append per-vertex {position, evaluated colour}.
        for (size_t i = 0; i < points.getCount(); ++i)
        {
            const Geom::Point2D &p = points.getAt(i);
            GpuVertex v;
            v.position = p;
            v.colour   = evaluateBrushAt(brush, p);
            result._vertices.push_back(v);
        }

        // Triangle indices are a flat list of triplets relative to this
        // shape's vertex range — pack them as-is into the shared buffer.
        // baseVertex on the instance shifts them at draw time.
        for (size_t i = 0; i < triangles.getCount(); ++i)
        {
            result._indices.push_back(static_cast<uint32_t>(triangles.getAt(i)));
        }

        const bool needsAlpha = brushNeedsAlpha(brush) || (opacity < 1.0);

        GpuInstance inst{};
        packTransform(shape.getWorldTransform(), inst.worldTransform);
        inst.opacity    = static_cast<float>(opacity);
        inst.flags      = needsAlpha ? GpuInstanceFlag::NeedsAlphaBlend : 0u;
        inst.firstIndex = firstIndex;
        inst.indexCount = static_cast<uint32_t>(triangles.getCount());
        inst.baseVertex = baseVertex;
        inst.reserved   = 0u;

        result._instances.push_back(inst);

        if (needsAlpha)
            result._anyAlphaBlend = true;
    }

    return result;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
