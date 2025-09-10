//! @file ObjectGL/Extensions/3DLabsCommands.cpp
//! @brief The definition of 3D Labs-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/3DLabsCommands.hpp"
#include "CommandSetTools.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// _3DLStereoControlAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the WGL_3DL_stereo_control extension.
_3DLStereoControlAPI::_3DLStereoControlAPI() :
    BaseExtension("WGL_3DL_stereo_control")
{
}

// Grant read-only access to the underlying function pointers.
const _3DLStereoControl &_3DLStereoControlAPI::getRawAPI() const
{
    return _api;
}

// Resolve the WGL_3DL_stereo_control entry points.
void _3DLStereoControlAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls wglSetStereoEmitterState3DL().
BOOL _3DLStereoControlAPI::setStereoEmitterState3DL(HDC hDC, UINT uState) const
{
    static const char *fnName = "wglSetStereoEmitterState3DL";

    beforeCommand(fnName, _api.wglSetStereoEmitterState3DL);
    BOOL result = _api.wglSetStereoEmitterState3DL(hDC, uState);
    afterCommand(fnName);

    return result;
}

} // namespace wgl
////////////////////////////////////////////////////////////////////////////////

