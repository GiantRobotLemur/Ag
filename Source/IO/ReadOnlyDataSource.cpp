//! @file IO/ReadOnlyDataSource.cpp
//! @brief The definition of a read-only random-access data source.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/Exceptions.hpp"
#include "Ag/IO/MemoryMappedFile.hpp"
#include "Ag/IO/SeekableFileStream.hpp"
#include "Ag/IO/StreamTools.hpp"

#include "ReadOnlyDataSource.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of ISeekableStream which can read data from a
//! linear block of memory owned by another object.
class BlockViewStream : public ISeekableStream
{
private:
    // Internal Fields
    uint8_cptr_t _source;
    size_t _length;
    size_t _offset;
public:
    //! @brief Constructs a stream to access a block of memory without owning it.
    //! @param[in] data A pointer to the first byte to access.
    //! @param[in] length The count of bytes pointed to by @p data.
    BlockViewStream(const void *data, size_t length) :
        _source(reinterpret_cast<uint8_cptr_t>(data)),
        _length(length),
        _offset(0)
    {
    }

    // Overrides

    // Inherited from IStream.
    virtual void flush() override
    {
        // Do nothing.
    }

    // Inherited from IStream.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override
    {
        size_t bytesToCopy = std::min(_length - _offset, requiredByteCount);

        if (bytesToCopy > 0)
        {
            memcpy(targetBuffer, _source + _offset, bytesToCopy);

            _offset += bytesToCopy;
        }

        return bytesToCopy;
    }

    // Inherited from IStream.
    virtual size_t write(const void */*sourceBuffer*/, size_t /*sourceByteCount*/) override
    {
        throw NotSupportedException("The stream does not allow data to be written.");
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition getLength() const override
    {
        return static_cast<StreamPosition>(_length);
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition getPosition() const override
    {
        return static_cast<StreamPosition>(_offset);
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition setPosition(StreamRelative relativeTo,
                                       StreamPosition offset) override
    {
        StreamPosition absOffset = static_cast<StreamPosition>(_offset);
        StreamPosition totalLength = static_cast<StreamPosition>(_length);

        switch (relativeTo)
        {
        case Ag::IO::StreamRelative::Beginning:
        default:
            absOffset = offset;
            break;

        case Ag::IO::StreamRelative::Current:
            absOffset += offset;
            break;

        case Ag::IO::StreamRelative::End:
            absOffset = totalLength + offset;
            break;
        }

        if ((absOffset < 0) || (absOffset > totalLength))
            throw ArgumentException("Stream offset out of range.", "offset");

        offset = static_cast<size_t>(absOffset);

        return absOffset;
    }
};

//! @brief An implementation of ReadOnlyDataSource backed by a single large
//! block of memory.
class InMemoryDataSource : public ReadOnlyDataSource
{
private:
    // Internal Fields
    ByteBlock _source;
public:
    // Construction/Destruction

    //! @brief Constructs an object which uses a linear block of memory as a
    //! source of data.
    //! @param[in] rootExtent The position and size of the data being served.
    //! @param[in] data An R-value pointer which allows the new object to
    //! take ownership of the data.
    InMemoryDataSource(StreamLength rootExtent, ByteBlock &&data) :
        ReadOnlyDataSource(rootExtent),
        _source(std::move(data))
    {
    }

    // Overrides

    // Inherited from ReadOnlyDataSource.
    virtual bool tryReadByte(StreamPosition at, uint8_t &value) override
    {
        if (isRegionValid(StreamRegion(at, 1)))
        {
            value = _source.at(static_cast<size_t>(at));
            return true;
        }

        value = 0;
        return false;
    }

    // Inherited from ReadOnlyDataSource.
    virtual bool tryRead(const StreamRegion &region, void *buffer) override
    {
        if (isRegionValid(region))
        {
            // Copy the data.
            memcpy(buffer, _source.data() + region.getOffset(),
                   static_cast<size_t>(region.getLength()));

            return true;
        }

        return false;
    }

    // Inherited from ReadOnlyDataSource.
    virtual void readExactly(const StreamRegion &region, void *buffer) override
    {
        // Calculate the offset relative to the buffer.
        verifyRegion(region);

        // Copy the data.
        memcpy(buffer, _source.data() + region.getOffset(),
               static_cast<size_t>(region.getLength()));
    }

    // Inherited from ReadOnlyDataSource.
    virtual ISeekableStreamUPtr readStream(const StreamRegion &region) override
    {
        // Calculate the offset relative to the buffer.
        verifyRegion(region);

        return ISeekableStreamUPtr(new BlockViewStream(_source.data() + region.getOffset(),
                                                       static_cast<size_t>(region.getLength())));
    }
};

//! @brief A wrapper for a MemoryMappedView object which adds a
//! Least-Recently-Used (LRU) sequence value.
class MappedBlock : public MemoryMappedView
{
private:
    // Internal Fields
    uint64_t _lastUsed;

public:
    // Construction/Destruction

    //! @brief Constructs a mapped block by acquiring a view of a memory
    //! mapped file.
    //! @param[in] view The mapped view to acquire.
    //! @param[in] lastUsed The sequence number indicating when the view
    //! was last accessed.
    MappedBlock(MemoryMappedView &&view, uint64_t lastUsed) noexcept :
        MemoryMappedView(std::move(view)),
        _lastUsed(lastUsed)
    {
    }

    //! @brief Acquires a mapped block from another object.
    //! @param[in] rhs The object to acquire the block from.
    MappedBlock(MappedBlock &&rhs) noexcept :
        MemoryMappedView(std::move(rhs)),
        _lastUsed(rhs._lastUsed)
    {
        rhs._lastUsed = 0;
    }

    //! @brief Acquires a mapped block from another object during assignment.
    //! @param[in] rhs The block to acquire the mapping from.
    //! @return A reference to the current object.
    MappedBlock &operator=(MappedBlock &&rhs) noexcept
    {
        MemoryMappedView::operator=(std::move(rhs));
        _lastUsed = rhs._lastUsed;
        rhs._lastUsed = 0;

        return *this;
    }

    //! @brief Gets the sequence value indicating when the block was last accessed.
    constexpr uint64_t getLastUsed() const noexcept
    {
        return _lastUsed;
    }

    //! @brief Sets the sequence number indicating when the block was last accessed.
    //! @param[in] lastUsed The new sequence number.
    void setLastUsed(uint64_t lastUsed) noexcept
    {
        _lastUsed = lastUsed;
    }
};

//! @brief A wrapper for SeekableFileStream which only allows access to a
//! sub-region of a file as if it were a file in its own right.
class SubFileStream : public ISeekableStream
{
private:
    // Internal Fields
    ISeekableStreamUPtr _file;
    StreamRegion _subRegion;
    StreamLength _readPosition;

public:
    // Construction/Destruction

    //! @brief Constructs a stream to wrap a file stream.
    //! @param[in] fileName The name of the file to open for reading.
    //! @param[in] region The region of the file which this object should
    //! provide access to.
    SubFileStream(const Fs::Path &fileName, const StreamRegion &region) :
        _subRegion(region),
        _readPosition(0)
    {
        _file = SeekableFileStream::open(fileName, FileAccess::Read | FileAccess::OpenExisting);

        // Move the read pointer to the start of the region.
        _file->setPosition(StreamRelative::Beginning, region.getOffset());
    }

    // Overrides

    // Inherited from IStream.
    virtual void flush() override
    {
        _file->flush();
    }

    // Inherited from IStream.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override
    {
        StreamLength maxStreamRead = _subRegion.getLength() - _readPosition;
        StreamLength safeRead = std::min(maxStreamRead, static_cast<StreamLength>(requiredByteCount));

        if (safeRead > 0)
        {
            size_t bytesRead = _file->read(targetBuffer, static_cast<size_t>(safeRead));

            _readPosition += static_cast<StreamLength>(bytesRead);

            return bytesRead;
        }
        else
        {
            // No more can be read.
            return 0;
        }
    }

    // Inherited from IStream.
    virtual size_t write(const void */*sourceBuffer*/, size_t /*sourceByteCount*/) override
    {
        throw NotSupportedException("Data cannot be written to a static data source.");
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition getLength() const override
    {
        return _subRegion.getLength();
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition getPosition() const override
    {
        return _readPosition;
    }

    // Inherited from ISeekableStream.
    virtual StreamPosition setPosition(StreamRelative relativeTo,
                                       StreamPosition offset) override
    {
        // Calculate the position within the sub-region of the stream.
        StreamPosition absPos = offset;

        switch (relativeTo)
        {
        case Ag::IO::StreamRelative::Beginning:
        default:
            absPos = offset;
            break;

        case Ag::IO::StreamRelative::Current:
            absPos = _readPosition + offset;
            break;

        case Ag::IO::StreamRelative::End:
            absPos = _subRegion.getLength() + offset;
            break;
        }

        // Don't allow offsets beyond the bounds of the sub-region.
        if ((absPos < 0) || (absPos > _subRegion.getLength()))
        {
            throw ArgumentException("The new file pointer is beyond the bounds of the stream."
                                    "offset");
        }

        // Position the underlying file stream.
        StreamPosition actualPos = _file->setPosition(StreamRelative::Beginning,
                                                      _subRegion.getOffset() + absPos);

        // Use the actual result to determine the new read position.
        _readPosition = actualPos - _subRegion.getOffset();

        return _readPosition;
    }
};

//! @brief An implementation of ReadOnlyDataSource backed by a single large
//! block of memory.
class FileDataSource : public ReadOnlyDataSource
{
private:
    // Internal Types
    using ViewMap = std::map<StreamPosition, MappedBlock>;

    // Internal Fields
    static constexpr size_t MaxViewCount = 16;

    MemoryMappedFile _mappedFile;
    ViewMap _viewsByBlockIndex;
    uint64_t _sequence;
    size_t _mappedBlockSize;

    // Internal Functions

    //! @brief Gets a view of the mapped file containing a specified offset.
    //! @param[in] streamOffset The offset of the first byte to access.
    //! @param[out] viewOffset Receives the offset of the same byte within the
    //! mapped view.
    //! @return A block mapped into memory containing the specified byte.
    MappedBlock &getBlock(StreamPosition streamOffset, StreamPosition &viewOffset)
    {
        StreamPosition blockIndex = streamOffset / _mappedBlockSize;
        viewOffset = streamOffset - (blockIndex * _mappedBlockSize);

        auto pos = _viewsByBlockIndex.find(blockIndex);

        if (pos == _viewsByBlockIndex.end())
        {
            // Create a new view.
            if (_viewsByBlockIndex.size() >= MaxViewCount)
            {
                // Evict the least recently used view first.
                auto lruItem = _viewsByBlockIndex.end();
                uint64_t lruSequence = _sequence;

                for (pos = _viewsByBlockIndex.begin(); pos != _viewsByBlockIndex.end(); ++pos)
                {
                    if (pos->second.getLastUsed() < lruSequence)
                    {
                        lruItem = pos;
                        lruSequence = lruItem->second.getLastUsed();
                    }
                }

                if (lruItem != _viewsByBlockIndex.end())
                    _viewsByBlockIndex.erase(lruItem);
            }

            StreamPosition fileBlockSize = MemoryMappedFile::getBlockSize();
            StreamPosition fileBlockIndex = (blockIndex * _mappedBlockSize) / fileBlockSize;
            StreamPosition fileOffset = fileBlockIndex * fileBlockSize;
            StreamLength fileMappingSize = std::min(_mappedFile.getMappingSize() - fileOffset,
                                                static_cast<StreamLength>(_mappedBlockSize));

            // Map the view into memory.
            auto view = _mappedFile.createView(fileBlockIndex,
                                               static_cast<size_t>(fileMappingSize));

            // Move the view into the map.
            auto insertResult = _viewsByBlockIndex.emplace(blockIndex,
                                                           MappedBlock(std::move(view), _sequence));

            // Return the view held by the map.
            return insertResult.first->second;
        }
        else
        {
            // The map already exists, return it.
            return pos->second;
        }
    }

    //! @brief Updates the least-recently-used values on the currently
    //! mapped views.
    void resequenceMappings()
    {
        // The sequence value as wrapped around having assigned the highest
        // LRU sequence value to the block we just accessed. Adjust all the
        // sequence values.
        //
        // Note: We can't map directly to the blocks as they own the
        // mapped views.
        LinearSortedMap<uint64_t, StreamPosition> blockIDBySequence;
        blockIDBySequence.reserve(_viewsByBlockIndex.size());

        // Get all the mapped blocks and sequence values.
        for (const ViewMap::value_type &mapping : _viewsByBlockIndex)
            blockIDBySequence.push_back(mapping.second.getLastUsed(), mapping.first);

        // Sort by sequence values.
        blockIDBySequence.reindex(true);

        // Go through the mapped blocks in sequence order, resetting
        // the sequence values.
        for (const auto &sequenceToID : blockIDBySequence)
        {
            auto pos = _viewsByBlockIndex.find(sequenceToID.second);

            if (pos != _viewsByBlockIndex.end())
                pos->second.setLastUsed(_sequence++);
        }
    }
public:
    // Construction/Destruction

    //! @brief Constructs a new data source backed by a temporary file.
    //! @param[in] rootExtent The length of the temp file.
    //! @param[in] tempFile The path to the temporary file to open and delete
    //! on disposal.
    FileDataSource(StreamLength rootExtent, const Fs::Path &tempFile) :
        ReadOnlyDataSource(rootExtent),
        _sequence(1),
        _mappedBlockSize(4 * 1024)
    {
        _mappedFile.open(tempFile, FileAccess::Read | FileAccess::OpenExisting);

        // Calculate the regular size of views mapped into the address space.
        constexpr size_t PreferredBlockSize = 64 * 1024 * 1024;
        const size_t MapBlockSize = MemoryMappedFile::getBlockSize();

        size_t blocksPerMapping = (PreferredBlockSize + MapBlockSize - 1) / MapBlockSize;

        _mappedBlockSize = blocksPerMapping * MapBlockSize;
    }

    //! @brief Ensures that the file mappings are disposed of and the
    //! temporary file deleted.
    virtual ~FileDataSource() override
    {
        Fs::Path tempFile = _mappedFile.getFileName();

        // Dispose of all of the mapped views.
        _viewsByBlockIndex.clear();

        // Close the file.
        _mappedFile.close();

        // Ensure the temporary file is deleted without creating any errors.
        Fs::Entry file(tempFile);

        if (file.exists())
            file.remove(/* reportError = */ false);
    }

    // Inherited from ReadOnlyDataSource.
    virtual bool tryReadByte(StreamPosition at, uint8_t &value) override
    {
        value = 0;

        if (isRegionValid(StreamRegion(at, 1)) == false)
            return false;

        StreamLength offsetInBlock;
        MappedBlock &block = getBlock(at, offsetInBlock);

        value = reinterpret_cast<uint8_cptr_t>(block.getPointer())[offsetInBlock];

        return true;
    }

    // Inherited from ReadOnlyDataSource.
    virtual bool tryRead(const StreamRegion &region, void *buffer) override
    {
        if (isRegionValid(region) == false)
            return false;

        StreamPosition blockOffset = region.getOffset();

        uint8_ptr_t target = reinterpret_cast<uint8_ptr_t>(buffer);
        StreamLength bytesRead = 0;

        while (bytesRead < region.getLength())
        {
            StreamPosition offsetInBlock;

            MappedBlock &block = getBlock(blockOffset + bytesRead, offsetInBlock);
            StreamLength maxRead = static_cast<StreamLength>(block.getSize()) - offsetInBlock;
            StreamLength safeSize = std::min(maxRead, region.getLength());

            memcpy(target + bytesRead,
                   reinterpret_cast<uint8_cptr_t>(block.getPointer()) + offsetInBlock,
                   static_cast<size_t>(safeSize));

            bytesRead += safeSize;

            // Keep track of which mappings were most recently used so that
            // we can evict the least recently used block at need.
            block.setLastUsed(_sequence++);

            if (_sequence == 0)
                resequenceMappings();
        }

        return true;
    }

    // Inherited from ReadOnlyDataSource.
    virtual void readExactly(const StreamRegion &region, void *buffer) override
    {
        verifyRegion(region);

        if (tryRead(region, buffer) == false)
            throw IOException("Failed to read the number of bytes requested.");
    }

    // Inherited from ReadOnlyDataSource.
    virtual ISeekableStreamUPtr readStream(const StreamRegion &region) override
    {
        verifyRegion(region);

        // Open a file stream to read only the region in question.
        SubFileStream *stream = new SubFileStream(_mappedFile.getFileName(), region);

        return ISeekableStreamUPtr(stream);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
//! @brief The maximum size of a block of data before it should be backed by a
//! memory mapped file rather than an in-memory block.
constexpr StreamLength MaxInMemorySize = 4l * 1024 * 1024;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// ReadOnlyDataSource Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a data source which represent a specific region of a stream.
//! @param[in] rootExtent The length of the region the data source accesses,
//! assuming it starts at offset 0.
ReadOnlyDataSource::ReadOnlyDataSource(StreamLength rootExtent) :
    _rootRegion(0, rootExtent)
{
}

//! @brief Creates an object which allows random read-only access to the data
//! in a stream.
//! @param[in] inputData The data to copy and provide access to.
//! @param[in] byteCount The count of bytes in @p input data to access.
//! @return An object which provides access to the data during its lifetime.
ReadOnlyDataSource::UPtr ReadOnlyDataSource::create(IStream *inputData,
                                                    StreamLength byteCount)
{
    StreamPosition startPos = 0;

    if (byteCount < 0)
        throw ArgumentException("The size of the data source must be non-negative.",
                                "byteCount");

    if (auto seekableStream = dynamic_cast<ISeekableStream *>(inputData))
    {
        startPos = seekableStream->getPosition();
    }

    if (byteCount > MaxInMemorySize)
    {
        // Copy the data to a temporary file and memory map parts of it.
        ISeekableStreamUPtr tempFile = SeekableFileStream::createTempFile("payload");
        Fs::Path tempPath = dynamic_cast<SeekableFileStream *>(tempFile.get())->getPath();

        copyStream(inputData, byteCount, tempFile.get(), MaxBufferSize);

        // Close the file.
        tempFile.reset();

        // Create a source based on the temp file.
        return UPtr(new FileDataSource(byteCount, tempPath));
    }
    else
    {
        // Copy the data into a single memory block.
        ByteBlock source;
        source.resize(static_cast<size_t>(byteCount));

        size_t bytesRead = inputData->read(source.data(), source.size());

        if (bytesRead != source.size())
            throw IOException("Failed to read all source data.");

        // Allocate and return an object to provide the data to the caller.
        return UPtr(new InMemoryDataSource(byteCount, std::move(source)));
    }
}

//! @brief Gets the region of the underlying data source the object accesses.
const StreamRegion &ReadOnlyDataSource::getRootRegion() const
{
    return _rootRegion;
}

//! @brief Verifies a region of the data source is within the root region.
//! @param[in] region The region to validate.
//! @retval true The region is wholly within the root region.
bool ReadOnlyDataSource::isRegionValid(const StreamRegion &region) const
{
    return (region.getOffset() >= _rootRegion.getOffset()) &&
           (region.getEnd() <= _rootRegion.getEnd());
}

//! @brief Verifies that a stream region is inside the root data source region.
//! @param[in] region The region to verify.
//! @throws ArgumentException Thrown if @p region is not wholly inside the
//! region encompassed by the data source.
void ReadOnlyDataSource::verifyRegion(const StreamRegion &region) const
{
    if ((region.getOffset() < _rootRegion.getOffset()) ||
        (region.getEnd() > _rootRegion.getEnd()))
    {
        throw ArgumentException("The requested data is outside that which can be accessed.",
                                "region");
    }
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

