//! @file ObjectGL/Extensions/Apple.cpp
//! @brief The definition of Apple-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Apple.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __APPLEElementArrayEntryPoints[] = {
    { offsetof(APPLEElementArray, glDrawElementArray), "glDrawElementArrayAPPLE" },
    { offsetof(APPLEElementArray, glDrawRangeElementArray), "glDrawRangeElementArrayAPPLE" },
    { offsetof(APPLEElementArray, glElementPointer), "glElementPointerAPPLE" },
    { offsetof(APPLEElementArray, glMultiDrawElementArray), "glMultiDrawElementArrayAPPLE" },
    { offsetof(APPLEElementArray, glMultiDrawRangeElementArray), "glMultiDrawRangeElementArrayAPPLE" },
};

static const EntryOffset __APPLEFenceEntryPoints[] = {
    { offsetof(APPLEFence, glDeleteFences), "glDeleteFencesAPPLE" },
    { offsetof(APPLEFence, glFinishFence), "glFinishFenceAPPLE" },
    { offsetof(APPLEFence, glFinishObject), "glFinishObjectAPPLE" },
    { offsetof(APPLEFence, glGenFences), "glGenFencesAPPLE" },
    { offsetof(APPLEFence, glIsFence), "glIsFenceAPPLE" },
    { offsetof(APPLEFence, glSetFence), "glSetFenceAPPLE" },
    { offsetof(APPLEFence, glTestFence), "glTestFenceAPPLE" },
    { offsetof(APPLEFence, glTestObject), "glTestObjectAPPLE" },
};

static const EntryOffset __APPLEFlushBufferRangeEntryPoints[] = {
    { offsetof(APPLEFlushBufferRange, glBufferParameteri), "glBufferParameteriAPPLE" },
    { offsetof(APPLEFlushBufferRange, glFlushMappedBufferRange), "glFlushMappedBufferRangeAPPLE" },
};

static const EntryOffset __APPLEObjectPurgeableEntryPoints[] = {
    { offsetof(APPLEObjectPurgeable, glGetObjectParameteriv), "glGetObjectParameterivAPPLE" },
    { offsetof(APPLEObjectPurgeable, glObjectPurgeable), "glObjectPurgeableAPPLE" },
    { offsetof(APPLEObjectPurgeable, glObjectUnpurgeable), "glObjectUnpurgeableAPPLE" },
};

static const EntryOffset __APPLETextureRangeEntryPoints[] = {
    { offsetof(APPLETextureRange, glGetTexParameterPointerv), "glGetTexParameterPointervAPPLE" },
    { offsetof(APPLETextureRange, glTextureRange), "glTextureRangeAPPLE" },
};

static const EntryOffset __APPLEVertexArrayObjectEntryPoints[] = {
    { offsetof(APPLEVertexArrayObject, glBindVertexArray), "glBindVertexArrayAPPLE" },
    { offsetof(APPLEVertexArrayObject, glDeleteVertexArrays), "glDeleteVertexArraysAPPLE" },
    { offsetof(APPLEVertexArrayObject, glGenVertexArrays), "glGenVertexArraysAPPLE" },
    { offsetof(APPLEVertexArrayObject, glIsVertexArray), "glIsVertexArrayAPPLE" },
};

static const EntryOffset __APPLEVertexArrayRangeEntryPoints[] = {
    { offsetof(APPLEVertexArrayRange, glFlushVertexArrayRange), "glFlushVertexArrayRangeAPPLE" },
    { offsetof(APPLEVertexArrayRange, glVertexArrayParameteri), "glVertexArrayParameteriAPPLE" },
    { offsetof(APPLEVertexArrayRange, glVertexArrayRange), "glVertexArrayRangeAPPLE" },
};

static const EntryOffset __APPLEVertexProgramEvaluatorsEntryPoints[] = {
    { offsetof(APPLEVertexProgramEvaluators, glDisableVertexAttrib), "glDisableVertexAttribAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glEnableVertexAttrib), "glEnableVertexAttribAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glIsVertexAttribEnabled), "glIsVertexAttribEnabledAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glMapVertexAttrib1d), "glMapVertexAttrib1dAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glMapVertexAttrib1f), "glMapVertexAttrib1fAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glMapVertexAttrib2d), "glMapVertexAttrib2dAPPLE" },
    { offsetof(APPLEVertexProgramEvaluators, glMapVertexAttrib2f), "glMapVertexAttrib2fAPPLE" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// APPLEElementArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEElementArray::APPLEElementArray()
{
    std::for_each_n(__APPLEElementArrayEntryPoints,
                    std::size(__APPLEElementArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEElementArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_element_array");
}

void APPLEElementArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEElementArrayEntryPoints,
                    std::size(__APPLEElementArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEFence Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEFence::APPLEFence()
{
    std::for_each_n(__APPLEFenceEntryPoints,
                    std::size(__APPLEFenceEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEFence::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_fence");
}

void APPLEFence::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEFenceEntryPoints,
                    std::size(__APPLEFenceEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEFlushBufferRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEFlushBufferRange::APPLEFlushBufferRange()
{
    std::for_each_n(__APPLEFlushBufferRangeEntryPoints,
                    std::size(__APPLEFlushBufferRangeEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEFlushBufferRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_flush_buffer_range");
}

void APPLEFlushBufferRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEFlushBufferRangeEntryPoints,
                    std::size(__APPLEFlushBufferRangeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEObjectPurgeable Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEObjectPurgeable::APPLEObjectPurgeable()
{
    std::for_each_n(__APPLEObjectPurgeableEntryPoints,
                    std::size(__APPLEObjectPurgeableEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEObjectPurgeable::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_object_purgeable");
}

void APPLEObjectPurgeable::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEObjectPurgeableEntryPoints,
                    std::size(__APPLEObjectPurgeableEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLETextureRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLETextureRange::APPLETextureRange()
{
    std::for_each_n(__APPLETextureRangeEntryPoints,
                    std::size(__APPLETextureRangeEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLETextureRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_texture_range");
}

void APPLETextureRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLETextureRangeEntryPoints,
                    std::size(__APPLETextureRangeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexArrayObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEVertexArrayObject::APPLEVertexArrayObject()
{
    std::for_each_n(__APPLEVertexArrayObjectEntryPoints,
                    std::size(__APPLEVertexArrayObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEVertexArrayObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_vertex_array_object");
}

void APPLEVertexArrayObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEVertexArrayObjectEntryPoints,
                    std::size(__APPLEVertexArrayObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexArrayRange Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEVertexArrayRange::APPLEVertexArrayRange()
{
    std::for_each_n(__APPLEVertexArrayRangeEntryPoints,
                    std::size(__APPLEVertexArrayRangeEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEVertexArrayRange::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_vertex_array_range");
}

void APPLEVertexArrayRange::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEVertexArrayRangeEntryPoints,
                    std::size(__APPLEVertexArrayRangeEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexProgramEvaluators Member Definitions
////////////////////////////////////////////////////////////////////////////////
APPLEVertexProgramEvaluators::APPLEVertexProgramEvaluators()
{
    std::for_each_n(__APPLEVertexProgramEvaluatorsEntryPoints,
                    std::size(__APPLEVertexProgramEvaluatorsEntryPoints),
                    ClearEntryPoint(this));
}

bool APPLEVertexProgramEvaluators::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_APPLE_vertex_program_evaluators");
}

void APPLEVertexProgramEvaluators::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__APPLEVertexProgramEvaluatorsEntryPoints,
                    std::size(__APPLEVertexProgramEvaluatorsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

