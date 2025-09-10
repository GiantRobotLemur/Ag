//! @file Ag/ObjectGL/Extensions/IngrCommands.hpp
//! @brief The declaration of Ingr-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_INGR_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_INGR_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "Ingr.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_INGR_blend_func_separate extension API.
class IngrBlendFuncSeparateAPI : public BaseExtension
{
public:
    // Construction
    IngrBlendFuncSeparateAPI();

    // Accessors
    const IngrBlendFuncSeparate &getRawAPI() const;

    // Operations
    void blendFuncSeparateIngr(BlendingFactor sfactorRGB,
                               BlendingFactor dfactorRGB,
                               BlendingFactor sfactorAlpha,
                               BlendingFactor dfactorAlpha) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    IngrBlendFuncSeparate _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
