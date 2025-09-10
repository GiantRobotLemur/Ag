//! @file Ag/ObjectGL/Extensions/IBM.hpp
//! @brief The declaration of IBM-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_IBM_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_IBM_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_IBM_multimode_draw_arrays extension API specification.
struct IBMMultimodeDrawArrays {
    // Public Members
    void (APIENTRY *glMultiModeDrawArrays)(const GLenum *mode,
                                           const GLint *first,
                                           const GLsizei *count,
                                           GLsizei primcount, GLint modestride);
    void (APIENTRY *glMultiModeDrawElements)(const GLenum *mode,
                                             const GLsizei *count, GLenum type,
                                             const void *const *indices,
                                             GLsizei primcount, GLint modestride);

    // Construction
    IBMMultimodeDrawArrays();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct IBMMultimodeDrawArrays

// GL_IBM_static_data extension API specification.
struct IBMStaticData {
    // Public Members
    void (APIENTRY *glFlushStaticData)(GLenum target);

    // Construction
    IBMStaticData();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct IBMStaticData

// GL_IBM_vertex_array_lists extension API specification.
struct IBMVertexArrayLists {
    // Public Members
    void (APIENTRY *glColorPointerList)(GLint size, GLenum type, GLint stride,
                                        const void **pointer, GLint ptrstride);
    void (APIENTRY *glEdgeFlagPointerList)(GLint stride,
                                           const GLboolean **pointer,
                                           GLint ptrstride);
    void (APIENTRY *glFogCoordPointerList)(GLenum type, GLint stride,
                                           const void **pointer, GLint ptrstride);
    void (APIENTRY *glIndexPointerList)(GLenum type, GLint stride,
                                        const void **pointer, GLint ptrstride);
    void (APIENTRY *glNormalPointerList)(GLenum type, GLint stride,
                                         const void **pointer, GLint ptrstride);
    void (APIENTRY *glSecondaryColorPointerList)(GLint size, GLenum type,
                                                 GLint stride,
                                                 const void **pointer,
                                                 GLint ptrstride);
    void (APIENTRY *glTexCoordPointerList)(GLint size, GLenum type, GLint stride,
                                           const void **pointer, GLint ptrstride);
    void (APIENTRY *glVertexPointerList)(GLint size, GLenum type, GLint stride,
                                         const void **pointer, GLint ptrstride);

    // Construction
    IBMVertexArrayLists();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct IBMVertexArrayLists



} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
