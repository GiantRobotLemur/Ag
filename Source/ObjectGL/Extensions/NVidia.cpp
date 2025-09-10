//! @file ObjectGL/Extensions/NVidia.cpp
//! @brief The definition of nVidia-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/NVidia.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __NVXConditionalRenderEntryPoints[] = {
    { offsetof(NVXConditionalRender, glBeginConditionalRender), "glBeginConditionalRenderNVX" },
    { offsetof(NVXConditionalRender, glEndConditionalRender), "glEndConditionalRenderNVX" },
};

static const EntryOffset __NVXGPUMULTICAST2EntryPoints[] = {
    { offsetof(NVXGPUMULTICAST2, glAsyncCopyBufferSubData), "glAsyncCopyBufferSubDataNVX" },
    { offsetof(NVXGPUMULTICAST2, glAsyncCopyImageSubData), "glAsyncCopyImageSubDataNVX" },
    { offsetof(NVXGPUMULTICAST2, glMulticastScissorArrayv), "glMulticastScissorArrayvNVX" },
    { offsetof(NVXGPUMULTICAST2, glMulticastViewportArrayv), "glMulticastViewportArrayvNVX" },
    { offsetof(NVXGPUMULTICAST2, glMulticastViewportPositionWScale), "glMulticastViewportPositionWScaleNVX" },
    { offsetof(NVXGPUMULTICAST2, glUploadGpuMask), "glUploadGpuMaskNVX" },
};

static const EntryOffset __NVXLinkedGPUMulticastEntryPoints[] = {
    { offsetof(NVXLinkedGPUMulticast, glLGPUCopyImageSubData), "glLGPUCopyImageSubDataNVX" },
    { offsetof(NVXLinkedGPUMulticast, glLGPUInterlock), "glLGPUInterlockNVX" },
    { offsetof(NVXLinkedGPUMulticast, glLGPUNamedBufferSubData), "glLGPUNamedBufferSubDataNVX" },
};

static const EntryOffset __NVXProgressFenceEntryPoints[] = {
    { offsetof(NVXProgressFence, glClientWaitSemaphoreui64), "glClientWaitSemaphoreui64NVX" },
    { offsetof(NVXProgressFence, glCreateProgressFence), "glCreateProgressFenceNVX" },
    { offsetof(NVXProgressFence, glSignalSemaphoreui64), "glSignalSemaphoreui64NVX" },
    { offsetof(NVXProgressFence, glWaitSemaphoreui64), "glWaitSemaphoreui64NVX" },
};

static const EntryOffset __NVAlphaToCoverageDitherControlEntryPoints[] = {
    { offsetof(NVAlphaToCoverageDitherControl, glAlphaToCoverageDitherControl), "glAlphaToCoverageDitherControlNV" },
};

static const EntryOffset __NVBindlessMultiDrawIndirectEntryPoints[] = {
    { offsetof(NVBindlessMultiDrawIndirect, glMultiDrawArraysIndirectBindless), "glMultiDrawArraysIndirectBindlessNV" },
    { offsetof(NVBindlessMultiDrawIndirect, glMultiDrawElementsIndirectBindless), "glMultiDrawElementsIndirectBindlessNV" },
};

static const EntryOffset __NVBindlessMultiDrawIndirectCountEntryPoints[] = {
    { offsetof(NVBindlessMultiDrawIndirectCount, glMultiDrawArraysIndirectBindlessCount), "glMultiDrawArraysIndirectBindlessCountNV" },
    { offsetof(NVBindlessMultiDrawIndirectCount, glMultiDrawElementsIndirectBindlessCount), "glMultiDrawElementsIndirectBindlessCountNV" },
};

static const EntryOffset __NVBindlessTextureEntryPoints[] = {
    { offsetof(NVBindlessTexture, glGetImageHandle), "glGetImageHandleNV" },
    { offsetof(NVBindlessTexture, glGetTextureHandle), "glGetTextureHandleNV" },
    { offsetof(NVBindlessTexture, glGetTextureSamplerHandle), "glGetTextureSamplerHandleNV" },
    { offsetof(NVBindlessTexture, glIsImageHandleResident), "glIsImageHandleResidentNV" },
    { offsetof(NVBindlessTexture, glIsTextureHandleResident), "glIsTextureHandleResidentNV" },
    { offsetof(NVBindlessTexture, glMakeImageHandleNonResident), "glMakeImageHandleNonResidentNV" },
    { offsetof(NVBindlessTexture, glMakeImageHandleResident), "glMakeImageHandleResidentNV" },
    { offsetof(NVBindlessTexture, glMakeTextureHandleNonResident), "glMakeTextureHandleNonResidentNV" },
    { offsetof(NVBindlessTexture, glMakeTextureHandleResident), "glMakeTextureHandleResidentNV" },
    { offsetof(NVBindlessTexture, glProgramUniformHandleui64), "glProgramUniformHandleui64NV" },
    { offsetof(NVBindlessTexture, glProgramUniformHandleui64v), "glProgramUniformHandleui64vNV" },
    { offsetof(NVBindlessTexture, glUniformHandleui64), "glUniformHandleui64NV" },
    { offsetof(NVBindlessTexture, glUniformHandleui64v), "glUniformHandleui64vNV" },
};

static const EntryOffset __NVBlendEquationAdvancedEntryPoints[] = {
    { offsetof(NVBlendEquationAdvanced, glBlendBarrier), "glBlendBarrierNV" },
    { offsetof(NVBlendEquationAdvanced, glBlendParameteri), "glBlendParameteriNV" },
};

static const EntryOffset __NVClipSpaceWScalingEntryPoints[] = {
    { offsetof(NVClipSpaceWScaling, glViewportPositionWScale), "glViewportPositionWScaleNV" },
};

static const EntryOffset __NVCommandListEntryPoints[] = {
    { offsetof(NVCommandList, glCallCommandList), "glCallCommandListNV" },
    { offsetof(NVCommandList, glCommandListSegments), "glCommandListSegmentsNV" },
    { offsetof(NVCommandList, glCompileCommandList), "glCompileCommandListNV" },
    { offsetof(NVCommandList, glCreateCommandLists), "glCreateCommandListsNV" },
    { offsetof(NVCommandList, glCreateStates), "glCreateStatesNV" },
    { offsetof(NVCommandList, glDeleteCommandLists), "glDeleteCommandListsNV" },
    { offsetof(NVCommandList, glDeleteStates), "glDeleteStatesNV" },
    { offsetof(NVCommandList, glDrawCommandsAddress), "glDrawCommandsAddressNV" },
    { offsetof(NVCommandList, glDrawCommands), "glDrawCommandsNV" },
    { offsetof(NVCommandList, glDrawCommandsStatesAddress), "glDrawCommandsStatesAddressNV" },
    { offsetof(NVCommandList, glDrawCommandsStates), "glDrawCommandsStatesNV" },
    { offsetof(NVCommandList, glGetCommandHeader), "glGetCommandHeaderNV" },
    { offsetof(NVCommandList, glGetStageIndex), "glGetStageIndexNV" },
    { offsetof(NVCommandList, glIsCommandList), "glIsCommandListNV" },
    { offsetof(NVCommandList, glIsState), "glIsStateNV" },
    { offsetof(NVCommandList, glListDrawCommandsStatesClient), "glListDrawCommandsStatesClientNV" },
    { offsetof(NVCommandList, glStateCapture), "glStateCaptureNV" },
};

static const EntryOffset __NVConditionalRenderEntryPoints[] = {
    { offsetof(NVConditionalRender, glBeginConditionalRender), "glBeginConditionalRenderNV" },
    { offsetof(NVConditionalRender, glEndConditionalRender), "glEndConditionalRenderNV" },
};

static const EntryOffset __NVConservativeRasterEntryPoints[] = {
    { offsetof(NVConservativeRaster, glSubpixelPrecisionBias), "glSubpixelPrecisionBiasNV" },
};

static const EntryOffset __NVConservativeRasterDilateEntryPoints[] = {
    { offsetof(NVConservativeRasterDilate, glConservativeRasterParameterf), "glConservativeRasterParameterfNV" },
};

static const EntryOffset __NVConservativeRasterPreSnapTrianglesEntryPoints[] = {
    { offsetof(NVConservativeRasterPreSnapTriangles, glConservativeRasterParameteri), "glConservativeRasterParameteriNV" },
};

static const EntryOffset __NVCopyImageEntryPoints[] = {
    { offsetof(NVCopyImage, glCopyImageSubData), "glCopyImageSubDataNV" },
};

static const EntryOffset __NVDepthBufferFloatEntryPoints[] = {
    { offsetof(NVDepthBufferFloat, glClearDepthd), "glClearDepthdNV" },
    { offsetof(NVDepthBufferFloat, glDepthBoundsd), "glDepthBoundsdNV" },
    { offsetof(NVDepthBufferFloat, glDepthRanged), "glDepthRangedNV" },
};

static const EntryOffset __NVDrawTextureEntryPoints[] = {
    { offsetof(NVDrawTexture, glDrawTexture), "glDrawTextureNV" },
};

static const EntryOffset __NVDrawVulkanImageEntryPoints[] = {
    { offsetof(NVDrawVulkanImage, glDrawVkImage), "glDrawVkImageNV" },
    { offsetof(NVDrawVulkanImage, glGetVkProcAddr), "glGetVkProcAddrNV" },
    { offsetof(NVDrawVulkanImage, glSignalVkFence), "glSignalVkFenceNV" },
    { offsetof(NVDrawVulkanImage, glSignalVkSemaphore), "glSignalVkSemaphoreNV" },
    { offsetof(NVDrawVulkanImage, glWaitVkSemaphore), "glWaitVkSemaphoreNV" },
};

static const EntryOffset __NVEvaluatorsEntryPoints[] = {
    { offsetof(NVEvaluators, glEvalMaps), "glEvalMapsNV" },
    { offsetof(NVEvaluators, glGetMapAttribParameterfv), "glGetMapAttribParameterfvNV" },
    { offsetof(NVEvaluators, glGetMapAttribParameteriv), "glGetMapAttribParameterivNV" },
    { offsetof(NVEvaluators, glGetMapControlPoints), "glGetMapControlPointsNV" },
    { offsetof(NVEvaluators, glGetMapParameterfv), "glGetMapParameterfvNV" },
    { offsetof(NVEvaluators, glGetMapParameteriv), "glGetMapParameterivNV" },
    { offsetof(NVEvaluators, glMapControlPoints), "glMapControlPointsNV" },
    { offsetof(NVEvaluators, glMapParameterfv), "glMapParameterfvNV" },
    { offsetof(NVEvaluators, glMapParameteriv), "glMapParameterivNV" },
};

static const EntryOffset __NVExplicitMultisampleEntryPoints[] = {
    { offsetof(NVExplicitMultisample, glGetMultisamplefv), "glGetMultisamplefvNV" },
    { offsetof(NVExplicitMultisample, glSampleMaskIndexed), "glSampleMaskIndexedNV" },
    { offsetof(NVExplicitMultisample, glTexRenderbuffer), "glTexRenderbufferNV" },
};

static const EntryOffset __NVFenceEntryPoints[] = {
    { offsetof(NVFence, glDeleteFences), "glDeleteFencesNV" },
    { offsetof(NVFence, glFinishFence), "glFinishFenceNV" },
    { offsetof(NVFence, glGenFences), "glGenFencesNV" },
    { offsetof(NVFence, glGetFenceiv), "glGetFenceivNV" },
    { offsetof(NVFence, glIsFence), "glIsFenceNV" },
    { offsetof(NVFence, glSetFence), "glSetFenceNV" },
    { offsetof(NVFence, glTestFence), "glTestFenceNV" },
};

static const EntryOffset __NVFragmentCoverageToColorEntryPoints[] = {
    { offsetof(NVFragmentCoverageToColor, glFragmentCoverageColor), "glFragmentCoverageColorNV" },
};

static const EntryOffset __NVFragmentProgramEntryPoints[] = {
    { offsetof(NVFragmentProgram, glGetProgramNamedParameterdv), "glGetProgramNamedParameterdvNV" },
    { offsetof(NVFragmentProgram, glGetProgramNamedParameterfv), "glGetProgramNamedParameterfvNV" },
    { offsetof(NVFragmentProgram, glProgramNamedParameter4d), "glProgramNamedParameter4dNV" },
    { offsetof(NVFragmentProgram, glProgramNamedParameter4dv), "glProgramNamedParameter4dvNV" },
    { offsetof(NVFragmentProgram, glProgramNamedParameter4f), "glProgramNamedParameter4fNV" },
    { offsetof(NVFragmentProgram, glProgramNamedParameter4fv), "glProgramNamedParameter4fvNV" },
};

static const EntryOffset __NVFramebufferMixedSamplesEntryPoints[] = {
    { offsetof(NVFramebufferMixedSamples, glCoverageModulation), "glCoverageModulationNV" },
    { offsetof(NVFramebufferMixedSamples, glCoverageModulationTable), "glCoverageModulationTableNV" },
    { offsetof(NVFramebufferMixedSamples, glGetCoverageModulationTable), "glGetCoverageModulationTableNV" },
};

static const EntryOffset __NVFramebufferMultisampleCoverageEntryPoints[] = {
    { offsetof(NVFramebufferMultisampleCoverage, glRenderbufferStorageMultisampleCoverage), "glRenderbufferStorageMultisampleCoverageNV" },
};

static const EntryOffset __NVGeometryPROGRAM4EntryPoints[] = {
    { offsetof(NVGeometryPROGRAM4, glFramebufferTexture), "glFramebufferTextureEXT" },
    { offsetof(NVGeometryPROGRAM4, glFramebufferTextureFace), "glFramebufferTextureFaceEXT" },
    { offsetof(NVGeometryPROGRAM4, glProgramVertexLimit), "glProgramVertexLimitNV" },
};

static const EntryOffset __NVGPUMulticastEntryPoints[] = {
    { offsetof(NVGPUMulticast, glMulticastBarrier), "glMulticastBarrierNV" },
    { offsetof(NVGPUMulticast, glMulticastBlitFramebuffer), "glMulticastBlitFramebufferNV" },
    { offsetof(NVGPUMulticast, glMulticastBufferSubData), "glMulticastBufferSubDataNV" },
    { offsetof(NVGPUMulticast, glMulticastCopyBufferSubData), "glMulticastCopyBufferSubDataNV" },
    { offsetof(NVGPUMulticast, glMulticastCopyImageSubData), "glMulticastCopyImageSubDataNV" },
    { offsetof(NVGPUMulticast, glMulticastFramebufferSampleLocationsfv), "glMulticastFramebufferSampleLocationsfvNV" },
    { offsetof(NVGPUMulticast, glMulticastGetQueryObjecti64v), "glMulticastGetQueryObjecti64vNV" },
    { offsetof(NVGPUMulticast, glMulticastGetQueryObjectiv), "glMulticastGetQueryObjectivNV" },
    { offsetof(NVGPUMulticast, glMulticastGetQueryObjectui64v), "glMulticastGetQueryObjectui64vNV" },
    { offsetof(NVGPUMulticast, glMulticastGetQueryObjectuiv), "glMulticastGetQueryObjectuivNV" },
    { offsetof(NVGPUMulticast, glMulticastWaitSync), "glMulticastWaitSyncNV" },
    { offsetof(NVGPUMulticast, glRenderGpuMask), "glRenderGpuMaskNV" },
};

static const EntryOffset __NVGPUPROGRAM4EntryPoints[] = {
    { offsetof(NVGPUPROGRAM4, glGetProgramEnvParameterIiv), "glGetProgramEnvParameterIivNV" },
    { offsetof(NVGPUPROGRAM4, glGetProgramEnvParameterIuiv), "glGetProgramEnvParameterIuivNV" },
    { offsetof(NVGPUPROGRAM4, glGetProgramLocalParameterIiv), "glGetProgramLocalParameterIivNV" },
    { offsetof(NVGPUPROGRAM4, glGetProgramLocalParameterIuiv), "glGetProgramLocalParameterIuivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParameterI4i), "glProgramEnvParameterI4iNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParameterI4iv), "glProgramEnvParameterI4ivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParameterI4ui), "glProgramEnvParameterI4uiNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParameterI4uiv), "glProgramEnvParameterI4uivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParametersI4iv), "glProgramEnvParametersI4ivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramEnvParametersI4uiv), "glProgramEnvParametersI4uivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParameterI4i), "glProgramLocalParameterI4iNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParameterI4iv), "glProgramLocalParameterI4ivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParameterI4ui), "glProgramLocalParameterI4uiNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParameterI4uiv), "glProgramLocalParameterI4uivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParametersI4iv), "glProgramLocalParametersI4ivNV" },
    { offsetof(NVGPUPROGRAM4, glProgramLocalParametersI4uiv), "glProgramLocalParametersI4uivNV" },
};

static const EntryOffset __NVGPUPROGRAM5EntryPoints[] = {
    { offsetof(NVGPUPROGRAM5, glGetProgramSubroutineParameteruiv), "glGetProgramSubroutineParameteruivNV" },
    { offsetof(NVGPUPROGRAM5, glProgramSubroutineParametersuiv), "glProgramSubroutineParametersuivNV" },
};

static const EntryOffset __NVHalfFloatEntryPoints[] = {
    { offsetof(NVHalfFloat, glColor3h), "glColor3hNV" },
    { offsetof(NVHalfFloat, glColor3hv), "glColor3hvNV" },
    { offsetof(NVHalfFloat, glColor4h), "glColor4hNV" },
    { offsetof(NVHalfFloat, glColor4hv), "glColor4hvNV" },
    { offsetof(NVHalfFloat, glFogCoordh), "glFogCoordhNV" },
    { offsetof(NVHalfFloat, glFogCoordhv), "glFogCoordhvNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord1h), "glMultiTexCoord1hNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord1hv), "glMultiTexCoord1hvNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord2h), "glMultiTexCoord2hNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord2hv), "glMultiTexCoord2hvNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord3h), "glMultiTexCoord3hNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord3hv), "glMultiTexCoord3hvNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord4h), "glMultiTexCoord4hNV" },
    { offsetof(NVHalfFloat, glMultiTexCoord4hv), "glMultiTexCoord4hvNV" },
    { offsetof(NVHalfFloat, glNormal3h), "glNormal3hNV" },
    { offsetof(NVHalfFloat, glNormal3hv), "glNormal3hvNV" },
    { offsetof(NVHalfFloat, glSecondaryColor3h), "glSecondaryColor3hNV" },
    { offsetof(NVHalfFloat, glSecondaryColor3hv), "glSecondaryColor3hvNV" },
    { offsetof(NVHalfFloat, glTexCoord1h), "glTexCoord1hNV" },
    { offsetof(NVHalfFloat, glTexCoord1hv), "glTexCoord1hvNV" },
    { offsetof(NVHalfFloat, glTexCoord2h), "glTexCoord2hNV" },
    { offsetof(NVHalfFloat, glTexCoord2hv), "glTexCoord2hvNV" },
    { offsetof(NVHalfFloat, glTexCoord3h), "glTexCoord3hNV" },
    { offsetof(NVHalfFloat, glTexCoord3hv), "glTexCoord3hvNV" },
    { offsetof(NVHalfFloat, glTexCoord4h), "glTexCoord4hNV" },
    { offsetof(NVHalfFloat, glTexCoord4hv), "glTexCoord4hvNV" },
    { offsetof(NVHalfFloat, glVertex2h), "glVertex2hNV" },
    { offsetof(NVHalfFloat, glVertex2hv), "glVertex2hvNV" },
    { offsetof(NVHalfFloat, glVertex3h), "glVertex3hNV" },
    { offsetof(NVHalfFloat, glVertex3hv), "glVertex3hvNV" },
    { offsetof(NVHalfFloat, glVertex4h), "glVertex4hNV" },
    { offsetof(NVHalfFloat, glVertex4hv), "glVertex4hvNV" },
    { offsetof(NVHalfFloat, glVertexAttrib1h), "glVertexAttrib1hNV" },
    { offsetof(NVHalfFloat, glVertexAttrib1hv), "glVertexAttrib1hvNV" },
    { offsetof(NVHalfFloat, glVertexAttrib2h), "glVertexAttrib2hNV" },
    { offsetof(NVHalfFloat, glVertexAttrib2hv), "glVertexAttrib2hvNV" },
    { offsetof(NVHalfFloat, glVertexAttrib3h), "glVertexAttrib3hNV" },
    { offsetof(NVHalfFloat, glVertexAttrib3hv), "glVertexAttrib3hvNV" },
    { offsetof(NVHalfFloat, glVertexAttrib4h), "glVertexAttrib4hNV" },
    { offsetof(NVHalfFloat, glVertexAttrib4hv), "glVertexAttrib4hvNV" },
    { offsetof(NVHalfFloat, glVertexAttribs1hv), "glVertexAttribs1hvNV" },
    { offsetof(NVHalfFloat, glVertexAttribs2hv), "glVertexAttribs2hvNV" },
    { offsetof(NVHalfFloat, glVertexAttribs3hv), "glVertexAttribs3hvNV" },
    { offsetof(NVHalfFloat, glVertexAttribs4hv), "glVertexAttribs4hvNV" },
    { offsetof(NVHalfFloat, glVertexWeighth), "glVertexWeighthNV" },
    { offsetof(NVHalfFloat, glVertexWeighthv), "glVertexWeighthvNV" },
};

static const EntryOffset __NVInternalformatSampleQueryEntryPoints[] = {
    { offsetof(NVInternalformatSampleQuery, glGetInternalformatSampleiv), "glGetInternalformatSampleivNV" },
};

static const EntryOffset __NVMemoryAttachmentEntryPoints[] = {
    { offsetof(NVMemoryAttachment, glBufferAttachMemory), "glBufferAttachMemoryNV" },
    { offsetof(NVMemoryAttachment, glGetMemoryObjectDetachedResourcesuiv), "glGetMemoryObjectDetachedResourcesuivNV" },
    { offsetof(NVMemoryAttachment, glNamedBufferAttachMemory), "glNamedBufferAttachMemoryNV" },
    { offsetof(NVMemoryAttachment, glResetMemoryObjectParameter), "glResetMemoryObjectParameterNV" },
    { offsetof(NVMemoryAttachment, glTexAttachMemory), "glTexAttachMemoryNV" },
    { offsetof(NVMemoryAttachment, glTextureAttachMemory), "glTextureAttachMemoryNV" },
};

static const EntryOffset __NVMemoryObjectSparseEntryPoints[] = {
    { offsetof(NVMemoryObjectSparse, glBufferPageCommitmentMem), "glBufferPageCommitmentMemNV" },
    { offsetof(NVMemoryObjectSparse, glNamedBufferPageCommitmentMem), "glNamedBufferPageCommitmentMemNV" },
    { offsetof(NVMemoryObjectSparse, glTexPageCommitmentMem), "glTexPageCommitmentMemNV" },
    { offsetof(NVMemoryObjectSparse, glTexturePageCommitmentMem), "glTexturePageCommitmentMemNV" },
};

static const EntryOffset __NVMeshShaderEntryPoints[] = {
    { offsetof(NVMeshShader, glDrawMeshTasksIndirect), "glDrawMeshTasksIndirectNV" },
    { offsetof(NVMeshShader, glDrawMeshTasks), "glDrawMeshTasksNV" },
    { offsetof(NVMeshShader, glMultiDrawMeshTasksIndirectCount), "glMultiDrawMeshTasksIndirectCountNV" },
    { offsetof(NVMeshShader, glMultiDrawMeshTasksIndirect), "glMultiDrawMeshTasksIndirectNV" },
};

static const EntryOffset __NVOcclusionQueryEntryPoints[] = {
    { offsetof(NVOcclusionQuery, glBeginOcclusionQuery), "glBeginOcclusionQueryNV" },
    { offsetof(NVOcclusionQuery, glDeleteOcclusionQueries), "glDeleteOcclusionQueriesNV" },
    { offsetof(NVOcclusionQuery, glEndOcclusionQuery), "glEndOcclusionQueryNV" },
    { offsetof(NVOcclusionQuery, glGenOcclusionQueries), "glGenOcclusionQueriesNV" },
    { offsetof(NVOcclusionQuery, glGetOcclusionQueryiv), "glGetOcclusionQueryivNV" },
    { offsetof(NVOcclusionQuery, glGetOcclusionQueryuiv), "glGetOcclusionQueryuivNV" },
    { offsetof(NVOcclusionQuery, glIsOcclusionQuery), "glIsOcclusionQueryNV" },
};

static const EntryOffset __NVParameterBufferObjectEntryPoints[] = {
    { offsetof(NVParameterBufferObject, glProgramBufferParametersIiv), "glProgramBufferParametersIivNV" },
    { offsetof(NVParameterBufferObject, glProgramBufferParametersIuiv), "glProgramBufferParametersIuivNV" },
    { offsetof(NVParameterBufferObject, glProgramBufferParametersfv), "glProgramBufferParametersfvNV" },
};

static const EntryOffset __NVPathRenderingEntryPoints[] = {
    { offsetof(NVPathRendering, glCopyPath), "glCopyPathNV" },
    { offsetof(NVPathRendering, glCoverFillPathInstanced), "glCoverFillPathInstancedNV" },
    { offsetof(NVPathRendering, glCoverFillPath), "glCoverFillPathNV" },
    { offsetof(NVPathRendering, glCoverStrokePathInstanced), "glCoverStrokePathInstancedNV" },
    { offsetof(NVPathRendering, glCoverStrokePath), "glCoverStrokePathNV" },
    { offsetof(NVPathRendering, glDeletePaths), "glDeletePathsNV" },
    { offsetof(NVPathRendering, glGenPaths), "glGenPathsNV" },
    { offsetof(NVPathRendering, glGetPathCommands), "glGetPathCommandsNV" },
    { offsetof(NVPathRendering, glGetPathCoords), "glGetPathCoordsNV" },
    { offsetof(NVPathRendering, glGetPathDashArray), "glGetPathDashArrayNV" },
    { offsetof(NVPathRendering, glGetPathLength), "glGetPathLengthNV" },
    { offsetof(NVPathRendering, glGetPathMetricRange), "glGetPathMetricRangeNV" },
    { offsetof(NVPathRendering, glGetPathMetrics), "glGetPathMetricsNV" },
    { offsetof(NVPathRendering, glGetPathParameterfv), "glGetPathParameterfvNV" },
    { offsetof(NVPathRendering, glGetPathParameteriv), "glGetPathParameterivNV" },
    { offsetof(NVPathRendering, glGetPathSpacing), "glGetPathSpacingNV" },
    { offsetof(NVPathRendering, glGetProgramResourcefv), "glGetProgramResourcefvNV" },
    { offsetof(NVPathRendering, glInterpolatePaths), "glInterpolatePathsNV" },
    { offsetof(NVPathRendering, glIsPath), "glIsPathNV" },
    { offsetof(NVPathRendering, glIsPointInFillPath), "glIsPointInFillPathNV" },
    { offsetof(NVPathRendering, glIsPointInStrokePath), "glIsPointInStrokePathNV" },
    { offsetof(NVPathRendering, glMatrixLoad3x2f), "glMatrixLoad3x2fNV" },
    { offsetof(NVPathRendering, glMatrixLoad3x3f), "glMatrixLoad3x3fNV" },
    { offsetof(NVPathRendering, glMatrixLoadTranspose3x3f), "glMatrixLoadTranspose3x3fNV" },
    { offsetof(NVPathRendering, glMatrixMult3x2f), "glMatrixMult3x2fNV" },
    { offsetof(NVPathRendering, glMatrixMult3x3f), "glMatrixMult3x3fNV" },
    { offsetof(NVPathRendering, glMatrixMultTranspose3x3f), "glMatrixMultTranspose3x3fNV" },
    { offsetof(NVPathRendering, glPathCommands), "glPathCommandsNV" },
    { offsetof(NVPathRendering, glPathCoords), "glPathCoordsNV" },
    { offsetof(NVPathRendering, glPathCoverDepthFunc), "glPathCoverDepthFuncNV" },
    { offsetof(NVPathRendering, glPathDashArray), "glPathDashArrayNV" },
    { offsetof(NVPathRendering, glPathGlyphIndexArray), "glPathGlyphIndexArrayNV" },
    { offsetof(NVPathRendering, glPathGlyphIndexRange), "glPathGlyphIndexRangeNV" },
    { offsetof(NVPathRendering, glPathGlyphRange), "glPathGlyphRangeNV" },
    { offsetof(NVPathRendering, glPathGlyphs), "glPathGlyphsNV" },
    { offsetof(NVPathRendering, glPathMemoryGlyphIndexArray), "glPathMemoryGlyphIndexArrayNV" },
    { offsetof(NVPathRendering, glPathParameterf), "glPathParameterfNV" },
    { offsetof(NVPathRendering, glPathParameterfv), "glPathParameterfvNV" },
    { offsetof(NVPathRendering, glPathParameteri), "glPathParameteriNV" },
    { offsetof(NVPathRendering, glPathParameteriv), "glPathParameterivNV" },
    { offsetof(NVPathRendering, glPathStencilDepthOffset), "glPathStencilDepthOffsetNV" },
    { offsetof(NVPathRendering, glPathStencilFunc), "glPathStencilFuncNV" },
    { offsetof(NVPathRendering, glPathString), "glPathStringNV" },
    { offsetof(NVPathRendering, glPathSubCommands), "glPathSubCommandsNV" },
    { offsetof(NVPathRendering, glPathSubCoords), "glPathSubCoordsNV" },
    { offsetof(NVPathRendering, glPointAlongPath), "glPointAlongPathNV" },
    { offsetof(NVPathRendering, glProgramPathFragmentInputGen), "glProgramPathFragmentInputGenNV" },
    { offsetof(NVPathRendering, glStencilFillPathInstanced), "glStencilFillPathInstancedNV" },
    { offsetof(NVPathRendering, glStencilFillPath), "glStencilFillPathNV" },
    { offsetof(NVPathRendering, glStencilStrokePathInstanced), "glStencilStrokePathInstancedNV" },
    { offsetof(NVPathRendering, glStencilStrokePath), "glStencilStrokePathNV" },
    { offsetof(NVPathRendering, glStencilThenCoverFillPathInstanced), "glStencilThenCoverFillPathInstancedNV" },
    { offsetof(NVPathRendering, glStencilThenCoverFillPath), "glStencilThenCoverFillPathNV" },
    { offsetof(NVPathRendering, glStencilThenCoverStrokePathInstanced), "glStencilThenCoverStrokePathInstancedNV" },
    { offsetof(NVPathRendering, glStencilThenCoverStrokePath), "glStencilThenCoverStrokePathNV" },
    { offsetof(NVPathRendering, glTransformPath), "glTransformPathNV" },
    { offsetof(NVPathRendering, glWeightPaths), "glWeightPathsNV" },
};

static const EntryOffset __NVPixelDataRangeEntryPoints[] = {
    { offsetof(NVPixelDataRange, glFlushPixelDataRange), "glFlushPixelDataRangeNV" },
    { offsetof(NVPixelDataRange, glPixelDataRange), "glPixelDataRangeNV" },
};

static const EntryOffset __NVPointSpriteEntryPoints[] = {
    { offsetof(NVPointSprite, glPointParameteri), "glPointParameteriNV" },
    { offsetof(NVPointSprite, glPointParameteriv), "glPointParameterivNV" },
};

static const EntryOffset __NVPresentVideoEntryPoints[] = {
    { offsetof(NVPresentVideo, glGetVideoi64v), "glGetVideoi64vNV" },
    { offsetof(NVPresentVideo, glGetVideoiv), "glGetVideoivNV" },
    { offsetof(NVPresentVideo, glGetVideoui64v), "glGetVideoui64vNV" },
    { offsetof(NVPresentVideo, glGetVideouiv), "glGetVideouivNV" },
    { offsetof(NVPresentVideo, glPresentFrameDualFill), "glPresentFrameDualFillNV" },
    { offsetof(NVPresentVideo, glPresentFrameKeyed), "glPresentFrameKeyedNV" },
};

static const EntryOffset __NVPrimitiveRestartEntryPoints[] = {
    { offsetof(NVPrimitiveRestart, glPrimitiveRestartIndex), "glPrimitiveRestartIndexNV" },
    { offsetof(NVPrimitiveRestart, glPrimitiveRestart), "glPrimitiveRestartNV" },
};

static const EntryOffset __NVQueryResourceEntryPoints[] = {
    { offsetof(NVQueryResource, glQueryResource), "glQueryResourceNV" },
};

static const EntryOffset __NVQueryResourceTagEntryPoints[] = {
    { offsetof(NVQueryResourceTag, glDeleteQueryResourceTag), "glDeleteQueryResourceTagNV" },
    { offsetof(NVQueryResourceTag, glGenQueryResourceTag), "glGenQueryResourceTagNV" },
    { offsetof(NVQueryResourceTag, glQueryResourceTag), "glQueryResourceTagNV" },
};

static const EntryOffset __NVRegisterCombinersEntryPoints[] = {
    { offsetof(NVRegisterCombiners, glCombinerInput), "glCombinerInputNV" },
    { offsetof(NVRegisterCombiners, glCombinerOutput), "glCombinerOutputNV" },
    { offsetof(NVRegisterCombiners, glCombinerParameterf), "glCombinerParameterfNV" },
    { offsetof(NVRegisterCombiners, glCombinerParameterfv), "glCombinerParameterfvNV" },
    { offsetof(NVRegisterCombiners, glCombinerParameteri), "glCombinerParameteriNV" },
    { offsetof(NVRegisterCombiners, glCombinerParameteriv), "glCombinerParameterivNV" },
    { offsetof(NVRegisterCombiners, glFinalCombinerInput), "glFinalCombinerInputNV" },
    { offsetof(NVRegisterCombiners, glGetCombinerInputParameterfv), "glGetCombinerInputParameterfvNV" },
    { offsetof(NVRegisterCombiners, glGetCombinerInputParameteriv), "glGetCombinerInputParameterivNV" },
    { offsetof(NVRegisterCombiners, glGetCombinerOutputParameterfv), "glGetCombinerOutputParameterfvNV" },
    { offsetof(NVRegisterCombiners, glGetCombinerOutputParameteriv), "glGetCombinerOutputParameterivNV" },
    { offsetof(NVRegisterCombiners, glGetFinalCombinerInputParameterfv), "glGetFinalCombinerInputParameterfvNV" },
    { offsetof(NVRegisterCombiners, glGetFinalCombinerInputParameteriv), "glGetFinalCombinerInputParameterivNV" },
};

static const EntryOffset __NVRegisterCOMBINERS2EntryPoints[] = {
    { offsetof(NVRegisterCOMBINERS2, glCombinerStageParameterfv), "glCombinerStageParameterfvNV" },
    { offsetof(NVRegisterCOMBINERS2, glGetCombinerStageParameterfv), "glGetCombinerStageParameterfvNV" },
};

static const EntryOffset __NVSampleLocationsEntryPoints[] = {
    { offsetof(NVSampleLocations, glFramebufferSampleLocationsfv), "glFramebufferSampleLocationsfvNV" },
    { offsetof(NVSampleLocations, glNamedFramebufferSampleLocationsfv), "glNamedFramebufferSampleLocationsfvNV" },
    { offsetof(NVSampleLocations, glResolveDepthValues), "glResolveDepthValuesNV" },
};

static const EntryOffset __NVScissorExclusiveEntryPoints[] = {
    { offsetof(NVScissorExclusive, glScissorExclusiveArrayv), "glScissorExclusiveArrayvNV" },
    { offsetof(NVScissorExclusive, glScissorExclusive), "glScissorExclusiveNV" },
};

static const EntryOffset __NVShaderBufferLoadEntryPoints[] = {
    { offsetof(NVShaderBufferLoad, glGetBufferParameterui64v), "glGetBufferParameterui64vNV" },
    { offsetof(NVShaderBufferLoad, glGetIntegerui64v), "glGetIntegerui64vNV" },
    { offsetof(NVShaderBufferLoad, glGetNamedBufferParameterui64v), "glGetNamedBufferParameterui64vNV" },
    { offsetof(NVShaderBufferLoad, glIsBufferResident), "glIsBufferResidentNV" },
    { offsetof(NVShaderBufferLoad, glIsNamedBufferResident), "glIsNamedBufferResidentNV" },
    { offsetof(NVShaderBufferLoad, glMakeBufferNonResident), "glMakeBufferNonResidentNV" },
    { offsetof(NVShaderBufferLoad, glMakeBufferResident), "glMakeBufferResidentNV" },
    { offsetof(NVShaderBufferLoad, glMakeNamedBufferNonResident), "glMakeNamedBufferNonResidentNV" },
    { offsetof(NVShaderBufferLoad, glMakeNamedBufferResident), "glMakeNamedBufferResidentNV" },
    { offsetof(NVShaderBufferLoad, glProgramUniformui64), "glProgramUniformui64NV" },
    { offsetof(NVShaderBufferLoad, glProgramUniformui64v), "glProgramUniformui64vNV" },
    { offsetof(NVShaderBufferLoad, glUniformui64), "glUniformui64NV" },
    { offsetof(NVShaderBufferLoad, glUniformui64v), "glUniformui64vNV" },
};

static const EntryOffset __NVShadingRateImageEntryPoints[] = {
    { offsetof(NVShadingRateImage, glBindShadingRateImage), "glBindShadingRateImageNV" },
    { offsetof(NVShadingRateImage, glGetShadingRateImagePalette), "glGetShadingRateImagePaletteNV" },
    { offsetof(NVShadingRateImage, glGetShadingRateSampleLocationiv), "glGetShadingRateSampleLocationivNV" },
    { offsetof(NVShadingRateImage, glShadingRateImageBarrier), "glShadingRateImageBarrierNV" },
    { offsetof(NVShadingRateImage, glShadingRateImagePalette), "glShadingRateImagePaletteNV" },
    { offsetof(NVShadingRateImage, glShadingRateSampleOrderCustom), "glShadingRateSampleOrderCustomNV" },
    { offsetof(NVShadingRateImage, glShadingRateSampleOrder), "glShadingRateSampleOrderNV" },
};

static const EntryOffset __NVTextureBarrierEntryPoints[] = {
    { offsetof(NVTextureBarrier, glTextureBarrier), "glTextureBarrierNV" },
};

static const EntryOffset __NVTextureMultisampleEntryPoints[] = {
    { offsetof(NVTextureMultisample, glTexImage2DMultisampleCoverage), "glTexImage2DMultisampleCoverageNV" },
    { offsetof(NVTextureMultisample, glTexImage3DMultisampleCoverage), "glTexImage3DMultisampleCoverageNV" },
    { offsetof(NVTextureMultisample, glTextureImage2DMultisampleCoverage), "glTextureImage2DMultisampleCoverageNV" },
    { offsetof(NVTextureMultisample, glTextureImage2DMultisample), "glTextureImage2DMultisampleNV" },
    { offsetof(NVTextureMultisample, glTextureImage3DMultisampleCoverage), "glTextureImage3DMultisampleCoverageNV" },
    { offsetof(NVTextureMultisample, glTextureImage3DMultisample), "glTextureImage3DMultisampleNV" },
};

static const EntryOffset __NVTimelineSemaphoreEntryPoints[] = {
    { offsetof(NVTimelineSemaphore, glCreateSemaphores), "glCreateSemaphoresNV" },
    { offsetof(NVTimelineSemaphore, glGetSemaphoreParameteriv), "glGetSemaphoreParameterivNV" },
    { offsetof(NVTimelineSemaphore, glSemaphoreParameteriv), "glSemaphoreParameterivNV" },
};

static const EntryOffset __NVTransformFeedbackEntryPoints[] = {
    { offsetof(NVTransformFeedback, glActiveVarying), "glActiveVaryingNV" },
    { offsetof(NVTransformFeedback, glBeginTransformFeedback), "glBeginTransformFeedbackNV" },
    { offsetof(NVTransformFeedback, glBindBufferBase), "glBindBufferBaseNV" },
    { offsetof(NVTransformFeedback, glBindBufferOffset), "glBindBufferOffsetNV" },
    { offsetof(NVTransformFeedback, glBindBufferRange), "glBindBufferRangeNV" },
    { offsetof(NVTransformFeedback, glEndTransformFeedback), "glEndTransformFeedbackNV" },
    { offsetof(NVTransformFeedback, glGetActiveVarying), "glGetActiveVaryingNV" },
    { offsetof(NVTransformFeedback, glGetTransformFeedbackVarying), "glGetTransformFeedbackVaryingNV" },
    { offsetof(NVTransformFeedback, glGetVaryingLocation), "glGetVaryingLocationNV" },
    { offsetof(NVTransformFeedback, glTransformFeedbackAttribs), "glTransformFeedbackAttribsNV" },
    { offsetof(NVTransformFeedback, glTransformFeedbackStreamAttribs), "glTransformFeedbackStreamAttribsNV" },
    { offsetof(NVTransformFeedback, glTransformFeedbackVaryings), "glTransformFeedbackVaryingsNV" },
};

static const EntryOffset __NVTransformFeedback2EntryPoints[] = {
    { offsetof(NVTransformFeedback2, glBindTransformFeedback), "glBindTransformFeedbackNV" },
    { offsetof(NVTransformFeedback2, glDeleteTransformFeedbacks), "glDeleteTransformFeedbacksNV" },
    { offsetof(NVTransformFeedback2, glDrawTransformFeedback), "glDrawTransformFeedbackNV" },
    { offsetof(NVTransformFeedback2, glGenTransformFeedbacks), "glGenTransformFeedbacksNV" },
    { offsetof(NVTransformFeedback2, glIsTransformFeedback), "glIsTransformFeedbackNV" },
    { offsetof(NVTransformFeedback2, glPauseTransformFeedback), "glPauseTransformFeedbackNV" },
    { offsetof(NVTransformFeedback2, glResumeTransformFeedback), "glResumeTransformFeedbackNV" },
};

static const EntryOffset __NVVdpauInteropEntryPoints[] = {
    { offsetof(NVVdpauInterop, glVDPAUFini), "glVDPAUFiniNV" },
    { offsetof(NVVdpauInterop, glVDPAUGetSurfaceiv), "glVDPAUGetSurfaceivNV" },
    { offsetof(NVVdpauInterop, glVDPAUInit), "glVDPAUInitNV" },
    { offsetof(NVVdpauInterop, glVDPAUIsSurface), "glVDPAUIsSurfaceNV" },
    { offsetof(NVVdpauInterop, glVDPAUMapSurfaces), "glVDPAUMapSurfacesNV" },
    { offsetof(NVVdpauInterop, glVDPAURegisterOutputSurface), "glVDPAURegisterOutputSurfaceNV" },
    { offsetof(NVVdpauInterop, glVDPAURegisterVideoSurface), "glVDPAURegisterVideoSurfaceNV" },
    { offsetof(NVVdpauInterop, glVDPAUSurfaceAccess), "glVDPAUSurfaceAccessNV" },
    { offsetof(NVVdpauInterop, glVDPAUUnmapSurfaces), "glVDPAUUnmapSurfacesNV" },
    { offsetof(NVVdpauInterop, glVDPAUUnregisterSurface), "glVDPAUUnregisterSurfaceNV" },
};

static const EntryOffset __NVVdpauINTEROP2EntryPoints[] = {
    { offsetof(NVVdpauINTEROP2, glVDPAURegisterVideoSurfaceWithPictureStructure), "glVDPAURegisterVideoSurfaceWithPictureStructureNV" },
};

static const EntryOffset __NVVertexArrayRangeEntryPoints[] = {
    { offsetof(NVVertexArrayRange, glFlushVertexArrayRange), "glFlushVertexArrayRangeNV" },
    { offsetof(NVVertexArrayRange, glVertexArrayRange), "glVertexArrayRangeNV" },
};

static const EntryOffset __NVVertexAttribInteger64BITEntryPoints[] = {
    { offsetof(NVVertexAttribInteger64BIT, glGetVertexAttribLi64v), "glGetVertexAttribLi64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glGetVertexAttribLui64v), "glGetVertexAttribLui64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL1i64), "glVertexAttribL1i64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL1i64v), "glVertexAttribL1i64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL1ui64), "glVertexAttribL1ui64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL1ui64v), "glVertexAttribL1ui64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL2i64), "glVertexAttribL2i64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL2i64v), "glVertexAttribL2i64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL2ui64), "glVertexAttribL2ui64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL2ui64v), "glVertexAttribL2ui64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL3i64), "glVertexAttribL3i64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL3i64v), "glVertexAttribL3i64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL3ui64), "glVertexAttribL3ui64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL3ui64v), "glVertexAttribL3ui64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL4i64), "glVertexAttribL4i64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL4i64v), "glVertexAttribL4i64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL4ui64), "glVertexAttribL4ui64NV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribL4ui64v), "glVertexAttribL4ui64vNV" },
    { offsetof(NVVertexAttribInteger64BIT, glVertexAttribLFormat), "glVertexAttribLFormatNV" },
};

static const EntryOffset __NVVertexBufferUnifiedMemoryEntryPoints[] = {
    { offsetof(NVVertexBufferUnifiedMemory, glBufferAddressRange), "glBufferAddressRangeNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glColorFormat), "glColorFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glEdgeFlagFormat), "glEdgeFlagFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glFogCoordFormat), "glFogCoordFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glGetIntegerui64i_v), "glGetIntegerui64i_vNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glIndexFormat), "glIndexFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glNormalFormat), "glNormalFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glSecondaryColorFormat), "glSecondaryColorFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glTexCoordFormat), "glTexCoordFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glVertexAttribFormat), "glVertexAttribFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glVertexAttribIFormat), "glVertexAttribIFormatNV" },
    { offsetof(NVVertexBufferUnifiedMemory, glVertexFormat), "glVertexFormatNV" },
};

static const EntryOffset __NVVertexProgramEntryPoints[] = {
    { offsetof(NVVertexProgram, glAreProgramsResident), "glAreProgramsResidentNV" },
    { offsetof(NVVertexProgram, glBindProgram), "glBindProgramNV" },
    { offsetof(NVVertexProgram, glDeletePrograms), "glDeleteProgramsNV" },
    { offsetof(NVVertexProgram, glExecuteProgram), "glExecuteProgramNV" },
    { offsetof(NVVertexProgram, glGenPrograms), "glGenProgramsNV" },
    { offsetof(NVVertexProgram, glGetProgramParameterdv), "glGetProgramParameterdvNV" },
    { offsetof(NVVertexProgram, glGetProgramParameterfv), "glGetProgramParameterfvNV" },
    { offsetof(NVVertexProgram, glGetProgramString), "glGetProgramStringNV" },
    { offsetof(NVVertexProgram, glGetProgramiv), "glGetProgramivNV" },
    { offsetof(NVVertexProgram, glGetTrackMatrixiv), "glGetTrackMatrixivNV" },
    { offsetof(NVVertexProgram, glGetVertexAttribPointerv), "glGetVertexAttribPointervNV" },
    { offsetof(NVVertexProgram, glGetVertexAttribdv), "glGetVertexAttribdvNV" },
    { offsetof(NVVertexProgram, glGetVertexAttribfv), "glGetVertexAttribfvNV" },
    { offsetof(NVVertexProgram, glGetVertexAttribiv), "glGetVertexAttribivNV" },
    { offsetof(NVVertexProgram, glIsProgram), "glIsProgramNV" },
    { offsetof(NVVertexProgram, glLoadProgram), "glLoadProgramNV" },
    { offsetof(NVVertexProgram, glProgramParameter4d), "glProgramParameter4dNV" },
    { offsetof(NVVertexProgram, glProgramParameter4dv), "glProgramParameter4dvNV" },
    { offsetof(NVVertexProgram, glProgramParameter4f), "glProgramParameter4fNV" },
    { offsetof(NVVertexProgram, glProgramParameter4fv), "glProgramParameter4fvNV" },
    { offsetof(NVVertexProgram, glProgramParameters4dv), "glProgramParameters4dvNV" },
    { offsetof(NVVertexProgram, glProgramParameters4fv), "glProgramParameters4fvNV" },
    { offsetof(NVVertexProgram, glRequestResidentPrograms), "glRequestResidentProgramsNV" },
    { offsetof(NVVertexProgram, glTrackMatrix), "glTrackMatrixNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1d), "glVertexAttrib1dNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1dv), "glVertexAttrib1dvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1f), "glVertexAttrib1fNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1fv), "glVertexAttrib1fvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1s), "glVertexAttrib1sNV" },
    { offsetof(NVVertexProgram, glVertexAttrib1sv), "glVertexAttrib1svNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2d), "glVertexAttrib2dNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2dv), "glVertexAttrib2dvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2f), "glVertexAttrib2fNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2fv), "glVertexAttrib2fvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2s), "glVertexAttrib2sNV" },
    { offsetof(NVVertexProgram, glVertexAttrib2sv), "glVertexAttrib2svNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3d), "glVertexAttrib3dNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3dv), "glVertexAttrib3dvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3f), "glVertexAttrib3fNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3fv), "glVertexAttrib3fvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3s), "glVertexAttrib3sNV" },
    { offsetof(NVVertexProgram, glVertexAttrib3sv), "glVertexAttrib3svNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4d), "glVertexAttrib4dNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4dv), "glVertexAttrib4dvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4f), "glVertexAttrib4fNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4fv), "glVertexAttrib4fvNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4s), "glVertexAttrib4sNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4sv), "glVertexAttrib4svNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4ub), "glVertexAttrib4ubNV" },
    { offsetof(NVVertexProgram, glVertexAttrib4ubv), "glVertexAttrib4ubvNV" },
    { offsetof(NVVertexProgram, glVertexAttribPointer), "glVertexAttribPointerNV" },
    { offsetof(NVVertexProgram, glVertexAttribs1dv), "glVertexAttribs1dvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs1fv), "glVertexAttribs1fvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs1sv), "glVertexAttribs1svNV" },
    { offsetof(NVVertexProgram, glVertexAttribs2dv), "glVertexAttribs2dvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs2fv), "glVertexAttribs2fvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs2sv), "glVertexAttribs2svNV" },
    { offsetof(NVVertexProgram, glVertexAttribs3dv), "glVertexAttribs3dvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs3fv), "glVertexAttribs3fvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs3sv), "glVertexAttribs3svNV" },
    { offsetof(NVVertexProgram, glVertexAttribs4dv), "glVertexAttribs4dvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs4fv), "glVertexAttribs4fvNV" },
    { offsetof(NVVertexProgram, glVertexAttribs4sv), "glVertexAttribs4svNV" },
    { offsetof(NVVertexProgram, glVertexAttribs4ubv), "glVertexAttribs4ubvNV" },
};

static const EntryOffset __NVVideoCaptureEntryPoints[] = {
    { offsetof(NVVideoCapture, glBeginVideoCapture), "glBeginVideoCaptureNV" },
    { offsetof(NVVideoCapture, glBindVideoCaptureStreamBuffer), "glBindVideoCaptureStreamBufferNV" },
    { offsetof(NVVideoCapture, glBindVideoCaptureStreamTexture), "glBindVideoCaptureStreamTextureNV" },
    { offsetof(NVVideoCapture, glEndVideoCapture), "glEndVideoCaptureNV" },
    { offsetof(NVVideoCapture, glGetVideoCaptureStreamdv), "glGetVideoCaptureStreamdvNV" },
    { offsetof(NVVideoCapture, glGetVideoCaptureStreamfv), "glGetVideoCaptureStreamfvNV" },
    { offsetof(NVVideoCapture, glGetVideoCaptureStreamiv), "glGetVideoCaptureStreamivNV" },
    { offsetof(NVVideoCapture, glGetVideoCaptureiv), "glGetVideoCaptureivNV" },
    { offsetof(NVVideoCapture, glVideoCapture), "glVideoCaptureNV" },
    { offsetof(NVVideoCapture, glVideoCaptureStreamParameterdv), "glVideoCaptureStreamParameterdvNV" },
    { offsetof(NVVideoCapture, glVideoCaptureStreamParameterfv), "glVideoCaptureStreamParameterfvNV" },
    { offsetof(NVVideoCapture, glVideoCaptureStreamParameteriv), "glVideoCaptureStreamParameterivNV" },
};

static const EntryOffset __NVViewportSwizzleEntryPoints[] = {
    { offsetof(NVViewportSwizzle, glViewportSwizzle), "glViewportSwizzleNV" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// NVXConditionalRender Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVXConditionalRender::NVXConditionalRender()
{
    std::for_each_n(__NVXConditionalRenderEntryPoints,
                    std::size(__NVXConditionalRenderEntryPoints),
                    ClearEntryPoint(this));
}

bool NVXConditionalRender::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NVX_conditional_render");
}

void NVXConditionalRender::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVXConditionalRenderEntryPoints,
                    std::size(__NVXConditionalRenderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVXGPUMULTICAST2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVXGPUMULTICAST2::NVXGPUMULTICAST2()
{
    std::for_each_n(__NVXGPUMULTICAST2EntryPoints,
                    std::size(__NVXGPUMULTICAST2EntryPoints),
                    ClearEntryPoint(this));
}

bool NVXGPUMULTICAST2::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NVX_gpu_multicast2");
}

void NVXGPUMULTICAST2::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVXGPUMULTICAST2EntryPoints,
                    std::size(__NVXGPUMULTICAST2EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVXLinkedGPUMulticast Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVXLinkedGPUMulticast::NVXLinkedGPUMulticast()
{
    std::for_each_n(__NVXLinkedGPUMulticastEntryPoints,
                    std::size(__NVXLinkedGPUMulticastEntryPoints),
                    ClearEntryPoint(this));
}

bool NVXLinkedGPUMulticast::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NVX_linked_gpu_multicast");
}

void NVXLinkedGPUMulticast::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVXLinkedGPUMulticastEntryPoints,
                    std::size(__NVXLinkedGPUMulticastEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVXProgressFence Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVXProgressFence::NVXProgressFence()
{
    std::for_each_n(__NVXProgressFenceEntryPoints,
                    std::size(__NVXProgressFenceEntryPoints),
                    ClearEntryPoint(this));
}

bool NVXProgressFence::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NVX_progress_fence");
}

void NVXProgressFence::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVXProgressFenceEntryPoints,
                    std::size(__NVXProgressFenceEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVAlphaToCoverageDitherControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVAlphaToCoverageDitherControl::NVAlphaToCoverageDitherControl()
{
    std::for_each_n(__NVAlphaToCoverageDitherControlEntryPoints,
                    std::size(__NVAlphaToCoverageDitherControlEntryPoints),
                    ClearEntryPoint(this));
}

bool NVAlphaToCoverageDitherControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_alpha_to_coverage_dither_control");
}

void NVAlphaToCoverageDitherControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVAlphaToCoverageDitherControlEntryPoints,
                    std::size(__NVAlphaToCoverageDitherControlEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessMultiDrawIndirect Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVBindlessMultiDrawIndirect::NVBindlessMultiDrawIndirect()
{
    std::for_each_n(__NVBindlessMultiDrawIndirectEntryPoints,
                    std::size(__NVBindlessMultiDrawIndirectEntryPoints),
                    ClearEntryPoint(this));
}

bool NVBindlessMultiDrawIndirect::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_bindless_multi_draw_indirect");
}

void NVBindlessMultiDrawIndirect::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVBindlessMultiDrawIndirectEntryPoints,
                    std::size(__NVBindlessMultiDrawIndirectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessMultiDrawIndirectCount Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVBindlessMultiDrawIndirectCount::NVBindlessMultiDrawIndirectCount()
{
    std::for_each_n(__NVBindlessMultiDrawIndirectCountEntryPoints,
                    std::size(__NVBindlessMultiDrawIndirectCountEntryPoints),
                    ClearEntryPoint(this));
}

bool NVBindlessMultiDrawIndirectCount::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_bindless_multi_draw_indirect_count");
}

void NVBindlessMultiDrawIndirectCount::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVBindlessMultiDrawIndirectCountEntryPoints,
                    std::size(__NVBindlessMultiDrawIndirectCountEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVBindlessTexture::NVBindlessTexture()
{
    std::for_each_n(__NVBindlessTextureEntryPoints,
                    std::size(__NVBindlessTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool NVBindlessTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_bindless_texture");
}

void NVBindlessTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVBindlessTextureEntryPoints,
                    std::size(__NVBindlessTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVBlendEquationAdvanced Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVBlendEquationAdvanced::NVBlendEquationAdvanced()
{
    std::for_each_n(__NVBlendEquationAdvancedEntryPoints,
                    std::size(__NVBlendEquationAdvancedEntryPoints),
                    ClearEntryPoint(this));
}

bool NVBlendEquationAdvanced::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_blend_equation_advanced");
}

void NVBlendEquationAdvanced::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVBlendEquationAdvancedEntryPoints,
                    std::size(__NVBlendEquationAdvancedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVClipSpaceWScaling Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVClipSpaceWScaling::NVClipSpaceWScaling()
{
    std::for_each_n(__NVClipSpaceWScalingEntryPoints,
                    std::size(__NVClipSpaceWScalingEntryPoints),
                    ClearEntryPoint(this));
}

bool NVClipSpaceWScaling::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_clip_space_w_scaling");
}

void NVClipSpaceWScaling::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVClipSpaceWScalingEntryPoints,
                    std::size(__NVClipSpaceWScalingEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVCommandList Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVCommandList::NVCommandList()
{
    std::for_each_n(__NVCommandListEntryPoints,
                    std::size(__NVCommandListEntryPoints),
                    ClearEntryPoint(this));
}

bool NVCommandList::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_command_list");
}

void NVCommandList::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVCommandListEntryPoints,
                    std::size(__NVCommandListEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVConditionalRender Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVConditionalRender::NVConditionalRender()
{
    std::for_each_n(__NVConditionalRenderEntryPoints,
                    std::size(__NVConditionalRenderEntryPoints),
                    ClearEntryPoint(this));
}

bool NVConditionalRender::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_conditional_render");
}

void NVConditionalRender::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVConditionalRenderEntryPoints,
                    std::size(__NVConditionalRenderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRaster Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVConservativeRaster::NVConservativeRaster()
{
    std::for_each_n(__NVConservativeRasterEntryPoints,
                    std::size(__NVConservativeRasterEntryPoints),
                    ClearEntryPoint(this));
}

bool NVConservativeRaster::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_conservative_raster");
}

void NVConservativeRaster::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVConservativeRasterEntryPoints,
                    std::size(__NVConservativeRasterEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRasterDilate Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVConservativeRasterDilate::NVConservativeRasterDilate()
{
    std::for_each_n(__NVConservativeRasterDilateEntryPoints,
                    std::size(__NVConservativeRasterDilateEntryPoints),
                    ClearEntryPoint(this));
}

bool NVConservativeRasterDilate::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_conservative_raster_dilate");
}

void NVConservativeRasterDilate::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVConservativeRasterDilateEntryPoints,
                    std::size(__NVConservativeRasterDilateEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRasterPreSnapTriangles Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVConservativeRasterPreSnapTriangles::NVConservativeRasterPreSnapTriangles()
{
    std::for_each_n(__NVConservativeRasterPreSnapTrianglesEntryPoints,
                    std::size(__NVConservativeRasterPreSnapTrianglesEntryPoints),
                    ClearEntryPoint(this));
}

bool NVConservativeRasterPreSnapTriangles::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_conservative_raster_pre_snap_triangles");
}

void NVConservativeRasterPreSnapTriangles::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVConservativeRasterPreSnapTrianglesEntryPoints,
                    std::size(__NVConservativeRasterPreSnapTrianglesEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVCopyImage::NVCopyImage()
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    ClearEntryPoint(this));
}

bool NVCopyImage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_copy_image");
}

void NVCopyImage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVDepthBufferFloat Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDepthBufferFloat::NVDepthBufferFloat()
{
    std::for_each_n(__NVDepthBufferFloatEntryPoints,
                    std::size(__NVDepthBufferFloatEntryPoints),
                    ClearEntryPoint(this));
}

bool NVDepthBufferFloat::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_depth_buffer_float");
}

void NVDepthBufferFloat::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDepthBufferFloatEntryPoints,
                    std::size(__NVDepthBufferFloatEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVDrawTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDrawTexture::NVDrawTexture()
{
    std::for_each_n(__NVDrawTextureEntryPoints,
                    std::size(__NVDrawTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool NVDrawTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_draw_texture");
}

void NVDrawTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDrawTextureEntryPoints,
                    std::size(__NVDrawTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVDrawVulkanImage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDrawVulkanImage::NVDrawVulkanImage()
{
    std::for_each_n(__NVDrawVulkanImageEntryPoints,
                    std::size(__NVDrawVulkanImageEntryPoints),
                    ClearEntryPoint(this));
}

bool NVDrawVulkanImage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_draw_vulkan_image");
}

void NVDrawVulkanImage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDrawVulkanImageEntryPoints,
                    std::size(__NVDrawVulkanImageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVEvaluators Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVEvaluators::NVEvaluators()
{
    std::for_each_n(__NVEvaluatorsEntryPoints,
                    std::size(__NVEvaluatorsEntryPoints),
                    ClearEntryPoint(this));
}

bool NVEvaluators::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_evaluators");
}

void NVEvaluators::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVEvaluatorsEntryPoints,
                    std::size(__NVEvaluatorsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVExplicitMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVExplicitMultisample::NVExplicitMultisample()
{
    std::for_each_n(__NVExplicitMultisampleEntryPoints,
                    std::size(__NVExplicitMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool NVExplicitMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_explicit_multisample");
}

void NVExplicitMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVExplicitMultisampleEntryPoints,
                    std::size(__NVExplicitMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVFence Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVFence::NVFence()
{
    std::for_each_n(__NVFenceEntryPoints,
                    std::size(__NVFenceEntryPoints),
                    ClearEntryPoint(this));
}

bool NVFence::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_fence");
}

void NVFence::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVFenceEntryPoints,
                    std::size(__NVFenceEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVFragmentCoverageToColor Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVFragmentCoverageToColor::NVFragmentCoverageToColor()
{
    std::for_each_n(__NVFragmentCoverageToColorEntryPoints,
                    std::size(__NVFragmentCoverageToColorEntryPoints),
                    ClearEntryPoint(this));
}

bool NVFragmentCoverageToColor::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_fragment_coverage_to_color");
}

void NVFragmentCoverageToColor::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVFragmentCoverageToColorEntryPoints,
                    std::size(__NVFragmentCoverageToColorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVFragmentProgram Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVFragmentProgram::NVFragmentProgram()
{
    std::for_each_n(__NVFragmentProgramEntryPoints,
                    std::size(__NVFragmentProgramEntryPoints),
                    ClearEntryPoint(this));
}

bool NVFragmentProgram::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_fragment_program");
}

void NVFragmentProgram::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVFragmentProgramEntryPoints,
                    std::size(__NVFragmentProgramEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVFramebufferMixedSamples Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVFramebufferMixedSamples::NVFramebufferMixedSamples()
{
    std::for_each_n(__NVFramebufferMixedSamplesEntryPoints,
                    std::size(__NVFramebufferMixedSamplesEntryPoints),
                    ClearEntryPoint(this));
}

bool NVFramebufferMixedSamples::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_framebuffer_mixed_samples");
}

void NVFramebufferMixedSamples::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVFramebufferMixedSamplesEntryPoints,
                    std::size(__NVFramebufferMixedSamplesEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVFramebufferMultisampleCoverage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVFramebufferMultisampleCoverage::NVFramebufferMultisampleCoverage()
{
    std::for_each_n(__NVFramebufferMultisampleCoverageEntryPoints,
                    std::size(__NVFramebufferMultisampleCoverageEntryPoints),
                    ClearEntryPoint(this));
}

bool NVFramebufferMultisampleCoverage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_framebuffer_multisample_coverage");
}

void NVFramebufferMultisampleCoverage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVFramebufferMultisampleCoverageEntryPoints,
                    std::size(__NVFramebufferMultisampleCoverageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVGeometryPROGRAM4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVGeometryPROGRAM4::NVGeometryPROGRAM4()
{
    std::for_each_n(__NVGeometryPROGRAM4EntryPoints,
                    std::size(__NVGeometryPROGRAM4EntryPoints),
                    ClearEntryPoint(this));
}

bool NVGeometryPROGRAM4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_geometry_program4");
}

void NVGeometryPROGRAM4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVGeometryPROGRAM4EntryPoints,
                    std::size(__NVGeometryPROGRAM4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUMulticast Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVGPUMulticast::NVGPUMulticast()
{
    std::for_each_n(__NVGPUMulticastEntryPoints,
                    std::size(__NVGPUMulticastEntryPoints),
                    ClearEntryPoint(this));
}

bool NVGPUMulticast::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_gpu_multicast");
}

void NVGPUMulticast::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVGPUMulticastEntryPoints,
                    std::size(__NVGPUMulticastEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUPROGRAM4 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVGPUPROGRAM4::NVGPUPROGRAM4()
{
    std::for_each_n(__NVGPUPROGRAM4EntryPoints,
                    std::size(__NVGPUPROGRAM4EntryPoints),
                    ClearEntryPoint(this));
}

bool NVGPUPROGRAM4::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_gpu_program4");
}

void NVGPUPROGRAM4::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVGPUPROGRAM4EntryPoints,
                    std::size(__NVGPUPROGRAM4EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUPROGRAM5 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVGPUPROGRAM5::NVGPUPROGRAM5()
{
    std::for_each_n(__NVGPUPROGRAM5EntryPoints,
                    std::size(__NVGPUPROGRAM5EntryPoints),
                    ClearEntryPoint(this));
}

bool NVGPUPROGRAM5::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_gpu_program5");
}

void NVGPUPROGRAM5::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVGPUPROGRAM5EntryPoints,
                    std::size(__NVGPUPROGRAM5EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVHalfFloat Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVHalfFloat::NVHalfFloat()
{
    std::for_each_n(__NVHalfFloatEntryPoints,
                    std::size(__NVHalfFloatEntryPoints),
                    ClearEntryPoint(this));
}

bool NVHalfFloat::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_half_float");
}

void NVHalfFloat::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVHalfFloatEntryPoints,
                    std::size(__NVHalfFloatEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVInternalformatSampleQuery Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVInternalformatSampleQuery::NVInternalformatSampleQuery()
{
    std::for_each_n(__NVInternalformatSampleQueryEntryPoints,
                    std::size(__NVInternalformatSampleQueryEntryPoints),
                    ClearEntryPoint(this));
}

bool NVInternalformatSampleQuery::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_internalformat_sample_query");
}

void NVInternalformatSampleQuery::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVInternalformatSampleQueryEntryPoints,
                    std::size(__NVInternalformatSampleQueryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVMemoryAttachment Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVMemoryAttachment::NVMemoryAttachment()
{
    std::for_each_n(__NVMemoryAttachmentEntryPoints,
                    std::size(__NVMemoryAttachmentEntryPoints),
                    ClearEntryPoint(this));
}

bool NVMemoryAttachment::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_memory_attachment");
}

void NVMemoryAttachment::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVMemoryAttachmentEntryPoints,
                    std::size(__NVMemoryAttachmentEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVMemoryObjectSparse Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVMemoryObjectSparse::NVMemoryObjectSparse()
{
    std::for_each_n(__NVMemoryObjectSparseEntryPoints,
                    std::size(__NVMemoryObjectSparseEntryPoints),
                    ClearEntryPoint(this));
}

bool NVMemoryObjectSparse::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_memory_object_sparse");
}

void NVMemoryObjectSparse::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVMemoryObjectSparseEntryPoints,
                    std::size(__NVMemoryObjectSparseEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVMeshShader Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVMeshShader::NVMeshShader()
{
    std::for_each_n(__NVMeshShaderEntryPoints,
                    std::size(__NVMeshShaderEntryPoints),
                    ClearEntryPoint(this));
}

bool NVMeshShader::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_mesh_shader");
}

void NVMeshShader::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVMeshShaderEntryPoints,
                    std::size(__NVMeshShaderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVOcclusionQuery Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVOcclusionQuery::NVOcclusionQuery()
{
    std::for_each_n(__NVOcclusionQueryEntryPoints,
                    std::size(__NVOcclusionQueryEntryPoints),
                    ClearEntryPoint(this));
}

bool NVOcclusionQuery::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_occlusion_query");
}

void NVOcclusionQuery::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVOcclusionQueryEntryPoints,
                    std::size(__NVOcclusionQueryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVParameterBufferObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVParameterBufferObject::NVParameterBufferObject()
{
    std::for_each_n(__NVParameterBufferObjectEntryPoints,
                    std::size(__NVParameterBufferObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool NVParameterBufferObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_parameter_buffer_object");
}

void NVParameterBufferObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVParameterBufferObjectEntryPoints,
                    std::size(__NVParameterBufferObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPathRendering Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPathRendering::NVPathRendering()
{
    std::for_each_n(__NVPathRenderingEntryPoints,
                    std::size(__NVPathRenderingEntryPoints),
                    ClearEntryPoint(this));
}

bool NVPathRendering::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_path_rendering");
}

void NVPathRendering::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPathRenderingEntryPoints,
                    std::size(__NVPathRenderingEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPixelDataRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPixelDataRange::NVPixelDataRange()
{
    std::for_each_n(__NVPixelDataRangeEntryPoints,
                    std::size(__NVPixelDataRangeEntryPoints),
                    ClearEntryPoint(this));
}

bool NVPixelDataRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_pixel_data_range");
}

void NVPixelDataRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPixelDataRangeEntryPoints,
                    std::size(__NVPixelDataRangeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPointSprite Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPointSprite::NVPointSprite()
{
    std::for_each_n(__NVPointSpriteEntryPoints,
                    std::size(__NVPointSpriteEntryPoints),
                    ClearEntryPoint(this));
}

bool NVPointSprite::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_point_sprite");
}

void NVPointSprite::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPointSpriteEntryPoints,
                    std::size(__NVPointSpriteEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideo Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPresentVideo::NVPresentVideo()
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    ClearEntryPoint(this));
}

bool NVPresentVideo::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_present_video");
}

void NVPresentVideo::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPrimitiveRestart Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPrimitiveRestart::NVPrimitiveRestart()
{
    std::for_each_n(__NVPrimitiveRestartEntryPoints,
                    std::size(__NVPrimitiveRestartEntryPoints),
                    ClearEntryPoint(this));
}

bool NVPrimitiveRestart::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_primitive_restart");
}

void NVPrimitiveRestart::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPrimitiveRestartEntryPoints,
                    std::size(__NVPrimitiveRestartEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVQueryResource Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVQueryResource::NVQueryResource()
{
    std::for_each_n(__NVQueryResourceEntryPoints,
                    std::size(__NVQueryResourceEntryPoints),
                    ClearEntryPoint(this));
}

bool NVQueryResource::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_query_resource");
}

void NVQueryResource::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVQueryResourceEntryPoints,
                    std::size(__NVQueryResourceEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVQueryResourceTag Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVQueryResourceTag::NVQueryResourceTag()
{
    std::for_each_n(__NVQueryResourceTagEntryPoints,
                    std::size(__NVQueryResourceTagEntryPoints),
                    ClearEntryPoint(this));
}

bool NVQueryResourceTag::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_query_resource_tag");
}

void NVQueryResourceTag::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVQueryResourceTagEntryPoints,
                    std::size(__NVQueryResourceTagEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVRegisterCombiners Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVRegisterCombiners::NVRegisterCombiners()
{
    std::for_each_n(__NVRegisterCombinersEntryPoints,
                    std::size(__NVRegisterCombinersEntryPoints),
                    ClearEntryPoint(this));
}

bool NVRegisterCombiners::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_register_combiners");
}

void NVRegisterCombiners::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVRegisterCombinersEntryPoints,
                    std::size(__NVRegisterCombinersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVRegisterCOMBINERS2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVRegisterCOMBINERS2::NVRegisterCOMBINERS2()
{
    std::for_each_n(__NVRegisterCOMBINERS2EntryPoints,
                    std::size(__NVRegisterCOMBINERS2EntryPoints),
                    ClearEntryPoint(this));
}

bool NVRegisterCOMBINERS2::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_register_combiners2");
}

void NVRegisterCOMBINERS2::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVRegisterCOMBINERS2EntryPoints,
                    std::size(__NVRegisterCOMBINERS2EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVSampleLocations Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVSampleLocations::NVSampleLocations()
{
    std::for_each_n(__NVSampleLocationsEntryPoints,
                    std::size(__NVSampleLocationsEntryPoints),
                    ClearEntryPoint(this));
}

bool NVSampleLocations::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_sample_locations");
}

void NVSampleLocations::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVSampleLocationsEntryPoints,
                    std::size(__NVSampleLocationsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVScissorExclusive Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVScissorExclusive::NVScissorExclusive()
{
    std::for_each_n(__NVScissorExclusiveEntryPoints,
                    std::size(__NVScissorExclusiveEntryPoints),
                    ClearEntryPoint(this));
}

bool NVScissorExclusive::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_scissor_exclusive");
}

void NVScissorExclusive::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVScissorExclusiveEntryPoints,
                    std::size(__NVScissorExclusiveEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVShaderBufferLoad Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVShaderBufferLoad::NVShaderBufferLoad()
{
    std::for_each_n(__NVShaderBufferLoadEntryPoints,
                    std::size(__NVShaderBufferLoadEntryPoints),
                    ClearEntryPoint(this));
}

bool NVShaderBufferLoad::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_shader_buffer_load");
}

void NVShaderBufferLoad::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVShaderBufferLoadEntryPoints,
                    std::size(__NVShaderBufferLoadEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVShadingRateImage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVShadingRateImage::NVShadingRateImage()
{
    std::for_each_n(__NVShadingRateImageEntryPoints,
                    std::size(__NVShadingRateImageEntryPoints),
                    ClearEntryPoint(this));
}

bool NVShadingRateImage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_shading_rate_image");
}

void NVShadingRateImage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVShadingRateImageEntryPoints,
                    std::size(__NVShadingRateImageEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVTextureBarrier Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVTextureBarrier::NVTextureBarrier()
{
    std::for_each_n(__NVTextureBarrierEntryPoints,
                    std::size(__NVTextureBarrierEntryPoints),
                    ClearEntryPoint(this));
}

bool NVTextureBarrier::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_texture_barrier");
}

void NVTextureBarrier::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVTextureBarrierEntryPoints,
                    std::size(__NVTextureBarrierEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVTextureMultisample Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVTextureMultisample::NVTextureMultisample()
{
    std::for_each_n(__NVTextureMultisampleEntryPoints,
                    std::size(__NVTextureMultisampleEntryPoints),
                    ClearEntryPoint(this));
}

bool NVTextureMultisample::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_texture_multisample");
}

void NVTextureMultisample::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVTextureMultisampleEntryPoints,
                    std::size(__NVTextureMultisampleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVTimelineSemaphore Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVTimelineSemaphore::NVTimelineSemaphore()
{
    std::for_each_n(__NVTimelineSemaphoreEntryPoints,
                    std::size(__NVTimelineSemaphoreEntryPoints),
                    ClearEntryPoint(this));
}

bool NVTimelineSemaphore::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_timeline_semaphore");
}

void NVTimelineSemaphore::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVTimelineSemaphoreEntryPoints,
                    std::size(__NVTimelineSemaphoreEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVTransformFeedback Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVTransformFeedback::NVTransformFeedback()
{
    std::for_each_n(__NVTransformFeedbackEntryPoints,
                    std::size(__NVTransformFeedbackEntryPoints),
                    ClearEntryPoint(this));
}

bool NVTransformFeedback::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_transform_feedback");
}

void NVTransformFeedback::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVTransformFeedbackEntryPoints,
                    std::size(__NVTransformFeedbackEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVTransformFeedback2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVTransformFeedback2::NVTransformFeedback2()
{
    std::for_each_n(__NVTransformFeedback2EntryPoints,
                    std::size(__NVTransformFeedback2EntryPoints),
                    ClearEntryPoint(this));
}

bool NVTransformFeedback2::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_transform_feedback2");
}

void NVTransformFeedback2::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVTransformFeedback2EntryPoints,
                    std::size(__NVTransformFeedback2EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVdpauInterop Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVdpauInterop::NVVdpauInterop()
{
    std::for_each_n(__NVVdpauInteropEntryPoints,
                    std::size(__NVVdpauInteropEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVdpauInterop::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vdpau_interop");
}

void NVVdpauInterop::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVdpauInteropEntryPoints,
                    std::size(__NVVdpauInteropEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVdpauINTEROP2 Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVdpauINTEROP2::NVVdpauINTEROP2()
{
    std::for_each_n(__NVVdpauINTEROP2EntryPoints,
                    std::size(__NVVdpauINTEROP2EntryPoints),
                    ClearEntryPoint(this));
}

bool NVVdpauINTEROP2::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vdpau_interop2");
}

void NVVdpauINTEROP2::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVdpauINTEROP2EntryPoints,
                    std::size(__NVVdpauINTEROP2EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexArrayRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVertexArrayRange::NVVertexArrayRange()
{
    std::for_each_n(__NVVertexArrayRangeEntryPoints,
                    std::size(__NVVertexArrayRangeEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVertexArrayRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vertex_array_range");
}

void NVVertexArrayRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVertexArrayRangeEntryPoints,
                    std::size(__NVVertexArrayRangeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexAttribInteger64BIT Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVertexAttribInteger64BIT::NVVertexAttribInteger64BIT()
{
    std::for_each_n(__NVVertexAttribInteger64BITEntryPoints,
                    std::size(__NVVertexAttribInteger64BITEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVertexAttribInteger64BIT::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vertex_attrib_integer_64bit");
}

void NVVertexAttribInteger64BIT::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVertexAttribInteger64BITEntryPoints,
                    std::size(__NVVertexAttribInteger64BITEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexBufferUnifiedMemory Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVertexBufferUnifiedMemory::NVVertexBufferUnifiedMemory()
{
    std::for_each_n(__NVVertexBufferUnifiedMemoryEntryPoints,
                    std::size(__NVVertexBufferUnifiedMemoryEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVertexBufferUnifiedMemory::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vertex_buffer_unified_memory");
}

void NVVertexBufferUnifiedMemory::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVertexBufferUnifiedMemoryEntryPoints,
                    std::size(__NVVertexBufferUnifiedMemoryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexProgram Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVertexProgram::NVVertexProgram()
{
    std::for_each_n(__NVVertexProgramEntryPoints,
                    std::size(__NVVertexProgramEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVertexProgram::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_vertex_program");
}

void NVVertexProgram::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVertexProgramEntryPoints,
                    std::size(__NVVertexProgramEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCapture Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVideoCapture::NVVideoCapture()
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    ClearEntryPoint(this));
}

bool NVVideoCapture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_video_capture");
}

void NVVideoCapture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVViewportSwizzle Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVViewportSwizzle::NVViewportSwizzle()
{
    std::for_each_n(__NVViewportSwizzleEntryPoints,
                    std::size(__NVViewportSwizzleEntryPoints),
                    ClearEntryPoint(this));
}

bool NVViewportSwizzle::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_NV_viewport_swizzle");
}

void NVViewportSwizzle::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVViewportSwizzleEntryPoints,
                    std::size(__NVViewportSwizzleEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl

#ifdef _WIN32
namespace wgl {
namespace {

static const gl::EntryOffset __NVDxInteropEntryPoints[] = {
    { offsetof(NVDxInterop, wglDXCloseDevice), "wglDXCloseDeviceNV" },
    { offsetof(NVDxInterop, wglDXLockObjects), "wglDXLockObjectsNV" },
    { offsetof(NVDxInterop, wglDXObjectAccess), "wglDXObjectAccessNV" },
    { offsetof(NVDxInterop, wglDXOpenDevice), "wglDXOpenDeviceNV" },
    { offsetof(NVDxInterop, wglDXRegisterObject), "wglDXRegisterObjectNV" },
    { offsetof(NVDxInterop, wglDXSetResourceShareHandle), "wglDXSetResourceShareHandleNV" },
    { offsetof(NVDxInterop, wglDXUnlockObjects), "wglDXUnlockObjectsNV" },
    { offsetof(NVDxInterop, wglDXUnregisterObject), "wglDXUnregisterObjectNV" },
};

static const gl::EntryOffset __NVCopyImageEntryPoints[] = {
    { offsetof(NVCopyImage, wglCopyImageSubData), "wglCopyImageSubDataNV" },
};

static const gl::EntryOffset __NVDelayBeforeSwapEntryPoints[] = {
    { offsetof(NVDelayBeforeSwap, wglDelayBeforeSwap), "wglDelayBeforeSwapNV" },
};

static const gl::EntryOffset __NVGPUAffinityEntryPoints[] = {
    { offsetof(NVGPUAffinity, wglCreateAffinityDC), "wglCreateAffinityDCNV" },
    { offsetof(NVGPUAffinity, wglDeleteDC), "wglDeleteDCNV" },
    { offsetof(NVGPUAffinity, wglEnumGpuDevices), "wglEnumGpuDevicesNV" },
    { offsetof(NVGPUAffinity, wglEnumGpusFromAffinityDC), "wglEnumGpusFromAffinityDCNV" },
    { offsetof(NVGPUAffinity, wglEnumGpus), "wglEnumGpusNV" },
};

static const gl::EntryOffset __NVPresentVideoEntryPoints[] = {
    { offsetof(NVPresentVideo, wglBindVideoDevice), "wglBindVideoDeviceNV" },
    { offsetof(NVPresentVideo, wglEnumerateVideoDevices), "wglEnumerateVideoDevicesNV" },
    { offsetof(NVPresentVideo, wglQueryCurrentContext), "wglQueryCurrentContextNV" },
};

static const gl::EntryOffset __NVSwapGroupEntryPoints[] = {
    { offsetof(NVSwapGroup, wglBindSwapBarrier), "wglBindSwapBarrierNV" },
    { offsetof(NVSwapGroup, wglJoinSwapGroup), "wglJoinSwapGroupNV" },
    { offsetof(NVSwapGroup, wglQueryFrameCount), "wglQueryFrameCountNV" },
    { offsetof(NVSwapGroup, wglQueryMaxSwapGroups), "wglQueryMaxSwapGroupsNV" },
    { offsetof(NVSwapGroup, wglQuerySwapGroup), "wglQuerySwapGroupNV" },
    { offsetof(NVSwapGroup, wglResetFrameCount), "wglResetFrameCountNV" },
};

static const gl::EntryOffset __NVVertexArrayRangeEntryPoints[] = {
    { offsetof(NVVertexArrayRange, wglAllocateMemory), "wglAllocateMemoryNV" },
    { offsetof(NVVertexArrayRange, wglFreeMemory), "wglFreeMemoryNV" },
};

static const gl::EntryOffset __NVVideoCaptureEntryPoints[] = {
    { offsetof(NVVideoCapture, wglBindVideoCaptureDevice), "wglBindVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, wglEnumerateVideoCaptureDevices), "wglEnumerateVideoCaptureDevicesNV" },
    { offsetof(NVVideoCapture, wglLockVideoCaptureDevice), "wglLockVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, wglQueryVideoCaptureDevice), "wglQueryVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, wglReleaseVideoCaptureDevice), "wglReleaseVideoCaptureDeviceNV" },
};

static const gl::EntryOffset __NVVideoOutputEntryPoints[] = {
    { offsetof(NVVideoOutput, wglBindVideoImage), "wglBindVideoImageNV" },
    { offsetof(NVVideoOutput, wglGetVideoDevice), "wglGetVideoDeviceNV" },
    { offsetof(NVVideoOutput, wglGetVideoInfo), "wglGetVideoInfoNV" },
    { offsetof(NVVideoOutput, wglReleaseVideoDevice), "wglReleaseVideoDeviceNV" },
    { offsetof(NVVideoOutput, wglReleaseVideoImage), "wglReleaseVideoImageNV" },
    { offsetof(NVVideoOutput, wglSendPbufferToVideo), "wglSendPbufferToVideoNV" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// NVDxInterop Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDxInterop::NVDxInterop()
{
    std::for_each_n(__NVDxInteropEntryPoints,
                    std::size(__NVDxInteropEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVDxInterop::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_DX_interop");
}

void NVDxInterop::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDxInteropEntryPoints,
                    std::size(__NVDxInteropEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVCopyImage::NVCopyImage()
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVCopyImage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_copy_image");
}

void NVCopyImage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVDelayBeforeSwap Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDelayBeforeSwap::NVDelayBeforeSwap()
{
    std::for_each_n(__NVDelayBeforeSwapEntryPoints,
                    std::size(__NVDelayBeforeSwapEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVDelayBeforeSwap::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_delay_before_swap");
}

void NVDelayBeforeSwap::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDelayBeforeSwapEntryPoints,
                    std::size(__NVDelayBeforeSwapEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUAffinity Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVGPUAffinity::NVGPUAffinity()
{
    std::for_each_n(__NVGPUAffinityEntryPoints,
                    std::size(__NVGPUAffinityEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVGPUAffinity::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_gpu_affinity");
}

void NVGPUAffinity::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVGPUAffinityEntryPoints,
                    std::size(__NVGPUAffinityEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideo Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPresentVideo::NVPresentVideo()
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVPresentVideo::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_present_video");
}

void NVPresentVideo::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVSwapGroup Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVSwapGroup::NVSwapGroup()
{
    std::for_each_n(__NVSwapGroupEntryPoints,
                    std::size(__NVSwapGroupEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVSwapGroup::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_swap_group");
}

void NVSwapGroup::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVSwapGroupEntryPoints,
                    std::size(__NVSwapGroupEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexArrayRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVertexArrayRange::NVVertexArrayRange()
{
    std::for_each_n(__NVVertexArrayRangeEntryPoints,
                    std::size(__NVVertexArrayRangeEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVVertexArrayRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_vertex_array_range");
}

void NVVertexArrayRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVertexArrayRangeEntryPoints,
                    std::size(__NVVertexArrayRangeEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCapture Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVideoCapture::NVVideoCapture()
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVVideoCapture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_video_capture");
}

void NVVideoCapture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoOutput Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVideoOutput::NVVideoOutput()
{
    std::for_each_n(__NVVideoOutputEntryPoints,
                    std::size(__NVVideoOutputEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVVideoOutput::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_NV_video_output");
}

void NVVideoOutput::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVideoOutputEntryPoints,
                    std::size(__NVVideoOutputEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __NVCopyBufferEntryPoints[] = {
    { offsetof(NVCopyBuffer, glXCopyBufferSubData), "glXCopyBufferSubDataNV" },
    { offsetof(NVCopyBuffer, glXNamedCopyBufferSubData), "glXNamedCopyBufferSubDataNV" },
};

static const gl::EntryOffset __NVCopyImageEntryPoints[] = {
    { offsetof(NVCopyImage, glXCopyImageSubData), "glXCopyImageSubDataNV" },
};

static const gl::EntryOffset __NVDelayBeforeSwapEntryPoints[] = {
    { offsetof(NVDelayBeforeSwap, glXDelayBeforeSwap), "glXDelayBeforeSwapNV" },
};

static const gl::EntryOffset __NVPresentVideoEntryPoints[] = {
    { offsetof(NVPresentVideo, glXBindVideoDevice), "glXBindVideoDeviceNV" },
    { offsetof(NVPresentVideo, glXEnumerateVideoDevices), "glXEnumerateVideoDevicesNV" },
};

static const gl::EntryOffset __NVSwapGroupEntryPoints[] = {
    { offsetof(NVSwapGroup, glXBindSwapBarrier), "glXBindSwapBarrierNV" },
    { offsetof(NVSwapGroup, glXJoinSwapGroup), "glXJoinSwapGroupNV" },
    { offsetof(NVSwapGroup, glXQueryFrameCount), "glXQueryFrameCountNV" },
    { offsetof(NVSwapGroup, glXQueryMaxSwapGroups), "glXQueryMaxSwapGroupsNV" },
    { offsetof(NVSwapGroup, glXQuerySwapGroup), "glXQuerySwapGroupNV" },
    { offsetof(NVSwapGroup, glXResetFrameCount), "glXResetFrameCountNV" },
};

static const gl::EntryOffset __NVVideoCaptureEntryPoints[] = {
    { offsetof(NVVideoCapture, glXBindVideoCaptureDevice), "glXBindVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, glXEnumerateVideoCaptureDevices), "glXEnumerateVideoCaptureDevicesNV" },
    { offsetof(NVVideoCapture, glXLockVideoCaptureDevice), "glXLockVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, glXQueryVideoCaptureDevice), "glXQueryVideoCaptureDeviceNV" },
    { offsetof(NVVideoCapture, glXReleaseVideoCaptureDevice), "glXReleaseVideoCaptureDeviceNV" },
};

static const gl::EntryOffset __NVVideoOutEntryPoints[] = {
    { offsetof(NVVideoOut, glXBindVideoImage), "glXBindVideoImageNV" },
    { offsetof(NVVideoOut, glXGetVideoDevice), "glXGetVideoDeviceNV" },
    { offsetof(NVVideoOut, glXGetVideoInfo), "glXGetVideoInfoNV" },
    { offsetof(NVVideoOut, glXReleaseVideoDevice), "glXReleaseVideoDeviceNV" },
    { offsetof(NVVideoOut, glXReleaseVideoImage), "glXReleaseVideoImageNV" },
    { offsetof(NVVideoOut, glXSendPbufferToVideo), "glXSendPbufferToVideoNV" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// NVCopyBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVCopyBuffer::NVCopyBuffer()
{
    std::for_each_n(__NVCopyBufferEntryPoints,
                    std::size(__NVCopyBufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVCopyBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_copy_buffer");
}

void NVCopyBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVCopyBufferEntryPoints,
                    std::size(__NVCopyBufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImage Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVCopyImage::NVCopyImage()
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVCopyImage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_copy_image");
}

void NVCopyImage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVCopyImageEntryPoints,
                    std::size(__NVCopyImageEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVDelayBeforeSwap Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVDelayBeforeSwap::NVDelayBeforeSwap()
{
    std::for_each_n(__NVDelayBeforeSwapEntryPoints,
                    std::size(__NVDelayBeforeSwapEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVDelayBeforeSwap::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_delay_before_swap");
}

void NVDelayBeforeSwap::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVDelayBeforeSwapEntryPoints,
                    std::size(__NVDelayBeforeSwapEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideo Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVPresentVideo::NVPresentVideo()
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVPresentVideo::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_present_video");
}

void NVPresentVideo::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVPresentVideoEntryPoints,
                    std::size(__NVPresentVideoEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVSwapGroup Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVSwapGroup::NVSwapGroup()
{
    std::for_each_n(__NVSwapGroupEntryPoints,
                    std::size(__NVSwapGroupEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVSwapGroup::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_swap_group");
}

void NVSwapGroup::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVSwapGroupEntryPoints,
                    std::size(__NVSwapGroupEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCapture Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVideoCapture::NVVideoCapture()
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVVideoCapture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_video_capture");
}

void NVVideoCapture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVideoCaptureEntryPoints,
                    std::size(__NVVideoCaptureEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoOut Member Definitions
////////////////////////////////////////////////////////////////////////////////
NVVideoOut::NVVideoOut()
{
    std::for_each_n(__NVVideoOutEntryPoints,
                    std::size(__NVVideoOutEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool NVVideoOut::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_NV_video_out");
}

void NVVideoOut::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__NVVideoOutEntryPoints,
                    std::size(__NVVideoOutEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

