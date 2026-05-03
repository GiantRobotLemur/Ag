//! @file Gfx2D/Test_PolygonClipping.cpp
//! @brief Unit tests covering Sutherland-Hodgman triangle-list clipping and
//! its end-to-end use through GraphicGroup-owned clip rectangles.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <array>

#include <gtest/gtest.h>

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/Brushes.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"
#include "Ag/Gfx2D/GraphicGroup.hpp"
#include "Ag/Gfx2D/PrimitiveGraphics.hpp"

#include "PolygonClipping.hpp"

namespace Ag {
namespace Gfx2D {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
constexpr double Tolerance = 1e-6;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
BrushSPtr makeRedBrush()
{
    return Brushes::Red;
}

//! @brief Builds a single-triangle PartitionedPolygon for clipping tests.
PartitionedPolygon makeTriangle(const Geom::Point2D &a,
                                const Geom::Point2D &b,
                                const Geom::Point2D &c)
{
    Geom::Point2DCollection vertices;
    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);

    Geom::DCEL::IDDeque triangles;
    triangles.push_back(0);
    triangles.push_back(1);
    triangles.push_back(2);

    Geom::DCEL::IDDeque outline;
    outline.push_back(0);
    outline.push_back(1);
    outline.push_back(2);
    outline.push_back(Geom::DCEL::EndIndex);

    Geom::Rect2D bounds(Geom::Point2D(std::min({a.getX(), b.getX(), c.getX()}),
                                      std::min({a.getY(), b.getY(), c.getY()})),
                        Geom::Point2D(std::max({a.getX(), b.getX(), c.getX()}),
                                      std::max({a.getY(), b.getY(), c.getY()})));

    return PartitionedPolygon(vertices, triangles, outline, bounds);
}

//! @brief A CCW unit square clip from (0,0) to (10,10).
std::array<Geom::Point2D, 4> unitSquareClip()
{
    return {
        Geom::Point2D(0,  0),
        Geom::Point2D(10, 0),
        Geom::Point2D(10, 10),
        Geom::Point2D(0,  10),
    };
}

//! @brief Sums signed area of a triangle list — useful to assert "got the
//! right amount of geometry" without pinning exact triangulation.
double signedAreaOfTriangles(const PartitionedPolygon &poly)
{
    const auto &points    = poly.getPoints();
    const auto &triangles = poly.getTriangleIndices();

    double total = 0.0;
    for (size_t t = 0; t + 2 < triangles.getCount(); t += 3)
    {
        const auto &a = points.getAt(triangles.getAt(t));
        const auto &b = points.getAt(triangles.getAt(t + 1));
        const auto &c = points.getAt(triangles.getAt(t + 2));

        total += 0.5 * ((b.getX() - a.getX()) * (c.getY() - a.getY()) -
                        (b.getY() - a.getY()) * (c.getX() - a.getX()));
    }

    return total;
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Low-level: clipPolygonAgainstConvex
////////////////////////////////////////////////////////////////////////////////
TEST(PolygonClipping, TriangleFullyInsideIsPreserved)
{
    PartitionedPolygon tri = makeTriangle(Geom::Point2D(2, 2),
                                          Geom::Point2D(8, 2),
                                          Geom::Point2D(5, 8));

    auto clip = unitSquareClip();
    PartitionedPolygon out = clipPolygonAgainstConvex(
        tri, Geom::Point2DCollectionView(clip.data(), clip.size()));

    EXPECT_EQ(3u, out.getPoints().getCount());
    EXPECT_EQ(3u, out.getTriangleIndices().getCount());

    // Area of the original triangle: base 6, height 6, => 18.
    EXPECT_NEAR(18.0, signedAreaOfTriangles(out), Tolerance);
}

TEST(PolygonClipping, TriangleFullyOutsideProducesEmpty)
{
    PartitionedPolygon tri = makeTriangle(Geom::Point2D(20, 20),
                                          Geom::Point2D(30, 20),
                                          Geom::Point2D(25, 30));

    auto clip = unitSquareClip();
    PartitionedPolygon out = clipPolygonAgainstConvex(
        tri, Geom::Point2DCollectionView(clip.data(), clip.size()));

    EXPECT_EQ(0u, out.getTriangleIndices().getCount());
}

TEST(PolygonClipping, TriangleStraddlingClipIsClipped)
{
    // Triangle covers (-5,5), (15,5), (5,15) — straddles all four sides of
    // the [0,10] square.
    PartitionedPolygon tri = makeTriangle(Geom::Point2D(-5, 5),
                                          Geom::Point2D(15, 5),
                                          Geom::Point2D(5, 15));

    auto clip = unitSquareClip();
    PartitionedPolygon out = clipPolygonAgainstConvex(
        tri, Geom::Point2DCollectionView(clip.data(), clip.size()));

    ASSERT_GT(out.getTriangleIndices().getCount(), 0u);

    // Every output vertex must lie inside the clip rectangle.
    for (size_t i = 0; i < out.getPoints().getCount(); ++i)
    {
        const auto &p = out.getPoints().getAt(i);
        EXPECT_GE(p.getX(),  0.0 - Tolerance);
        EXPECT_LE(p.getX(), 10.0 + Tolerance);
        EXPECT_GE(p.getY(),  0.0 - Tolerance);
        EXPECT_LE(p.getY(), 10.0 + Tolerance);
    }

    // Sanity: the clipped area must be positive and strictly less than the
    // input triangle's area (100).
    const double area = signedAreaOfTriangles(out);
    EXPECT_GT(area, 0.0);
    EXPECT_LT(area, 100.0);
}

////////////////////////////////////////////////////////////////////////////////
// End-to-end: GraphicGroup clip applied during decomposition
////////////////////////////////////////////////////////////////////////////////

namespace {

//! @brief Builds a clip Path consisting of the rectangle [(x0,y0)-(x1,y1)].
Path makeRectClip(double x0, double y0, double x1, double y1)
{
    PathBuilder pb;
    pb.beginFigure(Geom::Point2D(x0, y0));
    pb.appendLine(Geom::Point2D(x1, y0));
    pb.appendLine(Geom::Point2D(x1, y1));
    pb.appendLine(Geom::Point2D(x0, y1));
    pb.closeFigure();
    return pb.createPath();
}

//! @brief Computes the world-space axis-aligned bounding box of every output
//! vertex of every shape in @a decomp.
Geom::Rect2D worldBoundsOfShapes(const GraphicDecomposition &decomp)
{
    Geom::Rect2D bounds;
    bool seeded = false;

    for (const DecomposedShape &shape : decomp.getShapes())
    {
        const auto &points = shape.getGeometry().getPoints();
        const auto &t = shape.getWorldTransform();

        for (size_t i = 0; i < points.getCount(); ++i)
        {
            Geom::Point2D world = t * points.getAt(i);

            if (!seeded)
            {
                bounds = Geom::Rect2D(world, world);
                seeded = true;
            }
            else
            {
                bounds.combineTo(world);
            }
        }
    }

    return bounds;
}

} // anonymous namespace

TEST(GraphicClip, RectClipShrinksChildToClipBounds)
{
    auto group = std::make_shared<GraphicGroup>();
    group->setClip(makeRectClip(2.0, 2.0, 8.0, 8.0));

    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    child->setFill(makeRedBrush());
    group->addChild(child);

    GraphicDecomposition decomp = group->decompose();

    ASSERT_EQ(1u, decomp.getShapes().size());

    Geom::Rect2D bounds = worldBoundsOfShapes(decomp);
    EXPECT_NEAR(2.0, bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(2.0, bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(8.0, bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(8.0, bounds.getMaximumY(), Tolerance);
}

TEST(GraphicClip, ChildFullyOutsideClipIsDropped)
{
    auto group = std::make_shared<GraphicGroup>();
    group->setClip(makeRectClip(0.0, 0.0, 5.0, 5.0));

    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(20, 20, 30, 30));
    child->setFill(makeRedBrush());
    group->addChild(child);

    GraphicDecomposition decomp = group->decompose();

    EXPECT_EQ(0u, decomp.getShapes().size());
}

TEST(GraphicClip, ChildFullyInsideClipIsPreserved)
{
    auto group = std::make_shared<GraphicGroup>();
    group->setClip(makeRectClip(0.0, 0.0, 100.0, 100.0));

    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(10, 10, 20, 20));
    child->setFill(makeRedBrush());
    group->addChild(child);

    GraphicDecomposition decomp = group->decompose();

    ASSERT_EQ(1u, decomp.getShapes().size());

    Geom::Rect2D bounds = worldBoundsOfShapes(decomp);
    EXPECT_NEAR(10.0, bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(10.0, bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(20.0, bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(20.0, bounds.getMaximumY(), Tolerance);
}

TEST(GraphicClip, NestedClipsIntersect)
{
    // Outer clip [0..20], inner clip [5..15] (in outer's local space, which
    // is the same as world here). The child rectangle covers [-5..25].
    auto outer = std::make_shared<GraphicGroup>();
    outer->setClip(makeRectClip(0.0, 0.0, 20.0, 20.0));

    auto inner = std::make_shared<GraphicGroup>();
    inner->setClip(makeRectClip(5.0, 5.0, 15.0, 15.0));
    outer->addChild(inner);

    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(-5, -5, 25, 25));
    child->setFill(makeRedBrush());
    inner->addChild(child);

    GraphicDecomposition decomp = outer->decompose();

    ASSERT_EQ(1u, decomp.getShapes().size());

    // Result should be the intersection — the inner clip rect.
    Geom::Rect2D bounds = worldBoundsOfShapes(decomp);
    EXPECT_NEAR(5.0,  bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(5.0,  bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(15.0, bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(15.0, bounds.getMaximumY(), Tolerance);
}

TEST(GraphicClip, ClipRespectsGroupTranslation)
{
    // Group's transform translates the clip to world space [100..110].
    auto group = std::make_shared<GraphicGroup>();
    Geom::AffineTransform2D t;
    t.makeTranslation(100.0, 100.0);
    group->setTransform(t);
    group->setClip(makeRectClip(0.0, 0.0, 10.0, 10.0));

    // Child in group-local space — covers more than the clip.
    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(-5, -5, 20, 20));
    child->setFill(makeRedBrush());
    group->addChild(child);

    GraphicDecomposition decomp = group->decompose();

    ASSERT_EQ(1u, decomp.getShapes().size());

    Geom::Rect2D bounds = worldBoundsOfShapes(decomp);
    EXPECT_NEAR(100.0, bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(100.0, bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(110.0, bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(110.0, bounds.getMaximumY(), Tolerance);
}

TEST(GraphicClip, NoClipPassesThroughUnchanged)
{
    auto group = std::make_shared<GraphicGroup>();

    auto child = std::make_shared<RectangleGraphic>(Geom::Rect2D(0, 0, 10, 10));
    child->setFill(makeRedBrush());
    group->addChild(child);

    GraphicDecomposition decomp = group->decompose();

    ASSERT_EQ(1u, decomp.getShapes().size());

    // No clip — full 10x10 should be preserved (existing partition output).
    EXPECT_EQ(4u, decomp.getShapes().front().getGeometry().getPoints().getCount());
    EXPECT_EQ(6u, decomp.getShapes().front().getGeometry().getTriangleIndices().getCount());
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
