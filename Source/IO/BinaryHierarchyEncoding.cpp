//! @file IO/BinaryHierarchyEncoding.cpp
//! @brief The definition of internal functions useful for encoding an
//! object hierarchy as a stream of bytes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include <Ag/Core.hpp>

#include "Ag/IO/Exceptions.hpp"
#include "Ag/IO/ISeekableStream.hpp"
#include "Ag/IO/BufferedOutputStream.hpp"

#include "BinaryHierarchyEncoding.hpp"
#include "ReadOnlyDataSource.hpp"

namespace Ag {
namespace IO {

namespace {

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
//! @brief The value beyond which a size cannot be encoded as a single byte.
constexpr uint8_t SizeEncodingThreshold = 248;

////////////////////////////////////////////////////////////////////////////////
// Local Functions
////////////////////////////////////////////////////////////////////////////////
//! @brief Reads a size value which appears after a header byte encoding its length.
//! @param[in] source The data source to read the size from.
//! @param[in] region The position and size of the encoding to read.
//! @returns The size decoded from @p source.
//! @throws ArgumentException Thrown if @p region is larger than any possible size.
StreamLength readEncodedSize(ReadOnlyDataSource *source, const StreamRegion &region)
{
    uint8_t byteCount[sizeof(StreamLength)];

    if (region.getLength() > static_cast<StreamLength>(sizeof(StreamLength)))
        throw ArgumentException("The size field region is too large.", "region");

    source->readExactly(region, byteCount);

    StreamLength value = 0;
    size_t sizeByteCount = static_cast<size_t>(region.getLength());

    // Restore the value from its little endian encoding.
    for (size_t i = 0; i < sizeByteCount; ++i)
        value |= static_cast<StreamLength>(byteCount[i]) << (i * 8);

    return value;
}

//! @brief Calculates how many bytes it would take to encode a size value which
//! was not part of a field header (a stream size).
//! @param[in] sizeToEncode The size value to encode.
//! @return The count of bytes required to encode the size.
int calculateSizeOfAnonSizeEncoding(StreamLength sizeToEncode)
{
    // Determine the minimum number of bytes needed to encode the value.
    uint64_t rawSize = static_cast<uint64_t>(sizeToEncode);
    int msb;

    if (Bin::bitScanReverse(rawSize, msb))
    {
        if (sizeToEncode >= SizeEncodingThreshold)
        {
            // We have to encode the value as a header byte and some data bytes.
            int significantBits = msb + 1;
            int significantBytes = std::max((significantBits + 7) / 8, 1);

            return significantBytes + 1;
        }
        else
        {
            // We can encode the data as a single byte.
            return 1;
        }
    }
    else
    {
        // The size is zero. We can encode that as a single zero byte.
        return 1;
    }
}

//! @brief Writes a header and size field.
//! @param[in] output The output stream to write the header/size to.
//! @param[in] fieldType The data type to write to the header.
//! @param[in] ordinal The size to encode after the header.
void writeOrdinalField(IStream *output, FieldType fieldType, StreamLength ordinal)
{
    // Determine the minimum number of bytes needed to encode the value.
    uint64_t rawSize = static_cast<uint64_t>(ordinal);

    // We have to encode the value as a header byte and some data bytes.
    uint8_t buffer[16];
    size_t significantBytes = 0;

    // Encode the significant bytes of the ordinal in lsb-first order.
    while (rawSize != 0)
    {
        buffer[significantBytes + 1] = static_cast<uint8_t>(rawSize);
        ++significantBytes;
        rawSize >>= 8;
    }

    // Encode the header once we know how many significant bytes there were.
    buffer[0] = (toScalar(fieldType) << 4) |
        static_cast<uint8_t>(significantBytes & 0x0F);

    // Write the header all in one go.
    output->write(buffer, static_cast<size_t>(significantBytes + 1));
}

//! @brief Determines if a value can be converted to another data type without
//! loss of precision.
//! @tparam TVia The data type to convert to.
//! @tparam TLhs The data type of the original value.
//! @param[in] lhs The value to test.
//! @retval true The value @p lhs can be converted to type @p TVia without any
//! loss of information.
//! @retval false Information is lost when converting @p value to @p TVia.
template<typename TVia, typename TLhs>
bool canRoundTrip(TLhs lhs)
{
    TVia testValue = static_cast<TVia>(lhs);
    TLhs roundTrip = static_cast<TLhs>(testValue);

    return (roundTrip == lhs);
}

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// BinaryStreamHeader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs a new header in an empty state.
BinaryStreamHeader::BinaryStreamHeader() :
    Signature(0),
    Version(0),
    Flags(0),
    SymbolCount(0),
    SymbolTableSize(0),
    CompressedSymbolTableSize(-1),
    PayloadSize(0),
    CompressedPayloadSize(-1)
{
}

//! @brief Determines if the contents of the header are valid.
//! @retval true The header contains valid values.
//! @retval false The header contains invalid values.
bool BinaryStreamHeader::isValid() const
{
    Ag::String error;

    return isValid(error);
}

//! @brief Determines if the contents of the header are valid.
//! @param[out] error Receives details of the issue discovered if the header
//! is invalid.
//! @retval true The header contains valid values.
//! @retval false The header contains invalid values, @p error has been updated
//! to describe why.
bool BinaryStreamHeader::isValid(Ag::String &error) const
{
    error = Ag::String::Empty;

    if (Signature != BinaryStreamHeader::ExpectedSignature)
        error = "The binary stream signature is invalid.";

    else if ((Version < BinaryStreamHeader::MinFormatVersion) ||
             (Version > BinaryStreamHeader::CurrentFormatVersion))
        error = "The binary stream was not encoded in a recognised format.";

    else if (SymbolTableSize < 0)
        error = "The symbol table size cannot be negative.";

    else if (CompressedSymbolTableSize < 0)
        error = "The compressed symbol table size cannot be negative.";

    else if (PayloadSize < 0)
        error = "The payload size cannot be negative.";

    else if (CompressedPayloadSize < 0)
        error = "The compressed payload size cannot be negative.";

    return error.isEmpty();
}

//! @brief Ensures that the header is in a valid state.
//! @throws DataFormatException Thrown if the header is not in a valid state.
void BinaryStreamHeader::validate() const
{
    Ag::String error;

    if (isValid(error) == false)
        throw DataFormatException(error.toUtf8View());
}

//! @brief Attempts to read the header from a binary stream.
//! @param[in] input The stream to read from.
//! @retval true Enough bytes were read to populate the header.
//! @retval false There were not enough bytes in the stream to populate the header.
bool BinaryStreamHeader::tryRead(IStream *input)
{
    auto decoder = Bin::ByteOrder::getLittleEndian();

    uint32_t encodedDword;

    // Read and decode the Signature field.
    if (input->read(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    Signature = decoder->toHost(encodedDword);

    // Read and decode the Version field.
    if (input->read(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    Version = decoder->toHost(encodedDword);

    // Read and decode the Flags field.
    if (input->read(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    Flags = decoder->toHost(encodedDword);

    // Read and decode the Symbol Count field.
    if (input->read(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    SymbolCount = decoder->toHost(encodedDword);

    uint64_t encodedLong;

    // Read and decode the Symbol Table Size field.
    if (input->read(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    SymbolTableSize = static_cast<int64_t>(decoder->toHost(encodedLong));

    // Read and decode the Compressed Symbol Table Size field.
    if (input->read(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    CompressedSymbolTableSize = static_cast<int64_t>(decoder->toHost(encodedLong));

    // Read and decode the Payload Size field.
    if (input->read(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    PayloadSize = static_cast<int64_t>(decoder->toHost(encodedLong));

    // Read and decode the Compressed Payload Size field.
    if (input->read(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    CompressedPayloadSize = static_cast<int64_t>(decoder->toHost(encodedLong));

    return true;
}

//! @brief Attempts to write the header to a binary stream.
//! @param[in] output The stream to write to.
//! @retval true The header was successfully written.
//! @retval false The output stream did not write the entire header.
bool BinaryStreamHeader::tryWrite(IStream *output)
{
    BufferedOutputStream bufferedOutput(output);
    auto encoder = Bin::ByteOrder::getLittleEndian();

    // Encode and store the Signature field.
    uint32_t encodedDword = encoder->toTarget(Signature);

    if (bufferedOutput.write(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    // Encode and store the Version field.
    encodedDword = encoder->toTarget(Version);

    if (bufferedOutput.write(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    // Encode and store the Flags field.
    encodedDword = encoder->toTarget(Flags);

    if (bufferedOutput.write(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    // Encode and store the Symbol Count field.
    encodedDword = encoder->toTarget(SymbolCount);

    if (bufferedOutput.write(&encodedDword, sizeof(encodedDword)) != sizeof(encodedDword))
        return false;

    // Encode and store the Symbol Table Size field.
    uint64_t encodedLong = encoder->toTarget(static_cast<uint64_t>(SymbolTableSize));

    if (bufferedOutput.write(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    // Encode and store the Compressed Symbol Table Size field.
    int64_t sizeValue = (CompressedSymbolTableSize < 0) ? SymbolTableSize :
                                                          CompressedSymbolTableSize;

    encodedLong = encoder->toTarget(static_cast<uint64_t>(sizeValue));

    if (bufferedOutput.write(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    // Encode and store the Payload Size field.
    encodedLong = encoder->toTarget(static_cast<uint64_t>(PayloadSize));

    if (bufferedOutput.write(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    // Encode and store the Compressed Payload Size field.
    sizeValue = (CompressedPayloadSize < 0) ? PayloadSize : CompressedPayloadSize;
    encodedLong = encoder->toTarget(static_cast<uint64_t>(sizeValue));

    if (bufferedOutput.write(&encodedLong, sizeof(encodedLong)) != sizeof(encodedLong))
        return false;

    // Manually flush to allow exceptions to occur.
    bufferedOutput.flush();

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Global Function Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Reads an anonymous byte size value directly from a stream.
//! @param[in] stream The stream to read bytes from.
//! @param[in] encoding The object used to decode serialized values into the
//! proper host byte order.
//! @return The size read from the stream.
//! @throws OperationException If the bytes cannot be read or the size is too large.
size_t readSize(IStream *stream, const Bin::ByteOrder *encoding)
{
    StreamLength streamSize = readStreamSize(stream, encoding);

    return streamToMemorySize(streamSize);
}

//! @brief Reads an anonymous file size value directly from a stream.
//! @param[in] stream The stream to read bytes from.
//! @param[in] encoding The object used to decode serialized values into the
//! proper host byte order.
//! @return The size read from the stream.
StreamLength readStreamSize(IStream *stream, const Bin::ByteOrder *encoding)
{
    uint8_t headerByte;

    if (stream->read(&headerByte, 1) != 1)
        throw IOException("Failed to read size header byte.");

    if (headerByte >= SizeEncodingThreshold)
    {
        // The size was encoded in the bytes which follow.
        size_t byteCount = headerByte - SizeEncodingThreshold + 1;

        uint64_t encodedSize = 0;

        if (stream->read(&encodedSize, byteCount) != byteCount)
            throw IOException("Failed to read size encoding.");

        return static_cast<StreamLength>(encoding->toHost(encodedSize));
    }
    else
    {
        // The header byte was enough.
        return static_cast<StreamLength>(headerByte);
    }
}

//! @brief Reads an anonymous size value from a data source.
//! @param[in] source The data source to read the size value from.
//! @param[in] region The region of the data source to read from.
//! @param[out] bytesUsed Is updated with the count of bytes consumed
//! from the beginning of @p region which encoded the size value.
//! @return The decoded size value.
StreamLength readStreamSize(ReadOnlyDataSource *source,
                            const StreamRegion &region, int &bytesUsed)
{
    uint8_t headerByte;

    if (source->tryReadByte(region.getOffset(), headerByte) == false)
        throw DataFormatException("Failed to read the header byte of an anonymous size.");

    if (headerByte >= SizeEncodingThreshold)
    {
        // The size was encoded in the bytes which follow.
        int byteCount = headerByte - SizeEncodingThreshold + 1;

        uint8_t buffer[sizeof(StreamLength)];

        source->readExactly(region.slice(1, byteCount), buffer);

        // Re-assemble the value from little endian.
        StreamLength value = 0;

        for (int i = 0; i < byteCount; ++i)
            value |= static_cast<StreamLength>(buffer[i]) << (i * 8);

        bytesUsed = byteCount + 1;
        return value;
    }
    else
    {
        // The header byte was enough.
        bytesUsed = 1;

        return static_cast<StreamLength>(headerByte);
    }
}

//! @brief Writes an anonymous size to a stream.
//! @param[in] stream The stream to write to.
//! @param[in] length The size value to write.
//! @returns The count of bytes written to encode @p length in the stream.
StreamLength writeStreamSize(IStream *stream, StreamLength length)
{
    // Determine the minimum number of bytes needed to encode the value.
    uint64_t rawSize = static_cast<uint64_t>(length);

    if (rawSize == 0)
    {
        // The size is zero. We can encode that as a single zero byte.
        uint8_t zero = 0;

        if (stream->write(&zero, 1) != 1)
            throw IOException("Failed to write encoded size.");

        return 1;
    }
    else if (length >= SizeEncodingThreshold)
    {
        // We have to encode the value as a header byte and some data bytes.

        // Encode the header and significant bytes in a single buffer so
        // that we perform a single write operation.
        int significantBytes = 0;
        uint8_t buffer[16];

        while (rawSize != 0)
        {
            buffer[significantBytes + 1] = static_cast<uint8_t>(rawSize);
            ++significantBytes;
            rawSize >>= 8;
        }

        buffer[0] = static_cast<uint8_t>(significantBytes + SizeEncodingThreshold - 1);

        size_t encodingSize = significantBytes + 1;

        if (stream->write(buffer, encodingSize) != encodingSize)
            throw IOException("Failed to write encoded size.");

        return static_cast<StreamLength>(encodingSize);
    }
    else
    {
        // We can encode the data as a single byte.
        uint8_t singleByteEncoding = static_cast<uint8_t>(length);

        if (stream->write(&singleByteEncoding, 1) != 1)
            throw IOException("Failed to write encoded size.");

        return 1;
    }
}

//! @brief Combines a field type with the low nibble of a supplementary value.
//! @param fieldType
//! @param supplemental
//! @return
uint8_t makeFieldHeader(FieldType fieldType, uint8_t supplemental)
{
    return (toScalar(fieldType) << 4) | (supplemental & 0x0F);
}

//! @brief Reads the header of a serialized field.
//! @param[in] source The source to read the data from.
//! @param[in] region The region of @p source starting at the field header.
//! @param[out] fieldType Receives the decoded field type.
//! @param[out] fieldRegion Receives the position and size of the field data
//! in @p source.
//! @return The number of bytes required to encode the field header on success,
//! a negative value on failure.
//! @remarks
//! The field header and field data region may overlap.
StreamLength readFieldHeader(ReadOnlyDataSource *source, const StreamRegion &region,
                             FieldType &fieldType, StreamRegion &fieldRegion)
{
    if (source == nullptr)
        return -1;

    uint8_t headerByte;

    if (source->tryReadByte(region.getOffset(), headerByte) == false)
        return -1;

    StreamLength overallLength = 1;
    fieldType = fromScalar<FieldType>(headerByte >> 4);
    uint8_t supplemental = headerByte & 0x0F;

    switch (fieldType)
    {
    case FieldType::TinyInt:
        fieldRegion = region.slice(0, 1);
        break;

    case FieldType::PositiveInteger:
    case FieldType::NegativeInteger:
    case FieldType::StringID:
        fieldRegion = region.slice(1, supplemental);
        overallLength += supplemental;
        break;

    case FieldType::Real:
        if (supplemental <= 3)
        {
            fieldRegion = region.slice(1, static_cast<StreamLength>(1) << (supplemental + 1));
            overallLength += fieldRegion.getLength();
        }
        else
        {
            overallLength = -1;
        }
        break;

    case FieldType::Bytes:
    case FieldType::Object:
    case FieldType::Array:
        // The header is immediately followed by the little-endian encoded
        // most-significant bytes of the object size.
        if ((supplemental + 1) <= region.getLength())
        {
            StreamLength length = readEncodedSize(source, region.slice(1, supplemental));

            fieldRegion = region.slice(supplemental + 1, length);
            overallLength = supplemental + 1;
        }
        else
        {
            // There aren't enough bytes for the value which follows.
            overallLength = -1;
        }
        break;

    default:
        // Unknown field type.
        overallLength = -1;
        break;
    }

    return overallLength;
}

//! @brief Attempts to read an encoded string identifier.
//! @param[in] source The data source to read from.
//! @param[in] region The region of @p source to read the ID from.
//! @param[out] id Receives the string ID decoded.
//! @retval true The string identifier was successfully read.
//! @retval false The @p region was too big or small for the identifier data.
bool tryReadEncodedStringID(ReadOnlyDataSource *source,
                            const StreamRegion &region, uint32_t &id)
{
    if (region.getLength() > static_cast<StreamLength>(sizeof(uint32_t)))
        return false;

    // String IDs are encoded the same way as sizes, just cut down the result.
    StreamLength length = readEncodedSize(source, region);

    id = static_cast<uint32_t>(length);

    return true;
}

//! @brief Reads an encoded string identifier.
//! @param[in] source The data source to read from.
//! @param[in] region The region of @p source to read the ID from.
//! @return The string ID decoded.
uint32_t readEncodedStringID(ReadOnlyDataSource *source, const StreamRegion &region)
{
    if (region.getLength() > static_cast<StreamLength>(sizeof(uint32_t)))
        throw ArgumentException("The region is too large for a string ID.", "region");

    // String IDs are encoded the same way as sizes, just cut down the result.
    StreamLength length = readEncodedSize(source, region);

    return static_cast<uint32_t>(length);
}

//! @brief Attempts to read a real-encoded value as a 32-bit float.
//! @param[in] source The data source to read the field from.
//! @param[in] region The location of the field within the data source.
//! @param[out] value Receives the value on success.
//! @retval true The value was successfully read and interpreted.
//! @retval false The value could not be interpreted as a float from the
//! data available.
bool tryReadReal(ReadOnlyDataSource *source, const StreamRegion &region, float &value)
{
    if (region.getLength() == 4)
    {
        return tryReadRealEncoding(source, region, value);
    }

    value = 0.0f;
    return false;
}

//! @brief Attempts to read a real-encoded value as a 64-bit double.
//! @param[in] source The data source to read the field from.
//! @param[in] region The location of the field within the data source.
//! @param[out] value Receives the value on success.
//! @retval true The value was successfully read and interpreted.
//! @retval false The value could not be interpreted as a double from the
//! data available.
bool tryReadReal(ReadOnlyDataSource *source, const StreamRegion &region, double &value)
{
    float singleValue;

    if (region.getLength() == 4)
    {
        if (tryReadRealEncoding(source, region, singleValue))
        {
            value = singleValue;
            return true;
        }
    }
    else if (region.getLength() == 8)
    {
        return tryReadRealEncoding(source, region, value);
    }

    value = 0.0;
    return false;
}

//! @brief Writes a float value to the output stream in its most efficient encoding.
//! @param[in] output The output stream to write to.
//! @param[in] value The value to encode.
void writeRealField(IStream *output, float value)
{
    // See if we can write the value as an integer of the same size or less.
    if (canRoundTrip<int32_t>(value))
    {
        writeInteger(output, static_cast<int32_t>(value));
    }
    else
    {
        writeReal(output, value);
    }
}

//! @brief Writes a double value to the output stream in its most efficient encoding.
//! @param[in] output The output stream to write to.
//! @param[in] value The value to encode.
void writeRealField(IStream *output, double value)
{
    // See if we can write the value as an integer of the same size or less.
    if (canRoundTrip<int64_t>(value))
    {
        writeInteger(output, static_cast<int64_t>(value));
    }
    else if (canRoundTrip<float>(value))
    {
        writeReal(output, static_cast<float>(value));
    }
    else
    {
        writeReal(output, value);
    }
}

//! @brief Writes the header of a completed array to an output stream.
//! @param[in] output The stream to write the header to.
//! @param[in] dataSize The count of bytes of array data.
//! @param[in] elementCount The count of elements encoded in the array.
void writeArrayHeader(IStream *output, StreamLength dataSize, StreamLength elementCount)
{
    // The element count is part of the array data payload, and not the header,
    // so we need to account for it.
    dataSize += calculateSizeOfAnonSizeEncoding(elementCount);

    writeOrdinalField(output, FieldType::Array, dataSize);

    // The element count will appear in the header block, but be accounted for
    // as part of the array data.
    writeStreamSize(output, elementCount);
}

//! @brief Writes the header of a completed object to an output stream.
//! @param[in] output The stream to write the header to.
//! @param[in] dataSize The count of bytes of object data.
void writeObjectHeader(IStream *output, StreamLength dataSize)
{
    writeOrdinalField(output, FieldType::Object, dataSize);
}

//! @brief Writes the header and value of a string identifier to an output stream.
//! @param[in] output The stream to write the header to.
//! @param[in] stringID The numeric identifier of the string to write.
void writeStringField(IStream *output, uint32_t stringID)
{
    writeOrdinalField(output, FieldType::StringID,
                      static_cast<StreamLength>(stringID));
}

//! @brief Brief writes the type and size header for a byte block field.
//! @param[in] output The output stream to write to.
//! @param[in] size The count of bytes in the field data which will be written
//! after this header.
void writeByteFieldHeader(IStream *output, StreamLength size)
{
    writeOrdinalField(output, FieldType::Bytes, size);
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

