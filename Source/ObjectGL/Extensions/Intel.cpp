//! @file ObjectGL/Extensions/Intel.cpp
//! @brief The definition of Intel-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Intel.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __INTELFramebufferCmaaEntryPoints[] = {
    { offsetof(INTELFramebufferCmaa, glApplyFramebufferAttachmentCMAA), "glApplyFramebufferAttachmentCMAAINTEL" },
};

static const EntryOffset __INTELMapTextureEntryPoints[] = {
    { offsetof(INTELMapTexture, glMapTexture2D), "glMapTexture2DINTEL" },
    { offsetof(INTELMapTexture, glSyncTexture), "glSyncTextureINTEL" },
    { offsetof(INTELMapTexture, glUnmapTexture2D), "glUnmapTexture2DINTEL" },
};

static const EntryOffset __INTELParallelArraysEntryPoints[] = {
    { offsetof(INTELParallelArrays, glColorPointerv), "glColorPointervINTEL" },
    { offsetof(INTELParallelArrays, glNormalPointerv), "glNormalPointervINTEL" },
    { offsetof(INTELParallelArrays, glTexCoordPointerv), "glTexCoordPointervINTEL" },
    { offsetof(INTELParallelArrays, glVertexPointerv), "glVertexPointervINTEL" },
};

static const EntryOffset __INTELPerformanceQueryEntryPoints[] = {
    { offsetof(INTELPerformanceQuery, glBeginPerfQuery), "glBeginPerfQueryINTEL" },
    { offsetof(INTELPerformanceQuery, glCreatePerfQuery), "glCreatePerfQueryINTEL" },
    { offsetof(INTELPerformanceQuery, glDeletePerfQuery), "glDeletePerfQueryINTEL" },
    { offsetof(INTELPerformanceQuery, glEndPerfQuery), "glEndPerfQueryINTEL" },
    { offsetof(INTELPerformanceQuery, glGetFirstPerfQueryId), "glGetFirstPerfQueryIdINTEL" },
    { offsetof(INTELPerformanceQuery, glGetNextPerfQueryId), "glGetNextPerfQueryIdINTEL" },
    { offsetof(INTELPerformanceQuery, glGetPerfCounterInfo), "glGetPerfCounterInfoINTEL" },
    { offsetof(INTELPerformanceQuery, glGetPerfQueryData), "glGetPerfQueryDataINTEL" },
    { offsetof(INTELPerformanceQuery, glGetPerfQueryIdByName), "glGetPerfQueryIdByNameINTEL" },
    { offsetof(INTELPerformanceQuery, glGetPerfQueryInfo), "glGetPerfQueryInfoINTEL" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// INTELFramebufferCmaa Member Definitions
////////////////////////////////////////////////////////////////////////////////
INTELFramebufferCmaa::INTELFramebufferCmaa()
{
    std::for_each_n(__INTELFramebufferCmaaEntryPoints,
                    std::size(__INTELFramebufferCmaaEntryPoints),
                    ClearEntryPoint(this));
}

bool INTELFramebufferCmaa::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_INTEL_framebuffer_CMAA");
}

void INTELFramebufferCmaa::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__INTELFramebufferCmaaEntryPoints,
                    std::size(__INTELFramebufferCmaaEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// INTELMapTexture Member Definitions
////////////////////////////////////////////////////////////////////////////////
INTELMapTexture::INTELMapTexture()
{
    std::for_each_n(__INTELMapTextureEntryPoints,
                    std::size(__INTELMapTextureEntryPoints),
                    ClearEntryPoint(this));
}

bool INTELMapTexture::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_INTEL_map_texture");
}

void INTELMapTexture::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__INTELMapTextureEntryPoints,
                    std::size(__INTELMapTextureEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// INTELParallelArrays Member Definitions
////////////////////////////////////////////////////////////////////////////////
INTELParallelArrays::INTELParallelArrays()
{
    std::for_each_n(__INTELParallelArraysEntryPoints,
                    std::size(__INTELParallelArraysEntryPoints),
                    ClearEntryPoint(this));
}

bool INTELParallelArrays::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_INTEL_parallel_arrays");
}

void INTELParallelArrays::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__INTELParallelArraysEntryPoints,
                    std::size(__INTELParallelArraysEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// INTELPerformanceQuery Member Definitions
////////////////////////////////////////////////////////////////////////////////
INTELPerformanceQuery::INTELPerformanceQuery()
{
    std::for_each_n(__INTELPerformanceQueryEntryPoints,
                    std::size(__INTELPerformanceQueryEntryPoints),
                    ClearEntryPoint(this));
}

bool INTELPerformanceQuery::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_INTEL_performance_query");
}

void INTELPerformanceQuery::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__INTELPerformanceQueryEntryPoints,
                    std::size(__INTELPerformanceQueryEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

