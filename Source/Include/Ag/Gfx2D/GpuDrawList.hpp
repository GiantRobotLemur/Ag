//! @file Ag/Gfx2D/GpuDrawList.hpp
//! @brief The declaration of a GPU-ready draw list packed from a
//! GraphicDecomposition: a single shared vertex buffer, a single index
//! buffer, and per-shape instance data plus metadata flags.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_GPU_DRAW_LIST_HPP__
#define __GFX_2D_GPU_DRAW_LIST_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

#include "Ag/Geometry.hpp"

#include "Colour.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
////////////////////////////////////////////////////////////////////////////////
class GraphicDecomposition;

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief A single GPU vertex carrying a local-space position and an
//! evaluated RGBA colour.
//!
//! Positions are emitted in each shape's local space; the per-instance
//! @c worldTransform takes them to world space at draw time. Colours are
//! straight (non-premultiplied) RGBA — the back-end shader is expected to
//! premultiply by the per-instance opacity if its blending state requires it.
struct GpuVertex
{
    Geom::Point2D position;
    Colour        colour;
};

//! @brief Bit values for @c GpuInstance::flags.
namespace GpuInstanceFlag
{
    //! @brief The shape requires alpha blending — at least one vertex colour
    //! has alpha < 1.0 or the inherited opacity is < 1.0.
    constexpr uint32_t NeedsAlphaBlend = 1u << 0;
}

//! @brief Per-instance state for one decomposed shape, indexing into the
//! shared vertex and index buffers.
//!
//! @c worldTransform is laid out exactly as @c AffineTransform2D::toArray()
//! truncated to its first six values (the 2x2 matrix followed by the two
//! translation components), but cast to @c float for shader friendliness.
struct GpuInstance
{
    float    worldTransform[6];
    float    opacity;
    uint32_t flags;
    uint32_t firstIndex;
    uint32_t indexCount;
    uint32_t baseVertex;
    uint32_t reserved;
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////

//! @brief A flat, GPU-ready draw list packed from a @c GraphicDecomposition.
//!
//! The list is the artefact handed from the rendering thread to a GPU back-end:
//! a shared vertex buffer, a shared 32-bit index buffer, and one
//! @c GpuInstance per decomposed shape. Paint order matches the shape order
//! in the source decomposition. The back-end is expected to issue one
//! instanced draw — or to bucket instances by state if it wants to — using
//! the per-instance @c firstIndex / @c indexCount / @c baseVertex range.
class GpuDrawList
{
public:
    GpuDrawList() = default;
    ~GpuDrawList() = default;

    GpuDrawList(const GpuDrawList &) = delete;
    GpuDrawList &operator=(const GpuDrawList &) = delete;
    GpuDrawList(GpuDrawList &&) noexcept = default;
    GpuDrawList &operator=(GpuDrawList &&) noexcept = default;

    //! @brief Packs a decomposition into a GPU-ready draw list.
    //!
    //! For each @c DecomposedShape the brush is evaluated at every triangle
    //! vertex to produce per-vertex colour. Solid brushes produce a constant
    //! colour; linear gradient brushes produce per-vertex interpolated colour
    //! along the gradient axis. (For correct multi-stop gradients the
    //! decomposition must already include vertices on the stop lines — see
    //! the gradient-stop intersection step in the partitioner.)
    static GpuDrawList buildFrom(const GraphicDecomposition &decomp);

    // Accessors
    const std::vector<GpuVertex>   &getVertices() const noexcept  { return _vertices; }
    const std::vector<uint32_t>    &getIndices() const noexcept   { return _indices; }
    const std::vector<GpuInstance> &getInstances() const noexcept { return _instances; }

    //! @brief True if any instance has the @c NeedsAlphaBlend flag set.
    bool anyAlphaBlend() const noexcept { return _anyAlphaBlend; }

    bool isEmpty() const noexcept { return _instances.empty(); }

private:
    std::vector<GpuVertex>   _vertices;
    std::vector<uint32_t>    _indices;
    std::vector<GpuInstance> _instances;
    bool                     _anyAlphaBlend = false;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
