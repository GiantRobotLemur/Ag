//! @file Ag/ObjectGL/Extensions/3DLabsCommands.hpp
//! @brief The declaration of 3D Labs-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_3D_LABS_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_3D_LABS_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "3DLabs.hpp"

namespace wgl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the WGL_3DL_stereo_control extension API.
class _3DLStereoControlAPI : public gl::BaseExtension
{
public:
    // Construction
    _3DLStereoControlAPI();

    // Accessors
    const _3DLStereoControl &getRawAPI() const;

    // Operations
    BOOL setStereoEmitterState3DL(HDC hDC, UINT uState) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    _3DLStereoControl _api;
};

} // namespace wgl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
