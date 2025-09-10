//! @file ObjectGL/Extensions/HP.cpp
//! @brief The definition of HP-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/HP.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __HPImageTransformEntryPoints[] = {
    { offsetof(HPImageTransform, glGetImageTransformParameterfv), "glGetImageTransformParameterfvHP" },
    { offsetof(HPImageTransform, glGetImageTransformParameteriv), "glGetImageTransformParameterivHP" },
    { offsetof(HPImageTransform, glImageTransformParameterf), "glImageTransformParameterfHP" },
    { offsetof(HPImageTransform, glImageTransformParameterfv), "glImageTransformParameterfvHP" },
    { offsetof(HPImageTransform, glImageTransformParameteri), "glImageTransformParameteriHP" },
    { offsetof(HPImageTransform, glImageTransformParameteriv), "glImageTransformParameterivHP" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// HPImageTransform Member Definitions
////////////////////////////////////////////////////////////////////////////////
HPImageTransform::HPImageTransform()
{
    std::for_each_n(__HPImageTransformEntryPoints,
                    std::size(__HPImageTransformEntryPoints),
                    ClearEntryPoint(this));
}

bool HPImageTransform::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_HP_image_transform");
}

void HPImageTransform::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__HPImageTransformEntryPoints,
                    std::size(__HPImageTransformEntryPoints),
                    ResolveEntryPoint(this, resolver));
}



} // namespace gl
////////////////////////////////////////////////////////////////////////////////

