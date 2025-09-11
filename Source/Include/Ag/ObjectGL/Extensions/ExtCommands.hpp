//! @file Ag/ObjectGL/Extensions/ExtCommands.hpp
//! @brief The declaration of generic extensions to the OpenGL Command set
//! wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_EXT_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_EXT_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "Ext.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_EXT_EGL_image_storage extension API.
class EXTEglImageStorageAPI : public BaseExtension
{
public:
    // Construction
    EXTEglImageStorageAPI();

    // Accessors
    const EXTEglImageStorage &getRawAPI() const;

    // Operations
    void eglImageTargetTexStorage(GLenum target, GLeglImageOES image,
                                  const GLint *attrib_list) const;
    void eglImageTargetTextureStorage(TextureName texture, GLeglImageOES image,
                                      const GLint *attrib_list) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTEglImageStorage _api;
};

// Manages the entry points for the GL_EXT_bindable_uniform extension API.
class EXTBindableUniformAPI : public BaseExtension
{
public:
    // Construction
    EXTBindableUniformAPI();

    // Accessors
    const EXTBindableUniform &getRawAPI() const;

    // Operations
    GLint getUniformBufferSize(ProgramName program, GLint location) const;
    GLintptr getUniformOffset(ProgramName program, GLint location) const;
    void uniformBuffer(ProgramName program, GLint location, BufferName buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTBindableUniform _api;
};

// Manages the entry points for the GL_EXT_blend_color extension API.
class EXTBlendColorAPI : public BaseExtension
{
public:
    // Construction
    EXTBlendColorAPI();

    // Accessors
    const EXTBlendColor &getRawAPI() const;

    // Operations
    void blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTBlendColor _api;
};

// Manages the entry points for the GL_EXT_blend_equation_separate extension API.
class EXTBlendEquationSeparateAPI : public BaseExtension
{
public:
    // Construction
    EXTBlendEquationSeparateAPI();

    // Accessors
    const EXTBlendEquationSeparate &getRawAPI() const;

    // Operations
    void blendEquationSeparate(BlendEquationModeEXT modeRGB,
                               BlendEquationModeEXT modeAlpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTBlendEquationSeparate _api;
};

// Manages the entry points for the GL_EXT_blend_func_separate extension API.
class EXTBlendFuncSeparateAPI : public BaseExtension
{
public:
    // Construction
    EXTBlendFuncSeparateAPI();

    // Accessors
    const EXTBlendFuncSeparate &getRawAPI() const;

    // Operations
    void blendFuncSeparate(BlendingFactor sfactorRGB, BlendingFactor dfactorRGB,
                           BlendingFactor sfactorAlpha,
                           BlendingFactor dfactorAlpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTBlendFuncSeparate _api;
};

// Manages the entry points for the GL_EXT_blend_minmax extension API.
class EXTBlendMinmaxAPI : public BaseExtension
{
public:
    // Construction
    EXTBlendMinmaxAPI();

    // Accessors
    const EXTBlendMinmax &getRawAPI() const;

    // Operations
    void blendEquation(BlendEquationModeEXT mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTBlendMinmax _api;
};

// Manages the entry points for the GL_EXT_color_subtable extension API.
class EXTColorSubtableAPI : public BaseExtension
{
public:
    // Construction
    EXTColorSubtableAPI();

    // Accessors
    const EXTColorSubtable &getRawAPI() const;

    // Operations
    void colorSubTable(GLenum target, GLsizei start, GLsizei count,
                       PixelFormat format, PixelType type, const void *data) const;
    void copyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y,
                           GLsizei width) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTColorSubtable _api;
};

// Manages the entry points for the GL_EXT_compiled_vertex_array extension API.
class EXTCompiledVertexArrayAPI : public BaseExtension
{
public:
    // Construction
    EXTCompiledVertexArrayAPI();

    // Accessors
    const EXTCompiledVertexArray &getRawAPI() const;

    // Operations
    void lockArrays(GLint first, GLsizei count) const;
    void unlockArrays() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTCompiledVertexArray _api;
};

// Manages the entry points for the GL_EXT_convolution extension API.
class EXTConvolutionAPI : public BaseExtension
{
public:
    // Construction
    EXTConvolutionAPI();

    // Accessors
    const EXTConvolution &getRawAPI() const;

    // Operations
    void convolutionFilter1D(ConvolutionTargetEXT target,
                             InternalFormat internalformat, GLsizei width,
                             PixelFormat format, PixelType type,
                             const void *image) const;
    void convolutionFilter2D(ConvolutionTargetEXT target,
                             InternalFormat internalformat, GLsizei width,
                             GLsizei height, PixelFormat format, PixelType type,
                             const void *image) const;
    void convolutionParameterF(ConvolutionTargetEXT target,
                               ConvolutionParameterEXT pname, GLfloat params) const;
    void convolutionParameterFV(ConvolutionTargetEXT target,
                                ConvolutionParameterEXT pname,
                                const GLfloat *params) const;
    void convolutionParameterI(ConvolutionTargetEXT target,
                               ConvolutionParameterEXT pname, GLint params) const;
    void convolutionParameterIV(ConvolutionTargetEXT target,
                                ConvolutionParameterEXT pname,
                                const GLint *params) const;
    void copyConvolutionFilter1D(ConvolutionTargetEXT target,
                                 InternalFormat internalformat, GLint x, GLint y,
                                 GLsizei width) const;
    void copyConvolutionFilter2D(ConvolutionTargetEXT target,
                                 InternalFormat internalformat, GLint x, GLint y,
                                 GLsizei width, GLsizei height) const;
    void getConvolutionFilter(ConvolutionTargetEXT target, PixelFormat format,
                              PixelType type, void *image) const;
    void getConvolutionParameterFV(ConvolutionTargetEXT target,
                                   ConvolutionParameterEXT pname,
                                   GLfloat *params) const;
    void getConvolutionParameterIV(ConvolutionTargetEXT target,
                                   ConvolutionParameterEXT pname, GLint *params) const;
    void getSeparableFilter(SeparableTargetEXT target, PixelFormat format,
                            PixelType type, void *row, void *column, void *span) const;
    void separableFilter2D(SeparableTargetEXT target,
                           InternalFormat internalformat, GLsizei width,
                           GLsizei height, PixelFormat format, PixelType type,
                           const void *row, const void *column) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTConvolution _api;
};

// Manages the entry points for the GL_EXT_coordinate_frame extension API.
class EXTCoordinateFrameAPI : public BaseExtension
{
public:
    // Construction
    EXTCoordinateFrameAPI();

    // Accessors
    const EXTCoordinateFrame &getRawAPI() const;

    // Operations
    void binormal3B(GLbyte bx, GLbyte by, GLbyte bz) const;
    void binormal3BV(const GLbyte *v) const;
    void binormal3D(GLdouble bx, GLdouble by, GLdouble bz) const;
    void binormal3DV(const GLdouble *v) const;
    void binormal3F(GLfloat bx, GLfloat by, GLfloat bz) const;
    void binormal3FV(const GLfloat *v) const;
    void binormal3I(GLint bx, GLint by, GLint bz) const;
    void binormal3IV(const GLint *v) const;
    void binormal3S(GLshort bx, GLshort by, GLshort bz) const;
    void binormal3SV(const GLshort *v) const;
    void binormalPointer(BinormalPointerTypeEXT type, GLsizei stride,
                         const void *pointer) const;
    void tangent3B(GLbyte tx, GLbyte ty, GLbyte tz) const;
    void tangent3BV(const GLbyte *v) const;
    void tangent3D(GLdouble tx, GLdouble ty, GLdouble tz) const;
    void tangent3DV(const GLdouble *v) const;
    void tangent3F(GLfloat tx, GLfloat ty, GLfloat tz) const;
    void tangent3FV(const GLfloat *v) const;
    void tangent3I(GLint tx, GLint ty, GLint tz) const;
    void tangent3IV(const GLint *v) const;
    void tangent3S(GLshort tx, GLshort ty, GLshort tz) const;
    void tangent3SV(const GLshort *v) const;
    void tangentPointer(TangentPointerTypeEXT type, GLsizei stride,
                        const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTCoordinateFrame _api;
};

// Manages the entry points for the GL_EXT_copy_texture extension API.
class EXTCopyTextureAPI : public BaseExtension
{
public:
    // Construction
    EXTCopyTextureAPI();

    // Accessors
    const EXTCopyTexture &getRawAPI() const;

    // Operations
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
    void copyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                           GLint yoffset, GLint zoffset, GLint x, GLint y,
                           GLsizei width, GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTCopyTexture _api;
};

// Manages the entry points for the GL_EXT_cull_vertex extension API.
class EXTCullVertexAPI : public BaseExtension
{
public:
    // Construction
    EXTCullVertexAPI();

    // Accessors
    const EXTCullVertex &getRawAPI() const;

    // Operations
    void cullParameterDV(CullParameterEXT pname, GLdouble *params) const;
    void cullParameterFV(CullParameterEXT pname, GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTCullVertex _api;
};

// Manages the entry points for the GL_EXT_debug_label extension API.
class EXTDebugLabelAPI : public BaseExtension
{
public:
    // Construction
    EXTDebugLabelAPI();

    // Accessors
    const EXTDebugLabel &getRawAPI() const;

    // Operations
    void getObjectLabel(GLenum type, GLuint object, GLsizei bufSize,
                        GLsizei *length, GLchar *label) const;
    void labelObject(GLenum type, GLuint object, GLsizei length,
                     const GLchar *label) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDebugLabel _api;
};

// Manages the entry points for the GL_EXT_debug_marker extension API.
class EXTDebugMarkerAPI : public BaseExtension
{
public:
    // Construction
    EXTDebugMarkerAPI();

    // Accessors
    const EXTDebugMarker &getRawAPI() const;

    // Operations
    void insertEventMarker(GLsizei length, const GLchar *marker) const;
    void popGroupMarker() const;
    void pushGroupMarker(GLsizei length, const GLchar *marker) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDebugMarker _api;
};

// Manages the entry points for the GL_EXT_depth_bounds_test extension API.
class EXTDepthBoundsTestAPI : public BaseExtension
{
public:
    // Construction
    EXTDepthBoundsTestAPI();

    // Accessors
    const EXTDepthBoundsTest &getRawAPI() const;

    // Operations
    void depthBounds(GLclampd zmin, GLclampd zmax) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDepthBoundsTest _api;
};

// Manages the entry points for the GL_EXT_direct_state_access extension API.
class EXTDirectStateAccessAPI : public BaseExtension
{
public:
    // Construction
    EXTDirectStateAccessAPI();

    // Accessors
    const EXTDirectStateAccess &getRawAPI() const;

    // Operations
    void bindMultiTexture(TextureUnit texunit, TextureTarget target,
                          TextureName texture) const;
    FrameBufferStatus checkNamedFramebufferStatus(FrameBufferName framebuffer,
                                                  FrameBufferTarget target) const;
    void clearNamedBufferData(BufferName buffer,
                              SizedInternalFormat internalformat,
                              PixelFormat format, PixelType type,
                              const void *data) const;
    void clearNamedBufferSubData(BufferName buffer,
                                 SizedInternalFormat internalformat,
                                 GLsizeiptr offset, GLsizeiptr size,
                                 PixelFormat format, PixelType type,
                                 const void *data) const;
    void clientAttribDefault(GLbitfield mask) const;
    void compressedMultiTexImage1D(TextureUnit texunit, TextureTarget target,
                                   GLint level, InternalFormat internalformat,
                                   GLsizei width, GLint border,
                                   GLsizei imageSize, const void *bits) const;
    void compressedMultiTexImage2D(TextureUnit texunit, TextureTarget target,
                                   GLint level, InternalFormat internalformat,
                                   GLsizei width, GLsizei height, GLint border,
                                   GLsizei imageSize, const void *bits) const;
    void compressedMultiTexImage3D(TextureUnit texunit, TextureTarget target,
                                   GLint level, InternalFormat internalformat,
                                   GLsizei width, GLsizei height, GLsizei depth,
                                   GLint border, GLsizei imageSize,
                                   const void *bits) const;
    void compressedMultiTexSubImage1D(TextureUnit texunit, TextureTarget target,
                                      GLint level, GLint xoffset, GLsizei width,
                                      InternalFormat format, GLsizei imageSize,
                                      const void *bits) const;
    void compressedMultiTexSubImage2D(TextureUnit texunit, TextureTarget target,
                                      GLint level, GLint xoffset, GLint yoffset,
                                      GLsizei width, GLsizei height,
                                      InternalFormat format, GLsizei imageSize,
                                      const void *bits) const;
    void compressedMultiTexSubImage3D(TextureUnit texunit, TextureTarget target,
                                      GLint level, GLint xoffset, GLint yoffset,
                                      GLint zoffset, GLsizei width,
                                      GLsizei height, GLsizei depth,
                                      InternalFormat format, GLsizei imageSize,
                                      const void *bits) const;
    void compressedTextureImage1D(TextureName texture, TextureTarget target,
                                  GLint level, InternalFormat internalformat,
                                  GLsizei width, GLint border, GLsizei imageSize,
                                  const void *bits) const;
    void compressedTextureImage2D(TextureName texture, TextureTarget target,
                                  GLint level, InternalFormat internalformat,
                                  GLsizei width, GLsizei height, GLint border,
                                  GLsizei imageSize, const void *bits) const;
    void compressedTextureImage3D(TextureName texture, TextureTarget target,
                                  GLint level, InternalFormat internalformat,
                                  GLsizei width, GLsizei height, GLsizei depth,
                                  GLint border, GLsizei imageSize,
                                  const void *bits) const;
    void compressedTextureSubImage1D(TextureName texture, TextureTarget target,
                                     GLint level, GLint xoffset, GLsizei width,
                                     InternalFormat format, GLsizei imageSize,
                                     const void *bits) const;
    void compressedTextureSubImage2D(TextureName texture, TextureTarget target,
                                     GLint level, GLint xoffset, GLint yoffset,
                                     GLsizei width, GLsizei height,
                                     InternalFormat format, GLsizei imageSize,
                                     const void *bits) const;
    void compressedTextureSubImage3D(TextureName texture, TextureTarget target,
                                     GLint level, GLint xoffset, GLint yoffset,
                                     GLint zoffset, GLsizei width,
                                     GLsizei height, GLsizei depth,
                                     InternalFormat format, GLsizei imageSize,
                                     const void *bits) const;
    void copyMultiTexImage1D(TextureUnit texunit, TextureTarget target,
                             GLint level, InternalFormat internalformat, GLint x,
                             GLint y, GLsizei width, GLint border) const;
    void copyMultiTexImage2D(TextureUnit texunit, TextureTarget target,
                             GLint level, InternalFormat internalformat, GLint x,
                             GLint y, GLsizei width, GLsizei height,
                             GLint border) const;
    void copyMultiTexSubImage1D(TextureUnit texunit, TextureTarget target,
                                GLint level, GLint xoffset, GLint x, GLint y,
                                GLsizei width) const;
    void copyMultiTexSubImage2D(TextureUnit texunit, TextureTarget target,
                                GLint level, GLint xoffset, GLint yoffset,
                                GLint x, GLint y, GLsizei width, GLsizei height) const;
    void copyMultiTexSubImage3D(TextureUnit texunit, TextureTarget target,
                                GLint level, GLint xoffset, GLint yoffset,
                                GLint zoffset, GLint x, GLint y, GLsizei width,
                                GLsizei height) const;
    void copyTextureImage1D(TextureName texture, TextureTarget target,
                            GLint level, InternalFormat internalformat, GLint x,
                            GLint y, GLsizei width, GLint border) const;
    void copyTextureImage2D(TextureName texture, TextureTarget target,
                            GLint level, InternalFormat internalformat, GLint x,
                            GLint y, GLsizei width, GLsizei height, GLint border) const;
    void copyTextureSubImage1D(TextureName texture, TextureTarget target,
                               GLint level, GLint xoffset, GLint x, GLint y,
                               GLsizei width) const;
    void copyTextureSubImage2D(TextureName texture, TextureTarget target,
                               GLint level, GLint xoffset, GLint yoffset,
                               GLint x, GLint y, GLsizei width, GLsizei height) const;
    void copyTextureSubImage3D(TextureName texture, TextureTarget target,
                               GLint level, GLint xoffset, GLint yoffset,
                               GLint zoffset, GLint x, GLint y, GLsizei width,
                               GLsizei height) const;
    void disableClientStateIndexed(EnableCap array, GLuint index) const;
    void disableClientStateI(EnableCap array, GLuint index) const;
    void disableIndexed(EnableCap target, GLuint index) const;
    void disableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const;
    void disableVertexArray(VertexArrayName vaobj, EnableCap array) const;
    void enableClientStateIndexed(EnableCap array, GLuint index) const;
    void enableClientStateI(EnableCap array, GLuint index) const;
    void enableIndexed(EnableCap target, GLuint index) const;
    void enableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const;
    void enableVertexArray(VertexArrayName vaobj, EnableCap array) const;
    void flushMappedNamedBufferRange(BufferName buffer, GLintptr offset,
                                     GLsizeiptr length) const;
    void framebufferDrawBuffer(FrameBufferName framebuffer, DrawBufferMode mode) const;
    void framebufferDrawBuffers(FrameBufferName framebuffer, GLsizei n,
                                const DrawBufferMode *bufs) const;
    void framebufferReadBuffer(FrameBufferName framebuffer, ReadBufferMode mode) const;
    void generateMultiTexMipmap(TextureUnit texunit, TextureTarget target) const;
    void generateTextureMipmap(TextureName texture, TextureTarget target) const;
    void getBooleanIndexedv(BufferTarget target, GLuint index, Boolean *data) const;
    void getCompressedMultiTexImage(TextureUnit texunit, TextureTarget target,
                                    GLint lod, void *img) const;
    void getCompressedTextureImage(TextureName texture, TextureTarget target,
                                   GLint lod, void *img) const;
    void getDoubleIndexedv(GetPName target, GLuint index, GLdouble *data) const;
    void getDoubleIV(GetPName pname, GLuint index, GLdouble *params) const;
    void getFloatIndexedv(GetPName target, GLuint index, GLfloat *data) const;
    void getFloatIV(GetPName pname, GLuint index, GLfloat *params) const;
    void getFramebufferParameterIV(FrameBufferName framebuffer,
                                   GetFramebufferParameter pname, GLint *params) const;
    void getIntegerIndexedv(GetPName target, GLuint index, GLint *data) const;
    void getMultiTexEnvFV(TextureUnit texunit, GLenum target, GLenum pname,
                          GLfloat *params) const;
    void getMultiTexEnvIV(TextureUnit texunit, GLenum target, GLenum pname,
                          GLint *params) const;
    void getMultiTexGenDV(TextureUnit texunit, GLenum coord,
                          TextureGenParameter pname, GLdouble *params) const;
    void getMultiTexGenFV(TextureUnit texunit, GLenum coord,
                          TextureGenParameter pname, GLfloat *params) const;
    void getMultiTexGenIV(TextureUnit texunit, GLenum coord,
                          TextureGenParameter pname, GLint *params) const;
    void getMultiTexImage(TextureUnit texunit, TextureTarget target, GLint level,
                          PixelFormat format, PixelType type, void *pixels) const;
    void getMultiTexLevelParameterFV(TextureUnit texunit, TextureTarget target,
                                     GLint level, GetTextureParameter pname,
                                     GLfloat *params) const;
    void getMultiTexLevelParameterIV(TextureUnit texunit, TextureTarget target,
                                     GLint level, GetTextureParameter pname,
                                     GLint *params) const;
    void getMultiTexParameterIIV(TextureUnit texunit, TextureTarget target,
                                 GetTextureParameter pname, GLint *params) const;
    void getMultiTexParameterIUIV(TextureUnit texunit, TextureTarget target,
                                  GetTextureParameter pname, GLuint *params) const;
    void getMultiTexParameterFV(TextureUnit texunit, TextureTarget target,
                                GetTextureParameter pname, GLfloat *params) const;
    void getMultiTexParameterIV(TextureUnit texunit, TextureTarget target,
                                GetTextureParameter pname, GLint *params) const;
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
                                        GLint *params) const;
    void getNamedProgramLocalParameterIIV(ProgramName program,
                                          ProgramTarget target, GLuint index,
                                          GLint *params) const;
    void getNamedProgramLocalParameterIUIV(ProgramName program,
                                           ProgramTarget target, GLuint index,
                                           GLuint *params) const;
    void getNamedProgramLocalParameterDV(ProgramName program,
                                         ProgramTarget target, GLuint index,
                                         GLdouble *params) const;
    void getNamedProgramLocalParameterFV(ProgramName program,
                                         ProgramTarget target, GLuint index,
                                         GLfloat *params) const;
    void getNamedProgramString(ProgramName program, ProgramTarget target,
                               ProgramStringProperty pname, void *string) const;
    void getNamedProgramIV(ProgramName program, ProgramTarget target,
                           ProgramProperty pname, GLint *params) const;
    void getNamedRenderbufferParameterIV(RenderBufferName renderbuffer,
                                         RenderBufferParameterName pname,
                                         GLint *params) const;
    void getPointerIndexedv(GLenum target, GLuint index, void **data) const;
    void getPointerIV(GLenum pname, GLuint index, void **params) const;
    void getTextureImage(TextureName texture, TextureTarget target, GLint level,
                         PixelFormat format, PixelType type, void *pixels) const;
    void getTextureLevelParameterFV(TextureName texture, TextureTarget target,
                                    GLint level, GetTextureParameter pname,
                                    GLfloat *params) const;
    void getTextureLevelParameterIV(TextureName texture, TextureTarget target,
                                    GLint level, GetTextureParameter pname,
                                    GLint *params) const;
    void getTextureParameterIIV(TextureName texture, TextureTarget target,
                                GetTextureParameter pname, GLint *params) const;
    void getTextureParameterIUIV(TextureName texture, TextureTarget target,
                                 GetTextureParameter pname, GLuint *params) const;
    void getTextureParameterFV(TextureName texture, TextureTarget target,
                               GetTextureParameter pname, GLfloat *params) const;
    void getTextureParameterIV(TextureName texture, TextureTarget target,
                               GetTextureParameter pname, GLint *params) const;
    void getVertexArrayIntegerIV(VertexArrayName vaobj, GLuint index,
                                 VertexArrayPName pname, GLint *param) const;
    void getVertexArrayIntegerV(VertexArrayName vaobj, VertexArrayPName pname,
                                GLint *param) const;
    void getVertexArrayPointerIV(VertexArrayName vaobj, GLuint index,
                                 VertexArrayPName pname, void **param) const;
    void getVertexArrayPointerV(VertexArrayName vaobj, VertexArrayPName pname,
                                void **param) const;
    Boolean isEnabledIndexed(EnableCap target, GLuint index) const;
    void *mapNamedBuffer(BufferName buffer, BufferAccess access) const;
    void *mapNamedBufferRange(BufferName buffer, GLintptr offset,
                              GLsizeiptr length,
                              GLbitfield  /* MapBufferAccessMask */ access) const;
    void matrixFrustum(MatrixMode mode, GLdouble left, GLdouble right,
                       GLdouble bottom, GLdouble top, GLdouble zNear,
                       GLdouble zFar) const;
    void matrixLoadIdentity(MatrixMode mode) const;
    void matrixLoadTransposeD(MatrixMode mode, const GLdouble *m) const;
    void matrixLoadTransposeF(MatrixMode mode, const GLfloat *m) const;
    void matrixLoadD(MatrixMode mode, const GLdouble *m) const;
    void matrixLoadF(MatrixMode mode, const GLfloat *m) const;
    void matrixMultTransposeD(MatrixMode mode, const GLdouble *m) const;
    void matrixMultTransposeF(MatrixMode mode, const GLfloat *m) const;
    void matrixMultD(MatrixMode mode, const GLdouble *m) const;
    void matrixMultF(MatrixMode mode, const GLfloat *m) const;
    void matrixOrtho(MatrixMode mode, GLdouble left, GLdouble right,
                     GLdouble bottom, GLdouble top, GLdouble zNear,
                     GLdouble zFar) const;
    void matrixPop(MatrixMode mode) const;
    void matrixPush(MatrixMode mode) const;
    void matrixRotateD(MatrixMode mode, GLdouble angle, GLdouble x, GLdouble y,
                       GLdouble z) const;
    void matrixRotateF(MatrixMode mode, GLfloat angle, GLfloat x, GLfloat y,
                       GLfloat z) const;
    void matrixScaleD(MatrixMode mode, GLdouble x, GLdouble y, GLdouble z) const;
    void matrixScaleF(MatrixMode mode, GLfloat x, GLfloat y, GLfloat z) const;
    void matrixTranslateD(MatrixMode mode, GLdouble x, GLdouble y, GLdouble z) const;
    void matrixTranslateF(MatrixMode mode, GLfloat x, GLfloat y, GLfloat z) const;
    void multiTexBuffer(TextureUnit texunit, TextureTarget target,
                        InternalFormat internalformat, BufferName buffer) const;
    void multiTexCoordPointer(TextureUnit texunit, GLint size,
                              TexCoordPointerType type, GLsizei stride,
                              const void *pointer) const;
    void multiTexEnvF(TextureUnit texunit, GLenum target, GLenum pname,
                      GLfloat param) const;
    void multiTexEnvFV(TextureUnit texunit, GLenum target, GLenum pname,
                       const GLfloat *params) const;
    void multiTexEnvI(TextureUnit texunit, GLenum target, GLenum pname,
                      GLint param) const;
    void multiTexEnvIV(TextureUnit texunit, GLenum target, GLenum pname,
                       const GLint *params) const;
    void multiTexGenD(TextureUnit texunit, GLenum coord,
                      TextureGenParameter pname, GLdouble param) const;
    void multiTexGenDV(TextureUnit texunit, GLenum coord,
                       TextureGenParameter pname, const GLdouble *params) const;
    void multiTexGenF(TextureUnit texunit, GLenum coord,
                      TextureGenParameter pname, GLfloat param) const;
    void multiTexGenFV(TextureUnit texunit, GLenum coord,
                       TextureGenParameter pname, const GLfloat *params) const;
    void multiTexGenI(TextureUnit texunit, GLenum coord,
                      TextureGenParameter pname, GLint param) const;
    void multiTexGenIV(TextureUnit texunit, GLenum coord,
                       TextureGenParameter pname, const GLint *params) const;
    void multiTexImage1D(TextureUnit texunit, TextureTarget target, GLint level,
                         InternalFormat internalformat, GLsizei width,
                         GLint border, PixelFormat format, PixelType type,
                         const void *pixels) const;
    void multiTexImage2D(TextureUnit texunit, TextureTarget target, GLint level,
                         InternalFormat internalformat, GLsizei width,
                         GLsizei height, GLint border, PixelFormat format,
                         PixelType type, const void *pixels) const;
    void multiTexImage3D(TextureUnit texunit, TextureTarget target, GLint level,
                         InternalFormat internalformat, GLsizei width,
                         GLsizei height, GLsizei depth, GLint border,
                         PixelFormat format, PixelType type, const void *pixels) const;
    void multiTexParameterIIV(TextureUnit texunit, TextureTarget target,
                              TextureParameterName pname, const GLint *params) const;
    void multiTexParameterIUIV(TextureUnit texunit, TextureTarget target,
                               TextureParameterName pname, const GLuint *params) const;
    void multiTexParameterF(TextureUnit texunit, TextureTarget target,
                            TextureParameterName pname, GLfloat param) const;
    void multiTexParameterFV(TextureUnit texunit, TextureTarget target,
                             TextureParameterName pname, const GLfloat *params) const;
    void multiTexParameterI(TextureUnit texunit, TextureTarget target,
                            TextureParameterName pname, GLint param) const;
    void multiTexParameterIV(TextureUnit texunit, TextureTarget target,
                             TextureParameterName pname, const GLint *params) const;
    void multiTexRenderbuffer(TextureUnit texunit, TextureTarget target,
                              RenderBufferName renderbuffer) const;
    void multiTexSubImage1D(TextureUnit texunit, TextureTarget target,
                            GLint level, GLint xoffset, GLsizei width,
                            PixelFormat format, PixelType type,
                            const void *pixels) const;
    void multiTexSubImage2D(TextureUnit texunit, TextureTarget target,
                            GLint level, GLint xoffset, GLint yoffset,
                            GLsizei width, GLsizei height, PixelFormat format,
                            PixelType type, const void *pixels) const;
    void multiTexSubImage3D(TextureUnit texunit, TextureTarget target,
                            GLint level, GLint xoffset, GLint yoffset,
                            GLint zoffset, GLsizei width, GLsizei height,
                            GLsizei depth, PixelFormat format, PixelType type,
                            const void *pixels) const;
    void namedBufferData(BufferName buffer, GLsizeiptr size, const void *data,
                         VertexBufferObjectUsage usage) const;
    void namedBufferStorage(BufferName buffer, GLsizeiptr size, const void *data,
                            GLbitfield  /* BufferStorageMask */ flags) const;
    void namedBufferSubData(BufferName buffer, GLintptr offset, GLsizeiptr size,
                            const void *data) const;
    void namedCopyBufferSubData(BufferName readBuffer, BufferName writeBuffer,
                                GLintptr readOffset, GLintptr writeOffset,
                                GLsizeiptr size) const;
    void namedFramebufferParameterI(FrameBufferName framebuffer,
                                    FrameBufferParameterName pname, GLint param) const;
    void namedFramebufferRenderbuffer(FrameBufferName framebuffer,
                                      FramebufferAttachment attachment,
                                      RenderBufferTarget renderbuffertarget,
                                      RenderBufferName renderbuffer) const;
    void namedFramebufferTexture1D(FrameBufferName framebuffer,
                                   FramebufferAttachment attachment,
                                   TextureTarget textarget, TextureName texture,
                                   GLint level) const;
    void namedFramebufferTexture2D(FrameBufferName framebuffer,
                                   FramebufferAttachment attachment,
                                   TextureTarget textarget, TextureName texture,
                                   GLint level) const;
    void namedFramebufferTexture3D(FrameBufferName framebuffer,
                                   FramebufferAttachment attachment,
                                   TextureTarget textarget, TextureName texture,
                                   GLint level, GLint zoffset) const;
    void namedFramebufferTexture(FrameBufferName framebuffer,
                                 FramebufferAttachment attachment,
                                 TextureName texture, GLint level) const;
    void namedFramebufferTextureFace(FrameBufferName framebuffer,
                                     FramebufferAttachment attachment,
                                     TextureName texture, GLint level,
                                     TextureTarget face) const;
    void namedFramebufferTextureLayer(FrameBufferName framebuffer,
                                      FramebufferAttachment attachment,
                                      TextureName texture, GLint level,
                                      GLint layer) const;
    void namedProgramLocalParameter4D(ProgramName program, ProgramTarget target,
                                      GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z, GLdouble w) const;
    void namedProgramLocalParameter4DV(ProgramName program, ProgramTarget target,
                                       GLuint index, const GLdouble *params) const;
    void namedProgramLocalParameter4F(ProgramName program, ProgramTarget target,
                                      GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z, GLfloat w) const;
    void namedProgramLocalParameter4FV(ProgramName program, ProgramTarget target,
                                       GLuint index, const GLfloat *params) const;
    void namedProgramLocalParameterI4I(ProgramName program, ProgramTarget target,
                                       GLuint index, GLint x, GLint y, GLint z,
                                       GLint w) const;
    void namedProgramLocalParameterI4IV(ProgramName program,
                                        ProgramTarget target, GLuint index,
                                        const GLint *params) const;
    void namedProgramLocalParameterI4UI(ProgramName program,
                                        ProgramTarget target, GLuint index,
                                        GLuint x, GLuint y, GLuint z, GLuint w) const;
    void namedProgramLocalParameterI4UIV(ProgramName program,
                                         ProgramTarget target, GLuint index,
                                         const GLuint *params) const;
    void namedProgramLocalParameters4FV(ProgramName program,
                                        ProgramTarget target, GLuint index,
                                        GLsizei count, const GLfloat *params) const;
    void namedProgramLocalParametersI4IV(ProgramName program,
                                         ProgramTarget target, GLuint index,
                                         GLsizei count, const GLint *params) const;
    void namedProgramLocalParametersI4UIV(ProgramName program,
                                          ProgramTarget target, GLuint index,
                                          GLsizei count, const GLuint *params) const;
    void namedProgramString(ProgramName program, ProgramTarget target,
                            ProgramFormat format, GLsizei len,
                            const void *string) const;
    void namedRenderbufferStorage(RenderBufferName renderbuffer,
                                  InternalFormat internalformat, GLsizei width,
                                  GLsizei height) const;
    void namedRenderbufferStorageMultisampleCoverage(RenderBufferName renderbuffer,
                                                     GLsizei coverageSamples,
                                                     GLsizei colorSamples,
                                                     InternalFormat internalformat,
                                                     GLsizei width,
                                                     GLsizei height) const;
    void namedRenderbufferStorageMultisample(RenderBufferName renderbuffer,
                                             GLsizei samples,
                                             InternalFormat internalformat,
                                             GLsizei width, GLsizei height) const;
    void programUniform1D(ProgramName program, GLint location, GLdouble x) const;
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
    void programUniform2D(ProgramName program, GLint location, GLdouble x,
                          GLdouble y) const;
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
    void programUniform3D(ProgramName program, GLint location, GLdouble x,
                          GLdouble y, GLdouble z) const;
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
    void programUniform4D(ProgramName program, GLint location, GLdouble x,
                          GLdouble y, GLdouble z, GLdouble w) const;
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
    void pushClientAttribDefault(GLbitfield mask) const;
    void textureBuffer(TextureName texture, TextureTarget target,
                       SizedInternalFormat internalformat, BufferName buffer) const;
    void textureBufferRange(TextureName texture, TextureTarget target,
                            SizedInternalFormat internalformat,
                            BufferName buffer, GLintptr offset, GLsizeiptr size) const;
    void textureImage1D(TextureName texture, TextureTarget target, GLint level,
                        InternalFormat internalformat, GLsizei width,
                        GLint border, PixelFormat format, PixelType type,
                        const void *pixels) const;
    void textureImage2D(TextureName texture, TextureTarget target, GLint level,
                        InternalFormat internalformat, GLsizei width,
                        GLsizei height, GLint border, PixelFormat format,
                        PixelType type, const void *pixels) const;
    void textureImage3D(TextureName texture, TextureTarget target, GLint level,
                        InternalFormat internalformat, GLsizei width,
                        GLsizei height, GLsizei depth, GLint border,
                        PixelFormat format, PixelType type, const void *pixels) const;
    void texturePageCommitment(TextureName texture, GLint level, GLint xoffset,
                               GLint yoffset, GLint zoffset, GLsizei width,
                               GLsizei height, GLsizei depth, Boolean commit) const;
    void textureParameterIIV(TextureName texture, TextureTarget target,
                             TextureParameterName pname, const GLint *params) const;
    void textureParameterIUIV(TextureName texture, TextureTarget target,
                              TextureParameterName pname, const GLuint *params) const;
    void textureParameterF(TextureName texture, TextureTarget target,
                           TextureParameterName pname, GLfloat param) const;
    void textureParameterFV(TextureName texture, TextureTarget target,
                            TextureParameterName pname, const GLfloat *params) const;
    void textureParameterI(TextureName texture, TextureTarget target,
                           TextureParameterName pname, GLint param) const;
    void textureParameterIV(TextureName texture, TextureTarget target,
                            TextureParameterName pname, const GLint *params) const;
    void textureRenderbuffer(TextureName texture, TextureTarget target,
                             RenderBufferName renderbuffer) const;
    void textureStorage1D(TextureName texture, GLenum target, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width) const;
    void textureStorage2D(TextureName texture, GLenum target, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width,
                          GLsizei height) const;
    void textureStorage2DMultisample(TextureName texture, TextureTarget target,
                                     GLsizei samples,
                                     SizedInternalFormat internalformat,
                                     GLsizei width, GLsizei height,
                                     Boolean fixedsamplelocations) const;
    void textureStorage3D(TextureName texture, GLenum target, GLsizei levels,
                          SizedInternalFormat internalformat, GLsizei width,
                          GLsizei height, GLsizei depth) const;
    void textureStorage3DMultisample(TextureName texture, GLenum target,
                                     GLsizei samples,
                                     SizedInternalFormat internalformat,
                                     GLsizei width, GLsizei height,
                                     GLsizei depth, Boolean fixedsamplelocations) const;
    void textureSubImage1D(TextureName texture, TextureTarget target,
                           GLint level, GLint xoffset, GLsizei width,
                           PixelFormat format, PixelType type,
                           const void *pixels) const;
    void textureSubImage2D(TextureName texture, TextureTarget target,
                           GLint level, GLint xoffset, GLint yoffset,
                           GLsizei width, GLsizei height, PixelFormat format,
                           PixelType type, const void *pixels) const;
    void textureSubImage3D(TextureName texture, TextureTarget target,
                           GLint level, GLint xoffset, GLint yoffset,
                           GLint zoffset, GLsizei width, GLsizei height,
                           GLsizei depth, PixelFormat format, PixelType type,
                           const void *pixels) const;
    Boolean unmapNamedBuffer(BufferName buffer) const;
    void vertexArrayBindVertexBuffer(VertexArrayName vaobj, GLuint bindingindex,
                                     BufferName buffer, GLintptr offset,
                                     GLsizei stride) const;
    void vertexArrayColorOffset(VertexArrayName vaobj, BufferName buffer,
                                GLint size, ColorPointerType type,
                                GLsizei stride, GLintptr offset) const;
    void vertexArrayEdgeFlagOffset(VertexArrayName vaobj, BufferName buffer,
                                   GLsizei stride, GLintptr offset) const;
    void vertexArrayFogCoordOffset(VertexArrayName vaobj, BufferName buffer,
                                   FogCoordinatePointerType type, GLsizei stride,
                                   GLintptr offset) const;
    void vertexArrayIndexOffset(VertexArrayName vaobj, BufferName buffer,
                                IndexPointerType type, GLsizei stride,
                                GLintptr offset) const;
    void vertexArrayMultiTexCoordOffset(VertexArrayName vaobj, BufferName buffer,
                                        GLenum texunit, GLint size,
                                        TexCoordPointerType type, GLsizei stride,
                                        GLintptr offset) const;
    void vertexArrayNormalOffset(VertexArrayName vaobj, BufferName buffer,
                                 NormalPointerType type, GLsizei stride,
                                 GLintptr offset) const;
    void vertexArraySecondaryColorOffset(VertexArrayName vaobj,
                                         BufferName buffer, GLint size,
                                         ColorPointerType type, GLsizei stride,
                                         GLintptr offset) const;
    void vertexArrayTexCoordOffset(VertexArrayName vaobj, BufferName buffer,
                                   GLint size, TexCoordPointerType type,
                                   GLsizei stride, GLintptr offset) const;
    void vertexArrayVertexAttribBinding(VertexArrayName vaobj,
                                        GLuint attribindex, GLuint bindingindex) const;
    void vertexArrayVertexAttribDivisor(VertexArrayName vaobj, GLuint index,
                                        GLuint divisor) const;
    void vertexArrayVertexAttribFormat(VertexArrayName vaobj, GLuint attribindex,
                                       GLint size, VertexAttribType type,
                                       Boolean normalized, GLuint relativeoffset) const;
    void vertexArrayVertexAttribIFormat(VertexArrayName vaobj,
                                        GLuint attribindex, GLint size,
                                        VertexAttribIType type,
                                        GLuint relativeoffset) const;
    void vertexArrayVertexAttribIOffset(VertexArrayName vaobj, BufferName buffer,
                                        GLuint index, GLint size,
                                        VertexAttribType type, GLsizei stride,
                                        GLintptr offset) const;
    void vertexArrayVertexAttribLFormat(VertexArrayName vaobj,
                                        GLuint attribindex, GLint size,
                                        VertexAttribLType type,
                                        GLuint relativeoffset) const;
    void vertexArrayVertexAttribLOffset(VertexArrayName vaobj, BufferName buffer,
                                        GLuint index, GLint size,
                                        VertexAttribLType type, GLsizei stride,
                                        GLintptr offset) const;
    void vertexArrayVertexAttribOffset(VertexArrayName vaobj, BufferName buffer,
                                       GLuint index, GLint size,
                                       VertexAttribPointerType type,
                                       Boolean normalized, GLsizei stride,
                                       GLintptr offset) const;
    void vertexArrayVertexBindingDivisor(VertexArrayName vaobj,
                                         GLuint bindingindex, GLuint divisor) const;
    void vertexArrayVertexOffset(VertexArrayName vaobj, BufferName buffer,
                                 GLint size, VertexPointerType type,
                                 GLsizei stride, GLintptr offset) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDirectStateAccess _api;
};

// Manages the entry points for the GL_EXT_draw_buffers2 extension API.
class EXTDrawBUFFERS2API : public BaseExtension
{
public:
    // Construction
    EXTDrawBUFFERS2API();

    // Accessors
    const EXTDrawBUFFERS2 &getRawAPI() const;

    // Operations
    void colorMaskIndexed(GLuint index, Boolean r, Boolean g, Boolean b,
                          Boolean a) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDrawBUFFERS2 _api;
};

// Manages the entry points for the GL_EXT_draw_instanced extension API.
class EXTDrawInstancedAPI : public BaseExtension
{
public:
    // Construction
    EXTDrawInstancedAPI();

    // Accessors
    const EXTDrawInstanced &getRawAPI() const;

    // Operations
    void drawArraysInstanced(PrimitiveType mode, GLint start, GLsizei count,
                             GLsizei primcount) const;
    void drawElementsInstanced(PrimitiveType mode, GLsizei count,
                               DrawElementsType type, const void *indices,
                               GLsizei primcount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDrawInstanced _api;
};

// Manages the entry points for the GL_EXT_draw_range_elements extension API.
class EXTDrawRangeElementsAPI : public BaseExtension
{
public:
    // Construction
    EXTDrawRangeElementsAPI();

    // Accessors
    const EXTDrawRangeElements &getRawAPI() const;

    // Operations
    void drawRangeElements(PrimitiveType mode, GLuint start, GLuint end,
                           GLsizei count, DrawElementsType type,
                           const void *indices) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDrawRangeElements _api;
};

// Manages the entry points for the GL_EXT_external_buffer extension API.
class EXTExternalBufferAPI : public BaseExtension
{
public:
    // Construction
    EXTExternalBufferAPI();

    // Accessors
    const EXTExternalBuffer &getRawAPI() const;

    // Operations
    void bufferStorageExternal(GLenum target, GLintptr offset, GLsizeiptr size,
                               GLeglClientBufferEXT clientBuffer,
                               GLbitfield  /* BufferStorageMask */ flags) const;
    void namedBufferStorageExternal(BufferName buffer, GLintptr offset,
                                    GLsizeiptr size,
                                    GLeglClientBufferEXT clientBuffer,
                                    GLbitfield  /* BufferStorageMask */ flags) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTExternalBuffer _api;
};

// Manages the entry points for the GL_EXT_fog_coord extension API.
class EXTFogCoordAPI : public BaseExtension
{
public:
    // Construction
    EXTFogCoordAPI();

    // Accessors
    const EXTFogCoord &getRawAPI() const;

    // Operations
    void fogCoordPointer(FogPointerTypeEXT type, GLsizei stride,
                         const void *pointer) const;
    void fogCoordD(GLdouble coord) const;
    void fogCoordDV(const GLdouble *coord) const;
    void fogCoordF(GLfloat coord) const;
    void fogCoordFV(const GLfloat *coord) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTFogCoord _api;
};

// Manages the entry points for the GL_EXT_framebuffer_blit extension API.
class EXTFramebufferBlitAPI : public BaseExtension
{
public:
    // Construction
    EXTFramebufferBlitAPI();

    // Accessors
    const EXTFramebufferBlit &getRawAPI() const;

    // Operations
    void blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
                         GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                         GLbitfield  /* ClearBufferMask */ mask,
                         BlitFramebufferFilter filter) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTFramebufferBlit _api;
};

// Manages the entry points for the GL_EXT_framebuffer_multisample extension API.
class EXTFramebufferMultisampleAPI : public BaseExtension
{
public:
    // Construction
    EXTFramebufferMultisampleAPI();

    // Accessors
    const EXTFramebufferMultisample &getRawAPI() const;

    // Operations
    void renderbufferStorageMultisample(RenderBufferTarget target,
                                        GLsizei samples,
                                        InternalFormat internalformat,
                                        GLsizei width, GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTFramebufferMultisample _api;
};

// Manages the entry points for the GL_EXT_framebuffer_object extension API.
class EXTFramebufferObjectAPI : public BaseExtension
{
public:
    // Construction
    EXTFramebufferObjectAPI();

    // Accessors
    const EXTFramebufferObject &getRawAPI() const;

    // Operations
    void bindFramebuffer(FrameBufferTarget target, FrameBufferName framebuffer) const;
    void bindRenderbuffer(RenderBufferTarget target,
                          RenderBufferName renderbuffer) const;
    FrameBufferStatus checkFramebufferStatus(FrameBufferTarget target) const;
    void deleteFramebuffers(GLsizei n, const FrameBufferName *framebuffers) const;
    void deleteRenderbuffers(GLsizei n, const RenderBufferName *renderbuffers) const;
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
    void genFramebuffers(GLsizei n, FrameBufferName *framebuffers) const;
    void genRenderbuffers(GLsizei n, RenderBufferName *renderbuffers) const;
    void generateMipmap(TextureTarget target) const;
    void getFramebufferAttachmentParameterIV(FrameBufferTarget target,
                                             FramebufferAttachment attachment,
                                             FrameBufferAttachmentParameterName pname,
                                             GLint *params) const;
    void getRenderbufferParameterIV(RenderBufferTarget target,
                                    RenderBufferParameterName pname,
                                    GLint *params) const;
    Boolean isFramebuffer(FrameBufferName framebuffer) const;
    Boolean isRenderbuffer(RenderBufferName renderbuffer) const;
    void renderbufferStorage(RenderBufferTarget target,
                             InternalFormat internalformat, GLsizei width,
                             GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTFramebufferObject _api;
};

// Manages the entry points for the GL_EXT_geometry_shader4 extension API.
class EXTGeometrySHADER4API : public BaseExtension
{
public:
    // Construction
    EXTGeometrySHADER4API();

    // Accessors
    const EXTGeometrySHADER4 &getRawAPI() const;

    // Operations
    void programParameterI(ProgramName program, ProgramParameterPName pname,
                           GLint value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTGeometrySHADER4 _api;
};

// Manages the entry points for the GL_EXT_gpu_program_parameters extension API.
class EXTGPUProgramParametersAPI : public BaseExtension
{
public:
    // Construction
    EXTGPUProgramParametersAPI();

    // Accessors
    const EXTGPUProgramParameters &getRawAPI() const;

    // Operations
    void programEnvParameters4FV(ProgramTarget target, GLuint index,
                                 GLsizei count, const GLfloat *params) const;
    void programLocalParameters4FV(ProgramTarget target, GLuint index,
                                   GLsizei count, const GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTGPUProgramParameters _api;
};

// Manages the entry points for the GL_EXT_gpu_shader4 extension API.
class EXTGPUSHADER4API : public BaseExtension
{
public:
    // Construction
    EXTGPUSHADER4API();

    // Accessors
    const EXTGPUSHADER4 &getRawAPI() const;

    // Operations
    void bindFragDataLocation(ProgramName program, GLuint color,
                              const GLchar *name) const;
    GLint getFragDataLocation(ProgramName program, const GLchar *name) const;
    void getUniformUIV(ProgramName program, GLint location, GLuint *params) const;
    void getVertexAttribIIV(GLuint index, VertexAttribEnum pname, GLint *params) const;
    void getVertexAttribIUIV(GLuint index, VertexAttribEnum pname,
                             GLuint *params) const;
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

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTGPUSHADER4 _api;
};

// Manages the entry points for the GL_EXT_histogram extension API.
class EXTHistogramAPI : public BaseExtension
{
public:
    // Construction
    EXTHistogramAPI();

    // Accessors
    const EXTHistogram &getRawAPI() const;

    // Operations
    void getHistogram(HistogramTargetEXT target, Boolean reset,
                      PixelFormat format, PixelType type, void *values) const;
    void getHistogramParameterFV(HistogramTargetEXT target,
                                 GetHistogramParameterPNameEXT pname,
                                 GLfloat *params) const;
    void getHistogramParameterIV(HistogramTargetEXT target,
                                 GetHistogramParameterPNameEXT pname,
                                 GLint *params) const;
    void getMinmax(MinmaxTargetEXT target, Boolean reset, PixelFormat format,
                   PixelType type, void *values) const;
    void getMinmaxParameterFV(MinmaxTargetEXT target,
                              GetMinmaxParameterPNameEXT pname, GLfloat *params) const;
    void getMinmaxParameterIV(MinmaxTargetEXT target,
                              GetMinmaxParameterPNameEXT pname, GLint *params) const;
    void histogram(HistogramTargetEXT target, GLsizei width,
                   InternalFormat internalformat, Boolean sink) const;
    void minmax(MinmaxTargetEXT target, InternalFormat internalformat,
                Boolean sink) const;
    void resetHistogram(HistogramTargetEXT target) const;
    void resetMinmax(MinmaxTargetEXT target) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTHistogram _api;
};

// Manages the entry points for the GL_EXT_index_func extension API.
class EXTIndexFuncAPI : public BaseExtension
{
public:
    // Construction
    EXTIndexFuncAPI();

    // Accessors
    const EXTIndexFunc &getRawAPI() const;

    // Operations
    void indexFunc(IndexFunctionEXT func, GLclampf ref) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTIndexFunc _api;
};

// Manages the entry points for the GL_EXT_index_material extension API.
class EXTIndexMaterialAPI : public BaseExtension
{
public:
    // Construction
    EXTIndexMaterialAPI();

    // Accessors
    const EXTIndexMaterial &getRawAPI() const;

    // Operations
    void indexMaterial(MaterialFace face, GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTIndexMaterial _api;
};

// Manages the entry points for the GL_EXT_light_texture extension API.
class EXTLightTextureAPI : public BaseExtension
{
public:
    // Construction
    EXTLightTextureAPI();

    // Accessors
    const EXTLightTexture &getRawAPI() const;

    // Operations
    void applyTexture(LightTextureModeEXT mode) const;
    void textureLight(LightTexturePNameEXT pname) const;
    void textureMaterial(MaterialFace face, GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTLightTexture _api;
};

// Manages the entry points for the GL_EXT_memory_object extension API.
class EXTMemoryObjectAPI : public BaseExtension
{
public:
    // Construction
    EXTMemoryObjectAPI();

    // Accessors
    const EXTMemoryObject &getRawAPI() const;

    // Operations
    void bufferStorageMem(BufferTarget target, GLsizeiptr size, GLuint memory,
                          GLuint64 offset) const;
    void createMemoryObjects(GLsizei n, GLuint *memoryObjects) const;
    void deleteMemoryObjects(GLsizei n, const GLuint *memoryObjects) const;
    void getMemoryObjectParameterIV(GLuint memoryObject,
                                    MemoryObjectParameterName pname,
                                    GLint *params) const;
    void getUnsignedByteIV(GLenum target, GLuint index, GLubyte *data) const;
    void getUnsignedByteV(GetPName pname, GLubyte *data) const;
    Boolean isMemoryObject(GLuint memoryObject) const;
    void memoryObjectParameterIV(GLuint memoryObject,
                                 MemoryObjectParameterName pname,
                                 const GLint *params) const;
    void namedBufferStorageMem(BufferName buffer, GLsizeiptr size, GLuint memory,
                               GLuint64 offset) const;
    void texStorageMem1D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalFormat, GLsizei width,
                         GLuint memory, GLuint64 offset) const;
    void texStorageMem2D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalFormat, GLsizei width,
                         GLsizei height, GLuint memory, GLuint64 offset) const;
    void texStorageMem2DMultisample(TextureTarget target, GLsizei samples,
                                    SizedInternalFormat internalFormat,
                                    GLsizei width, GLsizei height,
                                    Boolean fixedSampleLocations, GLuint memory,
                                    GLuint64 offset) const;
    void texStorageMem3D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalFormat, GLsizei width,
                         GLsizei height, GLsizei depth, GLuint memory,
                         GLuint64 offset) const;
    void texStorageMem3DMultisample(TextureTarget target, GLsizei samples,
                                    SizedInternalFormat internalFormat,
                                    GLsizei width, GLsizei height, GLsizei depth,
                                    Boolean fixedSampleLocations, GLuint memory,
                                    GLuint64 offset) const;
    void textureStorageMem1D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalFormat, GLsizei width,
                             GLuint memory, GLuint64 offset) const;
    void textureStorageMem2D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalFormat, GLsizei width,
                             GLsizei height, GLuint memory, GLuint64 offset) const;
    void textureStorageMem2DMultisample(TextureName texture, GLsizei samples,
                                        SizedInternalFormat internalFormat,
                                        GLsizei width, GLsizei height,
                                        Boolean fixedSampleLocations,
                                        GLuint memory, GLuint64 offset) const;
    void textureStorageMem3D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalFormat, GLsizei width,
                             GLsizei height, GLsizei depth, GLuint memory,
                             GLuint64 offset) const;
    void textureStorageMem3DMultisample(TextureName texture, GLsizei samples,
                                        SizedInternalFormat internalFormat,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth,
                                        Boolean fixedSampleLocations,
                                        GLuint memory, GLuint64 offset) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMemoryObject _api;
};

// Manages the entry points for the GL_EXT_memory_object_fd extension API.
class EXTMemoryObjectFdAPI : public BaseExtension
{
public:
    // Construction
    EXTMemoryObjectFdAPI();

    // Accessors
    const EXTMemoryObjectFd &getRawAPI() const;

    // Operations
    void importMemoryFd(GLuint memory, GLuint64 size,
                        ExternalHandleType handleType, GLint fd) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMemoryObjectFd _api;
};

// Manages the entry points for the GL_EXT_memory_object_win32 extension API.
class EXTMemoryObjectWIN32API : public BaseExtension
{
public:
    // Construction
    EXTMemoryObjectWIN32API();

    // Accessors
    const EXTMemoryObjectWIN32 &getRawAPI() const;

    // Operations
    void importMemoryWIN32Handle(GLuint memory, GLuint64 size,
                                 ExternalHandleType handleType, void *handle) const;
    void importMemoryWIN32Name(GLuint memory, GLuint64 size,
                               ExternalHandleType handleType, const void *name) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMemoryObjectWIN32 _api;
};

// Manages the entry points for the GL_EXT_multi_draw_arrays extension API.
class EXTMultiDrawArraysAPI : public BaseExtension
{
public:
    // Construction
    EXTMultiDrawArraysAPI();

    // Accessors
    const EXTMultiDrawArrays &getRawAPI() const;

    // Operations
    void multiDrawArrays(PrimitiveType mode, const GLint *first,
                         const GLsizei *count, GLsizei primcount) const;
    void multiDrawElements(PrimitiveType mode, const GLsizei *count,
                           DrawElementsType type, const void *const *indices,
                           GLsizei primcount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMultiDrawArrays _api;
};

// Manages the entry points for the GL_EXT_multisample extension API.
class EXTMultisampleAPI : public BaseExtension
{
public:
    // Construction
    EXTMultisampleAPI();

    // Accessors
    const EXTMultisample &getRawAPI() const;

    // Operations
    void sampleMask(GLclampf value, Boolean invert) const;
    void samplePattern(SamplePatternEXT pattern) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMultisample _api;
};

// Manages the entry points for the GL_EXT_paletted_texture extension API.
class EXTPalettedTextureAPI : public BaseExtension
{
public:
    // Construction
    EXTPalettedTextureAPI();

    // Accessors
    const EXTPalettedTexture &getRawAPI() const;

    // Operations
    void colorTable(GLenum target, InternalFormat internalFormat, GLsizei width,
                    PixelFormat format, PixelType type, const void *table) const;
    void getColorTable(GLenum target, PixelFormat format, PixelType type,
                       void *data) const;
    void getColorTableParameterFV(GLenum target,
                                  GetColorTableParameterPNameSGI pname,
                                  GLfloat *params) const;
    void getColorTableParameterIV(GLenum target,
                                  GetColorTableParameterPNameSGI pname,
                                  GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPalettedTexture _api;
};

// Manages the entry points for the GL_EXT_pixel_transform extension API.
class EXTPixelTransformAPI : public BaseExtension
{
public:
    // Construction
    EXTPixelTransformAPI();

    // Accessors
    const EXTPixelTransform &getRawAPI() const;

    // Operations
    void getPixelTransformParameterFV(GLenum target, GLenum pname,
                                      GLfloat *params) const;
    void getPixelTransformParameterIV(GLenum target, GLenum pname, GLint *params) const;
    void pixelTransformParameterF(PixelTransformTargetEXT target,
                                  PixelTransformPNameEXT pname, GLfloat param) const;
    void pixelTransformParameterFV(PixelTransformTargetEXT target,
                                   PixelTransformPNameEXT pname,
                                   const GLfloat *params) const;
    void pixelTransformParameterI(PixelTransformTargetEXT target,
                                  PixelTransformPNameEXT pname, GLint param) const;
    void pixelTransformParameterIV(PixelTransformTargetEXT target,
                                   PixelTransformPNameEXT pname,
                                   const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPixelTransform _api;
};

// Manages the entry points for the GL_EXT_point_parameters extension API.
class EXTPointParametersAPI : public BaseExtension
{
public:
    // Construction
    EXTPointParametersAPI();

    // Accessors
    const EXTPointParameters &getRawAPI() const;

    // Operations
    void pointParameterF(PointParameterNameARB pname, GLfloat param) const;
    void pointParameterFV(PointParameterNameARB pname, const GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPointParameters _api;
};

// Manages the entry points for the GL_EXT_polygon_offset extension API.
class EXTPolygonOffsetAPI : public BaseExtension
{
public:
    // Construction
    EXTPolygonOffsetAPI();

    // Accessors
    const EXTPolygonOffset &getRawAPI() const;

    // Operations
    void polygonOffset(GLfloat factor, GLfloat bias) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPolygonOffset _api;
};

// Manages the entry points for the GL_EXT_polygon_offset_clamp extension API.
class EXTPolygonOffsetClampAPI : public BaseExtension
{
public:
    // Construction
    EXTPolygonOffsetClampAPI();

    // Accessors
    const EXTPolygonOffsetClamp &getRawAPI() const;

    // Operations
    void polygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPolygonOffsetClamp _api;
};

// Manages the entry points for the GL_EXT_provoking_vertex extension API.
class EXTProvokingVertexAPI : public BaseExtension
{
public:
    // Construction
    EXTProvokingVertexAPI();

    // Accessors
    const EXTProvokingVertex &getRawAPI() const;

    // Operations
    void provokingVertex(VertexProvokingMode mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTProvokingVertex _api;
};

// Manages the entry points for the GL_EXT_raster_multisample extension API.
class EXTRasterMultisampleAPI : public BaseExtension
{
public:
    // Construction
    EXTRasterMultisampleAPI();

    // Accessors
    const EXTRasterMultisample &getRawAPI() const;

    // Operations
    void rasterSamples(GLuint samples, Boolean fixedsamplelocations) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTRasterMultisample _api;
};

// Manages the entry points for the GL_EXT_secondary_color extension API.
class EXTSecondaryColorAPI : public BaseExtension
{
public:
    // Construction
    EXTSecondaryColorAPI();

    // Accessors
    const EXTSecondaryColor &getRawAPI() const;

    // Operations
    void secondaryColor3B(GLbyte red, GLbyte green, GLbyte blue) const;
    void secondaryColor3BV(const GLbyte *v) const;
    void secondaryColor3D(GLdouble red, GLdouble green, GLdouble blue) const;
    void secondaryColor3DV(const GLdouble *v) const;
    void secondaryColor3F(GLfloat red, GLfloat green, GLfloat blue) const;
    void secondaryColor3FV(const GLfloat *v) const;
    void secondaryColor3I(GLint red, GLint green, GLint blue) const;
    void secondaryColor3IV(const GLint *v) const;
    void secondaryColor3S(GLshort red, GLshort green, GLshort blue) const;
    void secondaryColor3SV(const GLshort *v) const;
    void secondaryColor3UB(GLubyte red, GLubyte green, GLubyte blue) const;
    void secondaryColor3UBV(const GLubyte *v) const;
    void secondaryColor3UI(GLuint red, GLuint green, GLuint blue) const;
    void secondaryColor3UIV(const GLuint *v) const;
    void secondaryColor3US(GLushort red, GLushort green, GLushort blue) const;
    void secondaryColor3USV(const GLushort *v) const;
    void secondaryColorPointer(GLint size, ColorPointerType type, GLsizei stride,
                               const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSecondaryColor _api;
};

// Manages the entry points for the GL_EXT_semaphore extension API.
class EXTSemaphoreAPI : public BaseExtension
{
public:
    // Construction
    EXTSemaphoreAPI();

    // Accessors
    const EXTSemaphore &getRawAPI() const;

    // Operations
    void deleteSemaphores(GLsizei n, const GLuint *semaphores) const;
    void genSemaphores(GLsizei n, GLuint *semaphores) const;
    void getSemaphoreParameterUI64(GLuint semaphore,
                                   SemaphoreParameterName pname,
                                   GLuint64 *params) const;
    Boolean isSemaphore(GLuint semaphore) const;
    void semaphoreParameterUI64(GLuint semaphore, SemaphoreParameterName pname,
                                const GLuint64 *params) const;
    void signalSemaphore(GLuint semaphore, GLuint numBufferBarriers,
                         const BufferName *buffers, GLuint numTextureBarriers,
                         const TextureName *textures,
                         const TextureLayout *dstLayouts) const;
    void waitSemaphore(GLuint semaphore, GLuint numBufferBarriers,
                       const BufferName *buffers, GLuint numTextureBarriers,
                       const TextureName *textures,
                       const TextureLayout *srcLayouts) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSemaphore _api;
};

// Manages the entry points for the GL_EXT_semaphore_fd extension API.
class EXTSemaphoreFdAPI : public BaseExtension
{
public:
    // Construction
    EXTSemaphoreFdAPI();

    // Accessors
    const EXTSemaphoreFd &getRawAPI() const;

    // Operations
    void importSemaphoreFd(GLuint semaphore, ExternalHandleType handleType,
                           GLint fd) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSemaphoreFd _api;
};

// Manages the entry points for the GL_EXT_semaphore_win32 extension API.
class EXTSemaphoreWIN32API : public BaseExtension
{
public:
    // Construction
    EXTSemaphoreWIN32API();

    // Accessors
    const EXTSemaphoreWIN32 &getRawAPI() const;

    // Operations
    void importSemaphoreWIN32Handle(GLuint semaphore,
                                    ExternalHandleType handleType, void *handle) const;
    void importSemaphoreWIN32Name(GLuint semaphore,
                                  ExternalHandleType handleType,
                                  const void *name) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSemaphoreWIN32 _api;
};

// Manages the entry points for the GL_EXT_separate_shader_objects extension API.
class EXTSeparateShaderObjectsAPI : public BaseExtension
{
public:
    // Construction
    EXTSeparateShaderObjectsAPI();

    // Accessors
    const EXTSeparateShaderObjects &getRawAPI() const;

    // Operations
    void activeProgram(ProgramName program) const;
    ProgramName createShaderProgram(ShaderType type, const GLchar *string) const;
    void useShaderProgram(GLenum type, ProgramName program) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSeparateShaderObjects _api;
};

// Manages the entry points for the GL_EXT_shader_framebuffer_fetch_non_coherent extension API.
class EXTShaderFramebufferFetchNonCoherentAPI : public BaseExtension
{
public:
    // Construction
    EXTShaderFramebufferFetchNonCoherentAPI();

    // Accessors
    const EXTShaderFramebufferFetchNonCoherent &getRawAPI() const;

    // Operations
    void framebufferFetchBarrier() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTShaderFramebufferFetchNonCoherent _api;
};

// Manages the entry points for the GL_EXT_shader_image_load_store extension API.
class EXTShaderImageLoadStoreAPI : public BaseExtension
{
public:
    // Construction
    EXTShaderImageLoadStoreAPI();

    // Accessors
    const EXTShaderImageLoadStore &getRawAPI() const;

    // Operations
    void bindImageTexture(GLuint index, TextureName texture, GLint level,
                          Boolean layered, GLint layer, BufferAccess access,
                          GLint format) const;
    void memoryBarrier(GLbitfield  /* MemoryBarrierMask */ barriers) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTShaderImageLoadStore _api;
};

// Manages the entry points for the GL_EXT_stencil_clear_tag extension API.
class EXTStencilClearTagAPI : public BaseExtension
{
public:
    // Construction
    EXTStencilClearTagAPI();

    // Accessors
    const EXTStencilClearTag &getRawAPI() const;

    // Operations
    void stencilClearTag(GLsizei stencilTagBits, GLuint stencilClearTag) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTStencilClearTag _api;
};

// Manages the entry points for the GL_EXT_stencil_two_side extension API.
class EXTStencilTwoSideAPI : public BaseExtension
{
public:
    // Construction
    EXTStencilTwoSideAPI();

    // Accessors
    const EXTStencilTwoSide &getRawAPI() const;

    // Operations
    void activeStencilFace(StencilFaceDirection face) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTStencilTwoSide _api;
};

// Manages the entry points for the GL_EXT_subtexture extension API.
class EXTSubtextureAPI : public BaseExtension
{
public:
    // Construction
    EXTSubtextureAPI();

    // Accessors
    const EXTSubtexture &getRawAPI() const;

    // Operations
    void texSubImage1D(TextureTarget target, GLint level, GLint xoffset,
                       GLsizei width, PixelFormat format, PixelType type,
                       const void *pixels) const;
    void texSubImage2D(TextureTarget target, GLint level, GLint xoffset,
                       GLint yoffset, GLsizei width, GLsizei height,
                       PixelFormat format, PixelType type, const void *pixels) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSubtexture _api;
};

// Manages the entry points for the GL_EXT_texture3D extension API.
class EXTTEXTURE3DAPI : public BaseExtension
{
public:
    // Construction
    EXTTEXTURE3DAPI();

    // Accessors
    const EXTTEXTURE3D &getRawAPI() const;

    // Operations
    void texImage3D(TextureTarget target, GLint level,
                    InternalFormat internalformat, GLsizei width, GLsizei height,
                    GLsizei depth, GLint border, PixelFormat format,
                    PixelType type, const void *pixels) const;
    void texSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                       GLint yoffset, GLint zoffset, GLsizei width,
                       GLsizei height, GLsizei depth, PixelFormat format,
                       PixelType type, const void *pixels) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTEXTURE3D _api;
};

// Manages the entry points for the GL_EXT_texture_array extension API.
class EXTTextureArrayAPI : public BaseExtension
{
public:
    // Construction
    EXTTextureArrayAPI();

    // Accessors
    const EXTTextureArray &getRawAPI() const;

    // Operations
    void framebufferTextureLayer(FrameBufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureName texture, GLint level, GLint layer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureArray _api;
};

// Manages the entry points for the GL_EXT_texture_buffer_object extension API.
class EXTTextureBufferObjectAPI : public BaseExtension
{
public:
    // Construction
    EXTTextureBufferObjectAPI();

    // Accessors
    const EXTTextureBufferObject &getRawAPI() const;

    // Operations
    void texBuffer(TextureTarget target, SizedInternalFormat internalformat,
                   BufferName buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureBufferObject _api;
};

// Manages the entry points for the GL_EXT_texture_integer extension API.
class EXTTextureIntegerAPI : public BaseExtension
{
public:
    // Construction
    EXTTextureIntegerAPI();

    // Accessors
    const EXTTextureInteger &getRawAPI() const;

    // Operations
    void clearColorII(GLint red, GLint green, GLint blue, GLint alpha) const;
    void clearColorIUI(GLuint red, GLuint green, GLuint blue, GLuint alpha) const;
    void getTexParameterIIV(TextureTarget target, GetTextureParameter pname,
                            GLint *params) const;
    void getTexParameterIUIV(TextureTarget target, GetTextureParameter pname,
                             GLuint *params) const;
    void texParameterIIV(TextureTarget target, TextureParameterName pname,
                         const GLint *params) const;
    void texParameterIUIV(TextureTarget target, TextureParameterName pname,
                          const GLuint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureInteger _api;
};

// Manages the entry points for the GL_EXT_texture_object extension API.
class EXTTextureObjectAPI : public BaseExtension
{
public:
    // Construction
    EXTTextureObjectAPI();

    // Accessors
    const EXTTextureObject &getRawAPI() const;

    // Operations
    Boolean areTexturesResident(GLsizei n, const TextureName *textures,
                                Boolean *residences) const;
    void bindTexture(TextureTarget target, TextureName texture) const;
    void deleteTextures(GLsizei n, const TextureName *textures) const;
    void genTextures(GLsizei n, TextureName *textures) const;
    Boolean isTexture(TextureName texture) const;
    void prioritizeTextures(GLsizei n, const TextureName *textures,
                            const GLclampf *priorities) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureObject _api;
};

// Manages the entry points for the GL_EXT_texture_perturb_normal extension API.
class EXTTexturePerturbNormalAPI : public BaseExtension
{
public:
    // Construction
    EXTTexturePerturbNormalAPI();

    // Accessors
    const EXTTexturePerturbNormal &getRawAPI() const;

    // Operations
    void textureNormal(TextureNormalModeEXT mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTexturePerturbNormal _api;
};

// Manages the entry points for the GL_EXT_texture_storage extension API.
class EXTTextureStorageAPI : public BaseExtension
{
public:
    // Construction
    EXTTextureStorageAPI();

    // Accessors
    const EXTTextureStorage &getRawAPI() const;

    // Operations
    void texStorage1D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width) const;
    void texStorage2D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width,
                      GLsizei height) const;
    void texStorage3D(TextureTarget target, GLsizei levels,
                      SizedInternalFormat internalformat, GLsizei width,
                      GLsizei height, GLsizei depth) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureStorage _api;
};

// Manages the entry points for the GL_EXT_timer_query extension API.
class EXTTimerQueryAPI : public BaseExtension
{
public:
    // Construction
    EXTTimerQueryAPI();

    // Accessors
    const EXTTimerQuery &getRawAPI() const;

    // Operations
    void getQueryObjectI64V(QueryName id, QueryObjectParameterName pname,
                            GLint64 *params) const;
    void getQueryObjectUI64(QueryName id, QueryObjectParameterName pname,
                            GLuint64 *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTimerQuery _api;
};

// Manages the entry points for the GL_EXT_transform_feedback extension API.
class EXTTransformFeedbackAPI : public BaseExtension
{
public:
    // Construction
    EXTTransformFeedbackAPI();

    // Accessors
    const EXTTransformFeedback &getRawAPI() const;

    // Operations
    void beginTransformFeedback(PrimitiveType primitiveMode) const;
    void bindBufferBase(BufferTarget target, GLuint index, BufferName buffer) const;
    void bindBufferOffset(BufferTarget target, GLuint index,
                          BufferName buffer, GLintptr offset) const;
    void bindBufferRange(BufferTarget target, GLuint index, BufferName buffer,
                         GLintptr offset, GLsizeiptr size) const;
    void endTransformFeedback() const;
    void getTransformFeedbackVarying(ProgramName program, GLuint index,
                                     GLsizei bufSize, GLsizei *length,
                                     GLsizei *size, AttributeType *type,
                                     GLchar *name) const;
    void transformFeedbackVaryings(ProgramName program, GLsizei count,
                                   const GLchar *const *varyings,
                                   GLenum bufferMode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTransformFeedback _api;
};

// Manages the entry points for the GL_EXT_vertex_array extension API.
class EXTVertexArrayAPI : public BaseExtension
{
public:
    // Construction
    EXTVertexArrayAPI();

    // Accessors
    const EXTVertexArray &getRawAPI() const;

    // Operations
    void arrayElement(GLint i) const;
    void colorPointer(GLint size, ColorPointerType type, GLsizei stride,
                      GLsizei count, const void *pointer) const;
    void drawArrays(PrimitiveType mode, GLint first, GLsizei count) const;
    void edgeFlagPointer(GLsizei stride, GLsizei count, const Boolean *pointer) const;
    void getPointerV(GetPointervPName pname, void **params) const;
    void indexPointer(IndexPointerType type, GLsizei stride, GLsizei count,
                      const void *pointer) const;
    void normalPointer(NormalPointerType type, GLsizei stride, GLsizei count,
                       const void *pointer) const;
    void texCoordPointer(GLint size, TexCoordPointerType type, GLsizei stride,
                         GLsizei count, const void *pointer) const;
    void vertexPointer(GLint size, VertexPointerType type, GLsizei stride,
                       GLsizei count, const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTVertexArray _api;
};

// Manages the entry points for the GL_EXT_vertex_attrib_64bit extension API.
class EXTVertexAttrib64BITAPI : public BaseExtension
{
public:
    // Construction
    EXTVertexAttrib64BITAPI();

    // Accessors
    const EXTVertexAttrib64BIT &getRawAPI() const;

    // Operations
    void getVertexAttribLDV(GLuint index, VertexAttribEnum pname,
                            GLdouble *params) const;
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

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTVertexAttrib64BIT _api;
};

// Manages the entry points for the GL_EXT_vertex_shader extension API.
class EXTVertexShaderAPI : public BaseExtension
{
public:
    // Construction
    EXTVertexShaderAPI();

    // Accessors
    const EXTVertexShader &getRawAPI() const;

    // Operations
    void beginVertexShader() const;
    GLuint bindLightParameter(LightName light, GLenum value) const;
    GLuint bindMaterialParameter(MaterialFace face, GLenum value) const;
    GLuint bindParameter(VertexShaderParameterEXT value) const;
    GLuint bindTexGenParameter(TextureUnit unit, GLenum coord,
                               TextureGenParameter value) const;
    GLuint bindTextureUnitParameter(TextureUnit unit, GLenum value) const;
    void bindVertexShader(GLuint id) const;
    void deleteVertexShader(GLuint id) const;
    void disableVariantClientState(GLuint id) const;
    void enableVariantClientState(GLuint id) const;
    void endVertexShader() const;
    void extractComponent(GLuint res, GLuint src, GLuint num) const;
    GLuint genSymbols(DataTypeEXT datatype,
                      VertexShaderStorageTypeEXT storagetype,
                      ParameterRangeEXT range, GLuint components) const;
    GLuint genVertexShaders(GLuint range) const;
    void getInvariantBooleanV(GLuint id, GetVariantValueEXT value, Boolean *data) const;
    void getInvariantFloatV(GLuint id, GetVariantValueEXT value, GLfloat *data) const;
    void getInvariantIntegerV(GLuint id, GetVariantValueEXT value, GLint *data) const;
    void getLocalConstantBooleanV(GLuint id, GetVariantValueEXT value,
                                  Boolean *data) const;
    void getLocalConstantFloatV(GLuint id, GetVariantValueEXT value,
                                GLfloat *data) const;
    void getLocalConstantIntegerV(GLuint id, GetVariantValueEXT value,
                                  GLint *data) const;
    void getVariantBooleanV(GLuint id, GetVariantValueEXT value, Boolean *data) const;
    void getVariantFloatV(GLuint id, GetVariantValueEXT value, GLfloat *data) const;
    void getVariantIntegerV(GLuint id, GetVariantValueEXT value, GLint *data) const;
    void getVariantPointerV(GLuint id, GetVariantValueEXT value, void **data) const;
    void insertComponent(GLuint res, GLuint src, GLuint num) const;
    Boolean isVariantEnabled(GLuint id, VariantCapEXT cap) const;
    void setInvariant(GLuint id, ScalarType type, const void *addr) const;
    void setLocalConstant(GLuint id, ScalarType type, const void *addr) const;
    void shaderOp1(VertexShaderOpEXT op, GLuint res, GLuint arg1) const;
    void shaderOp2(VertexShaderOpEXT op, GLuint res, GLuint arg1, GLuint arg2) const;
    void shaderOp3(VertexShaderOpEXT op, GLuint res, GLuint arg1, GLuint arg2,
                   GLuint arg3) const;
    void swizzle(GLuint res, GLuint in, VertexShaderCoordOutEXT outX,
                 VertexShaderCoordOutEXT outY, VertexShaderCoordOutEXT outZ,
                 VertexShaderCoordOutEXT outW) const;
    void variantPointer(GLuint id, ScalarType type, GLuint stride,
                        const void *addr) const;
    void variantBV(GLuint id, const GLbyte *addr) const;
    void variantDV(GLuint id, const GLdouble *addr) const;
    void variantFV(GLuint id, const GLfloat *addr) const;
    void variantIV(GLuint id, const GLint *addr) const;
    void variantSV(GLuint id, const GLshort *addr) const;
    void variantUBV(GLuint id, const GLubyte *addr) const;
    void variantUIV(GLuint id, const GLuint *addr) const;
    void variantUSV(GLuint id, const GLushort *addr) const;
    void writeMask(GLuint res, GLuint in, VertexShaderWriteMaskEXT outX,
                   VertexShaderWriteMaskEXT outY, VertexShaderWriteMaskEXT outZ,
                   VertexShaderWriteMaskEXT outW) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTVertexShader _api;
};

// Manages the entry points for the GL_EXT_vertex_weighting extension API.
class EXTVertexWeightingAPI : public BaseExtension
{
public:
    // Construction
    EXTVertexWeightingAPI();

    // Accessors
    const EXTVertexWeighting &getRawAPI() const;

    // Operations
    void vertexWeightPointer(GLint size, VertexWeightPointerTypeEXT type,
                             GLsizei stride, const void *pointer) const;
    void vertexWeightF(GLfloat weight) const;
    void vertexWeightFV(const GLfloat *weight) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTVertexWeighting _api;
};

// Manages the entry points for the GL_EXT_win32_keyed_mutex extension API.
class EXTWIN32KeyedMutexAPI : public BaseExtension
{
public:
    // Construction
    EXTWIN32KeyedMutexAPI();

    // Accessors
    const EXTWIN32KeyedMutex &getRawAPI() const;

    // Operations
    Boolean acquireKeyedMutexWIN32(GLuint memory, GLuint64 key, GLuint timeout) const;
    Boolean releaseKeyedMutexWIN32(GLuint memory, GLuint64 key) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTWIN32KeyedMutex _api;
};

// Manages the entry points for the GL_EXT_window_rectangles extension API.
class EXTWindowRectanglesAPI : public BaseExtension
{
public:
    // Construction
    EXTWindowRectanglesAPI();

    // Accessors
    const EXTWindowRectangles &getRawAPI() const;

    // Operations
    void windowRectangles(GLenum mode, GLsizei count, const GLint *box) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTWindowRectangles _api;
};

// Manages the entry points for the GL_EXT_x11_sync_object extension API.
class EXTX11SyncObjectAPI : public BaseExtension
{
public:
    // Construction
    EXTX11SyncObjectAPI();

    // Accessors
    const EXTX11SyncObject &getRawAPI() const;

    // Operations
    SyncName importSync(GLenum external_sync_type, GLintptr external_sync,
                        GLbitfield flags) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTX11SyncObject _api;
};

} // namespace gl

#ifdef _WIN32
namespace wgl {

// Manages the entry points for the WGL_EXT_display_color_table extension API.
class EXTDisplayColorTableAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTDisplayColorTableAPI();

    // Accessors
    const EXTDisplayColorTable &getRawAPI() const;

    // Operations
    GLboolean bindDisplayColorTable(GLushort id) const;
    GLboolean createDisplayColorTable(GLushort id) const;
    VOID destroyDisplayColorTable(GLushort id) const;
    GLboolean loadDisplayColorTable(const GLushort *table, GLuint length) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTDisplayColorTable _api;
};

// Manages the entry points for the WGL_EXT_extensions_string extension API.
class EXTExtensionsStringAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTExtensionsStringAPI();

    // Accessors
    const EXTExtensionsString &getRawAPI() const;

    // Operations
    const char *getExtensionsString() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTExtensionsString _api;
};

// Manages the entry points for the WGL_EXT_make_current_read extension API.
class EXTMakeCurrentReadAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTMakeCurrentReadAPI();

    // Accessors
    const EXTMakeCurrentRead &getRawAPI() const;

    // Operations
    HDC getCurrentReadDC() const;
    BOOL makeContextCurrent(HDC hDrawDC, HDC hReadDC, HGLRC hglrc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTMakeCurrentRead _api;
};

// Manages the entry points for the WGL_EXT_pbuffer extension API.
class EXTPbufferAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTPbufferAPI();

    // Accessors
    const EXTPbuffer &getRawAPI() const;

    // Operations
    HPBUFFEREXT createPbuffer(HDC hDC, int iPixelFormat, int iWidth, int iHeight,
                              const int *piAttribList) const;
    BOOL destroyPbuffer(HPBUFFEREXT hPbuffer) const;
    HDC getPbufferDC(HPBUFFEREXT hPbuffer) const;
    BOOL queryPbuffer(HPBUFFEREXT hPbuffer, int iAttribute, int *piValue) const;
    int releasePbufferDC(HPBUFFEREXT hPbuffer, HDC hDC) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPbuffer _api;
};

// Manages the entry points for the WGL_EXT_pixel_format extension API.
class EXTPixelFormatAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTPixelFormatAPI();

    // Accessors
    const EXTPixelFormat &getRawAPI() const;

    // Operations
    BOOL choosePixelFormat(HDC hdc, const int *piAttribIList,
                           const FLOAT *pfAttribFList, UINT nMaxFormats,
                           int *piFormats, UINT *nNumFormats) const;
    BOOL getPixelFormatAttribFV(HDC hdc, int iPixelFormat, int iLayerPlane,
                                UINT nAttributes, int *piAttributes,
                                FLOAT *pfValues) const;
    BOOL getPixelFormatAttribIV(HDC hdc, int iPixelFormat, int iLayerPlane,
                                UINT nAttributes, int *piAttributes,
                                int *piValues) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTPixelFormat _api;
};

// Manages the entry points for the WGL_EXT_swap_control extension API.
class EXTSwapControlAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTSwapControlAPI();

    // Accessors
    const EXTSwapControl &getRawAPI() const;

    // Operations
    int getSwapInterval() const;
    BOOL swapInterval(int interval) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSwapControl _api;
};

} // namespace wgl
#endif // ifdef _WIN32
#endif // Header guard

#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_EXT_import_context extension API.
class EXTImportContextAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTImportContextAPI();

    // Accessors
    const EXTImportContext &getRawAPI() const;

    // Operations
    void xFreeContext(Display *dpy, GLXContext context) const;
    GLXContextID xGetContextId(const GLXContext context) const;
    Display *xGetCurrentDisplay() const;
    GLXContext xImportContext(Display *dpy, GLXContextID contextID) const;
    int xQueryContextInfo(Display *dpy, GLXContext context, int attribute,
                          int *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTImportContext _api;
};

// Manages the entry points for the GLX_EXT_swap_control extension API.
class EXTSwapControlAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTSwapControlAPI();

    // Accessors
    const EXTSwapControl &getRawAPI() const;

    // Operations
    void xSwapInterval(Display *dpy, GLXDrawable drawable, int interval) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTSwapControl _api;
};

// Manages the entry points for the GLX_EXT_texture_from_pixmap extension API.
class EXTTextureFromPixmapAPI : public gl::BaseExtension
{
public:
    // Construction
    EXTTextureFromPixmapAPI();

    // Accessors
    const EXTTextureFromPixmap &getRawAPI() const;

    // Operations
    void xBindTexImage(Display *dpy, GLXDrawable drawable, int buffer,
                       const int *attrib_list) const;
    void xReleaseTexImage(Display *dpy, GLXDrawable drawable, int buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    EXTTextureFromPixmap _api;
};

} // namespace glx
#endif // ifdef _USES_GLX

////////////////////////////////////////////////////////////////////////////////
