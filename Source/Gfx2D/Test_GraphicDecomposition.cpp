//! @file Gfx2D/Test_GraphicDecomposition.cpp
//! @brief Unit tests covering the decomposition of VectorGraphic primitives
//! into the GraphicDecomposition draw list.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7
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
#include "Ag/Gfx2D/Pen.hpp"
#include "Ag/Gfx2D/PrimitiveGraphics.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"

namespace Ag {
namespace Gfx2D {

namespace {

constexpr double Tolerance = 1e-3;

BrushSPtr makeRedBrush()
{
    return std::make_shared<SolidColourBrush>(Colour(1.0f, 0.0f, 0.0f, 1.0f));
}

BrushSPtr makeBlueBrush()
{
    return std::make_shared<SolidColourBrush>(Colour(0.0f, 0.0f, 1.0f, 1.0f));
}

PenSPtr makeBlackPen(double thickness)
{
    auto brush = std::make_shared<SolidColourBrush>(Colour(0.0f, 0.0f, 0.0f, 1.0f));
    return std::make_shared<Pen>(brush, thickness);
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// VectorGraphic decomposition
////////////////////////////////////////////////////////////////////////////////

TEST(GraphicDecomposition, EmptyShapeProducesNoOutput)
{
    auto rect = std::make_shared<RectangleGraphic>();
    GraphicDecomposition out = rect->decompose();

    EXPECT_TRUE(out.isEmpty());
    EXPECT_EQ(0u, out.getShapes().size());
    EXPECT_EQ(0u, out.getClips().size());
}

TEST(GraphicDecomposition, RectangleFillProducesOneShape)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(makeRedBrush());

    GraphicDecomposition out = rect->decompose();

    ASSERT_EQ(1u, out.getShapes().size());
    EXPECT_EQ(0u, out.getClips().size());

    const DecomposedShape &shape = out.getShapes().front();
    EXPECT_DOUBLE_EQ(1.0, shape.getEffectiveOpacity());
    EXPECT_EQ(GraphicDecomposition::NoClip, shape.getClipStackId());
    EXPECT_NE(nullptr, shape.getBrush());
    const Geom::Rect2D &b = shape.getGeometry().getOriginalBounds();
    EXPECT_NEAR(0.0,  b.getMinimumX(), Tolerance);
    EXPECT_NEAR(10.0, b.getMaximumX(), Tolerance);

    // The fill should now be triangulated, not a bounds-only placeholder.
    EXPECT_EQ(4u, shape.getGeometry().getPoints().getCount());
    EXPECT_EQ(6u, shape.getGeometry().getTriangleIndices().getCount());
}

TEST(GraphicDecomposition, FillAndStrokeProduceTwoShapes)
{
    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 20, 20));
    rect->setFill(makeRedBrush());
    rect->setStroke(makeBlackPen(2.0));

    GraphicDecomposition out = rect->decompose();

    EXPECT_EQ(2u, out.getShapes().size());
}

TEST(GraphicDecomposition, StrokeOnlyProducesOneShape)
{
    auto line = std::make_shared<LineGraphic>(Geom::Point2D(0, 0),
                                              Geom::Point2D(50, 0));
    line->setStroke(makeBlackPen(4.0));

    GraphicDecomposition out = line->decompose();

    ASSERT_EQ(1u, out.getShapes().size());
}

TEST(GraphicDecomposition, GeometryIsLocalSpace_TransformIsSideband)
{
    Geom::Rect2D rectBox(0, 0, 10, 10);
    auto rect = std::make_shared<RectangleGraphic>(rectBox);
    rect->setFill(makeRedBrush());

    Geom::AffineTransform2D worldTransform;
    worldTransform.makeTranslation(100.0, 200.0);

    GraphicDecomposition out;
    DecompositionContext ctx;
    rect->decomposeInto(out, worldTransform, 1.0,
                        GraphicDecomposition::NoClip, ctx);

    ASSERT_EQ(1u, out.getShapes().size());
    const DecomposedShape &shape = out.getShapes().front();

    // Geometry must be in local space — the AABB of vertices should match
    // the original rect, NOT a translated version of it.
    const Geom::Rect2D &localBounds = shape.getGeometry().getOriginalBounds();
    EXPECT_NEAR(0.0,  localBounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(0.0,  localBounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(10.0, localBounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(10.0, localBounds.getMaximumY(), Tolerance);

    // Side-band transform should match what we passed in.
    const Geom::AffineTransform2D &t = shape.getWorldTransform();
    Geom::Point2D origin = t * Geom::Point2D(0, 0);
    EXPECT_NEAR(100.0, origin.getX(), Tolerance);
    EXPECT_NEAR(200.0, origin.getY(), Tolerance);
}

TEST(GraphicDecomposition, WorldBoundsAggregateAcrossShapes)
{
    auto a = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    a->setFill(makeRedBrush());
    auto b = std::make_shared<RectangleGraphic>(Geom::Rect2D(50, 50, 60, 60));
    b->setFill(makeBlueBrush());

    GraphicDecomposition out;
    DecompositionContext ctx;
    a->decomposeInto(out, Geom::AffineTransform2D(), 1.0,
                     GraphicDecomposition::NoClip, ctx);
    b->decomposeInto(out, Geom::AffineTransform2D(), 1.0,
                     GraphicDecomposition::NoClip, ctx);

    const Geom::Rect2D &world = out.getWorldBounds();
    EXPECT_NEAR(0.0,  world.getMinimumX(), Tolerance);
    EXPECT_NEAR(0.0,  world.getMinimumY(), Tolerance);
    EXPECT_NEAR(60.0, world.getMaximumX(), Tolerance);
    EXPECT_NEAR(60.0, world.getMaximumY(), Tolerance);
}

TEST(GraphicDecomposition, BrushIsFrozenInOutput)
{
    auto brush = makeRedBrush();
    EXPECT_FALSE(brush->isFrozen());

    auto rect = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    rect->setFill(brush);

    GraphicDecomposition out = rect->decompose();
    ASSERT_EQ(1u, out.getShapes().size());

    EXPECT_TRUE(out.getShapes().front().getBrush()->isFrozen());
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
