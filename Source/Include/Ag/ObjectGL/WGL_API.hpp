//! @file Ag/ObjectGL/WGL_API.hpp
//! @brief The declaration of Microsoft Windows-specific OpenGL entry points,
//! also known as WGL.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __0AE3D5F1_596C_46B2_8613_C0DB4AA3727F_INCLUDED__
#define __0AE3D5F1_596C_46B2_8613_C0DB4AA3727F_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "BaseTypes.hpp"
#include "WGL_Types.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// API Command Groups
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure which contains pointers to Windows-specific functions
//! which are resolved at runtime.
struct WGL {
    // Public Members

    // WGL 1.0
    int (APIENTRY *ChoosePixelFormat)(HDC hDc, const PIXELFORMATDESCRIPTOR *pPfd);
    int (APIENTRY *DescribePixelFormat)(HDC hdc, int ipfd, UINT cjpfd,
                                        const PIXELFORMATDESCRIPTOR *ppfd);
    UINT (APIENTRY *GetEnhMetaFilePixelFormat)(HENHMETAFILE hemf, UINT cbBuffer,
                                               const PIXELFORMATDESCRIPTOR *ppfd);
    int (APIENTRY *GetPixelFormat)(HDC hdc);
    BOOL (APIENTRY *SetPixelFormat)(HDC hdc, int ipfd,
                                    const PIXELFORMATDESCRIPTOR *ppfd);
    BOOL (APIENTRY *SwapBuffers)(HDC hdc);
    BOOL (APIENTRY *wglCopyContext)(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask);
    HGLRC (APIENTRY *wglCreateContext)(HDC hDc);
    HGLRC (APIENTRY *wglCreateLayerContext)(HDC hDc, int level);
    BOOL (APIENTRY *wglDeleteContext)(HGLRC oldContext);
    BOOL (APIENTRY *wglDescribeLayerPlane)(HDC hDc, int pixelFormat,
                                           int layerPlane, UINT nBytes,
                                           const LAYERPLANEDESCRIPTOR *plpd);
    HGLRC (APIENTRY *wglGetCurrentContext)();
    HDC (APIENTRY *wglGetCurrentDC)();
    int (APIENTRY *wglGetLayerPaletteEntries)(HDC hdc, int iLayerPlane,
                                              int iStart, int cEntries,
                                              const COLORREF *pcr);
    PROC (APIENTRY *wglGetProcAddress)(LPCSTR lpszProc);
    BOOL (APIENTRY *wglMakeCurrent)(HDC hDc, HGLRC newContext);
    BOOL (APIENTRY *wglRealizeLayerPalette)(HDC hdc, int iLayerPlane,
                                            BOOL bRealize);
    int (APIENTRY *wglSetLayerPaletteEntries)(HDC hdc, int iLayerPlane,
                                              int iStart, int cEntries,
                                              const COLORREF *pcr);
    BOOL (APIENTRY *wglShareLists)(HGLRC hrcSrvShare, HGLRC hrcSrvSource);
    BOOL (APIENTRY *wglSwapLayerBuffers)(HDC hdc, UINT fuFlags);
    BOOL (APIENTRY *wglUseFontBitmaps)(HDC hDC, DWORD first, DWORD count,
                                       DWORD listBase);
    BOOL (APIENTRY *wglUseFontBitmapsA)(HDC hDC, DWORD first, DWORD count,
                                        DWORD listBase);
    BOOL (APIENTRY *wglUseFontBitmapsW)(HDC hDC, DWORD first, DWORD count,
                                        DWORD listBase);
    BOOL (APIENTRY *wglUseFontOutlines)(HDC hDC, DWORD first, DWORD count,
                                        DWORD listBase, FLOAT deviation,
                                        FLOAT extrusion, int format,
                                        LPGLYPHMETRICSFLOAT lpgmf);
    BOOL (APIENTRY *wglUseFontOutlinesA)(HDC hDC, DWORD first, DWORD count,
                                         DWORD listBase, FLOAT deviation,
                                         FLOAT extrusion, int format,
                                         LPGLYPHMETRICSFLOAT lpgmf);
    BOOL (APIENTRY *wglUseFontOutlinesW)(HDC hDC, DWORD first, DWORD count,
                                         DWORD listBase, FLOAT deviation,
                                         FLOAT extrusion, int format,
                                         LPGLYPHMETRICSFLOAT lpgmf);

    // Construction
    WGL();

    // Operations
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct WGL

} // namespace wgl

#endif // ifndef __0AE3D5F1_596C_46B2_8613_C0DB4AA3727F_INCLUDED__
