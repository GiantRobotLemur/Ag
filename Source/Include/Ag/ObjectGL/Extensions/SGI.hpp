//! @file Ag/ObjectGL/Extensions/SGI.hpp
//! @brief The declaration of Silicon Graphics-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_SGI_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_SGI_EXTENSIONS_HPP__

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
// GL_SGIS_detail_texture extension API specification.
struct SGISDetailTexture {
    // Public Members
    void (APIENTRY *glDetailTexFunc)(GLenum target, GLsizei n,
                                     const GLfloat *points);
    void (APIENTRY *glGetDetailTexFunc)(GLenum target, GLfloat *points);

    // Construction
    SGISDetailTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISDetailTexture

// GL_SGIS_fog_function extension API specification.
struct SGISFogFunction {
    // Public Members
    void (APIENTRY *glFogFunc)(GLsizei n, const GLfloat *points);
    void (APIENTRY *glGetFogFunc)(GLfloat *points);

    // Construction
    SGISFogFunction();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISFogFunction

// GL_SGIS_multisample extension API specification.
struct SGISMultisample {
    // Public Members
    void (APIENTRY *glSampleMask)(GLclampf value, GLboolean invert);
    void (APIENTRY *glSamplePattern)(GLenum pattern);

    // Construction
    SGISMultisample();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISMultisample

// GL_SGIS_pixel_texture extension API specification.
struct SGISPixelTexture {
    // Public Members
    void (APIENTRY *glGetPixelTexGenParameterfv)(GLenum pname, GLfloat *params);
    void (APIENTRY *glGetPixelTexGenParameteriv)(GLenum pname, GLint *params);
    void (APIENTRY *glPixelTexGenParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPixelTexGenParameterfv)(GLenum pname,
                                              const GLfloat *params);
    void (APIENTRY *glPixelTexGenParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glPixelTexGenParameteriv)(GLenum pname, const GLint *params);

    // Construction
    SGISPixelTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISPixelTexture

// GL_SGIS_point_parameters extension API specification.
struct SGISPointParameters {
    // Public Members
    void (APIENTRY *glPointParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glPointParameterfv)(GLenum pname, const GLfloat *params);

    // Construction
    SGISPointParameters();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISPointParameters

// GL_SGIS_sharpen_texture extension API specification.
struct SGISSharpenTexture {
    // Public Members
    void (APIENTRY *glGetSharpenTexFunc)(GLenum target, GLfloat *points);
    void (APIENTRY *glSharpenTexFunc)(GLenum target, GLsizei n,
                                      const GLfloat *points);

    // Construction
    SGISSharpenTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISSharpenTexture

// GL_SGIS_texture4D extension API specification.
struct SGISTEXTURE4D {
    // Public Members
    void (APIENTRY *glTexImage4D)(GLenum target, GLint level,
                                  GLenum internalformat, GLsizei width,
                                  GLsizei height, GLsizei depth, GLsizei size4d,
                                  GLint border, GLenum format, GLenum type,
                                  const void *pixels);
    void (APIENTRY *glTexSubImage4D)(GLenum target, GLint level, GLint xoffset,
                                     GLint yoffset, GLint zoffset, GLint woffset,
                                     GLsizei width, GLsizei height,
                                     GLsizei depth, GLsizei size4d,
                                     GLenum format, GLenum type,
                                     const void *pixels);

    // Construction
    SGISTEXTURE4D();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISTEXTURE4D

// GL_SGIS_texture_color_mask extension API specification.
struct SGISTextureColorMask {
    // Public Members
    void (APIENTRY *glTextureColorMask)(GLboolean red, GLboolean green,
                                        GLboolean blue, GLboolean alpha);

    // Construction
    SGISTextureColorMask();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISTextureColorMask

// GL_SGIS_texture_filter4 extension API specification.
struct SGISTextureFILTER4 {
    // Public Members
    void (APIENTRY *glGetTexFilterFunc)(GLenum target, GLenum filter,
                                        GLfloat *weights);
    void (APIENTRY *glTexFilterFunc)(GLenum target, GLenum filter, GLsizei n,
                                     const GLfloat *weights);

    // Construction
    SGISTextureFILTER4();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGISTextureFILTER4

// GL_SGIX_async extension API specification.
struct SGIXAsync {
    // Public Members
    void (APIENTRY *glAsyncMarker)(GLuint marker);
    void (APIENTRY *glDeleteAsyncMarkers)(GLuint marker, GLsizei range);
    GLint(APIENTRY *glFinishAsync)(GLuint *markerp);
    GLuint(APIENTRY *glGenAsyncMarkers)(GLsizei range);
    GLboolean(APIENTRY *glIsAsyncMarker)(GLuint marker);
    GLint(APIENTRY *glPollAsync)(GLuint *markerp);

    // Construction
    SGIXAsync();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXAsync

// GL_SGIX_flush_raster extension API specification.
struct SGIXFlushRaster {
    // Public Members
    void (APIENTRY *glFlushRaster)();

    // Construction
    SGIXFlushRaster();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXFlushRaster

// GL_SGIX_fragment_lighting extension API specification.
// Incomplete extension
struct SGIXFragmentLighting {
    // Public Members
    void (APIENTRY *glFragmentColorMaterial)(GLenum face, GLenum mode);
    void (APIENTRY *glFragmentLightModelf)(GLenum pname, GLfloat param);
    void (APIENTRY *glFragmentLightModelfv)(GLenum pname, const GLfloat *params);
    void (APIENTRY *glFragmentLightModeli)(GLenum pname, GLint param);
    void (APIENTRY *glFragmentLightModeliv)(GLenum pname, const GLint *params);
    void (APIENTRY *glFragmentLightf)(GLenum light, GLenum pname, GLfloat param);
    void (APIENTRY *glFragmentLightfv)(GLenum light, GLenum pname,
                                       const GLfloat *params);
    void (APIENTRY *glFragmentLighti)(GLenum light, GLenum pname, GLint param);
    void (APIENTRY *glFragmentLightiv)(GLenum light, GLenum pname,
                                       const GLint *params);
    void (APIENTRY *glFragmentMaterialf)(GLenum face, GLenum pname,
                                         GLfloat param);
    void (APIENTRY *glFragmentMaterialfv)(GLenum face, GLenum pname,
                                          const GLfloat *params);
    void (APIENTRY *glFragmentMateriali)(GLenum face, GLenum pname, GLint param);
    void (APIENTRY *glFragmentMaterialiv)(GLenum face, GLenum pname,
                                          const GLint *params);
    void (APIENTRY *glGetFragmentLightfv)(GLenum light, GLenum pname,
                                          GLfloat *params);
    void (APIENTRY *glGetFragmentLightiv)(GLenum light, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glGetFragmentMaterialfv)(GLenum face, GLenum pname,
                                             GLfloat *params);
    void (APIENTRY *glGetFragmentMaterialiv)(GLenum face, GLenum pname,
                                             GLint *params);
    void (APIENTRY *glLightEnvi)(GLenum pname, GLint param);

    // Construction
    SGIXFragmentLighting();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXFragmentLighting

// GL_SGIX_framezoom extension API specification.
struct SGIXFramezoom {
    // Public Members
    void (APIENTRY *glFrameZoom)(GLint factor);

    // Construction
    SGIXFramezoom();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXFramezoom

// GL_SGIX_igloo_interface extension API specification.
struct SGIXIglooInterface {
    // Public Members
    void (APIENTRY *glIglooInterface)(GLenum pname, const void *params);

    // Construction
    SGIXIglooInterface();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXIglooInterface

// GL_SGIX_instruments extension API specification.
struct SGIXInstrumentS {
    // Public Members
    GLint(APIENTRY *glGetInstruments)();
    void (APIENTRY *glInstrumentsBuffer)(GLsizei size, GLint *buffer);
    GLint(APIENTRY *glPollInstruments)(GLint *marker_p);
    void (APIENTRY *glReadInstruments)(GLint marker);
    void (APIENTRY *glStartInstruments)();
    void (APIENTRY *glStopInstruments)(GLint marker);

    // Construction
    SGIXInstrumentS();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXInstrumentS

// GL_SGIX_list_priority extension API specification.
struct SGIXListPriority {
    // Public Members
    void (APIENTRY *glGetListParameterfv)(GLuint list, GLenum pname,
                                          GLfloat *params);
    void (APIENTRY *glGetListParameteriv)(GLuint list, GLenum pname,
                                          GLint *params);
    void (APIENTRY *glListParameterf)(GLuint list, GLenum pname, GLfloat param);
    void (APIENTRY *glListParameterfv)(GLuint list, GLenum pname,
                                       const GLfloat *params);
    void (APIENTRY *glListParameteri)(GLuint list, GLenum pname, GLint param);
    void (APIENTRY *glListParameteriv)(GLuint list, GLenum pname,
                                       const GLint *params);

    // Construction
    SGIXListPriority();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXListPriority

// GL_SGIX_pixel_texture extension API specification.
struct SGIXPixelTexture {
    // Public Members
    void (APIENTRY *glPixelTexGen)(GLenum mode);

    // Construction
    SGIXPixelTexture();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXPixelTexture

// GL_SGIX_polynomial_ffd extension API specification.
struct SGIXPolynomialFfd {
    // Public Members
    void (APIENTRY *glDeform)(GLbitfield mask);
    void (APIENTRY *glDeformationMap3d)(GLenum target, GLdouble u1, GLdouble u2,
                                        GLint ustride, GLint uorder, GLdouble v1,
                                        GLdouble v2, GLint vstride, GLint vorder,
                                        GLdouble w1, GLdouble w2, GLint wstride,
                                        GLint worder, const GLdouble *points);
    void (APIENTRY *glDeformationMap3f)(GLenum target, GLfloat u1, GLfloat u2,
                                        GLint ustride, GLint uorder, GLfloat v1,
                                        GLfloat v2, GLint vstride, GLint vorder,
                                        GLfloat w1, GLfloat w2, GLint wstride,
                                        GLint worder, const GLfloat *points);
    void (APIENTRY *glLoadIdentityDeformationMap)(GLbitfield mask);

    // Construction
    SGIXPolynomialFfd();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXPolynomialFfd

// GL_SGIX_reference_plane extension API specification.
struct SGIXReferencePlane {
    // Public Members
    void (APIENTRY *glReferencePlane)(const GLdouble *equation);

    // Construction
    SGIXReferencePlane();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXReferencePlane

// GL_SGIX_sprite extension API specification.
struct SGIXSprite {
    // Public Members
    void (APIENTRY *glSpriteParameterf)(GLenum pname, GLfloat param);
    void (APIENTRY *glSpriteParameterfv)(GLenum pname, const GLfloat *params);
    void (APIENTRY *glSpriteParameteri)(GLenum pname, GLint param);
    void (APIENTRY *glSpriteParameteriv)(GLenum pname, const GLint *params);

    // Construction
    SGIXSprite();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXSprite

// GL_SGIX_tag_sample_buffer extension API specification.
struct SGIXTagSampleBuffer {
    // Public Members
    void (APIENTRY *glTagSampleBuffer)();

    // Construction
    SGIXTagSampleBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXTagSampleBuffer

// GL_SGI_color_table extension API specification.
struct SGIColorTable {
    // Public Members
    void (APIENTRY *glColorTableParameterfv)(GLenum target, GLenum pname,
                                             const GLfloat *params);
    void (APIENTRY *glColorTableParameteriv)(GLenum target, GLenum pname,
                                             const GLint *params);
    void (APIENTRY *glColorTable)(GLenum target, GLenum internalformat,
                                  GLsizei width, GLenum format, GLenum type,
                                  const void *table);
    void (APIENTRY *glCopyColorTable)(GLenum target, GLenum internalformat,
                                      GLint x, GLint y, GLsizei width);
    void (APIENTRY *glGetColorTableParameterfv)(GLenum target, GLenum pname,
                                                GLfloat *params);
    void (APIENTRY *glGetColorTableParameteriv)(GLenum target, GLenum pname,
                                                GLint *params);
    void (APIENTRY *glGetColorTable)(GLenum target, GLenum format, GLenum type,
                                     void *table);

    // Construction
    SGIColorTable();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIColorTable

} // namespace gl


#ifdef _USES_GLX
namespace glx {

// GLX_SGIX_dmbuffer extension API specification.
struct SGIXDmbuffer {
    // Public Members
    Bool(APIENTRY *glXAssociateDMPbuffer)(Display *dpy, GLXPbufferSGIX pbuffer,
                                          DMparams *params, DMbuffer dmbuffer);

   // Construction
    SGIXDmbuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXDmbuffer

// GLX_SGIX_fbconfig extension API specification.
struct SGIXFbconfig {
    // Public Members
    GLXFBConfigSGIX *(APIENTRY *glXChooseFBConfig)(Display *dpy, int screen,
                                                   int *attrib_list,
                                                   int *nelements);
    GLXContext(APIENTRY *glXCreateContextWithConfig)(Display *dpy,
                                                     GLXFBConfigSGIX config,
                                                     int render_type,
                                                     GLXContext share_list,
                                                     Bool direct);
    GLXPixmap(APIENTRY *glXCreateGLXPixmapWithConfig)(Display *dpy,
                                                      GLXFBConfigSGIX config,
                                                      Pixmap pixmap);
    int (APIENTRY *glXGetFBConfigAttrib)(Display *dpy, GLXFBConfigSGIX config,
                                         int attribute, int *value);
    GLXFBConfigSGIX(APIENTRY *glXGetFBConfigFromVisual)(Display *dpy,
                                                        XVisualInfo *vis);
    XVisualInfo *(APIENTRY *glXGetVisualFromFBConfig)(Display *dpy,
                                                      GLXFBConfigSGIX config);

    // Construction
    SGIXFbconfig();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXFbconfig

// GLX_SGIX_hyperpipe extension API specification.
struct SGIXHyperpipe {
    // Public Members
    int (APIENTRY *glXBindHyperpipe)(Display *dpy, int hpId);
    int (APIENTRY *glXDestroyHyperpipeConfig)(Display *dpy, int hpId);
    int (APIENTRY *glXHyperpipeAttrib)(Display *dpy, int timeSlice, int attrib,
                                       int size, void *attribList);
    int (APIENTRY *glXHyperpipeConfig)(Display *dpy, int networkId, int npipes,
                                       GLXHyperpipeConfigSGIX *cfg, int *hpId);
    int (APIENTRY *glXQueryHyperpipeAttrib)(Display *dpy, int timeSlice,
                                            int attrib, int size,
                                            void *returnAttribList);
    int (APIENTRY *glXQueryHyperpipeBestAttrib)(Display *dpy, int timeSlice,
                                                int attrib, int size,
                                                void *attribList,
                                                void *returnAttribList);
    GLXHyperpipeConfigSGIX *(APIENTRY *glXQueryHyperpipeConfig)(Display *dpy,
                                                                int hpId,
                                                                int *npipes);
    GLXHyperpipeNetworkSGIX *(APIENTRY *glXQueryHyperpipeNetwork)(Display *dpy,
                                                                  int *npipes);

    // Construction
    SGIXHyperpipe();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXHyperpipe

// GLX_SGIX_pbuffer extension API specification.
struct SGIXPbuffer {
    // Public Members
    GLXPbufferSGIX(APIENTRY *glXCreateGLXPbuffer)(Display *dpy,
                                                  GLXFBConfigSGIX config,
                                                  unsigned int width,
                                                  unsigned int height,
                                                  int *attrib_list);
    void (APIENTRY *glXDestroyGLXPbuffer)(Display *dpy, GLXPbufferSGIX pbuf);
    void (APIENTRY *glXGetSelectedEvent)(Display *dpy, GLXDrawable drawable,
                                         unsigned long *mask);
    void (APIENTRY *glXQueryGLXPbuffer)(Display *dpy, GLXPbufferSGIX pbuf,
                                        int attribute, unsigned int *value);
    void (APIENTRY *glXSelectEvent)(Display *dpy, GLXDrawable drawable,
                                    unsigned long mask);

    // Construction
    SGIXPbuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXPbuffer

// GLX_SGIX_swap_barrier extension API specification.
struct SGIXSwapBarrier {
    // Public Members
    void (APIENTRY *glXBindSwapBarrier)(Display *dpy, GLXDrawable drawable,
                                        int barrier);
    Bool(APIENTRY *glXQueryMaxSwapBarriers)(Display *dpy, int screen, int *max);

    // Construction
    SGIXSwapBarrier();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXSwapBarrier

// GLX_SGIX_swap_group extension API specification.
struct SGIXSwapGroup {
    // Public Members
    void (APIENTRY *glXJoinSwapGroup)(Display *dpy, GLXDrawable drawable,
                                      GLXDrawable member);

    // Construction
    SGIXSwapGroup();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXSwapGroup

// GLX_SGIX_video_resize extension API specification.
struct SGIXVideoResize {
    // Public Members
    int (APIENTRY *glXBindChannelToWindow)(Display *display, int screen,
                                           int channel, Window window);
    int (APIENTRY *glXChannelRect)(Display *display, int screen, int channel,
                                   int x, int y, int w, int h);
    int (APIENTRY *glXChannelRectSync)(Display *display, int screen, int channel,
                                       GLenum synctype);
    int (APIENTRY *glXQueryChannelDeltas)(Display *display, int screen,
                                          int channel, int *x, int *y, int *w,
                                          int *h);
    int (APIENTRY *glXQueryChannelRect)(Display *display, int screen,
                                        int channel, int *dx, int *dy, int *dw,
                                        int *dh);

    // Construction
    SGIXVideoResize();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXVideoResize

// GLX_SGIX_video_source extension API specification.
struct SGIXVideoSource {
    // Public Members
    GLXVideoSourceSGIX(APIENTRY *glXCreateGLXVideoSource)(Display *display,
                                                          int screen,
                                                          VLServer server,
                                                          VLPath path,
                                                          int nodeClass,
                                                          VLNode drainNode);
    void (APIENTRY *glXDestroyGLXVideoSource)(Display *dpy,
                                              GLXVideoSourceSGIX glxvideosource);

    // Construction
    SGIXVideoSource();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SGIXVideoSource

// GLX_SGI_cushion extension API specification.
struct SgiCushion {
    // Public Members
    void (APIENTRY *glXCushionSGI)(Display *dpy, Window window, float cushion);

    // Construction
    SgiCushion();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SgiCushion

// GLX_SGI_make_current_read extension API specification.
struct SgiMakeCurrentRead {
    // Public Members
    GLXDrawable(APIENTRY *glXGetCurrentReadDrawableSGI)();
    Bool(APIENTRY *glXMakeCurrentReadSGI)(Display *dpy, GLXDrawable draw,
                                          GLXDrawable read, GLXContext ctx);

   // Construction
    SgiMakeCurrentRead();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SgiMakeCurrentRead

// GLX_SGI_swap_control extension API specification.
struct SgiSwapControl {
    // Public Members
    int (APIENTRY *glXSwapIntervalSGI)(int interval);

    // Construction
    SgiSwapControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SgiSwapControl

// GLX_SGI_video_sync extension API specification.
struct SgiVideoSync {
    // Public Members
    int (APIENTRY *glXGetVideoSyncSGI)(unsigned int *count);
    int (APIENTRY *glXWaitVideoSyncSGI)(int divisor, int remainder,
                                        unsigned int *count);

    // Construction
    SgiVideoSync();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct SgiVideoSync

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
