//! @file Ag/IO/SeekableFileStream.hpp
//! @brief The declaration of an implementation of ISeekableStream backed by
//! a file on a local file system.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_SEEKABLE_FILE_STREAM_HPP_
#define HEADER_IO_SEEKABLE_FILE_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of ISeekableStream backed by a file on a local
//! file system.
//! @remarks This object closely matches Ag::FileStream, which is needed in
//! the Ag::Core library, but is not seekable.
//! 
//! The SeekableFileStream wraps the lowest-level OS file access primitives. If
//! reading or writing small amounts of data, it would be wise to wrap the
//! stream in something like a BufferedOutputStream to batch low-level read or
//! write operations.
class SeekableFileStream : public ISeekableStream
{
public:
    // Public Types
#ifdef _WIN32
    using FileDescriptor = HANDLE;
#else
    using FileDescriptor = int;
#endif

protected:
    // Construction/Destruction
    SeekableFileStream(const Fs::Path &path, FileDescriptor fd);
public:
    virtual ~SeekableFileStream();
    static ISeekableStreamUPtr open(const Fs::Path &at, FileAccessBits access);
    static bool tryOpen(ISeekableStreamUPtr &stream, const Fs::Path &at,
                        FileAccessBits access);
    static ISeekableStreamUPtr createTempFile(const std::string_view &templateName);
    static ISeekableStreamUPtr createTempFile(const Fs::Path &tempDir,
                                              const std::string_view &templateName);

    // Accessors
    //! @brief Gets the path defining the file the stream accesses.
    const Fs::Path &getPath() const;

    // Inherited from IStream.
    virtual void flush() override;
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

    // Inherited from ISeekableStream
    virtual StreamPosition getLength() const override;
    virtual StreamPosition getPosition() const override;
    virtual StreamPosition setPosition(StreamRelative relativeTo, StreamPosition offset) override;

private:
    // Internal Fields
    Fs::Path _location;
    FileDescriptor _fd;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
