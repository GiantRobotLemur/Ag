//! @file Ag/ObjectGL/Shader.hpp
//! @brief The declaration of an object wrapping an OpenGL shader resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_SHADER_HPP__
#define __AG_OBJECT_GL_SHADER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Ag/Core/String.hpp"

#include "EnumTypes.hpp"
#include "Identifiers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class GLAPI;
class ShaderResource;

//! @brief An object wrapping an OpenGL shader resource.
class Shader
{
protected:
    // Construction/Destruction
    Shader(const std::shared_ptr<ShaderResource> &resource);
public:
    Shader() = default;
    ~Shader() = default;

    // Accessors
    bool isBound() const;
    ShaderType getType() const;
    ShaderName getName() const;
    bool isMarkedForDeletion() const;
    bool isCompiled() const;
    Ag::String getSource() const;
    void setSource(const char *source);
    void setSource(const char *source, size_t length);
    void setSource(const Ag::String &source);
    Ag::String getCompilationLog() const;

    // Operations
    void compile();
private:
    // Internal Types

    // Internal Functions
    const GLAPI &verifyAccess(const char *operation) const;

    // Internal Fields
    std::shared_ptr<ShaderResource> _shader;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
