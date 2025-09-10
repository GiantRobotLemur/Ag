//! @file Ag/ObjectGL/Extensions/OML.hpp
//! @brief The declaration of OML-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_OML_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OML_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
#include "../WGL_Types.hpp"
#endif // ifdef _WIN32

#ifdef _USES_GLX
#include "../GLX_Types.hpp"
#endif // ifdef _USES_GLX

#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// WGL_OML_sync_control extension API specification.
struct OMLSyncControl {
    // Public Members
    BOOL(APIENTRY *wglGetMscRate)(HDC hdc, INT32 *numerator, INT32 *denominator);
    BOOL(APIENTRY *wglGetSyncValues)(HDC hdc, INT64 *ust, INT64 *msc,
                                     INT64 *sbc);
    INT64(APIENTRY *wglSwapBuffersMsc)(HDC hdc, INT64 target_msc, INT64 divisor,
                                       INT64 remainder);
    INT64(APIENTRY *wglSwapLayerBuffersMsc)(HDC hdc, INT fuPlanes,
                                            INT64 target_msc, INT64 divisor,
                                            INT64 remainder);
    BOOL(APIENTRY *wglWaitForMsc)(HDC hdc, INT64 target_msc, INT64 divisor,
                                  INT64 remainder, INT64 *ust, INT64 *msc,
                                  INT64 *sbc);
    BOOL(APIENTRY *wglWaitForSbc)(HDC hdc, INT64 target_sbc, INT64 *ust,
                                  INT64 *msc, INT64 *sbc);

   // Construction
    OMLSyncControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OMLSyncControl

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// GLX_OML_sync_control extension API specification.
struct OMLSyncControl {
    // Public Members
    Bool(APIENTRY *glXGetMscRate)(Display *dpy, GLXDrawable drawable,
                                  int32_t *numerator, int32_t *denominator);
    Bool(APIENTRY *glXGetSyncValues)(Display *dpy, GLXDrawable drawable,
                                     int64_t *ust, int64_t *msc, int64_t *sbc);
    int64_t(APIENTRY *glXSwapBuffersMsc)(Display *dpy, GLXDrawable drawable,
                                         int64_t target_msc, int64_t divisor,
                                         int64_t remainder);
    Bool(APIENTRY *glXWaitForMsc)(Display *dpy, GLXDrawable drawable,
                                  int64_t target_msc, int64_t divisor,
                                  int64_t remainder, int64_t *ust, int64_t *msc,
                                  int64_t *sbc);
    Bool(APIENTRY *glXWaitForSbc)(Display *dpy, GLXDrawable drawable,
                                  int64_t target_sbc, int64_t *ust,
                                  int64_t *msc, int64_t *sbc);

   // Construction
    OMLSyncControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct OMLSyncControl

} // namespace glx
#endif // ifdef _USES_GLX

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
