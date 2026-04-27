//! @file Ag/Gfx2D/Pen.hpp
//! @brief The declaration of an object defining a graphic line style.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_PEN_HPP__
#define __GFX_2D_PEN_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <memory>

#include "GraphicArtefact.hpp"
#include "Brush.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Expresses the shape rendered at the end of a line segment.
enum class EndCap : uint8_t
{
    //! @brief The end edge is perpendicular to the line direction and
    //! intersects with the end of the line.
    Flat,

    //! @brief The end edge is perpendicular to the line direction and
    //! extends the line thickness beyond the end of the line.
    Square,

    //! @brief The end edge is a semi-circle with a diameter equal to the
    //! thickness of the line.
    Round,

    //! @brief The end edge draws to a point the line thickness away from the
    //! end point.
    Triangle,
};

//! @brief Expresses the shape rendered where two line segments join.
enum class JoinCap : uint8_t
{
    //! @brief The line edges are connected at their intersection.
    Mitre,

    //! @brief The join point is projected perpendicular to each line segment
    //! being joined and the outer edge of the join chamfered using those points.
    Bevel,

    //! @brief The joint point is used as the centre of an arc used to render
    //! a curve for the outer edge of the join.
    Round,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
using DoubleCollection = std::vector<double>;

//! @brief An object defining a graphic line style.
class Pen : public GraphicArtefact
{
public:
    // Public Constants
    static const Pen Empty;

    // Construction/Destruction
    Pen() = default;
    Pen(const BrushSPtr &brush, double thickenss);
    ~Pen() = default;

    // Accessors
    bool isThin() const noexcept;
    bool isSolid() const noexcept;
    double getThickness() const noexcept;
    void setThickness(double thickness);
    EndCap getLineStartCap() const noexcept;
    void setLineStartCap(EndCap lineStart);
    EndCap getLineEndCap() const noexcept;
    void setLineEndCap(EndCap lineEnd);
    EndCap getDashCap() const noexcept;
    void setDashCap(EndCap dashEnd);
    JoinCap getJoinCap() const noexcept;
    void setJoinCap(JoinCap join);
    const DoubleCollection &getDashPattern() const noexcept;
    const BrushSPtr &getFill() const noexcept;
    void setFill(const BrushSPtr &brush);

    // Operations
    void makeSolid();
    void addDash(double dashLength);

    // Overrides
    virtual void freeze() override;
    virtual std::shared_ptr<GraphicArtefact> clone() const override;
private:
    // Internal Fields
    BrushSPtr _fill;
    double _thickness;
    DoubleCollection _dashLengths;
    EndCap _lineStartCap;
    EndCap _lineEndCap;
    EndCap _dashCap;
    JoinCap _joinCap;
};

using PenSPtr = std::shared_ptr<Pen>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
