//! @file IO/MemoryStream.cpp
//! @brief The definition of an implementation of ISeekableStream backed by
//! physical RAM.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core.hpp>

#include "Ag/IO/MemoryStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
using BlockQueue = std::deque<uint8_ptr_t>;
using BlockQueueCIter = BlockQueue::const_iterator;

//! @brief An allocator used for managing the memory of a MemoryStream.
class IMemoryStreamAllocator
{
protected:
    // Construction/Destruction
    IMemoryStreamAllocator() = default;
public:
    virtual ~IMemoryStreamAllocator() = default;

    // Accessors
    virtual size_t getBlockSize() const =0;

    // Operations
    virtual void appendAllocatedBlocks(size_t count, BlockQueue &blocks) const = 0;
    virtual void freeBlocks(BlockQueueCIter begin, BlockQueueCIter end) const = 0;
};

namespace {

//! @brief An implementation of IMemoryStreamAllocator which uses malloc() and free().
class MallocStreamAllocator : public IMemoryStreamAllocator
{
private:
    // Internal Fields
    size_t _blockSize;

public:
    // Construction/Destruction
    MallocStreamAllocator(size_t blockSize) : _blockSize(blockSize) {}
    virtual ~MallocStreamAllocator() = default;

    // Overrides

    // Inherited from IMemoryStreamAllocator.
    virtual size_t getBlockSize() const override { return _blockSize; }

    // Inherited from IMemoryStreamAllocator.
    virtual void appendAllocatedBlocks(size_t count, BlockQueue &blocks) const override
    {
        for (size_t i = 0; i < count; ++i)
        {
            void *block = malloc(_blockSize);

            if (block == nullptr)
            {
                // Free the blocks we managed to allocate up to now.
                for (size_t j = 0; j < i; ++i)
                {
                    free(blocks.back());
                    blocks.pop_back();
                }

                throw Ag::OutOfMemoryException(_blockSize);
            }

            blocks.push_back(reinterpret_cast<uint8_ptr_t>(block));
        }
    }

    // Inherited from IMemoryStreamAllocator.
    virtual void freeBlocks(BlockQueueCIter begin, BlockQueueCIter end) const
    {
        for (auto pos = begin; pos != end; ++pos)
        {
            if (*pos != nullptr)
                free(*pos);
        }
    }
};

// TODO: Write an allocator based on VirtualAlloc (Win32) or mmap (POSIX) for
// management of larger blocks.

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
const MallocStreamAllocator smallAllocator(512);

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////

// TODO: The following code was producing a warning under gcc because it wasn't
// ever being called. Reinstate it when we have implemented an allocator based
// on memory page allocation.
//
// //! @brief Converts blocks allocated with one allocator to a new set of blocks
// //! allocated with another.
// //! @param[in] destinationAllocator The allocator implementation to convert the
// //! existing data to.
// //! @param[in] rhs The set of blocks to convert.
// //! @param[in] rhsBlockSize The size of each block in @p rhs.
// //! @return A new set of blocks allocated by @p destinationAllocator with
// //! the data fro @p rhs copied into them.
// BlockQueue convertAllocators(const IMemoryStreamAllocator *destinationAllocator,
//                              const BlockQueue &rhs, size_t rhsBlockSize)
// {
//     // Allocate enough memory to copy the existing data to.
//     size_t totalSize = rhs.size() * rhsBlockSize;

//     const size_t nativeBlockSize = destinationAllocator->getBlockSize();
//     size_t nativeBlockCount = (totalSize + nativeBlockSize - 1) / nativeBlockSize;

//     BlockQueue newQueue;
//     destinationAllocator->appendAllocatedBlocks(nativeBlockCount, newQueue);

//     // Copy the existing data to the new blocks.
//     auto lhsPos = newQueue.begin();
//     size_t lhsBlockOffset = 0;

//     for (uint8_ptr_t rhsBlockPtr : rhs)
//     {
//         size_t rhsCopied = 0;

//         while (rhsCopied < rhsBlockSize)
//         {
//             size_t rhsLeft = rhsBlockSize - rhsCopied;
//             size_t lhsLeft = nativeBlockSize - lhsBlockOffset;

//             if (lhsLeft == 0)
//             {
//                 // Move on to the next target block if there is no
//                 // space left in the current one.
//                 ++lhsPos;
//                 lhsBlockOffset = 0;
//             }

//             size_t bytesToCopy = std::min(lhsLeft, rhsLeft);
//             uint8_ptr_t lhsBlock = *lhsPos;

//             // Copy the data.
//             std::memcpy(lhsBlock + lhsBlockOffset,
//                         rhsBlockPtr + rhsCopied,
//                         bytesToCopy);

//             rhsCopied += bytesToCopy;
//             lhsBlockOffset += bytesToCopy;
//         }
//     }

//     // Blank the bytes in the remaining blocks.
//     while (lhsPos != newQueue.end())
//     {
//         uint8_ptr_t lhsBlock = *lhsPos;
//         std::memset(lhsBlock + lhsBlockOffset, 0,
//                     nativeBlockSize - lhsBlockOffset);

//         lhsBlockOffset = 0;
//         ++lhsPos;
//     }

//     return newQueue;
// }

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// MemoryStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new memory stream.
MemoryStream::MemoryStream() :
    _allocator(&smallAllocator),
    _totalSize(0),
    _position(0),
    _isReadOnly(false)
{
}

//! @brief Constructs a new stream to operate on a copy of data.
//! @param[in] data The data to copy.
//! @param[in] byteCount The count of bytes in @p data.
//! @param[in] isReadOnly True if the stream prevents writing, false to allow both
//! reading and writing.
MemoryStream::MemoryStream(const void *data, size_t byteCount, bool isReadOnly) :
    _allocator(&smallAllocator),
    _totalSize(byteCount),
    _position(0),
    _isReadOnly(false)
{
    // Copy the data into the stream, thus creating enough storage for it.
    write(data, byteCount);

    // Reset the stream state once filled.
    _isReadOnly = isReadOnly;
    _position = 0;
}

//! @brief Ensures all storage memory is de-allocated.
MemoryStream::~MemoryStream()
{
    if (_blocks.empty() == false)
    {
        _allocator->freeBlocks(_blocks.begin(), _blocks.end());
        _blocks.clear();
    }
}

//! @brief Extracts all bytes of the stream as a single linear array of bytes.
//! @return A copy of the contents of the stream.
ByteBlock MemoryStream::toArray() const
{
    ByteBlock linearBlock;
    linearBlock.resize(_totalSize);

    const size_t blockSize = _allocator->getBlockSize();
    size_t linearOffset = 0;

    for (uint8_ptr_t block : _blocks)
    {
        size_t bytesToCopy = std::min(_totalSize - linearOffset, blockSize);

        if (bytesToCopy == 0)
            break;

        memcpy(linearBlock.data() + linearOffset, block, bytesToCopy);
        linearOffset += bytesToCopy;
    }

    return linearBlock;
}

//! @brief Gets the total size of the data written to the stream, in bytes.
StreamLength MemoryStream::getSize() const
{
    return _totalSize;
}

// Inherited from IStream.
bool MemoryStream::isBuffered() const
{
    // A memory stream is an implicit buffer.
    return true;
}

// Inherited from IStream.
void MemoryStream::flush()
{
    // Does nothing in this implementation.
}

// Inherited from IStream.
size_t MemoryStream::read(void *targetBuffer, size_t requiredByteCount)
{
    size_t maxBytesToCopy = std::min(_totalSize - _position, requiredByteCount);

    if (maxBytesToCopy > 0)
    {
        const size_t blockSize = _allocator->getBlockSize();
        uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(targetBuffer);
        size_t blockIndex = _position / blockSize;
        size_t blockOffset = _position - (blockIndex * blockSize);
        size_t bytesCopied = 0;
        auto blockPos = _blocks.begin() + blockIndex;

        while (bytesCopied < maxBytesToCopy)
        {
            size_t bytesToCopy = std::min(blockSize - blockOffset,
                                          maxBytesToCopy - bytesCopied);
            uint8_ptr_t blockPtr = *blockPos;

            // Copy the bytes.
            memcpy(target + bytesCopied, blockPtr + blockOffset, bytesToCopy);

            // Update statistics.
            bytesCopied += bytesToCopy;

            // Move on to the next block.
            blockOffset = 0;
            ++blockPos;
        }

        _position += bytesCopied;
    }

    return maxBytesToCopy;
}

// Inherited from IStream.
size_t MemoryStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    if (_isReadOnly)
        throw OperationException("Cannot write to a read-only stream.");

    if (sourceByteCount == 0)
        return 0;

    size_t blockSize = _allocator->getBlockSize();
    size_t requiredSize = std::max(_position + sourceByteCount, _totalSize);

    // Ensure we have enough space allocated for the bytes to write.
    setMinimumSize(requiredSize);

    // Write the data knowing we have enough space.
    uint8_cptr_t sourceData = reinterpret_cast<uint8_cptr_t>(sourceBuffer);
    size_t bytesWritten = 0;

    // Calculate the index/offset into the first block.
    size_t blockIndex = _position / blockSize;
    size_t blockOffset = _position - (blockIndex * blockSize);

    while (bytesWritten < sourceByteCount)
    {
        size_t blockLeft = blockSize - blockOffset;
        size_t bytesToCopy = std::min(sourceByteCount - bytesWritten, blockLeft);

        uint8_ptr_t blockPtr = _blocks[blockIndex];

        memcpy(blockPtr + blockOffset, sourceData + bytesWritten, bytesToCopy);

        // Update based on the number of bytes copied in this iteration.
        bytesWritten += bytesToCopy;
        _position += bytesToCopy;

        // Reset to the start of the next block.
        ++blockIndex;
        blockOffset = 0;
    }

    _totalSize = std::max(_totalSize, _position);

    return bytesWritten;
}

// Inherited from ISeekableStream.
StreamPosition MemoryStream::getLength() const
{
    return _totalSize;
}

// Inherited from ISeekableStream.
StreamPosition MemoryStream::getPosition() const
{
    return _position;
}

// Inherited from ISeekableStream.
StreamPosition MemoryStream::setPosition(StreamRelative relativeTo,
                                         StreamPosition offset)
{
    StreamPosition absPos;

    switch (relativeTo)
    {
    case Ag::IO::StreamRelative::Beginning:
    default:
        absPos = offset;
        break;

    case Ag::IO::StreamRelative::Current:
        absPos = _position + offset;
        break;

    case Ag::IO::StreamRelative::End:
        absPos = _totalSize + offset;
        break;
    }

    if (absPos < 0)
    {
        throw Ag::ArgumentException("The resultant stream offset cannot be negative."
                                    "offset");
    }

    if (isStreamSizeTooLargeForMemory(absPos))
    {
        std::string buffer;
        buffer.assign("The required memory stream size of ");
        Ag::appendFileSize(FormatInfo::getDisplay(), buffer, static_cast<uint64_t>(absPos));
        buffer.append(" is too big for a memory-based stream.");

        throw Ag::OperationException(buffer.c_str());
    }

    // Ensure there is enough storage space for the position to exist.
    setMinimumSize(absPos);

    // Apply the new position.
    _position = streamToMemorySize(absPos);

    return absPos;
}

//! @brief Extends the size of the internal buffer to encompass a minimum
//! required size.
//! @param[in] requiredSize The minimum required size of the buffer, in bytes.
void MemoryStream::setMinimumSize(size_t requiredSize)
{
    size_t blockSize = _allocator->getBlockSize();
    size_t allocatedSize = blockSize * _blocks.size();

    // Ensure we have enough space allocated for the bytes to write.
    if (requiredSize > allocatedSize)
    {
        // TODO: Determine if we need to upgrade the allocation strategy.
        size_t requiredBlocks = (requiredSize + blockSize - 1) / blockSize;

        if (_blocks.size() < requiredBlocks)
        {
            _allocator->appendAllocatedBlocks(requiredBlocks - _blocks.size(), _blocks);
        }
    }

    _totalSize = std::max(requiredSize, _totalSize);
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////
