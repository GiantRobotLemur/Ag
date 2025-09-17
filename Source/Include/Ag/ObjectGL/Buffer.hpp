//! @file Ag/ObjectGL/Buffer.hpp
//! @brief The declaration of a wrapper for an OpenGL buffer resource.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_BUFFER_HPP__
#define __AG_OBJECT_GL_BUFFER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependant Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Identifiers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class BufferResource;

//! @brief A wrapper for an OpenGL buffer resource.
class Buffer
{
    // Construction/Destruction
protected:
    Buffer(const std::shared_ptr<BufferResource> &resource);
public:
    Buffer() = default;

    // Accessors
    bool isBound() const;
    BufferName getName() const;

    // Operations
    void dispose();
private:
    // Internal Fields
    std::shared_ptr<BufferResource> _buffer;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
