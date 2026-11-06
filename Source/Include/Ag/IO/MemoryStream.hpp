//! @file Ag/IO/MemoryStream.hpp
//! @brief The declaration of an implementation of ISeekableStream backed by
//! physical RAM.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_MEMORY_STREAM_HPP_
#define HEADER_IO_MEMORY_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>

#include "ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class IMemoryStreamAllocator;

//! @brief An implementation of ISeekableStream backed by physical RAM.
class MemoryStream : public ISeekableStream
{
public:
    // Construction/Destruction
    MemoryStream();
    MemoryStream(const void *data, size_t byteCount, bool isReadOnly);
    virtual ~MemoryStream();

    // Accessors
    ByteBlock toArray() const;
    StreamLength getSize() const;

    // Overrides

    // Inherited from IStream.
    virtual bool isBuffered() const override;
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

    // Inherited from ISeekableStream.
    virtual StreamPosition getLength() const override;
    virtual StreamPosition getPosition() const override;
    virtual StreamPosition setPosition(StreamRelative relativeTo, StreamPosition offset) override;
private:
    // Internal Types
    using ByteBlockQueue = std::deque<uint8_ptr_t>;

    // Internal Functions
    void setMinimumSize(size_t requiredSize);

    // Internal Fields
    const IMemoryStreamAllocator *_allocator;
    ByteBlockQueue _blocks;
    size_t _totalSize;
    size_t _position;
    bool _isReadOnly;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
