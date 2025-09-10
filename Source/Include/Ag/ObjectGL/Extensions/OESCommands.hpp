//! @file Ag/ObjectGL/Extensions/OESCommands.hpp
//! @brief The declaration of OES-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_OES_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OES_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "OES.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_OES_byte_coordinates extension API.
class OESByteCoordinatesAPI : public BaseExtension
{
public:
    // Construction
    OESByteCoordinatesAPI();

    // Accessors
    const OESByteCoordinates &getRawAPI() const;

    // Operations
    void multiTexCoord1B(TextureUnit texture, GLbyte s) const;
    void multiTexCoord1BV(TextureUnit texture, const GLbyte *coords) const;
    void multiTexCoord2B(TextureUnit texture, GLbyte s, GLbyte t) const;
    void multiTexCoord2BV(TextureUnit texture, const GLbyte *coords) const;
    void multiTexCoord3B(TextureUnit texture, GLbyte s, GLbyte t, GLbyte r) const;
    void multiTexCoord3BV(TextureUnit texture, const GLbyte *coords) const;
    void multiTexCoord4B(TextureUnit texture, GLbyte s, GLbyte t, GLbyte r,
                         GLbyte q) const;
    void multiTexCoord4BV(TextureUnit texture, const GLbyte *coords) const;
    void texCoord1B(GLbyte s) const;
    void texCoord1BV(const GLbyte *coords) const;
    void texCoord2B(GLbyte s, GLbyte t) const;
    void texCoord2BV(const GLbyte *coords) const;
    void texCoord3B(GLbyte s, GLbyte t, GLbyte r) const;
    void texCoord3BV(const GLbyte *coords) const;
    void texCoord4B(GLbyte s, GLbyte t, GLbyte r, GLbyte q) const;
    void texCoord4BV(const GLbyte *coords) const;
    void vertex2B(GLbyte x, GLbyte y) const;
    void vertex2BV(const GLbyte *coords) const;
    void vertex3B(GLbyte x, GLbyte y, GLbyte z) const;
    void vertex3BV(const GLbyte *coords) const;
    void vertex4B(GLbyte x, GLbyte y, GLbyte z, GLbyte w) const;
    void vertex4BV(const GLbyte *coords) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OESByteCoordinates _api;
};

// Manages the entry points for the GL_OES_fixed_point extension API.
class OESFixedPointAPI : public BaseExtension
{
public:
    // Construction
    OESFixedPointAPI();

    // Accessors
    const OESFixedPoint &getRawAPI() const;

    // Operations
    void accumx(GLenum op, GLfixed value) const;
    void alphaFuncx(AlphaFunction func, GLfixed ref) const;
    void bitmapx(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig,
                 GLfixed xmove, GLfixed ymove, const GLubyte *bitmap) const;
    void blendColorx(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) const;
    void clearAccumx(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) const;
    void clearColorx(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) const;
    void clearDepthx(GLfixed depth) const;
    void clipPlanex(ClipPlaneName plane, const GLfixed *equation) const;
    void color3X(GLfixed red, GLfixed green, GLfixed blue) const;
    void color3XV(const GLfixed *components) const;
    void color4X(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha) const;
    void color4XV(const GLfixed *components) const;
    void convolutionParameterx(ConvolutionTargetEXT target,
                               ConvolutionParameterEXT pname, GLfixed param) const;
    void convolutionParameterxV(ConvolutionTargetEXT target,
                                ConvolutionParameterEXT pname,
                                const GLfixed *params) const;
    void depthRangex(GLfixed n, GLfixed f) const;
    void evalCoord1X(GLfixed u) const;
    void evalCoord1XV(const GLfixed *coords) const;
    void evalCoord2X(GLfixed u, GLfixed v) const;
    void evalCoord2XV(const GLfixed *coords) const;
    void feedbackBufferx(GLsizei n, GLenum type, const GLfixed *buffer) const;
    void fogx(GLenum pname, GLfixed param) const;
    void fogxV(GLenum pname, const GLfixed *param) const;
    void frustumx(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n,
                  GLfixed f) const;
    void getClipPlanex(ClipPlaneName plane, GLfixed *equation) const;
    void getConvolutionParameterxV(GLenum target, GLenum pname, GLfixed *params) const;
    void getFixedv(GetPName pname, GLfixed *params) const;
    void getHistogramParameterxV(HistogramTargetEXT target,
                                 GetHistogramParameterPNameEXT pname,
                                 GLfixed *params) const;
    void getLightx(LightName light, GLenum pname, GLfixed *params) const;
    void getMapxV(MapTarget target, GLenum query, GLfixed *v) const;
    void getMaterialx(MaterialFace face, GLenum pname, GLfixed param) const;
    void getPixelMapxV(GLenum map, GLint size, GLfixed *values) const;
    void getTexEnvxV(GLenum target, GLenum pname, GLfixed *params) const;
    void getTexGenxV(GLenum coord, TextureGenParameter pname, GLfixed *params) const;
    void getTexLevelParameterxV(TextureTarget target, GLint level,
                                GetTextureParameter pname, GLfixed *params) const;
    void getTexParameterxV(TextureTarget target, GetTextureParameter pname,
                           GLfixed *params) const;
    void indexx(GLfixed component) const;
    void indexxV(const GLfixed *component) const;
    void lightModelx(LightModelParameter pname, GLfixed param) const;
    void lightModelxV(LightModelParameter pname, const GLfixed *param) const;
    void lightx(LightName light, GLenum pname, GLfixed param) const;
    void lightxV(LightName light, GLenum pname, const GLfixed *params) const;
    void lineWidthx(GLfixed width) const;
    void loadMatrixx(const GLfixed *m) const;
    void loadTransposeMatrixx(const GLfixed *m) const;
    void map1X(MapTarget target, GLfixed u1, GLfixed u2, GLint stride,
               GLint order, GLfixed points) const;
    void map2X(MapTarget target, GLfixed u1, GLfixed u2, GLint ustride,
               GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder,
               GLfixed points) const;
    void mapGRID1X(GLint n, GLfixed u1, GLfixed u2) const;
    void mapGRID2X(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2) const;
    void materialx(MaterialFace face, GLenum pname, GLfixed param) const;
    void materialxV(MaterialFace face, GLenum pname, const GLfixed *param) const;
    void multMatrixx(const GLfixed *m) const;
    void multTransposeMatrixx(const GLfixed *m) const;
    void multiTexCoord1X(TextureUnit texture, GLfixed s) const;
    void multiTexCoord1XV(TextureUnit texture, const GLfixed *coords) const;
    void multiTexCoord2X(TextureUnit texture, GLfixed s, GLfixed t) const;
    void multiTexCoord2XV(TextureUnit texture, const GLfixed *coords) const;
    void multiTexCoord3X(TextureUnit texture, GLfixed s, GLfixed t, GLfixed r) const;
    void multiTexCoord3XV(TextureUnit texture, const GLfixed *coords) const;
    void multiTexCoord4X(TextureUnit texture, GLfixed s, GLfixed t, GLfixed r,
                         GLfixed q) const;
    void multiTexCoord4XV(TextureUnit texture, const GLfixed *coords) const;
    void normal3X(GLfixed nx, GLfixed ny, GLfixed nz) const;
    void normal3XV(const GLfixed *coords) const;
    void orthox(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f) const;
    void passThroughx(GLfixed token) const;
    void pixelMapx(GLenum map, GLint size, const GLfixed *values) const;
    void pixelStorex(PixelStoreParameter pname, GLfixed param) const;
    void pixelTransferx(PixelTransferParameter pname, GLfixed param) const;
    void pixelZoomx(GLfixed xfactor, GLfixed yfactor) const;
    void pointParameterxV(PointParameterNameARB pname, const GLfixed *params) const;
    void pointSizex(GLfixed size) const;
    void polygonOffsetx(GLfixed factor, GLfixed units) const;
    void prioritizeTexturesx(GLsizei n, const TextureName *textures,
                             const GLfixed *priorities) const;
    void rasterPOS2X(GLfixed x, GLfixed y) const;
    void rasterPOS2XV(const GLfixed *coords) const;
    void rasterPOS3X(GLfixed x, GLfixed y, GLfixed z) const;
    void rasterPOS3XV(const GLfixed *coords) const;
    void rasterPOS4X(GLfixed x, GLfixed y, GLfixed z, GLfixed w) const;
    void rasterPOS4XV(const GLfixed *coords) const;
    void rectx(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2) const;
    void rectxV(const GLfixed *v1, const GLfixed *v2) const;
    void rotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z) const;
    void scalex(GLfixed x, GLfixed y, GLfixed z) const;
    void texCoord1X(GLfixed s) const;
    void texCoord1XV(const GLfixed *coords) const;
    void texCoord2X(GLfixed s, GLfixed t) const;
    void texCoord2XV(const GLfixed *coords) const;
    void texCoord3X(GLfixed s, GLfixed t, GLfixed r) const;
    void texCoord3XV(const GLfixed *coords) const;
    void texCoord4X(GLfixed s, GLfixed t, GLfixed r, GLfixed q) const;
    void texCoord4XV(const GLfixed *coords) const;
    void texEnvx(GLenum target, GLenum pname, GLfixed param) const;
    void texEnvxV(GLenum target, GLenum pname, const GLfixed *params) const;
    void texGenx(GLenum coord, TextureGenParameter pname, GLfixed param) const;
    void texGenxV(GLenum coord, TextureGenParameter pname, const GLfixed *params) const;
    void texParameterx(TextureTarget target, GetTextureParameter pname,
                       GLfixed param) const;
    void texParameterxV(TextureTarget target, GetTextureParameter pname,
                        const GLfixed *params) const;
    void translatex(GLfixed x, GLfixed y, GLfixed z) const;
    void vertex2X(GLfixed x) const;
    void vertex2XV(const GLfixed *coords) const;
    void vertex3X(GLfixed x, GLfixed y) const;
    void vertex3XV(const GLfixed *coords) const;
    void vertex4X(GLfixed x, GLfixed y, GLfixed z) const;
    void vertex4XV(const GLfixed *coords) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OESFixedPoint _api;
};

// Manages the entry points for the GL_OES_query_matrix extension API.
class OESQueryMatrixAPI : public BaseExtension
{
public:
    // Construction
    OESQueryMatrixAPI();

    // Accessors
    const OESQueryMatrix &getRawAPI() const;

    // Operations
    GLbitfield queryMatrixx(GLfixed *mantissa, GLint *exponent) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OESQueryMatrix _api;
};

// Manages the entry points for the GL_OES_single_precision extension API.
class OESSinglePrecisionAPI : public BaseExtension
{
public:
    // Construction
    OESSinglePrecisionAPI();

    // Accessors
    const OESSinglePrecision &getRawAPI() const;

    // Operations
    void clearDepthF(GLclampf depth) const;
    void clipPlaneF(ClipPlaneName plane, const GLfloat *equation) const;
    void depthRangeF(GLclampf n, GLclampf f) const;
    void frustumF(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n,
                  GLfloat f) const;
    void getClipPlaneF(ClipPlaneName plane, GLfloat *equation) const;
    void orthoF(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OESSinglePrecision _api;
};



} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
