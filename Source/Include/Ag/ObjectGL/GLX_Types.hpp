//! @file Ag/ObjectGL/GLX_Types.hpp
//! @brief The declaration of data types shared between GLX OpenGL extensions.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_GLX_TYPES_HPP__
#define __AG_OBJECT_GL_GLX_TYPES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GLX_OML_sync_control extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif

#ifdef _WIN32
// NOTE: These types are declared here so that the GLX interface can be BUILT
// under Windows - there is no intention of trying to use it.
using XID = uintptr_t;
using Bool = int;
struct Display;
using Window = uintptr_t;
using Pixmap = uintptr_t;
using Font = uintptr_t;
using Colormap = uintptr_t;
struct XVisualInfo;
using GLXContext = uintptr_t;
using GLXPixmap = uintptr_t;
using GLXDrawable = uintptr_t;
using GLXFBConfig = uintptr_t;
using GLXPbuffer = uintptr_t;
using GLXWindow = uintptr_t;
using GLXContextID = uintptr_t;
using __GLXextFuncPtr = FARPROC;
using GLXVideoDeviceNV = uintptr_t;
using GLXVideoCaptureDeviceNV = uintptr_t;
using GLXPbufferSGIX = uintptr_t;
using DMbuffer = uintptr_t;
struct DMparams;
struct GLXHyperpipeConfigSGIX;
using GLXFBConfigSGIX = GLXFBConfig;
using GLXPbufferSGIX = uintptr_t;
struct GLXHyperpipeConfigSGIX;
struct GLXHyperpipeNetworkSGIX;
using GLXVideoSourceSGIX = uintptr_t;
using VLServer = uintptr_t;
using VLPath = uintptr_t;
using VLNode = uintptr_t;
using Status = uintptr_t;
#endif

//! @brief A namespace encapsulating GLX-specific OpenGL commands.
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// Enumeration Types
////////////////////////////////////////////////////////////////////////////////
// Global constants which could be relevant to GLX extensions.
namespace Global {
    static const GLenum ContextReleaseBehaviorNone                 =          0; // GLX_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB
    static const GLenum PbufferClobber                             =          0; // GLX_PbufferClobber
    static const GLenum StereoNotify                               = 0x00000000; // GLX_STEREO_NOTIFY_EXT
    static const GLenum SyncFrame                                  = 0x00000000; // GLX_SYNC_FRAME_SGIX
    static const GLenum _3DfxWindowMode                            =        0x1; // GLX_3DFX_WINDOW_MODE_MESA
    static const GLenum BadScreen                                  =          1; // GLX_BAD_SCREEN
    static const GLenum BufferSwapComplete                         =          1; // GLX_BufferSwapComplete
    static const GLenum ContextCoreProfile                         = 0x00000001; // GLX_CONTEXT_CORE_PROFILE_BIT_ARB
    static const GLenum ContextDebug                               = 0x00000001; // GLX_CONTEXT_DEBUG_BIT_ARB
    static const GLenum FrontLeftBuffer                            = 0x00000001; // GLX_FRONT_LEFT_BUFFER_BIT
    static const GLenum HyperpipeDisplayPipe                       = 0x00000001; // GLX_HYPERPIPE_DISPLAY_PIPE_SGIX
    static const GLenum PipeRect                                   = 0x00000001; // GLX_PIPE_RECT_SGIX
    static const GLenum RGBABit                                    = 0x00000001; // GLX_RGBA_BIT
    static const GLenum StereoNotifyMask                           = 0x00000001; // GLX_STEREO_NOTIFY_MASK_EXT
    static const GLenum SyncSwap                                   = 0x00000001; // GLX_SYNC_SWAP_SGIX
    static const GLenum Texture1DBitEXT                            = 0x00000001; // GLX_TEXTURE_1D_BIT_EXT
    static const GLenum UseGl                                      =          1; // GLX_USE_GL
    static const GLenum Vendor                                     =        0x1; // GLX_VENDOR
    static const GLenum WindowBit                                  = 0x00000001; // GLX_WINDOW_BIT
    static const GLenum _3DfxFullscreenMode                        =        0x2; // GLX_3DFX_FULLSCREEN_MODE_MESA
    static const GLenum BadAttribute                               =          2; // GLX_BAD_ATTRIBUTE
    static const GLenum BufferSize                                 =          2; // GLX_BUFFER_SIZE
    static const GLenum ColorIndex                                 = 0x00000002; // GLX_COLOR_INDEX_BIT
    static const GLenum ContextCompatibilityProfile                = 0x00000002; // GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
    static const GLenum ContextForwardCompatible                   = 0x00000002; // GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
    static const GLenum FrontRightBuffer                           = 0x00000002; // GLX_FRONT_RIGHT_BUFFER_BIT
    static const GLenum HyperpipeRenderPipe                        = 0x00000002; // GLX_HYPERPIPE_RENDER_PIPE_SGIX
    static const GLenum PipeRectLimits                             = 0x00000002; // GLX_PIPE_RECT_LIMITS_SGIX
    static const GLenum Pixmap                                     = 0x00000002; // GLX_PIXMAP_BIT
    static const GLenum Texture2DBitEXT                            = 0x00000002; // GLX_TEXTURE_2D_BIT_EXT
    static const GLenum Version                                    =        0x2; // GLX_VERSION
    static const GLenum Extensions                                 =        0x3; // GLX_EXTENSIONS
    static const GLenum HyperpipeStereo                            = 0x00000003; // GLX_HYPERPIPE_STEREO_SGIX
    static const GLenum Level                                      =          3; // GLX_LEVEL
    static const GLenum NoExtension                                =          3; // GLX_NO_EXTENSION
    static const GLenum BackLeftBuffer                             = 0x00000004; // GLX_BACK_LEFT_BUFFER_BIT
    static const GLenum BadVisual                                  =          4; // GLX_BAD_VISUAL
    static const GLenum ContextEsProfile                           = 0x00000004; // GLX_CONTEXT_ES_PROFILE_BIT_EXT
    static const GLenum ContextES2Profile                          = 0x00000004; // GLX_CONTEXT_ES2_PROFILE_BIT_EXT
    static const GLenum ContextRobustAccess                        = 0x00000004; // GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB
    static const GLenum HyperpipePixelAverage                      = 0x00000004; // GLX_HYPERPIPE_PIXEL_AVERAGE_SGIX
    static const GLenum PbufferBit                                 = 0x00000004; // GLX_PBUFFER_BIT
    static const GLenum RGBA                                       =          4; // GLX_RGBA
    static const GLenum RGBAFloat                                  = 0x00000004; // GLX_RGBA_FLOAT_BIT_ARB
    static const GLenum TextureRectangleBitEXT                     = 0x00000004; // GLX_TEXTURE_RECTANGLE_BIT_EXT
    static const GLenum BadContext                                 =          5; // GLX_BAD_CONTEXT
    static const GLenum Doublebuffer                               =          5; // GLX_DOUBLEBUFFER
    static const GLenum BadValue                                   =          6; // GLX_BAD_VALUE
    static const GLenum Stereo                                     =          6; // GLX_STEREO
    static const GLenum AuxBuffers                                 =          7; // GLX_AUX_BUFFERS
    static const GLenum BadEnum                                    =          7; // GLX_BAD_ENUM
    static const GLenum BackRightBuffer                            = 0x00000008; // GLX_BACK_RIGHT_BUFFER_BIT
    static const GLenum ContextResetIsolation                      = 0x00000008; // GLX_CONTEXT_RESET_ISOLATION_BIT_ARB
    static const GLenum RedSize                                    =          8; // GLX_RED_SIZE
    static const GLenum RGBAUnsignedFloat                          = 0x00000008; // GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT
    static const GLenum GreenSize                                  =          9; // GLX_GREEN_SIZE
    static const GLenum BlueSize                                   =         10; // GLX_BLUE_SIZE
    static const GLenum AlphaSize                                  =         11; // GLX_ALPHA_SIZE
    static const GLenum DepthSize                                  =         12; // GLX_DEPTH_SIZE
    static const GLenum StencilSize                                =         13; // GLX_STENCIL_SIZE
    static const GLenum AccumRedSize                               =         14; // GLX_ACCUM_RED_SIZE
    static const GLenum AccumGreenSize                             =         15; // GLX_ACCUM_GREEN_SIZE
    static const GLenum AccumBlueSize                              =         16; // GLX_ACCUM_BLUE_SIZE
    static const GLenum AuxBuffersBit                              = 0x00000010; // GLX_AUX_BUFFERS_BIT
    static const GLenum GlxNumberEventS                            =         17; // __GLX_NUMBER_EVENTS
    static const GLenum AccumAlphaSize                             =         17; // GLX_ACCUM_ALPHA_SIZE
    static const GLenum ConfigCaveat                               =       0x20; // GLX_CONFIG_CAVEAT
    static const GLenum DepthBuffer                                = 0x00000020; // GLX_DEPTH_BUFFER_BIT
    static const GLenum VisualCaveat                               =       0x20; // GLX_VISUAL_CAVEAT_EXT
    static const GLenum XVisualType                                =       0x22; // GLX_X_VISUAL_TYPE
    static const GLenum TransparentType                            =       0x23; // GLX_TRANSPARENT_TYPE
    static const GLenum TransparentIndexValue                      =       0x24; // GLX_TRANSPARENT_INDEX_VALUE
    static const GLenum TransparentRedValue                        =       0x25; // GLX_TRANSPARENT_RED_VALUE
    static const GLenum TransparentGreenValue                      =       0x26; // GLX_TRANSPARENT_GREEN_VALUE
    static const GLenum TransparentBlueValue                       =       0x27; // GLX_TRANSPARENT_BLUE_VALUE
    static const GLenum TransparentAlphaValue                      =       0x28; // GLX_TRANSPARENT_ALPHA_VALUE
    static const GLenum StencilBuffer                              = 0x00000040; // GLX_STENCIL_BUFFER_BIT
    static const GLenum HyperpipePipeNameLength                    =         80; // GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX
    static const GLenum BadHyperpipeConfig                         =         91; // GLX_BAD_HYPERPIPE_CONFIG_SGIX
    static const GLenum BadHyperpipe                               =         92; // GLX_BAD_HYPERPIPE_SGIX
    static const GLenum AccumBuffer                                = 0x00000080; // GLX_ACCUM_BUFFER_BIT
    static const GLenum SampleBuffersBitSGIX                       = 0x00000100; // GLX_SAMPLE_BUFFERS_BIT_SGIX
    static const GLenum GPUVendor                                  =     0x1F00; // GLX_GPU_VENDOR_AMD
    static const GLenum GPURendererString                          =     0x1F01; // GLX_GPU_RENDERER_STRING_AMD
    static const GLenum GPUOpenglVersionString                     =     0x1F02; // GLX_GPU_OPENGL_VERSION_STRING_AMD
    static const GLenum ContextMajorVersion                        =     0x2091; // GLX_CONTEXT_MAJOR_VERSION_ARB
    static const GLenum ContextMinorVersion                        =     0x2092; // GLX_CONTEXT_MINOR_VERSION_ARB
    static const GLenum ContextFlags                               =     0x2094; // GLX_CONTEXT_FLAGS_ARB
    static const GLenum ContextAllowBufferByteOrderMismatch        =     0x2095; // GLX_CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB
    static const GLenum ContextReleaseBehavior                     =     0x2097; // GLX_CONTEXT_RELEASE_BEHAVIOR_ARB
    static const GLenum ContextReleaseBehaviorFlush                =     0x2098; // GLX_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB
    static const GLenum ContextMultigpuAttrib                      =     0x20AA; // GLX_CONTEXT_MULTIGPU_ATTRIB_NV
    static const GLenum ContextMultigpuAttribSingle                =     0x20AB; // GLX_CONTEXT_MULTIGPU_ATTRIB_SINGLE_NV
    static const GLenum ContextMultigpuAttribAfr                   =     0x20AC; // GLX_CONTEXT_MULTIGPU_ATTRIB_AFR_NV
    static const GLenum ContextMultigpuAttribMulticast             =     0x20AD; // GLX_CONTEXT_MULTIGPU_ATTRIB_MULTICAST_NV
    static const GLenum ContextMultigpuAttribMultiDisplayMulticast =     0x20AE; // GLX_CONTEXT_MULTIGPU_ATTRIB_MULTI_DISPLAY_MULTICAST_NV
    static const GLenum FloatComponents                            =     0x20B0; // GLX_FLOAT_COMPONENTS_NV
    static const GLenum RGBAUnsignedFloatType                      =     0x20B1; // GLX_RGBA_UNSIGNED_FLOAT_TYPE_EXT
    static const GLenum FramebufferSRGBCapable                     =     0x20B2; // GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
    static const GLenum ColorSamples                               =     0x20B3; // GLX_COLOR_SAMPLES_NV
    static const GLenum RGBAFloatType                              =     0x20B9; // GLX_RGBA_FLOAT_TYPE_ARB
    static const GLenum VideoOutColor                              =     0x20C3; // GLX_VIDEO_OUT_COLOR_NV
    static const GLenum VideoOutAlpha                              =     0x20C4; // GLX_VIDEO_OUT_ALPHA_NV
    static const GLenum VideoOutDepth                              =     0x20C5; // GLX_VIDEO_OUT_DEPTH_NV
    static const GLenum VideoOutColorAndAlpha                      =     0x20C6; // GLX_VIDEO_OUT_COLOR_AND_ALPHA_NV
    static const GLenum VideoOutColorAndDepth                      =     0x20C7; // GLX_VIDEO_OUT_COLOR_AND_DEPTH_NV
    static const GLenum VideoOutFrame                              =     0x20C8; // GLX_VIDEO_OUT_FRAME_NV
    static const GLenum VideoOutField1                             =     0x20C9; // GLX_VIDEO_OUT_FIELD_1_NV
    static const GLenum VideoOutField2                             =     0x20CA; // GLX_VIDEO_OUT_FIELD_2_NV
    static const GLenum VideoOutStackedFields1_2                   =     0x20CB; // GLX_VIDEO_OUT_STACKED_FIELDS_1_2_NV
    static const GLenum VideoOutStackedFields2_1                   =     0x20CC; // GLX_VIDEO_OUT_STACKED_FIELDS_2_1_NV
    static const GLenum DeviceId                                   =     0x20CD; // GLX_DEVICE_ID_NV
    static const GLenum UniqueId                                   =     0x20CE; // GLX_UNIQUE_ID_NV
    static const GLenum NumVideoCaptureSlots                       =     0x20CF; // GLX_NUM_VIDEO_CAPTURE_SLOTS_NV
    static const GLenum BindToTextureRGB                           =     0x20D0; // GLX_BIND_TO_TEXTURE_RGB_EXT
    static const GLenum BindToTextureRGBA                          =     0x20D1; // GLX_BIND_TO_TEXTURE_RGBA_EXT
    static const GLenum BindToMipmapTexture                        =     0x20D2; // GLX_BIND_TO_MIPMAP_TEXTURE_EXT
    static const GLenum BindToTextureTargets                       =     0x20D3; // GLX_BIND_TO_TEXTURE_TARGETS_EXT
    static const GLenum YInverted                                  =     0x20D4; // GLX_Y_INVERTED_EXT
    static const GLenum TextureFormat                              =     0x20D5; // GLX_TEXTURE_FORMAT_EXT
    static const GLenum TextureTarget                              =     0x20D6; // GLX_TEXTURE_TARGET_EXT
    static const GLenum MipmapTexture                              =     0x20D7; // GLX_MIPMAP_TEXTURE_EXT
    static const GLenum TextureFormatNone                          =     0x20D8; // GLX_TEXTURE_FORMAT_NONE_EXT
    static const GLenum TextureFormatRGB                           =     0x20D9; // GLX_TEXTURE_FORMAT_RGB_EXT
    static const GLenum TextureFormatRGBA                          =     0x20DA; // GLX_TEXTURE_FORMAT_RGBA_EXT
    static const GLenum Texture1DEXT                               =     0x20DB; // GLX_TEXTURE_1D_EXT
    static const GLenum Texture2DEXT                               =     0x20DC; // GLX_TEXTURE_2D_EXT
    static const GLenum TextureRectangleEXT                        =     0x20DD; // GLX_TEXTURE_RECTANGLE_EXT
    static const GLenum Front                                      =     0x20DE; // GLX_FRONT_EXT
    static const GLenum FrontLeft                                  =     0x20DE; // GLX_FRONT_LEFT_EXT
    static const GLenum FrontRight                                 =     0x20DF; // GLX_FRONT_RIGHT_EXT
    static const GLenum Back                                       =     0x20E0; // GLX_BACK_EXT
    static const GLenum BackLeft                                   =     0x20E0; // GLX_BACK_LEFT_EXT
    static const GLenum BackRight                                  =     0x20E1; // GLX_BACK_RIGHT_EXT
    static const GLenum AUX0                                       =     0x20E2; // GLX_AUX0_EXT
    static const GLenum AUX1                                       =     0x20E3; // GLX_AUX1_EXT
    static const GLenum AUX2                                       =     0x20E4; // GLX_AUX2_EXT
    static const GLenum AUX3                                       =     0x20E5; // GLX_AUX3_EXT
    static const GLenum AUX4                                       =     0x20E6; // GLX_AUX4_EXT
    static const GLenum AUX5                                       =     0x20E7; // GLX_AUX5_EXT
    static const GLenum AUX6                                       =     0x20E8; // GLX_AUX6_EXT
    static const GLenum AUX7                                       =     0x20E9; // GLX_AUX7_EXT
    static const GLenum AUX8                                       =     0x20EA; // GLX_AUX8_EXT
    static const GLenum AUX9                                       =     0x20EB; // GLX_AUX9_EXT
    static const GLenum NumVideoSlots                              =     0x20F0; // GLX_NUM_VIDEO_SLOTS_NV
    static const GLenum SwapInterval                               =     0x20F1; // GLX_SWAP_INTERVAL_EXT
    static const GLenum MaxSwapInterval                            =     0x20F2; // GLX_MAX_SWAP_INTERVAL_EXT
    static const GLenum LateSwapSTear                              =     0x20F3; // GLX_LATE_SWAPS_TEAR_EXT
    static const GLenum BackBufferAge                              =     0x20F4; // GLX_BACK_BUFFER_AGE_EXT
    static const GLenum StereoTree                                 =     0x20F5; // GLX_STEREO_TREE_EXT
    static const GLenum VendorNames                                =     0x20F6; // GLX_VENDOR_NAMES_EXT
    static const GLenum GenerateResetOnVideoMemoryPurge            =     0x20F7; // GLX_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV
    static const GLenum GPUFastestTargetGPUS                       =     0x21A2; // GLX_GPU_FASTEST_TARGET_GPUS_AMD
    static const GLenum GPURam                                     =     0x21A3; // GLX_GPU_RAM_AMD
    static const GLenum GPUClock                                   =     0x21A4; // GLX_GPU_CLOCK_AMD
    static const GLenum GPUNumPipes                                =     0x21A5; // GLX_GPU_NUM_PIPES_AMD
    static const GLenum GPUNumSIMD                                 =     0x21A6; // GLX_GPU_NUM_SIMD_AMD
    static const GLenum GPUNumRB                                   =     0x21A7; // GLX_GPU_NUM_RB_AMD
    static const GLenum GPUNumSPI                                  =     0x21A8; // GLX_GPU_NUM_SPI_AMD
    static const GLenum ContextPriorityLevel                       =     0x3100; // GLX_CONTEXT_PRIORITY_LEVEL_EXT
    static const GLenum ContextPriorityHigh                        =     0x3101; // GLX_CONTEXT_PRIORITY_HIGH_EXT
    static const GLenum ContextPriorityMedium                      =     0x3102; // GLX_CONTEXT_PRIORITY_MEDIUM_EXT
    static const GLenum ContextPriorityLow                         =     0x3103; // GLX_CONTEXT_PRIORITY_LOW_EXT
    static const GLenum ContextOpenglNoError                       =     0x31B3; // GLX_CONTEXT_OPENGL_NO_ERROR_ARB
    static const GLenum None                                       =     0x8000; // GLX_NONE - Attribute value
    static const GLenum SlowConfig                                 =     0x8001; // GLX_SLOW_CONFIG - CONFIG_CAVEAT attribute value
    static const GLenum SlowVisual                                 =     0x8001; // GLX_SLOW_VISUAL_EXT - VISUAL_CAVEAT_EXT attribute value
    static const GLenum TrueColor                                  =     0x8002; // GLX_TRUE_COLOR - X_VISUAL_TYPE attribute value
    static const GLenum DirectColor                                =     0x8003; // GLX_DIRECT_COLOR - X_VISUAL_TYPE attribute value
    static const GLenum PseudoColor                                =     0x8004; // GLX_PSEUDO_COLOR - X_VISUAL_TYPE attribute value
    static const GLenum StaticColor                                =     0x8005; // GLX_STATIC_COLOR - X_VISUAL_TYPE attribute value
    static const GLenum GrayScale                                  =     0x8006; // GLX_GRAY_SCALE - X_VISUAL_TYPE attribute value
    static const GLenum StaticGray                                 =     0x8007; // GLX_STATIC_GRAY - X_VISUAL_TYPE attribute value
    static const GLenum TransparentRGB                             =     0x8008; // GLX_TRANSPARENT_RGB - TRANSPARENT_TYPE attribute value
    static const GLenum TransparentIndex                           =     0x8009; // GLX_TRANSPARENT_INDEX - TRANSPARENT_TYPE attribute value
    static const GLenum ShareContext                               =     0x800A; // GLX_SHARE_CONTEXT_EXT - QueryContextInfoEXT attribute
    static const GLenum VisualId                                   =     0x800B; // GLX_VISUAL_ID - Context attribute
    static const GLenum Screen                                     =     0x800C; // GLX_SCREEN - Context attribute
    static const GLenum NonConformantConfig                        =     0x800D; // GLX_NON_CONFORMANT_CONFIG - CONFIG_CAVEAT attribute value
    static const GLenum NonConformantVisual                        =     0x800D; // GLX_NON_CONFORMANT_VISUAL_EXT - VISUAL_CAVEAT_EXT attribute value
    static const GLenum DrawableType                               =     0x8010; // GLX_DRAWABLE_TYPE - FBConfig attribute
    static const GLenum RenderType                                 =     0x8011; // GLX_RENDER_TYPE - FBConfig attribute
    static const GLenum XRenderable                                =     0x8012; // GLX_X_RENDERABLE - FBConfig attribute
    static const GLenum FbconfigId                                 =     0x8013; // GLX_FBCONFIG_ID - FBConfig attribute
    static const GLenum RGBAType                                   =     0x8014; // GLX_RGBA_TYPE - CreateNewContext render_type value
    static const GLenum ColorIndexType                             =     0x8015; // GLX_COLOR_INDEX_TYPE - CreateNewContext render_type value
    static const GLenum MaxPbufferWidth                            =     0x8016; // GLX_MAX_PBUFFER_WIDTH - FBConfig attribute
    static const GLenum MaxPbufferHeight                           =     0x8017; // GLX_MAX_PBUFFER_HEIGHT - FBConfig attribute
    static const GLenum MaxPbufferPixels                           =     0x8018; // GLX_MAX_PBUFFER_PIXELS - FBConfig attribute
    static const GLenum OptimalPbufferWidth                        =     0x8019; // GLX_OPTIMAL_PBUFFER_WIDTH_SGIX - FBConfigSGIX attribute
    static const GLenum OptimalPbufferHeight                       =     0x801A; // GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX - FBConfigSGIX attribute
    static const GLenum PreservedContents                          =     0x801B; // GLX_PRESERVED_CONTENTS - CreateGLXPbuffer attribute
    static const GLenum LargestPbuffer                             =     0x801C; // GLX_LARGEST_PBUFFER - CreateGLXPbuffer attribute
    static const GLenum Width                                      =     0x801D; // GLX_WIDTH - Drawable attribute
    static const GLenum Height                                     =     0x801E; // GLX_HEIGHT - Drawable attribute
    static const GLenum EventMask                                  =     0x801F; // GLX_EVENT_MASK - Drawable attribute
    static const GLenum Damaged                                    =     0x8020; // GLX_DAMAGED - PbufferClobber event_type value
    static const GLenum Saved                                      =     0x8021; // GLX_SAVED - PbufferClobber event_type value
    static const GLenum Window                                     =     0x8022; // GLX_WINDOW - PbufferClobber draw_type value
    static const GLenum Pbuffer                                    =     0x8023; // GLX_PBUFFER - PbufferClobber draw_type value
    static const GLenum DigitalMediaPbuffer                        =     0x8024; // GLX_DIGITAL_MEDIA_PBUFFER_SGIX - PbufferSGIX attribute
    static const GLenum BlendedRGBA                                =     0x8025; // GLX_BLENDED_RGBA_SGIS - TRANSPARENT_TYPE_EXT attribute value
    static const GLenum MultisampleSubRectWidth                    =     0x8026; // GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS - Visual attribute (shared_multisample)
    static const GLenum MultisampleSubRectHeight                   =     0x8027; // GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS - Visual attribute (shared_multisample)
    static const GLenum VisualSelectGroup                          =     0x8028; // GLX_VISUAL_SELECT_GROUP_SGIX - Visual attribute (visual_select_group)
    static const GLenum HyperpipeId                                =     0x8030; // GLX_HYPERPIPE_ID_SGIX
    static const GLenum PbufferHeight                              =     0x8040; // GLX_PBUFFER_HEIGHT - CreateGLXPbuffer attribute
    static const GLenum PbufferWidth                               =     0x8041; // GLX_PBUFFER_WIDTH - CreateGLXPbuffer attribute
    static const GLenum SampleBuffers3Dfx                          =     0x8050; // GLX_SAMPLE_BUFFERS_3DFX
    static const GLenum Samples3Dfx                                =     0x8051; // GLX_SAMPLES_3DFX
    static const GLenum SwapMethod                                 =     0x8060; // GLX_SWAP_METHOD_OML
    static const GLenum SwapExchange                               =     0x8061; // GLX_SWAP_EXCHANGE_OML
    static const GLenum SwapCopy                                   =     0x8062; // GLX_SWAP_COPY_OML
    static const GLenum SwapUndefined                              =     0x8063; // GLX_SWAP_UNDEFINED_OML
    static const GLenum ExchangeComplete                           =     0x8180; // GLX_EXCHANGE_COMPLETE_INTEL
    static const GLenum CopyComplete                               =     0x8181; // GLX_COPY_COMPLETE_INTEL
    static const GLenum FlipComplete                               =     0x8182; // GLX_FLIP_COMPLETE_INTEL
    static const GLenum RendererVendorId                           =     0x8183; // GLX_RENDERER_VENDOR_ID_MESA
    static const GLenum RendererDeviceId                           =     0x8184; // GLX_RENDERER_DEVICE_ID_MESA
    static const GLenum RendererVersion                            =     0x8185; // GLX_RENDERER_VERSION_MESA
    static const GLenum RendererAccelerated                        =     0x8186; // GLX_RENDERER_ACCELERATED_MESA
    static const GLenum RendererVideoMemory                        =     0x8187; // GLX_RENDERER_VIDEO_MEMORY_MESA
    static const GLenum RendererUnifiedMemoryArchitecture          =     0x8188; // GLX_RENDERER_UNIFIED_MEMORY_ARCHITECTURE_MESA
    static const GLenum RendererPreferredProfile                   =     0x8189; // GLX_RENDERER_PREFERRED_PROFILE_MESA
    static const GLenum RendererOpenglCoreProfileVersion           =     0x818A; // GLX_RENDERER_OPENGL_CORE_PROFILE_VERSION_MESA
    static const GLenum RendererOpenglCompatibilityProfileVersion  =     0x818B; // GLX_RENDERER_OPENGL_COMPATIBILITY_PROFILE_VERSION_MESA
    static const GLenum RendererOpenglEsProfileVersion             =     0x818C; // GLX_RENDERER_OPENGL_ES_PROFILE_VERSION_MESA
    static const GLenum RendererOpenglES2ProfileVersion            =     0x818D; // GLX_RENDERER_OPENGL_ES2_PROFILE_VERSION_MESA
    static const GLenum LoseContextOnReset                         =     0x8252; // GLX_LOSE_CONTEXT_ON_RESET_ARB
    static const GLenum ContextResetNotificationStrategy           =     0x8256; // GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB
    static const GLenum NoResetNotification                        =     0x8261; // GLX_NO_RESET_NOTIFICATION_ARB
    static const GLenum ContextProfileMask                         =     0x9126; // GLX_CONTEXT_PROFILE_MASK_ARB - Value shared with GL
    static const GLenum SampleBuffers                              =     100000; // GLX_SAMPLE_BUFFERS
    static const GLenum CoverageSamples                            =     100001; // GLX_COVERAGE_SAMPLES_NV
    static const GLenum Samples                                    =     100001; // GLX_SAMPLES
    static const GLenum BufferSwapCompleteIntelMask                = 0x04000000; // GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK
    static const GLenum BufferClobberMask                          = 0x08000000; // GLX_BUFFER_CLOBBER_MASK_SGIX
    static const GLenum PbufferClobberMask                         = 0x08000000; // GLX_PBUFFER_CLOBBER_MASK
    static const GLenum DontCare                                   = 0xFFFFFFFF; // GLX_DONT_CARE - For ChooseFBConfig attributes
    //static const GLenum ExtensionName                              =      "GLX"; // GLX_EXTENSION_NAME - This is modest abuse of the enum tag mechanism, maybe a string tag?
} // namespace Global

} // namespace glx

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
