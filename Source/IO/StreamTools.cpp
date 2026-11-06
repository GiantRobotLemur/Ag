//! @file IO/StreamTools.cpp
//! @brief The definition of various utilities related to IStream and
//! ISeekableStream implementations.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/Exceptions.hpp"
#include "Ag/IO/StreamTools.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Copies as much data as possible from one stream to another.
//! @param[in] input The stream to read data from.
//! @param[in] output The output buffer to write copied bytes to.
//! @param[in] bufferSize The optional buffer size, in bytes. The value will be
//! clamped to between MinBufferSize and MaxBufferSize.
//! @returns The count of bytes actually copied.
//! @throws IOException Thrown if, having read bytes from @p input, they could
//! not be written to @p output.
StreamLength copyStream(IStream *input, IStream *output,
                        size_t bufferSize /*= 0*/)
{
    size_t safeBufferSize = std::clamp(bufferSize, MinBufferSize, MaxBufferSize);

    ByteBlock buffer;
    buffer.resize(safeBufferSize);

    StreamLength bytesCopied = 0;
    size_t bufferUsed = 0;

    do
    {
        bufferUsed = input->read(buffer.data(), buffer.size());

        if (bufferUsed > 0)
        {
            size_t bufferCopied = output->write(buffer.data(), bufferUsed);

            if (bufferCopied != bufferUsed)
                throw IOException("Failed to write all copied bytes to output stream");

            bytesCopied += static_cast<StreamLength>(bufferCopied);
        }

        // Continue until we fail to read anything.
    } while (bufferUsed > 0);

    return bytesCopied;
}

//! @brief Copies up to a fixed number of bytes between streams.
//! @param[in] input The stream to read data from.
//! @param[in] maxSize The maximum number of bytes to copy.
//! @param[in] output The output buffer to write copied bytes to.
//! @param[in] bufferSize The optional buffer size, in bytes. The value will be
//! clamped to between MinBufferSize and MaxBufferSize.
//! @returns The count of bytes actually copied.
//! @throws IOException Thrown if, having read bytes from @p input, they could
//! not be written to @p output.
StreamLength copyStream(IStream *input, StreamLength maxSize,
                        IStream *output, size_t bufferSize /*= 0*/)
{
    size_t safeBufferSize = std::clamp(bufferSize, MinBufferSize, MaxBufferSize);

    ByteBlock buffer;
    buffer.resize(safeBufferSize);

    StreamLength bytesCopied = 0;
    size_t bufferUsed = 0;

    while (bytesCopied < maxSize)
    {
        StreamLength maxRead = std::min(maxSize - bytesCopied,
                                        static_cast<StreamLength>(safeBufferSize));
        size_t maxBytes = static_cast<size_t>(maxRead);

        bufferUsed = input->read(buffer.data(), maxBytes);

        if (bufferUsed > 0)
        {
            size_t bufferCopied = output->write(buffer.data(), bufferUsed);

            if (bufferCopied != bufferUsed)
                throw IOException("Failed to write all copied bytes to output stream");

            bytesCopied += static_cast<StreamLength>(bufferCopied);
        }

        // If we couldn't read the expected number of bytes from the input
        // stream, stop copying.
        if (bufferUsed < maxBytes)
            break;
    }

    return bytesCopied;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

