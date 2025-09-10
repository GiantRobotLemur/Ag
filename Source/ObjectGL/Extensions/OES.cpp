//! @file ObjectGL/Extensions/OES.cpp
//! @brief The definition of OES-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/OES.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __OESByteCoordinatesEntryPoints[] = {
    { offsetof(OESByteCoordinates, glMultiTexCoord1b), "glMultiTexCoord1bOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord1bv), "glMultiTexCoord1bvOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord2b), "glMultiTexCoord2bOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord2bv), "glMultiTexCoord2bvOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord3b), "glMultiTexCoord3bOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord3bv), "glMultiTexCoord3bvOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord4b), "glMultiTexCoord4bOES" },
    { offsetof(OESByteCoordinates, glMultiTexCoord4bv), "glMultiTexCoord4bvOES" },
    { offsetof(OESByteCoordinates, glTexCoord1b), "glTexCoord1bOES" },
    { offsetof(OESByteCoordinates, glTexCoord1bv), "glTexCoord1bvOES" },
    { offsetof(OESByteCoordinates, glTexCoord2b), "glTexCoord2bOES" },
    { offsetof(OESByteCoordinates, glTexCoord2bv), "glTexCoord2bvOES" },
    { offsetof(OESByteCoordinates, glTexCoord3b), "glTexCoord3bOES" },
    { offsetof(OESByteCoordinates, glTexCoord3bv), "glTexCoord3bvOES" },
    { offsetof(OESByteCoordinates, glTexCoord4b), "glTexCoord4bOES" },
    { offsetof(OESByteCoordinates, glTexCoord4bv), "glTexCoord4bvOES" },
    { offsetof(OESByteCoordinates, glVertex2b), "glVertex2bOES" },
    { offsetof(OESByteCoordinates, glVertex2bv), "glVertex2bvOES" },
    { offsetof(OESByteCoordinates, glVertex3b), "glVertex3bOES" },
    { offsetof(OESByteCoordinates, glVertex3bv), "glVertex3bvOES" },
    { offsetof(OESByteCoordinates, glVertex4b), "glVertex4bOES" },
    { offsetof(OESByteCoordinates, glVertex4bv), "glVertex4bvOES" },
};

static const EntryOffset __OESFixedPointEntryPoints[] = {
    { offsetof(OESFixedPoint, glAccumx), "glAccumxOES" },
    { offsetof(OESFixedPoint, glAlphaFuncx), "glAlphaFuncxOES" },
    { offsetof(OESFixedPoint, glBitmapx), "glBitmapxOES" },
    { offsetof(OESFixedPoint, glBlendColorx), "glBlendColorxOES" },
    { offsetof(OESFixedPoint, glClearAccumx), "glClearAccumxOES" },
    { offsetof(OESFixedPoint, glClearColorx), "glClearColorxOES" },
    { offsetof(OESFixedPoint, glClearDepthx), "glClearDepthxOES" },
    { offsetof(OESFixedPoint, glClipPlanex), "glClipPlanexOES" },
    { offsetof(OESFixedPoint, glColor3x), "glColor3xOES" },
    { offsetof(OESFixedPoint, glColor3xv), "glColor3xvOES" },
    { offsetof(OESFixedPoint, glColor4x), "glColor4xOES" },
    { offsetof(OESFixedPoint, glColor4xv), "glColor4xvOES" },
    { offsetof(OESFixedPoint, glConvolutionParameterx), "glConvolutionParameterxOES" },
    { offsetof(OESFixedPoint, glConvolutionParameterxv), "glConvolutionParameterxvOES" },
    { offsetof(OESFixedPoint, glDepthRangex), "glDepthRangexOES" },
    { offsetof(OESFixedPoint, glEvalCoord1x), "glEvalCoord1xOES" },
    { offsetof(OESFixedPoint, glEvalCoord1xv), "glEvalCoord1xvOES" },
    { offsetof(OESFixedPoint, glEvalCoord2x), "glEvalCoord2xOES" },
    { offsetof(OESFixedPoint, glEvalCoord2xv), "glEvalCoord2xvOES" },
    { offsetof(OESFixedPoint, glFeedbackBufferx), "glFeedbackBufferxOES" },
    { offsetof(OESFixedPoint, glFogx), "glFogxOES" },
    { offsetof(OESFixedPoint, glFogxv), "glFogxvOES" },
    { offsetof(OESFixedPoint, glFrustumx), "glFrustumxOES" },
    { offsetof(OESFixedPoint, glGetClipPlanex), "glGetClipPlanexOES" },
    { offsetof(OESFixedPoint, glGetConvolutionParameterxv), "glGetConvolutionParameterxvOES" },
    { offsetof(OESFixedPoint, glGetFixedv), "glGetFixedvOES" },
    { offsetof(OESFixedPoint, glGetHistogramParameterxv), "glGetHistogramParameterxvOES" },
    { offsetof(OESFixedPoint, glGetLightx), "glGetLightxOES" },
    { offsetof(OESFixedPoint, glGetMapxv), "glGetMapxvOES" },
    { offsetof(OESFixedPoint, glGetMaterialx), "glGetMaterialxOES" },
    { offsetof(OESFixedPoint, glGetPixelMapxv), "glGetPixelMapxv" },
    { offsetof(OESFixedPoint, glGetTexEnvxv), "glGetTexEnvxvOES" },
    { offsetof(OESFixedPoint, glGetTexGenxv), "glGetTexGenxvOES" },
    { offsetof(OESFixedPoint, glGetTexLevelParameterxv), "glGetTexLevelParameterxvOES" },
    { offsetof(OESFixedPoint, glGetTexParameterxv), "glGetTexParameterxvOES" },
    { offsetof(OESFixedPoint, glIndexx), "glIndexxOES" },
    { offsetof(OESFixedPoint, glIndexxv), "glIndexxvOES" },
    { offsetof(OESFixedPoint, glLightModelx), "glLightModelxOES" },
    { offsetof(OESFixedPoint, glLightModelxv), "glLightModelxvOES" },
    { offsetof(OESFixedPoint, glLightx), "glLightxOES" },
    { offsetof(OESFixedPoint, glLightxv), "glLightxvOES" },
    { offsetof(OESFixedPoint, glLineWidthx), "glLineWidthxOES" },
    { offsetof(OESFixedPoint, glLoadMatrixx), "glLoadMatrixxOES" },
    { offsetof(OESFixedPoint, glLoadTransposeMatrixx), "glLoadTransposeMatrixxOES" },
    { offsetof(OESFixedPoint, glMap1x), "glMap1xOES" },
    { offsetof(OESFixedPoint, glMap2x), "glMap2xOES" },
    { offsetof(OESFixedPoint, glMapGrid1x), "glMapGrid1xOES" },
    { offsetof(OESFixedPoint, glMapGrid2x), "glMapGrid2xOES" },
    { offsetof(OESFixedPoint, glMaterialx), "glMaterialxOES" },
    { offsetof(OESFixedPoint, glMaterialxv), "glMaterialxvOES" },
    { offsetof(OESFixedPoint, glMultMatrixx), "glMultMatrixxOES" },
    { offsetof(OESFixedPoint, glMultTransposeMatrixx), "glMultTransposeMatrixxOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord1x), "glMultiTexCoord1xOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord1xv), "glMultiTexCoord1xvOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord2x), "glMultiTexCoord2xOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord2xv), "glMultiTexCoord2xvOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord3x), "glMultiTexCoord3xOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord3xv), "glMultiTexCoord3xvOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord4x), "glMultiTexCoord4xOES" },
    { offsetof(OESFixedPoint, glMultiTexCoord4xv), "glMultiTexCoord4xvOES" },
    { offsetof(OESFixedPoint, glNormal3x), "glNormal3xOES" },
    { offsetof(OESFixedPoint, glNormal3xv), "glNormal3xvOES" },
    { offsetof(OESFixedPoint, glOrthox), "glOrthoxOES" },
    { offsetof(OESFixedPoint, glPassThroughx), "glPassThroughxOES" },
    { offsetof(OESFixedPoint, glPixelMapx), "glPixelMapx" },
    { offsetof(OESFixedPoint, glPixelStorex), "glPixelStorex" },
    { offsetof(OESFixedPoint, glPixelTransferx), "glPixelTransferxOES" },
    { offsetof(OESFixedPoint, glPixelZoomx), "glPixelZoomxOES" },
    { offsetof(OESFixedPoint, glPointParameterxv), "glPointParameterxvOES" },
    { offsetof(OESFixedPoint, glPointSizex), "glPointSizexOES" },
    { offsetof(OESFixedPoint, glPolygonOffsetx), "glPolygonOffsetxOES" },
    { offsetof(OESFixedPoint, glPrioritizeTexturesx), "glPrioritizeTexturesxOES" },
    { offsetof(OESFixedPoint, glRasterPos2x), "glRasterPos2xOES" },
    { offsetof(OESFixedPoint, glRasterPos2xv), "glRasterPos2xvOES" },
    { offsetof(OESFixedPoint, glRasterPos3x), "glRasterPos3xOES" },
    { offsetof(OESFixedPoint, glRasterPos3xv), "glRasterPos3xvOES" },
    { offsetof(OESFixedPoint, glRasterPos4x), "glRasterPos4xOES" },
    { offsetof(OESFixedPoint, glRasterPos4xv), "glRasterPos4xvOES" },
    { offsetof(OESFixedPoint, glRectx), "glRectxOES" },
    { offsetof(OESFixedPoint, glRectxv), "glRectxvOES" },
    { offsetof(OESFixedPoint, glRotatex), "glRotatexOES" },
    { offsetof(OESFixedPoint, glScalex), "glScalexOES" },
    { offsetof(OESFixedPoint, glTexCoord1x), "glTexCoord1xOES" },
    { offsetof(OESFixedPoint, glTexCoord1xv), "glTexCoord1xvOES" },
    { offsetof(OESFixedPoint, glTexCoord2x), "glTexCoord2xOES" },
    { offsetof(OESFixedPoint, glTexCoord2xv), "glTexCoord2xvOES" },
    { offsetof(OESFixedPoint, glTexCoord3x), "glTexCoord3xOES" },
    { offsetof(OESFixedPoint, glTexCoord3xv), "glTexCoord3xvOES" },
    { offsetof(OESFixedPoint, glTexCoord4x), "glTexCoord4xOES" },
    { offsetof(OESFixedPoint, glTexCoord4xv), "glTexCoord4xvOES" },
    { offsetof(OESFixedPoint, glTexEnvx), "glTexEnvxOES" },
    { offsetof(OESFixedPoint, glTexEnvxv), "glTexEnvxvOES" },
    { offsetof(OESFixedPoint, glTexGenx), "glTexGenxOES" },
    { offsetof(OESFixedPoint, glTexGenxv), "glTexGenxvOES" },
    { offsetof(OESFixedPoint, glTexParameterx), "glTexParameterxOES" },
    { offsetof(OESFixedPoint, glTexParameterxv), "glTexParameterxvOES" },
    { offsetof(OESFixedPoint, glTranslatex), "glTranslatexOES" },
    { offsetof(OESFixedPoint, glVertex2x), "glVertex2xOES" },
    { offsetof(OESFixedPoint, glVertex2xv), "glVertex2xvOES" },
    { offsetof(OESFixedPoint, glVertex3x), "glVertex3xOES" },
    { offsetof(OESFixedPoint, glVertex3xv), "glVertex3xvOES" },
    { offsetof(OESFixedPoint, glVertex4x), "glVertex4xOES" },
    { offsetof(OESFixedPoint, glVertex4xv), "glVertex4xvOES" },
};

static const EntryOffset __OESQueryMatrixEntryPoints[] = {
    { offsetof(OESQueryMatrix, glQueryMatrixx), "glQueryMatrixxOES" },
};

static const EntryOffset __OESSinglePrecisionEntryPoints[] = {
    { offsetof(OESSinglePrecision, glClearDepthf), "glClearDepthfOES" },
    { offsetof(OESSinglePrecision, glClipPlanef), "glClipPlanefOES" },
    { offsetof(OESSinglePrecision, glDepthRangef), "glDepthRangefOES" },
    { offsetof(OESSinglePrecision, glFrustumf), "glFrustumfOES" },
    { offsetof(OESSinglePrecision, glGetClipPlanef), "glGetClipPlanefOES" },
    { offsetof(OESSinglePrecision, glOrthof), "glOrthofOES" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// OESByteCoordinates Member Definitions
////////////////////////////////////////////////////////////////////////////////
OESByteCoordinates::OESByteCoordinates()
{
    std::for_each_n(__OESByteCoordinatesEntryPoints,
                    std::size(__OESByteCoordinatesEntryPoints),
                    ClearEntryPoint(this));
}

bool OESByteCoordinates::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_OES_byte_coordinates");
}

void OESByteCoordinates::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OESByteCoordinatesEntryPoints,
                    std::size(__OESByteCoordinatesEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// OESFixedPoint Member Definitions
////////////////////////////////////////////////////////////////////////////////
OESFixedPoint::OESFixedPoint()
{
    std::for_each_n(__OESFixedPointEntryPoints,
                    std::size(__OESFixedPointEntryPoints),
                    ClearEntryPoint(this));
}

bool OESFixedPoint::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_OES_fixed_point");
}

void OESFixedPoint::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OESFixedPointEntryPoints,
                    std::size(__OESFixedPointEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// OESQueryMatrix Member Definitions
////////////////////////////////////////////////////////////////////////////////
OESQueryMatrix::OESQueryMatrix()
{
    std::for_each_n(__OESQueryMatrixEntryPoints,
                    std::size(__OESQueryMatrixEntryPoints),
                    ClearEntryPoint(this));
}

bool OESQueryMatrix::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_OES_query_matrix");
}

void OESQueryMatrix::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OESQueryMatrixEntryPoints,
                    std::size(__OESQueryMatrixEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// OESSinglePrecision Member Definitions
////////////////////////////////////////////////////////////////////////////////
OESSinglePrecision::OESSinglePrecision()
{
    std::for_each_n(__OESSinglePrecisionEntryPoints,
                    std::size(__OESSinglePrecisionEntryPoints),
                    ClearEntryPoint(this));
}

bool OESSinglePrecision::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_OES_single_precision");
}

void OESSinglePrecision::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__OESSinglePrecisionEntryPoints,
                    std::size(__OESSinglePrecisionEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

