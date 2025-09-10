//! @file ObjectGL/Extensions/NVidiaCommands.cpp
//! @brief The definition of nVidia-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/NVidiaCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// NVXConditionalRenderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NVX_conditional_render extension.
NVXConditionalRenderAPI::NVXConditionalRenderAPI() :
    BaseExtension("GL_NVX_conditional_render")
{
}

// Grant read-only access to the underlying function pointers.
const NVXConditionalRender &NVXConditionalRenderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NVX_conditional_render entry points.
void NVXConditionalRenderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginConditionalRenderNVX().
void NVXConditionalRenderAPI::beginConditionalRender(GLuint id) const
{
    static const char *fnName = "glBeginConditionalRenderNVX";

    beforeCommand(fnName, _api.glBeginConditionalRender);
    _api.glBeginConditionalRender(id);
    afterCommand(fnName);
}

// Calls glEndConditionalRenderNVX().
void NVXConditionalRenderAPI::endConditionalRender() const
{
    static const char *fnName = "glEndConditionalRenderNVX";

    beforeCommand(fnName, _api.glEndConditionalRender);
    _api.glEndConditionalRender();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVXGPUMULTICAST2API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NVX_gpu_multicast2 extension.
NVXGPUMULTICAST2API::NVXGPUMULTICAST2API() :
    BaseExtension("GL_NVX_gpu_multicast2")
{
}

// Grant read-only access to the underlying function pointers.
const NVXGPUMULTICAST2 &NVXGPUMULTICAST2API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NVX_gpu_multicast2 entry points.
void NVXGPUMULTICAST2API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAsyncCopyBufferSubDataNVX().
GLuint NVXGPUMULTICAST2API::asyncCopyBufferSubData(GLsizei waitSemaphoreCount,
                                                   const GLuint *waitSemaphoreArray,
                                                   const GLuint64 *fenceValueArray,
                                                   GLuint readGpu,
                                                   GLbitfield writeGpuMask,
                                                   BufferName readBuffer,
                                                   BufferName writeBuffer,
                                                   GLintptr readOffset,
                                                   GLintptr writeOffset,
                                                   GLsizeiptr size,
                                                   GLsizei signalSemaphoreCount,
                                                   const GLuint *signalSemaphoreArray,
                                                   const GLuint64 *signalValueArray) const
{
    static const char *fnName = "glAsyncCopyBufferSubDataNVX";

    beforeCommand(fnName, _api.glAsyncCopyBufferSubData);
    GLuint result = _api.glAsyncCopyBufferSubData(waitSemaphoreCount,
                                                  waitSemaphoreArray,
                                                  fenceValueArray, readGpu,
                                                  writeGpuMask, readBuffer.ID,
                                                  writeBuffer.ID, readOffset,
                                                  writeOffset, size,
                                                  signalSemaphoreCount,
                                                  signalSemaphoreArray,
                                                  signalValueArray);
    afterCommand(fnName);

    return result;
}

// Calls glAsyncCopyImageSubDataNVX().
GLuint NVXGPUMULTICAST2API::asyncCopyImageSubData(GLsizei waitSemaphoreCount,
                                                  const GLuint *waitSemaphoreArray,
                                                  const GLuint64 *waitValueArray,
                                                  GLuint srcGpu,
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
                                                  GLsizei srcDepth,
                                                  GLsizei signalSemaphoreCount,
                                                  const GLuint *signalSemaphoreArray,
                                                  const GLuint64 *signalValueArray) const
{
    static const char *fnName = "glAsyncCopyImageSubDataNVX";

    beforeCommand(fnName, _api.glAsyncCopyImageSubData);
    GLuint result = _api.glAsyncCopyImageSubData(waitSemaphoreCount,
                                                 waitSemaphoreArray,
                                                 waitValueArray, srcGpu,
                                                 dstGpuMask, srcName, srcTarget,
                                                 srcLevel, srcX, srcY, srcZ,
                                                 dstName, dstTarget, dstLevel,
                                                 dstX, dstY, dstZ, srcWidth,
                                                 srcHeight, srcDepth,
                                                 signalSemaphoreCount,
                                                 signalSemaphoreArray,
                                                 signalValueArray);
    afterCommand(fnName);

    return result;
}

// Calls glMulticastScissorArrayvNVX().
void NVXGPUMULTICAST2API::multicastScissorArrayV(GLuint gpu, GLuint first,
                                                 GLsizei count, const GLint *v) const
{
    static const char *fnName = "glMulticastScissorArrayvNVX";

    beforeCommand(fnName, _api.glMulticastScissorArrayv);
    _api.glMulticastScissorArrayv(gpu, first, count, v);
    afterCommand(fnName);
}

// Calls glMulticastViewportArrayvNVX().
void NVXGPUMULTICAST2API::multicastViewportArrayV(GLuint gpu, GLuint first,
                                                  GLsizei count,
                                                  const GLfloat *v) const
{
    static const char *fnName = "glMulticastViewportArrayvNVX";

    beforeCommand(fnName, _api.glMulticastViewportArrayv);
    _api.glMulticastViewportArrayv(gpu, first, count, v);
    afterCommand(fnName);
}

// Calls glMulticastViewportPositionWScaleNVX().
void NVXGPUMULTICAST2API::multicastViewportPositionWScale(GLuint gpu,
                                                          GLuint index,
                                                          GLfloat xcoeff,
                                                          GLfloat ycoeff) const
{
    static const char *fnName = "glMulticastViewportPositionWScaleNVX";

    beforeCommand(fnName, _api.glMulticastViewportPositionWScale);
    _api.glMulticastViewportPositionWScale(gpu, index, xcoeff, ycoeff);
    afterCommand(fnName);
}

// Calls glUploadGpuMaskNVX().
void NVXGPUMULTICAST2API::uploadGpuMask(GLbitfield mask) const
{
    static const char *fnName = "glUploadGpuMaskNVX";

    beforeCommand(fnName, _api.glUploadGpuMask);
    _api.glUploadGpuMask(mask);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVXLinkedGPUMulticastAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NVX_linked_gpu_multicast extension.
NVXLinkedGPUMulticastAPI::NVXLinkedGPUMulticastAPI() :
    BaseExtension("GL_NVX_linked_gpu_multicast")
{
}

// Grant read-only access to the underlying function pointers.
const NVXLinkedGPUMulticast &NVXLinkedGPUMulticastAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NVX_linked_gpu_multicast entry points.
void NVXLinkedGPUMulticastAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glLGPUCopyImageSubDataNVX().
void NVXLinkedGPUMulticastAPI::lgpuCopyImageSubData(GLuint sourceGpu,
                                                    GLbitfield destinationGpuMask,
                                                    GLuint srcName,
                                                    GLenum srcTarget,
                                                    GLint srcLevel, GLint srcX,
                                                    GLint srxY, GLint srcZ,
                                                    GLuint dstName,
                                                    GLenum dstTarget,
                                                    GLint dstLevel, GLint dstX,
                                                    GLint dstY, GLint dstZ,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth) const
{
    static const char *fnName = "glLGPUCopyImageSubDataNVX";

    beforeCommand(fnName, _api.glLGPUCopyImageSubData);
    _api.glLGPUCopyImageSubData(sourceGpu, destinationGpuMask, srcName,
                                srcTarget, srcLevel, srcX, srxY, srcZ, dstName,
                                dstTarget, dstLevel, dstX, dstY, dstZ, width,
                                height, depth);
    afterCommand(fnName);
}

// Calls glLGPUInterlockNVX().
void NVXLinkedGPUMulticastAPI::lgpuInterlock() const
{
    static const char *fnName = "glLGPUInterlockNVX";

    beforeCommand(fnName, _api.glLGPUInterlock);
    _api.glLGPUInterlock();
    afterCommand(fnName);
}

// Calls glLGPUNamedBufferSubDataNVX().
void NVXLinkedGPUMulticastAPI::lgpuNamedBufferSubData(GLbitfield gpuMask,
                                                      BufferName buffer,
                                                      GLintptr offset,
                                                      GLsizeiptr size,
                                                      const void *data) const
{
    static const char *fnName = "glLGPUNamedBufferSubDataNVX";

    beforeCommand(fnName, _api.glLGPUNamedBufferSubData);
    _api.glLGPUNamedBufferSubData(gpuMask, buffer.ID, offset, size, data);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVXProgressFenceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NVX_progress_fence extension.
NVXProgressFenceAPI::NVXProgressFenceAPI() :
    BaseExtension("GL_NVX_progress_fence")
{
}

// Grant read-only access to the underlying function pointers.
const NVXProgressFence &NVXProgressFenceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NVX_progress_fence entry points.
void NVXProgressFenceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClientWaitSemaphoreui64NVX().
void NVXProgressFenceAPI::clientWaitSemaphoreUI64(GLsizei fenceObjectCount,
                                                  const GLuint *semaphoreArray,
                                                  const GLuint64 *fenceValueArray) const
{
    static const char *fnName = "glClientWaitSemaphoreui64NVX";

    beforeCommand(fnName, _api.glClientWaitSemaphoreui64);
    _api.glClientWaitSemaphoreui64(fenceObjectCount, semaphoreArray,
                                   fenceValueArray);
    afterCommand(fnName);
}

// Calls glCreateProgressFenceNVX().
GLuint NVXProgressFenceAPI::createProgressFence() const
{
    static const char *fnName = "glCreateProgressFenceNVX";

    beforeCommand(fnName, _api.glCreateProgressFence);
    GLuint result = _api.glCreateProgressFence();
    afterCommand(fnName);

    return result;
}

// Calls glSignalSemaphoreui64NVX().
void NVXProgressFenceAPI::signalSemaphoreUI64(GLuint signalGpu,
                                              GLsizei fenceObjectCount,
                                              const GLuint *semaphoreArray,
                                              const GLuint64 *fenceValueArray) const
{
    static const char *fnName = "glSignalSemaphoreui64NVX";

    beforeCommand(fnName, _api.glSignalSemaphoreui64);
    _api.glSignalSemaphoreui64(signalGpu, fenceObjectCount, semaphoreArray,
                               fenceValueArray);
    afterCommand(fnName);
}

// Calls glWaitSemaphoreui64NVX().
void NVXProgressFenceAPI::waitSemaphoreUI64(GLuint waitGpu,
                                            GLsizei fenceObjectCount,
                                            const GLuint *semaphoreArray,
                                            const GLuint64 *fenceValueArray) const
{
    static const char *fnName = "glWaitSemaphoreui64NVX";

    beforeCommand(fnName, _api.glWaitSemaphoreui64);
    _api.glWaitSemaphoreui64(waitGpu, fenceObjectCount, semaphoreArray,
                             fenceValueArray);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVAlphaToCoverageDitherControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_alpha_to_coverage_dither_control extension.
NVAlphaToCoverageDitherControlAPI::NVAlphaToCoverageDitherControlAPI() :
    BaseExtension("GL_NV_alpha_to_coverage_dither_control")
{
}

// Grant read-only access to the underlying function pointers.
const NVAlphaToCoverageDitherControl &NVAlphaToCoverageDitherControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_alpha_to_coverage_dither_control entry points.
void NVAlphaToCoverageDitherControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAlphaToCoverageDitherControlNV().
void NVAlphaToCoverageDitherControlAPI::alphaToCoverageDitherControl(GLenum mode) const
{
    static const char *fnName = "glAlphaToCoverageDitherControlNV";

    beforeCommand(fnName, _api.glAlphaToCoverageDitherControl);
    _api.glAlphaToCoverageDitherControl(mode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessMultiDrawIndirectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_bindless_multi_draw_indirect extension.
NVBindlessMultiDrawIndirectAPI::NVBindlessMultiDrawIndirectAPI() :
    BaseExtension("GL_NV_bindless_multi_draw_indirect")
{
}

// Grant read-only access to the underlying function pointers.
const NVBindlessMultiDrawIndirect &NVBindlessMultiDrawIndirectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_bindless_multi_draw_indirect entry points.
void NVBindlessMultiDrawIndirectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiDrawArraysIndirectBindlessNV().
void NVBindlessMultiDrawIndirectAPI::multiDrawArraysIndirectBindless(PrimitiveType mode,
                                                                     const void *indirect,
                                                                     GLsizei drawCount,
                                                                     GLsizei stride,
                                                                     GLint vertexBufferCount) const
{
    static const char *fnName = "glMultiDrawArraysIndirectBindlessNV";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirectBindless);
    _api.glMultiDrawArraysIndirectBindless(toScalar(mode), indirect, drawCount,
                                           stride, vertexBufferCount);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirectBindlessNV().
void NVBindlessMultiDrawIndirectAPI::multiDrawElementsIndirectBindless(PrimitiveType mode,
                                                                       DrawElementsType type,
                                                                       const void *indirect,
                                                                       GLsizei drawCount,
                                                                       GLsizei stride,
                                                                       GLint vertexBufferCount) const
{
    static const char *fnName = "glMultiDrawElementsIndirectBindlessNV";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirectBindless);
    _api.glMultiDrawElementsIndirectBindless(toScalar(mode), toScalar(type),
                                             indirect, drawCount, stride,
                                             vertexBufferCount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessMultiDrawIndirectCountAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_bindless_multi_draw_indirect_count extension.
NVBindlessMultiDrawIndirectCountAPI::NVBindlessMultiDrawIndirectCountAPI() :
    BaseExtension("GL_NV_bindless_multi_draw_indirect_count")
{
}

// Grant read-only access to the underlying function pointers.
const NVBindlessMultiDrawIndirectCount &NVBindlessMultiDrawIndirectCountAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_bindless_multi_draw_indirect_count entry points.
void NVBindlessMultiDrawIndirectCountAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiDrawArraysIndirectBindlessCountNV().
void NVBindlessMultiDrawIndirectCountAPI::multiDrawArraysIndirectBindlessCount(PrimitiveType mode,
                                                                               const void *indirect,
                                                                               GLsizei drawCount,
                                                                               GLsizei maxDrawCount,
                                                                               GLsizei stride,
                                                                               GLint vertexBufferCount) const
{
    static const char *fnName = "glMultiDrawArraysIndirectBindlessCountNV";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirectBindlessCount);
    _api.glMultiDrawArraysIndirectBindlessCount(toScalar(mode), indirect,
                                                drawCount, maxDrawCount, stride,
                                                vertexBufferCount);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirectBindlessCountNV().
void NVBindlessMultiDrawIndirectCountAPI::multiDrawElementsIndirectBindlessCount(PrimitiveType mode,
                                                                                 DrawElementsType type,
                                                                                 const void *indirect,
                                                                                 GLsizei drawCount,
                                                                                 GLsizei maxDrawCount,
                                                                                 GLsizei stride,
                                                                                 GLint vertexBufferCount) const
{
    static const char *fnName = "glMultiDrawElementsIndirectBindlessCountNV";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirectBindlessCount);
    _api.glMultiDrawElementsIndirectBindlessCount(toScalar(mode), toScalar(type),
                                                  indirect, drawCount,
                                                  maxDrawCount, stride,
                                                  vertexBufferCount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVBindlessTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_bindless_texture extension.
NVBindlessTextureAPI::NVBindlessTextureAPI() :
    BaseExtension("GL_NV_bindless_texture")
{
}

// Grant read-only access to the underlying function pointers.
const NVBindlessTexture &NVBindlessTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_bindless_texture entry points.
void NVBindlessTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetImageHandleNV().
GLuint64 NVBindlessTextureAPI::getImageHandle(TextureName texture, GLint level,
                                              Boolean layered, GLint layer,
                                              PixelFormat format) const
{
    static const char *fnName = "glGetImageHandleNV";

    beforeCommand(fnName, _api.glGetImageHandle);
    GLuint64 result = _api.glGetImageHandle(texture.ID, level, toScalar(layered),
                                            layer, toScalar(format));
    afterCommand(fnName);

    return result;
}

// Calls glGetTextureHandleNV().
GLuint64 NVBindlessTextureAPI::getTextureHandle(TextureName texture) const
{
    static const char *fnName = "glGetTextureHandleNV";

    beforeCommand(fnName, _api.glGetTextureHandle);
    GLuint64 result = _api.glGetTextureHandle(texture.ID);
    afterCommand(fnName);

    return result;
}

// Calls glGetTextureSamplerHandleNV().
GLuint64 NVBindlessTextureAPI::getTextureSamplerHandle(TextureName texture,
                                                       SamplerName sampler) const
{
    static const char *fnName = "glGetTextureSamplerHandleNV";

    beforeCommand(fnName, _api.glGetTextureSamplerHandle);
    GLuint64 result = _api.glGetTextureSamplerHandle(texture.ID, sampler.ID);
    afterCommand(fnName);

    return result;
}

// Calls glIsImageHandleResidentNV().
Boolean NVBindlessTextureAPI::isImageHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glIsImageHandleResidentNV";

    beforeCommand(fnName, _api.glIsImageHandleResident);
    GLboolean result = _api.glIsImageHandleResident(handle);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsTextureHandleResidentNV().
Boolean NVBindlessTextureAPI::isTextureHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glIsTextureHandleResidentNV";

    beforeCommand(fnName, _api.glIsTextureHandleResident);
    GLboolean result = _api.glIsTextureHandleResident(handle);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMakeImageHandleNonResidentNV().
void NVBindlessTextureAPI::makeImageHandleNonResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeImageHandleNonResidentNV";

    beforeCommand(fnName, _api.glMakeImageHandleNonResident);
    _api.glMakeImageHandleNonResident(handle);
    afterCommand(fnName);
}

// Calls glMakeImageHandleResidentNV().
void NVBindlessTextureAPI::makeImageHandleResident(GLuint64 handle,
                                                   GLenum access) const
{
    static const char *fnName = "glMakeImageHandleResidentNV";

    beforeCommand(fnName, _api.glMakeImageHandleResident);
    _api.glMakeImageHandleResident(handle, access);
    afterCommand(fnName);
}

// Calls glMakeTextureHandleNonResidentNV().
void NVBindlessTextureAPI::makeTextureHandleNonResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeTextureHandleNonResidentNV";

    beforeCommand(fnName, _api.glMakeTextureHandleNonResident);
    _api.glMakeTextureHandleNonResident(handle);
    afterCommand(fnName);
}

// Calls glMakeTextureHandleResidentNV().
void NVBindlessTextureAPI::makeTextureHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeTextureHandleResidentNV";

    beforeCommand(fnName, _api.glMakeTextureHandleResident);
    _api.glMakeTextureHandleResident(handle);
    afterCommand(fnName);
}

// Calls glProgramUniformHandleui64NV().
void NVBindlessTextureAPI::programUniformHandleUI64(ProgramName program,
                                                    GLint location,
                                                    GLuint64 value) const
{
    static const char *fnName = "glProgramUniformHandleui64NV";

    beforeCommand(fnName, _api.glProgramUniformHandleui64);
    _api.glProgramUniformHandleui64(program.ID, location, value);
    afterCommand(fnName);
}

// Calls glProgramUniformHandleui64vNV().
void NVBindlessTextureAPI::programUniformHandleUI64(ProgramName program,
                                                    GLint location,
                                                    GLsizei count,
                                                    const GLuint64 *values) const
{
    static const char *fnName = "glProgramUniformHandleui64vNV";

    beforeCommand(fnName, _api.glProgramUniformHandleui64v);
    _api.glProgramUniformHandleui64v(program.ID, location, count, values);
    afterCommand(fnName);
}

// Calls glUniformHandleui64NV().
void NVBindlessTextureAPI::uniformHandleUI64(GLint location, GLuint64 value) const
{
    static const char *fnName = "glUniformHandleui64NV";

    beforeCommand(fnName, _api.glUniformHandleui64);
    _api.glUniformHandleui64(location, value);
    afterCommand(fnName);
}

// Calls glUniformHandleui64vNV().
void NVBindlessTextureAPI::uniformHandleUI64(GLint location, GLsizei count,
                                             const GLuint64 *value) const
{
    static const char *fnName = "glUniformHandleui64vNV";

    beforeCommand(fnName, _api.glUniformHandleui64v);
    _api.glUniformHandleui64v(location, count, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVBlendEquationAdvancedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_blend_equation_advanced extension.
NVBlendEquationAdvancedAPI::NVBlendEquationAdvancedAPI() :
    BaseExtension("GL_NV_blend_equation_advanced")
{
}

// Grant read-only access to the underlying function pointers.
const NVBlendEquationAdvanced &NVBlendEquationAdvancedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_blend_equation_advanced entry points.
void NVBlendEquationAdvancedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendBarrierNV().
void NVBlendEquationAdvancedAPI::blendBarrier() const
{
    static const char *fnName = "glBlendBarrierNV";

    beforeCommand(fnName, _api.glBlendBarrier);
    _api.glBlendBarrier();
    afterCommand(fnName);
}

// Calls glBlendParameteriNV().
void NVBlendEquationAdvancedAPI::blendParameterI(GLenum pname, GLint value) const
{
    static const char *fnName = "glBlendParameteriNV";

    beforeCommand(fnName, _api.glBlendParameteri);
    _api.glBlendParameteri(pname, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVClipSpaceWScalingAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_clip_space_w_scaling extension.
NVClipSpaceWScalingAPI::NVClipSpaceWScalingAPI() :
    BaseExtension("GL_NV_clip_space_w_scaling")
{
}

// Grant read-only access to the underlying function pointers.
const NVClipSpaceWScaling &NVClipSpaceWScalingAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_clip_space_w_scaling entry points.
void NVClipSpaceWScalingAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glViewportPositionWScaleNV().
void NVClipSpaceWScalingAPI::viewportPositionWScale(GLuint index, GLfloat xcoeff,
                                                    GLfloat ycoeff) const
{
    static const char *fnName = "glViewportPositionWScaleNV";

    beforeCommand(fnName, _api.glViewportPositionWScale);
    _api.glViewportPositionWScale(index, xcoeff, ycoeff);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVCommandListAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_command_list extension.
NVCommandListAPI::NVCommandListAPI() :
    BaseExtension("GL_NV_command_list")
{
}

// Grant read-only access to the underlying function pointers.
const NVCommandList &NVCommandListAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_command_list entry points.
void NVCommandListAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCallCommandListNV().
void NVCommandListAPI::callCommandList(GLuint list) const
{
    static const char *fnName = "glCallCommandListNV";

    beforeCommand(fnName, _api.glCallCommandList);
    _api.glCallCommandList(list);
    afterCommand(fnName);
}

// Calls glCommandListSegmentsNV().
void NVCommandListAPI::commandListSegments(GLuint list, GLuint segments) const
{
    static const char *fnName = "glCommandListSegmentsNV";

    beforeCommand(fnName, _api.glCommandListSegments);
    _api.glCommandListSegments(list, segments);
    afterCommand(fnName);
}

// Calls glCompileCommandListNV().
void NVCommandListAPI::compileCommandList(GLuint list) const
{
    static const char *fnName = "glCompileCommandListNV";

    beforeCommand(fnName, _api.glCompileCommandList);
    _api.glCompileCommandList(list);
    afterCommand(fnName);
}

// Calls glCreateCommandListsNV().
void NVCommandListAPI::createCommandLists(GLsizei n, GLuint *lists) const
{
    static const char *fnName = "glCreateCommandListsNV";

    beforeCommand(fnName, _api.glCreateCommandLists);
    _api.glCreateCommandLists(n, lists);
    afterCommand(fnName);
}

// Calls glCreateStatesNV().
void NVCommandListAPI::createStateS(GLsizei n, GLuint *states) const
{
    static const char *fnName = "glCreateStatesNV";

    beforeCommand(fnName, _api.glCreateStates);
    _api.glCreateStates(n, states);
    afterCommand(fnName);
}

// Calls glDeleteCommandListsNV().
void NVCommandListAPI::deleteCommandLists(GLsizei n, const GLuint *lists) const
{
    static const char *fnName = "glDeleteCommandListsNV";

    beforeCommand(fnName, _api.glDeleteCommandLists);
    _api.glDeleteCommandLists(n, lists);
    afterCommand(fnName);
}

// Calls glDeleteStatesNV().
void NVCommandListAPI::deleteStateS(GLsizei n, const GLuint *states) const
{
    static const char *fnName = "glDeleteStatesNV";

    beforeCommand(fnName, _api.glDeleteStates);
    _api.glDeleteStates(n, states);
    afterCommand(fnName);
}

// Calls glDrawCommandsAddressNV().
void NVCommandListAPI::drawCommandsAddress(GLenum primitiveMode,
                                           const GLuint64 *indirects,
                                           const GLsizei *sizes, GLuint count) const
{
    static const char *fnName = "glDrawCommandsAddressNV";

    beforeCommand(fnName, _api.glDrawCommandsAddress);
    _api.glDrawCommandsAddress(primitiveMode, indirects, sizes, count);
    afterCommand(fnName);
}

// Calls glDrawCommandsNV().
void NVCommandListAPI::drawCommands(GLenum primitiveMode, GLuint buffer,
                                    const GLintptr *indirects,
                                    const GLsizei *sizes, GLuint count) const
{
    static const char *fnName = "glDrawCommandsNV";

    beforeCommand(fnName, _api.glDrawCommands);
    _api.glDrawCommands(primitiveMode, buffer, indirects, sizes, count);
    afterCommand(fnName);
}

// Calls glDrawCommandsStatesAddressNV().
void NVCommandListAPI::drawCommandsStateSAddress(const GLuint64 *indirects,
                                                 const GLsizei *sizes,
                                                 const GLuint *states,
                                                 const GLuint *fbos,
                                                 GLuint count) const
{
    static const char *fnName = "glDrawCommandsStatesAddressNV";

    beforeCommand(fnName, _api.glDrawCommandsStatesAddress);
    _api.glDrawCommandsStatesAddress(indirects, sizes, states, fbos, count);
    afterCommand(fnName);
}

// Calls glDrawCommandsStatesNV().
void NVCommandListAPI::drawCommandsStateS(BufferName buffer,
                                          const GLintptr *indirects,
                                          const GLsizei *sizes,
                                          const GLuint *states,
                                          const GLuint *fbos, GLuint count) const
{
    static const char *fnName = "glDrawCommandsStatesNV";

    beforeCommand(fnName, _api.glDrawCommandsStates);
    _api.glDrawCommandsStates(buffer.ID, indirects, sizes, states, fbos, count);
    afterCommand(fnName);
}

// Calls glGetCommandHeaderNV().
GLuint NVCommandListAPI::getCommandHeader(GLenum tokenID, GLuint size) const
{
    static const char *fnName = "glGetCommandHeaderNV";

    beforeCommand(fnName, _api.glGetCommandHeader);
    GLuint result = _api.glGetCommandHeader(tokenID, size);
    afterCommand(fnName);

    return result;
}

// Calls glGetStageIndexNV().
GLushort NVCommandListAPI::getStageIndex(ShaderType shadertype) const
{
    static const char *fnName = "glGetStageIndexNV";

    beforeCommand(fnName, _api.glGetStageIndex);
    GLushort result = _api.glGetStageIndex(toScalar(shadertype));
    afterCommand(fnName);

    return result;
}

// Calls glIsCommandListNV().
Boolean NVCommandListAPI::isCommandList(GLuint list) const
{
    static const char *fnName = "glIsCommandListNV";

    beforeCommand(fnName, _api.glIsCommandList);
    GLboolean result = _api.glIsCommandList(list);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsStateNV().
Boolean NVCommandListAPI::isState(GLuint state) const
{
    static const char *fnName = "glIsStateNV";

    beforeCommand(fnName, _api.glIsState);
    GLboolean result = _api.glIsState(state);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glListDrawCommandsStatesClientNV().
void NVCommandListAPI::listDrawCommandsStateSClient(GLuint list, GLuint segment,
                                                    const void **indirects,
                                                    const GLsizei *sizes,
                                                    const GLuint *states,
                                                    const GLuint *fbos,
                                                    GLuint count) const
{
    static const char *fnName = "glListDrawCommandsStatesClientNV";

    beforeCommand(fnName, _api.glListDrawCommandsStatesClient);
    _api.glListDrawCommandsStatesClient(list, segment, indirects, sizes, states,
                                        fbos, count);
    afterCommand(fnName);
}

// Calls glStateCaptureNV().
void NVCommandListAPI::stateCapture(GLuint state, GLenum mode) const
{
    static const char *fnName = "glStateCaptureNV";

    beforeCommand(fnName, _api.glStateCapture);
    _api.glStateCapture(state, mode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVConditionalRenderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_conditional_render extension.
NVConditionalRenderAPI::NVConditionalRenderAPI() :
    BaseExtension("GL_NV_conditional_render")
{
}

// Grant read-only access to the underlying function pointers.
const NVConditionalRender &NVConditionalRenderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_conditional_render entry points.
void NVConditionalRenderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginConditionalRenderNV().
void NVConditionalRenderAPI::beginConditionalRender(GLuint id,
                                                    ConditionalRenderMode mode) const
{
    static const char *fnName = "glBeginConditionalRenderNV";

    beforeCommand(fnName, _api.glBeginConditionalRender);
    _api.glBeginConditionalRender(id, toScalar(mode));
    afterCommand(fnName);
}

// Calls glEndConditionalRenderNV().
void NVConditionalRenderAPI::endConditionalRender() const
{
    static const char *fnName = "glEndConditionalRenderNV";

    beforeCommand(fnName, _api.glEndConditionalRender);
    _api.glEndConditionalRender();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRasterAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_conservative_raster extension.
NVConservativeRasterAPI::NVConservativeRasterAPI() :
    BaseExtension("GL_NV_conservative_raster")
{
}

// Grant read-only access to the underlying function pointers.
const NVConservativeRaster &NVConservativeRasterAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_conservative_raster entry points.
void NVConservativeRasterAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSubpixelPrecisionBiasNV().
void NVConservativeRasterAPI::subpixelPrecisionBias(GLuint xbits, GLuint ybits) const
{
    static const char *fnName = "glSubpixelPrecisionBiasNV";

    beforeCommand(fnName, _api.glSubpixelPrecisionBias);
    _api.glSubpixelPrecisionBias(xbits, ybits);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRasterDilateAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_conservative_raster_dilate extension.
NVConservativeRasterDilateAPI::NVConservativeRasterDilateAPI() :
    BaseExtension("GL_NV_conservative_raster_dilate")
{
}

// Grant read-only access to the underlying function pointers.
const NVConservativeRasterDilate &NVConservativeRasterDilateAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_conservative_raster_dilate entry points.
void NVConservativeRasterDilateAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glConservativeRasterParameterfNV().
void NVConservativeRasterDilateAPI::conservativeRasterParameterF(GLenum pname,
                                                                 GLfloat value) const
{
    static const char *fnName = "glConservativeRasterParameterfNV";

    beforeCommand(fnName, _api.glConservativeRasterParameterf);
    _api.glConservativeRasterParameterf(pname, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVConservativeRasterPreSnapTrianglesAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_conservative_raster_pre_snap_triangles extension.
NVConservativeRasterPreSnapTrianglesAPI::NVConservativeRasterPreSnapTrianglesAPI() :
    BaseExtension("GL_NV_conservative_raster_pre_snap_triangles")
{
}

// Grant read-only access to the underlying function pointers.
const NVConservativeRasterPreSnapTriangles &NVConservativeRasterPreSnapTrianglesAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_conservative_raster_pre_snap_triangles entry points.
void NVConservativeRasterPreSnapTrianglesAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glConservativeRasterParameteriNV().
void NVConservativeRasterPreSnapTrianglesAPI::conservativeRasterParameterI(GLenum pname,
                                                                           GLint param) const
{
    static const char *fnName = "glConservativeRasterParameteriNV";

    beforeCommand(fnName, _api.glConservativeRasterParameteri);
    _api.glConservativeRasterParameteri(pname, param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_copy_image extension.
NVCopyImageAPI::NVCopyImageAPI() :
    BaseExtension("GL_NV_copy_image")
{
}

// Grant read-only access to the underlying function pointers.
const NVCopyImage &NVCopyImageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_copy_image entry points.
void NVCopyImageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCopyImageSubDataNV().
void NVCopyImageAPI::copyImageSubData(GLuint srcName,
                                      CopyBufferSubDataTarget srcTarget,
                                      GLint srcLevel, GLint srcX, GLint srcY,
                                      GLint srcZ, GLuint dstName,
                                      CopyBufferSubDataTarget dstTarget,
                                      GLint dstLevel, GLint dstX, GLint dstY,
                                      GLint dstZ, GLsizei width, GLsizei height,
                                      GLsizei depth) const
{
    static const char *fnName = "glCopyImageSubDataNV";

    beforeCommand(fnName, _api.glCopyImageSubData);
    _api.glCopyImageSubData(srcName, toScalar(srcTarget), srcLevel, srcX, srcY,
                            srcZ, dstName, toScalar(dstTarget), dstLevel, dstX,
                            dstY, dstZ, width, height, depth);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVDepthBufferFloatAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_depth_buffer_float extension.
NVDepthBufferFloatAPI::NVDepthBufferFloatAPI() :
    BaseExtension("GL_NV_depth_buffer_float")
{
}

// Grant read-only access to the underlying function pointers.
const NVDepthBufferFloat &NVDepthBufferFloatAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_depth_buffer_float entry points.
void NVDepthBufferFloatAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClearDepthdNV().
void NVDepthBufferFloatAPI::clearDepthD(GLdouble depth) const
{
    static const char *fnName = "glClearDepthdNV";

    beforeCommand(fnName, _api.glClearDepthd);
    _api.glClearDepthd(depth);
    afterCommand(fnName);
}

// Calls glDepthBoundsdNV().
void NVDepthBufferFloatAPI::depthBoundsD(GLdouble zmin, GLdouble zmax) const
{
    static const char *fnName = "glDepthBoundsdNV";

    beforeCommand(fnName, _api.glDepthBoundsd);
    _api.glDepthBoundsd(zmin, zmax);
    afterCommand(fnName);
}

// Calls glDepthRangedNV().
void NVDepthBufferFloatAPI::depthRangeD(GLdouble zNear, GLdouble zFar) const
{
    static const char *fnName = "glDepthRangedNV";

    beforeCommand(fnName, _api.glDepthRanged);
    _api.glDepthRanged(zNear, zFar);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVDrawTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_draw_texture extension.
NVDrawTextureAPI::NVDrawTextureAPI() :
    BaseExtension("GL_NV_draw_texture")
{
}

// Grant read-only access to the underlying function pointers.
const NVDrawTexture &NVDrawTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_draw_texture entry points.
void NVDrawTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawTextureNV().
void NVDrawTextureAPI::drawTexture(TextureName texture, SamplerName sampler,
                                   GLfloat x0, GLfloat y0, GLfloat x1,
                                   GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0,
                                   GLfloat s1, GLfloat t1) const
{
    static const char *fnName = "glDrawTextureNV";

    beforeCommand(fnName, _api.glDrawTexture);
    _api.glDrawTexture(texture.ID, sampler.ID, x0, y0, x1, y1, z, s0, t0, s1, t1);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVDrawVulkanImageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_draw_vulkan_image extension.
NVDrawVulkanImageAPI::NVDrawVulkanImageAPI() :
    BaseExtension("GL_NV_draw_vulkan_image")
{
}

// Grant read-only access to the underlying function pointers.
const NVDrawVulkanImage &NVDrawVulkanImageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_draw_vulkan_image entry points.
void NVDrawVulkanImageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawVkImageNV().
void NVDrawVulkanImageAPI::drawVkImage(GLuint64 vkImage, SamplerName sampler,
                                       GLfloat x0, GLfloat y0, GLfloat x1,
                                       GLfloat y1, GLfloat z, GLfloat s0,
                                       GLfloat t0, GLfloat s1, GLfloat t1) const
{
    static const char *fnName = "glDrawVkImageNV";

    beforeCommand(fnName, _api.glDrawVkImage);
    _api.glDrawVkImage(vkImage, sampler.ID, x0, y0, x1, y1, z, s0, t0, s1, t1);
    afterCommand(fnName);
}

// Calls glGetVkProcAddrNV().
GLVULKANPROCNV NVDrawVulkanImageAPI::getVkProcAddr(const GLchar *name) const
{
    static const char *fnName = "glGetVkProcAddrNV";

    beforeCommand(fnName, _api.glGetVkProcAddr);
    GLVULKANPROCNV result = _api.glGetVkProcAddr(name);
    afterCommand(fnName);

    return result;
}

// Calls glSignalVkFenceNV().
void NVDrawVulkanImageAPI::signalVkFence(GLuint64 vkFence) const
{
    static const char *fnName = "glSignalVkFenceNV";

    beforeCommand(fnName, _api.glSignalVkFence);
    _api.glSignalVkFence(vkFence);
    afterCommand(fnName);
}

// Calls glSignalVkSemaphoreNV().
void NVDrawVulkanImageAPI::signalVkSemaphore(GLuint64 vkSemaphore) const
{
    static const char *fnName = "glSignalVkSemaphoreNV";

    beforeCommand(fnName, _api.glSignalVkSemaphore);
    _api.glSignalVkSemaphore(vkSemaphore);
    afterCommand(fnName);
}

// Calls glWaitVkSemaphoreNV().
void NVDrawVulkanImageAPI::waitVkSemaphore(GLuint64 vkSemaphore) const
{
    static const char *fnName = "glWaitVkSemaphoreNV";

    beforeCommand(fnName, _api.glWaitVkSemaphore);
    _api.glWaitVkSemaphore(vkSemaphore);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVEvaluatorsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_evaluators extension.
NVEvaluatorsAPI::NVEvaluatorsAPI() :
    BaseExtension("GL_NV_evaluators")
{
}

// Grant read-only access to the underlying function pointers.
const NVEvaluators &NVEvaluatorsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_evaluators entry points.
void NVEvaluatorsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glEvalMapsNV().
void NVEvaluatorsAPI::evalMaps(EvalTargetNV target, GLenum mode) const
{
    static const char *fnName = "glEvalMapsNV";

    beforeCommand(fnName, _api.glEvalMaps);
    _api.glEvalMaps(toScalar(target), mode);
    afterCommand(fnName);
}

// Calls glGetMapAttribParameterfvNV().
void NVEvaluatorsAPI::getMapAttribParameterFV(EvalTargetNV target, GLuint index,
                                              MapAttribParameterNV pname,
                                              GLfloat *params) const
{
    static const char *fnName = "glGetMapAttribParameterfvNV";

    beforeCommand(fnName, _api.glGetMapAttribParameterfv);
    _api.glGetMapAttribParameterfv(toScalar(target), index, toScalar(pname),
                                   params);
    afterCommand(fnName);
}

// Calls glGetMapAttribParameterivNV().
void NVEvaluatorsAPI::getMapAttribParameterIV(EvalTargetNV target, GLuint index,
                                              MapAttribParameterNV pname,
                                              GLint *params) const
{
    static const char *fnName = "glGetMapAttribParameterivNV";

    beforeCommand(fnName, _api.glGetMapAttribParameteriv);
    _api.glGetMapAttribParameteriv(toScalar(target), index, toScalar(pname),
                                   params);
    afterCommand(fnName);
}

// Calls glGetMapControlPointsNV().
void NVEvaluatorsAPI::getMapControlPoints(EvalTargetNV target, GLuint index,
                                          MapTypeNV type, GLsizei ustride,
                                          GLsizei vstride, Boolean packed,
                                          void *points) const
{
    static const char *fnName = "glGetMapControlPointsNV";

    beforeCommand(fnName, _api.glGetMapControlPoints);
    _api.glGetMapControlPoints(toScalar(target), index, toScalar(type), ustride,
                               vstride, toScalar(packed), points);
    afterCommand(fnName);
}

// Calls glGetMapParameterfvNV().
void NVEvaluatorsAPI::getMapParameterFV(EvalTargetNV target,
                                        MapParameterNV pname, GLfloat *params) const
{
    static const char *fnName = "glGetMapParameterfvNV";

    beforeCommand(fnName, _api.glGetMapParameterfv);
    _api.glGetMapParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMapParameterivNV().
void NVEvaluatorsAPI::getMapParameterIV(EvalTargetNV target,
                                        MapParameterNV pname, GLint *params) const
{
    static const char *fnName = "glGetMapParameterivNV";

    beforeCommand(fnName, _api.glGetMapParameteriv);
    _api.glGetMapParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMapControlPointsNV().
void NVEvaluatorsAPI::mapControlPoints(EvalTargetNV target, GLuint index,
                                       MapTypeNV type, GLsizei ustride,
                                       GLsizei vstride, GLint uorder,
                                       GLint vorder, Boolean packed,
                                       const void *points) const
{
    static const char *fnName = "glMapControlPointsNV";

    beforeCommand(fnName, _api.glMapControlPoints);
    _api.glMapControlPoints(toScalar(target), index, toScalar(type), ustride,
                            vstride, uorder, vorder, toScalar(packed), points);
    afterCommand(fnName);
}

// Calls glMapParameterfvNV().
void NVEvaluatorsAPI::mapParameterFV(EvalTargetNV target, MapParameterNV pname,
                                     const GLfloat *params) const
{
    static const char *fnName = "glMapParameterfvNV";

    beforeCommand(fnName, _api.glMapParameterfv);
    _api.glMapParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMapParameterivNV().
void NVEvaluatorsAPI::mapParameterIV(EvalTargetNV target, MapParameterNV pname,
                                     const GLint *params) const
{
    static const char *fnName = "glMapParameterivNV";

    beforeCommand(fnName, _api.glMapParameteriv);
    _api.glMapParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVExplicitMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_explicit_multisample extension.
NVExplicitMultisampleAPI::NVExplicitMultisampleAPI() :
    BaseExtension("GL_NV_explicit_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const NVExplicitMultisample &NVExplicitMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_explicit_multisample entry points.
void NVExplicitMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetMultisamplefvNV().
void NVExplicitMultisampleAPI::getMultisampleFV(GetMultisamplePNameNV pname,
                                                GLuint index, GLfloat *val) const
{
    static const char *fnName = "glGetMultisamplefvNV";

    beforeCommand(fnName, _api.glGetMultisamplefv);
    _api.glGetMultisamplefv(toScalar(pname), index, val);
    afterCommand(fnName);
}

// Calls glSampleMaskIndexedNV().
void NVExplicitMultisampleAPI::sampleMaskIndexed(GLuint index, GLbitfield mask) const
{
    static const char *fnName = "glSampleMaskIndexedNV";

    beforeCommand(fnName, _api.glSampleMaskIndexed);
    _api.glSampleMaskIndexed(index, mask);
    afterCommand(fnName);
}

// Calls glTexRenderbufferNV().
void NVExplicitMultisampleAPI::texRenderbuffer(TextureTarget target,
                                               RenderbufferName renderbuffer) const
{
    static const char *fnName = "glTexRenderbufferNV";

    beforeCommand(fnName, _api.glTexRenderbuffer);
    _api.glTexRenderbuffer(toScalar(target), renderbuffer.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVFenceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_fence extension.
NVFenceAPI::NVFenceAPI() :
    BaseExtension("GL_NV_fence")
{
}

// Grant read-only access to the underlying function pointers.
const NVFence &NVFenceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_fence entry points.
void NVFenceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeleteFencesNV().
void NVFenceAPI::deleteFences(GLsizei n, const GLuint *fences) const
{
    static const char *fnName = "glDeleteFencesNV";

    beforeCommand(fnName, _api.glDeleteFences);
    _api.glDeleteFences(n, fences);
    afterCommand(fnName);
}

// Calls glFinishFenceNV().
void NVFenceAPI::finishFence(GLuint fence) const
{
    static const char *fnName = "glFinishFenceNV";

    beforeCommand(fnName, _api.glFinishFence);
    _api.glFinishFence(fence);
    afterCommand(fnName);
}

// Calls glGenFencesNV().
void NVFenceAPI::genFences(GLsizei n, GLuint *fences) const
{
    static const char *fnName = "glGenFencesNV";

    beforeCommand(fnName, _api.glGenFences);
    _api.glGenFences(n, fences);
    afterCommand(fnName);
}

// Calls glGetFenceivNV().
void NVFenceAPI::getFenceIV(GLuint fence, FenceParameterNameNV pname,
                            GLint *params) const
{
    static const char *fnName = "glGetFenceivNV";

    beforeCommand(fnName, _api.glGetFenceiv);
    _api.glGetFenceiv(fence, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsFenceNV().
Boolean NVFenceAPI::isFence(GLuint fence) const
{
    static const char *fnName = "glIsFenceNV";

    beforeCommand(fnName, _api.glIsFence);
    GLboolean result = _api.glIsFence(fence);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glSetFenceNV().
void NVFenceAPI::setFence(GLuint fence, FenceConditionNV condition) const
{
    static const char *fnName = "glSetFenceNV";

    beforeCommand(fnName, _api.glSetFence);
    _api.glSetFence(fence, toScalar(condition));
    afterCommand(fnName);
}

// Calls glTestFenceNV().
Boolean NVFenceAPI::testFence(GLuint fence) const
{
    static const char *fnName = "glTestFenceNV";

    beforeCommand(fnName, _api.glTestFence);
    GLboolean result = _api.glTestFence(fence);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// NVFragmentCoverageToColorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_fragment_coverage_to_color extension.
NVFragmentCoverageToColorAPI::NVFragmentCoverageToColorAPI() :
    BaseExtension("GL_NV_fragment_coverage_to_color")
{
}

// Grant read-only access to the underlying function pointers.
const NVFragmentCoverageToColor &NVFragmentCoverageToColorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_fragment_coverage_to_color entry points.
void NVFragmentCoverageToColorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFragmentCoverageColorNV().
void NVFragmentCoverageToColorAPI::fragmentCoverageColor(GLuint color) const
{
    static const char *fnName = "glFragmentCoverageColorNV";

    beforeCommand(fnName, _api.glFragmentCoverageColor);
    _api.glFragmentCoverageColor(color);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVFragmentProgramAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_fragment_program extension.
NVFragmentProgramAPI::NVFragmentProgramAPI() :
    BaseExtension("GL_NV_fragment_program")
{
}

// Grant read-only access to the underlying function pointers.
const NVFragmentProgram &NVFragmentProgramAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_fragment_program entry points.
void NVFragmentProgramAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetProgramNamedParameterdvNV().
void NVFragmentProgramAPI::getProgramNamedParameterDV(ProgramName id,
                                                      GLsizei len,
                                                      const GLubyte *name,
                                                      GLdouble *params) const
{
    static const char *fnName = "glGetProgramNamedParameterdvNV";

    beforeCommand(fnName, _api.glGetProgramNamedParameterdv);
    _api.glGetProgramNamedParameterdv(id.ID, len, name, params);
    afterCommand(fnName);
}

// Calls glGetProgramNamedParameterfvNV().
void NVFragmentProgramAPI::getProgramNamedParameterFV(ProgramName id,
                                                      GLsizei len,
                                                      const GLubyte *name,
                                                      GLfloat *params) const
{
    static const char *fnName = "glGetProgramNamedParameterfvNV";

    beforeCommand(fnName, _api.glGetProgramNamedParameterfv);
    _api.glGetProgramNamedParameterfv(id.ID, len, name, params);
    afterCommand(fnName);
}

// Calls glProgramNamedParameter4dNV().
void NVFragmentProgramAPI::programNamedParameter4D(ProgramName id, GLsizei len,
                                                   const GLubyte *name,
                                                   GLdouble x, GLdouble y,
                                                   GLdouble z, GLdouble w) const
{
    static const char *fnName = "glProgramNamedParameter4dNV";

    beforeCommand(fnName, _api.glProgramNamedParameter4d);
    _api.glProgramNamedParameter4d(id.ID, len, name, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramNamedParameter4dvNV().
void NVFragmentProgramAPI::programNamedParameter4DV(ProgramName id, GLsizei len,
                                                    const GLubyte *name,
                                                    const GLdouble *v) const
{
    static const char *fnName = "glProgramNamedParameter4dvNV";

    beforeCommand(fnName, _api.glProgramNamedParameter4dv);
    _api.glProgramNamedParameter4dv(id.ID, len, name, v);
    afterCommand(fnName);
}

// Calls glProgramNamedParameter4fNV().
void NVFragmentProgramAPI::programNamedParameter4F(ProgramName id, GLsizei len,
                                                   const GLubyte *name,
                                                   GLfloat x, GLfloat y,
                                                   GLfloat z, GLfloat w) const
{
    static const char *fnName = "glProgramNamedParameter4fNV";

    beforeCommand(fnName, _api.glProgramNamedParameter4f);
    _api.glProgramNamedParameter4f(id.ID, len, name, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramNamedParameter4fvNV().
void NVFragmentProgramAPI::programNamedParameter4FV(ProgramName id, GLsizei len,
                                                    const GLubyte *name,
                                                    const GLfloat *v) const
{
    static const char *fnName = "glProgramNamedParameter4fvNV";

    beforeCommand(fnName, _api.glProgramNamedParameter4fv);
    _api.glProgramNamedParameter4fv(id.ID, len, name, v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVFramebufferMixedSamplesAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_framebuffer_mixed_samples extension.
NVFramebufferMixedSamplesAPI::NVFramebufferMixedSamplesAPI() :
    BaseExtension("GL_NV_framebuffer_mixed_samples")
{
}

// Grant read-only access to the underlying function pointers.
const NVFramebufferMixedSamples &NVFramebufferMixedSamplesAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_framebuffer_mixed_samples entry points.
void NVFramebufferMixedSamplesAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCoverageModulationNV().
void NVFramebufferMixedSamplesAPI::coverageModulation(GLenum components) const
{
    static const char *fnName = "glCoverageModulationNV";

    beforeCommand(fnName, _api.glCoverageModulation);
    _api.glCoverageModulation(components);
    afterCommand(fnName);
}

// Calls glCoverageModulationTableNV().
void NVFramebufferMixedSamplesAPI::coverageModulationTable(GLsizei n,
                                                           const GLfloat *v) const
{
    static const char *fnName = "glCoverageModulationTableNV";

    beforeCommand(fnName, _api.glCoverageModulationTable);
    _api.glCoverageModulationTable(n, v);
    afterCommand(fnName);
}

// Calls glGetCoverageModulationTableNV().
void NVFramebufferMixedSamplesAPI::getCoverageModulationTable(GLsizei bufSize,
                                                              GLfloat *v) const
{
    static const char *fnName = "glGetCoverageModulationTableNV";

    beforeCommand(fnName, _api.glGetCoverageModulationTable);
    _api.glGetCoverageModulationTable(bufSize, v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVFramebufferMultisampleCoverageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_framebuffer_multisample_coverage extension.
NVFramebufferMultisampleCoverageAPI::NVFramebufferMultisampleCoverageAPI() :
    BaseExtension("GL_NV_framebuffer_multisample_coverage")
{
}

// Grant read-only access to the underlying function pointers.
const NVFramebufferMultisampleCoverage &NVFramebufferMultisampleCoverageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_framebuffer_multisample_coverage entry points.
void NVFramebufferMultisampleCoverageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glRenderbufferStorageMultisampleCoverageNV().
void NVFramebufferMultisampleCoverageAPI::renderbufferStorageMultisampleCoverage(RenderbufferTarget target,
                                                                                 GLsizei coverageSamples,
                                                                                 GLsizei colorSamples,
                                                                                 InternalFormat internalformat,
                                                                                 GLsizei width,
                                                                                 GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorageMultisampleCoverageNV";

    beforeCommand(fnName, _api.glRenderbufferStorageMultisampleCoverage);
    _api.glRenderbufferStorageMultisampleCoverage(toScalar(target),
                                                  coverageSamples, colorSamples,
                                                  toScalar(internalformat),
                                                  width, height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVGeometryPROGRAM4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_geometry_program4 extension.
NVGeometryPROGRAM4API::NVGeometryPROGRAM4API() :
    BaseExtension("GL_NV_geometry_program4")
{
}

// Grant read-only access to the underlying function pointers.
const NVGeometryPROGRAM4 &NVGeometryPROGRAM4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_geometry_program4 entry points.
void NVGeometryPROGRAM4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferTextureEXT().
void NVGeometryPROGRAM4API::framebufferTexture(FramebufferTarget target,
                                               FramebufferAttachment attachment,
                                               TextureName texture, GLint level) const
{
    static const char *fnName = "glFramebufferTextureEXT";

    beforeCommand(fnName, _api.glFramebufferTexture);
    _api.glFramebufferTexture(toScalar(target), toScalar(attachment), texture.ID,
                              level);
    afterCommand(fnName);
}

// Calls glFramebufferTextureFaceEXT().
void NVGeometryPROGRAM4API::framebufferTextureFace(FramebufferTarget target,
                                                   FramebufferAttachment attachment,
                                                   TextureName texture,
                                                   GLint level,
                                                   TextureTarget face) const
{
    static const char *fnName = "glFramebufferTextureFaceEXT";

    beforeCommand(fnName, _api.glFramebufferTextureFace);
    _api.glFramebufferTextureFace(toScalar(target), toScalar(attachment),
                                  texture.ID, level, toScalar(face));
    afterCommand(fnName);
}

// Calls glProgramVertexLimitNV().
void NVGeometryPROGRAM4API::programVertexLimit(ProgramTarget target, GLint limit) const
{
    static const char *fnName = "glProgramVertexLimitNV";

    beforeCommand(fnName, _api.glProgramVertexLimit);
    _api.glProgramVertexLimit(toScalar(target), limit);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUMulticastAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_gpu_multicast extension.
NVGPUMulticastAPI::NVGPUMulticastAPI() :
    BaseExtension("GL_NV_gpu_multicast")
{
}

// Grant read-only access to the underlying function pointers.
const NVGPUMulticast &NVGPUMulticastAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_gpu_multicast entry points.
void NVGPUMulticastAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMulticastBarrierNV().
void NVGPUMulticastAPI::multicastBarrier() const
{
    static const char *fnName = "glMulticastBarrierNV";

    beforeCommand(fnName, _api.glMulticastBarrier);
    _api.glMulticastBarrier();
    afterCommand(fnName);
}

// Calls glMulticastBlitFramebufferNV().
void NVGPUMulticastAPI::multicastBlitFramebuffer(GLuint srcGpu, GLuint dstGpu,
                                                 GLint srcX0, GLint srcY0,
                                                 GLint srcX1, GLint srcY1,
                                                 GLint dstX0, GLint dstY0,
                                                 GLint dstX1, GLint dstY1,
                                                 GLbitfield  /* ClearBufferMask */ mask,
                                                 GLenum filter) const
{
    static const char *fnName = "glMulticastBlitFramebufferNV";

    beforeCommand(fnName, _api.glMulticastBlitFramebuffer);
    _api.glMulticastBlitFramebuffer(srcGpu, dstGpu, srcX0, srcY0, srcX1, srcY1,
                                    dstX0, dstY0, dstX1, dstY1, mask, filter);
    afterCommand(fnName);
}

// Calls glMulticastBufferSubDataNV().
void NVGPUMulticastAPI::multicastBufferSubData(GLbitfield gpuMask,
                                               BufferName buffer,
                                               GLintptr offset, GLsizeiptr size,
                                               const void *data) const
{
    static const char *fnName = "glMulticastBufferSubDataNV";

    beforeCommand(fnName, _api.glMulticastBufferSubData);
    _api.glMulticastBufferSubData(gpuMask, buffer.ID, offset, size, data);
    afterCommand(fnName);
}

// Calls glMulticastCopyBufferSubDataNV().
void NVGPUMulticastAPI::multicastCopyBufferSubData(GLuint readGpu,
                                                   GLbitfield writeGpuMask,
                                                   BufferName readBuffer,
                                                   BufferName writeBuffer,
                                                   GLintptr readOffset,
                                                   GLintptr writeOffset,
                                                   GLsizeiptr size) const
{
    static const char *fnName = "glMulticastCopyBufferSubDataNV";

    beforeCommand(fnName, _api.glMulticastCopyBufferSubData);
    _api.glMulticastCopyBufferSubData(readGpu, writeGpuMask, readBuffer.ID,
                                      writeBuffer.ID, readOffset, writeOffset,
                                      size);
    afterCommand(fnName);
}

// Calls glMulticastCopyImageSubDataNV().
void NVGPUMulticastAPI::multicastCopyImageSubData(GLuint srcGpu,
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
                                                  GLsizei srcDepth) const
{
    static const char *fnName = "glMulticastCopyImageSubDataNV";

    beforeCommand(fnName, _api.glMulticastCopyImageSubData);
    _api.glMulticastCopyImageSubData(srcGpu, dstGpuMask, srcName, srcTarget,
                                     srcLevel, srcX, srcY, srcZ, dstName,
                                     dstTarget, dstLevel, dstX, dstY, dstZ,
                                     srcWidth, srcHeight, srcDepth);
    afterCommand(fnName);
}

// Calls glMulticastFramebufferSampleLocationsfvNV().
void NVGPUMulticastAPI::multicastFramebufferSampleLocationsFV(GLuint gpu,
                                                              FramebufferName framebuffer,
                                                              GLuint start,
                                                              GLsizei count,
                                                              const GLfloat *v) const
{
    static const char *fnName = "glMulticastFramebufferSampleLocationsfvNV";

    beforeCommand(fnName, _api.glMulticastFramebufferSampleLocationsfv);
    _api.glMulticastFramebufferSampleLocationsfv(gpu, framebuffer.ID, start,
                                                 count, v);
    afterCommand(fnName);
}

// Calls glMulticastGetQueryObjecti64vNV().
void NVGPUMulticastAPI::multicastGetQueryObjectI64V(GLuint gpu, GLuint id,
                                                    GLenum pname,
                                                    GLint64 *params) const
{
    static const char *fnName = "glMulticastGetQueryObjecti64vNV";

    beforeCommand(fnName, _api.glMulticastGetQueryObjecti64v);
    _api.glMulticastGetQueryObjecti64v(gpu, id, pname, params);
    afterCommand(fnName);
}

// Calls glMulticastGetQueryObjectivNV().
void NVGPUMulticastAPI::multicastGetQueryObjectIV(GLuint gpu, GLuint id,
                                                  GLenum pname, GLint *params) const
{
    static const char *fnName = "glMulticastGetQueryObjectivNV";

    beforeCommand(fnName, _api.glMulticastGetQueryObjectiv);
    _api.glMulticastGetQueryObjectiv(gpu, id, pname, params);
    afterCommand(fnName);
}

// Calls glMulticastGetQueryObjectui64vNV().
void NVGPUMulticastAPI::multicastGetQueryObjectUI64(GLuint gpu, GLuint id,
                                                    GLenum pname,
                                                    GLuint64 *params) const
{
    static const char *fnName = "glMulticastGetQueryObjectui64vNV";

    beforeCommand(fnName, _api.glMulticastGetQueryObjectui64v);
    _api.glMulticastGetQueryObjectui64v(gpu, id, pname, params);
    afterCommand(fnName);
}

// Calls glMulticastGetQueryObjectuivNV().
void NVGPUMulticastAPI::multicastGetQueryObjectUIV(GLuint gpu, GLuint id,
                                                   GLenum pname, GLuint *params) const
{
    static const char *fnName = "glMulticastGetQueryObjectuivNV";

    beforeCommand(fnName, _api.glMulticastGetQueryObjectuiv);
    _api.glMulticastGetQueryObjectuiv(gpu, id, pname, params);
    afterCommand(fnName);
}

// Calls glMulticastWaitSyncNV().
void NVGPUMulticastAPI::multicastWaitSync(GLuint signalGpu,
                                          GLbitfield waitGpuMask) const
{
    static const char *fnName = "glMulticastWaitSyncNV";

    beforeCommand(fnName, _api.glMulticastWaitSync);
    _api.glMulticastWaitSync(signalGpu, waitGpuMask);
    afterCommand(fnName);
}

// Calls glRenderGpuMaskNV().
void NVGPUMulticastAPI::renderGpuMask(GLbitfield mask) const
{
    static const char *fnName = "glRenderGpuMaskNV";

    beforeCommand(fnName, _api.glRenderGpuMask);
    _api.glRenderGpuMask(mask);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUPROGRAM4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_gpu_program4 extension.
NVGPUPROGRAM4API::NVGPUPROGRAM4API() :
    BaseExtension("GL_NV_gpu_program4")
{
}

// Grant read-only access to the underlying function pointers.
const NVGPUPROGRAM4 &NVGPUPROGRAM4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_gpu_program4 entry points.
void NVGPUPROGRAM4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetProgramEnvParameterIivNV().
void NVGPUPROGRAM4API::getProgramEnvParameterIIV(ProgramTarget target,
                                                 GLuint index, GLint *params) const
{
    static const char *fnName = "glGetProgramEnvParameterIivNV";

    beforeCommand(fnName, _api.glGetProgramEnvParameterIiv);
    _api.glGetProgramEnvParameterIiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramEnvParameterIuivNV().
void NVGPUPROGRAM4API::getProgramEnvParameterIUIV(ProgramTarget target,
                                                  GLuint index, GLuint *params) const
{
    static const char *fnName = "glGetProgramEnvParameterIuivNV";

    beforeCommand(fnName, _api.glGetProgramEnvParameterIuiv);
    _api.glGetProgramEnvParameterIuiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramLocalParameterIivNV().
void NVGPUPROGRAM4API::getProgramLocalParameterIIV(ProgramTarget target,
                                                   GLuint index, GLint *params) const
{
    static const char *fnName = "glGetProgramLocalParameterIivNV";

    beforeCommand(fnName, _api.glGetProgramLocalParameterIiv);
    _api.glGetProgramLocalParameterIiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramLocalParameterIuivNV().
void NVGPUPROGRAM4API::getProgramLocalParameterIUIV(ProgramTarget target,
                                                    GLuint index, GLuint *params) const
{
    static const char *fnName = "glGetProgramLocalParameterIuivNV";

    beforeCommand(fnName, _api.glGetProgramLocalParameterIuiv);
    _api.glGetProgramLocalParameterIuiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramEnvParameterI4iNV().
void NVGPUPROGRAM4API::programEnvParameterI4I(ProgramTarget target, GLuint index,
                                              GLint x, GLint y, GLint z, GLint w) const
{
    static const char *fnName = "glProgramEnvParameterI4iNV";

    beforeCommand(fnName, _api.glProgramEnvParameterI4i);
    _api.glProgramEnvParameterI4i(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramEnvParameterI4ivNV().
void NVGPUPROGRAM4API::programEnvParameterI4IV(ProgramTarget target,
                                               GLuint index, const GLint *params) const
{
    static const char *fnName = "glProgramEnvParameterI4ivNV";

    beforeCommand(fnName, _api.glProgramEnvParameterI4iv);
    _api.glProgramEnvParameterI4iv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramEnvParameterI4uiNV().
void NVGPUPROGRAM4API::programEnvParameterI4UI(ProgramTarget target,
                                               GLuint index, GLuint x, GLuint y,
                                               GLuint z, GLuint w) const
{
    static const char *fnName = "glProgramEnvParameterI4uiNV";

    beforeCommand(fnName, _api.glProgramEnvParameterI4ui);
    _api.glProgramEnvParameterI4ui(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramEnvParameterI4uivNV().
void NVGPUPROGRAM4API::programEnvParameterI4UIV(ProgramTarget target,
                                                GLuint index,
                                                const GLuint *params) const
{
    static const char *fnName = "glProgramEnvParameterI4uivNV";

    beforeCommand(fnName, _api.glProgramEnvParameterI4uiv);
    _api.glProgramEnvParameterI4uiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramEnvParametersI4ivNV().
void NVGPUPROGRAM4API::programEnvParametersI4IV(ProgramTarget target,
                                                GLuint index, GLsizei count,
                                                const GLint *params) const
{
    static const char *fnName = "glProgramEnvParametersI4ivNV";

    beforeCommand(fnName, _api.glProgramEnvParametersI4iv);
    _api.glProgramEnvParametersI4iv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

// Calls glProgramEnvParametersI4uivNV().
void NVGPUPROGRAM4API::programEnvParametersI4UIV(ProgramTarget target,
                                                 GLuint index, GLsizei count,
                                                 const GLuint *params) const
{
    static const char *fnName = "glProgramEnvParametersI4uivNV";

    beforeCommand(fnName, _api.glProgramEnvParametersI4uiv);
    _api.glProgramEnvParametersI4uiv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParameterI4iNV().
void NVGPUPROGRAM4API::programLocalParameterI4I(ProgramTarget target,
                                                GLuint index, GLint x, GLint y,
                                                GLint z, GLint w) const
{
    static const char *fnName = "glProgramLocalParameterI4iNV";

    beforeCommand(fnName, _api.glProgramLocalParameterI4i);
    _api.glProgramLocalParameterI4i(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramLocalParameterI4ivNV().
void NVGPUPROGRAM4API::programLocalParameterI4IV(ProgramTarget target,
                                                 GLuint index,
                                                 const GLint *params) const
{
    static const char *fnName = "glProgramLocalParameterI4ivNV";

    beforeCommand(fnName, _api.glProgramLocalParameterI4iv);
    _api.glProgramLocalParameterI4iv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParameterI4uiNV().
void NVGPUPROGRAM4API::programLocalParameterI4UI(ProgramTarget target,
                                                 GLuint index, GLuint x,
                                                 GLuint y, GLuint z, GLuint w) const
{
    static const char *fnName = "glProgramLocalParameterI4uiNV";

    beforeCommand(fnName, _api.glProgramLocalParameterI4ui);
    _api.glProgramLocalParameterI4ui(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramLocalParameterI4uivNV().
void NVGPUPROGRAM4API::programLocalParameterI4UIV(ProgramTarget target,
                                                  GLuint index,
                                                  const GLuint *params) const
{
    static const char *fnName = "glProgramLocalParameterI4uivNV";

    beforeCommand(fnName, _api.glProgramLocalParameterI4uiv);
    _api.glProgramLocalParameterI4uiv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParametersI4ivNV().
void NVGPUPROGRAM4API::programLocalParametersI4IV(ProgramTarget target,
                                                  GLuint index, GLsizei count,
                                                  const GLint *params) const
{
    static const char *fnName = "glProgramLocalParametersI4ivNV";

    beforeCommand(fnName, _api.glProgramLocalParametersI4iv);
    _api.glProgramLocalParametersI4iv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParametersI4uivNV().
void NVGPUPROGRAM4API::programLocalParametersI4UIV(ProgramTarget target,
                                                   GLuint index, GLsizei count,
                                                   const GLuint *params) const
{
    static const char *fnName = "glProgramLocalParametersI4uivNV";

    beforeCommand(fnName, _api.glProgramLocalParametersI4uiv);
    _api.glProgramLocalParametersI4uiv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUPROGRAM5API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_gpu_program5 extension.
NVGPUPROGRAM5API::NVGPUPROGRAM5API() :
    BaseExtension("GL_NV_gpu_program5")
{
}

// Grant read-only access to the underlying function pointers.
const NVGPUPROGRAM5 &NVGPUPROGRAM5API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_gpu_program5 entry points.
void NVGPUPROGRAM5API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetProgramSubroutineParameteruivNV().
void NVGPUPROGRAM5API::getProgramSubroutineParameterUIV(GLenum target,
                                                        GLuint index,
                                                        GLuint *param) const
{
    static const char *fnName = "glGetProgramSubroutineParameteruivNV";

    beforeCommand(fnName, _api.glGetProgramSubroutineParameteruiv);
    _api.glGetProgramSubroutineParameteruiv(target, index, param);
    afterCommand(fnName);
}

// Calls glProgramSubroutineParametersuivNV().
void NVGPUPROGRAM5API::programSubroutineParametersUIV(GLenum target,
                                                      GLsizei count,
                                                      const GLuint *params) const
{
    static const char *fnName = "glProgramSubroutineParametersuivNV";

    beforeCommand(fnName, _api.glProgramSubroutineParametersuiv);
    _api.glProgramSubroutineParametersuiv(target, count, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVHalfFloatAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_half_float extension.
NVHalfFloatAPI::NVHalfFloatAPI() :
    BaseExtension("GL_NV_half_float")
{
}

// Grant read-only access to the underlying function pointers.
const NVHalfFloat &NVHalfFloatAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_half_float entry points.
void NVHalfFloatAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColor3hNV().
void NVHalfFloatAPI::color3H(GLhalfNV red, GLhalfNV green, GLhalfNV blue) const
{
    static const char *fnName = "glColor3hNV";

    beforeCommand(fnName, _api.glColor3h);
    _api.glColor3h(red, green, blue);
    afterCommand(fnName);
}

// Calls glColor3hvNV().
void NVHalfFloatAPI::color3HV(const GLhalfNV *v) const
{
    static const char *fnName = "glColor3hvNV";

    beforeCommand(fnName, _api.glColor3hv);
    _api.glColor3hv(v);
    afterCommand(fnName);
}

// Calls glColor4hNV().
void NVHalfFloatAPI::color4H(GLhalfNV red, GLhalfNV green, GLhalfNV blue,
                             GLhalfNV alpha) const
{
    static const char *fnName = "glColor4hNV";

    beforeCommand(fnName, _api.glColor4h);
    _api.glColor4h(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glColor4hvNV().
void NVHalfFloatAPI::color4HV(const GLhalfNV *v) const
{
    static const char *fnName = "glColor4hvNV";

    beforeCommand(fnName, _api.glColor4hv);
    _api.glColor4hv(v);
    afterCommand(fnName);
}

// Calls glFogCoordhNV().
void NVHalfFloatAPI::fogCoordh(GLhalfNV fog) const
{
    static const char *fnName = "glFogCoordhNV";

    beforeCommand(fnName, _api.glFogCoordh);
    _api.glFogCoordh(fog);
    afterCommand(fnName);
}

// Calls glFogCoordhvNV().
void NVHalfFloatAPI::fogCoordhV(const GLhalfNV *fog) const
{
    static const char *fnName = "glFogCoordhvNV";

    beforeCommand(fnName, _api.glFogCoordhv);
    _api.glFogCoordhv(fog);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1hNV().
void NVHalfFloatAPI::multiTexCoord1H(TextureUnit target, GLhalfNV s) const
{
    static const char *fnName = "glMultiTexCoord1hNV";

    beforeCommand(fnName, _api.glMultiTexCoord1h);
    _api.glMultiTexCoord1h(toScalar(target), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1hvNV().
void NVHalfFloatAPI::multiTexCoord1HV(TextureUnit target, const GLhalfNV *v) const
{
    static const char *fnName = "glMultiTexCoord1hvNV";

    beforeCommand(fnName, _api.glMultiTexCoord1hv);
    _api.glMultiTexCoord1hv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2hNV().
void NVHalfFloatAPI::multiTexCoord2H(TextureUnit target, GLhalfNV s, GLhalfNV t) const
{
    static const char *fnName = "glMultiTexCoord2hNV";

    beforeCommand(fnName, _api.glMultiTexCoord2h);
    _api.glMultiTexCoord2h(toScalar(target), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2hvNV().
void NVHalfFloatAPI::multiTexCoord2HV(TextureUnit target, const GLhalfNV *v) const
{
    static const char *fnName = "glMultiTexCoord2hvNV";

    beforeCommand(fnName, _api.glMultiTexCoord2hv);
    _api.glMultiTexCoord2hv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3hNV().
void NVHalfFloatAPI::multiTexCoord3H(TextureUnit target, GLhalfNV s, GLhalfNV t,
                                     GLhalfNV r) const
{
    static const char *fnName = "glMultiTexCoord3hNV";

    beforeCommand(fnName, _api.glMultiTexCoord3h);
    _api.glMultiTexCoord3h(toScalar(target), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3hvNV().
void NVHalfFloatAPI::multiTexCoord3HV(TextureUnit target, const GLhalfNV *v) const
{
    static const char *fnName = "glMultiTexCoord3hvNV";

    beforeCommand(fnName, _api.glMultiTexCoord3hv);
    _api.glMultiTexCoord3hv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4hNV().
void NVHalfFloatAPI::multiTexCoord4H(TextureUnit target, GLhalfNV s, GLhalfNV t,
                                     GLhalfNV r, GLhalfNV q) const
{
    static const char *fnName = "glMultiTexCoord4hNV";

    beforeCommand(fnName, _api.glMultiTexCoord4h);
    _api.glMultiTexCoord4h(toScalar(target), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4hvNV().
void NVHalfFloatAPI::multiTexCoord4HV(TextureUnit target, const GLhalfNV *v) const
{
    static const char *fnName = "glMultiTexCoord4hvNV";

    beforeCommand(fnName, _api.glMultiTexCoord4hv);
    _api.glMultiTexCoord4hv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glNormal3hNV().
void NVHalfFloatAPI::normal3H(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz) const
{
    static const char *fnName = "glNormal3hNV";

    beforeCommand(fnName, _api.glNormal3h);
    _api.glNormal3h(nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormal3hvNV().
void NVHalfFloatAPI::normal3HV(const GLhalfNV *v) const
{
    static const char *fnName = "glNormal3hvNV";

    beforeCommand(fnName, _api.glNormal3hv);
    _api.glNormal3hv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3hNV().
void NVHalfFloatAPI::secondaryColor3H(GLhalfNV red, GLhalfNV green,
                                      GLhalfNV blue) const
{
    static const char *fnName = "glSecondaryColor3hNV";

    beforeCommand(fnName, _api.glSecondaryColor3h);
    _api.glSecondaryColor3h(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3hvNV().
void NVHalfFloatAPI::secondaryColor3HV(const GLhalfNV *v) const
{
    static const char *fnName = "glSecondaryColor3hvNV";

    beforeCommand(fnName, _api.glSecondaryColor3hv);
    _api.glSecondaryColor3hv(v);
    afterCommand(fnName);
}

// Calls glTexCoord1hNV().
void NVHalfFloatAPI::texCoord1H(GLhalfNV s) const
{
    static const char *fnName = "glTexCoord1hNV";

    beforeCommand(fnName, _api.glTexCoord1h);
    _api.glTexCoord1h(s);
    afterCommand(fnName);
}

// Calls glTexCoord1hvNV().
void NVHalfFloatAPI::texCoord1HV(const GLhalfNV *v) const
{
    static const char *fnName = "glTexCoord1hvNV";

    beforeCommand(fnName, _api.glTexCoord1hv);
    _api.glTexCoord1hv(v);
    afterCommand(fnName);
}

// Calls glTexCoord2hNV().
void NVHalfFloatAPI::texCoord2H(GLhalfNV s, GLhalfNV t) const
{
    static const char *fnName = "glTexCoord2hNV";

    beforeCommand(fnName, _api.glTexCoord2h);
    _api.glTexCoord2h(s, t);
    afterCommand(fnName);
}

// Calls glTexCoord2hvNV().
void NVHalfFloatAPI::texCoord2HV(const GLhalfNV *v) const
{
    static const char *fnName = "glTexCoord2hvNV";

    beforeCommand(fnName, _api.glTexCoord2hv);
    _api.glTexCoord2hv(v);
    afterCommand(fnName);
}

// Calls glTexCoord3hNV().
void NVHalfFloatAPI::texCoord3H(GLhalfNV s, GLhalfNV t, GLhalfNV r) const
{
    static const char *fnName = "glTexCoord3hNV";

    beforeCommand(fnName, _api.glTexCoord3h);
    _api.glTexCoord3h(s, t, r);
    afterCommand(fnName);
}

// Calls glTexCoord3hvNV().
void NVHalfFloatAPI::texCoord3HV(const GLhalfNV *v) const
{
    static const char *fnName = "glTexCoord3hvNV";

    beforeCommand(fnName, _api.glTexCoord3hv);
    _api.glTexCoord3hv(v);
    afterCommand(fnName);
}

// Calls glTexCoord4hNV().
void NVHalfFloatAPI::texCoord4H(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q) const
{
    static const char *fnName = "glTexCoord4hNV";

    beforeCommand(fnName, _api.glTexCoord4h);
    _api.glTexCoord4h(s, t, r, q);
    afterCommand(fnName);
}

// Calls glTexCoord4hvNV().
void NVHalfFloatAPI::texCoord4HV(const GLhalfNV *v) const
{
    static const char *fnName = "glTexCoord4hvNV";

    beforeCommand(fnName, _api.glTexCoord4hv);
    _api.glTexCoord4hv(v);
    afterCommand(fnName);
}

// Calls glVertex2hNV().
void NVHalfFloatAPI::vertex2H(GLhalfNV x, GLhalfNV y) const
{
    static const char *fnName = "glVertex2hNV";

    beforeCommand(fnName, _api.glVertex2h);
    _api.glVertex2h(x, y);
    afterCommand(fnName);
}

// Calls glVertex2hvNV().
void NVHalfFloatAPI::vertex2HV(const GLhalfNV *v) const
{
    static const char *fnName = "glVertex2hvNV";

    beforeCommand(fnName, _api.glVertex2hv);
    _api.glVertex2hv(v);
    afterCommand(fnName);
}

// Calls glVertex3hNV().
void NVHalfFloatAPI::vertex3H(GLhalfNV x, GLhalfNV y, GLhalfNV z) const
{
    static const char *fnName = "glVertex3hNV";

    beforeCommand(fnName, _api.glVertex3h);
    _api.glVertex3h(x, y, z);
    afterCommand(fnName);
}

// Calls glVertex3hvNV().
void NVHalfFloatAPI::vertex3HV(const GLhalfNV *v) const
{
    static const char *fnName = "glVertex3hvNV";

    beforeCommand(fnName, _api.glVertex3hv);
    _api.glVertex3hv(v);
    afterCommand(fnName);
}

// Calls glVertex4hNV().
void NVHalfFloatAPI::vertex4H(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w) const
{
    static const char *fnName = "glVertex4hNV";

    beforeCommand(fnName, _api.glVertex4h);
    _api.glVertex4h(x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertex4hvNV().
void NVHalfFloatAPI::vertex4HV(const GLhalfNV *v) const
{
    static const char *fnName = "glVertex4hvNV";

    beforeCommand(fnName, _api.glVertex4hv);
    _api.glVertex4hv(v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1hNV().
void NVHalfFloatAPI::vertexAttrib1H(GLuint index, GLhalfNV x) const
{
    static const char *fnName = "glVertexAttrib1hNV";

    beforeCommand(fnName, _api.glVertexAttrib1h);
    _api.glVertexAttrib1h(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1hvNV().
void NVHalfFloatAPI::vertexAttrib1HV(GLuint index, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttrib1hvNV";

    beforeCommand(fnName, _api.glVertexAttrib1hv);
    _api.glVertexAttrib1hv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2hNV().
void NVHalfFloatAPI::vertexAttrib2H(GLuint index, GLhalfNV x, GLhalfNV y) const
{
    static const char *fnName = "glVertexAttrib2hNV";

    beforeCommand(fnName, _api.glVertexAttrib2h);
    _api.glVertexAttrib2h(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2hvNV().
void NVHalfFloatAPI::vertexAttrib2HV(GLuint index, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttrib2hvNV";

    beforeCommand(fnName, _api.glVertexAttrib2hv);
    _api.glVertexAttrib2hv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3hNV().
void NVHalfFloatAPI::vertexAttrib3H(GLuint index, GLhalfNV x, GLhalfNV y,
                                    GLhalfNV z) const
{
    static const char *fnName = "glVertexAttrib3hNV";

    beforeCommand(fnName, _api.glVertexAttrib3h);
    _api.glVertexAttrib3h(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3hvNV().
void NVHalfFloatAPI::vertexAttrib3HV(GLuint index, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttrib3hvNV";

    beforeCommand(fnName, _api.glVertexAttrib3hv);
    _api.glVertexAttrib3hv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4hNV().
void NVHalfFloatAPI::vertexAttrib4H(GLuint index, GLhalfNV x, GLhalfNV y,
                                    GLhalfNV z, GLhalfNV w) const
{
    static const char *fnName = "glVertexAttrib4hNV";

    beforeCommand(fnName, _api.glVertexAttrib4h);
    _api.glVertexAttrib4h(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4hvNV().
void NVHalfFloatAPI::vertexAttrib4HV(GLuint index, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttrib4hvNV";

    beforeCommand(fnName, _api.glVertexAttrib4hv);
    _api.glVertexAttrib4hv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs1hvNV().
void NVHalfFloatAPI::vertexAttribs1HV(GLuint index, GLsizei n, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttribs1hvNV";

    beforeCommand(fnName, _api.glVertexAttribs1hv);
    _api.glVertexAttribs1hv(index, n, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs2hvNV().
void NVHalfFloatAPI::vertexAttribs2HV(GLuint index, GLsizei n, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttribs2hvNV";

    beforeCommand(fnName, _api.glVertexAttribs2hv);
    _api.glVertexAttribs2hv(index, n, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs3hvNV().
void NVHalfFloatAPI::vertexAttribs3HV(GLuint index, GLsizei n, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttribs3hvNV";

    beforeCommand(fnName, _api.glVertexAttribs3hv);
    _api.glVertexAttribs3hv(index, n, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs4hvNV().
void NVHalfFloatAPI::vertexAttribs4HV(GLuint index, GLsizei n, const GLhalfNV *v) const
{
    static const char *fnName = "glVertexAttribs4hvNV";

    beforeCommand(fnName, _api.glVertexAttribs4hv);
    _api.glVertexAttribs4hv(index, n, v);
    afterCommand(fnName);
}

// Calls glVertexWeighthNV().
void NVHalfFloatAPI::vertexWeighth(GLhalfNV weight) const
{
    static const char *fnName = "glVertexWeighthNV";

    beforeCommand(fnName, _api.glVertexWeighth);
    _api.glVertexWeighth(weight);
    afterCommand(fnName);
}

// Calls glVertexWeighthvNV().
void NVHalfFloatAPI::vertexWeighthV(const GLhalfNV *weight) const
{
    static const char *fnName = "glVertexWeighthvNV";

    beforeCommand(fnName, _api.glVertexWeighthv);
    _api.glVertexWeighthv(weight);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVInternalformatSampleQueryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_internalformat_sample_query extension.
NVInternalformatSampleQueryAPI::NVInternalformatSampleQueryAPI() :
    BaseExtension("GL_NV_internalformat_sample_query")
{
}

// Grant read-only access to the underlying function pointers.
const NVInternalformatSampleQuery &NVInternalformatSampleQueryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_internalformat_sample_query entry points.
void NVInternalformatSampleQueryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetInternalformatSampleivNV().
void NVInternalformatSampleQueryAPI::getInternalformatSampleIV(TextureTarget target,
                                                               InternalFormat internalformat,
                                                               GLsizei samples,
                                                               InternalFormatPName pname,
                                                               GLsizei count,
                                                               GLint *params) const
{
    static const char *fnName = "glGetInternalformatSampleivNV";

    beforeCommand(fnName, _api.glGetInternalformatSampleiv);
    _api.glGetInternalformatSampleiv(toScalar(target), toScalar(internalformat),
                                     samples, toScalar(pname), count, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVMemoryAttachmentAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_memory_attachment extension.
NVMemoryAttachmentAPI::NVMemoryAttachmentAPI() :
    BaseExtension("GL_NV_memory_attachment")
{
}

// Grant read-only access to the underlying function pointers.
const NVMemoryAttachment &NVMemoryAttachmentAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_memory_attachment entry points.
void NVMemoryAttachmentAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferAttachMemoryNV().
void NVMemoryAttachmentAPI::bufferAttachMemory(BufferTargetARB target,
                                               GLuint memory, GLuint64 offset) const
{
    static const char *fnName = "glBufferAttachMemoryNV";

    beforeCommand(fnName, _api.glBufferAttachMemory);
    _api.glBufferAttachMemory(toScalar(target), memory, offset);
    afterCommand(fnName);
}

// Calls glGetMemoryObjectDetachedResourcesuivNV().
void NVMemoryAttachmentAPI::getMemoryObjectDetachedResourcesuiv(GLuint memory,
                                                                GLenum pname,
                                                                GLint first,
                                                                GLsizei count,
                                                                GLuint *params) const
{
    static const char *fnName = "glGetMemoryObjectDetachedResourcesuivNV";

    beforeCommand(fnName, _api.glGetMemoryObjectDetachedResourcesuiv);
    _api.glGetMemoryObjectDetachedResourcesuiv(memory, pname, first, count,
                                               params);
    afterCommand(fnName);
}

// Calls glNamedBufferAttachMemoryNV().
void NVMemoryAttachmentAPI::namedBufferAttachMemory(BufferName buffer,
                                                    GLuint memory,
                                                    GLuint64 offset) const
{
    static const char *fnName = "glNamedBufferAttachMemoryNV";

    beforeCommand(fnName, _api.glNamedBufferAttachMemory);
    _api.glNamedBufferAttachMemory(buffer.ID, memory, offset);
    afterCommand(fnName);
}

// Calls glResetMemoryObjectParameterNV().
void NVMemoryAttachmentAPI::resetMemoryObjectParameter(GLuint memory,
                                                       GLenum pname) const
{
    static const char *fnName = "glResetMemoryObjectParameterNV";

    beforeCommand(fnName, _api.glResetMemoryObjectParameter);
    _api.glResetMemoryObjectParameter(memory, pname);
    afterCommand(fnName);
}

// Calls glTexAttachMemoryNV().
void NVMemoryAttachmentAPI::texAttachMemory(TextureTarget target, GLuint memory,
                                            GLuint64 offset) const
{
    static const char *fnName = "glTexAttachMemoryNV";

    beforeCommand(fnName, _api.glTexAttachMemory);
    _api.glTexAttachMemory(toScalar(target), memory, offset);
    afterCommand(fnName);
}

// Calls glTextureAttachMemoryNV().
void NVMemoryAttachmentAPI::textureAttachMemory(TextureName texture,
                                                GLuint memory, GLuint64 offset) const
{
    static const char *fnName = "glTextureAttachMemoryNV";

    beforeCommand(fnName, _api.glTextureAttachMemory);
    _api.glTextureAttachMemory(texture.ID, memory, offset);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVMemoryObjectSparseAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_memory_object_sparse extension.
NVMemoryObjectSparseAPI::NVMemoryObjectSparseAPI() :
    BaseExtension("GL_NV_memory_object_sparse")
{
}

// Grant read-only access to the underlying function pointers.
const NVMemoryObjectSparse &NVMemoryObjectSparseAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_memory_object_sparse entry points.
void NVMemoryObjectSparseAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferPageCommitmentMemNV().
void NVMemoryObjectSparseAPI::bufferPageCommitmentMem(BufferStorageTarget target,
                                                      GLintptr offset,
                                                      GLsizeiptr size,
                                                      GLuint memory,
                                                      GLuint64 memOffset,
                                                      Boolean commit) const
{
    static const char *fnName = "glBufferPageCommitmentMemNV";

    beforeCommand(fnName, _api.glBufferPageCommitmentMem);
    _api.glBufferPageCommitmentMem(toScalar(target), offset, size, memory,
                                   memOffset, toScalar(commit));
    afterCommand(fnName);
}

// Calls glNamedBufferPageCommitmentMemNV().
void NVMemoryObjectSparseAPI::namedBufferPageCommitmentMem(BufferName buffer,
                                                           GLintptr offset,
                                                           GLsizeiptr size,
                                                           GLuint memory,
                                                           GLuint64 memOffset,
                                                           Boolean commit) const
{
    static const char *fnName = "glNamedBufferPageCommitmentMemNV";

    beforeCommand(fnName, _api.glNamedBufferPageCommitmentMem);
    _api.glNamedBufferPageCommitmentMem(buffer.ID, offset, size, memory,
                                        memOffset, toScalar(commit));
    afterCommand(fnName);
}

// Calls glTexPageCommitmentMemNV().
void NVMemoryObjectSparseAPI::texPageCommitmentMem(TextureTarget target,
                                                   GLint layer, GLint level,
                                                   GLint xoffset, GLint yoffset,
                                                   GLint zoffset, GLsizei width,
                                                   GLsizei height, GLsizei depth,
                                                   GLuint memory,
                                                   GLuint64 offset,
                                                   Boolean commit) const
{
    static const char *fnName = "glTexPageCommitmentMemNV";

    beforeCommand(fnName, _api.glTexPageCommitmentMem);
    _api.glTexPageCommitmentMem(toScalar(target), layer, level, xoffset, yoffset,
                                zoffset, width, height, depth, memory, offset,
                                toScalar(commit));
    afterCommand(fnName);
}

// Calls glTexturePageCommitmentMemNV().
void NVMemoryObjectSparseAPI::texturePageCommitmentMem(TextureName texture,
                                                       GLint layer, GLint level,
                                                       GLint xoffset,
                                                       GLint yoffset,
                                                       GLint zoffset,
                                                       GLsizei width,
                                                       GLsizei height,
                                                       GLsizei depth,
                                                       GLuint memory,
                                                       GLuint64 offset,
                                                       Boolean commit) const
{
    static const char *fnName = "glTexturePageCommitmentMemNV";

    beforeCommand(fnName, _api.glTexturePageCommitmentMem);
    _api.glTexturePageCommitmentMem(texture.ID, layer, level, xoffset, yoffset,
                                    zoffset, width, height, depth, memory,
                                    offset, toScalar(commit));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVMeshShaderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_mesh_shader extension.
NVMeshShaderAPI::NVMeshShaderAPI() :
    BaseExtension("GL_NV_mesh_shader")
{
}

// Grant read-only access to the underlying function pointers.
const NVMeshShader &NVMeshShaderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_mesh_shader entry points.
void NVMeshShaderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawMeshTasksIndirectNV().
void NVMeshShaderAPI::drawMeshTasksIndirect(GLintptr indirect) const
{
    static const char *fnName = "glDrawMeshTasksIndirectNV";

    beforeCommand(fnName, _api.glDrawMeshTasksIndirect);
    _api.glDrawMeshTasksIndirect(indirect);
    afterCommand(fnName);
}

// Calls glDrawMeshTasksNV().
void NVMeshShaderAPI::drawMeshTasks(GLuint first, GLuint count) const
{
    static const char *fnName = "glDrawMeshTasksNV";

    beforeCommand(fnName, _api.glDrawMeshTasks);
    _api.glDrawMeshTasks(first, count);
    afterCommand(fnName);
}

// Calls glMultiDrawMeshTasksIndirectCountNV().
void NVMeshShaderAPI::multiDrawMeshTasksIndirectCount(GLintptr indirect,
                                                      GLintptr drawcount,
                                                      GLsizei maxdrawcount,
                                                      GLsizei stride) const
{
    static const char *fnName = "glMultiDrawMeshTasksIndirectCountNV";

    beforeCommand(fnName, _api.glMultiDrawMeshTasksIndirectCount);
    _api.glMultiDrawMeshTasksIndirectCount(indirect, drawcount, maxdrawcount,
                                           stride);
    afterCommand(fnName);
}

// Calls glMultiDrawMeshTasksIndirectNV().
void NVMeshShaderAPI::multiDrawMeshTasksIndirect(GLintptr indirect,
                                                 GLsizei drawcount,
                                                 GLsizei stride) const
{
    static const char *fnName = "glMultiDrawMeshTasksIndirectNV";

    beforeCommand(fnName, _api.glMultiDrawMeshTasksIndirect);
    _api.glMultiDrawMeshTasksIndirect(indirect, drawcount, stride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVOcclusionQueryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_occlusion_query extension.
NVOcclusionQueryAPI::NVOcclusionQueryAPI() :
    BaseExtension("GL_NV_occlusion_query")
{
}

// Grant read-only access to the underlying function pointers.
const NVOcclusionQuery &NVOcclusionQueryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_occlusion_query entry points.
void NVOcclusionQueryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginOcclusionQueryNV().
void NVOcclusionQueryAPI::beginOcclusionQuery(GLuint id) const
{
    static const char *fnName = "glBeginOcclusionQueryNV";

    beforeCommand(fnName, _api.glBeginOcclusionQuery);
    _api.glBeginOcclusionQuery(id);
    afterCommand(fnName);
}

// Calls glDeleteOcclusionQueriesNV().
void NVOcclusionQueryAPI::deleteOcclusionQueries(GLsizei n, const GLuint *ids) const
{
    static const char *fnName = "glDeleteOcclusionQueriesNV";

    beforeCommand(fnName, _api.glDeleteOcclusionQueries);
    _api.glDeleteOcclusionQueries(n, ids);
    afterCommand(fnName);
}

// Calls glEndOcclusionQueryNV().
void NVOcclusionQueryAPI::endOcclusionQuery() const
{
    static const char *fnName = "glEndOcclusionQueryNV";

    beforeCommand(fnName, _api.glEndOcclusionQuery);
    _api.glEndOcclusionQuery();
    afterCommand(fnName);
}

// Calls glGenOcclusionQueriesNV().
void NVOcclusionQueryAPI::genOcclusionQueries(GLsizei n, GLuint *ids) const
{
    static const char *fnName = "glGenOcclusionQueriesNV";

    beforeCommand(fnName, _api.glGenOcclusionQueries);
    _api.glGenOcclusionQueries(n, ids);
    afterCommand(fnName);
}

// Calls glGetOcclusionQueryivNV().
void NVOcclusionQueryAPI::getOcclusionQueryIV(GLuint id,
                                              OcclusionQueryParameterNameNV pname,
                                              GLint *params) const
{
    static const char *fnName = "glGetOcclusionQueryivNV";

    beforeCommand(fnName, _api.glGetOcclusionQueryiv);
    _api.glGetOcclusionQueryiv(id, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetOcclusionQueryuivNV().
void NVOcclusionQueryAPI::getOcclusionQueryUIV(GLuint id,
                                               OcclusionQueryParameterNameNV pname,
                                               GLuint *params) const
{
    static const char *fnName = "glGetOcclusionQueryuivNV";

    beforeCommand(fnName, _api.glGetOcclusionQueryuiv);
    _api.glGetOcclusionQueryuiv(id, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsOcclusionQueryNV().
Boolean NVOcclusionQueryAPI::isOcclusionQuery(GLuint id) const
{
    static const char *fnName = "glIsOcclusionQueryNV";

    beforeCommand(fnName, _api.glIsOcclusionQuery);
    GLboolean result = _api.glIsOcclusionQuery(id);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// NVParameterBufferObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_parameter_buffer_object extension.
NVParameterBufferObjectAPI::NVParameterBufferObjectAPI() :
    BaseExtension("GL_NV_parameter_buffer_object")
{
}

// Grant read-only access to the underlying function pointers.
const NVParameterBufferObject &NVParameterBufferObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_parameter_buffer_object entry points.
void NVParameterBufferObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glProgramBufferParametersIivNV().
void NVParameterBufferObjectAPI::programBufferParametersIIV(ProgramTarget target,
                                                            GLuint bindingIndex,
                                                            GLuint wordIndex,
                                                            GLsizei count,
                                                            const GLint *params) const
{
    static const char *fnName = "glProgramBufferParametersIivNV";

    beforeCommand(fnName, _api.glProgramBufferParametersIiv);
    _api.glProgramBufferParametersIiv(toScalar(target), bindingIndex, wordIndex,
                                      count, params);
    afterCommand(fnName);
}

// Calls glProgramBufferParametersIuivNV().
void NVParameterBufferObjectAPI::programBufferParametersIUIV(ProgramTarget target,
                                                             GLuint bindingIndex,
                                                             GLuint wordIndex,
                                                             GLsizei count,
                                                             const GLuint *params) const
{
    static const char *fnName = "glProgramBufferParametersIuivNV";

    beforeCommand(fnName, _api.glProgramBufferParametersIuiv);
    _api.glProgramBufferParametersIuiv(toScalar(target), bindingIndex, wordIndex,
                                       count, params);
    afterCommand(fnName);
}

// Calls glProgramBufferParametersfvNV().
void NVParameterBufferObjectAPI::programBufferParametersFV(ProgramTarget target,
                                                           GLuint bindingIndex,
                                                           GLuint wordIndex,
                                                           GLsizei count,
                                                           const GLfloat *params) const
{
    static const char *fnName = "glProgramBufferParametersfvNV";

    beforeCommand(fnName, _api.glProgramBufferParametersfv);
    _api.glProgramBufferParametersfv(toScalar(target), bindingIndex, wordIndex,
                                     count, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVPathRenderingAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_path_rendering extension.
NVPathRenderingAPI::NVPathRenderingAPI() :
    BaseExtension("GL_NV_path_rendering")
{
}

// Grant read-only access to the underlying function pointers.
const NVPathRendering &NVPathRenderingAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_path_rendering entry points.
void NVPathRenderingAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCopyPathNV().
void NVPathRenderingAPI::copyPath(GLuint resultPath, GLuint srcPath) const
{
    static const char *fnName = "glCopyPathNV";

    beforeCommand(fnName, _api.glCopyPath);
    _api.glCopyPath(resultPath, srcPath);
    afterCommand(fnName);
}

// Calls glCoverFillPathInstancedNV().
void NVPathRenderingAPI::coverFillPathInstanced(GLsizei numPaths,
                                                PathElementType pathNameType,
                                                const void *paths,
                                                GLuint pathBase,
                                                PathCoverMode coverMode,
                                                PathTransformType transformType,
                                                const GLfloat *transformValues) const
{
    static const char *fnName = "glCoverFillPathInstancedNV";

    beforeCommand(fnName, _api.glCoverFillPathInstanced);
    _api.glCoverFillPathInstanced(numPaths, toScalar(pathNameType), paths,
                                  pathBase, toScalar(coverMode),
                                  toScalar(transformType), transformValues);
    afterCommand(fnName);
}

// Calls glCoverFillPathNV().
void NVPathRenderingAPI::coverFillPath(GLuint path, PathCoverMode coverMode) const
{
    static const char *fnName = "glCoverFillPathNV";

    beforeCommand(fnName, _api.glCoverFillPath);
    _api.glCoverFillPath(path, toScalar(coverMode));
    afterCommand(fnName);
}

// Calls glCoverStrokePathInstancedNV().
void NVPathRenderingAPI::coverStrokePathInstanced(GLsizei numPaths,
                                                  PathElementType pathNameType,
                                                  const void *paths,
                                                  GLuint pathBase,
                                                  PathCoverMode coverMode,
                                                  PathTransformType transformType,
                                                  const GLfloat *transformValues) const
{
    static const char *fnName = "glCoverStrokePathInstancedNV";

    beforeCommand(fnName, _api.glCoverStrokePathInstanced);
    _api.glCoverStrokePathInstanced(numPaths, toScalar(pathNameType), paths,
                                    pathBase, toScalar(coverMode),
                                    toScalar(transformType), transformValues);
    afterCommand(fnName);
}

// Calls glCoverStrokePathNV().
void NVPathRenderingAPI::coverStrokePath(GLuint path, PathCoverMode coverMode) const
{
    static const char *fnName = "glCoverStrokePathNV";

    beforeCommand(fnName, _api.glCoverStrokePath);
    _api.glCoverStrokePath(path, toScalar(coverMode));
    afterCommand(fnName);
}

// Calls glDeletePathsNV().
void NVPathRenderingAPI::deletePaths(GLuint path, GLsizei range) const
{
    static const char *fnName = "glDeletePathsNV";

    beforeCommand(fnName, _api.glDeletePaths);
    _api.glDeletePaths(path, range);
    afterCommand(fnName);
}

// Calls glGenPathsNV().
GLuint NVPathRenderingAPI::genPaths(GLsizei range) const
{
    static const char *fnName = "glGenPathsNV";

    beforeCommand(fnName, _api.glGenPaths);
    GLuint result = _api.glGenPaths(range);
    afterCommand(fnName);

    return result;
}

// Calls glGetPathCommandsNV().
void NVPathRenderingAPI::getPathCommands(GLuint path, GLubyte *commands) const
{
    static const char *fnName = "glGetPathCommandsNV";

    beforeCommand(fnName, _api.glGetPathCommands);
    _api.glGetPathCommands(path, commands);
    afterCommand(fnName);
}

// Calls glGetPathCoordsNV().
void NVPathRenderingAPI::getPathCoords(GLuint path, GLfloat *coords) const
{
    static const char *fnName = "glGetPathCoordsNV";

    beforeCommand(fnName, _api.glGetPathCoords);
    _api.glGetPathCoords(path, coords);
    afterCommand(fnName);
}

// Calls glGetPathDashArrayNV().
void NVPathRenderingAPI::getPathDashArray(GLuint path, GLfloat *dashArray) const
{
    static const char *fnName = "glGetPathDashArrayNV";

    beforeCommand(fnName, _api.glGetPathDashArray);
    _api.glGetPathDashArray(path, dashArray);
    afterCommand(fnName);
}

// Calls glGetPathLengthNV().
GLfloat NVPathRenderingAPI::getPathLength(GLuint path, GLsizei startSegment,
                                          GLsizei numSegments) const
{
    static const char *fnName = "glGetPathLengthNV";

    beforeCommand(fnName, _api.glGetPathLength);
    GLfloat result = _api.glGetPathLength(path, startSegment, numSegments);
    afterCommand(fnName);

    return result;
}

// Calls glGetPathMetricRangeNV().
void NVPathRenderingAPI::getPathMetricRange(GLbitfield  /* PathMetricMask */ metricQueryMask,
                                            GLuint firstPathName,
                                            GLsizei numPaths, GLsizei stride,
                                            GLfloat *metrics) const
{
    static const char *fnName = "glGetPathMetricRangeNV";

    beforeCommand(fnName, _api.glGetPathMetricRange);
    _api.glGetPathMetricRange(metricQueryMask, firstPathName, numPaths, stride,
                              metrics);
    afterCommand(fnName);
}

// Calls glGetPathMetricsNV().
void NVPathRenderingAPI::getPathMetrics(GLbitfield  /* PathMetricMask */ metricQueryMask,
                                        GLsizei numPaths,
                                        PathElementType pathNameType,
                                        const void *paths, GLuint pathBase,
                                        GLsizei stride, GLfloat *metrics) const
{
    static const char *fnName = "glGetPathMetricsNV";

    beforeCommand(fnName, _api.glGetPathMetrics);
    _api.glGetPathMetrics(metricQueryMask, numPaths, toScalar(pathNameType),
                          paths, pathBase, stride, metrics);
    afterCommand(fnName);
}

// Calls glGetPathParameterfvNV().
void NVPathRenderingAPI::getPathParameterFV(GLuint path, PathParameter pname,
                                            GLfloat *value) const
{
    static const char *fnName = "glGetPathParameterfvNV";

    beforeCommand(fnName, _api.glGetPathParameterfv);
    _api.glGetPathParameterfv(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glGetPathParameterivNV().
void NVPathRenderingAPI::getPathParameterIV(GLuint path, PathParameter pname,
                                            GLint *value) const
{
    static const char *fnName = "glGetPathParameterivNV";

    beforeCommand(fnName, _api.glGetPathParameteriv);
    _api.glGetPathParameteriv(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glGetPathSpacingNV().
void NVPathRenderingAPI::getPathSpacing(PathListMode pathListMode,
                                        GLsizei numPaths,
                                        PathElementType pathNameType,
                                        const void *paths, GLuint pathBase,
                                        GLfloat advanceScale,
                                        GLfloat kerningScale,
                                        PathTransformType transformType,
                                        GLfloat *returnedSpacing) const
{
    static const char *fnName = "glGetPathSpacingNV";

    beforeCommand(fnName, _api.glGetPathSpacing);
    _api.glGetPathSpacing(toScalar(pathListMode), numPaths,
                          toScalar(pathNameType), paths, pathBase, advanceScale,
                          kerningScale, toScalar(transformType), returnedSpacing);
    afterCommand(fnName);
}

// Calls glGetProgramResourcefvNV().
void NVPathRenderingAPI::getProgramResourceFV(ProgramName program,
                                              ProgramInterface programInterface,
                                              GLuint index, GLsizei propCount,
                                              const GLenum *props, GLsizei count,
                                              GLsizei *length, GLfloat *params) const
{
    static const char *fnName = "glGetProgramResourcefvNV";

    beforeCommand(fnName, _api.glGetProgramResourcefv);
    _api.glGetProgramResourcefv(program.ID, toScalar(programInterface), index,
                                propCount, props, count, length, params);
    afterCommand(fnName);
}

// Calls glInterpolatePathsNV().
void NVPathRenderingAPI::interpolatePaths(GLuint resultPath, GLuint pathA,
                                          GLuint pathB, GLfloat weight) const
{
    static const char *fnName = "glInterpolatePathsNV";

    beforeCommand(fnName, _api.glInterpolatePaths);
    _api.glInterpolatePaths(resultPath, pathA, pathB, weight);
    afterCommand(fnName);
}

// Calls glIsPathNV().
Boolean NVPathRenderingAPI::isPath(GLuint path) const
{
    static const char *fnName = "glIsPathNV";

    beforeCommand(fnName, _api.glIsPath);
    GLboolean result = _api.glIsPath(path);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsPointInFillPathNV().
Boolean NVPathRenderingAPI::isPointInFillPath(GLuint path, GLuint mask,
                                              GLfloat x, GLfloat y) const
{
    static const char *fnName = "glIsPointInFillPathNV";

    beforeCommand(fnName, _api.glIsPointInFillPath);
    GLboolean result = _api.glIsPointInFillPath(path, mask, x, y);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsPointInStrokePathNV().
Boolean NVPathRenderingAPI::isPointInStrokePath(GLuint path, GLfloat x,
                                                GLfloat y) const
{
    static const char *fnName = "glIsPointInStrokePathNV";

    beforeCommand(fnName, _api.glIsPointInStrokePath);
    GLboolean result = _api.glIsPointInStrokePath(path, x, y);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMatrixLoad3x2fNV().
void NVPathRenderingAPI::matrixLoad3x2F(GLenum matrixMode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixLoad3x2fNV";

    beforeCommand(fnName, _api.glMatrixLoad3x2f);
    _api.glMatrixLoad3x2f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glMatrixLoad3x3fNV().
void NVPathRenderingAPI::matrixLoad3x3F(GLenum matrixMode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixLoad3x3fNV";

    beforeCommand(fnName, _api.glMatrixLoad3x3f);
    _api.glMatrixLoad3x3f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glMatrixLoadTranspose3x3fNV().
void NVPathRenderingAPI::matrixLoadTranspose3x3F(GLenum matrixMode,
                                                 const GLfloat *m) const
{
    static const char *fnName = "glMatrixLoadTranspose3x3fNV";

    beforeCommand(fnName, _api.glMatrixLoadTranspose3x3f);
    _api.glMatrixLoadTranspose3x3f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glMatrixMult3x2fNV().
void NVPathRenderingAPI::matrixMult3x2F(GLenum matrixMode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixMult3x2fNV";

    beforeCommand(fnName, _api.glMatrixMult3x2f);
    _api.glMatrixMult3x2f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glMatrixMult3x3fNV().
void NVPathRenderingAPI::matrixMult3x3F(GLenum matrixMode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixMult3x3fNV";

    beforeCommand(fnName, _api.glMatrixMult3x3f);
    _api.glMatrixMult3x3f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glMatrixMultTranspose3x3fNV().
void NVPathRenderingAPI::matrixMultTranspose3x3F(GLenum matrixMode,
                                                 const GLfloat *m) const
{
    static const char *fnName = "glMatrixMultTranspose3x3fNV";

    beforeCommand(fnName, _api.glMatrixMultTranspose3x3f);
    _api.glMatrixMultTranspose3x3f(matrixMode, m);
    afterCommand(fnName);
}

// Calls glPathCommandsNV().
void NVPathRenderingAPI::pathCommands(GLuint path, GLsizei numCommands,
                                      const GLubyte *commands, GLsizei numCoords,
                                      PathCoordType coordType,
                                      const void *coords) const
{
    static const char *fnName = "glPathCommandsNV";

    beforeCommand(fnName, _api.glPathCommands);
    _api.glPathCommands(path, numCommands, commands, numCoords,
                        toScalar(coordType), coords);
    afterCommand(fnName);
}

// Calls glPathCoordsNV().
void NVPathRenderingAPI::pathCoords(GLuint path, GLsizei numCoords,
                                    PathCoordType coordType, const void *coords) const
{
    static const char *fnName = "glPathCoordsNV";

    beforeCommand(fnName, _api.glPathCoords);
    _api.glPathCoords(path, numCoords, toScalar(coordType), coords);
    afterCommand(fnName);
}

// Calls glPathCoverDepthFuncNV().
void NVPathRenderingAPI::pathCoverDepthFunc(DepthFunction func) const
{
    static const char *fnName = "glPathCoverDepthFuncNV";

    beforeCommand(fnName, _api.glPathCoverDepthFunc);
    _api.glPathCoverDepthFunc(toScalar(func));
    afterCommand(fnName);
}

// Calls glPathDashArrayNV().
void NVPathRenderingAPI::pathDashArray(GLuint path, GLsizei dashCount,
                                       const GLfloat *dashArray) const
{
    static const char *fnName = "glPathDashArrayNV";

    beforeCommand(fnName, _api.glPathDashArray);
    _api.glPathDashArray(path, dashCount, dashArray);
    afterCommand(fnName);
}

// Calls glPathGlyphIndexArrayNV().
GLenum NVPathRenderingAPI::pathGlyphIndexArray(GLuint firstPathName,
                                               GLenum fontTarget,
                                               const void *fontName,
                                               GLbitfield  /* PathFontStyle */ fontStyle,
                                               GLuint firstGlyphIndex,
                                               GLsizei numGlyphs,
                                               GLuint pathParameterTemplate,
                                               GLfloat emScale) const
{
    static const char *fnName = "glPathGlyphIndexArrayNV";

    beforeCommand(fnName, _api.glPathGlyphIndexArray);
    GLenum result = _api.glPathGlyphIndexArray(firstPathName, fontTarget,
                                               fontName, fontStyle,
                                               firstGlyphIndex, numGlyphs,
                                               pathParameterTemplate, emScale);
    afterCommand(fnName);

    return result;
}

// Calls glPathGlyphIndexRangeNV().
GLenum NVPathRenderingAPI::pathGlyphIndexRange(GLenum fontTarget,
                                               const void *fontName,
                                               GLbitfield  /* PathFontStyle */ fontStyle,
                                               GLuint pathParameterTemplate,
                                               GLfloat emScale,
                                               GLuint *baseAndCount) const
{
    static const char *fnName = "glPathGlyphIndexRangeNV";

    beforeCommand(fnName, _api.glPathGlyphIndexRange);
    GLenum result = _api.glPathGlyphIndexRange(fontTarget, fontName, fontStyle,
                                               pathParameterTemplate, emScale,
                                               baseAndCount);
    afterCommand(fnName);

    return result;
}

// Calls glPathGlyphRangeNV().
void NVPathRenderingAPI::pathGlyphRange(GLuint firstPathName,
                                        PathFontTarget fontTarget,
                                        const void *fontName,
                                        GLbitfield  /* PathFontStyle */ fontStyle,
                                        GLuint firstGlyph, GLsizei numGlyphs,
                                        PathHandleMissingGlyphs handleMissingGlyphs,
                                        GLuint pathParameterTemplate,
                                        GLfloat emScale) const
{
    static const char *fnName = "glPathGlyphRangeNV";

    beforeCommand(fnName, _api.glPathGlyphRange);
    _api.glPathGlyphRange(firstPathName, toScalar(fontTarget), fontName,
                          fontStyle, firstGlyph, numGlyphs,
                          toScalar(handleMissingGlyphs), pathParameterTemplate,
                          emScale);
    afterCommand(fnName);
}

// Calls glPathGlyphsNV().
void NVPathRenderingAPI::pathGlyphs(GLuint firstPathName,
                                    PathFontTarget fontTarget,
                                    const void *fontName,
                                    GLbitfield  /* PathFontStyle */ fontStyle,
                                    GLsizei numGlyphs, PathElementType type,
                                    const void *charcodes,
                                    PathHandleMissingGlyphs handleMissingGlyphs,
                                    GLuint pathParameterTemplate,
                                    GLfloat emScale) const
{
    static const char *fnName = "glPathGlyphsNV";

    beforeCommand(fnName, _api.glPathGlyphs);
    _api.glPathGlyphs(firstPathName, toScalar(fontTarget), fontName, fontStyle,
                      numGlyphs, toScalar(type), charcodes,
                      toScalar(handleMissingGlyphs), pathParameterTemplate,
                      emScale);
    afterCommand(fnName);
}

// Calls glPathMemoryGlyphIndexArrayNV().
GLenum NVPathRenderingAPI::pathMemoryGlyphIndexArray(GLuint firstPathName,
                                                     GLenum fontTarget,
                                                     GLsizeiptr fontSize,
                                                     const void *fontData,
                                                     GLsizei faceIndex,
                                                     GLuint firstGlyphIndex,
                                                     GLsizei numGlyphs,
                                                     GLuint pathParameterTemplate,
                                                     GLfloat emScale) const
{
    static const char *fnName = "glPathMemoryGlyphIndexArrayNV";

    beforeCommand(fnName, _api.glPathMemoryGlyphIndexArray);
    GLenum result = _api.glPathMemoryGlyphIndexArray(firstPathName, fontTarget,
                                                     fontSize, fontData,
                                                     faceIndex, firstGlyphIndex,
                                                     numGlyphs,
                                                     pathParameterTemplate,
                                                     emScale);
    afterCommand(fnName);

    return result;
}

// Calls glPathParameterfNV().
void NVPathRenderingAPI::pathParameterF(GLuint path, PathParameter pname,
                                        GLfloat value) const
{
    static const char *fnName = "glPathParameterfNV";

    beforeCommand(fnName, _api.glPathParameterf);
    _api.glPathParameterf(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glPathParameterfvNV().
void NVPathRenderingAPI::pathParameterFV(GLuint path, PathParameter pname,
                                         const GLfloat *value) const
{
    static const char *fnName = "glPathParameterfvNV";

    beforeCommand(fnName, _api.glPathParameterfv);
    _api.glPathParameterfv(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glPathParameteriNV().
void NVPathRenderingAPI::pathParameterI(GLuint path, PathParameter pname,
                                        GLint value) const
{
    static const char *fnName = "glPathParameteriNV";

    beforeCommand(fnName, _api.glPathParameteri);
    _api.glPathParameteri(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glPathParameterivNV().
void NVPathRenderingAPI::pathParameterIV(GLuint path, PathParameter pname,
                                         const GLint *value) const
{
    static const char *fnName = "glPathParameterivNV";

    beforeCommand(fnName, _api.glPathParameteriv);
    _api.glPathParameteriv(path, toScalar(pname), value);
    afterCommand(fnName);
}

// Calls glPathStencilDepthOffsetNV().
void NVPathRenderingAPI::pathStencilDepthOffset(GLfloat factor, GLfloat units) const
{
    static const char *fnName = "glPathStencilDepthOffsetNV";

    beforeCommand(fnName, _api.glPathStencilDepthOffset);
    _api.glPathStencilDepthOffset(factor, units);
    afterCommand(fnName);
}

// Calls glPathStencilFuncNV().
void NVPathRenderingAPI::pathStencilFunc(StencilFunction func, GLint ref,
                                         GLuint mask) const
{
    static const char *fnName = "glPathStencilFuncNV";

    beforeCommand(fnName, _api.glPathStencilFunc);
    _api.glPathStencilFunc(toScalar(func), ref, mask);
    afterCommand(fnName);
}

// Calls glPathStringNV().
void NVPathRenderingAPI::pathString(GLuint path, PathStringFormat format,
                                    GLsizei length, const void *pathString) const
{
    static const char *fnName = "glPathStringNV";

    beforeCommand(fnName, _api.glPathString);
    _api.glPathString(path, toScalar(format), length, pathString);
    afterCommand(fnName);
}

// Calls glPathSubCommandsNV().
void NVPathRenderingAPI::pathSubCommands(GLuint path, GLsizei commandStart,
                                         GLsizei commandsToDelete,
                                         GLsizei numCommands,
                                         const GLubyte *commands,
                                         GLsizei numCoords,
                                         PathCoordType coordType,
                                         const void *coords) const
{
    static const char *fnName = "glPathSubCommandsNV";

    beforeCommand(fnName, _api.glPathSubCommands);
    _api.glPathSubCommands(path, commandStart, commandsToDelete, numCommands,
                           commands, numCoords, toScalar(coordType), coords);
    afterCommand(fnName);
}

// Calls glPathSubCoordsNV().
void NVPathRenderingAPI::pathSubCoords(GLuint path, GLsizei coordStart,
                                       GLsizei numCoords,
                                       PathCoordType coordType,
                                       const void *coords) const
{
    static const char *fnName = "glPathSubCoordsNV";

    beforeCommand(fnName, _api.glPathSubCoords);
    _api.glPathSubCoords(path, coordStart, numCoords, toScalar(coordType),
                         coords);
    afterCommand(fnName);
}

// Calls glPointAlongPathNV().
Boolean NVPathRenderingAPI::pointAlongPath(GLuint path, GLsizei startSegment,
                                           GLsizei numSegments, GLfloat distance,
                                           GLfloat *x, GLfloat *y,
                                           GLfloat *tangentX, GLfloat *tangentY) const
{
    static const char *fnName = "glPointAlongPathNV";

    beforeCommand(fnName, _api.glPointAlongPath);
    GLboolean result = _api.glPointAlongPath(path, startSegment, numSegments,
                                             distance, x, y, tangentX, tangentY);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glProgramPathFragmentInputGenNV().
void NVPathRenderingAPI::programPathFragmentInputGen(ProgramName program,
                                                     GLint location,
                                                     GLenum genMode,
                                                     GLint components,
                                                     const GLfloat *coeffs) const
{
    static const char *fnName = "glProgramPathFragmentInputGenNV";

    beforeCommand(fnName, _api.glProgramPathFragmentInputGen);
    _api.glProgramPathFragmentInputGen(program.ID, location, genMode, components,
                                       coeffs);
    afterCommand(fnName);
}

// Calls glStencilFillPathInstancedNV().
void NVPathRenderingAPI::stencilFillPathInstanced(GLsizei numPaths,
                                                  PathElementType pathNameType,
                                                  const void *paths,
                                                  GLuint pathBase,
                                                  PathFillMode fillMode,
                                                  GLuint mask,
                                                  PathTransformType transformType,
                                                  const GLfloat *transformValues) const
{
    static const char *fnName = "glStencilFillPathInstancedNV";

    beforeCommand(fnName, _api.glStencilFillPathInstanced);
    _api.glStencilFillPathInstanced(numPaths, toScalar(pathNameType), paths,
                                    pathBase, toScalar(fillMode), mask,
                                    toScalar(transformType), transformValues);
    afterCommand(fnName);
}

// Calls glStencilFillPathNV().
void NVPathRenderingAPI::stencilFillPath(GLuint path, PathFillMode fillMode,
                                         GLuint mask) const
{
    static const char *fnName = "glStencilFillPathNV";

    beforeCommand(fnName, _api.glStencilFillPath);
    _api.glStencilFillPath(path, toScalar(fillMode), mask);
    afterCommand(fnName);
}

// Calls glStencilStrokePathInstancedNV().
void NVPathRenderingAPI::stencilStrokePathInstanced(GLsizei numPaths,
                                                    PathElementType pathNameType,
                                                    const void *paths,
                                                    GLuint pathBase,
                                                    GLint reference, GLuint mask,
                                                    PathTransformType transformType,
                                                    const GLfloat *transformValues) const
{
    static const char *fnName = "glStencilStrokePathInstancedNV";

    beforeCommand(fnName, _api.glStencilStrokePathInstanced);
    _api.glStencilStrokePathInstanced(numPaths, toScalar(pathNameType), paths,
                                      pathBase, reference, mask,
                                      toScalar(transformType), transformValues);
    afterCommand(fnName);
}

// Calls glStencilStrokePathNV().
void NVPathRenderingAPI::stencilStrokePath(GLuint path, GLint reference,
                                           GLuint mask) const
{
    static const char *fnName = "glStencilStrokePathNV";

    beforeCommand(fnName, _api.glStencilStrokePath);
    _api.glStencilStrokePath(path, reference, mask);
    afterCommand(fnName);
}

// Calls glStencilThenCoverFillPathInstancedNV().
void NVPathRenderingAPI::stencilThenCoverFillPathInstanced(GLsizei numPaths,
                                                           GLenum pathNameType,
                                                           const void *paths,
                                                           GLuint pathBase,
                                                           GLenum fillMode,
                                                           GLuint mask,
                                                           GLenum coverMode,
                                                           GLenum transformType,
                                                           const GLfloat *transformValues) const
{
    static const char *fnName = "glStencilThenCoverFillPathInstancedNV";

    beforeCommand(fnName, _api.glStencilThenCoverFillPathInstanced);
    _api.glStencilThenCoverFillPathInstanced(numPaths, pathNameType, paths,
                                             pathBase, fillMode, mask, coverMode,
                                             transformType, transformValues);
    afterCommand(fnName);
}

// Calls glStencilThenCoverFillPathNV().
void NVPathRenderingAPI::stencilThenCoverFillPath(GLuint path, GLenum fillMode,
                                                  GLuint mask, GLenum coverMode) const
{
    static const char *fnName = "glStencilThenCoverFillPathNV";

    beforeCommand(fnName, _api.glStencilThenCoverFillPath);
    _api.glStencilThenCoverFillPath(path, fillMode, mask, coverMode);
    afterCommand(fnName);
}

// Calls glStencilThenCoverStrokePathInstancedNV().
void NVPathRenderingAPI::stencilThenCoverStrokePathInstanced(GLsizei numPaths,
                                                             GLenum pathNameType,
                                                             const void *paths,
                                                             GLuint pathBase,
                                                             GLint reference,
                                                             GLuint mask,
                                                             GLenum coverMode,
                                                             GLenum transformType,
                                                             const GLfloat *transformValues) const
{
    static const char *fnName = "glStencilThenCoverStrokePathInstancedNV";

    beforeCommand(fnName, _api.glStencilThenCoverStrokePathInstanced);
    _api.glStencilThenCoverStrokePathInstanced(numPaths, pathNameType, paths,
                                               pathBase, reference, mask,
                                               coverMode, transformType,
                                               transformValues);
    afterCommand(fnName);
}

// Calls glStencilThenCoverStrokePathNV().
void NVPathRenderingAPI::stencilThenCoverStrokePath(GLuint path, GLint reference,
                                                    GLuint mask,
                                                    GLenum coverMode) const
{
    static const char *fnName = "glStencilThenCoverStrokePathNV";

    beforeCommand(fnName, _api.glStencilThenCoverStrokePath);
    _api.glStencilThenCoverStrokePath(path, reference, mask, coverMode);
    afterCommand(fnName);
}

// Calls glTransformPathNV().
void NVPathRenderingAPI::transformPath(GLuint resultPath, GLuint srcPath,
                                       PathTransformType transformType,
                                       const GLfloat *transformValues) const
{
    static const char *fnName = "glTransformPathNV";

    beforeCommand(fnName, _api.glTransformPath);
    _api.glTransformPath(resultPath, srcPath, toScalar(transformType),
                         transformValues);
    afterCommand(fnName);
}

// Calls glWeightPathsNV().
void NVPathRenderingAPI::weightPaths(GLuint resultPath, GLsizei numPaths,
                                     const GLuint *paths, const GLfloat *weights) const
{
    static const char *fnName = "glWeightPathsNV";

    beforeCommand(fnName, _api.glWeightPaths);
    _api.glWeightPaths(resultPath, numPaths, paths, weights);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVPixelDataRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_pixel_data_range extension.
NVPixelDataRangeAPI::NVPixelDataRangeAPI() :
    BaseExtension("GL_NV_pixel_data_range")
{
}

// Grant read-only access to the underlying function pointers.
const NVPixelDataRange &NVPixelDataRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_pixel_data_range entry points.
void NVPixelDataRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFlushPixelDataRangeNV().
void NVPixelDataRangeAPI::flushPixelDataRange(PixelDataRangeTargetNV target) const
{
    static const char *fnName = "glFlushPixelDataRangeNV";

    beforeCommand(fnName, _api.glFlushPixelDataRange);
    _api.glFlushPixelDataRange(toScalar(target));
    afterCommand(fnName);
}

// Calls glPixelDataRangeNV().
void NVPixelDataRangeAPI::pixelDataRange(PixelDataRangeTargetNV target,
                                         GLsizei length, const void *pointer) const
{
    static const char *fnName = "glPixelDataRangeNV";

    beforeCommand(fnName, _api.glPixelDataRange);
    _api.glPixelDataRange(toScalar(target), length, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVPointSpriteAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_point_sprite extension.
NVPointSpriteAPI::NVPointSpriteAPI() :
    BaseExtension("GL_NV_point_sprite")
{
}

// Grant read-only access to the underlying function pointers.
const NVPointSprite &NVPointSpriteAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_point_sprite entry points.
void NVPointSpriteAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPointParameteriNV().
void NVPointSpriteAPI::pointParameterI(PointParameterNameARB pname, GLint param) const
{
    static const char *fnName = "glPointParameteriNV";

    beforeCommand(fnName, _api.glPointParameteri);
    _api.glPointParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameterivNV().
void NVPointSpriteAPI::pointParameterIV(PointParameterNameARB pname,
                                        const GLint *params) const
{
    static const char *fnName = "glPointParameterivNV";

    beforeCommand(fnName, _api.glPointParameteriv);
    _api.glPointParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideoAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_present_video extension.
NVPresentVideoAPI::NVPresentVideoAPI() :
    BaseExtension("GL_NV_present_video")
{
}

// Grant read-only access to the underlying function pointers.
const NVPresentVideo &NVPresentVideoAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_present_video entry points.
void NVPresentVideoAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetVideoi64vNV().
void NVPresentVideoAPI::getVideoI64V(GLuint video_slot, GLenum pname,
                                     GLint64EXT *params) const
{
    static const char *fnName = "glGetVideoi64vNV";

    beforeCommand(fnName, _api.glGetVideoi64v);
    _api.glGetVideoi64v(video_slot, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideoivNV().
void NVPresentVideoAPI::getVideoIV(GLuint video_slot, GLenum pname,
                                   GLint *params) const
{
    static const char *fnName = "glGetVideoivNV";

    beforeCommand(fnName, _api.glGetVideoiv);
    _api.glGetVideoiv(video_slot, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideoui64vNV().
void NVPresentVideoAPI::getVideoUI64(GLuint video_slot, GLenum pname,
                                     GLuint64EXT *params) const
{
    static const char *fnName = "glGetVideoui64vNV";

    beforeCommand(fnName, _api.glGetVideoui64v);
    _api.glGetVideoui64v(video_slot, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideouivNV().
void NVPresentVideoAPI::getVideoUIV(GLuint video_slot, GLenum pname,
                                    GLuint *params) const
{
    static const char *fnName = "glGetVideouivNV";

    beforeCommand(fnName, _api.glGetVideouiv);
    _api.glGetVideouiv(video_slot, pname, params);
    afterCommand(fnName);
}

// Calls glPresentFrameDualFillNV().
void NVPresentVideoAPI::presentFrameDualFill(GLuint video_slot,
                                             GLuint64EXT minPresentTime,
                                             GLuint beginPresentTimeId,
                                             GLuint presentDurationId,
                                             GLenum type, GLenum target0,
                                             GLuint fill0, GLenum target1,
                                             GLuint fill1, GLenum target2,
                                             GLuint fill2, GLenum target3,
                                             GLuint fill3) const
{
    static const char *fnName = "glPresentFrameDualFillNV";

    beforeCommand(fnName, _api.glPresentFrameDualFill);
    _api.glPresentFrameDualFill(video_slot, minPresentTime, beginPresentTimeId,
                                presentDurationId, type, target0, fill0, target1,
                                fill1, target2, fill2, target3, fill3);
    afterCommand(fnName);
}

// Calls glPresentFrameKeyedNV().
void NVPresentVideoAPI::presentFrameKeyed(GLuint video_slot,
                                          GLuint64EXT minPresentTime,
                                          GLuint beginPresentTimeId,
                                          GLuint presentDurationId, GLenum type,
                                          GLenum target0, GLuint fill0,
                                          GLuint key0, GLenum target1,
                                          GLuint fill1, GLuint key1) const
{
    static const char *fnName = "glPresentFrameKeyedNV";

    beforeCommand(fnName, _api.glPresentFrameKeyed);
    _api.glPresentFrameKeyed(video_slot, minPresentTime, beginPresentTimeId,
                             presentDurationId, type, target0, fill0, key0,
                             target1, fill1, key1);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVPrimitiveRestartAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_primitive_restart extension.
NVPrimitiveRestartAPI::NVPrimitiveRestartAPI() :
    BaseExtension("GL_NV_primitive_restart")
{
}

// Grant read-only access to the underlying function pointers.
const NVPrimitiveRestart &NVPrimitiveRestartAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_primitive_restart entry points.
void NVPrimitiveRestartAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPrimitiveRestartIndexNV().
void NVPrimitiveRestartAPI::primitiveRestartIndex(GLuint index) const
{
    static const char *fnName = "glPrimitiveRestartIndexNV";

    beforeCommand(fnName, _api.glPrimitiveRestartIndex);
    _api.glPrimitiveRestartIndex(index);
    afterCommand(fnName);
}

// Calls glPrimitiveRestartNV().
void NVPrimitiveRestartAPI::primitiveRestart() const
{
    static const char *fnName = "glPrimitiveRestartNV";

    beforeCommand(fnName, _api.glPrimitiveRestart);
    _api.glPrimitiveRestart();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVQueryResourceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_query_resource extension.
NVQueryResourceAPI::NVQueryResourceAPI() :
    BaseExtension("GL_NV_query_resource")
{
}

// Grant read-only access to the underlying function pointers.
const NVQueryResource &NVQueryResourceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_query_resource entry points.
void NVQueryResourceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glQueryResourceNV().
GLint NVQueryResourceAPI::queryResource(GLenum queryType, GLint tagId,
                                        GLuint count, GLint *buffer) const
{
    static const char *fnName = "glQueryResourceNV";

    beforeCommand(fnName, _api.glQueryResource);
    GLint result = _api.glQueryResource(queryType, tagId, count, buffer);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVQueryResourceTagAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_query_resource_tag extension.
NVQueryResourceTagAPI::NVQueryResourceTagAPI() :
    BaseExtension("GL_NV_query_resource_tag")
{
}

// Grant read-only access to the underlying function pointers.
const NVQueryResourceTag &NVQueryResourceTagAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_query_resource_tag entry points.
void NVQueryResourceTagAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeleteQueryResourceTagNV().
void NVQueryResourceTagAPI::deleteQueryResourceTag(GLsizei n,
                                                   const GLint *tagIds) const
{
    static const char *fnName = "glDeleteQueryResourceTagNV";

    beforeCommand(fnName, _api.glDeleteQueryResourceTag);
    _api.glDeleteQueryResourceTag(n, tagIds);
    afterCommand(fnName);
}

// Calls glGenQueryResourceTagNV().
void NVQueryResourceTagAPI::genQueryResourceTag(GLsizei n, GLint *tagIds) const
{
    static const char *fnName = "glGenQueryResourceTagNV";

    beforeCommand(fnName, _api.glGenQueryResourceTag);
    _api.glGenQueryResourceTag(n, tagIds);
    afterCommand(fnName);
}

// Calls glQueryResourceTagNV().
void NVQueryResourceTagAPI::queryResourceTag(GLint tagId,
                                             const GLchar *tagString) const
{
    static const char *fnName = "glQueryResourceTagNV";

    beforeCommand(fnName, _api.glQueryResourceTag);
    _api.glQueryResourceTag(tagId, tagString);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVRegisterCombinersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_register_combiners extension.
NVRegisterCombinersAPI::NVRegisterCombinersAPI() :
    BaseExtension("GL_NV_register_combiners")
{
}

// Grant read-only access to the underlying function pointers.
const NVRegisterCombiners &NVRegisterCombinersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_register_combiners entry points.
void NVRegisterCombinersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCombinerInputNV().
void NVRegisterCombinersAPI::combinerInput(CombinerStageNV stage,
                                           CombinerPortionNV portion,
                                           CombinerVariableNV variable,
                                           CombinerRegisterNV input,
                                           CombinerMappingNV mapping,
                                           CombinerComponentUsageNV componentUsage) const
{
    static const char *fnName = "glCombinerInputNV";

    beforeCommand(fnName, _api.glCombinerInput);
    _api.glCombinerInput(toScalar(stage), toScalar(portion), toScalar(variable),
                         toScalar(input), toScalar(mapping),
                         toScalar(componentUsage));
    afterCommand(fnName);
}

// Calls glCombinerOutputNV().
void NVRegisterCombinersAPI::combinerOutput(CombinerStageNV stage,
                                            CombinerPortionNV portion,
                                            CombinerRegisterNV abOutput,
                                            CombinerRegisterNV cdOutput,
                                            CombinerRegisterNV sumOutput,
                                            CombinerScaleNV scale,
                                            CombinerBiasNV bias,
                                            Boolean abDotProduct,
                                            Boolean cdDotProduct, Boolean muxSum) const
{
    static const char *fnName = "glCombinerOutputNV";

    beforeCommand(fnName, _api.glCombinerOutput);
    _api.glCombinerOutput(toScalar(stage), toScalar(portion), toScalar(abOutput),
                          toScalar(cdOutput), toScalar(sumOutput),
                          toScalar(scale), toScalar(bias),
                          toScalar(abDotProduct), toScalar(cdDotProduct),
                          toScalar(muxSum));
    afterCommand(fnName);
}

// Calls glCombinerParameterfNV().
void NVRegisterCombinersAPI::combinerParameterF(CombinerParameterNV pname,
                                                GLfloat param) const
{
    static const char *fnName = "glCombinerParameterfNV";

    beforeCommand(fnName, _api.glCombinerParameterf);
    _api.glCombinerParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glCombinerParameterfvNV().
void NVRegisterCombinersAPI::combinerParameterFV(CombinerParameterNV pname,
                                                 const GLfloat *params) const
{
    static const char *fnName = "glCombinerParameterfvNV";

    beforeCommand(fnName, _api.glCombinerParameterfv);
    _api.glCombinerParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glCombinerParameteriNV().
void NVRegisterCombinersAPI::combinerParameterI(CombinerParameterNV pname,
                                                GLint param) const
{
    static const char *fnName = "glCombinerParameteriNV";

    beforeCommand(fnName, _api.glCombinerParameteri);
    _api.glCombinerParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glCombinerParameterivNV().
void NVRegisterCombinersAPI::combinerParameterIV(CombinerParameterNV pname,
                                                 const GLint *params) const
{
    static const char *fnName = "glCombinerParameterivNV";

    beforeCommand(fnName, _api.glCombinerParameteriv);
    _api.glCombinerParameteriv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glFinalCombinerInputNV().
void NVRegisterCombinersAPI::finalCombinerInput(CombinerVariableNV variable,
                                                CombinerRegisterNV input,
                                                CombinerMappingNV mapping,
                                                CombinerComponentUsageNV componentUsage) const
{
    static const char *fnName = "glFinalCombinerInputNV";

    beforeCommand(fnName, _api.glFinalCombinerInput);
    _api.glFinalCombinerInput(toScalar(variable), toScalar(input),
                              toScalar(mapping), toScalar(componentUsage));
    afterCommand(fnName);
}

// Calls glGetCombinerInputParameterfvNV().
void NVRegisterCombinersAPI::getCombinerInputParameterFV(CombinerStageNV stage,
                                                         CombinerPortionNV portion,
                                                         CombinerVariableNV variable,
                                                         CombinerParameterNV pname,
                                                         GLfloat *params) const
{
    static const char *fnName = "glGetCombinerInputParameterfvNV";

    beforeCommand(fnName, _api.glGetCombinerInputParameterfv);
    _api.glGetCombinerInputParameterfv(toScalar(stage), toScalar(portion),
                                       toScalar(variable), toScalar(pname),
                                       params);
    afterCommand(fnName);
}

// Calls glGetCombinerInputParameterivNV().
void NVRegisterCombinersAPI::getCombinerInputParameterIV(CombinerStageNV stage,
                                                         CombinerPortionNV portion,
                                                         CombinerVariableNV variable,
                                                         CombinerParameterNV pname,
                                                         GLint *params) const
{
    static const char *fnName = "glGetCombinerInputParameterivNV";

    beforeCommand(fnName, _api.glGetCombinerInputParameteriv);
    _api.glGetCombinerInputParameteriv(toScalar(stage), toScalar(portion),
                                       toScalar(variable), toScalar(pname),
                                       params);
    afterCommand(fnName);
}

// Calls glGetCombinerOutputParameterfvNV().
void NVRegisterCombinersAPI::getCombinerOutputParameterFV(CombinerStageNV stage,
                                                          CombinerPortionNV portion,
                                                          CombinerParameterNV pname,
                                                          GLfloat *params) const
{
    static const char *fnName = "glGetCombinerOutputParameterfvNV";

    beforeCommand(fnName, _api.glGetCombinerOutputParameterfv);
    _api.glGetCombinerOutputParameterfv(toScalar(stage), toScalar(portion),
                                        toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetCombinerOutputParameterivNV().
void NVRegisterCombinersAPI::getCombinerOutputParameterIV(CombinerStageNV stage,
                                                          CombinerPortionNV portion,
                                                          CombinerParameterNV pname,
                                                          GLint *params) const
{
    static const char *fnName = "glGetCombinerOutputParameterivNV";

    beforeCommand(fnName, _api.glGetCombinerOutputParameteriv);
    _api.glGetCombinerOutputParameteriv(toScalar(stage), toScalar(portion),
                                        toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetFinalCombinerInputParameterfvNV().
void NVRegisterCombinersAPI::getFinalCombinerInputParameterFV(CombinerVariableNV variable,
                                                              CombinerParameterNV pname,
                                                              GLfloat *params) const
{
    static const char *fnName = "glGetFinalCombinerInputParameterfvNV";

    beforeCommand(fnName, _api.glGetFinalCombinerInputParameterfv);
    _api.glGetFinalCombinerInputParameterfv(toScalar(variable), toScalar(pname),
                                            params);
    afterCommand(fnName);
}

// Calls glGetFinalCombinerInputParameterivNV().
void NVRegisterCombinersAPI::getFinalCombinerInputParameterIV(CombinerVariableNV variable,
                                                              CombinerParameterNV pname,
                                                              GLint *params) const
{
    static const char *fnName = "glGetFinalCombinerInputParameterivNV";

    beforeCommand(fnName, _api.glGetFinalCombinerInputParameteriv);
    _api.glGetFinalCombinerInputParameteriv(toScalar(variable), toScalar(pname),
                                            params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVRegisterCOMBINERS2API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_register_combiners2 extension.
NVRegisterCOMBINERS2API::NVRegisterCOMBINERS2API() :
    BaseExtension("GL_NV_register_combiners2")
{
}

// Grant read-only access to the underlying function pointers.
const NVRegisterCOMBINERS2 &NVRegisterCOMBINERS2API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_register_combiners2 entry points.
void NVRegisterCOMBINERS2API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCombinerStageParameterfvNV().
void NVRegisterCOMBINERS2API::combinerStageParameterFV(CombinerStageNV stage,
                                                       CombinerParameterNV pname,
                                                       const GLfloat *params) const
{
    static const char *fnName = "glCombinerStageParameterfvNV";

    beforeCommand(fnName, _api.glCombinerStageParameterfv);
    _api.glCombinerStageParameterfv(toScalar(stage), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetCombinerStageParameterfvNV().
void NVRegisterCOMBINERS2API::getCombinerStageParameterFV(CombinerStageNV stage,
                                                          CombinerParameterNV pname,
                                                          GLfloat *params) const
{
    static const char *fnName = "glGetCombinerStageParameterfvNV";

    beforeCommand(fnName, _api.glGetCombinerStageParameterfv);
    _api.glGetCombinerStageParameterfv(toScalar(stage), toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVSampleLocationsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_sample_locations extension.
NVSampleLocationsAPI::NVSampleLocationsAPI() :
    BaseExtension("GL_NV_sample_locations")
{
}

// Grant read-only access to the underlying function pointers.
const NVSampleLocations &NVSampleLocationsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_sample_locations entry points.
void NVSampleLocationsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferSampleLocationsfvNV().
void NVSampleLocationsAPI::framebufferSampleLocationsFV(FramebufferTarget target,
                                                        GLuint start,
                                                        GLsizei count,
                                                        const GLfloat *v) const
{
    static const char *fnName = "glFramebufferSampleLocationsfvNV";

    beforeCommand(fnName, _api.glFramebufferSampleLocationsfv);
    _api.glFramebufferSampleLocationsfv(toScalar(target), start, count, v);
    afterCommand(fnName);
}

// Calls glNamedFramebufferSampleLocationsfvNV().
void NVSampleLocationsAPI::namedFramebufferSampleLocationsFV(FramebufferName framebuffer,
                                                             GLuint start,
                                                             GLsizei count,
                                                             const GLfloat *v) const
{
    static const char *fnName = "glNamedFramebufferSampleLocationsfvNV";

    beforeCommand(fnName, _api.glNamedFramebufferSampleLocationsfv);
    _api.glNamedFramebufferSampleLocationsfv(framebuffer.ID, start, count, v);
    afterCommand(fnName);
}

// Calls glResolveDepthValuesNV().
void NVSampleLocationsAPI::resolveDepthValues() const
{
    static const char *fnName = "glResolveDepthValuesNV";

    beforeCommand(fnName, _api.glResolveDepthValues);
    _api.glResolveDepthValues();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVScissorExclusiveAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_scissor_exclusive extension.
NVScissorExclusiveAPI::NVScissorExclusiveAPI() :
    BaseExtension("GL_NV_scissor_exclusive")
{
}

// Grant read-only access to the underlying function pointers.
const NVScissorExclusive &NVScissorExclusiveAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_scissor_exclusive entry points.
void NVScissorExclusiveAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glScissorExclusiveArrayvNV().
void NVScissorExclusiveAPI::scissorExclusiveArrayV(GLuint first, GLsizei count,
                                                   const GLint *v) const
{
    static const char *fnName = "glScissorExclusiveArrayvNV";

    beforeCommand(fnName, _api.glScissorExclusiveArrayv);
    _api.glScissorExclusiveArrayv(first, count, v);
    afterCommand(fnName);
}

// Calls glScissorExclusiveNV().
void NVScissorExclusiveAPI::scissorExclusive(GLint x, GLint y, GLsizei width,
                                             GLsizei height) const
{
    static const char *fnName = "glScissorExclusiveNV";

    beforeCommand(fnName, _api.glScissorExclusive);
    _api.glScissorExclusive(x, y, width, height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVShaderBufferLoadAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_shader_buffer_load extension.
NVShaderBufferLoadAPI::NVShaderBufferLoadAPI() :
    BaseExtension("GL_NV_shader_buffer_load")
{
}

// Grant read-only access to the underlying function pointers.
const NVShaderBufferLoad &NVShaderBufferLoadAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_shader_buffer_load entry points.
void NVShaderBufferLoadAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetBufferParameterui64vNV().
void NVShaderBufferLoadAPI::getBufferParameterUI64(BufferTargetARB target,
                                                   GLenum pname,
                                                   GLuint64EXT *params) const
{
    static const char *fnName = "glGetBufferParameterui64vNV";

    beforeCommand(fnName, _api.glGetBufferParameterui64v);
    _api.glGetBufferParameterui64v(toScalar(target), pname, params);
    afterCommand(fnName);
}

// Calls glGetIntegerui64vNV().
void NVShaderBufferLoadAPI::getIntegerUI64(GLenum value, GLuint64EXT *result) const
{
    static const char *fnName = "glGetIntegerui64vNV";

    beforeCommand(fnName, _api.glGetIntegerui64v);
    _api.glGetIntegerui64v(value, result);
    afterCommand(fnName);
}

// Calls glGetNamedBufferParameterui64vNV().
void NVShaderBufferLoadAPI::getNamedBufferParameterUI64(BufferName buffer,
                                                        BufferPNameARB pname,
                                                        GLuint64EXT *params) const
{
    static const char *fnName = "glGetNamedBufferParameterui64vNV";

    beforeCommand(fnName, _api.glGetNamedBufferParameterui64v);
    _api.glGetNamedBufferParameterui64v(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsBufferResidentNV().
Boolean NVShaderBufferLoadAPI::isBufferResident(GLenum target) const
{
    static const char *fnName = "glIsBufferResidentNV";

    beforeCommand(fnName, _api.glIsBufferResident);
    GLboolean result = _api.glIsBufferResident(target);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsNamedBufferResidentNV().
Boolean NVShaderBufferLoadAPI::isNamedBufferResident(BufferName buffer) const
{
    static const char *fnName = "glIsNamedBufferResidentNV";

    beforeCommand(fnName, _api.glIsNamedBufferResident);
    GLboolean result = _api.glIsNamedBufferResident(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMakeBufferNonResidentNV().
void NVShaderBufferLoadAPI::makeBufferNonResident(GLenum target) const
{
    static const char *fnName = "glMakeBufferNonResidentNV";

    beforeCommand(fnName, _api.glMakeBufferNonResident);
    _api.glMakeBufferNonResident(target);
    afterCommand(fnName);
}

// Calls glMakeBufferResidentNV().
void NVShaderBufferLoadAPI::makeBufferResident(GLenum target, GLenum access) const
{
    static const char *fnName = "glMakeBufferResidentNV";

    beforeCommand(fnName, _api.glMakeBufferResident);
    _api.glMakeBufferResident(target, access);
    afterCommand(fnName);
}

// Calls glMakeNamedBufferNonResidentNV().
void NVShaderBufferLoadAPI::makeNamedBufferNonResident(BufferName buffer) const
{
    static const char *fnName = "glMakeNamedBufferNonResidentNV";

    beforeCommand(fnName, _api.glMakeNamedBufferNonResident);
    _api.glMakeNamedBufferNonResident(buffer.ID);
    afterCommand(fnName);
}

// Calls glMakeNamedBufferResidentNV().
void NVShaderBufferLoadAPI::makeNamedBufferResident(BufferName buffer,
                                                    GLenum access) const
{
    static const char *fnName = "glMakeNamedBufferResidentNV";

    beforeCommand(fnName, _api.glMakeNamedBufferResident);
    _api.glMakeNamedBufferResident(buffer.ID, access);
    afterCommand(fnName);
}

// Calls glProgramUniformui64NV().
void NVShaderBufferLoadAPI::programUniformUI64(ProgramName program,
                                               GLint location, GLuint64EXT value) const
{
    static const char *fnName = "glProgramUniformui64NV";

    beforeCommand(fnName, _api.glProgramUniformui64);
    _api.glProgramUniformui64(program.ID, location, value);
    afterCommand(fnName);
}

// Calls glProgramUniformui64vNV().
void NVShaderBufferLoadAPI::programUniformUI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64EXT *value) const
{
    static const char *fnName = "glProgramUniformui64vNV";

    beforeCommand(fnName, _api.glProgramUniformui64v);
    _api.glProgramUniformui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glUniformui64NV().
void NVShaderBufferLoadAPI::uniformUI64(GLint location, GLuint64EXT value) const
{
    static const char *fnName = "glUniformui64NV";

    beforeCommand(fnName, _api.glUniformui64);
    _api.glUniformui64(location, value);
    afterCommand(fnName);
}

// Calls glUniformui64vNV().
void NVShaderBufferLoadAPI::uniformUI64(GLint location, GLsizei count,
                                        const GLuint64EXT *value) const
{
    static const char *fnName = "glUniformui64vNV";

    beforeCommand(fnName, _api.glUniformui64v);
    _api.glUniformui64v(location, count, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVShadingRateImageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_shading_rate_image extension.
NVShadingRateImageAPI::NVShadingRateImageAPI() :
    BaseExtension("GL_NV_shading_rate_image")
{
}

// Grant read-only access to the underlying function pointers.
const NVShadingRateImage &NVShadingRateImageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_shading_rate_image entry points.
void NVShadingRateImageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindShadingRateImageNV().
void NVShadingRateImageAPI::bindShadingRateImage(TextureName texture) const
{
    static const char *fnName = "glBindShadingRateImageNV";

    beforeCommand(fnName, _api.glBindShadingRateImage);
    _api.glBindShadingRateImage(texture.ID);
    afterCommand(fnName);
}

// Calls glGetShadingRateImagePaletteNV().
void NVShadingRateImageAPI::getShadingRateImagePalette(GLuint viewport,
                                                       GLuint entry,
                                                       GLenum *rate) const
{
    static const char *fnName = "glGetShadingRateImagePaletteNV";

    beforeCommand(fnName, _api.glGetShadingRateImagePalette);
    _api.glGetShadingRateImagePalette(viewport, entry, rate);
    afterCommand(fnName);
}

// Calls glGetShadingRateSampleLocationivNV().
void NVShadingRateImageAPI::getShadingRateSampleLocationIV(GLenum rate,
                                                           GLuint samples,
                                                           GLuint index,
                                                           GLint *location) const
{
    static const char *fnName = "glGetShadingRateSampleLocationivNV";

    beforeCommand(fnName, _api.glGetShadingRateSampleLocationiv);
    _api.glGetShadingRateSampleLocationiv(rate, samples, index, location);
    afterCommand(fnName);
}

// Calls glShadingRateImageBarrierNV().
void NVShadingRateImageAPI::shadingRateImageBarrier(Boolean synchronize) const
{
    static const char *fnName = "glShadingRateImageBarrierNV";

    beforeCommand(fnName, _api.glShadingRateImageBarrier);
    _api.glShadingRateImageBarrier(toScalar(synchronize));
    afterCommand(fnName);
}

// Calls glShadingRateImagePaletteNV().
void NVShadingRateImageAPI::shadingRateImagePalette(GLuint viewport,
                                                    GLuint first, GLsizei count,
                                                    const GLenum *rates) const
{
    static const char *fnName = "glShadingRateImagePaletteNV";

    beforeCommand(fnName, _api.glShadingRateImagePalette);
    _api.glShadingRateImagePalette(viewport, first, count, rates);
    afterCommand(fnName);
}

// Calls glShadingRateSampleOrderCustomNV().
void NVShadingRateImageAPI::shadingRateSampleOrderCustom(GLenum rate,
                                                         GLuint samples,
                                                         const GLint *locations) const
{
    static const char *fnName = "glShadingRateSampleOrderCustomNV";

    beforeCommand(fnName, _api.glShadingRateSampleOrderCustom);
    _api.glShadingRateSampleOrderCustom(rate, samples, locations);
    afterCommand(fnName);
}

// Calls glShadingRateSampleOrderNV().
void NVShadingRateImageAPI::shadingRateSampleOrder(GLenum order) const
{
    static const char *fnName = "glShadingRateSampleOrderNV";

    beforeCommand(fnName, _api.glShadingRateSampleOrder);
    _api.glShadingRateSampleOrder(order);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVTextureBarrierAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_texture_barrier extension.
NVTextureBarrierAPI::NVTextureBarrierAPI() :
    BaseExtension("GL_NV_texture_barrier")
{
}

// Grant read-only access to the underlying function pointers.
const NVTextureBarrier &NVTextureBarrierAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_texture_barrier entry points.
void NVTextureBarrierAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTextureBarrierNV().
void NVTextureBarrierAPI::textureBarrier() const
{
    static const char *fnName = "glTextureBarrierNV";

    beforeCommand(fnName, _api.glTextureBarrier);
    _api.glTextureBarrier();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVTextureMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_texture_multisample extension.
NVTextureMultisampleAPI::NVTextureMultisampleAPI() :
    BaseExtension("GL_NV_texture_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const NVTextureMultisample &NVTextureMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_texture_multisample entry points.
void NVTextureMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexImage2DMultisampleCoverageNV().
void NVTextureMultisampleAPI::texImage2DMultisampleCoverage(TextureTarget target,
                                                            GLsizei coverageSamples,
                                                            GLsizei colorSamples,
                                                            InternalFormat internalFormat,
                                                            GLsizei width,
                                                            GLsizei height,
                                                            Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTexImage2DMultisampleCoverageNV";

    beforeCommand(fnName, _api.glTexImage2DMultisampleCoverage);
    _api.glTexImage2DMultisampleCoverage(toScalar(target), coverageSamples,
                                         colorSamples, toScalar(internalFormat),
                                         width, height,
                                         toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

// Calls glTexImage3DMultisampleCoverageNV().
void NVTextureMultisampleAPI::texImage3DMultisampleCoverage(TextureTarget target,
                                                            GLsizei coverageSamples,
                                                            GLsizei colorSamples,
                                                            InternalFormat internalFormat,
                                                            GLsizei width,
                                                            GLsizei height,
                                                            GLsizei depth,
                                                            Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTexImage3DMultisampleCoverageNV";

    beforeCommand(fnName, _api.glTexImage3DMultisampleCoverage);
    _api.glTexImage3DMultisampleCoverage(toScalar(target), coverageSamples,
                                         colorSamples, toScalar(internalFormat),
                                         width, height, depth,
                                         toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

// Calls glTextureImage2DMultisampleCoverageNV().
void NVTextureMultisampleAPI::textureImage2DMultisampleCoverage(TextureName texture,
                                                                TextureTarget target,
                                                                GLsizei coverageSamples,
                                                                GLsizei colorSamples,
                                                                InternalFormat internalFormat,
                                                                GLsizei width,
                                                                GLsizei height,
                                                                Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTextureImage2DMultisampleCoverageNV";

    beforeCommand(fnName, _api.glTextureImage2DMultisampleCoverage);
    _api.glTextureImage2DMultisampleCoverage(texture.ID, toScalar(target),
                                             coverageSamples, colorSamples,
                                             toScalar(internalFormat), width,
                                             height,
                                             toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

// Calls glTextureImage2DMultisampleNV().
void NVTextureMultisampleAPI::textureImage2DMultisample(TextureName texture,
                                                        TextureTarget target,
                                                        GLsizei samples,
                                                        InternalFormat internalFormat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTextureImage2DMultisampleNV";

    beforeCommand(fnName, _api.glTextureImage2DMultisample);
    _api.glTextureImage2DMultisample(texture.ID, toScalar(target), samples,
                                     toScalar(internalFormat), width, height,
                                     toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

// Calls glTextureImage3DMultisampleCoverageNV().
void NVTextureMultisampleAPI::textureImage3DMultisampleCoverage(TextureName texture,
                                                                TextureTarget target,
                                                                GLsizei coverageSamples,
                                                                GLsizei colorSamples,
                                                                InternalFormat internalFormat,
                                                                GLsizei width,
                                                                GLsizei height,
                                                                GLsizei depth,
                                                                Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTextureImage3DMultisampleCoverageNV";

    beforeCommand(fnName, _api.glTextureImage3DMultisampleCoverage);
    _api.glTextureImage3DMultisampleCoverage(texture.ID, toScalar(target),
                                             coverageSamples, colorSamples,
                                             toScalar(internalFormat), width,
                                             height, depth,
                                             toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

// Calls glTextureImage3DMultisampleNV().
void NVTextureMultisampleAPI::textureImage3DMultisample(TextureName texture,
                                                        TextureTarget target,
                                                        GLsizei samples,
                                                        InternalFormat internalFormat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        GLsizei depth,
                                                        Boolean fixedSampleLocations) const
{
    static const char *fnName = "glTextureImage3DMultisampleNV";

    beforeCommand(fnName, _api.glTextureImage3DMultisample);
    _api.glTextureImage3DMultisample(texture.ID, toScalar(target), samples,
                                     toScalar(internalFormat), width, height,
                                     depth, toScalar(fixedSampleLocations));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVTimelineSemaphoreAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_timeline_semaphore extension.
NVTimelineSemaphoreAPI::NVTimelineSemaphoreAPI() :
    BaseExtension("GL_NV_timeline_semaphore")
{
}

// Grant read-only access to the underlying function pointers.
const NVTimelineSemaphore &NVTimelineSemaphoreAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_timeline_semaphore entry points.
void NVTimelineSemaphoreAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCreateSemaphoresNV().
void NVTimelineSemaphoreAPI::createSemaphores(GLsizei n, GLuint *semaphores) const
{
    static const char *fnName = "glCreateSemaphoresNV";

    beforeCommand(fnName, _api.glCreateSemaphores);
    _api.glCreateSemaphores(n, semaphores);
    afterCommand(fnName);
}

// Calls glGetSemaphoreParameterivNV().
void NVTimelineSemaphoreAPI::getSemaphoreParameterIV(GLuint semaphore,
                                                     SemaphoreParameterName pname,
                                                     GLint *params) const
{
    static const char *fnName = "glGetSemaphoreParameterivNV";

    beforeCommand(fnName, _api.glGetSemaphoreParameteriv);
    _api.glGetSemaphoreParameteriv(semaphore, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glSemaphoreParameterivNV().
void NVTimelineSemaphoreAPI::semaphoreParameterIV(GLuint semaphore,
                                                  SemaphoreParameterName pname,
                                                  const GLint *params) const
{
    static const char *fnName = "glSemaphoreParameterivNV";

    beforeCommand(fnName, _api.glSemaphoreParameteriv);
    _api.glSemaphoreParameteriv(semaphore, toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVTransformFeedbackAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_transform_feedback extension.
NVTransformFeedbackAPI::NVTransformFeedbackAPI() :
    BaseExtension("GL_NV_transform_feedback")
{
}

// Grant read-only access to the underlying function pointers.
const NVTransformFeedback &NVTransformFeedbackAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_transform_feedback entry points.
void NVTransformFeedbackAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glActiveVaryingNV().
void NVTransformFeedbackAPI::activeVarying(ProgramName program,
                                           const GLchar *name) const
{
    static const char *fnName = "glActiveVaryingNV";

    beforeCommand(fnName, _api.glActiveVarying);
    _api.glActiveVarying(program.ID, name);
    afterCommand(fnName);
}

// Calls glBeginTransformFeedbackNV().
void NVTransformFeedbackAPI::beginTransformFeedback(PrimitiveType primitiveMode) const
{
    static const char *fnName = "glBeginTransformFeedbackNV";

    beforeCommand(fnName, _api.glBeginTransformFeedback);
    _api.glBeginTransformFeedback(toScalar(primitiveMode));
    afterCommand(fnName);
}

// Calls glBindBufferBaseNV().
void NVTransformFeedbackAPI::bindBufferBase(BufferTargetARB target, GLuint index,
                                            BufferName buffer) const
{
    static const char *fnName = "glBindBufferBaseNV";

    beforeCommand(fnName, _api.glBindBufferBase);
    _api.glBindBufferBase(toScalar(target), index, buffer.ID);
    afterCommand(fnName);
}

// Calls glBindBufferOffsetNV().
void NVTransformFeedbackAPI::bindBufferOffset(BufferTargetARB target,
                                              GLuint index, BufferName buffer,
                                              GLintptr offset) const
{
    static const char *fnName = "glBindBufferOffsetNV";

    beforeCommand(fnName, _api.glBindBufferOffset);
    _api.glBindBufferOffset(toScalar(target), index, buffer.ID, offset);
    afterCommand(fnName);
}

// Calls glBindBufferRangeNV().
void NVTransformFeedbackAPI::bindBufferRange(BufferTargetARB target,
                                             GLuint index, BufferName buffer,
                                             GLintptr offset, GLsizeiptr size) const
{
    static const char *fnName = "glBindBufferRangeNV";

    beforeCommand(fnName, _api.glBindBufferRange);
    _api.glBindBufferRange(toScalar(target), index, buffer.ID, offset, size);
    afterCommand(fnName);
}

// Calls glEndTransformFeedbackNV().
void NVTransformFeedbackAPI::endTransformFeedback() const
{
    static const char *fnName = "glEndTransformFeedbackNV";

    beforeCommand(fnName, _api.glEndTransformFeedback);
    _api.glEndTransformFeedback();
    afterCommand(fnName);
}

// Calls glGetActiveVaryingNV().
void NVTransformFeedbackAPI::getActiveVarying(ProgramName program, GLuint index,
                                              GLsizei bufSize, GLsizei *length,
                                              GLsizei *size, GLenum *type,
                                              GLchar *name) const
{
    static const char *fnName = "glGetActiveVaryingNV";

    beforeCommand(fnName, _api.glGetActiveVarying);
    _api.glGetActiveVarying(program.ID, index, bufSize, length, size, type, name);
    afterCommand(fnName);
}

// Calls glGetTransformFeedbackVaryingNV().
void NVTransformFeedbackAPI::getTransformFeedbackVarying(ProgramName program,
                                                         GLuint index,
                                                         GLint *location) const
{
    static const char *fnName = "glGetTransformFeedbackVaryingNV";

    beforeCommand(fnName, _api.glGetTransformFeedbackVarying);
    _api.glGetTransformFeedbackVarying(program.ID, index, location);
    afterCommand(fnName);
}

// Calls glGetVaryingLocationNV().
GLint NVTransformFeedbackAPI::getVaryingLocation(ProgramName program,
                                                 const GLchar *name) const
{
    static const char *fnName = "glGetVaryingLocationNV";

    beforeCommand(fnName, _api.glGetVaryingLocation);
    GLint result = _api.glGetVaryingLocation(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glTransformFeedbackAttribsNV().
void NVTransformFeedbackAPI::transformFeedbackAttribs(GLsizei count,
                                                      const GLint *attribs,
                                                      GLenum bufferMode) const
{
    static const char *fnName = "glTransformFeedbackAttribsNV";

    beforeCommand(fnName, _api.glTransformFeedbackAttribs);
    _api.glTransformFeedbackAttribs(count, attribs, bufferMode);
    afterCommand(fnName);
}

// Calls glTransformFeedbackStreamAttribsNV().
void NVTransformFeedbackAPI::transformFeedbackStreamAttribs(GLsizei count,
                                                            const GLint *attribs,
                                                            GLsizei nbuffers,
                                                            const GLint *bufstreams,
                                                            GLenum bufferMode) const
{
    static const char *fnName = "glTransformFeedbackStreamAttribsNV";

    beforeCommand(fnName, _api.glTransformFeedbackStreamAttribs);
    _api.glTransformFeedbackStreamAttribs(count, attribs, nbuffers, bufstreams,
                                          bufferMode);
    afterCommand(fnName);
}

// Calls glTransformFeedbackVaryingsNV().
void NVTransformFeedbackAPI::transformFeedbackVaryings(ProgramName program,
                                                       GLsizei count,
                                                       const GLint *locations,
                                                       GLenum bufferMode) const
{
    static const char *fnName = "glTransformFeedbackVaryingsNV";

    beforeCommand(fnName, _api.glTransformFeedbackVaryings);
    _api.glTransformFeedbackVaryings(program.ID, count, locations, bufferMode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVTransformFeedback2API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_transform_feedback2 extension.
NVTransformFeedback2API::NVTransformFeedback2API() :
    BaseExtension("GL_NV_transform_feedback2")
{
}

// Grant read-only access to the underlying function pointers.
const NVTransformFeedback2 &NVTransformFeedback2API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_transform_feedback2 entry points.
void NVTransformFeedback2API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindTransformFeedbackNV().
void NVTransformFeedback2API::bindTransformFeedback(BufferTargetARB target,
                                                    TransformFeedbackName id) const
{
    static const char *fnName = "glBindTransformFeedbackNV";

    beforeCommand(fnName, _api.glBindTransformFeedback);
    _api.glBindTransformFeedback(toScalar(target), id.ID);
    afterCommand(fnName);
}

// Calls glDeleteTransformFeedbacksNV().
void NVTransformFeedback2API::deleteTransformFeedbacks(GLsizei n,
                                                       const TransformFeedbackName *ids) const
{
    static const char *fnName = "glDeleteTransformFeedbacksNV";

    beforeCommand(fnName, _api.glDeleteTransformFeedbacks);
    _api.glDeleteTransformFeedbacks(n, reinterpret_cast<const GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glDrawTransformFeedbackNV().
void NVTransformFeedback2API::drawTransformFeedback(PrimitiveType mode,
                                                    TransformFeedbackName id) const
{
    static const char *fnName = "glDrawTransformFeedbackNV";

    beforeCommand(fnName, _api.glDrawTransformFeedback);
    _api.glDrawTransformFeedback(toScalar(mode), id.ID);
    afterCommand(fnName);
}

// Calls glGenTransformFeedbacksNV().
void NVTransformFeedback2API::genTransformFeedbacks(GLsizei n,
                                                    TransformFeedbackName *ids) const
{
    static const char *fnName = "glGenTransformFeedbacksNV";

    beforeCommand(fnName, _api.glGenTransformFeedbacks);
    _api.glGenTransformFeedbacks(n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glIsTransformFeedbackNV().
Boolean NVTransformFeedback2API::isTransformFeedback(TransformFeedbackName id) const
{
    static const char *fnName = "glIsTransformFeedbackNV";

    beforeCommand(fnName, _api.glIsTransformFeedback);
    GLboolean result = _api.glIsTransformFeedback(id.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glPauseTransformFeedbackNV().
void NVTransformFeedback2API::pauseTransformFeedback() const
{
    static const char *fnName = "glPauseTransformFeedbackNV";

    beforeCommand(fnName, _api.glPauseTransformFeedback);
    _api.glPauseTransformFeedback();
    afterCommand(fnName);
}

// Calls glResumeTransformFeedbackNV().
void NVTransformFeedback2API::resumeTransformFeedback() const
{
    static const char *fnName = "glResumeTransformFeedbackNV";

    beforeCommand(fnName, _api.glResumeTransformFeedback);
    _api.glResumeTransformFeedback();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVdpauInteropAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vdpau_interop extension.
NVVdpauInteropAPI::NVVdpauInteropAPI() :
    BaseExtension("GL_NV_vdpau_interop")
{
}

// Grant read-only access to the underlying function pointers.
const NVVdpauInterop &NVVdpauInteropAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vdpau_interop entry points.
void NVVdpauInteropAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVDPAUFiniNV().
void NVVdpauInteropAPI::vdpauFini() const
{
    static const char *fnName = "glVDPAUFiniNV";

    beforeCommand(fnName, _api.glVDPAUFini);
    _api.glVDPAUFini();
    afterCommand(fnName);
}

// Calls glVDPAUGetSurfaceivNV().
void NVVdpauInteropAPI::vdpauGetSurfaceIV(GLvdpauSurfaceNV surface, GLenum pname,
                                          GLsizei count, GLsizei *length,
                                          GLint *values) const
{
    static const char *fnName = "glVDPAUGetSurfaceivNV";

    beforeCommand(fnName, _api.glVDPAUGetSurfaceiv);
    _api.glVDPAUGetSurfaceiv(surface, pname, count, length, values);
    afterCommand(fnName);
}

// Calls glVDPAUInitNV().
void NVVdpauInteropAPI::vdpauInit(const void *vdpDevice,
                                  const void *getProcAddress) const
{
    static const char *fnName = "glVDPAUInitNV";

    beforeCommand(fnName, _api.glVDPAUInit);
    _api.glVDPAUInit(vdpDevice, getProcAddress);
    afterCommand(fnName);
}

// Calls glVDPAUIsSurfaceNV().
Boolean NVVdpauInteropAPI::vdpauIsSurface(GLvdpauSurfaceNV surface) const
{
    static const char *fnName = "glVDPAUIsSurfaceNV";

    beforeCommand(fnName, _api.glVDPAUIsSurface);
    GLboolean result = _api.glVDPAUIsSurface(surface);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glVDPAUMapSurfacesNV().
void NVVdpauInteropAPI::vdpauMapSurfaces(GLsizei numSurfaces,
                                         const GLvdpauSurfaceNV *surfaces) const
{
    static const char *fnName = "glVDPAUMapSurfacesNV";

    beforeCommand(fnName, _api.glVDPAUMapSurfaces);
    _api.glVDPAUMapSurfaces(numSurfaces, surfaces);
    afterCommand(fnName);
}

// Calls glVDPAURegisterOutputSurfaceNV().
GLvdpauSurfaceNV NVVdpauInteropAPI::vdpauRegisterOutputSurface(const void *vdpSurface,
                                                               GLenum target,
                                                               GLsizei numTextureNames,
                                                               const GLuint *textureNames) const
{
    static const char *fnName = "glVDPAURegisterOutputSurfaceNV";

    beforeCommand(fnName, _api.glVDPAURegisterOutputSurface);
    GLvdpauSurfaceNV result = _api.glVDPAURegisterOutputSurface(vdpSurface,
                                                                target,
                                                                numTextureNames,
                                                                textureNames);
    afterCommand(fnName);

    return result;
}

// Calls glVDPAURegisterVideoSurfaceNV().
GLvdpauSurfaceNV NVVdpauInteropAPI::vdpauRegisterVideoSurface(const void *vdpSurface,
                                                              GLenum target,
                                                              GLsizei numTextureNames,
                                                              const GLuint *textureNames) const
{
    static const char *fnName = "glVDPAURegisterVideoSurfaceNV";

    beforeCommand(fnName, _api.glVDPAURegisterVideoSurface);
    GLvdpauSurfaceNV result = _api.glVDPAURegisterVideoSurface(vdpSurface,
                                                               target,
                                                               numTextureNames,
                                                               textureNames);
    afterCommand(fnName);

    return result;
}

// Calls glVDPAUSurfaceAccessNV().
void NVVdpauInteropAPI::vdpauSurfaceAccess(GLvdpauSurfaceNV surface,
                                           GLenum access) const
{
    static const char *fnName = "glVDPAUSurfaceAccessNV";

    beforeCommand(fnName, _api.glVDPAUSurfaceAccess);
    _api.glVDPAUSurfaceAccess(surface, access);
    afterCommand(fnName);
}

// Calls glVDPAUUnmapSurfacesNV().
void NVVdpauInteropAPI::vdpauUnmapSurfaces(GLsizei numSurface,
                                           const GLvdpauSurfaceNV *surfaces) const
{
    static const char *fnName = "glVDPAUUnmapSurfacesNV";

    beforeCommand(fnName, _api.glVDPAUUnmapSurfaces);
    _api.glVDPAUUnmapSurfaces(numSurface, surfaces);
    afterCommand(fnName);
}

// Calls glVDPAUUnregisterSurfaceNV().
void NVVdpauInteropAPI::vdpauUnregisterSurface(GLvdpauSurfaceNV surface) const
{
    static const char *fnName = "glVDPAUUnregisterSurfaceNV";

    beforeCommand(fnName, _api.glVDPAUUnregisterSurface);
    _api.glVDPAUUnregisterSurface(surface);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVdpauINTEROP2API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vdpau_interop2 extension.
NVVdpauINTEROP2API::NVVdpauINTEROP2API() :
    BaseExtension("GL_NV_vdpau_interop2")
{
}

// Grant read-only access to the underlying function pointers.
const NVVdpauINTEROP2 &NVVdpauINTEROP2API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vdpau_interop2 entry points.
void NVVdpauINTEROP2API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVDPAURegisterVideoSurfaceWithPictureStructureNV().
GLvdpauSurfaceNV NVVdpauINTEROP2API::vdpauRegisterVideoSurfaceWithPictureStructure(const void *vdpSurface,
                                                                                   GLenum target,
                                                                                   GLsizei numTextureNames,
                                                                                   const GLuint *textureNames,
                                                                                   Boolean isFrameStructure) const
{
    static const char *fnName = "glVDPAURegisterVideoSurfaceWithPictureStructureNV";

    beforeCommand(fnName, _api.glVDPAURegisterVideoSurfaceWithPictureStructure);
    GLvdpauSurfaceNV result = _api.glVDPAURegisterVideoSurfaceWithPictureStructure(vdpSurface,
                                                                                   target,
                                                                                   numTextureNames,
                                                                                   textureNames,
                                                                                   toScalar(isFrameStructure));
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexArrayRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vertex_array_range extension.
NVVertexArrayRangeAPI::NVVertexArrayRangeAPI() :
    BaseExtension("GL_NV_vertex_array_range")
{
}

// Grant read-only access to the underlying function pointers.
const NVVertexArrayRange &NVVertexArrayRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vertex_array_range entry points.
void NVVertexArrayRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFlushVertexArrayRangeNV().
void NVVertexArrayRangeAPI::flushVertexArrayRange() const
{
    static const char *fnName = "glFlushVertexArrayRangeNV";

    beforeCommand(fnName, _api.glFlushVertexArrayRange);
    _api.glFlushVertexArrayRange();
    afterCommand(fnName);
}

// Calls glVertexArrayRangeNV().
void NVVertexArrayRangeAPI::vertexArrayRange(GLsizei length, const void *pointer) const
{
    static const char *fnName = "glVertexArrayRangeNV";

    beforeCommand(fnName, _api.glVertexArrayRange);
    _api.glVertexArrayRange(length, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexAttribInteger64BITAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vertex_attrib_integer_64bit extension.
NVVertexAttribInteger64BITAPI::NVVertexAttribInteger64BITAPI() :
    BaseExtension("GL_NV_vertex_attrib_integer_64bit")
{
}

// Grant read-only access to the underlying function pointers.
const NVVertexAttribInteger64BIT &NVVertexAttribInteger64BITAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vertex_attrib_integer_64bit entry points.
void NVVertexAttribInteger64BITAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetVertexAttribLi64vNV().
void NVVertexAttribInteger64BITAPI::getVertexAttribLI64V(GLuint index,
                                                         VertexAttribEnum pname,
                                                         GLint64EXT *params) const
{
    static const char *fnName = "glGetVertexAttribLi64vNV";

    beforeCommand(fnName, _api.glGetVertexAttribLi64v);
    _api.glGetVertexAttribLi64v(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribLui64vNV().
void NVVertexAttribInteger64BITAPI::getVertexAttribLUI64(GLuint index,
                                                         VertexAttribEnum pname,
                                                         GLuint64EXT *params) const
{
    static const char *fnName = "glGetVertexAttribLui64vNV";

    beforeCommand(fnName, _api.glGetVertexAttribLui64v);
    _api.glGetVertexAttribLui64v(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glVertexAttribL1i64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL1I64(GLuint index, GLint64EXT x) const
{
    static const char *fnName = "glVertexAttribL1i64NV";

    beforeCommand(fnName, _api.glVertexAttribL1i64);
    _api.glVertexAttribL1i64(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribL1i64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL1I64V(GLuint index,
                                                       const GLint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL1i64vNV";

    beforeCommand(fnName, _api.glVertexAttribL1i64v);
    _api.glVertexAttribL1i64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL1ui64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL1UI64(GLuint index,
                                                       GLuint64EXT x) const
{
    static const char *fnName = "glVertexAttribL1ui64NV";

    beforeCommand(fnName, _api.glVertexAttribL1ui64);
    _api.glVertexAttribL1ui64(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribL1ui64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL1UI64(GLuint index,
                                                       const GLuint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL1ui64vNV";

    beforeCommand(fnName, _api.glVertexAttribL1ui64v);
    _api.glVertexAttribL1ui64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL2i64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL2I64(GLuint index, GLint64EXT x,
                                                      GLint64EXT y) const
{
    static const char *fnName = "glVertexAttribL2i64NV";

    beforeCommand(fnName, _api.glVertexAttribL2i64);
    _api.glVertexAttribL2i64(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribL2i64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL2I64V(GLuint index,
                                                       const GLint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL2i64vNV";

    beforeCommand(fnName, _api.glVertexAttribL2i64v);
    _api.glVertexAttribL2i64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL2ui64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL2UI64(GLuint index,
                                                       GLuint64EXT x,
                                                       GLuint64EXT y) const
{
    static const char *fnName = "glVertexAttribL2ui64NV";

    beforeCommand(fnName, _api.glVertexAttribL2ui64);
    _api.glVertexAttribL2ui64(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribL2ui64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL2UI64(GLuint index,
                                                       const GLuint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL2ui64vNV";

    beforeCommand(fnName, _api.glVertexAttribL2ui64v);
    _api.glVertexAttribL2ui64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL3i64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL3I64(GLuint index, GLint64EXT x,
                                                      GLint64EXT y, GLint64EXT z) const
{
    static const char *fnName = "glVertexAttribL3i64NV";

    beforeCommand(fnName, _api.glVertexAttribL3i64);
    _api.glVertexAttribL3i64(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribL3i64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL3I64V(GLuint index,
                                                       const GLint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL3i64vNV";

    beforeCommand(fnName, _api.glVertexAttribL3i64v);
    _api.glVertexAttribL3i64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL3ui64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL3UI64(GLuint index,
                                                       GLuint64EXT x,
                                                       GLuint64EXT y,
                                                       GLuint64EXT z) const
{
    static const char *fnName = "glVertexAttribL3ui64NV";

    beforeCommand(fnName, _api.glVertexAttribL3ui64);
    _api.glVertexAttribL3ui64(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribL3ui64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL3UI64(GLuint index,
                                                       const GLuint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL3ui64vNV";

    beforeCommand(fnName, _api.glVertexAttribL3ui64v);
    _api.glVertexAttribL3ui64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL4i64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL4I64(GLuint index, GLint64EXT x,
                                                      GLint64EXT y, GLint64EXT z,
                                                      GLint64EXT w) const
{
    static const char *fnName = "glVertexAttribL4i64NV";

    beforeCommand(fnName, _api.glVertexAttribL4i64);
    _api.glVertexAttribL4i64(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribL4i64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL4I64V(GLuint index,
                                                       const GLint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL4i64vNV";

    beforeCommand(fnName, _api.glVertexAttribL4i64v);
    _api.glVertexAttribL4i64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL4ui64NV().
void NVVertexAttribInteger64BITAPI::vertexAttribL4UI64(GLuint index,
                                                       GLuint64EXT x,
                                                       GLuint64EXT y,
                                                       GLuint64EXT z,
                                                       GLuint64EXT w) const
{
    static const char *fnName = "glVertexAttribL4ui64NV";

    beforeCommand(fnName, _api.glVertexAttribL4ui64);
    _api.glVertexAttribL4ui64(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribL4ui64vNV().
void NVVertexAttribInteger64BITAPI::vertexAttribL4UI64(GLuint index,
                                                       const GLuint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL4ui64vNV";

    beforeCommand(fnName, _api.glVertexAttribL4ui64v);
    _api.glVertexAttribL4ui64v(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribLFormatNV().
void NVVertexAttribInteger64BITAPI::vertexAttribLFormat(GLuint index, GLint size,
                                                        VertexAttribLType type,
                                                        GLsizei stride) const
{
    static const char *fnName = "glVertexAttribLFormatNV";

    beforeCommand(fnName, _api.glVertexAttribLFormat);
    _api.glVertexAttribLFormat(index, size, toScalar(type), stride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexBufferUnifiedMemoryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vertex_buffer_unified_memory extension.
NVVertexBufferUnifiedMemoryAPI::NVVertexBufferUnifiedMemoryAPI() :
    BaseExtension("GL_NV_vertex_buffer_unified_memory")
{
}

// Grant read-only access to the underlying function pointers.
const NVVertexBufferUnifiedMemory &NVVertexBufferUnifiedMemoryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vertex_buffer_unified_memory entry points.
void NVVertexBufferUnifiedMemoryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferAddressRangeNV().
void NVVertexBufferUnifiedMemoryAPI::bufferAddressRange(GLenum pname,
                                                        GLuint index,
                                                        GLuint64EXT address,
                                                        GLsizeiptr length) const
{
    static const char *fnName = "glBufferAddressRangeNV";

    beforeCommand(fnName, _api.glBufferAddressRange);
    _api.glBufferAddressRange(pname, index, address, length);
    afterCommand(fnName);
}

// Calls glColorFormatNV().
void NVVertexBufferUnifiedMemoryAPI::colorFormat(GLint size, GLenum type,
                                                 GLsizei stride) const
{
    static const char *fnName = "glColorFormatNV";

    beforeCommand(fnName, _api.glColorFormat);
    _api.glColorFormat(size, type, stride);
    afterCommand(fnName);
}

// Calls glEdgeFlagFormatNV().
void NVVertexBufferUnifiedMemoryAPI::edgeFlagFormat(GLsizei stride) const
{
    static const char *fnName = "glEdgeFlagFormatNV";

    beforeCommand(fnName, _api.glEdgeFlagFormat);
    _api.glEdgeFlagFormat(stride);
    afterCommand(fnName);
}

// Calls glFogCoordFormatNV().
void NVVertexBufferUnifiedMemoryAPI::fogCoordFormat(GLenum type, GLsizei stride) const
{
    static const char *fnName = "glFogCoordFormatNV";

    beforeCommand(fnName, _api.glFogCoordFormat);
    _api.glFogCoordFormat(type, stride);
    afterCommand(fnName);
}

// Calls glGetIntegerui64i_vNV().
void NVVertexBufferUnifiedMemoryAPI::getIntegerUI64(GLenum value, GLuint index,
                                                    GLuint64EXT *result) const
{
    static const char *fnName = "glGetIntegerui64i_vNV";

    beforeCommand(fnName, _api.glGetIntegerui64i_v);
    _api.glGetIntegerui64i_v(value, index, result);
    afterCommand(fnName);
}

// Calls glIndexFormatNV().
void NVVertexBufferUnifiedMemoryAPI::indexFormat(GLenum type, GLsizei stride) const
{
    static const char *fnName = "glIndexFormatNV";

    beforeCommand(fnName, _api.glIndexFormat);
    _api.glIndexFormat(type, stride);
    afterCommand(fnName);
}

// Calls glNormalFormatNV().
void NVVertexBufferUnifiedMemoryAPI::normalFormat(GLenum type, GLsizei stride) const
{
    static const char *fnName = "glNormalFormatNV";

    beforeCommand(fnName, _api.glNormalFormat);
    _api.glNormalFormat(type, stride);
    afterCommand(fnName);
}

// Calls glSecondaryColorFormatNV().
void NVVertexBufferUnifiedMemoryAPI::secondaryColorFormat(GLint size,
                                                          ColorPointerType type,
                                                          GLsizei stride) const
{
    static const char *fnName = "glSecondaryColorFormatNV";

    beforeCommand(fnName, _api.glSecondaryColorFormat);
    _api.glSecondaryColorFormat(size, toScalar(type), stride);
    afterCommand(fnName);
}

// Calls glTexCoordFormatNV().
void NVVertexBufferUnifiedMemoryAPI::texCoordFormat(GLint size, GLenum type,
                                                    GLsizei stride) const
{
    static const char *fnName = "glTexCoordFormatNV";

    beforeCommand(fnName, _api.glTexCoordFormat);
    _api.glTexCoordFormat(size, type, stride);
    afterCommand(fnName);
}

// Calls glVertexAttribFormatNV().
void NVVertexBufferUnifiedMemoryAPI::vertexAttribFormat(GLuint index, GLint size,
                                                        VertexAttribType type,
                                                        Boolean normalized,
                                                        GLsizei stride) const
{
    static const char *fnName = "glVertexAttribFormatNV";

    beforeCommand(fnName, _api.glVertexAttribFormat);
    _api.glVertexAttribFormat(index, size, toScalar(type), toScalar(normalized),
                              stride);
    afterCommand(fnName);
}

// Calls glVertexAttribIFormatNV().
void NVVertexBufferUnifiedMemoryAPI::vertexAttribIFormat(GLuint index,
                                                         GLint size,
                                                         VertexAttribIType type,
                                                         GLsizei stride) const
{
    static const char *fnName = "glVertexAttribIFormatNV";

    beforeCommand(fnName, _api.glVertexAttribIFormat);
    _api.glVertexAttribIFormat(index, size, toScalar(type), stride);
    afterCommand(fnName);
}

// Calls glVertexFormatNV().
void NVVertexBufferUnifiedMemoryAPI::vertexFormat(GLint size,
                                                  VertexPointerType type,
                                                  GLsizei stride) const
{
    static const char *fnName = "glVertexFormatNV";

    beforeCommand(fnName, _api.glVertexFormat);
    _api.glVertexFormat(size, toScalar(type), stride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexProgramAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_vertex_program extension.
NVVertexProgramAPI::NVVertexProgramAPI() :
    BaseExtension("GL_NV_vertex_program")
{
}

// Grant read-only access to the underlying function pointers.
const NVVertexProgram &NVVertexProgramAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_vertex_program entry points.
void NVVertexProgramAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAreProgramsResidentNV().
Boolean NVVertexProgramAPI::areProgramsResident(GLsizei n,
                                                const ProgramName *programs,
                                                Boolean *residences) const
{
    static const char *fnName = "glAreProgramsResidentNV";

    beforeCommand(fnName, _api.glAreProgramsResident);
    GLboolean result = _api.glAreProgramsResident(n,
                                                  reinterpret_cast<const GLuint *>(programs),
                                                  toScalarPtr(residences));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glBindProgramNV().
void NVVertexProgramAPI::bindProgram(VertexAttribEnumNV target, ProgramName id) const
{
    static const char *fnName = "glBindProgramNV";

    beforeCommand(fnName, _api.glBindProgram);
    _api.glBindProgram(toScalar(target), id.ID);
    afterCommand(fnName);
}

// Calls glDeleteProgramsNV().
void NVVertexProgramAPI::deletePrograms(GLsizei n, const ProgramName *programs) const
{
    static const char *fnName = "glDeleteProgramsNV";

    beforeCommand(fnName, _api.glDeletePrograms);
    _api.glDeletePrograms(n, reinterpret_cast<const GLuint *>(programs));
    afterCommand(fnName);
}

// Calls glExecuteProgramNV().
void NVVertexProgramAPI::executeProgram(VertexAttribEnumNV target, GLuint id,
                                        const GLfloat *params) const
{
    static const char *fnName = "glExecuteProgramNV";

    beforeCommand(fnName, _api.glExecuteProgram);
    _api.glExecuteProgram(toScalar(target), id, params);
    afterCommand(fnName);
}

// Calls glGenProgramsNV().
void NVVertexProgramAPI::genPrograms(GLsizei n, ProgramName *programs) const
{
    static const char *fnName = "glGenProgramsNV";

    beforeCommand(fnName, _api.glGenPrograms);
    _api.glGenPrograms(n, reinterpret_cast<GLuint *>(programs));
    afterCommand(fnName);
}

// Calls glGetProgramParameterdvNV().
void NVVertexProgramAPI::getProgramParameterDV(VertexAttribEnumNV target,
                                               GLuint index,
                                               VertexAttribEnumNV pname,
                                               GLdouble *params) const
{
    static const char *fnName = "glGetProgramParameterdvNV";

    beforeCommand(fnName, _api.glGetProgramParameterdv);
    _api.glGetProgramParameterdv(toScalar(target), index, toScalar(pname),
                                 params);
    afterCommand(fnName);
}

// Calls glGetProgramParameterfvNV().
void NVVertexProgramAPI::getProgramParameterFV(VertexAttribEnumNV target,
                                               GLuint index,
                                               VertexAttribEnumNV pname,
                                               GLfloat *params) const
{
    static const char *fnName = "glGetProgramParameterfvNV";

    beforeCommand(fnName, _api.glGetProgramParameterfv);
    _api.glGetProgramParameterfv(toScalar(target), index, toScalar(pname),
                                 params);
    afterCommand(fnName);
}

// Calls glGetProgramStringNV().
void NVVertexProgramAPI::getProgramString(ProgramName id,
                                          VertexAttribEnumNV pname,
                                          GLubyte *program) const
{
    static const char *fnName = "glGetProgramStringNV";

    beforeCommand(fnName, _api.glGetProgramString);
    _api.glGetProgramString(id.ID, toScalar(pname), program);
    afterCommand(fnName);
}

// Calls glGetProgramivNV().
void NVVertexProgramAPI::getProgramIV(ProgramName id, VertexAttribEnumNV pname,
                                      GLint *params) const
{
    static const char *fnName = "glGetProgramivNV";

    beforeCommand(fnName, _api.glGetProgramiv);
    _api.glGetProgramiv(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTrackMatrixivNV().
void NVVertexProgramAPI::getTrackMatrixIV(VertexAttribEnumNV target,
                                          GLuint address,
                                          VertexAttribEnumNV pname,
                                          GLint *params) const
{
    static const char *fnName = "glGetTrackMatrixivNV";

    beforeCommand(fnName, _api.glGetTrackMatrixiv);
    _api.glGetTrackMatrixiv(toScalar(target), address, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribPointervNV().
void NVVertexProgramAPI::getVertexAttribPointerV(GLuint index,
                                                 VertexAttribEnumNV pname,
                                                 void **pointer) const
{
    static const char *fnName = "glGetVertexAttribPointervNV";

    beforeCommand(fnName, _api.glGetVertexAttribPointerv);
    _api.glGetVertexAttribPointerv(index, toScalar(pname), pointer);
    afterCommand(fnName);
}

// Calls glGetVertexAttribdvNV().
void NVVertexProgramAPI::getVertexAttribDV(GLuint index,
                                           VertexAttribEnumNV pname,
                                           GLdouble *params) const
{
    static const char *fnName = "glGetVertexAttribdvNV";

    beforeCommand(fnName, _api.glGetVertexAttribdv);
    _api.glGetVertexAttribdv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribfvNV().
void NVVertexProgramAPI::getVertexAttribFV(GLuint index,
                                           VertexAttribEnumNV pname,
                                           GLfloat *params) const
{
    static const char *fnName = "glGetVertexAttribfvNV";

    beforeCommand(fnName, _api.glGetVertexAttribfv);
    _api.glGetVertexAttribfv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribivNV().
void NVVertexProgramAPI::getVertexAttribIV(GLuint index,
                                           VertexAttribEnumNV pname,
                                           GLint *params) const
{
    static const char *fnName = "glGetVertexAttribivNV";

    beforeCommand(fnName, _api.glGetVertexAttribiv);
    _api.glGetVertexAttribiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsProgramNV().
Boolean NVVertexProgramAPI::isProgram(ProgramName id) const
{
    static const char *fnName = "glIsProgramNV";

    beforeCommand(fnName, _api.glIsProgram);
    GLboolean result = _api.glIsProgram(id.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glLoadProgramNV().
void NVVertexProgramAPI::loadProgram(VertexAttribEnumNV target, GLuint id,
                                     GLsizei len, const GLubyte *program) const
{
    static const char *fnName = "glLoadProgramNV";

    beforeCommand(fnName, _api.glLoadProgram);
    _api.glLoadProgram(toScalar(target), id, len, program);
    afterCommand(fnName);
}

// Calls glProgramParameter4dNV().
void NVVertexProgramAPI::programParameter4D(VertexAttribEnumNV target,
                                            GLuint index, GLdouble x, GLdouble y,
                                            GLdouble z, GLdouble w) const
{
    static const char *fnName = "glProgramParameter4dNV";

    beforeCommand(fnName, _api.glProgramParameter4d);
    _api.glProgramParameter4d(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramParameter4dvNV().
void NVVertexProgramAPI::programParameter4DV(VertexAttribEnumNV target,
                                             GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glProgramParameter4dvNV";

    beforeCommand(fnName, _api.glProgramParameter4dv);
    _api.glProgramParameter4dv(toScalar(target), index, v);
    afterCommand(fnName);
}

// Calls glProgramParameter4fNV().
void NVVertexProgramAPI::programParameter4F(VertexAttribEnumNV target,
                                            GLuint index, GLfloat x, GLfloat y,
                                            GLfloat z, GLfloat w) const
{
    static const char *fnName = "glProgramParameter4fNV";

    beforeCommand(fnName, _api.glProgramParameter4f);
    _api.glProgramParameter4f(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramParameter4fvNV().
void NVVertexProgramAPI::programParameter4FV(VertexAttribEnumNV target,
                                             GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glProgramParameter4fvNV";

    beforeCommand(fnName, _api.glProgramParameter4fv);
    _api.glProgramParameter4fv(toScalar(target), index, v);
    afterCommand(fnName);
}

// Calls glProgramParameters4dvNV().
void NVVertexProgramAPI::programParameters4DV(VertexAttribEnumNV target,
                                              GLuint index, GLsizei count,
                                              const GLdouble *v) const
{
    static const char *fnName = "glProgramParameters4dvNV";

    beforeCommand(fnName, _api.glProgramParameters4dv);
    _api.glProgramParameters4dv(toScalar(target), index, count, v);
    afterCommand(fnName);
}

// Calls glProgramParameters4fvNV().
void NVVertexProgramAPI::programParameters4FV(VertexAttribEnumNV target,
                                              GLuint index, GLsizei count,
                                              const GLfloat *v) const
{
    static const char *fnName = "glProgramParameters4fvNV";

    beforeCommand(fnName, _api.glProgramParameters4fv);
    _api.glProgramParameters4fv(toScalar(target), index, count, v);
    afterCommand(fnName);
}

// Calls glRequestResidentProgramsNV().
void NVVertexProgramAPI::requestResidentPrograms(GLsizei n,
                                                 const ProgramName *programs) const
{
    static const char *fnName = "glRequestResidentProgramsNV";

    beforeCommand(fnName, _api.glRequestResidentPrograms);
    _api.glRequestResidentPrograms(n, reinterpret_cast<const GLuint *>(programs));
    afterCommand(fnName);
}

// Calls glTrackMatrixNV().
void NVVertexProgramAPI::trackMatrix(VertexAttribEnumNV target, GLuint address,
                                     VertexAttribEnumNV matrix,
                                     VertexAttribEnumNV transform) const
{
    static const char *fnName = "glTrackMatrixNV";

    beforeCommand(fnName, _api.glTrackMatrix);
    _api.glTrackMatrix(toScalar(target), address, toScalar(matrix),
                       toScalar(transform));
    afterCommand(fnName);
}

// Calls glVertexAttrib1dNV().
void NVVertexProgramAPI::vertexAttrib1D(GLuint index, GLdouble x) const
{
    static const char *fnName = "glVertexAttrib1dNV";

    beforeCommand(fnName, _api.glVertexAttrib1d);
    _api.glVertexAttrib1d(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1dvNV().
void NVVertexProgramAPI::vertexAttrib1DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib1dvNV";

    beforeCommand(fnName, _api.glVertexAttrib1dv);
    _api.glVertexAttrib1dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1fNV().
void NVVertexProgramAPI::vertexAttrib1F(GLuint index, GLfloat x) const
{
    static const char *fnName = "glVertexAttrib1fNV";

    beforeCommand(fnName, _api.glVertexAttrib1f);
    _api.glVertexAttrib1f(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1fvNV().
void NVVertexProgramAPI::vertexAttrib1FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib1fvNV";

    beforeCommand(fnName, _api.glVertexAttrib1fv);
    _api.glVertexAttrib1fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1sNV().
void NVVertexProgramAPI::vertexAttrib1S(GLuint index, GLshort x) const
{
    static const char *fnName = "glVertexAttrib1sNV";

    beforeCommand(fnName, _api.glVertexAttrib1s);
    _api.glVertexAttrib1s(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1svNV().
void NVVertexProgramAPI::vertexAttrib1SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib1svNV";

    beforeCommand(fnName, _api.glVertexAttrib1sv);
    _api.glVertexAttrib1sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2dNV().
void NVVertexProgramAPI::vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const
{
    static const char *fnName = "glVertexAttrib2dNV";

    beforeCommand(fnName, _api.glVertexAttrib2d);
    _api.glVertexAttrib2d(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2dvNV().
void NVVertexProgramAPI::vertexAttrib2DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib2dvNV";

    beforeCommand(fnName, _api.glVertexAttrib2dv);
    _api.glVertexAttrib2dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2fNV().
void NVVertexProgramAPI::vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const
{
    static const char *fnName = "glVertexAttrib2fNV";

    beforeCommand(fnName, _api.glVertexAttrib2f);
    _api.glVertexAttrib2f(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2fvNV().
void NVVertexProgramAPI::vertexAttrib2FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib2fvNV";

    beforeCommand(fnName, _api.glVertexAttrib2fv);
    _api.glVertexAttrib2fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2sNV().
void NVVertexProgramAPI::vertexAttrib2S(GLuint index, GLshort x, GLshort y) const
{
    static const char *fnName = "glVertexAttrib2sNV";

    beforeCommand(fnName, _api.glVertexAttrib2s);
    _api.glVertexAttrib2s(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2svNV().
void NVVertexProgramAPI::vertexAttrib2SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib2svNV";

    beforeCommand(fnName, _api.glVertexAttrib2sv);
    _api.glVertexAttrib2sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3dNV().
void NVVertexProgramAPI::vertexAttrib3D(GLuint index, GLdouble x, GLdouble y,
                                        GLdouble z) const
{
    static const char *fnName = "glVertexAttrib3dNV";

    beforeCommand(fnName, _api.glVertexAttrib3d);
    _api.glVertexAttrib3d(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3dvNV().
void NVVertexProgramAPI::vertexAttrib3DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib3dvNV";

    beforeCommand(fnName, _api.glVertexAttrib3dv);
    _api.glVertexAttrib3dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3fNV().
void NVVertexProgramAPI::vertexAttrib3F(GLuint index, GLfloat x, GLfloat y,
                                        GLfloat z) const
{
    static const char *fnName = "glVertexAttrib3fNV";

    beforeCommand(fnName, _api.glVertexAttrib3f);
    _api.glVertexAttrib3f(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3fvNV().
void NVVertexProgramAPI::vertexAttrib3FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib3fvNV";

    beforeCommand(fnName, _api.glVertexAttrib3fv);
    _api.glVertexAttrib3fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3sNV().
void NVVertexProgramAPI::vertexAttrib3S(GLuint index, GLshort x, GLshort y,
                                        GLshort z) const
{
    static const char *fnName = "glVertexAttrib3sNV";

    beforeCommand(fnName, _api.glVertexAttrib3s);
    _api.glVertexAttrib3s(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3svNV().
void NVVertexProgramAPI::vertexAttrib3SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib3svNV";

    beforeCommand(fnName, _api.glVertexAttrib3sv);
    _api.glVertexAttrib3sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4dNV().
void NVVertexProgramAPI::vertexAttrib4D(GLuint index, GLdouble x, GLdouble y,
                                        GLdouble z, GLdouble w) const
{
    static const char *fnName = "glVertexAttrib4dNV";

    beforeCommand(fnName, _api.glVertexAttrib4d);
    _api.glVertexAttrib4d(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4dvNV().
void NVVertexProgramAPI::vertexAttrib4DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib4dvNV";

    beforeCommand(fnName, _api.glVertexAttrib4dv);
    _api.glVertexAttrib4dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4fNV().
void NVVertexProgramAPI::vertexAttrib4F(GLuint index, GLfloat x, GLfloat y,
                                        GLfloat z, GLfloat w) const
{
    static const char *fnName = "glVertexAttrib4fNV";

    beforeCommand(fnName, _api.glVertexAttrib4f);
    _api.glVertexAttrib4f(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4fvNV().
void NVVertexProgramAPI::vertexAttrib4FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib4fvNV";

    beforeCommand(fnName, _api.glVertexAttrib4fv);
    _api.glVertexAttrib4fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4sNV().
void NVVertexProgramAPI::vertexAttrib4S(GLuint index, GLshort x, GLshort y,
                                        GLshort z, GLshort w) const
{
    static const char *fnName = "glVertexAttrib4sNV";

    beforeCommand(fnName, _api.glVertexAttrib4s);
    _api.glVertexAttrib4s(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4svNV().
void NVVertexProgramAPI::vertexAttrib4SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib4svNV";

    beforeCommand(fnName, _api.glVertexAttrib4sv);
    _api.glVertexAttrib4sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4ubNV().
void NVVertexProgramAPI::vertexAttrib4UB(GLuint index, GLubyte x, GLubyte y,
                                         GLubyte z, GLubyte w) const
{
    static const char *fnName = "glVertexAttrib4ubNV";

    beforeCommand(fnName, _api.glVertexAttrib4ub);
    _api.glVertexAttrib4ub(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4ubvNV().
void NVVertexProgramAPI::vertexAttrib4UBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttrib4ubvNV";

    beforeCommand(fnName, _api.glVertexAttrib4ubv);
    _api.glVertexAttrib4ubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribPointerNV().
void NVVertexProgramAPI::vertexAttribPointer(GLuint index, GLint fsize,
                                             VertexAttribEnumNV type,
                                             GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glVertexAttribPointerNV";

    beforeCommand(fnName, _api.glVertexAttribPointer);
    _api.glVertexAttribPointer(index, fsize, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glVertexAttribs1dvNV().
void NVVertexProgramAPI::vertexAttribs1DV(GLuint index, GLsizei count,
                                          const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribs1dvNV";

    beforeCommand(fnName, _api.glVertexAttribs1dv);
    _api.glVertexAttribs1dv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs1fvNV().
void NVVertexProgramAPI::vertexAttribs1FV(GLuint index, GLsizei count,
                                          const GLfloat *v) const
{
    static const char *fnName = "glVertexAttribs1fvNV";

    beforeCommand(fnName, _api.glVertexAttribs1fv);
    _api.glVertexAttribs1fv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs1svNV().
void NVVertexProgramAPI::vertexAttribs1SV(GLuint index, GLsizei count,
                                          const GLshort *v) const
{
    static const char *fnName = "glVertexAttribs1svNV";

    beforeCommand(fnName, _api.glVertexAttribs1sv);
    _api.glVertexAttribs1sv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs2dvNV().
void NVVertexProgramAPI::vertexAttribs2DV(GLuint index, GLsizei count,
                                          const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribs2dvNV";

    beforeCommand(fnName, _api.glVertexAttribs2dv);
    _api.glVertexAttribs2dv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs2fvNV().
void NVVertexProgramAPI::vertexAttribs2FV(GLuint index, GLsizei count,
                                          const GLfloat *v) const
{
    static const char *fnName = "glVertexAttribs2fvNV";

    beforeCommand(fnName, _api.glVertexAttribs2fv);
    _api.glVertexAttribs2fv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs2svNV().
void NVVertexProgramAPI::vertexAttribs2SV(GLuint index, GLsizei count,
                                          const GLshort *v) const
{
    static const char *fnName = "glVertexAttribs2svNV";

    beforeCommand(fnName, _api.glVertexAttribs2sv);
    _api.glVertexAttribs2sv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs3dvNV().
void NVVertexProgramAPI::vertexAttribs3DV(GLuint index, GLsizei count,
                                          const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribs3dvNV";

    beforeCommand(fnName, _api.glVertexAttribs3dv);
    _api.glVertexAttribs3dv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs3fvNV().
void NVVertexProgramAPI::vertexAttribs3FV(GLuint index, GLsizei count,
                                          const GLfloat *v) const
{
    static const char *fnName = "glVertexAttribs3fvNV";

    beforeCommand(fnName, _api.glVertexAttribs3fv);
    _api.glVertexAttribs3fv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs3svNV().
void NVVertexProgramAPI::vertexAttribs3SV(GLuint index, GLsizei count,
                                          const GLshort *v) const
{
    static const char *fnName = "glVertexAttribs3svNV";

    beforeCommand(fnName, _api.glVertexAttribs3sv);
    _api.glVertexAttribs3sv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs4dvNV().
void NVVertexProgramAPI::vertexAttribs4DV(GLuint index, GLsizei count,
                                          const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribs4dvNV";

    beforeCommand(fnName, _api.glVertexAttribs4dv);
    _api.glVertexAttribs4dv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs4fvNV().
void NVVertexProgramAPI::vertexAttribs4FV(GLuint index, GLsizei count,
                                          const GLfloat *v) const
{
    static const char *fnName = "glVertexAttribs4fvNV";

    beforeCommand(fnName, _api.glVertexAttribs4fv);
    _api.glVertexAttribs4fv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs4svNV().
void NVVertexProgramAPI::vertexAttribs4SV(GLuint index, GLsizei count,
                                          const GLshort *v) const
{
    static const char *fnName = "glVertexAttribs4svNV";

    beforeCommand(fnName, _api.glVertexAttribs4sv);
    _api.glVertexAttribs4sv(index, count, v);
    afterCommand(fnName);
}

// Calls glVertexAttribs4ubvNV().
void NVVertexProgramAPI::vertexAttribs4UBV(GLuint index, GLsizei count,
                                           const GLubyte *v) const
{
    static const char *fnName = "glVertexAttribs4ubvNV";

    beforeCommand(fnName, _api.glVertexAttribs4ubv);
    _api.glVertexAttribs4ubv(index, count, v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCaptureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_video_capture extension.
NVVideoCaptureAPI::NVVideoCaptureAPI() :
    BaseExtension("GL_NV_video_capture")
{
}

// Grant read-only access to the underlying function pointers.
const NVVideoCapture &NVVideoCaptureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_video_capture entry points.
void NVVideoCaptureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginVideoCaptureNV().
void NVVideoCaptureAPI::beginVideoCapture(GLuint video_capture_slot) const
{
    static const char *fnName = "glBeginVideoCaptureNV";

    beforeCommand(fnName, _api.glBeginVideoCapture);
    _api.glBeginVideoCapture(video_capture_slot);
    afterCommand(fnName);
}

// Calls glBindVideoCaptureStreamBufferNV().
void NVVideoCaptureAPI::bindVideoCaptureStreamBuffer(GLuint video_capture_slot,
                                                     GLuint stream,
                                                     GLenum frame_region,
                                                     GLintptrARB offset) const
{
    static const char *fnName = "glBindVideoCaptureStreamBufferNV";

    beforeCommand(fnName, _api.glBindVideoCaptureStreamBuffer);
    _api.glBindVideoCaptureStreamBuffer(video_capture_slot, stream, frame_region,
                                        offset);
    afterCommand(fnName);
}

// Calls glBindVideoCaptureStreamTextureNV().
void NVVideoCaptureAPI::bindVideoCaptureStreamTexture(GLuint video_capture_slot,
                                                      GLuint stream,
                                                      GLenum frame_region,
                                                      GLenum target,
                                                      TextureName texture) const
{
    static const char *fnName = "glBindVideoCaptureStreamTextureNV";

    beforeCommand(fnName, _api.glBindVideoCaptureStreamTexture);
    _api.glBindVideoCaptureStreamTexture(video_capture_slot, stream,
                                         frame_region, target, texture.ID);
    afterCommand(fnName);
}

// Calls glEndVideoCaptureNV().
void NVVideoCaptureAPI::endVideoCapture(GLuint video_capture_slot) const
{
    static const char *fnName = "glEndVideoCaptureNV";

    beforeCommand(fnName, _api.glEndVideoCapture);
    _api.glEndVideoCapture(video_capture_slot);
    afterCommand(fnName);
}

// Calls glGetVideoCaptureStreamdvNV().
void NVVideoCaptureAPI::getVideoCaptureStreamDV(GLuint video_capture_slot,
                                                GLuint stream, GLenum pname,
                                                GLdouble *params) const
{
    static const char *fnName = "glGetVideoCaptureStreamdvNV";

    beforeCommand(fnName, _api.glGetVideoCaptureStreamdv);
    _api.glGetVideoCaptureStreamdv(video_capture_slot, stream, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideoCaptureStreamfvNV().
void NVVideoCaptureAPI::getVideoCaptureStreamFV(GLuint video_capture_slot,
                                                GLuint stream, GLenum pname,
                                                GLfloat *params) const
{
    static const char *fnName = "glGetVideoCaptureStreamfvNV";

    beforeCommand(fnName, _api.glGetVideoCaptureStreamfv);
    _api.glGetVideoCaptureStreamfv(video_capture_slot, stream, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideoCaptureStreamivNV().
void NVVideoCaptureAPI::getVideoCaptureStreamIV(GLuint video_capture_slot,
                                                GLuint stream, GLenum pname,
                                                GLint *params) const
{
    static const char *fnName = "glGetVideoCaptureStreamivNV";

    beforeCommand(fnName, _api.glGetVideoCaptureStreamiv);
    _api.glGetVideoCaptureStreamiv(video_capture_slot, stream, pname, params);
    afterCommand(fnName);
}

// Calls glGetVideoCaptureivNV().
void NVVideoCaptureAPI::getVideoCaptureIV(GLuint video_capture_slot,
                                          GLenum pname, GLint *params) const
{
    static const char *fnName = "glGetVideoCaptureivNV";

    beforeCommand(fnName, _api.glGetVideoCaptureiv);
    _api.glGetVideoCaptureiv(video_capture_slot, pname, params);
    afterCommand(fnName);
}

// Calls glVideoCaptureNV().
GLenum NVVideoCaptureAPI::videoCapture(GLuint video_capture_slot,
                                       GLuint *sequence_num,
                                       GLuint64EXT *capture_time) const
{
    static const char *fnName = "glVideoCaptureNV";

    beforeCommand(fnName, _api.glVideoCapture);
    GLenum result = _api.glVideoCapture(video_capture_slot, sequence_num,
                                        capture_time);
    afterCommand(fnName);

    return result;
}

// Calls glVideoCaptureStreamParameterdvNV().
void NVVideoCaptureAPI::videoCaptureStreamParameterDV(GLuint video_capture_slot,
                                                      GLuint stream,
                                                      GLenum pname,
                                                      const GLdouble *params) const
{
    static const char *fnName = "glVideoCaptureStreamParameterdvNV";

    beforeCommand(fnName, _api.glVideoCaptureStreamParameterdv);
    _api.glVideoCaptureStreamParameterdv(video_capture_slot, stream, pname,
                                         params);
    afterCommand(fnName);
}

// Calls glVideoCaptureStreamParameterfvNV().
void NVVideoCaptureAPI::videoCaptureStreamParameterFV(GLuint video_capture_slot,
                                                      GLuint stream,
                                                      GLenum pname,
                                                      const GLfloat *params) const
{
    static const char *fnName = "glVideoCaptureStreamParameterfvNV";

    beforeCommand(fnName, _api.glVideoCaptureStreamParameterfv);
    _api.glVideoCaptureStreamParameterfv(video_capture_slot, stream, pname,
                                         params);
    afterCommand(fnName);
}

// Calls glVideoCaptureStreamParameterivNV().
void NVVideoCaptureAPI::videoCaptureStreamParameterIV(GLuint video_capture_slot,
                                                      GLuint stream,
                                                      GLenum pname,
                                                      const GLint *params) const
{
    static const char *fnName = "glVideoCaptureStreamParameterivNV";

    beforeCommand(fnName, _api.glVideoCaptureStreamParameteriv);
    _api.glVideoCaptureStreamParameteriv(video_capture_slot, stream, pname,
                                         params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVViewportSwizzleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_NV_viewport_swizzle extension.
NVViewportSwizzleAPI::NVViewportSwizzleAPI() :
    BaseExtension("GL_NV_viewport_swizzle")
{
}

// Grant read-only access to the underlying function pointers.
const NVViewportSwizzle &NVViewportSwizzleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_NV_viewport_swizzle entry points.
void NVViewportSwizzleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glViewportSwizzleNV().
void NVViewportSwizzleAPI::viewportSwizzle(GLuint index, GLenum swizzlex,
                                           GLenum swizzley, GLenum swizzlez,
                                           GLenum swizzlew) const
{
    static const char *fnName = "glViewportSwizzleNV";

    beforeCommand(fnName, _api.glViewportSwizzle);
    _api.glViewportSwizzle(index, swizzlex, swizzley, swizzlez, swizzlew);
    afterCommand(fnName);
}

} // namespace gl

#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// NVDxInteropAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_DX_interop extension.
NVDxInteropAPI::NVDxInteropAPI() :
    BaseExtension("WGL_NV_DX_interop")
{
}

// Grant read-only access to the underlying function pointers.
const NVDxInterop &NVDxInteropAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_DX_interop entry points.
void NVDxInteropAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglDXCloseDeviceNV().
BOOL NVDxInteropAPI::dxCloseDevice(HANDLE hDevice) const
{
    static const char *fnName = "wglDXCloseDeviceNV";

    beforeCommand(fnName, _api.wglDXCloseDevice);
    BOOL result = _api.wglDXCloseDevice(hDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglDXLockObjectsNV().
BOOL NVDxInteropAPI::dxLockObjects(HANDLE hDevice, GLint count, HANDLE *hObjects) const
{
    static const char *fnName = "wglDXLockObjectsNV";

    beforeCommand(fnName, _api.wglDXLockObjects);
    BOOL result = _api.wglDXLockObjects(hDevice, count, hObjects);
    afterCommand(fnName);

    return result;
}

// Calls wglDXObjectAccessNV().
BOOL NVDxInteropAPI::dxObjectAccess(HANDLE hObject, GLenum access) const
{
    static const char *fnName = "wglDXObjectAccessNV";

    beforeCommand(fnName, _api.wglDXObjectAccess);
    BOOL result = _api.wglDXObjectAccess(hObject, access);
    afterCommand(fnName);

    return result;
}

// Calls wglDXOpenDeviceNV().
HANDLE NVDxInteropAPI::dxOpenDevice(void *dxDevice) const
{
    static const char *fnName = "wglDXOpenDeviceNV";

    beforeCommand(fnName, _api.wglDXOpenDevice);
    HANDLE result = _api.wglDXOpenDevice(dxDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglDXRegisterObjectNV().
HANDLE NVDxInteropAPI::dxRegisterObject(HANDLE hDevice, void *dxObject,
                                        GLuint name, GLenum type, GLenum access) const
{
    static const char *fnName = "wglDXRegisterObjectNV";

    beforeCommand(fnName, _api.wglDXRegisterObject);
    HANDLE result = _api.wglDXRegisterObject(hDevice, dxObject, name, type,
                                             access);
    afterCommand(fnName);

    return result;
}

// Calls wglDXSetResourceShareHandleNV().
BOOL NVDxInteropAPI::dxSetResourceShareHandle(void *dxObject, HANDLE shareHandle) const
{
    static const char *fnName = "wglDXSetResourceShareHandleNV";

    beforeCommand(fnName, _api.wglDXSetResourceShareHandle);
    BOOL result = _api.wglDXSetResourceShareHandle(dxObject, shareHandle);
    afterCommand(fnName);

    return result;
}

// Calls wglDXUnlockObjectsNV().
BOOL NVDxInteropAPI::dxUnlockObjects(HANDLE hDevice, GLint count,
                                     HANDLE *hObjects) const
{
    static const char *fnName = "wglDXUnlockObjectsNV";

    beforeCommand(fnName, _api.wglDXUnlockObjects);
    BOOL result = _api.wglDXUnlockObjects(hDevice, count, hObjects);
    afterCommand(fnName);

    return result;
}

// Calls wglDXUnregisterObjectNV().
BOOL NVDxInteropAPI::dxUnregisterObject(HANDLE hDevice, HANDLE hObject) const
{
    static const char *fnName = "wglDXUnregisterObjectNV";

    beforeCommand(fnName, _api.wglDXUnregisterObject);
    BOOL result = _api.wglDXUnregisterObject(hDevice, hObject);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_copy_image extension.
NVCopyImageAPI::NVCopyImageAPI() :
    BaseExtension("WGL_NV_copy_image")
{
}

// Grant read-only access to the underlying function pointers.
const NVCopyImage &NVCopyImageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_copy_image entry points.
void NVCopyImageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCopyImageSubDataNV().
BOOL NVCopyImageAPI::copyImageSubData(HGLRC hSrcRC, GLuint srcName,
                                      GLenum srcTarget, GLint srcLevel,
                                      GLint srcX, GLint srcY, GLint srcZ,
                                      HGLRC hDstRC, GLuint dstName,
                                      GLenum dstTarget, GLint dstLevel,
                                      GLint dstX, GLint dstY, GLint dstZ,
                                      GLsizei width, GLsizei height,
                                      GLsizei depth) const
{
    static const char *fnName = "wglCopyImageSubDataNV";

    beforeCommand(fnName, _api.wglCopyImageSubData);
    BOOL result = _api.wglCopyImageSubData(hSrcRC, srcName, srcTarget, srcLevel,
                                           srcX, srcY, srcZ, hDstRC, dstName,
                                           dstTarget, dstLevel, dstX, dstY, dstZ,
                                           width, height, depth);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVDelayBeforeSwapAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_delay_before_swap extension.
NVDelayBeforeSwapAPI::NVDelayBeforeSwapAPI() :
    BaseExtension("WGL_NV_delay_before_swap")
{
}

// Grant read-only access to the underlying function pointers.
const NVDelayBeforeSwap &NVDelayBeforeSwapAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_delay_before_swap entry points.
void NVDelayBeforeSwapAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglDelayBeforeSwapNV().
BOOL NVDelayBeforeSwapAPI::delayBeforeSwap(HDC hDC, GLfloat seconds) const
{
    static const char *fnName = "wglDelayBeforeSwapNV";

    beforeCommand(fnName, _api.wglDelayBeforeSwap);
    BOOL result = _api.wglDelayBeforeSwap(hDC, seconds);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVGPUAffinityAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_gpu_affinity extension.
NVGPUAffinityAPI::NVGPUAffinityAPI() :
    BaseExtension("WGL_NV_gpu_affinity")
{
}

// Grant read-only access to the underlying function pointers.
const NVGPUAffinity &NVGPUAffinityAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_gpu_affinity entry points.
void NVGPUAffinityAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCreateAffinityDCNV().
HDC NVGPUAffinityAPI::createAffinityDC(const HGPUNV *phGpuList) const
{
    static const char *fnName = "wglCreateAffinityDCNV";

    beforeCommand(fnName, _api.wglCreateAffinityDC);
    HDC result = _api.wglCreateAffinityDC(phGpuList);
    afterCommand(fnName);

    return result;
}

// Calls wglDeleteDCNV().
BOOL NVGPUAffinityAPI::deleteDC(HDC hdc) const
{
    static const char *fnName = "wglDeleteDCNV";

    beforeCommand(fnName, _api.wglDeleteDC);
    BOOL result = _api.wglDeleteDC(hdc);
    afterCommand(fnName);

    return result;
}

// Calls wglEnumGpuDevicesNV().
BOOL NVGPUAffinityAPI::enumGpuDevices(HGPUNV hGpu, UINT iDeviceIndex,
                                      PGPU_DEVICE lpGpuDevice) const
{
    static const char *fnName = "wglEnumGpuDevicesNV";

    beforeCommand(fnName, _api.wglEnumGpuDevices);
    BOOL result = _api.wglEnumGpuDevices(hGpu, iDeviceIndex, lpGpuDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglEnumGpusFromAffinityDCNV().
BOOL NVGPUAffinityAPI::enumGpusFromAffinityDC(HDC hAffinityDC, UINT iGpuIndex,
                                              HGPUNV *hGpu) const
{
    static const char *fnName = "wglEnumGpusFromAffinityDCNV";

    beforeCommand(fnName, _api.wglEnumGpusFromAffinityDC);
    BOOL result = _api.wglEnumGpusFromAffinityDC(hAffinityDC, iGpuIndex, hGpu);
    afterCommand(fnName);

    return result;
}

// Calls wglEnumGpusNV().
BOOL NVGPUAffinityAPI::enumGpus(UINT iGpuIndex, HGPUNV *phGpu) const
{
    static const char *fnName = "wglEnumGpusNV";

    beforeCommand(fnName, _api.wglEnumGpus);
    BOOL result = _api.wglEnumGpus(iGpuIndex, phGpu);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideoAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_present_video extension.
NVPresentVideoAPI::NVPresentVideoAPI() :
    BaseExtension("WGL_NV_present_video")
{
}

// Grant read-only access to the underlying function pointers.
const NVPresentVideo &NVPresentVideoAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_present_video entry points.
void NVPresentVideoAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindVideoDeviceNV().
BOOL NVPresentVideoAPI::bindVideoDevice(HDC hDc, unsigned int uVideoSlot,
                                        HVIDEOOUTPUTDEVICENV hVideoDevice,
                                        const int *piAttribList) const
{
    static const char *fnName = "wglBindVideoDeviceNV";

    beforeCommand(fnName, _api.wglBindVideoDevice);
    BOOL result = _api.wglBindVideoDevice(hDc, uVideoSlot, hVideoDevice,
                                          piAttribList);
    afterCommand(fnName);

    return result;
}

// Calls wglEnumerateVideoDevicesNV().
int NVPresentVideoAPI::enumerateVideoDevices(HDC hDc,
                                             HVIDEOOUTPUTDEVICENV *phDeviceList) const
{
    static const char *fnName = "wglEnumerateVideoDevicesNV";

    beforeCommand(fnName, _api.wglEnumerateVideoDevices);
    int result = _api.wglEnumerateVideoDevices(hDc, phDeviceList);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryCurrentContextNV().
BOOL NVPresentVideoAPI::queryCurrentContext(int iAttribute, int *piValue) const
{
    static const char *fnName = "wglQueryCurrentContextNV";

    beforeCommand(fnName, _api.wglQueryCurrentContext);
    BOOL result = _api.wglQueryCurrentContext(iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVSwapGroupAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_swap_group extension.
NVSwapGroupAPI::NVSwapGroupAPI() :
    BaseExtension("WGL_NV_swap_group")
{
}

// Grant read-only access to the underlying function pointers.
const NVSwapGroup &NVSwapGroupAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_swap_group entry points.
void NVSwapGroupAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindSwapBarrierNV().
BOOL NVSwapGroupAPI::bindSwapBarrier(GLuint group, GLuint barrier) const
{
    static const char *fnName = "wglBindSwapBarrierNV";

    beforeCommand(fnName, _api.wglBindSwapBarrier);
    BOOL result = _api.wglBindSwapBarrier(group, barrier);
    afterCommand(fnName);

    return result;
}

// Calls wglJoinSwapGroupNV().
BOOL NVSwapGroupAPI::joinSwapGroup(HDC hDC, GLuint group) const
{
    static const char *fnName = "wglJoinSwapGroupNV";

    beforeCommand(fnName, _api.wglJoinSwapGroup);
    BOOL result = _api.wglJoinSwapGroup(hDC, group);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryFrameCountNV().
BOOL NVSwapGroupAPI::queryFrameCount(HDC hDC, GLuint *count) const
{
    static const char *fnName = "wglQueryFrameCountNV";

    beforeCommand(fnName, _api.wglQueryFrameCount);
    BOOL result = _api.wglQueryFrameCount(hDC, count);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryMaxSwapGroupsNV().
BOOL NVSwapGroupAPI::queryMaxSwapGroups(HDC hDC, GLuint *maxGroups,
                                        GLuint *maxBarriers) const
{
    static const char *fnName = "wglQueryMaxSwapGroupsNV";

    beforeCommand(fnName, _api.wglQueryMaxSwapGroups);
    BOOL result = _api.wglQueryMaxSwapGroups(hDC, maxGroups, maxBarriers);
    afterCommand(fnName);

    return result;
}

// Calls wglQuerySwapGroupNV().
BOOL NVSwapGroupAPI::querySwapGroup(HDC hDC, GLuint *group, GLuint *barrier) const
{
    static const char *fnName = "wglQuerySwapGroupNV";

    beforeCommand(fnName, _api.wglQuerySwapGroup);
    BOOL result = _api.wglQuerySwapGroup(hDC, group, barrier);
    afterCommand(fnName);

    return result;
}

// Calls wglResetFrameCountNV().
BOOL NVSwapGroupAPI::resetFrameCount(HDC hDC) const
{
    static const char *fnName = "wglResetFrameCountNV";

    beforeCommand(fnName, _api.wglResetFrameCount);
    BOOL result = _api.wglResetFrameCount(hDC);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVVertexArrayRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_vertex_array_range extension.
NVVertexArrayRangeAPI::NVVertexArrayRangeAPI() :
    BaseExtension("WGL_NV_vertex_array_range")
{
}

// Grant read-only access to the underlying function pointers.
const NVVertexArrayRange &NVVertexArrayRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_vertex_array_range entry points.
void NVVertexArrayRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglAllocateMemoryNV().
void *NVVertexArrayRangeAPI::allocateMemory(GLsizei size, GLfloat readfreq,
                                            GLfloat writefreq, GLfloat priority) const
{
    static const char *fnName = "wglAllocateMemoryNV";

    beforeCommand(fnName, _api.wglAllocateMemory);
    void *result = _api.wglAllocateMemory(size, readfreq, writefreq, priority);
    afterCommand(fnName);

    return result;
}

// Calls wglFreeMemoryNV().
void NVVertexArrayRangeAPI::freeMemory(void *pointer) const
{
    static const char *fnName = "wglFreeMemoryNV";

    beforeCommand(fnName, _api.wglFreeMemory);
    _api.wglFreeMemory(pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCaptureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_video_capture extension.
NVVideoCaptureAPI::NVVideoCaptureAPI() :
    BaseExtension("WGL_NV_video_capture")
{
}

// Grant read-only access to the underlying function pointers.
const NVVideoCapture &NVVideoCaptureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_video_capture entry points.
void NVVideoCaptureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindVideoCaptureDeviceNV().
BOOL NVVideoCaptureAPI::bindVideoCaptureDevice(UINT uVideoSlot,
                                               HVIDEOINPUTDEVICENV hDevice) const
{
    static const char *fnName = "wglBindVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.wglBindVideoCaptureDevice);
    BOOL result = _api.wglBindVideoCaptureDevice(uVideoSlot, hDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglEnumerateVideoCaptureDevicesNV().
UINT NVVideoCaptureAPI::enumerateVideoCaptureDevices(HDC hDc,
                                                     HVIDEOINPUTDEVICENV *phDeviceList) const
{
    static const char *fnName = "wglEnumerateVideoCaptureDevicesNV";

    beforeCommand(fnName, _api.wglEnumerateVideoCaptureDevices);
    UINT result = _api.wglEnumerateVideoCaptureDevices(hDc, phDeviceList);
    afterCommand(fnName);

    return result;
}

// Calls wglLockVideoCaptureDeviceNV().
BOOL NVVideoCaptureAPI::lockVideoCaptureDevice(HDC hDc,
                                               HVIDEOINPUTDEVICENV hDevice) const
{
    static const char *fnName = "wglLockVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.wglLockVideoCaptureDevice);
    BOOL result = _api.wglLockVideoCaptureDevice(hDc, hDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryVideoCaptureDeviceNV().
BOOL NVVideoCaptureAPI::queryVideoCaptureDevice(HDC hDc,
                                                HVIDEOINPUTDEVICENV hDevice,
                                                int iAttribute, int *piValue) const
{
    static const char *fnName = "wglQueryVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.wglQueryVideoCaptureDevice);
    BOOL result = _api.wglQueryVideoCaptureDevice(hDc, hDevice, iAttribute,
                                                  piValue);
    afterCommand(fnName);

    return result;
}

// Calls wglReleaseVideoCaptureDeviceNV().
BOOL NVVideoCaptureAPI::releaseVideoCaptureDevice(HDC hDc,
                                                  HVIDEOINPUTDEVICENV hDevice) const
{
    static const char *fnName = "wglReleaseVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.wglReleaseVideoCaptureDevice);
    BOOL result = _api.wglReleaseVideoCaptureDevice(hDc, hDevice);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoOutputAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_NV_video_output extension.
NVVideoOutputAPI::NVVideoOutputAPI() :
    BaseExtension("WGL_NV_video_output")
{
}

// Grant read-only access to the underlying function pointers.
const NVVideoOutput &NVVideoOutputAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_NV_video_output entry points.
void NVVideoOutputAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindVideoImageNV().
BOOL NVVideoOutputAPI::bindVideoImage(HPVIDEODEV hVideoDevice,
                                      HPBUFFERARB hPbuffer, int iVideoBuffer) const
{
    static const char *fnName = "wglBindVideoImageNV";

    beforeCommand(fnName, _api.wglBindVideoImage);
    BOOL result = _api.wglBindVideoImage(hVideoDevice, hPbuffer, iVideoBuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglGetVideoDeviceNV().
BOOL NVVideoOutputAPI::getVideoDevice(HDC hDC, int numDevices,
                                      HPVIDEODEV *hVideoDevice) const
{
    static const char *fnName = "wglGetVideoDeviceNV";

    beforeCommand(fnName, _api.wglGetVideoDevice);
    BOOL result = _api.wglGetVideoDevice(hDC, numDevices, hVideoDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglGetVideoInfoNV().
BOOL NVVideoOutputAPI::getVideoInfo(HPVIDEODEV hpVideoDevice,
                                    unsigned long *pulCounterOutputPbuffer,
                                    unsigned long *pulCounterOutputVideo) const
{
    static const char *fnName = "wglGetVideoInfoNV";

    beforeCommand(fnName, _api.wglGetVideoInfo);
    BOOL result = _api.wglGetVideoInfo(hpVideoDevice, pulCounterOutputPbuffer,
                                       pulCounterOutputVideo);
    afterCommand(fnName);

    return result;
}

// Calls wglReleaseVideoDeviceNV().
BOOL NVVideoOutputAPI::releaseVideoDevice(HPVIDEODEV hVideoDevice) const
{
    static const char *fnName = "wglReleaseVideoDeviceNV";

    beforeCommand(fnName, _api.wglReleaseVideoDevice);
    BOOL result = _api.wglReleaseVideoDevice(hVideoDevice);
    afterCommand(fnName);

    return result;
}

// Calls wglReleaseVideoImageNV().
BOOL NVVideoOutputAPI::releaseVideoImage(HPBUFFERARB hPbuffer, int iVideoBuffer) const
{
    static const char *fnName = "wglReleaseVideoImageNV";

    beforeCommand(fnName, _api.wglReleaseVideoImage);
    BOOL result = _api.wglReleaseVideoImage(hPbuffer, iVideoBuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglSendPbufferToVideoNV().
BOOL NVVideoOutputAPI::sendPbufferToVideo(HPBUFFERARB hPbuffer, int iBufferType,
                                          unsigned long *pulCounterPbuffer,
                                          BOOL bBlock) const
{
    static const char *fnName = "wglSendPbufferToVideoNV";

    beforeCommand(fnName, _api.wglSendPbufferToVideo);
    BOOL result = _api.wglSendPbufferToVideo(hPbuffer, iBufferType,
                                             pulCounterPbuffer, bBlock);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// NVCopyBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_copy_buffer extension.
NVCopyBufferAPI::NVCopyBufferAPI() :
    BaseExtension("GLX_NV_copy_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const NVCopyBuffer &NVCopyBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_copy_buffer entry points.
void NVCopyBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCopyBufferSubDataNV().
void NVCopyBufferAPI::xCopyBufferSubData(Display *dpy, GLXContext readCtx,
                                         GLXContext writeCtx, GLenum readTarget,
                                         GLenum writeTarget, GLintptr readOffset,
                                         GLintptr writeOffset, GLsizeiptr size) const
{
    static const char *fnName = "glXCopyBufferSubDataNV";

    beforeCommand(fnName, _api.glXCopyBufferSubData);
    _api.glXCopyBufferSubData(dpy, readCtx, writeCtx, readTarget, writeTarget,
                              readOffset, writeOffset, size);
    afterCommand(fnName);
}

// Calls glXNamedCopyBufferSubDataNV().
void NVCopyBufferAPI::xNamedCopyBufferSubData(Display *dpy, GLXContext readCtx,
                                              GLXContext writeCtx,
                                              GLuint readBuffer,
                                              GLuint writeBuffer,
                                              GLintptr readOffset,
                                              GLintptr writeOffset,
                                              GLsizeiptr size) const
{
    static const char *fnName = "glXNamedCopyBufferSubDataNV";

    beforeCommand(fnName, _api.glXNamedCopyBufferSubData);
    _api.glXNamedCopyBufferSubData(dpy, readCtx, writeCtx, readBuffer,
                                   writeBuffer, readOffset, writeOffset, size);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVCopyImageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_copy_image extension.
NVCopyImageAPI::NVCopyImageAPI() :
    BaseExtension("GLX_NV_copy_image")
{
}

// Grant read-only access to the underlying function pointers.
const NVCopyImage &NVCopyImageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_copy_image entry points.
void NVCopyImageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCopyImageSubDataNV().
void NVCopyImageAPI::xCopyImageSubData(Display *dpy, GLXContext srcCtx,
                                       GLuint srcName, GLenum srcTarget,
                                       GLint srcLevel, GLint srcX, GLint srcY,
                                       GLint srcZ, GLXContext dstCtx,
                                       GLuint dstName, GLenum dstTarget,
                                       GLint dstLevel, GLint dstX, GLint dstY,
                                       GLint dstZ, GLsizei width, GLsizei height,
                                       GLsizei depth) const
{
    static const char *fnName = "glXCopyImageSubDataNV";

    beforeCommand(fnName, _api.glXCopyImageSubData);
    _api.glXCopyImageSubData(dpy, srcCtx, srcName, srcTarget, srcLevel, srcX,
                             srcY, srcZ, dstCtx, dstName, dstTarget, dstLevel,
                             dstX, dstY, dstZ, width, height, depth);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVDelayBeforeSwapAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_delay_before_swap extension.
NVDelayBeforeSwapAPI::NVDelayBeforeSwapAPI() :
    BaseExtension("GLX_NV_delay_before_swap")
{
}

// Grant read-only access to the underlying function pointers.
const NVDelayBeforeSwap &NVDelayBeforeSwapAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_delay_before_swap entry points.
void NVDelayBeforeSwapAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXDelayBeforeSwapNV().
Bool NVDelayBeforeSwapAPI::xDelayBeforeSwap(Display *dpy, GLXDrawable drawable,
                                            GLfloat seconds) const
{
    static const char *fnName = "glXDelayBeforeSwapNV";

    beforeCommand(fnName, _api.glXDelayBeforeSwap);
    Bool result = _api.glXDelayBeforeSwap(dpy, drawable, seconds);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVPresentVideoAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_present_video extension.
NVPresentVideoAPI::NVPresentVideoAPI() :
    BaseExtension("GLX_NV_present_video")
{
}

// Grant read-only access to the underlying function pointers.
const NVPresentVideo &NVPresentVideoAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_present_video entry points.
void NVPresentVideoAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindVideoDeviceNV().
int NVPresentVideoAPI::xBindVideoDevice(Display *dpy, unsigned int video_slot,
                                        unsigned int video_device,
                                        const int *attrib_list) const
{
    static const char *fnName = "glXBindVideoDeviceNV";

    beforeCommand(fnName, _api.glXBindVideoDevice);
    int result = _api.glXBindVideoDevice(dpy, video_slot, video_device,
                                         attrib_list);
    afterCommand(fnName);

    return result;
}

// Calls glXEnumerateVideoDevicesNV().
unsigned int *NVPresentVideoAPI::xEnumerateVideoDevices(Display *dpy, int screen,
                                                        int *nelements) const
{
    static const char *fnName = "glXEnumerateVideoDevicesNV";

    beforeCommand(fnName, _api.glXEnumerateVideoDevices);
    unsigned int *result = _api.glXEnumerateVideoDevices(dpy, screen, nelements);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVSwapGroupAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_swap_group extension.
NVSwapGroupAPI::NVSwapGroupAPI() :
    BaseExtension("GLX_NV_swap_group")
{
}

// Grant read-only access to the underlying function pointers.
const NVSwapGroup &NVSwapGroupAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_swap_group entry points.
void NVSwapGroupAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindSwapBarrierNV().
Bool NVSwapGroupAPI::xBindSwapBarrier(Display *dpy, GLuint group, GLuint barrier) const
{
    static const char *fnName = "glXBindSwapBarrierNV";

    beforeCommand(fnName, _api.glXBindSwapBarrier);
    Bool result = _api.glXBindSwapBarrier(dpy, group, barrier);
    afterCommand(fnName);

    return result;
}

// Calls glXJoinSwapGroupNV().
Bool NVSwapGroupAPI::xJoinSwapGroup(Display *dpy, GLXDrawable drawable,
                                    GLuint group) const
{
    static const char *fnName = "glXJoinSwapGroupNV";

    beforeCommand(fnName, _api.glXJoinSwapGroup);
    Bool result = _api.glXJoinSwapGroup(dpy, drawable, group);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryFrameCountNV().
Bool NVSwapGroupAPI::xQueryFrameCount(Display *dpy, int screen, GLuint *count) const
{
    static const char *fnName = "glXQueryFrameCountNV";

    beforeCommand(fnName, _api.glXQueryFrameCount);
    Bool result = _api.glXQueryFrameCount(dpy, screen, count);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryMaxSwapGroupsNV().
Bool NVSwapGroupAPI::xQueryMaxSwapGroups(Display *dpy, int screen,
                                         GLuint *maxGroups, GLuint *maxBarriers) const
{
    static const char *fnName = "glXQueryMaxSwapGroupsNV";

    beforeCommand(fnName, _api.glXQueryMaxSwapGroups);
    Bool result = _api.glXQueryMaxSwapGroups(dpy, screen, maxGroups, maxBarriers);
    afterCommand(fnName);

    return result;
}

// Calls glXQuerySwapGroupNV().
Bool NVSwapGroupAPI::xQuerySwapGroup(Display *dpy, GLXDrawable drawable,
                                     GLuint *group, GLuint *barrier) const
{
    static const char *fnName = "glXQuerySwapGroupNV";

    beforeCommand(fnName, _api.glXQuerySwapGroup);
    Bool result = _api.glXQuerySwapGroup(dpy, drawable, group, barrier);
    afterCommand(fnName);

    return result;
}

// Calls glXResetFrameCountNV().
Bool NVSwapGroupAPI::xResetFrameCount(Display *dpy, int screen) const
{
    static const char *fnName = "glXResetFrameCountNV";

    beforeCommand(fnName, _api.glXResetFrameCount);
    Bool result = _api.glXResetFrameCount(dpy, screen);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoCaptureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_video_capture extension.
NVVideoCaptureAPI::NVVideoCaptureAPI() :
    BaseExtension("GLX_NV_video_capture")
{
}

// Grant read-only access to the underlying function pointers.
const NVVideoCapture &NVVideoCaptureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_video_capture entry points.
void NVVideoCaptureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindVideoCaptureDeviceNV().
int NVVideoCaptureAPI::xBindVideoCaptureDevice(Display *dpy,
                                               unsigned int video_capture_slot,
                                               GLXVideoCaptureDeviceNV device) const
{
    static const char *fnName = "glXBindVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.glXBindVideoCaptureDevice);
    int result = _api.glXBindVideoCaptureDevice(dpy, video_capture_slot, device);
    afterCommand(fnName);

    return result;
}

// Calls glXEnumerateVideoCaptureDevicesNV().
GLXVideoCaptureDeviceNV *NVVideoCaptureAPI::xEnumerateVideoCaptureDevices(Display *dpy,
                                                                          int screen,
                                                                          int *nelements) const
{
    static const char *fnName = "glXEnumerateVideoCaptureDevicesNV";

    beforeCommand(fnName, _api.glXEnumerateVideoCaptureDevices);
    GLXVideoCaptureDeviceNV *result = _api.glXEnumerateVideoCaptureDevices(dpy,
                                                                           screen,
                                                                           nelements);
    afterCommand(fnName);

    return result;
}

// Calls glXLockVideoCaptureDeviceNV().
void NVVideoCaptureAPI::xLockVideoCaptureDevice(Display *dpy,
                                                GLXVideoCaptureDeviceNV device) const
{
    static const char *fnName = "glXLockVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.glXLockVideoCaptureDevice);
    _api.glXLockVideoCaptureDevice(dpy, device);
    afterCommand(fnName);
}

// Calls glXQueryVideoCaptureDeviceNV().
int NVVideoCaptureAPI::xQueryVideoCaptureDevice(Display *dpy,
                                                GLXVideoCaptureDeviceNV device,
                                                int attribute, int *value) const
{
    static const char *fnName = "glXQueryVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.glXQueryVideoCaptureDevice);
    int result = _api.glXQueryVideoCaptureDevice(dpy, device, attribute, value);
    afterCommand(fnName);

    return result;
}

// Calls glXReleaseVideoCaptureDeviceNV().
void NVVideoCaptureAPI::xReleaseVideoCaptureDevice(Display *dpy,
                                                   GLXVideoCaptureDeviceNV device) const
{
    static const char *fnName = "glXReleaseVideoCaptureDeviceNV";

    beforeCommand(fnName, _api.glXReleaseVideoCaptureDevice);
    _api.glXReleaseVideoCaptureDevice(dpy, device);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// NVVideoOutAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_NV_video_out extension.
NVVideoOutAPI::NVVideoOutAPI() :
    BaseExtension("GLX_NV_video_out")
{
}

// Grant read-only access to the underlying function pointers.
const NVVideoOut &NVVideoOutAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_NV_video_out entry points.
void NVVideoOutAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindVideoImageNV().
int NVVideoOutAPI::xBindVideoImage(Display *dpy, GLXVideoDeviceNV VideoDevice,
                                   GLXPbuffer pbuf, int iVideoBuffer) const
{
    static const char *fnName = "glXBindVideoImageNV";

    beforeCommand(fnName, _api.glXBindVideoImage);
    int result = _api.glXBindVideoImage(dpy, VideoDevice, pbuf, iVideoBuffer);
    afterCommand(fnName);

    return result;
}

// Calls glXGetVideoDeviceNV().
int NVVideoOutAPI::xGetVideoDevice(Display *dpy, int screen, int numVideoDevices,
                                   GLXVideoDeviceNV *pVideoDevice) const
{
    static const char *fnName = "glXGetVideoDeviceNV";

    beforeCommand(fnName, _api.glXGetVideoDevice);
    int result = _api.glXGetVideoDevice(dpy, screen, numVideoDevices,
                                        pVideoDevice);
    afterCommand(fnName);

    return result;
}

// Calls glXGetVideoInfoNV().
int NVVideoOutAPI::xGetVideoInfo(Display *dpy, int screen,
                                 GLXVideoDeviceNV VideoDevice,
                                 unsigned long *pulCounterOutputPbuffer,
                                 unsigned long *pulCounterOutputVideo) const
{
    static const char *fnName = "glXGetVideoInfoNV";

    beforeCommand(fnName, _api.glXGetVideoInfo);
    int result = _api.glXGetVideoInfo(dpy, screen, VideoDevice,
                                      pulCounterOutputPbuffer,
                                      pulCounterOutputVideo);
    afterCommand(fnName);

    return result;
}

// Calls glXReleaseVideoDeviceNV().
int NVVideoOutAPI::xReleaseVideoDevice(Display *dpy, int screen,
                                       GLXVideoDeviceNV VideoDevice) const
{
    static const char *fnName = "glXReleaseVideoDeviceNV";

    beforeCommand(fnName, _api.glXReleaseVideoDevice);
    int result = _api.glXReleaseVideoDevice(dpy, screen, VideoDevice);
    afterCommand(fnName);

    return result;
}

// Calls glXReleaseVideoImageNV().
int NVVideoOutAPI::xReleaseVideoImage(Display *dpy, GLXPbuffer pbuf) const
{
    static const char *fnName = "glXReleaseVideoImageNV";

    beforeCommand(fnName, _api.glXReleaseVideoImage);
    int result = _api.glXReleaseVideoImage(dpy, pbuf);
    afterCommand(fnName);

    return result;
}

// Calls glXSendPbufferToVideoNV().
int NVVideoOutAPI::xSendPbufferToVideo(Display *dpy, GLXPbuffer pbuf,
                                       int iBufferType,
                                       unsigned long *pulCounterPbuffer,
                                       GLboolean bBlock) const
{
    static const char *fnName = "glXSendPbufferToVideoNV";

    beforeCommand(fnName, _api.glXSendPbufferToVideo);
    int result = _api.glXSendPbufferToVideo(dpy, pbuf, iBufferType,
                                            pulCounterPbuffer, bBlock);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

