//! @file Ag/Gfx2D/Scene.hpp
//! @brief The declaration of a top-level scene owner that supports producing
//! frozen snapshots safe for consumption on a render thread.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __GFX_2D_SCENE_HPP__
#define __GFX_2D_SCENE_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "GraphicGroup.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A thin owner wrapping the root @c GraphicGroup of a 2D scene.
//!
//! The scene supports one mutator thread (the thread that holds the scene
//! and modifies its tree) and any number of reader/render threads, provided
//! they only ever consume the @c GraphicGroupSPtr returned by @c snapshot().
//! Each call to @c snapshot() produces a fully-frozen deep clone of the
//! current tree which is safe to traverse and decompose concurrently with
//! ongoing mutation of the live root.
class Scene
{
public:
    Scene();
    explicit Scene(const GraphicGroupSPtr &root);
    ~Scene() = default;

    //! @brief Returns the live, mutable root group.
    const GraphicGroupSPtr &root() const noexcept;

    //! @brief Produces a fully-frozen deep clone of the scene tree, suitable
    //! for handing to a render thread.
    GraphicGroupSPtr snapshot() const;

private:
    GraphicGroupSPtr _root;
};

}} // namespace Ag::Gfx2D

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
