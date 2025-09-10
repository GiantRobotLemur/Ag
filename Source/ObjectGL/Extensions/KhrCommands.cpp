//! @file ObjectGL/Extensions/KhrCommands.cpp
//! @brief The definition of Khronos-specific extensions to the OpenGL Command
//! set wrappers.
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
#include "Ag/ObjectGL/Extensions/KhrCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// KHRBlendEquationAdvancedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_KHR_blend_equation_advanced extension.
KHRBlendEquationAdvancedAPI::KHRBlendEquationAdvancedAPI() :
    BaseExtension("GL_KHR_blend_equation_advanced")
{
}

// Grant read-only access to the underlying function pointers.
const KHRBlendEquationAdvanced &KHRBlendEquationAdvancedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_KHR_blend_equation_advanced entry points.
void KHRBlendEquationAdvancedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendBarrierKHR().
void KHRBlendEquationAdvancedAPI::blendBarrier() const
{
    static const char *fnName = "glBlendBarrierKHR";

    beforeCommand(fnName, _api.glBlendBarrier);
    _api.glBlendBarrier();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// KHRParallelShaderCompileAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_KHR_parallel_shader_compile extension.
KHRParallelShaderCompileAPI::KHRParallelShaderCompileAPI() :
    BaseExtension("GL_KHR_parallel_shader_compile")
{
}

// Grant read-only access to the underlying function pointers.
const KHRParallelShaderCompile &KHRParallelShaderCompileAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_KHR_parallel_shader_compile entry points.
void KHRParallelShaderCompileAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMaxShaderCompilerThreadsKHR().
void KHRParallelShaderCompileAPI::maxShaderCompilerThreads(GLuint count) const
{
    static const char *fnName = "glMaxShaderCompilerThreadsKHR";

    beforeCommand(fnName, _api.glMaxShaderCompilerThreads);
    _api.glMaxShaderCompilerThreads(count);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

