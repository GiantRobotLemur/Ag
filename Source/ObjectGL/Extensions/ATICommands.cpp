//! @file ObjectGL/Extensions/ATICommands.cpp
//! @brief The definition of ATI-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/ATICommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// ATIDrawBuffersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_draw_buffers extension.
ATIDrawBuffersAPI::ATIDrawBuffersAPI() :
    BaseExtension("GL_ATI_draw_buffers")
{
}

// Grant read-only access to the underlying function pointers.
const ATIDrawBuffers &ATIDrawBuffersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_draw_buffers entry points.
void ATIDrawBuffersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawBuffersATI().
void ATIDrawBuffersAPI::drawBuffers(GLsizei n, const DrawBufferMode *bufs) const
{
    static const char *fnName = "glDrawBuffersATI";

    beforeCommand(fnName, _api.glDrawBuffers);
    _api.glDrawBuffers(n, toScalarPtr(bufs));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIElementArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_element_array extension.
ATIElementArrayAPI::ATIElementArrayAPI() :
    BaseExtension("GL_ATI_element_array")
{
}

// Grant read-only access to the underlying function pointers.
const ATIElementArray &ATIElementArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_element_array entry points.
void ATIElementArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawElementArrayATI().
void ATIElementArrayAPI::drawElementArray(PrimitiveType mode, GLsizei count) const
{
    static const char *fnName = "glDrawElementArrayATI";

    beforeCommand(fnName, _api.glDrawElementArray);
    _api.glDrawElementArray(toScalar(mode), count);
    afterCommand(fnName);
}

// Calls glDrawRangeElementArrayATI().
void ATIElementArrayAPI::drawRangeElementArray(PrimitiveType mode, GLuint start,
                                               GLuint end, GLsizei count) const
{
    static const char *fnName = "glDrawRangeElementArrayATI";

    beforeCommand(fnName, _api.glDrawRangeElementArray);
    _api.glDrawRangeElementArray(toScalar(mode), start, end, count);
    afterCommand(fnName);
}

// Calls glElementPointerATI().
void ATIElementArrayAPI::elementPointer(ElementPointerTypeATI type,
                                        const void *pointer) const
{
    static const char *fnName = "glElementPointerATI";

    beforeCommand(fnName, _api.glElementPointer);
    _api.glElementPointer(toScalar(type), pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIEnvmapBumpmapAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_envmap_bumpmap extension.
ATIEnvmapBumpmapAPI::ATIEnvmapBumpmapAPI() :
    BaseExtension("GL_ATI_envmap_bumpmap")
{
}

// Grant read-only access to the underlying function pointers.
const ATIEnvmapBumpmap &ATIEnvmapBumpmapAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_envmap_bumpmap entry points.
void ATIEnvmapBumpmapAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetTexBumpParameterfvATI().
void ATIEnvmapBumpmapAPI::getTexBumpParameterFV(GetTexBumpParameterATI pname,
                                                GLfloat *param) const
{
    static const char *fnName = "glGetTexBumpParameterfvATI";

    beforeCommand(fnName, _api.glGetTexBumpParameterfv);
    _api.glGetTexBumpParameterfv(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetTexBumpParameterivATI().
void ATIEnvmapBumpmapAPI::getTexBumpParameterIV(GetTexBumpParameterATI pname,
                                                GLint *param) const
{
    static const char *fnName = "glGetTexBumpParameterivATI";

    beforeCommand(fnName, _api.glGetTexBumpParameteriv);
    _api.glGetTexBumpParameteriv(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexBumpParameterfvATI().
void ATIEnvmapBumpmapAPI::texBumpParameterFV(TexBumpParameterATI pname,
                                             const GLfloat *param) const
{
    static const char *fnName = "glTexBumpParameterfvATI";

    beforeCommand(fnName, _api.glTexBumpParameterfv);
    _api.glTexBumpParameterfv(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glTexBumpParameterivATI().
void ATIEnvmapBumpmapAPI::texBumpParameterIV(TexBumpParameterATI pname,
                                             const GLint *param) const
{
    static const char *fnName = "glTexBumpParameterivATI";

    beforeCommand(fnName, _api.glTexBumpParameteriv);
    _api.glTexBumpParameteriv(toScalar(pname), param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIFragmentShaderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_fragment_shader extension.
ATIFragmentShaderAPI::ATIFragmentShaderAPI() :
    BaseExtension("GL_ATI_fragment_shader")
{
}

// Grant read-only access to the underlying function pointers.
const ATIFragmentShader &ATIFragmentShaderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_fragment_shader entry points.
void ATIFragmentShaderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAlphaFragmentOp1ATI().
void ATIFragmentShaderAPI::alphaFragmentOp1(FragmentOpATI op, GLuint dst,
                                            GLuint dstMod, GLuint arg1,
                                            GLuint arg1Rep, GLuint arg1Mod) const
{
    static const char *fnName = "glAlphaFragmentOp1ATI";

    beforeCommand(fnName, _api.glAlphaFragmentOp1);
    _api.glAlphaFragmentOp1(toScalar(op), dst, dstMod, arg1, arg1Rep, arg1Mod);
    afterCommand(fnName);
}

// Calls glAlphaFragmentOp2ATI().
void ATIFragmentShaderAPI::alphaFragmentOp2(FragmentOpATI op, GLuint dst,
                                            GLuint dstMod, GLuint arg1,
                                            GLuint arg1Rep, GLuint arg1Mod,
                                            GLuint arg2, GLuint arg2Rep,
                                            GLuint arg2Mod) const
{
    static const char *fnName = "glAlphaFragmentOp2ATI";

    beforeCommand(fnName, _api.glAlphaFragmentOp2);
    _api.glAlphaFragmentOp2(toScalar(op), dst, dstMod, arg1, arg1Rep, arg1Mod,
                            arg2, arg2Rep, arg2Mod);
    afterCommand(fnName);
}

// Calls glAlphaFragmentOp3ATI().
void ATIFragmentShaderAPI::alphaFragmentOp3(FragmentOpATI op, GLuint dst,
                                            GLuint dstMod, GLuint arg1,
                                            GLuint arg1Rep, GLuint arg1Mod,
                                            GLuint arg2, GLuint arg2Rep,
                                            GLuint arg2Mod, GLuint arg3,
                                            GLuint arg3Rep, GLuint arg3Mod) const
{
    static const char *fnName = "glAlphaFragmentOp3ATI";

    beforeCommand(fnName, _api.glAlphaFragmentOp3);
    _api.glAlphaFragmentOp3(toScalar(op), dst, dstMod, arg1, arg1Rep, arg1Mod,
                            arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
    afterCommand(fnName);
}

// Calls glBeginFragmentShaderATI().
void ATIFragmentShaderAPI::beginFragmentShader() const
{
    static const char *fnName = "glBeginFragmentShaderATI";

    beforeCommand(fnName, _api.glBeginFragmentShader);
    _api.glBeginFragmentShader();
    afterCommand(fnName);
}

// Calls glBindFragmentShaderATI().
void ATIFragmentShaderAPI::bindFragmentShader(GLuint id) const
{
    static const char *fnName = "glBindFragmentShaderATI";

    beforeCommand(fnName, _api.glBindFragmentShader);
    _api.glBindFragmentShader(id);
    afterCommand(fnName);
}

// Calls glColorFragmentOp1ATI().
void ATIFragmentShaderAPI::colorFragmentOp1(FragmentOpATI op, GLuint dst,
                                            GLuint dstMask, GLuint dstMod,
                                            GLuint arg1, GLuint arg1Rep,
                                            GLuint arg1Mod) const
{
    static const char *fnName = "glColorFragmentOp1ATI";

    beforeCommand(fnName, _api.glColorFragmentOp1);
    _api.glColorFragmentOp1(toScalar(op), dst, dstMask, dstMod, arg1, arg1Rep,
                            arg1Mod);
    afterCommand(fnName);
}

// Calls glColorFragmentOp2ATI().
void ATIFragmentShaderAPI::colorFragmentOp2(FragmentOpATI op, GLuint dst,
                                            GLuint dstMask, GLuint dstMod,
                                            GLuint arg1, GLuint arg1Rep,
                                            GLuint arg1Mod, GLuint arg2,
                                            GLuint arg2Rep, GLuint arg2Mod) const
{
    static const char *fnName = "glColorFragmentOp2ATI";

    beforeCommand(fnName, _api.glColorFragmentOp2);
    _api.glColorFragmentOp2(toScalar(op), dst, dstMask, dstMod, arg1, arg1Rep,
                            arg1Mod, arg2, arg2Rep, arg2Mod);
    afterCommand(fnName);
}

// Calls glColorFragmentOp3ATI().
void ATIFragmentShaderAPI::colorFragmentOp3(FragmentOpATI op, GLuint dst,
                                            GLuint dstMask, GLuint dstMod,
                                            GLuint arg1, GLuint arg1Rep,
                                            GLuint arg1Mod, GLuint arg2,
                                            GLuint arg2Rep, GLuint arg2Mod,
                                            GLuint arg3, GLuint arg3Rep,
                                            GLuint arg3Mod) const
{
    static const char *fnName = "glColorFragmentOp3ATI";

    beforeCommand(fnName, _api.glColorFragmentOp3);
    _api.glColorFragmentOp3(toScalar(op), dst, dstMask, dstMod, arg1, arg1Rep,
                            arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep,
                            arg3Mod);
    afterCommand(fnName);
}

// Calls glDeleteFragmentShaderATI().
void ATIFragmentShaderAPI::deleteFragmentShader(GLuint id) const
{
    static const char *fnName = "glDeleteFragmentShaderATI";

    beforeCommand(fnName, _api.glDeleteFragmentShader);
    _api.glDeleteFragmentShader(id);
    afterCommand(fnName);
}

// Calls glEndFragmentShaderATI().
void ATIFragmentShaderAPI::endFragmentShader() const
{
    static const char *fnName = "glEndFragmentShaderATI";

    beforeCommand(fnName, _api.glEndFragmentShader);
    _api.glEndFragmentShader();
    afterCommand(fnName);
}

// Calls glGenFragmentShadersATI().
GLuint ATIFragmentShaderAPI::genFragmentShaders(GLuint range) const
{
    static const char *fnName = "glGenFragmentShadersATI";

    beforeCommand(fnName, _api.glGenFragmentShaders);
    GLuint result = _api.glGenFragmentShaders(range);
    afterCommand(fnName);

    return result;
}

// Calls glPassTexCoordATI().
void ATIFragmentShaderAPI::passTexCoord(GLuint dst, GLuint coord,
                                        SwizzleOpATI swizzle) const
{
    static const char *fnName = "glPassTexCoordATI";

    beforeCommand(fnName, _api.glPassTexCoord);
    _api.glPassTexCoord(dst, coord, toScalar(swizzle));
    afterCommand(fnName);
}

// Calls glSampleMapATI().
void ATIFragmentShaderAPI::sampleMap(GLuint dst, GLuint interp,
                                     SwizzleOpATI swizzle) const
{
    static const char *fnName = "glSampleMapATI";

    beforeCommand(fnName, _api.glSampleMap);
    _api.glSampleMap(dst, interp, toScalar(swizzle));
    afterCommand(fnName);
}

// Calls glSetFragmentShaderConstantATI().
void ATIFragmentShaderAPI::setFragmentShaderConstant(GLuint dst,
                                                     const GLfloat *value) const
{
    static const char *fnName = "glSetFragmentShaderConstantATI";

    beforeCommand(fnName, _api.glSetFragmentShaderConstant);
    _api.glSetFragmentShaderConstant(dst, value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIMapObjectBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_map_object_buffer extension.
ATIMapObjectBufferAPI::ATIMapObjectBufferAPI() :
    BaseExtension("GL_ATI_map_object_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const ATIMapObjectBuffer &ATIMapObjectBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_map_object_buffer entry points.
void ATIMapObjectBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMapObjectBufferATI().
void *ATIMapObjectBufferAPI::mapObjectBuffer(BufferName buffer) const
{
    static const char *fnName = "glMapObjectBufferATI";

    beforeCommand(fnName, _api.glMapObjectBuffer);
    void *result = _api.glMapObjectBuffer(buffer.ID);
    afterCommand(fnName);

    return result;
}

// Calls glUnmapObjectBufferATI().
void ATIMapObjectBufferAPI::unmapObjectBuffer(BufferName buffer) const
{
    static const char *fnName = "glUnmapObjectBufferATI";

    beforeCommand(fnName, _api.glUnmapObjectBuffer);
    _api.glUnmapObjectBuffer(buffer.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIPnTrianglesAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_pn_triangles extension.
ATIPnTrianglesAPI::ATIPnTrianglesAPI() :
    BaseExtension("GL_ATI_pn_triangles")
{
}

// Grant read-only access to the underlying function pointers.
const ATIPnTriangles &ATIPnTrianglesAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_pn_triangles entry points.
void ATIPnTrianglesAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPNTrianglesfATI().
void ATIPnTrianglesAPI::pnTrianglesF(PNTrianglesPNameATI pname, GLfloat param) const
{
    static const char *fnName = "glPNTrianglesfATI";

    beforeCommand(fnName, _api.glPNTrianglesf);
    _api.glPNTrianglesf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPNTrianglesiATI().
void ATIPnTrianglesAPI::pnTrianglesI(PNTrianglesPNameATI pname, GLint param) const
{
    static const char *fnName = "glPNTrianglesiATI";

    beforeCommand(fnName, _api.glPNTrianglesi);
    _api.glPNTrianglesi(toScalar(pname), param);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATISeparateStencilAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_separate_stencil extension.
ATISeparateStencilAPI::ATISeparateStencilAPI() :
    BaseExtension("GL_ATI_separate_stencil")
{
}

// Grant read-only access to the underlying function pointers.
const ATISeparateStencil &ATISeparateStencilAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_separate_stencil entry points.
void ATISeparateStencilAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glStencilFuncSeparateATI().
void ATISeparateStencilAPI::stencilFuncSeparate(StencilFunction frontfunc,
                                                StencilFunction backfunc,
                                                GLint ref, GLuint mask) const
{
    static const char *fnName = "glStencilFuncSeparateATI";

    beforeCommand(fnName, _api.glStencilFuncSeparate);
    _api.glStencilFuncSeparate(toScalar(frontfunc), toScalar(backfunc), ref,
                               mask);
    afterCommand(fnName);
}

// Calls glStencilOpSeparateATI().
void ATISeparateStencilAPI::stencilOpSeparate(StencilFaceDirection face,
                                              StencilOp sfail, StencilOp dpfail,
                                              StencilOp dppass) const
{
    static const char *fnName = "glStencilOpSeparateATI";

    beforeCommand(fnName, _api.glStencilOpSeparate);
    _api.glStencilOpSeparate(toScalar(face), toScalar(sfail), toScalar(dpfail),
                             toScalar(dppass));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexArrayObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_vertex_array_object extension.
ATIVertexArrayObjectAPI::ATIVertexArrayObjectAPI() :
    BaseExtension("GL_ATI_vertex_array_object")
{
}

// Grant read-only access to the underlying function pointers.
const ATIVertexArrayObject &ATIVertexArrayObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_vertex_array_object entry points.
void ATIVertexArrayObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glArrayObjectATI().
void ATIVertexArrayObjectAPI::arrayObject(EnableCap array, GLint size,
                                          ScalarType type, GLsizei stride,
                                          BufferName buffer, GLuint offset) const
{
    static const char *fnName = "glArrayObjectATI";

    beforeCommand(fnName, _api.glArrayObject);
    _api.glArrayObject(toScalar(array), size, toScalar(type), stride, buffer.ID,
                       offset);
    afterCommand(fnName);
}

// Calls glFreeObjectBufferATI().
void ATIVertexArrayObjectAPI::freeObjectBuffer(BufferName buffer) const
{
    static const char *fnName = "glFreeObjectBufferATI";

    beforeCommand(fnName, _api.glFreeObjectBuffer);
    _api.glFreeObjectBuffer(buffer.ID);
    afterCommand(fnName);
}

// Calls glGetArrayObjectfvATI().
void ATIVertexArrayObjectAPI::getArrayObjectFV(EnableCap array,
                                               ArrayObjectPNameATI pname,
                                               GLfloat *params) const
{
    static const char *fnName = "glGetArrayObjectfvATI";

    beforeCommand(fnName, _api.glGetArrayObjectfv);
    _api.glGetArrayObjectfv(toScalar(array), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetArrayObjectivATI().
void ATIVertexArrayObjectAPI::getArrayObjectIV(EnableCap array,
                                               ArrayObjectPNameATI pname,
                                               GLint *params) const
{
    static const char *fnName = "glGetArrayObjectivATI";

    beforeCommand(fnName, _api.glGetArrayObjectiv);
    _api.glGetArrayObjectiv(toScalar(array), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetObjectBufferfvATI().
void ATIVertexArrayObjectAPI::getObjectBufferFV(BufferName buffer,
                                                ArrayObjectPNameATI pname,
                                                GLfloat *params) const
{
    static const char *fnName = "glGetObjectBufferfvATI";

    beforeCommand(fnName, _api.glGetObjectBufferfv);
    _api.glGetObjectBufferfv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetObjectBufferivATI().
void ATIVertexArrayObjectAPI::getObjectBufferIV(BufferName buffer,
                                                ArrayObjectPNameATI pname,
                                                GLint *params) const
{
    static const char *fnName = "glGetObjectBufferivATI";

    beforeCommand(fnName, _api.glGetObjectBufferiv);
    _api.glGetObjectBufferiv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVariantArrayObjectfvATI().
void ATIVertexArrayObjectAPI::getVariantArrayObjectFV(GLuint id,
                                                      ArrayObjectPNameATI pname,
                                                      GLfloat *params) const
{
    static const char *fnName = "glGetVariantArrayObjectfvATI";

    beforeCommand(fnName, _api.glGetVariantArrayObjectfv);
    _api.glGetVariantArrayObjectfv(id, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVariantArrayObjectivATI().
void ATIVertexArrayObjectAPI::getVariantArrayObjectIV(GLuint id,
                                                      ArrayObjectPNameATI pname,
                                                      GLint *params) const
{
    static const char *fnName = "glGetVariantArrayObjectivATI";

    beforeCommand(fnName, _api.glGetVariantArrayObjectiv);
    _api.glGetVariantArrayObjectiv(id, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsObjectBufferATI().
Boolean ATIVertexArrayObjectAPI::isObjectBuffer(BufferName buffer) const
{
    static const char *fnName = "glIsObjectBufferATI";

    beforeCommand(fnName, _api.glIsObjectBuffer);
    GLboolean result = _api.glIsObjectBuffer(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glNewObjectBufferATI().
GLuint ATIVertexArrayObjectAPI::newObjectBuffer(GLsizei size,
                                                const void *pointer,
                                                ArrayObjectUsageATI usage) const
{
    static const char *fnName = "glNewObjectBufferATI";

    beforeCommand(fnName, _api.glNewObjectBuffer);
    GLuint result = _api.glNewObjectBuffer(size, pointer, toScalar(usage));
    afterCommand(fnName);

    return result;
}

// Calls glUpdateObjectBufferATI().
void ATIVertexArrayObjectAPI::updateObjectBuffer(BufferName buffer,
                                                 GLuint offset, GLsizei size,
                                                 const void *pointer,
                                                 PreserveModeATI preserve) const
{
    static const char *fnName = "glUpdateObjectBufferATI";

    beforeCommand(fnName, _api.glUpdateObjectBuffer);
    _api.glUpdateObjectBuffer(buffer.ID, offset, size, pointer,
                              toScalar(preserve));
    afterCommand(fnName);
}

// Calls glVariantArrayObjectATI().
void ATIVertexArrayObjectAPI::variantArrayObject(GLuint id, ScalarType type,
                                                 GLsizei stride,
                                                 BufferName buffer,
                                                 GLuint offset) const
{
    static const char *fnName = "glVariantArrayObjectATI";

    beforeCommand(fnName, _api.glVariantArrayObject);
    _api.glVariantArrayObject(id, toScalar(type), stride, buffer.ID, offset);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexAttribArrayObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_vertex_attrib_array_object extension.
ATIVertexAttribArrayObjectAPI::ATIVertexAttribArrayObjectAPI() :
    BaseExtension("GL_ATI_vertex_attrib_array_object")
{
}

// Grant read-only access to the underlying function pointers.
const ATIVertexAttribArrayObject &ATIVertexAttribArrayObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_vertex_attrib_array_object entry points.
void ATIVertexAttribArrayObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetVertexAttribArrayObjectfvATI().
void ATIVertexAttribArrayObjectAPI::getVertexAttribArrayObjectFV(GLuint index,
                                                                 ArrayObjectPNameATI pname,
                                                                 GLfloat *params) const
{
    static const char *fnName = "glGetVertexAttribArrayObjectfvATI";

    beforeCommand(fnName, _api.glGetVertexAttribArrayObjectfv);
    _api.glGetVertexAttribArrayObjectfv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribArrayObjectivATI().
void ATIVertexAttribArrayObjectAPI::getVertexAttribArrayObjectIV(GLuint index,
                                                                 ArrayObjectPNameATI pname,
                                                                 GLint *params) const
{
    static const char *fnName = "glGetVertexAttribArrayObjectivATI";

    beforeCommand(fnName, _api.glGetVertexAttribArrayObjectiv);
    _api.glGetVertexAttribArrayObjectiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glVertexAttribArrayObjectATI().
void ATIVertexAttribArrayObjectAPI::vertexAttribArrayObject(GLuint index,
                                                            GLint size,
                                                            VertexAttribPointerType type,
                                                            Boolean normalized,
                                                            GLsizei stride,
                                                            BufferName buffer,
                                                            GLuint offset) const
{
    static const char *fnName = "glVertexAttribArrayObjectATI";

    beforeCommand(fnName, _api.glVertexAttribArrayObject);
    _api.glVertexAttribArrayObject(index, size, toScalar(type),
                                   toScalar(normalized), stride, buffer.ID,
                                   offset);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// ATIVertexStreamsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_ATI_vertex_streams extension.
ATIVertexStreamsAPI::ATIVertexStreamsAPI() :
    BaseExtension("GL_ATI_vertex_streams")
{
}

// Grant read-only access to the underlying function pointers.
const ATIVertexStreams &ATIVertexStreamsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_ATI_vertex_streams entry points.
void ATIVertexStreamsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClientActiveVertexStreamATI().
void ATIVertexStreamsAPI::clientActiveVertexStream(VertexStreamATI stream) const
{
    static const char *fnName = "glClientActiveVertexStreamATI";

    beforeCommand(fnName, _api.glClientActiveVertexStream);
    _api.glClientActiveVertexStream(toScalar(stream));
    afterCommand(fnName);
}

// Calls glNormalStream3bATI().
void ATIVertexStreamsAPI::normalStream3B(VertexStreamATI stream, GLbyte nx,
                                         GLbyte ny, GLbyte nz) const
{
    static const char *fnName = "glNormalStream3bATI";

    beforeCommand(fnName, _api.glNormalStream3b);
    _api.glNormalStream3b(toScalar(stream), nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormalStream3bvATI().
void ATIVertexStreamsAPI::normalStream3BV(VertexStreamATI stream,
                                          const GLbyte *coords) const
{
    static const char *fnName = "glNormalStream3bvATI";

    beforeCommand(fnName, _api.glNormalStream3bv);
    _api.glNormalStream3bv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glNormalStream3dATI().
void ATIVertexStreamsAPI::normalStream3D(VertexStreamATI stream, GLdouble nx,
                                         GLdouble ny, GLdouble nz) const
{
    static const char *fnName = "glNormalStream3dATI";

    beforeCommand(fnName, _api.glNormalStream3d);
    _api.glNormalStream3d(toScalar(stream), nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormalStream3dvATI().
void ATIVertexStreamsAPI::normalStream3DV(VertexStreamATI stream,
                                          const GLdouble *coords) const
{
    static const char *fnName = "glNormalStream3dvATI";

    beforeCommand(fnName, _api.glNormalStream3dv);
    _api.glNormalStream3dv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glNormalStream3fATI().
void ATIVertexStreamsAPI::normalStream3F(VertexStreamATI stream, GLfloat nx,
                                         GLfloat ny, GLfloat nz) const
{
    static const char *fnName = "glNormalStream3fATI";

    beforeCommand(fnName, _api.glNormalStream3f);
    _api.glNormalStream3f(toScalar(stream), nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormalStream3fvATI().
void ATIVertexStreamsAPI::normalStream3FV(VertexStreamATI stream,
                                          const GLfloat *coords) const
{
    static const char *fnName = "glNormalStream3fvATI";

    beforeCommand(fnName, _api.glNormalStream3fv);
    _api.glNormalStream3fv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glNormalStream3iATI().
void ATIVertexStreamsAPI::normalStream3I(VertexStreamATI stream, GLint nx,
                                         GLint ny, GLint nz) const
{
    static const char *fnName = "glNormalStream3iATI";

    beforeCommand(fnName, _api.glNormalStream3i);
    _api.glNormalStream3i(toScalar(stream), nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormalStream3ivATI().
void ATIVertexStreamsAPI::normalStream3IV(VertexStreamATI stream,
                                          const GLint *coords) const
{
    static const char *fnName = "glNormalStream3ivATI";

    beforeCommand(fnName, _api.glNormalStream3iv);
    _api.glNormalStream3iv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glNormalStream3sATI().
void ATIVertexStreamsAPI::normalStream3S(VertexStreamATI stream, GLshort nx,
                                         GLshort ny, GLshort nz) const
{
    static const char *fnName = "glNormalStream3sATI";

    beforeCommand(fnName, _api.glNormalStream3s);
    _api.glNormalStream3s(toScalar(stream), nx, ny, nz);
    afterCommand(fnName);
}

// Calls glNormalStream3svATI().
void ATIVertexStreamsAPI::normalStream3SV(VertexStreamATI stream,
                                          const GLshort *coords) const
{
    static const char *fnName = "glNormalStream3svATI";

    beforeCommand(fnName, _api.glNormalStream3sv);
    _api.glNormalStream3sv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexBlendEnvfATI().
void ATIVertexStreamsAPI::vertexBlendEnvF(VertexStreamATI pname, GLfloat param) const
{
    static const char *fnName = "glVertexBlendEnvfATI";

    beforeCommand(fnName, _api.glVertexBlendEnvf);
    _api.glVertexBlendEnvf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glVertexBlendEnviATI().
void ATIVertexStreamsAPI::vertexBlendEnvI(VertexStreamATI pname, GLint param) const
{
    static const char *fnName = "glVertexBlendEnviATI";

    beforeCommand(fnName, _api.glVertexBlendEnvi);
    _api.glVertexBlendEnvi(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glVertexStream1dATI().
void ATIVertexStreamsAPI::vertexStream1D(VertexStreamATI stream, GLdouble x) const
{
    static const char *fnName = "glVertexStream1dATI";

    beforeCommand(fnName, _api.glVertexStream1d);
    _api.glVertexStream1d(toScalar(stream), x);
    afterCommand(fnName);
}

// Calls glVertexStream1dvATI().
void ATIVertexStreamsAPI::vertexStream1DV(VertexStreamATI stream,
                                          const GLdouble *coords) const
{
    static const char *fnName = "glVertexStream1dvATI";

    beforeCommand(fnName, _api.glVertexStream1dv);
    _api.glVertexStream1dv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream1fATI().
void ATIVertexStreamsAPI::vertexStream1F(VertexStreamATI stream, GLfloat x) const
{
    static const char *fnName = "glVertexStream1fATI";

    beforeCommand(fnName, _api.glVertexStream1f);
    _api.glVertexStream1f(toScalar(stream), x);
    afterCommand(fnName);
}

// Calls glVertexStream1fvATI().
void ATIVertexStreamsAPI::vertexStream1FV(VertexStreamATI stream,
                                          const GLfloat *coords) const
{
    static const char *fnName = "glVertexStream1fvATI";

    beforeCommand(fnName, _api.glVertexStream1fv);
    _api.glVertexStream1fv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream1iATI().
void ATIVertexStreamsAPI::vertexStream1I(VertexStreamATI stream, GLint x) const
{
    static const char *fnName = "glVertexStream1iATI";

    beforeCommand(fnName, _api.glVertexStream1i);
    _api.glVertexStream1i(toScalar(stream), x);
    afterCommand(fnName);
}

// Calls glVertexStream1ivATI().
void ATIVertexStreamsAPI::vertexStream1IV(VertexStreamATI stream,
                                          const GLint *coords) const
{
    static const char *fnName = "glVertexStream1ivATI";

    beforeCommand(fnName, _api.glVertexStream1iv);
    _api.glVertexStream1iv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream1sATI().
void ATIVertexStreamsAPI::vertexStream1S(VertexStreamATI stream, GLshort x) const
{
    static const char *fnName = "glVertexStream1sATI";

    beforeCommand(fnName, _api.glVertexStream1s);
    _api.glVertexStream1s(toScalar(stream), x);
    afterCommand(fnName);
}

// Calls glVertexStream1svATI().
void ATIVertexStreamsAPI::vertexStream1SV(VertexStreamATI stream,
                                          const GLshort *coords) const
{
    static const char *fnName = "glVertexStream1svATI";

    beforeCommand(fnName, _api.glVertexStream1sv);
    _api.glVertexStream1sv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream2dATI().
void ATIVertexStreamsAPI::vertexStream2D(VertexStreamATI stream, GLdouble x,
                                         GLdouble y) const
{
    static const char *fnName = "glVertexStream2dATI";

    beforeCommand(fnName, _api.glVertexStream2d);
    _api.glVertexStream2d(toScalar(stream), x, y);
    afterCommand(fnName);
}

// Calls glVertexStream2dvATI().
void ATIVertexStreamsAPI::vertexStream2DV(VertexStreamATI stream,
                                          const GLdouble *coords) const
{
    static const char *fnName = "glVertexStream2dvATI";

    beforeCommand(fnName, _api.glVertexStream2dv);
    _api.glVertexStream2dv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream2fATI().
void ATIVertexStreamsAPI::vertexStream2F(VertexStreamATI stream, GLfloat x,
                                         GLfloat y) const
{
    static const char *fnName = "glVertexStream2fATI";

    beforeCommand(fnName, _api.glVertexStream2f);
    _api.glVertexStream2f(toScalar(stream), x, y);
    afterCommand(fnName);
}

// Calls glVertexStream2fvATI().
void ATIVertexStreamsAPI::vertexStream2FV(VertexStreamATI stream,
                                          const GLfloat *coords) const
{
    static const char *fnName = "glVertexStream2fvATI";

    beforeCommand(fnName, _api.glVertexStream2fv);
    _api.glVertexStream2fv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream2iATI().
void ATIVertexStreamsAPI::vertexStream2I(VertexStreamATI stream, GLint x,
                                         GLint y) const
{
    static const char *fnName = "glVertexStream2iATI";

    beforeCommand(fnName, _api.glVertexStream2i);
    _api.glVertexStream2i(toScalar(stream), x, y);
    afterCommand(fnName);
}

// Calls glVertexStream2ivATI().
void ATIVertexStreamsAPI::vertexStream2IV(VertexStreamATI stream,
                                          const GLint *coords) const
{
    static const char *fnName = "glVertexStream2ivATI";

    beforeCommand(fnName, _api.glVertexStream2iv);
    _api.glVertexStream2iv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream2sATI().
void ATIVertexStreamsAPI::vertexStream2S(VertexStreamATI stream, GLshort x,
                                         GLshort y) const
{
    static const char *fnName = "glVertexStream2sATI";

    beforeCommand(fnName, _api.glVertexStream2s);
    _api.glVertexStream2s(toScalar(stream), x, y);
    afterCommand(fnName);
}

// Calls glVertexStream2svATI().
void ATIVertexStreamsAPI::vertexStream2SV(VertexStreamATI stream,
                                          const GLshort *coords) const
{
    static const char *fnName = "glVertexStream2svATI";

    beforeCommand(fnName, _api.glVertexStream2sv);
    _api.glVertexStream2sv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream3dATI().
void ATIVertexStreamsAPI::vertexStream3D(VertexStreamATI stream, GLdouble x,
                                         GLdouble y, GLdouble z) const
{
    static const char *fnName = "glVertexStream3dATI";

    beforeCommand(fnName, _api.glVertexStream3d);
    _api.glVertexStream3d(toScalar(stream), x, y, z);
    afterCommand(fnName);
}

// Calls glVertexStream3dvATI().
void ATIVertexStreamsAPI::vertexStream3DV(VertexStreamATI stream,
                                          const GLdouble *coords) const
{
    static const char *fnName = "glVertexStream3dvATI";

    beforeCommand(fnName, _api.glVertexStream3dv);
    _api.glVertexStream3dv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream3fATI().
void ATIVertexStreamsAPI::vertexStream3F(VertexStreamATI stream, GLfloat x,
                                         GLfloat y, GLfloat z) const
{
    static const char *fnName = "glVertexStream3fATI";

    beforeCommand(fnName, _api.glVertexStream3f);
    _api.glVertexStream3f(toScalar(stream), x, y, z);
    afterCommand(fnName);
}

// Calls glVertexStream3fvATI().
void ATIVertexStreamsAPI::vertexStream3FV(VertexStreamATI stream,
                                          const GLfloat *coords) const
{
    static const char *fnName = "glVertexStream3fvATI";

    beforeCommand(fnName, _api.glVertexStream3fv);
    _api.glVertexStream3fv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream3iATI().
void ATIVertexStreamsAPI::vertexStream3I(VertexStreamATI stream, GLint x,
                                         GLint y, GLint z) const
{
    static const char *fnName = "glVertexStream3iATI";

    beforeCommand(fnName, _api.glVertexStream3i);
    _api.glVertexStream3i(toScalar(stream), x, y, z);
    afterCommand(fnName);
}

// Calls glVertexStream3ivATI().
void ATIVertexStreamsAPI::vertexStream3IV(VertexStreamATI stream,
                                          const GLint *coords) const
{
    static const char *fnName = "glVertexStream3ivATI";

    beforeCommand(fnName, _api.glVertexStream3iv);
    _api.glVertexStream3iv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream3sATI().
void ATIVertexStreamsAPI::vertexStream3S(VertexStreamATI stream, GLshort x,
                                         GLshort y, GLshort z) const
{
    static const char *fnName = "glVertexStream3sATI";

    beforeCommand(fnName, _api.glVertexStream3s);
    _api.glVertexStream3s(toScalar(stream), x, y, z);
    afterCommand(fnName);
}

// Calls glVertexStream3svATI().
void ATIVertexStreamsAPI::vertexStream3SV(VertexStreamATI stream,
                                          const GLshort *coords) const
{
    static const char *fnName = "glVertexStream3svATI";

    beforeCommand(fnName, _api.glVertexStream3sv);
    _api.glVertexStream3sv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream4dATI().
void ATIVertexStreamsAPI::vertexStream4D(VertexStreamATI stream, GLdouble x,
                                         GLdouble y, GLdouble z, GLdouble w) const
{
    static const char *fnName = "glVertexStream4dATI";

    beforeCommand(fnName, _api.glVertexStream4d);
    _api.glVertexStream4d(toScalar(stream), x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexStream4dvATI().
void ATIVertexStreamsAPI::vertexStream4DV(VertexStreamATI stream,
                                          const GLdouble *coords) const
{
    static const char *fnName = "glVertexStream4dvATI";

    beforeCommand(fnName, _api.glVertexStream4dv);
    _api.glVertexStream4dv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream4fATI().
void ATIVertexStreamsAPI::vertexStream4F(VertexStreamATI stream, GLfloat x,
                                         GLfloat y, GLfloat z, GLfloat w) const
{
    static const char *fnName = "glVertexStream4fATI";

    beforeCommand(fnName, _api.glVertexStream4f);
    _api.glVertexStream4f(toScalar(stream), x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexStream4fvATI().
void ATIVertexStreamsAPI::vertexStream4FV(VertexStreamATI stream,
                                          const GLfloat *coords) const
{
    static const char *fnName = "glVertexStream4fvATI";

    beforeCommand(fnName, _api.glVertexStream4fv);
    _api.glVertexStream4fv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream4iATI().
void ATIVertexStreamsAPI::vertexStream4I(VertexStreamATI stream, GLint x,
                                         GLint y, GLint z, GLint w) const
{
    static const char *fnName = "glVertexStream4iATI";

    beforeCommand(fnName, _api.glVertexStream4i);
    _api.glVertexStream4i(toScalar(stream), x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexStream4ivATI().
void ATIVertexStreamsAPI::vertexStream4IV(VertexStreamATI stream,
                                          const GLint *coords) const
{
    static const char *fnName = "glVertexStream4ivATI";

    beforeCommand(fnName, _api.glVertexStream4iv);
    _api.glVertexStream4iv(toScalar(stream), coords);
    afterCommand(fnName);
}

// Calls glVertexStream4sATI().
void ATIVertexStreamsAPI::vertexStream4S(VertexStreamATI stream, GLshort x,
                                         GLshort y, GLshort z, GLshort w) const
{
    static const char *fnName = "glVertexStream4sATI";

    beforeCommand(fnName, _api.glVertexStream4s);
    _api.glVertexStream4s(toScalar(stream), x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexStream4svATI().
void ATIVertexStreamsAPI::vertexStream4SV(VertexStreamATI stream,
                                          const GLshort *coords) const
{
    static const char *fnName = "glVertexStream4svATI";

    beforeCommand(fnName, _api.glVertexStream4sv);
    _api.glVertexStream4sv(toScalar(stream), coords);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

