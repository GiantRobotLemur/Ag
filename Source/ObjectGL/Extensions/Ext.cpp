//! @file ObjectGL/Extensions/Ext.cpp
//! @brief The definition of generic extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Ext.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __EXTEglImageStorageEntryPoints[] = {
    { offsetof(EXTEglImageStorage, glEGLImageTargetTexStorage), "glEGLImageTargetTexStorageEXT" },
    { offsetof(EXTEglImageStorage, glEGLImageTargetTextureStorage), "glEGLImageTargetTextureStorageEXT" },
};

static const EntryOffset __EXTBindableUniformEntryPoints[] = {
    { offsetof(EXTBindableUniform, glGetUniformBufferSize), "glGetUniformBufferSizeEXT" },
    { offsetof(EXTBindableUniform, glGetUniformOffset), "glGetUniformOffsetEXT" },
    { offsetof(EXTBindableUniform, glUniformBuffer), "glUniformBufferEXT" },
};

static const EntryOffset __EXTBlendColorEntryPoints[] = {
    { offsetof(EXTBlendColor, glBlendColor), "glBlendColorEXT" },
};

static const EntryOffset __EXTBlendEquationSeparateEntryPoints[] = {
    { offsetof(EXTBlendEquationSeparate, glBlendEquationSeparate), "glBlendEquationSeparateEXT" },
};

static const EntryOffset __EXTBlendFuncSeparateEntryPoints[] = {
    { offsetof(EXTBlendFuncSeparate, glBlendFuncSeparate), "glBlendFuncSeparateEXT" },
};

static const EntryOffset __EXTBlendMinmaxEntryPoints[] = {
    { offsetof(EXTBlendMinmax, glBlendEquation), "glBlendEquationEXT" },
};

static const EntryOffset __EXTColorSubtableEntryPoints[] = {
    { offsetof(EXTColorSubtable, glColorSubTable), "glColorSubTableEXT" },
    { offsetof(EXTColorSubtable, glCopyColorSubTable), "glCopyColorSubTableEXT" },
};

static const EntryOffset __EXTCompiledVertexArrayEntryPoints[] = {
    { offsetof(EXTCompiledVertexArray, glLockArrays), "glLockArraysEXT" },
    { offsetof(EXTCompiledVertexArray, glUnlockArrays), "glUnlockArraysEXT" },
};

static const EntryOffset __EXTConvolutionEntryPoints[] = {
    { offsetof(EXTConvolution, glConvolutionFilter1D), "glConvolutionFilter1DEXT" },
    { offsetof(EXTConvolution, glConvolutionFilter2D), "glConvolutionFilter2DEXT" },
    { offsetof(EXTConvolution, glConvolutionParameterf), "glConvolutionParameterfEXT" },
    { offsetof(EXTConvolution, glConvolutionParameterfv), "glConvolutionParameterfvEXT" },
    { offsetof(EXTConvolution, glConvolutionParameteri), "glConvolutionParameteriEXT" },
    { offsetof(EXTConvolution, glConvolutionParameteriv), "glConvolutionParameterivEXT" },
    { offsetof(EXTConvolution, glCopyConvolutionFilter1D), "glCopyConvolutionFilter1DEXT" },
    { offsetof(EXTConvolution, glCopyConvolutionFilter2D), "glCopyConvolutionFilter2DEXT" },
    { offsetof(EXTConvolution, glGetConvolutionFilter), "glGetConvolutionFilterEXT" },
    { offsetof(EXTConvolution, glGetConvolutionParameterfv), "glGetConvolutionParameterfvEXT" },
    { offsetof(EXTConvolution, glGetConvolutionParameteriv), "glGetConvolutionParameterivEXT" },
    { offsetof(EXTConvolution, glGetSeparableFilter), "glGetSeparableFilterEXT" },
    { offsetof(EXTConvolution, glSeparableFilter2D), "glSeparableFilter2DEXT" },
};

static const EntryOffset __EXTCoordinateFrameEntryPoints[] = {
    { offsetof(EXTCoordinateFrame, glBinormal3b), "glBinormal3bEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3bv), "glBinormal3bvEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3d), "glBinormal3dEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3dv), "glBinormal3dvEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3f), "glBinormal3fEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3fv), "glBinormal3fvEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3i), "glBinormal3iEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3iv), "glBinormal3ivEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3s), "glBinormal3sEXT" },
    { offsetof(EXTCoordinateFrame, glBinormal3sv), "glBinormal3svEXT" },
    { offsetof(EXTCoordinateFrame, glBinormalPointer), "glBinormalPointerEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3b), "glTangent3bEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3bv), "glTangent3bvEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3d), "glTangent3dEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3dv), "glTangent3dvEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3f), "glTangent3fEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3fv), "glTangent3fvEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3i), "glTangent3iEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3iv), "glTangent3ivEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3s), "glTangent3sEXT" },
    { offsetof(EXTCoordinateFrame, glTangent3sv), "glTangent3svEXT" },
    { offsetof(EXTCoordinateFrame, glTangentPointer), "glTangentPointerEXT" },
};

static const EntryOffset __EXTCopyTextureEntryPoints[] = {
    { offsetof(EXTCopyTexture, glCopyTexImage1D), "glCopyTexImage1DEXT" },
    { offsetof(EXTCopyTexture, glCopyTexImage2D), "glCopyTexImage2DEXT" },
    { offsetof(EXTCopyTexture, glCopyTexSubImage1D), "glCopyTexSubImage1DEXT" },
    { offsetof(EXTCopyTexture, glCopyTexSubImage2D), "glCopyTexSubImage2DEXT" },
    { offsetof(EXTCopyTexture, glCopyTexSubImage3D), "glCopyTexSubImage3DEXT" },
};

static const EntryOffset __EXTCullVertexEntryPoints[] = {
    { offsetof(EXTCullVertex, glCullParameterdv), "glCullParameterdvEXT" },
    { offsetof(EXTCullVertex, glCullParameterfv), "glCullParameterfvEXT" },
};

static const EntryOffset __EXTDebugLabelEntryPoints[] = {
    { offsetof(EXTDebugLabel, glGetObjectLabel), "glGetObjectLabelEXT" },
    { offsetof(EXTDebugLabel, glLabelObject), "glLabelObjectEXT" },
};

static const EntryOffset __EXTDebugMarkerEntryPoints[] = {
    { offsetof(EXTDebugMarker, glInsertEventMarker), "glInsertEventMarkerEXT" },
    { offsetof(EXTDebugMarker, glPopGroupMarker), "glPopGroupMarkerEXT" },
    { offsetof(EXTDebugMarker, glPushGroupMarker), "glPushGroupMarkerEXT" },
};

static const EntryOffset __EXTDepthBoundsTestEntryPoints[] = {
    { offsetof(EXTDepthBoundsTest, glDepthBounds), "glDepthBoundsEXT" },
};

static const EntryOffset __EXTDirectStateAccessEntryPoints[] = {
    { offsetof(EXTDirectStateAccess, glBindMultiTexture), "glBindMultiTextureEXT" },
    { offsetof(EXTDirectStateAccess, glCheckNamedFramebufferStatus), "glCheckNamedFramebufferStatusEXT" },
    { offsetof(EXTDirectStateAccess, glClearNamedBufferData), "glClearNamedBufferDataEXT" },
    { offsetof(EXTDirectStateAccess, glClearNamedBufferSubData), "glClearNamedBufferSubDataEXT" },
    { offsetof(EXTDirectStateAccess, glClientAttribDefault), "glClientAttribDefaultEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexImage1D), "glCompressedMultiTexImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexImage2D), "glCompressedMultiTexImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexImage3D), "glCompressedMultiTexImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexSubImage1D), "glCompressedMultiTexSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexSubImage2D), "glCompressedMultiTexSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedMultiTexSubImage3D), "glCompressedMultiTexSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureImage1D), "glCompressedTextureImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureImage2D), "glCompressedTextureImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureImage3D), "glCompressedTextureImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureSubImage1D), "glCompressedTextureSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureSubImage2D), "glCompressedTextureSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCompressedTextureSubImage3D), "glCompressedTextureSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyMultiTexImage1D), "glCopyMultiTexImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyMultiTexImage2D), "glCopyMultiTexImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyMultiTexSubImage1D), "glCopyMultiTexSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyMultiTexSubImage2D), "glCopyMultiTexSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyMultiTexSubImage3D), "glCopyMultiTexSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyTextureImage1D), "glCopyTextureImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyTextureImage2D), "glCopyTextureImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyTextureSubImage1D), "glCopyTextureSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyTextureSubImage2D), "glCopyTextureSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glCopyTextureSubImage3D), "glCopyTextureSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glDisableClientStateIndexed), "glDisableClientStateIndexedEXT" },
    { offsetof(EXTDirectStateAccess, glDisableClientStatei), "glDisableClientStateiEXT" },
    { offsetof(EXTDirectStateAccess, glDisableIndexed), "glDisableIndexedEXT" },
    { offsetof(EXTDirectStateAccess, glDisableVertexArrayAttrib), "glDisableVertexArrayAttribEXT" },
    { offsetof(EXTDirectStateAccess, glDisableVertexArray), "glDisableVertexArrayEXT" },
    { offsetof(EXTDirectStateAccess, glEnableClientStateIndexed), "glEnableClientStateIndexedEXT" },
    { offsetof(EXTDirectStateAccess, glEnableClientStatei), "glEnableClientStateiEXT" },
    { offsetof(EXTDirectStateAccess, glEnableIndexed), "glEnableIndexedEXT" },
    { offsetof(EXTDirectStateAccess, glEnableVertexArrayAttrib), "glEnableVertexArrayAttribEXT" },
    { offsetof(EXTDirectStateAccess, glEnableVertexArray), "glEnableVertexArrayEXT" },
    { offsetof(EXTDirectStateAccess, glFlushMappedNamedBufferRange), "glFlushMappedNamedBufferRangeEXT" },
    { offsetof(EXTDirectStateAccess, glFramebufferDrawBuffer), "glFramebufferDrawBufferEXT" },
    { offsetof(EXTDirectStateAccess, glFramebufferDrawBuffers), "glFramebufferDrawBuffersEXT" },
    { offsetof(EXTDirectStateAccess, glFramebufferReadBuffer), "glFramebufferReadBufferEXT" },
    { offsetof(EXTDirectStateAccess, glGenerateMultiTexMipmap), "glGenerateMultiTexMipmapEXT" },
    { offsetof(EXTDirectStateAccess, glGenerateTextureMipmap), "glGenerateTextureMipmapEXT" },
    { offsetof(EXTDirectStateAccess, glGetBooleanIndexedv), "glGetBooleanIndexedvEXT" },
    { offsetof(EXTDirectStateAccess, glGetCompressedMultiTexImage), "glGetCompressedMultiTexImageEXT" },
    { offsetof(EXTDirectStateAccess, glGetCompressedTextureImage), "glGetCompressedTextureImageEXT" },
    { offsetof(EXTDirectStateAccess, glGetDoubleIndexedv), "glGetDoubleIndexedvEXT" },
    { offsetof(EXTDirectStateAccess, glGetDoublei_v), "glGetDoublei_vEXT" },
    { offsetof(EXTDirectStateAccess, glGetFloatIndexedv), "glGetFloatIndexedvEXT" },
    { offsetof(EXTDirectStateAccess, glGetFloati_v), "glGetFloati_vEXT" },
    { offsetof(EXTDirectStateAccess, glGetFramebufferParameteriv), "glGetFramebufferParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetIntegerIndexedv), "glGetIntegerIndexedvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexEnvfv), "glGetMultiTexEnvfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexEnviv), "glGetMultiTexEnvivEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexGendv), "glGetMultiTexGendvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexGenfv), "glGetMultiTexGenfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexGeniv), "glGetMultiTexGenivEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexImage), "glGetMultiTexImageEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexLevelParameterfv), "glGetMultiTexLevelParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexLevelParameteriv), "glGetMultiTexLevelParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexParameterIiv), "glGetMultiTexParameterIivEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexParameterIuiv), "glGetMultiTexParameterIuivEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexParameterfv), "glGetMultiTexParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetMultiTexParameteriv), "glGetMultiTexParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedBufferParameteriv), "glGetNamedBufferParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedBufferPointerv), "glGetNamedBufferPointervEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedBufferSubData), "glGetNamedBufferSubDataEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedFramebufferAttachmentParameteriv), "glGetNamedFramebufferAttachmentParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedFramebufferParameteriv), "glGetNamedFramebufferParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramLocalParameterIiv), "glGetNamedProgramLocalParameterIivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramLocalParameterIuiv), "glGetNamedProgramLocalParameterIuivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramLocalParameterdv), "glGetNamedProgramLocalParameterdvEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramLocalParameterfv), "glGetNamedProgramLocalParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramString), "glGetNamedProgramStringEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedProgramiv), "glGetNamedProgramivEXT" },
    { offsetof(EXTDirectStateAccess, glGetNamedRenderbufferParameteriv), "glGetNamedRenderbufferParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetPointerIndexedv), "glGetPointerIndexedvEXT" },
    { offsetof(EXTDirectStateAccess, glGetPointeri_v), "glGetPointeri_vEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureImage), "glGetTextureImageEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureLevelParameterfv), "glGetTextureLevelParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureLevelParameteriv), "glGetTextureLevelParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureParameterIiv), "glGetTextureParameterIivEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureParameterIuiv), "glGetTextureParameterIuivEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureParameterfv), "glGetTextureParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glGetTextureParameteriv), "glGetTextureParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glGetVertexArrayIntegeri_v), "glGetVertexArrayIntegeri_vEXT" },
    { offsetof(EXTDirectStateAccess, glGetVertexArrayIntegerv), "glGetVertexArrayIntegervEXT" },
    { offsetof(EXTDirectStateAccess, glGetVertexArrayPointeri_v), "glGetVertexArrayPointeri_vEXT" },
    { offsetof(EXTDirectStateAccess, glGetVertexArrayPointerv), "glGetVertexArrayPointervEXT" },
    { offsetof(EXTDirectStateAccess, glIsEnabledIndexed), "glIsEnabledIndexedEXT" },
    { offsetof(EXTDirectStateAccess, glMapNamedBuffer), "glMapNamedBufferEXT" },
    { offsetof(EXTDirectStateAccess, glMapNamedBufferRange), "glMapNamedBufferRangeEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixFrustum), "glMatrixFrustumEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixLoadIdentity), "glMatrixLoadIdentityEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixLoadTransposed), "glMatrixLoadTransposedEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixLoadTransposef), "glMatrixLoadTransposefEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixLoadd), "glMatrixLoaddEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixLoadf), "glMatrixLoadfEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixMultTransposed), "glMatrixMultTransposedEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixMultTransposef), "glMatrixMultTransposefEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixMultd), "glMatrixMultdEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixMultf), "glMatrixMultfEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixOrtho), "glMatrixOrthoEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixPop), "glMatrixPopEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixPush), "glMatrixPushEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixRotated), "glMatrixRotatedEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixRotatef), "glMatrixRotatefEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixScaled), "glMatrixScaledEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixScalef), "glMatrixScalefEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixTranslated), "glMatrixTranslatedEXT" },
    { offsetof(EXTDirectStateAccess, glMatrixTranslatef), "glMatrixTranslatefEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexBuffer), "glMultiTexBufferEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexCoordPointer), "glMultiTexCoordPointerEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexEnvf), "glMultiTexEnvfEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexEnvfv), "glMultiTexEnvfvEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexEnvi), "glMultiTexEnviEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexEnviv), "glMultiTexEnvivEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGend), "glMultiTexGendEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGendv), "glMultiTexGendvEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGenf), "glMultiTexGenfEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGenfv), "glMultiTexGenfvEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGeni), "glMultiTexGeniEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexGeniv), "glMultiTexGenivEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexImage1D), "glMultiTexImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexImage2D), "glMultiTexImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexImage3D), "glMultiTexImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameterIiv), "glMultiTexParameterIivEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameterIuiv), "glMultiTexParameterIuivEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameterf), "glMultiTexParameterfEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameterfv), "glMultiTexParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameteri), "glMultiTexParameteriEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexParameteriv), "glMultiTexParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexRenderbuffer), "glMultiTexRenderbufferEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexSubImage1D), "glMultiTexSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexSubImage2D), "glMultiTexSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glMultiTexSubImage3D), "glMultiTexSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glNamedBufferData), "glNamedBufferDataEXT" },
    { offsetof(EXTDirectStateAccess, glNamedBufferStorage), "glNamedBufferStorageEXT" },
    { offsetof(EXTDirectStateAccess, glNamedBufferSubData), "glNamedBufferSubDataEXT" },
    { offsetof(EXTDirectStateAccess, glNamedCopyBufferSubData), "glNamedCopyBufferSubDataEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferParameteri), "glNamedFramebufferParameteriEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferRenderbuffer), "glNamedFramebufferRenderbufferEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTexture1D), "glNamedFramebufferTexture1DEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTexture2D), "glNamedFramebufferTexture2DEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTexture3D), "glNamedFramebufferTexture3DEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTexture), "glNamedFramebufferTextureEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTextureFace), "glNamedFramebufferTextureFaceEXT" },
    { offsetof(EXTDirectStateAccess, glNamedFramebufferTextureLayer), "glNamedFramebufferTextureLayerEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameter4d), "glNamedProgramLocalParameter4dEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameter4dv), "glNamedProgramLocalParameter4dvEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameter4f), "glNamedProgramLocalParameter4fEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameter4fv), "glNamedProgramLocalParameter4fvEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameterI4i), "glNamedProgramLocalParameterI4iEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameterI4iv), "glNamedProgramLocalParameterI4ivEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameterI4ui), "glNamedProgramLocalParameterI4uiEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameterI4uiv), "glNamedProgramLocalParameterI4uivEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParameters4fv), "glNamedProgramLocalParameters4fvEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParametersI4iv), "glNamedProgramLocalParametersI4ivEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramLocalParametersI4uiv), "glNamedProgramLocalParametersI4uivEXT" },
    { offsetof(EXTDirectStateAccess, glNamedProgramString), "glNamedProgramStringEXT" },
    { offsetof(EXTDirectStateAccess, glNamedRenderbufferStorage), "glNamedRenderbufferStorageEXT" },
    { offsetof(EXTDirectStateAccess, glNamedRenderbufferStorageMultisampleCoverage), "glNamedRenderbufferStorageMultisampleCoverageEXT" },
    { offsetof(EXTDirectStateAccess, glNamedRenderbufferStorageMultisample), "glNamedRenderbufferStorageMultisampleEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1d), "glProgramUniform1dEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1dv), "glProgramUniform1dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1f), "glProgramUniform1fEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1fv), "glProgramUniform1fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1i), "glProgramUniform1iEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1iv), "glProgramUniform1ivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1ui), "glProgramUniform1uiEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform1uiv), "glProgramUniform1uivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2d), "glProgramUniform2dEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2dv), "glProgramUniform2dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2f), "glProgramUniform2fEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2fv), "glProgramUniform2fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2i), "glProgramUniform2iEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2iv), "glProgramUniform2ivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2ui), "glProgramUniform2uiEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform2uiv), "glProgramUniform2uivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3d), "glProgramUniform3dEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3dv), "glProgramUniform3dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3f), "glProgramUniform3fEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3fv), "glProgramUniform3fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3i), "glProgramUniform3iEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3iv), "glProgramUniform3ivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3ui), "glProgramUniform3uiEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform3uiv), "glProgramUniform3uivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4d), "glProgramUniform4dEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4dv), "glProgramUniform4dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4f), "glProgramUniform4fEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4fv), "glProgramUniform4fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4i), "glProgramUniform4iEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4iv), "glProgramUniform4ivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4ui), "glProgramUniform4uiEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniform4uiv), "glProgramUniform4uivEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2dv), "glProgramUniformMatrix2dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2fv), "glProgramUniformMatrix2fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2x3dv), "glProgramUniformMatrix2x3dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2x3fv), "glProgramUniformMatrix2x3fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2x4dv), "glProgramUniformMatrix2x4dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix2x4fv), "glProgramUniformMatrix2x4fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3dv), "glProgramUniformMatrix3dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3fv), "glProgramUniformMatrix3fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3x2dv), "glProgramUniformMatrix3x2dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3x2fv), "glProgramUniformMatrix3x2fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3x4dv), "glProgramUniformMatrix3x4dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix3x4fv), "glProgramUniformMatrix3x4fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4dv), "glProgramUniformMatrix4dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4fv), "glProgramUniformMatrix4fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4x2dv), "glProgramUniformMatrix4x2dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4x2fv), "glProgramUniformMatrix4x2fvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4x3dv), "glProgramUniformMatrix4x3dvEXT" },
    { offsetof(EXTDirectStateAccess, glProgramUniformMatrix4x3fv), "glProgramUniformMatrix4x3fvEXT" },
    { offsetof(EXTDirectStateAccess, glPushClientAttribDefault), "glPushClientAttribDefaultEXT" },
    { offsetof(EXTDirectStateAccess, glTextureBuffer), "glTextureBufferEXT" },
    { offsetof(EXTDirectStateAccess, glTextureBufferRange), "glTextureBufferRangeEXT" },
    { offsetof(EXTDirectStateAccess, glTextureImage1D), "glTextureImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureImage2D), "glTextureImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureImage3D), "glTextureImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glTexturePageCommitment), "glTexturePageCommitmentEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameterIiv), "glTextureParameterIivEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameterIuiv), "glTextureParameterIuivEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameterf), "glTextureParameterfEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameterfv), "glTextureParameterfvEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameteri), "glTextureParameteriEXT" },
    { offsetof(EXTDirectStateAccess, glTextureParameteriv), "glTextureParameterivEXT" },
    { offsetof(EXTDirectStateAccess, glTextureRenderbuffer), "glTextureRenderbufferEXT" },
    { offsetof(EXTDirectStateAccess, glTextureStorage1D), "glTextureStorage1DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureStorage2D), "glTextureStorage2DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureStorage2DMultisample), "glTextureStorage2DMultisampleEXT" },
    { offsetof(EXTDirectStateAccess, glTextureStorage3D), "glTextureStorage3DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureStorage3DMultisample), "glTextureStorage3DMultisampleEXT" },
    { offsetof(EXTDirectStateAccess, glTextureSubImage1D), "glTextureSubImage1DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureSubImage2D), "glTextureSubImage2DEXT" },
    { offsetof(EXTDirectStateAccess, glTextureSubImage3D), "glTextureSubImage3DEXT" },
    { offsetof(EXTDirectStateAccess, glUnmapNamedBuffer), "glUnmapNamedBufferEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayBindVertexBuffer), "glVertexArrayBindVertexBufferEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayColorOffset), "glVertexArrayColorOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayEdgeFlagOffset), "glVertexArrayEdgeFlagOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayFogCoordOffset), "glVertexArrayFogCoordOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayIndexOffset), "glVertexArrayIndexOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayMultiTexCoordOffset), "glVertexArrayMultiTexCoordOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayNormalOffset), "glVertexArrayNormalOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArraySecondaryColorOffset), "glVertexArraySecondaryColorOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayTexCoordOffset), "glVertexArrayTexCoordOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribBinding), "glVertexArrayVertexAttribBindingEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribDivisor), "glVertexArrayVertexAttribDivisorEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribFormat), "glVertexArrayVertexAttribFormatEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribIFormat), "glVertexArrayVertexAttribIFormatEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribIOffset), "glVertexArrayVertexAttribIOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribLFormat), "glVertexArrayVertexAttribLFormatEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribLOffset), "glVertexArrayVertexAttribLOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexAttribOffset), "glVertexArrayVertexAttribOffsetEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexBindingDivisor), "glVertexArrayVertexBindingDivisorEXT" },
    { offsetof(EXTDirectStateAccess, glVertexArrayVertexOffset), "glVertexArrayVertexOffsetEXT" },
};

static const EntryOffset __EXTDrawBUFFERS2EntryPoints[] = {
    { offsetof(EXTDrawBUFFERS2, glColorMaskIndexed), "glColorMaskIndexedEXT" },
};

static const EntryOffset __EXTDrawInstancedEntryPoints[] = {
    { offsetof(EXTDrawInstanced, glDrawArraysInstanced), "glDrawArraysInstancedEXT" },
    { offsetof(EXTDrawInstanced, glDrawElementsInstanced), "glDrawElementsInstancedEXT" },
};

static const EntryOffset __EXTDrawRangeElementsEntryPoints[] = {
    { offsetof(EXTDrawRangeElements, glDrawRangeElements), "glDrawRangeElementsEXT" },
};

static const EntryOffset __EXTExternalBufferEntryPoints[] = {
    { offsetof(EXTExternalBuffer, glBufferStorageExternal), "glBufferStorageExternalEXT" },
    { offsetof(EXTExternalBuffer, glNamedBufferStorageExternal), "glNamedBufferStorageExternalEXT" },
};

static const EntryOffset __EXTFogCoordEntryPoints[] = {
    { offsetof(EXTFogCoord, glFogCoordPointer), "glFogCoordPointerEXT" },
    { offsetof(EXTFogCoord, glFogCoordd), "glFogCoorddEXT" },
    { offsetof(EXTFogCoord, glFogCoorddv), "glFogCoorddvEXT" },
    { offsetof(EXTFogCoord, glFogCoordf), "glFogCoordfEXT" },
    { offsetof(EXTFogCoord, glFogCoordfv), "glFogCoordfvEXT" },
};

static const EntryOffset __EXTFramebufferBlitEntryPoints[] = {
    { offsetof(EXTFramebufferBlit, glBlitFramebuffer), "glBlitFramebufferEXT" },
};

static const EntryOffset __EXTFramebufferBlitLayersEntryPoints[] = {
    { offsetof(EXTFramebufferBlitLayers, glBlitFramebufferLayer), "glBlitFramebufferLayerEXT" },
    { offsetof(EXTFramebufferBlitLayers, glBlitFramebufferLayers), "glBlitFramebufferLayersEXT" },
};

static const EntryOffset __EXTFramebufferMultisampleEntryPoints[] = {
    { offsetof(EXTFramebufferMultisample, glRenderbufferStorageMultisample), "glRenderbufferStorageMultisampleEXT" },
};

static const EntryOffset __EXTFramebufferObjectEntryPoints[] = {
    { offsetof(EXTFramebufferObject, glBindFramebuffer), "glBindFramebufferEXT" },
    { offsetof(EXTFramebufferObject, glBindRenderbuffer), "glBindRenderbufferEXT" },
    { offsetof(EXTFramebufferObject, glCheckFramebufferStatus), "glCheckFramebufferStatusEXT" },
    { offsetof(EXTFramebufferObject, glDeleteFramebuffers), "glDeleteFramebuffersEXT" },
    { offsetof(EXTFramebufferObject, glDeleteRenderbuffers), "glDeleteRenderbuffersEXT" },
    { offsetof(EXTFramebufferObject, glFramebufferRenderbuffer), "glFramebufferRenderbufferEXT" },
    { offsetof(EXTFramebufferObject, glFramebufferTexture1D), "glFramebufferTexture1DEXT" },
    { offsetof(EXTFramebufferObject, glFramebufferTexture2D), "glFramebufferTexture2DEXT" },
    { offsetof(EXTFramebufferObject, glFramebufferTexture3D), "glFramebufferTexture3DEXT" },
    { offsetof(EXTFramebufferObject, glGenFramebuffers), "glGenFramebuffersEXT" },
    { offsetof(EXTFramebufferObject, glGenRenderbuffers), "glGenRenderbuffersEXT" },
    { offsetof(EXTFramebufferObject, glGenerateMipmap), "glGenerateMipmapEXT" },
    { offsetof(EXTFramebufferObject, glGetFramebufferAttachmentParameteriv), "glGetFramebufferAttachmentParameterivEXT" },
    { offsetof(EXTFramebufferObject, glGetRenderbufferParameteriv), "glGetRenderbufferParameterivEXT" },
    { offsetof(EXTFramebufferObject, glIsFramebuffer), "glIsFramebufferEXT" },
    { offsetof(EXTFramebufferObject, glIsRenderbuffer), "glIsRenderbufferEXT" },
    { offsetof(EXTFramebufferObject, glRenderbufferStorage), "glRenderbufferStorageEXT" },
};

static const EntryOffset __EXTGeometrySHADER4EntryPoints[] = {
    { offsetof(EXTGeometrySHADER4, glProgramParameteri), "glProgramParameteriEXT" },
};

static const EntryOffset __EXTGPUProgramParametersEntryPoints[] = {
    { offsetof(EXTGPUProgramParameters, glProgramEnvParameters4fv), "glProgramEnvParameters4fvEXT" },
    { offsetof(EXTGPUProgramParameters, glProgramLocalParameters4fv), "glProgramLocalParameters4fvEXT" },
};

static const EntryOffset __EXTGPUSHADER4EntryPoints[] = {
    { offsetof(EXTGPUSHADER4, glBindFragDataLocation), "glBindFragDataLocationEXT" },
    { offsetof(EXTGPUSHADER4, glGetFragDataLocation), "glGetFragDataLocationEXT" },
    { offsetof(EXTGPUSHADER4, glGetUniformuiv), "glGetUniformuivEXT" },
    { offsetof(EXTGPUSHADER4, glGetVertexAttribIiv), "glGetVertexAttribIivEXT" },
    { offsetof(EXTGPUSHADER4, glGetVertexAttribIuiv), "glGetVertexAttribIuivEXT" },
    { offsetof(EXTGPUSHADER4, glUniform1ui), "glUniform1uiEXT" },
    { offsetof(EXTGPUSHADER4, glUniform1uiv), "glUniform1uivEXT" },
    { offsetof(EXTGPUSHADER4, glUniform2ui), "glUniform2uiEXT" },
    { offsetof(EXTGPUSHADER4, glUniform2uiv), "glUniform2uivEXT" },
    { offsetof(EXTGPUSHADER4, glUniform3ui), "glUniform3uiEXT" },
    { offsetof(EXTGPUSHADER4, glUniform3uiv), "glUniform3uivEXT" },
    { offsetof(EXTGPUSHADER4, glUniform4ui), "glUniform4uiEXT" },
    { offsetof(EXTGPUSHADER4, glUniform4uiv), "glUniform4uivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI1i), "glVertexAttribI1iEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI1iv), "glVertexAttribI1ivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI1ui), "glVertexAttribI1uiEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI1uiv), "glVertexAttribI1uivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI2i), "glVertexAttribI2iEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI2iv), "glVertexAttribI2ivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI2ui), "glVertexAttribI2uiEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI2uiv), "glVertexAttribI2uivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI3i), "glVertexAttribI3iEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI3iv), "glVertexAttribI3ivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI3ui), "glVertexAttribI3uiEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI3uiv), "glVertexAttribI3uivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4bv), "glVertexAttribI4bvEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4i), "glVertexAttribI4iEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4iv), "glVertexAttribI4ivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4sv), "glVertexAttribI4svEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4ubv), "glVertexAttribI4ubvEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4ui), "glVertexAttribI4uiEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4uiv), "glVertexAttribI4uivEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribI4usv), "glVertexAttribI4usvEXT" },
    { offsetof(EXTGPUSHADER4, glVertexAttribIPointer), "glVertexAttribIPointerEXT" },
};

static const EntryOffset __EXTHistogramEntryPoints[] = {
    { offsetof(EXTHistogram, glGetHistogram), "glGetHistogramEXT" },
    { offsetof(EXTHistogram, glGetHistogramParameterfv), "glGetHistogramParameterfvEXT" },
    { offsetof(EXTHistogram, glGetHistogramParameteriv), "glGetHistogramParameterivEXT" },
    { offsetof(EXTHistogram, glGetMinmax), "glGetMinmaxEXT" },
    { offsetof(EXTHistogram, glGetMinmaxParameterfv), "glGetMinmaxParameterfvEXT" },
    { offsetof(EXTHistogram, glGetMinmaxParameteriv), "glGetMinmaxParameterivEXT" },
    { offsetof(EXTHistogram, glHistogram), "glHistogramEXT" },
    { offsetof(EXTHistogram, glMinmax), "glMinmaxEXT" },
    { offsetof(EXTHistogram, glResetHistogram), "glResetHistogramEXT" },
    { offsetof(EXTHistogram, glResetMinmax), "glResetMinmaxEXT" },
};

static const EntryOffset __EXTIndexFuncEntryPoints[] = {
    { offsetof(EXTIndexFunc, glIndexFunc), "glIndexFuncEXT" },
};

static const EntryOffset __EXTIndexMaterialEntryPoints[] = {
    { offsetof(EXTIndexMaterial, glIndexMaterial), "glIndexMaterialEXT" },
};

static const EntryOffset __EXTLightTextureEntryPoints[] = {
    { offsetof(EXTLightTexture, glApplyTexture), "glApplyTextureEXT" },
    { offsetof(EXTLightTexture, glTextureLight), "glTextureLightEXT" },
    { offsetof(EXTLightTexture, glTextureMaterial), "glTextureMaterialEXT" },
};

static const EntryOffset __EXTMemoryObjectEntryPoints[] = {
    { offsetof(EXTMemoryObject, glBufferStorageMem), "glBufferStorageMemEXT" },
    { offsetof(EXTMemoryObject, glCreateMemoryObjects), "glCreateMemoryObjectsEXT" },
    { offsetof(EXTMemoryObject, glDeleteMemoryObjects), "glDeleteMemoryObjectsEXT" },
    { offsetof(EXTMemoryObject, glGetMemoryObjectParameteriv), "glGetMemoryObjectParameterivEXT" },
    { offsetof(EXTMemoryObject, glGetUnsignedBytei_v), "glGetUnsignedBytei_vEXT" },
    { offsetof(EXTMemoryObject, glGetUnsignedBytev), "glGetUnsignedBytevEXT" },
    { offsetof(EXTMemoryObject, glIsMemoryObject), "glIsMemoryObjectEXT" },
    { offsetof(EXTMemoryObject, glMemoryObjectParameteriv), "glMemoryObjectParameterivEXT" },
    { offsetof(EXTMemoryObject, glNamedBufferStorageMem), "glNamedBufferStorageMemEXT" },
    { offsetof(EXTMemoryObject, glTexStorageMem1D), "glTexStorageMem1DEXT" },
    { offsetof(EXTMemoryObject, glTexStorageMem2D), "glTexStorageMem2DEXT" },
    { offsetof(EXTMemoryObject, glTexStorageMem2DMultisample), "glTexStorageMem2DMultisampleEXT" },
    { offsetof(EXTMemoryObject, glTexStorageMem3D), "glTexStorageMem3DEXT" },
    { offsetof(EXTMemoryObject, glTexStorageMem3DMultisample), "glTexStorageMem3DMultisampleEXT" },
    { offsetof(EXTMemoryObject, glTextureStorageMem1D), "glTextureStorageMem1DEXT" },
    { offsetof(EXTMemoryObject, glTextureStorageMem2D), "glTextureStorageMem2DEXT" },
    { offsetof(EXTMemoryObject, glTextureStorageMem2DMultisample), "glTextureStorageMem2DMultisampleEXT" },
    { offsetof(EXTMemoryObject, glTextureStorageMem3D), "glTextureStorageMem3DEXT" },
    { offsetof(EXTMemoryObject, glTextureStorageMem3DMultisample), "glTextureStorageMem3DMultisampleEXT" },
};

static const EntryOffset __EXTMemoryObjectFdEntryPoints[] = {
    { offsetof(EXTMemoryObjectFd, glImportMemoryFd), "glImportMemoryFdEXT" },
};

static const EntryOffset __EXTMemoryObjectWIN32EntryPoints[] = {
    { offsetof(EXTMemoryObjectWIN32, glImportMemoryWin32Handle), "glImportMemoryWin32HandleEXT" },
    { offsetof(EXTMemoryObjectWIN32, glImportMemoryWin32Name), "glImportMemoryWin32NameEXT" },
};

static const EntryOffset __EXTMultiDrawArraysEntryPoints[] = {
    { offsetof(EXTMultiDrawArrays, glMultiDrawArrays), "glMultiDrawArraysEXT" },
    { offsetof(EXTMultiDrawArrays, glMultiDrawElements), "glMultiDrawElementsEXT" },
};

static const EntryOffset __EXTMultisampleEntryPoints[] = {
    { offsetof(EXTMultisample, glSampleMask), "glSampleMaskEXT" },
    { offsetof(EXTMultisample, glSamplePattern), "glSamplePatternEXT" },
};

static const EntryOffset __EXTPalettedTextureEntryPoints[] = {
    { offsetof(EXTPalettedTexture, glColorTable), "glColorTableEXT" },
    { offsetof(EXTPalettedTexture, glGetColorTable), "glGetColorTableEXT" },
    { offsetof(EXTPalettedTexture, glGetColorTableParameterfv), "glGetColorTableParameterfvEXT" },
    { offsetof(EXTPalettedTexture, glGetColorTableParameteriv), "glGetColorTableParameterivEXT" },
};

static const EntryOffset __EXTPixelTransformEntryPoints[] = {
    { offsetof(EXTPixelTransform, glGetPixelTransformParameterfv), "glGetPixelTransformParameterfvEXT" },
    { offsetof(EXTPixelTransform, glGetPixelTransformParameteriv), "glGetPixelTransformParameterivEXT" },
    { offsetof(EXTPixelTransform, glPixelTransformParameterf), "glPixelTransformParameterfEXT" },
    { offsetof(EXTPixelTransform, glPixelTransformParameterfv), "glPixelTransformParameterfvEXT" },
    { offsetof(EXTPixelTransform, glPixelTransformParameteri), "glPixelTransformParameteriEXT" },
    { offsetof(EXTPixelTransform, glPixelTransformParameteriv), "glPixelTransformParameterivEXT" },
};

static const EntryOffset __EXTPointParametersEntryPoints[] = {
    { offsetof(EXTPointParameters, glPointParameterf), "glPointParameterfEXT" },
    { offsetof(EXTPointParameters, glPointParameterfv), "glPointParameterfvEXT" },
};

static const EntryOffset __EXTPolygonOffsetEntryPoints[] = {
    { offsetof(EXTPolygonOffset, glPolygonOffset), "glPolygonOffsetEXT" },
};

static const EntryOffset __EXTPolygonOffsetClampEntryPoints[] = {
    { offsetof(EXTPolygonOffsetClamp, glPolygonOffsetClamp), "glPolygonOffsetClampEXT" },
};

static const EntryOffset __EXTProvokingVertexEntryPoints[] = {
    { offsetof(EXTProvokingVertex, glProvokingVertex), "glProvokingVertexEXT" },
};

static const EntryOffset __EXTRasterMultisampleEntryPoints[] = {
    { offsetof(EXTRasterMultisample, glRasterSamples), "glRasterSamplesEXT" },
};

static const EntryOffset __EXTSecondaryColorEntryPoints[] = {
    { offsetof(EXTSecondaryColor, glSecondaryColor3b), "glSecondaryColor3bEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3bv), "glSecondaryColor3bvEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3d), "glSecondaryColor3dEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3dv), "glSecondaryColor3dvEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3f), "glSecondaryColor3fEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3fv), "glSecondaryColor3fvEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3i), "glSecondaryColor3iEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3iv), "glSecondaryColor3ivEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3s), "glSecondaryColor3sEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3sv), "glSecondaryColor3svEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3ub), "glSecondaryColor3ubEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3ubv), "glSecondaryColor3ubvEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3ui), "glSecondaryColor3uiEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3uiv), "glSecondaryColor3uivEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3us), "glSecondaryColor3usEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColor3usv), "glSecondaryColor3usvEXT" },
    { offsetof(EXTSecondaryColor, glSecondaryColorPointer), "glSecondaryColorPointerEXT" },
};

static const EntryOffset __EXTSemaphoreEntryPoints[] = {
    { offsetof(EXTSemaphore, glDeleteSemaphores), "glDeleteSemaphoresEXT" },
    { offsetof(EXTSemaphore, glGenSemaphores), "glGenSemaphoresEXT" },
    { offsetof(EXTSemaphore, glGetSemaphoreParameterui64v), "glGetSemaphoreParameterui64vEXT" },
    { offsetof(EXTSemaphore, glIsSemaphore), "glIsSemaphoreEXT" },
    { offsetof(EXTSemaphore, glSemaphoreParameterui64v), "glSemaphoreParameterui64vEXT" },
    { offsetof(EXTSemaphore, glSignalSemaphore), "glSignalSemaphoreEXT" },
    { offsetof(EXTSemaphore, glWaitSemaphore), "glWaitSemaphoreEXT" },
};

static const EntryOffset __EXTSemaphoreFdEntryPoints[] = {
    { offsetof(EXTSemaphoreFd, glImportSemaphoreFd), "glImportSemaphoreFdEXT" },
};

static const EntryOffset __EXTSemaphoreWIN32EntryPoints[] = {
    { offsetof(EXTSemaphoreWIN32, glImportSemaphoreWin32Handle), "glImportSemaphoreWin32HandleEXT" },
    { offsetof(EXTSemaphoreWIN32, glImportSemaphoreWin32Name), "glImportSemaphoreWin32NameEXT" },
};

static const EntryOffset __EXTSeparateShaderObjectsEntryPoints[] = {
    { offsetof(EXTSeparateShaderObjects, glActiveProgram), "glActiveProgramEXT" },
    { offsetof(EXTSeparateShaderObjects, glCreateShaderProgram), "glCreateShaderProgramEXT" },
    { offsetof(EXTSeparateShaderObjects, glUseShaderProgram), "glUseShaderProgramEXT" },
};

static const EntryOffset __EXTShaderFramebufferFetchNonCoherentEntryPoints[] = {
    { offsetof(EXTShaderFramebufferFetchNonCoherent, glFramebufferFetchBarrier), "glFramebufferFetchBarrierEXT" },
};

static const EntryOffset __EXTShaderImageLoadStoreEntryPoints[] = {
    { offsetof(EXTShaderImageLoadStore, glBindImageTexture), "glBindImageTextureEXT" },
    { offsetof(EXTShaderImageLoadStore, glMemoryBarrier), "glMemoryBarrierEXT" },
};

static const EntryOffset __EXTStencilClearTagEntryPoints[] = {
    { offsetof(EXTStencilClearTag, glStencilClearTag), "glStencilClearTagEXT" },
};

static const EntryOffset __EXTStencilTwoSideEntryPoints[] = {
    { offsetof(EXTStencilTwoSide, glActiveStencilFace), "glActiveStencilFaceEXT" },
};

static const EntryOffset __EXTSubtextureEntryPoints[] = {
    { offsetof(EXTSubtexture, glTexSubImage1D), "glTexSubImage1DEXT" },
    { offsetof(EXTSubtexture, glTexSubImage2D), "glTexSubImage2DEXT" },
};

static const EntryOffset __EXTTEXTURE3DEntryPoints[] = {
    { offsetof(EXTTEXTURE3D, glTexImage3D), "glTexImage3DEXT" },
    { offsetof(EXTTEXTURE3D, glTexSubImage3D), "glTexSubImage3DEXT" },
};

static const EntryOffset __EXTTextureArrayEntryPoints[] = {
    { offsetof(EXTTextureArray, glFramebufferTextureLayer), "glFramebufferTextureLayerEXT" },
};

static const EntryOffset __EXTTextureBufferObjectEntryPoints[] = {
    { offsetof(EXTTextureBufferObject, glTexBuffer), "glTexBufferEXT" },
};

static const EntryOffset __EXTTextureIntegerEntryPoints[] = {
    { offsetof(EXTTextureInteger, glClearColorIi), "glClearColorIiEXT" },
    { offsetof(EXTTextureInteger, glClearColorIui), "glClearColorIuiEXT" },
    { offsetof(EXTTextureInteger, glGetTexParameterIiv), "glGetTexParameterIivEXT" },
    { offsetof(EXTTextureInteger, glGetTexParameterIuiv), "glGetTexParameterIuivEXT" },
    { offsetof(EXTTextureInteger, glTexParameterIiv), "glTexParameterIivEXT" },
    { offsetof(EXTTextureInteger, glTexParameterIuiv), "glTexParameterIuivEXT" },
};

static const EntryOffset __EXTTextureObjectEntryPoints[] = {
    { offsetof(EXTTextureObject, glAreTexturesResident), "glAreTexturesResidentEXT" },
    { offsetof(EXTTextureObject, glBindTexture), "glBindTextureEXT" },
    { offsetof(EXTTextureObject, glDeleteTextures), "glDeleteTexturesEXT" },
    { offsetof(EXTTextureObject, glGenTextures), "glGenTexturesEXT" },
    { offsetof(EXTTextureObject, glIsTexture), "glIsTextureEXT" },
    { offsetof(EXTTextureObject, glPrioritizeTextures), "glPrioritizeTexturesEXT" },
};

static const EntryOffset __EXTTexturePerturbNormalEntryPoints[] = {
    { offsetof(EXTTexturePerturbNormal, glTextureNormal), "glTextureNormalEXT" },
};

static const EntryOffset __EXTTextureStorageEntryPoints[] = {
    { offsetof(EXTTextureStorage, glTexStorage1D), "glTexStorage1DEXT" },
    { offsetof(EXTTextureStorage, glTexStorage2D), "glTexStorage2DEXT" },
    { offsetof(EXTTextureStorage, glTexStorage3D), "glTexStorage3DEXT" },
};

static const EntryOffset __EXTTimerQueryEntryPoints[] = {
    { offsetof(EXTTimerQuery, glGetQueryObjecti64v), "glGetQueryObjecti64vEXT" },
    { offsetof(EXTTimerQuery, glGetQueryObjectui64v), "glGetQueryObjectui64vEXT" },
};

static const EntryOffset __EXTTransformFeedbackEntryPoints[] = {
    { offsetof(EXTTransformFeedback, glBeginTransformFeedback), "glBeginTransformFeedbackEXT" },
    { offsetof(EXTTransformFeedback, glBindBufferBase), "glBindBufferBaseEXT" },
    { offsetof(EXTTransformFeedback, glBindBufferOffset), "glBindBufferOffsetEXT" },
    { offsetof(EXTTransformFeedback, glBindBufferRange), "glBindBufferRangeEXT" },
    { offsetof(EXTTransformFeedback, glEndTransformFeedback), "glEndTransformFeedbackEXT" },
    { offsetof(EXTTransformFeedback, glGetTransformFeedbackVarying), "glGetTransformFeedbackVaryingEXT" },
    { offsetof(EXTTransformFeedback, glTransformFeedbackVaryings), "glTransformFeedbackVaryingsEXT" },
};

static const EntryOffset __EXTVertexArrayEntryPoints[] = {
    { offsetof(EXTVertexArray, glArrayElement), "glArrayElementEXT" },
    { offsetof(EXTVertexArray, glColorPointer), "glColorPointerEXT" },
    { offsetof(EXTVertexArray, glDrawArrays), "glDrawArraysEXT" },
    { offsetof(EXTVertexArray, glEdgeFlagPointer), "glEdgeFlagPointerEXT" },
    { offsetof(EXTVertexArray, glGetPointerv), "glGetPointervEXT" },
    { offsetof(EXTVertexArray, glIndexPointer), "glIndexPointerEXT" },
    { offsetof(EXTVertexArray, glNormalPointer), "glNormalPointerEXT" },
    { offsetof(EXTVertexArray, glTexCoordPointer), "glTexCoordPointerEXT" },
    { offsetof(EXTVertexArray, glVertexPointer), "glVertexPointerEXT" },
};

static const EntryOffset __EXTVertexAttrib64BITEntryPoints[] = {
    { offsetof(EXTVertexAttrib64BIT, glGetVertexAttribLdv), "glGetVertexAttribLdvEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL1d), "glVertexAttribL1dEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL1dv), "glVertexAttribL1dvEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL2d), "glVertexAttribL2dEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL2dv), "glVertexAttribL2dvEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL3d), "glVertexAttribL3dEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL3dv), "glVertexAttribL3dvEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL4d), "glVertexAttribL4dEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribL4dv), "glVertexAttribL4dvEXT" },
    { offsetof(EXTVertexAttrib64BIT, glVertexAttribLPointer), "glVertexAttribLPointerEXT" },
};

static const EntryOffset __EXTVertexShaderEntryPoints[] = {
    { offsetof(EXTVertexShader, glBeginVertexShader), "glBeginVertexShaderEXT" },
    { offsetof(EXTVertexShader, glBindLightParameter), "glBindLightParameterEXT" },
    { offsetof(EXTVertexShader, glBindMaterialParameter), "glBindMaterialParameterEXT" },
    { offsetof(EXTVertexShader, glBindParameter), "glBindParameterEXT" },
    { offsetof(EXTVertexShader, glBindTexGenParameter), "glBindTexGenParameterEXT" },
    { offsetof(EXTVertexShader, glBindTextureUnitParameter), "glBindTextureUnitParameterEXT" },
    { offsetof(EXTVertexShader, glBindVertexShader), "glBindVertexShaderEXT" },
    { offsetof(EXTVertexShader, glDeleteVertexShader), "glDeleteVertexShaderEXT" },
    { offsetof(EXTVertexShader, glDisableVariantClientState), "glDisableVariantClientStateEXT" },
    { offsetof(EXTVertexShader, glEnableVariantClientState), "glEnableVariantClientStateEXT" },
    { offsetof(EXTVertexShader, glEndVertexShader), "glEndVertexShaderEXT" },
    { offsetof(EXTVertexShader, glExtractComponent), "glExtractComponentEXT" },
    { offsetof(EXTVertexShader, glGenSymbols), "glGenSymbolsEXT" },
    { offsetof(EXTVertexShader, glGenVertexShaders), "glGenVertexShadersEXT" },
    { offsetof(EXTVertexShader, glGetInvariantBooleanv), "glGetInvariantBooleanvEXT" },
    { offsetof(EXTVertexShader, glGetInvariantFloatv), "glGetInvariantFloatvEXT" },
    { offsetof(EXTVertexShader, glGetInvariantIntegerv), "glGetInvariantIntegervEXT" },
    { offsetof(EXTVertexShader, glGetLocalConstantBooleanv), "glGetLocalConstantBooleanvEXT" },
    { offsetof(EXTVertexShader, glGetLocalConstantFloatv), "glGetLocalConstantFloatvEXT" },
    { offsetof(EXTVertexShader, glGetLocalConstantIntegerv), "glGetLocalConstantIntegervEXT" },
    { offsetof(EXTVertexShader, glGetVariantBooleanv), "glGetVariantBooleanvEXT" },
    { offsetof(EXTVertexShader, glGetVariantFloatv), "glGetVariantFloatvEXT" },
    { offsetof(EXTVertexShader, glGetVariantIntegerv), "glGetVariantIntegervEXT" },
    { offsetof(EXTVertexShader, glGetVariantPointerv), "glGetVariantPointervEXT" },
    { offsetof(EXTVertexShader, glInsertComponent), "glInsertComponentEXT" },
    { offsetof(EXTVertexShader, glIsVariantEnabled), "glIsVariantEnabledEXT" },
    { offsetof(EXTVertexShader, glSetInvariant), "glSetInvariantEXT" },
    { offsetof(EXTVertexShader, glSetLocalConstant), "glSetLocalConstantEXT" },
    { offsetof(EXTVertexShader, glShaderOp1), "glShaderOp1EXT" },
    { offsetof(EXTVertexShader, glShaderOp2), "glShaderOp2EXT" },
    { offsetof(EXTVertexShader, glShaderOp3), "glShaderOp3EXT" },
    { offsetof(EXTVertexShader, glSwizzle), "glSwizzleEXT" },
    { offsetof(EXTVertexShader, glVariantPointer), "glVariantPointerEXT" },
    { offsetof(EXTVertexShader, glVariantbv), "glVariantbvEXT" },
    { offsetof(EXTVertexShader, glVariantdv), "glVariantdvEXT" },
    { offsetof(EXTVertexShader, glVariantfv), "glVariantfvEXT" },
    { offsetof(EXTVertexShader, glVariantiv), "glVariantivEXT" },
    { offsetof(EXTVertexShader, glVariantsv), "glVariantsvEXT" },
    { offsetof(EXTVertexShader, glVariantubv), "glVariantubvEXT" },
    { offsetof(EXTVertexShader, glVariantuiv), "glVariantuivEXT" },
    { offsetof(EXTVertexShader, glVariantusv), "glVariantusvEXT" },
    { offsetof(EXTVertexShader, glWriteMask), "glWriteMaskEXT" },
};

static const EntryOffset __EXTVertexWeightingEntryPoints[] = {
    { offsetof(EXTVertexWeighting, glVertexWeightPointer), "glVertexWeightPointerEXT" },
    { offsetof(EXTVertexWeighting, glVertexWeightf), "glVertexWeightfEXT" },
    { offsetof(EXTVertexWeighting, glVertexWeightfv), "glVertexWeightfvEXT" },
};

static const EntryOffset __EXTWIN32KeyedMutexEntryPoints[] = {
    { offsetof(EXTWIN32KeyedMutex, glAcquireKeyedMutexWin32), "glAcquireKeyedMutexWin32EXT" },
    { offsetof(EXTWIN32KeyedMutex, glReleaseKeyedMutexWin32), "glReleaseKeyedMutexWin32EXT" },
};

static const EntryOffset __EXTWindowRectanglesEntryPoints[] = {
    { offsetof(EXTWindowRectangles, glWindowRectangles), "glWindowRectanglesEXT" },
};

static const EntryOffset __EXTX11SyncObjectEntryPoints[] = {
    { offsetof(EXTX11SyncObject, glImportSync), "glImportSyncEXT" },
};


} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// EXTEglImageStorage Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTEglImageStorage::EXTEglImageStorage()
{
    std::for_each_n(__EXTEglImageStorageEntryPoints,
                    std::size(__EXTEglImageStorageEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTEglImageStorage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_EGL_image_storage");
}

void EXTEglImageStorage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTEglImageStorageEntryPoints,
                    std::size(__EXTEglImageStorageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTBindableUniform Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTBindableUniform::EXTBindableUniform()
{
    std::for_each_n(__EXTBindableUniformEntryPoints,
                    std::size(__EXTBindableUniformEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTBindableUniform::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_bindable_uniform");
}

void EXTBindableUniform::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTBindableUniformEntryPoints,
                    std::size(__EXTBindableUniformEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendColor Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTBlendColor::EXTBlendColor()
{
    std::for_each_n(__EXTBlendColorEntryPoints,
                    std::size(__EXTBlendColorEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTBlendColor::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_blend_color");
}

void EXTBlendColor::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTBlendColorEntryPoints,
                    std::size(__EXTBlendColorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendEquationSeparate Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTBlendEquationSeparate::EXTBlendEquationSeparate()
{
    std::for_each_n(__EXTBlendEquationSeparateEntryPoints,
                    std::size(__EXTBlendEquationSeparateEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTBlendEquationSeparate::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_blend_equation_separate");
}

void EXTBlendEquationSeparate::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTBlendEquationSeparateEntryPoints,
                    std::size(__EXTBlendEquationSeparateEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendFuncSeparate Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTBlendFuncSeparate::EXTBlendFuncSeparate()
{
    std::for_each_n(__EXTBlendFuncSeparateEntryPoints,
                    std::size(__EXTBlendFuncSeparateEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTBlendFuncSeparate::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_blend_func_separate");
}

void EXTBlendFuncSeparate::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTBlendFuncSeparateEntryPoints,
                    std::size(__EXTBlendFuncSeparateEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendMinmax Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTBlendMinmax::EXTBlendMinmax()
{
    std::for_each_n(__EXTBlendMinmaxEntryPoints,
                    std::size(__EXTBlendMinmaxEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTBlendMinmax::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_blend_minmax");
}

void EXTBlendMinmax::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTBlendMinmaxEntryPoints,
                    std::size(__EXTBlendMinmaxEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTColorSubtable Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTColorSubtable::EXTColorSubtable()
{
    std::for_each_n(__EXTColorSubtableEntryPoints,
                    std::size(__EXTColorSubtableEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTColorSubtable::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_color_subtable");
}

void EXTColorSubtable::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTColorSubtableEntryPoints,
                    std::size(__EXTColorSubtableEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTCompiledVertexArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTCompiledVertexArray::EXTCompiledVertexArray()
{
    std::for_each_n(__EXTCompiledVertexArrayEntryPoints,
                    std::size(__EXTCompiledVertexArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTCompiledVertexArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_compiled_vertex_array");
}

void EXTCompiledVertexArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTCompiledVertexArrayEntryPoints,
                    std::size(__EXTCompiledVertexArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTConvolution Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTConvolution::EXTConvolution()
{
    std::for_each_n(__EXTConvolutionEntryPoints,
                    std::size(__EXTConvolutionEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTConvolution::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_convolution");
}

void EXTConvolution::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTConvolutionEntryPoints,
                    std::size(__EXTConvolutionEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTCoordinateFrame Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTCoordinateFrame::EXTCoordinateFrame()
{
    std::for_each_n(__EXTCoordinateFrameEntryPoints,
                    std::size(__EXTCoordinateFrameEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTCoordinateFrame::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_coordinate_frame");
}

void EXTCoordinateFrame::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTCoordinateFrameEntryPoints,
                    std::size(__EXTCoordinateFrameEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTCopyTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTCopyTexture::EXTCopyTexture()
{
    std::for_each_n(__EXTCopyTextureEntryPoints,
                    std::size(__EXTCopyTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTCopyTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_copy_texture");
}

void EXTCopyTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTCopyTextureEntryPoints,
                    std::size(__EXTCopyTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTCullVertex Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTCullVertex::EXTCullVertex()
{
    std::for_each_n(__EXTCullVertexEntryPoints,
                    std::size(__EXTCullVertexEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTCullVertex::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_cull_vertex");
}

void EXTCullVertex::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTCullVertexEntryPoints,
                    std::size(__EXTCullVertexEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDebugLabel Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDebugLabel::EXTDebugLabel()
{
    std::for_each_n(__EXTDebugLabelEntryPoints,
                    std::size(__EXTDebugLabelEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDebugLabel::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_debug_label");
}

void EXTDebugLabel::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDebugLabelEntryPoints,
                    std::size(__EXTDebugLabelEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDebugMarker Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDebugMarker::EXTDebugMarker()
{
    std::for_each_n(__EXTDebugMarkerEntryPoints,
                    std::size(__EXTDebugMarkerEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDebugMarker::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_debug_marker");
}

void EXTDebugMarker::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDebugMarkerEntryPoints,
                    std::size(__EXTDebugMarkerEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDepthBoundsTest Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDepthBoundsTest::EXTDepthBoundsTest()
{
    std::for_each_n(__EXTDepthBoundsTestEntryPoints,
                    std::size(__EXTDepthBoundsTestEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDepthBoundsTest::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_depth_bounds_test");
}

void EXTDepthBoundsTest::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDepthBoundsTestEntryPoints,
                    std::size(__EXTDepthBoundsTestEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDirectStateAccess Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDirectStateAccess::EXTDirectStateAccess()
{
    std::for_each_n(__EXTDirectStateAccessEntryPoints,
                    std::size(__EXTDirectStateAccessEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDirectStateAccess::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_direct_state_access");
}

void EXTDirectStateAccess::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDirectStateAccessEntryPoints,
                    std::size(__EXTDirectStateAccessEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawBUFFERS2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDrawBUFFERS2::EXTDrawBUFFERS2()
{
    std::for_each_n(__EXTDrawBUFFERS2EntryPoints,
                    std::size(__EXTDrawBUFFERS2EntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDrawBUFFERS2::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_draw_buffers2");
}

void EXTDrawBUFFERS2::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDrawBUFFERS2EntryPoints,
                    std::size(__EXTDrawBUFFERS2EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawInstanced Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDrawInstanced::EXTDrawInstanced()
{
    std::for_each_n(__EXTDrawInstancedEntryPoints,
                    std::size(__EXTDrawInstancedEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDrawInstanced::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_draw_instanced");
}

void EXTDrawInstanced::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDrawInstancedEntryPoints,
                    std::size(__EXTDrawInstancedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawRangeElements Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDrawRangeElements::EXTDrawRangeElements()
{
    std::for_each_n(__EXTDrawRangeElementsEntryPoints,
                    std::size(__EXTDrawRangeElementsEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTDrawRangeElements::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_draw_range_elements");
}

void EXTDrawRangeElements::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDrawRangeElementsEntryPoints,
                    std::size(__EXTDrawRangeElementsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTExternalBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTExternalBuffer::EXTExternalBuffer()
{
    std::for_each_n(__EXTExternalBufferEntryPoints,
                    std::size(__EXTExternalBufferEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTExternalBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_external_buffer");
}

void EXTExternalBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTExternalBufferEntryPoints,
                    std::size(__EXTExternalBufferEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTFogCoord Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTFogCoord::EXTFogCoord()
{
    std::for_each_n(__EXTFogCoordEntryPoints,
                    std::size(__EXTFogCoordEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTFogCoord::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_fog_coord");
}

void EXTFogCoord::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTFogCoordEntryPoints,
                    std::size(__EXTFogCoordEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferBlit Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTFramebufferBlit::EXTFramebufferBlit()
{
    std::for_each_n(__EXTFramebufferBlitEntryPoints,
                    std::size(__EXTFramebufferBlitEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTFramebufferBlit::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_framebuffer_blit");
}

void EXTFramebufferBlit::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTFramebufferBlitEntryPoints,
                    std::size(__EXTFramebufferBlitEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferBlitLayers Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTFramebufferBlitLayers::EXTFramebufferBlitLayers()
{
    std::for_each_n(__EXTFramebufferBlitLayersEntryPoints,
                    std::size(__EXTFramebufferBlitLayersEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTFramebufferBlitLayers::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_framebuffer_blit_layers");
}

void EXTFramebufferBlitLayers::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTFramebufferBlitLayersEntryPoints,
                    std::size(__EXTFramebufferBlitLayersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTFramebufferMultisample::EXTFramebufferMultisample()
{
    std::for_each_n(__EXTFramebufferMultisampleEntryPoints,
                    std::size(__EXTFramebufferMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTFramebufferMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_framebuffer_multisample");
}

void EXTFramebufferMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTFramebufferMultisampleEntryPoints,
                    std::size(__EXTFramebufferMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTFramebufferObject::EXTFramebufferObject()
{
    std::for_each_n(__EXTFramebufferObjectEntryPoints,
                    std::size(__EXTFramebufferObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTFramebufferObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_framebuffer_object");
}

void EXTFramebufferObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTFramebufferObjectEntryPoints,
                    std::size(__EXTFramebufferObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTGeometrySHADER4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTGeometrySHADER4::EXTGeometrySHADER4()
{
    std::for_each_n(__EXTGeometrySHADER4EntryPoints,
                    std::size(__EXTGeometrySHADER4EntryPoints),
                    ClearEntryPoint(this));
}

bool EXTGeometrySHADER4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_geometry_shader4");
}

void EXTGeometrySHADER4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTGeometrySHADER4EntryPoints,
                    std::size(__EXTGeometrySHADER4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTGPUProgramParameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTGPUProgramParameters::EXTGPUProgramParameters()
{
    std::for_each_n(__EXTGPUProgramParametersEntryPoints,
                    std::size(__EXTGPUProgramParametersEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTGPUProgramParameters::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_gpu_program_parameters");
}

void EXTGPUProgramParameters::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTGPUProgramParametersEntryPoints,
                    std::size(__EXTGPUProgramParametersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTGPUSHADER4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTGPUSHADER4::EXTGPUSHADER4()
{
    std::for_each_n(__EXTGPUSHADER4EntryPoints,
                    std::size(__EXTGPUSHADER4EntryPoints),
                    ClearEntryPoint(this));
}

bool EXTGPUSHADER4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_gpu_shader4");
}

void EXTGPUSHADER4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTGPUSHADER4EntryPoints,
                    std::size(__EXTGPUSHADER4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTHistogram Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTHistogram::EXTHistogram()
{
    std::for_each_n(__EXTHistogramEntryPoints,
                    std::size(__EXTHistogramEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTHistogram::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_histogram");
}

void EXTHistogram::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTHistogramEntryPoints,
                    std::size(__EXTHistogramEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTIndexFunc Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTIndexFunc::EXTIndexFunc()
{
    std::for_each_n(__EXTIndexFuncEntryPoints,
                    std::size(__EXTIndexFuncEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTIndexFunc::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_index_func");
}

void EXTIndexFunc::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTIndexFuncEntryPoints,
                    std::size(__EXTIndexFuncEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTIndexMaterial Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTIndexMaterial::EXTIndexMaterial()
{
    std::for_each_n(__EXTIndexMaterialEntryPoints,
                    std::size(__EXTIndexMaterialEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTIndexMaterial::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_index_material");
}

void EXTIndexMaterial::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTIndexMaterialEntryPoints,
                    std::size(__EXTIndexMaterialEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTLightTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTLightTexture::EXTLightTexture()
{
    std::for_each_n(__EXTLightTextureEntryPoints,
                    std::size(__EXTLightTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTLightTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_light_texture");
}

void EXTLightTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTLightTextureEntryPoints,
                    std::size(__EXTLightTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMemoryObject::EXTMemoryObject()
{
    std::for_each_n(__EXTMemoryObjectEntryPoints,
                    std::size(__EXTMemoryObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTMemoryObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_memory_object");
}

void EXTMemoryObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMemoryObjectEntryPoints,
                    std::size(__EXTMemoryObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObjectFd Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMemoryObjectFd::EXTMemoryObjectFd()
{
    std::for_each_n(__EXTMemoryObjectFdEntryPoints,
                    std::size(__EXTMemoryObjectFdEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTMemoryObjectFd::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_memory_object_fd");
}

void EXTMemoryObjectFd::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMemoryObjectFdEntryPoints,
                    std::size(__EXTMemoryObjectFdEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObjectWIN32 Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMemoryObjectWIN32::EXTMemoryObjectWIN32()
{
    std::for_each_n(__EXTMemoryObjectWIN32EntryPoints,
                    std::size(__EXTMemoryObjectWIN32EntryPoints),
                    ClearEntryPoint(this));
}

bool EXTMemoryObjectWIN32::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_memory_object_win32");
}

void EXTMemoryObjectWIN32::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMemoryObjectWIN32EntryPoints,
                    std::size(__EXTMemoryObjectWIN32EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMultiDrawArrays Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMultiDrawArrays::EXTMultiDrawArrays()
{
    std::for_each_n(__EXTMultiDrawArraysEntryPoints,
                    std::size(__EXTMultiDrawArraysEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTMultiDrawArrays::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_multi_draw_arrays");
}

void EXTMultiDrawArrays::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMultiDrawArraysEntryPoints,
                    std::size(__EXTMultiDrawArraysEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMultisample::EXTMultisample()
{
    std::for_each_n(__EXTMultisampleEntryPoints,
                    std::size(__EXTMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_multisample");
}

void EXTMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMultisampleEntryPoints,
                    std::size(__EXTMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPalettedTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPalettedTexture::EXTPalettedTexture()
{
    std::for_each_n(__EXTPalettedTextureEntryPoints,
                    std::size(__EXTPalettedTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTPalettedTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_paletted_texture");
}

void EXTPalettedTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPalettedTextureEntryPoints,
                    std::size(__EXTPalettedTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPixelTransform Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPixelTransform::EXTPixelTransform()
{
    std::for_each_n(__EXTPixelTransformEntryPoints,
                    std::size(__EXTPixelTransformEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTPixelTransform::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_pixel_transform");
}

void EXTPixelTransform::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPixelTransformEntryPoints,
                    std::size(__EXTPixelTransformEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPointParameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPointParameters::EXTPointParameters()
{
    std::for_each_n(__EXTPointParametersEntryPoints,
                    std::size(__EXTPointParametersEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTPointParameters::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_point_parameters");
}

void EXTPointParameters::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPointParametersEntryPoints,
                    std::size(__EXTPointParametersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPolygonOffset Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPolygonOffset::EXTPolygonOffset()
{
    std::for_each_n(__EXTPolygonOffsetEntryPoints,
                    std::size(__EXTPolygonOffsetEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTPolygonOffset::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_polygon_offset");
}

void EXTPolygonOffset::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPolygonOffsetEntryPoints,
                    std::size(__EXTPolygonOffsetEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPolygonOffsetClamp Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPolygonOffsetClamp::EXTPolygonOffsetClamp()
{
    std::for_each_n(__EXTPolygonOffsetClampEntryPoints,
                    std::size(__EXTPolygonOffsetClampEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTPolygonOffsetClamp::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_polygon_offset_clamp");
}

void EXTPolygonOffsetClamp::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPolygonOffsetClampEntryPoints,
                    std::size(__EXTPolygonOffsetClampEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTProvokingVertex Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTProvokingVertex::EXTProvokingVertex()
{
    std::for_each_n(__EXTProvokingVertexEntryPoints,
                    std::size(__EXTProvokingVertexEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTProvokingVertex::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_provoking_vertex");
}

void EXTProvokingVertex::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTProvokingVertexEntryPoints,
                    std::size(__EXTProvokingVertexEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTRasterMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTRasterMultisample::EXTRasterMultisample()
{
    std::for_each_n(__EXTRasterMultisampleEntryPoints,
                    std::size(__EXTRasterMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTRasterMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_raster_multisample");
}

void EXTRasterMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTRasterMultisampleEntryPoints,
                    std::size(__EXTRasterMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSecondaryColor Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSecondaryColor::EXTSecondaryColor()
{
    std::for_each_n(__EXTSecondaryColorEntryPoints,
                    std::size(__EXTSecondaryColorEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSecondaryColor::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_secondary_color");
}

void EXTSecondaryColor::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSecondaryColorEntryPoints,
                    std::size(__EXTSecondaryColorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphore Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSemaphore::EXTSemaphore()
{
    std::for_each_n(__EXTSemaphoreEntryPoints,
                    std::size(__EXTSemaphoreEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSemaphore::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_semaphore");
}

void EXTSemaphore::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSemaphoreEntryPoints,
                    std::size(__EXTSemaphoreEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphoreFd Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSemaphoreFd::EXTSemaphoreFd()
{
    std::for_each_n(__EXTSemaphoreFdEntryPoints,
                    std::size(__EXTSemaphoreFdEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSemaphoreFd::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_semaphore_fd");
}

void EXTSemaphoreFd::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSemaphoreFdEntryPoints,
                    std::size(__EXTSemaphoreFdEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphoreWIN32 Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSemaphoreWIN32::EXTSemaphoreWIN32()
{
    std::for_each_n(__EXTSemaphoreWIN32EntryPoints,
                    std::size(__EXTSemaphoreWIN32EntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSemaphoreWIN32::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_semaphore_win32");
}

void EXTSemaphoreWIN32::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSemaphoreWIN32EntryPoints,
                    std::size(__EXTSemaphoreWIN32EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSeparateShaderObjects Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSeparateShaderObjects::EXTSeparateShaderObjects()
{
    std::for_each_n(__EXTSeparateShaderObjectsEntryPoints,
                    std::size(__EXTSeparateShaderObjectsEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSeparateShaderObjects::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_separate_shader_objects");
}

void EXTSeparateShaderObjects::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSeparateShaderObjectsEntryPoints,
                    std::size(__EXTSeparateShaderObjectsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTShaderFramebufferFetchNonCoherent Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTShaderFramebufferFetchNonCoherent::EXTShaderFramebufferFetchNonCoherent()
{
    std::for_each_n(__EXTShaderFramebufferFetchNonCoherentEntryPoints,
                    std::size(__EXTShaderFramebufferFetchNonCoherentEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTShaderFramebufferFetchNonCoherent::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_shader_framebuffer_fetch_non_coherent");
}

void EXTShaderFramebufferFetchNonCoherent::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTShaderFramebufferFetchNonCoherentEntryPoints,
                    std::size(__EXTShaderFramebufferFetchNonCoherentEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTShaderImageLoadStore Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTShaderImageLoadStore::EXTShaderImageLoadStore()
{
    std::for_each_n(__EXTShaderImageLoadStoreEntryPoints,
                    std::size(__EXTShaderImageLoadStoreEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTShaderImageLoadStore::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_shader_image_load_store");
}

void EXTShaderImageLoadStore::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTShaderImageLoadStoreEntryPoints,
                    std::size(__EXTShaderImageLoadStoreEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTStencilClearTag Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTStencilClearTag::EXTStencilClearTag()
{
    std::for_each_n(__EXTStencilClearTagEntryPoints,
                    std::size(__EXTStencilClearTagEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTStencilClearTag::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_stencil_clear_tag");
}

void EXTStencilClearTag::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTStencilClearTagEntryPoints,
                    std::size(__EXTStencilClearTagEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTStencilTwoSide Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTStencilTwoSide::EXTStencilTwoSide()
{
    std::for_each_n(__EXTStencilTwoSideEntryPoints,
                    std::size(__EXTStencilTwoSideEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTStencilTwoSide::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_stencil_two_side");
}

void EXTStencilTwoSide::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTStencilTwoSideEntryPoints,
                    std::size(__EXTStencilTwoSideEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSubtexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSubtexture::EXTSubtexture()
{
    std::for_each_n(__EXTSubtextureEntryPoints,
                    std::size(__EXTSubtextureEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTSubtexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_subtexture");
}

void EXTSubtexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSubtextureEntryPoints,
                    std::size(__EXTSubtextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTEXTURE3D Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTEXTURE3D::EXTTEXTURE3D()
{
    std::for_each_n(__EXTTEXTURE3DEntryPoints,
                    std::size(__EXTTEXTURE3DEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTEXTURE3D::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture3D");
}

void EXTTEXTURE3D::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTEXTURE3DEntryPoints,
                    std::size(__EXTTEXTURE3DEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureArray::EXTTextureArray()
{
    std::for_each_n(__EXTTextureArrayEntryPoints,
                    std::size(__EXTTextureArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTextureArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_array");
}

void EXTTextureArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureArrayEntryPoints,
                    std::size(__EXTTextureArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureBufferObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureBufferObject::EXTTextureBufferObject()
{
    std::for_each_n(__EXTTextureBufferObjectEntryPoints,
                    std::size(__EXTTextureBufferObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTextureBufferObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_buffer_object");
}

void EXTTextureBufferObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureBufferObjectEntryPoints,
                    std::size(__EXTTextureBufferObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureInteger Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureInteger::EXTTextureInteger()
{
    std::for_each_n(__EXTTextureIntegerEntryPoints,
                    std::size(__EXTTextureIntegerEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTextureInteger::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_integer");
}

void EXTTextureInteger::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureIntegerEntryPoints,
                    std::size(__EXTTextureIntegerEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureObject::EXTTextureObject()
{
    std::for_each_n(__EXTTextureObjectEntryPoints,
                    std::size(__EXTTextureObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTextureObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_object");
}

void EXTTextureObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureObjectEntryPoints,
                    std::size(__EXTTextureObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTexturePerturbNormal Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTexturePerturbNormal::EXTTexturePerturbNormal()
{
    std::for_each_n(__EXTTexturePerturbNormalEntryPoints,
                    std::size(__EXTTexturePerturbNormalEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTexturePerturbNormal::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_perturb_normal");
}

void EXTTexturePerturbNormal::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTexturePerturbNormalEntryPoints,
                    std::size(__EXTTexturePerturbNormalEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureStorage Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureStorage::EXTTextureStorage()
{
    std::for_each_n(__EXTTextureStorageEntryPoints,
                    std::size(__EXTTextureStorageEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTextureStorage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_texture_storage");
}

void EXTTextureStorage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureStorageEntryPoints,
                    std::size(__EXTTextureStorageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTimerQuery Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTimerQuery::EXTTimerQuery()
{
    std::for_each_n(__EXTTimerQueryEntryPoints,
                    std::size(__EXTTimerQueryEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTimerQuery::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_timer_query");
}

void EXTTimerQuery::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTimerQueryEntryPoints,
                    std::size(__EXTTimerQueryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTransformFeedback Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTransformFeedback::EXTTransformFeedback()
{
    std::for_each_n(__EXTTransformFeedbackEntryPoints,
                    std::size(__EXTTransformFeedbackEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTTransformFeedback::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_transform_feedback");
}

void EXTTransformFeedback::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTransformFeedbackEntryPoints,
                    std::size(__EXTTransformFeedbackEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTVertexArray::EXTVertexArray()
{
    std::for_each_n(__EXTVertexArrayEntryPoints,
                    std::size(__EXTVertexArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTVertexArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_vertex_array");
}

void EXTVertexArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTVertexArrayEntryPoints,
                    std::size(__EXTVertexArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexAttrib64BIT Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTVertexAttrib64BIT::EXTVertexAttrib64BIT()
{
    std::for_each_n(__EXTVertexAttrib64BITEntryPoints,
                    std::size(__EXTVertexAttrib64BITEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTVertexAttrib64BIT::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_vertex_attrib_64bit");
}

void EXTVertexAttrib64BIT::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTVertexAttrib64BITEntryPoints,
                    std::size(__EXTVertexAttrib64BITEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexShader Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTVertexShader::EXTVertexShader()
{
    std::for_each_n(__EXTVertexShaderEntryPoints,
                    std::size(__EXTVertexShaderEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTVertexShader::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_vertex_shader");
}

void EXTVertexShader::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTVertexShaderEntryPoints,
                    std::size(__EXTVertexShaderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexWeighting Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTVertexWeighting::EXTVertexWeighting()
{
    std::for_each_n(__EXTVertexWeightingEntryPoints,
                    std::size(__EXTVertexWeightingEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTVertexWeighting::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_vertex_weighting");
}

void EXTVertexWeighting::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTVertexWeightingEntryPoints,
                    std::size(__EXTVertexWeightingEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTWIN32KeyedMutex Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTWIN32KeyedMutex::EXTWIN32KeyedMutex()
{
    std::for_each_n(__EXTWIN32KeyedMutexEntryPoints,
                    std::size(__EXTWIN32KeyedMutexEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTWIN32KeyedMutex::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_win32_keyed_mutex");
}

void EXTWIN32KeyedMutex::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTWIN32KeyedMutexEntryPoints,
                    std::size(__EXTWIN32KeyedMutexEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTWindowRectangles Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTWindowRectangles::EXTWindowRectangles()
{
    std::for_each_n(__EXTWindowRectanglesEntryPoints,
                    std::size(__EXTWindowRectanglesEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTWindowRectangles::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_window_rectangles");
}

void EXTWindowRectangles::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTWindowRectanglesEntryPoints,
                    std::size(__EXTWindowRectanglesEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTX11SyncObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTX11SyncObject::EXTX11SyncObject()
{
    std::for_each_n(__EXTX11SyncObjectEntryPoints,
                    std::size(__EXTX11SyncObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool EXTX11SyncObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_EXT_x11_sync_object");
}

void EXTX11SyncObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTX11SyncObjectEntryPoints,
                    std::size(__EXTX11SyncObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl

#ifdef _WIN32
namespace wgl {
namespace {

static const gl::EntryOffset __EXTDisplayColorTableEntryPoints[] = {
    { offsetof(EXTDisplayColorTable, wglBindDisplayColorTable), "wglBindDisplayColorTableEXT" },
    { offsetof(EXTDisplayColorTable, wglCreateDisplayColorTable), "wglCreateDisplayColorTableEXT" },
    { offsetof(EXTDisplayColorTable, wglDestroyDisplayColorTable), "wglDestroyDisplayColorTableEXT" },
    { offsetof(EXTDisplayColorTable, wglLoadDisplayColorTable), "wglLoadDisplayColorTableEXT" },
};

static const gl::EntryOffset __EXTExtensionsStringEntryPoints[] = {
    { offsetof(EXTExtensionsString, wglGetExtensionsString), "wglGetExtensionsStringEXT" },
};

static const gl::EntryOffset __EXTMakeCurrentReadEntryPoints[] = {
    { offsetof(EXTMakeCurrentRead, wglGetCurrentReadDC), "wglGetCurrentReadDCEXT" },
    { offsetof(EXTMakeCurrentRead, wglMakeContextCurrent), "wglMakeContextCurrentEXT" },
};

static const gl::EntryOffset __EXTPbufferEntryPoints[] = {
    { offsetof(EXTPbuffer, wglCreatePbuffer), "wglCreatePbufferEXT" },
    { offsetof(EXTPbuffer, wglDestroyPbuffer), "wglDestroyPbufferEXT" },
    { offsetof(EXTPbuffer, wglGetPbufferDC), "wglGetPbufferDCEXT" },
    { offsetof(EXTPbuffer, wglQueryPbuffer), "wglQueryPbufferEXT" },
    { offsetof(EXTPbuffer, wglReleasePbufferDC), "wglReleasePbufferDCEXT" },
};

static const gl::EntryOffset __EXTPixelFormatEntryPoints[] = {
    { offsetof(EXTPixelFormat, wglChoosePixelFormat), "wglChoosePixelFormatEXT" },
    { offsetof(EXTPixelFormat, wglGetPixelFormatAttribfv), "wglGetPixelFormatAttribfvEXT" },
    { offsetof(EXTPixelFormat, wglGetPixelFormatAttribiv), "wglGetPixelFormatAttribivEXT" },
};

static const gl::EntryOffset __EXTSwapControlEntryPoints[] = {
    { offsetof(EXTSwapControl, wglGetSwapInterval), "wglGetSwapIntervalEXT" },
    { offsetof(EXTSwapControl, wglSwapInterval), "wglSwapIntervalEXT" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// EXTDisplayColorTable Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTDisplayColorTable::EXTDisplayColorTable()
{
    std::for_each_n(__EXTDisplayColorTableEntryPoints,
                    std::size(__EXTDisplayColorTableEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTDisplayColorTable::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_display_color_table");
}

void EXTDisplayColorTable::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTDisplayColorTableEntryPoints,
                    std::size(__EXTDisplayColorTableEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTExtensionsString Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTExtensionsString::EXTExtensionsString()
{
    std::for_each_n(__EXTExtensionsStringEntryPoints,
                    std::size(__EXTExtensionsStringEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTExtensionsString::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_extensions_string");
}

void EXTExtensionsString::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTExtensionsStringEntryPoints,
                    std::size(__EXTExtensionsStringEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTMakeCurrentRead Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTMakeCurrentRead::EXTMakeCurrentRead()
{
    std::for_each_n(__EXTMakeCurrentReadEntryPoints,
                    std::size(__EXTMakeCurrentReadEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTMakeCurrentRead::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_make_current_read");
}

void EXTMakeCurrentRead::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTMakeCurrentReadEntryPoints,
                    std::size(__EXTMakeCurrentReadEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPbuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPbuffer::EXTPbuffer()
{
    std::for_each_n(__EXTPbufferEntryPoints,
                    std::size(__EXTPbufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTPbuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_pbuffer");
}

void EXTPbuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPbufferEntryPoints,
                    std::size(__EXTPbufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTPixelFormat Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTPixelFormat::EXTPixelFormat()
{
    std::for_each_n(__EXTPixelFormatEntryPoints,
                    std::size(__EXTPixelFormatEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTPixelFormat::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_pixel_format");
}

void EXTPixelFormat::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTPixelFormatEntryPoints,
                    std::size(__EXTPixelFormatEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSwapControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSwapControl::EXTSwapControl()
{
    std::for_each_n(__EXTSwapControlEntryPoints,
                    std::size(__EXTSwapControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTSwapControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_EXT_swap_control");
}

void EXTSwapControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSwapControlEntryPoints,
                    std::size(__EXTSwapControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __EXTImportContextEntryPoints[] = {
    { offsetof(EXTImportContext, glXFreeContext), "glXFreeContextEXT" },
    { offsetof(EXTImportContext, glXGetContextID), "glXGetContextIDEXT" },
    { offsetof(EXTImportContext, glXGetCurrentDisplay), "glXGetCurrentDisplayEXT" },
    { offsetof(EXTImportContext, glXImportContext), "glXImportContextEXT" },
    { offsetof(EXTImportContext, glXQueryContextInfo), "glXQueryContextInfoEXT" },
};

static const gl::EntryOffset __EXTSwapControlEntryPoints[] = {
    { offsetof(EXTSwapControl, glXSwapInterval), "glXSwapIntervalEXT" },
};

static const gl::EntryOffset __EXTTextureFromPixmapEntryPoints[] = {
    { offsetof(EXTTextureFromPixmap, glXBindTexImage), "glXBindTexImageEXT" },
    { offsetof(EXTTextureFromPixmap, glXReleaseTexImage), "glXReleaseTexImageEXT" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// EXTImportContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTImportContext::EXTImportContext()
{
    std::for_each_n(__EXTImportContextEntryPoints,
                    std::size(__EXTImportContextEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTImportContext::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_EXT_import_context");
}

void EXTImportContext::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTImportContextEntryPoints,
                    std::size(__EXTImportContextEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTSwapControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTSwapControl::EXTSwapControl()
{
    std::for_each_n(__EXTSwapControlEntryPoints,
                    std::size(__EXTSwapControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTSwapControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_EXT_swap_control");
}

void EXTSwapControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTSwapControlEntryPoints,
                    std::size(__EXTSwapControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureFromPixmap Member Definitions
////////////////////////////////////////////////////////////////////////////////
EXTTextureFromPixmap::EXTTextureFromPixmap()
{
    std::for_each_n(__EXTTextureFromPixmapEntryPoints,
                    std::size(__EXTTextureFromPixmapEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool EXTTextureFromPixmap::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_EXT_texture_from_pixmap");
}

void EXTTextureFromPixmap::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__EXTTextureFromPixmapEntryPoints,
                    std::size(__EXTTextureFromPixmapEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

