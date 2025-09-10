//! @file Ag/ObjectGL/Extensions/Intense3D.hpp
//! @brief The declaration of Intense 3D-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_INTENSE_3D_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_INTENSE_3D_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../WGL_Types.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// WGL_I3D_digital_video_control extension API specification.
struct I3DDigitalVideoControl {
    // Public Members
    BOOL(APIENTRY *wglGetDigitalVideoParameters)(HDC hDC, int iAttribute,
                                                 int *piValue);
    BOOL(APIENTRY *wglSetDigitalVideoParameters)(HDC hDC, int iAttribute,
                                                 const int *piValue);

   // Construction
    I3DDigitalVideoControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DDigitalVideoControl

// WGL_I3D_gamma extension API specification.
struct I3DGamma {
    // Public Members
    BOOL(APIENTRY *wglGetGammaTable)(HDC hDC, int iEntries, USHORT *puRed,
                                     USHORT *puGreen, USHORT *puBlue);
    BOOL(APIENTRY *wglGetGammaTableParameters)(HDC hDC, int iAttribute,
                                               int *piValue);
    BOOL(APIENTRY *wglSetGammaTable)(HDC hDC, int iEntries, const USHORT *puRed,
                                     const USHORT *puGreen,
                                     const USHORT *puBlue);
    BOOL(APIENTRY *wglSetGammaTableParameters)(HDC hDC, int iAttribute,
                                               const int *piValue);

   // Construction
    I3DGamma();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DGamma

// WGL_I3D_genlock extension API specification.
struct I3DGenlock {
    // Public Members
    BOOL(APIENTRY *wglDisableGenlock)(HDC hDC);
    BOOL(APIENTRY *wglEnableGenlock)(HDC hDC);
    BOOL(APIENTRY *wglGenlockSampleRate)(HDC hDC, UINT uRate);
    BOOL(APIENTRY *wglGenlockSourceDelay)(HDC hDC, UINT uDelay);
    BOOL(APIENTRY *wglGenlockSourceEdge)(HDC hDC, UINT uEdge);
    BOOL(APIENTRY *wglGenlockSource)(HDC hDC, UINT uSource);
    BOOL(APIENTRY *wglGetGenlockSampleRate)(HDC hDC, UINT *uRate);
    BOOL(APIENTRY *wglGetGenlockSourceDelay)(HDC hDC, UINT *uDelay);
    BOOL(APIENTRY *wglGetGenlockSourceEdge)(HDC hDC, UINT *uEdge);
    BOOL(APIENTRY *wglGetGenlockSource)(HDC hDC, UINT *uSource);
    BOOL(APIENTRY *wglIsEnabledGenlock)(HDC hDC, BOOL *pFlag);
    BOOL(APIENTRY *wglQueryGenlockMaxSourceDelay)(HDC hDC, UINT *uMaxLineDelay,
                                                  UINT *uMaxPixelDelay);

   // Construction
    I3DGenlock();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DGenlock

// WGL_I3D_image_buffer extension API specification.
struct I3DImageBuffer {
    // Public Members
    BOOL(APIENTRY *wglAssociateImageBufferEvents)(HDC hDC, const HANDLE *pEvent,
                                                  const LPVOID *pAddress,
                                                  const DWORD *pSize,
                                                  UINT count);
    LPVOID(APIENTRY *wglCreateImageBuffer)(HDC hDC, DWORD dwSize, UINT uFlags);
    BOOL(APIENTRY *wglDestroyImageBuffer)(HDC hDC, LPVOID pAddress);
    BOOL(APIENTRY *wglReleaseImageBufferEvents)(HDC hDC, const LPVOID *pAddress,
                                                UINT count);

   // Construction
    I3DImageBuffer();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DImageBuffer

// WGL_I3D_swap_frame_lock extension API specification.
struct I3DSwapFrameLock {
    // Public Members
    BOOL(APIENTRY *wglDisableFrameLock)();
    BOOL(APIENTRY *wglEnableFrameLock)();
    BOOL(APIENTRY *wglIsEnabledFrameLock)(BOOL *pFlag);
    BOOL(APIENTRY *wglQueryFrameLockMaster)(BOOL *pFlag);

    // Construction
    I3DSwapFrameLock();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DSwapFrameLock

// WGL_I3D_swap_frame_usage extension API specification.
struct I3DSwapFrameUsage {
    // Public Members
    BOOL(APIENTRY *wglBeginFrameTracking)();
    BOOL(APIENTRY *wglEndFrameTracking)();
    BOOL(APIENTRY *wglGetFrameUsage)(float *pUsage);
    BOOL(APIENTRY *wglQueryFrameTracking)(DWORD *pFrameCount,
                                          DWORD *pMissedFrames,
                                          float *pLastMissedUsage);

   // Construction
    I3DSwapFrameUsage();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct I3DSwapFrameUsage

} // namespace wgl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
