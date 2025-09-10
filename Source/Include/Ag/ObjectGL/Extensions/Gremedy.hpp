//! @file Ag/ObjectGL/Extensions/Gremedy.hpp
//! @brief The declaration of Gremedy-specific extensions to the OpenGL API.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
//!
//! @note This contents of this file was generated from the Khronos XML API
//! definition using a bespoke code generation tool.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_GREMEDY_EXTENSIONS_HPP__
#define __AG_OBJECT_GL_GREMEDY_EXTENSIONS_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "../BaseTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
// GL_GREMEDY_frame_terminator extension API specification.
struct GremedyFrameTerminator {
    // Public Members
    void (APIENTRY *glFrameTerminatorGREMEDY)();

    // Construction
    GremedyFrameTerminator();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct GremedyFrameTerminator

// GL_GREMEDY_string_marker extension API specification.
struct GremedyStringMarker {
    // Public Members
    void (APIENTRY *glStringMarkerGREMEDY)(GLsizei len, const void *string);

    // Construction
    GremedyStringMarker();

    // Operations
    bool isPresent(const APIResolver *resolver) const;
    void resolveEntryPoints(const APIResolver *resolver);
}; // struct GremedyStringMarker

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
