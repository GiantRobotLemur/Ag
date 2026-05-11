//! @file Text/Test_MemoryStream.cpp
//! @brief In-memory IStream implementations used only by the Text_Tests
//! executable; not part of any production library.
//! @author GiantRobotLemur@na-se.co.uk and Claude Opus 4.7.
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <cstring>
#include <iterator>

#include "Test_MemoryStream.hpp"

namespace Ag {
namespace Test {

////////////////////////////////////////////////////////////////////////////////
// MemoryReadStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
MemoryReadStream::MemoryReadStream(const void *data, size_t size,
                                   size_t maxBytesPerRead /*= SIZE_MAX*/) :
    _data(reinterpret_cast<const uint8_t *>(data)),
    _size(size),
    _offset(0),
    _maxBytesPerRead(maxBytesPerRead)
{
}

size_t MemoryReadStream::getRemaining() const
{
    return _size - _offset;
}

void MemoryReadStream::flush()
{
}

size_t MemoryReadStream::read(void *targetBuffer, size_t requiredByteCount)
{
    size_t available = _size - _offset;
    size_t toCopy = std::min({ requiredByteCount, _maxBytesPerRead, available });

    if (toCopy > 0)
    {
        std::memcpy(targetBuffer, _data + _offset, toCopy);
        _offset += toCopy;
    }

    return toCopy;
}

size_t MemoryReadStream::write(const void * /*sourceBuffer*/,
                               size_t /*sourceByteCount*/)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
// MemoryWriteStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
void MemoryWriteStream::flush()
{
    FlushCalled = true;
}

size_t MemoryWriteStream::read(void * /*targetBuffer*/,
                               size_t /*requiredByteCount*/)
{
    return 0;
}

size_t MemoryWriteStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    if ((sourceBuffer == nullptr) || (sourceByteCount == 0))
        return 0;

    const uint8_t *src = reinterpret_cast<const uint8_t *>(sourceBuffer);
    Bytes.insert(Bytes.end(), src, src + sourceByteCount);
    return sourceByteCount;
}

}} // namespace Ag::Test
////////////////////////////////////////////////////////////////////////////////
