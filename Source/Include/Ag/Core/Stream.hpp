//! @file Stream.hpp
//! @brief The declaration of a simple interface for reading and writing
//! binary data.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2022-2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_CORE_STREAM_HPP__
#define __AG_CORE_STREAM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include <memory>
#include <optional>

#include "Binary.hpp"
#include "FsPath.hpp"

// A header shared between SymbolPackager and AgCore.
#include "../Private/ByteProducerConsumer.hpp"

namespace Ag {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A simple interface for reading and writing binary data.
class IStream
{
public:
    // Construction/Destruction
    virtual ~IStream() = default;

    // Operations

    //! @brief Executes any outstanding writes which were batched or buffered.
    virtual void flush() = 0;

    //! @brief Reads bytes from the stream.
    //! @param[in] targetBuffer The buffer to receive the bytes read.
    //! @param[in] requiredByteCount The maximum number of bytes to read.
    //! @return The actual number of bytes read.
    //! @throws Ag::Exception If an error occurs during the read.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) = 0;

    //! @brief Writes bytes to the stream.
    //! @param[in] sourceBuffer The bytes to write.
    //! @param[in] sourceByteCount The maximum count of bytes to write.
    //! @return The actual number of bytes written.
    //! @throws Ag::Exception If an error occurs during the write.
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) = 0;
};

//! @brief An object which deletes implementations of IStream as part of a
//! unique_ptr to a stream implementation.
struct IStreamDeleter
{
    void operator()(IStream *stream) const;
};

//! @brief An alias for a unique pointer to a stream.
using IStreamUPtr = std::unique_ptr<IStream, IStreamDeleter>;

//! @brief A simple interface for reading and writing binary data.
class BufferedStream : public IStream
{
public:
    // Construction/Destruction
    BufferedStream(IStream *innerStream, size_t bufferSize);
    virtual ~BufferedStream();

    // Overrides
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;
private:
    // Internal Fields
    static constexpr size_t MinBufferSize = 1024;

    IStream *_innerStream;
    ByteProducerConsumer _buffer;
    std::optional<bool> _isInput;
};

//! @brief An alias for a bit field used to define access to a file.
using FileAccessBits = uint8_t;

//! @brief Defines bit patterns used when opening file streams.
struct FileAccess
{
    static constexpr FileAccessBits Read = 0x01;
    static constexpr FileAccessBits Write = 0x02;
    static constexpr FileAccessBits CreateNew = 0x04;
    static constexpr FileAccessBits CreateAlways = 0x04;
    static constexpr FileAccessBits OpenExisting = 0x08;
};

//! @brief An IStream which represents the contents of a file.
//! @note The implementation of this stream is a raw OS stream interface
//! with no buffering, so each read and write operation corresponds to the
//! appropriate system call. If data is to be read a few bytes at a time,
//! wrapping the object with a BufferedStream will be far better for
//! performance.
class IFileStream : public IStream
{
public:
    // Public Types
    //! @brief An object which can delete an IFileStream implementation as part
    //! of a unique_ptr type.
    struct Deleter
    {
        void operator()(IFileStream *stream) const;
    };

    //! @brief An alias for a unique_ptr to an IFileStream implementation.
    using UPtr = std::unique_ptr<IFileStream, Deleter>;

    // Construction/Destruction
    static UPtr open(const Fs::Path &at, FileAccessBits access);
    static bool tryOpen(UPtr &stream, const Fs::Path &at, FileAccessBits access);
    virtual ~IFileStream() = default;

    // Accessors
    //! @brief Gets the path defining the file the stream accesses.
    virtual const Fs::Path &getPath() const =0;

    // Operations
    static void readWholeFile(const Fs::Path &fileName, ByteBlock &fileData);

    // Overrides
    virtual void flush() = 0;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) = 0;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) = 0;
};

//! @brief An alias for a unique_ptr to an IFileStream implementation.
using IFileStreamUPtr = IFileStream::UPtr;

// An opaque type which prevents the need for including the bzlib header
// allowing the library to remain private.
class AgBz2Context;

//! @brief A stream which compresses data before writing it to a nested stream.
class Bz2CompressionStream : public IStream
{
public:
    // Public Constants
    static constexpr size_t WorkspaceSize = 192;
    static constexpr size_t WorkspaceWordCount = (WorkspaceSize + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);

    // Construction/Destruction
    Bz2CompressionStream(IStream *outputStream,
                         size_t bufferSize = 256,
                         int compressionLevel = 9,
                         int verbosity = 0,
                         int workFactor = 30);
    virtual ~Bz2CompressionStream();

    // Operations
    void close();
    void disableExceptions();

    // Overrides
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;
private:
    // Internal Fields
    AgBz2Context *_context;

    // Create the block using machine words to ensure it is word-aligned.
    uintptr_t _workspace[WorkspaceWordCount];
};

//! @brief A stream which decompresses data read from a nested stream.
class Bz2DecompressionStream : public IStream
{
public:
    // Construction/Destruction
    Bz2DecompressionStream(IStream *inputStream,
                           size_t bufferSize = 256,
                           int verbosity = 0);
    virtual ~Bz2DecompressionStream();

    // Accessors
    void setReadLimit(int64_t maxBytesToRead);

    // Operations
    void close();
    void disableExceptions();

    // Overrides
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

private:
    // Internal Functions
    bool tryFillInputBuffer();

    // Internal Fields
    AgBz2Context *_context;
    ByteProducerConsumer _compressedData;
    IStream *_innerStream;
    int64_t _maxBytesToRead;
    int64_t _compressedBytesRead;

    // Create the block using machine words to ensure it is word-aligned.
    uintptr_t _workspace[Bz2CompressionStream::WorkspaceWordCount];
};

} // namespace Ag

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
