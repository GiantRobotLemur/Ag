//! @file ObjectGL/Extensions/PGICommands.cpp
//! @brief The definition of PGI-specific extensions to the OpenGL Command
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
#include "Ag/ObjectGL/Extensions/PGICommands.hpp"
#include "CommandSetTools.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// PGIMiscHintsAPI Member Function Definitions
////////////////////////////////////////////////////////////////////////////////
// Construct an unresolved command set for the GL_PGI_misc_hints extension.
PGIMiscHintsAPI::PGIMiscHintsAPI() :
    BaseExtension("GL_PGI_misc_hints")
{
}

// Grant read-only access to the underlying function pointers.
const PGIMiscHints &PGIMiscHintsAPI::getRawAPI() const
{
    return _api;
}

// Resolve the GL_PGI_misc_hints entry points.
void PGIMiscHintsAPI::resolve(const APIResolver *resolver)
{
    if (resolver != nullptr)
    {
        _api.resolveEntryPoints(resolver);

        // Call the base class.
        BaseExtension::resolve(resolver);
    }
}

// Calls glHintPGI().
void PGIMiscHintsAPI::hint(HintTargetPGI target, GLint mode) const
{
    static const char *fnName = "glHintPGI";

    beforeCommand(fnName, _api.glHint);
    _api.glHint(toScalar(target), mode);
    afterCommand(fnName);
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

