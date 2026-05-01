//! @file Gfx2D/Test_GraphicGroup.cpp
//! @brief Unit tests covering GraphicGroup transform / opacity / clip
//! propagation through the decomposition.
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
#include "Ag/Gfx2D/GraphicGroup.hpp"
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

RectangleGraphicSPtr filledRect(const Geom::Rect2D &r)
{
    auto rect = std::make_shared<RectangleGraphic>(r);
    rect->setFill(makeRedBrush());
    return rect;
}

Path makeRectClip(double x0, double y0, double x1, double y1)
{
    PathBuilder builder;
    builder.beginFigure(Geom::Point2D(x0, y0));
    builder.appendLine(Geom::Point2D(x1, y0));
    builder.appendLine(Geom::Point2D(x1, y1));
    builder.appendLine(Geom::Point2D(x0, y1));
    builder.closeFigure();
    return builder.createPath();
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GraphicGroup tests
////////////////////////////////////////////////////////////////////////////////

TEST(GraphicGroup, EmptyGroupHasNoOutput)
{
    auto group = std::make_shared<GraphicGroup>();
    GraphicDecomposition out = group->decompose();
    EXPECT_TRUE(out.isEmpty());
}

TEST(GraphicGroup, ChildrenAreEmittedInOrder)
{
    auto group = std::make_shared<GraphicGroup>();
    group->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));
    group->addChild(filledRect(Geom::Rect2D(20, 0, 30, 10)));
    group->addChild(filledRect(Geom::Rect2D(40, 0, 50, 10)));

    GraphicDecomposition out = group->decompose();
    EXPECT_EQ(3u, out.getShapes().size());

    // Paint order: first child should be at index 0, last child at the end.
    // Since the rectangles are at different x ranges, we can identify them
    // by inspecting each shape's local bounds (rect order matches add order).
    EXPECT_NEAR(0.0,  out.getShapes()[0].getGeometry().getOriginalBounds().getMinimumX(), Tolerance);
    EXPECT_NEAR(20.0, out.getShapes()[1].getGeometry().getOriginalBounds().getMinimumX(), Tolerance);
    EXPECT_NEAR(40.0, out.getShapes()[2].getGeometry().getOriginalBounds().getMinimumX(), Tolerance);
}

TEST(GraphicGroup, OpacityComposesMultiplicatively)
{
    auto inner = std::make_shared<GraphicGroup>();
    inner->setOpacity(0.5);
    inner->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));

    auto outer = std::make_shared<GraphicGroup>();
    outer->setOpacity(0.4);
    outer->addChild(inner);

    GraphicDecomposition out = outer->decompose();
    ASSERT_EQ(1u, out.getShapes().size());

    // 0.4 * 0.5 = 0.2
    EXPECT_NEAR(0.2, out.getShapes().front().getEffectiveOpacity(), Tolerance);
}

TEST(GraphicGroup, ZeroOpacitySuppressesOutput)
{
    auto group = std::make_shared<GraphicGroup>();
    group->setOpacity(0.0);
    group->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));

    GraphicDecomposition out = group->decompose();
    EXPECT_TRUE(out.isEmpty());
}

TEST(GraphicGroup, TransformComposesIntoShapeWorldTransform)
{
    auto group = std::make_shared<GraphicGroup>();
    Geom::AffineTransform2D translate;
    translate.makeTranslation(50.0, 70.0);
    group->setTransform(translate);

    group->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));

    GraphicDecomposition out = group->decompose();
    ASSERT_EQ(1u, out.getShapes().size());

    Geom::Point2D origin = out.getShapes().front().getWorldTransform() *
                           Geom::Point2D(0.0, 0.0);
    EXPECT_NEAR(50.0, origin.getX(), Tolerance);
    EXPECT_NEAR(70.0, origin.getY(), Tolerance);
}

TEST(GraphicGroup, ClipRegisteredAndPropagatedToChildren)
{
    auto group = std::make_shared<GraphicGroup>();
    group->setClip(makeRectClip(0, 0, 100, 100));
    group->addChild(filledRect(Geom::Rect2D(10, 10, 20, 20)));
    group->addChild(filledRect(Geom::Rect2D(30, 30, 40, 40)));

    GraphicDecomposition out = group->decompose();

    ASSERT_EQ(1u, out.getClips().size());
    ASSERT_EQ(2u, out.getShapes().size());

    // Both children should reference the same clip id.
    EXPECT_EQ(0u, out.getShapes()[0].getClipStackId());
    EXPECT_EQ(0u, out.getShapes()[1].getClipStackId());

    // The root clip has no parent.
    EXPECT_EQ(GraphicDecomposition::NoClip,
              out.getClips().front().getParentClipId());
}

TEST(GraphicGroup, NestedClipsChainViaParentId)
{
    auto inner = std::make_shared<GraphicGroup>();
    inner->setClip(makeRectClip(20, 20, 80, 80));
    inner->addChild(filledRect(Geom::Rect2D(30, 30, 40, 40)));

    auto outer = std::make_shared<GraphicGroup>();
    outer->setClip(makeRectClip(0, 0, 100, 100));
    outer->addChild(inner);

    GraphicDecomposition out = outer->decompose();

    ASSERT_EQ(2u, out.getClips().size());
    ASSERT_EQ(1u, out.getShapes().size());

    // Outer clip is the root, inner clip's parent is the outer.
    EXPECT_EQ(GraphicDecomposition::NoClip,
              out.getClips()[0].getParentClipId());
    EXPECT_EQ(0u, out.getClips()[1].getParentClipId());

    // The innermost shape should reference the inner clip (id 1).
    EXPECT_EQ(1u, out.getShapes().front().getClipStackId());
}

TEST(GraphicGroup, BoundsAggregateAcrossChildren)
{
    auto group = std::make_shared<GraphicGroup>();
    group->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));
    group->addChild(filledRect(Geom::Rect2D(50, 50, 60, 60)));

    Geom::Rect2D b = group->calculateBounds();
    EXPECT_NEAR(0.0,  b.getMinimumX(), Tolerance);
    EXPECT_NEAR(0.0,  b.getMinimumY(), Tolerance);
    EXPECT_NEAR(60.0, b.getMaximumX(), Tolerance);
    EXPECT_NEAR(60.0, b.getMaximumY(), Tolerance);
}

TEST(GraphicGroup, HitTestRecursesThroughChildren)
{
    auto group = std::make_shared<GraphicGroup>();
    group->addChild(filledRect(Geom::Rect2D(10, 10, 20, 20)));

    EXPECT_TRUE (group->hitTest(Geom::Point2D(15, 15)));
    EXPECT_FALSE(group->hitTest(Geom::Point2D(50, 50)));
}

TEST(GraphicGroup, HitTestHonoursTransform)
{
    auto group = std::make_shared<GraphicGroup>();
    Geom::AffineTransform2D translate;
    translate.makeTranslation(100.0, 0.0);
    group->setTransform(translate);
    group->addChild(filledRect(Geom::Rect2D(10, 10, 20, 20)));

    // After the +100 X translation the shape sits at world [110..120].
    EXPECT_FALSE(group->hitTest(Geom::Point2D(15, 15)));
    EXPECT_TRUE (group->hitTest(Geom::Point2D(115, 15)));
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
