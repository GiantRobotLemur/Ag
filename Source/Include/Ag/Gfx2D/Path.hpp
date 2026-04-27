//! @file Ag/Gfx2D/Path.hpp
//! @brief The declaration of an object representing one or more line segments,
//! possibly curves, creating one or more figures, possibly enclosed.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_PATH_HPP__
#define __GFX_2D_PATH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry.hpp"
#include "DecompositionContext.hpp"
#include "Pen.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class PathBuilderInternal;
class PathBuilderPrivate;
class PathPrivate;

//! @brief An object representing one or more line segments, possibly curves,
//! creating one or more figures, possibly enclosed.
class Path
{
public:
    // Construction/Destruction
    Path() = default;
    Path(const std::shared_ptr<PathPrivate> &path);
    ~Path() = default;

    // Accessors
    bool isBound() const noexcept;

    // Operations
    bool tryCalculateBounds(const DecompositionParams &decomposition,
                            Geom::Rect2D &bounds) const;

    DecompositionStatistics simulateDecomposition(const DecompositionParams &decomposition) const;

    void addFillToDecomposition(DecompositionContext &context,
                                const DecompositionParams &params,
                                bool isClip) const;
    void addOutlineToDecomposition(DecompositionContext &context,
                                   const DecompositionParams &params,
                                   const PenSPtr &stroke) const;
private:
    // Internal Fields
    std::shared_ptr<PathPrivate> _path;
};

//! @brief Incrementally defines a path.
class PathBuilder
{
public:
    // Construction/Destruction
    PathBuilder();
    ~PathBuilder() = default;

    // Accessors
    bool isEmpty() const noexcept;

    // Operations
    void clear();
    void beginFigure(const Geom::Point2D &start, bool isHole = false);
    void closeFigure();
    void appendLine(const Geom::Point2D &end);
    void appendPolyline(const Geom::Point2DCollectionView &points);
    void appendQuadBezier(const Geom::Point2D &ctrlPt, const Geom::Point2D &end);
    void appendCubicBezier(const Geom::Point2D &ctrlPt1, const Geom::Point2D &ctrlPt2,
                           const Geom::Point2D &end);
    void appendArc(const Geom::Point2D &end, const Geom::Point2D &axes,
                   double angle, bool isLargeSweep, bool isClockwise);

    Path createPath() const;
private:
    // Internal Fields
    std::shared_ptr<PathBuilderPrivate> _builder;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
