//! @file Ag/ObjectGL/Extensions/GremedyCommands.hpp
//! @brief The declaration of Gremedy-specific extensions to the OpenGL Command set
//! wrappers.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_AG_OBJECT_GL_GREMEDY_COMMANDS_EXTENSIONS_HPP_
#define HEADER_AG_OBJECT_GL_GREMEDY_COMMANDS_EXTENSIONS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"
#include "Gremedy.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Manages the entry points for the GL_GREMEDY_frame_terminator extension API.
class GremedyFrameTerminatorAPI : public BaseExtension
{
public:
    // Construction
    GremedyFrameTerminatorAPI();

    // Accessors
    const GremedyFrameTerminator &getRawAPI() const;

    // Operations
    void frameTerminatorGremedy() const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    GremedyFrameTerminator _api;
};

//! @brief Manages the entry points for the GL_GREMEDY_string_marker extension API.
class GremedyStringMarkerAPI : public BaseExtension
{
public:
    // Construction
    GremedyStringMarkerAPI();

    // Accessors
    const GremedyStringMarker &getRawAPI() const;

    // Operations
    void stringMarkerGremedy(GLsizei len, const void *string) const;

    // Overrides
    virtual void resolve(const APIResolver *resolver) override;

private:
    GremedyStringMarker _api;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
