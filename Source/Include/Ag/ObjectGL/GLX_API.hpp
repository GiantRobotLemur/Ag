//! @file Ag/ObjectGL/GLX_API.hpp
//! @brief The declaration of X Windows-specific OpenGL entry points,
//! also known as GLX.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __07F8F063_C34D_4F35_8447_118A48238BC5_INCLUDED__
#define __07F8F063_C34D_4F35_8447_118A48238BC5_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"
#include "GLX_Types.hpp"

namespace glx {

////////////////////////////////////////////////////////////////////////////////
// API Command Groups
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure which contains pointers to GLX-specific functions which
//! are resolved at runtime.
struct GLX {
    // Public Members

    // GLX 1.0
    XVisualInfo *(APIENTRY *glXChooseVisual)(Display *dpy, int screen,
                                             int *attribList);
    void (APIENTRY *glXCopyContext)(Display *dpy, GLXContext src, GLXContext dst,
                                    unsigned long mask);
    GLXContext (APIENTRY *glXCreateContext)(Display *dpy, XVisualInfo *vis,
                                            GLXContext shareList, Bool direct);
    GLXPixmap (APIENTRY *glXCreateGLXPixmap)(Display *dpy, XVisualInfo *visual,
                                             Pixmap pixmap);
    void (APIENTRY *glXDestroyContext)(Display *dpy, GLXContext ctx);
    void (APIENTRY *glXDestroyGLXPixmap)(Display *dpy, GLXPixmap pixmap);
    int (APIENTRY *glXGetConfig)(Display *dpy, XVisualInfo *visual, int attrib,
                                 int *value);
    GLXContext (APIENTRY *glXGetCurrentContext)();
    GLXDrawable (APIENTRY *glXGetCurrentDrawable)();
    Bool (APIENTRY *glXIsDirect)(Display *dpy, GLXContext ctx);
    Bool (APIENTRY *glXMakeCurrent)(Display *dpy, GLXDrawable drawable,
                                    GLXContext ctx);
    Bool (APIENTRY *glXQueryExtension)(Display *dpy, int *errorb, int *event);
    Bool (APIENTRY *glXQueryVersion)(Display *dpy, int *maj, int *min);
    void (APIENTRY *glXSwapBuffers)(Display *dpy, GLXDrawable drawable);
    void (APIENTRY *glXUseXFont)(Font font, int first, int count, int list);
    void (APIENTRY *glXWaitGL)();
    void (APIENTRY *glXWaitX)();

    // GLX 1.1
    const char *(APIENTRY *glXGetClientString)(Display *dpy, int name);
    const char *(APIENTRY *glXQueryExtensionsString)(Display *dpy, int screen);
    const char *(APIENTRY *glXQueryServerString)(Display *dpy, int screen,
                                                 int name);

    // GLX 1.2
    Display *(APIENTRY *glXGetCurrentDisplay)();

    // GLX 1.3
    GLXFBConfig *(APIENTRY *glXChooseFBConfig)(Display *dpy, int screen,
                                               const int *attrib_list,
                                               int *nelements);
    GLXContext (APIENTRY *glXCreateNewContext)(Display *dpy, GLXFBConfig config,
                                               int render_type,
                                               GLXContext share_list,
                                               Bool direct);
    GLXPbuffer (APIENTRY *glXCreatePbuffer)(Display *dpy, GLXFBConfig config,
                                            const int *attrib_list);
    GLXPixmap (APIENTRY *glXCreatePixmap)(Display *dpy, GLXFBConfig config,
                                          Pixmap pixmap, const int *attrib_list);
    GLXWindow (APIENTRY *glXCreateWindow)(Display *dpy, GLXFBConfig config,
                                          Window win, const int *attrib_list);
    void (APIENTRY *glXDestroyPbuffer)(Display *dpy, GLXPbuffer pbuf);
    void (APIENTRY *glXDestroyPixmap)(Display *dpy, GLXPixmap pixmap);
    void (APIENTRY *glXDestroyWindow)(Display *dpy, GLXWindow win);
    GLXDrawable (APIENTRY *glXGetCurrentReadDrawable)();
    int (APIENTRY *glXGetFBConfigAttrib)(Display *dpy, GLXFBConfig config,
                                         int attribute, int *value);
    GLXFBConfig *(APIENTRY *glXGetFBConfigs)(Display *dpy, int screen,
                                             int *nelements);
    void (APIENTRY *glXGetSelectedEvent)(Display *dpy, GLXDrawable draw,
                                         unsigned long *event_mask);
    XVisualInfo *(APIENTRY *glXGetVisualFromFBConfig)(Display *dpy,
                                                      GLXFBConfig config);
    Bool (APIENTRY *glXMakeContextCurrent)(Display *dpy, GLXDrawable draw,
                                           GLXDrawable read, GLXContext ctx);
    int (APIENTRY *glXQueryContext)(Display *dpy, GLXContext ctx, int attribute,
                                    int *value);
    void (APIENTRY *glXQueryDrawable)(Display *dpy, GLXDrawable draw,
                                      int attribute, unsigned int *value);
    void (APIENTRY *glXSelectEvent)(Display *dpy, GLXDrawable draw,
                                    unsigned long event_mask);

    // GLX 1.4
    __GLXextFuncPtr (APIENTRY *glXGetProcAddress)(const GLubyte *procName);

    // Construction
    GLX();

    // Operations
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct GLX

} // namespace glx

#endif // ifndef __07F8F063_C34D_4F35_8447_118A48238BC5_INCLUDED__
