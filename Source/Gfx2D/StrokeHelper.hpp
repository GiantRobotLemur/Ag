//! @file Gfx2D/StrokeHelper.hpp
//! @brief The declaration of an internal helper which expands a stroked path
//! into one or more closed offset polygons that can be emitted as fill
//! geometry through a DecompositionContext.
//! @author GiantRobotLemur@na-se.co.uk and Claude Code
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_STROKE_HELPER_HPP__
#define __GFX_2D_STROKE_HELPER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "Ag/Geometry.hpp"
#include "Ag/Gfx2D/Pen.hpp"
#include "DecompositionContext.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Expands stroked path geometry into closed offset polygons that are
//! emitted to a DecompositionContext as fill geometry.
//!
//! The StrokeHelper accepts the same primitive types as PathBuilder (lines,
//! quadratic and cubic Beziers and elliptical arcs). Each primitive is
//! flattened in transformed (display) space using the tolerance from the
//! DecompositionParams. When endFigure() is called the accumulated polyline
//! is offset by half the pen thickness on each side and the start, end and
//! join geometry is filled in according to the Pen settings. Dashed pens
//! produce one open sub-stroke per dash, each with start and end caps using
//! the pen's dash cap style.
class StrokeHelper
{
public:
    // Construction/Destruction
    StrokeHelper(DecompositionContext &context,
            const DecompositionParams &params,
            const Pen &pen);
    ~StrokeHelper() = default;

    // Operations
    void beginFigure(const Geom::Point2D &start);
    void appendLine(const Geom::Point2D &end);
    void appendQuadBezier(const Geom::Point2D &ctrl,
                          const Geom::Point2D &end);
    void appendCubicBezier(const Geom::Point2D &ctrl1,
                           const Geom::Point2D &ctrl2,
                           const Geom::Point2D &end);
    void appendArc(const Geom::Point2D &end, const Geom::Point2D &axes,
                   double rotation, bool isLargeSweep, bool isClockwise);
    void endFigure(bool isClosed);

private:
    // Internal Functions
    void appendPoint(const Geom::Point2D &point);
    void emitSolid(bool isClosed);
    void emitDashed(bool isClosed);
    void emitOpenStroke(size_t firstVertex, size_t lastVertex,
                        EndCap startCap, EndCap endCap);
    void emitClosedAnnulus();
    Geom::Point2D pointAtArcLength(double targetLength,
                                   size_t &edgeHint) const;

    // Internal Fields
    DecompositionContext &_context;
    const DecompositionParams &_params;
    const Pen &_pen;

    Geom::Point2DDeque _vertices;
    std::vector<double> _cumulativeLength;
    double _halfWidth;
    double _tolerance;
    bool _figureActive;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
