//! @file Core/Stream.cpp
//! @brief The definition of a simple interface for reading and writing
//! binary data.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2021-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "CoreInternal.hpp"
#include "Ag/Core/Binary.hpp"
#include "Ag/Core/CollectionTools.hpp"
#include "Ag/Core/Format.hpp"
#include "Ag/Core/FsDirectory.hpp"
#include "Ag/Core/InlineMemory.hpp"
#include "Ag/Core/Stream.hpp"
#include "Ag/Core/Utils.hpp"

// A header shared between SymbolPackager and AgCore.
#include "Ag/Private/Bz2Stream.hpp"

namespace Ag {

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

    static bool tryOpen(const Fs::Path &path, FileAccessBits access,
                        FileDescriptor &fd, uintptr_t &errorCode)
    {
        std::wstring filename = path.toWideString(Fs::PathUsage::Kernel);

        DWORD handleAccess = 0;
        DWORD shareMode = FILE_SHARE_READ;
        DWORD createMode = 0;

        if (access & FileAccess::Read)
        {
            handleAccess = GENERIC_READ;
        }

        if (access & FileAccess::Write)
        {
            handleAccess = GENERIC_WRITE;
        }

        if (access & FileAccess::CreateAlways)
        {
            createMode = CREATE_ALWAYS;
        }
        else if (access & FileAccess::CreateNew)
        {
            createMode = CREATE_NEW;
        }
        else if (access & FileAccess::OpenExisting)
        {
            createMode = OPEN_EXISTING;
        }
        else
        {
            createMode = OPEN_ALWAYS;
        }

        fd = ::CreateFileW(filename.c_str(), handleAccess,
                           shareMode, nullptr, createMode,
                           0, nullptr);

        errorCode = ::GetLastError();

        return fd != INVALID_HANDLE_VALUE;
    }

    static FileDescriptor open(const Fs::Path &path, FileAccessBits access)
    {
        uintptr_t errorCode;
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

    static bool tryOpen(const Fs::Path &path, FileAccessBits access,
                        FileDescriptor &fd, uintptr_t &errorCode)
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
#endif

//! @brief A concrete implementation of IFileStream.
class FileStream : public IFileStream
{
private:
    // Internal Fields
    Fs::Path _location;
    FileTraits::FileDescriptor _fd;

public:
    // Construction/Destruction
    FileStream(const Fs::Path &path, FileTraits::FileDescriptor fd) :
        _location(path),
        _fd(fd)
    {
    }

    virtual ~FileStream()
    {
        FileTraits::close(_fd);
        _fd = FileTraits::BadFile;
    }

    // Inherited from IStream.
    virtual void flush() override
    {
        if (_fd == FileTraits::BadFile)
        {
            throw OperationException("Flushing to a file which isn't open.");
        }

        FileTraits::flush(_fd);
    }

    // Inherited from IStream.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override
    {
        if (_fd == FileTraits::BadFile)
        {
            throw OperationException("Reading from a file which isn't open.");
        }

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
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override
    {
        if (_fd == FileTraits::BadFile)
        {
            throw OperationException("Writing to a file which isn't open.");
        }

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

    // Inherited from IFileStream.
    virtual const Fs::Path &getPath() const { return _location; }
};

//! @brief An exception thrown as a result of a bz2 library error code.
class Bz2Exception : public Exception
{
public:
    Bz2Exception(const char *fnName, int errorCode)
    {
        // Create a static mapping of error messages.
        using ErrorMessageMap = StaticMap<int, std::string_view>;

        static ErrorMessageMap::MappingType messages[] = {
            { BZ_SEQUENCE_ERROR, "The sequence of commands was invalid (BZ_SEQUENCE_ERROR)." },
            { BZ_MEM_ERROR, "Insufficient memory is available (BZ_MEM_ERROR)" },
            { BZ_DATA_ERROR, "A data integrity error is detected in the compressed stream (BZ_DATA_ERROR)." },
            { BZ_DATA_ERROR_MAGIC, "The compressed stream doesn't begin with the right magic bytes, (BZ_DATA_ERROR_MAGIC)." },
            { BZ_IO_ERROR, "There is an error reading from/writing to the compressed file (BZ_IO_ERROR)." },
            { BZ_UNEXPECTED_EOF, "The compressed file ended before the logical end-of-stream was detected (BZ_UNEXPECTED_EOF)." },
            { BZ_OUTBUFF_FULL, "The output data will not fit into the output buffer provided (BZ_OUTBUFF_FULL)." },
            { BZ_CONFIG_ERROR, "The bz2 library has been mis-compiled (BZ_CONFIG_ERROR)." },
        };

        ErrorMessageMap errorMessages(messages);
        std::string_view detail;
        size_t index;

        if (errorMessages.tryFindValue(errorCode, index))
        {
            detail = errorMessages.getValue(index);
        }
        else
        {
            detail = "Unknown bz2 error code.";
        }

        std::string message;
        message.assign("A call to the bz2 compression library function ");
        message.append(fnName);
        message.append(" returned an expected result.");

        initialise("Bz2Exception", message, detail, static_cast<uintptr_t>(errorCode));
    }
};

} // Anonymous namespace

//! @brief An implementation of Bz2Context which uses the Ag exception mechanism.
class AgBz2Context : public Bz2Context
{
private:
    IStream *_innerStream;
    bool _exceptionsEnabled;
    bool _hasError;
public:
    // Construction/Destruction
    AgBz2Context(IStream *innerStream) :
        _innerStream(innerStream),
        _exceptionsEnabled(true),
        _hasError(false)
    {
    }

    virtual ~AgBz2Context() = default;

    static AgBz2Context *createInPlace(IStream *innerStream,
                                       void *block, size_t blockSize)
    {
        if (blockSize < sizeof(AgBz2Context))
        {
            throw OperationException("The block provided was too small to "
                                     "create a bz2 compression context in.");
        }

        return new(block) AgBz2Context(innerStream);
    }

    static void destroyInPlace(void *block)
    {
        AgBz2Context *instance = reinterpret_cast<AgBz2Context *>(block);

        instance->~AgBz2Context();
    }

    // Accessors
    void disableExceptions()
    {
        _exceptionsEnabled = false;
    }

    // Overrides
    virtual void onBz2Error(const char *bz2Fn, int errorCode) override
    {
        _hasError = true;

        if (_exceptionsEnabled)
            throw Bz2Exception(bz2Fn, errorCode);
    }

    virtual void onInvalidState(State /*preferredState*/) override
    {
        _hasError = true;

        if (_exceptionsEnabled)
        {
            throw OperationException("The bz2 compression context was in an "
                                     "unexpected state for the operation requested.");
        }
    }

    virtual void onBytesCompressed(const uint8_t *compressedBytes,
                                   size_t byteCount) override
    {
        if (_innerStream != nullptr)
        {
            _innerStream->write(compressedBytes, byteCount);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////
// IStreamDeleter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Deletes an IStream implementation embedded in an IStreamUPtr.
//! @param[in] stream The implementation to delete.
void IStreamDeleter::operator()(IStream *stream) const
{
    safeDelete(stream);
}

////////////////////////////////////////////////////////////////////////////////
// BufferedStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
BufferedStream::BufferedStream(IStream *innerStream, size_t bufferSize) :
    _innerStream(innerStream),
    _buffer(bufferSize)
{
}

BufferedStream::~BufferedStream()
{
    if ((_isInput.value_or(true) == false) && _buffer.canProduce())
    {
        flush();
    }
}

void BufferedStream::flush()
{
    if (_isInput.value_or(true))
        return;

    while (_buffer.canProduce())
    {
        size_t bufferSize;
        auto bufferData = _buffer.lockProduceable(bufferSize);

        size_t bytesWritten = _innerStream->write(bufferData, bufferSize);

        _buffer.unlockProduceable(bytesWritten);
    }
}

size_t BufferedStream::read(void *targetBuffer, size_t requiredByteCount)
{
    if (_isInput.value_or(true) == false)
        throw NotSupportedException("An output buffered stream does not support read operations.");

    // If we get here, this is now an input stream.
    _isInput = true;

    size_t bytesRead = 0;
    uint8_ptr_t dest = reinterpret_cast<uint8_ptr_t>(targetBuffer);

    while (bytesRead < requiredByteCount)
    {
        size_t requiredBytesLeft = requiredByteCount - bytesRead;

        if (_buffer.canProduce())
        {
            // Copy bytes from the buffer.
            size_t maxBytesToCopy;
            auto bufferedBytes = _buffer.getConsumable(maxBytesToCopy);
            size_t bytesToCopy = std::min(maxBytesToCopy, requiredBytesLeft - bytesRead);

            memcpy(dest + bytesRead, bufferedBytes, bytesToCopy);
            _buffer.consume(bytesToCopy);

            bytesRead += bytesToCopy;
        }
        // There is no data in the buffer.
        else if (requiredBytesLeft > std::min(_buffer.getSize(), MinBufferSize))
        {
            // Read the data directly to the output buffer.
            size_t directBytesRead = _innerStream->read(dest + bytesRead,
                                                        requiredBytesLeft);

            // Given we are by-passing the cache, we should have read all we
            // needed 
            bytesRead += directBytesRead;
            break;
        }
        else if (_buffer.canConsume())
        {
            // The buffer is empty, re-fill it.
            size_t maxBufferedBytes;
            auto buffer = _buffer.lockProduceable(maxBufferedBytes);

            size_t newBufferedBytes = _innerStream->read(buffer, maxBufferedBytes);
            _buffer.unlockProduceable(newBufferedBytes);

            // If nothing more could be read, stop trying.
            if (newBufferedBytes == 0)
                break;
        }
    }

    return bytesRead;
}

size_t BufferedStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    if (_isInput.value_or(false))
        throw NotSupportedException("An input buffered stream does not support write operations.");

    // If we get this far, this is now an output stream.
    _isInput = false;

    uint8_cptr_t source = reinterpret_cast<uint8_cptr_t>(sourceBuffer);
    size_t bytesWritten = 0;

    while (bytesWritten < sourceByteCount)
    {
        size_t bytesLeftToWrite = sourceByteCount - bytesWritten;
        size_t blockWritten = 0;

        if (_buffer.isEmpty() &&
            (bytesLeftToWrite > std::min(_buffer.getSize(), MinBufferSize)))
        {
            // Try a direct write.
            blockWritten = _innerStream->write(source + bytesWritten,
                                                   bytesLeftToWrite);
        }
        else if (_buffer.canConsume())
        {
            // Writes what we can to the buffer.
            size_t bufferFree;
            auto buffer = _buffer.lockProduceable(bufferFree);

            blockWritten = std::min(bufferFree, bytesLeftToWrite);
            memcpy(buffer, source + bytesWritten, blockWritten);
            _buffer.unlockProduceable(blockWritten);
        }
        else if (_buffer.canProduce())
        {
            size_t bytesToWrite;
            auto buffer = _buffer.getConsumable(bytesToWrite);

            blockWritten = _innerStream->write(buffer, bytesToWrite);
            _buffer.consume(blockWritten);
        }

        bytesWritten += blockWritten;

        // If we couldn't output or consume any more bytes, stop trying.
        if (blockWritten == 0)
            break;
    }

    return bytesWritten;
}

////////////////////////////////////////////////////////////////////////////////
// IFileStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Deletes an IFileStream implementation embedded in an IFileStreamUPtr.
//! @param[in] stream The implementation to delete.
void IFileStream::Deleter::operator()(IFileStream *stream) const
{
    safeDelete(stream);
}

//! @brief Creates a new instance of an IFileStream by opening a file.
//! @param[in] at The location of the file to open.
//! @param[in] access A flags field defined by FileAccess specifying how the file
//! should be opened and managed.
//! @return A unique pointer to an implementation of IFileStream which can be
//! used to access the named file.
IFileStream::UPtr IFileStream::open(const Fs::Path &at, FileAccessBits access)
{
    // Create an absolute path from the outset.
    Fs::Path fullPath = at.convertToAbsolute();

    FileTraits::FileDescriptor fd = FileTraits::open(fullPath, access);

    return IFileStream::UPtr(new FileStream(fullPath, fd));
}

//! @brief Attempts to create a new instance of an IFileStream by opening a file.
//! @param[out] stream Receives the newly created stream, or is reset to an empty state.
//! @param[in] at The location of the file to open.
//! @param[in] access A flags field defined by FileAccess specifying how the file
//! should be opened and managed.
//! @retval true The file was successfully opened, @p stream has received a valid value.
//! @retval false The operation failed, @p stream is set to an empty state.
bool IFileStream::tryOpen(UPtr &stream, const Fs::Path &at, FileAccessBits access)
{
    // Ensure the stream is in an empty state should we fail.
    stream.reset();

    // Create an absolute path from the outset.
    Fs::Path fullPath = at.convertToAbsolute();
    uintptr_t errorCode;
    FileTraits::FileDescriptor fd;

    if (FileTraits::tryOpen(fullPath, access, fd, errorCode))
    {
        stream.reset(new FileStream(fullPath, fd));
        return true;
    }

    return false;
}

//! @brief Reads the entire contents of a file.
//! @param[in] fileName The path to the file to read.
//! @param[out] fileData Receives the data read from the file.
//! @throws OperationException If the file is larger than 256 MB.
//! @throws Fs::FileNotFoundException If the file cannot be read.
void IFileStream::readWholeFile(const Fs::Path &fileName, ByteBlock &fileData)
{
    fileData.clear();

    Fs::Entry fileInfo(fileName);

    if (fileInfo.exists() == false)
    {
        throw Fs::FileNotFoundException(fileInfo.getPath());
    }

    int64_t size = fileInfo.getSize();

    // Set sensible a maximum size of 256 MB.
    static constexpr int64_t MaxSize = static_cast<int64_t>(256) << 20;

   if ((size < 0) || (size > MaxSize))
    {
        std::string message;
        message.assign("File '");
        appendAgString(message, fileInfo.getPath().toString(Fs::PathUsage::Display));
        message.append("' too large to read into memory all at once.");

        throw OperationException(std::string_view(message));
    }

   fileData.resize(static_cast<size_t>(size));

   FileTraits::FileDescriptor fd = FileTraits::open(fileInfo.getPath(),
                                                    FileAccess::OpenExisting | FileAccess::Read);
   FileStream stream(fileInfo.getPath(), fd);

   size_t actualSize = stream.read(fileData.data(), fileData.size());
   fileData.resize(actualSize);
}

////////////////////////////////////////////////////////////////////////////////
// Bz2CompressionStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
Bz2CompressionStream::Bz2CompressionStream(IStream *outputStream,
                                           size_t bufferSize /*= 256*/,
                                           int compressionLevel /*= 9*/,
                                           int verbosity /*= 0*/,
                                           int workFactor /*= 30*/) :
    _context(nullptr)
{
    // Ensure there is enough space for the obfuscated Bz2 context and buffers.
    static_assert(WorkspaceSize >= sizeof(AgBz2Context),
                  "Not enough space for a bz2 compression context, increase BzCompressionStream::WorkspaceSize.");

    // Ensure the workspace buffer is cleared.
    zeroFill(_workspace);

    // Create the context in a single inline block to avoid additional memory
    // memory allocation, but keeping the bz2 library private.
    _context = AgBz2Context::createInPlace(outputStream, _workspace,
                                           sizeof(_workspace));

    _context->initialiseCompression(bufferSize, compressionLevel, verbosity, workFactor);
}

Bz2CompressionStream::~Bz2CompressionStream()
{
    if (_context != nullptr)
    {
        _context->finishCompression();

        _context = nullptr;
        AgBz2Context::destroyInPlace(_workspace);
    }
}

void Bz2CompressionStream::disableExceptions()
{
    _context->disableExceptions();
}

void Bz2CompressionStream::flush()
{
}

size_t Bz2CompressionStream::read(void */*targetBuffer*/, size_t /*requiredByteCount*/)
{
    throw NotSupportedException("Reading for a compression writer stream.");
}

size_t Bz2CompressionStream::write(const void *sourceBuffer, size_t sourceByteCount)
{
    size_t bytesWritten = 0;

    if (_context != nullptr)
    {
        bytesWritten = _context->compress(sourceBuffer, sourceByteCount);
    }

    return bytesWritten;
}

////////////////////////////////////////////////////////////////////////////////
// Bz2DecompressionStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
Bz2DecompressionStream::Bz2DecompressionStream(IStream *inputStream,
                                               size_t bufferSize,
                                               int verbosity) :
    _context(nullptr),
    _compressedData(bufferSize),
    _innerStream(inputStream),
    _maxBytesToRead(-1),
    _compressedBytesRead(0)
{
    // Ensure the workspace buffer is cleared.
    zeroFill(_workspace);

    // Create the context in a single inline block to avoid additional memory
    // memory allocation, but keeping the bz2 library private.
    _context = AgBz2Context::createInPlace(nullptr, _workspace,
                                           sizeof(_workspace));

    _context->initialiseDecompression(verbosity, false, bufferSize);
}

Bz2DecompressionStream::~Bz2DecompressionStream()
{
    if (_context != nullptr)
    {
        _context->finishDecompression();
        _context = nullptr;

        AgBz2Context::destroyInPlace(_workspace);
    }
}

void Bz2DecompressionStream::setReadLimit(int64_t maxBytesToRead)
{
    _maxBytesToRead = maxBytesToRead;
    _compressedBytesRead = 0;
}

void Bz2DecompressionStream::disableExceptions()
{
    _context->disableExceptions();
}

void Bz2DecompressionStream::flush()
{
}

size_t Bz2DecompressionStream::read(void *targetBuffer, size_t requiredByteCount)
{
    AgBz2Context *context = reinterpret_cast<AgBz2Context *>(_workspace);

    size_t bytesRead = 0;
    uint8_t *dest = reinterpret_cast<uint8_t *>(targetBuffer);
    auto &outputBuffer = context->getDecompressionBuffer();

    while (bytesRead < requiredByteCount)
    {
        size_t bytesLeft = requiredByteCount - bytesRead;

        if (outputBuffer.canProduce())
        {
            // Use up any buffered decompressed data first.
            bytesRead += outputBuffer.produce(dest + bytesRead, bytesLeft);
        }
        else if (_compressedData.canProduce() || tryFillInputBuffer())
        {
            // Try to decompress some more bytes into the internal buffer
            // so that we can read them on the next iteration.
            size_t maxCompressable;
            auto compressedBytes = _compressedData.getConsumable(maxCompressable);

            size_t compressedBytesUsed =
                context->decompress(compressedBytes, maxCompressable);

            _compressedData.consume(compressedBytesUsed);
        }
        else if (context->finishDecompression())
        {
            // If there is no more compressed data to read,
            // return with the bytes we have.
            break;
        }
    }

    return bytesRead;


    //uint8_ptr_t dest = reinterpret_cast<uint8_ptr_t>(targetBuffer);
    //auto &decompressionBuffer = context->getDecompressionBuffer();
    //size_t bytesWritten = 0;

    //while (bytesWritten < requiredByteCount)
    //{
    //    // Try to satisfy the read from the output buffer.
    //    size_t bytesCopied = context->readBufferedData(dest + bytesWritten,
    //                                                   requiredByteCount - bytesWritten);

    //    if (bytesCopied > 0)
    //    {
    //        // We grabbed some already decompressed data from the buffer.
    //        bytesWritten += bytesCopied;
    //    }
    //    else if ((_bufferedCompressedBytes > 0) || tryRefillCompressedBuffer())
    //    {
    //        // Read some more decompress some more data from the input buffer.
    //        size_t compressedBytesRead = context->decompress(_compressedBuffer.data(),
    //                                                         _bufferedCompressedBytes);

    //        if (compressedBytesRead < _bufferedCompressedBytes)
    //        {
    //            if (compressedBytesRead > 0)
    //            {
    //                // Shuffle the input buffer down.
    //                memmove(_compressedBuffer.data(),
    //                        _compressedBuffer.data() + compressedBytesRead,
    //                        _bufferedCompressedBytes - compressedBytesRead);

    //                _bufferedCompressedBytes -= compressedBytesRead;
    //            }
    //            else
    //            {
    //                // The compression algorithm doesn't want more bytes,
    //                // it needs to output decompressed data before it can
    //                // take more.
    //                break;
    //            }
    //        }
    //        else
    //        {
    //            // The input buffer was completely drained.
    //            _bufferedCompressedBytes = 0;
    //        }
    //    }
    //    else if (context->finishDecompression())
    //    {
    //        // There is nothing more we can do?
    //        break;
    //    }
    //}

    //return bytesWritten;
}

size_t Bz2DecompressionStream::write(const void */*sourceBuffer*/, size_t /*sourceByteCount*/)
{
    throw NotSupportedException("Writing to a decompression stream.");
}

bool Bz2DecompressionStream::tryFillInputBuffer()
{
    //size_t bytesRead = 0;

    //if (_bufferedCompressedBytes < _compressedBuffer.size())
    //{
    //    size_t maxBytesToRead = _compressedBuffer.size() - _bufferedCompressedBytes;

    //    // Apply the compressed data read limit.
    //    if (_maxBytesToRead > 0)
    //    {
    //        size_t readLimit = static_cast<size_t>(std::min(static_cast<uint64_t>(_maxBytesToRead - _compressedBytesRead),
    //                                                        static_cast<uint64_t>(SIZE_MAX)));

    //        maxBytesToRead = std::min(maxBytesToRead, readLimit);
    //    }

    //    if (maxBytesToRead > 0)
    //    {
    //        bytesRead = _innerStream->read(_compressedBuffer.data() + _bufferedCompressedBytes,
    //                                       maxBytesToRead);
    //        _bufferedCompressedBytes += bytesRead;

    //        _compressedBytesRead += static_cast<int64_t>(bytesRead);
    //    }
    //}

    //return bytesRead > 0;


    if (_compressedData.canConsume() == false)
        return false;

    size_t maxCompressedBytes;
    void *buffer = _compressedData.lockProduceable(maxCompressedBytes);

    size_t compressedBytesRead = _innerStream->read(buffer, maxCompressedBytes);
    _compressedData.unlockProduceable(compressedBytesRead);

    return compressedBytesRead > 0;
}


} // namespace Ag
////////////////////////////////////////////////////////////////////////////////

