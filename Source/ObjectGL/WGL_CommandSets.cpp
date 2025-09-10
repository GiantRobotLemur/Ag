//! @file ObjectGL/WGL_CommandSets.cpp
//! @brief The definition of Microsoft Windows-specific OpenGL entry points,
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

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CommandSetTools.hpp"
#include "Ag/ObjectGL/WGL_CommandSets.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// WGLAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Constructs an unresolved command set for the core API.
WGLAPI::WGLAPI()
{
}

// Grant read-only access to the underlying function pointers.
const WGL &WGLAPI::getRawAPI() const
{
    return _api;
}

// Resolve core API entry points.
void WGLAPI::resolve(const APIResolver* resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseAPI::resolve(resolver);
    }
}

// Calls ChoosePixelFormat().
int WGLAPI::choosePixelFormat(HDC hDc, const PIXELFORMATDESCRIPTOR *pPfd) const
{
    static const char *fnName = "ChoosePixelFormat";

    beforeCommand(fnName, _api.ChoosePixelFormat);
    int result = _api.ChoosePixelFormat(hDc, pPfd);
    afterCommand(fnName);

    return result;
}

// Calls DescribePixelFormat().
int WGLAPI::describePixelFormat(HDC hdc, int ipfd, UINT cjpfd,
                                const PIXELFORMATDESCRIPTOR *ppfd) const
{
    static const char *fnName = "DescribePixelFormat";

    beforeCommand(fnName, _api.DescribePixelFormat);
    int result = _api.DescribePixelFormat(hdc, ipfd, cjpfd, ppfd);
    afterCommand(fnName);

    return result;
}

// Calls GetEnhMetaFilePixelFormat().
UINT WGLAPI::getEnhMetaFilePixelFormat(HENHMETAFILE hemf, UINT cbBuffer,
                                       const PIXELFORMATDESCRIPTOR *ppfd) const
{
    static const char *fnName = "GetEnhMetaFilePixelFormat";

    beforeCommand(fnName, _api.GetEnhMetaFilePixelFormat);
    UINT result = _api.GetEnhMetaFilePixelFormat(hemf, cbBuffer, ppfd);
    afterCommand(fnName);

    return result;
}

// Calls GetPixelFormat().
int WGLAPI::getPixelFormat(HDC hdc) const
{
    static const char *fnName = "GetPixelFormat";

    beforeCommand(fnName, _api.GetPixelFormat);
    int result = _api.GetPixelFormat(hdc);
    afterCommand(fnName);

    return result;
}

// Calls SetPixelFormat().
BOOL WGLAPI::setPixelFormat(HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR *ppfd) const
{
    static const char *fnName = "SetPixelFormat";

    beforeCommand(fnName, _api.SetPixelFormat);
    BOOL result = _api.SetPixelFormat(hdc, ipfd, ppfd);
    afterCommand(fnName);

    return result;
}

// Calls SwapBuffers().
BOOL WGLAPI::swapBuffers(HDC hdc) const
{
    static const char *fnName = "SwapBuffers";

    beforeCommand(fnName, _api.SwapBuffers);
    BOOL result = _api.SwapBuffers(hdc);
    afterCommand(fnName);

    return result;
}

// Calls wglCopyContext().
BOOL WGLAPI::copyContext(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask) const
{
    static const char *fnName = "wglCopyContext";

    beforeCommand(fnName, _api.wglCopyContext);
    BOOL result = _api.wglCopyContext(hglrcSrc, hglrcDst, mask);
    afterCommand(fnName);

    return result;
}

// Calls wglCreateContext().
HGLRC WGLAPI::createContext(HDC hDc) const
{
    static const char *fnName = "wglCreateContext";

    beforeCommand(fnName, _api.wglCreateContext);
    HGLRC result = _api.wglCreateContext(hDc);
    afterCommand(fnName);

    return result;
}

// Calls wglCreateLayerContext().
HGLRC WGLAPI::createLayerContext(HDC hDc, int level) const
{
    static const char *fnName = "wglCreateLayerContext";

    beforeCommand(fnName, _api.wglCreateLayerContext);
    HGLRC result = _api.wglCreateLayerContext(hDc, level);
    afterCommand(fnName);

    return result;
}

// Calls wglDeleteContext().
BOOL WGLAPI::deleteContext(HGLRC oldContext) const
{
    static const char *fnName = "wglDeleteContext";

    beforeCommand(fnName, _api.wglDeleteContext);
    BOOL result = _api.wglDeleteContext(oldContext);
    afterCommand(fnName);

    return result;
}

// Calls wglDescribeLayerPlane().
BOOL WGLAPI::describeLayerPlane(HDC hDc, int pixelFormat, int layerPlane,
                                UINT nBytes, const LAYERPLANEDESCRIPTOR *plpd) const
{
    static const char *fnName = "wglDescribeLayerPlane";

    beforeCommand(fnName, _api.wglDescribeLayerPlane);
    BOOL result = _api.wglDescribeLayerPlane(hDc, pixelFormat, layerPlane,
                                             nBytes, plpd);
    afterCommand(fnName);

    return result;
}

// Calls wglGetCurrentContext().
HGLRC WGLAPI::getCurrentContext() const
{
    static const char *fnName = "wglGetCurrentContext";

    beforeCommand(fnName, _api.wglGetCurrentContext);
    HGLRC result = _api.wglGetCurrentContext();
    afterCommand(fnName);

    return result;
}

// Calls wglGetCurrentDC().
HDC WGLAPI::getCurrentDC() const
{
    static const char *fnName = "wglGetCurrentDC";

    beforeCommand(fnName, _api.wglGetCurrentDC);
    HDC result = _api.wglGetCurrentDC();
    afterCommand(fnName);

    return result;
}

// Calls wglGetLayerPaletteEntries().
int WGLAPI::getLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart,
                                   int cEntries, const COLORREF *pcr) const
{
    static const char *fnName = "wglGetLayerPaletteEntries";

    beforeCommand(fnName, _api.wglGetLayerPaletteEntries);
    int result = _api.wglGetLayerPaletteEntries(hdc, iLayerPlane, iStart,
                                                cEntries, pcr);
    afterCommand(fnName);

    return result;
}

// Calls wglGetProcAddress().
PROC WGLAPI::getProcAddress(LPCSTR lpszProc) const
{
    static const char *fnName = "wglGetProcAddress";

    beforeCommand(fnName, _api.wglGetProcAddress);
    PROC result = _api.wglGetProcAddress(lpszProc);
    afterCommand(fnName);

    return result;
}

// Calls wglMakeCurrent().
BOOL WGLAPI::makeCurrent(HDC hDc, HGLRC newContext) const
{
    static const char *fnName = "wglMakeCurrent";

    beforeCommand(fnName, _api.wglMakeCurrent);
    BOOL result = _api.wglMakeCurrent(hDc, newContext);
    afterCommand(fnName);

    return result;
}

// Calls wglRealizeLayerPalette().
BOOL WGLAPI::realizeLayerPalette(HDC hdc, int iLayerPlane, BOOL bRealize) const
{
    static const char *fnName = "wglRealizeLayerPalette";

    beforeCommand(fnName, _api.wglRealizeLayerPalette);
    BOOL result = _api.wglRealizeLayerPalette(hdc, iLayerPlane, bRealize);
    afterCommand(fnName);

    return result;
}

// Calls wglSetLayerPaletteEntries().
int WGLAPI::setLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart,
                                   int cEntries, const COLORREF *pcr) const
{
    static const char *fnName = "wglSetLayerPaletteEntries";

    beforeCommand(fnName, _api.wglSetLayerPaletteEntries);
    int result = _api.wglSetLayerPaletteEntries(hdc, iLayerPlane, iStart,
                                                cEntries, pcr);
    afterCommand(fnName);

    return result;
}

// Calls wglShareLists().
BOOL WGLAPI::shareLists(HGLRC hrcSrvShare, HGLRC hrcSrvSource) const
{
    static const char *fnName = "wglShareLists";

    beforeCommand(fnName, _api.wglShareLists);
    BOOL result = _api.wglShareLists(hrcSrvShare, hrcSrvSource);
    afterCommand(fnName);

    return result;
}

// Calls wglSwapLayerBuffers().
BOOL WGLAPI::swapLayerBuffers(HDC hdc, UINT fuFlags) const
{
    static const char *fnName = "wglSwapLayerBuffers";

    beforeCommand(fnName, _api.wglSwapLayerBuffers);
    BOOL result = _api.wglSwapLayerBuffers(hdc, fuFlags);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontBitmaps().
BOOL WGLAPI::useFontBitmaps(HDC hDC, DWORD first, DWORD count, DWORD listBase) const
{
    static const char *fnName = "wglUseFontBitmaps";

    beforeCommand(fnName, _api.wglUseFontBitmaps);
    BOOL result = _api.wglUseFontBitmaps(hDC, first, count, listBase);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontBitmapsA().
BOOL WGLAPI::useFontBitmapsA(HDC hDC, DWORD first, DWORD count, DWORD listBase) const
{
    static const char *fnName = "wglUseFontBitmapsA";

    beforeCommand(fnName, _api.wglUseFontBitmapsA);
    BOOL result = _api.wglUseFontBitmapsA(hDC, first, count, listBase);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontBitmapsW().
BOOL WGLAPI::useFontBitmapsW(HDC hDC, DWORD first, DWORD count, DWORD listBase) const
{
    static const char *fnName = "wglUseFontBitmapsW";

    beforeCommand(fnName, _api.wglUseFontBitmapsW);
    BOOL result = _api.wglUseFontBitmapsW(hDC, first, count, listBase);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontOutlines().
BOOL WGLAPI::useFontOutlines(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                             FLOAT deviation, FLOAT extrusion, int format,
                             LPGLYPHMETRICSFLOAT lpgmf) const
{
    static const char *fnName = "wglUseFontOutlines";

    beforeCommand(fnName, _api.wglUseFontOutlines);
    BOOL result = _api.wglUseFontOutlines(hDC, first, count, listBase, deviation,
                                          extrusion, format, lpgmf);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontOutlinesA().
BOOL WGLAPI::useFontOutlinesA(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                              FLOAT deviation, FLOAT extrusion, int format,
                              LPGLYPHMETRICSFLOAT lpgmf) const
{
    static const char *fnName = "wglUseFontOutlinesA";

    beforeCommand(fnName, _api.wglUseFontOutlinesA);
    BOOL result = _api.wglUseFontOutlinesA(hDC, first, count, listBase,
                                           deviation, extrusion, format, lpgmf);
    afterCommand(fnName);

    return result;
}

// Calls wglUseFontOutlinesW().
BOOL WGLAPI::useFontOutlinesW(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                              FLOAT deviation, FLOAT extrusion, int format,
                              LPGLYPHMETRICSFLOAT lpgmf) const
{
    static const char *fnName = "wglUseFontOutlinesW";

    beforeCommand(fnName, _api.wglUseFontOutlinesW);
    BOOL result = _api.wglUseFontOutlinesW(hDC, first, count, listBase,
                                           deviation, extrusion, format, lpgmf);
    afterCommand(fnName);

    return result;
}

} // namespace wgl

