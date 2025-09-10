//! @file Ag/ObjectGL/Extensions/AMD.hpp
//! @brief The declaration of AMD-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_AMD_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_AMD_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#ifdef _WIN32
#include "../WGL_API.hpp"
#endif // ifdef _WIN32

#ifdef _USES_GLX
#include "../GLX_Types.hpp"
#endif // ifdef _USES_GLX

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_AMD_debug_output extension API specification.
struct AMDDebugOutput {
    // Public Members
    void (APIENTRY *glDebugMessageCallback)(GLDEBUGPROCAMD callback,
                                            void *userParam);
    void (APIENTRY *glDebugMessageEnable)(GLenum category, GLenum severity,
                                          GLsizei count, const GLuint *ids,
                                          GLboolean enabled);
    void (APIENTRY *glDebugMessageInsert)(GLenum category, GLenum severity,
                                          GLuint id, GLsizei length,
                                          const GLchar *buf);
    GLuint(APIENTRY *glGetDebugMessageLog)(GLuint count, GLsizei bufSize,
                                           GLenum *categories,
                                           GLuint *severities, GLuint *ids,
                                           GLsizei *lengths, GLchar *message);

   // Construction
    AMDDebugOutput();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDDebugOutput

// GL_AMD_draw_buffers_blend extension API specification.
struct AMDDrawBuffersBlend {
    // Public Members
    void (APIENTRY *glBlendEquationIndexed)(GLuint buf, GLenum mode);
    void (APIENTRY *glBlendEquationSeparateIndexed)(GLuint buf, GLenum modeRGB,
                                                    GLenum modeAlpha);
    void (APIENTRY *glBlendFuncIndexed)(GLuint buf, GLenum src, GLenum dst);
    void (APIENTRY *glBlendFuncSeparateIndexed)(GLuint buf, GLenum srcRGB,
                                                GLenum dstRGB, GLenum srcAlpha,
                                                GLenum dstAlpha);

    // Construction
    AMDDrawBuffersBlend();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDDrawBuffersBlend

// GL_AMD_framebuffer_multisample_advanced extension API specification.
struct AMDFramebufferMultisampleAdvanced {
    // Public Members
    void (APIENTRY *glNamedRenderbufferStorageMultisampleAdvanced)(GLuint renderbuffer,
                                                                   GLsizei samples,
                                                                   GLsizei storageSamples,
                                                                   GLenum internalformat,
                                                                   GLsizei width,
                                                                   GLsizei height);
    void (APIENTRY *glRenderbufferStorageMultisampleAdvanced)(GLenum target,
                                                              GLsizei samples,
                                                              GLsizei storageSamples,
                                                              GLenum internalformat,
                                                              GLsizei width,
                                                              GLsizei height);

    // Construction
    AMDFramebufferMultisampleAdvanced();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDFramebufferMultisampleAdvanced

// GL_AMD_framebuffer_sample_positions extension API specification.
struct AMDFramebufferSamplePositions {
    // Public Members
    void (APIENTRY *glFramebufferSamplePositionsfv)(GLenum target,
                                                    GLuint numsamples,
                                                    GLuint pixelindex,
                                                    const GLfloat *values);
    void (APIENTRY *glGetFramebufferParameterfv)(GLenum target, GLenum pname,
                                                 GLuint numsamples,
                                                 GLuint pixelindex, GLsizei size,
                                                 GLfloat *values);
    void (APIENTRY *glGetNamedFramebufferParameterfv)(GLuint framebuffer,
                                                      GLenum pname,
                                                      GLuint numsamples,
                                                      GLuint pixelindex,
                                                      GLsizei size,
                                                      GLfloat *values);
    void (APIENTRY *glNamedFramebufferSamplePositionsfv)(GLuint framebuffer,
                                                         GLuint numsamples,
                                                         GLuint pixelindex,
                                                         const GLfloat *values);

    // Construction
    AMDFramebufferSamplePositions();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDFramebufferSamplePositions

// GL_AMD_gpu_shader_int64 extension API specification.
struct AMDGPUShaderInt64 {
    // Public Members
    void (APIENTRY *glGetUniformi64v)(GLuint program, GLint location,
                                      GLint64EXT *params);
    void (APIENTRY *glGetUniformui64v)(GLuint program, GLint location,
                                       GLuint64EXT *params);
    void (APIENTRY *glProgramUniform1i64)(GLuint program, GLint location,
                                          GLint64EXT x);
    void (APIENTRY *glProgramUniform1i64v)(GLuint program, GLint location,
                                           GLsizei count,
                                           const GLint64EXT *value);
    void (APIENTRY *glProgramUniform1ui64)(GLuint program, GLint location,
                                           GLuint64EXT x);
    void (APIENTRY *glProgramUniform1ui64v)(GLuint program, GLint location,
                                            GLsizei count,
                                            const GLuint64EXT *value);
    void (APIENTRY *glProgramUniform2i64)(GLuint program, GLint location,
                                          GLint64EXT x, GLint64EXT y);
    void (APIENTRY *glProgramUniform2i64v)(GLuint program, GLint location,
                                           GLsizei count,
                                           const GLint64EXT *value);
    void (APIENTRY *glProgramUniform2ui64)(GLuint program, GLint location,
                                           GLuint64EXT x, GLuint64EXT y);
    void (APIENTRY *glProgramUniform2ui64v)(GLuint program, GLint location,
                                            GLsizei count,
                                            const GLuint64EXT *value);
    void (APIENTRY *glProgramUniform3i64)(GLuint program, GLint location,
                                          GLint64EXT x, GLint64EXT y,
                                          GLint64EXT z);
    void (APIENTRY *glProgramUniform3i64v)(GLuint program, GLint location,
                                           GLsizei count,
                                           const GLint64EXT *value);
    void (APIENTRY *glProgramUniform3ui64)(GLuint program, GLint location,
                                           GLuint64EXT x, GLuint64EXT y,
                                           GLuint64EXT z);
    void (APIENTRY *glProgramUniform3ui64v)(GLuint program, GLint location,
                                            GLsizei count,
                                            const GLuint64EXT *value);
    void (APIENTRY *glProgramUniform4i64)(GLuint program, GLint location,
                                          GLint64EXT x, GLint64EXT y,
                                          GLint64EXT z, GLint64EXT w);
    void (APIENTRY *glProgramUniform4i64v)(GLuint program, GLint location,
                                           GLsizei count,
                                           const GLint64EXT *value);
    void (APIENTRY *glProgramUniform4ui64)(GLuint program, GLint location,
                                           GLuint64EXT x, GLuint64EXT y,
                                           GLuint64EXT z, GLuint64EXT w);
    void (APIENTRY *glProgramUniform4ui64v)(GLuint program, GLint location,
                                            GLsizei count,
                                            const GLuint64EXT *value);
    void (APIENTRY *glUniform1i64)(GLint location, GLint64EXT x);
    void (APIENTRY *glUniform1i64v)(GLint location, GLsizei count,
                                    const GLint64EXT *value);
    void (APIENTRY *glUniform1ui64)(GLint location, GLuint64EXT x);
    void (APIENTRY *glUniform1ui64v)(GLint location, GLsizei count,
                                     const GLuint64EXT *value);
    void (APIENTRY *glUniform2i64)(GLint location, GLint64EXT x, GLint64EXT y);
    void (APIENTRY *glUniform2i64v)(GLint location, GLsizei count,
                                    const GLint64EXT *value);
    void (APIENTRY *glUniform2ui64)(GLint location, GLuint64EXT x, GLuint64EXT y);
    void (APIENTRY *glUniform2ui64v)(GLint location, GLsizei count,
                                     const GLuint64EXT *value);
    void (APIENTRY *glUniform3i64)(GLint location, GLint64EXT x, GLint64EXT y,
                                   GLint64EXT z);
    void (APIENTRY *glUniform3i64v)(GLint location, GLsizei count,
                                    const GLint64EXT *value);
    void (APIENTRY *glUniform3ui64)(GLint location, GLuint64EXT x, GLuint64EXT y,
                                    GLuint64EXT z);
    void (APIENTRY *glUniform3ui64v)(GLint location, GLsizei count,
                                     const GLuint64EXT *value);
    void (APIENTRY *glUniform4i64)(GLint location, GLint64EXT x, GLint64EXT y,
                                   GLint64EXT z, GLint64EXT w);
    void (APIENTRY *glUniform4i64v)(GLint location, GLsizei count,
                                    const GLint64EXT *value);
    void (APIENTRY *glUniform4ui64)(GLint location, GLuint64EXT x, GLuint64EXT y,
                                    GLuint64EXT z, GLuint64EXT w);
    void (APIENTRY *glUniform4ui64v)(GLint location, GLsizei count,
                                     const GLuint64EXT *value);

    // Construction
    AMDGPUShaderInt64();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDGPUShaderInt64

// GL_AMD_interleaved_elements extension API specification.
struct AMDInterleavedElements {
    // Public Members
    void (APIENTRY *glVertexAttribParameteri)(GLuint index, GLenum pname,
                                              GLint param);

    // Construction
    AMDInterleavedElements();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDInterleavedElements

// GL_AMD_multi_draw_indirect extension API specification.
struct AMDMultiDrawIndirect {
    // Public Members
    void (APIENTRY *glMultiDrawArraysIndirect)(GLenum mode, const void *indirect,
                                               GLsizei primcount, GLsizei stride);
    void (APIENTRY *glMultiDrawElementsIndirect)(GLenum mode, GLenum type,
                                                 const void *indirect,
                                                 GLsizei primcount,
                                                 GLsizei stride);

    // Construction
    AMDMultiDrawIndirect();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDMultiDrawIndirect

// GL_AMD_name_gen_delete extension API specification.
struct AMDNameGenDelete {
    // Public Members
    void (APIENTRY *glDeleteNames)(GLenum identifier, GLuint num,
                                   const GLuint *names);
    void (APIENTRY *glGenNames)(GLenum identifier, GLuint num, GLuint *names);
    GLboolean(APIENTRY *glIsName)(GLenum identifier, GLuint name);

    // Construction
    AMDNameGenDelete();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDNameGenDelete

// GL_AMD_occlusion_query_event extension API specification.
struct AMDOcclusionQueryEvent {
    // Public Members
    void (APIENTRY *glQueryObjectParameterui)(GLenum target, GLuint id,
                                              GLenum pname, GLuint param);

    // Construction
    AMDOcclusionQueryEvent();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDOcclusionQueryEvent

// GL_AMD_performance_monitor extension API specification.
struct AMDPerformanceMonitor {
    // Public Members
    void (APIENTRY *glBeginPerfMonitor)(GLuint monitor);
    void (APIENTRY *glDeletePerfMonitors)(GLsizei n, GLuint *monitors);
    void (APIENTRY *glEndPerfMonitor)(GLuint monitor);
    void (APIENTRY *glGenPerfMonitors)(GLsizei n, GLuint *monitors);
    void (APIENTRY *glGetPerfMonitorCounterData)(GLuint monitor, GLenum pname,
                                                 GLsizei dataSize, GLuint *data,
                                                 GLint *bytesWritten);
    void (APIENTRY *glGetPerfMonitorCounterInfo)(GLuint group, GLuint counter,
                                                 GLenum pname, void *data);
    void (APIENTRY *glGetPerfMonitorCounterString)(GLuint group, GLuint counter,
                                                   GLsizei bufSize,
                                                   GLsizei *length,
                                                   GLchar *counterString);
    void (APIENTRY *glGetPerfMonitorCounters)(GLuint group, GLint *numCounters,
                                              GLint *maxActiveCounters,
                                              GLsizei counterSize,
                                              GLuint *counters);
    void (APIENTRY *glGetPerfMonitorGroupString)(GLuint group, GLsizei bufSize,
                                                 GLsizei *length,
                                                 GLchar *groupString);
    void (APIENTRY *glGetPerfMonitorGroups)(GLint *numGroups, GLsizei groupsSize,
                                            GLuint *groups);
    void (APIENTRY *glSelectPerfMonitorCounters)(GLuint monitor,
                                                 GLboolean enable, GLuint group,
                                                 GLint numCounters,
                                                 GLuint *counterList);

    // Construction
    AMDPerformanceMonitor();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDPerformanceMonitor

// GL_AMD_sample_positions extension API specification.
struct AMDSamplePositions {
    // Public Members
    void (APIENTRY *glSetMultisamplefv)(GLenum pname, GLuint index,
                                        const GLfloat *val);

    // Construction
    AMDSamplePositions();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDSamplePositions

// GL_AMD_sparse_texture extension API specification.
struct AMDSparseTexture {
    // Public Members
    void (APIENTRY *glTexStorageSparse)(GLenum target, GLenum internalFormat,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth, GLsizei layers,
                                        GLbitfield flags);
    void (APIENTRY *glTextureStorageSparse)(GLuint texture, GLenum target,
                                            GLenum internalFormat, GLsizei width,
                                            GLsizei height, GLsizei depth,
                                            GLsizei layers, GLbitfield flags);

    // Construction
    AMDSparseTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDSparseTexture

// GL_AMD_stencil_operation_extended extension API specification.
struct AMDStencilOperationExtended {
    // Public Members
    void (APIENTRY *glStencilOpValue)(GLenum face, GLuint value);

    // Construction
    AMDStencilOperationExtended();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDStencilOperationExtended

// GL_AMD_vertex_shader_tessellator extension API specification.
struct AMDVertexShaderTessellator {
    // Public Members
    void (APIENTRY *glTessellationFactor)(GLfloat factor);
    void (APIENTRY *glTessellationMode)(GLenum mode);

    // Construction
    AMDVertexShaderTessellator();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDVertexShaderTessellator

} // namespace gl

#ifdef _WIN32
namespace wgl {

// WGL_AMD_gpu_association extension API specification.
struct AMDGPUAssociation {
    // Public Members
    VOID(APIENTRY *wglBlitContextFramebuffer)(HGLRC dstCtx, GLint srcX0,
                                              GLint srcY0, GLint srcX1,
                                              GLint srcY1, GLint dstX0,
                                              GLint dstY0, GLint dstX1,
                                              GLint dstY1, GLbitfield mask,
                                              GLenum filter);
    HGLRC(APIENTRY *wglCreateAssociatedContext)(UINT id);
    HGLRC(APIENTRY *wglCreateAssociatedContextAttribs)(UINT id,
                                                       HGLRC hShareContext,
                                                       const int *attribList);
    BOOL(APIENTRY *wglDeleteAssociatedContext)(HGLRC hglrc);
    UINT(APIENTRY *wglGetContextGPUID)(HGLRC hglrc);
    HGLRC(APIENTRY *wglGetCurrentAssociatedContext)();
    UINT(APIENTRY *wglGetGPUIDs)(UINT maxCount, UINT *ids);
    INT(APIENTRY *wglGetGPUInfo)(UINT id, INT property, GLenum dataType,
                                 UINT size, void *data);
    BOOL(APIENTRY *wglMakeAssociatedContextCurrent)(HGLRC hglrc);

    // Construction
    AMDGPUAssociation();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDGPUAssociation

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// GLX_AMD_gpu_association extension API specification.
struct AMDGPUAssociation {
    // Public Members
    void (APIENTRY *glXBlitContextFramebuffer)(GLXContext dstCtx, GLint srcX0,
                                               GLint srcY0, GLint srcX1,
                                               GLint srcY1, GLint dstX0,
                                               GLint dstY0, GLint dstX1,
                                               GLint dstY1, GLbitfield mask,
                                               GLenum filter);
    GLXContext (APIENTRY *glXCreateAssociatedContext)(unsigned int id,
                                                      GLXContext share_list);
    GLXContext (APIENTRY *glXCreateAssociatedContextAttribs)(unsigned int id,
                                                             GLXContext share_context,
                                                             const int *attribList);
    Bool (APIENTRY *glXDeleteAssociatedContext)(GLXContext ctx);
    unsigned int (APIENTRY *glXGetContextGPUID)(GLXContext ctx);
    GLXContext (APIENTRY *glXGetCurrentAssociatedContext)();
    unsigned int (APIENTRY *glXGetGPUIDs)(unsigned int maxCount,
                                          unsigned int *ids);
    int (APIENTRY *glXGetGPUInfo)(unsigned int id, int property, GLenum dataType,
                                  unsigned int size, void *data);
    Bool (APIENTRY *glXMakeAssociatedContextCurrent)(GLXContext ctx);

    // Construction
    AMDGPUAssociation();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct AMDGPUAssociation

} // namespace glx
#endif // ifdef _USES_GLX

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
