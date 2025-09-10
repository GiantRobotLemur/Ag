//! @file ObjectGL/Extensions/ARBCommands.cpp
//! @brief The definition of Architecture Review Board (ARB) -specific
//! extensions to the OpenGL Command set wrappers.
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
#include "Ag/ObjectGL/Extensions/ARBCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// ARBES32CompatibilityAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_ES3_2_compatibility extension.
ARBES32CompatibilityAPI::ARBES32CompatibilityAPI() :
    BaseExtension("GL_ARB_ES3_2_compatibility")
{
}

// Grant read-only access to the underlying function pointers.
const ARBES32Compatibility &ARBES32CompatibilityAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_ES3_2_compatibility entry points.
void ARBES32CompatibilityAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPrimitiveBoundingBoxARB().
void ARBES32CompatibilityAPI::primitiveBoundingBox(GLfloat minX, GLfloat minY,
                                                   GLfloat minZ, GLfloat minW,
                                                   GLfloat maxX, GLfloat maxY,
                                                   GLfloat maxZ, GLfloat maxW) const
{
    static const char *fnName = "glPrimitiveBoundingBoxARB";

    beforeCommand(fnName, _api.glPrimitiveBoundingBox);
    _api.glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBBindlessTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_bindless_texture extension.
ARBBindlessTextureAPI::ARBBindlessTextureAPI() :
    BaseExtension("GL_ARB_bindless_texture")
{
}

// Grant read-only access to the underlying function pointers.
const ARBBindlessTexture &ARBBindlessTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_bindless_texture entry points.
void ARBBindlessTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetImageHandleARB().
GLuint64 ARBBindlessTextureAPI::getImageHandle(TextureName texture, GLint level,
                                               Boolean layered, GLint layer,
                                               PixelFormat format) const
{
    static const char *fnName = "glGetImageHandleARB";

    beforeCommand(fnName, _api.glGetImageHandle);
    GLuint64 result = _api.glGetImageHandle(texture.ID, level, toScalar(layered),
                                            layer, toScalar(format));
    afterCommand(fnName);

    return result;
}

// Calls glGetTextureHandleARB().
GLuint64 ARBBindlessTextureAPI::getTextureHandle(TextureName texture) const
{
    static const char *fnName = "glGetTextureHandleARB";

    beforeCommand(fnName, _api.glGetTextureHandle);
    GLuint64 result = _api.glGetTextureHandle(texture.ID);
    afterCommand(fnName);

    return result;
}

// Calls glGetTextureSamplerHandleARB().
GLuint64 ARBBindlessTextureAPI::getTextureSamplerHandle(TextureName texture,
                                                        SamplerName sampler) const
{
    static const char *fnName = "glGetTextureSamplerHandleARB";

    beforeCommand(fnName, _api.glGetTextureSamplerHandle);
    GLuint64 result = _api.glGetTextureSamplerHandle(texture.ID, sampler.ID);
    afterCommand(fnName);

    return result;
}

// Calls glGetVertexAttribLui64vARB().
void ARBBindlessTextureAPI::getVertexAttribLUI64(GLuint index,
                                                 VertexAttribEnum pname,
                                                 GLuint64EXT *params) const
{
    static const char *fnName = "glGetVertexAttribLui64vARB";

    beforeCommand(fnName, _api.glGetVertexAttribLui64v);
    _api.glGetVertexAttribLui64v(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsImageHandleResidentARB().
Boolean ARBBindlessTextureAPI::isImageHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glIsImageHandleResidentARB";

    beforeCommand(fnName, _api.glIsImageHandleResident);
    GLboolean result = _api.glIsImageHandleResident(handle);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsTextureHandleResidentARB().
Boolean ARBBindlessTextureAPI::isTextureHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glIsTextureHandleResidentARB";

    beforeCommand(fnName, _api.glIsTextureHandleResident);
    GLboolean result = _api.glIsTextureHandleResident(handle);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMakeImageHandleNonResidentARB().
void ARBBindlessTextureAPI::makeImageHandleNonResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeImageHandleNonResidentARB";

    beforeCommand(fnName, _api.glMakeImageHandleNonResident);
    _api.glMakeImageHandleNonResident(handle);
    afterCommand(fnName);
}

// Calls glMakeImageHandleResidentARB().
void ARBBindlessTextureAPI::makeImageHandleResident(GLuint64 handle,
                                                    GLenum access) const
{
    static const char *fnName = "glMakeImageHandleResidentARB";

    beforeCommand(fnName, _api.glMakeImageHandleResident);
    _api.glMakeImageHandleResident(handle, access);
    afterCommand(fnName);
}

// Calls glMakeTextureHandleNonResidentARB().
void ARBBindlessTextureAPI::makeTextureHandleNonResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeTextureHandleNonResidentARB";

    beforeCommand(fnName, _api.glMakeTextureHandleNonResident);
    _api.glMakeTextureHandleNonResident(handle);
    afterCommand(fnName);
}

// Calls glMakeTextureHandleResidentARB().
void ARBBindlessTextureAPI::makeTextureHandleResident(GLuint64 handle) const
{
    static const char *fnName = "glMakeTextureHandleResidentARB";

    beforeCommand(fnName, _api.glMakeTextureHandleResident);
    _api.glMakeTextureHandleResident(handle);
    afterCommand(fnName);
}

// Calls glProgramUniformHandleui64ARB().
void ARBBindlessTextureAPI::programUniformHandleUI64(ProgramName program,
                                                     GLint location,
                                                     GLuint64 value) const
{
    static const char *fnName = "glProgramUniformHandleui64ARB";

    beforeCommand(fnName, _api.glProgramUniformHandleui64);
    _api.glProgramUniformHandleui64(program.ID, location, value);
    afterCommand(fnName);
}

// Calls glProgramUniformHandleui64vARB().
void ARBBindlessTextureAPI::programUniformHandleUI64(ProgramName program,
                                                     GLint location,
                                                     GLsizei count,
                                                     const GLuint64 *values) const
{
    static const char *fnName = "glProgramUniformHandleui64vARB";

    beforeCommand(fnName, _api.glProgramUniformHandleui64v);
    _api.glProgramUniformHandleui64v(program.ID, location, count, values);
    afterCommand(fnName);
}

// Calls glUniformHandleui64ARB().
void ARBBindlessTextureAPI::uniformHandleUI64(GLint location, GLuint64 value) const
{
    static const char *fnName = "glUniformHandleui64ARB";

    beforeCommand(fnName, _api.glUniformHandleui64);
    _api.glUniformHandleui64(location, value);
    afterCommand(fnName);
}

// Calls glUniformHandleui64vARB().
void ARBBindlessTextureAPI::uniformHandleUI64(GLint location, GLsizei count,
                                              const GLuint64 *value) const
{
    static const char *fnName = "glUniformHandleui64vARB";

    beforeCommand(fnName, _api.glUniformHandleui64v);
    _api.glUniformHandleui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glVertexAttribL1ui64ARB().
void ARBBindlessTextureAPI::vertexAttribL1UI64(GLuint index, GLuint64EXT x) const
{
    static const char *fnName = "glVertexAttribL1ui64ARB";

    beforeCommand(fnName, _api.glVertexAttribL1ui64);
    _api.glVertexAttribL1ui64(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribL1ui64vARB().
void ARBBindlessTextureAPI::vertexAttribL1UI64(GLuint index,
                                               const GLuint64EXT *v) const
{
    static const char *fnName = "glVertexAttribL1ui64vARB";

    beforeCommand(fnName, _api.glVertexAttribL1ui64v);
    _api.glVertexAttribL1ui64v(index, v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBClEventAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_cl_event extension.
ARBClEventAPI::ARBClEventAPI() :
    BaseExtension("GL_ARB_cl_event")
{
}

// Grant read-only access to the underlying function pointers.
const ARBClEvent &ARBClEventAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_cl_event entry points.
void ARBClEventAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCreateSyncFromCLeventARB().
SyncName ARBClEventAPI::createSyncFromCLevent(struct _cl_context *context,
                                              struct _cl_event *event,
                                              GLbitfield flags) const
{
    static const char *fnName = "glCreateSyncFromCLeventARB";

    beforeCommand(fnName, _api.glCreateSyncFromCLevent);
    GLsync result = _api.glCreateSyncFromCLevent(context, event, flags);
    afterCommand(fnName);

    return SyncName(result);
}

////////////////////////////////////////////////////////////////////////////////
// ARBColorBufferFloatAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_color_buffer_float extension.
ARBColorBufferFloatAPI::ARBColorBufferFloatAPI() :
    BaseExtension("GL_ARB_color_buffer_float")
{
}

// Grant read-only access to the underlying function pointers.
const ARBColorBufferFloat &ARBColorBufferFloatAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_color_buffer_float entry points.
void ARBColorBufferFloatAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClampColorARB().
void ARBColorBufferFloatAPI::clampColor(ClampColorTargetARB target,
                                        ClampColorModeARB clamp) const
{
    static const char *fnName = "glClampColorARB";

    beforeCommand(fnName, _api.glClampColor);
    _api.glClampColor(toScalar(target), toScalar(clamp));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBComputeVariableGroupSizeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_compute_variable_group_size extension.
ARBComputeVariableGroupSizeAPI::ARBComputeVariableGroupSizeAPI() :
    BaseExtension("GL_ARB_compute_variable_group_size")
{
}

// Grant read-only access to the underlying function pointers.
const ARBComputeVariableGroupSize &ARBComputeVariableGroupSizeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_compute_variable_group_size entry points.
void ARBComputeVariableGroupSizeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDispatchComputeGroupSizeARB().
void ARBComputeVariableGroupSizeAPI::dispatchComputeGroupSize(GLuint num_groups_x,
                                                              GLuint num_groups_y,
                                                              GLuint num_groups_z,
                                                              GLuint group_size_x,
                                                              GLuint group_size_y,
                                                              GLuint group_size_z) const
{
    static const char *fnName = "glDispatchComputeGroupSizeARB";

    beforeCommand(fnName, _api.glDispatchComputeGroupSize);
    _api.glDispatchComputeGroupSize(num_groups_x, num_groups_y, num_groups_z,
                                    group_size_x, group_size_y, group_size_z);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBDebugOutputAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_debug_output extension.
ARBDebugOutputAPI::ARBDebugOutputAPI() :
    BaseExtension("GL_ARB_debug_output")
{
}

// Grant read-only access to the underlying function pointers.
const ARBDebugOutput &ARBDebugOutputAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_debug_output entry points.
void ARBDebugOutputAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDebugMessageCallbackARB().
void ARBDebugOutputAPI::debugMessageCallback(GLDEBUGPROCARB callback,
                                             const void *userParam) const
{
    static const char *fnName = "glDebugMessageCallbackARB";

    beforeCommand(fnName, _api.glDebugMessageCallback);
    _api.glDebugMessageCallback(callback, userParam);
    afterCommand(fnName);
}

// Calls glDebugMessageControlARB().
void ARBDebugOutputAPI::debugMessageControl(DebugSource source, DebugType type,
                                            DebugSeverity severity,
                                            GLsizei count, const GLuint *ids,
                                            Boolean enabled) const
{
    static const char *fnName = "glDebugMessageControlARB";

    beforeCommand(fnName, _api.glDebugMessageControl);
    _api.glDebugMessageControl(toScalar(source), toScalar(type),
                               toScalar(severity), count, ids, toScalar(enabled));
    afterCommand(fnName);
}

// Calls glDebugMessageInsertARB().
void ARBDebugOutputAPI::debugMessageInsert(DebugSource source, DebugType type,
                                           GLuint id, DebugSeverity severity,
                                           GLsizei length, const GLchar *buf) const
{
    static const char *fnName = "glDebugMessageInsertARB";

    beforeCommand(fnName, _api.glDebugMessageInsert);
    _api.glDebugMessageInsert(toScalar(source), toScalar(type), id,
                              toScalar(severity), length, buf);
    afterCommand(fnName);
}

// Calls glGetDebugMessageLogARB().
GLuint ARBDebugOutputAPI::getDebugMessageLog(GLuint count, GLsizei bufSize,
                                             DebugSource *sources,
                                             DebugType *types, GLuint *ids,
                                             DebugSeverity *severities,
                                             GLsizei *lengths,
                                             GLchar *messageLog) const
{
    static const char *fnName = "glGetDebugMessageLogARB";

    beforeCommand(fnName, _api.glGetDebugMessageLog);
    GLuint result = _api.glGetDebugMessageLog(count, bufSize,
                                              toScalarPtr(sources),
                                              toScalarPtr(types), ids,
                                              toScalarPtr(severities), lengths,
                                              messageLog);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawBuffersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_draw_buffers extension.
ARBDrawBuffersAPI::ARBDrawBuffersAPI() :
    BaseExtension("GL_ARB_draw_buffers")
{
}

// Grant read-only access to the underlying function pointers.
const ARBDrawBuffers &ARBDrawBuffersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_draw_buffers entry points.
void ARBDrawBuffersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawBuffersARB().
void ARBDrawBuffersAPI::drawBuffers(GLsizei n, const DrawBufferMode *bufs) const
{
    static const char *fnName = "glDrawBuffersARB";

    beforeCommand(fnName, _api.glDrawBuffers);
    _api.glDrawBuffers(n, toScalarPtr(bufs));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawBuffersBlendAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_draw_buffers_blend extension.
ARBDrawBuffersBlendAPI::ARBDrawBuffersBlendAPI() :
    BaseExtension("GL_ARB_draw_buffers_blend")
{
}

// Grant read-only access to the underlying function pointers.
const ARBDrawBuffersBlend &ARBDrawBuffersBlendAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_draw_buffers_blend entry points.
void ARBDrawBuffersBlendAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendEquationSeparateiARB().
void ARBDrawBuffersBlendAPI::blendEquationSeparateI(GLuint buf,
                                                    BlendEquationModeEXT modeRGB,
                                                    BlendEquationModeEXT modeAlpha) const
{
    static const char *fnName = "glBlendEquationSeparateiARB";

    beforeCommand(fnName, _api.glBlendEquationSeparatei);
    _api.glBlendEquationSeparatei(buf, toScalar(modeRGB), toScalar(modeAlpha));
    afterCommand(fnName);
}

// Calls glBlendEquationiARB().
void ARBDrawBuffersBlendAPI::blendEquationI(GLuint buf,
                                            BlendEquationModeEXT mode) const
{
    static const char *fnName = "glBlendEquationiARB";

    beforeCommand(fnName, _api.glBlendEquationi);
    _api.glBlendEquationi(buf, toScalar(mode));
    afterCommand(fnName);
}

// Calls glBlendFuncSeparateiARB().
void ARBDrawBuffersBlendAPI::blendFuncSeparateI(GLuint buf,
                                                BlendingFactor srcRGB,
                                                BlendingFactor dstRGB,
                                                BlendingFactor srcAlpha,
                                                BlendingFactor dstAlpha) const
{
    static const char *fnName = "glBlendFuncSeparateiARB";

    beforeCommand(fnName, _api.glBlendFuncSeparatei);
    _api.glBlendFuncSeparatei(buf, toScalar(srcRGB), toScalar(dstRGB),
                              toScalar(srcAlpha), toScalar(dstAlpha));
    afterCommand(fnName);
}

// Calls glBlendFunciARB().
void ARBDrawBuffersBlendAPI::blendFuncI(GLuint buf, BlendingFactor src,
                                        BlendingFactor dst) const
{
    static const char *fnName = "glBlendFunciARB";

    beforeCommand(fnName, _api.glBlendFunci);
    _api.glBlendFunci(buf, toScalar(src), toScalar(dst));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBDrawInstancedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_draw_instanced extension.
ARBDrawInstancedAPI::ARBDrawInstancedAPI() :
    BaseExtension("GL_ARB_draw_instanced")
{
}

// Grant read-only access to the underlying function pointers.
const ARBDrawInstanced &ARBDrawInstancedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_draw_instanced entry points.
void ARBDrawInstancedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawArraysInstancedARB().
void ARBDrawInstancedAPI::drawArraysInstanced(PrimitiveType mode, GLint first,
                                              GLsizei count, GLsizei primcount) const
{
    static const char *fnName = "glDrawArraysInstancedARB";

    beforeCommand(fnName, _api.glDrawArraysInstanced);
    _api.glDrawArraysInstanced(toScalar(mode), first, count, primcount);
    afterCommand(fnName);
}

// Calls glDrawElementsInstancedARB().
void ARBDrawInstancedAPI::drawElementsInstanced(PrimitiveType mode,
                                                GLsizei count,
                                                DrawElementsType type,
                                                const void *indices,
                                                GLsizei primcount) const
{
    static const char *fnName = "glDrawElementsInstancedARB";

    beforeCommand(fnName, _api.glDrawElementsInstanced);
    _api.glDrawElementsInstanced(toScalar(mode), count, toScalar(type), indices,
                                 primcount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBFragmentProgramAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_fragment_program extension.
ARBFragmentProgramAPI::ARBFragmentProgramAPI() :
    BaseExtension("GL_ARB_fragment_program")
{
}

// Grant read-only access to the underlying function pointers.
const ARBFragmentProgram &ARBFragmentProgramAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_fragment_program entry points.
void ARBFragmentProgramAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindProgramARB().
void ARBFragmentProgramAPI::bindProgram(ProgramTarget target,
                                        ProgramName program) const
{
    static const char *fnName = "glBindProgramARB";

    beforeCommand(fnName, _api.glBindProgram);
    _api.glBindProgram(toScalar(target), program.ID);
    afterCommand(fnName);
}

// Calls glDeleteProgramsARB().
void ARBFragmentProgramAPI::deletePrograms(GLsizei n,
                                           const ProgramName *programs) const
{
    static const char *fnName = "glDeleteProgramsARB";

    beforeCommand(fnName, _api.glDeletePrograms);
    _api.glDeletePrograms(n, reinterpret_cast<const GLuint *>(programs));
    afterCommand(fnName);
}

// Calls glGenProgramsARB().
void ARBFragmentProgramAPI::genPrograms(GLsizei n, ProgramName *programs) const
{
    static const char *fnName = "glGenProgramsARB";

    beforeCommand(fnName, _api.glGenPrograms);
    _api.glGenPrograms(n, reinterpret_cast<GLuint *>(programs));
    afterCommand(fnName);
}

// Calls glGetProgramEnvParameterdvARB().
void ARBFragmentProgramAPI::getProgramEnvParameterDV(ProgramTarget target,
                                                     GLuint index,
                                                     GLdouble *params) const
{
    static const char *fnName = "glGetProgramEnvParameterdvARB";

    beforeCommand(fnName, _api.glGetProgramEnvParameterdv);
    _api.glGetProgramEnvParameterdv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramEnvParameterfvARB().
void ARBFragmentProgramAPI::getProgramEnvParameterFV(ProgramTarget target,
                                                     GLuint index,
                                                     GLfloat *params) const
{
    static const char *fnName = "glGetProgramEnvParameterfvARB";

    beforeCommand(fnName, _api.glGetProgramEnvParameterfv);
    _api.glGetProgramEnvParameterfv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramLocalParameterdvARB().
void ARBFragmentProgramAPI::getProgramLocalParameterDV(ProgramTarget target,
                                                       GLuint index,
                                                       GLdouble *params) const
{
    static const char *fnName = "glGetProgramLocalParameterdvARB";

    beforeCommand(fnName, _api.glGetProgramLocalParameterdv);
    _api.glGetProgramLocalParameterdv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramLocalParameterfvARB().
void ARBFragmentProgramAPI::getProgramLocalParameterFV(ProgramTarget target,
                                                       GLuint index,
                                                       GLfloat *params) const
{
    static const char *fnName = "glGetProgramLocalParameterfvARB";

    beforeCommand(fnName, _api.glGetProgramLocalParameterfv);
    _api.glGetProgramLocalParameterfv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glGetProgramStringARB().
void ARBFragmentProgramAPI::getProgramString(ProgramTarget target,
                                             ProgramStringProperty pname,
                                             void *string) const
{
    static const char *fnName = "glGetProgramStringARB";

    beforeCommand(fnName, _api.glGetProgramString);
    _api.glGetProgramString(toScalar(target), toScalar(pname), string);
    afterCommand(fnName);
}

// Calls glGetProgramivARB().
void ARBFragmentProgramAPI::getProgramIV(ProgramTarget target,
                                         ProgramPropertyARB pname, GLint *params) const
{
    static const char *fnName = "glGetProgramivARB";

    beforeCommand(fnName, _api.glGetProgramiv);
    _api.glGetProgramiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsProgramARB().
Boolean ARBFragmentProgramAPI::isProgram(ProgramName program) const
{
    static const char *fnName = "glIsProgramARB";

    beforeCommand(fnName, _api.glIsProgram);
    GLboolean result = _api.glIsProgram(program.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glProgramEnvParameter4dARB().
void ARBFragmentProgramAPI::programEnvParameter4D(ProgramTarget target,
                                                  GLuint index, GLdouble x,
                                                  GLdouble y, GLdouble z,
                                                  GLdouble w) const
{
    static const char *fnName = "glProgramEnvParameter4dARB";

    beforeCommand(fnName, _api.glProgramEnvParameter4d);
    _api.glProgramEnvParameter4d(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramEnvParameter4dvARB().
void ARBFragmentProgramAPI::programEnvParameter4DV(ProgramTarget target,
                                                   GLuint index,
                                                   const GLdouble *params) const
{
    static const char *fnName = "glProgramEnvParameter4dvARB";

    beforeCommand(fnName, _api.glProgramEnvParameter4dv);
    _api.glProgramEnvParameter4dv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramEnvParameter4fARB().
void ARBFragmentProgramAPI::programEnvParameter4F(ProgramTarget target,
                                                  GLuint index, GLfloat x,
                                                  GLfloat y, GLfloat z,
                                                  GLfloat w) const
{
    static const char *fnName = "glProgramEnvParameter4fARB";

    beforeCommand(fnName, _api.glProgramEnvParameter4f);
    _api.glProgramEnvParameter4f(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramEnvParameter4fvARB().
void ARBFragmentProgramAPI::programEnvParameter4FV(ProgramTarget target,
                                                   GLuint index,
                                                   const GLfloat *params) const
{
    static const char *fnName = "glProgramEnvParameter4fvARB";

    beforeCommand(fnName, _api.glProgramEnvParameter4fv);
    _api.glProgramEnvParameter4fv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParameter4dARB().
void ARBFragmentProgramAPI::programLocalParameter4D(ProgramTarget target,
                                                    GLuint index, GLdouble x,
                                                    GLdouble y, GLdouble z,
                                                    GLdouble w) const
{
    static const char *fnName = "glProgramLocalParameter4dARB";

    beforeCommand(fnName, _api.glProgramLocalParameter4d);
    _api.glProgramLocalParameter4d(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramLocalParameter4dvARB().
void ARBFragmentProgramAPI::programLocalParameter4DV(ProgramTarget target,
                                                     GLuint index,
                                                     const GLdouble *params) const
{
    static const char *fnName = "glProgramLocalParameter4dvARB";

    beforeCommand(fnName, _api.glProgramLocalParameter4dv);
    _api.glProgramLocalParameter4dv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParameter4fARB().
void ARBFragmentProgramAPI::programLocalParameter4F(ProgramTarget target,
                                                    GLuint index, GLfloat x,
                                                    GLfloat y, GLfloat z,
                                                    GLfloat w) const
{
    static const char *fnName = "glProgramLocalParameter4fARB";

    beforeCommand(fnName, _api.glProgramLocalParameter4f);
    _api.glProgramLocalParameter4f(toScalar(target), index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramLocalParameter4fvARB().
void ARBFragmentProgramAPI::programLocalParameter4FV(ProgramTarget target,
                                                     GLuint index,
                                                     const GLfloat *params) const
{
    static const char *fnName = "glProgramLocalParameter4fvARB";

    beforeCommand(fnName, _api.glProgramLocalParameter4fv);
    _api.glProgramLocalParameter4fv(toScalar(target), index, params);
    afterCommand(fnName);
}

// Calls glProgramStringARB().
void ARBFragmentProgramAPI::programString(ProgramTarget target,
                                          ProgramFormat format, GLsizei len,
                                          const void *string) const
{
    static const char *fnName = "glProgramStringARB";

    beforeCommand(fnName, _api.glProgramString);
    _api.glProgramString(toScalar(target), toScalar(format), len, string);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBGeometrySHADER4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_geometry_shader4 extension.
ARBGeometrySHADER4API::ARBGeometrySHADER4API() :
    BaseExtension("GL_ARB_geometry_shader4")
{
}

// Grant read-only access to the underlying function pointers.
const ARBGeometrySHADER4 &ARBGeometrySHADER4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_geometry_shader4 entry points.
void ARBGeometrySHADER4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferTextureARB().
void ARBGeometrySHADER4API::framebufferTexture(FramebufferTarget target,
                                               FramebufferAttachment attachment,
                                               TextureName texture, GLint level) const
{
    static const char *fnName = "glFramebufferTextureARB";

    beforeCommand(fnName, _api.glFramebufferTexture);
    _api.glFramebufferTexture(toScalar(target), toScalar(attachment), texture.ID,
                              level);
    afterCommand(fnName);
}

// Calls glFramebufferTextureFaceARB().
void ARBGeometrySHADER4API::framebufferTextureFace(FramebufferTarget target,
                                                   FramebufferAttachment attachment,
                                                   TextureName texture,
                                                   GLint level,
                                                   TextureTarget face) const
{
    static const char *fnName = "glFramebufferTextureFaceARB";

    beforeCommand(fnName, _api.glFramebufferTextureFace);
    _api.glFramebufferTextureFace(toScalar(target), toScalar(attachment),
                                  texture.ID, level, toScalar(face));
    afterCommand(fnName);
}

// Calls glFramebufferTextureLayerARB().
void ARBGeometrySHADER4API::framebufferTextureLayer(FramebufferTarget target,
                                                    FramebufferAttachment attachment,
                                                    TextureName texture,
                                                    GLint level, GLint layer) const
{
    static const char *fnName = "glFramebufferTextureLayerARB";

    beforeCommand(fnName, _api.glFramebufferTextureLayer);
    _api.glFramebufferTextureLayer(toScalar(target), toScalar(attachment),
                                   texture.ID, level, layer);
    afterCommand(fnName);
}

// Calls glProgramParameteriARB().
void ARBGeometrySHADER4API::programParameterI(ProgramName program,
                                              ProgramParameterPName pname,
                                              GLint value) const
{
    static const char *fnName = "glProgramParameteriARB";

    beforeCommand(fnName, _api.glProgramParameteri);
    _api.glProgramParameteri(program.ID, toScalar(pname), value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBGlSpirvAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_gl_spirv extension.
ARBGlSpirvAPI::ARBGlSpirvAPI() :
    BaseExtension("GL_ARB_gl_spirv")
{
}

// Grant read-only access to the underlying function pointers.
const ARBGlSpirv &ARBGlSpirvAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_gl_spirv entry points.
void ARBGlSpirvAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSpecializeShaderARB().
void ARBGlSpirvAPI::specializeShader(ShaderName shader,
                                     const GLchar *pEntryPoint,
                                     GLuint numSpecializationConstants,
                                     const GLuint *pConstantIndex,
                                     const GLuint *pConstantValue) const
{
    static const char *fnName = "glSpecializeShaderARB";

    beforeCommand(fnName, _api.glSpecializeShader);
    _api.glSpecializeShader(shader.ID, pEntryPoint, numSpecializationConstants,
                            pConstantIndex, pConstantValue);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBGPUShaderInt64API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_gpu_shader_int64 extension.
ARBGPUShaderInt64API::ARBGPUShaderInt64API() :
    BaseExtension("GL_ARB_gpu_shader_int64")
{
}

// Grant read-only access to the underlying function pointers.
const ARBGPUShaderInt64 &ARBGPUShaderInt64API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_gpu_shader_int64 entry points.
void ARBGPUShaderInt64API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetUniformi64vARB().
void ARBGPUShaderInt64API::getUniformI64V(ProgramName program, GLint location,
                                          GLint64 *params) const
{
    static const char *fnName = "glGetUniformi64vARB";

    beforeCommand(fnName, _api.glGetUniformi64v);
    _api.glGetUniformi64v(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetUniformui64vARB().
void ARBGPUShaderInt64API::getUniformUI64(ProgramName program, GLint location,
                                          GLuint64 *params) const
{
    static const char *fnName = "glGetUniformui64vARB";

    beforeCommand(fnName, _api.glGetUniformui64v);
    _api.glGetUniformui64v(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetnUniformi64vARB().
void ARBGPUShaderInt64API::getnUniformI64V(ProgramName program, GLint location,
                                           GLsizei bufSize, GLint64 *params) const
{
    static const char *fnName = "glGetnUniformi64vARB";

    beforeCommand(fnName, _api.glGetnUniformi64v);
    _api.glGetnUniformi64v(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformui64vARB().
void ARBGPUShaderInt64API::getnUniformUI64(ProgramName program, GLint location,
                                           GLsizei bufSize, GLuint64 *params) const
{
    static const char *fnName = "glGetnUniformui64vARB";

    beforeCommand(fnName, _api.glGetnUniformui64v);
    _api.glGetnUniformui64v(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glProgramUniform1i64ARB().
void ARBGPUShaderInt64API::programUniform1I64(ProgramName program,
                                              GLint location, GLint64 x) const
{
    static const char *fnName = "glProgramUniform1i64ARB";

    beforeCommand(fnName, _api.glProgramUniform1i64);
    _api.glProgramUniform1i64(program.ID, location, x);
    afterCommand(fnName);
}

// Calls glProgramUniform1i64vARB().
void ARBGPUShaderInt64API::programUniform1I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64 *value) const
{
    static const char *fnName = "glProgramUniform1i64vARB";

    beforeCommand(fnName, _api.glProgramUniform1i64v);
    _api.glProgramUniform1i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1ui64ARB().
void ARBGPUShaderInt64API::programUniform1UI64(ProgramName program,
                                               GLint location, GLuint64 x) const
{
    static const char *fnName = "glProgramUniform1ui64ARB";

    beforeCommand(fnName, _api.glProgramUniform1ui64);
    _api.glProgramUniform1ui64(program.ID, location, x);
    afterCommand(fnName);
}

// Calls glProgramUniform1ui64vARB().
void ARBGPUShaderInt64API::programUniform1UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64 *value) const
{
    static const char *fnName = "glProgramUniform1ui64vARB";

    beforeCommand(fnName, _api.glProgramUniform1ui64v);
    _api.glProgramUniform1ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2i64ARB().
void ARBGPUShaderInt64API::programUniform2I64(ProgramName program,
                                              GLint location, GLint64 x,
                                              GLint64 y) const
{
    static const char *fnName = "glProgramUniform2i64ARB";

    beforeCommand(fnName, _api.glProgramUniform2i64);
    _api.glProgramUniform2i64(program.ID, location, x, y);
    afterCommand(fnName);
}

// Calls glProgramUniform2i64vARB().
void ARBGPUShaderInt64API::programUniform2I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64 *value) const
{
    static const char *fnName = "glProgramUniform2i64vARB";

    beforeCommand(fnName, _api.glProgramUniform2i64v);
    _api.glProgramUniform2i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2ui64ARB().
void ARBGPUShaderInt64API::programUniform2UI64(ProgramName program,
                                               GLint location, GLuint64 x,
                                               GLuint64 y) const
{
    static const char *fnName = "glProgramUniform2ui64ARB";

    beforeCommand(fnName, _api.glProgramUniform2ui64);
    _api.glProgramUniform2ui64(program.ID, location, x, y);
    afterCommand(fnName);
}

// Calls glProgramUniform2ui64vARB().
void ARBGPUShaderInt64API::programUniform2UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64 *value) const
{
    static const char *fnName = "glProgramUniform2ui64vARB";

    beforeCommand(fnName, _api.glProgramUniform2ui64v);
    _api.glProgramUniform2ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3i64ARB().
void ARBGPUShaderInt64API::programUniform3I64(ProgramName program,
                                              GLint location, GLint64 x,
                                              GLint64 y, GLint64 z) const
{
    static const char *fnName = "glProgramUniform3i64ARB";

    beforeCommand(fnName, _api.glProgramUniform3i64);
    _api.glProgramUniform3i64(program.ID, location, x, y, z);
    afterCommand(fnName);
}

// Calls glProgramUniform3i64vARB().
void ARBGPUShaderInt64API::programUniform3I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64 *value) const
{
    static const char *fnName = "glProgramUniform3i64vARB";

    beforeCommand(fnName, _api.glProgramUniform3i64v);
    _api.glProgramUniform3i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3ui64ARB().
void ARBGPUShaderInt64API::programUniform3UI64(ProgramName program,
                                               GLint location, GLuint64 x,
                                               GLuint64 y, GLuint64 z) const
{
    static const char *fnName = "glProgramUniform3ui64ARB";

    beforeCommand(fnName, _api.glProgramUniform3ui64);
    _api.glProgramUniform3ui64(program.ID, location, x, y, z);
    afterCommand(fnName);
}

// Calls glProgramUniform3ui64vARB().
void ARBGPUShaderInt64API::programUniform3UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64 *value) const
{
    static const char *fnName = "glProgramUniform3ui64vARB";

    beforeCommand(fnName, _api.glProgramUniform3ui64v);
    _api.glProgramUniform3ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4i64ARB().
void ARBGPUShaderInt64API::programUniform4I64(ProgramName program,
                                              GLint location, GLint64 x,
                                              GLint64 y, GLint64 z, GLint64 w) const
{
    static const char *fnName = "glProgramUniform4i64ARB";

    beforeCommand(fnName, _api.glProgramUniform4i64);
    _api.glProgramUniform4i64(program.ID, location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramUniform4i64vARB().
void ARBGPUShaderInt64API::programUniform4I64V(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLint64 *value) const
{
    static const char *fnName = "glProgramUniform4i64vARB";

    beforeCommand(fnName, _api.glProgramUniform4i64v);
    _api.glProgramUniform4i64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4ui64ARB().
void ARBGPUShaderInt64API::programUniform4UI64(ProgramName program,
                                               GLint location, GLuint64 x,
                                               GLuint64 y, GLuint64 z,
                                               GLuint64 w) const
{
    static const char *fnName = "glProgramUniform4ui64ARB";

    beforeCommand(fnName, _api.glProgramUniform4ui64);
    _api.glProgramUniform4ui64(program.ID, location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramUniform4ui64vARB().
void ARBGPUShaderInt64API::programUniform4UI64(ProgramName program,
                                               GLint location, GLsizei count,
                                               const GLuint64 *value) const
{
    static const char *fnName = "glProgramUniform4ui64vARB";

    beforeCommand(fnName, _api.glProgramUniform4ui64v);
    _api.glProgramUniform4ui64v(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1i64ARB().
void ARBGPUShaderInt64API::uniform1I64(GLint location, GLint64 x) const
{
    static const char *fnName = "glUniform1i64ARB";

    beforeCommand(fnName, _api.glUniform1i64);
    _api.glUniform1i64(location, x);
    afterCommand(fnName);
}

// Calls glUniform1i64vARB().
void ARBGPUShaderInt64API::uniform1I64V(GLint location, GLsizei count,
                                        const GLint64 *value) const
{
    static const char *fnName = "glUniform1i64vARB";

    beforeCommand(fnName, _api.glUniform1i64v);
    _api.glUniform1i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1ui64ARB().
void ARBGPUShaderInt64API::uniform1UI64(GLint location, GLuint64 x) const
{
    static const char *fnName = "glUniform1ui64ARB";

    beforeCommand(fnName, _api.glUniform1ui64);
    _api.glUniform1ui64(location, x);
    afterCommand(fnName);
}

// Calls glUniform1ui64vARB().
void ARBGPUShaderInt64API::uniform1UI64(GLint location, GLsizei count,
                                        const GLuint64 *value) const
{
    static const char *fnName = "glUniform1ui64vARB";

    beforeCommand(fnName, _api.glUniform1ui64v);
    _api.glUniform1ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2i64ARB().
void ARBGPUShaderInt64API::uniform2I64(GLint location, GLint64 x, GLint64 y) const
{
    static const char *fnName = "glUniform2i64ARB";

    beforeCommand(fnName, _api.glUniform2i64);
    _api.glUniform2i64(location, x, y);
    afterCommand(fnName);
}

// Calls glUniform2i64vARB().
void ARBGPUShaderInt64API::uniform2I64V(GLint location, GLsizei count,
                                        const GLint64 *value) const
{
    static const char *fnName = "glUniform2i64vARB";

    beforeCommand(fnName, _api.glUniform2i64v);
    _api.glUniform2i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2ui64ARB().
void ARBGPUShaderInt64API::uniform2UI64(GLint location, GLuint64 x, GLuint64 y) const
{
    static const char *fnName = "glUniform2ui64ARB";

    beforeCommand(fnName, _api.glUniform2ui64);
    _api.glUniform2ui64(location, x, y);
    afterCommand(fnName);
}

// Calls glUniform2ui64vARB().
void ARBGPUShaderInt64API::uniform2UI64(GLint location, GLsizei count,
                                        const GLuint64 *value) const
{
    static const char *fnName = "glUniform2ui64vARB";

    beforeCommand(fnName, _api.glUniform2ui64v);
    _api.glUniform2ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3i64ARB().
void ARBGPUShaderInt64API::uniform3I64(GLint location, GLint64 x, GLint64 y,
                                       GLint64 z) const
{
    static const char *fnName = "glUniform3i64ARB";

    beforeCommand(fnName, _api.glUniform3i64);
    _api.glUniform3i64(location, x, y, z);
    afterCommand(fnName);
}

// Calls glUniform3i64vARB().
void ARBGPUShaderInt64API::uniform3I64V(GLint location, GLsizei count,
                                        const GLint64 *value) const
{
    static const char *fnName = "glUniform3i64vARB";

    beforeCommand(fnName, _api.glUniform3i64v);
    _api.glUniform3i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3ui64ARB().
void ARBGPUShaderInt64API::uniform3UI64(GLint location, GLuint64 x, GLuint64 y,
                                        GLuint64 z) const
{
    static const char *fnName = "glUniform3ui64ARB";

    beforeCommand(fnName, _api.glUniform3ui64);
    _api.glUniform3ui64(location, x, y, z);
    afterCommand(fnName);
}

// Calls glUniform3ui64vARB().
void ARBGPUShaderInt64API::uniform3UI64(GLint location, GLsizei count,
                                        const GLuint64 *value) const
{
    static const char *fnName = "glUniform3ui64vARB";

    beforeCommand(fnName, _api.glUniform3ui64v);
    _api.glUniform3ui64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4i64ARB().
void ARBGPUShaderInt64API::uniform4I64(GLint location, GLint64 x, GLint64 y,
                                       GLint64 z, GLint64 w) const
{
    static const char *fnName = "glUniform4i64ARB";

    beforeCommand(fnName, _api.glUniform4i64);
    _api.glUniform4i64(location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glUniform4i64vARB().
void ARBGPUShaderInt64API::uniform4I64V(GLint location, GLsizei count,
                                        const GLint64 *value) const
{
    static const char *fnName = "glUniform4i64vARB";

    beforeCommand(fnName, _api.glUniform4i64v);
    _api.glUniform4i64v(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4ui64ARB().
void ARBGPUShaderInt64API::uniform4UI64(GLint location, GLuint64 x, GLuint64 y,
                                        GLuint64 z, GLuint64 w) const
{
    static const char *fnName = "glUniform4ui64ARB";

    beforeCommand(fnName, _api.glUniform4ui64);
    _api.glUniform4ui64(location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glUniform4ui64vARB().
void ARBGPUShaderInt64API::uniform4UI64(GLint location, GLsizei count,
                                        const GLuint64 *value) const
{
    static const char *fnName = "glUniform4ui64vARB";

    beforeCommand(fnName, _api.glUniform4ui64v);
    _api.glUniform4ui64v(location, count, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBIndirectParametersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_indirect_parameters extension.
ARBIndirectParametersAPI::ARBIndirectParametersAPI() :
    BaseExtension("GL_ARB_indirect_parameters")
{
}

// Grant read-only access to the underlying function pointers.
const ARBIndirectParameters &ARBIndirectParametersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_indirect_parameters entry points.
void ARBIndirectParametersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiDrawArraysIndirectCountARB().
void ARBIndirectParametersAPI::multiDrawArraysIndirectCount(PrimitiveType mode,
                                                            const void *indirect,
                                                            GLintptr drawcount,
                                                            GLsizei maxdrawcount,
                                                            GLsizei stride) const
{
    static const char *fnName = "glMultiDrawArraysIndirectCountARB";

    beforeCommand(fnName, _api.glMultiDrawArraysIndirectCount);
    _api.glMultiDrawArraysIndirectCount(toScalar(mode), indirect, drawcount,
                                        maxdrawcount, stride);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsIndirectCountARB().
void ARBIndirectParametersAPI::multiDrawElementsIndirectCount(PrimitiveType mode,
                                                              DrawElementsType type,
                                                              const void *indirect,
                                                              GLintptr drawcount,
                                                              GLsizei maxdrawcount,
                                                              GLsizei stride) const
{
    static const char *fnName = "glMultiDrawElementsIndirectCountARB";

    beforeCommand(fnName, _api.glMultiDrawElementsIndirectCount);
    _api.glMultiDrawElementsIndirectCount(toScalar(mode), toScalar(type),
                                          indirect, drawcount, maxdrawcount,
                                          stride);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBInstancedArraysAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_instanced_arrays extension.
ARBInstancedArraysAPI::ARBInstancedArraysAPI() :
    BaseExtension("GL_ARB_instanced_arrays")
{
}

// Grant read-only access to the underlying function pointers.
const ARBInstancedArrays &ARBInstancedArraysAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_instanced_arrays entry points.
void ARBInstancedArraysAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVertexAttribDivisorARB().
void ARBInstancedArraysAPI::vertexAttribDivisor(GLuint index, GLuint divisor) const
{
    static const char *fnName = "glVertexAttribDivisorARB";

    beforeCommand(fnName, _api.glVertexAttribDivisor);
    _api.glVertexAttribDivisor(index, divisor);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBMatrixPaletteAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_matrix_palette extension.
ARBMatrixPaletteAPI::ARBMatrixPaletteAPI() :
    BaseExtension("GL_ARB_matrix_palette")
{
}

// Grant read-only access to the underlying function pointers.
const ARBMatrixPalette &ARBMatrixPaletteAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_matrix_palette entry points.
void ARBMatrixPaletteAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCurrentPaletteMatrixARB().
void ARBMatrixPaletteAPI::currentPaletteMatrix(GLint index) const
{
    static const char *fnName = "glCurrentPaletteMatrixARB";

    beforeCommand(fnName, _api.glCurrentPaletteMatrix);
    _api.glCurrentPaletteMatrix(index);
    afterCommand(fnName);
}

// Calls glMatrixIndexPointerARB().
void ARBMatrixPaletteAPI::matrixIndexPointer(GLint size,
                                             MatrixIndexPointerTypeARB type,
                                             GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glMatrixIndexPointerARB";

    beforeCommand(fnName, _api.glMatrixIndexPointer);
    _api.glMatrixIndexPointer(size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glMatrixIndexubvARB().
void ARBMatrixPaletteAPI::matrixIndexUBV(GLint size, const GLubyte *indices) const
{
    static const char *fnName = "glMatrixIndexubvARB";

    beforeCommand(fnName, _api.glMatrixIndexubv);
    _api.glMatrixIndexubv(size, indices);
    afterCommand(fnName);
}

// Calls glMatrixIndexuivARB().
void ARBMatrixPaletteAPI::matrixIndexUIV(GLint size, const GLuint *indices) const
{
    static const char *fnName = "glMatrixIndexuivARB";

    beforeCommand(fnName, _api.glMatrixIndexuiv);
    _api.glMatrixIndexuiv(size, indices);
    afterCommand(fnName);
}

// Calls glMatrixIndexusvARB().
void ARBMatrixPaletteAPI::matrixIndexUSV(GLint size, const GLushort *indices) const
{
    static const char *fnName = "glMatrixIndexusvARB";

    beforeCommand(fnName, _api.glMatrixIndexusv);
    _api.glMatrixIndexusv(size, indices);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_multisample extension.
ARBMultisampleAPI::ARBMultisampleAPI() :
    BaseExtension("GL_ARB_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const ARBMultisample &ARBMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_multisample entry points.
void ARBMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSampleCoverageARB().
void ARBMultisampleAPI::sampleCoverage(GLfloat value, Boolean invert) const
{
    static const char *fnName = "glSampleCoverageARB";

    beforeCommand(fnName, _api.glSampleCoverage);
    _api.glSampleCoverage(value, toScalar(invert));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBMultitextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_multitexture extension.
ARBMultitextureAPI::ARBMultitextureAPI() :
    BaseExtension("GL_ARB_multitexture")
{
}

// Grant read-only access to the underlying function pointers.
const ARBMultitexture &ARBMultitextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_multitexture entry points.
void ARBMultitextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glActiveTextureARB().
void ARBMultitextureAPI::activeTexture(TextureUnit texture) const
{
    static const char *fnName = "glActiveTextureARB";

    beforeCommand(fnName, _api.glActiveTexture);
    _api.glActiveTexture(toScalar(texture));
    afterCommand(fnName);
}

// Calls glClientActiveTextureARB().
void ARBMultitextureAPI::clientActiveTexture(TextureUnit texture) const
{
    static const char *fnName = "glClientActiveTextureARB";

    beforeCommand(fnName, _api.glClientActiveTexture);
    _api.glClientActiveTexture(toScalar(texture));
    afterCommand(fnName);
}

// Calls glMultiTexCoord1dARB().
void ARBMultitextureAPI::multiTexCoord1D(TextureUnit target, GLdouble s) const
{
    static const char *fnName = "glMultiTexCoord1dARB";

    beforeCommand(fnName, _api.glMultiTexCoord1d);
    _api.glMultiTexCoord1d(toScalar(target), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1dvARB().
void ARBMultitextureAPI::multiTexCoord1DV(TextureUnit target, const GLdouble *v) const
{
    static const char *fnName = "glMultiTexCoord1dvARB";

    beforeCommand(fnName, _api.glMultiTexCoord1dv);
    _api.glMultiTexCoord1dv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1fARB().
void ARBMultitextureAPI::multiTexCoord1F(TextureUnit target, GLfloat s) const
{
    static const char *fnName = "glMultiTexCoord1fARB";

    beforeCommand(fnName, _api.glMultiTexCoord1f);
    _api.glMultiTexCoord1f(toScalar(target), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1fvARB().
void ARBMultitextureAPI::multiTexCoord1FV(TextureUnit target, const GLfloat *v) const
{
    static const char *fnName = "glMultiTexCoord1fvARB";

    beforeCommand(fnName, _api.glMultiTexCoord1fv);
    _api.glMultiTexCoord1fv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1iARB().
void ARBMultitextureAPI::multiTexCoord1I(TextureUnit target, GLint s) const
{
    static const char *fnName = "glMultiTexCoord1iARB";

    beforeCommand(fnName, _api.glMultiTexCoord1i);
    _api.glMultiTexCoord1i(toScalar(target), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1ivARB().
void ARBMultitextureAPI::multiTexCoord1IV(TextureUnit target, const GLint *v) const
{
    static const char *fnName = "glMultiTexCoord1ivARB";

    beforeCommand(fnName, _api.glMultiTexCoord1iv);
    _api.glMultiTexCoord1iv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1sARB().
void ARBMultitextureAPI::multiTexCoord1S(TextureUnit target, GLshort s) const
{
    static const char *fnName = "glMultiTexCoord1sARB";

    beforeCommand(fnName, _api.glMultiTexCoord1s);
    _api.glMultiTexCoord1s(toScalar(target), s);
    afterCommand(fnName);
}

// Calls glMultiTexCoord1svARB().
void ARBMultitextureAPI::multiTexCoord1SV(TextureUnit target, const GLshort *v) const
{
    static const char *fnName = "glMultiTexCoord1svARB";

    beforeCommand(fnName, _api.glMultiTexCoord1sv);
    _api.glMultiTexCoord1sv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2dARB().
void ARBMultitextureAPI::multiTexCoord2D(TextureUnit target, GLdouble s,
                                         GLdouble t) const
{
    static const char *fnName = "glMultiTexCoord2dARB";

    beforeCommand(fnName, _api.glMultiTexCoord2d);
    _api.glMultiTexCoord2d(toScalar(target), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2dvARB().
void ARBMultitextureAPI::multiTexCoord2DV(TextureUnit target, const GLdouble *v) const
{
    static const char *fnName = "glMultiTexCoord2dvARB";

    beforeCommand(fnName, _api.glMultiTexCoord2dv);
    _api.glMultiTexCoord2dv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2fARB().
void ARBMultitextureAPI::multiTexCoord2F(TextureUnit target, GLfloat s,
                                         GLfloat t) const
{
    static const char *fnName = "glMultiTexCoord2fARB";

    beforeCommand(fnName, _api.glMultiTexCoord2f);
    _api.glMultiTexCoord2f(toScalar(target), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2fvARB().
void ARBMultitextureAPI::multiTexCoord2FV(TextureUnit target, const GLfloat *v) const
{
    static const char *fnName = "glMultiTexCoord2fvARB";

    beforeCommand(fnName, _api.glMultiTexCoord2fv);
    _api.glMultiTexCoord2fv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2iARB().
void ARBMultitextureAPI::multiTexCoord2I(TextureUnit target, GLint s, GLint t) const
{
    static const char *fnName = "glMultiTexCoord2iARB";

    beforeCommand(fnName, _api.glMultiTexCoord2i);
    _api.glMultiTexCoord2i(toScalar(target), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2ivARB().
void ARBMultitextureAPI::multiTexCoord2IV(TextureUnit target, const GLint *v) const
{
    static const char *fnName = "glMultiTexCoord2ivARB";

    beforeCommand(fnName, _api.glMultiTexCoord2iv);
    _api.glMultiTexCoord2iv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2sARB().
void ARBMultitextureAPI::multiTexCoord2S(TextureUnit target, GLshort s,
                                         GLshort t) const
{
    static const char *fnName = "glMultiTexCoord2sARB";

    beforeCommand(fnName, _api.glMultiTexCoord2s);
    _api.glMultiTexCoord2s(toScalar(target), s, t);
    afterCommand(fnName);
}

// Calls glMultiTexCoord2svARB().
void ARBMultitextureAPI::multiTexCoord2SV(TextureUnit target, const GLshort *v) const
{
    static const char *fnName = "glMultiTexCoord2svARB";

    beforeCommand(fnName, _api.glMultiTexCoord2sv);
    _api.glMultiTexCoord2sv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3dARB().
void ARBMultitextureAPI::multiTexCoord3D(TextureUnit target, GLdouble s,
                                         GLdouble t, GLdouble r) const
{
    static const char *fnName = "glMultiTexCoord3dARB";

    beforeCommand(fnName, _api.glMultiTexCoord3d);
    _api.glMultiTexCoord3d(toScalar(target), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3dvARB().
void ARBMultitextureAPI::multiTexCoord3DV(TextureUnit target, const GLdouble *v) const
{
    static const char *fnName = "glMultiTexCoord3dvARB";

    beforeCommand(fnName, _api.glMultiTexCoord3dv);
    _api.glMultiTexCoord3dv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3fARB().
void ARBMultitextureAPI::multiTexCoord3F(TextureUnit target, GLfloat s,
                                         GLfloat t, GLfloat r) const
{
    static const char *fnName = "glMultiTexCoord3fARB";

    beforeCommand(fnName, _api.glMultiTexCoord3f);
    _api.glMultiTexCoord3f(toScalar(target), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3fvARB().
void ARBMultitextureAPI::multiTexCoord3FV(TextureUnit target, const GLfloat *v) const
{
    static const char *fnName = "glMultiTexCoord3fvARB";

    beforeCommand(fnName, _api.glMultiTexCoord3fv);
    _api.glMultiTexCoord3fv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3iARB().
void ARBMultitextureAPI::multiTexCoord3I(TextureUnit target, GLint s, GLint t,
                                         GLint r) const
{
    static const char *fnName = "glMultiTexCoord3iARB";

    beforeCommand(fnName, _api.glMultiTexCoord3i);
    _api.glMultiTexCoord3i(toScalar(target), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3ivARB().
void ARBMultitextureAPI::multiTexCoord3IV(TextureUnit target, const GLint *v) const
{
    static const char *fnName = "glMultiTexCoord3ivARB";

    beforeCommand(fnName, _api.glMultiTexCoord3iv);
    _api.glMultiTexCoord3iv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3sARB().
void ARBMultitextureAPI::multiTexCoord3S(TextureUnit target, GLshort s,
                                         GLshort t, GLshort r) const
{
    static const char *fnName = "glMultiTexCoord3sARB";

    beforeCommand(fnName, _api.glMultiTexCoord3s);
    _api.glMultiTexCoord3s(toScalar(target), s, t, r);
    afterCommand(fnName);
}

// Calls glMultiTexCoord3svARB().
void ARBMultitextureAPI::multiTexCoord3SV(TextureUnit target, const GLshort *v) const
{
    static const char *fnName = "glMultiTexCoord3svARB";

    beforeCommand(fnName, _api.glMultiTexCoord3sv);
    _api.glMultiTexCoord3sv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4dARB().
void ARBMultitextureAPI::multiTexCoord4D(TextureUnit target, GLdouble s,
                                         GLdouble t, GLdouble r, GLdouble q) const
{
    static const char *fnName = "glMultiTexCoord4dARB";

    beforeCommand(fnName, _api.glMultiTexCoord4d);
    _api.glMultiTexCoord4d(toScalar(target), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4dvARB().
void ARBMultitextureAPI::multiTexCoord4DV(TextureUnit target, const GLdouble *v) const
{
    static const char *fnName = "glMultiTexCoord4dvARB";

    beforeCommand(fnName, _api.glMultiTexCoord4dv);
    _api.glMultiTexCoord4dv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4fARB().
void ARBMultitextureAPI::multiTexCoord4F(TextureUnit target, GLfloat s,
                                         GLfloat t, GLfloat r, GLfloat q) const
{
    static const char *fnName = "glMultiTexCoord4fARB";

    beforeCommand(fnName, _api.glMultiTexCoord4f);
    _api.glMultiTexCoord4f(toScalar(target), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4fvARB().
void ARBMultitextureAPI::multiTexCoord4FV(TextureUnit target, const GLfloat *v) const
{
    static const char *fnName = "glMultiTexCoord4fvARB";

    beforeCommand(fnName, _api.glMultiTexCoord4fv);
    _api.glMultiTexCoord4fv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4iARB().
void ARBMultitextureAPI::multiTexCoord4I(TextureUnit target, GLint s, GLint t,
                                         GLint r, GLint q) const
{
    static const char *fnName = "glMultiTexCoord4iARB";

    beforeCommand(fnName, _api.glMultiTexCoord4i);
    _api.glMultiTexCoord4i(toScalar(target), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4ivARB().
void ARBMultitextureAPI::multiTexCoord4IV(TextureUnit target, const GLint *v) const
{
    static const char *fnName = "glMultiTexCoord4ivARB";

    beforeCommand(fnName, _api.glMultiTexCoord4iv);
    _api.glMultiTexCoord4iv(toScalar(target), v);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4sARB().
void ARBMultitextureAPI::multiTexCoord4S(TextureUnit target, GLshort s,
                                         GLshort t, GLshort r, GLshort q) const
{
    static const char *fnName = "glMultiTexCoord4sARB";

    beforeCommand(fnName, _api.glMultiTexCoord4s);
    _api.glMultiTexCoord4s(toScalar(target), s, t, r, q);
    afterCommand(fnName);
}

// Calls glMultiTexCoord4svARB().
void ARBMultitextureAPI::multiTexCoord4SV(TextureUnit target, const GLshort *v) const
{
    static const char *fnName = "glMultiTexCoord4svARB";

    beforeCommand(fnName, _api.glMultiTexCoord4sv);
    _api.glMultiTexCoord4sv(toScalar(target), v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBOcclusionQueryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_occlusion_query extension.
ARBOcclusionQueryAPI::ARBOcclusionQueryAPI() :
    BaseExtension("GL_ARB_occlusion_query")
{
}

// Grant read-only access to the underlying function pointers.
const ARBOcclusionQuery &ARBOcclusionQueryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_occlusion_query entry points.
void ARBOcclusionQueryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginQueryARB().
void ARBOcclusionQueryAPI::beginQuery(QueryTarget target, QueryName id) const
{
    static const char *fnName = "glBeginQueryARB";

    beforeCommand(fnName, _api.glBeginQuery);
    _api.glBeginQuery(toScalar(target), id.ID);
    afterCommand(fnName);
}

// Calls glDeleteQueriesARB().
void ARBOcclusionQueryAPI::deleteQueries(GLsizei n, const QueryName *ids) const
{
    static const char *fnName = "glDeleteQueriesARB";

    beforeCommand(fnName, _api.glDeleteQueries);
    _api.glDeleteQueries(n, reinterpret_cast<const GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glEndQueryARB().
void ARBOcclusionQueryAPI::endQuery(QueryTarget target) const
{
    static const char *fnName = "glEndQueryARB";

    beforeCommand(fnName, _api.glEndQuery);
    _api.glEndQuery(toScalar(target));
    afterCommand(fnName);
}

// Calls glGenQueriesARB().
void ARBOcclusionQueryAPI::genQueries(GLsizei n, QueryName *ids) const
{
    static const char *fnName = "glGenQueriesARB";

    beforeCommand(fnName, _api.glGenQueries);
    _api.glGenQueries(n, reinterpret_cast<GLuint *>(ids));
    afterCommand(fnName);
}

// Calls glGetQueryObjectivARB().
void ARBOcclusionQueryAPI::getQueryObjectIV(QueryName id,
                                            QueryObjectParameterName pname,
                                            GLint *params) const
{
    static const char *fnName = "glGetQueryObjectivARB";

    beforeCommand(fnName, _api.glGetQueryObjectiv);
    _api.glGetQueryObjectiv(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryObjectuivARB().
void ARBOcclusionQueryAPI::getQueryObjectUIV(QueryName id,
                                             QueryObjectParameterName pname,
                                             GLuint *params) const
{
    static const char *fnName = "glGetQueryObjectuivARB";

    beforeCommand(fnName, _api.glGetQueryObjectuiv);
    _api.glGetQueryObjectuiv(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryivARB().
void ARBOcclusionQueryAPI::getQueryIV(QueryTarget target,
                                      QueryParameterName pname, GLint *params) const
{
    static const char *fnName = "glGetQueryivARB";

    beforeCommand(fnName, _api.glGetQueryiv);
    _api.glGetQueryiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsQueryARB().
Boolean ARBOcclusionQueryAPI::isQuery(QueryName id) const
{
    static const char *fnName = "glIsQueryARB";

    beforeCommand(fnName, _api.glIsQuery);
    GLboolean result = _api.glIsQuery(id.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// ARBParallelShaderCompileAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_parallel_shader_compile extension.
ARBParallelShaderCompileAPI::ARBParallelShaderCompileAPI() :
    BaseExtension("GL_ARB_parallel_shader_compile")
{
}

// Grant read-only access to the underlying function pointers.
const ARBParallelShaderCompile &ARBParallelShaderCompileAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_parallel_shader_compile entry points.
void ARBParallelShaderCompileAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMaxShaderCompilerThreadsARB().
void ARBParallelShaderCompileAPI::maxShaderCompilerThreads(GLuint count) const
{
    static const char *fnName = "glMaxShaderCompilerThreadsARB";

    beforeCommand(fnName, _api.glMaxShaderCompilerThreads);
    _api.glMaxShaderCompilerThreads(count);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBPointParametersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_point_parameters extension.
ARBPointParametersAPI::ARBPointParametersAPI() :
    BaseExtension("GL_ARB_point_parameters")
{
}

// Grant read-only access to the underlying function pointers.
const ARBPointParameters &ARBPointParametersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_point_parameters entry points.
void ARBPointParametersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPointParameterfARB().
void ARBPointParametersAPI::pointParameterF(PointParameterNameARB pname,
                                            GLfloat param) const
{
    static const char *fnName = "glPointParameterfARB";

    beforeCommand(fnName, _api.glPointParameterf);
    _api.glPointParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameterfvARB().
void ARBPointParametersAPI::pointParameterFV(PointParameterNameARB pname,
                                             const GLfloat *params) const
{
    static const char *fnName = "glPointParameterfvARB";

    beforeCommand(fnName, _api.glPointParameterfv);
    _api.glPointParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBRobustnessAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_robustness extension.
ARBRobustnessAPI::ARBRobustnessAPI() :
    BaseExtension("GL_ARB_robustness")
{
}

// Grant read-only access to the underlying function pointers.
const ARBRobustness &ARBRobustnessAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_robustness entry points.
void ARBRobustnessAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetGraphicsResetStatusARB().
GraphicsResetStatus ARBRobustnessAPI::getGraphicsResetStatus() const
{
    static const char *fnName = "glGetGraphicsResetStatusARB";

    beforeCommand(fnName, _api.glGetGraphicsResetStatus);
    GLenum result = _api.glGetGraphicsResetStatus();
    afterCommand(fnName);

    return static_cast<GraphicsResetStatus>(result);
}

// Calls glGetnCompressedTexImageARB().
void ARBRobustnessAPI::getnCompressedTexImage(TextureTarget target, GLint lod,
                                              GLsizei bufSize, void *img) const
{
    static const char *fnName = "glGetnCompressedTexImageARB";

    beforeCommand(fnName, _api.glGetnCompressedTexImage);
    _api.glGetnCompressedTexImage(toScalar(target), lod, bufSize, img);
    afterCommand(fnName);
}

// Calls glGetnTexImageARB().
void ARBRobustnessAPI::getnTexImage(TextureTarget target, GLint level,
                                    PixelFormat format, PixelType type,
                                    GLsizei bufSize, void *img) const
{
    static const char *fnName = "glGetnTexImageARB";

    beforeCommand(fnName, _api.glGetnTexImage);
    _api.glGetnTexImage(toScalar(target), level, toScalar(format),
                        toScalar(type), bufSize, img);
    afterCommand(fnName);
}

// Calls glGetnUniformdvARB().
void ARBRobustnessAPI::getnUniformDV(ProgramName program, GLint location,
                                     GLsizei bufSize, GLdouble *params) const
{
    static const char *fnName = "glGetnUniformdvARB";

    beforeCommand(fnName, _api.glGetnUniformdv);
    _api.glGetnUniformdv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformfvARB().
void ARBRobustnessAPI::getnUniformFV(ProgramName program, GLint location,
                                     GLsizei bufSize, GLfloat *params) const
{
    static const char *fnName = "glGetnUniformfvARB";

    beforeCommand(fnName, _api.glGetnUniformfv);
    _api.glGetnUniformfv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformivARB().
void ARBRobustnessAPI::getnUniformIV(ProgramName program, GLint location,
                                     GLsizei bufSize, GLint *params) const
{
    static const char *fnName = "glGetnUniformivARB";

    beforeCommand(fnName, _api.glGetnUniformiv);
    _api.glGetnUniformiv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glGetnUniformuivARB().
void ARBRobustnessAPI::getnUniformUIV(ProgramName program, GLint location,
                                      GLsizei bufSize, GLuint *params) const
{
    static const char *fnName = "glGetnUniformuivARB";

    beforeCommand(fnName, _api.glGetnUniformuiv);
    _api.glGetnUniformuiv(program.ID, location, bufSize, params);
    afterCommand(fnName);
}

// Calls glReadnPixelsARB().
void ARBRobustnessAPI::readnPixels(GLint x, GLint y, GLsizei width,
                                   GLsizei height, PixelFormat format,
                                   PixelType type, GLsizei bufSize, void *data) const
{
    static const char *fnName = "glReadnPixelsARB";

    beforeCommand(fnName, _api.glReadnPixels);
    _api.glReadnPixels(x, y, width, height, toScalar(format), toScalar(type),
                       bufSize, data);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBSampleLocationsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_sample_locations extension.
ARBSampleLocationsAPI::ARBSampleLocationsAPI() :
    BaseExtension("GL_ARB_sample_locations")
{
}

// Grant read-only access to the underlying function pointers.
const ARBSampleLocations &ARBSampleLocationsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_sample_locations entry points.
void ARBSampleLocationsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glEvaluateDepthValuesARB().
void ARBSampleLocationsAPI::evaluateDepthValues() const
{
    static const char *fnName = "glEvaluateDepthValuesARB";

    beforeCommand(fnName, _api.glEvaluateDepthValues);
    _api.glEvaluateDepthValues();
    afterCommand(fnName);
}

// Calls glFramebufferSampleLocationsfvARB().
void ARBSampleLocationsAPI::framebufferSampleLocationsFV(FramebufferTarget target,
                                                         GLuint start,
                                                         GLsizei count,
                                                         const GLfloat *v) const
{
    static const char *fnName = "glFramebufferSampleLocationsfvARB";

    beforeCommand(fnName, _api.glFramebufferSampleLocationsfv);
    _api.glFramebufferSampleLocationsfv(toScalar(target), start, count, v);
    afterCommand(fnName);
}

// Calls glNamedFramebufferSampleLocationsfvARB().
void ARBSampleLocationsAPI::namedFramebufferSampleLocationsFV(FramebufferName framebuffer,
                                                              GLuint start,
                                                              GLsizei count,
                                                              const GLfloat *v) const
{
    static const char *fnName = "glNamedFramebufferSampleLocationsfvARB";

    beforeCommand(fnName, _api.glNamedFramebufferSampleLocationsfv);
    _api.glNamedFramebufferSampleLocationsfv(framebuffer.ID, start, count, v);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBSampleShadingAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_sample_shading extension.
ARBSampleShadingAPI::ARBSampleShadingAPI() :
    BaseExtension("GL_ARB_sample_shading")
{
}

// Grant read-only access to the underlying function pointers.
const ARBSampleShading &ARBSampleShadingAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_sample_shading entry points.
void ARBSampleShadingAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMinSampleShadingARB().
void ARBSampleShadingAPI::minSampleShading(GLfloat value) const
{
    static const char *fnName = "glMinSampleShadingARB";

    beforeCommand(fnName, _api.glMinSampleShading);
    _api.glMinSampleShading(value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBShaderObjectsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_shader_objects extension.
ARBShaderObjectsAPI::ARBShaderObjectsAPI() :
    BaseExtension("GL_ARB_shader_objects")
{
}

// Grant read-only access to the underlying function pointers.
const ARBShaderObjects &ARBShaderObjectsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_shader_objects entry points.
void ARBShaderObjectsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAttachObjectARB().
void ARBShaderObjectsAPI::attachObject(GLhandleARB containerObj, GLhandleARB obj) const
{
    static const char *fnName = "glAttachObjectARB";

    beforeCommand(fnName, _api.glAttachObject);
    _api.glAttachObject(containerObj, obj);
    afterCommand(fnName);
}

// Calls glCompileShaderARB().
void ARBShaderObjectsAPI::compileShader(GLhandleARB shaderObj) const
{
    static const char *fnName = "glCompileShaderARB";

    beforeCommand(fnName, _api.glCompileShader);
    _api.glCompileShader(shaderObj);
    afterCommand(fnName);
}

// Calls glCreateProgramObjectARB().
GLhandleARB ARBShaderObjectsAPI::createProgramObject() const
{
    static const char *fnName = "glCreateProgramObjectARB";

    beforeCommand(fnName, _api.glCreateProgramObject);
    GLhandleARB result = _api.glCreateProgramObject();
    afterCommand(fnName);

    return result;
}

// Calls glCreateShaderObjectARB().
GLhandleARB ARBShaderObjectsAPI::createShaderObject(ShaderType shaderType) const
{
    static const char *fnName = "glCreateShaderObjectARB";

    beforeCommand(fnName, _api.glCreateShaderObject);
    GLhandleARB result = _api.glCreateShaderObject(toScalar(shaderType));
    afterCommand(fnName);

    return result;
}

// Calls glDeleteObjectARB().
void ARBShaderObjectsAPI::deleteObject(GLhandleARB obj) const
{
    static const char *fnName = "glDeleteObjectARB";

    beforeCommand(fnName, _api.glDeleteObject);
    _api.glDeleteObject(obj);
    afterCommand(fnName);
}

// Calls glDetachObjectARB().
void ARBShaderObjectsAPI::detachObject(GLhandleARB containerObj,
                                       GLhandleARB attachedObj) const
{
    static const char *fnName = "glDetachObjectARB";

    beforeCommand(fnName, _api.glDetachObject);
    _api.glDetachObject(containerObj, attachedObj);
    afterCommand(fnName);
}

// Calls glGetActiveUniformARB().
void ARBShaderObjectsAPI::getActiveUniform(GLhandleARB programObj, GLuint index,
                                           GLsizei maxLength, GLsizei *length,
                                           GLint *size, UniformType *type,
                                           GLcharARB *name) const
{
    static const char *fnName = "glGetActiveUniformARB";

    beforeCommand(fnName, _api.glGetActiveUniform);
    _api.glGetActiveUniform(programObj, index, maxLength, length, size,
                            toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glGetAttachedObjectsARB().
void ARBShaderObjectsAPI::getAttachedObjects(GLhandleARB containerObj,
                                             GLsizei maxCount, GLsizei *count,
                                             GLhandleARB *obj) const
{
    static const char *fnName = "glGetAttachedObjectsARB";

    beforeCommand(fnName, _api.glGetAttachedObjects);
    _api.glGetAttachedObjects(containerObj, maxCount, count, obj);
    afterCommand(fnName);
}

// Calls glGetHandleARB().
GLhandleARB ARBShaderObjectsAPI::getHandle(GLenum pname) const
{
    static const char *fnName = "glGetHandleARB";

    beforeCommand(fnName, _api.glGetHandle);
    GLhandleARB result = _api.glGetHandle(pname);
    afterCommand(fnName);

    return result;
}

// Calls glGetInfoLogARB().
void ARBShaderObjectsAPI::getInfoLog(GLhandleARB obj, GLsizei maxLength,
                                     GLsizei *length, GLcharARB *infoLog) const
{
    static const char *fnName = "glGetInfoLogARB";

    beforeCommand(fnName, _api.glGetInfoLog);
    _api.glGetInfoLog(obj, maxLength, length, infoLog);
    afterCommand(fnName);
}

// Calls glGetObjectParameterfvARB().
void ARBShaderObjectsAPI::getObjectParameterFV(GLhandleARB obj, GLenum pname,
                                               GLfloat *params) const
{
    static const char *fnName = "glGetObjectParameterfvARB";

    beforeCommand(fnName, _api.glGetObjectParameterfv);
    _api.glGetObjectParameterfv(obj, pname, params);
    afterCommand(fnName);
}

// Calls glGetObjectParameterivARB().
void ARBShaderObjectsAPI::getObjectParameterIV(GLhandleARB obj, GLenum pname,
                                               GLint *params) const
{
    static const char *fnName = "glGetObjectParameterivARB";

    beforeCommand(fnName, _api.glGetObjectParameteriv);
    _api.glGetObjectParameteriv(obj, pname, params);
    afterCommand(fnName);
}

// Calls glGetShaderSourceARB().
void ARBShaderObjectsAPI::getShaderSource(GLhandleARB obj, GLsizei maxLength,
                                          GLsizei *length, GLcharARB *source) const
{
    static const char *fnName = "glGetShaderSourceARB";

    beforeCommand(fnName, _api.glGetShaderSource);
    _api.glGetShaderSource(obj, maxLength, length, source);
    afterCommand(fnName);
}

// Calls glGetUniformLocationARB().
GLint ARBShaderObjectsAPI::getUniformLocation(GLhandleARB programObj,
                                              const GLcharARB *name) const
{
    static const char *fnName = "glGetUniformLocationARB";

    beforeCommand(fnName, _api.glGetUniformLocation);
    GLint result = _api.glGetUniformLocation(programObj, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformfvARB().
void ARBShaderObjectsAPI::getUniformFV(GLhandleARB programObj, GLint location,
                                       GLfloat *params) const
{
    static const char *fnName = "glGetUniformfvARB";

    beforeCommand(fnName, _api.glGetUniformfv);
    _api.glGetUniformfv(programObj, location, params);
    afterCommand(fnName);
}

// Calls glGetUniformivARB().
void ARBShaderObjectsAPI::getUniformIV(GLhandleARB programObj, GLint location,
                                       GLint *params) const
{
    static const char *fnName = "glGetUniformivARB";

    beforeCommand(fnName, _api.glGetUniformiv);
    _api.glGetUniformiv(programObj, location, params);
    afterCommand(fnName);
}

// Calls glLinkProgramARB().
void ARBShaderObjectsAPI::linkProgram(GLhandleARB programObj) const
{
    static const char *fnName = "glLinkProgramARB";

    beforeCommand(fnName, _api.glLinkProgram);
    _api.glLinkProgram(programObj);
    afterCommand(fnName);
}

// Calls glShaderSourceARB().
void ARBShaderObjectsAPI::shaderSource(GLhandleARB shaderObj, GLsizei count,
                                       const GLcharARB **string,
                                       const GLint *length) const
{
    static const char *fnName = "glShaderSourceARB";

    beforeCommand(fnName, _api.glShaderSource);
    _api.glShaderSource(shaderObj, count, string, length);
    afterCommand(fnName);
}

// Calls glUniform1fARB().
void ARBShaderObjectsAPI::uniform1F(GLint location, GLfloat v0) const
{
    static const char *fnName = "glUniform1fARB";

    beforeCommand(fnName, _api.glUniform1f);
    _api.glUniform1f(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1fvARB().
void ARBShaderObjectsAPI::uniform1FV(GLint location, GLsizei count,
                                     const GLfloat *value) const
{
    static const char *fnName = "glUniform1fvARB";

    beforeCommand(fnName, _api.glUniform1fv);
    _api.glUniform1fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform1iARB().
void ARBShaderObjectsAPI::uniform1I(GLint location, GLint v0) const
{
    static const char *fnName = "glUniform1iARB";

    beforeCommand(fnName, _api.glUniform1i);
    _api.glUniform1i(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1ivARB().
void ARBShaderObjectsAPI::uniform1IV(GLint location, GLsizei count,
                                     const GLint *value) const
{
    static const char *fnName = "glUniform1ivARB";

    beforeCommand(fnName, _api.glUniform1iv);
    _api.glUniform1iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2fARB().
void ARBShaderObjectsAPI::uniform2F(GLint location, GLfloat v0, GLfloat v1) const
{
    static const char *fnName = "glUniform2fARB";

    beforeCommand(fnName, _api.glUniform2f);
    _api.glUniform2f(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2fvARB().
void ARBShaderObjectsAPI::uniform2FV(GLint location, GLsizei count,
                                     const GLfloat *value) const
{
    static const char *fnName = "glUniform2fvARB";

    beforeCommand(fnName, _api.glUniform2fv);
    _api.glUniform2fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2iARB().
void ARBShaderObjectsAPI::uniform2I(GLint location, GLint v0, GLint v1) const
{
    static const char *fnName = "glUniform2iARB";

    beforeCommand(fnName, _api.glUniform2i);
    _api.glUniform2i(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2ivARB().
void ARBShaderObjectsAPI::uniform2IV(GLint location, GLsizei count,
                                     const GLint *value) const
{
    static const char *fnName = "glUniform2ivARB";

    beforeCommand(fnName, _api.glUniform2iv);
    _api.glUniform2iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3fARB().
void ARBShaderObjectsAPI::uniform3F(GLint location, GLfloat v0, GLfloat v1,
                                    GLfloat v2) const
{
    static const char *fnName = "glUniform3fARB";

    beforeCommand(fnName, _api.glUniform3f);
    _api.glUniform3f(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3fvARB().
void ARBShaderObjectsAPI::uniform3FV(GLint location, GLsizei count,
                                     const GLfloat *value) const
{
    static const char *fnName = "glUniform3fvARB";

    beforeCommand(fnName, _api.glUniform3fv);
    _api.glUniform3fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3iARB().
void ARBShaderObjectsAPI::uniform3I(GLint location, GLint v0, GLint v1, GLint v2) const
{
    static const char *fnName = "glUniform3iARB";

    beforeCommand(fnName, _api.glUniform3i);
    _api.glUniform3i(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3ivARB().
void ARBShaderObjectsAPI::uniform3IV(GLint location, GLsizei count,
                                     const GLint *value) const
{
    static const char *fnName = "glUniform3ivARB";

    beforeCommand(fnName, _api.glUniform3iv);
    _api.glUniform3iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4fARB().
void ARBShaderObjectsAPI::uniform4F(GLint location, GLfloat v0, GLfloat v1,
                                    GLfloat v2, GLfloat v3) const
{
    static const char *fnName = "glUniform4fARB";

    beforeCommand(fnName, _api.glUniform4f);
    _api.glUniform4f(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4fvARB().
void ARBShaderObjectsAPI::uniform4FV(GLint location, GLsizei count,
                                     const GLfloat *value) const
{
    static const char *fnName = "glUniform4fvARB";

    beforeCommand(fnName, _api.glUniform4fv);
    _api.glUniform4fv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4iARB().
void ARBShaderObjectsAPI::uniform4I(GLint location, GLint v0, GLint v1, GLint v2,
                                    GLint v3) const
{
    static const char *fnName = "glUniform4iARB";

    beforeCommand(fnName, _api.glUniform4i);
    _api.glUniform4i(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4ivARB().
void ARBShaderObjectsAPI::uniform4IV(GLint location, GLsizei count,
                                     const GLint *value) const
{
    static const char *fnName = "glUniform4ivARB";

    beforeCommand(fnName, _api.glUniform4iv);
    _api.glUniform4iv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniformMatrix2fvARB().
void ARBShaderObjectsAPI::uniformMatrix2FV(GLint location, GLsizei count,
                                           Boolean transpose,
                                           const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix2fvARB";

    beforeCommand(fnName, _api.glUniformMatrix2fv);
    _api.glUniformMatrix2fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix3fvARB().
void ARBShaderObjectsAPI::uniformMatrix3FV(GLint location, GLsizei count,
                                           Boolean transpose,
                                           const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix3fvARB";

    beforeCommand(fnName, _api.glUniformMatrix3fv);
    _api.glUniformMatrix3fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUniformMatrix4fvARB().
void ARBShaderObjectsAPI::uniformMatrix4FV(GLint location, GLsizei count,
                                           Boolean transpose,
                                           const GLfloat *value) const
{
    static const char *fnName = "glUniformMatrix4fvARB";

    beforeCommand(fnName, _api.glUniformMatrix4fv);
    _api.glUniformMatrix4fv(location, count, toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glUseProgramObjectARB().
void ARBShaderObjectsAPI::useProgramObject(GLhandleARB programObj) const
{
    static const char *fnName = "glUseProgramObjectARB";

    beforeCommand(fnName, _api.glUseProgramObject);
    _api.glUseProgramObject(programObj);
    afterCommand(fnName);
}

// Calls glValidateProgramARB().
void ARBShaderObjectsAPI::validateProgram(GLhandleARB programObj) const
{
    static const char *fnName = "glValidateProgramARB";

    beforeCommand(fnName, _api.glValidateProgram);
    _api.glValidateProgram(programObj);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBShadingLanguageIncludeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_shading_language_include extension.
ARBShadingLanguageIncludeAPI::ARBShadingLanguageIncludeAPI() :
    BaseExtension("GL_ARB_shading_language_include")
{
}

// Grant read-only access to the underlying function pointers.
const ARBShadingLanguageInclude &ARBShadingLanguageIncludeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_shading_language_include entry points.
void ARBShadingLanguageIncludeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCompileShaderIncludeARB().
void ARBShadingLanguageIncludeAPI::compileShaderInclude(ShaderName shader,
                                                        GLsizei count,
                                                        const GLchar *const *path,
                                                        const GLint *length) const
{
    static const char *fnName = "glCompileShaderIncludeARB";

    beforeCommand(fnName, _api.glCompileShaderInclude);
    _api.glCompileShaderInclude(shader.ID, count, path, length);
    afterCommand(fnName);
}

// Calls glDeleteNamedStringARB().
void ARBShadingLanguageIncludeAPI::deleteNamedString(GLint namelen,
                                                     const GLchar *name) const
{
    static const char *fnName = "glDeleteNamedStringARB";

    beforeCommand(fnName, _api.glDeleteNamedString);
    _api.glDeleteNamedString(namelen, name);
    afterCommand(fnName);
}

// Calls glGetNamedStringARB().
void ARBShadingLanguageIncludeAPI::getNamedString(GLint namelen,
                                                  const GLchar *name,
                                                  GLsizei bufSize,
                                                  GLint *stringlen,
                                                  GLchar *string) const
{
    static const char *fnName = "glGetNamedStringARB";

    beforeCommand(fnName, _api.glGetNamedString);
    _api.glGetNamedString(namelen, name, bufSize, stringlen, string);
    afterCommand(fnName);
}

// Calls glGetNamedStringivARB().
void ARBShadingLanguageIncludeAPI::getNamedStringIV(GLint namelen,
                                                    const GLchar *name,
                                                    GLenum pname, GLint *params) const
{
    static const char *fnName = "glGetNamedStringivARB";

    beforeCommand(fnName, _api.glGetNamedStringiv);
    _api.glGetNamedStringiv(namelen, name, pname, params);
    afterCommand(fnName);
}

// Calls glIsNamedStringARB().
Boolean ARBShadingLanguageIncludeAPI::isNamedString(GLint namelen,
                                                    const GLchar *name) const
{
    static const char *fnName = "glIsNamedStringARB";

    beforeCommand(fnName, _api.glIsNamedString);
    GLboolean result = _api.glIsNamedString(namelen, name);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glNamedStringARB().
void ARBShadingLanguageIncludeAPI::namedString(GLenum type, GLint namelen,
                                               const GLchar *name,
                                               GLint stringlen,
                                               const GLchar *string) const
{
    static const char *fnName = "glNamedStringARB";

    beforeCommand(fnName, _api.glNamedString);
    _api.glNamedString(type, namelen, name, stringlen, string);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBSparseBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_sparse_buffer extension.
ARBSparseBufferAPI::ARBSparseBufferAPI() :
    BaseExtension("GL_ARB_sparse_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const ARBSparseBuffer &ARBSparseBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_sparse_buffer entry points.
void ARBSparseBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferPageCommitmentARB().
void ARBSparseBufferAPI::bufferPageCommitment(GLenum target, GLintptr offset,
                                              GLsizeiptr size, Boolean commit) const
{
    static const char *fnName = "glBufferPageCommitmentARB";

    beforeCommand(fnName, _api.glBufferPageCommitment);
    _api.glBufferPageCommitment(target, offset, size, toScalar(commit));
    afterCommand(fnName);
}

// Calls glNamedBufferPageCommitmentARB().
void ARBSparseBufferAPI::namedBufferPageCommitmentARB(BufferName buffer,
                                                      GLintptr offset,
                                                      GLsizeiptr size,
                                                      Boolean commit) const
{
    static const char *fnName = "glNamedBufferPageCommitmentARB";

    beforeCommand(fnName, _api.glNamedBufferPageCommitmentARB);
    _api.glNamedBufferPageCommitmentARB(buffer.ID, offset, size,
                                        toScalar(commit));
    afterCommand(fnName);
}

// Calls glNamedBufferPageCommitmentEXT().
void ARBSparseBufferAPI::namedBufferPageCommitmentEXT(BufferName buffer,
                                                      GLintptr offset,
                                                      GLsizeiptr size,
                                                      Boolean commit) const
{
    static const char *fnName = "glNamedBufferPageCommitmentEXT";

    beforeCommand(fnName, _api.glNamedBufferPageCommitmentEXT);
    _api.glNamedBufferPageCommitmentEXT(buffer.ID, offset, size,
                                        toScalar(commit));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBSparseTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_sparse_texture extension.
ARBSparseTextureAPI::ARBSparseTextureAPI() :
    BaseExtension("GL_ARB_sparse_texture")
{
}

// Grant read-only access to the underlying function pointers.
const ARBSparseTexture &ARBSparseTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_sparse_texture entry points.
void ARBSparseTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexPageCommitmentARB().
void ARBSparseTextureAPI::texPageCommitment(GLenum target, GLint level,
                                            GLint xoffset, GLint yoffset,
                                            GLint zoffset, GLsizei width,
                                            GLsizei height, GLsizei depth,
                                            Boolean commit) const
{
    static const char *fnName = "glTexPageCommitmentARB";

    beforeCommand(fnName, _api.glTexPageCommitment);
    _api.glTexPageCommitment(target, level, xoffset, yoffset, zoffset, width,
                             height, depth, toScalar(commit));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBTextureBufferObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_texture_buffer_object extension.
ARBTextureBufferObjectAPI::ARBTextureBufferObjectAPI() :
    BaseExtension("GL_ARB_texture_buffer_object")
{
}

// Grant read-only access to the underlying function pointers.
const ARBTextureBufferObject &ARBTextureBufferObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_texture_buffer_object entry points.
void ARBTextureBufferObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexBufferARB().
void ARBTextureBufferObjectAPI::texBuffer(TextureTarget target,
                                          SizedInternalFormat internalformat,
                                          BufferName buffer) const
{
    static const char *fnName = "glTexBufferARB";

    beforeCommand(fnName, _api.glTexBuffer);
    _api.glTexBuffer(toScalar(target), toScalar(internalformat), buffer.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBTextureCompressionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_texture_compression extension.
ARBTextureCompressionAPI::ARBTextureCompressionAPI() :
    BaseExtension("GL_ARB_texture_compression")
{
}

// Grant read-only access to the underlying function pointers.
const ARBTextureCompression &ARBTextureCompressionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_texture_compression entry points.
void ARBTextureCompressionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCompressedTexImage1DARB().
void ARBTextureCompressionAPI::compressedTexImage1D(TextureTarget target,
                                                    GLint level,
                                                    InternalFormat internalformat,
                                                    GLsizei width, GLint border,
                                                    GLsizei imageSize,
                                                    const void *data) const
{
    static const char *fnName = "glCompressedTexImage1DARB";

    beforeCommand(fnName, _api.glCompressedTexImage1D);
    _api.glCompressedTexImage1D(toScalar(target), level,
                                toScalar(internalformat), width, border,
                                imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexImage2DARB().
void ARBTextureCompressionAPI::compressedTexImage2D(TextureTarget target,
                                                    GLint level,
                                                    InternalFormat internalformat,
                                                    GLsizei width,
                                                    GLsizei height, GLint border,
                                                    GLsizei imageSize,
                                                    const void *data) const
{
    static const char *fnName = "glCompressedTexImage2DARB";

    beforeCommand(fnName, _api.glCompressedTexImage2D);
    _api.glCompressedTexImage2D(toScalar(target), level,
                                toScalar(internalformat), width, height, border,
                                imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexImage3DARB().
void ARBTextureCompressionAPI::compressedTexImage3D(TextureTarget target,
                                                    GLint level,
                                                    InternalFormat internalformat,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth, GLint border,
                                                    GLsizei imageSize,
                                                    const void *data) const
{
    static const char *fnName = "glCompressedTexImage3DARB";

    beforeCommand(fnName, _api.glCompressedTexImage3D);
    _api.glCompressedTexImage3D(toScalar(target), level,
                                toScalar(internalformat), width, height, depth,
                                border, imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage1DARB().
void ARBTextureCompressionAPI::compressedTexSubImage1D(TextureTarget target,
                                                       GLint level,
                                                       GLint xoffset,
                                                       GLsizei width,
                                                       InternalFormat format,
                                                       GLsizei imageSize,
                                                       const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage1DARB";

    beforeCommand(fnName, _api.glCompressedTexSubImage1D);
    _api.glCompressedTexSubImage1D(toScalar(target), level, xoffset, width,
                                   toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage2DARB().
void ARBTextureCompressionAPI::compressedTexSubImage2D(TextureTarget target,
                                                       GLint level,
                                                       GLint xoffset,
                                                       GLint yoffset,
                                                       GLsizei width,
                                                       GLsizei height,
                                                       InternalFormat format,
                                                       GLsizei imageSize,
                                                       const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage2DARB";

    beforeCommand(fnName, _api.glCompressedTexSubImage2D);
    _api.glCompressedTexSubImage2D(toScalar(target), level, xoffset, yoffset,
                                   width, height, toScalar(format), imageSize,
                                   data);
    afterCommand(fnName);
}

// Calls glCompressedTexSubImage3DARB().
void ARBTextureCompressionAPI::compressedTexSubImage3D(TextureTarget target,
                                                       GLint level,
                                                       GLint xoffset,
                                                       GLint yoffset,
                                                       GLint zoffset,
                                                       GLsizei width,
                                                       GLsizei height,
                                                       GLsizei depth,
                                                       InternalFormat format,
                                                       GLsizei imageSize,
                                                       const void *data) const
{
    static const char *fnName = "glCompressedTexSubImage3DARB";

    beforeCommand(fnName, _api.glCompressedTexSubImage3D);
    _api.glCompressedTexSubImage3D(toScalar(target), level, xoffset, yoffset,
                                   zoffset, width, height, depth,
                                   toScalar(format), imageSize, data);
    afterCommand(fnName);
}

// Calls glGetCompressedTexImageARB().
void ARBTextureCompressionAPI::getCompressedTexImage(TextureTarget target,
                                                     GLint level, void *img) const
{
    static const char *fnName = "glGetCompressedTexImageARB";

    beforeCommand(fnName, _api.glGetCompressedTexImage);
    _api.glGetCompressedTexImage(toScalar(target), level, img);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBTransposeMatrixAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_transpose_matrix extension.
ARBTransposeMatrixAPI::ARBTransposeMatrixAPI() :
    BaseExtension("GL_ARB_transpose_matrix")
{
}

// Grant read-only access to the underlying function pointers.
const ARBTransposeMatrix &ARBTransposeMatrixAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_transpose_matrix entry points.
void ARBTransposeMatrixAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glLoadTransposeMatrixdARB().
void ARBTransposeMatrixAPI::loadTransposeMatrixD(const GLdouble *m) const
{
    static const char *fnName = "glLoadTransposeMatrixdARB";

    beforeCommand(fnName, _api.glLoadTransposeMatrixd);
    _api.glLoadTransposeMatrixd(m);
    afterCommand(fnName);
}

// Calls glLoadTransposeMatrixfARB().
void ARBTransposeMatrixAPI::loadTransposeMatrixF(const GLfloat *m) const
{
    static const char *fnName = "glLoadTransposeMatrixfARB";

    beforeCommand(fnName, _api.glLoadTransposeMatrixf);
    _api.glLoadTransposeMatrixf(m);
    afterCommand(fnName);
}

// Calls glMultTransposeMatrixdARB().
void ARBTransposeMatrixAPI::multTransposeMatrixD(const GLdouble *m) const
{
    static const char *fnName = "glMultTransposeMatrixdARB";

    beforeCommand(fnName, _api.glMultTransposeMatrixd);
    _api.glMultTransposeMatrixd(m);
    afterCommand(fnName);
}

// Calls glMultTransposeMatrixfARB().
void ARBTransposeMatrixAPI::multTransposeMatrixF(const GLfloat *m) const
{
    static const char *fnName = "glMultTransposeMatrixfARB";

    beforeCommand(fnName, _api.glMultTransposeMatrixf);
    _api.glMultTransposeMatrixf(m);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexBlendAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_vertex_blend extension.
ARBVertexBlendAPI::ARBVertexBlendAPI() :
    BaseExtension("GL_ARB_vertex_blend")
{
}

// Grant read-only access to the underlying function pointers.
const ARBVertexBlend &ARBVertexBlendAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_vertex_blend entry points.
void ARBVertexBlendAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVertexBlendARB().
void ARBVertexBlendAPI::vertexBlend(GLint count) const
{
    static const char *fnName = "glVertexBlendARB";

    beforeCommand(fnName, _api.glVertexBlend);
    _api.glVertexBlend(count);
    afterCommand(fnName);
}

// Calls glWeightPointerARB().
void ARBVertexBlendAPI::weightPointer(GLint size, WeightPointerTypeARB type,
                                      GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glWeightPointerARB";

    beforeCommand(fnName, _api.glWeightPointer);
    _api.glWeightPointer(size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glWeightbvARB().
void ARBVertexBlendAPI::weightBV(GLint size, const GLbyte *weights) const
{
    static const char *fnName = "glWeightbvARB";

    beforeCommand(fnName, _api.glWeightbv);
    _api.glWeightbv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightdvARB().
void ARBVertexBlendAPI::weightDV(GLint size, const GLdouble *weights) const
{
    static const char *fnName = "glWeightdvARB";

    beforeCommand(fnName, _api.glWeightdv);
    _api.glWeightdv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightfvARB().
void ARBVertexBlendAPI::weightFV(GLint size, const GLfloat *weights) const
{
    static const char *fnName = "glWeightfvARB";

    beforeCommand(fnName, _api.glWeightfv);
    _api.glWeightfv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightivARB().
void ARBVertexBlendAPI::weightIV(GLint size, const GLint *weights) const
{
    static const char *fnName = "glWeightivARB";

    beforeCommand(fnName, _api.glWeightiv);
    _api.glWeightiv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightsvARB().
void ARBVertexBlendAPI::weightSV(GLint size, const GLshort *weights) const
{
    static const char *fnName = "glWeightsvARB";

    beforeCommand(fnName, _api.glWeightsv);
    _api.glWeightsv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightubvARB().
void ARBVertexBlendAPI::weightUBV(GLint size, const GLubyte *weights) const
{
    static const char *fnName = "glWeightubvARB";

    beforeCommand(fnName, _api.glWeightubv);
    _api.glWeightubv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightuivARB().
void ARBVertexBlendAPI::weightUIV(GLint size, const GLuint *weights) const
{
    static const char *fnName = "glWeightuivARB";

    beforeCommand(fnName, _api.glWeightuiv);
    _api.glWeightuiv(size, weights);
    afterCommand(fnName);
}

// Calls glWeightusvARB().
void ARBVertexBlendAPI::weightUSV(GLint size, const GLushort *weights) const
{
    static const char *fnName = "glWeightusvARB";

    beforeCommand(fnName, _api.glWeightusv);
    _api.glWeightusv(size, weights);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexBufferObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_vertex_buffer_object extension.
ARBVertexBufferObjectAPI::ARBVertexBufferObjectAPI() :
    BaseExtension("GL_ARB_vertex_buffer_object")
{
}

// Grant read-only access to the underlying function pointers.
const ARBVertexBufferObject &ARBVertexBufferObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_vertex_buffer_object entry points.
void ARBVertexBufferObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindBufferARB().
void ARBVertexBufferObjectAPI::bindBuffer(BufferTargetARB target,
                                          BufferName buffer) const
{
    static const char *fnName = "glBindBufferARB";

    beforeCommand(fnName, _api.glBindBuffer);
    _api.glBindBuffer(toScalar(target), buffer.ID);
    afterCommand(fnName);
}

// Calls glBufferDataARB().
void ARBVertexBufferObjectAPI::bufferData(BufferTargetARB target,
                                          GLsizeiptrARB size, const void *data,
                                          BufferUsageARB usage) const
{
    static const char *fnName = "glBufferDataARB";

    beforeCommand(fnName, _api.glBufferData);
    _api.glBufferData(toScalar(target), size, data, toScalar(usage));
    afterCommand(fnName);
}

// Calls glBufferSubDataARB().
void ARBVertexBufferObjectAPI::bufferSubData(BufferTargetARB target,
                                             GLintptrARB offset,
                                             GLsizeiptrARB size,
                                             const void *data) const
{
    static const char *fnName = "glBufferSubDataARB";

    beforeCommand(fnName, _api.glBufferSubData);
    _api.glBufferSubData(toScalar(target), offset, size, data);
    afterCommand(fnName);
}

// Calls glDeleteBuffersARB().
void ARBVertexBufferObjectAPI::deleteBuffers(GLsizei n,
                                             const BufferName *buffers) const
{
    static const char *fnName = "glDeleteBuffersARB";

    beforeCommand(fnName, _api.glDeleteBuffers);
    _api.glDeleteBuffers(n, reinterpret_cast<const GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glGenBuffersARB().
void ARBVertexBufferObjectAPI::genBuffers(GLsizei n, BufferName *buffers) const
{
    static const char *fnName = "glGenBuffersARB";

    beforeCommand(fnName, _api.glGenBuffers);
    _api.glGenBuffers(n, reinterpret_cast<GLuint *>(buffers));
    afterCommand(fnName);
}

// Calls glGetBufferParameterivARB().
void ARBVertexBufferObjectAPI::getBufferParameterIV(BufferTargetARB target,
                                                    BufferPNameARB pname,
                                                    GLint *params) const
{
    static const char *fnName = "glGetBufferParameterivARB";

    beforeCommand(fnName, _api.glGetBufferParameteriv);
    _api.glGetBufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetBufferPointervARB().
void ARBVertexBufferObjectAPI::getBufferPointerV(BufferTargetARB target,
                                                 BufferPointerNameARB pname,
                                                 void **params) const
{
    static const char *fnName = "glGetBufferPointervARB";

    beforeCommand(fnName, _api.glGetBufferPointerv);
    _api.glGetBufferPointerv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetBufferSubDataARB().
void ARBVertexBufferObjectAPI::getBufferSubData(BufferTargetARB target,
                                                GLintptrARB offset,
                                                GLsizeiptrARB size, void *data) const
{
    static const char *fnName = "glGetBufferSubDataARB";

    beforeCommand(fnName, _api.glGetBufferSubData);
    _api.glGetBufferSubData(toScalar(target), offset, size, data);
    afterCommand(fnName);
}

// Calls glIsBufferARB().
Boolean ARBVertexBufferObjectAPI::isBuffer(BufferName buffer) const
{
    static const char *fnName = "glIsBufferARB";

    beforeCommand(fnName, _api.glIsBuffer);
    GLboolean result = _api.glIsBuffer(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMapBufferARB().
void *ARBVertexBufferObjectAPI::mapBuffer(BufferTargetARB target,
                                          BufferAccessARB access) const
{
    static const char *fnName = "glMapBufferARB";

    beforeCommand(fnName, _api.glMapBuffer);
    void *result = _api.glMapBuffer(toScalar(target), toScalar(access));
    afterCommand(fnName);

    return result;
}

// Calls glUnmapBufferARB().
Boolean ARBVertexBufferObjectAPI::unmapBuffer(BufferTargetARB target) const
{
    static const char *fnName = "glUnmapBufferARB";

    beforeCommand(fnName, _api.glUnmapBuffer);
    GLboolean result = _api.glUnmapBuffer(toScalar(target));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexProgramAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_vertex_program extension.
ARBVertexProgramAPI::ARBVertexProgramAPI() :
    BaseExtension("GL_ARB_vertex_program")
{
}

// Grant read-only access to the underlying function pointers.
const ARBVertexProgram &ARBVertexProgramAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_vertex_program entry points.
void ARBVertexProgramAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDisableVertexAttribArrayARB().
void ARBVertexProgramAPI::disableVertexAttribArray(GLuint index) const
{
    static const char *fnName = "glDisableVertexAttribArrayARB";

    beforeCommand(fnName, _api.glDisableVertexAttribArray);
    _api.glDisableVertexAttribArray(index);
    afterCommand(fnName);
}

// Calls glEnableVertexAttribArrayARB().
void ARBVertexProgramAPI::enableVertexAttribArray(GLuint index) const
{
    static const char *fnName = "glEnableVertexAttribArrayARB";

    beforeCommand(fnName, _api.glEnableVertexAttribArray);
    _api.glEnableVertexAttribArray(index);
    afterCommand(fnName);
}

// Calls glGetVertexAttribPointervARB().
void ARBVertexProgramAPI::getVertexAttribPointerV(GLuint index,
                                                  VertexAttribPointerPropertyARB pname,
                                                  void **pointer) const
{
    static const char *fnName = "glGetVertexAttribPointervARB";

    beforeCommand(fnName, _api.glGetVertexAttribPointerv);
    _api.glGetVertexAttribPointerv(index, toScalar(pname), pointer);
    afterCommand(fnName);
}

// Calls glGetVertexAttribdvARB().
void ARBVertexProgramAPI::getVertexAttribDV(GLuint index,
                                            VertexAttribPropertyARB pname,
                                            GLdouble *params) const
{
    static const char *fnName = "glGetVertexAttribdvARB";

    beforeCommand(fnName, _api.glGetVertexAttribdv);
    _api.glGetVertexAttribdv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribfvARB().
void ARBVertexProgramAPI::getVertexAttribFV(GLuint index,
                                            VertexAttribPropertyARB pname,
                                            GLfloat *params) const
{
    static const char *fnName = "glGetVertexAttribfvARB";

    beforeCommand(fnName, _api.glGetVertexAttribfv);
    _api.glGetVertexAttribfv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribivARB().
void ARBVertexProgramAPI::getVertexAttribIV(GLuint index,
                                            VertexAttribPropertyARB pname,
                                            GLint *params) const
{
    static const char *fnName = "glGetVertexAttribivARB";

    beforeCommand(fnName, _api.glGetVertexAttribiv);
    _api.glGetVertexAttribiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glVertexAttrib1dARB().
void ARBVertexProgramAPI::vertexAttrib1D(GLuint index, GLdouble x) const
{
    static const char *fnName = "glVertexAttrib1dARB";

    beforeCommand(fnName, _api.glVertexAttrib1d);
    _api.glVertexAttrib1d(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1dvARB().
void ARBVertexProgramAPI::vertexAttrib1DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib1dvARB";

    beforeCommand(fnName, _api.glVertexAttrib1dv);
    _api.glVertexAttrib1dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1fARB().
void ARBVertexProgramAPI::vertexAttrib1F(GLuint index, GLfloat x) const
{
    static const char *fnName = "glVertexAttrib1fARB";

    beforeCommand(fnName, _api.glVertexAttrib1f);
    _api.glVertexAttrib1f(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1fvARB().
void ARBVertexProgramAPI::vertexAttrib1FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib1fvARB";

    beforeCommand(fnName, _api.glVertexAttrib1fv);
    _api.glVertexAttrib1fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib1sARB().
void ARBVertexProgramAPI::vertexAttrib1S(GLuint index, GLshort x) const
{
    static const char *fnName = "glVertexAttrib1sARB";

    beforeCommand(fnName, _api.glVertexAttrib1s);
    _api.glVertexAttrib1s(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttrib1svARB().
void ARBVertexProgramAPI::vertexAttrib1SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib1svARB";

    beforeCommand(fnName, _api.glVertexAttrib1sv);
    _api.glVertexAttrib1sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2dARB().
void ARBVertexProgramAPI::vertexAttrib2D(GLuint index, GLdouble x, GLdouble y) const
{
    static const char *fnName = "glVertexAttrib2dARB";

    beforeCommand(fnName, _api.glVertexAttrib2d);
    _api.glVertexAttrib2d(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2dvARB().
void ARBVertexProgramAPI::vertexAttrib2DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib2dvARB";

    beforeCommand(fnName, _api.glVertexAttrib2dv);
    _api.glVertexAttrib2dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2fARB().
void ARBVertexProgramAPI::vertexAttrib2F(GLuint index, GLfloat x, GLfloat y) const
{
    static const char *fnName = "glVertexAttrib2fARB";

    beforeCommand(fnName, _api.glVertexAttrib2f);
    _api.glVertexAttrib2f(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2fvARB().
void ARBVertexProgramAPI::vertexAttrib2FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib2fvARB";

    beforeCommand(fnName, _api.glVertexAttrib2fv);
    _api.glVertexAttrib2fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib2sARB().
void ARBVertexProgramAPI::vertexAttrib2S(GLuint index, GLshort x, GLshort y) const
{
    static const char *fnName = "glVertexAttrib2sARB";

    beforeCommand(fnName, _api.glVertexAttrib2s);
    _api.glVertexAttrib2s(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttrib2svARB().
void ARBVertexProgramAPI::vertexAttrib2SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib2svARB";

    beforeCommand(fnName, _api.glVertexAttrib2sv);
    _api.glVertexAttrib2sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3dARB().
void ARBVertexProgramAPI::vertexAttrib3D(GLuint index, GLdouble x, GLdouble y,
                                         GLdouble z) const
{
    static const char *fnName = "glVertexAttrib3dARB";

    beforeCommand(fnName, _api.glVertexAttrib3d);
    _api.glVertexAttrib3d(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3dvARB().
void ARBVertexProgramAPI::vertexAttrib3DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib3dvARB";

    beforeCommand(fnName, _api.glVertexAttrib3dv);
    _api.glVertexAttrib3dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3fARB().
void ARBVertexProgramAPI::vertexAttrib3F(GLuint index, GLfloat x, GLfloat y,
                                         GLfloat z) const
{
    static const char *fnName = "glVertexAttrib3fARB";

    beforeCommand(fnName, _api.glVertexAttrib3f);
    _api.glVertexAttrib3f(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3fvARB().
void ARBVertexProgramAPI::vertexAttrib3FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib3fvARB";

    beforeCommand(fnName, _api.glVertexAttrib3fv);
    _api.glVertexAttrib3fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib3sARB().
void ARBVertexProgramAPI::vertexAttrib3S(GLuint index, GLshort x, GLshort y,
                                         GLshort z) const
{
    static const char *fnName = "glVertexAttrib3sARB";

    beforeCommand(fnName, _api.glVertexAttrib3s);
    _api.glVertexAttrib3s(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttrib3svARB().
void ARBVertexProgramAPI::vertexAttrib3SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib3svARB";

    beforeCommand(fnName, _api.glVertexAttrib3sv);
    _api.glVertexAttrib3sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NbvARB().
void ARBVertexProgramAPI::vertexAttrib4NBV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttrib4NbvARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nbv);
    _api.glVertexAttrib4Nbv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NivARB().
void ARBVertexProgramAPI::vertexAttrib4NIV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttrib4NivARB";

    beforeCommand(fnName, _api.glVertexAttrib4Niv);
    _api.glVertexAttrib4Niv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NsvARB().
void ARBVertexProgramAPI::vertexAttrib4NSV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib4NsvARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nsv);
    _api.glVertexAttrib4Nsv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NubARB().
void ARBVertexProgramAPI::vertexAttrib4NUB(GLuint index, GLubyte x, GLubyte y,
                                           GLubyte z, GLubyte w) const
{
    static const char *fnName = "glVertexAttrib4NubARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nub);
    _api.glVertexAttrib4Nub(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NubvARB().
void ARBVertexProgramAPI::vertexAttrib4NUBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttrib4NubvARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nubv);
    _api.glVertexAttrib4Nubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NuivARB().
void ARBVertexProgramAPI::vertexAttrib4NUIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttrib4NuivARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nuiv);
    _api.glVertexAttrib4Nuiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4NusvARB().
void ARBVertexProgramAPI::vertexAttrib4NUSV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttrib4NusvARB";

    beforeCommand(fnName, _api.glVertexAttrib4Nusv);
    _api.glVertexAttrib4Nusv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4bvARB().
void ARBVertexProgramAPI::vertexAttrib4BV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttrib4bvARB";

    beforeCommand(fnName, _api.glVertexAttrib4bv);
    _api.glVertexAttrib4bv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4dARB().
void ARBVertexProgramAPI::vertexAttrib4D(GLuint index, GLdouble x, GLdouble y,
                                         GLdouble z, GLdouble w) const
{
    static const char *fnName = "glVertexAttrib4dARB";

    beforeCommand(fnName, _api.glVertexAttrib4d);
    _api.glVertexAttrib4d(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4dvARB().
void ARBVertexProgramAPI::vertexAttrib4DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttrib4dvARB";

    beforeCommand(fnName, _api.glVertexAttrib4dv);
    _api.glVertexAttrib4dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4fARB().
void ARBVertexProgramAPI::vertexAttrib4F(GLuint index, GLfloat x, GLfloat y,
                                         GLfloat z, GLfloat w) const
{
    static const char *fnName = "glVertexAttrib4fARB";

    beforeCommand(fnName, _api.glVertexAttrib4f);
    _api.glVertexAttrib4f(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4fvARB().
void ARBVertexProgramAPI::vertexAttrib4FV(GLuint index, const GLfloat *v) const
{
    static const char *fnName = "glVertexAttrib4fvARB";

    beforeCommand(fnName, _api.glVertexAttrib4fv);
    _api.glVertexAttrib4fv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4ivARB().
void ARBVertexProgramAPI::vertexAttrib4IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttrib4ivARB";

    beforeCommand(fnName, _api.glVertexAttrib4iv);
    _api.glVertexAttrib4iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4sARB().
void ARBVertexProgramAPI::vertexAttrib4S(GLuint index, GLshort x, GLshort y,
                                         GLshort z, GLshort w) const
{
    static const char *fnName = "glVertexAttrib4sARB";

    beforeCommand(fnName, _api.glVertexAttrib4s);
    _api.glVertexAttrib4s(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttrib4svARB().
void ARBVertexProgramAPI::vertexAttrib4SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttrib4svARB";

    beforeCommand(fnName, _api.glVertexAttrib4sv);
    _api.glVertexAttrib4sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4ubvARB().
void ARBVertexProgramAPI::vertexAttrib4UBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttrib4ubvARB";

    beforeCommand(fnName, _api.glVertexAttrib4ubv);
    _api.glVertexAttrib4ubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4uivARB().
void ARBVertexProgramAPI::vertexAttrib4UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttrib4uivARB";

    beforeCommand(fnName, _api.glVertexAttrib4uiv);
    _api.glVertexAttrib4uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttrib4usvARB().
void ARBVertexProgramAPI::vertexAttrib4USV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttrib4usvARB";

    beforeCommand(fnName, _api.glVertexAttrib4usv);
    _api.glVertexAttrib4usv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribPointerARB().
void ARBVertexProgramAPI::vertexAttribPointer(GLuint index, GLint size,
                                              VertexAttribPointerType type,
                                              Boolean normalized, GLsizei stride,
                                              const void *pointer) const
{
    static const char *fnName = "glVertexAttribPointerARB";

    beforeCommand(fnName, _api.glVertexAttribPointer);
    _api.glVertexAttribPointer(index, size, toScalar(type), toScalar(normalized),
                               stride, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBVertexShaderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_vertex_shader extension.
ARBVertexShaderAPI::ARBVertexShaderAPI() :
    BaseExtension("GL_ARB_vertex_shader")
{
}

// Grant read-only access to the underlying function pointers.
const ARBVertexShader &ARBVertexShaderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_vertex_shader entry points.
void ARBVertexShaderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindAttribLocationARB().
void ARBVertexShaderAPI::bindAttribLocation(GLhandleARB programObj, GLuint index,
                                            const GLcharARB *name) const
{
    static const char *fnName = "glBindAttribLocationARB";

    beforeCommand(fnName, _api.glBindAttribLocation);
    _api.glBindAttribLocation(programObj, index, name);
    afterCommand(fnName);
}

// Calls glGetActiveAttribARB().
void ARBVertexShaderAPI::getActiveAttrib(GLhandleARB programObj, GLuint index,
                                         GLsizei maxLength, GLsizei *length,
                                         GLint *size, AttributeType *type,
                                         GLcharARB *name) const
{
    static const char *fnName = "glGetActiveAttribARB";

    beforeCommand(fnName, _api.glGetActiveAttrib);
    _api.glGetActiveAttrib(programObj, index, maxLength, length, size,
                           toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glGetAttribLocationARB().
GLint ARBVertexShaderAPI::getAttribLocation(GLhandleARB programObj,
                                            const GLcharARB *name) const
{
    static const char *fnName = "glGetAttribLocationARB";

    beforeCommand(fnName, _api.glGetAttribLocation);
    GLint result = _api.glGetAttribLocation(programObj, name);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBViewportArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_viewport_array extension.
ARBViewportArrayAPI::ARBViewportArrayAPI() :
    BaseExtension("GL_ARB_viewport_array")
{
}

// Grant read-only access to the underlying function pointers.
const ARBViewportArray &ARBViewportArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_viewport_array entry points.
void ARBViewportArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDepthRangeArraydvNV().
void ARBViewportArrayAPI::depthRangeArrayDV(GLuint first, GLsizei count,
                                            const GLdouble *v) const
{
    static const char *fnName = "glDepthRangeArraydvNV";

    beforeCommand(fnName, _api.glDepthRangeArraydv);
    _api.glDepthRangeArraydv(first, count, v);
    afterCommand(fnName);
}

// Calls glDepthRangeIndexeddNV().
void ARBViewportArrayAPI::depthRangeIndexedD(GLuint index, GLdouble n,
                                             GLdouble f) const
{
    static const char *fnName = "glDepthRangeIndexeddNV";

    beforeCommand(fnName, _api.glDepthRangeIndexedd);
    _api.glDepthRangeIndexedd(index, n, f);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ARBWindowPosAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ARB_window_pos extension.
ARBWindowPosAPI::ARBWindowPosAPI() :
    BaseExtension("GL_ARB_window_pos")
{
}

// Grant read-only access to the underlying function pointers.
const ARBWindowPos &ARBWindowPosAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ARB_window_pos entry points.
void ARBWindowPosAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glWindowPos2dARB().
void ARBWindowPosAPI::windowPOS2D(GLdouble x, GLdouble y) const
{
    static const char *fnName = "glWindowPos2dARB";

    beforeCommand(fnName, _api.glWindowPos2d);
    _api.glWindowPos2d(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2dvARB().
void ARBWindowPosAPI::windowPOS2DV(const GLdouble *v) const
{
    static const char *fnName = "glWindowPos2dvARB";

    beforeCommand(fnName, _api.glWindowPos2dv);
    _api.glWindowPos2dv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2fARB().
void ARBWindowPosAPI::windowPOS2F(GLfloat x, GLfloat y) const
{
    static const char *fnName = "glWindowPos2fARB";

    beforeCommand(fnName, _api.glWindowPos2f);
    _api.glWindowPos2f(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2fvARB().
void ARBWindowPosAPI::windowPOS2FV(const GLfloat *v) const
{
    static const char *fnName = "glWindowPos2fvARB";

    beforeCommand(fnName, _api.glWindowPos2fv);
    _api.glWindowPos2fv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2iARB().
void ARBWindowPosAPI::windowPOS2I(GLint x, GLint y) const
{
    static const char *fnName = "glWindowPos2iARB";

    beforeCommand(fnName, _api.glWindowPos2i);
    _api.glWindowPos2i(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2ivARB().
void ARBWindowPosAPI::windowPOS2IV(const GLint *v) const
{
    static const char *fnName = "glWindowPos2ivARB";

    beforeCommand(fnName, _api.glWindowPos2iv);
    _api.glWindowPos2iv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2sARB().
void ARBWindowPosAPI::windowPOS2S(GLshort x, GLshort y) const
{
    static const char *fnName = "glWindowPos2sARB";

    beforeCommand(fnName, _api.glWindowPos2s);
    _api.glWindowPos2s(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2svARB().
void ARBWindowPosAPI::windowPOS2SV(const GLshort *v) const
{
    static const char *fnName = "glWindowPos2svARB";

    beforeCommand(fnName, _api.glWindowPos2sv);
    _api.glWindowPos2sv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3dARB().
void ARBWindowPosAPI::windowPOS3D(GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glWindowPos3dARB";

    beforeCommand(fnName, _api.glWindowPos3d);
    _api.glWindowPos3d(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3dvARB().
void ARBWindowPosAPI::windowPOS3DV(const GLdouble *v) const
{
    static const char *fnName = "glWindowPos3dvARB";

    beforeCommand(fnName, _api.glWindowPos3dv);
    _api.glWindowPos3dv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3fARB().
void ARBWindowPosAPI::windowPOS3F(GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glWindowPos3fARB";

    beforeCommand(fnName, _api.glWindowPos3f);
    _api.glWindowPos3f(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3fvARB().
void ARBWindowPosAPI::windowPOS3FV(const GLfloat *v) const
{
    static const char *fnName = "glWindowPos3fvARB";

    beforeCommand(fnName, _api.glWindowPos3fv);
    _api.glWindowPos3fv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3iARB().
void ARBWindowPosAPI::windowPOS3I(GLint x, GLint y, GLint z) const
{
    static const char *fnName = "glWindowPos3iARB";

    beforeCommand(fnName, _api.glWindowPos3i);
    _api.glWindowPos3i(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3ivARB().
void ARBWindowPosAPI::windowPOS3IV(const GLint *v) const
{
    static const char *fnName = "glWindowPos3ivARB";

    beforeCommand(fnName, _api.glWindowPos3iv);
    _api.glWindowPos3iv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3sARB().
void ARBWindowPosAPI::windowPOS3S(GLshort x, GLshort y, GLshort z) const
{
    static const char *fnName = "glWindowPos3sARB";

    beforeCommand(fnName, _api.glWindowPos3s);
    _api.glWindowPos3s(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3svARB().
void ARBWindowPosAPI::windowPOS3SV(const GLshort *v) const
{
    static const char *fnName = "glWindowPos3svARB";

    beforeCommand(fnName, _api.glWindowPos3sv);
    _api.glWindowPos3sv(v);
    afterCommand(fnName);
}

} // namespace gl


#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// ARBBufferRegionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_buffer_region extension.
ARBBufferRegionAPI::ARBBufferRegionAPI() :
    BaseExtension("WGL_ARB_buffer_region")
{
}

// Grant read-only access to the underlying function pointers.
const ARBBufferRegion &ARBBufferRegionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_buffer_region entry points.
void ARBBufferRegionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCreateBufferRegionARB().
HANDLE ARBBufferRegionAPI::createBufferRegion(HDC hDC, int iLayerPlane,
                                              UINT uType) const
{
    static const char *fnName = "wglCreateBufferRegionARB";

    beforeCommand(fnName, _api.wglCreateBufferRegion);
    HANDLE result = _api.wglCreateBufferRegion(hDC, iLayerPlane, uType);
    afterCommand(fnName);

    return result;
}

// Calls wglDeleteBufferRegionARB().
VOID ARBBufferRegionAPI::deleteBufferRegion(HANDLE hRegion) const
{
    static const char *fnName = "wglDeleteBufferRegionARB";

    beforeCommand(fnName, _api.wglDeleteBufferRegion);
    _api.wglDeleteBufferRegion(hRegion);
    afterCommand(fnName);
}

// Calls wglRestoreBufferRegionARB().
BOOL ARBBufferRegionAPI::restoreBufferRegion(HANDLE hRegion, int x, int y,
                                             int width, int height, int xSrc,
                                             int ySrc) const
{
    static const char *fnName = "wglRestoreBufferRegionARB";

    beforeCommand(fnName, _api.wglRestoreBufferRegion);
    BOOL result = _api.wglRestoreBufferRegion(hRegion, x, y, width, height, xSrc,
                                              ySrc);
    afterCommand(fnName);

    return result;
}

// Calls wglSaveBufferRegionARB().
BOOL ARBBufferRegionAPI::saveBufferRegion(HANDLE hRegion, int x, int y,
                                          int width, int height) const
{
    static const char *fnName = "wglSaveBufferRegionARB";

    beforeCommand(fnName, _api.wglSaveBufferRegion);
    BOOL result = _api.wglSaveBufferRegion(hRegion, x, y, width, height);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBCreateContextAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_create_context extension.
ARBCreateContextAPI::ARBCreateContextAPI() :
    BaseExtension("WGL_ARB_create_context")
{
}

// Grant read-only access to the underlying function pointers.
const ARBCreateContext &ARBCreateContextAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_create_context entry points.
void ARBCreateContextAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCreateContextAttribsARB().
HGLRC ARBCreateContextAPI::createContextAttribs(HDC hDC, HGLRC hShareContext,
                                                const int *attribList) const
{
    static const char *fnName = "wglCreateContextAttribsARB";

    beforeCommand(fnName, _api.wglCreateContextAttribs);
    HGLRC result = _api.wglCreateContextAttribs(hDC, hShareContext, attribList);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBExtensionsStringAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_extensions_string extension.
ARBExtensionsStringAPI::ARBExtensionsStringAPI() :
    BaseExtension("WGL_ARB_extensions_string")
{
}

// Grant read-only access to the underlying function pointers.
const ARBExtensionsString &ARBExtensionsStringAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_extensions_string entry points.
void ARBExtensionsStringAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetExtensionsStringARB().
const char *ARBExtensionsStringAPI::getExtensionsString(HDC hdc) const
{
    static const char *fnName = "wglGetExtensionsStringARB";

    beforeCommand(fnName, _api.wglGetExtensionsString);
    const char *result = _api.wglGetExtensionsString(hdc);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBMakeCurrentReadAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_make_current_read extension.
ARBMakeCurrentReadAPI::ARBMakeCurrentReadAPI() :
    BaseExtension("WGL_ARB_make_current_read")
{
}

// Grant read-only access to the underlying function pointers.
const ARBMakeCurrentRead &ARBMakeCurrentReadAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_make_current_read entry points.
void ARBMakeCurrentReadAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetCurrentReadDCARB().
HDC ARBMakeCurrentReadAPI::getCurrentReadDC() const
{
    static const char *fnName = "wglGetCurrentReadDCARB";

    beforeCommand(fnName, _api.wglGetCurrentReadDC);
    HDC result = _api.wglGetCurrentReadDC();
    afterCommand(fnName);

    return result;
}

// Calls wglMakeContextCurrentARB().
BOOL ARBMakeCurrentReadAPI::makeContextCurrent(HDC hDrawDC, HDC hReadDC,
                                               HGLRC hglrc) const
{
    static const char *fnName = "wglMakeContextCurrentARB";

    beforeCommand(fnName, _api.wglMakeContextCurrent);
    BOOL result = _api.wglMakeContextCurrent(hDrawDC, hReadDC, hglrc);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBPbufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_pbuffer extension.
ARBPbufferAPI::ARBPbufferAPI() :
    BaseExtension("WGL_ARB_pbuffer")
{
}

// Grant read-only access to the underlying function pointers.
const ARBPbuffer &ARBPbufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_pbuffer entry points.
void ARBPbufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCreatePbufferARB().
HPBUFFERARB ARBPbufferAPI::createPbuffer(HDC hDC, int iPixelFormat, int iWidth,
                                         int iHeight, const int *piAttribList) const
{
    static const char *fnName = "wglCreatePbufferARB";

    beforeCommand(fnName, _api.wglCreatePbuffer);
    HPBUFFERARB result = _api.wglCreatePbuffer(hDC, iPixelFormat, iWidth,
                                               iHeight, piAttribList);
    afterCommand(fnName);

    return result;
}

// Calls wglDestroyPbufferARB().
BOOL ARBPbufferAPI::destroyPbuffer(HPBUFFERARB hPbuffer) const
{
    static const char *fnName = "wglDestroyPbufferARB";

    beforeCommand(fnName, _api.wglDestroyPbuffer);
    BOOL result = _api.wglDestroyPbuffer(hPbuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPbufferDCARB().
HDC ARBPbufferAPI::getPbufferDC(HPBUFFERARB hPbuffer) const
{
    static const char *fnName = "wglGetPbufferDCARB";

    beforeCommand(fnName, _api.wglGetPbufferDC);
    HDC result = _api.wglGetPbufferDC(hPbuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryPbufferARB().
BOOL ARBPbufferAPI::queryPbuffer(HPBUFFERARB hPbuffer, int iAttribute,
                                 int *piValue) const
{
    static const char *fnName = "wglQueryPbufferARB";

    beforeCommand(fnName, _api.wglQueryPbuffer);
    BOOL result = _api.wglQueryPbuffer(hPbuffer, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

// Calls wglReleasePbufferDCARB().
int ARBPbufferAPI::releasePbufferDC(HPBUFFERARB hPbuffer, HDC hDC) const
{
    static const char *fnName = "wglReleasePbufferDCARB";

    beforeCommand(fnName, _api.wglReleasePbufferDC);
    int result = _api.wglReleasePbufferDC(hPbuffer, hDC);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBPixelFormatAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_pixel_format extension.
ARBPixelFormatAPI::ARBPixelFormatAPI() :
    BaseExtension("WGL_ARB_pixel_format")
{
}

// Grant read-only access to the underlying function pointers.
const ARBPixelFormat &ARBPixelFormatAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_pixel_format entry points.
void ARBPixelFormatAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglChoosePixelFormatARB().
BOOL ARBPixelFormatAPI::choosePixelFormat(HDC hdc, const int *piAttribIList,
                                          const FLOAT *pfAttribFList,
                                          UINT nMaxFormats, int *piFormats,
                                          UINT *nNumFormats) const
{
    static const char *fnName = "wglChoosePixelFormatARB";

    beforeCommand(fnName, _api.wglChoosePixelFormat);
    BOOL result = _api.wglChoosePixelFormat(hdc, piAttribIList, pfAttribFList,
                                            nMaxFormats, piFormats, nNumFormats);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPixelFormatAttribfvARB().
BOOL ARBPixelFormatAPI::getPixelFormatAttribFV(HDC hdc, int iPixelFormat,
                                               int iLayerPlane, UINT nAttributes,
                                               const int *piAttributes,
                                               FLOAT *pfValues) const
{
    static const char *fnName = "wglGetPixelFormatAttribfvARB";

    beforeCommand(fnName, _api.wglGetPixelFormatAttribfv);
    BOOL result = _api.wglGetPixelFormatAttribfv(hdc, iPixelFormat, iLayerPlane,
                                                 nAttributes, piAttributes,
                                                 pfValues);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPixelFormatAttribivARB().
BOOL ARBPixelFormatAPI::getPixelFormatAttribIV(HDC hdc, int iPixelFormat,
                                               int iLayerPlane, UINT nAttributes,
                                               const int *piAttributes,
                                               int *piValues) const
{
    static const char *fnName = "wglGetPixelFormatAttribivARB";

    beforeCommand(fnName, _api.wglGetPixelFormatAttribiv);
    BOOL result = _api.wglGetPixelFormatAttribiv(hdc, iPixelFormat, iLayerPlane,
                                                 nAttributes, piAttributes,
                                                 piValues);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBRenderTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_ARB_render_texture extension.
ARBRenderTextureAPI::ARBRenderTextureAPI() :
    BaseExtension("WGL_ARB_render_texture")
{
}

// Grant read-only access to the underlying function pointers.
const ARBRenderTexture &ARBRenderTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_ARB_render_texture entry points.
void ARBRenderTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindTexImageARB().
BOOL ARBRenderTextureAPI::bindTexImage(HPBUFFERARB hPbuffer, int iBuffer) const
{
    static const char *fnName = "wglBindTexImageARB";

    beforeCommand(fnName, _api.wglBindTexImage);
    BOOL result = _api.wglBindTexImage(hPbuffer, iBuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglReleaseTexImageARB().
BOOL ARBRenderTextureAPI::releaseTexImage(HPBUFFERARB hPbuffer, int iBuffer) const
{
    static const char *fnName = "wglReleaseTexImageARB";

    beforeCommand(fnName, _api.wglReleaseTexImage);
    BOOL result = _api.wglReleaseTexImage(hPbuffer, iBuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglSetPbufferAttribARB().
BOOL ARBRenderTextureAPI::setPbufferAttrib(HPBUFFERARB hPbuffer,
                                           const int *piAttribList) const
{
    static const char *fnName = "wglSetPbufferAttribARB";

    beforeCommand(fnName, _api.wglSetPbufferAttrib);
    BOOL result = _api.wglSetPbufferAttrib(hPbuffer, piAttribList);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// ARBCreateContextAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_ARB_create_context extension.
ARBCreateContextAPI::ARBCreateContextAPI() :
    BaseExtension("GLX_ARB_create_context")
{
}

// Grant read-only access to the underlying function pointers.
const ARBCreateContext &ARBCreateContextAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_ARB_create_context entry points.
void ARBCreateContextAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCreateContextAttribsARB().
GLXContext ARBCreateContextAPI::xCreateContextAttribs(Display *dpy,
                                                      GLXFBConfig config,
                                                      GLXContext share_context,
                                                      Bool direct,
                                                      const int *attrib_list) const
{
    static const char *fnName = "glXCreateContextAttribsARB";

    beforeCommand(fnName, _api.glXCreateContextAttribs);
    GLXContext result = _api.glXCreateContextAttribs(dpy, config, share_context,
                                                     direct, attrib_list);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ARBGetProcAddressAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_ARB_get_proc_address extension.
ARBGetProcAddressAPI::ARBGetProcAddressAPI() :
    BaseExtension("GLX_ARB_get_proc_address")
{
}

// Grant read-only access to the underlying function pointers.
const ARBGetProcAddress &ARBGetProcAddressAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_ARB_get_proc_address entry points.
void ARBGetProcAddressAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetProcAddressARB().
__GLXextFuncPtr ARBGetProcAddressAPI::xGetProcAddress(const GLubyte *procName) const
{
    static const char *fnName = "glXGetProcAddressARB";

    beforeCommand(fnName, _api.glXGetProcAddress);
    __GLXextFuncPtr result = _api.glXGetProcAddress(procName);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

