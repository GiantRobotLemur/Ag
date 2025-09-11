//! @file Ag/ObjectGL/ProgramBuilder.hpp
//! @brief The declaration of a tool to help construct and compile OpenGL
//! shader programs.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_PROGRAM_BUILDER_HPP__
#define __AG_OBJECT_GL_PROGRAM_BUILDER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include "CommandSets.hpp"
#include "RenderContext.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class ShaderCompilationException : public Ag::Exception
{
public:
    static const char *Domain;

    ShaderCompilationException(gl::ShaderType type, const std::string_view &errors);
};

class ProgramLinkException : public Ag::Exception
{
public:
    static const char *Domain;

    ProgramLinkException(const std::string_view &errors);
};

//! @brief A tool to help construct and compile OpenGL shader programs.
class ProgramBuilder
{
public:
    // Construction/Destruction
    ProgramBuilder() = delete;
    ProgramBuilder(ProgramBuilder &&) = delete;
    ProgramBuilder(const ProgramBuilder &) = delete;
    ProgramBuilder &operator=(const ProgramBuilder &) = delete;
    ProgramBuilder &operator=(ProgramBuilder &&) = delete;

    ProgramBuilder(const RenderContext &context);

    // Operations
    size_t addShader(gl::ShaderType type,
                     const std::string_view &sourceCode);

    Program create();
    bool tryCreate(Program &program, Ag::string_ref_t &errors);
private:
    // Internal Types
    using ShaderResourceCollection = std::vector<Shader>;

    // Internal Fields
    RenderContext _parentContext;
    ShaderResourceCollection _shaders;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
