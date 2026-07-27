//! @file Ag/IO/BufferedInputStream.hpp
//! @brief The declaration of an implementation of IStream which buffers bytes
//! read from an underlying stream.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_BUFFERED_INPUT_STREAM_HPP_
#define HEADER_IO_BUFFERED_INPUT_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Stream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of IStream which buffers bytes read from an
//! underlying stream.
class BufferedInputStream : public IStream
{
public:
    // Public Constants
    static constexpr size_t MinBufferSize = 512;
    static constexpr size_t MaxBufferSize = 1024 * 1024;

    // Construction/Destruction
    BufferedInputStream(IStream *input, size_t bufferSize = 0);
    virtual ~BufferedInputStream() override = default;

    // Accessors
    size_t getBufferSize() const;
    size_t getBufferUsed() const;
    size_t getBufferedBytesRead() const;
    const IStream *getInnerStream() const;

    // Operations
    void ungetBytes(size_t count);

    // Overrides
    virtual bool isBuffered() const override;
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount)  override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount)  override;
private:
    // Internal Fields
    ByteBlock _buffer;
    IStream *_innerStream;
    size_t _bytesRead;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
