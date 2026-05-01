//! @file Gfx2D/Scene.cpp
//! @brief The definition of a top-level scene owner that supports producing
//! frozen snapshots safe for consumption on a render thread.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2025-2026
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
Scene::Scene() :
    _root(std::make_shared<GraphicGroup>())
{
}

Scene::Scene(const GraphicGroupSPtr &root) :
    _root(root ? root : std::make_shared<GraphicGroup>())
{
}

const GraphicGroupSPtr &Scene::root() const noexcept
{
    return _root;
}

GraphicGroupSPtr Scene::snapshot() const
{
    auto cloneArtefact = _root->clone();
    auto cloned = std::dynamic_pointer_cast<GraphicGroup>(cloneArtefact);

    if (cloned)
        cloned->freeze();

    return cloned;
}

}} // namespace Ag::Gfx2D
////////////////////////////////////////////////////////////////////////////////
