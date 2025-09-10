//! @file ObjectGL/Extensions/ATI.cpp
//! @brief The definition of ATI-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/ATI.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __ATIDrawBuffersEntryPoints[] = {
    { offsetof(ATIDrawBuffers, glDrawBuffers), "glDrawBuffersATI" },
};

static const EntryOffset __ATIElementArrayEntryPoints[] = {
    { offsetof(ATIElementArray, glDrawElementArray), "glDrawElementArrayATI" },
    { offsetof(ATIElementArray, glDrawRangeElementArray), "glDrawRangeElementArrayATI" },
    { offsetof(ATIElementArray, glElementPointer), "glElementPointerATI" },
};

static const EntryOffset __ATIEnvmapBumpmapEntryPoints[] = {
    { offsetof(ATIEnvmapBumpmap, glGetTexBumpParameterfv), "glGetTexBumpParameterfvATI" },
    { offsetof(ATIEnvmapBumpmap, glGetTexBumpParameteriv), "glGetTexBumpParameterivATI" },
    { offsetof(ATIEnvmapBumpmap, glTexBumpParameterfv), "glTexBumpParameterfvATI" },
    { offsetof(ATIEnvmapBumpmap, glTexBumpParameteriv), "glTexBumpParameterivATI" },
};

static const EntryOffset __ATIFragmentShaderEntryPoints[] = {
    { offsetof(ATIFragmentShader, glAlphaFragmentOp1), "glAlphaFragmentOp1ATI" },
    { offsetof(ATIFragmentShader, glAlphaFragmentOp2), "glAlphaFragmentOp2ATI" },
    { offsetof(ATIFragmentShader, glAlphaFragmentOp3), "glAlphaFragmentOp3ATI" },
    { offsetof(ATIFragmentShader, glBeginFragmentShader), "glBeginFragmentShaderATI" },
    { offsetof(ATIFragmentShader, glBindFragmentShader), "glBindFragmentShaderATI" },
    { offsetof(ATIFragmentShader, glColorFragmentOp1), "glColorFragmentOp1ATI" },
    { offsetof(ATIFragmentShader, glColorFragmentOp2), "glColorFragmentOp2ATI" },
    { offsetof(ATIFragmentShader, glColorFragmentOp3), "glColorFragmentOp3ATI" },
    { offsetof(ATIFragmentShader, glDeleteFragmentShader), "glDeleteFragmentShaderATI" },
    { offsetof(ATIFragmentShader, glEndFragmentShader), "glEndFragmentShaderATI" },
    { offsetof(ATIFragmentShader, glGenFragmentShaders), "glGenFragmentShadersATI" },
    { offsetof(ATIFragmentShader, glPassTexCoord), "glPassTexCoordATI" },
    { offsetof(ATIFragmentShader, glSampleMap), "glSampleMapATI" },
    { offsetof(ATIFragmentShader, glSetFragmentShaderConstant), "glSetFragmentShaderConstantATI" },
};

static const EntryOffset __ATIMapObjectBufferEntryPoints[] = {
    { offsetof(ATIMapObjectBuffer, glMapObjectBuffer), "glMapObjectBufferATI" },
    { offsetof(ATIMapObjectBuffer, glUnmapObjectBuffer), "glUnmapObjectBufferATI" },
};

static const EntryOffset __ATIPnTrianglesEntryPoints[] = {
    { offsetof(ATIPnTriangles, glPNTrianglesf), "glPNTrianglesfATI" },
    { offsetof(ATIPnTriangles, glPNTrianglesi), "glPNTrianglesiATI" },
};

static const EntryOffset __ATISeparateStencilEntryPoints[] = {
    { offsetof(ATISeparateStencil, glStencilFuncSeparate), "glStencilFuncSeparateATI" },
    { offsetof(ATISeparateStencil, glStencilOpSeparate), "glStencilOpSeparateATI" },
};

static const EntryOffset __ATIVertexArrayObjectEntryPoints[] = {
    { offsetof(ATIVertexArrayObject, glArrayObject), "glArrayObjectATI" },
    { offsetof(ATIVertexArrayObject, glFreeObjectBuffer), "glFreeObjectBufferATI" },
    { offsetof(ATIVertexArrayObject, glGetArrayObjectfv), "glGetArrayObjectfvATI" },
    { offsetof(ATIVertexArrayObject, glGetArrayObjectiv), "glGetArrayObjectivATI" },
    { offsetof(ATIVertexArrayObject, glGetObjectBufferfv), "glGetObjectBufferfvATI" },
    { offsetof(ATIVertexArrayObject, glGetObjectBufferiv), "glGetObjectBufferivATI" },
    { offsetof(ATIVertexArrayObject, glGetVariantArrayObjectfv), "glGetVariantArrayObjectfvATI" },
    { offsetof(ATIVertexArrayObject, glGetVariantArrayObjectiv), "glGetVariantArrayObjectivATI" },
    { offsetof(ATIVertexArrayObject, glIsObjectBuffer), "glIsObjectBufferATI" },
    { offsetof(ATIVertexArrayObject, glNewObjectBuffer), "glNewObjectBufferATI" },
    { offsetof(ATIVertexArrayObject, glUpdateObjectBuffer), "glUpdateObjectBufferATI" },
    { offsetof(ATIVertexArrayObject, glVariantArrayObject), "glVariantArrayObjectATI" },
};

static const EntryOffset __ATIVertexAttribArrayObjectEntryPoints[] = {
    { offsetof(ATIVertexAttribArrayObject, glGetVertexAttribArrayObjectfv), "glGetVertexAttribArrayObjectfvATI" },
    { offsetof(ATIVertexAttribArrayObject, glGetVertexAttribArrayObjectiv), "glGetVertexAttribArrayObjectivATI" },
    { offsetof(ATIVertexAttribArrayObject, glVertexAttribArrayObject), "glVertexAttribArrayObjectATI" },
};

static const EntryOffset __ATIVertexStreamsEntryPoints[] = {
    { offsetof(ATIVertexStreams, glClientActiveVertexStream), "glClientActiveVertexStreamATI" },
    { offsetof(ATIVertexStreams, glNormalStream3b), "glNormalStream3bATI" },
    { offsetof(ATIVertexStreams, glNormalStream3bv), "glNormalStream3bvATI" },
    { offsetof(ATIVertexStreams, glNormalStream3d), "glNormalStream3dATI" },
    { offsetof(ATIVertexStreams, glNormalStream3dv), "glNormalStream3dvATI" },
    { offsetof(ATIVertexStreams, glNormalStream3f), "glNormalStream3fATI" },
    { offsetof(ATIVertexStreams, glNormalStream3fv), "glNormalStream3fvATI" },
    { offsetof(ATIVertexStreams, glNormalStream3i), "glNormalStream3iATI" },
    { offsetof(ATIVertexStreams, glNormalStream3iv), "glNormalStream3ivATI" },
    { offsetof(ATIVertexStreams, glNormalStream3s), "glNormalStream3sATI" },
    { offsetof(ATIVertexStreams, glNormalStream3sv), "glNormalStream3svATI" },
    { offsetof(ATIVertexStreams, glVertexBlendEnvf), "glVertexBlendEnvfATI" },
    { offsetof(ATIVertexStreams, glVertexBlendEnvi), "glVertexBlendEnviATI" },
    { offsetof(ATIVertexStreams, glVertexStream1d), "glVertexStream1dATI" },
    { offsetof(ATIVertexStreams, glVertexStream1dv), "glVertexStream1dvATI" },
    { offsetof(ATIVertexStreams, glVertexStream1f), "glVertexStream1fATI" },
    { offsetof(ATIVertexStreams, glVertexStream1fv), "glVertexStream1fvATI" },
    { offsetof(ATIVertexStreams, glVertexStream1i), "glVertexStream1iATI" },
    { offsetof(ATIVertexStreams, glVertexStream1iv), "glVertexStream1ivATI" },
    { offsetof(ATIVertexStreams, glVertexStream1s), "glVertexStream1sATI" },
    { offsetof(ATIVertexStreams, glVertexStream1sv), "glVertexStream1svATI" },
    { offsetof(ATIVertexStreams, glVertexStream2d), "glVertexStream2dATI" },
    { offsetof(ATIVertexStreams, glVertexStream2dv), "glVertexStream2dvATI" },
    { offsetof(ATIVertexStreams, glVertexStream2f), "glVertexStream2fATI" },
    { offsetof(ATIVertexStreams, glVertexStream2fv), "glVertexStream2fvATI" },
    { offsetof(ATIVertexStreams, glVertexStream2i), "glVertexStream2iATI" },
    { offsetof(ATIVertexStreams, glVertexStream2iv), "glVertexStream2ivATI" },
    { offsetof(ATIVertexStreams, glVertexStream2s), "glVertexStream2sATI" },
    { offsetof(ATIVertexStreams, glVertexStream2sv), "glVertexStream2svATI" },
    { offsetof(ATIVertexStreams, glVertexStream3d), "glVertexStream3dATI" },
    { offsetof(ATIVertexStreams, glVertexStream3dv), "glVertexStream3dvATI" },
    { offsetof(ATIVertexStreams, glVertexStream3f), "glVertexStream3fATI" },
    { offsetof(ATIVertexStreams, glVertexStream3fv), "glVertexStream3fvATI" },
    { offsetof(ATIVertexStreams, glVertexStream3i), "glVertexStream3iATI" },
    { offsetof(ATIVertexStreams, glVertexStream3iv), "glVertexStream3ivATI" },
    { offsetof(ATIVertexStreams, glVertexStream3s), "glVertexStream3sATI" },
    { offsetof(ATIVertexStreams, glVertexStream3sv), "glVertexStream3svATI" },
    { offsetof(ATIVertexStreams, glVertexStream4d), "glVertexStream4dATI" },
    { offsetof(ATIVertexStreams, glVertexStream4dv), "glVertexStream4dvATI" },
    { offsetof(ATIVertexStreams, glVertexStream4f), "glVertexStream4fATI" },
    { offsetof(ATIVertexStreams, glVertexStream4fv), "glVertexStream4fvATI" },
    { offsetof(ATIVertexStreams, glVertexStream4i), "glVertexStream4iATI" },
    { offsetof(ATIVertexStreams, glVertexStream4iv), "glVertexStream4ivATI" },
    { offsetof(ATIVertexStreams, glVertexStream4s), "glVertexStream4sATI" },
    { offsetof(ATIVertexStreams, glVertexStream4sv), "glVertexStream4svATI" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ATIDrawBuffers Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIDrawBuffers::ATIDrawBuffers()
{
    std::for_each_n(__ATIDrawBuffersEntryPoints,
                    std::size(__ATIDrawBuffersEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIDrawBuffers::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_draw_buffers");
}

void ATIDrawBuffers::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIDrawBuffersEntryPoints,
                    std::size(__ATIDrawBuffersEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIElementArray Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIElementArray::ATIElementArray()
{
    std::for_each_n(__ATIElementArrayEntryPoints,
                    std::size(__ATIElementArrayEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIElementArray::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_element_array");
}

void ATIElementArray::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIElementArrayEntryPoints,
                    std::size(__ATIElementArrayEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIEnvmapBumpmap Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIEnvmapBumpmap::ATIEnvmapBumpmap()
{
    std::for_each_n(__ATIEnvmapBumpmapEntryPoints,
                    std::size(__ATIEnvmapBumpmapEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIEnvmapBumpmap::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_envmap_bumpmap");
}

void ATIEnvmapBumpmap::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIEnvmapBumpmapEntryPoints,
                    std::size(__ATIEnvmapBumpmapEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIFragmentShader Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIFragmentShader::ATIFragmentShader()
{
    std::for_each_n(__ATIFragmentShaderEntryPoints,
                    std::size(__ATIFragmentShaderEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIFragmentShader::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_fragment_shader");
}

void ATIFragmentShader::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIFragmentShaderEntryPoints,
                    std::size(__ATIFragmentShaderEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIMapObjectBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIMapObjectBuffer::ATIMapObjectBuffer()
{
    std::for_each_n(__ATIMapObjectBufferEntryPoints,
                    std::size(__ATIMapObjectBufferEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIMapObjectBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_map_object_buffer");
}

void ATIMapObjectBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIMapObjectBufferEntryPoints,
                    std::size(__ATIMapObjectBufferEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIPnTriangles Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIPnTriangles::ATIPnTriangles()
{
    std::for_each_n(__ATIPnTrianglesEntryPoints,
                    std::size(__ATIPnTrianglesEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIPnTriangles::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_pn_triangles");
}

void ATIPnTriangles::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIPnTrianglesEntryPoints,
                    std::size(__ATIPnTrianglesEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATISeparateStencil Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATISeparateStencil::ATISeparateStencil()
{
    std::for_each_n(__ATISeparateStencilEntryPoints,
                    std::size(__ATISeparateStencilEntryPoints),
                    ClearEntryPoint(this));
}

bool ATISeparateStencil::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_separate_stencil");
}

void ATISeparateStencil::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATISeparateStencilEntryPoints,
                    std::size(__ATISeparateStencilEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexArrayObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIVertexArrayObject::ATIVertexArrayObject()
{
    std::for_each_n(__ATIVertexArrayObjectEntryPoints,
                    std::size(__ATIVertexArrayObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIVertexArrayObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_vertex_array_object");
}

void ATIVertexArrayObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIVertexArrayObjectEntryPoints,
                    std::size(__ATIVertexArrayObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexAttribArrayObject Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIVertexAttribArrayObject::ATIVertexAttribArrayObject()
{
    std::for_each_n(__ATIVertexAttribArrayObjectEntryPoints,
                    std::size(__ATIVertexAttribArrayObjectEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIVertexAttribArrayObject::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_vertex_attrib_array_object");
}

void ATIVertexAttribArrayObject::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIVertexAttribArrayObjectEntryPoints,
                    std::size(__ATIVertexAttribArrayObjectEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexStreams Member Definitions
////////////////////////////////////////////////////////////////////////////////
ATIVertexStreams::ATIVertexStreams()
{
    std::for_each_n(__ATIVertexStreamsEntryPoints,
                    std::size(__ATIVertexStreamsEntryPoints),
                    ClearEntryPoint(this));
}

bool ATIVertexStreams::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_ATI_vertex_streams");
}

void ATIVertexStreams::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__ATIVertexStreamsEntryPoints,
                    std::size(__ATIVertexStreamsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}



} // namespace gl
////////////////////////////////////////////////////////////////////////////////

