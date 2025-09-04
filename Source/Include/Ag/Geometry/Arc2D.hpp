//! @file Ag/Geometry/Arc2D.hpp
//! @brief The declaration of a parametric line segment representing a portion
//! of an elliptical arc.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_ARC_2D_HPP__
#define __AG_GEOMETRY_ARC_2D_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Point2D.hpp"

namespace Ag {
namespace Geom {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A parametric line segment representing a portion of an elliptical arc.
class Arc2D
{
private:
    // Internal Fields
    Point2D _start;
    Point2D _end;
    Point2D _ellipseAxes;
    double _ellipseAngle;
    bool _isLargeSweep;
    bool _isClockwiseSweep;
public:
    // Public Types
    //! @brief Parameters calculated from a curve which are worth retaining for
    //! successive calls to Arc2D::getPoint().
    struct Parameters
    {
    private:
        // Internal Fields
        //! @brief The centre of the circle the arc traces in circular space.
        Point2D _circleCentre;

        //! @brief The linear transform for points in circular space to points
        //! in elliptical space.
        double _toEllipse[4];

        //! @brief The uniform radius of the circle in circular space.
        double _circleRadius;

        //! @brief The angle in radians of the start point of the arc within
        //! circular space.
        double _startAngle;

        //! @brief The angle delta in radians from the start point to the end point.
        double _angleDelta;

    public:
        // Construction/Destruction
        Parameters();
        Parameters(const Arc2D &arc);
        ~Parameters() = default;

        // Concept
        Point2D getPoint(double parameter) const;
        double getParameter(const Point2D &position) const;
        double getDistanceToPoint(const Point2D &position, double &param) const;

        // Accessors
        Point2D getCentre() const;
        Point2D getMajorAxisPoint(double yScale = 1.0) const;
        Point2D getMinorAxisPoint(double xScale = 1.0) const;
    };

    // Construction/Destruction
    Arc2D();
    Arc2D(const Point2D &start, const Point2D &end, const Point2D &axes,
          double angle, bool isLargeSweep, bool isClockwise);
    Arc2D(const Point2D &start, const Point2D &end,
          const Point2D &ellipseCentre,
          const Point2D &ellipseXRadius,
          const Point2D &ellipseYRadius,
          bool isLargeSweep, bool isClockwise);
    ~Arc2D() = default;

    // Concept
    constexpr const double *toArray() const noexcept { return _start.toArray(); }
    constexpr const Point2D &getStart() const noexcept { return _start; }
    void setStart(const Point2D &newStart) noexcept;
    constexpr Point2D getEnd() const noexcept { return _end; }
    void setEnd(const Point2D &end) noexcept;
    Point2D getPoint(double parameter) const;
    double getParameter(const Point2D &position) const;
    double getDistanceToPoint(const Point2D &pt, double &param) const;
    Point2DCollection toPolyline(double tolerance, double startParam = 0.0,
                                 double endParam = 1.0) const;

    // Accessors
    //! @brief Gets the radius of the ellipse along the Y axis before rotation.
    constexpr double getMajorRadius() noexcept { return _ellipseAxes.getY(); }
    void setMajorRadius(double yRadius) noexcept;

    //! @brief Gets the radius of the ellipse along the X axis before rotation.
    constexpr double getMinorRadius() noexcept { return _ellipseAxes.getX(); }
    void setMinorRadius(double xRadius) noexcept;

    //! @brief Gets the angle of the ellipse coordinate system rotated
    //! clockwise from the X axis.
    constexpr double getRotationAngle() noexcept { return _ellipseAngle; }

    //! @brief Determines whether to use the clockwise sweep given the two
    //! possible outline traces directions between the start and end points.
    //! @retval true The segment will trace clockwise about the ellipse from the
    //! start to the end point.
    //! @retval false The segment will trace counter-clockwise about the ellipse
    //! from the start to the end point.
    constexpr bool isClockwiseSweep() const noexcept { return _isClockwiseSweep; }
    void setClockwiseSweep(bool isCCW);

    //! @brief Determines whether to use the longest sweep given the two
    //! possible outline traces between the start and end points.
    //! @retval true The larger segment will be traced.
    //! @retval false The shorter segment will be traced.
    constexpr bool isLargeSweep() const noexcept { return _isLargeSweep; }

    void setLargeSweep(bool isLargeSweep);
};

}} // namespace Ag::Geom

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
