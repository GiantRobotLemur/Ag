//! @file Ag/Core/Private/Bz2Stream.hpp
//! @brief The declaration of an object which manages compression and
//! decompression using the bz2 library.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////
// NOTE: This header is shared between AgCore and SymbolPackager, but is
// otherwise private.

#ifndef __AG_BZ2_STREAM_HPP__
#define __AG_BZ2_STREAM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
#include <cstring>

#include <algorithm>
#include <vector>

#ifdef WIN32
// bzlib.h includes windows.h - so make compatible with C++.
#define NOMINMAX
#endif

#include <bzlib.h>

#include "ByteProducerConsumer.hpp"

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An object which wraps compression and decompression streams using the
//! bz2 library.
//! @note
//! Instructions on use of the low-level bz2 compression library can
//! be found at https://www.sourceware.org/bzip2/manual/manual.html#low-level
class Bz2Context
{
public:
    // Public Types
    enum class State
    {
        Idle,
        RunningCompression,
        FinishingCompression,
        RunningDecompression,
        FinishingDecompression,
    };

    // Public Fields
    static constexpr size_t BufferSize = 256;

    // Overrides
    //! @brief Called when a bz2 function returned an unexpected result.
    //! @param[in] bz2Fn A string representation of the function called, perhaps
    //! with a summary or parameters.
    //! @param[in] errorCode The error value returned by the library function.
    virtual void onBz2Error(const char *bz2Fn, int errorCode) = 0;

    //! @brief Called when a member function was called when the object was in an
    //! inappropriate state.
    //! @param[in] preferredState The state the object needed to be in, but wasn't.
    virtual void onInvalidState(State preferredState) = 0;

    //! @brief Called when some data has been successfully compressed.
    //! @param[in] compressedBytes The array of compressed bytes.
    //! @param[in] byteCount byteCount The count of bytes in @p compressedBytes.
    virtual void onBytesCompressed(const uint8_t *compressedBytes, size_t byteCount) = 0;
private:
    // Internal Fields
    bz_stream _bzContext;
    Ag::ByteProducerConsumer _buffer;
    State _state;

    // Internal Functions
    void verifyState(State preferredState)
    {
        if (_state != preferredState)
            onInvalidState(preferredState);
    }

    void closeCompression()
    {
        if ((_state != State::RunningCompression) &&
            (_state != State::FinishingCompression))
            return;

        _state = State::Idle;
        _buffer.reset(0);

        int errorCode = BZ2_bzCompressEnd(&_bzContext);

        if (errorCode != BZ_OK)
            onBz2Error("BZ2_bzCompressEnd()", errorCode);
    }

    void closeDecompression()
    {
        if (_state != State::RunningDecompression)
            return;

        if (_buffer.canProduce())
        {
            // There is decompressed data left in the buffer, even if we
            // are unable to decompress any more.
            _state = State::FinishingDecompression;
        }
        else
        {
            _state = State::Idle;

            // Free the buffer if it is empty.
            _buffer.reset(0);
        }

        int errorCode = BZ2_bzDecompressEnd(&_bzContext);

        if (errorCode != BZ_OK)
            onBz2Error("BZ2_bzDecompressEnd()", errorCode);
    }
public:
    //! @brief Constructs a context in an idle state.
    Bz2Context() :
        _buffer(0),
        _state(State::Idle)
    {
        memset(&_bzContext, 0, sizeof(_bzContext));
    }

    virtual ~Bz2Context() = default;

    // Accessors
    Ag::ByteProducerConsumer &getDecompressionBuffer() { return _buffer; }
    const Ag::ByteProducerConsumer &getDecompressionBuffer() const { return _buffer; }

    // Operations

    //! @brief Initialises the object for compression operations.
    //! @param[in] bufferSize The size of the buffer used to receive
    //! compressed data, in bytes.
    //! @param[in] compressionLevel The size of the dictionary to use to
    //! compress data 0-9.
    //! @param[in] verbosity Specifies the amount of output from the bz2 library,
    //! 0 for silent, 4 for maximum output.
    //! @param[in] workFactor Controls how the compression phase behaves when presented
    //! with worst case, highly repetitive, input data. Values between 1 and 250
    //! are allowed, 30 is the default.
    void initialiseCompression(size_t bufferSize = BufferSize,
                               int compressionLevel = 9,
                               int verbosity = 0,
                               int workFactor = 30)
    {
        verifyState(State::Idle);

        int bzResult = BZ2_bzCompressInit(&_bzContext,
                                          std::clamp(compressionLevel, 1, 9),
                                          std::clamp(verbosity, 0, 4),
                                          std::clamp(workFactor, 0, 250));

        if (bzResult != BZ_OK)
            onBz2Error("BZ2_bzCompressInit()", bzResult);

        _buffer.reset(bufferSize);

        _state = State::RunningCompression;
    }

    //! @brief Compresses some data after a previous call to initialiseCompression().
    //! @param[in] dataToCompress The array of bytes to compress.
    //! @param[in] byteCount The count of bytes in @p dataToCompress.
    //! @return The count of bytes compressed, should be @p byteCount.
    //! @remarks This function calls onBytesCompressed() when a new run of
    //! compressed data is available.
    size_t compress(const void *dataToCompress, size_t byteCount)
    {
        verifyState(State::RunningCompression);

        char *source = const_cast<char *>(reinterpret_cast<const char *>(dataToCompress));
        size_t bytesRead = 0;

        while (bytesRead < byteCount)
        {
            size_t bytesToWrite = std::min(static_cast<size_t>(UINT32_MAX),
                                           byteCount - bytesRead);

            _bzContext.avail_in = static_cast<uint32_t>(bytesToWrite);
            _bzContext.next_in = source + bytesRead;

            size_t bufferFree;
            _bzContext.next_out = reinterpret_cast<char *>(_buffer.lockProduceable(bufferFree));
            _bzContext.avail_out = static_cast<uint32_t>(bufferFree);

            int errorCode = BZ2_bzCompress(&_bzContext, BZ_RUN);

            if (errorCode == BZ_RUN_OK)
            {
                size_t bytesConsumed = bytesToWrite - _bzContext.avail_in;
                _buffer.unlockProduceable(bufferFree - _bzContext.avail_out);

                bytesRead += bytesConsumed;

                if (_buffer.canProduce())
                {
                    // Flush compressed data to the output stream.
                    size_t consumableCount;
                    auto consumableBytes = _buffer.getConsumable(consumableCount);

                    onBytesCompressed(consumableBytes, consumableCount);
                    _buffer.consume(consumableCount);
                }
            }
            else
            {
                // Something went wrong.
                onBz2Error("BZ2_bzCompress(BZ_RUN)", errorCode);
                closeCompression();
            }
        }

        return bytesRead;
    }

    //! @brief Writes any final buffered compressed bytes and resets the object
    //! to an idle state.
    //! @remarks This function calls onBytesCompressed() when a new run of
    //! compressed data is available.
    void finishCompression()
    {
        verifyState(State::RunningCompression);
        _state = State::FinishingCompression;

        char InputBuffer;
        int errorCode = BZ_OK;

        do
        {
            _bzContext.avail_in = 0;
            _bzContext.next_in = &InputBuffer;

            size_t bufferFree;
            _bzContext.next_out = reinterpret_cast<char *>(_buffer.lockProduceable(bufferFree));
            _bzContext.avail_out = static_cast<uint32_t>(bufferFree);

            errorCode = BZ2_bzCompress(&_bzContext, BZ_FINISH);

            if ((errorCode == BZ_FINISH_OK) || (errorCode == BZ_STREAM_END))
            {
                _buffer.unlockProduceable(bufferFree - _bzContext.avail_out);

                if (_buffer.canProduce())
                {
                    size_t bytesCompressed;
                    auto compressedBytes = _buffer.getConsumable(bytesCompressed);

                    onBytesCompressed(compressedBytes, bytesCompressed);
                    _buffer.consume(bytesCompressed);
                }
            }
            else
            {
                onBz2Error("BZ2_bzCompress(BZ_FINISH)", errorCode);
                errorCode = BZ_STREAM_END;
            }
        } while (errorCode != BZ_STREAM_END);

        closeCompression();
    }

    //! @brief Initialises decompression operations.
    //! @param[in] verbosity Specifies the amount of output from the bz2 library,
    //! 0 for silent, 4 for maximum output.
    //! @param[i] small True to reduce memory consumption in the compression algorithm,
    //! but possible halving its speed.
    //! @param[in] bufferSize The size of the buffer allocated to receive
    //! decompressed data.
    void initialiseDecompression(int verbosity = 0, bool small = false,
                                 size_t bufferSize = BufferSize)
    {
        verifyState(State::Idle);

        int errorCode = BZ2_bzDecompressInit(&_bzContext,
                                             std::clamp(verbosity, 0, 4),
                                             small ? 1 : 0);

        if (errorCode != BZ_OK)
            onBz2Error("BZ2_bzDecompressInit()", errorCode);

        _buffer.reset(bufferSize);
        _state = State::RunningDecompression;
    }

    //! @brief Decompresses data.
    //! @param[in] compressedBytes An array of compressed bytes to unpack, possibly
    //! nullptr if we just want to read batched output.
    //! @param[in] compressedCount The count of bytes in @p compressedBytes.
    //! @param[out] decompressedBytes A buffer to receive the decompressed data.
    //! @param[in,out] decompressedByteCount Initially the count of bytes in
    //! @p decompressedBytes, on exit is updated with the actual count of bytes
    //! written to the @p decompressedBytes buffer.
    //! @return The count of bytes decompressed, should be @p byteCount.
    size_t decompress(const void *compressedBytes, size_t compressedCount)
    {
        if (_state == State::Idle)
            return 0;

        if (_state == State::FinishingDecompression)
            return 0;

        verifyState(State::RunningDecompression);

        char *source = const_cast<char *>(reinterpret_cast<const char *>(compressedBytes));
        size_t bytesRead = 0;

        while ((bytesRead < compressedCount) && _buffer.canConsume())
        {
            size_t bytesToConsume = std::min(static_cast<size_t>(UINT32_MAX),
                                             compressedCount - bytesRead);

            _bzContext.avail_in = static_cast<uint32_t>(bytesToConsume);
            _bzContext.next_in =  source + bytesRead;

            size_t bufferFree;
            _bzContext.next_out = reinterpret_cast<char *>(_buffer.lockProduceable(bufferFree));
            _bzContext.avail_out = static_cast<uint32_t>(bufferFree);

            int errorCode = BZ2_bzDecompress(&_bzContext);

            if ((errorCode == BZ_OK) || (errorCode == BZ_STREAM_END))
            {
                size_t bytesConsumed = bytesToConsume - _bzContext.avail_in;
                size_t bytesDecompressed = bufferFree - _bzContext.avail_out;
                _buffer.unlockProduceable(bytesDecompressed);
                bytesRead += bytesConsumed;

                if (errorCode == BZ_STREAM_END)
                {
                    // We've reached the logical end of the compression stream.
                    closeDecompression();
                }
                else if ((bytesConsumed == 0) && (bytesDecompressed == 0))
                {
                    // No work was done, perhaps more compressed data needs to
                    // be fed in?
                    break;
                }
            }
            else
            {
                // Something went wrong.
                onBz2Error("BZ2_bzDecompress()", errorCode);
                break;
            }
        }

        return bytesRead;
    }

    //! @brief Produces final decompressed data when there are no more
    //! compressed bytes to read.
    //! @retval true Decompression is finished, no more data decompressed
    //! data can be read.
    //! @retval false There is more decompressed data to read stored in the
    //! output buffer.
    bool finishDecompression()
    {
        if (_state == State::Idle)
            return true;

        if (_state == State::FinishingDecompression)
            return _buffer.canProduce() == false;

        verifyState(State::RunningDecompression);

        int errorCode = BZ_OK;
        char inputBuffer = '\0';

        // Extract decompressed data without putting any more
        // compressed data in.
        _bzContext.avail_in = 0;
        _bzContext.next_in = &inputBuffer;

        size_t bufferAvilable;
        _bzContext.next_out = reinterpret_cast<char *>(_buffer.lockProduceable(bufferAvilable));
        _bzContext.avail_out = static_cast<uint32_t>(bufferAvilable);

        errorCode = BZ2_bzDecompress(&_bzContext);

        if ((errorCode == BZ_RUN_OK) || (errorCode == BZ_STREAM_END))
        {
            size_t bytesDecompressed = bufferAvilable - _bzContext.avail_out;
            _buffer.unlockProduceable(bytesDecompressed);

            if (errorCode == BZ_STREAM_END)
            {
                // We've reached the logical end of the compression stream.
                closeDecompression();
            }
        }
        else
        {
            // Something went wrong.
            onBz2Error("BZ2_bzDecompress()", errorCode);
            errorCode = BZ_STREAM_END;
        }

        return false;
    }
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
