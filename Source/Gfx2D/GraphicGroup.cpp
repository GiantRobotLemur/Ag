//! @file Gfx2D/GraphicGroup.cpp
//! @brief The definition of a hierarchical scene-graph container with
//! optional transform, opacity and clip.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/GraphicGroup.hpp"
#include "Ag/Gfx2D/GraphicDecomposition.hpp"

#include "DecompositionContext.hpp"

namespace Ag {
namespace Gfx2D {

namespace {
const std::string_view GraphicGroupName("GraphicGroup");
constexpr double DefaultDecompositionTolerance = 0.5;
} // anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GraphicGroup Member Definitions
////////////////////////////////////////////////////////////////////////////////
GraphicGroup::GraphicGroup() :
    _opacity(1.0),
    _hasClip(false)
{
}

const std::vector<GraphicSPtr> &GraphicGroup::getChildren() const noexcept
{
    return _children;
}

const Geom::AffineTransform2D &GraphicGroup::getTransform() const noexcept
{
    return _transform;
}

double GraphicGroup::getOpacity() const noexcept
{
    return _opacity;
}

bool GraphicGroup::hasClip() const noexcept
{
    return _hasClip;
}

const Path &GraphicGroup::getClip() const noexcept
{
    return _clip;
}

void GraphicGroup::addChild(const GraphicSPtr &child)
{
    verifyAccess(GraphicGroupName, "add child");

    if (child)
    {
        _children.push_back(child);
    }
}

void GraphicGroup::clearChildren()
{
    verifyAccess(GraphicGroupName, "clear children");
    _children.clear();
}

void GraphicGroup::setTransform(const Geom::AffineTransform2D &transform)
{
    verifyAccess(GraphicGroupName, "set transform");
    _transform = transform;
}

void GraphicGroup::setOpacity(double opacity)
{
    verifyAccess(GraphicGroupName, "set opacity");

    if (opacity < 0.0)
    {
        opacity = 0.0;
    }
    else if (opacity > 1.0)
    {
        opacity = 1.0;
    }

    _opacity = opacity;
}

void GraphicGroup::setClip(const Path &clip)
{
    verifyAccess(GraphicGroupName, "set clip");
    _clip = clip;
    _hasClip = clip.isBound();
}

void GraphicGroup::clearClip()
{
    verifyAccess(GraphicGroupName, "clear clip");
    _clip = Path();
    _hasClip = false;
}

//! @brief Computes the world-space bounds of the group as the union of its
//! children's bounds in the composed transform. The clip is not used to
//! shrink bounds in v1 — bounds are conservative.
Geom::Rect2D GraphicGroup::calculateBounds(
    const Geom::AffineTransform2D &parentTransform) const
{
    Geom::AffineTransform2D composed = parentTransform * _transform;
    Geom::Rect2D bounds;
    bool hasBounds = false;

    for (const auto &child : _children)
    {
        if (!child)
            continue;

        Geom::Rect2D childBounds = child->calculateBounds(composed);

        if (childBounds.isEmpty())
            continue;

        bounds = hasBounds ? bounds.combine(childBounds) : childBounds;
        hasBounds = true;
    }

    return bounds;
}

//! @brief Hit-tests by recusing into children under the composed transform.
//! Returns true if any child is hit. The clip path is honoured: a hit
//! outside the clip is rejected.
bool GraphicGroup::hitTest(const Geom::Point2D &worldPoint,
                           const Geom::AffineTransform2D &parentTransform) const
{
    if (_opacity <= 0.0)
    {
        return false;
    }

    Geom::AffineTransform2D composed = parentTransform * _transform;

    if (_hasClip)
    {
        // Clip is in this group's local space — bounds-only check for v1.
        Geom::Rect2D clipBounds;

        if (_clip.tryCalculateBounds(
                DecompositionParams(composed, DefaultDecompositionTolerance),
                clipBounds))
        {
            if (!clipBounds.contains(worldPoint))
            {
                return false;
            }
        }
    }

    for (const auto &child : _children)
    {
        if (child && child->hitTest(worldPoint, composed))
        {
            return true;
        }
    }

    return false;
}

//! @brief Decomposes the group: composes transform / opacity, registers any
//! clip region, and recuses into children.
void GraphicGroup::decomposeInto(GraphicDecomposition &out,
                                 const Geom::AffineTransform2D &parentTransform,
                                 double parentOpacity,
                                 size_t parentClipId,
                                 DecompositionContext &ctx) const
{
    double effectiveOpacity = parentOpacity * _opacity;

    if (effectiveOpacity <= 0.0)
        return;

    Geom::AffineTransform2D composed = parentTransform * _transform;
    size_t childClipId = parentClipId;

    // See note in VectorGraphic::decomposeInto — partition() is currently
    // incomplete in the Geometry layer, so the clip is recorded as a
    // bounds-only placeholder until that pipeline lands. We always register
    // the clip when one is set; tryCalculateBounds() may return an empty
    // rect for some paths until the path simulation pipeline is complete.
    if (_hasClip && _clip.isBound())
    {
        Geom::Rect2D clipBounds;
        _clip.tryCalculateBounds(
            DecompositionParams(DefaultDecompositionTolerance),
            clipBounds);

        childClipId = out.appendClip(
            ClipRegion(PartitionedPolygon(clipBounds),
                       composed, parentClipId));
    }

    (void)ctx;

    for (const auto &child : _children)
    {
        if (child)
        {
            child->decomposeInto(out, composed, effectiveOpacity,
                                 childClipId, ctx);
        }
    }
}

//! @brief Recursively freezes the group, its clip-bearing brushes and all
//! children, then marks the group itself frozen.
void GraphicGroup::freeze()
{
    for (const auto &child : _children)
    {
        if (child)
        {
            child->freeze();
        }
    }

    GraphicArtefact::freeze();
}

//! @brief Produces an unfrozen deep clone: each child is cloned recursively,
//! and the group's own state (transform / opacity / clip / children) is
//! reproduced. The Path clip is shared (Path is value-typed with internal
//! sharing via shared_ptr).
GraphicArtefactSPtr GraphicGroup::clone() const
{
    auto copy = std::make_shared<GraphicGroup>();
    copy->_transform = _transform;
    copy->_opacity = _opacity;
    copy->_clip = _clip;
    copy->_hasClip = _hasClip;
    copy->_children.reserve(_children.size());

    for (const auto &child : _children)
    {
        if (!child)
            continue;

        auto childClone = std::dynamic_pointer_cast<Graphic>(child->clone());

        if (childClone)
            copy->_children.push_back(std::move(childClone));
    }

    return copy;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
