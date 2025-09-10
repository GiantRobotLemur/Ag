//! @file Ag/ObjectGL/Extensions/ARB.hpp
//! @brief The declaration of Architecture Review Board (ARB) -specific
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

#ifndef __AG_OBJECT_GL_ARB_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_ARB_EXTENSIONS_HPP__

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
// GL_ARB_ES3_2_compatibility extension API specification.
struct ARBES32Compatibility {
    // Public Members
    void (APIENTRY *glPrimitiveBoundingBox)(GLfloat minX, GLfloat minY,
                                            GLfloat minZ, GLfloat minW,
                                            GLfloat maxX, GLfloat maxY,
                                            GLfloat maxZ, GLfloat maxW);

    // Construction
    ARBES32Compatibility();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBES32Compatibility

// GL_ARB_bindless_texture extension API specification.
struct ARBBindlessTexture {
    // Public Members
    GLuint64(APIENTRY *glGetImageHandle)(GLuint texture, GLint level,
                                         GLboolean layered, GLint layer,
                                         GLenum format);
    GLuint64(APIENTRY *glGetTextureHandle)(GLuint texture);
    GLuint64(APIENTRY *glGetTextureSamplerHandle)(GLuint texture,
                                                  GLuint sampler);
    void (APIENTRY *glGetVertexAttribLui64v)(GLuint index, GLenum pname,
                                             GLuint64EXT *params);
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
    void (APIENTRY *glVertexAttribL1ui64)(GLuint index, GLuint64EXT x);
    void (APIENTRY *glVertexAttribL1ui64v)(GLuint index, const GLuint64EXT *v);

    // Construction
    ARBBindlessTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBBindlessTexture

// GL_ARB_cl_event extension API specification.
struct ARBClEvent {
    // Public Members
    GLsync(APIENTRY *glCreateSyncFromCLevent)(struct _cl_context *context,
                                              struct _cl_event *event,
                                              GLbitfield flags);

   // Construction
    ARBClEvent();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBClEvent

// GL_ARB_color_buffer_float extension API specification.
struct ARBColorBufferFloat {
    // Public Members
    void (APIENTRY *glClampColor)(GLenum target, GLenum clamp);

    // Construction
    ARBColorBufferFloat();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBColorBufferFloat

// GL_ARB_compute_variable_group_size extension API specification.
struct ARBComputeVariableGroupSize {
    // Public Members
    void (APIENTRY *glDispatchComputeGroupSize)(GLuint num_groups_x,
                                                GLuint num_groups_y,
                                                GLuint num_groups_z,
                                                GLuint group_size_x,
                                                GLuint group_size_y,
                                                GLuint group_size_z);

    // Construction
    ARBComputeVariableGroupSize();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBComputeVariableGroupSize

// GL_ARB_debug_output extension API specification.
struct ARBDebugOutput {
    // Public Members
    void (APIENTRY *glDebugMessageCallback)(GLDEBUGPROCARB callback,
                                            const void *userParam);
    void (APIENTRY *glDebugMessageControl)(GLenum source, GLenum type,
                                           GLenum severity, GLsizei count,
                                           const GLuint *ids, GLboolean enabled);
    void (APIENTRY *glDebugMessageInsert)(GLenum source, GLenum type, GLuint id,
                                          GLenum severity, GLsizei length,
                                          const GLchar *buf);
    GLuint(APIENTRY *glGetDebugMessageLog)(GLuint count, GLsizei bufSize,
                                           GLenum *sources, GLenum *types,
                                           GLuint *ids, GLenum *severities,
                                           GLsizei *lengths, GLchar *messageLog);

   // Construction
    ARBDebugOutput();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBDebugOutput

// GL_ARB_draw_buffers extension API specification.
struct ARBDrawBuffers {
    // Public Members
    void (APIENTRY *glDrawBuffers)(GLsizei n, const GLenum *bufs);

    // Construction
    ARBDrawBuffers();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBDrawBuffers

// GL_ARB_draw_buffers_blend extension API specification.
struct ARBDrawBuffersBlend {
    // Public Members
    void (APIENTRY *glBlendEquationSeparatei)(GLuint buf, GLenum modeRGB,
                                              GLenum modeAlpha);
    void (APIENTRY *glBlendEquationi)(GLuint buf, GLenum mode);
    void (APIENTRY *glBlendFuncSeparatei)(GLuint buf, GLenum srcRGB,
                                          GLenum dstRGB, GLenum srcAlpha,
                                          GLenum dstAlpha);
    void (APIENTRY *glBlendFunci)(GLuint buf, GLenum src, GLenum dst);

    // Construction
    ARBDrawBuffersBlend();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBDrawBuffersBlend

// GL_ARB_draw_instanced extension API specification.
struct ARBDrawInstanced {
    // Public Members
    void (APIENTRY *glDrawArraysInstanced)(GLenum mode, GLint first,
                                           GLsizei count, GLsizei primcount);
    void (APIENTRY *glDrawElementsInstanced)(GLenum mode, GLsizei count,
                                             GLenum type, const void *indices,
                                             GLsizei primcount);

    // Construction
    ARBDrawInstanced();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBDrawInstanced

// GL_ARB_fragment_program extension API specification.
struct ARBFragmentProgram {
    // Public Members
    void (APIENTRY *glBindProgram)(GLenum target, GLuint program);
    void (APIENTRY *glDeletePrograms)(GLsizei n, const GLuint *programs);
    void (APIENTRY *glGenPrograms)(GLsizei n, GLuint *programs);
    void (APIENTRY *glGetProgramEnvParameterdv)(GLenum target, GLuint index,
                                                GLdouble *params);
    void (APIENTRY *glGetProgramEnvParameterfv)(GLenum target, GLuint index,
                                                GLfloat *params);
    void (APIENTRY *glGetProgramLocalParameterdv)(GLenum target, GLuint index,
                                                  GLdouble *params);
    void (APIENTRY *glGetProgramLocalParameterfv)(GLenum target, GLuint index,
                                                  GLfloat *params);
    void (APIENTRY *glGetProgramString)(GLenum target, GLenum pname,
                                        void *string);
    void (APIENTRY *glGetProgramiv)(GLenum target, GLenum pname, GLint *params);
    GLboolean(APIENTRY *glIsProgram)(GLuint program);
    void (APIENTRY *glProgramEnvParameter4d)(GLenum target, GLuint index,
                                             GLdouble x, GLdouble y, GLdouble z,
                                             GLdouble w);
    void (APIENTRY *glProgramEnvParameter4dv)(GLenum target, GLuint index,
                                              const GLdouble *params);
    void (APIENTRY *glProgramEnvParameter4f)(GLenum target, GLuint index,
                                             GLfloat x, GLfloat y, GLfloat z,
                                             GLfloat w);
    void (APIENTRY *glProgramEnvParameter4fv)(GLenum target, GLuint index,
                                              const GLfloat *params);
    void (APIENTRY *glProgramLocalParameter4d)(GLenum target, GLuint index,
                                               GLdouble x, GLdouble y,
                                               GLdouble z, GLdouble w);
    void (APIENTRY *glProgramLocalParameter4dv)(GLenum target, GLuint index,
                                                const GLdouble *params);
    void (APIENTRY *glProgramLocalParameter4f)(GLenum target, GLuint index,
                                               GLfloat x, GLfloat y, GLfloat z,
                                               GLfloat w);
    void (APIENTRY *glProgramLocalParameter4fv)(GLenum target, GLuint index,
                                                const GLfloat *params);
    void (APIENTRY *glProgramString)(GLenum target, GLenum format, GLsizei len,
                                     const void *string);

    // Construction
    ARBFragmentProgram();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBFragmentProgram

// GL_ARB_geometry_shader4 extension API specification.
struct ARBGeometrySHADER4 {
    // Public Members
    void (APIENTRY *glFramebufferTexture)(GLenum target, GLenum attachment,
                                          GLuint texture, GLint level);
    void (APIENTRY *glFramebufferTextureFace)(GLenum target, GLenum attachment,
                                              GLuint texture, GLint level,
                                              GLenum face);
    void (APIENTRY *glFramebufferTextureLayer)(GLenum target, GLenum attachment,
                                               GLuint texture, GLint level,
                                               GLint layer);
    void (APIENTRY *glProgramParameteri)(GLuint program, GLenum pname,
                                         GLint value);

    // Construction
    ARBGeometrySHADER4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBGeometrySHADER4

// GL_ARB_gl_spirv extension API specification.
struct ARBGlSpirv {
    // Public Members
    void (APIENTRY *glSpecializeShader)(GLuint shader, const GLchar *pEntryPoint,
                                        GLuint numSpecializationConstants,
                                        const GLuint *pConstantIndex,
                                        const GLuint *pConstantValue);

    // Construction
    ARBGlSpirv();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBGlSpirv

// GL_ARB_gpu_shader_int64 extension API specification.
struct ARBGPUShaderInt64 {
    // Public Members
    void (APIENTRY *glGetUniformi64v)(GLuint program, GLint location,
                                      GLint64 *params);
    void (APIENTRY *glGetUniformui64v)(GLuint program, GLint location,
                                       GLuint64 *params);
    void (APIENTRY *glGetnUniformi64v)(GLuint program, GLint location,
                                       GLsizei bufSize, GLint64 *params);
    void (APIENTRY *glGetnUniformui64v)(GLuint program, GLint location,
                                        GLsizei bufSize, GLuint64 *params);
    void (APIENTRY *glProgramUniform1i64)(GLuint program, GLint location,
                                          GLint64 x);
    void (APIENTRY *glProgramUniform1i64v)(GLuint program, GLint location,
                                           GLsizei count, const GLint64 *value);
    void (APIENTRY *glProgramUniform1ui64)(GLuint program, GLint location,
                                           GLuint64 x);
    void (APIENTRY *glProgramUniform1ui64v)(GLuint program, GLint location,
                                            GLsizei count, const GLuint64 *value);
    void (APIENTRY *glProgramUniform2i64)(GLuint program, GLint location,
                                          GLint64 x, GLint64 y);
    void (APIENTRY *glProgramUniform2i64v)(GLuint program, GLint location,
                                           GLsizei count, const GLint64 *value);
    void (APIENTRY *glProgramUniform2ui64)(GLuint program, GLint location,
                                           GLuint64 x, GLuint64 y);
    void (APIENTRY *glProgramUniform2ui64v)(GLuint program, GLint location,
                                            GLsizei count, const GLuint64 *value);
    void (APIENTRY *glProgramUniform3i64)(GLuint program, GLint location,
                                          GLint64 x, GLint64 y, GLint64 z);
    void (APIENTRY *glProgramUniform3i64v)(GLuint program, GLint location,
                                           GLsizei count, const GLint64 *value);
    void (APIENTRY *glProgramUniform3ui64)(GLuint program, GLint location,
                                           GLuint64 x, GLuint64 y, GLuint64 z);
    void (APIENTRY *glProgramUniform3ui64v)(GLuint program, GLint location,
                                            GLsizei count, const GLuint64 *value);
    void (APIENTRY *glProgramUniform4i64)(GLuint program, GLint location,
                                          GLint64 x, GLint64 y, GLint64 z,
                                          GLint64 w);
    void (APIENTRY *glProgramUniform4i64v)(GLuint program, GLint location,
                                           GLsizei count, const GLint64 *value);
    void (APIENTRY *glProgramUniform4ui64)(GLuint program, GLint location,
                                           GLuint64 x, GLuint64 y, GLuint64 z,
                                           GLuint64 w);
    void (APIENTRY *glProgramUniform4ui64v)(GLuint program, GLint location,
                                            GLsizei count, const GLuint64 *value);
    void (APIENTRY *glUniform1i64)(GLint location, GLint64 x);
    void (APIENTRY *glUniform1i64v)(GLint location, GLsizei count,
                                    const GLint64 *value);
    void (APIENTRY *glUniform1ui64)(GLint location, GLuint64 x);
    void (APIENTRY *glUniform1ui64v)(GLint location, GLsizei count,
                                     const GLuint64 *value);
    void (APIENTRY *glUniform2i64)(GLint location, GLint64 x, GLint64 y);
    void (APIENTRY *glUniform2i64v)(GLint location, GLsizei count,
                                    const GLint64 *value);
    void (APIENTRY *glUniform2ui64)(GLint location, GLuint64 x, GLuint64 y);
    void (APIENTRY *glUniform2ui64v)(GLint location, GLsizei count,
                                     const GLuint64 *value);
    void (APIENTRY *glUniform3i64)(GLint location, GLint64 x, GLint64 y,
                                   GLint64 z);
    void (APIENTRY *glUniform3i64v)(GLint location, GLsizei count,
                                    const GLint64 *value);
    void (APIENTRY *glUniform3ui64)(GLint location, GLuint64 x, GLuint64 y,
                                    GLuint64 z);
    void (APIENTRY *glUniform3ui64v)(GLint location, GLsizei count,
                                     const GLuint64 *value);
    void (APIENTRY *glUniform4i64)(GLint location, GLint64 x, GLint64 y,
                                   GLint64 z, GLint64 w);
    void (APIENTRY *glUniform4i64v)(GLint location, GLsizei count,
                                    const GLint64 *value);
    void (APIENTRY *glUniform4ui64)(GLint location, GLuint64 x, GLuint64 y,
                                    GLuint64 z, GLuint64 w);
    void (APIENTRY *glUniform4ui64v)(GLint location, GLsizei count,
                                     const GLuint64 *value);

    // Construction
    ARBGPUShaderInt64();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBGPUShaderInt64

// GL_ARB_indirect_parameters extension API specification.
struct ARBIndirectParameters {
    // Public Members
    void (APIENTRY *glMultiDrawArraysIndirectCount)(GLenum mode,
                                                    const void *indirect,
                                                    GLintptr drawcount,
                                                    GLsizei maxdrawcount,
                                                    GLsizei stride);
    void (APIENTRY *glMultiDrawElementsIndirectCount)(GLenum mode, GLenum type,
                                                      const void *indirect,
                                                      GLintptr drawcount,
                                                      GLsizei maxdrawcount,
                                                      GLsizei stride);

    // Construction
    ARBIndirectParameters();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBIndirectParameters

// GL_ARB_instanced_arrays extension API specification.
struct ARBInstancedArrays {
    // Public Members
    void (APIENTRY *glVertexAttribDivisor)(GLuint index, GLuint divisor);

    // Construction
    ARBInstancedArrays();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBInstancedArrays

// GL_ARB_matrix_palette extension API specification.
struct ARBMatrixPalette {
    // Public Members
    void (APIENTRY *glCurrentPaletteMatrix)(GLint index);
    void (APIENTRY *glMatrixIndexPointer)(GLint size, GLenum type,
                                          GLsizei stride, const void *pointer);
    void (APIENTRY *glMatrixIndexubv)(GLint size, const GLubyte *indices);
    void (APIENTRY *glMatrixIndexuiv)(GLint size, const GLuint *indices);
    void (APIENTRY *glMatrixIndexusv)(GLint size, const GLushort *indices);

    // Construction
    ARBMatrixPalette();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBMatrixPalette

// GL_ARB_multisample extension API specification.
struct ARBMultisample {
    // Public Members
    void (APIENTRY *glSampleCoverage)(GLfloat value, GLboolean invert);

    // Construction
    ARBMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBMultisample

// GL_ARB_multitexture extension API specification.
struct ARBMultitexture {
    // Public Members
    void (APIENTRY *glActiveTexture)(GLenum texture);
    void (APIENTRY *glClientActiveTexture)(GLenum texture);
    void (APIENTRY *glMultiTexCoord1d)(GLenum target, GLdouble s);
    void (APIENTRY *glMultiTexCoord1dv)(GLenum target, const GLdouble *v);
    void (APIENTRY *glMultiTexCoord1f)(GLenum target, GLfloat s);
    void (APIENTRY *glMultiTexCoord1fv)(GLenum target, const GLfloat *v);
    void (APIENTRY *glMultiTexCoord1i)(GLenum target, GLint s);
    void (APIENTRY *glMultiTexCoord1iv)(GLenum target, const GLint *v);
    void (APIENTRY *glMultiTexCoord1s)(GLenum target, GLshort s);
    void (APIENTRY *glMultiTexCoord1sv)(GLenum target, const GLshort *v);
    void (APIENTRY *glMultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t);
    void (APIENTRY *glMultiTexCoord2dv)(GLenum target, const GLdouble *v);
    void (APIENTRY *glMultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t);
    void (APIENTRY *glMultiTexCoord2fv)(GLenum target, const GLfloat *v);
    void (APIENTRY *glMultiTexCoord2i)(GLenum target, GLint s, GLint t);
    void (APIENTRY *glMultiTexCoord2iv)(GLenum target, const GLint *v);
    void (APIENTRY *glMultiTexCoord2s)(GLenum target, GLshort s, GLshort t);
    void (APIENTRY *glMultiTexCoord2sv)(GLenum target, const GLshort *v);
    void (APIENTRY *glMultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t,
                                       GLdouble r);
    void (APIENTRY *glMultiTexCoord3dv)(GLenum target, const GLdouble *v);
    void (APIENTRY *glMultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t,
                                       GLfloat r);
    void (APIENTRY *glMultiTexCoord3fv)(GLenum target, const GLfloat *v);
    void (APIENTRY *glMultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r);
    void (APIENTRY *glMultiTexCoord3iv)(GLenum target, const GLint *v);
    void (APIENTRY *glMultiTexCoord3s)(GLenum target, GLshort s, GLshort t,
                                       GLshort r);
    void (APIENTRY *glMultiTexCoord3sv)(GLenum target, const GLshort *v);
    void (APIENTRY *glMultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t,
                                       GLdouble r, GLdouble q);
    void (APIENTRY *glMultiTexCoord4dv)(GLenum target, const GLdouble *v);
    void (APIENTRY *glMultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t,
                                       GLfloat r, GLfloat q);
    void (APIENTRY *glMultiTexCoord4fv)(GLenum target, const GLfloat *v);
    void (APIENTRY *glMultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r,
                                       GLint q);
    void (APIENTRY *glMultiTexCoord4iv)(GLenum target, const GLint *v);
    void (APIENTRY *glMultiTexCoord4s)(GLenum target, GLshort s, GLshort t,
                                       GLshort r, GLshort q);
    void (APIENTRY *glMultiTexCoord4sv)(GLenum target, const GLshort *v);

    // Construction
    ARBMultitexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBMultitexture

// GL_ARB_occlusion_query extension API specification.
struct ARBOcclusionQuery {
    // Public Members
    void (APIENTRY *glBeginQuery)(GLenum target, GLuint id);
    void (APIENTRY *glDeleteQueries)(GLsizei n, const GLuint *ids);
    void (APIENTRY *glEndQuery)(GLenum target);
    void (APIENTRY *glGenQueries)(GLsizei n, GLuint *ids);
    void (APIENTRY *glGetQueryObjectiv)(GLuint id, GLenum pname, GLint *params);
    void (APIENTRY *glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint *params);
    void (APIENTRY *glGetQueryiv)(GLenum target, GLenum pname, GLint *params);
    GLboolean(APIENTRY *glIsQuery)(GLuint id);

    // Construction
    ARBOcclusionQuery();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBOcclusionQuery

// GL_ARB_parallel_shader_compile extension API specification.
struct ARBParallelShaderCompile {
    // Public Members
    void (APIENTRY *glMaxShaderCompilerThreads)(GLuint count);

    // Construction
    ARBParallelShaderCompile();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBParallelShaderCompile

// GL_ARB_point_parameters extension API specification.
struct ARBPointParameters {
    // Public Members
    void (APIENTRY *glPointParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPointParameterfv)(GLenum pname, const GLfloat *params);

    // Construction
    ARBPointParameters();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBPointParameters

// GL_ARB_robustness extension API specification.
struct ARBRobustness {
    // Public Members
    GLenum(APIENTRY *glGetGraphicsResetStatus)();
    void (APIENTRY *glGetnCompressedTexImage)(GLenum target, GLint lod,
                                              GLsizei bufSize, void *img);
    void (APIENTRY *glGetnTexImage)(GLenum target, GLint level, GLenum format,
                                    GLenum type, GLsizei bufSize, void *img);
    void (APIENTRY *glGetnUniformdv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLdouble *params);
    void (APIENTRY *glGetnUniformfv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLfloat *params);
    void (APIENTRY *glGetnUniformiv)(GLuint program, GLint location,
                                     GLsizei bufSize, GLint *params);
    void (APIENTRY *glGetnUniformuiv)(GLuint program, GLint location,
                                      GLsizei bufSize, GLuint *params);
    void (APIENTRY *glReadnPixels)(GLint x, GLint y, GLsizei width,
                                   GLsizei height, GLenum format, GLenum type,
                                   GLsizei bufSize, void *data);

    // Construction
    ARBRobustness();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBRobustness

// GL_ARB_sample_locations extension API specification.
struct ARBSampleLocations {
    // Public Members
    void (APIENTRY *glEvaluateDepthValues)();
    void (APIENTRY *glFramebufferSampleLocationsfv)(GLenum target, GLuint start,
                                                    GLsizei count,
                                                    const GLfloat *v);
    void (APIENTRY *glNamedFramebufferSampleLocationsfv)(GLuint framebuffer,
                                                         GLuint start,
                                                         GLsizei count,
                                                         const GLfloat *v);

    // Construction
    ARBSampleLocations();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBSampleLocations

// GL_ARB_sample_shading extension API specification.
struct ARBSampleShading {
    // Public Members
    void (APIENTRY *glMinSampleShading)(GLfloat value);

    // Construction
    ARBSampleShading();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBSampleShading

// GL_ARB_shader_objects extension API specification.
struct ARBShaderObjects {
    // Public Members
    void (APIENTRY *glAttachObject)(GLhandleARB containerObj, GLhandleARB obj);
    void (APIENTRY *glCompileShader)(GLhandleARB shaderObj);
    GLhandleARB(APIENTRY *glCreateProgramObject)();
    GLhandleARB(APIENTRY *glCreateShaderObject)(GLenum shaderType);
    void (APIENTRY *glDeleteObject)(GLhandleARB obj);
    void (APIENTRY *glDetachObject)(GLhandleARB containerObj,
                                    GLhandleARB attachedObj);
    void (APIENTRY *glGetActiveUniform)(GLhandleARB programObj, GLuint index,
                                        GLsizei maxLength, GLsizei *length,
                                        GLint *size, GLenum *type,
                                        GLcharARB *name);
    void (APIENTRY *glGetAttachedObjects)(GLhandleARB containerObj,
                                          GLsizei maxCount, GLsizei *count,
                                          GLhandleARB *obj);
    GLhandleARB(APIENTRY *glGetHandle)(GLenum pname);
    void (APIENTRY *glGetInfoLog)(GLhandleARB obj, GLsizei maxLength,
                                  GLsizei *length, GLcharARB *infoLog);
    void (APIENTRY *glGetObjectParameterfv)(GLhandleARB obj, GLenum pname,
                                            GLfloat *params);
    void (APIENTRY *glGetObjectParameteriv)(GLhandleARB obj, GLenum pname,
                                            GLint *params);
    void (APIENTRY *glGetShaderSource)(GLhandleARB obj, GLsizei maxLength,
                                       GLsizei *length, GLcharARB *source);
    GLint(APIENTRY *glGetUniformLocation)(GLhandleARB programObj,
                                          const GLcharARB *name);
    void (APIENTRY *glGetUniformfv)(GLhandleARB programObj, GLint location,
                                    GLfloat *params);
    void (APIENTRY *glGetUniformiv)(GLhandleARB programObj, GLint location,
                                    GLint *params);
    void (APIENTRY *glLinkProgram)(GLhandleARB programObj);
    void (APIENTRY *glShaderSource)(GLhandleARB shaderObj, GLsizei count,
                                    const GLcharARB **string,
                                    const GLint *length);
    void (APIENTRY *glUniform1f)(GLint location, GLfloat v0);
    void (APIENTRY *glUniform1fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform1i)(GLint location, GLint v0);
    void (APIENTRY *glUniform1iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
    void (APIENTRY *glUniform2fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform2i)(GLint location, GLint v0, GLint v1);
    void (APIENTRY *glUniform2iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform3f)(GLint location, GLfloat v0, GLfloat v1,
                                 GLfloat v2);
    void (APIENTRY *glUniform3fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
    void (APIENTRY *glUniform3iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniform4f)(GLint location, GLfloat v0, GLfloat v1,
                                 GLfloat v2, GLfloat v3);
    void (APIENTRY *glUniform4fv)(GLint location, GLsizei count,
                                  const GLfloat *value);
    void (APIENTRY *glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2,
                                 GLint v3);
    void (APIENTRY *glUniform4iv)(GLint location, GLsizei count,
                                  const GLint *value);
    void (APIENTRY *glUniformMatrix2fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUniformMatrix3fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUniformMatrix4fv)(GLint location, GLsizei count,
                                        GLboolean transpose,
                                        const GLfloat *value);
    void (APIENTRY *glUseProgramObject)(GLhandleARB programObj);
    void (APIENTRY *glValidateProgram)(GLhandleARB programObj);

    // Construction
    ARBShaderObjects();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBShaderObjects

// GL_ARB_shading_language_include extension API specification.
struct ARBShadingLanguageInclude {
    // Public Members
    void (APIENTRY *glCompileShaderInclude)(GLuint shader, GLsizei count,
                                            const GLchar *const *path,
                                            const GLint *length);
    void (APIENTRY *glDeleteNamedString)(GLint namelen, const GLchar *name);
    void (APIENTRY *glGetNamedString)(GLint namelen, const GLchar *name,
                                      GLsizei bufSize, GLint *stringlen,
                                      GLchar *string);
    void (APIENTRY *glGetNamedStringiv)(GLint namelen, const GLchar *name,
                                        GLenum pname, GLint *params);
    GLboolean(APIENTRY *glIsNamedString)(GLint namelen, const GLchar *name);
    void (APIENTRY *glNamedString)(GLenum type, GLint namelen,
                                   const GLchar *name, GLint stringlen,
                                   const GLchar *string);

    // Construction
    ARBShadingLanguageInclude();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBShadingLanguageInclude

// GL_ARB_sparse_buffer extension API specification.
struct ARBSparseBuffer {
    // Public Members
    void (APIENTRY *glBufferPageCommitment)(GLenum target, GLintptr offset,
                                            GLsizeiptr size, GLboolean commit);
    void (APIENTRY *glNamedBufferPageCommitmentARB)(GLuint buffer,
                                                    GLintptr offset,
                                                    GLsizeiptr size,
                                                    GLboolean commit);
    void (APIENTRY *glNamedBufferPageCommitmentEXT)(GLuint buffer,
                                                    GLintptr offset,
                                                    GLsizeiptr size,
                                                    GLboolean commit);

    // Construction
    ARBSparseBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBSparseBuffer

// GL_ARB_sparse_texture extension API specification.
struct ARBSparseTexture {
    // Public Members
    void (APIENTRY *glTexPageCommitment)(GLenum target, GLint level,
                                         GLint xoffset, GLint yoffset,
                                         GLint zoffset, GLsizei width,
                                         GLsizei height, GLsizei depth,
                                         GLboolean commit);

    // Construction
    ARBSparseTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBSparseTexture

// GL_ARB_texture_buffer_object extension API specification.
struct ARBTextureBufferObject {
    // Public Members
    void (APIENTRY *glTexBuffer)(GLenum target, GLenum internalformat,
                                 GLuint buffer);

    // Construction
    ARBTextureBufferObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBTextureBufferObject

// GL_ARB_texture_compression extension API specification.
struct ARBTextureCompression {
    // Public Members
    void (APIENTRY *glCompressedTexImage1D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLint border, GLsizei imageSize,
                                            const void *data);
    void (APIENTRY *glCompressedTexImage2D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLsizei height, GLint border,
                                            GLsizei imageSize, const void *data);
    void (APIENTRY *glCompressedTexImage3D)(GLenum target, GLint level,
                                            GLenum internalformat, GLsizei width,
                                            GLsizei height, GLsizei depth,
                                            GLint border, GLsizei imageSize,
                                            const void *data);
    void (APIENTRY *glCompressedTexSubImage1D)(GLenum target, GLint level,
                                               GLint xoffset, GLsizei width,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glCompressedTexSubImage2D)(GLenum target, GLint level,
                                               GLint xoffset, GLint yoffset,
                                               GLsizei width, GLsizei height,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glCompressedTexSubImage3D)(GLenum target, GLint level,
                                               GLint xoffset, GLint yoffset,
                                               GLint zoffset, GLsizei width,
                                               GLsizei height, GLsizei depth,
                                               GLenum format, GLsizei imageSize,
                                               const void *data);
    void (APIENTRY *glGetCompressedTexImage)(GLenum target, GLint level,
                                             void *img);

    // Construction
    ARBTextureCompression();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBTextureCompression

// GL_ARB_transpose_matrix extension API specification.
struct ARBTransposeMatrix {
    // Public Members
    void (APIENTRY *glLoadTransposeMatrixd)(const GLdouble *m);
    void (APIENTRY *glLoadTransposeMatrixf)(const GLfloat *m);
    void (APIENTRY *glMultTransposeMatrixd)(const GLdouble *m);
    void (APIENTRY *glMultTransposeMatrixf)(const GLfloat *m);

    // Construction
    ARBTransposeMatrix();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBTransposeMatrix

// GL_ARB_vertex_blend extension API specification.
struct ARBVertexBlend {
    // Public Members
    void (APIENTRY *glVertexBlend)(GLint count);
    void (APIENTRY *glWeightPointer)(GLint size, GLenum type, GLsizei stride,
                                     const void *pointer);
    void (APIENTRY *glWeightbv)(GLint size, const GLbyte *weights);
    void (APIENTRY *glWeightdv)(GLint size, const GLdouble *weights);
    void (APIENTRY *glWeightfv)(GLint size, const GLfloat *weights);
    void (APIENTRY *glWeightiv)(GLint size, const GLint *weights);
    void (APIENTRY *glWeightsv)(GLint size, const GLshort *weights);
    void (APIENTRY *glWeightubv)(GLint size, const GLubyte *weights);
    void (APIENTRY *glWeightuiv)(GLint size, const GLuint *weights);
    void (APIENTRY *glWeightusv)(GLint size, const GLushort *weights);

    // Construction
    ARBVertexBlend();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBVertexBlend

// GL_ARB_vertex_buffer_object extension API specification.
struct ARBVertexBufferObject {
    // Public Members
    void (APIENTRY *glBindBuffer)(GLenum target, GLuint buffer);
    void (APIENTRY *glBufferData)(GLenum target, GLsizeiptrARB size,
                                  const void *data, GLenum usage);
    void (APIENTRY *glBufferSubData)(GLenum target, GLintptrARB offset,
                                     GLsizeiptrARB size, const void *data);
    void (APIENTRY *glDeleteBuffers)(GLsizei n, const GLuint *buffers);
    void (APIENTRY *glGenBuffers)(GLsizei n, GLuint *buffers);
    void (APIENTRY *glGetBufferParameteriv)(GLenum target, GLenum pname,
                                            GLint *params);
    void (APIENTRY *glGetBufferPointerv)(GLenum target, GLenum pname,
                                         void **params);
    void (APIENTRY *glGetBufferSubData)(GLenum target, GLintptrARB offset,
                                        GLsizeiptrARB size, void *data);
    GLboolean(APIENTRY *glIsBuffer)(GLuint buffer);
    void *(APIENTRY *glMapBuffer)(GLenum target, GLenum access);
    GLboolean(APIENTRY *glUnmapBuffer)(GLenum target);

    // Construction
    ARBVertexBufferObject();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBVertexBufferObject

// GL_ARB_vertex_program extension API specification.
struct ARBVertexProgram {
    // Public Members
    void (APIENTRY *glDisableVertexAttribArray)(GLuint index);
    void (APIENTRY *glEnableVertexAttribArray)(GLuint index);
    void (APIENTRY *glGetVertexAttribPointerv)(GLuint index, GLenum pname,
                                               void **pointer);
    void (APIENTRY *glGetVertexAttribdv)(GLuint index, GLenum pname,
                                         GLdouble *params);
    void (APIENTRY *glGetVertexAttribfv)(GLuint index, GLenum pname,
                                         GLfloat *params);
    void (APIENTRY *glGetVertexAttribiv)(GLuint index, GLenum pname,
                                         GLint *params);
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
    void (APIENTRY *glVertexAttrib4Nbv)(GLuint index, const GLbyte *v);
    void (APIENTRY *glVertexAttrib4Niv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttrib4Nsv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y,
                                        GLubyte z, GLubyte w);
    void (APIENTRY *glVertexAttrib4Nubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttrib4Nuiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttrib4Nusv)(GLuint index, const GLushort *v);
    void (APIENTRY *glVertexAttrib4bv)(GLuint index, const GLbyte *v);
    void (APIENTRY *glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y,
                                      GLdouble z, GLdouble w);
    void (APIENTRY *glVertexAttrib4dv)(GLuint index, const GLdouble *v);
    void (APIENTRY *glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y,
                                      GLfloat z, GLfloat w);
    void (APIENTRY *glVertexAttrib4fv)(GLuint index, const GLfloat *v);
    void (APIENTRY *glVertexAttrib4iv)(GLuint index, const GLint *v);
    void (APIENTRY *glVertexAttrib4s)(GLuint index, GLshort x, GLshort y,
                                      GLshort z, GLshort w);
    void (APIENTRY *glVertexAttrib4sv)(GLuint index, const GLshort *v);
    void (APIENTRY *glVertexAttrib4ubv)(GLuint index, const GLubyte *v);
    void (APIENTRY *glVertexAttrib4uiv)(GLuint index, const GLuint *v);
    void (APIENTRY *glVertexAttrib4usv)(GLuint index, const GLushort *v);
    void (APIENTRY *glVertexAttribPointer)(GLuint index, GLint size, GLenum type,
                                           GLboolean normalized, GLsizei stride,
                                           const void *pointer);

    // Construction
    ARBVertexProgram();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBVertexProgram

// GL_ARB_vertex_shader extension API specification.
struct ARBVertexShader {
    // Public Members
    void (APIENTRY *glBindAttribLocation)(GLhandleARB programObj, GLuint index,
                                          const GLcharARB *name);
    void (APIENTRY *glGetActiveAttrib)(GLhandleARB programObj, GLuint index,
                                       GLsizei maxLength, GLsizei *length,
                                       GLint *size, GLenum *type,
                                       GLcharARB *name);
    GLint(APIENTRY *glGetAttribLocation)(GLhandleARB programObj,
                                         const GLcharARB *name);

   // Construction
    ARBVertexShader();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBVertexShader

// GL_ARB_viewport_array extension API specification.
struct ARBViewportArray {
    // Public Members
    void (APIENTRY *glDepthRangeArraydv)(GLuint first, GLsizei count,
                                         const GLdouble *v);
    void (APIENTRY *glDepthRangeIndexedd)(GLuint index, GLdouble n, GLdouble f);

    // Construction
    ARBViewportArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBViewportArray

// GL_ARB_window_pos extension API specification.
struct ARBWindowPos {
    // Public Members
    void (APIENTRY *glWindowPos2d)(GLdouble x, GLdouble y);
    void (APIENTRY *glWindowPos2dv)(const GLdouble *v);
    void (APIENTRY *glWindowPos2f)(GLfloat x, GLfloat y);
    void (APIENTRY *glWindowPos2fv)(const GLfloat *v);
    void (APIENTRY *glWindowPos2i)(GLint x, GLint y);
    void (APIENTRY *glWindowPos2iv)(const GLint *v);
    void (APIENTRY *glWindowPos2s)(GLshort x, GLshort y);
    void (APIENTRY *glWindowPos2sv)(const GLshort *v);
    void (APIENTRY *glWindowPos3d)(GLdouble x, GLdouble y, GLdouble z);
    void (APIENTRY *glWindowPos3dv)(const GLdouble *v);
    void (APIENTRY *glWindowPos3f)(GLfloat x, GLfloat y, GLfloat z);
    void (APIENTRY *glWindowPos3fv)(const GLfloat *v);
    void (APIENTRY *glWindowPos3i)(GLint x, GLint y, GLint z);
    void (APIENTRY *glWindowPos3iv)(const GLint *v);
    void (APIENTRY *glWindowPos3s)(GLshort x, GLshort y, GLshort z);
    void (APIENTRY *glWindowPos3sv)(const GLshort *v);

    // Construction
    ARBWindowPos();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBWindowPos

} // namespace gl


#ifdef _WIN32
namespace wgl {

// WGL_ARB_buffer_region extension API specification.
struct ARBBufferRegion {
    // Public Members
    HANDLE(APIENTRY *wglCreateBufferRegion)(HDC hDC, int iLayerPlane,
                                            UINT uType);
    VOID(APIENTRY *wglDeleteBufferRegion)(HANDLE hRegion);
    BOOL(APIENTRY *wglRestoreBufferRegion)(HANDLE hRegion, int x, int y,
                                           int width, int height, int xSrc,
                                           int ySrc);
    BOOL(APIENTRY *wglSaveBufferRegion)(HANDLE hRegion, int x, int y, int width,
                                        int height);

   // Construction
    ARBBufferRegion();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBBufferRegion

// WGL_ARB_create_context extension API specification.
struct ARBCreateContext {
    // Public Members
    HGLRC(APIENTRY *wglCreateContextAttribs)(HDC hDC, HGLRC hShareContext,
                                             const int *attribList);

   // Construction
    ARBCreateContext();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBCreateContext

// WGL_ARB_extensions_string extension API specification.
struct ARBExtensionsString {
    // Public Members
    const char *(APIENTRY *wglGetExtensionsString)(HDC hdc);

    // Construction
    ARBExtensionsString();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBExtensionsString

// WGL_ARB_make_current_read extension API specification.
struct ARBMakeCurrentRead {
    // Public Members
    HDC(APIENTRY *wglGetCurrentReadDC)();
    BOOL(APIENTRY *wglMakeContextCurrent)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);

    // Construction
    ARBMakeCurrentRead();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBMakeCurrentRead

// WGL_ARB_pbuffer extension API specification.
struct ARBPbuffer {
    // Public Members
    HPBUFFERARB(APIENTRY *wglCreatePbuffer)(HDC hDC, int iPixelFormat,
                                            int iWidth, int iHeight,
                                            const int *piAttribList);
    BOOL(APIENTRY *wglDestroyPbuffer)(HPBUFFERARB hPbuffer);
    HDC(APIENTRY *wglGetPbufferDC)(HPBUFFERARB hPbuffer);
    BOOL(APIENTRY *wglQueryPbuffer)(HPBUFFERARB hPbuffer, int iAttribute,
                                    int *piValue);
    int (APIENTRY *wglReleasePbufferDC)(HPBUFFERARB hPbuffer, HDC hDC);

    // Construction
    ARBPbuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBPbuffer

// WGL_ARB_pixel_format extension API specification.
struct ARBPixelFormat {
    // Public Members
    BOOL(APIENTRY *wglChoosePixelFormat)(HDC hdc, const int *piAttribIList,
                                         const FLOAT *pfAttribFList,
                                         UINT nMaxFormats, int *piFormats,
                                         UINT *nNumFormats);
    BOOL(APIENTRY *wglGetPixelFormatAttribfv)(HDC hdc, int iPixelFormat,
                                              int iLayerPlane, UINT nAttributes,
                                              const int *piAttributes,
                                              FLOAT *pfValues);
    BOOL(APIENTRY *wglGetPixelFormatAttribiv)(HDC hdc, int iPixelFormat,
                                              int iLayerPlane, UINT nAttributes,
                                              const int *piAttributes,
                                              int *piValues);

   // Construction
    ARBPixelFormat();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBPixelFormat

// WGL_ARB_render_texture extension API specification.
struct ARBRenderTexture {
    // Public Members
    BOOL(APIENTRY *wglBindTexImage)(HPBUFFERARB hPbuffer, int iBuffer);
    BOOL(APIENTRY *wglReleaseTexImage)(HPBUFFERARB hPbuffer, int iBuffer);
    BOOL(APIENTRY *wglSetPbufferAttrib)(HPBUFFERARB hPbuffer,
                                        const int *piAttribList);

   // Construction
    ARBRenderTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBRenderTexture

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// GLX_ARB_create_context extension API specification.
struct ARBCreateContext {
    // Public Members
    GLXContext(APIENTRY *glXCreateContextAttribs)(Display *dpy,
                                                  GLXFBConfig config,
                                                  GLXContext share_context,
                                                  Bool direct,
                                                  const int *attrib_list);

   // Construction
    ARBCreateContext();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBCreateContext

// GLX_ARB_get_proc_address extension API specification.
struct ARBGetProcAddress {
    // Public Members
    __GLXextFuncPtr(APIENTRY *glXGetProcAddress)(const GLubyte *procName);

    // Construction
    ARBGetProcAddress();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct ARBGetProcAddress

} // namespace glx
#endif // ifdef _USES_GLX

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
