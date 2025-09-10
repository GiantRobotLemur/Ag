//! @file Ag/ObjectGL/Extensions/Khr.hpp
//! @brief The declaration of Khronos-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_KHR_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_KHR_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_KHR_blend_equation_advanced extension API specification.
struct KHRBlendEquationAdvanced {
    // Public Members
    void (APIENTRY *glBlendBarrier)();

    // Construction
    KHRBlendEquationAdvanced();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct KHRBlendEquationAdvanced

// GL_KHR_parallel_shader_compile extension API specification.
struct KHRParallelShaderCompile {
    // Public Members
    void (APIENTRY *glMaxShaderCompilerThreads)(GLuint count);

    // Construction
    KHRParallelShaderCompile();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct KHRParallelShaderCompile

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
