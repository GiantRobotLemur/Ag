//! @file Ag/ObjectGL/Extensions/Ext.hpp
//! @brief The declaration of generic extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_EXT_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_EXT_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

#ifdef _WIN32
#include "../WGL_Types.hpp"
#endif // ifdef _WIN32

#ifdef _USES_GLX
#include "../GLX_Types.hpp"
#endif // ifdef _USES_GLX

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_EXT_EGL_image_storage extension API specification.
struct EXTEglImageStorage {
    // Public Members
    void (APIENTRY *glEGLImageTargetTexStorage)(GLenum target,
                                                GLeglImageOES image,
                                                const GLint *attrib_list);
    void (APIENTRY *glEGLImageTargetTextureStorage)(GLuint texture,
                                                    GLeglImageOES image,
                                                    const GLint *attrib_list);

    // Construction
    EXTEglImageStorage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTEglImageStorage

// GL_EXT_bindable_uniform extension API specification.
struct EXTBindableUniform {
    // Public Members
    GLint(APIENTRY *glGetUniformBufferSize)(GLuint program, GLint location);
    GLintptr(APIENTRY *glGetUniformOffset)(GLuint program, GLint location);
    void (APIENTRY *glUniformBuffer)(GLuint program, GLint location,
                                     GLuint buffer);

    // Construction
    EXTBindableUniform();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTBindableUniform

// GL_EXT_blend_color extension API specification.
struct EXTBlendColor {
    // Public Members
    void (APIENTRY *glBlendColor)(GLfloat red, GLfloat green, GLfloat blue,
                                  GLfloat alpha);

    // Construction
    EXTBlendColor();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTBlendColor

// GL_EXT_blend_equation_separate extension API specification.
struct EXTBlendEquationSeparate {
    // Public Members
    void (APIENTRY *glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);

    // Construction
    EXTBlendEquationSeparate();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTBlendEquationSeparate

// GL_EXT_blend_func_separate extension API specification.
struct EXTBlendFuncSeparate {
    // Public Members
    void (APIENTRY *glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB,
                                         GLenum sfactorAlpha,
                                         GLenum dfactorAlpha);

    // Construction
    EXTBlendFuncSeparate();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTBlendFuncSeparate

// GL_EXT_blend_minmax extension API specification.
struct EXTBlendMinmax {
    // Public Members
    void (APIENTRY *glBlendEquation)(GLenum mode);

    // Construction
    EXTBlendMinmax();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTBlendMinmax

// GL_EXT_color_subtable extension API specification.
struct EXTColorSubtable {
    // Public Members
    void (APIENTRY *glColorSubTable)(GLenum target, GLsizei start, GLsizei count,
                                     GLenum format, GLenum type,
                                     const void *data);
    void (APIENTRY *glCopyColorSubTable)(GLenum target, GLsizei start, GLint x,
                                         GLint y, GLsizei width);

    // Construction
    EXTColorSubtable();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTColorSubtable

// GL_EXT_compiled_vertex_array extension API specification.
struct EXTCompiledVertexArray {
    // Public Members
    void (APIENTRY *glLockArrays)(GLint first, GLsizei count);
    void (APIENTRY *glUnlockArrays)();

    // Construction
    EXTCompiledVertexArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTCompiledVertexArray

// GL_EXT_convolution extension API specification.
struct EXTConvolution {
    // Public Members
    void (APIENTRY *glConvolutionFilter1D)(GLenum target, GLenum internalformat,
                                           GLsizei width, GLenum format,
                                           GLenum type, const void *image);
    void (APIENTRY *glConvolutionFilter2D)(GLenum target, GLenum internalformat,
                                           GLsizei width, GLsizei height,
                                           GLenum format, GLenum type,
                                           const void *image);
    void (APIENTRY *glConvolutionParameterf)(GLenum target, GLenum pname,
                                             GLfloat params);
    void (APIENTRY *glConvolutionParameterfv)(GLenum target, GLenum pname,
                                              const GLfloat *params);
    void (APIENTRY *glConvolutionParameteri)(GLenum target, GLenum pname,
                                             GLint params);
    void (APIENTRY *glConvolutionParameteriv)(GLenum target, GLenum pname,
                                              const GLint *params);
    void (APIENTRY *glCopyConvolutionFilter1D)(GLenum target,
                                               GLenum internalformat, GLint x,
                                               GLint y, GLsizei width);
    void (APIENTRY *glCopyConvolutionFilter2D)(GLenum target,
                                               GLenum internalformat, GLint x,
                                               GLint y, GLsizei width,
                                               GLsizei height);
    void (APIENTRY *glGetConvolutionFilter)(GLenum target, GLenum format,
                                            GLenum type, void *image);
    void (APIENTRY *glGetConvolutionParameterfv)(GLenum target, GLenum pname,
                                                 GLfloat *params);
    void (APIENTRY *glGetConvolutionParameteriv)(GLenum target, GLenum pname,
                                                 GLint *params);
    void (APIENTRY *glGetSeparableFilter)(GLenum target, GLenum format,
                                          GLenum type, void *row, void *column,
                                          void *span);
    void (APIENTRY *glSeparableFilter2D)(GLenum target, GLenum internalformat,
                                         GLsizei width, GLsizei height,
                                         GLenum format, GLenum type,
                                         const void *row, const void *column);

    // Construction
    EXTConvolution();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTConvolution

// GL_EXT_coordinate_frame extension API specification.
struct EXTCoordinateFrame {
    // Public Members
    void (APIENTRY *glBinormal3b)(GLbyte bx, GLbyte by, GLbyte bz);
    void (APIENTRY *glBinormal3bv)(const GLbyte *v);
    void (APIENTRY *glBinormal3d)(GLdouble bx, GLdouble by, GLdouble bz);
    void (APIENTRY *glBinormal3dv)(const GLdouble *v);
    void (APIENTRY *glBinormal3f)(GLfloat bx, GLfloat by, GLfloat bz);
    void (APIENTRY *glBinormal3fv)(const GLfloat *v);
    void (APIENTRY *glBinormal3i)(GLint bx, GLint by, GLint bz);
    void (APIENTRY *glBinormal3iv)(const GLint *v);
    void (APIENTRY *glBinormal3s)(GLshort bx, GLshort by, GLshort bz);
    void (APIENTRY *glBinormal3sv)(const GLshort *v);
    void (APIENTRY *glBinormalPointer)(GLenum type, GLsizei stride,
                                       const void *pointer);
    void (APIENTRY *glTangent3b)(GLbyte tx, GLbyte ty, GLbyte tz);
    void (APIENTRY *glTangent3bv)(const GLbyte *v);
    void (APIENTRY *glTangent3d)(GLdouble tx, GLdouble ty, GLdouble tz);
    void (APIENTRY *glTangent3dv)(const GLdouble *v);
    void (APIENTRY *glTangent3f)(GLfloat tx, GLfloat ty, GLfloat tz);
    void (APIENTRY *glTangent3fv)(const GLfloat *v);
    void (APIENTRY *glTangent3i)(GLint tx, GLint ty, GLint tz);
    void (APIENTRY *glTangent3iv)(const GLint *v);
    void (APIENTRY *glTangent3s)(GLshort tx, GLshort ty, GLshort tz);
    void (APIENTRY *glTangent3sv)(const GLshort *v);
    void (APIENTRY *glTangentPointer)(GLenum type, GLsizei stride,
                                      const void *pointer);

    // Construction
    EXTCoordinateFrame();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTCoordinateFrame

// GL_EXT_copy_texture extension API specification.
struct EXTCopyTexture {
    // Public Members
    void (APIENTRY *glCopyTexImage1D)(GLenum target, GLint level,
                                      GLenum internalformat, GLint x, GLint y,
                                      GLsizei width, GLint border);
    void (APIENTRY *glCopyTexImage2D)(GLenum target, GLint level,
                                      GLenum internalformat, GLint x, GLint y,
                                      GLsizei width, GLsizei height,
                                      GLint border);
    void (APIENTRY *glCopyTexSubImage1D)(GLenum target, GLint level,
                                         GLint xoffset, GLint x, GLint y,
                                         GLsizei width);
    void (APIENTRY *glCopyTexSubImage2D)(GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset, GLint x,
                                         GLint y, GLsizei width, GLsizei height);
    void (APIENTRY *glCopyTexSubImage3D)(GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLint x, GLint y,
                                         GLsizei width, GLsizei height);

    // Construction
    EXTCopyTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTCopyTexture

// GL_EXT_cull_vertex extension API specification.
struct EXTCullVertex {
    // Public Members
    void (APIENTRY *glCullParameterdv)(GLenum pname, GLdouble *params);
    void (APIENTRY *glCullParameterfv)(GLenum pname, GLfloat *params);

    // Construction
    EXTCullVertex();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTCullVertex

// GL_EXT_debug_label extension API specification.
struct EXTDebugLabel {
    // Public Members
    void (APIENTRY *glGetObjectLabel)(GLenum type, GLuint object,
                                      GLsizei bufSize, GLsizei *length,
                                      GLchar *label);
    void (APIENTRY *glLabelObject)(GLenum type, GLuint object, GLsizei length,
                                   const GLchar *label);

    // Construction
    EXTDebugLabel();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDebugLabel

// GL_EXT_debug_marker extension API specification.
struct EXTDebugMarker {
    // Public Members
    void (APIENTRY *glInsertEventMarker)(GLsizei length, const GLchar *marker);
    void (APIENTRY *glPopGroupMarker)();
    void (APIENTRY *glPushGroupMarker)(GLsizei length, const GLchar *marker);

    // Construction
    EXTDebugMarker();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDebugMarker

// GL_EXT_depth_bounds_test extension API specification.
struct EXTDepthBoundsTest {
    // Public Members
    void (APIENTRY *glDepthBounds)(GLclampd zmin, GLclampd zmax);

    // Construction
    EXTDepthBoundsTest();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDepthBoundsTest

// GL_EXT_direct_state_access extension API specification.
// DSA extension doesn't identify which interfaces are core profile and keeps getting expanded. This is in sync with revision 34, 2010/09/07
struct EXTDirectStateAccess {
    // Public Members
    void (APIENTRY *glBindMultiTexture)(GLenum texunit, GLenum target,
                                        GLuint texture);
    GLenum(APIENTRY *glCheckNamedFramebufferStatus)(GLuint framebuffer,
                                                    GLenum target);
    void (APIENTRY *glClearNamedBufferData)(GLuint buffer, GLenum internalformat,
                                            GLenum format, GLenum type,
                                            const void *data);
    void (APIENTRY *glClearNamedBufferSubData)(GLuint buffer,
                                               GLenum internalformat,
                                               GLsizeiptr offset,
                                               GLsizeiptr size, GLenum format,
                                               GLenum type, const void *data);
    void (APIENTRY *glClientAttribDefault)(GLbitfield mask);
    void (APIENTRY *glCompressedMultiTexImage1D)(GLenum texunit, GLenum target,
                                                 GLint level,
                                                 GLenum internalformat,
                                                 GLsizei width, GLint border,
                                                 GLsizei imageSize,
                                                 const void *bits);
    void (APIENTRY *glCompressedMultiTexImage2D)(GLenum texunit, GLenum target,
                                                 GLint level,
                                                 GLenum internalformat,
                                                 GLsizei width, GLsizei height,
                                                 GLint border, GLsizei imageSize,
                                                 const void *bits);
    void (APIENTRY *glCompressedMultiTexImage3D)(GLenum texunit, GLenum target,
                                                 GLint level,
                                                 GLenum internalformat,
                                                 GLsizei width, GLsizei height,
                                                 GLsizei depth, GLint border,
                                                 GLsizei imageSize,
                                                 const void *bits);
    void (APIENTRY *glCompressedMultiTexSubImage1D)(GLenum texunit,
                                                    GLenum target, GLint level,
                                                    GLint xoffset, GLsizei width,
                                                    GLenum format,
                                                    GLsizei imageSize,
                                                    const void *bits);
    void (APIENTRY *glCompressedMultiTexSubImage2D)(GLenum texunit,
                                                    GLenum target, GLint level,
                                                    GLint xoffset, GLint yoffset,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLenum format,
                                                    GLsizei imageSize,
                                                    const void *bits);
    void (APIENTRY *glCompressedMultiTexSubImage3D)(GLenum texunit,
                                                    GLenum target, GLint level,
                                                    GLint xoffset, GLint yoffset,
                                                    GLint zoffset, GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth, GLenum format,
                                                    GLsizei imageSize,
                                                    const void *bits);
    void (APIENTRY *glCompressedTextureImage1D)(GLuint texture, GLenum target,
                                                GLint level,
                                                GLenum internalformat,
                                                GLsizei width, GLint border,
                                                GLsizei imageSize,
                                                const void *bits);
    void (APIENTRY *glCompressedTextureImage2D)(GLuint texture, GLenum target,
                                                GLint level,
                                                GLenum internalformat,
                                                GLsizei width, GLsizei height,
                                                GLint border, GLsizei imageSize,
                                                const void *bits);
    void (APIENTRY *glCompressedTextureImage3D)(GLuint texture, GLenum target,
                                                GLint level,
                                                GLenum internalformat,
                                                GLsizei width, GLsizei height,
                                                GLsizei depth, GLint border,
                                                GLsizei imageSize,
                                                const void *bits);
    void (APIENTRY *glCompressedTextureSubImage1D)(GLuint texture, GLenum target,
                                                   GLint level, GLint xoffset,
                                                   GLsizei width, GLenum format,
                                                   GLsizei imageSize,
                                                   const void *bits);
    void (APIENTRY *glCompressedTextureSubImage2D)(GLuint texture, GLenum target,
                                                   GLint level, GLint xoffset,
                                                   GLint yoffset, GLsizei width,
                                                   GLsizei height, GLenum format,
                                                   GLsizei imageSize,
                                                   const void *bits);
    void (APIENTRY *glCompressedTextureSubImage3D)(GLuint texture, GLenum target,
                                                   GLint level, GLint xoffset,
                                                   GLint yoffset, GLint zoffset,
                                                   GLsizei width, GLsizei height,
                                                   GLsizei depth, GLenum format,
                                                   GLsizei imageSize,
                                                   const void *bits);
    void (APIENTRY *glCopyMultiTexImage1D)(GLenum texunit, GLenum target,
                                           GLint level, GLenum internalformat,
                                           GLint x, GLint y, GLsizei width,
                                           GLint border);
    void (APIENTRY *glCopyMultiTexImage2D)(GLenum texunit, GLenum target,
                                           GLint level, GLenum internalformat,
                                           GLint x, GLint y, GLsizei width,
                                           GLsizei height, GLint border);
    void (APIENTRY *glCopyMultiTexSubImage1D)(GLenum texunit, GLenum target,
                                              GLint level, GLint xoffset,
                                              GLint x, GLint y, GLsizei width);
    void (APIENTRY *glCopyMultiTexSubImage2D)(GLenum texunit, GLenum target,
                                              GLint level, GLint xoffset,
                                              GLint yoffset, GLint x, GLint y,
                                              GLsizei width, GLsizei height);
    void (APIENTRY *glCopyMultiTexSubImage3D)(GLenum texunit, GLenum target,
                                              GLint level, GLint xoffset,
                                              GLint yoffset, GLint zoffset,
                                              GLint x, GLint y, GLsizei width,
                                              GLsizei height);
    void (APIENTRY *glCopyTextureImage1D)(GLuint texture, GLenum target,
                                          GLint level, GLenum internalformat,
                                          GLint x, GLint y, GLsizei width,
                                          GLint border);
    void (APIENTRY *glCopyTextureImage2D)(GLuint texture, GLenum target,
                                          GLint level, GLenum internalformat,
                                          GLint x, GLint y, GLsizei width,
                                          GLsizei height, GLint border);
    void (APIENTRY *glCopyTextureSubImage1D)(GLuint texture, GLenum target,
                                             GLint level, GLint xoffset, GLint x,
                                             GLint y, GLsizei width);
    void (APIENTRY *glCopyTextureSubImage2D)(GLuint texture, GLenum target,
                                             GLint level, GLint xoffset,
                                             GLint yoffset, GLint x, GLint y,
                                             GLsizei width, GLsizei height);
    void (APIENTRY *glCopyTextureSubImage3D)(GLuint texture, GLenum target,
                                             GLint level, GLint xoffset,
                                             GLint yoffset, GLint zoffset,
                                             GLint x, GLint y, GLsizei width,
                                             GLsizei height);
    void (APIENTRY *glDisableClientStateIndexed)(GLenum array, GLuint index);
    void (APIENTRY *glDisableClientStatei)(GLenum array, GLuint index);
    void (APIENTRY *glDisableIndexed)(GLenum target, GLuint index);
    void (APIENTRY *glDisableVertexArrayAttrib)(GLuint vaobj, GLuint index);
    void (APIENTRY *glDisableVertexArray)(GLuint vaobj, GLenum array);
    void (APIENTRY *glEnableClientStateIndexed)(GLenum array, GLuint index);
    void (APIENTRY *glEnableClientStatei)(GLenum array, GLuint index);
    void (APIENTRY *glEnableIndexed)(GLenum target, GLuint index);
    void (APIENTRY *glEnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
    void (APIENTRY *glEnableVertexArray)(GLuint vaobj, GLenum array);
    void (APIENTRY *glFlushMappedNamedBufferRange)(GLuint buffer,
                                                   GLintptr offset,
                                                   GLsizeiptr length);
    void (APIENTRY *glFramebufferDrawBuffer)(GLuint framebuffer, GLenum mode);
    void (APIENTRY *glFramebufferDrawBuffers)(GLuint framebuffer, GLsizei n,
                                              const GLenum *bufs);
    void (APIENTRY *glFramebufferReadBuffer)(GLuint framebuffer, GLenum mode);
    void (APIENTRY *glGenerateMultiTexMipmap)(GLenum texunit, GLenum target);
    void (APIENTRY *glGenerateTextureMipmap)(GLuint texture, GLenum target);
    void (APIENTRY *glGetBooleanIndexedv)(GLenum target, GLuint index,
                                          GLboolean *data);
    void (APIENTRY *glGetCompressedMultiTexImage)(GLenum texunit, GLenum target,
                                                  GLint lod, void *img);
    void (APIENTRY *glGetCompressedTextureImage)(GLuint texture, GLenum target,
                                                 GLint lod, void *img);
    void (APIENTRY *glGetDoubleIndexedv)(GLenum target, GLuint index,
                                         GLdouble *data);
    void (APIENTRY *glGetDoublei_v)(GLenum pname, GLuint index, GLdouble *params);
    void (APIENTRY *glGetFloatIndexedv)(GLenum target, GLuint index,
                                        GLfloat *data);
    void (APIENTRY *glGetFloati_v)(GLenum pname, GLuint index, GLfloat *params);
    void (APIENTRY *glGetFramebufferParameteriv)(GLuint framebuffer,
                                                 GLenum pname, GLint *params);
    void (APIENTRY *glGetIntegerIndexedv)(GLenum target, GLuint index,
                                          GLint *data);
    void (APIENTRY *glGetMultiTexEnvfv)(GLenum texunit, GLenum target,
                                        GLenum pname, GLfloat *params);
    void (APIENTRY *glGetMultiTexEnviv)(GLenum texunit, GLenum target,
                                        GLenum pname, GLint *params);
    void (APIENTRY *glGetMultiTexGendv)(GLenum texunit, GLenum coord,
                                        GLenum pname, GLdouble *params);
    void (APIENTRY *glGetMultiTexGenfv)(GLenum texunit, GLenum coord,
                                        GLenum pname, GLfloat *params);
    void (APIENTRY *glGetMultiTexGeniv)(GLenum texunit, GLenum coord,
                                        GLenum pname, GLint *params);
    void (APIENTRY *glGetMultiTexImage)(GLenum texunit, GLenum target,
                                        GLint level, GLenum format, GLenum type,
                                        void *pixels);
    void (APIENTRY *glGetMultiTexLevelParameterfv)(GLenum texunit, GLenum target,
                                                   GLint level, GLenum pname,
                                                   GLfloat *params);
    void (APIENTRY *glGetMultiTexLevelParameteriv)(GLenum texunit, GLenum target,
                                                   GLint level, GLenum pname,
                                                   GLint *params);
    void (APIENTRY *glGetMultiTexParameterIiv)(GLenum texunit, GLenum target,
                                               GLenum pname, GLint *params);
    void (APIENTRY *glGetMultiTexParameterIuiv)(GLenum texunit, GLenum target,
                                                GLenum pname, GLuint *params);
    void (APIENTRY *glGetMultiTexParameterfv)(GLenum texunit, GLenum target,
                                              GLenum pname, GLfloat *params);
    void (APIENTRY *glGetMultiTexParameteriv)(GLenum texunit, GLenum target,
                                              GLenum pname, GLint *params);
    void (APIENTRY *glGetNamedBufferParameteriv)(GLuint buffer, GLenum pname,
                                                 GLint *params);
    void (APIENTRY *glGetNamedBufferPointerv)(GLuint buffer, GLenum pname,
                                              void **params);
    void (APIENTRY *glGetNamedBufferSubData)(GLuint buffer, GLintptr offset,
                                             GLsizeiptr size, void *data);
    void (APIENTRY *glGetNamedFramebufferAttachmentParameteriv)(GLuint framebuffer,
                                                                GLenum attachment,
                                                                GLenum pname,
                                                                GLint *params);
    void (APIENTRY *glGetNamedFramebufferParameteriv)(GLuint framebuffer,
                                                      GLenum pname,
                                                      GLint *params);
    void (APIENTRY *glGetNamedProgramLocalParameterIiv)(GLuint program,
                                                        GLenum target,
                                                        GLuint index,
                                                        GLint *params);
    void (APIENTRY *glGetNamedProgramLocalParameterIuiv)(GLuint program,
                                                         GLenum target,
                                                         GLuint index,
                                                         GLuint *params);
    void (APIENTRY *glGetNamedProgramLocalParameterdv)(GLuint program,
                                                       GLenum target,
                                                       GLuint index,
                                                       GLdouble *params);
    void (APIENTRY *glGetNamedProgramLocalParameterfv)(GLuint program,
                                                       GLenum target,
                                                       GLuint index,
                                                       GLfloat *params);
    void (APIENTRY *glGetNamedProgramString)(GLuint program, GLenum target,
                                             GLenum pname, void *string);
    void (APIENTRY *glGetNamedProgramiv)(GLuint program, GLenum target,
                                         GLenum pname, GLint *params);
    void (APIENTRY *glGetNamedRenderbufferParameteriv)(GLuint renderbuffer,
                                                       GLenum pname,
                                                       GLint *params);
    void (APIENTRY *glGetPointerIndexedv)(GLenum target, GLuint index,
                                          void **data);
    void (APIENTRY *glGetPointeri_v)(GLenum pname, GLuint index, void **params);
    void (APIENTRY *glGetTextureImage)(GLuint texture, GLenum target,
                                       GLint level, GLenum format, GLenum type,
                                       void *pixels);
    void (APIENTRY *glGetTextureLevelParameterfv)(GLuint texture, GLenum target,
                                                  GLint level, GLenum pname,
                                                  GLfloat *params);
    void (APIENTRY *glGetTextureLevelParameteriv)(GLuint texture, GLenum target,
                                                  GLint level, GLenum pname,
                                                  GLint *params);
    void (APIENTRY *glGetTextureParameterIiv)(GLuint texture, GLenum target,
                                              GLenum pname, GLint *params);
    void (APIENTRY *glGetTextureParameterIuiv)(GLuint texture, GLenum target,
                                               GLenum pname, GLuint *params);
    void (APIENTRY *glGetTextureParameterfv)(GLuint texture, GLenum target,
                                             GLenum pname, GLfloat *params);
    void (APIENTRY *glGetTextureParameteriv)(GLuint texture, GLenum target,
                                             GLenum pname, GLint *params);
    void (APIENTRY *glGetVertexArrayIntegeri_v)(GLuint vaobj, GLuint index,
                                                GLenum pname, GLint *param);
    void (APIENTRY *glGetVertexArrayIntegerv)(GLuint vaobj, GLenum pname,
                                              GLint *param);
    void (APIENTRY *glGetVertexArrayPointeri_v)(GLuint vaobj, GLuint index,
                                                GLenum pname, void **param);
    void (APIENTRY *glGetVertexArrayPointerv)(GLuint vaobj, GLenum pname,
                                              void **param);
    GLboolean(APIENTRY *glIsEnabledIndexed)(GLenum target, GLuint index);
    void *(APIENTRY *glMapNamedBuffer)(GLuint buffer, GLenum access);
    void *(APIENTRY *glMapNamedBufferRange)(GLuint buffer, GLintptr offset,
                                            GLsizeiptr length, GLbitfield access);
    void (APIENTRY *glMatrixFrustum)(GLenum mode, GLdouble left, GLdouble right,
                                     GLdouble bottom, GLdouble top,
                                     GLdouble zNear, GLdouble zFar);
    void (APIENTRY *glMatrixLoadIdentity)(GLenum mode);
    void (APIENTRY *glMatrixLoadTransposed)(GLenum mode, const GLdouble *m);
    void (APIENTRY *glMatrixLoadTransposef)(GLenum mode, const GLfloat *m);
    void (APIENTRY *glMatrixLoadd)(GLenum mode, const GLdouble *m);
    void (APIENTRY *glMatrixLoadf)(GLenum mode, const GLfloat *m);
    void (APIENTRY *glMatrixMultTransposed)(GLenum mode, const GLdouble *m);
    void (APIENTRY *glMatrixMultTransposef)(GLenum mode, const GLfloat *m);
    void (APIENTRY *glMatrixMultd)(GLenum mode, const GLdouble *m);
    void (APIENTRY *glMatrixMultf)(GLenum mode, const GLfloat *m);
    void (APIENTRY *glMatrixOrtho)(GLenum mode, GLdouble left, GLdouble right,
                                   GLdouble bottom, GLdouble top, GLdouble zNear,
                                   GLdouble zFar);
    void (APIENTRY *glMatrixPop)(GLenum mode);
    void (APIENTRY *glMatrixPush)(GLenum mode);
    void (APIENTRY *glMatrixRotated)(GLenum mode, GLdouble angle, GLdouble x,
                                     GLdouble y, GLdouble z);
    void (APIENTRY *glMatrixRotatef)(GLenum mode, GLfloat angle, GLfloat x,
                                     GLfloat y, GLfloat z);
    void (APIENTRY *glMatrixScaled)(GLenum mode, GLdouble x, GLdouble y,
                                    GLdouble z);
    void (APIENTRY *glMatrixScalef)(GLenum mode, GLfloat x, GLfloat y, GLfloat z);
    void (APIENTRY *glMatrixTranslated)(GLenum mode, GLdouble x, GLdouble y,
                                        GLdouble z);
    void (APIENTRY *glMatrixTranslatef)(GLenum mode, GLfloat x, GLfloat y,
                                        GLfloat z);
    void (APIENTRY *glMultiTexBuffer)(GLenum texunit, GLenum target,
                                      GLenum internalformat, GLuint buffer);
    void (APIENTRY *glMultiTexCoordPointer)(GLenum texunit, GLint size,
                                            GLenum type, GLsizei stride,
                                            const void *pointer);
    void (APIENTRY *glMultiTexEnvf)(GLenum texunit, GLenum target, GLenum pname,
                                    GLfloat param);
    void (APIENTRY *glMultiTexEnvfv)(GLenum texunit, GLenum target, GLenum pname,
                                     const GLfloat *params);
    void (APIENTRY *glMultiTexEnvi)(GLenum texunit, GLenum target, GLenum pname,
                                    GLint param);
    void (APIENTRY *glMultiTexEnviv)(GLenum texunit, GLenum target, GLenum pname,
                                     const GLint *params);
    void (APIENTRY *glMultiTexGend)(GLenum texunit, GLenum coord, GLenum pname,
                                    GLdouble param);
    void (APIENTRY *glMultiTexGendv)(GLenum texunit, GLenum coord, GLenum pname,
                                     const GLdouble *params);
    void (APIENTRY *glMultiTexGenf)(GLenum texunit, GLenum coord, GLenum pname,
                                    GLfloat param);
    void (APIENTRY *glMultiTexGenfv)(GLenum texunit, GLenum coord, GLenum pname,
                                     const GLfloat *params);
    void (APIENTRY *glMultiTexGeni)(GLenum texunit, GLenum coord, GLenum pname,
                                    GLint param);
    void (APIENTRY *glMultiTexGeniv)(GLenum texunit, GLenum coord, GLenum pname,
                                     const GLint *params);
    void (APIENTRY *glMultiTexImage1D)(GLenum texunit, GLenum target,
                                       GLint level, GLint internalformat,
                                       GLsizei width, GLint border,
                                       GLenum format, GLenum type,
                                       const void *pixels);
    void (APIENTRY *glMultiTexImage2D)(GLenum texunit, GLenum target,
                                       GLint level, GLint internalformat,
                                       GLsizei width, GLsizei height,
                                       GLint border, GLenum format, GLenum type,
                                       const void *pixels);
    void (APIENTRY *glMultiTexImage3D)(GLenum texunit, GLenum target,
                                       GLint level, GLint internalformat,
                                       GLsizei width, GLsizei height,
                                       GLsizei depth, GLint border,
                                       GLenum format, GLenum type,
                                       const void *pixels);
    void (APIENTRY *glMultiTexParameterIiv)(GLenum texunit, GLenum target,
                                            GLenum pname, const GLint *params);
    void (APIENTRY *glMultiTexParameterIuiv)(GLenum texunit, GLenum target,
                                             GLenum pname, const GLuint *params);
    void (APIENTRY *glMultiTexParameterf)(GLenum texunit, GLenum target,
                                          GLenum pname, GLfloat param);
    void (APIENTRY *glMultiTexParameterfv)(GLenum texunit, GLenum target,
                                           GLenum pname, const GLfloat *params);
    void (APIENTRY *glMultiTexParameteri)(GLenum texunit, GLenum target,
                                          GLenum pname, GLint param);
    void (APIENTRY *glMultiTexParameteriv)(GLenum texunit, GLenum target,
                                           GLenum pname, const GLint *params);
    void (APIENTRY *glMultiTexRenderbuffer)(GLenum texunit, GLenum target,
                                            GLuint renderbuffer);
    void (APIENTRY *glMultiTexSubImage1D)(GLenum texunit, GLenum target,
                                          GLint level, GLint xoffset,
                                          GLsizei width, GLenum format,
                                          GLenum type, const void *pixels);
    void (APIENTRY *glMultiTexSubImage2D)(GLenum texunit, GLenum target,
                                          GLint level, GLint xoffset,
                                          GLint yoffset, GLsizei width,
                                          GLsizei height, GLenum format,
                                          GLenum type, const void *pixels);
    void (APIENTRY *glMultiTexSubImage3D)(GLenum texunit, GLenum target,
                                          GLint level, GLint xoffset,
                                          GLint yoffset, GLint zoffset,
                                          GLsizei width, GLsizei height,
                                          GLsizei depth, GLenum format,
                                          GLenum type, const void *pixels);
    void (APIENTRY *glNamedBufferData)(GLuint buffer, GLsizeiptr size,
                                       const void *data, GLenum usage);
    void (APIENTRY *glNamedBufferStorage)(GLuint buffer, GLsizeiptr size,
                                          const void *data, GLbitfield flags);
    void (APIENTRY *glNamedBufferSubData)(GLuint buffer, GLintptr offset,
                                          GLsizeiptr size, const void *data);
    void (APIENTRY *glNamedCopyBufferSubData)(GLuint readBuffer,
                                              GLuint writeBuffer,
                                              GLintptr readOffset,
                                              GLintptr writeOffset,
                                              GLsizeiptr size);
    void (APIENTRY *glNamedFramebufferParameteri)(GLuint framebuffer,
                                                  GLenum pname, GLint param);
    void (APIENTRY *glNamedFramebufferRenderbuffer)(GLuint framebuffer,
                                                    GLenum attachment,
                                                    GLenum renderbuffertarget,
                                                    GLuint renderbuffer);
    void (APIENTRY *glNamedFramebufferTexture1D)(GLuint framebuffer,
                                                 GLenum attachment,
                                                 GLenum textarget,
                                                 GLuint texture, GLint level);
    void (APIENTRY *glNamedFramebufferTexture2D)(GLuint framebuffer,
                                                 GLenum attachment,
                                                 GLenum textarget,
                                                 GLuint texture, GLint level);
    void (APIENTRY *glNamedFramebufferTexture3D)(GLuint framebuffer,
                                                 GLenum attachment,
                                                 GLenum textarget,
                                                 GLuint texture, GLint level,
                                                 GLint zoffset);
    void (APIENTRY *glNamedFramebufferTexture)(GLuint framebuffer,
                                               GLenum attachment, GLuint texture,
                                               GLint level);
    void (APIENTRY *glNamedFramebufferTextureFace)(GLuint framebuffer,
                                                   GLenum attachment,
                                                   GLuint texture, GLint level,
                                                   GLenum face);
    void (APIENTRY *glNamedFramebufferTextureLayer)(GLuint framebuffer,
                                                    GLenum attachment,
                                                    GLuint texture, GLint level,
                                                    GLint layer);
    void (APIENTRY *glNamedProgramLocalParameter4d)(GLuint program,
                                                    GLenum target, GLuint index,
                                                    GLdouble x, GLdouble y,
                                                    GLdouble z, GLdouble w);
    void (APIENTRY *glNamedProgramLocalParameter4dv)(GLuint program,
                                                     GLenum target, GLuint index,
                                                     const GLdouble *params);
    void (APIENTRY *glNamedProgramLocalParameter4f)(GLuint program,
                                                    GLenum target, GLuint index,
                                                    GLfloat x, GLfloat y,
                                                    GLfloat z, GLfloat w);
    void (APIENTRY *glNamedProgramLocalParameter4fv)(GLuint program,
                                                     GLenum target, GLuint index,
                                                     const GLfloat *params);
    void (APIENTRY *glNamedProgramLocalParameterI4i)(GLuint program,
                                                     GLenum target, GLuint index,
                                                     GLint x, GLint y, GLint z,
                                                     GLint w);
    void (APIENTRY *glNamedProgramLocalParameterI4iv)(GLuint program,
                                                      GLenum target,
                                                      GLuint index,
                                                      const GLint *params);
    void (APIENTRY *glNamedProgramLocalParameterI4ui)(GLuint program,
                                                      GLenum target,
                                                      GLuint index, GLuint x,
                                                      GLuint y, GLuint z,
                                                      GLuint w);
    void (APIENTRY *glNamedProgramLocalParameterI4uiv)(GLuint program,
                                                       GLenum target,
                                                       GLuint index,
                                                       const GLuint *params);
    void (APIENTRY *glNamedProgramLocalParameters4fv)(GLuint program,
                                                      GLenum target,
                                                      GLuint index,
                                                      GLsizei count,
                                                      const GLfloat *params);
    void (APIENTRY *glNamedProgramLocalParametersI4iv)(GLuint program,
                                                       GLenum target,
                                                       GLuint index,
                                                       GLsizei count,
                                                       const GLint *params);
    void (APIENTRY *glNamedProgramLocalParametersI4uiv)(GLuint program,
                                                        GLenum target,
                                                        GLuint index,
                                                        GLsizei count,
                                                        const GLuint *params);
    void (APIENTRY *glNamedProgramString)(GLuint program, GLenum target,
                                          GLenum format, GLsizei len,
                                          const void *string);
    void (APIENTRY *glNamedRenderbufferStorage)(GLuint renderbuffer,
                                                GLenum internalformat,
                                                GLsizei width, GLsizei height);
    void (APIENTRY *glNamedRenderbufferStorageMultisampleCoverage)(GLuint renderbuffer,
                                                                   GLsizei coverageSamples,
                                                                   GLsizei colorSamples,
                                                                   GLenum internalformat,
                                                                   GLsizei width,
                                                                   GLsizei height);
    void (APIENTRY *glNamedRenderbufferStorageMultisample)(GLuint renderbuffer,
                                                           GLsizei samples,
                                                           GLenum internalformat,
                                                           GLsizei width,
                                                           GLsizei height);
    void (APIENTRY *glProgramUniform1d)(GLuint program, GLint location,
                                        GLdouble x);
    void (APIENTRY *glProgramUniform1dv)(GLuint program, GLint location,
                                         GLsizei count, const GLdouble *value);
    void (APIENTRY *glProgramUniform1f)(GLuint program, GLint location,
                                        GLfloat v0);
    void (APIENTRY *glProgramUniform1fv)(GLuint program, GLint location,
                                         GLsizei count, const GLfloat *value);
    void (APIENTRY *glProgramUniform1i)(GLuint program, GLint location, GLint v0);
    void (APIENTRY *glProgramUniform1iv)(GLuint program, GLint location,
                                         GLsizei count, const GLint *value);
    void (APIENTRY *glProgramUniform1ui)(GLuint program, GLint location,
                                         GLuint v0);
    void (APIENTRY *glProgramUniform1uiv)(GLuint program, GLint location,
                                          GLsizei count, const GLuint *value);
    void (APIENTRY *glProgramUniform2d)(GLuint program, GLint location,
                                        GLdouble x, GLdouble y);
    void (APIENTRY *glProgramUniform2dv)(GLuint program, GLint location,
                                         GLsizei count, const GLdouble *value);
    void (APIENTRY *glProgramUniform2f)(GLuint program, GLint location,
                                        GLfloat v0, GLfloat v1);
    void (APIENTRY *glProgramUniform2fv)(GLuint program, GLint location,
                                         GLsizei count, const GLfloat *value);
    void (APIENTRY *glProgramUniform2i)(GLuint program, GLint location, GLint v0,
                                        GLint v1);
    void (APIENTRY *glProgramUniform2iv)(GLuint program, GLint location,
                                         GLsizei count, const GLint *value);
    void (APIENTRY *glProgramUniform2ui)(GLuint program, GLint location,
                                         GLuint v0, GLuint v1);
    void (APIENTRY *glProgramUniform2uiv)(GLuint program, GLint location,
                                          GLsizei count, const GLuint *value);
    void (APIENTRY *glProgramUniform3d)(GLuint program, GLint location,
                                        GLdouble x, GLdouble y, GLdouble z);
    void (APIENTRY *glProgramUniform3dv)(GLuint program, GLint location,
                                         GLsizei count, const GLdouble *value);
    void (APIENTRY *glProgramUniform3f)(GLuint program, GLint location,
                                        GLfloat v0, GLfloat v1, GLfloat v2);
    void (APIENTRY *glProgramUniform3fv)(GLuint program, GLint location,
                                         GLsizei count, const GLfloat *value);
    void (APIENTRY *glProgramUniform3i)(GLuint program, GLint location, GLint v0,
                                        GLint v1, GLint v2);
    void (APIENTRY *glProgramUniform3iv)(GLuint program, GLint location,
                                         GLsizei count, const GLint *value);
    void (APIENTRY *glProgramUniform3ui)(GLuint program, GLint location,
                                         GLuint v0, GLuint v1, GLuint v2);
    void (APIENTRY *glProgramUniform3uiv)(GLuint program, GLint location,
                                          GLsizei count, const GLuint *value);
    void (APIENTRY *glProgramUniform4d)(GLuint program, GLint location,
                                        GLdouble x, GLdouble y, GLdouble z,
                                        GLdouble w);
    void (APIENTRY *glProgramUniform4dv)(GLuint program, GLint location,
                                         GLsizei count, const GLdouble *value);
    void (APIENTRY *glProgramUniform4f)(GLuint program, GLint location,
                                        GLfloat v0, GLfloat v1, GLfloat v2,
                                        GLfloat v3);
    void (APIENTRY *glProgramUniform4fv)(GLuint program, GLint location,
                                         GLsizei count, const GLfloat *value);
    void (APIENTRY *glProgramUniform4i)(GLuint program, GLint location, GLint v0,
                                        GLint v1, GLint v2, GLint v3);
    void (APIENTRY *glProgramUniform4iv)(GLuint program, GLint location,
                                         GLsizei count, const GLint *value);
    void (APIENTRY *glProgramUniform4ui)(GLuint program, GLint location,
                                         GLuint v0, GLuint v1, GLuint v2,
                                         GLuint v3);
    void (APIENTRY *glProgramUniform4uiv)(GLuint program, GLint location,
                                          GLsizei count, const GLuint *value);
    void (APIENTRY *glProgramUniformMatrix2dv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix2fv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix2x3dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix2x3fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix2x4dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix2x4fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix3dv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix3fv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix3x2dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix3x2fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix3x4dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix3x4fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix4dv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix4fv)(GLuint program, GLint location,
                                               GLsizei count,
                                               GLboolean transpose,
                                               const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix4x2dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix4x2fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glProgramUniformMatrix4x3dv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLdouble *value);
    void (APIENTRY *glProgramUniformMatrix4x3fv)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 GLboolean transpose,
                                                 const GLfloat *value);
    void (APIENTRY *glPushClientAttribDefault)(GLbitfield mask);
    void (APIENTRY *glTextureBuffer)(GLuint texture, GLenum target,
                                     GLenum internalformat, GLuint buffer);
    void (APIENTRY *glTextureBufferRange)(GLuint texture, GLenum target,
                                          GLenum internalformat, GLuint buffer,
                                          GLintptr offset, GLsizeiptr size);
    void (APIENTRY *glTextureImage1D)(GLuint texture, GLenum target, GLint level,
                                      GLint internalformat, GLsizei width,
                                      GLint border, GLenum format, GLenum type,
                                      const void *pixels);
    void (APIENTRY *glTextureImage2D)(GLuint texture, GLenum target, GLint level,
                                      GLint internalformat, GLsizei width,
                                      GLsizei height, GLint border,
                                      GLenum format, GLenum type,
                                      const void *pixels);
    void (APIENTRY *glTextureImage3D)(GLuint texture, GLenum target, GLint level,
                                      GLint internalformat, GLsizei width,
                                      GLsizei height, GLsizei depth,
                                      GLint border, GLenum format, GLenum type,
                                      const void *pixels);
    void (APIENTRY *glTexturePageCommitment)(GLuint texture, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint zoffset, GLsizei width,
                                             GLsizei height, GLsizei depth,
                                             GLboolean commit);
    void (APIENTRY *glTextureParameterIiv)(GLuint texture, GLenum target,
                                           GLenum pname, const GLint *params);
    void (APIENTRY *glTextureParameterIuiv)(GLuint texture, GLenum target,
                                            GLenum pname, const GLuint *params);
    void (APIENTRY *glTextureParameterf)(GLuint texture, GLenum target,
                                         GLenum pname, GLfloat param);
    void (APIENTRY *glTextureParameterfv)(GLuint texture, GLenum target,
                                          GLenum pname, const GLfloat *params);
    void (APIENTRY *glTextureParameteri)(GLuint texture, GLenum target,
                                         GLenum pname, GLint param);
    void (APIENTRY *glTextureParameteriv)(GLuint texture, GLenum target,
                                          GLenum pname, const GLint *params);
    void (APIENTRY *glTextureRenderbuffer)(GLuint texture, GLenum target,
                                           GLuint renderbuffer);
    void (APIENTRY *glTextureStorage1D)(GLuint texture, GLenum target,
                                        GLsizei levels, GLenum internalformat,
                                        GLsizei width);
    void (APIENTRY *glTextureStorage2D)(GLuint texture, GLenum target,
                                        GLsizei levels, GLenum internalformat,
                                        GLsizei width, GLsizei height);
    void (APIENTRY *glTextureStorage2DMultisample)(GLuint texture, GLenum target,
                                                   GLsizei samples,
                                                   GLenum internalformat,
                                                   GLsizei width, GLsizei height,
                                                   GLboolean fixedsamplelocations);
    void (APIENTRY *glTextureStorage3D)(GLuint texture, GLenum target,
                                        GLsizei levels, GLenum internalformat,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth);
    void (APIENTRY *glTextureStorage3DMultisample)(GLuint texture, GLenum target,
                                                   GLsizei samples,
                                                   GLenum internalformat,
                                                   GLsizei width, GLsizei height,
                                                   GLsizei depth,
                                                   GLboolean fixedsamplelocations);
    void (APIENTRY *glTextureSubImage1D)(GLuint texture, GLenum target,
                                         GLint level, GLint xoffset,
                                         GLsizei width, GLenum format,
                                         GLenum type, const void *pixels);
    void (APIENTRY *glTextureSubImage2D)(GLuint texture, GLenum target,
                                         GLint level, GLint xoffset,
                                         GLint yoffset, GLsizei width,
                                         GLsizei height, GLenum format,
                                         GLenum type, const void *pixels);
    void (APIENTRY *glTextureSubImage3D)(GLuint texture, GLenum target,
                                         GLint level, GLint xoffset,
                                         GLint yoffset, GLint zoffset,
                                         GLsizei width, GLsizei height,
                                         GLsizei depth, GLenum format,
                                         GLenum type, const void *pixels);
    GLboolean(APIENTRY *glUnmapNamedBuffer)(GLuint buffer);
    void (APIENTRY *glVertexArrayBindVertexBuffer)(GLuint vaobj,
                                                   GLuint bindingindex,
                                                   GLuint buffer,
                                                   GLintptr offset,
                                                   GLsizei stride);
    void (APIENTRY *glVertexArrayColorOffset)(GLuint vaobj, GLuint buffer,
                                              GLint size, GLenum type,
                                              GLsizei stride, GLintptr offset);
    void (APIENTRY *glVertexArrayEdgeFlagOffset)(GLuint vaobj, GLuint buffer,
                                                 GLsizei stride, GLintptr offset);
    void (APIENTRY *glVertexArrayFogCoordOffset)(GLuint vaobj, GLuint buffer,
                                                 GLenum type, GLsizei stride,
                                                 GLintptr offset);
    void (APIENTRY *glVertexArrayIndexOffset)(GLuint vaobj, GLuint buffer,
                                              GLenum type, GLsizei stride,
                                              GLintptr offset);
    void (APIENTRY *glVertexArrayMultiTexCoordOffset)(GLuint vaobj,
                                                      GLuint buffer,
                                                      GLenum texunit, GLint size,
                                                      GLenum type,
                                                      GLsizei stride,
                                                      GLintptr offset);
    void (APIENTRY *glVertexArrayNormalOffset)(GLuint vaobj, GLuint buffer,
                                               GLenum type, GLsizei stride,
                                               GLintptr offset);
    void (APIENTRY *glVertexArraySecondaryColorOffset)(GLuint vaobj,
                                                       GLuint buffer, GLint size,
                                                       GLenum type,
                                                       GLsizei stride,
                                                       GLintptr offset);
    void (APIENTRY *glVertexArrayTexCoordOffset)(GLuint vaobj, GLuint buffer,
                                                 GLint size, GLenum type,
                                                 GLsizei stride, GLintptr offset);
    void (APIENTRY *glVertexArrayVertexAttribBinding)(GLuint vaobj,
                                                      GLuint attribindex,
                                                      GLuint bindingindex);
    void (APIENTRY *glVertexArrayVertexAttribDivisor)(GLuint vaobj, GLuint index,
                                                      GLuint divisor);
    void (APIENTRY *glVertexArrayVertexAttribFormat)(GLuint vaobj,
                                                     GLuint attribindex,
                                                     GLint size, GLenum type,
                                                     GLboolean normalized,
                                                     GLuint relativeoffset);
    void (APIENTRY *glVertexArrayVertexAttribIFormat)(GLuint vaobj,
                                                      GLuint attribindex,
                                                      GLint size, GLenum type,
                                                      GLuint relativeoffset);
    void (APIENTRY *glVertexArrayVertexAttribIOffset)(GLuint vaobj,
                                                      GLuint buffer,
                                                      GLuint index, GLint size,
                                                      GLenum type,
                                                      GLsizei stride,
                                                      GLintptr offset);
    void (APIENTRY *glVertexArrayVertexAttribLFormat)(GLuint vaobj,
                                                      GLuint attribindex,
                                                      GLint size, GLenum type,
                                                      GLuint relativeoffset);
    void (APIENTRY *glVertexArrayVertexAttribLOffset)(GLuint vaobj,
                                                      GLuint buffer,
                                                      GLuint index, GLint size,
                                                      GLenum type,
                                                      GLsizei stride,
                                                      GLintptr offset);
    void (APIENTRY *glVertexArrayVertexAttribOffset)(GLuint vaobj, GLuint buffer,
                                                     GLuint index, GLint size,
                                                     GLenum type,
                                                     GLboolean normalized,
                                                     GLsizei stride,
                                                     GLintptr offset);
    void (APIENTRY *glVertexArrayVertexBindingDivisor)(GLuint vaobj,
                                                       GLuint bindingindex,
                                                       GLuint divisor);
    void (APIENTRY *glVertexArrayVertexOffset)(GLuint vaobj, GLuint buffer,
                                               GLint size, GLenum type,
                                               GLsizei stride, GLintptr offset);

    // Construction
    EXTDirectStateAccess();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDirectStateAccess

// GL_EXT_draw_buffers2 extension API specification.
struct EXTDrawBUFFERS2 {
    // Public Members
    void (APIENTRY *glColorMaskIndexed)(GLuint index, GLboolean r, GLboolean g,
                                        GLboolean b, GLboolean a);

    // Construction
    EXTDrawBUFFERS2();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDrawBUFFERS2

// GL_EXT_draw_instanced extension API specification.
struct EXTDrawInstanced {
    // Public Members
    void (APIENTRY *glDrawArraysInstanced)(GLenum mode, GLint start,
                                           GLsizei count, GLsizei primcount);
    void (APIENTRY *glDrawElementsInstanced)(GLenum mode, GLsizei count,
                                             GLenum type, const void *indices,
                                             GLsizei primcount);

    // Construction
    EXTDrawInstanced();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDrawInstanced

// GL_EXT_draw_range_elements extension API specification.
struct EXTDrawRangeElements {
    // Public Members
    void (APIENTRY *glDrawRangeElements)(GLenum mode, GLuint start, GLuint end,
                                         GLsizei count, GLenum type,
                                         const void *indices);

    // Construction
    EXTDrawRangeElements();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDrawRangeElements

// GL_EXT_external_buffer extension API specification.
struct EXTExternalBuffer {
    // Public Members
    void (APIENTRY *glBufferStorageExternal)(GLenum target, GLintptr offset,
                                             GLsizeiptr size,
                                             GLeglClientBufferEXT clientBuffer,
                                             GLbitfield flags);
    void (APIENTRY *glNamedBufferStorageExternal)(GLuint buffer, GLintptr offset,
                                                  GLsizeiptr size,
                                                  GLeglClientBufferEXT clientBuffer,
                                                  GLbitfield flags);

    // Construction
    EXTExternalBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTExternalBuffer

// GL_EXT_fog_coord extension API specification.
struct EXTFogCoord {
    // Public Members
    void (APIENTRY *glFogCoordPointer)(GLenum type, GLsizei stride,
                                       const void *pointer);
    void (APIENTRY *glFogCoordd)(GLdouble coord);
    void (APIENTRY *glFogCoorddv)(const GLdouble *coord);
    void (APIENTRY *glFogCoordf)(GLfloat coord);
    void (APIENTRY *glFogCoordfv)(const GLfloat *coord);

    // Construction
    EXTFogCoord();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTFogCoord

// GL_EXT_framebuffer_blit extension API specification.
struct EXTFramebufferBlit {
    // Public Members
    void (APIENTRY *glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1,
                                       GLint srcY1, GLint dstX0, GLint dstY0,
                                       GLint dstX1, GLint dstY1, GLbitfield mask,
                                       GLenum filter);

    // Construction
    EXTFramebufferBlit();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTFramebufferBlit

// GL_EXT_framebuffer_blit_layers extension API specification.
struct EXTFramebufferBlitLayers {
    // Public Members
    void (APIENTRY *glBlitFramebufferLayer)(GLint srcX0, GLint srcY0,
                                            GLint srcX1, GLint srcY1,
                                            GLint srcLayer, GLint dstX0,
                                            GLint dstY0, GLint dstX1,
                                            GLint dstY1, GLint dstLayer,
                                            GLbitfield mask, GLenum filter);
    void (APIENTRY *glBlitFramebufferLayers)(GLint srcX0, GLint srcY0,
                                             GLint srcX1, GLint srcY1,
                                             GLint dstX0, GLint dstY0,
                                             GLint dstX1, GLint dstY1,
                                             GLbitfield mask, GLenum filter);

    // Construction
    EXTFramebufferBlitLayers();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTFramebufferBlitLayers

// GL_EXT_framebuffer_multisample extension API specification.
struct EXTFramebufferMultisample {
    // Public Members
    void (APIENTRY *glRenderbufferStorageMultisample)(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height);

    // Construction
    EXTFramebufferMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTFramebufferMultisample

// GL_EXT_framebuffer_object extension API specification.
struct EXTFramebufferObject {
    // Public Members
    void (APIENTRY *glBindFramebuffer)(GLenum target, GLuint framebuffer);
    void (APIENTRY *glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
    GLenum(APIENTRY *glCheckFramebufferStatus)(GLenum target);
    void (APIENTRY *glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers);
    void (APIENTRY *glDeleteRenderbuffers)(GLsizei n,
                                           const GLuint *renderbuffers);
    void (APIENTRY *glFramebufferRenderbuffer)(GLenum target, GLenum attachment,
                                               GLenum renderbuffertarget,
                                               GLuint renderbuffer);
    void (APIENTRY *glFramebufferTexture1D)(GLenum target, GLenum attachment,
                                            GLenum textarget, GLuint texture,
                                            GLint level);
    void (APIENTRY *glFramebufferTexture2D)(GLenum target, GLenum attachment,
                                            GLenum textarget, GLuint texture,
                                            GLint level);
    void (APIENTRY *glFramebufferTexture3D)(GLenum target, GLenum attachment,
                                            GLenum textarget, GLuint texture,
                                            GLint level, GLint zoffset);
    void (APIENTRY *glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
    void (APIENTRY *glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
    void (APIENTRY *glGenerateMipmap)(GLenum target);
    void (APIENTRY *glGetFramebufferAttachmentParameteriv)(GLenum target,
                                                           GLenum attachment,
                                                           GLenum pname,
                                                           GLint *params);
    void (APIENTRY *glGetRenderbufferParameteriv)(GLenum target, GLenum pname,
                                                  GLint *params);
    GLboolean(APIENTRY *glIsFramebuffer)(GLuint framebuffer);
    GLboolean(APIENTRY *glIsRenderbuffer)(GLuint renderbuffer);
    void (APIENTRY *glRenderbufferStorage)(GLenum target, GLenum internalformat,
                                           GLsizei width, GLsizei height);

    // Construction
    EXTFramebufferObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTFramebufferObject

// GL_EXT_geometry_shader4 extension API specification.
struct EXTGeometrySHADER4 {
    // Public Members
    void (APIENTRY *glProgramParameteri)(GLuint program, GLenum pname,
                                         GLint value);

    // Construction
    EXTGeometrySHADER4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTGeometrySHADER4

// GL_EXT_gpu_program_parameters extension API specification.
struct EXTGPUProgramParameters {
    // Public Members
    void (APIENTRY *glProgramEnvParameters4fv)(GLenum target, GLuint index,
                                               GLsizei count,
                                               const GLfloat *params);
    void (APIENTRY *glProgramLocalParameters4fv)(GLenum target, GLuint index,
                                                 GLsizei count,
                                                 const GLfloat *params);

    // Construction
    EXTGPUProgramParameters();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTGPUProgramParameters

// GL_EXT_gpu_shader4 extension API specification.
struct EXTGPUSHADER4 {
    // Public Members
    void (APIENTRY *glBindFragDataLocation)(GLuint program, GLuint color,
                                            const GLchar *name);
    GLint(APIENTRY *glGetFragDataLocation)(GLuint program, const GLchar *name);
    void (APIENTRY *glGetUniformuiv)(GLuint program, GLint location,
                                     GLuint *params);
    void (APIENTRY *glGetVertexAttribIiv)(GLuint index, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glGetVertexAttribIuiv)(GLuint index, GLenum pname,
                                           GLuint *params);
    void (APIENTRY *glUniform1ui)(GLint location, GLuint v0);
    void (APIENTRY *glUniform1uiv)(GLint location, GLsizei count,
                                   const GLuint *value);
    void (APIENTRY *glUniform2ui)(GLint location, GLuint v0, GLuint v1);
    void (APIENTRY *glUniform2uiv)(GLint location, GLsizei count,
                                   const GLuint *value);
    void (APIENTRY *glUniform3ui)(GLint location, GLuint v0, GLuint v1,
                                  GLuint v2);
    void (APIENTRY *glUniform3uiv)(GLint location, GLsizei count,
                                   const GLuint *value);
    void (APIENTRY *glUniform4ui)(GLint location, GLuint v0, GLuint v1,
                                  GLuint v2, GLuint v3);
    void (APIENTRY *glUniform4uiv)(GLint location, GLsizei count,
                                   const GLuint *value);
    void (APIENTRY *glVertexAttribI1i)(GLuint index, GLint x);
    void (APIENTRY *glVertexAttribI1iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttribI1ui)(GLuint index, GLuint x);
    void (APIENTRY *glVertexAttribI1uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttribI2i)(GLuint index, GLint x, GLint y);
    void (APIENTRY *glVertexAttribI2iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttribI2ui)(GLuint index, GLuint x, GLuint y);
    void (APIENTRY *glVertexAttribI2uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z);
    void (APIENTRY *glVertexAttribI3iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttribI3ui)(GLuint index, GLuint x, GLuint y,
                                        GLuint z);
    void (APIENTRY *glVertexAttribI3uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttribI4bv)(GLuint index, const GLbyte *v);
    void (APIENTRY *glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z,
                                       GLint w);
    void (APIENTRY *glVertexAttribI4iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttribI4sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttribI4ubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y,
                                        GLuint z, GLuint w);
    void (APIENTRY *glVertexAttribI4uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttribI4usv)(GLuint index, const GLushort *v);
    void (APIENTRY *glVertexAttribIPointer)(GLuint index, GLint size,
                                            GLenum type, GLsizei stride,
                                            const void *pointer);

    // Construction
    EXTGPUSHADER4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTGPUSHADER4

// GL_EXT_histogram extension API specification.
struct EXTHistogram {
    // Public Members
    void (APIENTRY *glGetHistogram)(GLenum target, GLboolean reset,
                                    GLenum format, GLenum type, void *values);
    void (APIENTRY *glGetHistogramParameterfv)(GLenum target, GLenum pname,
                                               GLfloat *params);
    void (APIENTRY *glGetHistogramParameteriv)(GLenum target, GLenum pname,
                                               GLint *params);
    void (APIENTRY *glGetMinmax)(GLenum target, GLboolean reset, GLenum format,
                                 GLenum type, void *values);
    void (APIENTRY *glGetMinmaxParameterfv)(GLenum target, GLenum pname,
                                            GLfloat *params);
    void (APIENTRY *glGetMinmaxParameteriv)(GLenum target, GLenum pname,
                                            GLint *params);
    void (APIENTRY *glHistogram)(GLenum target, GLsizei width,
                                 GLenum internalformat, GLboolean sink);
    void (APIENTRY *glMinmax)(GLenum target, GLenum internalformat,
                              GLboolean sink);
    void (APIENTRY *glResetHistogram)(GLenum target);
    void (APIENTRY *glResetMinmax)(GLenum target);

    // Construction
    EXTHistogram();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTHistogram

// GL_EXT_index_func extension API specification.
struct EXTIndexFunc {
    // Public Members
    void (APIENTRY *glIndexFunc)(GLenum func, GLclampf ref);

    // Construction
    EXTIndexFunc();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTIndexFunc

// GL_EXT_index_material extension API specification.
struct EXTIndexMaterial {
    // Public Members
    void (APIENTRY *glIndexMaterial)(GLenum face, GLenum mode);

    // Construction
    EXTIndexMaterial();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTIndexMaterial

// GL_EXT_light_texture extension API specification.
struct EXTLightTexture {
    // Public Members
    void (APIENTRY *glApplyTexture)(GLenum mode);
    void (APIENTRY *glTextureLight)(GLenum pname);
    void (APIENTRY *glTextureMaterial)(GLenum face, GLenum mode);

    // Construction
    EXTLightTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTLightTexture

// GL_EXT_memory_object extension API specification.
struct EXTMemoryObject {
    // Public Members
    void (APIENTRY *glBufferStorageMem)(GLenum target, GLsizeiptr size,
                                        GLuint memory, GLuint64 offset);
    void (APIENTRY *glCreateMemoryObjects)(GLsizei n, GLuint *memoryObjects);
    void (APIENTRY *glDeleteMemoryObjects)(GLsizei n,
                                           const GLuint *memoryObjects);
    void (APIENTRY *glGetMemoryObjectParameteriv)(GLuint memoryObject,
                                                  GLenum pname, GLint *params);
    void (APIENTRY *glGetUnsignedBytei_v)(GLenum target, GLuint index,
                                          GLubyte *data);
    void (APIENTRY *glGetUnsignedBytev)(GLenum pname, GLubyte *data);
    GLboolean(APIENTRY *glIsMemoryObject)(GLuint memoryObject);
    void (APIENTRY *glMemoryObjectParameteriv)(GLuint memoryObject, GLenum pname,
                                               const GLint *params);
    void (APIENTRY *glNamedBufferStorageMem)(GLuint buffer, GLsizeiptr size,
                                             GLuint memory, GLuint64 offset);
    void (APIENTRY *glTexStorageMem1D)(GLenum target, GLsizei levels,
                                       GLenum internalFormat, GLsizei width,
                                       GLuint memory, GLuint64 offset);
    void (APIENTRY *glTexStorageMem2D)(GLenum target, GLsizei levels,
                                       GLenum internalFormat, GLsizei width,
                                       GLsizei height, GLuint memory,
                                       GLuint64 offset);
    void (APIENTRY *glTexStorageMem2DMultisample)(GLenum target, GLsizei samples,
                                                  GLenum internalFormat,
                                                  GLsizei width, GLsizei height,
                                                  GLboolean fixedSampleLocations,
                                                  GLuint memory, GLuint64 offset);
    void (APIENTRY *glTexStorageMem3D)(GLenum target, GLsizei levels,
                                       GLenum internalFormat, GLsizei width,
                                       GLsizei height, GLsizei depth,
                                       GLuint memory, GLuint64 offset);
    void (APIENTRY *glTexStorageMem3DMultisample)(GLenum target, GLsizei samples,
                                                  GLenum internalFormat,
                                                  GLsizei width, GLsizei height,
                                                  GLsizei depth,
                                                  GLboolean fixedSampleLocations,
                                                  GLuint memory, GLuint64 offset);
    void (APIENTRY *glTextureStorageMem1D)(GLuint texture, GLsizei levels,
                                           GLenum internalFormat, GLsizei width,
                                           GLuint memory, GLuint64 offset);
    void (APIENTRY *glTextureStorageMem2D)(GLuint texture, GLsizei levels,
                                           GLenum internalFormat, GLsizei width,
                                           GLsizei height, GLuint memory,
                                           GLuint64 offset);
    void (APIENTRY *glTextureStorageMem2DMultisample)(GLuint texture,
                                                      GLsizei samples,
                                                      GLenum internalFormat,
                                                      GLsizei width,
                                                      GLsizei height,
                                                      GLboolean fixedSampleLocations,
                                                      GLuint memory,
                                                      GLuint64 offset);
    void (APIENTRY *glTextureStorageMem3D)(GLuint texture, GLsizei levels,
                                           GLenum internalFormat, GLsizei width,
                                           GLsizei height, GLsizei depth,
                                           GLuint memory, GLuint64 offset);
    void (APIENTRY *glTextureStorageMem3DMultisample)(GLuint texture,
                                                      GLsizei samples,
                                                      GLenum internalFormat,
                                                      GLsizei width,
                                                      GLsizei height,
                                                      GLsizei depth,
                                                      GLboolean fixedSampleLocations,
                                                      GLuint memory,
                                                      GLuint64 offset);

    // Construction
    EXTMemoryObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMemoryObject

// GL_EXT_memory_object_fd extension API specification.
struct EXTMemoryObjectFd {
    // Public Members
    void (APIENTRY *glImportMemoryFd)(GLuint memory, GLuint64 size,
                                      GLenum handleType, GLint fd);

    // Construction
    EXTMemoryObjectFd();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMemoryObjectFd

// GL_EXT_memory_object_win32 extension API specification.
struct EXTMemoryObjectWIN32 {
    // Public Members
    void (APIENTRY *glImportMemoryWin32Handle)(GLuint memory, GLuint64 size,
                                               GLenum handleType, void *handle);
    void (APIENTRY *glImportMemoryWin32Name)(GLuint memory, GLuint64 size,
                                             GLenum handleType, const void *name);

    // Construction
    EXTMemoryObjectWIN32();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMemoryObjectWIN32

// GL_EXT_multi_draw_arrays extension API specification.
struct EXTMultiDrawArrays {
    // Public Members
    void (APIENTRY *glMultiDrawArrays)(GLenum mode, const GLint *first,
                                       const GLsizei *count, GLsizei primcount);
    void (APIENTRY *glMultiDrawElements)(GLenum mode, const GLsizei *count,
                                         GLenum type, const void *const *indices,
                                         GLsizei primcount);

    // Construction
    EXTMultiDrawArrays();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMultiDrawArrays

// GL_EXT_multisample extension API specification.
struct EXTMultisample {
    // Public Members
    void (APIENTRY *glSampleMask)(GLclampf value, GLboolean invert);
    void (APIENTRY *glSamplePattern)(GLenum pattern);

    // Construction
    EXTMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMultisample

// GL_EXT_paletted_texture extension API specification.
struct EXTPalettedTexture {
    // Public Members
    void (APIENTRY *glColorTable)(GLenum target, GLenum internalFormat,
                                  GLsizei width, GLenum format, GLenum type,
                                  const void *table);
    void (APIENTRY *glGetColorTable)(GLenum target, GLenum format, GLenum type,
                                     void *data);
    void (APIENTRY *glGetColorTableParameterfv)(GLenum target, GLenum pname,
                                                GLfloat *params);
    void (APIENTRY *glGetColorTableParameteriv)(GLenum target, GLenum pname,
                                                GLint *params);

    // Construction
    EXTPalettedTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPalettedTexture

// GL_EXT_pixel_transform extension API specification.
struct EXTPixelTransform {
    // Public Members
    void (APIENTRY *glGetPixelTransformParameterfv)(GLenum target, GLenum pname,
                                                    GLfloat *params);
    void (APIENTRY *glGetPixelTransformParameteriv)(GLenum target, GLenum pname,
                                                    GLint *params);
    void (APIENTRY *glPixelTransformParameterf)(GLenum target, GLenum pname,
                                                GLfloat param);
    void (APIENTRY *glPixelTransformParameterfv)(GLenum target, GLenum pname,
                                                 const GLfloat *params);
    void (APIENTRY *glPixelTransformParameteri)(GLenum target, GLenum pname,
                                                GLint param);
    void (APIENTRY *glPixelTransformParameteriv)(GLenum target, GLenum pname,
                                                 const GLint *params);

    // Construction
    EXTPixelTransform();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPixelTransform

// GL_EXT_point_parameters extension API specification.
struct EXTPointParameters {
    // Public Members
    void (APIENTRY *glPointParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPointParameterfv)(GLenum pname, const GLfloat *params);

    // Construction
    EXTPointParameters();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPointParameters

// GL_EXT_polygon_offset extension API specification.
struct EXTPolygonOffset {
    // Public Members
    void (APIENTRY *glPolygonOffset)(GLfloat factor, GLfloat bias);

    // Construction
    EXTPolygonOffset();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPolygonOffset

// GL_EXT_polygon_offset_clamp extension API specification.
struct EXTPolygonOffsetClamp {
    // Public Members
    void (APIENTRY *glPolygonOffsetClamp)(GLfloat factor, GLfloat units,
                                          GLfloat clamp);

    // Construction
    EXTPolygonOffsetClamp();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPolygonOffsetClamp

// GL_EXT_provoking_vertex extension API specification.
struct EXTProvokingVertex {
    // Public Members
    void (APIENTRY *glProvokingVertex)(GLenum mode);

    // Construction
    EXTProvokingVertex();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTProvokingVertex

// GL_EXT_raster_multisample extension API specification.
struct EXTRasterMultisample {
    // Public Members
    void (APIENTRY *glRasterSamples)(GLuint samples,
                                     GLboolean fixedsamplelocations);

    // Construction
    EXTRasterMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTRasterMultisample

// GL_EXT_secondary_color extension API specification.
struct EXTSecondaryColor {
    // Public Members
    void (APIENTRY *glSecondaryColor3b)(GLbyte red, GLbyte green, GLbyte blue);
    void (APIENTRY *glSecondaryColor3bv)(const GLbyte *v);
    void (APIENTRY *glSecondaryColor3d)(GLdouble red, GLdouble green,
                                        GLdouble blue);
    void (APIENTRY *glSecondaryColor3dv)(const GLdouble *v);
    void (APIENTRY *glSecondaryColor3f)(GLfloat red, GLfloat green, GLfloat blue);
    void (APIENTRY *glSecondaryColor3fv)(const GLfloat *v);
    void (APIENTRY *glSecondaryColor3i)(GLint red, GLint green, GLint blue);
    void (APIENTRY *glSecondaryColor3iv)(const GLint *v);
    void (APIENTRY *glSecondaryColor3s)(GLshort red, GLshort green, GLshort blue);
    void (APIENTRY *glSecondaryColor3sv)(const GLshort *v);
    void (APIENTRY *glSecondaryColor3ub)(GLubyte red, GLubyte green,
                                         GLubyte blue);
    void (APIENTRY *glSecondaryColor3ubv)(const GLubyte *v);
    void (APIENTRY *glSecondaryColor3ui)(GLuint red, GLuint green, GLuint blue);
    void (APIENTRY *glSecondaryColor3uiv)(const GLuint *v);
    void (APIENTRY *glSecondaryColor3us)(GLushort red, GLushort green,
                                         GLushort blue);
    void (APIENTRY *glSecondaryColor3usv)(const GLushort *v);
    void (APIENTRY *glSecondaryColorPointer)(GLint size, GLenum type,
                                             GLsizei stride, const void *pointer);

    // Construction
    EXTSecondaryColor();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSecondaryColor

// GL_EXT_semaphore extension API specification.
struct EXTSemaphore {
    // Public Members
    void (APIENTRY *glDeleteSemaphores)(GLsizei n, const GLuint *semaphores);
    void (APIENTRY *glGenSemaphores)(GLsizei n, GLuint *semaphores);
    void (APIENTRY *glGetSemaphoreParameterui64v)(GLuint semaphore, GLenum pname,
                                                  GLuint64 *params);
    GLboolean(APIENTRY *glIsSemaphore)(GLuint semaphore);
    void (APIENTRY *glSemaphoreParameterui64v)(GLuint semaphore, GLenum pname,
                                               const GLuint64 *params);
    void (APIENTRY *glSignalSemaphore)(GLuint semaphore,
                                       GLuint numBufferBarriers,
                                       const GLuint *buffers,
                                       GLuint numTextureBarriers,
                                       const GLuint *textures,
                                       const GLenum *dstLayouts);
    void (APIENTRY *glWaitSemaphore)(GLuint semaphore, GLuint numBufferBarriers,
                                     const GLuint *buffers,
                                     GLuint numTextureBarriers,
                                     const GLuint *textures,
                                     const GLenum *srcLayouts);

    // Construction
    EXTSemaphore();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSemaphore

// GL_EXT_semaphore_fd extension API specification.
struct EXTSemaphoreFd {
    // Public Members
    void (APIENTRY *glImportSemaphoreFd)(GLuint semaphore, GLenum handleType,
                                         GLint fd);

    // Construction
    EXTSemaphoreFd();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSemaphoreFd

// GL_EXT_semaphore_win32 extension API specification.
struct EXTSemaphoreWIN32 {
    // Public Members
    void (APIENTRY *glImportSemaphoreWin32Handle)(GLuint semaphore,
                                                  GLenum handleType,
                                                  void *handle);
    void (APIENTRY *glImportSemaphoreWin32Name)(GLuint semaphore,
                                                GLenum handleType,
                                                const void *name);

    // Construction
    EXTSemaphoreWIN32();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSemaphoreWIN32

// GL_EXT_separate_shader_objects extension API specification.
struct EXTSeparateShaderObjects {
    // Public Members
    void (APIENTRY *glActiveProgram)(GLuint program);
    GLuint(APIENTRY *glCreateShaderProgram)(GLenum type, const GLchar *string);
    void (APIENTRY *glUseShaderProgram)(GLenum type, GLuint program);

    // Construction
    EXTSeparateShaderObjects();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSeparateShaderObjects

// GL_EXT_shader_framebuffer_fetch_non_coherent extension API specification.
struct EXTShaderFramebufferFetchNonCoherent {
    // Public Members
    void (APIENTRY *glFramebufferFetchBarrier)();

    // Construction
    EXTShaderFramebufferFetchNonCoherent();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTShaderFramebufferFetchNonCoherent

// GL_EXT_shader_image_load_store extension API specification.
struct EXTShaderImageLoadStore {
    // Public Members
    void (APIENTRY *glBindImageTexture)(GLuint index, GLuint texture,
                                        GLint level, GLboolean layered,
                                        GLint layer, GLenum access, GLint format);
    void (APIENTRY *glMemoryBarrier)(GLbitfield barriers);

    // Construction
    EXTShaderImageLoadStore();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTShaderImageLoadStore

// GL_EXT_stencil_clear_tag extension API specification.
struct EXTStencilClearTag {
    // Public Members
    void (APIENTRY *glStencilClearTag)(GLsizei stencilTagBits,
                                       GLuint stencilClearTag);

    // Construction
    EXTStencilClearTag();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTStencilClearTag

// GL_EXT_stencil_two_side extension API specification.
struct EXTStencilTwoSide {
    // Public Members
    void (APIENTRY *glActiveStencilFace)(GLenum face);

    // Construction
    EXTStencilTwoSide();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTStencilTwoSide

// GL_EXT_subtexture extension API specification.
struct EXTSubtexture {
    // Public Members
    void (APIENTRY *glTexSubImage1D)(GLenum target, GLint level, GLint xoffset,
                                     GLsizei width, GLenum format, GLenum type,
                                     const void *pixels);
    void (APIENTRY *glTexSubImage2D)(GLenum target, GLint level, GLint xoffset,
                                     GLint yoffset, GLsizei width,
                                     GLsizei height, GLenum format, GLenum type,
                                     const void *pixels);

    // Construction
    EXTSubtexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSubtexture

// GL_EXT_texture3D extension API specification.
struct EXTTEXTURE3D {
    // Public Members
    void (APIENTRY *glTexImage3D)(GLenum target, GLint level,
                                  GLenum internalformat, GLsizei width,
                                  GLsizei height, GLsizei depth, GLint border,
                                  GLenum format, GLenum type, const void *pixels);
    void (APIENTRY *glTexSubImage3D)(GLenum target, GLint level, GLint xoffset,
                                     GLint yoffset, GLint zoffset, GLsizei width,
                                     GLsizei height, GLsizei depth,
                                     GLenum format, GLenum type,
                                     const void *pixels);

    // Construction
    EXTTEXTURE3D();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTEXTURE3D

// GL_EXT_texture_array extension API specification.
struct EXTTextureArray {
    // Public Members
    void (APIENTRY *glFramebufferTextureLayer)(GLenum target, GLenum attachment,
                                               GLuint texture, GLint level,
                                               GLint layer);

    // Construction
    EXTTextureArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureArray

// GL_EXT_texture_buffer_object extension API specification.
struct EXTTextureBufferObject {
    // Public Members
    void (APIENTRY *glTexBuffer)(GLenum target, GLenum internalformat,
                                 GLuint buffer);

    // Construction
    EXTTextureBufferObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureBufferObject

// GL_EXT_texture_integer extension API specification.
struct EXTTextureInteger {
    // Public Members
    void (APIENTRY *glClearColorIi)(GLint red, GLint green, GLint blue,
                                    GLint alpha);
    void (APIENTRY *glClearColorIui)(GLuint red, GLuint green, GLuint blue,
                                     GLuint alpha);
    void (APIENTRY *glGetTexParameterIiv)(GLenum target, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glGetTexParameterIuiv)(GLenum target, GLenum pname,
                                           GLuint *params);
    void (APIENTRY *glTexParameterIiv)(GLenum target, GLenum pname,
                                       const GLint *params);
    void (APIENTRY *glTexParameterIuiv)(GLenum target, GLenum pname,
                                        const GLuint *params);

    // Construction
    EXTTextureInteger();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureInteger

// GL_EXT_texture_object extension API specification.
struct EXTTextureObject {
    // Public Members
    GLboolean(APIENTRY *glAreTexturesResident)(GLsizei n,
                                               const GLuint *textures,
                                               GLboolean *residences);
    void (APIENTRY *glBindTexture)(GLenum target, GLuint texture);
    void (APIENTRY *glDeleteTextures)(GLsizei n, const GLuint *textures);
    void (APIENTRY *glGenTextures)(GLsizei n, GLuint *textures);
    GLboolean(APIENTRY *glIsTexture)(GLuint texture);
    void (APIENTRY *glPrioritizeTextures)(GLsizei n, const GLuint *textures,
                                          const GLclampf *priorities);

    // Construction
    EXTTextureObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureObject

// GL_EXT_texture_perturb_normal extension API specification.
struct EXTTexturePerturbNormal {
    // Public Members
    void (APIENTRY *glTextureNormal)(GLenum mode);

    // Construction
    EXTTexturePerturbNormal();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTexturePerturbNormal

// GL_EXT_texture_storage extension API specification.
struct EXTTextureStorage {
    // Public Members
    void (APIENTRY *glTexStorage1D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width);
    void (APIENTRY *glTexStorage2D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width,
                                    GLsizei height);
    void (APIENTRY *glTexStorage3D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width,
                                    GLsizei height, GLsizei depth);

    // Construction
    EXTTextureStorage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureStorage

// GL_EXT_timer_query extension API specification.
struct EXTTimerQuery {
    // Public Members
    void (APIENTRY *glGetQueryObjecti64v)(GLuint id, GLenum pname,
                                          GLint64 *params);
    void (APIENTRY *glGetQueryObjectui64v)(GLuint id, GLenum pname,
                                           GLuint64 *params);

    // Construction
    EXTTimerQuery();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTimerQuery

// GL_EXT_transform_feedback extension API specification.
struct EXTTransformFeedback {
    // Public Members
    void (APIENTRY *glBeginTransformFeedback)(GLenum primitiveMode);
    void (APIENTRY *glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
    void (APIENTRY *glBindBufferOffset)(GLenum target, GLuint index,
                                        GLuint buffer, GLintptr offset);
    void (APIENTRY *glBindBufferRange)(GLenum target, GLuint index,
                                       GLuint buffer, GLintptr offset,
                                       GLsizeiptr size);
    void (APIENTRY *glEndTransformFeedback)();
    void (APIENTRY *glGetTransformFeedbackVarying)(GLuint program, GLuint index,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLsizei *size, GLenum *type,
                                                   GLchar *name);
    void (APIENTRY *glTransformFeedbackVaryings)(GLuint program, GLsizei count,
                                                 const GLchar *const *varyings,
                                                 GLenum bufferMode);

    // Construction
    EXTTransformFeedback();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTransformFeedback

// GL_EXT_vertex_array extension API specification.
struct EXTVertexArray {
    // Public Members
    void (APIENTRY *glArrayElement)(GLint i);
    void (APIENTRY *glColorPointer)(GLint size, GLenum type, GLsizei stride,
                                    GLsizei count, const void *pointer);
    void (APIENTRY *glDrawArrays)(GLenum mode, GLint first, GLsizei count);
    void (APIENTRY *glEdgeFlagPointer)(GLsizei stride, GLsizei count,
                                       const GLboolean *pointer);
    void (APIENTRY *glGetPointerv)(GLenum pname, void **params);
    void (APIENTRY *glIndexPointer)(GLenum type, GLsizei stride, GLsizei count,
                                    const void *pointer);
    void (APIENTRY *glNormalPointer)(GLenum type, GLsizei stride, GLsizei count,
                                     const void *pointer);
    void (APIENTRY *glTexCoordPointer)(GLint size, GLenum type, GLsizei stride,
                                       GLsizei count, const void *pointer);
    void (APIENTRY *glVertexPointer)(GLint size, GLenum type, GLsizei stride,
                                     GLsizei count, const void *pointer);

    // Construction
    EXTVertexArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTVertexArray

// GL_EXT_vertex_attrib_64bit extension API specification.
struct EXTVertexAttrib64BIT {
    // Public Members
    void (APIENTRY *glGetVertexAttribLdv)(GLuint index, GLenum pname,
                                          GLdouble *params);
    void (APIENTRY *glVertexAttribL1d)(GLuint index, GLdouble x);
    void (APIENTRY *glVertexAttribL1dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttribL2d)(GLuint index, GLdouble x, GLdouble y);
    void (APIENTRY *glVertexAttribL2dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttribL3d)(GLuint index, GLdouble x, GLdouble y,
                                       GLdouble z);
    void (APIENTRY *glVertexAttribL3dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttribL4d)(GLuint index, GLdouble x, GLdouble y,
                                       GLdouble z, GLdouble w);
    void (APIENTRY *glVertexAttribL4dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttribLPointer)(GLuint index, GLint size,
                                            GLenum type, GLsizei stride,
                                            const void *pointer);

    // Construction
    EXTVertexAttrib64BIT();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTVertexAttrib64BIT

// GL_EXT_vertex_shader extension API specification.
struct EXTVertexShader {
    // Public Members
    void (APIENTRY *glBeginVertexShader)();
    GLuint(APIENTRY *glBindLightParameter)(GLenum light, GLenum value);
    GLuint(APIENTRY *glBindMaterialParameter)(GLenum face, GLenum value);
    GLuint(APIENTRY *glBindParameter)(GLenum value);
    GLuint(APIENTRY *glBindTexGenParameter)(GLenum unit, GLenum coord,
                                            GLenum value);
    GLuint(APIENTRY *glBindTextureUnitParameter)(GLenum unit, GLenum value);
    void (APIENTRY *glBindVertexShader)(GLuint id);
    void (APIENTRY *glDeleteVertexShader)(GLuint id);
    void (APIENTRY *glDisableVariantClientState)(GLuint id);
    void (APIENTRY *glEnableVariantClientState)(GLuint id);
    void (APIENTRY *glEndVertexShader)();
    void (APIENTRY *glExtractComponent)(GLuint res, GLuint src, GLuint num);
    GLuint(APIENTRY *glGenSymbols)(GLenum datatype, GLenum storagetype,
                                   GLenum range, GLuint components);
    GLuint(APIENTRY *glGenVertexShaders)(GLuint range);
    void (APIENTRY *glGetInvariantBooleanv)(GLuint id, GLenum value,
                                            GLboolean *data);
    void (APIENTRY *glGetInvariantFloatv)(GLuint id, GLenum value, GLfloat *data);
    void (APIENTRY *glGetInvariantIntegerv)(GLuint id, GLenum value, GLint *data);
    void (APIENTRY *glGetLocalConstantBooleanv)(GLuint id, GLenum value,
                                                GLboolean *data);
    void (APIENTRY *glGetLocalConstantFloatv)(GLuint id, GLenum value,
                                              GLfloat *data);
    void (APIENTRY *glGetLocalConstantIntegerv)(GLuint id, GLenum value,
                                                GLint *data);
    void (APIENTRY *glGetVariantBooleanv)(GLuint id, GLenum value,
                                          GLboolean *data);
    void (APIENTRY *glGetVariantFloatv)(GLuint id, GLenum value, GLfloat *data);
    void (APIENTRY *glGetVariantIntegerv)(GLuint id, GLenum value, GLint *data);
    void (APIENTRY *glGetVariantPointerv)(GLuint id, GLenum value, void **data);
    void (APIENTRY *glInsertComponent)(GLuint res, GLuint src, GLuint num);
    GLboolean(APIENTRY *glIsVariantEnabled)(GLuint id, GLenum cap);
    void (APIENTRY *glSetInvariant)(GLuint id, GLenum type, const void *addr);
    void (APIENTRY *glSetLocalConstant)(GLuint id, GLenum type, const void *addr);
    void (APIENTRY *glShaderOp1)(GLenum op, GLuint res, GLuint arg1);
    void (APIENTRY *glShaderOp2)(GLenum op, GLuint res, GLuint arg1, GLuint arg2);
    void (APIENTRY *glShaderOp3)(GLenum op, GLuint res, GLuint arg1, GLuint arg2,
                                 GLuint arg3);
    void (APIENTRY *glSwizzle)(GLuint res, GLuint in, GLenum outX, GLenum outY,
                               GLenum outZ, GLenum outW);
    void (APIENTRY *glVariantPointer)(GLuint id, GLenum type, GLuint stride,
                                      const void *addr);
    void (APIENTRY *glVariantbv)(GLuint id, const GLbyte *addr);
    void (APIENTRY *glVariantdv)(GLuint id, const GLdouble *addr);
    void (APIENTRY *glVariantfv)(GLuint id, const GLfloat *addr);
    void (APIENTRY *glVariantiv)(GLuint id, const GLint *addr);
    void (APIENTRY *glVariantsv)(GLuint id, const GLshort *addr);
    void (APIENTRY *glVariantubv)(GLuint id, const GLubyte *addr);
    void (APIENTRY *glVariantuiv)(GLuint id, const GLuint *addr);
    void (APIENTRY *glVariantusv)(GLuint id, const GLushort *addr);
    void (APIENTRY *glWriteMask)(GLuint res, GLuint in, GLenum outX, GLenum outY,
                                 GLenum outZ, GLenum outW);

    // Construction
    EXTVertexShader();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTVertexShader

// GL_EXT_vertex_weighting extension API specification.
struct EXTVertexWeighting {
    // Public Members
    void (APIENTRY *glVertexWeightPointer)(GLint size, GLenum type,
                                           GLsizei stride, const void *pointer);
    void (APIENTRY *glVertexWeightf)(GLfloat weight);
    void (APIENTRY *glVertexWeightfv)(const GLfloat *weight);

    // Construction
    EXTVertexWeighting();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTVertexWeighting

// GL_EXT_win32_keyed_mutex extension API specification.
struct EXTWIN32KeyedMutex {
    // Public Members
    GLboolean(APIENTRY *glAcquireKeyedMutexWin32)(GLuint memory, GLuint64 key,
                                                  GLuint timeout);
    GLboolean(APIENTRY *glReleaseKeyedMutexWin32)(GLuint memory, GLuint64 key);

    // Construction
    EXTWIN32KeyedMutex();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTWIN32KeyedMutex

// GL_EXT_window_rectangles extension API specification.
struct EXTWindowRectangles {
    // Public Members
    void (APIENTRY *glWindowRectangles)(GLenum mode, GLsizei count,
                                        const GLint *box);

    // Construction
    EXTWindowRectangles();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTWindowRectangles

// GL_EXT_x11_sync_object extension API specification.
struct EXTX11SyncObject {
    // Public Members
    GLsync(APIENTRY *glImportSync)(GLenum external_sync_type,
                                   GLintptr external_sync, GLbitfield flags);

   // Construction
    EXTX11SyncObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTX11SyncObject


} // namespace gl

#ifdef _WIN32
namespace wgl {

// WGL_EXT_display_color_table extension API specification.
struct EXTDisplayColorTable {
    // Public Members
    GLboolean(APIENTRY *wglBindDisplayColorTable)(GLushort id);
    GLboolean(APIENTRY *wglCreateDisplayColorTable)(GLushort id);
    VOID(APIENTRY *wglDestroyDisplayColorTable)(GLushort id);
    GLboolean(APIENTRY *wglLoadDisplayColorTable)(const GLushort *table,
                                                  GLuint length);

   // Construction
    EXTDisplayColorTable();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTDisplayColorTable

// WGL_EXT_extensions_string extension API specification.
struct EXTExtensionsString {
    // Public Members
    const char *(APIENTRY *wglGetExtensionsString)();

    // Construction
    EXTExtensionsString();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTExtensionsString

// WGL_EXT_make_current_read extension API specification.
struct EXTMakeCurrentRead {
    // Public Members
    HDC(APIENTRY *wglGetCurrentReadDC)();
    BOOL(APIENTRY *wglMakeContextCurrent)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);

    // Construction
    EXTMakeCurrentRead();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTMakeCurrentRead

// WGL_EXT_pbuffer extension API specification.
struct EXTPbuffer {
    // Public Members
    HPBUFFEREXT(APIENTRY *wglCreatePbuffer)(HDC hDC, int iPixelFormat,
                                            int iWidth, int iHeight,
                                            const int *piAttribList);
    BOOL(APIENTRY *wglDestroyPbuffer)(HPBUFFEREXT hPbuffer);
    HDC(APIENTRY *wglGetPbufferDC)(HPBUFFEREXT hPbuffer);
    BOOL(APIENTRY *wglQueryPbuffer)(HPBUFFEREXT hPbuffer, int iAttribute,
                                    int *piValue);
    int (APIENTRY *wglReleasePbufferDC)(HPBUFFEREXT hPbuffer, HDC hDC);

    // Construction
    EXTPbuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPbuffer

// WGL_EXT_pixel_format extension API specification.
struct EXTPixelFormat {
    // Public Members
    BOOL(APIENTRY *wglChoosePixelFormat)(HDC hdc, const int *piAttribIList,
                                         const FLOAT *pfAttribFList,
                                         UINT nMaxFormats, int *piFormats,
                                         UINT *nNumFormats);
    BOOL(APIENTRY *wglGetPixelFormatAttribfv)(HDC hdc, int iPixelFormat,
                                              int iLayerPlane, UINT nAttributes,
                                              int *piAttributes,
                                              FLOAT *pfValues);
    BOOL(APIENTRY *wglGetPixelFormatAttribiv)(HDC hdc, int iPixelFormat,
                                              int iLayerPlane, UINT nAttributes,
                                              int *piAttributes, int *piValues);

   // Construction
    EXTPixelFormat();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTPixelFormat

// WGL_EXT_swap_control extension API specification.
struct EXTSwapControl {
    // Public Members
    int (APIENTRY *wglGetSwapInterval)();
    BOOL(APIENTRY *wglSwapInterval)(int interval);

    // Construction
    EXTSwapControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSwapControl

} // namespace wgl
#endif // ifdef _WIN32
#endif // Header guard

#ifdef _USES_GLX
namespace glx {

// GLX_EXT_import_context extension API specification.
struct EXTImportContext {
    // Public Members
    void (APIENTRY *glXFreeContext)(Display *dpy, GLXContext context);
    GLXContextID(APIENTRY *glXGetContextID)(const GLXContext context);
    Display *(APIENTRY *glXGetCurrentDisplay)();
    GLXContext(APIENTRY *glXImportContext)(Display *dpy, GLXContextID contextID);
    int (APIENTRY *glXQueryContextInfo)(Display *dpy, GLXContext context,
                                        int attribute, int *value);

    // Construction
    EXTImportContext();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTImportContext

// GLX_EXT_swap_control extension API specification.
struct EXTSwapControl {
    // Public Members
    void (APIENTRY *glXSwapInterval)(Display *dpy, GLXDrawable drawable,
                                     int interval);

    // Construction
    EXTSwapControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTSwapControl

// GLX_EXT_texture_from_pixmap extension API specification.
struct EXTTextureFromPixmap {
    // Public Members
    void (APIENTRY *glXBindTexImage)(Display *dpy, GLXDrawable drawable,
                                     int buffer, const int *attrib_list);
    void (APIENTRY *glXReleaseTexImage)(Display *dpy, GLXDrawable drawable,
                                        int buffer);

    // Construction
    EXTTextureFromPixmap();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct EXTTextureFromPixmap

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////
