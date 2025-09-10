//! @file ObjectGL/Extensions/SGICommands.cpp
//! @brief The definition of SGI-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/SGICommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// SGISDetailTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_detail_texture extension.
SGISDetailTextureAPI::SGISDetailTextureAPI() :
    BaseExtension("GL_SGIS_detail_texture")
{
}

// Grant read-only access to the underlying function pointers.
const SGISDetailTexture &SGISDetailTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_detail_texture entry points.
void SGISDetailTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDetailTexFuncSGIS().
void SGISDetailTextureAPI::detailTexFunc(TextureTarget target, GLsizei n,
                                         const GLfloat *points) const
{
    static const char *fnName = "glDetailTexFuncSGIS";

    beforeCommand(fnName, _api.glDetailTexFunc);
    _api.glDetailTexFunc(toScalar(target), n, points);
    afterCommand(fnName);
}

// Calls glGetDetailTexFuncSGIS().
void SGISDetailTextureAPI::getDetailTexFunc(TextureTarget target,
                                            GLfloat *points) const
{
    static const char *fnName = "glGetDetailTexFuncSGIS";

    beforeCommand(fnName, _api.glGetDetailTexFunc);
    _api.glGetDetailTexFunc(toScalar(target), points);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISFogFunctionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_fog_function extension.
SGISFogFunctionAPI::SGISFogFunctionAPI() :
    BaseExtension("GL_SGIS_fog_function")
{
}

// Grant read-only access to the underlying function pointers.
const SGISFogFunction &SGISFogFunctionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_fog_function entry points.
void SGISFogFunctionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFogFuncSGIS().
void SGISFogFunctionAPI::fogFunc(GLsizei n, const GLfloat *points) const
{
    static const char *fnName = "glFogFuncSGIS";

    beforeCommand(fnName, _api.glFogFunc);
    _api.glFogFunc(n, points);
    afterCommand(fnName);
}

// Calls glGetFogFuncSGIS().
void SGISFogFunctionAPI::getFogFunc(GLfloat *points) const
{
    static const char *fnName = "glGetFogFuncSGIS";

    beforeCommand(fnName, _api.glGetFogFunc);
    _api.glGetFogFunc(points);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_multisample extension.
SGISMultisampleAPI::SGISMultisampleAPI() :
    BaseExtension("GL_SGIS_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const SGISMultisample &SGISMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_multisample entry points.
void SGISMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSampleMaskSGIS().
void SGISMultisampleAPI::sampleMask(GLclampf value, Boolean invert) const
{
    static const char *fnName = "glSampleMaskSGIS";

    beforeCommand(fnName, _api.glSampleMask);
    _api.glSampleMask(value, toScalar(invert));
    afterCommand(fnName);
}

// Calls glSamplePatternSGIS().
void SGISMultisampleAPI::samplePattern(SamplePatternSGIS pattern) const
{
    static const char *fnName = "glSamplePatternSGIS";

    beforeCommand(fnName, _api.glSamplePattern);
    _api.glSamplePattern(toScalar(pattern));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISPixelTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_pixel_texture extension.
SGISPixelTextureAPI::SGISPixelTextureAPI() :
    BaseExtension("GL_SGIS_pixel_texture")
{
}

// Grant read-only access to the underlying function pointers.
const SGISPixelTexture &SGISPixelTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_pixel_texture entry points.
void SGISPixelTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetPixelTexGenParameterfvSGIS().
void SGISPixelTextureAPI::getPixelTexGenParameterFV(PixelTexGenParameterNameSGIS pname,
                                                    GLfloat *params) const
{
    static const char *fnName = "glGetPixelTexGenParameterfvSGIS";

    beforeCommand(fnName, _api.glGetPixelTexGenParameterfv);
    _api.glGetPixelTexGenParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetPixelTexGenParameterivSGIS().
void SGISPixelTextureAPI::getPixelTexGenParameterIV(PixelTexGenParameterNameSGIS pname,
                                                    GLint *params) const
{
    static const char *fnName = "glGetPixelTexGenParameterivSGIS";

    beforeCommand(fnName, _api.glGetPixelTexGenParameteriv);
    _api.glGetPixelTexGenParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glPixelTexGenParameterfSGIS().
void SGISPixelTextureAPI::pixelTexGenParameterF(PixelTexGenParameterNameSGIS pname,
                                                GLfloat param) const
{
    static const char *fnName = "glPixelTexGenParameterfSGIS";

    beforeCommand(fnName, _api.glPixelTexGenParameterf);
    _api.glPixelTexGenParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelTexGenParameterfvSGIS().
void SGISPixelTextureAPI::pixelTexGenParameterFV(PixelTexGenParameterNameSGIS pname,
                                                 const GLfloat *params) const
{
    static const char *fnName = "glPixelTexGenParameterfvSGIS";

    beforeCommand(fnName, _api.glPixelTexGenParameterfv);
    _api.glPixelTexGenParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glPixelTexGenParameteriSGIS().
void SGISPixelTextureAPI::pixelTexGenParameterI(PixelTexGenParameterNameSGIS pname,
                                                GLint param) const
{
    static const char *fnName = "glPixelTexGenParameteriSGIS";

    beforeCommand(fnName, _api.glPixelTexGenParameteri);
    _api.glPixelTexGenParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelTexGenParameterivSGIS().
void SGISPixelTextureAPI::pixelTexGenParameterIV(PixelTexGenParameterNameSGIS pname,
                                                 const GLint *params) const
{
    static const char *fnName = "glPixelTexGenParameterivSGIS";

    beforeCommand(fnName, _api.glPixelTexGenParameteriv);
    _api.glPixelTexGenParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISPointParametersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_point_parameters extension.
SGISPointParametersAPI::SGISPointParametersAPI() :
    BaseExtension("GL_SGIS_point_parameters")
{
}

// Grant read-only access to the underlying function pointers.
const SGISPointParameters &SGISPointParametersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_point_parameters entry points.
void SGISPointParametersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPointParameterfSGIS().
void SGISPointParametersAPI::pointParameterF(PointParameterNameARB pname,
                                             GLfloat param) const
{
    static const char *fnName = "glPointParameterfSGIS";

    beforeCommand(fnName, _api.glPointParameterf);
    _api.glPointParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameterfvSGIS().
void SGISPointParametersAPI::pointParameterFV(PointParameterNameARB pname,
                                              const GLfloat *params) const
{
    static const char *fnName = "glPointParameterfvSGIS";

    beforeCommand(fnName, _api.glPointParameterfv);
    _api.glPointParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISSharpenTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_sharpen_texture extension.
SGISSharpenTextureAPI::SGISSharpenTextureAPI() :
    BaseExtension("GL_SGIS_sharpen_texture")
{
}

// Grant read-only access to the underlying function pointers.
const SGISSharpenTexture &SGISSharpenTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_sharpen_texture entry points.
void SGISSharpenTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetSharpenTexFuncSGIS().
void SGISSharpenTextureAPI::getSharpenTexFunc(TextureTarget target,
                                              GLfloat *points) const
{
    static const char *fnName = "glGetSharpenTexFuncSGIS";

    beforeCommand(fnName, _api.glGetSharpenTexFunc);
    _api.glGetSharpenTexFunc(toScalar(target), points);
    afterCommand(fnName);
}

// Calls glSharpenTexFuncSGIS().
void SGISSharpenTextureAPI::sharpenTexFunc(TextureTarget target, GLsizei n,
                                           const GLfloat *points) const
{
    static const char *fnName = "glSharpenTexFuncSGIS";

    beforeCommand(fnName, _api.glSharpenTexFunc);
    _api.glSharpenTexFunc(toScalar(target), n, points);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISTEXTURE4DAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_texture4D extension.
SGISTEXTURE4DAPI::SGISTEXTURE4DAPI() :
    BaseExtension("GL_SGIS_texture4D")
{
}

// Grant read-only access to the underlying function pointers.
const SGISTEXTURE4D &SGISTEXTURE4DAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_texture4D entry points.
void SGISTEXTURE4DAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexImage4DSGIS().
void SGISTEXTURE4DAPI::texImage4D(TextureTarget target, GLint level,
                                  InternalFormat internalformat, GLsizei width,
                                  GLsizei height, GLsizei depth, GLsizei size4d,
                                  GLint border, PixelFormat format,
                                  PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexImage4DSGIS";

    beforeCommand(fnName, _api.glTexImage4D);
    _api.glTexImage4D(toScalar(target), level, toScalar(internalformat), width,
                      height, depth, size4d, border, toScalar(format),
                      toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexSubImage4DSGIS().
void SGISTEXTURE4DAPI::texSubImage4D(TextureTarget target, GLint level,
                                     GLint xoffset, GLint yoffset, GLint zoffset,
                                     GLint woffset, GLsizei width,
                                     GLsizei height, GLsizei depth,
                                     GLsizei size4d, PixelFormat format,
                                     PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexSubImage4DSGIS";

    beforeCommand(fnName, _api.glTexSubImage4D);
    _api.glTexSubImage4D(toScalar(target), level, xoffset, yoffset, zoffset,
                         woffset, width, height, depth, size4d, toScalar(format),
                         toScalar(type), pixels);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISTextureColorMaskAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_texture_color_mask extension.
SGISTextureColorMaskAPI::SGISTextureColorMaskAPI() :
    BaseExtension("GL_SGIS_texture_color_mask")
{
}

// Grant read-only access to the underlying function pointers.
const SGISTextureColorMask &SGISTextureColorMaskAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_texture_color_mask entry points.
void SGISTextureColorMaskAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTextureColorMaskSGIS().
void SGISTextureColorMaskAPI::textureColorMask(Boolean red, Boolean green,
                                               Boolean blue, Boolean alpha) const
{
    static const char *fnName = "glTextureColorMaskSGIS";

    beforeCommand(fnName, _api.glTextureColorMask);
    _api.glTextureColorMask(toScalar(red), toScalar(green), toScalar(blue),
                            toScalar(alpha));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGISTextureFILTER4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIS_texture_filter4 extension.
SGISTextureFILTER4API::SGISTextureFILTER4API() :
    BaseExtension("GL_SGIS_texture_filter4")
{
}

// Grant read-only access to the underlying function pointers.
const SGISTextureFILTER4 &SGISTextureFILTER4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIS_texture_filter4 entry points.
void SGISTextureFILTER4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetTexFilterFuncSGIS().
void SGISTextureFILTER4API::getTexFilterFunc(TextureTarget target,
                                             TextureFilterSGIS filter,
                                             GLfloat *weights) const
{
    static const char *fnName = "glGetTexFilterFuncSGIS";

    beforeCommand(fnName, _api.glGetTexFilterFunc);
    _api.glGetTexFilterFunc(toScalar(target), toScalar(filter), weights);
    afterCommand(fnName);
}

// Calls glTexFilterFuncSGIS().
void SGISTextureFILTER4API::texFilterFunc(TextureTarget target,
                                          TextureFilterSGIS filter, GLsizei n,
                                          const GLfloat *weights) const
{
    static const char *fnName = "glTexFilterFuncSGIS";

    beforeCommand(fnName, _api.glTexFilterFunc);
    _api.glTexFilterFunc(toScalar(target), toScalar(filter), n, weights);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXAsyncAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_async extension.
SGIXAsyncAPI::SGIXAsyncAPI() :
    BaseExtension("GL_SGIX_async")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXAsync &SGIXAsyncAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_async entry points.
void SGIXAsyncAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAsyncMarkerSGIX().
void SGIXAsyncAPI::asyncMarker(GLuint marker) const
{
    static const char *fnName = "glAsyncMarkerSGIX";

    beforeCommand(fnName, _api.glAsyncMarker);
    _api.glAsyncMarker(marker);
    afterCommand(fnName);
}

// Calls glDeleteAsyncMarkersSGIX().
void SGIXAsyncAPI::deleteAsyncMarkers(GLuint marker, GLsizei range) const
{
    static const char *fnName = "glDeleteAsyncMarkersSGIX";

    beforeCommand(fnName, _api.glDeleteAsyncMarkers);
    _api.glDeleteAsyncMarkers(marker, range);
    afterCommand(fnName);
}

// Calls glFinishAsyncSGIX().
GLint SGIXAsyncAPI::finishAsync(GLuint *markerp) const
{
    static const char *fnName = "glFinishAsyncSGIX";

    beforeCommand(fnName, _api.glFinishAsync);
    GLint result = _api.glFinishAsync(markerp);
    afterCommand(fnName);

    return result;
}

// Calls glGenAsyncMarkersSGIX().
GLuint SGIXAsyncAPI::genAsyncMarkers(GLsizei range) const
{
    static const char *fnName = "glGenAsyncMarkersSGIX";

    beforeCommand(fnName, _api.glGenAsyncMarkers);
    GLuint result = _api.glGenAsyncMarkers(range);
    afterCommand(fnName);

    return result;
}

// Calls glIsAsyncMarkerSGIX().
Boolean SGIXAsyncAPI::isAsyncMarker(GLuint marker) const
{
    static const char *fnName = "glIsAsyncMarkerSGIX";

    beforeCommand(fnName, _api.glIsAsyncMarker);
    GLboolean result = _api.glIsAsyncMarker(marker);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glPollAsyncSGIX().
GLint SGIXAsyncAPI::pollAsync(GLuint *markerp) const
{
    static const char *fnName = "glPollAsyncSGIX";

    beforeCommand(fnName, _api.glPollAsync);
    GLint result = _api.glPollAsync(markerp);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFlushRasterAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_flush_raster extension.
SGIXFlushRasterAPI::SGIXFlushRasterAPI() :
    BaseExtension("GL_SGIX_flush_raster")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXFlushRaster &SGIXFlushRasterAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_flush_raster entry points.
void SGIXFlushRasterAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFlushRasterSGIX().
void SGIXFlushRasterAPI::flushRaster() const
{
    static const char *fnName = "glFlushRasterSGIX";

    beforeCommand(fnName, _api.glFlushRaster);
    _api.glFlushRaster();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFragmentLightingAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_fragment_lighting extension.
SGIXFragmentLightingAPI::SGIXFragmentLightingAPI() :
    BaseExtension("GL_SGIX_fragment_lighting")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXFragmentLighting &SGIXFragmentLightingAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_fragment_lighting entry points.
void SGIXFragmentLightingAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFragmentColorMaterialSGIX().
void SGIXFragmentLightingAPI::fragmentColorMaterial(MaterialFace face,
                                                    GLenum mode) const
{
    static const char *fnName = "glFragmentColorMaterialSGIX";

    beforeCommand(fnName, _api.glFragmentColorMaterial);
    _api.glFragmentColorMaterial(toScalar(face), mode);
    afterCommand(fnName);
}

// Calls glFragmentLightModelfSGIX().
void SGIXFragmentLightingAPI::fragmentLightModelF(FragmentLightModelParameterSGIX pname,
                                                  GLfloat param) const
{
    static const char *fnName = "glFragmentLightModelfSGIX";

    beforeCommand(fnName, _api.glFragmentLightModelf);
    _api.glFragmentLightModelf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glFragmentLightModelfvSGIX().
void SGIXFragmentLightingAPI::fragmentLightModelFV(FragmentLightModelParameterSGIX pname,
                                                   const GLfloat *params) const
{
    static const char *fnName = "glFragmentLightModelfvSGIX";

    beforeCommand(fnName, _api.glFragmentLightModelfv);
    _api.glFragmentLightModelfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glFragmentLightModeliSGIX().
void SGIXFragmentLightingAPI::fragmentLightModelI(FragmentLightModelParameterSGIX pname,
                                                  GLint param) const
{
    static const char *fnName = "glFragmentLightModeliSGIX";

    beforeCommand(fnName, _api.glFragmentLightModeli);
    _api.glFragmentLightModeli(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glFragmentLightModelivSGIX().
void SGIXFragmentLightingAPI::fragmentLightModelIV(FragmentLightModelParameterSGIX pname,
                                                   const GLint *params) const
{
    static const char *fnName = "glFragmentLightModelivSGIX";

    beforeCommand(fnName, _api.glFragmentLightModeliv);
    _api.glFragmentLightModeliv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glFragmentLightfSGIX().
void SGIXFragmentLightingAPI::fragmentLightF(FragmentLightNameSGIX light,
                                             GLenum pname, GLfloat param) const
{
    static const char *fnName = "glFragmentLightfSGIX";

    beforeCommand(fnName, _api.glFragmentLightf);
    _api.glFragmentLightf(toScalar(light), pname, param);
    afterCommand(fnName);
}

// Calls glFragmentLightfvSGIX().
void SGIXFragmentLightingAPI::fragmentLightFV(FragmentLightNameSGIX light,
                                              GLenum pname,
                                              const GLfloat *params) const
{
    static const char *fnName = "glFragmentLightfvSGIX";

    beforeCommand(fnName, _api.glFragmentLightfv);
    _api.glFragmentLightfv(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glFragmentLightiSGIX().
void SGIXFragmentLightingAPI::fragmentLightI(FragmentLightNameSGIX light,
                                             GLenum pname, GLint param) const
{
    static const char *fnName = "glFragmentLightiSGIX";

    beforeCommand(fnName, _api.glFragmentLighti);
    _api.glFragmentLighti(toScalar(light), pname, param);
    afterCommand(fnName);
}

// Calls glFragmentLightivSGIX().
void SGIXFragmentLightingAPI::fragmentLightIV(FragmentLightNameSGIX light,
                                              GLenum pname, const GLint *params) const
{
    static const char *fnName = "glFragmentLightivSGIX";

    beforeCommand(fnName, _api.glFragmentLightiv);
    _api.glFragmentLightiv(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glFragmentMaterialfSGIX().
void SGIXFragmentLightingAPI::fragmentMaterialF(MaterialFace face, GLenum pname,
                                                GLfloat param) const
{
    static const char *fnName = "glFragmentMaterialfSGIX";

    beforeCommand(fnName, _api.glFragmentMaterialf);
    _api.glFragmentMaterialf(toScalar(face), pname, param);
    afterCommand(fnName);
}

// Calls glFragmentMaterialfvSGIX().
void SGIXFragmentLightingAPI::fragmentMaterialFV(MaterialFace face, GLenum pname,
                                                 const GLfloat *params) const
{
    static const char *fnName = "glFragmentMaterialfvSGIX";

    beforeCommand(fnName, _api.glFragmentMaterialfv);
    _api.glFragmentMaterialfv(toScalar(face), pname, params);
    afterCommand(fnName);
}

// Calls glFragmentMaterialiSGIX().
void SGIXFragmentLightingAPI::fragmentMaterialI(MaterialFace face, GLenum pname,
                                                GLint param) const
{
    static const char *fnName = "glFragmentMaterialiSGIX";

    beforeCommand(fnName, _api.glFragmentMateriali);
    _api.glFragmentMateriali(toScalar(face), pname, param);
    afterCommand(fnName);
}

// Calls glFragmentMaterialivSGIX().
void SGIXFragmentLightingAPI::fragmentMaterialIV(MaterialFace face, GLenum pname,
                                                 const GLint *params) const
{
    static const char *fnName = "glFragmentMaterialivSGIX";

    beforeCommand(fnName, _api.glFragmentMaterialiv);
    _api.glFragmentMaterialiv(toScalar(face), pname, params);
    afterCommand(fnName);
}

// Calls glGetFragmentLightfvSGIX().
void SGIXFragmentLightingAPI::getFragmentLightFV(FragmentLightNameSGIX light,
                                                 GLenum pname, GLfloat *params) const
{
    static const char *fnName = "glGetFragmentLightfvSGIX";

    beforeCommand(fnName, _api.glGetFragmentLightfv);
    _api.glGetFragmentLightfv(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glGetFragmentLightivSGIX().
void SGIXFragmentLightingAPI::getFragmentLightIV(FragmentLightNameSGIX light,
                                                 GLenum pname, GLint *params) const
{
    static const char *fnName = "glGetFragmentLightivSGIX";

    beforeCommand(fnName, _api.glGetFragmentLightiv);
    _api.glGetFragmentLightiv(toScalar(light), pname, params);
    afterCommand(fnName);
}

// Calls glGetFragmentMaterialfvSGIX().
void SGIXFragmentLightingAPI::getFragmentMaterialFV(MaterialFace face,
                                                    GLenum pname,
                                                    GLfloat *params) const
{
    static const char *fnName = "glGetFragmentMaterialfvSGIX";

    beforeCommand(fnName, _api.glGetFragmentMaterialfv);
    _api.glGetFragmentMaterialfv(toScalar(face), pname, params);
    afterCommand(fnName);
}

// Calls glGetFragmentMaterialivSGIX().
void SGIXFragmentLightingAPI::getFragmentMaterialIV(MaterialFace face,
                                                    GLenum pname, GLint *params) const
{
    static const char *fnName = "glGetFragmentMaterialivSGIX";

    beforeCommand(fnName, _api.glGetFragmentMaterialiv);
    _api.glGetFragmentMaterialiv(toScalar(face), pname, params);
    afterCommand(fnName);
}

// Calls glLightEnviSGIX().
void SGIXFragmentLightingAPI::lightEnvI(LightEnvParameterSGIX pname, GLint param) const
{
    static const char *fnName = "glLightEnviSGIX";

    beforeCommand(fnName, _api.glLightEnvi);
    _api.glLightEnvi(toScalar(pname), param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFramezoomAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_framezoom extension.
SGIXFramezoomAPI::SGIXFramezoomAPI() :
    BaseExtension("GL_SGIX_framezoom")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXFramezoom &SGIXFramezoomAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_framezoom entry points.
void SGIXFramezoomAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFrameZoomSGIX().
void SGIXFramezoomAPI::frameZoom(GLint factor) const
{
    static const char *fnName = "glFrameZoomSGIX";

    beforeCommand(fnName, _api.glFrameZoom);
    _api.glFrameZoom(factor);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXIglooInterfaceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_igloo_interface extension.
SGIXIglooInterfaceAPI::SGIXIglooInterfaceAPI() :
    BaseExtension("GL_SGIX_igloo_interface")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXIglooInterface &SGIXIglooInterfaceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_igloo_interface entry points.
void SGIXIglooInterfaceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glIglooInterfaceSGIX().
void SGIXIglooInterfaceAPI::iglooInterface(GLenum pname, const void *params) const
{
    static const char *fnName = "glIglooInterfaceSGIX";

    beforeCommand(fnName, _api.glIglooInterface);
    _api.glIglooInterface(pname, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXInstrumentSAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_instruments extension.
SGIXInstrumentSAPI::SGIXInstrumentSAPI() :
    BaseExtension("GL_SGIX_instruments")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXInstrumentS &SGIXInstrumentSAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_instruments entry points.
void SGIXInstrumentSAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetInstrumentsSGIX().
GLint SGIXInstrumentSAPI::getInstrumentS() const
{
    static const char *fnName = "glGetInstrumentsSGIX";

    beforeCommand(fnName, _api.glGetInstruments);
    GLint result = _api.glGetInstruments();
    afterCommand(fnName);

    return result;
}

// Calls glInstrumentsBufferSGIX().
void SGIXInstrumentSAPI::instrumentSBuffer(GLsizei size, GLint *buffer) const
{
    static const char *fnName = "glInstrumentsBufferSGIX";

    beforeCommand(fnName, _api.glInstrumentsBuffer);
    _api.glInstrumentsBuffer(size, buffer);
    afterCommand(fnName);
}

// Calls glPollInstrumentsSGIX().
GLint SGIXInstrumentSAPI::pollInstrumentS(GLint *marker_p) const
{
    static const char *fnName = "glPollInstrumentsSGIX";

    beforeCommand(fnName, _api.glPollInstruments);
    GLint result = _api.glPollInstruments(marker_p);
    afterCommand(fnName);

    return result;
}

// Calls glReadInstrumentsSGIX().
void SGIXInstrumentSAPI::readInstrumentS(GLint marker) const
{
    static const char *fnName = "glReadInstrumentsSGIX";

    beforeCommand(fnName, _api.glReadInstruments);
    _api.glReadInstruments(marker);
    afterCommand(fnName);
}

// Calls glStartInstrumentsSGIX().
void SGIXInstrumentSAPI::startInstrumentS() const
{
    static const char *fnName = "glStartInstrumentsSGIX";

    beforeCommand(fnName, _api.glStartInstruments);
    _api.glStartInstruments();
    afterCommand(fnName);
}

// Calls glStopInstrumentsSGIX().
void SGIXInstrumentSAPI::stopInstrumentS(GLint marker) const
{
    static const char *fnName = "glStopInstrumentsSGIX";

    beforeCommand(fnName, _api.glStopInstruments);
    _api.glStopInstruments(marker);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXListPriorityAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_list_priority extension.
SGIXListPriorityAPI::SGIXListPriorityAPI() :
    BaseExtension("GL_SGIX_list_priority")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXListPriority &SGIXListPriorityAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_list_priority entry points.
void SGIXListPriorityAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetListParameterfvSGIX().
void SGIXListPriorityAPI::getListParameterFV(GLuint list,
                                             ListParameterName pname,
                                             GLfloat *params) const
{
    static const char *fnName = "glGetListParameterfvSGIX";

    beforeCommand(fnName, _api.glGetListParameterfv);
    _api.glGetListParameterfv(list, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetListParameterivSGIX().
void SGIXListPriorityAPI::getListParameterIV(GLuint list,
                                             ListParameterName pname,
                                             GLint *params) const
{
    static const char *fnName = "glGetListParameterivSGIX";

    beforeCommand(fnName, _api.glGetListParameteriv);
    _api.glGetListParameteriv(list, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glListParameterfSGIX().
void SGIXListPriorityAPI::listParameterF(GLuint list, ListParameterName pname,
                                         GLfloat param) const
{
    static const char *fnName = "glListParameterfSGIX";

    beforeCommand(fnName, _api.glListParameterf);
    _api.glListParameterf(list, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glListParameterfvSGIX().
void SGIXListPriorityAPI::listParameterFV(GLuint list, ListParameterName pname,
                                          const GLfloat *params) const
{
    static const char *fnName = "glListParameterfvSGIX";

    beforeCommand(fnName, _api.glListParameterfv);
    _api.glListParameterfv(list, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glListParameteriSGIX().
void SGIXListPriorityAPI::listParameterI(GLuint list, ListParameterName pname,
                                         GLint param) const
{
    static const char *fnName = "glListParameteriSGIX";

    beforeCommand(fnName, _api.glListParameteri);
    _api.glListParameteri(list, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glListParameterivSGIX().
void SGIXListPriorityAPI::listParameterIV(GLuint list, ListParameterName pname,
                                          const GLint *params) const
{
    static const char *fnName = "glListParameterivSGIX";

    beforeCommand(fnName, _api.glListParameteriv);
    _api.glListParameteriv(list, toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPixelTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_pixel_texture extension.
SGIXPixelTextureAPI::SGIXPixelTextureAPI() :
    BaseExtension("GL_SGIX_pixel_texture")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXPixelTexture &SGIXPixelTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_pixel_texture entry points.
void SGIXPixelTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPixelTexGenSGIX().
void SGIXPixelTextureAPI::pixelTexGen(GLenum mode) const
{
    static const char *fnName = "glPixelTexGenSGIX";

    beforeCommand(fnName, _api.glPixelTexGen);
    _api.glPixelTexGen(mode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPolynomialFfdAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_polynomial_ffd extension.
SGIXPolynomialFfdAPI::SGIXPolynomialFfdAPI() :
    BaseExtension("GL_SGIX_polynomial_ffd")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXPolynomialFfd &SGIXPolynomialFfdAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_polynomial_ffd entry points.
void SGIXPolynomialFfdAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeformSGIX().
void SGIXPolynomialFfdAPI::deform(GLbitfield  /* FfdMaskSGIX */ mask) const
{
    static const char *fnName = "glDeformSGIX";

    beforeCommand(fnName, _api.glDeform);
    _api.glDeform(mask);
    afterCommand(fnName);
}

// Calls glDeformationMap3dSGIX().
void SGIXPolynomialFfdAPI::deformationMap3D(FfdTargetSGIX target, GLdouble u1,
                                            GLdouble u2, GLint ustride,
                                            GLint uorder, GLdouble v1,
                                            GLdouble v2, GLint vstride,
                                            GLint vorder, GLdouble w1,
                                            GLdouble w2, GLint wstride,
                                            GLint worder, const GLdouble *points) const
{
    static const char *fnName = "glDeformationMap3dSGIX";

    beforeCommand(fnName, _api.glDeformationMap3d);
    _api.glDeformationMap3d(toScalar(target), u1, u2, ustride, uorder, v1, v2,
                            vstride, vorder, w1, w2, wstride, worder, points);
    afterCommand(fnName);
}

// Calls glDeformationMap3fSGIX().
void SGIXPolynomialFfdAPI::deformationMap3F(FfdTargetSGIX target, GLfloat u1,
                                            GLfloat u2, GLint ustride,
                                            GLint uorder, GLfloat v1, GLfloat v2,
                                            GLint vstride, GLint vorder,
                                            GLfloat w1, GLfloat w2,
                                            GLint wstride, GLint worder,
                                            const GLfloat *points) const
{
    static const char *fnName = "glDeformationMap3fSGIX";

    beforeCommand(fnName, _api.glDeformationMap3f);
    _api.glDeformationMap3f(toScalar(target), u1, u2, ustride, uorder, v1, v2,
                            vstride, vorder, w1, w2, wstride, worder, points);
    afterCommand(fnName);
}

// Calls glLoadIdentityDeformationMapSGIX().
void SGIXPolynomialFfdAPI::loadIdentityDeformationMap(GLbitfield  /* FfdMaskSGIX */ mask) const
{
    static const char *fnName = "glLoadIdentityDeformationMapSGIX";

    beforeCommand(fnName, _api.glLoadIdentityDeformationMap);
    _api.glLoadIdentityDeformationMap(mask);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXReferencePlaneAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_reference_plane extension.
SGIXReferencePlaneAPI::SGIXReferencePlaneAPI() :
    BaseExtension("GL_SGIX_reference_plane")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXReferencePlane &SGIXReferencePlaneAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_reference_plane entry points.
void SGIXReferencePlaneAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glReferencePlaneSGIX().
void SGIXReferencePlaneAPI::referencePlane(const GLdouble *equation) const
{
    static const char *fnName = "glReferencePlaneSGIX";

    beforeCommand(fnName, _api.glReferencePlane);
    _api.glReferencePlane(equation);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSpriteAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_sprite extension.
SGIXSpriteAPI::SGIXSpriteAPI() :
    BaseExtension("GL_SGIX_sprite")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXSprite &SGIXSpriteAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_sprite entry points.
void SGIXSpriteAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSpriteParameterfSGIX().
void SGIXSpriteAPI::spriteParameterF(SpriteParameterNameSGIX pname,
                                     GLfloat param) const
{
    static const char *fnName = "glSpriteParameterfSGIX";

    beforeCommand(fnName, _api.glSpriteParameterf);
    _api.glSpriteParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSpriteParameterfvSGIX().
void SGIXSpriteAPI::spriteParameterFV(SpriteParameterNameSGIX pname,
                                      const GLfloat *params) const
{
    static const char *fnName = "glSpriteParameterfvSGIX";

    beforeCommand(fnName, _api.glSpriteParameterfv);
    _api.glSpriteParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glSpriteParameteriSGIX().
void SGIXSpriteAPI::spriteParameterI(SpriteParameterNameSGIX pname, GLint param) const
{
    static const char *fnName = "glSpriteParameteriSGIX";

    beforeCommand(fnName, _api.glSpriteParameteri);
    _api.glSpriteParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glSpriteParameterivSGIX().
void SGIXSpriteAPI::spriteParameterIV(SpriteParameterNameSGIX pname,
                                      const GLint *params) const
{
    static const char *fnName = "glSpriteParameterivSGIX";

    beforeCommand(fnName, _api.glSpriteParameteriv);
    _api.glSpriteParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXTagSampleBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGIX_tag_sample_buffer extension.
SGIXTagSampleBufferAPI::SGIXTagSampleBufferAPI() :
    BaseExtension("GL_SGIX_tag_sample_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXTagSampleBuffer &SGIXTagSampleBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGIX_tag_sample_buffer entry points.
void SGIXTagSampleBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTagSampleBufferSGIX().
void SGIXTagSampleBufferAPI::tagSampleBuffer() const
{
    static const char *fnName = "glTagSampleBufferSGIX";

    beforeCommand(fnName, _api.glTagSampleBuffer);
    _api.glTagSampleBuffer();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIColorTableAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SGI_color_table extension.
SGIColorTableAPI::SGIColorTableAPI() :
    BaseExtension("GL_SGI_color_table")
{
}

// Grant read-only access to the underlying function pointers.
const SGIColorTable &SGIColorTableAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SGI_color_table entry points.
void SGIColorTableAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorTableParameterfvSGI().
void SGIColorTableAPI::colorTableParameterFV(ColorTableTargetSGI target,
                                             ColorTableParameterPNameSGI pname,
                                             const GLfloat *params) const
{
    static const char *fnName = "glColorTableParameterfvSGI";

    beforeCommand(fnName, _api.glColorTableParameterfv);
    _api.glColorTableParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glColorTableParameterivSGI().
void SGIColorTableAPI::colorTableParameterIV(ColorTableTargetSGI target,
                                             ColorTableParameterPNameSGI pname,
                                             const GLint *params) const
{
    static const char *fnName = "glColorTableParameterivSGI";

    beforeCommand(fnName, _api.glColorTableParameteriv);
    _api.glColorTableParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glColorTableSGI().
void SGIColorTableAPI::colorTable(ColorTableTargetSGI target,
                                  InternalFormat internalformat, GLsizei width,
                                  PixelFormat format, PixelType type,
                                  const void *table) const
{
    static const char *fnName = "glColorTableSGI";

    beforeCommand(fnName, _api.glColorTable);
    _api.glColorTable(toScalar(target), toScalar(internalformat), width,
                      toScalar(format), toScalar(type), table);
    afterCommand(fnName);
}

// Calls glCopyColorTableSGI().
void SGIColorTableAPI::copyColorTable(ColorTableTargetSGI target,
                                      InternalFormat internalformat, GLint x,
                                      GLint y, GLsizei width) const
{
    static const char *fnName = "glCopyColorTableSGI";

    beforeCommand(fnName, _api.glCopyColorTable);
    _api.glCopyColorTable(toScalar(target), toScalar(internalformat), x, y,
                          width);
    afterCommand(fnName);
}

// Calls glGetColorTableParameterfvSGI().
void SGIColorTableAPI::getColorTableParameterFV(ColorTableTargetSGI target,
                                                GetColorTableParameterPNameSGI pname,
                                                GLfloat *params) const
{
    static const char *fnName = "glGetColorTableParameterfvSGI";

    beforeCommand(fnName, _api.glGetColorTableParameterfv);
    _api.glGetColorTableParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetColorTableParameterivSGI().
void SGIColorTableAPI::getColorTableParameterIV(ColorTableTargetSGI target,
                                                GetColorTableParameterPNameSGI pname,
                                                GLint *params) const
{
    static const char *fnName = "glGetColorTableParameterivSGI";

    beforeCommand(fnName, _api.glGetColorTableParameteriv);
    _api.glGetColorTableParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetColorTableSGI().
void SGIColorTableAPI::getColorTable(ColorTableTargetSGI target,
                                     PixelFormat format, PixelType type,
                                     void *table) const
{
    static const char *fnName = "glGetColorTableSGI";

    beforeCommand(fnName, _api.glGetColorTable);
    _api.glGetColorTable(toScalar(target), toScalar(format), toScalar(type),
                         table);
    afterCommand(fnName);
}

} // namespace gl

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// SGIXDmbufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_dmbuffer extension.
SGIXDmbufferAPI::SGIXDmbufferAPI() :
    BaseExtension("GLX_SGIX_dmbuffer")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXDmbuffer &SGIXDmbufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_dmbuffer entry points.
void SGIXDmbufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXAssociateDMPbufferSGIX().
Bool SGIXDmbufferAPI::xAssociateDmPbuffer(Display *dpy, GLXPbufferSGIX pbuffer,
                                          DMparams *params, DMbuffer dmbuffer) const
{
    static const char *fnName = "glXAssociateDMPbufferSGIX";

    beforeCommand(fnName, _api.glXAssociateDMPbuffer);
    Bool result = _api.glXAssociateDMPbuffer(dpy, pbuffer, params, dmbuffer);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFbconfigAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_fbconfig extension.
SGIXFbconfigAPI::SGIXFbconfigAPI() :
    BaseExtension("GLX_SGIX_fbconfig")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXFbconfig &SGIXFbconfigAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_fbconfig entry points.
void SGIXFbconfigAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXChooseFBConfigSGIX().
GLXFBConfigSGIX *SGIXFbconfigAPI::xChooseFBConfig(Display *dpy, int screen,
                                                  int *attrib_list,
                                                  int *nelements) const
{
    static const char *fnName = "glXChooseFBConfigSGIX";

    beforeCommand(fnName, _api.glXChooseFBConfig);
    GLXFBConfigSGIX *result = _api.glXChooseFBConfig(dpy, screen, attrib_list,
                                                     nelements);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateContextWithConfigSGIX().
GLXContext SGIXFbconfigAPI::xCreateContextWithConfig(Display *dpy,
                                                     GLXFBConfigSGIX config,
                                                     int render_type,
                                                     GLXContext share_list,
                                                     Bool direct) const
{
    static const char *fnName = "glXCreateContextWithConfigSGIX";

    beforeCommand(fnName, _api.glXCreateContextWithConfig);
    GLXContext result = _api.glXCreateContextWithConfig(dpy, config, render_type,
                                                        share_list, direct);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateGLXPixmapWithConfigSGIX().
GLXPixmap SGIXFbconfigAPI::xCreateGlxPixmapWithConfig(Display *dpy,
                                                      GLXFBConfigSGIX config,
                                                      Pixmap pixmap) const
{
    static const char *fnName = "glXCreateGLXPixmapWithConfigSGIX";

    beforeCommand(fnName, _api.glXCreateGLXPixmapWithConfig);
    GLXPixmap result = _api.glXCreateGLXPixmapWithConfig(dpy, config, pixmap);
    afterCommand(fnName);

    return result;
}

// Calls glXGetFBConfigAttribSGIX().
int SGIXFbconfigAPI::xGetFBConfigAttrib(Display *dpy, GLXFBConfigSGIX config,
                                        int attribute, int *value) const
{
    static const char *fnName = "glXGetFBConfigAttribSGIX";

    beforeCommand(fnName, _api.glXGetFBConfigAttrib);
    int result = _api.glXGetFBConfigAttrib(dpy, config, attribute, value);
    afterCommand(fnName);

    return result;
}

// Calls glXGetFBConfigFromVisualSGIX().
GLXFBConfigSGIX SGIXFbconfigAPI::xGetFBConfigFromVisual(Display *dpy,
                                                        XVisualInfo *vis) const
{
    static const char *fnName = "glXGetFBConfigFromVisualSGIX";

    beforeCommand(fnName, _api.glXGetFBConfigFromVisual);
    GLXFBConfigSGIX result = _api.glXGetFBConfigFromVisual(dpy, vis);
    afterCommand(fnName);

    return result;
}

// Calls glXGetVisualFromFBConfigSGIX().
XVisualInfo *SGIXFbconfigAPI::xGetVisualFromFBConfig(Display *dpy,
                                                     GLXFBConfigSGIX config) const
{
    static const char *fnName = "glXGetVisualFromFBConfigSGIX";

    beforeCommand(fnName, _api.glXGetVisualFromFBConfig);
    XVisualInfo *result = _api.glXGetVisualFromFBConfig(dpy, config);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXHyperpipeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_hyperpipe extension.
SGIXHyperpipeAPI::SGIXHyperpipeAPI() :
    BaseExtension("GLX_SGIX_hyperpipe")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXHyperpipe &SGIXHyperpipeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_hyperpipe entry points.
void SGIXHyperpipeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindHyperpipeSGIX().
int SGIXHyperpipeAPI::xBindHyperpipe(Display *dpy, int hpId) const
{
    static const char *fnName = "glXBindHyperpipeSGIX";

    beforeCommand(fnName, _api.glXBindHyperpipe);
    int result = _api.glXBindHyperpipe(dpy, hpId);
    afterCommand(fnName);

    return result;
}

// Calls glXDestroyHyperpipeConfigSGIX().
int SGIXHyperpipeAPI::xDestroyHyperpipeConfig(Display *dpy, int hpId) const
{
    static const char *fnName = "glXDestroyHyperpipeConfigSGIX";

    beforeCommand(fnName, _api.glXDestroyHyperpipeConfig);
    int result = _api.glXDestroyHyperpipeConfig(dpy, hpId);
    afterCommand(fnName);

    return result;
}

// Calls glXHyperpipeAttribSGIX().
int SGIXHyperpipeAPI::xHyperpipeAttrib(Display *dpy, int timeSlice, int attrib,
                                       int size, void *attribList) const
{
    static const char *fnName = "glXHyperpipeAttribSGIX";

    beforeCommand(fnName, _api.glXHyperpipeAttrib);
    int result = _api.glXHyperpipeAttrib(dpy, timeSlice, attrib, size,
                                         attribList);
    afterCommand(fnName);

    return result;
}

// Calls glXHyperpipeConfigSGIX().
int SGIXHyperpipeAPI::xHyperpipeConfig(Display *dpy, int networkId, int npipes,
                                       GLXHyperpipeConfigSGIX *cfg, int *hpId) const
{
    static const char *fnName = "glXHyperpipeConfigSGIX";

    beforeCommand(fnName, _api.glXHyperpipeConfig);
    int result = _api.glXHyperpipeConfig(dpy, networkId, npipes, cfg, hpId);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryHyperpipeAttribSGIX().
int SGIXHyperpipeAPI::xQueryHyperpipeAttrib(Display *dpy, int timeSlice,
                                            int attrib, int size,
                                            void *returnAttribList) const
{
    static const char *fnName = "glXQueryHyperpipeAttribSGIX";

    beforeCommand(fnName, _api.glXQueryHyperpipeAttrib);
    int result = _api.glXQueryHyperpipeAttrib(dpy, timeSlice, attrib, size,
                                              returnAttribList);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryHyperpipeBestAttribSGIX().
int SGIXHyperpipeAPI::xQueryHyperpipeBestAttrib(Display *dpy, int timeSlice,
                                                int attrib, int size,
                                                void *attribList,
                                                void *returnAttribList) const
{
    static const char *fnName = "glXQueryHyperpipeBestAttribSGIX";

    beforeCommand(fnName, _api.glXQueryHyperpipeBestAttrib);
    int result = _api.glXQueryHyperpipeBestAttrib(dpy, timeSlice, attrib, size,
                                                  attribList, returnAttribList);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryHyperpipeConfigSGIX().
GLXHyperpipeConfigSGIX *SGIXHyperpipeAPI::xQueryHyperpipeConfig(Display *dpy,
                                                                int hpId,
                                                                int *npipes) const
{
    static const char *fnName = "glXQueryHyperpipeConfigSGIX";

    beforeCommand(fnName, _api.glXQueryHyperpipeConfig);
    GLXHyperpipeConfigSGIX *result = _api.glXQueryHyperpipeConfig(dpy, hpId,
                                                                  npipes);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryHyperpipeNetworkSGIX().
GLXHyperpipeNetworkSGIX *SGIXHyperpipeAPI::xQueryHyperpipeNetwork(Display *dpy,
                                                                  int *npipes) const
{
    static const char *fnName = "glXQueryHyperpipeNetworkSGIX";

    beforeCommand(fnName, _api.glXQueryHyperpipeNetwork);
    GLXHyperpipeNetworkSGIX *result = _api.glXQueryHyperpipeNetwork(dpy, npipes);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPbufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_pbuffer extension.
SGIXPbufferAPI::SGIXPbufferAPI() :
    BaseExtension("GLX_SGIX_pbuffer")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXPbuffer &SGIXPbufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_pbuffer entry points.
void SGIXPbufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCreateGLXPbufferSGIX().
GLXPbufferSGIX SGIXPbufferAPI::xCreateGlxPbuffer(Display *dpy,
                                                 GLXFBConfigSGIX config,
                                                 unsigned int width,
                                                 unsigned int height,
                                                 int *attrib_list) const
{
    static const char *fnName = "glXCreateGLXPbufferSGIX";

    beforeCommand(fnName, _api.glXCreateGLXPbuffer);
    GLXPbufferSGIX result = _api.glXCreateGLXPbuffer(dpy, config, width, height,
                                                     attrib_list);
    afterCommand(fnName);

    return result;
}

// Calls glXDestroyGLXPbufferSGIX().
void SGIXPbufferAPI::xDestroyGlxPbuffer(Display *dpy, GLXPbufferSGIX pbuf) const
{
    static const char *fnName = "glXDestroyGLXPbufferSGIX";

    beforeCommand(fnName, _api.glXDestroyGLXPbuffer);
    _api.glXDestroyGLXPbuffer(dpy, pbuf);
    afterCommand(fnName);
}

// Calls glXGetSelectedEventSGIX().
void SGIXPbufferAPI::xGetSelectedEvent(Display *dpy, GLXDrawable drawable,
                                       unsigned long *mask) const
{
    static const char *fnName = "glXGetSelectedEventSGIX";

    beforeCommand(fnName, _api.glXGetSelectedEvent);
    _api.glXGetSelectedEvent(dpy, drawable, mask);
    afterCommand(fnName);
}

// Calls glXQueryGLXPbufferSGIX().
void SGIXPbufferAPI::xQueryGlxPbuffer(Display *dpy, GLXPbufferSGIX pbuf,
                                      int attribute, unsigned int *value) const
{
    static const char *fnName = "glXQueryGLXPbufferSGIX";

    beforeCommand(fnName, _api.glXQueryGLXPbuffer);
    _api.glXQueryGLXPbuffer(dpy, pbuf, attribute, value);
    afterCommand(fnName);
}

// Calls glXSelectEventSGIX().
void SGIXPbufferAPI::xSelectEvent(Display *dpy, GLXDrawable drawable,
                                  unsigned long mask) const
{
    static const char *fnName = "glXSelectEventSGIX";

    beforeCommand(fnName, _api.glXSelectEvent);
    _api.glXSelectEvent(dpy, drawable, mask);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSwapBarrierAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_swap_barrier extension.
SGIXSwapBarrierAPI::SGIXSwapBarrierAPI() :
    BaseExtension("GLX_SGIX_swap_barrier")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXSwapBarrier &SGIXSwapBarrierAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_swap_barrier entry points.
void SGIXSwapBarrierAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindSwapBarrierSGIX().
void SGIXSwapBarrierAPI::xBindSwapBarrier(Display *dpy, GLXDrawable drawable,
                                          int barrier) const
{
    static const char *fnName = "glXBindSwapBarrierSGIX";

    beforeCommand(fnName, _api.glXBindSwapBarrier);
    _api.glXBindSwapBarrier(dpy, drawable, barrier);
    afterCommand(fnName);
}

// Calls glXQueryMaxSwapBarriersSGIX().
Bool SGIXSwapBarrierAPI::xQueryMaxSwapBarriers(Display *dpy, int screen,
                                               int *max) const
{
    static const char *fnName = "glXQueryMaxSwapBarriersSGIX";

    beforeCommand(fnName, _api.glXQueryMaxSwapBarriers);
    Bool result = _api.glXQueryMaxSwapBarriers(dpy, screen, max);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSwapGroupAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_swap_group extension.
SGIXSwapGroupAPI::SGIXSwapGroupAPI() :
    BaseExtension("GLX_SGIX_swap_group")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXSwapGroup &SGIXSwapGroupAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_swap_group entry points.
void SGIXSwapGroupAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXJoinSwapGroupSGIX().
void SGIXSwapGroupAPI::xJoinSwapGroup(Display *dpy, GLXDrawable drawable,
                                      GLXDrawable member) const
{
    static const char *fnName = "glXJoinSwapGroupSGIX";

    beforeCommand(fnName, _api.glXJoinSwapGroup);
    _api.glXJoinSwapGroup(dpy, drawable, member);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SGIXVideoResizeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_video_resize extension.
SGIXVideoResizeAPI::SGIXVideoResizeAPI() :
    BaseExtension("GLX_SGIX_video_resize")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXVideoResize &SGIXVideoResizeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_video_resize entry points.
void SGIXVideoResizeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindChannelToWindowSGIX().
int SGIXVideoResizeAPI::xBindChannelToWindow(Display *display, int screen,
                                             int channel, Window window) const
{
    static const char *fnName = "glXBindChannelToWindowSGIX";

    beforeCommand(fnName, _api.glXBindChannelToWindow);
    int result = _api.glXBindChannelToWindow(display, screen, channel, window);
    afterCommand(fnName);

    return result;
}

// Calls glXChannelRectSGIX().
int SGIXVideoResizeAPI::xChannelRect(Display *display, int screen, int channel,
                                     int x, int y, int w, int h) const
{
    static const char *fnName = "glXChannelRectSGIX";

    beforeCommand(fnName, _api.glXChannelRect);
    int result = _api.glXChannelRect(display, screen, channel, x, y, w, h);
    afterCommand(fnName);

    return result;
}

// Calls glXChannelRectSyncSGIX().
int SGIXVideoResizeAPI::xChannelRectSync(Display *display, int screen,
                                         int channel, GLenum synctype) const
{
    static const char *fnName = "glXChannelRectSyncSGIX";

    beforeCommand(fnName, _api.glXChannelRectSync);
    int result = _api.glXChannelRectSync(display, screen, channel, synctype);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryChannelDeltasSGIX().
int SGIXVideoResizeAPI::xQueryChannelDeltas(Display *display, int screen,
                                            int channel, int *x, int *y, int *w,
                                            int *h) const
{
    static const char *fnName = "glXQueryChannelDeltasSGIX";

    beforeCommand(fnName, _api.glXQueryChannelDeltas);
    int result = _api.glXQueryChannelDeltas(display, screen, channel, x, y, w, h);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryChannelRectSGIX().
int SGIXVideoResizeAPI::xQueryChannelRect(Display *display, int screen,
                                          int channel, int *dx, int *dy, int *dw,
                                          int *dh) const
{
    static const char *fnName = "glXQueryChannelRectSGIX";

    beforeCommand(fnName, _api.glXQueryChannelRect);
    int result = _api.glXQueryChannelRect(display, screen, channel, dx, dy, dw,
                                          dh);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SGIXVideoSourceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGIX_video_source extension.
SGIXVideoSourceAPI::SGIXVideoSourceAPI() :
    BaseExtension("GLX_SGIX_video_source")
{
}

// Grant read-only access to the underlying function pointers.
const SGIXVideoSource &SGIXVideoSourceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGIX_video_source entry points.
void SGIXVideoSourceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCreateGLXVideoSourceSGIX().
GLXVideoSourceSGIX SGIXVideoSourceAPI::xCreateGlxVideoSource(Display *display,
                                                             int screen,
                                                             VLServer server,
                                                             VLPath path,
                                                             int nodeClass,
                                                             VLNode drainNode) const
{
    static const char *fnName = "glXCreateGLXVideoSourceSGIX";

    beforeCommand(fnName, _api.glXCreateGLXVideoSource);
    GLXVideoSourceSGIX result = _api.glXCreateGLXVideoSource(display, screen,
                                                             server, path,
                                                             nodeClass,
                                                             drainNode);
    afterCommand(fnName);

    return result;
}

// Calls glXDestroyGLXVideoSourceSGIX().
void SGIXVideoSourceAPI::xDestroyGlxVideoSource(Display *dpy,
                                                GLXVideoSourceSGIX glxvideosource) const
{
    static const char *fnName = "glXDestroyGLXVideoSourceSGIX";

    beforeCommand(fnName, _api.glXDestroyGLXVideoSource);
    _api.glXDestroyGLXVideoSource(dpy, glxvideosource);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SgiCushionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGI_cushion extension.
SgiCushionAPI::SgiCushionAPI() :
    BaseExtension("GLX_SGI_cushion")
{
}

// Grant read-only access to the underlying function pointers.
const SgiCushion &SgiCushionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGI_cushion entry points.
void SgiCushionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCushionSGI().
void SgiCushionAPI::xCushionSgi(Display *dpy, Window window, float cushion) const
{
    static const char *fnName = "glXCushionSGI";

    beforeCommand(fnName, _api.glXCushionSGI);
    _api.glXCushionSGI(dpy, window, cushion);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SgiMakeCurrentReadAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGI_make_current_read extension.
SgiMakeCurrentReadAPI::SgiMakeCurrentReadAPI() :
    BaseExtension("GLX_SGI_make_current_read")
{
}

// Grant read-only access to the underlying function pointers.
const SgiMakeCurrentRead &SgiMakeCurrentReadAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGI_make_current_read entry points.
void SgiMakeCurrentReadAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetCurrentReadDrawableSGI().
GLXDrawable SgiMakeCurrentReadAPI::xGetCurrentReadDrawableSgi() const
{
    static const char *fnName = "glXGetCurrentReadDrawableSGI";

    beforeCommand(fnName, _api.glXGetCurrentReadDrawableSGI);
    GLXDrawable result = _api.glXGetCurrentReadDrawableSGI();
    afterCommand(fnName);

    return result;
}

// Calls glXMakeCurrentReadSGI().
Bool SgiMakeCurrentReadAPI::xMakeCurrentReadSgi(Display *dpy, GLXDrawable draw,
                                                GLXDrawable read, GLXContext ctx) const
{
    static const char *fnName = "glXMakeCurrentReadSGI";

    beforeCommand(fnName, _api.glXMakeCurrentReadSGI);
    Bool result = _api.glXMakeCurrentReadSGI(dpy, draw, read, ctx);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SgiSwapControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGI_swap_control extension.
SgiSwapControlAPI::SgiSwapControlAPI() :
    BaseExtension("GLX_SGI_swap_control")
{
}

// Grant read-only access to the underlying function pointers.
const SgiSwapControl &SgiSwapControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGI_swap_control entry points.
void SgiSwapControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXSwapIntervalSGI().
int SgiSwapControlAPI::xSwapIntervalSgi(int interval) const
{
    static const char *fnName = "glXSwapIntervalSGI";

    beforeCommand(fnName, _api.glXSwapIntervalSGI);
    int result = _api.glXSwapIntervalSGI(interval);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// SgiVideoSyncAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SGI_video_sync extension.
SgiVideoSyncAPI::SgiVideoSyncAPI() :
    BaseExtension("GLX_SGI_video_sync")
{
}

// Grant read-only access to the underlying function pointers.
const SgiVideoSync &SgiVideoSyncAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SGI_video_sync entry points.
void SgiVideoSyncAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetVideoSyncSGI().
int SgiVideoSyncAPI::xGetVideoSyncSgi(unsigned int *count) const
{
    static const char *fnName = "glXGetVideoSyncSGI";

    beforeCommand(fnName, _api.glXGetVideoSyncSGI);
    int result = _api.glXGetVideoSyncSGI(count);
    afterCommand(fnName);

    return result;
}

// Calls glXWaitVideoSyncSGI().
int SgiVideoSyncAPI::xWaitVideoSyncSgi(int divisor, int remainder,
                                       unsigned int *count) const
{
    static const char *fnName = "glXWaitVideoSyncSGI";

    beforeCommand(fnName, _api.glXWaitVideoSyncSGI);
    int result = _api.glXWaitVideoSyncSGI(divisor, remainder, count);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

