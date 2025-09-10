//! @file ObjectGL/Extensions/Khr.cpp
//! @brief The definition of Khronos-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Khr.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __KHRBlendEquationAdvancedEntryPoints[] = {
    { offsetof(KHRBlendEquationAdvanced, glBlendBarrier), "glBlendBarrierKHR" },
};

static const EntryOffset __KHRParallelShaderCompileEntryPoints[] = {
    { offsetof(KHRParallelShaderCompile, glMaxShaderCompilerThreads), "glMaxShaderCompilerThreadsKHR" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// KHRBlendEquationAdvanced Member Definitions
////////////////////////////////////////////////////////////////////////////////
KHRBlendEquationAdvanced::KHRBlendEquationAdvanced()
{
    std::for_each_n(__KHRBlendEquationAdvancedEntryPoints,
                    std::size(__KHRBlendEquationAdvancedEntryPoints),
                    ClearEntryPoint(this));
}

bool KHRBlendEquationAdvanced::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_KHR_blend_equation_advanced");
}

void KHRBlendEquationAdvanced::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__KHRBlendEquationAdvancedEntryPoints,
                    std::size(__KHRBlendEquationAdvancedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// KHRParallelShaderCompile Member Definitions
////////////////////////////////////////////////////////////////////////////////
KHRParallelShaderCompile::KHRParallelShaderCompile()
{
    std::for_each_n(__KHRParallelShaderCompileEntryPoints,
                    std::size(__KHRParallelShaderCompileEntryPoints),
                    ClearEntryPoint(this));
}

bool KHRParallelShaderCompile::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_KHR_parallel_shader_compile");
}

void KHRParallelShaderCompile::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__KHRParallelShaderCompileEntryPoints,
                    std::size(__KHRParallelShaderCompileEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

