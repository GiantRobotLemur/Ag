//! @file ObjectGL/Extensions/OMLCommands.cpp
//! @brief The definition of OML-specific extensions to the OpenGL Command
//! set wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/Extensions/OMLCommands.hpp"
#include "CommandSetTools.hpp"

#ifdef _WIN32
namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// OMLSyncControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_OML_sync_control extension.
OMLSyncControlAPI::OMLSyncControlAPI() :
    BaseExtension("WGL_OML_sync_control")
{
}

// Grant read-only access to the underlying function pointers.
const OMLSyncControl &OMLSyncControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_OML_sync_control entry points.
void OMLSyncControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetMscRateOML().
BOOL OMLSyncControlAPI::getMscRate(HDC hdc, INT32 *numerator, INT32 *denominator) const
{
    static const char *fnName = "wglGetMscRateOML";

    beforeCommand(fnName, _api.wglGetMscRate);
    BOOL result = _api.wglGetMscRate(hdc, numerator, denominator);
    afterCommand(fnName);

    return result;
}

// Calls wglGetSyncValuesOML().
BOOL OMLSyncControlAPI::getSyncValues(HDC hdc, INT64 *ust, INT64 *msc,
                                      INT64 *sbc) const
{
    static const char *fnName = "wglGetSyncValuesOML";

    beforeCommand(fnName, _api.wglGetSyncValues);
    BOOL result = _api.wglGetSyncValues(hdc, ust, msc, sbc);
    afterCommand(fnName);

    return result;
}

// Calls wglSwapBuffersMscOML().
INT64 OMLSyncControlAPI::swapBuffersMsc(HDC hdc, INT64 target_msc, INT64 divisor,
                                        INT64 remainder) const
{
    static const char *fnName = "wglSwapBuffersMscOML";

    beforeCommand(fnName, _api.wglSwapBuffersMsc);
    INT64 result = _api.wglSwapBuffersMsc(hdc, target_msc, divisor, remainder);
    afterCommand(fnName);

    return result;
}

// Calls wglSwapLayerBuffersMscOML().
INT64 OMLSyncControlAPI::swapLayerBuffersMsc(HDC hdc, INT fuPlanes,
                                             INT64 target_msc, INT64 divisor,
                                             INT64 remainder) const
{
    static const char *fnName = "wglSwapLayerBuffersMscOML";

    beforeCommand(fnName, _api.wglSwapLayerBuffersMsc);
    INT64 result = _api.wglSwapLayerBuffersMsc(hdc, fuPlanes, target_msc,
                                               divisor, remainder);
    afterCommand(fnName);

    return result;
}

// Calls wglWaitForMscOML().
BOOL OMLSyncControlAPI::waitForMsc(HDC hdc, INT64 target_msc, INT64 divisor,
                                   INT64 remainder, INT64 *ust, INT64 *msc,
                                   INT64 *sbc) const
{
    static const char *fnName = "wglWaitForMscOML";

    beforeCommand(fnName, _api.wglWaitForMsc);
    BOOL result = _api.wglWaitForMsc(hdc, target_msc, divisor, remainder, ust,
                                     msc, sbc);
    afterCommand(fnName);

    return result;
}

// Calls wglWaitForSbcOML().
BOOL OMLSyncControlAPI::waitForSbc(HDC hdc, INT64 target_sbc, INT64 *ust,
                                   INT64 *msc, INT64 *sbc) const
{
    static const char *fnName = "wglWaitForSbcOML";

    beforeCommand(fnName, _api.wglWaitForSbc);
    BOOL result = _api.wglWaitForSbc(hdc, target_sbc, ust, msc, sbc);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
#endif // ifdef _WIN32

#ifdef _USES_GLX
namespace glx {

////////////////////////////////////////////////////////////////////////////////
// OMLSyncControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GLX_OML_sync_control extension.
OMLSyncControlAPI::OMLSyncControlAPI() :
    BaseExtension("GLX_OML_sync_control")
{
}

// Grant read-only access to the underlying function pointers.
const OMLSyncControl &OMLSyncControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GLX_OML_sync_control entry points.
void OMLSyncControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glXGetMscRateOML().
Bool OMLSyncControlAPI::xGetMscRate(Display *dpy, GLXDrawable drawable,
                                    int32_t *numerator, int32_t *denominator) const
{
    static const char *fnName = "glXGetMscRateOML";

    beforeCommand(fnName, _api.glXGetMscRate);
    Bool result = _api.glXGetMscRate(dpy, drawable, numerator, denominator);
    afterCommand(fnName);

    return result;
}

// Calls glXGetSyncValuesOML().
Bool OMLSyncControlAPI::xGetSyncValues(Display *dpy, GLXDrawable drawable,
                                       int64_t *ust, int64_t *msc, int64_t *sbc) const
{
    static const char *fnName = "glXGetSyncValuesOML";

    beforeCommand(fnName, _api.glXGetSyncValues);
    Bool result = _api.glXGetSyncValues(dpy, drawable, ust, msc, sbc);
    afterCommand(fnName);

    return result;
}

// Calls glXSwapBuffersMscOML().
int64_t OMLSyncControlAPI::xSwapBuffersMsc(Display *dpy, GLXDrawable drawable,
                                           int64_t target_msc, int64_t divisor,
                                           int64_t remainder) const
{
    static const char *fnName = "glXSwapBuffersMscOML";

    beforeCommand(fnName, _api.glXSwapBuffersMsc);
    int64_t result = _api.glXSwapBuffersMsc(dpy, drawable, target_msc, divisor,
                                            remainder);
    afterCommand(fnName);

    return result;
}

// Calls glXWaitForMscOML().
Bool OMLSyncControlAPI::xWaitForMsc(Display *dpy, GLXDrawable drawable,
                                    int64_t target_msc, int64_t divisor,
                                    int64_t remainder, int64_t *ust,
                                    int64_t *msc, int64_t *sbc) const
{
    static const char *fnName = "glXWaitForMscOML";

    beforeCommand(fnName, _api.glXWaitForMsc);
    Bool result = _api.glXWaitForMsc(dpy, drawable, target_msc, divisor,
                                     remainder, ust, msc, sbc);
    afterCommand(fnName);

    return result;
}

// Calls glXWaitForSbcOML().
Bool OMLSyncControlAPI::xWaitForSbc(Display *dpy, GLXDrawable drawable,
                                    int64_t target_sbc, int64_t *ust,
                                    int64_t *msc, int64_t *sbc) const
{
    static const char *fnName = "glXWaitForSbcOML";

    beforeCommand(fnName, _api.glXWaitForSbc);
    Bool result = _api.glXWaitForSbc(dpy, drawable, target_sbc, ust, msc, sbc);
    afterCommand(fnName);

    return result;
}

} // namespace glx
#endif // ifdef _USES_GLX
////////////////////////////////////////////////////////////////////////////////

