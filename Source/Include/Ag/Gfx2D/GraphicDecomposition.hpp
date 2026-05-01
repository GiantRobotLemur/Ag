//! @file Ag/Gfx2D/GraphicDecomposition.hpp
//! @brief The declaration of an object representing a graphic which has been
//! de-composed ready for rendering by a graphic driver, probably GPU-based.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_GRAPHIC_DECOMPOSITION_HPP__
#define __GFX_2D_GRAPHIC_DECOMPOSITION_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "Ag/Geometry.hpp"

#include "Brush.hpp"
#include "PartitionedPolygon.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief A single materialised draw item produced by graphic decomposition.
//!
//! Each draw item carries the local-space geometry, the world transform under
//! which it should be rendered, the (frozen) fill brush to apply, the
//! cumulative opacity inherited from ancestor groups, and the id of the clip
//! region under which it must be rendered (or @c GraphicDecomposition::NoClip
//! if unclipped).
class DecomposedShape
{
public:
    DecomposedShape(PartitionedPolygon geometry,
                    const Geom::AffineTransform2D &worldTransform,
                    BrushSPtr brush,
                    double effectiveOpacity,
                    size_t clipStackId);

    DecomposedShape(const DecomposedShape &) = delete;
    DecomposedShape &operator=(const DecomposedShape &) = delete;
    DecomposedShape(DecomposedShape &&) noexcept = default;
    DecomposedShape &operator=(DecomposedShape &&) noexcept = default;

    const PartitionedPolygon       &getGeometry() const noexcept       { return _geometry; }
    const Geom::AffineTransform2D  &getWorldTransform() const noexcept { return _worldTransform; }
    const BrushSPtr                &getBrush() const noexcept          { return _brush; }
    double                          getEffectiveOpacity() const noexcept { return _effectiveOpacity; }
    size_t                          getClipStackId() const noexcept    { return _clipStackId; }

private:
    PartitionedPolygon      _geometry;
    Geom::AffineTransform2D _worldTransform;
    BrushSPtr               _brush;
    double                  _effectiveOpacity;
    size_t                  _clipStackId;
};

//! @brief A clip region in the decomposed draw list.
//!
//! Clip regions form a tree via @c parentClipId — a draw item under a clip is
//! rendered against the intersection of that clip with all of its ancestors.
//! The back-end may walk the chain or pre-compose the clips, whichever it
//! prefers.
class ClipRegion
{
public:
    ClipRegion(PartitionedPolygon geometry,
               const Geom::AffineTransform2D &worldTransform,
               size_t parentClipId);

    ClipRegion(const ClipRegion &) = delete;
    ClipRegion &operator=(const ClipRegion &) = delete;
    ClipRegion(ClipRegion &&) noexcept = default;
    ClipRegion &operator=(ClipRegion &&) noexcept = default;

    const PartitionedPolygon       &getGeometry() const noexcept       { return _geometry; }
    const Geom::AffineTransform2D  &getWorldTransform() const noexcept { return _worldTransform; }
    size_t                          getParentClipId() const noexcept   { return _parentClipId; }

private:
    PartitionedPolygon      _geometry;
    Geom::AffineTransform2D _worldTransform;
    size_t                  _parentClipId;
};

//! @brief The full output of decomposing a 2D scene graph: an ordered draw
//! list of shapes and the clip regions they reference.
//!
//! Paint order is shape-vector order. Vertex coordinates are local-space; the
//! back-end is expected to apply each shape's world transform when drawing.
class GraphicDecomposition
{
public:
    //! @brief Sentinel value indicating a shape or clip is not under any
    //! enclosing clip.
    static constexpr size_t NoClip = static_cast<size_t>(-1);

    GraphicDecomposition() = default;
    ~GraphicDecomposition() = default;

    GraphicDecomposition(const GraphicDecomposition &) = delete;
    GraphicDecomposition &operator=(const GraphicDecomposition &) = delete;
    GraphicDecomposition(GraphicDecomposition &&) noexcept = default;
    GraphicDecomposition &operator=(GraphicDecomposition &&) noexcept = default;

    // Accessors
    const std::vector<DecomposedShape> &getShapes() const noexcept { return _shapes; }
    const std::vector<ClipRegion>      &getClips() const noexcept  { return _clips; }
    const Geom::Rect2D                 &getWorldBounds() const noexcept { return _worldBounds; }
    bool                                isEmpty() const noexcept   { return _shapes.empty(); }

    // Builder operations (called during decomposition).
    void appendShape(DecomposedShape shape);
    size_t appendClip(ClipRegion clip);
    void mergeBounds(const Geom::Rect2D &bounds);

private:
    std::vector<DecomposedShape> _shapes;
    std::vector<ClipRegion>      _clips;
    Geom::Rect2D                 _worldBounds;
    bool                         _hasBounds = false;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
