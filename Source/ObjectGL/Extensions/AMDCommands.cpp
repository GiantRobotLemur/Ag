//! @file ObjectGL/Extensions/AMDCommands.cpp
//! @brief The definition of AMD-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/AMDCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// AMDDebugOutputAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_debug_output extension.
AMDDebugOutputAPI::AMDDebugOutputAPI() :
    BaseExtension("GL_AMD_debug_output")
{
}

// Grant read-only access to the underlying function pointers.
const AMDDebugOutput &AMDDebugOutputAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_debug_output entry points.
void AMDDebugOutputAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDebugMessageCallbackAMD().
void AMDDebugOutputAPI::debugMessageCallback(GLDEBUGPROCAMD callback,
                                             void *userParam) const
{
    static const char *fnName = "glDebugMessageCallbackAMD";

    beforeCommand(fnName, _api.glDebugMessageCallback);
    _api.glDebugMessageCallback(callback, userParam);
    afterCommand(fnName);
}

// Calls glDebugMessageEnableAMD().
void AMDDebugOutputAPI::debugMessageEnable(GLenum category,
                                           DebugSeverity severity, GLsizei count,
                                           const GLuint *ids, Boolean enabled) const
{
    static const char *fnName = "glDebugMessageEnableAMD";

    beforeCommand(fnName, _api.glDebugMessageEnable);
    _api.glDebugMessageEnable(category, toScalar(severity), count, ids,
                              toScalar(enabled));
    afterCommand(fnName);
}

// Calls glDebugMessageInsertAMD().
void AMDDebugOutputAPI::debugMessageInsert(GLenum category,
                                           DebugSeverity severity, GLuint id,
                                           GLsizei length, const GLchar *buf) const
{
    static const char *fnName = "glDebugMessageInsertAMD";

    beforeCommand(fnName, _api.glDebugMessageInsert);
    _api.glDebugMessageInsert(category, toScalar(severity), id, length, buf);
    afterCommand(fnName);
}

// Calls glGetDebugMessageLogAMD().
GLuint AMDDebugOutputAPI::getDebugMessageLog(GLuint count, GLsizei bufSize,
                                             GLenum *categories,
                                             DebugSeverity *severities,
                                             GLuint *ids, GLsizei *lengths,
                                             GLchar *message) const
{
    static const char *fnName = "glGetDebugMessageLogAMD";

    beforeCommand(fnName, _api.glGetDebugMessageLog);
    GLuint result = _api.glGetDebugMessageLog(count, bufSize, categories,
                                              toScalarPtr(severities), ids,
                                              lengths, message);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// AMDDrawBuffersBlendAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_draw_buffers_blend extension.
AMDDrawBuffersBlendAPI::AMDDrawBuffersBlendAPI() :
    BaseExtension("GL_AMD_draw_buffers_blend")
{
}

// Grant read-only access to the underlying function pointers.
const AMDDrawBuffersBlend &AMDDrawBuffersBlendAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_draw_buffers_blend entry points.
void AMDDrawBuffersBlendAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendEquationIndexedAMD().
void AMDDrawBuffersBlendAPI::blendEquationIndexed(GLuint buf,
                                                  BlendEquationModeEXT mode) const
{
    static const char *fnName = "glBlendEquationIndexedAMD";

    beforeCommand(fnName, _api.glBlendEquationIndexed);
    _api.glBlendEquationIndexed(buf, toScalar(mode));
    afterCommand(fnName);
}

// Calls glBlendEquationSeparateIndexedAMD().
void AMDDrawBuffersBlendAPI::blendEquationSeparateIndexed(GLuint buf,
                                                          BlendEquationModeEXT modeRGB,
                                                          BlendEquationModeEXT modeAlpha) const
{
    static const char *fnName = "glBlendEquationSeparateIndexedAMD";

    beforeCommand(fnName, _api.glBlendEquationSeparateIndexed);
    _api.glBlendEquationSeparateIndexed(buf, toScalar(modeRGB),
                                        toScalar(modeAlpha));
    afterCommand(fnName);
}

// Calls glBlendFuncIndexedAMD().
void AMDDrawBuffersBlendAPI::blendFuncIndexed(GLuint buf, GLenum src, GLenum dst) const
{
    static const char *fnName = "glBlendFuncIndexedAMD";

    beforeCommand(fnName, _api.glBlendFuncIndexed);
    _api.glBlendFuncIndexed(buf, src, dst);
    afterCommand(fnName);
}

// Calls glBlendFuncSeparateIndexedAMD().
void AMDDrawBuffersBlendAPI::blendFuncSeparateIndexed(GLuint buf,
                                                      BlendingFactor srcRGB,
                                                      BlendingFactor dstRGB,
                                                      BlendingFactor srcAlpha,
                                                      BlendingFactor dstAlpha) const
{
    static const char *fnName = "glBlendFuncSeparateIndexedAMD";

    beforeCommand(fnName, _api.glBlendFuncSeparateIndexed);
    _api.glBlendFuncSeparateIndexed(buf, toScalar(srcRGB), toScalar(dstRGB),
                                    toScalar(srcAlpha), toScalar(dstAlpha));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDFramebufferMultisampleAdvancedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_framebuffer_multisample_advanced extension.
AMDFramebufferMultisampleAdvancedAPI::AMDFramebufferMultisampleAdvancedAPI() :
    BaseExtension("GL_AMD_framebuffer_multisample_advanced")
{
}

// Grant read-only access to the underlying function pointers.
const AMDFramebufferMultisampleAdvanced &AMDFramebufferMultisampleAdvancedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_framebuffer_multisample_advanced entry points.
void AMDFramebufferMultisampleAdvancedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glNamedRenderbufferStorageMultisampleAdvancedAMD().
void AMDFramebufferMultisampleAdvancedAPI::namedRenderbufferStorageMultisampleAdvanced(RenderBufferName renderbuffer,
                                                                                       GLsizei samples,
                                                                                       GLsizei storageSamples,
                                                                                       InternalFormat internalformat,
                                                                                       GLsizei width,
                                                                                       GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorageMultisampleAdvancedAMD";

    beforeCommand(fnName, _api.glNamedRenderbufferStorageMultisampleAdvanced);
    _api.glNamedRenderbufferStorageMultisampleAdvanced(renderbuffer.ID, samples,
                                                       storageSamples,
                                                       toScalar(internalformat),
                                                       width, height);
    afterCommand(fnName);
}

// Calls glRenderbufferStorageMultisampleAdvancedAMD().
void AMDFramebufferMultisampleAdvancedAPI::renderbufferStorageMultisampleAdvanced(RenderBufferTarget target,
                                                                                  GLsizei samples,
                                                                                  GLsizei storageSamples,
                                                                                  InternalFormat internalformat,
                                                                                  GLsizei width,
                                                                                  GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorageMultisampleAdvancedAMD";

    beforeCommand(fnName, _api.glRenderbufferStorageMultisampleAdvanced);
    _api.glRenderbufferStorageMultisampleAdvanced(toScalar(target), samples,
                                                  storageSamples,
                                                  toScalar(internalformat),
                                                  width, height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDFramebufferSamplePositionsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_framebuffer_sample_positions extension.
AMDFramebufferSamplePositionsAPI::AMDFramebufferSamplePositionsAPI() :
    BaseExtension("GL_AMD_framebuffer_sample_positions")
{
}

// Grant read-only access to the underlying function pointers.
const AMDFramebufferSamplePositions &AMDFramebufferSamplePositionsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_framebuffer_sample_positions entry points.
void AMDFramebufferSamplePositionsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferSamplePositionsfvAMD().
void AMDFramebufferSamplePositionsAPI::framebufferSamplePositionsFV(FrameBufferTarget target,
                                                                    GLuint numsamples,
                                                                    GLuint pixelindex,
                                                                    const GLfloat *values) const
{
    static const char *fnName = "glFramebufferSamplePositionsfvAMD";

    beforeCommand(fnName, _api.glFramebufferSamplePositionsfv);
    _api.glFramebufferSamplePositionsfv(toScalar(target), numsamples, pixelindex,
                                        values);
    afterCommand(fnName);
}

// Calls glGetFramebufferParameterfvAMD().
void AMDFramebufferSamplePositionsAPI::getFramebufferParameterFV(FrameBufferTarget target,
                                                                 FrameBufferAttachmentParameterName pname,
                                                                 GLuint numsamples,
                                                                 GLuint pixelindex,
                                                                 GLsizei size,
                                                                 GLfloat *values) const
{
    static const char *fnName = "glGetFramebufferParameterfvAMD";

    beforeCommand(fnName, _api.glGetFramebufferParameterfv);
    _api.glGetFramebufferParameterfv(toScalar(target), toScalar(pname),
                                     numsamples, pixelindex, size, values);
    afterCommand(fnName);
}

// Calls glGetNamedFramebufferParameterfvAMD().
void AMDFramebufferSamplePositionsAPI::getNamedFramebufferParameterFV(FrameBufferName framebuffer,
                                                                      GLenum pname,
                                                                      GLuint numsamples,
                                                                      GLuint pixelindex,
                                                                      GLsizei size,
                                                                      GLfloat *values) const
{
    static const char *fnName = "glGetNamedFramebufferParameterfvAMD";

    beforeCommand(fnName, _api.glGetNamedFramebufferParameterfv);
    _api.glGetNamedFramebufferParameterfv(framebuffer.ID, pname, numsamples,
                                          pixelindex, size, values);
    afterCommand(fnName);
}

// Calls glNamedFramebufferSamplePositionsfvAMD().
void AMDFramebufferSamplePositionsAPI::namedFramebufferSamplePositionsFV(FrameBufferName framebuffer,
                                                                         GLuint numsamples,
                                                                         GLuint pixelindex,
                                                                         const GLfloat *values) const
{
    static const char *fnName = "glNamedFramebufferSamplePositionsfvAMD";

    beforeCommand(fnName, _api.glNamedFramebufferSamplePositionsfv);
    _api.glNamedFramebufferSamplePositionsfv(framebuffer.ID, numsamples,
                                             pixelindex, values);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDGPUShaderInt64API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_gpu_shader_int64 extension.
AMDGPUShaderInt64API::AMDGPUShaderInt64API() :
    BaseExtension("GL_AMD_gpu_shader_int64")
{
}

// Grant read-only access to the underlying function pointers.
const AMDGPUShaderInt64 &AMDGPUShaderInt64API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_gpu_shader_int64 entry points.
void AMDGPUShaderInt64API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetUniformi64vNV().
void AMDGPUShaderInt64API::getUniformI64V(ProgramName program, GLint location,
                                          GLint64EXT *params) const
{
    static const char *fnName = "glGetUniformi64vNV";

    beforeCommand(fnName, _api.glGetUniformi64v);
    _api.glGetUniformi64v(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetUniformui64vNV().
void AMDGPUShaderInt64API::getUniformUI64(ProgramName program, GLint location,
                                          GLuint64EXT *params) const
{
    static const char *fnName = "glGetUniformui64vNV";

    beforeCommand(fnName, _api.glGetUniformui64v);
    _api.glGetUniformui64v(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glProgramUniform1i64NV().
void AMDGPUShaderInt64API::programUniform1I64(ProgramName program,
                                              GLint location, GLint64EXT x) const
{
    static const char *fnName = "glProgramUniform1i64NV";

    beforeCommand(fnName, _api.glProgramUniform1i64);
    _api.glProgramUniform1i64(program.ID, location, x);
    afterCommand(fnName);
}

// Calls glProgramUniform1i64vNV().
void AMDGPUShaderInt64API::programUniform1I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64EXT *value) const
{
    static const char *fnName = "glProgramUniform1i64vNV";

    beforeCommand(fnName, _api.glProgramUniform1i64v);
    _api.glProgramUniform1i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1ui64NV().
void AMDGPUShaderInt64API::programUniform1UI64(ProgramName program,
                                               GLint location, GLuint64EXT x) const
{
    static const char *fnName = "glProgramUniform1ui64NV";

    beforeCommand(fnName, _api.glProgramUniform1ui64);
    _api.glProgramUniform1ui64(program.ID, location, x);
    afterCommand(fnName);
}

// Calls glProgramUniform1ui64vNV().
void AMDGPUShaderInt64API::programUniform1UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64EXT *value) const
{
    static const char *fnName = "glProgramUniform1ui64vNV";

    beforeCommand(fnName, _api.glProgramUniform1ui64v);
    _api.glProgramUniform1ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2i64NV().
void AMDGPUShaderInt64API::programUniform2I64(ProgramName program,
                                              GLint location, GLint64EXT x,
                                              GLint64EXT y) const
{
    static const char *fnName = "glProgramUniform2i64NV";

    beforeCommand(fnName, _api.glProgramUniform2i64);
    _api.glProgramUniform2i64(program.ID, location, x, y);
    afterCommand(fnName);
}

// Calls glProgramUniform2i64vNV().
void AMDGPUShaderInt64API::programUniform2I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64EXT *value) const
{
    static const char *fnName = "glProgramUniform2i64vNV";

    beforeCommand(fnName, _api.glProgramUniform2i64v);
    _api.glProgramUniform2i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2ui64NV().
void AMDGPUShaderInt64API::programUniform2UI64(ProgramName program,
                                               GLint location, GLuint64EXT x,
                                               GLuint64EXT y) const
{
    static const char *fnName = "glProgramUniform2ui64NV";

    beforeCommand(fnName, _api.glProgramUniform2ui64);
    _api.glProgramUniform2ui64(program.ID, location, x, y);
    afterCommand(fnName);
}

// Calls glProgramUniform2ui64vNV().
void AMDGPUShaderInt64API::programUniform2UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64EXT *value) const
{
    static const char *fnName = "glProgramUniform2ui64vNV";

    beforeCommand(fnName, _api.glProgramUniform2ui64v);
    _api.glProgramUniform2ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3i64NV().
void AMDGPUShaderInt64API::programUniform3I64(ProgramName program,
                                              GLint location, GLint64EXT x,
                                              GLint64EXT y, GLint64EXT z) const
{
    static const char *fnName = "glProgramUniform3i64NV";

    beforeCommand(fnName, _api.glProgramUniform3i64);
    _api.glProgramUniform3i64(program.ID, location, x, y, z);
    afterCommand(fnName);
}

// Calls glProgramUniform3i64vNV().
void AMDGPUShaderInt64API::programUniform3I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64EXT *value) const
{
    static const char *fnName = "glProgramUniform3i64vNV";

    beforeCommand(fnName, _api.glProgramUniform3i64v);
    _api.glProgramUniform3i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3ui64NV().
void AMDGPUShaderInt64API::programUniform3UI64(ProgramName program,
                                               GLint location, GLuint64EXT x,
                                               GLuint64EXT y, GLuint64EXT z) const
{
    static const char *fnName = "glProgramUniform3ui64NV";

    beforeCommand(fnName, _api.glProgramUniform3ui64);
    _api.glProgramUniform3ui64(program.ID, location, x, y, z);
    afterCommand(fnName);
}

// Calls glProgramUniform3ui64vNV().
void AMDGPUShaderInt64API::programUniform3UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64EXT *value) const
{
    static const char *fnName = "glProgramUniform3ui64vNV";

    beforeCommand(fnName, _api.glProgramUniform3ui64v);
    _api.glProgramUniform3ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4i64NV().
void AMDGPUShaderInt64API::programUniform4I64(ProgramName program,
                                              GLint location, GLint64EXT x,
                                              GLint64EXT y, GLint64EXT z,
                                              GLint64EXT w) const
{
    static const char *fnName = "glProgramUniform4i64NV";

    beforeCommand(fnName, _api.glProgramUniform4i64);
    _api.glProgramUniform4i64(program.ID, location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramUniform4i64vNV().
void AMDGPUShaderInt64API::programUniform4I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64EXT *value) const
{
    static const char *fnName = "glProgramUniform4i64vNV";

    beforeCommand(fnName, _api.glProgramUniform4i64v);
    _api.glProgramUniform4i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4ui64NV().
void AMDGPUShaderInt64API::programUniform4UI64(ProgramName program,
                                               GLint location, GLuint64EXT x,
                                               GLuint64EXT y, GLuint64EXT z,
                                               GLuint64EXT w) const
{
    static const char *fnName = "glProgramUniform4ui64NV";

    beforeCommand(fnName, _api.glProgramUniform4ui64);
    _api.glProgramUniform4ui64(program.ID, location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramUniform4ui64vNV().
void AMDGPUShaderInt64API::programUniform4UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64EXT *value) const
{
    static const char *fnName = "glProgramUniform4ui64vNV";

    beforeCommand(fnName, _api.glProgramUniform4ui64v);
    _api.glProgramUniform4ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1i64NV().
void AMDGPUShaderInt64API::uniform1I64(GLint location, GLint64EXT x) const
{
    static const char *fnName = "glUniform1i64NV";

    beforeCommand(fnName, _api.glUniform1i64);
    _api.glUniform1i64(location, x);
    afterCommand(fnName);
}

// Calls glUniform1i64vNV().
void AMDGPUShaderInt64API::uniform1I64V(GLint location, GLsizei count,
                                        const GLint64EXT *value) const
{
    static const char *fnName = "glUniform1i64vNV";

    beforeCommand(fnName, _api.glUniform1i64v);
    _api.glUniform1i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1ui64NV().
void AMDGPUShaderInt64API::uniform1UI64(GLint location, GLuint64EXT x) const
{
    static const char *fnName = "glUniform1ui64NV";

    beforeCommand(fnName, _api.glUniform1ui64);
    _api.glUniform1ui64(location, x);
    afterCommand(fnName);
}

// Calls glUniform1ui64vNV().
void AMDGPUShaderInt64API::uniform1UI64(GLint location, GLsizei count,
                                        const GLuint64EXT *value) const
{
    static const char *fnName = "glUniform1ui64vNV";

    beforeCommand(fnName, _api.glUniform1ui64v);
    _api.glUniform1ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2i64NV().
void AMDGPUShaderInt64API::uniform2I64(GLint location, GLint64EXT x,
                                       GLint64EXT y) const
{
    static const char *fnName = "glUniform2i64NV";

    beforeCommand(fnName, _api.glUniform2i64);
    _api.glUniform2i64(location, x, y);
    afterCommand(fnName);
}

// Calls glUniform2i64vNV().
void AMDGPUShaderInt64API::uniform2I64V(GLint location, GLsizei count,
                                        const GLint64EXT *value) const
{
    static const char *fnName = "glUniform2i64vNV";

    beforeCommand(fnName, _api.glUniform2i64v);
    _api.glUniform2i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2ui64NV().
void AMDGPUShaderInt64API::uniform2UI64(GLint location, GLuint64EXT x,
                                        GLuint64EXT y) const
{
    static const char *fnName = "glUniform2ui64NV";

    beforeCommand(fnName, _api.glUniform2ui64);
    _api.glUniform2ui64(location, x, y);
    afterCommand(fnName);
}

// Calls glUniform2ui64vNV().
void AMDGPUShaderInt64API::uniform2UI64(GLint location, GLsizei count,
                                        const GLuint64EXT *value) const
{
    static const char *fnName = "glUniform2ui64vNV";

    beforeCommand(fnName, _api.glUniform2ui64v);
    _api.glUniform2ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3i64NV().
void AMDGPUShaderInt64API::uniform3I64(GLint location, GLint64EXT x,
                                       GLint64EXT y, GLint64EXT z) const
{
    static const char *fnName = "glUniform3i64NV";

    beforeCommand(fnName, _api.glUniform3i64);
    _api.glUniform3i64(location, x, y, z);
    afterCommand(fnName);
}

// Calls glUniform3i64vNV().
void AMDGPUShaderInt64API::uniform3I64V(GLint location, GLsizei count,
                                        const GLint64EXT *value) const
{
    static const char *fnName = "glUniform3i64vNV";

    beforeCommand(fnName, _api.glUniform3i64v);
    _api.glUniform3i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3ui64NV().
void AMDGPUShaderInt64API::uniform3UI64(GLint location, GLuint64EXT x,
                                        GLuint64EXT y, GLuint64EXT z) const
{
    static const char *fnName = "glUniform3ui64NV";

    beforeCommand(fnName, _api.glUniform3ui64);
    _api.glUniform3ui64(location, x, y, z);
    afterCommand(fnName);
}

// Calls glUniform3ui64vNV().
void AMDGPUShaderInt64API::uniform3UI64(GLint location, GLsizei count,
                                        const GLuint64EXT *value) const
{
    static const char *fnName = "glUniform3ui64vNV";

    beforeCommand(fnName, _api.glUniform3ui64v);
    _api.glUniform3ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4i64NV().
void AMDGPUShaderInt64API::uniform4I64(GLint location, GLint64EXT x,
                                       GLint64EXT y, GLint64EXT z, GLint64EXT w) const
{
    static const char *fnName = "glUniform4i64NV";

    beforeCommand(fnName, _api.glUniform4i64);
    _api.glUniform4i64(location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glUniform4i64vNV().
void AMDGPUShaderInt64API::uniform4I64V(GLint location, GLsizei count,
                                        const GLint64EXT *value) const
{
    static const char *fnName = "glUniform4i64vNV";

    beforeCommand(fnName, _api.glUniform4i64v);
    _api.glUniform4i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4ui64NV().
void AMDGPUShaderInt64API::uniform4UI64(GLint location, GLuint64EXT x,
                                        GLuint64EXT y, GLuint64EXT z,
                                        GLuint64EXT w) const
{
    static const char *fnName = "glUniform4ui64NV";

    beforeCommand(fnName, _api.glUniform4ui64);
    _api.glUniform4ui64(location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glUniform4ui64vNV().
void AMDGPUShaderInt64API::uniform4UI64(GLint location, GLsizei count,
                                        const GLuint64EXT *value) const
{
    static const char *fnName = "glUniform4ui64vNV";

    beforeCommand(fnName, _api.glUniform4ui64v);
    _api.glUniform4ui64v(location, count, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDInterleavedElementsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_interleaved_elements extension.
AMDInterleavedElementsAPI::AMDInterleavedElementsAPI() :
    BaseExtension("GL_AMD_interleaved_elements")
{
}

// Grant read-only access to the underlying function pointers.
const AMDInterleavedElements &AMDInterleavedElementsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_interleaved_elements entry points.
void AMDInterleavedElementsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVertexAttribParameteriAMD().
void AMDInterleavedElementsAPI::vertexAttribParameterI(GLuint index,
                                                       GLenum pname, GLint param) const
{
    static const char *fnName = "glVertexAttribParameteriAMD";

    beforeCommand(fnName, _api.glVertexAttribParameteri);
    _api.glVertexAttribParameteri(index, pname, param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDMultiDrawIndirectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_multi_draw_indirect extension.
AMDMultiDrawIndirectAPI::AMDMultiDrawIndirectAPI() :
    BaseExtension("GL_AMD_multi_draw_indirect")
{
}

// Grant read-only access to the underlying function pointers.
const AMDMultiDrawIndirect &AMDMultiDrawIndirectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_multi_draw_indirect entry points.
void AMDMultiDrawIndirectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiDrawArraysIndirectAMD().
void AMDMultiDrawIndirectAPI::multiDrawArraysIndirect(PrimitiveType mode,
                                                      const void *indirect,
                                                      GLsizei primcount,
                                                      GLsizei stride) const
{
    static const char *fnName = "glMultiDrawArraysIndirectAMD";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirect);
    _api.glMultiDrawArraysIndirect(toScalar(mode), indirect, primcount, stride);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirectAMD().
void AMDMultiDrawIndirectAPI::multiDrawElementsIndirect(PrimitiveType mode,
                                                        DrawElementsType type,
                                                        const void *indirect,
                                                        GLsizei primcount,
                                                        GLsizei stride) const
{
    static const char *fnName = "glMultiDrawElementsIndirectAMD";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirect);
    _api.glMultiDrawElementsIndirect(toScalar(mode), toScalar(type), indirect,
                                     primcount, stride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDNameGenDeleteAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_name_gen_delete extension.
AMDNameGenDeleteAPI::AMDNameGenDeleteAPI() :
    BaseExtension("GL_AMD_name_gen_delete")
{
}

// Grant read-only access to the underlying function pointers.
const AMDNameGenDelete &AMDNameGenDeleteAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_name_gen_delete entry points.
void AMDNameGenDeleteAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeleteNamesAMD().
void AMDNameGenDeleteAPI::deleteNames(GLenum identifier, GLuint num,
                                      const GLuint *names) const
{
    static const char *fnName = "glDeleteNamesAMD";

    beforeCommand(fnName, _api.glDeleteNames);
    _api.glDeleteNames(identifier, num, names);
    afterCommand(fnName);
}

// Calls glGenNamesAMD().
void AMDNameGenDeleteAPI::genNames(GLenum identifier, GLuint num, GLuint *names) const
{
    static const char *fnName = "glGenNamesAMD";

    beforeCommand(fnName, _api.glGenNames);
    _api.glGenNames(identifier, num, names);
    afterCommand(fnName);
}

// Calls glIsNameAMD().
Boolean AMDNameGenDeleteAPI::isName(GLenum identifier, GLuint name) const
{
    static const char *fnName = "glIsNameAMD";

    beforeCommand(fnName, _api.glIsName);
    GLboolean result = _api.glIsName(identifier, name);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// AMDOcclusionQueryEventAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_occlusion_query_event extension.
AMDOcclusionQueryEventAPI::AMDOcclusionQueryEventAPI() :
    BaseExtension("GL_AMD_occlusion_query_event")
{
}

// Grant read-only access to the underlying function pointers.
const AMDOcclusionQueryEvent &AMDOcclusionQueryEventAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_occlusion_query_event entry points.
void AMDOcclusionQueryEventAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glQueryObjectParameteruiAMD().
void AMDOcclusionQueryEventAPI::queryObjectParameterUI(QueryTarget target,
                                                       QueryName id,
                                                       GLenum pname,
                                                       GLuint  /* OcclusionQueryEventMaskAMD */ param) const
{
    static const char *fnName = "glQueryObjectParameteruiAMD";

    beforeCommand(fnName, _api.glQueryObjectParameterui);
    _api.glQueryObjectParameterui(toScalar(target), id.ID, pname, param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDPerformanceMonitorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_performance_monitor extension.
AMDPerformanceMonitorAPI::AMDPerformanceMonitorAPI() :
    BaseExtension("GL_AMD_performance_monitor")
{
}

// Grant read-only access to the underlying function pointers.
const AMDPerformanceMonitor &AMDPerformanceMonitorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_performance_monitor entry points.
void AMDPerformanceMonitorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginPerfMonitorAMD().
void AMDPerformanceMonitorAPI::beginPerfMonitor(GLuint monitor) const
{
    static const char *fnName = "glBeginPerfMonitorAMD";

    beforeCommand(fnName, _api.glBeginPerfMonitor);
    _api.glBeginPerfMonitor(monitor);
    afterCommand(fnName);
}

// Calls glDeletePerfMonitorsAMD().
void AMDPerformanceMonitorAPI::deletePerfMonitors(GLsizei n, GLuint *monitors) const
{
    static const char *fnName = "glDeletePerfMonitorsAMD";

    beforeCommand(fnName, _api.glDeletePerfMonitors);
    _api.glDeletePerfMonitors(n, monitors);
    afterCommand(fnName);
}

// Calls glEndPerfMonitorAMD().
void AMDPerformanceMonitorAPI::endPerfMonitor(GLuint monitor) const
{
    static const char *fnName = "glEndPerfMonitorAMD";

    beforeCommand(fnName, _api.glEndPerfMonitor);
    _api.glEndPerfMonitor(monitor);
    afterCommand(fnName);
}

// Calls glGenPerfMonitorsAMD().
void AMDPerformanceMonitorAPI::genPerfMonitors(GLsizei n, GLuint *monitors) const
{
    static const char *fnName = "glGenPerfMonitorsAMD";

    beforeCommand(fnName, _api.glGenPerfMonitors);
    _api.glGenPerfMonitors(n, monitors);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorCounterDataAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorCounterData(GLuint monitor,
                                                         GLenum pname,
                                                         GLsizei dataSize,
                                                         GLuint *data,
                                                         GLint *bytesWritten) const
{
    static const char *fnName = "glGetPerfMonitorCounterDataAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorCounterData);
    _api.glGetPerfMonitorCounterData(monitor, pname, dataSize, data,
                                     bytesWritten);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorCounterInfoAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorCounterInfo(GLuint group,
                                                         GLuint counter,
                                                         GLenum pname,
                                                         void *data) const
{
    static const char *fnName = "glGetPerfMonitorCounterInfoAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorCounterInfo);
    _api.glGetPerfMonitorCounterInfo(group, counter, pname, data);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorCounterStringAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorCounterString(GLuint group,
                                                           GLuint counter,
                                                           GLsizei bufSize,
                                                           GLsizei *length,
                                                           GLchar *counterString) const
{
    static const char *fnName = "glGetPerfMonitorCounterStringAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorCounterString);
    _api.glGetPerfMonitorCounterString(group, counter, bufSize, length,
                                       counterString);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorCountersAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorCounters(GLuint group,
                                                      GLint *numCounters,
                                                      GLint *maxActiveCounters,
                                                      GLsizei counterSize,
                                                      GLuint *counters) const
{
    static const char *fnName = "glGetPerfMonitorCountersAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorCounters);
    _api.glGetPerfMonitorCounters(group, numCounters, maxActiveCounters,
                                  counterSize, counters);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorGroupStringAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorGroupString(GLuint group,
                                                         GLsizei bufSize,
                                                         GLsizei *length,
                                                         GLchar *groupString) const
{
    static const char *fnName = "glGetPerfMonitorGroupStringAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorGroupString);
    _api.glGetPerfMonitorGroupString(group, bufSize, length, groupString);
    afterCommand(fnName);
}

// Calls glGetPerfMonitorGroupsAMD().
void AMDPerformanceMonitorAPI::getPerfMonitorGroups(GLint *numGroups,
                                                    GLsizei groupsSize,
                                                    GLuint *groups) const
{
    static const char *fnName = "glGetPerfMonitorGroupsAMD";

    beforeCommand(fnName, _api.glGetPerfMonitorGroups);
    _api.glGetPerfMonitorGroups(numGroups, groupsSize, groups);
    afterCommand(fnName);
}

// Calls glSelectPerfMonitorCountersAMD().
void AMDPerformanceMonitorAPI::selectPerfMonitorCounters(GLuint monitor,
                                                         Boolean enable,
                                                         GLuint group,
                                                         GLint numCounters,
                                                         GLuint *counterList) const
{
    static const char *fnName = "glSelectPerfMonitorCountersAMD";

    beforeCommand(fnName, _api.glSelectPerfMonitorCounters);
    _api.glSelectPerfMonitorCounters(monitor, toScalar(enable), group,
                                     numCounters, counterList);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDSamplePositionsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_sample_positions extension.
AMDSamplePositionsAPI::AMDSamplePositionsAPI() :
    BaseExtension("GL_AMD_sample_positions")
{
}

// Grant read-only access to the underlying function pointers.
const AMDSamplePositions &AMDSamplePositionsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_sample_positions entry points.
void AMDSamplePositionsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSetMultisamplefvAMD().
void AMDSamplePositionsAPI::setMultisampleFV(GLenum pname, GLuint index,
                                             const GLfloat *val) const
{
    static const char *fnName = "glSetMultisamplefvAMD";

    beforeCommand(fnName, _api.glSetMultisamplefv);
    _api.glSetMultisamplefv(pname, index, val);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDSparseTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_sparse_texture extension.
AMDSparseTextureAPI::AMDSparseTextureAPI() :
    BaseExtension("GL_AMD_sparse_texture")
{
}

// Grant read-only access to the underlying function pointers.
const AMDSparseTexture &AMDSparseTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_sparse_texture entry points.
void AMDSparseTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexStorageSparseAMD().
void AMDSparseTextureAPI::texStorageSparse(TextureTarget target,
                                           SizedInternalFormat internalFormat,
                                           GLsizei width, GLsizei height,
                                           GLsizei depth, GLsizei layers,
                                           GLbitfield  /* TextureStorageMaskAMD */ flags) const
{
    static const char *fnName = "glTexStorageSparseAMD";

    beforeCommand(fnName, _api.glTexStorageSparse);
    _api.glTexStorageSparse(toScalar(target), toScalar(internalFormat), width,
                            height, depth, layers, flags);
    afterCommand(fnName);
}

// Calls glTextureStorageSparseAMD().
void AMDSparseTextureAPI::textureStorageSparse(TextureName texture,
                                               GLenum target,
                                               SizedInternalFormat internalFormat,
                                               GLsizei width, GLsizei height,
                                               GLsizei depth, GLsizei layers,
                                               GLbitfield  /* TextureStorageMaskAMD */ flags) const
{
    static const char *fnName = "glTextureStorageSparseAMD";

    beforeCommand(fnName, _api.glTextureStorageSparse);
    _api.glTextureStorageSparse(texture.ID, target, toScalar(internalFormat),
                                width, height, depth, layers, flags);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDStencilOperationExtendedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_stencil_operation_extended extension.
AMDStencilOperationExtendedAPI::AMDStencilOperationExtendedAPI() :
    BaseExtension("GL_AMD_stencil_operation_extended")
{
}

// Grant read-only access to the underlying function pointers.
const AMDStencilOperationExtended &AMDStencilOperationExtendedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_stencil_operation_extended entry points.
void AMDStencilOperationExtendedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glStencilOpValueAMD().
void AMDStencilOperationExtendedAPI::stencilOpValue(StencilFaceDirection face,
                                                    GLuint value) const
{
    static const char *fnName = "glStencilOpValueAMD";

    beforeCommand(fnName, _api.glStencilOpValue);
    _api.glStencilOpValue(toScalar(face), value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// AMDVertexShaderTessellatorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_AMD_vertex_shader_tessellator extension.
AMDVertexShaderTessellatorAPI::AMDVertexShaderTessellatorAPI() :
    BaseExtension("GL_AMD_vertex_shader_tessellator")
{
}

// Grant read-only access to the underlying function pointers.
const AMDVertexShaderTessellator &AMDVertexShaderTessellatorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_AMD_vertex_shader_tessellator entry points.
void AMDVertexShaderTessellatorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTessellationFactorAMD().
void AMDVertexShaderTessellatorAPI::tessellationFactor(GLfloat factor) const
{
    static const char *fnName = "glTessellationFactorAMD";

    beforeCommand(fnName, _api.glTessellationFactor);
    _api.glTessellationFactor(factor);
    afterCommand(fnName);
}

// Calls glTessellationModeAMD().
void AMDVertexShaderTessellatorAPI::tessellationMode(GLenum mode) const
{
    static const char *fnName = "glTessellationModeAMD";

    beforeCommand(fnName, _api.glTessellationMode);
    _api.glTessellationMode(mode);
    afterCommand(fnName);
}

} // namespace gl

#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// AMDGPUAssociationAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_AMD_gpu_association extension.
AMDGPUAssociationAPI::AMDGPUAssociationAPI() :
    BaseExtension("WGL_AMD_gpu_association")
{
}

// Grant read-only access to the underlying function pointers.
const AMDGPUAssociation &AMDGPUAssociationAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_AMD_gpu_association entry points.
void AMDGPUAssociationAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBlitContextFramebufferAMD().
VOID AMDGPUAssociationAPI::blitContextFramebuffer(HGLRC dstCtx, GLint srcX0,
                                                  GLint srcY0, GLint srcX1,
                                                  GLint srcY1, GLint dstX0,
                                                  GLint dstY0, GLint dstX1,
                                                  GLint dstY1, GLbitfield mask,
                                                  GLenum filter) const
{
    static const char *fnName = "wglBlitContextFramebufferAMD";

    beforeCommand(fnName, _api.wglBlitContextFramebuffer);
    _api.wglBlitContextFramebuffer(dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0,
                                   dstY0, dstX1, dstY1, mask, filter);
    afterCommand(fnName);
}

// Calls wglCreateAssociatedContextAMD().
HGLRC AMDGPUAssociationAPI::createAssociateDContext(UINT id) const
{
    static const char *fnName = "wglCreateAssociatedContextAMD";

    beforeCommand(fnName, _api.wglCreateAssociatedContext);
    HGLRC result = _api.wglCreateAssociatedContext(id);
    afterCommand(fnName);

    return result;
}

// Calls wglCreateAssociatedContextAttribsAMD().
HGLRC AMDGPUAssociationAPI::createAssociateDContextAttribs(UINT id,
                                                           HGLRC hShareContext,
                                                           const int *attribList) const
{
    static const char *fnName = "wglCreateAssociatedContextAttribsAMD";

    beforeCommand(fnName, _api.wglCreateAssociatedContextAttribs);
    HGLRC result = _api.wglCreateAssociatedContextAttribs(id, hShareContext,
                                                          attribList);
    afterCommand(fnName);

    return result;
}

// Calls wglDeleteAssociatedContextAMD().
BOOL AMDGPUAssociationAPI::deleteAssociateDContext(HGLRC hglrc) const
{
    static const char *fnName = "wglDeleteAssociatedContextAMD";

    beforeCommand(fnName, _api.wglDeleteAssociatedContext);
    BOOL result = _api.wglDeleteAssociatedContext(hglrc);
    afterCommand(fnName);

    return result;
}

// Calls wglGetContextGPUIDAMD().
UINT AMDGPUAssociationAPI::getContextGpuid(HGLRC hglrc) const
{
    static const char *fnName = "wglGetContextGPUIDAMD";

    beforeCommand(fnName, _api.wglGetContextGPUID);
    UINT result = _api.wglGetContextGPUID(hglrc);
    afterCommand(fnName);

    return result;
}

// Calls wglGetCurrentAssociatedContextAMD().
HGLRC AMDGPUAssociationAPI::getCurrentAssociateDContext() const
{
    static const char *fnName = "wglGetCurrentAssociatedContextAMD";

    beforeCommand(fnName, _api.wglGetCurrentAssociatedContext);
    HGLRC result = _api.wglGetCurrentAssociatedContext();
    afterCommand(fnName);

    return result;
}

// Calls wglGetGPUIDsAMD().
UINT AMDGPUAssociationAPI::getGpuiDs(UINT maxCount, UINT *ids) const
{
    static const char *fnName = "wglGetGPUIDsAMD";

    beforeCommand(fnName, _api.wglGetGPUIDs);
    UINT result = _api.wglGetGPUIDs(maxCount, ids);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGPUInfoAMD().
INT AMDGPUAssociationAPI::getGPUInfo(UINT id, INT property, GLenum dataType,
                                     UINT size, void *data) const
{
    static const char *fnName = "wglGetGPUInfoAMD";

    beforeCommand(fnName, _api.wglGetGPUInfo);
    INT result = _api.wglGetGPUInfo(id, property, dataType, size, data);
    afterCommand(fnName);

    return result;
}

// Calls wglMakeAssociatedContextCurrentAMD().
BOOL AMDGPUAssociationAPI::makeAssociateDContextCurrent(HGLRC hglrc) const
{
    static const char *fnName = "wglMakeAssociatedContextCurrentAMD";

    beforeCommand(fnName, _api.wglMakeAssociatedContextCurrent);
    BOOL result = _api.wglMakeAssociatedContextCurrent(hglrc);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// AMDGPUAssociationAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_AMD_gpu_association extension.
AMDGPUAssociationAPI::AMDGPUAssociationAPI() :
    BaseExtension("GLX_AMD_gpu_association")
{
}

// Grant read-only access to the underlying function pointers.
const AMDGPUAssociation &AMDGPUAssociationAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_AMD_gpu_association entry points.
void AMDGPUAssociationAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBlitContextFramebufferAMD().
void AMDGPUAssociationAPI::xBlitContextFramebuffer(GLXContext dstCtx,
                                                   GLint srcX0, GLint srcY0,
                                                   GLint srcX1, GLint srcY1,
                                                   GLint dstX0, GLint dstY0,
                                                   GLint dstX1, GLint dstY1,
                                                   GLbitfield mask,
                                                   GLenum filter) const
{
    static const char *fnName = "glXBlitContextFramebufferAMD";

    beforeCommand(fnName, _api.glXBlitContextFramebuffer);
    _api.glXBlitContextFramebuffer(dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0,
                                   dstY0, dstX1, dstY1, mask, filter);
    afterCommand(fnName);
}

// Calls glXCreateAssociatedContextAMD().
GLXContext AMDGPUAssociationAPI::xCreateAssociateDContext(unsigned int id,
                                                          GLXContext share_list) const
{
    static const char *fnName = "glXCreateAssociatedContextAMD";

    beforeCommand(fnName, _api.glXCreateAssociatedContext);
    GLXContext result = _api.glXCreateAssociatedContext(id, share_list);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateAssociatedContextAttribsAMD().
GLXContext AMDGPUAssociationAPI::xCreateAssociateDContextAttribs(unsigned int id,
                                                                 GLXContext share_context,
                                                                 const int *attribList) const
{
    static const char *fnName = "glXCreateAssociatedContextAttribsAMD";

    beforeCommand(fnName, _api.glXCreateAssociatedContextAttribs);
    GLXContext result = _api.glXCreateAssociatedContextAttribs(id, share_context,
                                                               attribList);
    afterCommand(fnName);

    return result;
}

// Calls glXDeleteAssociatedContextAMD().
Bool AMDGPUAssociationAPI::xDeleteAssociateDContext(GLXContext ctx) const
{
    static const char *fnName = "glXDeleteAssociatedContextAMD";

    beforeCommand(fnName, _api.glXDeleteAssociatedContext);
    Bool result = _api.glXDeleteAssociatedContext(ctx);
    afterCommand(fnName);

    return result;
}

// Calls glXGetContextGPUIDAMD().
unsigned int AMDGPUAssociationAPI::xGetContextGpuid(GLXContext ctx) const
{
    static const char *fnName = "glXGetContextGPUIDAMD";

    beforeCommand(fnName, _api.glXGetContextGPUID);
    unsigned int result = _api.glXGetContextGPUID(ctx);
    afterCommand(fnName);

    return result;
}

// Calls glXGetCurrentAssociatedContextAMD().
GLXContext AMDGPUAssociationAPI::xGetCurrentAssociateDContext() const
{
    static const char *fnName = "glXGetCurrentAssociatedContextAMD";

    beforeCommand(fnName, _api.glXGetCurrentAssociatedContext);
    GLXContext result = _api.glXGetCurrentAssociatedContext();
    afterCommand(fnName);

    return result;
}

// Calls glXGetGPUIDsAMD().
unsigned int AMDGPUAssociationAPI::xGetGpuiDs(unsigned int maxCount,
                                              unsigned int *ids) const
{
    static const char *fnName = "glXGetGPUIDsAMD";

    beforeCommand(fnName, _api.glXGetGPUIDs);
    unsigned int result = _api.glXGetGPUIDs(maxCount, ids);
    afterCommand(fnName);

    return result;
}

// Calls glXGetGPUInfoAMD().
int AMDGPUAssociationAPI::xGetGPUInfo(unsigned int id, int property,
                                      GLenum dataType, unsigned int size,
                                      void *data) const
{
    static const char *fnName = "glXGetGPUInfoAMD";

    beforeCommand(fnName, _api.glXGetGPUInfo);
    int result = _api.glXGetGPUInfo(id, property, dataType, size, data);
    afterCommand(fnName);

    return result;
}

// Calls glXMakeAssociatedContextCurrentAMD().
Bool AMDGPUAssociationAPI::xMakeAssociateDContextCurrent(GLXContext ctx) const
{
    static const char *fnName = "glXMakeAssociatedContextCurrentAMD";

    beforeCommand(fnName, _api.glXMakeAssociatedContextCurrent);
    Bool result = _api.glXMakeAssociatedContextCurrent(ctx);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

