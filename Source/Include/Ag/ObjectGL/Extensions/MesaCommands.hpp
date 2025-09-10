//! @file Ag/ObjectGL/Extensions/MesaCommands.hpp
//! @brief The declaration of Mesa-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_MESA_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_MESA_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "Mesa.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_MESA_framebuffer_flip_y extension API.
class MESAFramebufferFlipYAPI : public BaseExtension
{
public:
    // Construction
    MESAFramebufferFlipYAPI();

    // Accessors
    const MESAFramebufferFlipY &getRawAPI() const;

    // Operations
    void framebufferParameterI(FramebufferTarget target,
                               FramebufferParameterName pname, GLint param) const;
    void getFramebufferParameterIV(FramebufferTarget target,
                                   FramebufferAttachmentParameterName pname,
                                   GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAFramebufferFlipY _api;
};

// Manages the entry points for the GL_MESA_resize_buffers extension API.
class MESAResizeBuffersAPI : public BaseExtension
{
public:
    // Construction
    MESAResizeBuffersAPI();

    // Accessors
    const MESAResizeBuffers &getRawAPI() const;

    // Operations
    void resizeBuffers() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAResizeBuffers _api;
};

// Manages the entry points for the GL_MESA_window_pos extension API.
class MESAWindowPosAPI : public BaseExtension
{
public:
    // Construction
    MESAWindowPosAPI();

    // Accessors
    const MESAWindowPos &getRawAPI() const;

    // Operations
    void windowPOS2D(GLdouble x, GLdouble y) const;
    void windowPOS2DV(const GLdouble *v) const;
    void windowPOS2F(GLfloat x, GLfloat y) const;
    void windowPOS2FV(const GLfloat *v) const;
    void windowPOS2I(GLint x, GLint y) const;
    void windowPOS2IV(const GLint *v) const;
    void windowPOS2S(GLshort x, GLshort y) const;
    void windowPOS2SV(const GLshort *v) const;
    void windowPOS3D(GLdouble x, GLdouble y, GLdouble z) const;
    void windowPOS3DV(const GLdouble *v) const;
    void windowPOS3F(GLfloat x, GLfloat y, GLfloat z) const;
    void windowPOS3FV(const GLfloat *v) const;
    void windowPOS3I(GLint x, GLint y, GLint z) const;
    void windowPOS3IV(const GLint *v) const;
    void windowPOS3S(GLshort x, GLshort y, GLshort z) const;
    void windowPOS3SV(const GLshort *v) const;
    void windowPOS4D(GLdouble x, GLdouble y, GLdouble z, GLdouble w) const;
    void windowPOS4DV(const GLdouble *v) const;
    void windowPOS4F(GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
    void windowPOS4FV(const GLfloat *v) const;
    void windowPOS4I(GLint x, GLint y, GLint z, GLint w) const;
    void windowPOS4IV(const GLint *v) const;
    void windowPOS4S(GLshort x, GLshort y, GLshort z, GLshort w) const;
    void windowPOS4SV(const GLshort *v) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAWindowPos _api;
};

} // namespace gl

#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_MESA_agp_offset extension API.
class MESAAgpOffsetAPI : public gl::BaseExtension
{
public:
    // Construction
    MESAAgpOffsetAPI();

    // Accessors
    const MESAAgpOffset &getRawAPI() const;

    // Operations
    unsigned int xGetAgpOffset(const void *pointer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAAgpOffset _api;
};

// Manages the entry points for the GLX_MESA_copy_sub_buffer extension API.
class MESACopySubBufferAPI : public gl::BaseExtension
{
public:
    // Construction
    MESACopySubBufferAPI();

    // Accessors
    const MESACopySubBuffer &getRawAPI() const;

    // Operations
    void xCopySubBuffer(Display *dpy, GLXDrawable drawable, int x, int y,
                        int width, int height) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESACopySubBuffer _api;
};

// Manages the entry points for the GLX_MESA_pixmap_colormap extension API.
class MESAPixmapColormapAPI : public gl::BaseExtension
{
public:
    // Construction
    MESAPixmapColormapAPI();

    // Accessors
    const MESAPixmapColormap &getRawAPI() const;

    // Operations
    GLXPixmap xCreateGlxPixmap(Display *dpy, XVisualInfo *visual, Pixmap pixmap,
                               Colormap cmap) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAPixmapColormap _api;
};

// Manages the entry points for the GLX_MESA_query_renderer extension API.
class MESAQueryRendererAPI : public gl::BaseExtension
{
public:
    // Construction
    MESAQueryRendererAPI();

    // Accessors
    const MESAQueryRenderer &getRawAPI() const;

    // Operations
    Bool xQueryCurrentRendererInteger(int attribute, unsigned int *value) const;
    const char *xQueryCurrentRendererString(int attribute) const;
    Bool xQueryRendererInteger(Display *dpy, int screen, int renderer,
                               int attribute, unsigned int *value) const;
    const char *xQueryRendererString(Display *dpy, int screen, int renderer,
                                     int attribute) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAQueryRenderer _api;
};

// Manages the entry points for the GLX_MESA_release_buffers extension API.
class MESAReleaseBuffersAPI : public gl::BaseExtension
{
public:
    // Construction
    MESAReleaseBuffersAPI();

    // Accessors
    const MESAReleaseBuffers &getRawAPI() const;

    // Operations
    Bool xReleaseBuffers(Display *dpy, GLXDrawable drawable) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESAReleaseBuffers _api;
};

// Manages the entry points for the GLX_MESA_set_3dfx_mode extension API.
class MESASet3DFXModeAPI : public gl::BaseExtension
{
public:
    // Construction
    MESASet3DFXModeAPI();

    // Accessors
    const MESASet3DFXMode &getRawAPI() const;

    // Operations
    GLboolean xSET3DfxMode(GLint mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESASet3DFXMode _api;
};

// Manages the entry points for the GLX_MESA_swap_control extension API.
class MESASwapControlAPI : public gl::BaseExtension
{
public:
    // Construction
    MESASwapControlAPI();

    // Accessors
    const MESASwapControl &getRawAPI() const;

    // Operations
    int xGetSwapInterval() const;
    int xSwapInterval(unsigned int interval) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    MESASwapControl _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
