//! @file Ag/IO/HierarchySerialization.hpp
//! @brief The declaration of objects to allow a hierarchy of objects to be
//! loaded and saved as a stream of bytes.
//! @author GiantRobotLemur@na-se.co.uk
//! @date 2026
//! @copyright This file is part of the Silver (Ag) project which is released
//! under LGPL 3 license. See LICENSE file at the repository root or go to
//! https://github.com/GiantRobotLemur/Ag for full license details.
////////////////////////////////////////////////////////////////////////////////

#ifndef HEADER_IO_HIERARCHY_SERIALIZTION_HPP_
#define HEADER_IO_HIERARCHY_SERIALIZTION_HPP_

////////////////////////////////////////////////////////////////////////////////
// Dependent Header Files
////////////////////////////////////////////////////////////////////////////////
#include "ISeekableStream.hpp"
#include "Exceptions.hpp"

namespace Ag {
namespace IO {

////////////////////////////////////////////////////////////////////////////////
// Class Declarations
////////////////////////////////////////////////////////////////////////////////
class IObjectReader;
class IObjectWriter;
class IArrayReader;
class IArrayWriter;

class ArrayReader;
class ArrayWriter;

//! @brief An object which reads a serialized object in a serialized hierarchy.
class ObjectReader
{
public:
    // Construction/Destruction
    ObjectReader();
    ObjectReader(IObjectReader *reader);
    ObjectReader(const ObjectReader &) = delete;
    ObjectReader(ObjectReader &&rhs) noexcept;
    ~ObjectReader();

    // Accessors
    bool isBound() const;
    bool hasProperty(string_cref_t tag) const;
    StreamLength getPropertySize(string_cref_t tag) const;
    bool tryGetPropertySize(string_cref_t tag, StreamLength &propSize) const;

    // Operations
    void close();
    ObjectReader &operator=(const ObjectReader &) = delete;
    ObjectReader &operator=(ObjectReader &&rhs) noexcept;

    bool tryRead(string_cref_t tag, bool &value) const;
    bool tryRead(string_cref_t tag, int8_t &value) const;
    bool tryRead(string_cref_t tag, uint8_t &value) const;
    bool tryRead(string_cref_t tag, int16_t &value) const;
    bool tryRead(string_cref_t tag, uint16_t &value) const;
    bool tryRead(string_cref_t tag, int32_t &value) const;
    bool tryRead(string_cref_t tag, uint32_t &value) const;
    bool tryRead(string_cref_t tag, int64_t &value) const;
    bool tryRead(string_cref_t tag, uint64_t &value) const;
    bool tryRead(string_cref_t tag, char32_t &value) const;
    bool tryRead(string_cref_t tag, float &value) const;
    bool tryRead(string_cref_t tag, double &value) const;
    bool tryRead(string_cref_t tag, Ag::String &value) const;
    bool tryRead(string_cref_t tag, ByteBlock &value) const;
    bool tryRead(string_cref_t tag, ISeekableStreamUPtr &value) const;
    bool tryRead(string_cref_t tag, ObjectReader &value) const;
    bool tryRead(string_cref_t tag, ArrayReader &value) const;

    bool readBool(string_cref_t tag) const;
    int8_t readInt8(string_cref_t tag) const;
    uint8_t readUint8(string_cref_t tag) const;
    int16_t readInt16(string_cref_t tag) const;
    uint16_t readUint16(string_cref_t tag) const;
    int32_t readInt32(string_cref_t tag) const;
    uint32_t readUint32(string_cref_t tag) const;
    int64_t readInt64(string_cref_t tag) const;
    uint64_t readUint64(string_cref_t tag) const;
    char32_t readChar(string_cref_t tag) const;
    float readFloat(string_cref_t tag) const;
    double readDouble(string_cref_t tag) const;
    String readString(string_cref_t tag) const;
    ByteBlock readBytes(string_cref_t tag) const;
    ISeekableStreamUPtr readBytesStream(string_cref_t tag) const;
    ObjectReader readObject(string_cref_t tag) const;
    ArrayReader readArray(string_cref_t tag) const;
private:
    // Internal Functions
    IObjectReader *verifyAccess(utf8_cptr_t op) const;

    // Internal Fields
    IObjectReader *_reader;

    // Templates

    //! @brief Reads an object property, throwing an exception on failure.
    //! @tparam T The data type of the property value to return.
    //! @param[in] tag The tag identifying the property to obtain.
    //! @param[in] dataType A text rendering of the data type used in
    //! error messages.
    //! @return The value of the property read from the serialized object.
    //! @throws ObjectNotBoundException Thrown if the object is not bound to
    //! an underlying reader.
    //! @throws PropertyNotFoundException Thrown if the property does not exist.
    //! @throws PropertyTypeException If the property exists but the value cannot
    //! be converted to the appropriate type.
    template<typename T>
    T read(string_cref_t tag, utf8_cptr_t dataType) const
    {
        IObjectReader *reader = verifyAccess("read property");

        T value;

        if (reader->tryRead(tag, value))
            return value;

        if (reader->hasProperty(tag) == false)
            throw PropertyNotFoundException(tag);

        throw PropertyTypeException(tag, dataType);
    }
};

//! @brief An object which writes an object to a serialized hierarchy.
class ObjectWriter
{
public:
    // Construction/Destruction
    ObjectWriter();
    ObjectWriter(IObjectWriter *writer);
    ObjectWriter(const ObjectWriter &) = delete;
    ObjectWriter(ObjectWriter &&rhs) noexcept;
    ~ObjectWriter();

    // Accessors
    bool isBound() const;

    // Operations
    void close();
    ObjectWriter &operator=(const ObjectWriter &) = delete;
    ObjectWriter &operator=(ObjectWriter &&rhs) noexcept;

    void write(string_cref_t tag, bool value);

    void write(string_cref_t tag, int8_t value);
    void write(string_cref_t tag, uint8_t value);
    void write(string_cref_t tag, int16_t value);
    void write(string_cref_t tag, uint16_t value);
    void write(string_cref_t tag, int32_t value);
    void write(string_cref_t tag, uint32_t value);
    void write(string_cref_t tag, int64_t value);
    void write(string_cref_t tag, uint64_t value);
    void write(string_cref_t tag, char32_t value);
    void write(string_cref_t tag, float value);
    void write(string_cref_t tag, double value);
    void write(string_cref_t tag, string_cref_t value);
    void write(string_cref_t tag, const void *value, size_t byteCount);
    IStreamUPtr beginWriteBytes(string_cref_t tag);
    ObjectWriter beginWriteObject(string_cref_t tag);
    ArrayWriter beginWriteArray(string_cref_t tag);
private:
    // Internal Functions
    IObjectWriter *verifyAccess(utf8_cptr_t op);

    // Internal Fields
    IObjectWriter *_writer;
};

//! @brief An object which reads a serialized array in a serialized hierarchy.
class ArrayReader
{
public:
    // Construction/Destruction
    ArrayReader();
    ArrayReader(IArrayReader *reader);
    ArrayReader(const ArrayReader &) = delete;
    ArrayReader(ArrayReader &&) noexcept;
    ~ArrayReader();

    // Accessors
    bool isBound() const noexcept;
    bool hasMore() const;
    StreamLength getNextElementSize() const;
    bool tryGetNextElementSize(StreamLength &elementSize) const;
    StreamLength getElementCount() const;
    StreamPosition getCurrentElementIndex() const;

    // Operations
    void close();
    void reset();
    void skip(StreamLength count);

    ArrayReader &operator=(const ArrayReader &) = delete;
    ArrayReader &operator=(ArrayReader &&rhs) noexcept;

    bool tryReadNext(bool &value);
    bool tryReadNext(int8_t &value);
    bool tryReadNext(uint8_t &value);
    bool tryReadNext(int16_t &value);
    bool tryReadNext(uint16_t &value);
    bool tryReadNext(int32_t &value);
    bool tryReadNext(uint32_t &value);
    bool tryReadNext(int64_t &value);
    bool tryReadNext(uint64_t &value);
    bool tryReadNext(char32_t &value);
    bool tryReadNext(float &value);
    bool tryReadNext(double &value);
    bool tryReadNext(String &value);
    bool tryReadNext(ByteBlock &value);
    bool tryReadNext(ISeekableStreamUPtr &value);
    bool tryReadNext(ObjectReader &value);
    bool tryReadNext(ArrayReader &value);

    bool readNextBool();
    int8_t readNextInt8();
    uint8_t readNextUint8();
    int16_t readNextInt16();
    uint16_t readNextUint16();
    int32_t readNextInt32();
    uint32_t readNextUint32();
    int64_t readNextInt64();
    uint64_t readNextUint64();
    char32_t readNextChar();
    float readNextFloat();
    double readNextDouble();
    String readNextString();
    ByteBlock readNextBytes();
    ISeekableStreamUPtr readNextByteStream();
    ObjectReader readNextObject();
    ArrayReader readNextArray();
private:
    // Internal Functions
    IArrayReader *verifyAccess(utf8_cptr_t op) const;
    IArrayReader *verifyElementAccess(utf8_cptr_t op) const;

    // Internal Fields
    IArrayReader *_reader;

    // Templates

    //! @brief Attempts to read the next array element as a specified type.
    //! @tparam T The data type of the element to return.
    //! @param[in] dataType A text rendering of the data type used in
    //! error messages.
    //! @return The next array element converted to the required type if necessary.
    //! @throws ObjectNotBoundException Thrown if the object is not bound to
    //! an underlying reader.
    //! @throws DataFormatException Thrown if there are no more elements
    //! left to read.
    //! @throws PropertyTypeException Thrown if an element is available but could
    //! not be converted to the desired data type.
    template<typename T>
    T readNext(utf8_cptr_t dataType)
    {
        IArrayReader *reader = verifyAccess("read next element");
        T next;

        if (reader->tryReadNext(next))
            return next;

        if (reader->hasMore() == false)
            throw DataFormatException("The end of the array has been reached.");

        throw PropertyTypeException(dataType);
    }
};

//! @brief An object which writes and array to a serialized hierarchy.
class ArrayWriter
{
public:
    // Construction/Destruction
    ArrayWriter();
    ArrayWriter(IArrayWriter *writer);
    ArrayWriter(const ArrayWriter &) = delete;
    ArrayWriter(ArrayWriter &&rhs) noexcept;
    ~ArrayWriter();

    // Accessors
    bool isBound() const;

    // Operations
    void close();
    ArrayWriter &operator=(const ArrayWriter &) = delete;
    ArrayWriter &operator=(ArrayWriter &&) noexcept;

    void write(bool value);
    void write(int8_t value);
    void write(uint8_t value);
    void write(int16_t value);
    void write(uint16_t value);
    void write(int32_t value);
    void write(uint32_t value);
    void write(int64_t value);
    void write(uint64_t value);
    void write(char32_t value);
    void write(float value);
    void write(double value);
    void write(string_cref_t value);
    void write(const void *value, size_t byteCount);
    IStreamUPtr beginWriteBytes();
    ObjectWriter beginWriteObject();
    ArrayWriter beginWriteArray();
private:
    // Internal Functions
    IArrayWriter *verifyAccess(utf8_cptr_t op);

    // Internal Fields
    IArrayWriter *_writer;
};

//! @brief Represents the root of a hierarchy of serialized objects.
//! @remarks Access to the serialized data via sub-objects is coupled with the
//! lifetime of this object.
class HierarchyRoot
{
public:
    // Construction/Destruction
    HierarchyRoot(IStream *input);
    ~HierarchyRoot();

    // Accessors
    bool hasRootObject() const;
    bool hasRootArray() const;
    ObjectReader getRootObject();
    ArrayReader getRootArray();

private:
    // Internal Fields
    SharedVirtualBaseSPtr _root;
};

////////////////////////////////////////////////////////////////////////////////
// Function Declarations
////////////////////////////////////////////////////////////////////////////////
ArrayWriter beginSerializeArray(ISeekableStream *output, bool compress);
ObjectWriter beginSerializeObject(ISeekableStream *output, bool compress);

}} // namespace Ag::IO

#endif // Header guard
////////////////////////////////////////////////////////////////////////////////
