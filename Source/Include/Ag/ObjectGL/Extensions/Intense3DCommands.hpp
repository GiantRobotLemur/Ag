//! @file Ag/ObjectGL/Extensions/Intense3DCommands.hpp
//! @brief The declaration of Intense 3D-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_INTENSE_3D_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_INTENSE_3D_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Intense3D.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the WGL_I3D_digital_video_control extension API.
class I3DDigitalVideoControlAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DDigitalVideoControlAPI();

    // Accessors
    const I3DDigitalVideoControl &getRawAPI() const;

    // Operations
    BOOL getDigitalVideoParameters(HDC hDC, int iAttribute, int *piValue) const;
    BOOL setDigitalVideoParameters(HDC hDC, int iAttribute, const int *piValue) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DDigitalVideoControl _api;
};

// Manages the entry points for the WGL_I3D_gamma extension API.
class I3DGammaAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DGammaAPI();

    // Accessors
    const I3DGamma &getRawAPI() const;

    // Operations
    BOOL getGammaTable(HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen,
                       USHORT *puBlue) const;
    BOOL getGammaTableParameters(HDC hDC, int iAttribute, int *piValue) const;
    BOOL setGammaTable(HDC hDC, int iEntries, const USHORT *puRed,
                       const USHORT *puGreen, const USHORT *puBlue) const;
    BOOL setGammaTableParameters(HDC hDC, int iAttribute, const int *piValue) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DGamma _api;
};

// Manages the entry points for the WGL_I3D_genlock extension API.
class I3DGenlockAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DGenlockAPI();

    // Accessors
    const I3DGenlock &getRawAPI() const;

    // Operations
    BOOL disableGenlock(HDC hDC) const;
    BOOL enableGenlock(HDC hDC) const;
    BOOL genlockSampleRate(HDC hDC, UINT uRate) const;
    BOOL genlockSourceDelay(HDC hDC, UINT uDelay) const;
    BOOL genlockSourceEdge(HDC hDC, UINT uEdge) const;
    BOOL genlockSource(HDC hDC, UINT uSource) const;
    BOOL getGenlockSampleRate(HDC hDC, UINT *uRate) const;
    BOOL getGenlockSourceDelay(HDC hDC, UINT *uDelay) const;
    BOOL getGenlockSourceEdge(HDC hDC, UINT *uEdge) const;
    BOOL getGenlockSource(HDC hDC, UINT *uSource) const;
    BOOL isEnabledGenlock(HDC hDC, BOOL *pFlag) const;
    BOOL queryGenlockMaxSourceDelay(HDC hDC, UINT *uMaxLineDelay,
                                    UINT *uMaxPixelDelay) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DGenlock _api;
};

// Manages the entry points for the WGL_I3D_image_buffer extension API.
class I3DImageBufferAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DImageBufferAPI();

    // Accessors
    const I3DImageBuffer &getRawAPI() const;

    // Operations
    BOOL associateImageBufferEvents(HDC hDC, const HANDLE *pEvent,
                                    const LPVOID *pAddress, const DWORD *pSize,
                                    UINT count) const;
    LPVOID createImageBuffer(HDC hDC, DWORD dwSize, UINT uFlags) const;
    BOOL destroyImageBuffer(HDC hDC, LPVOID pAddress) const;
    BOOL releaseImageBufferEvents(HDC hDC, const LPVOID *pAddress, UINT count) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DImageBuffer _api;
};

// Manages the entry points for the WGL_I3D_swap_frame_lock extension API.
class I3DSwapFrameLockAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DSwapFrameLockAPI();

    // Accessors
    const I3DSwapFrameLock &getRawAPI() const;

    // Operations
    BOOL disableFrameLock() const;
    BOOL enableFrameLock() const;
    BOOL isEnabledFrameLock(BOOL *pFlag) const;
    BOOL queryFrameLockMaster(BOOL *pFlag) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DSwapFrameLock _api;
};

// Manages the entry points for the WGL_I3D_swap_frame_usage extension API.
class I3DSwapFrameUsageAPI : public gl::BaseExtension
{
public:
    // Construction
    I3DSwapFrameUsageAPI();

    // Accessors
    const I3DSwapFrameUsage &getRawAPI() const;

    // Operations
    BOOL beginFrameTracking() const;
    BOOL endFrameTracking() const;
    BOOL getFrameUsage(float *pUsage) const;
    BOOL queryFrameTracking(DWORD *pFrameCount, DWORD *pMissedFrames,
                            float *pLastMissedUsage) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    I3DSwapFrameUsage _api;
};

} // namespace wgl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
