//! @file ObjectGL/Extensions/SunCommands.cpp
//! @brief The definition of Sun Microsystems-specific extensions to the
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

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/SunCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// SUNXConstantDataAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SUNX_constant_data extension.
SUNXConstantDataAPI::SUNXConstantDataAPI() :
    BaseExtension("GL_SUNX_constant_data")
{
}

// Grant read-only access to the underlying function pointers.
const SUNXConstantData &SUNXConstantDataAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SUNX_constant_data entry points.
void SUNXConstantDataAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFinishTextureSUNX().
void SUNXConstantDataAPI::finishTexture() const
{
    static const char *fnName = "glFinishTextureSUNX";

    beforeCommand(fnName, _api.glFinishTexture);
    _api.glFinishTexture();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SUNGlobalAlphaAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SUN_global_alpha extension.
SUNGlobalAlphaAPI::SUNGlobalAlphaAPI() :
    BaseExtension("GL_SUN_global_alpha")
{
}

// Grant read-only access to the underlying function pointers.
const SUNGlobalAlpha &SUNGlobalAlphaAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SUN_global_alpha entry points.
void SUNGlobalAlphaAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glGlobalAlphaFactorbSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorB(GLbyte factor) const
{
    static const char *fnName = "glGlobalAlphaFactorbSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactorb);
    _api.glGlobalAlphaFactorb(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactordSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorD(GLdouble factor) const
{
    static const char *fnName = "glGlobalAlphaFactordSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactord);
    _api.glGlobalAlphaFactord(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactorfSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorF(GLfloat factor) const
{
    static const char *fnName = "glGlobalAlphaFactorfSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactorf);
    _api.glGlobalAlphaFactorf(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactoriSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorI(GLint factor) const
{
    static const char *fnName = "glGlobalAlphaFactoriSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactori);
    _api.glGlobalAlphaFactori(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactorsSUN().
void SUNGlobalAlphaAPI::globalAlphaFactors(GLshort factor) const
{
    static const char *fnName = "glGlobalAlphaFactorsSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactors);
    _api.glGlobalAlphaFactors(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactorubSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorUB(GLubyte factor) const
{
    static const char *fnName = "glGlobalAlphaFactorubSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactorub);
    _api.glGlobalAlphaFactorub(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactoruiSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorUI(GLuint factor) const
{
    static const char *fnName = "glGlobalAlphaFactoruiSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactorui);
    _api.glGlobalAlphaFactorui(factor);
    afterCommand(fnName);
}

// Calls glGlobalAlphaFactorusSUN().
void SUNGlobalAlphaAPI::globalAlphaFactorUS(GLushort factor) const
{
    static const char *fnName = "glGlobalAlphaFactorusSUN";

    beforeCommand(fnName, _api.glGlobalAlphaFactorus);
    _api.glGlobalAlphaFactorus(factor);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SUNMeshArrayAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SUN_mesh_array extension.
SUNMeshArrayAPI::SUNMeshArrayAPI() :
    BaseExtension("GL_SUN_mesh_array")
{
}

// Grant read-only access to the underlying function pointers.
const SUNMeshArray &SUNMeshArrayAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SUN_mesh_array entry points.
void SUNMeshArrayAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glDrawMeshArraysSUN().
void SUNMeshArrayAPI::drawMeshArrays(PrimitiveType mode, GLint first,
                                     GLsizei count, GLsizei width) const
{
    static const char *fnName = "glDrawMeshArraysSUN";

    beforeCommand(fnName, _api.glDrawMeshArrays);
    _api.glDrawMeshArrays(toScalar(mode), first, count, width);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SUNTriangleListAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SUN_triangle_list extension.
SUNTriangleListAPI::SUNTriangleListAPI() :
    BaseExtension("GL_SUN_triangle_list")
{
}

// Grant read-only access to the underlying function pointers.
const SUNTriangleList &SUNTriangleListAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SUN_triangle_list entry points.
void SUNTriangleListAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glReplacementCodePointerSUN().
void SUNTriangleListAPI::replacementCodePointer(ReplacementCodeTypeSUN type,
                                                GLsizei stride,
                                                const void **pointer) const
{
    static const char *fnName = "glReplacementCodePointerSUN";

    beforeCommand(fnName, _api.glReplacementCodePointer);
    _api.glReplacementCodePointer(toScalar(type), stride, pointer);
    afterCommand(fnName);
}

// Calls glReplacementCodeubSUN().
void SUNTriangleListAPI::replacementCodeUB(GLubyte code) const
{
    static const char *fnName = "glReplacementCodeubSUN";

    beforeCommand(fnName, _api.glReplacementCodeub);
    _api.glReplacementCodeub(code);
    afterCommand(fnName);
}

// Calls glReplacementCodeubvSUN().
void SUNTriangleListAPI::replacementCodeUBV(const GLubyte *code) const
{
    static const char *fnName = "glReplacementCodeubvSUN";

    beforeCommand(fnName, _api.glReplacementCodeubv);
    _api.glReplacementCodeubv(code);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiSUN().
void SUNTriangleListAPI::replacementCodeUI(GLuint code) const
{
    static const char *fnName = "glReplacementCodeuiSUN";

    beforeCommand(fnName, _api.glReplacementCodeui);
    _api.glReplacementCodeui(code);
    afterCommand(fnName);
}

// Calls glReplacementCodeuivSUN().
void SUNTriangleListAPI::replacementCodeUIV(const GLuint *code) const
{
    static const char *fnName = "glReplacementCodeuivSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiv);
    _api.glReplacementCodeuiv(code);
    afterCommand(fnName);
}

// Calls glReplacementCodeusSUN().
void SUNTriangleListAPI::replacementCodeUS(GLushort code) const
{
    static const char *fnName = "glReplacementCodeusSUN";

    beforeCommand(fnName, _api.glReplacementCodeus);
    _api.glReplacementCodeus(code);
    afterCommand(fnName);
}

// Calls glReplacementCodeusvSUN().
void SUNTriangleListAPI::replacementCodeUSV(const GLushort *code) const
{
    static const char *fnName = "glReplacementCodeusvSUN";

    beforeCommand(fnName, _api.glReplacementCodeusv);
    _api.glReplacementCodeusv(code);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// SUNVertexAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_SUN_vertex extension.
SUNVertexAPI::SUNVertexAPI() :
    BaseExtension("GL_SUN_vertex")
{
}

// Grant read-only access to the underlying function pointers.
const SUNVertex &SUNVertexAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_SUN_vertex entry points.
void SUNVertexAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glColor3fVertex3fSUN().
void SUNVertexAPI::color3FVertex3F(GLfloat r, GLfloat g, GLfloat b, GLfloat x,
                                   GLfloat y, GLfloat z) const
{
    static const char *fnName = "glColor3fVertex3fSUN";

    beforeCommand(fnName, _api.glColor3fVertex3f);
    _api.glColor3fVertex3f(r, g, b, x, y, z);
    afterCommand(fnName);
}

// Calls glColor3fVertex3fvSUN().
void SUNVertexAPI::color3FVertex3FV(const GLfloat *c, const GLfloat *v) const
{
    static const char *fnName = "glColor3fVertex3fvSUN";

    beforeCommand(fnName, _api.glColor3fVertex3fv);
    _api.glColor3fVertex3fv(c, v);
    afterCommand(fnName);
}

// Calls glColor4fNormal3fVertex3fSUN().
void SUNVertexAPI::color4FNormal3FVertex3F(GLfloat r, GLfloat g, GLfloat b,
                                           GLfloat a, GLfloat nx, GLfloat ny,
                                           GLfloat nz, GLfloat x, GLfloat y,
                                           GLfloat z) const
{
    static const char *fnName = "glColor4fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glColor4fNormal3fVertex3f);
    _api.glColor4fNormal3fVertex3f(r, g, b, a, nx, ny, nz, x, y, z);
    afterCommand(fnName);
}

// Calls glColor4fNormal3fVertex3fvSUN().
void SUNVertexAPI::color4FNormal3FVertex3FV(const GLfloat *c, const GLfloat *n,
                                            const GLfloat *v) const
{
    static const char *fnName = "glColor4fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glColor4fNormal3fVertex3fv);
    _api.glColor4fNormal3fVertex3fv(c, n, v);
    afterCommand(fnName);
}

// Calls glColor4ubVertex2fSUN().
void SUNVertexAPI::color4UBVertex2F(GLubyte r, GLubyte g, GLubyte b, GLubyte a,
                                    GLfloat x, GLfloat y) const
{
    static const char *fnName = "glColor4ubVertex2fSUN";

    beforeCommand(fnName, _api.glColor4ubVertex2f);
    _api.glColor4ubVertex2f(r, g, b, a, x, y);
    afterCommand(fnName);
}

// Calls glColor4ubVertex2fvSUN().
void SUNVertexAPI::color4UBVertex2FV(const GLubyte *c, const GLfloat *v) const
{
    static const char *fnName = "glColor4ubVertex2fvSUN";

    beforeCommand(fnName, _api.glColor4ubVertex2fv);
    _api.glColor4ubVertex2fv(c, v);
    afterCommand(fnName);
}

// Calls glColor4ubVertex3fSUN().
void SUNVertexAPI::color4UBVertex3F(GLubyte r, GLubyte g, GLubyte b, GLubyte a,
                                    GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glColor4ubVertex3fSUN";

    beforeCommand(fnName, _api.glColor4ubVertex3f);
    _api.glColor4ubVertex3f(r, g, b, a, x, y, z);
    afterCommand(fnName);
}

// Calls glColor4ubVertex3fvSUN().
void SUNVertexAPI::color4UBVertex3FV(const GLubyte *c, const GLfloat *v) const
{
    static const char *fnName = "glColor4ubVertex3fvSUN";

    beforeCommand(fnName, _api.glColor4ubVertex3fv);
    _api.glColor4ubVertex3fv(c, v);
    afterCommand(fnName);
}

// Calls glNormal3fVertex3fSUN().
void SUNVertexAPI::normal3FVertex3F(GLfloat nx, GLfloat ny, GLfloat nz,
                                    GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glNormal3fVertex3f);
    _api.glNormal3fVertex3f(nx, ny, nz, x, y, z);
    afterCommand(fnName);
}

// Calls glNormal3fVertex3fvSUN().
void SUNVertexAPI::normal3FVertex3FV(const GLfloat *n, const GLfloat *v) const
{
    static const char *fnName = "glNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glNormal3fVertex3fv);
    _api.glNormal3fVertex3fv(n, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor3fVertex3fSUN().
void SUNVertexAPI::replacementCodeUIColor3FVertex3F(GLuint rc, GLfloat r,
                                                    GLfloat g, GLfloat b,
                                                    GLfloat x, GLfloat y,
                                                    GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiColor3fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor3fVertex3f);
    _api.glReplacementCodeuiColor3fVertex3f(rc, r, g, b, x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor3fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUIColor3FVertex3FV(const GLuint *rc,
                                                     const GLfloat *c,
                                                     const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiColor3fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor3fVertex3fv);
    _api.glReplacementCodeuiColor3fVertex3fv(rc, c, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor4fNormal3fVertex3fSUN().
void SUNVertexAPI::replacementCodeUIColor4FNormal3FVertex3F(GLuint rc, GLfloat r,
                                                            GLfloat g, GLfloat b,
                                                            GLfloat a,
                                                            GLfloat nx,
                                                            GLfloat ny,
                                                            GLfloat nz,
                                                            GLfloat x, GLfloat y,
                                                            GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiColor4fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor4fNormal3fVertex3f);
    _api.glReplacementCodeuiColor4fNormal3fVertex3f(rc, r, g, b, a, nx, ny, nz,
                                                    x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor4fNormal3fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUIColor4FNormal3FVertex3FV(const GLuint *rc,
                                                             const GLfloat *c,
                                                             const GLfloat *n,
                                                             const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiColor4fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor4fNormal3fVertex3fv);
    _api.glReplacementCodeuiColor4fNormal3fVertex3fv(rc, c, n, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor4ubVertex3fSUN().
void SUNVertexAPI::replacementCodeUIColor4UBVertex3F(GLuint rc, GLubyte r,
                                                     GLubyte g, GLubyte b,
                                                     GLubyte a, GLfloat x,
                                                     GLfloat y, GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiColor4ubVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor4ubVertex3f);
    _api.glReplacementCodeuiColor4ubVertex3f(rc, r, g, b, a, x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiColor4ubVertex3fvSUN().
void SUNVertexAPI::replacementCodeUIColor4UBVertex3FV(const GLuint *rc,
                                                      const GLubyte *c,
                                                      const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiColor4ubVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiColor4ubVertex3fv);
    _api.glReplacementCodeuiColor4ubVertex3fv(rc, c, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiNormal3fVertex3fSUN().
void SUNVertexAPI::replacementCodeUINormal3FVertex3F(GLuint rc, GLfloat nx,
                                                     GLfloat ny, GLfloat nz,
                                                     GLfloat x, GLfloat y,
                                                     GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiNormal3fVertex3f);
    _api.glReplacementCodeuiNormal3fVertex3f(rc, nx, ny, nz, x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiNormal3fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUINormal3FVertex3FV(const GLuint *rc,
                                                      const GLfloat *n,
                                                      const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiNormal3fVertex3fv);
    _api.glReplacementCodeuiNormal3fVertex3fv(rc, n, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FColor4FNormal3FVertex3F(GLuint rc,
                                                                      GLfloat s,
                                                                      GLfloat t,
                                                                      GLfloat r,
                                                                      GLfloat g,
                                                                      GLfloat b,
                                                                      GLfloat a,
                                                                      GLfloat nx,
                                                                      GLfloat ny,
                                                                      GLfloat nz,
                                                                      GLfloat x,
                                                                      GLfloat y,
                                                                      GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3f);
    _api.glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3f(rc, s, t, r, g, b,
                                                              a, nx, ny, nz, x,
                                                              y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FColor4FNormal3FVertex3FV(const GLuint *rc,
                                                                       const GLfloat *tc,
                                                                       const GLfloat *c,
                                                                       const GLfloat *n,
                                                                       const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fv);
    _api.glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fv(rc, tc, c, n, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FNormal3FVertex3F(GLuint rc,
                                                               GLfloat s,
                                                               GLfloat t,
                                                               GLfloat nx,
                                                               GLfloat ny,
                                                               GLfloat nz,
                                                               GLfloat x,
                                                               GLfloat y,
                                                               GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fNormal3fVertex3f);
    _api.glReplacementCodeuiTexCoord2fNormal3fVertex3f(rc, s, t, nx, ny, nz, x,
                                                       y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FNormal3FVertex3FV(const GLuint *rc,
                                                                const GLfloat *tc,
                                                                const GLfloat *n,
                                                                const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fNormal3fVertex3fv);
    _api.glReplacementCodeuiTexCoord2fNormal3fVertex3fv(rc, tc, n, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fVertex3fSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FVertex3F(GLuint rc, GLfloat s,
                                                       GLfloat t, GLfloat x,
                                                       GLfloat y, GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fVertex3f);
    _api.glReplacementCodeuiTexCoord2fVertex3f(rc, s, t, x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiTexCoord2fVertex3fvSUN().
void SUNVertexAPI::replacementCodeUITexCoord2FVertex3FV(const GLuint *rc,
                                                        const GLfloat *tc,
                                                        const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiTexCoord2fVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiTexCoord2fVertex3fv);
    _api.glReplacementCodeuiTexCoord2fVertex3fv(rc, tc, v);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiVertex3fSUN().
void SUNVertexAPI::replacementCodeUIVertex3F(GLuint rc, GLfloat x, GLfloat y,
                                             GLfloat z) const
{
    static const char *fnName = "glReplacementCodeuiVertex3fSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiVertex3f);
    _api.glReplacementCodeuiVertex3f(rc, x, y, z);
    afterCommand(fnName);
}

// Calls glReplacementCodeuiVertex3fvSUN().
void SUNVertexAPI::replacementCodeUIVertex3FV(const GLuint *rc, const GLfloat *v) const
{
    static const char *fnName = "glReplacementCodeuiVertex3fvSUN";

    beforeCommand(fnName, _api.glReplacementCodeuiVertex3fv);
    _api.glReplacementCodeuiVertex3fv(rc, v);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor3fVertex3fSUN().
void SUNVertexAPI::texCoord2FColor3FVertex3F(GLfloat s, GLfloat t, GLfloat r,
                                             GLfloat g, GLfloat b, GLfloat x,
                                             GLfloat y, GLfloat z) const
{
    static const char *fnName = "glTexCoord2fColor3fVertex3fSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor3fVertex3f);
    _api.glTexCoord2fColor3fVertex3f(s, t, r, g, b, x, y, z);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor3fVertex3fvSUN().
void SUNVertexAPI::texCoord2FColor3FVertex3FV(const GLfloat *tc,
                                              const GLfloat *c, const GLfloat *v) const
{
    static const char *fnName = "glTexCoord2fColor3fVertex3fvSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor3fVertex3fv);
    _api.glTexCoord2fColor3fVertex3fv(tc, c, v);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor4fNormal3fVertex3fSUN().
void SUNVertexAPI::texCoord2FColor4FNormal3FVertex3F(GLfloat s, GLfloat t,
                                                     GLfloat r, GLfloat g,
                                                     GLfloat b, GLfloat a,
                                                     GLfloat nx, GLfloat ny,
                                                     GLfloat nz, GLfloat x,
                                                     GLfloat y, GLfloat z) const
{
    static const char *fnName = "glTexCoord2fColor4fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor4fNormal3fVertex3f);
    _api.glTexCoord2fColor4fNormal3fVertex3f(s, t, r, g, b, a, nx, ny, nz, x, y,
                                             z);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor4fNormal3fVertex3fvSUN().
void SUNVertexAPI::texCoord2FColor4FNormal3FVertex3FV(const GLfloat *tc,
                                                      const GLfloat *c,
                                                      const GLfloat *n,
                                                      const GLfloat *v) const
{
    static const char *fnName = "glTexCoord2fColor4fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor4fNormal3fVertex3fv);
    _api.glTexCoord2fColor4fNormal3fVertex3fv(tc, c, n, v);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor4ubVertex3fSUN().
void SUNVertexAPI::texCoord2FColor4UBVertex3F(GLfloat s, GLfloat t, GLubyte r,
                                              GLubyte g, GLubyte b, GLubyte a,
                                              GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glTexCoord2fColor4ubVertex3fSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor4ubVertex3f);
    _api.glTexCoord2fColor4ubVertex3f(s, t, r, g, b, a, x, y, z);
    afterCommand(fnName);
}

// Calls glTexCoord2fColor4ubVertex3fvSUN().
void SUNVertexAPI::texCoord2FColor4UBVertex3FV(const GLfloat *tc,
                                               const GLubyte *c,
                                               const GLfloat *v) const
{
    static const char *fnName = "glTexCoord2fColor4ubVertex3fvSUN";

    beforeCommand(fnName, _api.glTexCoord2fColor4ubVertex3fv);
    _api.glTexCoord2fColor4ubVertex3fv(tc, c, v);
    afterCommand(fnName);
}

// Calls glTexCoord2fNormal3fVertex3fSUN().
void SUNVertexAPI::texCoord2FNormal3FVertex3F(GLfloat s, GLfloat t, GLfloat nx,
                                              GLfloat ny, GLfloat nz, GLfloat x,
                                              GLfloat y, GLfloat z) const
{
    static const char *fnName = "glTexCoord2fNormal3fVertex3fSUN";

    beforeCommand(fnName, _api.glTexCoord2fNormal3fVertex3f);
    _api.glTexCoord2fNormal3fVertex3f(s, t, nx, ny, nz, x, y, z);
    afterCommand(fnName);
}

// Calls glTexCoord2fNormal3fVertex3fvSUN().
void SUNVertexAPI::texCoord2FNormal3FVertex3FV(const GLfloat *tc,
                                               const GLfloat *n,
                                               const GLfloat *v) const
{
    static const char *fnName = "glTexCoord2fNormal3fVertex3fvSUN";

    beforeCommand(fnName, _api.glTexCoord2fNormal3fVertex3fv);
    _api.glTexCoord2fNormal3fVertex3fv(tc, n, v);
    afterCommand(fnName);
}

// Calls glTexCoord2fVertex3fSUN().
void SUNVertexAPI::texCoord2FVertex3F(GLfloat s, GLfloat t, GLfloat x, GLfloat y,
                                      GLfloat z) const
{
    static const char *fnName = "glTexCoord2fVertex3fSUN";

    beforeCommand(fnName, _api.glTexCoord2fVertex3f);
    _api.glTexCoord2fVertex3f(s, t, x, y, z);
    afterCommand(fnName);
}

// Calls glTexCoord2fVertex3fvSUN().
void SUNVertexAPI::texCoord2FVertex3FV(const GLfloat *tc, const GLfloat *v) const
{
    static const char *fnName = "glTexCoord2fVertex3fvSUN";

    beforeCommand(fnName, _api.glTexCoord2fVertex3fv);
    _api.glTexCoord2fVertex3fv(tc, v);
    afterCommand(fnName);
}

// Calls glTexCoord4fColor4fNormal3fVertex4fSUN().
void SUNVertexAPI::texCoord4FColor4FNormal3FVertex4F(GLfloat s, GLfloat t,
                                                     GLfloat p, GLfloat q,
                                                     GLfloat r, GLfloat g,
                                                     GLfloat b, GLfloat a,
                                                     GLfloat nx, GLfloat ny,
                                                     GLfloat nz, GLfloat x,
                                                     GLfloat y, GLfloat z,
                                                     GLfloat w) const
{
    static const char *fnName = "glTexCoord4fColor4fNormal3fVertex4fSUN";

    beforeCommand(fnName, _api.glTexCoord4fColor4fNormal3fVertex4f);
    _api.glTexCoord4fColor4fNormal3fVertex4f(s, t, p, q, r, g, b, a, nx, ny, nz,
                                             x, y, z, w);
    afterCommand(fnName);
}

// Calls glTexCoord4fColor4fNormal3fVertex4fvSUN().
void SUNVertexAPI::texCoord4FColor4FNormal3FVertex4FV(const GLfloat *tc,
                                                      const GLfloat *c,
                                                      const GLfloat *n,
                                                      const GLfloat *v) const
{
    static const char *fnName = "glTexCoord4fColor4fNormal3fVertex4fvSUN";

    beforeCommand(fnName, _api.glTexCoord4fColor4fNormal3fVertex4fv);
    _api.glTexCoord4fColor4fNormal3fVertex4fv(tc, c, n, v);
    afterCommand(fnName);
}

// Calls glTexCoord4fVertex4fSUN().
void SUNVertexAPI::texCoord4FVertex4F(GLfloat s, GLfloat t, GLfloat p, GLfloat q,
                                      GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    static const char *fnName = "glTexCoord4fVertex4fSUN";

    beforeCommand(fnName, _api.glTexCoord4fVertex4f);
    _api.glTexCoord4fVertex4f(s, t, p, q, x, y, z, w);
    afterCommand(fnName);
}

// Calls glTexCoord4fVertex4fvSUN().
void SUNVertexAPI::texCoord4FVertex4FV(const GLfloat *tc, const GLfloat *v) const
{
    static const char *fnName = "glTexCoord4fVertex4fvSUN";

    beforeCommand(fnName, _api.glTexCoord4fVertex4fv);
    _api.glTexCoord4fVertex4fv(tc, v);
    afterCommand(fnName);
}

} // namespace gl


#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// SUNGetTransparentIndexAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_SUN_get_transparent_index extension.
SUNGetTransparentIndexAPI::SUNGetTransparentIndexAPI() :
    BaseExtension("GLX_SUN_get_transparent_index")
{
}

// Grant read-only access to the underlying function pointers.
const SUNGetTransparentIndex &SUNGetTransparentIndexAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_SUN_get_transparent_index entry points.
void SUNGetTransparentIndexAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetTransparentIndexSUN().
Status SUNGetTransparentIndexAPI::xGetTransparentIndex(Display *dpy,
                                                       Window overlay,
                                                       Window underlay,
                                                       unsigned long *pTransparentIndex) const
{
    static const char *fnName = "glXGetTransparentIndexSUN";

    beforeCommand(fnName, _api.glXGetTransparentIndex);
    Status result = _api.glXGetTransparentIndex(dpy, overlay, underlay,
                                                pTransparentIndex);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

