//! @file ObjectGL/Extensions/Gremedy.cpp
//! @brief The definition of Gremedy-specific extensions to the OpenGL API.
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
#include "Ag/ObjectGL/Extensions/Gremedy.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
static const EntryOffset __GremedyFrameTerminatorEntryPoints[] = {
    { offsetof(GremedyFrameTerminator, glFrameTerminatorGREMEDY), "glFrameTerminatorGREMEDY" },
};

static const EntryOffset __GremedyStringMarkerEntryPoints[] = {
    { offsetof(GremedyStringMarker, glStringMarkerGREMEDY), "glStringMarkerGREMEDY" },
};

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// GremedyFrameTerminator Member Definitions
////////////////////////////////////////////////////////////////////////////////
GremedyFrameTerminator::GremedyFrameTerminator()
{
    std::for_each_n(__GremedyFrameTerminatorEntryPoints,
                    std::size(__GremedyFrameTerminatorEntryPoints),
                    ClearEntryPoint(this));
}

bool GremedyFrameTerminator::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_GREMEDY_frame_terminator");
}

void GremedyFrameTerminator::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__GremedyFrameTerminatorEntryPoints,
                    std::size(__GremedyFrameTerminatorEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

////////////////////////////////////////////////////////////////////////////////
// GremedyStringMarker Member Definitions
////////////////////////////////////////////////////////////////////////////////
GremedyStringMarker::GremedyStringMarker()
{
    std::for_each_n(__GremedyStringMarkerEntryPoints,
                    std::size(__GremedyStringMarkerEntryPoints),
                    ClearEntryPoint(this));
}

bool GremedyStringMarker::isPresent(const APIResolver *resolver) const
{
    return resolver->isExtensionPresent("GL_GREMEDY_string_marker");
}

void GremedyStringMarker::resolveEntryPoints(const APIResolver *resolver)
{
    std::for_each_n(__GremedyStringMarkerEntryPoints,
                    std::size(__GremedyStringMarkerEntryPoints),
                    ResolveEntryPoint(this, resolver));
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

