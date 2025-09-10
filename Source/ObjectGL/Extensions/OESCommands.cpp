//! @file ObjectGL/Extensions/OESCommands.cpp
//! @brief The definition of OES-specific extensions to the OpenGL Command
//! set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/OESCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// OESByteCoordinatesAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_OES_byte_coordinates extension.
OESByteCoordinatesAPI::OESByteCoordinatesAPI() :
    BaseExtension("GL_OES_byte_coordinates")
{
}

// Grant read-only access to the underlying function pointers.
const OESByteCoordinates &OESByteCoordinatesAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_OES_byte_coordinates entry points.
void OESByteCoordinatesAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiTexCoord1bOES().
void OESByteCoordinatesAPI::multiTexCoord1B(TextureUnit texture, GLbyte s) const
{
    static const char *fnName = "glMultiTexCoord1bOES";

    beforeCommand(fnName, _api.glMultiTexCoord1b);
    _api.glMultiTexCoord1b(toScalar(texture), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1bvOES().
void OESByteCoordinatesAPI::multiTexCoord1BV(TextureUnit texture,
                                             const GLbyte *coords) const
{
    static const char *fnName = "glMultiTexCoord1bvOES";

    beforeCommand(fnName, _api.glMultiTexCoord1bv);
    _api.glMultiTexCoord1bv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2bOES().
void OESByteCoordinatesAPI::multiTexCoord2B(TextureUnit texture, GLbyte s,
                                            GLbyte t) const
{
    static const char *fnName = "glMultiTexCoord2bOES";

    beforeCommand(fnName, _api.glMultiTexCoord2b);
    _api.glMultiTexCoord2b(toScalar(texture), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2bvOES().
void OESByteCoordinatesAPI::multiTexCoord2BV(TextureUnit texture,
                                             const GLbyte *coords) const
{
    static const char *fnName = "glMultiTexCoord2bvOES";

    beforeCommand(fnName, _api.glMultiTexCoord2bv);
    _api.glMultiTexCoord2bv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3bOES().
void OESByteCoordinatesAPI::multiTexCoord3B(TextureUnit texture, GLbyte s,
                                            GLbyte t, GLbyte r) const
{
    static const char *fnName = "glMultiTexCoord3bOES";

    beforeCommand(fnName, _api.glMultiTexCoord3b);
    _api.glMultiTexCoord3b(toScalar(texture), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3bvOES().
void OESByteCoordinatesAPI::multiTexCoord3BV(TextureUnit texture,
                                             const GLbyte *coords) const
{
    static const char *fnName = "glMultiTexCoord3bvOES";

    beforeCommand(fnName, _api.glMultiTexCoord3bv);
    _api.glMultiTexCoord3bv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4bOES().
void OESByteCoordinatesAPI::multiTexCoord4B(TextureUnit texture, GLbyte s,
                                            GLbyte t, GLbyte r, GLbyte q) const
{
    static const char *fnName = "glMultiTexCoord4bOES";

    beforeCommand(fnName, _api.glMultiTexCoord4b);
    _api.glMultiTexCoord4b(toScalar(texture), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4bvOES().
void OESByteCoordinatesAPI::multiTexCoord4BV(TextureUnit texture,
                                             const GLbyte *coords) const
{
    static const char *fnName = "glMultiTexCoord4bvOES";

    beforeCommand(fnName, _api.glMultiTexCoord4bv);
    _api.glMultiTexCoord4bv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glTexCoord1bOES().
void OESByteCoordinatesAPI::texCoord1B(GLbyte s) const
{
    static const char *fnName = "glTexCoord1bOES";

    beforeCommand(fnName, _api.glTexCoord1b);
    _api.glTexCoord1b(s);
    afterCommand(fnName);
}

// Calls glTexCoord1bvOES().
void OESByteCoordinatesAPI::texCoord1BV(const GLbyte *coords) const
{
    static const char *fnName = "glTexCoord1bvOES";

    beforeCommand(fnName, _api.glTexCoord1bv);
    _api.glTexCoord1bv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord2bOES().
void OESByteCoordinatesAPI::texCoord2B(GLbyte s, GLbyte t) const
{
    static const char *fnName = "glTexCoord2bOES";

    beforeCommand(fnName, _api.glTexCoord2b);
    _api.glTexCoord2b(s, t);
    afterCommand(fnName);
}

// Calls glTexCoord2bvOES().
void OESByteCoordinatesAPI::texCoord2BV(const GLbyte *coords) const
{
    static const char *fnName = "glTexCoord2bvOES";

    beforeCommand(fnName, _api.glTexCoord2bv);
    _api.glTexCoord2bv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord3bOES().
void OESByteCoordinatesAPI::texCoord3B(GLbyte s, GLbyte t, GLbyte r) const
{
    static const char *fnName = "glTexCoord3bOES";

    beforeCommand(fnName, _api.glTexCoord3b);
    _api.glTexCoord3b(s, t, r);
    afterCommand(fnName);
}

// Calls glTexCoord3bvOES().
void OESByteCoordinatesAPI::texCoord3BV(const GLbyte *coords) const
{
    static const char *fnName = "glTexCoord3bvOES";

    beforeCommand(fnName, _api.glTexCoord3bv);
    _api.glTexCoord3bv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord4bOES().
void OESByteCoordinatesAPI::texCoord4B(GLbyte s, GLbyte t, GLbyte r, GLbyte q) const
{
    static const char *fnName = "glTexCoord4bOES";

    beforeCommand(fnName, _api.glTexCoord4b);
    _api.glTexCoord4b(s, t, r, q);
    afterCommand(fnName);
}

// Calls glTexCoord4bvOES().
void OESByteCoordinatesAPI::texCoord4BV(const GLbyte *coords) const
{
    static const char *fnName = "glTexCoord4bvOES";

    beforeCommand(fnName, _api.glTexCoord4bv);
    _api.glTexCoord4bv(coords);
    afterCommand(fnName);
}

// Calls glVertex2bOES().
void OESByteCoordinatesAPI::vertex2B(GLbyte x, GLbyte y) const
{
    static const char *fnName = "glVertex2bOES";

    beforeCommand(fnName, _api.glVertex2b);
    _api.glVertex2b(x, y);
    afterCommand(fnName);
}

// Calls glVertex2bvOES().
void OESByteCoordinatesAPI::vertex2BV(const GLbyte *coords) const
{
    static const char *fnName = "glVertex2bvOES";

    beforeCommand(fnName, _api.glVertex2bv);
    _api.glVertex2bv(coords);
    afterCommand(fnName);
}

// Calls glVertex3bOES().
void OESByteCoordinatesAPI::vertex3B(GLbyte x, GLbyte y, GLbyte z) const
{
    static const char *fnName = "glVertex3bOES";

    beforeCommand(fnName, _api.glVertex3b);
    _api.glVertex3b(x, y, z);
    afterCommand(fnName);
}

// Calls glVertex3bvOES().
void OESByteCoordinatesAPI::vertex3BV(const GLbyte *coords) const
{
    static const char *fnName = "glVertex3bvOES";

    beforeCommand(fnName, _api.glVertex3bv);
    _api.glVertex3bv(coords);
    afterCommand(fnName);
}

// Calls glVertex4bOES().
void OESByteCoordinatesAPI::vertex4B(GLbyte x, GLbyte y, GLbyte z, GLbyte w) const
{
    static const char *fnName = "glVertex4bOES";

    beforeCommand(fnName, _api.glVertex4b);
    _api.glVertex4b(x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertex4bvOES().
void OESByteCoordinatesAPI::vertex4BV(const GLbyte *coords) const
{
    static const char *fnName = "glVertex4bvOES";

    beforeCommand(fnName, _api.glVertex4bv);
    _api.glVertex4bv(coords);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// OESFixedPointAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_OES_fixed_point extension.
OESFixedPointAPI::OESFixedPointAPI() :
    BaseExtension("GL_OES_fixed_point")
{
}

// Grant read-only access to the underlying function pointers.
const OESFixedPoint &OESFixedPointAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_OES_fixed_point entry points.
void OESFixedPointAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAccumxOES().
void OESFixedPointAPI::accumx(GLenum op, GLfixed value) const
{
    static const char *fnName = "glAccumxOES";

    beforeCommand(fnName, _api.glAccumx);
    _api.glAccumx(op, value);
    afterCommand(fnName);
}

// Calls glAlphaFuncxOES().
void OESFixedPointAPI::alphaFuncx(AlphaFunction func, GLfixed ref) const
{
    static const char *fnName = "glAlphaFuncxOES";

    beforeCommand(fnName, _api.glAlphaFuncx);
    _api.glAlphaFuncx(toScalar(func), ref);
    afterCommand(fnName);
}

// Calls glBitmapxOES().
void OESFixedPointAPI::bitmapx(GLsizei width, GLsizei height, GLfixed xorig,
                               GLfixed yorig, GLfixed xmove, GLfixed ymove,
                               const GLubyte *bitmap) const
{
    static const char *fnName = "glBitmapxOES";

    beforeCommand(fnName, _api.glBitmapx);
    _api.glBitmapx(width, height, xorig, yorig, xmove, ymove, bitmap);
    afterCommand(fnName);
}

// Calls glBlendColorxOES().
void OESFixedPointAPI::blendColorx(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha) const
{
    static const char *fnName = "glBlendColorxOES";

    beforeCommand(fnName, _api.glBlendColorx);
    _api.glBlendColorx(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glClearAccumxOES().
void OESFixedPointAPI::clearAccumx(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha) const
{
    static const char *fnName = "glClearAccumxOES";

    beforeCommand(fnName, _api.glClearAccumx);
    _api.glClearAccumx(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glClearColorxOES().
void OESFixedPointAPI::clearColorx(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha) const
{
    static const char *fnName = "glClearColorxOES";

    beforeCommand(fnName, _api.glClearColorx);
    _api.glClearColorx(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glClearDepthxOES().
void OESFixedPointAPI::clearDepthx(GLfixed depth) const
{
    static const char *fnName = "glClearDepthxOES";

    beforeCommand(fnName, _api.glClearDepthx);
    _api.glClearDepthx(depth);
    afterCommand(fnName);
}

// Calls glClipPlanexOES().
void OESFixedPointAPI::clipPlanex(ClipPlaneName plane, const GLfixed *equation) const
{
    static const char *fnName = "glClipPlanexOES";

    beforeCommand(fnName, _api.glClipPlanex);
    _api.glClipPlanex(toScalar(plane), equation);
    afterCommand(fnName);
}

// Calls glColor3xOES().
void OESFixedPointAPI::color3X(GLfixed red, GLfixed green, GLfixed blue) const
{
    static const char *fnName = "glColor3xOES";

    beforeCommand(fnName, _api.glColor3x);
    _api.glColor3x(red, green, blue);
    afterCommand(fnName);
}

// Calls glColor3xvOES().
void OESFixedPointAPI::color3XV(const GLfixed *components) const
{
    static const char *fnName = "glColor3xvOES";

    beforeCommand(fnName, _api.glColor3xv);
    _api.glColor3xv(components);
    afterCommand(fnName);
}

// Calls glColor4xOES().
void OESFixedPointAPI::color4X(GLfixed red, GLfixed green, GLfixed blue,
                               GLfixed alpha) const
{
    static const char *fnName = "glColor4xOES";

    beforeCommand(fnName, _api.glColor4x);
    _api.glColor4x(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glColor4xvOES().
void OESFixedPointAPI::color4XV(const GLfixed *components) const
{
    static const char *fnName = "glColor4xvOES";

    beforeCommand(fnName, _api.glColor4xv);
    _api.glColor4xv(components);
    afterCommand(fnName);
}

// Calls glConvolutionParameterxOES().
void OESFixedPointAPI::convolutionParameterx(ConvolutionTargetEXT target,
                                             ConvolutionParameterEXT pname,
                                             GLfixed param) const
{
    static const char *fnName = "glConvolutionParameterxOES";

    beforeCommand(fnName, _api.glConvolutionParameterx);
    _api.glConvolutionParameterx(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glConvolutionParameterxvOES().
void OESFixedPointAPI::convolutionParameterxV(ConvolutionTargetEXT target,
                                              ConvolutionParameterEXT pname,
                                              const GLfixed *params) const
{
    static const char *fnName = "glConvolutionParameterxvOES";

    beforeCommand(fnName, _api.glConvolutionParameterxv);
    _api.glConvolutionParameterxv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glDepthRangexOES().
void OESFixedPointAPI::depthRangex(GLfixed n, GLfixed f) const
{
    static const char *fnName = "glDepthRangexOES";

    beforeCommand(fnName, _api.glDepthRangex);
    _api.glDepthRangex(n, f);
    afterCommand(fnName);
}

// Calls glEvalCoord1xOES().
void OESFixedPointAPI::evalCoord1X(GLfixed u) const
{
    static const char *fnName = "glEvalCoord1xOES";

    beforeCommand(fnName, _api.glEvalCoord1x);
    _api.glEvalCoord1x(u);
    afterCommand(fnName);
}

// Calls glEvalCoord1xvOES().
void OESFixedPointAPI::evalCoord1XV(const GLfixed *coords) const
{
    static const char *fnName = "glEvalCoord1xvOES";

    beforeCommand(fnName, _api.glEvalCoord1xv);
    _api.glEvalCoord1xv(coords);
    afterCommand(fnName);
}

// Calls glEvalCoord2xOES().
void OESFixedPointAPI::evalCoord2X(GLfixed u, GLfixed v) const
{
    static const char *fnName = "glEvalCoord2xOES";

    beforeCommand(fnName, _api.glEvalCoord2x);
    _api.glEvalCoord2x(u, v);
    afterCommand(fnName);
}

// Calls glEvalCoord2xvOES().
void OESFixedPointAPI::evalCoord2XV(const GLfixed *coords) const
{
    static const char *fnName = "glEvalCoord2xvOES";

    beforeCommand(fnName, _api.glEvalCoord2xv);
    _api.glEvalCoord2xv(coords);
    afterCommand(fnName);
}

// Calls glFeedbackBufferxOES().
void OESFixedPointAPI::feedbackBufferx(GLsizei n, GLenum type,
                                       const GLfixed *buffer) const
{
    static const char *fnName = "glFeedbackBufferxOES";

    beforeCommand(fnName, _api.glFeedbackBufferx);
    _api.glFeedbackBufferx(n, type, buffer);
    afterCommand(fnName);
}

// Calls glFogxOES().
void OESFixedPointAPI::fogx(GLenum pname, GLfixed param) const
{
    static const char *fnName = "glFogxOES";

    beforeCommand(fnName, _api.glFogx);
    _api.glFogx(pname, param);
    afterCommand(fnName);
}

// Calls glFogxvOES().
void OESFixedPointAPI::fogxV(GLenum pname, const GLfixed *param) const
{
    static const char *fnName = "glFogxvOES";

    beforeCommand(fnName, _api.glFogxv);
    _api.glFogxv(pname, param);
    afterCommand(fnName);
}

// Calls glFrustumxOES().
void OESFixedPointAPI::frustumx(GLfixed l, GLfixed r, GLfixed b, GLfixed t,
                                GLfixed n, GLfixed f) const
{
    static const char *fnName = "glFrustumxOES";

    beforeCommand(fnName, _api.glFrustumx);
    _api.glFrustumx(l, r, b, t, n, f);
    afterCommand(fnName);
}

// Calls glGetClipPlanexOES().
void OESFixedPointAPI::getClipPlanex(ClipPlaneName plane, GLfixed *equation) const
{
    static const char *fnName = "glGetClipPlanexOES";

    beforeCommand(fnName, _api.glGetClipPlanex);
    _api.glGetClipPlanex(toScalar(plane), equation);
    afterCommand(fnName);
}

// Calls glGetConvolutionParameterxvOES().
void OESFixedPointAPI::getConvolutionParameterxV(GLenum target, GLenum pname,
                                                 GLfixed *params) const
{
    static const char *fnName = "glGetConvolutionParameterxvOES";

    beforeCommand(fnName, _api.glGetConvolutionParameterxv);
    _api.glGetConvolutionParameterxv(target, pname, params);
    afterCommand(fnName);
}

// Calls glGetFixedvOES().
void OESFixedPointAPI::getFixedv(GetPName pname, GLfixed *params) const
{
    static const char *fnName = "glGetFixedvOES";

    beforeCommand(fnName, _api.glGetFixedv);
    _api.glGetFixedv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetHistogramParameterxvOES().
void OESFixedPointAPI::getHistogramParameterxV(HistogramTargetEXT target,
                                               GetHistogramParameterPNameEXT pname,
                                               GLfixed *params) const
{
    static const char *fnName = "glGetHistogramParameterxvOES";

    beforeCommand(fnName, _api.glGetHistogramParameterxv);
    _api.glGetHistogramParameterxv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetLightxOES().
void OESFixedPointAPI::getLightx(LightName light, GLenum pname, GLfixed *params) const
{
    static const char *fnName = "glGetLightxOES";

    beforeCommand(fnName, _api.glGetLightx);
    _api.glGetLightx(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glGetMapxvOES().
void OESFixedPointAPI::getMapxV(MapTarget target, GLenum query, GLfixed *v) const
{
    static const char *fnName = "glGetMapxvOES";

    beforeCommand(fnName, _api.glGetMapxv);
    _api.glGetMapxv(toScalar(target), query, v);
    afterCommand(fnName);
}

// Calls glGetMaterialxOES().
void OESFixedPointAPI::getMaterialx(MaterialFace face, GLenum pname,
                                    GLfixed param) const
{
    static const char *fnName = "glGetMaterialxOES";

    beforeCommand(fnName, _api.glGetMaterialx);
    _api.glGetMaterialx(toScalar(face), pname, param);
    afterCommand(fnName);
}

// Calls glGetPixelMapxv().
void OESFixedPointAPI::getPixelMapxV(GLenum map, GLint size, GLfixed *values) const
{
    static const char *fnName = "glGetPixelMapxv";

    beforeCommand(fnName, _api.glGetPixelMapxv);
    _api.glGetPixelMapxv(map, size, values);
    afterCommand(fnName);
}

// Calls glGetTexEnvxvOES().
void OESFixedPointAPI::getTexEnvxV(GLenum target, GLenum pname, GLfixed *params) const
{
    static const char *fnName = "glGetTexEnvxvOES";

    beforeCommand(fnName, _api.glGetTexEnvxv);
    _api.glGetTexEnvxv(target, pname, params);
    afterCommand(fnName);
}

// Calls glGetTexGenxvOES().
void OESFixedPointAPI::getTexGenxV(GLenum coord, TextureGenParameter pname,
                                   GLfixed *params) const
{
    static const char *fnName = "glGetTexGenxvOES";

    beforeCommand(fnName, _api.glGetTexGenxv);
    _api.glGetTexGenxv(coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTexLevelParameterxvOES().
void OESFixedPointAPI::getTexLevelParameterxV(TextureTarget target, GLint level,
                                              GetTextureParameter pname,
                                              GLfixed *params) const
{
    static const char *fnName = "glGetTexLevelParameterxvOES";

    beforeCommand(fnName, _api.glGetTexLevelParameterxv);
    _api.glGetTexLevelParameterxv(toScalar(target), level, toScalar(pname),
                                  params);
    afterCommand(fnName);
}

// Calls glGetTexParameterxvOES().
void OESFixedPointAPI::getTexParameterxV(TextureTarget target,
                                         GetTextureParameter pname,
                                         GLfixed *params) const
{
    static const char *fnName = "glGetTexParameterxvOES";

    beforeCommand(fnName, _api.glGetTexParameterxv);
    _api.glGetTexParameterxv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIndexxOES().
void OESFixedPointAPI::indexx(GLfixed component) const
{
    static const char *fnName = "glIndexxOES";

    beforeCommand(fnName, _api.glIndexx);
    _api.glIndexx(component);
    afterCommand(fnName);
}

// Calls glIndexxvOES().
void OESFixedPointAPI::indexxV(const GLfixed *component) const
{
    static const char *fnName = "glIndexxvOES";

    beforeCommand(fnName, _api.glIndexxv);
    _api.glIndexxv(component);
    afterCommand(fnName);
}

// Calls glLightModelxOES().
void OESFixedPointAPI::lightModelx(LightModelParameter pname, GLfixed param) const
{
    static const char *fnName = "glLightModelxOES";

    beforeCommand(fnName, _api.glLightModelx);
    _api.glLightModelx(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glLightModelxvOES().
void OESFixedPointAPI::lightModelxV(LightModelParameter pname,
                                    const GLfixed *param) const
{
    static const char *fnName = "glLightModelxvOES";

    beforeCommand(fnName, _api.glLightModelxv);
    _api.glLightModelxv(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glLightxOES().
void OESFixedPointAPI::lightx(LightName light, GLenum pname, GLfixed param) const
{
    static const char *fnName = "glLightxOES";

    beforeCommand(fnName, _api.glLightx);
    _api.glLightx(toScalar(light), pname, param);
    afterCommand(fnName);
}

// Calls glLightxvOES().
void OESFixedPointAPI::lightxV(LightName light, GLenum pname,
                               const GLfixed *params) const
{
    static const char *fnName = "glLightxvOES";

    beforeCommand(fnName, _api.glLightxv);
    _api.glLightxv(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glLineWidthxOES().
void OESFixedPointAPI::lineWidthx(GLfixed width) const
{
    static const char *fnName = "glLineWidthxOES";

    beforeCommand(fnName, _api.glLineWidthx);
    _api.glLineWidthx(width);
    afterCommand(fnName);
}

// Calls glLoadMatrixxOES().
void OESFixedPointAPI::loadMatrixx(const GLfixed *m) const
{
    static const char *fnName = "glLoadMatrixxOES";

    beforeCommand(fnName, _api.glLoadMatrixx);
    _api.glLoadMatrixx(m);
    afterCommand(fnName);
}

// Calls glLoadTransposeMatrixxOES().
void OESFixedPointAPI::loadTransposeMatrixx(const GLfixed *m) const
{
    static const char *fnName = "glLoadTransposeMatrixxOES";

    beforeCommand(fnName, _api.glLoadTransposeMatrixx);
    _api.glLoadTransposeMatrixx(m);
    afterCommand(fnName);
}

// Calls glMap1xOES().
void OESFixedPointAPI::map1X(MapTarget target, GLfixed u1, GLfixed u2,
                             GLint stride, GLint order, GLfixed points) const
{
    static const char *fnName = "glMap1xOES";

    beforeCommand(fnName, _api.glMap1x);
    _api.glMap1x(toScalar(target), u1, u2, stride, order, points);
    afterCommand(fnName);
}

// Calls glMap2xOES().
void OESFixedPointAPI::map2X(MapTarget target, GLfixed u1, GLfixed u2,
                             GLint ustride, GLint uorder, GLfixed v1, GLfixed v2,
                             GLint vstride, GLint vorder, GLfixed points) const
{
    static const char *fnName = "glMap2xOES";

    beforeCommand(fnName, _api.glMap2x);
    _api.glMap2x(toScalar(target), u1, u2, ustride, uorder, v1, v2, vstride,
                 vorder, points);
    afterCommand(fnName);
}

// Calls glMapGrid1xOES().
void OESFixedPointAPI::mapGRID1X(GLint n, GLfixed u1, GLfixed u2) const
{
    static const char *fnName = "glMapGrid1xOES";

    beforeCommand(fnName, _api.glMapGrid1x);
    _api.glMapGrid1x(n, u1, u2);
    afterCommand(fnName);
}

// Calls glMapGrid2xOES().
void OESFixedPointAPI::mapGRID2X(GLint n, GLfixed u1, GLfixed u2, GLfixed v1,
                                 GLfixed v2) const
{
    static const char *fnName = "glMapGrid2xOES";

    beforeCommand(fnName, _api.glMapGrid2x);
    _api.glMapGrid2x(n, u1, u2, v1, v2);
    afterCommand(fnName);
}

// Calls glMaterialxOES().
void OESFixedPointAPI::materialx(MaterialFace face, GLenum pname, GLfixed param) const
{
    static const char *fnName = "glMaterialxOES";

    beforeCommand(fnName, _api.glMaterialx);
    _api.glMaterialx(toScalar(face), pname, param);
    afterCommand(fnName);
}

// Calls glMaterialxvOES().
void OESFixedPointAPI::materialxV(MaterialFace face, GLenum pname,
                                  const GLfixed *param) const
{
    static const char *fnName = "glMaterialxvOES";

    beforeCommand(fnName, _api.glMaterialxv);
    _api.glMaterialxv(toScalar(face), pname, param);
    afterCommand(fnName);
}

// Calls glMultMatrixxOES().
void OESFixedPointAPI::multMatrixx(const GLfixed *m) const
{
    static const char *fnName = "glMultMatrixxOES";

    beforeCommand(fnName, _api.glMultMatrixx);
    _api.glMultMatrixx(m);
    afterCommand(fnName);
}

// Calls glMultTransposeMatrixxOES().
void OESFixedPointAPI::multTransposeMatrixx(const GLfixed *m) const
{
    static const char *fnName = "glMultTransposeMatrixxOES";

    beforeCommand(fnName, _api.glMultTransposeMatrixx);
    _api.glMultTransposeMatrixx(m);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1xOES().
void OESFixedPointAPI::multiTexCoord1X(TextureUnit texture, GLfixed s) const
{
    static const char *fnName = "glMultiTexCoord1xOES";

    beforeCommand(fnName, _api.glMultiTexCoord1x);
    _api.glMultiTexCoord1x(toScalar(texture), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1xvOES().
void OESFixedPointAPI::multiTexCoord1XV(TextureUnit texture,
                                        const GLfixed *coords) const
{
    static const char *fnName = "glMultiTexCoord1xvOES";

    beforeCommand(fnName, _api.glMultiTexCoord1xv);
    _api.glMultiTexCoord1xv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2xOES().
void OESFixedPointAPI::multiTexCoord2X(TextureUnit texture, GLfixed s, GLfixed t) const
{
    static const char *fnName = "glMultiTexCoord2xOES";

    beforeCommand(fnName, _api.glMultiTexCoord2x);
    _api.glMultiTexCoord2x(toScalar(texture), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2xvOES().
void OESFixedPointAPI::multiTexCoord2XV(TextureUnit texture,
                                        const GLfixed *coords) const
{
    static const char *fnName = "glMultiTexCoord2xvOES";

    beforeCommand(fnName, _api.glMultiTexCoord2xv);
    _api.glMultiTexCoord2xv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3xOES().
void OESFixedPointAPI::multiTexCoord3X(TextureUnit texture, GLfixed s, GLfixed t,
                                       GLfixed r) const
{
    static const char *fnName = "glMultiTexCoord3xOES";

    beforeCommand(fnName, _api.glMultiTexCoord3x);
    _api.glMultiTexCoord3x(toScalar(texture), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3xvOES().
void OESFixedPointAPI::multiTexCoord3XV(TextureUnit texture,
                                        const GLfixed *coords) const
{
    static const char *fnName = "glMultiTexCoord3xvOES";

    beforeCommand(fnName, _api.glMultiTexCoord3xv);
    _api.glMultiTexCoord3xv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4xOES().
void OESFixedPointAPI::multiTexCoord4X(TextureUnit texture, GLfixed s, GLfixed t,
                                       GLfixed r, GLfixed q) const
{
    static const char *fnName = "glMultiTexCoord4xOES";

    beforeCommand(fnName, _api.glMultiTexCoord4x);
    _api.glMultiTexCoord4x(toScalar(texture), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4xvOES().
void OESFixedPointAPI::multiTexCoord4XV(TextureUnit texture,
                                        const GLfixed *coords) const
{
    static const char *fnName = "glMultiTexCoord4xvOES";

    beforeCommand(fnName, _api.glMultiTexCoord4xv);
    _api.glMultiTexCoord4xv(toScalar(texture), coords);
    afterCommand(fnName);
}

// Calls glNormal3xOES().
void OESFixedPointAPI::normal3X(GLfixed nx, GLfixed ny, GLfixed nz) const
{
    static const char *fnName = "glNormal3xOES";

    beforeCommand(fnName, _api.glNormal3x);
    _api.glNormal3x(nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormal3xvOES().
void OESFixedPointAPI::normal3XV(const GLfixed *coords) const
{
    static const char *fnName = "glNormal3xvOES";

    beforeCommand(fnName, _api.glNormal3xv);
    _api.glNormal3xv(coords);
    afterCommand(fnName);
}

// Calls glOrthoxOES().
void OESFixedPointAPI::orthox(GLfixed l, GLfixed r, GLfixed b, GLfixed t,
                              GLfixed n, GLfixed f) const
{
    static const char *fnName = "glOrthoxOES";

    beforeCommand(fnName, _api.glOrthox);
    _api.glOrthox(l, r, b, t, n, f);
    afterCommand(fnName);
}

// Calls glPassThroughxOES().
void OESFixedPointAPI::passThroughx(GLfixed token) const
{
    static const char *fnName = "glPassThroughxOES";

    beforeCommand(fnName, _api.glPassThroughx);
    _api.glPassThroughx(token);
    afterCommand(fnName);
}

// Calls glPixelMapx().
void OESFixedPointAPI::pixelMapx(GLenum map, GLint size, const GLfixed *values) const
{
    static const char *fnName = "glPixelMapx";

    beforeCommand(fnName, _api.glPixelMapx);
    _api.glPixelMapx(map, size, values);
    afterCommand(fnName);
}

// Calls glPixelStorex().
void OESFixedPointAPI::pixelStorex(PixelStoreParameter pname, GLfixed param) const
{
    static const char *fnName = "glPixelStorex";

    beforeCommand(fnName, _api.glPixelStorex);
    _api.glPixelStorex(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelTransferxOES().
void OESFixedPointAPI::pixelTransferx(PixelTransferParameter pname,
                                      GLfixed param) const
{
    static const char *fnName = "glPixelTransferxOES";

    beforeCommand(fnName, _api.glPixelTransferx);
    _api.glPixelTransferx(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelZoomxOES().
void OESFixedPointAPI::pixelZoomx(GLfixed xfactor, GLfixed yfactor) const
{
    static const char *fnName = "glPixelZoomxOES";

    beforeCommand(fnName, _api.glPixelZoomx);
    _api.glPixelZoomx(xfactor, yfactor);
    afterCommand(fnName);
}

// Calls glPointParameterxvOES().
void OESFixedPointAPI::pointParameterxV(PointParameterNameARB pname,
                                        const GLfixed *params) const
{
    static const char *fnName = "glPointParameterxvOES";

    beforeCommand(fnName, _api.glPointParameterxv);
    _api.glPointParameterxv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glPointSizexOES().
void OESFixedPointAPI::pointSizex(GLfixed size) const
{
    static const char *fnName = "glPointSizexOES";

    beforeCommand(fnName, _api.glPointSizex);
    _api.glPointSizex(size);
    afterCommand(fnName);
}

// Calls glPolygonOffsetxOES().
void OESFixedPointAPI::polygonOffsetx(GLfixed factor, GLfixed units) const
{
    static const char *fnName = "glPolygonOffsetxOES";

    beforeCommand(fnName, _api.glPolygonOffsetx);
    _api.glPolygonOffsetx(factor, units);
    afterCommand(fnName);
}

// Calls glPrioritizeTexturesxOES().
void OESFixedPointAPI::prioritizeTexturesx(GLsizei n,
                                           const TextureName *textures,
                                           const GLfixed *priorities) const
{
    static const char *fnName = "glPrioritizeTexturesxOES";

    beforeCommand(fnName, _api.glPrioritizeTexturesx);
    _api.glPrioritizeTexturesx(n, reinterpret_cast<const GLuint *>(textures),
                               priorities);
    afterCommand(fnName);
}

// Calls glRasterPos2xOES().
void OESFixedPointAPI::rasterPOS2X(GLfixed x, GLfixed y) const
{
    static const char *fnName = "glRasterPos2xOES";

    beforeCommand(fnName, _api.glRasterPos2x);
    _api.glRasterPos2x(x, y);
    afterCommand(fnName);
}

// Calls glRasterPos2xvOES().
void OESFixedPointAPI::rasterPOS2XV(const GLfixed *coords) const
{
    static const char *fnName = "glRasterPos2xvOES";

    beforeCommand(fnName, _api.glRasterPos2xv);
    _api.glRasterPos2xv(coords);
    afterCommand(fnName);
}

// Calls glRasterPos3xOES().
void OESFixedPointAPI::rasterPOS3X(GLfixed x, GLfixed y, GLfixed z) const
{
    static const char *fnName = "glRasterPos3xOES";

    beforeCommand(fnName, _api.glRasterPos3x);
    _api.glRasterPos3x(x, y, z);
    afterCommand(fnName);
}

// Calls glRasterPos3xvOES().
void OESFixedPointAPI::rasterPOS3XV(const GLfixed *coords) const
{
    static const char *fnName = "glRasterPos3xvOES";

    beforeCommand(fnName, _api.glRasterPos3xv);
    _api.glRasterPos3xv(coords);
    afterCommand(fnName);
}

// Calls glRasterPos4xOES().
void OESFixedPointAPI::rasterPOS4X(GLfixed x, GLfixed y, GLfixed z, GLfixed w) const
{
    static const char *fnName = "glRasterPos4xOES";

    beforeCommand(fnName, _api.glRasterPos4x);
    _api.glRasterPos4x(x, y, z, w);
    afterCommand(fnName);
}

// Calls glRasterPos4xvOES().
void OESFixedPointAPI::rasterPOS4XV(const GLfixed *coords) const
{
    static const char *fnName = "glRasterPos4xvOES";

    beforeCommand(fnName, _api.glRasterPos4xv);
    _api.glRasterPos4xv(coords);
    afterCommand(fnName);
}

// Calls glRectxOES().
void OESFixedPointAPI::rectx(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2) const
{
    static const char *fnName = "glRectxOES";

    beforeCommand(fnName, _api.glRectx);
    _api.glRectx(x1, y1, x2, y2);
    afterCommand(fnName);
}

// Calls glRectxvOES().
void OESFixedPointAPI::rectxV(const GLfixed *v1, const GLfixed *v2) const
{
    static const char *fnName = "glRectxvOES";

    beforeCommand(fnName, _api.glRectxv);
    _api.glRectxv(v1, v2);
    afterCommand(fnName);
}

// Calls glRotatexOES().
void OESFixedPointAPI::rotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z) const
{
    static const char *fnName = "glRotatexOES";

    beforeCommand(fnName, _api.glRotatex);
    _api.glRotatex(angle, x, y, z);
    afterCommand(fnName);
}

// Calls glScalexOES().
void OESFixedPointAPI::scalex(GLfixed x, GLfixed y, GLfixed z) const
{
    static const char *fnName = "glScalexOES";

    beforeCommand(fnName, _api.glScalex);
    _api.glScalex(x, y, z);
    afterCommand(fnName);
}

// Calls glTexCoord1xOES().
void OESFixedPointAPI::texCoord1X(GLfixed s) const
{
    static const char *fnName = "glTexCoord1xOES";

    beforeCommand(fnName, _api.glTexCoord1x);
    _api.glTexCoord1x(s);
    afterCommand(fnName);
}

// Calls glTexCoord1xvOES().
void OESFixedPointAPI::texCoord1XV(const GLfixed *coords) const
{
    static const char *fnName = "glTexCoord1xvOES";

    beforeCommand(fnName, _api.glTexCoord1xv);
    _api.glTexCoord1xv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord2xOES().
void OESFixedPointAPI::texCoord2X(GLfixed s, GLfixed t) const
{
    static const char *fnName = "glTexCoord2xOES";

    beforeCommand(fnName, _api.glTexCoord2x);
    _api.glTexCoord2x(s, t);
    afterCommand(fnName);
}

// Calls glTexCoord2xvOES().
void OESFixedPointAPI::texCoord2XV(const GLfixed *coords) const
{
    static const char *fnName = "glTexCoord2xvOES";

    beforeCommand(fnName, _api.glTexCoord2xv);
    _api.glTexCoord2xv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord3xOES().
void OESFixedPointAPI::texCoord3X(GLfixed s, GLfixed t, GLfixed r) const
{
    static const char *fnName = "glTexCoord3xOES";

    beforeCommand(fnName, _api.glTexCoord3x);
    _api.glTexCoord3x(s, t, r);
    afterCommand(fnName);
}

// Calls glTexCoord3xvOES().
void OESFixedPointAPI::texCoord3XV(const GLfixed *coords) const
{
    static const char *fnName = "glTexCoord3xvOES";

    beforeCommand(fnName, _api.glTexCoord3xv);
    _api.glTexCoord3xv(coords);
    afterCommand(fnName);
}

// Calls glTexCoord4xOES().
void OESFixedPointAPI::texCoord4X(GLfixed s, GLfixed t, GLfixed r, GLfixed q) const
{
    static const char *fnName = "glTexCoord4xOES";

    beforeCommand(fnName, _api.glTexCoord4x);
    _api.glTexCoord4x(s, t, r, q);
    afterCommand(fnName);
}

// Calls glTexCoord4xvOES().
void OESFixedPointAPI::texCoord4XV(const GLfixed *coords) const
{
    static const char *fnName = "glTexCoord4xvOES";

    beforeCommand(fnName, _api.glTexCoord4xv);
    _api.glTexCoord4xv(coords);
    afterCommand(fnName);
}

// Calls glTexEnvxOES().
void OESFixedPointAPI::texEnvx(GLenum target, GLenum pname, GLfixed param) const
{
    static const char *fnName = "glTexEnvxOES";

    beforeCommand(fnName, _api.glTexEnvx);
    _api.glTexEnvx(target, pname, param);
    afterCommand(fnName);
}

// Calls glTexEnvxvOES().
void OESFixedPointAPI::texEnvxV(GLenum target, GLenum pname,
                                const GLfixed *params) const
{
    static const char *fnName = "glTexEnvxvOES";

    beforeCommand(fnName, _api.glTexEnvxv);
    _api.glTexEnvxv(target, pname, params);
    afterCommand(fnName);
}

// Calls glTexGenxOES().
void OESFixedPointAPI::texGenx(GLenum coord, TextureGenParameter pname,
                               GLfixed param) const
{
    static const char *fnName = "glTexGenxOES";

    beforeCommand(fnName, _api.glTexGenx);
    _api.glTexGenx(coord, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexGenxvOES().
void OESFixedPointAPI::texGenxV(GLenum coord, TextureGenParameter pname,
                                const GLfixed *params) const
{
    static const char *fnName = "glTexGenxvOES";

    beforeCommand(fnName, _api.glTexGenxv);
    _api.glTexGenxv(coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTexParameterxOES().
void OESFixedPointAPI::texParameterx(TextureTarget target,
                                     GetTextureParameter pname, GLfixed param) const
{
    static const char *fnName = "glTexParameterxOES";

    beforeCommand(fnName, _api.glTexParameterx);
    _api.glTexParameterx(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexParameterxvOES().
void OESFixedPointAPI::texParameterxV(TextureTarget target,
                                      GetTextureParameter pname,
                                      const GLfixed *params) const
{
    static const char *fnName = "glTexParameterxvOES";

    beforeCommand(fnName, _api.glTexParameterxv);
    _api.glTexParameterxv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTranslatexOES().
void OESFixedPointAPI::translatex(GLfixed x, GLfixed y, GLfixed z) const
{
    static const char *fnName = "glTranslatexOES";

    beforeCommand(fnName, _api.glTranslatex);
    _api.glTranslatex(x, y, z);
    afterCommand(fnName);
}

// Calls glVertex2xOES().
void OESFixedPointAPI::vertex2X(GLfixed x) const
{
    static const char *fnName = "glVertex2xOES";

    beforeCommand(fnName, _api.glVertex2x);
    _api.glVertex2x(x);
    afterCommand(fnName);
}

// Calls glVertex2xvOES().
void OESFixedPointAPI::vertex2XV(const GLfixed *coords) const
{
    static const char *fnName = "glVertex2xvOES";

    beforeCommand(fnName, _api.glVertex2xv);
    _api.glVertex2xv(coords);
    afterCommand(fnName);
}

// Calls glVertex3xOES().
void OESFixedPointAPI::vertex3X(GLfixed x, GLfixed y) const
{
    static const char *fnName = "glVertex3xOES";

    beforeCommand(fnName, _api.glVertex3x);
    _api.glVertex3x(x, y);
    afterCommand(fnName);
}

// Calls glVertex3xvOES().
void OESFixedPointAPI::vertex3XV(const GLfixed *coords) const
{
    static const char *fnName = "glVertex3xvOES";

    beforeCommand(fnName, _api.glVertex3xv);
    _api.glVertex3xv(coords);
    afterCommand(fnName);
}

// Calls glVertex4xOES().
void OESFixedPointAPI::vertex4X(GLfixed x, GLfixed y, GLfixed z) const
{
    static const char *fnName = "glVertex4xOES";

    beforeCommand(fnName, _api.glVertex4x);
    _api.glVertex4x(x, y, z);
    afterCommand(fnName);
}

// Calls glVertex4xvOES().
void OESFixedPointAPI::vertex4XV(const GLfixed *coords) const
{
    static const char *fnName = "glVertex4xvOES";

    beforeCommand(fnName, _api.glVertex4xv);
    _api.glVertex4xv(coords);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// OESQueryMatrixAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_OES_query_matrix extension.
OESQueryMatrixAPI::OESQueryMatrixAPI() :
    BaseExtension("GL_OES_query_matrix")
{
}

// Grant read-only access to the underlying function pointers.
const OESQueryMatrix &OESQueryMatrixAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_OES_query_matrix entry points.
void OESQueryMatrixAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glQueryMatrixxOES().
GLbitfield OESQueryMatrixAPI::queryMatrixx(GLfixed *mantissa, GLint *exponent) const
{
    static const char *fnName = "glQueryMatrixxOES";

    beforeCommand(fnName, _api.glQueryMatrixx);
    GLbitfield result = _api.glQueryMatrixx(mantissa, exponent);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// OESSinglePrecisionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_OES_single_precision extension.
OESSinglePrecisionAPI::OESSinglePrecisionAPI() :
    BaseExtension("GL_OES_single_precision")
{
}

// Grant read-only access to the underlying function pointers.
const OESSinglePrecision &OESSinglePrecisionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_OES_single_precision entry points.
void OESSinglePrecisionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClearDepthfOES().
void OESSinglePrecisionAPI::clearDepthF(GLclampf depth) const
{
    static const char *fnName = "glClearDepthfOES";

    beforeCommand(fnName, _api.glClearDepthf);
    _api.glClearDepthf(depth);
    afterCommand(fnName);
}

// Calls glClipPlanefOES().
void OESSinglePrecisionAPI::clipPlaneF(ClipPlaneName plane,
                                       const GLfloat *equation) const
{
    static const char *fnName = "glClipPlanefOES";

    beforeCommand(fnName, _api.glClipPlanef);
    _api.glClipPlanef(toScalar(plane), equation);
    afterCommand(fnName);
}

// Calls glDepthRangefOES().
void OESSinglePrecisionAPI::depthRangeF(GLclampf n, GLclampf f) const
{
    static const char *fnName = "glDepthRangefOES";

    beforeCommand(fnName, _api.glDepthRangef);
    _api.glDepthRangef(n, f);
    afterCommand(fnName);
}

// Calls glFrustumfOES().
void OESSinglePrecisionAPI::frustumF(GLfloat l, GLfloat r, GLfloat b, GLfloat t,
                                     GLfloat n, GLfloat f) const
{
    static const char *fnName = "glFrustumfOES";

    beforeCommand(fnName, _api.glFrustumf);
    _api.glFrustumf(l, r, b, t, n, f);
    afterCommand(fnName);
}

// Calls glGetClipPlanefOES().
void OESSinglePrecisionAPI::getClipPlaneF(ClipPlaneName plane, GLfloat *equation) const
{
    static const char *fnName = "glGetClipPlanefOES";

    beforeCommand(fnName, _api.glGetClipPlanef);
    _api.glGetClipPlanef(toScalar(plane), equation);
    afterCommand(fnName);
}

// Calls glOrthofOES().
void OESSinglePrecisionAPI::orthoF(GLfloat l, GLfloat r, GLfloat b, GLfloat t,
                                   GLfloat n, GLfloat f) const
{
    static const char *fnName = "glOrthofOES";

    beforeCommand(fnName, _api.glOrthof);
    _api.glOrthof(l, r, b, t, n, f);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

