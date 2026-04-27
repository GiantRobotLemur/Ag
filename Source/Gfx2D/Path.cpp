//! @file Gfx2D/Path.cpp
//! @brief The definition of an object representing one or more line segments,
//! possibly curves, creating one or more figures, possibly enclosed.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Path.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief Defines the types of line segments which can be encoded in a
//! path segment.
enum class SegmentType
{
    Polyline,
    QuadraticBezierCurve,
    CubicBezierCurve,
    Arc,
};

//! @brief An object passed around to gather statistics when simulating the
//! decomposition of a path.
class PreDecompositionStats : public DecompositionParams
{
private:
    // Internal Fields
    std::optional<Geom::Rect2D> _bounds;
    size_t _vertexCount;
    size_t _edgeCount;
    size_t _figureCount;
public:
    //! @brief Constructs an empty set of statistics from a set of
    //! decomposition parameters.
    //! @param[in] params The parameters used in gathering the statistics.
    PreDecompositionStats(const DecompositionParams &params) :
        DecompositionParams(params),
        _vertexCount(0),
        _edgeCount(0),
        _figureCount(0)
    {
    }

    // Accessors

    //! @brief Gets the statistics gathered by the object.
    DecompositionStatistics getStatistics() const
    {
        return DecompositionStatistics(_bounds.value(), _vertexCount,
                                       _edgeCount, _figureCount);
    }

    // Operations

    //! @brief Increments the count of vertices in the decomposition.
    void addVertex()
    {
        ++_vertexCount;
    }

    //! @brief Increments the count of edges in the decomposition.
    void addEdge()
    {
        ++_edgeCount;
    }

    //! @brief Increments the count of figures in the decomposition.
    void addFigure()
    {
        ++_figureCount;
    }

    //! @brief Increments the count of vertices and points by a value.
    //! @param[in] count The count of connected edges used to update statistics.
    void addConnectedVertices(size_t count)
    {
        _vertexCount += count;
        _edgeCount += count;
    }

    //! @brief Expands the calculated bounds to include a specified point.
    //! @param[in] pointOnBoundary The point to include in the bounding rectangle.
    void addBounds(const Geom::Point2D &pointOnBoundary)
    {
        if (_bounds.has_value())
            _bounds->combineTo(pointOnBoundary);
        else
            _bounds = Geom::Rect2D(pointOnBoundary);
    }

    //! @brief Expands the calculated bounds to include another rectangle.
    //! @param[in] subBounds The rectangle to add to the bounds.
    void addBounds(const Geom::Rect2D &subBounds)
    {
        if (_bounds.has_value())
            _bounds->combineTo(subBounds);
        else
            _bounds = subBounds;
    }
};

//! @brief Updates statistics based on the decomposition of a curved path segment.
//! @tparam TCurve The data type of the line segment being decomposed.
//! @param[in] curve The line segment being decomposed.
//! @param[in] stats An object defining the parameters of the decomposition and
//! to be updated with statistics.
//! @param[in] startPt The start point of the segment approximating the curve.
//! @param[in] startParam The parameter of the start point on the curve.
//! @param[in] endPt The end point of the segment approximating the curve.
//! @param[in] endParam The parameter of the end point on the curve.
template<typename TCurve>
void updateBounds(const TCurve &curve, PreDecompositionStats &stats,
                  const Geom::Point2D startPt, double startParam,
                  const Geom::Point2D endPt, double endParam)
{
    Geom::Point2D midPt = (startPt + endPt) * 0.5;
    Geom::Point2D curvePt;

    double midParam = (startParam + endParam) * 0.5;
    curvePt = curve.getPoint(midParam);

    double errorDistance = curvePt.distance(midPt);

    if (errorDistance > stats.getApproxThreadhold())
    {
        stats.addBounds(curvePt);
        stats.addVertex();
        stats.addEdge();

        // The error is still too large, split the segment into
        // two and perform a new approximation.
        updateBounds(curve, stats, startPt, startParam,
                     curvePt, midParam);

        updateBounds(curve, stats, curvePt, midParam,
                     endPt, endParam);
    }
}

//! @brief Keeps a record of a segment within a figure.
class PathSegment
{
private:
    // Internal Fields
    static constexpr uint8_t IsLargeSweep = 0x01;
    static constexpr uint8_t IsClockwise = 0x02;

    double _arcSweep;
    uint32_t _firstVertex;
    uint32_t _vertexCount;
    SegmentType _type;
    uint8_t _arcAttributes;
public:
    // Construction/Destruction

    //! @brief Constructs a segment representing a non-arc type.
    //! @param[in] type The type of segment being constructed.
    //! @param[in] firstVertex The 0-based index of the first defining vertex,
    //! assuming that the actual start of the segment is the end of the previous
    //! one or figure start point.
    //! @param[in] vertexCount The count of vertices which define this segment.
    PathSegment(SegmentType type, uint32_t firstVertex, uint32_t vertexCount = 1) :
        _arcSweep(0.0),
        _firstVertex(firstVertex),
        _vertexCount(vertexCount),
        _type(type),
        _arcAttributes(0)
    {
    }

    //! @brief Constructs a segment representing a section of the outline of an ellipse.
    //! @param[in] firstVertex The index of the first vertex.
    //! @param[in] sweepAngle The angle of the ellipse coordinate system rotated
    //! clockwise from the X axis.
    //! @param[in] isLargeSweep Use the longest sweep given the possible outline
    //! traces between the start and end points.
    //! @param[in] isClockwise Use the clockwise sweep given the possible outline
    //! trace directions between the start and end points.
    PathSegment(uint32_t firstVertex, double sweepAngle, bool isLargeSweep, bool isClockwise) :
        _arcSweep(sweepAngle),
        _firstVertex(firstVertex),
        _vertexCount(2),
        _type(SegmentType::Arc),
        _arcAttributes((isLargeSweep ? IsLargeSweep : 0) | (isClockwise ? IsClockwise : 0))
    {
        // Note: The points are:
        //   Implicit start point from previous segment
        //   Semi-major axis vector added to end point (to allow transformation)
        //   End point
        //
        // 3 points total, 2 explicit, 1 implicit.
        // Arc segments cannot be merged.
    }

    ~PathSegment() = default;

    // Accessors
    constexpr SegmentType getType() const noexcept { return _type; }
    constexpr uint32_t getFirstVertex() const noexcept { return _firstVertex; }
    constexpr uint32_t getLastVertex() const noexcept { return _firstVertex + _vertexCount - 1; }
    constexpr uint32_t getVertexCount() const noexcept { return _vertexCount; }
    constexpr double getArcSweepAngle() const noexcept { return _arcSweep; }
    constexpr bool isLargeArcSweep() const noexcept { return (_arcAttributes & IsLargeSweep) != 0; }
    constexpr bool isArcCW() const noexcept { return (_arcAttributes & IsClockwise) != 0; }

    // Operations

    //! @brief Attempts to merge the current path segment with one which is
    //! defined immediately afterwards.
    //! @param[in] nextSegment The segment to possibly merge with.
    //! @retval true The @p nextSegment was successfully merged and does not
    //! need to be explicitly added to the figure.
    //! @retval false The @p nextSegment was incompatible, no merge was performed.
    bool tryMerge(const PathSegment &nextSegment)
    {
        if ((_type == SegmentType::Arc) ||
            (_type != nextSegment._type) ||
            (nextSegment._firstVertex != (_firstVertex + _vertexCount)))
            return false;

        // This is correct given the first vertex of the next segment should be
        // the last segment of the previous one.
        _vertexCount += nextSegment._vertexCount;

        return true;
    }

    //! @brief Simulates the decomposition of the curve into line segments
    //! in order to calculate the bounds and count of vertices and edges.
    //! @param[in] stats The object defining the decomposition and to be
    //! updated with statistics.
    //! @param[in] points The collection of all points in the path.
    //! @param[in] start The pre-transformed start point of the segment.
    //! @return The transformed end point of the segment.
    Geom::Point2D simulateDecomposition(PreDecompositionStats &stats,
                                        const Geom::Point2DCollectionView &points,
                                        const Geom::Point2D &start) const
    {
        Geom::Point2DCollectionView segmentPoints = points.subset(_firstVertex, _vertexCount);

        // Add the first point on the segment.
        Geom::Point2D startPt = start;
        stats.addVertex();

        switch (_type)
        {
        case SegmentType::Polyline:
            for (const Geom::Point2D &endPt : segmentPoints)
            {
                startPt = stats.transform(endPt);

                stats.addBounds(startPt);
            }

            stats.addConnectedVertices(_vertexCount);
            break;

        case SegmentType::QuadraticBezierCurve:
            for (size_t i = 0; i < _vertexCount; i += 2)
            {
                auto curvePoints = segmentPoints.subset(i, 2);

                Geom::QuadBezierCurve2D curve(startPt,
                                              stats.transform(curvePoints[0]),
                                              stats.transform(curvePoints[1]));

                // Add a single edge in case no additional points are added
                // to approximate the curve.
                stats.addEdge();

                // Enumerate points to expand the bounds.
                updateBounds(curve, stats, startPt,
                             0.0, curve.getEnd(), 1.0);

                startPt = curve.getEnd();
            }
            break;

        case SegmentType::CubicBezierCurve:
            for (size_t i = 0; i < _vertexCount; i += 2)
            {
                auto curvePoints = segmentPoints.subset(i, 2);

                Geom::CubicBezierCurve2D curve(startPt,
                                               stats.transform(curvePoints[0]),
                                               stats.transform(curvePoints[1]),
                                               stats.transform(curvePoints[2]));

                // Add a single edge in case no additional points are added
                // to approximate the curve.
                stats.addEdge();

                // Enumerate points to expand the bounds.
                updateBounds(curve, stats, startPt, 0.0, curve.getEnd(), 1.0);

                startPt = curve.getEnd();
            }
            break;

        case SegmentType::Arc: {
            Geom::Point2D end = stats.transform(segmentPoints[1]);
            Geom::Point2D encodedRadii = stats.transform(segmentPoints[0]);
            Geom::Point2D radii = encodedRadii - end;

            Geom::Arc2D arc(startPt, end, radii, _arcSweep,
                            (_arcAttributes & IsLargeSweep) != 0,
                            (_arcAttributes & IsClockwise));

            Geom::Arc2D::Parameters arcParam(arc);

            // Add a single edge in case no additional points are added
            // to approximate the arc.
            stats.addEdge();

            // Enumerate points to expand the bounds.
            updateBounds(arcParam, stats, startPt, 0.0, end, 1.0);

        } break;

        } // switch (_type)

        return startPt;
    }

    //! @brief Decomposes the edge into points and straight line segments.
    //! @param[in] context The object to add points and line segments to.
    //! @param[in] params An object defining the decomposition.
    //! @param[in] points The collection of all points in the path.
    //! @param[in] start The pre-transformed start point of the segment.
    //! @param[in] isClip True if the edges added should be marked as
    //! clip geometry, false for fill geometry.
    //! @return The transformed end point of the segment.
    Geom::Point2D decompose(DecompositionContext &context,
                            const DecompositionParams &params,
                            const Geom::Point2DCollectionView &points,
                            const Geom::Point2D &start,
                            bool isClip) const
    {
        Geom::Point2DCollectionView segmentPoints = points.subset(_firstVertex, _vertexCount);
        Geom::Point2DCollection decomposedPoints;

        // Add the first point on the segment.
        Geom::Point2D startPt = start;
        Geom::DCEL::ID startID = context.definePoint(startPt);

        switch (_type)
        {
        case SegmentType::Polyline:
            for (const Geom::Point2D &endPt : segmentPoints)
            {
                startPt = params.transform(endPt);

                Geom::DCEL::ID endID = context.definePoint(startPt);

                context.defineEdge(startID, endID, isClip);

                // Move on to the next edge.
                startID = endID;
            }
            break;

        case SegmentType::QuadraticBezierCurve:
            for (size_t i = 0; i < _vertexCount; i += 2)
            {
                auto curvePoints = segmentPoints.subset(i, 2);

                Geom::QuadBezierCurve2D curve(startPt,
                                              params.transform(curvePoints[0]),
                                              params.transform(curvePoints[1]));

                decomposedPoints = curve.toPolyline(params.getApproxThreadhold());
                context.defineConnectedEdges(Geom::Point2DCollectionView(decomposedPoints), isClip);

                startPt = curve.getEnd();
            }
            break;

        case SegmentType::CubicBezierCurve:
            for (size_t i = 0; i < _vertexCount; i += 2)
            {
                auto curvePoints = segmentPoints.subset(i, 2);

                Geom::CubicBezierCurve2D curve(startPt,
                                               params.transform(curvePoints[0]),
                                               params.transform(curvePoints[1]),
                                               params.transform(curvePoints[2]));

                decomposedPoints = curve.toPolyline(params.getApproxThreadhold());
                context.defineConnectedEdges(decomposedPoints, isClip);

                startPt = curve.getEnd();
            }
            break;

        case SegmentType::Arc:
        {
            Geom::Point2D end = params.transform(segmentPoints[1]);
            Geom::Point2D encodedRadii = params.transform(segmentPoints[0]);
            Geom::Point2D radii = encodedRadii - end;

            Geom::Arc2D arc(startPt, end, radii, _arcSweep,
                            (_arcAttributes & IsLargeSweep) != 0,
                            (_arcAttributes & IsClockwise));

            decomposedPoints = arc.toPolyline(params.getApproxThreadhold());
            context.defineConnectedEdges(decomposedPoints, isClip);

            startPt = arc.getEnd();

        } break;

        } // switch (_type)

        return startPt;
    }
};

using SegmentDeque = std::deque<PathSegment>;
using SegmentView = ArrayView<PathSegment>;

//! @brief Keeps a record of a figure within a path being constructed.
class PathFigure
{
private:
    // Internal Fields
    uint32_t _startPoint;
    uint32_t _startSegment;
    uint32_t _segmentCount;
    bool _isClosed;
    bool _isHole;

public:
    // Construction/Destruction

    //! @brief Constructs a new, possibly incomplete, figure.
    //! @param[in] startPoint The 0-based index of the first point defining
    //! the figure.
    //! @param[in] startSegment The 0-based index of the first segment defining
    //! the figure.
    //! @param[in] isHole Indicates if the figure is a whole cut in a filled area.
    PathFigure(uint32_t startPoint, uint32_t startSegment, bool isHole) :
        _startPoint(startPoint),
        _startSegment(startSegment),
        _segmentCount(0),
        _isClosed(false),
        _isHole(isHole)
    {
    }

    ~PathFigure() = default;

    // Accessors

    //! @brief Indicates if the figure was marked as a hole or not.
    //! @retval true The figure was a hole.
    //! @retval false The figure was intended to be filled.
    constexpr bool isHole() const noexcept { return _isHole; }

    //! @brief Indicates whether the figure is complete.
    //! @retval true The figure is complete in its current state.
    //! @retval false The figure definition is not valid.
    constexpr bool isFinished() const noexcept { return _segmentCount > 0; }

    constexpr uint32_t getStartPointIndex() const noexcept { return _startPoint; }
    constexpr uint32_t getStartSegmentIndex() const noexcept { return _startSegment; }
    constexpr uint32_t getSegmentCount() const noexcept { return _segmentCount; }

    // Operations
    //! @brief Updates the figure definition.
    //! @param[in] segmentCount The count of lines defining the figure.
    //! @param[in] isClosed True if the figure has the same start and end point,
    //! false if the figure is just lines.
    void updateFigure(uint32_t segmentCount, bool isClosed)
    {
        _segmentCount = segmentCount;
        _isClosed = isClosed;
    }

    //! @brief Simulates the decomposition of the figure into line segments
    //! in order to calculate the bounds and count of vertices and edges.
    //! @param[in] stats The object defining the decomposition and to be
    //! updated with statistics.
    //! @param[in] segments The collection of all segments in the path.
    //! @param[in] points The collection of all points in the path.
    void simulateDecomposition(PreDecompositionStats &stats,
                               const SegmentView &segments,
                               const Geom::Point2DCollectionView &points) const
    {
        stats.addFigure();
        Geom::Point2D start = stats.transform(points[_startPoint]);

        SegmentView figureSegments = segments.subset(_startSegment,
                                                     _segmentCount);

        for (const PathSegment &segment : figureSegments)
        {
            start = segment.simulateDecomposition(stats, points, start);
        }
    }

    //! @brief Decomposes the figure into points and straight line segments.
    //! @param[in] context The object to add points and line segments to.
    //! @param[in] params An object defining the decomposition.
    //! @param[in] segments The collection of all segments in the path.
    //! @param[in] points The collection of all points in the path.
    //! @param[in] isClip True if the edges added should be marked as
    //! clip geometry, false for fill geometry.
    void decompose(DecompositionContext &context,
                   const DecompositionParams &params,
                   const SegmentView &segments,
                   const Geom::Point2DCollectionView &points,
                   bool isClip) const
    {
        Geom::Point2D start = params.transform(points[_startPoint]);

        SegmentView figureSegments = segments.subset(_startSegment,
                                                     _segmentCount);

        for (const PathSegment &segment : figureSegments)
        {
            start = segment.decompose(context, params, points, start, isClip);
        }
    }

    //! @brief Traces the outline of the figure and creates a new filled
    //! geometry by applying a line style.
    //! @param[in] builder The object to accumulate the figure geometry.
    //! @param[in] segments The collection of all segments in the path.
    //! @param[in] points The collection of all points in the path.
    //! @param[in] stroke The description of the line style, which must not be
    //! a "thin" line style.
    void buildOutline(PathBuilderInternal &builder,
                      const SegmentView &segments,
                      const Geom::Point2DCollectionView &points,
                      const PenSPtr &stroke) const
    {

        const Geom::Point2D &start = points[_startPoint];

        SegmentView figureSegments = segments.subset(_startSegment,
                                                     _segmentCount);

        if (_isClosed)
        {
            // TODO: Trace the first edge with stroke->getLineStartCap().
            //       Trace all except the last edges with connections defined
            //          by stroke->getJoinCap().
            //       Trace the final edge with stroke->getLineEndCap().
        }
        else
        {
            // TODO: Calculate the geometry of the join connecting the first
            //       and last edge.
            //       Trace all edges with connections defined by
            //          stroke->getJoinCap().
        }
    }
};

using FigureDeque = std::deque<PathFigure>;
using FigureView = ArrayView<PathFigure>;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which can be used to incrementally construct a Path.
class PathBuilderInternal
{
private:
    // Internal Fields
    Geom::Point2DDeque _points;
    SegmentDeque _segments;
    FigureDeque _figures;

    // Internal Functions

    //! @brief Appends a point to the path.
    //! @param[in] point The point to append.
    //! @return The index of the newly added point.
    uint32_t appendPoint(const Geom::Point2D &point)
    {
        uint32_t index = static_cast<uint32_t>(_points.size());

        _points.push_back(point);

        return index;
    }

    //! @brief Ensures that a figure is under construction.
    //! @throws OperationException If no figure is currently being defined.
    void verifyFigureActive()
    {
        if (_figures.empty() ||
            _figures.back().isFinished())
            throw OperationException("Appending to a figure when none is active.");
    }

    //! @brief Updates the active figure to consume all of the points and
    //! segments defined since its creation.
    //! @throws OperationException If no figure is currently being defined.
    void updateActiveFigure()
    {
        if (_figures.empty())
            throw OperationException("No figures are active.");

        auto &activeFigure = _figures.back();
        uint32_t segmentCount = static_cast<uint32_t>(_segments.size() -
                                                      activeFigure.getStartSegmentIndex());

        if (segmentCount != activeFigure.getSegmentCount())
        {
            const PathSegment &firstSegment = _segments[activeFigure.getStartSegmentIndex()];
            Geom::Point2D start = _points[firstSegment.getFirstVertex()];

            PathSegment &lastSegment = _segments.back();
            Geom::Point2D last = _points[lastSegment.getFirstVertex() + lastSegment.getVertexCount() - 1];

            bool isClosed = (start == last);

            activeFigure.updateFigure(segmentCount, isClosed);
        }
    }

    //! @brief Adds a segment to the figure currently being defined.
    //! @param[in] segment The segment to add.
    //! @remarks The segment may be merged with a previous one instead of
    //! being added if it is of a compatible type.
    void appendSegmentToActiveFigure(const PathSegment &segment)
    {
        if (_figures.empty())
            throw OperationException("No figures are active.");

        auto &activeFigure = _figures.back();

        // Ensure we don't merge the segment with one from a previous figure.
        if (_segments.empty() ||
            (activeFigure.getStartSegmentIndex() == _segments.size()) ||
            (_segments.back().tryMerge(segment) == false))
        {
            // Add the new segment to the active figure.
            _segments.push_back(segment);

            updateActiveFigure();
        }
    }
public:
    // Construction/Destruction
    PathBuilderInternal() = default;
    ~PathBuilderInternal() = default;

    // Accessors

    //! @brief Indicates if any possibly complete figures have been defined.
    //! @retval true At least one figure containing at least one segment has
    //! been defined.
    //! @retval false The object contains zero figures or the one figure
    //! defined has no edges.
    bool hasFigures() const
    {
        return (_figures.empty() == false) && (_figures.back().isFinished());
    }

    const Geom::Point2DDeque &getPoints() const noexcept { return _points; }
    const SegmentDeque &getSegments() const noexcept { return _segments; }
    const FigureDeque getFigures() const noexcept { return _figures; }

    // Operations

    //! @brief Removes all previous figure, segment and point definitions.
    void clear()
    {
        _points.clear();
        _segments.clear();
        _figures.clear();
    }

    //! @brief Starts a new figure.
    //! @param[in] start The position at the beginning of the first edge
    //! defining the new figure.
    //! @param[in] isHole Indicates if the figure is a whole cut in a filled area.
    void beginFigure(const Geom::Point2D &start, bool isHole)
    {
        // Remove the previous figure if it was empty.
        if ((_figures.empty() == false) &&
            (_figures.back().getSegmentCount() < 1))
        {
            _figures.pop_back();
            _points.pop_back();
        }

        uint32_t startPointId = appendPoint(start);
        _figures.emplace_back(startPointId,
                              static_cast<uint32_t>(_segments.size()),
                              isHole);
    }

    //! @brief Ensure the current figure is closed, adding a straight line
    //! segment connecting the start and end points if necessary.
    void closeFigure()
    {
        if (_figures.empty() || _figures.back().isFinished())
            return;

        PathFigure &lastFigure = _figures.back();

        if (lastFigure.getSegmentCount() > 0)
        {
            const PathSegment &firstSegment = _segments[lastFigure.getStartSegmentIndex()];
            Geom::Point2D startPoint = _points[firstSegment.getFirstVertex()];

            PathSegment &lastSegment = _segments.back();
            Geom::Point2D lastPoint = _points[lastSegment.getLastVertex()];

            if (startPoint != lastPoint)
            {
                // Add a straight line segment to close the figure.
                uint32_t endIndex = appendPoint(startPoint);
                PathSegment closingSegment(SegmentType::Polyline, endIndex, 1);

                appendSegmentToActiveFigure(closingSegment);
            }
        }
        else
        {
            // Remove the empty figure and its start point.
            _figures.pop_back();
            _points.pop_back();
        }
    }

    //! @brief Adds a straight line to the current figure.
    //! @param[in] end The point at the end of the line.
    //! @remarks The line is assumed to have started at the end of the
    //! previous line segment.
    void appendLine(const Geom::Point2D &end)
    {
        verifyFigureActive();

        uint32_t pointIndex = appendPoint(end);
        PathSegment segment(SegmentType::Polyline, pointIndex, 1);

        if (_segments.back().tryMerge(segment) == false)
        {
            _segments.push_back(segment);

            updateActiveFigure();
        }
    }

    //! @brief Adds a number of straight lines to the current figure.
    //! @param[in] points The points defining the end of each line.
    //! @remarks The first line is assumed to have started at the end of the
    //! previous line segment.
    void appendPolyline(const Geom::Point2DCollectionView &points)
    {
        verifyFigureActive();

        // Copy the points to the vertex collection.
        uint32_t pointIndex = static_cast<uint32_t>(_points.size());
        std::copy(points.begin(), points.end(), std::back_inserter(_points));

        // Create a segment encompassing all the points.
        PathSegment segment(SegmentType::Polyline, pointIndex,
                            static_cast<uint32_t>(points.getCount()));

        // Either merge of add the polyline segment.
        if (_segments.back().tryMerge(segment) == false)
        {
            _segments.push_back(segment);

            updateActiveFigure();
        }
    }

    //! @brief Adds a quadratic bezier curve to the current figure.
    //! @param[in] ctrlPt The control point defining curvature.
    //! @param[in] end The point at the end of the curve.
    void appendQuadBezier(const Geom::Point2D &ctrlPt, const Geom::Point2D &end)
    {
        verifyFigureActive();

        uint32_t pointIndex = appendPoint(ctrlPt);
        appendPoint(end);

         PathSegment segment(SegmentType::QuadraticBezierCurve, pointIndex, 2);
    }

    //! @brief Adds a cubic bezier curve to the current figure.
    //! @param[in] ctrlPt1 The first control point defining curvature.
    //! @param[in] ctrlPt2 The second control point defining curvature.
    //! @param[in] end The point at the end of the curve.
    void appendCubicBezier(const Geom::Point2D &ctrlPt1,
                           const Geom::Point2D &ctrlPt2,
                           const Geom::Point2D &end)
    {
        uint32_t pointIndex = appendPoint(ctrlPt1);
        appendPoint(ctrlPt2);
        appendPoint(end);

        _segments.emplace_back(SegmentType::CubicBezierCurve, pointIndex, 3);
    }

    //! @brief Adds an arc to the current figure.
    //! @param[in] end The end of the arc segment.
    //! @param[in] axes The radii of the ellipse relative to the X and Y
    //! axes in its local coordinate system.
    //! @param[in] angle The angle of the ellipse coordinate system rotated
    //! clockwise from the X axis.
    //! @param[in] isLargeSweep Use the longest sweep given the possible outline
    //! traces between the start and end points.
    //! @param[in] isClockwise Use the clockwise sweep given the possible outline
    //! trace directions between the start and end points.
    void appendArc(const Geom::Point2D &end, const Geom::Point2D &axes,
                   double angle, bool isLargeSweep, bool isClockwise)
    {
        Geom::Point2D axisOffset = end + axes;
        uint32_t pointIndex = appendPoint(axisOffset);
        appendPoint(end);

        _segments.emplace_back(pointIndex, angle, isLargeSweep, isClockwise);
    }
};

//! @brief A wrapper for PathBuilderInternal which give it shared
//! ownership semantics for use by external code.
class PathBuilderPrivate : public std::enable_shared_from_this<PathBuilderPrivate>
{
public:
    PathBuilderPrivate() = default;
    ~PathBuilderPrivate() = default;

    PathBuilderInternal Builder;
};

//! @brief An object which holds the immutable representation of a path.
class PathPrivate : public std::enable_shared_from_this<PathPrivate>
{
private:
    // Internal Types
    using AlignedBuffer = std::vector<uint8_t, AlignedAllocator<uint8_t, 16>>;

    // Internal Fields
    AlignedBuffer _data;
    Geom::Point2DCollectionView _points;
    SegmentView _segments;
    FigureView _figures;
    bool _hasHoles;

    // Internal Functions
    PathPrivate(const PathPrivate &) = delete;
    PathPrivate &operator=(const PathPrivate &) = delete;
public:
    //! @brief Constructs an immutable path from an incrementally created
    //! definition.
    //! @param[in] builder The builder containing the incremental definition.
    PathPrivate(const PathBuilderInternal &builder) :
        _hasHoles(false)
    {
        const auto &points = builder.getPoints();
        const auto &segments = builder.getSegments();
        const auto &figures = builder.getFigures();

        size_t pointCount = points.size();
        size_t segmentCount = segments.size();
        size_t figureCount = figures.size();
        const auto &lastFigure = figures.back();

        if (lastFigure.isFinished() == false)
        {
            // Ignore the last figure.
            pointCount = lastFigure.getStartPointIndex();
            segmentCount = lastFigure.getStartSegmentIndex();
            --figureCount;
        }

        InlineAllocator allocator;
        auto pointsField = allocator.allocateArray(pointCount, sizeof(Geom::Point2D));
        auto segmentsField = allocator.allocateArray(segmentCount, sizeof(PathSegment));
        auto figuresField = allocator.allocateArray(figureCount, sizeof(PathFigure));

        _data.resize(allocator.getSize());
        InlineInitialiser initialiser(_data.data(), _data.size());

        _points = initialiser.initialiseCollectionN<Geom::Point2D>(pointsField,
                                                                   points.begin(),
                                                                   pointCount);

        _segments =
            initialiser.initialiseCollectionN<PathSegment>(segmentsField,
                                                           segments.begin(),
                                                           segmentCount);

        _figures =
            initialiser.initialiseCollectionN<PathFigure>(figuresField,
                                                          figures.begin(),
                                                          figureCount);

        for (const auto &figure : _figures)
        {
            _hasHoles |= figure.isHole();
        }
    }

    //! @brief Simulates the decomposition of the path into line segments
    //! in order to calculate the bounds and count of vertices and edges.
    //! @param[in] stats The object defining the decomposition and to be
    //! updated with statistics.
    void simulateDecomposition(PreDecompositionStats &stats) const
    {
        for (const PathFigure &figure : _figures)
        {
            figure.simulateDecomposition(stats, _segments, _points);
        }
    }

    //! @brief Decomposes the path into points and straight line segments.
    //! @param[in] context The object to add points and line segments to.
    //! @param[in] params An object defining the decomposition.
    //! @param[in] isClip True if the edges added should be marked as
    //! clip geometry, false for fill geometry.
    void addToDecomposition(DecompositionContext &context,
                            const DecompositionParams &params,
                            bool isClip) const
    {
        for (const PathFigure &figure : _figures)
        {
            figure.decompose(context, params, _segments, _points, isClip);
        }
    }

    //! @brief Creates a path of filled figures by using tracing the figures
    //! of the current path with a specified line style.
    //! @param[in] builder The object used to accumulate the outline figures.
    //! @param[in] stroke The line style to apply. This MUST not be a "thin"
    //! line style.
    void buildOutline(PathBuilderInternal &builder, const PenSPtr &stroke) const
    {
        for (const PathFigure &figure : _figures)
        {
            figure.buildOutline(builder, _segments, _points, stroke);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
// Path Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a definition of an immutable path.
Path::Path(const std::shared_ptr<PathPrivate> &path) :
    _path(path)
{
}

//! @brief Determines if the object is bound to an underlying path.
//! @retval true The object contains a valid path.
//! @retval false The object is in an unbound state.
bool Path::isBound() const noexcept
{
    return static_cast<bool>(_path);
}

//! @brief Attempts to calculate the bounding rectangle of the path.
//! @param[in] decomposition The parameters used to decompose the path in order
//! to calculate its bounds.
//! @param[out] bounds Receives the bounds calculated from the path.
//! @retval true The object was in a bound state, bounds were calculated from
//! transformed geometry.
//! @retval false The object was not in a bound state.
bool Path::tryCalculateBounds(const DecompositionParams &decomposition,
                              Geom::Rect2D &bounds) const
{
    if (_path)
    {
        PreDecompositionStats stats(decomposition);

        _path->simulateDecomposition(stats);
        bounds = stats.getStatistics().getBounds();

        return bounds.isEmpty() == false;
    }
    else
    {
        bounds.clear();

        return false;
    }
}

//! @brief Simulates decomposition of the path into line segments.
//! @param[in] decomposition The parameters of the decomposition.
//! @return The bounds and point, edge and figure count calculated from
//! simulating the decomposition.
DecompositionStatistics Path::simulateDecomposition(const DecompositionParams &decomposition) const
{
    if (_path)
    {
        PreDecompositionStats stats(decomposition);

        _path->simulateDecomposition(stats);
        return stats.getStatistics();
    }
    else
    {
        return { };
    }
}

//! @brief Adds the geometry of the path to an object which decomposes geometry
//! into base primitives.
//! @param[in] context The context to add the geometry to.
//! @param[in] params Details of how the path should be transformed before being
//! decomposed.
//! @param[in] isClip True to indicate the geometry is used to clip other
//! geometry, false of the geometry is to be clipped.
void Path::addToDecomposition(DecompositionContext &context,
                              const DecompositionParams &params,
                              bool isClip) const
{
    if (_path)
        _path->addToDecomposition(context, params, isClip);
}

//! @brief Creates a path which traces the outline of the current path when
//! rendered with a specific line style.
//! @param[in] stroke The line style to apply.
//! @return 
Path Path::createOutlinePath(const PenSPtr &stroke)
{
    // If the line style has no thickness, the original geometry is fine.
    if (stroke->isThin())
        return *this;

    if (_path)
    {
        // Create a path builder and trace the upper/lower edges of the path.
        PathBuilderInternal builder;

        // Create figures by using the figures to create outline figures.
        _path->buildOutline(builder, stroke);

        // Construct a filled path from the outline figures created.
        return { std::make_shared<PathPrivate>(builder) };
    }
    else
    {
        return {};
    }
}

////////////////////////////////////////////////////////////////////////////////
// PathBuilder Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object used to incrementally define a graphic path.
PathBuilder::PathBuilder() :
    _builder(std::make_shared<PathBuilderPrivate>())
{
}

//! @brief Determines if the path contains no segments or figures.
//! @retval true The path contains no non-empty figures.
//! @retval false The path contains at least one figure with at least one
//! line segment.
bool PathBuilder::isEmpty() const noexcept
{
    return !_builder || _builder->Builder.getSegments().empty();
}

//! @brief Removes all figures from the builder, resetting it to an empty state.
void PathBuilder::clear()
{
    _builder->Builder.clear();
}

//! @brief Begins the definition of a new figure - set of connected line segments.
//! @param[in] start The position of the start of the first line segment.
//! @param[in] isHole Indicates if the figure is a whole cut in a filled area.
void PathBuilder::beginFigure(const Geom::Point2D &start, bool isHole /*= false*/)
{
    _builder->Builder.beginFigure(start, isHole);
}

//! @brief Adds a line to the active figure to connect its start and end point
//! if they are not already connected.
void PathBuilder::closeFigure()
{
    _builder->Builder.closeFigure();
}

//! @brief Appends a straight line to the active figure from the end of the
//! previous segment to a new point.
//! @param[in] end The end of the new line segment.
void PathBuilder::appendLine(const Geom::Point2D &end)
{
    _builder->Builder.appendLine(end);
}

//! @brief Appends a number of straight lines to the active figure from the
//! end of the previous segment.
//! @param[in] points The points the new line segments.
void PathBuilder::appendPolyline(const Geom::Point2DCollectionView &points)
{
    _builder->Builder.appendPolyline(points);
}

//! @brief Appends a quadratic bezier curve to the active figure.
//! @param[in] ctrlPt The control point which defines curvature.
//! @param[in] end The point where the curve ends.
void PathBuilder::appendQuadBezier(const Geom::Point2D &ctrlPt,
                                   const Geom::Point2D &end)
{
    _builder->Builder.appendQuadBezier(ctrlPt, end);
}

//! @brief Appends a cubic bezier curve to the active figure.
//! @param[in] ctrlPt1 The first control point which defines curvature.
//! @param[in] ctrlPt2 The second control point which defines curvature.
//! @param[in] end The point where the curve ends.
void PathBuilder::appendCubicBezier(const Geom::Point2D &ctrlPt1,
                                    const Geom::Point2D &ctrlPt2,
                                    const Geom::Point2D &end)
{
    _builder->Builder.appendCubicBezier(ctrlPt1, ctrlPt2, end);
}

//! @brief Adds an arc segment to the active figure.
//! @param[in] end The point where the arc ends.
//! @param[in] axes The radii of the ellipse relative to the X and Y
//! axes in its local coordinate system.
//! @param[in] angle The angle of the ellipse coordinate system rotated
//! clockwise from the X axis.
//! @param[in] isLargeSweep Use the longest sweep given the possible outline
//! traces between the start and end points.
//! @param[in] isClockwise Use the clockwise sweep given the possible outline
//! trace directions between the start and end points.
void PathBuilder::appendArc(const Geom::Point2D &end, const Geom::Point2D &axes,
                            double angle, bool isLargeSweep, bool isClockwise)
{
    _builder->Builder.appendArc(end, axes, angle, isLargeSweep, isClockwise);
}

//! @brief Creates an immutable path from the current state of the builder.
Path PathBuilder::createPath() const
{
    return { std::make_shared<PathPrivate>(_builder.get()->Builder) };
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

