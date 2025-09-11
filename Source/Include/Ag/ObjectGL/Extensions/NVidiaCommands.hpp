//! @file Ag/ObjectGL/Extensions/NVidiaCommands.hpp
//! @brief The declaration of nVidia-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_NVIDIA_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_NVIDIA_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "NVidia.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_NVX_conditional_render extension API.
class NVXConditionalRenderAPI : public BaseExtension
{
public:
    // Construction
    NVXConditionalRenderAPI();

    // Accessors
    const NVXConditionalRender &getRawAPI() const;

    // Operations
    void beginConditionalRender(GLuint id) const;
    void endConditionalRender() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVXConditionalRender _api;
};

// Manages the entry points for the GL_NVX_gpu_multicast2 extension API.
class NVXGPUMULTICAST2API : public BaseExtension
{
public:
    // Construction
    NVXGPUMULTICAST2API();

    // Accessors
    const NVXGPUMULTICAST2 &getRawAPI() const;

    // Operations
    GLuint asyncCopyBufferSubData(GLsizei waitSemaphoreCount,
                                  const GLuint *waitSemaphoreArray,
                                  const GLuint64 *fenceValueArray,
                                  GLuint readGpu, GLbitfield writeGpuMask,
                                  BufferName readBuffer, BufferName writeBuffer,
                                  GLintptr readOffset, GLintptr writeOffset,
                                  GLsizeiptr size, GLsizei signalSemaphoreCount,
                                  const GLuint *signalSemaphoreArray,
                                  const GLuint64 *signalValueArray) const;
    GLuint asyncCopyImageSubData(GLsizei waitSemaphoreCount,
                                 const GLuint *waitSemaphoreArray,
                                 const GLuint64 *waitValueArray, GLuint srcGpu,
                                 GLbitfield dstGpuMask, GLuint srcName,
                                 GLenum srcTarget, GLint srcLevel, GLint srcX,
                                 GLint srcY, GLint srcZ, GLuint dstName,
                                 GLenum dstTarget, GLint dstLevel, GLint dstX,
                                 GLint dstY, GLint dstZ, GLsizei srcWidth,
                                 GLsizei srcHeight, GLsizei srcDepth,
                                 GLsizei signalSemaphoreCount,
                                 const GLuint *signalSemaphoreArray,
                                 const GLuint64 *signalValueArray) const;
    void multicastScissorArrayV(GLuint gpu, GLuint first, GLsizei count,
                                const GLint *v) const;
    void multicastViewportArrayV(GLuint gpu, GLuint first, GLsizei count,
                                 const GLfloat *v) const;
    void multicastViewportPositionWScale(GLuint gpu, GLuint index,
                                         GLfloat xcoeff, GLfloat ycoeff) const;
    void uploadGpuMask(GLbitfield mask) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVXGPUMULTICAST2 _api;
};

// Manages the entry points for the GL_NVX_linked_gpu_multicast extension API.
class NVXLinkedGPUMulticastAPI : public BaseExtension
{
public:
    // Construction
    NVXLinkedGPUMulticastAPI();

    // Accessors
    const NVXLinkedGPUMulticast &getRawAPI() const;

    // Operations
    void lgpuCopyImageSubData(GLuint sourceGpu, GLbitfield destinationGpuMask,
                              GLuint srcName, GLenum srcTarget, GLint srcLevel,
                              GLint srcX, GLint srxY, GLint srcZ, GLuint dstName,
                              GLenum dstTarget, GLint dstLevel, GLint dstX,
                              GLint dstY, GLint dstZ, GLsizei width,
                              GLsizei height, GLsizei depth) const;
    void lgpuInterlock() const;
    void lgpuNamedBufferSubData(GLbitfield gpuMask, BufferName buffer,
                                GLintptr offset, GLsizeiptr size,
                                const void *data) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVXLinkedGPUMulticast _api;
};

// Manages the entry points for the GL_NVX_progress_fence extension API.
class NVXProgressFenceAPI : public BaseExtension
{
public:
    // Construction
    NVXProgressFenceAPI();

    // Accessors
    const NVXProgressFence &getRawAPI() const;

    // Operations
    void clientWaitSemaphoreUI64(GLsizei fenceObjectCount,
                                 const GLuint *semaphoreArray,
                                 const GLuint64 *fenceValueArray) const;
    GLuint createProgressFence() const;
    void signalSemaphoreUI64(GLuint signalGpu, GLsizei fenceObjectCount,
                             const GLuint *semaphoreArray,
                             const GLuint64 *fenceValueArray) const;
    void waitSemaphoreUI64(GLuint waitGpu, GLsizei fenceObjectCount,
                           const GLuint *semaphoreArray,
                           const GLuint64 *fenceValueArray) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVXProgressFence _api;
};

// Manages the entry points for the GL_NV_alpha_to_coverage_dither_control extension API.
class NVAlphaToCoverageDitherControlAPI : public BaseExtension
{
public:
    // Construction
    NVAlphaToCoverageDitherControlAPI();

    // Accessors
    const NVAlphaToCoverageDitherControl &getRawAPI() const;

    // Operations
    void alphaToCoverageDitherControl(GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVAlphaToCoverageDitherControl _api;
};

// Manages the entry points for the GL_NV_bindless_multi_draw_indirect extension API.
class NVBindlessMultiDrawIndirectAPI : public BaseExtension
{
public:
    // Construction
    NVBindlessMultiDrawIndirectAPI();

    // Accessors
    const NVBindlessMultiDrawIndirect &getRawAPI() const;

    // Operations
    void multiDrawArraysIndirectBindless(PrimitiveType mode,
                                         const void *indirect, GLsizei drawCount,
                                         GLsizei stride, GLint vertexBufferCount) const;
    void multiDrawElementsIndirectBindless(PrimitiveType mode,
                                           DrawElementsType type,
                                           const void *indirect,
                                           GLsizei drawCount, GLsizei stride,
                                           GLint vertexBufferCount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVBindlessMultiDrawIndirect _api;
};

// Manages the entry points for the GL_NV_bindless_multi_draw_indirect_count extension API.
class NVBindlessMultiDrawIndirectCountAPI : public BaseExtension
{
public:
    // Construction
    NVBindlessMultiDrawIndirectCountAPI();

    // Accessors
    const NVBindlessMultiDrawIndirectCount &getRawAPI() const;

    // Operations
    void multiDrawArraysIndirectBindlessCount(PrimitiveType mode,
                                              const void *indirect,
                                              GLsizei drawCount,
                                              GLsizei maxDrawCount,
                                              GLsizei stride,
                                              GLint vertexBufferCount) const;
    void multiDrawElementsIndirectBindlessCount(PrimitiveType mode,
                                                DrawElementsType type,
                                                const void *indirect,
                                                GLsizei drawCount,
                                                GLsizei maxDrawCount,
                                                GLsizei stride,
                                                GLint vertexBufferCount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVBindlessMultiDrawIndirectCount _api;
};

// Manages the entry points for the GL_NV_bindless_texture extension API.
class NVBindlessTextureAPI : public BaseExtension
{
public:
    // Construction
    NVBindlessTextureAPI();

    // Accessors
    const NVBindlessTexture &getRawAPI() const;

    // Operations
    GLuint64 getImageHandle(TextureName texture, GLint level, Boolean layered,
                            GLint layer, PixelFormat format) const;
    GLuint64 getTextureHandle(TextureName texture) const;
    GLuint64 getTextureSamplerHandle(TextureName texture, SamplerName sampler) const;
    Boolean isImageHandleResident(GLuint64 handle) const;
    Boolean isTextureHandleResident(GLuint64 handle) const;
    void makeImageHandleNonResident(GLuint64 handle) const;
    void makeImageHandleResident(GLuint64 handle, GLenum access) const;
    void makeTextureHandleNonResident(GLuint64 handle) const;
    void makeTextureHandleResident(GLuint64 handle) const;
    void programUniformHandleUI64(ProgramName program, GLint location,
                                  GLuint64 value) const;
    void programUniformHandleUI64(ProgramName program, GLint location,
                                  GLsizei count, const GLuint64 *values) const;
    void uniformHandleUI64(GLint location, GLuint64 value) const;
    void uniformHandleUI64(GLint location, GLsizei count, const GLuint64 *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVBindlessTexture _api;
};

// Manages the entry points for the GL_NV_blend_equation_advanced extension API.
class NVBlendEquationAdvancedAPI : public BaseExtension
{
public:
    // Construction
    NVBlendEquationAdvancedAPI();

    // Accessors
    const NVBlendEquationAdvanced &getRawAPI() const;

    // Operations
    void blendBarrier() const;
    void blendParameterI(GLenum pname, GLint value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVBlendEquationAdvanced _api;
};

// Manages the entry points for the GL_NV_clip_space_w_scaling extension API.
class NVClipSpaceWScalingAPI : public BaseExtension
{
public:
    // Construction
    NVClipSpaceWScalingAPI();

    // Accessors
    const NVClipSpaceWScaling &getRawAPI() const;

    // Operations
    void viewportPositionWScale(GLuint index, GLfloat xcoeff, GLfloat ycoeff) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVClipSpaceWScaling _api;
};

// Manages the entry points for the GL_NV_command_list extension API.
class NVCommandListAPI : public BaseExtension
{
public:
    // Construction
    NVCommandListAPI();

    // Accessors
    const NVCommandList &getRawAPI() const;

    // Operations
    void callCommandList(GLuint list) const;
    void commandListSegments(GLuint list, GLuint segments) const;
    void compileCommandList(GLuint list) const;
    void createCommandLists(GLsizei n, GLuint *lists) const;
    void createStateS(GLsizei n, GLuint *states) const;
    void deleteCommandLists(GLsizei n, const GLuint *lists) const;
    void deleteStateS(GLsizei n, const GLuint *states) const;
    void drawCommandsAddress(GLenum primitiveMode, const GLuint64 *indirects,
                             const GLsizei *sizes, GLuint count) const;
    void drawCommands(GLenum primitiveMode, GLuint buffer,
                      const GLintptr *indirects, const GLsizei *sizes,
                      GLuint count) const;
    void drawCommandsStateSAddress(const GLuint64 *indirects,
                                   const GLsizei *sizes, const GLuint *states,
                                   const GLuint *fbos, GLuint count) const;
    void drawCommandsStateS(BufferName buffer, const GLintptr *indirects,
                            const GLsizei *sizes, const GLuint *states,
                            const GLuint *fbos, GLuint count) const;
    GLuint getCommandHeader(GLenum tokenID, GLuint size) const;
    GLushort getStageIndex(ShaderType shadertype) const;
    Boolean isCommandList(GLuint list) const;
    Boolean isState(GLuint state) const;
    void listDrawCommandsStateSClient(GLuint list, GLuint segment,
                                      const void **indirects,
                                      const GLsizei *sizes, const GLuint *states,
                                      const GLuint *fbos, GLuint count) const;
    void stateCapture(GLuint state, GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVCommandList _api;
};

// Manages the entry points for the GL_NV_conditional_render extension API.
class NVConditionalRenderAPI : public BaseExtension
{
public:
    // Construction
    NVConditionalRenderAPI();

    // Accessors
    const NVConditionalRender &getRawAPI() const;

    // Operations
    void beginConditionalRender(GLuint id, ConditionalRenderMode mode) const;
    void endConditionalRender() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVConditionalRender _api;
};

// Manages the entry points for the GL_NV_conservative_raster extension API.
class NVConservativeRasterAPI : public BaseExtension
{
public:
    // Construction
    NVConservativeRasterAPI();

    // Accessors
    const NVConservativeRaster &getRawAPI() const;

    // Operations
    void subpixelPrecisionBias(GLuint xbits, GLuint ybits) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVConservativeRaster _api;
};

// Manages the entry points for the GL_NV_conservative_raster_dilate extension API.
class NVConservativeRasterDilateAPI : public BaseExtension
{
public:
    // Construction
    NVConservativeRasterDilateAPI();

    // Accessors
    const NVConservativeRasterDilate &getRawAPI() const;

    // Operations
    void conservativeRasterParameterF(GLenum pname, GLfloat value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVConservativeRasterDilate _api;
};

// Manages the entry points for the GL_NV_conservative_raster_pre_snap_triangles extension API.
class NVConservativeRasterPreSnapTrianglesAPI : public BaseExtension
{
public:
    // Construction
    NVConservativeRasterPreSnapTrianglesAPI();

    // Accessors
    const NVConservativeRasterPreSnapTriangles &getRawAPI() const;

    // Operations
    void conservativeRasterParameterI(GLenum pname, GLint param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVConservativeRasterPreSnapTriangles _api;
};

// Manages the entry points for the GL_NV_copy_image extension API.
class NVCopyImageAPI : public BaseExtension
{
public:
    // Construction
    NVCopyImageAPI();

    // Accessors
    const NVCopyImage &getRawAPI() const;

    // Operations
    void copyImageSubData(GLuint srcName, CopyBufferSubDataTarget srcTarget,
                          GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ,
                          GLuint dstName, CopyBufferSubDataTarget dstTarget,
                          GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
                          GLsizei width, GLsizei height, GLsizei depth) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVCopyImage _api;
};

// Manages the entry points for the GL_NV_depth_buffer_float extension API.
class NVDepthBufferFloatAPI : public BaseExtension
{
public:
    // Construction
    NVDepthBufferFloatAPI();

    // Accessors
    const NVDepthBufferFloat &getRawAPI() const;

    // Operations
    void clearDepthD(GLdouble depth) const;
    void depthBoundsD(GLdouble zmin, GLdouble zmax) const;
    void depthRangeD(GLdouble zNear, GLdouble zFar) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDepthBufferFloat _api;
};

// Manages the entry points for the GL_NV_draw_texture extension API.
class NVDrawTextureAPI : public BaseExtension
{
public:
    // Construction
    NVDrawTextureAPI();

    // Accessors
    const NVDrawTexture &getRawAPI() const;

    // Operations
    void drawTexture(TextureName texture, SamplerName sampler, GLfloat x0,
                     GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0,
                     GLfloat t0, GLfloat s1, GLfloat t1) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDrawTexture _api;
};

// Manages the entry points for the GL_NV_draw_vulkan_image extension API.
class NVDrawVulkanImageAPI : public BaseExtension
{
public:
    // Construction
    NVDrawVulkanImageAPI();

    // Accessors
    const NVDrawVulkanImage &getRawAPI() const;

    // Operations
    void drawVkImage(GLuint64 vkImage, SamplerName sampler, GLfloat x0,
                     GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0,
                     GLfloat t0, GLfloat s1, GLfloat t1) const;
    GLVULKANPROCNV getVkProcAddr(const GLchar *name) const;
    void signalVkFence(GLuint64 vkFence) const;
    void signalVkSemaphore(GLuint64 vkSemaphore) const;
    void waitVkSemaphore(GLuint64 vkSemaphore) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDrawVulkanImage _api;
};

// Manages the entry points for the GL_NV_evaluators extension API.
class NVEvaluatorsAPI : public BaseExtension
{
public:
    // Construction
    NVEvaluatorsAPI();

    // Accessors
    const NVEvaluators &getRawAPI() const;

    // Operations
    void evalMaps(EvalTargetNV target, GLenum mode) const;
    void getMapAttribParameterFV(EvalTargetNV target, GLuint index,
                                 MapAttribParameterNV pname, GLfloat *params) const;
    void getMapAttribParameterIV(EvalTargetNV target, GLuint index,
                                 MapAttribParameterNV pname, GLint *params) const;
    void getMapControlPoints(EvalTargetNV target, GLuint index, MapTypeNV type,
                             GLsizei ustride, GLsizei vstride, Boolean packed,
                             void *points) const;
    void getMapParameterFV(EvalTargetNV target, MapParameterNV pname,
                           GLfloat *params) const;
    void getMapParameterIV(EvalTargetNV target, MapParameterNV pname,
                           GLint *params) const;
    void mapControlPoints(EvalTargetNV target, GLuint index, MapTypeNV type,
                          GLsizei ustride, GLsizei vstride, GLint uorder,
                          GLint vorder, Boolean packed, const void *points) const;
    void mapParameterFV(EvalTargetNV target, MapParameterNV pname,
                        const GLfloat *params) const;
    void mapParameterIV(EvalTargetNV target, MapParameterNV pname,
                        const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVEvaluators _api;
};

// Manages the entry points for the GL_NV_explicit_multisample extension API.
class NVExplicitMultisampleAPI : public BaseExtension
{
public:
    // Construction
    NVExplicitMultisampleAPI();

    // Accessors
    const NVExplicitMultisample &getRawAPI() const;

    // Operations
    void getMultisampleFV(GetMultisamplePNameNV pname, GLuint index,
                          GLfloat *val) const;
    void sampleMaskIndexed(GLuint index, GLbitfield mask) const;
    void texRenderbuffer(TextureTarget target, RenderBufferName renderbuffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVExplicitMultisample _api;
};

// Manages the entry points for the GL_NV_fence extension API.
class NVFenceAPI : public BaseExtension
{
public:
    // Construction
    NVFenceAPI();

    // Accessors
    const NVFence &getRawAPI() const;

    // Operations
    void deleteFences(GLsizei n, const GLuint *fences) const;
    void finishFence(GLuint fence) const;
    void genFences(GLsizei n, GLuint *fences) const;
    void getFenceIV(GLuint fence, FenceParameterNameNV pname, GLint *params) const;
    Boolean isFence(GLuint fence) const;
    void setFence(GLuint fence, FenceConditionNV condition) const;
    Boolean testFence(GLuint fence) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVFence _api;
};

// Manages the entry points for the GL_NV_fragment_coverage_to_color extension API.
class NVFragmentCoverageToColorAPI : public BaseExtension
{
public:
    // Construction
    NVFragmentCoverageToColorAPI();

    // Accessors
    const NVFragmentCoverageToColor &getRawAPI() const;

    // Operations
    void fragmentCoverageColor(GLuint color) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVFragmentCoverageToColor _api;
};

// Manages the entry points for the GL_NV_fragment_program extension API.
class NVFragmentProgramAPI : public BaseExtension
{
public:
    // Construction
    NVFragmentProgramAPI();

    // Accessors
    const NVFragmentProgram &getRawAPI() const;

    // Operations
    void getProgramNamedParameterDV(ProgramName id, GLsizei len,
                                    const GLubyte *name, GLdouble *params) const;
    void getProgramNamedParameterFV(ProgramName id, GLsizei len,
                                    const GLubyte *name, GLfloat *params) const;
    void programNamedParameter4D(ProgramName id, GLsizei len,
                                 const GLubyte *name, GLdouble x, GLdouble y,
                                 GLdouble z, GLdouble w) const;
    void programNamedParameter4DV(ProgramName id, GLsizei len,
                                  const GLubyte *name, const GLdouble *v) const;
    void programNamedParameter4F(ProgramName id, GLsizei len,
                                 const GLubyte *name, GLfloat x, GLfloat y,
                                 GLfloat z, GLfloat w) const;
    void programNamedParameter4FV(ProgramName id, GLsizei len,
                                  const GLubyte *name, const GLfloat *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVFragmentProgram _api;
};

// Manages the entry points for the GL_NV_framebuffer_mixed_samples extension API.
class NVFramebufferMixedSamplesAPI : public BaseExtension
{
public:
    // Construction
    NVFramebufferMixedSamplesAPI();

    // Accessors
    const NVFramebufferMixedSamples &getRawAPI() const;

    // Operations
    void coverageModulation(GLenum components) const;
    void coverageModulationTable(GLsizei n, const GLfloat *v) const;
    void getCoverageModulationTable(GLsizei bufSize, GLfloat *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVFramebufferMixedSamples _api;
};

// Manages the entry points for the GL_NV_framebuffer_multisample_coverage extension API.
class NVFramebufferMultisampleCoverageAPI : public BaseExtension
{
public:
    // Construction
    NVFramebufferMultisampleCoverageAPI();

    // Accessors
    const NVFramebufferMultisampleCoverage &getRawAPI() const;

    // Operations
    void renderbufferStorageMultisampleCoverage(RenderBufferTarget target,
                                                GLsizei coverageSamples,
                                                GLsizei colorSamples,
                                                InternalFormat internalformat,
                                                GLsizei width, GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVFramebufferMultisampleCoverage _api;
};

// Manages the entry points for the GL_NV_geometry_program4 extension API.
class NVGeometryPROGRAM4API : public BaseExtension
{
public:
    // Construction
    NVGeometryPROGRAM4API();

    // Accessors
    const NVGeometryPROGRAM4 &getRawAPI() const;

    // Operations
    void framebufferTexture(FrameBufferTarget target,
                            FramebufferAttachment attachment,
                            TextureName texture, GLint level) const;
    void framebufferTextureFace(FrameBufferTarget target,
                                FramebufferAttachment attachment,
                                TextureName texture, GLint level,
                                TextureTarget face) const;
    void programVertexLimit(ProgramTarget target, GLint limit) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVGeometryPROGRAM4 _api;
};

// Manages the entry points for the GL_NV_gpu_multicast extension API.
class NVGPUMulticastAPI : public BaseExtension
{
public:
    // Construction
    NVGPUMulticastAPI();

    // Accessors
    const NVGPUMulticast &getRawAPI() const;

    // Operations
    void multicastBarrier() const;
    void multicastBlitFramebuffer(GLuint srcGpu, GLuint dstGpu, GLint srcX0,
                                  GLint srcY0, GLint srcX1, GLint srcY1,
                                  GLint dstX0, GLint dstY0, GLint dstX1,
                                  GLint dstY1,
                                  GLbitfield  /* ClearBufferMask */ mask,
                                  GLenum filter) const;
    void multicastBufferSubData(GLbitfield gpuMask, BufferName buffer,
                                GLintptr offset, GLsizeiptr size,
                                const void *data) const;
    void multicastCopyBufferSubData(GLuint readGpu, GLbitfield writeGpuMask,
                                    BufferName readBuffer,
                                    BufferName writeBuffer, GLintptr readOffset,
                                    GLintptr writeOffset, GLsizeiptr size) const;
    void multicastCopyImageSubData(GLuint srcGpu, GLbitfield dstGpuMask,
                                   GLuint srcName, GLenum srcTarget,
                                   GLint srcLevel, GLint srcX, GLint srcY,
                                   GLint srcZ, GLuint dstName, GLenum dstTarget,
                                   GLint dstLevel, GLint dstX, GLint dstY,
                                   GLint dstZ, GLsizei srcWidth,
                                   GLsizei srcHeight, GLsizei srcDepth) const;
    void multicastFramebufferSampleLocationsFV(GLuint gpu,
                                               FrameBufferName framebuffer,
                                               GLuint start, GLsizei count,
                                               const GLfloat *v) const;
    void multicastGetQueryObjectI64V(GLuint gpu, GLuint id, GLenum pname,
                                     GLint64 *params) const;
    void multicastGetQueryObjectIV(GLuint gpu, GLuint id, GLenum pname,
                                   GLint *params) const;
    void multicastGetQueryObjectUI64(GLuint gpu, GLuint id, GLenum pname,
                                     GLuint64 *params) const;
    void multicastGetQueryObjectUIV(GLuint gpu, GLuint id, GLenum pname,
                                    GLuint *params) const;
    void multicastWaitSync(GLuint signalGpu, GLbitfield waitGpuMask) const;
    void renderGpuMask(GLbitfield mask) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVGPUMulticast _api;
};

// Manages the entry points for the GL_NV_gpu_program4 extension API.
class NVGPUPROGRAM4API : public BaseExtension
{
public:
    // Construction
    NVGPUPROGRAM4API();

    // Accessors
    const NVGPUPROGRAM4 &getRawAPI() const;

    // Operations
    void getProgramEnvParameterIIV(ProgramTarget target, GLuint index,
                                   GLint *params) const;
    void getProgramEnvParameterIUIV(ProgramTarget target, GLuint index,
                                    GLuint *params) const;
    void getProgramLocalParameterIIV(ProgramTarget target, GLuint index,
                                     GLint *params) const;
    void getProgramLocalParameterIUIV(ProgramTarget target, GLuint index,
                                      GLuint *params) const;
    void programEnvParameterI4I(ProgramTarget target, GLuint index, GLint x,
                                GLint y, GLint z, GLint w) const;
    void programEnvParameterI4IV(ProgramTarget target, GLuint index,
                                 const GLint *params) const;
    void programEnvParameterI4UI(ProgramTarget target, GLuint index, GLuint x,
                                 GLuint y, GLuint z, GLuint w) const;
    void programEnvParameterI4UIV(ProgramTarget target, GLuint index,
                                  const GLuint *params) const;
    void programEnvParametersI4IV(ProgramTarget target, GLuint index,
                                  GLsizei count, const GLint *params) const;
    void programEnvParametersI4UIV(ProgramTarget target, GLuint index,
                                   GLsizei count, const GLuint *params) const;
    void programLocalParameterI4I(ProgramTarget target, GLuint index, GLint x,
                                  GLint y, GLint z, GLint w) const;
    void programLocalParameterI4IV(ProgramTarget target, GLuint index,
                                   const GLint *params) const;
    void programLocalParameterI4UI(ProgramTarget target, GLuint index, GLuint x,
                                   GLuint y, GLuint z, GLuint w) const;
    void programLocalParameterI4UIV(ProgramTarget target, GLuint index,
                                    const GLuint *params) const;
    void programLocalParametersI4IV(ProgramTarget target, GLuint index,
                                    GLsizei count, const GLint *params) const;
    void programLocalParametersI4UIV(ProgramTarget target, GLuint index,
                                     GLsizei count, const GLuint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVGPUPROGRAM4 _api;
};

// Manages the entry points for the GL_NV_gpu_program5 extension API.
class NVGPUPROGRAM5API : public BaseExtension
{
public:
    // Construction
    NVGPUPROGRAM5API();

    // Accessors
    const NVGPUPROGRAM5 &getRawAPI() const;

    // Operations
    void getProgramSubroutineParameterUIV(GLenum target, GLuint index,
                                          GLuint *param) const;
    void programSubroutineParametersUIV(GLenum target, GLsizei count,
                                        const GLuint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVGPUPROGRAM5 _api;
};

// Manages the entry points for the GL_NV_half_float extension API.
class NVHalfFloatAPI : public BaseExtension
{
public:
    // Construction
    NVHalfFloatAPI();

    // Accessors
    const NVHalfFloat &getRawAPI() const;

    // Operations
    void color3H(GLhalfNV red, GLhalfNV green, GLhalfNV blue) const;
    void color3HV(const GLhalfNV *v) const;
    void color4H(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha) const;
    void color4HV(const GLhalfNV *v) const;
    void fogCoordh(GLhalfNV fog) const;
    void fogCoordhV(const GLhalfNV *fog) const;
    void multiTexCoord1H(TextureUnit target, GLhalfNV s) const;
    void multiTexCoord1HV(TextureUnit target, const GLhalfNV *v) const;
    void multiTexCoord2H(TextureUnit target, GLhalfNV s, GLhalfNV t) const;
    void multiTexCoord2HV(TextureUnit target, const GLhalfNV *v) const;
    void multiTexCoord3H(TextureUnit target, GLhalfNV s, GLhalfNV t, GLhalfNV r) const;
    void multiTexCoord3HV(TextureUnit target, const GLhalfNV *v) const;
    void multiTexCoord4H(TextureUnit target, GLhalfNV s, GLhalfNV t, GLhalfNV r,
                         GLhalfNV q) const;
    void multiTexCoord4HV(TextureUnit target, const GLhalfNV *v) const;
    void normal3H(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz) const;
    void normal3HV(const GLhalfNV *v) const;
    void secondaryColor3H(GLhalfNV red, GLhalfNV green, GLhalfNV blue) const;
    void secondaryColor3HV(const GLhalfNV *v) const;
    void texCoord1H(GLhalfNV s) const;
    void texCoord1HV(const GLhalfNV *v) const;
    void texCoord2H(GLhalfNV s, GLhalfNV t) const;
    void texCoord2HV(const GLhalfNV *v) const;
    void texCoord3H(GLhalfNV s, GLhalfNV t, GLhalfNV r) const;
    void texCoord3HV(const GLhalfNV *v) const;
    void texCoord4H(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q) const;
    void texCoord4HV(const GLhalfNV *v) const;
    void vertex2H(GLhalfNV x, GLhalfNV y) const;
    void vertex2HV(const GLhalfNV *v) const;
    void vertex3H(GLhalfNV x, GLhalfNV y, GLhalfNV z) const;
    void vertex3HV(const GLhalfNV *v) const;
    void vertex4H(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w) const;
    void vertex4HV(const GLhalfNV *v) const;
    void vertexAttrib1H(GLuint index, GLhalfNV x) const;
    void vertexAttrib1HV(GLuint index, const GLhalfNV *v) const;
    void vertexAttrib2H(GLuint index, GLhalfNV x, GLhalfNV y) const;
    void vertexAttrib2HV(GLuint index, const GLhalfNV *v) const;
    void vertexAttrib3H(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z) const;
    void vertexAttrib3HV(GLuint index, const GLhalfNV *v) const;
    void vertexAttrib4H(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z,
                        GLhalfNV w) const;
    void vertexAttrib4HV(GLuint index, const GLhalfNV *v) const;
    void vertexAttribs1HV(GLuint index, GLsizei n, const GLhalfNV *v) const;
    void vertexAttribs2HV(GLuint index, GLsizei n, const GLhalfNV *v) const;
    void vertexAttribs3HV(GLuint index, GLsizei n, const GLhalfNV *v) const;
    void vertexAttribs4HV(GLuint index, GLsizei n, const GLhalfNV *v) const;
    void vertexWeighth(GLhalfNV weight) const;
    void vertexWeighthV(const GLhalfNV *weight) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVHalfFloat _api;
};

// Manages the entry points for the GL_NV_internalformat_sample_query extension API.
class NVInternalformatSampleQueryAPI : public BaseExtension
{
public:
    // Construction
    NVInternalformatSampleQueryAPI();

    // Accessors
    const NVInternalformatSampleQuery &getRawAPI() const;

    // Operations
    void getInternalformatSampleIV(TextureTarget target,
                                   InternalFormat internalformat,
                                   GLsizei samples, InternalFormatPName pname,
                                   GLsizei count, GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVInternalformatSampleQuery _api;
};

// Manages the entry points for the GL_NV_memory_attachment extension API.
class NVMemoryAttachmentAPI : public BaseExtension
{
public:
    // Construction
    NVMemoryAttachmentAPI();

    // Accessors
    const NVMemoryAttachment &getRawAPI() const;

    // Operations
    void bufferAttachMemory(BufferTarget target, GLuint memory,
                            GLuint64 offset) const;
    void getMemoryObjectDetachedResourcesuiv(GLuint memory, GLenum pname,
                                             GLint first, GLsizei count,
                                             GLuint *params) const;
    void namedBufferAttachMemory(BufferName buffer, GLuint memory,
                                 GLuint64 offset) const;
    void resetMemoryObjectParameter(GLuint memory, GLenum pname) const;
    void texAttachMemory(TextureTarget target, GLuint memory, GLuint64 offset) const;
    void textureAttachMemory(TextureName texture, GLuint memory, GLuint64 offset) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVMemoryAttachment _api;
};

// Manages the entry points for the GL_NV_memory_object_sparse extension API.
class NVMemoryObjectSparseAPI : public BaseExtension
{
public:
    // Construction
    NVMemoryObjectSparseAPI();

    // Accessors
    const NVMemoryObjectSparse &getRawAPI() const;

    // Operations
    void bufferPageCommitmentMem(BufferStorageTarget target, GLintptr offset,
                                 GLsizeiptr size, GLuint memory,
                                 GLuint64 memOffset, Boolean commit) const;
    void namedBufferPageCommitmentMem(BufferName buffer, GLintptr offset,
                                      GLsizeiptr size, GLuint memory,
                                      GLuint64 memOffset, Boolean commit) const;
    void texPageCommitmentMem(TextureTarget target, GLint layer, GLint level,
                              GLint xoffset, GLint yoffset, GLint zoffset,
                              GLsizei width, GLsizei height, GLsizei depth,
                              GLuint memory, GLuint64 offset, Boolean commit) const;
    void texturePageCommitmentMem(TextureName texture, GLint layer, GLint level,
                                  GLint xoffset, GLint yoffset, GLint zoffset,
                                  GLsizei width, GLsizei height, GLsizei depth,
                                  GLuint memory, GLuint64 offset, Boolean commit) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVMemoryObjectSparse _api;
};

// Manages the entry points for the GL_NV_mesh_shader extension API.
class NVMeshShaderAPI : public BaseExtension
{
public:
    // Construction
    NVMeshShaderAPI();

    // Accessors
    const NVMeshShader &getRawAPI() const;

    // Operations
    void drawMeshTasksIndirect(GLintptr indirect) const;
    void drawMeshTasks(GLuint first, GLuint count) const;
    void multiDrawMeshTasksIndirectCount(GLintptr indirect, GLintptr drawcount,
                                         GLsizei maxdrawcount, GLsizei stride) const;
    void multiDrawMeshTasksIndirect(GLintptr indirect, GLsizei drawcount,
                                    GLsizei stride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVMeshShader _api;
};

// Manages the entry points for the GL_NV_occlusion_query extension API.
class NVOcclusionQueryAPI : public BaseExtension
{
public:
    // Construction
    NVOcclusionQueryAPI();

    // Accessors
    const NVOcclusionQuery &getRawAPI() const;

    // Operations
    void beginOcclusionQuery(GLuint id) const;
    void deleteOcclusionQueries(GLsizei n, const GLuint *ids) const;
    void endOcclusionQuery() const;
    void genOcclusionQueries(GLsizei n, GLuint *ids) const;
    void getOcclusionQueryIV(GLuint id, OcclusionQueryParameterNameNV pname,
                             GLint *params) const;
    void getOcclusionQueryUIV(GLuint id, OcclusionQueryParameterNameNV pname,
                              GLuint *params) const;
    Boolean isOcclusionQuery(GLuint id) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVOcclusionQuery _api;
};

// Manages the entry points for the GL_NV_parameter_buffer_object extension API.
class NVParameterBufferObjectAPI : public BaseExtension
{
public:
    // Construction
    NVParameterBufferObjectAPI();

    // Accessors
    const NVParameterBufferObject &getRawAPI() const;

    // Operations
    void programBufferParametersIIV(ProgramTarget target, GLuint bindingIndex,
                                    GLuint wordIndex, GLsizei count,
                                    const GLint *params) const;
    void programBufferParametersIUIV(ProgramTarget target, GLuint bindingIndex,
                                     GLuint wordIndex, GLsizei count,
                                     const GLuint *params) const;
    void programBufferParametersFV(ProgramTarget target, GLuint bindingIndex,
                                   GLuint wordIndex, GLsizei count,
                                   const GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVParameterBufferObject _api;
};

// Manages the entry points for the GL_NV_path_rendering extension API.
class NVPathRenderingAPI : public BaseExtension
{
public:
    // Construction
    NVPathRenderingAPI();

    // Accessors
    const NVPathRendering &getRawAPI() const;

    // Operations
    void copyPath(GLuint resultPath, GLuint srcPath) const;
    void coverFillPathInstanced(GLsizei numPaths, PathElementType pathNameType,
                                const void *paths, GLuint pathBase,
                                PathCoverMode coverMode,
                                PathTransformType transformType,
                                const GLfloat *transformValues) const;
    void coverFillPath(GLuint path, PathCoverMode coverMode) const;
    void coverStrokePathInstanced(GLsizei numPaths, PathElementType pathNameType,
                                  const void *paths, GLuint pathBase,
                                  PathCoverMode coverMode,
                                  PathTransformType transformType,
                                  const GLfloat *transformValues) const;
    void coverStrokePath(GLuint path, PathCoverMode coverMode) const;
    void deletePaths(GLuint path, GLsizei range) const;
    GLuint genPaths(GLsizei range) const;
    void getPathCommands(GLuint path, GLubyte *commands) const;
    void getPathCoords(GLuint path, GLfloat *coords) const;
    void getPathDashArray(GLuint path, GLfloat *dashArray) const;
    GLfloat getPathLength(GLuint path, GLsizei startSegment, GLsizei numSegments) const;
    void getPathMetricRange(GLbitfield  /* PathMetricMask */ metricQueryMask,
                            GLuint firstPathName, GLsizei numPaths,
                            GLsizei stride, GLfloat *metrics) const;
    void getPathMetrics(GLbitfield  /* PathMetricMask */ metricQueryMask,
                        GLsizei numPaths, PathElementType pathNameType,
                        const void *paths, GLuint pathBase, GLsizei stride,
                        GLfloat *metrics) const;
    void getPathParameterFV(GLuint path, PathParameter pname, GLfloat *value) const;
    void getPathParameterIV(GLuint path, PathParameter pname, GLint *value) const;
    void getPathSpacing(PathListMode pathListMode, GLsizei numPaths,
                        PathElementType pathNameType, const void *paths,
                        GLuint pathBase, GLfloat advanceScale,
                        GLfloat kerningScale, PathTransformType transformType,
                        GLfloat *returnedSpacing) const;
    void getProgramResourceFV(ProgramName program,
                              ProgramInterface programInterface, GLuint index,
                              GLsizei propCount, const GLenum *props,
                              GLsizei count, GLsizei *length, GLfloat *params) const;
    void interpolatePaths(GLuint resultPath, GLuint pathA, GLuint pathB,
                          GLfloat weight) const;
    Boolean isPath(GLuint path) const;
    Boolean isPointInFillPath(GLuint path, GLuint mask, GLfloat x, GLfloat y) const;
    Boolean isPointInStrokePath(GLuint path, GLfloat x, GLfloat y) const;
    void matrixLoad3x2F(GLenum matrixMode, const GLfloat *m) const;
    void matrixLoad3x3F(GLenum matrixMode, const GLfloat *m) const;
    void matrixLoadTranspose3x3F(GLenum matrixMode, const GLfloat *m) const;
    void matrixMult3x2F(GLenum matrixMode, const GLfloat *m) const;
    void matrixMult3x3F(GLenum matrixMode, const GLfloat *m) const;
    void matrixMultTranspose3x3F(GLenum matrixMode, const GLfloat *m) const;
    void pathCommands(GLuint path, GLsizei numCommands, const GLubyte *commands,
                      GLsizei numCoords, PathCoordType coordType,
                      const void *coords) const;
    void pathCoords(GLuint path, GLsizei numCoords, PathCoordType coordType,
                    const void *coords) const;
    void pathCoverDepthFunc(DepthFunction func) const;
    void pathDashArray(GLuint path, GLsizei dashCount, const GLfloat *dashArray) const;
    GLenum pathGlyphIndexArray(GLuint firstPathName, GLenum fontTarget,
                               const void *fontName,
                               GLbitfield  /* PathFontStyle */ fontStyle,
                               GLuint firstGlyphIndex, GLsizei numGlyphs,
                               GLuint pathParameterTemplate, GLfloat emScale) const;
    GLenum pathGlyphIndexRange(GLenum fontTarget, const void *fontName,
                               GLbitfield  /* PathFontStyle */ fontStyle,
                               GLuint pathParameterTemplate, GLfloat emScale,
                               GLuint *baseAndCount) const;
    void pathGlyphRange(GLuint firstPathName, PathFontTarget fontTarget,
                        const void *fontName,
                        GLbitfield  /* PathFontStyle */ fontStyle,
                        GLuint firstGlyph, GLsizei numGlyphs,
                        PathHandleMissingGlyphs handleMissingGlyphs,
                        GLuint pathParameterTemplate, GLfloat emScale) const;
    void pathGlyphs(GLuint firstPathName, PathFontTarget fontTarget,
                    const void *fontName,
                    GLbitfield  /* PathFontStyle */ fontStyle, GLsizei numGlyphs,
                    PathElementType type, const void *charcodes,
                    PathHandleMissingGlyphs handleMissingGlyphs,
                    GLuint pathParameterTemplate, GLfloat emScale) const;
    GLenum pathMemoryGlyphIndexArray(GLuint firstPathName, GLenum fontTarget,
                                     GLsizeiptr fontSize, const void *fontData,
                                     GLsizei faceIndex, GLuint firstGlyphIndex,
                                     GLsizei numGlyphs,
                                     GLuint pathParameterTemplate,
                                     GLfloat emScale) const;
    void pathParameterF(GLuint path, PathParameter pname, GLfloat value) const;
    void pathParameterFV(GLuint path, PathParameter pname, const GLfloat *value) const;
    void pathParameterI(GLuint path, PathParameter pname, GLint value) const;
    void pathParameterIV(GLuint path, PathParameter pname, const GLint *value) const;
    void pathStencilDepthOffset(GLfloat factor, GLfloat units) const;
    void pathStencilFunc(StencilFunction func, GLint ref, GLuint mask) const;
    void pathString(GLuint path, PathStringFormat format, GLsizei length,
                    const void *pathString) const;
    void pathSubCommands(GLuint path, GLsizei commandStart,
                         GLsizei commandsToDelete, GLsizei numCommands,
                         const GLubyte *commands, GLsizei numCoords,
                         PathCoordType coordType, const void *coords) const;
    void pathSubCoords(GLuint path, GLsizei coordStart, GLsizei numCoords,
                       PathCoordType coordType, const void *coords) const;
    Boolean pointAlongPath(GLuint path, GLsizei startSegment,
                           GLsizei numSegments, GLfloat distance, GLfloat *x,
                           GLfloat *y, GLfloat *tangentX, GLfloat *tangentY) const;
    void programPathFragmentInputGen(ProgramName program, GLint location,
                                     GLenum genMode, GLint components,
                                     const GLfloat *coeffs) const;
    void stencilFillPathInstanced(GLsizei numPaths, PathElementType pathNameType,
                                  const void *paths, GLuint pathBase,
                                  PathFillMode fillMode, GLuint mask,
                                  PathTransformType transformType,
                                  const GLfloat *transformValues) const;
    void stencilFillPath(GLuint path, PathFillMode fillMode, GLuint mask) const;
    void stencilStrokePathInstanced(GLsizei numPaths,
                                    PathElementType pathNameType,
                                    const void *paths, GLuint pathBase,
                                    GLint reference, GLuint mask,
                                    PathTransformType transformType,
                                    const GLfloat *transformValues) const;
    void stencilStrokePath(GLuint path, GLint reference, GLuint mask) const;
    void stencilThenCoverFillPathInstanced(GLsizei numPaths, GLenum pathNameType,
                                           const void *paths, GLuint pathBase,
                                           GLenum fillMode, GLuint mask,
                                           GLenum coverMode,
                                           GLenum transformType,
                                           const GLfloat *transformValues) const;
    void stencilThenCoverFillPath(GLuint path, GLenum fillMode, GLuint mask,
                                  GLenum coverMode) const;
    void stencilThenCoverStrokePathInstanced(GLsizei numPaths,
                                             GLenum pathNameType,
                                             const void *paths, GLuint pathBase,
                                             GLint reference, GLuint mask,
                                             GLenum coverMode,
                                             GLenum transformType,
                                             const GLfloat *transformValues) const;
    void stencilThenCoverStrokePath(GLuint path, GLint reference, GLuint mask,
                                    GLenum coverMode) const;
    void transformPath(GLuint resultPath, GLuint srcPath,
                       PathTransformType transformType,
                       const GLfloat *transformValues) const;
    void weightPaths(GLuint resultPath, GLsizei numPaths, const GLuint *paths,
                     const GLfloat *weights) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPathRendering _api;
};

// Manages the entry points for the GL_NV_pixel_data_range extension API.
class NVPixelDataRangeAPI : public BaseExtension
{
public:
    // Construction
    NVPixelDataRangeAPI();

    // Accessors
    const NVPixelDataRange &getRawAPI() const;

    // Operations
    void flushPixelDataRange(PixelDataRangeTargetNV target) const;
    void pixelDataRange(PixelDataRangeTargetNV target, GLsizei length,
                        const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPixelDataRange _api;
};

// Manages the entry points for the GL_NV_point_sprite extension API.
class NVPointSpriteAPI : public BaseExtension
{
public:
    // Construction
    NVPointSpriteAPI();

    // Accessors
    const NVPointSprite &getRawAPI() const;

    // Operations
    void pointParameterI(PointParameterNameARB pname, GLint param) const;
    void pointParameterIV(PointParameterNameARB pname, const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPointSprite _api;
};

// Manages the entry points for the GL_NV_present_video extension API.
class NVPresentVideoAPI : public BaseExtension
{
public:
    // Construction
    NVPresentVideoAPI();

    // Accessors
    const NVPresentVideo &getRawAPI() const;

    // Operations
    void getVideoI64V(GLuint video_slot, GLenum pname, GLint64EXT *params) const;
    void getVideoIV(GLuint video_slot, GLenum pname, GLint *params) const;
    void getVideoUI64(GLuint video_slot, GLenum pname, GLuint64EXT *params) const;
    void getVideoUIV(GLuint video_slot, GLenum pname, GLuint *params) const;
    void presentFrameDualFill(GLuint video_slot, GLuint64EXT minPresentTime,
                              GLuint beginPresentTimeId,
                              GLuint presentDurationId, GLenum type,
                              GLenum target0, GLuint fill0, GLenum target1,
                              GLuint fill1, GLenum target2, GLuint fill2,
                              GLenum target3, GLuint fill3) const;
    void presentFrameKeyed(GLuint video_slot, GLuint64EXT minPresentTime,
                           GLuint beginPresentTimeId, GLuint presentDurationId,
                           GLenum type, GLenum target0, GLuint fill0,
                           GLuint key0, GLenum target1, GLuint fill1,
                           GLuint key1) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPresentVideo _api;
};

// Manages the entry points for the GL_NV_primitive_restart extension API.
class NVPrimitiveRestartAPI : public BaseExtension
{
public:
    // Construction
    NVPrimitiveRestartAPI();

    // Accessors
    const NVPrimitiveRestart &getRawAPI() const;

    // Operations
    void primitiveRestartIndex(GLuint index) const;
    void primitiveRestart() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPrimitiveRestart _api;
};

// Manages the entry points for the GL_NV_query_resource extension API.
class NVQueryResourceAPI : public BaseExtension
{
public:
    // Construction
    NVQueryResourceAPI();

    // Accessors
    const NVQueryResource &getRawAPI() const;

    // Operations
    GLint queryResource(GLenum queryType, GLint tagId, GLuint count,
                        GLint *buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVQueryResource _api;
};

// Manages the entry points for the GL_NV_query_resource_tag extension API.
class NVQueryResourceTagAPI : public BaseExtension
{
public:
    // Construction
    NVQueryResourceTagAPI();

    // Accessors
    const NVQueryResourceTag &getRawAPI() const;

    // Operations
    void deleteQueryResourceTag(GLsizei n, const GLint *tagIds) const;
    void genQueryResourceTag(GLsizei n, GLint *tagIds) const;
    void queryResourceTag(GLint tagId, const GLchar *tagString) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVQueryResourceTag _api;
};

// Manages the entry points for the GL_NV_register_combiners extension API.
class NVRegisterCombinersAPI : public BaseExtension
{
public:
    // Construction
    NVRegisterCombinersAPI();

    // Accessors
    const NVRegisterCombiners &getRawAPI() const;

    // Operations
    void combinerInput(CombinerStageNV stage, CombinerPortionNV portion,
                       CombinerVariableNV variable, CombinerRegisterNV input,
                       CombinerMappingNV mapping,
                       CombinerComponentUsageNV componentUsage) const;
    void combinerOutput(CombinerStageNV stage, CombinerPortionNV portion,
                        CombinerRegisterNV abOutput, CombinerRegisterNV cdOutput,
                        CombinerRegisterNV sumOutput, CombinerScaleNV scale,
                        CombinerBiasNV bias, Boolean abDotProduct,
                        Boolean cdDotProduct, Boolean muxSum) const;
    void combinerParameterF(CombinerParameterNV pname, GLfloat param) const;
    void combinerParameterFV(CombinerParameterNV pname, const GLfloat *params) const;
    void combinerParameterI(CombinerParameterNV pname, GLint param) const;
    void combinerParameterIV(CombinerParameterNV pname, const GLint *params) const;
    void finalCombinerInput(CombinerVariableNV variable,
                            CombinerRegisterNV input, CombinerMappingNV mapping,
                            CombinerComponentUsageNV componentUsage) const;
    void getCombinerInputParameterFV(CombinerStageNV stage,
                                     CombinerPortionNV portion,
                                     CombinerVariableNV variable,
                                     CombinerParameterNV pname, GLfloat *params) const;
    void getCombinerInputParameterIV(CombinerStageNV stage,
                                     CombinerPortionNV portion,
                                     CombinerVariableNV variable,
                                     CombinerParameterNV pname, GLint *params) const;
    void getCombinerOutputParameterFV(CombinerStageNV stage,
                                      CombinerPortionNV portion,
                                      CombinerParameterNV pname, GLfloat *params) const;
    void getCombinerOutputParameterIV(CombinerStageNV stage,
                                      CombinerPortionNV portion,
                                      CombinerParameterNV pname, GLint *params) const;
    void getFinalCombinerInputParameterFV(CombinerVariableNV variable,
                                          CombinerParameterNV pname,
                                          GLfloat *params) const;
    void getFinalCombinerInputParameterIV(CombinerVariableNV variable,
                                          CombinerParameterNV pname,
                                          GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVRegisterCombiners _api;
};

// Manages the entry points for the GL_NV_register_combiners2 extension API.
class NVRegisterCOMBINERS2API : public BaseExtension
{
public:
    // Construction
    NVRegisterCOMBINERS2API();

    // Accessors
    const NVRegisterCOMBINERS2 &getRawAPI() const;

    // Operations
    void combinerStageParameterFV(CombinerStageNV stage,
                                  CombinerParameterNV pname,
                                  const GLfloat *params) const;
    void getCombinerStageParameterFV(CombinerStageNV stage,
                                     CombinerParameterNV pname, GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVRegisterCOMBINERS2 _api;
};

// Manages the entry points for the GL_NV_sample_locations extension API.
class NVSampleLocationsAPI : public BaseExtension
{
public:
    // Construction
    NVSampleLocationsAPI();

    // Accessors
    const NVSampleLocations &getRawAPI() const;

    // Operations
    void framebufferSampleLocationsFV(FrameBufferTarget target, GLuint start,
                                      GLsizei count, const GLfloat *v) const;
    void namedFramebufferSampleLocationsFV(FrameBufferName framebuffer,
                                           GLuint start, GLsizei count,
                                           const GLfloat *v) const;
    void resolveDepthValues() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVSampleLocations _api;
};

// Manages the entry points for the GL_NV_scissor_exclusive extension API.
class NVScissorExclusiveAPI : public BaseExtension
{
public:
    // Construction
    NVScissorExclusiveAPI();

    // Accessors
    const NVScissorExclusive &getRawAPI() const;

    // Operations
    void scissorExclusiveArrayV(GLuint first, GLsizei count, const GLint *v) const;
    void scissorExclusive(GLint x, GLint y, GLsizei width, GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVScissorExclusive _api;
};

// Manages the entry points for the GL_NV_shader_buffer_load extension API.
class NVShaderBufferLoadAPI : public BaseExtension
{
public:
    // Construction
    NVShaderBufferLoadAPI();

    // Accessors
    const NVShaderBufferLoad &getRawAPI() const;

    // Operations
    void getBufferParameterUI64(BufferTarget target, GLenum pname,
                                GLuint64EXT *params) const;
    void getIntegerUI64(GLenum value, GLuint64EXT *result) const;
    void getNamedBufferParameterUI64(BufferName buffer, BufferPName pname,
                                     GLuint64EXT *params) const;
    Boolean isBufferResident(GLenum target) const;
    Boolean isNamedBufferResident(BufferName buffer) const;
    void makeBufferNonResident(GLenum target) const;
    void makeBufferResident(GLenum target, GLenum access) const;
    void makeNamedBufferNonResident(BufferName buffer) const;
    void makeNamedBufferResident(BufferName buffer, GLenum access) const;
    void programUniformUI64(ProgramName program, GLint location,
                            GLuint64EXT value) const;
    void programUniformUI64(ProgramName program, GLint location, GLsizei count,
                            const GLuint64EXT *value) const;
    void uniformUI64(GLint location, GLuint64EXT value) const;
    void uniformUI64(GLint location, GLsizei count, const GLuint64EXT *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVShaderBufferLoad _api;
};

// Manages the entry points for the GL_NV_shading_rate_image extension API.
class NVShadingRateImageAPI : public BaseExtension
{
public:
    // Construction
    NVShadingRateImageAPI();

    // Accessors
    const NVShadingRateImage &getRawAPI() const;

    // Operations
    void bindShadingRateImage(TextureName texture) const;
    void getShadingRateImagePalette(GLuint viewport, GLuint entry, GLenum *rate) const;
    void getShadingRateSampleLocationIV(GLenum rate, GLuint samples,
                                        GLuint index, GLint *location) const;
    void shadingRateImageBarrier(Boolean synchronize) const;
    void shadingRateImagePalette(GLuint viewport, GLuint first, GLsizei count,
                                 const GLenum *rates) const;
    void shadingRateSampleOrderCustom(GLenum rate, GLuint samples,
                                      const GLint *locations) const;
    void shadingRateSampleOrder(GLenum order) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVShadingRateImage _api;
};

// Manages the entry points for the GL_NV_texture_barrier extension API.
class NVTextureBarrierAPI : public BaseExtension
{
public:
    // Construction
    NVTextureBarrierAPI();

    // Accessors
    const NVTextureBarrier &getRawAPI() const;

    // Operations
    void textureBarrier() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVTextureBarrier _api;
};

// Manages the entry points for the GL_NV_texture_multisample extension API.
class NVTextureMultisampleAPI : public BaseExtension
{
public:
    // Construction
    NVTextureMultisampleAPI();

    // Accessors
    const NVTextureMultisample &getRawAPI() const;

    // Operations
    void texImage2DMultisampleCoverage(TextureTarget target,
                                       GLsizei coverageSamples,
                                       GLsizei colorSamples,
                                       InternalFormat internalFormat,
                                       GLsizei width, GLsizei height,
                                       Boolean fixedSampleLocations) const;
    void texImage3DMultisampleCoverage(TextureTarget target,
                                       GLsizei coverageSamples,
                                       GLsizei colorSamples,
                                       InternalFormat internalFormat,
                                       GLsizei width, GLsizei height,
                                       GLsizei depth,
                                       Boolean fixedSampleLocations) const;
    void textureImage2DMultisampleCoverage(TextureName texture,
                                           TextureTarget target,
                                           GLsizei coverageSamples,
                                           GLsizei colorSamples,
                                           InternalFormat internalFormat,
                                           GLsizei width, GLsizei height,
                                           Boolean fixedSampleLocations) const;
    void textureImage2DMultisample(TextureName texture, TextureTarget target,
                                   GLsizei samples,
                                   InternalFormat internalFormat, GLsizei width,
                                   GLsizei height, Boolean fixedSampleLocations) const;
    void textureImage3DMultisampleCoverage(TextureName texture,
                                           TextureTarget target,
                                           GLsizei coverageSamples,
                                           GLsizei colorSamples,
                                           InternalFormat internalFormat,
                                           GLsizei width, GLsizei height,
                                           GLsizei depth,
                                           Boolean fixedSampleLocations) const;
    void textureImage3DMultisample(TextureName texture, TextureTarget target,
                                   GLsizei samples,
                                   InternalFormat internalFormat, GLsizei width,
                                   GLsizei height, GLsizei depth,
                                   Boolean fixedSampleLocations) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVTextureMultisample _api;
};

// Manages the entry points for the GL_NV_timeline_semaphore extension API.
class NVTimelineSemaphoreAPI : public BaseExtension
{
public:
    // Construction
    NVTimelineSemaphoreAPI();

    // Accessors
    const NVTimelineSemaphore &getRawAPI() const;

    // Operations
    void createSemaphores(GLsizei n, GLuint *semaphores) const;
    void getSemaphoreParameterIV(GLuint semaphore, SemaphoreParameterName pname,
                                 GLint *params) const;
    void semaphoreParameterIV(GLuint semaphore, SemaphoreParameterName pname,
                              const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVTimelineSemaphore _api;
};

// Manages the entry points for the GL_NV_transform_feedback extension API.
class NVTransformFeedbackAPI : public BaseExtension
{
public:
    // Construction
    NVTransformFeedbackAPI();

    // Accessors
    const NVTransformFeedback &getRawAPI() const;

    // Operations
    void activeVarying(ProgramName program, const GLchar *name) const;
    void beginTransformFeedback(PrimitiveType primitiveMode) const;
    void bindBufferBase(BufferTarget target, GLuint index, BufferName buffer) const;
    void bindBufferOffset(BufferTarget target, GLuint index,
                          BufferName buffer, GLintptr offset) const;
    void bindBufferRange(BufferTarget target, GLuint index, BufferName buffer,
                         GLintptr offset, GLsizeiptr size) const;
    void endTransformFeedback() const;
    void getActiveVarying(ProgramName program, GLuint index, GLsizei bufSize,
                          GLsizei *length, GLsizei *size, GLenum *type,
                          GLchar *name) const;
    void getTransformFeedbackVarying(ProgramName program, GLuint index,
                                     GLint *location) const;
    GLint getVaryingLocation(ProgramName program, const GLchar *name) const;
    void transformFeedbackAttribs(GLsizei count, const GLint *attribs,
                                  GLenum bufferMode) const;
    void transformFeedbackStreamAttribs(GLsizei count, const GLint *attribs,
                                        GLsizei nbuffers,
                                        const GLint *bufstreams,
                                        GLenum bufferMode) const;
    void transformFeedbackVaryings(ProgramName program, GLsizei count,
                                   const GLint *locations, GLenum bufferMode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVTransformFeedback _api;
};

// Manages the entry points for the GL_NV_transform_feedback2 extension API.
class NVTransformFeedback2API : public BaseExtension
{
public:
    // Construction
    NVTransformFeedback2API();

    // Accessors
    const NVTransformFeedback2 &getRawAPI() const;

    // Operations
    void bindTransformFeedback(BufferTarget target, TransformFeedbackName id) const;
    void deleteTransformFeedbacks(GLsizei n, const TransformFeedbackName *ids) const;
    void drawTransformFeedback(PrimitiveType mode, TransformFeedbackName id) const;
    void genTransformFeedbacks(GLsizei n, TransformFeedbackName *ids) const;
    Boolean isTransformFeedback(TransformFeedbackName id) const;
    void pauseTransformFeedback() const;
    void resumeTransformFeedback() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVTransformFeedback2 _api;
};

// Manages the entry points for the GL_NV_vdpau_interop extension API.
class NVVdpauInteropAPI : public BaseExtension
{
public:
    // Construction
    NVVdpauInteropAPI();

    // Accessors
    const NVVdpauInterop &getRawAPI() const;

    // Operations
    void vdpauFini() const;
    void vdpauGetSurfaceIV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei count,
                           GLsizei *length, GLint *values) const;
    void vdpauInit(const void *vdpDevice, const void *getProcAddress) const;
    Boolean vdpauIsSurface(GLvdpauSurfaceNV surface) const;
    void vdpauMapSurfaces(GLsizei numSurfaces, const GLvdpauSurfaceNV *surfaces) const;
    GLvdpauSurfaceNV vdpauRegisterOutputSurface(const void *vdpSurface,
                                                GLenum target,
                                                GLsizei numTextureNames,
                                                const GLuint *textureNames) const;
    GLvdpauSurfaceNV vdpauRegisterVideoSurface(const void *vdpSurface,
                                               GLenum target,
                                               GLsizei numTextureNames,
                                               const GLuint *textureNames) const;
    void vdpauSurfaceAccess(GLvdpauSurfaceNV surface, GLenum access) const;
    void vdpauUnmapSurfaces(GLsizei numSurface, const GLvdpauSurfaceNV *surfaces) const;
    void vdpauUnregisterSurface(GLvdpauSurfaceNV surface) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVdpauInterop _api;
};

// Manages the entry points for the GL_NV_vdpau_interop2 extension API.
class NVVdpauINTEROP2API : public BaseExtension
{
public:
    // Construction
    NVVdpauINTEROP2API();

    // Accessors
    const NVVdpauINTEROP2 &getRawAPI() const;

    // Operations
    GLvdpauSurfaceNV vdpauRegisterVideoSurfaceWithPictureStructure(const void *vdpSurface,
                                                                   GLenum target,
                                                                   GLsizei numTextureNames,
                                                                   const GLuint *textureNames,
                                                                   Boolean isFrameStructure) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVdpauINTEROP2 _api;
};

// Manages the entry points for the GL_NV_vertex_array_range extension API.
class NVVertexArrayRangeAPI : public BaseExtension
{
public:
    // Construction
    NVVertexArrayRangeAPI();

    // Accessors
    const NVVertexArrayRange &getRawAPI() const;

    // Operations
    void flushVertexArrayRange() const;
    void vertexArrayRange(GLsizei length, const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVertexArrayRange _api;
};

// Manages the entry points for the GL_NV_vertex_attrib_integer_64bit extension API.
class NVVertexAttribInteger64BITAPI : public BaseExtension
{
public:
    // Construction
    NVVertexAttribInteger64BITAPI();

    // Accessors
    const NVVertexAttribInteger64BIT &getRawAPI() const;

    // Operations
    void getVertexAttribLI64V(GLuint index, VertexAttribEnum pname,
                              GLint64EXT *params) const;
    void getVertexAttribLUI64(GLuint index, VertexAttribEnum pname,
                              GLuint64EXT *params) const;
    void vertexAttribL1I64(GLuint index, GLint64EXT x) const;
    void vertexAttribL1I64V(GLuint index, const GLint64EXT *v) const;
    void vertexAttribL1UI64(GLuint index, GLuint64EXT x) const;
    void vertexAttribL1UI64(GLuint index, const GLuint64EXT *v) const;
    void vertexAttribL2I64(GLuint index, GLint64EXT x, GLint64EXT y) const;
    void vertexAttribL2I64V(GLuint index, const GLint64EXT *v) const;
    void vertexAttribL2UI64(GLuint index, GLuint64EXT x, GLuint64EXT y) const;
    void vertexAttribL2UI64(GLuint index, const GLuint64EXT *v) const;
    void vertexAttribL3I64(GLuint index, GLint64EXT x, GLint64EXT y,
                           GLint64EXT z) const;
    void vertexAttribL3I64V(GLuint index, const GLint64EXT *v) const;
    void vertexAttribL3UI64(GLuint index, GLuint64EXT x, GLuint64EXT y,
                            GLuint64EXT z) const;
    void vertexAttribL3UI64(GLuint index, const GLuint64EXT *v) const;
    void vertexAttribL4I64(GLuint index, GLint64EXT x, GLint64EXT y,
                           GLint64EXT z, GLint64EXT w) const;
    void vertexAttribL4I64V(GLuint index, const GLint64EXT *v) const;
    void vertexAttribL4UI64(GLuint index, GLuint64EXT x, GLuint64EXT y,
                            GLuint64EXT z, GLuint64EXT w) const;
    void vertexAttribL4UI64(GLuint index, const GLuint64EXT *v) const;
    void vertexAttribLFormat(GLuint index, GLint size, VertexAttribLType type,
                             GLsizei stride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVertexAttribInteger64BIT _api;
};

// Manages the entry points for the GL_NV_vertex_buffer_unified_memory extension API.
class NVVertexBufferUnifiedMemoryAPI : public BaseExtension
{
public:
    // Construction
    NVVertexBufferUnifiedMemoryAPI();

    // Accessors
    const NVVertexBufferUnifiedMemory &getRawAPI() const;

    // Operations
    void bufferAddressRange(GLenum pname, GLuint index, GLuint64EXT address,
                            GLsizeiptr length) const;
    void colorFormat(GLint size, GLenum type, GLsizei stride) const;
    void edgeFlagFormat(GLsizei stride) const;
    void fogCoordFormat(GLenum type, GLsizei stride) const;
    void getIntegerUI64(GLenum value, GLuint index, GLuint64EXT *result) const;
    void indexFormat(GLenum type, GLsizei stride) const;
    void normalFormat(GLenum type, GLsizei stride) const;
    void secondaryColorFormat(GLint size, ColorPointerType type, GLsizei stride) const;
    void texCoordFormat(GLint size, GLenum type, GLsizei stride) const;
    void vertexAttribFormat(GLuint index, GLint size, VertexAttribType type,
                            Boolean normalized, GLsizei stride) const;
    void vertexAttribIFormat(GLuint index, GLint size, VertexAttribIType type,
                             GLsizei stride) const;
    void vertexFormat(GLint size, VertexPointerType type, GLsizei stride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVertexBufferUnifiedMemory _api;
};

// Manages the entry points for the GL_NV_vertex_program extension API.
class NVVertexProgramAPI : public BaseExtension
{
public:
    // Construction
    NVVertexProgramAPI();

    // Accessors
    const NVVertexProgram &getRawAPI() const;

    // Operations
    Boolean areProgramsResident(GLsizei n, const ProgramName *programs,
                                Boolean *residences) const;
    void bindProgram(VertexAttribEnumNV target, ProgramName id) const;
    void deletePrograms(GLsizei n, const ProgramName *programs) const;
    void executeProgram(VertexAttribEnumNV target, GLuint id,
                        const GLfloat *params) const;
    void genPrograms(GLsizei n, ProgramName *programs) const;
    void getProgramParameterDV(VertexAttribEnumNV target, GLuint index,
                               VertexAttribEnumNV pname, GLdouble *params) const;
    void getProgramParameterFV(VertexAttribEnumNV target, GLuint index,
                               VertexAttribEnumNV pname, GLfloat *params) const;
    void getProgramString(ProgramName id, VertexAttribEnumNV pname,
                          GLubyte *program) const;
    void getProgramIV(ProgramName id, VertexAttribEnumNV pname, GLint *params) const;
    void getTrackMatrixIV(VertexAttribEnumNV target, GLuint address,
                          VertexAttribEnumNV pname, GLint *params) const;
    void getVertexAttribPointerV(GLuint index, VertexAttribEnumNV pname,
                                 void **pointer) const;
    void getVertexAttribDV(GLuint index, VertexAttribEnumNV pname,
                           GLdouble *params) const;
    void getVertexAttribFV(GLuint index, VertexAttribEnumNV pname,
                           GLfloat *params) const;
    void getVertexAttribIV(GLuint index, VertexAttribEnumNV pname, GLint *params) const;
    Boolean isProgram(ProgramName id) const;
    void loadProgram(VertexAttribEnumNV target, GLuint id, GLsizei len,
                     const GLubyte *program) const;
    void programParameter4D(VertexAttribEnumNV target, GLuint index, GLdouble x,
                            GLdouble y, GLdouble z, GLdouble w) const;
    void programParameter4DV(VertexAttribEnumNV target, GLuint index,
                             const GLdouble *v) const;
    void programParameter4F(VertexAttribEnumNV target, GLuint index, GLfloat x,
                            GLfloat y, GLfloat z, GLfloat w) const;
    void programParameter4FV(VertexAttribEnumNV target, GLuint index,
                             const GLfloat *v) const;
    void programParameters4DV(VertexAttribEnumNV target, GLuint index,
                              GLsizei count, const GLdouble *v) const;
    void programParameters4FV(VertexAttribEnumNV target, GLuint index,
                              GLsizei count, const GLfloat *v) const;
    void requestResidentPrograms(GLsizei n, const ProgramName *programs) const;
    void trackMatrix(VertexAttribEnumNV target, GLuint address,
                     VertexAttribEnumNV matrix, VertexAttribEnumNV transform) const;
    void vertexAttrib1D(GLuint index, GLdouble x) const;
    void vertexAttrib1DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib1F(GLuint index, GLfloat x) const;
    void vertexAttrib1FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib1S(GLuint index, GLshort x) const;
    void vertexAttrib1SV(GLuint index, const GLshort *v) const;
    void vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const;
    void vertexAttrib2DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const;
    void vertexAttrib2FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib2S(GLuint index, GLshort x, GLshort y) const;
    void vertexAttrib2SV(GLuint index, const GLshort *v) const;
    void vertexAttrib3D(GLuint index, GLdouble x, GLdouble y, GLdouble z) const;
    void vertexAttrib3DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib3F(GLuint index, GLfloat x, GLfloat y, GLfloat z) const;
    void vertexAttrib3FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib3S(GLuint index, GLshort x, GLshort y, GLshort z) const;
    void vertexAttrib3SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4D(GLuint index, GLdouble x, GLdouble y, GLdouble z,
                        GLdouble w) const;
    void vertexAttrib4DV(GLuint index, const GLdouble *v) const;
    void vertexAttrib4F(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void vertexAttrib4FV(GLuint index, const GLfloat *v) const;
    void vertexAttrib4S(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const;
    void vertexAttrib4SV(GLuint index, const GLshort *v) const;
    void vertexAttrib4UB(GLuint index, GLubyte x, GLubyte y, GLubyte z,
                         GLubyte w) const;
    void vertexAttrib4UBV(GLuint index, const GLubyte *v) const;
    void vertexAttribPointer(GLuint index, GLint fsize, VertexAttribEnumNV type,
                             GLsizei stride, const void *pointer) const;
    void vertexAttribs1DV(GLuint index, GLsizei count, const GLdouble *v) const;
    void vertexAttribs1FV(GLuint index, GLsizei count, const GLfloat *v) const;
    void vertexAttribs1SV(GLuint index, GLsizei count, const GLshort *v) const;
    void vertexAttribs2DV(GLuint index, GLsizei count, const GLdouble *v) const;
    void vertexAttribs2FV(GLuint index, GLsizei count, const GLfloat *v) const;
    void vertexAttribs2SV(GLuint index, GLsizei count, const GLshort *v) const;
    void vertexAttribs3DV(GLuint index, GLsizei count, const GLdouble *v) const;
    void vertexAttribs3FV(GLuint index, GLsizei count, const GLfloat *v) const;
    void vertexAttribs3SV(GLuint index, GLsizei count, const GLshort *v) const;
    void vertexAttribs4DV(GLuint index, GLsizei count, const GLdouble *v) const;
    void vertexAttribs4FV(GLuint index, GLsizei count, const GLfloat *v) const;
    void vertexAttribs4SV(GLuint index, GLsizei count, const GLshort *v) const;
    void vertexAttribs4UBV(GLuint index, GLsizei count, const GLubyte *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVertexProgram _api;
};

// Manages the entry points for the GL_NV_video_capture extension API.
class NVVideoCaptureAPI : public BaseExtension
{
public:
    // Construction
    NVVideoCaptureAPI();

    // Accessors
    const NVVideoCapture &getRawAPI() const;

    // Operations
    void beginVideoCapture(GLuint video_capture_slot) const;
    void bindVideoCaptureStreamBuffer(GLuint video_capture_slot, GLuint stream,
                                      GLenum frame_region, GLintptrARB offset) const;
    void bindVideoCaptureStreamTexture(GLuint video_capture_slot, GLuint stream,
                                       GLenum frame_region, GLenum target,
                                       TextureName texture) const;
    void endVideoCapture(GLuint video_capture_slot) const;
    void getVideoCaptureStreamDV(GLuint video_capture_slot, GLuint stream,
                                 GLenum pname, GLdouble *params) const;
    void getVideoCaptureStreamFV(GLuint video_capture_slot, GLuint stream,
                                 GLenum pname, GLfloat *params) const;
    void getVideoCaptureStreamIV(GLuint video_capture_slot, GLuint stream,
                                 GLenum pname, GLint *params) const;
    void getVideoCaptureIV(GLuint video_capture_slot, GLenum pname,
                           GLint *params) const;
    GLenum videoCapture(GLuint video_capture_slot, GLuint *sequence_num,
                        GLuint64EXT *capture_time) const;
    void videoCaptureStreamParameterDV(GLuint video_capture_slot, GLuint stream,
                                       GLenum pname, const GLdouble *params) const;
    void videoCaptureStreamParameterFV(GLuint video_capture_slot, GLuint stream,
                                       GLenum pname, const GLfloat *params) const;
    void videoCaptureStreamParameterIV(GLuint video_capture_slot, GLuint stream,
                                       GLenum pname, const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVideoCapture _api;
};

// Manages the entry points for the GL_NV_viewport_swizzle extension API.
class NVViewportSwizzleAPI : public BaseExtension
{
public:
    // Construction
    NVViewportSwizzleAPI();

    // Accessors
    const NVViewportSwizzle &getRawAPI() const;

    // Operations
    void viewportSwizzle(GLuint index, GLenum swizzlex, GLenum swizzley,
                         GLenum swizzlez, GLenum swizzlew) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVViewportSwizzle _api;
};

} // namespace gl

#ifdef _WIN32
namespace wgl {

// Manages the entry points for the WGL_NV_DX_interop extension API.
class NVDxInteropAPI : public gl::BaseExtension
{
public:
    // Construction
    NVDxInteropAPI();

    // Accessors
    const NVDxInterop &getRawAPI() const;

    // Operations
    BOOL dxCloseDevice(HANDLE hDevice) const;
    BOOL dxLockObjects(HANDLE hDevice, GLint count, HANDLE *hObjects) const;
    BOOL dxObjectAccess(HANDLE hObject, GLenum access) const;
    HANDLE dxOpenDevice(void *dxDevice) const;
    HANDLE dxRegisterObject(HANDLE hDevice, void *dxObject, GLuint name,
                            GLenum type, GLenum access) const;
    BOOL dxSetResourceShareHandle(void *dxObject, HANDLE shareHandle) const;
    BOOL dxUnlockObjects(HANDLE hDevice, GLint count, HANDLE *hObjects) const;
    BOOL dxUnregisterObject(HANDLE hDevice, HANDLE hObject) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDxInterop _api;
};

// Manages the entry points for the WGL_NV_copy_image extension API.
class NVCopyImageAPI : public gl::BaseExtension
{
public:
    // Construction
    NVCopyImageAPI();

    // Accessors
    const NVCopyImage &getRawAPI() const;

    // Operations
    BOOL copyImageSubData(HGLRC hSrcRC, GLuint srcName, GLenum srcTarget,
                          GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ,
                          HGLRC hDstRC, GLuint dstName, GLenum dstTarget,
                          GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ,
                          GLsizei width, GLsizei height, GLsizei depth) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVCopyImage _api;
};

// Manages the entry points for the WGL_NV_delay_before_swap extension API.
class NVDelayBeforeSwapAPI : public gl::BaseExtension
{
public:
    // Construction
    NVDelayBeforeSwapAPI();

    // Accessors
    const NVDelayBeforeSwap &getRawAPI() const;

    // Operations
    BOOL delayBeforeSwap(HDC hDC, GLfloat seconds) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDelayBeforeSwap _api;
};

// Manages the entry points for the WGL_NV_gpu_affinity extension API.
class NVGPUAffinityAPI : public gl::BaseExtension
{
public:
    // Construction
    NVGPUAffinityAPI();

    // Accessors
    const NVGPUAffinity &getRawAPI() const;

    // Operations
    HDC createAffinityDC(const HGPUNV *phGpuList) const;
    BOOL deleteDC(HDC hdc) const;
    BOOL enumGpuDevices(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice) const;
    BOOL enumGpusFromAffinityDC(HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu) const;
    BOOL enumGpus(UINT iGpuIndex, HGPUNV *phGpu) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVGPUAffinity _api;
};

// Manages the entry points for the WGL_NV_present_video extension API.
class NVPresentVideoAPI : public gl::BaseExtension
{
public:
    // Construction
    NVPresentVideoAPI();

    // Accessors
    const NVPresentVideo &getRawAPI() const;

    // Operations
    BOOL bindVideoDevice(HDC hDc, unsigned int uVideoSlot,
                         HVIDEOOUTPUTDEVICENV hVideoDevice,
                         const int *piAttribList) const;
    int enumerateVideoDevices(HDC hDc, HVIDEOOUTPUTDEVICENV *phDeviceList) const;
    BOOL queryCurrentContext(int iAttribute, int *piValue) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPresentVideo _api;
};

// Manages the entry points for the WGL_NV_swap_group extension API.
class NVSwapGroupAPI : public gl::BaseExtension
{
public:
    // Construction
    NVSwapGroupAPI();

    // Accessors
    const NVSwapGroup &getRawAPI() const;

    // Operations
    BOOL bindSwapBarrier(GLuint group, GLuint barrier) const;
    BOOL joinSwapGroup(HDC hDC, GLuint group) const;
    BOOL queryFrameCount(HDC hDC, GLuint *count) const;
    BOOL queryMaxSwapGroups(HDC hDC, GLuint *maxGroups, GLuint *maxBarriers) const;
    BOOL querySwapGroup(HDC hDC, GLuint *group, GLuint *barrier) const;
    BOOL resetFrameCount(HDC hDC) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVSwapGroup _api;
};

// Manages the entry points for the WGL_NV_vertex_array_range extension API.
class NVVertexArrayRangeAPI : public gl::BaseExtension
{
public:
    // Construction
    NVVertexArrayRangeAPI();

    // Accessors
    const NVVertexArrayRange &getRawAPI() const;

    // Operations
    void *allocateMemory(GLsizei size, GLfloat readfreq, GLfloat writefreq,
                         GLfloat priority) const;
    void freeMemory(void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVertexArrayRange _api;
};

// Manages the entry points for the WGL_NV_video_capture extension API.
class NVVideoCaptureAPI : public gl::BaseExtension
{
public:
    // Construction
    NVVideoCaptureAPI();

    // Accessors
    const NVVideoCapture &getRawAPI() const;

    // Operations
    BOOL bindVideoCaptureDevice(UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice) const;
    UINT enumerateVideoCaptureDevices(HDC hDc, HVIDEOINPUTDEVICENV *phDeviceList) const;
    BOOL lockVideoCaptureDevice(HDC hDc, HVIDEOINPUTDEVICENV hDevice) const;
    BOOL queryVideoCaptureDevice(HDC hDc, HVIDEOINPUTDEVICENV hDevice,
                                 int iAttribute, int *piValue) const;
    BOOL releaseVideoCaptureDevice(HDC hDc, HVIDEOINPUTDEVICENV hDevice) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVideoCapture _api;
};

// Manages the entry points for the WGL_NV_video_output extension API.
class NVVideoOutputAPI : public gl::BaseExtension
{
public:
    // Construction
    NVVideoOutputAPI();

    // Accessors
    const NVVideoOutput &getRawAPI() const;

    // Operations
    BOOL bindVideoImage(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer,
                        int iVideoBuffer) const;
    BOOL getVideoDevice(HDC hDC, int numDevices, HPVIDEODEV *hVideoDevice) const;
    BOOL getVideoInfo(HPVIDEODEV hpVideoDevice,
                      unsigned long *pulCounterOutputPbuffer,
                      unsigned long *pulCounterOutputVideo) const;
    BOOL releaseVideoDevice(HPVIDEODEV hVideoDevice) const;
    BOOL releaseVideoImage(HPBUFFERARB hPbuffer, int iVideoBuffer) const;
    BOOL sendPbufferToVideo(HPBUFFERARB hPbuffer, int iBufferType,
                            unsigned long *pulCounterPbuffer, BOOL bBlock) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVideoOutput _api;
};

} // namespace wgl
#endif // ifdef _WIN32


#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_NV_copy_buffer extension API.
class NVCopyBufferAPI : public gl::BaseExtension
{
public:
    // Construction
    NVCopyBufferAPI();

    // Accessors
    const NVCopyBuffer &getRawAPI() const;

    // Operations
    void xCopyBufferSubData(Display *dpy, GLXContext readCtx,
                            GLXContext writeCtx, GLenum readTarget,
                            GLenum writeTarget, GLintptr readOffset,
                            GLintptr writeOffset, GLsizeiptr size) const;
    void xNamedCopyBufferSubData(Display *dpy, GLXContext readCtx,
                                 GLXContext writeCtx, GLuint readBuffer,
                                 GLuint writeBuffer, GLintptr readOffset,
                                 GLintptr writeOffset, GLsizeiptr size) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVCopyBuffer _api;
};

// Manages the entry points for the GLX_NV_copy_image extension API.
class NVCopyImageAPI : public gl::BaseExtension
{
public:
    // Construction
    NVCopyImageAPI();

    // Accessors
    const NVCopyImage &getRawAPI() const;

    // Operations
    void xCopyImageSubData(Display *dpy, GLXContext srcCtx, GLuint srcName,
                           GLenum srcTarget, GLint srcLevel, GLint srcX,
                           GLint srcY, GLint srcZ, GLXContext dstCtx,
                           GLuint dstName, GLenum dstTarget, GLint dstLevel,
                           GLint dstX, GLint dstY, GLint dstZ, GLsizei width,
                           GLsizei height, GLsizei depth) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVCopyImage _api;
};

// Manages the entry points for the GLX_NV_delay_before_swap extension API.
class NVDelayBeforeSwapAPI : public gl::BaseExtension
{
public:
    // Construction
    NVDelayBeforeSwapAPI();

    // Accessors
    const NVDelayBeforeSwap &getRawAPI() const;

    // Operations
    Bool xDelayBeforeSwap(Display *dpy, GLXDrawable drawable, GLfloat seconds) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVDelayBeforeSwap _api;
};

// Manages the entry points for the GLX_NV_present_video extension API.
class NVPresentVideoAPI : public gl::BaseExtension
{
public:
    // Construction
    NVPresentVideoAPI();

    // Accessors
    const NVPresentVideo &getRawAPI() const;

    // Operations
    int xBindVideoDevice(Display *dpy, unsigned int video_slot,
                         unsigned int video_device, const int *attrib_list) const;
    unsigned int *xEnumerateVideoDevices(Display *dpy, int screen,
                                         int *nelements) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVPresentVideo _api;
};

// Manages the entry points for the GLX_NV_swap_group extension API.
class NVSwapGroupAPI : public gl::BaseExtension
{
public:
    // Construction
    NVSwapGroupAPI();

    // Accessors
    const NVSwapGroup &getRawAPI() const;

    // Operations
    Bool xBindSwapBarrier(Display *dpy, GLuint group, GLuint barrier) const;
    Bool xJoinSwapGroup(Display *dpy, GLXDrawable drawable, GLuint group) const;
    Bool xQueryFrameCount(Display *dpy, int screen, GLuint *count) const;
    Bool xQueryMaxSwapGroups(Display *dpy, int screen, GLuint *maxGroups,
                             GLuint *maxBarriers) const;
    Bool xQuerySwapGroup(Display *dpy, GLXDrawable drawable, GLuint *group,
                         GLuint *barrier) const;
    Bool xResetFrameCount(Display *dpy, int screen) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVSwapGroup _api;
};

// Manages the entry points for the GLX_NV_video_capture extension API.
class NVVideoCaptureAPI : public gl::BaseExtension
{
public:
    // Construction
    NVVideoCaptureAPI();

    // Accessors
    const NVVideoCapture &getRawAPI() const;

    // Operations
    int xBindVideoCaptureDevice(Display *dpy, unsigned int video_capture_slot,
                                GLXVideoCaptureDeviceNV device) const;
    GLXVideoCaptureDeviceNV *xEnumerateVideoCaptureDevices(Display *dpy,
                                                           int screen,
                                                           int *nelements) const;
    void xLockVideoCaptureDevice(Display *dpy, GLXVideoCaptureDeviceNV device) const;
    int xQueryVideoCaptureDevice(Display *dpy, GLXVideoCaptureDeviceNV device,
                                 int attribute, int *value) const;
    void xReleaseVideoCaptureDevice(Display *dpy, GLXVideoCaptureDeviceNV device) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVideoCapture _api;
};

// Manages the entry points for the GLX_NV_video_out extension API.
class NVVideoOutAPI : public gl::BaseExtension
{
public:
    // Construction
    NVVideoOutAPI();

    // Accessors
    const NVVideoOut &getRawAPI() const;

    // Operations
    int xBindVideoImage(Display *dpy, GLXVideoDeviceNV VideoDevice,
                        GLXPbuffer pbuf, int iVideoBuffer) const;
    int xGetVideoDevice(Display *dpy, int screen, int numVideoDevices,
                        GLXVideoDeviceNV *pVideoDevice) const;
    int xGetVideoInfo(Display *dpy, int screen, GLXVideoDeviceNV VideoDevice,
                      unsigned long *pulCounterOutputPbuffer,
                      unsigned long *pulCounterOutputVideo) const;
    int xReleaseVideoDevice(Display *dpy, int screen,
                            GLXVideoDeviceNV VideoDevice) const;
    int xReleaseVideoImage(Display *dpy, GLXPbuffer pbuf) const;
    int xSendPbufferToVideo(Display *dpy, GLXPbuffer pbuf, int iBufferType,
                            unsigned long *pulCounterPbuffer, GLboolean bBlock) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    NVVideoOut _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
