//! @file Ag/ObjectGL/Extensions/3DFX.hpp
//! @brief The declaration of 3DFX-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_3DFX_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_3DFX_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_3DFX_tbuffer extension API specification.
struct _3DFXTbuffer {
    // Public Members
    void (APIENTRY *glTbufferMask)(GLuint mask);

    // Construction
    _3DFXTbuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct _3DFXTbuffer

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
