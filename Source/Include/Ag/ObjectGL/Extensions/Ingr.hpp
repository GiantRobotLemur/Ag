//! @file Ag/ObjectGL/Extensions/Ingr.hpp
//! @brief The declaration of Ingr-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_INGR_EXTENSIONS_HPP_
#define HEADER_AG_OBJECT_GL_INGR_EXTENSIONS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief The GL_INGR_blend_func_separate extension API specification.
struct IngrBlendFuncSeparate {
    // Public Members
    void (APIENTRY *glBlendFuncSeparateINGR)(GLenum sfactorRGB,
                                             GLenum dfactorRGB,
                                             GLenum sfactorAlpha,
                                             GLenum dfactorAlpha);

    // Construction
    IngrBlendFuncSeparate();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct IngrBlendFuncSeparate

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
