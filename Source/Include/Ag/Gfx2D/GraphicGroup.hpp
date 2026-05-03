//! @file Ag/Gfx2D/GraphicGroup.hpp
//! @brief The declaration of a hierarchical scene-graph container with
//! optional transform, opacity and clip.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_GRAPHIC_GROUP_HPP__
#define __GFX_2D_GRAPHIC_GROUP_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "Graphic.hpp"
#include "Path.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief A scene-graph container holding ordered children with an optional
//! affine transform, group opacity and clip path.
//!
//! Paint order is the order in which children were added. Transform
//! composes from parent to child; opacity multiplies down the tree; the
//! clip (if set) is applied to all descendants in the group's local space.
class GraphicGroup : public Graphic
{
public:
    // Construction/Destruction
    GraphicGroup();
    virtual ~GraphicGroup() = default;

    // Accessors
    const std::vector<GraphicSPtr>      &getChildren() const noexcept;
    const Geom::AffineTransform2D       &getTransform() const noexcept;
    double                               getOpacity() const noexcept;
    bool                                 hasClip() const noexcept;
    const Path                          &getClip() const noexcept;

    // Mutators
    void addChild(const GraphicSPtr &child);
    void clearChildren();
    void setTransform(const Geom::AffineTransform2D &transform);
    void setOpacity(double opacity);
    void setClip(const Path &clip);
    void clearClip();

    // Graphic overrides
    virtual Geom::Rect2D calculateBounds(
        const Geom::AffineTransform2D &parentTransform) const override;
    virtual bool hitTest(const Geom::Point2D &worldPoint,
                         const Geom::AffineTransform2D &parentTransform) const override;
    virtual void decomposeInto(GraphicDecomposition &out,
                               const Geom::AffineTransform2D &parentTransform,
                               double parentOpacity,
                               size_t parentClipId,
                               const ClipStack &activeClips,
                               DecompositionContext &ctx) const override;

    using Graphic::calculateBounds;
    using Graphic::hitTest;
    using Graphic::decompose;
    using Graphic::decomposeInto;

    // GraphicArtefact overrides
    virtual void freeze() override;
    virtual GraphicArtefactSPtr clone() const override;

private:
    std::vector<GraphicSPtr> _children;
    Geom::AffineTransform2D  _transform;
    Path                     _clip;
    double                   _opacity;
    bool                     _hasClip;
};

using GraphicGroupSPtr = std::shared_ptr<GraphicGroup>;

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
