//! @file IO/BinaryReaderWriters.cpp
//! @brief The definition of implementations of hierarchy reader/writer
//! interfaces which operate on a binary encoding.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Header File Includes
////////////////////////////////////////////////////////////////////////////////
#include "BinaryReaderWriters.hpp"
#include "Ag/IO/Exceptions.hpp"

namespace Ag {
namespace IO {

namespace {
////////////////////////////////////////////////////////////////////////////////
// Local Data Types
////////////////////////////////////////////////////////////////////////////////
//! @brief An IStream implementation which will accumulate the bytes of a byte
//! block field. At destruction it will write a header before the field data
//! describing it.
class ByteBlockFieldStream : public IStream
{
private:
    BinaryWriterRootSPtr _root;
    OutOfOrderStream::BlockRef _fieldBlock;
    OutOfOrderStream::Stream *_innerStream;
public:
    //! @brief Constructs a stream to write a byte block field.
    //! @param[in] root The object managing the hierarchy being serialized.
    ByteBlockFieldStream(const BinaryWriterRootSPtr &root) :
        _root(root),
        _innerStream(_root->getOutput().beginWritingBlock(_fieldBlock))
    {
    }

    //! @brief Ensures that a header is written before the accumulated bytes
    //! of the field.
    virtual ~ByteBlockFieldStream() override
    {
        // Calculate the count of bytes written to the field.
        StreamLength totalLength = _innerStream->endWritingBlock(_fieldBlock);

        // Begin writing a header block which will appear before the field
        // data in the final output stream.
        OutOfOrderStream::Stream *headerStream =
            _root->getOutput().beginWritingBlockBefore(_fieldBlock);

        // Write the header and close it off.
        writeByteFieldHeader(headerStream, totalLength);
        headerStream->closeBlock();
    }

    // Overrides

    // Inherited from IStream.
    virtual bool isBuffered() const override { return _innerStream->isBuffered(); }

    // Inherited from IStream.
    virtual void flush() override { _innerStream->flush(); }

    // Inherited from IStream.
    virtual size_t read(void *targetBuffer, size_t requiredByteCount) override
    {
        return _innerStream->read(targetBuffer, requiredByteCount);
    }

    // Inherited from IStream.
    virtual size_t write(const void *sourceBuffer, size_t sourceByteCount) override
    {
        return _innerStream->write(sourceBuffer, sourceByteCount);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Local Data
////////////////////////////////////////////////////////////////////////////////
const std::string_view TrueText("TRUE");
const std::string_view FalseText("FALSE");
constexpr StreamLength MaxBlockSize = 4 * 1024 * 1024;

} // Anonymous namespace

////////////////////////////////////////////////////////////////////////////////
// BinaryHierarchyRoot Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object used to read a binary serialized hierarchy.
//! @param[in] header The header initially read from the stream.
//! @param[in] input The input stream positioned just after the header.
BinaryHierarchyRoot::BinaryHierarchyRoot(const BinaryStreamHeader &header,
                                         IStream *input) :
    _rootFieldType(FieldType::TinyInt)
{
    if (header.Flags & 1)
    {
        // The string table is compressed, so read it through a stream which
        // will decompress the data.
        Bz2DecompressionStream decompressor(input);

        _symbols = readStringTable(&decompressor, header.SymbolCount);
    }
    else
    {
        // Read the string table directly from the stream.
        _symbols = readStringTable(input, header.SymbolCount);
    }

    // Index the symbols to allow object properties to be indexed by ID.
    uint32_t id = 0;

    for (string_cref_t symbol : _symbols)
        _symbolIDsByText[symbol] = id++;

    // Copy the payload data to a static source (either in memory or to a
    // memory mapped file).
    ReadOnlyDataSourceUPtr sourceData;

    if (header.Flags & 2)
    {
        // The payload is compressed.
        Bz2DecompressionStream decompressor(input);

        // Decompress the payload into the static source.
        _source = ReadOnlyDataSource::create(&decompressor, header.PayloadSize);
    }
    else
    {
        // The payload is uncompressed, read it direct from the input stream.
        _source = ReadOnlyDataSource::create(input, header.PayloadSize);
    }

    // Analyse the root element.
    StreamLength result = readFieldHeader(_source.get(), _source->getRootRegion(),
                                          _rootFieldType, _rootFieldData);

    if (result < 0)
    {
        // Dispose of the data before throwing the exception.
        _source.reset();

        throw DataFormatException("Unable to read root field of serialized hierarchy.");
    }
}

//! @brief Gets the object containing the raw serialized hierarchy data.
ReadOnlyDataSource *BinaryHierarchyRoot::getDataSource() const
{
    return _source.get();
}

//! @brief Attempts to look up a string from an ID.
//! @param[in] id The ID of the string referenced in the hierarchy.
//! @param[out] text Receives the text of the string associated with the ID on success.
//! @retval true The string exists and was returned.
//! @retval false @p id did not represent a string store in the hierarchy.
bool BinaryHierarchyRoot::tryGetString(uint32_t id, Ag::String &text) const
{
    if (id < _symbols.size())
    {
        text = _symbols.at(id);

        return true;
    }

    text = String::Empty;
    return false;
}

//! @brief Attempts to lookup the numeric identifier of a string.
//! @param[in] text The test to look up.
//! @param[out] id Receives the identifier if the text was used in the hierarchy.
//! @retval true @p text was used in the hierarchy and its numeric identifier
//! was returned in @p id.
//! @retval false @p text was not used in the hierarchy.
bool BinaryHierarchyRoot::tryGetStringID(const Ag::String &text, uint32_t &id) const
{
    return tryFindMappedValue(_symbolIDsByText, text, id);
}

//! @brief Attempts to interpret a field as a boolean value.
//! @param[in] fieldType The encoding type of the field.
//! @param[in] fieldData The location of the field data.
//! @param[out] value The value interpreted from the field.
//! @retval true The value was successfully read and interpreted
//! as a boolean value.
//! @retval false The value could not be read or the value could not be
//! interpreted as a boolean value.
bool BinaryHierarchyRoot::tryReadBoolValue(FieldType fieldType,
                                           const StreamRegion &fieldData,
                                           bool &value) const
{
    bool hasValue = false;
    value = false;

    uint32_t stringID;
    uint8_t tinyValue;

    switch (fieldType)
    {
    case FieldType::TinyInt:
        if (IO::tryReadInteger(_source.get(), fieldType, fieldData, tinyValue))
        {
            value = tinyValue != 0;
            hasValue = true;
        }
        break;

    case FieldType::PositiveInteger:
    case FieldType::NegativeInteger:
        // By their very nature, a non-tiny integer cannot be 0 (false).
        value = true;
        hasValue = true;
        break;

    case FieldType::StringID:
        if (tryReadEncodedStringID(_source.get(), fieldData, stringID))
        {
            String textValue;

            if (tryGetString(stringID, textValue))
            {
                if (textValue.compareIgnoreCase(TrueText) == 0)
                {
                    value = true;
                    hasValue = true;
                }
                else if (textValue.compareIgnoreCase(FalseText) == 0)
                {
                    value = false;
                    hasValue = true;
                }
            }
        }
        break;

    default:
        hasValue = false;
        value = false;
        break;
    }

    return hasValue;
}

//! @brief Attempts to interpret a field as a Unicode character value.
//! @param[in] fieldType The encoding type of the field.
//! @param[in] fieldData The location of the field data.
//! @param[out] value The value interpreted from the field.
//! @retval true The value was successfully read and interpreted
//! as a character value.
//! @retval false The value could not be read or the value could not be
//! interpreted as a character value.
bool BinaryHierarchyRoot::tryReadCharValue(FieldType fieldType,
                                           const StreamRegion &fieldData,
                                           char32_t &value) const
{
    uint32_t rawValue;
    bool hasValue = false;
    value = U'\0';

    switch (fieldType)
    {
    case FieldType::TinyInt:
    case FieldType::PositiveInteger:
        if (IO::tryReadInteger(_source.get(), fieldType, fieldData, rawValue))
        {
            value = static_cast<char32_t>(rawValue);
            hasValue = true;
        }
        break;

    case FieldType::StringID:
        if (IO::tryReadEncodedStringID(_source.get(), fieldData, rawValue))
        {
            String textValue;

            if (tryGetString(rawValue, textValue) && (textValue.getUtf32Length() == 1))
            {
                // Interpret the initial bytes of the UTF-8 string as a
                // code point.
                value = *textValue.begin();
                hasValue = true;
            }
        }
        break;

    case FieldType::NegativeInteger:
    case FieldType::Real:
    case FieldType::Bytes:
    case FieldType::Object:
    case FieldType::Array:
    default:
        hasValue = false;
        break;
    }

    return hasValue;
}

// Inherited from HierarchyRootPrivate.
bool BinaryHierarchyRoot::hasRootObject() const
{
    return (_rootFieldType == FieldType::Object);
}

// Inherited from HierarchyRootPrivate.
bool BinaryHierarchyRoot::hasRootArray() const
{
    return (_rootFieldType == FieldType::Array);
}

// Inherited from HierarchyRootPrivate.
IObjectReader *BinaryHierarchyRoot::getRootObject()
{
    if (_rootFieldType == FieldType::Object)
    {
        auto rootPtr = std::dynamic_pointer_cast<BinaryHierarchyRoot>(shared_from_this());

        return new BinaryObjectReader(rootPtr, _rootFieldData);
    }

    throw OperationException("The root of the serialized hierarchy was not an object.");
}

// Inherited from HierarchyRootPrivate.
IArrayReader *BinaryHierarchyRoot::getRootArray()
{
    if (_rootFieldType == FieldType::Array)
    {
        auto rootPtr = std::dynamic_pointer_cast<BinaryHierarchyRoot>(shared_from_this());

        return new BinaryArrayReader(rootPtr, _rootFieldData);
    }

    throw OperationException("The root of the serialized hierarchy was not an array.");
}

//! @brief Reads a string table from a stream.
//! @param[in] stream The stream to read from, positioned at the beginning of
//! the string table.
//! @param[in] stringCount The count of strings to read.
//! @returns A collection of strings in the order in which they were read in.
StringCollection BinaryHierarchyRoot::readStringTable(IStream *stream, size_t stringCount)
{
    auto encoding = Bin::ByteOrder::getLittleEndian();
    StringCollection symbols;
    std::vector<char> buffer;

    symbols.reserve(stringCount);
    buffer.reserve(64);

    for (size_t i = 0; i < stringCount; ++i)
    {
        size_t utf8ByteCount = readSize(stream, encoding);

        if (utf8ByteCount > 0)
        {
            Ag::ensureCapacity(buffer, utf8ByteCount);
            buffer.resize(utf8ByteCount);

            size_t bytesRead = stream->read(buffer.data(), utf8ByteCount);

            if (bytesRead != utf8ByteCount)
                throw IOException("Failed to read hierarchy string value.");

            // Create a string from the bounded buffer.
            symbols.emplace_back(buffer.data(), utf8ByteCount);
        }
        else
        {
            // The string is empty.
            symbols.emplace_back();
        }
    }

    return symbols;
}

////////////////////////////////////////////////////////////////////////////////
// BinaryArrayReader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to read a binary-encoded array.
//! @param[in] root The root of the hierarchy containing the array.
//! @param[in] region The region of the data containing the serialized elements
//! of the array, positioned just after the field header.
BinaryArrayReader::BinaryArrayReader(const BinaryHierarchyRootSPtr &root,
                                     const StreamRegion &region) :
    _root(root),
    _elementCount(0),
    _currentElement(0),
    _currentOffset(0)
{
    int bytesUsed = 0;
    _elementCount = readStreamSize(root->getDataSource(), region, bytesUsed);

    _data = region.slice(bytesUsed);
}

// Inherited from IArrayReader.
bool BinaryArrayReader::hasMore() const
{
    return _currentElement < _elementCount;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryGetNextElementSize(StreamLength &elementSize) const
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData))
    {
        elementSize = fieldData.getLength();

        return true;
    }

    elementSize = -1;
    return false;
}

// Inherited from IArrayReader.
StreamLength BinaryArrayReader::getElementCount() const
{
    return _elementCount;
}

// Inherited from IArrayReader.
StreamPosition BinaryArrayReader::getCurrentElementIndex() const
{
    return _currentElement;
}

// Inherited from IArrayReader.
void BinaryArrayReader::reset()
{
    _currentElement = 0;
    _currentOffset = 0;
}

// Inherited from IArrayReader.
void BinaryArrayReader::skip(StreamLength count)
{
    if (count < 0)
        throw ArgumentException("The count of elements to skip cannot be negative.",
                                "count");

    if (count == 0)
        return;

    StreamLength targetElement = _currentElement + count;

    if (targetElement > _elementCount)
        throw ArgumentException("The count of elements to skip is out of range.",
                                "count");

    StreamRegion nextRegion;
    FieldType fieldType;

    while (_currentElement < targetElement)
    {
        if (tryGetNextField(fieldType, nextRegion))
        {
            commitField(nextRegion);
        }
        else
        {
            std::string message("Failed to decode element #");
            appendValue(FormatInfo::getDisplay(), message, _currentElement);
            message.push_back('.');

            throw DataFormatException(message);
        }
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(bool &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadBoolValue(fieldType, fieldData, value))
    {
        commitField(fieldData);
        return true;
    }

    value = false;
    return false;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(int8_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(uint8_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(int16_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(uint16_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(int32_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(uint32_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(int64_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(uint64_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadInteger(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(char32_t &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    // A Unicode code point is encoded as a 32-bit integer.
    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadCharValue(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = U'\0';

        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(float &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadReal(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0.0f;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(double &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        _root->tryReadReal(fieldType, fieldData, value))
    {
        commitField(fieldData);

        return true;
    }
    else
    {
        value = 0.0;
        return false;
    }
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(String &value)
{
    StreamRegion fieldData;
    uint32_t stringID;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        (fieldType == FieldType::StringID) &&
        tryReadEncodedStringID(_root->getDataSource(), fieldData, stringID) &&
        _root->tryGetString(stringID, value))
    {
        commitField(fieldData);

        return true;
    }

    value = String::Empty;
    return false;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(ByteBlock &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        (fieldType == FieldType::Bytes))
    {
        if (fieldData.getLength() > MaxBlockSize)
            throw FieldTooBigException(fieldData.getLength());

        size_t byteCount = static_cast<size_t>(fieldData.getLength());

        Ag::ensureCapacity(value, byteCount);
        value.resize(byteCount);

        if (_root->getDataSource()->tryRead(fieldData, value.data()))
        {
            // Move past the field once successfully read.
            commitField(fieldData);

            return true;
        }
    }

    value.clear();
    return false;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(ISeekableStreamUPtr &value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        (fieldType == FieldType::Bytes))
    {
        value = _root->getDataSource()->readStream(fieldData);

        // Mark the field as read so that we can move past it.
        commitField(fieldData);

        return true;
    }

    value.reset();
    return false;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(IObjectReader *&value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        (fieldType == FieldType::Object))
    {
        value = new BinaryObjectReader(_root, fieldData);

        // Mark the field as read so that we can move past it.
        commitField(fieldData);

        return true;
    }

    value = nullptr;
    return false;
}

// Inherited from IArrayReader.
bool BinaryArrayReader::tryReadNext(IArrayReader *&value)
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetNextField(fieldType, fieldData) &&
        (fieldType == FieldType::Array))
    {
        value = new BinaryArrayReader(_root, fieldData);

        // Mark the field as read so that we can move past it.
        commitField(fieldData);

        return true;
    }

    value = nullptr;
    return false;
}

//! @brief Attempts to get the field type and data location of the next
//! element of the array to be read.
//! @param[out] fieldType Receives the data type of the next field.
//! @param[out] fieldData Receives the location of the data of the next field.
//! @retval true There was another element and its type and position were returned.
//! @retval false There were no more elements, or the next element could not be
//! decoded.
bool BinaryArrayReader::tryGetNextField(FieldType &fieldType,
                                        StreamRegion &fieldData) const
{
    StreamRegion nextRegion = _data.slice(_currentOffset);

    return (_currentElement < _elementCount) &&
           (readFieldHeader(_root->getDataSource(), nextRegion,
                            fieldType, fieldData) >= 0);
}

//! @brief Moves past the next field.
//! @param[in] fieldData The field data for the field to move past.
void BinaryArrayReader::commitField(StreamRegion &fieldData)
{
    ++_currentElement;
    _currentOffset = fieldData.getEnd() - _data.getOffset();
}

////////////////////////////////////////////////////////////////////////////////
// BinaryObjectReader Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object to read an object serialized as binary data.
//! @param[in] root The object holding the entire binary encoded hierarchy.
//! @param[in] region The region of the serialized data encompassing the
//! object data.
BinaryObjectReader::BinaryObjectReader(const BinaryHierarchyRootSPtr &root,
                                       const StreamRegion &region) :
    _root(root)
{
    // The serialized object properties are encoded as string/value pairs.
    //
    // Index the regions of field data by their tags.
    StreamRegion objData = region;
    ReadOnlyDataSource *dataSource = root->getDataSource();

    while (objData.getLength() > 0)
    {
        // Read the property tag.
        StreamRegion tagData;
        FieldType tagType;

        StreamLength headerLength = readFieldHeader(dataSource, objData,
                                                    tagType, tagData);

        if ((headerLength <= 0) || (tagType != FieldType::StringID))
            throw DataFormatException("Unable to read object property tag.");

        // Read the field header to get an idea of how big it is.
        StreamRegion fieldValue;
        StreamLength tagLength = tagData.getEnd() - objData.getOffset();
        StreamPosition fieldValueOffset = objData.getOffset() + tagLength;
        uint32_t tagID = readEncodedStringID(dataSource, tagData);
        FieldType fieldType;

        headerLength = readFieldHeader(dataSource, objData.slice(tagLength),
                                       fieldType, fieldValue);

        if (headerLength <= 0)
            throw DataFormatException("Unable to read object property value header.");

        // Ensure the field data region encompasses the field header.
        StreamRegion fieldData(fieldValueOffset, fieldValue.getEnd() - fieldValueOffset);

        _regionsByTagID.push_back(tagID, fieldData);

        // Calculate the length of the entire property tag and value.
        StreamLength propertyLength = fieldData.getEnd() - objData.getOffset();

        // Move on to the next property.
        objData = objData.slice(propertyLength);
    }

    // Create an immutable index of ID to property.
    _regionsByTagID.reindex(true);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::hasProperty(string_cref_t tag) const
{
    uint32_t tagID;
    return _root->tryGetStringID(tag, tagID) &&
        _regionsByTagID.containsKey(tagID);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryGetPropertySize(string_cref_t tag,
                                            StreamLength &propSize) const
{
    StreamRegion fieldData;
    FieldType fieldType;

    if (tryGetFieldValue(tag, fieldType, fieldData))
    {
        propSize = fieldData.getLength();

        return true;
    }

    propSize = -1;
    return false;
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, bool &value) const
{
    StreamRegion fieldData;
    FieldType fieldType;
    value = false;

    return tryGetFieldValue(tag, fieldType, fieldData) &&
           _root->tryReadBoolValue(fieldType, fieldData, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, int8_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, uint8_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, int16_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, uint16_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, int32_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, uint32_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, int64_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, uint64_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadInteger(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, char32_t &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadCharValue(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, float &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadReal(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, double &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           _root->tryReadReal(fieldType, fieldValue, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, String &value) const
{
    StreamRegion fieldValue;
    uint32_t id;
    FieldType fieldType;

    auto dataSource = _root->getDataSource();

    // Get the field header + value, verify the type is a string, read the
    // value of the string ID, look up the string ID.
    return tryGetFieldValue(tag, fieldType, fieldValue) &&
           (fieldType == FieldType::StringID) &&
           tryReadEncodedStringID(dataSource, fieldValue, id) &&
           _root->tryGetString(id, value);
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, ByteBlock &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    if (tryGetFieldValue(tag, fieldType, fieldValue) &&
        (fieldType == FieldType::Bytes))
    {
        if (fieldValue.getLength() > MaxBlockSize)
            throw FieldTooBigException(fieldValue.getLength());

        size_t byteCount = static_cast<size_t>(fieldValue.getLength());
        value.resize(byteCount);

        return _root->getDataSource()->tryRead(fieldValue, value.data());
    }

    value.clear();
    return false;
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, ISeekableStreamUPtr &value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    if (tryGetFieldValue(tag, fieldType, fieldValue) &&
        (fieldType == FieldType::Bytes))
    {
        value = _root->getDataSource()->readStream(fieldValue);

        return true;
    }

    value.reset();
    return false;
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, IObjectReader *&value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    if (tryGetFieldValue(tag, fieldType, fieldValue) &&
        (fieldType == FieldType::Object))
    {
        value = new BinaryObjectReader(_root, fieldValue);

        return true;
    }

    value = nullptr;
    return false;
}

// Inherited from IObjectReader.
bool BinaryObjectReader::tryRead(string_cref_t tag, IArrayReader *&value) const
{
    StreamRegion fieldValue;
    FieldType fieldType;

    if (tryGetFieldValue(tag, fieldType, fieldValue) &&
        (fieldType == FieldType::Array))
    {
        value = new BinaryArrayReader(_root, fieldValue);

        return true;
    }

    value = nullptr;
    return false;
}

//! @brief Attempts to find the serialized data associated with a property.
//! @param[in] tag The identifier if the property.
//! @param[out] fieldData Receives the range within the stream containing
//! the field data.
//! @retval true A field with the specified tag was found, and the position of
//! its data was found.
//! @retval false The object did not contain a matching field.
bool BinaryObjectReader::tryFindField(string_cref_t tag, StreamRegion &fieldData) const
{
    uint32_t tagID;

    return _root->tryGetStringID(tag, tagID) &&
           _regionsByTagID.tryFind(tagID, fieldData);
}

//! @brief Attempts to get the header and region for a field value
//! @param[in] tag The tag used to identify the field.
//! @param[out] fieldType Receives the data type of the field.
//! @param[out] fieldValue Receives the region containing the field data.
//! @retval true The field was defined and the header/value returned.
//! @retval false The field was not defined or the header could not be interpreted.
bool BinaryObjectReader::tryGetFieldValue(string_cref_t tag, FieldType &fieldType,
                                          StreamRegion &fieldValue) const
{
    StreamRegion fieldData;
    auto dataSource = _root->getDataSource();
    uint32_t tagID;

    return _root->tryGetStringID(tag, tagID) &&
           _regionsByTagID.tryFind(tagID, fieldData) &&
           (readFieldHeader(dataSource, fieldData, fieldType, fieldValue) >= 0);
}

////////////////////////////////////////////////////////////////////////////////
// BinaryArrayWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Constructs an object which manages accumulating a hierarchy of
//! serialized data.
//! @param[in] output The stream the hierarchy will eventually be written to.
//! @param[in] rootWriter A pointer to the root BinaryArrayWriter or
//! BinaryObjectWriter.
BinaryWriterRoot::BinaryWriterRoot(ISeekableStream *output, const void *rootWriter,
                                   bool compress) :
    _output(output),
    _rootWriter(reinterpret_cast<uintptr_t>(rootWriter)),
    _compress(compress)
{
    // Stoke the string table with the empty string.
    _symbols.emplace_back();
    _symbolIDByValue[_symbols.back()] = 0;
}

//! @brief Determines if an object is the root writer.
//! @param[in] ptr A pointer to a BinaryArrayWriter or BinaryObjectWriter.
//! @retval true The instance passed as @p ptr was the root writer object.
//! @retval false The pointer passed to a more nested writer.
bool BinaryWriterRoot::isRootWriter(const void *ptr) const
{
    return reinterpret_cast<uintptr_t>(ptr) == _rootWriter;
}

//! @brief Gets the object to which hierarchy payload data can be written.
OutOfOrderStream &BinaryWriterRoot::getOutput()
{
    return _payloadStream;
}

//! @brief Gets the unique identifier associated with a string.
//! @param[in] symbol The string to look up.
//! @return The unique identifier associated with @p symbol which can be used
//! to represent it in payload data.
uint32_t BinaryWriterRoot::getStringID(string_cref_t symbol)
{
    auto pos = _symbolIDByValue.find(symbol);

    if (pos == _symbolIDByValue.end())
    {
        // The string hasn't been seen before. Add it to the symbol table and
        // allocate it an ID.
        uint32_t id = static_cast<uint32_t>(_symbols.size());

        _symbols.push_back(symbol);
        _symbolIDByValue[symbol] = id;

        return id;
    }
    else
    {
        // The string was already in the index, returns the ID it already has.
        return pos->second;
    }
}

//! @brief Writes a header, the string table and payload data to the stream
//! passed to the constructor.
void BinaryWriterRoot::write()
{
    BinaryStreamHeader header;
    StreamPosition headerOffset = _output->getPosition();

    // Write out the data of an invalid header, to be overwritten later.
    if (header.tryWrite(_output) == false)
        throw IOException("Failed to write initial hierarchy header.");

    // Start initialising the header with proper values.
    header.Signature = BinaryStreamHeader::ExpectedSignature;
    header.Version = BinaryStreamHeader::CurrentFormatVersion;
    header.SymbolCount = static_cast<uint32_t>(_symbols.size());

    if (_compress)
    {
        // Compress the string table data and write after the header.
        StreamPosition stringTableOffset = _output->getPosition();
        Bz2CompressionStream stringCompressor(_output);

        header.SymbolTableSize = writeStringTable(&stringCompressor);
        header.CompressedSymbolTableSize = _output->getPosition() - stringTableOffset;

        header.Flags |= 1;
    }
    else if (_output->isBuffered())
    {
        // Write the string table directly after the header.
        header.SymbolTableSize = writeStringTable(_output);
    }
    else
    {
        // Buffer writes to the output device.
        BufferedOutputStream bufferedOutput(_output);

        header.SymbolTableSize = writeStringTable(&bufferedOutput);

        // Ensure any final write exceptions are thrown.
        bufferedOutput.flush();
    }

    // Allow the string table and payload to be compressed separately.
    if (_compress)
    {
        // Compress the payload to be written after the string table.
        StreamPosition payloadOffset = _output->getPosition();
        Bz2CompressionStream payloadCompressor(_output);

        header.PayloadSize = _payloadStream.orderedWrite(&payloadCompressor);
        header.CompressedPayloadSize = _output->getPosition() - payloadOffset;

        header.Flags |= 2;
    }
    else if (_output->isBuffered())
    {
        // Buffer writes to the output device.
        BufferedOutputStream bufferedOutput(_output);

        header.PayloadSize = _payloadStream.orderedWrite(&bufferedOutput);

        // Ensure any final write exceptions are thrown.
        bufferedOutput.flush();
    }
    else
    {
        // Write the payload directly to the output stream.
        header.PayloadSize = _payloadStream.orderedWrite(_output);
    }

    // Move back to the start of the output stream so that we can write the
    // header with a valid and correct set of values.
    _output->setPosition(StreamRelative::Beginning, headerOffset);

    if (header.tryWrite(_output) == false)
        throw IOException("Failed to write out hierarchy header.");
}

//! @brief Writes the current string table to an output stream as a set of
//! headerless size values followed by the UTF-8 encoding of each string.
//! @param[in] output The stream to write the string table to.
//! @return The count of bytes written to @p output.
StreamLength BinaryWriterRoot::writeStringTable(IStream *output) const
{
    StreamLength bytesWritten = 0;

    for (string_cref_t symbol : _symbols)
    {
        size_t valueByteCount = symbol.getUtf8Length();
        bytesWritten += writeStreamSize(output, static_cast<StreamLength>(valueByteCount));

        if (valueByteCount > 0)
        {
            size_t valueBytesWritten = output->write(symbol.getUtf8Bytes(), valueByteCount);

            if (valueBytesWritten != valueByteCount)
                throw IOException("Failed to write UTF-8 string value.");

            bytesWritten += static_cast<StreamLength>(bytesWritten);
        }
    }

    return bytesWritten;
}

////////////////////////////////////////////////////////////////////////////////
// BinaryArrayWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object to write an array at the root of a serialized
//! hierarchy of data.
//! @param[in] output The stream the hierarchy should be written to when
//! the current object is destroyed.
//! @param[in] compress True to compress the resultant stream, false to store
//! it in its uncompressed from.
BinaryArrayWriter::BinaryArrayWriter(ISeekableStream *output, bool compress) :
    _root(std::make_shared<BinaryWriterRoot>(output, this, compress)),
    _blockWriter(nullptr),
    _elementCount(0)
{
    _blockWriter = _root->getOutput().beginWritingBlock(_payloadBlock);
}

//! @brief Creates an object to write an array nested within a serialized
//! hierarchy of data.
//! @param[in] root The object shared between all writers.
BinaryArrayWriter::BinaryArrayWriter(const BinaryWriterRootSPtr &root) :
    _root(root),
    _blockWriter(nullptr),
    _elementCount(0)
{
    _blockWriter = _root->getOutput().beginWritingBlock(_payloadBlock);
}

//! @brief Ensures the last of the array is written and the hierarchy is streamed
//! out if this was the root writer.
BinaryArrayWriter::~BinaryArrayWriter()
{
    // Write the header of the array.
    StreamLength arraySize = _blockWriter->endWritingBlock(_payloadBlock);

    OutOfOrderStream::BlockRef headerBlock;
    auto headerStream = _root->getOutput().beginWritingBlockBefore(_payloadBlock,
                                                                   headerBlock);

    // Write header fields.
    writeArrayHeader(headerStream, arraySize, _elementCount);

    // Finish header block.
    headerStream->closeBlock();

    // Stream the hierarchy out to the final output stream.
    if (_root && _root->isRootWriter(this))
        _root->write();
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(bool value)
{
    writeInteger(_blockWriter, value ? 1 : 0);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(int8_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(uint8_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(int16_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(uint16_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(int32_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(uint32_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(int64_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(uint64_t value)
{
    writeInteger(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(char32_t value)
{
    writeInteger(_blockWriter, static_cast<uint32_t>(value));

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(float value)
{
    writeRealField(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(double value)
{
    writeRealField(_blockWriter, value);

    ++_elementCount;
}

// Inherited from IArrayWriter.
void BinaryArrayWriter::write(string_cref_t value)
{
    uint32_t stringID = _root->getStringID(value);

    writeStringField(_blockWriter, stringID);
    ++_elementCount;
}
// Inherited from IArrayWriter.
void BinaryArrayWriter::write(const void *value, size_t byteCount)
{
    writeByteFieldHeader(_blockWriter, static_cast<StreamLength>(byteCount));

    if (byteCount > 0)
    {
        size_t bytesWritten = _blockWriter->write(value, byteCount);

        if (bytesWritten != byteCount)
            throw IOException("Failed to encode byte block field.");
    }

    ++_elementCount;
}

// Inherited from IArrayWriter.
IStreamUPtr BinaryArrayWriter::beginWriteBytes()
{
    // Assume we will end up writing another complete element.
    ++_elementCount;

    return IStreamUPtr(new ByteBlockFieldStream(_root));
}

// Inherited from IArrayWriter.
IObjectWriter *BinaryArrayWriter::beginWriteObject()
{
    // Assume we will end up writing another complete element.
    ++_elementCount;

    return new BinaryObjectWriter(_root);
}

// Inherited from IArrayWriter.
IArrayWriter *BinaryArrayWriter::beginWriteArray()
{
    // Assume we will end up writing another complete element.
    ++_elementCount;

    return new BinaryArrayWriter(_root);
}

////////////////////////////////////////////////////////////////////////////////
// BinaryObjectWriter Member Definitions
////////////////////////////////////////////////////////////////////////////////
//! @brief Creates an object to write a property set at the root of a serialized
//! hierarchy of data.
//! @param[in] output The stream the hierarchy should be written to when
//! the current object is destroyed.
//! @param[in] compress True to compress the resultant stream, false to store
//! it in its uncompressed from.
BinaryObjectWriter::BinaryObjectWriter(ISeekableStream *output, bool compress) :
    _root(std::make_shared<BinaryWriterRoot>(output, this, compress))
{
    _blockWriter = _root->getOutput().beginWritingBlock(_payloadBlock);
}

//! @brief Creates an object to write a property set nested within a serialized
//! hierarchy of data.
//! @param[in] root The object shared between all writers.
BinaryObjectWriter::BinaryObjectWriter(const BinaryWriterRootSPtr &root) :
    _root(root)
{
    _blockWriter = _root->getOutput().beginWritingBlock(_payloadBlock);
}

//! @brief Ensures the last of the property set is written and the hierarchy is
//! streamed out if this was the root writer.
BinaryObjectWriter::~BinaryObjectWriter()
{
    // Write the header of the object.
    StreamLength arraySize = _blockWriter->endWritingBlock(_payloadBlock);

    OutOfOrderStream::BlockRef headerBlock;
    auto headerStream = _root->getOutput().beginWritingBlockBefore(_payloadBlock,
                                                                   headerBlock);

    // Write header fields.
    writeObjectHeader(_blockWriter, arraySize);

    // Finish header block.
    headerStream->closeBlock();

    // Stream the hierarchy out to the final output stream.
    if (_root && _root->isRootWriter(this))
        _root->write();
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, bool value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value ? 1 : 0);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, int8_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, uint8_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, int16_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, uint16_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, int32_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, uint32_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, int64_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, uint64_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, char32_t value)
{
    IStream *output = writeTag(tag);

    writeInteger(output, static_cast<uint32_t>(value));
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, float value)
{
    IStream *output = writeTag(tag);

    writeReal(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, double value)
{
    IStream *output = writeTag(tag);

    writeReal(output, value);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, string_cref_t value)
{
    IStream *output = writeTag(tag);

    uint32_t stringID = _root->getStringID(value);
    writeStringField(output, stringID);
}

// Inherited from IObjectWriter.
void BinaryObjectWriter::write(string_cref_t tag, const void *value, size_t byteCount)
{
    IStream *output = writeTag(tag);

    writeByteFieldHeader(output, byteCount);

    size_t bytesWritten = output->write(value, byteCount);

    if (bytesWritten != byteCount)
        throw IOException("Failed to write byte block object property.");
}

// Inherited from IObjectWriter.
IStreamUPtr BinaryObjectWriter::beginWriteBytes(string_cref_t tag)
{
    // Write the tag to appear before the object data.
    writeTag(tag);

    return IStreamUPtr(new ByteBlockFieldStream(_root));
}

// Inherited from IObjectWriter.
IObjectWriter *BinaryObjectWriter::beginWriteObject(string_cref_t tag)
{
    // Write the tag to appear before the object data.
    writeTag(tag);

    return new BinaryObjectWriter(_root);
}

// Inherited from IObjectWriter.
IArrayWriter *BinaryObjectWriter::beginWriteArray(string_cref_t tag)
{
    // Write the tag to appear before the array data.
    writeTag(tag);

    return new BinaryArrayWriter(_root);
}

//! @brief Writes the tag proceeding an object property.
//! @param[in] tag The property tag.
//! @return The stream to write the property value to.
//! @throws ArgumentException Thrown if a property identified by @p tag has
//! already been written.
IStream *BinaryObjectWriter::writeTag(string_cref_t tag)
{
    auto result = _usedTags.insert(tag);

    if (result.second == false)
    {
        std::string message("A value has already been assigned to the '");
        appendAgString(message, tag);
        message.append("' property.");

        throw ArgumentException(message.c_str(), "tag");
    }

    uint32_t tagID = _root->getStringID(tag);

    writeStringField(_blockWriter, tagID);

    return _blockWriter;
}

}} // namespace Ag::IO
////////////////////////////////////////////////////////////////////////////////

