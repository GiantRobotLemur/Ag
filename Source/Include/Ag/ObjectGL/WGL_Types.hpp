//! @file Ag/ObjectGL/WGL_Types.hpp
//! @brief The declaration of data types and constants specific to WGL (Windows
//! OpenGL).
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_WGL_TYPES_HPP__
#define __AG_OBJECT_GL_WGL_TYPES_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
DECLARE_HANDLE(HGPUNV);
DECLARE_HANDLE(HPBUFFERARB);
DECLARE_HANDLE(HPBUFFEREXT);
DECLARE_HANDLE(HPVIDEODEV);
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
};
typedef struct _GPU_DEVICE *PGPU_DEVICE;

//! @brief A namespace encapsulating Windows-specific OpenGL commands and
//! extensions.
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Constant Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constants which maybe required by Windows-specific OpenGL commands.
namespace Global {
    static const GLenum AccessReadOnly                             = 0x00000000; // WGL_ACCESS_READ_ONLY_NV
    static const GLenum ContextReleaseBehaviorNone                 =          0; // WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB
    static const GLenum FontLines                                  =          0; // WGL_FONT_LINES
    static const GLenum AccessReadWrite                            = 0x00000001; // WGL_ACCESS_READ_WRITE_NV
    static const GLenum ContextCoreProfile                         = 0x00000001; // WGL_CONTEXT_CORE_PROFILE_BIT_ARB
    static const GLenum ContextDebug                               = 0x00000001; // WGL_CONTEXT_DEBUG_BIT_ARB
    static const GLenum FontPolygons                               =          1; // WGL_FONT_POLYGONS
    static const GLenum FrontColorBuffer                           = 0x00000001; // WGL_FRONT_COLOR_BUFFER_BIT_ARB
    static const GLenum ImageBufferMinAccessI3D                    = 0x00000001; // WGL_IMAGE_BUFFER_MIN_ACCESS_I3D
    static const GLenum SwapMainPlane                              = 0x00000001; // WGL_SWAP_MAIN_PLANE
    static const GLenum AccessWriteDiscard                         = 0x00000002; // WGL_ACCESS_WRITE_DISCARD_NV
    static const GLenum BackColorBuffer                            = 0x00000002; // WGL_BACK_COLOR_BUFFER_BIT_ARB
    static const GLenum ContextCompatibilityProfile                = 0x00000002; // WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
    static const GLenum ContextForwardCompatible                   = 0x00000002; // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
    static const GLenum ImageBufferLockI3D                         = 0x00000002; // WGL_IMAGE_BUFFER_LOCK_I3D
    static const GLenum SwapOverlay1                               = 0x00000002; // WGL_SWAP_OVERLAY1
    static const GLenum ContextESProfile                           = 0x00000004; // WGL_CONTEXT_ES_PROFILE_BIT_EXT
    static const GLenum ContextES2Profile                          = 0x00000004; // WGL_CONTEXT_ES2_PROFILE_BIT_EXT
    static const GLenum ContextRobustAccess                        = 0x00000004; // WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB
    static const GLenum DepthBuffer                                = 0x00000004; // WGL_DEPTH_BUFFER_BIT_ARB
    static const GLenum SwapOverlay2                               = 0x00000004; // WGL_SWAP_OVERLAY2
    static const GLenum ContextResetIsolation                      = 0x00000008; // WGL_CONTEXT_RESET_ISOLATION_BIT_ARB
    static const GLenum StencilBuffer                              = 0x00000008; // WGL_STENCIL_BUFFER_BIT_ARB
    static const GLenum SwapOverlay3                               = 0x00000008; // WGL_SWAP_OVERLAY3
    static const GLenum SwapOverlay4                               = 0x00000010; // WGL_SWAP_OVERLAY4
    static const GLenum SwapOverlay5                               = 0x00000020; // WGL_SWAP_OVERLAY5
    static const GLenum SwapOverlay6                               = 0x00000040; // WGL_SWAP_OVERLAY6
    static const GLenum SwapOverlay7                               = 0x00000080; // WGL_SWAP_OVERLAY7
    static const GLenum SwapOverlay8                               = 0x00000100; // WGL_SWAP_OVERLAY8
    static const GLenum SwapOverlay9                               = 0x00000200; // WGL_SWAP_OVERLAY9
    static const GLenum SwapOverlay10                              = 0x00000400; // WGL_SWAP_OVERLAY10
    static const GLenum SwapOverlay11                              = 0x00000800; // WGL_SWAP_OVERLAY11
    static const GLenum SwapOverlay12                              = 0x00001000; // WGL_SWAP_OVERLAY12
    static const GLenum GPUVendor                                  =     0x1F00; // WGL_GPU_VENDOR_AMD
    static const GLenum GPURendererString                          =     0x1F01; // WGL_GPU_RENDERER_STRING_AMD
    static const GLenum GPUOpenGLVersionString                     =     0x1F02; // WGL_GPU_OPENGL_VERSION_STRING_AMD
    static const GLenum NumberPixelFormats                         =     0x2000; // WGL_NUMBER_PIXEL_FORMATS_ARB
    static const GLenum SwapOverlay13                              = 0x00002000; // WGL_SWAP_OVERLAY13
    static const GLenum DrawToWindow                               =     0x2001; // WGL_DRAW_TO_WINDOW_ARB
    static const GLenum DrawToBitmap                               =     0x2002; // WGL_DRAW_TO_BITMAP_ARB
    static const GLenum Acceleration                               =     0x2003; // WGL_ACCELERATION_ARB
    static const GLenum NeedPalette                                =     0x2004; // WGL_NEED_PALETTE_ARB
    static const GLenum NeedSystemPalette                          =     0x2005; // WGL_NEED_SYSTEM_PALETTE_ARB
    static const GLenum SwapLayerBuffers                           =     0x2006; // WGL_SWAP_LAYER_BUFFERS_ARB
    static const GLenum SwapMethod                                 =     0x2007; // WGL_SWAP_METHOD_ARB
    static const GLenum NumberOverlays                             =     0x2008; // WGL_NUMBER_OVERLAYS_ARB
    static const GLenum NumberUnderlays                            =     0x2009; // WGL_NUMBER_UNDERLAYS_ARB
    static const GLenum Transparent                                =     0x200A; // WGL_TRANSPARENT_ARB
    static const GLenum TransparentValue                           =     0x200B; // WGL_TRANSPARENT_VALUE_EXT
    static const GLenum ShareDepth                                 =     0x200C; // WGL_SHARE_DEPTH_ARB
    static const GLenum ShareStencil                               =     0x200D; // WGL_SHARE_STENCIL_ARB
    static const GLenum ShareAccum                                 =     0x200E; // WGL_SHARE_ACCUM_ARB
    static const GLenum SupportGDI                                 =     0x200F; // WGL_SUPPORT_GDI_ARB
    static const GLenum SupportOpenGL                              =     0x2010; // WGL_SUPPORT_OPENGL_ARB
    static const GLenum DoubleBuffer                               =     0x2011; // WGL_DOUBLE_BUFFER_ARB
    static const GLenum Stereo                                     =     0x2012; // WGL_STEREO_ARB
    static const GLenum PixelType                                  =     0x2013; // WGL_PIXEL_TYPE_ARB
    static const GLenum ColorBits                                  =     0x2014; // WGL_COLOR_BITS_ARB
    static const GLenum RedBits                                    =     0x2015; // WGL_RED_BITS_ARB
    static const GLenum RedShift                                   =     0x2016; // WGL_RED_SHIFT_ARB
    static const GLenum GreenBits                                  =     0x2017; // WGL_GREEN_BITS_ARB
    static const GLenum GreenShift                                 =     0x2018; // WGL_GREEN_SHIFT_ARB
    static const GLenum BlueBits                                   =     0x2019; // WGL_BLUE_BITS_ARB
    static const GLenum BlueShift                                  =     0x201A; // WGL_BLUE_SHIFT_ARB
    static const GLenum AlphaBits                                  =     0x201B; // WGL_ALPHA_BITS_ARB
    static const GLenum AlphaShift                                 =     0x201C; // WGL_ALPHA_SHIFT_ARB
    static const GLenum AccumBits                                  =     0x201D; // WGL_ACCUM_BITS_ARB
    static const GLenum AccumRedBits                               =     0x201E; // WGL_ACCUM_RED_BITS_ARB
    static const GLenum AccumGreenBits                             =     0x201F; // WGL_ACCUM_GREEN_BITS_ARB
    static const GLenum AccumBlueBits                              =     0x2020; // WGL_ACCUM_BLUE_BITS_ARB
    static const GLenum AccumAlphaBits                             =     0x2021; // WGL_ACCUM_ALPHA_BITS_ARB
    static const GLenum DepthBits                                  =     0x2022; // WGL_DEPTH_BITS_ARB
    static const GLenum StencilBits                                =     0x2023; // WGL_STENCIL_BITS_ARB
    static const GLenum AuxBuffers                                 =     0x2024; // WGL_AUX_BUFFERS_ARB
    static const GLenum NoAcceleration                             =     0x2025; // WGL_NO_ACCELERATION_ARB
    static const GLenum GenericAcceleration                        =     0x2026; // WGL_GENERIC_ACCELERATION_ARB
    static const GLenum FullAcceleration                           =     0x2027; // WGL_FULL_ACCELERATION_ARB
    static const GLenum SwapExchange                               =     0x2028; // WGL_SWAP_EXCHANGE_ARB
    static const GLenum SwapCopy                                   =     0x2029; // WGL_SWAP_COPY_ARB
    static const GLenum SwapUndefined                              =     0x202A; // WGL_SWAP_UNDEFINED_ARB
    static const GLenum TypeRGBA                                   =     0x202B; // WGL_TYPE_RGBA_ARB
    static const GLenum TypeColorindex                             =     0x202C; // WGL_TYPE_COLORINDEX_ARB
    static const GLenum DrawToPbuffer                              =     0x202D; // WGL_DRAW_TO_PBUFFER_ARB
    static const GLenum MaxPBufferPixels                           =     0x202E; // WGL_MAX_PBUFFER_PIXELS_ARB
    static const GLenum MaxPBufferWidth                            =     0x202F; // WGL_MAX_PBUFFER_WIDTH_ARB
    static const GLenum MaxPBufferHeight                           =     0x2030; // WGL_MAX_PBUFFER_HEIGHT_ARB
    static const GLenum OptimalPBufferWidth                        =     0x2031; // WGL_OPTIMAL_PBUFFER_WIDTH_EXT
    static const GLenum OptimalPBufferHeight                       =     0x2032; // WGL_OPTIMAL_PBUFFER_HEIGHT_EXT
    static const GLenum PbufferLargest                             =     0x2033; // WGL_PBUFFER_LARGEST_ARB
    static const GLenum PbufferWidth                               =     0x2034; // WGL_PBUFFER_WIDTH_ARB
    static const GLenum PbufferHeight                              =     0x2035; // WGL_PBUFFER_HEIGHT_ARB
    static const GLenum PbufferLost                                =     0x2036; // WGL_PBUFFER_LOST_ARB
    static const GLenum TransparentRedValue                        =     0x2037; // WGL_TRANSPARENT_RED_VALUE_ARB
    static const GLenum TransparentGreenValue                      =     0x2038; // WGL_TRANSPARENT_GREEN_VALUE_ARB
    static const GLenum TransparentBlueValue                       =     0x2039; // WGL_TRANSPARENT_BLUE_VALUE_ARB
    static const GLenum TransparentAlphaValue                      =     0x203A; // WGL_TRANSPARENT_ALPHA_VALUE_ARB
    static const GLenum TransparentIndexValue                      =     0x203B; // WGL_TRANSPARENT_INDEX_VALUE_ARB
    static const GLenum DepthFloat                                 =     0x2040; // WGL_DEPTH_FLOAT_EXT
    static const GLenum SampleBuffersARB                           =     0x2041; // WGL_SAMPLE_BUFFERS_ARB
    static const GLenum CoverageSamples                            =     0x2042; // WGL_COVERAGE_SAMPLES_NV
    static const GLenum SamplesARB                                 =     0x2042; // WGL_SAMPLES_ARB
    static const GLenum ErrorInvalidPixelType                      =     0x2043; // ERROR_INVALID_PIXEL_TYPE_ARB
    static const GLenum GenlockSourceMultiviewI3D                  =     0x2044; // WGL_GENLOCK_SOURCE_MULTIVIEW_I3D
    static const GLenum GenlockSourceExternalSyncI3D               =     0x2045; // WGL_GENLOCK_SOURCE_EXTERNAL_SYNC_I3D
    static const GLenum GenlockSourceExternalFieldI3D              =     0x2046; // WGL_GENLOCK_SOURCE_EXTERNAL_FIELD_I3D
    static const GLenum GenlockSourceExternalTtlI3D                =     0x2047; // WGL_GENLOCK_SOURCE_EXTERNAL_TTL_I3D
    static const GLenum GenlockSourceDigitalSyncI3D                =     0x2048; // WGL_GENLOCK_SOURCE_DIGITAL_SYNC_I3D
    static const GLenum GenlockSourceDigitalFieldI3D               =     0x2049; // WGL_GENLOCK_SOURCE_DIGITAL_FIELD_I3D
    static const GLenum GenlockSourceEdgeFallingI3D                =     0x204A; // WGL_GENLOCK_SOURCE_EDGE_FALLING_I3D
    static const GLenum GenlockSourceEdgeRisingI3D                 =     0x204B; // WGL_GENLOCK_SOURCE_EDGE_RISING_I3D
    static const GLenum GenlockSourceEdgeBothI3D                   =     0x204C; // WGL_GENLOCK_SOURCE_EDGE_BOTH_I3D
    static const GLenum GammaTableSizeI3D                          =     0x204E; // WGL_GAMMA_TABLE_SIZE_I3D
    static const GLenum GammaExcludeDesktopI3D                     =     0x204F; // WGL_GAMMA_EXCLUDE_DESKTOP_I3D
    static const GLenum DigitalVideoCursorAlphaFramebufferI3D      =     0x2050; // WGL_DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D
    static const GLenum DigitalVideoCursorAlphaValueI3D            =     0x2051; // WGL_DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D
    static const GLenum DigitalVideoCursorIncludedI3D              =     0x2052; // WGL_DIGITAL_VIDEO_CURSOR_INCLUDED_I3D
    static const GLenum DigitalVideoGammaCorrectedI3D              =     0x2053; // WGL_DIGITAL_VIDEO_GAMMA_CORRECTED_I3D
    static const GLenum ErrorIncompatibleDeviceContextS            =     0x2054; // ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB
    static const GLenum StereoEmitterEnable3DL                     =     0x2055; // WGL_STEREO_EMITTER_ENABLE_3DL
    static const GLenum StereoEmitterDisable3DL                    =     0x2056; // WGL_STEREO_EMITTER_DISABLE_3DL
    static const GLenum StereoPolarityNormal3DL                    =     0x2057; // WGL_STEREO_POLARITY_NORMAL_3DL
    static const GLenum StereoPolarityInvert3DL                    =     0x2058; // WGL_STEREO_POLARITY_INVERT_3DL
    static const GLenum SampleBuffers3DFX                          =     0x2060; // WGL_SAMPLE_BUFFERS_3DFX
    static const GLenum Samples3DFX                                =     0x2061; // WGL_SAMPLES_3DFX
    static const GLenum BindToTextureRGB                           =     0x2070; // WGL_BIND_TO_TEXTURE_RGB_ARB
    static const GLenum BindToTextureRGBA                          =     0x2071; // WGL_BIND_TO_TEXTURE_RGBA_ARB
    static const GLenum TextureFormat                              =     0x2072; // WGL_TEXTURE_FORMAT_ARB
    static const GLenum TextureTarget                              =     0x2073; // WGL_TEXTURE_TARGET_ARB
    static const GLenum MipmapTexture                              =     0x2074; // WGL_MIPMAP_TEXTURE_ARB
    static const GLenum TextureRGB                                 =     0x2075; // WGL_TEXTURE_RGB_ARB
    static const GLenum TextureRGBA                                =     0x2076; // WGL_TEXTURE_RGBA_ARB
    static const GLenum NoTexture                                  =     0x2077; // WGL_NO_TEXTURE_ARB
    static const GLenum TextureCubeMap                             =     0x2078; // WGL_TEXTURE_CUBE_MAP_ARB
    static const GLenum Texture1D                                  =     0x2079; // WGL_TEXTURE_1D_ARB
    static const GLenum Texture2D                                  =     0x207A; // WGL_TEXTURE_2D_ARB
    static const GLenum MipmapLevel                                =     0x207B; // WGL_MIPMAP_LEVEL_ARB
    static const GLenum CubeMapFace                                =     0x207C; // WGL_CUBE_MAP_FACE_ARB
    static const GLenum TextureCubeMapPositiveX                    =     0x207D; // WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB
    static const GLenum TextureCubeMapNegativeX                    =     0x207E; // WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB
    static const GLenum TextureCubeMapPositiveY                    =     0x207F; // WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB
    static const GLenum TextureCubeMapNegativeY                    =     0x2080; // WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB
    static const GLenum TextureCubeMapPositiveZ                    =     0x2081; // WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB
    static const GLenum TextureCubeMapNegativeZ                    =     0x2082; // WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
    static const GLenum FrontLeft                                  =     0x2083; // WGL_FRONT_LEFT_ARB
    static const GLenum FrontRight                                 =     0x2084; // WGL_FRONT_RIGHT_ARB
    static const GLenum BackLeft                                   =     0x2085; // WGL_BACK_LEFT_ARB
    static const GLenum BackRight                                  =     0x2086; // WGL_BACK_RIGHT_ARB
    static const GLenum AUX0                                       =     0x2087; // WGL_AUX0_ARB
    static const GLenum AUX1                                       =     0x2088; // WGL_AUX1_ARB
    static const GLenum AUX2                                       =     0x2089; // WGL_AUX2_ARB
    static const GLenum AUX3                                       =     0x208A; // WGL_AUX3_ARB
    static const GLenum AUX4                                       =     0x208B; // WGL_AUX4_ARB
    static const GLenum AUX5                                       =     0x208C; // WGL_AUX5_ARB
    static const GLenum AUX6                                       =     0x208D; // WGL_AUX6_ARB
    static const GLenum AUX7                                       =     0x208E; // WGL_AUX7_ARB
    static const GLenum AUX8                                       =     0x208F; // WGL_AUX8_ARB
    static const GLenum AUX9                                       =     0x2090; // WGL_AUX9_ARB
    static const GLenum ContextMajorVersion                        =     0x2091; // WGL_CONTEXT_MAJOR_VERSION_ARB
    static const GLenum ContextMinorVersion                        =     0x2092; // WGL_CONTEXT_MINOR_VERSION_ARB
    static const GLenum ContextLayerPlane                          =     0x2093; // WGL_CONTEXT_LAYER_PLANE_ARB
    static const GLenum ContextFlags                               =     0x2094; // WGL_CONTEXT_FLAGS_ARB
    static const GLenum ErrorInvalidVersion                        =     0x2095; // ERROR_INVALID_VERSION_ARB
    static const GLenum ErrorInvalidProfile                        =     0x2096; // ERROR_INVALID_PROFILE_ARB
    static const GLenum ContextReleaseBehavior                     =     0x2097; // WGL_CONTEXT_RELEASE_BEHAVIOR_ARB
    static const GLenum ContextReleaseBehaviorFlush                =     0x2098; // WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB
    static const GLenum BindToTextureRectangleRGB                  =     0x20A0; // WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV
    static const GLenum BindToTextureRectangleRGBA                 =     0x20A1; // WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV
    static const GLenum TextureRectangleNV                         =     0x20A2; // WGL_TEXTURE_RECTANGLE_NV
    static const GLenum BindToTextureDepth                         =     0x20A3; // WGL_BIND_TO_TEXTURE_DEPTH_NV
    static const GLenum BindToTextureRectangleDepth                =     0x20A4; // WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV
    static const GLenum DepthTextureFormat                         =     0x20A5; // WGL_DEPTH_TEXTURE_FORMAT_NV
    static const GLenum TextureDepthComponent                      =     0x20A6; // WGL_TEXTURE_DEPTH_COMPONENT_NV
    static const GLenum DepthComponent                             =     0x20A7; // WGL_DEPTH_COMPONENT_NV
    static const GLenum TypeRGBAUnsignedFloat                      =     0x20A8; // WGL_TYPE_RGBA_UNSIGNED_FLOAT_EXT
    static const GLenum FrameBufferSRGBCapable                     =     0x20A9; // WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB
    static const GLenum ContextMultiGPUAttrib                      =     0x20AA; // WGL_CONTEXT_MULTIGPU_ATTRIB_NV
    static const GLenum ContextMultiGPUAttribSingle                =     0x20AB; // WGL_CONTEXT_MULTIGPU_ATTRIB_SINGLE_NV
    static const GLenum ContextMultiGPUAttribAFR                   =     0x20AC; // WGL_CONTEXT_MULTIGPU_ATTRIB_AFR_NV
    static const GLenum ContextMultiGPUAttribMulticast             =     0x20AD; // WGL_CONTEXT_MULTIGPU_ATTRIB_MULTICAST_NV
    static const GLenum ContextMultiGPUAttribMultiDisplayMulticast =     0x20AE; // WGL_CONTEXT_MULTIGPU_ATTRIB_MULTI_DISPLAY_MULTICAST_NV
    static const GLenum FloatComponents                            =     0x20B0; // WGL_FLOAT_COMPONENTS_NV
    static const GLenum BindToTextureRectangleFloatR               =     0x20B1; // WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV
    static const GLenum BindToTextureRectangleFloatRg              =     0x20B2; // WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV
    static const GLenum BindToTextureRectangleFloatRGB             =     0x20B3; // WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV
    static const GLenum BindToTextureRectangleFloatRGBA            =     0x20B4; // WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV
    static const GLenum TextureFloatR                              =     0x20B5; // WGL_TEXTURE_FLOAT_R_NV
    static const GLenum TextureFloatRg                             =     0x20B6; // WGL_TEXTURE_FLOAT_RG_NV
    static const GLenum TextureFloatRGB                            =     0x20B7; // WGL_TEXTURE_FLOAT_RGB_NV
    static const GLenum TextureFloatRGBA                           =     0x20B8; // WGL_TEXTURE_FLOAT_RGBA_NV
    static const GLenum ColorSamples                               =     0x20B9; // WGL_COLOR_SAMPLES_NV
    static const GLenum BindToVideoRGB                             =     0x20C0; // WGL_BIND_TO_VIDEO_RGB_NV
    static const GLenum BindToVideoRGBA                            =     0x20C1; // WGL_BIND_TO_VIDEO_RGBA_NV
    static const GLenum BindToVideoRGBAndDepth                     =     0x20C2; // WGL_BIND_TO_VIDEO_RGB_AND_DEPTH_NV
    static const GLenum VideoOutColor                              =     0x20C3; // WGL_VIDEO_OUT_COLOR_NV
    static const GLenum VideoOutAlpha                              =     0x20C4; // WGL_VIDEO_OUT_ALPHA_NV
    static const GLenum VideoOutDepth                              =     0x20C5; // WGL_VIDEO_OUT_DEPTH_NV
    static const GLenum VideoOutColorAndAlpha                      =     0x20C6; // WGL_VIDEO_OUT_COLOR_AND_ALPHA_NV
    static const GLenum VideoOutColorAndDepth                      =     0x20C7; // WGL_VIDEO_OUT_COLOR_AND_DEPTH_NV
    static const GLenum VideoOutFrame                              =     0x20C8; // WGL_VIDEO_OUT_FRAME
    static const GLenum VideoOutField1                             =     0x20C9; // WGL_VIDEO_OUT_FIELD_1
    static const GLenum VideoOutField2                             =     0x20CA; // WGL_VIDEO_OUT_FIELD_2
    static const GLenum VideoOutStackedFields1_2                   =     0x20CB; // WGL_VIDEO_OUT_STACKED_FIELDS_1_2
    static const GLenum VideoOutStackedFields2_1                   =     0x20CC; // WGL_VIDEO_OUT_STACKED_FIELDS_2_1
    static const GLenum UniqueID                                   =     0x20CE; // WGL_UNIQUE_ID_NV
    static const GLenum NumVideoCaptureSlots                       =     0x20CF; // WGL_NUM_VIDEO_CAPTURE_SLOTS_NV
    static const GLenum ErrorIncompatibleAffinityMasks             =     0x20D0; // ERROR_INCOMPATIBLE_AFFINITY_MASKS_NV
    static const GLenum ErrorMissingAffinityMask                   =     0x20D1; // ERROR_MISSING_AFFINITY_MASK_NV
    static const GLenum NumVideoSlots                              =     0x20F0; // WGL_NUM_VIDEO_SLOTS_NV
    static const GLenum TypeRGBAFloat                              =     0x21A0; // WGL_TYPE_RGBA_FLOAT_ARB
    static const GLenum GPUFastestTargetGPUS                       =     0x21A2; // WGL_GPU_FASTEST_TARGET_GPUS_AMD
    static const GLenum GPURam                                     =     0x21A3; // WGL_GPU_RAM_AMD
    static const GLenum GPUClock                                   =     0x21A4; // WGL_GPU_CLOCK_AMD
    static const GLenum GPUNumPipes                                =     0x21A5; // WGL_GPU_NUM_PIPES_AMD
    static const GLenum TextureRectangleATI                        =     0x21A5; // WGL_TEXTURE_RECTANGLE_ATI - Duplicates unrelated WGL_GPU_NUM_PIPES_AMD
    static const GLenum GPUNumSIMD                                 =     0x21A6; // WGL_GPU_NUM_SIMD_AMD
    static const GLenum GPUNumRB                                   =     0x21A7; // WGL_GPU_NUM_RB_AMD
    static const GLenum GPUNumSPI                                  =     0x21A8; // WGL_GPU_NUM_SPI_AMD
    static const GLenum ColorspaceSRGB                             =     0x3089; // WGL_COLORSPACE_SRGB_EXT
    static const GLenum ColorspaceLinear                           =     0x308A; // WGL_COLORSPACE_LINEAR_EXT
    static const GLenum Colorspace                                 =     0x309D; // WGL_COLORSPACE_EXT
    static const GLenum ContextOpenGLNoError                       =     0x31B3; // WGL_CONTEXT_OPENGL_NO_ERROR_ARB
    static const GLenum SwapOverlay14                              = 0x00004000; // WGL_SWAP_OVERLAY14
    static const GLenum SwapOverlay15                              = 0x00008000; // WGL_SWAP_OVERLAY15
    static const GLenum LoseContextOnReset                         =     0x8252; // WGL_LOSE_CONTEXT_ON_RESET_ARB
    static const GLenum ContextResetNotificationStrategy           =     0x8256; // WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB
    static const GLenum NoResetNotification                        =     0x8261; // WGL_NO_RESET_NOTIFICATION_ARB
    static const GLenum ContextProfileMask                         =     0x9126; // WGL_CONTEXT_PROFILE_MASK_ARB
    static const GLenum SwapUnderlay1                              = 0x00010000; // WGL_SWAP_UNDERLAY1
    static const GLenum SwapUnderlay2                              = 0x00020000; // WGL_SWAP_UNDERLAY2
    static const GLenum SwapUnderlay3                              = 0x00040000; // WGL_SWAP_UNDERLAY3
    static const GLenum SwapUnderlay4                              = 0x00080000; // WGL_SWAP_UNDERLAY4
    static const GLenum SwapUnderlay5                              = 0x00100000; // WGL_SWAP_UNDERLAY5
    static const GLenum SwapUnderlay6                              = 0x00200000; // WGL_SWAP_UNDERLAY6
    static const GLenum SwapUnderlay7                              = 0x00400000; // WGL_SWAP_UNDERLAY7
    static const GLenum SwapUnderlay8                              = 0x00800000; // WGL_SWAP_UNDERLAY8
    static const GLenum SwapUnderlay9                              = 0x01000000; // WGL_SWAP_UNDERLAY9
    static const GLenum SwapUnderlay10                             = 0x02000000; // WGL_SWAP_UNDERLAY10
    static const GLenum SwapUnderlay11                             = 0x04000000; // WGL_SWAP_UNDERLAY11
    static const GLenum SwapUnderlay12                             = 0x08000000; // WGL_SWAP_UNDERLAY12
    static const GLenum SwapUnderlay13                             = 0x10000000; // WGL_SWAP_UNDERLAY13
    static const GLenum SwapUnderlay14                             = 0x20000000; // WGL_SWAP_UNDERLAY14
    static const GLenum SwapUnderlay15                             = 0x40000000; // WGL_SWAP_UNDERLAY15
} // namespace Global

} // namespace wgl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
