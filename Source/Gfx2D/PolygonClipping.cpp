//! @file Gfx2D/PolygonClipping.cpp
//! @brief Internal helpers for clipping triangle lists against convex
//! polygons (Sutherland-Hodgman).
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "PolygonClipping.hpp"

#include <array>
#include <cstddef>

namespace Ag {
namespace Gfx2D {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

//! @brief Signed perpendicular distance of @a p from the directed line
//! through @a edgeStart -> @a edgeEnd. Positive when @a p is on the left
//! of the directed edge — i.e. inside, for a CCW clip polygon.
inline double signedDistance(const Geom::Point2D &p,
                             const Geom::Point2D &edgeStart,
                             const Geom::Point2D &edgeEnd)
{
    // TODO: Determinant - implement using SIMD or Point2D operations.

    const double ex = edgeEnd.getX() - edgeStart.getX();
    const double ey = edgeEnd.getY() - edgeStart.getY();
    const double px = p.getX() - edgeStart.getX();
    const double py = p.getY() - edgeStart.getY();

    return ex * py - ey * px;
}

//! @brief Linearly interpolates the intersection of segment a->b with the
//! line through edgeStart->edgeEnd. Caller has verified the two endpoint
//! signed distances have opposite signs.
Geom::Point2D intersect(const Geom::Point2D &a, double da,
                        const Geom::Point2D &b, double db)
{
    // TODO: Implement using SIMD-compatible Point2D operations.

    const double t = da / (da - db);
    return Geom::Point2D(a.getX() + t * (b.getX() - a.getX()),
                         a.getY() + t * (b.getY() - a.getY()));
}

//! @brief Clips a convex polygon (the @a input vertex list, in order) against
//! one half-plane defined by the directed edge edgeStart->edgeEnd of a CCW
//! clip polygon. The result is appended to @a output.
void clipAgainstHalfPlane(const std::vector<Geom::Point2D> &input,
                          const Geom::Point2D &edgeStart,
                          const Geom::Point2D &edgeEnd,
                          std::vector<Geom::Point2D> &output)
{
    output.clear();

    if (input.empty())
        return;

    Geom::Point2D prev = input.back();
    double prevDist = signedDistance(prev, edgeStart, edgeEnd);

    for (const Geom::Point2D &cur : input)
    {
        const double curDist = signedDistance(cur, edgeStart, edgeEnd);

        if (curDist >= 0.0)
        {
            // Current vertex is inside (or on) the half-plane.
            if (prevDist < 0.0)
            {
                // Crossing into the half-plane — emit the entry point.
                output.push_back(intersect(prev, prevDist, cur, curDist));
            }
            output.push_back(cur);
        }
        else if (prevDist >= 0.0)
        {
            // Crossing out of the half-plane — emit the exit point only.
            output.push_back(intersect(prev, prevDist, cur, curDist));
        }

        prev = cur;
        prevDist = curDist;
    }
}

//! @brief Clips a single source triangle against the entire convex clip
//! polygon, fan-triangulates the surviving sub-polygon, and appends its
//! vertices and triangle indices to the output buffers.
void clipAndAppendTriangle(const Geom::Point2D &v0,
                           const Geom::Point2D &v1,
                           const Geom::Point2D &v2,
                           const Geom::Point2DCollectionView &clipVertices,
                           Geom::Point2DCollection &outVertices,
                           Geom::DCEL::IDDeque &outTriangles)
{
    std::vector<Geom::Point2D> bufferA;
    std::vector<Geom::Point2D> bufferB;

    bufferA.reserve(8);
    bufferB.reserve(8);

    bufferA.push_back(v0);
    bufferA.push_back(v1);
    bufferA.push_back(v2);

    std::vector<Geom::Point2D> *current = &bufferA;
    std::vector<Geom::Point2D> *next    = &bufferB;

    const size_t clipCount = clipVertices.getCount();

    for (size_t i = 0; i < clipCount && !current->empty(); ++i)
    {
        const Geom::Point2D &edgeStart = clipVertices.getAt(i);
        const Geom::Point2D &edgeEnd   = clipVertices.getAt((i + 1) % clipCount);

        clipAgainstHalfPlane(*current, edgeStart, edgeEnd, *next);
        std::swap(current, next);
    }

    if (current->size() < 3)
        return;

    // Fan-triangulate the surviving convex sub-polygon. Each new triangle is
    // (v0, v[i-1], v[i]) for i in [2, n).
    const Geom::DCEL::ID baseIndex = static_cast<Geom::DCEL::ID>(outVertices.size());

    for (const Geom::Point2D &p : *current)
        outVertices.push_back(p);

    const size_t n = current->size();
    for (size_t i = 2; i < n; ++i)
    {
        outTriangles.push_back(baseIndex);
        outTriangles.push_back(baseIndex + static_cast<Geom::DCEL::ID>(i - 1));
        outTriangles.push_back(baseIndex + static_cast<Geom::DCEL::ID>(i));
    }
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Public Function Definitions
////////////////////////////////////////////////////////////////////////////////
PartitionedPolygon clipPolygonAgainstConvex(const PartitionedPolygon &source,
                                            const Geom::Point2DCollectionView &clipVertices)
{
    const auto &points    = source.getPoints();
    const auto &triangles = source.getTriangleIndices();

    if (clipVertices.getCount() < 3 ||
        points.getCount() == 0 ||
        triangles.getCount() < 3)
    {
        return PartitionedPolygon(source.getOriginalBounds());
    }

    Geom::Point2DCollection outVertices;
    Geom::DCEL::IDDeque     outTriangles;
    Geom::DCEL::IDDeque     outOutline; // empty: outline correspondence is lost

    outVertices.reserve(points.getCount());

    const size_t triCount = triangles.getCount() / 3;

    for (size_t t = 0; t < triCount; ++t)
    {
        const auto i0 = triangles.getAt(t * 3);
        const auto i1 = triangles.getAt(t * 3 + 1);
        const auto i2 = triangles.getAt(t * 3 + 2);

        clipAndAppendTriangle(points.getAt(i0),
                              points.getAt(i1),
                              points.getAt(i2),
                              clipVertices,
                              outVertices,
                              outTriangles);
    }

    if (outTriangles.empty())
        return PartitionedPolygon(source.getOriginalBounds());

    return PartitionedPolygon(outVertices, outTriangles, outOutline,
                              source.getOriginalBounds());
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
