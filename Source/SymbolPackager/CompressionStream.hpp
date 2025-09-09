//! @file SymbolPackager/CompressionStream.hpp
//! @brief The declaration of IStream implementations which perform in-line data
//! compression and decompression.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2025
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef __AG_SYMBOL_PACKAGER_COMPRESSION_STREAM_HPP__
#define __AG_SYMBOL_PACKAGER_COMPRESSION_STREAM_HPP__

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Utils.hpp"
#include "Ag/Private/Bz2Stream.hpp"

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A customisation of a Bz2Context suitable for operating in an
//! environment where exceptions aren't used.
class Bz2CustomContext : public Bz2Context
{
private:
    // Internal Fields
    bool _hasError;
public:
    // Construction/Destruction
    Bz2CustomContext();
    virtual ~Bz2CustomContext() = default;

    // Accessors
    bool hasError() const;
    void setError();

    // Overrides
    virtual void onBz2Error(const char *bz2Fn, int errorCode) override;
    virtual void onInvalidState(State preferredState) override;
};

//! @brief A context specialised for compression of data.
class Bz2CompressionContext : public Bz2CustomContext
{
private:
    // Internal Fields
    Ag::IStream *_outputStream;
public:
    // Construction/Destruction
    Bz2CompressionContext(Ag::IStream *outputStream);
    virtual ~Bz2CompressionContext() = default;

    // Overrides
    virtual void onBytesCompressed(const uint8_t *compressedBytes,
                                   size_t byteCount) override;
};

//! @brief A stream which compresses data written to it.
class Bz2CompressionStream : public Ag::IStream
{
private:
    // Internal Fields
    Bz2CompressionContext _compressionContext;
public:
    // Construction/Destruction
    Bz2CompressionStream(Ag::IStream *outputStream);
    virtual ~Bz2CompressionStream();

    // Overrides
    virtual size_t read(void *targetBuffer,
                        size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer,
                         size_t sourceByteCount) override;
};

//! @brief A compression context specialised for decompression.
class Bz2DecompressionContext : public Bz2CustomContext
{
public:
    // Construction/Destruction
    Bz2DecompressionContext() = default;
    virtual ~Bz2DecompressionContext() = default;

    // Overrides
    virtual void onBytesCompressed(const uint8_t *compressedBytes,
                                   size_t byteCount) override;
};

//! @brief A stream implementation which decompresses data read from
//! another stream.
class Bz2DecompressionStream : public Ag::IStream
{
private:
    // Internal Fields
    Bz2DecompressionContext _decompressionContext;
    Ag::ByteProducerConsumer _compressedData;
    Ag::IStream *_inputStream;

    // Internal Functions
    bool tryFillInputBuffer();
public:
    // Construction/Destruction
    Bz2DecompressionStream(Ag::IStream *inputStream, size_t bufferSize);
    virtual ~Bz2DecompressionStream();

    // Overrides
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override;
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override;
};

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
