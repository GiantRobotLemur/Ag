//! @file Ag/ObjectGL/Extensions/Apple.hpp
//! @brief The declaration of Apple-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_APPLE_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_APPLE_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_APPLE_element_array extension API specification.
struct APPLEElementArray {
    // Public Members
    void (APIENTRY *glDrawElementArray)(GLenum mode, GLint first, GLsizei count);
    void (APIENTRY *glDrawRangeElementArray)(GLenum mode, GLuint start,
                                             GLuint end, GLint first,
                                             GLsizei count);
    void (APIENTRY *glElementPointer)(GLenum type, const void *pointer);
    void (APIENTRY *glMultiDrawElementArray)(GLenum mode, const GLint *first,
                                             const GLsizei *count,
                                             GLsizei primcount);
    void (APIENTRY *glMultiDrawRangeElementArray)(GLenum mode, GLuint start,
                                                  GLuint end, const GLint *first,
                                                  const GLsizei *count,
                                                  GLsizei primcount);

    // Construction
    APPLEElementArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEElementArray

// GL_APPLE_fence extension API specification.
struct APPLEFence {
    // Public Members
    void (APIENTRY *glDeleteFences)(GLsizei n, const GLuint *fences);
    void (APIENTRY *glFinishFence)(GLuint fence);
    void (APIENTRY *glFinishObject)(GLenum object, GLint name);
    void (APIENTRY *glGenFences)(GLsizei n, GLuint *fences);
    GLboolean(APIENTRY *glIsFence)(GLuint fence);
    void (APIENTRY *glSetFence)(GLuint fence);
    GLboolean(APIENTRY *glTestFence)(GLuint fence);
    GLboolean(APIENTRY *glTestObject)(GLenum object, GLuint name);

    // Construction
    APPLEFence();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEFence

// GL_APPLE_flush_buffer_range extension API specification.
struct APPLEFlushBufferRange {
    // Public Members
    void (APIENTRY *glBufferParameteri)(GLenum target, GLenum pname, GLint param);
    void (APIENTRY *glFlushMappedBufferRange)(GLenum target, GLintptr offset,
                                              GLsizeiptr size);

    // Construction
    APPLEFlushBufferRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEFlushBufferRange

// GL_APPLE_object_purgeable extension API specification.
struct APPLEObjectPurgeable {
    // Public Members
    void (APIENTRY *glGetObjectParameteriv)(GLenum objectType, GLuint name,
                                            GLenum pname, GLint *params);
    GLenum(APIENTRY *glObjectPurgeable)(GLenum objectType, GLuint name,
                                        GLenum option);
    GLenum(APIENTRY *glObjectUnpurgeable)(GLenum objectType, GLuint name,
                                          GLenum option);

   // Construction
    APPLEObjectPurgeable();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEObjectPurgeable

// GL_APPLE_texture_range extension API specification.
struct APPLETextureRange {
    // Public Members
    void (APIENTRY *glGetTexParameterPointerv)(GLenum target, GLenum pname,
                                               void **params);
    void (APIENTRY *glTextureRange)(GLenum target, GLsizei length,
                                    const void *pointer);

    // Construction
    APPLETextureRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLETextureRange

// GL_APPLE_vertex_array_object extension API specification.
struct APPLEVertexArrayObject {
    // Public Members
    void (APIENTRY *glBindVertexArray)(GLuint array);
    void (APIENTRY *glDeleteVertexArrays)(GLsizei n, const GLuint *arrays);
    void (APIENTRY *glGenVertexArrays)(GLsizei n, GLuint *arrays);
    GLboolean(APIENTRY *glIsVertexArray)(GLuint array);

    // Construction
    APPLEVertexArrayObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEVertexArrayObject

// GL_APPLE_vertex_array_range extension API specification.
struct APPLEVertexArrayRange {
    // Public Members
    void (APIENTRY *glFlushVertexArrayRange)(GLsizei length, void *pointer);
    void (APIENTRY *glVertexArrayParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glVertexArrayRange)(GLsizei length, void *pointer);

    // Construction
    APPLEVertexArrayRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEVertexArrayRange

// GL_APPLE_vertex_program_evaluators extension API specification.
struct APPLEVertexProgramEvaluators {
    // Public Members
    void (APIENTRY *glDisableVertexAttrib)(GLuint index, GLenum pname);
    void (APIENTRY *glEnableVertexAttrib)(GLuint index, GLenum pname);
    GLboolean(APIENTRY *glIsVertexAttribEnabled)(GLuint index, GLenum pname);
    void (APIENTRY *glMapVertexAttrib1d)(GLuint index, GLuint size, GLdouble u1,
                                         GLdouble u2, GLint stride, GLint order,
                                         const GLdouble *points);
    void (APIENTRY *glMapVertexAttrib1f)(GLuint index, GLuint size, GLfloat u1,
                                         GLfloat u2, GLint stride, GLint order,
                                         const GLfloat *points);
    void (APIENTRY *glMapVertexAttrib2d)(GLuint index, GLuint size, GLdouble u1,
                                         GLdouble u2, GLint ustride,
                                         GLint uorder, GLdouble v1, GLdouble v2,
                                         GLint vstride, GLint vorder,
                                         const GLdouble *points);
    void (APIENTRY *glMapVertexAttrib2f)(GLuint index, GLuint size, GLfloat u1,
                                         GLfloat u2, GLint ustride, GLint uorder,
                                         GLfloat v1, GLfloat v2, GLint vstride,
                                         GLint vorder, const GLfloat *points);

    // Construction
    APPLEVertexProgramEvaluators();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct APPLEVertexProgramEvaluators

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
