//! @file ObjectGL/Extensions/AMD.cpp
//! @brief The definition of AMD-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/AMD.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __AMDDebugOutputEntryPoints[] = {
    { offsetof(AMDDebugOutput, glDebugMessageCallback), "glDebugMessageCallbackAMD" },
    { offsetof(AMDDebugOutput, glDebugMessageEnable), "glDebugMessageEnableAMD" },
    { offsetof(AMDDebugOutput, glDebugMessageInsert), "glDebugMessageInsertAMD" },
    { offsetof(AMDDebugOutput, glGetDebugMessageLog), "glGetDebugMessageLogAMD" },
};

static const size_t __AMDDebugOutputEntryCount = sizeof(__AMDDebugOutputEntryPoints) /
sizeof(__AMDDebugOutputEntryPoints[0]);

static const EntryOffset __AMDDrawBuffersBlendEntryPoints[] = {
    { offsetof(AMDDrawBuffersBlend, glBlendEquationIndexed), "glBlendEquationIndexedAMD" },
    { offsetof(AMDDrawBuffersBlend, glBlendEquationSeparateIndexed), "glBlendEquationSeparateIndexedAMD" },
    { offsetof(AMDDrawBuffersBlend, glBlendFuncIndexed), "glBlendFuncIndexedAMD" },
    { offsetof(AMDDrawBuffersBlend, glBlendFuncSeparateIndexed), "glBlendFuncSeparateIndexedAMD" },
};

static const size_t __AMDDrawBuffersBlendEntryCount = sizeof(__AMDDrawBuffersBlendEntryPoints) /
sizeof(__AMDDrawBuffersBlendEntryPoints[0]);

static const EntryOffset __AMDFramebufferMultisampleAdvancedEntryPoints[] = {
    { offsetof(AMDFramebufferMultisampleAdvanced, glNamedRenderbufferStorageMultisampleAdvanced), "glNamedRenderbufferStorageMultisampleAdvancedAMD" },
    { offsetof(AMDFramebufferMultisampleAdvanced, glRenderbufferStorageMultisampleAdvanced), "glRenderbufferStorageMultisampleAdvancedAMD" },
};

static const size_t __AMDFramebufferMultisampleAdvancedEntryCount = sizeof(__AMDFramebufferMultisampleAdvancedEntryPoints) /
sizeof(__AMDFramebufferMultisampleAdvancedEntryPoints[0]);

static const EntryOffset __AMDFramebufferSamplePositionsEntryPoints[] = {
    { offsetof(AMDFramebufferSamplePositions, glFramebufferSamplePositionsfv), "glFramebufferSamplePositionsfvAMD" },
    { offsetof(AMDFramebufferSamplePositions, glGetFramebufferParameterfv), "glGetFramebufferParameterfvAMD" },
    { offsetof(AMDFramebufferSamplePositions, glGetNamedFramebufferParameterfv), "glGetNamedFramebufferParameterfvAMD" },
    { offsetof(AMDFramebufferSamplePositions, glNamedFramebufferSamplePositionsfv), "glNamedFramebufferSamplePositionsfvAMD" },
};

static const size_t __AMDFramebufferSamplePositionsEntryCount = sizeof(__AMDFramebufferSamplePositionsEntryPoints) /
sizeof(__AMDFramebufferSamplePositionsEntryPoints[0]);

static const EntryOffset __AMDGPUShaderInt64EntryPoints[] = {
    { offsetof(AMDGPUShaderInt64, glGetUniformi64v), "glGetUniformi64vNV" },
    { offsetof(AMDGPUShaderInt64, glGetUniformui64v), "glGetUniformui64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform1i64), "glProgramUniform1i64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform1i64v), "glProgramUniform1i64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform1ui64), "glProgramUniform1ui64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform1ui64v), "glProgramUniform1ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform2i64), "glProgramUniform2i64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform2i64v), "glProgramUniform2i64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform2ui64), "glProgramUniform2ui64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform2ui64v), "glProgramUniform2ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform3i64), "glProgramUniform3i64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform3i64v), "glProgramUniform3i64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform3ui64), "glProgramUniform3ui64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform3ui64v), "glProgramUniform3ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform4i64), "glProgramUniform4i64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform4i64v), "glProgramUniform4i64vNV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform4ui64), "glProgramUniform4ui64NV" },
    { offsetof(AMDGPUShaderInt64, glProgramUniform4ui64v), "glProgramUniform4ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform1i64), "glUniform1i64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform1i64v), "glUniform1i64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform1ui64), "glUniform1ui64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform1ui64v), "glUniform1ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform2i64), "glUniform2i64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform2i64v), "glUniform2i64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform2ui64), "glUniform2ui64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform2ui64v), "glUniform2ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform3i64), "glUniform3i64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform3i64v), "glUniform3i64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform3ui64), "glUniform3ui64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform3ui64v), "glUniform3ui64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform4i64), "glUniform4i64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform4i64v), "glUniform4i64vNV" },
    { offsetof(AMDGPUShaderInt64, glUniform4ui64), "glUniform4ui64NV" },
    { offsetof(AMDGPUShaderInt64, glUniform4ui64v), "glUniform4ui64vNV" },
};

static const size_t __AMDGPUShaderInt64EntryCount = sizeof(__AMDGPUShaderInt64EntryPoints) /
sizeof(__AMDGPUShaderInt64EntryPoints[0]);

static const EntryOffset __AMDInterleavedElementsEntryPoints[] = {
    { offsetof(AMDInterleavedElements, glVertexAttribParameteri), "glVertexAttribParameteriAMD" },
};

static const size_t __AMDInterleavedElementsEntryCount = sizeof(__AMDInterleavedElementsEntryPoints) /
sizeof(__AMDInterleavedElementsEntryPoints[0]);

static const EntryOffset __AMDMultiDrawIndirectEntryPoints[] = {
    { offsetof(AMDMultiDrawIndirect, glMultiDrawArraysIndirect), "glMultiDrawArraysIndirectAMD" },
    { offsetof(AMDMultiDrawIndirect, glMultiDrawElementsIndirect), "glMultiDrawElementsIndirectAMD" },
};

static const size_t __AMDMultiDrawIndirectEntryCount = sizeof(__AMDMultiDrawIndirectEntryPoints) /
sizeof(__AMDMultiDrawIndirectEntryPoints[0]);

static const EntryOffset __AMDNameGenDeleteEntryPoints[] = {
    { offsetof(AMDNameGenDelete, glDeleteNames), "glDeleteNamesAMD" },
    { offsetof(AMDNameGenDelete, glGenNames), "glGenNamesAMD" },
    { offsetof(AMDNameGenDelete, glIsName), "glIsNameAMD" },
};

static const size_t __AMDNameGenDeleteEntryCount = sizeof(__AMDNameGenDeleteEntryPoints) /
sizeof(__AMDNameGenDeleteEntryPoints[0]);

static const EntryOffset __AMDOcclusionQueryEventEntryPoints[] = {
    { offsetof(AMDOcclusionQueryEvent, glQueryObjectParameterui), "glQueryObjectParameteruiAMD" },
};

static const size_t __AMDOcclusionQueryEventEntryCount = sizeof(__AMDOcclusionQueryEventEntryPoints) /
sizeof(__AMDOcclusionQueryEventEntryPoints[0]);

static const EntryOffset __AMDPerformanceMonitorEntryPoints[] = {
    { offsetof(AMDPerformanceMonitor, glBeginPerfMonitor), "glBeginPerfMonitorAMD" },
    { offsetof(AMDPerformanceMonitor, glDeletePerfMonitors), "glDeletePerfMonitorsAMD" },
    { offsetof(AMDPerformanceMonitor, glEndPerfMonitor), "glEndPerfMonitorAMD" },
    { offsetof(AMDPerformanceMonitor, glGenPerfMonitors), "glGenPerfMonitorsAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorCounterData), "glGetPerfMonitorCounterDataAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorCounterInfo), "glGetPerfMonitorCounterInfoAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorCounterString), "glGetPerfMonitorCounterStringAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorCounters), "glGetPerfMonitorCountersAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorGroupString), "glGetPerfMonitorGroupStringAMD" },
    { offsetof(AMDPerformanceMonitor, glGetPerfMonitorGroups), "glGetPerfMonitorGroupsAMD" },
    { offsetof(AMDPerformanceMonitor, glSelectPerfMonitorCounters), "glSelectPerfMonitorCountersAMD" },
};

static const size_t __AMDPerformanceMonitorEntryCount = sizeof(__AMDPerformanceMonitorEntryPoints) /
sizeof(__AMDPerformanceMonitorEntryPoints[0]);

static const EntryOffset __AMDSamplePositionsEntryPoints[] = {
    { offsetof(AMDSamplePositions, glSetMultisamplefv), "glSetMultisamplefvAMD" },
};

static const size_t __AMDSamplePositionsEntryCount = sizeof(__AMDSamplePositionsEntryPoints) /
sizeof(__AMDSamplePositionsEntryPoints[0]);

static const EntryOffset __AMDSparseTextureEntryPoints[] = {
    { offsetof(AMDSparseTexture, glTexStorageSparse), "glTexStorageSparseAMD" },
    { offsetof(AMDSparseTexture, glTextureStorageSparse), "glTextureStorageSparseAMD" },
};

static const size_t __AMDSparseTextureEntryCount = sizeof(__AMDSparseTextureEntryPoints) /
sizeof(__AMDSparseTextureEntryPoints[0]);

static const EntryOffset __AMDStencilOperationExtendedEntryPoints[] = {
    { offsetof(AMDStencilOperationExtended, glStencilOpValue), "glStencilOpValueAMD" },
};

static const size_t __AMDStencilOperationExtendedEntryCount = sizeof(__AMDStencilOperationExtendedEntryPoints) /
sizeof(__AMDStencilOperationExtendedEntryPoints[0]);

static const EntryOffset __AMDVertexShaderTessellatorEntryPoints[] = {
    { offsetof(AMDVertexShaderTessellator, glTessellationFactor), "glTessellationFactorAMD" },
    { offsetof(AMDVertexShaderTessellator, glTessellationMode), "glTessellationModeAMD" },
};

static const size_t __AMDVertexShaderTessellatorEntryCount = sizeof(__AMDVertexShaderTessellatorEntryPoints) /
sizeof(__AMDVertexShaderTessellatorEntryPoints[0]);


} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// AMDDebugOutput Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDDebugOutput::AMDDebugOutput()
{
    std::for_each_n(__AMDDebugOutputEntryPoints,
                    std::size(__AMDDebugOutputEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDDebugOutput::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_debug_output");
}

void AMDDebugOutput::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDDebugOutputEntryPoints,
                    std::size(__AMDDebugOutputEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDDrawBuffersBlend Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDDrawBuffersBlend::AMDDrawBuffersBlend()
{
    std::for_each_n(__AMDDrawBuffersBlendEntryPoints,
                    std::size(__AMDDrawBuffersBlendEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDDrawBuffersBlend::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_draw_buffers_blend");
}

void AMDDrawBuffersBlend::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDDrawBuffersBlendEntryPoints,
                    std::size(__AMDDrawBuffersBlendEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDFramebufferMultisampleAdvanced Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDFramebufferMultisampleAdvanced::AMDFramebufferMultisampleAdvanced()
{
    std::for_each_n(__AMDFramebufferMultisampleAdvancedEntryPoints,
                    std::size(__AMDFramebufferMultisampleAdvancedEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDFramebufferMultisampleAdvanced::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_framebuffer_multisample_advanced");
}

void AMDFramebufferMultisampleAdvanced::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDFramebufferMultisampleAdvancedEntryPoints,
                    std::size(__AMDFramebufferMultisampleAdvancedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDFramebufferSamplePositions Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDFramebufferSamplePositions::AMDFramebufferSamplePositions()
{
    std::for_each_n(__AMDFramebufferSamplePositionsEntryPoints,
                    std::size(__AMDFramebufferSamplePositionsEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDFramebufferSamplePositions::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_framebuffer_sample_positions");
}

void AMDFramebufferSamplePositions::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDFramebufferSamplePositionsEntryPoints,
                    std::size(__AMDFramebufferSamplePositionsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDGPUShaderInt64 Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDGPUShaderInt64::AMDGPUShaderInt64()
{
    std::for_each_n(__AMDGPUShaderInt64EntryPoints,
                    std::size(__AMDGPUShaderInt64EntryPoints),
                    ClearEntryPoint(this));
}

bool AMDGPUShaderInt64::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_gpu_shader_int64");
}

void AMDGPUShaderInt64::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDGPUShaderInt64EntryPoints,
                    std::size(__AMDGPUShaderInt64EntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDInterleavedElements Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDInterleavedElements::AMDInterleavedElements()
{
    std::for_each_n(__AMDInterleavedElementsEntryPoints,
                    std::size(__AMDInterleavedElementsEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDInterleavedElements::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_interleaved_elements");
}

void AMDInterleavedElements::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDInterleavedElementsEntryPoints,
                    std::size(__AMDInterleavedElementsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDMultiDrawIndirect Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDMultiDrawIndirect::AMDMultiDrawIndirect()
{
    std::for_each_n(__AMDMultiDrawIndirectEntryPoints,
                    std::size(__AMDMultiDrawIndirectEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDMultiDrawIndirect::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_multi_draw_indirect");
}

void AMDMultiDrawIndirect::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDMultiDrawIndirectEntryPoints,
                    std::size(__AMDMultiDrawIndirectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDNameGenDelete Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDNameGenDelete::AMDNameGenDelete()
{
    std::for_each_n(__AMDNameGenDeleteEntryPoints,
                    std::size(__AMDNameGenDeleteEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDNameGenDelete::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_name_gen_delete");
}

void AMDNameGenDelete::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDNameGenDeleteEntryPoints,
                    std::size(__AMDNameGenDeleteEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDOcclusionQueryEvent Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDOcclusionQueryEvent::AMDOcclusionQueryEvent()
{
    std::for_each_n(__AMDOcclusionQueryEventEntryPoints,
                    std::size(__AMDOcclusionQueryEventEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDOcclusionQueryEvent::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_occlusion_query_event");
}

void AMDOcclusionQueryEvent::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDOcclusionQueryEventEntryPoints,
                    std::size(__AMDOcclusionQueryEventEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDPerformanceMonitor Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDPerformanceMonitor::AMDPerformanceMonitor()
{
    std::for_each_n(__AMDPerformanceMonitorEntryPoints,
                    std::size(__AMDPerformanceMonitorEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDPerformanceMonitor::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_performance_monitor");
}

void AMDPerformanceMonitor::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDPerformanceMonitorEntryPoints,
                    std::size(__AMDPerformanceMonitorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDSamplePositions Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDSamplePositions::AMDSamplePositions()
{
    std::for_each_n(__AMDSamplePositionsEntryPoints,
                    std::size(__AMDSamplePositionsEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDSamplePositions::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_sample_positions");
}

void AMDSamplePositions::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDSamplePositionsEntryPoints,
                    std::size(__AMDSamplePositionsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDSparseTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDSparseTexture::AMDSparseTexture()
{
    std::for_each_n(__AMDSparseTextureEntryPoints,
                    std::size(__AMDSparseTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDSparseTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_sparse_texture");
}

void AMDSparseTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDSparseTextureEntryPoints,
                    std::size(__AMDSparseTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDStencilOperationExtended Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDStencilOperationExtended::AMDStencilOperationExtended()
{
    std::for_each_n(__AMDStencilOperationExtendedEntryPoints,
                    std::size(__AMDStencilOperationExtendedEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDStencilOperationExtended::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_stencil_operation_extended");
}

void AMDStencilOperationExtended::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDStencilOperationExtendedEntryPoints,
                    std::size(__AMDStencilOperationExtendedEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// AMDVertexShaderTessellator Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDVertexShaderTessellator::AMDVertexShaderTessellator()
{
    std::for_each_n(__AMDVertexShaderTessellatorEntryPoints,
                    std::size(__AMDVertexShaderTessellatorEntryPoints),
                    ClearEntryPoint(this));
}

bool AMDVertexShaderTessellator::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_AMD_vertex_shader_tessellator");
}

void AMDVertexShaderTessellator::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDVertexShaderTessellatorEntryPoints,
                    std::size(__AMDVertexShaderTessellatorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl

#ifdef _WIN32
namespace wgl {
namespace {

static const gl::EntryOffset __AMDGPUAssociationEntryPoints[] = {
    { offsetof(AMDGPUAssociation, wglBlitContextFramebuffer), "wglBlitContextFramebufferAMD" },
    { offsetof(AMDGPUAssociation, wglCreateAssociatedContext), "wglCreateAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, wglCreateAssociatedContextAttribs), "wglCreateAssociatedContextAttribsAMD" },
    { offsetof(AMDGPUAssociation, wglDeleteAssociatedContext), "wglDeleteAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, wglGetContextGPUID), "wglGetContextGPUIDAMD" },
    { offsetof(AMDGPUAssociation, wglGetCurrentAssociatedContext), "wglGetCurrentAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, wglGetGPUIDs), "wglGetGPUIDsAMD" },
    { offsetof(AMDGPUAssociation, wglGetGPUInfo), "wglGetGPUInfoAMD" },
    { offsetof(AMDGPUAssociation, wglMakeAssociatedContextCurrent), "wglMakeAssociatedContextCurrentAMD" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// AMDGPUAssociation Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDGPUAssociation::AMDGPUAssociation()
{
    std::for_each_n(__AMDGPUAssociationEntryPoints,
                    std::size(__AMDGPUAssociationEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool AMDGPUAssociation::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_AMD_gpu_association");
}

void AMDGPUAssociation::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDGPUAssociationEntryPoints,
                    std::size(__AMDGPUAssociationEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {
namespace {

static const gl::EntryOffset __AMDGPUAssociationEntryPoints[] = {
    { offsetof(AMDGPUAssociation, glXBlitContextFramebuffer), "glXBlitContextFramebufferAMD" },
    { offsetof(AMDGPUAssociation, glXCreateAssociatedContext), "glXCreateAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, glXCreateAssociatedContextAttribs), "glXCreateAssociatedContextAttribsAMD" },
    { offsetof(AMDGPUAssociation, glXDeleteAssociatedContext), "glXDeleteAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, glXGetContextGPUID), "glXGetContextGPUIDAMD" },
    { offsetof(AMDGPUAssociation, glXGetCurrentAssociatedContext), "glXGetCurrentAssociatedContextAMD" },
    { offsetof(AMDGPUAssociation, glXGetGPUIDs), "glXGetGPUIDsAMD" },
    { offsetof(AMDGPUAssociation, glXGetGPUInfo), "glXGetGPUInfoAMD" },
    { offsetof(AMDGPUAssociation, glXMakeAssociatedContextCurrent), "glXMakeAssociatedContextCurrentAMD" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// AMDGPUAssociation Member Definitions
////////////////////////////////////////////////////////////////////////////////
AMDGPUAssociation::AMDGPUAssociation()
{
    std::for_each_n(__AMDGPUAssociationEntryPoints,
                    std::size(__AMDGPUAssociationEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool AMDGPUAssociation::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GLX_AMD_gpu_association");
}

void AMDGPUAssociation::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__AMDGPUAssociationEntryPoints,
                    std::size(__AMDGPUAssociationEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} //namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////