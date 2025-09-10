//! @file Ag/ObjectGL/BufferSchema.hpp
//! @brief The declaration of an object which describes the format of an
//! OpenGL buffer resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_BUFFER_SCHEMA_HPP__
#define __AG_OBJECT_GL_BUFFER_SCHEMA_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <vector>

#include "Ag/Core/String.hpp"
#include "EnumTypes.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which describes a field within an OpenGL buffer.
class BufferElement
{
public:
    // Construction/Destruction

    // Accessors

    // Operations

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
};


//! @brief An object which describes the format of an OpenGL buffer resource.
class BufferSchema
{
public:
    // Construction/Destruction

    // Accessors

    // Operations

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
    std::vector<BufferElement> _elements;
};


//! @brief An object which constructs a description of the format of an
//! OpenGL buffer.
class BufferSchemaBuilder
{
public:
    // Construction/Destruction

    // Accessors

    // Operations

private:
    // Internal Types

    // Internal Functions

    // Internal Fields
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
