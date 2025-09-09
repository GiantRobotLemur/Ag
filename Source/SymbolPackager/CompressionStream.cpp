//! @file SymbolPackager/CompressionStream.cpp
//! @brief The definition of IStream implementations which perform in-line data
//! compression and decompression.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "CompressionStream.hpp"

////////////////////////////////////////////////////////////////////////////////
// Bz2CustomContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
Bz2CustomContext::Bz2CustomContext() :
    _hasError(false)
{
}

// Inherited from Bz2Context.
bool Bz2CustomContext::hasError() const { return _hasError; }

// Inherited from Bz2Context.
void Bz2CustomContext::setError() { _hasError = true; }

// Inherited from Bz2Context.
void Bz2CustomContext::onBz2Error(const char */*bz2Fn*/, int /*errorCode*/)
{
    _hasError = true;
}

// Inherited from Bz2Context.
void Bz2CustomContext::onInvalidState(State /*preferredState*/)
{
    _hasError = true;
}

////////////////////////////////////////////////////////////////////////////////
// Bz2CompressionContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates a context to compress data for delivery to an output stream
//! @param[in] outputStream The stream to write bytes to once they have been
//! compressed.
Bz2CompressionContext::Bz2CompressionContext(Ag::IStream *outputStream) :
    _outputStream(outputStream)
{
}

// Inherited from Bz2Context.
void Bz2CompressionContext::onBytesCompressed(const uint8_t *compressedBytes,
                                              size_t byteCount)
{
    if (_outputStream->write(compressedBytes, byteCount) != byteCount)
        setError();
}

////////////////////////////////////////////////////////////////////////////////
// Bz2CompressionStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a stream to compress data and write it to another stream.
//! @param[in] outputStream The stream to write bytes to once they have been
//! compressed.
Bz2CompressionStream::Bz2CompressionStream(Ag::IStream *outputStream) :
    _compressionContext(outputStream)
{
    _compressionContext.initialiseCompression(4096);
}

//! @brief Ensures that any buffered decompressed data is properly written
//! to the output stream.
Bz2CompressionStream::~Bz2CompressionStream()
{
    if (_compressionContext.hasError() == false)
        _compressionContext.finishCompression();
}

// Inherited from Ag::IStream.
size_t Bz2CompressionStream::read(void */*targetBuffer*/,
                                  size_t /*requiredByteCount*/)
{
    return 0;
}

// Inherited from Ag::IStream.
size_t Bz2CompressionStream::write(const void *sourceBuffer,
                                   size_t sourceByteCount)
{
    if (_compressionContext.hasError())
        return 0;

    return _compressionContext.compress(sourceBuffer, sourceByteCount);
}

////////////////////////////////////////////////////////////////////////////////
// Bz2DecompressionContext Member Definitions
////////////////////////////////////////////////////////////////////////////////
// Inherited from Bz2Context.
void Bz2DecompressionContext::onBytesCompressed(const uint8_t */*compressedBytes*/,
                                                size_t /*byteCount*/)
{
    setError();
}

////////////////////////////////////////////////////////////////////////////////
// Bz2DecompressionStream Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Attempts to refill the input buffer with data to decompress.
//! @retval true New compressed data became available.
//! @retval false No new data was read.
bool Bz2DecompressionStream::tryFillInputBuffer()
{
    if (_compressedData.canConsume() == false)
        return false;

    size_t maxCompressedBytes;
    void *buffer = _compressedData.lockProduceable(maxCompressedBytes);

    size_t compressedBytesRead = _inputStream->read(buffer, maxCompressedBytes);
    _compressedData.unlockProduceable(compressedBytesRead);

    return compressedBytesRead > 0;
}

//! @brief Constructs a stream to decompress data read from an input stream.
//! @param[in] inputStream The stream to read compressed bytes from.
//! @param[in] bufferSize The size of the buffer used to hold compressed and
//! decompressed data.
Bz2DecompressionStream::Bz2DecompressionStream(Ag::IStream *inputStream,
                                               size_t bufferSize) :
    _inputStream(inputStream),
    _compressedData(bufferSize)
{
    _decompressionContext.initialiseDecompression(0, false, bufferSize);
}

//! @brief Ensures decompression structures are properly disposed of.
Bz2DecompressionStream::~Bz2DecompressionStream()
{
    if (_decompressionContext.hasError() == false)
        _decompressionContext.finishDecompression();
}

// Inherited from Ag::IStream.
size_t Bz2DecompressionStream::read(void *targetBuffer,
                                    size_t requiredByteCount)
{
    size_t bytesRead = 0;
    uint8_t *dest = reinterpret_cast<uint8_t *>(targetBuffer);
    auto &outputBuffer = _decompressionContext.getDecompressionBuffer();

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
                _decompressionContext.decompress(compressedBytes, maxCompressable);

            _compressedData.consume(compressedBytesUsed);
        }
        else if (_decompressionContext.finishDecompression())
        {
            // If there is no more compressed data to read,
            // return with the bytes we have.
            break;
        }
    }

    return bytesRead;
}

// Inherited from Ag::IStream.
size_t Bz2DecompressionStream::write(const void */*sourceBuffer*/,
                                     size_t /*sourceByteCount*/)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

