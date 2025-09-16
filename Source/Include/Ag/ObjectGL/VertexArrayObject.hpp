//! @file Ag/ObjectGL/VertexArrayObject.hpp
//! @brief The declaration of an object configuring a Vertex input pipeline
//! for OpenGL rendering.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Mighty Oak project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/MightyOak for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_VERTEX_ARRAY_OBJECT_HPP__
#define __AG_OBJECT_GL_VERTEX_ARRAY_OBJECT_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <memory>

#include "Identifiers.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class VAOResource;
class GLAPI;

//! @brief An object configuring a Vertex input pipeline for OpenGL rendering.
class VertexArrayObject
{
protected:
    // Construction/Destruction
    VertexArrayObject(const std::shared_ptr<VAOResource> &vao);
public:
    VertexArrayObject() = default;
    ~VertexArrayObject() = default;

    // Accessors
    bool isBound() const;
    VertexArrayName getName() const;

    // Operations
    void select() const;
    void deselect() const;
    void dispose();
private:
    // Internal Functions
    const GLAPI &verifyAccess(const char *operation) const;

    // Internal Fields
    std::shared_ptr<VAOResource> _vao;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
