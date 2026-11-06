//! @file IO/MemoryMappedFile.cpp
//! @brief The definition of a wrapper for a memory mapped file.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <utility>

#ifndef _WIN32
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#endif

#include <Ag/Core.hpp>

#include "Ag/IO/MemoryMappedFile.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// MappingHandle Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Ensures the file and mapping is closed without any exceptions
//! being thrown.
MappingHandle::~MappingHandle()
{
    closeNoExcept();
}

//! @brief Gets the length of the region of the file which can be mapped, in bytes.
StreamLength MappingHandle::getLength() const
{
    return _length;
}

#ifdef _WIN32
//! @brief Constructs an empty mapping handle object.
MappingHandle::MappingHandle() :
    _length(-1),
    _file(INVALID_HANDLE_VALUE),
    _mapping(nullptr),
    _originalAccess(0)
{
}

//! @brief Acquires a mapping handle from another object.
//! @param[in] rhs The object from which to acquire an open mapping.
MappingHandle::MappingHandle(MappingHandle &&rhs) noexcept :
    _length(rhs._length),
    _file(std::exchange(rhs._file, INVALID_HANDLE_VALUE)),
    _mapping(std::exchange(rhs._mapping, nullptr)),
    _originalAccess(rhs._originalAccess)
{
}

//! @brief Determines if the object is in an open state.
//! @retval true The file is open, regions can be mapped into memory.
//! @retval false No file is open, no view can be mapped.
bool MappingHandle::isOpen() const
{
    return _mapping != nullptr;
}

//! @brief Gets the size of blocks used to determine the start of a mapping
//! within the underlying file.
size_t MappingHandle::getBlockSize()
{
    static size_t globalBlockSize = 0;

    if (globalBlockSize == 0)
    {
        SYSTEM_INFO si;
        ::GetSystemInfo(&si);

        globalBlockSize = static_cast<size_t>(si.dwAllocationGranularity);
    }

    return globalBlockSize;
}

//! @brief Closes the current mapping an acquires another from another object.
//! @param[in] rhs The object to acquire a mapping from.
//! @return A reference to the current object.
MappingHandle &MappingHandle::operator=(MappingHandle &&rhs) noexcept
{
    if (_mapping != rhs._mapping)
    {
        closeNoExcept();

        _file = std::exchange(rhs._file, INVALID_HANDLE_VALUE);
        _mapping = std::exchange(rhs._mapping, nullptr);
        _originalAccess = rhs._originalAccess;
    }

    return *this;
}

//! @brief Opens the file.
//! @param[in] filePath The path to the file to open.
//! @param[in] access The requested access to the underlying file.
//! @param[in] mappingSize The amount of the file to be able to map, measured in
//! bytes from the beginning of the file.
//! @remarks
//! If a file is being created, a positive @p mappingSize must be specified.
void MappingHandle::open(const Fs::Path &filePath, FileAccessBits access,
                         StreamLength mappingSize /*= -1*/)
{
    if (_file != INVALID_HANDLE_VALUE)
        throw OperationException("Cannot open a file which is already open.");

    std::wstring widePath = filePath.toWideString(Fs::PathUsage::Kernel);

    DWORD rawAccess = 0;
    DWORD protection = 0;
    DWORD shareMode = FILE_SHARE_READ;
    DWORD createMode = OPEN_ALWAYS;
    bool needsInitialSize = false;

    if (access & FileAccess::Read)
    {
        rawAccess |= GENERIC_READ;
        protection = PAGE_READONLY;
    }

    if (access & FileAccess::Write)
    {
        rawAccess |= GENERIC_WRITE;
        shareMode = 0;
        protection = PAGE_READWRITE;
    }
    else
    {
        // If the file is read-only, it needs an initial size.
        needsInitialSize = true;
    }

    if (access & FileAccess::CreateNew)
    {
        createMode = CREATE_NEW;
        needsInitialSize = true;
    }
    else if (access & FileAccess::CreateAlways)
    {
        createMode = CREATE_ALWAYS;
        needsInitialSize = true;
    }
    else if (access & FileAccess::OpenExisting)
    {
        createMode = OPEN_EXISTING;
        needsInitialSize = false;
    }

    HANDLE file = ::CreateFileW(widePath.c_str(), rawAccess, shareMode,
                                nullptr, createMode,
                                FILE_ATTRIBUTE_NORMAL, nullptr);

    if (file == INVALID_HANDLE_VALUE)
    {
        uint32_t errorCode = ::GetLastError();
        Fs::Path fullPath = filePath.convertToAbsolute();

        std::string fn("CreateFileW(\"");
        appendAgString(fn, fullPath.toString());
        fn.push_back('\"');
        fn.push_back(')');

        throw Win32Exception(fn.c_str(), errorCode);
    }

    // Ensure the file is closed if something goes wrong.
    AtScopeExit1 closeFileOnExit(::CloseHandle, file);

    if (needsInitialSize)
    {
        if (mappingSize <= 0)
        {
            throw ArgumentException("An initial size for the file needs to be specified",
                                    "access");
        }

        // Set the size of the file by setting the file pointer to the new end.
        LARGE_INTEGER fp;
        fp.QuadPart = mappingSize;

        if (::SetFilePointerEx(file, fp, nullptr, FILE_BEGIN) == FALSE)
            throw Win32Exception("SetFilePointerEx(Intended Length)", ::GetLastError());

        if (::SetEndOfFile(file) == FALSE)
            throw Win32Exception("SetEndOfFile()", ::GetLastError());

        // Reset the pointer to the beginning of the file.
        fp.QuadPart = 0;
        if (::SetFilePointerEx(file, fp, nullptr, FILE_BEGIN) == FALSE)
            throw Win32Exception("SetFilePointerEx(0)", ::GetLastError());
    }

    LARGE_INTEGER sizeComponents;

    if (mappingSize < 0)
    {
        // Determine the size of the file.
        ::GetFileSizeEx(file, &sizeComponents);
    }
    else
    {
        sizeComponents.QuadPart = mappingSize;
    }

    HANDLE mapping = ::CreateFileMappingW(file, nullptr, protection,
                                          static_cast<DWORD>(sizeComponents.HighPart),
                                          sizeComponents.LowPart, nullptr);

    if (mapping == nullptr)
    {
        // Capture the thread error code before doing anything else.
        uint32_t errorCode = ::GetLastError();

        Fs::Path fullPath = filePath.convertToAbsolute();

        std::string fn("CreateFileMappingW(\"");
        appendAgString(fn, fullPath.toString());
        fn.push_back('\"');
        fn.push_back(')');

        throw Win32Exception(fn.c_str(), errorCode);
    }

    // Otherwise, commit to the opening of the file mapping object.
    closeFileOnExit.cancel();

    _length = sizeComponents.QuadPart;
    _file = file;
    _mapping = mapping;
    _originalAccess = access;
}
//! @brief Attempts to create a memory mapped view of the open file.
//! @param[in] blockIndex The start of the region of the file to map, expressed
//! as an index of blocks based on the value returned by getBlockSize().
//! @param[in] length The length of the region to map, in bytes.
//! @return The pointer to the first byte of the file mapped into memory.
void *MappingHandle::createView(StreamPosition blockIndex,
                                StreamLength length)
{
    if (_file == INVALID_HANDLE_VALUE)
        throw OperationException("Cannot map a view of a closed file.");

    if (length < 1)
        throw ArgumentException("A view of a file must have a positive size.");

    DWORD viewAccess = 0;

    if (_originalAccess & FileAccess::Read)
        viewAccess = FILE_MAP_READ;

    if (_originalAccess & FileAccess::Write)
        viewAccess = FILE_MAP_WRITE;

    LARGE_INTEGER offset;
    offset.QuadPart = blockIndex * static_cast<StreamLength>(getBlockSize());

    void *ptr = ::MapViewOfFile(_mapping, viewAccess, offset.HighPart, offset.LowPart, length);

    if (ptr == nullptr)
        throw Win32Exception("MapViewOfFile()", ::GetLastError());

    return ptr;
}

//! @brief Unmaps a previously mapped view of a file.
//! @param[in] viewPtr The pointer returned by createView().
//! @param[in] length The length of the region to unmap - ignored in Win32 implementations.
//! @param[in] throwExceptions True if an exception should be thrown on failure,
//! false to silently ignore failures.
//! @return A boolean value indicating if the operation was successful, always
//! true if throwExceptions is true.
bool MappingHandle::destroyView(void *viewPtr, StreamLength /*length*/,
                                bool throwExceptions /*= false*/)
{
    if (::UnmapViewOfFile(viewPtr) == FALSE)
    {
        if (throwExceptions)
            throw Win32Exception("UnmapViewOfFile()", ::GetLastError());

        return false;
    }

    return true;
}

//! @brief Ensures that if the file is open, it will be closed.
//! @throws Win32Exception If there were failures closing the file.
void MappingHandle::close()
{
    HANDLE mapping = std::exchange(_mapping, nullptr);
    HANDLE file = std::exchange(_file, INVALID_HANDLE_VALUE);

    if (mapping != nullptr)
    {
        if (::CloseHandle(mapping) == FALSE)
            throw Win32Exception("CloseHandle(FileMapping)", ::GetLastError());
    }

    if (file != INVALID_HANDLE_VALUE)
    {
        if (::CloseHandle(file) == FALSE)
            throw Win32Exception("CloseHandle(File)", ::GetLastError());
    }
}

//! @brief Ensures that if the file is open, it will be closed, silently
//! ignoring any errors which occur.
void MappingHandle::closeNoExcept() noexcept
{
    HANDLE mapping = std::exchange(_mapping, nullptr);
    HANDLE file = std::exchange(_file, INVALID_HANDLE_VALUE);

    if (mapping != nullptr)
        ::CloseHandle(mapping);

    if (file != INVALID_HANDLE_VALUE)
        ::CloseHandle(file);
}

#else // ifndef _WIN32
//! @brief Constructs an empty mapping handle object.
MappingHandle::MappingHandle() :
    _length(-1),

    _mappingFd(-1),
    _originalAccess(0)
{
}

//! @brief Acquires a mapping handle from another object.
//! @param[in] rhs The object from which to acquire an open mapping.
MappingHandle::MappingHandle(MappingHandle &&rhs) noexcept :
    _length(rhs._length),
    _mappingFd(std::exchange(rhs._mappingFd, -1)),
    _originalAccess(rhs._originalAccess)
{
}

//! @brief Determines if the object is in an open state.
//! @retval true The file is open, regions can be mapped into memory.
//! @retval false No file is open, no view can be mapped.
bool MappingHandle::isOpen() const
{
    return _mappingFd >= 0;
}

//! @brief Gets the size of blocks used to determine the start of a mapping
//! within the underlying file.
size_t MappingHandle::getBlockSize()
{
    static size_t globalBlockSize = 0;

    if (globalBlockSize == 0)
    {
        globalBlockSize = static_cast<size_t>(sysconf(_SC_PAGESIZE));
    }

    return globalBlockSize;
}

//! @brief Closes the current mapping an acquires another from another object.
//! @param[in] rhs The object to acquire a mapping from.
//! @return A reference to the current object.
MappingHandle &MappingHandle::operator=(MappingHandle &&rhs) noexcept
{
    if (_mappingFd != rhs._mappingFd)
    {
        closeNoExcept();

        _mappingFd = std::exchange(rhs._mappingFd, -1);
        _originalAccess = rhs._originalAccess;
    }

    return *this;
}

//! @brief Opens the file.
//! @param[in] filePath The path to the file to open.
//! @param[in] access The requested access to the underlying file.
//! @param[in] mappingSize The amount of the file to be able to map, measured in
//! bytes from the beginning of the file.
//! @remarks
//! If a file is being created, a positive @p mappingSize must be specified.
void MappingHandle::open(const Fs::Path &filePath, FileAccessBits access,
                         StreamLength mappingSize /*= -1*/)
{
    if (_mappingFd >= 0)
        throw OperationException("Cannot open a file which is already open.");

    int flags = 0;
    mode_t mode;
    bool needsInitialSize = false;

    if (access & FileAccess::Read)
    {
        mode = S_IRUSR;
        flags = O_RDONLY;
    }

    if (access & FileAccess::Write)
    {
        mode |= S_IWUSR;
        flags = (access & FileAccess::Read) ? O_RDWR : O_WRONLY;
    }
    else
    {
        // If the file is read-only, it needs an initial size.
        needsInitialSize = true;
    }

    if (access & FileAccess::CreateNew)
    {
        flags |= (O_CREAT | O_EXCL);
        needsInitialSize = true;
    }
    else if (access & FileAccess::CreateAlways)
    {
        flags |= (O_CREAT | O_TRUNC);
        needsInitialSize = true;
    }
    else if (access & FileAccess::OpenExisting)
    {
        needsInitialSize = false;
    }

    Fs::Path fullPath = filePath.convertToAbsolute();
    String pathText = fullPath.toString(Fs::PathUsage::Kernel);

    int fd = open64(pathText.getUtf8Bytes(), flags, mode);

    if (fd < 0)
    {
        // Preserve the error code while we format an error message.
        auto errorCode = errno;

        std::string fnName("open64('");
        appendAgString(fnName, pathText);
        fnName.append("')");

        throw RuntimeLibraryException(fnName.c_str(), errorCode);
    }

    // Ensure the file is closed if something goes wrong.
    AtScopeExit1 closeFileOnExit(::close, fd);

    if (needsInitialSize)
    {
        // Set the initial size of the file before any views are mapped.
        if (ftruncate64(fd, static_cast<off64_t>(mappingSize)) < 0)
        {
            // Preserve the error code while we format an error message.
            auto errorCode = errno;

            std::string fnName("ftruncate64('");
            appendAgString(fnName, pathText);
            fnName.push_back(',');
            fnName.push_back(' ');
            appendFileSize(FormatInfo::getDisplay(), fnName, mappingSize);
            fnName.append("')");

            throw RuntimeLibraryException(fnName.c_str(), errorCode);
        }
    }
    else if (mappingSize < 0)
    {
        // Determine the size of the file.
        struct stat64 fileInfo;

        if (fstat64(fd, &fileInfo) < 0)
        {
            // Preserve the error code while we format an error message.
            auto errorCode = errno;

            std::string fnName("fstat64('");
            appendAgString(fnName, pathText);
            fnName.append("')");

            throw RuntimeLibraryException(fnName.c_str(), errorCode);
        }

        mappingSize = static_cast<StreamLength>(fileInfo.st_size);
    }

    // Otherwise, commit to the opening of the file mapping object.
    closeFileOnExit.cancel();

    _length = mappingSize;
    _mappingFd = fd;
    _originalAccess = access;
}

//! @brief Attempts to create a memory mapped view of the open file.
//! @param[in] blockIndex The start of the region of the file to map, expressed
//! as an index of blocks based on the value returned by getBlockSize().
//! @param[in] length The length of the region to map, in bytes.
//! @return The pointer to the first byte of the file mapped into memory.
void *MappingHandle::createView(StreamPosition blockIndex,
                                StreamLength length)
{
    if (_mappingFd < 0)
        throw OperationException("Cannot map a view of a closed file.");

    if (length < 1)
        throw ArgumentException("A view of a file must have a positive size.");

    int protect = 0;
    int flags = MAP_SHARED;

    if (_originalAccess & FileAccess::Read)
    {
        protect = PROT_READ;
    }

    if (_originalAccess & FileAccess::Write)
    {
        protect |= PROT_WRITE;
    }

    void *ptr = mmap64(nullptr, streamToMemorySize(length), protect, flags, _mappingFd,
                       static_cast<off64_t>(blockIndex) * getBlockSize());

    if (ptr == MAP_FAILED)
        throw RuntimeLibraryException("mmap64()", errno);

    return ptr;
}

//! @brief Unmaps a previously mapped view of a file.
//! @param[in] viewPtr The pointer returned by createView().
//! @param[in] length The length of the region to unmap.
//! @param[in] throwExceptions True if an exception should be thrown on failure,
//! false to silently ignore failures.
//! @return A boolean value indicating if the operation was successful, always
//! true if throwExceptions is true.
bool MappingHandle::destroyView(void *viewPtr, StreamLength length, bool throwExceptions /*= false*/)
{
    if (munmap(viewPtr, streamToMemorySize(length)) < 0)
    {
        if (throwExceptions)
            throw RuntimeLibraryException("munmap()", errno);

        return false;
    }

    return true;
}

//! @brief Ensures that if the file is open, it will be closed.
//! @throws RuntimeLibraryException If there were failures closing the file.
void MappingHandle::close()
{
    int fd = std::exchange(_mappingFd, -1);

    if (fd >= 0)
    {
        if (::close(fd) != 0)
            throw RuntimeLibraryException("close()", errno);
    }
}

//! @brief Ensures that if the file is open, it will be closed, silently
//! ignoring any errors which occur.
void MappingHandle::closeNoExcept() noexcept
{
    int fd = std::exchange(_mappingFd, -1);

    if (fd >= 0)
    {
        ::close(fd);
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////
// MemoryMappedView Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an empty object intended to wrap a view of a portion of
//! a file mapped into memory.
MemoryMappedView::MemoryMappedView() :
    _baseAddr(nullptr)
{
}

//! @brief Creates an object which acquires a view of a portion of a file from
//! another object.
//! @param[in] rhs The object from which to acquire the view.
MemoryMappedView::MemoryMappedView(MemoryMappedView &&rhs) noexcept :
    _position(rhs._position),
    _baseAddr(rhs._baseAddr)
{
    rhs._position = StreamRegion();
    rhs._baseAddr = nullptr;
}

//! @brief Creates an object initialised with a view of a portion of a file.
//! @param[in] position The portion of the file mapped.
//! @param[in] baseAddr A pointer to the file data mapped into the process
//! address space.
MemoryMappedView::MemoryMappedView(const StreamRegion &position, void *baseAddr) :
    _position(position),
    _baseAddr(baseAddr)
{
}

//! @brief Ensures that the mapping is released if it wasn't already.
MemoryMappedView::~MemoryMappedView()
{
    releaseNoThrow();
}

//! @brief Determines if the object wraps an active file mapping.
//! @retval true The object points to a block of memory mapped file contents.
//! @retval false The object is not initialised with a mapped block.
bool MemoryMappedView::isActive() const
{
    return _baseAddr != nullptr;
}

//! @brief Gets the position within the file of the mapped block.
const StreamRegion &MemoryMappedView::getPosition() const
{
    return _position;
}

//! @brief Gets the pointer of the first byte of file data mapped into the
//! process's address space, or nullptr if the object was inactive.
void *MemoryMappedView::getPointer() const
{
    return _baseAddr;
}

//! @brief Gets the size of the block of memory mapped from the file, in bytes.
size_t MemoryMappedView::getSize() const
{
    return static_cast<size_t>(_position.getLength());
}

//! @brief Acquires a mapping from another object.
//! @param[in] rhs The object to acquire the mapping from.
//! @return A reference to the current object.
MemoryMappedView &MemoryMappedView::operator=(MemoryMappedView &&rhs) noexcept
{
    releaseNoThrow();

    _position = rhs._position;
    _baseAddr = rhs._baseAddr;

    rhs._position = StreamRegion();
    rhs._baseAddr = nullptr;

    return *this;
}

//! @brief Release the file mapping, if it wasn't released already, throwing
//! an exception if the operation fails.
void MemoryMappedView::release()
{
    if (_baseAddr != nullptr)
    {
        StreamLength originalLength = _position.getLength();
        void *ptr = _baseAddr;
        _position = StreamRegion();
        _baseAddr = nullptr;

        MappingHandle::destroyView(ptr, originalLength, /* throwException = */ true);
    }
}

//! @brief Release the file mapping, if it wasn't released already, silently
//! ignoring any failures.
void MemoryMappedView::releaseNoThrow() noexcept
{
    if (_baseAddr != nullptr)
    {
        StreamLength originalLength = _position.getLength();
        void *ptr = _baseAddr;
        _position = StreamRegion();
        _baseAddr = nullptr;

        MappingHandle::destroyView(ptr, originalLength, /* throwException = */ false);
    }
}

////////////////////////////////////////////////////////////////////////////////
// MemoryMappedFile Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Determines if the object is in an open state.
//! @retval true The object is in an open state and new views can be created.
//! @retval false The file is closed.
bool MemoryMappedFile::isOpen() const
{
    return _handle.isOpen();
}

//! @brief Gets the size of blocks used to define the offset of views into a
//! memory mapped file.
//! @return The granularity of offsets into a file at which views can be created.
size_t MemoryMappedFile::getBlockSize()
{
    return MappingHandle::getBlockSize();
}

//! @brief Gets the name of the file which was mapped.
const Fs::Path &MemoryMappedFile::getFileName() const
{
    return _fileName;
}

//! @brief Gets the size of the area of the file which can be
//! memory mapped, in bytes.
StreamLength MemoryMappedFile::getMappingSize() const
{
    return _handle.getLength();
}

//! @brief Maps a view of part of the file.
//! @param[in] firstBlock The index of the first block of the file to map.
//! @param[in] length The length of the view.
//! @return An object representing the contents of the file mapped into memory.
//! @remarks
//! The @p firstBlock parameter can be calculated using the getBlockSize()
//! static member function. View must be mapped on block boundaries.
MemoryMappedView MemoryMappedFile::createView(uint64_t firstBlock, size_t length)
{
    void *ptr = _handle.createView(static_cast<StreamPosition>(firstBlock), length);

    StreamPosition offset = firstBlock * MappingHandle::getBlockSize();

    return MemoryMappedView(StreamRegion(offset, length), ptr);
}

//! @brief Opens an existing file for memory mapping.
//! @param[in] path The path to the file to create.
//! @param[in] access The desired access to the file.
//! @param[in] mappingSize The count of bytes in the file to be able to map.
void MemoryMappedFile::open(const Fs::Path &path,
                            FileAccessBits access,
                            StreamLength mappingSize /*= -1*/)
{
    _handle.open(path, access, mappingSize);

    _fileName = path.convertToAbsolute();
}

//! @brief Closes the file mapping if it wasn't already.
//! @remarks
//! It is up to the caller to ensure that all previously opened views on the
//! mapping area already closed.
void MemoryMappedFile::close()
{
    _fileName = Fs::Path();
    _handle.close();
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

