//! @file ObjectGL/Extensions/ARB.cpp
//! @brief The definition of Architecture Review Board (ARB) -specific
//! extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/ARB.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __ARBES32CompatibilityEntryPoints[] = {
    { offsetof(ARBES32Compatibility, glPrimitiveBoundingBox), "glPrimitiveBoundingBoxARB" },
};

static const EntryOffset __ARBBindlessTextureEntryPoints[] = {
    { offsetof(ARBBindlessTexture, glGetImageHandle), "glGetImageHandleARB" },
    { offsetof(ARBBindlessTexture, glGetTextureHandle), "glGetTextureHandleARB" },
    { offsetof(ARBBindlessTexture, glGetTextureSamplerHandle), "glGetTextureSamplerHandleARB" },
    { offsetof(ARBBindlessTexture, glGetVertexAttribLui64v), "glGetVertexAttribLui64vARB" },
    { offsetof(ARBBindlessTexture, glIsImageHandleResident), "glIsImageHandleResidentARB" },
    { offsetof(ARBBindlessTexture, glIsTextureHandleResident), "glIsTextureHandleResidentARB" },
    { offsetof(ARBBindlessTexture, glMakeImageHandleNonResident), "glMakeImageHandleNonResidentARB" },
    { offsetof(ARBBindlessTexture, glMakeImageHandleResident), "glMakeImageHandleResidentARB" },
    { offsetof(ARBBindlessTexture, glMakeTextureHandleNonResident), "glMakeTextureHandleNonResidentARB" },
    { offsetof(ARBBindlessTexture, glMakeTextureHandleResident), "glMakeTextureHandleResidentARB" },
    { offsetof(ARBBindlessTexture, glProgramUniformHandleui64), "glProgramUniformHandleui64ARB" },
    { offsetof(ARBBindlessTexture, glProgramUniformHandleui64v), "glProgramUniformHandleui64vARB" },
    { offsetof(ARBBindlessTexture, glUniformHandleui64), "glUniformHandleui64ARB" },
    { offsetof(ARBBindlessTexture, glUniformHandleui64v), "glUniformHandleui64vARB" },
    { offsetof(ARBBindlessTexture, glVertexAttribL1ui64), "glVertexAttribL1ui64ARB" },
    { offsetof(ARBBindlessTexture, glVertexAttribL1ui64v), "glVertexAttribL1ui64vARB" },
};

static const EntryOffset __ARBClEventEntryPoints[] = {
    { offsetof(ARBClEvent, glCreateSyncFromCLevent), "glCreateSyncFromCLeventARB" },
};

static const EntryOffset __ARBColorBufferFloatEntryPoints[] = {
    { offsetof(ARBColorBufferFloat, glClampColor), "glClampColorARB" },
};

static const EntryOffset __ARBComputeVariableGroupSizeEntryPoints[] = {
    { offsetof(ARBComputeVariableGroupSize, glDispatchComputeGroupSize), "glDispatchComputeGroupSizeARB" },
};

static const EntryOffset __ARBDebugOutputEntryPoints[] = {
    { offsetof(ARBDebugOutput, glDebugMessageCallback), "glDebugMessageCallbackARB" },
    { offsetof(ARBDebugOutput, glDebugMessageControl), "glDebugMessageControlARB" },
    { offsetof(ARBDebugOutput, glDebugMessageInsert), "glDebugMessageInsertARB" },
    { offsetof(ARBDebugOutput, glGetDebugMessageLog), "glGetDebugMessageLogARB" },
};

static const EntryOffset __ARBDrawBuffersEntryPoints[] = {
    { offsetof(ARBDrawBuffers, glDrawBuffers), "glDrawBuffersARB" },
};

static const EntryOffset __ARBDrawBuffersBlendEntryPoints[] = {
    { offsetof(ARBDrawBuffersBlend, glBlendEquationSeparatei), "glBlendEquationSeparateiARB" },
    { offsetof(ARBDrawBuffersBlend, glBlendEquationi), "glBlendEquationiARB" },
    { offsetof(ARBDrawBuffersBlend, glBlendFuncSeparatei), "glBlendFuncSeparateiARB" },
    { offsetof(ARBDrawBuffersBlend, glBlendFunci), "glBlendFunciARB" },
};

static const EntryOffset __ARBDrawInstancedEntryPoints[] = {
    { offsetof(ARBDrawInstanced, glDrawArraysInstanced), "glDrawArraysInstancedARB" },
    { offsetof(ARBDrawInstanced, glDrawElementsInstanced), "glDrawElementsInstancedARB" },
};

static const EntryOffset __ARBFragmentProgramEntryPoints[] = {
    { offsetof(ARBFragmentProgram, glBindProgram), "glBindProgramARB" },
    { offsetof(ARBFragmentProgram, glDeletePrograms), "glDeleteProgramsARB" },
    { offsetof(ARBFragmentProgram, glGenPrograms), "glGenProgramsARB" },
    { offsetof(ARBFragmentProgram, glGetProgramEnvParameterdv), "glGetProgramEnvParameterdvARB" },
    { offsetof(ARBFragmentProgram, glGetProgramEnvParameterfv), "glGetProgramEnvParameterfvARB" },
    { offsetof(ARBFragmentProgram, glGetProgramLocalParameterdv), "glGetProgramLocalParameterdvARB" },
    { offsetof(ARBFragmentProgram, glGetProgramLocalParameterfv), "glGetProgramLocalParameterfvARB" },
    { offsetof(ARBFragmentProgram, glGetProgramString), "glGetProgramStringARB" },
    { offsetof(ARBFragmentProgram, glGetProgramiv), "glGetProgramivARB" },
    { offsetof(ARBFragmentProgram, glIsProgram), "glIsProgramARB" },
    { offsetof(ARBFragmentProgram, glProgramEnvParameter4d), "glProgramEnvParameter4dARB" },
    { offsetof(ARBFragmentProgram, glProgramEnvParameter4dv), "glProgramEnvParameter4dvARB" },
    { offsetof(ARBFragmentProgram, glProgramEnvParameter4f), "glProgramEnvParameter4fARB" },
    { offsetof(ARBFragmentProgram, glProgramEnvParameter4fv), "glProgramEnvParameter4fvARB" },
    { offsetof(ARBFragmentProgram, glProgramLocalParameter4d), "glProgramLocalParameter4dARB" },
    { offsetof(ARBFragmentProgram, glProgramLocalParameter4dv), "glProgramLocalParameter4dvARB" },
    { offsetof(ARBFragmentProgram, glProgramLocalParameter4f), "glProgramLocalParameter4fARB" },
    { offsetof(ARBFragmentProgram, glProgramLocalParameter4fv), "glProgramLocalParameter4fvARB" },
    { offsetof(ARBFragmentProgram, glProgramString), "glProgramStringARB" },
};

static const EntryOffset __ARBGeometrySHADER4EntryPoints[] = {
    { offsetof(ARBGeometrySHADER4, glFramebufferTexture), "glFramebufferTextureARB" },
    { offsetof(ARBGeometrySHADER4, glFramebufferTextureFace), "glFramebufferTextureFaceARB" },
    { offsetof(ARBGeometrySHADER4, glFramebufferTextureLayer), "glFramebufferTextureLayerARB" },
    { offsetof(ARBGeometrySHADER4, glProgramParameteri), "glProgramParameteriARB" },
};

static const EntryOffset __ARBGlSpirvEntryPoints[] = {
    { offsetof(ARBGlSpirv, glSpecializeShader), "glSpecializeShaderARB" },
};

static const EntryOffset __ARBGPUShaderInt64EntryPoints[] = {
    { offsetof(ARBGPUShaderInt64, glGetUniformi64v), "glGetUniformi64vARB" },
    { offsetof(ARBGPUShaderInt64, glGetUniformui64v), "glGetUniformui64vARB" },
    { offsetof(ARBGPUShaderInt64, glGetnUniformi64v), "glGetnUniformi64vARB" },
    { offsetof(ARBGPUShaderInt64, glGetnUniformui64v), "glGetnUniformui64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform1i64), "glProgramUniform1i64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform1i64v), "glProgramUniform1i64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform1ui64), "glProgramUniform1ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform1ui64v), "glProgramUniform1ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform2i64), "glProgramUniform2i64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform2i64v), "glProgramUniform2i64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform2ui64), "glProgramUniform2ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform2ui64v), "glProgramUniform2ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform3i64), "glProgramUniform3i64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform3i64v), "glProgramUniform3i64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform3ui64), "glProgramUniform3ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform3ui64v), "glProgramUniform3ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform4i64), "glProgramUniform4i64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform4i64v), "glProgramUniform4i64vARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform4ui64), "glProgramUniform4ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glProgramUniform4ui64v), "glProgramUniform4ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform1i64), "glUniform1i64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform1i64v), "glUniform1i64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform1ui64), "glUniform1ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform1ui64v), "glUniform1ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform2i64), "glUniform2i64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform2i64v), "glUniform2i64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform2ui64), "glUniform2ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform2ui64v), "glUniform2ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform3i64), "glUniform3i64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform3i64v), "glUniform3i64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform3ui64), "glUniform3ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform3ui64v), "glUniform3ui64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform4i64), "glUniform4i64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform4i64v), "glUniform4i64vARB" },
    { offsetof(ARBGPUShaderInt64, glUniform4ui64), "glUniform4ui64ARB" },
    { offsetof(ARBGPUShaderInt64, glUniform4ui64v), "glUniform4ui64vARB" },
};

static const EntryOffset __ARBIndirectParametersEntryPoints[] = {
    { offsetof(ARBIndirectParameters, glMultiDrawArraysIndirectCount), "glMultiDrawArraysIndirectCountARB" },
    { offsetof(ARBIndirectParameters, glMultiDrawElementsIndirectCount), "glMultiDrawElementsIndirectCountARB" },
};

static const EntryOffset __ARBInstancedArraysEntryPoints[] = {
    { offsetof(ARBInstancedArrays, glVertexAttribDivisor), "glVertexAttribDivisorARB" },
};

static const EntryOffset __ARBMatrixPaletteEntryPoints[] = {
    { offsetof(ARBMatrixPalette, glCurrentPaletteMatrix), "glCurrentPaletteMatrixARB" },
    { offsetof(ARBMatrixPalette, glMatrixIndexPointer), "glMatrixIndexPointerARB" },
    { offsetof(ARBMatrixPalette, glMatrixIndexubv), "glMatrixIndexubvARB" },
    { offsetof(ARBMatrixPalette, glMatrixIndexuiv), "glMatrixIndexuivARB" },
    { offsetof(ARBMatrixPalette, glMatrixIndexusv), "glMatrixIndexusvARB" },
};

static const EntryOffset __ARBMultisampleEntryPoints[] = {
    { offsetof(ARBMultisample, glSampleCoverage), "glSampleCoverageARB" },
};

static const EntryOffset __ARBMultitextureEntryPoints[] = {
    { offsetof(ARBMultitexture, glActiveTexture), "glActiveTextureARB" },
    { offsetof(ARBMultitexture, glClientActiveTexture), "glClientActiveTextureARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1d), "glMultiTexCoord1dARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1dv), "glMultiTexCoord1dvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1f), "glMultiTexCoord1fARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1fv), "glMultiTexCoord1fvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1i), "glMultiTexCoord1iARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1iv), "glMultiTexCoord1ivARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1s), "glMultiTexCoord1sARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord1sv), "glMultiTexCoord1svARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2d), "glMultiTexCoord2dARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2dv), "glMultiTexCoord2dvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2f), "glMultiTexCoord2fARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2fv), "glMultiTexCoord2fvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2i), "glMultiTexCoord2iARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2iv), "glMultiTexCoord2ivARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2s), "glMultiTexCoord2sARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord2sv), "glMultiTexCoord2svARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3d), "glMultiTexCoord3dARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3dv), "glMultiTexCoord3dvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3f), "glMultiTexCoord3fARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3fv), "glMultiTexCoord3fvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3i), "glMultiTexCoord3iARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3iv), "glMultiTexCoord3ivARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3s), "glMultiTexCoord3sARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord3sv), "glMultiTexCoord3svARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4d), "glMultiTexCoord4dARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4dv), "glMultiTexCoord4dvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4f), "glMultiTexCoord4fARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4fv), "glMultiTexCoord4fvARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4i), "glMultiTexCoord4iARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4iv), "glMultiTexCoord4ivARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4s), "glMultiTexCoord4sARB" },
    { offsetof(ARBMultitexture, glMultiTexCoord4sv), "glMultiTexCoord4svARB" },
};

static const EntryOffset __ARBOcclusionQueryEntryPoints[] = {
    { offsetof(ARBOcclusionQuery, glBeginQuery), "glBeginQueryARB" },
    { offsetof(ARBOcclusionQuery, glDeleteQueries), "glDeleteQueriesARB" },
    { offsetof(ARBOcclusionQuery, glEndQuery), "glEndQueryARB" },
    { offsetof(ARBOcclusionQuery, glGenQueries), "glGenQueriesARB" },
    { offsetof(ARBOcclusionQuery, glGetQueryObjectiv), "glGetQueryObjectivARB" },
    { offsetof(ARBOcclusionQuery, glGetQueryObjectuiv), "glGetQueryObjectuivARB" },
    { offsetof(ARBOcclusionQuery, glGetQueryiv), "glGetQueryivARB" },
    { offsetof(ARBOcclusionQuery, glIsQuery), "glIsQueryARB" },
};

static const EntryOffset __ARBParallelShaderCompileEntryPoints[] = {
    { offsetof(ARBParallelShaderCompile, glMaxShaderCompilerThreads), "glMaxShaderCompilerThreadsARB" },
};

static const EntryOffset __ARBPointParametersEntryPoints[] = {
    { offsetof(ARBPointParameters, glPointParameterf), "glPointParameterfARB" },
    { offsetof(ARBPointParameters, glPointParameterfv), "glPointParameterfvARB" },
};

static const EntryOffset __ARBRobustnessEntryPoints[] = {
    { offsetof(ARBRobustness, glGetGraphicsResetStatus), "glGetGraphicsResetStatusARB" },
    { offsetof(ARBRobustness, glGetnCompressedTexImage), "glGetnCompressedTexImageARB" },
    { offsetof(ARBRobustness, glGetnTexImage), "glGetnTexImageARB" },
    { offsetof(ARBRobustness, glGetnUniformdv), "glGetnUniformdvARB" },
    { offsetof(ARBRobustness, glGetnUniformfv), "glGetnUniformfvARB" },
    { offsetof(ARBRobustness, glGetnUniformiv), "glGetnUniformivARB" },
    { offsetof(ARBRobustness, glGetnUniformuiv), "glGetnUniformuivARB" },
    { offsetof(ARBRobustness, glReadnPixels), "glReadnPixelsARB" },
};

static const EntryOffset __ARBSampleLocationsEntryPoints[] = {
    { offsetof(ARBSampleLocations, glEvaluateDepthValues), "glEvaluateDepthValuesARB" },
    { offsetof(ARBSampleLocations, glFramebufferSampleLocationsfv), "glFramebufferSampleLocationsfvARB" },
    { offsetof(ARBSampleLocations, glNamedFramebufferSampleLocationsfv), "glNamedFramebufferSampleLocationsfvARB" },
};

static const EntryOffset __ARBSampleShadingEntryPoints[] = {
    { offsetof(ARBSampleShading, glMinSampleShading), "glMinSampleShadingARB" },
};

static const EntryOffset __ARBShaderObjectsEntryPoints[] = {
    { offsetof(ARBShaderObjects, glAttachObject), "glAttachObjectARB" },
    { offsetof(ARBShaderObjects, glCompileShader), "glCompileShaderARB" },
    { offsetof(ARBShaderObjects, glCreateProgramObject), "glCreateProgramObjectARB" },
    { offsetof(ARBShaderObjects, glCreateShaderObject), "glCreateShaderObjectARB" },
    { offsetof(ARBShaderObjects, glDeleteObject), "glDeleteObjectARB" },
    { offsetof(ARBShaderObjects, glDetachObject), "glDetachObjectARB" },
    { offsetof(ARBShaderObjects, glGetActiveUniform), "glGetActiveUniformARB" },
    { offsetof(ARBShaderObjects, glGetAttachedObjects), "glGetAttachedObjectsARB" },
    { offsetof(ARBShaderObjects, glGetHandle), "glGetHandleARB" },
    { offsetof(ARBShaderObjects, glGetInfoLog), "glGetInfoLogARB" },
    { offsetof(ARBShaderObjects, glGetObjectParameterfv), "glGetObjectParameterfvARB" },
    { offsetof(ARBShaderObjects, glGetObjectParameteriv), "glGetObjectParameterivARB" },
    { offsetof(ARBShaderObjects, glGetShaderSource), "glGetShaderSourceARB" },
    { offsetof(ARBShaderObjects, glGetUniformLocation), "glGetUniformLocationARB" },
    { offsetof(ARBShaderObjects, glGetUniformfv), "glGetUniformfvARB" },
    { offsetof(ARBShaderObjects, glGetUniformiv), "glGetUniformivARB" },
    { offsetof(ARBShaderObjects, glLinkProgram), "glLinkProgramARB" },
    { offsetof(ARBShaderObjects, glShaderSource), "glShaderSourceARB" },
    { offsetof(ARBShaderObjects, glUniform1f), "glUniform1fARB" },
    { offsetof(ARBShaderObjects, glUniform1fv), "glUniform1fvARB" },
    { offsetof(ARBShaderObjects, glUniform1i), "glUniform1iARB" },
    { offsetof(ARBShaderObjects, glUniform1iv), "glUniform1ivARB" },
    { offsetof(ARBShaderObjects, glUniform2f), "glUniform2fARB" },
    { offsetof(ARBShaderObjects, glUniform2fv), "glUniform2fvARB" },
    { offsetof(ARBShaderObjects, glUniform2i), "glUniform2iARB" },
    { offsetof(ARBShaderObjects, glUniform2iv), "glUniform2ivARB" },
    { offsetof(ARBShaderObjects, glUniform3f), "glUniform3fARB" },
    { offsetof(ARBShaderObjects, glUniform3fv), "glUniform3fvARB" },
    { offsetof(ARBShaderObjects, glUniform3i), "glUniform3iARB" },
    { offsetof(ARBShaderObjects, glUniform3iv), "glUniform3ivARB" },
    { offsetof(ARBShaderObjects, glUniform4f), "glUniform4fARB" },
    { offsetof(ARBShaderObjects, glUniform4fv), "glUniform4fvARB" },
    { offsetof(ARBShaderObjects, glUniform4i), "glUniform4iARB" },
    { offsetof(ARBShaderObjects, glUniform4iv), "glUniform4ivARB" },
    { offsetof(ARBShaderObjects, glUniformMatrix2fv), "glUniformMatrix2fvARB" },
    { offsetof(ARBShaderObjects, glUniformMatrix3fv), "glUniformMatrix3fvARB" },
    { offsetof(ARBShaderObjects, glUniformMatrix4fv), "glUniformMatrix4fvARB" },
    { offsetof(ARBShaderObjects, glUseProgramObject), "glUseProgramObjectARB" },
    { offsetof(ARBShaderObjects, glValidateProgram), "glValidateProgramARB" },
};

static const EntryOffset __ARBShadingLanguageIncludeEntryPoints[] = {
    { offsetof(ARBShadingLanguageInclude, glCompileShaderInclude), "glCompileShaderIncludeARB" },
    { offsetof(ARBShadingLanguageInclude, glDeleteNamedString), "glDeleteNamedStringARB" },
    { offsetof(ARBShadingLanguageInclude, glGetNamedString), "glGetNamedStringARB" },
    { offsetof(ARBShadingLanguageInclude, glGetNamedStringiv), "glGetNamedStringivARB" },
    { offsetof(ARBShadingLanguageInclude, glIsNamedString), "glIsNamedStringARB" },
    { offsetof(ARBShadingLanguageInclude, glNamedString), "glNamedStringARB" },
};

static const EntryOffset __ARBSparseBufferEntryPoints[] = {
    { offsetof(ARBSparseBuffer, glBufferPageCommitment), "glBufferPageCommitmentARB" },
    { offsetof(ARBSparseBuffer, glNamedBufferPageCommitmentARB), "glNamedBufferPageCommitmentARB" },
    { offsetof(ARBSparseBuffer, glNamedBufferPageCommitmentEXT), "glNamedBufferPageCommitmentEXT" },
};

static const EntryOffset __ARBSparseTextureEntryPoints[] = {
    { offsetof(ARBSparseTexture, glTexPageCommitment), "glTexPageCommitmentARB" },
};

static const EntryOffset __ARBTextureBufferObjectEntryPoints[] = {
    { offsetof(ARBTextureBufferObject, glTexBuffer), "glTexBufferARB" },
};

static const EntryOffset __ARBTextureCompressionEntryPoints[] = {
    { offsetof(ARBTextureCompression, glCompressedTexImage1D), "glCompressedTexImage1DARB" },
    { offsetof(ARBTextureCompression, glCompressedTexImage2D), "glCompressedTexImage2DARB" },
    { offsetof(ARBTextureCompression, glCompressedTexImage3D), "glCompressedTexImage3DARB" },
    { offsetof(ARBTextureCompression, glCompressedTexSubImage1D), "glCompressedTexSubImage1DARB" },
    { offsetof(ARBTextureCompression, glCompressedTexSubImage2D), "glCompressedTexSubImage2DARB" },
    { offsetof(ARBTextureCompression, glCompressedTexSubImage3D), "glCompressedTexSubImage3DARB" },
    { offsetof(ARBTextureCompression, glGetCompressedTexImage), "glGetCompressedTexImageARB" },
};

static const EntryOffset __ARBTransposeMatrixEntryPoints[] = {
    { offsetof(ARBTransposeMatrix, glLoadTransposeMatrixd), "glLoadTransposeMatrixdARB" },
    { offsetof(ARBTransposeMatrix, glLoadTransposeMatrixf), "glLoadTransposeMatrixfARB" },
    { offsetof(ARBTransposeMatrix, glMultTransposeMatrixd), "glMultTransposeMatrixdARB" },
    { offsetof(ARBTransposeMatrix, glMultTransposeMatrixf), "glMultTransposeMatrixfARB" },
};

static const EntryOffset __ARBVertexBlendEntryPoints[] = {
    { offsetof(ARBVertexBlend, glVertexBlend), "glVertexBlendARB" },
    { offsetof(ARBVertexBlend, glWeightPointer), "glWeightPointerARB" },
    { offsetof(ARBVertexBlend, glWeightbv), "glWeightbvARB" },
    { offsetof(ARBVertexBlend, glWeightdv), "glWeightdvARB" },
    { offsetof(ARBVertexBlend, glWeightfv), "glWeightfvARB" },
    { offsetof(ARBVertexBlend, glWeightiv), "glWeightivARB" },
    { offsetof(ARBVertexBlend, glWeightsv), "glWeightsvARB" },
    { offsetof(ARBVertexBlend, glWeightubv), "glWeightubvARB" },
    { offsetof(ARBVertexBlend, glWeightuiv), "glWeightuivARB" },
    { offsetof(ARBVertexBlend, glWeightusv), "glWeightusvARB" },
};

static const EntryOffset __ARBVertexBufferObjectEntryPoints[] = {
    { offsetof(ARBVertexBufferObject, glBindBuffer), "glBindBufferARB" },
    { offsetof(ARBVertexBufferObject, glBufferData), "glBufferDataARB" },
    { offsetof(ARBVertexBufferObject, glBufferSubData), "glBufferSubDataARB" },
    { offsetof(ARBVertexBufferObject, glDeleteBuffers), "glDeleteBuffersARB" },
    { offsetof(ARBVertexBufferObject, glGenBuffers), "glGenBuffersARB" },
    { offsetof(ARBVertexBufferObject, glGetBufferParameteriv), "glGetBufferParameterivARB" },
    { offsetof(ARBVertexBufferObject, glGetBufferPointerv), "glGetBufferPointervARB" },
    { offsetof(ARBVertexBufferObject, glGetBufferSubData), "glGetBufferSubDataARB" },
    { offsetof(ARBVertexBufferObject, glIsBuffer), "glIsBufferARB" },
    { offsetof(ARBVertexBufferObject, glMapBuffer), "glMapBufferARB" },
    { offsetof(ARBVertexBufferObject, glUnmapBuffer), "glUnmapBufferARB" },
};

static const EntryOffset __ARBVertexProgramEntryPoints[] = {
    { offsetof(ARBVertexProgram, glDisableVertexAttribArray), "glDisableVertexAttribArrayARB" },
    { offsetof(ARBVertexProgram, glEnableVertexAttribArray), "glEnableVertexAttribArrayARB" },
    { offsetof(ARBVertexProgram, glGetVertexAttribPointerv), "glGetVertexAttribPointervARB" },
    { offsetof(ARBVertexProgram, glGetVertexAttribdv), "glGetVertexAttribdvARB" },
    { offsetof(ARBVertexProgram, glGetVertexAttribfv), "glGetVertexAttribfvARB" },
    { offsetof(ARBVertexProgram, glGetVertexAttribiv), "glGetVertexAttribivARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1d), "glVertexAttrib1dARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1dv), "glVertexAttrib1dvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1f), "glVertexAttrib1fARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1fv), "glVertexAttrib1fvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1s), "glVertexAttrib1sARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib1sv), "glVertexAttrib1svARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2d), "glVertexAttrib2dARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2dv), "glVertexAttrib2dvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2f), "glVertexAttrib2fARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2fv), "glVertexAttrib2fvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2s), "glVertexAttrib2sARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib2sv), "glVertexAttrib2svARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3d), "glVertexAttrib3dARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3dv), "glVertexAttrib3dvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3f), "glVertexAttrib3fARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3fv), "glVertexAttrib3fvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3s), "glVertexAttrib3sARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib3sv), "glVertexAttrib3svARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nbv), "glVertexAttrib4NbvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Niv), "glVertexAttrib4NivARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nsv), "glVertexAttrib4NsvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nub), "glVertexAttrib4NubARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nubv), "glVertexAttrib4NubvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nuiv), "glVertexAttrib4NuivARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4Nusv), "glVertexAttrib4NusvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4bv), "glVertexAttrib4bvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4d), "glVertexAttrib4dARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4dv), "glVertexAttrib4dvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4f), "glVertexAttrib4fARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4fv), "glVertexAttrib4fvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4iv), "glVertexAttrib4ivARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4s), "glVertexAttrib4sARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4sv), "glVertexAttrib4svARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4ubv), "glVertexAttrib4ubvARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4uiv), "glVertexAttrib4uivARB" },
    { offsetof(ARBVertexProgram, glVertexAttrib4usv), "glVertexAttrib4usvARB" },
    { offsetof(ARBVertexProgram, glVertexAttribPointer), "glVertexAttribPointerARB" },
};

static const EntryOffset __ARBVertexShaderEntryPoints[] = {
    { offsetof(ARBVertexShader, glBindAttribLocation), "glBindAttribLocationARB" },
    { offsetof(ARBVertexShader, glGetActiveAttrib), "glGetActiveAttribARB" },
    { offsetof(ARBVertexShader, glGetAttribLocation), "glGetAttribLocationARB" },
};

static const EntryOffset __ARBViewportArrayEntryPoints[] = {
    { offsetof(ARBViewportArray, glDepthRangeArraydv), "glDepthRangeArraydvNV" },
    { offsetof(ARBViewportArray, glDepthRangeIndexedd), "glDepthRangeIndexeddNV" },
};

static const EntryOffset __ARBWindowPosEntryPoints[] = {
    { offsetof(ARBWindowPos, glWindowPos2d), "glWindowPos2dARB" },
    { offsetof(ARBWindowPos, glWindowPos2dv), "glWindowPos2dvARB" },
    { offsetof(ARBWindowPos, glWindowPos2f), "glWindowPos2fARB" },
    { offsetof(ARBWindowPos, glWindowPos2fv), "glWindowPos2fvARB" },
    { offsetof(ARBWindowPos, glWindowPos2i), "glWindowPos2iARB" },
    { offsetof(ARBWindowPos, glWindowPos2iv), "glWindowPos2ivARB" },
    { offsetof(ARBWindowPos, glWindowPos2s), "glWindowPos2sARB" },
    { offsetof(ARBWindowPos, glWindowPos2sv), "glWindowPos2svARB" },
    { offsetof(ARBWindowPos, glWindowPos3d), "glWindowPos3dARB" },
    { offsetof(ARBWindowPos, glWindowPos3dv), "glWindowPos3dvARB" },
    { offsetof(ARBWindowPos, glWindowPos3f), "glWindowPos3fARB" },
    { offsetof(ARBWindowPos, glWindowPos3fv), "glWindowPos3fvARB" },
    { offsetof(ARBWindowPos, glWindowPos3i), "glWindowPos3iARB" },
    { offsetof(ARBWindowPos, glWindowPos3iv), "glWindowPos3ivARB" },
    { offsetof(ARBWindowPos, glWindowPos3s), "glWindowPos3sARB" },
    { offsetof(ARBWindowPos, glWindowPos3sv), "glWindowPos3svARB" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ARBES32Compatibility Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBES32Compatibility::ARBES32Compatibility()
{
    std::for_each_n(__ARBES32CompatibilityEntryPoints,
                    std::size(__ARBES32CompatibilityEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBES32Compatibility::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_ES3_2_compatibility");
}

void ARBES32Compatibility::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBES32CompatibilityEntryPoints,
                    std::size(__ARBES32CompatibilityEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBBindlessTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBBindlessTexture::ARBBindlessTexture()
{
    std::for_each_n(__ARBBindlessTextureEntryPoints,
                    std::size(__ARBBindlessTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBBindlessTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_bindless_texture");
}

void ARBBindlessTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBBindlessTextureEntryPoints,
                    std::size(__ARBBindlessTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBClEvent Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBClEvent::ARBClEvent()
{
    std::for_each_n(__ARBClEventEntryPoints,
                    std::size(__ARBClEventEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBClEvent::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_cl_event");
}

void ARBClEvent::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBClEventEntryPoints,
                    std::size(__ARBClEventEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBColorBufferFloat Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBColorBufferFloat::ARBColorBufferFloat()
{
    std::for_each_n(__ARBColorBufferFloatEntryPoints,
                    std::size(__ARBColorBufferFloatEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBColorBufferFloat::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_color_buffer_float");
}

void ARBColorBufferFloat::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBColorBufferFloatEntryPoints,
                    std::size(__ARBColorBufferFloatEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBComputeVariableGroupSize Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBComputeVariableGroupSize::ARBComputeVariableGroupSize()
{
    std::for_each_n(__ARBComputeVariableGroupSizeEntryPoints,
                    std::size(__ARBComputeVariableGroupSizeEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBComputeVariableGroupSize::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_compute_variable_group_size");
}

void ARBComputeVariableGroupSize::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBComputeVariableGroupSizeEntryPoints,
                    std::size(__ARBComputeVariableGroupSizeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBDebugOutput Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBDebugOutput::ARBDebugOutput()
{
    std::for_each_n(__ARBDebugOutputEntryPoints,
                    std::size(__ARBDebugOutputEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBDebugOutput::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_debug_output");
}

void ARBDebugOutput::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBDebugOutputEntryPoints,
                    std::size(__ARBDebugOutputEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawBuffers Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBDrawBuffers::ARBDrawBuffers()
{
    std::for_each_n(__ARBDrawBuffersEntryPoints,
                    std::size(__ARBDrawBuffersEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBDrawBuffers::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_draw_buffers");
}

void ARBDrawBuffers::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBDrawBuffersEntryPoints,
                    std::size(__ARBDrawBuffersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawBuffersBlend Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBDrawBuffersBlend::ARBDrawBuffersBlend()
{
    std::for_each_n(__ARBDrawBuffersBlendEntryPoints,
                    std::size(__ARBDrawBuffersBlendEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBDrawBuffersBlend::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_draw_buffers_blend");
}

void ARBDrawBuffersBlend::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBDrawBuffersBlendEntryPoints,
                    std::size(__ARBDrawBuffersBlendEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawInstanced Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBDrawInstanced::ARBDrawInstanced()
{
    std::for_each_n(__ARBDrawInstancedEntryPoints,
                    std::size(__ARBDrawInstancedEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBDrawInstanced::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_draw_instanced");
}

void ARBDrawInstanced::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBDrawInstancedEntryPoints,
                    std::size(__ARBDrawInstancedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBFragmentProgram Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBFragmentProgram::ARBFragmentProgram()
{
    std::for_each_n(__ARBFragmentProgramEntryPoints,
                    std::size(__ARBFragmentProgramEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBFragmentProgram::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_fragment_program");
}

void ARBFragmentProgram::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBFragmentProgramEntryPoints,
                    std::size(__ARBFragmentProgramEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBGeometrySHADER4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBGeometrySHADER4::ARBGeometrySHADER4()
{
    std::for_each_n(__ARBGeometrySHADER4EntryPoints,
                    std::size(__ARBGeometrySHADER4EntryPoints),
                    ClearEntryPoint(this));
}

bool ARBGeometrySHADER4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_geometry_shader4");
}

void ARBGeometrySHADER4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBGeometrySHADER4EntryPoints,
                    std::size(__ARBGeometrySHADER4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBGlSpirv Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBGlSpirv::ARBGlSpirv()
{
    std::for_each_n(__ARBGlSpirvEntryPoints,
                    std::size(__ARBGlSpirvEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBGlSpirv::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_gl_spirv");
}

void ARBGlSpirv::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBGlSpirvEntryPoints,
                    std::size(__ARBGlSpirvEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBGPUShaderInt64 Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBGPUShaderInt64::ARBGPUShaderInt64()
{
    std::for_each_n(__ARBGPUShaderInt64EntryPoints,
                    std::size(__ARBGPUShaderInt64EntryPoints),
                    ClearEntryPoint(this));
}

bool ARBGPUShaderInt64::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_gpu_shader_int64");
}

void ARBGPUShaderInt64::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBGPUShaderInt64EntryPoints,
                    std::size(__ARBGPUShaderInt64EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBIndirectParameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBIndirectParameters::ARBIndirectParameters()
{
    std::for_each_n(__ARBIndirectParametersEntryPoints,
                    std::size(__ARBIndirectParametersEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBIndirectParameters::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_indirect_parameters");
}

void ARBIndirectParameters::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBIndirectParametersEntryPoints,
                    std::size(__ARBIndirectParametersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBInstancedArrays Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBInstancedArrays::ARBInstancedArrays()
{
    std::for_each_n(__ARBInstancedArraysEntryPoints,
                    std::size(__ARBInstancedArraysEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBInstancedArrays::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_instanced_arrays");
}

void ARBInstancedArrays::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBInstancedArraysEntryPoints,
                    std::size(__ARBInstancedArraysEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBMatrixPalette Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBMatrixPalette::ARBMatrixPalette()
{
    std::for_each_n(__ARBMatrixPaletteEntryPoints,
                    std::size(__ARBMatrixPaletteEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBMatrixPalette::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_matrix_palette");
}

void ARBMatrixPalette::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBMatrixPaletteEntryPoints,
                    std::size(__ARBMatrixPaletteEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBMultisample::ARBMultisample()
{
    std::for_each_n(__ARBMultisampleEntryPoints,
                    std::size(__ARBMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_multisample");
}

void ARBMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBMultisampleEntryPoints,
                    std::size(__ARBMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBMultitexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBMultitexture::ARBMultitexture()
{
    std::for_each_n(__ARBMultitextureEntryPoints,
                    std::size(__ARBMultitextureEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBMultitexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_multitexture");
}

void ARBMultitexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBMultitextureEntryPoints,
                    std::size(__ARBMultitextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBOcclusionQuery Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBOcclusionQuery::ARBOcclusionQuery()
{
    std::for_each_n(__ARBOcclusionQueryEntryPoints,
                    std::size(__ARBOcclusionQueryEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBOcclusionQuery::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_occlusion_query");
}

void ARBOcclusionQuery::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBOcclusionQueryEntryPoints,
                    std::size(__ARBOcclusionQueryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBParallelShaderCompile Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBParallelShaderCompile::ARBParallelShaderCompile()
{
    std::for_each_n(__ARBParallelShaderCompileEntryPoints,
                    std::size(__ARBParallelShaderCompileEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBParallelShaderCompile::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_parallel_shader_compile");
}

void ARBParallelShaderCompile::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBParallelShaderCompileEntryPoints,
                    std::size(__ARBParallelShaderCompileEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBPointParameters Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBPointParameters::ARBPointParameters()
{
    std::for_each_n(__ARBPointParametersEntryPoints,
                    std::size(__ARBPointParametersEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBPointParameters::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_point_parameters");
}

void ARBPointParameters::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBPointParametersEntryPoints,
                    std::size(__ARBPointParametersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBRobustness Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBRobustness::ARBRobustness()
{
    std::for_each_n(__ARBRobustnessEntryPoints,
                    std::size(__ARBRobustnessEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBRobustness::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_robustness");
}

void ARBRobustness::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBRobustnessEntryPoints,
                    std::size(__ARBRobustnessEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBSampleLocations Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBSampleLocations::ARBSampleLocations()
{
    std::for_each_n(__ARBSampleLocationsEntryPoints,
                    std::size(__ARBSampleLocationsEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBSampleLocations::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_sample_locations");
}

void ARBSampleLocations::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBSampleLocationsEntryPoints,
                    std::size(__ARBSampleLocationsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBSampleShading Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBSampleShading::ARBSampleShading()
{
    std::for_each_n(__ARBSampleShadingEntryPoints,
                    std::size(__ARBSampleShadingEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBSampleShading::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_sample_shading");
}

void ARBSampleShading::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBSampleShadingEntryPoints,
                    std::size(__ARBSampleShadingEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBShaderObjects Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBShaderObjects::ARBShaderObjects()
{
    std::for_each_n(__ARBShaderObjectsEntryPoints,
                    std::size(__ARBShaderObjectsEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBShaderObjects::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_shader_objects");
}

void ARBShaderObjects::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBShaderObjectsEntryPoints,
                    std::size(__ARBShaderObjectsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBShadingLanguageInclude Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBShadingLanguageInclude::ARBShadingLanguageInclude()
{
    std::for_each_n(__ARBShadingLanguageIncludeEntryPoints,
                    std::size(__ARBShadingLanguageIncludeEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBShadingLanguageInclude::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_shading_language_include");
}

void ARBShadingLanguageInclude::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBShadingLanguageIncludeEntryPoints,
                    std::size(__ARBShadingLanguageIncludeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBSparseBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBSparseBuffer::ARBSparseBuffer()
{
    std::for_each_n(__ARBSparseBufferEntryPoints,
                    std::size(__ARBSparseBufferEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBSparseBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_sparse_buffer");
}

void ARBSparseBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBSparseBufferEntryPoints,
                    std::size(__ARBSparseBufferEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBSparseTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBSparseTexture::ARBSparseTexture()
{
    std::for_each_n(__ARBSparseTextureEntryPoints,
                    std::size(__ARBSparseTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBSparseTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_sparse_texture");
}

void ARBSparseTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBSparseTextureEntryPoints,
                    std::size(__ARBSparseTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBTextureBufferObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBTextureBufferObject::ARBTextureBufferObject()
{
    std::for_each_n(__ARBTextureBufferObjectEntryPoints,
                    std::size(__ARBTextureBufferObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBTextureBufferObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_texture_buffer_object");
}

void ARBTextureBufferObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBTextureBufferObjectEntryPoints,
                    std::size(__ARBTextureBufferObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBTextureCompression Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBTextureCompression::ARBTextureCompression()
{
    std::for_each_n(__ARBTextureCompressionEntryPoints,
                    std::size(__ARBTextureCompressionEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBTextureCompression::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_texture_compression");
}

void ARBTextureCompression::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBTextureCompressionEntryPoints,
                    std::size(__ARBTextureCompressionEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBTransposeMatrix Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBTransposeMatrix::ARBTransposeMatrix()
{
    std::for_each_n(__ARBTransposeMatrixEntryPoints,
                    std::size(__ARBTransposeMatrixEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBTransposeMatrix::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_transpose_matrix");
}

void ARBTransposeMatrix::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBTransposeMatrixEntryPoints,
                    std::size(__ARBTransposeMatrixEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexBlend Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBVertexBlend::ARBVertexBlend()
{
    std::for_each_n(__ARBVertexBlendEntryPoints,
                    std::size(__ARBVertexBlendEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBVertexBlend::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_vertex_blend");
}

void ARBVertexBlend::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBVertexBlendEntryPoints,
                    std::size(__ARBVertexBlendEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexBufferObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBVertexBufferObject::ARBVertexBufferObject()
{
    std::for_each_n(__ARBVertexBufferObjectEntryPoints,
                    std::size(__ARBVertexBufferObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBVertexBufferObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_vertex_buffer_object");
}

void ARBVertexBufferObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBVertexBufferObjectEntryPoints,
                    std::size(__ARBVertexBufferObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexProgram Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBVertexProgram::ARBVertexProgram()
{
    std::for_each_n(__ARBVertexProgramEntryPoints,
                    std::size(__ARBVertexProgramEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBVertexProgram::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_vertex_program");
}

void ARBVertexProgram::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBVertexProgramEntryPoints,
                    std::size(__ARBVertexProgramEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexShader Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBVertexShader::ARBVertexShader()
{
    std::for_each_n(__ARBVertexShaderEntryPoints,
                    std::size(__ARBVertexShaderEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBVertexShader::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_vertex_shader");
}

void ARBVertexShader::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBVertexShaderEntryPoints,
                    std::size(__ARBVertexShaderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBViewportArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBViewportArray::ARBViewportArray()
{
    std::for_each_n(__ARBViewportArrayEntryPoints,
                    std::size(__ARBViewportArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBViewportArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_viewport_array");
}

void ARBViewportArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBViewportArrayEntryPoints,
                    std::size(__ARBViewportArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBWindowPos Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBWindowPos::ARBWindowPos()
{
    std::for_each_n(__ARBWindowPosEntryPoints,
                    std::size(__ARBWindowPosEntryPoints),
                    ClearEntryPoint(this));
}

bool ARBWindowPos::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ARB_window_pos");
}

void ARBWindowPos::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBWindowPosEntryPoints,
                    std::size(__ARBWindowPosEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl

#ifdef _WIN32
namespace wgl {
namespace {

static const gl::EntryOffset __ARBBufferRegionEntryPoints[] = {
    { offsetof(ARBBufferRegion, wglCreateBufferRegion), "wglCreateBufferRegionARB" },
    { offsetof(ARBBufferRegion, wglDeleteBufferRegion), "wglDeleteBufferRegionARB" },
    { offsetof(ARBBufferRegion, wglRestoreBufferRegion), "wglRestoreBufferRegionARB" },
    { offsetof(ARBBufferRegion, wglSaveBufferRegion), "wglSaveBufferRegionARB" },
};

static const gl::EntryOffset __ARBCreateContextEntryPoints[] = {
    { offsetof(ARBCreateContext, wglCreateContextAttribs), "wglCreateContextAttribsARB" },
};

static const gl::EntryOffset __ARBExtensionsStringEntryPoints[] = {
    { offsetof(ARBExtensionsString, wglGetExtensionsString), "wglGetExtensionsStringARB" },
};

static const gl::EntryOffset __ARBMakeCurrentReadEntryPoints[] = {
    { offsetof(ARBMakeCurrentRead, wglGetCurrentReadDC), "wglGetCurrentReadDCARB" },
    { offsetof(ARBMakeCurrentRead, wglMakeContextCurrent), "wglMakeContextCurrentARB" },
};

static const gl::EntryOffset __ARBPbufferEntryPoints[] = {
    { offsetof(ARBPbuffer, wglCreatePbuffer), "wglCreatePbufferARB" },
    { offsetof(ARBPbuffer, wglDestroyPbuffer), "wglDestroyPbufferARB" },
    { offsetof(ARBPbuffer, wglGetPbufferDC), "wglGetPbufferDCARB" },
    { offsetof(ARBPbuffer, wglQueryPbuffer), "wglQueryPbufferARB" },
    { offsetof(ARBPbuffer, wglReleasePbufferDC), "wglReleasePbufferDCARB" },
};

static const gl::EntryOffset __ARBPixelFormatEntryPoints[] = {
    { offsetof(ARBPixelFormat, wglChoosePixelFormat), "wglChoosePixelFormatARB" },
    { offsetof(ARBPixelFormat, wglGetPixelFormatAttribfv), "wglGetPixelFormatAttribfvARB" },
    { offsetof(ARBPixelFormat, wglGetPixelFormatAttribiv), "wglGetPixelFormatAttribivARB" },
};

static const gl::EntryOffset __ARBRenderTextureEntryPoints[] = {
    { offsetof(ARBRenderTexture, wglBindTexImage), "wglBindTexImageARB" },
    { offsetof(ARBRenderTexture, wglReleaseTexImage), "wglReleaseTexImageARB" },
    { offsetof(ARBRenderTexture, wglSetPbufferAttrib), "wglSetPbufferAttribARB" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ARBBufferRegion Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBBufferRegion::ARBBufferRegion()
{
    std::for_each_n(__ARBBufferRegionEntryPoints,
                    std::size(__ARBBufferRegionEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBBufferRegion::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_buffer_region");
}

void ARBBufferRegion::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBBufferRegionEntryPoints,
                    std::size(__ARBBufferRegionEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBCreateContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBCreateContext::ARBCreateContext()
{
    std::for_each_n(__ARBCreateContextEntryPoints,
                    std::size(__ARBCreateContextEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBCreateContext::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_create_context");
}

void ARBCreateContext::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBCreateContextEntryPoints,
                    std::size(__ARBCreateContextEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBExtensionsString Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBExtensionsString::ARBExtensionsString()
{
    std::for_each_n(__ARBExtensionsStringEntryPoints,
                    std::size(__ARBExtensionsStringEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBExtensionsString::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_extensions_string");
}

void ARBExtensionsString::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBExtensionsStringEntryPoints,
                    std::size(__ARBExtensionsStringEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBMakeCurrentRead Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBMakeCurrentRead::ARBMakeCurrentRead()
{
    std::for_each_n(__ARBMakeCurrentReadEntryPoints,
                    std::size(__ARBMakeCurrentReadEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBMakeCurrentRead::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_make_current_read");
}

void ARBMakeCurrentRead::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBMakeCurrentReadEntryPoints,
                    std::size(__ARBMakeCurrentReadEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBPbuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBPbuffer::ARBPbuffer()
{
    std::for_each_n(__ARBPbufferEntryPoints,
                    std::size(__ARBPbufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBPbuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_pbuffer");
}

void ARBPbuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBPbufferEntryPoints,
                    std::size(__ARBPbufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBPixelFormat Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBPixelFormat::ARBPixelFormat()
{
    std::for_each_n(__ARBPixelFormatEntryPoints,
                    std::size(__ARBPixelFormatEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBPixelFormat::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_pixel_format");
}

void ARBPixelFormat::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBPixelFormatEntryPoints,
                    std::size(__ARBPixelFormatEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBRenderTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBRenderTexture::ARBRenderTexture()
{
    std::for_each_n(__ARBRenderTextureEntryPoints,
                    std::size(__ARBRenderTextureEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBRenderTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_ARB_render_texture");
}

void ARBRenderTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBRenderTextureEntryPoints,
                    std::size(__ARBRenderTextureEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __ARBCreateContextEntryPoints[] = {
    { offsetof(ARBCreateContext, glXCreateContextAttribs), "glXCreateContextAttribsARB" },
};

static const gl::EntryOffset __ARBGetProcAddressEntryPoints[] = {
    { offsetof(ARBGetProcAddress, glXGetProcAddress), "glXGetProcAddressARB" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ARBCreateContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBCreateContext::ARBCreateContext()
{
    std::for_each_n(__ARBCreateContextEntryPoints,
                    std::size(__ARBCreateContextEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBCreateContext::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_ARB_create_context");
}

void ARBCreateContext::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBCreateContextEntryPoints,
                    std::size(__ARBCreateContextEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ARBGetProcAddress Member Definitions
////////////////////////////////////////////////////////////////////////////////
ARBGetProcAddress::ARBGetProcAddress()
{
    std::for_each_n(__ARBGetProcAddressEntryPoints,
                    std::size(__ARBGetProcAddressEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool ARBGetProcAddress::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_ARB_get_proc_address");
}

void ARBGetProcAddress::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ARBGetProcAddressEntryPoints,
                    std::size(__ARBGetProcAddressEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

