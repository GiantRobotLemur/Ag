//! @file Ag/ObjectGL/Extensions/Intel.hpp
//! @brief The declaration of Intel-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_INTEL_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_INTEL_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_INTEL_framebuffer_CMAA extension API specification.
struct INTELFramebufferCmaa {
    // Public Members
    void (APIENTRY *glApplyFramebufferAttachmentCMAA)();

    // Construction
    INTELFramebufferCmaa();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct INTELFramebufferCmaa

// GL_INTEL_map_texture extension API specification.
struct INTELMapTexture {
    // Public Members
    void *(APIENTRY *glMapTexture2D)(GLuint texture, GLint level,
                                     GLbitfield access, GLint *stride,
                                     GLenum *layout);
    void (APIENTRY *glSyncTexture)(GLuint texture);
    void (APIENTRY *glUnmapTexture2D)(GLuint texture, GLint level);

    // Construction
    INTELMapTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct INTELMapTexture

// GL_INTEL_parallel_arrays extension API specification.
struct INTELParallelArrays {
    // Public Members
    void (APIENTRY *glColorPointerv)(GLint size, GLenum type,
                                     const void **pointer);
    void (APIENTRY *glNormalPointerv)(GLenum type, const void **pointer);
    void (APIENTRY *glTexCoordPointerv)(GLint size, GLenum type,
                                        const void **pointer);
    void (APIENTRY *glVertexPointerv)(GLint size, GLenum type,
                                      const void **pointer);

    // Construction
    INTELParallelArrays();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct INTELParallelArrays

// GL_INTEL_performance_query extension API specification.
struct INTELPerformanceQuery {
    // Public Members
    void (APIENTRY *glBeginPerfQuery)(GLuint queryHandle);
    void (APIENTRY *glCreatePerfQuery)(GLuint queryId, GLuint *queryHandle);
    void (APIENTRY *glDeletePerfQuery)(GLuint queryHandle);
    void (APIENTRY *glEndPerfQuery)(GLuint queryHandle);
    void (APIENTRY *glGetFirstPerfQueryId)(GLuint *queryId);
    void (APIENTRY *glGetNextPerfQueryId)(GLuint queryId, GLuint *nextQueryId);
    void (APIENTRY *glGetPerfCounterInfo)(GLuint queryId, GLuint counterId,
                                          GLuint counterNameLength,
                                          GLchar *counterName,
                                          GLuint counterDescLength,
                                          GLchar *counterDesc,
                                          GLuint *counterOffset,
                                          GLuint *counterDataSize,
                                          GLuint *counterTypeEnum,
                                          GLuint *counterDataTypeEnum,
                                          GLuint64 *rawCounterMaxValue);
    void (APIENTRY *glGetPerfQueryData)(GLuint queryHandle, GLuint flags,
                                        GLsizei dataSize, void *data,
                                        GLuint *bytesWritten);
    void (APIENTRY *glGetPerfQueryIdByName)(GLchar *queryName, GLuint *queryId);
    void (APIENTRY *glGetPerfQueryInfo)(GLuint queryId, GLuint queryNameLength,
                                        GLchar *queryName, GLuint *dataSize,
                                        GLuint *noCounters, GLuint *noInstances,
                                        GLuint *capsMask);

    // Construction
    INTELPerformanceQuery();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct INTELPerformanceQuery

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
