//! @file Ag/Gfx2D/DecompositionContext.hpp
//! @brief The declaration of an object which can be used to decompose graphic
//! artefacts into partitioned paths and lines while retaining resources
//! between operations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_DECOMPOSITION_CONTEXT_HPP__
#define __GFX_2D_DECOMPOSITION_CONTEXT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "Ag/Geometry.hpp"
#include "Ag/Gfx2D/PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object describing the parameters required to decompose a path
//! into a set of straight line segments.
class DecompositionParams
{
private:
    // Internal Fields
    Geom::AffineTransform2D _transform;
    double _approxThreashold;
    bool _isIdentity;
public:
    // Construction/Destruction
    DecompositionParams();
    DecompositionParams(double threshold);
    DecompositionParams(const Geom::AffineTransform2D &transform,
                        double threshold = 1.0);
    ~DecompositionParams() = default;

    // Accessors
    constexpr bool isTransformed() const noexcept { return _isIdentity; }
    constexpr double getApproxThreadhold() const noexcept { return _approxThreashold; }
    const Geom::AffineTransform2D getTransform() const noexcept { return _transform; }

    // Operations
    Geom::Point2D transform(const Geom::Point2D &original) const noexcept;
};

//! @brief An object describing the decomposition of a path or paths.
class DecompositionStatistics
{
private:
    // Internal Fields
    Geom::Rect2D _bounds;
    size_t _pointCount;
    size_t _edgeCount;
    size_t _figureCount;
public:
    DecompositionStatistics();
    DecompositionStatistics(const Geom::Rect2D &bounds,
                            size_t pointCount, size_t edgeCount,
                            size_t figureCount);
    ~DecompositionStatistics() = default;

    // Accessors
    constexpr bool isEmpty() const noexcept { return _pointCount == 0; }
    constexpr const Geom::Rect2D &getBounds() const noexcept { return _bounds; }
    constexpr size_t getPointCount() const noexcept { return _pointCount; }
    constexpr size_t getEdgeCount() const noexcept { return _edgeCount; }
    constexpr size_t getFigureCount() const noexcept { return _figureCount; }

    // Operations
    DecompositionStatistics operator+(const DecompositionStatistics &stats) const;
    DecompositionStatistics &operator+=(const DecompositionStatistics &rhs);
};

//! @brief An object which can be used to decompose graphic artefacts into
//! partitioned paths and lines while retaining resources between operations.
class DecompositionContext
{
public:
    // Construction/Destruction
    DecompositionContext() = default;
    ~DecompositionContext() = default;

    // Accessors
    const Geom::Rect2D &getFilledBounds() const;
    const Geom::Rect2D &getClipBounds() const;

    // Operations
    void reset(const DecompositionStatistics &stats);
    Geom::DCEL::ID definePoint(const Geom::Point2D &position);
    Geom::DCEL::ID defineEdge(Geom::DCEL::ID startID, Geom::DCEL::ID endID,
                              bool isClip);
    void defineConnectedEdges(const Geom::Point2DCollectionView &points,
                              bool isClip);

    void addIntersectionLine(const Geom::LineEq2D &line);
    Geom::DCEL::ExplicitRingCollection extractFillRings();
    PartitionedPolygon partition(Geom::DCEL::ExplicitRingCollection &originalRings,
                                 bool includeIntersections);
    PartitionedPolygon partition(bool includeIntersections = false);
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    Geom::DCEL::NodeTable _nodes;
    Geom::DCEL::EdgeTable _edges;
    Geom::Rect2D _filledBounds;
    Geom::Rect2D _clipBounds;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
