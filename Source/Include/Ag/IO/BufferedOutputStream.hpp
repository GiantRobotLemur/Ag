//! @file Ag/IO/BufferedOutputStream.hpp
//! @brief The declaration of an IStream implementation which buffers output
//! before writing it to an inner IStream implementation.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_BUFFERED_OUTPUT_STREAM_HPP_
#define HEADER_IO_BUFFERED_OUTPUT_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/Stream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An IStream implementation which buffers output before writing it to
//! an inner IStream implementation.
//! @remarks
//! The BufferedOutputStream does not manage the lifetime of the inner stream
//! in any way, nor does is expect the write pointer of the inner stream to
//! change outside of its interaction. Thus, if a BufferedOutputStream is used
//! with an ISeekableStream, or a readable IStream, the outer stream must be
//! flushed before the inner stream is re-positioned.
//! 
//! The BufferedOutputStream will throw NotSupportedException on any call to
//! read(), whether the underlying stream is capable of reading or not.
class BufferedOutputStream : public IStream
{
public:
    // Public Constants
    static constexpr size_t MinBufferSize = 512;
    static constexpr size_t MaxBufferSize = 1024 * 1024;

    // Construction/Destruction
    BufferedOutputStream(IStream *innerStream, size_t bufferSize = 0);
    virtual ~BufferedOutputStream();

    // Accessors
    size_t getBufferSize() const;
    size_t getBufferUsed() const;
    const IStream *getInnerStream() const;

    // Overrides
    virtual bool isBuffered() const override;
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;
private:
    // Internal Fields
    ByteBlock _buffer;
    IStream *_innerStream;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
