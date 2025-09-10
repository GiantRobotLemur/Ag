//! @file ObjectGL/Extensions/IntelCommands.cpp
//! @brief The definition of Intel-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/IntelCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// INTELFramebufferCmaaAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_INTEL_framebuffer_CMAA extension.
INTELFramebufferCmaaAPI::INTELFramebufferCmaaAPI() :
    BaseExtension("GL_INTEL_framebuffer_CMAA")
{
}

// Grant read-only access to the underlying function pointers.
const INTELFramebufferCmaa &INTELFramebufferCmaaAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_INTEL_framebuffer_CMAA entry points.
void INTELFramebufferCmaaAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glApplyFramebufferAttachmentCMAAINTEL().
void INTELFramebufferCmaaAPI::applyFramebufferAttachmentCmaa() const
{
    static const char *fnName = "glApplyFramebufferAttachmentCMAAINTEL";

    beforeCommand(fnName, _api.glApplyFramebufferAttachmentCMAA);
    _api.glApplyFramebufferAttachmentCMAA();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// INTELMapTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_INTEL_map_texture extension.
INTELMapTextureAPI::INTELMapTextureAPI() :
    BaseExtension("GL_INTEL_map_texture")
{
}

// Grant read-only access to the underlying function pointers.
const INTELMapTexture &INTELMapTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_INTEL_map_texture entry points.
void INTELMapTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMapTexture2DINTEL().
void *INTELMapTextureAPI::mapTexture2D(TextureName texture, GLint level,
                                       GLbitfield access, GLint *stride,
                                       GLenum *layout) const
{
    static const char *fnName = "glMapTexture2DINTEL";

    beforeCommand(fnName, _api.glMapTexture2D);
    void *result = _api.glMapTexture2D(texture.ID, level, access, stride, layout);
    afterCommand(fnName);

    return result;
}

// Calls glSyncTextureINTEL().
void INTELMapTextureAPI::syncTexture(TextureName texture) const
{
    static const char *fnName = "glSyncTextureINTEL";

    beforeCommand(fnName, _api.glSyncTexture);
    _api.glSyncTexture(texture.ID);
    afterCommand(fnName);
}

// Calls glUnmapTexture2DINTEL().
void INTELMapTextureAPI::unmapTexture2D(TextureName texture, GLint level) const
{
    static const char *fnName = "glUnmapTexture2DINTEL";

    beforeCommand(fnName, _api.glUnmapTexture2D);
    _api.glUnmapTexture2D(texture.ID, level);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// INTELParallelArraysAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_INTEL_parallel_arrays extension.
INTELParallelArraysAPI::INTELParallelArraysAPI() :
    BaseExtension("GL_INTEL_parallel_arrays")
{
}

// Grant read-only access to the underlying function pointers.
const INTELParallelArrays &INTELParallelArraysAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_INTEL_parallel_arrays entry points.
void INTELParallelArraysAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorPointervINTEL().
void INTELParallelArraysAPI::colorPointerV(GLint size, VertexPointerType type,
                                           const void **pointer) const
{
    static const char *fnName = "glColorPointervINTEL";

    beforeCommand(fnName, _api.glColorPointerv);
    _api.glColorPointerv(size, toScalar(type), pointer);
    afterCommand(fnName);
}

// Calls glNormalPointervINTEL().
void INTELParallelArraysAPI::normalPointerV(NormalPointerType type,
                                            const void **pointer) const
{
    static const char *fnName = "glNormalPointervINTEL";

    beforeCommand(fnName, _api.glNormalPointerv);
    _api.glNormalPointerv(toScalar(type), pointer);
    afterCommand(fnName);
}

// Calls glTexCoordPointervINTEL().
void INTELParallelArraysAPI::texCoordPointerV(GLint size, VertexPointerType type,
                                              const void **pointer) const
{
    static const char *fnName = "glTexCoordPointervINTEL";

    beforeCommand(fnName, _api.glTexCoordPointerv);
    _api.glTexCoordPointerv(size, toScalar(type), pointer);
    afterCommand(fnName);
}

// Calls glVertexPointervINTEL().
void INTELParallelArraysAPI::vertexPointerV(GLint size, VertexPointerType type,
                                            const void **pointer) const
{
    static const char *fnName = "glVertexPointervINTEL";

    beforeCommand(fnName, _api.glVertexPointerv);
    _api.glVertexPointerv(size, toScalar(type), pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// INTELPerformanceQueryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_INTEL_performance_query extension.
INTELPerformanceQueryAPI::INTELPerformanceQueryAPI() :
    BaseExtension("GL_INTEL_performance_query")
{
}

// Grant read-only access to the underlying function pointers.
const INTELPerformanceQuery &INTELPerformanceQueryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_INTEL_performance_query entry points.
void INTELPerformanceQueryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginPerfQueryINTEL().
void INTELPerformanceQueryAPI::beginPerfQuery(GLuint queryHandle) const
{
    static const char *fnName = "glBeginPerfQueryINTEL";

    beforeCommand(fnName, _api.glBeginPerfQuery);
    _api.glBeginPerfQuery(queryHandle);
    afterCommand(fnName);
}

// Calls glCreatePerfQueryINTEL().
void INTELPerformanceQueryAPI::createPerfQuery(GLuint queryId,
                                               GLuint *queryHandle) const
{
    static const char *fnName = "glCreatePerfQueryINTEL";

    beforeCommand(fnName, _api.glCreatePerfQuery);
    _api.glCreatePerfQuery(queryId, queryHandle);
    afterCommand(fnName);
}

// Calls glDeletePerfQueryINTEL().
void INTELPerformanceQueryAPI::deletePerfQuery(GLuint queryHandle) const
{
    static const char *fnName = "glDeletePerfQueryINTEL";

    beforeCommand(fnName, _api.glDeletePerfQuery);
    _api.glDeletePerfQuery(queryHandle);
    afterCommand(fnName);
}

// Calls glEndPerfQueryINTEL().
void INTELPerformanceQueryAPI::endPerfQuery(GLuint queryHandle) const
{
    static const char *fnName = "glEndPerfQueryINTEL";

    beforeCommand(fnName, _api.glEndPerfQuery);
    _api.glEndPerfQuery(queryHandle);
    afterCommand(fnName);
}

// Calls glGetFirstPerfQueryIdINTEL().
void INTELPerformanceQueryAPI::getFirstPerfQueryID(GLuint *queryId) const
{
    static const char *fnName = "glGetFirstPerfQueryIdINTEL";

    beforeCommand(fnName, _api.glGetFirstPerfQueryId);
    _api.glGetFirstPerfQueryId(queryId);
    afterCommand(fnName);
}

// Calls glGetNextPerfQueryIdINTEL().
void INTELPerformanceQueryAPI::getNextPerfQueryID(GLuint queryId,
                                                  GLuint *nextQueryId) const
{
    static const char *fnName = "glGetNextPerfQueryIdINTEL";

    beforeCommand(fnName, _api.glGetNextPerfQueryId);
    _api.glGetNextPerfQueryId(queryId, nextQueryId);
    afterCommand(fnName);
}

// Calls glGetPerfCounterInfoINTEL().
void INTELPerformanceQueryAPI::getPerfCounterInfo(GLuint queryId,
                                                  GLuint counterId,
                                                  GLuint counterNameLength,
                                                  GLchar *counterName,
                                                  GLuint counterDescLength,
                                                  GLchar *counterDesc,
                                                  GLuint *counterOffset,
                                                  GLuint *counterDataSize,
                                                  GLuint *counterTypeEnum,
                                                  GLuint *counterDataTypeEnum,
                                                  GLuint64 *rawCounterMaxValue) const
{
    static const char *fnName = "glGetPerfCounterInfoINTEL";

    beforeCommand(fnName, _api.glGetPerfCounterInfo);
    _api.glGetPerfCounterInfo(queryId, counterId, counterNameLength, counterName,
                              counterDescLength, counterDesc, counterOffset,
                              counterDataSize, counterTypeEnum,
                              counterDataTypeEnum, rawCounterMaxValue);
    afterCommand(fnName);
}

// Calls glGetPerfQueryDataINTEL().
void INTELPerformanceQueryAPI::getPerfQueryData(GLuint queryHandle, GLuint flags,
                                                GLsizei dataSize, void *data,
                                                GLuint *bytesWritten) const
{
    static const char *fnName = "glGetPerfQueryDataINTEL";

    beforeCommand(fnName, _api.glGetPerfQueryData);
    _api.glGetPerfQueryData(queryHandle, flags, dataSize, data, bytesWritten);
    afterCommand(fnName);
}

// Calls glGetPerfQueryIdByNameINTEL().
void INTELPerformanceQueryAPI::getPerfQueryIDByName(GLchar *queryName,
                                                    GLuint *queryId) const
{
    static const char *fnName = "glGetPerfQueryIdByNameINTEL";

    beforeCommand(fnName, _api.glGetPerfQueryIdByName);
    _api.glGetPerfQueryIdByName(queryName, queryId);
    afterCommand(fnName);
}

// Calls glGetPerfQueryInfoINTEL().
void INTELPerformanceQueryAPI::getPerfQueryInfo(GLuint queryId,
                                                GLuint queryNameLength,
                                                GLchar *queryName,
                                                GLuint *dataSize,
                                                GLuint *noCounters,
                                                GLuint *noInstances,
                                                GLuint *capsMask) const
{
    static const char *fnName = "glGetPerfQueryInfoINTEL";

    beforeCommand(fnName, _api.glGetPerfQueryInfo);
    _api.glGetPerfQueryInfo(queryId, queryNameLength, queryName, dataSize,
                            noCounters, noInstances, capsMask);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

