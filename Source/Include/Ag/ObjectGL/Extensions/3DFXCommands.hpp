//! @file Ag/ObjectGL/Extensions/3DFXCommands.hpp
//! @brief The declaration of 3DFX-specific extensions to the OpenGL Command
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

#ifndef __AG_OBJECT_GL_3DFX_COMMAND_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_3DFX_COMMAND_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "3DFX.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_3DFX_tbuffer extension API.
class _3DFXTbufferAPI : public BaseExtension
{
public:
    // Construction
    _3DFXTbufferAPI();

    // Accessors
    const _3DFXTbuffer &getRawAPI() const;

    // Operations
    void tbufferMask(GLuint mask) const;

    // Overrides
    virtual void resolve(const APIResolver* resolver) override;

private:
    _3DFXTbuffer _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
