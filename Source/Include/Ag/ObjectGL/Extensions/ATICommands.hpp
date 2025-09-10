//! @file Ag/ObjectGL/Extensions/ATICommands.hpp
//! @brief The declaration of ATI-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_ATI_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_ATI_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "ATI.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_ATI_draw_buffers extension API.
class ATIDrawBuffersAPI : public BaseExtension
{
public:
    // Construction
    ATIDrawBuffersAPI();

    // Accessors
    const ATIDrawBuffers &getRawAPI() const;

    // Operations
    void drawBuffers(GLsizei n, const DrawBufferMode *bufs) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIDrawBuffers _api;
};

// Manages the entry points for the GL_ATI_element_array extension API.
class ATIElementArrayAPI : public BaseExtension
{
public:
    // Construction
    ATIElementArrayAPI();

    // Accessors
    const ATIElementArray &getRawAPI() const;

    // Operations
    void drawElementArray(PrimitiveType mode, GLsizei count) const;
    void drawRangeElementArray(PrimitiveType mode, GLuint start, GLuint end,
                               GLsizei count) const;
    void elementPointer(ElementPointerTypeATI type, const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIElementArray _api;
};

// Manages the entry points for the GL_ATI_envmap_bumpmap extension API.
class ATIEnvmapBumpmapAPI : public BaseExtension
{
public:
    // Construction
    ATIEnvmapBumpmapAPI();

    // Accessors
    const ATIEnvmapBumpmap &getRawAPI() const;

    // Operations
    void getTexBumpParameterFV(GetTexBumpParameterATI pname, GLfloat *param) const;
    void getTexBumpParameterIV(GetTexBumpParameterATI pname, GLint *param) const;
    void texBumpParameterFV(TexBumpParameterATI pname, const GLfloat *param) const;
    void texBumpParameterIV(TexBumpParameterATI pname, const GLint *param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIEnvmapBumpmap _api;
};

// Manages the entry points for the GL_ATI_fragment_shader extension API.
class ATIFragmentShaderAPI : public BaseExtension
{
public:
    // Construction
    ATIFragmentShaderAPI();

    // Accessors
    const ATIFragmentShader &getRawAPI() const;

    // Operations
    void alphaFragmentOp1(FragmentOpATI op, GLuint dst, GLuint dstMod,
                          GLuint arg1, GLuint arg1Rep, GLuint arg1Mod) const;
    void alphaFragmentOp2(FragmentOpATI op, GLuint dst, GLuint dstMod,
                          GLuint arg1, GLuint arg1Rep, GLuint arg1Mod,
                          GLuint arg2, GLuint arg2Rep, GLuint arg2Mod) const;
    void alphaFragmentOp3(FragmentOpATI op, GLuint dst, GLuint dstMod,
                          GLuint arg1, GLuint arg1Rep, GLuint arg1Mod,
                          GLuint arg2, GLuint arg2Rep, GLuint arg2Mod,
                          GLuint arg3, GLuint arg3Rep, GLuint arg3Mod) const;
    void beginFragmentShader() const;
    void bindFragmentShader(GLuint id) const;
    void colorFragmentOp1(FragmentOpATI op, GLuint dst, GLuint dstMask,
                          GLuint dstMod, GLuint arg1, GLuint arg1Rep,
                          GLuint arg1Mod) const;
    void colorFragmentOp2(FragmentOpATI op, GLuint dst, GLuint dstMask,
                          GLuint dstMod, GLuint arg1, GLuint arg1Rep,
                          GLuint arg1Mod, GLuint arg2, GLuint arg2Rep,
                          GLuint arg2Mod) const;
    void colorFragmentOp3(FragmentOpATI op, GLuint dst, GLuint dstMask,
                          GLuint dstMod, GLuint arg1, GLuint arg1Rep,
                          GLuint arg1Mod, GLuint arg2, GLuint arg2Rep,
                          GLuint arg2Mod, GLuint arg3, GLuint arg3Rep,
                          GLuint arg3Mod) const;
    void deleteFragmentShader(GLuint id) const;
    void endFragmentShader() const;
    GLuint genFragmentShaders(GLuint range) const;
    void passTexCoord(GLuint dst, GLuint coord, SwizzleOpATI swizzle) const;
    void sampleMap(GLuint dst, GLuint interp, SwizzleOpATI swizzle) const;
    void setFragmentShaderConstant(GLuint dst, const GLfloat *value) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIFragmentShader _api;
};

// Manages the entry points for the GL_ATI_map_object_buffer extension API.
class ATIMapObjectBufferAPI : public BaseExtension
{
public:
    // Construction
    ATIMapObjectBufferAPI();

    // Accessors
    const ATIMapObjectBuffer &getRawAPI() const;

    // Operations
    void *mapObjectBuffer(BufferName buffer) const;
    void unmapObjectBuffer(BufferName buffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIMapObjectBuffer _api;
};

// Manages the entry points for the GL_ATI_pn_triangles extension API.
class ATIPnTrianglesAPI : public BaseExtension
{
public:
    // Construction
    ATIPnTrianglesAPI();

    // Accessors
    const ATIPnTriangles &getRawAPI() const;

    // Operations
    void pnTrianglesF(PNTrianglesPNameATI pname, GLfloat param) const;
    void pnTrianglesI(PNTrianglesPNameATI pname, GLint param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIPnTriangles _api;
};

// Manages the entry points for the GL_ATI_separate_stencil extension API.
class ATISeparateStencilAPI : public BaseExtension
{
public:
    // Construction
    ATISeparateStencilAPI();

    // Accessors
    const ATISeparateStencil &getRawAPI() const;

    // Operations
    void stencilFuncSeparate(StencilFunction frontfunc, StencilFunction backfunc,
                             GLint ref, GLuint mask) const;
    void stencilOpSeparate(StencilFaceDirection face, StencilOp sfail,
                           StencilOp dpfail, StencilOp dppass) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATISeparateStencil _api;
};

// Manages the entry points for the GL_ATI_vertex_array_object extension API.
class ATIVertexArrayObjectAPI : public BaseExtension
{
public:
    // Construction
    ATIVertexArrayObjectAPI();

    // Accessors
    const ATIVertexArrayObject &getRawAPI() const;

    // Operations
    void arrayObject(EnableCap array, GLint size, ScalarType type,
                     GLsizei stride, BufferName buffer, GLuint offset) const;
    void freeObjectBuffer(BufferName buffer) const;
    void getArrayObjectFV(EnableCap array, ArrayObjectPNameATI pname,
                          GLfloat *params) const;
    void getArrayObjectIV(EnableCap array, ArrayObjectPNameATI pname,
                          GLint *params) const;
    void getObjectBufferFV(BufferName buffer, ArrayObjectPNameATI pname,
                           GLfloat *params) const;
    void getObjectBufferIV(BufferName buffer, ArrayObjectPNameATI pname,
                           GLint *params) const;
    void getVariantArrayObjectFV(GLuint id, ArrayObjectPNameATI pname,
                                 GLfloat *params) const;
    void getVariantArrayObjectIV(GLuint id, ArrayObjectPNameATI pname,
                                 GLint *params) const;
    Boolean isObjectBuffer(BufferName buffer) const;
    GLuint newObjectBuffer(GLsizei size, const void *pointer,
                           ArrayObjectUsageATI usage) const;
    void updateObjectBuffer(BufferName buffer, GLuint offset, GLsizei size,
                            const void *pointer, PreserveModeATI preserve) const;
    void variantArrayObject(GLuint id, ScalarType type, GLsizei stride,
                            BufferName buffer, GLuint offset) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIVertexArrayObject _api;
};

// Manages the entry points for the GL_ATI_vertex_attrib_array_object extension API.
class ATIVertexAttribArrayObjectAPI : public BaseExtension
{
public:
    // Construction
    ATIVertexAttribArrayObjectAPI();

    // Accessors
    const ATIVertexAttribArrayObject &getRawAPI() const;

    // Operations
    void getVertexAttribArrayObjectFV(GLuint index, ArrayObjectPNameATI pname,
                                      GLfloat *params) const;
    void getVertexAttribArrayObjectIV(GLuint index, ArrayObjectPNameATI pname,
                                      GLint *params) const;
    void vertexAttribArrayObject(GLuint index, GLint size,
                                 VertexAttribPointerType type,
                                 Boolean normalized, GLsizei stride,
                                 BufferName buffer, GLuint offset) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIVertexAttribArrayObject _api;
};

// Manages the entry points for the GL_ATI_vertex_streams extension API.
class ATIVertexStreamsAPI : public BaseExtension
{
public:
    // Construction
    ATIVertexStreamsAPI();

    // Accessors
    const ATIVertexStreams &getRawAPI() const;

    // Operations
    void clientActiveVertexStream(VertexStreamATI stream) const;
    void normalStream3B(VertexStreamATI stream, GLbyte nx, GLbyte ny, GLbyte nz) const;
    void normalStream3BV(VertexStreamATI stream, const GLbyte *coords) const;
    void normalStream3D(VertexStreamATI stream, GLdouble nx, GLdouble ny,
                        GLdouble nz) const;
    void normalStream3DV(VertexStreamATI stream, const GLdouble *coords) const;
    void normalStream3F(VertexStreamATI stream, GLfloat nx, GLfloat ny,
                        GLfloat nz) const;
    void normalStream3FV(VertexStreamATI stream, const GLfloat *coords) const;
    void normalStream3I(VertexStreamATI stream, GLint nx, GLint ny, GLint nz) const;
    void normalStream3IV(VertexStreamATI stream, const GLint *coords) const;
    void normalStream3S(VertexStreamATI stream, GLshort nx, GLshort ny,
                        GLshort nz) const;
    void normalStream3SV(VertexStreamATI stream, const GLshort *coords) const;
    void vertexBlendEnvF(VertexStreamATI pname, GLfloat param) const;
    void vertexBlendEnvI(VertexStreamATI pname, GLint param) const;
    void vertexStream1D(VertexStreamATI stream, GLdouble x) const;
    void vertexStream1DV(VertexStreamATI stream, const GLdouble *coords) const;
    void vertexStream1F(VertexStreamATI stream, GLfloat x) const;
    void vertexStream1FV(VertexStreamATI stream, const GLfloat *coords) const;
    void vertexStream1I(VertexStreamATI stream, GLint x) const;
    void vertexStream1IV(VertexStreamATI stream, const GLint *coords) const;
    void vertexStream1S(VertexStreamATI stream, GLshort x) const;
    void vertexStream1SV(VertexStreamATI stream, const GLshort *coords) const;
    void vertexStream2D(VertexStreamATI stream, GLdouble x, GLdouble y) const;
    void vertexStream2DV(VertexStreamATI stream, const GLdouble *coords) const;
    void vertexStream2F(VertexStreamATI stream, GLfloat x, GLfloat y) const;
    void vertexStream2FV(VertexStreamATI stream, const GLfloat *coords) const;
    void vertexStream2I(VertexStreamATI stream, GLint x, GLint y) const;
    void vertexStream2IV(VertexStreamATI stream, const GLint *coords) const;
    void vertexStream2S(VertexStreamATI stream, GLshort x, GLshort y) const;
    void vertexStream2SV(VertexStreamATI stream, const GLshort *coords) const;
    void vertexStream3D(VertexStreamATI stream, GLdouble x, GLdouble y,
                        GLdouble z) const;
    void vertexStream3DV(VertexStreamATI stream, const GLdouble *coords) const;
    void vertexStream3F(VertexStreamATI stream, GLfloat x, GLfloat y, GLfloat z) const;
    void vertexStream3FV(VertexStreamATI stream, const GLfloat *coords) const;
    void vertexStream3I(VertexStreamATI stream, GLint x, GLint y, GLint z) const;
    void vertexStream3IV(VertexStreamATI stream, const GLint *coords) const;
    void vertexStream3S(VertexStreamATI stream, GLshort x, GLshort y, GLshort z) const;
    void vertexStream3SV(VertexStreamATI stream, const GLshort *coords) const;
    void vertexStream4D(VertexStreamATI stream, GLdouble x, GLdouble y,
                        GLdouble z, GLdouble w) const;
    void vertexStream4DV(VertexStreamATI stream, const GLdouble *coords) const;
    void vertexStream4F(VertexStreamATI stream, GLfloat x, GLfloat y, GLfloat z,
                        GLfloat w) const;
    void vertexStream4FV(VertexStreamATI stream, const GLfloat *coords) const;
    void vertexStream4I(VertexStreamATI stream, GLint x, GLint y, GLint z,
                        GLint w) const;
    void vertexStream4IV(VertexStreamATI stream, const GLint *coords) const;
    void vertexStream4S(VertexStreamATI stream, GLshort x, GLshort y, GLshort z,
                        GLshort w) const;
    void vertexStream4SV(VertexStreamATI stream, const GLshort *coords) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    ATIVertexStreams _api;
};


} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
