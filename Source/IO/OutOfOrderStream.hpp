//! @file Ag/IO/OutOfOrderStream.hpp
//! @brief The declaration of an object which allows data to be temporarily
//! written out of order and then transferred to another stream in the
//! correct order.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_OUT_OF_ORDER_STREAM_HPP_
#define HEADER_IO_OUT_OF_ORDER_STREAM_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/ISeekableStream.hpp"
#include "Ag/IO/BufferedOutputStream.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which allows data to be temporarily written out of order
//! and then transferred to another stream in the correct order.
class OutOfOrderStream
{
public:
    // Public Types
    using StreamRegionList = std::list<StreamRegion>;
    using BlockRef = StreamRegionList::iterator;

    //! @brief A stream which keeps track of the bytes it writes.
    class BlockWriterStream : public BufferedOutputStream
    {
    private:
        // Internal Fields
        OutOfOrderStream *_parent;
        BlockRef _block;

    public:
        // Construction/Destruction
        BlockWriterStream(OutOfOrderStream *parent, bool bigBuffer);

        // Accessors
        bool isActive() const;

        // Operations
        StreamLength endWritingBlock(BlockRef startBlock);
        void closeBlock();

        // Overrides
        virtual void flush() override;
        virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
        virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;

        // Ensure the parent can manipulate the child in ways the caller can't.
        friend class OutOfOrderStream;
    };

    using Stream = BlockWriterStream;

    // Construction/Destruction
    OutOfOrderStream();
    ~OutOfOrderStream();

    // Accessors
    BlockRef getEndBlock();
    StreamLength getLength() const;

    // Operations
    BlockWriterStream *beginWritingBlock(BlockRef &block);
    BlockWriterStream *beginWritingBlockBefore(BlockRef block);
    BlockWriterStream *beginWritingBlockBefore(BlockRef block, BlockRef &writingBlock);

    StreamLength orderedWrite(IStream *output);
    StreamLength orderedWrite(IStream *output, BlockRef startBlock, BlockRef endBlock);

private:
    // Internal Functions
    StreamLength innerOrderedWrite(IStream *output, BlockRef startBlock,
                                   BlockRef endBlock, StreamLength maxBlockSize);

    BlockRef accountForWrite(BlockRef block, size_t bytesWritten);
    StreamLength calculateSizeToEnd(BlockRef startBlock) const;
    void checkForUpgrade(size_t bytesToAdd);

    // Internal Fields
    StreamRegionList _orderedBlocks;
    ISeekableStreamUPtr _baseStream;
    BlockWriterStream _currentBlock;
    StreamPosition _writeOffset;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
