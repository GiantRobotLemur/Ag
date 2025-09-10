//! @file Ag/ObjectGL/Extensions/IntelCommands.hpp
//! @brief The declaration of Intel-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_INTEL_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_INTEL_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "Intel.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_INTEL_framebuffer_CMAA extension API.
class INTELFramebufferCmaaAPI : public BaseExtension
{
public:
    // Construction
    INTELFramebufferCmaaAPI();

    // Accessors
    const INTELFramebufferCmaa &getRawAPI() const;

    // Operations
    void applyFramebufferAttachmentCmaa() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    INTELFramebufferCmaa _api;
};

// Manages the entry points for the GL_INTEL_map_texture extension API.
class INTELMapTextureAPI : public BaseExtension
{
public:
    // Construction
    INTELMapTextureAPI();

    // Accessors
    const INTELMapTexture &getRawAPI() const;

    // Operations
    void *mapTexture2D(TextureName texture, GLint level, GLbitfield access,
                       GLint *stride, GLenum *layout) const;
    void syncTexture(TextureName texture) const;
    void unmapTexture2D(TextureName texture, GLint level) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    INTELMapTexture _api;
};

// Manages the entry points for the GL_INTEL_parallel_arrays extension API.
class INTELParallelArraysAPI : public BaseExtension
{
public:
    // Construction
    INTELParallelArraysAPI();

    // Accessors
    const INTELParallelArrays &getRawAPI() const;

    // Operations
    void colorPointerV(GLint size, VertexPointerType type, const void **pointer) const;
    void normalPointerV(NormalPointerType type, const void **pointer) const;
    void texCoordPointerV(GLint size, VertexPointerType type,
                          const void **pointer) const;
    void vertexPointerV(GLint size, VertexPointerType type, const void **pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    INTELParallelArrays _api;
};

// Manages the entry points for the GL_INTEL_performance_query extension API.
class INTELPerformanceQueryAPI : public BaseExtension
{
public:
    // Construction
    INTELPerformanceQueryAPI();

    // Accessors
    const INTELPerformanceQuery &getRawAPI() const;

    // Operations
    void beginPerfQuery(GLuint queryHandle) const;
    void createPerfQuery(GLuint queryId, GLuint *queryHandle) const;
    void deletePerfQuery(GLuint queryHandle) const;
    void endPerfQuery(GLuint queryHandle) const;
    void getFirstPerfQueryID(GLuint *queryId) const;
    void getNextPerfQueryID(GLuint queryId, GLuint *nextQueryId) const;
    void getPerfCounterInfo(GLuint queryId, GLuint counterId,
                            GLuint counterNameLength, GLchar *counterName,
                            GLuint counterDescLength, GLchar *counterDesc,
                            GLuint *counterOffset, GLuint *counterDataSize,
                            GLuint *counterTypeEnum, GLuint *counterDataTypeEnum,
                            GLuint64 *rawCounterMaxValue) const;
    void getPerfQueryData(GLuint queryHandle, GLuint flags, GLsizei dataSize,
                          void *data, GLuint *bytesWritten) const;
    void getPerfQueryIDByName(GLchar *queryName, GLuint *queryId) const;
    void getPerfQueryInfo(GLuint queryId, GLuint queryNameLength,
                          GLchar *queryName, GLuint *dataSize,
                          GLuint *noCounters, GLuint *noInstances,
                          GLuint *capsMask) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    INTELPerformanceQuery _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
