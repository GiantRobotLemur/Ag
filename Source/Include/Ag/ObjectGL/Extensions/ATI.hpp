//! @file Ag/ObjectGL/Extensions/ATI.hpp
//! @brief The declaration of ATI-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_ATI_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_ATI_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_ATI_draw_buffers extension API specification.
struct ATIDrawBuffers {
    // Public Members
    void (APIENTRY *glDrawBuffers)(GLsizei n, const GLenum *bufs);

    // Construction
    ATIDrawBuffers();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIDrawBuffers

// GL_ATI_element_array extension API specification.
struct ATIElementArray {
    // Public Members
    void (APIENTRY *glDrawElementArray)(GLenum mode, GLsizei count);
    void (APIENTRY *glDrawRangeElementArray)(GLenum mode, GLuint start,
                                             GLuint end, GLsizei count);
    void (APIENTRY *glElementPointer)(GLenum type, const void *pointer);

    // Construction
    ATIElementArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIElementArray

// GL_ATI_envmap_bumpmap extension API specification.
struct ATIEnvmapBumpmap {
    // Public Members
    void (APIENTRY *glGetTexBumpParameterfv)(GLenum pname, GLfloat *param);
    void (APIENTRY *glGetTexBumpParameteriv)(GLenum pname, GLint *param);
    void (APIENTRY *glTexBumpParameterfv)(GLenum pname, const GLfloat *param);
    void (APIENTRY *glTexBumpParameteriv)(GLenum pname, const GLint *param);

    // Construction
    ATIEnvmapBumpmap();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIEnvmapBumpmap

// GL_ATI_fragment_shader extension API specification.
struct ATIFragmentShader {
    // Public Members
    void (APIENTRY *glAlphaFragmentOp1)(GLenum op, GLuint dst, GLuint dstMod,
                                        GLuint arg1, GLuint arg1Rep,
                                        GLuint arg1Mod);
    void (APIENTRY *glAlphaFragmentOp2)(GLenum op, GLuint dst, GLuint dstMod,
                                        GLuint arg1, GLuint arg1Rep,
                                        GLuint arg1Mod, GLuint arg2,
                                        GLuint arg2Rep, GLuint arg2Mod);
    void (APIENTRY *glAlphaFragmentOp3)(GLenum op, GLuint dst, GLuint dstMod,
                                        GLuint arg1, GLuint arg1Rep,
                                        GLuint arg1Mod, GLuint arg2,
                                        GLuint arg2Rep, GLuint arg2Mod,
                                        GLuint arg3, GLuint arg3Rep,
                                        GLuint arg3Mod);
    void (APIENTRY *glBeginFragmentShader)();
    void (APIENTRY *glBindFragmentShader)(GLuint id);
    void (APIENTRY *glColorFragmentOp1)(GLenum op, GLuint dst, GLuint dstMask,
                                        GLuint dstMod, GLuint arg1,
                                        GLuint arg1Rep, GLuint arg1Mod);
    void (APIENTRY *glColorFragmentOp2)(GLenum op, GLuint dst, GLuint dstMask,
                                        GLuint dstMod, GLuint arg1,
                                        GLuint arg1Rep, GLuint arg1Mod,
                                        GLuint arg2, GLuint arg2Rep,
                                        GLuint arg2Mod);
    void (APIENTRY *glColorFragmentOp3)(GLenum op, GLuint dst, GLuint dstMask,
                                        GLuint dstMod, GLuint arg1,
                                        GLuint arg1Rep, GLuint arg1Mod,
                                        GLuint arg2, GLuint arg2Rep,
                                        GLuint arg2Mod, GLuint arg3,
                                        GLuint arg3Rep, GLuint arg3Mod);
    void (APIENTRY *glDeleteFragmentShader)(GLuint id);
    void (APIENTRY *glEndFragmentShader)();
    GLuint(APIENTRY *glGenFragmentShaders)(GLuint range);
    void (APIENTRY *glPassTexCoord)(GLuint dst, GLuint coord, GLenum swizzle);
    void (APIENTRY *glSampleMap)(GLuint dst, GLuint interp, GLenum swizzle);
    void (APIENTRY *glSetFragmentShaderConstant)(GLuint dst,
                                                 const GLfloat *value);

    // Construction
    ATIFragmentShader();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIFragmentShader

// GL_ATI_map_object_buffer extension API specification.
struct ATIMapObjectBuffer {
    // Public Members
    void *(APIENTRY *glMapObjectBuffer)(GLuint buffer);
    void (APIENTRY *glUnmapObjectBuffer)(GLuint buffer);

    // Construction
    ATIMapObjectBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIMapObjectBuffer

// GL_ATI_pn_triangles extension API specification.
struct ATIPnTriangles {
    // Public Members
    void (APIENTRY *glPNTrianglesf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPNTrianglesi)(GLenum pname, GLint param);

    // Construction
    ATIPnTriangles();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIPnTriangles

// GL_ATI_separate_stencil extension API specification.
struct ATISeparateStencil {
    // Public Members
    void (APIENTRY *glStencilFuncSeparate)(GLenum frontfunc, GLenum backfunc,
                                           GLint ref, GLuint mask);
    void (APIENTRY *glStencilOpSeparate)(GLenum face, GLenum sfail,
                                         GLenum dpfail, GLenum dppass);

    // Construction
    ATISeparateStencil();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATISeparateStencil

// GL_ATI_vertex_array_object extension API specification.
struct ATIVertexArrayObject {
    // Public Members
    void (APIENTRY *glArrayObject)(GLenum array, GLint size, GLenum type,
                                   GLsizei stride, GLuint buffer, GLuint offset);
    void (APIENTRY *glFreeObjectBuffer)(GLuint buffer);
    void (APIENTRY *glGetArrayObjectfv)(GLenum array, GLenum pname,
                                        GLfloat *params);
    void (APIENTRY *glGetArrayObjectiv)(GLenum array, GLenum pname,
                                        GLint *params);
    void (APIENTRY *glGetObjectBufferfv)(GLuint buffer, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetObjectBufferiv)(GLuint buffer, GLenum pname,
                                         GLint *params);
    void (APIENTRY *glGetVariantArrayObjectfv)(GLuint id, GLenum pname,
                                               GLfloat *params);
    void (APIENTRY *glGetVariantArrayObjectiv)(GLuint id, GLenum pname,
                                               GLint *params);
    GLboolean(APIENTRY *glIsObjectBuffer)(GLuint buffer);
    GLuint(APIENTRY *glNewObjectBuffer)(GLsizei size, const void *pointer,
                                        GLenum usage);
    void (APIENTRY *glUpdateObjectBuffer)(GLuint buffer, GLuint offset,
                                          GLsizei size, const void *pointer,
                                          GLenum preserve);
    void (APIENTRY *glVariantArrayObject)(GLuint id, GLenum type, GLsizei stride,
                                          GLuint buffer, GLuint offset);

    // Construction
    ATIVertexArrayObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIVertexArrayObject

// GL_ATI_vertex_attrib_array_object extension API specification.
struct ATIVertexAttribArrayObject {
    // Public Members
    void (APIENTRY *glGetVertexAttribArrayObjectfv)(GLuint index, GLenum pname,
                                                    GLfloat *params);
    void (APIENTRY *glGetVertexAttribArrayObjectiv)(GLuint index, GLenum pname,
                                                    GLint *params);
    void (APIENTRY *glVertexAttribArrayObject)(GLuint index, GLint size,
                                               GLenum type, GLboolean normalized,
                                               GLsizei stride, GLuint buffer,
                                               GLuint offset);

    // Construction
    ATIVertexAttribArrayObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIVertexAttribArrayObject

// GL_ATI_vertex_streams extension API specification.
struct ATIVertexStreams {
    // Public Members
    void (APIENTRY *glClientActiveVertexStream)(GLenum stream);
    void (APIENTRY *glNormalStream3b)(GLenum stream, GLbyte nx, GLbyte ny,
                                      GLbyte nz);
    void (APIENTRY *glNormalStream3bv)(GLenum stream, const GLbyte *coords);
    void (APIENTRY *glNormalStream3d)(GLenum stream, GLdouble nx, GLdouble ny,
                                      GLdouble nz);
    void (APIENTRY *glNormalStream3dv)(GLenum stream, const GLdouble *coords);
    void (APIENTRY *glNormalStream3f)(GLenum stream, GLfloat nx, GLfloat ny,
                                      GLfloat nz);
    void (APIENTRY *glNormalStream3fv)(GLenum stream, const GLfloat *coords);
    void (APIENTRY *glNormalStream3i)(GLenum stream, GLint nx, GLint ny,
                                      GLint nz);
    void (APIENTRY *glNormalStream3iv)(GLenum stream, const GLint *coords);
    void (APIENTRY *glNormalStream3s)(GLenum stream, GLshort nx, GLshort ny,
                                      GLshort nz);
    void (APIENTRY *glNormalStream3sv)(GLenum stream, const GLshort *coords);
    void (APIENTRY *glVertexBlendEnvf)(GLenum pname, GLfloat param);
    void (APIENTRY *glVertexBlendEnvi)(GLenum pname, GLint param);
    void (APIENTRY *glVertexStream1d)(GLenum stream, GLdouble x);
    void (APIENTRY *glVertexStream1dv)(GLenum stream, const GLdouble *coords);
    void (APIENTRY *glVertexStream1f)(GLenum stream, GLfloat x);
    void (APIENTRY *glVertexStream1fv)(GLenum stream, const GLfloat *coords);
    void (APIENTRY *glVertexStream1i)(GLenum stream, GLint x);
    void (APIENTRY *glVertexStream1iv)(GLenum stream, const GLint *coords);
    void (APIENTRY *glVertexStream1s)(GLenum stream, GLshort x);
    void (APIENTRY *glVertexStream1sv)(GLenum stream, const GLshort *coords);
    void (APIENTRY *glVertexStream2d)(GLenum stream, GLdouble x, GLdouble y);
    void (APIENTRY *glVertexStream2dv)(GLenum stream, const GLdouble *coords);
    void (APIENTRY *glVertexStream2f)(GLenum stream, GLfloat x, GLfloat y);
    void (APIENTRY *glVertexStream2fv)(GLenum stream, const GLfloat *coords);
    void (APIENTRY *glVertexStream2i)(GLenum stream, GLint x, GLint y);
    void (APIENTRY *glVertexStream2iv)(GLenum stream, const GLint *coords);
    void (APIENTRY *glVertexStream2s)(GLenum stream, GLshort x, GLshort y);
    void (APIENTRY *glVertexStream2sv)(GLenum stream, const GLshort *coords);
    void (APIENTRY *glVertexStream3d)(GLenum stream, GLdouble x, GLdouble y,
                                      GLdouble z);
    void (APIENTRY *glVertexStream3dv)(GLenum stream, const GLdouble *coords);
    void (APIENTRY *glVertexStream3f)(GLenum stream, GLfloat x, GLfloat y,
                                      GLfloat z);
    void (APIENTRY *glVertexStream3fv)(GLenum stream, const GLfloat *coords);
    void (APIENTRY *glVertexStream3i)(GLenum stream, GLint x, GLint y, GLint z);
    void (APIENTRY *glVertexStream3iv)(GLenum stream, const GLint *coords);
    void (APIENTRY *glVertexStream3s)(GLenum stream, GLshort x, GLshort y,
                                      GLshort z);
    void (APIENTRY *glVertexStream3sv)(GLenum stream, const GLshort *coords);
    void (APIENTRY *glVertexStream4d)(GLenum stream, GLdouble x, GLdouble y,
                                      GLdouble z, GLdouble w);
    void (APIENTRY *glVertexStream4dv)(GLenum stream, const GLdouble *coords);
    void (APIENTRY *glVertexStream4f)(GLenum stream, GLfloat x, GLfloat y,
                                      GLfloat z, GLfloat w);
    void (APIENTRY *glVertexStream4fv)(GLenum stream, const GLfloat *coords);
    void (APIENTRY *glVertexStream4i)(GLenum stream, GLint x, GLint y, GLint z,
                                      GLint w);
    void (APIENTRY *glVertexStream4iv)(GLenum stream, const GLint *coords);
    void (APIENTRY *glVertexStream4s)(GLenum stream, GLshort x, GLshort y,
                                      GLshort z, GLshort w);
    void (APIENTRY *glVertexStream4sv)(GLenum stream, const GLshort *coords);

    // Construction
    ATIVertexStreams();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ATIVertexStreams

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
