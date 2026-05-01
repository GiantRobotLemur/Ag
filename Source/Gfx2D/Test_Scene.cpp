//! @file Gfx2D/Test_Scene.cpp
//! @brief Unit tests covering Scene::snapshot() — frozen deep-clone semantics.
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

#include "Ag/Core.hpp"

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/Scene.hpp"
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

} // anonymous namespace

TEST(Scene, RootIsCreatedByDefault)
{
    Scene scene;
    EXPECT_NE(nullptr, scene.root());
    EXPECT_TRUE(scene.root()->getChildren().empty());
}

TEST(Scene, SnapshotReturnsFrozenTree)
{
    Scene scene;
    scene.root()->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));

    auto snap = scene.snapshot();
    ASSERT_NE(nullptr, snap);
    EXPECT_TRUE(snap->isFrozen());

    ASSERT_EQ(1u, snap->getChildren().size());
    EXPECT_TRUE(snap->getChildren().front()->isFrozen());
}

TEST(Scene, SnapshotIsIndependentOfLiveTree)
{
    Scene scene;
    scene.root()->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));

    auto snap = scene.snapshot();
    ASSERT_EQ(1u, snap->getChildren().size());

    // Mutating the live tree must not perturb the snapshot.
    scene.root()->addChild(filledRect(Geom::Rect2D(20, 20, 30, 30)));
    EXPECT_EQ(2u, scene.root()->getChildren().size());
    EXPECT_EQ(1u, snap->getChildren().size());
}

TEST(Scene, SnapshotRejectsMutation)
{
    Scene scene;
    auto snap = scene.snapshot();

    EXPECT_THROW(snap->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10))),
                 Ag::Exception);
}

TEST(Scene, SnapshotIsDecomposable)
{
    Scene scene;
    scene.root()->addChild(filledRect(Geom::Rect2D(0, 0, 10, 10)));
    scene.root()->addChild(filledRect(Geom::Rect2D(20, 0, 30, 10)));

    auto snap = scene.snapshot();
    GraphicDecomposition out = snap->decompose();

    EXPECT_EQ(2u, out.getShapes().size());
    EXPECT_NEAR(0.0,  out.getWorldBounds().getMinimumX(), Tolerance);
    EXPECT_NEAR(30.0, out.getWorldBounds().getMaximumX(), Tolerance);
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
