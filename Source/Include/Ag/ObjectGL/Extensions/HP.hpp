//! @file Ag/ObjectGL/Extensions/HP.hpp
//! @brief The declaration of HP-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_HP_EXTENSIONS_HPP_
#define HEADER_AG_OBJECT_GL_HP_EXTENSIONS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief The GL_HP_image_transform extension API specification.
struct HPImageTransform {
    // Public Members
    void (APIENTRY *glGetImageTransformParameterfv)(GLenum target, GLenum pname,
                                                    GLfloat *params);
    void (APIENTRY *glGetImageTransformParameteriv)(GLenum target, GLenum pname,
                                                    GLint *params);
    void (APIENTRY *glImageTransformParameterf)(GLenum target, GLenum pname,
                                                GLfloat param);
    void (APIENTRY *glImageTransformParameterfv)(GLenum target, GLenum pname,
                                                 const GLfloat *params);
    void (APIENTRY *glImageTransformParameteri)(GLenum target, GLenum pname,
                                                GLint param);
    void (APIENTRY *glImageTransformParameteriv)(GLenum target, GLenum pname,
                                                 const GLint *params);

    // Construction
    HPImageTransform();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct HPImageTransform

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
