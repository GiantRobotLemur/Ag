//! @file WriteGlyphGeometry/GlyphWriter.cpp
//! @brief The definition of an object which simplifies and outputs the outline
//! of a glyph as literal C++ data values.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "GlyphWriter.hpp"

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
using Figure = TTPOLYGONHEADER;
using Curve = TTPOLYCURVE;
using FigurePtr = const Figure *;
using CurvePtr = const Curve *;
using IndexRange = std::pair<uint32_t, uint32_t>;
using IndexRangeCollection = std::vector<IndexRange>;

struct PointD
{
    double X, Y;

    PointD() : X(0.0), Y(0.0) {}
    PointD(double x, double y) : X(x), Y(y) {}

    bool operator==(const PointD &rhs) const { return (X == rhs.X) && (Y == rhs.Y); }
    PointD operator+(const PointD &rhs) const { return PointD(X + rhs.X, Y + rhs.Y); }
    PointD operator-(const PointD &rhs) const { return PointD(X - rhs.X, Y - rhs.Y); }
    PointD operator*(const PointD &rhs) const { return PointD(X * rhs.X, Y * rhs.Y); }
    PointD operator/(const PointD &rhs) const { return PointD(X / rhs.X, Y / rhs.Y); }
    PointD operator*(double rhs) const { return PointD(X * rhs, Y * rhs); }
    PointD operator/(double rhs) const { return PointD(X / rhs, Y / rhs); }
    PointD &operator+=(const PointD &rhs) { X += rhs.X; Y += rhs.Y; return *this; }
    double distance(const PointD &rhs) const
    {
        double dX = X - rhs.X;
        double dY = Y - rhs.Y;

        return std::sqrt((dX * dX) + (dY * dY));
    }
};

using PointCollection = std::vector<PointD>;

struct ParamPoint
{
    PointD Position;
    double Parameter;

    ParamPoint() : Parameter(0.0) {}
    ParamPoint(const PointD &pos, double param) : Position(pos), Parameter(param) {}

    bool operator<(const ParamPoint &rhs) const
    {
        return Parameter < rhs.Parameter;
    }
};

using ParamPointCollection = std::vector<ParamPoint>;

class ConversionContext
{
private:
    PointD _scale;
    double _tolerance;
public:
    ConversionContext(double scaleX, double scaleY, double tolerance) :
        _scale(scaleX / 0x10000, scaleY / 0x10000),
        _tolerance(tolerance)
    {
    }

    double getTolerance() const { return _tolerance; }

    PointD convert(const POINTFX &pt) const
    {
        int32_t originalX = *reinterpret_cast<const int32_t *>(&pt.x);
        int32_t originalY = *reinterpret_cast<const int32_t *>(&pt.y);

        return PointD(originalX * _scale.X, originalY * _scale.Y);
    }
};

class CurveParams
{
private:
    PointD _start;
    PointD _end;
    double _threshold;
public:
    CurveParams(const PointD &start, const PointD &end, double threshold) :
        _start(start),
        _end(end),
        _threshold(threshold)
    {
    }

    const PointD &getStart() const { return _start; }
    const PointD &getEnd() const { return _end; }
    double getThreashold() const { return _threshold; }

    virtual PointD getPoint(double param) const = 0;
};

class QuadraticCurveParams : public CurveParams
{
private:
    PointD _ctrlPoint;

public:
    QuadraticCurveParams(const PointD &start, const PointD &end,
                         const PointD &ctrl, double threshold) :
        CurveParams(start, end, threshold),
        _ctrlPoint(ctrl)
    {
    }

    virtual PointD getPoint(double param) const override
    {
        PointD pt = (getStart() - (_ctrlPoint * 2.0) + getEnd()) * (param * param);
        pt += ((_ctrlPoint * 2.0) - (getStart() * 2.0)) * param;
        pt += getStart();

        return pt;
    }
};

class CubicCurveParams : public CurveParams
{
private:
    PointD _startCtrlPoint;
    PointD _endCtrlPoint;

public:
    CubicCurveParams(const PointD &start, const PointD &end,
                     const PointD &startCtrl, const PointD &endCtrl,
                     double threshold) :
        CurveParams(start, end, threshold),
        _startCtrlPoint(startCtrl),
        _endCtrlPoint(endCtrl)
    {
    }

    virtual PointD getPoint(double param) const override
    {
        double reverseParam = 1.0 - param;
        double reverseParamSq = reverseParam * reverseParam;
        double paramSq = param * param;

        PointD pt = getStart() * (reverseParamSq * reverseParam);
        pt += _startCtrlPoint * ((reverseParamSq * 3.0) * param);
        pt += _endCtrlPoint * ((reverseParam * 3.0) * paramSq);
        pt += getEnd() * (paramSq * param);

        return pt;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename U> size_t getOffset(const T *base, const U *interior)
{
    return reinterpret_cast<uintptr_t>(interior) - reinterpret_cast<uintptr_t>(base);
}

template<typename T, typename U> const T *getPtr(const U *base, size_t offset)
{
    return reinterpret_cast<const T *>(reinterpret_cast<const uint8_t *>(base) + offset);
}

template<typename T> void reserveExtra(std::vector<T> &collection, size_t extra)
{
    size_t required = collection.size() + extra;

    if (collection.capacity() < required)
        collection.reserve(required);
}

void recursiveInterpolate(const CurveParams &curve,
                          ParamPointCollection &points,
                          size_t startPtIndex, size_t endPtIndex)
{
    const auto &start = points[startPtIndex];
    const auto &end = points[endPtIndex];

    PointD approxMidPt = (start.Position + end.Position) * 0.5;
    double midParam = (start.Parameter + end.Parameter) * 0.5;

    PointD actualMidPt = curve.getPoint(midParam);

    double delta = actualMidPt.distance(approxMidPt);

    if (delta > curve.getThreashold())
    {
        size_t midIndex = points.size();
        points.emplace_back(actualMidPt, midParam);
        recursiveInterpolate(curve, points, startPtIndex, midIndex);
        recursiveInterpolate(curve, points, midIndex, endPtIndex);
    }
}

void interpolateCurve(PointCollection &vertices,
                      ParamPointCollection &curveCache,
                      const CurveParams &curve)
{
    curveCache.clear();

    curveCache.emplace_back(curve.getStart(), 0.0);
    curveCache.emplace_back(curve.getEnd(), 1.0);

    recursiveInterpolate(curve, curveCache, 0, 1);

    if (curveCache.size() < 2)
        return;

    // Sort the points by parameter.
    std::sort(curveCache.begin(), curveCache.end());

    reserveExtra(vertices, curveCache.size() - 1);

    // Copy the points over, skipping the first because it should be the last
    // vertex already in the collection.
    for (size_t index = 1; index < curveCache.size(); ++index)
    {
        vertices.push_back(curveCache[index].Position);
    }
}

void simplifyCubicBezier(PointCollection &points, ParamPointCollection &cache,
                         const ConversionContext &converter,
                         const POINTFX *rawPoints, int count)
{
    // Points are structured after the GDI function PolyBezierTo().
    for (int i = 2; i < count; i += 3)
    {
        PointD ctrlPt1 = converter.convert(rawPoints[i - 2]);
        PointD ctrlPt2 = converter.convert(rawPoints[i - 1]);
        PointD endPt = converter.convert(rawPoints[i]);

        CubicCurveParams curveParams(points.back(), endPt, ctrlPt1, ctrlPt2,
                                     converter.getTolerance());

        interpolateCurve(points, cache, curveParams);
    }
}

void simplifyQuadraticBezier(PointCollection &points, ParamPointCollection &cache,
                             const ConversionContext &converter,
                             const POINTFX *rawPoints, int count)
{
    // See: https://jeffpar.github.io/kbarchive/kb/087/Q87115/
    for (int i = 0; i < (count - 1); ++i)
    {
        PointD ctrlPt = converter.convert(rawPoints[i]);
        PointD midPt = converter.convert(rawPoints[i + 1]);
        PointD endPt;

        if (i < (count - 2))
        {
            // Not the last spline.
            endPt = (ctrlPt + midPt) * 0.5;
        }
        else
        {
            endPt = midPt;
        }

        QuadraticCurveParams curveParams(points.back(), endPt, ctrlPt,
                                         converter.getTolerance());

        interpolateCurve(points, cache, curveParams);
    }
}

void writeGlpyhData(FILE *stream, const std::wstring &name,
                    const IndexRangeCollection &indices,
                    const PointCollection &vertices)
{
    std::pair<uint32_t, uint32_t> AnA_Indices[] = { { 0, 5 } };
    std::pair<double, double> AnA_Vertices[] = { { 12.5, 6.2 } };

    fwprintf_s(stream, L"std::pair<uint32_t, uint32_t> %s_Indices[] = {\n",
               name.c_str());

    for (const auto &indexRange : indices)
    {
        fwprintf_s(stream, L"  { %u, %u },\n", indexRange.first, indexRange.second);
    }

    fwprintf_s(stream, L"};\n\nstd::pair<double, double> %s_Vertices[] = {\n", name.c_str());

    for (const auto &vertex : vertices)
    {
        fwprintf_s(stream, L"  { %g, %g },\n", vertex.X, vertex.Y);
    }

    fputws(L"};\n\n", stream);
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GlyphWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to enumerate and serialize glyph data as C++
//! literals.
//! @param[in] glyphData The block of bytes used to define the figures and
//! curves defining the glyph outline.
GlyphWriter::GlyphWriter(const std::vector<uint8_t> &glyphData) :
    _glyphSource(glyphData),
    _figureCount(0)
{
    // See: https://jeffpar.github.io/kbarchive/kb/087/Q87115/
    // TTPOLYGONHEADER - Per figure
    //  TTPOLYCURVE[] - Per curve
    //      POINTFX[] - Per vertex

    auto figure = getFirstFigure();
    if (figure == nullptr)
        return;

    do
    {
        ++_figureCount;
    } while (tryGetNextFigure(figure));
}

//! @brief Writes the glyph data as literal C++ data values.
//! @param[in] stream The stream to write C++ source code to.
//! @param[in] name The name associated with the glyph.
//! @param[in] accuracyThreshold The maximum distance allowed between the defined
//! curve of the glyph outline and its straight line approximation.
//! @param[in] scaleX The horizontal scale factor to apply to vertices.
//! @param[in] scaleY The vertical scale factor to apply to vertices.
void GlyphWriter::write(FILE *stream, const std::wstring &name,
                        double accuracyThreshold,
                        double scaleX, double scaleY) const
{
    auto figure = getFirstFigure();

    if (figure == nullptr)
        return;

    ConversionContext converter(scaleX, scaleY, accuracyThreshold);
    PointCollection vertices;
    ParamPointCollection curveCache;
    IndexRangeCollection indices;

    vertices.reserve(64);
    curveCache.reserve(32);
    indices.reserve(16);

    do
    {
        auto curve = getFirstCurve(figure);
        size_t startIndex = vertices.size();

        vertices.push_back(converter.convert(figure->pfxStart));

        if (curve != nullptr)
        {
            do
            {

                switch (curve->wType)
                {
                case TT_PRIM_LINE:
                    reserveExtra(vertices, curve->cpfx);

                    for (WORD i = 0; i < curve->cpfx; ++i)
                    {
                        vertices.push_back(converter.convert(curve->apfx[i]));
                    }
                    break;

                case TT_PRIM_QSPLINE:
                    assert(curve->cpfx >= 2);
                    simplifyQuadraticBezier(vertices, curveCache,
                                            converter, curve->apfx,
                                            static_cast<int>(curve->cpfx));
                    break;

                case TT_PRIM_CSPLINE:
                    assert((curve->cpfx % 3) == 0);
                    simplifyCubicBezier(vertices, curveCache,
                                        converter, curve->apfx,
                                        static_cast<int>(curve->cpfx));
                    break;

                default:
                    assert(false);
                    break;
                }
            } while (tryGetNextCurve(figure, curve));
        }

        if ((vertices.size() > 1) && (vertices.front() == vertices.back()))
        {
            // The first vertex is repeated.
            vertices.pop_back();
        }

        size_t figureVertexCount = vertices.size() - startIndex;

        if (figureVertexCount > 2)
        {
            // Define the figure bit it's indices.
            indices.emplace_back(static_cast<uint32_t>(startIndex),
                                 static_cast<uint32_t>(figureVertexCount));
        }
        else
        {
            // Remove the vertices of the invalid figure.
            vertices.erase(vertices.begin() + startIndex, vertices.end());
        }
    } while (tryGetNextFigure(figure));

    // Write the data as C++ literals.
    writeGlpyhData(stream, name, indices, vertices);
}

//! @brief Gets a pointer to the first figure in the glyph.
//! @return A pointer to the first figure, nullptr if there are none.
const TTPOLYGONHEADER *GlyphWriter::getFirstFigure() const
{
    return _glyphSource.empty() ? nullptr :
                                  reinterpret_cast<const TTPOLYGONHEADER *>(_glyphSource.data());
}

//! @brief Attempts to update a pointer to the next figure.
//! @param[in,out] figure The pointer to the current figure to be updated to
//! the next.
//! @retval true The pointer was successfully updated.
//! @retval false The input figure was the last one in the glyph.
bool GlyphWriter::tryGetNextFigure(const TTPOLYGONHEADER *&figure) const
{
    if (figure == nullptr)
        return false;

    size_t figureOffset = getOffset(_glyphSource.data(), figure);

    if (figureOffset >= _glyphSource.size())
    {
        // We've past the last figure.
        figure = nullptr;
        return false;
    }

    figureOffset += figure->cb;

    if (figureOffset >= _glyphSource.size())
    {
        figure = nullptr;
        return false;
    }

    figure = getPtr<Figure>(figure, figure->cb);
    return true;
}

//! @brief Gets a pointer to the first curve within a figure.
//! @param[in] figure The figure containing the curve.
//! @return A pointer to a curve specification, or nullptr if the figure
//! is invalid.
const TTPOLYCURVE *GlyphWriter::getFirstCurve(const TTPOLYGONHEADER *figure) const
{
    if (figure == nullptr)
        return nullptr;

    size_t figureOffset = getOffset(_glyphSource.data(), figure);

    if (figureOffset >= _glyphSource.size())
    {
        // We've past the last figure.
        return nullptr;
    }

    return getPtr<Curve>(figure, sizeof(Figure));
}

//! @brief Updates a curve pointer to point to the next one.
//! @param[in] figure The figure the curve belongs to.
//! @param[in,out] curve The curve pointer to update.
//! @retval true The curve pointer was updated to point to the next
//! curve.
//! @retval false There were no more curves in the figure.
bool GlyphWriter::tryGetNextCurve(const TTPOLYGONHEADER *figure,
                                  const TTPOLYCURVE *&curve) const
{
    if ((curve == nullptr) || (figure == nullptr))
        return false;

    size_t curveOffset = getOffset(figure, curve);
    size_t figureSize = sizeof(Curve) + ((curve->cpfx - 1) * sizeof(POINTFX));
    size_t nextCurve = curveOffset + figureSize;

    if (nextCurve < figure->cb)
    {
        curve = getPtr<Curve>(figure, nextCurve);
        return true;
    }
    else
    {
        curve = nullptr;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////

