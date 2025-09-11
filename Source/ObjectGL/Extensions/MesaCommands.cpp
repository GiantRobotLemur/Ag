//! @file ObjectGL/Extensions/MesaCommands.cpp
//! @brief The definition of Mesa-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/MesaCommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// MESAFramebufferFlipYAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_MESA_framebuffer_flip_y extension.
MESAFramebufferFlipYAPI::MESAFramebufferFlipYAPI() :
    BaseExtension("GL_MESA_framebuffer_flip_y")
{
}

// Grant read-only access to the underlying function pointers.
const MESAFramebufferFlipY &MESAFramebufferFlipYAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_MESA_framebuffer_flip_y entry points.
void MESAFramebufferFlipYAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glFramebufferParameteriMESA().
void MESAFramebufferFlipYAPI::framebufferParameterI(FrameBufferTarget target,
                                                    FrameBufferParameterName pname,
                                                    GLint param) const
{
    static const char *fnName = "glFramebufferParameteriMESA";

    beforeCommand(fnName, _api.glFramebufferParameteri);
    _api.glFramebufferParameteri(toScalar(target), toScalar(pname), param);
    afterCommand(fnName);
}

// Calls glGetFramebufferParameterivMESA().
void MESAFramebufferFlipYAPI::getFramebufferParameterIV(FrameBufferTarget target,
                                                        FrameBufferAttachmentParameterName pname,
                                                        GLint *params) const
{
    static const char *fnName = "glGetFramebufferParameterivMESA";

    beforeCommand(fnName, _api.glGetFramebufferParameteriv);
    _api.glGetFramebufferParameteriv(toScalar(target), toScalar(pname), params);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// MESAResizeBuffersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_MESA_resize_buffers extension.
MESAResizeBuffersAPI::MESAResizeBuffersAPI() :
    BaseExtension("GL_MESA_resize_buffers")
{
}

// Grant read-only access to the underlying function pointers.
const MESAResizeBuffers &MESAResizeBuffersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_MESA_resize_buffers entry points.
void MESAResizeBuffersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glResizeBuffersMESA().
void MESAResizeBuffersAPI::resizeBuffers() const
{
    static const char *fnName = "glResizeBuffersMESA";

    beforeCommand(fnName, _api.glResizeBuffers);
    _api.glResizeBuffers();
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// MESAWindowPosAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_MESA_window_pos extension.
MESAWindowPosAPI::MESAWindowPosAPI() :
    BaseExtension("GL_MESA_window_pos")
{
}

// Grant read-only access to the underlying function pointers.
const MESAWindowPos &MESAWindowPosAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_MESA_window_pos entry points.
void MESAWindowPosAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glWindowPos2dMESA().
void MESAWindowPosAPI::windowPOS2D(GLdouble x, GLdouble y) const
{
    static const char *fnName = "glWindowPos2dMESA";

    beforeCommand(fnName, _api.glWindowPos2d);
    _api.glWindowPos2d(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2dvMESA().
void MESAWindowPosAPI::windowPOS2DV(const GLdouble *v) const
{
    static const char *fnName = "glWindowPos2dvMESA";

    beforeCommand(fnName, _api.glWindowPos2dv);
    _api.glWindowPos2dv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2fMESA().
void MESAWindowPosAPI::windowPOS2F(GLfloat x, GLfloat y) const
{
    static const char *fnName = "glWindowPos2fMESA";

    beforeCommand(fnName, _api.glWindowPos2f);
    _api.glWindowPos2f(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2fvMESA().
void MESAWindowPosAPI::windowPOS2FV(const GLfloat *v) const
{
    static const char *fnName = "glWindowPos2fvMESA";

    beforeCommand(fnName, _api.glWindowPos2fv);
    _api.glWindowPos2fv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2iMESA().
void MESAWindowPosAPI::windowPOS2I(GLint x, GLint y) const
{
    static const char *fnName = "glWindowPos2iMESA";

    beforeCommand(fnName, _api.glWindowPos2i);
    _api.glWindowPos2i(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2ivMESA().
void MESAWindowPosAPI::windowPOS2IV(const GLint *v) const
{
    static const char *fnName = "glWindowPos2ivMESA";

    beforeCommand(fnName, _api.glWindowPos2iv);
    _api.glWindowPos2iv(v);
    afterCommand(fnName);
}

// Calls glWindowPos2sMESA().
void MESAWindowPosAPI::windowPOS2S(GLshort x, GLshort y) const
{
    static const char *fnName = "glWindowPos2sMESA";

    beforeCommand(fnName, _api.glWindowPos2s);
    _api.glWindowPos2s(x, y);
    afterCommand(fnName);
}

// Calls glWindowPos2svMESA().
void MESAWindowPosAPI::windowPOS2SV(const GLshort *v) const
{
    static const char *fnName = "glWindowPos2svMESA";

    beforeCommand(fnName, _api.glWindowPos2sv);
    _api.glWindowPos2sv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3dMESA().
void MESAWindowPosAPI::windowPOS3D(GLdouble x, GLdouble y, GLdouble z) const
{
    static const char *fnName = "glWindowPos3dMESA";

    beforeCommand(fnName, _api.glWindowPos3d);
    _api.glWindowPos3d(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3dvMESA().
void MESAWindowPosAPI::windowPOS3DV(const GLdouble *v) const
{
    static const char *fnName = "glWindowPos3dvMESA";

    beforeCommand(fnName, _api.glWindowPos3dv);
    _api.glWindowPos3dv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3fMESA().
void MESAWindowPosAPI::windowPOS3F(GLfloat x, GLfloat y, GLfloat z) const
{
    static const char *fnName = "glWindowPos3fMESA";

    beforeCommand(fnName, _api.glWindowPos3f);
    _api.glWindowPos3f(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3fvMESA().
void MESAWindowPosAPI::windowPOS3FV(const GLfloat *v) const
{
    static const char *fnName = "glWindowPos3fvMESA";

    beforeCommand(fnName, _api.glWindowPos3fv);
    _api.glWindowPos3fv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3iMESA().
void MESAWindowPosAPI::windowPOS3I(GLint x, GLint y, GLint z) const
{
    static const char *fnName = "glWindowPos3iMESA";

    beforeCommand(fnName, _api.glWindowPos3i);
    _api.glWindowPos3i(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3ivMESA().
void MESAWindowPosAPI::windowPOS3IV(const GLint *v) const
{
    static const char *fnName = "glWindowPos3ivMESA";

    beforeCommand(fnName, _api.glWindowPos3iv);
    _api.glWindowPos3iv(v);
    afterCommand(fnName);
}

// Calls glWindowPos3sMESA().
void MESAWindowPosAPI::windowPOS3S(GLshort x, GLshort y, GLshort z) const
{
    static const char *fnName = "glWindowPos3sMESA";

    beforeCommand(fnName, _api.glWindowPos3s);
    _api.glWindowPos3s(x, y, z);
    afterCommand(fnName);
}

// Calls glWindowPos3svMESA().
void MESAWindowPosAPI::windowPOS3SV(const GLshort *v) const
{
    static const char *fnName = "glWindowPos3svMESA";

    beforeCommand(fnName, _api.glWindowPos3sv);
    _api.glWindowPos3sv(v);
    afterCommand(fnName);
}

// Calls glWindowPos4dMESA().
void MESAWindowPosAPI::windowPOS4D(GLdouble x, GLdouble y, GLdouble z,
                                   GLdouble w) const
{
    static const char *fnName = "glWindowPos4dMESA";

    beforeCommand(fnName, _api.glWindowPos4d);
    _api.glWindowPos4d(x, y, z, w);
    afterCommand(fnName);
}

// Calls glWindowPos4dvMESA().
void MESAWindowPosAPI::windowPOS4DV(const GLdouble *v) const
{
    static const char *fnName = "glWindowPos4dvMESA";

    beforeCommand(fnName, _api.glWindowPos4dv);
    _api.glWindowPos4dv(v);
    afterCommand(fnName);
}

// Calls glWindowPos4fMESA().
void MESAWindowPosAPI::windowPOS4F(GLfloat x, GLfloat y, GLfloat z, GLfloat w) const
{
    static const char *fnName = "glWindowPos4fMESA";

    beforeCommand(fnName, _api.glWindowPos4f);
    _api.glWindowPos4f(x, y, z, w);
    afterCommand(fnName);
}

// Calls glWindowPos4fvMESA().
void MESAWindowPosAPI::windowPOS4FV(const GLfloat *v) const
{
    static const char *fnName = "glWindowPos4fvMESA";

    beforeCommand(fnName, _api.glWindowPos4fv);
    _api.glWindowPos4fv(v);
    afterCommand(fnName);
}

// Calls glWindowPos4iMESA().
void MESAWindowPosAPI::windowPOS4I(GLint x, GLint y, GLint z, GLint w) const
{
    static const char *fnName = "glWindowPos4iMESA";

    beforeCommand(fnName, _api.glWindowPos4i);
    _api.glWindowPos4i(x, y, z, w);
    afterCommand(fnName);
}

// Calls glWindowPos4ivMESA().
void MESAWindowPosAPI::windowPOS4IV(const GLint *v) const
{
    static const char *fnName = "glWindowPos4ivMESA";

    beforeCommand(fnName, _api.glWindowPos4iv);
    _api.glWindowPos4iv(v);
    afterCommand(fnName);
}

// Calls glWindowPos4sMESA().
void MESAWindowPosAPI::windowPOS4S(GLshort x, GLshort y, GLshort z, GLshort w) const
{
    static const char *fnName = "glWindowPos4sMESA";

    beforeCommand(fnName, _api.glWindowPos4s);
    _api.glWindowPos4s(x, y, z, w);
    afterCommand(fnName);
}

// Calls glWindowPos4svMESA().
void MESAWindowPosAPI::windowPOS4SV(const GLshort *v) const
{
    static const char *fnName = "glWindowPos4svMESA";

    beforeCommand(fnName, _api.glWindowPos4sv);
    _api.glWindowPos4sv(v);
    afterCommand(fnName);
}

} // namespace gl

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// MESAAgpOffsetAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_agp_offset extension.
MESAAgpOffsetAPI::MESAAgpOffsetAPI() :
    BaseExtension("GLX_MESA_agp_offset")
{
}

// Grant read-only access to the underlying function pointers.
const MESAAgpOffset &MESAAgpOffsetAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_agp_offset entry points.
void MESAAgpOffsetAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetAGPOffsetMESA().
unsigned int MESAAgpOffsetAPI::xGetAgpOffset(const void *pointer) const
{
    static const char *fnName = "glXGetAGPOffsetMESA";

    beforeCommand(fnName, _api.glXGetAGPOffset);
    unsigned int result = _api.glXGetAGPOffset(pointer);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// MESACopySubBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_copy_sub_buffer extension.
MESACopySubBufferAPI::MESACopySubBufferAPI() :
    BaseExtension("GLX_MESA_copy_sub_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const MESACopySubBuffer &MESACopySubBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_copy_sub_buffer entry points.
void MESACopySubBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCopySubBufferMESA().
void MESACopySubBufferAPI::xCopySubBuffer(Display *dpy, GLXDrawable drawable,
                                          int x, int y, int width, int height) const
{
    static const char *fnName = "glXCopySubBufferMESA";

    beforeCommand(fnName, _api.glXCopySubBuffer);
    _api.glXCopySubBuffer(dpy, drawable, x, y, width, height);
    afterCommand(fnName);
}

////////////////////////////////////////////////////////////////////////////////
// MESAPixmapColormapAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_pixmap_colormap extension.
MESAPixmapColormapAPI::MESAPixmapColormapAPI() :
    BaseExtension("GLX_MESA_pixmap_colormap")
{
}

// Grant read-only access to the underlying function pointers.
const MESAPixmapColormap &MESAPixmapColormapAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_pixmap_colormap entry points.
void MESAPixmapColormapAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXCreateGLXPixmapMESA().
GLXPixmap MESAPixmapColormapAPI::xCreateGlxPixmap(Display *dpy,
                                                  XVisualInfo *visual,
                                                  Pixmap pixmap, Colormap cmap) const
{
    static const char *fnName = "glXCreateGLXPixmapMESA";

    beforeCommand(fnName, _api.glXCreateGLXPixmap);
    GLXPixmap result = _api.glXCreateGLXPixmap(dpy, visual, pixmap, cmap);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// MESAQueryRendererAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_query_renderer extension.
MESAQueryRendererAPI::MESAQueryRendererAPI() :
    BaseExtension("GLX_MESA_query_renderer")
{
}

// Grant read-only access to the underlying function pointers.
const MESAQueryRenderer &MESAQueryRendererAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_query_renderer entry points.
void MESAQueryRendererAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXQueryCurrentRendererIntegerMESA().
Bool MESAQueryRendererAPI::xQueryCurrentRendererInteger(int attribute,
                                                        unsigned int *value) const
{
    static const char *fnName = "glXQueryCurrentRendererIntegerMESA";

    beforeCommand(fnName, _api.glXQueryCurrentRendererInteger);
    Bool result = _api.glXQueryCurrentRendererInteger(attribute, value);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryCurrentRendererStringMESA().
const char *MESAQueryRendererAPI::xQueryCurrentRendererString(int attribute) const
{
    static const char *fnName = "glXQueryCurrentRendererStringMESA";

    beforeCommand(fnName, _api.glXQueryCurrentRendererString);
    const char *result = _api.glXQueryCurrentRendererString(attribute);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryRendererIntegerMESA().
Bool MESAQueryRendererAPI::xQueryRendererInteger(Display *dpy, int screen,
                                                 int renderer, int attribute,
                                                 unsigned int *value) const
{
    static const char *fnName = "glXQueryRendererIntegerMESA";

    beforeCommand(fnName, _api.glXQueryRendererInteger);
    Bool result = _api.glXQueryRendererInteger(dpy, screen, renderer, attribute,
                                               value);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryRendererStringMESA().
const char *MESAQueryRendererAPI::xQueryRendererString(Display *dpy, int screen,
                                                       int renderer,
                                                       int attribute) const
{
    static const char *fnName = "glXQueryRendererStringMESA";

    beforeCommand(fnName, _api.glXQueryRendererString);
    const char *result = _api.glXQueryRendererString(dpy, screen, renderer,
                                                     attribute);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// MESAReleaseBuffersAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_release_buffers extension.
MESAReleaseBuffersAPI::MESAReleaseBuffersAPI() :
    BaseExtension("GLX_MESA_release_buffers")
{
}

// Grant read-only access to the underlying function pointers.
const MESAReleaseBuffers &MESAReleaseBuffersAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_release_buffers entry points.
void MESAReleaseBuffersAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXReleaseBuffersMESA().
Bool MESAReleaseBuffersAPI::xReleaseBuffers(Display *dpy, GLXDrawable drawable) const
{
    static const char *fnName = "glXReleaseBuffersMESA";

    beforeCommand(fnName, _api.glXReleaseBuffers);
    Bool result = _api.glXReleaseBuffers(dpy, drawable);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// MESASet3DFXModeAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_set_3dfx_mode extension.
MESASet3DFXModeAPI::MESASet3DFXModeAPI() :
    BaseExtension("GLX_MESA_set_3dfx_mode")
{
}

// Grant read-only access to the underlying function pointers.
const MESASet3DFXMode &MESASet3DFXModeAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_set_3dfx_mode entry points.
void MESASet3DFXModeAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXSet3DfxModeMESA().
GLboolean MESASet3DFXModeAPI::xSET3DfxMode(GLint mode) const
{
    static const char *fnName = "glXSet3DfxModeMESA";

    beforeCommand(fnName, _api.glXSet3DfxMode);
    GLboolean result = _api.glXSet3DfxMode(mode);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// MESASwapControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_MESA_swap_control extension.
MESASwapControlAPI::MESASwapControlAPI() :
    BaseExtension("GLX_MESA_swap_control")
{
}

// Grant read-only access to the underlying function pointers.
const MESASwapControl &MESASwapControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_MESA_swap_control entry points.
void MESASwapControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetSwapIntervalMESA().
int MESASwapControlAPI::xGetSwapInterval() const
{
    static const char *fnName = "glXGetSwapIntervalMESA";

    beforeCommand(fnName, _api.glXGetSwapInterval);
    int result = _api.glXGetSwapInterval();
    afterCommand(fnName);

    return result;
}

// Calls glXSwapIntervalMESA().
int MESASwapControlAPI::xSwapInterval(unsigned int interval) const
{
    static const char *fnName = "glXSwapIntervalMESA";

    beforeCommand(fnName, _api.glXSwapInterval);
    int result = _api.glXSwapInterval(interval);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

