//! @file IO/ISeekableStream.cpp
//! @brief The definition of an interface to an object which represents a
//! stream where the position can be read and set and supporting objects.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <algorithm>

#include <Ag/Core/Exception.hpp>

#include "Ag/IO/ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// StreamRegion Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an initialised stream region.
//! @param[in] offset The offset within the stream of the start of the region,
//! in bytes.
//! @param[in] length The length of the region within the stream, in bytes.
//! @throws Ag::ArgumentException If either @p position or @p length are
//! negative.
StreamRegion::StreamRegion(StreamPosition offset, StreamLength length) :
    _offset(offset),
    _length(length)
{
    if (_offset < 0)
        throw Ag::ArgumentException("A position within a stream must be non-negative.",
                                    "offset");

    if (_length < 0)
        throw Ag::ArgumentException("A stream length must be non-negative.",
                                    "length");
}

//! @brief Creates a sub-region of the current region.
//! @param[in] offset The byte offset into the current region at which to
//! start the sub-region.
//! @return A sub-region from @p offset to the end of the current region.
//! @throws Ag::ArgumentException If @p offset is negative or beyond the end
//! of the current region.
StreamRegion StreamRegion::slice(StreamPosition offset) const
{
    auto end = _offset + _length;

    if (offset < 0)
        throw Ag::ArgumentException("A stream region cannot be sliced with a negative offset."
                                    "offset");

    if (offset > _length)
        throw Ag::ArgumentException("The stream region slice offset is beyond the end of the original region."
                                    "offset");

    auto pos = std::min(offset, _length) + _offset;
    auto length = end - pos;

    return { pos, length };
}

//! @brief Creates a sub-region of the current region.
//! @param[in] offset The byte offset into the current region at which to
//! start the sub-region.
//! @param[in] length The length of the sub-region.
//! @return A new sub-region offset from the start of the current region.
//! @throws Ag::ArgumentException If @p offset is negative or beyond the end
//! of the current region, or @p length is negative or extends beyond the
//! end of the current region.
StreamRegion StreamRegion::slice(StreamPosition offset, StreamLength length) const
{
    auto end = _offset + _length;

    if (offset < 0)
        throw Ag::ArgumentException("A stream region cannot be sliced with a negative offset."
                                    "offset");

    if (length < 0)
        throw Ag::ArgumentException("A stream region length cannot negative." "length");

    if (offset > _length)
        throw Ag::ArgumentException("The stream region slice offset is beyond the end of the original region."
                                    "offset");

    auto rhsEnd = _offset + offset + length;

    if (rhsEnd > end)
        throw Ag::ArgumentException("The end of the stream slice is beyond the end of the original region.",
                                    "length");

    auto pos = std::min(offset, _length) + _offset;
    auto subLength = std::min(_length - offset, length);

    return { pos, subLength };
}

//! @brief Creates a region which encompasses the bytes of the current and
//! another region and any in between.
//! @param[in] rhs The region to combine with the current one.
//! @return The union of the two regions.
StreamRegion StreamRegion::combine(const StreamRegion &rhs) const
{
    auto lhsEnd = _offset + _length;
    auto rhsEnd = rhs._offset + rhs._length;
    auto pos = std::min(_offset, rhs._offset);
    auto length = std::max(lhsEnd, rhsEnd) - pos;

    return { pos, length };
}

//! @brief Creates a version of the region with a restricted length.
//! @param[in] maxLength The maximum length of the resultant region.
//! @return A new region with the same offset, but possibly a shortened length.
StreamRegion StreamRegion::maxLength(StreamLength maxLength) const
{
    return StreamRegion(_offset, std::min(_length, maxLength));
}

//! @brief Tests another region for equality.
//! @param[in] rhs The other region to test.
//! @retval true The @p rhs region had a matching offset and length.
//! @retval false The @p rhs region had at least one differing component.
bool StreamRegion::operator==(const StreamRegion &rhs) const
{
    return (_offset == rhs._offset) && (_length == rhs._length);
}

//! @brief Tests another region for inequality.
//! @param[in] rhs The other region to test.
//! @retval true The @p rhs region had at least one differing component.
//! @retval false The @p rhs region had a matching offset and length.
bool StreamRegion::operator!=(const StreamRegion &rhs) const
{
    return (_offset != rhs._offset) || (_length != rhs._length);
}

////////////////////////////////////////////////////////////////////////////////
// ISeekableStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_UNIQUE_PTR(ISeekableStream);

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

