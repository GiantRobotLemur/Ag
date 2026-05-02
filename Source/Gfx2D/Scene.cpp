//! @file Gfx2D/Scene.cpp
//! @brief The definition of a top-level scene owner that supports producing
//! frozen snapshots safe for consumption on a render thread.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Gfx2D/Scene.hpp"

namespace Ag {
namespace Gfx2D {

////////////////////////////////////////////////////////////////////////////////
// Scene Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an empty scene.
Scene::Scene() :
    _root(std::make_shared<GraphicGroup>())
{
}

//! @brief Constructs a scene populated with a graphic.
//! @param[in] root The graphic at the root of the scene.
Scene::Scene(const GraphicGroupSPtr &root) :
    _root(root ? root : std::make_shared<GraphicGroup>())
{
}

//! @brief Returns the live, mutable root group.
const GraphicGroupSPtr &Scene::root() const noexcept
{
    return _root;
}

//! @brief Produces a fully-frozen deep clone of the scene tree, suitable
//! for handing to a render thread.
GraphicGroupSPtr Scene::snapshot() const
{
    auto cloneArtefact = _root->createFrozenClone();

    return std::dynamic_pointer_cast<GraphicGroup>(cloneArtefact);
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
