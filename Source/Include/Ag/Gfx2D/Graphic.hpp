//! @file Ag/Gfx2D/Graphic.hpp
//! @brief The declaration of a set of classes representing the components of
//! a 2D scene graph.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_GRAPHIC_HPP__
#define __GFX_2D_GRAPHIC_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Geometry.hpp"

#include "Brush.hpp"
#include "Pen.hpp"
#include "PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//class RawScene2D;
//using RawScene2DSPtr = std::shared_ptr<RawScene2D>;

//! @brief A base class representing a component of a 2D scene graph.
class Graphic : public GraphicArtefact
{
protected:
    // Construction/Destruction
    Graphic() = default;
public:
    virtual ~Graphic() = default;

    // Accessors

    // Operations
    virtual Geom::Rect2D calculateBounds(const Geom::AffineTransform2D &transform) const =0;
    virtual bool isPointIn(const Geom::AffineTransform2D &transform, const Geom::Point2D &point) const =0;
    //virtual RawScene2DSPtr decompose(const Geom::AffineTransform2D &transform) const = 0;

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
};

class DecompositionContext;

//! @brief A class representing a component of a 2D scene graph defined by
//! vector graphics, possibly filled, possibly outlined.
class VectorGraphic : public Graphic
{
protected:
    // Construction/Destruction
    VectorGraphic() = default;
public:
    virtual ~VectorGraphic() = default;

    // Accessors
    BrushSPtr getFill() const;
    void setFill(const BrushSPtr &fillStyle);
    PenSPtr getStroke() const;
    void setStroke(const PenSPtr &lineStyle);

    // Operations
    //virtual Geom::Rect2D calculateBounds(const Geom::AffineTransform2D &transform) const = 0;
    //virtual bool isPointIn(const Geom::AffineTransform2D &transform, const Geom::Point2D &point) const = 0;
    //virtual RawScene2DSPtr decompose(const Geom::AffineTransform2D &transform) const = 0;

    // Overrides

protected:
    virtual PartitionedPolygon decompose(const Geom::AffineTransform2D &transform,
                                         DecompositionContext &context) const =0;

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    BrushSPtr _fill;
    PenSPtr _stroke;
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
