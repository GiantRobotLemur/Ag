//! @file ObjectGL/CommandSets.cpp
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

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CommandSetTools.hpp"
#include "Ag/ObjectGL/CommandSets.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// GLAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Constructs an unresolved command set for the core API.
GLAPI::GLAPI()
{
}

// Grant read-only access to the underlying function pointers.
const GL &GLAPI::getRawAPI() const
{
    return _api;
}

// Resolve core API entry points.
void GLAPI::resolve(const APIResolver* resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseAPI::resolve(resolver);
    }
}

// Calls glBlendFunc().
void GLAPI::blendFunc(BlendingFactor sfactor, BlendingFactor dfactor) const
{
    static const char *fnName = "glBlendFunc";

    beforeCommand(fnName, _api.glBlendFunc);
    _api.glBlendFunc(toScalar(sfactor), toScalar(dfactor));
    afterCommand(fnName);
}

// Calls glClear().
void GLAPI::clear(GLbitfield  /* ClearBufferMask */ mask) const
{
    static const char *fnName = "glClear";

    beforeCommand(fnName, _api.glClear);
    _api.glClear(mask);
    afterCommand(fnName);
}

// Calls glClearColor().
void GLAPI::clearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const
{
    static const char *fnName = "glClearColor";

    beforeCommand(fnName, _api.glClearColor);
    _api.glClearColor(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glClearDepth().
void GLAPI::clearDepth(GLdouble depth) const
{
    static const char *fnName = "glClearDepth";

    beforeCommand(fnName, _api.glClearDepth);
    _api.glClearDepth(depth);
    afterCommand(fnName);
}

// Calls glClearStencil().
void GLAPI::clearStencil(GLint s) const
{
    static const char *fnName = "glClearStencil";

    beforeCommand(fnName, _api.glClearStencil);
    _api.glClearStencil(s);
    afterCommand(fnName);
}

// Calls glColorMask().
void GLAPI::colorMask(Boolean red, Boolean green, Boolean blue, Boolean alpha) const
{
    static const char *fnName = "glColorMask";

    beforeCommand(fnName, _api.glColorMask);
    _api.glColorMask(toScalar(red), toScalar(green), toScalar(blue),
                     toScalar(alpha));
    afterCommand(fnName);
}

// Calls glCullFace().
void GLAPI::cullFace(CullFaceMode mode) const
{
    static const char *fnName = "glCullFace";

    beforeCommand(fnName, _api.glCullFace);
    _api.glCullFace(toScalar(mode));
    afterCommand(fnName);
}

// Calls glDepthFunc().
void GLAPI::depthFunc(DepthFunction func) const
{
    static const char *fnName = "glDepthFunc";

    beforeCommand(fnName, _api.glDepthFunc);
    _api.glDepthFunc(toScalar(func));
    afterCommand(fnName);
}

// Calls glDepthMask().
void GLAPI::depthMask(Boolean flag) const
{
    static const char *fnName = "glDepthMask";

    beforeCommand(fnName, _api.glDepthMask);
    _api.glDepthMask(toScalar(flag));
    afterCommand(fnName);
}

// Calls glDepthRange().
void GLAPI::depthRange(GLdouble n, GLdouble f) const
{
    static const char *fnName = "glDepthRange";

    beforeCommand(fnName, _api.glDepthRange);
    _api.glDepthRange(n, f);
    afterCommand(fnName);
}

// Calls glDisable().
void GLAPI::disable(EnableCap cap) const
{
    static const char *fnName = "glDisable";

    beforeCommand(fnName, _api.glDisable);
    _api.glDisable(toScalar(cap));
    afterCommand(fnName);
}

// Calls glDrawBuffer().
void GLAPI::drawBuffer(DrawBufferMode buf) const
{
    static const char *fnName = "glDrawBuffer";

    beforeCommand(fnName, _api.glDrawBuffer);
    _api.glDrawBuffer(toScalar(buf));
    afterCommand(fnName);
}

// Calls glEnable().
void GLAPI::enable(EnableCap cap) const
{
    static const char *fnName = "glEnable";

    beforeCommand(fnName, _api.glEnable);
    _api.glEnable(toScalar(cap));
    afterCommand(fnName);
}

// Calls glFinish().
void GLAPI::finish() const
{
    static const char *fnName = "glFinish";

    beforeCommand(fnName, _api.glFinish);
    _api.glFinish();
    afterCommand(fnName);
}

// Calls glFlush().
void GLAPI::flush() const
{
    static const char *fnName = "glFlush";

    beforeCommand(fnName, _api.glFlush);
    _api.glFlush();
    afterCommand(fnName);
}

// Calls glFrontFace().
void GLAPI::frontFace(FrontFaceDirection mode) const
{
    static const char *fnName = "glFrontFace";

    beforeCommand(fnName, _api.glFrontFace);
    _api.glFrontFace(toScalar(mode));
    afterCommand(fnName);
}

// Calls glGetBooleanv().
void GLAPI::getBooleanV(GetPName pname, Boolean *data) const
{
    static const char *fnName = "glGetBooleanv";

    beforeCommand(fnName, _api.glGetBooleanv);
    _api.glGetBooleanv(toScalar(pname), toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetDoublev().
void GLAPI::getDoubleV(GetPName pname, GLdouble *data) const
{
    static const char *fnName = "glGetDoublev";

    beforeCommand(fnName, _api.glGetDoublev);
    _api.glGetDoublev(toScalar(pname), data);
    afterCommand(fnName);
}

// Calls glGetError().
ErrorCode GLAPI::getError() const
{
    static const char *fnName = "glGetError";

    beforeCommand(fnName, _api.glGetError);
    GLenum result = _api.glGetError();
    afterCommand(fnName);

    return static_cast<ErrorCode>(result);
}

// Calls glGetFloatv().
void GLAPI::getFloatV(GetPName pname, GLfloat *data) const
{
    static const char *fnName = "glGetFloatv";

    beforeCommand(fnName, _api.glGetFloatv);
    _api.glGetFloatv(toScalar(pname), data);
    afterCommand(fnName);
}

// Calls glGetIntegerv().
void GLAPI::getIntegerV(GetPName pname, GLint *data) const
{
    static const char *fnName = "glGetIntegerv";

    beforeCommand(fnName, _api.glGetIntegerv);
    _api.glGetIntegerv(toScalar(pname), data);
    afterCommand(fnName);
}

// Calls glGetString().
const GLubyte *GLAPI::getString(StringName name) const
{
    static const char *fnName = "glGetString";

    beforeCommand(fnName, _api.glGetString);
    const GLubyte *result = _api.glGetString(toScalar(name));
    afterCommand(fnName);

    return result;
}

// Calls glGetTexImage().
void GLAPI::getTexImage(TextureTarget target, GLint level, PixelFormat format,
                        PixelType type, void *pixels) const
{
    static const char *fnName = "glGetTexImage";

    beforeCommand(fnName, _api.glGetTexImage);
    _api.glGetTexImage(toScalar(target), level, toScalar(format), toScalar(type),
                       pixels);
    afterCommand(fnName);
}

// Calls glGetTexLevelParameterfv().
void GLAPI::getTexLevelParameterFV(TextureTarget target, GLint level,
                                   GetTextureParameter pname, GLfloat *params) const
{
    static const char *fnName = "glGetTexLevelParameterfv";

    beforeCommand(fnName, _api.glGetTexLevelParameterfv);
    _api.glGetTexLevelParameterfv(toScalar(target), level, toScalar(pname),
                                  params);
    afterCommand(fnName);
}

// Calls glGetTexLevelParameteriv().
void GLAPI::getTexLevelParameterIV(TextureTarget target, GLint level,
                                   GetTextureParameter pname, GLint *params) const
{
    static const char *fnName = "glGetTexLevelParameteriv";

    beforeCommand(fnName, _api.glGetTexLevelParameteriv);
    _api.glGetTexLevelParameteriv(toScalar(target), level, toScalar(pname),
                                  params);
    afterCommand(fnName);
}

// Calls glGetTexParameterfv().
void GLAPI::getTexParameterFV(TextureTarget target, GetTextureParameter pname,
                              GLfloat *params) const
{
    static const char *fnName = "glGetTexParameterfv";

    beforeCommand(fnName, _api.glGetTexParameterfv);
    _api.glGetTexParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTexParameteriv().
void GLAPI::getTexParameterIV(TextureTarget target, GetTextureParameter pname,
                              GLint *params) const
{
    static const char *fnName = "glGetTexParameteriv";

    beforeCommand(fnName, _api.glGetTexParameteriv);
    _api.glGetTexParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glHint().
void GLAPI::hint(HintTarget target, HintMode mode) const
{
    static const char *fnName = "glHint";

    beforeCommand(fnName, _api.glHint);
    _api.glHint(toScalar(target), toScalar(mode));
    afterCommand(fnName);
}

// Calls glIsEnabled().
Boolean GLAPI::isEnabled(EnableCap cap) const
{
    static const char *fnName = "glIsEnabled";

    beforeCommand(fnName, _api.glIsEnabled);
    GLboolean result = _api.glIsEnabled(toScalar(cap));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glLineWidth().
void GLAPI::lineWidth(GLfloat width) const
{
    static const char *fnName = "glLineWidth";

    beforeCommand(fnName, _api.glLineWidth);
    _api.glLineWidth(width);
    afterCommand(fnName);
}

// Calls glLogicOp().
void GLAPI::logicOp(LogicOp opcode) const
{
    static const char *fnName = "glLogicOp";

    beforeCommand(fnName, _api.glLogicOp);
    _api.glLogicOp(toScalar(opcode));
    afterCommand(fnName);
}

// Calls glPixelStoref().
void GLAPI::pixelStoreF(PixelStoreParameter pname, GLfloat param) const
{
    static const char *fnName = "glPixelStoref";

    beforeCommand(fnName, _api.glPixelStoref);
    _api.glPixelStoref(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelStorei().
void GLAPI::pixelStoreI(PixelStoreParameter pname, GLint param) const
{
    static const char *fnName = "glPixelStorei";

    beforeCommand(fnName, _api.glPixelStorei);
    _api.glPixelStorei(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointSize().
void GLAPI::pointSize(GLfloat size) const
{
    static const char *fnName = "glPointSize";

    beforeCommand(fnName, _api.glPointSize);
    _api.glPointSize(size);
    afterCommand(fnName);
}

// Calls glPolygonMode().
void GLAPI::polygonMode(MaterialFace face, PolygonMode mode) const
{
    static const char *fnName = "glPolygonMode";

    beforeCommand(fnName, _api.glPolygonMode);
    _api.glPolygonMode(toScalar(face), toScalar(mode));
    afterCommand(fnName);
}

// Calls glReadBuffer().
void GLAPI::readBuffer(ReadBufferMode src) const
{
    static const char *fnName = "glReadBuffer";

    beforeCommand(fnName, _api.glReadBuffer);
    _api.glReadBuffer(toScalar(src));
    afterCommand(fnName);
}

// Calls glReadPixels().
void GLAPI::readPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                       PixelFormat format, PixelType type, void *pixels) const
{
    static const char *fnName = "glReadPixels";

    beforeCommand(fnName, _api.glReadPixels);
    _api.glReadPixels(x, y, width, height, toScalar(format), toScalar(type),
                      pixels);
    afterCommand(fnName);
}

// Calls glScissor().
void GLAPI::scissor(GLint x, GLint y, GLsizei width, GLsizei height) const
{
    static const char *fnName = "glScissor";

    beforeCommand(fnName, _api.glScissor);
    _api.glScissor(x, y, width, height);
    afterCommand(fnName);
}

// Calls glStencilFunc().
void GLAPI::stencilFunc(StencilFunction func, GLint ref, GLuint mask) const
{
    static const char *fnName = "glStencilFunc";

    beforeCommand(fnName, _api.glStencilFunc);
    _api.glStencilFunc(toScalar(func), ref, mask);
    afterCommand(fnName);
}

// Calls glStencilMask().
void GLAPI::stencilMask(GLuint mask) const
{
    static const char *fnName = "glStencilMask";

    beforeCommand(fnName, _api.glStencilMask);
    _api.glStencilMask(mask);
    afterCommand(fnName);
}

// Calls glStencilOp().
void GLAPI::stencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass) const
{
    static const char *fnName = "glStencilOp";

    beforeCommand(fnName, _api.glStencilOp);
    _api.glStencilOp(toScalar(fail), toScalar(zfail), toScalar(zpass));
    afterCommand(fnName);
}

// Calls glTexImage1D().
void GLAPI::texImage1D(TextureTarget target, GLint level,
                       InternalFormat internalformat, GLsizei width,
                       GLint border, PixelFormat format, PixelType type,
                       const void *pixels) const
{
    static const char *fnName = "glTexImage1D";

    beforeCommand(fnName, _api.glTexImage1D);
    _api.glTexImage1D(toScalar(target), level, toScalar(internalformat), width,
                      border, toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexImage2D().
void GLAPI::texImage2D(TextureTarget target, GLint level,
                       InternalFormat internalformat, GLsizei width,
                       GLsizei height, GLint border, PixelFormat format,
                       PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexImage2D";

    beforeCommand(fnName, _api.glTexImage2D);
    _api.glTexImage2D(toScalar(target), level, toScalar(internalformat), width,
                      height, border, toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexParameterf().
void GLAPI::texParameterF(TextureTarget target, TextureParameterName pname,
                          GLfloat param) const
{
    static const char *fnName = "glTexParameterf";

    beforeCommand(fnName, _api.glTexParameterf);
    _api.glTexParameterf(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexParameterfv().
void GLAPI::texParameterFV(TextureTarget target, TextureParameterName pname,
                           const GLfloat *params) const
{
    static const char *fnName = "glTexParameterfv";

    beforeCommand(fnName, _api.glTexParameterfv);
    _api.glTexParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTexParameteri().
void GLAPI::texParameterI(TextureTarget target, TextureParameterName pname,
                          GLint param) const
{
    static const char *fnName = "glTexParameteri";

    beforeCommand(fnName, _api.glTexParameteri);
    _api.glTexParameteri(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexParameteriv().
void GLAPI::texParameterIV(TextureTarget target, TextureParameterName pname,
                           const GLint *params) const
{
    static const char *fnName = "glTexParameteriv";

    beforeCommand(fnName, _api.glTexParameteriv);
    _api.glTexParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glViewport().
void GLAPI::viewport(GLint x, GLint y, GLsizei width, GLsizei height) const
{
    static const char *fnName = "glViewport";

    beforeCommand(fnName, _api.glViewport);
    _api.glViewport(x, y, width, height);
    afterCommand(fnName);
}

// Calls glBindTexture().
void GLAPI::bindTexture(TextureTarget target, TextureName texture) const
{
    static const char *fnName = "glBindTexture";

    beforeCommand(fnName, _api.glBindTexture);
    _api.glBindTexture(toScalar(target), texture.ID);
    afterCommand(fnName);
}

// Calls glCopyTexImage1D().
void GLAPI::copyTexImage1D(TextureTarget target, GLint level,
                           InternalFormat internalformat, GLint x, GLint y,
                           GLsizei width, GLint border) const
{
    static const char *fnName = "glCopyTexImage1D";

    beforeCommand(fnName, _api.glCopyTexImage1D);
    _api.glCopyTexImage1D(toScalar(target), level, toScalar(internalformat), x,
                          y, width, border);
    afterCommand(fnName);
}

// Calls glCopyTexImage2D().
void GLAPI::copyTexImage2D(TextureTarget target, GLint level,
                           InternalFormat internalformat, GLint x, GLint y,
                           GLsizei width, GLsizei height, GLint border) const
{
    static const char *fnName = "glCopyTexImage2D";

    beforeCommand(fnName, _api.glCopyTexImage2D);
    _api.glCopyTexImage2D(toScalar(target), level, toScalar(internalformat), x,
                          y, width, height, border);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage1D().
void GLAPI::copyTexSubImage1D(TextureTarget target, GLint level, GLint xoffset,
                              GLint x, GLint y, GLsizei width) const
{
    static const char *fnName = "glCopyTexSubImage1D";

    beforeCommand(fnName, _api.glCopyTexSubImage1D);
    _api.glCopyTexSubImage1D(toScalar(target), level, xoffset, x, y, width);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage2D().
void GLAPI::copyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset,
                              GLint yoffset, GLint x, GLint y, GLsizei width,
                              GLsizei height) const
{
    static const char *fnName = "glCopyTexSubImage2D";

    beforeCommand(fnName, _api.glCopyTexSubImage2D);
    _api.glCopyTexSubImage2D(toScalar(target), level, xoffset, yoffset, x, y,
                             width, height);
    afterCommand(fnName);
}

// Calls glDeleteTextures().
void GLAPI::deleteTextures(GLsizei n, const TextureName *textures) const
{
    static const char *fnName = "glDeleteTextures";

    beforeCommand(fnName, _api.glDeleteTextures);
    _api.glDeleteTextures(n, reinterpret_cast<const GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glDrawArrays().
void GLAPI::drawArrays(PrimitiveType mode, GLint first, GLsizei count) const
{
    static const char *fnName = "glDrawArrays";

    beforeCommand(fnName, _api.glDrawArrays);
    _api.glDrawArrays(toScalar(mode), first, count);
    afterCommand(fnName);
}

// Calls glDrawElements().
void GLAPI::drawElements(PrimitiveType mode, GLsizei count,
                         DrawElementsType type, const void *indices) const
{
    static const char *fnName = "glDrawElements";

    beforeCommand(fnName, _api.glDrawElements);
    _api.glDrawElements(toScalar(mode), count, toScalar(type), indices);
    afterCommand(fnName);
}

// Calls glGenTextures().
void GLAPI::genTextures(GLsizei n, TextureName *textures) const
{
    static const char *fnName = "glGenTextures";

    beforeCommand(fnName, _api.glGenTextures);
    _api.glGenTextures(n, reinterpret_cast<GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glIsTexture().
Boolean GLAPI::isTexture(TextureName texture) const
{
    static const char *fnName = "glIsTexture";

    beforeCommand(fnName, _api.glIsTexture);
    GLboolean result = _api.glIsTexture(texture.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glPolygonOffset().
void GLAPI::polygonOffset(GLfloat factor, GLfloat units) const
{
    static const char *fnName = "glPolygonOffset";

    beforeCommand(fnName, _api.glPolygonOffset);
    _api.glPolygonOffset(factor, units);
    afterCommand(fnName);
}

// Calls glTexSubImage1D().
void GLAPI::texSubImage1D(TextureTarget target, GLint level, GLint xoffset,
                          GLsizei width, PixelFormat format, PixelType type,
                          const void *pixels) const
{
    static const char *fnName = "glTexSubImage1D";

    beforeCommand(fnName, _api.glTexSubImage1D);
    _api.glTexSubImage1D(toScalar(target), level, xoffset, width,
                         toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexSubImage2D().
void GLAPI::texSubImage2D(TextureTarget target, GLint level, GLint xoffset,
                          GLint yoffset, GLsizei width, GLsizei height,
                          PixelFormat format, PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexSubImage2D";

    beforeCommand(fnName, _api.glTexSubImage2D);
    _api.glTexSubImage2D(toScalar(target), level, xoffset, yoffset, width,
                         height, toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage3D().
void GLAPI::copyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                              GLint yoffset, GLint zoffset, GLint x, GLint y,
                              GLsizei width, GLsizei height) const
{
    static const char *fnName = "glCopyTexSubImage3D";

    beforeCommand(fnName, _api.glCopyTexSubImage3D);
    _api.glCopyTexSubImage3D(toScalar(target), level, xoffset, yoffset, zoffset,
                             x, y, width, height);
    afterCommand(fnName);
}

// Calls glDrawRangeElements().
void GLAPI::drawRangeElements(PrimitiveType mode, GLuint start, GLuint end,
                              GLsizei count, DrawElementsType type,
                              const void *indices) const
{
    static const char *fnName = "glDrawRangeElements";

    beforeCommand(fnName, _api.glDrawRangeElements);
    _api.glDrawRangeElements(toScalar(mode), start, end, count, toScalar(type),
                             indices);
    afterCommand(fnName);
}

// Calls glTexImage3D().
void GLAPI::texImage3D(TextureTarget target, GLint level,
                       InternalFormat internalformat, GLsizei width,
                       GLsizei height, GLsizei depth, GLint border,
                       PixelFormat format, PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexImage3D";

    beforeCommand(fnName, _api.glTexImage3D);
    _api.glTexImage3D(toScalar(target), level, toScalar(internalformat), width,
                      height, depth, border, toScalar(format), toScalar(type),
                      pixels);
    afterCommand(fnName);
}

// Calls glTexSubImage3D().
void GLAPI::texSubImage3D(TextureTarget target, GLint level, GLint xoffset,
                          GLint yoffset, GLint zoffset, GLsizei width,
                          GLsizei height, GLsizei depth, PixelFormat format,
                          PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexSubImage3D";

    beforeCommand(fnName, _api.glTexSubImage3D);
    _api.glTexSubImage3D(toScalar(target), level, xoffset, yoffset, zoffset,
                         width, height, depth, toScalar(format), toScalar(type),
                         pixels);
    afterCommand(fnName);
}

// Calls glActiveTexture().
void GLAPI::activeTexture(TextureUnit texture) const
{
    static const char *fnName = "glActiveTexture";

    beforeCommand(fnName, _api.glActiveTexture);
    _api.glActiveTexture(toScalar(texture));
    afterCommand(fnName);
}

// Calls glCompressedTexImage1D().
void GLAPI::compressedTexImage1D(TextureTarget target, GLint level,
                                 InternalFormat internalformat, GLsizei width,
                                 GLint border, GLsizei imageSize,
                                 const void *data) const
{
    static const char *fnName = "glCompressedTexImage1D";

    beforeCommand(fnName, _api.glCompressedTexImage1D);
    _api.glCompressedTexImage1D(toScalar(target), level,
                                toScalar(internalformat), width, border,
                                imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexImage2D().
void GLAPI::compressedTexImage2D(TextureTarget target, GLint level,
                                 InternalFormat internalformat, GLsizei width,
                                 GLsizei height, GLint border, GLsizei imageSize,
                                 const void *data) const
{
    static const char *fnName = "glCompressedTexImage2D";

    beforeCommand(fnName, _api.glCompressedTexImage2D);
    _api.glCompressedTexImage2D(toScalar(target), level,
                                toScalar(internalformat), width, height, border,
                                imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexImage3D().
void GLAPI::compressedTexImage3D(TextureTarget target, GLint level,
                                 InternalFormat internalformat, GLsizei width,
                                 GLsizei height, GLsizei depth, GLint border,
                                 GLsizei imageSize, const void *data) const
{
    static const char *fnName = "glCompressedTexImage3D";

    beforeCommand(fnName, _api.glCompressedTexImage3D);
    _api.glCompressedTexImage3D(toScalar(target), level,
                                toScalar(internalformat), width, height, depth,
                                border, imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage1D().
void GLAPI::compressedTexSubImage1D(TextureTarget target, GLint level,
                                    GLint xoffset, GLsizei width,
                                    InternalFormat format, GLsizei imageSize,
                                    const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage1D";

    beforeCommand(fnName, _api.glCompressedTexSubImage1D);
    _api.glCompressedTexSubImage1D(toScalar(target), level, xoffset, width,
                                   toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage2D().
void GLAPI::compressedTexSubImage2D(TextureTarget target, GLint level,
                                    GLint xoffset, GLint yoffset, GLsizei width,
                                    GLsizei height, InternalFormat format,
                                    GLsizei imageSize, const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage2D";

    beforeCommand(fnName, _api.glCompressedTexSubImage2D);
    _api.glCompressedTexSubImage2D(toScalar(target), level, xoffset, yoffset,
                                   width, height, toScalar(format), imageSize,
                                   data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage3D().
void GLAPI::compressedTexSubImage3D(TextureTarget target, GLint level,
                                    GLint xoffset, GLint yoffset, GLint zoffset,
                                    GLsizei width, GLsizei height, GLsizei depth,
                                    InternalFormat format, GLsizei imageSize,
                                    const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage3D";

    beforeCommand(fnName, _api.glCompressedTexSubImage3D);
    _api.glCompressedTexSubImage3D(toScalar(target), level, xoffset, yoffset,
                                   zoffset, width, height, depth,
                                   toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glGetCompressedTexImage().
void GLAPI::getCompressedTexImage(TextureTarget target, GLint level, void *img) const
{
    static const char *fnName = "glGetCompressedTexImage";

    beforeCommand(fnName, _api.glGetCompressedTexImage);
    _api.glGetCompressedTexImage(toScalar(target), level, img);
    afterCommand(fnName);
}

// Calls glSampleCoverage().
void GLAPI::sampleCoverage(GLfloat value, Boolean invert) const
{
    static const char *fnName = "glSampleCoverage";

    beforeCommand(fnName, _api.glSampleCoverage);
    _api.glSampleCoverage(value, toScalar(invert));
    afterCommand(fnName);
}

// Calls glBlendColor().
void GLAPI::blendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const
{
    static const char *fnName = "glBlendColor";

    beforeCommand(fnName, _api.glBlendColor);
    _api.glBlendColor(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glBlendEquation().
void GLAPI::blendEquation(BlendEquationModeEXT mode) const
{
    static const char *fnName = "glBlendEquation";

    beforeCommand(fnName, _api.glBlendEquation);
    _api.glBlendEquation(toScalar(mode));
    afterCommand(fnName);
}

// Calls glBlendFuncSeparate().
void GLAPI::blendFuncSeparate(BlendingFactor sfactorRGB,
                              BlendingFactor dfactorRGB,
                              BlendingFactor sfactorAlpha,
                              BlendingFactor dfactorAlpha) const
{
    static const char *fnName = "glBlendFuncSeparate";

    beforeCommand(fnName, _api.glBlendFuncSeparate);
    _api.glBlendFuncSeparate(toScalar(sfactorRGB), toScalar(dfactorRGB),
                             toScalar(sfactorAlpha), toScalar(dfactorAlpha));
    afterCommand(fnName);
}

// Calls glMultiDrawArrays().
void GLAPI::multiDrawArrays(PrimitiveType mode, const GLint *first,
                            const GLsizei *count, GLsizei drawcount) const
{
    static const char *fnName = "glMultiDrawArrays";

    beforeCommand(fnName, _api.glMultiDrawArrays);
    _api.glMultiDrawArrays(toScalar(mode), first, count, drawcount);
    afterCommand(fnName);
}

// Calls glMultiDrawElements().
void GLAPI::multiDrawElements(PrimitiveType mode, const GLsizei *count,
                              DrawElementsType type, const void *const*indices,
                              GLsizei drawcount) const
{
    static const char *fnName = "glMultiDrawElements";

    beforeCommand(fnName, _api.glMultiDrawElements);
    _api.glMultiDrawElements(toScalar(mode), count, toScalar(type), indices,
                             drawcount);
    afterCommand(fnName);
}

// Calls glPointParameterf().
void GLAPI::pointParameterF(PointParameterNameARB pname, GLfloat param) const
{
    static const char *fnName = "glPointParameterf";

    beforeCommand(fnName, _api.glPointParameterf);
    _api.glPointParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameterfv().
void GLAPI::pointParameterFV(PointParameterNameARB pname, const GLfloat *params) const
{
    static const char *fnName = "glPointParameterfv";

    beforeCommand(fnName, _api.glPointParameterfv);
    _api.glPointParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glPointParameteri().
void GLAPI::pointParameterI(PointParameterNameARB pname, GLint param) const
{
    static const char *fnName = "glPointParameteri";

    beforeCommand(fnName, _api.glPointParameteri);
    _api.glPointParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameteriv().
void GLAPI::pointParameterIV(PointParameterNameARB pname, const GLint *params) const
{
    static const char *fnName = "glPointParameteriv";

    beforeCommand(fnName, _api.glPointParameteriv);
    _api.glPointParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glBeginQuery().
void GLAPI::beginQuery(QueryTarget target, QueryName id) const
{
    static const char *fnName = "glBeginQuery";

    beforeCommand(fnName, _api.glBeginQuery);
    _api.glBeginQuery(toScalar(target), id.ID);
    afterCommand(fnName);
}

// Calls glBindBuffer().
void GLAPI::bindBuffer(BufferTargetARB target, BufferName buffer) const
{
    static const char *fnName = "glBindBuffer";

    beforeCommand(fnName, _api.glBindBuffer);
    _api.glBindBuffer(toScalar(target), buffer.ID);
    afterCommand(fnName);
}

// Calls glBufferData().
void GLAPI::bufferData(BufferTargetARB target, GLsizeiptr size, const void *data,
                       BufferUsageARB usage) const
{
    static const char *fnName = "glBufferData";

    beforeCommand(fnName, _api.glBufferData);
    _api.glBufferData(toScalar(target), size, data, toScalar(usage));
    afterCommand(fnName);
}

// Calls glBufferSubData().
void GLAPI::bufferSubData(BufferTargetARB target, GLintptr offset,
                          GLsizeiptr size, const void *data) const
{
    static const char *fnName = "glBufferSubData";

    beforeCommand(fnName, _api.glBufferSubData);
    _api.glBufferSubData(toScalar(target), offset, size, data);
    afterCommand(fnName);
}

// Calls glDeleteBuffers().
void GLAPI::deleteBuffers(GLsizei n, const BufferName *buffers) const
{
    static const char *fnName = "glDeleteBuffers";

    beforeCommand(fnName, _api.glDeleteBuffers);
    _api.glDeleteBuffers(n, reinterpret_cast<const GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glDeleteQueries().
void GLAPI::deleteQueries(GLsizei n, const QueryName *ids) const
{
    static const char *fnName = "glDeleteQueries";

    beforeCommand(fnName, _api.glDeleteQueries);
    _api.glDeleteQueries(n, reinterpret_cast<const GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glEndQuery().
void GLAPI::endQuery(QueryTarget target) const
{
    static const char *fnName = "glEndQuery";

    beforeCommand(fnName, _api.glEndQuery);
    _api.glEndQuery(toScalar(target));
    afterCommand(fnName);
}

// Calls glGenBuffers().
void GLAPI::genBuffers(GLsizei n, BufferName *buffers) const
{
    static const char *fnName = "glGenBuffers";

    beforeCommand(fnName, _api.glGenBuffers);
    _api.glGenBuffers(n, reinterpret_cast<GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glGenQueries().
void GLAPI::genQueries(GLsizei n, QueryName *ids) const
{
    static const char *fnName = "glGenQueries";

    beforeCommand(fnName, _api.glGenQueries);
    _api.glGenQueries(n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glGetBufferParameteriv().
void GLAPI::getBufferParameterIV(BufferTargetARB target, BufferPNameARB pname,
                                 GLint *params) const
{
    static const char *fnName = "glGetBufferParameteriv";

    beforeCommand(fnName, _api.glGetBufferParameteriv);
    _api.glGetBufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetBufferPointerv().
void GLAPI::getBufferPointerV(BufferTargetARB target, BufferPointerNameARB pname,
                              void **params) const
{
    static const char *fnName = "glGetBufferPointerv";

    beforeCommand(fnName, _api.glGetBufferPointerv);
    _api.glGetBufferPointerv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetBufferSubData().
void GLAPI::getBufferSubData(BufferTargetARB target, GLintptr offset,
                             GLsizeiptr size, void *data) const
{
    static const char *fnName = "glGetBufferSubData";

    beforeCommand(fnName, _api.glGetBufferSubData);
    _api.glGetBufferSubData(toScalar(target), offset, size, data);
    afterCommand(fnName);
}

// Calls glGetQueryObjectiv().
void GLAPI::getQueryObjectIV(QueryName id, QueryObjectParameterName pname,
                             GLint *params) const
{
    static const char *fnName = "glGetQueryObjectiv";

    beforeCommand(fnName, _api.glGetQueryObjectiv);
    _api.glGetQueryObjectiv(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryObjectuiv().
void GLAPI::getQueryObjectUIV(QueryName id, QueryObjectParameterName pname,
                              GLuint *params) const
{
    static const char *fnName = "glGetQueryObjectuiv";

    beforeCommand(fnName, _api.glGetQueryObjectuiv);
    _api.glGetQueryObjectuiv(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryiv().
void GLAPI::getQueryIV(QueryTarget target, QueryParameterName pname,
                       GLint *params) const
{
    static const char *fnName = "glGetQueryiv";

    beforeCommand(fnName, _api.glGetQueryiv);
    _api.glGetQueryiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsBuffer().
Boolean GLAPI::isBuffer(BufferName buffer) const
{
    static const char *fnName = "glIsBuffer";

    beforeCommand(fnName, _api.glIsBuffer);
    GLboolean result = _api.glIsBuffer(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsQuery().
Boolean GLAPI::isQuery(QueryName id) const
{
    static const char *fnName = "glIsQuery";

    beforeCommand(fnName, _api.glIsQuery);
    GLboolean result = _api.glIsQuery(id.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMapBuffer().
void *GLAPI::mapBuffer(BufferTargetARB target, BufferAccessARB access) const
{
    static const char *fnName = "glMapBuffer";

    beforeCommand(fnName, _api.glMapBuffer);
    void *result = _api.glMapBuffer(toScalar(target), toScalar(access));
    afterCommand(fnName);

    return result;
}

// Calls glUnmapBuffer().
Boolean GLAPI::unmapBuffer(BufferTargetARB target) const
{
    static const char *fnName = "glUnmapBuffer";

    beforeCommand(fnName, _api.glUnmapBuffer);
    GLboolean result = _api.glUnmapBuffer(toScalar(target));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glAttachShader().
void GLAPI::attachShader(ProgramName program, ShaderName shader) const
{
    static const char *fnName = "glAttachShader";

    beforeCommand(fnName, _api.glAttachShader);
    _api.glAttachShader(program.ID, shader.ID);
    afterCommand(fnName);
}

// Calls glBindAttribLocation().
void GLAPI::bindAttribLocation(ProgramName program, GLuint index,
                               const GLchar *name) const
{
    static const char *fnName = "glBindAttribLocation";

    beforeCommand(fnName, _api.glBindAttribLocation);
    _api.glBindAttribLocation(program.ID, index, name);
    afterCommand(fnName);
}

// Calls glBlendEquationSeparate().
void GLAPI::blendEquationSeparate(BlendEquationModeEXT modeRGB,
                                  BlendEquationModeEXT modeAlpha) const
{
    static const char *fnName = "glBlendEquationSeparate";

    beforeCommand(fnName, _api.glBlendEquationSeparate);
    _api.glBlendEquationSeparate(toScalar(modeRGB), toScalar(modeAlpha));
    afterCommand(fnName);
}

// Calls glCompileShader().
void GLAPI::compileShader(ShaderName shader) const
{
    static const char *fnName = "glCompileShader";

    beforeCommand(fnName, _api.glCompileShader);
    _api.glCompileShader(shader.ID);
    afterCommand(fnName);
}

// Calls glCreateProgram().
ProgramName GLAPI::createProgram() const
{
    static const char *fnName = "glCreateProgram";

    beforeCommand(fnName, _api.glCreateProgram);
    GLuint result = _api.glCreateProgram();
    afterCommand(fnName);

    return ProgramName(result);
}

// Calls glCreateShader().
ShaderName GLAPI::createShader(ShaderType type) const
{
    static const char *fnName = "glCreateShader";

    beforeCommand(fnName, _api.glCreateShader);
    GLuint result = _api.glCreateShader(toScalar(type));
    afterCommand(fnName);

    return ShaderName(result);
}

// Calls glDeleteProgram().
void GLAPI::deleteProgram(ProgramName program) const
{
    static const char *fnName = "glDeleteProgram";

    beforeCommand(fnName, _api.glDeleteProgram);
    _api.glDeleteProgram(program.ID);
    afterCommand(fnName);
}

// Calls glDeleteShader().
void GLAPI::deleteShader(ShaderName shader) const
{
    static const char *fnName = "glDeleteShader";

    beforeCommand(fnName, _api.glDeleteShader);
    _api.glDeleteShader(shader.ID);
    afterCommand(fnName);
}

// Calls glDetachShader().
void GLAPI::detachShader(ProgramName program, ShaderName shader) const
{
    static const char *fnName = "glDetachShader";

    beforeCommand(fnName, _api.glDetachShader);
    _api.glDetachShader(program.ID, shader.ID);
    afterCommand(fnName);
}

// Calls glDisableVertexAttribArray().
void GLAPI::disableVertexAttribArray(GLuint index) const
{
    static const char *fnName = "glDisableVertexAttribArray";

    beforeCommand(fnName, _api.glDisableVertexAttribArray);
    _api.glDisableVertexAttribArray(index);
    afterCommand(fnName);
}

// Calls glDrawBuffers().
void GLAPI::drawBuffers(GLsizei n, const DrawBufferMode *bufs) const
{
    static const char *fnName = "glDrawBuffers";

    beforeCommand(fnName, _api.glDrawBuffers);
    _api.glDrawBuffers(n, toScalarPtr(bufs));
    afterCommand(fnName);
}

// Calls glEnableVertexAttribArray().
void GLAPI::enableVertexAttribArray(GLuint index) const
{
    static const char *fnName = "glEnableVertexAttribArray";

    beforeCommand(fnName, _api.glEnableVertexAttribArray);
    _api.glEnableVertexAttribArray(index);
    afterCommand(fnName);
}

// Calls glGetActiveAttrib().
void GLAPI::getActiveAttrib(ProgramName program, GLuint index, GLsizei bufSize,
                            GLsizei *length, GLint *size, AttributeType *type,
                            GLchar *name) const
{
    static const char *fnName = "glGetActiveAttrib";

    beforeCommand(fnName, _api.glGetActiveAttrib);
    _api.glGetActiveAttrib(program.ID, index, bufSize, length, size,
                           toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glGetActiveUniform().
void GLAPI::getActiveUniform(ProgramName program, GLuint index, GLsizei bufSize,
                             GLsizei *length, GLint *size, UniformType *type,
                             GLchar *name) const
{
    static const char *fnName = "glGetActiveUniform";

    beforeCommand(fnName, _api.glGetActiveUniform);
    _api.glGetActiveUniform(program.ID, index, bufSize, length, size,
                            toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glGetAttachedShaders().
void GLAPI::getAttachedShaders(ProgramName program, GLsizei maxCount,
                               GLsizei *count, ShaderName *shaders) const
{
    static const char *fnName = "glGetAttachedShaders";

    beforeCommand(fnName, _api.glGetAttachedShaders);
    _api.glGetAttachedShaders(program.ID, maxCount, count,
                              reinterpret_cast<GLuint *>(shaders));
    afterCommand(fnName);
}

// Calls glGetAttribLocation().
GLint GLAPI::getAttribLocation(ProgramName program, const GLchar *name) const
{
    static const char *fnName = "glGetAttribLocation";

    beforeCommand(fnName, _api.glGetAttribLocation);
    GLint result = _api.glGetAttribLocation(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetProgramInfoLog().
void GLAPI::getProgramInfoLog(ProgramName program, GLsizei bufSize,
                              GLsizei *length, GLchar *infoLog) const
{
    static const char *fnName = "glGetProgramInfoLog";

    beforeCommand(fnName, _api.glGetProgramInfoLog);
    _api.glGetProgramInfoLog(program.ID, bufSize, length, infoLog);
    afterCommand(fnName);
}

// Calls glGetProgramiv().
void GLAPI::getProgramIV(ProgramName program, ProgramPropertyARB pname,
                         GLint *params) const
{
    static const char *fnName = "glGetProgramiv";

    beforeCommand(fnName, _api.glGetProgramiv);
    _api.glGetProgramiv(program.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetShaderInfoLog().
void GLAPI::getShaderInfoLog(ShaderName shader, GLsizei bufSize, GLsizei *length,
                             GLchar *infoLog) const
{
    static const char *fnName = "glGetShaderInfoLog";

    beforeCommand(fnName, _api.glGetShaderInfoLog);
    _api.glGetShaderInfoLog(shader.ID, bufSize, length, infoLog);
    afterCommand(fnName);
}

// Calls glGetShaderSource().
void GLAPI::getShaderSource(ShaderName shader, GLsizei bufSize, GLsizei *length,
                            GLchar *source) const
{
    static const char *fnName = "glGetShaderSource";

    beforeCommand(fnName, _api.glGetShaderSource);
    _api.glGetShaderSource(shader.ID, bufSize, length, source);
    afterCommand(fnName);
}

// Calls glGetShaderiv().
void GLAPI::getShaderIV(ShaderName shader, ShaderParameterName pname,
                        GLint *params) const
{
    static const char *fnName = "glGetShaderiv";

    beforeCommand(fnName, _api.glGetShaderiv);
    _api.glGetShaderiv(shader.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetUniformLocation().
GLint GLAPI::getUniformLocation(ProgramName program, const GLchar *name) const
{
    static const char *fnName = "glGetUniformLocation";

    beforeCommand(fnName, _api.glGetUniformLocation);
    GLint result = _api.glGetUniformLocation(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformfv().
void GLAPI::getUniformFV(ProgramName program, GLint location, GLfloat *params) const
{
    static const char *fnName = "glGetUniformfv";

    beforeCommand(fnName, _api.glGetUniformfv);
    _api.glGetUniformfv(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetUniformiv().
void GLAPI::getUniformIV(ProgramName program, GLint location, GLint *params) const
{
    static const char *fnName = "glGetUniformiv";

    beforeCommand(fnName, _api.glGetUniformiv);
    _api.glGetUniformiv(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribPointerv().
void GLAPI::getVertexAttribPointerV(GLuint index,
                                    VertexAttribPointerPropertyARB pname,
                                    void **pointer) const
{
    static const char *fnName = "glGetVertexAttribPointerv";

    beforeCommand(fnName, _api.glGetVertexAttribPointerv);
    _api.glGetVertexAttribPointerv(index, toScalar(pname), pointer);
    afterCommand(fnName);
}

// Calls glGetVertexAttribdv().
void GLAPI::getVertexAttribDV(GLuint index, VertexAttribPropertyARB pname,
                              GLdouble *params) const
{
    static const char *fnName = "glGetVertexAttribdv";

    beforeCommand(fnName, _api.glGetVertexAttribdv);
    _api.glGetVertexAttribdv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribfv().
void GLAPI::getVertexAttribFV(GLuint index, VertexAttribPropertyARB pname,
                              GLfloat *params) const
{
    static const char *fnName = "glGetVertexAttribfv";

    beforeCommand(fnName, _api.glGetVertexAttribfv);
    _api.glGetVertexAttribfv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribiv().
void GLAPI::getVertexAttribIV(GLuint index, VertexAttribPropertyARB pname,
                              GLint *params) const
{
    static const char *fnName = "glGetVertexAttribiv";

    beforeCommand(fnName, _api.glGetVertexAttribiv);
    _api.glGetVertexAttribiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsProgram().
Boolean GLAPI::isProgram(ProgramName program) const
{
    static const char *fnName = "glIsProgram";

    beforeCommand(fnName, _api.glIsProgram);
    GLboolean result = _api.glIsProgram(program.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsShader().
Boolean GLAPI::isShader(ShaderName shader) const
{
    static const char *fnName = "glIsShader";

    beforeCommand(fnName, _api.glIsShader);
    GLboolean result = _api.glIsShader(shader.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glLinkProgram().
void GLAPI::linkProgram(ProgramName program) const
{
    static const char *fnName = "glLinkProgram";

    beforeCommand(fnName, _api.glLinkProgram);
    _api.glLinkProgram(program.ID);
    afterCommand(fnName);
}

// Calls glShaderSource().
void GLAPI::shaderSource(ShaderName shader, GLsizei count,
                         const GLchar *const*string, const GLint *length) const
{
    static const char *fnName = "glShaderSource";

    beforeCommand(fnName, _api.glShaderSource);
    _api.glShaderSource(shader.ID, count, string, length);
    afterCommand(fnName);
}

// Calls glStencilFuncSeparate().
void GLAPI::stencilFuncSeparate(StencilFaceDirection face, StencilFunction func,
                                GLint ref, GLuint mask) const
{
    static const char *fnName = "glStencilFuncSeparate";

    beforeCommand(fnName, _api.glStencilFuncSeparate);
    _api.glStencilFuncSeparate(toScalar(face), toScalar(func), ref, mask);
    afterCommand(fnName);
}

// Calls glStencilMaskSeparate().
void GLAPI::stencilMaskSeparate(StencilFaceDirection face, GLuint mask) const
{
    static const char *fnName = "glStencilMaskSeparate";

    beforeCommand(fnName, _api.glStencilMaskSeparate);
    _api.glStencilMaskSeparate(toScalar(face), mask);
    afterCommand(fnName);
}

// Calls glStencilOpSeparate().
void GLAPI::stencilOpSeparate(StencilFaceDirection face, StencilOp sfail,
                              StencilOp dpfail, StencilOp dppass) const
{
    static const char *fnName = "glStencilOpSeparate";

    beforeCommand(fnName, _api.glStencilOpSeparate);
    _api.glStencilOpSeparate(toScalar(face), toScalar(sfail), toScalar(dpfail),
                             toScalar(dppass));
    afterCommand(fnName);
}

// Calls glUniform1f().
void GLAPI::uniform1F(GLint location, GLfloat v0) const
{
    static const char *fnName = "glUniform1f";

    beforeCommand(fnName, _api.glUniform1f);
    _api.glUniform1f(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1fv().
void GLAPI::uniform1FV(GLint location, GLsizei count, const GLfloat *value) const
{
    static const char *fnName = "glUniform1fv";

    beforeCommand(fnName, _api.glUniform1fv);
    _api.glUniform1fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1i().
void GLAPI::uniform1I(GLint location, GLint v0) const
{
    static const char *fnName = "glUniform1i";

    beforeCommand(fnName, _api.glUniform1i);
    _api.glUniform1i(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1iv().
void GLAPI::uniform1IV(GLint location, GLsizei count, const GLint *value) const
{
    static const char *fnName = "glUniform1iv";

    beforeCommand(fnName, _api.glUniform1iv);
    _api.glUniform1iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2f().
void GLAPI::uniform2F(GLint location, GLfloat v0, GLfloat v1) const
{
    static const char *fnName = "glUniform2f";

    beforeCommand(fnName, _api.glUniform2f);
    _api.glUniform2f(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2fv().
void GLAPI::uniform2FV(GLint location, GLsizei count, const GLfloat *value) const
{
    static const char *fnName = "glUniform2fv";

    beforeCommand(fnName, _api.glUniform2fv);
    _api.glUniform2fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2i().
void GLAPI::uniform2I(GLint location, GLint v0, GLint v1) const
{
    static const char *fnName = "glUniform2i";

    beforeCommand(fnName, _api.glUniform2i);
    _api.glUniform2i(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2iv().
void GLAPI::uniform2IV(GLint location, GLsizei count, const GLint *value) const
{
    static const char *fnName = "glUniform2iv";

    beforeCommand(fnName, _api.glUniform2iv);
    _api.glUniform2iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3f().
void GLAPI::uniform3F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const
{
    static const char *fnName = "glUniform3f";

    beforeCommand(fnName, _api.glUniform3f);
    _api.glUniform3f(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3fv().
void GLAPI::uniform3FV(GLint location, GLsizei count, const GLfloat *value) const
{
    static const char *fnName = "glUniform3fv";

    beforeCommand(fnName, _api.glUniform3fv);
    _api.glUniform3fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3i().
void GLAPI::uniform3I(GLint location, GLint v0, GLint v1, GLint v2) const
{
    static const char *fnName = "glUniform3i";

    beforeCommand(fnName, _api.glUniform3i);
    _api.glUniform3i(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3iv().
void GLAPI::uniform3IV(GLint location, GLsizei count, const GLint *value) const
{
    static const char *fnName = "glUniform3iv";

    beforeCommand(fnName, _api.glUniform3iv);
    _api.glUniform3iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4f().
void GLAPI::uniform4F(GLint location, GLfloat v0, GLfloat v1, GLfloat v2,
                      GLfloat v3) const
{
    static const char *fnName = "glUniform4f";

    beforeCommand(fnName, _api.glUniform4f);
    _api.glUniform4f(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4fv().
void GLAPI::uniform4FV(GLint location, GLsizei count, const GLfloat *value) const
{
    static const char *fnName = "glUniform4fv";

    beforeCommand(fnName, _api.glUniform4fv);
    _api.glUniform4fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4i().
void GLAPI::uniform4I(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const
{
    static const char *fnName = "glUniform4i";

    beforeCommand(fnName, _api.glUniform4i);
    _api.glUniform4i(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4iv().
void GLAPI::uniform4IV(GLint location, GLsizei count, const GLint *value) const
{
    static const char *fnName = "glUniform4iv";

    beforeCommand(fnName, _api.glUniform4iv);
    _api.glUniform4iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2fv().
void GLAPI::uniformMatrix2FV(GLint location, GLsizei count, Boolean transpose,
                             const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix2fv";

    beforeCommand(fnName, _api.glUniformMatrix2fv);
    _api.glUniformMatrix2fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3fv().
void GLAPI::uniformMatrix3FV(GLint location, GLsizei count, Boolean transpose,
                             const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix3fv";

    beforeCommand(fnName, _api.glUniformMatrix3fv);
    _api.glUniformMatrix3fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4fv().
void GLAPI::uniformMatrix4FV(GLint location, GLsizei count, Boolean transpose,
                             const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix4fv";

    beforeCommand(fnName, _api.glUniformMatrix4fv);
    _api.glUniformMatrix4fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUseProgram().
void GLAPI::useProgram(ProgramName program) const
{
    static const char *fnName = "glUseProgram";

    beforeCommand(fnName, _api.glUseProgram);
    _api.glUseProgram(program.ID);
    afterCommand(fnName);
}

// Calls glValidateProgram().
void GLAPI::validateProgram(ProgramName program) const
{
    static const char *fnName = "glValidateProgram";

    beforeCommand(fnName, _api.glValidateProgram);
    _api.glValidateProgram(program.ID);
    afterCommand(fnName);
}

// Calls glVertexAttrib1d().
void GLAPI::vertexAttrib1D(GLuint index, GLdouble x) const
{
    static const char *fnName = "glVertexAttrib1d";

    beforeCommand(fnName, _api.glVertexAttrib1d);
    _api.glVertexAttrib1d(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1dv().
void GLAPI::vertexAttrib1DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib1dv";

    beforeCommand(fnName, _api.glVertexAttrib1dv);
    _api.glVertexAttrib1dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1f().
void GLAPI::vertexAttrib1F(GLuint index, GLfloat x) const
{
    static const char *fnName = "glVertexAttrib1f";

    beforeCommand(fnName, _api.glVertexAttrib1f);
    _api.glVertexAttrib1f(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1fv().
void GLAPI::vertexAttrib1FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib1fv";

    beforeCommand(fnName, _api.glVertexAttrib1fv);
    _api.glVertexAttrib1fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1s().
void GLAPI::vertexAttrib1S(GLuint index, GLshort x) const
{
    static const char *fnName = "glVertexAttrib1s";

    beforeCommand(fnName, _api.glVertexAttrib1s);
    _api.glVertexAttrib1s(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1sv().
void GLAPI::vertexAttrib1SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib1sv";

    beforeCommand(fnName, _api.glVertexAttrib1sv);
    _api.glVertexAttrib1sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2d().
void GLAPI::vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const
{
    static const char *fnName = "glVertexAttrib2d";

    beforeCommand(fnName, _api.glVertexAttrib2d);
    _api.glVertexAttrib2d(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2dv().
void GLAPI::vertexAttrib2DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib2dv";

    beforeCommand(fnName, _api.glVertexAttrib2dv);
    _api.glVertexAttrib2dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2f().
void GLAPI::vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const
{
    static const char *fnName = "glVertexAttrib2f";

    beforeCommand(fnName, _api.glVertexAttrib2f);
    _api.glVertexAttrib2f(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2fv().
void GLAPI::vertexAttrib2FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib2fv";

    beforeCommand(fnName, _api.glVertexAttrib2fv);
    _api.glVertexAttrib2fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2s().
void GLAPI::vertexAttrib2S(GLuint index, GLshort x, GLshort y) const
{
    static const char *fnName = "glVertexAttrib2s";

    beforeCommand(fnName, _api.glVertexAttrib2s);
    _api.glVertexAttrib2s(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2sv().
void GLAPI::vertexAttrib2SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib2sv";

    beforeCommand(fnName, _api.glVertexAttrib2sv);
    _api.glVertexAttrib2sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3d().
void GLAPI::vertexAttrib3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glVertexAttrib3d";

    beforeCommand(fnName, _api.glVertexAttrib3d);
    _api.glVertexAttrib3d(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3dv().
void GLAPI::vertexAttrib3DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib3dv";

    beforeCommand(fnName, _api.glVertexAttrib3dv);
    _api.glVertexAttrib3dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3f().
void GLAPI::vertexAttrib3F(GLuint index, GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glVertexAttrib3f";

    beforeCommand(fnName, _api.glVertexAttrib3f);
    _api.glVertexAttrib3f(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3fv().
void GLAPI::vertexAttrib3FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib3fv";

    beforeCommand(fnName, _api.glVertexAttrib3fv);
    _api.glVertexAttrib3fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3s().
void GLAPI::vertexAttrib3S(GLuint index, GLshort x, GLshort y, GLshort z) const
{
    static const char *fnName = "glVertexAttrib3s";

    beforeCommand(fnName, _api.glVertexAttrib3s);
    _api.glVertexAttrib3s(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3sv().
void GLAPI::vertexAttrib3SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib3sv";

    beforeCommand(fnName, _api.glVertexAttrib3sv);
    _api.glVertexAttrib3sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nbv().
void GLAPI::vertexAttrib4NBV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttrib4Nbv";

    beforeCommand(fnName, _api.glVertexAttrib4Nbv);
    _api.glVertexAttrib4Nbv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Niv().
void GLAPI::vertexAttrib4NIV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttrib4Niv";

    beforeCommand(fnName, _api.glVertexAttrib4Niv);
    _api.glVertexAttrib4Niv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nsv().
void GLAPI::vertexAttrib4NSV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib4Nsv";

    beforeCommand(fnName, _api.glVertexAttrib4Nsv);
    _api.glVertexAttrib4Nsv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nub().
void GLAPI::vertexAttrib4NUB(GLuint index, GLubyte x, GLubyte y, GLubyte z,
                             GLubyte w) const
{
    static const char *fnName = "glVertexAttrib4Nub";

    beforeCommand(fnName, _api.glVertexAttrib4Nub);
    _api.glVertexAttrib4Nub(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nubv().
void GLAPI::vertexAttrib4NUBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttrib4Nubv";

    beforeCommand(fnName, _api.glVertexAttrib4Nubv);
    _api.glVertexAttrib4Nubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nuiv().
void GLAPI::vertexAttrib4NUIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttrib4Nuiv";

    beforeCommand(fnName, _api.glVertexAttrib4Nuiv);
    _api.glVertexAttrib4Nuiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4Nusv().
void GLAPI::vertexAttrib4NUSV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttrib4Nusv";

    beforeCommand(fnName, _api.glVertexAttrib4Nusv);
    _api.glVertexAttrib4Nusv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4bv().
void GLAPI::vertexAttrib4BV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttrib4bv";

    beforeCommand(fnName, _api.glVertexAttrib4bv);
    _api.glVertexAttrib4bv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4d().
void GLAPI::vertexAttrib4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                           GLdouble w) const
{
    static const char *fnName = "glVertexAttrib4d";

    beforeCommand(fnName, _api.glVertexAttrib4d);
    _api.glVertexAttrib4d(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4dv().
void GLAPI::vertexAttrib4DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib4dv";

    beforeCommand(fnName, _api.glVertexAttrib4dv);
    _api.glVertexAttrib4dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4f().
void GLAPI::vertexAttrib4F(GLuint index, GLfloat x, GLfloat y, GLfloat z,
                           GLfloat w) const
{
    static const char *fnName = "glVertexAttrib4f";

    beforeCommand(fnName, _api.glVertexAttrib4f);
    _api.glVertexAttrib4f(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4fv().
void GLAPI::vertexAttrib4FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib4fv";

    beforeCommand(fnName, _api.glVertexAttrib4fv);
    _api.glVertexAttrib4fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4iv().
void GLAPI::vertexAttrib4IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttrib4iv";

    beforeCommand(fnName, _api.glVertexAttrib4iv);
    _api.glVertexAttrib4iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4s().
void GLAPI::vertexAttrib4S(GLuint index, GLshort x, GLshort y, GLshort z,
                           GLshort w) const
{
    static const char *fnName = "glVertexAttrib4s";

    beforeCommand(fnName, _api.glVertexAttrib4s);
    _api.glVertexAttrib4s(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4sv().
void GLAPI::vertexAttrib4SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib4sv";

    beforeCommand(fnName, _api.glVertexAttrib4sv);
    _api.glVertexAttrib4sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4ubv().
void GLAPI::vertexAttrib4UBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttrib4ubv";

    beforeCommand(fnName, _api.glVertexAttrib4ubv);
    _api.glVertexAttrib4ubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4uiv().
void GLAPI::vertexAttrib4UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttrib4uiv";

    beforeCommand(fnName, _api.glVertexAttrib4uiv);
    _api.glVertexAttrib4uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4usv().
void GLAPI::vertexAttrib4USV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttrib4usv";

    beforeCommand(fnName, _api.glVertexAttrib4usv);
    _api.glVertexAttrib4usv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribPointer().
void GLAPI::vertexAttribPointer(GLuint index, GLint size,
                                VertexAttribPointerType type, Boolean normalized,
                                GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glVertexAttribPointer";

    beforeCommand(fnName, _api.glVertexAttribPointer);
    _api.glVertexAttribPointer(index, size, toScalar(type), toScalar(normalized),
                               stride, pointer);
    afterCommand(fnName);
}

// Calls glUniformMatrix2x3fv().
void GLAPI::uniformMatrix2x3FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix2x3fv";

    beforeCommand(fnName, _api.glUniformMatrix2x3fv);
    _api.glUniformMatrix2x3fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2x4fv().
void GLAPI::uniformMatrix2x4FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix2x4fv";

    beforeCommand(fnName, _api.glUniformMatrix2x4fv);
    _api.glUniformMatrix2x4fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3x2fv().
void GLAPI::uniformMatrix3x2FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix3x2fv";

    beforeCommand(fnName, _api.glUniformMatrix3x2fv);
    _api.glUniformMatrix3x2fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3x4fv().
void GLAPI::uniformMatrix3x4FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix3x4fv";

    beforeCommand(fnName, _api.glUniformMatrix3x4fv);
    _api.glUniformMatrix3x4fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4x2fv().
void GLAPI::uniformMatrix4x2FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix4x2fv";

    beforeCommand(fnName, _api.glUniformMatrix4x2fv);
    _api.glUniformMatrix4x2fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4x3fv().
void GLAPI::uniformMatrix4x3FV(GLint location, GLsizei count, Boolean transpose,
                               const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix4x3fv";

    beforeCommand(fnName, _api.glUniformMatrix4x3fv);
    _api.glUniformMatrix4x3fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glBeginConditionalRender().
void GLAPI::beginConditionalRender(GLuint id, ConditionalRenderMode mode) const
{
    static const char *fnName = "glBeginConditionalRender";

    beforeCommand(fnName, _api.glBeginConditionalRender);
    _api.glBeginConditionalRender(id, toScalar(mode));
    afterCommand(fnName);
}

// Calls glBeginTransformFeedback().
void GLAPI::beginTransformFeedback(PrimitiveType primitiveMode) const
{
    static const char *fnName = "glBeginTransformFeedback";

    beforeCommand(fnName, _api.glBeginTransformFeedback);
    _api.glBeginTransformFeedback(toScalar(primitiveMode));
    afterCommand(fnName);
}

// Calls glBindBufferBase().
void GLAPI::bindBufferBase(BufferTargetARB target, GLuint index,
                           BufferName buffer) const
{
    static const char *fnName = "glBindBufferBase";

    beforeCommand(fnName, _api.glBindBufferBase);
    _api.glBindBufferBase(toScalar(target), index, buffer.ID);
    afterCommand(fnName);
}

// Calls glBindBufferRange().
void GLAPI::bindBufferRange(BufferTargetARB target, GLuint index,
                            BufferName buffer, GLintptr offset, GLsizeiptr size) const
{
    static const char *fnName = "glBindBufferRange";

    beforeCommand(fnName, _api.glBindBufferRange);
    _api.glBindBufferRange(toScalar(target), index, buffer.ID, offset, size);
    afterCommand(fnName);
}

// Calls glBindFragDataLocation().
void GLAPI::bindFragDataLocation(ProgramName program, GLuint color,
                                 const GLchar *name) const
{
    static const char *fnName = "glBindFragDataLocation";

    beforeCommand(fnName, _api.glBindFragDataLocation);
    _api.glBindFragDataLocation(program.ID, color, name);
    afterCommand(fnName);
}

// Calls glBindFramebuffer().
void GLAPI::bindFramebuffer(FramebufferTarget target,
                            FramebufferName framebuffer) const
{
    static const char *fnName = "glBindFramebuffer";

    beforeCommand(fnName, _api.glBindFramebuffer);
    _api.glBindFramebuffer(toScalar(target), framebuffer.ID);
    afterCommand(fnName);
}

// Calls glBindRenderbuffer().
void GLAPI::bindRenderbuffer(RenderbufferTarget target,
                             RenderbufferName renderbuffer) const
{
    static const char *fnName = "glBindRenderbuffer";

    beforeCommand(fnName, _api.glBindRenderbuffer);
    _api.glBindRenderbuffer(toScalar(target), renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glBindVertexArray().
void GLAPI::bindVertexArray(VertexArrayName array) const
{
    static const char *fnName = "glBindVertexArray";

    beforeCommand(fnName, _api.glBindVertexArray);
    _api.glBindVertexArray(array.ID);
    afterCommand(fnName);
}

// Calls glBlitFramebuffer().
void GLAPI::blitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1,
                            GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1,
                            GLbitfield  /* ClearBufferMask */ mask,
                            BlitFramebufferFilter filter) const
{
    static const char *fnName = "glBlitFramebuffer";

    beforeCommand(fnName, _api.glBlitFramebuffer);
    _api.glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1,
                           dstY1, mask, toScalar(filter));
    afterCommand(fnName);
}

// Calls glCheckFramebufferStatus().
FramebufferStatus GLAPI::checkFramebufferStatus(FramebufferTarget target) const
{
    static const char *fnName = "glCheckFramebufferStatus";

    beforeCommand(fnName, _api.glCheckFramebufferStatus);
    GLenum result = _api.glCheckFramebufferStatus(toScalar(target));
    afterCommand(fnName);

    return static_cast<FramebufferStatus>(result);
}

// Calls glClampColor().
void GLAPI::clampColor(ClampColorTargetARB target, ClampColorModeARB clamp) const
{
    static const char *fnName = "glClampColor";

    beforeCommand(fnName, _api.glClampColor);
    _api.glClampColor(toScalar(target), toScalar(clamp));
    afterCommand(fnName);
}

// Calls glClearBufferfi().
void GLAPI::clearBufferFI(BufferEnum buffer, GLint drawbuffer, GLfloat depth,
                          GLint stencil) const
{
    static const char *fnName = "glClearBufferfi";

    beforeCommand(fnName, _api.glClearBufferfi);
    _api.glClearBufferfi(toScalar(buffer), drawbuffer, depth, stencil);
    afterCommand(fnName);
}

// Calls glClearBufferfv().
void GLAPI::clearBufferFV(BufferEnum buffer, GLint drawbuffer,
                          const GLfloat *value) const
{
    static const char *fnName = "glClearBufferfv";

    beforeCommand(fnName, _api.glClearBufferfv);
    _api.glClearBufferfv(toScalar(buffer), drawbuffer, value);
    afterCommand(fnName);
}

// Calls glClearBufferiv().
void GLAPI::clearBufferIV(BufferEnum buffer, GLint drawbuffer,
                          const GLint *value) const
{
    static const char *fnName = "glClearBufferiv";

    beforeCommand(fnName, _api.glClearBufferiv);
    _api.glClearBufferiv(toScalar(buffer), drawbuffer, value);
    afterCommand(fnName);
}

// Calls glClearBufferuiv().
void GLAPI::clearBufferUIV(BufferEnum buffer, GLint drawbuffer,
                           const GLuint *value) const
{
    static const char *fnName = "glClearBufferuiv";

    beforeCommand(fnName, _api.glClearBufferuiv);
    _api.glClearBufferuiv(toScalar(buffer), drawbuffer, value);
    afterCommand(fnName);
}

// Calls glColorMaski().
void GLAPI::colorMaskI(GLuint index, Boolean r, Boolean g, Boolean b, Boolean a) const
{
    static const char *fnName = "glColorMaski";

    beforeCommand(fnName, _api.glColorMaski);
    _api.glColorMaski(index, toScalar(r), toScalar(g), toScalar(b), toScalar(a));
    afterCommand(fnName);
}

// Calls glDeleteFramebuffers().
void GLAPI::deleteFramebuffers(GLsizei n, const FramebufferName *framebuffers) const
{
    static const char *fnName = "glDeleteFramebuffers";

    beforeCommand(fnName, _api.glDeleteFramebuffers);
    _api.glDeleteFramebuffers(n, reinterpret_cast<const GLuint *>(framebuffers));
    afterCommand(fnName);
}

// Calls glDeleteRenderbuffers().
void GLAPI::deleteRenderbuffers(GLsizei n, const RenderbufferName *renderbuffers) const
{
    static const char *fnName = "glDeleteRenderbuffers";

    beforeCommand(fnName, _api.glDeleteRenderbuffers);
    _api.glDeleteRenderbuffers(n,
                               reinterpret_cast<const GLuint *>(renderbuffers));
    afterCommand(fnName);
}

// Calls glDeleteVertexArrays().
void GLAPI::deleteVertexArrays(GLsizei n, const VertexArrayName *arrays) const
{
    static const char *fnName = "glDeleteVertexArrays";

    beforeCommand(fnName, _api.glDeleteVertexArrays);
    _api.glDeleteVertexArrays(n, reinterpret_cast<const GLuint *>(arrays));
    afterCommand(fnName);
}

// Calls glDisablei().
void GLAPI::disableI(EnableCap target, GLuint index) const
{
    static const char *fnName = "glDisablei";

    beforeCommand(fnName, _api.glDisablei);
    _api.glDisablei(toScalar(target), index);
    afterCommand(fnName);
}

// Calls glEnablei().
void GLAPI::enableI(EnableCap target, GLuint index) const
{
    static const char *fnName = "glEnablei";

    beforeCommand(fnName, _api.glEnablei);
    _api.glEnablei(toScalar(target), index);
    afterCommand(fnName);
}

// Calls glEndConditionalRender().
void GLAPI::endConditionalRender() const
{
    static const char *fnName = "glEndConditionalRender";

    beforeCommand(fnName, _api.glEndConditionalRender);
    _api.glEndConditionalRender();
    afterCommand(fnName);
}

// Calls glEndTransformFeedback().
void GLAPI::endTransformFeedback() const
{
    static const char *fnName = "glEndTransformFeedback";

    beforeCommand(fnName, _api.glEndTransformFeedback);
    _api.glEndTransformFeedback();
    afterCommand(fnName);
}

// Calls glFlushMappedBufferRange().
void GLAPI::flushMappedBufferRange(BufferTargetARB target, GLintptr offset,
                                   GLsizeiptr length) const
{
    static const char *fnName = "glFlushMappedBufferRange";

    beforeCommand(fnName, _api.glFlushMappedBufferRange);
    _api.glFlushMappedBufferRange(toScalar(target), offset, length);
    afterCommand(fnName);
}

// Calls glFramebufferRenderbuffer().
void GLAPI::framebufferRenderbuffer(FramebufferTarget target,
                                    FramebufferAttachment attachment,
                                    RenderbufferTarget renderbuffertarget,
                                    RenderbufferName renderbuffer) const
{
    static const char *fnName = "glFramebufferRenderbuffer";

    beforeCommand(fnName, _api.glFramebufferRenderbuffer);
    _api.glFramebufferRenderbuffer(toScalar(target), toScalar(attachment),
                                   toScalar(renderbuffertarget), renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glFramebufferTexture1D().
void GLAPI::framebufferTexture1D(FramebufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureTarget textarget, TextureName texture,
                                 GLint level) const
{
    static const char *fnName = "glFramebufferTexture1D";

    beforeCommand(fnName, _api.glFramebufferTexture1D);
    _api.glFramebufferTexture1D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glFramebufferTexture2D().
void GLAPI::framebufferTexture2D(FramebufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureTarget textarget, TextureName texture,
                                 GLint level) const
{
    static const char *fnName = "glFramebufferTexture2D";

    beforeCommand(fnName, _api.glFramebufferTexture2D);
    _api.glFramebufferTexture2D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glFramebufferTexture3D().
void GLAPI::framebufferTexture3D(FramebufferTarget target,
                                 FramebufferAttachment attachment,
                                 TextureTarget textarget, TextureName texture,
                                 GLint level, GLint zoffset) const
{
    static const char *fnName = "glFramebufferTexture3D";

    beforeCommand(fnName, _api.glFramebufferTexture3D);
    _api.glFramebufferTexture3D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level, zoffset);
    afterCommand(fnName);
}

// Calls glFramebufferTextureLayer().
void GLAPI::framebufferTextureLayer(FramebufferTarget target,
                                    FramebufferAttachment attachment,
                                    TextureName texture, GLint level,
                                    GLint layer) const
{
    static const char *fnName = "glFramebufferTextureLayer";

    beforeCommand(fnName, _api.glFramebufferTextureLayer);
    _api.glFramebufferTextureLayer(toScalar(target), toScalar(attachment),
                                   texture.ID, level, layer);
    afterCommand(fnName);
}

// Calls glGenFramebuffers().
void GLAPI::genFramebuffers(GLsizei n, FramebufferName *framebuffers) const
{
    static const char *fnName = "glGenFramebuffers";

    beforeCommand(fnName, _api.glGenFramebuffers);
    _api.glGenFramebuffers(n, reinterpret_cast<GLuint *>(framebuffers));
    afterCommand(fnName);
}

// Calls glGenRenderbuffers().
void GLAPI::genRenderbuffers(GLsizei n, RenderbufferName *renderbuffers) const
{
    static const char *fnName = "glGenRenderbuffers";

    beforeCommand(fnName, _api.glGenRenderbuffers);
    _api.glGenRenderbuffers(n, reinterpret_cast<GLuint *>(renderbuffers));
    afterCommand(fnName);
}

// Calls glGenVertexArrays().
void GLAPI::genVertexArrays(GLsizei n, VertexArrayName *arrays) const
{
    static const char *fnName = "glGenVertexArrays";

    beforeCommand(fnName, _api.glGenVertexArrays);
    _api.glGenVertexArrays(n, reinterpret_cast<GLuint *>(arrays));
    afterCommand(fnName);
}

// Calls glGenerateMipmap().
void GLAPI::generateMipmap(TextureTarget target) const
{
    static const char *fnName = "glGenerateMipmap";

    beforeCommand(fnName, _api.glGenerateMipmap);
    _api.glGenerateMipmap(toScalar(target));
    afterCommand(fnName);
}

// Calls glGetBooleani_v().
void GLAPI::getBooleanIV(BufferTargetARB target, GLuint index, Boolean *data) const
{
    static const char *fnName = "glGetBooleani_v";

    beforeCommand(fnName, _api.glGetBooleani_v);
    _api.glGetBooleani_v(toScalar(target), index, toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetFragDataLocation().
GLint GLAPI::getFragDataLocation(ProgramName program, const GLchar *name) const
{
    static const char *fnName = "glGetFragDataLocation";

    beforeCommand(fnName, _api.glGetFragDataLocation);
    GLint result = _api.glGetFragDataLocation(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetFramebufferAttachmentParameteriv().
void GLAPI::getFramebufferAttachmentParameterIV(FramebufferTarget target,
                                                FramebufferAttachment attachment,
                                                FramebufferAttachmentParameterName pname,
                                                GLint *params) const
{
    static const char *fnName = "glGetFramebufferAttachmentParameteriv";

    beforeCommand(fnName, _api.glGetFramebufferAttachmentParameteriv);
    _api.glGetFramebufferAttachmentParameteriv(toScalar(target),
                                               toScalar(attachment),
                                               toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetIntegeri_v().
void GLAPI::getIntegerIV(GetPName target, GLuint index, GLint *data) const
{
    static const char *fnName = "glGetIntegeri_v";

    beforeCommand(fnName, _api.glGetIntegeri_v);
    _api.glGetIntegeri_v(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetRenderbufferParameteriv().
void GLAPI::getRenderbufferParameterIV(RenderbufferTarget target,
                                       RenderbufferParameterName pname,
                                       GLint *params) const
{
    static const char *fnName = "glGetRenderbufferParameteriv";

    beforeCommand(fnName, _api.glGetRenderbufferParameteriv);
    _api.glGetRenderbufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetStringi().
const GLubyte *GLAPI::getStringI(StringName name, GLuint index) const
{
    static const char *fnName = "glGetStringi";

    beforeCommand(fnName, _api.glGetStringi);
    const GLubyte *result = _api.glGetStringi(toScalar(name), index);
    afterCommand(fnName);

    return result;
}

// Calls glGetTexParameterIiv().
void GLAPI::getTexParameterIIV(TextureTarget target, GetTextureParameter pname,
                               GLint *params) const
{
    static const char *fnName = "glGetTexParameterIiv";

    beforeCommand(fnName, _api.glGetTexParameterIiv);
    _api.glGetTexParameterIiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTexParameterIuiv().
void GLAPI::getTexParameterIUIV(TextureTarget target, GetTextureParameter pname,
                                GLuint *params) const
{
    static const char *fnName = "glGetTexParameterIuiv";

    beforeCommand(fnName, _api.glGetTexParameterIuiv);
    _api.glGetTexParameterIuiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTransformFeedbackVarying().
void GLAPI::getTransformFeedbackVarying(ProgramName program, GLuint index,
                                        GLsizei bufSize, GLsizei *length,
                                        GLsizei *size, AttributeType *type,
                                        GLchar *name) const
{
    static const char *fnName = "glGetTransformFeedbackVarying";

    beforeCommand(fnName, _api.glGetTransformFeedbackVarying);
    _api.glGetTransformFeedbackVarying(program.ID, index, bufSize, length, size,
                                       toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glGetUniformuiv().
void GLAPI::getUniformUIV(ProgramName program, GLint location, GLuint *params) const
{
    static const char *fnName = "glGetUniformuiv";

    beforeCommand(fnName, _api.glGetUniformuiv);
    _api.glGetUniformuiv(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribIiv().
void GLAPI::getVertexAttribIIV(GLuint index, VertexAttribEnum pname,
                               GLint *params) const
{
    static const char *fnName = "glGetVertexAttribIiv";

    beforeCommand(fnName, _api.glGetVertexAttribIiv);
    _api.glGetVertexAttribIiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribIuiv().
void GLAPI::getVertexAttribIUIV(GLuint index, VertexAttribEnum pname,
                                GLuint *params) const
{
    static const char *fnName = "glGetVertexAttribIuiv";

    beforeCommand(fnName, _api.glGetVertexAttribIuiv);
    _api.glGetVertexAttribIuiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsEnabledi().
Boolean GLAPI::isEnabledI(EnableCap target, GLuint index) const
{
    static const char *fnName = "glIsEnabledi";

    beforeCommand(fnName, _api.glIsEnabledi);
    GLboolean result = _api.glIsEnabledi(toScalar(target), index);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsFramebuffer().
Boolean GLAPI::isFramebuffer(FramebufferName framebuffer) const
{
    static const char *fnName = "glIsFramebuffer";

    beforeCommand(fnName, _api.glIsFramebuffer);
    GLboolean result = _api.glIsFramebuffer(framebuffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsRenderbuffer().
Boolean GLAPI::isRenderbuffer(RenderbufferName renderbuffer) const
{
    static const char *fnName = "glIsRenderbuffer";

    beforeCommand(fnName, _api.glIsRenderbuffer);
    GLboolean result = _api.glIsRenderbuffer(renderbuffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsVertexArray().
Boolean GLAPI::isVertexArray(VertexArrayName array) const
{
    static const char *fnName = "glIsVertexArray";

    beforeCommand(fnName, _api.glIsVertexArray);
    GLboolean result = _api.glIsVertexArray(array.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMapBufferRange().
void *GLAPI::mapBufferRange(BufferTargetARB target, GLintptr offset,
                            GLsizeiptr length,
                            GLbitfield  /* MapBufferAccessMask */ access) const
{
    static const char *fnName = "glMapBufferRange";

    beforeCommand(fnName, _api.glMapBufferRange);
    void *result = _api.glMapBufferRange(toScalar(target), offset, length,
                                         access);
    afterCommand(fnName);

    return result;
}

// Calls glRenderbufferStorage().
void GLAPI::renderbufferStorage(RenderbufferTarget target,
                                InternalFormat internalformat, GLsizei width,
                                GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorage";

    beforeCommand(fnName, _api.glRenderbufferStorage);
    _api.glRenderbufferStorage(toScalar(target), toScalar(internalformat), width,
                               height);
    afterCommand(fnName);
}

// Calls glRenderbufferStorageMultisample().
void GLAPI::renderbufferStorageMultisample(RenderbufferTarget target,
                                           GLsizei samples,
                                           InternalFormat internalformat,
                                           GLsizei width, GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorageMultisample";

    beforeCommand(fnName, _api.glRenderbufferStorageMultisample);
    _api.glRenderbufferStorageMultisample(toScalar(target), samples,
                                          toScalar(internalformat), width,
                                          height);
    afterCommand(fnName);
}

// Calls glTexParameterIiv().
void GLAPI::texParameterIIV(TextureTarget target, TextureParameterName pname,
                            const GLint *params) const
{
    static const char *fnName = "glTexParameterIiv";

    beforeCommand(fnName, _api.glTexParameterIiv);
    _api.glTexParameterIiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTexParameterIuiv().
void GLAPI::texParameterIUIV(TextureTarget target, TextureParameterName pname,
                             const GLuint *params) const
{
    static const char *fnName = "glTexParameterIuiv";

    beforeCommand(fnName, _api.glTexParameterIuiv);
    _api.glTexParameterIuiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTransformFeedbackVaryings().
void GLAPI::transformFeedbackVaryings(ProgramName program, GLsizei count,
                                      const GLchar *const*varyings,
                                      TransformFeedbackBufferMode bufferMode) const
{
    static const char *fnName = "glTransformFeedbackVaryings";

    beforeCommand(fnName, _api.glTransformFeedbackVaryings);
    _api.glTransformFeedbackVaryings(program.ID, count, varyings,
                                     toScalar(bufferMode));
    afterCommand(fnName);
}

// Calls glUniform1ui().
void GLAPI::uniform1UI(GLint location, GLuint v0) const
{
    static const char *fnName = "glUniform1ui";

    beforeCommand(fnName, _api.glUniform1ui);
    _api.glUniform1ui(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1uiv().
void GLAPI::uniform1UIV(GLint location, GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glUniform1uiv";

    beforeCommand(fnName, _api.glUniform1uiv);
    _api.glUniform1uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2ui().
void GLAPI::uniform2UI(GLint location, GLuint v0, GLuint v1) const
{
    static const char *fnName = "glUniform2ui";

    beforeCommand(fnName, _api.glUniform2ui);
    _api.glUniform2ui(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2uiv().
void GLAPI::uniform2UIV(GLint location, GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glUniform2uiv";

    beforeCommand(fnName, _api.glUniform2uiv);
    _api.glUniform2uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3ui().
void GLAPI::uniform3UI(GLint location, GLuint v0, GLuint v1, GLuint v2) const
{
    static const char *fnName = "glUniform3ui";

    beforeCommand(fnName, _api.glUniform3ui);
    _api.glUniform3ui(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3uiv().
void GLAPI::uniform3UIV(GLint location, GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glUniform3uiv";

    beforeCommand(fnName, _api.glUniform3uiv);
    _api.glUniform3uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4ui().
void GLAPI::uniform4UI(GLint location, GLuint v0, GLuint v1, GLuint v2,
                       GLuint v3) const
{
    static const char *fnName = "glUniform4ui";

    beforeCommand(fnName, _api.glUniform4ui);
    _api.glUniform4ui(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4uiv().
void GLAPI::uniform4UIV(GLint location, GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glUniform4uiv";

    beforeCommand(fnName, _api.glUniform4uiv);
    _api.glUniform4uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glVertexAttribI1i().
void GLAPI::vertexAttribI1I(GLuint index, GLint x) const
{
    static const char *fnName = "glVertexAttribI1i";

    beforeCommand(fnName, _api.glVertexAttribI1i);
    _api.glVertexAttribI1i(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribI1iv().
void GLAPI::vertexAttribI1IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI1iv";

    beforeCommand(fnName, _api.glVertexAttribI1iv);
    _api.glVertexAttribI1iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI1ui().
void GLAPI::vertexAttribI1UI(GLuint index, GLuint x) const
{
    static const char *fnName = "glVertexAttribI1ui";

    beforeCommand(fnName, _api.glVertexAttribI1ui);
    _api.glVertexAttribI1ui(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribI1uiv().
void GLAPI::vertexAttribI1UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI1uiv";

    beforeCommand(fnName, _api.glVertexAttribI1uiv);
    _api.glVertexAttribI1uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI2i().
void GLAPI::vertexAttribI2I(GLuint index, GLint x, GLint y) const
{
    static const char *fnName = "glVertexAttribI2i";

    beforeCommand(fnName, _api.glVertexAttribI2i);
    _api.glVertexAttribI2i(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribI2iv().
void GLAPI::vertexAttribI2IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI2iv";

    beforeCommand(fnName, _api.glVertexAttribI2iv);
    _api.glVertexAttribI2iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI2ui().
void GLAPI::vertexAttribI2UI(GLuint index, GLuint x, GLuint y) const
{
    static const char *fnName = "glVertexAttribI2ui";

    beforeCommand(fnName, _api.glVertexAttribI2ui);
    _api.glVertexAttribI2ui(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribI2uiv().
void GLAPI::vertexAttribI2UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI2uiv";

    beforeCommand(fnName, _api.glVertexAttribI2uiv);
    _api.glVertexAttribI2uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI3i().
void GLAPI::vertexAttribI3I(GLuint index, GLint x, GLint y, GLint z) const
{
    static const char *fnName = "glVertexAttribI3i";

    beforeCommand(fnName, _api.glVertexAttribI3i);
    _api.glVertexAttribI3i(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribI3iv().
void GLAPI::vertexAttribI3IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI3iv";

    beforeCommand(fnName, _api.glVertexAttribI3iv);
    _api.glVertexAttribI3iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI3ui().
void GLAPI::vertexAttribI3UI(GLuint index, GLuint x, GLuint y, GLuint z) const
{
    static const char *fnName = "glVertexAttribI3ui";

    beforeCommand(fnName, _api.glVertexAttribI3ui);
    _api.glVertexAttribI3ui(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribI3uiv().
void GLAPI::vertexAttribI3UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI3uiv";

    beforeCommand(fnName, _api.glVertexAttribI3uiv);
    _api.glVertexAttribI3uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4bv().
void GLAPI::vertexAttribI4BV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttribI4bv";

    beforeCommand(fnName, _api.glVertexAttribI4bv);
    _api.glVertexAttribI4bv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4i().
void GLAPI::vertexAttribI4I(GLuint index, GLint x, GLint y, GLint z, GLint w) const
{
    static const char *fnName = "glVertexAttribI4i";

    beforeCommand(fnName, _api.glVertexAttribI4i);
    _api.glVertexAttribI4i(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribI4iv().
void GLAPI::vertexAttribI4IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI4iv";

    beforeCommand(fnName, _api.glVertexAttribI4iv);
    _api.glVertexAttribI4iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4sv().
void GLAPI::vertexAttribI4SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttribI4sv";

    beforeCommand(fnName, _api.glVertexAttribI4sv);
    _api.glVertexAttribI4sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4ubv().
void GLAPI::vertexAttribI4UBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttribI4ubv";

    beforeCommand(fnName, _api.glVertexAttribI4ubv);
    _api.glVertexAttribI4ubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4ui().
void GLAPI::vertexAttribI4UI(GLuint index, GLuint x, GLuint y, GLuint z,
                             GLuint w) const
{
    static const char *fnName = "glVertexAttribI4ui";

    beforeCommand(fnName, _api.glVertexAttribI4ui);
    _api.glVertexAttribI4ui(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribI4uiv().
void GLAPI::vertexAttribI4UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI4uiv";

    beforeCommand(fnName, _api.glVertexAttribI4uiv);
    _api.glVertexAttribI4uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4usv().
void GLAPI::vertexAttribI4USV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttribI4usv";

    beforeCommand(fnName, _api.glVertexAttribI4usv);
    _api.glVertexAttribI4usv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribIPointer().
void GLAPI::vertexAttribIPointer(GLuint index, GLint size,
                                 VertexAttribIType type, GLsizei stride,
                                 const void *pointer) const
{
    static const char *fnName = "glVertexAttribIPointer";

    beforeCommand(fnName, _api.glVertexAttribIPointer);
    _api.glVertexAttribIPointer(index, size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glCopyBufferSubData().
void GLAPI::copyBufferSubData(CopyBufferSubDataTarget readTarget,
                              CopyBufferSubDataTarget writeTarget,
                              GLintptr readOffset, GLintptr writeOffset,
                              GLsizeiptr size) const
{
    static const char *fnName = "glCopyBufferSubData";

    beforeCommand(fnName, _api.glCopyBufferSubData);
    _api.glCopyBufferSubData(toScalar(readTarget), toScalar(writeTarget),
                             readOffset, writeOffset, size);
    afterCommand(fnName);
}

// Calls glDrawArraysInstanced().
void GLAPI::drawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count,
                                GLsizei instancecount) const
{
    static const char *fnName = "glDrawArraysInstanced";

    beforeCommand(fnName, _api.glDrawArraysInstanced);
    _api.glDrawArraysInstanced(toScalar(mode), first, count, instancecount);
    afterCommand(fnName);
}

// Calls glDrawElementsInstanced().
void GLAPI::drawElementsInstanced(PrimitiveType mode, GLsizei count,
                                  DrawElementsType type, const void *indices,
                                  GLsizei instancecount) const
{
    static const char *fnName = "glDrawElementsInstanced";

    beforeCommand(fnName, _api.glDrawElementsInstanced);
    _api.glDrawElementsInstanced(toScalar(mode), count, toScalar(type), indices,
                                 instancecount);
    afterCommand(fnName);
}

// Calls glGetActiveUniformBlockName().
void GLAPI::getActiveUniformBlockName(ProgramName program,
                                      GLuint uniformBlockIndex, GLsizei bufSize,
                                      GLsizei *length, GLchar *uniformBlockName) const
{
    static const char *fnName = "glGetActiveUniformBlockName";

    beforeCommand(fnName, _api.glGetActiveUniformBlockName);
    _api.glGetActiveUniformBlockName(program.ID, uniformBlockIndex, bufSize,
                                     length, uniformBlockName);
    afterCommand(fnName);
}

// Calls glGetActiveUniformBlockiv().
void GLAPI::getActiveUniformBlockIV(ProgramName program,
                                    GLuint uniformBlockIndex,
                                    UniformBlockPName pname, GLint *params) const
{
    static const char *fnName = "glGetActiveUniformBlockiv";

    beforeCommand(fnName, _api.glGetActiveUniformBlockiv);
    _api.glGetActiveUniformBlockiv(program.ID, uniformBlockIndex,
                                   toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetActiveUniformName().
void GLAPI::getActiveUniformName(ProgramName program, GLuint uniformIndex,
                                 GLsizei bufSize, GLsizei *length,
                                 GLchar *uniformName) const
{
    static const char *fnName = "glGetActiveUniformName";

    beforeCommand(fnName, _api.glGetActiveUniformName);
    _api.glGetActiveUniformName(program.ID, uniformIndex, bufSize, length,
                                uniformName);
    afterCommand(fnName);
}

// Calls glGetActiveUniformsiv().
void GLAPI::getActiveUniformsIV(ProgramName program, GLsizei uniformCount,
                                const GLuint *uniformIndices, UniformPName pname,
                                GLint *params) const
{
    static const char *fnName = "glGetActiveUniformsiv";

    beforeCommand(fnName, _api.glGetActiveUniformsiv);
    _api.glGetActiveUniformsiv(program.ID, uniformCount, uniformIndices,
                               toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetUniformBlockIndex().
GLuint GLAPI::getUniformBlockIndex(ProgramName program,
                                   const GLchar *uniformBlockName) const
{
    static const char *fnName = "glGetUniformBlockIndex";

    beforeCommand(fnName, _api.glGetUniformBlockIndex);
    GLuint result = _api.glGetUniformBlockIndex(program.ID, uniformBlockName);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformIndices().
void GLAPI::getUniformIndices(ProgramName program, GLsizei uniformCount,
                              const GLchar *const*uniformNames,
                              GLuint *uniformIndices) const
{
    static const char *fnName = "glGetUniformIndices";

    beforeCommand(fnName, _api.glGetUniformIndices);
    _api.glGetUniformIndices(program.ID, uniformCount, uniformNames,
                             uniformIndices);
    afterCommand(fnName);
}

// Calls glPrimitiveRestartIndex().
void GLAPI::primitiveRestartIndex(GLuint index) const
{
    static const char *fnName = "glPrimitiveRestartIndex";

    beforeCommand(fnName, _api.glPrimitiveRestartIndex);
    _api.glPrimitiveRestartIndex(index);
    afterCommand(fnName);
}

// Calls glTexBuffer().
void GLAPI::texBuffer(TextureTarget target, SizedInternalFormat internalformat,
                      BufferName buffer) const
{
    static const char *fnName = "glTexBuffer";

    beforeCommand(fnName, _api.glTexBuffer);
    _api.glTexBuffer(toScalar(target), toScalar(internalformat), buffer.ID);
    afterCommand(fnName);
}

// Calls glUniformBlockBinding().
void GLAPI::uniformBlockBinding(ProgramName program, GLuint uniformBlockIndex,
                                GLuint uniformBlockBinding) const
{
    static const char *fnName = "glUniformBlockBinding";

    beforeCommand(fnName, _api.glUniformBlockBinding);
    _api.glUniformBlockBinding(program.ID, uniformBlockIndex,
                               uniformBlockBinding);
    afterCommand(fnName);
}

// Calls glClientWaitSync().
SyncStatus GLAPI::clientWaitSync(SyncName sync,
                                 GLbitfield  /* SyncObjectMask */ flags,
                                 GLuint64 timeout) const
{
    static const char *fnName = "glClientWaitSync";

    beforeCommand(fnName, _api.glClientWaitSync);
    GLenum result = _api.glClientWaitSync(sync.ID, flags, timeout);
    afterCommand(fnName);

    return static_cast<SyncStatus>(result);
}

// Calls glDeleteSync().
void GLAPI::deleteSync(SyncName sync) const
{
    static const char *fnName = "glDeleteSync";

    beforeCommand(fnName, _api.glDeleteSync);
    _api.glDeleteSync(sync.ID);
    afterCommand(fnName);
}

// Calls glDrawElementsBaseVertex().
void GLAPI::drawElementsBaseVertex(PrimitiveType mode, GLsizei count,
                                   DrawElementsType type, const void *indices,
                                   GLint basevertex) const
{
    static const char *fnName = "glDrawElementsBaseVertex";

    beforeCommand(fnName, _api.glDrawElementsBaseVertex);
    _api.glDrawElementsBaseVertex(toScalar(mode), count, toScalar(type), indices,
                                  basevertex);
    afterCommand(fnName);
}

// Calls glDrawElementsInstancedBaseVertex().
void GLAPI::drawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count,
                                            DrawElementsType type,
                                            const void *indices,
                                            GLsizei instancecount,
                                            GLint basevertex) const
{
    static const char *fnName = "glDrawElementsInstancedBaseVertex";

    beforeCommand(fnName, _api.glDrawElementsInstancedBaseVertex);
    _api.glDrawElementsInstancedBaseVertex(toScalar(mode), count, toScalar(type),
                                           indices, instancecount, basevertex);
    afterCommand(fnName);
}

// Calls glDrawRangeElementsBaseVertex().
void GLAPI::drawRangeElementsBaseVertex(PrimitiveType mode, GLuint start,
                                        GLuint end, GLsizei count,
                                        DrawElementsType type,
                                        const void *indices, GLint basevertex) const
{
    static const char *fnName = "glDrawRangeElementsBaseVertex";

    beforeCommand(fnName, _api.glDrawRangeElementsBaseVertex);
    _api.glDrawRangeElementsBaseVertex(toScalar(mode), start, end, count,
                                       toScalar(type), indices, basevertex);
    afterCommand(fnName);
}

// Calls glFenceSync().
SyncName GLAPI::fenceSync(SyncCondition condition, SyncBehaviorFlags flags) const
{
    static const char *fnName = "glFenceSync";

    beforeCommand(fnName, _api.glFenceSync);
    GLsync result = _api.glFenceSync(toScalar(condition), toScalar(flags));
    afterCommand(fnName);

    return SyncName(result);
}

// Calls glFramebufferTexture().
void GLAPI::framebufferTexture(FramebufferTarget target,
                               FramebufferAttachment attachment,
                               TextureName texture, GLint level) const
{
    static const char *fnName = "glFramebufferTexture";

    beforeCommand(fnName, _api.glFramebufferTexture);
    _api.glFramebufferTexture(toScalar(target), toScalar(attachment), texture.ID,
                              level);
    afterCommand(fnName);
}

// Calls glGetBufferParameteri64v().
void GLAPI::getBufferParameterI64V(BufferTargetARB target, BufferPNameARB pname,
                                   GLint64 *params) const
{
    static const char *fnName = "glGetBufferParameteri64v";

    beforeCommand(fnName, _api.glGetBufferParameteri64v);
    _api.glGetBufferParameteri64v(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetInteger64i_v().
void GLAPI::getInteger64IV(GetPName target, GLuint index, GLint64 *data) const
{
    static const char *fnName = "glGetInteger64i_v";

    beforeCommand(fnName, _api.glGetInteger64i_v);
    _api.glGetInteger64i_v(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetInteger64v().
void GLAPI::getInteger64V(GetPName pname, GLint64 *data) const
{
    static const char *fnName = "glGetInteger64v";

    beforeCommand(fnName, _api.glGetInteger64v);
    _api.glGetInteger64v(toScalar(pname), data);
    afterCommand(fnName);
}

// Calls glGetMultisamplefv().
void GLAPI::getMultisampleFV(GetMultisamplePNameNV pname, GLuint index,
                             GLfloat *val) const
{
    static const char *fnName = "glGetMultisamplefv";

    beforeCommand(fnName, _api.glGetMultisamplefv);
    _api.glGetMultisamplefv(toScalar(pname), index, val);
    afterCommand(fnName);
}

// Calls glGetSynciv().
void GLAPI::getSyncIV(SyncName sync, SyncParameterName pname, GLsizei count,
                      GLsizei *length, GLint *values) const
{
    static const char *fnName = "glGetSynciv";

    beforeCommand(fnName, _api.glGetSynciv);
    _api.glGetSynciv(sync.ID, toScalar(pname), count, length, values);
    afterCommand(fnName);
}

// Calls glIsSync().
Boolean GLAPI::isSync(SyncName sync) const
{
    static const char *fnName = "glIsSync";

    beforeCommand(fnName, _api.glIsSync);
    GLboolean result = _api.glIsSync(sync.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMultiDrawElementsBaseVertex().
void GLAPI::multiDrawElementsBaseVertex(PrimitiveType mode, const GLsizei *count,
                                        DrawElementsType type,
                                        const void *const*indices,
                                        GLsizei drawcount,
                                        const GLint *basevertex) const
{
    static const char *fnName = "glMultiDrawElementsBaseVertex";

    beforeCommand(fnName, _api.glMultiDrawElementsBaseVertex);
    _api.glMultiDrawElementsBaseVertex(toScalar(mode), count, toScalar(type),
                                       indices, drawcount, basevertex);
    afterCommand(fnName);
}

// Calls glProvokingVertex().
void GLAPI::provokingVertex(VertexProvokingMode mode) const
{
    static const char *fnName = "glProvokingVertex";

    beforeCommand(fnName, _api.glProvokingVertex);
    _api.glProvokingVertex(toScalar(mode));
    afterCommand(fnName);
}

// Calls glSampleMaski().
void GLAPI::sampleMaskI(GLuint maskNumber, GLbitfield mask) const
{
    static const char *fnName = "glSampleMaski";

    beforeCommand(fnName, _api.glSampleMaski);
    _api.glSampleMaski(maskNumber, mask);
    afterCommand(fnName);
}

// Calls glTexImage2DMultisample().
void GLAPI::texImage2DMultisample(TextureTarget target, GLsizei samples,
                                  InternalFormat internalformat, GLsizei width,
                                  GLsizei height, Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTexImage2DMultisample";

    beforeCommand(fnName, _api.glTexImage2DMultisample);
    _api.glTexImage2DMultisample(toScalar(target), samples,
                                 toScalar(internalformat), width, height,
                                 toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTexImage3DMultisample().
void GLAPI::texImage3DMultisample(TextureTarget target, GLsizei samples,
                                  InternalFormat internalformat, GLsizei width,
                                  GLsizei height, GLsizei depth,
                                  Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTexImage3DMultisample";

    beforeCommand(fnName, _api.glTexImage3DMultisample);
    _api.glTexImage3DMultisample(toScalar(target), samples,
                                 toScalar(internalformat), width, height, depth,
                                 toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glWaitSync().
void GLAPI::waitSync(SyncName sync, SyncBehaviorFlags flags, GLuint64 timeout) const
{
    static const char *fnName = "glWaitSync";

    beforeCommand(fnName, _api.glWaitSync);
    _api.glWaitSync(sync.ID, toScalar(flags), timeout);
    afterCommand(fnName);
}

// Calls glBindFragDataLocationIndexed().
void GLAPI::bindFragDataLocationIndexed(ProgramName program, GLuint colorNumber,
                                        GLuint index, const GLchar *name) const
{
    static const char *fnName = "glBindFragDataLocationIndexed";

    beforeCommand(fnName, _api.glBindFragDataLocationIndexed);
    _api.glBindFragDataLocationIndexed(program.ID, colorNumber, index, name);
    afterCommand(fnName);
}

// Calls glBindSampler().
void GLAPI::bindSampler(GLuint unit, SamplerName sampler) const
{
    static const char *fnName = "glBindSampler";

    beforeCommand(fnName, _api.glBindSampler);
    _api.glBindSampler(unit, sampler.ID);
    afterCommand(fnName);
}

// Calls glDeleteSamplers().
void GLAPI::deleteSamplers(GLsizei count, const SamplerName *samplers) const
{
    static const char *fnName = "glDeleteSamplers";

    beforeCommand(fnName, _api.glDeleteSamplers);
    _api.glDeleteSamplers(count, reinterpret_cast<const GLuint *>(samplers));
    afterCommand(fnName);
}

// Calls glGenSamplers().
void GLAPI::genSamplers(GLsizei count, SamplerName *samplers) const
{
    static const char *fnName = "glGenSamplers";

    beforeCommand(fnName, _api.glGenSamplers);
    _api.glGenSamplers(count, reinterpret_cast<GLuint *>(samplers));
    afterCommand(fnName);
}

// Calls glGetFragDataIndex().
GLint GLAPI::getFragDataIndex(ProgramName program, const GLchar *name) const
{
    static const char *fnName = "glGetFragDataIndex";

    beforeCommand(fnName, _api.glGetFragDataIndex);
    GLint result = _api.glGetFragDataIndex(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetQueryObjecti64v().
void GLAPI::getQueryObjectI64V(QueryName id, QueryObjectParameterName pname,
                               GLint64 *params) const
{
    static const char *fnName = "glGetQueryObjecti64v";

    beforeCommand(fnName, _api.glGetQueryObjecti64v);
    _api.glGetQueryObjecti64v(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryObjectui64v().
void GLAPI::getQueryObjectUI64(QueryName id, QueryObjectParameterName pname,
                               GLuint64 *params) const
{
    static const char *fnName = "glGetQueryObjectui64v";

    beforeCommand(fnName, _api.glGetQueryObjectui64v);
    _api.glGetQueryObjectui64v(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSamplerParameterIiv().
void GLAPI::getSamplerParameterIIV(SamplerName sampler, SamplerParameterI pname,
                                   GLint *params) const
{
    static const char *fnName = "glGetSamplerParameterIiv";

    beforeCommand(fnName, _api.glGetSamplerParameterIiv);
    _api.glGetSamplerParameterIiv(sampler.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSamplerParameterIuiv().
void GLAPI::getSamplerParameterIUIV(SamplerName sampler, SamplerParameterI pname,
                                    GLuint *params) const
{
    static const char *fnName = "glGetSamplerParameterIuiv";

    beforeCommand(fnName, _api.glGetSamplerParameterIuiv);
    _api.glGetSamplerParameterIuiv(sampler.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSamplerParameterfv().
void GLAPI::getSamplerParameterFV(SamplerName sampler, SamplerParameterF pname,
                                  GLfloat *params) const
{
    static const char *fnName = "glGetSamplerParameterfv";

    beforeCommand(fnName, _api.glGetSamplerParameterfv);
    _api.glGetSamplerParameterfv(sampler.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSamplerParameteriv().
void GLAPI::getSamplerParameterIV(SamplerName sampler, SamplerParameterI pname,
                                  GLint *params) const
{
    static const char *fnName = "glGetSamplerParameteriv";

    beforeCommand(fnName, _api.glGetSamplerParameteriv);
    _api.glGetSamplerParameteriv(sampler.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsSampler().
Boolean GLAPI::isSampler(SamplerName sampler) const
{
    static const char *fnName = "glIsSampler";

    beforeCommand(fnName, _api.glIsSampler);
    GLboolean result = _api.glIsSampler(sampler.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glQueryCounter().
void GLAPI::queryCounter(QueryName id, QueryCounterTarget target) const
{
    static const char *fnName = "glQueryCounter";

    beforeCommand(fnName, _api.glQueryCounter);
    _api.glQueryCounter(id.ID, toScalar(target));
    afterCommand(fnName);
}

// Calls glSamplerParameterIiv().
void GLAPI::samplerParameterIIV(SamplerName sampler, SamplerParameterI pname,
                                const GLint *param) const
{
    static const char *fnName = "glSamplerParameterIiv";

    beforeCommand(fnName, _api.glSamplerParameterIiv);
    _api.glSamplerParameterIiv(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSamplerParameterIuiv().
void GLAPI::samplerParameterIUIV(SamplerName sampler, SamplerParameterI pname,
                                 const GLuint *param) const
{
    static const char *fnName = "glSamplerParameterIuiv";

    beforeCommand(fnName, _api.glSamplerParameterIuiv);
    _api.glSamplerParameterIuiv(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSamplerParameterf().
void GLAPI::samplerParameterF(SamplerName sampler, SamplerParameterF pname,
                              GLfloat param) const
{
    static const char *fnName = "glSamplerParameterf";

    beforeCommand(fnName, _api.glSamplerParameterf);
    _api.glSamplerParameterf(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSamplerParameterfv().
void GLAPI::samplerParameterFV(SamplerName sampler, SamplerParameterF pname,
                               const GLfloat *param) const
{
    static const char *fnName = "glSamplerParameterfv";

    beforeCommand(fnName, _api.glSamplerParameterfv);
    _api.glSamplerParameterfv(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSamplerParameteri().
void GLAPI::samplerParameterI(SamplerName sampler, SamplerParameterI pname,
                              GLint param) const
{
    static const char *fnName = "glSamplerParameteri";

    beforeCommand(fnName, _api.glSamplerParameteri);
    _api.glSamplerParameteri(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSamplerParameteriv().
void GLAPI::samplerParameterIV(SamplerName sampler, SamplerParameterI pname,
                               const GLint *param) const
{
    static const char *fnName = "glSamplerParameteriv";

    beforeCommand(fnName, _api.glSamplerParameteriv);
    _api.glSamplerParameteriv(sampler.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glVertexAttribDivisor().
void GLAPI::vertexAttribDivisor(GLuint index, GLuint divisor) const
{
    static const char *fnName = "glVertexAttribDivisor";

    beforeCommand(fnName, _api.glVertexAttribDivisor);
    _api.glVertexAttribDivisor(index, divisor);
    afterCommand(fnName);
}

// Calls glVertexAttribP1ui().
void GLAPI::vertexAttribP1UI(GLuint index, VertexAttribPointerType type,
                             Boolean normalized, GLuint value) const
{
    static const char *fnName = "glVertexAttribP1ui";

    beforeCommand(fnName, _api.glVertexAttribP1ui);
    _api.glVertexAttribP1ui(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP1uiv().
void GLAPI::vertexAttribP1UIV(GLuint index, VertexAttribPointerType type,
                              Boolean normalized, const GLuint *value) const
{
    static const char *fnName = "glVertexAttribP1uiv";

    beforeCommand(fnName, _api.glVertexAttribP1uiv);
    _api.glVertexAttribP1uiv(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP2ui().
void GLAPI::vertexAttribP2UI(GLuint index, VertexAttribPointerType type,
                             Boolean normalized, GLuint value) const
{
    static const char *fnName = "glVertexAttribP2ui";

    beforeCommand(fnName, _api.glVertexAttribP2ui);
    _api.glVertexAttribP2ui(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP2uiv().
void GLAPI::vertexAttribP2UIV(GLuint index, VertexAttribPointerType type,
                              Boolean normalized, const GLuint *value) const
{
    static const char *fnName = "glVertexAttribP2uiv";

    beforeCommand(fnName, _api.glVertexAttribP2uiv);
    _api.glVertexAttribP2uiv(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP3ui().
void GLAPI::vertexAttribP3UI(GLuint index, VertexAttribPointerType type,
                             Boolean normalized, GLuint value) const
{
    static const char *fnName = "glVertexAttribP3ui";

    beforeCommand(fnName, _api.glVertexAttribP3ui);
    _api.glVertexAttribP3ui(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP3uiv().
void GLAPI::vertexAttribP3UIV(GLuint index, VertexAttribPointerType type,
                              Boolean normalized, const GLuint *value) const
{
    static const char *fnName = "glVertexAttribP3uiv";

    beforeCommand(fnName, _api.glVertexAttribP3uiv);
    _api.glVertexAttribP3uiv(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP4ui().
void GLAPI::vertexAttribP4UI(GLuint index, VertexAttribPointerType type,
                             Boolean normalized, GLuint value) const
{
    static const char *fnName = "glVertexAttribP4ui";

    beforeCommand(fnName, _api.glVertexAttribP4ui);
    _api.glVertexAttribP4ui(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glVertexAttribP4uiv().
void GLAPI::vertexAttribP4UIV(GLuint index, VertexAttribPointerType type,
                              Boolean normalized, const GLuint *value) const
{
    static const char *fnName = "glVertexAttribP4uiv";

    beforeCommand(fnName, _api.glVertexAttribP4uiv);
    _api.glVertexAttribP4uiv(index, toScalar(type), toScalar(normalized), value);
    afterCommand(fnName);
}

// Calls glBeginQueryIndexed().
void GLAPI::beginQueryIndexed(QueryTarget target, GLuint index, QueryName id) const
{
    static const char *fnName = "glBeginQueryIndexed";

    beforeCommand(fnName, _api.glBeginQueryIndexed);
    _api.glBeginQueryIndexed(toScalar(target), index, id.ID);
    afterCommand(fnName);
}

// Calls glBindTransformFeedback().
void GLAPI::bindTransformFeedback(BindTransformFeedbackTarget target,
                                  TransformFeedbackName id) const
{
    static const char *fnName = "glBindTransformFeedback";

    beforeCommand(fnName, _api.glBindTransformFeedback);
    _api.glBindTransformFeedback(toScalar(target), id.ID);
    afterCommand(fnName);
}

// Calls glBlendEquationSeparatei().
void GLAPI::blendEquationSeparateI(GLuint buf, BlendEquationModeEXT modeRGB,
                                   BlendEquationModeEXT modeAlpha) const
{
    static const char *fnName = "glBlendEquationSeparatei";

    beforeCommand(fnName, _api.glBlendEquationSeparatei);
    _api.glBlendEquationSeparatei(buf, toScalar(modeRGB), toScalar(modeAlpha));
    afterCommand(fnName);
}

// Calls glBlendEquationi().
void GLAPI::blendEquationI(GLuint buf, BlendEquationModeEXT mode) const
{
    static const char *fnName = "glBlendEquationi";

    beforeCommand(fnName, _api.glBlendEquationi);
    _api.glBlendEquationi(buf, toScalar(mode));
    afterCommand(fnName);
}

// Calls glBlendFuncSeparatei().
void GLAPI::blendFuncSeparateI(GLuint buf, BlendingFactor srcRGB,
                               BlendingFactor dstRGB, BlendingFactor srcAlpha,
                               BlendingFactor dstAlpha) const
{
    static const char *fnName = "glBlendFuncSeparatei";

    beforeCommand(fnName, _api.glBlendFuncSeparatei);
    _api.glBlendFuncSeparatei(buf, toScalar(srcRGB), toScalar(dstRGB),
                              toScalar(srcAlpha), toScalar(dstAlpha));
    afterCommand(fnName);
}

// Calls glBlendFunci().
void GLAPI::blendFuncI(GLuint buf, BlendingFactor src, BlendingFactor dst) const
{
    static const char *fnName = "glBlendFunci";

    beforeCommand(fnName, _api.glBlendFunci);
    _api.glBlendFunci(buf, toScalar(src), toScalar(dst));
    afterCommand(fnName);
}

// Calls glDeleteTransformFeedbacks().
void GLAPI::deleteTransformFeedbacks(GLsizei n, const TransformFeedbackName *ids) const
{
    static const char *fnName = "glDeleteTransformFeedbacks";

    beforeCommand(fnName, _api.glDeleteTransformFeedbacks);
    _api.glDeleteTransformFeedbacks(n, reinterpret_cast<const GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glDrawArraysIndirect().
void GLAPI::drawArraysIndirect(PrimitiveType mode, const void *indirect) const
{
    static const char *fnName = "glDrawArraysIndirect";

    beforeCommand(fnName, _api.glDrawArraysIndirect);
    _api.glDrawArraysIndirect(toScalar(mode), indirect);
    afterCommand(fnName);
}

// Calls glDrawElementsIndirect().
void GLAPI::drawElementsIndirect(PrimitiveType mode, DrawElementsType type,
                                 const void *indirect) const
{
    static const char *fnName = "glDrawElementsIndirect";

    beforeCommand(fnName, _api.glDrawElementsIndirect);
    _api.glDrawElementsIndirect(toScalar(mode), toScalar(type), indirect);
    afterCommand(fnName);
}

// Calls glDrawTransformFeedback().
void GLAPI::drawTransformFeedback(PrimitiveType mode, TransformFeedbackName id) const
{
    static const char *fnName = "glDrawTransformFeedback";

    beforeCommand(fnName, _api.glDrawTransformFeedback);
    _api.glDrawTransformFeedback(toScalar(mode), id.ID);
    afterCommand(fnName);
}

// Calls glDrawTransformFeedbackStream().
void GLAPI::drawTransformFeedbackStream(PrimitiveType mode,
                                        TransformFeedbackName id, GLuint stream) const
{
    static const char *fnName = "glDrawTransformFeedbackStream";

    beforeCommand(fnName, _api.glDrawTransformFeedbackStream);
    _api.glDrawTransformFeedbackStream(toScalar(mode), id.ID, stream);
    afterCommand(fnName);
}

// Calls glEndQueryIndexed().
void GLAPI::endQueryIndexed(QueryTarget target, GLuint index) const
{
    static const char *fnName = "glEndQueryIndexed";

    beforeCommand(fnName, _api.glEndQueryIndexed);
    _api.glEndQueryIndexed(toScalar(target), index);
    afterCommand(fnName);
}

// Calls glGenTransformFeedbacks().
void GLAPI::genTransformFeedbacks(GLsizei n, TransformFeedbackName *ids) const
{
    static const char *fnName = "glGenTransformFeedbacks";

    beforeCommand(fnName, _api.glGenTransformFeedbacks);
    _api.glGenTransformFeedbacks(n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glGetActiveSubroutineName().
void GLAPI::getActiveSubroutineName(ProgramName program, ShaderType shadertype,
                                    GLuint index, GLsizei bufSize,
                                    GLsizei *length, GLchar *name) const
{
    static const char *fnName = "glGetActiveSubroutineName";

    beforeCommand(fnName, _api.glGetActiveSubroutineName);
    _api.glGetActiveSubroutineName(program.ID, toScalar(shadertype), index,
                                   bufSize, length, name);
    afterCommand(fnName);
}

// Calls glGetActiveSubroutineUniformName().
void GLAPI::getActiveSubroutineUniformName(ProgramName program,
                                           ShaderType shadertype, GLuint index,
                                           GLsizei bufSize, GLsizei *length,
                                           GLchar *name) const
{
    static const char *fnName = "glGetActiveSubroutineUniformName";

    beforeCommand(fnName, _api.glGetActiveSubroutineUniformName);
    _api.glGetActiveSubroutineUniformName(program.ID, toScalar(shadertype),
                                          index, bufSize, length, name);
    afterCommand(fnName);
}

// Calls glGetActiveSubroutineUniformiv().
void GLAPI::getActiveSubroutineUniformIV(ProgramName program,
                                         ShaderType shadertype, GLuint index,
                                         SubroutineParameterName pname,
                                         GLint *values) const
{
    static const char *fnName = "glGetActiveSubroutineUniformiv";

    beforeCommand(fnName, _api.glGetActiveSubroutineUniformiv);
    _api.glGetActiveSubroutineUniformiv(program.ID, toScalar(shadertype), index,
                                        toScalar(pname), values);
    afterCommand(fnName);
}

// Calls glGetProgramStageiv().
void GLAPI::getProgramStageIV(ProgramName program, ShaderType shadertype,
                              ProgramStagePName pname, GLint *values) const
{
    static const char *fnName = "glGetProgramStageiv";

    beforeCommand(fnName, _api.glGetProgramStageiv);
    _api.glGetProgramStageiv(program.ID, toScalar(shadertype), toScalar(pname),
                             values);
    afterCommand(fnName);
}

// Calls glGetQueryIndexediv().
void GLAPI::getQueryIndexedIV(QueryTarget target, GLuint index,
                              QueryParameterName pname, GLint *params) const
{
    static const char *fnName = "glGetQueryIndexediv";

    beforeCommand(fnName, _api.glGetQueryIndexediv);
    _api.glGetQueryIndexediv(toScalar(target), index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSubroutineIndex().
GLuint GLAPI::getSubroutineIndex(ProgramName program, ShaderType shadertype,
                                 const GLchar *name) const
{
    static const char *fnName = "glGetSubroutineIndex";

    beforeCommand(fnName, _api.glGetSubroutineIndex);
    GLuint result = _api.glGetSubroutineIndex(program.ID, toScalar(shadertype),
                                              name);
    afterCommand(fnName);

    return result;
}

// Calls glGetSubroutineUniformLocation().
GLint GLAPI::getSubroutineUniformLocation(ProgramName program,
                                          ShaderType shadertype,
                                          const GLchar *name) const
{
    static const char *fnName = "glGetSubroutineUniformLocation";

    beforeCommand(fnName, _api.glGetSubroutineUniformLocation);
    GLint result = _api.glGetSubroutineUniformLocation(program.ID,
                                                       toScalar(shadertype),
                                                       name);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformSubroutineuiv().
void GLAPI::getUniformSubroutineUIV(ShaderType shadertype, GLint location,
                                    GLuint *params) const
{
    static const char *fnName = "glGetUniformSubroutineuiv";

    beforeCommand(fnName, _api.glGetUniformSubroutineuiv);
    _api.glGetUniformSubroutineuiv(toScalar(shadertype), location, params);
    afterCommand(fnName);
}

// Calls glGetUniformdv().
void GLAPI::getUniformDV(ProgramName program, GLint location, GLdouble *params) const
{
    static const char *fnName = "glGetUniformdv";

    beforeCommand(fnName, _api.glGetUniformdv);
    _api.glGetUniformdv(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glIsTransformFeedback().
Boolean GLAPI::isTransformFeedback(TransformFeedbackName id) const
{
    static const char *fnName = "glIsTransformFeedback";

    beforeCommand(fnName, _api.glIsTransformFeedback);
    GLboolean result = _api.glIsTransformFeedback(id.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMinSampleShading().
void GLAPI::minSampleShading(GLfloat value) const
{
    static const char *fnName = "glMinSampleShading";

    beforeCommand(fnName, _api.glMinSampleShading);
    _api.glMinSampleShading(value);
    afterCommand(fnName);
}

// Calls glPatchParameterfv().
void GLAPI::patchParameterFV(PatchParameterName pname, const GLfloat *values) const
{
    static const char *fnName = "glPatchParameterfv";

    beforeCommand(fnName, _api.glPatchParameterfv);
    _api.glPatchParameterfv(toScalar(pname), values);
    afterCommand(fnName);
}

// Calls glPatchParameteri().
void GLAPI::patchParameterI(PatchParameterName pname, GLint value) const
{
    static const char *fnName = "glPatchParameteri";

    beforeCommand(fnName, _api.glPatchParameteri);
    _api.glPatchParameteri(toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glPauseTransformFeedback().
void GLAPI::pauseTransformFeedback() const
{
    static const char *fnName = "glPauseTransformFeedback";

    beforeCommand(fnName, _api.glPauseTransformFeedback);
    _api.glPauseTransformFeedback();
    afterCommand(fnName);
}

// Calls glResumeTransformFeedback().
void GLAPI::resumeTransformFeedback() const
{
    static const char *fnName = "glResumeTransformFeedback";

    beforeCommand(fnName, _api.glResumeTransformFeedback);
    _api.glResumeTransformFeedback();
    afterCommand(fnName);
}

// Calls glUniform1d().
void GLAPI::uniform1D(GLint location, GLdouble x) const
{
    static const char *fnName = "glUniform1d";

    beforeCommand(fnName, _api.glUniform1d);
    _api.glUniform1d(location, x);
    afterCommand(fnName);
}

// Calls glUniform1dv().
void GLAPI::uniform1DV(GLint location, GLsizei count, const GLdouble *value) const
{
    static const char *fnName = "glUniform1dv";

    beforeCommand(fnName, _api.glUniform1dv);
    _api.glUniform1dv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2d().
void GLAPI::uniform2D(GLint location, GLdouble x, GLdouble y) const
{
    static const char *fnName = "glUniform2d";

    beforeCommand(fnName, _api.glUniform2d);
    _api.glUniform2d(location, x, y);
    afterCommand(fnName);
}

// Calls glUniform2dv().
void GLAPI::uniform2DV(GLint location, GLsizei count, const GLdouble *value) const
{
    static const char *fnName = "glUniform2dv";

    beforeCommand(fnName, _api.glUniform2dv);
    _api.glUniform2dv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3d().
void GLAPI::uniform3D(GLint location, GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glUniform3d";

    beforeCommand(fnName, _api.glUniform3d);
    _api.glUniform3d(location, x, y, z);
    afterCommand(fnName);
}

// Calls glUniform3dv().
void GLAPI::uniform3DV(GLint location, GLsizei count, const GLdouble *value) const
{
    static const char *fnName = "glUniform3dv";

    beforeCommand(fnName, _api.glUniform3dv);
    _api.glUniform3dv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4d().
void GLAPI::uniform4D(GLint location, GLdouble x, GLdouble y, GLdouble z,
                      GLdouble w) const
{
    static const char *fnName = "glUniform4d";

    beforeCommand(fnName, _api.glUniform4d);
    _api.glUniform4d(location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glUniform4dv().
void GLAPI::uniform4DV(GLint location, GLsizei count, const GLdouble *value) const
{
    static const char *fnName = "glUniform4dv";

    beforeCommand(fnName, _api.glUniform4dv);
    _api.glUniform4dv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2dv().
void GLAPI::uniformMatrix2DV(GLint location, GLsizei count, Boolean transpose,
                             const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix2dv";

    beforeCommand(fnName, _api.glUniformMatrix2dv);
    _api.glUniformMatrix2dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2x3dv().
void GLAPI::uniformMatrix2x3DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix2x3dv";

    beforeCommand(fnName, _api.glUniformMatrix2x3dv);
    _api.glUniformMatrix2x3dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2x4dv().
void GLAPI::uniformMatrix2x4DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix2x4dv";

    beforeCommand(fnName, _api.glUniformMatrix2x4dv);
    _api.glUniformMatrix2x4dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3dv().
void GLAPI::uniformMatrix3DV(GLint location, GLsizei count, Boolean transpose,
                             const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix3dv";

    beforeCommand(fnName, _api.glUniformMatrix3dv);
    _api.glUniformMatrix3dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3x2dv().
void GLAPI::uniformMatrix3x2DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix3x2dv";

    beforeCommand(fnName, _api.glUniformMatrix3x2dv);
    _api.glUniformMatrix3x2dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3x4dv().
void GLAPI::uniformMatrix3x4DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix3x4dv";

    beforeCommand(fnName, _api.glUniformMatrix3x4dv);
    _api.glUniformMatrix3x4dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4dv().
void GLAPI::uniformMatrix4DV(GLint location, GLsizei count, Boolean transpose,
                             const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix4dv";

    beforeCommand(fnName, _api.glUniformMatrix4dv);
    _api.glUniformMatrix4dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4x2dv().
void GLAPI::uniformMatrix4x2DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix4x2dv";

    beforeCommand(fnName, _api.glUniformMatrix4x2dv);
    _api.glUniformMatrix4x2dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4x3dv().
void GLAPI::uniformMatrix4x3DV(GLint location, GLsizei count, Boolean transpose,
                               const GLdouble *value) const
{
    static const char *fnName = "glUniformMatrix4x3dv";

    beforeCommand(fnName, _api.glUniformMatrix4x3dv);
    _api.glUniformMatrix4x3dv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformSubroutinesuiv().
void GLAPI::uniformSubroutinesUIV(ShaderType shadertype, GLsizei count,
                                  const GLuint *indices) const
{
    static const char *fnName = "glUniformSubroutinesuiv";

    beforeCommand(fnName, _api.glUniformSubroutinesuiv);
    _api.glUniformSubroutinesuiv(toScalar(shadertype), count, indices);
    afterCommand(fnName);
}

// Calls glActiveShaderProgram().
void GLAPI::activeShaderProgram(ProgramPipelineName pipeline,
                                ProgramName program) const
{
    static const char *fnName = "glActiveShaderProgram";

    beforeCommand(fnName, _api.glActiveShaderProgram);
    _api.glActiveShaderProgram(pipeline.ID, program.ID);
    afterCommand(fnName);
}

// Calls glBindProgramPipeline().
void GLAPI::bindProgramPipeline(ProgramPipelineName pipeline) const
{
    static const char *fnName = "glBindProgramPipeline";

    beforeCommand(fnName, _api.glBindProgramPipeline);
    _api.glBindProgramPipeline(pipeline.ID);
    afterCommand(fnName);
}

// Calls glClearDepthf().
void GLAPI::clearDepthF(GLfloat d) const
{
    static const char *fnName = "glClearDepthf";

    beforeCommand(fnName, _api.glClearDepthf);
    _api.glClearDepthf(d);
    afterCommand(fnName);
}

// Calls glCreateShaderProgramv().
ProgramName GLAPI::createShaderProgramV(ShaderType type, GLsizei count,
                                        const GLchar *const*strings) const
{
    static const char *fnName = "glCreateShaderProgramv";

    beforeCommand(fnName, _api.glCreateShaderProgramv);
    GLuint result = _api.glCreateShaderProgramv(toScalar(type), count, strings);
    afterCommand(fnName);

    return ProgramName(result);
}

// Calls glDeleteProgramPipelines().
void GLAPI::deleteProgramPipelines(GLsizei n,
                                   const ProgramPipelineName *pipelines) const
{
    static const char *fnName = "glDeleteProgramPipelines";

    beforeCommand(fnName, _api.glDeleteProgramPipelines);
    _api.glDeleteProgramPipelines(n, reinterpret_cast<const GLuint *>(pipelines));
    afterCommand(fnName);
}

// Calls glDepthRangeArrayv().
void GLAPI::depthRangeArrayV(GLuint first, GLsizei count, const GLdouble *v) const
{
    static const char *fnName = "glDepthRangeArrayv";

    beforeCommand(fnName, _api.glDepthRangeArrayv);
    _api.glDepthRangeArrayv(first, count, v);
    afterCommand(fnName);
}

// Calls glDepthRangeIndexed().
void GLAPI::depthRangeIndexed(GLuint index, GLdouble n, GLdouble f) const
{
    static const char *fnName = "glDepthRangeIndexed";

    beforeCommand(fnName, _api.glDepthRangeIndexed);
    _api.glDepthRangeIndexed(index, n, f);
    afterCommand(fnName);
}

// Calls glDepthRangef().
void GLAPI::depthRangeF(GLfloat n, GLfloat f) const
{
    static const char *fnName = "glDepthRangef";

    beforeCommand(fnName, _api.glDepthRangef);
    _api.glDepthRangef(n, f);
    afterCommand(fnName);
}

// Calls glGenProgramPipelines().
void GLAPI::genProgramPipelines(GLsizei n, ProgramPipelineName *pipelines) const
{
    static const char *fnName = "glGenProgramPipelines";

    beforeCommand(fnName, _api.glGenProgramPipelines);
    _api.glGenProgramPipelines(n, reinterpret_cast<GLuint *>(pipelines));
    afterCommand(fnName);
}

// Calls glGetDoublei_v().
void GLAPI::getDoubleIV(GetPName target, GLuint index, GLdouble *data) const
{
    static const char *fnName = "glGetDoublei_v";

    beforeCommand(fnName, _api.glGetDoublei_v);
    _api.glGetDoublei_v(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetFloati_v().
void GLAPI::getFloatIV(GetPName target, GLuint index, GLfloat *data) const
{
    static const char *fnName = "glGetFloati_v";

    beforeCommand(fnName, _api.glGetFloati_v);
    _api.glGetFloati_v(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetProgramBinary().
void GLAPI::getProgramBinary(ProgramName program, GLsizei bufSize,
                             GLsizei *length, GLenum *binaryFormat, void *binary) const
{
    static const char *fnName = "glGetProgramBinary";

    beforeCommand(fnName, _api.glGetProgramBinary);
    _api.glGetProgramBinary(program.ID, bufSize, length, binaryFormat, binary);
    afterCommand(fnName);
}

// Calls glGetProgramPipelineInfoLog().
void GLAPI::getProgramPipelineInfoLog(ProgramPipelineName pipeline,
                                      GLsizei bufSize, GLsizei *length,
                                      GLchar *infoLog) const
{
    static const char *fnName = "glGetProgramPipelineInfoLog";

    beforeCommand(fnName, _api.glGetProgramPipelineInfoLog);
    _api.glGetProgramPipelineInfoLog(pipeline.ID, bufSize, length, infoLog);
    afterCommand(fnName);
}

// Calls glGetProgramPipelineiv().
void GLAPI::getProgramPipelineIV(ProgramPipelineName pipeline,
                                 PipelineParameterName pname, GLint *params) const
{
    static const char *fnName = "glGetProgramPipelineiv";

    beforeCommand(fnName, _api.glGetProgramPipelineiv);
    _api.glGetProgramPipelineiv(pipeline.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetShaderPrecisionFormat().
void GLAPI::getShaderPrecisionFormat(ShaderType shadertype,
                                     PrecisionType precisiontype, GLint *range,
                                     GLint *precision) const
{
    static const char *fnName = "glGetShaderPrecisionFormat";

    beforeCommand(fnName, _api.glGetShaderPrecisionFormat);
    _api.glGetShaderPrecisionFormat(toScalar(shadertype),
                                    toScalar(precisiontype), range, precision);
    afterCommand(fnName);
}

// Calls glGetVertexAttribLdv().
void GLAPI::getVertexAttribLDV(GLuint index, VertexAttribEnum pname,
                               GLdouble *params) const
{
    static const char *fnName = "glGetVertexAttribLdv";

    beforeCommand(fnName, _api.glGetVertexAttribLdv);
    _api.glGetVertexAttribLdv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsProgramPipeline().
Boolean GLAPI::isProgramPipeline(ProgramPipelineName pipeline) const
{
    static const char *fnName = "glIsProgramPipeline";

    beforeCommand(fnName, _api.glIsProgramPipeline);
    GLboolean result = _api.glIsProgramPipeline(pipeline.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glProgramBinary().
void GLAPI::programBinary(ProgramName program, GLenum binaryFormat,
                          const void *binary, GLsizei length) const
{
    static const char *fnName = "glProgramBinary";

    beforeCommand(fnName, _api.glProgramBinary);
    _api.glProgramBinary(program.ID, binaryFormat, binary, length);
    afterCommand(fnName);
}

// Calls glProgramParameteri().
void GLAPI::programParameterI(ProgramName program, ProgramParameterPName pname,
                              GLint value) const
{
    static const char *fnName = "glProgramParameteri";

    beforeCommand(fnName, _api.glProgramParameteri);
    _api.glProgramParameteri(program.ID, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glProgramUniform1d().
void GLAPI::programUniform1D(ProgramName program, GLint location, GLdouble v0) const
{
    static const char *fnName = "glProgramUniform1d";

    beforeCommand(fnName, _api.glProgramUniform1d);
    _api.glProgramUniform1d(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1dv().
void GLAPI::programUniform1DV(ProgramName program, GLint location, GLsizei count,
                              const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform1dv";

    beforeCommand(fnName, _api.glProgramUniform1dv);
    _api.glProgramUniform1dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1f().
void GLAPI::programUniform1F(ProgramName program, GLint location, GLfloat v0) const
{
    static const char *fnName = "glProgramUniform1f";

    beforeCommand(fnName, _api.glProgramUniform1f);
    _api.glProgramUniform1f(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1fv().
void GLAPI::programUniform1FV(ProgramName program, GLint location, GLsizei count,
                              const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform1fv";

    beforeCommand(fnName, _api.glProgramUniform1fv);
    _api.glProgramUniform1fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1i().
void GLAPI::programUniform1I(ProgramName program, GLint location, GLint v0) const
{
    static const char *fnName = "glProgramUniform1i";

    beforeCommand(fnName, _api.glProgramUniform1i);
    _api.glProgramUniform1i(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1iv().
void GLAPI::programUniform1IV(ProgramName program, GLint location, GLsizei count,
                              const GLint *value) const
{
    static const char *fnName = "glProgramUniform1iv";

    beforeCommand(fnName, _api.glProgramUniform1iv);
    _api.glProgramUniform1iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1ui().
void GLAPI::programUniform1UI(ProgramName program, GLint location, GLuint v0) const
{
    static const char *fnName = "glProgramUniform1ui";

    beforeCommand(fnName, _api.glProgramUniform1ui);
    _api.glProgramUniform1ui(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1uiv().
void GLAPI::programUniform1UIV(ProgramName program, GLint location,
                               GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glProgramUniform1uiv";

    beforeCommand(fnName, _api.glProgramUniform1uiv);
    _api.glProgramUniform1uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2d().
void GLAPI::programUniform2D(ProgramName program, GLint location, GLdouble v0,
                             GLdouble v1) const
{
    static const char *fnName = "glProgramUniform2d";

    beforeCommand(fnName, _api.glProgramUniform2d);
    _api.glProgramUniform2d(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2dv().
void GLAPI::programUniform2DV(ProgramName program, GLint location, GLsizei count,
                              const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform2dv";

    beforeCommand(fnName, _api.glProgramUniform2dv);
    _api.glProgramUniform2dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2f().
void GLAPI::programUniform2F(ProgramName program, GLint location, GLfloat v0,
                             GLfloat v1) const
{
    static const char *fnName = "glProgramUniform2f";

    beforeCommand(fnName, _api.glProgramUniform2f);
    _api.glProgramUniform2f(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2fv().
void GLAPI::programUniform2FV(ProgramName program, GLint location, GLsizei count,
                              const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform2fv";

    beforeCommand(fnName, _api.glProgramUniform2fv);
    _api.glProgramUniform2fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2i().
void GLAPI::programUniform2I(ProgramName program, GLint location, GLint v0,
                             GLint v1) const
{
    static const char *fnName = "glProgramUniform2i";

    beforeCommand(fnName, _api.glProgramUniform2i);
    _api.glProgramUniform2i(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2iv().
void GLAPI::programUniform2IV(ProgramName program, GLint location, GLsizei count,
                              const GLint *value) const
{
    static const char *fnName = "glProgramUniform2iv";

    beforeCommand(fnName, _api.glProgramUniform2iv);
    _api.glProgramUniform2iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2ui().
void GLAPI::programUniform2UI(ProgramName program, GLint location, GLuint v0,
                              GLuint v1) const
{
    static const char *fnName = "glProgramUniform2ui";

    beforeCommand(fnName, _api.glProgramUniform2ui);
    _api.glProgramUniform2ui(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2uiv().
void GLAPI::programUniform2UIV(ProgramName program, GLint location,
                               GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glProgramUniform2uiv";

    beforeCommand(fnName, _api.glProgramUniform2uiv);
    _api.glProgramUniform2uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3d().
void GLAPI::programUniform3D(ProgramName program, GLint location, GLdouble v0,
                             GLdouble v1, GLdouble v2) const
{
    static const char *fnName = "glProgramUniform3d";

    beforeCommand(fnName, _api.glProgramUniform3d);
    _api.glProgramUniform3d(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3dv().
void GLAPI::programUniform3DV(ProgramName program, GLint location, GLsizei count,
                              const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform3dv";

    beforeCommand(fnName, _api.glProgramUniform3dv);
    _api.glProgramUniform3dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3f().
void GLAPI::programUniform3F(ProgramName program, GLint location, GLfloat v0,
                             GLfloat v1, GLfloat v2) const
{
    static const char *fnName = "glProgramUniform3f";

    beforeCommand(fnName, _api.glProgramUniform3f);
    _api.glProgramUniform3f(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3fv().
void GLAPI::programUniform3FV(ProgramName program, GLint location, GLsizei count,
                              const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform3fv";

    beforeCommand(fnName, _api.glProgramUniform3fv);
    _api.glProgramUniform3fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3i().
void GLAPI::programUniform3I(ProgramName program, GLint location, GLint v0,
                             GLint v1, GLint v2) const
{
    static const char *fnName = "glProgramUniform3i";

    beforeCommand(fnName, _api.glProgramUniform3i);
    _api.glProgramUniform3i(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3iv().
void GLAPI::programUniform3IV(ProgramName program, GLint location, GLsizei count,
                              const GLint *value) const
{
    static const char *fnName = "glProgramUniform3iv";

    beforeCommand(fnName, _api.glProgramUniform3iv);
    _api.glProgramUniform3iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3ui().
void GLAPI::programUniform3UI(ProgramName program, GLint location, GLuint v0,
                              GLuint v1, GLuint v2) const
{
    static const char *fnName = "glProgramUniform3ui";

    beforeCommand(fnName, _api.glProgramUniform3ui);
    _api.glProgramUniform3ui(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3uiv().
void GLAPI::programUniform3UIV(ProgramName program, GLint location,
                               GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glProgramUniform3uiv";

    beforeCommand(fnName, _api.glProgramUniform3uiv);
    _api.glProgramUniform3uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4d().
void GLAPI::programUniform4D(ProgramName program, GLint location, GLdouble v0,
                             GLdouble v1, GLdouble v2, GLdouble v3) const
{
    static const char *fnName = "glProgramUniform4d";

    beforeCommand(fnName, _api.glProgramUniform4d);
    _api.glProgramUniform4d(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4dv().
void GLAPI::programUniform4DV(ProgramName program, GLint location, GLsizei count,
                              const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform4dv";

    beforeCommand(fnName, _api.glProgramUniform4dv);
    _api.glProgramUniform4dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4f().
void GLAPI::programUniform4F(ProgramName program, GLint location, GLfloat v0,
                             GLfloat v1, GLfloat v2, GLfloat v3) const
{
    static const char *fnName = "glProgramUniform4f";

    beforeCommand(fnName, _api.glProgramUniform4f);
    _api.glProgramUniform4f(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4fv().
void GLAPI::programUniform4FV(ProgramName program, GLint location, GLsizei count,
                              const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform4fv";

    beforeCommand(fnName, _api.glProgramUniform4fv);
    _api.glProgramUniform4fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4i().
void GLAPI::programUniform4I(ProgramName program, GLint location, GLint v0,
                             GLint v1, GLint v2, GLint v3) const
{
    static const char *fnName = "glProgramUniform4i";

    beforeCommand(fnName, _api.glProgramUniform4i);
    _api.glProgramUniform4i(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4iv().
void GLAPI::programUniform4IV(ProgramName program, GLint location, GLsizei count,
                              const GLint *value) const
{
    static const char *fnName = "glProgramUniform4iv";

    beforeCommand(fnName, _api.glProgramUniform4iv);
    _api.glProgramUniform4iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4ui().
void GLAPI::programUniform4UI(ProgramName program, GLint location, GLuint v0,
                              GLuint v1, GLuint v2, GLuint v3) const
{
    static const char *fnName = "glProgramUniform4ui";

    beforeCommand(fnName, _api.glProgramUniform4ui);
    _api.glProgramUniform4ui(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4uiv().
void GLAPI::programUniform4UIV(ProgramName program, GLint location,
                               GLsizei count, const GLuint *value) const
{
    static const char *fnName = "glProgramUniform4uiv";

    beforeCommand(fnName, _api.glProgramUniform4uiv);
    _api.glProgramUniform4uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2dv().
void GLAPI::programUniformMatrix2DV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2dv);
    _api.glProgramUniformMatrix2dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2fv().
void GLAPI::programUniformMatrix2FV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2fv);
    _api.glProgramUniformMatrix2fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x3dv().
void GLAPI::programUniformMatrix2x3DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x3dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x3dv);
    _api.glProgramUniformMatrix2x3dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x3fv().
void GLAPI::programUniformMatrix2x3FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x3fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x3fv);
    _api.glProgramUniformMatrix2x3fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x4dv().
void GLAPI::programUniformMatrix2x4DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x4dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x4dv);
    _api.glProgramUniformMatrix2x4dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x4fv().
void GLAPI::programUniformMatrix2x4FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x4fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x4fv);
    _api.glProgramUniformMatrix2x4fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3dv().
void GLAPI::programUniformMatrix3DV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3dv);
    _api.glProgramUniformMatrix3dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3fv().
void GLAPI::programUniformMatrix3FV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3fv);
    _api.glProgramUniformMatrix3fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x2dv().
void GLAPI::programUniformMatrix3x2DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x2dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x2dv);
    _api.glProgramUniformMatrix3x2dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x2fv().
void GLAPI::programUniformMatrix3x2FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x2fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x2fv);
    _api.glProgramUniformMatrix3x2fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x4dv().
void GLAPI::programUniformMatrix3x4DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x4dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x4dv);
    _api.glProgramUniformMatrix3x4dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x4fv().
void GLAPI::programUniformMatrix3x4FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x4fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x4fv);
    _api.glProgramUniformMatrix3x4fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4dv().
void GLAPI::programUniformMatrix4DV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4dv);
    _api.glProgramUniformMatrix4dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4fv().
void GLAPI::programUniformMatrix4FV(ProgramName program, GLint location,
                                    GLsizei count, Boolean transpose,
                                    const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4fv);
    _api.glProgramUniformMatrix4fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x2dv().
void GLAPI::programUniformMatrix4x2DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x2dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x2dv);
    _api.glProgramUniformMatrix4x2dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x2fv().
void GLAPI::programUniformMatrix4x2FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x2fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x2fv);
    _api.glProgramUniformMatrix4x2fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x3dv().
void GLAPI::programUniformMatrix4x3DV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x3dv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x3dv);
    _api.glProgramUniformMatrix4x3dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x3fv().
void GLAPI::programUniformMatrix4x3FV(ProgramName program, GLint location,
                                      GLsizei count, Boolean transpose,
                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x3fv";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x3fv);
    _api.glProgramUniformMatrix4x3fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glReleaseShaderCompiler().
void GLAPI::releaseShaderCompiler() const
{
    static const char *fnName = "glReleaseShaderCompiler";

    beforeCommand(fnName, _api.glReleaseShaderCompiler);
    _api.glReleaseShaderCompiler();
    afterCommand(fnName);
}

// Calls glScissorArrayv().
void GLAPI::scissorArrayV(GLuint first, GLsizei count, const GLint *v) const
{
    static const char *fnName = "glScissorArrayv";

    beforeCommand(fnName, _api.glScissorArrayv);
    _api.glScissorArrayv(first, count, v);
    afterCommand(fnName);
}

// Calls glScissorIndexed().
void GLAPI::scissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width,
                           GLsizei height) const
{
    static const char *fnName = "glScissorIndexed";

    beforeCommand(fnName, _api.glScissorIndexed);
    _api.glScissorIndexed(index, left, bottom, width, height);
    afterCommand(fnName);
}

// Calls glScissorIndexedv().
void GLAPI::scissorIndexedv(GLuint index, const GLint *v) const
{
    static const char *fnName = "glScissorIndexedv";

    beforeCommand(fnName, _api.glScissorIndexedv);
    _api.glScissorIndexedv(index, v);
    afterCommand(fnName);
}

// Calls glShaderBinary().
void GLAPI::shaderBinary(GLsizei count, const ShaderName *shaders,
                         ShaderBinaryFormat binaryFormat, const void *binary,
                         GLsizei length) const
{
    static const char *fnName = "glShaderBinary";

    beforeCommand(fnName, _api.glShaderBinary);
    _api.glShaderBinary(count, reinterpret_cast<const GLuint *>(shaders),
                        toScalar(binaryFormat), binary, length);
    afterCommand(fnName);
}

// Calls glUseProgramStages().
void GLAPI::useProgramStages(ProgramPipelineName pipeline,
                             GLbitfield  /* UseProgramStageMask */ stages,
                             ProgramName program) const
{
    static const char *fnName = "glUseProgramStages";

    beforeCommand(fnName, _api.glUseProgramStages);
    _api.glUseProgramStages(pipeline.ID, stages, program.ID);
    afterCommand(fnName);
}

// Calls glValidateProgramPipeline().
void GLAPI::validateProgramPipeline(ProgramPipelineName pipeline) const
{
    static const char *fnName = "glValidateProgramPipeline";

    beforeCommand(fnName, _api.glValidateProgramPipeline);
    _api.glValidateProgramPipeline(pipeline.ID);
    afterCommand(fnName);
}

// Calls glVertexAttribL1d().
void GLAPI::vertexAttribL1D(GLuint index, GLdouble x) const
{
    static const char *fnName = "glVertexAttribL1d";

    beforeCommand(fnName, _api.glVertexAttribL1d);
    _api.glVertexAttribL1d(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribL1dv().
void GLAPI::vertexAttribL1DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL1dv";

    beforeCommand(fnName, _api.glVertexAttribL1dv);
    _api.glVertexAttribL1dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL2d().
void GLAPI::vertexAttribL2D(GLuint index, GLdouble x, GLdouble y) const
{
    static const char *fnName = "glVertexAttribL2d";

    beforeCommand(fnName, _api.glVertexAttribL2d);
    _api.glVertexAttribL2d(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribL2dv().
void GLAPI::vertexAttribL2DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL2dv";

    beforeCommand(fnName, _api.glVertexAttribL2dv);
    _api.glVertexAttribL2dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL3d().
void GLAPI::vertexAttribL3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glVertexAttribL3d";

    beforeCommand(fnName, _api.glVertexAttribL3d);
    _api.glVertexAttribL3d(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribL3dv().
void GLAPI::vertexAttribL3DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL3dv";

    beforeCommand(fnName, _api.glVertexAttribL3dv);
    _api.glVertexAttribL3dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL4d().
void GLAPI::vertexAttribL4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                            GLdouble w) const
{
    static const char *fnName = "glVertexAttribL4d";

    beforeCommand(fnName, _api.glVertexAttribL4d);
    _api.glVertexAttribL4d(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribL4dv().
void GLAPI::vertexAttribL4DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL4dv";

    beforeCommand(fnName, _api.glVertexAttribL4dv);
    _api.glVertexAttribL4dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribLPointer().
void GLAPI::vertexAttribLPointer(GLuint index, GLint size,
                                 VertexAttribLType type, GLsizei stride,
                                 const void *pointer) const
{
    static const char *fnName = "glVertexAttribLPointer";

    beforeCommand(fnName, _api.glVertexAttribLPointer);
    _api.glVertexAttribLPointer(index, size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glViewportArrayv().
void GLAPI::viewportArrayV(GLuint first, GLsizei count, const GLfloat *v) const
{
    static const char *fnName = "glViewportArrayv";

    beforeCommand(fnName, _api.glViewportArrayv);
    _api.glViewportArrayv(first, count, v);
    afterCommand(fnName);
}

// Calls glViewportIndexedf().
void GLAPI::viewportIndexedF(GLuint index, GLfloat x, GLfloat y, GLfloat w,
                             GLfloat h) const
{
    static const char *fnName = "glViewportIndexedf";

    beforeCommand(fnName, _api.glViewportIndexedf);
    _api.glViewportIndexedf(index, x, y, w, h);
    afterCommand(fnName);
}

// Calls glViewportIndexedfv().
void GLAPI::viewportIndexedFV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glViewportIndexedfv";

    beforeCommand(fnName, _api.glViewportIndexedfv);
    _api.glViewportIndexedfv(index, v);
    afterCommand(fnName);
}

// Calls glBindImageTexture().
void GLAPI::bindImageTexture(GLuint unit, TextureName texture, GLint level,
                             Boolean layered, GLint layer,
                             BufferAccessARB access, InternalFormat format) const
{
    static const char *fnName = "glBindImageTexture";

    beforeCommand(fnName, _api.glBindImageTexture);
    _api.glBindImageTexture(unit, texture.ID, level, toScalar(layered), layer,
                            toScalar(access), toScalar(format));
    afterCommand(fnName);
}

// Calls glDrawArraysInstancedBaseInstance().
void GLAPI::drawArraysInstancedBaseInstance(PrimitiveType mode, GLint first,
                                            GLsizei count, GLsizei instancecount,
                                            GLuint baseinstance) const
{
    static const char *fnName = "glDrawArraysInstancedBaseInstance";

    beforeCommand(fnName, _api.glDrawArraysInstancedBaseInstance);
    _api.glDrawArraysInstancedBaseInstance(toScalar(mode), first, count,
                                           instancecount, baseinstance);
    afterCommand(fnName);
}

// Calls glDrawElementsInstancedBaseInstance().
void GLAPI::drawElementsInstancedBaseInstance(PrimitiveType mode, GLsizei count,
                                              PrimitiveType type,
                                              const void *indices,
                                              GLsizei instancecount,
                                              GLuint baseinstance) const
{
    static const char *fnName = "glDrawElementsInstancedBaseInstance";

    beforeCommand(fnName, _api.glDrawElementsInstancedBaseInstance);
    _api.glDrawElementsInstancedBaseInstance(toScalar(mode), count,
                                             toScalar(type), indices,
                                             instancecount, baseinstance);
    afterCommand(fnName);
}

// Calls glDrawElementsInstancedBaseVertexBaseInstance().
void GLAPI::drawElementsInstancedBaseVertexBaseInstance(PrimitiveType mode,
                                                        GLsizei count,
                                                        DrawElementsType type,
                                                        const void *indices,
                                                        GLsizei instancecount,
                                                        GLint basevertex,
                                                        GLuint baseinstance) const
{
    static const char *fnName = "glDrawElementsInstancedBaseVertexBaseInstance";

    beforeCommand(fnName, _api.glDrawElementsInstancedBaseVertexBaseInstance);
    _api.glDrawElementsInstancedBaseVertexBaseInstance(toScalar(mode), count,
                                                       toScalar(type), indices,
                                                       instancecount, basevertex,
                                                       baseinstance);
    afterCommand(fnName);
}

// Calls glDrawTransformFeedbackInstanced().
void GLAPI::drawTransformFeedbackInstanced(PrimitiveType mode,
                                           TransformFeedbackName id,
                                           GLsizei instancecount) const
{
    static const char *fnName = "glDrawTransformFeedbackInstanced";

    beforeCommand(fnName, _api.glDrawTransformFeedbackInstanced);
    _api.glDrawTransformFeedbackInstanced(toScalar(mode), id.ID, instancecount);
    afterCommand(fnName);
}

// Calls glDrawTransformFeedbackStreamInstanced().
void GLAPI::drawTransformFeedbackStreamInstanced(PrimitiveType mode,
                                                 TransformFeedbackName id,
                                                 GLuint stream,
                                                 GLsizei instancecount) const
{
    static const char *fnName = "glDrawTransformFeedbackStreamInstanced";

    beforeCommand(fnName, _api.glDrawTransformFeedbackStreamInstanced);
    _api.glDrawTransformFeedbackStreamInstanced(toScalar(mode), id.ID, stream,
                                                instancecount);
    afterCommand(fnName);
}

// Calls glGetActiveAtomicCounterBufferiv().
void GLAPI::getActiveAtomicCounterBufferIV(ProgramName program,
                                           GLuint bufferIndex,
                                           AtomicCounterBufferPName pname,
                                           GLint *params) const
{
    static const char *fnName = "glGetActiveAtomicCounterBufferiv";

    beforeCommand(fnName, _api.glGetActiveAtomicCounterBufferiv);
    _api.glGetActiveAtomicCounterBufferiv(program.ID, bufferIndex,
                                          toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetInternalformativ().
void GLAPI::getInternalformatIV(TextureTarget target,
                                InternalFormat internalformat,
                                InternalFormatPName pname, GLsizei count,
                                GLint *params) const
{
    static const char *fnName = "glGetInternalformativ";

    beforeCommand(fnName, _api.glGetInternalformativ);
    _api.glGetInternalformativ(toScalar(target), toScalar(internalformat),
                               toScalar(pname), count, params);
    afterCommand(fnName);
}

// Calls glMemoryBarrier().
void GLAPI::memoryBarrier(GLbitfield  /* MemoryBarrierMask */ barriers) const
{
    static const char *fnName = "glMemoryBarrier";

    beforeCommand(fnName, _api.glMemoryBarrier);
    _api.glMemoryBarrier(barriers);
    afterCommand(fnName);
}

// Calls glTexStorage1D().
void GLAPI::texStorage1D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalformat, GLsizei width) const
{
    static const char *fnName = "glTexStorage1D";

    beforeCommand(fnName, _api.glTexStorage1D);
    _api.glTexStorage1D(toScalar(target), levels, toScalar(internalformat),
                        width);
    afterCommand(fnName);
}

// Calls glTexStorage2D().
void GLAPI::texStorage2D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalformat, GLsizei width,
                         GLsizei height) const
{
    static const char *fnName = "glTexStorage2D";

    beforeCommand(fnName, _api.glTexStorage2D);
    _api.glTexStorage2D(toScalar(target), levels, toScalar(internalformat),
                        width, height);
    afterCommand(fnName);
}

// Calls glTexStorage3D().
void GLAPI::texStorage3D(TextureTarget target, GLsizei levels,
                         SizedInternalFormat internalformat, GLsizei width,
                         GLsizei height, GLsizei depth) const
{
    static const char *fnName = "glTexStorage3D";

    beforeCommand(fnName, _api.glTexStorage3D);
    _api.glTexStorage3D(toScalar(target), levels, toScalar(internalformat),
                        width, height, depth);
    afterCommand(fnName);
}

// Calls glBindVertexBuffer().
void GLAPI::bindVertexBuffer(GLuint bindingindex, BufferName buffer,
                             GLintptr offset, GLsizei stride) const
{
    static const char *fnName = "glBindVertexBuffer";

    beforeCommand(fnName, _api.glBindVertexBuffer);
    _api.glBindVertexBuffer(bindingindex, buffer.ID, offset, stride);
    afterCommand(fnName);
}

// Calls glClearBufferData().
void GLAPI::clearBufferData(BufferStorageTarget target,
                            SizedInternalFormat internalformat,
                            PixelFormat format, PixelType type, const void *data) const
{
    static const char *fnName = "glClearBufferData";

    beforeCommand(fnName, _api.glClearBufferData);
    _api.glClearBufferData(toScalar(target), toScalar(internalformat),
                           toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glClearBufferSubData().
void GLAPI::clearBufferSubData(BufferTargetARB target,
                               SizedInternalFormat internalformat,
                               GLintptr offset, GLsizeiptr size,
                               PixelFormat format, PixelType type,
                               const void *data) const
{
    static const char *fnName = "glClearBufferSubData";

    beforeCommand(fnName, _api.glClearBufferSubData);
    _api.glClearBufferSubData(toScalar(target), toScalar(internalformat), offset,
                              size, toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glCopyImageSubData().
void GLAPI::copyImageSubData(GLuint srcName, CopyImageSubDataTarget srcTarget,
                             GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ,
                             GLuint dstName, CopyImageSubDataTarget dstTarget,
                             GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
                             GLsizei srcWidth, GLsizei srcHeight,
                             GLsizei srcDepth) const
{
    static const char *fnName = "glCopyImageSubData";

    beforeCommand(fnName, _api.glCopyImageSubData);
    _api.glCopyImageSubData(srcName, toScalar(srcTarget), srcLevel, srcX, srcY,
                            srcZ, dstName, toScalar(dstTarget), dstLevel, dstX,
                            dstY, dstZ, srcWidth, srcHeight, srcDepth);
    afterCommand(fnName);
}

// Calls glDebugMessageCallback().
void GLAPI::debugMessageCallback(GLDEBUGPROC callback, const void *userParam) const
{
    static const char *fnName = "glDebugMessageCallback";

    beforeCommand(fnName, _api.glDebugMessageCallback);
    _api.glDebugMessageCallback(callback, userParam);
    afterCommand(fnName);
}

// Calls glDebugMessageControl().
void GLAPI::debugMessageControl(DebugSource source, DebugType type,
                                DebugSeverity severity, GLsizei count,
                                const GLuint *ids, Boolean enabled) const
{
    static const char *fnName = "glDebugMessageControl";

    beforeCommand(fnName, _api.glDebugMessageControl);
    _api.glDebugMessageControl(toScalar(source), toScalar(type),
                               toScalar(severity), count, ids, toScalar(enabled));
    afterCommand(fnName);
}

// Calls glDebugMessageInsert().
void GLAPI::debugMessageInsert(DebugSource source, DebugType type, GLuint id,
                               DebugSeverity severity, GLsizei length,
                               const GLchar *buf) const
{
    static const char *fnName = "glDebugMessageInsert";

    beforeCommand(fnName, _api.glDebugMessageInsert);
    _api.glDebugMessageInsert(toScalar(source), toScalar(type), id,
                              toScalar(severity), length, buf);
    afterCommand(fnName);
}

// Calls glDispatchCompute().
void GLAPI::dispatchCompute(GLuint num_groups_x, GLuint num_groups_y,
                            GLuint num_groups_z) const
{
    static const char *fnName = "glDispatchCompute";

    beforeCommand(fnName, _api.glDispatchCompute);
    _api.glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
    afterCommand(fnName);
}

// Calls glDispatchComputeIndirect().
void GLAPI::dispatchComputeIndirect(GLintptr indirect) const
{
    static const char *fnName = "glDispatchComputeIndirect";

    beforeCommand(fnName, _api.glDispatchComputeIndirect);
    _api.glDispatchComputeIndirect(indirect);
    afterCommand(fnName);
}

// Calls glFramebufferParameteri().
void GLAPI::framebufferParameterI(FramebufferTarget target,
                                  FramebufferParameterName pname, GLint param) const
{
    static const char *fnName = "glFramebufferParameteri";

    beforeCommand(fnName, _api.glFramebufferParameteri);
    _api.glFramebufferParameteri(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetDebugMessageLog().
GLuint GLAPI::getDebugMessageLog(GLuint count, GLsizei bufSize,
                                 DebugSource *sources, DebugType *types,
                                 GLuint *ids, DebugSeverity *severities,
                                 GLsizei *lengths, GLchar *messageLog) const
{
    static const char *fnName = "glGetDebugMessageLog";

    beforeCommand(fnName, _api.glGetDebugMessageLog);
    GLuint result = _api.glGetDebugMessageLog(count, bufSize,
                                              toScalarPtr(sources),
                                              toScalarPtr(types), ids,
                                              toScalarPtr(severities), lengths,
                                              messageLog);
    afterCommand(fnName);

    return result;
}

// Calls glGetFramebufferParameteriv().
void GLAPI::getFramebufferParameterIV(FramebufferTarget target,
                                      FramebufferAttachmentParameterName pname,
                                      GLint *params) const
{
    static const char *fnName = "glGetFramebufferParameteriv";

    beforeCommand(fnName, _api.glGetFramebufferParameteriv);
    _api.glGetFramebufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetInternalformati64v().
void GLAPI::getInternalformatI64V(TextureTarget target,
                                  InternalFormat internalformat,
                                  InternalFormatPName pname, GLsizei count,
                                  GLint64 *params) const
{
    static const char *fnName = "glGetInternalformati64v";

    beforeCommand(fnName, _api.glGetInternalformati64v);
    _api.glGetInternalformati64v(toScalar(target), toScalar(internalformat),
                                 toScalar(pname), count, params);
    afterCommand(fnName);
}

// Calls glGetObjectLabel().
void GLAPI::getObjectLabel(ObjectIdentifier identifier, GLuint name,
                           GLsizei bufSize, GLsizei *length, GLchar *label) const
{
    static const char *fnName = "glGetObjectLabel";

    beforeCommand(fnName, _api.glGetObjectLabel);
    _api.glGetObjectLabel(toScalar(identifier), name, bufSize, length, label);
    afterCommand(fnName);
}

// Calls glGetObjectPtrLabel().
void GLAPI::getObjectPtrLabel(const void *ptr, GLsizei bufSize, GLsizei *length,
                              GLchar *label) const
{
    static const char *fnName = "glGetObjectPtrLabel";

    beforeCommand(fnName, _api.glGetObjectPtrLabel);
    _api.glGetObjectPtrLabel(ptr, bufSize, length, label);
    afterCommand(fnName);
}

// Calls glGetPointerv().
void GLAPI::getPointerV(GetPointervPName pname, void **params) const
{
    static const char *fnName = "glGetPointerv";

    beforeCommand(fnName, _api.glGetPointerv);
    _api.glGetPointerv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetProgramInterfaceiv().
void GLAPI::getProgramInterfaceIV(ProgramName program,
                                  ProgramInterface programInterface,
                                  ProgramInterfacePName pname, GLint *params) const
{
    static const char *fnName = "glGetProgramInterfaceiv";

    beforeCommand(fnName, _api.glGetProgramInterfaceiv);
    _api.glGetProgramInterfaceiv(program.ID, toScalar(programInterface),
                                 toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetProgramResourceIndex().
GLuint GLAPI::getProgramResourceIndex(ProgramName program,
                                      ProgramInterface programInterface,
                                      const GLchar *name) const
{
    static const char *fnName = "glGetProgramResourceIndex";

    beforeCommand(fnName, _api.glGetProgramResourceIndex);
    GLuint result = _api.glGetProgramResourceIndex(program.ID,
                                                   toScalar(programInterface),
                                                   name);
    afterCommand(fnName);

    return result;
}

// Calls glGetProgramResourceLocation().
GLint GLAPI::getProgramResourceLocation(ProgramName program,
                                        ProgramInterface programInterface,
                                        const GLchar *name) const
{
    static const char *fnName = "glGetProgramResourceLocation";

    beforeCommand(fnName, _api.glGetProgramResourceLocation);
    GLint result = _api.glGetProgramResourceLocation(program.ID,
                                                     toScalar(programInterface),
                                                     name);
    afterCommand(fnName);

    return result;
}

// Calls glGetProgramResourceLocationIndex().
GLint GLAPI::getProgramResourceLocationIndex(ProgramName program,
                                             ProgramInterface programInterface,
                                             const GLchar *name) const
{
    static const char *fnName = "glGetProgramResourceLocationIndex";

    beforeCommand(fnName, _api.glGetProgramResourceLocationIndex);
    GLint result = _api.glGetProgramResourceLocationIndex(program.ID,
                                                          toScalar(programInterface),
                                                          name);
    afterCommand(fnName);

    return result;
}

// Calls glGetProgramResourceName().
void GLAPI::getProgramResourceName(ProgramName program,
                                   ProgramInterface programInterface,
                                   GLuint index, GLsizei bufSize,
                                   GLsizei *length, GLchar *name) const
{
    static const char *fnName = "glGetProgramResourceName";

    beforeCommand(fnName, _api.glGetProgramResourceName);
    _api.glGetProgramResourceName(program.ID, toScalar(programInterface), index,
                                  bufSize, length, name);
    afterCommand(fnName);
}

// Calls glGetProgramResourceiv().
void GLAPI::getProgramResourceIV(ProgramName program,
                                 ProgramInterface programInterface, GLuint index,
                                 GLsizei propCount,
                                 const ProgramResourceProperty *props,
                                 GLsizei count, GLsizei *length, GLint *params) const
{
    static const char *fnName = "glGetProgramResourceiv";

    beforeCommand(fnName, _api.glGetProgramResourceiv);
    _api.glGetProgramResourceiv(program.ID, toScalar(programInterface), index,
                                propCount, toScalarPtr(props), count, length,
                                params);
    afterCommand(fnName);
}

// Calls glInvalidateBufferData().
void GLAPI::invalidateBufferData(BufferName buffer) const
{
    static const char *fnName = "glInvalidateBufferData";

    beforeCommand(fnName, _api.glInvalidateBufferData);
    _api.glInvalidateBufferData(buffer.ID);
    afterCommand(fnName);
}

// Calls glInvalidateBufferSubData().
void GLAPI::invalidateBufferSubData(BufferName buffer, GLintptr offset,
                                    GLsizeiptr length) const
{
    static const char *fnName = "glInvalidateBufferSubData";

    beforeCommand(fnName, _api.glInvalidateBufferSubData);
    _api.glInvalidateBufferSubData(buffer.ID, offset, length);
    afterCommand(fnName);
}

// Calls glInvalidateFramebuffer().
void GLAPI::invalidateFramebuffer(FramebufferTarget target,
                                  GLsizei numAttachments,
                                  const InvalidateFramebufferAttachment *attachments) const
{
    static const char *fnName = "glInvalidateFramebuffer";

    beforeCommand(fnName, _api.glInvalidateFramebuffer);
    _api.glInvalidateFramebuffer(toScalar(target), numAttachments,
                                 toScalarPtr(attachments));
    afterCommand(fnName);
}

// Calls glInvalidateSubFramebuffer().
void GLAPI::invalidateSubFramebuffer(FramebufferTarget target,
                                     GLsizei numAttachments,
                                     const InvalidateFramebufferAttachment *attachments,
                                     GLint x, GLint y, GLsizei width,
                                     GLsizei height) const
{
    static const char *fnName = "glInvalidateSubFramebuffer";

    beforeCommand(fnName, _api.glInvalidateSubFramebuffer);
    _api.glInvalidateSubFramebuffer(toScalar(target), numAttachments,
                                    toScalarPtr(attachments), x, y, width,
                                    height);
    afterCommand(fnName);
}

// Calls glInvalidateTexImage().
void GLAPI::invalidateTexImage(TextureName texture, GLint level) const
{
    static const char *fnName = "glInvalidateTexImage";

    beforeCommand(fnName, _api.glInvalidateTexImage);
    _api.glInvalidateTexImage(texture.ID, level);
    afterCommand(fnName);
}

// Calls glInvalidateTexSubImage().
void GLAPI::invalidateTexSubImage(TextureName texture, GLint level,
                                  GLint xoffset, GLint yoffset, GLint zoffset,
                                  GLsizei width, GLsizei height, GLsizei depth) const
{
    static const char *fnName = "glInvalidateTexSubImage";

    beforeCommand(fnName, _api.glInvalidateTexSubImage);
    _api.glInvalidateTexSubImage(texture.ID, level, xoffset, yoffset, zoffset,
                                 width, height, depth);
    afterCommand(fnName);
}

// Calls glMultiDrawArraysIndirect().
void GLAPI::multiDrawArraysIndirect(PrimitiveType mode, const void *indirect,
                                    GLsizei drawcount, GLsizei stride) const
{
    static const char *fnName = "glMultiDrawArraysIndirect";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirect);
    _api.glMultiDrawArraysIndirect(toScalar(mode), indirect, drawcount, stride);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirect().
void GLAPI::multiDrawElementsIndirect(PrimitiveType mode, DrawElementsType type,
                                      const void *indirect, GLsizei drawcount,
                                      GLsizei stride) const
{
    static const char *fnName = "glMultiDrawElementsIndirect";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirect);
    _api.glMultiDrawElementsIndirect(toScalar(mode), toScalar(type), indirect,
                                     drawcount, stride);
    afterCommand(fnName);
}

// Calls glObjectLabel().
void GLAPI::objectLabel(ObjectIdentifier identifier, GLuint name, GLsizei length,
                        const GLchar *label) const
{
    static const char *fnName = "glObjectLabel";

    beforeCommand(fnName, _api.glObjectLabel);
    _api.glObjectLabel(toScalar(identifier), name, length, label);
    afterCommand(fnName);
}

// Calls glObjectPtrLabel().
void GLAPI::objectPtrLabel(const void *ptr, GLsizei length, const GLchar *label) const
{
    static const char *fnName = "glObjectPtrLabel";

    beforeCommand(fnName, _api.glObjectPtrLabel);
    _api.glObjectPtrLabel(ptr, length, label);
    afterCommand(fnName);
}

// Calls glPopDebugGroup().
void GLAPI::popDebugGroup() const
{
    static const char *fnName = "glPopDebugGroup";

    beforeCommand(fnName, _api.glPopDebugGroup);
    _api.glPopDebugGroup();
    afterCommand(fnName);
}

// Calls glPushDebugGroup().
void GLAPI::pushDebugGroup(DebugSource source, GLuint id, GLsizei length,
                           const GLchar *message) const
{
    static const char *fnName = "glPushDebugGroup";

    beforeCommand(fnName, _api.glPushDebugGroup);
    _api.glPushDebugGroup(toScalar(source), id, length, message);
    afterCommand(fnName);
}

// Calls glShaderStorageBlockBinding().
void GLAPI::shaderStorageBlockBinding(ProgramName program,
                                      GLuint storageBlockIndex,
                                      GLuint storageBlockBinding) const
{
    static const char *fnName = "glShaderStorageBlockBinding";

    beforeCommand(fnName, _api.glShaderStorageBlockBinding);
    _api.glShaderStorageBlockBinding(program.ID, storageBlockIndex,
                                     storageBlockBinding);
    afterCommand(fnName);
}

// Calls glTexBufferRange().
void GLAPI::texBufferRange(TextureTarget target,
                           SizedInternalFormat internalformat, BufferName buffer,
                           GLintptr offset, GLsizeiptr size) const
{
    static const char *fnName = "glTexBufferRange";

    beforeCommand(fnName, _api.glTexBufferRange);
    _api.glTexBufferRange(toScalar(target), toScalar(internalformat), buffer.ID,
                          offset, size);
    afterCommand(fnName);
}

// Calls glTexStorage2DMultisample().
void GLAPI::texStorage2DMultisample(TextureTarget target, GLsizei samples,
                                    SizedInternalFormat internalformat,
                                    GLsizei width, GLsizei height,
                                    Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTexStorage2DMultisample";

    beforeCommand(fnName, _api.glTexStorage2DMultisample);
    _api.glTexStorage2DMultisample(toScalar(target), samples,
                                   toScalar(internalformat), width, height,
                                   toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTexStorage3DMultisample().
void GLAPI::texStorage3DMultisample(TextureTarget target, GLsizei samples,
                                    SizedInternalFormat internalformat,
                                    GLsizei width, GLsizei height, GLsizei depth,
                                    Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTexStorage3DMultisample";

    beforeCommand(fnName, _api.glTexStorage3DMultisample);
    _api.glTexStorage3DMultisample(toScalar(target), samples,
                                   toScalar(internalformat), width, height,
                                   depth, toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTextureView().
void GLAPI::textureView(TextureName texture, TextureTarget target,
                        TextureName origtexture,
                        SizedInternalFormat internalformat, GLuint minlevel,
                        GLuint numlevels, GLuint minlayer, GLuint numlayers) const
{
    static const char *fnName = "glTextureView";

    beforeCommand(fnName, _api.glTextureView);
    _api.glTextureView(texture.ID, toScalar(target), origtexture.ID,
                       toScalar(internalformat), minlevel, numlevels, minlayer,
                       numlayers);
    afterCommand(fnName);
}

// Calls glVertexAttribBinding().
void GLAPI::vertexAttribBinding(GLuint attribindex, GLuint bindingindex) const
{
    static const char *fnName = "glVertexAttribBinding";

    beforeCommand(fnName, _api.glVertexAttribBinding);
    _api.glVertexAttribBinding(attribindex, bindingindex);
    afterCommand(fnName);
}

// Calls glVertexAttribFormat().
void GLAPI::vertexAttribFormat(GLuint attribindex, GLint size,
                               VertexAttribType type, Boolean normalized,
                               GLuint relativeoffset) const
{
    static const char *fnName = "glVertexAttribFormat";

    beforeCommand(fnName, _api.glVertexAttribFormat);
    _api.glVertexAttribFormat(attribindex, size, toScalar(type),
                              toScalar(normalized), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexAttribIFormat().
void GLAPI::vertexAttribIFormat(GLuint attribindex, GLint size,
                                VertexAttribIType type, GLuint relativeoffset) const
{
    static const char *fnName = "glVertexAttribIFormat";

    beforeCommand(fnName, _api.glVertexAttribIFormat);
    _api.glVertexAttribIFormat(attribindex, size, toScalar(type), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexAttribLFormat().
void GLAPI::vertexAttribLFormat(GLuint attribindex, GLint size,
                                VertexAttribLType type, GLuint relativeoffset) const
{
    static const char *fnName = "glVertexAttribLFormat";

    beforeCommand(fnName, _api.glVertexAttribLFormat);
    _api.glVertexAttribLFormat(attribindex, size, toScalar(type), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexBindingDivisor().
void GLAPI::vertexBindingDivisor(GLuint bindingindex, GLuint divisor) const
{
    static const char *fnName = "glVertexBindingDivisor";

    beforeCommand(fnName, _api.glVertexBindingDivisor);
    _api.glVertexBindingDivisor(bindingindex, divisor);
    afterCommand(fnName);
}

// Calls glBindBuffersBase().
void GLAPI::bindBuffersBase(BufferTargetARB target, GLuint first, GLsizei count,
                            const BufferName *buffers) const
{
    static const char *fnName = "glBindBuffersBase";

    beforeCommand(fnName, _api.glBindBuffersBase);
    _api.glBindBuffersBase(toScalar(target), first, count,
                           reinterpret_cast<const GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glBindBuffersRange().
void GLAPI::bindBuffersRange(BufferTargetARB target, GLuint first, GLsizei count,
                             const BufferName *buffers, const GLintptr *offsets,
                             const GLsizeiptr *sizes) const
{
    static const char *fnName = "glBindBuffersRange";

    beforeCommand(fnName, _api.glBindBuffersRange);
    _api.glBindBuffersRange(toScalar(target), first, count,
                            reinterpret_cast<const GLuint *>(buffers), offsets,
                            sizes);
    afterCommand(fnName);
}

// Calls glBindImageTextures().
void GLAPI::bindImageTextures(GLuint first, GLsizei count,
                              const TextureName *textures) const
{
    static const char *fnName = "glBindImageTextures";

    beforeCommand(fnName, _api.glBindImageTextures);
    _api.glBindImageTextures(first, count,
                             reinterpret_cast<const GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glBindSamplers().
void GLAPI::bindSamplers(GLuint first, GLsizei count,
                         const SamplerName *samplers) const
{
    static const char *fnName = "glBindSamplers";

    beforeCommand(fnName, _api.glBindSamplers);
    _api.glBindSamplers(first, count, reinterpret_cast<const GLuint *>(samplers));
    afterCommand(fnName);
}

// Calls glBindTextures().
void GLAPI::bindTextures(GLuint first, GLsizei count,
                         const TextureName *textures) const
{
    static const char *fnName = "glBindTextures";

    beforeCommand(fnName, _api.glBindTextures);
    _api.glBindTextures(first, count, reinterpret_cast<const GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glBindVertexBuffers().
void GLAPI::bindVertexBuffers(GLuint first, GLsizei count,
                              const BufferName *buffers, const GLintptr *offsets,
                              const GLsizei *strides) const
{
    static const char *fnName = "glBindVertexBuffers";

    beforeCommand(fnName, _api.glBindVertexBuffers);
    _api.glBindVertexBuffers(first, count,
                             reinterpret_cast<const GLuint *>(buffers), offsets,
                             strides);
    afterCommand(fnName);
}

// Calls glBufferStorage().
void GLAPI::bufferStorage(BufferStorageTarget target, GLsizeiptr size,
                          const void *data,
                          GLbitfield  /* BufferStorageMask */ flags) const
{
    static const char *fnName = "glBufferStorage";

    beforeCommand(fnName, _api.glBufferStorage);
    _api.glBufferStorage(toScalar(target), size, data, flags);
    afterCommand(fnName);
}

// Calls glClearTexImage().
void GLAPI::clearTexImage(TextureName texture, GLint level, PixelFormat format,
                          PixelType type, const void *data) const
{
    static const char *fnName = "glClearTexImage";

    beforeCommand(fnName, _api.glClearTexImage);
    _api.glClearTexImage(texture.ID, level, toScalar(format), toScalar(type),
                         data);
    afterCommand(fnName);
}

// Calls glClearTexSubImage().
void GLAPI::clearTexSubImage(TextureName texture, GLint level, GLint xoffset,
                             GLint yoffset, GLint zoffset, GLsizei width,
                             GLsizei height, GLsizei depth, PixelFormat format,
                             PixelType type, const void *data) const
{
    static const char *fnName = "glClearTexSubImage";

    beforeCommand(fnName, _api.glClearTexSubImage);
    _api.glClearTexSubImage(texture.ID, level, xoffset, yoffset, zoffset, width,
                            height, depth, toScalar(format), toScalar(type),
                            data);
    afterCommand(fnName);
}

// Calls glBindTextureUnit().
void GLAPI::bindTextureUnit(GLuint unit, TextureName texture) const
{
    static const char *fnName = "glBindTextureUnit";

    beforeCommand(fnName, _api.glBindTextureUnit);
    _api.glBindTextureUnit(unit, texture.ID);
    afterCommand(fnName);
}

// Calls glBlitNamedFramebuffer().
void GLAPI::blitNamedFramebuffer(FramebufferName readFramebuffer,
                                 FramebufferName drawFramebuffer, GLint srcX0,
                                 GLint srcY0, GLint srcX1, GLint srcY1,
                                 GLint dstX0, GLint dstY0, GLint dstX1,
                                 GLint dstY1,
                                 GLbitfield  /* ClearBufferMask */ mask,
                                 BlitFramebufferFilter filter) const
{
    static const char *fnName = "glBlitNamedFramebuffer";

    beforeCommand(fnName, _api.glBlitNamedFramebuffer);
    _api.glBlitNamedFramebuffer(readFramebuffer.ID, drawFramebuffer.ID, srcX0,
                                srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,
                                mask, toScalar(filter));
    afterCommand(fnName);
}

// Calls glCheckNamedFramebufferStatus().
FramebufferStatus GLAPI::checkNamedFramebufferStatus(FramebufferName framebuffer,
                                                     FramebufferTarget target) const
{
    static const char *fnName = "glCheckNamedFramebufferStatus";

    beforeCommand(fnName, _api.glCheckNamedFramebufferStatus);
    GLenum result = _api.glCheckNamedFramebufferStatus(framebuffer.ID,
                                                       toScalar(target));
    afterCommand(fnName);

    return static_cast<FramebufferStatus>(result);
}

// Calls glClearNamedBufferData().
void GLAPI::clearNamedBufferData(BufferName buffer,
                                 SizedInternalFormat internalformat,
                                 PixelFormat format, PixelType type,
                                 const void *data) const
{
    static const char *fnName = "glClearNamedBufferData";

    beforeCommand(fnName, _api.glClearNamedBufferData);
    _api.glClearNamedBufferData(buffer.ID, toScalar(internalformat),
                                toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glClearNamedBufferSubData().
void GLAPI::clearNamedBufferSubData(BufferName buffer,
                                    SizedInternalFormat internalformat,
                                    GLintptr offset, GLsizeiptr size,
                                    PixelFormat format, PixelType type,
                                    const void *data) const
{
    static const char *fnName = "glClearNamedBufferSubData";

    beforeCommand(fnName, _api.glClearNamedBufferSubData);
    _api.glClearNamedBufferSubData(buffer.ID, toScalar(internalformat), offset,
                                   size, toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glClearNamedFramebufferfi().
void GLAPI::clearNamedFramebufferFI(FramebufferName framebuffer,
                                    BufferEnum buffer, GLint drawbuffer,
                                    GLfloat depth, GLint stencil) const
{
    static const char *fnName = "glClearNamedFramebufferfi";

    beforeCommand(fnName, _api.glClearNamedFramebufferfi);
    _api.glClearNamedFramebufferfi(framebuffer.ID, toScalar(buffer), drawbuffer,
                                   depth, stencil);
    afterCommand(fnName);
}

// Calls glClearNamedFramebufferfv().
void GLAPI::clearNamedFramebufferFV(FramebufferName framebuffer,
                                    BufferEnum buffer, GLint drawbuffer,
                                    const GLfloat *value) const
{
    static const char *fnName = "glClearNamedFramebufferfv";

    beforeCommand(fnName, _api.glClearNamedFramebufferfv);
    _api.glClearNamedFramebufferfv(framebuffer.ID, toScalar(buffer), drawbuffer,
                                   value);
    afterCommand(fnName);
}

// Calls glClearNamedFramebufferiv().
void GLAPI::clearNamedFramebufferIV(FramebufferName framebuffer,
                                    BufferEnum buffer, GLint drawbuffer,
                                    const GLint *value) const
{
    static const char *fnName = "glClearNamedFramebufferiv";

    beforeCommand(fnName, _api.glClearNamedFramebufferiv);
    _api.glClearNamedFramebufferiv(framebuffer.ID, toScalar(buffer), drawbuffer,
                                   value);
    afterCommand(fnName);
}

// Calls glClearNamedFramebufferuiv().
void GLAPI::clearNamedFramebufferUIV(FramebufferName framebuffer,
                                     BufferEnum buffer, GLint drawbuffer,
                                     const GLuint *value) const
{
    static const char *fnName = "glClearNamedFramebufferuiv";

    beforeCommand(fnName, _api.glClearNamedFramebufferuiv);
    _api.glClearNamedFramebufferuiv(framebuffer.ID, toScalar(buffer), drawbuffer,
                                    value);
    afterCommand(fnName);
}

// Calls glClipControl().
void GLAPI::clipControl(ClipControlOrigin origin, ClipControlDepth depth) const
{
    static const char *fnName = "glClipControl";

    beforeCommand(fnName, _api.glClipControl);
    _api.glClipControl(toScalar(origin), toScalar(depth));
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage1D().
void GLAPI::compressedTextureSubImage1D(TextureName texture, GLint level,
                                        GLint xoffset, GLsizei width,
                                        InternalFormat format, GLsizei imageSize,
                                        const void *data) const
{
    static const char *fnName = "glCompressedTextureSubImage1D";

    beforeCommand(fnName, _api.glCompressedTextureSubImage1D);
    _api.glCompressedTextureSubImage1D(texture.ID, level, xoffset, width,
                                       toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage2D().
void GLAPI::compressedTextureSubImage2D(TextureName texture, GLint level,
                                        GLint xoffset, GLint yoffset,
                                        GLsizei width, GLsizei height,
                                        InternalFormat format, GLsizei imageSize,
                                        const void *data) const
{
    static const char *fnName = "glCompressedTextureSubImage2D";

    beforeCommand(fnName, _api.glCompressedTextureSubImage2D);
    _api.glCompressedTextureSubImage2D(texture.ID, level, xoffset, yoffset,
                                       width, height, toScalar(format),
                                       imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage3D().
void GLAPI::compressedTextureSubImage3D(TextureName texture, GLint level,
                                        GLint xoffset, GLint yoffset,
                                        GLint zoffset, GLsizei width,
                                        GLsizei height, GLsizei depth,
                                        InternalFormat format, GLsizei imageSize,
                                        const void *data) const
{
    static const char *fnName = "glCompressedTextureSubImage3D";

    beforeCommand(fnName, _api.glCompressedTextureSubImage3D);
    _api.glCompressedTextureSubImage3D(texture.ID, level, xoffset, yoffset,
                                       zoffset, width, height, depth,
                                       toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glCopyNamedBufferSubData().
void GLAPI::copyNamedBufferSubData(BufferName readBuffer, BufferName writeBuffer,
                                   GLintptr readOffset, GLintptr writeOffset,
                                   GLsizeiptr size) const
{
    static const char *fnName = "glCopyNamedBufferSubData";

    beforeCommand(fnName, _api.glCopyNamedBufferSubData);
    _api.glCopyNamedBufferSubData(readBuffer.ID, writeBuffer.ID, readOffset,
                                  writeOffset, size);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage1D().
void GLAPI::copyTextureSubImage1D(TextureName texture, GLint level,
                                  GLint xoffset, GLint x, GLint y, GLsizei width) const
{
    static const char *fnName = "glCopyTextureSubImage1D";

    beforeCommand(fnName, _api.glCopyTextureSubImage1D);
    _api.glCopyTextureSubImage1D(texture.ID, level, xoffset, x, y, width);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage2D().
void GLAPI::copyTextureSubImage2D(TextureName texture, GLint level,
                                  GLint xoffset, GLint yoffset, GLint x, GLint y,
                                  GLsizei width, GLsizei height) const
{
    static const char *fnName = "glCopyTextureSubImage2D";

    beforeCommand(fnName, _api.glCopyTextureSubImage2D);
    _api.glCopyTextureSubImage2D(texture.ID, level, xoffset, yoffset, x, y,
                                 width, height);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage3D().
void GLAPI::copyTextureSubImage3D(TextureName texture, GLint level,
                                  GLint xoffset, GLint yoffset, GLint zoffset,
                                  GLint x, GLint y, GLsizei width,
                                  GLsizei height) const
{
    static const char *fnName = "glCopyTextureSubImage3D";

    beforeCommand(fnName, _api.glCopyTextureSubImage3D);
    _api.glCopyTextureSubImage3D(texture.ID, level, xoffset, yoffset, zoffset, x,
                                 y, width, height);
    afterCommand(fnName);
}

// Calls glCreateBuffers().
void GLAPI::createBuffers(GLsizei n, BufferName *buffers) const
{
    static const char *fnName = "glCreateBuffers";

    beforeCommand(fnName, _api.glCreateBuffers);
    _api.glCreateBuffers(n, reinterpret_cast<GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glCreateFramebuffers().
void GLAPI::createFramebuffers(GLsizei n, FramebufferName *framebuffers) const
{
    static const char *fnName = "glCreateFramebuffers";

    beforeCommand(fnName, _api.glCreateFramebuffers);
    _api.glCreateFramebuffers(n, reinterpret_cast<GLuint *>(framebuffers));
    afterCommand(fnName);
}

// Calls glCreateProgramPipelines().
void GLAPI::createProgramPipelines(GLsizei n, ProgramPipelineName *pipelines) const
{
    static const char *fnName = "glCreateProgramPipelines";

    beforeCommand(fnName, _api.glCreateProgramPipelines);
    _api.glCreateProgramPipelines(n, reinterpret_cast<GLuint *>(pipelines));
    afterCommand(fnName);
}

// Calls glCreateQueries().
void GLAPI::createQueries(QueryTarget target, GLsizei n, QueryName *ids) const
{
    static const char *fnName = "glCreateQueries";

    beforeCommand(fnName, _api.glCreateQueries);
    _api.glCreateQueries(toScalar(target), n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glCreateRenderbuffers().
void GLAPI::createRenderbuffers(GLsizei n, RenderbufferName *renderbuffers) const
{
    static const char *fnName = "glCreateRenderbuffers";

    beforeCommand(fnName, _api.glCreateRenderbuffers);
    _api.glCreateRenderbuffers(n, reinterpret_cast<GLuint *>(renderbuffers));
    afterCommand(fnName);
}

// Calls glCreateSamplers().
void GLAPI::createSamplers(GLsizei n, SamplerName *samplers) const
{
    static const char *fnName = "glCreateSamplers";

    beforeCommand(fnName, _api.glCreateSamplers);
    _api.glCreateSamplers(n, reinterpret_cast<GLuint *>(samplers));
    afterCommand(fnName);
}

// Calls glCreateTextures().
void GLAPI::createTextures(TextureTarget target, GLsizei n,
                           TextureName *textures) const
{
    static const char *fnName = "glCreateTextures";

    beforeCommand(fnName, _api.glCreateTextures);
    _api.glCreateTextures(toScalar(target), n,
                          reinterpret_cast<GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glCreateTransformFeedbacks().
void GLAPI::createTransformFeedbacks(GLsizei n, TransformFeedbackName *ids) const
{
    static const char *fnName = "glCreateTransformFeedbacks";

    beforeCommand(fnName, _api.glCreateTransformFeedbacks);
    _api.glCreateTransformFeedbacks(n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glCreateVertexArrays().
void GLAPI::createVertexArrays(GLsizei n, VertexArrayName *arrays) const
{
    static const char *fnName = "glCreateVertexArrays";

    beforeCommand(fnName, _api.glCreateVertexArrays);
    _api.glCreateVertexArrays(n, reinterpret_cast<GLuint *>(arrays));
    afterCommand(fnName);
}

// Calls glDisableVertexArrayAttrib().
void GLAPI::disableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const
{
    static const char *fnName = "glDisableVertexArrayAttrib";

    beforeCommand(fnName, _api.glDisableVertexArrayAttrib);
    _api.glDisableVertexArrayAttrib(vaobj.ID, index);
    afterCommand(fnName);
}

// Calls glEnableVertexArrayAttrib().
void GLAPI::enableVertexArrayAttrib(VertexArrayName vaobj, GLuint index) const
{
    static const char *fnName = "glEnableVertexArrayAttrib";

    beforeCommand(fnName, _api.glEnableVertexArrayAttrib);
    _api.glEnableVertexArrayAttrib(vaobj.ID, index);
    afterCommand(fnName);
}

// Calls glFlushMappedNamedBufferRange().
void GLAPI::flushMappedNamedBufferRange(BufferName buffer, GLintptr offset,
                                        GLsizeiptr length) const
{
    static const char *fnName = "glFlushMappedNamedBufferRange";

    beforeCommand(fnName, _api.glFlushMappedNamedBufferRange);
    _api.glFlushMappedNamedBufferRange(buffer.ID, offset, length);
    afterCommand(fnName);
}

// Calls glGenerateTextureMipmap().
void GLAPI::generateTextureMipmap(TextureName texture) const
{
    static const char *fnName = "glGenerateTextureMipmap";

    beforeCommand(fnName, _api.glGenerateTextureMipmap);
    _api.glGenerateTextureMipmap(texture.ID);
    afterCommand(fnName);
}

// Calls glGetCompressedTextureImage().
void GLAPI::getCompressedTextureImage(TextureName texture, GLint level,
                                      GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetCompressedTextureImage";

    beforeCommand(fnName, _api.glGetCompressedTextureImage);
    _api.glGetCompressedTextureImage(texture.ID, level, bufSize, pixels);
    afterCommand(fnName);
}

// Calls glGetCompressedTextureSubImage().
void GLAPI::getCompressedTextureSubImage(TextureName texture, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLsizei width,
                                         GLsizei height, GLsizei depth,
                                         GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetCompressedTextureSubImage";

    beforeCommand(fnName, _api.glGetCompressedTextureSubImage);
    _api.glGetCompressedTextureSubImage(texture.ID, level, xoffset, yoffset,
                                        zoffset, width, height, depth, bufSize,
                                        pixels);
    afterCommand(fnName);
}

// Calls glGetGraphicsResetStatus().
GraphicsResetStatus GLAPI::getGraphicsResetStatus() const
{
    static const char *fnName = "glGetGraphicsResetStatus";

    beforeCommand(fnName, _api.glGetGraphicsResetStatus);
    GLenum result = _api.glGetGraphicsResetStatus();
    afterCommand(fnName);

    return static_cast<GraphicsResetStatus>(result);
}

// Calls glGetNamedBufferParameteri64v().
void GLAPI::getNamedBufferParameterI64V(BufferName buffer, BufferPNameARB pname,
                                        GLint64 *params) const
{
    static const char *fnName = "glGetNamedBufferParameteri64v";

    beforeCommand(fnName, _api.glGetNamedBufferParameteri64v);
    _api.glGetNamedBufferParameteri64v(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferParameteriv().
void GLAPI::getNamedBufferParameterIV(BufferName buffer, BufferPNameARB pname,
                                      GLint *params) const
{
    static const char *fnName = "glGetNamedBufferParameteriv";

    beforeCommand(fnName, _api.glGetNamedBufferParameteriv);
    _api.glGetNamedBufferParameteriv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferPointerv().
void GLAPI::getNamedBufferPointerV(BufferName buffer, BufferPointerNameARB pname,
                                   void **params) const
{
    static const char *fnName = "glGetNamedBufferPointerv";

    beforeCommand(fnName, _api.glGetNamedBufferPointerv);
    _api.glGetNamedBufferPointerv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferSubData().
void GLAPI::getNamedBufferSubData(BufferName buffer, GLintptr offset,
                                  GLsizeiptr size, void *data) const
{
    static const char *fnName = "glGetNamedBufferSubData";

    beforeCommand(fnName, _api.glGetNamedBufferSubData);
    _api.glGetNamedBufferSubData(buffer.ID, offset, size, data);
    afterCommand(fnName);
}

// Calls glGetNamedFramebufferAttachmentParameteriv().
void GLAPI::getNamedFramebufferAttachmentParameterIV(FramebufferName framebuffer,
                                                     FramebufferAttachment attachment,
                                                     FramebufferAttachmentParameterName pname,
                                                     GLint *params) const
{
    static const char *fnName = "glGetNamedFramebufferAttachmentParameteriv";

    beforeCommand(fnName, _api.glGetNamedFramebufferAttachmentParameteriv);
    _api.glGetNamedFramebufferAttachmentParameteriv(framebuffer.ID,
                                                    toScalar(attachment),
                                                    toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedFramebufferParameteriv().
void GLAPI::getNamedFramebufferParameterIV(FramebufferName framebuffer,
                                           GetFramebufferParameter pname,
                                           GLint *param) const
{
    static const char *fnName = "glGetNamedFramebufferParameteriv";

    beforeCommand(fnName, _api.glGetNamedFramebufferParameteriv);
    _api.glGetNamedFramebufferParameteriv(framebuffer.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetNamedRenderbufferParameteriv().
void GLAPI::getNamedRenderbufferParameterIV(RenderbufferName renderbuffer,
                                            RenderbufferParameterName pname,
                                            GLint *params) const
{
    static const char *fnName = "glGetNamedRenderbufferParameteriv";

    beforeCommand(fnName, _api.glGetNamedRenderbufferParameteriv);
    _api.glGetNamedRenderbufferParameteriv(renderbuffer.ID, toScalar(pname),
                                           params);
    afterCommand(fnName);
}

// Calls glGetQueryBufferObjecti64v().
void GLAPI::getQueryBufferObjectI64V(QueryName id, BufferName buffer,
                                     QueryObjectParameterName pname,
                                     GLintptr offset) const
{
    static const char *fnName = "glGetQueryBufferObjecti64v";

    beforeCommand(fnName, _api.glGetQueryBufferObjecti64v);
    _api.glGetQueryBufferObjecti64v(id.ID, buffer.ID, toScalar(pname), offset);
    afterCommand(fnName);
}

// Calls glGetQueryBufferObjectiv().
void GLAPI::getQueryBufferObjectIV(QueryName id, BufferName buffer,
                                   QueryObjectParameterName pname,
                                   GLintptr offset) const
{
    static const char *fnName = "glGetQueryBufferObjectiv";

    beforeCommand(fnName, _api.glGetQueryBufferObjectiv);
    _api.glGetQueryBufferObjectiv(id.ID, buffer.ID, toScalar(pname), offset);
    afterCommand(fnName);
}

// Calls glGetQueryBufferObjectui64v().
void GLAPI::getQueryBufferObjectUI64(QueryName id, BufferName buffer,
                                     QueryObjectParameterName pname,
                                     GLintptr offset) const
{
    static const char *fnName = "glGetQueryBufferObjectui64v";

    beforeCommand(fnName, _api.glGetQueryBufferObjectui64v);
    _api.glGetQueryBufferObjectui64v(id.ID, buffer.ID, toScalar(pname), offset);
    afterCommand(fnName);
}

// Calls glGetQueryBufferObjectuiv().
void GLAPI::getQueryBufferObjectUIV(QueryName id, BufferName buffer,
                                    QueryObjectParameterName pname,
                                    GLintptr offset) const
{
    static const char *fnName = "glGetQueryBufferObjectuiv";

    beforeCommand(fnName, _api.glGetQueryBufferObjectuiv);
    _api.glGetQueryBufferObjectuiv(id.ID, buffer.ID, toScalar(pname), offset);
    afterCommand(fnName);
}

// Calls glGetTextureImage().
void GLAPI::getTextureImage(TextureName texture, GLint level, PixelFormat format,
                            PixelType type, GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetTextureImage";

    beforeCommand(fnName, _api.glGetTextureImage);
    _api.glGetTextureImage(texture.ID, level, toScalar(format), toScalar(type),
                           bufSize, pixels);
    afterCommand(fnName);
}

// Calls glGetTextureLevelParameterfv().
void GLAPI::getTextureLevelParameterFV(TextureName texture, GLint level,
                                       GetTextureParameter pname,
                                       GLfloat *params) const
{
    static const char *fnName = "glGetTextureLevelParameterfv";

    beforeCommand(fnName, _api.glGetTextureLevelParameterfv);
    _api.glGetTextureLevelParameterfv(texture.ID, level, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureLevelParameteriv().
void GLAPI::getTextureLevelParameterIV(TextureName texture, GLint level,
                                       GetTextureParameter pname, GLint *params) const
{
    static const char *fnName = "glGetTextureLevelParameteriv";

    beforeCommand(fnName, _api.glGetTextureLevelParameteriv);
    _api.glGetTextureLevelParameteriv(texture.ID, level, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterIiv().
void GLAPI::getTextureParameterIIV(TextureName texture,
                                   GetTextureParameter pname, GLint *params) const
{
    static const char *fnName = "glGetTextureParameterIiv";

    beforeCommand(fnName, _api.glGetTextureParameterIiv);
    _api.glGetTextureParameterIiv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterIuiv().
void GLAPI::getTextureParameterIUIV(TextureName texture,
                                    GetTextureParameter pname, GLuint *params) const
{
    static const char *fnName = "glGetTextureParameterIuiv";

    beforeCommand(fnName, _api.glGetTextureParameterIuiv);
    _api.glGetTextureParameterIuiv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterfv().
void GLAPI::getTextureParameterFV(TextureName texture, GetTextureParameter pname,
                                  GLfloat *params) const
{
    static const char *fnName = "glGetTextureParameterfv";

    beforeCommand(fnName, _api.glGetTextureParameterfv);
    _api.glGetTextureParameterfv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureParameteriv().
void GLAPI::getTextureParameterIV(TextureName texture, GetTextureParameter pname,
                                  GLint *params) const
{
    static const char *fnName = "glGetTextureParameteriv";

    beforeCommand(fnName, _api.glGetTextureParameteriv);
    _api.glGetTextureParameteriv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureSubImage().
void GLAPI::getTextureSubImage(TextureName texture, GLint level, GLint xoffset,
                               GLint yoffset, GLint zoffset, GLsizei width,
                               GLsizei height, GLsizei depth, PixelFormat format,
                               PixelType type, GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetTextureSubImage";

    beforeCommand(fnName, _api.glGetTextureSubImage);
    _api.glGetTextureSubImage(texture.ID, level, xoffset, yoffset, zoffset,
                              width, height, depth, toScalar(format),
                              toScalar(type), bufSize, pixels);
    afterCommand(fnName);
}

// Calls glGetTransformFeedbacki64_v().
void GLAPI::getTransformFeedbackI64(TransformFeedbackName xfb,
                                    TransformFeedbackPName pname, GLuint index,
                                    GLint64 *param) const
{
    static const char *fnName = "glGetTransformFeedbacki64_v";

    beforeCommand(fnName, _api.glGetTransformFeedbacki64_v);
    _api.glGetTransformFeedbacki64_v(xfb.ID, toScalar(pname), index, param);
    afterCommand(fnName);
}

// Calls glGetTransformFeedbacki_v().
void GLAPI::getTransformFeedbackIV(TransformFeedbackName xfb,
                                   TransformFeedbackPName pname, GLuint index,
                                   GLint *param) const
{
    static const char *fnName = "glGetTransformFeedbacki_v";

    beforeCommand(fnName, _api.glGetTransformFeedbacki_v);
    _api.glGetTransformFeedbacki_v(xfb.ID, toScalar(pname), index, param);
    afterCommand(fnName);
}

// Calls glGetTransformFeedbackiv().
void GLAPI::getTransformFeedbackIV(TransformFeedbackName xfb,
                                   TransformFeedbackPName pname, GLint *param) const
{
    static const char *fnName = "glGetTransformFeedbackiv";

    beforeCommand(fnName, _api.glGetTransformFeedbackiv);
    _api.glGetTransformFeedbackiv(xfb.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayIndexed64iv().
void GLAPI::getVertexArrayIndexed64IV(VertexArrayName vaobj, GLuint index,
                                      VertexArrayPName pname, GLint64 *param) const
{
    static const char *fnName = "glGetVertexArrayIndexed64iv";

    beforeCommand(fnName, _api.glGetVertexArrayIndexed64iv);
    _api.glGetVertexArrayIndexed64iv(vaobj.ID, index, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayIndexediv().
void GLAPI::getVertexArrayIndexedIV(VertexArrayName vaobj, GLuint index,
                                    VertexArrayPName pname, GLint *param) const
{
    static const char *fnName = "glGetVertexArrayIndexediv";

    beforeCommand(fnName, _api.glGetVertexArrayIndexediv);
    _api.glGetVertexArrayIndexediv(vaobj.ID, index, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayiv().
void GLAPI::getVertexArrayIV(VertexArrayName vaobj, VertexArrayPName pname,
                             GLint *param) const
{
    static const char *fnName = "glGetVertexArrayiv";

    beforeCommand(fnName, _api.glGetVertexArrayiv);
    _api.glGetVertexArrayiv(vaobj.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetnCompressedTexImage().
void GLAPI::getnCompressedTexImage(TextureTarget target, GLint lod,
                                   GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetnCompressedTexImage";

    beforeCommand(fnName, _api.glGetnCompressedTexImage);
    _api.glGetnCompressedTexImage(toScalar(target), lod, bufSize, pixels);
    afterCommand(fnName);
}

// Calls glGetnTexImage().
void GLAPI::getnTexImage(TextureTarget target, GLint level, PixelFormat format,
                         PixelType type, GLsizei bufSize, void *pixels) const
{
    static const char *fnName = "glGetnTexImage";

    beforeCommand(fnName, _api.glGetnTexImage);
    _api.glGetnTexImage(toScalar(target), level, toScalar(format),
                        toScalar(type), bufSize, pixels);
    afterCommand(fnName);
}

// Calls glGetnUniformdv().
void GLAPI::getnUniformDV(ProgramName program, GLint location, GLsizei bufSize,
                          GLdouble *params) const
{
    static const char *fnName = "glGetnUniformdv";

    beforeCommand(fnName, _api.glGetnUniformdv);
    _api.glGetnUniformdv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformfv().
void GLAPI::getnUniformFV(ProgramName program, GLint location, GLsizei bufSize,
                          GLfloat *params) const
{
    static const char *fnName = "glGetnUniformfv";

    beforeCommand(fnName, _api.glGetnUniformfv);
    _api.glGetnUniformfv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformiv().
void GLAPI::getnUniformIV(ProgramName program, GLint location, GLsizei bufSize,
                          GLint *params) const
{
    static const char *fnName = "glGetnUniformiv";

    beforeCommand(fnName, _api.glGetnUniformiv);
    _api.glGetnUniformiv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformuiv().
void GLAPI::getnUniformUIV(ProgramName program, GLint location, GLsizei bufSize,
                           GLuint *params) const
{
    static const char *fnName = "glGetnUniformuiv";

    beforeCommand(fnName, _api.glGetnUniformuiv);
    _api.glGetnUniformuiv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glInvalidateNamedFramebufferData().
void GLAPI::invalidateNamedFramebufferData(FramebufferName framebuffer,
                                           GLsizei numAttachments,
                                           const FramebufferAttachment *attachments) const
{
    static const char *fnName = "glInvalidateNamedFramebufferData";

    beforeCommand(fnName, _api.glInvalidateNamedFramebufferData);
    _api.glInvalidateNamedFramebufferData(framebuffer.ID, numAttachments,
                                          toScalarPtr(attachments));
    afterCommand(fnName);
}

// Calls glInvalidateNamedFramebufferSubData().
void GLAPI::invalidateNamedFramebufferSubData(FramebufferName framebuffer,
                                              GLsizei numAttachments,
                                              const FramebufferAttachment *attachments,
                                              GLint x, GLint y, GLsizei width,
                                              GLsizei height) const
{
    static const char *fnName = "glInvalidateNamedFramebufferSubData";

    beforeCommand(fnName, _api.glInvalidateNamedFramebufferSubData);
    _api.glInvalidateNamedFramebufferSubData(framebuffer.ID, numAttachments,
                                             toScalarPtr(attachments), x, y,
                                             width, height);
    afterCommand(fnName);
}

// Calls glMapNamedBuffer().
void *GLAPI::mapNamedBuffer(BufferName buffer, BufferAccessARB access) const
{
    static const char *fnName = "glMapNamedBuffer";

    beforeCommand(fnName, _api.glMapNamedBuffer);
    void *result = _api.glMapNamedBuffer(buffer.ID, toScalar(access));
    afterCommand(fnName);

    return result;
}

// Calls glMapNamedBufferRange().
void *GLAPI::mapNamedBufferRange(BufferName buffer, GLintptr offset,
                                 GLsizeiptr length,
                                 GLbitfield  /* MapBufferAccessMask */ access) const
{
    static const char *fnName = "glMapNamedBufferRange";

    beforeCommand(fnName, _api.glMapNamedBufferRange);
    void *result = _api.glMapNamedBufferRange(buffer.ID, offset, length, access);
    afterCommand(fnName);

    return result;
}

// Calls glMemoryBarrierByRegion().
void GLAPI::memoryBarrierByRegion(GLbitfield  /* MemoryBarrierMask */ barriers) const
{
    static const char *fnName = "glMemoryBarrierByRegion";

    beforeCommand(fnName, _api.glMemoryBarrierByRegion);
    _api.glMemoryBarrierByRegion(barriers);
    afterCommand(fnName);
}

// Calls glNamedBufferData().
void GLAPI::namedBufferData(BufferName buffer, GLsizeiptr size, const void *data,
                            VertexBufferObjectUsage usage) const
{
    static const char *fnName = "glNamedBufferData";

    beforeCommand(fnName, _api.glNamedBufferData);
    _api.glNamedBufferData(buffer.ID, size, data, toScalar(usage));
    afterCommand(fnName);
}

// Calls glNamedBufferStorage().
void GLAPI::namedBufferStorage(BufferName buffer, GLsizeiptr size,
                               const void *data,
                               GLbitfield  /* BufferStorageMask */ flags) const
{
    static const char *fnName = "glNamedBufferStorage";

    beforeCommand(fnName, _api.glNamedBufferStorage);
    _api.glNamedBufferStorage(buffer.ID, size, data, flags);
    afterCommand(fnName);
}

// Calls glNamedBufferSubData().
void GLAPI::namedBufferSubData(BufferName buffer, GLintptr offset,
                               GLsizeiptr size, const void *data) const
{
    static const char *fnName = "glNamedBufferSubData";

    beforeCommand(fnName, _api.glNamedBufferSubData);
    _api.glNamedBufferSubData(buffer.ID, offset, size, data);
    afterCommand(fnName);
}

// Calls glNamedFramebufferDrawBuffer().
void GLAPI::namedFramebufferDrawBuffer(FramebufferName framebuffer,
                                       ColorBuffer buf) const
{
    static const char *fnName = "glNamedFramebufferDrawBuffer";

    beforeCommand(fnName, _api.glNamedFramebufferDrawBuffer);
    _api.glNamedFramebufferDrawBuffer(framebuffer.ID, toScalar(buf));
    afterCommand(fnName);
}

// Calls glNamedFramebufferDrawBuffers().
void GLAPI::namedFramebufferDrawBuffers(FramebufferName framebuffer, GLsizei n,
                                        const ColorBuffer *bufs) const
{
    static const char *fnName = "glNamedFramebufferDrawBuffers";

    beforeCommand(fnName, _api.glNamedFramebufferDrawBuffers);
    _api.glNamedFramebufferDrawBuffers(framebuffer.ID, n, toScalarPtr(bufs));
    afterCommand(fnName);
}

// Calls glNamedFramebufferParameteri().
void GLAPI::namedFramebufferParameterI(FramebufferName framebuffer,
                                       FramebufferParameterName pname,
                                       GLint param) const
{
    static const char *fnName = "glNamedFramebufferParameteri";

    beforeCommand(fnName, _api.glNamedFramebufferParameteri);
    _api.glNamedFramebufferParameteri(framebuffer.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glNamedFramebufferReadBuffer().
void GLAPI::namedFramebufferReadBuffer(FramebufferName framebuffer,
                                       ColorBuffer src) const
{
    static const char *fnName = "glNamedFramebufferReadBuffer";

    beforeCommand(fnName, _api.glNamedFramebufferReadBuffer);
    _api.glNamedFramebufferReadBuffer(framebuffer.ID, toScalar(src));
    afterCommand(fnName);
}

// Calls glNamedFramebufferRenderbuffer().
void GLAPI::namedFramebufferRenderbuffer(FramebufferName framebuffer,
                                         FramebufferAttachment attachment,
                                         RenderbufferTarget renderbuffertarget,
                                         RenderbufferName renderbuffer) const
{
    static const char *fnName = "glNamedFramebufferRenderbuffer";

    beforeCommand(fnName, _api.glNamedFramebufferRenderbuffer);
    _api.glNamedFramebufferRenderbuffer(framebuffer.ID, toScalar(attachment),
                                        toScalar(renderbuffertarget),
                                        renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTexture().
void GLAPI::namedFramebufferTexture(FramebufferName framebuffer,
                                    FramebufferAttachment attachment,
                                    TextureName texture, GLint level) const
{
    static const char *fnName = "glNamedFramebufferTexture";

    beforeCommand(fnName, _api.glNamedFramebufferTexture);
    _api.glNamedFramebufferTexture(framebuffer.ID, toScalar(attachment),
                                   texture.ID, level);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTextureLayer().
void GLAPI::namedFramebufferTextureLayer(FramebufferName framebuffer,
                                         FramebufferAttachment attachment,
                                         TextureName texture, GLint level,
                                         GLint layer) const
{
    static const char *fnName = "glNamedFramebufferTextureLayer";

    beforeCommand(fnName, _api.glNamedFramebufferTextureLayer);
    _api.glNamedFramebufferTextureLayer(framebuffer.ID, toScalar(attachment),
                                        texture.ID, level, layer);
    afterCommand(fnName);
}

// Calls glNamedRenderbufferStorage().
void GLAPI::namedRenderbufferStorage(RenderbufferName renderbuffer,
                                     InternalFormat internalformat,
                                     GLsizei width, GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorage";

    beforeCommand(fnName, _api.glNamedRenderbufferStorage);
    _api.glNamedRenderbufferStorage(renderbuffer.ID, toScalar(internalformat),
                                    width, height);
    afterCommand(fnName);
}

// Calls glNamedRenderbufferStorageMultisample().
void GLAPI::namedRenderbufferStorageMultisample(RenderbufferName renderbuffer,
                                                GLsizei samples,
                                                InternalFormat internalformat,
                                                GLsizei width, GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorageMultisample";

    beforeCommand(fnName, _api.glNamedRenderbufferStorageMultisample);
    _api.glNamedRenderbufferStorageMultisample(renderbuffer.ID, samples,
                                               toScalar(internalformat), width,
                                               height);
    afterCommand(fnName);
}

// Calls glReadnPixels().
void GLAPI::readnPixels(GLint x, GLint y, GLsizei width, GLsizei height,
                        PixelFormat format, PixelType type, GLsizei bufSize,
                        void *data) const
{
    static const char *fnName = "glReadnPixels";

    beforeCommand(fnName, _api.glReadnPixels);
    _api.glReadnPixels(x, y, width, height, toScalar(format), toScalar(type),
                       bufSize, data);
    afterCommand(fnName);
}

// Calls glTextureBarrier().
void GLAPI::textureBarrier() const
{
    static const char *fnName = "glTextureBarrier";

    beforeCommand(fnName, _api.glTextureBarrier);
    _api.glTextureBarrier();
    afterCommand(fnName);
}

// Calls glTextureBuffer().
void GLAPI::textureBuffer(TextureName texture,
                          SizedInternalFormat internalformat, BufferName buffer) const
{
    static const char *fnName = "glTextureBuffer";

    beforeCommand(fnName, _api.glTextureBuffer);
    _api.glTextureBuffer(texture.ID, toScalar(internalformat), buffer.ID);
    afterCommand(fnName);
}

// Calls glTextureBufferRange().
void GLAPI::textureBufferRange(TextureName texture,
                               SizedInternalFormat internalformat,
                               BufferName buffer, GLintptr offset,
                               GLsizeiptr size) const
{
    static const char *fnName = "glTextureBufferRange";

    beforeCommand(fnName, _api.glTextureBufferRange);
    _api.glTextureBufferRange(texture.ID, toScalar(internalformat), buffer.ID,
                              offset, size);
    afterCommand(fnName);
}

// Calls glTextureParameterIiv().
void GLAPI::textureParameterIIV(TextureName texture, TextureParameterName pname,
                                const GLint *params) const
{
    static const char *fnName = "glTextureParameterIiv";

    beforeCommand(fnName, _api.glTextureParameterIiv);
    _api.glTextureParameterIiv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTextureParameterIuiv().
void GLAPI::textureParameterIUIV(TextureName texture, TextureParameterName pname,
                                 const GLuint *params) const
{
    static const char *fnName = "glTextureParameterIuiv";

    beforeCommand(fnName, _api.glTextureParameterIuiv);
    _api.glTextureParameterIuiv(texture.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTextureParameterf().
void GLAPI::textureParameterF(TextureName texture, TextureParameterName pname,
                              GLfloat param) const
{
    static const char *fnName = "glTextureParameterf";

    beforeCommand(fnName, _api.glTextureParameterf);
    _api.glTextureParameterf(texture.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTextureParameterfv().
void GLAPI::textureParameterFV(TextureName texture, TextureParameterName pname,
                               const GLfloat *param) const
{
    static const char *fnName = "glTextureParameterfv";

    beforeCommand(fnName, _api.glTextureParameterfv);
    _api.glTextureParameterfv(texture.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTextureParameteri().
void GLAPI::textureParameterI(TextureName texture, TextureParameterName pname,
                              GLint param) const
{
    static const char *fnName = "glTextureParameteri";

    beforeCommand(fnName, _api.glTextureParameteri);
    _api.glTextureParameteri(texture.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTextureParameteriv().
void GLAPI::textureParameterIV(TextureName texture, TextureParameterName pname,
                               const GLint *param) const
{
    static const char *fnName = "glTextureParameteriv";

    beforeCommand(fnName, _api.glTextureParameteriv);
    _api.glTextureParameteriv(texture.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTextureStorage1D().
void GLAPI::textureStorage1D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalformat, GLsizei width) const
{
    static const char *fnName = "glTextureStorage1D";

    beforeCommand(fnName, _api.glTextureStorage1D);
    _api.glTextureStorage1D(texture.ID, levels, toScalar(internalformat), width);
    afterCommand(fnName);
}

// Calls glTextureStorage2D().
void GLAPI::textureStorage2D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalformat, GLsizei width,
                             GLsizei height) const
{
    static const char *fnName = "glTextureStorage2D";

    beforeCommand(fnName, _api.glTextureStorage2D);
    _api.glTextureStorage2D(texture.ID, levels, toScalar(internalformat), width,
                            height);
    afterCommand(fnName);
}

// Calls glTextureStorage2DMultisample().
void GLAPI::textureStorage2DMultisample(TextureName texture, GLsizei samples,
                                        SizedInternalFormat internalformat,
                                        GLsizei width, GLsizei height,
                                        Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTextureStorage2DMultisample";

    beforeCommand(fnName, _api.glTextureStorage2DMultisample);
    _api.glTextureStorage2DMultisample(texture.ID, samples,
                                       toScalar(internalformat), width, height,
                                       toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTextureStorage3D().
void GLAPI::textureStorage3D(TextureName texture, GLsizei levels,
                             SizedInternalFormat internalformat, GLsizei width,
                             GLsizei height, GLsizei depth) const
{
    static const char *fnName = "glTextureStorage3D";

    beforeCommand(fnName, _api.glTextureStorage3D);
    _api.glTextureStorage3D(texture.ID, levels, toScalar(internalformat), width,
                            height, depth);
    afterCommand(fnName);
}

// Calls glTextureStorage3DMultisample().
void GLAPI::textureStorage3DMultisample(TextureName texture, GLsizei samples,
                                        SizedInternalFormat internalformat,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth,
                                        Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTextureStorage3DMultisample";

    beforeCommand(fnName, _api.glTextureStorage3DMultisample);
    _api.glTextureStorage3DMultisample(texture.ID, samples,
                                       toScalar(internalformat), width, height,
                                       depth, toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTextureSubImage1D().
void GLAPI::textureSubImage1D(TextureName texture, GLint level, GLint xoffset,
                              GLsizei width, PixelFormat format, PixelType type,
                              const void *pixels) const
{
    static const char *fnName = "glTextureSubImage1D";

    beforeCommand(fnName, _api.glTextureSubImage1D);
    _api.glTextureSubImage1D(texture.ID, level, xoffset, width, toScalar(format),
                             toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureSubImage2D().
void GLAPI::textureSubImage2D(TextureName texture, GLint level, GLint xoffset,
                              GLint yoffset, GLsizei width, GLsizei height,
                              PixelFormat format, PixelType type,
                              const void *pixels) const
{
    static const char *fnName = "glTextureSubImage2D";

    beforeCommand(fnName, _api.glTextureSubImage2D);
    _api.glTextureSubImage2D(texture.ID, level, xoffset, yoffset, width, height,
                             toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureSubImage3D().
void GLAPI::textureSubImage3D(TextureName texture, GLint level, GLint xoffset,
                              GLint yoffset, GLint zoffset, GLsizei width,
                              GLsizei height, GLsizei depth, PixelFormat format,
                              PixelType type, const void *pixels) const
{
    static const char *fnName = "glTextureSubImage3D";

    beforeCommand(fnName, _api.glTextureSubImage3D);
    _api.glTextureSubImage3D(texture.ID, level, xoffset, yoffset, zoffset, width,
                             height, depth, toScalar(format), toScalar(type),
                             pixels);
    afterCommand(fnName);
}

// Calls glTransformFeedbackBufferBase().
void GLAPI::transformFeedbackBufferBase(TransformFeedbackName xfb, GLuint index,
                                        BufferName buffer) const
{
    static const char *fnName = "glTransformFeedbackBufferBase";

    beforeCommand(fnName, _api.glTransformFeedbackBufferBase);
    _api.glTransformFeedbackBufferBase(xfb.ID, index, buffer.ID);
    afterCommand(fnName);
}

// Calls glTransformFeedbackBufferRange().
void GLAPI::transformFeedbackBufferRange(TransformFeedbackName xfb, GLuint index,
                                         BufferName buffer, GLintptr offset,
                                         GLsizeiptr size) const
{
    static const char *fnName = "glTransformFeedbackBufferRange";

    beforeCommand(fnName, _api.glTransformFeedbackBufferRange);
    _api.glTransformFeedbackBufferRange(xfb.ID, index, buffer.ID, offset, size);
    afterCommand(fnName);
}

// Calls glUnmapNamedBuffer().
Boolean GLAPI::unmapNamedBuffer(BufferName buffer) const
{
    static const char *fnName = "glUnmapNamedBuffer";

    beforeCommand(fnName, _api.glUnmapNamedBuffer);
    GLboolean result = _api.glUnmapNamedBuffer(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glVertexArrayAttribBinding().
void GLAPI::vertexArrayAttribBinding(VertexArrayName vaobj, GLuint attribindex,
                                     GLuint bindingindex) const
{
    static const char *fnName = "glVertexArrayAttribBinding";

    beforeCommand(fnName, _api.glVertexArrayAttribBinding);
    _api.glVertexArrayAttribBinding(vaobj.ID, attribindex, bindingindex);
    afterCommand(fnName);
}

// Calls glVertexArrayAttribFormat().
void GLAPI::vertexArrayAttribFormat(VertexArrayName vaobj, GLuint attribindex,
                                    GLint size, VertexAttribType type,
                                    Boolean normalized, GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayAttribFormat";

    beforeCommand(fnName, _api.glVertexArrayAttribFormat);
    _api.glVertexArrayAttribFormat(vaobj.ID, attribindex, size, toScalar(type),
                                   toScalar(normalized), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayAttribIFormat().
void GLAPI::vertexArrayAttribIFormat(VertexArrayName vaobj, GLuint attribindex,
                                     GLint size, VertexAttribIType type,
                                     GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayAttribIFormat";

    beforeCommand(fnName, _api.glVertexArrayAttribIFormat);
    _api.glVertexArrayAttribIFormat(vaobj.ID, attribindex, size, toScalar(type),
                                    relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayAttribLFormat().
void GLAPI::vertexArrayAttribLFormat(VertexArrayName vaobj, GLuint attribindex,
                                     GLint size, VertexAttribLType type,
                                     GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayAttribLFormat";

    beforeCommand(fnName, _api.glVertexArrayAttribLFormat);
    _api.glVertexArrayAttribLFormat(vaobj.ID, attribindex, size, toScalar(type),
                                    relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayBindingDivisor().
void GLAPI::vertexArrayBindingDivisor(VertexArrayName vaobj, GLuint bindingindex,
                                      GLuint divisor) const
{
    static const char *fnName = "glVertexArrayBindingDivisor";

    beforeCommand(fnName, _api.glVertexArrayBindingDivisor);
    _api.glVertexArrayBindingDivisor(vaobj.ID, bindingindex, divisor);
    afterCommand(fnName);
}

// Calls glVertexArrayElementBuffer().
void GLAPI::vertexArrayElementBuffer(VertexArrayName vaobj, BufferName buffer) const
{
    static const char *fnName = "glVertexArrayElementBuffer";

    beforeCommand(fnName, _api.glVertexArrayElementBuffer);
    _api.glVertexArrayElementBuffer(vaobj.ID, buffer.ID);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexBuffer().
void GLAPI::vertexArrayVertexBuffer(VertexArrayName vaobj, GLuint bindingindex,
                                    BufferName buffer, GLintptr offset,
                                    GLsizei stride) const
{
    static const char *fnName = "glVertexArrayVertexBuffer";

    beforeCommand(fnName, _api.glVertexArrayVertexBuffer);
    _api.glVertexArrayVertexBuffer(vaobj.ID, bindingindex, buffer.ID, offset,
                                   stride);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexBuffers().
void GLAPI::vertexArrayVertexBuffers(VertexArrayName vaobj, GLuint first,
                                     GLsizei count, const BufferName *buffers,
                                     const GLintptr *offsets,
                                     const GLsizei *strides) const
{
    static const char *fnName = "glVertexArrayVertexBuffers";

    beforeCommand(fnName, _api.glVertexArrayVertexBuffers);
    _api.glVertexArrayVertexBuffers(vaobj.ID, first, count,
                                    reinterpret_cast<const GLuint *>(buffers),
                                    offsets, strides);
    afterCommand(fnName);
}

// Calls glMultiDrawArraysIndirectCount().
void GLAPI::multiDrawArraysIndirectCount(PrimitiveType mode,
                                         const void *indirect,
                                         GLintptr drawcount,
                                         GLsizei maxdrawcount, GLsizei stride) const
{
    static const char *fnName = "glMultiDrawArraysIndirectCount";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirectCount);
    _api.glMultiDrawArraysIndirectCount(toScalar(mode), indirect, drawcount,
                                        maxdrawcount, stride);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirectCount().
void GLAPI::multiDrawElementsIndirectCount(PrimitiveType mode,
                                           DrawElementsType type,
                                           const void *indirect,
                                           GLintptr drawcount,
                                           GLsizei maxdrawcount, GLsizei stride) const
{
    static const char *fnName = "glMultiDrawElementsIndirectCount";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirectCount);
    _api.glMultiDrawElementsIndirectCount(toScalar(mode), toScalar(type),
                                          indirect, drawcount, maxdrawcount,
                                          stride);
    afterCommand(fnName);
}

// Calls glPolygonOffsetClamp().
void GLAPI::polygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) const
{
    static const char *fnName = "glPolygonOffsetClamp";

    beforeCommand(fnName, _api.glPolygonOffsetClamp);
    _api.glPolygonOffsetClamp(factor, units, clamp);
    afterCommand(fnName);
}

// Calls glSpecializeShader().
void GLAPI::specializeShader(ShaderName shader, const GLchar *pEntryPoint,
                             GLuint numSpecializationConstants,
                             const GLuint *pConstantIndex,
                             const GLuint *pConstantValue) const
{
    static const char *fnName = "glSpecializeShader";

    beforeCommand(fnName, _api.glSpecializeShader);
    _api.glSpecializeShader(shader.ID, pEntryPoint, numSpecializationConstants,
                            pConstantIndex, pConstantValue);
    afterCommand(fnName);
}

} // namespace gl

