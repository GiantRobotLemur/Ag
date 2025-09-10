//! @file Ag/ObjectGL/WGL_CommandSets.hpp
//! @brief The declaration of wrappers for Window-specific OpenGL entry points.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This file was generated from the Khronos XML API definition using
//! a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __69715089_2592_4213_BA85_9662D7A21643_INCLUDED__
#define __69715089_2592_4213_BA85_9662D7A21643_INCLUDED__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "WGL_API.hpp"

namespace wgl {

//! @brief A class which wraps all core Windows-specific entry points so that
//! they can be called with more useful data types and with inherit type
//! checking and error detection.
class WGLAPI : public gl::BaseAPI
{
public:
    // Construction
    WGLAPI();

    // Accessors
    const WGL &getRawAPI() const;

    // Operations

    // WGL 1.0
    int choosePixelFormat(HDC hDc, const PIXELFORMATDESCRIPTOR *pPfd) const;
    int describePixelFormat(HDC hdc, int ipfd, UINT cjpfd,
                            const PIXELFORMATDESCRIPTOR *ppfd) const;
    UINT getEnhMetaFilePixelFormat(HENHMETAFILE hemf, UINT cbBuffer,
                                   const PIXELFORMATDESCRIPTOR *ppfd) const;
    int getPixelFormat(HDC hdc) const;
    BOOL setPixelFormat(HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR *ppfd) const;
    BOOL swapBuffers(HDC hdc) const;
    BOOL copyContext(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask) const;
    HGLRC createContext(HDC hDc) const;
    HGLRC createLayerContext(HDC hDc, int level) const;
    BOOL deleteContext(HGLRC oldContext) const;
    BOOL describeLayerPlane(HDC hDc, int pixelFormat, int layerPlane,
                            UINT nBytes, const LAYERPLANEDESCRIPTOR *plpd) const;
    HGLRC getCurrentContext() const;
    HDC getCurrentDC() const;
    int getLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart,
                               int cEntries, const COLORREF *pcr) const;
    PROC getProcAddress(LPCSTR lpszProc) const;
    BOOL makeCurrent(HDC hDc, HGLRC newContext) const;
    BOOL realizeLayerPalette(HDC hdc, int iLayerPlane, BOOL bRealize) const;
    int setLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart,
                               int cEntries, const COLORREF *pcr) const;
    BOOL shareLists(HGLRC hrcSrvShare, HGLRC hrcSrvSource) const;
    BOOL swapLayerBuffers(HDC hdc, UINT fuFlags) const;
    BOOL useFontBitmaps(HDC hDC, DWORD first, DWORD count, DWORD listBase) const;
    BOOL useFontBitmapsA(HDC hDC, DWORD first, DWORD count, DWORD listBase) const;
    BOOL useFontBitmapsW(HDC hDC, DWORD first, DWORD count, DWORD listBase) const;
    BOOL useFontOutlines(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                         FLOAT deviation, FLOAT extrusion, int format,
                         LPGLYPHMETRICSFLOAT lpgmf) const;
    BOOL useFontOutlinesA(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                          FLOAT deviation, FLOAT extrusion, int format,
                          LPGLYPHMETRICSFLOAT lpgmf) const;
    BOOL useFontOutlinesW(HDC hDC, DWORD first, DWORD count, DWORD listBase,
                          FLOAT deviation, FLOAT extrusion, int format,
                          LPGLYPHMETRICSFLOAT lpgmf) const;

    // Overrides
    virtual void resolve(const APIResolver* resolver) override;

private:
    WGL _api;
};

} // namespace wgl


#endif // ifndef __69715089_2592_4213_BA85_9662D7A21643_INCLUDED__
