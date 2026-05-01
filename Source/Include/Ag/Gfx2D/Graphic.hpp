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
#include "Path.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class DecompositionContext;
class GraphicDecomposition;

//! @brief A base class representing a component of a 2D scene graph.
class Graphic : public GraphicArtefact
{
protected:
    // Construction/Destruction
    Graphic() = default;
public:
    virtual ~Graphic() = default;

    // Operations

    //! @brief Computes the world-space bounding rectangle of this node,
    //! given the accumulated transform from its ancestors.
    //! @param[in] parentTransform The transform composed from all ancestors,
    //! identity at the root.
    virtual Geom::Rect2D calculateBounds(
        const Geom::AffineTransform2D &parentTransform) const = 0;

    //! @brief Tests whether a world-space point lies within this node.
    //! @param[in] worldPoint The point to test in world space.
    //! @param[in] parentTransform The transform composed from all ancestors,
    //! identity at the root.
    virtual bool hitTest(const Geom::Point2D &worldPoint,
                         const Geom::AffineTransform2D &parentTransform) const = 0;

    //! @brief Decomposes this node into draw items, appending them to @a out.
    //! @param[out] out The decomposition to append to.
    //! @param[in] parentTransform The transform composed from all ancestors.
    //! @param[in] parentOpacity The opacity composed from all ancestors,
    //! 1.0 at the root.
    //! @param[in] parentClipId The clip-region id inherited from the
    //! enclosing group, or @c GraphicDecomposition::NoClip if unclipped.
    //! @param[in,out] ctx A scratch decomposition context, reused across
    //! invocations to retain allocations.
    virtual void decomposeInto(GraphicDecomposition &out,
                               const Geom::AffineTransform2D &parentTransform,
                               double parentOpacity,
                               size_t parentClipId,
                               DecompositionContext &ctx) const = 0;

    // Convenience overloads for top-level callers.
    Geom::Rect2D calculateBounds() const;
    bool hitTest(const Geom::Point2D &worldPoint) const;
    GraphicDecomposition decompose() const;
};

using GraphicSPtr = std::shared_ptr<Graphic>;

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

    // Graphic overrides
    virtual Geom::Rect2D calculateBounds(
        const Geom::AffineTransform2D &parentTransform) const override;
    virtual bool hitTest(const Geom::Point2D &worldPoint,
                         const Geom::AffineTransform2D &parentTransform) const override;
    virtual void decomposeInto(GraphicDecomposition &out,
                               const Geom::AffineTransform2D &parentTransform,
                               double parentOpacity,
                               size_t parentClipId,
                               DecompositionContext &ctx) const override;

    using Graphic::calculateBounds;
    using Graphic::hitTest;
    using Graphic::decompose;

    // GraphicArtefact overrides
    virtual void freeze() override;

protected:
    //! @brief Returns the geometric path which represents this primitive in
    //! its local coordinate space. Concrete subclasses implement this to
    //! lower their high-level shape (rectangle, ellipse, etc.) to a Path.
    virtual Path lowerToPath() const = 0;

    //! @brief Returns the bounding rectangle of this primitive in its
    //! local coordinate space (before any parent transform is applied).
    //! Concrete subclasses provide this directly so we don't have to round-
    //! trip through the (incomplete) Path simulation pipeline.
    virtual Geom::Rect2D calculateLocalBounds() const = 0;

private:
    // Internal Fields
    BrushSPtr _fill;
    PenSPtr _stroke;
};

using VectorGraphicSPtr = std::shared_ptr<VectorGraphic>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
