//! @file Gfx2D/PrimitiveGraphics.cpp
//! @brief The definitions of the concrete VectorGraphic primitives shipped
//! in the v1 Gfx2D scene-graph.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/PrimitiveGraphics.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
const std::string_view PathGraphicName("PathGraphic");
const std::string_view RectangleGraphicName("RectangleGraphic");
const std::string_view EllipseGraphicName("EllipseGraphic");
const std::string_view LineGraphicName("LineGraphic");
const std::string_view PolylineGraphicName("PolylineGraphic");

//! @brief Helper that copies the fill/stroke state of a VectorGraphic into
//! a freshly-cloned target.
template<typename TTarget, typename TSource>
void copyVectorGraphicState(TTarget &target, const TSource &source)
{
    target.setFill(source.getFill());
    target.setStroke(source.getStroke());
}

} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// PathGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
PathGraphic::PathGraphic(const Path &path) :
    _path(path)
{
}

const Path &PathGraphic::getPath() const noexcept
{
    return _path;
}

void PathGraphic::setPath(const Path &path)
{
    verifyAccess(PathGraphicName, "set path");
    _path = path;
}

GraphicArtefactSPtr PathGraphic::clone() const
{
    auto copy = std::make_shared<PathGraphic>(_path);
    copyVectorGraphicState(*copy, *this);
    return copy;
}

Path PathGraphic::lowerToPath() const
{
    return _path;
}

Geom::Rect2D PathGraphic::calculateLocalBounds() const
{
    if (!_path.isBound())
    {
        return Geom::Rect2D();
    }

    Geom::Rect2D bounds;

    if (_path.tryCalculateBounds(DecompositionParams(0.5), bounds))
    {
        return bounds;
    }

    return Geom::Rect2D();
}

////////////////////////////////////////////////////////////////////////////////
// RectangleGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
RectangleGraphic::RectangleGraphic() :
    _cornerRadius(0.0)
{
}

RectangleGraphic::RectangleGraphic(const Geom::Rect2D &rect, double cornerRadius) :
    _rect(rect),
    _cornerRadius(cornerRadius < 0.0 ? 0.0 : cornerRadius)
{
}

const Geom::Rect2D &RectangleGraphic::getRect() const noexcept
{
    return _rect;
}

void RectangleGraphic::setRect(const Geom::Rect2D &rect)
{
    verifyAccess(RectangleGraphicName, "set rect");
    _rect = rect;
}

double RectangleGraphic::getCornerRadius() const noexcept
{
    return _cornerRadius;
}

void RectangleGraphic::setCornerRadius(double radius)
{
    verifyAccess(RectangleGraphicName, "set corner radius");
    _cornerRadius = (radius < 0.0) ? 0.0 : radius;
}

GraphicArtefactSPtr RectangleGraphic::clone() const
{
    auto copy = std::make_shared<RectangleGraphic>(_rect, _cornerRadius);
    copyVectorGraphicState(*copy, *this);
    return copy;
}

Path RectangleGraphic::lowerToPath() const
{
    if (_rect.isEmpty())
    {
        return Path();
    }

    PathBuilder builder;

    const double x0 = _rect.getMinimumX();
    const double y0 = _rect.getMinimumY();
    const double x1 = _rect.getMaximumX();
    const double y1 = _rect.getMaximumY();
    const double w = _rect.getWidth();
    const double h = _rect.getHeight();
    double r = _cornerRadius;
    double maxR = std::min(w, h) * 0.5;

    if (r > maxR)
    {
        r = maxR;
    }

    if (r <= 0.0)
    {
        builder.beginFigure(Geom::Point2D(x0, y0));
        builder.appendLine(Geom::Point2D(x1, y0));
        builder.appendLine(Geom::Point2D(x1, y1));
        builder.appendLine(Geom::Point2D(x0, y1));
        builder.closeFigure();
    }
    else
    {
        // Rounded rectangle traced clockwise starting at the top edge after
        // the top-left corner radius.
        builder.beginFigure(Geom::Point2D(x0 + r, y0));
        builder.appendLine(Geom::Point2D(x1 - r, y0));
        builder.appendArc(Geom::Point2D(x1, y0 + r),
                          Geom::Point2D(r, r), 0.0, false, true);
        builder.appendLine(Geom::Point2D(x1, y1 - r));
        builder.appendArc(Geom::Point2D(x1 - r, y1),
                          Geom::Point2D(r, r), 0.0, false, true);
        builder.appendLine(Geom::Point2D(x0 + r, y1));
        builder.appendArc(Geom::Point2D(x0, y1 - r),
                          Geom::Point2D(r, r), 0.0, false, true);
        builder.appendLine(Geom::Point2D(x0, y0 + r));
        builder.appendArc(Geom::Point2D(x0 + r, y0),
                          Geom::Point2D(r, r), 0.0, false, true);
        builder.closeFigure();
    }

    return builder.createPath();
}

Geom::Rect2D RectangleGraphic::calculateLocalBounds() const
{
    return _rect;
}

////////////////////////////////////////////////////////////////////////////////
// EllipseGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
EllipseGraphic::EllipseGraphic() :
    _radiusX(0.0),
    _radiusY(0.0)
{
}

EllipseGraphic::EllipseGraphic(const Geom::Point2D &centre,
                               double radiusX, double radiusY) :
    _centre(centre),
    _radiusX(radiusX < 0.0 ? 0.0 : radiusX),
    _radiusY(radiusY < 0.0 ? 0.0 : radiusY)
{
}

const Geom::Point2D &EllipseGraphic::getCentre() const noexcept
{
    return _centre;
}

void EllipseGraphic::setCentre(const Geom::Point2D &centre)
{
    verifyAccess(EllipseGraphicName, "set centre");
    _centre = centre;
}

double EllipseGraphic::getRadiusX() const noexcept { return _radiusX; }
double EllipseGraphic::getRadiusY() const noexcept { return _radiusY; }

void EllipseGraphic::setRadii(double radiusX, double radiusY)
{
    verifyAccess(EllipseGraphicName, "set radii");
    _radiusX = (radiusX < 0.0) ? 0.0 : radiusX;
    _radiusY = (radiusY < 0.0) ? 0.0 : radiusY;
}

GraphicArtefactSPtr EllipseGraphic::clone() const
{
    auto copy = std::make_shared<EllipseGraphic>(_centre, _radiusX, _radiusY);
    copyVectorGraphicState(*copy, *this);
    return copy;
}

Path EllipseGraphic::lowerToPath() const
{
    if (_radiusX <= 0.0 || _radiusY <= 0.0)
    {
        return Path();
    }

    PathBuilder builder;

    // Two SVG-style elliptical arcs traced clockwise, starting at the
    // rightmost point.
    Geom::Point2D right(_centre.getX() + _radiusX, _centre.getY());
    Geom::Point2D left (_centre.getX() - _radiusX, _centre.getY());
    Geom::Point2D axes(_radiusX, _radiusY);

    builder.beginFigure(right);
    builder.appendArc(left,  axes, 0.0, false, true);
    builder.appendArc(right, axes, 0.0, false, true);
    builder.closeFigure();

    return builder.createPath();
}

Geom::Rect2D EllipseGraphic::calculateLocalBounds() const
{
    if (_radiusX <= 0.0 || _radiusY <= 0.0)
    {
        return Geom::Rect2D();
    }

    return Geom::Rect2D(_centre.getX() - _radiusX,
                        _centre.getY() - _radiusY,
                        _centre.getX() + _radiusX,
                        _centre.getY() + _radiusY);
}

////////////////////////////////////////////////////////////////////////////////
// LineGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
LineGraphic::LineGraphic(const Geom::Point2D &start, const Geom::Point2D &end) :
    _start(start),
    _end(end)
{
}

const Geom::Point2D &LineGraphic::getStart() const noexcept { return _start; }
const Geom::Point2D &LineGraphic::getEnd() const noexcept   { return _end; }

void LineGraphic::setStart(const Geom::Point2D &start)
{
    verifyAccess(LineGraphicName, "set start");
    _start = start;
}

void LineGraphic::setEnd(const Geom::Point2D &end)
{
    verifyAccess(LineGraphicName, "set end");
    _end = end;
}

GraphicArtefactSPtr LineGraphic::clone() const
{
    auto copy = std::make_shared<LineGraphic>(_start, _end);
    copyVectorGraphicState(*copy, *this);
    return copy;
}

Path LineGraphic::lowerToPath() const
{
    PathBuilder builder;
    builder.beginFigure(_start);
    builder.appendLine(_end);
    return builder.createPath();
}

Geom::Rect2D LineGraphic::calculateLocalBounds() const
{
    if (_start == _end)
    {
        return Geom::Rect2D();
    }

    return Geom::Rect2D(_start, _end);
}

////////////////////////////////////////////////////////////////////////////////
// PolylineGraphic Member Definitions
////////////////////////////////////////////////////////////////////////////////
PolylineGraphic::PolylineGraphic() :
    _isClosed(false)
{
}

PolylineGraphic::PolylineGraphic(Geom::Point2DCollection points, bool isClosed) :
    _points(std::move(points)),
    _isClosed(isClosed)
{
}

const Geom::Point2DCollection &PolylineGraphic::getPoints() const noexcept
{
    return _points;
}

void PolylineGraphic::setPoints(Geom::Point2DCollection points)
{
    verifyAccess(PolylineGraphicName, "set points");
    _points = std::move(points);
}

bool PolylineGraphic::isClosed() const noexcept
{
    return _isClosed;
}

void PolylineGraphic::setClosed(bool isClosed)
{
    verifyAccess(PolylineGraphicName, "set closed");
    _isClosed = isClosed;
}

GraphicArtefactSPtr PolylineGraphic::clone() const
{
    auto copy = std::make_shared<PolylineGraphic>(_points, _isClosed);
    copyVectorGraphicState(*copy, *this);
    return copy;
}

Path PolylineGraphic::lowerToPath() const
{
    if (_points.size() < 2)
    {
        return Path();
    }

    PathBuilder builder;
    builder.beginFigure(_points.front());

    for (size_t i = 1; i < _points.size(); ++i)
    {
        builder.appendLine(_points[i]);
    }

    if (_isClosed)
    {
        builder.closeFigure();
    }

    return builder.createPath();
}

Geom::Rect2D PolylineGraphic::calculateLocalBounds() const
{
    if (_points.empty())
    {
        return Geom::Rect2D();
    }

    return Geom::Rect2D(_points.data(), _points.size());
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
