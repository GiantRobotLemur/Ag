//! @file Ag/ObjectGL/Extensions/AMDCommands.hpp
//! @brief The declaration of AMD-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_AMD_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_AMD_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "AMD.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_AMD_debug_output extension API.
class AMDDebugOutputAPI : public BaseExtension
{
public:
    // Construction
    AMDDebugOutputAPI();

    // Accessors
    const AMDDebugOutput &getRawAPI() const;

    // Operations
    void debugMessageCallback(GLDEBUGPROCAMD callback, void *userParam) const;
    void debugMessageEnable(GLenum category, DebugSeverity severity,
                            GLsizei count, const GLuint *ids, Boolean enabled) const;
    void debugMessageInsert(GLenum category, DebugSeverity severity, GLuint id,
                            GLsizei length, const GLchar *buf) const;
    GLuint getDebugMessageLog(GLuint count, GLsizei bufSize, GLenum *categories,
                              DebugSeverity *severities, GLuint *ids,
                              GLsizei *lengths, GLchar *message) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDDebugOutput _api;
};

// Manages the entry points for the GL_AMD_draw_buffers_blend extension API.
class AMDDrawBuffersBlendAPI : public BaseExtension
{
public:
    // Construction
    AMDDrawBuffersBlendAPI();

    // Accessors
    const AMDDrawBuffersBlend &getRawAPI() const;

    // Operations
    void blendEquationIndexed(GLuint buf, BlendEquationModeEXT mode) const;
    void blendEquationSeparateIndexed(GLuint buf, BlendEquationModeEXT modeRGB,
                                      BlendEquationModeEXT modeAlpha) const;
    void blendFuncIndexed(GLuint buf, GLenum src, GLenum dst) const;
    void blendFuncSeparateIndexed(GLuint buf, BlendingFactor srcRGB,
                                  BlendingFactor dstRGB, BlendingFactor srcAlpha,
                                  BlendingFactor dstAlpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDDrawBuffersBlend _api;
};

// Manages the entry points for the GL_AMD_framebuffer_multisample_advanced extension API.
class AMDFramebufferMultisampleAdvancedAPI : public BaseExtension
{
public:
    // Construction
    AMDFramebufferMultisampleAdvancedAPI();

    // Accessors
    const AMDFramebufferMultisampleAdvanced &getRawAPI() const;

    // Operations
    void namedRenderbufferStorageMultisampleAdvanced(RenderBufferName renderbuffer,
                                                     GLsizei samples,
                                                     GLsizei storageSamples,
                                                     InternalFormat internalformat,
                                                     GLsizei width,
                                                     GLsizei height) const;
    void renderbufferStorageMultisampleAdvanced(RenderBufferTarget target,
                                                GLsizei samples,
                                                GLsizei storageSamples,
                                                InternalFormat internalformat,
                                                GLsizei width, GLsizei height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDFramebufferMultisampleAdvanced _api;
};

// Manages the entry points for the GL_AMD_framebuffer_sample_positions extension API.
class AMDFramebufferSamplePositionsAPI : public BaseExtension
{
public:
    // Construction
    AMDFramebufferSamplePositionsAPI();

    // Accessors
    const AMDFramebufferSamplePositions &getRawAPI() const;

    // Operations
    void framebufferSamplePositionsFV(FrameBufferTarget target,
                                      GLuint numsamples, GLuint pixelindex,
                                      const GLfloat *values) const;
    void getFramebufferParameterFV(FrameBufferTarget target,
                                   FrameBufferAttachmentParameterName pname,
                                   GLuint numsamples, GLuint pixelindex,
                                   GLsizei size, GLfloat *values) const;
    void getNamedFramebufferParameterFV(FrameBufferName framebuffer,
                                        GLenum pname, GLuint numsamples,
                                        GLuint pixelindex, GLsizei size,
                                        GLfloat *values) const;
    void namedFramebufferSamplePositionsFV(FrameBufferName framebuffer,
                                           GLuint numsamples, GLuint pixelindex,
                                           const GLfloat *values) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDFramebufferSamplePositions _api;
};

// Manages the entry points for the GL_AMD_gpu_shader_int64 extension API.
class AMDGPUShaderInt64API : public BaseExtension
{
public:
    // Construction
    AMDGPUShaderInt64API();

    // Accessors
    const AMDGPUShaderInt64 &getRawAPI() const;

    // Operations
    void getUniformI64V(ProgramName program, GLint location, GLint64EXT *params) const;
    void getUniformUI64(ProgramName program, GLint location, GLuint64EXT *params) const;
    void programUniform1I64(ProgramName program, GLint location, GLint64EXT x) const;
    void programUniform1I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64EXT *value) const;
    void programUniform1UI64(ProgramName program, GLint location, GLuint64EXT x) const;
    void programUniform1UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64EXT *value) const;
    void programUniform2I64(ProgramName program, GLint location, GLint64EXT x,
                            GLint64EXT y) const;
    void programUniform2I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64EXT *value) const;
    void programUniform2UI64(ProgramName program, GLint location, GLuint64EXT x,
                             GLuint64EXT y) const;
    void programUniform2UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64EXT *value) const;
    void programUniform3I64(ProgramName program, GLint location, GLint64EXT x,
                            GLint64EXT y, GLint64EXT z) const;
    void programUniform3I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64EXT *value) const;
    void programUniform3UI64(ProgramName program, GLint location, GLuint64EXT x,
                             GLuint64EXT y, GLuint64EXT z) const;
    void programUniform3UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64EXT *value) const;
    void programUniform4I64(ProgramName program, GLint location, GLint64EXT x,
                            GLint64EXT y, GLint64EXT z, GLint64EXT w) const;
    void programUniform4I64V(ProgramName program, GLint location, GLsizei count,
                             const GLint64EXT *value) const;
    void programUniform4UI64(ProgramName program, GLint location, GLuint64EXT x,
                             GLuint64EXT y, GLuint64EXT z, GLuint64EXT w) const;
    void programUniform4UI64(ProgramName program, GLint location, GLsizei count,
                             const GLuint64EXT *value) const;
    void uniform1I64(GLint location, GLint64EXT x) const;
    void uniform1I64V(GLint location, GLsizei count, const GLint64EXT *value) const;
    void uniform1UI64(GLint location, GLuint64EXT x) const;
    void uniform1UI64(GLint location, GLsizei count, const GLuint64EXT *value) const;
    void uniform2I64(GLint location, GLint64EXT x, GLint64EXT y) const;
    void uniform2I64V(GLint location, GLsizei count, const GLint64EXT *value) const;
    void uniform2UI64(GLint location, GLuint64EXT x, GLuint64EXT y) const;
    void uniform2UI64(GLint location, GLsizei count, const GLuint64EXT *value) const;
    void uniform3I64(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z) const;
    void uniform3I64V(GLint location, GLsizei count, const GLint64EXT *value) const;
    void uniform3UI64(GLint location, GLuint64EXT x, GLuint64EXT y,
                      GLuint64EXT z) const;
    void uniform3UI64(GLint location, GLsizei count, const GLuint64EXT *value) const;
    void uniform4I64(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z,
                     GLint64EXT w) const;
    void uniform4I64V(GLint location, GLsizei count, const GLint64EXT *value) const;
    void uniform4UI64(GLint location, GLuint64EXT x, GLuint64EXT y,
                      GLuint64EXT z, GLuint64EXT w) const;
    void uniform4UI64(GLint location, GLsizei count, const GLuint64EXT *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDGPUShaderInt64 _api;
};

// Manages the entry points for the GL_AMD_interleaved_elements extension API.
class AMDInterleavedElementsAPI : public BaseExtension
{
public:
    // Construction
    AMDInterleavedElementsAPI();

    // Accessors
    const AMDInterleavedElements &getRawAPI() const;

    // Operations
    void vertexAttribParameterI(GLuint index, GLenum pname, GLint param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDInterleavedElements _api;
};

// Manages the entry points for the GL_AMD_multi_draw_indirect extension API.
class AMDMultiDrawIndirectAPI : public BaseExtension
{
public:
    // Construction
    AMDMultiDrawIndirectAPI();

    // Accessors
    const AMDMultiDrawIndirect &getRawAPI() const;

    // Operations
    void multiDrawArraysIndirect(PrimitiveType mode, const void *indirect,
                                 GLsizei primcount, GLsizei stride) const;
    void multiDrawElementsIndirect(PrimitiveType mode, DrawElementsType type,
                                   const void *indirect, GLsizei primcount,
                                   GLsizei stride) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDMultiDrawIndirect _api;
};

// Manages the entry points for the GL_AMD_name_gen_delete extension API.
class AMDNameGenDeleteAPI : public BaseExtension
{
public:
    // Construction
    AMDNameGenDeleteAPI();

    // Accessors
    const AMDNameGenDelete &getRawAPI() const;

    // Operations
    void deleteNames(GLenum identifier, GLuint num, const GLuint *names) const;
    void genNames(GLenum identifier, GLuint num, GLuint *names) const;
    Boolean isName(GLenum identifier, GLuint name) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDNameGenDelete _api;
};

// Manages the entry points for the GL_AMD_occlusion_query_event extension API.
class AMDOcclusionQueryEventAPI : public BaseExtension
{
public:
    // Construction
    AMDOcclusionQueryEventAPI();

    // Accessors
    const AMDOcclusionQueryEvent &getRawAPI() const;

    // Operations
    void queryObjectParameterUI(QueryTarget target, QueryName id, GLenum pname,
                                GLuint  /* OcclusionQueryEventMaskAMD */ param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDOcclusionQueryEvent _api;
};

// Manages the entry points for the GL_AMD_performance_monitor extension API.
class AMDPerformanceMonitorAPI : public BaseExtension
{
public:
    // Construction
    AMDPerformanceMonitorAPI();

    // Accessors
    const AMDPerformanceMonitor &getRawAPI() const;

    // Operations
    void beginPerfMonitor(GLuint monitor) const;
    void deletePerfMonitors(GLsizei n, GLuint *monitors) const;
    void endPerfMonitor(GLuint monitor) const;
    void genPerfMonitors(GLsizei n, GLuint *monitors) const;
    void getPerfMonitorCounterData(GLuint monitor, GLenum pname,
                                   GLsizei dataSize, GLuint *data,
                                   GLint *bytesWritten) const;
    void getPerfMonitorCounterInfo(GLuint group, GLuint counter, GLenum pname,
                                   void *data) const;
    void getPerfMonitorCounterString(GLuint group, GLuint counter,
                                     GLsizei bufSize, GLsizei *length,
                                     GLchar *counterString) const;
    void getPerfMonitorCounters(GLuint group, GLint *numCounters,
                                GLint *maxActiveCounters, GLsizei counterSize,
                                GLuint *counters) const;
    void getPerfMonitorGroupString(GLuint group, GLsizei bufSize,
                                   GLsizei *length, GLchar *groupString) const;
    void getPerfMonitorGroups(GLint *numGroups, GLsizei groupsSize,
                              GLuint *groups) const;
    void selectPerfMonitorCounters(GLuint monitor, Boolean enable, GLuint group,
                                   GLint numCounters, GLuint *counterList) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDPerformanceMonitor _api;
};

// Manages the entry points for the GL_AMD_sample_positions extension API.
class AMDSamplePositionsAPI : public BaseExtension
{
public:
    // Construction
    AMDSamplePositionsAPI();

    // Accessors
    const AMDSamplePositions &getRawAPI() const;

    // Operations
    void setMultisampleFV(GLenum pname, GLuint index, const GLfloat *val) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDSamplePositions _api;
};

// Manages the entry points for the GL_AMD_sparse_texture extension API.
class AMDSparseTextureAPI : public BaseExtension
{
public:
    // Construction
    AMDSparseTextureAPI();

    // Accessors
    const AMDSparseTexture &getRawAPI() const;

    // Operations
    void texStorageSparse(TextureTarget target,
                          SizedInternalFormat internalFormat, GLsizei width,
                          GLsizei height, GLsizei depth, GLsizei layers,
                          GLbitfield  /* TextureStorageMaskAMD */ flags) const;
    void textureStorageSparse(TextureName texture, GLenum target,
                              SizedInternalFormat internalFormat, GLsizei width,
                              GLsizei height, GLsizei depth, GLsizei layers,
                              GLbitfield  /* TextureStorageMaskAMD */ flags) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDSparseTexture _api;
};

// Manages the entry points for the GL_AMD_stencil_operation_extended extension API.
class AMDStencilOperationExtendedAPI : public BaseExtension
{
public:
    // Construction
    AMDStencilOperationExtendedAPI();

    // Accessors
    const AMDStencilOperationExtended &getRawAPI() const;

    // Operations
    void stencilOpValue(StencilFaceDirection face, GLuint value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDStencilOperationExtended _api;
};

// Manages the entry points for the GL_AMD_vertex_shader_tessellator extension API.
class AMDVertexShaderTessellatorAPI : public BaseExtension
{
public:
    // Construction
    AMDVertexShaderTessellatorAPI();

    // Accessors
    const AMDVertexShaderTessellator &getRawAPI() const;

    // Operations
    void tessellationFactor(GLfloat factor) const;
    void tessellationMode(GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDVertexShaderTessellator _api;
};

} // namespace gl


#ifdef _WIN32
namespace wgl {

// Manages the entry points for the WGL_AMD_gpu_association extension API.
class AMDGPUAssociationAPI : public gl::BaseExtension
{
public:
    // Construction
    AMDGPUAssociationAPI();

    // Accessors
    const AMDGPUAssociation &getRawAPI() const;

    // Operations
    VOID blitContextFramebuffer(HGLRC dstCtx, GLint srcX0, GLint srcY0,
                                GLint srcX1, GLint srcY1, GLint dstX0,
                                GLint dstY0, GLint dstX1, GLint dstY1,
                                GLbitfield mask, GLenum filter) const;
    HGLRC createAssociateDContext(UINT id) const;
    HGLRC createAssociateDContextAttribs(UINT id, HGLRC hShareContext,
                                         const int *attribList) const;
    BOOL deleteAssociateDContext(HGLRC hglrc) const;
    UINT getContextGpuid(HGLRC hglrc) const;
    HGLRC getCurrentAssociateDContext() const;
    UINT getGpuiDs(UINT maxCount, UINT *ids) const;
    INT getGPUInfo(UINT id, INT property, GLenum dataType, UINT size, void *data) const;
    BOOL makeAssociateDContextCurrent(HGLRC hglrc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDGPUAssociation _api;
};

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_AMD_gpu_association extension API.
class AMDGPUAssociationAPI : public gl::BaseExtension
{
public:
    // Construction
    AMDGPUAssociationAPI();

    // Accessors
    const AMDGPUAssociation &getRawAPI() const;

    // Operations
    void xBlitContextFramebuffer(GLXContext dstCtx, GLint srcX0, GLint srcY0,
                                 GLint srcX1, GLint srcY1, GLint dstX0,
                                 GLint dstY0, GLint dstX1, GLint dstY1,
                                 GLbitfield mask, GLenum filter) const;
    GLXContext xCreateAssociateDContext(unsigned int id, GLXContext share_list) const;
    GLXContext xCreateAssociateDContextAttribs(unsigned int id,
                                               GLXContext share_context,
                                               const int *attribList) const;
    Bool xDeleteAssociateDContext(GLXContext ctx) const;
    unsigned int xGetContextGpuid(GLXContext ctx) const;
    GLXContext xGetCurrentAssociateDContext() const;
    unsigned int xGetGpuiDs(unsigned int maxCount, unsigned int *ids) const;
    int xGetGPUInfo(unsigned int id, int property, GLenum dataType,
                    unsigned int size, void *data) const;
    Bool xMakeAssociateDContextCurrent(GLXContext ctx) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    AMDGPUAssociation _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
