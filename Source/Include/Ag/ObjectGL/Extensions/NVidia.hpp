//! @file Ag/ObjectGL/Extensions/NVidia.hpp
//! @brief The declaration of nVidia-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_NVIDIA_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_NVIDIA_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

#ifdef _WIN32
#include "../WGL_Types.hpp"
#endif // ifdef _WIN32

#ifdef _USES_GLX
#include "../GLX_Types.hpp"
#endif // ifdef _USES_GLX

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_NVX_conditional_render extension API specification.
struct NVXConditionalRender {
    // Public Members
    void (APIENTRY *glBeginConditionalRender)(GLuint id);
    void (APIENTRY *glEndConditionalRender)();

    // Construction
    NVXConditionalRender();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVXConditionalRender

// GL_NVX_gpu_multicast2 extension API specification.
struct NVXGPUMULTICAST2 {
    // Public Members
    GLuint(APIENTRY *glAsyncCopyBufferSubData)(GLsizei waitSemaphoreCount,
                                               const GLuint *waitSemaphoreArray,
                                               const GLuint64 *fenceValueArray,
                                               GLuint readGpu,
                                               GLbitfield writeGpuMask,
                                               GLuint readBuffer,
                                               GLuint writeBuffer,
                                               GLintptr readOffset,
                                               GLintptr writeOffset,
                                               GLsizeiptr size,
                                               GLsizei signalSemaphoreCount,
                                               const GLuint *signalSemaphoreArray,
                                               const GLuint64 *signalValueArray);
    GLuint(APIENTRY *glAsyncCopyImageSubData)(GLsizei waitSemaphoreCount,
                                              const GLuint *waitSemaphoreArray,
                                              const GLuint64 *waitValueArray,
                                              GLuint srcGpu,
                                              GLbitfield dstGpuMask,
                                              GLuint srcName, GLenum srcTarget,
                                              GLint srcLevel, GLint srcX,
                                              GLint srcY, GLint srcZ,
                                              GLuint dstName, GLenum dstTarget,
                                              GLint dstLevel, GLint dstX,
                                              GLint dstY, GLint dstZ,
                                              GLsizei srcWidth,
                                              GLsizei srcHeight,
                                              GLsizei srcDepth,
                                              GLsizei signalSemaphoreCount,
                                              const GLuint *signalSemaphoreArray,
                                              const GLuint64 *signalValueArray);
    void (APIENTRY *glMulticastScissorArrayv)(GLuint gpu, GLuint first,
                                              GLsizei count, const GLint *v);
    void (APIENTRY *glMulticastViewportArrayv)(GLuint gpu, GLuint first,
                                               GLsizei count, const GLfloat *v);
    void (APIENTRY *glMulticastViewportPositionWScale)(GLuint gpu, GLuint index,
                                                       GLfloat xcoeff,
                                                       GLfloat ycoeff);
    void (APIENTRY *glUploadGpuMask)(GLbitfield mask);

    // Construction
    NVXGPUMULTICAST2();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVXGPUMULTICAST2

// GL_NVX_linked_gpu_multicast extension API specification.
struct NVXLinkedGPUMulticast {
    // Public Members
    void (APIENTRY *glLGPUCopyImageSubData)(GLuint sourceGpu,
                                            GLbitfield destinationGpuMask,
                                            GLuint srcName, GLenum srcTarget,
                                            GLint srcLevel, GLint srcX,
                                            GLint srxY, GLint srcZ,
                                            GLuint dstName, GLenum dstTarget,
                                            GLint dstLevel, GLint dstX,
                                            GLint dstY, GLint dstZ,
                                            GLsizei width, GLsizei height,
                                            GLsizei depth);
    void (APIENTRY *glLGPUInterlock)();
    void (APIENTRY *glLGPUNamedBufferSubData)(GLbitfield gpuMask, GLuint buffer,
                                              GLintptr offset, GLsizeiptr size,
                                              const void *data);

    // Construction
    NVXLinkedGPUMulticast();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVXLinkedGPUMulticast

// GL_NVX_progress_fence extension API specification.
struct NVXProgressFence {
    // Public Members
    void (APIENTRY *glClientWaitSemaphoreui64)(GLsizei fenceObjectCount,
                                               const GLuint *semaphoreArray,
                                               const GLuint64 *fenceValueArray);
    GLuint(APIENTRY *glCreateProgressFence)();
    void (APIENTRY *glSignalSemaphoreui64)(GLuint signalGpu,
                                           GLsizei fenceObjectCount,
                                           const GLuint *semaphoreArray,
                                           const GLuint64 *fenceValueArray);
    void (APIENTRY *glWaitSemaphoreui64)(GLuint waitGpu,
                                         GLsizei fenceObjectCount,
                                         const GLuint *semaphoreArray,
                                         const GLuint64 *fenceValueArray);

    // Construction
    NVXProgressFence();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVXProgressFence

// GL_NV_alpha_to_coverage_dither_control extension API specification.
struct NVAlphaToCoverageDitherControl {
    // Public Members
    void (APIENTRY *glAlphaToCoverageDitherControl)(GLenum mode);

    // Construction
    NVAlphaToCoverageDitherControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVAlphaToCoverageDitherControl

// GL_NV_bindless_multi_draw_indirect extension API specification.
struct NVBindlessMultiDrawIndirect {
    // Public Members
    void (APIENTRY *glMultiDrawArraysIndirectBindless)(GLenum mode,
                                                       const void *indirect,
                                                       GLsizei drawCount,
                                                       GLsizei stride,
                                                       GLint vertexBufferCount);
    void (APIENTRY *glMultiDrawElementsIndirectBindless)(GLenum mode,
                                                         GLenum type,
                                                         const void *indirect,
                                                         GLsizei drawCount,
                                                         GLsizei stride,
                                                         GLint vertexBufferCount);

    // Construction
    NVBindlessMultiDrawIndirect();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVBindlessMultiDrawIndirect

// GL_NV_bindless_multi_draw_indirect_count extension API specification.
struct NVBindlessMultiDrawIndirectCount {
    // Public Members
    void (APIENTRY *glMultiDrawArraysIndirectBindlessCount)(GLenum mode,
                                                            const void *indirect,
                                                            GLsizei drawCount,
                                                            GLsizei maxDrawCount,
                                                            GLsizei stride,
                                                            GLint vertexBufferCount);
    void (APIENTRY *glMultiDrawElementsIndirectBindlessCount)(GLenum mode,
                                                              GLenum type,
                                                              const void *indirect,
                                                              GLsizei drawCount,
                                                              GLsizei maxDrawCount,
                                                              GLsizei stride,
                                                              GLint vertexBufferCount);

    // Construction
    NVBindlessMultiDrawIndirectCount();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVBindlessMultiDrawIndirectCount

// GL_NV_bindless_texture extension API specification.
struct NVBindlessTexture {
    // Public Members
    GLuint64(APIENTRY *glGetImageHandle)(GLuint texture, GLint level,
                                         GLboolean layered, GLint layer,
                                         GLenum format);
    GLuint64(APIENTRY *glGetTextureHandle)(GLuint texture);
    GLuint64(APIENTRY *glGetTextureSamplerHandle)(GLuint texture,
                                                  GLuint sampler);
    GLboolean(APIENTRY *glIsImageHandleResident)(GLuint64 handle);
    GLboolean(APIENTRY *glIsTextureHandleResident)(GLuint64 handle);
    void (APIENTRY *glMakeImageHandleNonResident)(GLuint64 handle);
    void (APIENTRY *glMakeImageHandleResident)(GLuint64 handle, GLenum access);
    void (APIENTRY *glMakeTextureHandleNonResident)(GLuint64 handle);
    void (APIENTRY *glMakeTextureHandleResident)(GLuint64 handle);
    void (APIENTRY *glProgramUniformHandleui64)(GLuint program, GLint location,
                                                GLuint64 value);
    void (APIENTRY *glProgramUniformHandleui64v)(GLuint program, GLint location,
                                                 GLsizei count,
                                                 const GLuint64 *values);
    void (APIENTRY *glUniformHandleui64)(GLint location, GLuint64 value);
    void (APIENTRY *glUniformHandleui64v)(GLint location, GLsizei count,
                                          const GLuint64 *value);

    // Construction
    NVBindlessTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVBindlessTexture

// GL_NV_blend_equation_advanced extension API specification.
struct NVBlendEquationAdvanced {
    // Public Members
    void (APIENTRY *glBlendBarrier)();
    void (APIENTRY *glBlendParameteri)(GLenum pname, GLint value);

    // Construction
    NVBlendEquationAdvanced();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVBlendEquationAdvanced

// GL_NV_clip_space_w_scaling extension API specification.
struct NVClipSpaceWScaling {
    // Public Members
    void (APIENTRY *glViewportPositionWScale)(GLuint index, GLfloat xcoeff,
                                              GLfloat ycoeff);

    // Construction
    NVClipSpaceWScaling();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVClipSpaceWScaling

// GL_NV_command_list extension API specification.
struct NVCommandList {
    // Public Members
    void (APIENTRY *glCallCommandList)(GLuint list);
    void (APIENTRY *glCommandListSegments)(GLuint list, GLuint segments);
    void (APIENTRY *glCompileCommandList)(GLuint list);
    void (APIENTRY *glCreateCommandLists)(GLsizei n, GLuint *lists);
    void (APIENTRY *glCreateStates)(GLsizei n, GLuint *states);
    void (APIENTRY *glDeleteCommandLists)(GLsizei n, const GLuint *lists);
    void (APIENTRY *glDeleteStates)(GLsizei n, const GLuint *states);
    void (APIENTRY *glDrawCommandsAddress)(GLenum primitiveMode,
                                           const GLuint64 *indirects,
                                           const GLsizei *sizes, GLuint count);
    void (APIENTRY *glDrawCommands)(GLenum primitiveMode, GLuint buffer,
                                    const GLintptr *indirects,
                                    const GLsizei *sizes, GLuint count);
    void (APIENTRY *glDrawCommandsStatesAddress)(const GLuint64 *indirects,
                                                 const GLsizei *sizes,
                                                 const GLuint *states,
                                                 const GLuint *fbos,
                                                 GLuint count);
    void (APIENTRY *glDrawCommandsStates)(GLuint buffer,
                                          const GLintptr *indirects,
                                          const GLsizei *sizes,
                                          const GLuint *states,
                                          const GLuint *fbos, GLuint count);
    GLuint(APIENTRY *glGetCommandHeader)(GLenum tokenID, GLuint size);
    GLushort(APIENTRY *glGetStageIndex)(GLenum shadertype);
    GLboolean(APIENTRY *glIsCommandList)(GLuint list);
    GLboolean(APIENTRY *glIsState)(GLuint state);
    void (APIENTRY *glListDrawCommandsStatesClient)(GLuint list, GLuint segment,
                                                    const void **indirects,
                                                    const GLsizei *sizes,
                                                    const GLuint *states,
                                                    const GLuint *fbos,
                                                    GLuint count);
    void (APIENTRY *glStateCapture)(GLuint state, GLenum mode);

    // Construction
    NVCommandList();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVCommandList

// GL_NV_conditional_render extension API specification.
struct NVConditionalRender {
    // Public Members
    void (APIENTRY *glBeginConditionalRender)(GLuint id, GLenum mode);
    void (APIENTRY *glEndConditionalRender)();

    // Construction
    NVConditionalRender();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVConditionalRender

// GL_NV_conservative_raster extension API specification.
struct NVConservativeRaster {
    // Public Members
    void (APIENTRY *glSubpixelPrecisionBias)(GLuint xbits, GLuint ybits);

    // Construction
    NVConservativeRaster();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVConservativeRaster

// GL_NV_conservative_raster_dilate extension API specification.
struct NVConservativeRasterDilate {
    // Public Members
    void (APIENTRY *glConservativeRasterParameterf)(GLenum pname, GLfloat value);

    // Construction
    NVConservativeRasterDilate();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVConservativeRasterDilate

// GL_NV_conservative_raster_pre_snap_triangles extension API specification.
struct NVConservativeRasterPreSnapTriangles {
    // Public Members
    void (APIENTRY *glConservativeRasterParameteri)(GLenum pname, GLint param);

    // Construction
    NVConservativeRasterPreSnapTriangles();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVConservativeRasterPreSnapTriangles

// GL_NV_copy_image extension API specification.
struct NVCopyImage {
    // Public Members
    void (APIENTRY *glCopyImageSubData)(GLuint srcName, GLenum srcTarget,
                                        GLint srcLevel, GLint srcX, GLint srcY,
                                        GLint srcZ, GLuint dstName,
                                        GLenum dstTarget, GLint dstLevel,
                                        GLint dstX, GLint dstY, GLint dstZ,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth);

    // Construction
    NVCopyImage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVCopyImage

// GL_NV_depth_buffer_float extension API specification.
struct NVDepthBufferFloat {
    // Public Members
    void (APIENTRY *glClearDepthd)(GLdouble depth);
    void (APIENTRY *glDepthBoundsd)(GLdouble zmin, GLdouble zmax);
    void (APIENTRY *glDepthRanged)(GLdouble zNear, GLdouble zFar);

    // Construction
    NVDepthBufferFloat();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDepthBufferFloat

// GL_NV_draw_texture extension API specification.
struct NVDrawTexture {
    // Public Members
    void (APIENTRY *glDrawTexture)(GLuint texture, GLuint sampler, GLfloat x0,
                                   GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z,
                                   GLfloat s0, GLfloat t0, GLfloat s1,
                                   GLfloat t1);

    // Construction
    NVDrawTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDrawTexture

// GL_NV_draw_vulkan_image extension API specification.
struct NVDrawVulkanImage {
    // Public Members
    void (APIENTRY *glDrawVkImage)(GLuint64 vkImage, GLuint sampler, GLfloat x0,
                                   GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z,
                                   GLfloat s0, GLfloat t0, GLfloat s1,
                                   GLfloat t1);
    GLVULKANPROCNV(APIENTRY *glGetVkProcAddr)(const GLchar *name);
    void (APIENTRY *glSignalVkFence)(GLuint64 vkFence);
    void (APIENTRY *glSignalVkSemaphore)(GLuint64 vkSemaphore);
    void (APIENTRY *glWaitVkSemaphore)(GLuint64 vkSemaphore);

    // Construction
    NVDrawVulkanImage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDrawVulkanImage

// GL_NV_evaluators extension API specification.
struct NVEvaluators {
    // Public Members
    void (APIENTRY *glEvalMaps)(GLenum target, GLenum mode);
    void (APIENTRY *glGetMapAttribParameterfv)(GLenum target, GLuint index,
                                               GLenum pname, GLfloat *params);
    void (APIENTRY *glGetMapAttribParameteriv)(GLenum target, GLuint index,
                                               GLenum pname, GLint *params);
    void (APIENTRY *glGetMapControlPoints)(GLenum target, GLuint index,
                                           GLenum type, GLsizei ustride,
                                           GLsizei vstride, GLboolean packed,
                                           void *points);
    void (APIENTRY *glGetMapParameterfv)(GLenum target, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetMapParameteriv)(GLenum target, GLenum pname,
                                         GLint *params);
    void (APIENTRY *glMapControlPoints)(GLenum target, GLuint index, GLenum type,
                                        GLsizei ustride, GLsizei vstride,
                                        GLint uorder, GLint vorder,
                                        GLboolean packed, const void *points);
    void (APIENTRY *glMapParameterfv)(GLenum target, GLenum pname,
                                      const GLfloat *params);
    void (APIENTRY *glMapParameteriv)(GLenum target, GLenum pname,
                                      const GLint *params);

    // Construction
    NVEvaluators();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVEvaluators

// GL_NV_explicit_multisample extension API specification.
struct NVExplicitMultisample {
    // Public Members
    void (APIENTRY *glGetMultisamplefv)(GLenum pname, GLuint index, GLfloat *val);
    void (APIENTRY *glSampleMaskIndexed)(GLuint index, GLbitfield mask);
    void (APIENTRY *glTexRenderbuffer)(GLenum target, GLuint renderbuffer);

    // Construction
    NVExplicitMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVExplicitMultisample

// GL_NV_fence extension API specification.
struct NVFence {
    // Public Members
    void (APIENTRY *glDeleteFences)(GLsizei n, const GLuint *fences);
    void (APIENTRY *glFinishFence)(GLuint fence);
    void (APIENTRY *glGenFences)(GLsizei n, GLuint *fences);
    void (APIENTRY *glGetFenceiv)(GLuint fence, GLenum pname, GLint *params);
    GLboolean(APIENTRY *glIsFence)(GLuint fence);
    void (APIENTRY *glSetFence)(GLuint fence, GLenum condition);
    GLboolean(APIENTRY *glTestFence)(GLuint fence);

    // Construction
    NVFence();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVFence

// GL_NV_fragment_coverage_to_color extension API specification.
struct NVFragmentCoverageToColor {
    // Public Members
    void (APIENTRY *glFragmentCoverageColor)(GLuint color);

    // Construction
    NVFragmentCoverageToColor();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVFragmentCoverageToColor

// GL_NV_fragment_program extension API specification.
struct NVFragmentProgram {
    // Public Members
    void (APIENTRY *glGetProgramNamedParameterdv)(GLuint id, GLsizei len,
                                                  const GLubyte *name,
                                                  GLdouble *params);
    void (APIENTRY *glGetProgramNamedParameterfv)(GLuint id, GLsizei len,
                                                  const GLubyte *name,
                                                  GLfloat *params);
    void (APIENTRY *glProgramNamedParameter4d)(GLuint id, GLsizei len,
                                               const GLubyte *name, GLdouble x,
                                               GLdouble y, GLdouble z,
                                               GLdouble w);
    void (APIENTRY *glProgramNamedParameter4dv)(GLuint id, GLsizei len,
                                                const GLubyte *name,
                                                const GLdouble *v);
    void (APIENTRY *glProgramNamedParameter4f)(GLuint id, GLsizei len,
                                               const GLubyte *name, GLfloat x,
                                               GLfloat y, GLfloat z, GLfloat w);
    void (APIENTRY *glProgramNamedParameter4fv)(GLuint id, GLsizei len,
                                                const GLubyte *name,
                                                const GLfloat *v);

    // Construction
    NVFragmentProgram();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVFragmentProgram

// GL_NV_framebuffer_mixed_samples extension API specification.
struct NVFramebufferMixedSamples {
    // Public Members
    void (APIENTRY *glCoverageModulation)(GLenum components);
    void (APIENTRY *glCoverageModulationTable)(GLsizei n, const GLfloat *v);
    void (APIENTRY *glGetCoverageModulationTable)(GLsizei bufSize, GLfloat *v);

    // Construction
    NVFramebufferMixedSamples();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVFramebufferMixedSamples

// GL_NV_framebuffer_multisample_coverage extension API specification.
struct NVFramebufferMultisampleCoverage {
    // Public Members
    void (APIENTRY *glRenderbufferStorageMultisampleCoverage)(GLenum target,
                                                              GLsizei coverageSamples,
                                                              GLsizei colorSamples,
                                                              GLenum internalformat,
                                                              GLsizei width,
                                                              GLsizei height);

    // Construction
    NVFramebufferMultisampleCoverage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVFramebufferMultisampleCoverage

// GL_NV_geometry_program4 extension API specification.
struct NVGeometryPROGRAM4 {
    // Public Members
    void (APIENTRY *glFramebufferTexture)(GLenum target, GLenum attachment,
                                          GLuint texture, GLint level);
    void (APIENTRY *glFramebufferTextureFace)(GLenum target, GLenum attachment,
                                              GLuint texture, GLint level,
                                              GLenum face);
    void (APIENTRY *glProgramVertexLimit)(GLenum target, GLint limit);

    // Construction
    NVGeometryPROGRAM4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVGeometryPROGRAM4

// GL_NV_gpu_multicast extension API specification.
struct NVGPUMulticast {
    // Public Members
    void (APIENTRY *glMulticastBarrier)();
    void (APIENTRY *glMulticastBlitFramebuffer)(GLuint srcGpu, GLuint dstGpu,
                                                GLint srcX0, GLint srcY0,
                                                GLint srcX1, GLint srcY1,
                                                GLint dstX0, GLint dstY0,
                                                GLint dstX1, GLint dstY1,
                                                GLbitfield mask, GLenum filter);
    void (APIENTRY *glMulticastBufferSubData)(GLbitfield gpuMask, GLuint buffer,
                                              GLintptr offset, GLsizeiptr size,
                                              const void *data);
    void (APIENTRY *glMulticastCopyBufferSubData)(GLuint readGpu,
                                                  GLbitfield writeGpuMask,
                                                  GLuint readBuffer,
                                                  GLuint writeBuffer,
                                                  GLintptr readOffset,
                                                  GLintptr writeOffset,
                                                  GLsizeiptr size);
    void (APIENTRY *glMulticastCopyImageSubData)(GLuint srcGpu,
                                                 GLbitfield dstGpuMask,
                                                 GLuint srcName,
                                                 GLenum srcTarget,
                                                 GLint srcLevel, GLint srcX,
                                                 GLint srcY, GLint srcZ,
                                                 GLuint dstName,
                                                 GLenum dstTarget,
                                                 GLint dstLevel, GLint dstX,
                                                 GLint dstY, GLint dstZ,
                                                 GLsizei srcWidth,
                                                 GLsizei srcHeight,
                                                 GLsizei srcDepth);
    void (APIENTRY *glMulticastFramebufferSampleLocationsfv)(GLuint gpu,
                                                             GLuint framebuffer,
                                                             GLuint start,
                                                             GLsizei count,
                                                             const GLfloat *v);
    void (APIENTRY *glMulticastGetQueryObjecti64v)(GLuint gpu, GLuint id,
                                                   GLenum pname, GLint64 *params);
    void (APIENTRY *glMulticastGetQueryObjectiv)(GLuint gpu, GLuint id,
                                                 GLenum pname, GLint *params);
    void (APIENTRY *glMulticastGetQueryObjectui64v)(GLuint gpu, GLuint id,
                                                    GLenum pname,
                                                    GLuint64 *params);
    void (APIENTRY *glMulticastGetQueryObjectuiv)(GLuint gpu, GLuint id,
                                                  GLenum pname, GLuint *params);
    void (APIENTRY *glMulticastWaitSync)(GLuint signalGpu,
                                         GLbitfield waitGpuMask);
    void (APIENTRY *glRenderGpuMask)(GLbitfield mask);

    // Construction
    NVGPUMulticast();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVGPUMulticast

// GL_NV_gpu_program4 extension API specification.
struct NVGPUPROGRAM4 {
    // Public Members
    void (APIENTRY *glGetProgramEnvParameterIiv)(GLenum target, GLuint index,
                                                 GLint *params);
    void (APIENTRY *glGetProgramEnvParameterIuiv)(GLenum target, GLuint index,
                                                  GLuint *params);
    void (APIENTRY *glGetProgramLocalParameterIiv)(GLenum target, GLuint index,
                                                   GLint *params);
    void (APIENTRY *glGetProgramLocalParameterIuiv)(GLenum target, GLuint index,
                                                    GLuint *params);
    void (APIENTRY *glProgramEnvParameterI4i)(GLenum target, GLuint index,
                                              GLint x, GLint y, GLint z, GLint w);
    void (APIENTRY *glProgramEnvParameterI4iv)(GLenum target, GLuint index,
                                               const GLint *params);
    void (APIENTRY *glProgramEnvParameterI4ui)(GLenum target, GLuint index,
                                               GLuint x, GLuint y, GLuint z,
                                               GLuint w);
    void (APIENTRY *glProgramEnvParameterI4uiv)(GLenum target, GLuint index,
                                                const GLuint *params);
    void (APIENTRY *glProgramEnvParametersI4iv)(GLenum target, GLuint index,
                                                GLsizei count,
                                                const GLint *params);
    void (APIENTRY *glProgramEnvParametersI4uiv)(GLenum target, GLuint index,
                                                 GLsizei count,
                                                 const GLuint *params);
    void (APIENTRY *glProgramLocalParameterI4i)(GLenum target, GLuint index,
                                                GLint x, GLint y, GLint z,
                                                GLint w);
    void (APIENTRY *glProgramLocalParameterI4iv)(GLenum target, GLuint index,
                                                 const GLint *params);
    void (APIENTRY *glProgramLocalParameterI4ui)(GLenum target, GLuint index,
                                                 GLuint x, GLuint y, GLuint z,
                                                 GLuint w);
    void (APIENTRY *glProgramLocalParameterI4uiv)(GLenum target, GLuint index,
                                                  const GLuint *params);
    void (APIENTRY *glProgramLocalParametersI4iv)(GLenum target, GLuint index,
                                                  GLsizei count,
                                                  const GLint *params);
    void (APIENTRY *glProgramLocalParametersI4uiv)(GLenum target, GLuint index,
                                                   GLsizei count,
                                                   const GLuint *params);

    // Construction
    NVGPUPROGRAM4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVGPUPROGRAM4

// GL_NV_gpu_program5 extension API specification.
struct NVGPUPROGRAM5 {
    // Public Members
    void (APIENTRY *glGetProgramSubroutineParameteruiv)(GLenum target,
                                                        GLuint index,
                                                        GLuint *param);
    void (APIENTRY *glProgramSubroutineParametersuiv)(GLenum target,
                                                      GLsizei count,
                                                      const GLuint *params);

    // Construction
    NVGPUPROGRAM5();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVGPUPROGRAM5

// GL_NV_half_float extension API specification.
struct NVHalfFloat {
    // Public Members
    void (APIENTRY *glColor3h)(GLhalfNV red, GLhalfNV green, GLhalfNV blue);
    void (APIENTRY *glColor3hv)(const GLhalfNV *v);
    void (APIENTRY *glColor4h)(GLhalfNV red, GLhalfNV green, GLhalfNV blue,
                               GLhalfNV alpha);
    void (APIENTRY *glColor4hv)(const GLhalfNV *v);
    void (APIENTRY *glFogCoordh)(GLhalfNV fog);
    void (APIENTRY *glFogCoordhv)(const GLhalfNV *fog);
    void (APIENTRY *glMultiTexCoord1h)(GLenum target, GLhalfNV s);
    void (APIENTRY *glMultiTexCoord1hv)(GLenum target, const GLhalfNV *v);
    void (APIENTRY *glMultiTexCoord2h)(GLenum target, GLhalfNV s, GLhalfNV t);
    void (APIENTRY *glMultiTexCoord2hv)(GLenum target, const GLhalfNV *v);
    void (APIENTRY *glMultiTexCoord3h)(GLenum target, GLhalfNV s, GLhalfNV t,
                                       GLhalfNV r);
    void (APIENTRY *glMultiTexCoord3hv)(GLenum target, const GLhalfNV *v);
    void (APIENTRY *glMultiTexCoord4h)(GLenum target, GLhalfNV s, GLhalfNV t,
                                       GLhalfNV r, GLhalfNV q);
    void (APIENTRY *glMultiTexCoord4hv)(GLenum target, const GLhalfNV *v);
    void (APIENTRY *glNormal3h)(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz);
    void (APIENTRY *glNormal3hv)(const GLhalfNV *v);
    void (APIENTRY *glSecondaryColor3h)(GLhalfNV red, GLhalfNV green,
                                        GLhalfNV blue);
    void (APIENTRY *glSecondaryColor3hv)(const GLhalfNV *v);
    void (APIENTRY *glTexCoord1h)(GLhalfNV s);
    void (APIENTRY *glTexCoord1hv)(const GLhalfNV *v);
    void (APIENTRY *glTexCoord2h)(GLhalfNV s, GLhalfNV t);
    void (APIENTRY *glTexCoord2hv)(const GLhalfNV *v);
    void (APIENTRY *glTexCoord3h)(GLhalfNV s, GLhalfNV t, GLhalfNV r);
    void (APIENTRY *glTexCoord3hv)(const GLhalfNV *v);
    void (APIENTRY *glTexCoord4h)(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q);
    void (APIENTRY *glTexCoord4hv)(const GLhalfNV *v);
    void (APIENTRY *glVertex2h)(GLhalfNV x, GLhalfNV y);
    void (APIENTRY *glVertex2hv)(const GLhalfNV *v);
    void (APIENTRY *glVertex3h)(GLhalfNV x, GLhalfNV y, GLhalfNV z);
    void (APIENTRY *glVertex3hv)(const GLhalfNV *v);
    void (APIENTRY *glVertex4h)(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w);
    void (APIENTRY *glVertex4hv)(const GLhalfNV *v);
    void (APIENTRY *glVertexAttrib1h)(GLuint index, GLhalfNV x);
    void (APIENTRY *glVertexAttrib1hv)(GLuint index, const GLhalfNV *v);
    void (APIENTRY *glVertexAttrib2h)(GLuint index, GLhalfNV x, GLhalfNV y);
    void (APIENTRY *glVertexAttrib2hv)(GLuint index, const GLhalfNV *v);
    void (APIENTRY *glVertexAttrib3h)(GLuint index, GLhalfNV x, GLhalfNV y,
                                      GLhalfNV z);
    void (APIENTRY *glVertexAttrib3hv)(GLuint index, const GLhalfNV *v);
    void (APIENTRY *glVertexAttrib4h)(GLuint index, GLhalfNV x, GLhalfNV y,
                                      GLhalfNV z, GLhalfNV w);
    void (APIENTRY *glVertexAttrib4hv)(GLuint index, const GLhalfNV *v);
    void (APIENTRY *glVertexAttribs1hv)(GLuint index, GLsizei n,
                                        const GLhalfNV *v);
    void (APIENTRY *glVertexAttribs2hv)(GLuint index, GLsizei n,
                                        const GLhalfNV *v);
    void (APIENTRY *glVertexAttribs3hv)(GLuint index, GLsizei n,
                                        const GLhalfNV *v);
    void (APIENTRY *glVertexAttribs4hv)(GLuint index, GLsizei n,
                                        const GLhalfNV *v);
    void (APIENTRY *glVertexWeighth)(GLhalfNV weight);
    void (APIENTRY *glVertexWeighthv)(const GLhalfNV *weight);

    // Construction
    NVHalfFloat();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVHalfFloat

// GL_NV_internalformat_sample_query extension API specification.
struct NVInternalformatSampleQuery {
    // Public Members
    void (APIENTRY *glGetInternalformatSampleiv)(GLenum target,
                                                 GLenum internalformat,
                                                 GLsizei samples, GLenum pname,
                                                 GLsizei count, GLint *params);

    // Construction
    NVInternalformatSampleQuery();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVInternalformatSampleQuery

// GL_NV_memory_attachment extension API specification.
struct NVMemoryAttachment {
    // Public Members
    void (APIENTRY *glBufferAttachMemory)(GLenum target, GLuint memory,
                                          GLuint64 offset);
    void (APIENTRY *glGetMemoryObjectDetachedResourcesuiv)(GLuint memory,
                                                           GLenum pname,
                                                           GLint first,
                                                           GLsizei count,
                                                           GLuint *params);
    void (APIENTRY *glNamedBufferAttachMemory)(GLuint buffer, GLuint memory,
                                               GLuint64 offset);
    void (APIENTRY *glResetMemoryObjectParameter)(GLuint memory, GLenum pname);
    void (APIENTRY *glTexAttachMemory)(GLenum target, GLuint memory,
                                       GLuint64 offset);
    void (APIENTRY *glTextureAttachMemory)(GLuint texture, GLuint memory,
                                           GLuint64 offset);

    // Construction
    NVMemoryAttachment();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVMemoryAttachment

// GL_NV_memory_object_sparse extension API specification.
struct NVMemoryObjectSparse {
    // Public Members
    void (APIENTRY *glBufferPageCommitmentMem)(GLenum target, GLintptr offset,
                                               GLsizeiptr size, GLuint memory,
                                               GLuint64 memOffset,
                                               GLboolean commit);
    void (APIENTRY *glNamedBufferPageCommitmentMem)(GLuint buffer,
                                                    GLintptr offset,
                                                    GLsizeiptr size,
                                                    GLuint memory,
                                                    GLuint64 memOffset,
                                                    GLboolean commit);
    void (APIENTRY *glTexPageCommitmentMem)(GLenum target, GLint layer,
                                            GLint level, GLint xoffset,
                                            GLint yoffset, GLint zoffset,
                                            GLsizei width, GLsizei height,
                                            GLsizei depth, GLuint memory,
                                            GLuint64 offset, GLboolean commit);
    void (APIENTRY *glTexturePageCommitmentMem)(GLuint texture, GLint layer,
                                                GLint level, GLint xoffset,
                                                GLint yoffset, GLint zoffset,
                                                GLsizei width, GLsizei height,
                                                GLsizei depth, GLuint memory,
                                                GLuint64 offset,
                                                GLboolean commit);

    // Construction
    NVMemoryObjectSparse();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVMemoryObjectSparse

// GL_NV_mesh_shader extension API specification.
struct NVMeshShader {
    // Public Members
    void (APIENTRY *glDrawMeshTasksIndirect)(GLintptr indirect);
    void (APIENTRY *glDrawMeshTasks)(GLuint first, GLuint count);
    void (APIENTRY *glMultiDrawMeshTasksIndirectCount)(GLintptr indirect,
                                                       GLintptr drawcount,
                                                       GLsizei maxdrawcount,
                                                       GLsizei stride);
    void (APIENTRY *glMultiDrawMeshTasksIndirect)(GLintptr indirect,
                                                  GLsizei drawcount,
                                                  GLsizei stride);

    // Construction
    NVMeshShader();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVMeshShader

// GL_NV_occlusion_query extension API specification.
struct NVOcclusionQuery {
    // Public Members
    void (APIENTRY *glBeginOcclusionQuery)(GLuint id);
    void (APIENTRY *glDeleteOcclusionQueries)(GLsizei n, const GLuint *ids);
    void (APIENTRY *glEndOcclusionQuery)();
    void (APIENTRY *glGenOcclusionQueries)(GLsizei n, GLuint *ids);
    void (APIENTRY *glGetOcclusionQueryiv)(GLuint id, GLenum pname,
                                           GLint *params);
    void (APIENTRY *glGetOcclusionQueryuiv)(GLuint id, GLenum pname,
                                            GLuint *params);
    GLboolean(APIENTRY *glIsOcclusionQuery)(GLuint id);

    // Construction
    NVOcclusionQuery();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVOcclusionQuery

// GL_NV_parameter_buffer_object extension API specification.
struct NVParameterBufferObject {
    // Public Members
    void (APIENTRY *glProgramBufferParametersIiv)(GLenum target,
                                                  GLuint bindingIndex,
                                                  GLuint wordIndex,
                                                  GLsizei count,
                                                  const GLint *params);
    void (APIENTRY *glProgramBufferParametersIuiv)(GLenum target,
                                                   GLuint bindingIndex,
                                                   GLuint wordIndex,
                                                   GLsizei count,
                                                   const GLuint *params);
    void (APIENTRY *glProgramBufferParametersfv)(GLenum target,
                                                 GLuint bindingIndex,
                                                 GLuint wordIndex, GLsizei count,
                                                 const GLfloat *params);

    // Construction
    NVParameterBufferObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVParameterBufferObject

// GL_NV_path_rendering extension API specification.
struct NVPathRendering {
    // Public Members
    void (APIENTRY *glCopyPath)(GLuint resultPath, GLuint srcPath);
    void (APIENTRY *glCoverFillPathInstanced)(GLsizei numPaths,
                                              GLenum pathNameType,
                                              const void *paths, GLuint pathBase,
                                              GLenum coverMode,
                                              GLenum transformType,
                                              const GLfloat *transformValues);
    void (APIENTRY *glCoverFillPath)(GLuint path, GLenum coverMode);
    void (APIENTRY *glCoverStrokePathInstanced)(GLsizei numPaths,
                                                GLenum pathNameType,
                                                const void *paths,
                                                GLuint pathBase,
                                                GLenum coverMode,
                                                GLenum transformType,
                                                const GLfloat *transformValues);
    void (APIENTRY *glCoverStrokePath)(GLuint path, GLenum coverMode);
    void (APIENTRY *glDeletePaths)(GLuint path, GLsizei range);
    GLuint(APIENTRY *glGenPaths)(GLsizei range);
    void (APIENTRY *glGetPathCommands)(GLuint path, GLubyte *commands);
    void (APIENTRY *glGetPathCoords)(GLuint path, GLfloat *coords);
    void (APIENTRY *glGetPathDashArray)(GLuint path, GLfloat *dashArray);
    GLfloat(APIENTRY *glGetPathLength)(GLuint path, GLsizei startSegment,
                                       GLsizei numSegments);
    void (APIENTRY *glGetPathMetricRange)(GLbitfield metricQueryMask,
                                          GLuint firstPathName, GLsizei numPaths,
                                          GLsizei stride, GLfloat *metrics);
    void (APIENTRY *glGetPathMetrics)(GLbitfield metricQueryMask,
                                      GLsizei numPaths, GLenum pathNameType,
                                      const void *paths, GLuint pathBase,
                                      GLsizei stride, GLfloat *metrics);
    void (APIENTRY *glGetPathParameterfv)(GLuint path, GLenum pname,
                                          GLfloat *value);
    void (APIENTRY *glGetPathParameteriv)(GLuint path, GLenum pname,
                                          GLint *value);
    void (APIENTRY *glGetPathSpacing)(GLenum pathListMode, GLsizei numPaths,
                                      GLenum pathNameType, const void *paths,
                                      GLuint pathBase, GLfloat advanceScale,
                                      GLfloat kerningScale, GLenum transformType,
                                      GLfloat *returnedSpacing);
    void (APIENTRY *glGetProgramResourcefv)(GLuint program,
                                            GLenum programInterface,
                                            GLuint index, GLsizei propCount,
                                            const GLenum *props, GLsizei count,
                                            GLsizei *length, GLfloat *params);
    void (APIENTRY *glInterpolatePaths)(GLuint resultPath, GLuint pathA,
                                        GLuint pathB, GLfloat weight);
    GLboolean(APIENTRY *glIsPath)(GLuint path);
    GLboolean(APIENTRY *glIsPointInFillPath)(GLuint path, GLuint mask,
                                             GLfloat x, GLfloat y);
    GLboolean(APIENTRY *glIsPointInStrokePath)(GLuint path, GLfloat x,
                                               GLfloat y);
    void (APIENTRY *glMatrixLoad3x2f)(GLenum matrixMode, const GLfloat *m);
    void (APIENTRY *glMatrixLoad3x3f)(GLenum matrixMode, const GLfloat *m);
    void (APIENTRY *glMatrixLoadTranspose3x3f)(GLenum matrixMode,
                                               const GLfloat *m);
    void (APIENTRY *glMatrixMult3x2f)(GLenum matrixMode, const GLfloat *m);
    void (APIENTRY *glMatrixMult3x3f)(GLenum matrixMode, const GLfloat *m);
    void (APIENTRY *glMatrixMultTranspose3x3f)(GLenum matrixMode,
                                               const GLfloat *m);
    void (APIENTRY *glPathCommands)(GLuint path, GLsizei numCommands,
                                    const GLubyte *commands, GLsizei numCoords,
                                    GLenum coordType, const void *coords);
    void (APIENTRY *glPathCoords)(GLuint path, GLsizei numCoords,
                                  GLenum coordType, const void *coords);
    void (APIENTRY *glPathCoverDepthFunc)(GLenum func);
    void (APIENTRY *glPathDashArray)(GLuint path, GLsizei dashCount,
                                     const GLfloat *dashArray);
    GLenum(APIENTRY *glPathGlyphIndexArray)(GLuint firstPathName,
                                            GLenum fontTarget,
                                            const void *fontName,
                                            GLbitfield fontStyle,
                                            GLuint firstGlyphIndex,
                                            GLsizei numGlyphs,
                                            GLuint pathParameterTemplate,
                                            GLfloat emScale);
    GLenum(APIENTRY *glPathGlyphIndexRange)(GLenum fontTarget,
                                            const void *fontName,
                                            GLbitfield fontStyle,
                                            GLuint pathParameterTemplate,
                                            GLfloat emScale,
                                            GLuint *baseAndCount);
    void (APIENTRY *glPathGlyphRange)(GLuint firstPathName, GLenum fontTarget,
                                      const void *fontName, GLbitfield fontStyle,
                                      GLuint firstGlyph, GLsizei numGlyphs,
                                      GLenum handleMissingGlyphs,
                                      GLuint pathParameterTemplate,
                                      GLfloat emScale);
    void (APIENTRY *glPathGlyphs)(GLuint firstPathName, GLenum fontTarget,
                                  const void *fontName, GLbitfield fontStyle,
                                  GLsizei numGlyphs, GLenum type,
                                  const void *charcodes,
                                  GLenum handleMissingGlyphs,
                                  GLuint pathParameterTemplate, GLfloat emScale);
    GLenum(APIENTRY *glPathMemoryGlyphIndexArray)(GLuint firstPathName,
                                                  GLenum fontTarget,
                                                  GLsizeiptr fontSize,
                                                  const void *fontData,
                                                  GLsizei faceIndex,
                                                  GLuint firstGlyphIndex,
                                                  GLsizei numGlyphs,
                                                  GLuint pathParameterTemplate,
                                                  GLfloat emScale);
    void (APIENTRY *glPathParameterf)(GLuint path, GLenum pname, GLfloat value);
    void (APIENTRY *glPathParameterfv)(GLuint path, GLenum pname,
                                       const GLfloat *value);
    void (APIENTRY *glPathParameteri)(GLuint path, GLenum pname, GLint value);
    void (APIENTRY *glPathParameteriv)(GLuint path, GLenum pname,
                                       const GLint *value);
    void (APIENTRY *glPathStencilDepthOffset)(GLfloat factor, GLfloat units);
    void (APIENTRY *glPathStencilFunc)(GLenum func, GLint ref, GLuint mask);
    void (APIENTRY *glPathString)(GLuint path, GLenum format, GLsizei length,
                                  const void *pathString);
    void (APIENTRY *glPathSubCommands)(GLuint path, GLsizei commandStart,
                                       GLsizei commandsToDelete,
                                       GLsizei numCommands,
                                       const GLubyte *commands,
                                       GLsizei numCoords, GLenum coordType,
                                       const void *coords);
    void (APIENTRY *glPathSubCoords)(GLuint path, GLsizei coordStart,
                                     GLsizei numCoords, GLenum coordType,
                                     const void *coords);
    GLboolean(APIENTRY *glPointAlongPath)(GLuint path, GLsizei startSegment,
                                          GLsizei numSegments, GLfloat distance,
                                          GLfloat *x, GLfloat *y,
                                          GLfloat *tangentX, GLfloat *tangentY);
    void (APIENTRY *glProgramPathFragmentInputGen)(GLuint program,
                                                   GLint location,
                                                   GLenum genMode,
                                                   GLint components,
                                                   const GLfloat *coeffs);
    void (APIENTRY *glStencilFillPathInstanced)(GLsizei numPaths,
                                                GLenum pathNameType,
                                                const void *paths,
                                                GLuint pathBase, GLenum fillMode,
                                                GLuint mask,
                                                GLenum transformType,
                                                const GLfloat *transformValues);
    void (APIENTRY *glStencilFillPath)(GLuint path, GLenum fillMode, GLuint mask);
    void (APIENTRY *glStencilStrokePathInstanced)(GLsizei numPaths,
                                                  GLenum pathNameType,
                                                  const void *paths,
                                                  GLuint pathBase,
                                                  GLint reference, GLuint mask,
                                                  GLenum transformType,
                                                  const GLfloat *transformValues);
    void (APIENTRY *glStencilStrokePath)(GLuint path, GLint reference,
                                         GLuint mask);
    void (APIENTRY *glStencilThenCoverFillPathInstanced)(GLsizei numPaths,
                                                         GLenum pathNameType,
                                                         const void *paths,
                                                         GLuint pathBase,
                                                         GLenum fillMode,
                                                         GLuint mask,
                                                         GLenum coverMode,
                                                         GLenum transformType,
                                                         const GLfloat *transformValues);
    void (APIENTRY *glStencilThenCoverFillPath)(GLuint path, GLenum fillMode,
                                                GLuint mask, GLenum coverMode);
    void (APIENTRY *glStencilThenCoverStrokePathInstanced)(GLsizei numPaths,
                                                           GLenum pathNameType,
                                                           const void *paths,
                                                           GLuint pathBase,
                                                           GLint reference,
                                                           GLuint mask,
                                                           GLenum coverMode,
                                                           GLenum transformType,
                                                           const GLfloat *transformValues);
    void (APIENTRY *glStencilThenCoverStrokePath)(GLuint path, GLint reference,
                                                  GLuint mask, GLenum coverMode);
    void (APIENTRY *glTransformPath)(GLuint resultPath, GLuint srcPath,
                                     GLenum transformType,
                                     const GLfloat *transformValues);
    void (APIENTRY *glWeightPaths)(GLuint resultPath, GLsizei numPaths,
                                   const GLuint *paths, const GLfloat *weights);

    // Construction
    NVPathRendering();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPathRendering

// GL_NV_pixel_data_range extension API specification.
struct NVPixelDataRange {
    // Public Members
    void (APIENTRY *glFlushPixelDataRange)(GLenum target);
    void (APIENTRY *glPixelDataRange)(GLenum target, GLsizei length,
                                      const void *pointer);

    // Construction
    NVPixelDataRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPixelDataRange

// GL_NV_point_sprite extension API specification.
struct NVPointSprite {
    // Public Members
    void (APIENTRY *glPointParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glPointParameteriv)(GLenum pname, const GLint *params);

    // Construction
    NVPointSprite();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPointSprite

// GL_NV_present_video extension API specification.
struct NVPresentVideo {
    // Public Members
    void (APIENTRY *glGetVideoi64v)(GLuint video_slot, GLenum pname,
                                    GLint64EXT *params);
    void (APIENTRY *glGetVideoiv)(GLuint video_slot, GLenum pname, GLint *params);
    void (APIENTRY *glGetVideoui64v)(GLuint video_slot, GLenum pname,
                                     GLuint64EXT *params);
    void (APIENTRY *glGetVideouiv)(GLuint video_slot, GLenum pname,
                                   GLuint *params);
    void (APIENTRY *glPresentFrameDualFill)(GLuint video_slot,
                                            GLuint64EXT minPresentTime,
                                            GLuint beginPresentTimeId,
                                            GLuint presentDurationId,
                                            GLenum type, GLenum target0,
                                            GLuint fill0, GLenum target1,
                                            GLuint fill1, GLenum target2,
                                            GLuint fill2, GLenum target3,
                                            GLuint fill3);
    void (APIENTRY *glPresentFrameKeyed)(GLuint video_slot,
                                         GLuint64EXT minPresentTime,
                                         GLuint beginPresentTimeId,
                                         GLuint presentDurationId, GLenum type,
                                         GLenum target0, GLuint fill0,
                                         GLuint key0, GLenum target1,
                                         GLuint fill1, GLuint key1);

    // Construction
    NVPresentVideo();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPresentVideo

// GL_NV_primitive_restart extension API specification.
struct NVPrimitiveRestart {
    // Public Members
    void (APIENTRY *glPrimitiveRestartIndex)(GLuint index);
    void (APIENTRY *glPrimitiveRestart)();

    // Construction
    NVPrimitiveRestart();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPrimitiveRestart

// GL_NV_query_resource extension API specification.
struct NVQueryResource {
    // Public Members
    GLint(APIENTRY *glQueryResource)(GLenum queryType, GLint tagId,
                                     GLuint count, GLint *buffer);

   // Construction
    NVQueryResource();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVQueryResource

// GL_NV_query_resource_tag extension API specification.
struct NVQueryResourceTag {
    // Public Members
    void (APIENTRY *glDeleteQueryResourceTag)(GLsizei n, const GLint *tagIds);
    void (APIENTRY *glGenQueryResourceTag)(GLsizei n, GLint *tagIds);
    void (APIENTRY *glQueryResourceTag)(GLint tagId, const GLchar *tagString);

    // Construction
    NVQueryResourceTag();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVQueryResourceTag

// GL_NV_register_combiners extension API specification.
struct NVRegisterCombiners {
    // Public Members
    void (APIENTRY *glCombinerInput)(GLenum stage, GLenum portion,
                                     GLenum variable, GLenum input,
                                     GLenum mapping, GLenum componentUsage);
    void (APIENTRY *glCombinerOutput)(GLenum stage, GLenum portion,
                                      GLenum abOutput, GLenum cdOutput,
                                      GLenum sumOutput, GLenum scale,
                                      GLenum bias, GLboolean abDotProduct,
                                      GLboolean cdDotProduct, GLboolean muxSum);
    void (APIENTRY *glCombinerParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glCombinerParameterfv)(GLenum pname, const GLfloat *params);
    void (APIENTRY *glCombinerParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glCombinerParameteriv)(GLenum pname, const GLint *params);
    void (APIENTRY *glFinalCombinerInput)(GLenum variable, GLenum input,
                                          GLenum mapping, GLenum componentUsage);
    void (APIENTRY *glGetCombinerInputParameterfv)(GLenum stage, GLenum portion,
                                                   GLenum variable, GLenum pname,
                                                   GLfloat *params);
    void (APIENTRY *glGetCombinerInputParameteriv)(GLenum stage, GLenum portion,
                                                   GLenum variable, GLenum pname,
                                                   GLint *params);
    void (APIENTRY *glGetCombinerOutputParameterfv)(GLenum stage, GLenum portion,
                                                    GLenum pname,
                                                    GLfloat *params);
    void (APIENTRY *glGetCombinerOutputParameteriv)(GLenum stage, GLenum portion,
                                                    GLenum pname, GLint *params);
    void (APIENTRY *glGetFinalCombinerInputParameterfv)(GLenum variable,
                                                        GLenum pname,
                                                        GLfloat *params);
    void (APIENTRY *glGetFinalCombinerInputParameteriv)(GLenum variable,
                                                        GLenum pname,
                                                        GLint *params);

    // Construction
    NVRegisterCombiners();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVRegisterCombiners

// GL_NV_register_combiners2 extension API specification.
struct NVRegisterCOMBINERS2 {
    // Public Members
    void (APIENTRY *glCombinerStageParameterfv)(GLenum stage, GLenum pname,
                                                const GLfloat *params);
    void (APIENTRY *glGetCombinerStageParameterfv)(GLenum stage, GLenum pname,
                                                   GLfloat *params);

    // Construction
    NVRegisterCOMBINERS2();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVRegisterCOMBINERS2

// GL_NV_sample_locations extension API specification.
struct NVSampleLocations {
    // Public Members
    void (APIENTRY *glFramebufferSampleLocationsfv)(GLenum target, GLuint start,
                                                    GLsizei count,
                                                    const GLfloat *v);
    void (APIENTRY *glNamedFramebufferSampleLocationsfv)(GLuint framebuffer,
                                                         GLuint start,
                                                         GLsizei count,
                                                         const GLfloat *v);
    void (APIENTRY *glResolveDepthValues)();

    // Construction
    NVSampleLocations();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVSampleLocations

// GL_NV_scissor_exclusive extension API specification.
struct NVScissorExclusive {
    // Public Members
    void (APIENTRY *glScissorExclusiveArrayv)(GLuint first, GLsizei count,
                                              const GLint *v);
    void (APIENTRY *glScissorExclusive)(GLint x, GLint y, GLsizei width,
                                        GLsizei height);

    // Construction
    NVScissorExclusive();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVScissorExclusive

// GL_NV_shader_buffer_load extension API specification.
struct NVShaderBufferLoad {
    // Public Members
    void (APIENTRY *glGetBufferParameterui64v)(GLenum target, GLenum pname,
                                               GLuint64EXT *params);
    void (APIENTRY *glGetIntegerui64v)(GLenum value, GLuint64EXT *result);
    void (APIENTRY *glGetNamedBufferParameterui64v)(GLuint buffer, GLenum pname,
                                                    GLuint64EXT *params);
    GLboolean(APIENTRY *glIsBufferResident)(GLenum target);
    GLboolean(APIENTRY *glIsNamedBufferResident)(GLuint buffer);
    void (APIENTRY *glMakeBufferNonResident)(GLenum target);
    void (APIENTRY *glMakeBufferResident)(GLenum target, GLenum access);
    void (APIENTRY *glMakeNamedBufferNonResident)(GLuint buffer);
    void (APIENTRY *glMakeNamedBufferResident)(GLuint buffer, GLenum access);
    void (APIENTRY *glProgramUniformui64)(GLuint program, GLint location,
                                          GLuint64EXT value);
    void (APIENTRY *glProgramUniformui64v)(GLuint program, GLint location,
                                           GLsizei count,
                                           const GLuint64EXT *value);
    void (APIENTRY *glUniformui64)(GLint location, GLuint64EXT value);
    void (APIENTRY *glUniformui64v)(GLint location, GLsizei count,
                                    const GLuint64EXT *value);

    // Construction
    NVShaderBufferLoad();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVShaderBufferLoad

// GL_NV_shading_rate_image extension API specification.
struct NVShadingRateImage {
    // Public Members
    void (APIENTRY *glBindShadingRateImage)(GLuint texture);
    void (APIENTRY *glGetShadingRateImagePalette)(GLuint viewport, GLuint entry,
                                                  GLenum *rate);
    void (APIENTRY *glGetShadingRateSampleLocationiv)(GLenum rate,
                                                      GLuint samples,
                                                      GLuint index,
                                                      GLint *location);
    void (APIENTRY *glShadingRateImageBarrier)(GLboolean synchronize);
    void (APIENTRY *glShadingRateImagePalette)(GLuint viewport, GLuint first,
                                               GLsizei count,
                                               const GLenum *rates);
    void (APIENTRY *glShadingRateSampleOrderCustom)(GLenum rate, GLuint samples,
                                                    const GLint *locations);
    void (APIENTRY *glShadingRateSampleOrder)(GLenum order);

    // Construction
    NVShadingRateImage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVShadingRateImage

// GL_NV_texture_barrier extension API specification.
struct NVTextureBarrier {
    // Public Members
    void (APIENTRY *glTextureBarrier)();

    // Construction
    NVTextureBarrier();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVTextureBarrier

// GL_NV_texture_multisample extension API specification.
struct NVTextureMultisample {
    // Public Members
    void (APIENTRY *glTexImage2DMultisampleCoverage)(GLenum target,
                                                     GLsizei coverageSamples,
                                                     GLsizei colorSamples,
                                                     GLint internalFormat,
                                                     GLsizei width,
                                                     GLsizei height,
                                                     GLboolean fixedSampleLocations);
    void (APIENTRY *glTexImage3DMultisampleCoverage)(GLenum target,
                                                     GLsizei coverageSamples,
                                                     GLsizei colorSamples,
                                                     GLint internalFormat,
                                                     GLsizei width,
                                                     GLsizei height,
                                                     GLsizei depth,
                                                     GLboolean fixedSampleLocations);
    void (APIENTRY *glTextureImage2DMultisampleCoverage)(GLuint texture,
                                                         GLenum target,
                                                         GLsizei coverageSamples,
                                                         GLsizei colorSamples,
                                                         GLint internalFormat,
                                                         GLsizei width,
                                                         GLsizei height,
                                                         GLboolean fixedSampleLocations);
    void (APIENTRY *glTextureImage2DMultisample)(GLuint texture, GLenum target,
                                                 GLsizei samples,
                                                 GLint internalFormat,
                                                 GLsizei width, GLsizei height,
                                                 GLboolean fixedSampleLocations);
    void (APIENTRY *glTextureImage3DMultisampleCoverage)(GLuint texture,
                                                         GLenum target,
                                                         GLsizei coverageSamples,
                                                         GLsizei colorSamples,
                                                         GLint internalFormat,
                                                         GLsizei width,
                                                         GLsizei height,
                                                         GLsizei depth,
                                                         GLboolean fixedSampleLocations);
    void (APIENTRY *glTextureImage3DMultisample)(GLuint texture, GLenum target,
                                                 GLsizei samples,
                                                 GLint internalFormat,
                                                 GLsizei width, GLsizei height,
                                                 GLsizei depth,
                                                 GLboolean fixedSampleLocations);

    // Construction
    NVTextureMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVTextureMultisample

// GL_NV_timeline_semaphore extension API specification.
struct NVTimelineSemaphore {
    // Public Members
    void (APIENTRY *glCreateSemaphores)(GLsizei n, GLuint *semaphores);
    void (APIENTRY *glGetSemaphoreParameteriv)(GLuint semaphore, GLenum pname,
                                               GLint *params);
    void (APIENTRY *glSemaphoreParameteriv)(GLuint semaphore, GLenum pname,
                                            const GLint *params);

    // Construction
    NVTimelineSemaphore();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVTimelineSemaphore

// GL_NV_transform_feedback extension API specification.
struct NVTransformFeedback {
    // Public Members
    void (APIENTRY *glActiveVarying)(GLuint program, const GLchar *name);
    void (APIENTRY *glBeginTransformFeedback)(GLenum primitiveMode);
    void (APIENTRY *glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
    void (APIENTRY *glBindBufferOffset)(GLenum target, GLuint index,
                                        GLuint buffer, GLintptr offset);
    void (APIENTRY *glBindBufferRange)(GLenum target, GLuint index,
                                       GLuint buffer, GLintptr offset,
                                       GLsizeiptr size);
    void (APIENTRY *glEndTransformFeedback)();
    void (APIENTRY *glGetActiveVarying)(GLuint program, GLuint index,
                                        GLsizei bufSize, GLsizei *length,
                                        GLsizei *size, GLenum *type,
                                        GLchar *name);
    void (APIENTRY *glGetTransformFeedbackVarying)(GLuint program, GLuint index,
                                                   GLint *location);
    GLint(APIENTRY *glGetVaryingLocation)(GLuint program, const GLchar *name);
    void (APIENTRY *glTransformFeedbackAttribs)(GLsizei count,
                                                const GLint *attribs,
                                                GLenum bufferMode);
    void (APIENTRY *glTransformFeedbackStreamAttribs)(GLsizei count,
                                                      const GLint *attribs,
                                                      GLsizei nbuffers,
                                                      const GLint *bufstreams,
                                                      GLenum bufferMode);
    void (APIENTRY *glTransformFeedbackVaryings)(GLuint program, GLsizei count,
                                                 const GLint *locations,
                                                 GLenum bufferMode);

    // Construction
    NVTransformFeedback();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVTransformFeedback

// GL_NV_transform_feedback2 extension API specification.
struct NVTransformFeedback2 {
    // Public Members
    void (APIENTRY *glBindTransformFeedback)(GLenum target, GLuint id);
    void (APIENTRY *glDeleteTransformFeedbacks)(GLsizei n, const GLuint *ids);
    void (APIENTRY *glDrawTransformFeedback)(GLenum mode, GLuint id);
    void (APIENTRY *glGenTransformFeedbacks)(GLsizei n, GLuint *ids);
    GLboolean(APIENTRY *glIsTransformFeedback)(GLuint id);
    void (APIENTRY *glPauseTransformFeedback)();
    void (APIENTRY *glResumeTransformFeedback)();

    // Construction
    NVTransformFeedback2();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVTransformFeedback2

// GL_NV_vdpau_interop extension API specification.
struct NVVdpauInterop {
    // Public Members
    void (APIENTRY *glVDPAUFini)();
    void (APIENTRY *glVDPAUGetSurfaceiv)(GLvdpauSurfaceNV surface, GLenum pname,
                                         GLsizei count, GLsizei *length,
                                         GLint *values);
    void (APIENTRY *glVDPAUInit)(const void *vdpDevice,
                                 const void *getProcAddress);
    GLboolean(APIENTRY *glVDPAUIsSurface)(GLvdpauSurfaceNV surface);
    void (APIENTRY *glVDPAUMapSurfaces)(GLsizei numSurfaces,
                                        const GLvdpauSurfaceNV *surfaces);
    GLvdpauSurfaceNV(APIENTRY *glVDPAURegisterOutputSurface)(const void *vdpSurface,
                                                             GLenum target,
                                                             GLsizei numTextureNames,
                                                             const GLuint *textureNames);
    GLvdpauSurfaceNV(APIENTRY *glVDPAURegisterVideoSurface)(const void *vdpSurface,
                                                            GLenum target,
                                                            GLsizei numTextureNames,
                                                            const GLuint *textureNames);
    void (APIENTRY *glVDPAUSurfaceAccess)(GLvdpauSurfaceNV surface,
                                          GLenum access);
    void (APIENTRY *glVDPAUUnmapSurfaces)(GLsizei numSurface,
                                          const GLvdpauSurfaceNV *surfaces);
    void (APIENTRY *glVDPAUUnregisterSurface)(GLvdpauSurfaceNV surface);

    // Construction
    NVVdpauInterop();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVdpauInterop

// GL_NV_vdpau_interop2 extension API specification.
struct NVVdpauINTEROP2 {
    // Public Members
    GLvdpauSurfaceNV(APIENTRY *glVDPAURegisterVideoSurfaceWithPictureStructure)(const void *vdpSurface,
                                                                                GLenum target,
                                                                                GLsizei numTextureNames,
                                                                                const GLuint *textureNames,
                                                                                GLboolean isFrameStructure);

   // Construction
    NVVdpauINTEROP2();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVdpauINTEROP2

// GL_NV_vertex_array_range extension API specification.
struct NVVertexArrayRange {
    // Public Members
    void (APIENTRY *glFlushVertexArrayRange)();
    void (APIENTRY *glVertexArrayRange)(GLsizei length, const void *pointer);

    // Construction
    NVVertexArrayRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVertexArrayRange

// GL_NV_vertex_attrib_integer_64bit extension API specification.
struct NVVertexAttribInteger64BIT {
    // Public Members
    void (APIENTRY *glGetVertexAttribLi64v)(GLuint index, GLenum pname,
                                            GLint64EXT *params);
    void (APIENTRY *glGetVertexAttribLui64v)(GLuint index, GLenum pname,
                                             GLuint64EXT *params);
    void (APIENTRY *glVertexAttribL1i64)(GLuint index, GLint64EXT x);
    void (APIENTRY *glVertexAttribL1i64v)(GLuint index, const GLint64EXT *v);
    void (APIENTRY *glVertexAttribL1ui64)(GLuint index, GLuint64EXT x);
    void (APIENTRY *glVertexAttribL1ui64v)(GLuint index, const GLuint64EXT *v);
    void (APIENTRY *glVertexAttribL2i64)(GLuint index, GLint64EXT x,
                                         GLint64EXT y);
    void (APIENTRY *glVertexAttribL2i64v)(GLuint index, const GLint64EXT *v);
    void (APIENTRY *glVertexAttribL2ui64)(GLuint index, GLuint64EXT x,
                                          GLuint64EXT y);
    void (APIENTRY *glVertexAttribL2ui64v)(GLuint index, const GLuint64EXT *v);
    void (APIENTRY *glVertexAttribL3i64)(GLuint index, GLint64EXT x,
                                         GLint64EXT y, GLint64EXT z);
    void (APIENTRY *glVertexAttribL3i64v)(GLuint index, const GLint64EXT *v);
    void (APIENTRY *glVertexAttribL3ui64)(GLuint index, GLuint64EXT x,
                                          GLuint64EXT y, GLuint64EXT z);
    void (APIENTRY *glVertexAttribL3ui64v)(GLuint index, const GLuint64EXT *v);
    void (APIENTRY *glVertexAttribL4i64)(GLuint index, GLint64EXT x,
                                         GLint64EXT y, GLint64EXT z,
                                         GLint64EXT w);
    void (APIENTRY *glVertexAttribL4i64v)(GLuint index, const GLint64EXT *v);
    void (APIENTRY *glVertexAttribL4ui64)(GLuint index, GLuint64EXT x,
                                          GLuint64EXT y, GLuint64EXT z,
                                          GLuint64EXT w);
    void (APIENTRY *glVertexAttribL4ui64v)(GLuint index, const GLuint64EXT *v);
    void (APIENTRY *glVertexAttribLFormat)(GLuint index, GLint size, GLenum type,
                                           GLsizei stride);

    // Construction
    NVVertexAttribInteger64BIT();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVertexAttribInteger64BIT

// GL_NV_vertex_buffer_unified_memory extension API specification.
struct NVVertexBufferUnifiedMemory {
    // Public Members
    void (APIENTRY *glBufferAddressRange)(GLenum pname, GLuint index,
                                          GLuint64EXT address, GLsizeiptr length);
    void (APIENTRY *glColorFormat)(GLint size, GLenum type, GLsizei stride);
    void (APIENTRY *glEdgeFlagFormat)(GLsizei stride);
    void (APIENTRY *glFogCoordFormat)(GLenum type, GLsizei stride);
    void (APIENTRY *glGetIntegerui64i_v)(GLenum value, GLuint index,
                                         GLuint64EXT *result);
    void (APIENTRY *glIndexFormat)(GLenum type, GLsizei stride);
    void (APIENTRY *glNormalFormat)(GLenum type, GLsizei stride);
    void (APIENTRY *glSecondaryColorFormat)(GLint size, GLenum type,
                                            GLsizei stride);
    void (APIENTRY *glTexCoordFormat)(GLint size, GLenum type, GLsizei stride);
    void (APIENTRY *glVertexAttribFormat)(GLuint index, GLint size, GLenum type,
                                          GLboolean normalized, GLsizei stride);
    void (APIENTRY *glVertexAttribIFormat)(GLuint index, GLint size, GLenum type,
                                           GLsizei stride);
    void (APIENTRY *glVertexFormat)(GLint size, GLenum type, GLsizei stride);

    // Construction
    NVVertexBufferUnifiedMemory();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVertexBufferUnifiedMemory

// GL_NV_vertex_program extension API specification.
struct NVVertexProgram {
    // Public Members
    GLboolean(APIENTRY *glAreProgramsResident)(GLsizei n,
                                               const GLuint *programs,
                                               GLboolean *residences);
    void (APIENTRY *glBindProgram)(GLenum target, GLuint id);
    void (APIENTRY *glDeletePrograms)(GLsizei n, const GLuint *programs);
    void (APIENTRY *glExecuteProgram)(GLenum target, GLuint id,
                                      const GLfloat *params);
    void (APIENTRY *glGenPrograms)(GLsizei n, GLuint *programs);
    void (APIENTRY *glGetProgramParameterdv)(GLenum target, GLuint index,
                                             GLenum pname, GLdouble *params);
    void (APIENTRY *glGetProgramParameterfv)(GLenum target, GLuint index,
                                             GLenum pname, GLfloat *params);
    void (APIENTRY *glGetProgramString)(GLuint id, GLenum pname,
                                        GLubyte *program);
    void (APIENTRY *glGetProgramiv)(GLuint id, GLenum pname, GLint *params);
    void (APIENTRY *glGetTrackMatrixiv)(GLenum target, GLuint address,
                                        GLenum pname, GLint *params);
    void (APIENTRY *glGetVertexAttribPointerv)(GLuint index, GLenum pname,
                                               void **pointer);
    void (APIENTRY *glGetVertexAttribdv)(GLuint index, GLenum pname,
                                         GLdouble *params);
    void (APIENTRY *glGetVertexAttribfv)(GLuint index, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetVertexAttribiv)(GLuint index, GLenum pname,
                                         GLint *params);
    GLboolean(APIENTRY *glIsProgram)(GLuint id);
    void (APIENTRY *glLoadProgram)(GLenum target, GLuint id, GLsizei len,
                                   const GLubyte *program);
    void (APIENTRY *glProgramParameter4d)(GLenum target, GLuint index,
                                          GLdouble x, GLdouble y, GLdouble z,
                                          GLdouble w);
    void (APIENTRY *glProgramParameter4dv)(GLenum target, GLuint index,
                                           const GLdouble *v);
    void (APIENTRY *glProgramParameter4f)(GLenum target, GLuint index, GLfloat x,
                                          GLfloat y, GLfloat z, GLfloat w);
    void (APIENTRY *glProgramParameter4fv)(GLenum target, GLuint index,
                                           const GLfloat *v);
    void (APIENTRY *glProgramParameters4dv)(GLenum target, GLuint index,
                                            GLsizei count, const GLdouble *v);
    void (APIENTRY *glProgramParameters4fv)(GLenum target, GLuint index,
                                            GLsizei count, const GLfloat *v);
    void (APIENTRY *glRequestResidentPrograms)(GLsizei n, const GLuint *programs);
    void (APIENTRY *glTrackMatrix)(GLenum target, GLuint address, GLenum matrix,
                                   GLenum transform);
    void (APIENTRY *glVertexAttrib1d)(GLuint index, GLdouble x);
    void (APIENTRY *glVertexAttrib1dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib1f)(GLuint index, GLfloat x);
    void (APIENTRY *glVertexAttrib1fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib1s)(GLuint index, GLshort x);
    void (APIENTRY *glVertexAttrib1sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
    void (APIENTRY *glVertexAttrib2dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
    void (APIENTRY *glVertexAttrib2fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib2s)(GLuint index, GLshort x, GLshort y);
    void (APIENTRY *glVertexAttrib2sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z);
    void (APIENTRY *glVertexAttrib3dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z);
    void (APIENTRY *glVertexAttrib3fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib3s)(GLuint index, GLshort x, GLshort y,
                                      GLshort z);
    void (APIENTRY *glVertexAttrib3sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z, GLdouble w);
    void (APIENTRY *glVertexAttrib4dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z, GLfloat w);
    void (APIENTRY *glVertexAttrib4fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib4s)(GLuint index, GLshort x, GLshort y,
                                      GLshort z, GLshort w);
    void (APIENTRY *glVertexAttrib4sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4ub)(GLuint index, GLubyte x, GLubyte y,
                                       GLubyte z, GLubyte w);
    void (APIENTRY *glVertexAttrib4ubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttribPointer)(GLuint index, GLint fsize,
                                           GLenum type, GLsizei stride,
                                           const void *pointer);
    void (APIENTRY *glVertexAttribs1dv)(GLuint index, GLsizei count,
                                        const GLdouble *v);
    void (APIENTRY *glVertexAttribs1fv)(GLuint index, GLsizei count,
                                        const GLfloat *v);
    void (APIENTRY *glVertexAttribs1sv)(GLuint index, GLsizei count,
                                        const GLshort *v);
    void (APIENTRY *glVertexAttribs2dv)(GLuint index, GLsizei count,
                                        const GLdouble *v);
    void (APIENTRY *glVertexAttribs2fv)(GLuint index, GLsizei count,
                                        const GLfloat *v);
    void (APIENTRY *glVertexAttribs2sv)(GLuint index, GLsizei count,
                                        const GLshort *v);
    void (APIENTRY *glVertexAttribs3dv)(GLuint index, GLsizei count,
                                        const GLdouble *v);
    void (APIENTRY *glVertexAttribs3fv)(GLuint index, GLsizei count,
                                        const GLfloat *v);
    void (APIENTRY *glVertexAttribs3sv)(GLuint index, GLsizei count,
                                        const GLshort *v);
    void (APIENTRY *glVertexAttribs4dv)(GLuint index, GLsizei count,
                                        const GLdouble *v);
    void (APIENTRY *glVertexAttribs4fv)(GLuint index, GLsizei count,
                                        const GLfloat *v);
    void (APIENTRY *glVertexAttribs4sv)(GLuint index, GLsizei count,
                                        const GLshort *v);
    void (APIENTRY *glVertexAttribs4ubv)(GLuint index, GLsizei count,
                                         const GLubyte *v);

    // Construction
    NVVertexProgram();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVertexProgram

// GL_NV_video_capture extension API specification.
struct NVVideoCapture {
    // Public Members
    void (APIENTRY *glBeginVideoCapture)(GLuint video_capture_slot);
    void (APIENTRY *glBindVideoCaptureStreamBuffer)(GLuint video_capture_slot,
                                                    GLuint stream,
                                                    GLenum frame_region,
                                                    GLintptrARB offset);
    void (APIENTRY *glBindVideoCaptureStreamTexture)(GLuint video_capture_slot,
                                                     GLuint stream,
                                                     GLenum frame_region,
                                                     GLenum target,
                                                     GLuint texture);
    void (APIENTRY *glEndVideoCapture)(GLuint video_capture_slot);
    void (APIENTRY *glGetVideoCaptureStreamdv)(GLuint video_capture_slot,
                                               GLuint stream, GLenum pname,
                                               GLdouble *params);
    void (APIENTRY *glGetVideoCaptureStreamfv)(GLuint video_capture_slot,
                                               GLuint stream, GLenum pname,
                                               GLfloat *params);
    void (APIENTRY *glGetVideoCaptureStreamiv)(GLuint video_capture_slot,
                                               GLuint stream, GLenum pname,
                                               GLint *params);
    void (APIENTRY *glGetVideoCaptureiv)(GLuint video_capture_slot, GLenum pname,
                                         GLint *params);
    GLenum(APIENTRY *glVideoCapture)(GLuint video_capture_slot,
                                     GLuint *sequence_num,
                                     GLuint64EXT *capture_time);
    void (APIENTRY *glVideoCaptureStreamParameterdv)(GLuint video_capture_slot,
                                                     GLuint stream, GLenum pname,
                                                     const GLdouble *params);
    void (APIENTRY *glVideoCaptureStreamParameterfv)(GLuint video_capture_slot,
                                                     GLuint stream, GLenum pname,
                                                     const GLfloat *params);
    void (APIENTRY *glVideoCaptureStreamParameteriv)(GLuint video_capture_slot,
                                                     GLuint stream, GLenum pname,
                                                     const GLint *params);

    // Construction
    NVVideoCapture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVideoCapture

// GL_NV_viewport_swizzle extension API specification.
struct NVViewportSwizzle {
    // Public Members
    void (APIENTRY *glViewportSwizzle)(GLuint index, GLenum swizzlex,
                                       GLenum swizzley, GLenum swizzlez,
                                       GLenum swizzlew);

    // Construction
    NVViewportSwizzle();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVViewportSwizzle

} // namespace gl


#ifdef _WIN32
namespace wgl {

// WGL_NV_DX_interop extension API specification.
struct NVDxInterop {
    // Public Members
    BOOL(APIENTRY *wglDXCloseDevice)(HANDLE hDevice);
    BOOL(APIENTRY *wglDXLockObjects)(HANDLE hDevice, GLint count,
                                     HANDLE *hObjects);
    BOOL(APIENTRY *wglDXObjectAccess)(HANDLE hObject, GLenum access);
    HANDLE(APIENTRY *wglDXOpenDevice)(void *dxDevice);
    HANDLE(APIENTRY *wglDXRegisterObject)(HANDLE hDevice, void *dxObject,
                                          GLuint name, GLenum type,
                                          GLenum access);
    BOOL(APIENTRY *wglDXSetResourceShareHandle)(void *dxObject,
                                                HANDLE shareHandle);
    BOOL(APIENTRY *wglDXUnlockObjects)(HANDLE hDevice, GLint count,
                                       HANDLE *hObjects);
    BOOL(APIENTRY *wglDXUnregisterObject)(HANDLE hDevice, HANDLE hObject);

    // Construction
    NVDxInterop();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDxInterop

// WGL_NV_copy_image extension API specification.
struct NVCopyImage {
    // Public Members
    BOOL(APIENTRY *wglCopyImageSubData)(HGLRC hSrcRC, GLuint srcName,
                                        GLenum srcTarget, GLint srcLevel,
                                        GLint srcX, GLint srcY, GLint srcZ,
                                        HGLRC hDstRC, GLuint dstName,
                                        GLenum dstTarget, GLint dstLevel,
                                        GLint dstX, GLint dstY, GLint dstZ,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth);

   // Construction
    NVCopyImage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVCopyImage

// WGL_NV_delay_before_swap extension API specification.
struct NVDelayBeforeSwap {
    // Public Members
    BOOL(APIENTRY *wglDelayBeforeSwap)(HDC hDC, GLfloat seconds);

    // Construction
    NVDelayBeforeSwap();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDelayBeforeSwap

// WGL_NV_gpu_affinity extension API specification.
struct NVGPUAffinity {
    // Public Members
    HDC(APIENTRY *wglCreateAffinityDC)(const HGPUNV *phGpuList);
    BOOL(APIENTRY *wglDeleteDC)(HDC hdc);
    BOOL(APIENTRY *wglEnumGpuDevices)(HGPUNV hGpu, UINT iDeviceIndex,
                                      PGPU_DEVICE lpGpuDevice);
    BOOL(APIENTRY *wglEnumGpusFromAffinityDC)(HDC hAffinityDC, UINT iGpuIndex,
                                              HGPUNV *hGpu);
    BOOL(APIENTRY *wglEnumGpus)(UINT iGpuIndex, HGPUNV *phGpu);

    // Construction
    NVGPUAffinity();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVGPUAffinity

// WGL_NV_present_video extension API specification.
struct NVPresentVideo {
    // Public Members
    BOOL(APIENTRY *wglBindVideoDevice)(HDC hDc, unsigned int uVideoSlot,
                                       HVIDEOOUTPUTDEVICENV hVideoDevice,
                                       const int *piAttribList);
    int (APIENTRY *wglEnumerateVideoDevices)(HDC hDc,
                                             HVIDEOOUTPUTDEVICENV *phDeviceList);
    BOOL(APIENTRY *wglQueryCurrentContext)(int iAttribute, int *piValue);

    // Construction
    NVPresentVideo();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPresentVideo

// WGL_NV_swap_group extension API specification.
struct NVSwapGroup {
    // Public Members
    BOOL(APIENTRY *wglBindSwapBarrier)(GLuint group, GLuint barrier);
    BOOL(APIENTRY *wglJoinSwapGroup)(HDC hDC, GLuint group);
    BOOL(APIENTRY *wglQueryFrameCount)(HDC hDC, GLuint *count);
    BOOL(APIENTRY *wglQueryMaxSwapGroups)(HDC hDC, GLuint *maxGroups,
                                          GLuint *maxBarriers);
    BOOL(APIENTRY *wglQuerySwapGroup)(HDC hDC, GLuint *group, GLuint *barrier);
    BOOL(APIENTRY *wglResetFrameCount)(HDC hDC);

    // Construction
    NVSwapGroup();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVSwapGroup

// WGL_NV_vertex_array_range extension API specification.
struct NVVertexArrayRange {
    // Public Members
    void *(APIENTRY *wglAllocateMemory)(GLsizei size, GLfloat readfreq,
                                        GLfloat writefreq, GLfloat priority);
    void (APIENTRY *wglFreeMemory)(void *pointer);

    // Construction
    NVVertexArrayRange();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVertexArrayRange

// WGL_NV_video_capture extension API specification.
struct NVVideoCapture {
    // Public Members
    BOOL(APIENTRY *wglBindVideoCaptureDevice)(UINT uVideoSlot,
                                              HVIDEOINPUTDEVICENV hDevice);
    UINT(APIENTRY *wglEnumerateVideoCaptureDevices)(HDC hDc,
                                                    HVIDEOINPUTDEVICENV *phDeviceList);
    BOOL(APIENTRY *wglLockVideoCaptureDevice)(HDC hDc,
                                              HVIDEOINPUTDEVICENV hDevice);
    BOOL(APIENTRY *wglQueryVideoCaptureDevice)(HDC hDc,
                                               HVIDEOINPUTDEVICENV hDevice,
                                               int iAttribute, int *piValue);
    BOOL(APIENTRY *wglReleaseVideoCaptureDevice)(HDC hDc,
                                                 HVIDEOINPUTDEVICENV hDevice);

   // Construction
    NVVideoCapture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVideoCapture

// WGL_NV_video_output extension API specification.
struct NVVideoOutput {
    // Public Members
    BOOL(APIENTRY *wglBindVideoImage)(HPVIDEODEV hVideoDevice,
                                      HPBUFFERARB hPbuffer, int iVideoBuffer);
    BOOL(APIENTRY *wglGetVideoDevice)(HDC hDC, int numDevices,
                                      HPVIDEODEV *hVideoDevice);
    BOOL(APIENTRY *wglGetVideoInfo)(HPVIDEODEV hpVideoDevice,
                                    unsigned long *pulCounterOutputPbuffer,
                                    unsigned long *pulCounterOutputVideo);
    BOOL(APIENTRY *wglReleaseVideoDevice)(HPVIDEODEV hVideoDevice);
    BOOL(APIENTRY *wglReleaseVideoImage)(HPBUFFERARB hPbuffer, int iVideoBuffer);
    BOOL(APIENTRY *wglSendPbufferToVideo)(HPBUFFERARB hPbuffer, int iBufferType,
                                          unsigned long *pulCounterPbuffer,
                                          BOOL bBlock);

   // Construction
    NVVideoOutput();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVideoOutput

} // namespace wgl
#endif // ifdef _WIN32


#ifdef _USES_GLX
namespace glx {

// GLX_NV_copy_buffer extension API specification.
struct NVCopyBuffer {
    // Public Members
    void (APIENTRY *glXCopyBufferSubData)(Display *dpy, GLXContext readCtx,
                                          GLXContext writeCtx, GLenum readTarget,
                                          GLenum writeTarget,
                                          GLintptr readOffset,
                                          GLintptr writeOffset, GLsizeiptr size);
    void (APIENTRY *glXNamedCopyBufferSubData)(Display *dpy, GLXContext readCtx,
                                               GLXContext writeCtx,
                                               GLuint readBuffer,
                                               GLuint writeBuffer,
                                               GLintptr readOffset,
                                               GLintptr writeOffset,
                                               GLsizeiptr size);

    // Construction
    NVCopyBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVCopyBuffer

// GLX_NV_copy_image extension API specification.
struct NVCopyImage {
    // Public Members
    void (APIENTRY *glXCopyImageSubData)(Display *dpy, GLXContext srcCtx,
                                         GLuint srcName, GLenum srcTarget,
                                         GLint srcLevel, GLint srcX, GLint srcY,
                                         GLint srcZ, GLXContext dstCtx,
                                         GLuint dstName, GLenum dstTarget,
                                         GLint dstLevel, GLint dstX, GLint dstY,
                                         GLint dstZ, GLsizei width,
                                         GLsizei height, GLsizei depth);

    // Construction
    NVCopyImage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVCopyImage

// GLX_NV_delay_before_swap extension API specification.
struct NVDelayBeforeSwap {
    // Public Members
    Bool(APIENTRY *glXDelayBeforeSwap)(Display *dpy, GLXDrawable drawable,
                                       GLfloat seconds);

   // Construction
    NVDelayBeforeSwap();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVDelayBeforeSwap

// GLX_NV_present_video extension API specification.
struct NVPresentVideo {
    // Public Members
    int (APIENTRY *glXBindVideoDevice)(Display *dpy, unsigned int video_slot,
                                       unsigned int video_device,
                                       const int *attrib_list);
    unsigned int *(APIENTRY *glXEnumerateVideoDevices)(Display *dpy, int screen,
                                                       int *nelements);

    // Construction
    NVPresentVideo();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVPresentVideo

// GLX_NV_swap_group extension API specification.
struct NVSwapGroup {
    // Public Members
    Bool(APIENTRY *glXBindSwapBarrier)(Display *dpy, GLuint group,
                                       GLuint barrier);
    Bool(APIENTRY *glXJoinSwapGroup)(Display *dpy, GLXDrawable drawable,
                                     GLuint group);
    Bool(APIENTRY *glXQueryFrameCount)(Display *dpy, int screen, GLuint *count);
    Bool(APIENTRY *glXQueryMaxSwapGroups)(Display *dpy, int screen,
                                          GLuint *maxGroups,
                                          GLuint *maxBarriers);
    Bool(APIENTRY *glXQuerySwapGroup)(Display *dpy, GLXDrawable drawable,
                                      GLuint *group, GLuint *barrier);
    Bool(APIENTRY *glXResetFrameCount)(Display *dpy, int screen);

    // Construction
    NVSwapGroup();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVSwapGroup

// GLX_NV_video_capture extension API specification.
struct NVVideoCapture {
    // Public Members
    int (APIENTRY *glXBindVideoCaptureDevice)(Display *dpy,
                                              unsigned int video_capture_slot,
                                              GLXVideoCaptureDeviceNV device);
    GLXVideoCaptureDeviceNV *(APIENTRY *glXEnumerateVideoCaptureDevices)(Display *dpy,
                                                                         int screen,
                                                                         int *nelements);
    void (APIENTRY *glXLockVideoCaptureDevice)(Display *dpy,
                                               GLXVideoCaptureDeviceNV device);
    int (APIENTRY *glXQueryVideoCaptureDevice)(Display *dpy,
                                               GLXVideoCaptureDeviceNV device,
                                               int attribute, int *value);
    void (APIENTRY *glXReleaseVideoCaptureDevice)(Display *dpy,
                                                  GLXVideoCaptureDeviceNV device);

    // Construction
    NVVideoCapture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVideoCapture

// GLX_NV_video_out extension API specification.
struct NVVideoOut {
    // Public Members
    int (APIENTRY *glXBindVideoImage)(Display *dpy, GLXVideoDeviceNV VideoDevice,
                                      GLXPbuffer pbuf, int iVideoBuffer);
    int (APIENTRY *glXGetVideoDevice)(Display *dpy, int screen,
                                      int numVideoDevices,
                                      GLXVideoDeviceNV *pVideoDevice);
    int (APIENTRY *glXGetVideoInfo)(Display *dpy, int screen,
                                    GLXVideoDeviceNV VideoDevice,
                                    unsigned long *pulCounterOutputPbuffer,
                                    unsigned long *pulCounterOutputVideo);
    int (APIENTRY *glXReleaseVideoDevice)(Display *dpy, int screen,
                                          GLXVideoDeviceNV VideoDevice);
    int (APIENTRY *glXReleaseVideoImage)(Display *dpy, GLXPbuffer pbuf);
    int (APIENTRY *glXSendPbufferToVideo)(Display *dpy, GLXPbuffer pbuf,
                                          int iBufferType,
                                          unsigned long *pulCounterPbuffer,
                                          GLboolean bBlock);

    // Construction
    NVVideoOut();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct NVVideoOut

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
