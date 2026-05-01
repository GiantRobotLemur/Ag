//! @file Ag/Gfx2D/PrimitiveGraphics.hpp
//! @brief The declarations of the concrete VectorGraphic primitives shipped
//! in the v1 Gfx2D scene-graph: PathGraphic, RectangleGraphic, EllipseGraphic,
//! LineGraphic and PolylineGraphic.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_PRIMITIVE_GRAPHICS_HPP__
#define __GFX_2D_PRIMITIVE_GRAPHICS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Graphic.hpp"
#include "Path.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A scene-graph primitive whose geometry is an explicit @c Path.
class PathGraphic : public VectorGraphic
{
public:
    PathGraphic() = default;
    explicit PathGraphic(const Path &path);

    const Path &getPath() const noexcept;
    void setPath(const Path &path);

    virtual GraphicArtefactSPtr clone() const override;

protected:
    virtual Path lowerToPath() const override;
    virtual Geom::Rect2D calculateLocalBounds() const override;

private:
    Path _path;
};

using PathGraphicSPtr = std::shared_ptr<PathGraphic>;

//! @brief An axis-aligned rectangle, optionally with rounded corners.
class RectangleGraphic : public VectorGraphic
{
public:
    RectangleGraphic();
    explicit RectangleGraphic(const Geom::Rect2D &rect, double cornerRadius = 0.0);

    const Geom::Rect2D &getRect() const noexcept;
    void setRect(const Geom::Rect2D &rect);
    double getCornerRadius() const noexcept;
    void setCornerRadius(double radius);

    virtual GraphicArtefactSPtr clone() const override;

protected:
    virtual Path lowerToPath() const override;
    virtual Geom::Rect2D calculateLocalBounds() const override;

private:
    Geom::Rect2D _rect;
    double       _cornerRadius;
};

using RectangleGraphicSPtr = std::shared_ptr<RectangleGraphic>;

//! @brief An ellipse defined by a centre point and X / Y radii.
class EllipseGraphic : public VectorGraphic
{
public:
    EllipseGraphic();
    EllipseGraphic(const Geom::Point2D &centre, double radiusX, double radiusY);

    const Geom::Point2D &getCentre() const noexcept;
    void setCentre(const Geom::Point2D &centre);
    double getRadiusX() const noexcept;
    double getRadiusY() const noexcept;
    void setRadii(double radiusX, double radiusY);

    virtual GraphicArtefactSPtr clone() const override;

protected:
    virtual Path lowerToPath() const override;
    virtual Geom::Rect2D calculateLocalBounds() const override;

private:
    Geom::Point2D _centre;
    double        _radiusX;
    double        _radiusY;
};

using EllipseGraphicSPtr = std::shared_ptr<EllipseGraphic>;

//! @brief A single straight line segment between two points. Stroke-only;
//! any fill brush is ignored.
class LineGraphic : public VectorGraphic
{
public:
    LineGraphic() = default;
    LineGraphic(const Geom::Point2D &start, const Geom::Point2D &end);

    const Geom::Point2D &getStart() const noexcept;
    const Geom::Point2D &getEnd() const noexcept;
    void setStart(const Geom::Point2D &start);
    void setEnd(const Geom::Point2D &end);

    virtual GraphicArtefactSPtr clone() const override;

protected:
    virtual Path lowerToPath() const override;
    virtual Geom::Rect2D calculateLocalBounds() const override;

private:
    Geom::Point2D _start;
    Geom::Point2D _end;
};

using LineGraphicSPtr = std::shared_ptr<LineGraphic>;

//! @brief A connected sequence of straight line segments. When @c isClosed
//! is true the figure is closed and may be filled; otherwise it is treated
//! as an open polyline (stroke only).
class PolylineGraphic : public VectorGraphic
{
public:
    PolylineGraphic();
    explicit PolylineGraphic(Geom::Point2DCollection points, bool isClosed = false);

    const Geom::Point2DCollection &getPoints() const noexcept;
    void setPoints(Geom::Point2DCollection points);
    bool isClosed() const noexcept;
    void setClosed(bool isClosed);

    virtual GraphicArtefactSPtr clone() const override;

protected:
    virtual Path lowerToPath() const override;
    virtual Geom::Rect2D calculateLocalBounds() const override;

private:
    Geom::Point2DCollection _points;
    bool                    _isClosed;
};

using PolylineGraphicSPtr = std::shared_ptr<PolylineGraphic>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
