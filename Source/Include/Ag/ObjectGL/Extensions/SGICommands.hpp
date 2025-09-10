//! @file Ag/ObjectGL/Extensions/SGICommands.hpp
//! @brief The declaration of Silicon Graphics-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_SGI_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_SGI_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "SGI.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_SGIS_detail_texture extension API.
class SGISDetailTextureAPI : public BaseExtension
{
public:
    // Construction
    SGISDetailTextureAPI();

    // Accessors
    const SGISDetailTexture &getRawAPI() const;

    // Operations
    void detailTexFunc(TextureTarget target, GLsizei n, const GLfloat *points) const;
    void getDetailTexFunc(TextureTarget target, GLfloat *points) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISDetailTexture _api;
};

// Manages the entry points for the GL_SGIS_fog_function extension API.
class SGISFogFunctionAPI : public BaseExtension
{
public:
    // Construction
    SGISFogFunctionAPI();

    // Accessors
    const SGISFogFunction &getRawAPI() const;

    // Operations
    void fogFunc(GLsizei n, const GLfloat *points) const;
    void getFogFunc(GLfloat *points) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISFogFunction _api;
};

// Manages the entry points for the GL_SGIS_multisample extension API.
class SGISMultisampleAPI : public BaseExtension
{
public:
    // Construction
    SGISMultisampleAPI();

    // Accessors
    const SGISMultisample &getRawAPI() const;

    // Operations
    void sampleMask(GLclampf value, Boolean invert) const;
    void samplePattern(SamplePatternSGIS pattern) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISMultisample _api;
};

// Manages the entry points for the GL_SGIS_pixel_texture extension API.
class SGISPixelTextureAPI : public BaseExtension
{
public:
    // Construction
    SGISPixelTextureAPI();

    // Accessors
    const SGISPixelTexture &getRawAPI() const;

    // Operations
    void getPixelTexGenParameterFV(PixelTexGenParameterNameSGIS pname,
                                   GLfloat *params) const;
    void getPixelTexGenParameterIV(PixelTexGenParameterNameSGIS pname,
                                   GLint *params) const;
    void pixelTexGenParameterF(PixelTexGenParameterNameSGIS pname, GLfloat param) const;
    void pixelTexGenParameterFV(PixelTexGenParameterNameSGIS pname,
                                const GLfloat *params) const;
    void pixelTexGenParameterI(PixelTexGenParameterNameSGIS pname, GLint param) const;
    void pixelTexGenParameterIV(PixelTexGenParameterNameSGIS pname,
                                const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISPixelTexture _api;
};

// Manages the entry points for the GL_SGIS_point_parameters extension API.
class SGISPointParametersAPI : public BaseExtension
{
public:
    // Construction
    SGISPointParametersAPI();

    // Accessors
    const SGISPointParameters &getRawAPI() const;

    // Operations
    void pointParameterF(PointParameterNameARB pname, GLfloat param) const;
    void pointParameterFV(PointParameterNameARB pname, const GLfloat *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISPointParameters _api;
};

// Manages the entry points for the GL_SGIS_sharpen_texture extension API.
class SGISSharpenTextureAPI : public BaseExtension
{
public:
    // Construction
    SGISSharpenTextureAPI();

    // Accessors
    const SGISSharpenTexture &getRawAPI() const;

    // Operations
    void getSharpenTexFunc(TextureTarget target, GLfloat *points) const;
    void sharpenTexFunc(TextureTarget target, GLsizei n, const GLfloat *points) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISSharpenTexture _api;
};

// Manages the entry points for the GL_SGIS_texture4D extension API.
class SGISTEXTURE4DAPI : public BaseExtension
{
public:
    // Construction
    SGISTEXTURE4DAPI();

    // Accessors
    const SGISTEXTURE4D &getRawAPI() const;

    // Operations
    void texImage4D(TextureTarget target, GLint level,
                    InternalFormat internalformat, GLsizei width, GLsizei height,
                    GLsizei depth, GLsizei size4d, GLint border,
                    PixelFormat format, PixelType type, const void *pixels) const;
    void texSubImage4D(TextureTarget target, GLint level, GLint xoffset,
                       GLint yoffset, GLint zoffset, GLint woffset,
                       GLsizei width, GLsizei height, GLsizei depth,
                       GLsizei size4d, PixelFormat format, PixelType type,
                       const void *pixels) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISTEXTURE4D _api;
};

// Manages the entry points for the GL_SGIS_texture_color_mask extension API.
class SGISTextureColorMaskAPI : public BaseExtension
{
public:
    // Construction
    SGISTextureColorMaskAPI();

    // Accessors
    const SGISTextureColorMask &getRawAPI() const;

    // Operations
    void textureColorMask(Boolean red, Boolean green, Boolean blue,
                          Boolean alpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISTextureColorMask _api;
};

// Manages the entry points for the GL_SGIS_texture_filter4 extension API.
class SGISTextureFILTER4API : public BaseExtension
{
public:
    // Construction
    SGISTextureFILTER4API();

    // Accessors
    const SGISTextureFILTER4 &getRawAPI() const;

    // Operations
    void getTexFilterFunc(TextureTarget target, TextureFilterSGIS filter,
                          GLfloat *weights) const;
    void texFilterFunc(TextureTarget target, TextureFilterSGIS filter, GLsizei n,
                       const GLfloat *weights) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGISTextureFILTER4 _api;
};

// Manages the entry points for the GL_SGIX_async extension API.
class SGIXAsyncAPI : public BaseExtension
{
public:
    // Construction
    SGIXAsyncAPI();

    // Accessors
    const SGIXAsync &getRawAPI() const;

    // Operations
    void asyncMarker(GLuint marker) const;
    void deleteAsyncMarkers(GLuint marker, GLsizei range) const;
    GLint finishAsync(GLuint *markerp) const;
    GLuint genAsyncMarkers(GLsizei range) const;
    Boolean isAsyncMarker(GLuint marker) const;
    GLint pollAsync(GLuint *markerp) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXAsync _api;
};

// Manages the entry points for the GL_SGIX_flush_raster extension API.
class SGIXFlushRasterAPI : public BaseExtension
{
public:
    // Construction
    SGIXFlushRasterAPI();

    // Accessors
    const SGIXFlushRaster &getRawAPI() const;

    // Operations
    void flushRaster() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXFlushRaster _api;
};

// Manages the entry points for the GL_SGIX_fragment_lighting extension API.
class SGIXFragmentLightingAPI : public BaseExtension
{
public:
    // Construction
    SGIXFragmentLightingAPI();

    // Accessors
    const SGIXFragmentLighting &getRawAPI() const;

    // Operations
    void fragmentColorMaterial(MaterialFace face, GLenum mode) const;
    void fragmentLightModelF(FragmentLightModelParameterSGIX pname,
                             GLfloat param) const;
    void fragmentLightModelFV(FragmentLightModelParameterSGIX pname,
                              const GLfloat *params) const;
    void fragmentLightModelI(FragmentLightModelParameterSGIX pname, GLint param) const;
    void fragmentLightModelIV(FragmentLightModelParameterSGIX pname,
                              const GLint *params) const;
    void fragmentLightF(FragmentLightNameSGIX light, GLenum pname, GLfloat param) const;
    void fragmentLightFV(FragmentLightNameSGIX light, GLenum pname,
                         const GLfloat *params) const;
    void fragmentLightI(FragmentLightNameSGIX light, GLenum pname, GLint param) const;
    void fragmentLightIV(FragmentLightNameSGIX light, GLenum pname,
                         const GLint *params) const;
    void fragmentMaterialF(MaterialFace face, GLenum pname, GLfloat param) const;
    void fragmentMaterialFV(MaterialFace face, GLenum pname,
                            const GLfloat *params) const;
    void fragmentMaterialI(MaterialFace face, GLenum pname, GLint param) const;
    void fragmentMaterialIV(MaterialFace face, GLenum pname, const GLint *params) const;
    void getFragmentLightFV(FragmentLightNameSGIX light, GLenum pname,
                            GLfloat *params) const;
    void getFragmentLightIV(FragmentLightNameSGIX light, GLenum pname,
                            GLint *params) const;
    void getFragmentMaterialFV(MaterialFace face, GLenum pname, GLfloat *params) const;
    void getFragmentMaterialIV(MaterialFace face, GLenum pname, GLint *params) const;
    void lightEnvI(LightEnvParameterSGIX pname, GLint param) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXFragmentLighting _api;
};

// Manages the entry points for the GL_SGIX_framezoom extension API.
class SGIXFramezoomAPI : public BaseExtension
{
public:
    // Construction
    SGIXFramezoomAPI();

    // Accessors
    const SGIXFramezoom &getRawAPI() const;

    // Operations
    void frameZoom(GLint factor) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXFramezoom _api;
};

// Manages the entry points for the GL_SGIX_igloo_interface extension API.
class SGIXIglooInterfaceAPI : public BaseExtension
{
public:
    // Construction
    SGIXIglooInterfaceAPI();

    // Accessors
    const SGIXIglooInterface &getRawAPI() const;

    // Operations
    void iglooInterface(GLenum pname, const void *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXIglooInterface _api;
};

// Manages the entry points for the GL_SGIX_instruments extension API.
class SGIXInstrumentSAPI : public BaseExtension
{
public:
    // Construction
    SGIXInstrumentSAPI();

    // Accessors
    const SGIXInstrumentS &getRawAPI() const;

    // Operations
    GLint getInstrumentS() const;
    void instrumentSBuffer(GLsizei size, GLint *buffer) const;
    GLint pollInstrumentS(GLint *marker_p) const;
    void readInstrumentS(GLint marker) const;
    void startInstrumentS() const;
    void stopInstrumentS(GLint marker) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXInstrumentS _api;
};

// Manages the entry points for the GL_SGIX_list_priority extension API.
class SGIXListPriorityAPI : public BaseExtension
{
public:
    // Construction
    SGIXListPriorityAPI();

    // Accessors
    const SGIXListPriority &getRawAPI() const;

    // Operations
    void getListParameterFV(GLuint list, ListParameterName pname,
                            GLfloat *params) const;
    void getListParameterIV(GLuint list, ListParameterName pname, GLint *params) const;
    void listParameterF(GLuint list, ListParameterName pname, GLfloat param) const;
    void listParameterFV(GLuint list, ListParameterName pname,
                         const GLfloat *params) const;
    void listParameterI(GLuint list, ListParameterName pname, GLint param) const;
    void listParameterIV(GLuint list, ListParameterName pname,
                         const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXListPriority _api;
};

// Manages the entry points for the GL_SGIX_pixel_texture extension API.
class SGIXPixelTextureAPI : public BaseExtension
{
public:
    // Construction
    SGIXPixelTextureAPI();

    // Accessors
    const SGIXPixelTexture &getRawAPI() const;

    // Operations
    void pixelTexGen(GLenum mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXPixelTexture _api;
};

// Manages the entry points for the GL_SGIX_polynomial_ffd extension API.
class SGIXPolynomialFfdAPI : public BaseExtension
{
public:
    // Construction
    SGIXPolynomialFfdAPI();

    // Accessors
    const SGIXPolynomialFfd &getRawAPI() const;

    // Operations
    void deform(GLbitfield  /* FfdMaskSGIX */ mask) const;
    void deformationMap3D(FfdTargetSGIX target, GLdouble u1, GLdouble u2,
                          GLint ustride, GLint uorder, GLdouble v1, GLdouble v2,
                          GLint vstride, GLint vorder, GLdouble w1, GLdouble w2,
                          GLint wstride, GLint worder, const GLdouble *points) const;
    void deformationMap3F(FfdTargetSGIX target, GLfloat u1, GLfloat u2,
                          GLint ustride, GLint uorder, GLfloat v1, GLfloat v2,
                          GLint vstride, GLint vorder, GLfloat w1, GLfloat w2,
                          GLint wstride, GLint worder, const GLfloat *points) const;
    void loadIdentityDeformationMap(GLbitfield  /* FfdMaskSGIX */ mask) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXPolynomialFfd _api;
};

// Manages the entry points for the GL_SGIX_reference_plane extension API.
class SGIXReferencePlaneAPI : public BaseExtension
{
public:
    // Construction
    SGIXReferencePlaneAPI();

    // Accessors
    const SGIXReferencePlane &getRawAPI() const;

    // Operations
    void referencePlane(const GLdouble *equation) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXReferencePlane _api;
};

// Manages the entry points for the GL_SGIX_sprite extension API.
class SGIXSpriteAPI : public BaseExtension
{
public:
    // Construction
    SGIXSpriteAPI();

    // Accessors
    const SGIXSprite &getRawAPI() const;

    // Operations
    void spriteParameterF(SpriteParameterNameSGIX pname, GLfloat param) const;
    void spriteParameterFV(SpriteParameterNameSGIX pname, const GLfloat *params) const;
    void spriteParameterI(SpriteParameterNameSGIX pname, GLint param) const;
    void spriteParameterIV(SpriteParameterNameSGIX pname, const GLint *params) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXSprite _api;
};

// Manages the entry points for the GL_SGIX_tag_sample_buffer extension API.
class SGIXTagSampleBufferAPI : public BaseExtension
{
public:
    // Construction
    SGIXTagSampleBufferAPI();

    // Accessors
    const SGIXTagSampleBuffer &getRawAPI() const;

    // Operations
    void tagSampleBuffer() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXTagSampleBuffer _api;
};

// Manages the entry points for the GL_SGI_color_table extension API.
class SGIColorTableAPI : public BaseExtension
{
public:
    // Construction
    SGIColorTableAPI();

    // Accessors
    const SGIColorTable &getRawAPI() const;

    // Operations
    void colorTableParameterFV(ColorTableTargetSGI target,
                               ColorTableParameterPNameSGI pname,
                               const GLfloat *params) const;
    void colorTableParameterIV(ColorTableTargetSGI target,
                               ColorTableParameterPNameSGI pname,
                               const GLint *params) const;
    void colorTable(ColorTableTargetSGI target, InternalFormat internalformat,
                    GLsizei width, PixelFormat format, PixelType type,
                    const void *table) const;
    void copyColorTable(ColorTableTargetSGI target,
                        InternalFormat internalformat, GLint x, GLint y,
                        GLsizei width) const;
    void getColorTableParameterFV(ColorTableTargetSGI target,
                                  GetColorTableParameterPNameSGI pname,
                                  GLfloat *params) const;
    void getColorTableParameterIV(ColorTableTargetSGI target,
                                  GetColorTableParameterPNameSGI pname,
                                  GLint *params) const;
    void getColorTable(ColorTableTargetSGI target, PixelFormat format,
                       PixelType type, void *table) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIColorTable _api;
};

} // namespace gl


#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_SGIX_dmbuffer extension API.
class SGIXDmbufferAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXDmbufferAPI();

    // Accessors
    const SGIXDmbuffer &getRawAPI() const;

    // Operations
    Bool xAssociateDmPbuffer(Display *dpy, GLXPbufferSGIX pbuffer,
                             DMparams *params, DMbuffer dmbuffer) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXDmbuffer _api;
};

// Manages the entry points for the GLX_SGIX_fbconfig extension API.
class SGIXFbconfigAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXFbconfigAPI();

    // Accessors
    const SGIXFbconfig &getRawAPI() const;

    // Operations
    GLXFBConfigSGIX *xChooseFBConfig(Display *dpy, int screen, int *attrib_list,
                                     int *nelements) const;
    GLXContext xCreateContextWithConfig(Display *dpy, GLXFBConfigSGIX config,
                                        int render_type, GLXContext share_list,
                                        Bool direct) const;
    GLXPixmap xCreateGlxPixmapWithConfig(Display *dpy, GLXFBConfigSGIX config,
                                         Pixmap pixmap) const;
    int xGetFBConfigAttrib(Display *dpy, GLXFBConfigSGIX config, int attribute,
                           int *value) const;
    GLXFBConfigSGIX xGetFBConfigFromVisual(Display *dpy, XVisualInfo *vis) const;
    XVisualInfo *xGetVisualFromFBConfig(Display *dpy, GLXFBConfigSGIX config) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXFbconfig _api;
};

// Manages the entry points for the GLX_SGIX_hyperpipe extension API.
class SGIXHyperpipeAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXHyperpipeAPI();

    // Accessors
    const SGIXHyperpipe &getRawAPI() const;

    // Operations
    int xBindHyperpipe(Display *dpy, int hpId) const;
    int xDestroyHyperpipeConfig(Display *dpy, int hpId) const;
    int xHyperpipeAttrib(Display *dpy, int timeSlice, int attrib, int size,
                         void *attribList) const;
    int xHyperpipeConfig(Display *dpy, int networkId, int npipes,
                         GLXHyperpipeConfigSGIX *cfg, int *hpId) const;
    int xQueryHyperpipeAttrib(Display *dpy, int timeSlice, int attrib, int size,
                              void *returnAttribList) const;
    int xQueryHyperpipeBestAttrib(Display *dpy, int timeSlice, int attrib,
                                  int size, void *attribList,
                                  void *returnAttribList) const;
    GLXHyperpipeConfigSGIX *xQueryHyperpipeConfig(Display *dpy, int hpId,
                                                  int *npipes) const;
    GLXHyperpipeNetworkSGIX *xQueryHyperpipeNetwork(Display *dpy, int *npipes) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXHyperpipe _api;
};

// Manages the entry points for the GLX_SGIX_pbuffer extension API.
class SGIXPbufferAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXPbufferAPI();

    // Accessors
    const SGIXPbuffer &getRawAPI() const;

    // Operations
    GLXPbufferSGIX xCreateGlxPbuffer(Display *dpy, GLXFBConfigSGIX config,
                                     unsigned int width, unsigned int height,
                                     int *attrib_list) const;
    void xDestroyGlxPbuffer(Display *dpy, GLXPbufferSGIX pbuf) const;
    void xGetSelectedEvent(Display *dpy, GLXDrawable drawable,
                           unsigned long *mask) const;
    void xQueryGlxPbuffer(Display *dpy, GLXPbufferSGIX pbuf, int attribute,
                          unsigned int *value) const;
    void xSelectEvent(Display *dpy, GLXDrawable drawable, unsigned long mask) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXPbuffer _api;
};

// Manages the entry points for the GLX_SGIX_swap_barrier extension API.
class SGIXSwapBarrierAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXSwapBarrierAPI();

    // Accessors
    const SGIXSwapBarrier &getRawAPI() const;

    // Operations
    void xBindSwapBarrier(Display *dpy, GLXDrawable drawable, int barrier) const;
    Bool xQueryMaxSwapBarriers(Display *dpy, int screen, int *max) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXSwapBarrier _api;
};

// Manages the entry points for the GLX_SGIX_swap_group extension API.
class SGIXSwapGroupAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXSwapGroupAPI();

    // Accessors
    const SGIXSwapGroup &getRawAPI() const;

    // Operations
    void xJoinSwapGroup(Display *dpy, GLXDrawable drawable, GLXDrawable member) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXSwapGroup _api;
};

// Manages the entry points for the GLX_SGIX_video_resize extension API.
class SGIXVideoResizeAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXVideoResizeAPI();

    // Accessors
    const SGIXVideoResize &getRawAPI() const;

    // Operations
    int xBindChannelToWindow(Display *display, int screen, int channel,
                             Window window) const;
    int xChannelRect(Display *display, int screen, int channel, int x, int y,
                     int w, int h) const;
    int xChannelRectSync(Display *display, int screen, int channel,
                         GLenum synctype) const;
    int xQueryChannelDeltas(Display *display, int screen, int channel, int *x,
                            int *y, int *w, int *h) const;
    int xQueryChannelRect(Display *display, int screen, int channel, int *dx,
                          int *dy, int *dw, int *dh) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXVideoResize _api;
};

// Manages the entry points for the GLX_SGIX_video_source extension API.
class SGIXVideoSourceAPI : public gl::BaseExtension
{
public:
    // Construction
    SGIXVideoSourceAPI();

    // Accessors
    const SGIXVideoSource &getRawAPI() const;

    // Operations
    GLXVideoSourceSGIX xCreateGlxVideoSource(Display *display, int screen,
                                             VLServer server, VLPath path,
                                             int nodeClass, VLNode drainNode) const;
    void xDestroyGlxVideoSource(Display *dpy, GLXVideoSourceSGIX glxvideosource) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SGIXVideoSource _api;
};

// Manages the entry points for the GLX_SGI_cushion extension API.
class SgiCushionAPI : public gl::BaseExtension
{
public:
    // Construction
    SgiCushionAPI();

    // Accessors
    const SgiCushion &getRawAPI() const;

    // Operations
    void xCushionSgi(Display *dpy, Window window, float cushion) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SgiCushion _api;
};

// Manages the entry points for the GLX_SGI_make_current_read extension API.
class SgiMakeCurrentReadAPI : public gl::BaseExtension
{
public:
    // Construction
    SgiMakeCurrentReadAPI();

    // Accessors
    const SgiMakeCurrentRead &getRawAPI() const;

    // Operations
    GLXDrawable xGetCurrentReadDrawableSgi() const;
    Bool xMakeCurrentReadSgi(Display *dpy, GLXDrawable draw, GLXDrawable read,
                             GLXContext ctx) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SgiMakeCurrentRead _api;
};

// Manages the entry points for the GLX_SGI_swap_control extension API.
class SgiSwapControlAPI : public gl::BaseExtension
{
public:
    // Construction
    SgiSwapControlAPI();

    // Accessors
    const SgiSwapControl &getRawAPI() const;

    // Operations
    int xSwapIntervalSgi(int interval) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SgiSwapControl _api;
};

// Manages the entry points for the GLX_SGI_video_sync extension API.
class SgiVideoSyncAPI : public gl::BaseExtension
{
public:
    // Construction
    SgiVideoSyncAPI();

    // Accessors
    const SgiVideoSync &getRawAPI() const;

    // Operations
    int xGetVideoSyncSgi(unsigned int *count) const;
    int xWaitVideoSyncSgi(int divisor, int remainder, unsigned int *count) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    SgiVideoSync _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
