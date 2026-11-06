//! @file Ag/ObjectGL/Extensions/PGI.hpp
//! @brief The declaration of PGI-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_PGI_EXTENSIONS_HPP_
#define HEADER_AG_OBJECT_GL_PGI_EXTENSIONS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief The GL_PGI_misc_hints extension API specification.
struct PGIMiscHints {
    // Public Members
    void (APIENTRY *glHint)(GLenum target, GLint mode);

    // Construction
    PGIMiscHints();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct PGIMiscHints

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
