//! @file ObjectGL/IndexBuffer.cpp
//! @brief The definition of an object encapsulating a set of indices into
//! a vertex buffer held in GPU memory.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2025
//! @copyright This file is part of the Mighty Oak project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/MightyOak for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/ObjectGL/IndexBuffer.hpp"
#include "ResourceWrappers.hpp"

namespace gl {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
template<typename TIndexType, typename FwdIter>
TIndexType findMaxIndex(FwdIter begin, FwdIter end)
{
    static constexpr TIndexType Restart = std::numeric_limits<TIndexType>::max();
    TIndexType maximum = std::numeric_limits<TIndexType>::lowest();

    for (FwdIter current = begin; current != end; ++current)
    {
        if ((*current) != Restart)
        {
            maximum = std::max(maximum, (*current));
        }
    }

    return maximum;
}

template<typename TOutput, typename FwdIter>
std::vector<TOutput> compressIndices(FwdIter begin, FwdIter end)
{
    std::vector<TOutput> results;
    results.reserve(std::distance(begin, end));

    for (FwdIter current = begin; current != end; ++current)
    {
        results.push_back(static_cast<TOutput>(*current));
    }

    return results;
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// IndexBuffer Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which accesses an Index Buffer resource.
//! @param[in] resource The resource to manage.
IndexBuffer::IndexBuffer(const std::shared_ptr<IndexBufferResource> &resource) :
    _buffer(resource)
{
}

//! @brief Gets whether the object is bound to a valid index buffer resource.
bool IndexBuffer::isBound() const { return static_cast<bool>(_buffer); }

//! @brief Gets the identifier of the index buffer resource.
BufferName IndexBuffer::getName() const
{
    return _buffer ? _buffer->getName() : BufferName();
}

//! @brief Gets whether the buffer has been encoded with indices which signal
//! a primitive restart.
//! @retval true Primitive restart index values are embedded in the buffer data.
//! @retval false The index data doesn't contain any special values or the
//! object is not bound to a valid resource.
bool IndexBuffer::usesPrimitiveRestart() const
{
    return _buffer ? _buffer->usesPrimitiveRestart() : false;
}

//! @brief Gets the data type used to encode the index data.
//! @note This may differ from the data type passed to the fill()
//! member function as data is compressed where possible.
DrawElementsType IndexBuffer::getDataType() const
{
    return _buffer ? _buffer->getDataType() : DrawElementsType::UnsignedByte;
}

//! @brief Binds the index buffer to the current OpenGL context.
void IndexBuffer::select() const
{
    const auto &api = verifyAccess("select()");

    api.bindBuffer(BufferTarget::ElementArrayBuffer, _buffer->getName());
}

//! @brief Unbinds any index buffer from the current OpenGL context.
void IndexBuffer::deselect() const
{
    const auto &api = verifyAccess("deselect()");

    api.bindBuffer(BufferTarget::ElementArrayBuffer, BufferName());
}

//! @brief Resets the object to an unbound state, disposing of the
//! underlying resource if necessary.
void IndexBuffer::dispose()
{
    _buffer.reset();
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 8-bit unsigned values.
//! @param[in] count The count of values in indices.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd8 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
void IndexBuffer::fill(const uint8_t *indices, size_t count,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    const auto &api = verifyAccess("fill(uint8_t*)");

    api.bindBuffer(BufferTarget::ElementArrayBuffer, _buffer->getName());
    api.bufferData(BufferTarget::ElementArrayBuffer, count, indices, usage);

    // Annotate the buffer resource with the data type and usability.
    _buffer->setDataType(DrawElementsType::UnsignedByte);
    _buffer->setUsePrimitiveRestart(hasRestarts);
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 16-bit unsigned values.
//! @param[in] count The count of values in indices.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd16 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
//! @note The data will be converted to 8-bit if all index values are in the
//! 8-bit range.
void IndexBuffer::fill(const uint16_t *indices, size_t count,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    const auto &api = verifyAccess("fill(uint16_t*)");

    api.bindBuffer(BufferTarget::ElementArrayBuffer, _buffer->getName());
    uint16_t maxIndex = 0;

    if (count > 0)
    {
        maxIndex = hasRestarts ? findMaxIndex<uint16_t>(indices, indices + count) :
                                 *std::max_element(indices, indices + count);
    }

    if (maxIndex < 0xFF)
    {
        // Convert to byte indexes.
        IndicesCollection8 compressed = compressIndices<uint8_t>(indices, indices + count);

        api.bufferData(BufferTarget::ElementArrayBuffer, count,
                       compressed.data(), usage);

        // Annotate the buffer resource with the data type.
        _buffer->setDataType(DrawElementsType::UnsignedByte);
    }
    else
    {
        api.bufferData(BufferTarget::ElementArrayBuffer,
                       count * sizeof(uint16_t), indices, usage);

        // Annotate the buffer resource with the data type.
        _buffer->setDataType(DrawElementsType::UnsignedShort);
    }

    _buffer->setUsePrimitiveRestart(hasRestarts);
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 32-bit unsigned values.
//! @param[in] count The count of values in indices.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd32 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
//! @note The data will be converted to 8-bit or 16-bit indices if all index
//! values are in the appropriate range.
void IndexBuffer::fill(const uint32_t *indices, size_t count,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    const auto &api = verifyAccess("fill(uint32_t*)");

    api.bindBuffer(BufferTarget::ElementArrayBuffer, _buffer->getName());
    uint32_t maxIndex = 0;

    if (count > 0)
    {
        maxIndex = hasRestarts ? findMaxIndex<uint32_t>(indices, indices + count) :
                                 *std::max_element(indices, indices + count);
    }

    if (maxIndex < 0xFF)
    {
        // Convert to byte indexes.
        IndicesCollection8 compressed = compressIndices<uint8_t>(indices, indices + count);

        api.bufferData(BufferTarget::ElementArrayBuffer, count,
                       compressed.data(), usage);

        // Annotate the buffer resource with the data type.
        _buffer->setDataType(DrawElementsType::UnsignedByte);
        _buffer->setRestartIndex(static_cast<uint32_t>(PrimitiveEnd8));
    }
    else if (maxIndex < 0xFFFF)
    {
        // Convert to 16-bit words.
        IndicesCollection16 compressed = compressIndices<uint16_t>(indices, indices + count);

        api.bufferData(BufferTarget::ElementArrayBuffer,
                       count * sizeof(uint16_t),
                       compressed.data(), usage);

        // Annotate the buffer resource with the data type.
        _buffer->setDataType(DrawElementsType::UnsignedShort);
        _buffer->setRestartIndex(static_cast<uint32_t>(PrimitiveEnd16));
    }
    else
    {
        api.bufferData(BufferTarget::ElementArrayBuffer,
                       count * sizeof(uint32_t), indices, usage);

        // Annotate the buffer resource with the data type.
        _buffer->setDataType(DrawElementsType::UnsignedShort);
        _buffer->setRestartIndex(PrimitiveEnd32);
    }

    _buffer->setUsePrimitiveRestart(hasRestarts);
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 16-bit unsigned values.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd16 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
void IndexBuffer::fill(const IndicesCollection8 &indices,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    fill(indices.data(), indices.size(), usage, hasRestarts);
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 16-bit unsigned values.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd16 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
//! @note The data will be converted to 8-bit if all index values are in the
//! 8-bit range.
void IndexBuffer::fill(const IndicesCollection16 &indices,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    fill(indices.data(), indices.size(), usage, hasRestarts);
}

//! @brief Sets the contents of the index buffer.
//! @param[in] indices The source index data expressed as 16-bit unsigned values.
//! @param[in] usage Gives a hint as to the usage and lifetime of the data.
//! @param[in] hasRestarts True if IndexBuffer::PrimitiveEnd16 values have been
//! embedded to signal the end of a primitive, false if the data contains no
//! special values.
//! @note The data will be converted to 8-bit or 16-bit if all index values
//! are in the appropriate range.
void IndexBuffer::fill(const IndicesCollection32 &indices,
                       BufferUsage usage, bool hasRestarts /*= false*/)
{
    fill(indices.data(), indices.size(), usage, hasRestarts);
}

//! @brief Configures the current context with an appropriate primitive
//! restart index.
void IndexBuffer::configurePrimitiveRestart() const
{
    const auto &api = verifyAccess("configurePrimitiveRestart()");

    if (_buffer->usesPrimitiveRestart())
    {
        api.enable(EnableCap::PrimitiveRestart);
        api.primitiveRestartIndex(_buffer->getRestartIndex());
    }
    else
    {
        api.disable(EnableCap::PrimitiveRestart);
    }
}

//! @brief Verifies that the object is associated with a valid resource and
//! returns an API used to operate on it.
//! @param[in] operation The name of the operation being performed.
//! @return A reference to an OpenGL API used to manipulate the resource.
//! @throws ObjectNotBoundException If the object is not bound to a
//! valid resource.
const GLAPI &IndexBuffer::verifyAccess(const char *operation) const
{
    if (_buffer)
    {
        return _buffer->getDisplay()->getAPI();
    }
    else
    {
        throw Ag::ObjectNotBoundException("IndexBuffer", operation);
    }
}

} // namespace gl
////////////////////////////////////////////////////////////////////////////////

