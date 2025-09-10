//! @file ObjectGL/Extensions/AppleCommands.cpp
//! @brief The definition of Apple-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/AppleCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// APPLEElementArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_element_array extension.
APPLEElementArrayAPI::APPLEElementArrayAPI() :
    BaseExtension("GL_APPLE_element_array")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEElementArray &APPLEElementArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_element_array entry points.
void APPLEElementArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawElementArrayAPPLE().
void APPLEElementArrayAPI::drawElementArray(PrimitiveType mode, GLint first,
                                            GLsizei count) const
{
    static const char *fnName = "glDrawElementArrayAPPLE";

    beforeCommand(fnName, _api.glDrawElementArray);
    _api.glDrawElementArray(toScalar(mode), first, count);
    afterCommand(fnName);
}

// Calls glDrawRangeElementArrayAPPLE().
void APPLEElementArrayAPI::drawRangeElementArray(PrimitiveType mode,
                                                 GLuint start, GLuint end,
                                                 GLint first, GLsizei count) const
{
    static const char *fnName = "glDrawRangeElementArrayAPPLE";

    beforeCommand(fnName, _api.glDrawRangeElementArray);
    _api.glDrawRangeElementArray(toScalar(mode), start, end, first, count);
    afterCommand(fnName);
}

// Calls glElementPointerAPPLE().
void APPLEElementArrayAPI::elementPointer(ElementPointerTypeATI type,
                                          const void *pointer) const
{
    static const char *fnName = "glElementPointerAPPLE";

    beforeCommand(fnName, _api.glElementPointer);
    _api.glElementPointer(toScalar(type), pointer);
    afterCommand(fnName);
}

// Calls glMultiDrawElementArrayAPPLE().
void APPLEElementArrayAPI::multiDrawElementArray(PrimitiveType mode,
                                                 const GLint *first,
                                                 const GLsizei *count,
                                                 GLsizei primcount) const
{
    static const char *fnName = "glMultiDrawElementArrayAPPLE";

    beforeCommand(fnName, _api.glMultiDrawElementArray);
    _api.glMultiDrawElementArray(toScalar(mode), first, count, primcount);
    afterCommand(fnName);
}

// Calls glMultiDrawRangeElementArrayAPPLE().
void APPLEElementArrayAPI::multiDrawRangeElementArray(PrimitiveType mode,
                                                      GLuint start, GLuint end,
                                                      const GLint *first,
                                                      const GLsizei *count,
                                                      GLsizei primcount) const
{
    static const char *fnName = "glMultiDrawRangeElementArrayAPPLE";

    beforeCommand(fnName, _api.glMultiDrawRangeElementArray);
    _api.glMultiDrawRangeElementArray(toScalar(mode), start, end, first, count,
                                      primcount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEFenceAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_fence extension.
APPLEFenceAPI::APPLEFenceAPI() :
    BaseExtension("GL_APPLE_fence")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEFence &APPLEFenceAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_fence entry points.
void APPLEFenceAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeleteFencesAPPLE().
void APPLEFenceAPI::deleteFences(GLsizei n, const GLuint *fences) const
{
    static const char *fnName = "glDeleteFencesAPPLE";

    beforeCommand(fnName, _api.glDeleteFences);
    _api.glDeleteFences(n, fences);
    afterCommand(fnName);
}

// Calls glFinishFenceAPPLE().
void APPLEFenceAPI::finishFence(GLuint fence) const
{
    static const char *fnName = "glFinishFenceAPPLE";

    beforeCommand(fnName, _api.glFinishFence);
    _api.glFinishFence(fence);
    afterCommand(fnName);
}

// Calls glFinishObjectAPPLE().
void APPLEFenceAPI::finishObject(ObjectTypeAPPLE object, GLint name) const
{
    static const char *fnName = "glFinishObjectAPPLE";

    beforeCommand(fnName, _api.glFinishObject);
    _api.glFinishObject(toScalar(object), name);
    afterCommand(fnName);
}

// Calls glGenFencesAPPLE().
void APPLEFenceAPI::genFences(GLsizei n, GLuint *fences) const
{
    static const char *fnName = "glGenFencesAPPLE";

    beforeCommand(fnName, _api.glGenFences);
    _api.glGenFences(n, fences);
    afterCommand(fnName);
}

// Calls glIsFenceAPPLE().
Boolean APPLEFenceAPI::isFence(GLuint fence) const
{
    static const char *fnName = "glIsFenceAPPLE";

    beforeCommand(fnName, _api.glIsFence);
    GLboolean result = _api.glIsFence(fence);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glSetFenceAPPLE().
void APPLEFenceAPI::setFence(GLuint fence) const
{
    static const char *fnName = "glSetFenceAPPLE";

    beforeCommand(fnName, _api.glSetFence);
    _api.glSetFence(fence);
    afterCommand(fnName);
}

// Calls glTestFenceAPPLE().
Boolean APPLEFenceAPI::testFence(GLuint fence) const
{
    static const char *fnName = "glTestFenceAPPLE";

    beforeCommand(fnName, _api.glTestFence);
    GLboolean result = _api.glTestFence(fence);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glTestObjectAPPLE().
Boolean APPLEFenceAPI::testObject(ObjectTypeAPPLE object, GLuint name) const
{
    static const char *fnName = "glTestObjectAPPLE";

    beforeCommand(fnName, _api.glTestObject);
    GLboolean result = _api.glTestObject(toScalar(object), name);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEFlushBufferRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_flush_buffer_range extension.
APPLEFlushBufferRangeAPI::APPLEFlushBufferRangeAPI() :
    BaseExtension("GL_APPLE_flush_buffer_range")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEFlushBufferRange &APPLEFlushBufferRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_flush_buffer_range entry points.
void APPLEFlushBufferRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferParameteriAPPLE().
void APPLEFlushBufferRangeAPI::bufferParameterI(GLenum target, GLenum pname,
                                                GLint param) const
{
    static const char *fnName = "glBufferParameteriAPPLE";

    beforeCommand(fnName, _api.glBufferParameteri);
    _api.glBufferParameteri(target, pname, param);
    afterCommand(fnName);
}

// Calls glFlushMappedBufferRangeAPPLE().
void APPLEFlushBufferRangeAPI::flushMappedBufferRange(BufferTargetARB target,
                                                      GLintptr offset,
                                                      GLsizeiptr size) const
{
    static const char *fnName = "glFlushMappedBufferRangeAPPLE";

    beforeCommand(fnName, _api.glFlushMappedBufferRange);
    _api.glFlushMappedBufferRange(toScalar(target), offset, size);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEObjectPurgeableAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_object_purgeable extension.
APPLEObjectPurgeableAPI::APPLEObjectPurgeableAPI() :
    BaseExtension("GL_APPLE_object_purgeable")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEObjectPurgeable &APPLEObjectPurgeableAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_object_purgeable entry points.
void APPLEObjectPurgeableAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetObjectParameterivAPPLE().
void APPLEObjectPurgeableAPI::getObjectParameterIV(GLenum objectType,
                                                   GLuint name, GLenum pname,
                                                   GLint *params) const
{
    static const char *fnName = "glGetObjectParameterivAPPLE";

    beforeCommand(fnName, _api.glGetObjectParameteriv);
    _api.glGetObjectParameteriv(objectType, name, pname, params);
    afterCommand(fnName);
}

// Calls glObjectPurgeableAPPLE().
GLenum APPLEObjectPurgeableAPI::objectPurgeable(GLenum objectType, GLuint name,
                                                GLenum option) const
{
    static const char *fnName = "glObjectPurgeableAPPLE";

    beforeCommand(fnName, _api.glObjectPurgeable);
    GLenum result = _api.glObjectPurgeable(objectType, name, option);
    afterCommand(fnName);

    return result;
}

// Calls glObjectUnpurgeableAPPLE().
GLenum APPLEObjectPurgeableAPI::objectUnpurgeable(GLenum objectType, GLuint name,
                                                  GLenum option) const
{
    static const char *fnName = "glObjectUnpurgeableAPPLE";

    beforeCommand(fnName, _api.glObjectUnpurgeable);
    GLenum result = _api.glObjectUnpurgeable(objectType, name, option);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// APPLETextureRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_texture_range extension.
APPLETextureRangeAPI::APPLETextureRangeAPI() :
    BaseExtension("GL_APPLE_texture_range")
{
}

// Grant read-only access to the underlying function pointers.
const APPLETextureRange &APPLETextureRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_texture_range entry points.
void APPLETextureRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetTexParameterPointervAPPLE().
void APPLETextureRangeAPI::getTexParameterPointerV(GLenum target, GLenum pname,
                                                   void **params) const
{
    static const char *fnName = "glGetTexParameterPointervAPPLE";

    beforeCommand(fnName, _api.glGetTexParameterPointerv);
    _api.glGetTexParameterPointerv(target, pname, params);
    afterCommand(fnName);
}

// Calls glTextureRangeAPPLE().
void APPLETextureRangeAPI::textureRange(GLenum target, GLsizei length,
                                        const void *pointer) const
{
    static const char *fnName = "glTextureRangeAPPLE";

    beforeCommand(fnName, _api.glTextureRange);
    _api.glTextureRange(target, length, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexArrayObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_vertex_array_object extension.
APPLEVertexArrayObjectAPI::APPLEVertexArrayObjectAPI() :
    BaseExtension("GL_APPLE_vertex_array_object")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEVertexArrayObject &APPLEVertexArrayObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_vertex_array_object entry points.
void APPLEVertexArrayObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindVertexArrayAPPLE().
void APPLEVertexArrayObjectAPI::bindVertexArray(VertexArrayName array) const
{
    static const char *fnName = "glBindVertexArrayAPPLE";

    beforeCommand(fnName, _api.glBindVertexArray);
    _api.glBindVertexArray(array.ID);
    afterCommand(fnName);
}

// Calls glDeleteVertexArraysAPPLE().
void APPLEVertexArrayObjectAPI::deleteVertexArrays(GLsizei n,
                                                   const VertexArrayName *arrays) const
{
    static const char *fnName = "glDeleteVertexArraysAPPLE";

    beforeCommand(fnName, _api.glDeleteVertexArrays);
    _api.glDeleteVertexArrays(n, reinterpret_cast<const GLuint *>(arrays));
    afterCommand(fnName);
}

// Calls glGenVertexArraysAPPLE().
void APPLEVertexArrayObjectAPI::genVertexArrays(GLsizei n,
                                                VertexArrayName *arrays) const
{
    static const char *fnName = "glGenVertexArraysAPPLE";

    beforeCommand(fnName, _api.glGenVertexArrays);
    _api.glGenVertexArrays(n, reinterpret_cast<GLuint *>(arrays));
    afterCommand(fnName);
}

// Calls glIsVertexArrayAPPLE().
Boolean APPLEVertexArrayObjectAPI::isVertexArray(VertexArrayName array) const
{
    static const char *fnName = "glIsVertexArrayAPPLE";

    beforeCommand(fnName, _api.glIsVertexArray);
    GLboolean result = _api.glIsVertexArray(array.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexArrayRangeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_vertex_array_range extension.
APPLEVertexArrayRangeAPI::APPLEVertexArrayRangeAPI() :
    BaseExtension("GL_APPLE_vertex_array_range")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEVertexArrayRange &APPLEVertexArrayRangeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_vertex_array_range entry points.
void APPLEVertexArrayRangeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFlushVertexArrayRangeAPPLE().
void APPLEVertexArrayRangeAPI::flushVertexArrayRange(GLsizei length,
                                                     void *pointer) const
{
    static const char *fnName = "glFlushVertexArrayRangeAPPLE";

    beforeCommand(fnName, _api.glFlushVertexArrayRange);
    _api.glFlushVertexArrayRange(length, pointer);
    afterCommand(fnName);
}

// Calls glVertexArrayParameteriAPPLE().
void APPLEVertexArrayRangeAPI::vertexArrayParameterI(VertexArrayPNameAPPLE pname,
                                                     GLint param) const
{
    static const char *fnName = "glVertexArrayParameteriAPPLE";

    beforeCommand(fnName, _api.glVertexArrayParameteri);
    _api.glVertexArrayParameteri(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glVertexArrayRangeAPPLE().
void APPLEVertexArrayRangeAPI::vertexArrayRange(GLsizei length, void *pointer) const
{
    static const char *fnName = "glVertexArrayRangeAPPLE";

    beforeCommand(fnName, _api.glVertexArrayRange);
    _api.glVertexArrayRange(length, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// APPLEVertexProgramEvaluatorsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_APPLE_vertex_program_evaluators extension.
APPLEVertexProgramEvaluatorsAPI::APPLEVertexProgramEvaluatorsAPI() :
    BaseExtension("GL_APPLE_vertex_program_evaluators")
{
}

// Grant read-only access to the underlying function pointers.
const APPLEVertexProgramEvaluators &APPLEVertexProgramEvaluatorsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_APPLE_vertex_program_evaluators entry points.
void APPLEVertexProgramEvaluatorsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDisableVertexAttribAPPLE().
void APPLEVertexProgramEvaluatorsAPI::disableVertexAttrib(GLuint index,
                                                          GLenum pname) const
{
    static const char *fnName = "glDisableVertexAttribAPPLE";

    beforeCommand(fnName, _api.glDisableVertexAttrib);
    _api.glDisableVertexAttrib(index, pname);
    afterCommand(fnName);
}

// Calls glEnableVertexAttribAPPLE().
void APPLEVertexProgramEvaluatorsAPI::enableVertexAttrib(GLuint index,
                                                         GLenum pname) const
{
    static const char *fnName = "glEnableVertexAttribAPPLE";

    beforeCommand(fnName, _api.glEnableVertexAttrib);
    _api.glEnableVertexAttrib(index, pname);
    afterCommand(fnName);
}

// Calls glIsVertexAttribEnabledAPPLE().
Boolean APPLEVertexProgramEvaluatorsAPI::isVertexAttribEnabled(GLuint index,
                                                               GLenum pname) const
{
    static const char *fnName = "glIsVertexAttribEnabledAPPLE";

    beforeCommand(fnName, _api.glIsVertexAttribEnabled);
    GLboolean result = _api.glIsVertexAttribEnabled(index, pname);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMapVertexAttrib1dAPPLE().
void APPLEVertexProgramEvaluatorsAPI::mapVertexAttrib1D(GLuint index,
                                                        GLuint size, GLdouble u1,
                                                        GLdouble u2,
                                                        GLint stride,
                                                        GLint order,
                                                        const GLdouble *points) const
{
    static const char *fnName = "glMapVertexAttrib1dAPPLE";

    beforeCommand(fnName, _api.glMapVertexAttrib1d);
    _api.glMapVertexAttrib1d(index, size, u1, u2, stride, order, points);
    afterCommand(fnName);
}

// Calls glMapVertexAttrib1fAPPLE().
void APPLEVertexProgramEvaluatorsAPI::mapVertexAttrib1F(GLuint index,
                                                        GLuint size, GLfloat u1,
                                                        GLfloat u2, GLint stride,
                                                        GLint order,
                                                        const GLfloat *points) const
{
    static const char *fnName = "glMapVertexAttrib1fAPPLE";

    beforeCommand(fnName, _api.glMapVertexAttrib1f);
    _api.glMapVertexAttrib1f(index, size, u1, u2, stride, order, points);
    afterCommand(fnName);
}

// Calls glMapVertexAttrib2dAPPLE().
void APPLEVertexProgramEvaluatorsAPI::mapVertexAttrib2D(GLuint index,
                                                        GLuint size, GLdouble u1,
                                                        GLdouble u2,
                                                        GLint ustride,
                                                        GLint uorder,
                                                        GLdouble v1, GLdouble v2,
                                                        GLint vstride,
                                                        GLint vorder,
                                                        const GLdouble *points) const
{
    static const char *fnName = "glMapVertexAttrib2dAPPLE";

    beforeCommand(fnName, _api.glMapVertexAttrib2d);
    _api.glMapVertexAttrib2d(index, size, u1, u2, ustride, uorder, v1, v2,
                             vstride, vorder, points);
    afterCommand(fnName);
}

// Calls glMapVertexAttrib2fAPPLE().
void APPLEVertexProgramEvaluatorsAPI::mapVertexAttrib2F(GLuint index,
                                                        GLuint size, GLfloat u1,
                                                        GLfloat u2,
                                                        GLint ustride,
                                                        GLint uorder, GLfloat v1,
                                                        GLfloat v2,
                                                        GLint vstride,
                                                        GLint vorder,
                                                        const GLfloat *points) const
{
    static const char *fnName = "glMapVertexAttrib2fAPPLE";

    beforeCommand(fnName, _api.glMapVertexAttrib2f);
    _api.glMapVertexAttrib2f(index, size, u1, u2, ustride, uorder, v1, v2,
                             vstride, vorder, points);
    afterCommand(fnName);
}



} // namespace gl
////////////////////////////////////////////////////////////////////////////////

