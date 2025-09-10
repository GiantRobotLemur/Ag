//! @file ObjectGL/Extensions/ExtCommands.cpp
//! @brief The definition of generic extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/ExtCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// EXTEglImageStorageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_EGL_image_storage extension.
EXTEglImageStorageAPI::EXTEglImageStorageAPI() :
    BaseExtension("GL_EXT_EGL_image_storage")
{
}

// Grant read-only access to the underlying function pointers.
const EXTEglImageStorage &EXTEglImageStorageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_EGL_image_storage entry points.
void EXTEglImageStorageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glEGLImageTargetTexStorageEXT().
void EXTEglImageStorageAPI::eglImageTargetTexStorage(GLenum target,
                                                     GLeglImageOES image,
                                                     const GLint *attrib_list) const
{
    static const char *fnName = "glEGLImageTargetTexStorageEXT";

    beforeCommand(fnName, _api.glEGLImageTargetTexStorage);
    _api.glEGLImageTargetTexStorage(target, image, attrib_list);
    afterCommand(fnName);
}

// Calls glEGLImageTargetTextureStorageEXT().
void EXTEglImageStorageAPI::eglImageTargetTextureStorage(TextureName texture,
                                                         GLeglImageOES image,
                                                         const GLint *attrib_list) const
{
    static const char *fnName = "glEGLImageTargetTextureStorageEXT";

    beforeCommand(fnName, _api.glEGLImageTargetTextureStorage);
    _api.glEGLImageTargetTextureStorage(texture.ID, image, attrib_list);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTBindableUniformAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_bindable_uniform extension.
EXTBindableUniformAPI::EXTBindableUniformAPI() :
    BaseExtension("GL_EXT_bindable_uniform")
{
}

// Grant read-only access to the underlying function pointers.
const EXTBindableUniform &EXTBindableUniformAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_bindable_uniform entry points.
void EXTBindableUniformAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetUniformBufferSizeEXT().
GLint EXTBindableUniformAPI::getUniformBufferSize(ProgramName program,
                                                  GLint location) const
{
    static const char *fnName = "glGetUniformBufferSizeEXT";

    beforeCommand(fnName, _api.glGetUniformBufferSize);
    GLint result = _api.glGetUniformBufferSize(program.ID, location);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformOffsetEXT().
GLintptr EXTBindableUniformAPI::getUniformOffset(ProgramName program,
                                                 GLint location) const
{
    static const char *fnName = "glGetUniformOffsetEXT";

    beforeCommand(fnName, _api.glGetUniformOffset);
    GLintptr result = _api.glGetUniformOffset(program.ID, location);
    afterCommand(fnName);

    return result;
}

// Calls glUniformBufferEXT().
void EXTBindableUniformAPI::uniformBuffer(ProgramName program, GLint location,
                                          BufferName buffer) const
{
    static const char *fnName = "glUniformBufferEXT";

    beforeCommand(fnName, _api.glUniformBuffer);
    _api.glUniformBuffer(program.ID, location, buffer.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendColorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_blend_color extension.
EXTBlendColorAPI::EXTBlendColorAPI() :
    BaseExtension("GL_EXT_blend_color")
{
}

// Grant read-only access to the underlying function pointers.
const EXTBlendColor &EXTBlendColorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_blend_color entry points.
void EXTBlendColorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendColorEXT().
void EXTBlendColorAPI::blendColor(GLfloat red, GLfloat green, GLfloat blue,
                                  GLfloat alpha) const
{
    static const char *fnName = "glBlendColorEXT";

    beforeCommand(fnName, _api.glBlendColor);
    _api.glBlendColor(red, green, blue, alpha);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendEquationSeparateAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_blend_equation_separate extension.
EXTBlendEquationSeparateAPI::EXTBlendEquationSeparateAPI() :
    BaseExtension("GL_EXT_blend_equation_separate")
{
}

// Grant read-only access to the underlying function pointers.
const EXTBlendEquationSeparate &EXTBlendEquationSeparateAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_blend_equation_separate entry points.
void EXTBlendEquationSeparateAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendEquationSeparateEXT().
void EXTBlendEquationSeparateAPI::blendEquationSeparate(BlendEquationModeEXT modeRGB,
                                                        BlendEquationModeEXT modeAlpha) const
{
    static const char *fnName = "glBlendEquationSeparateEXT";

    beforeCommand(fnName, _api.glBlendEquationSeparate);
    _api.glBlendEquationSeparate(toScalar(modeRGB), toScalar(modeAlpha));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendFuncSeparateAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_blend_func_separate extension.
EXTBlendFuncSeparateAPI::EXTBlendFuncSeparateAPI() :
    BaseExtension("GL_EXT_blend_func_separate")
{
}

// Grant read-only access to the underlying function pointers.
const EXTBlendFuncSeparate &EXTBlendFuncSeparateAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_blend_func_separate entry points.
void EXTBlendFuncSeparateAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendFuncSeparateEXT().
void EXTBlendFuncSeparateAPI::blendFuncSeparate(BlendingFactor sfactorRGB,
                                                BlendingFactor dfactorRGB,
                                                BlendingFactor sfactorAlpha,
                                                BlendingFactor dfactorAlpha) const
{
    static const char *fnName = "glBlendFuncSeparateEXT";

    beforeCommand(fnName, _api.glBlendFuncSeparate);
    _api.glBlendFuncSeparate(toScalar(sfactorRGB), toScalar(dfactorRGB),
                             toScalar(sfactorAlpha), toScalar(dfactorAlpha));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTBlendMinmaxAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_blend_minmax extension.
EXTBlendMinmaxAPI::EXTBlendMinmaxAPI() :
    BaseExtension("GL_EXT_blend_minmax")
{
}

// Grant read-only access to the underlying function pointers.
const EXTBlendMinmax &EXTBlendMinmaxAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_blend_minmax entry points.
void EXTBlendMinmaxAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlendEquationEXT().
void EXTBlendMinmaxAPI::blendEquation(BlendEquationModeEXT mode) const
{
    static const char *fnName = "glBlendEquationEXT";

    beforeCommand(fnName, _api.glBlendEquation);
    _api.glBlendEquation(toScalar(mode));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTColorSubtableAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_color_subtable extension.
EXTColorSubtableAPI::EXTColorSubtableAPI() :
    BaseExtension("GL_EXT_color_subtable")
{
}

// Grant read-only access to the underlying function pointers.
const EXTColorSubtable &EXTColorSubtableAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_color_subtable entry points.
void EXTColorSubtableAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorSubTableEXT().
void EXTColorSubtableAPI::colorSubTable(GLenum target, GLsizei start,
                                        GLsizei count, PixelFormat format,
                                        PixelType type, const void *data) const
{
    static const char *fnName = "glColorSubTableEXT";

    beforeCommand(fnName, _api.glColorSubTable);
    _api.glColorSubTable(target, start, count, toScalar(format), toScalar(type),
                         data);
    afterCommand(fnName);
}

// Calls glCopyColorSubTableEXT().
void EXTColorSubtableAPI::copyColorSubTable(GLenum target, GLsizei start,
                                            GLint x, GLint y, GLsizei width) const
{
    static const char *fnName = "glCopyColorSubTableEXT";

    beforeCommand(fnName, _api.glCopyColorSubTable);
    _api.glCopyColorSubTable(target, start, x, y, width);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTCompiledVertexArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_compiled_vertex_array extension.
EXTCompiledVertexArrayAPI::EXTCompiledVertexArrayAPI() :
    BaseExtension("GL_EXT_compiled_vertex_array")
{
}

// Grant read-only access to the underlying function pointers.
const EXTCompiledVertexArray &EXTCompiledVertexArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_compiled_vertex_array entry points.
void EXTCompiledVertexArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glLockArraysEXT().
void EXTCompiledVertexArrayAPI::lockArrays(GLint first, GLsizei count) const
{
    static const char *fnName = "glLockArraysEXT";

    beforeCommand(fnName, _api.glLockArrays);
    _api.glLockArrays(first, count);
    afterCommand(fnName);
}

// Calls glUnlockArraysEXT().
void EXTCompiledVertexArrayAPI::unlockArrays() const
{
    static const char *fnName = "glUnlockArraysEXT";

    beforeCommand(fnName, _api.glUnlockArrays);
    _api.glUnlockArrays();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTConvolutionAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_convolution extension.
EXTConvolutionAPI::EXTConvolutionAPI() :
    BaseExtension("GL_EXT_convolution")
{
}

// Grant read-only access to the underlying function pointers.
const EXTConvolution &EXTConvolutionAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_convolution entry points.
void EXTConvolutionAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glConvolutionFilter1DEXT().
void EXTConvolutionAPI::convolutionFilter1D(ConvolutionTargetEXT target,
                                            InternalFormat internalformat,
                                            GLsizei width, PixelFormat format,
                                            PixelType type, const void *image) const
{
    static const char *fnName = "glConvolutionFilter1DEXT";

    beforeCommand(fnName, _api.glConvolutionFilter1D);
    _api.glConvolutionFilter1D(toScalar(target), toScalar(internalformat), width,
                               toScalar(format), toScalar(type), image);
    afterCommand(fnName);
}

// Calls glConvolutionFilter2DEXT().
void EXTConvolutionAPI::convolutionFilter2D(ConvolutionTargetEXT target,
                                            InternalFormat internalformat,
                                            GLsizei width, GLsizei height,
                                            PixelFormat format, PixelType type,
                                            const void *image) const
{
    static const char *fnName = "glConvolutionFilter2DEXT";

    beforeCommand(fnName, _api.glConvolutionFilter2D);
    _api.glConvolutionFilter2D(toScalar(target), toScalar(internalformat), width,
                               height, toScalar(format), toScalar(type), image);
    afterCommand(fnName);
}

// Calls glConvolutionParameterfEXT().
void EXTConvolutionAPI::convolutionParameterF(ConvolutionTargetEXT target,
                                              ConvolutionParameterEXT pname,
                                              GLfloat params) const
{
    static const char *fnName = "glConvolutionParameterfEXT";

    beforeCommand(fnName, _api.glConvolutionParameterf);
    _api.glConvolutionParameterf(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glConvolutionParameterfvEXT().
void EXTConvolutionAPI::convolutionParameterFV(ConvolutionTargetEXT target,
                                               ConvolutionParameterEXT pname,
                                               const GLfloat *params) const
{
    static const char *fnName = "glConvolutionParameterfvEXT";

    beforeCommand(fnName, _api.glConvolutionParameterfv);
    _api.glConvolutionParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glConvolutionParameteriEXT().
void EXTConvolutionAPI::convolutionParameterI(ConvolutionTargetEXT target,
                                              ConvolutionParameterEXT pname,
                                              GLint params) const
{
    static const char *fnName = "glConvolutionParameteriEXT";

    beforeCommand(fnName, _api.glConvolutionParameteri);
    _api.glConvolutionParameteri(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glConvolutionParameterivEXT().
void EXTConvolutionAPI::convolutionParameterIV(ConvolutionTargetEXT target,
                                               ConvolutionParameterEXT pname,
                                               const GLint *params) const
{
    static const char *fnName = "glConvolutionParameterivEXT";

    beforeCommand(fnName, _api.glConvolutionParameteriv);
    _api.glConvolutionParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glCopyConvolutionFilter1DEXT().
void EXTConvolutionAPI::copyConvolutionFilter1D(ConvolutionTargetEXT target,
                                                InternalFormat internalformat,
                                                GLint x, GLint y, GLsizei width) const
{
    static const char *fnName = "glCopyConvolutionFilter1DEXT";

    beforeCommand(fnName, _api.glCopyConvolutionFilter1D);
    _api.glCopyConvolutionFilter1D(toScalar(target), toScalar(internalformat), x,
                                   y, width);
    afterCommand(fnName);
}

// Calls glCopyConvolutionFilter2DEXT().
void EXTConvolutionAPI::copyConvolutionFilter2D(ConvolutionTargetEXT target,
                                                InternalFormat internalformat,
                                                GLint x, GLint y, GLsizei width,
                                                GLsizei height) const
{
    static const char *fnName = "glCopyConvolutionFilter2DEXT";

    beforeCommand(fnName, _api.glCopyConvolutionFilter2D);
    _api.glCopyConvolutionFilter2D(toScalar(target), toScalar(internalformat), x,
                                   y, width, height);
    afterCommand(fnName);
}

// Calls glGetConvolutionFilterEXT().
void EXTConvolutionAPI::getConvolutionFilter(ConvolutionTargetEXT target,
                                             PixelFormat format, PixelType type,
                                             void *image) const
{
    static const char *fnName = "glGetConvolutionFilterEXT";

    beforeCommand(fnName, _api.glGetConvolutionFilter);
    _api.glGetConvolutionFilter(toScalar(target), toScalar(format),
                                toScalar(type), image);
    afterCommand(fnName);
}

// Calls glGetConvolutionParameterfvEXT().
void EXTConvolutionAPI::getConvolutionParameterFV(ConvolutionTargetEXT target,
                                                  ConvolutionParameterEXT pname,
                                                  GLfloat *params) const
{
    static const char *fnName = "glGetConvolutionParameterfvEXT";

    beforeCommand(fnName, _api.glGetConvolutionParameterfv);
    _api.glGetConvolutionParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetConvolutionParameterivEXT().
void EXTConvolutionAPI::getConvolutionParameterIV(ConvolutionTargetEXT target,
                                                  ConvolutionParameterEXT pname,
                                                  GLint *params) const
{
    static const char *fnName = "glGetConvolutionParameterivEXT";

    beforeCommand(fnName, _api.glGetConvolutionParameteriv);
    _api.glGetConvolutionParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetSeparableFilterEXT().
void EXTConvolutionAPI::getSeparableFilter(SeparableTargetEXT target,
                                           PixelFormat format, PixelType type,
                                           void *row, void *column, void *span) const
{
    static const char *fnName = "glGetSeparableFilterEXT";

    beforeCommand(fnName, _api.glGetSeparableFilter);
    _api.glGetSeparableFilter(toScalar(target), toScalar(format), toScalar(type),
                              row, column, span);
    afterCommand(fnName);
}

// Calls glSeparableFilter2DEXT().
void EXTConvolutionAPI::separableFilter2D(SeparableTargetEXT target,
                                          InternalFormat internalformat,
                                          GLsizei width, GLsizei height,
                                          PixelFormat format, PixelType type,
                                          const void *row, const void *column) const
{
    static const char *fnName = "glSeparableFilter2DEXT";

    beforeCommand(fnName, _api.glSeparableFilter2D);
    _api.glSeparableFilter2D(toScalar(target), toScalar(internalformat), width,
                             height, toScalar(format), toScalar(type), row,
                             column);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTCoordinateFrameAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_coordinate_frame extension.
EXTCoordinateFrameAPI::EXTCoordinateFrameAPI() :
    BaseExtension("GL_EXT_coordinate_frame")
{
}

// Grant read-only access to the underlying function pointers.
const EXTCoordinateFrame &EXTCoordinateFrameAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_coordinate_frame entry points.
void EXTCoordinateFrameAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBinormal3bEXT().
void EXTCoordinateFrameAPI::binormal3B(GLbyte bx, GLbyte by, GLbyte bz) const
{
    static const char *fnName = "glBinormal3bEXT";

    beforeCommand(fnName, _api.glBinormal3b);
    _api.glBinormal3b(bx, by, bz);
    afterCommand(fnName);
}

// Calls glBinormal3bvEXT().
void EXTCoordinateFrameAPI::binormal3BV(const GLbyte *v) const
{
    static const char *fnName = "glBinormal3bvEXT";

    beforeCommand(fnName, _api.glBinormal3bv);
    _api.glBinormal3bv(v);
    afterCommand(fnName);
}

// Calls glBinormal3dEXT().
void EXTCoordinateFrameAPI::binormal3D(GLdouble bx, GLdouble by, GLdouble bz) const
{
    static const char *fnName = "glBinormal3dEXT";

    beforeCommand(fnName, _api.glBinormal3d);
    _api.glBinormal3d(bx, by, bz);
    afterCommand(fnName);
}

// Calls glBinormal3dvEXT().
void EXTCoordinateFrameAPI::binormal3DV(const GLdouble *v) const
{
    static const char *fnName = "glBinormal3dvEXT";

    beforeCommand(fnName, _api.glBinormal3dv);
    _api.glBinormal3dv(v);
    afterCommand(fnName);
}

// Calls glBinormal3fEXT().
void EXTCoordinateFrameAPI::binormal3F(GLfloat bx, GLfloat by, GLfloat bz) const
{
    static const char *fnName = "glBinormal3fEXT";

    beforeCommand(fnName, _api.glBinormal3f);
    _api.glBinormal3f(bx, by, bz);
    afterCommand(fnName);
}

// Calls glBinormal3fvEXT().
void EXTCoordinateFrameAPI::binormal3FV(const GLfloat *v) const
{
    static const char *fnName = "glBinormal3fvEXT";

    beforeCommand(fnName, _api.glBinormal3fv);
    _api.glBinormal3fv(v);
    afterCommand(fnName);
}

// Calls glBinormal3iEXT().
void EXTCoordinateFrameAPI::binormal3I(GLint bx, GLint by, GLint bz) const
{
    static const char *fnName = "glBinormal3iEXT";

    beforeCommand(fnName, _api.glBinormal3i);
    _api.glBinormal3i(bx, by, bz);
    afterCommand(fnName);
}

// Calls glBinormal3ivEXT().
void EXTCoordinateFrameAPI::binormal3IV(const GLint *v) const
{
    static const char *fnName = "glBinormal3ivEXT";

    beforeCommand(fnName, _api.glBinormal3iv);
    _api.glBinormal3iv(v);
    afterCommand(fnName);
}

// Calls glBinormal3sEXT().
void EXTCoordinateFrameAPI::binormal3S(GLshort bx, GLshort by, GLshort bz) const
{
    static const char *fnName = "glBinormal3sEXT";

    beforeCommand(fnName, _api.glBinormal3s);
    _api.glBinormal3s(bx, by, bz);
    afterCommand(fnName);
}

// Calls glBinormal3svEXT().
void EXTCoordinateFrameAPI::binormal3SV(const GLshort *v) const
{
    static const char *fnName = "glBinormal3svEXT";

    beforeCommand(fnName, _api.glBinormal3sv);
    _api.glBinormal3sv(v);
    afterCommand(fnName);
}

// Calls glBinormalPointerEXT().
void EXTCoordinateFrameAPI::binormalPointer(BinormalPointerTypeEXT type,
                                            GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glBinormalPointerEXT";

    beforeCommand(fnName, _api.glBinormalPointer);
    _api.glBinormalPointer(toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glTangent3bEXT().
void EXTCoordinateFrameAPI::tangent3B(GLbyte tx, GLbyte ty, GLbyte tz) const
{
    static const char *fnName = "glTangent3bEXT";

    beforeCommand(fnName, _api.glTangent3b);
    _api.glTangent3b(tx, ty, tz);
    afterCommand(fnName);
}

// Calls glTangent3bvEXT().
void EXTCoordinateFrameAPI::tangent3BV(const GLbyte *v) const
{
    static const char *fnName = "glTangent3bvEXT";

    beforeCommand(fnName, _api.glTangent3bv);
    _api.glTangent3bv(v);
    afterCommand(fnName);
}

// Calls glTangent3dEXT().
void EXTCoordinateFrameAPI::tangent3D(GLdouble tx, GLdouble ty, GLdouble tz) const
{
    static const char *fnName = "glTangent3dEXT";

    beforeCommand(fnName, _api.glTangent3d);
    _api.glTangent3d(tx, ty, tz);
    afterCommand(fnName);
}

// Calls glTangent3dvEXT().
void EXTCoordinateFrameAPI::tangent3DV(const GLdouble *v) const
{
    static const char *fnName = "glTangent3dvEXT";

    beforeCommand(fnName, _api.glTangent3dv);
    _api.glTangent3dv(v);
    afterCommand(fnName);
}

// Calls glTangent3fEXT().
void EXTCoordinateFrameAPI::tangent3F(GLfloat tx, GLfloat ty, GLfloat tz) const
{
    static const char *fnName = "glTangent3fEXT";

    beforeCommand(fnName, _api.glTangent3f);
    _api.glTangent3f(tx, ty, tz);
    afterCommand(fnName);
}

// Calls glTangent3fvEXT().
void EXTCoordinateFrameAPI::tangent3FV(const GLfloat *v) const
{
    static const char *fnName = "glTangent3fvEXT";

    beforeCommand(fnName, _api.glTangent3fv);
    _api.glTangent3fv(v);
    afterCommand(fnName);
}

// Calls glTangent3iEXT().
void EXTCoordinateFrameAPI::tangent3I(GLint tx, GLint ty, GLint tz) const
{
    static const char *fnName = "glTangent3iEXT";

    beforeCommand(fnName, _api.glTangent3i);
    _api.glTangent3i(tx, ty, tz);
    afterCommand(fnName);
}

// Calls glTangent3ivEXT().
void EXTCoordinateFrameAPI::tangent3IV(const GLint *v) const
{
    static const char *fnName = "glTangent3ivEXT";

    beforeCommand(fnName, _api.glTangent3iv);
    _api.glTangent3iv(v);
    afterCommand(fnName);
}

// Calls glTangent3sEXT().
void EXTCoordinateFrameAPI::tangent3S(GLshort tx, GLshort ty, GLshort tz) const
{
    static const char *fnName = "glTangent3sEXT";

    beforeCommand(fnName, _api.glTangent3s);
    _api.glTangent3s(tx, ty, tz);
    afterCommand(fnName);
}

// Calls glTangent3svEXT().
void EXTCoordinateFrameAPI::tangent3SV(const GLshort *v) const
{
    static const char *fnName = "glTangent3svEXT";

    beforeCommand(fnName, _api.glTangent3sv);
    _api.glTangent3sv(v);
    afterCommand(fnName);
}

// Calls glTangentPointerEXT().
void EXTCoordinateFrameAPI::tangentPointer(TangentPointerTypeEXT type,
                                           GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glTangentPointerEXT";

    beforeCommand(fnName, _api.glTangentPointer);
    _api.glTangentPointer(toScalar(type), stride, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTCopyTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_copy_texture extension.
EXTCopyTextureAPI::EXTCopyTextureAPI() :
    BaseExtension("GL_EXT_copy_texture")
{
}

// Grant read-only access to the underlying function pointers.
const EXTCopyTexture &EXTCopyTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_copy_texture entry points.
void EXTCopyTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCopyTexImage1DEXT().
void EXTCopyTextureAPI::copyTexImage1D(TextureTarget target, GLint level,
                                       InternalFormat internalformat, GLint x,
                                       GLint y, GLsizei width, GLint border) const
{
    static const char *fnName = "glCopyTexImage1DEXT";

    beforeCommand(fnName, _api.glCopyTexImage1D);
    _api.glCopyTexImage1D(toScalar(target), level, toScalar(internalformat), x,
                          y, width, border);
    afterCommand(fnName);
}

// Calls glCopyTexImage2DEXT().
void EXTCopyTextureAPI::copyTexImage2D(TextureTarget target, GLint level,
                                       InternalFormat internalformat, GLint x,
                                       GLint y, GLsizei width, GLsizei height,
                                       GLint border) const
{
    static const char *fnName = "glCopyTexImage2DEXT";

    beforeCommand(fnName, _api.glCopyTexImage2D);
    _api.glCopyTexImage2D(toScalar(target), level, toScalar(internalformat), x,
                          y, width, height, border);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage1DEXT().
void EXTCopyTextureAPI::copyTexSubImage1D(TextureTarget target, GLint level,
                                          GLint xoffset, GLint x, GLint y,
                                          GLsizei width) const
{
    static const char *fnName = "glCopyTexSubImage1DEXT";

    beforeCommand(fnName, _api.glCopyTexSubImage1D);
    _api.glCopyTexSubImage1D(toScalar(target), level, xoffset, x, y, width);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage2DEXT().
void EXTCopyTextureAPI::copyTexSubImage2D(TextureTarget target, GLint level,
                                          GLint xoffset, GLint yoffset, GLint x,
                                          GLint y, GLsizei width, GLsizei height) const
{
    static const char *fnName = "glCopyTexSubImage2DEXT";

    beforeCommand(fnName, _api.glCopyTexSubImage2D);
    _api.glCopyTexSubImage2D(toScalar(target), level, xoffset, yoffset, x, y,
                             width, height);
    afterCommand(fnName);
}

// Calls glCopyTexSubImage3DEXT().
void EXTCopyTextureAPI::copyTexSubImage3D(TextureTarget target, GLint level,
                                          GLint xoffset, GLint yoffset,
                                          GLint zoffset, GLint x, GLint y,
                                          GLsizei width, GLsizei height) const
{
    static const char *fnName = "glCopyTexSubImage3DEXT";

    beforeCommand(fnName, _api.glCopyTexSubImage3D);
    _api.glCopyTexSubImage3D(toScalar(target), level, xoffset, yoffset, zoffset,
                             x, y, width, height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTCullVertexAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_cull_vertex extension.
EXTCullVertexAPI::EXTCullVertexAPI() :
    BaseExtension("GL_EXT_cull_vertex")
{
}

// Grant read-only access to the underlying function pointers.
const EXTCullVertex &EXTCullVertexAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_cull_vertex entry points.
void EXTCullVertexAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glCullParameterdvEXT().
void EXTCullVertexAPI::cullParameterDV(CullParameterEXT pname, GLdouble *params) const
{
    static const char *fnName = "glCullParameterdvEXT";

    beforeCommand(fnName, _api.glCullParameterdv);
    _api.glCullParameterdv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glCullParameterfvEXT().
void EXTCullVertexAPI::cullParameterFV(CullParameterEXT pname, GLfloat *params) const
{
    static const char *fnName = "glCullParameterfvEXT";

    beforeCommand(fnName, _api.glCullParameterfv);
    _api.glCullParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDebugLabelAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_debug_label extension.
EXTDebugLabelAPI::EXTDebugLabelAPI() :
    BaseExtension("GL_EXT_debug_label")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDebugLabel &EXTDebugLabelAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_debug_label entry points.
void EXTDebugLabelAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetObjectLabelEXT().
void EXTDebugLabelAPI::getObjectLabel(GLenum type, GLuint object,
                                      GLsizei bufSize, GLsizei *length,
                                      GLchar *label) const
{
    static const char *fnName = "glGetObjectLabelEXT";

    beforeCommand(fnName, _api.glGetObjectLabel);
    _api.glGetObjectLabel(type, object, bufSize, length, label);
    afterCommand(fnName);
}

// Calls glLabelObjectEXT().
void EXTDebugLabelAPI::labelObject(GLenum type, GLuint object, GLsizei length,
                                   const GLchar *label) const
{
    static const char *fnName = "glLabelObjectEXT";

    beforeCommand(fnName, _api.glLabelObject);
    _api.glLabelObject(type, object, length, label);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDebugMarkerAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_debug_marker extension.
EXTDebugMarkerAPI::EXTDebugMarkerAPI() :
    BaseExtension("GL_EXT_debug_marker")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDebugMarker &EXTDebugMarkerAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_debug_marker entry points.
void EXTDebugMarkerAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glInsertEventMarkerEXT().
void EXTDebugMarkerAPI::insertEventMarker(GLsizei length, const GLchar *marker) const
{
    static const char *fnName = "glInsertEventMarkerEXT";

    beforeCommand(fnName, _api.glInsertEventMarker);
    _api.glInsertEventMarker(length, marker);
    afterCommand(fnName);
}

// Calls glPopGroupMarkerEXT().
void EXTDebugMarkerAPI::popGroupMarker() const
{
    static const char *fnName = "glPopGroupMarkerEXT";

    beforeCommand(fnName, _api.glPopGroupMarker);
    _api.glPopGroupMarker();
    afterCommand(fnName);
}

// Calls glPushGroupMarkerEXT().
void EXTDebugMarkerAPI::pushGroupMarker(GLsizei length, const GLchar *marker) const
{
    static const char *fnName = "glPushGroupMarkerEXT";

    beforeCommand(fnName, _api.glPushGroupMarker);
    _api.glPushGroupMarker(length, marker);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDepthBoundsTestAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_depth_bounds_test extension.
EXTDepthBoundsTestAPI::EXTDepthBoundsTestAPI() :
    BaseExtension("GL_EXT_depth_bounds_test")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDepthBoundsTest &EXTDepthBoundsTestAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_depth_bounds_test entry points.
void EXTDepthBoundsTestAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDepthBoundsEXT().
void EXTDepthBoundsTestAPI::depthBounds(GLclampd zmin, GLclampd zmax) const
{
    static const char *fnName = "glDepthBoundsEXT";

    beforeCommand(fnName, _api.glDepthBounds);
    _api.glDepthBounds(zmin, zmax);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDirectStateAccessAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_direct_state_access extension.
EXTDirectStateAccessAPI::EXTDirectStateAccessAPI() :
    BaseExtension("GL_EXT_direct_state_access")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDirectStateAccess &EXTDirectStateAccessAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_direct_state_access entry points.
void EXTDirectStateAccessAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindMultiTextureEXT().
void EXTDirectStateAccessAPI::bindMultiTexture(TextureUnit texunit,
                                               TextureTarget target,
                                               TextureName texture) const
{
    static const char *fnName = "glBindMultiTextureEXT";

    beforeCommand(fnName, _api.glBindMultiTexture);
    _api.glBindMultiTexture(toScalar(texunit), toScalar(target), texture.ID);
    afterCommand(fnName);
}

// Calls glCheckNamedFramebufferStatusEXT().
FramebufferStatus EXTDirectStateAccessAPI::checkNamedFramebufferStatus(FramebufferName framebuffer,
                                                                       FramebufferTarget target) const
{
    static const char *fnName = "glCheckNamedFramebufferStatusEXT";

    beforeCommand(fnName, _api.glCheckNamedFramebufferStatus);
    GLenum result = _api.glCheckNamedFramebufferStatus(framebuffer.ID,
                                                       toScalar(target));
    afterCommand(fnName);

    return static_cast<FramebufferStatus>(result);
}

// Calls glClearNamedBufferDataEXT().
void EXTDirectStateAccessAPI::clearNamedBufferData(BufferName buffer,
                                                   SizedInternalFormat internalformat,
                                                   PixelFormat format,
                                                   PixelType type,
                                                   const void *data) const
{
    static const char *fnName = "glClearNamedBufferDataEXT";

    beforeCommand(fnName, _api.glClearNamedBufferData);
    _api.glClearNamedBufferData(buffer.ID, toScalar(internalformat),
                                toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glClearNamedBufferSubDataEXT().
void EXTDirectStateAccessAPI::clearNamedBufferSubData(BufferName buffer,
                                                      SizedInternalFormat internalformat,
                                                      GLsizeiptr offset,
                                                      GLsizeiptr size,
                                                      PixelFormat format,
                                                      PixelType type,
                                                      const void *data) const
{
    static const char *fnName = "glClearNamedBufferSubDataEXT";

    beforeCommand(fnName, _api.glClearNamedBufferSubData);
    _api.glClearNamedBufferSubData(buffer.ID, toScalar(internalformat), offset,
                                   size, toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glClientAttribDefaultEXT().
void EXTDirectStateAccessAPI::clientAttribDefault(GLbitfield mask) const
{
    static const char *fnName = "glClientAttribDefaultEXT";

    beforeCommand(fnName, _api.glClientAttribDefault);
    _api.glClientAttribDefault(mask);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexImage1DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexImage1D(TextureUnit texunit,
                                                        TextureTarget target,
                                                        GLint level,
                                                        InternalFormat internalformat,
                                                        GLsizei width,
                                                        GLint border,
                                                        GLsizei imageSize,
                                                        const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexImage1DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexImage1D);
    _api.glCompressedMultiTexImage1D(toScalar(texunit), toScalar(target), level,
                                     toScalar(internalformat), width, border,
                                     imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexImage2DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexImage2D(TextureUnit texunit,
                                                        TextureTarget target,
                                                        GLint level,
                                                        InternalFormat internalformat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        GLint border,
                                                        GLsizei imageSize,
                                                        const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexImage2DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexImage2D);
    _api.glCompressedMultiTexImage2D(toScalar(texunit), toScalar(target), level,
                                     toScalar(internalformat), width, height,
                                     border, imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexImage3DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexImage3D(TextureUnit texunit,
                                                        TextureTarget target,
                                                        GLint level,
                                                        InternalFormat internalformat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        GLsizei depth,
                                                        GLint border,
                                                        GLsizei imageSize,
                                                        const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexImage3DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexImage3D);
    _api.glCompressedMultiTexImage3D(toScalar(texunit), toScalar(target), level,
                                     toScalar(internalformat), width, height,
                                     depth, border, imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexSubImage1DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexSubImage1D(TextureUnit texunit,
                                                           TextureTarget target,
                                                           GLint level,
                                                           GLint xoffset,
                                                           GLsizei width,
                                                           InternalFormat format,
                                                           GLsizei imageSize,
                                                           const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexSubImage1DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexSubImage1D);
    _api.glCompressedMultiTexSubImage1D(toScalar(texunit), toScalar(target),
                                        level, xoffset, width, toScalar(format),
                                        imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexSubImage2DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexSubImage2D(TextureUnit texunit,
                                                           TextureTarget target,
                                                           GLint level,
                                                           GLint xoffset,
                                                           GLint yoffset,
                                                           GLsizei width,
                                                           GLsizei height,
                                                           InternalFormat format,
                                                           GLsizei imageSize,
                                                           const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexSubImage2DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexSubImage2D);
    _api.glCompressedMultiTexSubImage2D(toScalar(texunit), toScalar(target),
                                        level, xoffset, yoffset, width, height,
                                        toScalar(format), imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedMultiTexSubImage3DEXT().
void EXTDirectStateAccessAPI::compressedMultiTexSubImage3D(TextureUnit texunit,
                                                           TextureTarget target,
                                                           GLint level,
                                                           GLint xoffset,
                                                           GLint yoffset,
                                                           GLint zoffset,
                                                           GLsizei width,
                                                           GLsizei height,
                                                           GLsizei depth,
                                                           InternalFormat format,
                                                           GLsizei imageSize,
                                                           const void *bits) const
{
    static const char *fnName = "glCompressedMultiTexSubImage3DEXT";

    beforeCommand(fnName, _api.glCompressedMultiTexSubImage3D);
    _api.glCompressedMultiTexSubImage3D(toScalar(texunit), toScalar(target),
                                        level, xoffset, yoffset, zoffset, width,
                                        height, depth, toScalar(format),
                                        imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureImage1DEXT().
void EXTDirectStateAccessAPI::compressedTextureImage1D(TextureName texture,
                                                       TextureTarget target,
                                                       GLint level,
                                                       InternalFormat internalformat,
                                                       GLsizei width,
                                                       GLint border,
                                                       GLsizei imageSize,
                                                       const void *bits) const
{
    static const char *fnName = "glCompressedTextureImage1DEXT";

    beforeCommand(fnName, _api.glCompressedTextureImage1D);
    _api.glCompressedTextureImage1D(texture.ID, toScalar(target), level,
                                    toScalar(internalformat), width, border,
                                    imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureImage2DEXT().
void EXTDirectStateAccessAPI::compressedTextureImage2D(TextureName texture,
                                                       TextureTarget target,
                                                       GLint level,
                                                       InternalFormat internalformat,
                                                       GLsizei width,
                                                       GLsizei height,
                                                       GLint border,
                                                       GLsizei imageSize,
                                                       const void *bits) const
{
    static const char *fnName = "glCompressedTextureImage2DEXT";

    beforeCommand(fnName, _api.glCompressedTextureImage2D);
    _api.glCompressedTextureImage2D(texture.ID, toScalar(target), level,
                                    toScalar(internalformat), width, height,
                                    border, imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureImage3DEXT().
void EXTDirectStateAccessAPI::compressedTextureImage3D(TextureName texture,
                                                       TextureTarget target,
                                                       GLint level,
                                                       InternalFormat internalformat,
                                                       GLsizei width,
                                                       GLsizei height,
                                                       GLsizei depth,
                                                       GLint border,
                                                       GLsizei imageSize,
                                                       const void *bits) const
{
    static const char *fnName = "glCompressedTextureImage3DEXT";

    beforeCommand(fnName, _api.glCompressedTextureImage3D);
    _api.glCompressedTextureImage3D(texture.ID, toScalar(target), level,
                                    toScalar(internalformat), width, height,
                                    depth, border, imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage1DEXT().
void EXTDirectStateAccessAPI::compressedTextureSubImage1D(TextureName texture,
                                                          TextureTarget target,
                                                          GLint level,
                                                          GLint xoffset,
                                                          GLsizei width,
                                                          InternalFormat format,
                                                          GLsizei imageSize,
                                                          const void *bits) const
{
    static const char *fnName = "glCompressedTextureSubImage1DEXT";

    beforeCommand(fnName, _api.glCompressedTextureSubImage1D);
    _api.glCompressedTextureSubImage1D(texture.ID, toScalar(target), level,
                                       xoffset, width, toScalar(format),
                                       imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage2DEXT().
void EXTDirectStateAccessAPI::compressedTextureSubImage2D(TextureName texture,
                                                          TextureTarget target,
                                                          GLint level,
                                                          GLint xoffset,
                                                          GLint yoffset,
                                                          GLsizei width,
                                                          GLsizei height,
                                                          InternalFormat format,
                                                          GLsizei imageSize,
                                                          const void *bits) const
{
    static const char *fnName = "glCompressedTextureSubImage2DEXT";

    beforeCommand(fnName, _api.glCompressedTextureSubImage2D);
    _api.glCompressedTextureSubImage2D(texture.ID, toScalar(target), level,
                                       xoffset, yoffset, width, height,
                                       toScalar(format), imageSize, bits);
    afterCommand(fnName);
}

// Calls glCompressedTextureSubImage3DEXT().
void EXTDirectStateAccessAPI::compressedTextureSubImage3D(TextureName texture,
                                                          TextureTarget target,
                                                          GLint level,
                                                          GLint xoffset,
                                                          GLint yoffset,
                                                          GLint zoffset,
                                                          GLsizei width,
                                                          GLsizei height,
                                                          GLsizei depth,
                                                          InternalFormat format,
                                                          GLsizei imageSize,
                                                          const void *bits) const
{
    static const char *fnName = "glCompressedTextureSubImage3DEXT";

    beforeCommand(fnName, _api.glCompressedTextureSubImage3D);
    _api.glCompressedTextureSubImage3D(texture.ID, toScalar(target), level,
                                       xoffset, yoffset, zoffset, width, height,
                                       depth, toScalar(format), imageSize, bits);
    afterCommand(fnName);
}

// Calls glCopyMultiTexImage1DEXT().
void EXTDirectStateAccessAPI::copyMultiTexImage1D(TextureUnit texunit,
                                                  TextureTarget target,
                                                  GLint level,
                                                  InternalFormat internalformat,
                                                  GLint x, GLint y,
                                                  GLsizei width, GLint border) const
{
    static const char *fnName = "glCopyMultiTexImage1DEXT";

    beforeCommand(fnName, _api.glCopyMultiTexImage1D);
    _api.glCopyMultiTexImage1D(toScalar(texunit), toScalar(target), level,
                               toScalar(internalformat), x, y, width, border);
    afterCommand(fnName);
}

// Calls glCopyMultiTexImage2DEXT().
void EXTDirectStateAccessAPI::copyMultiTexImage2D(TextureUnit texunit,
                                                  TextureTarget target,
                                                  GLint level,
                                                  InternalFormat internalformat,
                                                  GLint x, GLint y,
                                                  GLsizei width, GLsizei height,
                                                  GLint border) const
{
    static const char *fnName = "glCopyMultiTexImage2DEXT";

    beforeCommand(fnName, _api.glCopyMultiTexImage2D);
    _api.glCopyMultiTexImage2D(toScalar(texunit), toScalar(target), level,
                               toScalar(internalformat), x, y, width, height,
                               border);
    afterCommand(fnName);
}

// Calls glCopyMultiTexSubImage1DEXT().
void EXTDirectStateAccessAPI::copyMultiTexSubImage1D(TextureUnit texunit,
                                                     TextureTarget target,
                                                     GLint level, GLint xoffset,
                                                     GLint x, GLint y,
                                                     GLsizei width) const
{
    static const char *fnName = "glCopyMultiTexSubImage1DEXT";

    beforeCommand(fnName, _api.glCopyMultiTexSubImage1D);
    _api.glCopyMultiTexSubImage1D(toScalar(texunit), toScalar(target), level,
                                  xoffset, x, y, width);
    afterCommand(fnName);
}

// Calls glCopyMultiTexSubImage2DEXT().
void EXTDirectStateAccessAPI::copyMultiTexSubImage2D(TextureUnit texunit,
                                                     TextureTarget target,
                                                     GLint level, GLint xoffset,
                                                     GLint yoffset, GLint x,
                                                     GLint y, GLsizei width,
                                                     GLsizei height) const
{
    static const char *fnName = "glCopyMultiTexSubImage2DEXT";

    beforeCommand(fnName, _api.glCopyMultiTexSubImage2D);
    _api.glCopyMultiTexSubImage2D(toScalar(texunit), toScalar(target), level,
                                  xoffset, yoffset, x, y, width, height);
    afterCommand(fnName);
}

// Calls glCopyMultiTexSubImage3DEXT().
void EXTDirectStateAccessAPI::copyMultiTexSubImage3D(TextureUnit texunit,
                                                     TextureTarget target,
                                                     GLint level, GLint xoffset,
                                                     GLint yoffset,
                                                     GLint zoffset, GLint x,
                                                     GLint y, GLsizei width,
                                                     GLsizei height) const
{
    static const char *fnName = "glCopyMultiTexSubImage3DEXT";

    beforeCommand(fnName, _api.glCopyMultiTexSubImage3D);
    _api.glCopyMultiTexSubImage3D(toScalar(texunit), toScalar(target), level,
                                  xoffset, yoffset, zoffset, x, y, width, height);
    afterCommand(fnName);
}

// Calls glCopyTextureImage1DEXT().
void EXTDirectStateAccessAPI::copyTextureImage1D(TextureName texture,
                                                 TextureTarget target,
                                                 GLint level,
                                                 InternalFormat internalformat,
                                                 GLint x, GLint y, GLsizei width,
                                                 GLint border) const
{
    static const char *fnName = "glCopyTextureImage1DEXT";

    beforeCommand(fnName, _api.glCopyTextureImage1D);
    _api.glCopyTextureImage1D(texture.ID, toScalar(target), level,
                              toScalar(internalformat), x, y, width, border);
    afterCommand(fnName);
}

// Calls glCopyTextureImage2DEXT().
void EXTDirectStateAccessAPI::copyTextureImage2D(TextureName texture,
                                                 TextureTarget target,
                                                 GLint level,
                                                 InternalFormat internalformat,
                                                 GLint x, GLint y, GLsizei width,
                                                 GLsizei height, GLint border) const
{
    static const char *fnName = "glCopyTextureImage2DEXT";

    beforeCommand(fnName, _api.glCopyTextureImage2D);
    _api.glCopyTextureImage2D(texture.ID, toScalar(target), level,
                              toScalar(internalformat), x, y, width, height,
                              border);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage1DEXT().
void EXTDirectStateAccessAPI::copyTextureSubImage1D(TextureName texture,
                                                    TextureTarget target,
                                                    GLint level, GLint xoffset,
                                                    GLint x, GLint y,
                                                    GLsizei width) const
{
    static const char *fnName = "glCopyTextureSubImage1DEXT";

    beforeCommand(fnName, _api.glCopyTextureSubImage1D);
    _api.glCopyTextureSubImage1D(texture.ID, toScalar(target), level, xoffset, x,
                                 y, width);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage2DEXT().
void EXTDirectStateAccessAPI::copyTextureSubImage2D(TextureName texture,
                                                    TextureTarget target,
                                                    GLint level, GLint xoffset,
                                                    GLint yoffset, GLint x,
                                                    GLint y, GLsizei width,
                                                    GLsizei height) const
{
    static const char *fnName = "glCopyTextureSubImage2DEXT";

    beforeCommand(fnName, _api.glCopyTextureSubImage2D);
    _api.glCopyTextureSubImage2D(texture.ID, toScalar(target), level, xoffset,
                                 yoffset, x, y, width, height);
    afterCommand(fnName);
}

// Calls glCopyTextureSubImage3DEXT().
void EXTDirectStateAccessAPI::copyTextureSubImage3D(TextureName texture,
                                                    TextureTarget target,
                                                    GLint level, GLint xoffset,
                                                    GLint yoffset, GLint zoffset,
                                                    GLint x, GLint y,
                                                    GLsizei width,
                                                    GLsizei height) const
{
    static const char *fnName = "glCopyTextureSubImage3DEXT";

    beforeCommand(fnName, _api.glCopyTextureSubImage3D);
    _api.glCopyTextureSubImage3D(texture.ID, toScalar(target), level, xoffset,
                                 yoffset, zoffset, x, y, width, height);
    afterCommand(fnName);
}

// Calls glDisableClientStateIndexedEXT().
void EXTDirectStateAccessAPI::disableClientStateIndexed(EnableCap array,
                                                        GLuint index) const
{
    static const char *fnName = "glDisableClientStateIndexedEXT";

    beforeCommand(fnName, _api.glDisableClientStateIndexed);
    _api.glDisableClientStateIndexed(toScalar(array), index);
    afterCommand(fnName);
}

// Calls glDisableClientStateiEXT().
void EXTDirectStateAccessAPI::disableClientStateI(EnableCap array, GLuint index) const
{
    static const char *fnName = "glDisableClientStateiEXT";

    beforeCommand(fnName, _api.glDisableClientStatei);
    _api.glDisableClientStatei(toScalar(array), index);
    afterCommand(fnName);
}

// Calls glDisableIndexedEXT().
void EXTDirectStateAccessAPI::disableIndexed(EnableCap target, GLuint index) const
{
    static const char *fnName = "glDisableIndexedEXT";

    beforeCommand(fnName, _api.glDisableIndexed);
    _api.glDisableIndexed(toScalar(target), index);
    afterCommand(fnName);
}

// Calls glDisableVertexArrayAttribEXT().
void EXTDirectStateAccessAPI::disableVertexArrayAttrib(VertexArrayName vaobj,
                                                       GLuint index) const
{
    static const char *fnName = "glDisableVertexArrayAttribEXT";

    beforeCommand(fnName, _api.glDisableVertexArrayAttrib);
    _api.glDisableVertexArrayAttrib(vaobj.ID, index);
    afterCommand(fnName);
}

// Calls glDisableVertexArrayEXT().
void EXTDirectStateAccessAPI::disableVertexArray(VertexArrayName vaobj,
                                                 EnableCap array) const
{
    static const char *fnName = "glDisableVertexArrayEXT";

    beforeCommand(fnName, _api.glDisableVertexArray);
    _api.glDisableVertexArray(vaobj.ID, toScalar(array));
    afterCommand(fnName);
}

// Calls glEnableClientStateIndexedEXT().
void EXTDirectStateAccessAPI::enableClientStateIndexed(EnableCap array,
                                                       GLuint index) const
{
    static const char *fnName = "glEnableClientStateIndexedEXT";

    beforeCommand(fnName, _api.glEnableClientStateIndexed);
    _api.glEnableClientStateIndexed(toScalar(array), index);
    afterCommand(fnName);
}

// Calls glEnableClientStateiEXT().
void EXTDirectStateAccessAPI::enableClientStateI(EnableCap array, GLuint index) const
{
    static const char *fnName = "glEnableClientStateiEXT";

    beforeCommand(fnName, _api.glEnableClientStatei);
    _api.glEnableClientStatei(toScalar(array), index);
    afterCommand(fnName);
}

// Calls glEnableIndexedEXT().
void EXTDirectStateAccessAPI::enableIndexed(EnableCap target, GLuint index) const
{
    static const char *fnName = "glEnableIndexedEXT";

    beforeCommand(fnName, _api.glEnableIndexed);
    _api.glEnableIndexed(toScalar(target), index);
    afterCommand(fnName);
}

// Calls glEnableVertexArrayAttribEXT().
void EXTDirectStateAccessAPI::enableVertexArrayAttrib(VertexArrayName vaobj,
                                                      GLuint index) const
{
    static const char *fnName = "glEnableVertexArrayAttribEXT";

    beforeCommand(fnName, _api.glEnableVertexArrayAttrib);
    _api.glEnableVertexArrayAttrib(vaobj.ID, index);
    afterCommand(fnName);
}

// Calls glEnableVertexArrayEXT().
void EXTDirectStateAccessAPI::enableVertexArray(VertexArrayName vaobj,
                                                EnableCap array) const
{
    static const char *fnName = "glEnableVertexArrayEXT";

    beforeCommand(fnName, _api.glEnableVertexArray);
    _api.glEnableVertexArray(vaobj.ID, toScalar(array));
    afterCommand(fnName);
}

// Calls glFlushMappedNamedBufferRangeEXT().
void EXTDirectStateAccessAPI::flushMappedNamedBufferRange(BufferName buffer,
                                                          GLintptr offset,
                                                          GLsizeiptr length) const
{
    static const char *fnName = "glFlushMappedNamedBufferRangeEXT";

    beforeCommand(fnName, _api.glFlushMappedNamedBufferRange);
    _api.glFlushMappedNamedBufferRange(buffer.ID, offset, length);
    afterCommand(fnName);
}

// Calls glFramebufferDrawBufferEXT().
void EXTDirectStateAccessAPI::framebufferDrawBuffer(FramebufferName framebuffer,
                                                    DrawBufferMode mode) const
{
    static const char *fnName = "glFramebufferDrawBufferEXT";

    beforeCommand(fnName, _api.glFramebufferDrawBuffer);
    _api.glFramebufferDrawBuffer(framebuffer.ID, toScalar(mode));
    afterCommand(fnName);
}

// Calls glFramebufferDrawBuffersEXT().
void EXTDirectStateAccessAPI::framebufferDrawBuffers(FramebufferName framebuffer,
                                                     GLsizei n,
                                                     const DrawBufferMode *bufs) const
{
    static const char *fnName = "glFramebufferDrawBuffersEXT";

    beforeCommand(fnName, _api.glFramebufferDrawBuffers);
    _api.glFramebufferDrawBuffers(framebuffer.ID, n, toScalarPtr(bufs));
    afterCommand(fnName);
}

// Calls glFramebufferReadBufferEXT().
void EXTDirectStateAccessAPI::framebufferReadBuffer(FramebufferName framebuffer,
                                                    ReadBufferMode mode) const
{
    static const char *fnName = "glFramebufferReadBufferEXT";

    beforeCommand(fnName, _api.glFramebufferReadBuffer);
    _api.glFramebufferReadBuffer(framebuffer.ID, toScalar(mode));
    afterCommand(fnName);
}

// Calls glGenerateMultiTexMipmapEXT().
void EXTDirectStateAccessAPI::generateMultiTexMipmap(TextureUnit texunit,
                                                     TextureTarget target) const
{
    static const char *fnName = "glGenerateMultiTexMipmapEXT";

    beforeCommand(fnName, _api.glGenerateMultiTexMipmap);
    _api.glGenerateMultiTexMipmap(toScalar(texunit), toScalar(target));
    afterCommand(fnName);
}

// Calls glGenerateTextureMipmapEXT().
void EXTDirectStateAccessAPI::generateTextureMipmap(TextureName texture,
                                                    TextureTarget target) const
{
    static const char *fnName = "glGenerateTextureMipmapEXT";

    beforeCommand(fnName, _api.glGenerateTextureMipmap);
    _api.glGenerateTextureMipmap(texture.ID, toScalar(target));
    afterCommand(fnName);
}

// Calls glGetBooleanIndexedvEXT().
void EXTDirectStateAccessAPI::getBooleanIndexedv(BufferTargetARB target,
                                                 GLuint index, Boolean *data) const
{
    static const char *fnName = "glGetBooleanIndexedvEXT";

    beforeCommand(fnName, _api.glGetBooleanIndexedv);
    _api.glGetBooleanIndexedv(toScalar(target), index, toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetCompressedMultiTexImageEXT().
void EXTDirectStateAccessAPI::getCompressedMultiTexImage(TextureUnit texunit,
                                                         TextureTarget target,
                                                         GLint lod, void *img) const
{
    static const char *fnName = "glGetCompressedMultiTexImageEXT";

    beforeCommand(fnName, _api.glGetCompressedMultiTexImage);
    _api.glGetCompressedMultiTexImage(toScalar(texunit), toScalar(target), lod,
                                      img);
    afterCommand(fnName);
}

// Calls glGetCompressedTextureImageEXT().
void EXTDirectStateAccessAPI::getCompressedTextureImage(TextureName texture,
                                                        TextureTarget target,
                                                        GLint lod, void *img) const
{
    static const char *fnName = "glGetCompressedTextureImageEXT";

    beforeCommand(fnName, _api.glGetCompressedTextureImage);
    _api.glGetCompressedTextureImage(texture.ID, toScalar(target), lod, img);
    afterCommand(fnName);
}

// Calls glGetDoubleIndexedvEXT().
void EXTDirectStateAccessAPI::getDoubleIndexedv(GetPName target, GLuint index,
                                                GLdouble *data) const
{
    static const char *fnName = "glGetDoubleIndexedvEXT";

    beforeCommand(fnName, _api.glGetDoubleIndexedv);
    _api.glGetDoubleIndexedv(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetDoublei_vEXT().
void EXTDirectStateAccessAPI::getDoubleIV(GetPName pname, GLuint index,
                                          GLdouble *params) const
{
    static const char *fnName = "glGetDoublei_vEXT";

    beforeCommand(fnName, _api.glGetDoublei_v);
    _api.glGetDoublei_v(toScalar(pname), index, params);
    afterCommand(fnName);
}

// Calls glGetFloatIndexedvEXT().
void EXTDirectStateAccessAPI::getFloatIndexedv(GetPName target, GLuint index,
                                               GLfloat *data) const
{
    static const char *fnName = "glGetFloatIndexedvEXT";

    beforeCommand(fnName, _api.glGetFloatIndexedv);
    _api.glGetFloatIndexedv(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetFloati_vEXT().
void EXTDirectStateAccessAPI::getFloatIV(GetPName pname, GLuint index,
                                         GLfloat *params) const
{
    static const char *fnName = "glGetFloati_vEXT";

    beforeCommand(fnName, _api.glGetFloati_v);
    _api.glGetFloati_v(toScalar(pname), index, params);
    afterCommand(fnName);
}

// Calls glGetFramebufferParameterivEXT().
void EXTDirectStateAccessAPI::getFramebufferParameterIV(FramebufferName framebuffer,
                                                        GetFramebufferParameter pname,
                                                        GLint *params) const
{
    static const char *fnName = "glGetFramebufferParameterivEXT";

    beforeCommand(fnName, _api.glGetFramebufferParameteriv);
    _api.glGetFramebufferParameteriv(framebuffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetIntegerIndexedvEXT().
void EXTDirectStateAccessAPI::getIntegerIndexedv(GetPName target, GLuint index,
                                                 GLint *data) const
{
    static const char *fnName = "glGetIntegerIndexedvEXT";

    beforeCommand(fnName, _api.glGetIntegerIndexedv);
    _api.glGetIntegerIndexedv(toScalar(target), index, data);
    afterCommand(fnName);
}

// Calls glGetMultiTexEnvfvEXT().
void EXTDirectStateAccessAPI::getMultiTexEnvFV(TextureUnit texunit,
                                               GLenum target, GLenum pname,
                                               GLfloat *params) const
{
    static const char *fnName = "glGetMultiTexEnvfvEXT";

    beforeCommand(fnName, _api.glGetMultiTexEnvfv);
    _api.glGetMultiTexEnvfv(toScalar(texunit), target, pname, params);
    afterCommand(fnName);
}

// Calls glGetMultiTexEnvivEXT().
void EXTDirectStateAccessAPI::getMultiTexEnvIV(TextureUnit texunit,
                                               GLenum target, GLenum pname,
                                               GLint *params) const
{
    static const char *fnName = "glGetMultiTexEnvivEXT";

    beforeCommand(fnName, _api.glGetMultiTexEnviv);
    _api.glGetMultiTexEnviv(toScalar(texunit), target, pname, params);
    afterCommand(fnName);
}

// Calls glGetMultiTexGendvEXT().
void EXTDirectStateAccessAPI::getMultiTexGenDV(TextureUnit texunit, GLenum coord,
                                               TextureGenParameter pname,
                                               GLdouble *params) const
{
    static const char *fnName = "glGetMultiTexGendvEXT";

    beforeCommand(fnName, _api.glGetMultiTexGendv);
    _api.glGetMultiTexGendv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexGenfvEXT().
void EXTDirectStateAccessAPI::getMultiTexGenFV(TextureUnit texunit, GLenum coord,
                                               TextureGenParameter pname,
                                               GLfloat *params) const
{
    static const char *fnName = "glGetMultiTexGenfvEXT";

    beforeCommand(fnName, _api.glGetMultiTexGenfv);
    _api.glGetMultiTexGenfv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexGenivEXT().
void EXTDirectStateAccessAPI::getMultiTexGenIV(TextureUnit texunit, GLenum coord,
                                               TextureGenParameter pname,
                                               GLint *params) const
{
    static const char *fnName = "glGetMultiTexGenivEXT";

    beforeCommand(fnName, _api.glGetMultiTexGeniv);
    _api.glGetMultiTexGeniv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexImageEXT().
void EXTDirectStateAccessAPI::getMultiTexImage(TextureUnit texunit,
                                               TextureTarget target, GLint level,
                                               PixelFormat format,
                                               PixelType type, void *pixels) const
{
    static const char *fnName = "glGetMultiTexImageEXT";

    beforeCommand(fnName, _api.glGetMultiTexImage);
    _api.glGetMultiTexImage(toScalar(texunit), toScalar(target), level,
                            toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glGetMultiTexLevelParameterfvEXT().
void EXTDirectStateAccessAPI::getMultiTexLevelParameterFV(TextureUnit texunit,
                                                          TextureTarget target,
                                                          GLint level,
                                                          GetTextureParameter pname,
                                                          GLfloat *params) const
{
    static const char *fnName = "glGetMultiTexLevelParameterfvEXT";

    beforeCommand(fnName, _api.glGetMultiTexLevelParameterfv);
    _api.glGetMultiTexLevelParameterfv(toScalar(texunit), toScalar(target),
                                       level, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexLevelParameterivEXT().
void EXTDirectStateAccessAPI::getMultiTexLevelParameterIV(TextureUnit texunit,
                                                          TextureTarget target,
                                                          GLint level,
                                                          GetTextureParameter pname,
                                                          GLint *params) const
{
    static const char *fnName = "glGetMultiTexLevelParameterivEXT";

    beforeCommand(fnName, _api.glGetMultiTexLevelParameteriv);
    _api.glGetMultiTexLevelParameteriv(toScalar(texunit), toScalar(target),
                                       level, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexParameterIivEXT().
void EXTDirectStateAccessAPI::getMultiTexParameterIIV(TextureUnit texunit,
                                                      TextureTarget target,
                                                      GetTextureParameter pname,
                                                      GLint *params) const
{
    static const char *fnName = "glGetMultiTexParameterIivEXT";

    beforeCommand(fnName, _api.glGetMultiTexParameterIiv);
    _api.glGetMultiTexParameterIiv(toScalar(texunit), toScalar(target),
                                   toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexParameterIuivEXT().
void EXTDirectStateAccessAPI::getMultiTexParameterIUIV(TextureUnit texunit,
                                                       TextureTarget target,
                                                       GetTextureParameter pname,
                                                       GLuint *params) const
{
    static const char *fnName = "glGetMultiTexParameterIuivEXT";

    beforeCommand(fnName, _api.glGetMultiTexParameterIuiv);
    _api.glGetMultiTexParameterIuiv(toScalar(texunit), toScalar(target),
                                    toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexParameterfvEXT().
void EXTDirectStateAccessAPI::getMultiTexParameterFV(TextureUnit texunit,
                                                     TextureTarget target,
                                                     GetTextureParameter pname,
                                                     GLfloat *params) const
{
    static const char *fnName = "glGetMultiTexParameterfvEXT";

    beforeCommand(fnName, _api.glGetMultiTexParameterfv);
    _api.glGetMultiTexParameterfv(toScalar(texunit), toScalar(target),
                                  toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMultiTexParameterivEXT().
void EXTDirectStateAccessAPI::getMultiTexParameterIV(TextureUnit texunit,
                                                     TextureTarget target,
                                                     GetTextureParameter pname,
                                                     GLint *params) const
{
    static const char *fnName = "glGetMultiTexParameterivEXT";

    beforeCommand(fnName, _api.glGetMultiTexParameteriv);
    _api.glGetMultiTexParameteriv(toScalar(texunit), toScalar(target),
                                  toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferParameterivEXT().
void EXTDirectStateAccessAPI::getNamedBufferParameterIV(BufferName buffer,
                                                        BufferPNameARB pname,
                                                        GLint *params) const
{
    static const char *fnName = "glGetNamedBufferParameterivEXT";

    beforeCommand(fnName, _api.glGetNamedBufferParameteriv);
    _api.glGetNamedBufferParameteriv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferPointervEXT().
void EXTDirectStateAccessAPI::getNamedBufferPointerV(BufferName buffer,
                                                     BufferPointerNameARB pname,
                                                     void **params) const
{
    static const char *fnName = "glGetNamedBufferPointervEXT";

    beforeCommand(fnName, _api.glGetNamedBufferPointerv);
    _api.glGetNamedBufferPointerv(buffer.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedBufferSubDataEXT().
void EXTDirectStateAccessAPI::getNamedBufferSubData(BufferName buffer,
                                                    GLintptr offset,
                                                    GLsizeiptr size, void *data) const
{
    static const char *fnName = "glGetNamedBufferSubDataEXT";

    beforeCommand(fnName, _api.glGetNamedBufferSubData);
    _api.glGetNamedBufferSubData(buffer.ID, offset, size, data);
    afterCommand(fnName);
}

// Calls glGetNamedFramebufferAttachmentParameterivEXT().
void EXTDirectStateAccessAPI::getNamedFramebufferAttachmentParameterIV(FramebufferName framebuffer,
                                                                       FramebufferAttachment attachment,
                                                                       FramebufferAttachmentParameterName pname,
                                                                       GLint *params) const
{
    static const char *fnName = "glGetNamedFramebufferAttachmentParameterivEXT";

    beforeCommand(fnName, _api.glGetNamedFramebufferAttachmentParameteriv);
    _api.glGetNamedFramebufferAttachmentParameteriv(framebuffer.ID,
                                                    toScalar(attachment),
                                                    toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetNamedFramebufferParameterivEXT().
void EXTDirectStateAccessAPI::getNamedFramebufferParameterIV(FramebufferName framebuffer,
                                                             GetFramebufferParameter pname,
                                                             GLint *params) const
{
    static const char *fnName = "glGetNamedFramebufferParameterivEXT";

    beforeCommand(fnName, _api.glGetNamedFramebufferParameteriv);
    _api.glGetNamedFramebufferParameteriv(framebuffer.ID, toScalar(pname),
                                          params);
    afterCommand(fnName);
}

// Calls glGetNamedProgramLocalParameterIivEXT().
void EXTDirectStateAccessAPI::getNamedProgramLocalParameterIIV(ProgramName program,
                                                               ProgramTarget target,
                                                               GLuint index,
                                                               GLint *params) const
{
    static const char *fnName = "glGetNamedProgramLocalParameterIivEXT";

    beforeCommand(fnName, _api.glGetNamedProgramLocalParameterIiv);
    _api.glGetNamedProgramLocalParameterIiv(program.ID, toScalar(target), index,
                                            params);
    afterCommand(fnName);
}

// Calls glGetNamedProgramLocalParameterIuivEXT().
void EXTDirectStateAccessAPI::getNamedProgramLocalParameterIUIV(ProgramName program,
                                                                ProgramTarget target,
                                                                GLuint index,
                                                                GLuint *params) const
{
    static const char *fnName = "glGetNamedProgramLocalParameterIuivEXT";

    beforeCommand(fnName, _api.glGetNamedProgramLocalParameterIuiv);
    _api.glGetNamedProgramLocalParameterIuiv(program.ID, toScalar(target), index,
                                             params);
    afterCommand(fnName);
}

// Calls glGetNamedProgramLocalParameterdvEXT().
void EXTDirectStateAccessAPI::getNamedProgramLocalParameterDV(ProgramName program,
                                                              ProgramTarget target,
                                                              GLuint index,
                                                              GLdouble *params) const
{
    static const char *fnName = "glGetNamedProgramLocalParameterdvEXT";

    beforeCommand(fnName, _api.glGetNamedProgramLocalParameterdv);
    _api.glGetNamedProgramLocalParameterdv(program.ID, toScalar(target), index,
                                           params);
    afterCommand(fnName);
}

// Calls glGetNamedProgramLocalParameterfvEXT().
void EXTDirectStateAccessAPI::getNamedProgramLocalParameterFV(ProgramName program,
                                                              ProgramTarget target,
                                                              GLuint index,
                                                              GLfloat *params) const
{
    static const char *fnName = "glGetNamedProgramLocalParameterfvEXT";

    beforeCommand(fnName, _api.glGetNamedProgramLocalParameterfv);
    _api.glGetNamedProgramLocalParameterfv(program.ID, toScalar(target), index,
                                           params);
    afterCommand(fnName);
}

// Calls glGetNamedProgramStringEXT().
void EXTDirectStateAccessAPI::getNamedProgramString(ProgramName program,
                                                    ProgramTarget target,
                                                    ProgramStringProperty pname,
                                                    void *string) const
{
    static const char *fnName = "glGetNamedProgramStringEXT";

    beforeCommand(fnName, _api.glGetNamedProgramString);
    _api.glGetNamedProgramString(program.ID, toScalar(target), toScalar(pname),
                                 string);
    afterCommand(fnName);
}

// Calls glGetNamedProgramivEXT().
void EXTDirectStateAccessAPI::getNamedProgramIV(ProgramName program,
                                                ProgramTarget target,
                                                ProgramPropertyARB pname,
                                                GLint *params) const
{
    static const char *fnName = "glGetNamedProgramivEXT";

    beforeCommand(fnName, _api.glGetNamedProgramiv);
    _api.glGetNamedProgramiv(program.ID, toScalar(target), toScalar(pname),
                             params);
    afterCommand(fnName);
}

// Calls glGetNamedRenderbufferParameterivEXT().
void EXTDirectStateAccessAPI::getNamedRenderbufferParameterIV(RenderbufferName renderbuffer,
                                                              RenderbufferParameterName pname,
                                                              GLint *params) const
{
    static const char *fnName = "glGetNamedRenderbufferParameterivEXT";

    beforeCommand(fnName, _api.glGetNamedRenderbufferParameteriv);
    _api.glGetNamedRenderbufferParameteriv(renderbuffer.ID, toScalar(pname),
                                           params);
    afterCommand(fnName);
}

// Calls glGetPointerIndexedvEXT().
void EXTDirectStateAccessAPI::getPointerIndexedv(GLenum target, GLuint index,
                                                 void **data) const
{
    static const char *fnName = "glGetPointerIndexedvEXT";

    beforeCommand(fnName, _api.glGetPointerIndexedv);
    _api.glGetPointerIndexedv(target, index, data);
    afterCommand(fnName);
}

// Calls glGetPointeri_vEXT().
void EXTDirectStateAccessAPI::getPointerIV(GLenum pname, GLuint index,
                                           void **params) const
{
    static const char *fnName = "glGetPointeri_vEXT";

    beforeCommand(fnName, _api.glGetPointeri_v);
    _api.glGetPointeri_v(pname, index, params);
    afterCommand(fnName);
}

// Calls glGetTextureImageEXT().
void EXTDirectStateAccessAPI::getTextureImage(TextureName texture,
                                              TextureTarget target, GLint level,
                                              PixelFormat format, PixelType type,
                                              void *pixels) const
{
    static const char *fnName = "glGetTextureImageEXT";

    beforeCommand(fnName, _api.glGetTextureImage);
    _api.glGetTextureImage(texture.ID, toScalar(target), level, toScalar(format),
                           toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glGetTextureLevelParameterfvEXT().
void EXTDirectStateAccessAPI::getTextureLevelParameterFV(TextureName texture,
                                                         TextureTarget target,
                                                         GLint level,
                                                         GetTextureParameter pname,
                                                         GLfloat *params) const
{
    static const char *fnName = "glGetTextureLevelParameterfvEXT";

    beforeCommand(fnName, _api.glGetTextureLevelParameterfv);
    _api.glGetTextureLevelParameterfv(texture.ID, toScalar(target), level,
                                      toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureLevelParameterivEXT().
void EXTDirectStateAccessAPI::getTextureLevelParameterIV(TextureName texture,
                                                         TextureTarget target,
                                                         GLint level,
                                                         GetTextureParameter pname,
                                                         GLint *params) const
{
    static const char *fnName = "glGetTextureLevelParameterivEXT";

    beforeCommand(fnName, _api.glGetTextureLevelParameteriv);
    _api.glGetTextureLevelParameteriv(texture.ID, toScalar(target), level,
                                      toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterIivEXT().
void EXTDirectStateAccessAPI::getTextureParameterIIV(TextureName texture,
                                                     TextureTarget target,
                                                     GetTextureParameter pname,
                                                     GLint *params) const
{
    static const char *fnName = "glGetTextureParameterIivEXT";

    beforeCommand(fnName, _api.glGetTextureParameterIiv);
    _api.glGetTextureParameterIiv(texture.ID, toScalar(target), toScalar(pname),
                                  params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterIuivEXT().
void EXTDirectStateAccessAPI::getTextureParameterIUIV(TextureName texture,
                                                      TextureTarget target,
                                                      GetTextureParameter pname,
                                                      GLuint *params) const
{
    static const char *fnName = "glGetTextureParameterIuivEXT";

    beforeCommand(fnName, _api.glGetTextureParameterIuiv);
    _api.glGetTextureParameterIuiv(texture.ID, toScalar(target), toScalar(pname),
                                   params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterfvEXT().
void EXTDirectStateAccessAPI::getTextureParameterFV(TextureName texture,
                                                    TextureTarget target,
                                                    GetTextureParameter pname,
                                                    GLfloat *params) const
{
    static const char *fnName = "glGetTextureParameterfvEXT";

    beforeCommand(fnName, _api.glGetTextureParameterfv);
    _api.glGetTextureParameterfv(texture.ID, toScalar(target), toScalar(pname),
                                 params);
    afterCommand(fnName);
}

// Calls glGetTextureParameterivEXT().
void EXTDirectStateAccessAPI::getTextureParameterIV(TextureName texture,
                                                    TextureTarget target,
                                                    GetTextureParameter pname,
                                                    GLint *params) const
{
    static const char *fnName = "glGetTextureParameterivEXT";

    beforeCommand(fnName, _api.glGetTextureParameteriv);
    _api.glGetTextureParameteriv(texture.ID, toScalar(target), toScalar(pname),
                                 params);
    afterCommand(fnName);
}

// Calls glGetVertexArrayIntegeri_vEXT().
void EXTDirectStateAccessAPI::getVertexArrayIntegerIV(VertexArrayName vaobj,
                                                      GLuint index,
                                                      VertexArrayPName pname,
                                                      GLint *param) const
{
    static const char *fnName = "glGetVertexArrayIntegeri_vEXT";

    beforeCommand(fnName, _api.glGetVertexArrayIntegeri_v);
    _api.glGetVertexArrayIntegeri_v(vaobj.ID, index, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayIntegervEXT().
void EXTDirectStateAccessAPI::getVertexArrayIntegerV(VertexArrayName vaobj,
                                                     VertexArrayPName pname,
                                                     GLint *param) const
{
    static const char *fnName = "glGetVertexArrayIntegervEXT";

    beforeCommand(fnName, _api.glGetVertexArrayIntegerv);
    _api.glGetVertexArrayIntegerv(vaobj.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayPointeri_vEXT().
void EXTDirectStateAccessAPI::getVertexArrayPointerIV(VertexArrayName vaobj,
                                                      GLuint index,
                                                      VertexArrayPName pname,
                                                      void **param) const
{
    static const char *fnName = "glGetVertexArrayPointeri_vEXT";

    beforeCommand(fnName, _api.glGetVertexArrayPointeri_v);
    _api.glGetVertexArrayPointeri_v(vaobj.ID, index, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetVertexArrayPointervEXT().
void EXTDirectStateAccessAPI::getVertexArrayPointerV(VertexArrayName vaobj,
                                                     VertexArrayPName pname,
                                                     void **param) const
{
    static const char *fnName = "glGetVertexArrayPointervEXT";

    beforeCommand(fnName, _api.glGetVertexArrayPointerv);
    _api.glGetVertexArrayPointerv(vaobj.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glIsEnabledIndexedEXT().
Boolean EXTDirectStateAccessAPI::isEnabledIndexed(EnableCap target, GLuint index) const
{
    static const char *fnName = "glIsEnabledIndexedEXT";

    beforeCommand(fnName, _api.glIsEnabledIndexed);
    GLboolean result = _api.glIsEnabledIndexed(toScalar(target), index);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMapNamedBufferEXT().
void *EXTDirectStateAccessAPI::mapNamedBuffer(BufferName buffer,
                                              BufferAccessARB access) const
{
    static const char *fnName = "glMapNamedBufferEXT";

    beforeCommand(fnName, _api.glMapNamedBuffer);
    void *result = _api.glMapNamedBuffer(buffer.ID, toScalar(access));
    afterCommand(fnName);

    return result;
}

// Calls glMapNamedBufferRangeEXT().
void *EXTDirectStateAccessAPI::mapNamedBufferRange(BufferName buffer,
                                                   GLintptr offset,
                                                   GLsizeiptr length,
                                                   GLbitfield  /* MapBufferAccessMask */ access) const
{
    static const char *fnName = "glMapNamedBufferRangeEXT";

    beforeCommand(fnName, _api.glMapNamedBufferRange);
    void *result = _api.glMapNamedBufferRange(buffer.ID, offset, length, access);
    afterCommand(fnName);

    return result;
}

// Calls glMatrixFrustumEXT().
void EXTDirectStateAccessAPI::matrixFrustum(MatrixMode mode, GLdouble left,
                                            GLdouble right, GLdouble bottom,
                                            GLdouble top, GLdouble zNear,
                                            GLdouble zFar) const
{
    static const char *fnName = "glMatrixFrustumEXT";

    beforeCommand(fnName, _api.glMatrixFrustum);
    _api.glMatrixFrustum(toScalar(mode), left, right, bottom, top, zNear, zFar);
    afterCommand(fnName);
}

// Calls glMatrixLoadIdentityEXT().
void EXTDirectStateAccessAPI::matrixLoadIdentity(MatrixMode mode) const
{
    static const char *fnName = "glMatrixLoadIdentityEXT";

    beforeCommand(fnName, _api.glMatrixLoadIdentity);
    _api.glMatrixLoadIdentity(toScalar(mode));
    afterCommand(fnName);
}

// Calls glMatrixLoadTransposedEXT().
void EXTDirectStateAccessAPI::matrixLoadTransposeD(MatrixMode mode,
                                                   const GLdouble *m) const
{
    static const char *fnName = "glMatrixLoadTransposedEXT";

    beforeCommand(fnName, _api.glMatrixLoadTransposed);
    _api.glMatrixLoadTransposed(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixLoadTransposefEXT().
void EXTDirectStateAccessAPI::matrixLoadTransposeF(MatrixMode mode,
                                                   const GLfloat *m) const
{
    static const char *fnName = "glMatrixLoadTransposefEXT";

    beforeCommand(fnName, _api.glMatrixLoadTransposef);
    _api.glMatrixLoadTransposef(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixLoaddEXT().
void EXTDirectStateAccessAPI::matrixLoadD(MatrixMode mode, const GLdouble *m) const
{
    static const char *fnName = "glMatrixLoaddEXT";

    beforeCommand(fnName, _api.glMatrixLoadd);
    _api.glMatrixLoadd(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixLoadfEXT().
void EXTDirectStateAccessAPI::matrixLoadF(MatrixMode mode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixLoadfEXT";

    beforeCommand(fnName, _api.glMatrixLoadf);
    _api.glMatrixLoadf(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixMultTransposedEXT().
void EXTDirectStateAccessAPI::matrixMultTransposeD(MatrixMode mode,
                                                   const GLdouble *m) const
{
    static const char *fnName = "glMatrixMultTransposedEXT";

    beforeCommand(fnName, _api.glMatrixMultTransposed);
    _api.glMatrixMultTransposed(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixMultTransposefEXT().
void EXTDirectStateAccessAPI::matrixMultTransposeF(MatrixMode mode,
                                                   const GLfloat *m) const
{
    static const char *fnName = "glMatrixMultTransposefEXT";

    beforeCommand(fnName, _api.glMatrixMultTransposef);
    _api.glMatrixMultTransposef(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixMultdEXT().
void EXTDirectStateAccessAPI::matrixMultD(MatrixMode mode, const GLdouble *m) const
{
    static const char *fnName = "glMatrixMultdEXT";

    beforeCommand(fnName, _api.glMatrixMultd);
    _api.glMatrixMultd(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixMultfEXT().
void EXTDirectStateAccessAPI::matrixMultF(MatrixMode mode, const GLfloat *m) const
{
    static const char *fnName = "glMatrixMultfEXT";

    beforeCommand(fnName, _api.glMatrixMultf);
    _api.glMatrixMultf(toScalar(mode), m);
    afterCommand(fnName);
}

// Calls glMatrixOrthoEXT().
void EXTDirectStateAccessAPI::matrixOrtho(MatrixMode mode, GLdouble left,
                                          GLdouble right, GLdouble bottom,
                                          GLdouble top, GLdouble zNear,
                                          GLdouble zFar) const
{
    static const char *fnName = "glMatrixOrthoEXT";

    beforeCommand(fnName, _api.glMatrixOrtho);
    _api.glMatrixOrtho(toScalar(mode), left, right, bottom, top, zNear, zFar);
    afterCommand(fnName);
}

// Calls glMatrixPopEXT().
void EXTDirectStateAccessAPI::matrixPop(MatrixMode mode) const
{
    static const char *fnName = "glMatrixPopEXT";

    beforeCommand(fnName, _api.glMatrixPop);
    _api.glMatrixPop(toScalar(mode));
    afterCommand(fnName);
}

// Calls glMatrixPushEXT().
void EXTDirectStateAccessAPI::matrixPush(MatrixMode mode) const
{
    static const char *fnName = "glMatrixPushEXT";

    beforeCommand(fnName, _api.glMatrixPush);
    _api.glMatrixPush(toScalar(mode));
    afterCommand(fnName);
}

// Calls glMatrixRotatedEXT().
void EXTDirectStateAccessAPI::matrixRotateD(MatrixMode mode, GLdouble angle,
                                            GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glMatrixRotatedEXT";

    beforeCommand(fnName, _api.glMatrixRotated);
    _api.glMatrixRotated(toScalar(mode), angle, x, y, z);
    afterCommand(fnName);
}

// Calls glMatrixRotatefEXT().
void EXTDirectStateAccessAPI::matrixRotateF(MatrixMode mode, GLfloat angle,
                                            GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glMatrixRotatefEXT";

    beforeCommand(fnName, _api.glMatrixRotatef);
    _api.glMatrixRotatef(toScalar(mode), angle, x, y, z);
    afterCommand(fnName);
}

// Calls glMatrixScaledEXT().
void EXTDirectStateAccessAPI::matrixScaleD(MatrixMode mode, GLdouble x,
                                           GLdouble y, GLdouble z) const
{
    static const char *fnName = "glMatrixScaledEXT";

    beforeCommand(fnName, _api.glMatrixScaled);
    _api.glMatrixScaled(toScalar(mode), x, y, z);
    afterCommand(fnName);
}

// Calls glMatrixScalefEXT().
void EXTDirectStateAccessAPI::matrixScaleF(MatrixMode mode, GLfloat x, GLfloat y,
                                           GLfloat z) const
{
    static const char *fnName = "glMatrixScalefEXT";

    beforeCommand(fnName, _api.glMatrixScalef);
    _api.glMatrixScalef(toScalar(mode), x, y, z);
    afterCommand(fnName);
}

// Calls glMatrixTranslatedEXT().
void EXTDirectStateAccessAPI::matrixTranslateD(MatrixMode mode, GLdouble x,
                                               GLdouble y, GLdouble z) const
{
    static const char *fnName = "glMatrixTranslatedEXT";

    beforeCommand(fnName, _api.glMatrixTranslated);
    _api.glMatrixTranslated(toScalar(mode), x, y, z);
    afterCommand(fnName);
}

// Calls glMatrixTranslatefEXT().
void EXTDirectStateAccessAPI::matrixTranslateF(MatrixMode mode, GLfloat x,
                                               GLfloat y, GLfloat z) const
{
    static const char *fnName = "glMatrixTranslatefEXT";

    beforeCommand(fnName, _api.glMatrixTranslatef);
    _api.glMatrixTranslatef(toScalar(mode), x, y, z);
    afterCommand(fnName);
}

// Calls glMultiTexBufferEXT().
void EXTDirectStateAccessAPI::multiTexBuffer(TextureUnit texunit,
                                             TextureTarget target,
                                             InternalFormat internalformat,
                                             BufferName buffer) const
{
    static const char *fnName = "glMultiTexBufferEXT";

    beforeCommand(fnName, _api.glMultiTexBuffer);
    _api.glMultiTexBuffer(toScalar(texunit), toScalar(target),
                          toScalar(internalformat), buffer.ID);
    afterCommand(fnName);
}

// Calls glMultiTexCoordPointerEXT().
void EXTDirectStateAccessAPI::multiTexCoordPointer(TextureUnit texunit,
                                                   GLint size,
                                                   TexCoordPointerType type,
                                                   GLsizei stride,
                                                   const void *pointer) const
{
    static const char *fnName = "glMultiTexCoordPointerEXT";

    beforeCommand(fnName, _api.glMultiTexCoordPointer);
    _api.glMultiTexCoordPointer(toScalar(texunit), size, toScalar(type), stride,
                                pointer);
    afterCommand(fnName);
}

// Calls glMultiTexEnvfEXT().
void EXTDirectStateAccessAPI::multiTexEnvF(TextureUnit texunit, GLenum target,
                                           GLenum pname, GLfloat param) const
{
    static const char *fnName = "glMultiTexEnvfEXT";

    beforeCommand(fnName, _api.glMultiTexEnvf);
    _api.glMultiTexEnvf(toScalar(texunit), target, pname, param);
    afterCommand(fnName);
}

// Calls glMultiTexEnvfvEXT().
void EXTDirectStateAccessAPI::multiTexEnvFV(TextureUnit texunit, GLenum target,
                                            GLenum pname, const GLfloat *params) const
{
    static const char *fnName = "glMultiTexEnvfvEXT";

    beforeCommand(fnName, _api.glMultiTexEnvfv);
    _api.glMultiTexEnvfv(toScalar(texunit), target, pname, params);
    afterCommand(fnName);
}

// Calls glMultiTexEnviEXT().
void EXTDirectStateAccessAPI::multiTexEnvI(TextureUnit texunit, GLenum target,
                                           GLenum pname, GLint param) const
{
    static const char *fnName = "glMultiTexEnviEXT";

    beforeCommand(fnName, _api.glMultiTexEnvi);
    _api.glMultiTexEnvi(toScalar(texunit), target, pname, param);
    afterCommand(fnName);
}

// Calls glMultiTexEnvivEXT().
void EXTDirectStateAccessAPI::multiTexEnvIV(TextureUnit texunit, GLenum target,
                                            GLenum pname, const GLint *params) const
{
    static const char *fnName = "glMultiTexEnvivEXT";

    beforeCommand(fnName, _api.glMultiTexEnviv);
    _api.glMultiTexEnviv(toScalar(texunit), target, pname, params);
    afterCommand(fnName);
}

// Calls glMultiTexGendEXT().
void EXTDirectStateAccessAPI::multiTexGenD(TextureUnit texunit, GLenum coord,
                                           TextureGenParameter pname,
                                           GLdouble param) const
{
    static const char *fnName = "glMultiTexGendEXT";

    beforeCommand(fnName, _api.glMultiTexGend);
    _api.glMultiTexGend(toScalar(texunit), coord, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glMultiTexGendvEXT().
void EXTDirectStateAccessAPI::multiTexGenDV(TextureUnit texunit, GLenum coord,
                                            TextureGenParameter pname,
                                            const GLdouble *params) const
{
    static const char *fnName = "glMultiTexGendvEXT";

    beforeCommand(fnName, _api.glMultiTexGendv);
    _api.glMultiTexGendv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexGenfEXT().
void EXTDirectStateAccessAPI::multiTexGenF(TextureUnit texunit, GLenum coord,
                                           TextureGenParameter pname,
                                           GLfloat param) const
{
    static const char *fnName = "glMultiTexGenfEXT";

    beforeCommand(fnName, _api.glMultiTexGenf);
    _api.glMultiTexGenf(toScalar(texunit), coord, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glMultiTexGenfvEXT().
void EXTDirectStateAccessAPI::multiTexGenFV(TextureUnit texunit, GLenum coord,
                                            TextureGenParameter pname,
                                            const GLfloat *params) const
{
    static const char *fnName = "glMultiTexGenfvEXT";

    beforeCommand(fnName, _api.glMultiTexGenfv);
    _api.glMultiTexGenfv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexGeniEXT().
void EXTDirectStateAccessAPI::multiTexGenI(TextureUnit texunit, GLenum coord,
                                           TextureGenParameter pname,
                                           GLint param) const
{
    static const char *fnName = "glMultiTexGeniEXT";

    beforeCommand(fnName, _api.glMultiTexGeni);
    _api.glMultiTexGeni(toScalar(texunit), coord, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glMultiTexGenivEXT().
void EXTDirectStateAccessAPI::multiTexGenIV(TextureUnit texunit, GLenum coord,
                                            TextureGenParameter pname,
                                            const GLint *params) const
{
    static const char *fnName = "glMultiTexGenivEXT";

    beforeCommand(fnName, _api.glMultiTexGeniv);
    _api.glMultiTexGeniv(toScalar(texunit), coord, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexImage1DEXT().
void EXTDirectStateAccessAPI::multiTexImage1D(TextureUnit texunit,
                                              TextureTarget target, GLint level,
                                              InternalFormat internalformat,
                                              GLsizei width, GLint border,
                                              PixelFormat format, PixelType type,
                                              const void *pixels) const
{
    static const char *fnName = "glMultiTexImage1DEXT";

    beforeCommand(fnName, _api.glMultiTexImage1D);
    _api.glMultiTexImage1D(toScalar(texunit), toScalar(target), level,
                           toScalar(internalformat), width, border,
                           toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glMultiTexImage2DEXT().
void EXTDirectStateAccessAPI::multiTexImage2D(TextureUnit texunit,
                                              TextureTarget target, GLint level,
                                              InternalFormat internalformat,
                                              GLsizei width, GLsizei height,
                                              GLint border, PixelFormat format,
                                              PixelType type, const void *pixels) const
{
    static const char *fnName = "glMultiTexImage2DEXT";

    beforeCommand(fnName, _api.glMultiTexImage2D);
    _api.glMultiTexImage2D(toScalar(texunit), toScalar(target), level,
                           toScalar(internalformat), width, height, border,
                           toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glMultiTexImage3DEXT().
void EXTDirectStateAccessAPI::multiTexImage3D(TextureUnit texunit,
                                              TextureTarget target, GLint level,
                                              InternalFormat internalformat,
                                              GLsizei width, GLsizei height,
                                              GLsizei depth, GLint border,
                                              PixelFormat format, PixelType type,
                                              const void *pixels) const
{
    static const char *fnName = "glMultiTexImage3DEXT";

    beforeCommand(fnName, _api.glMultiTexImage3D);
    _api.glMultiTexImage3D(toScalar(texunit), toScalar(target), level,
                           toScalar(internalformat), width, height, depth,
                           border, toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glMultiTexParameterIivEXT().
void EXTDirectStateAccessAPI::multiTexParameterIIV(TextureUnit texunit,
                                                   TextureTarget target,
                                                   TextureParameterName pname,
                                                   const GLint *params) const
{
    static const char *fnName = "glMultiTexParameterIivEXT";

    beforeCommand(fnName, _api.glMultiTexParameterIiv);
    _api.glMultiTexParameterIiv(toScalar(texunit), toScalar(target),
                                toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexParameterIuivEXT().
void EXTDirectStateAccessAPI::multiTexParameterIUIV(TextureUnit texunit,
                                                    TextureTarget target,
                                                    TextureParameterName pname,
                                                    const GLuint *params) const
{
    static const char *fnName = "glMultiTexParameterIuivEXT";

    beforeCommand(fnName, _api.glMultiTexParameterIuiv);
    _api.glMultiTexParameterIuiv(toScalar(texunit), toScalar(target),
                                 toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexParameterfEXT().
void EXTDirectStateAccessAPI::multiTexParameterF(TextureUnit texunit,
                                                 TextureTarget target,
                                                 TextureParameterName pname,
                                                 GLfloat param) const
{
    static const char *fnName = "glMultiTexParameterfEXT";

    beforeCommand(fnName, _api.glMultiTexParameterf);
    _api.glMultiTexParameterf(toScalar(texunit), toScalar(target),
                              toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glMultiTexParameterfvEXT().
void EXTDirectStateAccessAPI::multiTexParameterFV(TextureUnit texunit,
                                                  TextureTarget target,
                                                  TextureParameterName pname,
                                                  const GLfloat *params) const
{
    static const char *fnName = "glMultiTexParameterfvEXT";

    beforeCommand(fnName, _api.glMultiTexParameterfv);
    _api.glMultiTexParameterfv(toScalar(texunit), toScalar(target),
                               toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexParameteriEXT().
void EXTDirectStateAccessAPI::multiTexParameterI(TextureUnit texunit,
                                                 TextureTarget target,
                                                 TextureParameterName pname,
                                                 GLint param) const
{
    static const char *fnName = "glMultiTexParameteriEXT";

    beforeCommand(fnName, _api.glMultiTexParameteri);
    _api.glMultiTexParameteri(toScalar(texunit), toScalar(target),
                              toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glMultiTexParameterivEXT().
void EXTDirectStateAccessAPI::multiTexParameterIV(TextureUnit texunit,
                                                  TextureTarget target,
                                                  TextureParameterName pname,
                                                  const GLint *params) const
{
    static const char *fnName = "glMultiTexParameterivEXT";

    beforeCommand(fnName, _api.glMultiTexParameteriv);
    _api.glMultiTexParameteriv(toScalar(texunit), toScalar(target),
                               toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glMultiTexRenderbufferEXT().
void EXTDirectStateAccessAPI::multiTexRenderbuffer(TextureUnit texunit,
                                                   TextureTarget target,
                                                   RenderbufferName renderbuffer) const
{
    static const char *fnName = "glMultiTexRenderbufferEXT";

    beforeCommand(fnName, _api.glMultiTexRenderbuffer);
    _api.glMultiTexRenderbuffer(toScalar(texunit), toScalar(target),
                                renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glMultiTexSubImage1DEXT().
void EXTDirectStateAccessAPI::multiTexSubImage1D(TextureUnit texunit,
                                                 TextureTarget target,
                                                 GLint level, GLint xoffset,
                                                 GLsizei width,
                                                 PixelFormat format,
                                                 PixelType type,
                                                 const void *pixels) const
{
    static const char *fnName = "glMultiTexSubImage1DEXT";

    beforeCommand(fnName, _api.glMultiTexSubImage1D);
    _api.glMultiTexSubImage1D(toScalar(texunit), toScalar(target), level,
                              xoffset, width, toScalar(format), toScalar(type),
                              pixels);
    afterCommand(fnName);
}

// Calls glMultiTexSubImage2DEXT().
void EXTDirectStateAccessAPI::multiTexSubImage2D(TextureUnit texunit,
                                                 TextureTarget target,
                                                 GLint level, GLint xoffset,
                                                 GLint yoffset, GLsizei width,
                                                 GLsizei height,
                                                 PixelFormat format,
                                                 PixelType type,
                                                 const void *pixels) const
{
    static const char *fnName = "glMultiTexSubImage2DEXT";

    beforeCommand(fnName, _api.glMultiTexSubImage2D);
    _api.glMultiTexSubImage2D(toScalar(texunit), toScalar(target), level,
                              xoffset, yoffset, width, height, toScalar(format),
                              toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glMultiTexSubImage3DEXT().
void EXTDirectStateAccessAPI::multiTexSubImage3D(TextureUnit texunit,
                                                 TextureTarget target,
                                                 GLint level, GLint xoffset,
                                                 GLint yoffset, GLint zoffset,
                                                 GLsizei width, GLsizei height,
                                                 GLsizei depth,
                                                 PixelFormat format,
                                                 PixelType type,
                                                 const void *pixels) const
{
    static const char *fnName = "glMultiTexSubImage3DEXT";

    beforeCommand(fnName, _api.glMultiTexSubImage3D);
    _api.glMultiTexSubImage3D(toScalar(texunit), toScalar(target), level,
                              xoffset, yoffset, zoffset, width, height, depth,
                              toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glNamedBufferDataEXT().
void EXTDirectStateAccessAPI::namedBufferData(BufferName buffer, GLsizeiptr size,
                                              const void *data,
                                              VertexBufferObjectUsage usage) const
{
    static const char *fnName = "glNamedBufferDataEXT";

    beforeCommand(fnName, _api.glNamedBufferData);
    _api.glNamedBufferData(buffer.ID, size, data, toScalar(usage));
    afterCommand(fnName);
}

// Calls glNamedBufferStorageEXT().
void EXTDirectStateAccessAPI::namedBufferStorage(BufferName buffer,
                                                 GLsizeiptr size,
                                                 const void *data,
                                                 GLbitfield  /* BufferStorageMask */ flags) const
{
    static const char *fnName = "glNamedBufferStorageEXT";

    beforeCommand(fnName, _api.glNamedBufferStorage);
    _api.glNamedBufferStorage(buffer.ID, size, data, flags);
    afterCommand(fnName);
}

// Calls glNamedBufferSubDataEXT().
void EXTDirectStateAccessAPI::namedBufferSubData(BufferName buffer,
                                                 GLintptr offset,
                                                 GLsizeiptr size,
                                                 const void *data) const
{
    static const char *fnName = "glNamedBufferSubDataEXT";

    beforeCommand(fnName, _api.glNamedBufferSubData);
    _api.glNamedBufferSubData(buffer.ID, offset, size, data);
    afterCommand(fnName);
}

// Calls glNamedCopyBufferSubDataEXT().
void EXTDirectStateAccessAPI::namedCopyBufferSubData(BufferName readBuffer,
                                                     BufferName writeBuffer,
                                                     GLintptr readOffset,
                                                     GLintptr writeOffset,
                                                     GLsizeiptr size) const
{
    static const char *fnName = "glNamedCopyBufferSubDataEXT";

    beforeCommand(fnName, _api.glNamedCopyBufferSubData);
    _api.glNamedCopyBufferSubData(readBuffer.ID, writeBuffer.ID, readOffset,
                                  writeOffset, size);
    afterCommand(fnName);
}

// Calls glNamedFramebufferParameteriEXT().
void EXTDirectStateAccessAPI::namedFramebufferParameterI(FramebufferName framebuffer,
                                                         FramebufferParameterName pname,
                                                         GLint param) const
{
    static const char *fnName = "glNamedFramebufferParameteriEXT";

    beforeCommand(fnName, _api.glNamedFramebufferParameteri);
    _api.glNamedFramebufferParameteri(framebuffer.ID, toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glNamedFramebufferRenderbufferEXT().
void EXTDirectStateAccessAPI::namedFramebufferRenderbuffer(FramebufferName framebuffer,
                                                           FramebufferAttachment attachment,
                                                           RenderbufferTarget renderbuffertarget,
                                                           RenderbufferName renderbuffer) const
{
    static const char *fnName = "glNamedFramebufferRenderbufferEXT";

    beforeCommand(fnName, _api.glNamedFramebufferRenderbuffer);
    _api.glNamedFramebufferRenderbuffer(framebuffer.ID, toScalar(attachment),
                                        toScalar(renderbuffertarget),
                                        renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTexture1DEXT().
void EXTDirectStateAccessAPI::namedFramebufferTexture1D(FramebufferName framebuffer,
                                                        FramebufferAttachment attachment,
                                                        TextureTarget textarget,
                                                        TextureName texture,
                                                        GLint level) const
{
    static const char *fnName = "glNamedFramebufferTexture1DEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTexture1D);
    _api.glNamedFramebufferTexture1D(framebuffer.ID, toScalar(attachment),
                                     toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTexture2DEXT().
void EXTDirectStateAccessAPI::namedFramebufferTexture2D(FramebufferName framebuffer,
                                                        FramebufferAttachment attachment,
                                                        TextureTarget textarget,
                                                        TextureName texture,
                                                        GLint level) const
{
    static const char *fnName = "glNamedFramebufferTexture2DEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTexture2D);
    _api.glNamedFramebufferTexture2D(framebuffer.ID, toScalar(attachment),
                                     toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTexture3DEXT().
void EXTDirectStateAccessAPI::namedFramebufferTexture3D(FramebufferName framebuffer,
                                                        FramebufferAttachment attachment,
                                                        TextureTarget textarget,
                                                        TextureName texture,
                                                        GLint level,
                                                        GLint zoffset) const
{
    static const char *fnName = "glNamedFramebufferTexture3DEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTexture3D);
    _api.glNamedFramebufferTexture3D(framebuffer.ID, toScalar(attachment),
                                     toScalar(textarget), texture.ID, level,
                                     zoffset);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTextureEXT().
void EXTDirectStateAccessAPI::namedFramebufferTexture(FramebufferName framebuffer,
                                                      FramebufferAttachment attachment,
                                                      TextureName texture,
                                                      GLint level) const
{
    static const char *fnName = "glNamedFramebufferTextureEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTexture);
    _api.glNamedFramebufferTexture(framebuffer.ID, toScalar(attachment),
                                   texture.ID, level);
    afterCommand(fnName);
}

// Calls glNamedFramebufferTextureFaceEXT().
void EXTDirectStateAccessAPI::namedFramebufferTextureFace(FramebufferName framebuffer,
                                                          FramebufferAttachment attachment,
                                                          TextureName texture,
                                                          GLint level,
                                                          TextureTarget face) const
{
    static const char *fnName = "glNamedFramebufferTextureFaceEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTextureFace);
    _api.glNamedFramebufferTextureFace(framebuffer.ID, toScalar(attachment),
                                       texture.ID, level, toScalar(face));
    afterCommand(fnName);
}

// Calls glNamedFramebufferTextureLayerEXT().
void EXTDirectStateAccessAPI::namedFramebufferTextureLayer(FramebufferName framebuffer,
                                                           FramebufferAttachment attachment,
                                                           TextureName texture,
                                                           GLint level,
                                                           GLint layer) const
{
    static const char *fnName = "glNamedFramebufferTextureLayerEXT";

    beforeCommand(fnName, _api.glNamedFramebufferTextureLayer);
    _api.glNamedFramebufferTextureLayer(framebuffer.ID, toScalar(attachment),
                                        texture.ID, level, layer);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameter4dEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameter4D(ProgramName program,
                                                           ProgramTarget target,
                                                           GLuint index,
                                                           GLdouble x,
                                                           GLdouble y,
                                                           GLdouble z,
                                                           GLdouble w) const
{
    static const char *fnName = "glNamedProgramLocalParameter4dEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameter4d);
    _api.glNamedProgramLocalParameter4d(program.ID, toScalar(target), index, x,
                                        y, z, w);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameter4dvEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameter4DV(ProgramName program,
                                                            ProgramTarget target,
                                                            GLuint index,
                                                            const GLdouble *params) const
{
    static const char *fnName = "glNamedProgramLocalParameter4dvEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameter4dv);
    _api.glNamedProgramLocalParameter4dv(program.ID, toScalar(target), index,
                                         params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameter4fEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameter4F(ProgramName program,
                                                           ProgramTarget target,
                                                           GLuint index,
                                                           GLfloat x, GLfloat y,
                                                           GLfloat z, GLfloat w) const
{
    static const char *fnName = "glNamedProgramLocalParameter4fEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameter4f);
    _api.glNamedProgramLocalParameter4f(program.ID, toScalar(target), index, x,
                                        y, z, w);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameter4fvEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameter4FV(ProgramName program,
                                                            ProgramTarget target,
                                                            GLuint index,
                                                            const GLfloat *params) const
{
    static const char *fnName = "glNamedProgramLocalParameter4fvEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameter4fv);
    _api.glNamedProgramLocalParameter4fv(program.ID, toScalar(target), index,
                                         params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameterI4iEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameterI4I(ProgramName program,
                                                            ProgramTarget target,
                                                            GLuint index,
                                                            GLint x, GLint y,
                                                            GLint z, GLint w) const
{
    static const char *fnName = "glNamedProgramLocalParameterI4iEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameterI4i);
    _api.glNamedProgramLocalParameterI4i(program.ID, toScalar(target), index, x,
                                         y, z, w);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameterI4ivEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameterI4IV(ProgramName program,
                                                             ProgramTarget target,
                                                             GLuint index,
                                                             const GLint *params) const
{
    static const char *fnName = "glNamedProgramLocalParameterI4ivEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameterI4iv);
    _api.glNamedProgramLocalParameterI4iv(program.ID, toScalar(target), index,
                                          params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameterI4uiEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameterI4UI(ProgramName program,
                                                             ProgramTarget target,
                                                             GLuint index,
                                                             GLuint x, GLuint y,
                                                             GLuint z, GLuint w) const
{
    static const char *fnName = "glNamedProgramLocalParameterI4uiEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameterI4ui);
    _api.glNamedProgramLocalParameterI4ui(program.ID, toScalar(target), index, x,
                                          y, z, w);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameterI4uivEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameterI4UIV(ProgramName program,
                                                              ProgramTarget target,
                                                              GLuint index,
                                                              const GLuint *params) const
{
    static const char *fnName = "glNamedProgramLocalParameterI4uivEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameterI4uiv);
    _api.glNamedProgramLocalParameterI4uiv(program.ID, toScalar(target), index,
                                           params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParameters4fvEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParameters4FV(ProgramName program,
                                                             ProgramTarget target,
                                                             GLuint index,
                                                             GLsizei count,
                                                             const GLfloat *params) const
{
    static const char *fnName = "glNamedProgramLocalParameters4fvEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParameters4fv);
    _api.glNamedProgramLocalParameters4fv(program.ID, toScalar(target), index,
                                          count, params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParametersI4ivEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParametersI4IV(ProgramName program,
                                                              ProgramTarget target,
                                                              GLuint index,
                                                              GLsizei count,
                                                              const GLint *params) const
{
    static const char *fnName = "glNamedProgramLocalParametersI4ivEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParametersI4iv);
    _api.glNamedProgramLocalParametersI4iv(program.ID, toScalar(target), index,
                                           count, params);
    afterCommand(fnName);
}

// Calls glNamedProgramLocalParametersI4uivEXT().
void EXTDirectStateAccessAPI::namedProgramLocalParametersI4UIV(ProgramName program,
                                                               ProgramTarget target,
                                                               GLuint index,
                                                               GLsizei count,
                                                               const GLuint *params) const
{
    static const char *fnName = "glNamedProgramLocalParametersI4uivEXT";

    beforeCommand(fnName, _api.glNamedProgramLocalParametersI4uiv);
    _api.glNamedProgramLocalParametersI4uiv(program.ID, toScalar(target), index,
                                            count, params);
    afterCommand(fnName);
}

// Calls glNamedProgramStringEXT().
void EXTDirectStateAccessAPI::namedProgramString(ProgramName program,
                                                 ProgramTarget target,
                                                 ProgramFormat format,
                                                 GLsizei len, const void *string) const
{
    static const char *fnName = "glNamedProgramStringEXT";

    beforeCommand(fnName, _api.glNamedProgramString);
    _api.glNamedProgramString(program.ID, toScalar(target), toScalar(format),
                              len, string);
    afterCommand(fnName);
}

// Calls glNamedRenderbufferStorageEXT().
void EXTDirectStateAccessAPI::namedRenderbufferStorage(RenderbufferName renderbuffer,
                                                       InternalFormat internalformat,
                                                       GLsizei width,
                                                       GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorageEXT";

    beforeCommand(fnName, _api.glNamedRenderbufferStorage);
    _api.glNamedRenderbufferStorage(renderbuffer.ID, toScalar(internalformat),
                                    width, height);
    afterCommand(fnName);
}

// Calls glNamedRenderbufferStorageMultisampleCoverageEXT().
void EXTDirectStateAccessAPI::namedRenderbufferStorageMultisampleCoverage(RenderbufferName renderbuffer,
                                                                          GLsizei coverageSamples,
                                                                          GLsizei colorSamples,
                                                                          InternalFormat internalformat,
                                                                          GLsizei width,
                                                                          GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorageMultisampleCoverageEXT";

    beforeCommand(fnName, _api.glNamedRenderbufferStorageMultisampleCoverage);
    _api.glNamedRenderbufferStorageMultisampleCoverage(renderbuffer.ID,
                                                       coverageSamples,
                                                       colorSamples,
                                                       toScalar(internalformat),
                                                       width, height);
    afterCommand(fnName);
}

// Calls glNamedRenderbufferStorageMultisampleEXT().
void EXTDirectStateAccessAPI::namedRenderbufferStorageMultisample(RenderbufferName renderbuffer,
                                                                  GLsizei samples,
                                                                  InternalFormat internalformat,
                                                                  GLsizei width,
                                                                  GLsizei height) const
{
    static const char *fnName = "glNamedRenderbufferStorageMultisampleEXT";

    beforeCommand(fnName, _api.glNamedRenderbufferStorageMultisample);
    _api.glNamedRenderbufferStorageMultisample(renderbuffer.ID, samples,
                                               toScalar(internalformat), width,
                                               height);
    afterCommand(fnName);
}

// Calls glProgramUniform1dEXT().
void EXTDirectStateAccessAPI::programUniform1D(ProgramName program,
                                               GLint location, GLdouble x) const
{
    static const char *fnName = "glProgramUniform1dEXT";

    beforeCommand(fnName, _api.glProgramUniform1d);
    _api.glProgramUniform1d(program.ID, location, x);
    afterCommand(fnName);
}

// Calls glProgramUniform1dvEXT().
void EXTDirectStateAccessAPI::programUniform1DV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform1dvEXT";

    beforeCommand(fnName, _api.glProgramUniform1dv);
    _api.glProgramUniform1dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1fEXT().
void EXTDirectStateAccessAPI::programUniform1F(ProgramName program,
                                               GLint location, GLfloat v0) const
{
    static const char *fnName = "glProgramUniform1fEXT";

    beforeCommand(fnName, _api.glProgramUniform1f);
    _api.glProgramUniform1f(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1fvEXT().
void EXTDirectStateAccessAPI::programUniform1FV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform1fvEXT";

    beforeCommand(fnName, _api.glProgramUniform1fv);
    _api.glProgramUniform1fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1iEXT().
void EXTDirectStateAccessAPI::programUniform1I(ProgramName program,
                                               GLint location, GLint v0) const
{
    static const char *fnName = "glProgramUniform1iEXT";

    beforeCommand(fnName, _api.glProgramUniform1i);
    _api.glProgramUniform1i(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1ivEXT().
void EXTDirectStateAccessAPI::programUniform1IV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLint *value) const
{
    static const char *fnName = "glProgramUniform1ivEXT";

    beforeCommand(fnName, _api.glProgramUniform1iv);
    _api.glProgramUniform1iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform1uiEXT().
void EXTDirectStateAccessAPI::programUniform1UI(ProgramName program,
                                                GLint location, GLuint v0) const
{
    static const char *fnName = "glProgramUniform1uiEXT";

    beforeCommand(fnName, _api.glProgramUniform1ui);
    _api.glProgramUniform1ui(program.ID, location, v0);
    afterCommand(fnName);
}

// Calls glProgramUniform1uivEXT().
void EXTDirectStateAccessAPI::programUniform1UIV(ProgramName program,
                                                 GLint location, GLsizei count,
                                                 const GLuint *value) const
{
    static const char *fnName = "glProgramUniform1uivEXT";

    beforeCommand(fnName, _api.glProgramUniform1uiv);
    _api.glProgramUniform1uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2dEXT().
void EXTDirectStateAccessAPI::programUniform2D(ProgramName program,
                                               GLint location, GLdouble x,
                                               GLdouble y) const
{
    static const char *fnName = "glProgramUniform2dEXT";

    beforeCommand(fnName, _api.glProgramUniform2d);
    _api.glProgramUniform2d(program.ID, location, x, y);
    afterCommand(fnName);
}

// Calls glProgramUniform2dvEXT().
void EXTDirectStateAccessAPI::programUniform2DV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform2dvEXT";

    beforeCommand(fnName, _api.glProgramUniform2dv);
    _api.glProgramUniform2dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2fEXT().
void EXTDirectStateAccessAPI::programUniform2F(ProgramName program,
                                               GLint location, GLfloat v0,
                                               GLfloat v1) const
{
    static const char *fnName = "glProgramUniform2fEXT";

    beforeCommand(fnName, _api.glProgramUniform2f);
    _api.glProgramUniform2f(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2fvEXT().
void EXTDirectStateAccessAPI::programUniform2FV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform2fvEXT";

    beforeCommand(fnName, _api.glProgramUniform2fv);
    _api.glProgramUniform2fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2iEXT().
void EXTDirectStateAccessAPI::programUniform2I(ProgramName program,
                                               GLint location, GLint v0,
                                               GLint v1) const
{
    static const char *fnName = "glProgramUniform2iEXT";

    beforeCommand(fnName, _api.glProgramUniform2i);
    _api.glProgramUniform2i(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2ivEXT().
void EXTDirectStateAccessAPI::programUniform2IV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLint *value) const
{
    static const char *fnName = "glProgramUniform2ivEXT";

    beforeCommand(fnName, _api.glProgramUniform2iv);
    _api.glProgramUniform2iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform2uiEXT().
void EXTDirectStateAccessAPI::programUniform2UI(ProgramName program,
                                                GLint location, GLuint v0,
                                                GLuint v1) const
{
    static const char *fnName = "glProgramUniform2uiEXT";

    beforeCommand(fnName, _api.glProgramUniform2ui);
    _api.glProgramUniform2ui(program.ID, location, v0, v1);
    afterCommand(fnName);
}

// Calls glProgramUniform2uivEXT().
void EXTDirectStateAccessAPI::programUniform2UIV(ProgramName program,
                                                 GLint location, GLsizei count,
                                                 const GLuint *value) const
{
    static const char *fnName = "glProgramUniform2uivEXT";

    beforeCommand(fnName, _api.glProgramUniform2uiv);
    _api.glProgramUniform2uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3dEXT().
void EXTDirectStateAccessAPI::programUniform3D(ProgramName program,
                                               GLint location, GLdouble x,
                                               GLdouble y, GLdouble z) const
{
    static const char *fnName = "glProgramUniform3dEXT";

    beforeCommand(fnName, _api.glProgramUniform3d);
    _api.glProgramUniform3d(program.ID, location, x, y, z);
    afterCommand(fnName);
}

// Calls glProgramUniform3dvEXT().
void EXTDirectStateAccessAPI::programUniform3DV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform3dvEXT";

    beforeCommand(fnName, _api.glProgramUniform3dv);
    _api.glProgramUniform3dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3fEXT().
void EXTDirectStateAccessAPI::programUniform3F(ProgramName program,
                                               GLint location, GLfloat v0,
                                               GLfloat v1, GLfloat v2) const
{
    static const char *fnName = "glProgramUniform3fEXT";

    beforeCommand(fnName, _api.glProgramUniform3f);
    _api.glProgramUniform3f(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3fvEXT().
void EXTDirectStateAccessAPI::programUniform3FV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform3fvEXT";

    beforeCommand(fnName, _api.glProgramUniform3fv);
    _api.glProgramUniform3fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3iEXT().
void EXTDirectStateAccessAPI::programUniform3I(ProgramName program,
                                               GLint location, GLint v0,
                                               GLint v1, GLint v2) const
{
    static const char *fnName = "glProgramUniform3iEXT";

    beforeCommand(fnName, _api.glProgramUniform3i);
    _api.glProgramUniform3i(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3ivEXT().
void EXTDirectStateAccessAPI::programUniform3IV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLint *value) const
{
    static const char *fnName = "glProgramUniform3ivEXT";

    beforeCommand(fnName, _api.glProgramUniform3iv);
    _api.glProgramUniform3iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform3uiEXT().
void EXTDirectStateAccessAPI::programUniform3UI(ProgramName program,
                                                GLint location, GLuint v0,
                                                GLuint v1, GLuint v2) const
{
    static const char *fnName = "glProgramUniform3uiEXT";

    beforeCommand(fnName, _api.glProgramUniform3ui);
    _api.glProgramUniform3ui(program.ID, location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glProgramUniform3uivEXT().
void EXTDirectStateAccessAPI::programUniform3UIV(ProgramName program,
                                                 GLint location, GLsizei count,
                                                 const GLuint *value) const
{
    static const char *fnName = "glProgramUniform3uivEXT";

    beforeCommand(fnName, _api.glProgramUniform3uiv);
    _api.glProgramUniform3uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4dEXT().
void EXTDirectStateAccessAPI::programUniform4D(ProgramName program,
                                               GLint location, GLdouble x,
                                               GLdouble y, GLdouble z,
                                               GLdouble w) const
{
    static const char *fnName = "glProgramUniform4dEXT";

    beforeCommand(fnName, _api.glProgramUniform4d);
    _api.glProgramUniform4d(program.ID, location, x, y, z, w);
    afterCommand(fnName);
}

// Calls glProgramUniform4dvEXT().
void EXTDirectStateAccessAPI::programUniform4DV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLdouble *value) const
{
    static const char *fnName = "glProgramUniform4dvEXT";

    beforeCommand(fnName, _api.glProgramUniform4dv);
    _api.glProgramUniform4dv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4fEXT().
void EXTDirectStateAccessAPI::programUniform4F(ProgramName program,
                                               GLint location, GLfloat v0,
                                               GLfloat v1, GLfloat v2,
                                               GLfloat v3) const
{
    static const char *fnName = "glProgramUniform4fEXT";

    beforeCommand(fnName, _api.glProgramUniform4f);
    _api.glProgramUniform4f(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4fvEXT().
void EXTDirectStateAccessAPI::programUniform4FV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLfloat *value) const
{
    static const char *fnName = "glProgramUniform4fvEXT";

    beforeCommand(fnName, _api.glProgramUniform4fv);
    _api.glProgramUniform4fv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4iEXT().
void EXTDirectStateAccessAPI::programUniform4I(ProgramName program,
                                               GLint location, GLint v0,
                                               GLint v1, GLint v2, GLint v3) const
{
    static const char *fnName = "glProgramUniform4iEXT";

    beforeCommand(fnName, _api.glProgramUniform4i);
    _api.glProgramUniform4i(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4ivEXT().
void EXTDirectStateAccessAPI::programUniform4IV(ProgramName program,
                                                GLint location, GLsizei count,
                                                const GLint *value) const
{
    static const char *fnName = "glProgramUniform4ivEXT";

    beforeCommand(fnName, _api.glProgramUniform4iv);
    _api.glProgramUniform4iv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniform4uiEXT().
void EXTDirectStateAccessAPI::programUniform4UI(ProgramName program,
                                                GLint location, GLuint v0,
                                                GLuint v1, GLuint v2, GLuint v3) const
{
    static const char *fnName = "glProgramUniform4uiEXT";

    beforeCommand(fnName, _api.glProgramUniform4ui);
    _api.glProgramUniform4ui(program.ID, location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glProgramUniform4uivEXT().
void EXTDirectStateAccessAPI::programUniform4UIV(ProgramName program,
                                                 GLint location, GLsizei count,
                                                 const GLuint *value) const
{
    static const char *fnName = "glProgramUniform4uivEXT";

    beforeCommand(fnName, _api.glProgramUniform4uiv);
    _api.glProgramUniform4uiv(program.ID, location, count, value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2DV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2dv);
    _api.glProgramUniformMatrix2dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2FV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2fv);
    _api.glProgramUniformMatrix2fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x3dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2x3DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x3dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x3dv);
    _api.glProgramUniformMatrix2x3dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x3fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2x3FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x3fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x3fv);
    _api.glProgramUniformMatrix2x3fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x4dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2x4DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x4dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x4dv);
    _api.glProgramUniformMatrix2x4dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix2x4fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix2x4FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix2x4fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix2x4fv);
    _api.glProgramUniformMatrix2x4fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3DV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3dv);
    _api.glProgramUniformMatrix3dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3FV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3fv);
    _api.glProgramUniformMatrix3fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x2dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3x2DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x2dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x2dv);
    _api.glProgramUniformMatrix3x2dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x2fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3x2FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x2fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x2fv);
    _api.glProgramUniformMatrix3x2fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x4dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3x4DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x4dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x4dv);
    _api.glProgramUniformMatrix3x4dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix3x4fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix3x4FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix3x4fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix3x4fv);
    _api.glProgramUniformMatrix3x4fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4DV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4dv);
    _api.glProgramUniformMatrix4dv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4FV(ProgramName program,
                                                      GLint location,
                                                      GLsizei count,
                                                      Boolean transpose,
                                                      const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4fv);
    _api.glProgramUniformMatrix4fv(program.ID, location, count,
                                   toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x2dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4x2DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x2dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x2dv);
    _api.glProgramUniformMatrix4x2dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x2fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4x2FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x2fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x2fv);
    _api.glProgramUniformMatrix4x2fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x3dvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4x3DV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLdouble *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x3dvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x3dv);
    _api.glProgramUniformMatrix4x3dv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glProgramUniformMatrix4x3fvEXT().
void EXTDirectStateAccessAPI::programUniformMatrix4x3FV(ProgramName program,
                                                        GLint location,
                                                        GLsizei count,
                                                        Boolean transpose,
                                                        const GLfloat *value) const
{
    static const char *fnName = "glProgramUniformMatrix4x3fvEXT";

    beforeCommand(fnName, _api.glProgramUniformMatrix4x3fv);
    _api.glProgramUniformMatrix4x3fv(program.ID, location, count,
                                     toScalar(transpose), value);
    afterCommand(fnName);
}

// Calls glPushClientAttribDefaultEXT().
void EXTDirectStateAccessAPI::pushClientAttribDefault(GLbitfield mask) const
{
    static const char *fnName = "glPushClientAttribDefaultEXT";

    beforeCommand(fnName, _api.glPushClientAttribDefault);
    _api.glPushClientAttribDefault(mask);
    afterCommand(fnName);
}

// Calls glTextureBufferEXT().
void EXTDirectStateAccessAPI::textureBuffer(TextureName texture,
                                            TextureTarget target,
                                            SizedInternalFormat internalformat,
                                            BufferName buffer) const
{
    static const char *fnName = "glTextureBufferEXT";

    beforeCommand(fnName, _api.glTextureBuffer);
    _api.glTextureBuffer(texture.ID, toScalar(target), toScalar(internalformat),
                         buffer.ID);
    afterCommand(fnName);
}

// Calls glTextureBufferRangeEXT().
void EXTDirectStateAccessAPI::textureBufferRange(TextureName texture,
                                                 TextureTarget target,
                                                 SizedInternalFormat internalformat,
                                                 BufferName buffer,
                                                 GLintptr offset,
                                                 GLsizeiptr size) const
{
    static const char *fnName = "glTextureBufferRangeEXT";

    beforeCommand(fnName, _api.glTextureBufferRange);
    _api.glTextureBufferRange(texture.ID, toScalar(target),
                              toScalar(internalformat), buffer.ID, offset, size);
    afterCommand(fnName);
}

// Calls glTextureImage1DEXT().
void EXTDirectStateAccessAPI::textureImage1D(TextureName texture,
                                             TextureTarget target, GLint level,
                                             InternalFormat internalformat,
                                             GLsizei width, GLint border,
                                             PixelFormat format, PixelType type,
                                             const void *pixels) const
{
    static const char *fnName = "glTextureImage1DEXT";

    beforeCommand(fnName, _api.glTextureImage1D);
    _api.glTextureImage1D(texture.ID, toScalar(target), level,
                          toScalar(internalformat), width, border,
                          toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureImage2DEXT().
void EXTDirectStateAccessAPI::textureImage2D(TextureName texture,
                                             TextureTarget target, GLint level,
                                             InternalFormat internalformat,
                                             GLsizei width, GLsizei height,
                                             GLint border, PixelFormat format,
                                             PixelType type, const void *pixels) const
{
    static const char *fnName = "glTextureImage2DEXT";

    beforeCommand(fnName, _api.glTextureImage2D);
    _api.glTextureImage2D(texture.ID, toScalar(target), level,
                          toScalar(internalformat), width, height, border,
                          toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureImage3DEXT().
void EXTDirectStateAccessAPI::textureImage3D(TextureName texture,
                                             TextureTarget target, GLint level,
                                             InternalFormat internalformat,
                                             GLsizei width, GLsizei height,
                                             GLsizei depth, GLint border,
                                             PixelFormat format, PixelType type,
                                             const void *pixels) const
{
    static const char *fnName = "glTextureImage3DEXT";

    beforeCommand(fnName, _api.glTextureImage3D);
    _api.glTextureImage3D(texture.ID, toScalar(target), level,
                          toScalar(internalformat), width, height, depth, border,
                          toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexturePageCommitmentEXT().
void EXTDirectStateAccessAPI::texturePageCommitment(TextureName texture,
                                                    GLint level, GLint xoffset,
                                                    GLint yoffset, GLint zoffset,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth,
                                                    Boolean commit) const
{
    static const char *fnName = "glTexturePageCommitmentEXT";

    beforeCommand(fnName, _api.glTexturePageCommitment);
    _api.glTexturePageCommitment(texture.ID, level, xoffset, yoffset, zoffset,
                                 width, height, depth, toScalar(commit));
    afterCommand(fnName);
}

// Calls glTextureParameterIivEXT().
void EXTDirectStateAccessAPI::textureParameterIIV(TextureName texture,
                                                  TextureTarget target,
                                                  TextureParameterName pname,
                                                  const GLint *params) const
{
    static const char *fnName = "glTextureParameterIivEXT";

    beforeCommand(fnName, _api.glTextureParameterIiv);
    _api.glTextureParameterIiv(texture.ID, toScalar(target), toScalar(pname),
                               params);
    afterCommand(fnName);
}

// Calls glTextureParameterIuivEXT().
void EXTDirectStateAccessAPI::textureParameterIUIV(TextureName texture,
                                                   TextureTarget target,
                                                   TextureParameterName pname,
                                                   const GLuint *params) const
{
    static const char *fnName = "glTextureParameterIuivEXT";

    beforeCommand(fnName, _api.glTextureParameterIuiv);
    _api.glTextureParameterIuiv(texture.ID, toScalar(target), toScalar(pname),
                                params);
    afterCommand(fnName);
}

// Calls glTextureParameterfEXT().
void EXTDirectStateAccessAPI::textureParameterF(TextureName texture,
                                                TextureTarget target,
                                                TextureParameterName pname,
                                                GLfloat param) const
{
    static const char *fnName = "glTextureParameterfEXT";

    beforeCommand(fnName, _api.glTextureParameterf);
    _api.glTextureParameterf(texture.ID, toScalar(target), toScalar(pname),
                             param);
    afterCommand(fnName);
}

// Calls glTextureParameterfvEXT().
void EXTDirectStateAccessAPI::textureParameterFV(TextureName texture,
                                                 TextureTarget target,
                                                 TextureParameterName pname,
                                                 const GLfloat *params) const
{
    static const char *fnName = "glTextureParameterfvEXT";

    beforeCommand(fnName, _api.glTextureParameterfv);
    _api.glTextureParameterfv(texture.ID, toScalar(target), toScalar(pname),
                              params);
    afterCommand(fnName);
}

// Calls glTextureParameteriEXT().
void EXTDirectStateAccessAPI::textureParameterI(TextureName texture,
                                                TextureTarget target,
                                                TextureParameterName pname,
                                                GLint param) const
{
    static const char *fnName = "glTextureParameteriEXT";

    beforeCommand(fnName, _api.glTextureParameteri);
    _api.glTextureParameteri(texture.ID, toScalar(target), toScalar(pname),
                             param);
    afterCommand(fnName);
}

// Calls glTextureParameterivEXT().
void EXTDirectStateAccessAPI::textureParameterIV(TextureName texture,
                                                 TextureTarget target,
                                                 TextureParameterName pname,
                                                 const GLint *params) const
{
    static const char *fnName = "glTextureParameterivEXT";

    beforeCommand(fnName, _api.glTextureParameteriv);
    _api.glTextureParameteriv(texture.ID, toScalar(target), toScalar(pname),
                              params);
    afterCommand(fnName);
}

// Calls glTextureRenderbufferEXT().
void EXTDirectStateAccessAPI::textureRenderbuffer(TextureName texture,
                                                  TextureTarget target,
                                                  RenderbufferName renderbuffer) const
{
    static const char *fnName = "glTextureRenderbufferEXT";

    beforeCommand(fnName, _api.glTextureRenderbuffer);
    _api.glTextureRenderbuffer(texture.ID, toScalar(target), renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glTextureStorage1DEXT().
void EXTDirectStateAccessAPI::textureStorage1D(TextureName texture,
                                               GLenum target, GLsizei levels,
                                               SizedInternalFormat internalformat,
                                               GLsizei width) const
{
    static const char *fnName = "glTextureStorage1DEXT";

    beforeCommand(fnName, _api.glTextureStorage1D);
    _api.glTextureStorage1D(texture.ID, target, levels, toScalar(internalformat),
                            width);
    afterCommand(fnName);
}

// Calls glTextureStorage2DEXT().
void EXTDirectStateAccessAPI::textureStorage2D(TextureName texture,
                                               GLenum target, GLsizei levels,
                                               SizedInternalFormat internalformat,
                                               GLsizei width, GLsizei height) const
{
    static const char *fnName = "glTextureStorage2DEXT";

    beforeCommand(fnName, _api.glTextureStorage2D);
    _api.glTextureStorage2D(texture.ID, target, levels, toScalar(internalformat),
                            width, height);
    afterCommand(fnName);
}

// Calls glTextureStorage2DMultisampleEXT().
void EXTDirectStateAccessAPI::textureStorage2DMultisample(TextureName texture,
                                                          TextureTarget target,
                                                          GLsizei samples,
                                                          SizedInternalFormat internalformat,
                                                          GLsizei width,
                                                          GLsizei height,
                                                          Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTextureStorage2DMultisampleEXT";

    beforeCommand(fnName, _api.glTextureStorage2DMultisample);
    _api.glTextureStorage2DMultisample(texture.ID, toScalar(target), samples,
                                       toScalar(internalformat), width, height,
                                       toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTextureStorage3DEXT().
void EXTDirectStateAccessAPI::textureStorage3D(TextureName texture,
                                               GLenum target, GLsizei levels,
                                               SizedInternalFormat internalformat,
                                               GLsizei width, GLsizei height,
                                               GLsizei depth) const
{
    static const char *fnName = "glTextureStorage3DEXT";

    beforeCommand(fnName, _api.glTextureStorage3D);
    _api.glTextureStorage3D(texture.ID, target, levels, toScalar(internalformat),
                            width, height, depth);
    afterCommand(fnName);
}

// Calls glTextureStorage3DMultisampleEXT().
void EXTDirectStateAccessAPI::textureStorage3DMultisample(TextureName texture,
                                                          GLenum target,
                                                          GLsizei samples,
                                                          SizedInternalFormat internalformat,
                                                          GLsizei width,
                                                          GLsizei height,
                                                          GLsizei depth,
                                                          Boolean fixedsamplelocations) const
{
    static const char *fnName = "glTextureStorage3DMultisampleEXT";

    beforeCommand(fnName, _api.glTextureStorage3DMultisample);
    _api.glTextureStorage3DMultisample(texture.ID, target, samples,
                                       toScalar(internalformat), width, height,
                                       depth, toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

// Calls glTextureSubImage1DEXT().
void EXTDirectStateAccessAPI::textureSubImage1D(TextureName texture,
                                                TextureTarget target,
                                                GLint level, GLint xoffset,
                                                GLsizei width,
                                                PixelFormat format,
                                                PixelType type,
                                                const void *pixels) const
{
    static const char *fnName = "glTextureSubImage1DEXT";

    beforeCommand(fnName, _api.glTextureSubImage1D);
    _api.glTextureSubImage1D(texture.ID, toScalar(target), level, xoffset, width,
                             toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureSubImage2DEXT().
void EXTDirectStateAccessAPI::textureSubImage2D(TextureName texture,
                                                TextureTarget target,
                                                GLint level, GLint xoffset,
                                                GLint yoffset, GLsizei width,
                                                GLsizei height,
                                                PixelFormat format,
                                                PixelType type,
                                                const void *pixels) const
{
    static const char *fnName = "glTextureSubImage2DEXT";

    beforeCommand(fnName, _api.glTextureSubImage2D);
    _api.glTextureSubImage2D(texture.ID, toScalar(target), level, xoffset,
                             yoffset, width, height, toScalar(format),
                             toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTextureSubImage3DEXT().
void EXTDirectStateAccessAPI::textureSubImage3D(TextureName texture,
                                                TextureTarget target,
                                                GLint level, GLint xoffset,
                                                GLint yoffset, GLint zoffset,
                                                GLsizei width, GLsizei height,
                                                GLsizei depth,
                                                PixelFormat format,
                                                PixelType type,
                                                const void *pixels) const
{
    static const char *fnName = "glTextureSubImage3DEXT";

    beforeCommand(fnName, _api.glTextureSubImage3D);
    _api.glTextureSubImage3D(texture.ID, toScalar(target), level, xoffset,
                             yoffset, zoffset, width, height, depth,
                             toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glUnmapNamedBufferEXT().
Boolean EXTDirectStateAccessAPI::unmapNamedBuffer(BufferName buffer) const
{
    static const char *fnName = "glUnmapNamedBufferEXT";

    beforeCommand(fnName, _api.glUnmapNamedBuffer);
    GLboolean result = _api.glUnmapNamedBuffer(buffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glVertexArrayBindVertexBufferEXT().
void EXTDirectStateAccessAPI::vertexArrayBindVertexBuffer(VertexArrayName vaobj,
                                                          GLuint bindingindex,
                                                          BufferName buffer,
                                                          GLintptr offset,
                                                          GLsizei stride) const
{
    static const char *fnName = "glVertexArrayBindVertexBufferEXT";

    beforeCommand(fnName, _api.glVertexArrayBindVertexBuffer);
    _api.glVertexArrayBindVertexBuffer(vaobj.ID, bindingindex, buffer.ID, offset,
                                       stride);
    afterCommand(fnName);
}

// Calls glVertexArrayColorOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayColorOffset(VertexArrayName vaobj,
                                                     BufferName buffer,
                                                     GLint size,
                                                     ColorPointerType type,
                                                     GLsizei stride,
                                                     GLintptr offset) const
{
    static const char *fnName = "glVertexArrayColorOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayColorOffset);
    _api.glVertexArrayColorOffset(vaobj.ID, buffer.ID, size, toScalar(type),
                                  stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayEdgeFlagOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayEdgeFlagOffset(VertexArrayName vaobj,
                                                        BufferName buffer,
                                                        GLsizei stride,
                                                        GLintptr offset) const
{
    static const char *fnName = "glVertexArrayEdgeFlagOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayEdgeFlagOffset);
    _api.glVertexArrayEdgeFlagOffset(vaobj.ID, buffer.ID, stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayFogCoordOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayFogCoordOffset(VertexArrayName vaobj,
                                                        BufferName buffer,
                                                        FogCoordinatePointerType type,
                                                        GLsizei stride,
                                                        GLintptr offset) const
{
    static const char *fnName = "glVertexArrayFogCoordOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayFogCoordOffset);
    _api.glVertexArrayFogCoordOffset(vaobj.ID, buffer.ID, toScalar(type), stride,
                                     offset);
    afterCommand(fnName);
}

// Calls glVertexArrayIndexOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayIndexOffset(VertexArrayName vaobj,
                                                     BufferName buffer,
                                                     IndexPointerType type,
                                                     GLsizei stride,
                                                     GLintptr offset) const
{
    static const char *fnName = "glVertexArrayIndexOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayIndexOffset);
    _api.glVertexArrayIndexOffset(vaobj.ID, buffer.ID, toScalar(type), stride,
                                  offset);
    afterCommand(fnName);
}

// Calls glVertexArrayMultiTexCoordOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayMultiTexCoordOffset(VertexArrayName vaobj,
                                                             BufferName buffer,
                                                             GLenum texunit,
                                                             GLint size,
                                                             TexCoordPointerType type,
                                                             GLsizei stride,
                                                             GLintptr offset) const
{
    static const char *fnName = "glVertexArrayMultiTexCoordOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayMultiTexCoordOffset);
    _api.glVertexArrayMultiTexCoordOffset(vaobj.ID, buffer.ID, texunit, size,
                                          toScalar(type), stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayNormalOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayNormalOffset(VertexArrayName vaobj,
                                                      BufferName buffer,
                                                      NormalPointerType type,
                                                      GLsizei stride,
                                                      GLintptr offset) const
{
    static const char *fnName = "glVertexArrayNormalOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayNormalOffset);
    _api.glVertexArrayNormalOffset(vaobj.ID, buffer.ID, toScalar(type), stride,
                                   offset);
    afterCommand(fnName);
}

// Calls glVertexArraySecondaryColorOffsetEXT().
void EXTDirectStateAccessAPI::vertexArraySecondaryColorOffset(VertexArrayName vaobj,
                                                              BufferName buffer,
                                                              GLint size,
                                                              ColorPointerType type,
                                                              GLsizei stride,
                                                              GLintptr offset) const
{
    static const char *fnName = "glVertexArraySecondaryColorOffsetEXT";

    beforeCommand(fnName, _api.glVertexArraySecondaryColorOffset);
    _api.glVertexArraySecondaryColorOffset(vaobj.ID, buffer.ID, size,
                                           toScalar(type), stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayTexCoordOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayTexCoordOffset(VertexArrayName vaobj,
                                                        BufferName buffer,
                                                        GLint size,
                                                        TexCoordPointerType type,
                                                        GLsizei stride,
                                                        GLintptr offset) const
{
    static const char *fnName = "glVertexArrayTexCoordOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayTexCoordOffset);
    _api.glVertexArrayTexCoordOffset(vaobj.ID, buffer.ID, size, toScalar(type),
                                     stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribBindingEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribBinding(VertexArrayName vaobj,
                                                             GLuint attribindex,
                                                             GLuint bindingindex) const
{
    static const char *fnName = "glVertexArrayVertexAttribBindingEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribBinding);
    _api.glVertexArrayVertexAttribBinding(vaobj.ID, attribindex, bindingindex);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribDivisorEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribDivisor(VertexArrayName vaobj,
                                                             GLuint index,
                                                             GLuint divisor) const
{
    static const char *fnName = "glVertexArrayVertexAttribDivisorEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribDivisor);
    _api.glVertexArrayVertexAttribDivisor(vaobj.ID, index, divisor);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribFormatEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribFormat(VertexArrayName vaobj,
                                                            GLuint attribindex,
                                                            GLint size,
                                                            VertexAttribType type,
                                                            Boolean normalized,
                                                            GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayVertexAttribFormatEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribFormat);
    _api.glVertexArrayVertexAttribFormat(vaobj.ID, attribindex, size,
                                         toScalar(type), toScalar(normalized),
                                         relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribIFormatEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribIFormat(VertexArrayName vaobj,
                                                             GLuint attribindex,
                                                             GLint size,
                                                             VertexAttribIType type,
                                                             GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayVertexAttribIFormatEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribIFormat);
    _api.glVertexArrayVertexAttribIFormat(vaobj.ID, attribindex, size,
                                          toScalar(type), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribIOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribIOffset(VertexArrayName vaobj,
                                                             BufferName buffer,
                                                             GLuint index,
                                                             GLint size,
                                                             VertexAttribType type,
                                                             GLsizei stride,
                                                             GLintptr offset) const
{
    static const char *fnName = "glVertexArrayVertexAttribIOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribIOffset);
    _api.glVertexArrayVertexAttribIOffset(vaobj.ID, buffer.ID, index, size,
                                          toScalar(type), stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribLFormatEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribLFormat(VertexArrayName vaobj,
                                                             GLuint attribindex,
                                                             GLint size,
                                                             VertexAttribLType type,
                                                             GLuint relativeoffset) const
{
    static const char *fnName = "glVertexArrayVertexAttribLFormatEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribLFormat);
    _api.glVertexArrayVertexAttribLFormat(vaobj.ID, attribindex, size,
                                          toScalar(type), relativeoffset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribLOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribLOffset(VertexArrayName vaobj,
                                                             BufferName buffer,
                                                             GLuint index,
                                                             GLint size,
                                                             VertexAttribLType type,
                                                             GLsizei stride,
                                                             GLintptr offset) const
{
    static const char *fnName = "glVertexArrayVertexAttribLOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribLOffset);
    _api.glVertexArrayVertexAttribLOffset(vaobj.ID, buffer.ID, index, size,
                                          toScalar(type), stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexAttribOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexAttribOffset(VertexArrayName vaobj,
                                                            BufferName buffer,
                                                            GLuint index,
                                                            GLint size,
                                                            VertexAttribPointerType type,
                                                            Boolean normalized,
                                                            GLsizei stride,
                                                            GLintptr offset) const
{
    static const char *fnName = "glVertexArrayVertexAttribOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexAttribOffset);
    _api.glVertexArrayVertexAttribOffset(vaobj.ID, buffer.ID, index, size,
                                         toScalar(type), toScalar(normalized),
                                         stride, offset);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexBindingDivisorEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexBindingDivisor(VertexArrayName vaobj,
                                                              GLuint bindingindex,
                                                              GLuint divisor) const
{
    static const char *fnName = "glVertexArrayVertexBindingDivisorEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexBindingDivisor);
    _api.glVertexArrayVertexBindingDivisor(vaobj.ID, bindingindex, divisor);
    afterCommand(fnName);
}

// Calls glVertexArrayVertexOffsetEXT().
void EXTDirectStateAccessAPI::vertexArrayVertexOffset(VertexArrayName vaobj,
                                                      BufferName buffer,
                                                      GLint size,
                                                      VertexPointerType type,
                                                      GLsizei stride,
                                                      GLintptr offset) const
{
    static const char *fnName = "glVertexArrayVertexOffsetEXT";

    beforeCommand(fnName, _api.glVertexArrayVertexOffset);
    _api.glVertexArrayVertexOffset(vaobj.ID, buffer.ID, size, toScalar(type),
                                   stride, offset);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawBUFFERS2API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_draw_buffers2 extension.
EXTDrawBUFFERS2API::EXTDrawBUFFERS2API() :
    BaseExtension("GL_EXT_draw_buffers2")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDrawBUFFERS2 &EXTDrawBUFFERS2API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_draw_buffers2 entry points.
void EXTDrawBUFFERS2API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorMaskIndexedEXT().
void EXTDrawBUFFERS2API::colorMaskIndexed(GLuint index, Boolean r, Boolean g,
                                          Boolean b, Boolean a) const
{
    static const char *fnName = "glColorMaskIndexedEXT";

    beforeCommand(fnName, _api.glColorMaskIndexed);
    _api.glColorMaskIndexed(index, toScalar(r), toScalar(g), toScalar(b),
                            toScalar(a));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawInstancedAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_draw_instanced extension.
EXTDrawInstancedAPI::EXTDrawInstancedAPI() :
    BaseExtension("GL_EXT_draw_instanced")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDrawInstanced &EXTDrawInstancedAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_draw_instanced entry points.
void EXTDrawInstancedAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawArraysInstancedEXT().
void EXTDrawInstancedAPI::drawArraysInstanced(PrimitiveType mode, GLint start,
                                              GLsizei count, GLsizei primcount) const
{
    static const char *fnName = "glDrawArraysInstancedEXT";

    beforeCommand(fnName, _api.glDrawArraysInstanced);
    _api.glDrawArraysInstanced(toScalar(mode), start, count, primcount);
    afterCommand(fnName);
}

// Calls glDrawElementsInstancedEXT().
void EXTDrawInstancedAPI::drawElementsInstanced(PrimitiveType mode,
                                                GLsizei count,
                                                DrawElementsType type,
                                                const void *indices,
                                                GLsizei primcount) const
{
    static const char *fnName = "glDrawElementsInstancedEXT";

    beforeCommand(fnName, _api.glDrawElementsInstanced);
    _api.glDrawElementsInstanced(toScalar(mode), count, toScalar(type), indices,
                                 primcount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTDrawRangeElementsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_draw_range_elements extension.
EXTDrawRangeElementsAPI::EXTDrawRangeElementsAPI() :
    BaseExtension("GL_EXT_draw_range_elements")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDrawRangeElements &EXTDrawRangeElementsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_draw_range_elements entry points.
void EXTDrawRangeElementsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawRangeElementsEXT().
void EXTDrawRangeElementsAPI::drawRangeElements(PrimitiveType mode, GLuint start,
                                                GLuint end, GLsizei count,
                                                DrawElementsType type,
                                                const void *indices) const
{
    static const char *fnName = "glDrawRangeElementsEXT";

    beforeCommand(fnName, _api.glDrawRangeElements);
    _api.glDrawRangeElements(toScalar(mode), start, end, count, toScalar(type),
                             indices);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTExternalBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_external_buffer extension.
EXTExternalBufferAPI::EXTExternalBufferAPI() :
    BaseExtension("GL_EXT_external_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const EXTExternalBuffer &EXTExternalBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_external_buffer entry points.
void EXTExternalBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferStorageExternalEXT().
void EXTExternalBufferAPI::bufferStorageExternal(GLenum target, GLintptr offset,
                                                 GLsizeiptr size,
                                                 GLeglClientBufferEXT clientBuffer,
                                                 GLbitfield  /* BufferStorageMask */ flags) const
{
    static const char *fnName = "glBufferStorageExternalEXT";

    beforeCommand(fnName, _api.glBufferStorageExternal);
    _api.glBufferStorageExternal(target, offset, size, clientBuffer, flags);
    afterCommand(fnName);
}

// Calls glNamedBufferStorageExternalEXT().
void EXTExternalBufferAPI::namedBufferStorageExternal(BufferName buffer,
                                                      GLintptr offset,
                                                      GLsizeiptr size,
                                                      GLeglClientBufferEXT clientBuffer,
                                                      GLbitfield  /* BufferStorageMask */ flags) const
{
    static const char *fnName = "glNamedBufferStorageExternalEXT";

    beforeCommand(fnName, _api.glNamedBufferStorageExternal);
    _api.glNamedBufferStorageExternal(buffer.ID, offset, size, clientBuffer,
                                      flags);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTFogCoordAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_fog_coord extension.
EXTFogCoordAPI::EXTFogCoordAPI() :
    BaseExtension("GL_EXT_fog_coord")
{
}

// Grant read-only access to the underlying function pointers.
const EXTFogCoord &EXTFogCoordAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_fog_coord entry points.
void EXTFogCoordAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFogCoordPointerEXT().
void EXTFogCoordAPI::fogCoordPointer(FogPointerTypeEXT type, GLsizei stride,
                                     const void *pointer) const
{
    static const char *fnName = "glFogCoordPointerEXT";

    beforeCommand(fnName, _api.glFogCoordPointer);
    _api.glFogCoordPointer(toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glFogCoorddEXT().
void EXTFogCoordAPI::fogCoordD(GLdouble coord) const
{
    static const char *fnName = "glFogCoorddEXT";

    beforeCommand(fnName, _api.glFogCoordd);
    _api.glFogCoordd(coord);
    afterCommand(fnName);
}

// Calls glFogCoorddvEXT().
void EXTFogCoordAPI::fogCoordDV(const GLdouble *coord) const
{
    static const char *fnName = "glFogCoorddvEXT";

    beforeCommand(fnName, _api.glFogCoorddv);
    _api.glFogCoorddv(coord);
    afterCommand(fnName);
}

// Calls glFogCoordfEXT().
void EXTFogCoordAPI::fogCoordF(GLfloat coord) const
{
    static const char *fnName = "glFogCoordfEXT";

    beforeCommand(fnName, _api.glFogCoordf);
    _api.glFogCoordf(coord);
    afterCommand(fnName);
}

// Calls glFogCoordfvEXT().
void EXTFogCoordAPI::fogCoordFV(const GLfloat *coord) const
{
    static const char *fnName = "glFogCoordfvEXT";

    beforeCommand(fnName, _api.glFogCoordfv);
    _api.glFogCoordfv(coord);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferBlitAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_framebuffer_blit extension.
EXTFramebufferBlitAPI::EXTFramebufferBlitAPI() :
    BaseExtension("GL_EXT_framebuffer_blit")
{
}

// Grant read-only access to the underlying function pointers.
const EXTFramebufferBlit &EXTFramebufferBlitAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_framebuffer_blit entry points.
void EXTFramebufferBlitAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBlitFramebufferEXT().
void EXTFramebufferBlitAPI::blitFramebuffer(GLint srcX0, GLint srcY0,
                                            GLint srcX1, GLint srcY1,
                                            GLint dstX0, GLint dstY0,
                                            GLint dstX1, GLint dstY1,
                                            GLbitfield  /* ClearBufferMask */ mask,
                                            BlitFramebufferFilter filter) const
{
    static const char *fnName = "glBlitFramebufferEXT";

    beforeCommand(fnName, _api.glBlitFramebuffer);
    _api.glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1,
                           dstY1, mask, toScalar(filter));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_framebuffer_multisample extension.
EXTFramebufferMultisampleAPI::EXTFramebufferMultisampleAPI() :
    BaseExtension("GL_EXT_framebuffer_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const EXTFramebufferMultisample &EXTFramebufferMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_framebuffer_multisample entry points.
void EXTFramebufferMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glRenderbufferStorageMultisampleEXT().
void EXTFramebufferMultisampleAPI::renderbufferStorageMultisample(RenderbufferTarget target,
                                                                  GLsizei samples,
                                                                  InternalFormat internalformat,
                                                                  GLsizei width,
                                                                  GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorageMultisampleEXT";

    beforeCommand(fnName, _api.glRenderbufferStorageMultisample);
    _api.glRenderbufferStorageMultisample(toScalar(target), samples,
                                          toScalar(internalformat), width,
                                          height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTFramebufferObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_framebuffer_object extension.
EXTFramebufferObjectAPI::EXTFramebufferObjectAPI() :
    BaseExtension("GL_EXT_framebuffer_object")
{
}

// Grant read-only access to the underlying function pointers.
const EXTFramebufferObject &EXTFramebufferObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_framebuffer_object entry points.
void EXTFramebufferObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindFramebufferEXT().
void EXTFramebufferObjectAPI::bindFramebuffer(FramebufferTarget target,
                                              FramebufferName framebuffer) const
{
    static const char *fnName = "glBindFramebufferEXT";

    beforeCommand(fnName, _api.glBindFramebuffer);
    _api.glBindFramebuffer(toScalar(target), framebuffer.ID);
    afterCommand(fnName);
}

// Calls glBindRenderbufferEXT().
void EXTFramebufferObjectAPI::bindRenderbuffer(RenderbufferTarget target,
                                               RenderbufferName renderbuffer) const
{
    static const char *fnName = "glBindRenderbufferEXT";

    beforeCommand(fnName, _api.glBindRenderbuffer);
    _api.glBindRenderbuffer(toScalar(target), renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glCheckFramebufferStatusEXT().
FramebufferStatus EXTFramebufferObjectAPI::checkFramebufferStatus(FramebufferTarget target) const
{
    static const char *fnName = "glCheckFramebufferStatusEXT";

    beforeCommand(fnName, _api.glCheckFramebufferStatus);
    GLenum result = _api.glCheckFramebufferStatus(toScalar(target));
    afterCommand(fnName);

    return static_cast<FramebufferStatus>(result);
}

// Calls glDeleteFramebuffersEXT().
void EXTFramebufferObjectAPI::deleteFramebuffers(GLsizei n,
                                                 const FramebufferName *framebuffers) const
{
    static const char *fnName = "glDeleteFramebuffersEXT";

    beforeCommand(fnName, _api.glDeleteFramebuffers);
    _api.glDeleteFramebuffers(n, reinterpret_cast<const GLuint *>(framebuffers));
    afterCommand(fnName);
}

// Calls glDeleteRenderbuffersEXT().
void EXTFramebufferObjectAPI::deleteRenderbuffers(GLsizei n,
                                                  const RenderbufferName *renderbuffers) const
{
    static const char *fnName = "glDeleteRenderbuffersEXT";

    beforeCommand(fnName, _api.glDeleteRenderbuffers);
    _api.glDeleteRenderbuffers(n,
                               reinterpret_cast<const GLuint *>(renderbuffers));
    afterCommand(fnName);
}

// Calls glFramebufferRenderbufferEXT().
void EXTFramebufferObjectAPI::framebufferRenderbuffer(FramebufferTarget target,
                                                      FramebufferAttachment attachment,
                                                      RenderbufferTarget renderbuffertarget,
                                                      RenderbufferName renderbuffer) const
{
    static const char *fnName = "glFramebufferRenderbufferEXT";

    beforeCommand(fnName, _api.glFramebufferRenderbuffer);
    _api.glFramebufferRenderbuffer(toScalar(target), toScalar(attachment),
                                   toScalar(renderbuffertarget), renderbuffer.ID);
    afterCommand(fnName);
}

// Calls glFramebufferTexture1DEXT().
void EXTFramebufferObjectAPI::framebufferTexture1D(FramebufferTarget target,
                                                   FramebufferAttachment attachment,
                                                   TextureTarget textarget,
                                                   TextureName texture,
                                                   GLint level) const
{
    static const char *fnName = "glFramebufferTexture1DEXT";

    beforeCommand(fnName, _api.glFramebufferTexture1D);
    _api.glFramebufferTexture1D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glFramebufferTexture2DEXT().
void EXTFramebufferObjectAPI::framebufferTexture2D(FramebufferTarget target,
                                                   FramebufferAttachment attachment,
                                                   TextureTarget textarget,
                                                   TextureName texture,
                                                   GLint level) const
{
    static const char *fnName = "glFramebufferTexture2DEXT";

    beforeCommand(fnName, _api.glFramebufferTexture2D);
    _api.glFramebufferTexture2D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level);
    afterCommand(fnName);
}

// Calls glFramebufferTexture3DEXT().
void EXTFramebufferObjectAPI::framebufferTexture3D(FramebufferTarget target,
                                                   FramebufferAttachment attachment,
                                                   TextureTarget textarget,
                                                   TextureName texture,
                                                   GLint level, GLint zoffset) const
{
    static const char *fnName = "glFramebufferTexture3DEXT";

    beforeCommand(fnName, _api.glFramebufferTexture3D);
    _api.glFramebufferTexture3D(toScalar(target), toScalar(attachment),
                                toScalar(textarget), texture.ID, level, zoffset);
    afterCommand(fnName);
}

// Calls glGenFramebuffersEXT().
void EXTFramebufferObjectAPI::genFramebuffers(GLsizei n,
                                              FramebufferName *framebuffers) const
{
    static const char *fnName = "glGenFramebuffersEXT";

    beforeCommand(fnName, _api.glGenFramebuffers);
    _api.glGenFramebuffers(n, reinterpret_cast<GLuint *>(framebuffers));
    afterCommand(fnName);
}

// Calls glGenRenderbuffersEXT().
void EXTFramebufferObjectAPI::genRenderbuffers(GLsizei n,
                                               RenderbufferName *renderbuffers) const
{
    static const char *fnName = "glGenRenderbuffersEXT";

    beforeCommand(fnName, _api.glGenRenderbuffers);
    _api.glGenRenderbuffers(n, reinterpret_cast<GLuint *>(renderbuffers));
    afterCommand(fnName);
}

// Calls glGenerateMipmapEXT().
void EXTFramebufferObjectAPI::generateMipmap(TextureTarget target) const
{
    static const char *fnName = "glGenerateMipmapEXT";

    beforeCommand(fnName, _api.glGenerateMipmap);
    _api.glGenerateMipmap(toScalar(target));
    afterCommand(fnName);
}

// Calls glGetFramebufferAttachmentParameterivEXT().
void EXTFramebufferObjectAPI::getFramebufferAttachmentParameterIV(FramebufferTarget target,
                                                                  FramebufferAttachment attachment,
                                                                  FramebufferAttachmentParameterName pname,
                                                                  GLint *params) const
{
    static const char *fnName = "glGetFramebufferAttachmentParameterivEXT";

    beforeCommand(fnName, _api.glGetFramebufferAttachmentParameteriv);
    _api.glGetFramebufferAttachmentParameteriv(toScalar(target),
                                               toScalar(attachment),
                                               toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetRenderbufferParameterivEXT().
void EXTFramebufferObjectAPI::getRenderbufferParameterIV(RenderbufferTarget target,
                                                         RenderbufferParameterName pname,
                                                         GLint *params) const
{
    static const char *fnName = "glGetRenderbufferParameterivEXT";

    beforeCommand(fnName, _api.glGetRenderbufferParameteriv);
    _api.glGetRenderbufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsFramebufferEXT().
Boolean EXTFramebufferObjectAPI::isFramebuffer(FramebufferName framebuffer) const
{
    static const char *fnName = "glIsFramebufferEXT";

    beforeCommand(fnName, _api.glIsFramebuffer);
    GLboolean result = _api.glIsFramebuffer(framebuffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glIsRenderbufferEXT().
Boolean EXTFramebufferObjectAPI::isRenderbuffer(RenderbufferName renderbuffer) const
{
    static const char *fnName = "glIsRenderbufferEXT";

    beforeCommand(fnName, _api.glIsRenderbuffer);
    GLboolean result = _api.glIsRenderbuffer(renderbuffer.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glRenderbufferStorageEXT().
void EXTFramebufferObjectAPI::renderbufferStorage(RenderbufferTarget target,
                                                  InternalFormat internalformat,
                                                  GLsizei width, GLsizei height) const
{
    static const char *fnName = "glRenderbufferStorageEXT";

    beforeCommand(fnName, _api.glRenderbufferStorage);
    _api.glRenderbufferStorage(toScalar(target), toScalar(internalformat), width,
                               height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTGeometrySHADER4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_geometry_shader4 extension.
EXTGeometrySHADER4API::EXTGeometrySHADER4API() :
    BaseExtension("GL_EXT_geometry_shader4")
{
}

// Grant read-only access to the underlying function pointers.
const EXTGeometrySHADER4 &EXTGeometrySHADER4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_geometry_shader4 entry points.
void EXTGeometrySHADER4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glProgramParameteriEXT().
void EXTGeometrySHADER4API::programParameterI(ProgramName program,
                                              ProgramParameterPName pname,
                                              GLint value) const
{
    static const char *fnName = "glProgramParameteriEXT";

    beforeCommand(fnName, _api.glProgramParameteri);
    _api.glProgramParameteri(program.ID, toScalar(pname), value);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTGPUProgramParametersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_gpu_program_parameters extension.
EXTGPUProgramParametersAPI::EXTGPUProgramParametersAPI() :
    BaseExtension("GL_EXT_gpu_program_parameters")
{
}

// Grant read-only access to the underlying function pointers.
const EXTGPUProgramParameters &EXTGPUProgramParametersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_gpu_program_parameters entry points.
void EXTGPUProgramParametersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glProgramEnvParameters4fvEXT().
void EXTGPUProgramParametersAPI::programEnvParameters4FV(ProgramTarget target,
                                                         GLuint index,
                                                         GLsizei count,
                                                         const GLfloat *params) const
{
    static const char *fnName = "glProgramEnvParameters4fvEXT";

    beforeCommand(fnName, _api.glProgramEnvParameters4fv);
    _api.glProgramEnvParameters4fv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

// Calls glProgramLocalParameters4fvEXT().
void EXTGPUProgramParametersAPI::programLocalParameters4FV(ProgramTarget target,
                                                           GLuint index,
                                                           GLsizei count,
                                                           const GLfloat *params) const
{
    static const char *fnName = "glProgramLocalParameters4fvEXT";

    beforeCommand(fnName, _api.glProgramLocalParameters4fv);
    _api.glProgramLocalParameters4fv(toScalar(target), index, count, params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTGPUSHADER4API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_gpu_shader4 extension.
EXTGPUSHADER4API::EXTGPUSHADER4API() :
    BaseExtension("GL_EXT_gpu_shader4")
{
}

// Grant read-only access to the underlying function pointers.
const EXTGPUSHADER4 &EXTGPUSHADER4API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_gpu_shader4 entry points.
void EXTGPUSHADER4API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindFragDataLocationEXT().
void EXTGPUSHADER4API::bindFragDataLocation(ProgramName program, GLuint color,
                                            const GLchar *name) const
{
    static const char *fnName = "glBindFragDataLocationEXT";

    beforeCommand(fnName, _api.glBindFragDataLocation);
    _api.glBindFragDataLocation(program.ID, color, name);
    afterCommand(fnName);
}

// Calls glGetFragDataLocationEXT().
GLint EXTGPUSHADER4API::getFragDataLocation(ProgramName program,
                                            const GLchar *name) const
{
    static const char *fnName = "glGetFragDataLocationEXT";

    beforeCommand(fnName, _api.glGetFragDataLocation);
    GLint result = _api.glGetFragDataLocation(program.ID, name);
    afterCommand(fnName);

    return result;
}

// Calls glGetUniformuivEXT().
void EXTGPUSHADER4API::getUniformUIV(ProgramName program, GLint location,
                                     GLuint *params) const
{
    static const char *fnName = "glGetUniformuivEXT";

    beforeCommand(fnName, _api.glGetUniformuiv);
    _api.glGetUniformuiv(program.ID, location, params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribIivEXT().
void EXTGPUSHADER4API::getVertexAttribIIV(GLuint index, VertexAttribEnum pname,
                                          GLint *params) const
{
    static const char *fnName = "glGetVertexAttribIivEXT";

    beforeCommand(fnName, _api.glGetVertexAttribIiv);
    _api.glGetVertexAttribIiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetVertexAttribIuivEXT().
void EXTGPUSHADER4API::getVertexAttribIUIV(GLuint index, VertexAttribEnum pname,
                                           GLuint *params) const
{
    static const char *fnName = "glGetVertexAttribIuivEXT";

    beforeCommand(fnName, _api.glGetVertexAttribIuiv);
    _api.glGetVertexAttribIuiv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glUniform1uiEXT().
void EXTGPUSHADER4API::uniform1UI(GLint location, GLuint v0) const
{
    static const char *fnName = "glUniform1uiEXT";

    beforeCommand(fnName, _api.glUniform1ui);
    _api.glUniform1ui(location, v0);
    afterCommand(fnName);
}

// Calls glUniform1uivEXT().
void EXTGPUSHADER4API::uniform1UIV(GLint location, GLsizei count,
                                   const GLuint *value) const
{
    static const char *fnName = "glUniform1uivEXT";

    beforeCommand(fnName, _api.glUniform1uiv);
    _api.glUniform1uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform2uiEXT().
void EXTGPUSHADER4API::uniform2UI(GLint location, GLuint v0, GLuint v1) const
{
    static const char *fnName = "glUniform2uiEXT";

    beforeCommand(fnName, _api.glUniform2ui);
    _api.glUniform2ui(location, v0, v1);
    afterCommand(fnName);
}

// Calls glUniform2uivEXT().
void EXTGPUSHADER4API::uniform2UIV(GLint location, GLsizei count,
                                   const GLuint *value) const
{
    static const char *fnName = "glUniform2uivEXT";

    beforeCommand(fnName, _api.glUniform2uiv);
    _api.glUniform2uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform3uiEXT().
void EXTGPUSHADER4API::uniform3UI(GLint location, GLuint v0, GLuint v1,
                                  GLuint v2) const
{
    static const char *fnName = "glUniform3uiEXT";

    beforeCommand(fnName, _api.glUniform3ui);
    _api.glUniform3ui(location, v0, v1, v2);
    afterCommand(fnName);
}

// Calls glUniform3uivEXT().
void EXTGPUSHADER4API::uniform3UIV(GLint location, GLsizei count,
                                   const GLuint *value) const
{
    static const char *fnName = "glUniform3uivEXT";

    beforeCommand(fnName, _api.glUniform3uiv);
    _api.glUniform3uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glUniform4uiEXT().
void EXTGPUSHADER4API::uniform4UI(GLint location, GLuint v0, GLuint v1,
                                  GLuint v2, GLuint v3) const
{
    static const char *fnName = "glUniform4uiEXT";

    beforeCommand(fnName, _api.glUniform4ui);
    _api.glUniform4ui(location, v0, v1, v2, v3);
    afterCommand(fnName);
}

// Calls glUniform4uivEXT().
void EXTGPUSHADER4API::uniform4UIV(GLint location, GLsizei count,
                                   const GLuint *value) const
{
    static const char *fnName = "glUniform4uivEXT";

    beforeCommand(fnName, _api.glUniform4uiv);
    _api.glUniform4uiv(location, count, value);
    afterCommand(fnName);
}

// Calls glVertexAttribI1iEXT().
void EXTGPUSHADER4API::vertexAttribI1I(GLuint index, GLint x) const
{
    static const char *fnName = "glVertexAttribI1iEXT";

    beforeCommand(fnName, _api.glVertexAttribI1i);
    _api.glVertexAttribI1i(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribI1ivEXT().
void EXTGPUSHADER4API::vertexAttribI1IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI1ivEXT";

    beforeCommand(fnName, _api.glVertexAttribI1iv);
    _api.glVertexAttribI1iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI1uiEXT().
void EXTGPUSHADER4API::vertexAttribI1UI(GLuint index, GLuint x) const
{
    static const char *fnName = "glVertexAttribI1uiEXT";

    beforeCommand(fnName, _api.glVertexAttribI1ui);
    _api.glVertexAttribI1ui(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribI1uivEXT().
void EXTGPUSHADER4API::vertexAttribI1UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI1uivEXT";

    beforeCommand(fnName, _api.glVertexAttribI1uiv);
    _api.glVertexAttribI1uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI2iEXT().
void EXTGPUSHADER4API::vertexAttribI2I(GLuint index, GLint x, GLint y) const
{
    static const char *fnName = "glVertexAttribI2iEXT";

    beforeCommand(fnName, _api.glVertexAttribI2i);
    _api.glVertexAttribI2i(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribI2ivEXT().
void EXTGPUSHADER4API::vertexAttribI2IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI2ivEXT";

    beforeCommand(fnName, _api.glVertexAttribI2iv);
    _api.glVertexAttribI2iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI2uiEXT().
void EXTGPUSHADER4API::vertexAttribI2UI(GLuint index, GLuint x, GLuint y) const
{
    static const char *fnName = "glVertexAttribI2uiEXT";

    beforeCommand(fnName, _api.glVertexAttribI2ui);
    _api.glVertexAttribI2ui(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribI2uivEXT().
void EXTGPUSHADER4API::vertexAttribI2UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI2uivEXT";

    beforeCommand(fnName, _api.glVertexAttribI2uiv);
    _api.glVertexAttribI2uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI3iEXT().
void EXTGPUSHADER4API::vertexAttribI3I(GLuint index, GLint x, GLint y, GLint z) const
{
    static const char *fnName = "glVertexAttribI3iEXT";

    beforeCommand(fnName, _api.glVertexAttribI3i);
    _api.glVertexAttribI3i(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribI3ivEXT().
void EXTGPUSHADER4API::vertexAttribI3IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI3ivEXT";

    beforeCommand(fnName, _api.glVertexAttribI3iv);
    _api.glVertexAttribI3iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI3uiEXT().
void EXTGPUSHADER4API::vertexAttribI3UI(GLuint index, GLuint x, GLuint y,
                                        GLuint z) const
{
    static const char *fnName = "glVertexAttribI3uiEXT";

    beforeCommand(fnName, _api.glVertexAttribI3ui);
    _api.glVertexAttribI3ui(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribI3uivEXT().
void EXTGPUSHADER4API::vertexAttribI3UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI3uivEXT";

    beforeCommand(fnName, _api.glVertexAttribI3uiv);
    _api.glVertexAttribI3uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4bvEXT().
void EXTGPUSHADER4API::vertexAttribI4BV(GLuint index, const GLbyte *v) const
{
    static const char *fnName = "glVertexAttribI4bvEXT";

    beforeCommand(fnName, _api.glVertexAttribI4bv);
    _api.glVertexAttribI4bv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4iEXT().
void EXTGPUSHADER4API::vertexAttribI4I(GLuint index, GLint x, GLint y, GLint z,
                                       GLint w) const
{
    static const char *fnName = "glVertexAttribI4iEXT";

    beforeCommand(fnName, _api.glVertexAttribI4i);
    _api.glVertexAttribI4i(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribI4ivEXT().
void EXTGPUSHADER4API::vertexAttribI4IV(GLuint index, const GLint *v) const
{
    static const char *fnName = "glVertexAttribI4ivEXT";

    beforeCommand(fnName, _api.glVertexAttribI4iv);
    _api.glVertexAttribI4iv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4svEXT().
void EXTGPUSHADER4API::vertexAttribI4SV(GLuint index, const GLshort *v) const
{
    static const char *fnName = "glVertexAttribI4svEXT";

    beforeCommand(fnName, _api.glVertexAttribI4sv);
    _api.glVertexAttribI4sv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4ubvEXT().
void EXTGPUSHADER4API::vertexAttribI4UBV(GLuint index, const GLubyte *v) const
{
    static const char *fnName = "glVertexAttribI4ubvEXT";

    beforeCommand(fnName, _api.glVertexAttribI4ubv);
    _api.glVertexAttribI4ubv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4uiEXT().
void EXTGPUSHADER4API::vertexAttribI4UI(GLuint index, GLuint x, GLuint y,
                                        GLuint z, GLuint w) const
{
    static const char *fnName = "glVertexAttribI4uiEXT";

    beforeCommand(fnName, _api.glVertexAttribI4ui);
    _api.glVertexAttribI4ui(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribI4uivEXT().
void EXTGPUSHADER4API::vertexAttribI4UIV(GLuint index, const GLuint *v) const
{
    static const char *fnName = "glVertexAttribI4uivEXT";

    beforeCommand(fnName, _api.glVertexAttribI4uiv);
    _api.glVertexAttribI4uiv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribI4usvEXT().
void EXTGPUSHADER4API::vertexAttribI4USV(GLuint index, const GLushort *v) const
{
    static const char *fnName = "glVertexAttribI4usvEXT";

    beforeCommand(fnName, _api.glVertexAttribI4usv);
    _api.glVertexAttribI4usv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribIPointerEXT().
void EXTGPUSHADER4API::vertexAttribIPointer(GLuint index, GLint size,
                                            VertexAttribIType type,
                                            GLsizei stride, const void *pointer) const
{
    static const char *fnName = "glVertexAttribIPointerEXT";

    beforeCommand(fnName, _api.glVertexAttribIPointer);
    _api.glVertexAttribIPointer(index, size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTHistogramAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_histogram extension.
EXTHistogramAPI::EXTHistogramAPI() :
    BaseExtension("GL_EXT_histogram")
{
}

// Grant read-only access to the underlying function pointers.
const EXTHistogram &EXTHistogramAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_histogram entry points.
void EXTHistogramAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetHistogramEXT().
void EXTHistogramAPI::getHistogram(HistogramTargetEXT target, Boolean reset,
                                   PixelFormat format, PixelType type,
                                   void *values) const
{
    static const char *fnName = "glGetHistogramEXT";

    beforeCommand(fnName, _api.glGetHistogram);
    _api.glGetHistogram(toScalar(target), toScalar(reset), toScalar(format),
                        toScalar(type), values);
    afterCommand(fnName);
}

// Calls glGetHistogramParameterfvEXT().
void EXTHistogramAPI::getHistogramParameterFV(HistogramTargetEXT target,
                                              GetHistogramParameterPNameEXT pname,
                                              GLfloat *params) const
{
    static const char *fnName = "glGetHistogramParameterfvEXT";

    beforeCommand(fnName, _api.glGetHistogramParameterfv);
    _api.glGetHistogramParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetHistogramParameterivEXT().
void EXTHistogramAPI::getHistogramParameterIV(HistogramTargetEXT target,
                                              GetHistogramParameterPNameEXT pname,
                                              GLint *params) const
{
    static const char *fnName = "glGetHistogramParameterivEXT";

    beforeCommand(fnName, _api.glGetHistogramParameteriv);
    _api.glGetHistogramParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMinmaxEXT().
void EXTHistogramAPI::getMinmax(MinmaxTargetEXT target, Boolean reset,
                                PixelFormat format, PixelType type, void *values) const
{
    static const char *fnName = "glGetMinmaxEXT";

    beforeCommand(fnName, _api.glGetMinmax);
    _api.glGetMinmax(toScalar(target), toScalar(reset), toScalar(format),
                     toScalar(type), values);
    afterCommand(fnName);
}

// Calls glGetMinmaxParameterfvEXT().
void EXTHistogramAPI::getMinmaxParameterFV(MinmaxTargetEXT target,
                                           GetMinmaxParameterPNameEXT pname,
                                           GLfloat *params) const
{
    static const char *fnName = "glGetMinmaxParameterfvEXT";

    beforeCommand(fnName, _api.glGetMinmaxParameterfv);
    _api.glGetMinmaxParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetMinmaxParameterivEXT().
void EXTHistogramAPI::getMinmaxParameterIV(MinmaxTargetEXT target,
                                           GetMinmaxParameterPNameEXT pname,
                                           GLint *params) const
{
    static const char *fnName = "glGetMinmaxParameterivEXT";

    beforeCommand(fnName, _api.glGetMinmaxParameteriv);
    _api.glGetMinmaxParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glHistogramEXT().
void EXTHistogramAPI::histogram(HistogramTargetEXT target, GLsizei width,
                                InternalFormat internalformat, Boolean sink) const
{
    static const char *fnName = "glHistogramEXT";

    beforeCommand(fnName, _api.glHistogram);
    _api.glHistogram(toScalar(target), width, toScalar(internalformat),
                     toScalar(sink));
    afterCommand(fnName);
}

// Calls glMinmaxEXT().
void EXTHistogramAPI::minmax(MinmaxTargetEXT target,
                             InternalFormat internalformat, Boolean sink) const
{
    static const char *fnName = "glMinmaxEXT";

    beforeCommand(fnName, _api.glMinmax);
    _api.glMinmax(toScalar(target), toScalar(internalformat), toScalar(sink));
    afterCommand(fnName);
}

// Calls glResetHistogramEXT().
void EXTHistogramAPI::resetHistogram(HistogramTargetEXT target) const
{
    static const char *fnName = "glResetHistogramEXT";

    beforeCommand(fnName, _api.glResetHistogram);
    _api.glResetHistogram(toScalar(target));
    afterCommand(fnName);
}

// Calls glResetMinmaxEXT().
void EXTHistogramAPI::resetMinmax(MinmaxTargetEXT target) const
{
    static const char *fnName = "glResetMinmaxEXT";

    beforeCommand(fnName, _api.glResetMinmax);
    _api.glResetMinmax(toScalar(target));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTIndexFuncAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_index_func extension.
EXTIndexFuncAPI::EXTIndexFuncAPI() :
    BaseExtension("GL_EXT_index_func")
{
}

// Grant read-only access to the underlying function pointers.
const EXTIndexFunc &EXTIndexFuncAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_index_func entry points.
void EXTIndexFuncAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glIndexFuncEXT().
void EXTIndexFuncAPI::indexFunc(IndexFunctionEXT func, GLclampf ref) const
{
    static const char *fnName = "glIndexFuncEXT";

    beforeCommand(fnName, _api.glIndexFunc);
    _api.glIndexFunc(toScalar(func), ref);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTIndexMaterialAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_index_material extension.
EXTIndexMaterialAPI::EXTIndexMaterialAPI() :
    BaseExtension("GL_EXT_index_material")
{
}

// Grant read-only access to the underlying function pointers.
const EXTIndexMaterial &EXTIndexMaterialAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_index_material entry points.
void EXTIndexMaterialAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glIndexMaterialEXT().
void EXTIndexMaterialAPI::indexMaterial(MaterialFace face, GLenum mode) const
{
    static const char *fnName = "glIndexMaterialEXT";

    beforeCommand(fnName, _api.glIndexMaterial);
    _api.glIndexMaterial(toScalar(face), mode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTLightTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_light_texture extension.
EXTLightTextureAPI::EXTLightTextureAPI() :
    BaseExtension("GL_EXT_light_texture")
{
}

// Grant read-only access to the underlying function pointers.
const EXTLightTexture &EXTLightTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_light_texture entry points.
void EXTLightTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glApplyTextureEXT().
void EXTLightTextureAPI::applyTexture(LightTextureModeEXT mode) const
{
    static const char *fnName = "glApplyTextureEXT";

    beforeCommand(fnName, _api.glApplyTexture);
    _api.glApplyTexture(toScalar(mode));
    afterCommand(fnName);
}

// Calls glTextureLightEXT().
void EXTLightTextureAPI::textureLight(LightTexturePNameEXT pname) const
{
    static const char *fnName = "glTextureLightEXT";

    beforeCommand(fnName, _api.glTextureLight);
    _api.glTextureLight(toScalar(pname));
    afterCommand(fnName);
}

// Calls glTextureMaterialEXT().
void EXTLightTextureAPI::textureMaterial(MaterialFace face, GLenum mode) const
{
    static const char *fnName = "glTextureMaterialEXT";

    beforeCommand(fnName, _api.glTextureMaterial);
    _api.glTextureMaterial(toScalar(face), mode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_memory_object extension.
EXTMemoryObjectAPI::EXTMemoryObjectAPI() :
    BaseExtension("GL_EXT_memory_object")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMemoryObject &EXTMemoryObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_memory_object entry points.
void EXTMemoryObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBufferStorageMemEXT().
void EXTMemoryObjectAPI::bufferStorageMem(BufferTargetARB target,
                                          GLsizeiptr size, GLuint memory,
                                          GLuint64 offset) const
{
    static const char *fnName = "glBufferStorageMemEXT";

    beforeCommand(fnName, _api.glBufferStorageMem);
    _api.glBufferStorageMem(toScalar(target), size, memory, offset);
    afterCommand(fnName);
}

// Calls glCreateMemoryObjectsEXT().
void EXTMemoryObjectAPI::createMemoryObjects(GLsizei n, GLuint *memoryObjects) const
{
    static const char *fnName = "glCreateMemoryObjectsEXT";

    beforeCommand(fnName, _api.glCreateMemoryObjects);
    _api.glCreateMemoryObjects(n, memoryObjects);
    afterCommand(fnName);
}

// Calls glDeleteMemoryObjectsEXT().
void EXTMemoryObjectAPI::deleteMemoryObjects(GLsizei n,
                                             const GLuint *memoryObjects) const
{
    static const char *fnName = "glDeleteMemoryObjectsEXT";

    beforeCommand(fnName, _api.glDeleteMemoryObjects);
    _api.glDeleteMemoryObjects(n, memoryObjects);
    afterCommand(fnName);
}

// Calls glGetMemoryObjectParameterivEXT().
void EXTMemoryObjectAPI::getMemoryObjectParameterIV(GLuint memoryObject,
                                                    MemoryObjectParameterName pname,
                                                    GLint *params) const
{
    static const char *fnName = "glGetMemoryObjectParameterivEXT";

    beforeCommand(fnName, _api.glGetMemoryObjectParameteriv);
    _api.glGetMemoryObjectParameteriv(memoryObject, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetUnsignedBytei_vEXT().
void EXTMemoryObjectAPI::getUnsignedByteIV(GLenum target, GLuint index,
                                           GLubyte *data) const
{
    static const char *fnName = "glGetUnsignedBytei_vEXT";

    beforeCommand(fnName, _api.glGetUnsignedBytei_v);
    _api.glGetUnsignedBytei_v(target, index, data);
    afterCommand(fnName);
}

// Calls glGetUnsignedBytevEXT().
void EXTMemoryObjectAPI::getUnsignedByteV(GetPName pname, GLubyte *data) const
{
    static const char *fnName = "glGetUnsignedBytevEXT";

    beforeCommand(fnName, _api.glGetUnsignedBytev);
    _api.glGetUnsignedBytev(toScalar(pname), data);
    afterCommand(fnName);
}

// Calls glIsMemoryObjectEXT().
Boolean EXTMemoryObjectAPI::isMemoryObject(GLuint memoryObject) const
{
    static const char *fnName = "glIsMemoryObjectEXT";

    beforeCommand(fnName, _api.glIsMemoryObject);
    GLboolean result = _api.glIsMemoryObject(memoryObject);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glMemoryObjectParameterivEXT().
void EXTMemoryObjectAPI::memoryObjectParameterIV(GLuint memoryObject,
                                                 MemoryObjectParameterName pname,
                                                 const GLint *params) const
{
    static const char *fnName = "glMemoryObjectParameterivEXT";

    beforeCommand(fnName, _api.glMemoryObjectParameteriv);
    _api.glMemoryObjectParameteriv(memoryObject, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glNamedBufferStorageMemEXT().
void EXTMemoryObjectAPI::namedBufferStorageMem(BufferName buffer,
                                               GLsizeiptr size, GLuint memory,
                                               GLuint64 offset) const
{
    static const char *fnName = "glNamedBufferStorageMemEXT";

    beforeCommand(fnName, _api.glNamedBufferStorageMem);
    _api.glNamedBufferStorageMem(buffer.ID, size, memory, offset);
    afterCommand(fnName);
}

// Calls glTexStorageMem1DEXT().
void EXTMemoryObjectAPI::texStorageMem1D(TextureTarget target, GLsizei levels,
                                         SizedInternalFormat internalFormat,
                                         GLsizei width, GLuint memory,
                                         GLuint64 offset) const
{
    static const char *fnName = "glTexStorageMem1DEXT";

    beforeCommand(fnName, _api.glTexStorageMem1D);
    _api.glTexStorageMem1D(toScalar(target), levels, toScalar(internalFormat),
                           width, memory, offset);
    afterCommand(fnName);
}

// Calls glTexStorageMem2DEXT().
void EXTMemoryObjectAPI::texStorageMem2D(TextureTarget target, GLsizei levels,
                                         SizedInternalFormat internalFormat,
                                         GLsizei width, GLsizei height,
                                         GLuint memory, GLuint64 offset) const
{
    static const char *fnName = "glTexStorageMem2DEXT";

    beforeCommand(fnName, _api.glTexStorageMem2D);
    _api.glTexStorageMem2D(toScalar(target), levels, toScalar(internalFormat),
                           width, height, memory, offset);
    afterCommand(fnName);
}

// Calls glTexStorageMem2DMultisampleEXT().
void EXTMemoryObjectAPI::texStorageMem2DMultisample(TextureTarget target,
                                                    GLsizei samples,
                                                    SizedInternalFormat internalFormat,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    Boolean fixedSampleLocations,
                                                    GLuint memory,
                                                    GLuint64 offset) const
{
    static const char *fnName = "glTexStorageMem2DMultisampleEXT";

    beforeCommand(fnName, _api.glTexStorageMem2DMultisample);
    _api.glTexStorageMem2DMultisample(toScalar(target), samples,
                                      toScalar(internalFormat), width, height,
                                      toScalar(fixedSampleLocations), memory,
                                      offset);
    afterCommand(fnName);
}

// Calls glTexStorageMem3DEXT().
void EXTMemoryObjectAPI::texStorageMem3D(TextureTarget target, GLsizei levels,
                                         SizedInternalFormat internalFormat,
                                         GLsizei width, GLsizei height,
                                         GLsizei depth, GLuint memory,
                                         GLuint64 offset) const
{
    static const char *fnName = "glTexStorageMem3DEXT";

    beforeCommand(fnName, _api.glTexStorageMem3D);
    _api.glTexStorageMem3D(toScalar(target), levels, toScalar(internalFormat),
                           width, height, depth, memory, offset);
    afterCommand(fnName);
}

// Calls glTexStorageMem3DMultisampleEXT().
void EXTMemoryObjectAPI::texStorageMem3DMultisample(TextureTarget target,
                                                    GLsizei samples,
                                                    SizedInternalFormat internalFormat,
                                                    GLsizei width,
                                                    GLsizei height,
                                                    GLsizei depth,
                                                    Boolean fixedSampleLocations,
                                                    GLuint memory,
                                                    GLuint64 offset) const
{
    static const char *fnName = "glTexStorageMem3DMultisampleEXT";

    beforeCommand(fnName, _api.glTexStorageMem3DMultisample);
    _api.glTexStorageMem3DMultisample(toScalar(target), samples,
                                      toScalar(internalFormat), width, height,
                                      depth, toScalar(fixedSampleLocations),
                                      memory, offset);
    afterCommand(fnName);
}

// Calls glTextureStorageMem1DEXT().
void EXTMemoryObjectAPI::textureStorageMem1D(TextureName texture, GLsizei levels,
                                             SizedInternalFormat internalFormat,
                                             GLsizei width, GLuint memory,
                                             GLuint64 offset) const
{
    static const char *fnName = "glTextureStorageMem1DEXT";

    beforeCommand(fnName, _api.glTextureStorageMem1D);
    _api.glTextureStorageMem1D(texture.ID, levels, toScalar(internalFormat),
                               width, memory, offset);
    afterCommand(fnName);
}

// Calls glTextureStorageMem2DEXT().
void EXTMemoryObjectAPI::textureStorageMem2D(TextureName texture, GLsizei levels,
                                             SizedInternalFormat internalFormat,
                                             GLsizei width, GLsizei height,
                                             GLuint memory, GLuint64 offset) const
{
    static const char *fnName = "glTextureStorageMem2DEXT";

    beforeCommand(fnName, _api.glTextureStorageMem2D);
    _api.glTextureStorageMem2D(texture.ID, levels, toScalar(internalFormat),
                               width, height, memory, offset);
    afterCommand(fnName);
}

// Calls glTextureStorageMem2DMultisampleEXT().
void EXTMemoryObjectAPI::textureStorageMem2DMultisample(TextureName texture,
                                                        GLsizei samples,
                                                        SizedInternalFormat internalFormat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        Boolean fixedSampleLocations,
                                                        GLuint memory,
                                                        GLuint64 offset) const
{
    static const char *fnName = "glTextureStorageMem2DMultisampleEXT";

    beforeCommand(fnName, _api.glTextureStorageMem2DMultisample);
    _api.glTextureStorageMem2DMultisample(texture.ID, samples,
                                          toScalar(internalFormat), width,
                                          height, toScalar(fixedSampleLocations),
                                          memory, offset);
    afterCommand(fnName);
}

// Calls glTextureStorageMem3DEXT().
void EXTMemoryObjectAPI::textureStorageMem3D(TextureName texture, GLsizei levels,
                                             SizedInternalFormat internalFormat,
                                             GLsizei width, GLsizei height,
                                             GLsizei depth, GLuint memory,
                                             GLuint64 offset) const
{
    static const char *fnName = "glTextureStorageMem3DEXT";

    beforeCommand(fnName, _api.glTextureStorageMem3D);
    _api.glTextureStorageMem3D(texture.ID, levels, toScalar(internalFormat),
                               width, height, depth, memory, offset);
    afterCommand(fnName);
}

// Calls glTextureStorageMem3DMultisampleEXT().
void EXTMemoryObjectAPI::textureStorageMem3DMultisample(TextureName texture,
                                                        GLsizei samples,
                                                        SizedInternalFormat internalFormat,
                                                        GLsizei width,
                                                        GLsizei height,
                                                        GLsizei depth,
                                                        Boolean fixedSampleLocations,
                                                        GLuint memory,
                                                        GLuint64 offset) const
{
    static const char *fnName = "glTextureStorageMem3DMultisampleEXT";

    beforeCommand(fnName, _api.glTextureStorageMem3DMultisample);
    _api.glTextureStorageMem3DMultisample(texture.ID, samples,
                                          toScalar(internalFormat), width,
                                          height, depth,
                                          toScalar(fixedSampleLocations), memory,
                                          offset);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObjectFdAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_memory_object_fd extension.
EXTMemoryObjectFdAPI::EXTMemoryObjectFdAPI() :
    BaseExtension("GL_EXT_memory_object_fd")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMemoryObjectFd &EXTMemoryObjectFdAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_memory_object_fd entry points.
void EXTMemoryObjectFdAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glImportMemoryFdEXT().
void EXTMemoryObjectFdAPI::importMemoryFd(GLuint memory, GLuint64 size,
                                          ExternalHandleType handleType,
                                          GLint fd) const
{
    static const char *fnName = "glImportMemoryFdEXT";

    beforeCommand(fnName, _api.glImportMemoryFd);
    _api.glImportMemoryFd(memory, size, toScalar(handleType), fd);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTMemoryObjectWIN32API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_memory_object_win32 extension.
EXTMemoryObjectWIN32API::EXTMemoryObjectWIN32API() :
    BaseExtension("GL_EXT_memory_object_win32")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMemoryObjectWIN32 &EXTMemoryObjectWIN32API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_memory_object_win32 entry points.
void EXTMemoryObjectWIN32API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glImportMemoryWin32HandleEXT().
void EXTMemoryObjectWIN32API::importMemoryWIN32Handle(GLuint memory,
                                                      GLuint64 size,
                                                      ExternalHandleType handleType,
                                                      void *handle) const
{
    static const char *fnName = "glImportMemoryWin32HandleEXT";

    beforeCommand(fnName, _api.glImportMemoryWin32Handle);
    _api.glImportMemoryWin32Handle(memory, size, toScalar(handleType), handle);
    afterCommand(fnName);
}

// Calls glImportMemoryWin32NameEXT().
void EXTMemoryObjectWIN32API::importMemoryWIN32Name(GLuint memory, GLuint64 size,
                                                    ExternalHandleType handleType,
                                                    const void *name) const
{
    static const char *fnName = "glImportMemoryWin32NameEXT";

    beforeCommand(fnName, _api.glImportMemoryWin32Name);
    _api.glImportMemoryWin32Name(memory, size, toScalar(handleType), name);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTMultiDrawArraysAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_multi_draw_arrays extension.
EXTMultiDrawArraysAPI::EXTMultiDrawArraysAPI() :
    BaseExtension("GL_EXT_multi_draw_arrays")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMultiDrawArrays &EXTMultiDrawArraysAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_multi_draw_arrays entry points.
void EXTMultiDrawArraysAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glMultiDrawArraysEXT().
void EXTMultiDrawArraysAPI::multiDrawArrays(PrimitiveType mode,
                                            const GLint *first,
                                            const GLsizei *count,
                                            GLsizei primcount) const
{
    static const char *fnName = "glMultiDrawArraysEXT";

    beforeCommand(fnName, _api.glMultiDrawArrays);
    _api.glMultiDrawArrays(toScalar(mode), first, count, primcount);
    afterCommand(fnName);
}

// Calls glMultiDrawElementsEXT().
void EXTMultiDrawArraysAPI::multiDrawElements(PrimitiveType mode,
                                              const GLsizei *count,
                                              DrawElementsType type,
                                              const void *const *indices,
                                              GLsizei primcount) const
{
    static const char *fnName = "glMultiDrawElementsEXT";

    beforeCommand(fnName, _api.glMultiDrawElements);
    _api.glMultiDrawElements(toScalar(mode), count, toScalar(type), indices,
                             primcount);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_multisample extension.
EXTMultisampleAPI::EXTMultisampleAPI() :
    BaseExtension("GL_EXT_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMultisample &EXTMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_multisample entry points.
void EXTMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSampleMaskEXT().
void EXTMultisampleAPI::sampleMask(GLclampf value, Boolean invert) const
{
    static const char *fnName = "glSampleMaskEXT";

    beforeCommand(fnName, _api.glSampleMask);
    _api.glSampleMask(value, toScalar(invert));
    afterCommand(fnName);
}

// Calls glSamplePatternEXT().
void EXTMultisampleAPI::samplePattern(SamplePatternEXT pattern) const
{
    static const char *fnName = "glSamplePatternEXT";

    beforeCommand(fnName, _api.glSamplePattern);
    _api.glSamplePattern(toScalar(pattern));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTPalettedTextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_paletted_texture extension.
EXTPalettedTextureAPI::EXTPalettedTextureAPI() :
    BaseExtension("GL_EXT_paletted_texture")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPalettedTexture &EXTPalettedTextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_paletted_texture entry points.
void EXTPalettedTextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColorTableEXT().
void EXTPalettedTextureAPI::colorTable(GLenum target,
                                       InternalFormat internalFormat,
                                       GLsizei width, PixelFormat format,
                                       PixelType type, const void *table) const
{
    static const char *fnName = "glColorTableEXT";

    beforeCommand(fnName, _api.glColorTable);
    _api.glColorTable(target, toScalar(internalFormat), width, toScalar(format),
                      toScalar(type), table);
    afterCommand(fnName);
}

// Calls glGetColorTableEXT().
void EXTPalettedTextureAPI::getColorTable(GLenum target, PixelFormat format,
                                          PixelType type, void *data) const
{
    static const char *fnName = "glGetColorTableEXT";

    beforeCommand(fnName, _api.glGetColorTable);
    _api.glGetColorTable(target, toScalar(format), toScalar(type), data);
    afterCommand(fnName);
}

// Calls glGetColorTableParameterfvEXT().
void EXTPalettedTextureAPI::getColorTableParameterFV(GLenum target,
                                                     GetColorTableParameterPNameSGI pname,
                                                     GLfloat *params) const
{
    static const char *fnName = "glGetColorTableParameterfvEXT";

    beforeCommand(fnName, _api.glGetColorTableParameterfv);
    _api.glGetColorTableParameterfv(target, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetColorTableParameterivEXT().
void EXTPalettedTextureAPI::getColorTableParameterIV(GLenum target,
                                                     GetColorTableParameterPNameSGI pname,
                                                     GLint *params) const
{
    static const char *fnName = "glGetColorTableParameterivEXT";

    beforeCommand(fnName, _api.glGetColorTableParameteriv);
    _api.glGetColorTableParameteriv(target, toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTPixelTransformAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_pixel_transform extension.
EXTPixelTransformAPI::EXTPixelTransformAPI() :
    BaseExtension("GL_EXT_pixel_transform")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPixelTransform &EXTPixelTransformAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_pixel_transform entry points.
void EXTPixelTransformAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetPixelTransformParameterfvEXT().
void EXTPixelTransformAPI::getPixelTransformParameterFV(GLenum target,
                                                        GLenum pname,
                                                        GLfloat *params) const
{
    static const char *fnName = "glGetPixelTransformParameterfvEXT";

    beforeCommand(fnName, _api.glGetPixelTransformParameterfv);
    _api.glGetPixelTransformParameterfv(target, pname, params);
    afterCommand(fnName);
}

// Calls glGetPixelTransformParameterivEXT().
void EXTPixelTransformAPI::getPixelTransformParameterIV(GLenum target,
                                                        GLenum pname,
                                                        GLint *params) const
{
    static const char *fnName = "glGetPixelTransformParameterivEXT";

    beforeCommand(fnName, _api.glGetPixelTransformParameteriv);
    _api.glGetPixelTransformParameteriv(target, pname, params);
    afterCommand(fnName);
}

// Calls glPixelTransformParameterfEXT().
void EXTPixelTransformAPI::pixelTransformParameterF(PixelTransformTargetEXT target,
                                                    PixelTransformPNameEXT pname,
                                                    GLfloat param) const
{
    static const char *fnName = "glPixelTransformParameterfEXT";

    beforeCommand(fnName, _api.glPixelTransformParameterf);
    _api.glPixelTransformParameterf(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelTransformParameterfvEXT().
void EXTPixelTransformAPI::pixelTransformParameterFV(PixelTransformTargetEXT target,
                                                     PixelTransformPNameEXT pname,
                                                     const GLfloat *params) const
{
    static const char *fnName = "glPixelTransformParameterfvEXT";

    beforeCommand(fnName, _api.glPixelTransformParameterfv);
    _api.glPixelTransformParameterfv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glPixelTransformParameteriEXT().
void EXTPixelTransformAPI::pixelTransformParameterI(PixelTransformTargetEXT target,
                                                    PixelTransformPNameEXT pname,
                                                    GLint param) const
{
    static const char *fnName = "glPixelTransformParameteriEXT";

    beforeCommand(fnName, _api.glPixelTransformParameteri);
    _api.glPixelTransformParameteri(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPixelTransformParameterivEXT().
void EXTPixelTransformAPI::pixelTransformParameterIV(PixelTransformTargetEXT target,
                                                     PixelTransformPNameEXT pname,
                                                     const GLint *params) const
{
    static const char *fnName = "glPixelTransformParameterivEXT";

    beforeCommand(fnName, _api.glPixelTransformParameteriv);
    _api.glPixelTransformParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTPointParametersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_point_parameters extension.
EXTPointParametersAPI::EXTPointParametersAPI() :
    BaseExtension("GL_EXT_point_parameters")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPointParameters &EXTPointParametersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_point_parameters entry points.
void EXTPointParametersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPointParameterfEXT().
void EXTPointParametersAPI::pointParameterF(PointParameterNameARB pname,
                                            GLfloat param) const
{
    static const char *fnName = "glPointParameterfEXT";

    beforeCommand(fnName, _api.glPointParameterf);
    _api.glPointParameterf(toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glPointParameterfvEXT().
void EXTPointParametersAPI::pointParameterFV(PointParameterNameARB pname,
                                             const GLfloat *params) const
{
    static const char *fnName = "glPointParameterfvEXT";

    beforeCommand(fnName, _api.glPointParameterfv);
    _api.glPointParameterfv(toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTPolygonOffsetAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_polygon_offset extension.
EXTPolygonOffsetAPI::EXTPolygonOffsetAPI() :
    BaseExtension("GL_EXT_polygon_offset")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPolygonOffset &EXTPolygonOffsetAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_polygon_offset entry points.
void EXTPolygonOffsetAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPolygonOffsetEXT().
void EXTPolygonOffsetAPI::polygonOffset(GLfloat factor, GLfloat bias) const
{
    static const char *fnName = "glPolygonOffsetEXT";

    beforeCommand(fnName, _api.glPolygonOffset);
    _api.glPolygonOffset(factor, bias);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTPolygonOffsetClampAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_polygon_offset_clamp extension.
EXTPolygonOffsetClampAPI::EXTPolygonOffsetClampAPI() :
    BaseExtension("GL_EXT_polygon_offset_clamp")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPolygonOffsetClamp &EXTPolygonOffsetClampAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_polygon_offset_clamp entry points.
void EXTPolygonOffsetClampAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glPolygonOffsetClampEXT().
void EXTPolygonOffsetClampAPI::polygonOffsetClamp(GLfloat factor, GLfloat units,
                                                  GLfloat clamp) const
{
    static const char *fnName = "glPolygonOffsetClampEXT";

    beforeCommand(fnName, _api.glPolygonOffsetClamp);
    _api.glPolygonOffsetClamp(factor, units, clamp);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTProvokingVertexAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_provoking_vertex extension.
EXTProvokingVertexAPI::EXTProvokingVertexAPI() :
    BaseExtension("GL_EXT_provoking_vertex")
{
}

// Grant read-only access to the underlying function pointers.
const EXTProvokingVertex &EXTProvokingVertexAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_provoking_vertex entry points.
void EXTProvokingVertexAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glProvokingVertexEXT().
void EXTProvokingVertexAPI::provokingVertex(VertexProvokingMode mode) const
{
    static const char *fnName = "glProvokingVertexEXT";

    beforeCommand(fnName, _api.glProvokingVertex);
    _api.glProvokingVertex(toScalar(mode));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTRasterMultisampleAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_raster_multisample extension.
EXTRasterMultisampleAPI::EXTRasterMultisampleAPI() :
    BaseExtension("GL_EXT_raster_multisample")
{
}

// Grant read-only access to the underlying function pointers.
const EXTRasterMultisample &EXTRasterMultisampleAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_raster_multisample entry points.
void EXTRasterMultisampleAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glRasterSamplesEXT().
void EXTRasterMultisampleAPI::rasterSamples(GLuint samples,
                                            Boolean fixedsamplelocations) const
{
    static const char *fnName = "glRasterSamplesEXT";

    beforeCommand(fnName, _api.glRasterSamples);
    _api.glRasterSamples(samples, toScalar(fixedsamplelocations));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSecondaryColorAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_secondary_color extension.
EXTSecondaryColorAPI::EXTSecondaryColorAPI() :
    BaseExtension("GL_EXT_secondary_color")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSecondaryColor &EXTSecondaryColorAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_secondary_color entry points.
void EXTSecondaryColorAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glSecondaryColor3bEXT().
void EXTSecondaryColorAPI::secondaryColor3B(GLbyte red, GLbyte green,
                                            GLbyte blue) const
{
    static const char *fnName = "glSecondaryColor3bEXT";

    beforeCommand(fnName, _api.glSecondaryColor3b);
    _api.glSecondaryColor3b(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3bvEXT().
void EXTSecondaryColorAPI::secondaryColor3BV(const GLbyte *v) const
{
    static const char *fnName = "glSecondaryColor3bvEXT";

    beforeCommand(fnName, _api.glSecondaryColor3bv);
    _api.glSecondaryColor3bv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3dEXT().
void EXTSecondaryColorAPI::secondaryColor3D(GLdouble red, GLdouble green,
                                            GLdouble blue) const
{
    static const char *fnName = "glSecondaryColor3dEXT";

    beforeCommand(fnName, _api.glSecondaryColor3d);
    _api.glSecondaryColor3d(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3dvEXT().
void EXTSecondaryColorAPI::secondaryColor3DV(const GLdouble *v) const
{
    static const char *fnName = "glSecondaryColor3dvEXT";

    beforeCommand(fnName, _api.glSecondaryColor3dv);
    _api.glSecondaryColor3dv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3fEXT().
void EXTSecondaryColorAPI::secondaryColor3F(GLfloat red, GLfloat green,
                                            GLfloat blue) const
{
    static const char *fnName = "glSecondaryColor3fEXT";

    beforeCommand(fnName, _api.glSecondaryColor3f);
    _api.glSecondaryColor3f(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3fvEXT().
void EXTSecondaryColorAPI::secondaryColor3FV(const GLfloat *v) const
{
    static const char *fnName = "glSecondaryColor3fvEXT";

    beforeCommand(fnName, _api.glSecondaryColor3fv);
    _api.glSecondaryColor3fv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3iEXT().
void EXTSecondaryColorAPI::secondaryColor3I(GLint red, GLint green, GLint blue) const
{
    static const char *fnName = "glSecondaryColor3iEXT";

    beforeCommand(fnName, _api.glSecondaryColor3i);
    _api.glSecondaryColor3i(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3ivEXT().
void EXTSecondaryColorAPI::secondaryColor3IV(const GLint *v) const
{
    static const char *fnName = "glSecondaryColor3ivEXT";

    beforeCommand(fnName, _api.glSecondaryColor3iv);
    _api.glSecondaryColor3iv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3sEXT().
void EXTSecondaryColorAPI::secondaryColor3S(GLshort red, GLshort green,
                                            GLshort blue) const
{
    static const char *fnName = "glSecondaryColor3sEXT";

    beforeCommand(fnName, _api.glSecondaryColor3s);
    _api.glSecondaryColor3s(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3svEXT().
void EXTSecondaryColorAPI::secondaryColor3SV(const GLshort *v) const
{
    static const char *fnName = "glSecondaryColor3svEXT";

    beforeCommand(fnName, _api.glSecondaryColor3sv);
    _api.glSecondaryColor3sv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3ubEXT().
void EXTSecondaryColorAPI::secondaryColor3UB(GLubyte red, GLubyte green,
                                             GLubyte blue) const
{
    static const char *fnName = "glSecondaryColor3ubEXT";

    beforeCommand(fnName, _api.glSecondaryColor3ub);
    _api.glSecondaryColor3ub(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3ubvEXT().
void EXTSecondaryColorAPI::secondaryColor3UBV(const GLubyte *v) const
{
    static const char *fnName = "glSecondaryColor3ubvEXT";

    beforeCommand(fnName, _api.glSecondaryColor3ubv);
    _api.glSecondaryColor3ubv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3uiEXT().
void EXTSecondaryColorAPI::secondaryColor3UI(GLuint red, GLuint green,
                                             GLuint blue) const
{
    static const char *fnName = "glSecondaryColor3uiEXT";

    beforeCommand(fnName, _api.glSecondaryColor3ui);
    _api.glSecondaryColor3ui(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3uivEXT().
void EXTSecondaryColorAPI::secondaryColor3UIV(const GLuint *v) const
{
    static const char *fnName = "glSecondaryColor3uivEXT";

    beforeCommand(fnName, _api.glSecondaryColor3uiv);
    _api.glSecondaryColor3uiv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColor3usEXT().
void EXTSecondaryColorAPI::secondaryColor3US(GLushort red, GLushort green,
                                             GLushort blue) const
{
    static const char *fnName = "glSecondaryColor3usEXT";

    beforeCommand(fnName, _api.glSecondaryColor3us);
    _api.glSecondaryColor3us(red, green, blue);
    afterCommand(fnName);
}

// Calls glSecondaryColor3usvEXT().
void EXTSecondaryColorAPI::secondaryColor3USV(const GLushort *v) const
{
    static const char *fnName = "glSecondaryColor3usvEXT";

    beforeCommand(fnName, _api.glSecondaryColor3usv);
    _api.glSecondaryColor3usv(v);
    afterCommand(fnName);
}

// Calls glSecondaryColorPointerEXT().
void EXTSecondaryColorAPI::secondaryColorPointer(GLint size,
                                                 ColorPointerType type,
                                                 GLsizei stride,
                                                 const void *pointer) const
{
    static const char *fnName = "glSecondaryColorPointerEXT";

    beforeCommand(fnName, _api.glSecondaryColorPointer);
    _api.glSecondaryColorPointer(size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphoreAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_semaphore extension.
EXTSemaphoreAPI::EXTSemaphoreAPI() :
    BaseExtension("GL_EXT_semaphore")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSemaphore &EXTSemaphoreAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_semaphore entry points.
void EXTSemaphoreAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDeleteSemaphoresEXT().
void EXTSemaphoreAPI::deleteSemaphores(GLsizei n, const GLuint *semaphores) const
{
    static const char *fnName = "glDeleteSemaphoresEXT";

    beforeCommand(fnName, _api.glDeleteSemaphores);
    _api.glDeleteSemaphores(n, semaphores);
    afterCommand(fnName);
}

// Calls glGenSemaphoresEXT().
void EXTSemaphoreAPI::genSemaphores(GLsizei n, GLuint *semaphores) const
{
    static const char *fnName = "glGenSemaphoresEXT";

    beforeCommand(fnName, _api.glGenSemaphores);
    _api.glGenSemaphores(n, semaphores);
    afterCommand(fnName);
}

// Calls glGetSemaphoreParameterui64vEXT().
void EXTSemaphoreAPI::getSemaphoreParameterUI64(GLuint semaphore,
                                                SemaphoreParameterName pname,
                                                GLuint64 *params) const
{
    static const char *fnName = "glGetSemaphoreParameterui64vEXT";

    beforeCommand(fnName, _api.glGetSemaphoreParameterui64v);
    _api.glGetSemaphoreParameterui64v(semaphore, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIsSemaphoreEXT().
Boolean EXTSemaphoreAPI::isSemaphore(GLuint semaphore) const
{
    static const char *fnName = "glIsSemaphoreEXT";

    beforeCommand(fnName, _api.glIsSemaphore);
    GLboolean result = _api.glIsSemaphore(semaphore);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glSemaphoreParameterui64vEXT().
void EXTSemaphoreAPI::semaphoreParameterUI64(GLuint semaphore,
                                             SemaphoreParameterName pname,
                                             const GLuint64 *params) const
{
    static const char *fnName = "glSemaphoreParameterui64vEXT";

    beforeCommand(fnName, _api.glSemaphoreParameterui64v);
    _api.glSemaphoreParameterui64v(semaphore, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glSignalSemaphoreEXT().
void EXTSemaphoreAPI::signalSemaphore(GLuint semaphore, GLuint numBufferBarriers,
                                      const BufferName *buffers,
                                      GLuint numTextureBarriers,
                                      const TextureName *textures,
                                      const TextureLayout *dstLayouts) const
{
    static const char *fnName = "glSignalSemaphoreEXT";

    beforeCommand(fnName, _api.glSignalSemaphore);
    _api.glSignalSemaphore(semaphore, numBufferBarriers,
                           reinterpret_cast<const GLuint *>(buffers),
                           numTextureBarriers,
                           reinterpret_cast<const GLuint *>(textures),
                           toScalarPtr(dstLayouts));
    afterCommand(fnName);
}

// Calls glWaitSemaphoreEXT().
void EXTSemaphoreAPI::waitSemaphore(GLuint semaphore, GLuint numBufferBarriers,
                                    const BufferName *buffers,
                                    GLuint numTextureBarriers,
                                    const TextureName *textures,
                                    const TextureLayout *srcLayouts) const
{
    static const char *fnName = "glWaitSemaphoreEXT";

    beforeCommand(fnName, _api.glWaitSemaphore);
    _api.glWaitSemaphore(semaphore, numBufferBarriers,
                         reinterpret_cast<const GLuint *>(buffers),
                         numTextureBarriers,
                         reinterpret_cast<const GLuint *>(textures),
                         toScalarPtr(srcLayouts));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphoreFdAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_semaphore_fd extension.
EXTSemaphoreFdAPI::EXTSemaphoreFdAPI() :
    BaseExtension("GL_EXT_semaphore_fd")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSemaphoreFd &EXTSemaphoreFdAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_semaphore_fd entry points.
void EXTSemaphoreFdAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glImportSemaphoreFdEXT().
void EXTSemaphoreFdAPI::importSemaphoreFd(GLuint semaphore,
                                          ExternalHandleType handleType,
                                          GLint fd) const
{
    static const char *fnName = "glImportSemaphoreFdEXT";

    beforeCommand(fnName, _api.glImportSemaphoreFd);
    _api.glImportSemaphoreFd(semaphore, toScalar(handleType), fd);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSemaphoreWIN32API Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_semaphore_win32 extension.
EXTSemaphoreWIN32API::EXTSemaphoreWIN32API() :
    BaseExtension("GL_EXT_semaphore_win32")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSemaphoreWIN32 &EXTSemaphoreWIN32API::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_semaphore_win32 entry points.
void EXTSemaphoreWIN32API::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glImportSemaphoreWin32HandleEXT().
void EXTSemaphoreWIN32API::importSemaphoreWIN32Handle(GLuint semaphore,
                                                      ExternalHandleType handleType,
                                                      void *handle) const
{
    static const char *fnName = "glImportSemaphoreWin32HandleEXT";

    beforeCommand(fnName, _api.glImportSemaphoreWin32Handle);
    _api.glImportSemaphoreWin32Handle(semaphore, toScalar(handleType), handle);
    afterCommand(fnName);
}

// Calls glImportSemaphoreWin32NameEXT().
void EXTSemaphoreWIN32API::importSemaphoreWIN32Name(GLuint semaphore,
                                                    ExternalHandleType handleType,
                                                    const void *name) const
{
    static const char *fnName = "glImportSemaphoreWin32NameEXT";

    beforeCommand(fnName, _api.glImportSemaphoreWin32Name);
    _api.glImportSemaphoreWin32Name(semaphore, toScalar(handleType), name);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSeparateShaderObjectsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_separate_shader_objects extension.
EXTSeparateShaderObjectsAPI::EXTSeparateShaderObjectsAPI() :
    BaseExtension("GL_EXT_separate_shader_objects")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSeparateShaderObjects &EXTSeparateShaderObjectsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_separate_shader_objects entry points.
void EXTSeparateShaderObjectsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glActiveProgramEXT().
void EXTSeparateShaderObjectsAPI::activeProgram(ProgramName program) const
{
    static const char *fnName = "glActiveProgramEXT";

    beforeCommand(fnName, _api.glActiveProgram);
    _api.glActiveProgram(program.ID);
    afterCommand(fnName);
}

// Calls glCreateShaderProgramEXT().
ProgramName EXTSeparateShaderObjectsAPI::createShaderProgram(ShaderType type,
                                                             const GLchar *string) const
{
    static const char *fnName = "glCreateShaderProgramEXT";

    beforeCommand(fnName, _api.glCreateShaderProgram);
    GLuint result = _api.glCreateShaderProgram(toScalar(type), string);
    afterCommand(fnName);

    return ProgramName(result);
}

// Calls glUseShaderProgramEXT().
void EXTSeparateShaderObjectsAPI::useShaderProgram(GLenum type,
                                                   ProgramName program) const
{
    static const char *fnName = "glUseShaderProgramEXT";

    beforeCommand(fnName, _api.glUseShaderProgram);
    _api.glUseShaderProgram(type, program.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTShaderFramebufferFetchNonCoherentAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_shader_framebuffer_fetch_non_coherent extension.
EXTShaderFramebufferFetchNonCoherentAPI::EXTShaderFramebufferFetchNonCoherentAPI() :
    BaseExtension("GL_EXT_shader_framebuffer_fetch_non_coherent")
{
}

// Grant read-only access to the underlying function pointers.
const EXTShaderFramebufferFetchNonCoherent &EXTShaderFramebufferFetchNonCoherentAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_shader_framebuffer_fetch_non_coherent entry points.
void EXTShaderFramebufferFetchNonCoherentAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferFetchBarrierEXT().
void EXTShaderFramebufferFetchNonCoherentAPI::framebufferFetchBarrier() const
{
    static const char *fnName = "glFramebufferFetchBarrierEXT";

    beforeCommand(fnName, _api.glFramebufferFetchBarrier);
    _api.glFramebufferFetchBarrier();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTShaderImageLoadStoreAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_shader_image_load_store extension.
EXTShaderImageLoadStoreAPI::EXTShaderImageLoadStoreAPI() :
    BaseExtension("GL_EXT_shader_image_load_store")
{
}

// Grant read-only access to the underlying function pointers.
const EXTShaderImageLoadStore &EXTShaderImageLoadStoreAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_shader_image_load_store entry points.
void EXTShaderImageLoadStoreAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBindImageTextureEXT().
void EXTShaderImageLoadStoreAPI::bindImageTexture(GLuint index,
                                                  TextureName texture,
                                                  GLint level, Boolean layered,
                                                  GLint layer,
                                                  BufferAccessARB access,
                                                  GLint format) const
{
    static const char *fnName = "glBindImageTextureEXT";

    beforeCommand(fnName, _api.glBindImageTexture);
    _api.glBindImageTexture(index, texture.ID, level, toScalar(layered), layer,
                            toScalar(access), format);
    afterCommand(fnName);
}

// Calls glMemoryBarrierEXT().
void EXTShaderImageLoadStoreAPI::memoryBarrier(GLbitfield  /* MemoryBarrierMask */ barriers) const
{
    static const char *fnName = "glMemoryBarrierEXT";

    beforeCommand(fnName, _api.glMemoryBarrier);
    _api.glMemoryBarrier(barriers);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTStencilClearTagAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_stencil_clear_tag extension.
EXTStencilClearTagAPI::EXTStencilClearTagAPI() :
    BaseExtension("GL_EXT_stencil_clear_tag")
{
}

// Grant read-only access to the underlying function pointers.
const EXTStencilClearTag &EXTStencilClearTagAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_stencil_clear_tag entry points.
void EXTStencilClearTagAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glStencilClearTagEXT().
void EXTStencilClearTagAPI::stencilClearTag(GLsizei stencilTagBits,
                                            GLuint stencilClearTag) const
{
    static const char *fnName = "glStencilClearTagEXT";

    beforeCommand(fnName, _api.glStencilClearTag);
    _api.glStencilClearTag(stencilTagBits, stencilClearTag);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTStencilTwoSideAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_stencil_two_side extension.
EXTStencilTwoSideAPI::EXTStencilTwoSideAPI() :
    BaseExtension("GL_EXT_stencil_two_side")
{
}

// Grant read-only access to the underlying function pointers.
const EXTStencilTwoSide &EXTStencilTwoSideAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_stencil_two_side entry points.
void EXTStencilTwoSideAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glActiveStencilFaceEXT().
void EXTStencilTwoSideAPI::activeStencilFace(StencilFaceDirection face) const
{
    static const char *fnName = "glActiveStencilFaceEXT";

    beforeCommand(fnName, _api.glActiveStencilFace);
    _api.glActiveStencilFace(toScalar(face));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTSubtextureAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_subtexture extension.
EXTSubtextureAPI::EXTSubtextureAPI() :
    BaseExtension("GL_EXT_subtexture")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSubtexture &EXTSubtextureAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_subtexture entry points.
void EXTSubtextureAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexSubImage1DEXT().
void EXTSubtextureAPI::texSubImage1D(TextureTarget target, GLint level,
                                     GLint xoffset, GLsizei width,
                                     PixelFormat format, PixelType type,
                                     const void *pixels) const
{
    static const char *fnName = "glTexSubImage1DEXT";

    beforeCommand(fnName, _api.glTexSubImage1D);
    _api.glTexSubImage1D(toScalar(target), level, xoffset, width,
                         toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

// Calls glTexSubImage2DEXT().
void EXTSubtextureAPI::texSubImage2D(TextureTarget target, GLint level,
                                     GLint xoffset, GLint yoffset, GLsizei width,
                                     GLsizei height, PixelFormat format,
                                     PixelType type, const void *pixels) const
{
    static const char *fnName = "glTexSubImage2DEXT";

    beforeCommand(fnName, _api.glTexSubImage2D);
    _api.glTexSubImage2D(toScalar(target), level, xoffset, yoffset, width,
                         height, toScalar(format), toScalar(type), pixels);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTEXTURE3DAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture3D extension.
EXTTEXTURE3DAPI::EXTTEXTURE3DAPI() :
    BaseExtension("GL_EXT_texture3D")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTEXTURE3D &EXTTEXTURE3DAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture3D entry points.
void EXTTEXTURE3DAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexImage3DEXT().
void EXTTEXTURE3DAPI::texImage3D(TextureTarget target, GLint level,
                                 InternalFormat internalformat, GLsizei width,
                                 GLsizei height, GLsizei depth, GLint border,
                                 PixelFormat format, PixelType type,
                                 const void *pixels) const
{
    static const char *fnName = "glTexImage3DEXT";

    beforeCommand(fnName, _api.glTexImage3D);
    _api.glTexImage3D(toScalar(target), level, toScalar(internalformat), width,
                      height, depth, border, toScalar(format), toScalar(type),
                      pixels);
    afterCommand(fnName);
}

// Calls glTexSubImage3DEXT().
void EXTTEXTURE3DAPI::texSubImage3D(TextureTarget target, GLint level,
                                    GLint xoffset, GLint yoffset, GLint zoffset,
                                    GLsizei width, GLsizei height, GLsizei depth,
                                    PixelFormat format, PixelType type,
                                    const void *pixels) const
{
    static const char *fnName = "glTexSubImage3DEXT";

    beforeCommand(fnName, _api.glTexSubImage3D);
    _api.glTexSubImage3D(toScalar(target), level, xoffset, yoffset, zoffset,
                         width, height, depth, toScalar(format), toScalar(type),
                         pixels);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_array extension.
EXTTextureArrayAPI::EXTTextureArrayAPI() :
    BaseExtension("GL_EXT_texture_array")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureArray &EXTTextureArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_array entry points.
void EXTTextureArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferTextureLayerEXT().
void EXTTextureArrayAPI::framebufferTextureLayer(FramebufferTarget target,
                                                 FramebufferAttachment attachment,
                                                 TextureName texture,
                                                 GLint level, GLint layer) const
{
    static const char *fnName = "glFramebufferTextureLayerEXT";

    beforeCommand(fnName, _api.glFramebufferTextureLayer);
    _api.glFramebufferTextureLayer(toScalar(target), toScalar(attachment),
                                   texture.ID, level, layer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureBufferObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_buffer_object extension.
EXTTextureBufferObjectAPI::EXTTextureBufferObjectAPI() :
    BaseExtension("GL_EXT_texture_buffer_object")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureBufferObject &EXTTextureBufferObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_buffer_object entry points.
void EXTTextureBufferObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexBufferEXT().
void EXTTextureBufferObjectAPI::texBuffer(TextureTarget target,
                                          SizedInternalFormat internalformat,
                                          BufferName buffer) const
{
    static const char *fnName = "glTexBufferEXT";

    beforeCommand(fnName, _api.glTexBuffer);
    _api.glTexBuffer(toScalar(target), toScalar(internalformat), buffer.ID);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureIntegerAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_integer extension.
EXTTextureIntegerAPI::EXTTextureIntegerAPI() :
    BaseExtension("GL_EXT_texture_integer")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureInteger &EXTTextureIntegerAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_integer entry points.
void EXTTextureIntegerAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glClearColorIiEXT().
void EXTTextureIntegerAPI::clearColorII(GLint red, GLint green, GLint blue,
                                        GLint alpha) const
{
    static const char *fnName = "glClearColorIiEXT";

    beforeCommand(fnName, _api.glClearColorIi);
    _api.glClearColorIi(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glClearColorIuiEXT().
void EXTTextureIntegerAPI::clearColorIUI(GLuint red, GLuint green, GLuint blue,
                                         GLuint alpha) const
{
    static const char *fnName = "glClearColorIuiEXT";

    beforeCommand(fnName, _api.glClearColorIui);
    _api.glClearColorIui(red, green, blue, alpha);
    afterCommand(fnName);
}

// Calls glGetTexParameterIivEXT().
void EXTTextureIntegerAPI::getTexParameterIIV(TextureTarget target,
                                              GetTextureParameter pname,
                                              GLint *params) const
{
    static const char *fnName = "glGetTexParameterIivEXT";

    beforeCommand(fnName, _api.glGetTexParameterIiv);
    _api.glGetTexParameterIiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetTexParameterIuivEXT().
void EXTTextureIntegerAPI::getTexParameterIUIV(TextureTarget target,
                                               GetTextureParameter pname,
                                               GLuint *params) const
{
    static const char *fnName = "glGetTexParameterIuivEXT";

    beforeCommand(fnName, _api.glGetTexParameterIuiv);
    _api.glGetTexParameterIuiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTexParameterIivEXT().
void EXTTextureIntegerAPI::texParameterIIV(TextureTarget target,
                                           TextureParameterName pname,
                                           const GLint *params) const
{
    static const char *fnName = "glTexParameterIivEXT";

    beforeCommand(fnName, _api.glTexParameterIiv);
    _api.glTexParameterIiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glTexParameterIuivEXT().
void EXTTextureIntegerAPI::texParameterIUIV(TextureTarget target,
                                            TextureParameterName pname,
                                            const GLuint *params) const
{
    static const char *fnName = "glTexParameterIuivEXT";

    beforeCommand(fnName, _api.glTexParameterIuiv);
    _api.glTexParameterIuiv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_object extension.
EXTTextureObjectAPI::EXTTextureObjectAPI() :
    BaseExtension("GL_EXT_texture_object")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureObject &EXTTextureObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_object entry points.
void EXTTextureObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAreTexturesResidentEXT().
Boolean EXTTextureObjectAPI::areTexturesResident(GLsizei n,
                                                 const TextureName *textures,
                                                 Boolean *residences) const
{
    static const char *fnName = "glAreTexturesResidentEXT";

    beforeCommand(fnName, _api.glAreTexturesResident);
    GLboolean result = _api.glAreTexturesResident(n,
                                                  reinterpret_cast<const GLuint *>(textures),
                                                  toScalarPtr(residences));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glBindTextureEXT().
void EXTTextureObjectAPI::bindTexture(TextureTarget target, TextureName texture) const
{
    static const char *fnName = "glBindTextureEXT";

    beforeCommand(fnName, _api.glBindTexture);
    _api.glBindTexture(toScalar(target), texture.ID);
    afterCommand(fnName);
}

// Calls glDeleteTexturesEXT().
void EXTTextureObjectAPI::deleteTextures(GLsizei n, const TextureName *textures) const
{
    static const char *fnName = "glDeleteTexturesEXT";

    beforeCommand(fnName, _api.glDeleteTextures);
    _api.glDeleteTextures(n, reinterpret_cast<const GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glGenTexturesEXT().
void EXTTextureObjectAPI::genTextures(GLsizei n, TextureName *textures) const
{
    static const char *fnName = "glGenTexturesEXT";

    beforeCommand(fnName, _api.glGenTextures);
    _api.glGenTextures(n, reinterpret_cast<GLuint *>(textures));
    afterCommand(fnName);
}

// Calls glIsTextureEXT().
Boolean EXTTextureObjectAPI::isTexture(TextureName texture) const
{
    static const char *fnName = "glIsTextureEXT";

    beforeCommand(fnName, _api.glIsTexture);
    GLboolean result = _api.glIsTexture(texture.ID);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glPrioritizeTexturesEXT().
void EXTTextureObjectAPI::prioritizeTextures(GLsizei n,
                                             const TextureName *textures,
                                             const GLclampf *priorities) const
{
    static const char *fnName = "glPrioritizeTexturesEXT";

    beforeCommand(fnName, _api.glPrioritizeTextures);
    _api.glPrioritizeTextures(n, reinterpret_cast<const GLuint *>(textures),
                              priorities);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTexturePerturbNormalAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_perturb_normal extension.
EXTTexturePerturbNormalAPI::EXTTexturePerturbNormalAPI() :
    BaseExtension("GL_EXT_texture_perturb_normal")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTexturePerturbNormal &EXTTexturePerturbNormalAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_perturb_normal entry points.
void EXTTexturePerturbNormalAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTextureNormalEXT().
void EXTTexturePerturbNormalAPI::textureNormal(TextureNormalModeEXT mode) const
{
    static const char *fnName = "glTextureNormalEXT";

    beforeCommand(fnName, _api.glTextureNormal);
    _api.glTextureNormal(toScalar(mode));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureStorageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_texture_storage extension.
EXTTextureStorageAPI::EXTTextureStorageAPI() :
    BaseExtension("GL_EXT_texture_storage")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureStorage &EXTTextureStorageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_texture_storage entry points.
void EXTTextureStorageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glTexStorage1DEXT().
void EXTTextureStorageAPI::texStorage1D(TextureTarget target, GLsizei levels,
                                        SizedInternalFormat internalformat,
                                        GLsizei width) const
{
    static const char *fnName = "glTexStorage1DEXT";

    beforeCommand(fnName, _api.glTexStorage1D);
    _api.glTexStorage1D(toScalar(target), levels, toScalar(internalformat),
                        width);
    afterCommand(fnName);
}

// Calls glTexStorage2DEXT().
void EXTTextureStorageAPI::texStorage2D(TextureTarget target, GLsizei levels,
                                        SizedInternalFormat internalformat,
                                        GLsizei width, GLsizei height) const
{
    static const char *fnName = "glTexStorage2DEXT";

    beforeCommand(fnName, _api.glTexStorage2D);
    _api.glTexStorage2D(toScalar(target), levels, toScalar(internalformat),
                        width, height);
    afterCommand(fnName);
}

// Calls glTexStorage3DEXT().
void EXTTextureStorageAPI::texStorage3D(TextureTarget target, GLsizei levels,
                                        SizedInternalFormat internalformat,
                                        GLsizei width, GLsizei height,
                                        GLsizei depth) const
{
    static const char *fnName = "glTexStorage3DEXT";

    beforeCommand(fnName, _api.glTexStorage3D);
    _api.glTexStorage3D(toScalar(target), levels, toScalar(internalformat),
                        width, height, depth);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTimerQueryAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_timer_query extension.
EXTTimerQueryAPI::EXTTimerQueryAPI() :
    BaseExtension("GL_EXT_timer_query")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTimerQuery &EXTTimerQueryAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_timer_query entry points.
void EXTTimerQueryAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetQueryObjecti64vEXT().
void EXTTimerQueryAPI::getQueryObjectI64V(QueryName id,
                                          QueryObjectParameterName pname,
                                          GLint64 *params) const
{
    static const char *fnName = "glGetQueryObjecti64vEXT";

    beforeCommand(fnName, _api.glGetQueryObjecti64v);
    _api.glGetQueryObjecti64v(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glGetQueryObjectui64vEXT().
void EXTTimerQueryAPI::getQueryObjectUI64(QueryName id,
                                          QueryObjectParameterName pname,
                                          GLuint64 *params) const
{
    static const char *fnName = "glGetQueryObjectui64vEXT";

    beforeCommand(fnName, _api.glGetQueryObjectui64v);
    _api.glGetQueryObjectui64v(id.ID, toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTransformFeedbackAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_transform_feedback extension.
EXTTransformFeedbackAPI::EXTTransformFeedbackAPI() :
    BaseExtension("GL_EXT_transform_feedback")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTransformFeedback &EXTTransformFeedbackAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_transform_feedback entry points.
void EXTTransformFeedbackAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginTransformFeedbackEXT().
void EXTTransformFeedbackAPI::beginTransformFeedback(PrimitiveType primitiveMode) const
{
    static const char *fnName = "glBeginTransformFeedbackEXT";

    beforeCommand(fnName, _api.glBeginTransformFeedback);
    _api.glBeginTransformFeedback(toScalar(primitiveMode));
    afterCommand(fnName);
}

// Calls glBindBufferBaseEXT().
void EXTTransformFeedbackAPI::bindBufferBase(BufferTargetARB target,
                                             GLuint index, BufferName buffer) const
{
    static const char *fnName = "glBindBufferBaseEXT";

    beforeCommand(fnName, _api.glBindBufferBase);
    _api.glBindBufferBase(toScalar(target), index, buffer.ID);
    afterCommand(fnName);
}

// Calls glBindBufferOffsetEXT().
void EXTTransformFeedbackAPI::bindBufferOffset(BufferTargetARB target,
                                               GLuint index, BufferName buffer,
                                               GLintptr offset) const
{
    static const char *fnName = "glBindBufferOffsetEXT";

    beforeCommand(fnName, _api.glBindBufferOffset);
    _api.glBindBufferOffset(toScalar(target), index, buffer.ID, offset);
    afterCommand(fnName);
}

// Calls glBindBufferRangeEXT().
void EXTTransformFeedbackAPI::bindBufferRange(BufferTargetARB target,
                                              GLuint index, BufferName buffer,
                                              GLintptr offset, GLsizeiptr size) const
{
    static const char *fnName = "glBindBufferRangeEXT";

    beforeCommand(fnName, _api.glBindBufferRange);
    _api.glBindBufferRange(toScalar(target), index, buffer.ID, offset, size);
    afterCommand(fnName);
}

// Calls glEndTransformFeedbackEXT().
void EXTTransformFeedbackAPI::endTransformFeedback() const
{
    static const char *fnName = "glEndTransformFeedbackEXT";

    beforeCommand(fnName, _api.glEndTransformFeedback);
    _api.glEndTransformFeedback();
    afterCommand(fnName);
}

// Calls glGetTransformFeedbackVaryingEXT().
void EXTTransformFeedbackAPI::getTransformFeedbackVarying(ProgramName program,
                                                          GLuint index,
                                                          GLsizei bufSize,
                                                          GLsizei *length,
                                                          GLsizei *size,
                                                          AttributeType *type,
                                                          GLchar *name) const
{
    static const char *fnName = "glGetTransformFeedbackVaryingEXT";

    beforeCommand(fnName, _api.glGetTransformFeedbackVarying);
    _api.glGetTransformFeedbackVarying(program.ID, index, bufSize, length, size,
                                       toScalarPtr(type), name);
    afterCommand(fnName);
}

// Calls glTransformFeedbackVaryingsEXT().
void EXTTransformFeedbackAPI::transformFeedbackVaryings(ProgramName program,
                                                        GLsizei count,
                                                        const GLchar *const *varyings,
                                                        GLenum bufferMode) const
{
    static const char *fnName = "glTransformFeedbackVaryingsEXT";

    beforeCommand(fnName, _api.glTransformFeedbackVaryings);
    _api.glTransformFeedbackVaryings(program.ID, count, varyings, bufferMode);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_vertex_array extension.
EXTVertexArrayAPI::EXTVertexArrayAPI() :
    BaseExtension("GL_EXT_vertex_array")
{
}

// Grant read-only access to the underlying function pointers.
const EXTVertexArray &EXTVertexArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_vertex_array entry points.
void EXTVertexArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glArrayElementEXT().
void EXTVertexArrayAPI::arrayElement(GLint i) const
{
    static const char *fnName = "glArrayElementEXT";

    beforeCommand(fnName, _api.glArrayElement);
    _api.glArrayElement(i);
    afterCommand(fnName);
}

// Calls glColorPointerEXT().
void EXTVertexArrayAPI::colorPointer(GLint size, ColorPointerType type,
                                     GLsizei stride, GLsizei count,
                                     const void *pointer) const
{
    static const char *fnName = "glColorPointerEXT";

    beforeCommand(fnName, _api.glColorPointer);
    _api.glColorPointer(size, toScalar(type), stride, count, pointer);
    afterCommand(fnName);
}

// Calls glDrawArraysEXT().
void EXTVertexArrayAPI::drawArrays(PrimitiveType mode, GLint first,
                                   GLsizei count) const
{
    static const char *fnName = "glDrawArraysEXT";

    beforeCommand(fnName, _api.glDrawArrays);
    _api.glDrawArrays(toScalar(mode), first, count);
    afterCommand(fnName);
}

// Calls glEdgeFlagPointerEXT().
void EXTVertexArrayAPI::edgeFlagPointer(GLsizei stride, GLsizei count,
                                        const Boolean *pointer) const
{
    static const char *fnName = "glEdgeFlagPointerEXT";

    beforeCommand(fnName, _api.glEdgeFlagPointer);
    _api.glEdgeFlagPointer(stride, count, toScalarPtr(pointer));
    afterCommand(fnName);
}

// Calls glGetPointervEXT().
void EXTVertexArrayAPI::getPointerV(GetPointervPName pname, void **params) const
{
    static const char *fnName = "glGetPointervEXT";

    beforeCommand(fnName, _api.glGetPointerv);
    _api.glGetPointerv(toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glIndexPointerEXT().
void EXTVertexArrayAPI::indexPointer(IndexPointerType type, GLsizei stride,
                                     GLsizei count, const void *pointer) const
{
    static const char *fnName = "glIndexPointerEXT";

    beforeCommand(fnName, _api.glIndexPointer);
    _api.glIndexPointer(toScalar(type), stride, count, pointer);
    afterCommand(fnName);
}

// Calls glNormalPointerEXT().
void EXTVertexArrayAPI::normalPointer(NormalPointerType type, GLsizei stride,
                                      GLsizei count, const void *pointer) const
{
    static const char *fnName = "glNormalPointerEXT";

    beforeCommand(fnName, _api.glNormalPointer);
    _api.glNormalPointer(toScalar(type), stride, count, pointer);
    afterCommand(fnName);
}

// Calls glTexCoordPointerEXT().
void EXTVertexArrayAPI::texCoordPointer(GLint size, TexCoordPointerType type,
                                        GLsizei stride, GLsizei count,
                                        const void *pointer) const
{
    static const char *fnName = "glTexCoordPointerEXT";

    beforeCommand(fnName, _api.glTexCoordPointer);
    _api.glTexCoordPointer(size, toScalar(type), stride, count, pointer);
    afterCommand(fnName);
}

// Calls glVertexPointerEXT().
void EXTVertexArrayAPI::vertexPointer(GLint size, VertexPointerType type,
                                      GLsizei stride, GLsizei count,
                                      const void *pointer) const
{
    static const char *fnName = "glVertexPointerEXT";

    beforeCommand(fnName, _api.glVertexPointer);
    _api.glVertexPointer(size, toScalar(type), stride, count, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexAttrib64BITAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_vertex_attrib_64bit extension.
EXTVertexAttrib64BITAPI::EXTVertexAttrib64BITAPI() :
    BaseExtension("GL_EXT_vertex_attrib_64bit")
{
}

// Grant read-only access to the underlying function pointers.
const EXTVertexAttrib64BIT &EXTVertexAttrib64BITAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_vertex_attrib_64bit entry points.
void EXTVertexAttrib64BITAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGetVertexAttribLdvEXT().
void EXTVertexAttrib64BITAPI::getVertexAttribLDV(GLuint index,
                                                 VertexAttribEnum pname,
                                                 GLdouble *params) const
{
    static const char *fnName = "glGetVertexAttribLdvEXT";

    beforeCommand(fnName, _api.glGetVertexAttribLdv);
    _api.glGetVertexAttribLdv(index, toScalar(pname), params);
    afterCommand(fnName);
}

// Calls glVertexAttribL1dEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL1D(GLuint index, GLdouble x) const
{
    static const char *fnName = "glVertexAttribL1dEXT";

    beforeCommand(fnName, _api.glVertexAttribL1d);
    _api.glVertexAttribL1d(index, x);
    afterCommand(fnName);
}

// Calls glVertexAttribL1dvEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL1DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL1dvEXT";

    beforeCommand(fnName, _api.glVertexAttribL1dv);
    _api.glVertexAttribL1dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL2dEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL2D(GLuint index, GLdouble x,
                                              GLdouble y) const
{
    static const char *fnName = "glVertexAttribL2dEXT";

    beforeCommand(fnName, _api.glVertexAttribL2d);
    _api.glVertexAttribL2d(index, x, y);
    afterCommand(fnName);
}

// Calls glVertexAttribL2dvEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL2DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL2dvEXT";

    beforeCommand(fnName, _api.glVertexAttribL2dv);
    _api.glVertexAttribL2dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL3dEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL3D(GLuint index, GLdouble x,
                                              GLdouble y, GLdouble z) const
{
    static const char *fnName = "glVertexAttribL3dEXT";

    beforeCommand(fnName, _api.glVertexAttribL3d);
    _api.glVertexAttribL3d(index, x, y, z);
    afterCommand(fnName);
}

// Calls glVertexAttribL3dvEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL3DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL3dvEXT";

    beforeCommand(fnName, _api.glVertexAttribL3dv);
    _api.glVertexAttribL3dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribL4dEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL4D(GLuint index, GLdouble x,
                                              GLdouble y, GLdouble z, GLdouble w) const
{
    static const char *fnName = "glVertexAttribL4dEXT";

    beforeCommand(fnName, _api.glVertexAttribL4d);
    _api.glVertexAttribL4d(index, x, y, z, w);
    afterCommand(fnName);
}

// Calls glVertexAttribL4dvEXT().
void EXTVertexAttrib64BITAPI::vertexAttribL4DV(GLuint index, const GLdouble *v) const
{
    static const char *fnName = "glVertexAttribL4dvEXT";

    beforeCommand(fnName, _api.glVertexAttribL4dv);
    _api.glVertexAttribL4dv(index, v);
    afterCommand(fnName);
}

// Calls glVertexAttribLPointerEXT().
void EXTVertexAttrib64BITAPI::vertexAttribLPointer(GLuint index, GLint size,
                                                   VertexAttribLType type,
                                                   GLsizei stride,
                                                   const void *pointer) const
{
    static const char *fnName = "glVertexAttribLPointerEXT";

    beforeCommand(fnName, _api.glVertexAttribLPointer);
    _api.glVertexAttribLPointer(index, size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexShaderAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_vertex_shader extension.
EXTVertexShaderAPI::EXTVertexShaderAPI() :
    BaseExtension("GL_EXT_vertex_shader")
{
}

// Grant read-only access to the underlying function pointers.
const EXTVertexShader &EXTVertexShaderAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_vertex_shader entry points.
void EXTVertexShaderAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glBeginVertexShaderEXT().
void EXTVertexShaderAPI::beginVertexShader() const
{
    static const char *fnName = "glBeginVertexShaderEXT";

    beforeCommand(fnName, _api.glBeginVertexShader);
    _api.glBeginVertexShader();
    afterCommand(fnName);
}

// Calls glBindLightParameterEXT().
GLuint EXTVertexShaderAPI::bindLightParameter(LightName light, GLenum value) const
{
    static const char *fnName = "glBindLightParameterEXT";

    beforeCommand(fnName, _api.glBindLightParameter);
    GLuint result = _api.glBindLightParameter(toScalar(light), value);
    afterCommand(fnName);

    return result;
}

// Calls glBindMaterialParameterEXT().
GLuint EXTVertexShaderAPI::bindMaterialParameter(MaterialFace face, GLenum value) const
{
    static const char *fnName = "glBindMaterialParameterEXT";

    beforeCommand(fnName, _api.glBindMaterialParameter);
    GLuint result = _api.glBindMaterialParameter(toScalar(face), value);
    afterCommand(fnName);

    return result;
}

// Calls glBindParameterEXT().
GLuint EXTVertexShaderAPI::bindParameter(VertexShaderParameterEXT value) const
{
    static const char *fnName = "glBindParameterEXT";

    beforeCommand(fnName, _api.glBindParameter);
    GLuint result = _api.glBindParameter(toScalar(value));
    afterCommand(fnName);

    return result;
}

// Calls glBindTexGenParameterEXT().
GLuint EXTVertexShaderAPI::bindTexGenParameter(TextureUnit unit, GLenum coord,
                                               TextureGenParameter value) const
{
    static const char *fnName = "glBindTexGenParameterEXT";

    beforeCommand(fnName, _api.glBindTexGenParameter);
    GLuint result = _api.glBindTexGenParameter(toScalar(unit), coord,
                                               toScalar(value));
    afterCommand(fnName);

    return result;
}

// Calls glBindTextureUnitParameterEXT().
GLuint EXTVertexShaderAPI::bindTextureUnitParameter(TextureUnit unit,
                                                    GLenum value) const
{
    static const char *fnName = "glBindTextureUnitParameterEXT";

    beforeCommand(fnName, _api.glBindTextureUnitParameter);
    GLuint result = _api.glBindTextureUnitParameter(toScalar(unit), value);
    afterCommand(fnName);

    return result;
}

// Calls glBindVertexShaderEXT().
void EXTVertexShaderAPI::bindVertexShader(GLuint id) const
{
    static const char *fnName = "glBindVertexShaderEXT";

    beforeCommand(fnName, _api.glBindVertexShader);
    _api.glBindVertexShader(id);
    afterCommand(fnName);
}

// Calls glDeleteVertexShaderEXT().
void EXTVertexShaderAPI::deleteVertexShader(GLuint id) const
{
    static const char *fnName = "glDeleteVertexShaderEXT";

    beforeCommand(fnName, _api.glDeleteVertexShader);
    _api.glDeleteVertexShader(id);
    afterCommand(fnName);
}

// Calls glDisableVariantClientStateEXT().
void EXTVertexShaderAPI::disableVariantClientState(GLuint id) const
{
    static const char *fnName = "glDisableVariantClientStateEXT";

    beforeCommand(fnName, _api.glDisableVariantClientState);
    _api.glDisableVariantClientState(id);
    afterCommand(fnName);
}

// Calls glEnableVariantClientStateEXT().
void EXTVertexShaderAPI::enableVariantClientState(GLuint id) const
{
    static const char *fnName = "glEnableVariantClientStateEXT";

    beforeCommand(fnName, _api.glEnableVariantClientState);
    _api.glEnableVariantClientState(id);
    afterCommand(fnName);
}

// Calls glEndVertexShaderEXT().
void EXTVertexShaderAPI::endVertexShader() const
{
    static const char *fnName = "glEndVertexShaderEXT";

    beforeCommand(fnName, _api.glEndVertexShader);
    _api.glEndVertexShader();
    afterCommand(fnName);
}

// Calls glExtractComponentEXT().
void EXTVertexShaderAPI::extractComponent(GLuint res, GLuint src, GLuint num) const
{
    static const char *fnName = "glExtractComponentEXT";

    beforeCommand(fnName, _api.glExtractComponent);
    _api.glExtractComponent(res, src, num);
    afterCommand(fnName);
}

// Calls glGenSymbolsEXT().
GLuint EXTVertexShaderAPI::genSymbols(DataTypeEXT datatype,
                                      VertexShaderStorageTypeEXT storagetype,
                                      ParameterRangeEXT range, GLuint components) const
{
    static const char *fnName = "glGenSymbolsEXT";

    beforeCommand(fnName, _api.glGenSymbols);
    GLuint result = _api.glGenSymbols(toScalar(datatype), toScalar(storagetype),
                                      toScalar(range), components);
    afterCommand(fnName);

    return result;
}

// Calls glGenVertexShadersEXT().
GLuint EXTVertexShaderAPI::genVertexShaders(GLuint range) const
{
    static const char *fnName = "glGenVertexShadersEXT";

    beforeCommand(fnName, _api.glGenVertexShaders);
    GLuint result = _api.glGenVertexShaders(range);
    afterCommand(fnName);

    return result;
}

// Calls glGetInvariantBooleanvEXT().
void EXTVertexShaderAPI::getInvariantBooleanV(GLuint id,
                                              GetVariantValueEXT value,
                                              Boolean *data) const
{
    static const char *fnName = "glGetInvariantBooleanvEXT";

    beforeCommand(fnName, _api.glGetInvariantBooleanv);
    _api.glGetInvariantBooleanv(id, toScalar(value), toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetInvariantFloatvEXT().
void EXTVertexShaderAPI::getInvariantFloatV(GLuint id, GetVariantValueEXT value,
                                            GLfloat *data) const
{
    static const char *fnName = "glGetInvariantFloatvEXT";

    beforeCommand(fnName, _api.glGetInvariantFloatv);
    _api.glGetInvariantFloatv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetInvariantIntegervEXT().
void EXTVertexShaderAPI::getInvariantIntegerV(GLuint id,
                                              GetVariantValueEXT value,
                                              GLint *data) const
{
    static const char *fnName = "glGetInvariantIntegervEXT";

    beforeCommand(fnName, _api.glGetInvariantIntegerv);
    _api.glGetInvariantIntegerv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetLocalConstantBooleanvEXT().
void EXTVertexShaderAPI::getLocalConstantBooleanV(GLuint id,
                                                  GetVariantValueEXT value,
                                                  Boolean *data) const
{
    static const char *fnName = "glGetLocalConstantBooleanvEXT";

    beforeCommand(fnName, _api.glGetLocalConstantBooleanv);
    _api.glGetLocalConstantBooleanv(id, toScalar(value), toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetLocalConstantFloatvEXT().
void EXTVertexShaderAPI::getLocalConstantFloatV(GLuint id,
                                                GetVariantValueEXT value,
                                                GLfloat *data) const
{
    static const char *fnName = "glGetLocalConstantFloatvEXT";

    beforeCommand(fnName, _api.glGetLocalConstantFloatv);
    _api.glGetLocalConstantFloatv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetLocalConstantIntegervEXT().
void EXTVertexShaderAPI::getLocalConstantIntegerV(GLuint id,
                                                  GetVariantValueEXT value,
                                                  GLint *data) const
{
    static const char *fnName = "glGetLocalConstantIntegervEXT";

    beforeCommand(fnName, _api.glGetLocalConstantIntegerv);
    _api.glGetLocalConstantIntegerv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetVariantBooleanvEXT().
void EXTVertexShaderAPI::getVariantBooleanV(GLuint id, GetVariantValueEXT value,
                                            Boolean *data) const
{
    static const char *fnName = "glGetVariantBooleanvEXT";

    beforeCommand(fnName, _api.glGetVariantBooleanv);
    _api.glGetVariantBooleanv(id, toScalar(value), toScalarPtr(data));
    afterCommand(fnName);
}

// Calls glGetVariantFloatvEXT().
void EXTVertexShaderAPI::getVariantFloatV(GLuint id, GetVariantValueEXT value,
                                          GLfloat *data) const
{
    static const char *fnName = "glGetVariantFloatvEXT";

    beforeCommand(fnName, _api.glGetVariantFloatv);
    _api.glGetVariantFloatv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetVariantIntegervEXT().
void EXTVertexShaderAPI::getVariantIntegerV(GLuint id, GetVariantValueEXT value,
                                            GLint *data) const
{
    static const char *fnName = "glGetVariantIntegervEXT";

    beforeCommand(fnName, _api.glGetVariantIntegerv);
    _api.glGetVariantIntegerv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glGetVariantPointervEXT().
void EXTVertexShaderAPI::getVariantPointerV(GLuint id, GetVariantValueEXT value,
                                            void **data) const
{
    static const char *fnName = "glGetVariantPointervEXT";

    beforeCommand(fnName, _api.glGetVariantPointerv);
    _api.glGetVariantPointerv(id, toScalar(value), data);
    afterCommand(fnName);
}

// Calls glInsertComponentEXT().
void EXTVertexShaderAPI::insertComponent(GLuint res, GLuint src, GLuint num) const
{
    static const char *fnName = "glInsertComponentEXT";

    beforeCommand(fnName, _api.glInsertComponent);
    _api.glInsertComponent(res, src, num);
    afterCommand(fnName);
}

// Calls glIsVariantEnabledEXT().
Boolean EXTVertexShaderAPI::isVariantEnabled(GLuint id, VariantCapEXT cap) const
{
    static const char *fnName = "glIsVariantEnabledEXT";

    beforeCommand(fnName, _api.glIsVariantEnabled);
    GLboolean result = _api.glIsVariantEnabled(id, toScalar(cap));
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glSetInvariantEXT().
void EXTVertexShaderAPI::setInvariant(GLuint id, ScalarType type,
                                      const void *addr) const
{
    static const char *fnName = "glSetInvariantEXT";

    beforeCommand(fnName, _api.glSetInvariant);
    _api.glSetInvariant(id, toScalar(type), addr);
    afterCommand(fnName);
}

// Calls glSetLocalConstantEXT().
void EXTVertexShaderAPI::setLocalConstant(GLuint id, ScalarType type,
                                          const void *addr) const
{
    static const char *fnName = "glSetLocalConstantEXT";

    beforeCommand(fnName, _api.glSetLocalConstant);
    _api.glSetLocalConstant(id, toScalar(type), addr);
    afterCommand(fnName);
}

// Calls glShaderOp1EXT().
void EXTVertexShaderAPI::shaderOp1(VertexShaderOpEXT op, GLuint res, GLuint arg1) const
{
    static const char *fnName = "glShaderOp1EXT";

    beforeCommand(fnName, _api.glShaderOp1);
    _api.glShaderOp1(toScalar(op), res, arg1);
    afterCommand(fnName);
}

// Calls glShaderOp2EXT().
void EXTVertexShaderAPI::shaderOp2(VertexShaderOpEXT op, GLuint res, GLuint arg1,
                                   GLuint arg2) const
{
    static const char *fnName = "glShaderOp2EXT";

    beforeCommand(fnName, _api.glShaderOp2);
    _api.glShaderOp2(toScalar(op), res, arg1, arg2);
    afterCommand(fnName);
}

// Calls glShaderOp3EXT().
void EXTVertexShaderAPI::shaderOp3(VertexShaderOpEXT op, GLuint res, GLuint arg1,
                                   GLuint arg2, GLuint arg3) const
{
    static const char *fnName = "glShaderOp3EXT";

    beforeCommand(fnName, _api.glShaderOp3);
    _api.glShaderOp3(toScalar(op), res, arg1, arg2, arg3);
    afterCommand(fnName);
}

// Calls glSwizzleEXT().
void EXTVertexShaderAPI::swizzle(GLuint res, GLuint in,
                                 VertexShaderCoordOutEXT outX,
                                 VertexShaderCoordOutEXT outY,
                                 VertexShaderCoordOutEXT outZ,
                                 VertexShaderCoordOutEXT outW) const
{
    static const char *fnName = "glSwizzleEXT";

    beforeCommand(fnName, _api.glSwizzle);
    _api.glSwizzle(res, in, toScalar(outX), toScalar(outY), toScalar(outZ),
                   toScalar(outW));
    afterCommand(fnName);
}

// Calls glVariantPointerEXT().
void EXTVertexShaderAPI::variantPointer(GLuint id, ScalarType type,
                                        GLuint stride, const void *addr) const
{
    static const char *fnName = "glVariantPointerEXT";

    beforeCommand(fnName, _api.glVariantPointer);
    _api.glVariantPointer(id, toScalar(type), stride, addr);
    afterCommand(fnName);
}

// Calls glVariantbvEXT().
void EXTVertexShaderAPI::variantBV(GLuint id, const GLbyte *addr) const
{
    static const char *fnName = "glVariantbvEXT";

    beforeCommand(fnName, _api.glVariantbv);
    _api.glVariantbv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantdvEXT().
void EXTVertexShaderAPI::variantDV(GLuint id, const GLdouble *addr) const
{
    static const char *fnName = "glVariantdvEXT";

    beforeCommand(fnName, _api.glVariantdv);
    _api.glVariantdv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantfvEXT().
void EXTVertexShaderAPI::variantFV(GLuint id, const GLfloat *addr) const
{
    static const char *fnName = "glVariantfvEXT";

    beforeCommand(fnName, _api.glVariantfv);
    _api.glVariantfv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantivEXT().
void EXTVertexShaderAPI::variantIV(GLuint id, const GLint *addr) const
{
    static const char *fnName = "glVariantivEXT";

    beforeCommand(fnName, _api.glVariantiv);
    _api.glVariantiv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantsvEXT().
void EXTVertexShaderAPI::variantSV(GLuint id, const GLshort *addr) const
{
    static const char *fnName = "glVariantsvEXT";

    beforeCommand(fnName, _api.glVariantsv);
    _api.glVariantsv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantubvEXT().
void EXTVertexShaderAPI::variantUBV(GLuint id, const GLubyte *addr) const
{
    static const char *fnName = "glVariantubvEXT";

    beforeCommand(fnName, _api.glVariantubv);
    _api.glVariantubv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantuivEXT().
void EXTVertexShaderAPI::variantUIV(GLuint id, const GLuint *addr) const
{
    static const char *fnName = "glVariantuivEXT";

    beforeCommand(fnName, _api.glVariantuiv);
    _api.glVariantuiv(id, addr);
    afterCommand(fnName);
}

// Calls glVariantusvEXT().
void EXTVertexShaderAPI::variantUSV(GLuint id, const GLushort *addr) const
{
    static const char *fnName = "glVariantusvEXT";

    beforeCommand(fnName, _api.glVariantusv);
    _api.glVariantusv(id, addr);
    afterCommand(fnName);
}

// Calls glWriteMaskEXT().
void EXTVertexShaderAPI::writeMask(GLuint res, GLuint in,
                                   VertexShaderWriteMaskEXT outX,
                                   VertexShaderWriteMaskEXT outY,
                                   VertexShaderWriteMaskEXT outZ,
                                   VertexShaderWriteMaskEXT outW) const
{
    static const char *fnName = "glWriteMaskEXT";

    beforeCommand(fnName, _api.glWriteMask);
    _api.glWriteMask(res, in, toScalar(outX), toScalar(outY), toScalar(outZ),
                     toScalar(outW));
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTVertexWeightingAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_vertex_weighting extension.
EXTVertexWeightingAPI::EXTVertexWeightingAPI() :
    BaseExtension("GL_EXT_vertex_weighting")
{
}

// Grant read-only access to the underlying function pointers.
const EXTVertexWeighting &EXTVertexWeightingAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_vertex_weighting entry points.
void EXTVertexWeightingAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glVertexWeightPointerEXT().
void EXTVertexWeightingAPI::vertexWeightPointer(GLint size,
                                                VertexWeightPointerTypeEXT type,
                                                GLsizei stride,
                                                const void *pointer) const
{
    static const char *fnName = "glVertexWeightPointerEXT";

    beforeCommand(fnName, _api.glVertexWeightPointer);
    _api.glVertexWeightPointer(size, toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glVertexWeightfEXT().
void EXTVertexWeightingAPI::vertexWeightF(GLfloat weight) const
{
    static const char *fnName = "glVertexWeightfEXT";

    beforeCommand(fnName, _api.glVertexWeightf);
    _api.glVertexWeightf(weight);
    afterCommand(fnName);
}

// Calls glVertexWeightfvEXT().
void EXTVertexWeightingAPI::vertexWeightFV(const GLfloat *weight) const
{
    static const char *fnName = "glVertexWeightfvEXT";

    beforeCommand(fnName, _api.glVertexWeightfv);
    _api.glVertexWeightfv(weight);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTWIN32KeyedMutexAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_win32_keyed_mutex extension.
EXTWIN32KeyedMutexAPI::EXTWIN32KeyedMutexAPI() :
    BaseExtension("GL_EXT_win32_keyed_mutex")
{
}

// Grant read-only access to the underlying function pointers.
const EXTWIN32KeyedMutex &EXTWIN32KeyedMutexAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_win32_keyed_mutex entry points.
void EXTWIN32KeyedMutexAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glAcquireKeyedMutexWin32EXT().
Boolean EXTWIN32KeyedMutexAPI::acquireKeyedMutexWIN32(GLuint memory,
                                                      GLuint64 key,
                                                      GLuint timeout) const
{
    static const char *fnName = "glAcquireKeyedMutexWin32EXT";

    beforeCommand(fnName, _api.glAcquireKeyedMutexWin32);
    GLboolean result = _api.glAcquireKeyedMutexWin32(memory, key, timeout);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

// Calls glReleaseKeyedMutexWin32EXT().
Boolean EXTWIN32KeyedMutexAPI::releaseKeyedMutexWIN32(GLuint memory,
                                                      GLuint64 key) const
{
    static const char *fnName = "glReleaseKeyedMutexWin32EXT";

    beforeCommand(fnName, _api.glReleaseKeyedMutexWin32);
    GLboolean result = _api.glReleaseKeyedMutexWin32(memory, key);
    afterCommand(fnName);

    return static_cast<Boolean>(result);
}

////////////////////////////////////////////////////////////////////////////////
// EXTWindowRectanglesAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_window_rectangles extension.
EXTWindowRectanglesAPI::EXTWindowRectanglesAPI() :
    BaseExtension("GL_EXT_window_rectangles")
{
}

// Grant read-only access to the underlying function pointers.
const EXTWindowRectangles &EXTWindowRectanglesAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_window_rectangles entry points.
void EXTWindowRectanglesAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glWindowRectanglesEXT().
void EXTWindowRectanglesAPI::windowRectangles(GLenum mode, GLsizei count,
                                              const GLint *box) const
{
    static const char *fnName = "glWindowRectanglesEXT";

    beforeCommand(fnName, _api.glWindowRectangles);
    _api.glWindowRectangles(mode, count, box);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTX11SyncObjectAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_EXT_x11_sync_object extension.
EXTX11SyncObjectAPI::EXTX11SyncObjectAPI() :
    BaseExtension("GL_EXT_x11_sync_object")
{
}

// Grant read-only access to the underlying function pointers.
const EXTX11SyncObject &EXTX11SyncObjectAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_EXT_x11_sync_object entry points.
void EXTX11SyncObjectAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glImportSyncEXT().
SyncName EXTX11SyncObjectAPI::importSync(GLenum external_sync_type,
                                         GLintptr external_sync,
                                         GLbitfield flags) const
{
    static const char *fnName = "glImportSyncEXT";

    beforeCommand(fnName, _api.glImportSync);
    GLsync result = _api.glImportSync(external_sync_type, external_sync, flags);
    afterCommand(fnName);

    return SyncName(result);
}

} // namespace gl

#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// EXTDisplayColorTableAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_display_color_table extension.
EXTDisplayColorTableAPI::EXTDisplayColorTableAPI() :
    BaseExtension("WGL_EXT_display_color_table")
{
}

// Grant read-only access to the underlying function pointers.
const EXTDisplayColorTable &EXTDisplayColorTableAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_display_color_table entry points.
void EXTDisplayColorTableAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBindDisplayColorTableEXT().
GLboolean EXTDisplayColorTableAPI::bindDisplayColorTable(GLushort id) const
{
    static const char *fnName = "wglBindDisplayColorTableEXT";

    beforeCommand(fnName, _api.wglBindDisplayColorTable);
    GLboolean result = _api.wglBindDisplayColorTable(id);
    afterCommand(fnName);

    return result;
}

// Calls wglCreateDisplayColorTableEXT().
GLboolean EXTDisplayColorTableAPI::createDisplayColorTable(GLushort id) const
{
    static const char *fnName = "wglCreateDisplayColorTableEXT";

    beforeCommand(fnName, _api.wglCreateDisplayColorTable);
    GLboolean result = _api.wglCreateDisplayColorTable(id);
    afterCommand(fnName);

    return result;
}

// Calls wglDestroyDisplayColorTableEXT().
VOID EXTDisplayColorTableAPI::destroyDisplayColorTable(GLushort id) const
{
    static const char *fnName = "wglDestroyDisplayColorTableEXT";

    beforeCommand(fnName, _api.wglDestroyDisplayColorTable);
    _api.wglDestroyDisplayColorTable(id);
    afterCommand(fnName);
}

// Calls wglLoadDisplayColorTableEXT().
GLboolean EXTDisplayColorTableAPI::loadDisplayColorTable(const GLushort *table,
                                                         GLuint length) const
{
    static const char *fnName = "wglLoadDisplayColorTableEXT";

    beforeCommand(fnName, _api.wglLoadDisplayColorTable);
    GLboolean result = _api.wglLoadDisplayColorTable(table, length);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTExtensionsStringAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_extensions_string extension.
EXTExtensionsStringAPI::EXTExtensionsStringAPI() :
    BaseExtension("WGL_EXT_extensions_string")
{
}

// Grant read-only access to the underlying function pointers.
const EXTExtensionsString &EXTExtensionsStringAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_extensions_string entry points.
void EXTExtensionsStringAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetExtensionsStringEXT().
const char *EXTExtensionsStringAPI::getExtensionsString() const
{
    static const char *fnName = "wglGetExtensionsStringEXT";

    beforeCommand(fnName, _api.wglGetExtensionsString);
    const char *result = _api.wglGetExtensionsString();
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTMakeCurrentReadAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_make_current_read extension.
EXTMakeCurrentReadAPI::EXTMakeCurrentReadAPI() :
    BaseExtension("WGL_EXT_make_current_read")
{
}

// Grant read-only access to the underlying function pointers.
const EXTMakeCurrentRead &EXTMakeCurrentReadAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_make_current_read entry points.
void EXTMakeCurrentReadAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetCurrentReadDCEXT().
HDC EXTMakeCurrentReadAPI::getCurrentReadDC() const
{
    static const char *fnName = "wglGetCurrentReadDCEXT";

    beforeCommand(fnName, _api.wglGetCurrentReadDC);
    HDC result = _api.wglGetCurrentReadDC();
    afterCommand(fnName);

    return result;
}

// Calls wglMakeContextCurrentEXT().
BOOL EXTMakeCurrentReadAPI::makeContextCurrent(HDC hDrawDC, HDC hReadDC,
                                               HGLRC hglrc) const
{
    static const char *fnName = "wglMakeContextCurrentEXT";

    beforeCommand(fnName, _api.wglMakeContextCurrent);
    BOOL result = _api.wglMakeContextCurrent(hDrawDC, hReadDC, hglrc);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTPbufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_pbuffer extension.
EXTPbufferAPI::EXTPbufferAPI() :
    BaseExtension("WGL_EXT_pbuffer")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPbuffer &EXTPbufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_pbuffer entry points.
void EXTPbufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglCreatePbufferEXT().
HPBUFFEREXT EXTPbufferAPI::createPbuffer(HDC hDC, int iPixelFormat, int iWidth,
                                         int iHeight, const int *piAttribList) const
{
    static const char *fnName = "wglCreatePbufferEXT";

    beforeCommand(fnName, _api.wglCreatePbuffer);
    HPBUFFEREXT result = _api.wglCreatePbuffer(hDC, iPixelFormat, iWidth,
                                               iHeight, piAttribList);
    afterCommand(fnName);

    return result;
}

// Calls wglDestroyPbufferEXT().
BOOL EXTPbufferAPI::destroyPbuffer(HPBUFFEREXT hPbuffer) const
{
    static const char *fnName = "wglDestroyPbufferEXT";

    beforeCommand(fnName, _api.wglDestroyPbuffer);
    BOOL result = _api.wglDestroyPbuffer(hPbuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPbufferDCEXT().
HDC EXTPbufferAPI::getPbufferDC(HPBUFFEREXT hPbuffer) const
{
    static const char *fnName = "wglGetPbufferDCEXT";

    beforeCommand(fnName, _api.wglGetPbufferDC);
    HDC result = _api.wglGetPbufferDC(hPbuffer);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryPbufferEXT().
BOOL EXTPbufferAPI::queryPbuffer(HPBUFFEREXT hPbuffer, int iAttribute,
                                 int *piValue) const
{
    static const char *fnName = "wglQueryPbufferEXT";

    beforeCommand(fnName, _api.wglQueryPbuffer);
    BOOL result = _api.wglQueryPbuffer(hPbuffer, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

// Calls wglReleasePbufferDCEXT().
int EXTPbufferAPI::releasePbufferDC(HPBUFFEREXT hPbuffer, HDC hDC) const
{
    static const char *fnName = "wglReleasePbufferDCEXT";

    beforeCommand(fnName, _api.wglReleasePbufferDC);
    int result = _api.wglReleasePbufferDC(hPbuffer, hDC);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTPixelFormatAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_pixel_format extension.
EXTPixelFormatAPI::EXTPixelFormatAPI() :
    BaseExtension("WGL_EXT_pixel_format")
{
}

// Grant read-only access to the underlying function pointers.
const EXTPixelFormat &EXTPixelFormatAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_pixel_format entry points.
void EXTPixelFormatAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglChoosePixelFormatEXT().
BOOL EXTPixelFormatAPI::choosePixelFormat(HDC hdc, const int *piAttribIList,
                                          const FLOAT *pfAttribFList,
                                          UINT nMaxFormats, int *piFormats,
                                          UINT *nNumFormats) const
{
    static const char *fnName = "wglChoosePixelFormatEXT";

    beforeCommand(fnName, _api.wglChoosePixelFormat);
    BOOL result = _api.wglChoosePixelFormat(hdc, piAttribIList, pfAttribFList,
                                            nMaxFormats, piFormats, nNumFormats);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPixelFormatAttribfvEXT().
BOOL EXTPixelFormatAPI::getPixelFormatAttribFV(HDC hdc, int iPixelFormat,
                                               int iLayerPlane, UINT nAttributes,
                                               int *piAttributes,
                                               FLOAT *pfValues) const
{
    static const char *fnName = "wglGetPixelFormatAttribfvEXT";

    beforeCommand(fnName, _api.wglGetPixelFormatAttribfv);
    BOOL result = _api.wglGetPixelFormatAttribfv(hdc, iPixelFormat, iLayerPlane,
                                                 nAttributes, piAttributes,
                                                 pfValues);
    afterCommand(fnName);

    return result;
}

// Calls wglGetPixelFormatAttribivEXT().
BOOL EXTPixelFormatAPI::getPixelFormatAttribIV(HDC hdc, int iPixelFormat,
                                               int iLayerPlane, UINT nAttributes,
                                               int *piAttributes, int *piValues) const
{
    static const char *fnName = "wglGetPixelFormatAttribivEXT";

    beforeCommand(fnName, _api.wglGetPixelFormatAttribiv);
    BOOL result = _api.wglGetPixelFormatAttribiv(hdc, iPixelFormat, iLayerPlane,
                                                 nAttributes, piAttributes,
                                                 piValues);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTSwapControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_EXT_swap_control extension.
EXTSwapControlAPI::EXTSwapControlAPI() :
    BaseExtension("WGL_EXT_swap_control")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSwapControl &EXTSwapControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_EXT_swap_control entry points.
void EXTSwapControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetSwapIntervalEXT().
int EXTSwapControlAPI::getSwapInterval() const
{
    static const char *fnName = "wglGetSwapIntervalEXT";

    beforeCommand(fnName, _api.wglGetSwapInterval);
    int result = _api.wglGetSwapInterval();
    afterCommand(fnName);

    return result;
}

// Calls wglSwapIntervalEXT().
BOOL EXTSwapControlAPI::swapInterval(int interval) const
{
    static const char *fnName = "wglSwapIntervalEXT";

    beforeCommand(fnName, _api.wglSwapInterval);
    BOOL result = _api.wglSwapInterval(interval);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// EXTImportContextAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_EXT_import_context extension.
EXTImportContextAPI::EXTImportContextAPI() :
    BaseExtension("GLX_EXT_import_context")
{
}

// Grant read-only access to the underlying function pointers.
const EXTImportContext &EXTImportContextAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_EXT_import_context entry points.
void EXTImportContextAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXFreeContextEXT().
void EXTImportContextAPI::xFreeContext(Display *dpy, GLXContext context) const
{
    static const char *fnName = "glXFreeContextEXT";

    beforeCommand(fnName, _api.glXFreeContext);
    _api.glXFreeContext(dpy, context);
    afterCommand(fnName);
}

// Calls glXGetContextIDEXT().
GLXContextID EXTImportContextAPI::xGetContextId(const GLXContext context) const
{
    static const char *fnName = "glXGetContextIDEXT";

    beforeCommand(fnName, _api.glXGetContextID);
    GLXContextID result = _api.glXGetContextID(context);
    afterCommand(fnName);

    return result;
}

// Calls glXGetCurrentDisplayEXT().
Display *EXTImportContextAPI::xGetCurrentDisplay() const
{
    static const char *fnName = "glXGetCurrentDisplayEXT";

    beforeCommand(fnName, _api.glXGetCurrentDisplay);
    Display *result = _api.glXGetCurrentDisplay();
    afterCommand(fnName);

    return result;
}

// Calls glXImportContextEXT().
GLXContext EXTImportContextAPI::xImportContext(Display *dpy,
                                               GLXContextID contextID) const
{
    static const char *fnName = "glXImportContextEXT";

    beforeCommand(fnName, _api.glXImportContext);
    GLXContext result = _api.glXImportContext(dpy, contextID);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryContextInfoEXT().
int EXTImportContextAPI::xQueryContextInfo(Display *dpy, GLXContext context,
                                           int attribute, int *value) const
{
    static const char *fnName = "glXQueryContextInfoEXT";

    beforeCommand(fnName, _api.glXQueryContextInfo);
    int result = _api.glXQueryContextInfo(dpy, context, attribute, value);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// EXTSwapControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_EXT_swap_control extension.
EXTSwapControlAPI::EXTSwapControlAPI() :
    BaseExtension("GLX_EXT_swap_control")
{
}

// Grant read-only access to the underlying function pointers.
const EXTSwapControl &EXTSwapControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_EXT_swap_control entry points.
void EXTSwapControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXSwapIntervalEXT().
void EXTSwapControlAPI::xSwapInterval(Display *dpy, GLXDrawable drawable,
                                      int interval) const
{
    static const char *fnName = "glXSwapIntervalEXT";

    beforeCommand(fnName, _api.glXSwapInterval);
    _api.glXSwapInterval(dpy, drawable, interval);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// EXTTextureFromPixmapAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_EXT_texture_from_pixmap extension.
EXTTextureFromPixmapAPI::EXTTextureFromPixmapAPI() :
    BaseExtension("GLX_EXT_texture_from_pixmap")
{
}

// Grant read-only access to the underlying function pointers.
const EXTTextureFromPixmap &EXTTextureFromPixmapAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_EXT_texture_from_pixmap entry points.
void EXTTextureFromPixmapAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXBindTexImageEXT().
void EXTTextureFromPixmapAPI::xBindTexImage(Display *dpy, GLXDrawable drawable,
                                            int buffer, const int *attrib_list) const
{
    static const char *fnName = "glXBindTexImageEXT";

    beforeCommand(fnName, _api.glXBindTexImage);
    _api.glXBindTexImage(dpy, drawable, buffer, attrib_list);
    afterCommand(fnName);
}

// Calls glXReleaseTexImageEXT().
void EXTTextureFromPixmapAPI::xReleaseTexImage(Display *dpy,
                                               GLXDrawable drawable, int buffer) const
{
    static const char *fnName = "glXReleaseTexImageEXT";

    beforeCommand(fnName, _api.glXReleaseTexImage);
    _api.glXReleaseTexImage(dpy, drawable, buffer);
    afterCommand(fnName);
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

