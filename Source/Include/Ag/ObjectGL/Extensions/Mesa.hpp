//! @file Ag/ObjectGL/Extensions/Mesa.hpp
//! @brief The declaration of Mesa-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_MESA_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_MESA_EXTENSIONS_HPP__

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
// GL_MESA_framebuffer_flip_y extension API specification.
struct MESAFramebufferFlipY {
    // Public Members
    void (APIENTRY *glFramebufferParameteri)(GLenum target, GLenum pname,
                                             GLint param);
    void (APIENTRY *glGetFramebufferParameteriv)(GLenum target, GLenum pname,
                                                 GLint *params);

    // Construction
    MESAFramebufferFlipY();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAFramebufferFlipY

// GL_MESA_resize_buffers extension API specification.
struct MESAResizeBuffers {
    // Public Members
    void (APIENTRY *glResizeBuffers)();

    // Construction
    MESAResizeBuffers();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAResizeBuffers

// GL_MESA_window_pos extension API specification.
struct MESAWindowPos {
    // Public Members
    void (APIENTRY *glWindowPos2d)(GLdouble x, GLdouble y);
    void (APIENTRY *glWindowPos2dv)(const GLdouble *v);
    void (APIENTRY *glWindowPos2f)(GLfloat x, GLfloat y);
    void (APIENTRY *glWindowPos2fv)(const GLfloat *v);
    void (APIENTRY *glWindowPos2i)(GLint x, GLint y);
    void (APIENTRY *glWindowPos2iv)(const GLint *v);
    void (APIENTRY *glWindowPos2s)(GLshort x, GLshort y);
    void (APIENTRY *glWindowPos2sv)(const GLshort *v);
    void (APIENTRY *glWindowPos3d)(GLdouble x, GLdouble y, GLdouble z);
    void (APIENTRY *glWindowPos3dv)(const GLdouble *v);
    void (APIENTRY *glWindowPos3f)(GLfloat x, GLfloat y, GLfloat z);
    void (APIENTRY *glWindowPos3fv)(const GLfloat *v);
    void (APIENTRY *glWindowPos3i)(GLint x, GLint y, GLint z);
    void (APIENTRY *glWindowPos3iv)(const GLint *v);
    void (APIENTRY *glWindowPos3s)(GLshort x, GLshort y, GLshort z);
    void (APIENTRY *glWindowPos3sv)(const GLshort *v);
    void (APIENTRY *glWindowPos4d)(GLdouble x, GLdouble y, GLdouble z,
                                   GLdouble w);
    void (APIENTRY *glWindowPos4dv)(const GLdouble *v);
    void (APIENTRY *glWindowPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void (APIENTRY *glWindowPos4fv)(const GLfloat *v);
    void (APIENTRY *glWindowPos4i)(GLint x, GLint y, GLint z, GLint w);
    void (APIENTRY *glWindowPos4iv)(const GLint *v);
    void (APIENTRY *glWindowPos4s)(GLshort x, GLshort y, GLshort z, GLshort w);
    void (APIENTRY *glWindowPos4sv)(const GLshort *v);

    // Construction
    MESAWindowPos();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAWindowPos

} // namespace gl

#ifdef _USES_GLX
namespace glx {

// GLX_MESA_agp_offset extension API specification.
struct MESAAgpOffset {
    // Public Members
    unsigned int (APIENTRY *glXGetAGPOffset)(const void *pointer);

    // Construction
    MESAAgpOffset();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAAgpOffset

// GLX_MESA_copy_sub_buffer extension API specification.
struct MESACopySubBuffer {
    // Public Members
    void (APIENTRY *glXCopySubBuffer)(Display *dpy, GLXDrawable drawable, int x,
                                      int y, int width, int height);

    // Construction
    MESACopySubBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESACopySubBuffer

// GLX_MESA_pixmap_colormap extension API specification.
struct MESAPixmapColormap {
    // Public Members
    GLXPixmap(APIENTRY *glXCreateGLXPixmap)(Display *dpy, XVisualInfo *visual,
                                            Pixmap pixmap, Colormap cmap);

   // Construction
    MESAPixmapColormap();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAPixmapColormap

// GLX_MESA_query_renderer extension API specification.
struct MESAQueryRenderer {
    // Public Members
    Bool(APIENTRY *glXQueryCurrentRendererInteger)(int attribute,
                                                   unsigned int *value);
    const char *(APIENTRY *glXQueryCurrentRendererString)(int attribute);
    Bool(APIENTRY *glXQueryRendererInteger)(Display *dpy, int screen,
                                            int renderer, int attribute,
                                            unsigned int *value);
    const char *(APIENTRY *glXQueryRendererString)(Display *dpy, int screen,
                                                   int renderer, int attribute);

    // Construction
    MESAQueryRenderer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAQueryRenderer

// GLX_MESA_release_buffers extension API specification.
struct MESAReleaseBuffers {
    // Public Members
    Bool(APIENTRY *glXReleaseBuffers)(Display *dpy, GLXDrawable drawable);

    // Construction
    MESAReleaseBuffers();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESAReleaseBuffers

// GLX_MESA_set_3dfx_mode extension API specification.
struct MESASet3DFXMode {
    // Public Members
    GLboolean(APIENTRY *glXSet3DfxMode)(GLint mode);

    // Construction
    MESASet3DFXMode();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESASet3DFXMode

// GLX_MESA_swap_control extension API specification.
struct MESASwapControl {
    // Public Members
    int (APIENTRY *glXGetSwapInterval)();
    int (APIENTRY *glXSwapInterval)(unsigned int interval);

    // Construction
    MESASwapControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct MESASwapControl

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
