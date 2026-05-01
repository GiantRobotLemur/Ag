//! @file Ag/Gfx2D/PartitionedPolygon.hpp
//! @brief The declaration of a polygon which has been partitioned into a set
//! of triangles ready for rendering by a driver.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_PARTITIONEDPOLYGON_HPP__
#define __GFX_2D_PARTITIONEDPOLYGON_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core.hpp"
#include "Ag/Geometry.hpp"

////////////////////////////////////////////////////////////////////////////////
// Macro Definitions
////////////////////////////////////////////////////////////////////////////////

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
class DecompositionContext;

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A polygon which has been partitioned into a set of triangles ready
//! for rendering by a driver.
class PartitionedPolygon
{
private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    ByteBlock _data;
    Geom::Point2DCollectionView _points;
    Geom::DCEL::IDCollectionView _triangleIndices;
    Geom::DCEL::IDCollectionView _outlineIndices;
    Geom::Rect2D _originalBounds;
public:
    // Construction/Destruction
    PartitionedPolygon() = default;
    PartitionedPolygon(const Geom::Point2DCollection &vertices,
                       const Geom::DCEL::IDDeque &triangleIndices,
                       const Geom::DCEL::IDDeque &outlineIndices,
                       const Geom::Rect2D &originalBounds);

    //! @brief Constructs a bounds-only placeholder polygon with no vertex
    //! or index data. Intended as a workaround until the DCEL partition
    //! pipeline lands.
    explicit PartitionedPolygon(const Geom::Rect2D &originalBounds);

    ~PartitionedPolygon() = default;

    // The internal views point at memory owned by _data. A deep copy would
    // leave the views referencing the source's buffer, so copying is
    // explicitly disallowed. std::vector move semantics preserve the buffer
    // pointer, so move construction/assignment is safe.
    PartitionedPolygon(const PartitionedPolygon &) = delete;
    PartitionedPolygon &operator=(const PartitionedPolygon &) = delete;
    PartitionedPolygon(PartitionedPolygon &&) noexcept = default;
    PartitionedPolygon &operator=(PartitionedPolygon &&) noexcept = default;

    // Accessors
    constexpr const Geom::Point2DCollectionView &getPoints() const noexcept { return _points; }
    constexpr const Geom::DCEL::IDCollectionView &getTriangleIndices() const noexcept { return _triangleIndices; }
    constexpr const Geom::DCEL::IDCollectionView &getOutlineIndices() const noexcept { return _outlineIndices; }
    constexpr const Geom::Rect2D &getOriginalBounds() const noexcept { return _originalBounds; }

    // Operations


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
