//! @file Ag/ObjectGL/Extensions/OvrCommands.hpp
//! @brief The declaration of Ovr-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_OVR_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_OVR_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "../Identifiers.hpp"
#include "Ovr.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_OVR_multiview extension API.
class OvrMultiviewAPI : public BaseExtension
{
public:
    // Construction
    OvrMultiviewAPI();

    // Accessors
    const OvrMultiview &getRawAPI() const;

    // Operations
    void framebufferTextureMultiviewOvr(FrameBufferTarget target,
                                        FramebufferAttachment attachment,
                                        TextureName texture, GLint level,
                                        GLint baseViewIndex, GLsizei numViews) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    OvrMultiview _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
