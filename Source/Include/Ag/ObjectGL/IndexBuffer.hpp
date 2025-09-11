//! @file Ag/ObjectGL/IndexBuffer.hpp
//! @brief The declaration of an object encapsulating a set of indices into
//! a vertex buffer held in GPU memory.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Mighty Oak project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/MightyOak for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_OBJECT_GL_INDEX_BUFFER_HPP__
#define __AG_OBJECT_GL_INDEX_BUFFER_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <vector>

#include "Ag/ObjectGL/EnumTypes.hpp"
#include "Ag/ObjectGL/Identifiers.hpp"
#include "Ag/ObjectGL/CommandSets.hpp"

namespace gl {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class IndexBufferResource;

using IndicesCollection8 = std::vector<uint8_t>;
using IndicesCollection16 = std::vector<uint16_t>;
using IndicesCollection32 = std::vector<uint32_t>;

//! @brief An object encapsulating a set of indices into a vertex buffer held
//! in GPU memory.
class IndexBuffer
{
    // Construction/Destruction
protected:
    IndexBuffer(const std::shared_ptr<IndexBufferResource> &resource);
public:
    IndexBuffer() = default;
    ~IndexBuffer() = default;

    // Public Constants
    static constexpr uint8_t PrimitiveEnd8 = 0xFF;
    static constexpr uint16_t PrimitiveEnd16 = 0xFFFF;
    static constexpr uint32_t PrimitiveEnd32 = 0xFFFFFFFFu;

    // Accessors
    bool isBound() const;
    gl::BufferName getName() const;
    bool usesPrimitiveRestart() const;
    gl::DrawElementsType getDataType() const;

    // Operations
    void select() const;
    void deselect() const;
    void fill(const uint8_t *indices, size_t count, BufferUsage usage, bool hasRestarts = false);
    void fill(const uint16_t *indices, size_t count, BufferUsage usage, bool hasRestarts = false);
    void fill(const uint32_t *indices, size_t count, BufferUsage usage, bool hasRestarts = false);
    void fill(const IndicesCollection8 &indices, BufferUsage usage, bool hasRestarts = false);
    void fill(const IndicesCollection16 &indices, BufferUsage usage, bool hasRestarts = false);
    void fill(const IndicesCollection32 &indices, BufferUsage usage, bool hasRestarts = false);
private:
    // Internal Functions
    const gl::GLAPI &verifyAccess(const char *operation) const;

    // Internal Fields
    std::shared_ptr<IndexBufferResource> _buffer;
};

} // namespace gl

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
