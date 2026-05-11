//! @file Text/Test_MemoryStream.hpp
//! @brief In-memory IStream implementations used only by the Text_Tests
//! executable; not part of any production library.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef _AG_TEXT_TEST_MEMORY_STREAM_HPP__
#define _AG_TEXT_TEST_MEMORY_STREAM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstddef>
#include <cstdint>
#include <vector>

#include "Ag/Core/Stream.hpp"

namespace Ag {
namespace Test {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An IStream which serves bytes from a fixed in-memory buffer.
//! @details The optional @p maxBytesPerRead parameter clamps how many bytes a
//! single read() call returns, which lets a unit test exercise the
//! buffer-refill and rollback paths in StreamCharacterSource without needing
//! a real file or pipe.
class MemoryReadStream : public Ag::IStream
{
public:
    // Construction/Destruction
    MemoryReadStream(const void *data, size_t size,
                     size_t maxBytesPerRead = SIZE_MAX);
    virtual ~MemoryReadStream() = default;

    // Accessors
    size_t getRemaining() const;

    // Overrides
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

private:
    // Internal Fields
    const uint8_t *_data;
    size_t _size;
    size_t _offset;
    size_t _maxBytesPerRead;
};

//! @brief An IStream which appends every written byte into the public Bytes
//! vector and tracks whether flush() has been invoked.
class MemoryWriteStream : public Ag::IStream
{
public:
    // Construction/Destruction
    MemoryWriteStream() = default;
    virtual ~MemoryWriteStream() = default;

    // Public Fields
    std::vector<uint8_t> Bytes;
    bool FlushCalled = false;

    // Overrides
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;
};

}} // namespace Ag::Test

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
