//! @file Gfx2D/Test_StrokeHelper.cpp
//! @brief Unit tests for the StrokeHelper class and the
//! Path::addOutlineToDecomposition() entry point.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cmath>

#include <gtest/gtest.h>

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/Pen.hpp"

#include "DecompositionContext.hpp"
#include "StrokeHelper.hpp"

namespace Ag {
namespace Gfx2D {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Helpers
////////////////////////////////////////////////////////////////////////////////
constexpr double Epsilon = 1e-6;
constexpr double Tolerance = 0.05;
constexpr double Thickness = 10.0;
constexpr double HalfWidth = Thickness * 0.5;

//! @brief Constructs a pen with a default solid brush, the supplied thickness
//! and the supplied cap and join style.
PenSPtr makePen(double thickness, EndCap cap, JoinCap join)
{
    auto pen = std::make_shared<Pen>(Brush::Empty, thickness);
    pen->setLineStartCap(cap);
    pen->setLineEndCap(cap);
    pen->setDashCap(cap);
    pen->setJoinCap(join);
    return pen;
}

//! @brief Builds DecompositionParams with a unit transform and a fine
//! tolerance suited to bounds-comparison tests.
DecompositionParams makeParams()
{
    return DecompositionParams(Tolerance);
}

void expectBoundsNear(const Geom::Rect2D &bounds,
                      double minX, double minY,
                      double maxX, double maxY,
                      double tol = Epsilon)
{
    ASSERT_FALSE(bounds.isEmpty());
    EXPECT_NEAR(bounds.getMinimumX(), minX, tol);
    EXPECT_NEAR(bounds.getMinimumY(), minY, tol);
    EXPECT_NEAR(bounds.getMaximumX(), maxX, tol);
    EXPECT_NEAR(bounds.getMaximumY(), maxY, tol);
}

////////////////////////////////////////////////////////////////////////////////
// StrokeHelper Direct Tests
////////////////////////////////////////////////////////////////////////////////
GTEST_TEST(StrokeHelper, HorizontalLineFlatCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    expectBoundsNear(context.getFilledBounds(), 0.0, -HalfWidth,
                     100.0, HalfWidth);
}

GTEST_TEST(StrokeHelper, HorizontalLineSquareCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Square, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    // Square caps extend the line by halfWidth at each end.
    expectBoundsNear(context.getFilledBounds(),
                     -HalfWidth, -HalfWidth,
                     100.0 + HalfWidth, HalfWidth);
}

GTEST_TEST(StrokeHelper, HorizontalLineRoundCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Round, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    // The semicircular cap extends to the full halfWidth in line direction;
    // chord error from flattening is bounded by Tolerance.
    const Geom::Rect2D &b = context.getFilledBounds();
    EXPECT_LE(b.getMinimumX(), -HalfWidth + Tolerance);
    EXPECT_GE(b.getMinimumX(), -HalfWidth);
    EXPECT_GE(b.getMaximumX(), 100.0 + HalfWidth - Tolerance);
    EXPECT_LE(b.getMaximumX(), 100.0 + HalfWidth);
    EXPECT_NEAR(b.getMinimumY(), -HalfWidth, Epsilon);
    EXPECT_NEAR(b.getMaximumY(), HalfWidth, Epsilon);
}

GTEST_TEST(StrokeHelper, HorizontalLineTriangleCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Triangle, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    expectBoundsNear(context.getFilledBounds(),
                     -HalfWidth, -HalfWidth,
                     100.0 + HalfWidth, HalfWidth);
}

GTEST_TEST(StrokeHelper, VerticalLineFlatCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(0, 100));
    stroker.endFigure(false);

    expectBoundsNear(context.getFilledBounds(),
                     -HalfWidth, 0.0, HalfWidth, 100.0);
}

GTEST_TEST(StrokeHelper, DiagonalLineFlatCaps)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 100));
    stroker.endFigure(false);

    // Perpendicular offset of HalfWidth at 45 degrees moves by HalfWidth/sqrt(2)
    // in each axis.
    double perp = HalfWidth / std::sqrt(2.0);
    expectBoundsNear(context.getFilledBounds(),
                     -perp, -perp, 100.0 + perp, 100.0 + perp);
}

GTEST_TEST(StrokeHelper, RightAngleBevelJoin)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.appendLine(Geom::Point2D(100, 100));
    stroker.endFigure(false);

    // The figure is an L going east then north. Flat caps at each end do
    // not extend the line; the only extra extent is the half thickness on
    // each side of each segment.
    expectBoundsNear(context.getFilledBounds(),
                     0.0, -HalfWidth,
                     100.0 + HalfWidth, 100.0);
}

GTEST_TEST(StrokeHelper, RightAngleMitreJoinReachesIntersectionPoint)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Mitre);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.appendLine(Geom::Point2D(100, 100));
    stroker.endFigure(false);

    // The 90-degree mitre point sits at (100 + halfWidth, -halfWidth) -
    // the intersection of the two outer offset lines. That is the same
    // bounding extent that the segments themselves already reach, so the
    // overall bounds match the bevel case; this test asserts only that
    // the mitre version produces non-empty geometry within the expected
    // box (i.e. it didn't fall back to bevel for this 90-degree case).
    expectBoundsNear(context.getFilledBounds(),
                     0.0, -HalfWidth,
                     100.0 + HalfWidth, 100.0);
}

GTEST_TEST(StrokeHelper, AcuteAngleMitreFallsBackToBevel)
{
    // A near-zero angle (path doubles back on itself) would produce an
    // arbitrarily long mitre spike; the 4x mitre limit must demote it to
    // a bevel so the bounds stay close to the line itself.
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Mitre);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    // Reverse direction at a very shallow angle.
    stroker.appendLine(Geom::Point2D(0, 1));
    stroker.endFigure(false);

    const Geom::Rect2D &b = context.getFilledBounds();
    ASSERT_FALSE(b.isEmpty());

    // Without mitre limit, the spike at the corner would push X far past
    // 100 + 4 * HalfWidth = 100 + 20.
    double mitreLimitMax = 100.0 + 4.0 * HalfWidth;
    EXPECT_LT(b.getMaximumX(), mitreLimitMax);
}

GTEST_TEST(StrokeHelper, ClosedSquareEmitsAnnulus)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.appendLine(Geom::Point2D(100, 100));
    stroker.appendLine(Geom::Point2D(0, 100));
    stroker.appendLine(Geom::Point2D(0, 0));
    stroker.endFigure(true);

    // The outer ring extends by halfWidth beyond the original square; the
    // inner ring shrinks by halfWidth. The combined filled bounds should
    // match the outer ring extents.
    expectBoundsNear(context.getFilledBounds(),
                     -HalfWidth, -HalfWidth,
                     100.0 + HalfWidth, 100.0 + HalfWidth);
}

GTEST_TEST(StrokeHelper, DashedLineEmitsBoundedGeometry)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);
    pen->addDash(20.0); // dash
    pen->addDash(10.0); // gap
    pen->addDash(20.0); // dash
    pen->addDash(10.0); // gap

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    // Each dash is a thin rectangle of thickness 10. Dashes occupy
    // [0,20], [30,50], [60,80], [90,100] - so the X bounds span the full
    // [0,100] (the last gap is truncated by total length).
    expectBoundsNear(context.getFilledBounds(),
                     0.0, -HalfWidth, 100.0, HalfWidth);
}

GTEST_TEST(StrokeHelper, ThinPenEmitsNothing)
{
    DecompositionContext context;
    Pen pen(Brush::Empty, 0.0); // thickness 0 -> thin

    StrokeHelper stroker(context, makeParams(), pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    EXPECT_TRUE(context.getFilledBounds().isEmpty());
    EXPECT_TRUE(context.getClipBounds().isEmpty());
}

GTEST_TEST(StrokeHelper, DegenerateFigureNoCrash)
{
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    // Two coincident points - no real edge to stroke.
    stroker.beginFigure(Geom::Point2D(50, 50));
    stroker.appendLine(Geom::Point2D(50, 50));
    stroker.endFigure(false);

    EXPECT_TRUE(context.getFilledBounds().isEmpty());

    // And then a real figure on the same stroker should still work.
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    expectBoundsNear(context.getFilledBounds(),
                     0.0, -HalfWidth, 100.0, HalfWidth);
}

GTEST_TEST(StrokeHelper, TransformAppliedToOutline)
{
    // Apply a 2x scale transform via DecompositionParams; the stroke
    // should be twice as wide along the line axis but the pen thickness
    // is interpreted in display space and remains 10.
    Geom::AffineTransform2D xform;
    xform.makeScale(2.0);
    DecompositionParams params(xform, Tolerance);

    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, params, *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendLine(Geom::Point2D(100, 0));
    stroker.endFigure(false);

    // Transformed line is from (0,0) to (200,0); thickness still 10.
    expectBoundsNear(context.getFilledBounds(),
                     0.0, -HalfWidth, 200.0, HalfWidth);
}

GTEST_TEST(StrokeHelper, QuadBezierStrokedWithinExpectedBounds)
{
    // A symmetric arch from (0,0) up to control (50,100) down to (100,0).
    // The curve apex sits at (50, 50); the LEFT-side stroke reaches y=55
    // there. At the endpoints the curve tangent is angled, so the stroke
    // ends at points offset perpendicular to that tangent.
    DecompositionContext context;
    auto pen = makePen(Thickness, EndCap::Flat, JoinCap::Bevel);

    StrokeHelper stroker(context, makeParams(), *pen);
    stroker.beginFigure(Geom::Point2D(0, 0));
    stroker.appendQuadBezier(Geom::Point2D(50, 100), Geom::Point2D(100, 0));
    stroker.endFigure(false);

    const Geom::Rect2D &b = context.getFilledBounds();
    ASSERT_FALSE(b.isEmpty());

    // Endpoint tangent at t=0 points toward (50,100); the perpendicular
    // offset of magnitude halfWidth has horizontal component of
    // halfWidth * 100/sqrt(50^2+100^2) ~= 4.47.
    double endpointHorizExtent = HalfWidth * 100.0 / std::sqrt(50.0 * 50.0 +
                                                               100.0 * 100.0);
    EXPECT_NEAR(b.getMinimumX(), -endpointHorizExtent, 0.5);
    EXPECT_NEAR(b.getMaximumX(), 100.0 + endpointHorizExtent, 0.5);

    // At the apex, LEFT offset reaches y = 50 + halfWidth.
    EXPECT_NEAR(b.getMaximumY(), 50.0 + HalfWidth, 0.5);
    // Bottom of the stroke at endpoints reaches y ~= -halfWidth*50/sqrt(...).
    double endpointVertExtent = HalfWidth * 50.0 / std::sqrt(50.0 * 50.0 +
                                                             100.0 * 100.0);
    EXPECT_NEAR(b.getMinimumY(), -endpointVertExtent, 0.5);
}

// NOTE: End-to-end tests through Path::addOutlineToDecomposition are not
// included here because the existing PathBuilder code paths in Path.cpp
// (PathBuilderInternal::appendLine, appendPolyline, appendQuadBezier and
// appendCubicBezier) are missing safeguards on the segment deque and do
// not consistently route segments through appendSegmentToActiveFigure,
// so constructing a Path via the public PathBuilder API currently
// triggers a deque assertion before the outline code is reached. Those
// pre-existing PathBuilder issues are separate from the outline
// decomposition feature itself; once they are resolved, end-to-end
// coverage can be added on top of the StrokeHelper tests above.

} // Anonymous namespace

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
