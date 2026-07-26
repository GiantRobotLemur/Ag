//! @file IO/BufferedInputStream.cpp
//! @brief The definition of an implementation of IStream which buffers bytes
//! read from an underlying stream.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/BufferedInputStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// BufferedInputStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a stream to batch reads to an underlying stream.
//! @param[in] input The underlying stream to read form.
//! @param[in] bufferSize A hint at the size of the buffer to use, in bytes.
BufferedInputStream::BufferedInputStream(IStream *input, size_t bufferSize /*= 0*/) :
    _innerStream(input),
    _bytesRead(0)
{
    // Calculate a reasonable buffer size from the hint.
    const size_t MinBufferSize = 512;
    const size_t MaxBufferSize = 1024 * 1024;

    size_t safeBufferSize = std::clamp(bufferSize, MinBufferSize, MaxBufferSize);

    // Ensure the buffer is allocated once only.
    _buffer.reserve(safeBufferSize);
}

//! @brief Gets the total size of the buffer, in bytes.
size_t BufferedInputStream::getBufferSize() const
{
    return _buffer.capacity();
}

//! @brief Gets the count of bytes left in the buffer to be read.
size_t BufferedInputStream::getBufferUsed() const
{
    return _buffer.size() - _bytesRead;
}

//! @brief Gets the count of bytes in the buffer which have already been read.
size_t BufferedInputStream::getBufferedBytesRead() const
{
    return _bytesRead;
}

//! @brief Steps back over previously read bytes so that they will be returned
//! by the next call to read().
//! @param[in] count The count of bytes to step back over. The maximum count is
//! returned by getBufferedBytesRead().
//! @throws ArgumentException Thrown if the value of @p count is too large.
void BufferedInputStream::ungetBytes(size_t count)
{
    if (count > _bytesRead)
        throw ArgumentException("Not enough buffered bytes to unget.", "count");
    _bytesRead -= count;
}

//! @brief Gets a read-only reference to the underlying stream.
const IStream *BufferedInputStream::getInnerStream() const
{
    return _innerStream;
}

// Inherited from IStream.
bool BufferedInputStream::isBuffered() const
{
    return true;
}

// Inherited from IStream.
void BufferedInputStream::flush()
{
    // Nothing to flush for a reader. Simply pass down to the inner stream.
    _innerStream->flush();
}

// Inherited from IStream.
size_t BufferedInputStream::read(void *targetBuffer, size_t requiredByteCount)
{
    size_t bufferedBytesLeft = _buffer.size() - _bytesRead;
    uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(targetBuffer);
    size_t bytesRead = 0;

    if (bufferedBytesLeft > 0)
    {
        // Satisfy the first bytes from the buffer.
        size_t bytesToCopy = std::min(bufferedBytesLeft, requiredByteCount);

        memcpy(target, _buffer.data() + _bytesRead, bytesToCopy);

        bytesRead += bytesToCopy;
        _bytesRead += bytesToCopy;
    }

    if (bytesRead < requiredByteCount)
    {
        // There are still more bytes left to read, and we have already
        // emptied the buffer.
        size_t bytesRequired = requiredByteCount - bytesRead;

        // Clear the buffer.
        _buffer.clear();
        _bytesRead = 0;

        if (bytesRequired >= _buffer.capacity())
        {
            // Read the rest bypassing the cache.
            size_t read = _innerStream->read(target + bytesRead, bytesRequired);

            // That should be as much as we can read.
            bytesRead += read;
        }
        else
        {
            // Re-fill the buffer.
            _buffer.resize(_buffer.capacity());
            size_t read = _innerStream->read(_buffer.data(), _buffer.size());

            // Truncate the buffer.
            _buffer.resize(read);

            // Transfer what we can.
            size_t bytesToCopy = std::min(_buffer.size(), bytesRequired);

            memcpy(target + bytesRead, _buffer.data(), bytesToCopy);

            // Update the statistics.
            _bytesRead = bytesToCopy;
            bytesRead += bytesToCopy;
        }
    }

    return bytesRead;
}

// Inherited from IStream.
size_t BufferedInputStream::write(const void */*sourceBuffer*/,
                                  size_t /*sourceByteCount*/)
{
    throw NotSupportedException("Writing to a buffered read stream is not supported.");
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

