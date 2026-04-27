//! @file Gfx2D/StrokeHelper.cpp
//! @brief The definition of an internal helper which expands stroked path
//! geometry into closed offset polygons.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <cmath>

#include "StrokeHelper.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Constants and Helpers
////////////////////////////////////////////////////////////////////////////////
//! @brief Fallback mitre limit expressed as a multiple of the line thickness.
//! Joins exceeding this limit are demoted to bevel to avoid spikes at very
//! acute angles.
constexpr double MitreLimit = 4.0;

//! @brief Smallest edge length, in display units, for which an offset will be
//! attempted. Edges shorter than this are treated as zero length.
constexpr double EdgeEpsilon = 1e-9;

//! @brief Returns the unit vector perpendicular to @p v rotated 90 degrees
//! counter-clockwise. The zero vector is returned unchanged.
Geom::Point2D leftNormal(const Geom::Point2D &v) noexcept
{
    return Geom::Point2D(-v.getY(), v.getX());
}

//! @brief Normalises a vector or returns @c std::nullopt-equivalent zero if
//! the input is degenerate.
Geom::Point2D safeNormalise(const Geom::Point2D &v) noexcept
{
    double m = v.magnitude();
    if (m < EdgeEpsilon)
        return Geom::Point2D(0, 0);
    return v * (1.0 / m);
}

//! @brief Determines an angle step for discretising an arc to a given
//! chord-error tolerance.
//! @param[in] radius The radius of the arc.
//! @param[in] tolerance The maximum chord error allowed.
//! @return An angular step in radians, clamped to a sensible maximum.
double angleStepForArc(double radius, double tolerance) noexcept
{
    if (radius <= tolerance)
    {
        // The whole arc is within the tolerance of a single chord.
        return Geom::Angle::Pi;
    }

    double cosTerm = 1.0 - (tolerance / radius);
    cosTerm = std::clamp(cosTerm, -1.0, 1.0);

    double step = 2.0 * std::acos(cosTerm);
    return std::clamp(step, 1e-3, Geom::Angle::Pi * 0.25);
}

//! @brief Appends a fan of points approximating a circular arc.
//! @param[in,out] out Receives the appended points (excluding the start point,
//! which is assumed to already be present at the back of @p out).
//! @param[in] centre The centre of the arc.
//! @param[in] radius The radius of the arc.
//! @param[in] startAngle The starting angle of the arc in radians.
//! @param[in] sweep The signed sweep angle. Positive sweeps anti-clockwise,
//! negative sweeps clockwise.
//! @param[in] tolerance The maximum chord error tolerated.
void appendArcFan(Geom::Point2DCollection &out,
                  const Geom::Point2D &centre, double radius,
                  double startAngle, double sweep, double tolerance)
{
    if (std::abs(sweep) < 1e-9 || radius < EdgeEpsilon)
        return;

    double absStep = angleStepForArc(radius, tolerance);
    auto stepCount = static_cast<size_t>(std::ceil(std::abs(sweep) / absStep));
    if (stepCount < 1)
        stepCount = 1;

    double dt = sweep / static_cast<double>(stepCount);

    for (size_t i = 1; i <= stepCount; ++i)
    {
        double a = startAngle + dt * static_cast<double>(i);
        out.emplace_back(centre.getX() + radius * std::cos(a),
                         centre.getY() + radius * std::sin(a));
    }
}

//! @brief Appends an end cap to an offset polygon being built.
//! @param[in,out] out The polygon under construction. The last point in @p out
//! must be the offset position on the @em entry side of the cap (e.g. for an
//! end cap this is the LEFT offset of the line end).
//! @param[in] anchor The position on the original polyline where the cap is
//! anchored (the line end point).
//! @param[in] forward A unit vector pointing away from the line in the
//! direction the cap should extend.
//! @param[in] entryNormal The unit normal pointing from @p anchor to the
//! entry-side offset point (currently at the back of @p out).
//! @param[in] cap The cap style.
//! @param[in] halfWidth Half the line thickness.
//! @param[in] tolerance The flattening tolerance for round caps.
//! @remark The function will append all points required to bridge from the
//! entry-side offset to the exit-side offset, including the exit-side offset
//! itself.
void appendCap(Geom::Point2DCollection &out,
               const Geom::Point2D &anchor,
               const Geom::Point2D &forward,
               const Geom::Point2D &entryNormal,
               EndCap cap, double halfWidth, double tolerance)
{
    Geom::Point2D exitNormal(-entryNormal.getX(), -entryNormal.getY());
    Geom::Point2D exitPoint = anchor + (exitNormal * halfWidth);

    switch (cap)
    {
    case EndCap::Flat:
        out.push_back(exitPoint);
        break;

    case EndCap::Square:
    {
        Geom::Point2D extrude = forward * halfWidth;
        out.push_back(out.back() + extrude);
        out.push_back(exitPoint + extrude);
        out.push_back(exitPoint);
        break;
    }

    case EndCap::Triangle:
        out.push_back(anchor + (forward * halfWidth));
        out.push_back(exitPoint);
        break;

    case EndCap::Round:
    {
        // Sweep a semicircle from the entry offset to the exit offset, on
        // the side @p forward points to.
        double startAngle = std::atan2(entryNormal.getY(), entryNormal.getX());
        // Sweep direction: rotate by +pi if forward is on the left of
        // entryNormal (cross > 0), -pi otherwise. The cross of entryNormal
        // and forward gives that sign.
        double cross = entryNormal.determinant(forward);
        double sweep = (cross >= 0.0) ? Geom::Angle::Pi : -Geom::Angle::Pi;

        appendArcFan(out, anchor, halfWidth, startAngle, sweep, tolerance);
        // appendArcFan ends exactly at the exit offset point.
        break;
    }
    }
}

//! @brief Appends a join to an offset polygon being built.
//! @param[in,out] out The polygon under construction. The last point in @p out
//! must be the offset position on the incoming edge at @p anchor.
//! @param[in] anchor The original polyline vertex.
//! @param[in] inDir Unit direction of the incoming edge (towards @p anchor).
//! @param[in] outDir Unit direction of the outgoing edge (away from @p anchor).
//! @param[in] join The join style.
//! @param[in] halfWidth Half the line thickness.
//! @param[in] tolerance The flattening tolerance for round joins.
//! @remark The function appends all points required to bridge between the two
//! offset positions, ending at the outgoing-edge offset position. The walk
//! convention is "left side": the offsets are anchor + halfWidth*leftNormal(dir).
void appendJoin(Geom::Point2DCollection &out,
                const Geom::Point2D &anchor,
                const Geom::Point2D &inDir,
                const Geom::Point2D &outDir,
                JoinCap join, double halfWidth, double tolerance)
{
    Geom::Point2D nIn = leftNormal(inDir);
    Geom::Point2D nOut = leftNormal(outDir);
    Geom::Point2D outerIn = anchor + (nIn * halfWidth);
    Geom::Point2D outerOut = anchor + (nOut * halfWidth);

    // Walk the incoming offset edge up to the corner. The previous join
    // (or the seed of the polygon) leaves @c out ending at the offset of
    // the incoming edge at the @em previous vertex; we need to advance to
    // the offset of the same edge at this vertex, which is @c outerIn.
    if (out.empty() ||
        (outerIn - out.back()).magnitudeSquared() > EdgeEpsilon * EdgeEpsilon)
    {
        out.push_back(outerIn);
    }

    // Determine the turn direction. With a +90-degree CCW normal
    // convention, a left turn (cross > 0) places the LEFT-side offsets on
    // the INNER side of the bend; a right turn (cross < 0) places them on
    // the OUTER side where a join cap is needed. On the inner side the
    // two offsets simply meet (with a small overlap that downstream
    // cleanup resolves).
    double cross = inDir.determinant(outDir);

    if (cross >= 0.0)
    {
        out.push_back(outerOut);
        return;
    }

    switch (join)
    {
    case JoinCap::Bevel:
        out.push_back(outerOut);
        break;

    case JoinCap::Mitre: {
        // Solve for the intersection of the two outer offset lines:
        //   outerIn + s * inDir
        //   outerOut - t * outDir
        // The bisector direction nIn + nOut points from anchor towards the
        // mitre point; its length determines the mitre distance.
        Geom::Point2D bisector = nIn + nOut;
        double bisLen = bisector.magnitude();

        if (bisLen < EdgeEpsilon)
        {
            // 180 degree turn - mitre is at infinity. Fall back to bevel.
            out.push_back(outerOut);
            break;
        }

        Geom::Point2D bisUnit = bisector * (1.0 / bisLen);

        // The mitre distance from the anchor along the bisector is
        // halfWidth / cos(theta/2) where theta is the turn angle. Since
        // bisUnit . nIn = cos(theta/2), the distance is halfWidth / (bisUnit . nIn).
        double cosHalf = bisUnit.dotProduct(nIn);
        if (cosHalf < EdgeEpsilon)
        {
            // Should not happen when cross > 0, but guard anyway.
            out.push_back(outerOut);
            break;
        }

        double mitreDistance = halfWidth / cosHalf;
        if (mitreDistance > halfWidth * MitreLimit)
        {
            // Spike is too long; fall back to bevel.
            out.push_back(outerOut);
            break;
        }

        Geom::Point2D mitrePoint = anchor + (bisUnit * mitreDistance);
        out.push_back(mitrePoint);
        out.push_back(outerOut);
    } break;

    case JoinCap::Round: {
        double startAngle = std::atan2(nIn.getY(), nIn.getX());
        double endAngle = std::atan2(nOut.getY(), nOut.getX());

        // Right turn (cross < 0): the outer arc sweeps clockwise (negative)
        // by the deflection angle. Wrap into (-pi, pi] so the short way
        // around is taken.
        double sweep = endAngle - startAngle;
        while (sweep > Geom::Angle::Pi)
            sweep -= Geom::Angle::Pi2;
        while (sweep <= -Geom::Angle::Pi)
            sweep += Geom::Angle::Pi2;

        appendArcFan(out, anchor, halfWidth, startAngle, sweep, tolerance);
    } break;
    }
}

//! @brief Builds a single closed offset polygon for an open polyline run.
//! @param[in] vertices The polyline vertices, in walk order.
//! @param[in] firstIndex Index of the first vertex (inclusive).
//! @param[in] lastIndex Index of the last vertex (inclusive). Must be greater
//! than @p firstIndex.
//! @param[in] startCap The cap style for the start of the run.
//! @param[in] endCap The cap style for the end of the run.
//! @param[in] join The join style for interior corners.
//! @param[in] halfWidth Half the pen thickness.
//! @param[in] tolerance The flattening tolerance.
//! @return The closed offset polygon (first point repeated at the back).
Geom::Point2DCollection buildOpenStrokePolygon(
    const Geom::Point2DDeque &vertices,
    size_t firstIndex, size_t lastIndex,
    EndCap startCap, EndCap endCap, JoinCap join,
    double halfWidth, double tolerance)
{
    Geom::Point2DCollection polygon;

    auto firstEdgeDir = [&](size_t i) -> Geom::Point2D {
        // Direction of the edge starting at vertices[i] going to vertices[i+1].
        return safeNormalise(vertices[i + 1] - vertices[i]);
    };

    // --- LEFT side: walk forwards from firstIndex to lastIndex. ---
    Geom::Point2D dirFirst = firstEdgeDir(firstIndex);
    if (dirFirst.magnitudeSquared() < EdgeEpsilon)
        return polygon; // Degenerate run.

    polygon.push_back(vertices[firstIndex] + (leftNormal(dirFirst) * halfWidth));

    Geom::Point2D inDir = dirFirst;
    for (size_t i = firstIndex + 1; i < lastIndex; ++i)
    {
        Geom::Point2D outDir = firstEdgeDir(i);
        if (outDir.magnitudeSquared() < EdgeEpsilon)
            continue;

        appendJoin(polygon, vertices[i], inDir, outDir, join, halfWidth, tolerance);
        inDir = outDir;
    }

    // Walk the LEFT offset of the final edge up to the line end and then
    // emit the end cap, which bridges to the RIGHT offset.
    {
        Geom::Point2D entryNormal = leftNormal(inDir);
        Geom::Point2D entryOffset =
            vertices[lastIndex] + (entryNormal * halfWidth);

        if ((entryOffset - polygon.back()).magnitudeSquared() >
            EdgeEpsilon * EdgeEpsilon)
        {
            polygon.push_back(entryOffset);
        }

        appendCap(polygon, vertices[lastIndex], inDir, entryNormal,
                  endCap, halfWidth, tolerance);
    }

    // --- RIGHT side: walk backwards from lastIndex to firstIndex. ---
    // Reuse the same left-side machinery on the reversed polyline.
    auto reverseEdgeDir = [&](size_t i) -> Geom::Point2D {
        // Direction of reversed edge: from vertices[i] to vertices[i-1].
        return safeNormalise(vertices[i - 1] - vertices[i]);
    };

    inDir = reverseEdgeDir(lastIndex);
    if (inDir.magnitudeSquared() < EdgeEpsilon)
        return polygon; // Should not happen given firstEdgeDir already passed.

    // The end cap above deposited the LEFT-of-reversed-walk offset at
    // vertices[lastIndex] as its final appended point, so the reverse walk
    // is already correctly seeded.

    for (size_t i = lastIndex - 1; i > firstIndex; --i)
    {
        Geom::Point2D outDir = reverseEdgeDir(i);
        if (outDir.magnitudeSquared() < EdgeEpsilon)
            continue;

        appendJoin(polygon, vertices[i], inDir, outDir, join, halfWidth, tolerance);
        inDir = outDir;
    }

    // Walk the LEFT-of-reversed-walk offset of the final reversed edge up
    // to vertices[firstIndex] and emit the start cap.
    {
        Geom::Point2D entryNormal = leftNormal(inDir);
        Geom::Point2D entryOffset =
            vertices[firstIndex] + (entryNormal * halfWidth);

        if ((entryOffset - polygon.back()).magnitudeSquared() >
            EdgeEpsilon * EdgeEpsilon)
        {
            polygon.push_back(entryOffset);
        }

        appendCap(polygon, vertices[firstIndex], inDir, entryNormal,
                  startCap, halfWidth, tolerance);
    }

    // Close the polygon explicitly so defineConnectedEdges produces a loop,
    // unless the start cap already brought us back to the seed.
    if (polygon.size() >= 2 &&
        (polygon.front() - polygon.back()).magnitudeSquared() >
            EdgeEpsilon * EdgeEpsilon)
    {
        polygon.push_back(polygon.front());
    }

    return polygon;
}

//! @brief Builds the LEFT offset ring of a closed polyline.
Geom::Point2DCollection buildClosedRing(const Geom::Point2DDeque &vertices,
                                        size_t vertexCount,
                                        bool reverseWalk,
                                        JoinCap join,
                                        double halfWidth, double tolerance)
{
    Geom::Point2DCollection ring;

    if (vertexCount < 2)
        return ring;

    auto walkIndex = [&](size_t i) -> size_t {
        return reverseWalk ? (vertexCount - 1 - i) : i;
    };

    auto edgeDir = [&](size_t i) -> Geom::Point2D {
        // Direction of the i-th edge in the walk.
        size_t a = walkIndex(i);
        size_t b = walkIndex(i + 1);
        return safeNormalise(vertices[b] - vertices[a]);
    };

    size_t edgeCount = vertexCount - 1; // last vertex equals first.
    if (edgeCount == 0)
        return ring;

    Geom::Point2D inDir = edgeDir(edgeCount - 1);
    if (inDir.magnitudeSquared() < EdgeEpsilon)
        return ring;

    // Seed with the offset of the first vertex using the join between the
    // last edge (incoming) and the first edge (outgoing).
    Geom::Point2D firstOut = edgeDir(0);
    if (firstOut.magnitudeSquared() < EdgeEpsilon)
        return ring;

    // Place the seed offset point on the incoming edge before the first
    // join, then run the join machinery as for any other corner.
    Geom::Point2D seedAnchor = vertices[walkIndex(0)];
    ring.push_back(seedAnchor + (leftNormal(inDir) * halfWidth));
    appendJoin(ring, seedAnchor, inDir, firstOut, join, halfWidth, tolerance);

    inDir = firstOut;
    for (size_t i = 1; i < edgeCount; ++i)
    {
        Geom::Point2D outDir = edgeDir(i);
        if (outDir.magnitudeSquared() < EdgeEpsilon)
            continue;

        appendJoin(ring, vertices[walkIndex(i)], inDir, outDir,
                   join, halfWidth, tolerance);
        inDir = outDir;
    }

    if (ring.size() >= 2 &&
        (ring.front() - ring.back()).magnitudeSquared() >
            EdgeEpsilon * EdgeEpsilon)
    {
        ring.push_back(ring.front());
    }

    return ring;
}

//! @brief Pushes the points of a flattened curve onto a deque, skipping the
//! first point (assumed to already match the back of @p target).
void appendFlattened(Geom::Point2DDeque &target,
                     std::vector<double> &cumulativeLength,
                     const Geom::Point2DCollection &flattened)
{
    if (flattened.size() < 2)
        return;

    Geom::Point2D prev = target.empty() ? flattened.front() : target.back();

    for (size_t i = 1; i < flattened.size(); ++i)
    {
        const Geom::Point2D &p = flattened[i];
        double segLen = p.distance(prev);

        if (segLen < EdgeEpsilon)
            continue;

        target.push_back(p);
        cumulativeLength.push_back(cumulativeLength.back() + segLen);
        prev = p;
    }
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// StrokeHelper Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a stroker bound to a particular decomposition target.
//! @param[in] context Where the stroked geometry is emitted.
//! @param[in] params The decomposition parameters (transform and tolerance).
//! @param[in] pen The line style.
StrokeHelper::StrokeHelper(DecompositionContext &context,
                 const DecompositionParams &params,
                 const Pen &pen) :
    _context(context),
    _params(params),
    _pen(pen),
    _halfWidth(std::max(pen.getThickness(), 0.0) * 0.5),
    _tolerance(std::max(params.getApproxThreadhold(), 1e-6)),
    _figureActive(false)
{
    _cumulativeLength.push_back(0.0);
}

//! @brief Begins accumulating a new figure.
//! @param[in] start The first point on the figure, in untransformed coordinates.
void StrokeHelper::beginFigure(const Geom::Point2D &start)
{
    _vertices.clear();
    _cumulativeLength.clear();
    _cumulativeLength.push_back(0.0);

    _vertices.push_back(_params.transform(start));
    _figureActive = true;
}

//! @brief Appends a single point to the polyline, updating the running length.
void StrokeHelper::appendPoint(const Geom::Point2D &point)
{
    if (_vertices.empty())
    {
        _vertices.push_back(point);
        return;
    }

    double segLen = point.distance(_vertices.back());
    if (segLen < EdgeEpsilon)
        return;

    _vertices.push_back(point);
    _cumulativeLength.push_back(_cumulativeLength.back() + segLen);
}

void StrokeHelper::appendLine(const Geom::Point2D &end)
{
    appendPoint(_params.transform(end));
}

void StrokeHelper::appendQuadBezier(const Geom::Point2D &ctrl,
                               const Geom::Point2D &end)
{
    Geom::Point2D start = _vertices.empty() ? Geom::Point2D(0, 0) : _vertices.back();

    Geom::QuadBezierCurve2D curve(start,
                                  _params.transform(ctrl),
                                  _params.transform(end));

    Geom::Point2DCollection flattened = curve.toPolyline(_tolerance);
    appendFlattened(_vertices, _cumulativeLength, flattened);
}

void StrokeHelper::appendCubicBezier(const Geom::Point2D &ctrl1,
                                const Geom::Point2D &ctrl2,
                                const Geom::Point2D &end)
{
    Geom::Point2D start = _vertices.empty() ? Geom::Point2D(0, 0) : _vertices.back();

    Geom::CubicBezierCurve2D curve(start,
                                   _params.transform(ctrl1),
                                   _params.transform(ctrl2),
                                   _params.transform(end));

    Geom::Point2DCollection flattened = curve.toPolyline(_tolerance);
    appendFlattened(_vertices, _cumulativeLength, flattened);
}

void StrokeHelper::appendArc(const Geom::Point2D &end, const Geom::Point2D &axes,
                        double rotation, bool isLargeSweep, bool isClockwise)
{
    Geom::Point2D start = _vertices.empty() ? Geom::Point2D(0, 0) : _vertices.back();
    Geom::Point2D transformedEnd = _params.transform(end);

    // The axes argument is a vector of (xRadius, yRadius); to apply the
    // affine transform to it consistently we transform the offset point
    // (end + axes) and subtract the transformed end. This is equivalent to
    // applying the linear part of the transform to the axes vector and
    // matches how PathSegment::decompose recovers the radii vector for
    // fill geometry.
    Geom::Point2D transformedAxes =
        _params.transform(end + axes) - transformedEnd;

    Geom::Arc2D arc(start, transformedEnd, transformedAxes, rotation,
                    isLargeSweep, isClockwise);

    Geom::Point2DCollection flattened = arc.toPolyline(_tolerance);
    appendFlattened(_vertices, _cumulativeLength, flattened);
}

//! @brief Finalises the figure and emits stroked geometry to the context.
//! @param[in] isClosed Whether the figure should be treated as closed (i.e.
//! the first and last vertex are the same point).
void StrokeHelper::endFigure(bool isClosed)
{
    if (_figureActive == false || _vertices.size() < 2 || _halfWidth <= 0.0)
    {
        _figureActive = false;
        return;
    }

    if (_pen.isSolid())
        emitSolid(isClosed);
    else
        emitDashed(isClosed);

    _figureActive = false;
    _vertices.clear();
    _cumulativeLength.clear();
    _cumulativeLength.push_back(0.0);
}

void StrokeHelper::emitSolid(bool isClosed)
{
    if (isClosed)
    {
        emitClosedAnnulus();
    }
    else
    {
        emitOpenStroke(0, _vertices.size() - 1,
                       _pen.getLineStartCap(), _pen.getLineEndCap());
    }
}

void StrokeHelper::emitOpenStroke(size_t firstVertex, size_t lastVertex,
                             EndCap startCap, EndCap endCap)
{
    if (firstVertex >= lastVertex)
        return;

    Geom::Point2DCollection polygon =
        buildOpenStrokePolygon(_vertices, firstVertex, lastVertex,
                               startCap, endCap, _pen.getJoinCap(),
                               _halfWidth, _tolerance);

    if (polygon.size() >= 3)
        _context.defineConnectedEdges(polygon, false);
}

void StrokeHelper::emitClosedAnnulus()
{
    // For closed figures the stroked geometry is an annulus: the LEFT
    // offset ring (forward walk) plus the RIGHT offset ring (reverse walk
    // - which the ring builder produces by walking the polyline in the
    // opposite direction).
    size_t n = _vertices.size();

    Geom::Point2DCollection outer =
        buildClosedRing(_vertices, n, false, _pen.getJoinCap(),
                        _halfWidth, _tolerance);

    Geom::Point2DCollection inner =
        buildClosedRing(_vertices, n, true, _pen.getJoinCap(),
                        _halfWidth, _tolerance);

    if (outer.size() >= 3)
        _context.defineConnectedEdges(outer, false);
    if (inner.size() >= 3)
        _context.defineConnectedEdges(inner, false);
}

//! @brief Locates a point at a specified arc length along the accumulated
//! polyline.
//! @param[in] targetLength The arc length to locate, clamped to [0, total].
//! @param[in,out] edgeHint The starting edge index for the search; updated to
//! the edge containing the result for use in subsequent calls.
//! @return The point on the polyline at @p targetLength.
Geom::Point2D StrokeHelper::pointAtArcLength(double targetLength,
                                        size_t &edgeHint) const
{
    double total = _cumulativeLength.back();
    targetLength = std::clamp(targetLength, 0.0, total);

    while (edgeHint + 1 < _cumulativeLength.size() &&
           _cumulativeLength[edgeHint + 1] < targetLength)
    {
        ++edgeHint;
    }

    while (edgeHint > 0 &&
           _cumulativeLength[edgeHint] > targetLength)
    {
        --edgeHint;
    }

    double segStart = _cumulativeLength[edgeHint];
    double segEnd = _cumulativeLength[edgeHint + 1];
    double segLen = segEnd - segStart;

    double t = (segLen > EdgeEpsilon)
        ? (targetLength - segStart) / segLen
        : 0.0;

    const Geom::Point2D &a = _vertices[edgeHint];
    const Geom::Point2D &b = _vertices[edgeHint + 1];

    return a + (b - a) * t;
}

void StrokeHelper::emitDashed(bool isClosed)
{
    const auto &pattern = _pen.getDashPattern();

    if (pattern.empty())
    {
        emitSolid(isClosed);
        return;
    }

    double totalLength = _cumulativeLength.back();

    if (totalLength < EdgeEpsilon)
        return;

    // The pattern alternates dash, gap, dash, gap, ... starting with a dash.
    // A leading entry of length 0 indicates the line begins with a gap; in
    // that case the first real run is the second entry as a gap.
    double cursor = 0.0;
    size_t patternIndex = 0;
    bool drawingDash = true;
    EndCap dashCap = _pen.getDashCap();

    if (pattern.front() <= 0.0)
    {
        drawingDash = false;
        ++patternIndex;
    }

    size_t edgeHint = 0;

    while (cursor < totalLength)
    {
        double length = pattern[patternIndex % pattern.size()];

        if (length <= 0.0)
        {
            // Skip degenerate entries to avoid an infinite loop.
            ++patternIndex;
            drawingDash = !drawingDash;
            continue;
        }

        double next = std::min(cursor + length, totalLength);

        if (drawingDash)
        {
            // Build a contiguous polyline for this dash by walking the
            // accumulated vertices between cursor and next, inserting
            // synthetic endpoints at the cursor positions.
            Geom::Point2DDeque dashRun;
            std::vector<double> dashLengths;
            dashLengths.push_back(0.0);

            size_t hintLocal = edgeHint;
            Geom::Point2D startPoint = pointAtArcLength(cursor, hintLocal);
            dashRun.push_back(startPoint);

            // Walk through any whole vertices that fall inside [cursor, next].
            size_t walkIndex = hintLocal + 1;

            while (walkIndex < _cumulativeLength.size() &&
                   _cumulativeLength[walkIndex] < next)
            {
                const Geom::Point2D &v = _vertices[walkIndex];
                double segLen = v.distance(dashRun.back());
                if (segLen >= EdgeEpsilon)
                {
                    dashRun.push_back(v);
                    dashLengths.push_back(dashLengths.back() + segLen);
                }
                ++walkIndex;
            }

            size_t endHint = walkIndex > 0 ? walkIndex - 1 : 0;
            Geom::Point2D endPoint = pointAtArcLength(next, endHint);

            double tailLen = endPoint.distance(dashRun.back());

            if (tailLen >= EdgeEpsilon)
            {
                dashRun.push_back(endPoint);
                dashLengths.push_back(dashLengths.back() + tailLen);
            }

            if (dashRun.size() >= 2)
            {
                Geom::Point2DCollection polygon =
                    buildOpenStrokePolygon(dashRun, 0, dashRun.size() - 1,
                                           dashCap, dashCap, _pen.getJoinCap(),
                                           _halfWidth, _tolerance);

                if (polygon.size() >= 3)
                    _context.defineConnectedEdges(polygon, false);
            }
        }

        cursor = next;
        ++patternIndex;
        drawingDash = !drawingDash;
    }
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
