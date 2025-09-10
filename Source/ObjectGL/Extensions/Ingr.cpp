//! @file ObjectGL/Extensions/Ingr.cpp
//! @brief The definition of Xxx-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Ingr.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __IngrBlendFuncSeparateEntryPoints[] = {
    { offsetof(IngrBlendFuncSeparate, glBlendFuncSeparateINGR), "glBlendFuncSeparateINGR" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// IngrBlendFuncSeparate Member Definitions
////////////////////////////////////////////////////////////////////////////////
IngrBlendFuncSeparate::IngrBlendFuncSeparate()
{
    std::for_each_n(__IngrBlendFuncSeparateEntryPoints,
                    std::size(__IngrBlendFuncSeparateEntryPoints),
                    ClearEntryPoint(this));
}

bool IngrBlendFuncSeparate::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_INGR_blend_func_separate");
}

void IngrBlendFuncSeparate::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__IngrBlendFuncSeparateEntryPoints,
                    std::size(__IngrBlendFuncSeparateEntryPoints),
                    ResolveEntryPoint(this, resolver));
}




} // namespace gl
////////////////////////////////////////////////////////////////////////////////

