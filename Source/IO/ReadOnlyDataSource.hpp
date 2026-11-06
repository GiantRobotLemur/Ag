//! @file IO/ReadOnlyDataSource.hpp
//! @brief The declaration of a read-only random-access data source.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_READ_ONLY_DATA_SOURCE_HPP_
#define HEADER_IO_READ_ONLY_DATA_SOURCE_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/ISeekableStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A read-only random-access data source.
class ReadOnlyDataSource
{
public:
    // Public Types
    using UPtr = std::unique_ptr<ReadOnlyDataSource>;

protected:
    // Construction/Destruction
    ReadOnlyDataSource(StreamLength rootExtent);

public:
    virtual ~ReadOnlyDataSource() = default;
    static UPtr create(IStream *inputData, StreamLength byteCount);

    // Accessors
    const StreamRegion &getRootRegion() const;
    bool isRegionValid(const StreamRegion &region) const;

    // Operations
    virtual bool tryReadByte(StreamPosition at, uint8_t &value) = 0;
    virtual bool tryRead(const StreamRegion &region, void *buffer) = 0;
    virtual void readExactly(const StreamRegion &region, void *buffer) = 0;
    virtual ISeekableStreamUPtr readStream(const StreamRegion &region) = 0;

protected:
    // Internal Functions
    void verifyRegion(const StreamRegion &region) const;

private:
    // Internal Fields
    StreamRegion _rootRegion;
};

using ReadOnlyDataSourceUPtr = ReadOnlyDataSource::UPtr;

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
