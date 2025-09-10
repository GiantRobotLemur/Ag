//! @file Ag/ObjectGL/Extensions/Ovr.hpp
//! @brief The declaration of Ovr-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_OVR_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OVR_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_OVR_multiview extension API specification.
struct OvrMultiview {
    // Public Members
    void (APIENTRY *glFramebufferTextureMultiviewOVR)(GLenum target,
                                                      GLenum attachment,
                                                      GLuint texture,
                                                      GLint level,
                                                      GLint baseViewIndex,
                                                      GLsizei numViews);
    void (APIENTRY *glNamedFramebufferTextureMultiviewOVR)(GLuint framebuffer,
                                                           GLenum attachment,
                                                           GLuint texture,
                                                           GLint level,
                                                           GLint baseViewIndex,
                                                           GLsizei numViews);

    // Construction
    OvrMultiview();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OvrMultiview

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
