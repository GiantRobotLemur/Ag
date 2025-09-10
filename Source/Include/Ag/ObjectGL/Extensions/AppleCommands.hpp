//! @file Ag/ObjectGL/Extensions/AppleCommands.hpp
//! @brief The declaration of Apple-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_APPLE_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_APPLE_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "Apple.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_APPLE_element_array extension API.
class APPLEElementArrayAPI : public BaseExtension
{
public:
    // Construction
    APPLEElementArrayAPI();

    // Accessors
    const APPLEElementArray &getRawAPI() const;

    // Operations
    void drawElementArray(PrimitiveType mode, GLint first, GLsizei count) const;
    void drawRangeElementArray(PrimitiveType mode, GLuint start, GLuint end,
                               GLint first, GLsizei count) const;
    void elementPointer(ElementPointerTypeATI type, const void *pointer) const;
    void multiDrawElementArray(PrimitiveType mode, const GLint *first,
                               const GLsizei *count, GLsizei primcount) const;
    void multiDrawRangeElementArray(PrimitiveType mode, GLuint start, GLuint end,
                                    const GLint *first, const GLsizei *count,
                                    GLsizei primcount) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEElementArray _api;
};

// Manages the entry points for the GL_APPLE_fence extension API.
class APPLEFenceAPI : public BaseExtension
{
public:
    // Construction
    APPLEFenceAPI();

    // Accessors
    const APPLEFence &getRawAPI() const;

    // Operations
    void deleteFences(GLsizei n, const GLuint *fences) const;
    void finishFence(GLuint fence) const;
    void finishObject(ObjectTypeAPPLE object, GLint name) const;
    void genFences(GLsizei n, GLuint *fences) const;
    Boolean isFence(GLuint fence) const;
    void setFence(GLuint fence) const;
    Boolean testFence(GLuint fence) const;
    Boolean testObject(ObjectTypeAPPLE object, GLuint name) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEFence _api;
};

// Manages the entry points for the GL_APPLE_flush_buffer_range extension API.
class APPLEFlushBufferRangeAPI : public BaseExtension
{
public:
    // Construction
    APPLEFlushBufferRangeAPI();

    // Accessors
    const APPLEFlushBufferRange &getRawAPI() const;

    // Operations
    void bufferParameterI(GLenum target, GLenum pname, GLint param) const;
    void flushMappedBufferRange(BufferTargetARB target, GLintptr offset,
                                GLsizeiptr size) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEFlushBufferRange _api;
};

// Manages the entry points for the GL_APPLE_object_purgeable extension API.
class APPLEObjectPurgeableAPI : public BaseExtension
{
public:
    // Construction
    APPLEObjectPurgeableAPI();

    // Accessors
    const APPLEObjectPurgeable &getRawAPI() const;

    // Operations
    void getObjectParameterIV(GLenum objectType, GLuint name, GLenum pname,
                              GLint *params) const;
    GLenum objectPurgeable(GLenum objectType, GLuint name, GLenum option) const;
    GLenum objectUnpurgeable(GLenum objectType, GLuint name, GLenum option) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEObjectPurgeable _api;
};

// Manages the entry points for the GL_APPLE_texture_range extension API.
class APPLETextureRangeAPI : public BaseExtension
{
public:
    // Construction
    APPLETextureRangeAPI();

    // Accessors
    const APPLETextureRange &getRawAPI() const;

    // Operations
    void getTexParameterPointerV(GLenum target, GLenum pname, void **params) const;
    void textureRange(GLenum target, GLsizei length, const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLETextureRange _api;
};

// Manages the entry points for the GL_APPLE_vertex_array_object extension API.
class APPLEVertexArrayObjectAPI : public BaseExtension
{
public:
    // Construction
    APPLEVertexArrayObjectAPI();

    // Accessors
    const APPLEVertexArrayObject &getRawAPI() const;

    // Operations
    void bindVertexArray(VertexArrayName array) const;
    void deleteVertexArrays(GLsizei n, const VertexArrayName *arrays) const;
    void genVertexArrays(GLsizei n, VertexArrayName *arrays) const;
    Boolean isVertexArray(VertexArrayName array) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEVertexArrayObject _api;
};

// Manages the entry points for the GL_APPLE_vertex_array_range extension API.
class APPLEVertexArrayRangeAPI : public BaseExtension
{
public:
    // Construction
    APPLEVertexArrayRangeAPI();

    // Accessors
    const APPLEVertexArrayRange &getRawAPI() const;

    // Operations
    void flushVertexArrayRange(GLsizei length, void *pointer) const;
    void vertexArrayParameterI(VertexArrayPNameAPPLE pname, GLint param) const;
    void vertexArrayRange(GLsizei length, void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEVertexArrayRange _api;
};

// Manages the entry points for the GL_APPLE_vertex_program_evaluators extension API.
class APPLEVertexProgramEvaluatorsAPI : public BaseExtension
{
public:
    // Construction
    APPLEVertexProgramEvaluatorsAPI();

    // Accessors
    const APPLEVertexProgramEvaluators &getRawAPI() const;

    // Operations
    void disableVertexAttrib(GLuint index, GLenum pname) const;
    void enableVertexAttrib(GLuint index, GLenum pname) const;
    Boolean isVertexAttribEnabled(GLuint index, GLenum pname) const;
    void mapVertexAttrib1D(GLuint index, GLuint size, GLdouble u1, GLdouble u2,
                           GLint stride, GLint order, const GLdouble *points) const;
    void mapVertexAttrib1F(GLuint index, GLuint size, GLfloat u1, GLfloat u2,
                           GLint stride, GLint order, const GLfloat *points) const;
    void mapVertexAttrib2D(GLuint index, GLuint size, GLdouble u1, GLdouble u2,
                           GLint ustride, GLint uorder, GLdouble v1, GLdouble v2,
                           GLint vstride, GLint vorder, const GLdouble *points) const;
    void mapVertexAttrib2F(GLuint index, GLuint size, GLfloat u1, GLfloat u2,
                           GLint ustride, GLint uorder, GLfloat v1, GLfloat v2,
                           GLint vstride, GLint vorder, const GLfloat *points) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    APPLEVertexProgramEvaluators _api;
};


} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
