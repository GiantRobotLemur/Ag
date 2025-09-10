//! @file Ag/ObjectGL/Extensions/KhrCommands.hpp
//! @brief The declaration of Khronos-specific extensions to the OpenGL Command set
//! wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_KHR_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_KHR_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "Khr.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_KHR_blend_equation_advanced extension API.
class KHRBlendEquationAdvancedAPI : public BaseExtension
{
public:
    // Construction
    KHRBlendEquationAdvancedAPI();

    // Accessors
    const KHRBlendEquationAdvanced &getRawAPI() const;

    // Operations
    void blendBarrier() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    KHRBlendEquationAdvanced _api;
};

// Manages the entry points for the GL_KHR_parallel_shader_compile extension API.
class KHRParallelShaderCompileAPI : public BaseExtension
{
public:
    // Construction
    KHRParallelShaderCompileAPI();

    // Accessors
    const KHRParallelShaderCompile &getRawAPI() const;

    // Operations
    void maxShaderCompilerThreads(GLuint count) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    KHRParallelShaderCompile _api;
};



} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
