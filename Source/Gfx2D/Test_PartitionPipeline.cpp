//! @file Gfx2D/Test_PartitionPipeline.cpp
//! @brief Unit tests covering the end-to-end DCEL partition pipeline driven
//! through DecompositionContext (reset / addFillToDecomposition / partition).
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

#include "Ag/Gfx2D/Path.hpp"
#include "Ag/Gfx2D/PartitionedPolygon.hpp"

#include "DecompositionContext.hpp"

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

// Build a Path containing a single closed figure traced through the supplied
// vertices.
Path makeClosedPolyPath(std::initializer_list<Geom::Point2D> vertices)
{
    PathBuilder builder;
    auto it = vertices.begin();
    auto end = vertices.end();
    if (it == end)
        return builder.createPath();

    builder.beginFigure(*it++);
    while (it != end)
    {
        builder.appendLine(*it++);
    }
    builder.closeFigure();

    return builder.createPath();
}

// Drive the full pipeline (simulate → reset → addFill → partition) for a path
// and return the resulting partitioned polygon.
PartitionedPolygon partitionPath(const Path &path)
{
    DecompositionParams params(0.5);
    DecompositionStatistics stats = path.simulateDecomposition(params);

    DecompositionContext ctx;
    ctx.reset(stats);
    path.addFillToDecomposition(ctx, params, false);

    return ctx.partition(false);
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Bounds bug regression
////////////////////////////////////////////////////////////////////////////////

TEST(PathBounds, OpenPolylineIncludesStartPoint)
{
    PathBuilder builder;
    builder.beginFigure(Geom::Point2D(3.0, 4.0));
    builder.appendLine(Geom::Point2D(7.0, 11.0));
    Path path = builder.createPath();

    Geom::Rect2D bounds;
    ASSERT_TRUE(path.tryCalculateBounds(DecompositionParams(0.5), bounds));

    EXPECT_NEAR(3.0,  bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(4.0,  bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(7.0,  bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(11.0, bounds.getMaximumY(), Tolerance);
}

TEST(PathBounds, ClosedTriangleAABB)
{
    Path path = makeClosedPolyPath({
        Geom::Point2D(0.0, 0.0),
        Geom::Point2D(10.0, 0.0),
        Geom::Point2D(5.0, 8.0)
    });

    Geom::Rect2D bounds;
    ASSERT_TRUE(path.tryCalculateBounds(DecompositionParams(0.5), bounds));

    EXPECT_NEAR(0.0,  bounds.getMinimumX(), Tolerance);
    EXPECT_NEAR(0.0,  bounds.getMinimumY(), Tolerance);
    EXPECT_NEAR(10.0, bounds.getMaximumX(), Tolerance);
    EXPECT_NEAR(8.0,  bounds.getMaximumY(), Tolerance);
}

////////////////////////////////////////////////////////////////////////////////
// Partition pipeline
////////////////////////////////////////////////////////////////////////////////

TEST(PartitionPipeline, TriangleProducesOneTriangle)
{
    Path path = makeClosedPolyPath({
        Geom::Point2D(0.0, 0.0),
        Geom::Point2D(10.0, 0.0),
        Geom::Point2D(5.0, 8.0)
    });

    PartitionedPolygon poly = partitionPath(path);

    EXPECT_EQ(3u, poly.getPoints().getCount());
    EXPECT_EQ(3u, poly.getTriangleIndices().getCount()); // 1 triangle * 3 indices
}

TEST(PartitionPipeline, AxisAlignedSquareProducesTwoTriangles)
{
    Path path = makeClosedPolyPath({
        Geom::Point2D(0.0, 0.0),
        Geom::Point2D(10.0, 0.0),
        Geom::Point2D(10.0, 10.0),
        Geom::Point2D(0.0, 10.0)
    });

    PartitionedPolygon poly = partitionPath(path);

    EXPECT_EQ(4u, poly.getPoints().getCount());
    EXPECT_EQ(6u, poly.getTriangleIndices().getCount()); // 2 triangles * 3 indices
}

TEST(PartitionPipeline, LShapeProducesFourTriangles)
{
    // L-shape with 6 vertices (one reflex). Any valid triangulation produces
    // 4 triangles (n - 2 = 4).
    Path path = makeClosedPolyPath({
        Geom::Point2D(0.0, 0.0),
        Geom::Point2D(10.0, 0.0),
        Geom::Point2D(10.0, 4.0),
        Geom::Point2D(4.0, 4.0),
        Geom::Point2D(4.0, 10.0),
        Geom::Point2D(0.0, 10.0)
    });

    PartitionedPolygon poly = partitionPath(path);

    EXPECT_EQ(6u, poly.getPoints().getCount());
    EXPECT_EQ(12u, poly.getTriangleIndices().getCount()); // 4 triangles
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
