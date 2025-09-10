//! @file Ag/ObjectGL/Extensions/Sun.hpp
//! @brief The declaration of Sun Microsystems-specific extensions to the
//! OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_SUN_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_SUN_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

#ifdef _USES_GLX
#include "../GLX_Types.hpp"
#endif // ifdef _USES_GLX

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_SUNX_constant_data extension API specification.
struct SUNXConstantData {
    // Public Members
    void (APIENTRY *glFinishTexture)();

    // Construction
    SUNXConstantData();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNXConstantData

// GL_SUN_global_alpha extension API specification.
struct SUNGlobalAlpha {
    // Public Members
    void (APIENTRY *glGlobalAlphaFactorb)(GLbyte factor);
    void (APIENTRY *glGlobalAlphaFactord)(GLdouble factor);
    void (APIENTRY *glGlobalAlphaFactorf)(GLfloat factor);
    void (APIENTRY *glGlobalAlphaFactori)(GLint factor);
    void (APIENTRY *glGlobalAlphaFactors)(GLshort factor);
    void (APIENTRY *glGlobalAlphaFactorub)(GLubyte factor);
    void (APIENTRY *glGlobalAlphaFactorui)(GLuint factor);
    void (APIENTRY *glGlobalAlphaFactorus)(GLushort factor);

    // Construction
    SUNGlobalAlpha();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNGlobalAlpha

// GL_SUN_mesh_array extension API specification.
struct SUNMeshArray {
    // Public Members
    void (APIENTRY *glDrawMeshArrays)(GLenum mode, GLint first, GLsizei count,
                                      GLsizei width);

    // Construction
    SUNMeshArray();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNMeshArray

// GL_SUN_triangle_list extension API specification.
struct SUNTriangleList {
    // Public Members
    void (APIENTRY *glReplacementCodePointer)(GLenum type, GLsizei stride,
                                              const void **pointer);
    void (APIENTRY *glReplacementCodeub)(GLubyte code);
    void (APIENTRY *glReplacementCodeubv)(const GLubyte *code);
    void (APIENTRY *glReplacementCodeui)(GLuint code);
    void (APIENTRY *glReplacementCodeuiv)(const GLuint *code);
    void (APIENTRY *glReplacementCodeus)(GLushort code);
    void (APIENTRY *glReplacementCodeusv)(const GLushort *code);

    // Construction
    SUNTriangleList();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNTriangleList

// GL_SUN_vertex extension API specification.
struct SUNVertex {
    // Public Members
    void (APIENTRY *glColor3fVertex3f)(GLfloat r, GLfloat g, GLfloat b,
                                       GLfloat x, GLfloat y, GLfloat z);
    void (APIENTRY *glColor3fVertex3fv)(const GLfloat *c, const GLfloat *v);
    void (APIENTRY *glColor4fNormal3fVertex3f)(GLfloat r, GLfloat g, GLfloat b,
                                               GLfloat a, GLfloat nx, GLfloat ny,
                                               GLfloat nz, GLfloat x, GLfloat y,
                                               GLfloat z);
    void (APIENTRY *glColor4fNormal3fVertex3fv)(const GLfloat *c,
                                                const GLfloat *n,
                                                const GLfloat *v);
    void (APIENTRY *glColor4ubVertex2f)(GLubyte r, GLubyte g, GLubyte b,
                                        GLubyte a, GLfloat x, GLfloat y);
    void (APIENTRY *glColor4ubVertex2fv)(const GLubyte *c, const GLfloat *v);
    void (APIENTRY *glColor4ubVertex3f)(GLubyte r, GLubyte g, GLubyte b,
                                        GLubyte a, GLfloat x, GLfloat y,
                                        GLfloat z);
    void (APIENTRY *glColor4ubVertex3fv)(const GLubyte *c, const GLfloat *v);
    void (APIENTRY *glNormal3fVertex3f)(GLfloat nx, GLfloat ny, GLfloat nz,
                                        GLfloat x, GLfloat y, GLfloat z);
    void (APIENTRY *glNormal3fVertex3fv)(const GLfloat *n, const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiColor3fVertex3f)(GLuint rc, GLfloat r,
                                                        GLfloat g, GLfloat b,
                                                        GLfloat x, GLfloat y,
                                                        GLfloat z);
    void (APIENTRY *glReplacementCodeuiColor3fVertex3fv)(const GLuint *rc,
                                                         const GLfloat *c,
                                                         const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiColor4fNormal3fVertex3f)(GLuint rc,
                                                                GLfloat r,
                                                                GLfloat g,
                                                                GLfloat b,
                                                                GLfloat a,
                                                                GLfloat nx,
                                                                GLfloat ny,
                                                                GLfloat nz,
                                                                GLfloat x,
                                                                GLfloat y,
                                                                GLfloat z);
    void (APIENTRY *glReplacementCodeuiColor4fNormal3fVertex3fv)(const GLuint *rc,
                                                                 const GLfloat *c,
                                                                 const GLfloat *n,
                                                                 const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiColor4ubVertex3f)(GLuint rc, GLubyte r,
                                                         GLubyte g, GLubyte b,
                                                         GLubyte a, GLfloat x,
                                                         GLfloat y, GLfloat z);
    void (APIENTRY *glReplacementCodeuiColor4ubVertex3fv)(const GLuint *rc,
                                                          const GLubyte *c,
                                                          const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiNormal3fVertex3f)(GLuint rc, GLfloat nx,
                                                         GLfloat ny, GLfloat nz,
                                                         GLfloat x, GLfloat y,
                                                         GLfloat z);
    void (APIENTRY *glReplacementCodeuiNormal3fVertex3fv)(const GLuint *rc,
                                                          const GLfloat *n,
                                                          const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3f)(GLuint rc,
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
                                                                          GLfloat z);
    void (APIENTRY *glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fv)(const GLuint *rc,
                                                                           const GLfloat *tc,
                                                                           const GLfloat *c,
                                                                           const GLfloat *n,
                                                                           const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiTexCoord2fNormal3fVertex3f)(GLuint rc,
                                                                   GLfloat s,
                                                                   GLfloat t,
                                                                   GLfloat nx,
                                                                   GLfloat ny,
                                                                   GLfloat nz,
                                                                   GLfloat x,
                                                                   GLfloat y,
                                                                   GLfloat z);
    void (APIENTRY *glReplacementCodeuiTexCoord2fNormal3fVertex3fv)(const GLuint *rc,
                                                                    const GLfloat *tc,
                                                                    const GLfloat *n,
                                                                    const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiTexCoord2fVertex3f)(GLuint rc, GLfloat s,
                                                           GLfloat t, GLfloat x,
                                                           GLfloat y, GLfloat z);
    void (APIENTRY *glReplacementCodeuiTexCoord2fVertex3fv)(const GLuint *rc,
                                                            const GLfloat *tc,
                                                            const GLfloat *v);
    void (APIENTRY *glReplacementCodeuiVertex3f)(GLuint rc, GLfloat x, GLfloat y,
                                                 GLfloat z);
    void (APIENTRY *glReplacementCodeuiVertex3fv)(const GLuint *rc,
                                                  const GLfloat *v);
    void (APIENTRY *glTexCoord2fColor3fVertex3f)(GLfloat s, GLfloat t, GLfloat r,
                                                 GLfloat g, GLfloat b, GLfloat x,
                                                 GLfloat y, GLfloat z);
    void (APIENTRY *glTexCoord2fColor3fVertex3fv)(const GLfloat *tc,
                                                  const GLfloat *c,
                                                  const GLfloat *v);
    void (APIENTRY *glTexCoord2fColor4fNormal3fVertex3f)(GLfloat s, GLfloat t,
                                                         GLfloat r, GLfloat g,
                                                         GLfloat b, GLfloat a,
                                                         GLfloat nx, GLfloat ny,
                                                         GLfloat nz, GLfloat x,
                                                         GLfloat y, GLfloat z);
    void (APIENTRY *glTexCoord2fColor4fNormal3fVertex3fv)(const GLfloat *tc,
                                                          const GLfloat *c,
                                                          const GLfloat *n,
                                                          const GLfloat *v);
    void (APIENTRY *glTexCoord2fColor4ubVertex3f)(GLfloat s, GLfloat t,
                                                  GLubyte r, GLubyte g,
                                                  GLubyte b, GLubyte a,
                                                  GLfloat x, GLfloat y,
                                                  GLfloat z);
    void (APIENTRY *glTexCoord2fColor4ubVertex3fv)(const GLfloat *tc,
                                                   const GLubyte *c,
                                                   const GLfloat *v);
    void (APIENTRY *glTexCoord2fNormal3fVertex3f)(GLfloat s, GLfloat t,
                                                  GLfloat nx, GLfloat ny,
                                                  GLfloat nz, GLfloat x,
                                                  GLfloat y, GLfloat z);
    void (APIENTRY *glTexCoord2fNormal3fVertex3fv)(const GLfloat *tc,
                                                   const GLfloat *n,
                                                   const GLfloat *v);
    void (APIENTRY *glTexCoord2fVertex3f)(GLfloat s, GLfloat t, GLfloat x,
                                          GLfloat y, GLfloat z);
    void (APIENTRY *glTexCoord2fVertex3fv)(const GLfloat *tc, const GLfloat *v);
    void (APIENTRY *glTexCoord4fColor4fNormal3fVertex4f)(GLfloat s, GLfloat t,
                                                         GLfloat p, GLfloat q,
                                                         GLfloat r, GLfloat g,
                                                         GLfloat b, GLfloat a,
                                                         GLfloat nx, GLfloat ny,
                                                         GLfloat nz, GLfloat x,
                                                         GLfloat y, GLfloat z,
                                                         GLfloat w);
    void (APIENTRY *glTexCoord4fColor4fNormal3fVertex4fv)(const GLfloat *tc,
                                                          const GLfloat *c,
                                                          const GLfloat *n,
                                                          const GLfloat *v);
    void (APIENTRY *glTexCoord4fVertex4f)(GLfloat s, GLfloat t, GLfloat p,
                                          GLfloat q, GLfloat x, GLfloat y,
                                          GLfloat z, GLfloat w);
    void (APIENTRY *glTexCoord4fVertex4fv)(const GLfloat *tc, const GLfloat *v);

    // Construction
    SUNVertex();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNVertex

} // namespace gl


#ifdef _USES_GLX
namespace glx {

// GLX_SUN_get_transparent_index extension API specification.
struct SUNGetTransparentIndex {
    // Public Members
    Status(APIENTRY *glXGetTransparentIndex)(Display *dpy, Window overlay,
                                             Window underlay,
                                             unsigned long *pTransparentIndex);

   // Construction
    SUNGetTransparentIndex();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SUNGetTransparentIndex

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
