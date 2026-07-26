//! @file IO/TestTools.cpp
//! @brief The definition of tools shared between various IO unit tests.
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

#include "TestTools.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// RandomByteGenerator Member Definitions
////////////////////////////////////////////////////////////////////////////////
RandomByteGenerator::InnerState::InnerState(RandomByteGenerator::RootScalar seed) :
    _engine(seed),
    _seed(seed),
    _latest(0),
    _bytesUsed(sizeof(RootScalar))
{
}

void RandomByteGenerator::InnerState::reset()
{
    _engine.seed(_seed);
    _latest = 0;
    _bytesUsed = sizeof(RootScalar);
}

uint8_t RandomByteGenerator::InnerState::generate()
{
    if (_bytesUsed >= sizeof(RootScalar))
    {
        _latest = _engine();
        _bytesUsed = 0;
    }

    return reinterpret_cast<uint8_cptr_t>(&_latest)[_bytesUsed++];
}

void RandomByteGenerator::InnerState::skip(size_t count)
{
    // The engine doesn't work in terms of bytes, so we need
    // to skip words and then discard any spare bytes.
    size_t skipWords = count / sizeof(RootScalar);
    uint8_t skipOffset = static_cast<uint8_t>(count % sizeof(RootScalar));

    if (skipOffset == 0)
    {
        // Prepare to start at the next word.
        _engine.discard(skipWords);
        _bytesUsed = sizeof(RootScalar);
    }
    else if (skipWords > 1)
    {
        _engine.discard(skipWords - 1);
        _latest = _engine();
        _bytesUsed = skipOffset;
    }
    else
    {
        _bytesUsed -= skipOffset;
    }
}

RandomByteGenerator::RandomByteGenerator(RandomByteGenerator::RootScalar seed) :
    _state(std::make_shared<InnerState>(seed))
{
}

void RandomByteGenerator::reset()
{
    // Reseed the engine.
    _state->reset();
}

uint8_t RandomByteGenerator::operator()()
{
    return _state->generate();
}

void RandomByteGenerator::skip(size_t count)
{
    // Reseed the engine.
    _state->skip(count);
}

String RandomByteGenerator::nextString(size_t preferredSize /*= 0*/)
{
    if (preferredSize == 0)
        preferredSize = nextValue<uint16_t>();

    Utf::ToUtf8Converter converter;
    std::string buffer;
    buffer.reserve((preferredSize * 110) / 100);

    // Try to generate printable characters.
    constexpr int PrintableMin = 32;

    for (size_t i = 0; i < preferredSize; ++i)
    {
        int code = _state->generate() + PrintableMin;

        if (converter.setCodePoint(static_cast<char32_t>(code)) > 0)
        {
            uint8_t nextByte;

            while (converter.tryGetNextByte(nextByte))
                buffer.push_back(nextByte);
        }
    }

    return { buffer };
}

////////////////////////////////////////////////////////////////////////////////
// FileDeleter Member Definitions
////////////////////////////////////////////////////////////////////////////////
FileDeleter::FileDeleter(const Fs::Path &fileToDelete) :
    _fileToDelete(fileToDelete)
{
}

FileDeleter::~FileDeleter()
{
    try
    {
        _fileToDelete.refresh();

        if (_fileToDelete.exists())
            _fileToDelete.remove();
    }
    catch(const Exception &)
    {
        // Ignore any errors.
    }
}

const Fs::Path &FileDeleter::getPath() const
{
    return _fileToDelete.getPath();
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
size_t writeRandomBytes(RandomByteGenerator &generator, IStream *stream,
                        size_t byteCount)
{
    size_t bytesWritten = 0;
    uint8_t next;

    for (size_t i = 0; i < byteCount; ++i)
    {
        next = generator();

        bytesWritten += stream->write(&next, 1);
    }

    return bytesWritten;
}

ByteBlock fillRandomData(RandomByteGenerator &generator, size_t byteCount)
{
    if (byteCount < 1)
        return { };

    ByteBlock data;
    data.resize(byteCount);

    size_t bytesWritten = 0;
    auto inserter = std::back_inserter(data);

    while (bytesWritten < byteCount)
    {
        auto next = generator();

        size_t bytesToWrite = std::min(byteCount - bytesWritten, sizeof(next));

        memcpy(data.data() + bytesWritten, &next, bytesToWrite);
        bytesWritten += bytesToWrite;
    }

    return data;
}

Fs::Path generateTempFileName()
{
    Fs::PathBuilder builder;

    // The program folder should be appropriate for testing.
    builder.assignProgramDirectory();

    for (size_t i = 0; i < 0xFFFF; ++i)
    {
        builder.pushElement(String::format("{0:D4}.tmp", { i }));

        Fs::Path attemptedPath(builder);
        builder.popElement();

        Fs::Entry fileEntry(attemptedPath);

        if (fileEntry.exists() == false)
        {
            return attemptedPath;
        }
    }

    throw OperationException("Failed to generate a temporary file name.");
}

void createRandomDataFile(RandomByteGenerator &entropySource,
                          const Fs::Path &fileName, size_t fileSize)
{
    String errorMessage;
    FILE *fp = nullptr;

    // Open an empty file to overwrite via more conventional means.
    if (Ag::tryOpenFile(fileName.toString(), "wb", fp, errorMessage))
    {
        // Ensure the file is closed when the scope ends.
        StdFilePtr fileScope(fp);

        // Generate and write random data in blocks.
        constexpr size_t BlockSize = 4096;

        ByteBlock randomData;
        randomData.reserve(std::min(BlockSize, fileSize));

        size_t bytesWritten = 0;

        while (bytesWritten < fileSize)
        {
            // Generate a new block of random data.
            size_t bytesToWrite = std::min(fileSize - bytesWritten, BlockSize);

            std::generate_n(std::back_inserter(randomData), bytesToWrite, entropySource);

            // Write the data.
            fwrite(randomData.data(), 1, randomData.size(), fp);

            // Update statistics.
            bytesWritten += bytesToWrite;
            randomData.clear();
        }
    }
    else
    {
        throw OperationException(errorMessage);
    }
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

