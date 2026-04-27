//! @file Gfx2D/Pen.cpp
//! @brief The definition of an object describing a graphic line style.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <memory>

#include "Ag/Gfx2D/Brush.hpp"
#include "Ag/Gfx2D/Pen.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const std::string_view Pen_Name("Pen");

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// Pen Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new solid pen.
//! @param[in] fill The style used to fill line segments.
//! @param[in] thickness The thickness of the line in display units, a value
//! of 0 or less indicates a pixel thick line.
Pen::Pen(const BrushSPtr &brush, double thickness) :
    _fill(brush),
    _thickness(std::max(thickness, 0.0)),
    _lineStartCap(EndCap::Flat),
    _lineEndCap(EndCap::Flat),
    _dashCap(EndCap::Flat),
    _joinCap(JoinCap::Bevel)
{
}

//! @brief Indicates whether the line has a thickness of 1 device unit at any
//! scale factor.
//! @retval true The line always has a thickness of 1 device unit.
//! @retval false The lines thickness is scaled by transformations.
bool Pen::isThin() const noexcept
{
    return _thickness <= 0.0;
}

//! @brief Indicates whether a dash pattern has been defined.
//! @retval true The line has no dash pattern.
//! @retval false The line has a properly defined dash pattern.
bool Pen::isSolid() const noexcept
{
    return _dashLengths.empty();
}

//! @brief Gets the thickness of the line in display units.
double Pen::getThickness() const noexcept
{
    return _thickness;
}

//! @brief Sets the thickness of the line in display units.
//! @param[in] thickness The line thickness, zero or less for a pixel thick
//! line at any scale factor.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::setThickness(double thickness)
{
    verifyAccess(Pen_Name, "set thickness");

    _thickness = thickness;
}

//! @brief Gets the shape used at the beginning of a lines created with the
//! style.
EndCap Pen::getLineStartCap() const noexcept
{
    return _lineStartCap;
}

//! @brief Sets the shape used at the beginning of a lines created with the
//! style.
//! @param[in] lineStart The new end shape.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::setLineStartCap(EndCap lineStart)
{
    verifyAccess(Pen_Name, "set start cap");

    _lineStartCap = lineStart;
}

//! @brief Gets the shape used at the end of a lines created with the
//! style.
EndCap Pen::getLineEndCap() const noexcept
{
    return _lineEndCap;
}

//! @brief Sets the shape used at the end of a lines created with the
//! style.
//! @param[in] lineEnd The new end shape.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::setLineEndCap(EndCap lineEnd)
{
    verifyAccess(Pen_Name, "set end cap");

    _lineEndCap = lineEnd;
}

//! @brief Gets the shape used at in gaps created by dashes of a lines created
//! with the style.
EndCap Pen::getDashCap() const noexcept
{
    return _dashCap;
}

//! @brief Sets the shape used at in gaps created by dashes of a lines created
//! with the style.
//! @param[in] dashEnd The new end shape.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::setDashCap(EndCap dashEnd)
{
    verifyAccess(Pen_Name, "set dash cap");

    _dashCap = dashEnd;
}

//! @brief Gets the shape used where edges connect.
JoinCap Pen::getJoinCap() const noexcept
{
    return _joinCap;
}

//! @brief Sets the shape used where edges connect.
//! @param[in] join The new join style.
void Pen::setJoinCap(JoinCap join)
{
    verifyAccess(Pen_Name, "set join cap");

    _joinCap = join;
}


//! @brief Gets the alternate length of lines and gaps used to define a dash pattern.
//! @return A collection of lengths.
const DoubleCollection &Pen::getDashPattern() const noexcept
{
    return _dashLengths;
}

//! @brief Gets the detailed style of the line the pen produces.
const BrushSPtr &Pen::getFill() const noexcept
{
    return _fill;
}

//! @brief Sets the fill style used for the pixels covered by the line.
//! @param[in] brush A reference to the brush defining the new fill style.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::setFill(const BrushSPtr &brush)
{
    verifyAccess(Pen_Name, "set fill");

    _fill = brush;
}

//! @brief Removes all dashes making the line style solid.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::makeSolid()
{
    verifyAccess(Pen_Name, "remove all dashes");

    _dashLengths.clear();
}

//! @brief Adds the length of a dash or gap.
//! @param[in] dashLength The length in display units.
//! @throws ArtefactFrozenException If the pen is in a frozen state.
void Pen::addDash(double dashLength)
{
    verifyAccess(Pen_Name, "add dash");

    if (_dashLengths.empty())
    {
        // Allow only the first dash to have zero length to indicate that
        // any line starts with a gap.
        _dashLengths.push_back(std::max(dashLength, 0.0));
    }
    else if (dashLength <= 0.0)
    {
        throw ArgumentException("A dash cannot have a length of equal below "
                                "unless it is the first one of a dash pattern.",
                                "dashLength");
    }
    else
    {
        _dashLengths.push_back(dashLength);
    }
}

// Inherited from GraphicArtefact.
void Pen::freeze()
{
    GraphicArtefact::freeze();

    if (_fill)
    {
        // Ensure the underlying brush is frozen too.
        _fill = std::dynamic_pointer_cast<Brush>(_fill->createFrozenClone());
    }
}

// Inherited from GraphicArtefact.
std::shared_ptr<GraphicArtefact> Pen::clone() const
{
    PenSPtr clonedPen = std::make_shared<Pen>(_fill, _thickness);

    clonedPen->_lineStartCap = _lineStartCap;
    clonedPen->_lineEndCap = _lineEndCap;
    clonedPen->_dashCap = _dashCap;
    clonedPen->_joinCap = _joinCap;

    clonedPen->_dashLengths = _dashLengths;

    if (_dashLengths.empty() == false)
    {
        // Copy the dash lengths.
        auto &clonedDashes = clonedPen->_dashLengths;

        clonedDashes.reserve(_dashLengths.size());
        std::copy(_dashLengths.begin(), _dashLengths.end(),
                  std::back_inserter(clonedDashes));
    }

    return clonedPen;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////

