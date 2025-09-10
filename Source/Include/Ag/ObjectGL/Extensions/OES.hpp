//! @file Ag/ObjectGL/Extensions/OES.hpp
//! @brief The declaration of OES-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_OES_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OES_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_OES_byte_coordinates extension API specification.
struct OESByteCoordinates {
    // Public Members
    void (APIENTRY *glMultiTexCoord1b)(GLenum texture, GLbyte s);
    void (APIENTRY *glMultiTexCoord1bv)(GLenum texture, const GLbyte *coords);
    void (APIENTRY *glMultiTexCoord2b)(GLenum texture, GLbyte s, GLbyte t);
    void (APIENTRY *glMultiTexCoord2bv)(GLenum texture, const GLbyte *coords);
    void (APIENTRY *glMultiTexCoord3b)(GLenum texture, GLbyte s, GLbyte t,
                                       GLbyte r);
    void (APIENTRY *glMultiTexCoord3bv)(GLenum texture, const GLbyte *coords);
    void (APIENTRY *glMultiTexCoord4b)(GLenum texture, GLbyte s, GLbyte t,
                                       GLbyte r, GLbyte q);
    void (APIENTRY *glMultiTexCoord4bv)(GLenum texture, const GLbyte *coords);
    void (APIENTRY *glTexCoord1b)(GLbyte s);
    void (APIENTRY *glTexCoord1bv)(const GLbyte *coords);
    void (APIENTRY *glTexCoord2b)(GLbyte s, GLbyte t);
    void (APIENTRY *glTexCoord2bv)(const GLbyte *coords);
    void (APIENTRY *glTexCoord3b)(GLbyte s, GLbyte t, GLbyte r);
    void (APIENTRY *glTexCoord3bv)(const GLbyte *coords);
    void (APIENTRY *glTexCoord4b)(GLbyte s, GLbyte t, GLbyte r, GLbyte q);
    void (APIENTRY *glTexCoord4bv)(const GLbyte *coords);
    void (APIENTRY *glVertex2b)(GLbyte x, GLbyte y);
    void (APIENTRY *glVertex2bv)(const GLbyte *coords);
    void (APIENTRY *glVertex3b)(GLbyte x, GLbyte y, GLbyte z);
    void (APIENTRY *glVertex3bv)(const GLbyte *coords);
    void (APIENTRY *glVertex4b)(GLbyte x, GLbyte y, GLbyte z, GLbyte w);
    void (APIENTRY *glVertex4bv)(const GLbyte *coords);

    // Construction
    OESByteCoordinates();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OESByteCoordinates

// GL_OES_fixed_point extension API specification.
struct OESFixedPoint {
    // Public Members
    void (APIENTRY *glAccumx)(GLenum op, GLfixed value);
    void (APIENTRY *glAlphaFuncx)(GLenum func, GLfixed ref);
    void (APIENTRY *glBitmapx)(GLsizei width, GLsizei height, GLfixed xorig,
                               GLfixed yorig, GLfixed xmove, GLfixed ymove,
                               const GLubyte *bitmap);
    void (APIENTRY *glBlendColorx)(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha);
    void (APIENTRY *glClearAccumx)(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha);
    void (APIENTRY *glClearColorx)(GLfixed red, GLfixed green, GLfixed blue,
                                   GLfixed alpha);
    void (APIENTRY *glClearDepthx)(GLfixed depth);
    void (APIENTRY *glClipPlanex)(GLenum plane, const GLfixed *equation);
    void (APIENTRY *glColor3x)(GLfixed red, GLfixed green, GLfixed blue);
    void (APIENTRY *glColor3xv)(const GLfixed *components);
    void (APIENTRY *glColor4x)(GLfixed red, GLfixed green, GLfixed blue,
                               GLfixed alpha);
    void (APIENTRY *glColor4xv)(const GLfixed *components);
    void (APIENTRY *glConvolutionParameterx)(GLenum target, GLenum pname,
                                             GLfixed param);
    void (APIENTRY *glConvolutionParameterxv)(GLenum target, GLenum pname,
                                              const GLfixed *params);
    void (APIENTRY *glDepthRangex)(GLfixed n, GLfixed f);
    void (APIENTRY *glEvalCoord1x)(GLfixed u);
    void (APIENTRY *glEvalCoord1xv)(const GLfixed *coords);
    void (APIENTRY *glEvalCoord2x)(GLfixed u, GLfixed v);
    void (APIENTRY *glEvalCoord2xv)(const GLfixed *coords);
    void (APIENTRY *glFeedbackBufferx)(GLsizei n, GLenum type,
                                       const GLfixed *buffer);
    void (APIENTRY *glFogx)(GLenum pname, GLfixed param);
    void (APIENTRY *glFogxv)(GLenum pname, const GLfixed *param);
    void (APIENTRY *glFrustumx)(GLfixed l, GLfixed r, GLfixed b, GLfixed t,
                                GLfixed n, GLfixed f);
    void (APIENTRY *glGetClipPlanex)(GLenum plane, GLfixed *equation);
    void (APIENTRY *glGetConvolutionParameterxv)(GLenum target, GLenum pname,
                                                 GLfixed *params);
    void (APIENTRY *glGetFixedv)(GLenum pname, GLfixed *params);
    void (APIENTRY *glGetHistogramParameterxv)(GLenum target, GLenum pname,
                                               GLfixed *params);
    void (APIENTRY *glGetLightx)(GLenum light, GLenum pname, GLfixed *params);
    void (APIENTRY *glGetMapxv)(GLenum target, GLenum query, GLfixed *v);
    void (APIENTRY *glGetMaterialx)(GLenum face, GLenum pname, GLfixed param);
    void (APIENTRY *glGetPixelMapxv)(GLenum map, GLint size, GLfixed *values);
    void (APIENTRY *glGetTexEnvxv)(GLenum target, GLenum pname, GLfixed *params);
    void (APIENTRY *glGetTexGenxv)(GLenum coord, GLenum pname, GLfixed *params);
    void (APIENTRY *glGetTexLevelParameterxv)(GLenum target, GLint level,
                                              GLenum pname, GLfixed *params);
    void (APIENTRY *glGetTexParameterxv)(GLenum target, GLenum pname,
                                         GLfixed *params);
    void (APIENTRY *glIndexx)(GLfixed component);
    void (APIENTRY *glIndexxv)(const GLfixed *component);
    void (APIENTRY *glLightModelx)(GLenum pname, GLfixed param);
    void (APIENTRY *glLightModelxv)(GLenum pname, const GLfixed *param);
    void (APIENTRY *glLightx)(GLenum light, GLenum pname, GLfixed param);
    void (APIENTRY *glLightxv)(GLenum light, GLenum pname, const GLfixed *params);
    void (APIENTRY *glLineWidthx)(GLfixed width);
    void (APIENTRY *glLoadMatrixx)(const GLfixed *m);
    void (APIENTRY *glLoadTransposeMatrixx)(const GLfixed *m);
    void (APIENTRY *glMap1x)(GLenum target, GLfixed u1, GLfixed u2, GLint stride,
                             GLint order, GLfixed points);
    void (APIENTRY *glMap2x)(GLenum target, GLfixed u1, GLfixed u2,
                             GLint ustride, GLint uorder, GLfixed v1, GLfixed v2,
                             GLint vstride, GLint vorder, GLfixed points);
    void (APIENTRY *glMapGrid1x)(GLint n, GLfixed u1, GLfixed u2);
    void (APIENTRY *glMapGrid2x)(GLint n, GLfixed u1, GLfixed u2, GLfixed v1,
                                 GLfixed v2);
    void (APIENTRY *glMaterialx)(GLenum face, GLenum pname, GLfixed param);
    void (APIENTRY *glMaterialxv)(GLenum face, GLenum pname,
                                  const GLfixed *param);
    void (APIENTRY *glMultMatrixx)(const GLfixed *m);
    void (APIENTRY *glMultTransposeMatrixx)(const GLfixed *m);
    void (APIENTRY *glMultiTexCoord1x)(GLenum texture, GLfixed s);
    void (APIENTRY *glMultiTexCoord1xv)(GLenum texture, const GLfixed *coords);
    void (APIENTRY *glMultiTexCoord2x)(GLenum texture, GLfixed s, GLfixed t);
    void (APIENTRY *glMultiTexCoord2xv)(GLenum texture, const GLfixed *coords);
    void (APIENTRY *glMultiTexCoord3x)(GLenum texture, GLfixed s, GLfixed t,
                                       GLfixed r);
    void (APIENTRY *glMultiTexCoord3xv)(GLenum texture, const GLfixed *coords);
    void (APIENTRY *glMultiTexCoord4x)(GLenum texture, GLfixed s, GLfixed t,
                                       GLfixed r, GLfixed q);
    void (APIENTRY *glMultiTexCoord4xv)(GLenum texture, const GLfixed *coords);
    void (APIENTRY *glNormal3x)(GLfixed nx, GLfixed ny, GLfixed nz);
    void (APIENTRY *glNormal3xv)(const GLfixed *coords);
    void (APIENTRY *glOrthox)(GLfixed l, GLfixed r, GLfixed b, GLfixed t,
                              GLfixed n, GLfixed f);
    void (APIENTRY *glPassThroughx)(GLfixed token);
    void (APIENTRY *glPixelMapx)(GLenum map, GLint size, const GLfixed *values);
    void (APIENTRY *glPixelStorex)(GLenum pname, GLfixed param);
    void (APIENTRY *glPixelTransferx)(GLenum pname, GLfixed param);
    void (APIENTRY *glPixelZoomx)(GLfixed xfactor, GLfixed yfactor);
    void (APIENTRY *glPointParameterxv)(GLenum pname, const GLfixed *params);
    void (APIENTRY *glPointSizex)(GLfixed size);
    void (APIENTRY *glPolygonOffsetx)(GLfixed factor, GLfixed units);
    void (APIENTRY *glPrioritizeTexturesx)(GLsizei n, const GLuint *textures,
                                           const GLfixed *priorities);
    void (APIENTRY *glRasterPos2x)(GLfixed x, GLfixed y);
    void (APIENTRY *glRasterPos2xv)(const GLfixed *coords);
    void (APIENTRY *glRasterPos3x)(GLfixed x, GLfixed y, GLfixed z);
    void (APIENTRY *glRasterPos3xv)(const GLfixed *coords);
    void (APIENTRY *glRasterPos4x)(GLfixed x, GLfixed y, GLfixed z, GLfixed w);
    void (APIENTRY *glRasterPos4xv)(const GLfixed *coords);
    void (APIENTRY *glRectx)(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2);
    void (APIENTRY *glRectxv)(const GLfixed *v1, const GLfixed *v2);
    void (APIENTRY *glRotatex)(GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
    void (APIENTRY *glScalex)(GLfixed x, GLfixed y, GLfixed z);
    void (APIENTRY *glTexCoord1x)(GLfixed s);
    void (APIENTRY *glTexCoord1xv)(const GLfixed *coords);
    void (APIENTRY *glTexCoord2x)(GLfixed s, GLfixed t);
    void (APIENTRY *glTexCoord2xv)(const GLfixed *coords);
    void (APIENTRY *glTexCoord3x)(GLfixed s, GLfixed t, GLfixed r);
    void (APIENTRY *glTexCoord3xv)(const GLfixed *coords);
    void (APIENTRY *glTexCoord4x)(GLfixed s, GLfixed t, GLfixed r, GLfixed q);
    void (APIENTRY *glTexCoord4xv)(const GLfixed *coords);
    void (APIENTRY *glTexEnvx)(GLenum target, GLenum pname, GLfixed param);
    void (APIENTRY *glTexEnvxv)(GLenum target, GLenum pname,
                                const GLfixed *params);
    void (APIENTRY *glTexGenx)(GLenum coord, GLenum pname, GLfixed param);
    void (APIENTRY *glTexGenxv)(GLenum coord, GLenum pname,
                                const GLfixed *params);
    void (APIENTRY *glTexParameterx)(GLenum target, GLenum pname, GLfixed param);
    void (APIENTRY *glTexParameterxv)(GLenum target, GLenum pname,
                                      const GLfixed *params);
    void (APIENTRY *glTranslatex)(GLfixed x, GLfixed y, GLfixed z);
    void (APIENTRY *glVertex2x)(GLfixed x);
    void (APIENTRY *glVertex2xv)(const GLfixed *coords);
    void (APIENTRY *glVertex3x)(GLfixed x, GLfixed y);
    void (APIENTRY *glVertex3xv)(const GLfixed *coords);
    void (APIENTRY *glVertex4x)(GLfixed x, GLfixed y, GLfixed z);
    void (APIENTRY *glVertex4xv)(const GLfixed *coords);

    // Construction
    OESFixedPoint();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OESFixedPoint

// GL_OES_query_matrix extension API specification.
struct OESQueryMatrix {
    // Public Members
    GLbitfield(APIENTRY *glQueryMatrixx)(GLfixed *mantissa, GLint *exponent);

    // Construction
    OESQueryMatrix();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OESQueryMatrix

// GL_OES_single_precision extension API specification.
struct OESSinglePrecision {
    // Public Members
    void (APIENTRY *glClearDepthf)(GLclampf depth);
    void (APIENTRY *glClipPlanef)(GLenum plane, const GLfloat *equation);
    void (APIENTRY *glDepthRangef)(GLclampf n, GLclampf f);
    void (APIENTRY *glFrustumf)(GLfloat l, GLfloat r, GLfloat b, GLfloat t,
                                GLfloat n, GLfloat f);
    void (APIENTRY *glGetClipPlanef)(GLenum plane, GLfloat *equation);
    void (APIENTRY *glOrthof)(GLfloat l, GLfloat r, GLfloat b, GLfloat t,
                              GLfloat n, GLfloat f);

    // Construction
    OESSinglePrecision();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OESSinglePrecision

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
