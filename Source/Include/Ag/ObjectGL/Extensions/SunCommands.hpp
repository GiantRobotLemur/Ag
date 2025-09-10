//! @file Ag/ObjectGL/Extensions/SunCommands.hpp
//! @brief The declaration of Sun Microsystems-specific extensions to the
//! OpenGL Command set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_SUN_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_SUN_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "Sun.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_SUNX_constant_data extension API.
class SUNXConstantDataAPI : public BaseExtension
{
public:
    // Construction
    SUNXConstantDataAPI();

    // Accessors
    const SUNXConstantData &getRawAPI() const;

    // Operations
    void finishTexture() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNXConstantData _api;
};

// Manages the entry points for the GL_SUN_global_alpha extension API.
class SUNGlobalAlphaAPI : public BaseExtension
{
public:
    // Construction
    SUNGlobalAlphaAPI();

    // Accessors
    const SUNGlobalAlpha &getRawAPI() const;

    // Operations
    void globalAlphaFactorB(GLbyte factor) const;
    void globalAlphaFactorD(GLdouble factor) const;
    void globalAlphaFactorF(GLfloat factor) const;
    void globalAlphaFactorI(GLint factor) const;
    void globalAlphaFactors(GLshort factor) const;
    void globalAlphaFactorUB(GLubyte factor) const;
    void globalAlphaFactorUI(GLuint factor) const;
    void globalAlphaFactorUS(GLushort factor) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNGlobalAlpha _api;
};

// Manages the entry points for the GL_SUN_mesh_array extension API.
class SUNMeshArrayAPI : public BaseExtension
{
public:
    // Construction
    SUNMeshArrayAPI();

    // Accessors
    const SUNMeshArray &getRawAPI() const;

    // Operations
    void drawMeshArrays(PrimitiveType mode, GLint first, GLsizei count,
                        GLsizei width) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNMeshArray _api;
};

// Manages the entry points for the GL_SUN_triangle_list extension API.
class SUNTriangleListAPI : public BaseExtension
{
public:
    // Construction
    SUNTriangleListAPI();

    // Accessors
    const SUNTriangleList &getRawAPI() const;

    // Operations
    void replacementCodePointer(ReplacementCodeTypeSUN type, GLsizei stride,
                                const void **pointer) const;
    void replacementCodeUB(GLubyte code) const;
    void replacementCodeUBV(const GLubyte *code) const;
    void replacementCodeUI(GLuint code) const;
    void replacementCodeUIV(const GLuint *code) const;
    void replacementCodeUS(GLushort code) const;
    void replacementCodeUSV(const GLushort *code) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNTriangleList _api;
};

// Manages the entry points for the GL_SUN_vertex extension API.
class SUNVertexAPI : public BaseExtension
{
public:
    // Construction
    SUNVertexAPI();

    // Accessors
    const SUNVertex &getRawAPI() const;

    // Operations
    void color3FVertex3F(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y,
                         GLfloat z) const;
    void color3FVertex3FV(const GLfloat *c, const GLfloat *v) const;
    void color4FNormal3FVertex3F(GLfloat r, GLfloat g, GLfloat b, GLfloat a,
                                 GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x,
                                 GLfloat y, GLfloat z) const;
    void color4FNormal3FVertex3FV(const GLfloat *c, const GLfloat *n,
                                  const GLfloat *v) const;
    void color4UBVertex2F(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x,
                          GLfloat y) const;
    void color4UBVertex2FV(const GLubyte *c, const GLfloat *v) const;
    void color4UBVertex3F(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x,
                          GLfloat y, GLfloat z) const;
    void color4UBVertex3FV(const GLubyte *c, const GLfloat *v) const;
    void normal3FVertex3F(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x,
                          GLfloat y, GLfloat z) const;
    void normal3FVertex3FV(const GLfloat *n, const GLfloat *v) const;
    void replacementCodeUIColor3FVertex3F(GLuint rc, GLfloat r, GLfloat g,
                                          GLfloat b, GLfloat x, GLfloat y,
                                          GLfloat z) const;
    void replacementCodeUIColor3FVertex3FV(const GLuint *rc, const GLfloat *c,
                                           const GLfloat *v) const;
    void replacementCodeUIColor4FNormal3FVertex3F(GLuint rc, GLfloat r,
                                                  GLfloat g, GLfloat b,
                                                  GLfloat a, GLfloat nx,
                                                  GLfloat ny, GLfloat nz,
                                                  GLfloat x, GLfloat y,
                                                  GLfloat z) const;
    void replacementCodeUIColor4FNormal3FVertex3FV(const GLuint *rc,
                                                   const GLfloat *c,
                                                   const GLfloat *n,
                                                   const GLfloat *v) const;
    void replacementCodeUIColor4UBVertex3F(GLuint rc, GLubyte r, GLubyte g,
                                           GLubyte b, GLubyte a, GLfloat x,
                                           GLfloat y, GLfloat z) const;
    void replacementCodeUIColor4UBVertex3FV(const GLuint *rc, const GLubyte *c,
                                            const GLfloat *v) const;
    void replacementCodeUINormal3FVertex3F(GLuint rc, GLfloat nx, GLfloat ny,
                                           GLfloat nz, GLfloat x, GLfloat y,
                                           GLfloat z) const;
    void replacementCodeUINormal3FVertex3FV(const GLuint *rc, const GLfloat *n,
                                            const GLfloat *v) const;
    void replacementCodeUITexCoord2FColor4FNormal3FVertex3F(GLuint rc, GLfloat s,
                                                            GLfloat t, GLfloat r,
                                                            GLfloat g, GLfloat b,
                                                            GLfloat a,
                                                            GLfloat nx,
                                                            GLfloat ny,
                                                            GLfloat nz,
                                                            GLfloat x, GLfloat y,
                                                            GLfloat z) const;
    void replacementCodeUITexCoord2FColor4FNormal3FVertex3FV(const GLuint *rc,
                                                             const GLfloat *tc,
                                                             const GLfloat *c,
                                                             const GLfloat *n,
                                                             const GLfloat *v) const;
    void replacementCodeUITexCoord2FNormal3FVertex3F(GLuint rc, GLfloat s,
                                                     GLfloat t, GLfloat nx,
                                                     GLfloat ny, GLfloat nz,
                                                     GLfloat x, GLfloat y,
                                                     GLfloat z) const;
    void replacementCodeUITexCoord2FNormal3FVertex3FV(const GLuint *rc,
                                                      const GLfloat *tc,
                                                      const GLfloat *n,
                                                      const GLfloat *v) const;
    void replacementCodeUITexCoord2FVertex3F(GLuint rc, GLfloat s, GLfloat t,
                                             GLfloat x, GLfloat y, GLfloat z) const;
    void replacementCodeUITexCoord2FVertex3FV(const GLuint *rc,
                                              const GLfloat *tc,
                                              const GLfloat *v) const;
    void replacementCodeUIVertex3F(GLuint rc, GLfloat x, GLfloat y, GLfloat z) const;
    void replacementCodeUIVertex3FV(const GLuint *rc, const GLfloat *v) const;
    void texCoord2FColor3FVertex3F(GLfloat s, GLfloat t, GLfloat r, GLfloat g,
                                   GLfloat b, GLfloat x, GLfloat y, GLfloat z) const;
    void texCoord2FColor3FVertex3FV(const GLfloat *tc, const GLfloat *c,
                                    const GLfloat *v) const;
    void texCoord2FColor4FNormal3FVertex3F(GLfloat s, GLfloat t, GLfloat r,
                                           GLfloat g, GLfloat b, GLfloat a,
                                           GLfloat nx, GLfloat ny, GLfloat nz,
                                           GLfloat x, GLfloat y, GLfloat z) const;
    void texCoord2FColor4FNormal3FVertex3FV(const GLfloat *tc, const GLfloat *c,
                                            const GLfloat *n, const GLfloat *v) const;
    void texCoord2FColor4UBVertex3F(GLfloat s, GLfloat t, GLubyte r, GLubyte g,
                                    GLubyte b, GLubyte a, GLfloat x, GLfloat y,
                                    GLfloat z) const;
    void texCoord2FColor4UBVertex3FV(const GLfloat *tc, const GLubyte *c,
                                     const GLfloat *v) const;
    void texCoord2FNormal3FVertex3F(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny,
                                    GLfloat nz, GLfloat x, GLfloat y, GLfloat z) const;
    void texCoord2FNormal3FVertex3FV(const GLfloat *tc, const GLfloat *n,
                                     const GLfloat *v) const;
    void texCoord2FVertex3F(GLfloat s, GLfloat t, GLfloat x, GLfloat y,
                            GLfloat z) const;
    void texCoord2FVertex3FV(const GLfloat *tc, const GLfloat *v) const;
    void texCoord4FColor4FNormal3FVertex4F(GLfloat s, GLfloat t, GLfloat p,
                                           GLfloat q, GLfloat r, GLfloat g,
                                           GLfloat b, GLfloat a, GLfloat nx,
                                           GLfloat ny, GLfloat nz, GLfloat x,
                                           GLfloat y, GLfloat z, GLfloat w) const;
    void texCoord4FColor4FNormal3FVertex4FV(const GLfloat *tc, const GLfloat *c,
                                            const GLfloat *n, const GLfloat *v) const;
    void texCoord4FVertex4F(GLfloat s, GLfloat t, GLfloat p, GLfloat q,
                            GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void texCoord4FVertex4FV(const GLfloat *tc, const GLfloat *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNVertex _api;
};

} // namespace gl


#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_SUN_get_transparent_index extension API.
class SUNGetTransparentIndexAPI : public gl::BaseExtension
{
public:
    // Construction
    SUNGetTransparentIndexAPI();

    // Accessors
    const SUNGetTransparentIndex &getRawAPI() const;

    // Operations
    Status xGetTransparentIndex(Display *dpy, Window overlay, Window underlay,
                                unsigned long *pTransparentIndex) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SUNGetTransparentIndex _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
