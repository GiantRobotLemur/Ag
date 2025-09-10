//! @file Ag/ObjectGL/GLX_CommandSets.hpp
//! @brief The declaration of wrappers for X Windows-specific OpenGL entry points.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __9EF999CC_34BD_4556_B456_98B375866E15_INCLUDED__
#define __9EF999CC_34BD_4556_B456_98B375866E15_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "GLX_API.hpp"

namespace glx {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A class which wraps all core GLX-specific entry points so that they
//! can be called with more useful data types and with inherit type checking and
//! error detection.
class GLXAPI : public gl::BaseAPI
{
public:
    // Construction
    GLXAPI();

    // Accessors
    const GLX &getRawAPI() const;

    // Operations

    // GLX 1.0
    XVisualInfo *xChooseVisual(Display *dpy, int screen, int *attribList) const;
    void xCopyContext(Display *dpy, GLXContext src, GLXContext dst,
                      unsigned long mask) const;
    GLXContext xCreateContext(Display *dpy, XVisualInfo *vis,
                              GLXContext shareList, Bool direct) const;
    GLXPixmap xCreateGlxPixmap(Display *dpy, XVisualInfo *visual, Pixmap pixmap) const;
    void xDestroyContext(Display *dpy, GLXContext ctx) const;
    void xDestroyGlxPixmap(Display *dpy, GLXPixmap pixmap) const;
    int xGetConfig(Display *dpy, XVisualInfo *visual, int attrib, int *value) const;
    GLXContext xGetCurrentContext() const;
    GLXDrawable xGetCurrentDrawable() const;
    Bool xIsDirect(Display *dpy, GLXContext ctx) const;
    Bool xMakeCurrent(Display *dpy, GLXDrawable drawable, GLXContext ctx) const;
    Bool xQueryExtension(Display *dpy, int *errorb, int *event) const;
    Bool xQueryVersion(Display *dpy, int *maj, int *min) const;
    void xSwapBuffers(Display *dpy, GLXDrawable drawable) const;
    void xUseXFont(Font font, int first, int count, int list) const;
    void xWaitGl() const;
    void xWaitX() const;

    // GLX 1.1
    const char *xGetClientString(Display *dpy, int name) const;
    const char *xQueryExtensionsString(Display *dpy, int screen) const;
    const char *xQueryServerString(Display *dpy, int screen, int name) const;

    // GLX 1.2
    Display *xGetCurrentDisplay() const;

    // GLX 1.3
    GLXFBConfig *xChooseFBConfig(Display *dpy, int screen,
                                 const int *attrib_list, int *nelements) const;
    GLXContext xCreateNewContext(Display *dpy, GLXFBConfig config,
                                 int render_type, GLXContext share_list,
                                 Bool direct) const;
    GLXPbuffer xCreatePbuffer(Display *dpy, GLXFBConfig config,
                              const int *attrib_list) const;
    GLXPixmap xCreatePixmap(Display *dpy, GLXFBConfig config, Pixmap pixmap,
                            const int *attrib_list) const;
    GLXWindow xCreateWindow(Display *dpy, GLXFBConfig config, Window win,
                            const int *attrib_list) const;
    void xDestroyPbuffer(Display *dpy, GLXPbuffer pbuf) const;
    void xDestroyPixmap(Display *dpy, GLXPixmap pixmap) const;
    void xDestroyWindow(Display *dpy, GLXWindow win) const;
    GLXDrawable xGetCurrentReadDrawable() const;
    int xGetFBConfigAttrib(Display *dpy, GLXFBConfig config, int attribute,
                           int *value) const;
    GLXFBConfig *xGetFBConfigs(Display *dpy, int screen, int *nelements) const;
    void xGetSelectedEvent(Display *dpy, GLXDrawable draw,
                           unsigned long *event_mask) const;
    XVisualInfo *xGetVisualFromFBConfig(Display *dpy, GLXFBConfig config) const;
    Bool xMakeContextCurrent(Display *dpy, GLXDrawable draw, GLXDrawable read,
                             GLXContext ctx) const;
    int xQueryContext(Display *dpy, GLXContext ctx, int attribute, int *value) const;
    void xQueryDrawable(Display *dpy, GLXDrawable draw, int attribute,
                        unsigned int *value) const;
    void xSelectEvent(Display *dpy, GLXDrawable draw, unsigned long event_mask) const;

    // GLX 1.4
    __GLXextFuncPtr xGetProcAddress(const GLubyte *procName) const;

    // Overrides
    virtual void resolve(const APIResolver* resolver) override;

private:
    GLX _api;
};

} // namespace glx

#endif // ifndef __9EF999CC_34BD_4556_B456_98B375866E15_INCLUDED__
