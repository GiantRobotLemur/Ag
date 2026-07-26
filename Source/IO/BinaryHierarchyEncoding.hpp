//! @file IO/BinaryHierarchyEncoding.hpp
//! @brief The declaration of internal functions useful for encoding an
//! object hierarchy as a stream of bytes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_BINARY_HIERARCHY_ENCODING_HPP_
#define HEADER_IO_BINARY_HIERARCHY_ENCODING_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "Ag/IO/ISeekableStream.hpp"
#include "ReadOnlyDataSource.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Data Type Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief Expresses the type of hierarchy field which is encoded in the bytes
//! which follow the value.
//! @remarks This encoding scheme is compatible with the C#
//! Nase.Helper.HierarchySerialization binary hierarchy encoding format.
enum class FieldType : uint8_t
{
    //! @brief Encodes a non-negative integer value between 0 and 15 as a single byte.
    TinyInt,

    //! @brief Indicates that a positive integer is encoded.
    //! @remarks
    //! The value is combined with a count of little-endian encoded bytes minus
    //! one which follow to encode the actual value.
    PositiveInteger,

    //! @brief Indicates that a negative integer is encoded.
    //! @remarks The value is combined with a count of the bytes that follow,
    //! which little-endian encode the binary compliment of the significant bits
    //! of the 2s compliment number.
    NegativeInteger,

    //! @brief Indicates that a floating-point value follows.
    //! @remarks The value is combine an indicator of the type of value which
    //! follows:
    //! - 0 - A CLR Half value (2 bytes)
    //! - 1 - A single precision float (4 bytes)
    //! - 2 - A double precision double (8 bytes)
    //! - 3 - A CLR decimal value (16 bytes)
    Real,

    //! @brief Indicates that an array of raw bytes follows.
    //! @remarks The value is combined with a count of bytes which give the
    //! little-endian-encoded significant bits of the count of bytes in
    //! the block of unformatted data which follows.
    Bytes,

    //! @brief Indicates that an identifier of a string follows.
    //! @remarks The value is combined with a count of bytes which give the
    //! little-endian-encoded significant bits of the numeric string identifier.
    StringID,

    //! @brief Indicates that a serialized object follows.
    //! @remarks The value is combined with a count of bytes which give the
    //! little-endian-encoded significant bits of the count of bytes in
    //! the block of object data which follows.
    //! 
    //! The object data is encoded as pairs of fields, a string giving the
    //! identifier of the field (the tag) and the field data.
    Object,

    //! @brief Indicates that a serialized array follows.
    //! @remarks The value is combined with a count of bytes which give the
    //! little-endian-encoded significant bits of the count of bytes in
    //! the block of array data which follows.
    //! 
    //! The first value in the array is always an anonymously encoded
    //! size value giving the, up to 64-bit, count of elements in the array.
    Array,
};

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief A structure representing the header fields of a binary hierarchy.
struct BinaryStreamHeader
{
    // Public Fields
    static constexpr uint32_t ExpectedSignature = 0x72694842;
    static constexpr uint32_t MinFormatVersion = 1;
    static constexpr uint32_t CurrentFormatVersion = 1;

    uint32_t Signature;
    uint32_t Version;
    uint32_t Flags;
    uint32_t SymbolCount;
    int64_t SymbolTableSize;
    int64_t CompressedSymbolTableSize;
    int64_t PayloadSize;
    int64_t CompressedPayloadSize;

    // Construction/Destruction
    BinaryStreamHeader();
    ~BinaryStreamHeader() = default;

    // Operations
    bool isValid() const;
    bool isValid(Ag::String &error) const;
    void validate() const;
    bool tryRead(IStream *input);
    bool tryWrite(IStream *output);
};

class ReadOnlyDataSource;

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
size_t readSize(IStream *stream, const Bin::ByteOrder *encoding);
StreamLength readStreamSize(IStream *stream, const Bin::ByteOrder *encoding);
StreamLength readStreamSize(ReadOnlyDataSource *source, const StreamRegion &region,
                            int &bytesUsed);
StreamLength writeStreamSize(IStream *stream, StreamLength length);

uint8_t makeFieldHeader(FieldType fieldType, uint8_t supplemental);
StreamLength readFieldHeader(ReadOnlyDataSource *source, const StreamRegion &region,
                             FieldType &fieldType, StreamRegion &fieldRegion);
bool tryReadEncodedStringID(ReadOnlyDataSource *source,
                            const StreamRegion &region, uint32_t &id);
uint32_t readEncodedStringID(ReadOnlyDataSource *source, const StreamRegion &region);

bool tryReadReal(ReadOnlyDataSource *source, const StreamRegion &region, float &value);
bool tryReadReal(ReadOnlyDataSource *source, const StreamRegion &region, double &value);

void writeRealField(IStream *output, float value);
void writeRealField(IStream *output, double value);
void writeArrayHeader(IStream *output, StreamLength dataSize, StreamLength elementCount);
void writeObjectHeader(IStream *output, StreamLength dataSize);
void writeStringField(IStream *output, uint32_t stringID);
void writeByteFieldHeader(IStream *output, StreamLength size);

////////////////////////////////////////////////////////////////////////////////
// Templates
////////////////////////////////////////////////////////////////////////////////

//! @brief Attempts to read an binary-encoded integer from a data source.
//! @tparam T The data type of the integer to read.
//! @param[in] source The data source to read from.
//! @param[in] fieldType The data type of the field.
//! @param[in] fieldData The region of the data source in which the value is encoded.
//! @param[out] value Receives the value, if read successfully.
//! @retval true The value was successfully interpreted.
//! @retval false The value could not be read or the data could not be properly
//! interpreted as the required data type.
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
bool tryReadInteger(ReadOnlyDataSource *source, FieldType fieldType,
                    const StreamRegion &fieldData, T &value)
{
    using IntType = T;
    using IntLimits = std::numeric_limits<IntType>;
    constexpr IntType Zero = static_cast<IntType>(0);

    StreamRegion safeField = fieldData.maxLength(16);
    uint8_t buffer[16];
    bool canRead = false;

    switch (fieldType)
    {
    case FieldType::TinyInt:
        if (source->tryReadByte(fieldData.getOffset(), buffer[0]))
        {
            value = static_cast<IntType>(buffer[0] & 0x0F);

            canRead = true;
        }
        break;

    case FieldType::PositiveInteger:
        if (source->tryRead(safeField, buffer))
        {
            value = Zero;
            uint8_t len = static_cast<uint8_t>(safeField.getLength());

            // Re-assemble the value.
            for (uint8_t i = 0; i < len; ++i)
                value |= static_cast<IntType>(buffer[i]) << (i * 8);

            canRead = true;
        }
        break;

    case FieldType::NegativeInteger:
        // If the data type is not signed, a negative value will always
        // be invalid.
        if constexpr (IntLimits::is_signed)
        {
            using UnsignedInt = std::make_unsigned_t<T>;

            if (source->tryRead(safeField, buffer))
            {
                // We need to manipulate the bits as a raw unsigned value
                // before complimenting them and casting to the signed type.
                UnsignedInt rawValue = static_cast<UnsignedInt>(0);
                uint8_t len = static_cast<uint8_t>(safeField.getLength());

                // Re-assemble the value - negating each byte first.
                for (uint8_t i = 0; i < len; ++i)
                {
                    rawValue |= static_cast<UnsignedInt>(buffer[i]) << (i * 8);
                }

                // Only make the value signed once we have all the bits.
                value = static_cast<T>(~rawValue);

                canRead = true;
            }
        }
        break;

    default:
        canRead = false;
        break;
    }

    return canRead;
}

//! @brief Encodes an integer value and writes it to a stream.
//! @tparam T The data type of the integer to encode.
//! @param[in] output The stream to write the encoding out to.
//! @param[in] value The integer value to write.
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void writeInteger(IStream *output, T value)
{
    using IntType = T;
    using IntLimits = std::numeric_limits<IntType>;
    constexpr IntType Zero = static_cast<IntType>(0);
    constexpr IntType TinyMax = static_cast<IntType>(15);

    // Determine what type to write the value out as.
    FieldType encodingType = FieldType::TinyInt;

    if constexpr (IntLimits::is_signed)
    {
        if (value < 0)
        {
            encodingType = FieldType::NegativeInteger;
            value = ~value;
        }
        else if (value > TinyMax)
        {
            encodingType = FieldType::PositiveInteger;
        }
    }
    else if (value > TinyMax)
    {
        encodingType = FieldType::PositiveInteger;
    }

    uint8_t buffer[17];
    size_t bufferUsed = 1;

    if (encodingType == FieldType::TinyInt)
    {
        // Encode the value with the header.
        buffer[0] = (toScalar(FieldType::TinyInt) << 4) |
                    static_cast<uint8_t>(value);
    }
    else
    {
        while (value != Zero)
        {
            buffer[bufferUsed++] = static_cast<uint8_t>(value);
            value >>= 8;
        }

        // Write the header now that we know how long the encoding is.
        buffer[0] = (toScalar(encodingType) << 4) |
                    static_cast<uint8_t>(bufferUsed - 1);
    }

    size_t bytesWritten = output->write(buffer, bufferUsed);

    if (bytesWritten != bufferUsed)
        throw IOException("Failed to write binary encoded integer value.");
}

//! @brief Reads a binary-encoded floating point value from a data source,
//! assuming the header has already been read.
//! @tparam T The floating point value to read.
//! @param[in] source The data source to read from.
//! @param[in] region The location of the field in the data source.
//! @param[out] value Receives the value read from the data source on success.
//! @retval true The value was successfully read.
//! @retval false The value could not be read.
template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
bool tryReadRealEncoding(ReadOnlyDataSource *source, const StreamRegion &region, T &value)
{
    // Read the raw bits of the floating point value, allowing for byte order.
    using RealType = T;
    using RealLimits = std::numeric_limits<RealType>;
    constexpr RealType Zero = static_cast<RealType>(0);

    if (region.getLength() != static_cast<StreamLength>(sizeof(T)))
        return false;

    uint8_t buffer[sizeof(T)];

    if (source->tryRead(region, buffer))
    {
        if (Ag::Bin::ByteOrder::getLittleEndian()->requiresSwap())
            std::reverse(buffer, buffer + sizeof(T));

        value = *reinterpret_cast<const T *>(buffer);

        return true;
    }

    value = Zero;
    return false;
}

//! @brief Encodes a floating point header and value to a stream.
//! @tparam T The data type of the floating point value to encode.
//! @param[in] output The stream to write the header and value to.
//! @param[in] value The value to encode.
template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
void writeReal(IStream *output, T value)
{
    using RealType = T;
    using RealLimits = std::numeric_limits<RealType>;

    uint8_t buffer[sizeof(RealType) + 1];

    int supplement = Bin::log2(sizeof(value), true) - 1;
    buffer[0] = (toScalar(FieldType::Real) << 4) |
                static_cast<uint8_t>(supplement);

    memcpy(buffer + 1, &value, sizeof(RealType));

    if (Bin::ByteOrder::getLittleEndian()->requiresSwap())
        std::reverse(buffer + 1, buffer + sizeof(RealType) + 1);

    size_t bytesWritten = output->write(buffer, std::size(buffer));

    if (bytesWritten != std::size(buffer))
        throw IOException("Failed to encode real value in an output stream.");
}

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
