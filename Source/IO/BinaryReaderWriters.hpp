//! @file Ag/IO/BinaryReaderWriters.hpp
//! @brief The declaration of implementations of hierarchy reader/writer
//! interfaces which operate on a binary encoding.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_BINARY_READER_WRITERS_HPP_
#define HEADER_IO_BINARY_READER_WRITERS_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include <deque>
#include <unordered_map>

#include "HierarchyInterfaces.hpp"
#include "BinaryHierarchyEncoding.hpp"
#include "OutOfOrderStream.hpp"
#include "ReadOnlyDataSource.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
//! @brief An implementation of HierarchyRootPrivate based on a binary encoding.
class BinaryHierarchyRoot : public HierarchyRootPrivate
{
public:
    // Construction/Destruction
    BinaryHierarchyRoot(const BinaryStreamHeader &header, IStream *input);

    // Accessors
    ReadOnlyDataSource *getDataSource() const;
    bool tryGetString(uint32_t id, Ag::String &text) const;
    bool tryGetStringID(const Ag::String &text, uint32_t &id) const;

    bool tryReadBoolValue(FieldType fieldType,
                          const StreamRegion &fieldData,
                          bool &value) const;

    bool tryReadCharValue(FieldType fieldType,
                          const StreamRegion &fieldData,
                          char32_t &value) const;

    // Overrides
    virtual bool hasRootObject() const override;
    virtual bool hasRootArray() const override;
    virtual IObjectReader *getRootObject() override;
    virtual IArrayReader *getRootArray() override;
private:
    // Internal Types
    using SymbolIDMap = std::unordered_map<Ag::String, uint32_t>;

    // Internal Functions
    static StringCollection readStringTable(IStream *stream, size_t stringCount);

    // Internal Fields
    ReadOnlyDataSourceUPtr _source;
    StringCollection _symbols;
    SymbolIDMap _symbolIDsByText;
    StreamRegion _rootFieldData;
    FieldType _rootFieldType;
public:
    // Templates

    //! @brief Attempts to interpret a field as an integer.
    //! @tparam T The data type of the integer to interpret.
    //! @param[in] fieldType The data type of the field encoding.
    //! @param[in] fieldData The location of the field data.
    //! @param[out] value Receives the interpreted value on success.
    //! @retval true The value was read and successfully interpreted as an
    //! integer of appropriate size.
    //! @retval false The value could not be read, or could not be interpreted
    //! as the desired integer type.
    template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
    bool tryReadInteger(FieldType fieldType, const StreamRegion &fieldData, T &value) const
    {
        uint32_t stringID;
        bool hasValue = false;

        switch (fieldType)
        {
        case FieldType::TinyInt:
        case FieldType::PositiveInteger:
        case FieldType::NegativeInteger:
            hasValue = IO::tryReadInteger<T>(_source.get(), fieldType, fieldData, value);
            break;

        case FieldType::StringID:
            if (tryReadEncodedStringID(_source.get(), fieldData, stringID))
            {
                String textValue;

                hasValue = tryGetString(stringID, textValue) &&
                           textValue.tryParseScalar(value);
            }
            break;

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

    //! @brief Attempts to interpret a field as an floating point value.
    //! @tparam T The data type of the integer to interpret.
    //! @param[in] fieldType The data type of the field encoding.
    //! @param[in] fieldData The location of the field data.
    //! @param[out] value Receives the interpreted value on success.
    //! @retval true The value was read and successfully interpreted as an
    //! integer of appropriate size.
    //! @retval false The value could not be read, or could not be interpreted
    //! as the desired integer type.
    template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    bool tryReadReal(FieldType fieldType, const StreamRegion &fieldData, T &value) const
    {
        int64_t longValue;
        uint32_t stringID;
        bool hasValue = false;

        switch (fieldType)
        {
        case FieldType::TinyInt:
        case FieldType::PositiveInteger:
        case FieldType::NegativeInteger:
            if (IO::tryReadInteger<int64_t>(_source.get(), fieldType,
                                            fieldData, longValue))
            {
                value = static_cast<T>(longValue);
                hasValue = true;
            }
            break;

        case FieldType::StringID:
            if (tryReadEncodedStringID(_source.get(), fieldData, stringID))
            {
                String textValue;

                hasValue = tryGetString(stringID, textValue) &&
                           textValue.tryParseScalar(value);
            }
            break;

        case FieldType::Real:
            hasValue = IO::tryReadReal(_source.get(), fieldData, value);
            break;

        case FieldType::Bytes:
        case FieldType::Object:
        case FieldType::Array:
        default:
            hasValue = false;
            break;
        }

        return hasValue;
    }
};

//! @brief An alias for a shared pointer to a BinaryHierarchyRoot.
using BinaryHierarchyRootSPtr = std::shared_ptr<BinaryHierarchyRoot>;

//! @brief An implementation of IArrayReader which reads an array encoded as
//! binary data.
class BinaryArrayReader : public IArrayReader
{
public:
    // Construction/Destruction
    BinaryArrayReader(const BinaryHierarchyRootSPtr &root, const StreamRegion &region);

    // Overrides
    virtual bool hasMore() const override;
    virtual bool tryGetNextElementSize(StreamLength &elementSize) const override;
    virtual StreamLength getElementCount() const override;
    virtual StreamPosition getCurrentElementIndex() const override;
    virtual void reset() override;
    virtual void skip(StreamLength count) override;

    virtual bool tryReadNext(bool &value) override;
    virtual bool tryReadNext(int8_t &value) override;
    virtual bool tryReadNext(uint8_t &value) override;
    virtual bool tryReadNext(int16_t &value) override;
    virtual bool tryReadNext(uint16_t &value) override;
    virtual bool tryReadNext(int32_t &value) override;
    virtual bool tryReadNext(uint32_t &value) override;
    virtual bool tryReadNext(int64_t &value) override;
    virtual bool tryReadNext(uint64_t &value) override;
    virtual bool tryReadNext(char32_t &value) override;
    virtual bool tryReadNext(float &value) override;
    virtual bool tryReadNext(double &value) override;
    virtual bool tryReadNext(String &value) override;
    virtual bool tryReadNext(ByteBlock &value) override;
    virtual bool tryReadNext(ISeekableStreamUPtr &value) override;
    virtual bool tryReadNext(IObjectReader *&value) override;
    virtual bool tryReadNext(IArrayReader *&value) override;
private:
    // Internal Functions
    bool tryGetNextField(FieldType &fieldType, StreamRegion &fieldData) const;
    void commitField(StreamRegion &fieldData);

    // Internal Fields
    BinaryHierarchyRootSPtr _root;
    StreamRegion _data;
    StreamLength _elementCount;
    StreamLength _currentElement;
    StreamLength _currentOffset;
};

//! @brief An implementation of IObjectReader which reads object properties
//! serialized as binary data.
class BinaryObjectReader : public IObjectReader
{
public:
    // Construction/Destruction
    BinaryObjectReader(const BinaryHierarchyRootSPtr &root, const StreamRegion &region);

    // Accessors

    // Operations

    // Overrides
    virtual bool hasProperty(string_cref_t tag) const override;
    virtual bool tryGetPropertySize(string_cref_t tag,
                                    StreamLength &propSize) const override;

    virtual bool tryRead(string_cref_t tag, bool &value) const override;
    virtual bool tryRead(string_cref_t tag, int8_t &value) const override;
    virtual bool tryRead(string_cref_t tag, uint8_t &value) const override;
    virtual bool tryRead(string_cref_t tag, int16_t &value) const override;
    virtual bool tryRead(string_cref_t tag, uint16_t &value) const override;
    virtual bool tryRead(string_cref_t tag, int32_t &value) const override;
    virtual bool tryRead(string_cref_t tag, uint32_t &value) const override;
    virtual bool tryRead(string_cref_t tag, int64_t &value) const override;
    virtual bool tryRead(string_cref_t tag, uint64_t &value) const override;
    virtual bool tryRead(string_cref_t tag, char32_t &value) const override;
    virtual bool tryRead(string_cref_t tag, float &value) const override;
    virtual bool tryRead(string_cref_t tag, double &value) const override;
    virtual bool tryRead(string_cref_t tag, String &value) const override;
    virtual bool tryRead(string_cref_t tag, ByteBlock &value) const override;
    virtual bool tryRead(string_cref_t tag, ISeekableStreamUPtr &value) const override;
    virtual bool tryRead(string_cref_t tag, IObjectReader *&value) const override;
    virtual bool tryRead(string_cref_t tag, IArrayReader *&value) const override;
private:
    // Internal Types
    using FieldDataTagIDMap = Ag::LinearSortedMap<uint32_t, StreamRegion>;

    // Internal Functions
    bool tryFindField(string_cref_t tag, StreamRegion &fieldData) const;
    bool tryGetFieldValue(string_cref_t tag, FieldType &feldType,
                          StreamRegion &fieldValue) const;

    // Internal Fields
    BinaryHierarchyRootSPtr _root;
    FieldDataTagIDMap _regionsByTagID;
};

//! @brief An implementation if IArrayWriter which encodes array elements as
//! binary data.
class BinaryWriterRoot : public std::enable_shared_from_this<BinaryWriterRoot>
{
public:
    // Construction/Destruction
    BinaryWriterRoot(ISeekableStream *output, const void *rootWriter, bool compress);
    ~BinaryWriterRoot() = default;

    // Accessors
    bool isRootWriter(const void *ptr) const;
    OutOfOrderStream &getOutput();

    // Operations
    uint32_t getStringID(string_cref_t symbol);
    void write();
private:
    // Internal Types
    using SymbolIDMap = std::unordered_map<String, uint32_t>;
    using StringBag = std::deque<String>;

    // Internal Functions
    StreamLength writeStringTable(IStream *output) const;

    // Internal Fields
    OutOfOrderStream _payloadStream;
    SymbolIDMap _symbolIDByValue;
    StringBag _symbols;
    ISeekableStream *_output;
    uintptr_t _rootWriter;
    bool _compress;
};

//! @brief An alias for a shared pointer to a BinaryWriterRoot.
using BinaryWriterRootSPtr = std::shared_ptr<BinaryWriterRoot>;

//! @brief An implementation if IArrayWriter which encodes array elements as
//! binary data.
class BinaryArrayWriter : public IArrayWriter
{
public:
    // Construction/Destruction
    BinaryArrayWriter() = delete;
    BinaryArrayWriter(ISeekableStream *output, bool compress);
    BinaryArrayWriter(const BinaryWriterRootSPtr &root);
    virtual ~BinaryArrayWriter() override;

    // Overrides
    virtual void write(bool value) override;
    virtual void write(int8_t value) override;
    virtual void write(uint8_t value) override;
    virtual void write(int16_t value) override;
    virtual void write(uint16_t value) override;
    virtual void write(int32_t value) override;
    virtual void write(uint32_t value) override;
    virtual void write(int64_t value) override;
    virtual void write(uint64_t value) override;
    virtual void write(char32_t value) override;
    virtual void write(float value) override;
    virtual void write(double value) override;
    virtual void write(string_cref_t value) override;
    virtual void write(const void *value, size_t byteCount) override;
    virtual IStreamUPtr beginWriteBytes() override;
    virtual IObjectWriter *beginWriteObject() override;
    virtual IArrayWriter *beginWriteArray() override;

private:
    // Internal Fields
    BinaryWriterRootSPtr _root;
    OutOfOrderStream::Stream *_blockWriter;
    OutOfOrderStream::BlockRef _payloadBlock;
    StreamLength _elementCount;
};

//! @brief An implementation of IObjectWriter which encodes object properties as
//! binary data.
class BinaryObjectWriter : public IObjectWriter
{
public:
    // Construction/Destruction
    BinaryObjectWriter() = delete;
    BinaryObjectWriter(ISeekableStream *output, bool compress);
    BinaryObjectWriter(const BinaryWriterRootSPtr &root);
    virtual ~BinaryObjectWriter() override;

    // Overrides
    virtual void write(string_cref_t tag, bool value) override;
    virtual void write(string_cref_t tag, int8_t value) override;
    virtual void write(string_cref_t tag, uint8_t value) override;
    virtual void write(string_cref_t tag, int16_t value) override;
    virtual void write(string_cref_t tag, uint16_t value) override;
    virtual void write(string_cref_t tag, int32_t value) override;
    virtual void write(string_cref_t tag, uint32_t value) override;
    virtual void write(string_cref_t tag, int64_t value) override;
    virtual void write(string_cref_t tag, uint64_t value) override;
    virtual void write(string_cref_t tag, char32_t value) override;
    virtual void write(string_cref_t tag, float value) override;
    virtual void write(string_cref_t tag, double value) override;
    virtual void write(string_cref_t tag, string_cref_t value) override;
    virtual void write(string_cref_t tag, const void *value, size_t byteCount) override;
    virtual IStreamUPtr beginWriteBytes(string_cref_t tag) override;
    virtual IObjectWriter *beginWriteObject(string_cref_t tag) override;
    virtual IArrayWriter *beginWriteArray(string_cref_t tag) override;

private:
    // Internal Functions
    IStream *writeTag(string_cref_t tag);

    // Internal Fields
    BinaryWriterRootSPtr _root;
    OutOfOrderStream::Stream *_blockWriter;
    OutOfOrderStream::BlockRef _payloadBlock;
    StringSet _usedTags;
};

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
