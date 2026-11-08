//! @file Core/Memory.cpp
//! @brief The definition of utility functions related to memory management.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2023-2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <cstdlib>

#ifndef _WIN32
#include <sys/mman.h>
#endif

#include "Ag/Core/Exception.hpp"
#include "Ag/Core/Memory.hpp"
#include "Ag/Core/Variant.hpp"
#include "Ag/Core/VariantTypes.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Allocates a block of memory with a specific address alignment.
//! @param[in] alignment The address boundary the block should be aligned on,
//! must be a power of 2.
//! @param[in] sizeInBytes The minimum count of bytes in the allocated block.
//! @return A pointer to the newly allocated block of memory, to be freed with
//! a call to freeAligned().
void *mallocAligned(size_t alignment, size_t sizeInBytes)
{
#ifdef _MSC_VER
#define MALLOC_FN "_aligned_malloc()"
    void *block = _aligned_malloc(sizeInBytes, alignment);
#else
#define MALLOC_FN "aligned_malloc()"
    void *block = aligned_alloc(alignment, sizeInBytes);
#endif

    if (block == nullptr)
    {
        if (errno == 0)
        {
            String detail = String::format("Failed to allocate a block of {0} "
                                           "bytes on an {1} byte address boundary.",
                                           { sizeInBytes, alignment });
            throw OperationException(detail);
        }
        else
        {
            throw RuntimeLibraryException(MALLOC_FN, errno);
        }
    }

#undef MALLOC_FN

    return block;
}

//! @brief Allocates a block of memory with a specific address alignment.
//! @param[in] alignmentPow2 The address boundary the block should be aligned on,
//! expressed as a power of 2.
//! @param[in] sizeInBytes The minimum count of bytes in the allocated block.
//! @return A pointer to the newly allocated block of memory, to be freed with
//! a call to freeAligned().
void *mallocAlignedPow2(uint8_t alignmentPow2, size_t sizeInBytes)
{
    return mallocAligned(static_cast<size_t>(1) << alignmentPow2,
                         sizeInBytes);
}

//! @brief Frees a block of memory previously allocated with mallocAligned*().
//! @param[in] alignedBlock A pointer to the start of the memory block to free,
//! if nullptr, no action is performed.
void freeAligned(void *alignedBlock)
{
    if (alignedBlock != nullptr)
    {
#ifdef _MSC_VER
        _aligned_free(alignedBlock);
#else
        // In non-MSVC runtime libraries, the conventional free function
        // is good enough.
        free(alignedBlock);
#endif
    }
}

//! @brief Gets the size of a paged block, which is the granularity of bytes
//! which can be allocated using allocatePagedBlock().
//! @return A count of bytes, very probably an exact power of 2.
size_t getPagedBlockSize()
{
    static size_t BlockSize = 0;

    if (BlockSize == 0)
    {
#ifdef _WIN32
        SYSTEM_INFO si;
        ::GetSystemInfo(&si);

        BlockSize = si.dwPageSize;
#else
        BlockSize = static_cast<size_t>(sysconf(_SC_PAGESIZE));
#endif
    }

    return BlockSize;
}

//! @brief Allocates a count page blocks.
//! @param[in] blockCount The count of page blocks to allocate.
//! @return A pointer to the newly allocated block.
//! @throws OutOfMemoryException if the
void *allocatePagedBlock(size_t blockCount)
{
    if (blockCount < 1)
        throw ArgumentException("A positive count of page blocks must be requested.",
                                "blockCount");

    size_t actualSize = blockCount * getPagedBlockSize();

#ifdef _WIN32
    void *block = ::VirtualAlloc(nullptr, actualSize,
                                 MEM_RESERVE | MEM_COMMIT,
                                 PAGE_READWRITE);

    if (block == nullptr)
#else
    void *block = mmap64(nullptr, actualSize, PROT_READ | PROT_WRITE,
                         MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

    if (block == MAP_FAILED)
#endif

        throw OutOfMemoryException(actualSize);

    return block;
}

//! @brief Frees memory allocated with allocatePagedBlock().
//! @param[in] block A pointer to the beginning of the block to free.
//! @param[in] blockCount The count of paged blocks in the region being freed.
//! @param[in] dontThrow True to suppress exceptions on failure, false to report
//! failures by throwing an exception.
bool freePagedBlock(void *block, size_t blockCount, bool dontThrow)
{
#ifdef _WIN32
    AG_UNUSED_PARAM(blockCount);

    bool isOK = (::VirtualFree(block, 0, MEM_RELEASE) == FALSE);

    if ((isOK == false) && (dontThrow == false))
        throw Win32Exception("VirtualFree()", ::GetLastError());
#else
    bool isOK = (::munmap(block, blockCount * getPagedBlockSize()) == 0);

    if ((isOK == false) && (dontThrow == false))
        throw RuntimeLibraryException("mmap64()", errno);
#endif

    return isOK;
}

} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

