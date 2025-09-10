//! @file Ag/ObjectGL/APIs.hpp
//! @brief The declaration of core profile OpenGL entry points.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __061B23F4_7783_415E_B538_DD0F5B335134_INCLUDED__
#define __061B23F4_7783_415E_B538_DD0F5B335134_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"

namespace gl {
////////////////////////////////////////////////////////////////////////////////
// API Command Groups
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure which contains pointers to all Core profile OpenGL
//! functions and contains the logic to resolve them by name.
struct GL {
    // Public Members

    // GL 1.0
#pragma region Core GL 1.0
    void (APIENTRY *glBlendFunc)(GLenum sfactor, GLenum dfactor);
    void (APIENTRY *glClear)(GLbitfield mask);
    void (APIENTRY *glClearColor)(GLfloat red, GLfloat green, GLfloat blue,
                                  GLfloat alpha);
    void (APIENTRY *glClearDepth)(GLdouble depth);
    void (APIENTRY *glClearStencil)(GLint s);
    void (APIENTRY *glColorMask)(GLboolean red, GLboolean green, GLboolean blue,
                                 GLboolean alpha);
    void (APIENTRY *glCullFace)(GLenum mode);
    void (APIENTRY *glDepthFunc)(GLenum func);
    void (APIENTRY *glDepthMask)(GLboolean flag);
    void (APIENTRY *glDepthRange)(GLdouble n, GLdouble f);
    void (APIENTRY *glDisable)(GLenum cap);
    void (APIENTRY *glDrawBuffer)(GLenum buf);
    void (APIENTRY *glEnable)(GLenum cap);
    void (APIENTRY *glFinish)();
    void (APIENTRY *glFlush)();
    void (APIENTRY *glFrontFace)(GLenum mode);
    void (APIENTRY *glGetBooleanv)(GLenum pname, GLboolean *data);
    void (APIENTRY *glGetDoublev)(GLenum pname, GLdouble *data);
    GLenum (APIENTRY *glGetError)();
    void (APIENTRY *glGetFloatv)(GLenum pname, GLfloat *data);
    void (APIENTRY *glGetIntegerv)(GLenum pname, GLint *data);
    const GLubyte *(APIENTRY *glGetString)(GLenum name);
    void (APIENTRY *glGetTexImage)(GLenum target, GLint level, GLenum format,
                                   GLenum type, void *pixels);
    void (APIENTRY *glGetTexLevelParameterfv)(GLenum target, GLint level,
                                              GLenum pname, GLfloat *params);
    void (APIENTRY *glGetTexLevelParameteriv)(GLenum target, GLint level,
                                              GLenum pname, GLint *params);
    void (APIENTRY *glGetTexParameterfv)(GLenum target, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetTexParameteriv)(GLenum target, GLenum pname,
                                         GLint *params);
    void (APIENTRY *glHint)(GLenum target, GLenum mode);
    GLboolean (APIENTRY *glIsEnabled)(GLenum cap);
    void (APIENTRY *glLineWidth)(GLfloat width);
    void (APIENTRY *glLogicOp)(GLenum opcode);
    void (APIENTRY *glPixelStoref)(GLenum pname, GLfloat param);
    void (APIENTRY *glPixelStorei)(GLenum pname, GLint param);
    void (APIENTRY *glPointSize)(GLfloat size);
    void (APIENTRY *glPolygonMode)(GLenum face, GLenum mode);
    void (APIENTRY *glReadBuffer)(GLenum src);
    void (APIENTRY *glReadPixels)(GLint x, GLint y, GLsizei width,
                                  GLsizei height, GLenum format, GLenum type,
                                  void *pixels);
    void (APIENTRY *glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
    void (APIENTRY *glStencilFunc)(GLenum func, GLint ref, GLuint mask);
    void (APIENTRY *glStencilMask)(GLuint mask);
    void (APIENTRY *glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
    void (APIENTRY *glTexImage1D)(GLenum target, GLint level,
                                  GLint internalformat, GLsizei width,
                                  GLint border, GLenum format, GLenum type,
                                  const void *pixels);
    void (APIENTRY *glTexImage2D)(GLenum target, GLint level,
                                  GLint internalformat, GLsizei width,
                                  GLsizei height, GLint border, GLenum format,
                                  GLenum type, const void *pixels);
    void (APIENTRY *glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
    void (APIENTRY *glTexParameterfv)(GLenum target, GLenum pname,
                                      const GLfloat *params);
    void (APIENTRY *glTexParameteri)(GLenum target, GLenum pname, GLint param);
    void (APIENTRY *glTexParameteriv)(GLenum target, GLenum pname,
                                      const GLint *params);
    void (APIENTRY *glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
#pragma endregion

    // GL 1.1
#pragma region Core GL 1.1
    void (APIENTRY *glBindTexture)(GLenum target, GLuint texture);
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
    void (APIENTRY *glDeleteTextures)(GLsizei n, const GLuint *textures);
    void (APIENTRY *glDrawArrays)(GLenum mode, GLint first, GLsizei count);
    void (APIENTRY *glDrawElements)(GLenum mode, GLsizei count, GLenum type,
                                    const void *indices);
    void (APIENTRY *glGenTextures)(GLsizei n, GLuint *textures);
    GLboolean (APIENTRY *glIsTexture)(GLuint texture);
    void (APIENTRY *glPolygonOffset)(GLfloat factor, GLfloat units);
    void (APIENTRY *glTexSubImage1D)(GLenum target, GLint level, GLint xoffset,
                                     GLsizei width, GLenum format, GLenum type,
                                     const void *pixels);
    void (APIENTRY *glTexSubImage2D)(GLenum target, GLint level, GLint xoffset,
                                     GLint yoffset, GLsizei width,
                                     GLsizei height, GLenum format, GLenum type,
                                     const void *pixels);
#pragma endregion

    // GL 1.2
#pragma region Core GL 1.2
    void (APIENTRY *glCopyTexSubImage3D)(GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLint x, GLint y,
                                         GLsizei width, GLsizei height);
    void (APIENTRY *glDrawRangeElements)(GLenum mode, GLuint start, GLuint end,
                                         GLsizei count, GLenum type,
                                         const void *indices);
    void (APIENTRY *glTexImage3D)(GLenum target, GLint level,
                                  GLint internalformat, GLsizei width,
                                  GLsizei height, GLsizei depth, GLint border,
                                  GLenum format, GLenum type, const void *pixels);
    void (APIENTRY *glTexSubImage3D)(GLenum target, GLint level, GLint xoffset,
                                     GLint yoffset, GLint zoffset, GLsizei width,
                                     GLsizei height, GLsizei depth,
                                     GLenum format, GLenum type,
                                     const void *pixels);
#pragma endregion

    // GL 1.3
#pragma region Core GL 1.3
    void (APIENTRY *glActiveTexture)(GLenum texture);
    void (APIENTRY *glCompressedTexImage1D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLint border, GLsizei imageSize,
                                            const void *data);
    void (APIENTRY *glCompressedTexImage2D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLsizei height, GLint border,
                                            GLsizei imageSize, const void *data);
    void (APIENTRY *glCompressedTexImage3D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLsizei height, GLsizei depth,
                                            GLint border, GLsizei imageSize,
                                            const void *data);
    void (APIENTRY *glCompressedTexSubImage1D)(GLenum target, GLint level,
                                               GLint xoffset, GLsizei width,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glCompressedTexSubImage2D)(GLenum target, GLint level,
                                               GLint xoffset, GLint yoffset,
                                               GLsizei width, GLsizei height,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glCompressedTexSubImage3D)(GLenum target, GLint level,
                                               GLint xoffset, GLint yoffset,
                                               GLint zoffset, GLsizei width,
                                               GLsizei height, GLsizei depth,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glGetCompressedTexImage)(GLenum target, GLint level,
                                             void *img);
    void (APIENTRY *glSampleCoverage)(GLfloat value, GLboolean invert);
#pragma endregion

    // GL 1.4
#pragma region Core GL 1.4
    void (APIENTRY *glBlendColor)(GLfloat red, GLfloat green, GLfloat blue,
                                  GLfloat alpha);
    void (APIENTRY *glBlendEquation)(GLenum mode);
    void (APIENTRY *glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB,
                                         GLenum sfactorAlpha,
                                         GLenum dfactorAlpha);
    void (APIENTRY *glMultiDrawArrays)(GLenum mode, const GLint *first,
                                       const GLsizei *count, GLsizei drawcount);
    void (APIENTRY *glMultiDrawElements)(GLenum mode, const GLsizei *count,
                                         GLenum type, const void *const*indices,
                                         GLsizei drawcount);
    void (APIENTRY *glPointParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPointParameterfv)(GLenum pname, const GLfloat *params);
    void (APIENTRY *glPointParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glPointParameteriv)(GLenum pname, const GLint *params);
#pragma endregion

    // GL 1.5
#pragma region Core GL 1.5
    void (APIENTRY *glBeginQuery)(GLenum target, GLuint id);
    void (APIENTRY *glBindBuffer)(GLenum target, GLuint buffer);
    void (APIENTRY *glBufferData)(GLenum target, GLsizeiptr size,
                                  const void *data, GLenum usage);
    void (APIENTRY *glBufferSubData)(GLenum target, GLintptr offset,
                                     GLsizeiptr size, const void *data);
    void (APIENTRY *glDeleteBuffers)(GLsizei n, const GLuint *buffers);
    void (APIENTRY *glDeleteQueries)(GLsizei n, const GLuint *ids);
    void (APIENTRY *glEndQuery)(GLenum target);
    void (APIENTRY *glGenBuffers)(GLsizei n, GLuint *buffers);
    void (APIENTRY *glGenQueries)(GLsizei n, GLuint *ids);
    void (APIENTRY *glGetBufferParameteriv)(GLenum target, GLenum pname,
                                            GLint *params);
    void (APIENTRY *glGetBufferPointerv)(GLenum target, GLenum pname,
                                         void **params);
    void (APIENTRY *glGetBufferSubData)(GLenum target, GLintptr offset,
                                        GLsizeiptr size, void *data);
    void (APIENTRY *glGetQueryObjectiv)(GLuint id, GLenum pname, GLint *params);
    void (APIENTRY *glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint *params);
    void (APIENTRY *glGetQueryiv)(GLenum target, GLenum pname, GLint *params);
    GLboolean (APIENTRY *glIsBuffer)(GLuint buffer);
    GLboolean (APIENTRY *glIsQuery)(GLuint id);
    void *(APIENTRY *glMapBuffer)(GLenum target, GLenum access);
    GLboolean (APIENTRY *glUnmapBuffer)(GLenum target);
#pragma endregion

    // GL 2.0
#pragma region Core GL 2.0
    void (APIENTRY *glAttachShader)(GLuint program, GLuint shader);
    void (APIENTRY *glBindAttribLocation)(GLuint program, GLuint index,
                                          const GLchar *name);
    void (APIENTRY *glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
    void (APIENTRY *glCompileShader)(GLuint shader);
    GLuint (APIENTRY *glCreateProgram)();
    GLuint (APIENTRY *glCreateShader)(GLenum type);
    void (APIENTRY *glDeleteProgram)(GLuint program);
    void (APIENTRY *glDeleteShader)(GLuint shader);
    void (APIENTRY *glDetachShader)(GLuint program, GLuint shader);
    void (APIENTRY *glDisableVertexAttribArray)(GLuint index);
    void (APIENTRY *glDrawBuffers)(GLsizei n, const GLenum *bufs);
    void (APIENTRY *glEnableVertexAttribArray)(GLuint index);
    void (APIENTRY *glGetActiveAttrib)(GLuint program, GLuint index,
                                       GLsizei bufSize, GLsizei *length,
                                       GLint *size, GLenum *type, GLchar *name);
    void (APIENTRY *glGetActiveUniform)(GLuint program, GLuint index,
                                        GLsizei bufSize, GLsizei *length,
                                        GLint *size, GLenum *type, GLchar *name);
    void (APIENTRY *glGetAttachedShaders)(GLuint program, GLsizei maxCount,
                                          GLsizei *count, GLuint *shaders);
    GLint (APIENTRY *glGetAttribLocation)(GLuint program, const GLchar *name);
    void (APIENTRY *glGetProgramInfoLog)(GLuint program, GLsizei bufSize,
                                         GLsizei *length, GLchar *infoLog);
    void (APIENTRY *glGetProgramiv)(GLuint program, GLenum pname, GLint *params);
    void (APIENTRY *glGetShaderInfoLog)(GLuint shader, GLsizei bufSize,
                                        GLsizei *length, GLchar *infoLog);
    void (APIENTRY *glGetShaderSource)(GLuint shader, GLsizei bufSize,
                                       GLsizei *length, GLchar *source);
    void (APIENTRY *glGetShaderiv)(GLuint shader, GLenum pname, GLint *params);
    GLint (APIENTRY *glGetUniformLocation)(GLuint program, const GLchar *name);
    void (APIENTRY *glGetUniformfv)(GLuint program, GLint location,
                                    GLfloat *params);
    void (APIENTRY *glGetUniformiv)(GLuint program, GLint location,
                                    GLint *params);
    void (APIENTRY *glGetVertexAttribPointerv)(GLuint index, GLenum pname,
                                               void **pointer);
    void (APIENTRY *glGetVertexAttribdv)(GLuint index, GLenum pname,
                                         GLdouble *params);
    void (APIENTRY *glGetVertexAttribfv)(GLuint index, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetVertexAttribiv)(GLuint index, GLenum pname,
                                         GLint *params);
    GLboolean (APIENTRY *glIsProgram)(GLuint program);
    GLboolean (APIENTRY *glIsShader)(GLuint shader);
    void (APIENTRY *glLinkProgram)(GLuint program);
    void (APIENTRY *glShaderSource)(GLuint shader, GLsizei count,
                                    const GLchar *const*string,
                                    const GLint *length);
    void (APIENTRY *glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref,
                                           GLuint mask);
    void (APIENTRY *glStencilMaskSeparate)(GLenum face, GLuint mask);
    void (APIENTRY *glStencilOpSeparate)(GLenum face, GLenum sfail,
                                         GLenum dpfail, GLenum dppass);
    void (APIENTRY *glUniform1f)(GLint location, GLfloat v0);
    void (APIENTRY *glUniform1fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform1i)(GLint location, GLint v0);
    void (APIENTRY *glUniform1iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
    void (APIENTRY *glUniform2fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform2i)(GLint location, GLint v0, GLint v1);
    void (APIENTRY *glUniform2iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform3f)(GLint location, GLfloat v0, GLfloat v1,
                                 GLfloat v2);
    void (APIENTRY *glUniform3fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
    void (APIENTRY *glUniform3iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform4f)(GLint location, GLfloat v0, GLfloat v1,
                                 GLfloat v2, GLfloat v3);
    void (APIENTRY *glUniform4fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2,
                                 GLint v3);
    void (APIENTRY *glUniform4iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniformMatrix2fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUniformMatrix3fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUniformMatrix4fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUseProgram)(GLuint program);
    void (APIENTRY *glValidateProgram)(GLuint program);
    void (APIENTRY *glVertexAttrib1d)(GLuint index, GLdouble x);
    void (APIENTRY *glVertexAttrib1dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib1f)(GLuint index, GLfloat x);
    void (APIENTRY *glVertexAttrib1fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib1s)(GLuint index, GLshort x);
    void (APIENTRY *glVertexAttrib1sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
    void (APIENTRY *glVertexAttrib2dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
    void (APIENTRY *glVertexAttrib2fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib2s)(GLuint index, GLshort x, GLshort y);
    void (APIENTRY *glVertexAttrib2sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z);
    void (APIENTRY *glVertexAttrib3dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z);
    void (APIENTRY *glVertexAttrib3fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib3s)(GLuint index, GLshort x, GLshort y,
                                      GLshort z);
    void (APIENTRY *glVertexAttrib3sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4Nbv)(GLuint index, const GLbyte *v);
    void (APIENTRY *glVertexAttrib4Niv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttrib4Nsv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y,
                                        GLubyte z, GLubyte w);
    void (APIENTRY *glVertexAttrib4Nubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttrib4Nuiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttrib4Nusv)(GLuint index, const GLushort *v);
    void (APIENTRY *glVertexAttrib4bv)(GLuint index, const GLbyte *v);
    void (APIENTRY *glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z, GLdouble w);
    void (APIENTRY *glVertexAttrib4dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z, GLfloat w);
    void (APIENTRY *glVertexAttrib4fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib4iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttrib4s)(GLuint index, GLshort x, GLshort y,
                                      GLshort z, GLshort w);
    void (APIENTRY *glVertexAttrib4sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4ubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttrib4uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttrib4usv)(GLuint index, const GLushort *v);
    void (APIENTRY *glVertexAttribPointer)(GLuint index, GLint size, GLenum type,
                                           GLboolean normalized, GLsizei stride,
                                           const void *pointer);
#pragma endregion

    // GL 2.1
#pragma region Core GL 2.1
    void (APIENTRY *glUniformMatrix2x3fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
    void (APIENTRY *glUniformMatrix2x4fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
    void (APIENTRY *glUniformMatrix3x2fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
    void (APIENTRY *glUniformMatrix3x4fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
    void (APIENTRY *glUniformMatrix4x2fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
    void (APIENTRY *glUniformMatrix4x3fv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLfloat *value);
#pragma endregion

    // GL 3.0
#pragma region Core GL 3.0
    void (APIENTRY *glBeginConditionalRender)(GLuint id, GLenum mode);
    void (APIENTRY *glBeginTransformFeedback)(GLenum primitiveMode);
    void (APIENTRY *glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
    void (APIENTRY *glBindBufferRange)(GLenum target, GLuint index,
                                       GLuint buffer, GLintptr offset,
                                       GLsizeiptr size);
    void (APIENTRY *glBindFragDataLocation)(GLuint program, GLuint color,
                                            const GLchar *name);
    void (APIENTRY *glBindFramebuffer)(GLenum target, GLuint framebuffer);
    void (APIENTRY *glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
    void (APIENTRY *glBindVertexArray)(GLuint array);
    void (APIENTRY *glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1,
                                       GLint srcY1, GLint dstX0, GLint dstY0,
                                       GLint dstX1, GLint dstY1, GLbitfield mask,
                                       GLenum filter);
    GLenum (APIENTRY *glCheckFramebufferStatus)(GLenum target);
    void (APIENTRY *glClampColor)(GLenum target, GLenum clamp);
    void (APIENTRY *glClearBufferfi)(GLenum buffer, GLint drawbuffer,
                                     GLfloat depth, GLint stencil);
    void (APIENTRY *glClearBufferfv)(GLenum buffer, GLint drawbuffer,
                                     const GLfloat *value);
    void (APIENTRY *glClearBufferiv)(GLenum buffer, GLint drawbuffer,
                                     const GLint *value);
    void (APIENTRY *glClearBufferuiv)(GLenum buffer, GLint drawbuffer,
                                      const GLuint *value);
    void (APIENTRY *glColorMaski)(GLuint index, GLboolean r, GLboolean g,
                                  GLboolean b, GLboolean a);
    void (APIENTRY *glDeleteFramebuffers)(GLsizei n, const GLuint *framebuffers);
    void (APIENTRY *glDeleteRenderbuffers)(GLsizei n,
                                           const GLuint *renderbuffers);
    void (APIENTRY *glDeleteVertexArrays)(GLsizei n, const GLuint *arrays);
    void (APIENTRY *glDisablei)(GLenum target, GLuint index);
    void (APIENTRY *glEnablei)(GLenum target, GLuint index);
    void (APIENTRY *glEndConditionalRender)();
    void (APIENTRY *glEndTransformFeedback)();
    void (APIENTRY *glFlushMappedBufferRange)(GLenum target, GLintptr offset,
                                              GLsizeiptr length);
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
    void (APIENTRY *glFramebufferTextureLayer)(GLenum target, GLenum attachment,
                                               GLuint texture, GLint level,
                                               GLint layer);
    void (APIENTRY *glGenFramebuffers)(GLsizei n, GLuint *framebuffers);
    void (APIENTRY *glGenRenderbuffers)(GLsizei n, GLuint *renderbuffers);
    void (APIENTRY *glGenVertexArrays)(GLsizei n, GLuint *arrays);
    void (APIENTRY *glGenerateMipmap)(GLenum target);
    void (APIENTRY *glGetBooleani_v)(GLenum target, GLuint index,
                                     GLboolean *data);
    GLint (APIENTRY *glGetFragDataLocation)(GLuint program, const GLchar *name);
    void (APIENTRY *glGetFramebufferAttachmentParameteriv)(GLenum target,
                                                           GLenum attachment,
                                                           GLenum pname,
                                                           GLint *params);
    void (APIENTRY *glGetIntegeri_v)(GLenum target, GLuint index, GLint *data);
    void (APIENTRY *glGetRenderbufferParameteriv)(GLenum target, GLenum pname,
                                                  GLint *params);
    const GLubyte *(APIENTRY *glGetStringi)(GLenum name, GLuint index);
    void (APIENTRY *glGetTexParameterIiv)(GLenum target, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glGetTexParameterIuiv)(GLenum target, GLenum pname,
                                           GLuint *params);
    void (APIENTRY *glGetTransformFeedbackVarying)(GLuint program, GLuint index,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLsizei *size, GLenum *type,
                                                   GLchar *name);
    void (APIENTRY *glGetUniformuiv)(GLuint program, GLint location,
                                     GLuint *params);
    void (APIENTRY *glGetVertexAttribIiv)(GLuint index, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glGetVertexAttribIuiv)(GLuint index, GLenum pname,
                                           GLuint *params);
    GLboolean (APIENTRY *glIsEnabledi)(GLenum target, GLuint index);
    GLboolean (APIENTRY *glIsFramebuffer)(GLuint framebuffer);
    GLboolean (APIENTRY *glIsRenderbuffer)(GLuint renderbuffer);
    GLboolean (APIENTRY *glIsVertexArray)(GLuint array);
    void *(APIENTRY *glMapBufferRange)(GLenum target, GLintptr offset,
                                       GLsizeiptr length, GLbitfield access);
    void (APIENTRY *glRenderbufferStorage)(GLenum target, GLenum internalformat,
                                           GLsizei width, GLsizei height);
    void (APIENTRY *glRenderbufferStorageMultisample)(GLenum target,
                                                      GLsizei samples,
                                                      GLenum internalformat,
                                                      GLsizei width,
                                                      GLsizei height);
    void (APIENTRY *glTexParameterIiv)(GLenum target, GLenum pname,
                                       const GLint *params);
    void (APIENTRY *glTexParameterIuiv)(GLenum target, GLenum pname,
                                        const GLuint *params);
    void (APIENTRY *glTransformFeedbackVaryings)(GLuint program, GLsizei count,
                                                 const GLchar *const*varyings,
                                                 GLenum bufferMode);
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
#pragma endregion

    // GL 3.1
#pragma region Core GL 3.1
    void (APIENTRY *glCopyBufferSubData)(GLenum readTarget, GLenum writeTarget,
                                         GLintptr readOffset,
                                         GLintptr writeOffset, GLsizeiptr size);
    void (APIENTRY *glDrawArraysInstanced)(GLenum mode, GLint first,
                                           GLsizei count, GLsizei instancecount);
    void (APIENTRY *glDrawElementsInstanced)(GLenum mode, GLsizei count,
                                             GLenum type, const void *indices,
                                             GLsizei instancecount);
    void (APIENTRY *glGetActiveUniformBlockName)(GLuint program,
                                                 GLuint uniformBlockIndex,
                                                 GLsizei bufSize,
                                                 GLsizei *length,
                                                 GLchar *uniformBlockName);
    void (APIENTRY *glGetActiveUniformBlockiv)(GLuint program,
                                               GLuint uniformBlockIndex,
                                               GLenum pname, GLint *params);
    void (APIENTRY *glGetActiveUniformName)(GLuint program, GLuint uniformIndex,
                                            GLsizei bufSize, GLsizei *length,
                                            GLchar *uniformName);
    void (APIENTRY *glGetActiveUniformsiv)(GLuint program, GLsizei uniformCount,
                                           const GLuint *uniformIndices,
                                           GLenum pname, GLint *params);
    GLuint (APIENTRY *glGetUniformBlockIndex)(GLuint program,
                                              const GLchar *uniformBlockName);
    void (APIENTRY *glGetUniformIndices)(GLuint program, GLsizei uniformCount,
                                         const GLchar *const*uniformNames,
                                         GLuint *uniformIndices);
    void (APIENTRY *glPrimitiveRestartIndex)(GLuint index);
    void (APIENTRY *glTexBuffer)(GLenum target, GLenum internalformat,
                                 GLuint buffer);
    void (APIENTRY *glUniformBlockBinding)(GLuint program,
                                           GLuint uniformBlockIndex,
                                           GLuint uniformBlockBinding);
#pragma endregion

    // GL 3.2
#pragma region Core GL 3.2
    GLenum (APIENTRY *glClientWaitSync)(GLsync sync, GLbitfield flags,
                                        GLuint64 timeout);
    void (APIENTRY *glDeleteSync)(GLsync sync);
    void (APIENTRY *glDrawElementsBaseVertex)(GLenum mode, GLsizei count,
                                              GLenum type, const void *indices,
                                              GLint basevertex);
    void (APIENTRY *glDrawElementsInstancedBaseVertex)(GLenum mode,
                                                       GLsizei count,
                                                       GLenum type,
                                                       const void *indices,
                                                       GLsizei instancecount,
                                                       GLint basevertex);
    void (APIENTRY *glDrawRangeElementsBaseVertex)(GLenum mode, GLuint start,
                                                   GLuint end, GLsizei count,
                                                   GLenum type,
                                                   const void *indices,
                                                   GLint basevertex);
    GLsync (APIENTRY *glFenceSync)(GLenum condition, GLbitfield flags);
    void (APIENTRY *glFramebufferTexture)(GLenum target, GLenum attachment,
                                          GLuint texture, GLint level);
    void (APIENTRY *glGetBufferParameteri64v)(GLenum target, GLenum pname,
                                              GLint64 *params);
    void (APIENTRY *glGetInteger64i_v)(GLenum target, GLuint index,
                                       GLint64 *data);
    void (APIENTRY *glGetInteger64v)(GLenum pname, GLint64 *data);
    void (APIENTRY *glGetMultisamplefv)(GLenum pname, GLuint index, GLfloat *val);
    void (APIENTRY *glGetSynciv)(GLsync sync, GLenum pname, GLsizei count,
                                 GLsizei *length, GLint *values);
    GLboolean (APIENTRY *glIsSync)(GLsync sync);
    void (APIENTRY *glMultiDrawElementsBaseVertex)(GLenum mode,
                                                   const GLsizei *count,
                                                   GLenum type,
                                                   const void *const*indices,
                                                   GLsizei drawcount,
                                                   const GLint *basevertex);
    void (APIENTRY *glProvokingVertex)(GLenum mode);
    void (APIENTRY *glSampleMaski)(GLuint maskNumber, GLbitfield mask);
    void (APIENTRY *glTexImage2DMultisample)(GLenum target, GLsizei samples,
                                             GLenum internalformat,
                                             GLsizei width, GLsizei height,
                                             GLboolean fixedsamplelocations);
    void (APIENTRY *glTexImage3DMultisample)(GLenum target, GLsizei samples,
                                             GLenum internalformat,
                                             GLsizei width, GLsizei height,
                                             GLsizei depth,
                                             GLboolean fixedsamplelocations);
    void (APIENTRY *glWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
#pragma endregion

    // GL 3.3
#pragma region Core GL 3.3
    void (APIENTRY *glBindFragDataLocationIndexed)(GLuint program,
                                                   GLuint colorNumber,
                                                   GLuint index,
                                                   const GLchar *name);
    void (APIENTRY *glBindSampler)(GLuint unit, GLuint sampler);
    void (APIENTRY *glDeleteSamplers)(GLsizei count, const GLuint *samplers);
    void (APIENTRY *glGenSamplers)(GLsizei count, GLuint *samplers);
    GLint (APIENTRY *glGetFragDataIndex)(GLuint program, const GLchar *name);
    void (APIENTRY *glGetQueryObjecti64v)(GLuint id, GLenum pname,
                                          GLint64 *params);
    void (APIENTRY *glGetQueryObjectui64v)(GLuint id, GLenum pname,
                                           GLuint64 *params);
    void (APIENTRY *glGetSamplerParameterIiv)(GLuint sampler, GLenum pname,
                                              GLint *params);
    void (APIENTRY *glGetSamplerParameterIuiv)(GLuint sampler, GLenum pname,
                                               GLuint *params);
    void (APIENTRY *glGetSamplerParameterfv)(GLuint sampler, GLenum pname,
                                             GLfloat *params);
    void (APIENTRY *glGetSamplerParameteriv)(GLuint sampler, GLenum pname,
                                             GLint *params);
    GLboolean (APIENTRY *glIsSampler)(GLuint sampler);
    void (APIENTRY *glQueryCounter)(GLuint id, GLenum target);
    void (APIENTRY *glSamplerParameterIiv)(GLuint sampler, GLenum pname,
                                           const GLint *param);
    void (APIENTRY *glSamplerParameterIuiv)(GLuint sampler, GLenum pname,
                                            const GLuint *param);
    void (APIENTRY *glSamplerParameterf)(GLuint sampler, GLenum pname,
                                         GLfloat param);
    void (APIENTRY *glSamplerParameterfv)(GLuint sampler, GLenum pname,
                                          const GLfloat *param);
    void (APIENTRY *glSamplerParameteri)(GLuint sampler, GLenum pname,
                                         GLint param);
    void (APIENTRY *glSamplerParameteriv)(GLuint sampler, GLenum pname,
                                          const GLint *param);
    void (APIENTRY *glVertexAttribDivisor)(GLuint index, GLuint divisor);
    void (APIENTRY *glVertexAttribP1ui)(GLuint index, GLenum type,
                                        GLboolean normalized, GLuint value);
    void (APIENTRY *glVertexAttribP1uiv)(GLuint index, GLenum type,
                                         GLboolean normalized,
                                         const GLuint *value);
    void (APIENTRY *glVertexAttribP2ui)(GLuint index, GLenum type,
                                        GLboolean normalized, GLuint value);
    void (APIENTRY *glVertexAttribP2uiv)(GLuint index, GLenum type,
                                         GLboolean normalized,
                                         const GLuint *value);
    void (APIENTRY *glVertexAttribP3ui)(GLuint index, GLenum type,
                                        GLboolean normalized, GLuint value);
    void (APIENTRY *glVertexAttribP3uiv)(GLuint index, GLenum type,
                                         GLboolean normalized,
                                         const GLuint *value);
    void (APIENTRY *glVertexAttribP4ui)(GLuint index, GLenum type,
                                        GLboolean normalized, GLuint value);
    void (APIENTRY *glVertexAttribP4uiv)(GLuint index, GLenum type,
                                         GLboolean normalized,
                                         const GLuint *value);
#pragma endregion

    // GL 4.0
#pragma region Core GL 4.0
    void (APIENTRY *glBeginQueryIndexed)(GLenum target, GLuint index, GLuint id);
    void (APIENTRY *glBindTransformFeedback)(GLenum target, GLuint id);
    void (APIENTRY *glBlendEquationSeparatei)(GLuint buf, GLenum modeRGB,
                                              GLenum modeAlpha);
    void (APIENTRY *glBlendEquationi)(GLuint buf, GLenum mode);
    void (APIENTRY *glBlendFuncSeparatei)(GLuint buf, GLenum srcRGB,
                                          GLenum dstRGB, GLenum srcAlpha,
                                          GLenum dstAlpha);
    void (APIENTRY *glBlendFunci)(GLuint buf, GLenum src, GLenum dst);
    void (APIENTRY *glDeleteTransformFeedbacks)(GLsizei n, const GLuint *ids);
    void (APIENTRY *glDrawArraysIndirect)(GLenum mode, const void *indirect);
    void (APIENTRY *glDrawElementsIndirect)(GLenum mode, GLenum type,
                                            const void *indirect);
    void (APIENTRY *glDrawTransformFeedback)(GLenum mode, GLuint id);
    void (APIENTRY *glDrawTransformFeedbackStream)(GLenum mode, GLuint id,
                                                   GLuint stream);
    void (APIENTRY *glEndQueryIndexed)(GLenum target, GLuint index);
    void (APIENTRY *glGenTransformFeedbacks)(GLsizei n, GLuint *ids);
    void (APIENTRY *glGetActiveSubroutineName)(GLuint program, GLenum shadertype,
                                               GLuint index, GLsizei bufSize,
                                               GLsizei *length, GLchar *name);
    void (APIENTRY *glGetActiveSubroutineUniformName)(GLuint program,
                                                      GLenum shadertype,
                                                      GLuint index,
                                                      GLsizei bufSize,
                                                      GLsizei *length,
                                                      GLchar *name);
    void (APIENTRY *glGetActiveSubroutineUniformiv)(GLuint program,
                                                    GLenum shadertype,
                                                    GLuint index, GLenum pname,
                                                    GLint *values);
    void (APIENTRY *glGetProgramStageiv)(GLuint program, GLenum shadertype,
                                         GLenum pname, GLint *values);
    void (APIENTRY *glGetQueryIndexediv)(GLenum target, GLuint index,
                                         GLenum pname, GLint *params);
    GLuint (APIENTRY *glGetSubroutineIndex)(GLuint program, GLenum shadertype,
                                            const GLchar *name);
    GLint (APIENTRY *glGetSubroutineUniformLocation)(GLuint program,
                                                     GLenum shadertype,
                                                     const GLchar *name);
    void (APIENTRY *glGetUniformSubroutineuiv)(GLenum shadertype, GLint location,
                                               GLuint *params);
    void (APIENTRY *glGetUniformdv)(GLuint program, GLint location,
                                    GLdouble *params);
    GLboolean (APIENTRY *glIsTransformFeedback)(GLuint id);
    void (APIENTRY *glMinSampleShading)(GLfloat value);
    void (APIENTRY *glPatchParameterfv)(GLenum pname, const GLfloat *values);
    void (APIENTRY *glPatchParameteri)(GLenum pname, GLint value);
    void (APIENTRY *glPauseTransformFeedback)();
    void (APIENTRY *glResumeTransformFeedback)();
    void (APIENTRY *glUniform1d)(GLint location, GLdouble x);
    void (APIENTRY *glUniform1dv)(GLint location, GLsizei count,
                                  const GLdouble *value);
    void (APIENTRY *glUniform2d)(GLint location, GLdouble x, GLdouble y);
    void (APIENTRY *glUniform2dv)(GLint location, GLsizei count,
                                  const GLdouble *value);
    void (APIENTRY *glUniform3d)(GLint location, GLdouble x, GLdouble y,
                                 GLdouble z);
    void (APIENTRY *glUniform3dv)(GLint location, GLsizei count,
                                  const GLdouble *value);
    void (APIENTRY *glUniform4d)(GLint location, GLdouble x, GLdouble y,
                                 GLdouble z, GLdouble w);
    void (APIENTRY *glUniform4dv)(GLint location, GLsizei count,
                                  const GLdouble *value);
    void (APIENTRY *glUniformMatrix2dv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLdouble *value);
    void (APIENTRY *glUniformMatrix2x3dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformMatrix2x4dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformMatrix3dv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLdouble *value);
    void (APIENTRY *glUniformMatrix3x2dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformMatrix3x4dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformMatrix4dv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLdouble *value);
    void (APIENTRY *glUniformMatrix4x2dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformMatrix4x3dv)(GLint location, GLsizei count,
                                          GLboolean transpose,
                                          const GLdouble *value);
    void (APIENTRY *glUniformSubroutinesuiv)(GLenum shadertype, GLsizei count,
                                             const GLuint *indices);
#pragma endregion

    // GL 4.1
#pragma region Core GL 4.1
    void (APIENTRY *glActiveShaderProgram)(GLuint pipeline, GLuint program);
    void (APIENTRY *glBindProgramPipeline)(GLuint pipeline);
    void (APIENTRY *glClearDepthf)(GLfloat d);
    GLuint (APIENTRY *glCreateShaderProgramv)(GLenum type, GLsizei count,
                                              const GLchar *const*strings);
    void (APIENTRY *glDeleteProgramPipelines)(GLsizei n, const GLuint *pipelines);
    void (APIENTRY *glDepthRangeArrayv)(GLuint first, GLsizei count,
                                        const GLdouble *v);
    void (APIENTRY *glDepthRangeIndexed)(GLuint index, GLdouble n, GLdouble f);
    void (APIENTRY *glDepthRangef)(GLfloat n, GLfloat f);
    void (APIENTRY *glGenProgramPipelines)(GLsizei n, GLuint *pipelines);
    void (APIENTRY *glGetDoublei_v)(GLenum target, GLuint index, GLdouble *data);
    void (APIENTRY *glGetFloati_v)(GLenum target, GLuint index, GLfloat *data);
    void (APIENTRY *glGetProgramBinary)(GLuint program, GLsizei bufSize,
                                        GLsizei *length, GLenum *binaryFormat,
                                        void *binary);
    void (APIENTRY *glGetProgramPipelineInfoLog)(GLuint pipeline,
                                                 GLsizei bufSize,
                                                 GLsizei *length,
                                                 GLchar *infoLog);
    void (APIENTRY *glGetProgramPipelineiv)(GLuint pipeline, GLenum pname,
                                            GLint *params);
    void (APIENTRY *glGetShaderPrecisionFormat)(GLenum shadertype,
                                                GLenum precisiontype,
                                                GLint *range, GLint *precision);
    void (APIENTRY *glGetVertexAttribLdv)(GLuint index, GLenum pname,
                                          GLdouble *params);
    GLboolean (APIENTRY *glIsProgramPipeline)(GLuint pipeline);
    void (APIENTRY *glProgramBinary)(GLuint program, GLenum binaryFormat,
                                     const void *binary, GLsizei length);
    void (APIENTRY *glProgramParameteri)(GLuint program, GLenum pname,
                                         GLint value);
    void (APIENTRY *glProgramUniform1d)(GLuint program, GLint location,
                                        GLdouble v0);
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
                                        GLdouble v0, GLdouble v1);
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
                                        GLdouble v0, GLdouble v1, GLdouble v2);
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
                                        GLdouble v0, GLdouble v1, GLdouble v2,
                                        GLdouble v3);
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
    void (APIENTRY *glReleaseShaderCompiler)();
    void (APIENTRY *glScissorArrayv)(GLuint first, GLsizei count, const GLint *v);
    void (APIENTRY *glScissorIndexed)(GLuint index, GLint left, GLint bottom,
                                      GLsizei width, GLsizei height);
    void (APIENTRY *glScissorIndexedv)(GLuint index, const GLint *v);
    void (APIENTRY *glShaderBinary)(GLsizei count, const GLuint *shaders,
                                    GLenum binaryFormat, const void *binary,
                                    GLsizei length);
    void (APIENTRY *glUseProgramStages)(GLuint pipeline, GLbitfield stages,
                                        GLuint program);
    void (APIENTRY *glValidateProgramPipeline)(GLuint pipeline);
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
    void (APIENTRY *glViewportArrayv)(GLuint first, GLsizei count,
                                      const GLfloat *v);
    void (APIENTRY *glViewportIndexedf)(GLuint index, GLfloat x, GLfloat y,
                                        GLfloat w, GLfloat h);
    void (APIENTRY *glViewportIndexedfv)(GLuint index, const GLfloat *v);
#pragma endregion

    // GL 4.2
#pragma region Core GL 4.2
    void (APIENTRY *glBindImageTexture)(GLuint unit, GLuint texture, GLint level,
                                        GLboolean layered, GLint layer,
                                        GLenum access, GLenum format);
    void (APIENTRY *glDrawArraysInstancedBaseInstance)(GLenum mode, GLint first,
                                                       GLsizei count,
                                                       GLsizei instancecount,
                                                       GLuint baseinstance);
    void (APIENTRY *glDrawElementsInstancedBaseInstance)(GLenum mode,
                                                         GLsizei count,
                                                         GLenum type,
                                                         const void *indices,
                                                         GLsizei instancecount,
                                                         GLuint baseinstance);
    void (APIENTRY *glDrawElementsInstancedBaseVertexBaseInstance)(GLenum mode,
                                                                   GLsizei count,
                                                                   GLenum type,
                                                                   const void *indices,
                                                                   GLsizei instancecount,
                                                                   GLint basevertex,
                                                                   GLuint baseinstance);
    void (APIENTRY *glDrawTransformFeedbackInstanced)(GLenum mode, GLuint id,
                                                      GLsizei instancecount);
    void (APIENTRY *glDrawTransformFeedbackStreamInstanced)(GLenum mode,
                                                            GLuint id,
                                                            GLuint stream,
                                                            GLsizei instancecount);
    void (APIENTRY *glGetActiveAtomicCounterBufferiv)(GLuint program,
                                                      GLuint bufferIndex,
                                                      GLenum pname,
                                                      GLint *params);
    void (APIENTRY *glGetInternalformativ)(GLenum target, GLenum internalformat,
                                           GLenum pname, GLsizei count,
                                           GLint *params);
    void (APIENTRY *glMemoryBarrier)(GLbitfield barriers);
    void (APIENTRY *glTexStorage1D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width);
    void (APIENTRY *glTexStorage2D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width,
                                    GLsizei height);
    void (APIENTRY *glTexStorage3D)(GLenum target, GLsizei levels,
                                    GLenum internalformat, GLsizei width,
                                    GLsizei height, GLsizei depth);
#pragma endregion

    // GL 4.3
#pragma region Core GL 4.3
    void (APIENTRY *glBindVertexBuffer)(GLuint bindingindex, GLuint buffer,
                                        GLintptr offset, GLsizei stride);
    void (APIENTRY *glClearBufferData)(GLenum target, GLenum internalformat,
                                       GLenum format, GLenum type,
                                       const void *data);
    void (APIENTRY *glClearBufferSubData)(GLenum target, GLenum internalformat,
                                          GLintptr offset, GLsizeiptr size,
                                          GLenum format, GLenum type,
                                          const void *data);
    void (APIENTRY *glCopyImageSubData)(GLuint srcName, GLenum srcTarget,
                                        GLint srcLevel, GLint srcX, GLint srcY,
                                        GLint srcZ, GLuint dstName,
                                        GLenum dstTarget, GLint dstLevel,
                                        GLint dstX, GLint dstY, GLint dstZ,
                                        GLsizei srcWidth, GLsizei srcHeight,
                                        GLsizei srcDepth);
    void (APIENTRY *glDebugMessageCallback)(GLDEBUGPROC callback,
                                            const void *userParam);
    void (APIENTRY *glDebugMessageControl)(GLenum source, GLenum type,
                                           GLenum severity, GLsizei count,
                                           const GLuint *ids, GLboolean enabled);
    void (APIENTRY *glDebugMessageInsert)(GLenum source, GLenum type, GLuint id,
                                          GLenum severity, GLsizei length,
                                          const GLchar *buf);
    void (APIENTRY *glDispatchCompute)(GLuint num_groups_x, GLuint num_groups_y,
                                       GLuint num_groups_z);
    void (APIENTRY *glDispatchComputeIndirect)(GLintptr indirect);
    void (APIENTRY *glFramebufferParameteri)(GLenum target, GLenum pname,
                                             GLint param);
    GLuint (APIENTRY *glGetDebugMessageLog)(GLuint count, GLsizei bufSize,
                                            GLenum *sources, GLenum *types,
                                            GLuint *ids, GLenum *severities,
                                            GLsizei *lengths, GLchar *messageLog);
    void (APIENTRY *glGetFramebufferParameteriv)(GLenum target, GLenum pname,
                                                 GLint *params);
    void (APIENTRY *glGetInternalformati64v)(GLenum target,
                                             GLenum internalformat, GLenum pname,
                                             GLsizei count, GLint64 *params);
    void (APIENTRY *glGetObjectLabel)(GLenum identifier, GLuint name,
                                      GLsizei bufSize, GLsizei *length,
                                      GLchar *label);
    void (APIENTRY *glGetObjectPtrLabel)(const void *ptr, GLsizei bufSize,
                                         GLsizei *length, GLchar *label);
    void (APIENTRY *glGetPointerv)(GLenum pname, void **params);
    void (APIENTRY *glGetProgramInterfaceiv)(GLuint program,
                                             GLenum programInterface,
                                             GLenum pname, GLint *params);
    GLuint (APIENTRY *glGetProgramResourceIndex)(GLuint program,
                                                 GLenum programInterface,
                                                 const GLchar *name);
    GLint (APIENTRY *glGetProgramResourceLocation)(GLuint program,
                                                   GLenum programInterface,
                                                   const GLchar *name);
    GLint (APIENTRY *glGetProgramResourceLocationIndex)(GLuint program,
                                                        GLenum programInterface,
                                                        const GLchar *name);
    void (APIENTRY *glGetProgramResourceName)(GLuint program,
                                              GLenum programInterface,
                                              GLuint index, GLsizei bufSize,
                                              GLsizei *length, GLchar *name);
    void (APIENTRY *glGetProgramResourceiv)(GLuint program,
                                            GLenum programInterface,
                                            GLuint index, GLsizei propCount,
                                            const GLenum *props, GLsizei count,
                                            GLsizei *length, GLint *params);
    void (APIENTRY *glInvalidateBufferData)(GLuint buffer);
    void (APIENTRY *glInvalidateBufferSubData)(GLuint buffer, GLintptr offset,
                                               GLsizeiptr length);
    void (APIENTRY *glInvalidateFramebuffer)(GLenum target,
                                             GLsizei numAttachments,
                                             const GLenum *attachments);
    void (APIENTRY *glInvalidateSubFramebuffer)(GLenum target,
                                                GLsizei numAttachments,
                                                const GLenum *attachments,
                                                GLint x, GLint y, GLsizei width,
                                                GLsizei height);
    void (APIENTRY *glInvalidateTexImage)(GLuint texture, GLint level);
    void (APIENTRY *glInvalidateTexSubImage)(GLuint texture, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint zoffset, GLsizei width,
                                             GLsizei height, GLsizei depth);
    void (APIENTRY *glMultiDrawArraysIndirect)(GLenum mode, const void *indirect,
                                               GLsizei drawcount, GLsizei stride);
    void (APIENTRY *glMultiDrawElementsIndirect)(GLenum mode, GLenum type,
                                                 const void *indirect,
                                                 GLsizei drawcount,
                                                 GLsizei stride);
    void (APIENTRY *glObjectLabel)(GLenum identifier, GLuint name,
                                   GLsizei length, const GLchar *label);
    void (APIENTRY *glObjectPtrLabel)(const void *ptr, GLsizei length,
                                      const GLchar *label);
    void (APIENTRY *glPopDebugGroup)();
    void (APIENTRY *glPushDebugGroup)(GLenum source, GLuint id, GLsizei length,
                                      const GLchar *message);
    void (APIENTRY *glShaderStorageBlockBinding)(GLuint program,
                                                 GLuint storageBlockIndex,
                                                 GLuint storageBlockBinding);
    void (APIENTRY *glTexBufferRange)(GLenum target, GLenum internalformat,
                                      GLuint buffer, GLintptr offset,
                                      GLsizeiptr size);
    void (APIENTRY *glTexStorage2DMultisample)(GLenum target, GLsizei samples,
                                               GLenum internalformat,
                                               GLsizei width, GLsizei height,
                                               GLboolean fixedsamplelocations);
    void (APIENTRY *glTexStorage3DMultisample)(GLenum target, GLsizei samples,
                                               GLenum internalformat,
                                               GLsizei width, GLsizei height,
                                               GLsizei depth,
                                               GLboolean fixedsamplelocations);
    void (APIENTRY *glTextureView)(GLuint texture, GLenum target,
                                   GLuint origtexture, GLenum internalformat,
                                   GLuint minlevel, GLuint numlevels,
                                   GLuint minlayer, GLuint numlayers);
    void (APIENTRY *glVertexAttribBinding)(GLuint attribindex,
                                           GLuint bindingindex);
    void (APIENTRY *glVertexAttribFormat)(GLuint attribindex, GLint size,
                                          GLenum type, GLboolean normalized,
                                          GLuint relativeoffset);
    void (APIENTRY *glVertexAttribIFormat)(GLuint attribindex, GLint size,
                                           GLenum type, GLuint relativeoffset);
    void (APIENTRY *glVertexAttribLFormat)(GLuint attribindex, GLint size,
                                           GLenum type, GLuint relativeoffset);
    void (APIENTRY *glVertexBindingDivisor)(GLuint bindingindex, GLuint divisor);
#pragma endregion

    // GL 4.4
#pragma region Core GL 4.4
    void (APIENTRY *glBindBuffersBase)(GLenum target, GLuint first,
                                       GLsizei count, const GLuint *buffers);
    void (APIENTRY *glBindBuffersRange)(GLenum target, GLuint first,
                                        GLsizei count, const GLuint *buffers,
                                        const GLintptr *offsets,
                                        const GLsizeiptr *sizes);
    void (APIENTRY *glBindImageTextures)(GLuint first, GLsizei count,
                                         const GLuint *textures);
    void (APIENTRY *glBindSamplers)(GLuint first, GLsizei count,
                                    const GLuint *samplers);
    void (APIENTRY *glBindTextures)(GLuint first, GLsizei count,
                                    const GLuint *textures);
    void (APIENTRY *glBindVertexBuffers)(GLuint first, GLsizei count,
                                         const GLuint *buffers,
                                         const GLintptr *offsets,
                                         const GLsizei *strides);
    void (APIENTRY *glBufferStorage)(GLenum target, GLsizeiptr size,
                                     const void *data, GLbitfield flags);
    void (APIENTRY *glClearTexImage)(GLuint texture, GLint level, GLenum format,
                                     GLenum type, const void *data);
    void (APIENTRY *glClearTexSubImage)(GLuint texture, GLint level,
                                        GLint xoffset, GLint yoffset,
                                        GLint zoffset, GLsizei width,
                                        GLsizei height, GLsizei depth,
                                        GLenum format, GLenum type,
                                        const void *data);
#pragma endregion

    // GL 4.5
#pragma region Core GL 4.5
    void (APIENTRY *glBindTextureUnit)(GLuint unit, GLuint texture);
    void (APIENTRY *glBlitNamedFramebuffer)(GLuint readFramebuffer,
                                            GLuint drawFramebuffer, GLint srcX0,
                                            GLint srcY0, GLint srcX1,
                                            GLint srcY1, GLint dstX0,
                                            GLint dstY0, GLint dstX1,
                                            GLint dstY1, GLbitfield mask,
                                            GLenum filter);
    GLenum (APIENTRY *glCheckNamedFramebufferStatus)(GLuint framebuffer,
                                                     GLenum target);
    void (APIENTRY *glClearNamedBufferData)(GLuint buffer, GLenum internalformat,
                                            GLenum format, GLenum type,
                                            const void *data);
    void (APIENTRY *glClearNamedBufferSubData)(GLuint buffer,
                                               GLenum internalformat,
                                               GLintptr offset, GLsizeiptr size,
                                               GLenum format, GLenum type,
                                               const void *data);
    void (APIENTRY *glClearNamedFramebufferfi)(GLuint framebuffer, GLenum buffer,
                                               GLint drawbuffer, GLfloat depth,
                                               GLint stencil);
    void (APIENTRY *glClearNamedFramebufferfv)(GLuint framebuffer, GLenum buffer,
                                               GLint drawbuffer,
                                               const GLfloat *value);
    void (APIENTRY *glClearNamedFramebufferiv)(GLuint framebuffer, GLenum buffer,
                                               GLint drawbuffer,
                                               const GLint *value);
    void (APIENTRY *glClearNamedFramebufferuiv)(GLuint framebuffer,
                                                GLenum buffer, GLint drawbuffer,
                                                const GLuint *value);
    void (APIENTRY *glClipControl)(GLenum origin, GLenum depth);
    void (APIENTRY *glCompressedTextureSubImage1D)(GLuint texture, GLint level,
                                                   GLint xoffset, GLsizei width,
                                                   GLenum format,
                                                   GLsizei imageSize,
                                                   const void *data);
    void (APIENTRY *glCompressedTextureSubImage2D)(GLuint texture, GLint level,
                                                   GLint xoffset, GLint yoffset,
                                                   GLsizei width, GLsizei height,
                                                   GLenum format,
                                                   GLsizei imageSize,
                                                   const void *data);
    void (APIENTRY *glCompressedTextureSubImage3D)(GLuint texture, GLint level,
                                                   GLint xoffset, GLint yoffset,
                                                   GLint zoffset, GLsizei width,
                                                   GLsizei height, GLsizei depth,
                                                   GLenum format,
                                                   GLsizei imageSize,
                                                   const void *data);
    void (APIENTRY *glCopyNamedBufferSubData)(GLuint readBuffer,
                                              GLuint writeBuffer,
                                              GLintptr readOffset,
                                              GLintptr writeOffset,
                                              GLsizeiptr size);
    void (APIENTRY *glCopyTextureSubImage1D)(GLuint texture, GLint level,
                                             GLint xoffset, GLint x, GLint y,
                                             GLsizei width);
    void (APIENTRY *glCopyTextureSubImage2D)(GLuint texture, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint x, GLint y, GLsizei width,
                                             GLsizei height);
    void (APIENTRY *glCopyTextureSubImage3D)(GLuint texture, GLint level,
                                             GLint xoffset, GLint yoffset,
                                             GLint zoffset, GLint x, GLint y,
                                             GLsizei width, GLsizei height);
    void (APIENTRY *glCreateBuffers)(GLsizei n, GLuint *buffers);
    void (APIENTRY *glCreateFramebuffers)(GLsizei n, GLuint *framebuffers);
    void (APIENTRY *glCreateProgramPipelines)(GLsizei n, GLuint *pipelines);
    void (APIENTRY *glCreateQueries)(GLenum target, GLsizei n, GLuint *ids);
    void (APIENTRY *glCreateRenderbuffers)(GLsizei n, GLuint *renderbuffers);
    void (APIENTRY *glCreateSamplers)(GLsizei n, GLuint *samplers);
    void (APIENTRY *glCreateTextures)(GLenum target, GLsizei n, GLuint *textures);
    void (APIENTRY *glCreateTransformFeedbacks)(GLsizei n, GLuint *ids);
    void (APIENTRY *glCreateVertexArrays)(GLsizei n, GLuint *arrays);
    void (APIENTRY *glDisableVertexArrayAttrib)(GLuint vaobj, GLuint index);
    void (APIENTRY *glEnableVertexArrayAttrib)(GLuint vaobj, GLuint index);
    void (APIENTRY *glFlushMappedNamedBufferRange)(GLuint buffer,
                                                   GLintptr offset,
                                                   GLsizeiptr length);
    void (APIENTRY *glGenerateTextureMipmap)(GLuint texture);
    void (APIENTRY *glGetCompressedTextureImage)(GLuint texture, GLint level,
                                                 GLsizei bufSize, void *pixels);
    void (APIENTRY *glGetCompressedTextureSubImage)(GLuint texture, GLint level,
                                                    GLint xoffset, GLint yoffset,
                                                    GLint zoffset, GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth,
                                                    GLsizei bufSize,
                                                    void *pixels);
    GLenum (APIENTRY *glGetGraphicsResetStatus)();
    void (APIENTRY *glGetNamedBufferParameteri64v)(GLuint buffer, GLenum pname,
                                                   GLint64 *params);
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
                                                      GLenum pname, GLint *param);
    void (APIENTRY *glGetNamedRenderbufferParameteriv)(GLuint renderbuffer,
                                                       GLenum pname,
                                                       GLint *params);
    void (APIENTRY *glGetQueryBufferObjecti64v)(GLuint id, GLuint buffer,
                                                GLenum pname, GLintptr offset);
    void (APIENTRY *glGetQueryBufferObjectiv)(GLuint id, GLuint buffer,
                                              GLenum pname, GLintptr offset);
    void (APIENTRY *glGetQueryBufferObjectui64v)(GLuint id, GLuint buffer,
                                                 GLenum pname, GLintptr offset);
    void (APIENTRY *glGetQueryBufferObjectuiv)(GLuint id, GLuint buffer,
                                               GLenum pname, GLintptr offset);
    void (APIENTRY *glGetTextureImage)(GLuint texture, GLint level,
                                       GLenum format, GLenum type,
                                       GLsizei bufSize, void *pixels);
    void (APIENTRY *glGetTextureLevelParameterfv)(GLuint texture, GLint level,
                                                  GLenum pname, GLfloat *params);
    void (APIENTRY *glGetTextureLevelParameteriv)(GLuint texture, GLint level,
                                                  GLenum pname, GLint *params);
    void (APIENTRY *glGetTextureParameterIiv)(GLuint texture, GLenum pname,
                                              GLint *params);
    void (APIENTRY *glGetTextureParameterIuiv)(GLuint texture, GLenum pname,
                                               GLuint *params);
    void (APIENTRY *glGetTextureParameterfv)(GLuint texture, GLenum pname,
                                             GLfloat *params);
    void (APIENTRY *glGetTextureParameteriv)(GLuint texture, GLenum pname,
                                             GLint *params);
    void (APIENTRY *glGetTextureSubImage)(GLuint texture, GLint level,
                                          GLint xoffset, GLint yoffset,
                                          GLint zoffset, GLsizei width,
                                          GLsizei height, GLsizei depth,
                                          GLenum format, GLenum type,
                                          GLsizei bufSize, void *pixels);
    void (APIENTRY *glGetTransformFeedbacki64_v)(GLuint xfb, GLenum pname,
                                                 GLuint index, GLint64 *param);
    void (APIENTRY *glGetTransformFeedbacki_v)(GLuint xfb, GLenum pname,
                                               GLuint index, GLint *param);
    void (APIENTRY *glGetTransformFeedbackiv)(GLuint xfb, GLenum pname,
                                              GLint *param);
    void (APIENTRY *glGetVertexArrayIndexed64iv)(GLuint vaobj, GLuint index,
                                                 GLenum pname, GLint64 *param);
    void (APIENTRY *glGetVertexArrayIndexediv)(GLuint vaobj, GLuint index,
                                               GLenum pname, GLint *param);
    void (APIENTRY *glGetVertexArrayiv)(GLuint vaobj, GLenum pname, GLint *param);
    void (APIENTRY *glGetnCompressedTexImage)(GLenum target, GLint lod,
                                              GLsizei bufSize, void *pixels);
    void (APIENTRY *glGetnTexImage)(GLenum target, GLint level, GLenum format,
                                    GLenum type, GLsizei bufSize, void *pixels);
    void (APIENTRY *glGetnUniformdv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLdouble *params);
    void (APIENTRY *glGetnUniformfv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLfloat *params);
    void (APIENTRY *glGetnUniformiv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLint *params);
    void (APIENTRY *glGetnUniformuiv)(GLuint program, GLint location,
                                      GLsizei bufSize, GLuint *params);
    void (APIENTRY *glInvalidateNamedFramebufferData)(GLuint framebuffer,
                                                      GLsizei numAttachments,
                                                      const GLenum *attachments);
    void (APIENTRY *glInvalidateNamedFramebufferSubData)(GLuint framebuffer,
                                                         GLsizei numAttachments,
                                                         const GLenum *attachments,
                                                         GLint x, GLint y,
                                                         GLsizei width,
                                                         GLsizei height);
    void *(APIENTRY *glMapNamedBuffer)(GLuint buffer, GLenum access);
    void *(APIENTRY *glMapNamedBufferRange)(GLuint buffer, GLintptr offset,
                                            GLsizeiptr length, GLbitfield access);
    void (APIENTRY *glMemoryBarrierByRegion)(GLbitfield barriers);
    void (APIENTRY *glNamedBufferData)(GLuint buffer, GLsizeiptr size,
                                       const void *data, GLenum usage);
    void (APIENTRY *glNamedBufferStorage)(GLuint buffer, GLsizeiptr size,
                                          const void *data, GLbitfield flags);
    void (APIENTRY *glNamedBufferSubData)(GLuint buffer, GLintptr offset,
                                          GLsizeiptr size, const void *data);
    void (APIENTRY *glNamedFramebufferDrawBuffer)(GLuint framebuffer, GLenum buf);
    void (APIENTRY *glNamedFramebufferDrawBuffers)(GLuint framebuffer, GLsizei n,
                                                   const GLenum *bufs);
    void (APIENTRY *glNamedFramebufferParameteri)(GLuint framebuffer,
                                                  GLenum pname, GLint param);
    void (APIENTRY *glNamedFramebufferReadBuffer)(GLuint framebuffer, GLenum src);
    void (APIENTRY *glNamedFramebufferRenderbuffer)(GLuint framebuffer,
                                                    GLenum attachment,
                                                    GLenum renderbuffertarget,
                                                    GLuint renderbuffer);
    void (APIENTRY *glNamedFramebufferTexture)(GLuint framebuffer,
                                               GLenum attachment, GLuint texture,
                                               GLint level);
    void (APIENTRY *glNamedFramebufferTextureLayer)(GLuint framebuffer,
                                                    GLenum attachment,
                                                    GLuint texture, GLint level,
                                                    GLint layer);
    void (APIENTRY *glNamedRenderbufferStorage)(GLuint renderbuffer,
                                                GLenum internalformat,
                                                GLsizei width, GLsizei height);
    void (APIENTRY *glNamedRenderbufferStorageMultisample)(GLuint renderbuffer,
                                                           GLsizei samples,
                                                           GLenum internalformat,
                                                           GLsizei width,
                                                           GLsizei height);
    void (APIENTRY *glReadnPixels)(GLint x, GLint y, GLsizei width,
                                   GLsizei height, GLenum format, GLenum type,
                                   GLsizei bufSize, void *data);
    void (APIENTRY *glTextureBarrier)();
    void (APIENTRY *glTextureBuffer)(GLuint texture, GLenum internalformat,
                                     GLuint buffer);
    void (APIENTRY *glTextureBufferRange)(GLuint texture, GLenum internalformat,
                                          GLuint buffer, GLintptr offset,
                                          GLsizeiptr size);
    void (APIENTRY *glTextureParameterIiv)(GLuint texture, GLenum pname,
                                           const GLint *params);
    void (APIENTRY *glTextureParameterIuiv)(GLuint texture, GLenum pname,
                                            const GLuint *params);
    void (APIENTRY *glTextureParameterf)(GLuint texture, GLenum pname,
                                         GLfloat param);
    void (APIENTRY *glTextureParameterfv)(GLuint texture, GLenum pname,
                                          const GLfloat *param);
    void (APIENTRY *glTextureParameteri)(GLuint texture, GLenum pname,
                                         GLint param);
    void (APIENTRY *glTextureParameteriv)(GLuint texture, GLenum pname,
                                          const GLint *param);
    void (APIENTRY *glTextureStorage1D)(GLuint texture, GLsizei levels,
                                        GLenum internalformat, GLsizei width);
    void (APIENTRY *glTextureStorage2D)(GLuint texture, GLsizei levels,
                                        GLenum internalformat, GLsizei width,
                                        GLsizei height);
    void (APIENTRY *glTextureStorage2DMultisample)(GLuint texture,
                                                   GLsizei samples,
                                                   GLenum internalformat,
                                                   GLsizei width, GLsizei height,
                                                   GLboolean fixedsamplelocations);
    void (APIENTRY *glTextureStorage3D)(GLuint texture, GLsizei levels,
                                        GLenum internalformat, GLsizei width,
                                        GLsizei height, GLsizei depth);
    void (APIENTRY *glTextureStorage3DMultisample)(GLuint texture,
                                                   GLsizei samples,
                                                   GLenum internalformat,
                                                   GLsizei width, GLsizei height,
                                                   GLsizei depth,
                                                   GLboolean fixedsamplelocations);
    void (APIENTRY *glTextureSubImage1D)(GLuint texture, GLint level,
                                         GLint xoffset, GLsizei width,
                                         GLenum format, GLenum type,
                                         const void *pixels);
    void (APIENTRY *glTextureSubImage2D)(GLuint texture, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLsizei width, GLsizei height,
                                         GLenum format, GLenum type,
                                         const void *pixels);
    void (APIENTRY *glTextureSubImage3D)(GLuint texture, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLsizei width,
                                         GLsizei height, GLsizei depth,
                                         GLenum format, GLenum type,
                                         const void *pixels);
    void (APIENTRY *glTransformFeedbackBufferBase)(GLuint xfb, GLuint index,
                                                   GLuint buffer);
    void (APIENTRY *glTransformFeedbackBufferRange)(GLuint xfb, GLuint index,
                                                    GLuint buffer,
                                                    GLintptr offset,
                                                    GLsizeiptr size);
    GLboolean (APIENTRY *glUnmapNamedBuffer)(GLuint buffer);
    void (APIENTRY *glVertexArrayAttribBinding)(GLuint vaobj, GLuint attribindex,
                                                GLuint bindingindex);
    void (APIENTRY *glVertexArrayAttribFormat)(GLuint vaobj, GLuint attribindex,
                                               GLint size, GLenum type,
                                               GLboolean normalized,
                                               GLuint relativeoffset);
    void (APIENTRY *glVertexArrayAttribIFormat)(GLuint vaobj, GLuint attribindex,
                                                GLint size, GLenum type,
                                                GLuint relativeoffset);
    void (APIENTRY *glVertexArrayAttribLFormat)(GLuint vaobj, GLuint attribindex,
                                                GLint size, GLenum type,
                                                GLuint relativeoffset);
    void (APIENTRY *glVertexArrayBindingDivisor)(GLuint vaobj,
                                                 GLuint bindingindex,
                                                 GLuint divisor);
    void (APIENTRY *glVertexArrayElementBuffer)(GLuint vaobj, GLuint buffer);
    void (APIENTRY *glVertexArrayVertexBuffer)(GLuint vaobj, GLuint bindingindex,
                                               GLuint buffer, GLintptr offset,
                                               GLsizei stride);
    void (APIENTRY *glVertexArrayVertexBuffers)(GLuint vaobj, GLuint first,
                                                GLsizei count,
                                                const GLuint *buffers,
                                                const GLintptr *offsets,
                                                const GLsizei *strides);
#pragma endregion

    // GL 4.6
#pragma region Core GL 4.6
    void (APIENTRY *glMultiDrawArraysIndirectCount)(GLenum mode,
                                                    const void *indirect,
                                                    GLintptr drawcount,
                                                    GLsizei maxdrawcount,
                                                    GLsizei stride);
    void (APIENTRY *glMultiDrawElementsIndirectCount)(GLenum mode, GLenum type,
                                                      const void *indirect,
                                                      GLintptr drawcount,
                                                      GLsizei maxdrawcount,
                                                      GLsizei stride);
    void (APIENTRY *glPolygonOffsetClamp)(GLfloat factor, GLfloat units,
                                          GLfloat clamp);
    void (APIENTRY *glSpecializeShader)(GLuint shader, const GLchar *pEntryPoint,
                                        GLuint numSpecializationConstants,
                                        const GLuint *pConstantIndex,
                                        const GLuint *pConstantValue);
#pragma endregion

    // Construction
    GL();

    // Operations
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct GL

} // namespace gl

#endif // ifndef __061B23F4_7783_415E_B538_DD0F5B335134_INCLUDED__
