//! @file IO/OutOfOrderStream.cpp
//! @brief The definition of an object which allows data to be temporarily
//! written out of order and then transferred to another stream in the
//! correct order.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/MemoryStream.hpp"
#include "Ag/IO/SeekableFileStream.hpp"
#include "Ag/IO/StreamTools.hpp"

#include "OutOfOrderStream.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
//! @brief The threshold beyond which data should be backed by a file rather
//! than an in-memory buffer.
constexpr StreamLength MaxMemoryStreamSize = 4 * 1024 * 1024;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// OutOfOrderStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a stream which will batch writes to an underlying stream
//! and keep track of how many bytes were written where.
//! @param[in] parent The OutOfOrderStream this stream serves.
//! @param[in] bigBuffer True to use the maximum size of buffer.
OutOfOrderStream::BlockWriterStream::BlockWriterStream(OutOfOrderStream *parent,
                                                       bool bigBuffer) :
    BufferedOutputStream(parent->_baseStream.get(),
                         bigBuffer ? MaxBufferSize : MinBufferSize),
    _parent(parent),
    _block(parent->_orderedBlocks.end())
{
}

//! @brief Determines whether the stream is set to write to an active block.
//! @retval true The stream is writing to an active block and recording the
//! bytes written.
//! @retval false The stream is not currently associated with a block.
bool OutOfOrderStream::BlockWriterStream::isActive() const
{
    return _block != _parent->_orderedBlocks.end();
}

//! @brief Finishes writing the current block, flushing any cached data to the
//! underlying stream and updating block statistics.
//! @throws OperationException If the stream is not currently associated with
//! an active block.
StreamLength OutOfOrderStream::BlockWriterStream::endWritingBlock(BlockRef startBlock)
{
    // Calculate the size of the run of blocks.
    StreamLength blockSize = _parent->calculateSizeToEnd(startBlock);

    // Deactivate the writer.
    closeBlock();

    return blockSize;
}

//! @brief Ensures the next bytes start a new block in terms of ordering of the
//! output stream.
void OutOfOrderStream::BlockWriterStream::closeBlock()
{
    _block = _parent->_orderedBlocks.end();
}

// Inherited from IStream.
void OutOfOrderStream::BlockWriterStream::flush()
{
    // Ensure all buffered bytes are written to the underlying stream.
    BufferedOutputStream::flush();
}

// Inherited from IStream.
size_t OutOfOrderStream::BlockWriterStream::read(void */*targetBuffer*/,
                                                 size_t /*requiredByteCount*/)
{
    throw NotSupportedException("An out-of-order block cannot be read from.");
}

// Inherited from IStream.
size_t OutOfOrderStream::BlockWriterStream::write(const void *sourceBuffer,
                                                  size_t sourceByteCount)
{
    // Assess whether the underlying stream needs to be "upgraded" from a
    // memory buffer to a temporary file.
    _parent->checkForUpgrade(sourceByteCount);

    size_t bytesWritten = BufferedOutputStream::write(sourceBuffer, sourceByteCount);

    // Keep track of the write position in parallel with the underlying stream.
    _block = _parent->accountForWrite(_block, bytesWritten);

    return bytesWritten;
}

//! @brief Constructs an object to accumulate data out of order before writing
//! it to another stream in the correct order.
OutOfOrderStream::OutOfOrderStream() :
    _baseStream(new MemoryStream()),
    _currentBlock(this, /* bigBufferSize = */ false),
    _writeOffset(0)
{
}

//! @brief Ensures that any temporary file is closed and deleted.
OutOfOrderStream::~OutOfOrderStream()
{
    _currentBlock.flush();

    auto fileStream = dynamic_cast<SeekableFileStream *>(_baseStream.get());

    if (fileStream != nullptr)
    {
        // We need to dispose of the temporary file.
        Fs::Path tempFilePath = fileStream->getPath();

        // Close the stream before we delete the file.
        _baseStream.reset();

        Fs::Entry fileEntry(tempFilePath);
        fileEntry.remove(/* reportError = */ false);
    }
}

//! @brief Gets the block after the last one in the ordered sequence.
OutOfOrderStream::BlockRef OutOfOrderStream::getEndBlock()
{
    return _orderedBlocks.end();
}

//! @brief Gets the total amount of data written to the stream, in bytes.
StreamLength OutOfOrderStream::getLength() const
{
    // Sum the sizes of all the outstanding blocks and
    // any buffered data.
    StreamLength length = 0;

    for (const StreamRegion &region : _orderedBlocks)
        length += region.getLength();

    return length;
}

//! @brief Begins writing a block of data.
//! @param[out] block Receives a reference to the block being written, which
//! can be used to order other blocks before it.
//! @return A pointer to an IStream implementation which will allow block data
//! to be accumulated.
OutOfOrderStream::Stream *OutOfOrderStream::beginWritingBlock(
    OutOfOrderStream::BlockRef &block)
{
    StreamRegion lastBlock(_writeOffset, 0);
    block = _orderedBlocks.insert(_orderedBlocks.end(), lastBlock);

    // Have the block update the region we just created.
    _currentBlock._block = block;

    // Return the stream we own.
    return &_currentBlock;
}

//! @brief Begins writing a block of data which should appear before another
//! block in the ordered output.
//! @param[in] block The block the new block should appear before.
//! @return A pointer to an IStream implementation which will allow block data
//! to be accumulated.
OutOfOrderStream::Stream *OutOfOrderStream::beginWritingBlockBefore(BlockRef block)
{
    BlockRef writingBlock;

    return beginWritingBlockBefore(block, writingBlock);
}

//! @brief Begins writing a block of data which should appear before another
//! block in the ordered output.
//! @param[in] block The block the new block should appear before.
//! @param[in] writingBlock A reference to the first block the stream will write.
//! @return A pointer to an IStream implementation which will allow block data
//! to be accumulated.
OutOfOrderStream::Stream *OutOfOrderStream::beginWritingBlockBefore(BlockRef block,
                                                                    BlockRef &writingBlock)
{
    if (_currentBlock.isActive())
        throw OperationException("Cannot start writing an out-of-order block "
                                 "while another is being written.");

    // Create a region for bytes written to the end of the underlying stream.
    StreamRegion lastBlock(_writeOffset, 0);

    // But ensure the data ends up being written before another block
    // in the finally ordered stream.
    writingBlock = _orderedBlocks.insert(block, lastBlock);

    // Have the block update the region we just created.
    _currentBlock._block = writingBlock;

    // Return the stream we own.
    return &_currentBlock;
}

//! @brief Writes the entire contents of the stream to an output stream in
//! the correct order.
//! @param[in] output The output stream to write to.
//! @returns The count of bytes written to @p output.
StreamLength OutOfOrderStream::orderedWrite(IStream *output)
{
    return orderedWrite(output, _orderedBlocks.begin(), _orderedBlocks.end());
}

//! @brief Writes the entire contents of the stream to an output stream in
//! the correct order.
//! @param[in] output The output stream to write to.
//! @param[in] startBlock The reference to the first block in the run to write.
//! @param[in] endBlock The reference to the block after the last one to write.
//! @returns The count of bytes written to @p output.
StreamLength OutOfOrderStream::orderedWrite(IStream *output, BlockRef startBlock,
                                            BlockRef endBlock)
{
    if (_currentBlock.isActive())
        throw OperationException("Cannot transfer the unordered data while it "
                                 "is still in the process of being written.");

    // Ensure all cached data is pushed to the underlying stream.
    _currentBlock.flush();

    StreamLength largestBlock = 0;

    auto blockPos = startBlock;

    for (; (blockPos != endBlock) && (blockPos != _orderedBlocks.end()); ++blockPos)
        largestBlock = std::max(largestBlock, blockPos->getLength());

    if (blockPos != endBlock)
        throw ArgumentException("The specified end block does not appear after "
                                "the specified start block.", "endBlock");

    if (largestBlock <= 0)
        return 0;

    if (output->isBuffered())
    {
        return innerOrderedWrite(output, startBlock, endBlock, largestBlock);
    }
    else
    {
        // Write using buffered output for efficiency.
        size_t bufferSize = static_cast<size_t>(std::min(largestBlock,
                                                         static_cast<StreamLength>(SIZE_MAX)));

        BufferedOutputStream bufferedOutput(output, bufferSize);

        return innerOrderedWrite(&bufferedOutput, startBlock, endBlock, largestBlock);
    }
}

//! @brief Writes the entire contents of the stream to an output stream in
//! the correct order.
//! @param[in] output A buffered output stream to write to.
//! @param[in] startBlock The reference to the first block in the run to write.
//! @param[in] endBlock The reference to the block after the last one to write.
//! @returns The count of bytes written to @p output.
StreamLength OutOfOrderStream::innerOrderedWrite(IStream *output, BlockRef startBlock,
                                                 BlockRef endBlock, StreamLength maxBlockSize)
{
    // Determine a good size for the transfer buffer.
    constexpr size_t MaxTransferSize = 64 * 1024;

    StreamPosition originalPosition = _baseStream->getPosition();
    ByteBlock transferBuffer;

    transferBuffer.resize(std::min(MaxTransferSize, static_cast<size_t>(maxBlockSize)));
    StreamLength bufferSize = static_cast<StreamLength>(transferBuffer.size());
    StreamLength totalBytesWritten = 0;

    // Go through each block in the out-of-order stream and transfer them
    // to the output stream.
    for (auto blockPos = startBlock; blockPos != endBlock; ++blockPos)
    {
        // Skip empty blocks.
        if (blockPos->getLength() <= 0)
            continue;

        // Find the block in the out-of-order stream.
        _baseStream->setPosition(StreamRelative::Beginning, blockPos->getOffset());

        // Transfer the data using a fixed buffer.
        StreamLength bytesWritten = 0;

        while (bytesWritten < blockPos->getLength())
        {
            StreamLength bytesToWrite = std::min(blockPos->getLength() - bytesWritten, bufferSize);
            size_t byteCount = static_cast<size_t>(bytesToWrite);

            size_t bytesRead = _baseStream->read(transferBuffer.data(), byteCount);

            if (bytesRead > 0)
            {
                size_t written = output->write(transferBuffer.data(), bytesRead);

                bytesWritten += static_cast<StreamLength>(written);

                if (written == 0)
                    throw OperationException("Failed to write ordered data to the output stream.");
            }
            else
            {
                throw OperationException("Failed to read bytes from the out-of-order stream.");
            }
        }

        totalBytesWritten += bytesWritten;
    }

    // Restore the original out-of-order stream position.
    _baseStream->setPosition(StreamRelative::Beginning, originalPosition);

    return totalBytesWritten;
}

//! @brief Updates statistics based on bytes being written to he underlying stream.
//! @param[in] block The reference to the block to possibly update.
//! @param[in] bytesWritten The count of bytes to be added to the relevant block.
//! @return The reference to the block which was actually updated.
OutOfOrderStream::BlockRef OutOfOrderStream::accountForWrite(BlockRef block, size_t bytesWritten)
{
    StreamLength streamWritten = static_cast<StreamLength>(bytesWritten);
    BlockRef blockUpdated = _orderedBlocks.end();

    if ((block != _orderedBlocks.end()) && (block->getEnd() == _writeOffset))
    {
        // We are writing to the specified block, update it.
        StreamRegion region(block->getOffset(), block->getLength() + streamWritten);

        *block = region;
        blockUpdated = block;
    }
    else if (_orderedBlocks.empty() == false)
    {
        // The block is out of date, but we are updating the end of the stream.
        StreamRegion &lastRegion = _orderedBlocks.back();

        if (lastRegion.getEnd() == _writeOffset)
        {
            lastRegion = StreamRegion(lastRegion.getOffset(),
                                      lastRegion.getLength() + streamWritten);

            // Get a reference to the last block
            blockUpdated = _orderedBlocks.end();
            --blockUpdated;
        }
    }

    if (blockUpdated == _orderedBlocks.end())
    {
        // If we get this far, we are writing to an unknown block - create one
        // at the end of the run.
        // Start a new block encompassing the newly written bytes.
        blockUpdated = _orderedBlocks.insert(_orderedBlocks.end(),
                                             StreamRegion(_writeOffset, streamWritten));
    }

    _writeOffset += streamWritten;

    return blockUpdated;
}

//! @brief Calculates the number of bytes written to the stream from a starting
//! block to the end of the current ordered run of bytes.
//! @param[in] startBlock The block to start counting from.
//! @return The count of bytes in that run of blocks.
StreamLength OutOfOrderStream::calculateSizeToEnd(BlockRef startBlock) const
{
    StreamLength blockLength = 0;

    for (auto pos = startBlock; pos != _orderedBlocks.end(); ++pos)
        blockLength += pos->getLength();

    return blockLength;
}

//! @brief Assesses whether the stream has accumulated enough data that it
//! should be switched from being backed by memory to being backed by a file,
//! and performs the upgrade if necessary.
//! @param[in] bytesToAdd The count of bytes about to be added to the stream.
void OutOfOrderStream::checkForUpgrade(size_t bytesToAdd)
{
    // Trivially reject if the stream has already been upgraded.
    if (_writeOffset > MaxMemoryStreamSize)
        return;

    StreamLength expectedLength = _writeOffset + bytesToAdd;

    if (expectedLength <= MaxMemoryStreamSize)
        return;

    // Flush what we have out of the buffer.
    _currentBlock.flush();
    BlockRef currentRef = _currentBlock._block;

    // Create a temporary file to be the new backing store.
    ISeekableStreamUPtr tempFile = SeekableFileStream::createTempFile("hierarchy");

    // Copy the memory stream to the file.
    _baseStream->setPosition(StreamRelative::Beginning, 0);

    copyStream(_baseStream.get(), tempFile.get(), 0x10000);

    // Overwrite the memory stream with the file stream.
    _baseStream = std::move(tempFile);

    // Reset the buffered writer to point to the new base stream.
    // Use a larger buffer now that we are writing large volumes out to a file.
    _currentBlock = BlockWriterStream(this, true);
    _currentBlock._block = currentRef;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

