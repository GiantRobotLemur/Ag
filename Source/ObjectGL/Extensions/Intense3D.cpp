//! @file ObjectGL/Extensions/Intense3D.cpp
//! @brief The definition of Intense 3D-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Intense3D.hpp"

namespace wgl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const gl::EntryOffset __I3DDigitalVideoControlEntryPoints[] = {
    { offsetof(I3DDigitalVideoControl, wglGetDigitalVideoParameters), "wglGetDigitalVideoParametersI3D" },
    { offsetof(I3DDigitalVideoControl, wglSetDigitalVideoParameters), "wglSetDigitalVideoParametersI3D" },
};

static const gl::EntryOffset __I3DGammaEntryPoints[] = {
    { offsetof(I3DGamma, wglGetGammaTable), "wglGetGammaTableI3D" },
    { offsetof(I3DGamma, wglGetGammaTableParameters), "wglGetGammaTableParametersI3D" },
    { offsetof(I3DGamma, wglSetGammaTable), "wglSetGammaTableI3D" },
    { offsetof(I3DGamma, wglSetGammaTableParameters), "wglSetGammaTableParametersI3D" },
};

static const gl::EntryOffset __I3DGenlockEntryPoints[] = {
    { offsetof(I3DGenlock, wglDisableGenlock), "wglDisableGenlockI3D" },
    { offsetof(I3DGenlock, wglEnableGenlock), "wglEnableGenlockI3D" },
    { offsetof(I3DGenlock, wglGenlockSampleRate), "wglGenlockSampleRateI3D" },
    { offsetof(I3DGenlock, wglGenlockSourceDelay), "wglGenlockSourceDelayI3D" },
    { offsetof(I3DGenlock, wglGenlockSourceEdge), "wglGenlockSourceEdgeI3D" },
    { offsetof(I3DGenlock, wglGenlockSource), "wglGenlockSourceI3D" },
    { offsetof(I3DGenlock, wglGetGenlockSampleRate), "wglGetGenlockSampleRateI3D" },
    { offsetof(I3DGenlock, wglGetGenlockSourceDelay), "wglGetGenlockSourceDelayI3D" },
    { offsetof(I3DGenlock, wglGetGenlockSourceEdge), "wglGetGenlockSourceEdgeI3D" },
    { offsetof(I3DGenlock, wglGetGenlockSource), "wglGetGenlockSourceI3D" },
    { offsetof(I3DGenlock, wglIsEnabledGenlock), "wglIsEnabledGenlockI3D" },
    { offsetof(I3DGenlock, wglQueryGenlockMaxSourceDelay), "wglQueryGenlockMaxSourceDelayI3D" },
};

static const gl::EntryOffset __I3DImageBufferEntryPoints[] = {
    { offsetof(I3DImageBuffer, wglAssociateImageBufferEvents), "wglAssociateImageBufferEventsI3D" },
    { offsetof(I3DImageBuffer, wglCreateImageBuffer), "wglCreateImageBufferI3D" },
    { offsetof(I3DImageBuffer, wglDestroyImageBuffer), "wglDestroyImageBufferI3D" },
    { offsetof(I3DImageBuffer, wglReleaseImageBufferEvents), "wglReleaseImageBufferEventsI3D" },
};

static const gl::EntryOffset __I3DSwapFrameLockEntryPoints[] = {
    { offsetof(I3DSwapFrameLock, wglDisableFrameLock), "wglDisableFrameLockI3D" },
    { offsetof(I3DSwapFrameLock, wglEnableFrameLock), "wglEnableFrameLockI3D" },
    { offsetof(I3DSwapFrameLock, wglIsEnabledFrameLock), "wglIsEnabledFrameLockI3D" },
    { offsetof(I3DSwapFrameLock, wglQueryFrameLockMaster), "wglQueryFrameLockMasterI3D" },
};

static const gl::EntryOffset __I3DSwapFrameUsageEntryPoints[] = {
    { offsetof(I3DSwapFrameUsage, wglBeginFrameTracking), "wglBeginFrameTrackingI3D" },
    { offsetof(I3DSwapFrameUsage, wglEndFrameTracking), "wglEndFrameTrackingI3D" },
    { offsetof(I3DSwapFrameUsage, wglGetFrameUsage), "wglGetFrameUsageI3D" },
    { offsetof(I3DSwapFrameUsage, wglQueryFrameTracking), "wglQueryFrameTrackingI3D" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// I3DDigitalVideoControl Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DDigitalVideoControl::I3DDigitalVideoControl()
{
    std::for_each_n(__I3DDigitalVideoControlEntryPoints,
                    std::size(__I3DDigitalVideoControlEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DDigitalVideoControl::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_digital_video_control");
}

void I3DDigitalVideoControl::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DDigitalVideoControlEntryPoints,
                    std::size(__I3DDigitalVideoControlEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// I3DGamma Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DGamma::I3DGamma()
{
    std::for_each_n(__I3DGammaEntryPoints,
                    std::size(__I3DGammaEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DGamma::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_gamma");
}

void I3DGamma::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DGammaEntryPoints,
                    std::size(__I3DGammaEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// I3DGenlock Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DGenlock::I3DGenlock()
{
    std::for_each_n(__I3DGenlockEntryPoints,
                    std::size(__I3DGenlockEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DGenlock::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_genlock");
}

void I3DGenlock::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DGenlockEntryPoints,
                    std::size(__I3DGenlockEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// I3DImageBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DImageBuffer::I3DImageBuffer()
{
    std::for_each_n(__I3DImageBufferEntryPoints,
                    std::size(__I3DImageBufferEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DImageBuffer::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_image_buffer");
}

void I3DImageBuffer::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DImageBufferEntryPoints,
                    std::size(__I3DImageBufferEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// I3DSwapFrameLock Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DSwapFrameLock::I3DSwapFrameLock()
{
    std::for_each_n(__I3DSwapFrameLockEntryPoints,
                    std::size(__I3DSwapFrameLockEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DSwapFrameLock::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_swap_frame_lock");
}

void I3DSwapFrameLock::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DSwapFrameLockEntryPoints,
                    std::size(__I3DSwapFrameLockEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// I3DSwapFrameUsage Member Definitions
////////////////////////////////////////////////////////////////////////////////
I3DSwapFrameUsage::I3DSwapFrameUsage()
{
    std::for_each_n(__I3DSwapFrameUsageEntryPoints,
                    std::size(__I3DSwapFrameUsageEntryPoints),
                    gl::ClearEntryPoint(this));
}

bool I3DSwapFrameUsage::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("WGL_I3D_swap_frame_usage");
}

void I3DSwapFrameUsage::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__I3DSwapFrameUsageEntryPoints,
                    std::size(__I3DSwapFrameUsageEntryPoints),
                    gl::ResolveEntryPoint(this, resolver));
}

} // namespace wgl
////////////////////////////////////////////////////////////////////////////////

