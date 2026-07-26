//! @file IO/SeekableFileStream.cpp
//! @brief The definition of an implementation of ISeekableStream backed by
//! a file on a local file system.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////

#ifndef _WIN32
// POSIX Headers required.
#include <sys/stat.h>
#endif

#include "Ag/IO/SeekableFileStream.hpp"

namespace Ag {
namespace IO {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32

//! @brief A structure which defines generic C-style file operations.
struct FileTraits
{
    using FileDescriptor = HANDLE;
    using ErrorCode = DWORD;
    static constexpr FileDescriptor BadFile = INVALID_HANDLE_VALUE;

    static Exception createError(const std::string_view &fnName,
                                 ErrorCode errorCode)
    {
        return Win32Exception(fnName.data(), errorCode);
    }

    static bool isValidFd(FileDescriptor fd)
    {
        return (fd != NULL) && (fd != INVALID_HANDLE_VALUE);
    }

    static void flush(FileDescriptor fd)
    {
        ::FlushFileBuffers(fd);
    }

    static size_t read(FileDescriptor fd, void *buffer,
                       size_t byteCount, ErrorCode &errorCode)
    {
        size_t bytesRead = 0;
        errorCode = ERROR_SUCCESS;

        do
        {
            DWORD bytesToRead = static_cast<DWORD>(std::min<size_t>(UINT32_MAX,
                                                                    byteCount - bytesRead));
            DWORD actuallyRead = 0;

            if (::ReadFile(fd, buffer, bytesToRead, &actuallyRead, nullptr))
            {
                bytesRead += actuallyRead;

                if (actuallyRead < bytesToRead)
                {
                    // We got as much as we could.
                    break;
                }
            }
            else
            {
                errorCode = ::GetLastError();
                break;
            }
        } while (bytesRead < byteCount);

        return bytesRead;
    }

    static size_t write(FileDescriptor fd, const void *buffer,
                        size_t byteCount, ErrorCode &errorCode)
    {
        size_t bytesWritten = 0;
        errorCode = ERROR_SUCCESS;

        const uint8_t *source = reinterpret_cast<const uint8_t *>(buffer);

        while (bytesWritten < byteCount)
        {
            DWORD bytesToWrite = static_cast<DWORD>(std::min<size_t>(UINT32_MAX,
                                                                     byteCount - bytesWritten));
            DWORD actuallyWritten;

            if (::WriteFile(fd, source + bytesWritten, bytesToWrite, &actuallyWritten, nullptr))
            {
                bytesWritten += actuallyWritten;

                if (actuallyWritten < bytesToWrite)
                {
                    // We didn't manage to write it all, so stop trying.
                    break;
                }
            }
            else
            {
                errorCode = ::GetLastError();
                break;
            }
        }

        return bytesWritten;
    }

    static StreamPosition getSize(FileDescriptor fd, ErrorCode &errorCode)
    {
        LARGE_INTEGER win32FileSize;

        if (::GetFileSizeEx(fd, &win32FileSize) == FALSE)
        {
            errorCode = ::GetLastError();
            return -1;
        }

        errorCode = 0;
        return win32FileSize.QuadPart;
    }

    static StreamPosition tell(FileDescriptor fd, ErrorCode &errorCode)
    {
        LARGE_INTEGER win32RelativePos, absPos;
        win32RelativePos.QuadPart = 0;

        if (::SetFilePointerEx(fd, win32RelativePos, &absPos, FILE_CURRENT) == FALSE)
        {
            errorCode = ::GetLastError();
            return -1;
        }

        errorCode = 0;
        return absPos.QuadPart;
    }

    static StreamPosition seek(FileDescriptor fd, StreamRelative relativeTo,
                               StreamPosition offset, ErrorCode &errorCode)
    {
        LARGE_INTEGER win32RelativePos, absPos;
        win32RelativePos.QuadPart = offset;

        DWORD method;

        switch (relativeTo)
        {
        case StreamRelative::Beginning:
        default:
            method = FILE_BEGIN;
            break;

        case StreamRelative::Current:
            method = FILE_CURRENT;
            break;

        case StreamRelative::End:
            method = FILE_END;
            break;
        }

        if (::SetFilePointerEx(fd, win32RelativePos, &absPos, method) == FALSE)
        {
            errorCode = ::GetLastError();
            return -1;
        }

        errorCode = 0;
        return absPos.QuadPart;
    }

    static bool tryOpen(const Fs::Path &path, FileAccessBits access,
                        FileDescriptor &fd, ErrorCode &errorCode)
    {
        std::wstring filename = path.toWideString(Fs::PathUsage::Kernel);

        DWORD handleAccess = 0;
        DWORD shareMode = FILE_SHARE_READ;
        DWORD createMode = 0;

        if (access & FileAccess::Read)
        {
            handleAccess |= GENERIC_READ;
        }

        if (access & FileAccess::Write)
        {
            handleAccess |= GENERIC_WRITE;
            shareMode = 0;
        }

        if (access & FileAccess::CreateAlways)
        {
            createMode |= CREATE_ALWAYS;
        }
        else if (access & FileAccess::CreateNew)
        {
            createMode |= CREATE_NEW;
        }
        else if (access & FileAccess::OpenExisting)
        {
            createMode |= OPEN_EXISTING;
        }
        else
        {
            createMode |= OPEN_ALWAYS;
        }

        fd = ::CreateFileW(filename.c_str(), handleAccess,
                           shareMode, nullptr, createMode,
                           0, nullptr);

        errorCode = ::GetLastError();

        return fd != INVALID_HANDLE_VALUE;
    }

    static FileDescriptor open(const Fs::Path &path, FileAccessBits access)
    {
        ErrorCode errorCode;
        FileDescriptor fd;

        if (tryOpen(path, access, fd, errorCode) == false)
        {
            std::string fnName("CreateFile('");
            appendAgString(fnName, path.toString(Fs::PathUsage::Kernel));
            fnName.append("')");

            throw Win32Exception(fnName.c_str(), static_cast<uint32_t>(errorCode));
        }

        return fd;
    }

    static bool close(FileDescriptor fd)
    {
        if (fd != BadFile)
        {
            return ::CloseHandle(fd) != FALSE;
        }

        return true;
    }
};
#else // if POSIX

//! @brief A structure which defines generic C-style file operations.
struct FileTraits
{
    using FileDescriptor = int;
    using ErrorCode = int;
    static constexpr FileDescriptor BadFile = -1;

    static Exception createError(const std::string_view &fnName,
                                 ErrorCode errorCode)
    {
        return RuntimeLibraryException(fnName.data(), errorCode);
    }

    static bool isValidFd(FileDescriptor fd)
    {
        return fd >= 0;
    }

    static void flush(FileDescriptor fd)
    {
        ::fsync(fd);
    }

    static size_t read(FileDescriptor fd, void *buffer,
                       size_t byteCount, ErrorCode &errorCode)
    {
        auto bytesRead = ::read(fd, buffer, byteCount);

        if (bytesRead < 0)
        {
            errorCode = errno;
            return 0;
        }
        else
        {
            errorCode = 0;
            return static_cast<size_t>(bytesRead);
        }
    }

    static size_t write(FileDescriptor fd, const void *buffer,
                        size_t byteCount, ErrorCode &errorCode)
    {
        auto bytesWritten = ::write(fd, buffer, byteCount);

        if (bytesWritten < 0)
        {
            errorCode = errno;
            return 0;
        }
        else
        {
            errorCode = 0;
            return static_cast<size_t>(bytesWritten);
        }
    }

    static StreamPosition getSize(FileDescriptor fd, ErrorCode &errorCode)
    {
        struct stat64 fileInfo;

        errorCode = fstat64(fd, &fileInfo);

        if (errorCode < 0)
        {
            errorCode = errno;

            return -1;
        }

        errorCode = 0;
        return static_cast<StreamPosition>(fileInfo.st_size);
    }

    static StreamPosition tell(FileDescriptor fd, ErrorCode &errorCode)
    {
        // Seek to the current position to retrieve the current absolute position.
        auto offset = lseek64(fd, 0, SEEK_CUR);

        if (offset < 0)
        {
            errorCode = errno;

            return -1;
        }

        errorCode = 0;
        return static_cast<StreamPosition>(offset);
    }

    static StreamPosition seek(FileDescriptor fd, StreamRelative relativeTo,
                               StreamPosition offset, ErrorCode &errorCode)
    {
        int whence;

        switch (relativeTo)
        {
        case StreamRelative::Beginning:
        default:
            whence = SEEK_SET;
            break;

        case StreamRelative::Current:
            whence = SEEK_CUR;
            break;

        case StreamRelative::End:
            whence = SEEK_END;
            break;
        }

        auto absPos = lseek64(fd, static_cast<off64_t>(offset), whence);

        if (absPos < 0)
        {
            errorCode = errno;
            return -1;
        }

        errorCode = 0;
        return static_cast<StreamPosition>(absPos);
    }

    static bool tryOpen(const Fs::Path &path, FileAccessBits access,
                        FileDescriptor &fd, ErrorCode &errorCode)
    {
        String pathText = path.toString(Fs::PathUsage::Kernel);
        int flags = 0;
        int mode = S_IREAD | S_IWRITE | S_IRGRP | S_IWGRP;

        static constexpr FileAccessBits ReadWrite = FileAccess::Read | FileAccess::Write;
        static constexpr FileAccessBits Create = FileAccess::CreateNew | FileAccess::CreateAlways;

        if ((access & ReadWrite) == ReadWrite)
        {
            flags = O_RDWR;
        }
        else if (access & FileAccess::Write)
        {
            flags = O_WRONLY;
        }
        else
        {
            flags = O_RDONLY;
        }

        FileDescriptor fd;

        if (access & Create)
        {
            fd = ::open64(pathText.getUtf8Bytes(), flags | O_EXCL | O_CREAT, mode);

            if ((fd >= 0) && (access & FileAccess::CreateAlways))
            {
                // Truncate the file to zero length.
                if (ftruncate(fd, 0) < 0)
                {
                    errorCode = static_cast<uintptr_t>(errno);

                    return false;
                }
            }
        }
        else
        {
            fd = ::open64(pathText.getUtf8Bytes(), flags, mode);
        }

        // Capture the last error.
        errorCode = static_cast<uintptr_t>(errno);

        return (fd < 0);
    }

    static FileDescriptor open(const Fs::Path &path, FileAccessBits access)
    {
        uintptr_t errorCode;
        int fd;

        if (tryOpen(path, access, fd, errorCode))
        {
            return fd;
        }
        else
        {
            std::string fnName("open64('");
            appendAgString(fnName, path.toString(Fs::PathUsage::Kernel));
            fnName.append("')");

            throw RuntimeLibraryException(fnName.c_str(), errorCode);
        }
    }

    static bool close(FileDescriptor fd)
    {
        if (fd < 0)
        {
            return true;
        }
        else
        {
            return ::close(fd) >= 0;
        }
    }
};
#endif // ifdef _WIN32

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ISeekableFileStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object wrapping a file stream.
//! @param[in] path The location of the file being accessed.
//! @param[in] fd The value identifying the connection to the file.
SeekableFileStream::SeekableFileStream(const Fs::Path &path, FileDescriptor fd) :
    _location(path),
    _fd(fd)
{
}

//! @brief Ensure that the file is properly closed, if still open.
SeekableFileStream::~SeekableFileStream()
{
    FileTraits::close(_fd);
    _fd = FileTraits::BadFile;
}

//! @brief Creates a new instance of an ISeekableFileStream by opening a file.
//! @param[in] at The location of the file to open.
//! @param[in] access A flags field defined by FileAccess specifying how the file
//! should be opened and managed.
//! @return A unique pointer to an implementation of IFileStream which can be
//! used to access the named file.
ISeekableStreamUPtr SeekableFileStream::open(const Fs::Path &at, FileAccessBits access)
{
    FileTraits::FileDescriptor fd = FileTraits::open(at, access);

    return ISeekableStreamUPtr(new SeekableFileStream(at, fd));
}

//! @brief Attempts to create a new instance of an ISeekableFileStream by opening a file.
//! @param[out] stream Receives the newly created stream, or is reset to an empty state.
//! @param[in] at The location of the file to open.
//! @param[in] access A flags field defined by FileAccess specifying how the file
//! should be opened and managed.
//! @retval true The file was successfully opened, @p stream has received a valid value.
//! @retval false The operation failed, @p stream is set to an empty state.
bool SeekableFileStream::tryOpen(ISeekableStreamUPtr &stream,
                                 const Fs::Path &at, FileAccessBits access)
{
    stream.reset();

    FileTraits::FileDescriptor fd;
    FileTraits::ErrorCode errorCode;

    if (FileTraits::tryOpen(at, access, fd, errorCode))
    {
        stream = ISeekableStreamUPtr(new SeekableFileStream(at, fd));

        return true;
    }

    return false;
}

//! @brief Creates a temporary file and returns a stream object.
//! @param[in] templateName The filename prefix used to generate a file name
//! with a unique sequence number.
//! @return A stream to the newly created temporary file.
//! @remarks
//! It is up to the caller to dispose of the file after use.
ISeekableStreamUPtr SeekableFileStream::createTempFile(const std::string_view &templateName)
{
    return createTempFile(Fs::Path::getTempDirectory(), templateName);
}

//! @brief Creates a temporary file and returns a stream object.
//! @param[in] tempDir The directory in which to create the temporary file.
//! @param[in] templateName The filename prefix used to generate a file name
//! with a unique sequence number.
//! @return A stream to the newly created temporary file.
//! @remarks
//! It is up to the caller to dispose of the file after use.
ISeekableStreamUPtr SeekableFileStream::createTempFile(const Fs::Path &tempDir,
                                                       const std::string_view &templateName)
{
    Fs::PathBuilder builder(tempDir);
    std::string fileName;

    if (templateName.empty())
        fileName.assign("temp");
    else
        fileName.assign(templateName);

    size_t baseSize = fileName.length();
    FormatInfo sequenceFormat = FormatInfo::getDisplay();
    sequenceFormat.setRequiredSignificantFigures(4);

    constexpr FileAccessBits flags = FileAccess::CreateNew | FileAccess::ReadWrite;
    ISeekableStreamUPtr stream;
    uint32_t sequence = 1;

    do
    {
        // Creates a file name with the latest sequence number.
        appendValue(sequenceFormat, fileName, sequence++);
        fileName.append(".tmp");

        // Add it to the path.
        builder.pushElement(fileName);

        // Try to create the file.
        if (tryOpen(stream, builder, flags) == false)
        {
            // Reset by removing the sequence value text and file name.
            fileName.erase(baseSize, fileName.length() - baseSize);
            builder.popElement();
        }
    } while (!stream);

    return stream;
}

//! @brief Gets the full path to the file being accessed.
const Fs::Path &SeekableFileStream::getPath() const
{
    return _location;
}

// Inherited from IStream.
void SeekableFileStream::flush()
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Flushing to a file which isn't open.");

    FileTraits::flush(_fd);
}

// Inherited from IStream.
size_t SeekableFileStream::read(void *targetBuffer, size_t requiredByteCount)
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Reading from a file which isn't open.");

    FileTraits::ErrorCode errorCode;
    size_t bytesRead = FileTraits::read(_fd, targetBuffer,
                                        requiredByteCount,
                                        errorCode);

    if (errorCode != 0)
    {
        std::string fnName;
        fnName.assign("file.read('");
        appendAgString(fnName, _location.toString(Fs::PathUsage::Kernel));
        fnName.append("', ");
        appendFileSize(FormatInfo::getDisplay(), fnName, requiredByteCount);
        fnName.push_back(')');

        throw FileTraits::createError(fnName, errorCode);
    }

    return bytesRead;
}

// Inherited from IStream.
size_t SeekableFileStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Writing to a file which isn't open.");

    FileTraits::ErrorCode errorCode;
    size_t bytesWritten = FileTraits::write(_fd, sourceBuffer,
                                            sourceByteCount,
                                            errorCode);

    if (errorCode != 0)
    {
        std::string fnName;
        fnName.assign("file.write('");
        appendAgString(fnName, _location.toString(Fs::PathUsage::Kernel));
        fnName.append("', ");
        appendFileSize(FormatInfo::getDisplay(), fnName, sourceByteCount);
        fnName.push_back(')');

        throw FileTraits::createError(fnName, errorCode);
    }

    return bytesWritten;
}

// Inherited from ISeekableStream.
StreamPosition SeekableFileStream::getLength() const
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Cannot query size of a closed file.");

    FileTraits::ErrorCode errorCode = 0;

    StreamPosition size = FileTraits::getSize(_fd, errorCode);

    if (size < 0)
    {
        std::string fnName;
        fnName.assign("file.getLength('");
        appendAgString(fnName, _location.toString(Fs::PathUsage::Kernel));
        fnName.append("')");

        throw FileTraits::createError(fnName, errorCode);
    }

    return size;
}

// Inherited from ISeekableStream.
StreamPosition SeekableFileStream::getPosition() const
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Cannot query position of a closed file.");

    FileTraits::ErrorCode errorCode = 0;
    StreamPosition absPos = FileTraits::tell(_fd, errorCode);

    if (absPos < 0)
    {
        std::string fnName;
        fnName.assign("file.tell('");
        appendAgString(fnName, _location.toString(Fs::PathUsage::Kernel));
        fnName.append("')");

        throw FileTraits::createError(fnName, errorCode);
    }

    return absPos;
}

// Inherited from ISeekableStream.
StreamPosition SeekableFileStream::setPosition(StreamRelative relativeTo, StreamPosition offset)
{
    if (_fd == FileTraits::BadFile)
        throw OperationException("Cannot query position of a closed file.");

    FileTraits::ErrorCode errorCode = 0;
    StreamPosition absPos = FileTraits::seek(_fd, relativeTo, offset, errorCode);

    if (absPos < 0)
    {
        std::string fnName;
        fnName.assign("file.seek('");
        appendAgString(fnName, _location.toString(Fs::PathUsage::Kernel));
        fnName.append("')");

        throw FileTraits::createError(fnName, errorCode);
    }

    return absPos;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

