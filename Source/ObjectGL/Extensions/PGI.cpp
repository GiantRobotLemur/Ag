//! @file ObjectGL/Extensions/PGI.cpp
//! @brief The definition of PGI-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/PGI.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __PGIMiscHintsEntryPoints[] = {
    { offsetof(PGIMiscHints, glHint), "glHintPGI" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// PGIMiscHints Member Definitions
////////////////////////////////////////////////////////////////////////////////
PGIMiscHints::PGIMiscHints()
{
    std::for_each_n(__PGIMiscHintsEntryPoints,
                    std::size(__PGIMiscHintsEntryPoints),
                    ClearEntryPoint(this));
}

bool PGIMiscHints::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_PGI_misc_hints");
}

void PGIMiscHints::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__PGIMiscHintsEntryPoints,
                    std::size(__PGIMiscHintsEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

