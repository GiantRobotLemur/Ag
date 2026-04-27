//! @file Ag/Gfx2D/Brush.hpp
//! @brief The declaration of classes which describe a graphic fill style.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_BRUSH_HPP__
#define __GFX_2D_BRUSH_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Ag/Geometry.hpp"

#include "Colour.hpp"
#include "GraphicArtefact.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Specifies the type of a brush.
enum class FillType
{
    Empty,
    Solid,
    Linear,
    Pattern,
    Image,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//class BrushPrivate;

struct GradientStop
{
    Colour Value;
    double Offset;
    uint64_t Padding;

    GradientStop();
    GradientStop(double offset, const Colour &value);
    ~GradientStop() = default;
};

using GradientStopCollection = std::vector<GradientStop, Ag::AlignedAllocator<GradientStop, 16>>;

////! @brief An object which specifies a linearly interpolated fill style.
//class LinearBrushBuilder
//{
//public:
//    // Construction/Destruction
//    LinearBrushBuilder(const Colour &startColour,
//                       const Colour &endColour);
//
//    LinearBrushBuilder(const Colour &startColour,
//                       const Colour &endColour,
//                       const Geom::Point2D &startPosition,
//                       const Geom::Point2D &endPosition);
//    ~LinearBrushBuilder() = default;
//
//    // Accessors
//    const Colour &getStartColour() const;
//    void setStartColour(const Colour &start);
//    const Colour &getEndColour() const;
//    void setEndColour(const Colour &end);
//    const Geom::Point2D &getStartPosition() const;
//    void setStartPosition(const Geom::Point2D &start);
//    const Geom::Point2D &getEndPosition() const;
//    void setEndPosition(const Geom::Point2D &end);
//    const GradientStopCollection &getIntermediateColourPoints() const;
//
//    // Operations
//    void addGradientStop(const Colour &colour, double offset);
//private:
//
//    // Internal Fields
//    Geom::Point2D _startPosition;
//    Geom::Point2D _endPosition;
//    Colour _startColour;
//    Colour _endColour;
//    GradientStopCollection _gradients;
//};

//! @brief An object which forms the base of any fill style.
class Brush : public GraphicArtefact
{
public:
    // Constants
    static const std::shared_ptr<Brush> Empty;

protected:
    // Construction/Destruction
    Brush(bool isFrozen);
public:
    Brush();
    virtual ~Brush() = default;

    // Accessors

    //! @brief Gets the type of fill the object represents.
    virtual FillType getType() const =0;
};

using BrushSPtr = std::shared_ptr<Brush>;

//! @brief An object which represents a solid fill style.
class SolidColourBrush : public AlignedBase_t<Brush, Colour>
{
public:
    // Construction/Destruction
    SolidColourBrush(const Colour &fillColour, bool isFrozen = false);
    virtual ~SolidColourBrush() = default;

    // Accessors
    const Colour &getFill() const noexcept;
    void setFill(const Colour fillColour) noexcept;

    // Overrides
    virtual GraphicArtefactSPtr clone() const override;
    virtual FillType getType() const override;
private:
    // Internal Fields
    Colour _fill;
};

using SolidColourBrushSPtr = std::shared_ptr<SolidColourBrush>;

//! @brief An object which represents a solid fill style.
class LinearGradientBrush : public AlignedBase_t<Brush, Colour>
{
public:
    // Construction/Destruction
    LinearGradientBrush(const Colour &startColour,
                       const Colour &endColour,
                        bool isFrozen = false);

    LinearGradientBrush(const Colour &startColour,
                        const Colour &endColour,
                        const Geom::Point2D &startPosition,
                        const Geom::Point2D &endPosition,
                        bool isFrozen = false);
    LinearGradientBrush(const Colour &startColour,
                        const Colour &endColour,
                        const GradientStop *gradients,
                        size_t gradientCount,
                        const Geom::Point2D &startPosition,
                        const Geom::Point2D &endPosition,
                        bool isFrozen = false);

    virtual ~LinearGradientBrush() = default;

    // Accessors
    const Colour &getStartColour() const noexcept;
    void setStartColour(const Colour &start);
    const Colour &getEndColour() const noexcept;
    void setEndColour(const Colour &end);
    const Geom::Point2D &getStartPosition() const noexcept;
    void setStartPosition(const Geom::Point2D &start);
    const Geom::Point2D &getEndPosition() const noexcept;
    void setEndPosition(const Geom::Point2D &end);
    const GradientStopCollection &getGradientStops() const noexcept;

    // Operations
    void addGradientStop(const Colour &colour, double offset);

    // Overrides
    virtual GraphicArtefactSPtr clone() const override;
    virtual FillType getType() const override;
private:
    // Internal Fields
    Geom::Point2D _startPosition;
    Geom::Point2D _endPosition;
    Colour _startColour;
    Colour _endColour;
    GradientStopCollection _gradients;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
