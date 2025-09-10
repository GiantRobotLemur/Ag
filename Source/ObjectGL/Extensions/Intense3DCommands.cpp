//! @file ObjectGL/Extensions/Intense3DCommands.cpp
//! @brief The definition of Intense 3D-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/Intense3DCommands.hpp"
#include "CommandSetTools.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// I3DDigitalVideoControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_digital_video_control extension.
I3DDigitalVideoControlAPI::I3DDigitalVideoControlAPI() :
    BaseExtension("WGL_I3D_digital_video_control")
{
}

// Grant read-only access to the underlying function pointers.
const I3DDigitalVideoControl &I3DDigitalVideoControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_digital_video_control entry points.
void I3DDigitalVideoControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetDigitalVideoParametersI3D().
BOOL I3DDigitalVideoControlAPI::getDigitalVideoParameters(HDC hDC,
                                                          int iAttribute,
                                                          int *piValue) const
{
    static const char *fnName = "wglGetDigitalVideoParametersI3D";

    beforeCommand(fnName, _api.wglGetDigitalVideoParameters);
    BOOL result = _api.wglGetDigitalVideoParameters(hDC, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

// Calls wglSetDigitalVideoParametersI3D().
BOOL I3DDigitalVideoControlAPI::setDigitalVideoParameters(HDC hDC,
                                                          int iAttribute,
                                                          const int *piValue) const
{
    static const char *fnName = "wglSetDigitalVideoParametersI3D";

    beforeCommand(fnName, _api.wglSetDigitalVideoParameters);
    BOOL result = _api.wglSetDigitalVideoParameters(hDC, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// I3DGammaAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_gamma extension.
I3DGammaAPI::I3DGammaAPI() :
    BaseExtension("WGL_I3D_gamma")
{
}

// Grant read-only access to the underlying function pointers.
const I3DGamma &I3DGammaAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_gamma entry points.
void I3DGammaAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglGetGammaTableI3D().
BOOL I3DGammaAPI::getGammaTable(HDC hDC, int iEntries, USHORT *puRed,
                                USHORT *puGreen, USHORT *puBlue) const
{
    static const char *fnName = "wglGetGammaTableI3D";

    beforeCommand(fnName, _api.wglGetGammaTable);
    BOOL result = _api.wglGetGammaTable(hDC, iEntries, puRed, puGreen, puBlue);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGammaTableParametersI3D().
BOOL I3DGammaAPI::getGammaTableParameters(HDC hDC, int iAttribute, int *piValue) const
{
    static const char *fnName = "wglGetGammaTableParametersI3D";

    beforeCommand(fnName, _api.wglGetGammaTableParameters);
    BOOL result = _api.wglGetGammaTableParameters(hDC, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

// Calls wglSetGammaTableI3D().
BOOL I3DGammaAPI::setGammaTable(HDC hDC, int iEntries, const USHORT *puRed,
                                const USHORT *puGreen, const USHORT *puBlue) const
{
    static const char *fnName = "wglSetGammaTableI3D";

    beforeCommand(fnName, _api.wglSetGammaTable);
    BOOL result = _api.wglSetGammaTable(hDC, iEntries, puRed, puGreen, puBlue);
    afterCommand(fnName);

    return result;
}

// Calls wglSetGammaTableParametersI3D().
BOOL I3DGammaAPI::setGammaTableParameters(HDC hDC, int iAttribute,
                                          const int *piValue) const
{
    static const char *fnName = "wglSetGammaTableParametersI3D";

    beforeCommand(fnName, _api.wglSetGammaTableParameters);
    BOOL result = _api.wglSetGammaTableParameters(hDC, iAttribute, piValue);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// I3DGenlockAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_genlock extension.
I3DGenlockAPI::I3DGenlockAPI() :
    BaseExtension("WGL_I3D_genlock")
{
}

// Grant read-only access to the underlying function pointers.
const I3DGenlock &I3DGenlockAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_genlock entry points.
void I3DGenlockAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglDisableGenlockI3D().
BOOL I3DGenlockAPI::disableGenlock(HDC hDC) const
{
    static const char *fnName = "wglDisableGenlockI3D";

    beforeCommand(fnName, _api.wglDisableGenlock);
    BOOL result = _api.wglDisableGenlock(hDC);
    afterCommand(fnName);

    return result;
}

// Calls wglEnableGenlockI3D().
BOOL I3DGenlockAPI::enableGenlock(HDC hDC) const
{
    static const char *fnName = "wglEnableGenlockI3D";

    beforeCommand(fnName, _api.wglEnableGenlock);
    BOOL result = _api.wglEnableGenlock(hDC);
    afterCommand(fnName);

    return result;
}

// Calls wglGenlockSampleRateI3D().
BOOL I3DGenlockAPI::genlockSampleRate(HDC hDC, UINT uRate) const
{
    static const char *fnName = "wglGenlockSampleRateI3D";

    beforeCommand(fnName, _api.wglGenlockSampleRate);
    BOOL result = _api.wglGenlockSampleRate(hDC, uRate);
    afterCommand(fnName);

    return result;
}

// Calls wglGenlockSourceDelayI3D().
BOOL I3DGenlockAPI::genlockSourceDelay(HDC hDC, UINT uDelay) const
{
    static const char *fnName = "wglGenlockSourceDelayI3D";

    beforeCommand(fnName, _api.wglGenlockSourceDelay);
    BOOL result = _api.wglGenlockSourceDelay(hDC, uDelay);
    afterCommand(fnName);

    return result;
}

// Calls wglGenlockSourceEdgeI3D().
BOOL I3DGenlockAPI::genlockSourceEdge(HDC hDC, UINT uEdge) const
{
    static const char *fnName = "wglGenlockSourceEdgeI3D";

    beforeCommand(fnName, _api.wglGenlockSourceEdge);
    BOOL result = _api.wglGenlockSourceEdge(hDC, uEdge);
    afterCommand(fnName);

    return result;
}

// Calls wglGenlockSourceI3D().
BOOL I3DGenlockAPI::genlockSource(HDC hDC, UINT uSource) const
{
    static const char *fnName = "wglGenlockSourceI3D";

    beforeCommand(fnName, _api.wglGenlockSource);
    BOOL result = _api.wglGenlockSource(hDC, uSource);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGenlockSampleRateI3D().
BOOL I3DGenlockAPI::getGenlockSampleRate(HDC hDC, UINT *uRate) const
{
    static const char *fnName = "wglGetGenlockSampleRateI3D";

    beforeCommand(fnName, _api.wglGetGenlockSampleRate);
    BOOL result = _api.wglGetGenlockSampleRate(hDC, uRate);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGenlockSourceDelayI3D().
BOOL I3DGenlockAPI::getGenlockSourceDelay(HDC hDC, UINT *uDelay) const
{
    static const char *fnName = "wglGetGenlockSourceDelayI3D";

    beforeCommand(fnName, _api.wglGetGenlockSourceDelay);
    BOOL result = _api.wglGetGenlockSourceDelay(hDC, uDelay);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGenlockSourceEdgeI3D().
BOOL I3DGenlockAPI::getGenlockSourceEdge(HDC hDC, UINT *uEdge) const
{
    static const char *fnName = "wglGetGenlockSourceEdgeI3D";

    beforeCommand(fnName, _api.wglGetGenlockSourceEdge);
    BOOL result = _api.wglGetGenlockSourceEdge(hDC, uEdge);
    afterCommand(fnName);

    return result;
}

// Calls wglGetGenlockSourceI3D().
BOOL I3DGenlockAPI::getGenlockSource(HDC hDC, UINT *uSource) const
{
    static const char *fnName = "wglGetGenlockSourceI3D";

    beforeCommand(fnName, _api.wglGetGenlockSource);
    BOOL result = _api.wglGetGenlockSource(hDC, uSource);
    afterCommand(fnName);

    return result;
}

// Calls wglIsEnabledGenlockI3D().
BOOL I3DGenlockAPI::isEnabledGenlock(HDC hDC, BOOL *pFlag) const
{
    static const char *fnName = "wglIsEnabledGenlockI3D";

    beforeCommand(fnName, _api.wglIsEnabledGenlock);
    BOOL result = _api.wglIsEnabledGenlock(hDC, pFlag);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryGenlockMaxSourceDelayI3D().
BOOL I3DGenlockAPI::queryGenlockMaxSourceDelay(HDC hDC, UINT *uMaxLineDelay,
                                               UINT *uMaxPixelDelay) const
{
    static const char *fnName = "wglQueryGenlockMaxSourceDelayI3D";

    beforeCommand(fnName, _api.wglQueryGenlockMaxSourceDelay);
    BOOL result = _api.wglQueryGenlockMaxSourceDelay(hDC, uMaxLineDelay,
                                                     uMaxPixelDelay);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// I3DImageBufferAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_image_buffer extension.
I3DImageBufferAPI::I3DImageBufferAPI() :
    BaseExtension("WGL_I3D_image_buffer")
{
}

// Grant read-only access to the underlying function pointers.
const I3DImageBuffer &I3DImageBufferAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_image_buffer entry points.
void I3DImageBufferAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglAssociateImageBufferEventsI3D().
BOOL I3DImageBufferAPI::associateImageBufferEvents(HDC hDC, const HANDLE *pEvent,
                                                   const LPVOID *pAddress,
                                                   const DWORD *pSize,
                                                   UINT count) const
{
    static const char *fnName = "wglAssociateImageBufferEventsI3D";

    beforeCommand(fnName, _api.wglAssociateImageBufferEvents);
    BOOL result = _api.wglAssociateImageBufferEvents(hDC, pEvent, pAddress,
                                                     pSize, count);
    afterCommand(fnName);

    return result;
}

// Calls wglCreateImageBufferI3D().
LPVOID I3DImageBufferAPI::createImageBuffer(HDC hDC, DWORD dwSize, UINT uFlags) const
{
    static const char *fnName = "wglCreateImageBufferI3D";

    beforeCommand(fnName, _api.wglCreateImageBuffer);
    LPVOID result = _api.wglCreateImageBuffer(hDC, dwSize, uFlags);
    afterCommand(fnName);

    return result;
}

// Calls wglDestroyImageBufferI3D().
BOOL I3DImageBufferAPI::destroyImageBuffer(HDC hDC, LPVOID pAddress) const
{
    static const char *fnName = "wglDestroyImageBufferI3D";

    beforeCommand(fnName, _api.wglDestroyImageBuffer);
    BOOL result = _api.wglDestroyImageBuffer(hDC, pAddress);
    afterCommand(fnName);

    return result;
}

// Calls wglReleaseImageBufferEventsI3D().
BOOL I3DImageBufferAPI::releaseImageBufferEvents(HDC hDC, const LPVOID *pAddress,
                                                 UINT count) const
{
    static const char *fnName = "wglReleaseImageBufferEventsI3D";

    beforeCommand(fnName, _api.wglReleaseImageBufferEvents);
    BOOL result = _api.wglReleaseImageBufferEvents(hDC, pAddress, count);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// I3DSwapFrameLockAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_swap_frame_lock extension.
I3DSwapFrameLockAPI::I3DSwapFrameLockAPI() :
    BaseExtension("WGL_I3D_swap_frame_lock")
{
}

// Grant read-only access to the underlying function pointers.
const I3DSwapFrameLock &I3DSwapFrameLockAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_swap_frame_lock entry points.
void I3DSwapFrameLockAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglDisableFrameLockI3D().
BOOL I3DSwapFrameLockAPI::disableFrameLock() const
{
    static const char *fnName = "wglDisableFrameLockI3D";

    beforeCommand(fnName, _api.wglDisableFrameLock);
    BOOL result = _api.wglDisableFrameLock();
    afterCommand(fnName);

    return result;
}

// Calls wglEnableFrameLockI3D().
BOOL I3DSwapFrameLockAPI::enableFrameLock() const
{
    static const char *fnName = "wglEnableFrameLockI3D";

    beforeCommand(fnName, _api.wglEnableFrameLock);
    BOOL result = _api.wglEnableFrameLock();
    afterCommand(fnName);

    return result;
}

// Calls wglIsEnabledFrameLockI3D().
BOOL I3DSwapFrameLockAPI::isEnabledFrameLock(BOOL *pFlag) const
{
    static const char *fnName = "wglIsEnabledFrameLockI3D";

    beforeCommand(fnName, _api.wglIsEnabledFrameLock);
    BOOL result = _api.wglIsEnabledFrameLock(pFlag);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryFrameLockMasterI3D().
BOOL I3DSwapFrameLockAPI::queryFrameLockMaster(BOOL *pFlag) const
{
    static const char *fnName = "wglQueryFrameLockMasterI3D";

    beforeCommand(fnName, _api.wglQueryFrameLockMaster);
    BOOL result = _api.wglQueryFrameLockMaster(pFlag);
    afterCommand(fnName);

    return result;
}

////////////////////////////////////////////////////////////////////////////////
// I3DSwapFrameUsageAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_I3D_swap_frame_usage extension.
I3DSwapFrameUsageAPI::I3DSwapFrameUsageAPI() :
    BaseExtension("WGL_I3D_swap_frame_usage")
{
}

// Grant read-only access to the underlying function pointers.
const I3DSwapFrameUsage &I3DSwapFrameUsageAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_I3D_swap_frame_usage entry points.
void I3DSwapFrameUsageAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglBeginFrameTrackingI3D().
BOOL I3DSwapFrameUsageAPI::beginFrameTracking() const
{
    static const char *fnName = "wglBeginFrameTrackingI3D";

    beforeCommand(fnName, _api.wglBeginFrameTracking);
    BOOL result = _api.wglBeginFrameTracking();
    afterCommand(fnName);

    return result;
}

// Calls wglEndFrameTrackingI3D().
BOOL I3DSwapFrameUsageAPI::endFrameTracking() const
{
    static const char *fnName = "wglEndFrameTrackingI3D";

    beforeCommand(fnName, _api.wglEndFrameTracking);
    BOOL result = _api.wglEndFrameTracking();
    afterCommand(fnName);

    return result;
}

// Calls wglGetFrameUsageI3D().
BOOL I3DSwapFrameUsageAPI::getFrameUsage(float *pUsage) const
{
    static const char *fnName = "wglGetFrameUsageI3D";

    beforeCommand(fnName, _api.wglGetFrameUsage);
    BOOL result = _api.wglGetFrameUsage(pUsage);
    afterCommand(fnName);

    return result;
}

// Calls wglQueryFrameTrackingI3D().
BOOL I3DSwapFrameUsageAPI::queryFrameTracking(DWORD *pFrameCount,
                                              DWORD *pMissedFrames,
                                              float *pLastMissedUsage) const
{
    static const char *fnName = "wglQueryFrameTrackingI3D";

    beforeCommand(fnName, _api.wglQueryFrameTracking);
    BOOL result = _api.wglQueryFrameTracking(pFrameCount, pMissedFrames,
                                             pLastMissedUsage);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
////////////////////////////////////////////////////////////////////////////////

