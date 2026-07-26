//! @file IO/BufferedOutputStream.cpp
//! @brief The definition of an IStream implementation which buffers output
//! before writing it to an inner IStream implementation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Exception.hpp"

#include "Ag/IO/BufferedOutputStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// BufferedOutputStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a wrapper for a stream which batches write operations.
//! @param[in] innerStream The stream to wrap.
//! @param[in] bufferSize The suggested size of the buffer used to batch writes.
BufferedOutputStream::BufferedOutputStream(IStream *innerStream,
                                           size_t bufferSize /*= 0*/) :
    _innerStream(innerStream)
{
    if (_innerStream == nullptr)
        throw ArgumentNullException("innerStream");

    const size_t MinBufferSize = 512;
    const size_t MaxBufferSize = 1024 * 1024;

    size_t bufferSizeHint = std::clamp(bufferSize, MinBufferSize, MaxBufferSize);

    _buffer.reserve(bufferSizeHint);
}

//! @brief Ensures any buffered data is flushed before destruction.
BufferedOutputStream::~BufferedOutputStream()
{
    flush();

    _innerStream = nullptr;
}

//! @brief Gets the maximum capacity of the buffer, in bytes.
size_t BufferedOutputStream::getBufferSize() const
{
    return _buffer.capacity();
}

//! @brief Gets the count of bytes currently buffered.
size_t BufferedOutputStream::getBufferUsed() const
{
    return _buffer.size();
}

//! @brief Gets a read-only pointer to the underlying stream.
const IStream *BufferedOutputStream::getInnerStream() const
{
    return _innerStream;
}

// Inherited from IStream.
bool BufferedOutputStream::isBuffered() const
{
    return true;
}

// Inherited from IStream.
void BufferedOutputStream::flush()
{
    if (_innerStream == nullptr)
        throw OperationException("Cannot flush to a closed stream.");

    if (_buffer.empty() == false)
    {
        size_t bytesToWrite = _buffer.size();
        size_t written = _innerStream->write(_buffer.data(), bytesToWrite);
        _buffer.clear();

        if (written != bytesToWrite)
            throw OperationException("Failed to write all buffered bytes to the inner stream.");
    }
}

// Inherited from IStream.
size_t BufferedOutputStream::read(void */*targetBuffer*/, size_t /*requiredByteCount*/)
{
    throw NotSupportedException("The stream does not support reading.");
}

// Inherited from IStream.
size_t BufferedOutputStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    if (_innerStream == nullptr)
        throw OperationException("Cannot flush to a closed stream.");

    if (sourceByteCount == 0)
        return 0;

    uint8_cptr_t source = reinterpret_cast<uint8_cptr_t>(sourceBuffer);
    size_t bytesWritten = 0;
    size_t bytesToWrite = 0;
    size_t bufferFree = _buffer.capacity() - _buffer.size();

    // Determine the smallest number of maximum-sized writes we can perform.
    if (sourceByteCount >= bufferFree)
    {
        // We'll need to flush what we have, then deal with the rest.
        if (_buffer.empty())
        {
            // We have nothing to flush.
            bytesWritten = _innerStream->write(source, sourceByteCount);
        }
        else
        {
            // There will need to be at least one write from the
            // buffer - maximize that.
            size_t extraBufferNeeded = std::min(bufferFree, sourceByteCount);
            size_t bufferOffset = _buffer.size();
            _buffer.resize(bufferOffset + extraBufferNeeded);

            // Copy bytes to the end of the buffer.
            memcpy(_buffer.data() + bufferOffset, source, extraBufferNeeded);

            // Now flush the buffer.
            bytesToWrite = _buffer.size();
            size_t innerBytesWritten = _innerStream->write(_buffer.data(), bytesToWrite);

            // Clear the buffer before any error handling.
            _buffer.clear();

            if (innerBytesWritten != bytesToWrite)
                throw OperationException("Failed to write all buffered bytes to the inner stream.");

            // Account for the bytes written to the buffer, then flushed.
            bytesWritten += extraBufferNeeded;
        }
    }

    bytesToWrite = sourceByteCount - bytesWritten;

    if (bytesToWrite >= _buffer.capacity())
    {
        // There is not point buffering what is left, just write through.
        size_t innerBytesWritten = _innerStream->write(source + bytesWritten, bytesToWrite);

        if (innerBytesWritten != bytesToWrite)
            throw OperationException("Failed to write all buffered bytes to the inner stream.");

        // Account for the bytes directly written.
        bytesWritten += innerBytesWritten;
    }
    else if (bytesToWrite > 0)
    {
        // If we get here with bytes left to write, we know the buffer is empty.

        // Buffer the rest of the data.
        size_t originalSize = _buffer.size();
        _buffer.resize(originalSize + bytesToWrite);

        memcpy(_buffer.data() + originalSize,
               source + bytesWritten, bytesToWrite);

        // Account for the bytes copied to the buffer.
        bytesWritten += bytesToWrite;
    }

    return bytesWritten;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

