//! @file Ag/IO/ISeekableStream.hpp
//! @brief The declaration of an interface to an object which represents a
//! stream where the position can be read and set and supporting objects.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_ISEEKABLE_STREAM_HPP_
#define HEADER_IO_ISEEKABLE_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>

#include "Ag/Core/Stream.hpp"

namespace Ag {

//! @brief A namespace which contains tools for manipulating and managing input
//! and output to devices and files.
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An alias for an integer representing an offset within a stream.
using StreamPosition = int64_t;

//! @brief An alias for an integer representing a count of bytes in  a stream.
using StreamLength = StreamPosition;

//! @brief Expresses a known position within a stream to specify a position.
enum class StreamRelative
{
    //! @brief Positions are specified as a positive offset from the beginning
    //! of the stream.
    Beginning,

    //! @brief Positions are specified as any offset relative to the current
    //! stream position.
    Current,

    //! @brief Positions are specified as a negative offset from the end of
    //! the stream.
    End,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object representing a run of bytes within a stream.
class StreamRegion
{
private:
    // Internal Fields
    StreamPosition _offset;
    StreamLength _length;

public:
    // Construction/Destruction
    constexpr StreamRegion() noexcept : _offset(0), _length(0) {}
    StreamRegion(StreamPosition offset, StreamLength length);
    ~StreamRegion() = default;

    // Accessors

    //! @brief Gets the offset into the stream of the beginning of the region,
    //! in bytes.
    //! @remarks This value will always be non-negative.
    constexpr StreamPosition getOffset() const noexcept { return _offset; }

    //! @brief Gets the length of the region, in bytes.
    constexpr StreamLength getLength() const noexcept { return _length; }

    //! @brief Gets the offset into the stream of the byte just after the end
    //! of the region, in bytes.
    constexpr StreamPosition getEnd() const noexcept { return _offset + _length; }

    // Operations
    StreamRegion slice(StreamPosition offset) const;
    StreamRegion slice(StreamPosition offset, StreamLength length) const;
    StreamRegion combine(const StreamRegion &rhs) const;
    StreamRegion maxLength(StreamLength maxLength) const;

    bool operator==(const StreamRegion &rhs) const;
    bool operator!=(const StreamRegion &rhs) const;
};

//! @brief An extension to the IStream interface which allows for a read/write
//! position which can be read and written.
class ISeekableStream : public IStream
{
protected:
    // Construction/Destruction
    ISeekableStream() = default;
public:
    virtual ~ISeekableStream() = default;

    // Accessors

    //! @brief Gets the total length of the stream.
    //! @return The total length of the stream, in bytes, or a negative value
    //! if the stream length is unknown or meaningless.
    virtual StreamPosition getLength() const = 0;

    // Operations

    //! @brief Gets the current read/write position of the stream.
    //! @return The offset in bytes from the beginning of the stream at which
    //! the next bytes will be read or written.
    virtual StreamPosition getPosition() const = 0;

    //! @brief Sets the current read/write position of the stream.
    //! @param[in] relativeTo Specifies what the position will be set relative to.
    //! @param[in] offset The offset which, when coupled with @p relativeTo, is
    //! used to define the desired position.
    //! @return The resultant position of the next read/write operation, in bytes
    //! relative to the beginning of the stream.
    virtual StreamPosition setPosition(StreamRelative relativeTo,
                                       StreamPosition offset) = 0;
};

DECLARE_UNIQUE_PTR(ISeekableStream);

////////////////////////////////////////////////////////////////////////////////
// Global Functions
////////////////////////////////////////////////////////////////////////////////
bool isStreamSizeTooLargeForMemory(StreamLength streamSize);
size_t streamToMemorySize(StreamLength streamSize, bool throwOnFailure = true);
StreamLength memoryToStreamSize(size_t memorySize);

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
