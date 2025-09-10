//! @file Ag/ObjectGL/Extensions/OMLCommands.hpp
//! @brief The declaration of OML-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_OML_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OML_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "OML.hpp"
#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the WGL_OML_sync_control extension API.
class OMLSyncControlAPI : public gl::BaseExtension
{
public:
    // Construction
    OMLSyncControlAPI();

    // Accessors
    const OMLSyncControl &getRawAPI() const;

    // Operations
    BOOL getMscRate(HDC hdc, INT32 *numerator, INT32 *denominator) const;
    BOOL getSyncValues(HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc) const;
    INT64 swapBuffersMsc(HDC hdc, INT64 target_msc, INT64 divisor,
                         INT64 remainder) const;
    INT64 swapLayerBuffersMsc(HDC hdc, INT fuPlanes, INT64 target_msc,
                              INT64 divisor, INT64 remainder) const;
    BOOL waitForMsc(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder,
                    INT64 *ust, INT64 *msc, INT64 *sbc) const;
    BOOL waitForSbc(HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc,
                    INT64 *sbc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OMLSyncControl _api;
};

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

// Manages the entry points for the GLX_OML_sync_control extension API.
class OMLSyncControlAPI : public gl::BaseExtension
{
public:
    // Construction
    OMLSyncControlAPI();

    // Accessors
    const OMLSyncControl &getRawAPI() const;

    // Operations
    Bool xGetMscRate(Display *dpy, GLXDrawable drawable, int32_t *numerator,
                     int32_t *denominator) const;
    Bool xGetSyncValues(Display *dpy, GLXDrawable drawable, int64_t *ust,
                        int64_t *msc, int64_t *sbc) const;
    int64_t xSwapBuffersMsc(Display *dpy, GLXDrawable drawable,
                            int64_t target_msc, int64_t divisor,
                            int64_t remainder) const;
    Bool xWaitForMsc(Display *dpy, GLXDrawable drawable, int64_t target_msc,
                     int64_t divisor, int64_t remainder, int64_t *ust,
                     int64_t *msc, int64_t *sbc) const;
    Bool xWaitForSbc(Display *dpy, GLXDrawable drawable, int64_t target_sbc,
                     int64_t *ust, int64_t *msc, int64_t *sbc) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OMLSyncControl _api;
};

} // namespace glx
#endif // ifdef _USES_GLX
#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
