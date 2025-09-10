//! @file ObjectGL/Extensions/SGI.cpp
//! @brief The definition of Silicon Graphics-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/SGI.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __SGISDetailTextureEntryPoints[] = {
    { offsetof(SGISDetailTexture, glDetailTexFunc), "glDetailTexFuncSGIS" },
    { offsetof(SGISDetailTexture, glGetDetailTexFunc), "glGetDetailTexFuncSGIS" },
};

static const EntryOffset __SGISFogFunctionEntryPoints[] = {
    { offsetof(SGISFogFunction, glFogFunc), "glFogFuncSGIS" },
    { offsetof(SGISFogFunction, glGetFogFunc), "glGetFogFuncSGIS" },
};

static const EntryOffset __SGISMultisampleEntryPoints[] = {
    { offsetof(SGISMultisample, glSampleMask), "glSampleMaskSGIS" },
    { offsetof(SGISMultisample, glSamplePattern), "glSamplePatternSGIS" },
};

static const EntryOffset __SGISPixelTextureEntryPoints[] = {
    { offsetof(SGISPixelTexture, glGetPixelTexGenParameterfv), "glGetPixelTexGenParameterfvSGIS" },
    { offsetof(SGISPixelTexture, glGetPixelTexGenParameteriv), "glGetPixelTexGenParameterivSGIS" },
    { offsetof(SGISPixelTexture, glPixelTexGenParameterf), "glPixelTexGenParameterfSGIS" },
    { offsetof(SGISPixelTexture, glPixelTexGenParameterfv), "glPixelTexGenParameterfvSGIS" },
    { offsetof(SGISPixelTexture, glPixelTexGenParameteri), "glPixelTexGenParameteriSGIS" },
    { offsetof(SGISPixelTexture, glPixelTexGenParameteriv), "glPixelTexGenParameterivSGIS" },
};

static const EntryOffset __SGISPointParametersEntryPoints[] = {
    { offsetof(SGISPointParameters, glPointParameterf), "glPointParameterfSGIS" },
    { offsetof(SGISPointParameters, glPointParameterfv), "glPointParameterfvSGIS" },
};

static const EntryOffset __SGISSharpenTextureEntryPoints[] = {
    { offsetof(SGISSharpenTexture, glGetSharpenTexFunc), "glGetSharpenTexFuncSGIS" },
    { offsetof(SGISSharpenTexture, glSharpenTexFunc), "glSharpenTexFuncSGIS" },
};

static const EntryOffset __SGISTEXTURE4DEntryPoints[] = {
    { offsetof(SGISTEXTURE4D, glTexImage4D), "glTexImage4DSGIS" },
    { offsetof(SGISTEXTURE4D, glTexSubImage4D), "glTexSubImage4DSGIS" },
};

static const EntryOffset __SGISTextureColorMaskEntryPoints[] = {
    { offsetof(SGISTextureColorMask, glTextureColorMask), "glTextureColorMaskSGIS" },
};

static const EntryOffset __SGISTextureFILTER4EntryPoints[] = {
    { offsetof(SGISTextureFILTER4, glGetTexFilterFunc), "glGetTexFilterFuncSGIS" },
    { offsetof(SGISTextureFILTER4, glTexFilterFunc), "glTexFilterFuncSGIS" },
};

static const EntryOffset __SGIXAsyncEntryPoints[] = {
    { offsetof(SGIXAsync, glAsyncMarker), "glAsyncMarkerSGIX" },
    { offsetof(SGIXAsync, glDeleteAsyncMarkers), "glDeleteAsyncMarkersSGIX" },
    { offsetof(SGIXAsync, glFinishAsync), "glFinishAsyncSGIX" },
    { offsetof(SGIXAsync, glGenAsyncMarkers), "glGenAsyncMarkersSGIX" },
    { offsetof(SGIXAsync, glIsAsyncMarker), "glIsAsyncMarkerSGIX" },
    { offsetof(SGIXAsync, glPollAsync), "glPollAsyncSGIX" },
};

static const EntryOffset __SGIXFlushRasterEntryPoints[] = {
    { offsetof(SGIXFlushRaster, glFlushRaster), "glFlushRasterSGIX" },
};

static const EntryOffset __SGIXFragmentLightingEntryPoints[] = {
    { offsetof(SGIXFragmentLighting, glFragmentColorMaterial), "glFragmentColorMaterialSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightModelf), "glFragmentLightModelfSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightModelfv), "glFragmentLightModelfvSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightModeli), "glFragmentLightModeliSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightModeliv), "glFragmentLightModelivSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightf), "glFragmentLightfSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightfv), "glFragmentLightfvSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLighti), "glFragmentLightiSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentLightiv), "glFragmentLightivSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentMaterialf), "glFragmentMaterialfSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentMaterialfv), "glFragmentMaterialfvSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentMateriali), "glFragmentMaterialiSGIX" },
    { offsetof(SGIXFragmentLighting, glFragmentMaterialiv), "glFragmentMaterialivSGIX" },
    { offsetof(SGIXFragmentLighting, glGetFragmentLightfv), "glGetFragmentLightfvSGIX" },
    { offsetof(SGIXFragmentLighting, glGetFragmentLightiv), "glGetFragmentLightivSGIX" },
    { offsetof(SGIXFragmentLighting, glGetFragmentMaterialfv), "glGetFragmentMaterialfvSGIX" },
    { offsetof(SGIXFragmentLighting, glGetFragmentMaterialiv), "glGetFragmentMaterialivSGIX" },
    { offsetof(SGIXFragmentLighting, glLightEnvi), "glLightEnviSGIX" },
};

static const EntryOffset __SGIXFramezoomEntryPoints[] = {
    { offsetof(SGIXFramezoom, glFrameZoom), "glFrameZoomSGIX" },
};

static const EntryOffset __SGIXIglooInterfaceEntryPoints[] = {
    { offsetof(SGIXIglooInterface, glIglooInterface), "glIglooInterfaceSGIX" },
};

static const EntryOffset __SGIXInstrumentSEntryPoints[] = {
    { offsetof(SGIXInstrumentS, glGetInstruments), "glGetInstrumentsSGIX" },
    { offsetof(SGIXInstrumentS, glInstrumentsBuffer), "glInstrumentsBufferSGIX" },
    { offsetof(SGIXInstrumentS, glPollInstruments), "glPollInstrumentsSGIX" },
    { offsetof(SGIXInstrumentS, glReadInstruments), "glReadInstrumentsSGIX" },
    { offsetof(SGIXInstrumentS, glStartInstruments), "glStartInstrumentsSGIX" },
    { offsetof(SGIXInstrumentS, glStopInstruments), "glStopInstrumentsSGIX" },
};

static const EntryOffset __SGIXListPriorityEntryPoints[] = {
    { offsetof(SGIXListPriority, glGetListParameterfv), "glGetListParameterfvSGIX" },
    { offsetof(SGIXListPriority, glGetListParameteriv), "glGetListParameterivSGIX" },
    { offsetof(SGIXListPriority, glListParameterf), "glListParameterfSGIX" },
    { offsetof(SGIXListPriority, glListParameterfv), "glListParameterfvSGIX" },
    { offsetof(SGIXListPriority, glListParameteri), "glListParameteriSGIX" },
    { offsetof(SGIXListPriority, glListParameteriv), "glListParameterivSGIX" },
};

static const EntryOffset __SGIXPixelTextureEntryPoints[] = {
    { offsetof(SGIXPixelTexture, glPixelTexGen), "glPixelTexGenSGIX" },
};

static const EntryOffset __SGIXPolynomialFfdEntryPoints[] = {
    { offsetof(SGIXPolynomialFfd, glDeform), "glDeformSGIX" },
    { offsetof(SGIXPolynomialFfd, glDeformationMap3d), "glDeformationMap3dSGIX" },
    { offsetof(SGIXPolynomialFfd, glDeformationMap3f), "glDeformationMap3fSGIX" },
    { offsetof(SGIXPolynomialFfd, glLoadIdentityDeformationMap), "glLoadIdentityDeformationMapSGIX" },
};

static const EntryOffset __SGIXReferencePlaneEntryPoints[] = {
    { offsetof(SGIXReferencePlane, glReferencePlane), "glReferencePlaneSGIX" },
};

static const EntryOffset __SGIXSpriteEntryPoints[] = {
    { offsetof(SGIXSprite, glSpriteParameterf), "glSpriteParameterfSGIX" },
    { offsetof(SGIXSprite, glSpriteParameterfv), "glSpriteParameterfvSGIX" },
    { offsetof(SGIXSprite, glSpriteParameteri), "glSpriteParameteriSGIX" },
    { offsetof(SGIXSprite, glSpriteParameteriv), "glSpriteParameterivSGIX" },
};

static const EntryOffset __SGIXTagSampleBufferEntryPoints[] = {
    { offsetof(SGIXTagSampleBuffer, glTagSampleBuffer), "glTagSampleBufferSGIX" },
};

static const EntryOffset __SGIColorTableEntryPoints[] = {
    { offsetof(SGIColorTable, glColorTableParameterfv), "glColorTableParameterfvSGI" },
    { offsetof(SGIColorTable, glColorTableParameteriv), "glColorTableParameterivSGI" },
    { offsetof(SGIColorTable, glColorTable), "glColorTableSGI" },
    { offsetof(SGIColorTable, glCopyColorTable), "glCopyColorTableSGI" },
    { offsetof(SGIColorTable, glGetColorTableParameterfv), "glGetColorTableParameterfvSGI" },
    { offsetof(SGIColorTable, glGetColorTableParameteriv), "glGetColorTableParameterivSGI" },
    { offsetof(SGIColorTable, glGetColorTable), "glGetColorTableSGI" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// SGISDetailTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISDetailTexture::SGISDetailTexture()
{
    std::for_each_n(__SGISDetailTextureEntryPoints,
                    std::size(__SGISDetailTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISDetailTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_detail_texture");
}

void SGISDetailTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISDetailTextureEntryPoints,
                    std::size(__SGISDetailTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISFogFunction Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISFogFunction::SGISFogFunction()
{
    std::for_each_n(__SGISFogFunctionEntryPoints,
                    std::size(__SGISFogFunctionEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISFogFunction::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_fog_function");
}

void SGISFogFunction::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISFogFunctionEntryPoints,
                    std::size(__SGISFogFunctionEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISMultisample::SGISMultisample()
{
    std::for_each_n(__SGISMultisampleEntryPoints,
                    std::size(__SGISMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_multisample");
}

void SGISMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISMultisampleEntryPoints,
                    std::size(__SGISMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISPixelTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISPixelTexture::SGISPixelTexture()
{
    std::for_each_n(__SGISPixelTextureEntryPoints,
                    std::size(__SGISPixelTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISPixelTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_pixel_texture");
}

void SGISPixelTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISPixelTextureEntryPoints,
                    std::size(__SGISPixelTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISPointParameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISPointParameters::SGISPointParameters()
{
    std::for_each_n(__SGISPointParametersEntryPoints,
                    std::size(__SGISPointParametersEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISPointParameters::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_point_parameters");
}

void SGISPointParameters::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISPointParametersEntryPoints,
                    std::size(__SGISPointParametersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISSharpenTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISSharpenTexture::SGISSharpenTexture()
{
    std::for_each_n(__SGISSharpenTextureEntryPoints,
                    std::size(__SGISSharpenTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISSharpenTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_sharpen_texture");
}

void SGISSharpenTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISSharpenTextureEntryPoints,
                    std::size(__SGISSharpenTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISTEXTURE4D Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISTEXTURE4D::SGISTEXTURE4D()
{
    std::for_each_n(__SGISTEXTURE4DEntryPoints,
                    std::size(__SGISTEXTURE4DEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISTEXTURE4D::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_texture4D");
}

void SGISTEXTURE4D::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISTEXTURE4DEntryPoints,
                    std::size(__SGISTEXTURE4DEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISTextureColorMask Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISTextureColorMask::SGISTextureColorMask()
{
    std::for_each_n(__SGISTextureColorMaskEntryPoints,
                    std::size(__SGISTextureColorMaskEntryPoints),
                    ClearEntryPoint(this));
}

bool SGISTextureColorMask::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_texture_color_mask");
}

void SGISTextureColorMask::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISTextureColorMaskEntryPoints,
                    std::size(__SGISTextureColorMaskEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGISTextureFILTER4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGISTextureFILTER4::SGISTextureFILTER4()
{
    std::for_each_n(__SGISTextureFILTER4EntryPoints,
                    std::size(__SGISTextureFILTER4EntryPoints),
                    ClearEntryPoint(this));
}

bool SGISTextureFILTER4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIS_texture_filter4");
}

void SGISTextureFILTER4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGISTextureFILTER4EntryPoints,
                    std::size(__SGISTextureFILTER4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXAsync Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXAsync::SGIXAsync()
{
    std::for_each_n(__SGIXAsyncEntryPoints,
                    std::size(__SGIXAsyncEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXAsync::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_async");
}

void SGIXAsync::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXAsyncEntryPoints,
                    std::size(__SGIXAsyncEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFlushRaster Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXFlushRaster::SGIXFlushRaster()
{
    std::for_each_n(__SGIXFlushRasterEntryPoints,
                    std::size(__SGIXFlushRasterEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXFlushRaster::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_flush_raster");
}

void SGIXFlushRaster::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXFlushRasterEntryPoints,
                    std::size(__SGIXFlushRasterEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFragmentLighting Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXFragmentLighting::SGIXFragmentLighting()
{
    std::for_each_n(__SGIXFragmentLightingEntryPoints,
                    std::size(__SGIXFragmentLightingEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXFragmentLighting::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_fragment_lighting");
}

void SGIXFragmentLighting::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXFragmentLightingEntryPoints,
                    std::size(__SGIXFragmentLightingEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFramezoom Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXFramezoom::SGIXFramezoom()
{
    std::for_each_n(__SGIXFramezoomEntryPoints,
                    std::size(__SGIXFramezoomEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXFramezoom::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_framezoom");
}

void SGIXFramezoom::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXFramezoomEntryPoints,
                    std::size(__SGIXFramezoomEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXIglooInterface Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXIglooInterface::SGIXIglooInterface()
{
    std::for_each_n(__SGIXIglooInterfaceEntryPoints,
                    std::size(__SGIXIglooInterfaceEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXIglooInterface::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_igloo_interface");
}

void SGIXIglooInterface::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXIglooInterfaceEntryPoints,
                    std::size(__SGIXIglooInterfaceEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXInstrumentS Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXInstrumentS::SGIXInstrumentS()
{
    std::for_each_n(__SGIXInstrumentSEntryPoints,
                    std::size(__SGIXInstrumentSEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXInstrumentS::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_instruments");
}

void SGIXInstrumentS::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXInstrumentSEntryPoints,
                    std::size(__SGIXInstrumentSEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXListPriority Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXListPriority::SGIXListPriority()
{
    std::for_each_n(__SGIXListPriorityEntryPoints,
                    std::size(__SGIXListPriorityEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXListPriority::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_list_priority");
}

void SGIXListPriority::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXListPriorityEntryPoints,
                    std::size(__SGIXListPriorityEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPixelTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXPixelTexture::SGIXPixelTexture()
{
    std::for_each_n(__SGIXPixelTextureEntryPoints,
                    std::size(__SGIXPixelTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXPixelTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_pixel_texture");
}

void SGIXPixelTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXPixelTextureEntryPoints,
                    std::size(__SGIXPixelTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPolynomialFfd Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXPolynomialFfd::SGIXPolynomialFfd()
{
    std::for_each_n(__SGIXPolynomialFfdEntryPoints,
                    std::size(__SGIXPolynomialFfdEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXPolynomialFfd::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_polynomial_ffd");
}

void SGIXPolynomialFfd::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXPolynomialFfdEntryPoints,
                    std::size(__SGIXPolynomialFfdEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXReferencePlane Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXReferencePlane::SGIXReferencePlane()
{
    std::for_each_n(__SGIXReferencePlaneEntryPoints,
                    std::size(__SGIXReferencePlaneEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXReferencePlane::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_reference_plane");
}

void SGIXReferencePlane::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXReferencePlaneEntryPoints,
                    std::size(__SGIXReferencePlaneEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSprite Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXSprite::SGIXSprite()
{
    std::for_each_n(__SGIXSpriteEntryPoints,
                    std::size(__SGIXSpriteEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXSprite::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_sprite");
}

void SGIXSprite::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXSpriteEntryPoints,
                    std::size(__SGIXSpriteEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXTagSampleBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXTagSampleBuffer::SGIXTagSampleBuffer()
{
    std::for_each_n(__SGIXTagSampleBufferEntryPoints,
                    std::size(__SGIXTagSampleBufferEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIXTagSampleBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGIX_tag_sample_buffer");
}

void SGIXTagSampleBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXTagSampleBufferEntryPoints,
                    std::size(__SGIXTagSampleBufferEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIColorTable Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIColorTable::SGIColorTable()
{
    std::for_each_n(__SGIColorTableEntryPoints,
                    std::size(__SGIColorTableEntryPoints),
                    ClearEntryPoint(this));
}

bool SGIColorTable::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_SGI_color_table");
}

void SGIColorTable::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIColorTableEntryPoints,
                    std::size(__SGIColorTableEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl


#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __SGIXDmbufferEntryPoints[] = {
    { offsetof(SGIXDmbuffer, glXAssociateDMPbuffer), "glXAssociateDMPbufferSGIX" },
};

static const gl::EntryOffset __SGIXFbconfigEntryPoints[] = {
    { offsetof(SGIXFbconfig, glXChooseFBConfig), "glXChooseFBConfigSGIX" },
    { offsetof(SGIXFbconfig, glXCreateContextWithConfig), "glXCreateContextWithConfigSGIX" },
    { offsetof(SGIXFbconfig, glXCreateGLXPixmapWithConfig), "glXCreateGLXPixmapWithConfigSGIX" },
    { offsetof(SGIXFbconfig, glXGetFBConfigAttrib), "glXGetFBConfigAttribSGIX" },
    { offsetof(SGIXFbconfig, glXGetFBConfigFromVisual), "glXGetFBConfigFromVisualSGIX" },
    { offsetof(SGIXFbconfig, glXGetVisualFromFBConfig), "glXGetVisualFromFBConfigSGIX" },
};

static const gl::EntryOffset __SGIXHyperpipeEntryPoints[] = {
    { offsetof(SGIXHyperpipe, glXBindHyperpipe), "glXBindHyperpipeSGIX" },
    { offsetof(SGIXHyperpipe, glXDestroyHyperpipeConfig), "glXDestroyHyperpipeConfigSGIX" },
    { offsetof(SGIXHyperpipe, glXHyperpipeAttrib), "glXHyperpipeAttribSGIX" },
    { offsetof(SGIXHyperpipe, glXHyperpipeConfig), "glXHyperpipeConfigSGIX" },
    { offsetof(SGIXHyperpipe, glXQueryHyperpipeAttrib), "glXQueryHyperpipeAttribSGIX" },
    { offsetof(SGIXHyperpipe, glXQueryHyperpipeBestAttrib), "glXQueryHyperpipeBestAttribSGIX" },
    { offsetof(SGIXHyperpipe, glXQueryHyperpipeConfig), "glXQueryHyperpipeConfigSGIX" },
    { offsetof(SGIXHyperpipe, glXQueryHyperpipeNetwork), "glXQueryHyperpipeNetworkSGIX" },
};

static const gl::EntryOffset __SGIXPbufferEntryPoints[] = {
    { offsetof(SGIXPbuffer, glXCreateGLXPbuffer), "glXCreateGLXPbufferSGIX" },
    { offsetof(SGIXPbuffer, glXDestroyGLXPbuffer), "glXDestroyGLXPbufferSGIX" },
    { offsetof(SGIXPbuffer, glXGetSelectedEvent), "glXGetSelectedEventSGIX" },
    { offsetof(SGIXPbuffer, glXQueryGLXPbuffer), "glXQueryGLXPbufferSGIX" },
    { offsetof(SGIXPbuffer, glXSelectEvent), "glXSelectEventSGIX" },
};

static const gl::EntryOffset __SGIXSwapBarrierEntryPoints[] = {
    { offsetof(SGIXSwapBarrier, glXBindSwapBarrier), "glXBindSwapBarrierSGIX" },
    { offsetof(SGIXSwapBarrier, glXQueryMaxSwapBarriers), "glXQueryMaxSwapBarriersSGIX" },
};

static const gl::EntryOffset __SGIXSwapGroupEntryPoints[] = {
    { offsetof(SGIXSwapGroup, glXJoinSwapGroup), "glXJoinSwapGroupSGIX" },
};

static const gl::EntryOffset __SGIXVideoResizeEntryPoints[] = {
    { offsetof(SGIXVideoResize, glXBindChannelToWindow), "glXBindChannelToWindowSGIX" },
    { offsetof(SGIXVideoResize, glXChannelRect), "glXChannelRectSGIX" },
    { offsetof(SGIXVideoResize, glXChannelRectSync), "glXChannelRectSyncSGIX" },
    { offsetof(SGIXVideoResize, glXQueryChannelDeltas), "glXQueryChannelDeltasSGIX" },
    { offsetof(SGIXVideoResize, glXQueryChannelRect), "glXQueryChannelRectSGIX" },
};

static const gl::EntryOffset __SGIXVideoSourceEntryPoints[] = {
    { offsetof(SGIXVideoSource, glXCreateGLXVideoSource), "glXCreateGLXVideoSourceSGIX" },
    { offsetof(SGIXVideoSource, glXDestroyGLXVideoSource), "glXDestroyGLXVideoSourceSGIX" },
};

static const gl::EntryOffset __SgiCushionEntryPoints[] = {
    { offsetof(SgiCushion, glXCushionSGI), "glXCushionSGI" },
};

static const gl::EntryOffset __SgiMakeCurrentReadEntryPoints[] = {
    { offsetof(SgiMakeCurrentRead, glXGetCurrentReadDrawableSGI), "glXGetCurrentReadDrawableSGI" },
    { offsetof(SgiMakeCurrentRead, glXMakeCurrentReadSGI), "glXMakeCurrentReadSGI" },
};

static const gl::EntryOffset __SgiSwapControlEntryPoints[] = {
    { offsetof(SgiSwapControl, glXSwapIntervalSGI), "glXSwapIntervalSGI" },
};

static const gl::EntryOffset __SgiVideoSyncEntryPoints[] = {
    { offsetof(SgiVideoSync, glXGetVideoSyncSGI), "glXGetVideoSyncSGI" },
    { offsetof(SgiVideoSync, glXWaitVideoSyncSGI), "glXWaitVideoSyncSGI" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// SGIXDmbuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXDmbuffer::SGIXDmbuffer()
{
    std::for_each_n(__SGIXDmbufferEntryPoints,
                    std::size(__SGIXDmbufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXDmbuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_dmbuffer");
}

void SGIXDmbuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXDmbufferEntryPoints,
                    std::size(__SGIXDmbufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXFbconfig Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXFbconfig::SGIXFbconfig()
{
    std::for_each_n(__SGIXFbconfigEntryPoints,
                    std::size(__SGIXFbconfigEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXFbconfig::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_fbconfig");
}

void SGIXFbconfig::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXFbconfigEntryPoints,
                    std::size(__SGIXFbconfigEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXHyperpipe Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXHyperpipe::SGIXHyperpipe()
{
    std::for_each_n(__SGIXHyperpipeEntryPoints,
                    std::size(__SGIXHyperpipeEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXHyperpipe::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_hyperpipe");
}

void SGIXHyperpipe::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXHyperpipeEntryPoints,
                    std::size(__SGIXHyperpipeEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXPbuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXPbuffer::SGIXPbuffer()
{
    std::for_each_n(__SGIXPbufferEntryPoints,
                    std::size(__SGIXPbufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXPbuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_pbuffer");
}

void SGIXPbuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXPbufferEntryPoints,
                    std::size(__SGIXPbufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSwapBarrier Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXSwapBarrier::SGIXSwapBarrier()
{
    std::for_each_n(__SGIXSwapBarrierEntryPoints,
                    std::size(__SGIXSwapBarrierEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXSwapBarrier::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_swap_barrier");
}

void SGIXSwapBarrier::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXSwapBarrierEntryPoints,
                    std::size(__SGIXSwapBarrierEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXSwapGroup Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXSwapGroup::SGIXSwapGroup()
{
    std::for_each_n(__SGIXSwapGroupEntryPoints,
                    std::size(__SGIXSwapGroupEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXSwapGroup::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_swap_group");
}

void SGIXSwapGroup::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXSwapGroupEntryPoints,
                    std::size(__SGIXSwapGroupEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXVideoResize Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXVideoResize::SGIXVideoResize()
{
    std::for_each_n(__SGIXVideoResizeEntryPoints,
                    std::size(__SGIXVideoResizeEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXVideoResize::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_video_resize");
}

void SGIXVideoResize::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXVideoResizeEntryPoints,
                    std::size(__SGIXVideoResizeEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SGIXVideoSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
SGIXVideoSource::SGIXVideoSource()
{
    std::for_each_n(__SGIXVideoSourceEntryPoints,
                    std::size(__SGIXVideoSourceEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SGIXVideoSource::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGIX_video_source");
}

void SGIXVideoSource::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SGIXVideoSourceEntryPoints,
                    std::size(__SGIXVideoSourceEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SgiCushion Member Definitions
////////////////////////////////////////////////////////////////////////////////
SgiCushion::SgiCushion()
{
    std::for_each_n(__SgiCushionEntryPoints,
                    std::size(__SgiCushionEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SgiCushion::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGI_cushion");
}

void SgiCushion::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SgiCushionEntryPoints,
                    std::size(__SgiCushionEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SgiMakeCurrentRead Member Definitions
////////////////////////////////////////////////////////////////////////////////
SgiMakeCurrentRead::SgiMakeCurrentRead()
{
    std::for_each_n(__SgiMakeCurrentReadEntryPoints,
                    std::size(__SgiMakeCurrentReadEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SgiMakeCurrentRead::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGI_make_current_read");
}

void SgiMakeCurrentRead::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SgiMakeCurrentReadEntryPoints,
                    std::size(__SgiMakeCurrentReadEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SgiSwapControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
SgiSwapControl::SgiSwapControl()
{
    std::for_each_n(__SgiSwapControlEntryPoints,
                    std::size(__SgiSwapControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SgiSwapControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGI_swap_control");
}

void SgiSwapControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SgiSwapControlEntryPoints,
                    std::size(__SgiSwapControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// SgiVideoSync Member Definitions
////////////////////////////////////////////////////////////////////////////////
SgiVideoSync::SgiVideoSync()
{
    std::for_each_n(__SgiVideoSyncEntryPoints,
                    std::size(__SgiVideoSyncEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool SgiVideoSync::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_SGI_video_sync");
}

void SgiVideoSync::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__SgiVideoSyncEntryPoints,
                    std::size(__SgiVideoSyncEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

