//! @file Ag/ObjectGL/CommandSets.hpp
//! @brief The declaration of wrappers for core profile OpenGL entry points.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __C887F2C6_25FE_46FA_A234_66CE1D192F9E_INCLUDED__
#define __C887F2C6_25FE_46FA_A234_66CE1D192F9E_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Version.hpp"
#include "APIs.hpp"
#include "EnumTypes.hpp"
#include "Identifiers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class which wraps all core profile OpenGL entry points so that they
//! can be called with more useful data types and with inherit type checking and
//! error detection.
class GLAPI : public BaseAPI
{
public:
    // Construction
    GLAPI();

    // Accessors
    const GL &getRawAPI() const;
    const Ag::Version &getAPIVersion() const;

    // Operations
    void verifyAPIVersion(const Ag::Version &minRequired, const char *feature) const;

#pragma region OpenGL Commands
#pragma region Core GL 1.0
    // GL 1.0
    void blendFunc(BlendingFactor sfactor, BlendingFactor dfactor) const;
    void clear(GLbitfield  /* ClearBufferMask */ mask) const;
    void clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const;
    void clearDepth(GLdouble depth) const;
    void clearStencil(GLint s) const;
    void colorMask(Boolean red, Boolean green, Boolean blue, Boolean alpha) const;
    void cullFace(CullFaceMode mode) const;
    void depthFunc(DepthFunction func) const;
    void depthMask(Boolean flag) const;
    void depthRange(GLdouble n, GLdouble f) const;
    void disable(EnableCap cap) const;
    void drawBuffer(DrawBufferMode buf) const;
    void enable(EnableCap cap) const;
    void finish() const;
    void flush() const;
    void frontFace(FrontFaceDirection mode) const;
    void getBooleanV(GetPName pname, Boolean *data) const;
    void getDoubleV(GetPName pname, GLdouble *data) const;
    ErrorCode getError() const;
    void getFloatV(GetPName pname, GLfloat *data) const;
    void getIntegerV(GetPName pname, GLint *data) const;
    const GLubyte *getString(StringName name) const;
    void getTexImage(TextureTarget target, GLint level, PixelFormat format,
                     PixelType type, void *pixels) const;
    void getTexLevelParameterFV(TextureTarget target, GLint level,
                                GetTextureParameter pname, GLfloat *params) const;
    void getTexLevelParameterIV(TextureTarget target, GLint level,
                                GetTextureParameter pname, GLint *params) const;
    void getTexParameterFV(TextureTarget target, GetTextureParameter pname,
                           GLfloat *params) const;
    void getTexParameterIV(TextureTarget target, GetTextureParameter pname,
                           GLint *params) const;
    void hint(HintTarget target, HintMode mode) const;
    Boolean isEnabled(EnableCap cap) const;
    void lineWidth(GLfloat width) const;
    void logicOp(LogicOp opcode) const;
    void pixelStoreF(PixelStoreParameter pname, GLfloat param) const;
    void pixelStoreI(PixelStoreParameter pname, GLint param) const;
    void pointSize(GLfloat size) const;
    void polygonMode(MaterialFace face, PolygonMode mode) const;
    void readBuffer(ReadBufferMode src) const;
    void readPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                    PixelFormat format, PixelType type, void *pixels) const;
    void scissor(GLint x, GLint y, GLsizei width, GLsizei height) const;
    void stencilFunc(StencilFunction func, GLint ref, GLuint mask) const;
    void stencilMask(GLuint mask) const;
    void stencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass) const;
    void texImage1D(TextureTarget target, GLint level,
                    InternalFormat internalformat, GLsizei width, GLint border,
                    PixelFormat format, PixelType type, const void *pixels) const;
    void texImage2D(TextureTarget target, GLint level,
                    InternalFormat internalformat, GLsizei width, GLsizei height,
                    GLint border, PixelFormat format, PixelType type,
                    const void *pixels) const;
    void texParameterF(TextureTarget target, TextureParameterName pname,
                       GLfloat param) const;
    void texParameterFV(TextureTarget target, TextureParameterName pname,
                        const GLfloat *params) const;
    void texParameterI(TextureTarget target, TextureParameterName pname,
                       GLint param) const;
    void texParameterIV(TextureTarget target, TextureParameterName pname,
                        const GLint *params) const;
    void viewport(GLint x, GLint y, GLsizei width, GLsizei height) const;
#pragma endregion

#pragma region Core GL 1.1
    // GL 1.1
    void bindTexture(TextureTarget target, TextureName texture) const;
    void copyTexImage1D(TextureTarget target, GLint level,
                        InternalFormat internalformat, GLint x, GLint y,
                        GLsizei width, GLint border) const;
    void copyTexImage2D(TextureTarget target, GLint level,
                        InternalFormat internalformat, GLint x, GLint y,
                        GLsizei width, GLsizei height, GLint border) const;
    void copyTexSubImage1D(TextureTarget target, GLint level, GLint xoffset,
                           GLint x, GLint y, GLsizei width) const;
    void copyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset,
                           GLint yoffset, GLint x, GLint y, GLsizei width,
                           GLsizei height) const;
    void deleteTextures(GLsizei n, const TextureName *textures) const;
    void drawArrays(PrimitiveType mode, GLint first, GLsizei count) const;
    void drawElements(PrimitiveType mode, GLsizei count, DrawElementsType type,
                      const void *indices) const;
    void genTextures(GLsizei n, TextureName *textures) const;
    Boolean isTexture(TextureName texture) const;
    void polygonOffset(GLfloat factor, GLfloat units) const;
    void texSubImage1D(TextureTarget target, GLint level, GLint xoffset,
                       GLsizei width, PixelFormat format, PixelType type,
                       const void *pixels) const;
    void texSubImage2D(TextureTarget target, GLint level, GLint xoffset,
                       GLint yoffset, GLsizei width, GLsizei height,
                       PixelFormat format, PixelType type, const void *pixels) const;
#pragma endregion

#pragma region Core GL 1.2
    // GL 1.2
    void copyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                           GLint yoffset, GLint zoffset, GLint x, GLint y,
                           GLsizei width, GLsizei height) const;
    void drawRangeElements(PrimitiveType mode, GLuint start, GLuint end,
                           GLsizei count, DrawElementsType type,
                           const void *indices) const;
    void texImage3D(TextureTarget target, GLint level,
                    InternalFormat internalformat, GLsizei width, GLsizei height,
                    GLsizei depth, GLint border, PixelFormat format,
                    PixelType type, const void *pixels) const;
    void texSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                       GLint yoffset, GLint zoffset, GLsizei width,
                       GLsizei height, GLsizei depth, PixelFormat format,
                       PixelType type, const void *pixels) const;
#pragma endregion

#pragma region Core GL 1.3
    // GL 1.3
    void activeTexture(TextureUnit texture) const;
    void compressedTexImage1D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLint border, GLsizei imageSize, const void *data) const;
    void compressedTexImage2D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLsizei height, GLint border, GLsizei imageSize,
                              const void *data) const;
    void compressedTexImage3D(TextureTarget target, GLint level,
                              InternalFormat internalformat, GLsizei width,
                              GLsizei height, GLsizei depth, GLint border,
                              GLsizei imageSize, const void *data) const;
    void compressedTexSubImage1D(TextureTarget target, GLint level,
                                 GLint xoffset, GLsizei width,
                                 InternalFormat format, GLsizei imageSize,
                                 const void *data) const;
    void compressedTexSubImage2D(TextureTarget target, GLint level,
                                 GLint xoffset, GLint yoffset, GLsizei width,
                                 GLsizei height, InternalFormat format,
                                 GLsizei imageSize, const void *data) const;
    void compressedTexSubImage3D(TextureTarget target, GLint level,
                                 GLint xoffset, GLint yoffset, GLint zoffset,
                                 GLsizei width, GLsizei height, GLsizei depth,
                                 InternalFormat format, GLsizei imageSize,
                                 const void *data) const;
    void getCompressedTexImage(TextureTarget target, GLint level, void *img) const;
    void sampleCoverage(GLfloat value, Boolean invert) const;
#pragma endregion

#pragma region Core GL 1.4
    // GL 1.4
    void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const;
    void blendEquation(BlendEquationModeEXT mode) const;
    void blendFuncSeparate(BlendingFactor sfactorRGB, BlendingFactor dfactorRGB,
                           BlendingFactor sfactorAlpha,
                           BlendingFactor dfactorAlpha) const;
    void multiDrawArrays(PrimitiveType mode, const GLint *first,
                         const GLsizei *count, GLsizei drawcount) const;
    void multiDrawElements(PrimitiveType mode, const GLsizei *count,
                           DrawElementsType type, const void *const*indices,
                           GLsizei drawcount) const;
    void pointParameterF(PointParameterNameARB pname, GLfloat param) const;
    void pointParameterFV(PointParameterNameARB pname, const GLfloat *params) const;
    void pointParameterI(PointParameterNameARB pname, GLint param) const;
    void pointParameterIV(PointParameterNameARB pname, const GLint *params) const;
#pragma endregion

#pragma region Core GL 1.5
    // GL 1.5
    void beginQuery(QueryTarget target, QueryName id) const;
    void bindBuffer(BufferTarget target, BufferName buffer) const;
    void bufferData(BufferTarget target, GLsizeiptr size, const void *data,
                    BufferUsage usage) const;
    void bufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size,
                       const void *data) const;
    void deleteBuffers(GLsizei n, const BufferName *buffers) const;
    void deleteQueries(GLsizei n, const QueryName *ids) const;
    void endQuery(QueryTarget target) const;
    void genBuffers(GLsizei n, BufferName *buffers) const;
    void genQueries(GLsizei n, QueryName *ids) const;
    void getBufferParameterIV(BufferTarget target, BufferPName pname,
                              GLint *params) const;
    void getBufferPointerV(BufferTarget target, BufferPointerName pname,
                           void **params) const;
    void getBufferSubData(BufferTarget target, GLintptr offset,
                          GLsizeiptr size, void *data) const;
    void getQueryObjectIV(QueryName id, QueryObjectParameterName pname,
                          GLint *params) const;
    void getQueryObjectUIV(QueryName id, QueryObjectParameterName pname,
                           GLuint *params) const;
    void getQueryIV(QueryTarget target, QueryParameterName pname, GLint *params) const;
    Boolean isBuffer(BufferName buffer) const;
    Boolean isQuery(QueryName id) const;
    void *mapBuffer(BufferTarget target, BufferAccess access) const;
    Boolean unmapBuffer(BufferTarget target) const;
#pragma endregion

#pragma region Core GL 2.0
    // GL 2.0
    void attachShader(ProgramName program, ShaderName shader) const;
    void bindAttribLocation(ProgramName program, GLuint index,
                            const GLchar *name) const;
    void blendEquationSeparate(BlendEquationModeEXT modeRGB,
                               BlendEquationModeEXT modeAlpha) const;
    void compileShader(ShaderName shader) const;
    ProgramName createProgram() const;
    ShaderName createShader(ShaderType type) const;
    void deleteProgram(ProgramName program) const;
    void deleteShader(ShaderName shader) const;
    void detachShader(ProgramName program, ShaderName shader) const;
    void disableVertexAttribArray(GLuint index) const;
    void drawBuffers(GLsizei n, const DrawBufferMode *bufs) const;
    void enableVertexAttribArray(GLuint index) const;
    void getActiveAttrib(ProgramName program, GLuint index, GLsizei bufSize,
                         GLsizei *length, GLint *size, AttributeType *type,
                         GLchar *name) const;
    void getActiveUniform(ProgramName program, GLuint index, GLsizei bufSize,
                          GLsizei *length, GLint *size, UniformType *type,
                          GLchar *name) const;
    void getAttachedShaders(ProgramName program, GLsizei maxCount,
                            GLsizei *count, ShaderName *shaders) const;
    GLint getAttribLocation(ProgramName program, const GLchar *name) const;
    void getProgramInfoLog(ProgramName program, GLsizei bufSize, GLsizei *length,
                           GLchar *infoLog) const;
    void getProgramIV(ProgramName program, ProgramProperty pname,
                      GLint *params) const;
    void getShaderInfoLog(ShaderName shader, GLsizei bufSize, GLsizei *length,
                          GLchar *infoLog) const;
    void getShaderSource(ShaderName shader, GLsizei bufSize, GLsizei *length,
                         GLchar *source) const;
    void getShaderIV(ShaderName shader, ShaderParameterName pname, GLint *params) const;
    GLint getUniformLocation(ProgramName program, const GLchar *name) const;
    void getUniformFV(ProgramName program, GLint location, GLfloat *params) const;
    void getUniformIV(ProgramName program, GLint location, GLint *params) const;
    void getVertexAttribPointerV(GLuint index,
                                 VertexAttribPointerPropertyARB pname,
                                 void **pointer) const;
    void getVertexAttribDV(GLuint index, VertexAttribPropertyARB pname,
                           GLdouble *params) const;
    void getVertexAttribFV(GLuint index, VertexAttribPropertyARB pname,
                           GLfloat *params) const;
    void getVertexAttribIV(GLuint index, VertexAttribPropertyARB pname,
                           GLint *params) const;
    Boolean isProgram(ProgramName program) const;
    Boolean isShader(ShaderName shader) const;
    void linkProgram(ProgramName program) const;
    void shaderSource(ShaderName shader, GLsizei count,
                      const GLchar *const*string, const GLint *length) const;
    void stencilFuncSeparate(StencilFaceDirection face, StencilFunction func,
                             GLint ref, GLuint mask) const;
    void stencilMaskSeparate(StencilFaceDirection face, GLuint mask) const;
    void stencilOpSeparate(StencilFaceDirection face, StencilOp sfail,
                           StencilOp dpfail, StencilOp dppass) const;
    void uniform1F(GLint location, GLfloat v0) const;
    void uniform1FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform1I(GLint location, GLint v0) const;
    void uniform1IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform2F(GLint location, GLfloat v0, GLfloat v1) const;
    void uniform2FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform2I(GLint location, GLint v0, GLint v1) const;
    void uniform2IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform3F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const;
    void uniform3FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform3I(GLint location, GLint v0, GLint v1, GLint v2) const;
    void uniform3IV(GLint location, GLsizei count, const GLint *value) const;
    void uniform4F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
                   GLfloat v3) const;
    void uniform4FV(GLint location, GLsizei count, const GLfloat *value) const;
    void uniform4I(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const;
    void uniform4IV(GLint location, GLsizei count, const GLint *value) const;
    void uniformMatrix2FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void uniformMatrix3FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void uniformMatrix4FV(GLint location, GLsizei count, Boolean transpose,
                          const GLfloat *value) const;
    void useProgram(ProgramName program) const;
    void validateProgram(ProgramName program) const;
    void vertexAttrib1D(GLuint index, GLdouble x) const;
    void vertexAttrib1DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib1F(GLuint index, GLfloat x) const;
    void vertexAttrib1FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib1S(GLuint index, GLshort x) const;
    void vertexAttrib1SV(GLuint index, const GLshort *v) const;
    void vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const;
    void vertexAttrib2DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const;
    void vertexAttrib2FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib2S(GLuint index, GLshort x, GLshort y) const;
    void vertexAttrib2SV(GLuint index, const GLshort *v) const;
    void vertexAttrib3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const;
    void vertexAttrib3DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib3F(GLuint index, GLfloat x, GLfloat y, GLfloat z) const;
    void vertexAttrib3FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib3S(GLuint index, GLshort x, GLshort y, GLshort z) const;
    void vertexAttrib3SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4NBV(GLuint index, const GLbyte *v) const;
    void vertexAttrib4NIV(GLuint index, const GLint *v) const;
    void vertexAttrib4NSV(GLuint index, const GLshort *v) const;
    void vertexAttrib4NUB(GLuint index, GLubyte x, GLubyte y, GLubyte z,
                          GLubyte w) const;
    void vertexAttrib4NUBV(GLuint index, const GLubyte *v) const;
    void vertexAttrib4NUIV(GLuint index, const GLuint *v) const;
    void vertexAttrib4NUSV(GLuint index, const GLushort *v) const;
    void vertexAttrib4BV(GLuint index, const GLbyte *v) const;
    void vertexAttrib4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                        GLdouble w) const;
    void vertexAttrib4DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib4F(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void vertexAttrib4FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib4IV(GLuint index, const GLint *v) const;
    void vertexAttrib4S(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const;
    void vertexAttrib4SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4UBV(GLuint index, const GLubyte *v) const;
    void vertexAttrib4UIV(GLuint index, const GLuint *v) const;
    void vertexAttrib4USV(GLuint index, const GLushort *v) const;
    void vertexAttribPointer(GLuint index, GLint size,
                             VertexAttribPointerType type, Boolean normalized,
                             GLsizei stride, const void *pointer) const;
#pragma endregion

#pragma region Core GL 2.1
    // GL 2.1
    void uniformMatrix2x3FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
    void uniformMatrix2x4FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
    void uniformMatrix3x2FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
    void uniformMatrix3x4FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
    void uniformMatrix4x2FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
    void uniformMatrix4x3FV(GLint location, GLsizei count, Boolean transpose,
                            const GLfloat *value) const;
#pragma endregion

#pragma region Core GL 3.0
    // GL 3.0
    void beginConditionalRender(GLuint id, ConditionalRenderMode mode) const;
    void beginTransformFeedback(PrimitiveType primitiveMode) const;
    void bindBufferBase(BufferTarget target, GLuint index, BufferName buffer) const;
    void bindBufferRange(BufferTarget target, GLuint index, BufferName buffer,
                         GLintptr offset, GLsizeiptr size) const;
    void bindFragDataLocation(ProgramName program, GLuint color,
                              const GLchar *name) const;
    void bindFramebuffer(FrameBufferTarget target, FrameBufferName framebuffer) const;
    void bindRenderbuffer(RenderBufferTarget target,
                          RenderBufferName renderbuffer) const;
    void bindVertexArray(VertexArrayName array) const;
    void blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
                         GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                         GLbitfield  /* ClearBufferMask */ mask,
                         BlitFramebufferFilter filter) const;
    FrameBufferStatus checkFramebufferStatus(FrameBufferTarget target) const;
    void clampColor(ClampColorTargetARB target, ClampColorModeARB clamp) const;
    void clearBufferFI(BufferEnum buffer, GLint drawbuffer, GLfloat depth,
                       GLint stencil) const;
    void clearBufferFV(BufferEnum buffer, GLint drawbuffer, const GLfloat *value) const;
    void clearBufferIV(BufferEnum buffer, GLint drawbuffer, const GLint *value) const;
    void clearBufferUIV(BufferEnum buffer, GLint drawbuffer, const GLuint *value) const;
    void colorMaskI(GLuint index, Boolean r, Boolean g, Boolean b, Boolean a) const;
    void deleteFramebuffers(GLsizei n, const FrameBufferName *framebuffers) const;
    void deleteRenderbuffers(GLsizei n, const RenderBufferName *renderbuffers) const;
    void deleteVertexArrays(GLsizei n, const VertexArrayName *arrays) const;
    void disableI(EnableCap target, GLuint index) const;
    void enableI(EnableCap target, GLuint index) const;
    void endConditionalRender() const;
    void endTransformFeedback() const;
    void flushMappedBufferRange(BufferTarget target, GLintptr offset,
                                GLsizeiptr length) const;
    void framebufferRenderbuffer(FrameBufferTarget target,
                                 FramebufferAttachment attachment,
                                 RenderBufferTarget renderbuffertarget,
                                 RenderBufferName renderbuffer) const;
    void framebufferTexture1D(FrameBufferTarget target,
                              FramebufferAttachment attachment,
                              TextureTarget textarget, TextureName texture,
                              GLint level) const;
    void framebufferTexture2D(FrameBufferTarget target,
                              FramebufferAttachment attachment,
                              TextureTarget textarget, TextureName texture,
                              GLint level) const;
    void framebufferTexture3D(FrameBufferTarget target,
                              FramebufferAttachment attachment,
                              TextureTarget textarget, TextureName texture,
                              GLint level, GLint zoffset) const;
    void framebufferTextureLayer(FrameBufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureName texture, GLint level, GLint layer) const;
    void genFramebuffers(GLsizei n, FrameBufferName *framebuffers) const;
    void genRenderbuffers(GLsizei n, RenderBufferName *renderbuffers) const;
    void genVertexArrays(GLsizei n, VertexArrayName *arrays) const;
    void generateMipmap(TextureTarget target) const;
    void getBooleanIV(BufferTarget target, GLuint index, Boolean *data) const;
    GLint getFragDataLocation(ProgramName program, const GLchar *name) const;
    void getFramebufferAttachmentParameterIV(FrameBufferTarget target,
                                             FramebufferAttachment attachment,
                                             FrameBufferAttachmentParameterName pname,
                                             GLint *params) const;
    void getIntegerIV(GetPName target, GLuint index, GLint *data) const;
    void getRenderbufferParameterIV(RenderBufferTarget target,
                                    RenderBufferParameterName pname,
                                    GLint *params) const;
    const GLubyte *getStringI(StringName name, GLuint index) const;
    void getTexParameterIIV(TextureTarget target, GetTextureParameter pname,
                            GLint *params) const;
    void getTexParameterIUIV(TextureTarget target, GetTextureParameter pname,
                             GLuint *params) const;
    void getTransformFeedbackVarying(ProgramName program, GLuint index,
                                     GLsizei bufSize, GLsizei *length,
                                     GLsizei *size, AttributeType *type,
                                     GLchar *name) const;
    void getUniformUIV(ProgramName program, GLint location, GLuint *params) const;
    void getVertexAttribIIV(GLuint index, VertexAttribEnum pname, GLint *params) const;
    void getVertexAttribIUIV(GLuint index, VertexAttribEnum pname,
                             GLuint *params) const;
    Boolean isEnabledI(EnableCap target, GLuint index) const;
    Boolean isFramebuffer(FrameBufferName framebuffer) const;
    Boolean isRenderbuffer(RenderBufferName renderbuffer) const;
    Boolean isVertexArray(VertexArrayName array) const;
    void *mapBufferRange(BufferTarget target, GLintptr offset,
                         GLsizeiptr length,
                         GLbitfield  /* MapBufferAccessMask */ access) const;
    void renderbufferStorage(RenderBufferTarget target,
                             InternalFormat internalformat, GLsizei width,
                             GLsizei height) const;
    void renderbufferStorageMultisample(RenderBufferTarget target,
                                        GLsizei samples,
                                        InternalFormat internalformat,
                                        GLsizei width, GLsizei height) const;
    void texParameterIIV(TextureTarget target, TextureParameterName pname,
                         const GLint *params) const;
    void texParameterIUIV(TextureTarget target, TextureParameterName pname,
                          const GLuint *params) const;
    void transformFeedbackVaryings(ProgramName program, GLsizei count,
                                   const GLchar *const*varyings,
                                   TransformFeedbackBufferMode bufferMode) const;
    void uniform1UI(GLint location, GLuint v0) const;
    void uniform1UIV(GLint location, GLsizei count, const GLuint *value) const;
    void uniform2UI(GLint location, GLuint v0, GLuint v1) const;
    void uniform2UIV(GLint location, GLsizei count, const GLuint *value) const;
    void uniform3UI(GLint location, GLuint v0, GLuint v1, GLuint v2) const;
    void uniform3UIV(GLint location, GLsizei count, const GLuint *value) const;
    void uniform4UI(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
    void uniform4UIV(GLint location, GLsizei count, const GLuint *value) const;
    void vertexAttribI1I(GLuint index, GLint x) const;
    void vertexAttribI1IV(GLuint index, const GLint *v) const;
    void vertexAttribI1UI(GLuint index, GLuint x) const;
    void vertexAttribI1UIV(GLuint index, const GLuint *v) const;
    void vertexAttribI2I(GLuint index, GLint x, GLint y) const;
    void vertexAttribI2IV(GLuint index, const GLint *v) const;
    void vertexAttribI2UI(GLuint index, GLuint x, GLuint y) const;
    void vertexAttribI2UIV(GLuint index, const GLuint *v) const;
    void vertexAttribI3I(GLuint index, GLint x, GLint y, GLint z) const;
    void vertexAttribI3IV(GLuint index, const GLint *v) const;
    void vertexAttribI3UI(GLuint index, GLuint x, GLuint y, GLuint z) const;
    void vertexAttribI3UIV(GLuint index, const GLuint *v) const;
    void vertexAttribI4BV(GLuint index, const GLbyte *v) const;
    void vertexAttribI4I(GLuint index, GLint x, GLint y, GLint z, GLint w) const;
    void vertexAttribI4IV(GLuint index, const GLint *v) const;
    void vertexAttribI4SV(GLuint index, const GLshort *v) const;
    void vertexAttribI4UBV(GLuint index, const GLubyte *v) const;
    void vertexAttribI4UI(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) const;
    void vertexAttribI4UIV(GLuint index, const GLuint *v) const;
    void vertexAttribI4USV(GLuint index, const GLushort *v) const;
    void vertexAttribIPointer(GLuint index, GLint size, VertexAttribIType type,
                              GLsizei stride, const void *pointer) const;
#pragma endregion

#pragma region Core GL 3.1
    // GL 3.1
    void copyBufferSubData(CopyBufferSubDataTarget readTarget,
                           CopyBufferSubDataTarget writeTarget,
                           GLintptr readOffset, GLintptr writeOffset,
                           GLsizeiptr size) const;
    void drawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count,
                             GLsizei instancecount) const;
    void drawElementsInstanced(PrimitiveType mode, GLsizei count,
                               DrawElementsType type, const void *indices,
                               GLsizei instancecount) const;
    void getActiveUniformBlockName(ProgramName program, GLuint uniformBlockIndex,
                                   GLsizei bufSize, GLsizei *length,
                                   GLchar *uniformBlockName) const;
    void getActiveUniformBlockIV(ProgramName program, GLuint uniformBlockIndex,
                                 UniformBlockPName pname, GLint *params) const;
    void getActiveUniformName(ProgramName program, GLuint uniformIndex,
                              GLsizei bufSize, GLsizei *length,
                              GLchar *uniformName) const;
    void getActiveUniformsIV(ProgramName program, GLsizei uniformCount,
                             const GLuint *uniformIndices, UniformPName pname,
                             GLint *params) const;
    GLuint getUniformBlockIndex(ProgramName program,
                                const GLchar *uniformBlockName) const;
    void getUniformIndices(ProgramName program, GLsizei uniformCount,
                           const GLchar *const*uniformNames,
                           GLuint *uniformIndices) const;
    void primitiveRestartIndex(GLuint index) const;
    void texBuffer(TextureTarget target, SizedInternalFormat internalformat,
                   BufferName buffer) const;
    void uniformBlockBinding(ProgramName program, GLuint uniformBlockIndex,
                             GLuint uniformBlockBinding) const;
#pragma endregion

#pragma region Core GL 3.2
    // GL 3.2
    SyncStatus clientWaitSync(SyncName sync,
                              GLbitfield  /* SyncObjectMask */ flags,
                              GLuint64 timeout) const;
    void deleteSync(SyncName sync) const;
    void drawElementsBaseVertex(PrimitiveType mode, GLsizei count,
                                DrawElementsType type, const void *indices,
                                GLint basevertex) const;
    void drawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count,
                                         DrawElementsType type,
                                         const void *indices,
                                         GLsizei instancecount, GLint basevertex) const;
    void drawRangeElementsBaseVertex(PrimitiveType mode, GLuint start,
                                     GLuint end, GLsizei count,
                                     DrawElementsType type, const void *indices,
                                     GLint basevertex) const;
    SyncName fenceSync(SyncCondition condition, SyncBehaviorFlags flags) const;
    void framebufferTexture(FrameBufferTarget target,
                            FramebufferAttachment attachment,
                            TextureName texture, GLint level) const;
    void getBufferParameterI64V(BufferTarget target, BufferPName pname,
                                GLint64 *params) const;
    void getInteger64IV(GetPName target, GLuint index, GLint64 *data) const;
    void getInteger64V(GetPName pname, GLint64 *data) const;
    void getMultisampleFV(GetMultisamplePNameNV pname, GLuint index,
                          GLfloat *val) const;
    void getSyncIV(SyncName sync, SyncParameterName pname, GLsizei count,
                   GLsizei *length, GLint *values) const;
    Boolean isSync(SyncName sync) const;
    void multiDrawElementsBaseVertex(PrimitiveType mode, const GLsizei *count,
                                     DrawElementsType type,
                                     const void *const*indices,
                                     GLsizei drawcount, const GLint *basevertex) const;
    void provokingVertex(VertexProvokingMode mode) const;
    void sampleMaskI(GLuint maskNumber, GLbitfield mask) const;
    void texImage2DMultisample(TextureTarget target, GLsizei samples,
                               InternalFormat internalformat, GLsizei width,
                               GLsizei height, Boolean fixedsamplelocations) const;
    void texImage3DMultisample(TextureTarget target, GLsizei samples,
                               InternalFormat internalformat, GLsizei width,
                               GLsizei height, GLsizei depth,
                               Boolean fixedsamplelocations) const;
    void waitSync(SyncName sync, SyncBehaviorFlags flags, GLuint64 timeout) const;
#pragma endregion

#pragma region Core GL 3.3
    // GL 3.3
    void bindFragDataLocationIndexed(ProgramName program, GLuint colorNumber,
                                     GLuint index, const GLchar *name) const;
    void bindSampler(GLuint unit, SamplerName sampler) const;
    void deleteSamplers(GLsizei count, const SamplerName *samplers) const;
    void genSamplers(GLsizei count, SamplerName *samplers) const;
    GLint getFragDataIndex(ProgramName program, const GLchar *name) const;
    void getQueryObjectI64V(QueryName id, QueryObjectParameterName pname,
                            GLint64 *params) const;
    void getQueryObjectUI64(QueryName id, QueryObjectParameterName pname,
                            GLuint64 *params) const;
    void getSamplerParameterIIV(SamplerName sampler, SamplerParameterI pname,
                                GLint *params) const;
    void getSamplerParameterIUIV(SamplerName sampler, SamplerParameterI pname,
                                 GLuint *params) const;
    void getSamplerParameterFV(SamplerName sampler, SamplerParameterF pname,
                               GLfloat *params) const;
    void getSamplerParameterIV(SamplerName sampler, SamplerParameterI pname,
                               GLint *params) const;
    Boolean isSampler(SamplerName sampler) const;
    void queryCounter(QueryName id, QueryCounterTarget target) const;
    void samplerParameterIIV(SamplerName sampler, SamplerParameterI pname,
                             const GLint *param) const;
    void samplerParameterIUIV(SamplerName sampler, SamplerParameterI pname,
                              const GLuint *param) const;
    void samplerParameterF(SamplerName sampler, SamplerParameterF pname,
                           GLfloat param) const;
    void samplerParameterFV(SamplerName sampler, SamplerParameterF pname,
                            const GLfloat *param) const;
    void samplerParameterI(SamplerName sampler, SamplerParameterI pname,
                           GLint param) const;
    void samplerParameterIV(SamplerName sampler, SamplerParameterI pname,
                            const GLint *param) const;
    void vertexAttribDivisor(GLuint index, GLuint divisor) const;
    void vertexAttribP1UI(GLuint index, VertexAttribPointerType type,
                          Boolean normalized, GLuint value) const;
    void vertexAttribP1UIV(GLuint index, VertexAttribPointerType type,
                           Boolean normalized, const GLuint *value) const;
    void vertexAttribP2UI(GLuint index, VertexAttribPointerType type,
                          Boolean normalized, GLuint value) const;
    void vertexAttribP2UIV(GLuint index, VertexAttribPointerType type,
                           Boolean normalized, const GLuint *value) const;
    void vertexAttribP3UI(GLuint index, VertexAttribPointerType type,
                          Boolean normalized, GLuint value) const;
    void vertexAttribP3UIV(GLuint index, VertexAttribPointerType type,
                           Boolean normalized, const GLuint *value) const;
    void vertexAttribP4UI(GLuint index, VertexAttribPointerType type,
                          Boolean normalized, GLuint value) const;
    void vertexAttribP4UIV(GLuint index, VertexAttribPointerType type,
                           Boolean normalized, const GLuint *value) const;
#pragma endregion

#pragma region Core GL 4.0
    // GL 4.0
    void beginQueryIndexed(QueryTarget target, GLuint index, QueryName id) const;
    void bindTransformFeedback(BindTransformFeedbackTarget target,
                               TransformFeedbackName id) const;
    void blendEquationSeparateI(GLuint buf, BlendEquationModeEXT modeRGB,
                                BlendEquationModeEXT modeAlpha) const;
    void blendEquationI(GLuint buf, BlendEquationModeEXT mode) const;
    void blendFuncSeparateI(GLuint buf, BlendingFactor srcRGB,
                            BlendingFactor dstRGB, BlendingFactor srcAlpha,
                            BlendingFactor dstAlpha) const;
    void blendFuncI(GLuint buf, BlendingFactor src, BlendingFactor dst) const;
    void deleteTransformFeedbacks(GLsizei n, const TransformFeedbackName *ids) const;
    void drawArraysIndirect(PrimitiveType mode, const void *indirect) const;
    void drawElementsIndirect(PrimitiveType mode, DrawElementsType type,
                              const void *indirect) const;
    void drawTransformFeedback(PrimitiveType mode, TransformFeedbackName id) const;
    void drawTransformFeedbackStream(PrimitiveType mode,
                                     TransformFeedbackName id, GLuint stream) const;
    void endQueryIndexed(QueryTarget target, GLuint index) const;
    void genTransformFeedbacks(GLsizei n, TransformFeedbackName *ids) const;
    void getActiveSubroutineName(ProgramName program, ShaderType shadertype,
                                 GLuint index, GLsizei bufSize, GLsizei *length,
                                 GLchar *name) const;
    void getActiveSubroutineUniformName(ProgramName program,
                                        ShaderType shadertype, GLuint index,
                                        GLsizei bufSize, GLsizei *length,
                                        GLchar *name) const;
    void getActiveSubroutineUniformIV(ProgramName program, ShaderType shadertype,
                                      GLuint index,
                                      SubroutineParameterName pname,
                                      GLint *values) const;
    void getProgramStageIV(ProgramName program, ShaderType shadertype,
                           ProgramStagePName pname, GLint *values) const;
    void getQueryIndexedIV(QueryTarget target, GLuint index,
                           QueryParameterName pname, GLint *params) const;
    GLuint getSubroutineIndex(ProgramName program, ShaderType shadertype,
                              const GLchar *name) const;
    GLint getSubroutineUniformLocation(ProgramName program,
                                       ShaderType shadertype, const GLchar *name) const;
    void getUniformSubroutineUIV(ShaderType shadertype, GLint location,
                                 GLuint *params) const;
    void getUniformDV(ProgramName program, GLint location, GLdouble *params) const;
    Boolean isTransformFeedback(TransformFeedbackName id) const;
    void minSampleShading(GLfloat value) const;
    void patchParameterFV(PatchParameterName pname, const GLfloat *values) const;
    void patchParameterI(PatchParameterName pname, GLint value) const;
    void pauseTransformFeedback() const;
    void resumeTransformFeedback() const;
    void uniform1D(GLint location, GLdouble x) const;
    void uniform1DV(GLint location, GLsizei count, const GLdouble *value) const;
    void uniform2D(GLint location, GLdouble x, GLdouble y) const;
    void uniform2DV(GLint location, GLsizei count, const GLdouble *value) const;
    void uniform3D(GLint location, GLdouble x, GLdouble y, GLdouble z) const;
    void uniform3DV(GLint location, GLsizei count, const GLdouble *value) const;
    void uniform4D(GLint location, GLdouble x, GLdouble y, GLdouble z,
                   GLdouble w) const;
    void uniform4DV(GLint location, GLsizei count, const GLdouble *value) const;
    void uniformMatrix2DV(GLint location, GLsizei count, Boolean transpose,
                          const GLdouble *value) const;
    void uniformMatrix2x3DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformMatrix2x4DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformMatrix3DV(GLint location, GLsizei count, Boolean transpose,
                          const GLdouble *value) const;
    void uniformMatrix3x2DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformMatrix3x4DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformMatrix4DV(GLint location, GLsizei count, Boolean transpose,
                          const GLdouble *value) const;
    void uniformMatrix4x2DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformMatrix4x3DV(GLint location, GLsizei count, Boolean transpose,
                            const GLdouble *value) const;
    void uniformSubroutinesUIV(ShaderType shadertype, GLsizei count,
                               const GLuint *indices) const;
#pragma endregion

#pragma region Core GL 4.1
    // GL 4.1
    void activeShaderProgram(ProgramPipelineName pipeline, ProgramName program) const;
    void bindProgramPipeline(ProgramPipelineName pipeline) const;
    void clearDepthF(GLfloat d) const;
    ProgramName createShaderProgramV(ShaderType type, GLsizei count,
                                     const GLchar *const*strings) const;
    void deleteProgramPipelines(GLsizei n, const ProgramPipelineName *pipelines) const;
    void depthRangeArrayV(GLuint first, GLsizei count, const GLdouble *v) const;
    void depthRangeIndexed(GLuint index, GLdouble n, GLdouble f) const;
    void depthRangeF(GLfloat n, GLfloat f) const;
    void genProgramPipelines(GLsizei n, ProgramPipelineName *pipelines) const;
    void getDoubleIV(GetPName target, GLuint index, GLdouble *data) const;
    void getFloatIV(GetPName target, GLuint index, GLfloat *data) const;
    void getProgramBinary(ProgramName program, GLsizei bufSize, GLsizei *length,
                          GLenum *binaryFormat, void *binary) const;
    void getProgramPipelineInfoLog(ProgramPipelineName pipeline, GLsizei bufSize,
                                   GLsizei *length, GLchar *infoLog) const;
    void getProgramPipelineIV(ProgramPipelineName pipeline,
                              PipelineParameterName pname, GLint *params) const;
    void getShaderPrecisionFormat(ShaderType shadertype,
                                  PrecisionType precisiontype, GLint *range,
                                  GLint *precision) const;
    void getVertexAttribLDV(GLuint index, VertexAttribEnum pname,
                            GLdouble *params) const;
    Boolean isProgramPipeline(ProgramPipelineName pipeline) const;
    void programBinary(ProgramName program, GLenum binaryFormat,
                       const void *binary, GLsizei length) const;
    void programParameterI(ProgramName program, ProgramParameterPName pname,
                           GLint value) const;
    void programUniform1D(ProgramName program, GLint location, GLdouble v0) const;
    void programUniform1DV(ProgramName program, GLint location, GLsizei count,
                           const GLdouble *value) const;
    void programUniform1F(ProgramName program, GLint location, GLfloat v0) const;
    void programUniform1FV(ProgramName program, GLint location, GLsizei count,
                           const GLfloat *value) const;
    void programUniform1I(ProgramName program, GLint location, GLint v0) const;
    void programUniform1IV(ProgramName program, GLint location, GLsizei count,
                           const GLint *value) const;
    void programUniform1UI(ProgramName program, GLint location, GLuint v0) const;
    void programUniform1UIV(ProgramName program, GLint location, GLsizei count,
                            const GLuint *value) const;
    void programUniform2D(ProgramName program, GLint location, GLdouble v0,
                          GLdouble v1) const;
    void programUniform2DV(ProgramName program, GLint location, GLsizei count,
                           const GLdouble *value) const;
    void programUniform2F(ProgramName program, GLint location, GLfloat v0,
                          GLfloat v1) const;
    void programUniform2FV(ProgramName program, GLint location, GLsizei count,
                           const GLfloat *value) const;
    void programUniform2I(ProgramName program, GLint location, GLint v0,
                          GLint v1) const;
    void programUniform2IV(ProgramName program, GLint location, GLsizei count,
                           const GLint *value) const;
    void programUniform2UI(ProgramName program, GLint location, GLuint v0,
                           GLuint v1) const;
    void programUniform2UIV(ProgramName program, GLint location, GLsizei count,
                            const GLuint *value) const;
    void programUniform3D(ProgramName program, GLint location, GLdouble v0,
                          GLdouble v1, GLdouble v2) const;
    void programUniform3DV(ProgramName program, GLint location, GLsizei count,
                           const GLdouble *value) const;
    void programUniform3F(ProgramName program, GLint location, GLfloat v0,
                          GLfloat v1, GLfloat v2) const;
    void programUniform3FV(ProgramName program, GLint location, GLsizei count,
                           const GLfloat *value) const;
    void programUniform3I(ProgramName program, GLint location, GLint v0,
                          GLint v1, GLint v2) const;
    void programUniform3IV(ProgramName program, GLint location, GLsizei count,
                           const GLint *value) const;
    void programUniform3UI(ProgramName program, GLint location, GLuint v0,
                           GLuint v1, GLuint v2) const;
    void programUniform3UIV(ProgramName program, GLint location, GLsizei count,
                            const GLuint *value) const;
    void programUniform4D(ProgramName program, GLint location, GLdouble v0,
                          GLdouble v1, GLdouble v2, GLdouble v3) const;
    void programUniform4DV(ProgramName program, GLint location, GLsizei count,
                           const GLdouble *value) const;
    void programUniform4F(ProgramName program, GLint location, GLfloat v0,
                          GLfloat v1, GLfloat v2, GLfloat v3) const;
    void programUniform4FV(ProgramName program, GLint location, GLsizei count,
                           const GLfloat *value) const;
    void programUniform4I(ProgramName program, GLint location, GLint v0,
                          GLint v1, GLint v2, GLint v3) const;
    void programUniform4IV(ProgramName program, GLint location, GLsizei count,
                           const GLint *value) const;
    void programUniform4UI(ProgramName program, GLint location, GLuint v0,
                           GLuint v1, GLuint v2, GLuint v3) const;
    void programUniform4UIV(ProgramName program, GLint location, GLsizei count,
                            const GLuint *value) const;
    void programUniformMatrix2DV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLdouble *value) const;
    void programUniformMatrix2FV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLfloat *value) const;
    void programUniformMatrix2x3DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix2x3FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void programUniformMatrix2x4DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix2x4FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void programUniformMatrix3DV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLdouble *value) const;
    void programUniformMatrix3FV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLfloat *value) const;
    void programUniformMatrix3x2DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix3x2FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void programUniformMatrix3x4DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix3x4FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void programUniformMatrix4DV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLdouble *value) const;
    void programUniformMatrix4FV(ProgramName program, GLint location,
                                 GLsizei count, Boolean transpose,
                                 const GLfloat *value) const;
    void programUniformMatrix4x2DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix4x2FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void programUniformMatrix4x3DV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLdouble *value) const;
    void programUniformMatrix4x3FV(ProgramName program, GLint location,
                                   GLsizei count, Boolean transpose,
                                   const GLfloat *value) const;
    void releaseShaderCompiler() const;
    void scissorArrayV(GLuint first, GLsizei count, const GLint *v) const;
    void scissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width,
                        GLsizei height) const;
    void scissorIndexedv(GLuint index, const GLint *v) const;
    void shaderBinary(GLsizei count, const ShaderName *shaders,
                      ShaderBinaryFormat binaryFormat, const void *binary,
                      GLsizei length) const;
    void useProgramStages(ProgramPipelineName pipeline,
                          GLbitfield  /* UseProgramStageMask */ stages,
                          ProgramName program) const;
    void validateProgramPipeline(ProgramPipelineName pipeline) const;
    void vertexAttribL1D(GLuint index, GLdouble x) const;
    void vertexAttribL1DV(GLuint index, const GLdouble *v) const;
    void vertexAttribL2D(GLuint index, GLdouble x, GLdouble y) const;
    void vertexAttribL2DV(GLuint index, const GLdouble *v) const;
    void vertexAttribL3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const;
    void vertexAttribL3DV(GLuint index, const GLdouble *v) const;
    void vertexAttribL4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                         GLdouble w) const;
    void vertexAttribL4DV(GLuint index, const GLdouble *v) const;
    void vertexAttribLPointer(GLuint index, GLint size, VertexAttribLType type,
                              GLsizei stride, const void *pointer) const;
    void viewportArrayV(GLuint first, GLsizei count, const GLfloat *v) const;
    void viewportIndexedF(GLuint index, GLfloat x, GLfloat y, GLfloat w,
                          GLfloat h) const;
    void viewportIndexedFV(GLuint index, const GLfloat *v) const;
#pragma endregion

#pragma region Core GL 4.2
    // GL 4.2
    void bindImageTexture(GLuint unit, TextureName texture, GLint level,
                          Boolean layered, GLint layer, BufferAccess access,
                          InternalFormat format) const;
    void drawArraysInstancedBaseInstance(PrimitiveType mode, GLint first,
                                         GLsizei count, GLsizei instancecount,
                                         GLuint baseinstance) const;
    void drawElementsInstancedBaseInstance(PrimitiveType mode, GLsizei count,
                                           PrimitiveType type,
                                           const void *indices,
                                           GLsizei instancecount,
                                           GLuint baseinstance) const;
    void drawElementsInstancedBaseVertexBaseInstance(PrimitiveType mode,
                                                     GLsizei count,
                                                     DrawElementsType type,
                                                     const void *indices,
                                                     GLsizei instancecount,
                                                     GLint basevertex,
                                                     GLuint baseinstance) const;
    void drawTransformFeedbackInstanced(PrimitiveType mode,
                                        TransformFeedbackName id,
                                        GLsizei instancecount) const;
    void drawTransformFeedbackStreamInstanced(PrimitiveType mode,
                                              TransformFeedbackName id,
                                              GLuint stream,
                                              GLsizei instancecount) const;
    void getActiveAtomicCounterBufferIV(ProgramName program, GLuint bufferIndex,
                                        AtomicCounterBufferPName pname,
                                        GLint *params) const;
    void getInternalformatIV(TextureTarget target, InternalFormat internalformat,
                             InternalFormatPName pname, GLsizei count,
                             GLint *params) const;
    void memoryBarrier(GLbitfield  /* MemoryBarrierMask */ barriers) const;
    void texStorage1D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width) const;
    void texStorage2D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width,
                      GLsizei height) const;
    void texStorage3D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width,
                      GLsizei height, GLsizei depth) const;
#pragma endregion

#pragma region Core GL 4.3
    // GL 4.3
    void bindVertexBuffer(GLuint bindingindex, BufferName buffer,
                          GLintptr offset, GLsizei stride) const;
    void clearBufferData(BufferStorageTarget target,
                         SizedInternalFormat internalformat, PixelFormat format,
                         PixelType type, const void *data) const;
    void clearBufferSubData(BufferTarget target,
                            SizedInternalFormat internalformat, GLintptr offset,
                            GLsizeiptr size, PixelFormat format, PixelType type,
                            const void *data) const;
    void copyImageSubData(GLuint srcName, CopyImageSubDataTarget srcTarget,
                          GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ,
                          GLuint dstName, CopyImageSubDataTarget dstTarget,
                          GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
                          GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) const;
    void debugMessageCallback(GLDEBUGPROC callback, const void *userParam) const;
    void debugMessageControl(DebugSource source, DebugType type,
                             DebugSeverity severity, GLsizei count,
                             const GLuint *ids, Boolean enabled) const;
    void debugMessageInsert(DebugSource source, DebugType type, GLuint id,
                            DebugSeverity severity, GLsizei length,
                            const GLchar *buf) const;
    void dispatchCompute(GLuint num_groups_x, GLuint num_groups_y,
                         GLuint num_groups_z) const;
    void dispatchComputeIndirect(GLintptr indirect) const;
    void framebufferParameterI(FrameBufferTarget target,
                               FrameBufferParameterName pname, GLint param) const;
    GLuint getDebugMessageLog(GLuint count, GLsizei bufSize,
                              DebugSource *sources, DebugType *types,
                              GLuint *ids, DebugSeverity *severities,
                              GLsizei *lengths, GLchar *messageLog) const;
    void getFramebufferParameterIV(FrameBufferTarget target,
                                   FrameBufferAttachmentParameterName pname,
                                   GLint *params) const;
    void getInternalformatI64V(TextureTarget target,
                               InternalFormat internalformat,
                               InternalFormatPName pname, GLsizei count,
                               GLint64 *params) const;
    void getObjectLabel(ObjectIdentifier identifier, GLuint name,
                        GLsizei bufSize, GLsizei *length, GLchar *label) const;
    void getObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length,
                           GLchar *label) const;
    void getPointerV(GetPointervPName pname, void **params) const;
    void getProgramInterfaceIV(ProgramName program,
                               ProgramInterface programInterface,
                               ProgramInterfacePName pname, GLint *params) const;
    GLuint getProgramResourceIndex(ProgramName program,
                                   ProgramInterface programInterface,
                                   const GLchar *name) const;
    GLint getProgramResourceLocation(ProgramName program,
                                     ProgramInterface programInterface,
                                     const GLchar *name) const;
    GLint getProgramResourceLocationIndex(ProgramName program,
                                          ProgramInterface programInterface,
                                          const GLchar *name) const;
    void getProgramResourceName(ProgramName program,
                                ProgramInterface programInterface, GLuint index,
                                GLsizei bufSize, GLsizei *length, GLchar *name) const;
    void getProgramResourceIV(ProgramName program,
                              ProgramInterface programInterface, GLuint index,
                              GLsizei propCount,
                              const ProgramResourceProperty *props,
                              GLsizei count, GLsizei *length, GLint *params) const;
    void invalidateBufferData(BufferName buffer) const;
    void invalidateBufferSubData(BufferName buffer, GLintptr offset,
                                 GLsizeiptr length) const;
    void invalidateFramebuffer(FrameBufferTarget target, GLsizei numAttachments,
                               const InvalidateFramebufferAttachment *attachments) const;
    void invalidateSubFramebuffer(FrameBufferTarget target,
                                  GLsizei numAttachments,
                                  const InvalidateFramebufferAttachment *attachments,
                                  GLint x, GLint y, GLsizei width,
                                  GLsizei height) const;
    void invalidateTexImage(TextureName texture, GLint level) const;
    void invalidateTexSubImage(TextureName texture, GLint level, GLint xoffset,
                               GLint yoffset, GLint zoffset, GLsizei width,
                               GLsizei height, GLsizei depth) const;
    void multiDrawArraysIndirect(PrimitiveType mode, const void *indirect,
                                 GLsizei drawcount, GLsizei stride) const;
    void multiDrawElementsIndirect(PrimitiveType mode, DrawElementsType type,
                                   const void *indirect, GLsizei drawcount,
                                   GLsizei stride) const;
    void objectLabel(ObjectIdentifier identifier, GLuint name, GLsizei length,
                     const GLchar *label) const;
    void objectPtrLabel(const void *ptr, GLsizei length, const GLchar *label) const;
    void popDebugGroup() const;
    void pushDebugGroup(DebugSource source, GLuint id, GLsizei length,
                        const GLchar *message) const;
    void shaderStorageBlockBinding(ProgramName program, GLuint storageBlockIndex,
                                   GLuint storageBlockBinding) const;
    void texBufferRange(TextureTarget target, SizedInternalFormat internalformat,
                        BufferName buffer, GLintptr offset, GLsizeiptr size) const;
    void texStorage2DMultisample(TextureTarget target, GLsizei samples,
                                 SizedInternalFormat internalformat,
                                 GLsizei width, GLsizei height,
                                 Boolean fixedsamplelocations) const;
    void texStorage3DMultisample(TextureTarget target, GLsizei samples,
                                 SizedInternalFormat internalformat,
                                 GLsizei width, GLsizei height, GLsizei depth,
                                 Boolean fixedsamplelocations) const;
    void textureView(TextureName texture, TextureTarget target,
                     TextureName origtexture, SizedInternalFormat internalformat,
                     GLuint minlevel, GLuint numlevels, GLuint minlayer,
                     GLuint numlayers) const;
    void vertexAttribBinding(GLuint attribindex, GLuint bindingindex) const;
    void vertexAttribFormat(GLuint attribindex, GLint size,
                            VertexAttribType type, Boolean normalized,
                            GLuint relativeoffset) const;
    void vertexAttribIFormat(GLuint attribindex, GLint size,
                             VertexAttribIType type, GLuint relativeoffset) const;
    void vertexAttribLFormat(GLuint attribindex, GLint size,
                             VertexAttribLType type, GLuint relativeoffset) const;
    void vertexBindingDivisor(GLuint bindingindex, GLuint divisor) const;
#pragma endregion

#pragma region Core GL 4.4
    // GL 4.4
    void bindBuffersBase(BufferTarget target, GLuint first, GLsizei count,
                         const BufferName *buffers) const;
    void bindBuffersRange(BufferTarget target, GLuint first, GLsizei count,
                          const BufferName *buffers, const GLintptr *offsets,
                          const GLsizeiptr *sizes) const;
    void bindImageTextures(GLuint first, GLsizei count,
                           const TextureName *textures) const;
    void bindSamplers(GLuint first, GLsizei count, const SamplerName *samplers) const;
    void bindTextures(GLuint first, GLsizei count, const TextureName *textures) const;
    void bindVertexBuffers(GLuint first, GLsizei count,
                           const BufferName *buffers, const GLintptr *offsets,
                           const GLsizei *strides) const;
    void bufferStorage(BufferStorageTarget target, GLsizeiptr size,
                       const void *data,
                       GLbitfield  /* BufferStorageMask */ flags) const;
    void clearTexImage(TextureName texture, GLint level, PixelFormat format,
                       PixelType type, const void *data) const;
    void clearTexSubImage(TextureName texture, GLint level, GLint xoffset,
                          GLint yoffset, GLint zoffset, GLsizei width,
                          GLsizei height, GLsizei depth, PixelFormat format,
                          PixelType type, const void *data) const;

    // GL 4.5
    void bindTextureUnit(GLuint unit, TextureName texture) const;
    void blitNamedFramebuffer(FrameBufferName readFramebuffer,
                              FrameBufferName drawFramebuffer, GLint srcX0,
                              GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0,
                              GLint dstY0, GLint dstX1, GLint dstY1,
                              GLbitfield  /* ClearBufferMask */ mask,
                              BlitFramebufferFilter filter) const;
    FrameBufferStatus checkNamedFramebufferStatus(FrameBufferName framebuffer,
                                                  FrameBufferTarget target) const;
    void clearNamedBufferData(BufferName buffer,
                              SizedInternalFormat internalformat,
                              PixelFormat format, PixelType type,
                              const void *data) const;
    void clearNamedBufferSubData(BufferName buffer,
                                 SizedInternalFormat internalformat,
                                 GLintptr offset, GLsizeiptr size,
                                 PixelFormat format, PixelType type,
                                 const void *data) const;
    void clearNamedFramebufferFI(FrameBufferName framebuffer, BufferEnum buffer,
                                 GLint drawbuffer, GLfloat depth, GLint stencil) const;
    void clearNamedFramebufferFV(FrameBufferName framebuffer, BufferEnum buffer,
                                 GLint drawbuffer, const GLfloat *value) const;
    void clearNamedFramebufferIV(FrameBufferName framebuffer, BufferEnum buffer,
                                 GLint drawbuffer, const GLint *value) const;
    void clearNamedFramebufferUIV(FrameBufferName framebuffer, BufferEnum buffer,
                                  GLint drawbuffer, const GLuint *value) const;
    void clipControl(ClipControlOrigin origin, ClipControlDepth depth) const;
    void compressedTextureSubImage1D(TextureName texture, GLint level,
                                     GLint xoffset, GLsizei width,
                                     InternalFormat format, GLsizei imageSize,
                                     const void *data) const;
    void compressedTextureSubImage2D(TextureName texture, GLint level,
                                     GLint xoffset, GLint yoffset, GLsizei width,
                                     GLsizei height, InternalFormat format,
                                     GLsizei imageSize, const void *data) const;
    void compressedTextureSubImage3D(TextureName texture, GLint level,
                                     GLint xoffset, GLint yoffset, GLint zoffset,
                                     GLsizei width, GLsizei height,
                                     GLsizei depth, InternalFormat format,
                                     GLsizei imageSize, const void *data) const;
    void copyNamedBufferSubData(BufferName readBuffer, BufferName writeBuffer,
                                GLintptr readOffset, GLintptr writeOffset,
                                GLsizeiptr size) const;
    void copyTextureSubImage1D(TextureName texture, GLint level, GLint xoffset,
                               GLint x, GLint y, GLsizei width) const;
    void copyTextureSubImage2D(TextureName texture, GLint level, GLint xoffset,
                               GLint yoffset, GLint x, GLint y, GLsizei width,
                               GLsizei height) const;
    void copyTextureSubImage3D(TextureName texture, GLint level, GLint xoffset,
                               GLint yoffset, GLint zoffset, GLint x, GLint y,
                               GLsizei width, GLsizei height) const;
    void createBuffers(GLsizei n, BufferName *buffers) const;
    void createFramebuffers(GLsizei n, FrameBufferName *framebuffers) const;
    void createProgramPipelines(GLsizei n, ProgramPipelineName *pipelines) const;
    void createQueries(QueryTarget target, GLsizei n, QueryName *ids) const;
    void createRenderbuffers(GLsizei n, RenderBufferName *renderbuffers) const;
    void createSamplers(GLsizei n, SamplerName *samplers) const;
    void createTextures(TextureTarget target, GLsizei n, TextureName *textures) const;
    void createTransformFeedbacks(GLsizei n, TransformFeedbackName *ids) const;
    void createVertexArrays(GLsizei n, VertexArrayName *arrays) const;
    void disableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const;
    void enableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const;
    void flushMappedNamedBufferRange(BufferName buffer, GLintptr offset,
                                     GLsizeiptr length) const;
    void generateTextureMipmap(TextureName texture) const;
    void getCompressedTextureImage(TextureName texture, GLint level,
                                   GLsizei bufSize, void *pixels) const;
    void getCompressedTextureSubImage(TextureName texture, GLint level,
                                      GLint xoffset, GLint yoffset,
                                      GLint zoffset, GLsizei width,
                                      GLsizei height, GLsizei depth,
                                      GLsizei bufSize, void *pixels) const;
    GraphicsResetStatus getGraphicsResetStatus() const;
    void getNamedBufferParameterI64V(BufferName buffer, BufferPName pname,
                                     GLint64 *params) const;
    void getNamedBufferParameterIV(BufferName buffer, BufferPName pname,
                                   GLint *params) const;
    void getNamedBufferPointerV(BufferName buffer, BufferPointerName pname,
                                void **params) const;
    void getNamedBufferSubData(BufferName buffer, GLintptr offset,
                               GLsizeiptr size, void *data) const;
    void getNamedFramebufferAttachmentParameterIV(FrameBufferName framebuffer,
                                                  FramebufferAttachment attachment,
                                                  FrameBufferAttachmentParameterName pname,
                                                  GLint *params) const;
    void getNamedFramebufferParameterIV(FrameBufferName framebuffer,
                                        GetFramebufferParameter pname,
                                        GLint *param) const;
    void getNamedRenderbufferParameterIV(RenderBufferName renderbuffer,
                                         RenderBufferParameterName pname,
                                         GLint *params) const;
    void getQueryBufferObjectI64V(QueryName id, BufferName buffer,
                                  QueryObjectParameterName pname,
                                  GLintptr offset) const;
    void getQueryBufferObjectIV(QueryName id, BufferName buffer,
                                QueryObjectParameterName pname, GLintptr offset) const;
    void getQueryBufferObjectUI64(QueryName id, BufferName buffer,
                                  QueryObjectParameterName pname,
                                  GLintptr offset) const;
    void getQueryBufferObjectUIV(QueryName id, BufferName buffer,
                                 QueryObjectParameterName pname, GLintptr offset) const;
    void getTextureImage(TextureName texture, GLint level, PixelFormat format,
                         PixelType type, GLsizei bufSize, void *pixels) const;
    void getTextureLevelParameterFV(TextureName texture, GLint level,
                                    GetTextureParameter pname, GLfloat *params) const;
    void getTextureLevelParameterIV(TextureName texture, GLint level,
                                    GetTextureParameter pname, GLint *params) const;
    void getTextureParameterIIV(TextureName texture, GetTextureParameter pname,
                                GLint *params) const;
    void getTextureParameterIUIV(TextureName texture, GetTextureParameter pname,
                                 GLuint *params) const;
    void getTextureParameterFV(TextureName texture, GetTextureParameter pname,
                               GLfloat *params) const;
    void getTextureParameterIV(TextureName texture, GetTextureParameter pname,
                               GLint *params) const;
    void getTextureSubImage(TextureName texture, GLint level, GLint xoffset,
                            GLint yoffset, GLint zoffset, GLsizei width,
                            GLsizei height, GLsizei depth, PixelFormat format,
                            PixelType type, GLsizei bufSize, void *pixels) const;
    void getTransformFeedbackI64(TransformFeedbackName xfb,
                                 TransformFeedbackPName pname, GLuint index,
                                 GLint64 *param) const;
    void getTransformFeedbackIV(TransformFeedbackName xfb,
                                TransformFeedbackPName pname, GLuint index,
                                GLint *param) const;
    void getTransformFeedbackIV(TransformFeedbackName xfb,
                                TransformFeedbackPName pname, GLint *param) const;
    void getVertexArrayIndexed64IV(VertexArrayName vaobj, GLuint index,
                                   VertexArrayPName pname, GLint64 *param) const;
    void getVertexArrayIndexedIV(VertexArrayName vaobj, GLuint index,
                                 VertexArrayPName pname, GLint *param) const;
    void getVertexArrayIV(VertexArrayName vaobj, VertexArrayPName pname,
                          GLint *param) const;
    void getnCompressedTexImage(TextureTarget target, GLint lod, GLsizei bufSize,
                                void *pixels) const;
    void getnTexImage(TextureTarget target, GLint level, PixelFormat format,
                      PixelType type, GLsizei bufSize, void *pixels) const;
    void getnUniformDV(ProgramName program, GLint location, GLsizei bufSize,
                       GLdouble *params) const;
    void getnUniformFV(ProgramName program, GLint location, GLsizei bufSize,
                       GLfloat *params) const;
    void getnUniformIV(ProgramName program, GLint location, GLsizei bufSize,
                       GLint *params) const;
    void getnUniformUIV(ProgramName program, GLint location, GLsizei bufSize,
                        GLuint *params) const;
    void invalidateNamedFramebufferData(FrameBufferName framebuffer,
                                        GLsizei numAttachments,
                                        const FramebufferAttachment *attachments) const;
    void invalidateNamedFramebufferSubData(FrameBufferName framebuffer,
                                           GLsizei numAttachments,
                                           const FramebufferAttachment *attachments,
                                           GLint x, GLint y, GLsizei width,
                                           GLsizei height) const;
    void *mapNamedBuffer(BufferName buffer, BufferAccess access) const;
    void *mapNamedBufferRange(BufferName buffer, GLintptr offset,
                              GLsizeiptr length,
                              GLbitfield  /* MapBufferAccessMask */ access) const;
    void memoryBarrierByRegion(GLbitfield  /* MemoryBarrierMask */ barriers) const;
    void namedBufferData(BufferName buffer, GLsizeiptr size, const void *data,
                         VertexBufferObjectUsage usage) const;
    void namedBufferStorage(BufferName buffer, GLsizeiptr size, const void *data,
                            GLbitfield  /* BufferStorageMask */ flags) const;
    void namedBufferSubData(BufferName buffer, GLintptr offset, GLsizeiptr size,
                            const void *data) const;
    void namedFramebufferDrawBuffer(FrameBufferName framebuffer, ColorBuffer buf) const;
    void namedFramebufferDrawBuffers(FrameBufferName framebuffer, GLsizei n,
                                     const ColorBuffer *bufs) const;
    void namedFramebufferParameterI(FrameBufferName framebuffer,
                                    FrameBufferParameterName pname, GLint param) const;
    void namedFramebufferReadBuffer(FrameBufferName framebuffer, ColorBuffer src) const;
    void namedFramebufferRenderbuffer(FrameBufferName framebuffer,
                                      FramebufferAttachment attachment,
                                      RenderBufferTarget renderbuffertarget,
                                      RenderBufferName renderbuffer) const;
    void namedFramebufferTexture(FrameBufferName framebuffer,
                                 FramebufferAttachment attachment,
                                 TextureName texture, GLint level) const;
    void namedFramebufferTextureLayer(FrameBufferName framebuffer,
                                      FramebufferAttachment attachment,
                                      TextureName texture, GLint level,
                                      GLint layer) const;
    void namedRenderbufferStorage(RenderBufferName renderbuffer,
                                  InternalFormat internalformat, GLsizei width,
                                  GLsizei height) const;
    void namedRenderbufferStorageMultisample(RenderBufferName renderbuffer,
                                             GLsizei samples,
                                             InternalFormat internalformat,
                                             GLsizei width, GLsizei height) const;
    void readnPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                     PixelFormat format, PixelType type, GLsizei bufSize,
                     void *data) const;
    void textureBarrier() const;
    void textureBuffer(TextureName texture, SizedInternalFormat internalformat,
                       BufferName buffer) const;
    void textureBufferRange(TextureName texture,
                            SizedInternalFormat internalformat,
                            BufferName buffer, GLintptr offset, GLsizeiptr size) const;
    void textureParameterIIV(TextureName texture, TextureParameterName pname,
                             const GLint *params) const;
    void textureParameterIUIV(TextureName texture, TextureParameterName pname,
                              const GLuint *params) const;
    void textureParameterF(TextureName texture, TextureParameterName pname,
                           GLfloat param) const;
    void textureParameterFV(TextureName texture, TextureParameterName pname,
                            const GLfloat *param) const;
    void textureParameterI(TextureName texture, TextureParameterName pname,
                           GLint param) const;
    void textureParameterIV(TextureName texture, TextureParameterName pname,
                            const GLint *param) const;
    void textureStorage1D(TextureName texture, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width) const;
    void textureStorage2D(TextureName texture, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width,
                          GLsizei height) const;
    void textureStorage2DMultisample(TextureName texture, GLsizei samples,
                                     SizedInternalFormat internalformat,
                                     GLsizei width, GLsizei height,
                                     Boolean fixedsamplelocations) const;
    void textureStorage3D(TextureName texture, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width,
                          GLsizei height, GLsizei depth) const;
    void textureStorage3DMultisample(TextureName texture, GLsizei samples,
                                     SizedInternalFormat internalformat,
                                     GLsizei width, GLsizei height,
                                     GLsizei depth, Boolean fixedsamplelocations) const;
    void textureSubImage1D(TextureName texture, GLint level, GLint xoffset,
                           GLsizei width, PixelFormat format, PixelType type,
                           const void *pixels) const;
    void textureSubImage2D(TextureName texture, GLint level, GLint xoffset,
                           GLint yoffset, GLsizei width, GLsizei height,
                           PixelFormat format, PixelType type,
                           const void *pixels) const;
    void textureSubImage3D(TextureName texture, GLint level, GLint xoffset,
                           GLint yoffset, GLint zoffset, GLsizei width,
                           GLsizei height, GLsizei depth, PixelFormat format,
                           PixelType type, const void *pixels) const;
    void transformFeedbackBufferBase(TransformFeedbackName xfb, GLuint index,
                                     BufferName buffer) const;
    void transformFeedbackBufferRange(TransformFeedbackName xfb, GLuint index,
                                      BufferName buffer, GLintptr offset,
                                      GLsizeiptr size) const;
    Boolean unmapNamedBuffer(BufferName buffer) const;
    void vertexArrayAttribBinding(VertexArrayName vaobj, GLuint attribindex,
                                  GLuint bindingindex) const;
    void vertexArrayAttribFormat(VertexArrayName vaobj, GLuint attribindex,
                                 GLint size, VertexAttribType type,
                                 Boolean normalized, GLuint relativeoffset) const;
    void vertexArrayAttribIFormat(VertexArrayName vaobj, GLuint attribindex,
                                  GLint size, VertexAttribIType type,
                                  GLuint relativeoffset) const;
    void vertexArrayAttribLFormat(VertexArrayName vaobj, GLuint attribindex,
                                  GLint size, VertexAttribLType type,
                                  GLuint relativeoffset) const;
    void vertexArrayBindingDivisor(VertexArrayName vaobj, GLuint bindingindex,
                                   GLuint divisor) const;
    void vertexArrayElementBuffer(VertexArrayName vaobj, BufferName buffer) const;
    void vertexArrayVertexBuffer(VertexArrayName vaobj, GLuint bindingindex,
                                 BufferName buffer, GLintptr offset,
                                 GLsizei stride) const;
    void vertexArrayVertexBuffers(VertexArrayName vaobj, GLuint first,
                                  GLsizei count, const BufferName *buffers,
                                  const GLintptr *offsets,
                                  const GLsizei *strides) const;
#pragma endregion

#pragma region Core GL 4.6
    // GL 4.6
    void multiDrawArraysIndirectCount(PrimitiveType mode, const void *indirect,
                                      GLintptr drawcount, GLsizei maxdrawcount,
                                      GLsizei stride) const;
    void multiDrawElementsIndirectCount(PrimitiveType mode,
                                        DrawElementsType type,
                                        const void *indirect, GLintptr drawcount,
                                        GLsizei maxdrawcount, GLsizei stride) const;
    void polygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) const;
    void specializeShader(ShaderName shader, const GLchar *pEntryPoint,
                          GLuint numSpecializationConstants,
                          const GLuint *pConstantIndex,
                          const GLuint *pConstantValue) const;
#pragma endregion
#pragma endregion
    // Overrides
    virtual void resolve(const APIResolver* resolver) override;

private:
    GL _api;
    Ag::Version _version;
};

} // namespace gl

#endif // ifndef __C887F2C6_25FE_46FA_A234_66CE1D192F9E_INCLUDED__
