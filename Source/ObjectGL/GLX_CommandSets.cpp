//! @file ObjectGL/GLX_CommandSets.cpp
//! @brief The definition of of wrappers for X Windows-specific OpenGL
//! entry points.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CommandSetTools.hpp"
#include "Ag/ObjectGL/GLX_CommandSets.hpp"

namespace glx {

////////////////////////////////////////////////////////////////////////////////
// GLXAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Constructs an unresolved command set for the core API.
GLXAPI::GLXAPI()
{
}

// Grant read-only access to the underlying function pointers.
const GLX &GLXAPI::getRawAPI() const
{
    return _api;
}

// Resolve core API entry points.
void GLXAPI::resolve(const APIResolver* resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseAPI::resolve(resolver);
    }
}

// Calls glXChooseVisual().
XVisualInfo *GLXAPI::xChooseVisual(Display *dpy, int screen, int *attribList) const
{
    static const char *fnName = "glXChooseVisual";

    beforeCommand(fnName, _api.glXChooseVisual);
    XVisualInfo *result = _api.glXChooseVisual(dpy, screen, attribList);
    afterCommand(fnName);

    return result;
}

// Calls glXCopyContext().
void GLXAPI::xCopyContext(Display *dpy, GLXContext src, GLXContext dst,
                          unsigned long mask) const
{
    static const char *fnName = "glXCopyContext";

    beforeCommand(fnName, _api.glXCopyContext);
    _api.glXCopyContext(dpy, src, dst, mask);
    afterCommand(fnName);
}

// Calls glXCreateContext().
GLXContext GLXAPI::xCreateContext(Display *dpy, XVisualInfo *vis,
                                  GLXContext shareList, Bool direct) const
{
    static const char *fnName = "glXCreateContext";

    beforeCommand(fnName, _api.glXCreateContext);
    GLXContext result = _api.glXCreateContext(dpy, vis, shareList, direct);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateGLXPixmap().
GLXPixmap GLXAPI::xCreateGlxPixmap(Display *dpy, XVisualInfo *visual,
                                   Pixmap pixmap) const
{
    static const char *fnName = "glXCreateGLXPixmap";

    beforeCommand(fnName, _api.glXCreateGLXPixmap);
    GLXPixmap result = _api.glXCreateGLXPixmap(dpy, visual, pixmap);
    afterCommand(fnName);

    return result;
}

// Calls glXDestroyContext().
void GLXAPI::xDestroyContext(Display *dpy, GLXContext ctx) const
{
    static const char *fnName = "glXDestroyContext";

    beforeCommand(fnName, _api.glXDestroyContext);
    _api.glXDestroyContext(dpy, ctx);
    afterCommand(fnName);
}

// Calls glXDestroyGLXPixmap().
void GLXAPI::xDestroyGlxPixmap(Display *dpy, GLXPixmap pixmap) const
{
    static const char *fnName = "glXDestroyGLXPixmap";

    beforeCommand(fnName, _api.glXDestroyGLXPixmap);
    _api.glXDestroyGLXPixmap(dpy, pixmap);
    afterCommand(fnName);
}

// Calls glXGetConfig().
int GLXAPI::xGetConfig(Display *dpy, XVisualInfo *visual, int attrib, int *value) const
{
    static const char *fnName = "glXGetConfig";

    beforeCommand(fnName, _api.glXGetConfig);
    int result = _api.glXGetConfig(dpy, visual, attrib, value);
    afterCommand(fnName);

    return result;
}

// Calls glXGetCurrentContext().
GLXContext GLXAPI::xGetCurrentContext() const
{
    static const char *fnName = "glXGetCurrentContext";

    beforeCommand(fnName, _api.glXGetCurrentContext);
    GLXContext result = _api.glXGetCurrentContext();
    afterCommand(fnName);

    return result;
}

// Calls glXGetCurrentDrawable().
GLXDrawable GLXAPI::xGetCurrentDrawable() const
{
    static const char *fnName = "glXGetCurrentDrawable";

    beforeCommand(fnName, _api.glXGetCurrentDrawable);
    GLXDrawable result = _api.glXGetCurrentDrawable();
    afterCommand(fnName);

    return result;
}

// Calls glXIsDirect().
Bool GLXAPI::xIsDirect(Display *dpy, GLXContext ctx) const
{
    static const char *fnName = "glXIsDirect";

    beforeCommand(fnName, _api.glXIsDirect);
    Bool result = _api.glXIsDirect(dpy, ctx);
    afterCommand(fnName);

    return result;
}

// Calls glXMakeCurrent().
Bool GLXAPI::xMakeCurrent(Display *dpy, GLXDrawable drawable, GLXContext ctx) const
{
    static const char *fnName = "glXMakeCurrent";

    beforeCommand(fnName, _api.glXMakeCurrent);
    Bool result = _api.glXMakeCurrent(dpy, drawable, ctx);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryExtension().
Bool GLXAPI::xQueryExtension(Display *dpy, int *errorb, int *event) const
{
    static const char *fnName = "glXQueryExtension";

    beforeCommand(fnName, _api.glXQueryExtension);
    Bool result = _api.glXQueryExtension(dpy, errorb, event);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryVersion().
Bool GLXAPI::xQueryVersion(Display *dpy, int *maj, int *min) const
{
    static const char *fnName = "glXQueryVersion";

    beforeCommand(fnName, _api.glXQueryVersion);
    Bool result = _api.glXQueryVersion(dpy, maj, min);
    afterCommand(fnName);

    return result;
}

// Calls glXSwapBuffers().
void GLXAPI::xSwapBuffers(Display *dpy, GLXDrawable drawable) const
{
    static const char *fnName = "glXSwapBuffers";

    beforeCommand(fnName, _api.glXSwapBuffers);
    _api.glXSwapBuffers(dpy, drawable);
    afterCommand(fnName);
}

// Calls glXUseXFont().
void GLXAPI::xUseXFont(Font font, int first, int count, int list) const
{
    static const char *fnName = "glXUseXFont";

    beforeCommand(fnName, _api.glXUseXFont);
    _api.glXUseXFont(font, first, count, list);
    afterCommand(fnName);
}

// Calls glXWaitGL().
void GLXAPI::xWaitGl() const
{
    static const char *fnName = "glXWaitGL";

    beforeCommand(fnName, _api.glXWaitGL);
    _api.glXWaitGL();
    afterCommand(fnName);
}

// Calls glXWaitX().
void GLXAPI::xWaitX() const
{
    static const char *fnName = "glXWaitX";

    beforeCommand(fnName, _api.glXWaitX);
    _api.glXWaitX();
    afterCommand(fnName);
}

// Calls glXGetClientString().
const char *GLXAPI::xGetClientString(Display *dpy, int name) const
{
    static const char *fnName = "glXGetClientString";

    beforeCommand(fnName, _api.glXGetClientString);
    const char *result = _api.glXGetClientString(dpy, name);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryExtensionsString().
const char *GLXAPI::xQueryExtensionsString(Display *dpy, int screen) const
{
    static const char *fnName = "glXQueryExtensionsString";

    beforeCommand(fnName, _api.glXQueryExtensionsString);
    const char *result = _api.glXQueryExtensionsString(dpy, screen);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryServerString().
const char *GLXAPI::xQueryServerString(Display *dpy, int screen, int name) const
{
    static const char *fnName = "glXQueryServerString";

    beforeCommand(fnName, _api.glXQueryServerString);
    const char *result = _api.glXQueryServerString(dpy, screen, name);
    afterCommand(fnName);

    return result;
}

// Calls glXGetCurrentDisplay().
Display *GLXAPI::xGetCurrentDisplay() const
{
    static const char *fnName = "glXGetCurrentDisplay";

    beforeCommand(fnName, _api.glXGetCurrentDisplay);
    Display *result = _api.glXGetCurrentDisplay();
    afterCommand(fnName);

    return result;
}

// Calls glXChooseFBConfig().
GLXFBConfig *GLXAPI::xChooseFBConfig(Display *dpy, int screen,
                                     const int *attrib_list, int *nelements) const
{
    static const char *fnName = "glXChooseFBConfig";

    beforeCommand(fnName, _api.glXChooseFBConfig);
    GLXFBConfig *result = _api.glXChooseFBConfig(dpy, screen, attrib_list,
                                                 nelements);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateNewContext().
GLXContext GLXAPI::xCreateNewContext(Display *dpy, GLXFBConfig config,
                                     int render_type, GLXContext share_list,
                                     Bool direct) const
{
    static const char *fnName = "glXCreateNewContext";

    beforeCommand(fnName, _api.glXCreateNewContext);
    GLXContext result = _api.glXCreateNewContext(dpy, config, render_type,
                                                 share_list, direct);
    afterCommand(fnName);

    return result;
}

// Calls glXCreatePbuffer().
GLXPbuffer GLXAPI::xCreatePbuffer(Display *dpy, GLXFBConfig config,
                                  const int *attrib_list) const
{
    static const char *fnName = "glXCreatePbuffer";

    beforeCommand(fnName, _api.glXCreatePbuffer);
    GLXPbuffer result = _api.glXCreatePbuffer(dpy, config, attrib_list);
    afterCommand(fnName);

    return result;
}

// Calls glXCreatePixmap().
GLXPixmap GLXAPI::xCreatePixmap(Display *dpy, GLXFBConfig config, Pixmap pixmap,
                                const int *attrib_list) const
{
    static const char *fnName = "glXCreatePixmap";

    beforeCommand(fnName, _api.glXCreatePixmap);
    GLXPixmap result = _api.glXCreatePixmap(dpy, config, pixmap, attrib_list);
    afterCommand(fnName);

    return result;
}

// Calls glXCreateWindow().
GLXWindow GLXAPI::xCreateWindow(Display *dpy, GLXFBConfig config, Window win,
                                const int *attrib_list) const
{
    static const char *fnName = "glXCreateWindow";

    beforeCommand(fnName, _api.glXCreateWindow);
    GLXWindow result = _api.glXCreateWindow(dpy, config, win, attrib_list);
    afterCommand(fnName);

    return result;
}

// Calls glXDestroyPbuffer().
void GLXAPI::xDestroyPbuffer(Display *dpy, GLXPbuffer pbuf) const
{
    static const char *fnName = "glXDestroyPbuffer";

    beforeCommand(fnName, _api.glXDestroyPbuffer);
    _api.glXDestroyPbuffer(dpy, pbuf);
    afterCommand(fnName);
}

// Calls glXDestroyPixmap().
void GLXAPI::xDestroyPixmap(Display *dpy, GLXPixmap pixmap) const
{
    static const char *fnName = "glXDestroyPixmap";

    beforeCommand(fnName, _api.glXDestroyPixmap);
    _api.glXDestroyPixmap(dpy, pixmap);
    afterCommand(fnName);
}

// Calls glXDestroyWindow().
void GLXAPI::xDestroyWindow(Display *dpy, GLXWindow win) const
{
    static const char *fnName = "glXDestroyWindow";

    beforeCommand(fnName, _api.glXDestroyWindow);
    _api.glXDestroyWindow(dpy, win);
    afterCommand(fnName);
}

// Calls glXGetCurrentReadDrawable().
GLXDrawable GLXAPI::xGetCurrentReadDrawable() const
{
    static const char *fnName = "glXGetCurrentReadDrawable";

    beforeCommand(fnName, _api.glXGetCurrentReadDrawable);
    GLXDrawable result = _api.glXGetCurrentReadDrawable();
    afterCommand(fnName);

    return result;
}

// Calls glXGetFBConfigAttrib().
int GLXAPI::xGetFBConfigAttrib(Display *dpy, GLXFBConfig config, int attribute,
                               int *value) const
{
    static const char *fnName = "glXGetFBConfigAttrib";

    beforeCommand(fnName, _api.glXGetFBConfigAttrib);
    int result = _api.glXGetFBConfigAttrib(dpy, config, attribute, value);
    afterCommand(fnName);

    return result;
}

// Calls glXGetFBConfigs().
GLXFBConfig *GLXAPI::xGetFBConfigs(Display *dpy, int screen, int *nelements) const
{
    static const char *fnName = "glXGetFBConfigs";

    beforeCommand(fnName, _api.glXGetFBConfigs);
    GLXFBConfig *result = _api.glXGetFBConfigs(dpy, screen, nelements);
    afterCommand(fnName);

    return result;
}

// Calls glXGetSelectedEvent().
void GLXAPI::xGetSelectedEvent(Display *dpy, GLXDrawable draw,
                               unsigned long *event_mask) const
{
    static const char *fnName = "glXGetSelectedEvent";

    beforeCommand(fnName, _api.glXGetSelectedEvent);
    _api.glXGetSelectedEvent(dpy, draw, event_mask);
    afterCommand(fnName);
}

// Calls glXGetVisualFromFBConfig().
XVisualInfo *GLXAPI::xGetVisualFromFBConfig(Display *dpy, GLXFBConfig config) const
{
    static const char *fnName = "glXGetVisualFromFBConfig";

    beforeCommand(fnName, _api.glXGetVisualFromFBConfig);
    XVisualInfo *result = _api.glXGetVisualFromFBConfig(dpy, config);
    afterCommand(fnName);

    return result;
}

// Calls glXMakeContextCurrent().
Bool GLXAPI::xMakeContextCurrent(Display *dpy, GLXDrawable draw,
                                 GLXDrawable read, GLXContext ctx) const
{
    static const char *fnName = "glXMakeContextCurrent";

    beforeCommand(fnName, _api.glXMakeContextCurrent);
    Bool result = _api.glXMakeContextCurrent(dpy, draw, read, ctx);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryContext().
int GLXAPI::xQueryContext(Display *dpy, GLXContext ctx, int attribute,
                          int *value) const
{
    static const char *fnName = "glXQueryContext";

    beforeCommand(fnName, _api.glXQueryContext);
    int result = _api.glXQueryContext(dpy, ctx, attribute, value);
    afterCommand(fnName);

    return result;
}

// Calls glXQueryDrawable().
void GLXAPI::xQueryDrawable(Display *dpy, GLXDrawable draw, int attribute,
                            unsigned int *value) const
{
    static const char *fnName = "glXQueryDrawable";

    beforeCommand(fnName, _api.glXQueryDrawable);
    _api.glXQueryDrawable(dpy, draw, attribute, value);
    afterCommand(fnName);
}

// Calls glXSelectEvent().
void GLXAPI::xSelectEvent(Display *dpy, GLXDrawable draw,
                          unsigned long event_mask) const
{
    static const char *fnName = "glXSelectEvent";

    beforeCommand(fnName, _api.glXSelectEvent);
    _api.glXSelectEvent(dpy, draw, event_mask);
    afterCommand(fnName);
}

// Calls glXGetProcAddress().
__GLXextFuncPtr GLXAPI::xGetProcAddress(const GLubyte *procName) const
{
    static const char *fnName = "glXGetProcAddress";

    beforeCommand(fnName, _api.glXGetProcAddress);
    __GLXextFuncPtr result = _api.glXGetProcAddress(procName);
    afterCommand(fnName);

    return result;
}

} // namespace glx

