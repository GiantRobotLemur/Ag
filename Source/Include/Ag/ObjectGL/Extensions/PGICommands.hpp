//! @file Ag/ObjectGL/Extensions/PGICommands.hpp
//! @brief The declaration of PGI-specific extensions to the OpenGL Command set
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

#ifndef __AG_OBJECT_GL_PGI_COMMANDS_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_PGI_COMMANDS_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "../EnumTypes.hpp"
#include "PGI.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// Manages the entry points for the GL_PGI_misc_hints extension API.
class PGIMiscHintsAPI : public BaseExtension
{
public:
    // Construction
    PGIMiscHintsAPI();

    // Accessors
    const PGIMiscHints &getRawAPI() const;

    // Operations
    void hint(HintTargetPGI target, GLint mode) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    PGIMiscHints _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
