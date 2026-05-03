//! @file Gfx2D/Test_GpuDrawList.cpp
//! @brief Unit tests covering the packaging of a GraphicDecomposition into a
//! GpuDrawList: per-vertex colour evaluation, instance ranges, the
//! NeedsAlphaBlend flag, and the linear gradient projection.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <gtest/gtest.h>

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/GpuDrawList.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"
#include "Ag/Gfx2D/PrimitiveGraphics.hpp"

namespace Ag {
namespace Gfx2D {

namespace {

constexpr float Tolerance = 1e-4f;

BrushSPtr makeRedBrush()
{
    return std::make_shared<SolidColourBrush>(Colour(1.0f, 0.0f, 0.0f, 1.0f));
}

BrushSPtr makeTranslucentBrush()
{
    return std::make_shared<SolidColourBrush>(Colour(0.0f, 1.0f, 0.0f, 0.5f));
}

BrushSPtr makeRedToBlueGradient()
{
    return std::make_shared<LinearGradientBrush>(Colour(1.0f, 0.0f, 0.0f, 1.0f),
                                                 Colour(0.0f, 0.0f, 1.0f, 1.0f),
                                                 Geom::Point2D(0.0, 0.0),
                                                 Geom::Point2D(10.0, 0.0));
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Empty input
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, EmptyDecompositionProducesEmptyList)
{
    GraphicDecomposition decomp;
    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(0u, list.getVertices().size());
    EXPECT_EQ(0u, list.getIndices().size());
    EXPECT_EQ(0u, list.getInstances().size());
    EXPECT_FALSE(list.anyAlphaBlend());
}

////////////////////////////////////////////////////////////////////////////////
// Solid brush — per-vertex colour is the brush's fill colour everywhere
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, SolidFillProducesUniformVertexColour)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeRedBrush());

    GraphicDecomposition decomp = rect->decompose();
    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(1u, list.getInstances().size());
    EXPECT_EQ(4u, list.getVertices().size());
    EXPECT_EQ(6u, list.getIndices().size());

    for (const GpuVertex &v : list.getVertices())
    {
        EXPECT_NEAR(1.0f, v.colour.getRed(),   Tolerance);
        EXPECT_NEAR(0.0f, v.colour.getGreen(), Tolerance);
        EXPECT_NEAR(0.0f, v.colour.getBlue(),  Tolerance);
        EXPECT_NEAR(1.0f, v.colour.getAlpha(), Tolerance);
    }

    const GpuInstance &inst = list.getInstances().front();
    EXPECT_EQ(0u, inst.firstIndex);
    EXPECT_EQ(6u, inst.indexCount);
    EXPECT_EQ(0u, inst.baseVertex);
    EXPECT_NEAR(1.0f, inst.opacity, Tolerance);
    EXPECT_EQ(0u, inst.flags);          // opaque red, no blend needed
    EXPECT_FALSE(list.anyAlphaBlend());
}

////////////////////////////////////////////////////////////////////////////////
// NeedsAlphaBlend flag
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, TranslucentBrushSetsAlphaBlendFlag)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeTranslucentBrush());

    GraphicDecomposition decomp = rect->decompose();
    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(1u, list.getInstances().size());
    EXPECT_TRUE((list.getInstances().front().flags & GpuInstanceFlag::NeedsAlphaBlend) != 0u);
    EXPECT_TRUE(list.anyAlphaBlend());
}

////////////////////////////////////////////////////////////////////////////////
// Two shapes — instance ranges chain correctly through the shared buffers
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, TwoShapesProduceContiguousRanges)
{
    auto a = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    a->setFill(makeRedBrush());
    auto b = std::make_shared<RectangleGraphic>(Geom::Rect2D(20, 0, 30, 10));
    b->setFill(makeRedBrush());

    GraphicDecomposition decomp;
    DecompositionContext ctx;
    a->decomposeInto(decomp, Geom::AffineTransform2D(), 1.0,
                     GraphicDecomposition::NoClip, ctx);
    b->decomposeInto(decomp, Geom::AffineTransform2D(), 1.0,
                     GraphicDecomposition::NoClip, ctx);

    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(2u, list.getInstances().size());

    const GpuInstance &i0 = list.getInstances()[0];
    const GpuInstance &i1 = list.getInstances()[1];

    EXPECT_EQ(0u, i0.baseVertex);
    EXPECT_EQ(0u, i0.firstIndex);

    EXPECT_EQ(i0.baseVertex + static_cast<uint32_t>(decomp.getShapes()[0]
                                                       .getGeometry()
                                                       .getPoints().getCount()),
              i1.baseVertex);
    EXPECT_EQ(i0.firstIndex + i0.indexCount, i1.firstIndex);

    // Total buffer sizes match aggregated geometry.
    EXPECT_EQ(static_cast<size_t>(i1.baseVertex + decomp.getShapes()[1]
                                                     .getGeometry()
                                                     .getPoints().getCount()),
              list.getVertices().size());
    EXPECT_EQ(static_cast<size_t>(i1.firstIndex + i1.indexCount),
              list.getIndices().size());
}

////////////////////////////////////////////////////////////////////////////////
// Linear gradient — vertex colours interpolate along the gradient axis
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, LinearGradientInterpolatesAlongAxis)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeRedToBlueGradient());

    GraphicDecomposition decomp = rect->decompose();
    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(1u, list.getInstances().size());
    ASSERT_GE(list.getVertices().size(), 4u);

    // The rectangle has corners at (0,0), (10,0), (10,10), (0,10) —
    // gradient axis is x. Every vertex with x==0 must be the start colour
    // (red, alpha 1) and every vertex with x==10 must be the end colour
    // (blue, alpha 1), regardless of y.
    bool sawLeft = false;
    bool sawRight = false;

    for (const GpuVertex &v : list.getVertices())
    {
        if (v.position.getX() == 0.0)
        {
            EXPECT_NEAR(1.0f, v.colour.getRed(),   Tolerance);
            EXPECT_NEAR(0.0f, v.colour.getBlue(),  Tolerance);
            sawLeft = true;
        }
        else if (v.position.getX() == 10.0)
        {
            EXPECT_NEAR(0.0f, v.colour.getRed(),   Tolerance);
            EXPECT_NEAR(1.0f, v.colour.getBlue(),  Tolerance);
            sawRight = true;
        }
    }

    EXPECT_TRUE(sawLeft);
    EXPECT_TRUE(sawRight);
}

////////////////////////////////////////////////////////////////////////////////
// Inherited opacity below 1.0 must set NeedsAlphaBlend even with an opaque brush
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, GroupOpacitySetsAlphaBlendFlag)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeRedBrush());

    GraphicDecomposition decomp;
    DecompositionContext ctx;
    rect->decomposeInto(decomp, Geom::AffineTransform2D(), 0.5,
                        GraphicDecomposition::NoClip, ctx);

    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(1u, list.getInstances().size());
    EXPECT_NEAR(0.5f, list.getInstances().front().opacity, Tolerance);
    EXPECT_TRUE((list.getInstances().front().flags & GpuInstanceFlag::NeedsAlphaBlend) != 0u);
    EXPECT_TRUE(list.anyAlphaBlend());
}

////////////////////////////////////////////////////////////////////////////////
// World transform passes through into the instance buffer
////////////////////////////////////////////////////////////////////////////////
TEST(GpuDrawList, WorldTransformIsPackedIntoInstance)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeRedBrush());

    Geom::AffineTransform2D world;
    world.makeTranslation(100.0, 200.0);

    GraphicDecomposition decomp;
    DecompositionContext ctx;
    rect->decomposeInto(decomp, world, 1.0,
                        GraphicDecomposition::NoClip, ctx);

    GpuDrawList list = GpuDrawList::buildFrom(decomp);

    ASSERT_EQ(1u, list.getInstances().size());
    const GpuInstance &inst = list.getInstances().front();

    // First six values of AffineTransform2D::toArray() are 2x2 + translation.
    const double *expected = world.toArray();
    for (int i = 0; i < 6; ++i)
    {
        EXPECT_NEAR(static_cast<float>(expected[i]), inst.worldTransform[i], Tolerance);
    }
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
