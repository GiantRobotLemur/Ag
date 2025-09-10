//! @file Ag/ObjectGL/Extensions/3DLabs.hpp
//! @brief The declaration of 3D Labs-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_3D_LABS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_3D_LABS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../WGL_Types.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// WGL_3DL_stereo_control extension API specification.
struct _3DLStereoControl {
    // Public Members
    BOOL(APIENTRY *wglSetStereoEmitterState3DL)(HDC hDC, UINT uState);

    // Construction
    _3DLStereoControl();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct _3DLStereoControl

} // namespace wgl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
