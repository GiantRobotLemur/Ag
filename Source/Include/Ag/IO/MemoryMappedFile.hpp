//! @file Ag/IO/MemoryMappedFile.hpp
//! @brief The declaration of a wrapper for a memory mapped file.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_MEMORY_MAPPED_FILE_HPP_
#define HEADER_IO_MEMORY_MAPPED_FILE_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/Core/FsPath.hpp"

#include "ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A platform-specific abstraction of memory-mapped file mechanics.
class MappingHandle
{
public:
    // Construction/Destruction
    MappingHandle();
    MappingHandle(const MappingHandle &) = delete;
    MappingHandle(MappingHandle &&rhs) noexcept;
    ~MappingHandle();

    // Accessors
    bool isOpen() const;
    static size_t getBlockSize();
    StreamLength getLength() const;

    // Operations
    MappingHandle &operator=(const MappingHandle &) = delete;
    MappingHandle &operator=(MappingHandle &&rhs) noexcept;

    void open(const Fs::Path &filePath, FileAccessBits access,
              StreamLength mappingSize = -1);
    void *createView(StreamPosition blockIndex,
                     StreamLength length);
    static bool destroyView(void *viewPtr, StreamLength length, bool throwExceptions = false);
    void close();
private:
    // Internal Functions
    void closeNoExcept() noexcept;

    // Internal Fields
    StreamLength _length;
#ifdef _WIN32
    HANDLE _file;
    HANDLE _mapping;
#else
    int _mappingFd;
#endif
    FileAccessBits _originalAccess;
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object describing an area of memory at which the contents of 
//! a file has been mapped.
//! @remarks
//! The mapping remains in existence for the lifetime of the object.
class MemoryMappedView
{
public:
    // Construction/Destruction
    MemoryMappedView();
    MemoryMappedView(MemoryMappedView &&rhs) noexcept;
    MemoryMappedView(const StreamRegion &position, void *baseAddr);
    ~MemoryMappedView();

    // Accessors
    bool isActive() const;
    const StreamRegion &getPosition() const;
    void *getPointer() const;
    size_t getSize() const;

    // Operations
    // Copying not allowed.
    MemoryMappedView(const MemoryMappedView &) = delete;
    MemoryMappedView &operator=(const MemoryMappedView &) = delete;

    // Moving is allowed.
    MemoryMappedView &operator=(MemoryMappedView &&rhs) noexcept;
    void release();
private:
    // Internal Functions
    void releaseNoThrow() noexcept;

    // Internal Fields
    StreamRegion _position;
    void *_baseAddr;
};

//! @brief A wrapper for a memory mapped file.
class MemoryMappedFile
{
public:
    // Construction/Destruction
    MemoryMappedFile() = default;
    ~MemoryMappedFile() = default;

    // Accessors
    bool isOpen() const;
    static size_t getBlockSize();
    const Fs::Path &getFileName() const;
    StreamLength getMappingSize() const;

    // Operations
    MemoryMappedView createView(uint64_t firstBlock, size_t length);
    void open(const Fs::Path &path, FileAccessBits access, StreamLength mappingSize = -1);
    void close();
private:
    // Internal Fields
    Fs::Path _fileName;
    MappingHandle _handle;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
