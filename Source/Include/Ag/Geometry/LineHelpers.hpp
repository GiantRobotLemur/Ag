//! @file Ag/Geometry/LineHelpers.hpp
//! @brief The declaration of template functions useful for manipulating line
//! segments and curves.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_GEOMETRY_LINE_HELPERS_HPP__
#define __AG_GEOMETRY_LINE_HELPERS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <vector>

#include "Point2D.hpp"

namespace Ag {
namespace Geom {
namespace Line {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
using ParamCollection = std::vector<double>;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure representing a point on a parametric line.
struct ParamPoint
{
    Point2D LinePoint;
    double Param;

    //! @brief Constructs an empty parametrized point.
    ParamPoint() :
        Param(0)
    {
    }

    //! @brief Constructs a parametrized point initialise from a parametric line.
    //! @tparam TLine The data type of the parametric line, such as LineSeg2 or
    //! QuadBezierCurve2D.
    //! @param[in] line The line to calculate the position on.
    //! @param[in] param The parameter defining the position on the line to
    //! update with.
    template<typename TLine> ParamPoint(const TLine &line, double param) :
        LinePoint(line.getPoint(param)),
        Param(param)
    {
    }

    //! @brief Sets the point by calculating a position on a parametric line.
    //! @tparam TLine The data type of the parametric line, such as LineSeg2 or
    //! QuadBezierCurve2D.
    //! @param[in] line The line to calculate the position on.
    //! @param[in] param The parameter defining the position on the line to
    //! update with.
    template<typename TLine> void setPoint(const TLine &line, double param)
    {
        Param = param;
        LinePoint = line.getPoint(param);
    }

    //! @brief Performs the less-than comparison based on the line parameter.
    //! @param[in] rhs The parameterized point to compare against.
    //! @retval true If the current object as a lower Param value.
    //! @retval false If the current object has a greater or equal Param value
    //! to that of @p rhs.
    bool operator<(const ParamPoint &rhs) const
    {
        return Param < rhs.Param;
    }
};

// An alias for a collection of points on a parametric line.
using ParamPointCollection = std::deque<ParamPoint>;

//! @brief A structure representing a point on a parametric line and its
//! distance to another target point.
struct MeasuredPoint : ParamPoint
{
    double DistanceToTarget;

    //! @brief Constructs an empty measured parametrized point.
    MeasuredPoint() :
        DistanceToTarget(0)
    {
    }

    //! @brief Updates the object with a new point and distance to target.
    //! @tparam TLine The data type of the parametric line, such as LineSeg2 or
    //! QuadBezierCurve2D.
    //! @param[in] line The line to calculate the position on.
    //! @param[in] newParam The parameter defining the position on the line to
    //! update with.
    //! @param[in] target The point to measure the distance to from the newly
    //! calculated point on @p line.
    //! @return The new distance from the point on @p line to @p target.
    template<typename TLine>
    double updatePoint(const TLine &line, double newParam, const Point2D &target)
    {
        Param = newParam;
        LinePoint = line.getPoint(newParam);
        DistanceToTarget = LinePoint.distance(target);

        return DistanceToTarget;
    }
};

//! @brief Context used in the recursive simplification of a curve into a polyline.
template<typename TLine>
struct SimplifyContext
{
    TLine Line;
    std::deque<ParamPoint> Points;
    double Tolerance;
    bool IsReversed;

    //! @brief Creates an context object ready to be reset for a new curve.
    SimplifyContext() :
        Tolerance(1.0),
        IsReversed(false)
    {
    }

    //! @brief Adds a new point to the simplification.
    //! @param[in] param The parameter of the point on the curve to add.
    //! @return The index of the newly added point in the Points collection.
    size_t addPoint(double param)
    {
        size_t index = Points.size();
        Points.emplace_back(Line, param);

        return index;
    }

    //! @brief Adds a new point to approximate the curve.
    //! @param[in] param The parameter of the point to add.
    //! @param[in] approx The approximation point on the polyline being created.
    //! @param[out] addedIndex Receives the index of the newly added point in
    //! the Points collection.
    //! @return The distance from the newly added point to @p approx.
    double addApproxPoint(double param, const Point2D &approx, size_t &addedIndex)
    {
        addedIndex = Points.size();
        Points.emplace_back(Line, param);

        return Points.back().LinePoint.distance(approx);
    }

    //! @brief Prepares for a new curve decomposition.
    //! @param[in] line The curve to approximate.
    //! @param[in] tolerance The maximum distance allowed between the
    //! approximation and the actual curve.
    //! @param[in] startParam The parameter of the first point on the
    //! curve to appear on the polyline.
    //! @param[in] endParam The parameter of the last point on the curve to
    //! appear on the polyline.
    void reset(const TLine &line, double tolerace,
               double startParam, double endParam)
    {
        Line = line;
        Points.clear();
        Tolerance = std::abs(tolerace);
        IsReversed = (endParam < startParam);

        Points.emplace_back(line, startParam);
        Points.emplace_back(line, endParam);
    }

    //! @brief Sorts the points once they have been accumulated.
    void completeDecompostion()
    {
        if (IsReversed)
        {
            // Sort the points into reverse order.
            std::sort(Points.begin(), Points.end(),
                      ReverseParamPointCompare());
        }
        else
        {
            // Sort the points by their parameter values.
            std::sort(Points.begin(), Points.end());
        }
    }
};

//! @brief A comparer of ParamPoint items which orders ParamPoints in
//! descending order of their parameter values.
struct ReverseParamPointCompare
{
    bool operator()(const ParamPoint &lhs, const ParamPoint &rhs) const
    {
        return rhs.Param < lhs.Param;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////
//! @brief Finds the parameter of the nearest point on a parametric line to a
//! specified point using successive approximation.
//! @tparam The data type of the parametric line, such as LineSeg2 or
//! QuadBezierCurve2D.
//! @param[in] line The line to find the nearest point.
//! @param[in] point The point to track in relation to @p line.
//! @param[in] startParam The parameter on @p line to start searching from.
//! @param[in] endParam The parameter on @p line to not search beyond.
//! @return The parameter value, 0.0 to 1.0 of the point on @p line which is
//! closest to @p point.
template<typename TLine>
double findNearestPointParam(const TLine &line, const Point2D &point,
                             double startParam, double endParam)
{
    // The parameter values are fixed in the domain 0.0 to 1.0.
    const NumericDomain &domain = NumericDomain::UnsignedScalar;

    MeasuredPoint earliest;
    MeasuredPoint latest;
    MeasuredPoint midPoint;

    double delta = std::abs(endParam - startParam);
    double step = delta * 0.5;
    auto paramRange = std::minmax(startParam, endParam);
    earliest.updatePoint(line, paramRange.first, point);
    latest.updatePoint(line, paramRange.second, point);

    do
    {
        midPoint.updatePoint(line, earliest.Param + step, point);

        if (earliest.DistanceToTarget < latest.DistanceToTarget)
        {
            delta = std::abs(midPoint.Param - latest.Param);
            latest = midPoint;
        }
        else
        {
            delta = std::abs(midPoint.Param - earliest.Param);
            earliest = midPoint;
        }

        step *= 0.5;

    } while (domain.isNearZero(delta) == false);

    // Use the parameter of the closest point.
    if (earliest.DistanceToTarget < midPoint.DistanceToTarget)
        return earliest.Param;
    else if (latest.DistanceToTarget < midPoint.DistanceToTarget)
        return latest.Param;
    else
        return midPoint.Param;
}

//! @brief An internal function which recursively de-composes a curve
//! down into a polyline.
//! @param[in] context The context of the simplification process.
//! @param[in] line The line being converted to a polyline.
//! @param startPtIndex The index of the point in the Points collection
//! which is at the start of the approximating line segment.
//! @param endPtIndex The index of the point in the Points collection
//! which is at the end of the approximating line segment.
template<typename TLine>
void simplifyLineRecursive(SimplifyContext<TLine> &context,
                           size_t startPtIndex, size_t endPtIndex)
{
    const ParamPoint &startPt = context.Points[startPtIndex];
    const ParamPoint &endPt = context.Points[endPtIndex];

    const Point2D approxMidPt = (startPt.LinePoint + endPt.LinePoint) * 0.5;

    size_t midPtIndex;

    if (context.addApproxPoint((startPt.Param + endPt.Param) * 0.5,
                               approxMidPt, midPtIndex) < context.Tolerance)
    {
        // There is no need to define the mid-point.
        context.Points.pop_back();
    }
    else
    {
        simplifyLineRecursive(context, startPtIndex, midPtIndex);
        simplifyLineRecursive(context, midPtIndex, endPtIndex);
    }
}

//! @brief Decomposes a curve into a polyline by calculating the parameters
//! of approximation points on the curve.
//! @tparam TLine The data type of the line segment to decompose.
//! @param[in] line The line segment to decompose.
//! @param[in] tolerance The maximum distance allowed between the
//! approximation and the actual curve.
//! @param[in] startParam The parameter of the first point on the
//! curve to appear on the polyline.
//! @param[in] endParam The parameter of the last point on the curve to
//! appear on the polyline.
//! @return A collection of parameters of points on @p line which
//! can be used to approximate the curve into a polyline with the
//! specified level of accuracy.
template<typename TLine>
ParamCollection simplifyLineParams(const TLine &line, double tolerance,
                                   double startParam, double endParam)
{
    if (startParam == endParam)
    {
        return { startParam, endParam };
    }

    SimplifyContext<TLine> context;
    context.reset(line, tolerance, startParam, endParam);

    simplifyLineRecursive(context, 0, 1);

    context.completeDecompostion();

    ParamCollection params;
    ensureCapacity(params, context.Points.size());

    for (const ParamPoint &point : context.Points)
    {
        params.push_back(point.Param);
    }

    return params;
}

//! @brief Calculates a polyline simplification of a curve.
//! @tparam TLine The data type of the line segment to decompose.
//! @param[in] line The line segment to decompose.
//! @param[in] tolerance The maximum distance allowed between the
//! approximation and the actual curve.
//! @param[in] startParam The parameter of the first point on the
//! curve to appear on the polyline.
//! @param[in] endParam The parameter of the last point on the curve to
//! appear on the polyline.
//! @return A collection of points on @p line which approximate the curve as
//! a polyline with the specified level of accuracy.
template<typename TLine>
Point2DCollection simplifyLinePoints(const TLine &line, double tolerance,
                                     double startParam, double endParam)
{
    if (startParam == endParam)
    {
        Point2D singlePoint = line.getPoint(startParam);

        return { singlePoint, singlePoint };
    }

    SimplifyContext<TLine> context;
    context.reset(line, tolerance, startParam, endParam);

    simplifyLineRecursive(context, 0, 1);

    context.completeDecompostion();

    Point2DCollection points;
    ensureCapacity(points, context.Points.size());

    for (const ParamPoint &point : context.Points)
    {
        points.push_back(point.LinePoint);
    }

    return points;
}

}}} // namespace Ag::Geom::Line

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
