//! @file Gfx2D/Brush.cpp
//! @brief The definition of classes which describe a graphic fill style.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Brush.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief A less-than operator which compares GradientStop object by offset.
struct GradientStopLessThan
{
    bool operator()(const GradientStop &lhs, const GradientStop &rhs) const
    {
        return lhs.Offset < rhs.Offset;
    }
};

//! @brief An equality operator which compares GradientStop objects by offset.
struct GradientStopEqual
{
    bool operator()(const GradientStop &lhs, const GradientStop &rhs) const
    {
        return lhs.Offset == rhs.Offset;
    }
};

//! @brief An equality operator which compares GradientStop objects by colour value.
struct GradientColourEqual
{
    bool operator()(const GradientStop &lhs, const GradientStop &rhs) const
    {
        return lhs.Value == rhs.Value;
    }
};

//! @brief An object which represent no fill.
class EmptyBrush : public Brush
{
public:
    EmptyBrush() :
        Brush(true)
    {
    }

    virtual ~EmptyBrush() = default;

    virtual GraphicArtefactSPtr clone() const override
    {
        return const_cast<EmptyBrush *>(this)->shared_from_this();
    }

    virtual FillType getType() const override
    {
        return FillType::Empty;
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const std::string_view SolidColourBrush_Name("SolidColourBrush");
static const std::string_view LinearGradientBrush_Name("LinearGradientBrush");

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GradientStop Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty object representing a point in a linear
//! gradient fill pattern.
GradientStop::GradientStop() :
    Offset(0),
    Padding(0)
{
}

//! @brief Constructs an object initialised with a point in a linear gradient
//! fill pattern.
//! @param[in] offset The offset of the point within the pattern, preferably
//! between 0.0 and 1.0.
//! @param[in] value The colour to fill with at that point in the fill.
GradientStop::GradientStop(double offset, const Colour &value) :
    Value(value),
    Offset(offset),
    Padding(0)
{
}

////////////////////////////////////////////////////////////////////////////////
// Brush Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief A brush which produces no fill.
const BrushSPtr Brush::Empty = std::dynamic_pointer_cast<Brush>(std::make_shared<EmptyBrush>());

//! @brief Constructs the base of a fill description, possibly already frozen.
//! @param[in] isFrozen True to create a pre-frozen brush.
Brush::Brush(bool isFrozen) :
    GraphicArtefact(isFrozen)
{
}

////////////////////////////////////////////////////////////////////////////////
// SolidColourBrush Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a description of a solid fill.
//! @param[in] fillColour The colour applied to all pixels filled.
//! @param[in] isFrozen Indicates if the brush is created frozen or can be edited.
SolidColourBrush::SolidColourBrush(const Colour &fillColour,
                                   bool isFrozen /*= false*/) :
    AlignedBase_t<Brush, Colour>(isFrozen),
    _fill(fillColour)
{
}

//! @brief Gets the current fill colour.
const Colour &SolidColourBrush::getFill() const noexcept
{
    return _fill;
}

//! @brief Sets the new fill colour.
//! @param[in] fillColour The new fill colour.
void SolidColourBrush::setFill(const Colour fillColour) noexcept
{
    // Ensure the object isn't frozen.
    verifyAccess(SolidColourBrush_Name, "set fill colour");

    _fill = fillColour;
}

// Inherited from GraphicArtefact.
GraphicArtefactSPtr SolidColourBrush::clone() const
{
    return std::make_shared<SolidColourBrush>(_fill, false);
}

// Inherited from Brush.
FillType SolidColourBrush::getType() const
{
    return FillType::Solid;
}

////////////////////////////////////////////////////////////////////////////////
// LinearGradientBrush Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new linear gradient brush which shades across a square.
//! @param[in] startColour The colour at the fill origin.
//! @param[in] endColour The colour at the fill extreme.
//! @param[in] isFrozen True to create an immutable brush.
LinearGradientBrush::LinearGradientBrush(const Colour &startColour,
                                         const Colour &endColour,
                                         bool isFrozen /*= false*/) :
    AlignedBase_t<Brush, Colour>(isFrozen),
    _startPosition(0, 0),
    _endPosition(1, 1),
    _startColour(startColour),
    _endColour(endColour),
    _gradients()
{
}

//! @brief Constructs a new linear gradient brush which shades between two points.
//! @param[in] startColour The colour at the fill origin.
//! @param[in] endColour The colour at the fill extreme.
//! @param[in] startPosition The position where shading starts.
//! @param[in] endPosition The position where shading ends.
//! @param[in] isFrozen True to create an immutable brush.
LinearGradientBrush::LinearGradientBrush(const Colour &startColour,
                                         const Colour &endColour,
                                         const Geom::Point2D &startPosition,
                                         const Geom::Point2D &endPosition,
                                         bool isFrozen /*= false*/) :
    AlignedBase_t<Brush, Colour>(isFrozen),
    _startPosition(startPosition),
    _endPosition(endPosition),
    _startColour(startColour),
    _endColour(endColour),
    _gradients()
{
}

//! @brief Constructs a new linear gradient brush which shades between two points
//! and across a number of intermediate gradients.
//! @param[in] startColour The colour at the fill offset 0.0.
//! @param[in] endColour The colour at the fill offset 1.0.
//! @param[in] gradients An array of GradientStops with offsets between 0.0 and 1.0.
//! @param[in] gradientCount The number of elements in @p gradients.
//! @param[in] startPosition The position where shading starts.
//! @param[in] endPosition The position where shading ends.
//! @param[in] isFrozen True to create an immutable brush.
LinearGradientBrush::LinearGradientBrush(const Colour &startColour,
                                         const Colour &endColour,
                                         const GradientStop *gradients,
                                         size_t gradientCount,
                                         const Geom::Point2D &startPosition,
                                         const Geom::Point2D &endPosition,
                                         bool isFrozen /*= false*/) :
    AlignedBase_t<Brush, Colour>(isFrozen),
    _startPosition(startPosition),
    _endPosition(endPosition),
    _startColour(startColour),
    _endColour(endColour)
{
    if (gradientCount > 0)
    {
        _gradients.reserve(gradientCount);

        std::copy_n(gradients, gradientCount, std::back_inserter(_gradients));
    }
}

//! @brief Gets the colour at the fill offset 0.0.
const Colour &LinearGradientBrush::getStartColour() const noexcept
{
    return _startColour;
}

//! @brief Sets the colour at the fill offset 0.0.
//! @param[in] start The new start colour.
void LinearGradientBrush::setStartColour(const Colour &start)
{
    verifyAccess(LinearGradientBrush_Name, "set start colour");

    _startColour = start;
}

//! @brief Gets the colour at the fill offset 1.0.
const Colour &LinearGradientBrush::getEndColour() const noexcept
{
    return _endColour;
}

//! @brief Sets the colour at the fill offset 1.0.
//! @param[in] end The new end colour.
void LinearGradientBrush::setEndColour(const Colour &end)
{
    verifyAccess(LinearGradientBrush_Name, "set the end colour");

    _endColour = end;
}

//! @brief Gets the position at which gradients are measured from relative
//! to the filled area.
const Geom::Point2D &LinearGradientBrush::getStartPosition() const noexcept
{
    return _startPosition;
}

//! @brief Sets the position at which gradients are measured from relative
//! to the filled area.
//! @param[in] start The new start position.
void LinearGradientBrush::setStartPosition(const Geom::Point2D &start)
{
    verifyAccess(LinearGradientBrush_Name, "set the start position");

    _startPosition = start;
}

//! @brief Gets the position at which gradients are measured to relative
//! to the filled area.
const Geom::Point2D &LinearGradientBrush::getEndPosition() const noexcept
{
    return _endPosition;
}

//! @brief Sets the position at which gradients are measured to relative
//! to the filled area.
//! @param[in] end The new end position.
void LinearGradientBrush::setEndPosition(const Geom::Point2D &end)
{
    verifyAccess(LinearGradientBrush_Name, "set the end position");

    _endPosition = end;
}

//! @brief Gets the ordered collection of gradient stops.
const GradientStopCollection &LinearGradientBrush::getGradientStops() const noexcept
{
    return _gradients;
}

//! @brief Adds a new colour at an offset through the area being filled.
//! @param[in] colour The colour which should appear at that offset.
//! @param[in] offset The linear offset between the start and end points at
//! which the colour should be applied.
void LinearGradientBrush::addGradientStop(const Colour &colour, double offset)
{
    verifyAccess(LinearGradientBrush_Name, "add gradient stop");

    if (offset == 0)
    {
        _startColour = colour;
    }
    else if (offset == 1.0)
    {
        _endColour = colour;
    }
    else
    {
        GradientStop stop(offset, colour);

        auto insertionPos = std::lower_bound(_gradients.begin(),
                                             _gradients.end(),
                                             stop, GradientStopLessThan());

        if ((insertionPos != _gradients.end()) &&
            (insertionPos->Offset == offset))
        {
            insertionPos->Value = colour;
        }
        else
        {
            _gradients.insert(insertionPos, stop);
        }
    }
}

// Inherited from GraphicArtefact.
GraphicArtefactSPtr LinearGradientBrush::clone() const
{
    return std::make_shared<LinearGradientBrush>(_startColour, _endColour,
                                                 _gradients.data(), _gradients.size(),
                                                 _startPosition, _endPosition, false);
}

// Inherited from Brush.
FillType LinearGradientBrush::getType() const
{
    return FillType::Linear;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

